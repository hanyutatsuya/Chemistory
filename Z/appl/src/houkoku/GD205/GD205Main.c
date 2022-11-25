/********************************************************************/
/*																	*/
/*		ＢＭＬ様向け検査システム									*/
/*																	*/
/*		システム名	：次世代システム								*/
/*		ファイル名	：GD205Main.c									*/
/*		概要		：緊急結果報告ファイル作成処理					*/
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
/*  3.01    2007/06/05      INTEC.INC       緊急用に変更            */
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
#include "GD205Main.h"
#include "GD205Hkkknri.h"

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
GD205_STSCODE		gintErrorCode;
struct stcLogMember	gstLogMem;
char        G_msg[256];     // 1.06 ADD LogMessage

/******************************************************************************/
/*　関 数 名　：GD205ConvTimestamp()										  */
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
void GD205ConvTimestamp(ULONG ulTm, char *pDest)
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
/*　関 数 名　：GD205ConvNumber()                                             */
/*　機能概要　：依頼書No、検体No変換関数                                      */
/*　入　　力　：                                                              */
/*　　第２引数：char *pSrc          変換前文字列                              */
/*　　　　　　                      [1][2][3][4][5][6][7][8][9][10][11]\0     */
/*　出　　力　：                                                              */
/*　　第１引数：char *pDest         変換後文字列                              */
/*　　　　　　                      [3][4][5] 0  0 [6][7][8][9][10][11]       */
/*　復帰情報　：int                                                           */
/*　　　　　　      RTN_OK  : 正常終了                                        */
/*　　　　　　      RTN_NG  : 異常終了                                        */
/******************************************************************************/
int GD205ConvNumber(char *pDest, char *pSrc)
{
    // ポインタのチェック
    if ( pDest == NULL || pSrc == NULL ) {
        return( RTN_NG );
    }

    // 変換前文字列の長さチェック
    if ( strlen( pSrc ) < GD205_LEN_NOITEM ) {
        return( RTN_NG );
    }

	/* PNC11桁に変換 */
	sprintf (pDest,"%-3.3s00%-6.6s",&pSrc[GD205_POS_SRCNO1],&pSrc[GD205_POS_SRCNO2]);

    return( RTN_OK );
}


/******************************************************************************/
/*　関 数 名　：GD205CopyFromLeft()											  */
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
int GD205CopyFromLeft(char *pDest, char *pSrc, int iSize, BOOL bMbFlg)
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
/*　関 数 名　：GD205CopyFromRight()										  */
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
int GD205CopyFromRight(char *pDest, char *pSrc, int iSize, BOOL bMbFlg)
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

/******************************************************************************/
/*　関 数 名　：GD205CopyReplace()   										  */
/*　機能概要　：小数点を削除し、前ZEROを編集する    						  */
/*　入　　力　：															  */
/*　　第２引数：char *pSrc			コピー元文字列							  */
/*　　第３引数：int iSize			コピー桁数								  */
/*　出　　力　：															  */
/*　　第１引数：char *pDest			コピー後文字列							  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int GD205CopyReplace(char *pDest, char *pSrc, int iSize )
{
	int	iTargetPos;
	int	iLoop;
	int	iCopySize;

	// ポインタのチェック
	if ( pDest == NULL || pSrc == NULL ) {
		return( RTN_NG );
	}

	iCopySize=strlen( pSrc );
	iTargetPos=iSize;
	for( iTargetPos=iSize; iTargetPos >= 0 ; iTargetPos-- ){
			// 出力サイズに満たない場合0で埋める
		if( iCopySize < 0 ){
			pDest[iTargetPos]='0';	
		} else
			// 小数点を削除する
		if( pSrc[iCopySize] == '.' ){
			// ログ出力
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"小数点削除" );
			iTargetPos++;
		} else 
			// 空白は0に置換する
		if( pSrc[iCopySize] == ' ' ){
			pDest[iTargetPos]='0';	
		} else {
			pDest[iTargetPos]=pSrc[iCopySize];
		}
		iCopySize--;
	}

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD205CopyReplace", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"IN[%s] OUT[%s]\n", pSrc ,pDest );

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
/*　　第３引数：GD205Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int initFunction( int argc, char *argv[], GD205Env *pEnv )
{
	char	cPrmBuf[256];
	char	*lc_login;

	// 初期化
	// エラーステータス変更
	gintErrorCode = 0;
	// プログラム環境変数初期化
	memset( pEnv, '\0', sizeof( GD205Env ) );

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

	// 開始ログ出力
	sFncPutLog( TRCKIND_TRACE, __FILE__, "", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"プログラム起動" );

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
		gintErrorCode = GD205_STSCODE_ERR_PRM_FILE;
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZZbmlPrmOpen", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"パラメータファイルのオープンに失敗しました[%s]", 
					pEnv->pcFileNamePRM );
		return( RTN_NG );
	}

	// データベース接続名
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_DBNAME,
						 pEnv->cDBName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ログインユーザ
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_DBUSER,
						pEnv->cDBUser ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ログインパスワード
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_DBPAWD,
						pEnv->cDBPawd ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 報告データファイル出力ディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_DIR_DATAFILE,
						pEnv->cDirDataFile ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 転送データファイル出力ディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_DIR_TODAY,
						pEnv->cDirToday ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 転送データファイル過去ディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_DIR_OLDDAY,
						pEnv->cDirOldday ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 転送データファイル送信ディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_DIR_SENDFILE,
						pEnv->cDirSendFile ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 転送データファイルREQUESTディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_DIR_SENDREQ,
						pEnv->cDirSendREQ ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 転送データファイルOKディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_DIR_SENDOK,
						pEnv->cDirSendOK ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 転送データファイルERRディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_DIR_SENDERR,
						pEnv->cDirSendERR ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
/* 3.01 DELL STA 
DEL	// データフローＩＤ
DEL	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_DATAFLOWID,
DEL						pEnv->cDataFlowID ) != 0 ) {
DEL		// 異常終了	LOG
DEL		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
DEL		return( RTN_NG );
DEL	}
DEL	// 送信元ＩＤ
DEL	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_SENDID_MOTO,
DEL						pEnv->cSendIDMoto ) != 0 ) {
DEL		// 異常終了	LOG
DEL		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
DEL		return( RTN_NG );
DEL	}
DEL	// 送信先ＩＤ
DEL	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_SENDID_SAKI,
DEL						pEnv->cSendIDSaki ) != 0 ) {
DEL		// 異常終了	LOG
DEL		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
DEL		return( RTN_NG );
DEL	}
*/
	// デバッグログファイル
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_FILE_DBG,
						pEnv->cDebugLogName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// トレースログファイル
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_FILE_TR,
						pEnv->cTraceLogName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// アクセスログファイル
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_FILE_ACS,
						pEnv->cAccessLogName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// エラーログファイル
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_FILE_ERR,
						pEnv->cErrorLogName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 共有メモリキー取得
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_SHM_KEY,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->shm_Key = atoi( cPrmBuf );
	// スリープ時間（秒）取得
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_SLEEP_SEC,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iSleepSec= atoi( cPrmBuf );
	// 更新者ID
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_UP_ID,
						pEnv->cUpdateId ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 更新者名
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_UP_NM,
						pEnv->cUpdateName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 実行モード
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_PROC_MD,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->proc_mode= atoi( cPrmBuf );

	// 1.13 ADD 結果情報 一括COMMIT件数
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_COMMIT_SU,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iCommitSu=atoi( cPrmBuf );

	// 3.01 ADD 
	// 緊急用ファイル名先頭文字列
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_PREFIXNM,
						pEnv->cPrefixNm ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}

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
/*　関 数 名　：GD205UpdateHkkknriSts()										  */
/*　機能概要　：報告管理情報エラー更新										  */
/*　入　　力　：															  */
/*　　第１引数：Hkkknri *pHkkknri	報告管理情報環境構造体					  */
/*　　第２引数：char *pHkkjkflg		報告状況フラグ							  */
/*　　第３引数：char *pHkkerrcode	報告エラーコード						  */
/*　出　　力　：															  */
/*　復帰情報　：なし														  */
/******************************************************************************/
void GD205UpdateHkkknriSts( Hkkknri *pHkkknri, char *pHkkjkflg, char *pHkkerrcode )
{
	int			iRet;

	// 報告管理情報を更新
	ZbmlInfocpy( pHkkknri->hkkjkflg, pHkkjkflg, sizeof( pHkkknri->hkkjkflg ) );
	ZbmlInfocpy( pHkkknri->hkkerrcode, pHkkerrcode, sizeof( pHkkknri->hkkerrcode ) );

	// 報告管理情報を更新
	iRet = ZdbHkkknriGD205UpdateSts( pHkkknri );
	if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
		// ロールバック
		ZdbRollback();
		// 異常終了	LOG
		// 1.06 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205UpdateHkkknriSts", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"ZdbHkkknriGD205UpdateSts error [%d]", iRet );
	} else {
		// コミット
		ZdbCommit();
	}
}

/******************************************************************************/
/*　関 数 名　：mainFunction()												  */
/*　機能概要　：メイン処理関数												  */
/*　入　　力　：															  */
/*　　第１引数：GD205Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int mainFunction( GD205Env *pEnv )
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

	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	if( iRet = ZdbConnect( pEnv->cDBName,
						   pEnv->cDBUser,
						   pEnv->cDBPawd ) ) {
		// 1.06 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"ZdbConnect error [%d]", iRet );
		return( RTN_NG );
	}

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
		iRet = ZdbHkkknriGD205SelectAll( &pHkkknriArrayOut, &iHkkknriNumOut );
		if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
			//異常終了
			//ログ出力
			// 1.06 異常終了	LOG
			sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction", __LINE__,
					EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
					"ZdbHkkknriGD205SelectAll error [%d]", iRet );
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
					// 1.06 異常終了	LOG
					sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
							"ZdbSysknrmstSelect error [%d]", iRet );
					return( RTN_NG );
				}

				// 作成開始日時を取得
				time( (long *)&ulSt );

				// 作成件数、保留件数をクリア
				iHkkssknsu = 0;
				iHkkhrysu = 0;
				memset( cDataFile, 0, sizeof( cDataFile ) );

				// 結果情報検索（送信対象のみ）
				// 報告区分を結果状況コードの値にあわせる
				switch ( pHkkknriArrayOut[iHkkknriLoop].hkkkbn ) {
				case GD205_DB_HKKKBN_LAST:	// 最終
					pHkkknriArrayOut[iHkkknriLoop].hkkkbn = GD205_DB_KKAJKCD_LAST;
					break;
				case GD205_DB_HKKKBN_CYUU:	// 中間
					pHkkknriArrayOut[iHkkknriLoop].hkkkbn = GD205_DB_KKAJKCD_CYUU;
					break;
				}

				// 再転送の場合は、再転送処理を呼び出す
					// 3.01 緊急の場合は項目コードに報告条件が設定されている
				//if( pHkkknriArrayOut[iHkkknriLoop].hkkjkn == GD205_DB_HKKJKN_RESEND ) [
				if ( pHkkknriArrayOut[iHkkknriLoop].kmkcd[0] == GD205_DB_HKKJKN_RESEND ) {
					if ( GD205ResendFile( pEnv,
										  &stSysknrmst,
						 				  &pHkkknriArrayOut[iHkkknriLoop] ) == RTN_OK ) {
						// 報告ファイル名
						// GD205ResendFile内で設定
						// 報告状況フラグ
						ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg,
									 GD205_DB_HKKJKFLG_CHUU,
									 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg ) );
						// 情報更新日時は関数内で設定

						// 報告管理情報を更新
						iRet = ZdbHkkknriGD205UpdateNormal( &pHkkknriArrayOut[iHkkknriLoop] );
						if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
							// ロールバック
							ZdbRollback();
							// 異常終了	LOG
							// 1.06 異常終了	LOG
							sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction",
									 __LINE__,
									EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
									"ZdbHkkknriGD205UpdateNormal error [%d]", 
									iRet );

							return( RTN_NG );
						}

						// コミット
						ZdbCommit();
					} else {
						// 異常終了	LOG
						// 1.06 異常終了	LOG
						sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction",
								 __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"GD205ResendFile error " );

						// 報告管理情報を更新
						GD205UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
												GD205_DB_HKKJKFLG_ERRFILE,
												GD205_DB_HKKERRCODE_RESEND );
					}
					continue;
				}

				// 報告条件により、検索方法を切替える
				// switch ( pHkkknriArrayOut[iHkkknriLoop].hkkjkn ) {
					// 3.01 緊急分の検索条件は項目コードに設定
				switch ( pHkkknriArrayOut[iHkkknriLoop].kmkcd[0] ) {
				case GD205_DB_HKKJKN_CTRLNO:	// コントロールNo
					iRet = ZdbKekkaGD205SelectByCtrlNo( &pHkkknriArrayOut[iHkkknriLoop],
														&pKekkaArrayOut, &iKekkaNumOut );
					break;
				case GD205_DB_HKKJKN_PLTNO:		// プロットNo
					iRet = ZdbKekkaGD205SelectByPltNo( &pHkkknriArrayOut[iHkkknriLoop],
													   &pKekkaArrayOut, &iKekkaNumOut );
					break;
				case GD205_DB_HKKJKN_KNSSEQ:	// 検査SEQ
					iRet = ZdbKekkaGD205SelectByKnsSeq( &pHkkknriArrayOut[iHkkknriLoop],
														&pKekkaArrayOut, &iKekkaNumOut );
					break;
				case GD205_DB_HKKJKN_IRINO:		// 依頼書No
					iRet = ZdbKekkaGD205SelectByIriNo( &pHkkknriArrayOut[iHkkknriLoop],
													   &pKekkaArrayOut, &iKekkaNumOut );
					break;
				case GD205_DB_HKKJKN_KNTNO:		// 検体No
					iRet = ZdbKekkaGD205SelectByKntNo( &pHkkknriArrayOut[iHkkknriLoop],
													   &pKekkaArrayOut, &iKekkaNumOut );
					break;
				default:
					// 1.06 異常終了	LOG
					sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"kkknri.hkkjkn の範囲エラー (HKKJKN='%c')", 
							pHkkknriArrayOut[iHkkknriLoop].hkkjkn );

					// 報告管理情報を更新
					GD205UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
										   GD205_DB_HKKJKFLG_ERRFILE,
										   GD205_DB_HKKERRCODE_HKKJKN );
					continue;
				}
				if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
					// 異常終了	LOG
					// 1.06 異常終了	LOG
					sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
							"ZdbKekkaGD205SelectByXXXX error (%d)", iRet);

					// 報告管理情報を更新
					GD205UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
										   GD205_DB_HKKJKFLG_ERRFILE,
										   GD205_DB_HKKERRCODE_DBACS );
					continue;
				}
				if ( iRet == HRC_SQL_NOT_FOUND ) {
					// 異常終了	LOG
					// 1.06 異常終了	LOG
					sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
							"ZdbKekkaGD205SelectByXXXX no data  error" );

					// 報告管理情報を更新
					GD205UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
										   GD205_DB_HKKJKFLG_ERRFILE,
										   GD205_DB_HKKERRCODE_NODATA );
					continue;
				}
				if ( iRet == HRC_SQL_NORMAL ) {
					// 報告データファイルの作成
				if ( GD205CreateFile( pEnv,
									&stSysknrmst,
									pKekkaArrayOut,
									iKekkaNumOut,
									&iHkkssknsu,
									&iHkkhrysu,
									cDataFile,
									&pHkkknriArrayOut[iHkkknriLoop],  // 3.01 ADD
								   	&li_stopFlg //2006.12.08 Kim Jinsuk DBエラー時終了させる 
									) == RTN_NG ) {

                          //2006.12.08　Kim Jinsuk DBエラー時異常終了させる
                          if(li_stopFlg==1)
                          {
                                printf("#############################3");
                                sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbKekkaGD205Update"
								, __LINE__,
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
							GD205UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
												   GD205_DB_HKKJKFLG_ERRFILE,
												   GD205_DB_HKKERRCODE_NODATA );
							continue;
						}

						// 異常終了	LOG
					sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"GD205CreateFile error" );


						// 報告管理情報を更新
						GD205UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
											   GD205_DB_HKKJKFLG_ERRFILE,
											   GD205_DB_HKKERRCODE_CREATE );
						continue;
					}

				}

				// 結果情報を解放
				if ( pKekkaArrayOut != NULL ) {
					ZbmlFree( pKekkaArrayOut );
				}

				// 作成完了日時を取得
				time( (long *)&ulEd );

				// 報告ファイル名
				// GD205CreateHULFTFile内で設定 -> 3.01 GD205CreateFile 内で設定
				// 作成開始日時
				GD205ConvTimestamp( ulSt, cTimestamp );
				ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkstdh,
							 cTimestamp,
							 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkstdh ) );
				// 作成完了日時
				GD205ConvTimestamp( ulEd, cTimestamp );
				ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkeddh,
							 cTimestamp,
							 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkeddh ) );
				// 作成件数
				pHkkknriArrayOut[iHkkknriLoop].hkkssknsu = iHkkssknsu;
				// 報告保留件数
				pHkkknriArrayOut[iHkkknriLoop].hkkhrysu = iHkkhrysu;
				// 送信ファイルＩＤ
				// GD205CreateHULFTFile内で設定
				// 報告状況フラグ
				ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg,
							 GD205_DB_HKKJKFLG_CHUU,
							 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg ) );
				// 情報更新日時は関数内で設定

				// 報告管理情報を更新
				iRet = ZdbHkkknriGD205UpdateNormal( &pHkkknriArrayOut[iHkkknriLoop] );
				if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
					// ロールバック
					ZdbRollback();
					// 異常終了	LOG
					// 1.06 異常終了	LOG
					sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
							"ZdbHkkknriGD205UpdateNormal error (%d)", iRet);

					return( RTN_NG );
				}

				// コミット
				ZdbCommit();
			}

			// 報告管理情報を解放
			ZbmlFree( pHkkknriArrayOut );
		}

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
/*　　第１引数：GD205Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：なし														  */
/******************************************************************************/
void endFunction( GD205Env *pEnv )
{
	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "endFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");
	// 1.09 ADD
	/***	
     ***    データベースクローズ
     ***/
    ZdbDisConnect() ;

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
/*　関 数 名　：GD205MakeData()												  */
/*　機能概要　：報告データ作成												  */
/*　入　　力　：															  */
/*　　第１引数：Kekka *pKekka		検査結果データ							  */
/*　　第２引数：char *pLBCD			ラボコード								  */
/*　出　　力　：															  */
/*　　第３引数：GD205Rec *pGD205Rec	報告データ								  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int GD205MakeData(Kekka *pKekka, char *pLBCD, GD205Rec *pGD205Rec)
{
	char	cTempBuff[128];
	char	cKkassflg[1+1];		// 1.11 ADD 結果修正ﾌﾗｸﾞMAX取得
	char	cSbtkbn[1+1];		// 3.01 ADD 性別区分
	int		edt_ret;			// 3.01 


	// 検査結果データまたは報告データへのポインタがNULLの場合異常終了
	if ( pKekka == NULL || pGD205Rec == NULL ) {
		return( RTN_NG );
	}

	// 1.06 ADD 施設別換算対応
	GD205_sstknz( pKekka );


	// 報告データをスペースでクリア
	memset( pGD205Rec, GD205_DATA_SPACE, sizeof(GD205Rec) );

	// 検査結果データから報告データを作成
	// ＢＭＬ受付年月日
	// [YYYYMMDD]に変換して設定
	ZbmlChgAPDate( pGD205Rec->cUTKYMD, pKekka->utkymd );

	/* 依頼書No．*/
	/* 内部形式をPNC形式に変換 */
	/* (変換前)[1][2][3][4][5][6][7][8][9][10][11] */
	/* (変換後)[4][5][6] 0  0 [7][8][9][9][10][11] */
	if ( GD205ConvNumber( pGD205Rec->cKNTNO, pKekka->irino ) == RTN_NG ) {
		return( RTN_NG );
	}

	/* 親項目コード */
	/* 増桁により、項目コードが7桁化されたのでそのままコピーする */
	if ( GD205CopyFromLeft( pGD205Rec->cOYAKMKCD,
								pKekka->oyakmkcd,
								sizeof( pGD205Rec->cOYAKMKCD ),
								FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}

	/* 項目コード */
	/* 増桁により、項目コードが7桁化されたのでそのままコピーする */
	if ( GD205CopyFromLeft( pGD205Rec->cKMKCD,
								pKekka->kmkcd,
								sizeof( pGD205Rec->cKMKCD ),
								FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}

	/* WSコード(サンプリングコード) */
		// 3.01 ADD 緊急対応項目マスタから編集する
/*** AS400側 増桁に伴い、緊急対応項目マスタからASWSCDを取得するのを止め -> ***/
/*** サテライト側のWSCD(=SMPCD)をそのまま設定して送る                   -> ***/
/*	if( GD205_GetWscd( pGD205Rec->cWSCD, pKekka->kmkcd, pKekka->knskisymd ) != RTN_OK ){*/
/*		if ( GD205CopyFromLeft( pGD205Rec->cWSCD,*/
/*								 pKekka->smpcd,*/
/*								 sizeof( pGD205Rec->cWSCD ),*/
/*								 FALSE ) == RTN_NG ) {*/
/*			return( RTN_NG );*/
/*		}*/
/*	}*/
	if ( GD205CopyFromLeft( pGD205Rec->cWSCD, pKekka->smpcd, 
						   sizeof( pGD205Rec->cWSCD ), FALSE ) == RTN_NG ) {
		return( RTN_NG );									/* KEKKAのSMPCDをそのまま報告のWSCDに設定 */
	}
/*** AS400側 増桁に伴う修正 <-                                              ***/

	
	
	// ＷＳＳＥＱ（検査ＳＥＱ）
    // 数値を文字列に変換後、右から4桁を設定。（ゼロサプレスなし）
    sprintf( cTempBuff, "%06d", pKekka->knsseq );
    if ( GD205CopyFromRight( pGD205Rec->cWSSEQ,
                             cTempBuff,
                             sizeof( pGD205Rec->cWSSEQ ),
                             FALSE ) == RTN_NG ) {
        return( RTN_NG );
    }

    // 検査結果
/* 3.01 2007.06.12 PTN対応　STA ========================================================
DEL    // 検査結果１or検査結果２（検査結果１優先）
DEL		// GD105 knskka1 RIGHT
DEL	memset( cTempBuff, '\0',	sizeof( cTempBuff ));
DEL    if ( pKekka->knskka1[0] != '\0' 
DEL	  && strspn( pKekka->knskka1, " " ) != ( sizeof( pKekka->knskka1 ) - 1 ) ){
DEL        // 検査結果１：右から6桁を設定（ゼロサプレスあり、小数点削除）
DEL        if ( GD205CopyFromRight( cTempBuff,
DEL                                pKekka->knskka1,
DEL                                sizeof( pGD205Rec->cKNSKKA ),
DEL                                FALSE ) == RTN_NG ) {
DEL            return( RTN_NG );
DEL        }
DEL			// 小数点削除、前ゼロ付加
DEL        if ( GD205CopyReplace( pGD205Rec->cKNSKKA,
DEL                                cTempBuff,
DEL                                sizeof( pGD205Rec->cKNSKKA )) == RTN_NG ) {
DEL            return( RTN_NG );
DEL        }
DEL    } else {
DEL        // 検査結果２
DEL        // 検査結果区分='0'→'*'+左2桁目から6桁目まで
DEL        // 以外→左から6桁を設定（2バイト文字に注意する）
DEL        // ?? if ( ED203CopyFromRight( pED203Rec->cKNSKKA,
DEL        if ( GD205CopyFromLeft( pGD205Rec->cKNSKKA,
DEL                                pKekka->knskka2,
DEL                                sizeof( pGD205Rec->cKNSKKA ),
DEL                                TRUE ) == RTN_NG ) {
DEL            return( RTN_NG );
DEL        }
DEL        if ( pKekka->knskka2kbn[0] == GD205_DATA_CHAR0 ) {
DEL            // 検査結果区分='0'→'*'+左2桁目から6桁目まで
DEL            pGD205Rec->cKNSKKA[0] = GD205_DATA_ASTERISK;
DEL        }
DEL    }
=================================================================================== */
    // 検査結果
	// 3.01 AS400用にオンコーディング
	edt_ret=RTN_OK;
	memset( cTempBuff, '\0',	sizeof( cTempBuff ));

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD205MakeData", __LINE__,
		"EDIT IN### irino[%s]kmkcd[%s]KNSKKA[%6.6s]\nkka1[%s]kka2[%s]2kbn[%s]kkahskcd[%s]\n"
		,pKekka->irino,pKekka->kmkcd, pGD205Rec->cKNSKKA
		, pKekka->knskka1,pKekka->knskka2,pKekka->knskka2kbn,pKekka->kkahskcd );

	// 結果１が空白以外
    if ( strspn( pKekka->knskka1, " " ) != ( sizeof( pKekka->knskka1 ) - 1 ) ){
		// 結果補足が空白
    	if ( pKekka->kkahskcd[0] == ' '  ){
				// 検査結果１の小数点、空白以外のlength <= 6
			if(((sizeof(pKekka->knskka1)-1) - strspn(pKekka->knskka1," ")  ) <= 6 ){
					// 小数点削除、前ゼロ付加
				if ( GD205CopyReplace( cTempBuff,
										pKekka->knskka1,
										sizeof(pKekka->knskka1)) == RTN_NG ) {
					edt_ret=RTN_NG;
				}
				// 検査結果１：右から6桁を設定
				if ( GD205CopyFromRight( pGD205Rec->cKNSKKA,
										cTempBuff,
										sizeof( pGD205Rec->cKNSKKA ),
										FALSE ) == RTN_NG ) {
					edt_ret=RTN_NG;
				}
			} else {
				// 結果編集不可
				edt_ret=RTN_NG;
			}
		}
		// 結果補足が空白以外
		else {
				// 検査結果１の空白以外のlength <= 4
			if(((sizeof(pKekka->knskka1)-1) - strspn(pKekka->knskka1," "))<= 4 ){
					// LT編集 + 前スペースを取り除いた結果１を編集
				if( ( memcmp( pKekka->kkahskcd, "001" ,3 ) == 0 )
				 || ( memcmp( pKekka->kkahskcd, "002" ,3 ) == 0 )){
					sprintf( cTempBuff, "LT%s    " , strrchr( pKekka->knskka1, ' ')+1 );
				} else
					// GT編集 + 前スペースを取り除いた結果１を編集
				if( ( memcmp( pKekka->kkahskcd, "003" ,3 ) == 0 )
				 || ( memcmp( pKekka->kkahskcd, "004" ,3 ) == 0 )){
					sprintf( cTempBuff, "GT%s    " , strrchr( pKekka->knskka1, ' ')+1 );
				} else {
					// 結果編集不可
					edt_ret=RTN_NG;
				}
				// 後ろスペース考慮し設定
				if( edt_ret != RTN_NG ){
					memcpy( pGD205Rec->cKNSKKA, cTempBuff, sizeof( pGD205Rec->cKNSKKA ));
				}
			} else {
				// 結果編集不可
				edt_ret=RTN_NG;
			}
		}
	} 
	// 結果１が空白
	else {
			// 結果２区分='0'
        if ( pKekka->knskka2kbn[0] == GD205_DATA_CHAR0 ) {
				// 結果２の先頭１byte目='0'
        	if ( pKekka->knskka2[0] == GD205_DATA_CHAR0 ) {
            		// 先頭１byte目を'*'に置換した結果２を編集
				if ( GD205CopyFromLeft( pGD205Rec->cKNSKKA,
										pKekka->knskka2,
										sizeof( pGD205Rec->cKNSKKA ),
										TRUE ) == RTN_NG ) {
					// 結果編集不可
					edt_ret=RTN_NG;
				}
				pGD205Rec->cKNSKKA[0] = GD205_DATA_ASTERISK;
			} else {
				// 結果２の先頭１byte目<>'0'
				if( memcmp( pKekka->knskka2, "1005" ,4 ) == 0 ) {
					memcpy( pGD205Rec->cKNSKKA, "-     ", 6 );
				} else if( memcmp( pKekka->knskka2, "1006" ,4 ) == 0 ) {
					memcpy( pGD205Rec->cKNSKKA, "+-    ", 6 );
				} else if( memcmp( pKekka->knskka2, "1008" ,4 ) == 0 ) {
					memcpy( pGD205Rec->cKNSKKA, "1+    ", 6 );
				} else if( memcmp( pKekka->knskka2, "1009" ,4 ) == 0 ) {
					memcpy( pGD205Rec->cKNSKKA, "2+    ", 6 );
				} else {
					// 結果編集不可
					edt_ret=RTN_NG;
				}
			}
        } 
		// 結果２区分<>'0'
		else {
			// 結果編集不可
			edt_ret=RTN_NG;
		}
	}
	// 結果編集不可 -> *340
	if( edt_ret==RTN_NG ){
		memcpy( pGD205Rec->cKNSKKA, "*340  ", 6 );
	}

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD205MakeData", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		"-->cKNSKKA[%6.6s]" , pGD205Rec->cKNSKKA );

	// 結果コメント
    // 右から3桁を設定
    // 3.01 左2byte目から3桁を設定
    //if ( GD205CopyFromRight( pGD205Rec->cKKACMT,
    if ( GD205CopyFromLeft( pGD205Rec->cKKACMT,
                             //pKekka->kkacmt1,
                             &pKekka->kkacmt1[1],
                             sizeof( pGD205Rec->cKKACMT ),
                             FALSE ) == RTN_NG ) {
        return( RTN_NG );
    }

    // 異常値マーク
    // 異常値区分（男、女、不明）が'4','5','6'以外であれば'*'
		// 3.01 ADD 判定に用いる値は性別により変える
	if ( GD205GetSbtkbn( pKekka, cSbtkbn ) != RTN_OK ){
		cSbtkbn[0] = '9';
	}
/* 3.01 DELL
DEL if ( ( pKekka->ijkbnm != '4' && pKekka->ijkbnm != '5' && pKekka->ijkbnm != '6' ) ||
DEL      ( pKekka->ijkbnf != '4' && pKekka->ijkbnf != '5' && pKekka->ijkbnf != '6' ) ||
DEL      ( pKekka->ijkbnn != '4' && pKekka->ijkbnn != '5' && pKekka->ijkbnn != '6' ) ) [
*/
    if((cSbtkbn[0] =='0' && pKekka->ijkbnm != '4' && pKekka->ijkbnm != '5' && pKekka->ijkbnm != '6' ) ||
       ( cSbtkbn[0] =='1' && pKekka->ijkbnf != '4' && pKekka->ijkbnf != '5' && pKekka->ijkbnf != '6' ) ||
       ( cSbtkbn[0] =='9' && pKekka->ijkbnn != '4' && pKekka->ijkbnn != '5' && pKekka->ijkbnn != '6' ) ) {
        pGD205Rec->cIJKBN = GD205_DATA_ASTERISK;
	}

    // FILLER2
    // 空白を設定なので何もしない
    // LF
    pGD205Rec->cLF = GD205_FILE_LINEFEED;


	// 後処理
// 1.11 ADD 結果修正フラグは同一KEY内のMAX(結果修正FLG）を編集
	 if ( pKekka->kkassflg != '\0' ){
		memset( cKkassflg,	'\0',	sizeof( cKkassflg ));
		if ( GD205GetKkassflgMax( pKekka, cKkassflg ) == RTN_OK ) {
			// 更新用に取得したMAXを構造体に編集する
			pKekka->kkassflg	= cKkassflg[0];
		}
	}
// 1.11 END ====================================================

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：GD205DataFileFilter()										  */
/*　機能概要　：ディレクトリ検索用のファイルフィルタ(コールバック)			  */
/*　入　　力　：															  */
/*　　第１引数：struct dirent *pDirEnt	ディレクトリエントリ				  */
/*　出　　力　：検査結果ファイル											  */
/*　復帰情報　：int															  */
/*　　　　　　		0	: 対象外ファイル									  */
/*　　　　　　		1	: 対象ファイル										  */
/******************************************************************************/
int GD205DataFileFilter(struct dirent *pDirEnt)
{
	BmlDate		today;
	char		cToday[GD205_LEN_DATESHORT + 1];

	// 文字列長チェック
	if ( strlen ( pDirEnt->d_name )  < GD205_LEN_FILEID ) {
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
/*　関 数 名　：GD205WriteFile()											  */
/*　機能概要　：報告データファイル書込み									  */
/*　入　　力　：															  */
/*　　第１引数：FILE *fp			ファイルポインタ						  */
/*　　第２引数：GD205Rec *pGD205Rec	報告データ								  */
/*　　第３引数：int iRecCnt			レコード数								  */
/*　出　　力　：検査結果ファイル											  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int GD205WriteFile(FILE *fp, GD205Rec *pGD205Rec, int iRecCnt)
{
	int				iLoop;
	int				iFileCnt;
	GD205Rec		stGD205RecTemp;
	char			cTemp[GD205_FILE_FILLER_SIZE];

	// ファイル出力
	// レコード書込み
	iFileCnt = fwrite( pGD205Rec, sizeof( GD205Rec ) * iRecCnt, 1, fp);
	if ( iFileCnt != 1 ) {
		// 異常終了	LOG
		// 1.06 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205WriteFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"write status:[%d] ", iFileCnt );

		gintErrorCode = GD205_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}
	for ( iLoop = iRecCnt; iLoop < GD205_REC_LOOP_MAX; iLoop++ ) {
		memset( &stGD205RecTemp, GD205_DATA_SPACE, sizeof( GD205Rec ) );
		iFileCnt = fwrite( &stGD205RecTemp, sizeof( GD205Rec ), 1, fp);
		if ( iFileCnt != 1 ) {
			// 異常終了	LOG
			// 1.06 異常終了	LOG
			sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205WriteFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"write status:[%d]", iFileCnt );

			gintErrorCode = GD205_STSCODE_ERR_FR_FILE ;
			return( RTN_NG ) ;
		}
	}

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：GD205ResendFile()											  */
/*　機能概要　：再転送用ファイル移動										  */
/*　入　　力　：															  */
/*　　第１引数：GD205Env *pEnv		プログラム環境構造体					  */
/*　　第２引数：Sysknrmst *pSysknrmst システム管理マスタ情報				  */
/*　　第３引数：Hkkknri *pHkkknri	報告管理情報情報						  */
/*　出　　力　：															  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int GD205ResendFile(GD205Env *pEnv, Sysknrmst *pSysknrmst, Hkkknri *pHkkknri)
{
	int				iRet;
	struct dirent	**pDirEnt;
	int				iFileCnt;
	int	 			iSeqNo;
	char			cSeqBuff[10];
	BmlDate			today;
	char			cKjnsriymd[GD205_LEN_DATESHORT + 1];
	char			cFileDate[GD205_LEN_DATESHORT + 1];
	char			cFileSrc[PATH_MAX + 1];
	char			cSendFile[PATH_MAX + 1];
	char			cSendFileTemp[PATH_MAX + 1];
	FILE *			fpSrc;
	FILE *			fpDest;
	int				iLoop;
	char			cTemp[GD205_SIZE_BUFF + 1];
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

/* 3.01 DELL STA PNC送信ファイルをそのまま使用 ============================
DEL	// 元ファイルの処理日付を取得
DEL	memset( cFileDate, 0, sizeof( cFileDate ) );
DEL	memcpy( cFileDate, pHkkknri->ssnmtfilid, GD205_LEN_DATESHORT );
DEL
DEL	// 1.07 INTEC ADD STA
DEL	// ファイル名の後ろ空白をtrim
DEL	sprintf( cWfilnm, "%.*s",
DEL			strcspn( pHkkknri->stsflnm, " " ) ,
DEL			pHkkknri->stsflnm );
DEL	strcpy( pHkkknri->stsflnm, cWfilnm );
DEL	// 1.07 INTEC ADD END
DEL
DEL	// 送信用ファイル名生成
DEL   memset(sNewFlName, 0, sizeof(sNewFlName));
DEL   sprintf(sNewFlName, "%-3.3s_%04d_%-18.18s%04d", pHkkknri->stsflnm, pHkkknri->hkksjno,
DEL		&pHkkknri->stsflnm[9], pSysknrmst->ssntubn);
DEL
DEL	memset(cSendFile, 0, sizeof(cSendFile));
DEL	memset(cSendFileTemp, 0, sizeof(cSendFileTemp));
DEL	sprintf(cSendFile, "%s/%s/%s/%s%s",
DEL			pEnv->cDirToday,
DEL		 	pEnv->cDirSendFile,
DEL			pEnv->cDirSendREQ,
DEL			sNewFlName, GD205_FILEEXT_DATA);	
DEL	sprintf(cSendFileTemp, "%s/%s/%s/%s%s",
DEL			pEnv->cDirToday,
DEL		 	pEnv->cDirSendFile,
DEL			pEnv->cDirSendREQ,
DEL			sNewFlName, GD205_FILEEXT_TEMP);	
DEL
DEL	// 処理日元ファイルのOKディレクトリのフルパスを生成
DEL	//if ( memcmp( cKjnsriymd, pHkkknri->stsflnm, GD205_LEN_DATESHORT ) == 0 ) [
DEL	if ( memcmp( cKjnsriymd, pHkkknri->ssnmtfilid, GD205_LEN_DATESHORT ) == 0 ) {
DEL		sprintf( cFileSrc, "%s/%s/%s/%s",
DEL			 	pEnv->cDirToday,
DEL			 	pEnv->cDirSendFile,
DEL			 	pEnv->cDirSendOK,
DEL				pHkkknri->stsflnm );
DEL	} else {
DEL		sprintf( cFileSrc, "%s/%s/%s/%s/%s",
DEL			 	pEnv->cDirOldday,
DEL			 	cFileDate,
DEL			 	pEnv->cDirSendFile,
DEL			 	pEnv->cDirSendOK,
DEL				pHkkknri->stsflnm );
DEL	}
========================================================================= */

// 3.01 ADD STA
	sprintf( cWfilnm, "%.*s",
			strcspn( pHkkknri->stsflnm, " " ) ,
			pHkkknri->stsflnm );

	// 元ファイル
    sprintf( cFileSrc, "%s/%s/%s/%s",
			 pEnv->cDirToday,
			 pEnv->cDirSendFile,
			 pEnv->cDirSendOK,
			 cWfilnm );

	// 送信用ファイル名生成
		// ロットNoの次のbyteを１カウントアップする
		// 20070622 再転送時の送信番号をファイル名に反映させる
	memset(sNewFlName, 0, sizeof(sNewFlName));
	//sprintf( sNewFlName, "%-30.30s%1.1d" , cWfilnm, ( cWfilnm[30] - '0' ) + 1 );
	sprintf( sNewFlName, "%-4.4s%04d%-22.22s%1.1d" 
			, cWfilnm
			, pHkkknri->hkksjno
			, &cWfilnm[8]
			, ( cWfilnm[30] - '0' ) + 1 );

	memset(cSendFile, 0, sizeof(cSendFile));
	memset(cSendFileTemp, 0, sizeof(cSendFileTemp));
	sprintf(cSendFile, "%s/%s/%s/%s%s",
			pEnv->cDirToday,
		 	pEnv->cDirSendFile,
			pEnv->cDirSendREQ,
			sNewFlName, GD205_FILEEXT_DATA );	
	sprintf(cSendFileTemp, "%s/%s/%s/%31.31s%s",
			pEnv->cDirToday,
		 	pEnv->cDirSendFile,
			pEnv->cDirSendREQ,
			sNewFlName, GD205_FILEEXT_TEMP );	

// 3.01 ADD  END

	// 元ファイルオープン
	fpSrc = fopen ( cFileSrc, "r" );
	if ( fpSrc == NULL ) {
/* 3.01 DELL STA ======================================================
DEL		// ファイルがオープンできない場合はERRディレクトリで再挑戦
DEL		if ( strncmp( cKjnsriymd, pHkkknri->ssnmtfilid, GD205_LEN_DATESHORT ) == 0 ) {
DEL			sprintf( cFileSrc, "%s/%s/%s/%s",
DEL				 	pEnv->cDirToday,
DEL				 	pEnv->cDirSendFile,
DEL				 	pEnv->cDirSendERR,
DEL					pHkkknri->stsflnm );
DEL		} else {
DEL			sprintf( cFileSrc, "%s/%s/%s/%s/%s",
DEL				 	pEnv->cDirOldday,
DEL			 		cFileDate,
DEL				 	pEnv->cDirSendFile,
DEL				 	pEnv->cDirSendERR,
DEL					pHkkknri->stsflnm );
DEL		}
DEL		// 元ファイルオープン
DEL		fpSrc = fopen ( cFileSrc, "r" );
======================================================================= */

		if ( fpSrc == NULL ) {
			// 異常終了	LOG
			gintErrorCode = GD205_STSCODE_ERR_FR_FILE ;
			return( RTN_NG ) ;
		}
	}

	// 送信用ファイルオープン
	fpDest = fopen ( cSendFileTemp, "w" );
	if ( fpDest == NULL ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	// 読み込み
	iHead = 0;
	while ( iRet = fgets( cTemp, sizeof ( cTemp ), fpSrc ) != NULL ) {
		if ( fputs( cTemp, fpDest ) < 0 ) {
			//エラーログ出力
//1.06 DELL printf("fputs error \n");
			// 1.06 異常終了	LOG
			sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205ResendFile", __LINE__,
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
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205ResendFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"ResendFile rename status:[%d] ", iRet);

		gintErrorCode = GD205_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	// 返却用にファイル名と送信ファイルＩＤを設定
	memset( pHkkknri->hkkflnm, 0, sizeof( pHkkknri->hkkflnm ) );
	sprintf( pHkkknri->hkkflnm, "%s%s",
			sNewFlName, GD205_FILEEXT_DATA);	

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：GD205CreateFile()											  */
/*　機能概要　：報告データファイル作成										  */
/*　入　　力　：															  */
/*　　第１引数：GD205Env *pEnv		プログラム環境構造体					  */
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
int GD205CreateFile(GD205Env *pEnv,
					Sysknrmst *pSysknrmst,
					Kekka *pKekkaArray,
					int iKekkaNum,
					int *piHkkssknsu,
					int *piHkkhrysu,
					char *pFileName,
					Hkkknri *pHkkknriArrayOut,	// 3.01 ADD
					int *sqlErrorFlag)			//2006.12.08 Kim Jinsuk DBエラー時異常終了させる
{
	int				iRet;
	struct dirent	**pDirEnt;
	int				iFileCnt;
	int	 			iSeqNo;
	char			cSeqBuff[10];
	BmlDate			today;
	char			cToday[GD205_LEN_DATESHORT + 1];
	char			cFileNameTemp[PATH_MAX + 1];
	char			cFileName[PATH_MAX + 1];
	FILE *			fp;
	int				iLoop;
	GD205Rec		stGD205RecTemp;
	int				iKekkaLoop;
	GD205Rec		stGD205Rec[GD205_REC_LOOP_MAX];
	int				iFileLoopIdx;
	int				iCmmtCnt=0;				// 1.13 ADD

	char			cKjnsriymd[GD205_LEN_DATESHORT + 1];
	char			cSendFileTemp[PATH_MAX + 1];
	char			cSendFile[PATH_MAX + 1];
	FILE *			fpSrc;
	FILE *			fpDest;
	int				iRecCnt;
	char			cTemp[GD205_SIZE_BUFF + 1];
    char            sNewFlName[PATH_MAX + 1];
    char            sKaisibi[10];
    int             i;

    //
	// 引数チェック
	if ( pEnv == NULL || pSysknrmst == NULL || pKekkaArray == NULL ||
		 piHkkssknsu == NULL || piHkkhrysu == NULL || pFileName == NULL ) {
		// 異常終了	LOG
//1.06 DELL printf("GD205CreateFile parameter is NULL\n");
		// 1.06 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205CreateFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"GD205CreateFile parameter is NULL");

		gintErrorCode = GD205_STSCODE_ERR_FR_FILE;
		return( RTN_NG );
	}

// 3.01 ADD STA
	// 処理日付取得
	ZbmlChgAPDate( cKjnsriymd, pSysknrmst->kjnsriymd );
	// 1.06 異常終了	LOG
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD205CreateFile", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"基準処理年月日:[%s]", cKjnsriymd );

	// ファイル名生成
    memset(sNewFlName, 0, sizeof(sNewFlName));
		// 3.01 UPD
    //switch(pHkkknriArrayOut->hkkjkn) {
    switch(pHkkknriArrayOut->kmkcd[0]) {
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
    // 3.01 sprintf( cSendFile, "%s/%s/%s/%s_%04d_%s_%s_%s%04d%s",
    sprintf( cSendFile, "%s/%s/%s/%s_%04d_%s_%s_%s%03d0%s",
			 pEnv->cDirToday,
			 pEnv->cDirSendFile,
			 pEnv->cDirSendREQ,
             // 3.01 pSysknrmst->sateid, 
             pEnv->cPrefixNm, 
			 pHkkknriArrayOut->hkksjno,
             pHkkknriArrayOut->seccd, sNewFlName, cKjnsriymd, 
			 // 3.01 pSysknrmst->ssntubn, 
			 pHkkknriArrayOut->kkirilotno, 
			 GD205_FILEEXT_DATA );
			 //cKjnsriymd,
    // 3.01 sprintf( cSendFileTemp, "%s/%s/%s/%s_%04d_%s_%s_%s%04d%s",
    sprintf( cSendFileTemp, "%s/%s/%s/%s_%04d_%s_%s_%s%03d0%s",
			 pEnv->cDirToday,
			 pEnv->cDirSendFile,
			 pEnv->cDirSendREQ,
             // 3.01 pSysknrmst->sateid, 
             pEnv->cPrefixNm, 
			 pHkkknriArrayOut->hkksjno,
             pHkkknriArrayOut->seccd, sNewFlName, cKjnsriymd, 
			 // 3.01 pSysknrmst->ssntubn,
			 pHkkknriArrayOut->kkirilotno, 
			 GD205_FILEEXT_TEMP );
	// 報告データファイルオープン
	fp = fopen ( cSendFileTemp, "w" );
	if ( fp == NULL ) {
		// 1.06 異常終了    LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205CreateFile", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"file open error[%s]", cSendFileTemp );
		gintErrorCode = GD205_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

// 3.01 ADD END

	// 結果情報を１件ずつ処理
	for ( iKekkaLoop = 0, iFileLoopIdx  = 0;
		  iKekkaLoop < iKekkaNum;
		  iKekkaLoop++ ) {

		// 3.01 ADD STA 緊急依頼ロットNoの指定有りの場合は該当結果以外はSKIP
		if( pHkkknriArrayOut->kkirilotno > 0 ){
			if( pHkkknriArrayOut->kkirilotno != pKekkaArray[iKekkaLoop].kkirilotno ){
				continue;
			}
		}
		// 3.01 ADD END

		// 保留かどうかチェック
		if ( pKekkaArray[iKekkaLoop].knsflg == GD205_DB_KNSFLG_HORYU ) {
			++*piHkkhrysu;
			continue;
		}
		// Add 2007.05.09 waj
		// knskka1,knskka2共にスペースの場合、報告レコードを作成せず保留扱いとする
		if ((strncmp(pKekkaArray[iKekkaLoop].knskka1, "            ", 12) == 0) &&
		    (strncmp(pKekkaArray[iKekkaLoop].knskka2, "                        ", 24) == 0)) {

            sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205CreateFile", __LINE__,
                        EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
                        "knskka1,knskka2共にスペースのため保留とする [%s %s %d]",
						pKekkaArray[iKekkaLoop].sriymd	,pKekkaArray[iKekkaLoop].kmkcd
						,pKekkaArray[iKekkaLoop].knsseq);

			// 検査フラグに保留を設定
			pKekkaArray[iKekkaLoop].knsflg = GD205_DB_KNSFLG_HORYU;

			// 結果情報の検査フラグを保留にするため更新
			iRet = ZdbKekkaGD205Update( &pKekkaArray[iKekkaLoop] );

	        if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
				// DBエラーの場合は、処理を抜ける
				sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205CreateFile", __LINE__,
                            EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
                            "ZdbKekkaGD205Update error(%d)", iRet);

				// ロールバック
				ZdbRollback();

            	if((iRet < 0) && (iRet !=-803) && (iRet != -911))
	            {
	                *sqlErrorFlag = 1;
	                printf("##### DBエラー　発生　#####\n");
	                printf("iRet %d", iRet);
	                sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbKekkaGD205Update", __LINE__,
	                            EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
	                            "DB エラー　発生　error value 0 %d", iRet);

                	return( RTN_NG );
            	}
				// DBエラーの場合は、全て無し
				*piHkkssknsu=0;
            	break;
        	}

			// 保留カウンタアップ
			++*piHkkhrysu;

			continue;
		}

		// 繰返し件数に達したらファイル出力
		if ( iFileLoopIdx >= GD205_REC_LOOP_MAX ) {
			// ファイル出力
			if ( GD205WriteFile( fp, &stGD205Rec[0], GD205_REC_LOOP_MAX ) == RTN_NG ) {
				// 異常終了	LOG
//1.06 DELL printf("GD205WriteFile error\n");
				// 1.06 異常終了	LOG
				sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205CreateFile",__LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"GD205WriteFile error" );

				return( RTN_NG );
			}

			iFileLoopIdx = 0;
		}
		// 結果をファイル出力形式に展開
		if ( GD205MakeData( &pKekkaArray[iKekkaLoop],
							pSysknrmst->lbcd,
							&stGD205Rec[iFileLoopIdx] ) == RTN_NG ) {
			// 異常終了	LOG
//1.06 DELL printf("GD205MakeData error\n");
			// 1.06 異常終了	LOG
			sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205CreateFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"GD205MakeData error" );

			return( RTN_NG );
		}

		// 結果修正フラグをカウントアップ（最大'9'）
		if ( pKekkaArray[iKekkaLoop].kkassflg == GD205_DATA_SPACE ) {
			pKekkaArray[iKekkaLoop].kkassflg = '0';
		} else if ( pKekkaArray[iKekkaLoop].kkassflg != GD205_DB_KKASSFLG_MAX ) {
			++pKekkaArray[iKekkaLoop].kkassflg;
		}
		// 報告日時は関数内で設定

		// 検査フラグ←報告済
		pKekkaArray[iKekkaLoop].knsflg = GD205_DB_KNSFLG_DONE;

		// 情報更新日時は関数内で設定
        //2006.12.08 Kim Jinsuk DBエラー時異常終了させる
        int nRetValue;

		// 検査結果情報を更新
		iRet = ZdbKekkaGD205Update( &pKekkaArray[iKekkaLoop] );
		if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
//1.06 DELL printf("ZdbKekkaGD205Update error(%d)\n", iRet);
			// 1.06 異常終了	LOG
			sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205CreateFile", __LINE__,
						EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
						"ZdbKekkaGD205Update error(%d)", iRet);

            //2006.12.08 Kim Jinsuk DBエラー時異常終了させる
            nRetValue = iRet;

			// ロールバック
			ZdbRollback();

            //2006.12.08　Kim Jinsuk DBエラー時異常終了させる
            if((nRetValue < 0) && (nRetValue !=-803) && (nRetValue != -911))
            {
                *sqlErrorFlag = 1;
                printf("##### DBエラー　発生　#####\n");
                printf("iRet %d", iRet);
                sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbKekkaGD205Update", __LINE__,
                        EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
                        "DB エラー　発生　error value 0 %d", iRet);

                return( RTN_NG );
            }
            //2006.12.08　Kim Jinsuk DBエラー時異常終了させる

			// 1.13 ADD STA 一括COMMITに伴いエラー時は処理を抜ける			
				// エラーファイルとするため件数を0にする
			*piHkkssknsu=0;	
			break;
			// 1.13 ADD END 一括COMMITに伴いエラー時は処理を抜ける			

		}
// 2006-04-20 H.Suyama Add Start
		if ( pKekkaArray[iKekkaLoop].kkajkcd == GD205_DB_KKAJKCD_LAST ) {
			iRet = ZdbKekkaGD205UpdateOthers( &pKekkaArray[iKekkaLoop] );
			if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
//1.06 DELL printf("ZdbKekkaGD205UpdateOthers error(%d)\n", iRet);
				// 1.06 異常終了	LOG
				sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205CreateFile",__LINE__,
							EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
							"ZdbKekkaGD205UpdateOthers error (%d)", iRet);

				//2006.12.08 Kim Jinsuk DBエラー時異常終了させる
 				nRetValue = iRet;				

				// ロールバック
				ZdbRollback();
			
				//2006.12.08　Kim Jinsuk DBエラー時異常終了させる
				if((nRetValue < 0) && (nRetValue !=-803) && (nRetValue != -911))
				{

    				*sqlErrorFlag = 1;
    				printf("##### DBエラー　発生　#####\n");
    				printf("iRet %d", iRet);
					sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbKekkaGD205UpdateOthers", __LINE__,
        			EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
        			"DB エラー　発生");
    				return( RTN_NG );
				}
				//2006.12.08　Kim Jinsuk DBエラー時異常終了させる

				// 1.13 ADD STA 一括COMMITに伴いエラー時は処理を抜ける			
					// エラーファイルとするため件数を0にする
				*piHkkssknsu=0;	
				break;
				// 1.13 ADD END 一括COMMITに伴いエラー時は処理を抜ける			

			}
		}
		// 1.13 ADD 5000件毎にCOMMIT
		++iCmmtCnt;
		if( iCmmtCnt >= pEnv->iCommitSu ){
        	ZdbCommit();
			iCmmtCnt=0;
		}
		// 1.06 ADD コミット
		// 1.13 DELL
        //ZdbCommit();

// 2006-04-20 H.Suyama Add End
		++*piHkkssknsu;

		++iFileLoopIdx;
	}
	// 1.13 ADD 5000件毎にCOMMIT ファイル終了時には必ずCOMMIT
	if(( iCmmtCnt >= 1 )			// COMMIT 以降の更新件数が１以上
	 ||( *piHkkssknsu > 1 )){		// 報告ファイル出力件数が１以上
   		ZdbCommit();
	}

	// 1.12 ADD 保留以外報告対象0件の場合の考慮
	if( *piHkkssknsu == 0 ){
			// ファイルクローズ
			fclose( fp );
			// 中間ファイルなので0byte作成もOKとし、ファイル削除は行わない
			// 3.01 ファイル削除
			sFncPutLog( TRCKIND_TRACE, __FILE__, "GD205CreateFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"unlink cSendFileTemp" );
			unlink( cSendFileTemp );
			return( RTN_NG );
	}

	// ファイル出力
	if ( GD205WriteFile( fp, &stGD205Rec[0], iFileLoopIdx ) == RTN_NG ) {
		// 異常終了	LOG
//1.06 DELL printf("GD205WriteFile error\n");
		// 1.06 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205CreateFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"GD205WriteFile error " );
		return( RTN_NG );
	}

	// ファイルクローズ
	fclose( fp );

	// ファイル名（フルパス）を返却
	ZbmlInfocpy( pFileName, cFileName, PATH_MAX );

// 3.01 ADD STA
	// ファイル拡張子名変更
	iRet = rename( cSendFileTemp, cSendFile );
	if ( iRet != 0 ) {
		// 異常終了	LOG
		// 1.06 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205CreateFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"CreateHULFTFile rename status:[%d] ", iRet );

		gintErrorCode = GD205_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	// 返却用にファイル名と送信ファイルＩＤを設定
	memset( pHkkknriArrayOut->hkkflnm, 0, sizeof( pHkkknriArrayOut->hkkflnm ) );
	// 3.01 sprintf( pHkkknriArrayOut->hkkflnm, "%s_%04d_%s_%s_%s%04d%s",
	sprintf( pHkkknriArrayOut->hkkflnm, "%s_%04d_%s_%s_%s%03d0%s",
             // 3.01 pSysknrmst->sateid, 
             pEnv->cPrefixNm, 
			 pHkkknriArrayOut->hkksjno,
             pHkkknriArrayOut->seccd, sNewFlName, cKjnsriymd, 
			 // 3.01 pSysknrmst->ssntubn,
			 pHkkknriArrayOut->kkirilotno,
			 GD205_FILEEXT_DATA );
	memset( pHkkknriArrayOut->ssnmtfilid, 0, sizeof( pHkkknriArrayOut->ssnmtfilid ) );
	// 3.01 sprintf( pHkkknriArrayOut->ssnmtfilid, "%s%04d",
	sprintf( pHkkknriArrayOut->ssnmtfilid, "%s%03d0",
			 cKjnsriymd,
			 pHkkknriArrayOut->kkirilotno );
			 // 3.01 pSysknrmst->ssntubn );
// 3.01 ADD END

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：sFncShmCrt()												  */
/*　機能概要　：共有メモリ生成												  */
/*　入　　力　：															  */
/*　　第１引数：GD205Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：なし														  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
static int sFncShmCrt( GD205Env *pEnv )
{
	int	 *shmData;

	// 取得
	pEnv->shm_Id = shmget( (key_t)pEnv->shm_Key,
							GD205_SHM_SIZE,
							0666 | IPC_CREAT );
	if ( pEnv->shm_Id < 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_SHM_GET;
		return( RTN_NG );
	}

	// アタッチ
	shmData = ( int * ) shmat( pEnv->shm_Id, 0 , 0 );
	if ( shmData == ( int * )-1 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_SHM_AT;
		return( RTN_NG );
	}
loging ( "stocker : 共有メモリ[CRT] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n",
		 pEnv->shm_Key, pEnv->shm_Id, *shmData, shmData );

	// 値設定
	*shmData = 0;

	// デタッチ
	if ( shmdt( shmData ) == -1 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_SHM_DT;
		return( RTN_NG );
	}

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：sFncShmGet()												  */
/*　機能概要　：共有メモリ取得												  */
/*　入　　力　：															  */
/*　　第１引数：GD205Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　　第２引数：int *pshmData		値										  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
static int sFncShmGet( GD205Env *pEnv, int *pshmData )
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
		gintErrorCode = GD205_STSCODE_ERR_SHM_AT;
		return( RTN_NG );
	}

	// 値設定
	*pshmData = *shmData;

loging ( "stocker : 共有メモリ[GET] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n",
		 pEnv->shm_Key, pEnv->shm_Id, *shmData, shmData );
	// デタッチ
	if ( shmdt( shmData ) == -1 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_SHM_DT;
		return( RTN_NG );
	}

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：sFncShmDel()												  */
/*　機能概要　：共有メモリ削除												  */
/*　入　　力　：															  */
/*　　第１引数：GD205Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
static int sFncShmDel( GD205Env *pEnv )
{
	int	 *shmData;

loging ( "%s : 共有メモリ[DEL] shmKey[%d]-ID[%d]\n",
		 MYAPP_APP_NAME, pEnv->shm_Key, pEnv->shm_Id);
	// 削除
	if ( shmctl( pEnv->shm_Id, IPC_RMID, NULL) < 0 ) {
		// 異常終了	LOG
		gintErrorCode = GD205_STSCODE_ERR_SHM_DEL;
		return( RTN_NG );
	}
	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：_sFncEnvDip()												  */
/*　機能概要　：プログラム環境変数出力関数【トレース用】					  */
/*　入　　力　：															  */
/*　　第１引数：GD205Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：無し														  */
/******************************************************************************/
static void _sFncEnvDip( GD205Env *pEnv )
{
//#if defined ( _TRACE )
	loging( "########## GD205 - _sFncEnvDip ##########\n" );
	loging( "\t%s : [%s]\n", GD205_PRM_DBNAME,		 pEnv->cDBName );
	loging( "\t%s : [%s]\n", GD205_PRM_DBUSER,		 pEnv->cDBUser );
	loging( "\t%s : [%s]\n", GD205_PRM_DBPAWD,		 pEnv->cDBPawd );
	loging( "\t%s : [%s]\n", GD205_PRM_DIR_DATAFILE,   pEnv->cDirDataFile );
	loging( "\t%s : [%s]\n", GD205_PRM_SLEEP_SEC,	  pEnv->iSleepSec );
	loging( "\t%s : [%s]\n", GD205_PRM_SHM_KEY,	pEnv->shm_Key );
	loging( "\t%s : [%s]\n", GD205_PRM_FILE_DBG,	pEnv->cDebugLogName );
	loging( "\t%s : [%s]\n", GD205_PRM_FILE_TR,	pEnv->cTraceLogName );
	loging( "\t%s : [%s]\n", GD205_PRM_FILE_ACS,	pEnv->cAccessLogName );
	loging( "\t%s : [%s]\n", GD205_PRM_FILE_ERR,	pEnv->cErrorLogName );
	loging( "\t%s : [%s]\n", GD205_PRM_UP_ID,		pEnv->cUpdateId );
	loging( "\t%s : [%s]\n", GD205_PRM_UP_NM,		pEnv->cUpdateName );
	loging( "\t%s : [%s]\n", GD205_PRM_PROC_MD,	pEnv->proc_mode );
	loging( "########## GD205 - _sFncEnvDip ##########\n" );
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
	GD205Env	stEnv;

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


