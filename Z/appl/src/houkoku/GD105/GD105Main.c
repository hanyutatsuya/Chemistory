/********************************************************************/
/*																	*/
/*		ＢＭＬ様向け検査システム									*/
/*																	*/
/*		システム名	：次世代システム								*/
/*		ファイル名	：GD105Main.c									*/
/*		概要		：結果報告ファイル作成処理						*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	作成日			名前			修正内容				*/
/* ---------------------------------------------------------------- */
/*  1.00	2006/02/27		H.Suyama		Create					*/
/*  1.01    2006/04/01      H.Suyama        システム管理情報の送信  */
/*                          通番を取得直後に更新                    */
/*  1.02    2006/04/06      H.Suyama        エラーコード修正		*/
/*                                          トレーラの設定値修正	*/
/*  1.03    2006/04/06      H.Suyama        ファイル設定内容修正	*/
/*  1.04    2006/04/07      H.Suyama        物理レコード件数修正	*/
/*  1.05    2006/04/20      H.Suyama        ヘッダパラメータ１修正	*/
/*                                          １桁の項目NULL→' '		*/
/*                                          結果状況最終時同項目	*/
/*											レコードを'M'に更新		*/
/*  1.06    2006/05/03      INTEC.INC       施設別換算処理追加,LOG  */
/*  1.07    2006/06/06      INTEC.INC       ファイル名転送時の考慮  */
/*  1.09    2006/07/25      INTEC.INC       検査結果２は左から編集  */
/*  1.10    2006/08/23      INTEC.INC       再転送時ファイル名変更  */
/*  1.11    2006/08/29      INTEC.INC       結果修正FLGはMAXから    */
/*  1.12    2006/09/04      INTEC.INC       保留以外出力件数0の考慮 */
/*  1.13    2006/09/13      INTEC.INC       結果のcommitを1000件毎に*/
/*  1.14    2006/12/08      INTEC.INC       DBエラー時異常終了させる*/
/*  2.00    2009/05/19      K.Moriya        結果変換マスタ対応      */
/********************************************************************/

/********************************************************************/
/*	インクルード宣言												*/
/********************************************************************/
#include <time.h>
#include <errno.h>							// 1.07 INTEC ADD
//#include "bml_misc.h"
#include "bml_date.h"
#include "bmllog.h"
#include "bmlprm.h"
#include "GD105Main.h"
#include "GD105Hkkknri.h"

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
GD105_STSCODE		gintErrorCode;
struct stcLogMember	gstLogMem;
char        G_msg[256];     // 1.06 ADD LogMessage
/* 2.00 2009.05.19 結果変換マスタ対応 START */
Kkaconvmst	*g_pKkaconvmst = NULL;	/* 結果変換マスタ構造体 */
int			g_iNumOut;				/* 結果変換マスタ全件数 */
/* 2.00 2009.05.19 結果変換マスタ対応 END */

/******************************************************************************/
/*　関 数 名　：GD105ConvTimestamp()										  */
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
void GD105ConvTimestamp(ULONG ulTm, char *pDest)
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

/******************************************************************************/
/*　関 数 名　：GD105ConvNumber()											  */
/*　機能概要　：依頼書No、検体No変換関数									  */
/*　入　　力　：															  */
/*　　第２引数：char *pSrc			変換前文字列							  */
/*　　　　　　						[1][2][3][4][5][6][7][8][9][10][11]\0	  */
/*　出　　力　：															  */
/*　　第１引数：char *pDest			変換後文字列							  */
/*　　　　　　						[3][4][5] 0  0 [6][7][8][9][10][11]		  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int GD105ConvNumber(char *pDest, char *pSrc)
{
	// ポインタのチェック
	if ( pDest == NULL || pSrc == NULL ) {
		return( RTN_NG );
	}

	// 変換前文字列の長さチェック
	if ( strlen( pSrc ) < GD105_LEN_NOITEM ) {
		return( RTN_NG );
	}

	memcpy( &pDest[GD105_POS_DESTNO1], &pSrc[GD105_POS_SRCNO1], GD105_LEN_SRCNO1 );
	memcpy( &pDest[GD105_POS_DESTNO2], GD105_DATA_STR00, strlen( GD105_DATA_STR00 ) );
	memcpy( &pDest[GD105_POS_DESTNO3], &pSrc[GD105_POS_SRCNO2], GD105_LEN_SRCNO2 );

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：GD105CopyFromLeft()											  */
/*　機能概要　：指定文字列の左から指定桁数をコピーする						  */
/*　入　　力　：															  */
/*　　第２引数：char *pSrc			コピー元文字列							  */
/*　　第３引数：int iSize			コピー桁数								  */
/*　　第４引数：BOOL bMbFlg			マルチバイトフラグ						  */
/* 　　　　　		TRUE	: 考慮する										  */
/* 　　　　　		FALSE	: 無視する										  */
/*　出　　力　：															  */
/*　　第１引数：char *pDest			コピー後文字列							  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int GD105CopyFromLeft(char *pDest, char *pSrc, int iSize, BOOL bMbFlg)
{
	int	iLoop;
	int	iCopySize;

	// ポインタのチェック
	if ( pDest == NULL || pSrc == NULL ) {
		return( RTN_NG );
	}

	// コピー元文字列がコピー桁数に満たない場合
	if ( strlen( pSrc ) <= iSize ) {
		// すべてコピーする
		iCopySize = strlen( pSrc );
	} else {
		iCopySize = iSize;
		// マルチバイトを考慮する場合
		if ( bMbFlg ) {
			// 漢字判定処理
			for ( iLoop = 0; iLoop < iSize; iLoop++ ) {
				if ( isAscii(pSrc[iLoop]) == 0 ) {
					++iLoop;
					if ( iLoop == iLoop ) {
						--iCopySize;
						break;
					}
				}
			}
		}
	}
	memcpy( pDest, pSrc, iCopySize );

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：GD105CopyFromRight()										  */
/*　機能概要　：指定文字列の右から指定桁数をコピーする						  */
/*　入　　力　：															  */
/*　　第２引数：char *pSrc			コピー元文字列							  */
/*　　第３引数：int iSize			コピー桁数								  */
/*　　第４引数：BOOL bMbFlg			マルチバイトフラグ						  */
/* 　　　　　		TRUE	: 考慮する										  */
/* 　　　　　		FALSE	: 無視する										  */
/*　出　　力　：															  */
/*　　第１引数：char *pDest			コピー後文字列							  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int GD105CopyFromRight(char *pDest, char *pSrc, int iSize, BOOL bMbFlg)
{
	int 	iTargetPos;
	int	iLoop;
	int	iCopySize;

	// ポインタのチェック
	if ( pDest == NULL || pSrc == NULL ) {
		return( RTN_NG );
	}

	// コピー元文字列がコピー桁数に満たない場合
	if ( strlen( pSrc ) <= iSize ) {
		// すべてコピーする
		iTargetPos = 0;
		iCopySize = strlen( pSrc );
	} else {
		iTargetPos = strlen( pSrc ) - iSize;
		iCopySize = iSize;
		// マルチバイトを考慮する場合
		if ( bMbFlg ) {
			// 漢字判定処理
			for ( iLoop = 0; iLoop < strlen( pSrc ); iLoop++ ) {
				if ( isAscii(pSrc[iLoop]) == 0 ) {
					++iLoop;
					if ( iLoop == iTargetPos ) {
						++iTargetPos;
						--iCopySize;
						break;
					}
				}
			}
		}
	}
	memcpy( pDest, &pSrc[iTargetPos], iCopySize );

	return( RTN_OK );
}

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
/*　　第３引数：GD105Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int initFunction( int argc, char *argv[], GD105Env *pEnv )
{
	char	cPrmBuf[256];
	char	*lc_login;

	// 初期化
	// エラーステータス変更
	gintErrorCode = 0;
	// プログラム環境変数初期化
	memset( pEnv, '\0', sizeof( GD105Env ) );

	// ログオープン
	// 1.06 UPD	if( ZbmlOpenLog( MYAPP_LOGINIFILE ) != 0 ) [
	lc_login= EnvRef( MYAPP_LOGINIFILE );
	if( ZbmlOpenLog( lc_login ) != 0 ) {
		return( RTN_NG );
	}

	// ログ情報初期設定
	memset( &gstLogMem, '\0', sizeof( gstLogMem ) );
	if ( ( lc_login = getenv( "LOGNAME" ) ) != NULL ) {
		strcpy( gstLogMem.pcLoginId, lc_login );
	}
	strcpy( gstLogMem.pcAppName, MYAPP_APP_NAME );

#ifdef _TRACE
	// 開始ログ出力
	sFncPutLog( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"プログラム起動" );
#endif

/*
	// 引数数チェック
	if ( argc != 2 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_USEGE;
		sFncPutLog( TRCKIND_ERROR, __FILE__, "initFunction", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"コマンドパラメータに誤りがあります" );
		return( RTN_NG );
	}
*/
	// パラメータファイル名退避
	lc_login= EnvRef( MYAPP_LOGINIFILE );
	if ( argc >= 2 ) {
/* 1.06
DEL		pEnv->pcFileNamePRM = argv[1];
*/
		pEnv->pcFileNamePRM = EnvRef( argv[1] );
	} else {
/* 1.06
DEL		pEnv->pcFileNamePRM = MYAPP_INIFILE;
*/
		pEnv->pcFileNamePRM = EnvRef( MYAPP_INIFILE );
	}

	// パラメータファイルオープン
	// 1.06 UPD pEnv->bp = ZbmlPrmOpen( pEnv->pcFileNamePRM );
	pEnv->bp = ZbmlPrmOpen( pEnv->pcFileNamePRM );
	if ( pEnv->bp == NULL ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_FILE;
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZZbmlPrmOpen", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"パラメータファイルのオープンに失敗しました[%s]", 
					pEnv->pcFileNamePRM );
		return( RTN_NG );
	}

	// データベース接続名
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_DBNAME,
						 pEnv->cDBName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ログインユーザ
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_DBUSER,
						pEnv->cDBUser ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ログインパスワード
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_DBPAWD,
						pEnv->cDBPawd ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 報告データファイル出力ディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_DIR_DATAFILE,
						pEnv->cDirDataFile ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 転送データファイル出力ディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_DIR_TODAY,
						pEnv->cDirToday ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 転送データファイル過去ディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_DIR_OLDDAY,
						pEnv->cDirOldday ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 転送データファイル送信ディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_DIR_SENDFILE,
						pEnv->cDirSendFile ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 転送データファイルREQUESTディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_DIR_SENDREQ,
						pEnv->cDirSendREQ ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 転送データファイルOKディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_DIR_SENDOK,
						pEnv->cDirSendOK ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 転送データファイルERRディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_DIR_SENDERR,
						pEnv->cDirSendERR ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// データフローＩＤ
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_DATAFLOWID,
						pEnv->cDataFlowID ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 送信元ＩＤ
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_SENDID_MOTO,
						pEnv->cSendIDMoto ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 送信先ＩＤ
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_SENDID_SAKI,
						pEnv->cSendIDSaki ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// デバッグログファイル
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_FILE_DBG,
						pEnv->cDebugLogName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// トレースログファイル
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_FILE_TR,
						pEnv->cTraceLogName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// アクセスログファイル
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_FILE_ACS,
						pEnv->cAccessLogName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// エラーログファイル
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_FILE_ERR,
						pEnv->cErrorLogName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 共有メモリキー取得
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_SHM_KEY,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->shm_Key = atoi( cPrmBuf );
	// スリープ時間（秒）取得
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_SLEEP_SEC,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iSleepSec= atoi( cPrmBuf );
	// 更新者ID
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_UP_ID,
						pEnv->cUpdateId ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 更新者名
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_UP_NM,
						pEnv->cUpdateName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 実行モード
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_PROC_MD,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->proc_mode= atoi( cPrmBuf );

	// 1.13 ADD 結果情報 一括COMMIT件数
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_COMMIT_SU,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iCommitSu=atoi( cPrmBuf );

	// パラメータファイルクローズ
	ZbmlPrmClose( pEnv->bp );

	// 共有メモリ生成
	if ( sFncShmCrt( pEnv ) != RTN_OK ) {
		return( RTN_NG );
	}

#ifdef _TRACE
	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "initFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function" );
#endif

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：GD105UpdateHkkknriSts()										  */
/*　機能概要　：報告管理情報エラー更新										  */
/*　入　　力　：															  */
/*　　第１引数：Hkkknri *pHkkknri	報告管理情報環境構造体					  */
/*　　第２引数：char *pHkkjkflg		報告状況フラグ							  */
/*　　第３引数：char *pHkkerrcode	報告エラーコード						  */
/*　出　　力　：															  */
/*　復帰情報　：なし														  */
/******************************************************************************/
void GD105UpdateHkkknriSts( Hkkknri *pHkkknri, char *pHkkjkflg, char *pHkkerrcode )
{
	int			iRet;

	// 報告管理情報を更新
	ZbmlInfocpy( pHkkknri->hkkjkflg, pHkkjkflg, sizeof( pHkkknri->hkkjkflg ) );
	ZbmlInfocpy( pHkkknri->hkkerrcode, pHkkerrcode, sizeof( pHkkknri->hkkerrcode ) );

	// 報告管理情報を更新
	iRet = ZdbHkkknriGD105UpdateSts( pHkkknri );
	if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
		// ロールバック
		ZdbRollback();
		// 異常終了	LOG
// 1.06 printf("ZdbHkkknriGD105UpdateSts error (%d)\n", iRet);
		// 1.06 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105UpdateHkkknriSts", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"ZdbHkkknriGD105UpdateSts error [%d]", iRet );
	} else {
		// コミット
		ZdbCommit();
	}
}

/******************************************************************************/
/*　関 数 名　：mainFunction()												  */
/*　機能概要　：メイン処理関数												  */
/*　入　　力　：															  */
/*　　第１引数：GD105Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int mainFunction( GD105Env *pEnv )
{
	int			iRet;
	Sysknrmst	stSysknrmst;
	Hkkknri		*pHkkknriArrayOut;
	int			iHkkknriNumOut;
	int			iHkkknriLoop;
	Kekka		stKekkaKey;
	Kekka		*pKekkaArrayOut;
	int			iKekkaNumOut;
	ULONG		ulNow;
	ULONG		ulSt;
	ULONG		ulEd;
	char		cTimestamp[27];
	int			iHkkssknsu;
	int			iHkkhrysu;
	char		cDataFile[PATH_MAX + 1];
	int			li_stopFlg = 0;

#ifdef _TRACE
	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");
#endif

	if( iRet = ZdbConnect( pEnv->cDBName,
						   pEnv->cDBUser,
						   pEnv->cDBPawd ) ) {
		// 異常終了	LOG
// 1.06 DELL printf("ZdbConnect error (%d)\n", iRet);
		// 1.06 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"ZdbConnect error [%d]", iRet );
		return( RTN_NG );
	}

/* 2.00 2009.05.19 結果変換マスタ対応 START */
	/*************************************************************************/
	/* 結果変換マスタ取得                                                    */
	/* ※ 結果変換マスタを全件取得し、グローバル変数に件数と一緒に格納する。 */
	/*************************************************************************/
	iRet = mGD105_KKACONVMST_SelAll( &g_pKkaconvmst, &g_iNumOut );
	if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
		//異常終了
		//ログ出力
		sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction", __LINE__,
				EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"mGD105_KKACONVMST_SelAll ERROR iRet = [%d]", iRet );
		return( RTN_NG );
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
			"g_iNumOut = [%d]", g_iNumOut );

	for (iRet = 0; iRet < g_iNumOut; iRet++)
	{
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].knsgrp     = [%s]", iRet, g_pKkaconvmst[iRet].knsgrp );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].kmkcd      = [%s]", iRet, g_pKkaconvmst[iRet].kmkcd );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].sstcd      = [%s]", iRet, g_pKkaconvmst[iRet].sstcd );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].no         = [%d]", iRet, g_pKkaconvmst[iRet].no );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].sbtkbn     = [%c]", iRet, g_pKkaconvmst[iRet].sbtkbn );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].age        = [%s]", iRet, g_pKkaconvmst[iRet].age );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].agekbn     = [%c]", iRet, g_pKkaconvmst[iRet].agekbn );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].sc         = [%s]", iRet, g_pKkaconvmst[iRet].sc );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].tj         = [%s]", iRet, g_pKkaconvmst[iRet].tj );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].tjtni      = [%c]", iRet, g_pKkaconvmst[iRet].tjtni );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].tntme      = [%s]", iRet, g_pKkaconvmst[iRet].tntme );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].tntni      = [%c]", iRet, g_pKkaconvmst[iRet].tntni );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].tnryo      = [%s]", iRet, g_pKkaconvmst[iRet].tnryo );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].tnryotni   = [%c]", iRet, g_pKkaconvmst[iRet].tnryotni );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].knskka1    = [%s]", iRet, g_pKkaconvmst[iRet].knskka1 );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].knskka2    = [%s]", iRet, g_pKkaconvmst[iRet].knskka2 );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].knskka2kbn = [%s]", iRet, g_pKkaconvmst[iRet].knskka2kbn );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].kkahskcd   = [%s]", iRet, g_pKkaconvmst[iRet].kkahskcd );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].hjkka      = [%s]", iRet, g_pKkaconvmst[iRet].hjkka );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].kaiymd     = [%s]", iRet, g_pKkaconvmst[iRet].kaiymd );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].haiymd     = [%s]", iRet, g_pKkaconvmst[iRet].haiymd );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].hnktntid   = [%s]", iRet, g_pKkaconvmst[iRet].hnktntid );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].ksndh      = [%s]", iRet, g_pKkaconvmst[iRet].ksndh );
	}
#endif
/* 2.00 2009.05.19 結果変換マスタ対応 END */

	// 報告管理情報テーブル監視
	// 永久ループ、停止コマンドで終了
	while ( 1 ) {
		// 停止コマンド確認
		if ( sFncShmGet( pEnv, &li_stopFlg ) != RTN_OK ) {
			// 1.06 異常終了	LOG
			sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"sFncShmGet error" );
			return( RTN_NG );
		}
		if ( li_stopFlg == 1 ) {
			break;
		}

		// 報告管理情報検索
		iRet = ZdbHkkknriGD105SelectAll( &pHkkknriArrayOut, &iHkkknriNumOut );
		if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
			//異常終了
			//ログ出力
			// 1.06 異常終了	LOG
			sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction", __LINE__,
					EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
					"ZdbHkkknriGD105SelectAll error [%d]", iRet );
			return( RTN_NG );
		}
		if ( iRet == HRC_SQL_NORMAL ) {
			// 報告管理情報を１件ずつ処理
			for ( iHkkknriLoop = 0;
				  iHkkknriLoop < iHkkknriNumOut;
				  iHkkknriLoop++ ) {
				// システム管理情報取得
                iRet = ZdbSysknrmstSelect( &stSysknrmst );
				if ( iRet != HRC_SQL_NORMAL ) {
					// 異常終了	LOG
// 1.06 DELL printf("ZdbSysknrmstSelect error (%d)\n", iRet);
					// 1.06 異常終了	LOG
					sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
							"ZdbSysknrmstSelect error [%d]", iRet );
					return( RTN_NG );
				}

				// システム管理情報の送信通番がMAXの場合はエラー
				if ( stSysknrmst.ssntubn == GD105_DB_SSNTUBN_MAX ) {
					// 異常終了	LOG
// 1.06 DELL	printf("SYSKNRMST.SSTUBN is max\n");
					// 1.06 異常終了	LOG
					sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
							"SYSKNRMST.SSTUBN is max " );
					// 報告管理情報を更新
					GD105UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
											GD105_DB_HKKJKFLG_ERRFILE,
											GD105_DB_HKKERRCODE_SEQMAX );

// 2006-04-01 H.Suyama Add Start
					continue;
// 2006-04-01 H.Suyama Add End
				}
				++stSysknrmst.ssntubn;
// 2006-04-01 H.Suyama Add Start
				// システム管理情報を更新
				iRet = ZdbSysknrmstUpdate( &stSysknrmst );
				if ( iRet != HRC_SQL_NORMAL ) {
					// ロールバック
					ZdbRollback();

					// 異常終了	LOG
//1.06 DELL printf("ZdbSysknrmstUpdate error (%d)\n", iRet);
					// 1.06 異常終了	LOG
					sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
							"ZdbSysknrmstUpdate error [%d]", iRet );

					return( RTN_NG );
				}

				// コミット
				ZdbCommit();
// 2006-04-01 H.Suyama Add End

				// 作成開始日時を取得
				time( (long *)&ulSt );

				// 作成件数、保留件数をクリア
				iHkkssknsu = 0;
				iHkkhrysu = 0;
				memset( cDataFile, 0, sizeof( cDataFile ) );

				// 結果情報検索（送信対象のみ）
				// 報告区分を結果状況コードの値にあわせる
// 2006-04-20 H.Suyama Change Start
#if 0
//				switch ( pHkkknriArrayOut[iHkkknriLoop].hkkkbn ) {
//				case '1':	// 最終
//					pHkkknriArrayOut[iHkkknriLoop].hkkkbn = '3';
//					break;
//				case '2':	// 中間
//					pHkkknriArrayOut[iHkkknriLoop].hkkkbn = '1';
//					break;
//				}
#else
				switch ( pHkkknriArrayOut[iHkkknriLoop].hkkkbn ) {
				case GD105_DB_HKKKBN_LAST:	// 最終
					pHkkknriArrayOut[iHkkknriLoop].hkkkbn = GD105_DB_KKAJKCD_LAST;
					break;
				case GD105_DB_HKKKBN_CYUU:	// 中間
					pHkkknriArrayOut[iHkkknriLoop].hkkkbn = GD105_DB_KKAJKCD_CYUU;
					break;
				}
#endif
// 2006-04-20 H.Suyama Change End

				// 再転送の場合は、再転送処理を呼び出す
				if ( pHkkknriArrayOut[iHkkknriLoop].hkkjkn == GD105_DB_HKKJKN_RESEND ) {
					if ( GD105ResendFile( pEnv,
										  &stSysknrmst,
						 				  &pHkkknriArrayOut[iHkkknriLoop] ) == RTN_OK ) {
						// 報告ファイル名
						// GD105ResendFile内で設定
						// 報告状況フラグ
						ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg,
									 GD105_DB_HKKJKFLG_CHUU,
									 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg ) );
						// 情報更新日時は関数内で設定

						// 報告管理情報を更新
						iRet = ZdbHkkknriGD105UpdateNormal( &pHkkknriArrayOut[iHkkknriLoop] );
						if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
							// ロールバック
							ZdbRollback();
							// 異常終了	LOG
//1.06 DELL printf("ZdbHkkknriGD105UpdateNormal error (%d)\n", iRet);
							// 1.06 異常終了	LOG
							sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction",
									 __LINE__,
									EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
									"ZdbHkkknriGD105UpdateNormal error [%d]", 
									iRet );

							return( RTN_NG );
						}

						// コミット
						ZdbCommit();
					} else {
						// 異常終了	LOG
// 1.06 DELL printf("GD105ResendFile error\n");
						// 1.06 異常終了	LOG
						sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction",
								 __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"GD105ResendFile error " );

						// 報告管理情報を更新
						GD105UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
												GD105_DB_HKKJKFLG_ERRFILE,
												GD105_DB_HKKERRCODE_RESEND );
					}
					continue;
				}

				// 報告条件により、検索方法を切替える
				switch ( pHkkknriArrayOut[iHkkknriLoop].hkkjkn ) {
				case GD105_DB_HKKJKN_CTRLNO:	// コントロールNo
					iRet = ZdbKekkaGD105SelectByCtrlNo( &pHkkknriArrayOut[iHkkknriLoop],
														&pKekkaArrayOut, &iKekkaNumOut );
					break;
				case GD105_DB_HKKJKN_PLTNO:		// プロットNo
					iRet = ZdbKekkaGD105SelectByPltNo( &pHkkknriArrayOut[iHkkknriLoop],
													   &pKekkaArrayOut, &iKekkaNumOut );
					break;
				case GD105_DB_HKKJKN_KNSSEQ:	// 検査SEQ
					iRet = ZdbKekkaGD105SelectByKnsSeq( &pHkkknriArrayOut[iHkkknriLoop],
														&pKekkaArrayOut, &iKekkaNumOut );
					break;
				case GD105_DB_HKKJKN_IRINO:		// 依頼書No
					iRet = ZdbKekkaGD105SelectByIriNo( &pHkkknriArrayOut[iHkkknriLoop],
													   &pKekkaArrayOut, &iKekkaNumOut );
					break;
				case GD105_DB_HKKJKN_KNTNO:		// 検体No
					iRet = ZdbKekkaGD105SelectByKntNo( &pHkkknriArrayOut[iHkkknriLoop],
													   &pKekkaArrayOut, &iKekkaNumOut );
					break;
				default:
					// 異常終了	LOG
//1.06 DELL printf("hkkknri.hkkjkn の範囲エラー (HKKJKN='%c')\n", pHkkknriArrayOut[iHkkknriLoop].hkkjkn);
					// 1.06 異常終了	LOG
					sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"kkknri.hkkjkn の範囲エラー (HKKJKN='%c')", 
							pHkkknriArrayOut[iHkkknriLoop].hkkjkn );

					// 報告管理情報を更新
					GD105UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
										   GD105_DB_HKKJKFLG_ERRFILE,
										   GD105_DB_HKKERRCODE_HKKJKN );
					continue;
				}
				if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
					// 異常終了	LOG
//1.06 DELL printf("ZdbKekkaGD105SelectByXXXX error (%d)\n", iRet);
					// 1.06 異常終了	LOG
					sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
							"ZdbKekkaGD105SelectByXXXX error (%d)", iRet);

					// 報告管理情報を更新
					GD105UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
										   GD105_DB_HKKJKFLG_ERRFILE,
// 2006-04-06 H.Suyama Change Start
#if 0
//										   GD105_DB_HKKERRCODE_HKKJKN );
#else
										   GD105_DB_HKKERRCODE_DBACS );
#endif
// 2006-04-06 H.Suyama Change End
					continue;
				}
				if ( iRet == HRC_SQL_NOT_FOUND ) {
					// 異常終了	LOG
//1.06 DELL printf("ZdbKekkaGD105SelectByXXXX no data error\n");
					// 1.06 異常終了	LOG
					sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
							"ZdbKekkaGD105SelectByXXXX no data  error" );

					// 報告管理情報を更新
					GD105UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
										   GD105_DB_HKKJKFLG_ERRFILE,
										   GD105_DB_HKKERRCODE_NODATA );
					continue;
				}
				if ( iRet == HRC_SQL_NORMAL ) {
					// 報告データファイルの作成
					if ( GD105CreateFile( pEnv,
										  &stSysknrmst,
										  pKekkaArrayOut,
										  iKekkaNumOut,
										  &iHkkssknsu,
										  &iHkkhrysu,
										  cDataFile,
											&li_stopFlg//2006.12.08 Kim Jinsuk DBエラー時終了させる 
											) == RTN_NG ) {

						//2006.12.08　Kim Jinsuk DBエラー時異常終了させる
						if(li_stopFlg==1)
						{
						    printf("#############################3");
						    sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbKekkaGD105Update", __LINE__,
						    EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
						    "[[DB ERROR]]" );

						    return( RTN_NG );
						}
						//2006.12.08　Kim Jinsuk DBエラー時異常終了させる


						// 1.12 ADD 保留件数以外報告対象0件の場合
						if( iKekkaNumOut == iHkkhrysu ){
							sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction", __LINE__,
									EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"保留以外報告対象0件" );
							// 報告保留件数
	            			pHkkknriArrayOut[iHkkknriLoop].hkkssknsu = iHkkssknsu;
	            			pHkkknriArrayOut[iHkkknriLoop].hkkhrysu = iHkkhrysu;
							GD105UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
												   GD105_DB_HKKJKFLG_ERRFILE,
												   GD105_DB_HKKERRCODE_NODATA );

							// 検査フラグを更新
							if ( GD105UpdateKekka( pEnv,
												   &stSysknrmst,
												   pKekkaArrayOut,
												   iKekkaNumOut,
												   &li_stopFlg
												 ) == RTN_NG ) {

								if(li_stopFlg==1) {
									sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105UpdateKekka", __LINE__,
											EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON, "[[DB ERROR]]" );

									return( RTN_NG );
								}
								sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction", __LINE__,
											EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "GD105UpdateKekka error" );
							}

							continue;
						}

						// 異常終了	LOG
// 1.06 DELL printf("GD105CreateFile error\n");
						// 1.06 異常終了	LOG
						sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
								 __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"GD105CreateFile error" );


						// 報告管理情報を更新
						GD105UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
											   GD105_DB_HKKJKFLG_ERRFILE,
// 2006-04-06 H.Suyama Change Start
#if 0
//											   GD105_DB_HKKERRCODE_HKKJKN );
#else
											   GD105_DB_HKKERRCODE_CREATE );
#endif
// 2006-04-06 H.Suyama Change End

/* 2008-09-02 Start → 2014-01-15 削除
						if ( iHkkssknsu != 0 ) {
							// HULFT送信用ファイルの作成
							if ( GD105CreateHULFTFile( pEnv,
													   &stSysknrmst,
													   &pHkkknriArrayOut[iHkkknriLoop],
													   cDataFile,
													   iHkkssknsu,
											  			&pHkkknriArrayOut[iHkkknriLoop] ) == RTN_NG ) {

								sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
										 __LINE__,
										EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
										"GD105CreateHULFTFile error" );

								// 報告管理情報を更新
								GD105UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
													   GD105_DB_HKKJKFLG_ERRFILE,
													   GD105_DB_HKKERRCODE_HULFT );
							}

							// 作成開始日時
							GD105ConvTimestamp( ulSt, cTimestamp );
							ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkstdh,
										 cTimestamp,
										 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkstdh ) );
							// 作成完了日時を取得
							time( (long *)&ulEd );
							// 作成完了日時
							GD105ConvTimestamp( ulEd, cTimestamp );
							ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkeddh,
										 cTimestamp,
										 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkeddh ) );
							// 作成件数
							pHkkknriArrayOut[iHkkknriLoop].hkkssknsu = iHkkssknsu;
							// 報告保留件数
							pHkkknriArrayOut[iHkkknriLoop].hkkhrysu = iHkkhrysu;
							// 送信ファイルＩＤ
							// GD105CreateHULFTFile内で設定
							// 報告状況フラグ
							ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg,
										 GD105_DB_HKKJKFLG_ERRFILE,
										 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg ) );
							// 情報更新日時は関数内で設定

							// 報告管理情報を更新
							iRet = ZdbHkkknriGD105UpdateNormal( &pHkkknriArrayOut[iHkkknriLoop] );
							if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
								// ロールバック
								ZdbRollback();
								// 異常終了	LOG
								sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction",
										 __LINE__,
										EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
										"ZdbHkkknriGD105UpdateNormal error (%d)", iRet);

								return( RTN_NG );
							}

							// 報告管理情報を更新 GD105_DB_HKKERRCODE_DBACS は仮とする
							GD105UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
												   GD105_DB_HKKJKFLG_ERRFILE,
												   GD105_DB_HKKERRCODE_DBACS );

							// コミット
							ZdbCommit();
						}
 2008-09-02 End → 2014-01-15 削除 */
						continue;
					}


					// HULFT送信用ファイルの作成
// 2006-04-06 H.Suyama Change Start
#if 0
//					if ( GD105CreateHULFTFile( pEnv,
//											   &stSysknrmst,
//											   &pHkkknriArrayOut[iHkkknriLoop],
//											   cDataFile ) == RTN_NG ) {
#else
//2006-07-06 CHG Osada ファイル名命名方法変更
//					if ( GD105CreateHULFTFile( pEnv,
//											   &stSysknrmst,
//											   &pHkkknriArrayOut[iHkkknriLoop],
//											   cDataFile,
//											   iHkkssknsu ) == RTN_NG ) {
					if ( GD105CreateHULFTFile( pEnv,
											   &stSysknrmst,
											   &pHkkknriArrayOut[iHkkknriLoop],
											   cDataFile,
											   iHkkssknsu,
									  			&pHkkknriArrayOut[iHkkknriLoop] ) == RTN_NG ) {
#endif
// 2006-04-06 H.Suyama Change End
						// 異常終了	LOG
// 1.06 DELL printf("GD105CreateHULFTFile error\n");
					// 1.06 異常終了	LOG
						sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
								 __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"GD105CreateHULFTFile error" );

						// 報告管理情報を更新
						GD105UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
											   GD105_DB_HKKJKFLG_ERRFILE,
// 2006-04-06 H.Suyama Change Start
#if 0
//											   GD105_DB_HKKERRCODE_HKKJKN );
#else
											   GD105_DB_HKKERRCODE_HULFT );
#endif
// 2006-04-06 H.Suyama Change End
						continue;
					}
				}


				// 作成完了日時を取得
				time( (long *)&ulEd );

				// 報告ファイル名
				// GD105CreateHULFTFile内で設定
				// 作成開始日時
				GD105ConvTimestamp( ulSt, cTimestamp );
				ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkstdh,
							 cTimestamp,
							 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkstdh ) );
				// 作成完了日時
				GD105ConvTimestamp( ulEd, cTimestamp );
				ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkeddh,
							 cTimestamp,
							 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkeddh ) );
				// 作成件数
				pHkkknriArrayOut[iHkkknriLoop].hkkssknsu = iHkkssknsu;
				// 報告保留件数
				pHkkknriArrayOut[iHkkknriLoop].hkkhrysu = iHkkhrysu;
				// 送信ファイルＩＤ
				// GD105CreateHULFTFile内で設定
			

				// 検査フラグを報告済みに更新
				if ( GD105UpdateKekka( pEnv,
									   &stSysknrmst,
									   pKekkaArrayOut,
									   iKekkaNumOut,
									   &li_stopFlg 
										) == RTN_OK ) {
					// 報告状況フラグ
					ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg,
								 GD105_DB_HKKJKFLG_CHUU,
								 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg ) );
				} else {

					// 報告管理情報を更新
					GD105UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
										   GD105_DB_HKKJKFLG_OK_DBERR,
										   GD105_DB_HKKERRCODE_DBACS );

					if(li_stopFlg==1) {
						sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105UpdateKekka", __LINE__,
									EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON, "[[DB ERROR]]" );
						return( RTN_NG );
					}
					sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "GD105UpdateKekka error" );

					// 報告状況フラグ
					ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg,
								 GD105_DB_HKKJKFLG_OK_DBERR,
								 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg ) );
				}

				// 情報更新日時は関数内で設定

				// 報告管理情報を更新
				iRet = ZdbHkkknriGD105UpdateNormal( &pHkkknriArrayOut[iHkkknriLoop] );
				if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
					// ロールバック
					ZdbRollback();
					// 異常終了	LOG
// 1.06 DELL printf("ZdbHkkknriGD105UpdateNormal error (%d)\n", iRet);
					// 1.06 異常終了	LOG
					sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
							"ZdbHkkknriGD105UpdateNormal error (%d)", iRet);

					return( RTN_NG );
				}

// 2006-04-01 H.Suyama Del Start
#if 0
//				// システム管理情報を更新
//				iRet = ZdbSysknrmstUpdate( &stSysknrmst );
//				if ( iRet != HRC_SQL_NORMAL ) {
//					// 異常終了	LOG
//printf("ZdbSysknrmstUpdate error (%d)\n", iRet);
//					return( RTN_NG );
//				}
#endif
// 2006-04-01 H.Suyama Del Start

				// コミット
				ZdbCommit();
				
				
				// 結果情報を解放
				if ( pKekkaArrayOut != NULL ) {
					ZbmlFree( pKekkaArrayOut );
				}
			}

			// 報告管理情報を解放
			ZbmlFree( pHkkknriArrayOut );
		}

		// スリープ
		sleep( pEnv->iSleepSec );
	}

#ifdef _TRACE
	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");
#endif

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：endFunction()												  */
/*　機能概要　：終了処理関数												  */
/*　入　　力　：															  */
/*　　第１引数：GD105Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：なし														  */
/******************************************************************************/
void endFunction( GD105Env *pEnv )
{
#ifdef _TRACE
	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "endFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");
#endif
	// 1.09 ADD
	/***	
     ***    データベースクローズ
     ***/
    ZdbDisConnect() ;

	// 共有メモリ削除
	if ( sFncShmDel( pEnv ) != RTN_OK ) {
		return;
	}

#ifdef _TRACE
	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "endFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");
#endif
}

/******************************************************************************/
/*　関 数 名　：GD105MakeData()												  */
/*　機能概要　：報告データ作成												  */
/*　入　　力　：															  */
/*　　第１引数：Kekka *pKekka		検査結果データ							  */
/*　　第２引数：char *pLBCD			ラボコード								  */
/*　出　　力　：															  */
/*　　第３引数：GD105Rec *pGD105Rec	報告データ								  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int GD105MakeData(Kekka *pKekka, char *pLBCD, GD105Rec *pGD105Rec)
{
	char	cTempBuff[128];
	char	cKkassflg[1+1];		// 1.11 ADD 結果修正ﾌﾗｸﾞMAX取得


	// 検査結果データまたは報告データへのポインタがNULLの場合異常終了
	if ( pKekka == NULL || pGD105Rec == NULL ) {
		return( RTN_NG );
	}

	// 1.06 ADD 施設別換算対応
	GD105_sstknz( pKekka );

	// 報告データをスペースでクリア
	memset( pGD105Rec, GD105_DATA_SPACE, sizeof(GD105Rec) );

	// 検査結果データから報告データを作成
	// ＢＭＬ受付年月日
	// [YYYYMMDD]に変換して設定
	ZbmlChgAPDate( pGD105Rec->cUTKYMD, pKekka->utkymd );
	// 依頼書Ｎｏ．
	// 左から11桁を↓のように変換
	// (変換前)[1][2][3][4][5][6][7][8][9][10][11]
	// (変換後)[3][4][5] 0  0 [6][7][8][9][10][11]
	if ( GD105ConvNumber( pGD105Rec->cIRINO, pKekka->irino ) == RTN_NG ) {
		return( RTN_NG );
	}
	// 項目コード
	if ( GD105CopyFromLeft( pGD105Rec->cKMKCD,
							pKekka->kmkcd,
							sizeof( pGD105Rec->cKMKCD ),
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// 検体Ｎｏ．
	// 左から11桁を↓のように変換
	// (変換前)[1][2][3][4][5][6][7][8][9][10][11]
	// (変換後)[3][4][5] 0  0 [6][7][8][9][10][11]
	if ( GD105ConvNumber( pGD105Rec->cKNTNO, pKekka->kntno ) == RTN_NG ) {
		return( RTN_NG );
	}
	// 親項目コード
	if ( GD105CopyFromLeft( pGD105Rec->cOYAKMKCD,
							pKekka->oyakmkcd,
							sizeof( pGD105Rec->cOYAKMKCD ),
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// 検査結果１
	// 右から8桁を設定（ｾﾞﾛｻﾌﾟﾚｽあり）
	if ( GD105CopyFromRight( pGD105Rec->cKNSKKA1,
							 pKekka->knskka1,
							 sizeof( pGD105Rec->cKNSKKA1 ),
							 FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// 検査結果２
	// 左から8桁を設定（2バイト文字に注意する）
	//1.09 UPD
	//if ( GD105CopyFromRight( pGD105Rec->cKNSKKA2,
	if ( GD105CopyFromLeft( pGD105Rec->cKNSKKA2,
							 pKekka->knskka2,
							 sizeof( pGD105Rec->cKNSKKA2 ),
							 TRUE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// 結果２区分
	// 左から1桁を設定
// 2006-04-20 H.Suyama Change Start
#if 0
//	pGD105Rec->cKNSKKA2KBN = pKekka->knskka2kbn[0];
#else
	if ( pKekka->knskka2kbn[0] == '\0' )
		pGD105Rec->cKNSKKA2KBN = GD105_DATA_SPACE;
	else
		pGD105Rec->cKNSKKA2KBN = pKekka->knskka2kbn[0];
#endif
// 2006-04-20 H.Suyama Change End
	// 結果補足コード
	if ( GD105CopyFromLeft( pGD105Rec->cKKAHSKCD,
							pKekka->kkahskcd,
							sizeof( pGD105Rec->cKKAHSKCD ),
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// 結果コメント１
// 2006-04-06 H.Suyama Change Start
#if 0
//	// 右から4桁を設定
//	if ( GD105CopyFromRight( pGD105Rec->cKKACMT1,
//							 pKekka->kkacmt1,
//							 sizeof( pGD105Rec->cKKACMT1 ),
//							 FALSE ) == RTN_NG ) {
//		return( RTN_NG );
//	}
#else
	// 左から4桁を設定
	if ( GD105CopyFromLeft( pGD105Rec->cKKACMT1,
							pKekka->kkacmt1,
							sizeof( pGD105Rec->cKKACMT1 ),
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
#endif
// 2006-04-06 H.Suyama Change End
	// 結果コメント２
// 2006-04-06 H.Suyama Change Start
#if 0
//	// 右から4桁を設定
//	if ( GD105CopyFromRight( pGD105Rec->cKKACMT2,
//							 pKekka->kkacmt2,
//							 sizeof( pGD105Rec->cKKACMT2 ),
//							 FALSE ) == RTN_NG ) {
//		return( RTN_NG );
//	}
#else
	// 左から4桁を設定
	if ( GD105CopyFromLeft( pGD105Rec->cKKACMT2,
							pKekka->kkacmt2,
							sizeof( pGD105Rec->cKKACMT2 ),
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
#endif
// 2006-04-06 H.Suyama Change End
	// 異常値区分（男）
// 2006-04-20 H.Suyama Change Start
#if 0
//	pGD105Rec->cIJKBNM = pKekka->ijkbnm;
#else
	if ( pKekka->ijkbnm == '\0' )
		pGD105Rec->cIJKBNM = GD105_DATA_SPACE;
	else
		pGD105Rec->cIJKBNM = pKekka->ijkbnm;
#endif
// 2006-04-20 H.Suyama Change End
	// 異常値区分（女）
// 2006-04-20 H.Suyama Change Start
#if 0
//	pGD105Rec->cIJKBNF = pKekka->ijkbnf;
#else
	if ( pKekka->ijkbnf == '\0' )
		pGD105Rec->cIJKBNF = GD105_DATA_SPACE;
	else
		pGD105Rec->cIJKBNF = pKekka->ijkbnf;
#endif
// 2006-04-20 H.Suyama Change End
	// 異常値区分（不明）
// 2006-04-20 H.Suyama Change Start
#if 0
//	pGD105Rec->cIJKBNN = pKekka->ijkbnn;
#else
	if ( pKekka->ijkbnn == '\0' )
		pGD105Rec->cIJKBNN = GD105_DATA_SPACE;
	else
		pGD105Rec->cIJKBNN = pKekka->ijkbnn;
#endif
// 2006-04-20 H.Suyama Change End
	// 指数（ＳＤ１）
	if ( GD105CopyFromLeft( pGD105Rec->cSDI,
							pKekka->sdi,
							sizeof( pGD105Rec->cSDI ),
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// 基準値Ｎｏ．
	if ( GD105CopyFromLeft( pGD105Rec->cKJNO,
							pKekka->kjno,
							sizeof( pGD105Rec->cKJNO ),
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// ラボ着日
	// 空白を設定なので何もしない
	// 検査完了予定日
	// 空白を設定なので何もしない
	// 拡張結果DB識別ｺｰﾄﾞ
	// [0]を設定
	pGD105Rec->cEXTKKADBIDCD = GD105_DATA_CHAR0;
	// 結果状況コード
// 2006-04-20 H.Suyama Change Start
#if 0
//	pGD105Rec->cKKAJKCD = pKekka->kkajkcd;
#else
	if ( pKekka->kkajkcd == '\0' )
		pGD105Rec->cKKAJKCD = GD105_DATA_SPACE;
	else
		pGD105Rec->cKKAJKCD = pKekka->kkajkcd;
#endif
// 2006-04-20 H.Suyama Change End
	// パニックレンジフラグ
// 2006-04-20 H.Suyama Change Start
#if 0
//	pGD105Rec->cPNCRGFLG = pKekka->pncrgflg;
#else
	if ( pKekka->pncrgflg == '\0' )
		pGD105Rec->cPNCRGFLG = GD105_DATA_SPACE;
	else
		pGD105Rec->cPNCRGFLG = pKekka->pncrgflg;
#endif
// 2006-04-20 H.Suyama Change End
	// ＷＳコード
// 2006-04-06 H.Suyama Change Start
#if 0
//	// 右から4桁を設定
//	if ( GD105CopyFromRight( pGD105Rec->cSMPCD,
//							 pKekka->smpcd,
//							 sizeof( pGD105Rec->cSMPCD ),
//							 FALSE ) == RTN_NG ) {
//		return( RTN_NG );
//	}
#else
	// 左から4桁を設定
	if ( GD105CopyFromLeft( pGD105Rec->cSMPCD,
							pKekka->smpcd,
							sizeof( pGD105Rec->cSMPCD ),
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
#endif
// 2006-04-06 H.Suyama Change End
	// 検査ＳＥＱ
	// 数値を文字列に変換後、右から6桁を設定。（ｾﾞﾛｻﾌﾟﾚｽなし）
	sprintf( cTempBuff, "%06d", pKekka->knsseq );
	if ( GD105CopyFromRight( pGD105Rec->cKNSSEQ,
							 cTempBuff,
							 sizeof( pGD105Rec->cKNSSEQ ),
							 FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// 推定材料コード
		// 1.06 ADD 条件により固定で推定材料を設定
		// 099: ?
/* 1.13 STA str->mem */
//	if( strncmp( pKekka->smpcd, "0952", 4 ) == 0 ){
//		strcpy( pKekka->zrcd,	"099" );
//	}
	if( memcmp( pKekka->smpcd, "0952", 4 ) == 0 ){
		memcpy( pKekka->zrcd,	"099", 3 );
	}
		// 007:胆汁
//	if( strncmp( pKekka->smpcd, "0959", 4 ) == 0 ){
//		strcpy( pKekka->zrcd,	"007" );
//	}
	if( memcmp( pKekka->smpcd, "0959", 4 ) == 0 ){
		memcpy( pKekka->zrcd,	"007", 3 );
	}
/* 1.13 END str->mem */

// 2006-04-06 H.Suyama Change Start
#if 0
//	// 右から3桁設定
//	if ( GD105CopyFromRight( pGD105Rec->cZRCD,
//							 pKekka->zrcd,
//							 sizeof( pGD105Rec->cZRCD ),
//							 FALSE ) == RTN_NG ) {
//		return( RTN_NG );
//	}
#else
	// 左から3桁設定
	if ( GD105CopyFromLeft( pGD105Rec->cZRCD,
							pKekka->zrcd,
							sizeof( pGD105Rec->cZRCD ),
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
#endif
// 2006-04-06 H.Suyama Change End
	// 結果換算フラグ
// 2006-04-20 H.Suyama Change Start
#if 0
//	pGD105Rec->cKKAKSFLG = pKekka->kkaksflg;
#else
	if ( pKekka->kkaksflg == '\0' )
		pGD105Rec->cKKAKSFLG = GD105_DATA_SPACE;
	else
		pGD105Rec->cKKAKSFLG = pKekka->kkaksflg;
#endif
// 2006-04-20 H.Suyama Change End

	// 結果修正フラグ
// 1.11 STA ====================================================
// 1.11 DEL// 2006-04-20 H.Suyama Change Start
// 1.11 DEL #if 0
// 1.11 DEL //	pGD105Rec->cKKASSFLG = pKekka->kkassflg;
// 1.11 DEL #else
// 1.11 DEL 	if ( pKekka->kkassflg == '\0' )
// 1.11 DEL 		pGD105Rec->cKKASSFLG = GD105_DATA_SPACE;
// 1.11 DEL 	else
// 1.11 DEL 		pGD105Rec->cKKASSFLG = pKekka->kkassflg;
// 1.11 DEL #endif
// 1.11 DEL // 2006-04-20 H.Suyama Change End

// 1.11 ADD 結果修正フラグは同一KEY内のMAX(結果修正FLG）を編集
	 if ( pKekka->kkassflg == '\0' ){
		pGD105Rec->cKKASSFLG = GD105_DATA_SPACE;
	} else {
		memset( cKkassflg,	'\0',	sizeof( cKkassflg ));
		if ( GD105GetKkassflgMax( pKekka, cKkassflg ) == RTN_OK ) {
			pGD105Rec->cKKASSFLG = cKkassflg[0];
			// 更新用に取得したMAXを構造体に編集する
			pKekka->kkassflg	= cKkassflg[0];
		} else {
			pGD105Rec->cKKASSFLG = pKekka->kkassflg;
		}
	}
// 1.11 END ====================================================

	// 非照会フラグ
// 2006-04-20 H.Suyama Change Start
#if 0
//	pGD105Rec->cHSYKFLG = pKekka->hsykflg;
#else
	if ( pKekka->hsykflg == '\0' )
		pGD105Rec->cHSYKFLG = GD105_DATA_SPACE;
	else
		pGD105Rec->cHSYKFLG = pKekka->hsykflg;
#endif
// 2006-04-20 H.Suyama Change End
	// 非請求区分
// 2006-04-20 H.Suyama Change Start
#if 0
//	pGD105Rec->cHSKFLG = pKekka->hskflg;
#else
	if ( pKekka->hskflg == '\0' )
		pGD105Rec->cHSKFLG = GD105_DATA_SPACE;
	else
		pGD105Rec->cHSKFLG = pKekka->hskflg;
#endif
// 2006-04-20 H.Suyama Change End
	// 非報告フラグ
// 2006-04-20 H.Suyama Change Start
#if 0
//	pGD105Rec->cHHKKFLG = pKekka->hhkkflg;
#else
	if ( pKekka->hhkkflg == '\0' )
		pGD105Rec->cHHKKFLG = GD105_DATA_SPACE;
	else
		pGD105Rec->cHHKKFLG = pKekka->hhkkflg;
#endif
// 2006-04-20 H.Suyama Change End
	// 検査識別コード
	// [0]を設定
	pGD105Rec->cKNSIDCD = GD105_DATA_CHAR0;
	// 検査実施ラボコード
	if ( GD105CopyFromLeft( pGD105Rec->cLBCD,
							pLBCD,
							sizeof( pGD105Rec->cLBCD ),
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// 予約フィールド
	// 空白を設定なので何もしない

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：GD105DataFileFilter()										  */
/*　機能概要　：ディレクトリ検索用のファイルフィルタ(コールバック)			  */
/*　入　　力　：															  */
/*　　第１引数：struct dirent *pDirEnt	ディレクトリエントリ				  */
/*　出　　力　：検査結果ファイル											  */
/*　復帰情報　：int															  */
/*　　　　　　		0	: 対象外ファイル									  */
/*　　　　　　		1	: 対象ファイル										  */
/******************************************************************************/
int GD105DataFileFilter(struct dirent *pDirEnt)
{
	BmlDate		today;
	char		cToday[GD105_LEN_DATESHORT + 1];

	// 文字列長チェック
	if ( strlen ( pDirEnt->d_name )  < GD105_LEN_FILEID ) {
		return( 0 ) ;
	}

	// 当日日付取得
	if ( ZbmlDateGetToday(&today) == FALSE ) {
		return( 0 );
	}
	sprintf( cToday, "%04d%02d%02d", today.year, today.month, today.day);

	// 日付チェック
	if ( memcmp ( pDirEnt->d_name,
				  cToday,
				  strlen ( cToday ) ) != 0 ) {
		return( 0 ) ;
	}

	return( 1 );
}

/******************************************************************************/
/*　関 数 名　：GD105WriteFile()											  */
/*　機能概要　：報告データファイル書込み									  */
/*　入　　力　：															  */
/*　　第１引数：FILE *fp			ファイルポインタ						  */
/*　　第２引数：GD105Rec *pGD105Rec	報告データ								  */
/*　　第３引数：int iRecCnt			レコード数								  */
/*　出　　力　：検査結果ファイル											  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int GD105WriteFile(FILE *fp, GD105Rec *pGD105Rec, int iRecCnt)
{
	int				iLoop;
	int				iFileCnt;
	GD105Rec		stGD105RecTemp;
	char			cTemp[GD105_FILE_FILLER_SIZE];

	// ファイル出力
	// データ識別子書込み
	iFileCnt = fwrite( GD105_FILE_DATAID, strlen( GD105_FILE_DATAID ), 1, fp);
	if ( iFileCnt != 1 ) {
		// 異常終了	LOG
// 1.06 DELL printf("write status:[%d]\n", iFileCnt);
		// 1.06 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105WriteFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"write status:[%d]", iFileCnt );

		gintErrorCode = GD105_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	// レコード書込み
	iFileCnt = fwrite( pGD105Rec, sizeof( GD105Rec ) * iRecCnt, 1, fp);
	if ( iFileCnt != 1 ) {
		// 異常終了	LOG
// 1.06 DELL printf("write status:[%d]\n", iFileCnt);
		// 1.06 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105WriteFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"write status:[%d] ", iFileCnt );

		gintErrorCode = GD105_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}
	for ( iLoop = iRecCnt; iLoop < GD105_REC_LOOP_MAX; iLoop++ ) {
		memset( &stGD105RecTemp, GD105_DATA_SPACE, sizeof( GD105Rec ) );
		iFileCnt = fwrite( &stGD105RecTemp, sizeof( GD105Rec ), 1, fp);
		if ( iFileCnt != 1 ) {
			// 異常終了	LOG
// 1.06 DELL printf("write status:[%d]\n", iFileCnt);
			// 1.06 異常終了	LOG
			sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105WriteFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"write status:[%d]", iFileCnt );

			gintErrorCode = GD105_STSCODE_ERR_FR_FILE ;
			return( RTN_NG ) ;
		}
	}

	// Filler書込み
	memset( cTemp, GD105_DATA_SPACE, GD105_FILE_FILLER_SIZE );
	iFileCnt = fwrite( cTemp, GD105_FILE_FILLER_SIZE, 1, fp );
	if ( iFileCnt != 1 ) {
		// 異常終了	LOG
//1.06 DELL printf("write status:[%d]\n", iFileCnt);
		// 1.06 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105WriteFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"write status:[%d]", iFileCnt );

		gintErrorCode = GD105_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	// LF書込み
	cTemp[0] = GD105_FILE_LINEFEED;
	iFileCnt = fwrite( cTemp, 1, 1, fp);
	if ( iFileCnt != 1 ) {
		// 異常終了	LOG
// 1.06 DELL printf("write status:[%d]\n", iFileCnt);
		// 1.06 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105WriteFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"write status:[%d] ", iFileCnt );

		gintErrorCode = GD105_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：GD105ResendFile()											  */
/*　機能概要　：再転送用ファイル移動										  */
/*　入　　力　：															  */
/*　　第１引数：GD105Env *pEnv		プログラム環境構造体					  */
/*　　第２引数：Sysknrmst *pSysknrmst システム管理マスタ情報				  */
/*　　第３引数：Hkkknri *pHkkknri	報告管理情報情報						  */
/*　出　　力　：															  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int GD105ResendFile(GD105Env *pEnv, Sysknrmst *pSysknrmst, Hkkknri *pHkkknri)
{
	int				iRet;
	struct dirent	**pDirEnt;
	int				iFileCnt;
	int	 			iSeqNo;
	char			cSeqBuff[10];
	BmlDate			today;
	char			cKjnsriymd[GD105_LEN_DATESHORT + 1];
	char			cFileDate[GD105_LEN_DATESHORT + 1];
	char			cFileSrc[PATH_MAX + 1];
	char			cSendFile[PATH_MAX + 1];
	char			cSendFileTemp[PATH_MAX + 1];
	FILE *			fpSrc;
	FILE *			fpDest;
	int				iLoop;
	FILEHEADER		stHeader, *pHead;
	FILETRAILER		stTrailer;
	char			cTemp[GD105_SIZE_BUFF + 1];
	char			cWfilnm[PATH_MAX + 1];
    //2006-07-06 ADD Osada ファイル名命名方法変更
    char            sNewFlName[PATH_MAX + 1];
    char            sKaisibi[10];
	char			sSecCd[3];
    int             i;
	int	iHead;
	char			sBuf[128];
    //

	// 処理日付取得
	ZbmlChgAPDate( cKjnsriymd, pSysknrmst->kjnsriymd );

	// 元ファイルの処理日付を取得
	memset( cFileDate, 0, sizeof( cFileDate ) );
	memcpy( cFileDate, pHkkknri->ssnmtfilid, GD105_LEN_DATESHORT );

	// 1.07 INTEC ADD STA
	// ファイル名の後ろ空白をTrim
	sprintf( cWfilnm, "%.*s",
			strcspn( pHkkknri->stsflnm, " " ) ,
			pHkkknri->stsflnm );
	strcpy( pHkkknri->stsflnm, cWfilnm );
	// 1.07 INTEC ADD END

	// 送信用ファイル名生成
//2006-07-06 CHG Osada ファイル名命名方法変更
#if 0
	sprintf( cSendFile, "%s/%s/%s/%s%04d%s",
			 pEnv->cDirToday,
			 pEnv->cDirSendFile,
			 pEnv->cDirSendREQ,
			 pHkkknri->ssnmtfilid,
			 pHkkknri->hkksjno,
			 GD105_FILEEXT_DATA );
	sprintf( cSendFileTemp, "%s/%s/%s/%s%04d%s",
			 pEnv->cDirToday,
			 pEnv->cDirSendFile,
			 pEnv->cDirSendREQ,
			 pHkkknri->ssnmtfilid,
			 pHkkknri->hkksjno,
			 GD105_FILEEXT_TEMP );
#else
   memset(sNewFlName, 0, sizeof(sNewFlName));
   //CHG E/Osada 2006-07-18 
   //sprintf(sNewFlName, "%-3.3s_%04d_%-22.22s", pHkkknri->stsflnm, pHkkknri->hkksjno,
	// 1.10 UPD 報告指示NOをそのまま編集(-1しない)
   //sprintf(sNewFlName, "%-3.3s_%04d_%-18.18s%04d", pHkkknri->stsflnm, pHkkknri->hkksjno - 1,
   sprintf(sNewFlName, "%-3.3s_%04d_%-18.18s%04d", pHkkknri->stsflnm, pHkkknri->hkksjno,
		&pHkkknri->stsflnm[9], pSysknrmst->ssntubn);
	memset(cSendFile, 0, sizeof(cSendFile));
	memset(cSendFileTemp, 0, sizeof(cSendFileTemp));
	sprintf(cSendFile, "%s/%s/%s/%s%s",
			pEnv->cDirToday,
		 	pEnv->cDirSendFile,
			pEnv->cDirSendREQ,
			sNewFlName, GD105_FILEEXT_DATA);	
	sprintf(cSendFileTemp, "%s/%s/%s/%s%s",
			pEnv->cDirToday,
		 	pEnv->cDirSendFile,
			pEnv->cDirSendREQ,
			sNewFlName, GD105_FILEEXT_TEMP);	
#endif
//

	// 処理日元ファイルのOKディレクトリのフルパスを生成
	//if ( memcmp( cKjnsriymd, pHkkknri->stsflnm, GD105_LEN_DATESHORT ) == 0 ) {
	if ( memcmp( cKjnsriymd, pHkkknri->ssnmtfilid, GD105_LEN_DATESHORT ) == 0 ) {
		sprintf( cFileSrc, "%s/%s/%s/%s",
			 	pEnv->cDirToday,
			 	pEnv->cDirSendFile,
			 	pEnv->cDirSendOK,
				pHkkknri->stsflnm );
	} else {
		sprintf( cFileSrc, "%s/%s/%s/%s/%s",
			 	pEnv->cDirOldday,
			 	cFileDate,
			 	pEnv->cDirSendFile,
			 	pEnv->cDirSendOK,
				pHkkknri->stsflnm );
	}
	// 元ファイルオープン
	fpSrc = fopen ( cFileSrc, "r" );
	if ( fpSrc == NULL ) {
		// ファイルがオープンできない場合はERRディレクトリで再挑戦
		if ( strncmp( cKjnsriymd, pHkkknri->ssnmtfilid, GD105_LEN_DATESHORT ) == 0 ) {
		//if ( strncmp( cKjnsriymd, pHkkknri->stsflnm, GD105_LEN_DATESHORT ) == 0 ) {
			sprintf( cFileSrc, "%s/%s/%s/%s",
				 	pEnv->cDirToday,
				 	pEnv->cDirSendFile,
				 	pEnv->cDirSendERR,
					pHkkknri->stsflnm );
		} else {
			sprintf( cFileSrc, "%s/%s/%s/%s/%s",
				 	pEnv->cDirOldday,
			 		cFileDate,
				 	pEnv->cDirSendFile,
				 	pEnv->cDirSendERR,
					pHkkknri->stsflnm );
		}
		// 元ファイルオープン
		fpSrc = fopen ( cFileSrc, "r" );
		if ( fpSrc == NULL ) {
			// 異常終了	LOG
			gintErrorCode = GD105_STSCODE_ERR_FR_FILE ;
			return( RTN_NG ) ;
		}
	}

	// 送信用ファイルオープン
	fpDest = fopen ( cSendFileTemp, "w" );
	if ( fpDest == NULL ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	// 読み込み
	iHead = 0;
	while ( iRet = fgets( cTemp, sizeof ( cTemp ), fpSrc ) != NULL ) {
		if( !iHead ) {
			pHead = (FILEHEADER *)cTemp;
			memset(sBuf, 0, sizeof(sBuf));
			sprintf( sBuf, "%04d", pSysknrmst->ssntubn );
			ZbmlStrCpy( pHead->cSeqNo, sBuf, sizeof( stHeader.cSeqNo ) );
			memset(sBuf, 0, sizeof(sBuf));
			memset(pHead->cParam1, ' ', 128);
			// 1.10 UPD 再転送元ファイル名の先頭18byteをパラムに設定する
			//sprintf( sBuf, "%s%s", sNewFlName, GD105_FILEEXT_DATA );
			//memcpy(pHead->cParam1, sBuf, 18);
			memcpy(pHead->cParam1, pHkkknri->stsflnm, 18);
			iHead = 1;
		}
		// ﾊﾟﾗﾒｰﾀ1
	//stHeader.cParam1
// 2006-04-20 H.Suyama Add Start
	// 1.07 INTEC UPD cSendIDSaki -> cSendIDMoto
	//							pEnv->cSendIDSaki,
		if ( fputs( cTemp, fpDest ) < 0 ) {
			//エラーログ出力
//1.06 DELL printf("fputs error \n");
			// 1.06 異常終了	LOG
			sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105ResendFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"fputs error ");

			return( RTN_NG );
		}
	}

	// ファイルクローズ
	fclose( fpSrc );
	fclose( fpDest );

	// ファイル拡張子名変更
	iRet = rename( cSendFileTemp, cSendFile );
	if ( iRet != 0 ) {
		// 異常終了	LOG
//1.06 DELL printf("ResendFile rename status:[%d]\n", iRet);
		// 1.06 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105ResendFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"ResendFile rename status:[%d] ", iRet);

		gintErrorCode = GD105_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	// 返却用にファイル名と送信ファイルＩＤを設定
	memset( pHkkknri->hkkflnm, 0, sizeof( pHkkknri->hkkflnm ) );
//2006-07-06 CHG Osada ファイル名命名方法変更
//	sprintf( pHkkknri->hkkflnm, "%s%04d%s",
//			 pHkkknri->ssnmtfilid,
//			 pHkkknri->hkksjno,
//			 GD105_FILEEXT_DATA );
	sprintf( pHkkknri->hkkflnm, "%s%s",
			sNewFlName, GD105_FILEEXT_DATA);	

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：GD105CreateHULFTFile()										  */
/*　機能概要　：HULFT転送用ファイル作成										  */
/*　入　　力　：															  */
/*　　第１引数：GD105Env *pEnv		プログラム環境構造体					  */
/*　　第２引数：Sysknrmst *pSysknrmst システム管理マスタ情報				  */
/*　　第３引数：Hkkknri *pHkkknri	報告管理情報環境構造体					  */
/*　　第４引数：char *pDataFile		報告データファイル名					  */
/*　　第５引数：int iLogicalCnt		論理レコード件数						  */
/*　出　　力　：															  */
/*　　第３引数：Hkkknri *pHkkknri	報告管理情報環境構造体					  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
// 2006-04-06 H.Suyama Change Start
#if 0
//int GD105CreateHULFTFile(GD105Env *pEnv, Sysknrmst *pSysknrmst, Hkkknri *pHkkknri, char *pDataFile)
#else
//2006-07-06 CHG Osada ファイル名命名方法変更
//int GD105CreateHULFTFile(GD105Env *pEnv, Sysknrmst *pSysknrmst, Hkkknri *pHkkknri, char *pDataFile, int iLogicalCnt)
int GD105CreateHULFTFile(GD105Env *pEnv, Sysknrmst *pSysknrmst, Hkkknri *pHkkknri, char *pDataFile, int iLogicalCnt, Hkkknri *pHkkknriArrayOut)
#endif
// 2006-04-06 H.Suyama Change End
{
	int				iRet;
	char			cKjnsriymd[GD105_LEN_DATESHORT + 1];
	char			cSendFileTemp[PATH_MAX + 1];
	char			cSendFile[PATH_MAX + 1];
	FILE *			fpSrc;
	FILE *			fpDest;
	int				iLoop;
	int				iRecCnt;
	FILEHEADER		stHeader;
	FILETRAILER		stTrailer;
	char			cTemp[GD105_SIZE_BUFF + 1];
    //2006-07-06 ADD Osada ファイル名命名方法変更
    char            sNewFlName[PATH_MAX + 1];
    char            sKaisibi[10];
    int             i;
    //

	// 処理日付取得
	ZbmlChgAPDate( cKjnsriymd, pSysknrmst->kjnsriymd );
//1.06 DELL printf("基準処理年月日:[%s]\n", cKjnsriymd);
#ifdef _TRACE
	// 1.06 異常終了	LOG
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD105CreateHULFTFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"基準処理年月日:[%s]", cKjnsriymd );
#endif

	// ファイル名生成
//2006-07-06 CHG Osada ファイル名命名方法変更
#if 0
	sprintf( cSendFile, "%s/%s/%s/%s%04d%04d%s",
			 pEnv->cDirToday,
			 pEnv->cDirSendFile,
			 pEnv->cDirSendREQ,
			 cKjnsriymd,
			 pSysknrmst->ssntubn,
			 pHkkknri->hkksjno,
			 GD105_FILEEXT_DATA );
	sprintf( cSendFileTemp, "%s/%s/%s/%s%04d%04d%s",
			 pEnv->cDirToday,
			 pEnv->cDirSendFile,
			 pEnv->cDirSendREQ,
			 cKjnsriymd,
			 pSysknrmst->ssntubn,
			 pHkkknri->hkksjno,
			 GD105_FILEEXT_TEMP );
#else
    memset(sNewFlName, 0, sizeof(sNewFlName));
    switch(pHkkknriArrayOut->hkkjkn) {
    case '1':
        memcpy(sNewFlName, "CTRLNO", 6);
        break;
    case '2':
        memcpy(sNewFlName, "PLOTNO", 6);
        break;
    case '3':
        for(i=0; i < 16 ;++i) {
            if( (pHkkknriArrayOut->knsgrp[i] == 0) || (pHkkknriArrayOut->knsgrp[i] == ' ') ) {
                pHkkknriArrayOut->knsgrp[i] = '-';
            }
        }
        memcpy(sNewFlName, pHkkknriArrayOut->knsgrp, 6);
        break;
    case '4':
        memcpy(sNewFlName, "IRAINO", 6);
        break;
    case '5':
        memcpy(sNewFlName, "KENTNO", 6);
        break;
    }
    for(i=0; i < 2 ;++i) {
        if( (pHkkknriArrayOut->seccd[i] == 0) || (pHkkknriArrayOut->seccd[i] == ' ') ) {
            pHkkknriArrayOut->seccd[i] = '-';
        }
    }
    sprintf( cSendFile, "%s/%s/%s/%s_%04d_%s_%s_%s%04d%s",
			 pEnv->cDirToday,
			 pEnv->cDirSendFile,
			 pEnv->cDirSendREQ,
             pSysknrmst->sateid, pHkkknriArrayOut->hkksjno,
             pHkkknriArrayOut->seccd, sNewFlName, cKjnsriymd, pSysknrmst->ssntubn, 
			 GD105_FILEEXT_DATA );
			 cKjnsriymd,
    sprintf( cSendFileTemp, "%s/%s/%s/%s_%04d_%s_%s_%s%04d%s",
			 pEnv->cDirToday,
			 pEnv->cDirSendFile,
			 pEnv->cDirSendREQ,
             pSysknrmst->sateid, pHkkknriArrayOut->hkksjno,
             pHkkknriArrayOut->seccd, sNewFlName, cKjnsriymd, pSysknrmst->ssntubn,
			 GD105_FILEEXT_TEMP );
#endif
	// 報告データファイルオープン
	fpSrc = fopen ( pDataFile, "r" );
	if ( fpSrc == NULL ) {
		// 異常終了	LOG
// 1.06 DELL printf("file open error[%s]\n", pDataFile);
		// 1.06 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105CreateHULFTFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"file open error[%s]", pDataFile );

		gintErrorCode = GD105_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	// HULFT転送用ファイルオープン
	fpDest = fopen ( cSendFileTemp, "w" );
	if ( fpDest == NULL ) {
		// 異常終了	LOG
// 1.06 DELL printf("file open error[%s]\n", cSendFileTemp);
		// 1.06 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105CreateHULFTFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"file open error[%s]", cSendFileTemp );

		gintErrorCode = GD105_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	// ファイルヘッダの出力
	memset( &stHeader, GD105_DATA_SPACE, sizeof( stHeader ) );
	// レコード識別子
	ZbmlStrCpy( stHeader.cID, GD105_FILE_HEADERID, sizeof( stHeader.cID ) );
	// 送信先ID
	ZbmlStrCpy( stHeader.cSendToID, pEnv->cSendIDSaki, sizeof( stHeader.cSendToID ) );
	// 送信元ID
	ZbmlStrCpy( stHeader.cSendFromID, pEnv->cSendIDMoto, sizeof( stHeader.cSendFromID ) );
	// 送信元処理年月日
	ZbmlStrCpy( stHeader.cSendDate, cKjnsriymd, sizeof( stHeader.cSendDate ) );
	// 通番
	sprintf( cTemp, "%04d", pSysknrmst->ssntubn );
	ZbmlStrCpy( stHeader.cSeqNo, cTemp, sizeof( stHeader.cSeqNo ) );
	// ﾃﾞｰﾀﾌﾛｰID
	ZbmlStrCpy( stHeader.cDataFlowID, pEnv->cDataFlowID, sizeof( stHeader.cDataFlowID ) );
	// ﾊﾟﾗﾒｰﾀ1
	//stHeader.cParam1
// 2006-04-20 H.Suyama Add Start
	// 1.07 INTEC UPD cSendIDSaki -> cSendIDMoto
	//							pEnv->cSendIDSaki,
//CHG E.Osada 2006-07-18
#if 0
	if ( GD105CopyFromLeft( stHeader.cParam1,
							pEnv->cSendIDMoto,
							8,
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	sprintf( cTemp, "%04d%04d", pSysknrmst->ssntubn, pHkkknri->hkksjno );
	if ( GD105CopyFromLeft( &stHeader.cParam1[8],
							cTemp,
							8,
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
#else
	memset(cTemp, 0, sizeof(cTemp));
	memset(stHeader.cParam1, 0, sizeof(stHeader.cParam1));
	sprintf( cTemp, "%s_%04d_%s_%s_%s%04d%s",
             pSysknrmst->sateid, pHkkknriArrayOut->hkksjno,
             pHkkknriArrayOut->seccd, sNewFlName, cKjnsriymd, pSysknrmst->ssntubn,
			 GD105_FILEEXT_DATA );
	/*
	if ( GD105CopyFromLeft( stHeader.cParam1,
							cTemp,
							8,
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	*/
	memset(stHeader.cParam1, ' ', 128);
	memcpy(stHeader.cParam1, cTemp, 18);
#endif
// 2006-04-20 H.Suyama Add End
	// ﾊﾟﾗﾒｰﾀ2
	//stHeader.cParam2
	// 予備
	//stHeader.cReserve
	// 最後に'\n'をつける
	stHeader.cReserve[sizeof( stHeader.cReserve ) - 1] = GD105_FILE_LINEFEED;

	iRet = fwrite( (char *)&stHeader, sizeof( stHeader ), 1, fpDest);
	if ( iRet != 1 ) {
		//エラーログ出力
//1.06 DELL printf("fwrite header error \n");
		// 1.06 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105CreateHULFTFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"fwrite header error" );

		return( RTN_NG );
	}

	// レコード件数クリア
	iRecCnt = 0;

	// 読み込み
	while ( iRet = fgets( cTemp, sizeof ( cTemp ), fpSrc ) != NULL ) {
		if ( fputs( cTemp, fpDest ) < 0 ) {
			//エラーログ出力
//1.06 DELL printf("fputs error \n");
			// 1.06 異常終了	LOG
			sFncPutLog(TRCKIND_ERROR, __FILE__,"GD105CreateHULFTFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"fputs error " );

			return( RTN_NG );
		}
		// レコード件数カウント
		++iRecCnt;
	}

	// ファイルトレーラの出力
	memset( &stTrailer, GD105_DATA_SPACE, sizeof( stTrailer ) );
	// レコード識別子
	ZbmlStrCpy( stTrailer.cID, GD105_FILE_TRAILERID, sizeof( stTrailer.cID ) );
	// 送信先ID
// 2006-04-06 H.Suyama Change Start
#if 0
//	ZbmlStrCpy( stHeader.cSendToID, pEnv->cSendIDSaki, sizeof( stHeader.cSendToID ) );
#else
	ZbmlStrCpy( stTrailer.cSendToID, pEnv->cSendIDSaki, sizeof( stTrailer.cSendToID ) );
#endif
// 2006-04-06 H.Suyama Change End
	// 送信元ID
// 2006-04-06 H.Suyama Change Start
#if 0
//	ZbmlStrCpy( stHeader.cSendFromID, pEnv->cSendIDMoto, sizeof( stHeader.cSendFromID ) );
#else
	ZbmlStrCpy( stTrailer.cSendFromID, pEnv->cSendIDMoto, sizeof( stTrailer.cSendFromID ) );
#endif
// 2006-04-06 H.Suyama Change End
	// 送信元処理年月日
	ZbmlStrCpy( stTrailer.cSendDate, cKjnsriymd, sizeof( stTrailer.cSendDate ) );
	// 通番
	sprintf( cTemp, "%04d", pSysknrmst->ssntubn );
	ZbmlStrCpy( stTrailer.cSeqNo, cTemp, sizeof( stTrailer.cSeqNo ) );
	// ﾃﾞｰﾀﾌﾛｰID
// 2006-04-06 H.Suyama Change Start
#if 0
//	ZbmlStrCpy( stHeader.cDataFlowID, pEnv->cDataFlowID, sizeof( stHeader.cDataFlowID ) );
#else
	ZbmlStrCpy( stTrailer.cDataFlowID, pEnv->cDataFlowID, sizeof( stTrailer.cDataFlowID ) );
#endif
// 2006-04-06 H.Suyama Change End
	// 物理ﾚｺｰﾄﾞ件数
// 2006-04-06 H.Suyama Change Start
#if 0
//	sprintf( cTemp, "%04d", iRecCnt );
#else
	// レコード件数にヘッダとトレーラ分を加算
// 2006-04-07 H.Suyama Change Start
#if 0
//	sprintf( cTemp, "%04d", iRecCnt + 2 );
#else
	sprintf( cTemp, "%08d", iRecCnt + 2 );
#endif
// 2006-04-07 H.Suyama Change End
#endif
// 2006-04-06 H.Suyama Change End
	ZbmlStrCpy( stTrailer.cPhysicalCnt, cTemp, sizeof( stTrailer.cPhysicalCnt ) );
	// 論理ﾚｺｰﾄﾞ件数１
	// レコード件数にヘッダとトレーラ分を加算
// 2006-04-06 H.Suyama Change Start
#if 0
//	sprintf( cTemp, "%08d", iRecCnt + 2 );
#else
	sprintf( cTemp, "%08d", iLogicalCnt );
#endif
// 2006-04-06 H.Suyama Change End
	ZbmlStrCpy( stTrailer.cRecCnt1, cTemp, sizeof( stTrailer.cRecCnt1 ) );
	// 論理ﾚｺｰﾄﾞ件数２
	memset( stTrailer.cRecCnt2, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt2 ) );
	// 論理ﾚｺｰﾄﾞ件数３
	memset( stTrailer.cRecCnt3, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt3 ) );
	// 論理ﾚｺｰﾄﾞ件数４
	memset( stTrailer.cRecCnt4, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt4 ) );
	// 論理ﾚｺｰﾄﾞ件数５
	memset( stTrailer.cRecCnt5, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt5 ) );
	// 論理ﾚｺｰﾄﾞ件数６
	memset( stTrailer.cRecCnt6, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt6 ) );
	// 論理ﾚｺｰﾄﾞ件数７
	memset( stTrailer.cRecCnt7, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt7 ) );
	// 論理ﾚｺｰﾄﾞ件数８
	memset( stTrailer.cRecCnt8, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt8 ) );
	// 論理ﾚｺｰﾄﾞ件数９
	memset( stTrailer.cRecCnt9, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt9 ) );
	// 論理ﾚｺｰﾄﾞ件数１０
	memset( stTrailer.cRecCnt10, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt10 ) );
	// 論理ﾚｺｰﾄﾞ件数１１
	memset( stTrailer.cRecCnt11, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt11 ) );
	// 論理ﾚｺｰﾄﾞ件数１２
	memset( stTrailer.cRecCnt12, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt12 ) );
	// 論理ﾚｺｰﾄﾞ件数１３
	memset( stTrailer.cRecCnt13, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt13 ) );
	// 論理ﾚｺｰﾄﾞ件数１４
	memset( stTrailer.cRecCnt14, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt14 ) );
	// 論理ﾚｺｰﾄﾞ件数１５
	memset( stTrailer.cRecCnt15, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt15 ) );
	// 予備
	//stTrailer.cReserve
	// 最後に'\n'をつける
	stTrailer.cReserve[sizeof( stTrailer.cReserve ) - 1] = GD105_FILE_LINEFEED;

	iRet = fwrite( (char *)&stTrailer, sizeof( stTrailer ), 1, fpDest);
	if ( iRet != 1 ) {
		//エラーログ出力
//1.06 DELL printf("fwrite trailer error \n");
		// 1.06 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105CreateHULFTFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"fwrite trailer error " );

		return( RTN_NG );
	}

	// ファイルクローズ
	fclose( fpSrc );
	fclose( fpDest );

	// ファイル拡張子名変更
	iRet = rename( cSendFileTemp, cSendFile );
	if ( iRet != 0 ) {
		// 異常終了	LOG
//1.06 DELL printf("CreateHULFTFile rename status:[%d]\n", iRet);
		// 1.06 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105CreateHULFTFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"CreateHULFTFile rename status:[%d] ", iRet );

		gintErrorCode = GD105_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	// 返却用にファイル名と送信ファイルＩＤを設定
	memset( pHkkknri->hkkflnm, 0, sizeof( pHkkknri->hkkflnm ) );
//2006-07-06 CHG Osada ファイル名命名方法変更
//	sprintf( pHkkknri->hkkflnm, "%s%04d%04d%s",
//			 cKjnsriymd,
//			 pSysknrmst->ssntubn,
//			 pHkkknri->hkksjno,
//			 GD105_FILEEXT_DATA );
	sprintf( pHkkknri->hkkflnm, "%s_%04d_%s_%s_%s%04d%s",
             pSysknrmst->sateid, pHkkknriArrayOut->hkksjno,
             pHkkknriArrayOut->seccd, sNewFlName, cKjnsriymd, pSysknrmst->ssntubn,
			 GD105_FILEEXT_DATA );
	memset( pHkkknri->ssnmtfilid, 0, sizeof( pHkkknri->ssnmtfilid ) );
	sprintf( pHkkknri->ssnmtfilid, "%s%04d",
			 cKjnsriymd,
			 pSysknrmst->ssntubn );

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：GD105CreateFile()											  */
/*　機能概要　：報告データファイル作成										  */
/*　入　　力　：															  */
/*　　第１引数：GD105Env *pEnv		プログラム環境構造体					  */
/*　　第２引数：Sysknrmst *pSysknrmst システム管理マスタ情報				  */
/*　　第３引数：Kekka *pKekkaArray	検査結果情報							  */
/*　　第４引数：int iKekkaNum		検査結果情報件数						  */
/*　出　　力　：															  */
/*　　第５引数：int *piHkkssknsu	作成件数								  */
/*　　第６引数：int *piHkkhrysu		保留件数								  */
/*　　第７引数：char *pFileName		ファイル名								  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int GD105CreateFile(GD105Env *pEnv,
					Sysknrmst *pSysknrmst,
					Kekka *pKekkaArray,
					int iKekkaNum,
					int *piHkkssknsu,
					int *piHkkhrysu,
					char *pFileName,
					int *sqlErrorFlag)//2006.12.08 Kim Jinsuk DBエラー時異常終了させる
{
	int				iRet;
	struct dirent	**pDirEnt;
	int				iFileCnt;
	int	 			iSeqNo;
	char			cSeqBuff[10];
	BmlDate			today;
	char			cToday[GD105_LEN_DATESHORT + 1];
	char			cFileNameTemp[PATH_MAX + 1];
	char			cFileName[PATH_MAX + 1];
	FILE *			fp;
	int				iLoop;
	GD105Rec		stGD105RecTemp;
	int				iKekkaLoop;
	GD105Rec		stGD105Rec[GD105_REC_LOOP_MAX];
	int				iFileLoopIdx;
/*	int				iCmmtCnt=0; */
	int				iFlg911=0;

/* 2.00 2009.05.19 結果変換マスタ対応 START */
	char			cSstcd[7+1];		/* 施設コード */
	int				iSstcdLoopCnt;		/* 施設コード用ループカウンタ */
	int				iKkaconvCnt;		/* 結果変換マスタ件数ループカウンタ */
	int				iRetChk;			/* 結果変換処理フラグ */
/* 2.00 2009.05.19 結果変換マスタ対応 END */

	// 引数チェック
	if ( pEnv == NULL || pSysknrmst == NULL || pKekkaArray == NULL ||
		 piHkkssknsu == NULL || piHkkhrysu == NULL || pFileName == NULL ) {
		// 異常終了	LOG
//1.06 DELL printf("GD105CreateFile parameter is NULL\n");
		// 1.06 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105CreateFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"GD105CreateFile parameter is NULL");

		gintErrorCode = GD105_STSCODE_ERR_FR_FILE;
		return( RTN_NG );
	}

	// データファイル用ディレクトリを検索
	// フィルタにより、当日のYYYYMMDD9999で始まるファイルのみ検索
	if ( ( iFileCnt = scandir( pEnv->cDirDataFile,
							   &pDirEnt,
							   (void *)GD105DataFileFilter,
							   alphasort ) ) < 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_DIR;
		return( RTN_NG );
	}

	// ファイルSEQを採番
	if ( iFileCnt == 0 ) {
		iSeqNo = 1;
	} else {
		memset( cSeqBuff, 0, sizeof( cSeqBuff ) );
		strcpy( cFileName, pDirEnt[iFileCnt - 1]->d_name );
		memcpy( cSeqBuff, &cFileName[GD105_LEN_DATESHORT],
			GD105_LEN_FILESEQNO );
		iSeqNo = atoi( cSeqBuff ) + 1;
	}

	// 内部メモリ解放
	for ( iLoop = 0; iLoop < iFileCnt; iLoop++ ) {
		ZbmlFree( pDirEnt[iLoop] );
	}

	// 当日日付取得
	if ( ZbmlDateGetToday(&today) == FALSE ) {
		return( RTN_NG );
	}
	sprintf( cToday, "%04d%02d%02d", today.year, today.month, today.day);

	// ファイル名生成
	sprintf( cFileName, "%s/%s%04d%s",
			 pEnv->cDirDataFile, cToday, iSeqNo, GD105_FILEEXT_DATA );

	// ファイルオープン
	fp = fopen ( cFileName, "w" );
	if ( fp == NULL ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	// 結果情報を１件ずつ処理
	for ( iKekkaLoop = 0, iFileLoopIdx  = 0;
		  iKekkaLoop < iKekkaNum;
		  iKekkaLoop++ ) {
		// 保留かどうかチェック
		if ( pKekkaArray[iKekkaLoop].knsflg == GD105_DB_KNSFLG_HORYU ) {
			// 保留数カウンタ +1
			++*piHkkhrysu;
			continue;
		}

		// Add 2007.05.09 waj
		// knskka1,knskka2共にスペースの場合、報告レコードを作成せず保留扱いとする
		// Add 2008.02.07 Nagata
		// knskka2が'////////'の場合、報告レコードを作成せず保留扱いにする。
		if ( ( (strncmp(pKekkaArray[iKekkaLoop].knskka1, "            ", 12) == 0) &&
		       (strncmp(pKekkaArray[iKekkaLoop].knskka2, "                        ", 24) == 0) )
			|| strncmp(pKekkaArray[iKekkaLoop].knskka2, "////////", 8) == 0) {

            sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105CreateFile", __LINE__,
                        EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
                        "knskka1,knskka2共にスペースのため保留とする [%s %s %d]",
						pKekkaArray[iKekkaLoop].sriymd,pKekkaArray[iKekkaLoop].kmkcd,pKekkaArray[iKekkaLoop].knsseq);

			// 検査フラグに保留を設定
			pKekkaArray[iKekkaLoop].knsflg = GD105_DB_KNSFLG_HORYU;
			
			// 保留数カウンタ +1
			++*piHkkhrysu;

			continue;
		}

		// 繰返し件数に達したらファイル出力
		if ( iFileLoopIdx >= GD105_REC_LOOP_MAX ) {
			// ファイル出力
			if ( GD105WriteFile( fp, &stGD105Rec[0], GD105_REC_LOOP_MAX ) == RTN_NG ) {
				// 異常終了	LOG
//1.06 DELL printf("GD105WriteFile error\n");
				// 1.06 異常終了	LOG
				sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105CreateFile",__LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"GD105WriteFile error" );

				return( RTN_NG );
			}

			iFileLoopIdx = 0;
		}

/* 2.00 2009.05.19 結果変換マスタ対応 START */
		/*******************************************************************/
		/* knskka2kbn == '0'の場合、既にコメント入力されている状態なので、 */
		/* 自動変換の対象にしない。                                        */
		/*******************************************************************/
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"pKekkaArray[%d].knskka2kbn[0] = [%c]", iKekkaLoop, pKekkaArray[iKekkaLoop].knskka2kbn[0] );
#endif
		if (pKekkaArray[iKekkaLoop].knskka2kbn[0] != GD105_DATA_CHAR0)
		{
			/* 結果変換処理フラグ初期化 */
			iRetChk = 0;

			/**************************************************************************/
			/* 結果テーブルの施設コードと結果変換マスタの施設コードが一致しない場合、 */
			/* 施設コード＝'0000000'でもう一度処理する。                              */
			/**************************************************************************/
			for (iSstcdLoopCnt = 0; iSstcdLoopCnt < GD105_SSTCD_LOOP_CNT; iSstcdLoopCnt++)
			{
				memset(cSstcd, 0, sizeof(cSstcd));
				/* 1回目ループ：施設コード = 結果テーブルの施設コード(ただし、'0000000' でない場合) */
				if (iSstcdLoopCnt == 0 &&
					memcmp(pKekkaArray[iKekkaLoop].sstcd, GD105_SSTCD_ALL_ZERO, sizeof(pKekkaArray[iKekkaLoop].sstcd) - 1) != 0)
				{
					strcpy(cSstcd, pKekkaArray[iKekkaLoop].sstcd);
				}
				/* 2回目ループ：施設コード = '0000000' (ALLゼロ)でもう一度検索に行く */
				else
				{
					strcpy(cSstcd, GD105_SSTCD_ALL_ZERO);
					iSstcdLoopCnt++;
				}

				/********************************************************************/
				/* 結果変換マスタチェック(処理中の項目がマスタに設定されているか？) */
				/********************************************************************/
				for (iKkaconvCnt = 0; iKkaconvCnt < g_iNumOut; iKkaconvCnt++)
				{
#ifdef _DEBUG
					sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"● 結果キーと結果変換マスタキー比較" );
					sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"  ◆ 結果キー" );
					sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"    pKekkaArray[%d].knsgrp   = [%s]", iKekkaLoop, pKekkaArray[iKekkaLoop].knsgrp );
					sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"    pKekkaArray[%d].kmkcd    = [%s]", iKekkaLoop, pKekkaArray[iKekkaLoop].kmkcd );
					sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"    cSstcd                   = [%s]", cSstcd );

					sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"  ◆ 結果変換マスタキー" );
					sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"    g_pKkaconvmst[%d].knsgrp = [%s]", iKkaconvCnt, g_pKkaconvmst[iKkaconvCnt].knsgrp );
					sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"    g_pKkaconvmst[%d].kmkcd  = [%s]", iKkaconvCnt, g_pKkaconvmst[iKkaconvCnt].kmkcd );
					sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"    g_pKkaconvmst[%d].sstcd  = [%s]", iKkaconvCnt, g_pKkaconvmst[iKkaconvCnt].sstcd );
#endif

					/* 下記の条件でマスタ検索を抜ける(マスタはプライマリキーでソートしてあり無駄ループさせない為)   */
					/*   ・結果.検査G < マスタ.検査G                                                                */
					/*   ・結果.検査G = マスタ.検査G && 結果.項目CD < マスタ.項目CD                                 */
					/*   ・結果.検査G = マスタ.検査G && 結果.項目CD = マスタ.項目CD && 結果.施設CD < マスタ.施設CD  */
					if ((atoi(pKekkaArray[iKekkaLoop].knsgrp) <  atoi(g_pKkaconvmst[iKkaconvCnt].knsgrp)) ||
						
						(atoi(pKekkaArray[iKekkaLoop].knsgrp) == atoi(g_pKkaconvmst[iKkaconvCnt].knsgrp)  &&
						 atoi(pKekkaArray[iKekkaLoop].kmkcd)  <  atoi(g_pKkaconvmst[iKkaconvCnt].kmkcd))  ||
						
						(atoi(pKekkaArray[iKekkaLoop].knsgrp) == atoi(g_pKkaconvmst[iKkaconvCnt].knsgrp)  &&
						 atoi(pKekkaArray[iKekkaLoop].kmkcd)  == atoi(g_pKkaconvmst[iKkaconvCnt].kmkcd)   &&
						 atoi(cSstcd)                         <  atoi(g_pKkaconvmst[iKkaconvCnt].sstcd)))
					{
#ifdef _DEBUG
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"● 結果キー < 結果変換マスタキー なので break！" );
#endif
						break;
					}

					/* 検査グループ、項目コード、施設コード、材料コード、開始日～廃止日に合致した場合 */
					if (memcmp(g_pKkaconvmst[iKkaconvCnt].knsgrp, pKekkaArray[iKekkaLoop].knsgrp, sizeof(pKekkaArray[iKekkaLoop].knsgrp)-1) == 0 &&
						memcmp(g_pKkaconvmst[iKkaconvCnt].kmkcd, pKekkaArray[iKekkaLoop].kmkcd, sizeof(pKekkaArray[iKekkaLoop].kmkcd)-1) == 0 &&
						memcmp(g_pKkaconvmst[iKkaconvCnt].sstcd, cSstcd, sizeof(cSstcd)-1) == 0 &&
						(memcmp(g_pKkaconvmst[iKkaconvCnt].kaiymd, pKekkaArray[iKekkaLoop].knskisymd, sizeof(pKekkaArray[iKekkaLoop].knskisymd)-1) <= 0 &&
						 memcmp(pKekkaArray[iKekkaLoop].knskisymd, g_pKkaconvmst[iKkaconvCnt].haiymd, sizeof(pKekkaArray[iKekkaLoop].knskisymd)-1) <= 0))
					{
#ifdef _DEBUG
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"● 結果変換マスタチェック - 開始" );
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"  ◆ 結果変換マスタデータ" );
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"    g_pKkaconvmst[%d]->knsgrp = [%s]", iKkaconvCnt, g_pKkaconvmst[iKkaconvCnt].knsgrp );
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"    g_pKkaconvmst[%d]->kmkcd  = [%s]", iKkaconvCnt, g_pKkaconvmst[iKkaconvCnt].kmkcd );
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"    g_pKkaconvmst[%d]->sstcd  = [%s]", iKkaconvCnt, g_pKkaconvmst[iKkaconvCnt].sstcd );
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"    g_pKkaconvmst[%d]->kaiymd = [%s]", iKkaconvCnt, g_pKkaconvmst[iKkaconvCnt].kaiymd );
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"    g_pKkaconvmst[%d]->haiymd = [%s]", iKkaconvCnt, g_pKkaconvmst[iKkaconvCnt].haiymd );
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"  ◆ 結果情報データ" );
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"    pKekkaArray[%d].knskisymd = [%s]", iKekkaLoop, pKekkaArray[iKekkaLoop].knskisymd );
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"    pKekkaArray[%d].knsgrp    = [%s]", iKekkaLoop, pKekkaArray[iKekkaLoop].knsgrp );
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"    pKekkaArray[%d].kmkcd     = [%s]", iKekkaLoop, pKekkaArray[iKekkaLoop].kmkcd );
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"    cSstcd                    = [%s]", cSstcd );
#endif

						/* 結果変換チェック関数 */
						iRet = GD105KkaConvChk(&pKekkaArray[iKekkaLoop], &g_pKkaconvmst[iKkaconvCnt], cSstcd);
						/* 結果変換した場合 */
						if (iRet == RTN_OK)
						{
							/* 結果変換済み */
#ifdef _DEBUG
							sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
										"  ◆ 結果変換済み" );
#endif
							iRetChk = 1;
							break;
						}
						/* 変換対象にならず、スキップした場合 */
						else if (iRet == RTN_SKIP)
						{
#ifdef _DEBUG
							sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
										"  ◆ 変換対象にならず、スキップした" );
#endif
						}
						/* 何かしらのエラーがあった場合 */
						else if ( iRet == RTN_NG )
						{
							// 異常終了	LOG
							sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105CreateFile", __LINE__,
										EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
										"GD105KkaConvChk ERROR iRet = [%d]", iRet );

							return RTN_NG;
						}
					}
				}
				
				/* 結果変換した場合は施設ループ処理を抜ける */
				if (iRetChk == 1)
				{
#ifdef _DEBUG
					sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"  ◆ 施設ループ処理を抜ける" );
#endif
					break;
				}
			}
		}
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"● 結果変換マスタチェック - 終了" );
#endif
/* 2.00 2009.05.19 結果変換マスタ対応 END */

		// 結果をファイル出力形式に展開
		if ( GD105MakeData( &pKekkaArray[iKekkaLoop],
							pSysknrmst->lbcd,
							&stGD105Rec[iFileLoopIdx] ) == RTN_NG ) {
			// 異常終了	LOG
			sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105CreateFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"GD105MakeData error" );

			return( RTN_NG );
		}

		++*piHkkssknsu;

		++iFileLoopIdx;
	}

	// 1.12 ADD 保留以外報告対象0件の場合の考慮
	if( *piHkkssknsu == 0 || iFlg911 == 1 ){
			// ファイルクローズ
			fclose( fp );
			// 中間ファイルなので0byte作成もOKとし、ファイル削除は行わない
			return( RTN_NG );
	}

	// ファイル出力
	if ( GD105WriteFile( fp, &stGD105Rec[0], iFileLoopIdx ) == RTN_NG ) {
		// 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105CreateFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"GD105WriteFile error " );
		return( RTN_NG );
	}

	// ファイルクローズ
	fclose( fp );

	// ファイル名（フルパス）を返却
	ZbmlInfocpy( pFileName, cFileName, PATH_MAX );
	return( RTN_OK );
}


/******************************************************************************/
/*　関 数 名　：GD105UpdateKekka()											  */
/*　機能概要　：報告データ フラグ更新										  */
/*　入　　力　：															  */
/*　　第１引数：GD105Env *pEnv		プログラム環境構造体					  */
/*　　第２引数：Sysknrmst *pSysknrmst システム管理マスタ情報				  */
/*　　第３引数：Kekka *pKekkaArray	検査結果情報							  */
/*　　第４引数：int iKekkaNum		検査結果情報件数						  */
/*　出　　力　：															  */
/*　　第５引数：int *splErrorFlag	エラー停止フラグ						  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int GD105UpdateKekka(GD105Env *pEnv,
					Sysknrmst *pSysknrmst,
					Kekka *pKekkaArray,
					int iKekkaNum,
					int *sqlErrorFlag)
{
	int				iRet;
	int				iLoop;
	int				iKekkaLoop;
	int				iFileLoopIdx;
	int				iCmmtCnt=0;

	char			last_sriymd[11];
	char			last_kntno[11];
	char			last_knsgrp[17];

	strcpy(last_sriymd, pKekkaArray[0].sriymd);
	strcpy(last_kntno, pKekkaArray[0].kntno);
	strcpy(last_knsgrp, pKekkaArray[0].knsgrp);

	for ( iKekkaLoop = 0, iFileLoopIdx  = 0;
		  iKekkaLoop < iKekkaNum;
		  iKekkaLoop++ ) {

		/* COMMIT単位を検体単位に変更 件数はINIファイルに設定 */
		if ( (strncmp(pKekkaArray[iKekkaLoop].sriymd, last_sriymd , 11) != 0) ||
			 (strncmp(pKekkaArray[iKekkaLoop].kntno, last_kntno , 11) != 0) ||
			 (strncmp(pKekkaArray[iKekkaLoop].knsgrp, last_knsgrp , 17) != 0) ) {

			++iCmmtCnt;
			if( iCmmtCnt >= pEnv->iCommitSu ){
        		ZdbCommit();
				iCmmtCnt=0;
			}
		}

		if ( pKekkaArray[iKekkaLoop].knsflg == GD105_DB_KNSFLG_HORYU ) {
			// 保留の場合はフラグを変更しない。
		} else {
			// 結果修正フラグをカウントアップ（最大'9'）
			if ( pKekkaArray[iKekkaLoop].kkassflg == GD105_DATA_SPACE ) {
				pKekkaArray[iKekkaLoop].kkassflg = '0';
			} else if ( pKekkaArray[iKekkaLoop].kkassflg != GD105_DB_KKASSFLG_MAX ) {
				++pKekkaArray[iKekkaLoop].kkassflg;
			}

			// 検査フラグ←報告済
			pKekkaArray[iKekkaLoop].knsflg = GD105_DB_KNSFLG_DONE;
		}

		// 情報更新日時は関数内で設定
        int nRetValue;

		// 検査結果情報を更新
		iRet = ZdbKekkaGD105Update( &pKekkaArray[iKekkaLoop] );
		if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
			// 異常終了	LOG
			sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105UpdateKekka", __LINE__,
						EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
						"ZdbKekkaGD105Update error(%d)", iRet);

            nRetValue = iRet;

			// ロールバック
			ZdbRollback();

			if((nRetValue < 0) && (nRetValue !=-803) && (nRetValue != -911)) {
				*sqlErrorFlag = 1;
				sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbKekkaGD105Update", __LINE__,
							EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
							"DB エラー　発生　error value 0 %d", iRet);
			}
			return( RTN_NG );
		}

		if ( pKekkaArray[iKekkaLoop].knsflg == GD105_DB_KNSFLG_HORYU ) {
			//保留の場合は ZdbKekkaGD105UpdateOthers(未報告完了への更新)を行わない。
		} else if ( pKekkaArray[iKekkaLoop].kkajkcd == GD105_DB_KKAJKCD_LAST ) {
			iRet = ZdbKekkaGD105UpdateOthers( &pKekkaArray[iKekkaLoop] );
			if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
				// 1.06 異常終了	LOG
				sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105UpdateKekka",__LINE__,
							EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
							"ZdbKekkaGD105UpdateOthers error (%d)", iRet);

 				nRetValue = iRet;				

				// ロールバック
				ZdbRollback();
			
				if((nRetValue < 0) && (nRetValue !=-803) && (nRetValue != -911)) {
    				*sqlErrorFlag = 1;
					sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbKekkaGD105Update", __LINE__,
								EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
								"DB エラー　発生　error value 0 %d", iRet);
				}
				return( RTN_NG );
			}
		}
		
		strcpy(last_sriymd, pKekkaArray[iKekkaLoop].sriymd);
		strcpy(last_kntno, pKekkaArray[iKekkaLoop].kntno);
		strcpy(last_knsgrp, pKekkaArray[iKekkaLoop].knsgrp);

		++iFileLoopIdx;
	}

	ZdbCommit();

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：sFncShmCrt()												  */
/*　機能概要　：共有メモリ生成												  */
/*　入　　力　：															  */
/*　　第１引数：GD105Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：なし														  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
static int sFncShmCrt( GD105Env *pEnv )
{
	int	 *shmData;

	// 取得
	pEnv->shm_Id = shmget( (key_t)pEnv->shm_Key,
							GD105_SHM_SIZE,
							0666 | IPC_CREAT );
	if ( pEnv->shm_Id < 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_SHM_GET;
		return( RTN_NG );
	}

	// アタッチ
	shmData = ( int * ) shmat( pEnv->shm_Id, 0 , 0 );
	if ( shmData == ( int * )-1 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_SHM_AT;
		return( RTN_NG );
	}
loging ( "stocker : 共有メモリ[CRT] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n",
		 pEnv->shm_Key, pEnv->shm_Id, *shmData, shmData );

	// 値設定
	*shmData = 0;

	// デタッチ
	if ( shmdt( shmData ) == -1 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_SHM_DT;
		return( RTN_NG );
	}

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：sFncShmGet()												  */
/*　機能概要　：共有メモリ取得												  */
/*　入　　力　：															  */
/*　　第１引数：GD105Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　　第２引数：int *pshmData		値										  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
static int sFncShmGet( GD105Env *pEnv, int *pshmData )
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
		gintErrorCode = GD105_STSCODE_ERR_SHM_AT;
		return( RTN_NG );
	}

	// 値設定
	*pshmData = *shmData;

loging ( "stocker : 共有メモリ[GET] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n",
		 pEnv->shm_Key, pEnv->shm_Id, *shmData, shmData );
	// デタッチ
	if ( shmdt( shmData ) == -1 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_SHM_DT;
		return( RTN_NG );
	}

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：sFncShmDel()												  */
/*　機能概要　：共有メモリ削除												  */
/*　入　　力　：															  */
/*　　第１引数：GD105Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
static int sFncShmDel( GD105Env *pEnv )
{
	int	 *shmData;

loging ( "%s : 共有メモリ[DEL] shmKey[%d]-ID[%d]\n",
		 MYAPP_APP_NAME, pEnv->shm_Key, pEnv->shm_Id);
	// 削除
	if ( shmctl( pEnv->shm_Id, IPC_RMID, NULL) < 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD105_STSCODE_ERR_SHM_DEL;
		return( RTN_NG );
	}
	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：_sFncEnvDip()												  */
/*　機能概要　：プログラム環境変数出力関数【トレース用】					  */
/*　入　　力　：															  */
/*　　第１引数：GD105Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：無し														  */
/******************************************************************************/
static void _sFncEnvDip( GD105Env *pEnv )
{
//#if defined ( _TRACE )
	loging( "########## GD105 - _sFncEnvDip ##########\n" );
	loging( "\t%s : [%s]\n", GD105_PRM_DBNAME,		 pEnv->cDBName );
	loging( "\t%s : [%s]\n", GD105_PRM_DBUSER,		 pEnv->cDBUser );
	loging( "\t%s : [%s]\n", GD105_PRM_DBPAWD,		 pEnv->cDBPawd );
	loging( "\t%s : [%s]\n", GD105_PRM_DIR_DATAFILE,   pEnv->cDirDataFile );
	loging( "\t%s : [%s]\n", GD105_PRM_SLEEP_SEC,	  pEnv->iSleepSec );
	loging( "\t%s : [%s]\n", GD105_PRM_SHM_KEY,	pEnv->shm_Key );
	loging( "\t%s : [%s]\n", GD105_PRM_FILE_DBG,	pEnv->cDebugLogName );
	loging( "\t%s : [%s]\n", GD105_PRM_FILE_TR,	pEnv->cTraceLogName );
	loging( "\t%s : [%s]\n", GD105_PRM_FILE_ACS,	pEnv->cAccessLogName );
	loging( "\t%s : [%s]\n", GD105_PRM_FILE_ERR,	pEnv->cErrorLogName );
	loging( "\t%s : [%s]\n", GD105_PRM_UP_ID,		pEnv->cUpdateId );
	loging( "\t%s : [%s]\n", GD105_PRM_UP_NM,		pEnv->cUpdateName );
	loging( "\t%s : [%s]\n", GD105_PRM_PROC_MD,	pEnv->proc_mode );
	loging( "########## GD105 - _sFncEnvDip ##########\n" );
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
/*　機能概要　：報告データファイル作成処理メイン							  */
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
	GD105Env	stEnv;

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
