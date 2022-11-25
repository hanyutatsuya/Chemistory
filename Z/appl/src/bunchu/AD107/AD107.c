/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：AD107.c                                                      */
/* 　概　　　要：３ＩＤ情報受信                                               */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2008/02/27     moriya         新規作成                           */
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

#include "AD107.h"

/******************************************************************************/
/* Define定義                                                                 */
/******************************************************************************/
//	TRACE
#if defined ( _TRACE )
#define malloc(a)   _malloc(a, __FILE__, __LINE__)
#define free(p)     _free(p, __FILE__, __LINE__)
#endif

/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/
MYAPP_STSCODE			gintErrorCode ;
struct	stcLogMember	gstLogMem ;			/* ログ出力情報				*/
static	int				gintEnd ;			/* ＥＮＤ情報受信フラグ		*/
static	int				gintSeq ;			/* BUNPOS展開ファイルの連番	*/

/******************************************************************************/
/* 関数宣言                                                                   */
/******************************************************************************/
// BUNPOS情報展開関連関数
static	int		sFncGet3rdidMaxSeq ( char * ) ;
static	int		sFncFtpRecv ( struct appEnv * ) ;
static	int		sFncWCline ( char *, int *, int * ) ;
static	int		sFncSleepEx ( struct appEnv * ) ;
static	int		sFncPauseEx ( struct appEnv * ) ;
static	int		sFncMoveSkip ( struct appEnv * ) ;

// 共有メモリ操作関数
static	int		sFncShmCrt ( struct appEnv * ) ;
static	int		sFncShmGet ( struct appEnv * , int * ) ;
static	int		sFncShmDel ( struct appEnv * ) ;

//	コールバック関数
static	int		sFncFileFillter ( struct dirent * ) ;

// ログ関数
void			sFncPutLog ( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... ) ;

// その他
static	void	sFncTrim ( char * ) ;
static	int		sFncFileRename ( char *, char *, char *, char * ) ;


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

	/***              ***
	 ***    初期化    ***
	 ***              ***/
	//	エラーステータス変更
	gintErrorCode = 0 ;

	//	プログラム環境変数初期化
	memset ( pAppEnv , '\0', sizeof ( struct appEnv ) ) ;

	/***                                    ***
	 ***    ログオープン (AD107_LOG.ini)    ***
	 ***                                    ***/
	if ( ZbmlOpenLog ( MYAPP_LOGINIFILE ) != 0 ) {
		return ( -1 ) ;
	}
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "ログINIオープン[%s]", MYAPP_LOGINIFILE ) ;

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

	/***                    ***
	 ***    引数チェック    ***
	 ***                    ***/
	if ( argc != 2 ) {
		gintErrorCode = MYAPP_STSCODE_ERR_USEGE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "initFunction", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "コマンドパラメータに誤りがあります" ) ;
		return ( -1 ) ;
	}

	/***                                  ***
	 ***    パラメータファイル情報退避    ***
	 ***                                  ***/
	//	パラメータファイル名退避 (AD107.ini)
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "パラメータファイル(AD107.ini)[%s]", argv[1] ) ;
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

	/*** パラメータ値取得 ***/
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
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "pAppEnv->shm_Key[%d]", pAppEnv->shm_Key ) ;

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
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "pAppEnv->sleep_Sec[%d]", pAppEnv->sleep_Sec ) ;

	//	リモート側ホスト名取得
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_FTP_HOST, pAppEnv->cFtpHost ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_FTP_HOST ) ;
		return ( -1 ) ;
	}
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "pAppEnv->cFtpHost[%s]", pAppEnv->cFtpHost ) ;

	//	リモート側ログインユーザ取得
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_FTP_USER, pAppEnv->cFtpUser ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_FTP_USER ) ;
		return ( -1 ) ;
	}
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "pAppEnv->cFtpUser[%s]", pAppEnv->cFtpUser ) ;

	//	リモート側ログインパスワード取得
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_FTP_PSWD, pAppEnv->cFtpPswd ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_FTP_PSWD ) ;
		return ( -1 ) ;
	}
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "pAppEnv->cFtpPswd[%s]", pAppEnv->cFtpPswd ) ;

	//	リモート側受信元パス取得
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_R_PATH, pAppEnv->cR_Path ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_R_PATH ) ;
		return ( -1 ) ;
	}
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "pAppEnv->cR_Path[%s]", pAppEnv->cR_Path ) ;

	//	リモート側受信ファイル名取得
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_R_FILE, pAppEnv->cR_File ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_R_FILE ) ;
		return ( -1 ) ;
	}
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "pAppEnv->cR_File[%s]", pAppEnv->cR_File ) ;

	//	ローカル側受信先パス取得
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_L_PATH, pAppEnv->cL_Path ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_L_PATH ) ;
		return ( -1 ) ;
	}
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "pAppEnv->cL_Path[%s]", pAppEnv->cL_Path ) ;

	//	ローカル側展開用パス取得
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_I_PATH, pAppEnv->cI_Path ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_I_PATH ) ;
		return ( -1 ) ;
	}
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "pAppEnv->cI_Path[%s]", pAppEnv->cI_Path ) ;

	//	差分管理ディレクトリパス取得
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_M_PATH, pAppEnv->cM_Path ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_M_PATH ) ;
		return ( -1 ) ;
	}
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "pAppEnv->cM_Path[%s]", pAppEnv->cM_Path ) ;

	//	3ID情報展開(AD108)のスキップファイルパス取得
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_S_PATH, pAppEnv->cS_Path ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_S_PATH ) ;
		return ( -1 ) ;
	}
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "pAppEnv->cS_Path[%s]", pAppEnv->cS_Path ) ;

	//	FTP周期（単位：秒）取得
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_ITVAL, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_ITVAL ) ;
		return ( -1 ) ;
	}
	pAppEnv->iItval= atoi ( lc_prmBuf ) ;
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "pAppEnv->iItval[%d]", pAppEnv->iItval ) ;

	//	パラメータファイルクローズ	
	ZbmlPrmClose ( pAppEnv->bp ) ;

	/***                                            ***
	 ***    BUNPOS展開用ファイルの連番最大値取得    ***
	 ***                                            ***/
	gintSeq = 0 ;
	if ( sFncGet3rdidMaxSeq( pAppEnv->cM_Path ) != 0 )
	{
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "initFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "BUNPOS展開用ファイルの連番最大値が取得できませんでした[%s/%s]", pAppEnv->cM_Path, FNM_3RDID_NUM ) ;
		return( -1 );
	}

	/***                      ***
	 ***    共有メモリ生成    ***
	 ***                      ***/
	if ( sFncShmCrt ( pAppEnv ) < 0 ) {
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
	int			iStopFlg ;
	int			iRet ;
	char		cZenFile[128] ;
	char		cKonFile[128] ;

	/* END情報受信フラグ初期化 */
	gintEnd = 0 ;

	/* 前回ファイル(3rdid.bak)、今回ファイル(3rdid.dat)パス初期化 */
	memset( cZenFile, 0, sizeof(cZenFile) ) ;
	memset( cKonFile, 0, sizeof(cKonFile) ) ;
	/* 前回ファイル(3rdid.bak) */
	sprintf( cZenFile , "%s/%s" , pAppEnv->cM_Path , FNM_3RDID_BAK );
	/* 今回ファイル(3rdid.dat) */
	sprintf( cKonFile , "%s/%s" , pAppEnv->cM_Path , FNM_3RDID_DAT );

	/***                                  ***
	 ***    BUNPOSファイル情報展開処理    ***
	 ***        永久ループ                ***
	 ***        停止コマンドで終了        ***
	 ***                                  ***/
	while ( 1 ) {
		/* 前々回に受信したファイルは消去する */
		unlink( cZenFile );
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "mainFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "unlink( cZenFile:%s )", cZenFile ) ;

		/* ｆｔｐする前に最新の受信ファイルを前回受信ファイルとする */
		link( cKonFile, cZenFile );
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "mainFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "link( %s, %s )", cKonFile, cZenFile ) ;

		/* 3rdidファイル(A00_bunpos.dat)の受信＆差分出力(POS.data.XXXX) */
		sFncFtpRecv ( pAppEnv );

		/* 3ID情報展開(AD108)のスキップファイル移動 */
		sFncMoveSkip ( pAppEnv );

		/* ＥＮＤレコード受信まで繰り返す */
		if( gintEnd == 1 ){
			break;
		}

		/* FTP周期パラメータ値分、待機する */
		if ( sFncSleepEx ( pAppEnv ) != 0 ) {
			break;
		}

		/***                        ***
		 ***    停止コマンド確認    ***
		 ***                        ***/
		if ( sFncShmGet ( pAppEnv, &iStopFlg ) == 0 ) {
			if ( iStopFlg == 1 ) {
				break ;
			}
		}
	}

	/* ENDレコード受信 */
	if ( gintEnd == 1 ){
		sFncPutLog ( TRCKIND_OPT, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "ＥＮＤレコードの受信を確認 -> 待機に入る" ) ;
		sFncPauseEx ( pAppEnv ) ;
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

	/***                      ***
	 ***    共有メモリ削除    ***
	 ***                      ***/
	sFncShmDel ( pAppEnv ) ;

	/***                    ***
	 ***    ログクローズ    ***
	 ***                    ***/
	//	終了ログ出力
	sFncPutLog ( TRCKIND_OPT, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "プログラム終了" ) ;

	//	ログ閉じる
	ZbmlCloseLog();
	
	return ;
}

/******************************************************************************/
/*  関 数 名　：sFncGet3rdidMaxSeq()                                          */
/*  機能概要　：BUNPOS展開用ファイルの最大ＳＥＱ抽出                          */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *      ローカル側差分管理パス                            */
/*  出　　力　：                                                              */
/*  復帰情報　：  0     : 成功                                                */
/* 　　　　　　　-1     : 失敗                                                */
/******************************************************************************/
static int
sFncGet3rdidMaxSeq( pMpath )
char *pMpath ;
{
	char	cBuf[128] ;
	FILE	*pFp ;

	memset( cBuf, 0, sizeof(cBuf) ) ;
	sprintf( cBuf, "%s/%s", pMpath, FNM_3RDID_NUM );

	/* 3rdid.numファイル存在チェック */
	if( access( cBuf, 0 ) < 0 ){
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncGet3rdidMaxSeq", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "通番管理ファイルなし[%s]", cBuf ) ;
		return ( 0 );
	}

	/* 開く */
	pFp = fopen( cBuf, "r" ) ;
	if( pFp == NULL ){
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncGet3rdidMaxSeq", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "通番管理ファイルオープンエラー[%s]", cBuf ) ;
		return ( -1 );
	}

	/* 読み込む */
	memset( cBuf, 0, sizeof(cBuf) ) ;
	if( fgets( cBuf, sizeof(cBuf), pFp ) == NULL ) {
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncGet3rdidMaxSeq", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "通番管理ファイル内容なし" ) ;
	} else {
		/* 連番設定 */
		gintSeq = atoi( cBuf ) ;
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncGet3rdidMaxSeq", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "通番取得[%d]", gintSeq ) ;
	}

	/* 閉じる */
	fclose( pFp ) ;

	return ( 0 ) ;
}

/******************************************************************************/
/*  関 数 名　：sFncFtpRecv()                                                 */
/*  機能概要　：フロンティアより３ｒｄｉｄ情報ファイルを受信する              */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv * プログラム環境構造体                          */
/*  出　　力　：                                                              */
/*  復帰情報　：  0     : 成功                                                */
/* 　　　　　　　-1     : 失敗                                                */
/******************************************************************************/
static int
sFncFtpRecv( pAppEnv )
struct appEnv	*pAppEnv ;
{
	FILE    *pFp;
	FILE    *pFp_w;
	char	cLnkF[128];
	char	cRcvF[128];
	char	cTenF[128];
	char	cFPath[128];
	char	cCmdLine[128];
	char	cBuf[512];
	int		i;
	int     iRet;
	int		iWcRcv;
	int		iWcRcvSz;
	int		iWcBak;
	int		iWcBakSz;
	long	lOffset;

	/* 念のためFTP受信予定ファイル(A00_bunpos.dat)を削除しておく */
	memset( cRcvF, 0, sizeof(cRcvF) ) ;
	sprintf( cRcvF, "%s/%s", pAppEnv->cL_Path, pAppEnv->cR_File );
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "unlink( cRcvF:%s )", cRcvF ) ;
	unlink( cRcvF );

	/* FTPコマンドファイル(3rdid.ftp)パス */
	memset( cFPath, 0, sizeof(cFPath) ) ;
	sprintf( cFPath , "%s/%s" , pAppEnv->cM_Path , FNM_3RDID_CMD );
	/* FTPコマンドファイル(3rdid.ftp)作成 */
	pFp = fopen( cFPath, "w" );
	if( pFp == NULL ){
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "FTPコマンドファイルオープンエラー[%s]", cFPath ) ;
		return( -1 );
	}
	fprintf( pFp, "open %s\n", pAppEnv->cFtpHost );
	fprintf( pFp, "user %s %s\n", pAppEnv->cFtpUser, pAppEnv->cFtpPswd );
	fprintf( pFp, "cd %s\n", pAppEnv->cR_Path );
	fprintf( pFp, "lcd %s\n", pAppEnv->cL_Path );
/*	fprintf( pFp, "binary\n" ); */
	fprintf( pFp, "get %s\n", pAppEnv->cR_File );
	fprintf( pFp, "close\n" );
	fprintf( pFp, "quit\n" );

	if( ferror(pFp) ){
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "FTPコマンドが出力できません[%s]", cFPath ) ;
		return( -1 );
	}
	fclose( pFp );

	/* FTP受信 */
	memset( cCmdLine, 0, sizeof(cCmdLine) ) ;
	sprintf( cCmdLine, "lftp -f %s", cFPath );
/*	sprintf( cCmdLine, "ftp -n < %s", cFPath ); */
	system( cCmdLine );

	/* FTP受信ファイル存在確認 */
	if( access ( cRcvF, 0 ) != 0 ){
//		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//					 "FTP受信ファイルがありません[%s : %s]", pAppEnv->cFtpHost, cRcvF ) ;
		return( 100 );
	}

	/* 今回受信ファイルの行数取得 */
	iWcRcv = 0 ;
	iWcRcvSz = 0 ;
	iRet = sFncWCline( cRcvF, &iWcRcv, &iWcRcvSz );
	if( iRet != 0 ){
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "今回受信ファイルの行数取得失敗[%s]", cRcvF ) ;
		return( -1 );
	}

	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "今回受信ファイル[Line : %d] [Size : %d] [Path : %s]", iWcRcv, iWcRcvSz, cRcvF ) ;

	/* 前回受信ファイルパス */
	memset( cFPath, 0, sizeof(cFPath) ) ;
	sprintf( cFPath , "%s/%s" , pAppEnv->cM_Path , FNM_3RDID_BAK );
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "cFPath( %s )", cFPath ) ;

	/* 前回受信ファイルの行数取得 */
	iWcBak = 0 ;
	iWcBakSz = 0 ;
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "iWcBak( %d ) iWcBakSz( %d )", iWcBak, iWcBakSz ) ;
	if( access ( cFPath, 0 ) == 0 ){
		/* 前回受信ファイルあり */
		iRet = sFncWCline( cFPath, &iWcBak, &iWcBakSz );
		if( iRet != 0 ){
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 	 "前回受信ファイルの行数取得失敗[%s]", cFPath ) ;
			return( -1 );
		}
//		/* 前回受信ファイルの最終行が不完全かもなので */
//		if( iWcBak > 0 ){
//			iWcBak--;
//		}
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "前回受信ファイル[Line : %d] [Size : %d] [Path : %s]", iWcBak, iWcBakSz, cFPath ) ;
	}
	else{
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "前回受信ファイルなし" ) ;
	}

	if( iWcRcvSz == iWcBakSz ){
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "前回受信ファイルとの差分なし[iWcBakSz(%d) == iWcRcvSz(%d)]", iWcBakSz, iWcRcvSz ) ;
		return( 100 );
	}

	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "前回受信ファイルとの差分あり[iWcBakSz(%d) != iWcRcvSz(%d)]", iWcBakSz, iWcRcvSz ) ;

	/* 今回受信ファイル(A00_bunpos.dat)をオープン */
	pFp = fopen( cRcvF, "r" );
	if( pFp == NULL ){
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "今回受信ファイルオープンエラー[%s]", cRcvF ) ;
		return( -1 );
	}

	/* 既に前回展開していたらその分をスキップ */
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "iWcBak( %d )", iWcBak ) ;
	lOffset = (long)( iWcBak * RECLEN_3RDID );
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "lOffset( %ld )", lOffset ) ;
	iRet = fseek( pFp, lOffset, 0 );
	if( iRet < 0 ){
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "今回受信ファイルSEEKエラー[%s]", cRcvF ) ;
		fclose( pFp );
		return( -1 );
	}
	
	/* BUNPOS展開用TMPファイル(TMP.data.0000) */
	memset( cTenF, 0, sizeof(cTenF) ) ;
	sprintf( cTenF, "%s/%s.data.0000", pAppEnv->cI_Path, TMP_BUNPOS );
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "cTenF( %s )", cTenF ) ;
	pFp_w = fopen( cTenF, "w" );
	if( pFp_w == NULL ){
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "BUNPOS展開用TMPファイルオープンエラー[%s]", cTenF ) ;
		fclose( pFp );
		return( -1 );
	}

	/* 今回受信ファイルデータ読み込み */
	memset( cBuf, 0, sizeof(cBuf) );
	while( 1 ){
		/* 1行読み込み */
		if( fgets( cBuf, sizeof(cBuf), pFp ) == NULL ){
			break;
		}
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "cBuf( %s )", cBuf ) ;
		if( strlen( cBuf ) >= RECLEN_3RDID ){
			/* BUNPOS展開用TMPファイルに出力 */
			iRet = fputs( cBuf, pFp_w );
			if( iRet < 0 ){
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						 	 "BUNPOS展開用TMPファイル書込みエラー[%s]", cBuf ) ;
				fclose(pFp);
				fclose(pFp_w);
				return( -1 );
			}
			if( memcmp( cBuf, RECEND_3RDID, 3 ) == 0 ){
				gintEnd = 1;
			}
		}
	}
	fclose(pFp);
	fclose(pFp_w);

	/* 展開ファイル名を変更 */
	for( i=0 ; i<99 ; i++ ){
		gintSeq++;
		sprintf( cLnkF, "%s/%s.data.%4.4d", pAppEnv->cI_Path, SEND_BUNPOS, gintSeq );
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "link( %s, %s )", cTenF, cLnkF ) ;
		iRet = link( cTenF, cLnkF );
		if( iRet == 0 ){
			sFncPutLog ( TRCKIND_TRACE, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 	 "ファイル作成[%s]", cLnkF ) ;
			break;
		}
	}
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "unlink( %s )", cTenF ) ;
	unlink( cTenF );

	/* ファイルNo書き込み */
	sprintf( cBuf, "echo '%d' > %s/%s", gintSeq , pAppEnv->cM_Path , FNM_3RDID_NUM );
	system(cBuf);

	/* 今回受信ファイルパス */
	sprintf( cFPath , "%s/%s" , pAppEnv->cM_Path , FNM_3RDID_DAT );

	/* 最後に受信ファイル(A00_bunpos.dat)を今回受信ファイル(3rdid.dat)としてコピー */
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "unlink( %s )", cFPath ) ;
	unlink( cFPath );
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "link( %s, %s )", cRcvF, cFPath ) ;
	link( cRcvF, cFPath );

	return( 0 );
}

/******************************************************************************/
/*  関 数 名　：sFncWCline()                                                  */
/*  機能概要　：ファイル行数の取得                                            */
/*  入　　力　：                                                              */
/*　 第１引数 ：char * ファイルパス                                           */
/*　 第２引数 ：int  * ファイル行数                                           */
/*　 第３引数 ：int  * ファイルサイズ                                         */
/*  出　　力　：                                                              */
/*  復帰情報　：  0     : 成功                                                */
/* 　　　　　　　-1     : 失敗                                                */
/******************************************************************************/
static int
sFncWCline( pFilePath, piLine, piSize )
char *pFilePath ;
int  *piLine ;
int  *piSize ;
{
	int		iSw;
	int		iIdx;
	int		i;
	char	cCmd[256];
	char	cBuf[256];
	char	cSize[256];
	char	cLine[256];
	FILE	*pFp;

	/* ファイルの存在確認 */
	if( access( pFilePath, 0 ) < 0 ){
		return( -1 );
	}

	/* 行数とバイト数取得 */
	memset( cCmd, 0, sizeof(cCmd) );
	sprintf( cCmd, "wc -lc %s", pFilePath );
	pFp = popen( cCmd, "r" );
	if( pFp == NULL ){
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncWCline", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "受信ファイルのＷＣオープンできません[%s]", cCmd ) ;
		return( -1 );
	}
	memset( cBuf, 0, sizeof(cBuf) );
	if( fgets( cBuf, sizeof(cBuf), pFp ) == NULL ){
		if( ferror( pFp ) ){
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncWCline", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 	 "受信ファイルのＷＣエラー[%s]", cCmd ) ;
			pclose(pFp);
			return( -1 );
		}
	}
	pclose( pFp );

	memset( cLine, 0, sizeof(cLine) );
	memset( cSize, 0, sizeof(cSize) );

	for( iSw=0,iIdx=0,i=0 ; i<sizeof(cBuf) ; i++ ){
		if( iSw == 9 ){
			break;
		}
		if( cBuf[i] == 0 || cBuf[i] == '\n' ){
			break;
		}
		if( cBuf[i] == ' ' || cBuf[i] == '\t' ){
			if( iSw == 3 ){ iSw = 9; }
			if( iSw == 1 ){ iSw = 2; }
		}
		if( cBuf[i] >= '0' && cBuf[i] <= '9' ){
			if( iSw == 2 ){ iSw = 3; iIdx = 0; }
			if( iSw == 0 ){ iSw = 1; iIdx = 0; }
		}
		if( iSw == 1 ){
			cLine[iIdx] = cBuf[i];
			iIdx++;
		}
		if( iSw == 3 ){
			cSize[iIdx] = cBuf[i];
			iIdx++;
		}
	}
	*piLine = atoi( cLine );
	*piSize = atoi( cSize );

	return( 0 );
}

/******************************************************************************/
/*  関 数 名　：sFncSleepEx()                                                 */
/*  機能概要　：スリープ                                                      */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv * プログラム環境構造体                          */
/*  出　　力　：                                                              */
/*  復帰情報　：  0     : 正常                                                */
/*  　　　　　：  1     : 停止コマンド受信                                    */
/******************************************************************************/
static int
sFncSleepEx ( pAppEnv )
struct appEnv	*pAppEnv ;
{
	int		iStopFlg = 0 ;	/* 終了フラグ */
	time_t	sleepTm ;		/* スリープ時間 */
	
	/* スリープする時間取得 */
	sleepTm = time(NULL) + (time_t)pAppEnv->iItval ;
	
	while( time(NULL) < sleepTm )
	{
		/***                        ***
		 ***    停止コマンド確認    ***
		 ***                        ***/
		if ( sFncShmGet ( pAppEnv, &iStopFlg ) == 0 ) {
			if ( iStopFlg == 1 ) {
				break ;
			}
		}

		/* 1秒スリープ */
		sleep ( 1 );
	}

	return iStopFlg;
}

/******************************************************************************/
/*  関 数 名　：sFncPauseEx()                                                 */
/*  機能概要　：ポーズ                                                        */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv * プログラム環境構造体                          */
/*  出　　力　：                                                              */
/*  復帰情報　：  0     : 正常                                                */
/*  　　　　　：  1     : 停止コマンド受信                                    */
/******************************************************************************/
static int
sFncPauseEx ( pAppEnv )
struct appEnv	*pAppEnv ;
{
	int iStopFlg = 0;	/* 終了フラグ */
	int iSkipCnt = 0 ;	/* SKIPファイルMOVEのためのカウンタ */
	int sleepTm ;		/* スリープ時間 */
	
	/* スリープする時間取得 */
	sleepTm = pAppEnv->iItval ;

	for( ; ; )
	{
		if ( iSkipCnt == sleepTm )
		{
			/* 3ID情報展開(AD108)のSKIPファイル移動 */
			sFncMoveSkip ( pAppEnv );

			iSkipCnt = 0 ;
		}

		/***                        ***
		 ***    停止コマンド確認    ***
		 ***                        ***/
		if ( sFncShmGet ( pAppEnv, &iStopFlg ) == 0 ) {
			if ( iStopFlg == 1 ) {
				break ;
			}
		}

		iSkipCnt++ ;

		/* 1秒スリープ */
		sleep ( 1 );
	}

	return iStopFlg;
}

/******************************************************************************/
/*  関 数 名　：sFncMoveSkip()                                                */
/*  機能概要　：AD108でSKIPされたファイルをMOVEする                           */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv * プログラム環境構造体                          */
/*  出　　力　：                                                              */
/*  復帰情報　：  0     : 正常                                                */
/*  　　　　　： -1     : 異常                                                */
/******************************************************************************/
static int
sFncMoveSkip ( pAppEnv )
struct appEnv	*pAppEnv ;
{
	int				  li_fileCnt ;
	int				  li_idx ;
	struct dirent	**lpst_dirBuf ;

	// SKIP.～ファイルのみ検索
	if ( ( li_fileCnt = scandir ( pAppEnv->cS_Path, &lpst_dirBuf, (void*)sFncFileFillter, alphasort ) ) < 0 )
	{
		// 異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_DIR;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncMoveSkip", __LINE__,
			 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 "SKIPファイルの取得に失敗しました" ) ;
		return ( -1 ) ;
	}

	if( li_fileCnt ) {
		sFncPutLog ( TRCKIND_OPT, __FILE__, "sFncMoveSkip", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "SKIPファイル取得数[%d]", li_fileCnt) ;
	} else {
		return ( -1 ) ;
	}

	li_idx = 0 ;
	for ( li_idx = 0 ; li_idx < li_fileCnt ; li_idx ++ ) {
		// SKIPファイルをローカル側展開パスへ移動する
		sFncPutLog ( TRCKIND_OPT, __FILE__, "sFncMoveSkip", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "SKIPファイル移動[%s/%s -> %s/%s]",
					 pAppEnv->cS_Path, lpst_dirBuf[li_idx]->d_name,
					 pAppEnv->cI_Path, lpst_dirBuf[li_idx]->d_name ) ;

		sFncFileRename ( pAppEnv->cS_Path, lpst_dirBuf[li_idx]->d_name,
						 pAppEnv->cI_Path, lpst_dirBuf[li_idx]->d_name ) ;
		free ( lpst_dirBuf[li_idx] ) ;
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
		//識別チェック
		if ( memcmp ( pdirEnt->d_name, 
					  SKIP_BUNPOS, 
					  strlen ( SKIP_BUNPOS ) ) != 0 ) {
			return ( 0 ) ;
		}
//		//拡張子チェック
//		if ( memcmp ( &(pdirEnt->d_name[li_len-strlen(MYAPP_RECV_SFX)]), 
//					  MYAPP_RECV_SFX, 
//					  strlen ( MYAPP_RECV_SFX ) ) != 0 ) {
//			return ( 0 ) ;
//		}
		return ( 1 ) ;
}

/******************************************************************************/
/*  関 数 名　：sFncPutLog()                                                  */
/*  機能概要　：アプリケーションログ出力                                      */
/*  入　　力　：                                                              */
/*　 第１引数 ：LOG_TRCKIND トレース種別                                      */
/*　 第２引数 ：char *      ソース名                                          */
/*　 第３引数 ：char *      関数名                                            */
/*　 第４引数 ：int         ソース行数                                        */
/*　 第５引数 ：char *      実行フラグ                                        */
/*　 第６引数 ：char *      エラーコード                                      */
/*　 第７引数 ：char *      出力メッセージ                                    */
/*　 第ｎ引数 ：...                                                           */
/*  出　　力　：                                                              */
/*  復帰情報　：無し                                                          */
/******************************************************************************/
void
sFncPutLog ( LOG_TRCKIND peTrcKind, char * pcSrcName, char * pcFncName, int plLineNo, char * pcExeFlg, char * pcErrCode, char * pcfmt, ... )
{
	va_list	 ap ;
	char	 cMsg[1024] ;

	/***                      ***
	 ***    ログ初期値設定    ***
	 ***                      ***/
	gstLogMem.eTrcKind = peTrcKind ;
	strcpy ( gstLogMem.pcFncName, pcFncName ) ;
	strcpy ( gstLogMem.pcExeFlg,  pcExeFlg ) ;
	strcpy ( gstLogMem.pcErrCode, pcErrCode ) ;
	va_start ( ap, pcfmt ) ;
	vsprintf ( gstLogMem.pcMsg, pcfmt, ap ) ;
	va_end ( ap ) ;

	/***                ***
	 ***    ログ出力    ***
	 ***                ***/
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
 	 	 			 "ファイルの移動に失敗しました[%s -> %s]", lc_fromPath, lc_toPath ) ;
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
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncShmCrt", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}

	//	アタッチ	
	shmData = ( int * ) shmat ( pAppEnv->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncShmCrt", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}

	//	値設定	
	*shmData = 0 ;

	//	デタッチ	
	if ( shmdt ( shmData ) == -1 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncShmCrt", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
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
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncShmGet", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}

	//	値設定	
	*pshmData = *shmData ;

	//	デタッチ	
	if ( shmdt ( shmData ) == -1 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncShmGet", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
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
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncShmDel", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
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

	/***                            ***
	 ***    バックグラウンド実行    ***
	 ***                            ***/
	if ( daemon ( 0, 0 ) < 0 ) {
		exit ( 9 ) ;
	}


	/***                ***
	 ***    初期処理    ***
	 ***                ***/
	if ( initFunction ( argc, argv, &sAppEnv )  != 0 ) {
		endFunction ( &sAppEnv ) ;
		exit ( 9 ) ;
	}
	
	/***              ***
	 ***    主処理    ***
	 ***              ***/
	if ( mainFunction ( &sAppEnv )  != 0 ) {
		endFunction ( &sAppEnv ) ;
		exit ( 9 ) ;
	}

	/***                ***
	 ***    終了処理    ***
	 ***                ***/
	endFunction ( &sAppEnv ) ;
	exit(9);
}

/** End of File ***************************************************************/
