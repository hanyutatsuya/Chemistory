/********************************************************************/
/*									*/
/*		ＢＭＬ様向け検査システム				*/
/*									*/
/*		システム名	：次世代システム			*/
/*		ファイル名	：LD104.c				*/
/*		概要		：他サテライト結果要求ファイル作成処理	*/
/*									*/
/********************************************************************/

/********************************************************************/
/*  Ver.	作成日		名前		修正内容		*/
/* ---------------------------------------------------------------- */
/********************************************************************/

/********************************************************************/
/*	インクルード宣言						*/
/********************************************************************/
#include <time.h>
#include <errno.h>
#include "bml_date.h"
#include "bmllog.h"
#include "bmlprm.h"
#include "LD104.h"

/**************************************************************************/
/* Define定義								  */
/**************************************************************************/
// TRACE
#if defined ( _TRACE )
#define malloc(a)   _malloc(a, __FILE__, __LINE__)
#define free(p)	 _free(p, __FILE__, __LINE__)
#endif

#define      isAscii(c)      (((c) >= 0x20 && (c) <= 0x7e) ? 1 : 0)

/**************************************************************************/
/* グローバル宣言							  */
/**************************************************************************/
struct stcLogMember	gstLogMem;

/******************************************************************************/
/*　関 数 名　：LD104ConvTimestamp()						*/
/*　機能概要　：日時変換関数							*/
/*　入　　力　：								*/
/*　　第１引数：ULONG ulTm	日時						*/
/*　出　　力　：								*/
/*　　第２引数：char *pDest	変換後文字列					*/
/*　　　　　　				YYYY-MM-DD-HH.MM.SS.000000		*/
/*　復帰情報　：int								*/
/*　　　　　　	RTN_OK	: 正常終了						*/
/*　　　　　　	RTN_NG	: 異常終了						*/
/******************************************************************************/
void LD104ConvTimestamp(ULONG ulTm, char *pDest)
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
/*　関 数 名　：LD104ConvNumber()						*/
/*　機能概要　：依頼書No、検体No変換関数					*/
/*　入　　力　：								*/
/*　　第２引数：char *pSrc	変換前文字列					*/
/*　　　　　　				[1][2][3][4][5][6][7][8][9][10][11]\0	*/
/*　出　　力　：								*/
/*　　第１引数：char *pDest	変換後文字列					*/
/*　　　　　　				[3][4][5] 0  0 [6][7][8][9][10][11]	*/
/*　復帰情報　：int								*/
/*　　　　　　		RTN_OK	: 正常終了					*/
/*　　　　　　		RTN_NG	: 異常終了					*/
/******************************************************************************/
int LD104ConvNumber(char *pDest, char *pSrc)
{
	// ポインタのチェック
	if ( pDest == NULL || pSrc == NULL ) {
		return( RTN_NG );
	}

	// 変換前文字列の長さチェック
	if ( strlen( pSrc ) < LD104_LEN_NOITEM ) {
		return( RTN_NG );
	}

	memcpy( &pDest[LD104_POS_DESTNO1], &pSrc[LD104_POS_SRCNO1], LD104_LEN_SRCNO1 );
	memcpy( &pDest[LD104_POS_DESTNO2], LD104_DATA_STR00, strlen( LD104_DATA_STR00 ) );
	memcpy( &pDest[LD104_POS_DESTNO3], &pSrc[LD104_POS_SRCNO2], LD104_LEN_SRCNO2 );

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：LD104CopyFromLeft()						*/
/*　機能概要　：指定文字列の左から指定桁数をコピーする				*/
/*　入　　力　：								*/
/*　　第２引数：char *pSrc			コピー元文字列			*/
/*　　第３引数：int iSize			コピー桁数			*/
/*　　第４引数：BOOL bMbFlg			マルチバイトフラグ		*/
/* 　　　　　		TRUE	: 考慮する					*/
/* 　　　　　		FALSE	: 無視する					*/
/*　出　　力　：								*/
/*　　第１引数：char *pDest			コピー後文字列			*/
/*　復帰情報　：int								*/
/*　　　　　　		RTN_OK	: 正常終了					*/
/*　　　　　　		RTN_NG	: 異常終了					*/
/******************************************************************************/
int LD104CopyFromLeft(char *pDest, char *pSrc, int iSize, BOOL bMbFlg)
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

/********************************************************************************/
/*　関 数 名　：LD104CopyFromRight()						*/
/*　機能概要　：指定文字列の右から指定桁数をコピーする				*/
/*　入　　力　：								*/
/*　　第２引数：char *pSrc	コピー元文字列					*/
/*　　第３引数：int iSize	コピー桁数					*/
/*　　第４引数：BOOL bMbFlg	マルチバイトフラグ				*/
/* 　　　　　	TRUE	: 考慮する						*/
/* 　　　　　	FALSE	: 無視する						*/
/*　出　　力　：								*/
/*　　第１引数：char *pDest			コピー後文字列			*/
/*　復帰情報　：int								*/
/*　　　　　　		RTN_OK	: 正常終了					*/
/*　　　　　　		RTN_NG	: 異常終了					*/
/********************************************************************************/
int LD104CopyFromRight(char *pDest, char *pSrc, int iSize, BOOL bMbFlg)
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
/*　関 数 名　：initFunction()							  */
/*　機能概要　：初期処理関数							  */
/*　入　　力　：								  */
/*　　第１引数：int argc		プログラム引数数			  */
/*　　第２引数：char *argv[]		プログラム引数				  */
/*　出　　力　：								  */
/*　復帰情報　：int								  */
/*　　　　　　		RTN_OK	: 正常終了					  */
/*　　　　　　		RTN_NG	: 異常終了					  */
/******************************************************************************/
int initFunction( int argc, char *argv[] )
{
	char	cPrmBuf[256];
	char	*lc_login;

	// 初期化
	// プログラム環境変数初期化
	memset( &pAppEnv, '\0', sizeof( pAppEnv ) );

	// ログオープン
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

	//      開始ログ出力
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "プログラム起動" ) ;

	// パラメータファイル名退避
	lc_login= EnvRef( MYAPP_LOGINIFILE );
	if ( argc >= 2 ) {
		pAppEnv.pcFileNamePRM = EnvRef( argv[1] );
	} else {
		pAppEnv.pcFileNamePRM = EnvRef( MYAPP_INIFILE );
	}

	pAppEnv.bp = ZbmlPrmOpen( pAppEnv.pcFileNamePRM );
	if ( pAppEnv.bp == NULL ) {
		// 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmOpen", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "パラメータファイルのオープンに失敗しました[%s]", pAppEnv.pcFileNamePRM );
		return( RTN_NG );
	}

	// データベース接続名
	if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_DBNAME, pAppEnv.cDBName ) != 0 ) {
		// 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "パラメータの取得に失敗しました[%s]", LD104_PRM_DBNAME );
		return( RTN_NG );
	}
	// ログインユーザ
	if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_DBUSER, pAppEnv.cDBUser ) != 0 ) {
		// 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "パラメータの取得に失敗しました[%s]", LD104_PRM_DBUSER );
		return( RTN_NG );
	}
        // データフローＩＤ
        if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_DATAFLOWID, pAppEnv.cDataFlowID ) != 0 ) {
                // 異常終了     LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "パラメータの取得に失敗しました[%s]", LD104_PRM_DATAFLOWID );
                return( RTN_NG );
        }
        // 送信元ＩＤ
        if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_SENDID_MOTO, pAppEnv.cSendIDMoto ) != 0 ) {
                // 異常終了     LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "パラメータの取得に失敗しました[%s]", LD104_PRM_SENDID_MOTO );
                return( RTN_NG );
        }
        // 送信先ＩＤ
        if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_SENDID_SAKI, pAppEnv.cSendIDSaki ) != 0 ) {
                // 異常終了     LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "パラメータの取得に失敗しました[%s]", LD104_PRM_SENDID_SAKI );
                return( RTN_NG );
        }
	// ログインパスワード
	if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_DBPAWD, pAppEnv.cDBPawd ) != 0 ) {
		// 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "パラメータの取得に失敗しました[%s]", LD104_PRM_DBPAWD );
		return( RTN_NG );
	}
	// データファイル出力ディレクトリ
	if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_DIR_DATAFILE, pAppEnv.cDirDataFile ) != 0 ) {
		// 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"パラメータの取得に失敗しました[%s]", LD104_PRM_DIR_DATAFILE );
		return( RTN_NG );
	}
	// データファイル送信用ディレクトリ
	if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_DIR_SEND, pAppEnv.cDirSend ) != 0 ) {
		// 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "パラメータの取得に失敗しました[%s]", LD104_PRM_DIR_SEND );
		return( RTN_NG );
	}
	// デバッグログファイル
	if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_FILE_DBG, pAppEnv.cDebugLogName ) != 0 ) {
		// 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "パラメータの取得に失敗しました[%s]", LD104_PRM_FILE_DBG );
		return( RTN_NG );
	}
	// トレースログファイル
	if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_FILE_TR, pAppEnv.cTraceLogName ) != 0 ) {
		// 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "パラメータの取得に失敗しました[%s]", LD104_PRM_FILE_TR );
		return( RTN_NG );
	}
	// アクセスログファイル
	if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_FILE_ACS, pAppEnv.cAccessLogName ) != 0 ) {
		// 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "パラメータの取得に失敗しました[%s]", LD104_PRM_FILE_ACS );
		return( RTN_NG );
	}
	// エラーログファイル
	if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_FILE_ERR, pAppEnv.cErrorLogName ) != 0 ) {
		// 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "パラメータの取得に失敗しました[%s]", LD104_PRM_FILE_ERR );
		return( RTN_NG );
	}
	// 共有メモリキー取得
	if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_SHM_KEY, cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "パラメータの取得に失敗しました[%s]", LD104_PRM_SHM_KEY );
		return( RTN_NG );
	}
	pAppEnv.shm_Key = atoi( cPrmBuf );
	// スリープ時間（秒）取得
	if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_SLEEP_MIN, cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "パラメータの取得に失敗しました[%s]", LD104_PRM_SLEEP_MIN );
		return( RTN_NG );
	}
	pAppEnv.iSleepMin= atoi( cPrmBuf );
	// 検索日付の取得
	if ( ZbmlPrmGetVal ( pAppEnv.bp, LD104_PRM_DATE_RANGE, cPrmBuf ) != 0 ) {
		// 異常終了     LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "パラメータが取得できませんでした[%s]", LD104_PRM_DATE_RANGE ) ;
		return ( -1 ) ;
	}
	pAppEnv.DateRange= atoi ( cPrmBuf ) ;

	// パラメータファイルクローズ
	ZbmlPrmClose( pAppEnv.bp );

	// 共有メモリ生成
	if ( sFncShmCrt() != RTN_OK ) {
		return( RTN_NG );
	}

	return( RTN_OK );
}

/**************************************************************************/
/*　関 数 名　：mainFunction()						  */
/*　機能概要　：メイン処理関数						  */
/*　入　　力　：							  */
/*　出　　力　：							  */
/*　復帰情報　：int							  */
/*　　　　　　		RTN_OK	: 正常終了				  */
/*　　　　　　		RTN_NG	: 異常終了				  */
/**************************************************************************/
int mainFunction()
{
	int		li_stopFlg = 0;

	int		min = 0;
	int		iRet;
	int		iKekkaNumOut;
	char		serch_date[11];

	Sysknrmst	stSysknrmst;
	GetKekka	*pGetKekkaArrayOut;

	if( iRet = ZdbConnect( pAppEnv.cDBName, pAppEnv.cDBUser, pAppEnv.cDBPawd ) ) {
		return( RTN_NG );
	}

	// 永久ループ、停止コマンドで終了
	while ( 1 ) {
		/* 1分ごとに停止コマンドを確認しながら設定された時間スリープ */
		for ( min=0; min < pAppEnv.iSleepMin; min++ ) {
			sleep( 60 );
			// 停止コマンド確認
			if ( sFncShmGet( &li_stopFlg ) != RTN_OK ) {
				return( RTN_NG );
			}
			if ( li_stopFlg == 1 ) {
				return( RTN_OK );
			}
			// システム管理情報取得
			iRet = ZdbSysknrmstSelect( &stSysknrmst );
			if ( iRet != HRC_SQL_NORMAL ) {
				return( RTN_NG );
			}
			// 分注ＥＮＤが来ている場合は、日次処理の開始確認を行う。
			if ( stSysknrmst.bchendflg == '1' ){
				/* 日次処理が始まっていたら終了 */
				if ( stSysknrmst.unyflg == '1' ){
					sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						     "日次処理の開始を確認しました。");
					return( RTN_OK );
				}
			}
		}

		// システム管理情報取得
		iRet = ZdbSysknrmstSelect( &stSysknrmst );
		if ( iRet != HRC_SQL_NORMAL ) {
			return( RTN_NG );
		}
		// 分注ＥＮＤがきていなければ、処理を開始しない
		if ( stSysknrmst.bchendflg != '1' ){
			continue;
		}

		sFncPutLog( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
			    "要求カード作成処理開始");

		memset( serch_date, '\0', sizeof( serch_date ) );
		sFncGetdate( serch_date, stSysknrmst.kjnsriymd, pAppEnv.DateRange );
		iRet = ZdbKekkaLD104Select( serch_date, &pGetKekkaArrayOut, &iKekkaNumOut );
		if ( iRet == HRC_SQL_NORMAL ) {
			/* 送信管理通番 カウントアップ */
			++stSysknrmst.ssntubn;
			iRet = ZdbSysknrmstUpdate( &stSysknrmst );
		        if ( iRet != HRC_SQL_NORMAL ) {
				// ロールバック
				ZdbRollback();
				sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
					    "ZdbSysknrmstUpdate error [%d]", iRet );

				return( RTN_NG );
		        }
			// コミット
			ZdbCommit();

			// 要求カードファイルの作成
			if ( LD104CreateFile( &stSysknrmst, pGetKekkaArrayOut, iKekkaNumOut) != RTN_OK ) {
				return( RTN_NG );
			}
		} else if ( iRet == HRC_SQL_NOT_FOUND ) {
			sFncPutLog( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
				    "要求カード作成対象無し");
		} else {
			// 結果情報を解放
			if ( pGetKekkaArrayOut != NULL ) {
				ZbmlFree( pGetKekkaArrayOut );
			}
			return( RTN_NG );
		}

		// 結果情報を解放
		if ( pGetKekkaArrayOut != NULL ) {
			ZbmlFree( pGetKekkaArrayOut );
		}
	}

	return( RTN_OK );
}

/**************************************************************************/
/*　関 数 名　：endFunction()						  */
/*　機能概要　：終了処理関数						  */
/*　入　　力　：							  */
/*　出　　力　：							  */
/*　復帰情報　：なし							  */
/**************************************************************************/
void endFunction()
{
	/***	
	***    データベースクローズ
	**/
	ZdbDisConnect() ;

	// 共有メモリ削除
	if ( sFncShmDel() != RTN_OK ) {
		return;
	}
	/*      終了ログ出力 */
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "プログラム終了" ) ;
	/*      ログクローズ */
	ZbmlCloseLog() ;

	return ;
}

/**************************************************************************/
/*　関 数 名　：LD104MakeData()						  */
/*　機能概要　：他サテライト結果要求ファイルデータ作成			  */
/*　入　　力　：							  */
/*　　第１引数：Kekka *pKekka		検査結果データ			  */
/*　出　　力　：							  */
/*　　第３引数：LD104Rec *pLD104Rec	要求ファイルデータ		  */
/*　復帰情報　：int							  */
/*　　　　　　		RTN_OK	: 正常終了				  */
/*　　　　　　		RTN_NG	: 異常終了				  */
/**************************************************************************/
int LD104WriteRecord(FILE *fp, GetKekka *pGetKekka)
{
	int		iFileCnt;
	LD104Rec	pLD104Rec;

	// 検査結果データへのポインタがNULLの場合異常終了
	if ( pGetKekka == NULL ) {
		return( RTN_NG );
	}

	// 要求ファイルデータをスペースでクリア
	memset( &pLD104Rec, LD104_DATA_SPACE, sizeof(LD104Rec) );

	// レコード識別子
	memcpy( pLD104Rec.c_sbt, "R11", sizeof( pLD104Rec.c_sbt ));

	// ＢＭＬ受付年月日
	// [YYYYMMDD]に変換して設定
	ZbmlChgAPDate( pLD104Rec.c_utkymd, pGetKekka->utkymd );
	// 依頼書Ｎｏ．
	// 左から11桁を↓のように変換
	// (変換前)[1][2][3][4][5][6][7][8][9][10][11]
	// (変換後)[3][4][5] 0  0 [6][7][8][9][10][11]
	if ( LD104ConvNumber( pLD104Rec.c_irino, pGetKekka->irino ) == RTN_NG ) {
		return( RTN_NG );
	}
	// 項目コード
	if ( LD104CopyFromLeft( pLD104Rec.c_kmkcd, pGetKekka->kmkcd, sizeof( pLD104Rec.c_kmkcd ), FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}

        /* FILLER               */
        memset( pLD104Rec.c_filler, ' ', sizeof( pLD104Rec.c_filler ));
        /* 改行ｺｰﾄﾞ             */
        memcpy( pLD104Rec.c_kaigyo, "\n", sizeof( pLD104Rec.c_kaigyo ));

	// レコード書込み
	iFileCnt = fwrite( &pLD104Rec, sizeof( LD104Rec ) , 1, fp);
	if ( iFileCnt != 1 ) {
		// 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "LD104WriteFile", __LINE__,
			    EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "write status:[%d] ", iFileCnt );
		return( RTN_NG ) ;
	}

	return( RTN_OK );
}

/************************************************************************/
/*　関 数 名　：LD104WriteFile()					*/
/*　機能概要　：トレーラーレコード書込み				*/
/*　入　　力　：							*/
/*　　第１引数：FILE *fp		ファイルポインタ		*/
/*　　第２引数：LD104Rec *pLD104Rec	要求ファイルデータ		*/
/*　出　　力　：検査結果ファイル					*/
/*　復帰情報　：int							*/
/*　　　　　　		RTN_OK	: 正常終了				*/
/*　　　　　　		RTN_NG	: 異常終了				*/
/************************************************************************/
int LD104WriteHeader(FILE *fp, Sysknrmst *pSysknrmst)
{
	int		iFileCnt;
	LD104Header	z00;

	memset( &z00, ' ', sizeof( struct Z00SJHD ) );

        /* ﾚｺｰﾄﾞ識別子          */
        memcpy( z00.c_sbt, "HD", sizeof( z00.c_sbt ));
        /* 送信先               */
        memcpy( z00.c_sosinsaki, pAppEnv.cSendIDSaki, strlen( pAppEnv.cSendIDSaki ));
        /* 送信元               */
        memcpy( z00.c_sosinmoto, pAppEnv.cSendIDMoto, strlen( pAppEnv.cSendIDMoto ));
        /* 送信元処理年月日     */
	// [YYYYMMDD]に変換して設定
	ZbmlChgAPDate( z00.c_opedate, pSysknrmst->kjnsriymd );
        /* 通番                 */
	sprintf( z00.c_tuban, "%04d" , pSysknrmst->ssntubn);
	/* ﾃﾞｰﾀﾌﾛｰID */
	memcpy( z00.c_dflow,   pAppEnv.cDataFlowID, strlen( pAppEnv.cDataFlowID ));
        /* ﾊﾟﾗﾒｰﾀ1              */
        memset( z00.c_param1, ' ', sizeof( z00.c_param1 ));
        /* ﾊﾟﾗﾒｰﾀ2              */
        memset( z00.c_param2, ' ', sizeof( z00.c_param2 ));
        /* 予備                 */
        memset( z00.c_yobi, ' ', sizeof( z00.c_yobi ));
        /* FILLER               */
        memset( z00.c_filler, ' ', sizeof( z00.c_filler ));
        /* 改行ｺｰﾄﾞ             */
        memcpy( z00.c_kaigyo, "\n", sizeof( z00.c_kaigyo ));

	// レコード書込み
	iFileCnt = fwrite( &z00, sizeof( z00 ) , 1, fp);
	if ( iFileCnt != 1 ) {
		// 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "LD104WriteFile", __LINE__,
			    EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "write status:[%d] ", iFileCnt );
		return( RTN_NG ) ;
	}


	return( RTN_OK );
}

/************************************************************************/
/*　関 数 名　：LD104WriteTrailer()					*/
/*　機能概要　：トレーラーレコード書込み				*/
/*　入　　力　：							*/
/*　　第１引数：FILE *fp		ファイルポインタ		*/
/*　　第２引数：LD104Rec *pLD104Rec	要求ファイルデータ		*/
/*　出　　力　：検査結果ファイル					*/
/*　復帰情報　：int							*/
/*　　　　　　		RTN_OK	: 正常終了				*/
/*　　　　　　		RTN_NG	: 異常終了				*/
/************************************************************************/
int LD104WriteTrailer(FILE *fp, Sysknrmst *pSysknrmst, int iKekkaNum)
{
	int		iFileCnt;
	LD104Trailer	z01;

        // PNC送受信 、トレーラー作成
	memset( &z01, ' ', sizeof( LD104Trailer ) );

        /* ﾚｺｰﾄﾞ識別子          */
	memcpy( z01.c_sbt, "TR", sizeof( z01.c_sbt ));
        /* 送信先               */
        memcpy( z01.c_sosinsaki, pAppEnv.cSendIDSaki, strlen( pAppEnv.cSendIDSaki ));
        /* 送信元               */
        memcpy( z01.c_sosinmoto, pAppEnv.cSendIDMoto, strlen( pAppEnv.cSendIDMoto ));
        /* 送信元処理年月日     */
	// [YYYYMMDD]に変換して設定
	ZbmlChgAPDate( z01.c_opedate, pSysknrmst->kjnsriymd );
        /* 通番                 */
	sprintf( z01.c_tuban, "%04d" , pSysknrmst->ssntubn);
	/* ﾃﾞｰﾀﾌﾛｰID */
	memcpy( z01.c_dflow,   pAppEnv.cDataFlowID, strlen( pAppEnv.cDataFlowID ));
        /* 物理ﾚｺｰﾄﾞ件数 */
	sprintf( z01.c_reccnt, "%08d" , iKekkaNum + 2);
        /* 論理ﾚｺｰﾄﾞ件数１ */
	sprintf( z01.c_reccnt01, "%08d" , iKekkaNum);
        /* 論理ﾚｺｰﾄﾞ件数２～１５ */
        memset( z01.c_reccnt02, '0', sizeof( z01.c_reccnt02 ));
        /* 予備                 */
        memset( z01.c_yobi, ' ', sizeof( z01.c_yobi ));
        /* FILLER               */
        memset( z01.c_filler, ' ', sizeof( z01.c_filler ));
        /* 改行ｺｰﾄﾞ             */
        memcpy( z01.c_kaigyo, "\n", sizeof( z01.c_kaigyo ));

	// レコード書込み
	iFileCnt = fwrite( &z01, sizeof( z01 ) , 1, fp);
	if ( iFileCnt != 1 ) {
		// 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "LD104WriteFile", __LINE__,
			    EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "write status:[%d] ", iFileCnt );
		return( RTN_NG ) ;
	}

	return( RTN_OK );
}

/********************************************************************************/
/*　関 数 名　：LD104CreateFile()						*/
/*　機能概要　：要求ファイル作成						*/
/*　入　　力　：								*/
/*　　第１引数：GetKekka *pGetKekkaArray	検査結果情報			*/
/*　　第２引数：int iKekkaNum			検査結果情報件数		*/
/*　出　　力　：								*/
/*　復帰情報　：int								*/
/*　　　　　　		RTN_OK	: 正常終了					*/
/*　　　　　　		RTN_NG	: 異常終了					*/
/********************************************************************************/
int LD104CreateFile(Sysknrmst *pSysknrmst, GetKekka *pGetKekkaArray, int iKekkaNum)
{
	int		iRet = 0;
	FILE *		fp;
	int		iKekkaLoop;
	time_t timer;
        struct tm	*tm;
	char		cToday[LD104_LEN_DATETIME + 1];
	char		cTmpFileName[PATH_MAX + 1];
	char		cFileName[PATH_MAX + 1];


	// 引数チェック
	if ( pGetKekkaArray == NULL ) {
		return( RTN_NG );
	}

	time(&timer);
        tm = localtime(&timer);
        sprintf( cToday, "%04d%02d%02d%02d%02d%02d",
                         tm->tm_year + 1900,
                         tm->tm_mon + 1,
                         tm->tm_mday,
                         tm->tm_hour,
                         tm->tm_min,
                         tm->tm_sec );

	// ファイル名生成
	sprintf( cTmpFileName, "%s/REQ00%s%s", pAppEnv.cDirDataFile, cToday, LD104_FILEEXT_DATA );
	sprintf( cFileName, "%s/REQ00%s%s", pAppEnv.cDirSend, cToday, LD104_FILEEXT_DATA );

	// ファイルオープン
	fp = fopen ( cTmpFileName, "w" );
	if ( fp == NULL ) {
		// 異常終了	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "LD104CreateFile",__LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			    "fopen error [%s]:%s", cTmpFileName, strerror(errno) );
		fclose( fp );
		return( RTN_NG ) ;
	}

	// ヘッダ出力
	if ( LD104WriteHeader( fp, pSysknrmst ) == RTN_NG ) {
		sFncPutLog( TRCKIND_ERROR, __FILE__, "LD104CreateFile",__LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			    "LD104WriteFile error [%s]", cTmpFileName );
		fclose( fp );
		return( RTN_NG );
	}

	// 要求結果情報を１件ずつ処理
	for ( iKekkaLoop = 0;
		  iKekkaLoop < iKekkaNum;
		  iKekkaLoop++ ) {

		// 結果をファイル出力形式に展開
		if ( LD104WriteRecord( fp, &pGetKekkaArray[iKekkaLoop] ) == RTN_NG ) {
			sFncPutLog( TRCKIND_ERROR, __FILE__, "LD104CreateFile",__LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				    "LD104MakeData error [%s]", cTmpFileName );
			fclose( fp );
			return( RTN_NG );
		}

	}

	// フッター 出力
	if ( LD104WriteTrailer( fp, pSysknrmst, iKekkaNum ) == RTN_NG ) {
		sFncPutLog( TRCKIND_ERROR, __FILE__, "LD104CreateFile",__LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "LD104WriteFile error [%s]", cTmpFileName );
		fclose( fp );
		return( RTN_NG );
	}

	// ファイルクローズ
	fclose( fp );

	// ファイルを送信用ディレクトリへ移動
	if ( rename( cTmpFileName, cFileName ) != 0 ){
		sFncPutLog( TRCKIND_ERROR, __FILE__, "LD104CreateFile",__LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "rename error [%s]->[%s]:%s", cTmpFileName, cFileName, strerror(errno) );
		return( RTN_NG );
	}

	sFncPutLog( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
		    "ファイル作成完了 [%s : %d件]", cFileName, iKekkaNum );

	return( RTN_OK );
}

/******************************************************************************/
/*  関 数 名　：sFncGetdate()                                                   */
/*  機能概要　：日付演算関数                                                    */
/*  入　　力　：                                                              */
/*　 第２引数 ：char *  基準日付文字列( yyyy-mm-dd )                            */
/*　 第３引数 ：int     差分日数(普通に指定すると何日後。－指定で何日前となる)  */
/*  出　　力　：                                                              */
/*　 第１引数 ：char *  取得日付文字列( yyyy-mm-dd )                            */
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

/******************************************************************************/
/*　関 数 名　：sFncShmCrt()							*/
/*　機能概要　：共有メモリ生成							*/
/*　入　　力　：								*/
/*　出　　力　：なし								*/
/*　復帰情報　：int								*/
/*　　　　　　		RTN_OK	: 正常終了					*/
/*　　　　　　		RTN_NG	: 異常終了					*/
/******************************************************************************/
static int sFncShmCrt()
{
	int	 *shmData;

	// 取得
	pAppEnv.shm_Id = shmget( (key_t)pAppEnv.shm_Key, LD104_SHM_SIZE, 0666 | IPC_CREAT );
	if ( pAppEnv.shm_Id < 0 ) {
		// 異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmget", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"共有メモリの操作に失敗しました" ) ;
		return( RTN_NG );
	}

	// アタッチ
	shmData = ( int * ) shmat( pAppEnv.shm_Id, 0 , 0 );
	if ( shmData == ( int * )-1 ) {
		// 異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmat", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"共有メモリの操作に失敗しました" ) ;
		return( RTN_NG );
	}

	// 値設定
	*shmData = 0;

	// デタッチ
	if ( shmdt( shmData ) == -1 ) {
		// 異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"共有メモリの操作に失敗しました" ) ;
		return( RTN_NG );
	}

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：sFncShmGet()							*/
/*　機能概要　：共有メモリ取得							*/
/*　入　　力　：								*/
/*　出　　力　：								*/
/*　　第１引数：int *pshmData		値					*/
/*　復帰情報　：int								*/
/*　　　　　　		RTN_OK	: 正常終了					*/
/*　　　　　　		RTN_NG	: 異常終了					*/
/******************************************************************************/
static int sFncShmGet( int *pshmData )
{
	int	 *shmData;

	//
	if ( pshmData == NULL ) {
		// 異常終了	LOG
		return( RTN_NG );
	}

	// アタッチ
	shmData = ( int * ) shmat( pAppEnv.shm_Id, 0 , 0 );
	if ( shmData == ( int * )-1 ) {
		//      異常終了        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmat", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"共有メモリの操作に失敗しました" ) ;

		return( RTN_NG );
	}

	// 値設定
	*pshmData = *shmData;

	// デタッチ
	if ( shmdt( shmData ) == -1 ) {
		// 異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"共有メモリの操作に失敗しました" ) ;

		return( RTN_NG );
	}

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：sFncShmDel()							*/
/*　機能概要　：共有メモリ削除							*/
/*　入　　力　：								*/
/*　出　　力　：								*/
/*　復帰情報　：int								*/
/*　　　　　　		RTN_OK	: 正常終了					*/
/*　　　　　　		RTN_NG	: 異常終了					*/
/******************************************************************************/
static int sFncShmDel()
{
	int	 *shmData;

	loging ( "%s : 共有メモリ[DEL] shmKey[%d]-ID[%d]\n",
		 MYAPP_APP_NAME, pAppEnv.shm_Key, pAppEnv.shm_Id);
	// 削除
	if ( shmctl( pAppEnv.shm_Id, IPC_RMID, NULL) < 0 ) {
		// 異常終了	LOG
		return( RTN_NG );
	}
	return( RTN_OK );
}


/******************************************************************************/
/*　関 数 名　：sFncPutLog()							*/
/*　機能概要　：アプリケーションログ出力					*/
/*　入　　力　：								*/
/*　　第１引数：char *	  編集文字列						*/
/*　出　　力　：								*/
/*　復帰情報　：無し								*/
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
/*　関 数 名　：main()								*/
/*　機能概要　：要求カードファイル作成処理メイン				*/
/*　入　　力　：								*/
/*　　第１引数：int argc		プログラム引数数			*/
/*　　第２引数：char *argv[]		プログラム引数				*/
/*　出　　力　：								*/
/*　復帰情報　：int								*/
/******************************************************************************/
int main( int argc, char *argv[] )
{
    if ( daemon ( 1, 0 ) < 0 ) {
        exit ( 9 ) ;
    }

	// 初期処理
	if ( initFunction( argc, argv )  != 0 ) {
		exit( 9 );
	}

	// 主処理
	if ( mainFunction()  != 0 ) {
		exit( 9 );
	}

	// 終了処理
	endFunction();
}
