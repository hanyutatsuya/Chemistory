/******************************************************************************/
/* 　ＺＳ０５０　検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：MD103.c                                                      */
/* 　概　　　要：ストッカー【供給】                                           */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2020/05/02                    新規作成                           */
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

#include "MD103.h"

/******************************************************************************/
/* Define定義                                                                 */
/******************************************************************************/

//  フラグ定義
typedef enum {
    LC_false,
    LC_true
} LC_BOOLEAN ;

/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/
MYAPP_STSCODE		 gintErrorCode ;
int			 gtBunchuFlg;		//	自動分注ＯＫ or ＮＧ
struct stcLogMember	 gstLogMem ;		//	ログ出力情報

/******************************************************************************/
/* 関数宣言                                                                   */
/******************************************************************************/
//	トレー・ラック紐付け情報関連関数
static	int	sFncTrFileRead ( struct appEnv *, char *, struct trInfo *, int * ) ;
/*
static	int	sFncSelChkOrderSumiTray ( char *, char *, int * ) ;
static	int	sFncSelChkOrderSumiRack ( char *, char *, int * ) ;
*/
//	ファイル・データベース出力関数
static	int 	sFncOutput ( struct appEnv *, struct trInfo *, int ) ;
static	int 	sFncFileOutOnline ( struct appEnv *, struct my_stKENORDER *, int ) ;
static	int 	sFncFileOutLane ( struct appEnv *, struct my_stKENORDER *, int ) ;
static	int 	sFncOutRecKENORDER ( FILE *, char *, struct my_stKENORDER *, struct appEnv * ) ;
static	int 	sFncOutRecKESSEI ( FILE *, char *, struct my_stKENORDER *, struct appEnv * ) ;
static	int 	sFncOutRecLane ( FILE *, char *, struct my_stKENORDER * ) ;
static	int 	sFncOutRecLaneHeader ( FILE *, char *, struct my_stKENORDER * ) ;
static	void	sFncCreFileName ( char *, char *, char *, short, char *, struct tm * ) ;

//	共有メモリ操作関数
static	int	sFncShmCrt ( struct appEnv * ) ;
static	int	sFncShmGet ( struct appEnv * , int *) ;
static	int	sFncShmDel ( struct appEnv * ) ;

//	コールバック関数
static	int	sFncFileCompar ( struct dirent **, struct dirent ** )  ;
static	int	sFncFileFillter ( struct dirent * ) ;

//	その他
static	int	sFncFileRename ( char *, char *, char *, char * ) ;
static	void	sFncTrim ( char * ) ;
static  void	endFunction(struct appEnv *);

//	トレース用

/******************************************************************************/
/*  関 数 名　：initFunction()							*/
/*  機能概要　：初期処理関数							*/
/*  入　　力　：                                                              */
/*　 第１引数 ：struct	env *   	プログラム環境構造体。		 	*/
/*  出　　力　：                                                              */
/*  復帰情報　：  0     : 成功							*/
/* 　　　　　　　-1     : 失敗							*/
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

	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"プログラム起動" ) ;
	//	開始ログ出力

	/***
	 ***	初期化	
	 ***/
	//	エラーステータス変更
	gintErrorCode = 0 ;

	//	プログラム環境変数初期化
	memset ( pAppEnv , '\0', sizeof ( struct appEnv ) ) ;

	//	パラメータファイル名退避
	pAppEnv->pcFielNamePRM = argv[1] ;

	//	パラメータファイルオープン	
	pAppEnv->bp = ZbmlPrmOpen ( pAppEnv->pcFielNamePRM ) ;		
	if ( pAppEnv->bp == NULL ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmOpen", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"パラメータファイルのオープンに失敗しました[%s]", pAppEnv->pcFielNamePRM ) ;
		return ( -1 ) ;
	}

	//	受信供給
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_NR_SUP, pAppEnv->cDirNR_Sup ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_NR_SUP ) ;
		return ( -1 ) ;
	}
	//	受信供給既読
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_NR_SUP_OK, pAppEnv->cDirNR_SupOk ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_NR_SUP_OK ) ;
		return ( -1 ) ;
	}
	//	受信供給エラー
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_NR_SUP_ERR, pAppEnv->cDirNR_SupErr ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_NR_SUP_ERR ) ;
		return ( -1 ) ;
	}
	//	オンライン用依頼ファイル出力ディレクトリ
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_ONL_DAT, pAppEnv->cDirOnl_Dat ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_ONL_DAT ) ;
		return ( -1 ) ;
	}
	//	日設レーン用依頼ファイル出力ディレクトリ
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_LANE_DAT, pAppEnv->cDirLane_Dat ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_LANE_DAT ) ;
		return ( -1 ) ;
	}
	//	血清情報(乳び)項目コード
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_NYUBI_CODE, pAppEnv->cNyubiCD ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"パラメータが取得できませんでした[%s]", MYAPP_PRM_NYUBI_CODE ) ;
		return ( -1 ) ;
	}
	//	血清情報(溶血)項目コード
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_YOKETSU_CODE, pAppEnv->cYoketsuCD ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"パラメータが取得できませんでした[%s]", MYAPP_PRM_YOKETSU_CODE ) ;
		return ( -1 ) ;
	}
	//	血清情報(黄だん)項目コード
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_OUDANCD_CODE, pAppEnv->cOudanCD ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"パラメータが取得できませんでした[%s]", MYAPP_PRM_OUDANCD_CODE ) ;
		return ( -1 ) ;
	}
	//	血清情報(生食)項目コード　--　血清情報を測定する際に同時に依頼を発生させる必要あり。
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_SEISYOKU_CODE, pAppEnv->cSeisyokuCD ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"パラメータが取得できませんでした[%s]", MYAPP_PRM_SEISYOKU_CODE ) ;
		return ( -1 ) ;
	}
	//	希釈倍率表示用(B10)
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_KSKBR_B10_HYOJI, pAppEnv->cKskbrB10HY ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"パラメータが取得できませんでした[%s]", MYAPP_PRM_KSKBR_B10_HYOJI ) ;
		return ( -1 ) ;
	}
	//	希釈倍率分析機送信用コード(B10)
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_KSKBR_B10_CODE, pAppEnv->cKskbrB10CD ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"パラメータが取得できませんでした[%s]", MYAPP_PRM_KSKBR_B10_CODE ) ;
		return ( -1 ) ;
	}
	//	希釈倍率表示用(B2)
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_KSKBR_B2_HYOJI, pAppEnv->cKskbrB2HY ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"パラメータが取得できませんでした[%s]", MYAPP_PRM_KSKBR_B2_HYOJI ) ;
		return ( -1 ) ;
	}
	//	希釈倍率分析機送信用コード(B2)
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_KSKBR_B2_CODE, pAppEnv->cKskbrB2CD ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"パラメータが取得できませんでした[%s]", MYAPP_PRM_KSKBR_B2_CODE ) ;
		return ( -1 ) ;
	}
	//	共有メモリキー取得
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_SHM_KEY, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"パラメータが取得できませんでした[%s]", MYAPP_PRM_SHM_KEY ) ;
		return ( -1 ) ;
	}

	pAppEnv->shm_Key = atoi ( lc_prmBuf ) ;
	//	SLEEPSEC取得
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_SLEEP_SEC, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"パラメータが取得できませんでした[%s]", MYAPP_PRM_SLEEP_SEC ) ;
		return ( -1 ) ;
	}
	pAppEnv->sleep_Sec= atoi ( lc_prmBuf ) ;
	//	データベース名
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DB_NAME, pAppEnv->cDb_Name ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	"パラメータが取得できませんでした[%s]", MYAPP_PRM_DB_NAME ) ;
		return ( -1 ) ;
	}
	//	データベースユーザ
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DB_USER, pAppEnv->cDb_User ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"パラメータが取得できませんでした[%s]", MYAPP_PRM_DB_USER ) ;
		return ( -1 ) ;
	}
	//	データベースパスワード
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DB_PASSWD, pAppEnv->cDb_Passwd ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DB_PASSWD ) ;
		return ( -1 ) ;
	}
	//	ファイル読込リトライ回数
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_FILE_RETRY, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "パラメータが取得できませんでした[%s]", MYAPP_PRM_FILE_RETRY ) ;
		return ( -1 ) ;
	}
	pAppEnv->fileRetry = atoi ( lc_prmBuf ) ;

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
/*  関 数 名　：mainFunction()							*/
/*  機能概要　：メイン処理関数							*/
/*  入　　力　：                                                              */
/*　 第１引数 ：struct	env *   	プログラム環境構造体。		 	*/
/*  出　　力　：                                                              */
/*  復帰情報　：  0     : 成功							*/
/* 　　　　　　　-1     : 失敗							*/
/******************************************************************************/
int
mainFunction( pAppEnv )
struct appEnv	*pAppEnv ;
{
	int		  li_retSts ;

	int		  li_idx ;	
	int		  li_stopFlg ;

	//	ディレクトリ情報 
	struct dirent	**lpst_dirBuf ;

	//	トレーラック情報関連
	int		 li_fileCnt ;				
	int		 li_rackCnt ;				
	struct trInfo	 lst_trInfo ;
	char		 file_basename[1024];

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
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "scandir", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	  "トレー・ラック紐付け情報ファイルの取得に失敗しました" ) ;
			return ( -1 ) ;
		}

		/***
		 ***	データ処理
		 ***/
		li_idx = 0 ;
		for ( li_idx = 0 ; li_idx < li_fileCnt ; li_idx ++ ) {
			memset( file_basename, '\0', sizeof ( file_basename ) );
			strncpy( file_basename, lpst_dirBuf[li_idx]->d_name, strlen(lpst_dirBuf[li_idx]->d_name)-strlen(MYAPP_RECV_SFX) );
			//	トレー・ラック紐付け情報取得
			li_retSts = sFncTrFileRead ( pAppEnv, lpst_dirBuf[li_idx]->d_name, &lst_trInfo, &li_rackCnt ) ;
			if ( li_retSts < 0 ) {
				//	エラーディレクトリに移動
				sFncFileRename ( pAppEnv->cDirNR_Sup, lpst_dirBuf[li_idx]->d_name,
						 pAppEnv->cDirNR_SupErr, strcat ( file_basename, MYAPP_RECV_SFX_ERR ) ) ;
				//	次のトレー・ラック紐付け情報ファイルの処理を行う
				free ( lpst_dirBuf[li_idx] ) ;
				continue ;
			} else if ( li_retSts == 2 ) {
				//	トレー・ラック紐付け情報ファイル以外
				//	次のトレー・ラック紐付け情報ファイルの処理を行う
				free ( lpst_dirBuf[li_idx] ) ;
				continue ;
			}

			sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						 "ファイル処理開始[%s]", lpst_dirBuf[li_idx]->d_name ) ;

			//	検査オーダー・即時チェック情報出力
			li_retSts = sFncOutput ( pAppEnv, &lst_trInfo, li_rackCnt ) ;
			if ( li_retSts == 0 ) {
				//	既読ディレクトリに移動
				sFncFileRename ( pAppEnv->cDirNR_Sup, lpst_dirBuf[li_idx]->d_name,
						 pAppEnv->cDirNR_SupOk, strcat ( file_basename, MYAPP_RECV_SFX_END ) ) ;
			} else if ( li_retSts == 2 ) {
				//	DBロックが発生した場合、該当ファイルをスキップして次のファイルの処理へ移る
				sleep ( 3 );
				free ( lpst_dirBuf[li_idx] ) ;
				continue ;
			} else {
				//	エラーディレクトリに移動
				sFncFileRename ( pAppEnv->cDirNR_Sup, lpst_dirBuf[li_idx]->d_name,
						 pAppEnv->cDirNR_SupErr, strcat ( file_basename, MYAPP_RECV_SFX_ERR ) ) ;

				if ( li_retSts < 0 ) {
					//	解放
					free ( lpst_dirBuf[li_idx] ) ;
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "[[DB ERROR]]で終了" ) ;
					endFunction ( pAppEnv ) ;
        				exit ( 9 ) ;
				}
			}
			//	解放
			free ( lpst_dirBuf[li_idx] ) ;

			sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						 "ファイル処理完了[%s]", lpst_dirBuf[li_idx]->d_name ) ;
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
/*  関 数 名　：endFunction()							*/
/*  機能概要　：終了処理関数							*/
/*  入　　力　：                                                              */
/*　 第１引数 ：struct	env *   	プログラム環境構造体。		 	*/
/*  出　　力　：                                                              */
/*  復帰情報　：  0     : 成功							*/
/* 　　　　　　　-1     : 失敗							*/
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
/*  関 数 名　：sFncOutput()				 			*/
/*  機能概要　：検査オーダー情報、即時チェックファイル出力	 	 	*/
/*				ラック毎に各ファイル、データベースの更新を行う	*/
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体			*/
/*　 第３引数 ：struct trInfo *  	トレー・ラック紐付け情報格納構造体	*/
/*  出　　力　：                                                              */
/*  復帰情報　：int								*/
/*					 0	正常				*/
/*					 2	デッドロック			*/
/*					-1	異常				*/
/******************************************************************************/
static int
sFncOutput ( pAppEnv, pst_trInfo, li_rackCnt )
struct appEnv	*pAppEnv ;
struct trInfo	*pst_trInfo ;
int		 li_rackCnt ;
{
	int			li_idx ;
	int			li_retSts ;

	char			cSel_knskisymd[MYAPP_DATE_SIZE] ;
	struct my_stKENORDER	*recKENORDER ;		 		 
	struct my_stREALCHK	*recREALCHK ;
	int			recCnt ;
	int			svRecCnt ;
	LC_BOOLEAN		blnErrFlg ;
	LC_BOOLEAN		blnLockFlg ;
	LC_BOOLEAN		blnNgFlg ;
	int			li_BunTrCnt ;
	int			li_len ;
	int			li_Trknhsu ;	//トレー内検体本数
	int			li_MaxOrderTrpos ;
	char			buf[11], buf1[11], buf2[11], cKnsgrp[17] ;

	int			li_TrRkhsu  = 0 ;	//トレー内ラック件数
	int			li_chkCnt = 0 ;		//登録済みオーダー件数
	int			li_LineNo = 0 ;		//投入先ラインＮＯ
	int			li_cntSkip  = 0 ;	//スキップしたラック数
	
	/***
	 ***	変数初期化
	 ***/
	blnErrFlg   = LC_false ;
	blnLockFlg  = LC_false ;
	blnNgFlg    = LC_false ;

	recCnt      = 0 ;
	svRecCnt    = 0 ;
	recKENORDER = NULL ;
	recREALCHK  = NULL ;
	
	//	基本検索キー設定 検査開始日)
	sprintf ( cSel_knskisymd, "%4.4s-%2.2s-%2.2s", 
		  pst_trInfo->knskisymd, &(pst_trInfo->knskisymd[4]), &(pst_trInfo->knskisymd[6]) ) ;

	//	取得したトレーがすでに登録されていないか確認する。
	li_chkCnt = 0;
	li_retSts = sFncSelChkOrderSumiTray ( cSel_knskisymd, pst_trInfo->trid, &li_chkCnt ) ;
	if ( li_retSts == MYAPP_SQL_DEADLOCK ) {
		//デッドロック
		return ( 2 );
	} else if ( li_retSts < 0 ) {
		return ( -1 );
	}
	if ( li_chkCnt > 0 ){
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "該当のトレーはすでに登録済みです。[%s]", pst_trInfo->trid ) ;
		return ( 1 );
	}

	// pst_trInfo->trid(日設ファイル内のトレーID)でKENORDERを検索
	li_BunTrCnt = 0 ;
	li_retSts = sFncSelCntKENORDER ( cSel_knskisymd, pst_trInfo->trid, &li_BunTrCnt ) ;
	if ( li_retSts == MYAPP_SQL_DEADLOCK ) {
		//デッドロック
		return ( 2 );
	} else if ( li_retSts < 0 ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "ＤＢ内ラック数 検索失敗" ) ;
		return ( -1 );
	}

	if ( li_BunTrCnt == 0 ) {
		gtBunchuFlg = MYAPP_BUNCHU_OK;
	} else {
		/* 自動分注分以外(分注ＮＧ、非分注、用手再検等)*/
		gtBunchuFlg = MYAPP_BUNCHU_NG;
/*	
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "前読みラック数[%d] ＤＢ内検体数[%d]" ,li_rackCnt, li_BunTrCnt ) ;
*/
		if ( ( li_BunTrCnt % 5 ) == 0 ) {
			li_TrRkhsu = li_BunTrCnt / 5 ;
		} else {
			li_TrRkhsu = ( li_BunTrCnt / 5 ) + 1;
		}
		/*　前読みで登録したラック数とＤＢ内のラック数が合致しない場合はエラー */
		if ( li_TrRkhsu != li_rackCnt ) {
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "不一致！前読みラック数[%d] ＤＢ内ラック数[%d]" ,li_rackCnt, li_TrRkhsu ) ;
			return ( 1 );
		}
		/*　前読みで登録したトレーの先頭の検体でラインの投入先をチェックし、マスタに登録されていない場合はエラー */
		li_retSts = sFncSelZsLineMstTray( cSel_knskisymd, pst_trInfo->trid, &li_LineNo ) ;
		if ( li_retSts == MYAPP_SQL_DEADLOCK ) {
			//デッドロック
			return ( 2 );
		} else if ( li_retSts < 0 ) {
			return ( -1 );
		}
		if ( li_LineNo <= 0 ) {
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "投入先ライン未登録 トレーＩＤ[%s]", pst_trInfo->trid ) ;
			return ( 0 );
		}
	}
	
	/***
	 ***	メイン処理
	 ***/
	for ( li_idx = 0 ; li_idx < MYAPP_RACK_MAXCNT ; li_idx++ ) {
		//	ブランクは処理を行わない
		if ( pst_trInfo->asyrckid[li_idx][0] == '\0' ) {
			continue ;
		}
		li_chkCnt = 0;
		//	取得したラックがすでに登録されていないか確認する。
		li_retSts = sFncSelChkOrderSumiRack ( cSel_knskisymd, pst_trInfo->asyrckid[li_idx], &li_chkCnt ) ;
		if ( li_retSts == MYAPP_SQL_DEADLOCK ) {
			//デッドロック
			blnLockFlg = LC_true ;
			break ;
		} else if ( li_retSts < 0 ) {
			blnErrFlg = LC_true ;
			break ;
		}
		if ( li_chkCnt > 0 ){
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "該当のアッセイラックはすでに登録済みです。[%s]", pst_trInfo->asyrckid[li_idx] ) ;
			blnNgFlg = LC_true ;
			break ;
		}

		/***
		 ***	更新・検索
		 ***/
		if ( gtBunchuFlg == MYAPP_BUNCHU_NG ) {
			//	検査オーダー情報更新
			li_retSts = sFncUpdKENORDER ( cSel_knskisymd, pst_trInfo->trid, ( 5 * li_idx ) + 1, ( 5 * li_idx ) + 5, pst_trInfo->asyrckid[li_idx], li_idx ) ;
			if ( li_retSts == MYAPP_SQL_DEADLOCK ) {
				//デッドロック
				blnLockFlg = LC_true ;
				break ;
			} else if ( li_retSts < 0 ) {
				blnErrFlg = LC_true ;
				break ;
			}

			//	検体ポジション情報追加
			li_retSts = sFncInsKENPOS ( cSel_knskisymd, pst_trInfo->trid, ( 5 * li_idx ) + 1, ( 5 * li_idx ) + 5, pst_trInfo->stkno ) ;
			if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION) {
				//デッドロックor重複
				blnLockFlg = LC_true ;
				break ;
			} else if ( li_retSts < 0 ) {
				blnErrFlg = LC_true ;
				break ;
			}
			
			//	検査オーダー情報・即時チェック情報検索
			li_retSts = sFncSelKENORDER_REALCHK ( cSel_knskisymd, pst_trInfo->trid, ( 5 * li_idx ) + 1, ( 5 * li_idx ) + 5,
							      &recKENORDER, &recREALCHK, &recCnt ) ;
			if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION) {
				//デッドロックor重複
				blnLockFlg = LC_true ;
				break ;
			} else if ( li_retSts < 0 ) {
			 	blnErrFlg = LC_true ;
				break ;
			}		

			if ( ( recCnt - svRecCnt ) == 0 ) {
				sFncPutLog ( TRCKIND_WARNING, __FILE__, "sFncOutput", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
			 		 	 "検査オーダ情報、または即時チェック情報が存在しません KNSKISYMD='%s' TRID='%s' TRPOS %d-%d RCKID='%s'",
						 cSel_knskisymd, pst_trInfo->trid, ( 5 * li_idx ) + 1, ( 5 * li_idx ) + 5, pst_trInfo->asyrckid[li_idx] ) ;
			 	blnNgFlg = LC_true ;
				break ;
			} else {
				svRecCnt = recCnt ;
			}
		} else {
			/*　前読みで登録したラックの先頭の検体でラインの投入先をチェックし、マスタに登録されていない場合はスキップ */
			li_LineNo = 0 ;
			li_retSts = sFncSelZsLineMstRack( cSel_knskisymd, pst_trInfo->asyrckid[li_idx], &li_LineNo ) ;
			if ( li_retSts == MYAPP_SQL_DEADLOCK ) {
				//デッドロック
				blnLockFlg = LC_true ;
				break;
			} else if ( li_retSts == MYAPP_SQL_NOT_FOUND ) {
				sFncPutLog ( TRCKIND_WARNING, __FILE__, "sFncOutput", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
			 		 	"検査オーダ情報、または即時チェック情報が存在しません KNSKISYMD='%s' TRID='%s' RCKID='%s'",
						cSel_knskisymd, pst_trInfo->trid, pst_trInfo->asyrckid[li_idx] ) ;
			 	blnNgFlg = LC_true ;
				break;
			} else if ( li_retSts < 0 ) {
			 	blnErrFlg = LC_true ;
				break;
			}
			if ( li_LineNo <= 0 ) {
				sFncPutLog ( TRCKIND_WARNING, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "投入先ライン未登録 ラックＩＤ[%s]", pst_trInfo->asyrckid[li_idx] ) ;
				li_cntSkip++ ;
				continue;
			}

			// トレー内検体本数 (100)
			li_Trknhsu = MYAPP_TRKNHSU_MAXCNT ;
			//	検査オーダー情報更新
			memset(buf, 0, sizeof(buf)) ;
			memset(buf1, 0, sizeof(buf1)) ;
			memcpy(buf, pst_trInfo->trid, 11) ;
			li_len = strlen(buf) - 4 ;
			strcpy(buf1, &buf[li_len]);
			li_len = atoi(buf1);
			li_retSts = sFncUpdKENORDER_NXT ( cSel_knskisymd, pst_trInfo->asyrckid[li_idx], pst_trInfo->trid, li_len * li_Trknhsu, li_idx - li_cntSkip) ;
			if ( li_retSts == MYAPP_SQL_DEADLOCK ) {
				//デッドロック
				blnLockFlg = LC_true ;
				break ;
			} else if ( li_retSts < 0 ) {
				blnErrFlg = LC_true ;
				break ;
			}

			//	検体ポジション情報追加
			li_retSts = sFncInsKENPOS_NXT ( cSel_knskisymd, pst_trInfo->asyrckid[li_idx], pst_trInfo->stkno ) ;
			if ( li_retSts == MYAPP_SQL_DEADLOCK ) {
				//デッドロック
				blnLockFlg = LC_true ;
				break ;
			} else if ( li_retSts < 0 ) {
				blnErrFlg = LC_true ;
				break ;
			}
			//	検査オーダー情報・即時チェック情報検索
			li_retSts = sFncSelKENORDER_REALCHK_NXT ( cSel_knskisymd,
								  pst_trInfo->trid,
								  ( 5 * (li_idx - li_cntSkip) ) + 1,
								  ( 5 * (li_idx - li_cntSkip) ) + 5,
								  &recKENORDER,
								  &recREALCHK,
								  &recCnt ) ;
			if ( li_retSts == MYAPP_SQL_DEADLOCK ) {
				//デッドロック
				blnLockFlg = LC_true ;
				break ;
			} else if ( li_retSts < 0 ) {
				blnErrFlg = LC_true ;
				break ;
			}			
			if ( ( recCnt - svRecCnt ) == 0 ) {
				sFncPutLog ( TRCKIND_WARNING, __FILE__, "sFncOutput", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
			 		 	"検査オーダ情報、または即時チェック情報が存在しません KNSKISYMD='%s' TRID='%s' TRPOS %d-%d RCKID='%s'",
						cSel_knskisymd, pst_trInfo->trid, ( 5 * (li_idx - li_cntSkip) ) + 1, ( 5 * (li_idx - li_cntSkip) ) + 5, pst_trInfo->asyrckid[li_idx] ) ;
			 	blnNgFlg = LC_true ;
				break ;
			} else {
				svRecCnt = recCnt ;
			}
		}
	} 

	if ( gtBunchuFlg == MYAPP_BUNCHU_OK ) {
		li_retSts = sFncSelKENORDER ( cSel_knskisymd, pst_trInfo->trid, &li_MaxOrderTrpos );
		if ( li_retSts == MYAPP_SQL_DEADLOCK ) {
			//デッドロック
			blnLockFlg = LC_true ;
		} else if ( li_retSts < 0 ) {
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
			li_retSts = insWsseqknri(cSel_knskisymd, cKnsgrp, pst_trInfo->trid, li_MaxOrderTrpos,
					 (li_len * li_Trknhsu + 1), (li_len * li_Trknhsu + li_MaxOrderTrpos) ) ;

			if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION) {
			    //デッドロック or 重複
			    blnLockFlg = LC_true ;
			} else if ( li_retSts < 0 ) {
			    blnErrFlg = LC_true ;
			}
		}
	}

	/***
	 ***	トランザクション終了
	 ***/
	if ( blnErrFlg == LC_true || blnLockFlg == LC_true || blnNgFlg == LC_true ) {
	 	//	ロールバック
		ZdbRollback () ;
	} else {
		//	コミット
		ZdbCommit () ; 
	}

	/***
	 ***	ファイル出力
	 ***/
	if ( blnErrFlg != LC_true && blnLockFlg != LC_true && blnNgFlg != LC_true && recCnt > 0 ) {
		//	検査オーダー情報
		li_retSts = sFncFileOutOnline ( pAppEnv, recKENORDER, recCnt ) ;
		if ( li_retSts < 0 ) {
			blnErrFlg = LC_true ;
		}
		//	検査オーダー情報
		li_retSts = sFncFileOutLane ( pAppEnv, recKENORDER, recCnt ) ;
		if ( li_retSts < 0 ) {
			blnErrFlg = LC_true ;
		}
	}

	free ( recKENORDER ) ;
	free ( recREALCHK ) ;

	if ( blnNgFlg == LC_true ) {
		return ( 1 ) ; /* 情報未着検体有り。エラーディレクトリへ移動。 */
	}
	if ( blnErrFlg == LC_true ) {
		return ( -1 ) ; /* ＤＢエラー発生。エラーディレクトリへ移動。 */
	}
	if ( blnLockFlg == LC_true ) {
		return ( 2 ) ; /* ＤＢロック発生。スキップして次回に再処理する。 */
	}
	return ( 0 ) ;
}
/******************************************************************************/
/*  関 数 名　：sFncFileOutOnline()			 			*/
/*  機能概要　：検査オーダー・即時チェック情報ファイル出力			*/
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体			*/
/*　 第２引数 ：Kenorder  *   		検査オーダー情報環境構造体		*/
/*  出　　力　：                                                              */
/*  復帰情報　：int								*/
/*					 0	正常				*/
/*					-1	異常				*/
/******************************************************************************/
static int
sFncFileOutOnline ( pAppEnv, precKenorder, precCnt )
struct appEnv		*pAppEnv ;
struct my_stKENORDER	*precKenorder ;
int			 precCnt ;
{
	FILE		*lfp_K ;
	int		 li_cntKessei ;
	char		 lc_recBuf_K[512] ;
	char		 lc_dataFileName_K[MYAPP_PATH_SIZE] ;
	char		 lc_dataFileName_tmp[MYAPP_PATH_SIZE] ;
	char		 lc_fileName_K[MYAPP_PATH_SIZE] ;
	char		 lc_fileName_tmp[MYAPP_PATH_SIZE] ;

	char		 SV_asyrckid[MYAPP_RKNO_SIZE] ;
	int		 SV_asyrckpos ;
	LC_BOOLEAN	 blnFirstFlg ;

	int		 idx ;

	struct tm	*timepos ;
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
	lfp_K   = NULL ;
	
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
				fclose ( lfp_K ) ;
				//検査オーダー情報 ファイル名変更
				if ( rename( lc_dataFileName_tmp, lc_dataFileName_K ) != 0 ) {
					//	異常終了	LOG
					gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "rename", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"ファイル名の変更に失敗しました[%s]", lc_fileName_K ) ;
					return ( -1 ) ;
				}
				sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"オンライン用依頼ファイル出力[%s]", lc_dataFileName_K ) ;
			} else {
				blnFirstFlg = LC_false ;
			}

			/* ブレイクキー初期化 */
			strcpy ( SV_asyrckid, precKenorder[idx].asyrckid ) ;
			SV_asyrckpos =  precKenorder[idx].asyrckpos ;

			//	検査オーダー情報ファイル名作成
			sFncCreFileName ( lc_fileName_K, MYAPP_SEND_KIND_OD, 
							  precKenorder[idx].asyrckid, 
							  precKenorder[idx].asyrckpos, 
							  MYAPP_SEND_SFX, timepos ) ;
			sprintf ( lc_dataFileName_K, "%s/%s", pAppEnv->cDirOnl_Dat,lc_fileName_K);
			//	検査オーダー情報一次ファイル名作成
			sFncCreFileName ( lc_fileName_tmp, MYAPP_SEND_KIND_OD, 
							  precKenorder[idx].asyrckid, 
							  precKenorder[idx].asyrckpos, 
							  MYAPP_SEND_SFX_TMP, timepos ) ;
			sprintf ( lc_dataFileName_tmp,  "%s/%s", pAppEnv->cDirOnl_Dat,lc_fileName_tmp);

			/* ファイルオープン 検査オーダー情報ファイル */
			lfp_K  = fopen ( lc_dataFileName_tmp , "w" ) ;
			if ( lfp_K == NULL ) {
				//	異常終了	LOG
				gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "fopen", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 			"ファイルのオープンに失敗しました[%s]",lc_dataFileName_K);
				return ( -1 ) ;
			}
			/* 血清情報測定有無確認 */
			if ( sFncSelCntKesseiOrder ( precKenorder[idx].knskisymd,
					 	     precKenorder[idx].asyrckid,
						     precKenorder[idx].asyrckpos, 
						     &li_cntKessei ) != 0 ) {
				if ( lfp_K != NULL ) {
					fclose ( lfp_K ) ;
				}
				//	異常終了	LOG
				gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncSelCntKesseiOrder", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"ファイルの出力に失敗しました[%s]", lc_dataFileName_K ) ;
				return ( -1 ) ;
			}
			if ( li_cntKessei > 0 ) {
				//	血清情報オーダー情報レコード作成
				if ( sFncOutRecKESSEI ( lfp_K, lc_recBuf_K, &precKenorder[idx], pAppEnv ) < 0 ) {
					if ( lfp_K != NULL ) {
						fclose ( lfp_K ) ;
					}
					//	異常終了	LOG
					gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOutRecKESSEI", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"ファイルの出力に失敗しました[%s]", lc_dataFileName_K ) ;
					return ( -1 ) ;
				}
			}
		}
		
		//	検査オーダー情報レコード作成
		if ( sFncOutRecKENORDER ( lfp_K, lc_recBuf_K, &precKenorder[idx], pAppEnv ) < 0 ) {
			if ( lfp_K != NULL ) {
				fclose ( lfp_K ) ;
			}
			//	異常終了	LOG
			gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOutRecKENORDER", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"ファイルの出力に失敗しました[%s]", lc_dataFileName_K ) ;
			return ( -1 ) ;
		}
	}

	/***
	 ***	ファイル出力後処理
	 ***/
	//	ファイルクローズ
	if ( lfp_K != NULL ) {
		fclose ( lfp_K ) ;
	}
	//検査オーダー情報 ファイル名変更
	if ( rename( lc_dataFileName_tmp, lc_dataFileName_K ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "rename", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"ファイル名の変更に失敗しました[%s -> %s]", lc_fileName_tmp, lc_fileName_K ) ;
		return ( -1 ) ;
	}

	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"オンライン用依頼ファイル出力[%s]", lc_dataFileName_K ) ;
	return ( 0 ) ;
}
/******************************************************************************/
/*  関 数 名　：sFncFileOutLane()			 			*/
/*  機能概要　：検査オーダー・即時チェック情報ファイル出力			*/
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体			*/
/*　 第２引数 ：Kenorder  *   		検査オーダー情報環境構造体		*/
/*  出　　力　：                                                              */
/*  復帰情報　：int								*/
/*					 0	正常				*/
/*					-1	異常				*/
/******************************************************************************/
static int
sFncFileOutLane ( pAppEnv, precKenorder, precCnt )
struct appEnv		*pAppEnv ;
struct my_stKENORDER	*precKenorder ;
int			 precCnt ;
{
	FILE		*lfp_Lane ;
	char		 lc_recBuf_Lane[512] ;
	char		 lc_asyrckidBuf[MYAPP_RKNO_SIZE] ;	
	char		 lc_dataFileName_Lane[MYAPP_PATH_SIZE] ;
	char		 lc_dataFileName_tmp[MYAPP_PATH_SIZE] ;
	char		 lc_fileName_Lane[MYAPP_PATH_SIZE] ;
	char		 lc_fileName_tmp[MYAPP_PATH_SIZE] ;

	char		 SV_asyrckid[MYAPP_RKNO_SIZE] ;
	int		 SV_asyrckpos ;
	LC_BOOLEAN	 blnFirstFlg ;

	int		 idx ;
 
	/***
	 ***	初期処理
	 ***/
	blnFirstFlg   = LC_true ;
	//	ブレイクキー
	memset ( SV_asyrckid, '\0', sizeof ( SV_asyrckid ) ) ;
	SV_asyrckpos = -1 ;
	//	変数初期化
	lfp_Lane = NULL ;
	
	for ( idx = 0 ; idx < precCnt ; idx ++ ) {

		if ( strcmp ( SV_asyrckid, precKenorder[idx].asyrckid ) != 0 ){
			/* 初回以外の処理(検査オーダー情報ファイル出力, ファイルクロース) */
			if ( blnFirstFlg != LC_true ) {
			 	//	ファイルクローズ
				fclose ( lfp_Lane ) ;
				//検査オーダー情報 ファイル名変更
				if ( rename( lc_dataFileName_tmp, lc_dataFileName_Lane ) != 0 ) {
					//	異常終了	LOG
					gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "rename", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"ファイル名の変更に失敗しました[%s]", lc_fileName_Lane ) ;
					return ( -1 ) ;
				}
				sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"日設ライン用依頼ファイル出力[%s]", lc_dataFileName_Lane ) ;
			} else {
				blnFirstFlg = LC_false ;
			}

			/* ブレイクキー初期化 */
			strcpy ( SV_asyrckid, precKenorder[idx].asyrckid ) ;
			SV_asyrckpos =  precKenorder[idx].asyrckpos ;

			//	ラックＮＯ
			memset ( lc_asyrckidBuf, '\0', sizeof ( lc_asyrckidBuf ) ) ;
			strcpy ( lc_asyrckidBuf, precKenorder[idx].asyrckid ) ;
			sFncTrim ( lc_asyrckidBuf ) ;

			/* 検査オーダー情報ファイル名作成 */
			sprintf ( lc_fileName_Lane, "%s%s", lc_asyrckidBuf, MYAPP_SEND_SFX ) ;
			sprintf ( lc_dataFileName_Lane, "%s/%s", pAppEnv->cDirLane_Dat,lc_fileName_Lane);
			/* 検査オーダー情報一次ファイル名作成 */
			sprintf ( lc_fileName_tmp, "%s%s", lc_asyrckidBuf, MYAPP_SEND_SFX_TMP ) ;
			sprintf ( lc_dataFileName_tmp,  "%s/%s", pAppEnv->cDirLane_Dat,lc_fileName_tmp);

			/* 検査オーダー情報ファイル オープン */
			lfp_Lane  = fopen ( lc_dataFileName_tmp , "w" ) ;
			if ( lfp_Lane == NULL ) {
				//	異常終了	LOG
				gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "fopen", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"ファイルのオープンに失敗しました[%s]",lc_dataFileName_tmp);
				return ( -1 ) ;
			}
			/* ラックＩＤが切り替わったら、ヘッダレコード作成 */
			if ( sFncOutRecLaneHeader ( lfp_Lane, lc_recBuf_Lane, &precKenorder[idx] ) < 0 ) {
				//	異常終了	LOG
				gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOutRecLane", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"ファイルの出力に失敗しました[%s]", lc_dataFileName_tmp ) ;
				return ( -1 ) ;
			}
			/* ラックＩＤが切り替わったら、検査オーダー情報レコード作成 */
			if ( sFncOutRecLane ( lfp_Lane, lc_recBuf_Lane, &precKenorder[idx] ) < 0 ) {
				//	異常終了	LOG
				gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOutRecLane", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"ファイルの出力に失敗しました[%s]", lc_dataFileName_tmp ) ;
				return ( -1 ) ;
			}
		}
		
		/* ラックポジションが切り替わったら、検査オーダー情報レコード作成 */
		if ( SV_asyrckpos != precKenorder[idx].asyrckpos ){
			if ( sFncOutRecLane ( lfp_Lane, lc_recBuf_Lane, &precKenorder[idx] ) < 0 ) {
				//	異常終了	LOG
				gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOutRecLane", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"ファイルの出力に失敗しました[%s]", lc_dataFileName_tmp ) ;
				return ( -1 ) ;
			}
			SV_asyrckpos =  precKenorder[idx].asyrckpos ;
		}
	}

	//	ファイルクローズ
	if ( lfp_Lane != NULL ) {
		fclose ( lfp_Lane ) ;
	}
	//検査オーダー情報 ファイル名変更
	if ( rename( lc_dataFileName_tmp, lc_dataFileName_Lane ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "rename", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
	 	 		"ファイル名の変更に失敗しました[%s]", lc_fileName_Lane ) ;
		return ( -1 ) ;
	}

	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		     "日設ライン用依頼ファイル出力[%s]", lc_dataFileName_Lane ) ;
	return ( 0 ) ;
}
/******************************************************************************/
/*  関 数 名　：sFncTrFileRead()			 			*/
/*  機能概要　：トレー・ラック紐付け情報読込				  	*/
/*	特記事項  ：第２引数はfree						*/
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体		 	*/
/*　 第２引数 ：char *  	 	トレー・ラック紐付け情報ファイル名	*/
/*　 第３引数 ：struct trInfo *   	トレー・ラック紐付け情報格納構造体    	*/
/*  出　　力　：                                                              */
/*  復帰情報　：int								*/
/*					 0	正常				*/
/*					-1	異常				*/
/*					 1	データ異常			*/
/******************************************************************************/
static	int
sFncTrFileRead ( pAppEnv, pc_trFileName, pst_trInfo, li_rackCnt )
struct appEnv	*pAppEnv ;
char		*pc_trFileName ;
struct trInfo	*pst_trInfo ;
int		*li_rackCnt ;
{
	FILE		*lfp ;
	char		 lc_recBuf[MYAPP_RECV_RECSIZE] ;
	int	 	 li_recBuflen;
	int		 li_idx ;
	int		 li_idx_rack ;
	int		 li_retryCnt ;

	char		 lc_fileName[1024] ;
	struct stat	 lst_statBuf ;

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

	//	構造体設定
	li_idx = 0 ;
	li_idx_rack = 0 ;
	memset ( pst_trInfo, '\0', sizeof ( struct trInfo ) ) ;
	//	トレーＩＤ取得
	strncpy ( pst_trInfo->trid, lc_recBuf, 8 ) ;
	//	ラックＩＤ取得
	while ( li_idx  < MYAPP_RACK_MAXCNT ) {
		strncpy ( pst_trInfo->asyrckid[li_idx], &lc_recBuf[ 8+(li_idx*5) ], 5 ) ;
		sFncTrim ( pst_trInfo->asyrckid[li_idx] ) ;
                if ( pst_trInfo->asyrckid[li_idx][0] != '\0' ) {
			li_idx_rack++ ;
                }
		li_idx++ ;
	}
	*li_rackCnt = li_idx_rack;

	//	トレーＩＤ取得
	strncpy ( pst_trInfo->knskisymd, &lc_recBuf[108], 8 ) ;

	/***
	 ***	ストッカーＮＯ(前読み一台のため固定とする)
	 ***/
	memcpy ( pst_trInfo->stkno, "10", sizeof ( pst_trInfo->stkno ) - 1 ) ;

	return ( 0 ) ;
}
/******************************************************************************/
/*  関 数 名　：sFncPutLog()  			 				*/
/*  機能概要　：アプリケーションログ出力					*/
/*  入　　力　：                                                              */
/*　 第１引数 ：char *   	編集文字列					*/
/*  出　　力　：                                                              */
/*  復帰情報　：無し								*/
/******************************************************************************/
void
sFncPutLog ( LOG_TRCKIND peTrcKind, char * pcSrcName, char * pcFncName, int plLineNo, char * pcExeFlg, char * pcErrCode, char * pcfmt, ... ) 
{
	va_list	 ap ;

	/***
	 ***	ログ初期値設定
	 ***/
	gstLogMem.eTrcKind = peTrcKind ;
	strcpy ( gstLogMem.pcFncName, pcFncName ) ;
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
/*  関 数 名　：sFncOutRecKENORDER()		 				*/
/*  機能概要　：検査オーダ情報情報レコード生成				  	*/
/*  入　　力　：                                                              */
/*　 第２引数 ：struct my_stKENORDER *   	検査オーダ情報構造体		*/
/*  出　　力　：                                                              */
/*　 第１引数 ：char 				*   	レコード格納バッファ	*/
/*  復帰情報　：無し								*/
/******************************************************************************/
static	int
sFncOutRecKENORDER ( pfp, p_recBuf, precKenorder, pAppEnv )
FILE					*pfp ;
char					*p_recBuf ;
struct my_stKENORDER	*precKenorder ;
struct appEnv	*pAppEnv ;
{
	int		retSts ;
	char		cYtiksbr[15+1];

	/* セットする予定希釈倍率を分析機向けに変換する */
	memset( cYtiksbr, '\0', sizeof ( cYtiksbr ) );
	strncpy( cYtiksbr, precKenorder->ytiksbr, sizeof ( cYtiksbr ) - 1 );
	sFncTrim ( cYtiksbr );
	if( strcmp( cYtiksbr, pAppEnv->cKskbrB10HY ) == 0 ){
		memset( cYtiksbr, ' ', sizeof ( cYtiksbr ) - 1 );
		strncpy( cYtiksbr, pAppEnv->cKskbrB10CD , strlen( pAppEnv->cKskbrB10CD ) );
	} else if ( strcmp( cYtiksbr, pAppEnv->cKskbrB2HY ) == 0 ) {
		memset( cYtiksbr, ' ', sizeof ( cYtiksbr ) - 1 );
		strncpy( cYtiksbr, pAppEnv->cKskbrB2CD , strlen( pAppEnv->cKskbrB2CD ) );
	} else {
		memset( cYtiksbr, ' ', sizeof ( cYtiksbr ) - 1 );
	}

	//	レコード作成
	retSts = fprintf ( pfp, "%s,%s,%s,%s,%s,%s,%hd,%hd,%s,%s,%s,%s,%s,%s,%hd,%s,%s,%hd,%s,%hd,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%hd,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%hd,%s,%s\n",
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
				/* precKenorder->ytiksbr, */
				cYtiksbr,
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
/*  関 数 名　：sFncOutRecKESSEI()		 				*/
/*  機能概要　：血清情報オーダ情報情報レコード生成			  	*/
/*  入　　力　：                                                              */
/*　 第２引数 ：struct my_stKENORDER *   	検査オーダ情報構造体		*/
/*  出　　力　：                                                              */
/*　 第１引数 ：char 				*   	レコード格納バッファ	*/
/*  復帰情報　：無し								*/
/******************************************************************************/
static	int
sFncOutRecKESSEI ( pfp, p_recBuf, precKenorder, pAppEnv )
FILE					*pfp ;
char					*p_recBuf ;
struct my_stKENORDER	*precKenorder ;
struct appEnv	*pAppEnv ;
{
	int	retSts ;
	int	i ;
	char	cKesseiCd[4][7+1] ;

	strcpy( cKesseiCd[0], pAppEnv->cNyubiCD );
	strcpy( cKesseiCd[1], pAppEnv->cYoketsuCD );
	strcpy( cKesseiCd[2], pAppEnv->cOudanCD );
	strcpy( cKesseiCd[3], pAppEnv->cSeisyokuCD );
	for(i = 0; i <= 3; i++) {
	//	レコード作成
		retSts = fprintf ( pfp, "%s,%s,%s,%s,%s,%s,%hd,%hd,%s,%s,%s,%s,%s,%s,%hd,%s,%s,%hd,%s,%hd,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%hd,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%hd,%s,%s\n",
					precKenorder->knskisymd,
					precKenorder->sriymd,
					precKenorder->kntno,
					precKenorder->kntketflg,
					"    ",
					cKesseiCd[i],
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
					"       ",
					precKenorder->seccd,
					precKenorder->bkfkkbn,
					precKenorder->smpcd,
					precKenorder->bskkbn,
					precKenorder->nbkmkcd,
					"   ",
					precKenorder->ysnlbl,
					"  ",
					precKenorder->fkhkknohjkbn,
					precKenorder->tbkjno,
					precKenorder->tbkjflg,
					precKenorder->htkfkhms,
					precKenorder->skflg,
					precKenorder->tskflg,
					precKenorder->tktflg,
					/* precKenorder->ytiksbr, */
					" ",
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
	}
	return ( 0 ) ;
}
/******************************************************************************/
/*  関 数 名　：sFncOutRecLaneHeader()		 				*/
/*  機能概要　：搬送レーン用依頼情報ヘッダレコード生成			  	*/
/*  入　　力　：                                                              */
/*　 第２引数 ：struct my_stKENORDER *   	検査オーダ情報構造体		*/
/*  出　　力　：                                                              */
/*　 第１引数 ：char 				*   	レコード格納バッファ	*/
/*  復帰情報　：無し								*/
/******************************************************************************/
static	int
sFncOutRecLaneHeader ( pfp, p_recBuf, precKenorder )
FILE			*pfp ;
char			*p_recBuf ;
struct my_stKENORDER	*precKenorder ;
{
	int	retSts ;
	int	iLine ;	
	char	lc_asyrckidBuf[MYAPP_RKNO_SIZE] ;
	char	lc_knskisymdBuf[10+1] ;
	char	lc_yyyyBuf[4+1] ;
	char	lc_mmBuf[2+1] ;
	char	lc_ddBuf[2+1] ;

	retSts = sFncSelZsLineMst ( precKenorder->knskisymd, precKenorder->knsgrp, &iLine ) ;
	if ( retSts < 0 ) {
		return ( -1 ) ;
	}

	//	検査開始日
	memset ( lc_knskisymdBuf, '\0', sizeof ( lc_knskisymdBuf ) ) ;
	strncpy ( lc_knskisymdBuf, precKenorder->knskisymd, 10 ) ;
	memset ( lc_yyyyBuf, '\0', sizeof ( lc_yyyyBuf ) ) ;
	strncpy ( lc_yyyyBuf, lc_knskisymdBuf, 4 ) ;
	memset ( lc_mmBuf, '\0', sizeof ( lc_mmBuf ) ) ;
	strncpy ( lc_mmBuf, &lc_knskisymdBuf[5], 2 ) ;
	memset ( lc_ddBuf, '\0', sizeof ( lc_ddBuf ) ) ;
	strncpy ( lc_ddBuf, &lc_knskisymdBuf[8], 2 ) ;
	
	//	ラックＮＯ
	memset ( lc_asyrckidBuf, '\0', sizeof ( lc_asyrckidBuf ) ) ;
	strcpy ( lc_asyrckidBuf, precKenorder->asyrckid ) ;
	sFncTrim ( lc_asyrckidBuf ) ;
/*
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "sFncOutRecLaneHeader[%s,%s]", precKenorder->knskisymd, lc_asyrckidBuf ) ;
*/
	//	レコード作成
	retSts = fprintf ( pfp, "%s%s%s%s%d\r\n",
				lc_yyyyBuf ,
				lc_mmBuf ,
				lc_ddBuf ,
				lc_asyrckidBuf,
				iLine ) ;
	if ( retSts < 0 ) {
		return ( -1 ) ;
	}
	return ( 0 ) ;
}
/******************************************************************************/
/*  関 数 名　：sFncOutRecLane()		 				*/
/*  機能概要　：搬送レーン用依頼情報レコード生成			  	*/
/*  入　　力　：                                                              */
/*　 第２引数 ：struct my_stKENORDER *   	検査オーダ情報構造体		*/
/*  出　　力　：                                                              */
/*　 第１引数 ：char 				*   	レコード格納バッファ	*/
/*  復帰情報　：無し								*/
/******************************************************************************/
static	int
sFncOutRecLane ( pfp, p_recBuf, precKenorder )
FILE			*pfp ;
char			*p_recBuf ;
struct my_stKENORDER	*precKenorder ;
{
	int		retSts ;
	//	レコード作成
/*
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"sFncOutRecLane[%03d,%s]", precKenorder->asyrckpos, precKenorder->irino ) ;
*/
	retSts = fprintf ( pfp, "%03d%s\r\n",
				precKenorder->asyrckpos,
				precKenorder->irino ) ;
	if ( retSts < 0 ) {
		return ( -1 ) ;
	}
	return ( 0 ) ;
}
/******************************************************************************/
/*  関 数 名　：sFncCreFileName()						*/
/*  機能概要　：オーダーファイル名生成						*/
/*  入　　力　：                                                              */
/*　 第１引数 ：char *   	ファイル名格納バッファ				*/
/*　 第２引数 ：char *   	種別						*/
/*　 第３引数 ：char *   	ラックＮＯ					*/
/*　 第４引数 ：short   	ポジション					*/
/*　 第５引数 ：char *   	拡張子						*/
/*  出　　力　：                                                              */
/*  復帰情報　：char *								*/
/*					 NULL	終端				*/
/*					 NULL以外	文字列			*/
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
	return ;
}
/******************************************************************************/
/*  関 数 名　：sFncTrim()  			 				*/
/*  機能概要　：文字列前後のスペースを削除する				  	*/
/*  入　　力　：                                                              */
/*　 第１引数 ：char *   	編集文字列					*/
/*  出　　力　：                                                              */
/*  復帰情報　：無し								*/
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
/*  関 数 名　：sFncFileRename()  			 			*/
/*  機能概要　：ファイルを移動する。						*/
/*	　　　　移動先に同じ名前のファイルが存在した場合はインクリメントする。	*/
/*  入　　力　：                                                              */
/*　 第１引数 ：char *   	移動元ディレクトリ				*/
/*　 第２引数 ：char *   	移動元ファイル名				*/
/*　 第３引数 ：char *   	移動先ディレクトリ				*/
/*　 第４引数 ：char *   	移動先ファイル					*/
/*  出　　力　：                                                              */
/*  復帰情報　：int								*/
/*					 0	正常				*/
/*					-1	異常				*/
/******************************************************************************/
static int
sFncFileRename ( pc_fromDir, pc_fromFileName, pc_toDir, pc_toFileName )
char	*pc_fromDir ;
char	*pc_fromFileName ;
char	*pc_toDir ;
char	*pc_toFileName ;
{
	char		lc_fromPath[MYAPP_PATH_SIZE] ;
	char		lc_toPath[MYAPP_PATH_SIZE] ;
	int		ret = 0;
	int		retry_cnt = 1;
	struct stat	fst;

	sprintf ( lc_fromPath, "%s/%s", pc_fromDir, pc_fromFileName ) ;
	sprintf ( lc_toPath,   "%s/%s", pc_toDir,   pc_toFileName ) ;

	ret = stat ( lc_toPath, &fst ) ;
	if (ret == 0) {
		/* 既にファイルが存在する。無いファイル名を検索 */
		while ( ret == 0 ) {
			sprintf ( lc_toPath, "%s/%s%02d", pc_toDir, pc_toFileName, retry_cnt ) ;
			ret = stat ( lc_toPath, &fst ) ;
			retry_cnt ++ ;
			if ( retry_cnt > 99 ) {
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncFileRename", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
 	 			 		 "ファイルのカウンタが最大値を超えました" ) ;
				return ( -1 ) ;
			}
		}
	}

	if ( rename ( lc_fromPath, lc_toPath ) < 0 ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncFileRename:rename", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
 	 	 		 "ファイルの移動に失敗しました[%s->%s]", lc_fromPath, lc_toPath ) ;
		return ( -1 ) ;
	}
	
	return ( 0 ) ;
}
/******************************************************************************/
/*  関 数 名　：sFncShmCrt()				 			*/
/*  機能概要　：共有メモリ生成							*/
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体			*/
/*  出　　力　：                                                              */
/*  復帰情報　：int								*/
/*					 0	正常				*/
/*					-1	異常				*/
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
/*  関 数 名　：sFncShmGet()				 			*/
/*  機能概要　：共有メモリ取得							*/
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体		 	*/
/*　 第２引数 ：int *   			値				*/
/*  出　　力　：                                                              */
/*  復帰情報　：int								*/
/*					 0	正常				*/
/*					-1	異常				*/
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
/*  関 数 名　：sFncShmDel()				 			*/
/*  機能概要　：共有メモリ削除							*/
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体。		 	*/
/*  出　　力　：                                                              */
/*  復帰情報　：int								*/
/*					 0	正常				*/
/*					-1	異常				*/
/******************************************************************************/
static int
sFncShmDel ( pAppEnv )
struct appEnv	*pAppEnv ;
{

	//	削除	
	if ( shmctl ( pAppEnv->shm_Id, IPC_RMID, NULL) < 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}	
/******************************************************************************/
/*  関 数 名　：sFncFileCompar()			 			*/
/*  機能概要　：ファイル名比較【コールバック関数】			  	*/
/*  入　　力　：                                                              */
/*　 第１引数 ：char *   	比較文字列					*/
/*　 第２引数 ：char *   	比較文字列					*/
/*  出　　力　：                                                              */
/*  復帰情報　：int								*/
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
/*  関 数 名　：sFncFileFillter()						*/
/*  機能概要　：ファイルフィルター【コールバック関数】				*/
/*  入　　力　：                                                              */
/*　 第１引数 ：struct dirent *		ディレクトリ構造体		 	*/
/*  出　　力　：                                                              */
/*  復帰情報　：int								*/
/*					 0	対象外ファイル			*/
/*					 1	対象ファイル			*/
/******************************************************************************/
static	int
sFncFileFillter ( pdirEnt ) 
struct dirent *pdirEnt ;
{
		int		li_len ;

		//文字列長チェック
		li_len = strlen ( pdirEnt->d_name )  ;
		if ( li_len != 12 ) {
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

/****************************************************************************/
/*  関 数 名　：insWsseqknri()							*/
/*  機能概要　：初回WSの情報をテーブルに登録する				*/
/*  入　　力　：                                                            */
/*　 第１引数 ：								*/
/*  出　　力　：                                                            */
/*  復帰情報　：  0     : 成功							*/
/* 　　　　　　　-1     : 失敗							*/
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
	
	return( 0 );
}

/******************************************************************************/
/*  関 数 名　：main()								*/
/*  機能概要　：メイン関数							*/
/*  入　　力　：                                                              */
/*　 第１引数 ：char *pcLogName	【任意】ログファイル名を指定する。		*/
/*					※NULLを指定した場合はINIファイルより	*/
/*					  ログ情報を取得する。			*/
/*  出　　力　：                                                              */
/*  復帰情報　：  0     : 成功							*/
/* 　　　　　　　-1     : 失敗							*/
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

	exit ( 0 ) ;
}

/** End of File ***************************************************************/
