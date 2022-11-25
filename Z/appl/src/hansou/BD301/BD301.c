/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：BD301.c                                                      */
/* 　概　　　要：ストッカー【供給】                                           */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/15     芳賀弘幸       新規作成                           */
/*  1.01     2006/12/16   YOON JONG JIN    エラー追加                         */
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
#include <unistd.h>

#include "bmllog.h"
#include "bmlprm.h"
#include "bml_misc.h"
#include "bml_date.h"

#include "sql.h"

#include "BD301.h"

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
// 2008-02-04 新フロンティア対応 INS START
MYAPP_SYSTEM_VERSION	 gtNewFrontierFlg;
// 2008-02-04 新フロンティア対応 INS END
static	char			*gpToken ;			//	sFncTrFileToken用静的ポインタ
struct stcLogMember		 gstLogMem ;		//	ログ出力情報

/******************************************************************************/
/* 関数宣言                                                                   */
/******************************************************************************/
//	トレー・ラック紐付け情報関連関数
static	int		sFncTrFileRead ( struct appEnv *, char *, struct trInfo * ) ;
static	char*	sFncTrFileToken ( char * ) ;

//	ファイル・データベース出力関数
static	int 	sFncOutput ( struct appEnv *, struct trInfo * ) ;
static	int 	sFncFileOut ( struct appEnv *, struct my_stKENORDER *, struct my_stREALCHK *, int ) ;
static	int 	sFncOutRecKENORDER ( FILE *, char *, struct my_stKENORDER * ) ;
static	int 	sFncOutRecREALCHK ( FILE *, char *, struct my_stREALCHK * ) ;
static	void	sFncCreFileName ( char *, char *, char *, short, char *, struct tm * ) ;

//	共有メモリ操作関数
static	int		sFncShmCrt ( struct appEnv * ) ;
static	int		sFncShmGet ( struct appEnv * , int *) ;
static	int		sFncShmDel ( struct appEnv * ) ;

//	コールバック関数
static	int		sFncFileCompar ( struct dirent **, struct dirent ** )  ;
static	int		sFncFileFillter ( struct dirent * ) ;

//	その他
static	int		sFncFileRename ( char *, char *, char *, char * ) ;
static	void	sFncTrim ( char * ) ;
static  void	endFunction(struct appEnv *);

//	トレース用
static	void	_sFncEnvDip ( struct appEnv * ) ;
static	void	_sFncTrInfoDisp ( struct trInfo * ) ;

/******************************************************************************/
/*  関 数 名　：initFunction()												  */
/*  機能概要　：初期処理関数												  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct	env *   	プログラム環境構造体。		 			  */
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
	 ***	引数チェック	
	 ***/
	if ( argc != 2 ) {
		fprintf ( stderr, "%s : There is an error in a command parameter\n", MYAPP_APP_NAME ) ;
		return ( -1 ) ;
	}

	/***
	 ***	ログオープン
	 ***/
	if ( ZbmlOpenLog ( argv[1] ) != 0 ) {
		fprintf ( stderr, "ZbmlOpenLog NOT OPEN(%s)\n",argv[1]); 
		return ( -1 ) ;
	}


	//	ログ情報初期設定
	memset ( &gstLogMem, '\0', sizeof ( gstLogMem ) ) ;
	if ( ( lc_login = getenv( "LOGNAME" ) ) != NULL ) {
		strcpy ( gstLogMem.pcLoginId, lc_login ) ;
	}
	strcpy ( gstLogMem.pcAppName, MYAPP_APP_NAME ) ;

	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__,
				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "プログラム起動" ) ;
	//	開始ログ出力

	/***
	 ***	初期化	
	 ***/
	//	エラーステータス変更
	gintErrorCode = 0 ;

	//	プログラム環境変数初期化
	memset ( pAppEnv , '\0', sizeof ( struct appEnv ) ) ;


	/***
	 ***	引数チェック	
	if ( argc != 2 ) {
		gintErrorCode = MYAPP_STSCODE_ERR_USEGE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "initFunction", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "コマンドパラメータに誤りがあります" ) ;
		return ( -1 ) ;
	}
	 ***/

	/***
	 ***	パラメータファイル情報退避
	 ***/
	//	パラメータファイル名退避
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

	//	受信供給
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_NR_SUP,
						pAppEnv->cDirNR_Sup ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_NR_SUP ) ;
		return ( -1 ) ;
	}
	//	受信供給既読
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_NR_SUP_OK, 
						pAppEnv->cDirNR_SupOk ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_NR_SUP_OK ) ;
		return ( -1 ) ;
	}
	//	受信供給エラー
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_NR_SUP_ERR, 
						pAppEnv->cDirNR_SupErr ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_NR_SUP_ERR ) ;
		return ( -1 ) ;
	}
	//	受信供給ログ
//DEL	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_NR_LOG, 
//DEL						pAppEnv->cDirNR_Log ) != 0 ) {
//DEL		//	異常終了	LOG
//DEL		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
//DEL		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
//DEL				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//DEL				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_NR_LOG ) ;
//DEL		return ( -1 ) ;
//DEL	}
	//	オーダーデータ
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_IA_DAT, 
						pAppEnv->cDirIA_Dat ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_IA_DAT ) ;
		return ( -1 ) ;
	}
	//	オーダーデータ既読
//DEL	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_IA_DAT_OK, 
//DEL						pAppEnv->cDirIA_DatOk ) != 0 ) {
//DEL		//	異常終了	LOG
//DEL		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
//DEL		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
//DEL				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//DEL				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_IA_DAT_OK ) ;
//DEL		return ( -1 ) ;
//DEL	}
	//	オーダーデータエラー
//DEL	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_IA_DAT_ERR, 
//DEL						pAppEnv->cDirIA_DatErr ) != 0 ) {
//DEL		//	異常終了	LOG
//DEL		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
//DEL		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
//DEL				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//DEL				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_IA_DAT_ERR ) ;
//DEL		return ( -1 ) ;
//DEL	}
	//	作成完了データ
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_IA_IDX, 
						pAppEnv->cDirIA_Idx ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_IA_IDX ) ;
		return ( -1 ) ;
	}
	//	作成完了データ既読
//DEL	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_IA_IDX_OK, 
//DEL						pAppEnv->cDirIA_IdxOk ) != 0 ) {
//DEL		//	異常終了	LOG
//DEL		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
//DEL		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
//DEL				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//DEL				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_IA_IDX_OK ) ;
//DEL		return ( -1 ) ;
//DEL	}
	//	作成完了データエラー
//DEL	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_IA_IDX_ERR, 
//DEL						pAppEnv->cDirIA_IdxErr ) != 0 ) {
//DEL		//	異常終了	LOG
//DEL		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
//DEL		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
//DEL				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//DEL				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_IA_IDX_ERR ) ;
//DEL		return ( -1 ) ;
//DEL	}
	//	オーダーデータログ
//DEL	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_IA_LOG, 
//DEL						pAppEnv->cDirIA_Log ) != 0 ) {
//DEL		//	異常終了	LOG
//DEL		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
//DEL		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
//DEL				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//DEL				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_IA_LOG ) ;
//DEL		return ( -1 ) ;
//DEL	}
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
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DB_NAME, 
						pAppEnv->cDb_Name ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DB_NAME ) ;
		return ( -1 ) ;
	}
	//	データベースユーザ
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DB_USER, 
						pAppEnv->cDb_User ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DB_USER ) ;
		return ( -1 ) ;
	}
	//	データベースパスワード
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DB_PASSWD, 
						pAppEnv->cDb_Passwd ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DB_PASSWD ) ;
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
	//	バージョン情報（次世代対応）	
	gtSystemVersion = MYAPP_SYSTEM_NEW ;
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_VERSION, 
						pAppEnv->cVersion ) != 0 ) {
		gtSystemVersion = MYAPP_SYSTEM_OLD ;
	}

	//	パラメータファイルクローズ	
	ZbmlPrmClose ( pAppEnv->bp ) ;

	/***
	 ***	共有メモリ生成	
	 ***/
	if ( sFncShmCrt ( pAppEnv ) < 0 ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
        	EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "共有メモリえらー") ;
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
	int					  li_retSts ;
	long				  ll_retSts ;

	int					  li_idx ;	
	int					  li_stopFlg ;

	//	ディレクトリ情報 
	DIR					 *lt_dp ;
	struct dirent		**lpst_dirBuf ;

	//	トレーラック情報関連
	int					  li_fileCnt ;				
	struct trInfo		  lst_trInfo ;

	/***
	 ***	受信トレー・ラック供給ディレクトリ監視	
	 ***		永久ループ
	 ***		停止コマンドで終了
	 ***/
	while ( 1 ) {

		/***
		 *** ファイル名取得
		 ***/
		if ( ( li_fileCnt = scandir ( pAppEnv->cDirNR_Sup, 
									  &lpst_dirBuf,
									  (void*)sFncFileFillter,
					   				  (void*)sFncFileCompar ) ) < 0 ) {
			//	異常終了	LOG
			gintErrorCode = MYAPP_STSCODE_ERR_DIR;
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "scandir", __LINE__,
				 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 	 "トレー・ラック紐付け情報ファイルの取得に失敗しました" ) ;
			return ( -1 ) ;
		}

		/***
		 ***	データ処理
		 ***/
		li_idx = 0 ;
		for ( li_idx = 0 ; li_idx < li_fileCnt ; li_idx ++ ) {
//my_loging ( "STR : %s\n", lpst_dirBuf[li_idx]->d_name ) ;
			//	トレー・ラック紐付け情報取得
			li_retSts = sFncTrFileRead ( pAppEnv, lpst_dirBuf[li_idx]->d_name, 
				&lst_trInfo ) ;
			if ( li_retSts < 0 ) {
				//	エラーディレクトリに移動
				sFncFileRename ( pAppEnv->cDirNR_Sup, 
								 lpst_dirBuf[li_idx]->d_name,
								 pAppEnv->cDirNR_SupErr,
								 lpst_dirBuf[li_idx]->d_name ) ;
				//	次のトレー・ラック紐付け情報ファイルの処理を行う
				free ( lpst_dirBuf[li_idx] ) ;
				continue ;
			} else if ( li_retSts == 2 ) {
				//	トレー・ラック紐付け情報ファイル以外
				//	次のトレー・ラック紐付け情報ファイルの処理を行う
				free ( lpst_dirBuf[li_idx] ) ;
				continue ;
			}
_sFncTrInfoDisp ( &lst_trInfo ) ;

			//	検査オーダー・即時チェック情報出力
			li_retSts = sFncOutput ( pAppEnv, &lst_trInfo ) ;
			if ( li_retSts == 0 ) {
				//	既読ディレクトリに移動
				sFncFileRename ( pAppEnv->cDirNR_Sup, 
								 lpst_dirBuf[li_idx]->d_name,
								 pAppEnv->cDirNR_SupOk,
								 lpst_dirBuf[li_idx]->d_name ) ;
			} else {
				    
				//2006-12-15 YOON
				if ( li_retSts != 2 ) {
					//	エラーディレクトリに移動
					sFncFileRename ( pAppEnv->cDirNR_Sup, 
								 	lpst_dirBuf[li_idx]->d_name,
								 	pAppEnv->cDirNR_SupErr,
								 	lpst_dirBuf[li_idx]->d_name ) ;
					sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__,
    					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
	                 	"[[DB ERROR]]で終了" ) ;

					endFunction ( pAppEnv ) ;
        			exit ( 9 ) ;
				}
			}
//my_loging ( "END : %s\n", lpst_dirBuf[li_idx]->d_name ) ;
				
			//	解放
			free ( lpst_dirBuf[li_idx] ) ;

			/***
		 	 *** 停止コマンド確認
		 	 ***/
			if ( sFncShmGet ( pAppEnv, &li_stopFlg ) == 0 ) {
				if ( li_stopFlg == 1 ) {
					return ( 0 ) ;
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
	 ***	ログクローズ
	 ***/
	//	終了ログ出力
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__,
				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "プログラム終了" ) ;
	ZbmlCloseLog() ;
	
	return ;
}

/******************************************************************************/
/*  関 数 名　：sFncOutput()				 								  */
/*  機能概要　：検査オーダー情報、即時チェックファイル出力	 	 			  */
/*				ラック毎に各ファイル、データベースの更新を行う				  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体			 	      */
/*　 第３引数 ：struct trInfo *  	トレー・ラック紐付け情報格納構造体		  */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					 2	デッドロック										  */
/*					-1	異常												  */
/******************************************************************************/
static int
sFncOutput ( pAppEnv, pst_trInfo )
struct appEnv		*pAppEnv ;
struct trInfo		*pst_trInfo ;
{
	int		 				 li_idx ;
	int		 				 li_recIdx ;
	int		 				 li_retSts ;
	long	 				 ll_retSts ;
	int		 				 li_Return ;

	char					 cSel_knskisymd[MYAPP_DATE_SIZE] ;
	/*
	struct my_stKENORDER	 recKENORDER[100] ;		 		 
	struct my_stREALCHK		 recREALCHK[100] ;
	*/
	struct my_stKENORDER	*recKENORDER ;		 		 
	struct my_stREALCHK		*recREALCHK ;
	int						 recCnt ;
	int						 svRecCnt ;
	LC_BOOLEAN				 blnErrFlg ;
	LC_BOOLEAN				 blnLockFlg ;
// 2008-02-04 新フロンティア対応 INS START
	int						 li_BunTrCnt ;
	int						 li_len ;
	int						 li_Trknhsu ;	//トレー内検体本数
	int						 li_MaxOrderTrpos ;
	char					 buf[11], buf1[11], buf2[11], cTrhdid[11], cKnsgrp[17] ;
	int						 recTrCnt ;
// 2008-02-04 新フロンティア対応 INS END

	
	/***
	 ***	変数初期化
	 ***/
	blnErrFlg   = LC_false ;
	blnLockFlg  = LC_false ;
	li_Return   = 0 ;

	recCnt      = 0 ;
	svRecCnt    = 0 ;
	recKENORDER = NULL ;
	recREALCHK  = NULL ;
	
	//	基本検索キー設定 検査開始日)
	sprintf ( cSel_knskisymd, "%4.4s-%2.2s-%2.2s", 
					  		  pst_trInfo->knskisymd, 
					  		  &(pst_trInfo->knskisymd[4]), 
					  		  &(pst_trInfo->knskisymd[6]) ) ;

// 2008-02-04 新フロンティア対応 INS START
	// pst_trInfo->trid(日設ファイル内のトレーID)でBUNCHUを検索
	li_BunTrCnt = 0 ;
	li_retSts = sFncSelCntKENORDER ( cSel_knskisymd,
									 pst_trInfo->trid,
									 &li_BunTrCnt ) ;
	
	// 検索結果が0の場合は新フロ対応データ (TRID = '____0000')
	if ( li_BunTrCnt == 0 ) {
		gtNewFrontierFlg = MYAPP_SYSTEM_NEW;
	} else {
		gtNewFrontierFlg = MYAPP_SYSTEM_OLD;
	}
// 2008-02-04 新フロンティア対応 INS END
	
	/***
	 ***	メイン処理
	 ***/
	/*
	memset ( recKENORDER, '\0', sizeof ( recKENORDER ) ) ;
	memset ( recREALCHK,  '\0', sizeof ( recREALCHK ) ) ;
	*/
	for ( li_idx = 0 ; li_idx < MYAPP_RACK_MAXCNT ; li_idx++ ) {

		//	ブランクは処理を行わない
		if ( pst_trInfo->asyrckid[li_idx][0] == '\0' ) {
			continue ;
		}

		/***
		 ***	更新・検索
		 ***/
// 2008-02-04 新フロンティア対応 UPD START
//		if ( gtSystemVersion == MYAPP_SYSTEM_OLD ) {
		if ( gtNewFrontierFlg == MYAPP_SYSTEM_OLD ) {
// 2008-02-04 新フロンティア対応 UPD END
			//	【過渡期】	
			//	検査オーダー情報更新
			li_retSts = sFncUpdKENORDER ( cSel_knskisymd,
										  pst_trInfo->trid,
										  ( 5 * li_idx ) + 1,
										  ( 5 * li_idx ) + 5,
										  pst_trInfo->asyrckid[li_idx],
										  li_idx ) ;
           	//2006-12-16 YOON 
            if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
            {
                //デッドロックor重複
                blnLockFlg = LC_true ;
                break ;
            }
            else if ( li_retSts < 0 ) {
                blnErrFlg = LC_true ;
                break ;
            }
			//DEL	即時チェック情報更新
			//DEL	li_retSts = sFncUpdREALCHK ( cSel_knskisymd,
			//DEL								 pst_trInfo->trid,
			//DEL								 ( 5 * li_idx ) + 1,
			//DEL								 ( 5 * li_idx ) + 5,
			//DEL								 pst_trInfo->asyrckid[li_idx], 
			//DEL								 li_idx ) ;
			//DEL	if ( li_retSts == 2 ) {
			//DEL		//デッドロック
			//DEL		blnLockFlg = LC_true ;
			//DEL		break ;
			//DEL	}
			//DEL	if ( li_retSts < 0 ) {
			//DEL		blnErrFlg = LC_true ;
			//DEL		break ;
			//DEL	}

			//	検体ポジション情報追加
			li_retSts = sFncInsKENPOS ( cSel_knskisymd,
										pst_trInfo->trid,
										( 5 * li_idx ) + 1,
										( 5 * li_idx ) + 5,
										pst_trInfo->stkno ) ;
           	//2006-12-16 YOON 
            if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
            {
                //デッドロックor重複
                blnLockFlg = LC_true ;
                break ;
            }
            else if ( li_retSts < 0 ) {
                blnErrFlg = LC_true ;
                break ;
            }
			
			//	検査オーダー情報・即時チェック情報検索
			li_retSts = sFncSelKENORDER_REALCHK ( cSel_knskisymd,
												  pst_trInfo->trid,
												  ( 5 * li_idx ) + 1,
												  ( 5 * li_idx ) + 5,
												  &recKENORDER,
												  &recREALCHK,
												  &recCnt ) ;
           	//2006-12-16 YOON 
			if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
            {
                //デッドロックor重複
                blnLockFlg = LC_true ;
                break ;
            }
            else if ( li_retSts < 0 ) {
                blnErrFlg = LC_true ;
                break ;
            }		


			if ( ( recCnt - svRecCnt ) == 0 ) {
				sFncPutLog ( TRCKIND_WARNING, __FILE__, "sFncOutput", __LINE__,
			 	 			 EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
			 		 		 "検査オーダ情報、または即時チェック情報が存在しません KNSKISYMD='%s' TRID='%s' TRPOS %d-%d RCKID='%s'", cSel_knskisymd, pst_trInfo->trid, ( 5 * li_idx ) + 1, ( 5 * li_idx ) + 5, pst_trInfo->asyrckid[li_idx] ) ;
			} else {
				svRecCnt = recCnt ;
			}
			
		} else {
			//	【次世代】	
// 2008-02-04 新フロンティア対応 INS START
// ↓↓↓ トレー管理マスタから取ってもli_Trknhsuは100なので、
// ヘッダファイルの MYAPP_TRKNHSU_MAXCNT (100)を使う。
			// トレー内検体本数 (100)
			li_Trknhsu = MYAPP_TRKNHSU_MAXCNT ;
// トレー管理マスタから取る場合は↑をコメントにし、↓を復活する。
//			// トレー管理マスタからトレー内検体本数を取得
//			memset(cTrhdid, 0, sizeof(cTrhdid)) ;
//			memcpy(cTrhdid, pst_trInfo->trid, 4) ;
//			li_retSts = sFncSelTRMST ( cTrhdid,
//									   cSel_knskisymd,
//									   &li_Trknhsu,
//									   &recTrCnt ) ;
//
//			if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
//			{
//				//デッドロックor重複
//				blnLockFlg = LC_true ;
//				break ;
//			}
//			else if ( li_retSts < 0 ) {
//				blnErrFlg = LC_true ;
//				break ;
//			}
//			else if ( recTrCnt == 0 ) {
//				blnErrFlg = LC_true ;
//				sFncPutLog ( TRCKIND_WARNING, __FILE__, "sFncOutput", __LINE__,
//							 EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
//							 "トレー管理マスタに該当データが存在しません TRHDID='%s' KAIYMD='%s' HAIYMD='%s'", cTrhdid, cSel_knskisymd, cSel_knskisymd ) ;
//				break ;
//			}
// 2008-02-04 新フロンティア対応 INS END

			//	検査オーダー情報更新
// 2008-02-04 新フロンティア対応 UPD START
//			li_retSts = sFncUpdKENORDER_NXT ( cSel_knskisymd,
//											  pst_trInfo->asyrckid[li_idx],
//											  pst_trInfo->trid,
//											  li_idx ) ;

			memset(buf, 0, sizeof(buf)) ;
			memset(buf1, 0, sizeof(buf1)) ;
			memcpy(buf, pst_trInfo->trid, 11) ;
			li_len = strlen(buf) - 4 ;
			strcpy(buf1, &buf[li_len]);
			li_len = atoi(buf1);
			li_retSts = sFncUpdKENORDER_NXT ( cSel_knskisymd,
											  pst_trInfo->asyrckid[li_idx],
											  pst_trInfo->trid,
											  li_len * li_Trknhsu,
											  li_idx ) ;
// 2008-02-04 新フロンティア対応 UPD END

           	//2006-12-16 YOON 
            if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
            {
                //デッドロックor重複
                blnLockFlg = LC_true ;
                break ;
            }
            else if ( li_retSts < 0 ) {
                blnErrFlg = LC_true ;
                break ;
            }

// 2008-02-04 新フロンティア対応 DEL START
//			//	即時チェック情報更新
//			li_retSts = sFncUpdREALCHK_NXT ( cSel_knskisymd,
//											 pst_trInfo->asyrckid[li_idx],
//										     pst_trInfo->trid,
//										     li_idx ) ;
//           	//2006-12-16 YOON 
//            if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
//            {
//                //デッドロックor重複
//                blnLockFlg = LC_true ;
//                break ;
//            }
//            else if ( li_retSts < 0 ) {
//                blnErrFlg = LC_true ;
//                break ;
//            }
// 2008-02-04 新フロンティア対応 DEL END

			//	検体ポジション情報追加
			li_retSts = sFncInsKENPOS_NXT ( cSel_knskisymd,
											pst_trInfo->asyrckid[li_idx],
											pst_trInfo->stkno ) ;
           	//2006-12-16 YOON 
            if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
            {
                //デッドロックor重複
                blnLockFlg = LC_true ;
                break ;
            }
            else if ( li_retSts < 0 ) {
                blnErrFlg = LC_true ;
                break ;
            }
			//	検査オーダー情報・即時チェック情報検索
			li_retSts = sFncSelKENORDER_REALCHK_NXT ( cSel_knskisymd,
												      pst_trInfo->trid,
												      ( 5 * li_idx ) + 1,
												      ( 5 * li_idx ) + 5,
												      &recKENORDER,
												      &recREALCHK,
												      &recCnt ) ;
           	//2006-12-16 YOON 
            if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
            {
                //デッドロックor重複
                blnLockFlg = LC_true ;
                break ;
            }
            else if ( li_retSts < 0 ) {
                blnErrFlg = LC_true ;
                break ;
            }			
			if ( ( recCnt - svRecCnt ) == 0 ) {
				sFncPutLog ( TRCKIND_WARNING, __FILE__, "sFncOutput", __LINE__,
			 	 			 EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
			 		 		 "検査オーダ情報、または即時チェック情報が存在しません KNSKISYMD='%s' TRID='%s' TRPOS %d-%d RCKID='%s'", cSel_knskisymd, pst_trInfo->trid, ( 5 * li_idx ) + 1, ( 5 * li_idx ) + 5, pst_trInfo->asyrckid[li_idx] ) ;
			} else {
				svRecCnt = recCnt ;
			}
		}
	} 

// 2008-02-04 新フロンティア対応 INS (AD105から移行) START
	if ( gtNewFrontierFlg == MYAPP_SYSTEM_NEW ) {
		li_retSts = sFncSelKENORDER ( cSel_knskisymd,
									  pst_trInfo->trid,
									  &li_MaxOrderTrpos );
		if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
		{
		    //デッドロックor重複
		    blnLockFlg = LC_true ;
		}
		else if ( li_retSts < 0 ) {
		    blnErrFlg = LC_true ;
		}

		// オーダーがある場合のみWSSEQKNRIにINSERTする
		if ( li_MaxOrderTrpos != 0 ) {
			// 検査グループ(スペース16桁)設定
			memset(cKnsgrp, 0, sizeof(cKnsgrp));
			memset(cKnsgrp, ' ', 16);
			//トレーIDの下4桁を数値化
			memset(buf1, 0, sizeof(buf1));
			memset(buf2, 0, sizeof(buf2));
			ZbmlInfocpy(buf1, pst_trInfo->trid, 11) ;
			li_len = strlen(buf1) - 4 ;
			strcpy(buf2, &buf1[li_len]);
			li_len = atoi(buf2);

			//初回WSレコードの登録
			insWsseqknri(cSel_knskisymd,
						 cKnsgrp,
						 pst_trInfo->trid,
						 li_MaxOrderTrpos,
						 (li_len * li_Trknhsu + 1),
						 (li_len * li_Trknhsu + li_MaxOrderTrpos) ) ;

			if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
			{
			    //デッドロックor重複
			    blnLockFlg = LC_true ;
			}
			else if ( li_retSts < 0 ) {
			    blnErrFlg = LC_true ;
			}
		}
	}
// 2008-02-04 新フロンティア対応 INS (AD105から移行) END

	/***
	 ***	トランザクション終了
	 ***	検査オーダ情報、即時チェック情報のみトランザクション終了
	 ***	ADD NO.14 2006/05/26
	 ***/
	if ( blnErrFlg == LC_true || blnLockFlg == LC_true ) {
	 	//	ロールバック
		ZdbRollback () ;
	} else {
		//	コミット
		ZdbCommit () ; 
	}

// 2008-02-04 新フロンティア対応 DEL (使ってなさそう・・・) START
//	/***
//	 ***	トレー管理情報更新
//	 ***	エラーが発生しても現時点のファイルを作成する
//	 ***/
//	li_retSts = sFncUpdTRAYKNRI ( cSel_knskisymd,
//							  	  pst_trInfo->trid,
//							  	  pst_trInfo->stkno ) ;
//	if ( li_retSts < 0 ) {
//	 	//	ロールバック
//		ZdbRollback () ;
//	} else {
//		//	コミット
//		ZdbCommit () ; 
//	}
// 2008-02-04 新フロンティア対応 DEL (使ってなさそう・・・) END


	/***
	 ***	ファイル出力
	 ***/
	if ( blnErrFlg != LC_true && blnLockFlg != LC_true && recCnt > 0 ) {
		//	検査オーダー情報
		li_retSts = sFncFileOut ( pAppEnv, recKENORDER, recREALCHK, recCnt ) ;
		if ( li_retSts < 0 ) {
			blnErrFlg = LC_true ;
		}
	}

	free ( recKENORDER ) ;
	free ( recREALCHK ) ;

	if ( blnLockFlg == LC_true ) {
		return ( 2 ) ;
	}
	if ( blnErrFlg == LC_true ) {
		return ( -1 ) ;
	}
	return ( 0 ) ;
}
/******************************************************************************/
/*  関 数 名　：sFncFileOut()				 								  */
/*  機能概要　：検査オーダー・即時チェック情報ファイル出力				 	  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体			 	      */
/*　 第２引数 ：Kenorder  *   		検査オーダー情報環境構造体			      */
/*　 第３引数 ：Realchk  *   		即時チェック情報環境構造体		 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
/******************************************************************************/
static int
sFncFileOut ( pAppEnv, precKenorder, precRealchk, precCnt )
struct appEnv			*pAppEnv ;
struct my_stKENORDER	*precKenorder ;
struct my_stREALCHK		*precRealchk ;
int						 precCnt ;
{
	FILE			*lfp_R ;
	FILE			*lfp_K ;
	FILE			*lfp_IDX ;
	char			 lc_recBuf_K[512] ;
	char			 lc_recBuf_R[8192] ;
	char			 lc_dataFileName_K[MYAPP_PATH_SIZE] ;
	char			 lc_dataFileName_R[MYAPP_PATH_SIZE] ;
	char			 lc_fileName_K[MYAPP_PATH_SIZE] ;
	char			 lc_fileName_R[MYAPP_PATH_SIZE] ;
	char			 lc_idxFileName[MYAPP_PATH_SIZE] ;

	char			 SV_asyrckid[MYAPP_RKNO_SIZE] ;
	int			 	 SV_asyrckpos ;
	LC_BOOLEAN		 blnFirstFlg ;

	int				 idx ;

	struct tm		*timepos ;
	struct timeb	 timebuf ;

	/***
	 ***	初期処理
	 ***/
	blnFirstFlg   = LC_true ;
	//	システム日付日時取得
	ftime ( &timebuf ) ;
	timepos  = ( struct tm * ) localtime ( &( timebuf.time ) ) ;
	//	ブレイクキー
	memset ( SV_asyrckid, '\0', sizeof ( SV_asyrckid ) ) ;
	SV_asyrckpos = -1 ;
	//	変数初期化
	lfp_R   = NULL ;
	lfp_K   = NULL ;
	lfp_IDX = NULL ;

	
	/***
	 ***	ファイル出力
	 ***/
	for ( idx = 0 ; idx < precCnt ; idx ++ ) {
		/***
		 ***	ブレイク処理 
		 ***/
		if ( strcmp ( SV_asyrckid, precKenorder[idx].asyrckid ) != 0 ||
			 SV_asyrckpos != precKenorder[idx].asyrckpos ) {
			/***
			 ***	初回以外の処理
			 ***		検査オーダー情報ファイル出力
			 ***		ファイルクロース
			 ***/
			if ( blnFirstFlg != LC_true ) {
			 	//	ファイルクローズ
				fclose ( lfp_R ) ;
				fclose ( lfp_K ) ;
				//検査オーダー情報ファイル出力
				lfp_IDX  = fopen ( lc_idxFileName , "w" ) ;
				if ( lfp_IDX == NULL ) {
					//	異常終了	LOG
					unlink ( lc_dataFileName_R ) ;
					unlink ( lc_dataFileName_K ) ;
					gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "fopen", __LINE__,
			 	 	 			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 			"ファイルのオープンに失敗しました[%s]", 
								lc_idxFileName ) ;
					return ( -1 ) ;
				}
				fclose ( lfp_IDX ) ;
			} else {
				blnFirstFlg = LC_false ;
			}

			/***
			 ***	ブレイクキー初期化
			 ***/
			strcpy ( SV_asyrckid, precKenorder[idx].asyrckid ) ;
			SV_asyrckpos =  precKenorder[idx].asyrckpos ;

			/***
			 ***	ファイル名作成	
			 ***/
			//	即時チェック情報ファイル名作成
			sFncCreFileName ( lc_fileName_R, MYAPP_SEND_KIND_CH, 
							  precKenorder[idx].asyrckid, 
							  precKenorder[idx].asyrckpos, 
							  MYAPP_SEND_SFX, timepos ) ;
			sprintf ( lc_dataFileName_R, "%s/%s", pAppEnv->cDirIA_Dat,lc_fileName_R);
			//	検査オーダー情報ファイル名作成
			sFncCreFileName ( lc_fileName_K, MYAPP_SEND_KIND_OD, 
							  precKenorder[idx].asyrckid, 
							  precKenorder[idx].asyrckpos, 
							  MYAPP_SEND_SFX, timepos ) ;
			sprintf ( lc_dataFileName_K, "%s/%s", pAppEnv->cDirIA_Dat,lc_fileName_K);
			sprintf ( lc_idxFileName,  "%s/%s", pAppEnv->cDirIA_Idx,lc_fileName_K);

			/***
			 ***	ファイルオープン	
			 ***/
			//	即時チェック情報ファイル
			lfp_R  = fopen ( lc_dataFileName_R , "w" ) ;
			if ( lfp_R == NULL ) {
				//	異常終了	LOG
				gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "fopen", __LINE__,
			 	 	 		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 		"ファイルのオープンに失敗しました[%s]",lc_dataFileName_R);
				return ( -1 ) ;
			}
			//	検査オーダー情報ファイル
			lfp_K  = fopen ( lc_dataFileName_K , "w" ) ;
			if ( lfp_K == NULL ) {
				//	異常終了	LOG
				gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "fopen", __LINE__,
			 	 	 		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 		"ファイルのオープンに失敗しました[%s]",lc_dataFileName_K);
				return ( -1 ) ;
			}
		}
		
		/***
		 ***	データ出力
		 ***/
		//	即時チェック情報レコード作成
		if ( sFncOutRecREALCHK ( lfp_R, lc_recBuf_R, &precRealchk[idx] ) < 0 ) {
			//	異常終了	LOG
			gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOutRecREALCHK", __LINE__,
			 	 	 	EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 	"ファイルの出力に失敗しました[%s]", lc_dataFileName_R ) ;
			return ( -1 ) ;
		}
		//	検査オーダー情報レコード作成
		if ( sFncOutRecKENORDER ( lfp_K, lc_recBuf_K, &precKenorder[idx] ) < 0 ) {
			//	異常終了	LOG
			gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOutRecKENORDER", __LINE__,
			 	 	 	EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 	"ファイルの出力に失敗しました[%s]", lc_dataFileName_K ) ;
			return ( -1 ) ;
		}
	}

	/***
	 ***	ファイル出力後処理
	 ***/
	//	ファイルクローズ
	if ( lfp_R != NULL ) {
		fclose ( lfp_R ) ;
	}
	if ( lfp_K != NULL ) {
		fclose ( lfp_K ) ;
	}
	//検査オーダー情報ファイル出力
	lfp_IDX  = fopen ( lc_idxFileName , "w" ) ;
	if ( lfp_IDX == NULL ) {
		//	異常終了	LOG
		unlink ( lc_dataFileName_R ) ;
		unlink ( lc_dataFileName_K ) ;
		gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "fopen", __LINE__,
 	 	 			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
 	 	 			"ファイルのオープンに失敗しました[%s]", 
					lc_idxFileName ) ;
		return ( -1 ) ;
	}
	fclose ( lfp_IDX ) ;

	return ( 0 ) ;
}
/******************************************************************************/
/*  関 数 名　：sFncTrFileRead()			 								  */
/*  機能概要　：トレー・ラック紐付け情報読込				  	 			  */
/*	特記事項  ：第２引数はfree												  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体		 	          */
/*　 第２引数 ：char *  	 		トレー・ラック紐付け情報ファイル名	      */
/*　 第３引数 ：struct trInfo *   	トレー・ラック紐付け情報格納構造体    	  */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
/*					 1	データ異常											  */
/******************************************************************************/
static	int
sFncTrFileRead ( pAppEnv, pc_trFileName, pst_trInfo )
struct appEnv	*pAppEnv ;
char			*pc_trFileName ;
struct trInfo	*pst_trInfo ;
{
	FILE	*lfp ;
	char	 lc_recBuf[MYAPP_RECV_RECSIZE] ;
	int	 	 li_recBuflen;
	char	*lpc_recBuf ;
	char	*lpc_Token ;
	char	*lpc_trInfoMem[MYAPP_RECV_COLCNT] ;
	int		 li_tokenCnt ;
	int		 li_rackCnt ;
	int		 li_retryCnt ;

	char		  lc_fileName[1024] ;
	char		  lc_fileNameBuf[1024] ;
	char		 *pToken ;
	struct stat	  lst_statBuf ;

	/***
	 ***	ファイル属性チェック
	 ***/
	//	ファイル名作成
	sprintf ( lc_fileName, "%s/%s", pAppEnv->cDirNR_Sup, pc_trFileName ) ;
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
	//	ファイルオープン	
	li_retryCnt = 0 ;
	while ( li_retryCnt  < pAppEnv->fileRetry ) {
		lfp  = fopen ( lc_fileName, "r" ) ;
		if ( lfp == NULL ) {
			li_retryCnt ++ ;
			continue ;
		}
	
		//	読み込み（１行のみ）
		if ( fgets ( lc_recBuf, sizeof ( lc_recBuf ), lfp ) == NULL ) {
			fclose ( lfp ) ;
			li_retryCnt ++ ;
			continue ;
		}
		
		//	ファイルクローズ	
		fclose ( lfp ) ;
		break ;
	}
	if ( li_retryCnt == pAppEnv->fileRetry ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncTrFileRead", __LINE__,
		 	 	 	EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		 	 	 	"ファイルの読み込みに失敗しました[%s]", lc_fileName ) ;
		return ( -1 ) ;
	}

	//	改行コード置換
	li_recBuflen = strlen ( lc_recBuf ) ;
	if ( lc_recBuf[li_recBuflen-2] == '\r' ) {
		lc_recBuf[li_recBuflen-2] = '\0' ;
	}
	if ( lc_recBuf[li_recBuflen-1] == '\n' ) { 
		lc_recBuf[li_recBuflen-1] = '\0' ;
	}

	//	トークン分割
	memset ( lpc_trInfoMem, '\0', sizeof ( lpc_trInfoMem ) )  ;
	lpc_recBuf = lc_recBuf ;
	for ( li_tokenCnt = 0 ; li_tokenCnt < MYAPP_RECV_COLCNT ; li_tokenCnt ++ ) {
		lpc_Token = sFncTrFileToken ( lpc_recBuf ) ;
		//lpc_Token = strtok ( lpc_recBuf, "," ) ;
		if ( lpc_Token == NULL ) {
			break ;
		}
		if ( lpc_recBuf != NULL ) {
			lpc_recBuf = NULL ;
		}
		lpc_trInfoMem[li_tokenCnt] = lpc_Token ;
	}

	//	トークン数チェック（２３以外はファイル異常）
	if ( li_tokenCnt != MYAPP_RECV_COLCNT ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "fgets", __LINE__,
			 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 "フォーマットに誤りがあります[%s]", lc_fileName ) ;
		return ( -1 ) ;
	}

	//	構造体設定
	li_tokenCnt = 0 ;
	li_rackCnt = 0 ;
	memset ( pst_trInfo, '\0', sizeof ( struct trInfo ) ) ;
	while ( li_tokenCnt  < MYAPP_RECV_COLCNT ) {
		if ( li_tokenCnt == 0 ) {	//トレーＮＯ
			strcpy ( pst_trInfo->trid, lpc_trInfoMem[li_tokenCnt] ) ;
			sFncTrim ( pst_trInfo->trid ) ;
		}
		else 
		if ( li_tokenCnt == 1 ) {	//検査開始日
			strcpy ( pst_trInfo->knskisymd, lpc_trInfoMem[li_tokenCnt] ) ;
			sFncTrim ( pst_trInfo->knskisymd ) ;
		}
		else 
		if ( li_tokenCnt == 22 ) {	//生成日時
			strcpy ( pst_trInfo->createDate, lpc_trInfoMem[li_tokenCnt] ) ;
			sFncTrim ( pst_trInfo->createDate ) ;
		}
		else {
			strcpy ( pst_trInfo->asyrckid[li_rackCnt], lpc_trInfoMem[li_tokenCnt] ) ;
			sFncTrim ( pst_trInfo->asyrckid[li_rackCnt] ) ;
			li_rackCnt++ ;
		}
		li_tokenCnt++ ;
	}

	/***
	 ***	ストッカーＮＯ取得
	 ***		ファイル名より取得	
	 ***/
	strcpy ( lc_fileNameBuf, &pc_trFileName[ strlen ( MYAPP_RECV_KIND ) ] ) ;
	if ( ( pToken = strtok ( lc_fileNameBuf, "_" ) ) != NULL ) {
		memcpy ( pst_trInfo->stkno, pToken, sizeof ( pst_trInfo->stkno ) - 1 ) ;
	}


	return ( 0 ) ;
}
/******************************************************************************/
/*  関 数 名　：sFncPutLog()  			 									  */
/*  機能概要　：アプリケーションログ出力					  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *   	編集文字列								 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：無し														  */
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
/*  関 数 名　：sFncOutRecKENORDER()		 								  */
/*  機能概要　：検査オーダ情報情報レコード生成				  	 			  */
/*  入　　力　：                                                              */
/*　 第２引数 ：struct my_stKENORDER *   	検査オーダ情報構造体		      */
/*  出　　力　：                                                              */
/*　 第１引数 ：char 				*   	レコード格納バッファ			  */
/*  復帰情報　：無し														  */
/******************************************************************************/
static	int
sFncOutRecKENORDER ( pfp, p_recBuf, precKenorder )
FILE					*pfp ;
char					*p_recBuf ;
struct my_stKENORDER	*precKenorder ;
{
	int		retSts ;
	//	レコード作成
	retSts = fprintf ( pfp, "%s,%s,%s,%s,%s,%s,%hd,%hd,%s,%s,%s,%s,%s,%s,%hd,%s,%s,%hd,%s,%hd,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%hd,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%ld,%hd,%s,%s\n",
				precKenorder->knskisymd,
				precKenorder->sriymd,
				precKenorder->kntno,
				precKenorder->kntketflg,
				precKenorder->knsgrp,
				precKenorder->kmkcd,
				precKenorder->knssu,
				precKenorder->knssueda,
				precKenorder->irihsmkbn,
				precKenorder->irikbn,
				precKenorder->ksktkbn,
				precKenorder->utkymd,
				precKenorder->irino,
				precKenorder->iriketflg,
				precKenorder->zssdino,
				precKenorder->sstcd,
				precKenorder->trid,
				precKenorder->trpos,
				precKenorder->asyrckid,
				precKenorder->asyrckpos,
				precKenorder->oyakmkcd,
				precKenorder->seccd,
				precKenorder->bkfkkbn,
				precKenorder->smpcd,
				precKenorder->bskkbn,
				precKenorder->nbkmkcd,
				precKenorder->zrcd,
				precKenorder->ysnlbl,
				precKenorder->kjno,
				precKenorder->fkhkknohjkbn,
				precKenorder->tbkjno,
				precKenorder->tbkjflg,
				precKenorder->htkfkhms,
				precKenorder->skflg,
				precKenorder->tskflg,
				precKenorder->tktflg,
				precKenorder->ytiksbr,
				precKenorder->kkflg,
				precKenorder->kkiriflg,
				precKenorder->kkirilotno,
				precKenorder->sc,
				precKenorder->tj,
				precKenorder->tjtni,
				precKenorder->sbtkbn,
				precKenorder->birthday,
				precKenorder->birthdaykbn,
				precKenorder->age,
				precKenorder->agekbn,
				precKenorder->sstme,
				precKenorder->ssymd,
				precKenorder->tntme,
				precKenorder->tntni,
				precKenorder->tnryo,
				precKenorder->tnryotni,
				precKenorder->knsseq,
				precKenorder->bthno,
				precKenorder->knsjkflg,
				precKenorder->ksndh ) ;
	if ( retSts < 0 ) {
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*  関 数 名　：sFncCreRecREALCHK()			 								  */
/*  機能概要　：即時チェック情報レコード生成				  	 			  */
/*  入　　力　：                                                              */
/*　 第２引数 ：struct my_stREALCHK *   	即時チェック情報構造体		      */
/*  出　　力　：                                                              */
/*　 第１引数 ：char 				*   	レコード格納バッファ			  */
/*  復帰情報　：無し														  */
/******************************************************************************/
static	int
sFncOutRecREALCHK ( pfp, p_recBuf, precRealchk )
FILE					*pfp ;
char					*p_recBuf ;
struct my_stREALCHK		*precRealchk ;
{

	int		retSts ;
	//	レコード作成
	retSts = fprintf ( pfp, "%s,%s,%s,%s,%s,%s,%hd,%hd,%s,%s,%s,%hd,%s,%hd,%s,%hd,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%.256s,%.256s,%.256s,%.256s,%.256s,%.256s,%.256s,%.1024s,%.256s,%.256s,%.256s,%.256s,%.256s,%.256s,%.256s,%.256s,%.256s,%.256s,%.256s,%.256s,%s\n",
				precRealchk->knskisymd,
				precRealchk->sriymd,
				precRealchk->kntno,
				precRealchk->kntketflg,
				precRealchk->knsgrp,
				precRealchk->kmkcd,
				precRealchk->knssu,
				precRealchk->knssueda,
				precRealchk->utkymd,
				precRealchk->irino,
				precRealchk->iriketflg,
				precRealchk->zssdino,
				precRealchk->trid,
				precRealchk->trpos,
				precRealchk->asyrckid,
				precRealchk->asyrckpos,
				precRealchk->bskkbn,
				precRealchk->nbkmkcd,
				precRealchk->renjicflg,
				precRealchk->soukn1flg,
				precRealchk->kanrenflg,
				precRealchk->bunkkuflg,
				precRealchk->kesseiflg,
				precRealchk->rirekiflg,
				precRealchk->syougoflg,
				precRealchk->keisanflg,
				precRealchk->per100flg,
				precRealchk->tousekflg,
				precRealchk->kisyakflg,
				precRealchk->kouseiflg,
				precRealchk->syoungflg,
				precRealchk->soukn2flg,
				precRealchk->fukaptflg,
				precRealchk->yobiflg01,
				precRealchk->tobiflg02,
				precRealchk->yobiflg03,
				precRealchk->yobiflg04,
				precRealchk->yobiflg05,
				precRealchk->renjicpara.data,
				precRealchk->soukn1para.data,
				precRealchk->kanrenpara.data,
				precRealchk->bunkkupara.data,
				precRealchk->kesseipara.data,
				precRealchk->rirekipara.data,
				precRealchk->syougopara.data,
				precRealchk->keisanpara.data,
				precRealchk->per100para.data,
				precRealchk->tousekpara.data,
				precRealchk->kisyakpara.data,
				precRealchk->kouseipara.data,
				precRealchk->syoungpara.data,
				precRealchk->soukn2para.data,
				precRealchk->fukaptpara.data,
				precRealchk->yobipara01.data,
				precRealchk->yobipara02.data,
				precRealchk->yobipara03.data,
				precRealchk->yobipara04.data,
				precRealchk->yobipara05.data,
				precRealchk->ksndh ) ;
	if ( retSts < 0 ) {
		return ( -1 ) ;
	}
	return ( 0 ) ;
}
/******************************************************************************/
/*  関 数 名　：sFncCreFileName()			 								  */
/*  機能概要　：オーダーファイル名生成						  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *   	ファイル名格納バッファ					 	      */
/*　 第２引数 ：char *   	種別									 	      */
/*　 第３引数 ：char *   	ラックＮＯ								 	      */
/*　 第４引数 ：short   	ポジション								 	      */
/*　 第５引数 ：char *   	拡張子									 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：char *														  */
/*					 NULL	終端											  */
/*					 NULL以外	文字列										  */
/******************************************************************************/
static	void
sFncCreFileName ( pc_fileName, pc_kind, pc_asyrckid, ps_pos, pc_sfx, pst_timepos )
char				*pc_fileName ;
char				*pc_kind ;
char				*pc_asyrckid ;
short				 ps_pos ;
char				*pc_sfx ;
struct tm			*pst_timepos ;
{
	
	char	lc_asyrckid[MYAPP_RKNO_SIZE] ;	
	char	lc_asyrckidBuf[MYAPP_RKNO_SIZE] ;	
	
	//	ラックＮＯ編集
	memset ( lc_asyrckid, '\0', sizeof ( lc_asyrckid ) ) ;
	memset ( lc_asyrckid, '_', sizeof ( lc_asyrckid ) - 1 ) ;
	strcpy ( lc_asyrckidBuf, pc_asyrckid ) ;
	sFncTrim ( lc_asyrckidBuf ) ;
	memcpy ( lc_asyrckid, lc_asyrckidBuf, strlen ( lc_asyrckidBuf ) ) ;

		
	//	ファイル名作成
	sprintf ( pc_fileName, "%s_%s%03d%s",
						pc_kind,
						lc_asyrckid,
						ps_pos,
						pc_sfx ) ;
/*****	旧オーダファイル名
	sprintf ( pc_fileName, "%s_%02d%02d%02d%02d%02d%02d_%s%03d%s",
						pc_kind,
						( pst_timepos->tm_year + 1900 ) % 100,
						pst_timepos->tm_mon + 1,
						pst_timepos->tm_mday,
						pst_timepos->tm_hour,
						pst_timepos->tm_min,
						pst_timepos->tm_sec,
						lc_asyrckid,
						ps_pos,
						pc_sfx ) ;
*****/
	return ;
}
/******************************************************************************/
/*  関 数 名　：sFncTrFileToken()			 								  */
/*  機能概要　：トークン分割								  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *   	文字列									 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：char *														  */
/*					 NULL	終端											  */
/*					 NULL以外	文字列										  */
/******************************************************************************/
static	char*
sFncTrFileToken ( pString )
char	*pString ;
{
	char	*p ;
	char	*pRet ;
	int		 liIdx ;

	//	分割文字列ポインター設定
	if ( pString == NULL ) {
		p = gpToken ;	
	}
	else {
		gpToken = pString ;
		p = pString ;	
	}

	//	終端チェック（最終カンマ以降を最後の値と取得するため）	
	if ( p == NULL ) {
		return ( NULL ) ;
	}

	//	トークン分割
	gpToken = NULL ;	//最終カンマ以降を最後の値と取得するため
	pRet = p ;
	while ( *p ) {
		if ( *p == ',' ) {
			*p  = '\0' ;
			gpToken =  p + 1 ;
			break  ;
		}	
		p++ ;
	}
	return ( pRet ) ;
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
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "rename", __LINE__,
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
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmget", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}

	//	アタッチ	
	shmData = ( int * ) shmat ( pAppEnv->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmat", __LINE__,
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
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
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
int					*pshmData ;
{
	int		*shmData ;

	//	アタッチ	
	shmData = ( int * ) shmat ( pAppEnv->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmat", __LINE__,
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
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
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
		//sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmctl", __LINE__,
		//		 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		//		 	 "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}	
/******************************************************************************/
/*  関 数 名　：sFncFileCompar()			 								  */
/*  機能概要　：ファイル名比較【コールバック関数】			  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *   	比較文字列								 	      */
/*　 第２引数 ：char *   	比較文字列								 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/******************************************************************************/
static	int
sFncFileCompar ( a, b ) 
struct dirent	**a ;
struct dirent	**b ;
{
		char	*p1 ;
		char	*p2 ;

		p1 = strchr ( (*a)->d_name, '_' ) ;
		if ( p1 == NULL ) {
			p1 = (*a)->d_name ;
		}
		p2 = strchr ( (*b)->d_name, '_' ) ;
		if ( p2 == NULL ) {
			p2 = (*b)->d_name ;
		}
		return ( strcoll ( p1, p2 ) ) ;
		
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
		//識別チェック
		if ( memcmp ( pdirEnt->d_name, 
					  MYAPP_RECV_KIND, 
					  strlen ( MYAPP_RECV_KIND ) ) != 0 ) {
			return ( 0 ) ;
		}
		//拡張子チェック
		if ( memcmp ( &(pdirEnt->d_name[li_len-strlen(MYAPP_RECV_SFX)]), 
					  MYAPP_RECV_SFX, 
					  strlen ( MYAPP_RECV_SFX ) ) != 0 ) {
			return ( 0 ) ;
		}
		return ( 1 ) ;
}
/******************************************************************************/
/*  関 数 名　：_sFncEnvDip()				 								  */
/*  機能概要　：プログラム環境変数出力関数【トレース用】	  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体			 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：無し														  */
/******************************************************************************/
static void
_sFncEnvDip( pAppEnv )
struct appEnv	*pAppEnv ;
{
#if defined ( _TRACE )
	loging ( "########## Stocker - _sFncEnvDip ##########\n" ) ;
	loging ( "\t【共有ディレクトリ】\n" ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_NR_SUP,     pAppEnv->cDirNR_Sup ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_NR_SUP_OK,  pAppEnv->cDirNR_SupOk ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_NR_SUP_ERR, pAppEnv->cDirNR_SupErr ) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_NR_COL,     pAppEnv->cDirNR_Col ) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_NR_COL_OK,  pAppEnv->cDirNR_ColOk ) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_NR_COL_ERR, pAppEnv->cDirNR_ColErr ) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_NR_LOG,     pAppEnv->cDirNR_Log ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_IA_DAT,     pAppEnv->cDirIA_Dat ) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_IA_DAT_OK,  pAppEnv->cDirIA_DatOk ) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_IA_DAT_ERR, pAppEnv->cDirIA_DatErr ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_IA_IDX,     pAppEnv->cDirIA_Idx ) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_IA_IDX_OK,  pAppEnv->cDirIA_IdxOk ) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_IA_IDX_ERR, pAppEnv->cDirIA_IdxErr ) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_IA_LOG,     pAppEnv->cDirIA_Log ) ;
	loging ( "\t%s : [%d]\n", MYAPP_PRM_SHM_KEY,        pAppEnv->shm_Key ) ;
	loging ( "\t%s : [%d]\n", MYAPP_PRM_SLEEP_SEC,      pAppEnv->sleep_Sec ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DB_NAME,        pAppEnv->cDb_Name ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DB_USER,        pAppEnv->cDb_User ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DB_PASSWD,      pAppEnv->cDb_Passwd ) ;
	loging ( "########## Stocker - _sFncEnvDip ##########\n" ) ;
#endif
}
/******************************************************************************/
/*  関 数 名　：_sFncTrInfoDisp()			 								  */
/*  機能概要　：トレーラック紐付け情報構造体出力関数【トレース用】  		  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct trInfo *   	トレーラック紐付け情報構造体。	 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：無し														  */
/******************************************************************************/
static void
_sFncTrInfoDisp ( pst_trInfo )
struct trInfo	*pst_trInfo ;
{
#if defined ( _TRACE )
	int li_rackCnt ;
	loging ( "########## Stocker - _sFncTrInfoDisp ##########\n" ) ;
	loging ( "ストッカー  :[%s]\n",pst_trInfo->stkno ) ;
	loging ( "トレーＮＯ  :[%s]\n",pst_trInfo->trid ) ;
	loging ( "検査開始日  :[%s]\n",pst_trInfo->knskisymd ) ;
	for ( li_rackCnt = 0 ; li_rackCnt < MYAPP_RACK_MAXCNT ; li_rackCnt++ ) {
		loging ( "ラックＮＯ%02d:[%s]\n",li_rackCnt+1, pst_trInfo->asyrckid[li_rackCnt] ) ;
	}
	loging ( "生成日時    :[%s]\n",pst_trInfo->createDate ) ;
	loging ( "########## Stocker - _sFncTrInfoDisp ##########\n" ) ;
#endif
}

/****************************************************************************/
/*  関 数 名　：insWsseqknri()												*/
/*  機能概要　：初回WSの情報をテーブルに登録する							*/
/*  入　　力　：                                                            */
/*　 第１引数 ：															*/
/*  出　　力　：                                                            */
/*  復帰情報　：  0     : 成功												*/
/* 　　　　　　　-1     : 失敗												*/
/****************************************************************************/
int insWsseqknri( char *sSriymd, char *sKnsgrp, char *sTrid, int iKntsu, int iMinSeq, int iMaxSeq )
{
	int num;
	struct	my_stWSSEQKNRI	strWsSeq ;
	long lRet;
	char	buf[10];

	//ワークシートＳＥＱ管理情報の件数を取得する
	if( (lRet = sFncSelWSSEQKNRI( &num ) ) < 0 ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "insWsseqknri", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"WSSEQKNRI SELECT(ALL) ERROR SQLCODE(%d)", lRet );
		return( -1 );
	}

	//データのセット
	memset(&strWsSeq, 0, sizeof(strWsSeq));
	strWsSeq.wstbnknr = num+1;
	memcpy(strWsSeq.knskisymd, sSriymd, sizeof(strWsSeq.knskisymd)-1);
	memcpy(strWsSeq.knsgrp, sKnsgrp, sizeof(strWsSeq.knsgrp)-1);
	memcpy(strWsSeq.wssbt, sTrid, 4);
	memset(buf, 0, sizeof(buf));
	memcpy(buf, &sTrid[4], 4);
	strWsSeq.wsno = atoi(buf);
	strWsSeq.knsseqst = iMinSeq;
	strWsSeq.knsseqed = iMaxSeq;
	strWsSeq.knsseqsu = iKntsu;
	strcpy(strWsSeq.dtnrtts, "DEAMON");
	strWsSeq.ksktkbn = 'A';

	if( (lRet = sFncInsWSSEQKNRI( &strWsSeq )) < 0 ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "insWsseqknri", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"WSSEQKNRI INSERT ERROR! SQLCODE(%d) ＷＳ管理通番(%d) トレーID(%s)", lRet, strWsSeq.wstbnknr, sTrid );
		return( -1 );
	}
	
	ZdbCommit();

	return( 0 );
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
//	if ( daemon ( 0, 1 ) < 0 ) {
	if ( daemon ( 0, 1 ) < 0 ) {
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                 "daemon起動失敗" ) ;
		exit ( 9 ) ;
	}



	/***
	 ***	初期処理	
	 ***/
	if ( initFunction ( argc, argv, &sAppEnv )  != 0 ) {
		endFunction ( &sAppEnv ) ;
		exit ( 9 ) ;
	}
_sFncEnvDip ( &sAppEnv ) ;
	
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
}

/** End of File ***************************************************************/
