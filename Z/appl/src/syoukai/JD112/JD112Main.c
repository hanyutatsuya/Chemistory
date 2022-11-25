/********************************************************************/
/*																	*/
/*		ＢＭＬ様向け検査システム									*/
/*																	*/
/*		システム名	：次世代システム								*/
/*		ファイル名	：JD112Main.c									*/
/*		概要		：検査進行状況集計処理							*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	作成日			名前			修正内容				*/
/* ---------------------------------------------------------------- */
/*  1.00	2006/03/23		H.Suyama		Create					*/
/*  1.01	2006-04-26		H.Suyama		BSKGOK→BSKLNEに変更	*/
/*  1.02	2006-06-03		INTEC   		集計結果0もINSERT		*/
/*  1.04    2006-06-17      INTEC           登録日時10分単位に作成 */
/********************************************************************/

/********************************************************************/
/*	インクルード宣言												*/
/********************************************************************/
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "bml_date.h"
#include "bmllog.h"
#include "bmlprm.h"
#include "JD112Main.h"
#include "JD112Sysknrmst.h"
#include "JD112Syukei.h"

/******************************************************************************/
/* Define定義																  */
/******************************************************************************/
// TRACE
#if defined ( _TRACE )
#define malloc(a)   _malloc(a, __FILE__, __LINE__)
#define free(p)	 _free(p, __FILE__, __LINE__)
#endif

/******************************************************************************/
/* グローバル宣言															  */
/******************************************************************************/
JD112_STSCODE		gintErrorCode;
struct stcLogMember	gstLogMem;

/*:KH-------------------------------------------------------------------------*/
/*:K  関数名   : EnvRef                                                       */
/*----------------------------------------------------------------------------*/
/*:A  機能概要 : ＄環境変数を展開する                                         */
/*----------------------------------------------------------------------------*/
/*:I  入力     : char    *src_cp  : 展開前文字列                              */
/*:O  出力     : 無し             : 無し                                      */
/*:R  戻り値   : char *           : 展開後文字列                              */
/*:C  特記事項 :                                                              */
/*----------------------------------------------------------------------------*/
char    *EnvRef( src_cp )
char        *src_cp;
{
static char value[256];                 /* 展開後文字列 */
    char    *dst_cp;                    /* 展開後文字列 */
    char    buf[256];                   /* ＄環境変数 */
    char    *env_cp;                    /* ＄環境変数 */

    dst_cp = value;
    while( *src_cp != 0 ) {
        if( *src_cp == '$' ) {
            env_cp = buf;
            *env_cp++ = *src_cp++;
            while( *src_cp != 0
                && *src_cp != ' ' && *src_cp != '\t'
                && *src_cp != '$' && *src_cp != '/' && *src_cp != '\\' ) {
                *env_cp++ = *src_cp++;
            }
            *env_cp = 0;
            if( (env_cp = getenv( &buf[1] )) == NULL ) {
                env_cp = buf;
            }
            while( *env_cp != 0 ) {
                *dst_cp++ = *env_cp++;
            }
        } else {
            *dst_cp++ = *src_cp++;
        }
    }
    *dst_cp = 0;

    return( value );
}

/******************************************************************************/
/*　関 数 名　：initFunction()												  */
/*　機能概要　：初期処理関数												  */
/*　入　　力　：															  */
/*　　第１引数：int argc			プログラム引数数						  */
/*　　第２引数：char *argv[]		プログラム引数							  */
/*　　第３引数：JD112Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int initFunction( int argc, char *argv[], JD112Env *pEnv )
{
	char	cPrmBuf[256];
	char	*lc_login;

	// 初期化
	// エラーステータス変更
	gintErrorCode = 0;
	// プログラム環境変数初期化
	memset( pEnv, '\0', sizeof( JD112Env ) );

	// ログオープン
    // 1.03 HAGA DELL 環境変数展開後の値を渡す
/*
DEL if( ZbmlOpenLog( MYAPP_LOGINIFILE ) != 0 ) {
*/
    if( ZbmlOpenLog( EnvRef( MYAPP_LOGINIFILE ) ) != 0 ) {
        return( RTN_NG );
    }

	// ログ情報初期設定
	memset( &gstLogMem, '\0', sizeof( gstLogMem ) );
	if ( ( lc_login = getenv( "LOGNAME" ) ) != NULL ) {
		strcpy( gstLogMem.pcLoginId, lc_login );
	}
	strcpy( gstLogMem.pcAppName, MYAPP_APP_NAME );

	// 開始ログ出力
	sFncPutLog( TRCKIND_TRACE, __FILE__, "", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"プログラム起動" );

/*
	// 引数数チェック
	if ( argc != 2 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_USEGE;
		sFncPutLog( TRCKIND_ERROR, __FILE__, "initFunction", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"コマンドパラメータに誤りがあります" );
		return( RTN_NG );
	}
*/
	// パラメータファイル名退避
	if ( argc >= 2 ) {
		pEnv->pcFileNamePRM = argv[1];
	} else {
		pEnv->pcFileNamePRM = MYAPP_INIFILE;
	}

	// パラメータファイルオープン
	pEnv->bp = ZbmlPrmOpen( pEnv->pcFileNamePRM );
	if ( pEnv->bp == NULL ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_FILE;
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZZbmlPrmOpen", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"パラメータファイルのオープンに失敗しました[%s]", pEnv->pcFileNamePRM );
		return( RTN_NG );
	}

	// データベース接続名
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_DBNAME,
						 pEnv->cDBName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ログインユーザ
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_DBUSER,
						pEnv->cDBUser ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ログインパスワード
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_DBPAWD,
						pEnv->cDBPawd ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ポート番号
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_PORTNO,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iPortNo= atoi( cPrmBuf );
	// コネクト接続待ち数
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_LISTEN,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iListen= atoi( cPrmBuf );
	// 通信リトライ回数
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_RETRY_CNT,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iRetryCnt= atoi( cPrmBuf );
	// タイムアウト値（秒）
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_TIMEOUT,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iTimeout= atoi( cPrmBuf );
	// 依頼展開アプリ名
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_APP_IRAI,
						pEnv->cAppIrai ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 患者属性展開アプリ名
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_APP_KANJYA,
						pEnv->cAppKanjya ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 分注展開アプリ名
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_APP_BUNCHU,
						pEnv->cAppBunchu ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 認識展開アプリ名
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_APP_NINSIKI,
						pEnv->cAppNinsiki ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 検体属性展開アプリ名
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_APP_KENZOK,
						pEnv->cAppKenzok ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// デバッグログファイル
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_FILE_DBG,
						pEnv->cDebugLogName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// トレースログファイル
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_FILE_TR,
						pEnv->cTraceLogName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// アクセスログファイル
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_FILE_ACS,
						pEnv->cAccessLogName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// エラーログファイル
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_FILE_ERR,
						pEnv->cErrorLogName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 共有メモリキー取得
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_SHM_KEY,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->shm_Key = atoi( cPrmBuf );
	// スリープ時間（秒）取得
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_SLEEP_SEC,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iSleepSec= atoi( cPrmBuf );
	// 更新間隔（分）取得
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_UPDATE_MIN,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iUpdateMin= atoi( cPrmBuf );
	// 更新者ID
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_UP_ID,
						pEnv->cUpdateId ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 更新者名
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_UP_NM,
						pEnv->cUpdateName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 実行モード
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_PROC_MD,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->proc_mode= atoi( cPrmBuf );

	// 1.04 ADD 集計対象開始日時(YYYY-MM-DD-HH24:MI:00)(必須ではない)
	ZbmlPrmGetVal( pEnv->bp, JD112_PRM_STA_DH, pEnv->cStaTimestamp );

	// パラメータファイルクローズ
	ZbmlPrmClose( pEnv->bp );

	// 共有メモリ生成
	if ( sFncShmCrt( pEnv ) != RTN_OK ) {
		return( RTN_NG );
	}

	// ソケットFD初期化
	pEnv->iSockFd = 0;
	// スレッドステータス初期化
	pEnv->iThreadSts = 0;
	// 集計実行開始フラグ初期化
	pEnv->iCallFunc = JD112_CALLFUNC_START;
	// 集計開始時間初期化
	pEnv->ulPrevKsndh = 0;
	// 初回起動時の時間
	pEnv->iBaseJikan = 0;

	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "initFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function" );
	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：mainFunction()												  */
/*　機能概要　：メイン処理関数												  */
/*　入　　力　：															  */
/*　　第１引数：JD112Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int mainFunction( JD112Env *pEnv )
{
	int			iRet;
	int			iShmMem;
	int			iLapseSec = 0;
	pthread_t	thread;
	int			*pExitCode;
	Sysknrmst	stSysknrmst;

	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	// データベース接続
	if( iRet = ZdbConnect( pEnv->cDBName,
						   pEnv->cDBUser,
						   pEnv->cDBPawd ) ) {
		// 異常終了	LOG
printf("ZdbConnect error (%d)\n", iRet);
		return( RTN_NG );
	}

	// ソケット通信用スレッドの作成
	if ( iRet = pthread_create( &thread, NULL, JD112SocketThread, (void *)pEnv ) ) {
		// 異常終了	LOG
printf("pthread_create error (%d)\n", iRet);
		return( RTN_NG );
	}

	// システム管理情報取得
	iRet = ZdbSysknrmstSelect( &stSysknrmst );
	if ( iRet != HRC_SQL_NORMAL ) {
		// 異常終了	LOG
printf("ZdbSysknrmstSelect error (%d)\n", iRet);
		return( RTN_NG );
	}

	// 報告管理情報テーブル監視
	// 永久ループ、停止コマンドで終了
	while ( 1 ) {
		// 停止コマンド確認
		if ( sFncShmGet( pEnv, &iShmMem ) != RTN_OK ) {
printf("sFncShmGet error\n");
			return( RTN_NG );
		}
		if ( iShmMem == 1 ) {
			if ( pEnv->iSockFd != 0 ) {
				shutdown( pEnv->iSockFd, SHUT_RDWR );
			}
printf( "sock FD:[%d]\n", pEnv->iSockFd );
//			pthread_cancel( thread );
			break;
		}

		// 更新間隔を超えたら集計処理をコールする
		if ( iLapseSec >= ( pEnv->iUpdateMin * JD112_SECOFMIN ) ) {
			iLapseSec = 0;
			pEnv->iCallFunc = JD112_CALLFUNC_START;
		}

		// 初回、更新間隔経過後、クライアント要求時は経過時間が０
		if ( pEnv->iCallFunc == JD112_CALLFUNC_START ) {
printf("call JD112SyukeiMain\n");
			// 検査進行状況集計メイン呼び出し
			JD112SyukeiMain( pEnv, stSysknrmst.kjnsriymd );
			pEnv->iCallFunc = JD112_CALLFUNC_STOP;
		}
		
		// スリープ
		sleep( pEnv->iSleepSec );
		iLapseSec += pEnv->iSleepSec;
	}

	pthread_join( thread, (void **)&pExitCode );
	if ( pExitCode == NULL ) {
		printf("Thread code is NULL\n");
	} else {
printf("3\n");
		printf("Thread code is %d\n", *pExitCode);
	}

	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：endFunction()												  */
/*　機能概要　：終了処理関数												  */
/*　入　　力　：															  */
/*　　第１引数：JD112Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：なし														  */
/******************************************************************************/
void endFunction( JD112Env *pEnv )
{
	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "endFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");
	// 共有メモリ削除
	if ( sFncShmDel( pEnv ) != RTN_OK ) {
		return;
	}

	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "endFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");
}

/******************************************************************************/
/*　関 数 名　：JD112SyukeiMain()											  */
/*　機能概要　：検査進行状況集計メイン										  */
/*　入　　力　：															  */
/*　　第１引数：JD112Env *pEnv		プログラム環境構造体					  */
/*　　第２引数：char *pKnskisymd	検査開始日								  */
/*　出　　力　：															  */
/*　復帰情報　：なし														  */
/******************************************************************************/
int JD112SyukeiMain( JD112Env *pEnv, char *pKnskisymd )
{
	int			iRet;
	JD112Syukei	*pJD112SyukeiArray = NULL;
	int			iJD112SyukeiNum;
	Knssnkjyk	stKnssnkjyk;
	ULONG		ulExecTime;
	struct tm	*tm;
	char		cFromDt[27];
	char		cToDt[27];
	char		cFromDateTime[19];
	char		cToDateTime[19];
	char		cKoteiLoop;
	int			iLoop;
	int			iJikan;
	char		cbuf[10];			// 1.02 ADD
	int			iLoop2;				// 1.02 ADD
	int			me_max;				// 1.02 ADD
	struct		_MEMST	*pMe;		// 1.02 ADD
	char		clExecTime[27];		// 1.04 ADD
	int			iDateRet;			// 1.04 ADD
	int 		icnt0 = 0;				// 1.04 ADD

	// 処理日時設定
	time( (long *)&ulExecTime );
	tm = localtime( (long *)&ulExecTime );
/* 1.04 DELL 
//	sprintf( cToDt, JD112_FMT_TIMESTAMP,
//			 tm->tm_year + 1900,
//			 tm->tm_mon + 1,
//			 tm->tm_mday,
//			 tm->tm_hour,
//			 tm->tm_min,
//			 tm->tm_sec );
//	sprintf( cToDateTime, JD112_FMT_DATETIME,
//			 tm->tm_year + 1900,
//			 tm->tm_mon + 1,
//			 tm->tm_mday,
//			 tm->tm_hour,
//			 tm->tm_min,
//			 tm->tm_sec );
//
//	if ( pEnv->ulPrevKsndh == 0 ) {
//		// 前回集計開始時間が初期値の場合はシステム起動時間から算出
//		tm->tm_min = 0;
//		tm->tm_sec = 0;
//		// 初回起動時の時間を保存
//	 	pEnv->iBaseJikan = tm->tm_hour;
//	} else {
//		// 前回集計開始時間
//		tm = localtime( (long *)&pEnv->ulPrevKsndh );
//	}
//	sprintf( cFromDt, JD112_FMT_TIMESTAMP,
//			 tm->tm_year + 1900,
//			 tm->tm_mon + 1,
//			 tm->tm_mday,
//			 tm->tm_hour,
//			 tm->tm_min,
//			 tm->tm_sec );
//	sprintf( cFromDateTime, JD112_FMT_DATETIME,
//			 tm->tm_year + 1900,
//			 tm->tm_mon + 1,
//			 tm->tm_mday,
//			 tm->tm_hour,
//			 tm->tm_min,
//			 tm->tm_sec );
*/
	// 検索対象終了日時(=SYSDATE)の設定
	memset( clExecTime, '\0', sizeof( clExecTime ));
	sprintf( clExecTime, JD112_FMT_TIMESTAMP,
			 tm->tm_year + 1900,
			 tm->tm_mon + 1,
			 tm->tm_mday,
			 tm->tm_hour,
			 tm->tm_min,
			 tm->tm_sec );
		// 分を０にする	
	clExecTime[15] = '0';

	// 検索対象開始日時の設定 TO -10min -> FROM
	memset( cFromDt,	'\0',	sizeof( cFromDt ));
	memset( cToDt,		'\0',	sizeof( cToDt ));
		// 初回
	if ( pEnv->clPrevKsndh[0] == '\0' ) {
			// CurrenTimestamp -1 hour を取得
		if( SelStaTimestamp( cToDt ) != RTN_OK ){
			// ERROR
			strcpy( cToDt,	clExecTime );
		}
		// 集計開始日時の指定あり
		if ( pEnv->cStaTimestamp[0] != '\0' ) {
				// 日時妥当性チェック
			if( SelStaTimestamp( pEnv->cStaTimestamp ) == RTN_OK ){
				strcpy( cToDt, pEnv->cStaTimestamp );	
			}
		}
		// 検索対象は１０分単位とし分は切り捨て,秒以下も０に
		strcpy( cFromDt,	cToDt );
		sprintf( cToDt, "%.15s0.00.000000", cFromDt );
	} else {
		// 前回集計開始時間
		strcpy( cToDt,	pEnv->clPrevKsndh );
	}
		// MINUS 10
	SelPlus10Minutes( cToDt, MYAPP_FUNC_MINUS );

// 1.04 ADD 開始日時からSYSDATEまで10分刻みで集計処理を実施
while( 1 ){
	strcpy( cFromDt, cToDt );
	if(( iDateRet = SelPlus10Minutes( cToDt, MYAPP_FUNC_PLUS )) !=  RTN_OK ){
		strcpy( cToDt, clExecTime );	
	}
//printf("exec[%s] from[%s] to[%s]\n", clExecTime, cFromDt, cToDt );
	if( strncmp( clExecTime, cFromDt, 15 ) < 0 ){
		break;
	}
		
	for ( cKoteiLoop = JD112_DB_KOTEIKBN_IRAI;
		  cKoteiLoop <= JD112_DB_KOTEIKBN_SYUNOU;
		  cKoteiLoop++ ) {
		switch ( cKoteiLoop ) {
		// 依頼数集計
		case JD112_DB_KOTEIKBN_IRAI:
			iRet = ZdbJD112SelectCountA( cFromDt, cToDt,
										 &pJD112SyukeiArray,
										 &iJD112SyukeiNum );
			break;
		// 患者数集計
		case JD112_DB_KOTEIKBN_KANJYA:
			iRet = ZdbJD112SelectCountB( cFromDt, cToDt,
										 &pJD112SyukeiArray,
										 &iJD112SyukeiNum );
			// 1.04 ADD 集検フラグNULL対応 0と合算
			for( iLoop2 = 0; iLoop2 < iJD112SyukeiNum ; iLoop2++ ){
				if ( pJD112SyukeiArray[iLoop2].skflg == JD112_DB_SKFLG_NORMAL ){
					icnt0 += pJD112SyukeiArray[iLoop2].count;
				}
			}
			for( iLoop2 = 0; iLoop2 < iJD112SyukeiNum ; iLoop2++ ){
				if ( pJD112SyukeiArray[iLoop2].skflg == JD112_DB_SKFLG_NORMAL ){
					pJD112SyukeiArray[iLoop2].count = icnt0;
				}
			}
			break;
		// 分注数集計
		case JD112_DB_KOTEIKBN_BUNCHU:
			iRet = ZdbJD112SelectCountC( cFromDt, cToDt,
										 &pJD112SyukeiArray,
										 &iJD112SyukeiNum );
			break;
		// 認識数集計
		case JD112_DB_KOTEIKBN_NINSIKI:
			iRet = ZdbJD112SelectCountD( cFromDt, cToDt,
										 &pJD112SyukeiArray,
										 &iJD112SyukeiNum );
			break;
		// 検体属性数集計
		case JD112_DB_KOTEIKBN_KENZOK:
			iRet = ZdbJD112SelectCountE( cFromDt, cToDt,
										 &pJD112SyukeiArray,
										 &iJD112SyukeiNum );
			break;
		// 依頼（エラー）数集計
		case JD112_DB_KOTEIKBN_E_IRAI:
			// 1.04 UPD
			//iRet = ZdbJD112SelectCountFGHIJ( cFromDateTime,
			//								 cToDateTime,
			iRet = ZdbJD112SelectCountFGHIJ( cFromDt, cToDt,
											 pEnv->cAppIrai,
											 &pJD112SyukeiArray,
											 &iJD112SyukeiNum );
			break;
		// 患者（エラー）数集計
		case JD112_DB_KOTEIKBN_E_KANJYA:
			// 1.04 UPD
			//iRet = ZdbJD112SelectCountFGHIJ( cFromDateTime,
			//								 cToDateTime,
			iRet = ZdbJD112SelectCountFGHIJ( cFromDt, cToDt,
											 pEnv->cAppKanjya,
											 &pJD112SyukeiArray,
											 &iJD112SyukeiNum );
			break;
		// 分注（エラー）数集計
		case JD112_DB_KOTEIKBN_E_BUNCHU:
			// 1.04 UPD
			//iRet = ZdbJD112SelectCountFGHIJ( cFromDateTime,
			//								 cToDateTime,
			iRet = ZdbJD112SelectCountFGHIJ( cFromDt, cToDt,
											 pEnv->cAppBunchu,
											 &pJD112SyukeiArray,
											 &iJD112SyukeiNum );
			break;
		// 認識（エラー）数集計
		case JD112_DB_KOTEIKBN_E_NINSIKI:
			// 1.04 UPD
			//iRet = ZdbJD112SelectCountFGHIJ( cFromDateTime,
			//								 cToDateTime,
			iRet = ZdbJD112SelectCountFGHIJ( cFromDt, cToDt,
											 pEnv->cAppNinsiki,
											 &pJD112SyukeiArray,
											 &iJD112SyukeiNum );
			break;
		// 検体属性（エラー）数集計
		case JD112_DB_KOTEIKBN_E_KENZOK:
			// 1.04 UPD
			//iRet = ZdbJD112SelectCountFGHIJ( cFromDateTime,
			//								 cToDateTime,
			iRet = ZdbJD112SelectCountFGHIJ( cFromDt, cToDt,
											 pEnv->cAppKenzok,
											 &pJD112SyukeiArray,
											 &iJD112SyukeiNum );
			break;
		// 投入数集計
		case JD112_DB_KOTEIKBN_TOUNYU:
			iRet = ZdbJD112SelectCountKM( cFromDt, cToDt,
										  JD112_DB_KNSJKFLG_CHUU,
										 &pJD112SyukeiArray,
										 &iJD112SyukeiNum );
			break;
		// 測定数集計
		case JD112_DB_KOTEIKBN_SOKUTEI:
			iRet = ZdbJD112SelectCountL( cFromDt, cToDt,
										 &pJD112SyukeiArray,
										 &iJD112SyukeiNum );
			break;
		// 収納数集計
		case JD112_DB_KOTEIKBN_SYUNOU:
			iRet = ZdbJD112SelectCountKM( cFromDt, cToDt,
										  JD112_DB_KNSJKFLG_DONE,
										  &pJD112SyukeiArray,
										  &iJD112SyukeiNum );
			break;
		}
		if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
			//異常終了
			//ログ出力
printf("ZdbJD112SelectCount* error (%d)\n", iRet);
			return( RTN_NG );
		}

		// 取得した分類分集計テーブル更新
		for ( iLoop = 0; iLoop < iJD112SyukeiNum; iLoop++ ) {
			memset( &stKnssnkjyk, 0, sizeof( stKnssnkjyk ) );

/* 1.04 DELL 検査開始日には登録日を、経過seqは算出せず時分を設定
//			ZbmlInfocpy( stKnssnkjyk.knskisymd, pKnskisymd, 
//					sizeof( stKnssnkjyk.knskisymd ) );
//			// 経過ＳＥＱは起動時の時間から算出
//			iJikan = atoi( pJD112SyukeiArray[iLoop].jikan );
//			if ( iJikan >= pEnv->iBaseJikan ) {
//				stKnssnkjyk.keikseq = iJikan - pEnv->iBaseJikan + 1;
//			} else {
//				stKnssnkjyk.keikseq = iJikan + 24 - pEnv->iBaseJikan + 1;
//			}
*/
			// jikan( YYYY-MM-DD-HH24:MI )
			// 検査開始日 (jikan YYYY-MM-DD)
			sprintf( stKnssnkjyk.knskisymd, "%.10s"
					, pJD112SyukeiArray[iLoop].jikan );
			// 経過seq 時分( jikan HH24MI 0 )
			sprintf( stKnssnkjyk.jikan, "%.2s%.1s0"
					, &pJD112SyukeiArray[iLoop].jikan[11] 
					, &pJD112SyukeiArray[iLoop].jikan[14] );
			stKnssnkjyk.keikseq = atoi( stKnssnkjyk.jikan );

			stKnssnkjyk.koteikbn = cKoteiLoop;
			if ( pJD112SyukeiArray[iLoop].skflg == JD112_DB_SKFLG_NORMAL )
				stKnssnkjyk.datazok = JD112_DB_DATAZOK_NORMAL;
			else if ( pJD112SyukeiArray[iLoop].skflg == JD112_DB_SKFLG_SYUKEN )
				stKnssnkjyk.datazok = JD112_DB_DATAZOK_SYUKEN;

			if ( stKnssnkjyk.koteikbn == JD112_DB_KOTEIKBN_SOKUTEI ) {
				ZbmlInfocpy( stKnssnkjyk.bskkbn
					, pJD112SyukeiArray[iLoop].bskkbn
					, sizeof( stKnssnkjyk.bskkbn ) );
// 2006-04-26 H.Suyama Change Start
#if 0
//				ZbmlInfocpy( stKnssnkjyk.bskgok, pJD112SyukeiArray[iLoop].bskgok, sizeof( stKnssnkjyk.bskgok ) );
#else
				ZbmlInfocpy( stKnssnkjyk.bskgok
					, pJD112SyukeiArray[iLoop].bsklne
					, sizeof( stKnssnkjyk.bskgok ) );
#endif
// 2006-04-26 H.Suyama Change End
			} else {
				memset( stKnssnkjyk.bskkbn, JD112_CHAR_SPACE
						, sizeof( stKnssnkjyk.bskkbn ) - 1 );
				memset( stKnssnkjyk.bskgok, JD112_CHAR_SPACE
						, sizeof( stKnssnkjyk.bskgok ) - 1 );
			}
			stKnssnkjyk.syukka = pJD112SyukeiArray[iLoop].count;
/* 1.04 DELL 
//			sprintf( stKnssnkjyk.jikan, "%2s00"
//					, pJD112SyukeiArray[iLoop].jikan );
*/
			ZbmlInfocpy( stKnssnkjyk.ksndh, cToDt, sizeof( stKnssnkjyk.ksndh ));

			// 検査進行状況集計更新
			iRet = JD112UpdateKnssnkjyk( &stKnssnkjyk );
			if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
				//異常終了
				//ログ出力
printf("JD112UpdateKnssnkjyk error (%d)\n", iRet);
				return( RTN_NG );
			}
		}

		// 1.02 INTEC ADD STA
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// 全データ属性、分析機区分、号機のレコードを０件で作成する
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			// 共通データ設定
		memset( &stKnssnkjyk, '\0', sizeof( stKnssnkjyk ) );
/* 1.04 DELL
//		ZbmlInfocpy( stKnssnkjyk.knskisymd, pKnskisymd, 
//					sizeof( stKnssnkjyk.knskisymd ) );
//			// 経過ＳＥＱ算出元は、fromの時間をセット
//		memset( cbuf, '\0', sizeof( cbuf ));
//		sprintf( cbuf, "%.2s", &cToDt[11] );
//		iJikan = atoi( cbuf );
//		if ( iJikan >= pEnv->iBaseJikan ) {
//			stKnssnkjyk.keikseq = iJikan - pEnv->iBaseJikan + 1;
//		} else {
//			stKnssnkjyk.keikseq = iJikan + 24 - pEnv->iBaseJikan + 1;
//		}
*/
		// 検査開始日 (cToDt YYYY-MM-DD)
		sprintf( stKnssnkjyk.knskisymd, "%.10s" , cFromDt  );
		// 経過seq 時分( cToDt HH24MI 0 )
		sprintf( stKnssnkjyk.jikan, "%.2s%.1s0"
				, &cFromDt[11], &cFromDt[14] );
		stKnssnkjyk.keikseq = atoi( stKnssnkjyk.jikan );

		stKnssnkjyk.koteikbn = cKoteiLoop;

		memset( stKnssnkjyk.bskkbn, JD112_CHAR_SPACE, 
						sizeof( stKnssnkjyk.bskkbn ) - 1 );
		memset( stKnssnkjyk.bskgok, JD112_CHAR_SPACE, 
						sizeof( stKnssnkjyk.bskgok ) - 1 );
		stKnssnkjyk.syukka = 0;
/* 1.04 DELL
//			// 時間にはfromの時間を使用
//		sprintf( stKnssnkjyk.jikan, "%2s00", cbuf );
*/
		ZbmlInfocpy( stKnssnkjyk.ksndh, cToDt, sizeof( stKnssnkjyk.ksndh ));

		// データ属性分作成
		for ( iLoop = 0; iLoop < 2; iLoop++ ) {
			if ( stKnssnkjyk.koteikbn == JD112_DB_KOTEIKBN_SOKUTEI ) {
				continue;
			}
			if( iLoop == 0 ){
				stKnssnkjyk.datazok = JD112_DB_DATAZOK_NORMAL;
			} else {
				stKnssnkjyk.datazok = JD112_DB_DATAZOK_SYUKEN;
			}
			// 検査進行状況集計更新

			iRet = JD112UpdateKnssnkjyk( &stKnssnkjyk );
			if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
				//異常終了
				//ログ出力
				// commit rollback はJD112UpdateKnssnkjyk　にて実施
				return( RTN_NG );
			}
		}
		// 工程＝Lの場合は、分析機区分、ライン分作成 データ属性分作成
		if ( stKnssnkjyk.koteikbn == JD112_DB_KOTEIKBN_SOKUTEI ) {
			// 分析機マスタの件数取得
			me_max=SelCountMemst( stKnssnkjyk.knskisymd );
			if( me_max == 0 ){
				// ERROR
				break;
			}
			// 領域確保
			if(( pMe = ((struct _MEMST *)malloc(
					sizeof(struct _MEMST) * me_max ))) == NULL ){
				//sprintf(G_msg, "分析機マスタの領域確保に失敗しました。" );
				// WARNING
				break;
			}
			/* 基準値マスタ退避領域の初期化 */
			memset( pMe, '\0', sizeof( struct _MEMST ) * me_max );

			// 対象基準値マスタの取得
			if( SelMemst( stKnssnkjyk.knskisymd, me_max, pMe ) !=  RTN_OK ){
				//sprintf(G_msg, "分析機マスタの読み込みに失敗しました。" );
				// WARNING
				free( pMe );
				break;
       		}
			
			// データ属性分作成
			for ( iLoop2 = 0; iLoop2 < me_max; iLoop2++ ) {
				strcpy( stKnssnkjyk.bskkbn, pMe[iLoop2].bskkbn );
				strcpy( stKnssnkjyk.bskgok, pMe[iLoop2].bsklne );

				for ( iLoop = 0; iLoop < 2; iLoop++ ) {
					if( iLoop == 0 ){
						stKnssnkjyk.datazok = JD112_DB_DATAZOK_NORMAL;
					} else {
						stKnssnkjyk.datazok = JD112_DB_DATAZOK_SYUKEN;
					}
					// 検査進行状況集計更新
					iRet = JD112UpdateKnssnkjyk( &stKnssnkjyk );
					if (iRet != HRC_SQL_NORMAL&&iRet != HRC_SQL_NOT_FOUND){
						//異常終了
						//ログ出力
						free( pMe );
						return( RTN_NG );
					}
				}
			}
			if( pMe != NULL ){
				free( pMe );
			}
		}
		// 1.02 INTEC ADD END

		if ( pJD112SyukeiArray ) {
			ZbmlFree( pJD112SyukeiArray );
			pJD112SyukeiArray = NULL;
		}
	}

	ZdbCommit();
}

	pEnv->ulPrevKsndh = ulExecTime;
	strcpy( pEnv->clPrevKsndh, cFromDt );

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：JD112UpdateKnssnkjyk()										  */
/*　機能概要　：検査進行状況集計更新										  */
/*　入　　力　：															  */
/*　　第１引数：Knssnkjyk	*pKnssnkjyk	検査進行状況集計情報構造体			  */
/*　出　　力　：															  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int JD112UpdateKnssnkjyk(Knssnkjyk *pKnssnkjyk)
{
	int			iRet;
	Knssnkjyk	stKnssnkjyk;
	int			iKeikseq;

	//memset( &stKnssnkjyk, 0, sizeof( stKnssnkjyk ) );
	memset( &stKnssnkjyk, '\0', sizeof( stKnssnkjyk ) );

	// 同じ時間帯の同一キーレコードがあるか検索
	iRet = ZdbKnssnkjykJD112SelectJikan( pKnssnkjyk,
										 &stKnssnkjyk );
	if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
		// ロールバック
		ZdbRollback();
		// 異常終了	LOG
printf("ZdbKnssnkjykJD112SelectJikan error (%d)\n", iRet);
		return( RTN_NG );
	}

	if ( iRet == HRC_SQL_NOT_FOUND ) {
		// 検査進行状況集計挿入
		iRet = ZdbKnssnkjykInsert( pKnssnkjyk );
	} else {
		// 1.04 ADD 集計値が０の場合は処理を抜ける
		if( pKnssnkjyk->syukka == 0 ){
			ZdbCommit();
			return( RTN_OK );
		}
		// 1.04 DELL 加算はせずに更新する
/*
//		// 累計を計算
//		stKnssnkjyk.syukka += pKnssnkjyk->syukka;
//		// 情報更新日時を変更
//		ZbmlInfocpy( stKnssnkjyk.ksndh, pKnssnkjyk->ksndh, sizeof( stKnssnkjyk.ksndh ) );
//
//		// 検査進行状況集計更新
//		iRet = ZdbKnssnkjykUpdate( &stKnssnkjyk );
*/
		// 検査進行状況集計更新
		iRet = ZdbKnssnkjykUpdate( pKnssnkjyk );
	}

	if ( iRet != HRC_SQL_NORMAL ) {
		// ロールバック
		ZdbRollback();
		// 異常終了	LOG
printf("ZdbKnssnkjykXXXXXX error (%d)\n", iRet);
// 1.02 INTEC ADD STA
		sFncPutLog( TRCKIND_ERROR, __FILE__, "JD112UpdateKnssnkjyk", __LINE__,
                    EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
               	 	"検査進行状況集計更新に失敗しました。"
					"KNSKISYMD[%s] KEIKSEQ[%d] KOTEIKBN[%c] DATAZOK[%c]", 
					pKnssnkjyk->knskisymd,	pKnssnkjyk->keikseq, 
					pKnssnkjyk->koteikbn,	pKnssnkjyk->datazok );
// 1.02 INTEC ADD END
		return( RTN_NG );
	}
ZdbCommit();

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：JD112SocketThread()											  */
/*　機能概要　：ソケット通信用スレッド										  */
/*　入　　力　：															  */
/*　　第１引数：JD112Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：なし														  */
/******************************************************************************/
void *JD112SocketThread(void *pParam)
{
	JD112Env	*pEnv;
	int			iSockFd;
	int			iNewSockFd;
	int			iSockSts;
	int			iFcSts;
	int			iLen;
	struct sockaddr_in	stSockAddrIn;
	struct sockaddr_in	stSockAddrInCl;
	char		cBuff[JD112_MSG_BUFFLEN];

	pEnv = (JD112Env *)pParam;

	// ソケット初期化
	if ( ( iSockFd = socket( AF_INET, SOCK_STREAM, 0 ) ) == 0 ) {
printf( "socket error\n", iSockFd );
		pEnv->iThreadSts = MYAPP_LOG_ERRCODE_SOCKET;
		pthread_exit( &pEnv->iThreadSts );
	}
	pEnv->iSockFd = iSockFd;

	// バインド
	memset( &stSockAddrIn, 0, sizeof( stSockAddrIn ) );
	stSockAddrIn.sin_family = AF_INET;
	stSockAddrIn.sin_addr.s_addr = INADDR_ANY;
	stSockAddrIn.sin_port = htons( pEnv->iPortNo );
	if ( bind( iSockFd, (struct sockaddr *)&stSockAddrIn,
			   sizeof( struct sockaddr_in ) ) == -1 ) {
		close( iSockFd );
		pEnv->iThreadSts = MYAPP_LOG_ERRCODE_SOCKET;
		pthread_exit( &pEnv->iThreadSts );
	}

	// 接続待ち設定
	if ( listen( iSockFd, pEnv->iListen ) < 0 ) {
		close( iSockFd );
		pEnv->iThreadSts = MYAPP_LOG_ERRCODE_SOCKET;
		pthread_exit( &pEnv->iThreadSts );
	}
printf("Thread start\n");

	while ( 1 ) {
		// 接続待ち
		if ( ( iNewSockFd = accept( iSockFd,
									(struct sockaddr *)&stSockAddrInCl,
									&iLen ) ) < 0 ) {
			close( iSockFd );
			if ( errno != EINVAL ) {
				pEnv->iThreadSts = MYAPP_LOG_ERRCODE_SOCKET;
			}
			if ( errno != EINTR ) {
				close( iNewSockFd );
			}
			pthread_exit( &pEnv->iThreadSts );
		}
printf("accept OK\n");

		// データ読み込み
		if ( JD112SocketRead( iNewSockFd,
							  cBuff,
							  sizeof( cBuff ),
							  pEnv ) == RTN_NG ) {
			shutdown( iNewSockFd, SHUT_RDWR );
			close( iNewSockFd );
			pEnv->iThreadSts = MYAPP_LOG_ERRCODE_SOCKET;
			pthread_exit( &pEnv->iThreadSts );
		}

		// データ検証
		if ( memcmp( cBuff, JD112_MSG_START, sizeof( JD112_MSG_START ) ) == 0 ) {
			pEnv->iCallFunc = JD112_CALLFUNC_START;

			// 集計完了待ち
			while ( pEnv->iCallFunc == JD112_CALLFUNC_START ) {
				sleep( 1 );
			}
printf("Syukei end\n");

			// 終了電文送信
			strcpy( cBuff, JD112_MSG_END );
			if ( JD112SocketWrite( iNewSockFd,
								   cBuff,
								   strlen( cBuff ),
								   pEnv ) == RTN_NG ) {
				shutdown( iNewSockFd, SHUT_RDWR );
				close( iNewSockFd );
				pEnv->iThreadSts = MYAPP_LOG_ERRCODE_SOCKET;
				pthread_exit( &pEnv->iThreadSts );
			}
		}

		close( iNewSockFd );
	}

printf("Thread end\n");

	return( NULL );
}

/******************************************************************************/
/*　関 数 名　：JD112SocketRead()											  */
/*　機能概要　：ソケットデータ読み込み										  */
/*　入　　力　：															  */
/*　　第１引数：int		 iSockFd	ソケットFD								  */
/*　　第３引数：int		 iSize		バッファサイズ							  */
/*　　第４引数：JD112Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　　第２引数：char	 *pBuff		読み込み用バッファ						  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int JD112SocketRead(int iSockFd, char *pBuff, int iSize, JD112Env *pEnv)
{
	int			iLoop;
	int			iSts;
	int			iRet = RTN_NG;

	for ( iLoop = 0; iLoop < pEnv->iRetryCnt; iLoop++ ) {
		memset( pBuff, 0, iSize );
		
		iSts = read( iSockFd, pBuff, iSize );
		if ( iSts < 0 ) {
			if ( errno == EINTR ) {
				continue;
			}
		} else {
			iRet = RTN_OK;
			break;
		}
	}

	return( iRet );
}

/******************************************************************************/
/*　関 数 名　：JD112SocketWrite()											  */
/*　機能概要　：ソケットデータ書き込み										  */
/*　入　　力　：															  */
/*　　第１引数：int		 iSockFd	ソケットFD								  */
/*　　第３引数：int		 iSize		バッファサイズ							  */
/*　　第４引数：JD112Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　　第２引数：char	 *pBuff		読み込み用バッファ						  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int JD112SocketWrite(int iSockFd, char *pBuff, int iSize, JD112Env *pEnv)
{
	int			iLoop;
	int			iSts;
	int			iRet = RTN_NG;

	for ( iLoop = 0; iLoop < pEnv->iRetryCnt; iLoop++ ) {
		iSts = write( iSockFd, pBuff, iSize );
		if ( iSts < 0 ) {
			if ( errno == EINTR ) {
				continue;
			}
		} else {
			iRet = RTN_OK;
			break;
		}
	}

	return( iRet );
}

/******************************************************************************/
/*　関 数 名　：sFncShmCrt()												  */
/*　機能概要　：共有メモリ生成												  */
/*　入　　力　：															  */
/*　　第１引数：JD112Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：なし														  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
static int sFncShmCrt( JD112Env *pEnv )
{
	int	 *shmData;

	// 取得
	pEnv->shm_Id = shmget( (key_t)pEnv->shm_Key,
							JD112_SHM_SIZE,
							0666 | IPC_CREAT );
	if ( pEnv->shm_Id < 0 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_SHM_GET;
		return( RTN_NG );
	}

	// アタッチ
	shmData = ( int * ) shmat( pEnv->shm_Id, 0 , 0 );
	if ( shmData == ( int * )-1 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_SHM_AT;
		return( RTN_NG );
	}
loging ( "stocker : 共有メモリ[CRT] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n",
		 pEnv->shm_Key, pEnv->shm_Id, *shmData, shmData );

	// 値設定
	*shmData = 0;

	// デタッチ
	if ( shmdt( shmData ) == -1 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_SHM_DT;
		return( RTN_NG );
	}

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：sFncShmGet()												  */
/*　機能概要　：共有メモリ取得												  */
/*　入　　力　：															  */
/*　　第１引数：JD112Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　　第２引数：int *pshmData		値										  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
static int sFncShmGet( JD112Env *pEnv, int *pshmData )
{
	int	 *shmData;

	// 
	if ( pshmData == NULL ) {
		// 異常終了	LOG
		return( RTN_NG );
	}

	// アタッチ
	shmData = ( int * ) shmat( pEnv->shm_Id, 0 , 0 );
	if ( shmData == ( int * )-1 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_SHM_AT;
		return( RTN_NG );
	}

	// 値設定
	*pshmData = *shmData;

loging ( "stocker : 共有メモリ[GET] shmKey[%d]-ID[%d]-Data[%d]-Data2[%d]-Add[%x]\n",
		 pEnv->shm_Key, pEnv->shm_Id, shmData[0], shmData[1], shmData );
	// デタッチ
	if ( shmdt( shmData ) == -1 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_SHM_DT;
		return( RTN_NG );
	}

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：sFncShmDel()												  */
/*　機能概要　：共有メモリ削除												  */
/*　入　　力　：															  */
/*　　第１引数：JD112Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
static int sFncShmDel( JD112Env *pEnv )
{
	int	 *shmData;

loging ( "%s : 共有メモリ[DEL] shmKey[%d]-ID[%d]\n",
		 MYAPP_APP_NAME, pEnv->shm_Key, pEnv->shm_Id);
	// 削除
	if ( shmctl( pEnv->shm_Id, IPC_RMID, NULL) < 0 ) {
		// 異常終了	LOG
		gintErrorCode = JD112_STSCODE_ERR_SHM_DEL;
		return( RTN_NG );
	}
	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：_sFncEnvDip()												  */
/*　機能概要　：プログラム環境変数出力関数【トレース用】					  */
/*　入　　力　：															  */
/*　　第１引数：JD112Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：無し														  */
/******************************************************************************/
static void _sFncEnvDip( JD112Env *pEnv )
{
//#if defined ( _TRACE )
	loging( "########## JD112 - _sFncEnvDip ##########\n" );
	loging( "\t%s : [%s]\n", JD112_PRM_DBNAME,		 pEnv->cDBName );
	loging( "\t%s : [%s]\n", JD112_PRM_DBUSER,		 pEnv->cDBUser );
	loging( "\t%s : [%s]\n", JD112_PRM_DBPAWD,		 pEnv->cDBPawd );
	loging( "\t%s : [%s]\n", JD112_PRM_SLEEP_SEC,	  pEnv->iSleepSec );
	loging( "\t%s : [%s]\n", JD112_PRM_SHM_KEY,	pEnv->shm_Key );
	loging( "\t%s : [%s]\n", JD112_PRM_FILE_DBG,	pEnv->cDebugLogName );
	loging( "\t%s : [%s]\n", JD112_PRM_FILE_TR,	pEnv->cTraceLogName );
	loging( "\t%s : [%s]\n", JD112_PRM_FILE_ACS,	pEnv->cAccessLogName );
	loging( "\t%s : [%s]\n", JD112_PRM_FILE_ERR,	pEnv->cErrorLogName );
	loging( "\t%s : [%s]\n", JD112_PRM_UP_ID,		pEnv->cUpdateId );
	loging( "\t%s : [%s]\n", JD112_PRM_UP_NM,		pEnv->cUpdateName );
	loging( "\t%s : [%s]\n", JD112_PRM_PROC_MD,	pEnv->proc_mode );
	loging( "########## JD112 - _sFncEnvDip ##########\n" );
//#endif
}

/******************************************************************************/
/*　関 数 名　：sFncPutLog()												  */
/*　機能概要　：アプリケーションログ出力									  */
/*　入　　力　：															  */
/*　　第１引数：char *	  編集文字列										*/
/*　出　　力　：															  */
/*　復帰情報　：無し														  */
/******************************************************************************/
void sFncPutLog( LOG_TRCKIND peTrcKind, char * pcSrcName, char * pcFncName, int plLineNo, char * pcExeFlg, char * pcErrCode, char * pcfmt, ... )
{
	va_list  ap;
	char	 cMsg[1024];

	// ログ初期値設定
	gstLogMem.eTrcKind = peTrcKind;
	//strcpy( gstLogMem.pcSrcName, pcSrcName );
	strcpy( gstLogMem.pcFncName, pcFncName );
	//gstLogMem.lLineNo = plLineNo;
	strcpy( gstLogMem.pcExeFlg,  pcExeFlg );
	strcpy( gstLogMem.pcErrCode, pcErrCode );
	va_start( ap, pcfmt );
	vsprintf( gstLogMem.pcMsg, pcfmt, ap );
	va_end( ap );

	// ログ出力
	_ZbmlPutLog( &gstLogMem, pcSrcName, plLineNo);
}

/******************************************************************************/
/*　関 数 名　：main()														  */
/*　機能概要　：データ転送処理メイン										  */
/*　入　　力　：															  */
/*　　第１引数：int argc			プログラム引数数						  */
/*　　第２引数：char *argv[]		プログラム引数							  */
/*　出　　力　：															  */
/*　復帰情報　：int															  */
/*　　　　　　		0		： 正常											  */
/*　　　　　　		1以上	： 異常											  */
/******************************************************************************/
int main( int argc, char *argv[] )
{
	JD112Env	stEnv;
    if ( daemon ( 1, 0 ) < 0 ) {
        exit ( 9 ) ;
    }

	// 初期処理
	if ( initFunction( argc, argv, &stEnv )  != 0 ) {
		fprintf( stderr, "%s : Error initFunction [%d]\n",
				 MYAPP_APP_NAME, gintErrorCode );
		exit( 9 );
	}
	_sFncEnvDip( &stEnv );

	// 主処理
	if ( mainFunction( &stEnv )  != 0 ) {
		fprintf( stderr, "%s : Error mainFunction [%d]\n",
				 MYAPP_APP_NAME, gintErrorCode );
		exit( 9 );
	}

	// 終了処理
	endFunction( &stEnv );
	fprintf( stderr, "%s : endFunction [%d]\n",
			 MYAPP_APP_NAME, gintErrorCode );
}


