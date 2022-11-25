/********************************************************************/
/*																	*/
/*		ＢＭＬ様向け検査システム									*/
/*																	*/
/*		システム名	：次世代システム								*/
/*		ファイル名	：GD102Main.c									*/
/*		概要		：結果報告ファイル作成処理						*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	作成日			名前			修正内容				*/
/* ---------------------------------------------------------------- */
/*  1.00	2006/02/27		H.Suyama		Create					*/
/*  1.01	2006/04/05		H.Suyama		HKKSTDH→TNSSTDH		*/
/*      	          		        		HKKEDDH→TNSEDDH		*/
/*  1.02	2006/04/13		H.Suyama		ファイル存在チェックに	*/
/*      	          		        		リトライ処理追加		*/
/*  1.03	2006/04/21		INTEC   		転送エラー対応          */
/*                            	            statには後空白無FILE渡し*/
/********************************************************************/

/********************************************************************/
/*	インクルード宣言												*/
/********************************************************************/
#include <time.h>
#include <sys/stat.h>
#include <errno.h>
#include "bml_date.h"
#include "bmllog.h"
#include "bmlprm.h"
#include "GD102Main.h"
#include "GD102Hkkknri.h"

/******************************************************************************/
/* Define定義																  */
/******************************************************************************/
// TRACE
#if defined ( _TRACE )
#define malloc(a)   _malloc(a, __FILE__, __LINE__)
#define free(p)	 _free(p, __FILE__, __LINE__)
#endif

#define      isAscii(c)      (((c) >= 0x20 && (c) <= 0x7e) ? 1 : 0)

/******************************************************************************/
/* グローバル宣言															  */
/******************************************************************************/
GD102_STSCODE		gintErrorCode;
struct stcLogMember	gstLogMem;
char				gcLogMsg[256];				// 1.03 INTEC ADD

/******************************************************************************/
/*　関 数 名　：GD102ConvTimestamp()										  */
/*　機能概要　：日時変換関数												  */
/*　入　　力　：															  */
/*　　第１引数：ULONG ulTm			日時									  */
/*　出　　力　：															  */
/*　　第２引数：char *pDest			変換後文字列							  */
/*　　　　　　						YYYY-MM-DD-HH.MM.SS.000000				  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
void GD102ConvTimestamp(ULONG ulTm, char *pDest)
{
	struct tm	*tm;

	tm = localtime((long *)&ulTm);
	sprintf( pDest, "%04d-%02d-%02d-%02d.%02d.%02d.000000",
			 tm->tm_year + 1900,
			 tm->tm_mon + 1,
			 tm->tm_mday,
			 tm->tm_hour,
			 tm->tm_min,
			 tm->tm_sec );
}

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
char		*src_cp;
{
static char	value[256];     			/* 展開後文字列 */
    char	*dst_cp;        			/* 展開後文字列 */
    char	buf[256];       			/* ＄環境変数 */
    char	*env_cp;        			/* ＄環境変数 */

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
/*　　第３引数：GD102Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int initFunction( int argc, char *argv[], GD102Env *pEnv )
{
	char	cPrmBuf[256];
	char	*lc_login;

	// 初期化
		// 1.03 INTEC ADD
	memset( gcLogMsg, '\0',	sizeof( gcLogMsg ));
	// エラーステータス変更
	gintErrorCode = 0;
	// プログラム環境変数初期化
	memset( pEnv, '\0', sizeof( GD102Env ) );

	// ログオープン
	// 1.03 INTEC DELL 環境変数展開後の値を渡す
/*	
DEL	if( ZbmlOpenLog( MYAPP_LOGINIFILE ) != 0 ) {
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
	sFncPutLog( TRCKIND_TRACE, __FILE__, "initFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"プログラム起動" );

/*
	// 引数数チェック
	if ( argc != 2 ) {
		// 異常終了	LOG
		gintErrorCode = GD102_STSCODE_ERR_USEGE;
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
		gintErrorCode = GD102_STSCODE_ERR_PRM_FILE;
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmOpen", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"パラメータファイルのオープンに失敗しました[%s]", pEnv->pcFileNamePRM );
		return( RTN_NG );
	}

	// データベース接続名
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DBNAME,
						 pEnv->cDBName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ログインユーザ
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DBUSER,
						pEnv->cDBUser ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ログインパスワード
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DBPAWD,
						pEnv->cDBPawd ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// HULFT実行ファイルディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_HULFTBIN,
						pEnv->cDirHULFTBin ) != 0 ) {
		// 異常終了     LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 結果報告ファイルREQUESTディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_REQ_KKA,
						pEnv->cDirReqKKA ) != 0 ) {
		// 異常終了 LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 依頼要求ファイルREQUESTディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_REQ_IRAI,
						pEnv->cDirReqIRAI ) != 0 ) {
		// 異常終了 LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 分注結果要求ファイルREQUESTディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_REQ_BUNC,
						pEnv->cDirReqBUNC ) != 0 ) {
		// 異常終了 LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 他サテライト結果要求ファイルREQUESTディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_REQ_OTHERKKA,
						pEnv->cDirReqOTHERKKA ) != 0 ) {
		// 異常終了 LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 結果報告ファイルOKディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_OK_KKA,
						pEnv->cDirOkKKA ) != 0 ) {
		// 異常終了 LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 依頼要求ファイルOKディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_OK_IRAI,
						pEnv->cDirOkIRAI ) != 0 ) {
		// 異常終了 LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 分注結果要求ファイルOKディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_OK_BUNC,
						pEnv->cDirOkBUNC ) != 0 ) {
		// 異常終了 LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 他サテライト結果要求ファイルOKディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_OK_OTHERKKA,
						pEnv->cDirOkOTHERKKA ) != 0 ) {
		// 異常終了 LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 結果報告ファイルERRディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_ERR_KKA,
						pEnv->cDirErrKKA ) != 0 ) {
		// 異常終了 LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 依頼要求ファイルERRディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_ERR_IRAI,
						pEnv->cDirErrIRAI ) != 0 ) {
		// 異常終了 LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 分注結果要求ファイルERRディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_ERR_BUNC,
						pEnv->cDirErrBUNC ) != 0 ) {
		// 異常終了 LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 他サテライト結果要求ファイルERRディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_ERR_OTHERKKA,
						pEnv->cDirErrOTHERKKA ) != 0 ) {
		// 異常終了 LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// HULFT送信ファイル名
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_SEND_FILENAME,
						pEnv->cSendFileName ) != 0 ) {
		// 異常終了 LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// HULFT送信OK確認ファイル名
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_SEND_FILEOK,
						pEnv->cSendFileOK ) != 0 ) {
		// 異常終了 LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// HULFT送信NG確認ファイル名
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_SEND_FILENG,
						pEnv->cSendFileNG ) != 0 ) {
		// 異常終了 LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// HULFT送信ファイルID
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_HULFT_FILEID,
						pEnv->cHULFTFileID ) != 0 ) {
		// 異常終了     LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// HULFT実行結果待ち時間
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_INTERVAL,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iInterval= atoi( cPrmBuf );
	// 送信リトライ回数
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_SEND_RETRY,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iSendRetry= atoi( cPrmBuf );
	// 送信コマンドリトライ回数
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_CMD_RETRY,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iCmdRetry= atoi( cPrmBuf );
	// 結果チェックコマンドリトライ回数
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_RESULT_RETRY,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iResultRetry= atoi( cPrmBuf );
	// デバッグログファイル
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_FILE_DBG,
						pEnv->cDebugLogName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// トレースログファイル
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_FILE_TR,
						pEnv->cTraceLogName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// アクセスログファイル
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_FILE_ACS,
						pEnv->cAccessLogName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// エラーログファイル
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_FILE_ERR,
						pEnv->cErrorLogName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 共有メモリキー取得
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_SHM_KEY,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->shm_Key = atoi( cPrmBuf );
	// スリープ時間（秒）取得
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_SLEEP_SEC,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iSleepSec= atoi( cPrmBuf );
	// 更新者ID
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_UP_ID,
						pEnv->cUpdateId ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 更新者名
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_UP_NM,
						pEnv->cUpdateName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 実行モード
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_PROC_MD,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->proc_mode= atoi( cPrmBuf );

	// パラメータファイルクローズ
	ZbmlPrmClose( pEnv->bp );

	// 共有メモリ生成
	if ( sFncShmCrt( pEnv ) != RTN_OK ) {
		return( RTN_NG );
	}

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
/*　　第１引数：GD102Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int mainFunction( GD102Env *pEnv )
{
	int			iRet;
	int			li_stopFlg = 0;

	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	if( iRet = ZdbConnect( pEnv->cDBName,
						   pEnv->cDBUser,
						   pEnv->cDBPawd ) ) {
		// 異常終了	LOG
		//	1.03 printf -> LOG
		sprintf( gcLogMsg,	"ZdbConnect error (%d)", iRet);
		sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_DB, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("ZdbConnect error (%d)\n", iRet);
*/
		return( RTN_NG );
	}

	// 報告管理情報テーブル監視
	// 永久ループ、停止コマンドで終了
	while ( 1 ) {
		// 停止コマンド確認
		if ( sFncShmGet( pEnv, &li_stopFlg ) != RTN_OK ) {
				//	1.03 printf -> LOG
				sprintf( gcLogMsg,	"sFncShmGet error [%d]", gintErrorCode );
				sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_ETC, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("sFncShmGet error\n");
*/
			return( RTN_NG );
		}
		if ( li_stopFlg == 1 ) {
			break;
		}

		// 結果報告ファイルの送信
		GD102SendKekkaFile( pEnv );

		// 他サテライト結果要求情報の送信
		GD102SendOtherKkaFile( pEnv );

		// 依頼項目要求情報の送信
		GD102SendIraiFile( pEnv );

		// 分注結果要求情報の送信
		GD102SendBunchuFile( pEnv );

		// スリープ
		sleep( pEnv->iSleepSec );
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
/*　　第１引数：GD102Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：なし														  */
/******************************************************************************/
void endFunction( GD102Env *pEnv )
{
	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "endFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");
	// 共有メモリ削除
	if ( sFncShmDel( pEnv ) != RTN_OK ) {
		//	1.03 LOG
		sprintf( gcLogMsg,	"sFncShmDel error (%d)", gintErrorCode );
		sFncPutLog( TRCKIND_WARNING, __FILE__, "endFunction", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_ETC, gcLogMsg );
		return;
	}

	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "endFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");
}

/******************************************************************************/
/*　関 数 名　：GD102UpdateHkkknriSts()										  */
/*　機能概要　：報告管理情報エラー更新										  */
/*　入　　力　：															  */
/*　　第１引数：Hkkknri *pHkkknri	報告管理情報環境構造体					  */
/*　　第２引数：char *pHkkjkflg		報告状況フラグ							  */
/*　　第３引数：char *pHkkerrcode	報告エラーコード						  */
/*　出　　力　：															  */
/*　復帰情報　：なし														  */
/******************************************************************************/
void GD102UpdateHkkknriSts( Hkkknri *pHkkknri, char *pHkkjkflg, char *pHkkerrcode )
{
	int			iRet;

	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102UpdateHkkknriSts", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	// 報告管理情報を更新
	ZbmlInfocpy( pHkkknri->hkkjkflg, pHkkjkflg, sizeof( pHkkknri->hkkjkflg ) );
	ZbmlInfocpy( pHkkknri->hkkerrcode, pHkkerrcode, sizeof( pHkkknri->hkkerrcode ) );

	// 報告管理情報を更新
	iRet = ZdbHkkknriGD102Update( pHkkknri );
	if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
		// ロールバック
		ZdbRollback();
		// 異常終了	LOG
			//	1.03 printf -> LOG
		sprintf( gcLogMsg,	"ZdbHkkknriGD102Update error (%d)", iRet );
		sFncPutLog( TRCKIND_WARNING, __FILE__, "GD102UpdateHkkknriSts", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_DB, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("ZdbHkkknriGD102Update error (%d)\n", iRet);
*/
	} else {
		// コミット
		ZdbCommit();
	}

	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102UpdateHkkknriSts", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");
}

/******************************************************************************/
/*　関 数 名　：GD102SendFile()												  */
/*　機能概要　：結果報告ファイル送信										  */
/*　入　　力　：															  */
/*　　第１引数：GD102Env *pEnv		プログラム環境構造体					  */
/*　　第２引数：char *pFileName		送信ファイル名							  */
/*　出　　力　：															  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int GD102SendFile(GD102Env *pEnv, char *pFileName)
{
	int				iRet;
	int				iLoop;
	char			cCmdBuff[256];
	char			iRetryLoop;
	char			iCmdRetryLoop;
	int				iResult;
	struct stat		stStat;

	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102SendFile", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	// 送信対象ファイルをHULFT送信用ファイルにコピー
	memset( cCmdBuff, 0, sizeof( cCmdBuff ) );
	sprintf( cCmdBuff, "cp -p %s %s", pFileName, pEnv->cSendFileName );
	system( cCmdBuff );
	
	iResult = RTN_NG;
	for ( iRetryLoop = 0; iRetryLoop < pEnv->iSendRetry; iRetryLoop++ ) {
		// 送信状態（SEND_OK,SEND_NG）を削除
		if ( ( stat( pEnv->cSendFileOK, &stStat ) ) == 0 ) {
			remove( pEnv->cSendFileOK );
		}
		if ( ( stat( pEnv->cSendFileNG, &stStat ) ) == 0 ) {
			remove( pEnv->cSendFileNG );
		}
		
		// HULFTで送信
		memset( cCmdBuff, 0, sizeof( cCmdBuff ) );
		sprintf( cCmdBuff, "%s/utlsend -f %s",
				 pEnv->cDirHULFTBin,
				 pEnv->cHULFTFileID );
		for ( iCmdRetryLoop = 0; iCmdRetryLoop < pEnv->iCmdRetry; iCmdRetryLoop++ ) {
			iRet = system( cCmdBuff );
			// コマンドが正常に実行されたら抜ける
			if ( iRet == 0 )
				break;

			sleep( 20 );
		}
		// コマンド実行失敗ならば抜ける
		if ( iRet != 0 ) {
			//	1.03 printf -> LOG
			sprintf( gcLogMsg,	"コマンド実行失敗:[%s]", cCmdBuff);
			sFncPutLog( TRCKIND_WARNING, __FILE__,"GD102SendFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_ETC, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("コマンド実行失敗:[%s]\n", cCmdBuff);
*/
			break;
		}

		// SEND_OK or SEND_NGを待つ
		sleep( 3 );
		for ( iLoop = 0; iLoop < pEnv->iResultRetry; iLoop++ ) {
			// SEND_OK確認
			if ( ( stat( pEnv->cSendFileOK, &stStat ) ) == 0 ) {
				iResult = RTN_OK;
				remove( pEnv->cSendFileOK );
				break;
			}

			// SEND_NG確認
			if ( ( stat( pEnv->cSendFileNG, &stStat ) ) == 0 ) {
				remove( pEnv->cSendFileNG );
				break;
			}

			sleep( pEnv->iInterval );
		}
		if ( iResult == RTN_OK )
			break;

			//	1.03 printf -> LOG
			sprintf( gcLogMsg,"送信後の SEND_OK or SEND_NG 待ち[%d秒]超え", 
						iLoop * pEnv->iInterval );
			sFncPutLog( TRCKIND_TRACE, __FILE__,"GD102SendFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_APP, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("送信後の SEND_OK or SEND_NG 待ち[%d秒]超え\n",
DEL 	   iLoop * pEnv->iInterval );
*/
	}
 
	// HULFT送信用ファイルを削除
	memset( cCmdBuff, 0, sizeof( cCmdBuff ) );
	sprintf( cCmdBuff, "rm %s", pEnv->cSendFileName );
	system( cCmdBuff );

	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102SendFile", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");

	return( iResult );
}

/******************************************************************************/
/*　関 数 名　：GD102SendKekkaFile()										  */
/*　機能概要　：結果報告ファイル送信										  */
/*　入　　力　：															  */
/*　　第１引数：GD102Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int GD102SendKekkaFile(GD102Env *pEnv)
{
	int				iRet;
	char			cFileName[PATH_MAX + 1];
	int				iLoop;
	Hkkknri			*pHkkknriArrayOut;
	int				iHkkknriNumOut;
	int				iHkkknriLoop;
	ULONG			ulSt;
	ULONG			ulEd;
	char			cTimestamp[27];
	char			cCmdBuff[256];
	struct stat		stStat;
// 2006-04-13 H.Suyama Add Start
	char			iRetryLoop;
// 2006-04-13 H.Suyama Add End

	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102SendKekkaFile", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	// 報告管理情報検索
	iRet = ZdbHkkknriGD102SelectAll( &pHkkknriArrayOut, &iHkkknriNumOut );
	if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
		//異常終了
		//ログ出力
		//	1.03 printf -> LOG
		sprintf( gcLogMsg, "ZdbHkkknriGD102SelectAll error (%d)\n", iRet );
		sFncPutLog( TRCKIND_WARNING, __FILE__,"GD102SendKekkaFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_DB, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("ZdbHkkknriGD102SelectAll error (%d)\n", iRet);
*/
		return( RTN_NG );
	}

	// 報告管理情報を１件ずつ処理
	for ( iHkkknriLoop = 0;
		  iHkkknriLoop < iHkkknriNumOut;
		  iHkkknriLoop++ ) {
		// 転送開始日時を取得
		time( (long *)&ulSt );

		// 送信ファイル名の生成
/* 1.03 INTEDE DELL
DEL		sprintf( cFileName, "%s/%s",
DEL				 pEnv->cDirReqKKA,
DEL				 pHkkknriArrayOut[iHkkknriLoop].hkkflnm );
*/
			// 1.03 送信ファイル名は後ろSPACEをCUTする
		sprintf( cFileName, "%s/%.*s",
				 pEnv->cDirReqKKA,
				 strcspn( pHkkknriArrayOut[iHkkknriLoop].hkkflnm , " " ) ,
				 pHkkknriArrayOut[iHkkknriLoop].hkkflnm );
		errno=0;

		// ファイルの存在確認
// 2006-04-13 H.Suyama Change Start
#if 0
//		if ( ( stat( cFileName, &stStat ) ) != 0 ) {
//			// 異常終了	LOG
//			gintErrorCode = GD102_STSCODE_ERR_FR_FILE ;
//printf("file not exist:[%s]\n", cFileName);
//			// 報告管理情報を更新
//			GD102UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
//									GD102_DB_HKKJKFLG_ERRSEND,
//									GD102_DB_HKKERRCODE_NOFILE );
//
//			continue;
//		}
#else
		for ( iRetryLoop = 0; iRetryLoop < pEnv->iCmdRetry; iRetryLoop++ ) {
			iRet = stat( cFileName, &stStat );
			if ( iRet == 0 )
				break;
			sleep( 1 );
		}

		if ( iRet != 0 ) {
			// 異常終了	LOG
			gintErrorCode = GD102_STSCODE_ERR_FR_FILE ;

			//	1.03 printf -> LOG
			sprintf( gcLogMsg, "file not exist:[%s] err[%d]", cFileName, errno);
			sFncPutLog( TRCKIND_WARNING, __FILE__,"GD102SendKekkaFile",__LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_APP, gcLogMsg );
/* 1.03 INTEC DEL ****************************************
printf("file not exist:[%s]\n", cFileName);
switch ( iRet ) {
case EBADF:
	printf("statエラーコード:[EBADF],filedes が不正。\n");
case ENOENT:
	printf("statエラーコード:[ENOENT],file_name のパス成分が存在しないか、パスが空文字列である。\n");
case ENOTDIR:
	printf("statエラーコード:[ENOTDIR],パスの成分がディレクトリではない。\n");
case ELOOP:
	printf("statエラーコード:[ELOOP],パスを解決する際に遭遇したシンボリック・リンクが多過ぎる。\n");
case EFAULT:
	printf("statエラーコード:[EFAULT],アドレスが間違っている。\n");
case EACCES:
	printf("statエラーコード:[EACCES],許可がない。\n");
case ENOMEM:
	printf("statエラーコード:[ENOMEM],カーネルのメモリが足りない。\n");
case ENAMETOOLONG:
	printf("statエラーコード:[ENAMETOOLONG],ファイル名が長過ぎる。\n");
default:
	printf("statエラーコード:[%d],エラー内容不明\n", iRet);
}
************************************************************* */
			// 報告管理情報を更新
			GD102UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
									GD102_DB_HKKJKFLG_ERRSEND,
									GD102_DB_HKKERRCODE_NOFILE );

			continue;
		}
#endif
// 2006-04-13 H.Suyama Change End

		// ファイル送信
		if ( GD102SendFile( pEnv, cFileName ) == RTN_OK ) {
			//	1.03 printf -> LOG
			sprintf( gcLogMsg, "HULFT送信OK:[%s]", cFileName);
			sFncPutLog( TRCKIND_TRACE, __FILE__,"GD102SendKekkaFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("HULFT送信OK:[%s]\n", cFileName);
*/
			// ファイルをOKディレクトリに移動
			memset( cCmdBuff, 0, sizeof( cCmdBuff ) );
			sprintf( cCmdBuff, "mv %s %s",
					 cFileName,
					 pEnv->cDirOkKKA );
			system( cCmdBuff );
		} else {
			//	1.03 printf -> LOG
			sprintf( gcLogMsg, "HULFT送信NG:[%s]", cFileName );
			sFncPutLog( TRCKIND_WARNING, __FILE__,"GD102SendKekkaFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_APP, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("HULFT送信NG:[%s]\n", cFileName);
*/
			// 異常終了	LOG
			gintErrorCode = GD102_STSCODE_ERR_FR_FILE ;
			// ファイルをERRディレクトリに移動
			memset( cCmdBuff, 0, sizeof( cCmdBuff ) );
			sprintf( cCmdBuff, "mv %s %s",
					 cFileName,
					 pEnv->cDirErrKKA );
			system( cCmdBuff );
			
			// 報告管理情報を更新
			GD102UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
									GD102_DB_HKKJKFLG_ERRSEND,
									GD102_DB_HKKERRCODE_SENDNG );
			continue;
		}

		// 転送完了日時を取得
		time( (long *)&ulEd );

		// 転送開始日時
		GD102ConvTimestamp( ulSt, cTimestamp );
// 2006-04-05 H.Suyama Change Start
#if 0
//		ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkstdh,
//					 cTimestamp,
//					 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkstdh ) );
#else
		ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].tnsstdh,
					 cTimestamp,
					 sizeof( pHkkknriArrayOut[iHkkknriLoop].tnsstdh ) );
#endif
// 2006-04-05 H.Suyama Change End
		// 転送完了日時
		GD102ConvTimestamp( ulEd, cTimestamp );
// 2006-04-05 H.Suyama Change Start
#if 0
//		ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkeddh,
//					 cTimestamp,
//					 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkeddh ) );
#else
		ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].tnseddh,
					 cTimestamp,
					 sizeof( pHkkknriArrayOut[iHkkknriLoop].tnseddh ) );
#endif
// 2006-04-05 H.Suyama Change End
		// 報告状況フラグ
		if ( strcmp( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg, GD102_DB_HKKJKFLG_SEND_DBERR ) == 0) {
			ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg,
						 GD102_DB_HKKJKFLG_ERRFILE,
						 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg ) );
		} else {
			ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg,
						 GD102_DB_HKKJKFLG_DONE,
						 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg ) );
		}
		// 情報更新日時は関数内で設定

		// 報告管理情報を更新
		iRet = ZdbHkkknriGD102Update( &pHkkknriArrayOut[iHkkknriLoop] );
		if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
			// ロールバック
			ZdbRollback();
			// 異常終了	LOG
			//	1.03 printf -> LOG
			sprintf( gcLogMsg, "ZdbHkkknriGD102Update error (%d)\n", iRet);
			sFncPutLog( TRCKIND_WARNING, __FILE__,"GD102SendKekkaFile", __LINE__,
						EXEFLG_UPD, MYAPP_LOG_ERRCODE_DB, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("ZdbHkkknriGD102Update error (%d)\n", iRet);
*/
			return( RTN_NG );
		}

		// コミット
		ZdbCommit();
	}

	// 報告管理情報を解放
	ZbmlFree( pHkkknriArrayOut );

	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102SendKekkaFile", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：GD102BunchuFileFilter()										  */
/*　機能概要　：ディレクトリ検索用のファイルフィルタ(コールバック)			  */
/*　入　　力　：															  */
/*　　第１引数：struct dirent *pDirEnt	ディレクトリエントリ				  */
/*　出　　力　：															  */
/*　復帰情報　：int															  */
/*　　　　　　		0	: 対象外ファイル									  */
/*　　　　　　		1	: 対象ファイル										  */
/******************************************************************************/
int GD102BunchuFileFilter(struct dirent *pDirEnt)
{
//	BmlDate		today;
//	char		cToday[GD102_LEN_DATESHORT + 1];

	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102BunchuFileFilter", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	// 文字列長チェック
	if ( strlen ( pDirEnt->d_name ) < GD102_LEN_BUNCFILE ) {
		return( 0 ) ;
	}

//	// 当日日付取得
//	if ( ZbmlDateGetToday(&today) == FALSE ) {
//		return( 0 );
//	}
//	sprintf( cToday, "%04d%02d%02d", today.year, today.month, today.day);

//	// 日付チェック
//	if ( memcmp ( pDirEnt->d_name, 
//				  cToday, 
//				  strlen ( cToday ) ) != 0 ) {
//		return( 0 ) ;
//	}

	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102BunchuFileFilter", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");

	return( 1 );
}

/******************************************************************************/
/*　関 数 名　：GD102SendBunchuFile()										  */
/*　機能概要　：分注結果要求情報ファイル送信								  */
/*　入　　力　：															  */
/*　　第１引数：GD102Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int GD102SendBunchuFile(GD102Env *pEnv)
{
	int				iFileCnt;
	int				iFileLoopIdx;
	char			cFileName[PATH_MAX + 1];
	struct dirent	**pDirEnt;
	char			cCmdBuff[256];

	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102SendBunchuFile", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	// フィルタにより、分注結果要求情報ファイルのみ検索
	if ( ( iFileCnt = scandir( pEnv->cDirReqBUNC,
							   &pDirEnt,
							   (void *)GD102BunchuFileFilter,
							   alphasort ) ) < 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD102_STSCODE_ERR_DIR;
		return( RTN_NG );
	}

	// 見つかった件数分送信
	for ( iFileLoopIdx = 0; iFileLoopIdx < iFileCnt; iFileLoopIdx++ ) {
		sprintf( cFileName, "%s/%s", pEnv->cDirReqBUNC, pDirEnt[iFileLoopIdx]->d_name );

		// ファイル送信
		memset( cCmdBuff, 0, sizeof( cCmdBuff ) );
		if ( GD102SendFile( pEnv, cFileName ) == RTN_OK ) {
			//	1.03 printf -> LOG
			sprintf( gcLogMsg, "HULFT送信OK:[%s]", cFileName);
			sFncPutLog( TRCKIND_WARNING, __FILE__,"GD102SendBunchuFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("HULFT送信OK:[%s]\n", cFileName);
*/
			// ファイルの移動先をOKディレクトリに設定
			sprintf( cCmdBuff, "mv %s %s",
					 cFileName,
					 pEnv->cDirOkBUNC );
		} else {
			//	1.03 printf -> LOG
			sprintf( gcLogMsg, "HULFT送信NG:[%s]", cFileName );
			sFncPutLog( TRCKIND_WARNING, __FILE__,"GD102SendBunchuFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_APP, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("HULFT送信NG:[%s]\n", cFileName);
*/
			// 異常終了	LOG
			gintErrorCode = GD102_STSCODE_ERR_FR_FILE ;
			// ファイルの移動先をERRディレクトリに設定
			sprintf( cCmdBuff, "mv %s %s",
					 cFileName,
					 pEnv->cDirErrBUNC );
		}
		// ファイルを移動
		system( cCmdBuff );
		
		// 内部メモリ解放
		ZbmlFree( pDirEnt[iFileLoopIdx] );
	}

	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102SendBunchuFile", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：GD102IraiFileFilter()										  */
/*　機能概要　：ディレクトリ検索用のファイルフィルタ(コールバック)			  */
/*　入　　力　：															  */
/*　　第１引数：struct dirent *pDirEnt	ディレクトリエントリ				  */
/*　出　　力　：															  */
/*　復帰情報　：int															  */
/*　　　　　　		0	: 対象外ファイル									  */
/*　　　　　　		1	: 対象ファイル										  */
/******************************************************************************/
int GD102IraiFileFilter(struct dirent *pDirEnt)
{
//	BmlDate		today;
//	char		cToday[GD102_LEN_DATESHORT + 1];

	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102IraiFileFilter", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	// 文字列長チェック
	if ( strlen ( pDirEnt->d_name )  < GD102_LEN_IRAIFILE ) {
		return( 0 ) ;
	}

//	// 当日日付取得
//	if ( ZbmlDateGetToday(&today) == FALSE ) {
//		return( 0 );
//	}
//	sprintf( cToday, "%04d%02d%02d", today.year, today.month, today.day);

//	// 日付チェック
//	if ( memcmp ( pDirEnt->d_name, 
//				  cToday, 
//				  strlen ( cToday ) ) != 0 ) {
//		return( 0 ) ;
//	}

	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102IraiFileFilter", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");

	return( 1 );
}

/******************************************************************************/
/*　関 数 名　：GD102SendIraiFile()											  */
/*　機能概要　：依頼項目要求情報ファイル送信								  */
/*　入　　力　：															  */
/*　　第１引数：GD102Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int GD102SendIraiFile(GD102Env *pEnv)
{
	int				iFileCnt;
	int				iFileLoopIdx;
	char			cFileName[PATH_MAX + 1];
	struct dirent	**pDirEnt;
	char			cCmdBuff[256];

	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102SendIraiFile", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	// フィルタにより、依頼項目要求情報ファイルのみ検索
	if ( ( iFileCnt = scandir( pEnv->cDirReqIRAI,
							   &pDirEnt,
							   (void *)GD102IraiFileFilter,
							   alphasort ) ) < 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD102_STSCODE_ERR_DIR;
		return( RTN_NG );
	}

	// 見つかった件数分送信
	for ( iFileLoopIdx = 0; iFileLoopIdx < iFileCnt; iFileLoopIdx++ ) {
		sprintf( cFileName, "%s/%s", pEnv->cDirReqIRAI, pDirEnt[iFileLoopIdx]->d_name );

		// ファイル送信
		memset( cCmdBuff, 0, sizeof( cCmdBuff ) );
		if ( GD102SendFile( pEnv, cFileName ) == RTN_OK ) {
			//	1.03 printf -> LOG
			sprintf( gcLogMsg, "HULFT送信OK:[%s]", cFileName);
			sFncPutLog( TRCKIND_TRACE, __FILE__,"GD102SendIraiFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("HULFT送信OK:[%s]\n", cFileName);
*/
			// ファイルの移動先をOKディレクトリに設定
			sprintf( cCmdBuff, "mv %s %s",
					 cFileName,
					 pEnv->cDirOkIRAI );
		} else {
			//	1.03 printf -> LOG
			sprintf( gcLogMsg, "HULFT送信NG:[%s]\n", cFileName );
			sFncPutLog( TRCKIND_WARNING, __FILE__,"GD102SendIraiFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_APP, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("HULFT送信NG:[%s]\n", cFileName);
*/
			// 異常終了	LOG
			gintErrorCode = GD102_STSCODE_ERR_FR_FILE ;
			// ファイルの移動先をERRディレクトリに設定
			sprintf( cCmdBuff, "mv %s %s",
					 cFileName,
					 pEnv->cDirErrIRAI );
		}
		// ファイルを移動
		system( cCmdBuff );
		
		// 内部メモリ解放
		ZbmlFree( pDirEnt[iFileLoopIdx] );
	}

	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102SendIraiFile", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");

	return( RTN_OK );
}

/**********************************************************************************/
/*　関 数 名　：GD102OtherKkaFileFilter()					  */
/*　機能概要　：ディレクトリ検索用のファイルフィルタ(コールバック)		  */
/*　入　　力　：								  */
/*　　第１引数：struct dirent *pDirEnt	ディレクトリエントリ			  */
/*　出　　力　：								  */
/*　復帰情報　：int								  */
/*　　　　　　		0	: 対象外ファイル				  */
/*　　　　　　		1	: 対象ファイル					  */
/**********************************************************************************/
int GD102OtherKkaFileFilter(struct dirent *pDirEnt)
{
	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102OtherKkaFileFilter", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	// 文字列長チェック
	if ( strlen ( pDirEnt->d_name )  < GD102_LEN_OTHERKKAFILE ) {
		return( 0 ) ;
	}

	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102OtherKkaFileFilter", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");

	return( 1 );
}

/**********************************************************************************/
/*　関 数 名　：GD102SendOtherKkaFile()						  */
/*　機能概要　：他サテライト結果要求情報ファイル送信				  */
/*　入　　力　：								  */
/*　　第１引数：GD102Env *pEnv		プログラム環境構造体			  */
/*　出　　力　：								  */
/*　復帰情報　：int								  */
/*　　　　　　		RTN_OK	: 正常終了					  */
/*　　　　　　		RTN_NG	: 異常終了					  */
/**********************************************************************************/
int GD102SendOtherKkaFile(GD102Env *pEnv)
{
	int		iFileCnt;
	int		iFileLoopIdx;
	char		cFileName[PATH_MAX + 1];
	struct dirent	**pDirEnt;
	char		cCmdBuff[256];

	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102SendOtherKkaFile", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	// フィルタにより、依頼項目要求情報ファイルのみ検索
	if ( ( iFileCnt = scandir( pEnv->cDirReqOTHERKKA,
							   &pDirEnt,
							   (void *)GD102OtherKkaFileFilter,
							   alphasort ) ) < 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD102_STSCODE_ERR_DIR;
		return( RTN_NG );
	}

	// 見つかった件数分送信
	for ( iFileLoopIdx = 0; iFileLoopIdx < iFileCnt; iFileLoopIdx++ ) {
		sprintf( cFileName, "%s/%s", pEnv->cDirReqOTHERKKA, pDirEnt[iFileLoopIdx]->d_name );

		// ファイル送信
		memset( cCmdBuff, 0, sizeof( cCmdBuff ) );
		if ( GD102SendFile( pEnv, cFileName ) == RTN_OK ) {
			//	1.03 printf -> LOG
			sprintf( gcLogMsg, "HULFT送信OK:[%s]", cFileName);
			sFncPutLog( TRCKIND_TRACE, __FILE__,"GD102SendOtherKkaFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, gcLogMsg );
			// ファイルの移動先をOKディレクトリに設定
			sprintf( cCmdBuff, "mv %s %s",
					 cFileName,
					 pEnv->cDirOkOTHERKKA );
		} else {
			sprintf( gcLogMsg, "HULFT送信NG:[%s]\n", cFileName );
			sFncPutLog( TRCKIND_WARNING, __FILE__,"GD102SendOtherKkaFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_APP, gcLogMsg );
			// 異常終了	LOG
			gintErrorCode = GD102_STSCODE_ERR_FR_FILE ;
			// ファイルの移動先をERRディレクトリに設定
			sprintf( cCmdBuff, "mv %s %s",
					 cFileName,
					 pEnv->cDirErrOTHERKKA );
		}
		// ファイルを移動
		system( cCmdBuff );
		
		// 内部メモリ解放
		ZbmlFree( pDirEnt[iFileLoopIdx] );
	}

	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102SendOtherKkaFile", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");

	return( RTN_OK );
}
/******************************************************************************/
/*　関 数 名　：sFncShmCrt()												  */
/*　機能概要　：共有メモリ生成												  */
/*　入　　力　：															  */
/*　　第１引数：GD102Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：なし														  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
static int sFncShmCrt( GD102Env *pEnv )
{
	int	 *shmData;

	// 取得
	pEnv->shm_Id = shmget( (key_t)pEnv->shm_Key,
							GD102_SHM_SIZE,
							0666 | IPC_CREAT );
	if ( pEnv->shm_Id < 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD102_STSCODE_ERR_SHM_GET;
		return( RTN_NG );
	}

	// アタッチ
	shmData = ( int * ) shmat( pEnv->shm_Id, 0 , 0 );
	if ( shmData == ( int * )-1 ) {
		// 異常終了	LOG
		gintErrorCode = GD102_STSCODE_ERR_SHM_AT;
		return( RTN_NG );
	}
loging ( "stocker : 共有メモリ[CRT] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n",
		 pEnv->shm_Key, pEnv->shm_Id, *shmData, shmData );

	// 値設定
	*shmData = 0;

	// デタッチ
	if ( shmdt( shmData ) == -1 ) {
		// 異常終了	LOG
		gintErrorCode = GD102_STSCODE_ERR_SHM_DT;
		return( RTN_NG );
	}

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：sFncShmGet()												  */
/*　機能概要　：共有メモリ取得												  */
/*　入　　力　：															  */
/*　　第１引数：GD102Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　　第２引数：int *pshmData		値										  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
static int sFncShmGet( GD102Env *pEnv, int *pshmData )
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
		gintErrorCode = GD102_STSCODE_ERR_SHM_AT;
		return( RTN_NG );
	}

	// 値設定
	*pshmData = *shmData;

loging ( "stocker : 共有メモリ[GET] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n",
		 pEnv->shm_Key, pEnv->shm_Id, *shmData, shmData );
	// デタッチ
	if ( shmdt( shmData ) == -1 ) {
		// 異常終了	LOG
		gintErrorCode = GD102_STSCODE_ERR_SHM_DT;
		return( RTN_NG );
	}

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：sFncShmDel()												  */
/*　機能概要　：共有メモリ削除												  */
/*　入　　力　：															  */
/*　　第１引数：GD102Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
static int sFncShmDel( GD102Env *pEnv )
{
	int	 *shmData;

loging ( "%s : 共有メモリ[DEL] shmKey[%d]-ID[%d]\n",
		 MYAPP_APP_NAME, pEnv->shm_Key, pEnv->shm_Id);
	// 削除
	if ( shmctl( pEnv->shm_Id, IPC_RMID, NULL) < 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD102_STSCODE_ERR_SHM_DEL;
		//	1.03 LOG
		sprintf( gcLogMsg, "共有メモリ削除 error errno[%d]", errno );
		sFncPutLog( TRCKIND_WARNING, __FILE__,"sFncShmDel", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_APP, gcLogMsg );

		return( RTN_NG );
	}
	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：_sFncEnvDip()												  */
/*　機能概要　：プログラム環境変数出力関数【トレース用】					  */
/*　入　　力　：															  */
/*　　第１引数：GD102Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：無し														  */
/******************************************************************************/
static void _sFncEnvDip( GD102Env *pEnv )
{
//#if defined ( _TRACE )
	loging( "########## GD102 - _sFncEnvDip ##########\n" );
	loging( "\t%s : [%s]\n", GD102_PRM_DBNAME,		 pEnv->cDBName );
	loging( "\t%s : [%s]\n", GD102_PRM_DBUSER,		 pEnv->cDBUser );
	loging( "\t%s : [%s]\n", GD102_PRM_DBPAWD,		 pEnv->cDBPawd );
	loging( "\t%s : [%s]\n", GD102_PRM_SLEEP_SEC,	  pEnv->iSleepSec );
	loging( "\t%s : [%s]\n", GD102_PRM_SHM_KEY,	pEnv->shm_Key );
	loging( "\t%s : [%s]\n", GD102_PRM_FILE_DBG,	pEnv->cDebugLogName );
	loging( "\t%s : [%s]\n", GD102_PRM_FILE_TR,	pEnv->cTraceLogName );
	loging( "\t%s : [%s]\n", GD102_PRM_FILE_ACS,	pEnv->cAccessLogName );
	loging( "\t%s : [%s]\n", GD102_PRM_FILE_ERR,	pEnv->cErrorLogName );
	loging( "\t%s : [%s]\n", GD102_PRM_UP_ID,		pEnv->cUpdateId );
	loging( "\t%s : [%s]\n", GD102_PRM_UP_NM,		pEnv->cUpdateName );
	loging( "\t%s : [%s]\n", GD102_PRM_PROC_MD,	pEnv->proc_mode );
	loging( "########## GD102 - _sFncEnvDip ##########\n" );
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
	GD102Env	stEnv;

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


