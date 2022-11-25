/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：LD101.c                                                      */
/* 　概　　　要：                                                             */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2019/12/15     BML.inc        新規作成                           */
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
#include "bml_DBCom.h"

#include "sql.h"

#include "LD101.h"

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
struct stcLogMember	 gstLogMem ;		//	ログ出力情報

/******************************************************************************/
/* 関数宣言                                                                   */
/******************************************************************************/
//	ファイル・データベース出力関数
static	int 	sFncGetFileName ( char * ) ;
static	int 	sFncOutHKHRIRAI ( FILE *, my_stCHKZOK ) ;

//      共有メモリ操作関数
static	int	sFncShmCrt() ;
static	int	sFncShmGet( int *) ;
static	int	sFncShmDel() ;


//	その他
int	ChkErrZok( my_stCHKZOK * ) ;
int	isCorrectChar( char * ) ;
void	sFncTrim( char *, char * );
static void	sFncGetdate( char *, char *, int ) ;
static void	endFunction();


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
initFunction( argc, argv )
int	 argc ;
char	*argv[] ;
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

	/*	ログオープン */
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

	//	開始ログ出力
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "プログラム起動" ) ;

	/*	初期化	*/

	//	プログラム環境変数初期化
	memset ( &pAppEnv , '\0', sizeof( pAppEnv ) ) ;

	//	パラメータファイル名退避
	pAppEnv.pcFielNamePRM = argv[1] ;

	//	パラメータファイルオープン	
	pAppEnv.bp = ZbmlPrmOpen ( pAppEnv.pcFielNamePRM ) ;		
	if ( pAppEnv.bp == NULL ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmOpen", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータファイルのオープンに失敗しました[%s]", pAppEnv.pcFielNamePRM ) ;
		return ( -1 ) ;
	}
	//	共有メモリキー取得
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_SHM_KEY, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_SHM_KEY ) ;
		return ( -1 ) ;
	}
	pAppEnv.shm_Key = atoi ( lc_prmBuf ) ;
	//	データベース名
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DB_NAME, pAppEnv.cDb_Name ) != 0 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_DB_NAME ) ;
		return ( -1 ) ;
	}
	//	データベースユーザ
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DB_USER, pAppEnv.cDb_User ) != 0 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_DB_USER ) ;
		return ( -1 ) ;
	}
	//	データベースパスワード
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DB_PASSWD, pAppEnv.cDb_Passwd ) != 0 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_DB_PASSWD ) ;
		return ( -1 ) ;
	}
	//	ファイル出力ディレクトリ
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_OUTPUT_DIR, pAppEnv.cOutputDir ) != 0 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_OUTPUT_DIR ) ;
		return ( -1 ) ;
	}
	//	出力ファイル名
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_OUTPUT_FILE, pAppEnv.cOutputFile ) != 0 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_OUTPUT_FILE ) ;
		return ( -1 ) ;
	}
	//	ＦＴＰ送信用シェル名
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_SEND_SHELL, pAppEnv.cSendShell ) != 0 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_SEND_SHELL ) ;
		return ( -1 ) ;
	}
	//	スタートトリガーファイル
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_TRG_FILE, pAppEnv.cTrgFile ) != 0 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_TRG_FILE ) ;
		return ( -1 ) ;
	}
	//	年齢警告上限取得
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_AGE_HI, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_AGE_HI ) ;
		return ( -1 ) ;
	}
	pAppEnv.AgeHi= atoi ( lc_prmBuf ) ;
	//	年齢警告下限取得
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_AGE_LOW, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_AGE_LOW ) ;
		return ( -1 ) ;
	}
	pAppEnv.AgeLow= atoi ( lc_prmBuf ) ;
	//	身長警告上限取得
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_SC_HI, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_SC_HI ) ;
		return ( -1 ) ;
	}
	pAppEnv.ScHi= atof ( lc_prmBuf ) ;
	//	身長警告下限取得
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_SC_LOW, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_SC_LOW ) ;
		return ( -1 ) ;
	}
	pAppEnv.ScLow= atof ( lc_prmBuf ) ;
	//	体重警告上限取得
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_TJ_HI, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_TJ_HI ) ;
		return ( -1 ) ;
	}
	pAppEnv.TjHi= atof ( lc_prmBuf ) ;
	//	体重警告下限取得
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_TJ_LOW, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_TJ_LOW ) ;
		return ( -1 ) ;
	}
	pAppEnv.TjLow= atof ( lc_prmBuf ) ;
	//	SLEEPSEC取得
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_SLEEP_SEC, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_SLEEP_SEC ) ;
		return ( -1 ) ;
	}
	pAppEnv.sleep_Sec= atoi ( lc_prmBuf ) ;
	//	検索日付の取得
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DATE_RANGE, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_DATE_RANGE ) ;
		return ( -1 ) ;
	}
	pAppEnv.DateRange= atoi ( lc_prmBuf ) ;

	//	パラメータファイルクローズ	
	ZbmlPrmClose ( pAppEnv.bp ) ;

	/***
	 ***	共有メモリ生成	
	 ***/
	if ( sFncShmCrt ( ) < 0 ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "共有メモリエラー") ;
		return ( -1 ) ;
	}

	/***
	 ***	データベースオープン
	 ***/
	ll_retSts = ZdbConnect( pAppEnv.cDb_Name, pAppEnv.cDb_User, pAppEnv.cDb_Passwd ) ;
	if ( ll_retSts != 0 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZdbConnect", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "データベースオープンに失敗しました[DB=%s USER=%s PASS=%s]", pAppEnv.cDb_Name, pAppEnv.cDb_User, pAppEnv.cDb_Passwd ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ; 
}
/********************************************************************************/
/*  関 数 名　：mainFunction()							*/
/*  機能概要　：メイン処理関数							*/
/*  入　　力　：								*/
/*　 第１引数 ：struct	env *   	プログラム環境構造体。			*/
/*  出　　力　：								*/
/*  復帰情報　：  0     : 成功							*/
/* 　　　　　　　-1     : 失敗							*/
/********************************************************************************/
int
mainFunction()
{
	int	 li_stopFlg = 0;

	int	 i = 0;
	int	 chk_cnt = 0;
	int	 chk_err = 0;
	char	 serch_date[11];
	FILE	*lfp ;
	char	 sFileName[MYAPP_PATH_SIZE] ;
	char	cmd[MYAPP_PATH_SIZE];

	struct stat st;

	my_stSYSKNR pSysKnr; 	//
	my_stCHKZOK *pChkZok;	// 属性チェック情報

	/***
	 ***		永久ループ
	 ***		停止コマンドで終了
	 ***/
	while ( 1 ) {
		/* スリープ */
		sleep ( pAppEnv.sleep_Sec ) ;

		/* 停止コマンド確認 */
		if ( sFncShmGet ( &li_stopFlg ) != 0 ) {
			return( RTN_NG );
		}
		if ( li_stopFlg == 1 ) {
			return( RTN_OK );
		}
		/* LD103 がトリガーファイルを作成するまで待機 */
		if ( stat( pAppEnv.cTrgFile, &st ) != 0 ){
			continue ;
		}
		/* システム管理マスタ取得 */
		if ( sFncSelSysKnr( &pSysKnr ) !=  RTN_OK ){
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
	 		 		"システム管理情報の取得に失敗しました");
			return( RTN_NG );
		}

		chk_cnt = 0;
		chk_err = 0;
		pChkZok = NULL;
		lfp = NULL ;

		sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "処理を開始しました。" ) ;
		/* 検索範囲を取得 */
		sFncGetdate( serch_date, pSysKnr.kjnsriymd, pAppEnv.DateRange );
		/* ファイル名取得 */
		if (sFncGetFileName ( sFileName ) != RTN_OK ) {
			return ( RTN_NG ) ;
		}
		/* 対象件数に関わらず、ファイルは作成する */
		lfp = fopen ( sFileName , "w" ) ;
		if ( lfp == NULL ) {
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "fopen", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
	 		 		"ファイルのオープンに失敗しました[%s]", sFileName);
			return ( RTN_NG ) ;
		}

		sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "送信用ファイルをオープンしました。[%s]", sFileName ) ;

		/* 属性エラーチェック用情報取得処理 */
		if( sFncSelChkZok( serch_date, &pChkZok, &chk_cnt ) !=  RTN_OK ){
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
	 		 		"データ取得に失敗しました");
			if ( lfp != NULL ) {
				fclose ( lfp ) ;
			}
			if ( pChkZok!= NULL ) {
				ZbmlFree( pChkZok );
			}
			return( RTN_NG );
		}

		sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "属性情報の取得を完了。属性チェック処理開始。" ) ;

		for ( i = 0; i < chk_cnt; i++ ){
			/* 属性エラーチェック */
			if( ChkErrZok( &pChkZok[i] ) != RTN_OK ){
				/* ＤＢ更新 */
				if ( InsHkHrIrai( &pChkZok[i] ) != RTN_OK ){
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
	 		 			     "ＤＢ更新に失敗しました[%s:%d件目]", sFileName, i);
					if ( lfp != NULL ) {
						fclose ( lfp ) ;
					}
					if ( pChkZok!= NULL ) {
						ZbmlFree( pChkZok );
					}
					return( RTN_NG );
				}
			
					/* ファイルレコード出力 */
				if ( sFncOutHKHRIRAI ( lfp, pChkZok[i] ) != RTN_OK ){
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
	 		 			     "ファイル出力に失敗しました[%s:%d件目]", sFileName, i);
					if ( lfp != NULL ) {
						fclose ( lfp ) ;
					}
					if ( pChkZok!= NULL ) {
						ZbmlFree( pChkZok );
					}
					return( RTN_NG );
				}
				chk_err++;
			}
		}

		sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "属性チェック処理完了。[総数：%d件,エラー件数：%d件]", chk_cnt, chk_err ) ;

		if ( lfp != NULL ) {
			fclose ( lfp ) ;
		}
		if ( pChkZok!= NULL ) {
			ZbmlFree( pChkZok );
		}
		break;
	}

	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                             "FTP コマンドを開始します。");

	// FTPコマンド用シェルの実行
	sprintf( cmd, "sh %s", pAppEnv.cSendShell );
	system( cmd );

	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                             "FTP コマンドを終了しました。");

	return ( RTN_OK ) ;
}
/******************************************************************************/
/*  関 数 名  ：ChkErrZok							*/
/*  機能概要  ：属性エラーチェック関数						*/
/*  入    力  ：								*/
/*   第１引数 ：struct my_stCHKZOK  *pChkZok    : 属性チェック情報		*/
/*  出    力  ：なし								*/
/*  復帰情報  ：INT								*/
/*		RTN_OK     : 成功						*/
/*		RTN_NG     : 失敗						*/
/******************************************************************************/
int	ChkErrZok( pChkZok )
my_stCHKZOK	*pChkZok ;
{
	
	int	ret = RTN_OK;
	double	tmpNumDbl = 0.0;
	int	tmpNumInt = 0;

	if( strcmp( pChkZok->scflg, MYAPP_ZOK_CHK ) == 0 ){
		if( isCorrectChar( pChkZok->sc ) != RTN_OK || !strcmp(pChkZok->sc, "     ") ) {
			strcpy( pChkZok->scflg, MYAPP_ZOK_ERR );
			ret = RTN_NG;
		} else {
			tmpNumDbl = atof( pChkZok->sc );
			if( tmpNumDbl > pAppEnv.ScHi || tmpNumDbl < pAppEnv.ScLow ) {
				strcpy( pChkZok->scflg, MYAPP_ZOK_NG );
				ret = RTN_NG;
			}
		}
	}

	if( strcmp( pChkZok->tjflg, MYAPP_ZOK_CHK ) == 0 ){
		if( isCorrectChar( pChkZok->tj ) != RTN_OK || !strcmp(pChkZok->tj, "     ") ) {
			strcpy( pChkZok->tjflg, MYAPP_ZOK_ERR );
			ret = RTN_NG;
		} else {
			tmpNumDbl = atof( pChkZok->tj );
			if ( tmpNumDbl > pAppEnv.TjHi || tmpNumDbl < pAppEnv.TjLow ) {
				strcpy( pChkZok->tjflg, MYAPP_ZOK_NG );
				ret = RTN_NG;
			}
		}
	}

	if( strcmp( pChkZok->tjtniflg, MYAPP_ZOK_CHK ) == 0 ){
		if( strcmp( pChkZok->tjtni, "0" ) != 0 ) {
			strcpy( pChkZok->tjtniflg, MYAPP_ZOK_NG );
			ret = RTN_NG;
		}
	}

	if( strcmp( pChkZok->sbtkbnflg, MYAPP_ZOK_CHK ) == 0 ){
		if( strcmp( pChkZok->sbtkbn, "0" ) != 0 && strcmp( pChkZok->sbtkbn , "1" ) != 0 ) {
			strcpy(pChkZok->sbtkbnflg, MYAPP_ZOK_ERR );
			ret = RTN_NG;
		}
	}

	if( strcmp( pChkZok->ageflg, MYAPP_ZOK_CHK ) == 0 ){
		if( isCorrectChar( pChkZok->age ) != RTN_OK || !strcmp( pChkZok->age , "   ") ) {
			strcpy( pChkZok->ageflg, MYAPP_ZOK_ERR );
			ret = RTN_NG;
		} else {
			tmpNumInt = atoi( pChkZok->age );
			if( tmpNumInt > pAppEnv.AgeHi || tmpNumInt < pAppEnv.AgeLow ) {
				strcpy( pChkZok->ageflg, MYAPP_ZOK_NG );
				ret = RTN_NG;
			}
		}
	}

	if( strcmp( pChkZok->agekbnflg, MYAPP_ZOK_CHK ) == 0 ){
		if( strcmp( pChkZok->agekbn , "Y" ) != 0 ){
			strcpy(pChkZok->agekbnflg, MYAPP_ZOK_NG );
			ret=RTN_NG;
		}
	}
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "ChkErrZok", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "utkymd[%s] irino[%s] kmkcd[%s] sc[%s] tj[%s] tjtni[%s] sbtkbn[%s] age[%s] agekbn[%s] ret[%d]", 
			pChkZok->utkymd, pChkZok->irino, pChkZok->kmkcd, pChkZok->sc, pChkZok->tj, pChkZok->tjtni, pChkZok->sbtkbn, pChkZok->age, pChkZok->agekbn, ret ) ;
	return(ret);
}

/**************************************************************************/
/*      関 数 名  ：isCorrectChar                                         */
/*      機能概要  ：患者属性数値エリアチェック                            */
/*      入        力  ：                                                  */
/*       第１引数 ： char       In[];   : チェック文字列                  */
/*      出        力  ：                                                  */
/*      復帰情報  ： RTN_OK             : 正常終了                        */
/*                               以外   : 失敗                            */
/**************************************************************************/
int isCorrectChar(char *In)
{
	int	ret = RTN_OK;

	int	i = 0;
	int	nSuziFlg =0; /*初めが数字かとうか検索 */

	/* 初期処理     */
	int nMaxNum = strlen(In);
	char    buf[nMaxNum + 1];
	memset( buf,    '\0', sizeof( buf ));

	sFncTrim( buf, In );
	nMaxNum = strlen(buf);

	for( i = 0 ; i < nMaxNum ; i++ ) {
		if(In[i] == ' '){
			if(nSuziFlg == 1){
				// DEBUG
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "数値 数字中にSPACE[%s]", In );
				// ERROR
				ret=RTN_NG;
				break;
			}
		}
		else if(In[i] == '.'){
			if(i==0){
				// DEBUG
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "数値 先頭.不可[%s]", In );
				// ERROR
				ret=RTN_NG;
				break;
			}
			if(nSuziFlg == 0){
				// DEBUG
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "数値 先頭.不可[%s]" , In );
				// ERROR
				ret=RTN_NG;
				break;
			}
		}
		else if(In[i] >= '0' && In[i] <= '9'){
			nSuziFlg = 1;
		}
		else{
			// DEBUG
			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "数値 空白.以外不可[%s]" , In );
			// ERROR
			ret=RTN_NG;
			break;
		}
	}

	if(i == nMaxNum){
		ret=RTN_OK;
	}

	return( ret );
}


/********************************************************************************/
/*  関 数 名　：sFncFileOut()				 			*/
/*  機能概要　：チェック情報ファイル出力		 			*/
/*  入　　力　：                                                                */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体			*/
/*　 第２引数 ：Kenorder  *   		検査オーダー情報環境構造体		*/
/*  出　　力　：                                                                */
/*  復帰情報　：int								*/
/*		 0	正常							*/
/*		-1	異常							*/
/********************************************************************************/
static int
sFncGetFileName ( sFileName )
char	*sFileName ;
{
	/* 同名ファイルリネーム用 */
	char	lc_FileName[MYAPP_PATH_SIZE] ;
	struct	stat st;

	/*	ファイル名作成	*/
	sprintf ( sFileName, "%s/%s", pAppEnv.cOutputDir, pAppEnv.cOutputFile );

	/* 同名ファイルがある場合はリネームしておく */
	if ( stat( sFileName, &st ) == 0 ){
		sprintf ( lc_FileName, "%s", sFileName );
		for( ;; ){
			strcat( lc_FileName, "_" );
			if( open( lc_FileName, O_RDONLY, 0 ) == EOF ){
				break;
			}
		}
		rename( sFileName, lc_FileName );
	}

	return ( 0 ) ;
}
/******************************************************************************/
/*  関 数 名　：sFncOutHKHRIRAI()		 				*/
/*  機能概要　属性チェックエラー情報レコード生成				*/
/*  入　　力　：                                                              */
/*　 第２引数 ：struct my_stCHKZOK *   	検査オーダ情報構造体			*/
/*  出　　力　：                                                              */
/*　 第１引数 ：char 	*  	レコード格納バッファ				*/
/*  復帰情報　：無し								*/
/******************************************************************************/
static	int
sFncOutHKHRIRAI ( pfp, precChkZok )
FILE	*pfp ;
my_stCHKZOK	precChkZok ;
{
	int	retSts ;
	char	ngKbn[6+1];
	char	cnv_utkymd[10+1];
	char	cnv_irino[8+1];
	char	cnv_sbt[2+1];
	char	cnv_age[3+1];
	char	cnv_agekbn[4+1];
	char	cnv_sc[5+1];
	char	cnv_tj[5+1];
	char	cnv_tjtni[2+1];
	char	sbtchk, agechk, scchk, tjchk;

	// ＮＧ区分初期化
	sprintf( ngKbn, "%s%s%s", MYAPP_SPACE_FULL, MYAPP_SPACE_FULL, MYAPP_SPACE_FULL );

	sprintf( cnv_utkymd, "%.4s/%.2s/%.2s" , precChkZok.utkymd, &precChkZok.utkymd[5], &precChkZok.utkymd[8] );
	sprintf( cnv_irino, "%-3.3s-%-4.4s" , &precChkZok.irino[2], &precChkZok.irino[5] );

	// 性別
	if(strcmp( precChkZok.sbtkbnflg, MYAPP_ZOK_NOT_CHK ) == 0 ){
		sprintf( cnv_sbt, "%s", MYAPP_HYPHEN_FULL );
		sbtchk = MYAPP_SPACE_HALF;
	} else {
		// 性別区分 -> 性別区分名称
		if(strcmp(precChkZok.sbtkbn ,MYAPP_SBTKBN_MALE) == 0 ){ 
			sprintf( cnv_sbt, "%s", MYAPP_MARK_MALE );
		} else if(strcmp(precChkZok.sbtkbn ,MYAPP_SBTKBN_FEMALE) == 0 ){
			sprintf( cnv_sbt, "%s", MYAPP_MARK_FEMALE );
		} else {
			sprintf( cnv_sbt, "%s", MYAPP_SPACE_FULL );
		} 
		// 性別区分入力チェック
		if(strcmp(precChkZok.sbtkbnflg ,MYAPP_ZOK_NG) == 0 ){ 
			sbtchk = MYAPP_MARK_NG;
			sprintf( ngKbn, "%s", MYAPP_MARK_KBN_NG );
		} else if(strcmp(precChkZok.sbtkbnflg ,MYAPP_ZOK_ERR) == 0 ){ 
			sbtchk = MYAPP_MARK_ERR;
			sprintf( ngKbn, "%s", MYAPP_MARK_KBN_ERR );
		} else { 
			sbtchk = MYAPP_SPACE_HALF;
		}
	}
	// 年齢＋年齢区分
	if((strcmp( precChkZok.ageflg, MYAPP_ZOK_NOT_CHK ) == 0 ) && ( strcmp( precChkZok.agekbnflg, MYAPP_ZOK_NOT_CHK ) == 0 )){
		sprintf( cnv_age, "%c  ", MYAPP_HYPHEN_HALF );
		sprintf( cnv_agekbn, "%s%s", MYAPP_SPACE_FULL, MYAPP_SPACE_FULL );
		agechk = MYAPP_SPACE_HALF;
	} else {
		// 年齢
		sprintf( cnv_age, "%-3.3s", precChkZok.age );
		// 年齢区分
		if(strcmp(precChkZok.agekbn ,MYAPP_AGEKBN_YEAR) == 0 ){ 
			sprintf( cnv_agekbn, "%-4.4s", MYAPP_MARK_YEAR );
		} else if(strcmp(precChkZok.agekbn ,MYAPP_AGEKBN_MONTH) == 0 ){ 
			sprintf( cnv_agekbn, "%-4.4s", MYAPP_MARK_MONTH );
		} else if(strcmp(precChkZok.agekbn ,MYAPP_AGEKBN_WEEK) == 0 ){ 
			sprintf( cnv_agekbn, "%-4.4s", MYAPP_MARK_WEEK );
		} else if(strcmp(precChkZok.agekbn ,MYAPP_AGEKBN_DAY) == 0 ){ 
			sprintf( cnv_agekbn, "%-4.4s", MYAPP_MARK_DAY );
		} else { 
			sprintf( cnv_agekbn, "%s%s", MYAPP_SPACE_FULL, MYAPP_SPACE_FULL );
		}
		// 年齢入力チェック
		if((strcmp( precChkZok.ageflg, MYAPP_ZOK_NG ) == 0 ) || ( strcmp( precChkZok.agekbnflg, MYAPP_ZOK_NG ) == 0 )){
			agechk = MYAPP_MARK_NG;
			sprintf( ngKbn, "%s", MYAPP_MARK_KBN_NG );
		} else if((strcmp( precChkZok.ageflg, MYAPP_ZOK_ERR ) == 0 ) || ( strcmp( precChkZok.agekbnflg, MYAPP_ZOK_ERR ) == 0 )){
			agechk = MYAPP_MARK_ERR ;
			if( strcmp( ngKbn, MYAPP_MARK_KBN_NG ) != 0 ) {
				/* 未入力と異常の場合、異常を優先 */
				sprintf( ngKbn, "%s", MYAPP_MARK_KBN_ERR );
			}
		} else {
			agechk = MYAPP_SPACE_HALF;
		}
	}
	// 身長
	if(strcmp( precChkZok.scflg, MYAPP_ZOK_NOT_CHK ) == 0 ){
		sprintf( cnv_sc, "%c    ", MYAPP_HYPHEN_HALF ) ;
		scchk = MYAPP_SPACE_HALF;
	} else {
		// 身長
		sprintf( cnv_sc, "%-5.5s", precChkZok.sc ) ;
		// 身長入力チェック
		if(strcmp( precChkZok.scflg, MYAPP_ZOK_NG ) == 0 ){
			scchk = MYAPP_MARK_NG;
			sprintf( ngKbn, "%s", MYAPP_MARK_KBN_NG );
		} else if(strcmp( precChkZok.scflg, MYAPP_ZOK_ERR ) == 0 ){
			scchk = MYAPP_MARK_ERR;
			if( strcmp( ngKbn, MYAPP_MARK_KBN_NG ) != 0 ) {
				sprintf( ngKbn, "%s", MYAPP_MARK_KBN_ERR );
			}
		} else {
			scchk = MYAPP_SPACE_HALF;
		}
	}
	// 体重
	if((strcmp( precChkZok.tjflg, MYAPP_ZOK_NOT_CHK ) == 0 ) && ( strcmp( precChkZok.tjtniflg, MYAPP_ZOK_NOT_CHK ) == 0 )){
		tjchk = MYAPP_SPACE_HALF;
		sprintf( cnv_tj, "%c  %c", MYAPP_HYPHEN_HALF, tjchk ) ;
	} else {
		// 体重
		sprintf( cnv_tj, "%-5.5s", precChkZok.tj) ;
		// 体重単位
		if(strcmp(precChkZok.tjtni ,MYAPP_TJTNI_KGRAM ) == 0 ){ 
			sprintf( cnv_tjtni, "%-2.2s", MYAPP_MARK_KGRAM ) ;
		} else if(strcmp(precChkZok.tjtni ,MYAPP_TJTNI_GRAM ) == 0 ){ 
			sprintf( cnv_tjtni, "%-2.2s", MYAPP_MARK_GRAM ) ;
		} else {
			sprintf( cnv_tjtni, "%c%c", MYAPP_SPACE_HALF, MYAPP_SPACE_HALF ) ;
		}
		// 体重入力チェック
		if((strcmp( precChkZok.tjflg, MYAPP_ZOK_NG ) == 0 ) || ( strcmp( precChkZok.tjtniflg, MYAPP_ZOK_NG ) == 0 )){
			tjchk = MYAPP_MARK_NG;
			sprintf( ngKbn, "%s", MYAPP_MARK_KBN_NG );
		} else if((strcmp( precChkZok.tjflg, MYAPP_ZOK_ERR ) == 0 ) || ( strcmp( precChkZok.tjtniflg, MYAPP_ZOK_ERR ) == 0 )){
			tjchk = MYAPP_MARK_ERR;
			if( strcmp( ngKbn, MYAPP_MARK_KBN_NG ) != 0 ) {
				sprintf( ngKbn, "%s", MYAPP_MARK_KBN_ERR );
			}
		} else {
			tjchk = MYAPP_SPACE_HALF;
		}
	}

	//	レコード作成
	retSts = fprintf ( pfp, "\"%s\",\"%-7s\",\"%-40s\",\"%-10s\",\"%-8s\",\"%-20.20s\",\"%-15.15s\",\"%-7.7s\",\"%-24.24s\",\"%-2.2s\",\"%c\",\"%-3.3s\",\"%-4.4s\",\"%c\",\"%-5.5s\",\"%c\",\"%-5.5s\",\"%-2.2s\",\"%c\"\r\n",
				ngKbn,	
				precChkZok.sstcd,
				precChkZok.sstssnmj,
				cnv_utkymd,
				cnv_irino,
				precChkZok.knjnmn,
				precChkZok.krtno,
				precChkZok.kmkcd,
				precChkZok.kmknmj,
				cnv_sbt,
				sbtchk,
				cnv_age,
				cnv_agekbn,
				agechk,
				cnv_sc,
				scchk,
				cnv_tj,
				cnv_tjtni,
				tjchk ) ;
	if ( retSts < 0 ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOutHKHRIRAI", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "fprintf 失敗" ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*  関 数 名　：sFncGetdate()							*/
/*  機能概要　：日付演算関数							*/
/*  入　　力　：                                                              */
/*　 第２引数 ：char *	基準日付文字列( yyyy-mm-dd )				*/
/*　 第３引数 ：int	差分日数(普通に指定すると何日後。－指定で何日前となる)	*/
/*  出　　力　：      	                                                      */
/*　 第１引数 ：char *	取得日付文字列( yyyy-mm-dd )				*/
/******************************************************************************/
void sFncGetdate( newdate, date, days )
char *newdate ;
char *date ;
int days ;
{
	int y, m, d;

	sscanf(date, "%d-%d-%d", &y, &m, &d);
	struct tm tm = { 0, 0, 0, d, m-1, y-1900 }; 
	time_t time = mktime(&tm) + 86400 * days;
	struct tm *ltime = localtime(&time);

	sprintf(newdate, "%d-%02d-%02d", ltime->tm_year+1900, ltime->tm_mon+1, ltime->tm_mday);
}

/********************************************************************************/
/*  関 数 名  ：sFncTrim                                                        */
/*  機能概要  ：指定文字列の前後のスペースを取り除いて文字列をコピーする        */
/*  入    力  ：                                                                */
/*   第２引数 ：char * 変換元文字列                                             */
/*  出    力  ：                                                                */
/*   第１引数 ：char * 変換後文字列                                             */
/********************************************************************************/
void sFncTrim(char * dst, char *src) {
	int dstCnt;
	int srcCnt;
	int Flg;

	for(dstCnt = 0, srcCnt = 0, Flg = 0; src[srcCnt] != '\0'; srcCnt ++) {
		if ((dstCnt == 0) && (src[srcCnt] == '\x20')) {
			continue;
		}
		dst[dstCnt++] = src[srcCnt];
		if (src[srcCnt] != '\x20') {
			Flg = dstCnt;
		}
	}
	dst[Flg] = '\0';
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
endFunction()
{
	/*	データベースクローズ */
	ZdbDisConnect() ;

	/*	共有メモリ削除	*/
	sFncShmDel() ;

	/*	終了ログ出力 */
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "プログラム終了" ) ;
	/*	ログクローズ */
	ZbmlCloseLog() ;
	
	return ;
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
/********************************************************************************/
/*  関 数 名　：sFncShmCrt()							*/
/*  機能概要　：共有メモリ生成							*/
/*  入　　力　：                                                                */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体			*/
/*  出　　力　：                                                                */
/*  復帰情報　：int								*/
/*		 0	正常							*/
/*		-1	異常							*/
/********************************************************************************/
static int
sFncShmCrt()
{
	int		*shmData ;

	//	取得
	pAppEnv.shm_Id = shmget ( (key_t)pAppEnv.shm_Key, 
							MYAPP_SHM_SIZE, 
							0666 | IPC_CREAT ) ;
	if ( pAppEnv.shm_Id < 0 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmget", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}

	//	アタッチ	
	shmData = ( int * ) shmat ( pAppEnv.shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	異常終了	LOG
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
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/********************************************************************************/
/*  関 数 名　：sFncShmGet()							*/
/*  機能概要　：共有メモリ取得							*/
/*  入　　力　：                                                                */
/*　 第１引数 ：struct appEnv *	プログラム環境構造体	 			*/
/*　 第２引数 ：int *   	値						*/
/*  出　　力　：                                                                */
/*  復帰情報　：int								*/
/*		 0	正常							*/
/*		-1	異常							*/
/********************************************************************************/
static int
sFncShmGet ( pshmData )
int					*pshmData ;
{
	int		*shmData ;

	//	アタッチ	
	shmData = ( int * ) shmat ( pAppEnv.shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	異常終了	LOG
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
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/********************************************************************************/
/*  関 数 名　：sFncShmDel()							*/
/*  機能概要　：共有メモリ削除							*/
/*  入　　力　：                                                                */
/*　 第１引数 ：struct appEnv *	プログラム環境構造体。		 		*/
/*  出　　力　：                                                                */
/*  復帰情報　：int								*/
/*		 0	正常							*/
/*		-1	異常							*/
/********************************************************************************/
static int
sFncShmDel()
{
	//	削除	
	if ( shmctl ( pAppEnv.shm_Id, IPC_RMID, NULL) < 0 ) {
		//	異常終了	LOG
		return ( -1 ) ;
	}
	return ( 0 ) ;
}	

/********************************************************************************/
/*  関 数 名　：main()								*/
/*  機能概要　：メイン関数							*/
/*  入　　力　：                                                                */
/*　 第１引数 ：char *pcLogName	【任意】ログファイル名を指定する。		*/
/*		※NULLを指定した場合はINIファイルよりログ情報を取得する		*/
/*  出　　力　：                                                                */
/*  復帰情報　：  0     : 成功							*/
/* 　　　　　　　-1     : 失敗							*/
/********************************************************************************/
int 
main( argc, argv )
int	 argc ;
char	*argv[] ;
{
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
	if ( initFunction ( argc, argv )  != 0 ) {
		endFunction() ;
		exit ( 9 ) ;
	}
	
	/***
	 ***	主処理	
	 ***/
	if ( mainFunction()  != 0 ) {
		endFunction() ;
		exit ( 9 ) ;
	}

	/***
	 ***	終了処理	
	 ***/
	endFunction() ;
	exit( 0 ) ;
}

/** End of File ***************************************************************/
