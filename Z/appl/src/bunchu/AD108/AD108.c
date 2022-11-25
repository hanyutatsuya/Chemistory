/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：AD108.c                                                      */
/* 　概　　　要：３ＩＤ情報展開                                               */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2008/02/12     moriya         新規作成                           */
/*  1.01     2008/11/13     sekiya         薬剤ＷＳの並び順がおかしくなること */
/*                                         に対する対応                       */
/*  1.02     2008/12/22     sekiya         SKIPファイルを出力している時に、   */
/*                                         AD107がアクセスしないように        */
/*                                         １度、tmpに出力してリネームする    */
/*                                         ように仕様を変更                   */
/******************************************************************************/

/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <dirent.h>
#include <fcntl.h>
#include <time.h>
#include <ctype.h>
#include <stdarg.h>

#include "bmllog.h"
#include "bmlprm.h"
#include "bml_misc.h"
#include "bml_date.h"

#include "sql.h"

#include "AD108.h"

/******************************************************************************/
/* Define定義                                                                 */
/******************************************************************************/
//	TRACE
#if defined ( _TRACE )
#define malloc(a)   _malloc(a, __FILE__, __LINE__)
#define free(p)     _free(p, __FILE__, __LINE__)
#endif

//  フラグ定義
typedef enum {
    LC_false,
    LC_true
} LC_BOOLEAN ;

/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/
MYAPP_STSCODE			 gintErrorCode ;
MYAPP_SYSTEM_VERSION	 gtSystemVersion ;
struct stcLogMember		 gstLogMem ;		//	ログ出力情報

/******************************************************************************/
/* 関数宣言                                                                   */
/******************************************************************************/
//	BUNPOS情報展開関連関数
static	int		sFncTrFileRead ( struct appEnv *, char *, int * ) ;
/* 1.01 対応のため引数を変更 */
static  int     AbunGetSort ( struct appEnv *, char *, char ) ;
static	int		AgetSortInfo( BUNSORT ** ) ;

//	ファイル出力関数
static	int 	sFncOutput ( struct appEnv *, char *, char * ) ;

//	共有メモリ操作関数
static	int		sFncShmCrt ( struct appEnv * ) ;
static	int		sFncShmGet ( struct appEnv * , int *) ;
static	int		sFncShmDel ( struct appEnv * ) ;

//	コールバック関数
static	int		sFncFileFillter ( struct dirent * ) ;

//	その他
static	void	sFncGetNowdate ( char *, char * ) ;
static	void	sFncGetNowdate1 ( char * ) ;
static	int		sFncFileRename ( char *, char *, char *, char * ) ;
static	void	sFncTrim ( char * ) ;


/******************************************************************************/
/*  関 数 名　：initFunction()												  */
/*  機能概要　：初期処理関数												  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct	env *   	プログラム環境構造体		 			  */
/*  出　　力　：                                                              */
/*  復帰情報　：  0     : 成功												  */
/* 　　　　　　　-1     : 失敗												  */
/******************************************************************************/
int
initFunction( argc, argv, pAppEnv )
int					 argc ;
char				*argv[] ;
struct appEnv	*pAppEnv ;
{
	char	 lc_prmBuf[256] ;
	long	 ll_retSts ;
	char	*lc_login ;

	/***
	 ***	初期化	
	 ***/
	//	エラーステータス変更
	gintErrorCode = 0 ;

	//	プログラム環境変数初期化
	memset ( pAppEnv , '\0', sizeof ( struct appEnv ) ) ;

	/***
	 ***	ログオープン (AD108_LOG.ini)
	 ***/
	if ( ZbmlOpenLog ( MYAPP_LOGINIFILE ) != 0 ) {
		return ( -1 ) ;
	}

	//	ログ情報初期設定
	memset ( &gstLogMem, '\0', sizeof ( gstLogMem ) ) ;
	if ( ( lc_login = getenv( "LOGNAME" ) ) != NULL ) {
		strcpy ( gstLogMem.pcLoginId, lc_login ) ;
	}
	strcpy ( gstLogMem.pcAppName, MYAPP_APP_NAME ) ;

	//	開始ログ出力
	sFncPutLog ( TRCKIND_OPT, __FILE__, "", __LINE__,
				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "プログラム起動" ) ;

	/***
	 ***	引数チェック	
	 ***/
	if ( argc != 2 ) {
		gintErrorCode = MYAPP_STSCODE_ERR_USEGE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "initFunction", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "コマンドパラメータに誤りがあります" ) ;
		return ( -1 ) ;
	}

	/***
	 ***	パラメータファイル情報退避
	 ***/
	//	パラメータファイル名退避 (AD108.ini)
	pAppEnv->pcFielNamePRM = argv[1] ;

	//	パラメータファイルオープン	
	pAppEnv->bp = ZbmlPrmOpen ( pAppEnv->pcFielNamePRM ) ;
	if ( pAppEnv->bp == NULL ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmOpen", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータファイルのオープンに失敗しました[%s]", pAppEnv->pcFielNamePRM ) ;
		return ( -1 ) ;
	}

	//	BUNPOS展開ファイルディレクトリ
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_3ID, pAppEnv->cDir3Id ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_3ID ) ;
		return ( -1 ) ;
	}

	//	BUNPOS展開ファイルOKディレクトリ
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_3ID_OK, pAppEnv->cDir3IdOk ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_3ID_OK ) ;
		return ( -1 ) ;
	}

	//	BUNPOS展開ファイルNGディレクトリ
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_3ID_NG, pAppEnv->cDir3IdNg ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_3ID_NG ) ;
		return ( -1 ) ;
	}

	//	BUNPOS展開ファイルSKIPディレクトリ
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_3ID_SKIP, pAppEnv->cDir3IdSkip ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_3ID_SKIP ) ;
		return ( -1 ) ;
	}

	//	共有メモリキー取得
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_SHM_KEY, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_SHM_KEY ) ;
		return ( -1 ) ;
	}
	pAppEnv->shm_Key = atoi ( lc_prmBuf ) ;

	//	SLEEPSEC取得
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_SLEEP_SEC, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_SLEEP_SEC ) ;
		return ( -1 ) ;
	}
	pAppEnv->sleep_Sec= atoi ( lc_prmBuf ) ;

	//	データベース名
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DB_NAME, pAppEnv->cDb_Name ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DB_NAME ) ;
		return ( -1 ) ;
	}

	//	データベースユーザ
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DB_USER, pAppEnv->cDb_User ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DB_USER ) ;
		return ( -1 ) ;
	}

	//	データベースパスワード
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DB_PASSWD, pAppEnv->cDb_Passwd ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DB_PASSWD ) ;
		return ( -1 ) ;
	}

	//	ラボコード
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_LABOCD, pAppEnv->cLbcd ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_LABOCD ) ;
		return ( -1 ) ;
	}

	//	サテライトＩＤ
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_SATECD, pAppEnv->cSateid ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_SATECD ) ;
		return ( -1 ) ;
	}

	//	ファイル読込リトライ回数
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_FILE_RETRY, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_FILE_RETRY ) ;
		return ( -1 ) ;
	}
	pAppEnv->fileRetry = atoi ( lc_prmBuf ) ;

	//	パラメータファイルクローズ	
	ZbmlPrmClose ( pAppEnv->bp ) ;

	// ソートキー情報の取得
	if( (pAppEnv->pSortNo = AgetSortInfo(&pAppEnv->pSort)) < 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "AgetSortInfo", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "SORTキー情報が取得できませんでした[%s]", MYAPP_AD105SORTINIFILE ) ;
		return ( -1 ) ;
	}

	/***
	 ***	共有メモリ生成	
	 ***/
	if ( sFncShmCrt ( pAppEnv ) < 0 ) {
		return ( -1 ) ;
	}

	/***
	 ***	データベースオープン
	 ***/
	ll_retSts = ZdbConnect( pAppEnv->cDb_Name, pAppEnv->cDb_User, pAppEnv->cDb_Passwd ) ;
	if ( ll_retSts != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_DB ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZdbConnect", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "データベースオープンに失敗しました[DB=%s USER=%s PASS=%s]", pAppEnv->cDb_Name, pAppEnv->cDb_User, pAppEnv->cDb_Passwd ) ;
		return ( -1 ) ;
	}

	return ( 0 ) ; 
}

/******************************************************************************/
/*  関 数 名　：mainFunction()												  */
/*  機能概要　：メイン処理関数												  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct	env *   	プログラム環境構造体。		 			  */
/*  出　　力　：                                                              */
/*  復帰情報　：  0     : 成功												  */
/* 　　　　　　　-1     : 失敗												  */
/******************************************************************************/
int
mainFunction( pAppEnv )
struct appEnv	*pAppEnv ;
{
	int				  li_retSts ;
	long			  ll_retSts ;
	int				  li_idx ;	
	int				  li_stopFlg ;
	int				  li_OkSkipFlg ;
	char			  sDttm[128];

	//	ディレクトリ情報 
	DIR				 *lt_dp ;
	struct dirent	**lpst_dirBuf ;

	//	指定ディレクトリ内ファイルカウント
	int				  li_fileCnt ;

	/***
	 ***	BUNPOSファイル情報展開処理
	 ***		永久ループ
	 ***		停止コマンドで終了
	 ***/
	while ( 1 ) {

		/***
		 *** ファイル名取得
		 ***/
		if ( ( li_fileCnt = scandir ( pAppEnv->cDir3Id, 
									  &lpst_dirBuf,
									  (void*)sFncFileFillter,
					   				  alphasort ) ) < 0 ) {
			//	異常終了	LOG
			gintErrorCode = MYAPP_STSCODE_ERR_DIR;
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "scandir", __LINE__,
				 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 	 "3ID情報ファイルの取得に失敗しました" ) ;
			return ( -1 ) ;
		}

		if( li_fileCnt ) {
			//トレースログ
			memset(sDttm, 0, sizeof(sDttm));
			sFncGetNowdate1( sDttm ) ;
			sFncPutLog ( TRCKIND_OPT, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						 "処理開始(%s) ファイル数(%d)", sDttm, li_fileCnt);
		}

		/***
		 ***	データ処理
		 ***/
		li_idx = 0 ;
		for ( li_idx = 0 ; li_idx < li_fileCnt ; li_idx ++ ) {

			//	BUNPOS情報ファイル取得
			li_retSts=sFncTrFileRead ( pAppEnv,lpst_dirBuf[li_idx]->d_name, &li_OkSkipFlg ) ;
			if ( li_retSts < 0 ) {
				// NGディレクトリに移動
				sFncPutLog ( TRCKIND_OPT, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							 "  RENAME NG [%s/%s]->[%s/%s]", pAppEnv->cDir3Id, lpst_dirBuf[li_idx]->d_name, pAppEnv->cDir3IdNg, lpst_dirBuf[li_idx]->d_name);
				sFncFileRename ( pAppEnv->cDir3Id, 
								 lpst_dirBuf[li_idx]->d_name,
								 pAppEnv->cDir3IdNg,
								 lpst_dirBuf[li_idx]->d_name ) ;
				// BUNPOS情報ファイルの処理を行う
				free ( lpst_dirBuf[li_idx] ) ;
				continue ;
			} else if ( li_retSts == 2 ) {
				// BUNPOS情報ファイル以外
				// 次のBUNPOS情報ファイルの処理を行う
				free ( lpst_dirBuf[li_idx] ) ;
				continue ;
			} else {
				// テーブルのUPDATEに成功した(POS、SKIPファイル両方とも) or POSファイルの場合
				if ( li_OkSkipFlg == 0 ) {
					// OKディレクトリに移動
					sFncPutLog ( TRCKIND_OPT, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								 "  RENAME OK [%s/%s]->[%s/%s]", pAppEnv->cDir3Id, lpst_dirBuf[li_idx]->d_name, pAppEnv->cDir3IdOk, lpst_dirBuf[li_idx]->d_name);
					sFncFileRename ( pAppEnv->cDir3Id, 
									 lpst_dirBuf[li_idx]->d_name,
									 pAppEnv->cDir3IdOk,
									 lpst_dirBuf[li_idx]->d_name ) ;

				// 元ファイルがSKIPファイルで、UPDATEできなかった場合
				} else {
					// 読み込み元ファイル(SKIP.～)をSKIPディレクトリに移動
					sFncPutLog ( TRCKIND_OPT, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								 "  RENAME SKIP [%s/%s]->[%s/%s]", pAppEnv->cDir3Id, lpst_dirBuf[li_idx]->d_name, pAppEnv->cDir3IdSkip, lpst_dirBuf[li_idx]->d_name);
					sFncFileRename ( pAppEnv->cDir3Id, 
									 lpst_dirBuf[li_idx]->d_name,
									 pAppEnv->cDir3IdSkip,
									 lpst_dirBuf[li_idx]->d_name ) ;
				}
			}
				
			//	解放
			free ( lpst_dirBuf[li_idx] ) ;

			/***
		 	 *** 停止コマンド確認
		 	 ***/
			if ( sFncShmGet ( pAppEnv, &li_stopFlg ) == 0 ) {
				if ( li_stopFlg == 1 ) {
					break ;
				}
			}
		}

		/***
		 *** 停止コマンド確認
		 ***/
		if ( sFncShmGet ( pAppEnv, &li_stopFlg ) == 0 ) {
			if ( li_stopFlg == 1 ) {
				break ;
			}
		}

		/***
		 *** スリープ
		 ***/
		sleep ( pAppEnv->sleep_Sec ) ;
	}


	return ( 0 ) ;
}

/******************************************************************************/
/*  関 数 名　：endFunction()												  */
/*  機能概要　：終了処理関数												  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct	env *   	プログラム環境構造体。		 			  */
/*  出　　力　：                                                              */
/*  復帰情報　：  0     : 成功												  */
/* 　　　　　　　-1     : 失敗												  */
/******************************************************************************/
void
endFunction( pAppEnv )
struct appEnv	*pAppEnv ;
{
	/***
	 ***	データベースクローズ
	 ***/
	ZdbDisConnect() ;

	/***
	 ***	共有メモリ削除	
	 ***/
	sFncShmDel ( pAppEnv ) ;

	/***
	 ***	ログクロース
	 ***/
	//	開始ログ出力
	sFncPutLog ( TRCKIND_OPT, __FILE__, "", __LINE__,
				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "プログラム終了" ) ;
	ZbmlCloseLog() ;
	
	return ;
}

/******************************************************************************/
/*  関 数 名　：sFncTrFileRead()			 								  */
/*  機能概要　：BUNPOS情報ファイル読込										  */
/*	特記事項  ：第２引数はfree												  */
/*              1.01 SMPCDごとに分注結果を取得するように変更                  */
/*  入　　力　：															  */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体					  */
/*　 第２引数 ：char *  	 		BUNPOS情報ファイル名					  */
/*  出　　力　：															  */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
/*					 1	データ異常											  */
/******************************************************************************/
static	int
sFncTrFileRead ( pAppEnv, pc_trFileName, piOkSkipFlg )
struct appEnv	*pAppEnv ;
char			*pc_trFileName ;
int				*piOkSkipFlg ;
{
	FILE				*lfp ;
	ID3Info				*pId3Info ;
	ID3TB				 strId3Tb ;
	char				 lc_recBuf[MYAPP_RECV_RECSIZE] ;
	int					 li_recBuflen;
	int					 li_retryCnt ;
	char				 lc_fileName[1024] ;
	char				 cEnd ;
	char                 cBnckka ;
	struct stat			 lst_statBuf ;
	int					 li_retSts ;
	int					 li_EndFlg ;
	LC_BOOLEAN			 blnErrFlg ;
	LC_BOOLEAN			 blnNotFoundFlg ;

	int					 li_idx ;
	int					 li_CntSmpcd ;
	SORTInfo			*pSortInfo ;

	/***
	 ***	変数初期化
	 ***/
	blnErrFlg = LC_false ;
	blnNotFoundFlg = LC_false ;
	li_EndFlg = 0 ;
	cEnd = '0' ;
	*piOkSkipFlg = 0 ;

	li_idx = 0 ;
	li_CntSmpcd = 0 ;

	/***
	 ***	ファイル属性チェック
	 ***/
	//	ファイル名作成
	sprintf ( lc_fileName, "%s/%s", pAppEnv->cDir3Id, pc_trFileName ) ;
	//	ファイル属性取得
	if ( stat ( lc_fileName, &lst_statBuf ) < 0 ) {
			//	異常終了	LOG
			gintErrorCode = MYAPP_STSCODE_ERR_DIR;
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "stat", __LINE__,
				 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 	 "ファイル属性の取得に失敗しました[%s]", lc_fileName ) ;
			return ( -1 ) ;
	}
	//	通常ファイル以外は処理を行わない
	if ( !S_ISREG ( lst_statBuf.st_mode ) ) {
			return ( 2 ) ;
	}

	/***
	 ***	読込処理
	 ***/
	li_retryCnt = 0 ;
	while ( li_retryCnt  < pAppEnv->fileRetry ) {
		// ファイルオープン	
		lfp = fopen ( lc_fileName, "r" ) ;
		
		// ファイルオープン失敗
		if ( lfp == NULL ) {
			li_retryCnt ++ ;
			
			if ( li_retryCnt == pAppEnv->fileRetry ) {
				//	異常終了	LOG
				gintErrorCode = MYAPP_STSCODE_ERR_TR_FILE ;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 	 	"ファイルの読み込みに失敗しました[%s] retry[%d]", lc_fileName, li_retryCnt ) ;
				if ( lfp != NULL ) {
					fclose ( lfp ) ;
				}
				return ( -1 ) ;
			}
			continue ;
		} else {
			break ;
		}
	}

	memset(lc_recBuf, 0, MYAPP_RECV_RECSIZE) ;
	memset(&strId3Tb, 0, sizeof(ID3TB)) ;

	// 1レコードずつ処理
	while ( fgets ( lc_recBuf, sizeof ( lc_recBuf ), lfp ) != NULL ) {
		// 改行コード置換
		li_recBuflen = strlen ( lc_recBuf ) ;
		if ( lc_recBuf[li_recBuflen-2] == '\r' ) {
			lc_recBuf[li_recBuflen-2] = '\0' ;
		}
		if ( lc_recBuf[li_recBuflen-1] == '\n' ) { 
			lc_recBuf[li_recBuflen-1] = '\0' ;
		}

		// SQL結果フラグ初期化
		blnErrFlg 	= LC_false ;
		blnNotFoundFlg  = LC_false ;

		// BUNPOSレコード分割
		pId3Info = (ID3Info *)lc_recBuf ;

		/*** BUNPOSレコードから各値を設定 ***/
		// 受付日
		memcpy( strId3Tb.cUtkymd, pId3Info->cUtkymd, sizeof(pId3Info->cUtkymd) ) ;
		// 依頼書No
		memcpy( strId3Tb.cIrino, pId3Info->cIrino, sizeof(pId3Info->cIrino) ) ;
		// 処理日
		memcpy( strId3Tb.cSriymd, pId3Info->cSriymd, sizeof(pId3Info->cSriymd) ) ;
		// 検体番号
		memcpy( strId3Tb.cKntno, pId3Info->cKntno, sizeof(pId3Info->cKntno) ) ;
		// ラックID
		memcpy( strId3Tb.cRackId, pId3Info->cRackId, sizeof(pId3Info->cRackId) ) ;
		// ラックポジション
		memcpy( strId3Tb.cRackPos, pId3Info->cRackPos, sizeof(pId3Info->cRackPos) ) ;
		// 予備
		memcpy( strId3Tb.cYobi, pId3Info->cYobi, sizeof(pId3Info->cYobi) ) ;

		// ENDレコードかどうか判断する
		if ( !memcmp( strId3Tb.cUtkymd, RECEND_3RDID, 3 ) ) {

			cEnd = '1' ;

			// 3ID ENDレコードの場合
			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						 "3ID ENDレコード展開 TBL[SYSKNRMST] LBCD[%s] SATEID[%s] NSKENDFLG[%c]", pAppEnv->cLbcd, pAppEnv->cSateid, cEnd ) ;

			/********************************************/
			/***                                      ***/
			/***  システム管理マスタテーブルをUPDATE  ***/
			/***                                      ***/
			/********************************************/

			// システム管理マスタテーブルをUPDATE
			li_retSts = sFncUpdSYSKNRMST( pAppEnv->cLbcd, pAppEnv->cSateid, cEnd ) ;
			if ( li_retSts == MYAPP_SQL_NOTFOUND )
			{
				//更新対象データがない場合
				blnNotFoundFlg = LC_true ;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"UPDATE SYSKNRMST NOTFOUND[%ld] LBCD[%s] SATEID[%s] NSKENDFLG[%c]", pAppEnv->cLbcd, pAppEnv->cSateid, cEnd ) ;
			}
			else if ( li_retSts < 0 ) {
				blnErrFlg = LC_true ;
			}
		} else {

			// 3IDレコードの場合
			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"3IDレコード展開 UTKYMD[%s] IRINO[%s] SRIYMD[%s] KNTNO[%s] RACKID[%s] RACKPOS[%s]",
						strId3Tb.cUtkymd, strId3Tb.cIrino, strId3Tb.cSriymd, strId3Tb.cKntno, strId3Tb.cRackId, strId3Tb.cRackPos ) ;

			/****************************/
			/***                      ***/
			/***  各テーブルをUPDATE  ***/
			/***                      ***/
			/****************************/
            // 分注結果テーブルからサンプリングコード(SMPCD)、分注結果(BNCKKA)を取得
            li_retSts = sFncSelBUNCHU( &strId3Tb, &pSortInfo, &li_CntSmpcd ) ;
			if ( li_retSts == MYAPP_SQL_NOTFOUND )
			{
				//更新対象データがない場合
				blnNotFoundFlg = LC_true ;
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"SELECT BUNCHU NOTFOUND[%ld] UTKYMD[%s] IRINO[%s] SRIYMD[%s] KNTNO[%s] RACKID[%s] RACKPOS[%s]",
							li_retSts, strId3Tb.cUtkymd, strId3Tb.cIrino, strId3Tb.cSriymd, strId3Tb.cKntno, strId3Tb.cRackId, strId3Tb.cRackPos ) ;
			}
			else if ( li_retSts < 0 ) {
				blnErrFlg = LC_true ;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"SELECT BUNCHU ERROR[%ld] UTKYMD[%s] IRINO[%s] SRIYMD[%s] KNTNO[%s] RACKID[%s] RACKPOS[%s]",
							li_retSts, strId3Tb.cUtkymd, strId3Tb.cIrino, strId3Tb.cSriymd, strId3Tb.cKntno, strId3Tb.cRackId, strId3Tb.cRackPos ) ;
			}
			else {
				/* 1.01 取得したサンプリングコードごとにソートキーを設定してUPDATE */
				for ( li_idx = 0 ; li_idx < li_CntSmpcd ; li_idx++ ) {

					cBnckka =  pSortInfo[li_idx].cBnckka ;

					// ソートキー設定
					pSortInfo[li_idx].iSrtkey = AbunGetSort( pAppEnv, pId3Info->cRackId, cBnckka ) ;

					// 分注結果テーブルをUPDATE
					li_retSts = sFncUpdBUNCHU( &strId3Tb, &pSortInfo[li_idx] ) ;
					if ( li_retSts == MYAPP_SQL_NOTFOUND )
					{
						//更新対象データがない場合
						blnNotFoundFlg = LC_true ;
						sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"SELECT BUNCHU NOTFOUND[%ld] UTKYMD[%s] IRINO[%s] SRIYMD[%s] KNTNO[%s] RACKID[%s] RACKPOS[%s]",
									li_retSts, strId3Tb.cUtkymd, strId3Tb.cIrino, strId3Tb.cSriymd, strId3Tb.cKntno, strId3Tb.cRackId, strId3Tb.cRackPos ) ;
					}
					else if ( li_retSts < 0 ) {
						blnErrFlg = LC_true ;
						sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"SELECT BUNCHU ERROR[%ld] UTKYMD[%s] IRINO[%s] SRIYMD[%s] KNTNO[%s] RACKID[%s] RACKPOS[%s]",
									li_retSts, strId3Tb.cUtkymd, strId3Tb.cIrino, strId3Tb.cSriymd, strId3Tb.cKntno, strId3Tb.cRackId, strId3Tb.cRackPos ) ;
					}
				}

				// 検体属性情報テーブルをUPDATE
				li_retSts = sFncUpdKENZOK( &strId3Tb ) ;
				if ( li_retSts == MYAPP_SQL_NOTFOUND )
				{
					//更新対象データがない場合
					blnNotFoundFlg = LC_true ;
					sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"UPDATE KENZOK NOTFOUND[%ld] UTKYMD[%s] IRINO[%s] SRIYMD[%s] KNTNO[%s] RACKID[%s] RACKPOS[%s]",
								li_retSts, strId3Tb.cUtkymd, strId3Tb.cIrino, strId3Tb.cSriymd, strId3Tb.cKntno, strId3Tb.cRackId, strId3Tb.cRackPos ) ;
				}
				else if ( li_retSts < 0 ) {
					blnErrFlg = LC_true ;
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"UPDATE KENZOK ERROR[%ld] UTKYMD[%s] IRINO[%s] SRIYMD[%s] KNTNO[%s] RACKID[%s] RACKPOS[%s]",
								li_retSts, strId3Tb.cUtkymd, strId3Tb.cIrino, strId3Tb.cSriymd, strId3Tb.cKntno, strId3Tb.cRackId, strId3Tb.cRackPos ) ;
				}

				// 検体認識情報テーブルをUPDATE
				li_retSts = sFncUpdNINSIKI( &strId3Tb ) ;
				if ( li_retSts == MYAPP_SQL_NOTFOUND )
				{
					//更新対象データがない場合
					blnNotFoundFlg = LC_true ;
					sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"UPDATE NINSIKI NOTFOUND[%ld] UTKYMD[%s] IRINO[%s] SRIYMD[%s] KNTNO[%s] RACKID[%s] RACKPOS[%s]",
								li_retSts, strId3Tb.cUtkymd, strId3Tb.cIrino, strId3Tb.cSriymd, strId3Tb.cKntno, strId3Tb.cRackId, strId3Tb.cRackPos ) ;
				}
				else if ( li_retSts < 0 ) {
					blnErrFlg = LC_true ;
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"UPDATE NINSIKI ERROR[%ld] UTKYMD[%s] IRINO[%s] SRIYMD[%s] KNTNO[%s] RACKID[%s] RACKPOS[%s]",
								li_retSts, strId3Tb.cUtkymd, strId3Tb.cIrino, strId3Tb.cSriymd, strId3Tb.cKntno, strId3Tb.cRackId, strId3Tb.cRackPos ) ;
				}
			}
			/* 1.01 ソート用構造体領域の開放 */
			free ( pSortInfo ) ;
		}

		/*** BUNPOSファイルの1レコード単位でCOMMIT or ROLLBACK ***/
		// 更新対象レコードが見つからない or 更新エラーの場合
		if ( blnNotFoundFlg == LC_true || blnErrFlg == LC_true ) {
//			sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//						"Rollback !!! UTKYMD[%s] IRINO[%s] SRIYMD[%s] KNTNO[%s] RACKID[%s] RACKPOS[%s]",
//						strId3Tb.cUtkymd, strId3Tb.cIrino, strId3Tb.cSriymd, strId3Tb.cKntno, strId3Tb.cRackId, strId3Tb.cRackPos ) ;

			// ロールバック
			ZdbRollback () ;

			// 読み込み元ファイルが POS.data.XXXX の場合
			if ( !memcmp( pc_trFileName, MYAPP_RECV_KIND_POS, 3 ) ) {
				// 対象レコード(lc_recBuf)をSKIPファイルに出力
				if ( sFncOutput( pAppEnv, strId3Tb.cKntno, lc_recBuf ) < 0 ) {
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"SKIPファイル出力 ERROR UTKYMD[%s] IRINO[%s] SRIYMD[%s] KNTNO[%s] RACKID[%s] RACKPOS[%s]",
								strId3Tb.cUtkymd, strId3Tb.cIrino, strId3Tb.cSriymd, strId3Tb.cKntno, strId3Tb.cRackId, strId3Tb.cRackPos ) ;
					if ( lfp != NULL ) {
						fclose ( lfp ) ;
					}
					return ( -1 ) ;
				}

			// 読み込み元ファイルが SKIP.～ の場合
			} else if ( !memcmp( pc_trFileName, MYAPP_RECV_KIND_SKIP, 4 ) ) {
				// mainFunction関数でSKIPファイルをSKIPディレクトリにMOVEする為のフラグ設定
				*piOkSkipFlg = 1 ;
			}
		} else {
			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "COMMIT !!!" ) ;

			// コミット
			ZdbCommit () ; 
		}

		memset(lc_recBuf, 0, MYAPP_RECV_RECSIZE) ;
		memset(&strId3Tb, 0, sizeof(ID3TB)) ;

		/* 1.01 ソート用構造体領域の開放 */
//		free ( pSortInfo ) ;
	}

	fclose ( lfp ) ;

	return ( 0 ) ;
}

/******************************************************************************/
/*  関 数 名　：sFncOutput()				 								  */
/*  機能概要　：更新に失敗したデータをSKIPファイルに出力する				  */
/*  入　　力　：															  */
/*   第１引数 ：struct appEnv * 	プログラム環境構造体					  */
/*   第２引数 ：char lc_Kntno * 	検体No									  */
/*   第３引数 ：char lc_recBuf * 	BUNPOS情報レコード						  */
/*  出　　力　：															  */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
/******************************************************************************/
static int
sFncOutput ( pAppEnv, lc_Kntno, lc_recBuf )
struct appEnv		*pAppEnv ;
char				*lc_Kntno ;
char				*lc_recBuf ;
{
	FILE	*lfp ;
	char	 sRetryFile[1024];
	char	 sSysdate[128] ;
	char	 sSystime[128] ;

	/* 1.02 一時ファイルのファイル名 */
	char     sRetryTmpFile[1024];

    /* 現在の年月日、時分秒取得 */
	memset( sSysdate, 0, sizeof(sSysdate) ) ;
	memset( sSystime, 0, sizeof(sSystime) ) ;
	sFncGetNowdate( sSysdate, sSystime ) ;

	memset( sRetryTmpFile, 0, sizeof(sRetryTmpFile) ) ;
	sprintf( sRetryTmpFile, "%s/%s.%s%s.%s", pAppEnv->cDir3IdSkip, MYAPP_RECV_KIND_TMP, sSysdate, sSystime, lc_Kntno );

	/* 1.02対応 SKIP作成用TMPファイルオープン */
	if( (lfp = fopen(sRetryTmpFile,"a")) == NULL ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOutput   ", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"SKIP作成用TMPファイルのオープンに失敗しました[%s]", sRetryTmpFile ) ;
		return -1;
	}

	/* 更新失敗データをリトライ用ファイルに出力 */
	if( fputs(lc_recBuf, lfp) == EOF ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOutput	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "SKIPファイルの出力に失敗しました[%s]", lc_recBuf ) ;
		if ( lfp != NULL ) {
			fclose ( lfp ) ;
		}
		return -1;
	}

	fclose ( lfp ) ;

	/* SKIPファイル名作成 (/apdata/today/online/host/Recv/3id/SKIP/SKIP.YYYYMMDDHHMMSS.12345678901) */
	memset( sRetryFile, 0, sizeof(sRetryFile) ) ;
	sprintf( sRetryFile, "%s/%s.%s%s.%s", pAppEnv->cDir3IdSkip, MYAPP_RECV_KIND_SKIP, sSysdate, sSystime, lc_Kntno ) ;

	/* 同名のスキップファイルがすでに存在する場合は出力しない (同一検体の情報がすでに存在しているため) */
	if ( (lfp = fopen( sRetryFile,"r")) != NULL ){
		fclose( lfp );
		unlink( sRetryTmpFile );
		return ( 0 ) ;
	}

	/* 1.02対応 TMP → SKIP ファイル名変更 */
	if ( link( sRetryTmpFile, sRetryFile ) == 0 ) {
		sFncPutLog ( TRCKIND_OPT, __FILE__, "sFncOutput ", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  SKIPファイル出力[%s]", sRetryFile ) ;
		unlink( sRetryTmpFile );
	} else {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOutput ", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  TMPファイルからSKIPファイルへの変換に失敗しました[%s] → [%s]", sRetryTmpFile, sRetryFile ) ;
		return -1;
	}

	return ( 0 ) ;
}

/******************************************************************************/
/*  関 数 名　：sFncGetNowdate()			 								  */
/*  機能概要　：現在の年月日、時分秒を返す									  */
/*  入　　力　：															  */
/*   第１引数 ：char *sysdate	YYYYMMDD形式								  */
/*   第２引数 ：char *systime	HHMMSS形式									  */
/*  出　　力　：															  */
/*  復帰情報　：無し														  */
/******************************************************************************/
void
sFncGetNowdate( sysdate, systime )
char	*sysdate ;
char	*systime ;
{
	struct	tm	*newtime ;
	long		 ltime ;

	time( &ltime) ;
	newtime = localtime( &ltime ) ;
	sprintf( sysdate, "%04d%02d%02d", newtime->tm_year+1900,
			 newtime->tm_mon+1, newtime->tm_mday ) ;
	sprintf( systime, "%02d%02d%02d", newtime->tm_hour,
			 newtime->tm_min, newtime->tm_sec ) ;

	return ;
}

/******************************************************************************/
/*  関 数 名　：sFncGetNowdate1()			 								  */
/*  機能概要　：現在の年月日、時分秒を返す									  */
/*  入　　力　：															  */
/*   第１引数 ：char *sysdttm	YYYY-MM-DD HH:MI:SS形式						  */
/*  出　　力　：															  */
/*  復帰情報　：無し														  */
/******************************************************************************/
void
sFncGetNowdate1( sysdttm )
char	*sysdttm ;
{
	struct	tm	*newtime ;
	long		 ltime ;

	time( &ltime) ;
	newtime = localtime( &ltime ) ;
	sprintf( sysdttm, "%04d-%02d-%02d %02d:%02d:%02d", newtime->tm_year+1900,
			 newtime->tm_mon+1, newtime->tm_mday, newtime->tm_hour,
			 newtime->tm_min, newtime->tm_sec ) ;

	return ;
}

/******************************************************************************/
/*  関 数 名　：sFncPutLog()                                                  */
/*  機能概要　：アプリケーションログ出力                                      */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *      編集文字列                                        */
/*  出　　力　：                                                              */
/*  復帰情報　：無し                                                          */
/******************************************************************************/
void
sFncPutLog ( LOG_TRCKIND peTrcKind, char * pcSrcName, char * pcFncName, int plLineNo, char * pcExeFlg, char * pcErrCode, char * pcfmt, ... ) 
{
	va_list	 ap ;
	char	 cMsg[1024] ;

	/***
	 ***	ログ初期値設定
	 ***/
	gstLogMem.eTrcKind = peTrcKind ;
	//strcpy ( gstLogMem.pcSrcName, pcSrcName ) ;
	strcpy ( gstLogMem.pcFncName, pcFncName ) ;
	//gstLogMem.lLineNo = plLineNo ;
	strcpy ( gstLogMem.pcExeFlg,  pcExeFlg ) ;
	strcpy ( gstLogMem.pcErrCode, pcErrCode ) ;
	va_start ( ap, pcfmt ) ;
	vsprintf ( gstLogMem.pcMsg, pcfmt, ap ) ;
	va_end ( ap ) ;

	/***
	 ***	ログ出力
	 ***/
	_ZbmlPutLog ( &gstLogMem, pcSrcName, plLineNo) ;
	return ;
	
}

/******************************************************************************/
/*  関 数 名　：sFncTrim()  			 									  */
/*  機能概要　：文字列前後のスペースを削除する				  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *   	編集文字列								 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：無し														  */
/******************************************************************************/
static	void
sFncTrim ( s )
char	*s ;
{
	int		i ;

    i = strlen ( s ) ;

    while ( --i >= 0 && isspace ( (unsigned char)s[i] ) ) ;
    s[i+1] = '\0';
    for (i = 0; isspace((unsigned char)s[i]); i++) ;
    if ( i != 0 ) {
		strcpy ( s, s + i ) ;
	}
}

/******************************************************************************/
/*  関 数 名　：sFncFileRename()  			 								  */
/*  機能概要　：ファイルを移動する							  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *   	移動元ディレクトリ						 	      */
/*　 第２引数 ：char *   	移動元ファイル名						 	      */
/*　 第３引数 ：char *   	移動先ディレクトリ						 	      */
/*　 第４引数 ：char *   	移動先ファイル							 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
/******************************************************************************/
static int
sFncFileRename ( pc_fromDir, pc_fromFileName, pc_toDir, pc_toFileName )
char	*pc_fromDir ;
char	*pc_fromFileName ;
char	*pc_toDir ;
char	*pc_toFileName ;
{
	char	lc_fromPath[MYAPP_PATH_SIZE] ;
	char	lc_toPath[MYAPP_PATH_SIZE] ;

	sprintf ( lc_fromPath, "%s/%s", pc_fromDir, pc_fromFileName ) ;
	sprintf ( lc_toPath,   "%s/%s", pc_toDir,   pc_toFileName ) ;

	if ( rename ( lc_fromPath, lc_toPath ) < 0 ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncFileRename", __LINE__,
 	 	 			 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
 	 	 			 "ファイルの移動に失敗しました[%s->%s]", lc_fromPath, lc_toPath ) ;
		return ( -1 ) ;
	}
	
	return ( 0 ) ;
}

/******************************************************************************/
/*  関 数 名　：sFncShmCrt()				 								  */
/*  機能概要　：共有メモリ生成								  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体			 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
/******************************************************************************/
static int
sFncShmCrt ( pAppEnv )
struct appEnv	*pAppEnv ;
{
	int		*shmData ;

	//	取得
	pAppEnv->shm_Id = shmget ( (key_t)pAppEnv->shm_Key, 
							MYAPP_SHM_SIZE, 
							0666 | IPC_CREAT ) ;
	if ( pAppEnv->shm_Id < 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncShmCrt", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}

	//	アタッチ	
	shmData = ( int * ) shmat ( pAppEnv->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncShmCrt", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}

	//	値設定	
	*shmData = 0 ;

	//	デタッチ	
	if ( shmdt ( shmData ) == -1 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncShmCrt", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*  関 数 名　：sFncShmGet()				 								  */
/*  機能概要　：共有メモリ取得								  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体		 		      */
/*　 第２引数 ：int *   			値							 		      */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
/******************************************************************************/
static int
sFncShmGet ( pAppEnv, pshmData )
struct appEnv	*pAppEnv ;
int				*pshmData ;
{
	int		*shmData ;

	//	アタッチ	
	shmData = ( int * ) shmat ( pAppEnv->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncShmGet", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}

	//	値設定	
	*pshmData = *shmData ;

	//	デタッチ	
	if ( shmdt ( shmData ) == -1 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncShmGet", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*  関 数 名　：sFncShmDel()				 								  */
/*  機能概要　：共有メモリ削除								  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体。		 		      */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
/******************************************************************************/
static int
sFncShmDel ( pAppEnv )
struct appEnv	*pAppEnv ;
{
	int		*shmData ;

	//	削除	
	if ( shmctl ( pAppEnv->shm_Id, IPC_RMID, NULL) < 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncShmDel", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*  関 数 名　：sFncFileFillter()			 								  */
/*  機能概要　：ファイルフィルター【コールバック関数】		  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct dirent *   	ディレクトリ構造体				 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	対象外ファイル										  */
/*					 1	対象ファイル										  */
/******************************************************************************/
static	int
sFncFileFillter ( pdirEnt ) 
struct dirent *pdirEnt ;
{
		int		li_len ;

		//文字列長チェック
		li_len = strlen ( pdirEnt->d_name )  ;
		if ( li_len  < 5 ) {
			return ( 0 ) ;
		}
		//識別チェック("POS")
		if ( memcmp ( pdirEnt->d_name, 
					  MYAPP_RECV_KIND_POS, 
					  strlen ( MYAPP_RECV_KIND_POS ) ) == 0 ) {
			return ( 1 ) ;
		}
		//識別チェック("SKIP")
		if ( memcmp ( pdirEnt->d_name, 
					  MYAPP_RECV_KIND_SKIP, 
					  strlen ( MYAPP_RECV_KIND_SKIP ) ) == 0 ) {
			return ( 1 ) ;
		}
//		//拡張子チェック
//		if ( memcmp ( &(pdirEnt->d_name[li_len-strlen(MYAPP_RECV_SFX)]), 
//					  MYAPP_RECV_SFX, 
//					  strlen ( MYAPP_RECV_SFX ) ) == 0 ) {
//			return ( 1 ) ;
//		}
		return ( 0 ) ;
}

/****************************************************************************/
/*  関 数 名　：AbunGetSort()												*/
/*  機能概要　：分注TBLに格納するソートキーを算出する						*/
/*              1.01 引数を変更                                             */
/*  入　　力　：                                                            */
/*　 第１引数 ：															*/
/*  出　　力　：                                                            */
/*  復帰情報　：  0     : 成功												*/
/* 　　　　　　　-1     : 失敗												*/
/****************************************************************************/
static    int
AbunGetSort( pst_Env, sId, cBnckka )
struct appEnv *pst_Env ;
char          *sId ;
char          cBnckka ;
{
	int		i, cnt, iKey, iHit ;
	char	sBuf[10] ;
	BUNSORT	*p ;
	char	flg_tbl[] = {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"} ;

	memset(sBuf, 0, sizeof(sBuf)) ;
	memcpy(sBuf, sId, 4) ;
	cnt = pst_Env->pSortNo ;

	iKey = 999 ;
	for( i=0; i < cnt ;++i ) {
		p = pst_Env->pSort + i ;
		if( !memcmp(sBuf, p->sData, 2) ) {
			iKey = atoi(p->sKey) ;
			break ;
		}
	}

	if( !memcmp(sBuf, "XX", 2) || !memcmp(sBuf, "YY", 2) ) {
		return( iKey ) ;
	}

	iHit = 0 ;
	for( i=0; flg_tbl[i] != '\0' ;++i ) {
		if ( flg_tbl[i] == cBnckka ) {
			iHit = 1 ;
			break ;
		}
	}
	if( iHit == 1 ) {
		if( i == 36) i = 40 ;
		iKey = iKey + i ;
	}

	return( iKey ) ;
}

/****************************************************************************/
/*  関 数 名　：AgetSortInfo()												*/
/*  機能概要　：ソート初期ファイルからソート情報を取得する					*/
/*  入　　力　：                                                            */
/*　 第１引数 ：BUNSORT **strBun	ソート構造体							*/
/*  出　　力　：                                                            */
/*  復帰情報　：  0     : 成功												*/
/* 　　　　　　　-1     : 失敗												*/
/****************************************************************************/
static int AgetSortInfo(BUNSORT **strBun )
{
	FILE *fp;
	char	buf[1024], buf1[10];
	BUNSORT *pBun = NULL;
	int		i, j, k, cnt, iHit, iSu;

	if( (fp = fopen(MYAPP_AD105SORTINIFILE, "r")) == NULL ) {
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "AgetSortInfo", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"fopen ERROR(%d)", errno);
		return( -1 );
	}

	memset(buf, 0, sizeof(buf));
	iSu = 0;
	for( i=0; fgets(buf, sizeof(buf), fp ) != NULL ;++i ) {
		// 先頭が#はスキップする。
		if( (buf[0] == '#') || (buf[0] == '\n') ) {
			memset(buf, 0, sizeof(buf));
			continue;
		}
		pBun = (BUNSORT *)realloc((BUNSORT *)pBun, sizeof(BUNSORT) * (iSu + 1));
		memset(pBun+iSu, 0, sizeof(BUNSORT));
		memcpy((pBun+iSu)->sData, buf, 4);
		memcpy((pBun+iSu)->sKey, &buf[5], 3);
		++iSu;
	}

	fclose(fp);

	*strBun = pBun;

	return( iSu );
}

/******************************************************************************/
/*  関 数 名　：main()														  */
/*  機能概要　：メイン関数													  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *pcLogName    	【任意】ログファイル名を指定する。		  */
/*									※NULLを指定した場合はINIファイルより	  */
/*									  ログ情報を取得する。					  */
/*  出　　力　：                                                              */
/*  復帰情報　：  0     : 成功												  */
/* 　　　　　　　-1     : 失敗												  */
/******************************************************************************/
int 
main( argc, argv )
int		 argc ;
char	*argv[] ;
{

	struct appEnv	 sAppEnv ;

	/***
	 ***    バックグラウンド実行
	 ***/
	if ( daemon ( 0, 0 ) < 0 ) {
		exit ( 9 ) ;
	}


	/***
	 ***	初期処理	
	 ***/
	if ( initFunction ( argc, argv, &sAppEnv )  != 0 ) {
		endFunction ( &sAppEnv ) ;
		exit ( 9 ) ;
	}
	
	/***
	 ***	主処理	
	 ***/
	if ( mainFunction ( &sAppEnv )  != 0 ) {
		endFunction ( &sAppEnv ) ;
		exit ( 9 ) ;
	}

	/***
	 ***	終了処理	
	 ***/
	endFunction ( &sAppEnv ) ;
	exit(9);
}

/** End of File ***************************************************************/
