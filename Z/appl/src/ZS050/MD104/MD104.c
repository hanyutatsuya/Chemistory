/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：MD104.c                                                      */
/* 　概　　　要：ストッカー【回収】                                           */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/15     芳賀弘幸       新規作成                           */
/*  1.01     2006/12/06   YOON JONG JIN    エラー追加                         */
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

#include "MD104.h"

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
struct stcLogMember		 gstLogMem ;		//	ログ出力情報

/******************************************************************************/
/* 関数宣言                                                                   */
/******************************************************************************/
//	トレー・ラック紐付け情報関連関数
static	int	sFncTrFileRead ( struct appEnv *, char *, struct trInfo * ) ;

//	ファイル・データベース出力関数
static	int 	sFncOutput ( struct appEnv *, struct trInfo * ) ;


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

//	トレース用
static	void	_sFncEnvDip ( struct appEnv * ) ;
static	void	_sFncTrInfoDisp ( struct trInfo * ) ;

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
     ***    引数チェック
     ***/
	if ( argc != 2 ) {
		fprintf ( stderr, "%s : There is an error in a command parameter\n", MYAPP_APP_NAME ) ;
		return ( -1 ) ;
	}

	/***
	 ***	ログオープン
	 ***/
	if ( ZbmlOpenLog ( argv[1] ) != 0 ) {
		return ( -1 ) ;
	}

	//	ログ情報初期設定
	memset ( &gstLogMem, '\0', sizeof ( gstLogMem ) ) ;
	if ( ( lc_login = getenv( "LOGNAME" ) ) != NULL ) {
		strcpy ( gstLogMem.pcLoginId, lc_login ) ;
	}
	strcpy ( gstLogMem.pcAppName, MYAPP_APP_NAME ) ;

	//	開始ログ出力
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__,
				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "プログラム起動" ) ;

	/***
	 ***	初期化	
	 ***/
	//	エラーステータス変更
	gintErrorCode = 0 ;

	//	プログラム環境変数初期化
	memset ( pAppEnv , '\0', sizeof ( struct appEnv ) ) ;

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

	//	受信回収
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_NR_COL,
						pAppEnv->cDirNR_Col ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_NR_COL ) ;
		return ( -1 ) ;
	}
	//	受信回収既読
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_NR_COL_OK, 
						pAppEnv->cDirNR_ColOk ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_NR_COL_OK ) ;
		return ( -1 ) ;
	}
	//	受信回収エラー
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_NR_COL_ERR, 
						pAppEnv->cDirNR_ColErr ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_NR_COL_ERR ) ;
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

	//	パラメータファイルクローズ	
	ZbmlPrmClose ( pAppEnv->bp ) ;

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
	int			  li_retSts ;
	long			  ll_retSts ;

	int			  li_idx ;	
	int			  li_stopFlg ;

	//	ディレクトリ情報 
	DIR			 *lt_dp ;
	struct dirent		**lpst_dirBuf ;

	//	トレーラック情報関連
	int			  li_fileCnt ;				
	struct trInfo		  lst_trInfo ;

	/***
	 ***	受信トレー・ラック回収ディレクトリ監視	
	 ***		永久ループ
	 ***		停止コマンドで終了
	 ***/
	while ( 1 ) {

		/***
		 *** ファイル名取得
		 ***/
		if ( ( li_fileCnt = scandir ( pAppEnv->cDirNR_Col, 
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

			//	トレー・ラック紐付け情報取得
			li_retSts=sFncTrFileRead ( pAppEnv,lpst_dirBuf[li_idx]->d_name, &lst_trInfo ) ;
			if ( li_retSts < 0 ) {
				//	エラーディレクトリに移動
				sFncFileRename ( pAppEnv->cDirNR_Col, 
							lpst_dirBuf[li_idx]->d_name,
							pAppEnv->cDirNR_ColErr,
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

			//	情報出力
			li_retSts = sFncOutput ( pAppEnv, &lst_trInfo ) ;
			if ( li_retSts == 0 ) {
				//	既読ディレクトリに移動
				sFncFileRename ( pAppEnv->cDirNR_Col, 
							 lpst_dirBuf[li_idx]->d_name,
							 pAppEnv->cDirNR_ColOk,
							 lpst_dirBuf[li_idx]->d_name ) ;
			} else {
				if ( li_retSts != 2 ) {
					//	エラーディレクトリに移動
					sFncFileRename ( pAppEnv->cDirNR_Col,
							lpst_dirBuf[li_idx]->d_name,
							pAppEnv->cDirNR_ColErr,
							lpst_dirBuf[li_idx]->d_name ) ;
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__,
				 			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 			"[[DB ERROR]] プロセス終了" ) ;
		
					return 0;						
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
	 ***	ログクロース
	 ***/
	//	開始ログ出力
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
/*					-1	異常				*/
/******************************************************************************/
static int
sFncOutput ( pAppEnv, pst_trInfo )
struct appEnv		*pAppEnv ;
struct trInfo		*pst_trInfo ;
{
	int		li_idx ;
	int		li_recIdx ;
	int		li_retSts ;
	long	 	ll_retSts ;
	int		li_Return ;

	char		cSel_knskisymd[MYAPP_DATE_SIZE] ;
	int		recCnt ;
	LC_BOOLEAN	blnErrFlg ;
	LC_BOOLEAN	blnLockFlg ;
	
	/***
	 ***	変数初期化
	 ***/
	recCnt = 0 ;
	blnErrFlg 	= LC_false ;
	blnLockFlg  = LC_false ;
	li_Return = 0 ;
	
	//	基本検索キー設定
	sprintf ( cSel_knskisymd, "%4.4s-%2.2s-%2.2s", 
				  pst_trInfo->knskisymd, 
				  &(pst_trInfo->knskisymd[4]), 
				  &(pst_trInfo->knskisymd[6]) ) ;
	
	/***
	 ***	メイン処理
	 ***/
	for ( li_idx = 0 ; li_idx < MYAPP_RACK_MAXCNT ; li_idx++ ) {
		//	ブランクは処理を行わない
		if ( pst_trInfo->asyrckid[li_idx][0] == '\0' ) {
			continue ;
		}

		blnErrFlg = LC_false ;

		/***
		 ***	更新
		 ***/
		//	検体ポジション情報追加
		li_retSts = sFncInsKENPOS ( cSel_knskisymd,
						pst_trInfo->asyrckid[li_idx],
						pst_trInfo->trid,
						pst_trInfo->stkno,
						li_idx ) ;
		
		if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
		{	//デッドロックor重複
			blnLockFlg = LC_true ;
		}
		else if ( li_retSts < 0 ) {
			blnErrFlg = LC_true ;
		}

		//	検査オーダー情報更新
		li_retSts = sFncUpdKENORDER ( cSel_knskisymd, pst_trInfo->asyrckid[li_idx] ) ;
		if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
		{   //デッドロックor重複
			blnLockFlg = LC_true ;
		}		
		if ( li_retSts < 0 ) {
			blnErrFlg = LC_true ;
		}

		/***
	 	 ***    トランザクション終了
	  	 ***    検査オーダ情報のみトランザクション終了
	 	 ***/
		if ( blnLockFlg == LC_true) {
			//  ロールバック
			ZdbRollback () ;
		}
		else if(blnErrFlg == LC_true){
		        ZdbRollback () ;
		        break;
		} else {
			//  コミット
			ZdbCommit () ;
		}
	} 

	if ( li_retSts < 0 ) {
		//  ロールバック
		ZdbRollback () ;
	} else {
		//  コミット
		ZdbCommit () ;
	}


	/***
	 ***	トランザクション終了
	 ***/
	if ( blnLockFlg == LC_true ) {
		return ( 2 ) ;
	}
	if ( blnErrFlg == LC_true ) {
		return ( -1 ) ;
	}
	
	return ( 0 ) ;
}
/******************************************************************************/
/*  関 数 名　：sFncTrFileRead()			 			*/
/*  機能概要　：トレー・ラック紐付け情報読込				  	*/
/*	特記事項  ：第２引数はfree						*/
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体			*/
/*　 第２引数 ：char *  	 	トレー・ラック紐付け情報ファイル名	*/
/*　 第３引数 ：struct trInfo *   	トレー・ラック紐付け情報格納構造体	*/
/*  出　　力　：                                                              */
/*  復帰情報　：int								*/
/*					 0	正常				*/
/*					-1	異常				*/
/*					 1	データ異常			*/
/******************************************************************************/
static	int
sFncTrFileRead ( pAppEnv, pc_trFileName, pst_trInfo )
struct appEnv	*pAppEnv ;
char			*pc_trFileName ;
struct trInfo	*pst_trInfo ;
{
	FILE		 *lfp ;
	char	 	  lc_recBuf[MYAPP_RECV_RECSIZE] ;
	int	 	  li_recBuflen;
	char		 *lpc_recBuf ;
	char		 *lpc_Token ;
	char		 *lpc_trInfoMem[MYAPP_RECV_COLCNT] ;
	int		  li_headCnt ;
	int	 	  li_rackCnt ;
	int		  li_retryCnt ;
	char		  lc_fileName[1024] ;
	char		  lc_fileNameBuf[1024] ;
	char		 *pToken ;
	struct stat	  lst_statBuf ;

	/***
	 ***	ファイル属性チェック
	 ***/
	//	ファイル名作成
	sprintf ( lc_fileName, "%s/%s", pAppEnv->cDirNR_Col, pc_trFileName ) ;
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
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "ファイル名 %s", lc_fileName ) ;
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
			if ( li_retryCnt == pAppEnv->fileRetry ) {
				//	異常終了	LOG
				gintErrorCode = MYAPP_STSCODE_ERR_TR_FILE ;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncTrFileRead", __LINE__,
		 	 		 	EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		 	 	 		"ファイルの読み込みに失敗しました[%s]", lc_fileName ) ;
				return ( -1 ) ;
			}
			continue ;
		}
		break ;
	}
	
	//	構造体設定
	li_headCnt = 0 ;
	li_rackCnt = 0 ;
	memset ( pst_trInfo, '\0', sizeof ( struct trInfo ) ) ;
	//	読み込み
	while ( fgets ( lc_recBuf, sizeof ( lc_recBuf ), lfp ) != NULL ) {
		//	改行コード置換
		li_recBuflen = strlen ( lc_recBuf ) ;
		if ( lc_recBuf[li_recBuflen-2] == '\r' ) {
			lc_recBuf[li_recBuflen-2] = '\0' ;
		}
		if ( lc_recBuf[li_recBuflen-1] == '\n' ) { 
			lc_recBuf[li_recBuflen-1] = '\0' ;
		}

		sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "ファイル名 %s, レコード %s", lc_fileName, lc_recBuf) ;

		if ( li_headCnt == 0 ) {
			//検査開始日
			strncpy ( pst_trInfo->knskisymd, lc_recBuf, 8 ) ;
			sFncTrim ( pst_trInfo->knskisymd ) ;
			//トレーＮＯ
			strncpy ( pst_trInfo->trid, &lc_recBuf[8], 8 ) ;
			sFncTrim ( pst_trInfo->trid ) ;
			li_headCnt++;
		}
		else {
			strncpy ( pst_trInfo->asyrckid[li_rackCnt], &lc_recBuf[11], 5 ) ;
			sFncTrim ( pst_trInfo->asyrckid[li_rackCnt] ) ;
			li_rackCnt++ ;
		}
		if( li_rackCnt >= 20 ){
			break;
		}
	}

	//	ファイルクローズ	
	fclose ( lfp ) ;

	/***
	 ***    ストッカーＮＯ(今回は情報がないため固定とする)
	 ***/
        memcpy ( pst_trInfo->stkno, "11", sizeof ( pst_trInfo->stkno ) - 1 ) ;

	return ( 0 ) ;
}
/******************************************************************************/
/*  関 数 名　：sFncTrim()  			 				*/
/*  機能概要　：文字列前後のスペースを削除する				  	*/
/*  入　　力　：                                                              */
/*　 第１引数 ：char *   	編集文字列					*/
/*  出　　力　：                                                              */
/*  復帰情報　：無し								*/
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
/*  機能概要　：ファイルを移動する						*/
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
	int		*shmData ;

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
/*  関 数 名　：sFncFileFillter()			 			*/
/*  機能概要　：ファイルフィルター【コールバック関数】		  	 	*/
/*  入　　力　：                                                              */
/*　 第１引数 ：struct dirent *   	ディレクトリ構造体			*/
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

/******************************************************************************/
/*  関 数 名　：main()								*/
/*  機能概要　：メイン関数							*/
/*  入　　力　：                                                              */
/*　 第１引数 ：char *pcLogName    【任意】ログファイル名を指定する。		*/
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
