/********************************************************************/
/*																	*/
/*		ＢＭＬ様向け検査システム									*/
/*																	*/
/*		システム名	：次世代システム								*/
/*		ファイル名	：ED203Main.c									*/
/*		概要		：緊急結果報告ファイル作成処理					*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	作成日			名前			修正内容				*/
/* ---------------------------------------------------------------- */
/*  1.00	2006/03/13		H.Suyama		Create					*/
/********************************************************************/

/********************************************************************/
/*	インクルード宣言												*/
/********************************************************************/
#include <time.h>
//#include "bml_misc.h"
#include "bml_date.h"
#include "bmllog.h"
#include "bmlprm.h"
#include "ED203Main.h"
#include "Sysknrmst.h"
#include "ED203Hkkknri.h"

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
ED203_STSCODE		gintErrorCode;
struct stcLogMember	gstLogMem;

/******************************************************************************/
/*　関 数 名　：ED203ConvTimestamp()										  */
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
void ED203ConvTimestamp(ULONG ulTm, char *pDest)
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
/*　関 数 名　：ED203ConvNumber()											  */
/*　機能概要　：依頼書No、検体No変換関数									  */
/*　入　　力　：															  */
/*　　第２引数：char *pSrc			変換前文字列							  */
/*　　　　　　						[1][2][3][4][5][6][7][8][9][10][11]\0	  */
/*　出　　力　：															  */
/*　　第１引数：char *pDest			変換後文字列							  */
/*　　　　　　						[4][5][6][7][8][9]						  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int ED203ConvNumber(char *pDest, char *pSrc)
{
	// ポインタのチェック
	if ( pDest == NULL || pSrc == NULL ) {
		return( RTN_NG );
	}

	// 変換前文字列の長さチェック
	if ( strlen( pSrc ) < ED203_LEN_NOITEM ) {
		return( RTN_NG );
	}

	memcpy( pDest, &pSrc[ED203_POS_SRCNO], ED203_LEN_SRCNO );

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：ED203CopyFromLeft()											  */
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
int ED203CopyFromLeft(char *pDest, char *pSrc, int iSize, BOOL bMbFlg)
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
/*　関 数 名　：ED203CopyFromRight()										  */
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
int ED203CopyFromRight(char *pDest, char *pSrc, int iSize, BOOL bMbFlg)
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
/*　関 数 名　：initFunction()												  */
/*　機能概要　：初期処理関数												  */
/*　入　　力　：															  */
/*　　第１引数：int argc			プログラム引数数						  */
/*　　第２引数：char *argv[]		プログラム引数							  */
/*　　第３引数：ED203Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int initFunction( int argc, char *argv[], ED203Env *pEnv )
{
	char	cPrmBuf[256];
	char	*lc_login;

	// 初期化
	// エラーステータス変更
	gintErrorCode = 0;
	// プログラム環境変数初期化
	memset( pEnv, '\0', sizeof( ED203Env ) );

	// ログオープン
	if( ZbmlOpenLog( MYAPP_LOGINIFILE ) != 0 ) {
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
		gintErrorCode = ED203_STSCODE_ERR_USEGE;
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
		gintErrorCode = ED203_STSCODE_ERR_PRM_FILE;
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZZbmlPrmOpen", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"パラメータファイルのオープンに失敗しました[%s]", pEnv->pcFileNamePRM );
		return( RTN_NG );
	}

	// データベース接続名
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_DBNAME,
						 pEnv->cDBName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ログインユーザ
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_DBUSER,
						pEnv->cDBUser ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ログインパスワード
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_DBPAWD,
						pEnv->cDBPawd ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 報告データファイル出力ディレクトリ
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_DIR_DATAFILE,
						pEnv->cDirDataFile ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// デバッグログファイル
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_FILE_DBG,
						pEnv->cDebugLogName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// トレースログファイル
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_FILE_TR,
						pEnv->cTraceLogName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// アクセスログファイル
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_FILE_ACS,
						pEnv->cAccessLogName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// エラーログファイル
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_FILE_ERR,
						pEnv->cErrorLogName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 共有メモリキー取得
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_SHM_KEY,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->shm_Key = atoi( cPrmBuf );
	// スリープ時間（秒）取得
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_SLEEP_SEC,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iSleepSec= atoi( cPrmBuf );
	// 更新者ID
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_UP_ID,
						pEnv->cUpdateId ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 更新者名
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_UP_NM,
						pEnv->cUpdateName ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// 実行モード
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_PROC_MD,
						cPrmBuf ) != 0 ) {
		// 異常終了	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
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
/*　　第１引数：ED203Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int mainFunction( ED203Env *pEnv )
{
	int			iRet;
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
	char		cHkkflnm[51];
	int			li_stopFlg = 0;

	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	if( iRet = ZdbConnect( pEnv->cDBName,
						   pEnv->cDBUser,
						   pEnv->cDBPawd ) ) {
		// 異常終了	LOG
printf("ZdbConnect error (%d)\n", iRet);
		return( RTN_NG );
	}

	// 報告管理情報テーブル監視
	// 永久ループ、停止コマンドで終了
	while ( 1 ) {
		// 停止コマンド確認
		if ( sFncShmGet( pEnv, &li_stopFlg ) != RTN_OK ) {
printf("sFncShmGet error\n");
			return( RTN_NG );
		}
		if ( li_stopFlg == 1 ) {
			break;
		}

		// 報告管理情報検索
		iRet = ZdbHkkknriED203SelectAll( &pHkkknriArrayOut, &iHkkknriNumOut );
		if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
			//異常終了
			//ログ出力
printf("ZdbHkkknriED203SelectAll error (%d)\n", iRet);
			return( RTN_NG );
		}
		if ( iRet == HRC_SQL_NORMAL ) {
			// 報告管理情報を１件ずつ処理
			for ( iHkkknriLoop = 0;
				  iHkkknriLoop < iHkkknriNumOut;
				  iHkkknriLoop++ ) {
				// 作成開始日時を取得
				time( (long *)&ulSt );

				// 作成件数、保留件数をクリア
				iHkkssknsu = 0;
				iHkkhrysu = 0;
				memset( cHkkflnm, 0, sizeof( cHkkflnm ) );

				// 結果情報検索（送信対象のみ）
				// 報告区分を結果状況コードの値にあわせる
				switch ( pHkkknriArrayOut[iHkkknriLoop].hkkkbn ) {
				case '1':	// 最終
					pHkkknriArrayOut[iHkkknriLoop].hkkkbn = '3';
					break;
				case '2':	// 中間
					pHkkknriArrayOut[iHkkknriLoop].hkkkbn = '1';
					break;
				}
				iRet = ZdbKekkaED203SelectByKkIriLotNo( &pHkkknriArrayOut[iHkkknriLoop],
														&pKekkaArrayOut, &iKekkaNumOut );
				if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
					// 異常終了	LOG
printf("ZdbKekkaED203SelectByXXXX error (%d)\n", iRet);
					return( RTN_NG );
				}
				if ( iRet == HRC_SQL_NORMAL ) {
					if ( ED203CreateFile( pEnv, 
										  pKekkaArrayOut,
										  iKekkaNumOut,
										  &iHkkssknsu,
										  &iHkkhrysu,
										  cHkkflnm ) == RTN_NG ) {
						// 異常終了	LOG
printf("ED203CreateFile error\n");
						return( RTN_NG );
					}
				}

				// 結果情報を解放
				if ( pKekkaArrayOut != NULL ) {
					ZbmlFree( pKekkaArrayOut );
				}

				// 作成完了日時を取得
				time( (long *)&ulEd );

				// 作成開始日時
				ED203ConvTimestamp( ulSt, cTimestamp );
				ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkstdh,
							 cTimestamp,
							 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkstdh ) );
				// 作成完了日時
				ED203ConvTimestamp( ulEd, cTimestamp );
				ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkeddh,
							 cTimestamp,
							 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkeddh ) );
				// 報告ファイル名
				ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkflnm,
							 cHkkflnm,
							 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkflnm ) );
				// 作成件数
				pHkkknriArrayOut[iHkkknriLoop].hkkssknsu = iHkkssknsu;
				// 報告保留件数
				pHkkknriArrayOut[iHkkknriLoop].hkkhrysu = iHkkhrysu;
				// 報告状況フラグ
				ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg,
							 ED203_DB_HKKJKFLG_CHUU,
							 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg ) );
				// 情報更新日時は関数内で設定

				// 報告管理情報を更新
				iRet = ZdbHkkknriED203Update( &pHkkknriArrayOut[iHkkknriLoop] );
				if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
					// ロールバック
					ZdbRollback();
					// 異常終了	LOG
printf("ZdbHkkknriUpdate error (%d)\n", iRet);
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
/*　　第１引数：ED203Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：なし														  */
/******************************************************************************/
void endFunction( ED203Env *pEnv )
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
/*　関 数 名　：ED203MakeData()												  */
/*　機能概要　：報告データ作成												  */
/*　入　　力　：															  */
/*　　第１引数：Kekka *pKekka		検査結果データ							  */
/*　出　　力　：															  */
/*　　第２引数：ED203Rec *pED203Rec	報告データ								  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int ED203MakeData(Kekka *pKekka, ED203Rec *pED203Rec)
{
	char	cTempBuff[128];

	// 検査結果データまたは報告データへのポインタがNULLの場合異常終了
	if ( pKekka == NULL || pED203Rec == NULL ) {
		return( RTN_NG );
	}

	// 報告データをスペースでクリア
	memset( pED203Rec, ED203_DATA_SPACE, sizeof(ED203Rec) );

	// 検査結果データから報告データを作成
	// ＢＭＬ受付年月日
	// [YYYYMMDD]に変換して設定
	ZbmlChgAPDate( pED203Rec->cUTKYMD, pKekka->utkymd );
	// 検体Ｎｏ．
	// 左から11桁を↓のように変換
	// (変換前)[1][2][3][4][5][6][7][8][9][10][11]
	// (変換後)[4][5][6][7][8][9]
	if ( ED203ConvNumber( pED203Rec->cKNTNO, pKekka->kntno ) == RTN_NG ) {
		return( RTN_NG );
	}
	// FILLER1
	// 空白を設定なので何もしない
	// 親項目コード
	if ( ED203CopyFromRight( pED203Rec->cOYAKMKCD,
							 pKekka->oyakmkcd,
							 sizeof( pED203Rec->cOYAKMKCD ),
							 FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// 項目コード
	if ( ED203CopyFromRight( pED203Rec->cKMKCD,
							 pKekka->kmkcd,
							 sizeof( pED203Rec->cKMKCD ),
							 FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// ＷＳコード（サンプリングコード）
	if ( ED203CopyFromRight( pED203Rec->cWSCD,
							 pKekka->smpcd,
							 sizeof( pED203Rec->cWSCD ),
							 FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// ＷＳＳＥＱ（検査ＳＥＱ）
	// 数値を文字列に変換後、右から4桁を設定。（wｼwﾜwﾙwｹwﾊwﾝwﾘwｻなし）
	sprintf( cTempBuff, "%06d", pKekka->knsseq );
	if ( ED203CopyFromRight( pED203Rec->cWSSEQ,
							 cTempBuff,
							 sizeof( pED203Rec->cWSSEQ ),
							 FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// 検査結果
	// 検査結果１or検査結果２（検査結果１優先）
	if ( pKekka->knskka1[0] != '\0' && pKekka->knskka1[0] != ED203_DATA_SPACE ) {
		// 検査結果１：右から6桁を設定（wｼwﾜwﾙwｹwﾊwﾝwﾘwｻあり、小数点削除）
		if ( ED203CopyFromRight( pED203Rec->cKNSKKA,
							 	pKekka->knskka1,
							 	sizeof( pED203Rec->cKNSKKA ),
							 	FALSE ) == RTN_NG ) {
			return( RTN_NG );
		}
	} else {
		// 検査結果２
		// 検査結果区分='0'→'*'+左2桁目から6桁目まで
		// 以外→左から6桁を設定（2バイト文字に注意する）
		if ( ED203CopyFromRight( pED203Rec->cKNSKKA,
							 	pKekka->knskka2,
							 	sizeof( pED203Rec->cKNSKKA ),
							 	TRUE ) == RTN_NG ) {
			return( RTN_NG );
		}
		if ( pKekka->knskka2kbn[0] == ED203_DATA_CHAR0 ) {
			// 検査結果区分='0'→'*'+左2桁目から6桁目まで
			pED203Rec->cKNSKKA[0] = ED203_DATA_ASTERISK;
		}
	}
	// 結果コメント
	// 右から3桁を設定
	if ( ED203CopyFromRight( pED203Rec->cKKACMT,
							 pKekka->kkacmt1,
							 sizeof( pED203Rec->cKKACMT ),
							 FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// 異常値マーク
	// 異常値区分（男、女、不明）が'4','5','6'以外であれば'*'
	if ( ( pKekka->ijkbnm != '4' && pKekka->ijkbnm != '5' && pKekka->ijkbnm != '6' ) ||
		 ( pKekka->ijkbnf != '4' && pKekka->ijkbnf != '5' && pKekka->ijkbnf != '6' ) ||
		 ( pKekka->ijkbnn != '4' && pKekka->ijkbnn != '5' && pKekka->ijkbnn != '6' ) ) {
		pED203Rec->cIJKBN = ED203_DATA_ASTERISK;
	}
	// FILLER2
	// 空白を設定なので何もしない
	// LF
	pED203Rec->cLF = ED203_FILE_LINEFEED;

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：ED203DataFileFilter()										  */
/*　機能概要　：ディレクトリ検索用のファイルフィルタ(コールバック)			  */
/*　入　　力　：															  */
/*　　第１引数：struct dirent *pDirEnt	ディレクトリエントリ				  */
/*　出　　力　：検査結果ファイル											  */
/*　復帰情報　：int															  */
/*　　　　　　		0	: 対象外ファイル									  */
/*　　　　　　		1	: 対象ファイル										  */
/******************************************************************************/
int ED203DataFileFilter(struct dirent *pDirEnt)
{
	BmlDate		today;
	char		cToday[ED203_LEN_DATESHORT + 1];

	// 文字列長チェック
	if ( strlen ( pDirEnt->d_name )  < ED203_LEN_FILEID ) {
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
/*　関 数 名　：ED203CreateFile()											  */
/*　機能概要　：報告データファイル作成										  */
/*　入　　力　：															  */
/*　　第１引数：ED203Env *pEnv		プログラム環境構造体					  */
/*　　第２引数：Kekka *pKekkaArray	検査結果情報							  */
/*　　第３引数：int iKekkaNum		検査結果情報件数						  */
/*　出　　力　：															  */
/*　　第４引数：int *piHkkssknsu	作成件数								  */
/*　　第５引数：int *piHkkhrysu		保留件数								  */
/*　　第６引数：char *pFileName		ファイル名								  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int ED203CreateFile(ED203Env *pEnv,
					Kekka *pKekkaArray,
					int iKekkaNum,
					int *piHkkssknsu,
					int *piHkkhrysu,
					char *pFileName)
{
	int				iRet;
	struct dirent	**pDirEnt;
	int				iFileCnt;
	int	 			iSeqNo;
	char			cSeqBuff[10];
	BmlDate			today;
	char			cToday[ED203_LEN_DATESHORT + 1];
	char			cFileNameTemp[PATH_MAX + 1];
	char			cFileName[PATH_MAX + 1];
	FILE *			fp;
	int				iLoop;
	ED203Rec		stED203RecTemp;
	int				iKekkaLoop;
	ED203Rec		stED203Rec;

	// 引数チェック
	if ( pEnv == NULL || pKekkaArray == NULL ||
		 piHkkssknsu == NULL || piHkkhrysu == NULL || pFileName == NULL ) {
		// 異常終了	LOG
printf("ED203CreateFile parameter is NULL\n");
		gintErrorCode = ED203_STSCODE_ERR_FR_FILE;
		return( RTN_NG );
	}

	// データファイル用ディレクトリを検索
	// フィルタにより、当日のYYYYMMDD9999で始まるファイルのみ検索
	if ( ( iFileCnt = scandir( pEnv->cDirDataFile,
							   &pDirEnt,
							   (void *)ED203DataFileFilter,
							   alphasort ) ) < 0 ) {
		// 異常終了	LOG
		gintErrorCode = ED203_STSCODE_ERR_DIR;
		return( RTN_NG );
	}

	// ファイルSEQを採番
	if ( iFileCnt == 0 ) {
		iSeqNo = 1;
	} else {
		memset( cSeqBuff, 0, sizeof( cSeqBuff ) );
		strcpy( cFileName, pDirEnt[iFileCnt - 1]->d_name );
		memcpy( cSeqBuff, &cFileName[ED203_LEN_DATESHORT],
			ED203_LEN_FILESEQNO );
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
	sprintf( cFileNameTemp, "%s/%s%04d.tmp",
			 pEnv->cDirDataFile, cToday, iSeqNo );
	sprintf( cFileName, "%s/%s%04d.dat",
			 pEnv->cDirDataFile, cToday, iSeqNo );
	sprintf( pFileName, "%s%04d.dat", cToday, iSeqNo );

	// ファイルオープン
	fp = fopen ( cFileNameTemp, "w" );
	if ( fp == NULL ) {
		// 異常終了	LOG
		gintErrorCode = ED203_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	// 結果情報を１件ずつ処理
	for ( iKekkaLoop = 0;
		  iKekkaLoop < iKekkaNum;
		  iKekkaLoop++ ) {
		// 保留かどうかチェック
		if ( pKekkaArray[iKekkaLoop].knsflg == ED203_DB_KNSFLG_HORYU ) {
			++*piHkkhrysu;
			continue;
		}

		// 結果をファイル出力形式に展開
		if ( ED203MakeData( &pKekkaArray[iKekkaLoop],
							&stED203Rec ) == RTN_NG ) {
			// 異常終了	LOG
printf("ED203MakeData error\n");
			return( RTN_NG );
		}

		// ファイル出力
		iRet = fwrite( (char *)&stED203Rec, sizeof( stED203Rec ), 1, fp);
		if ( iRet != 1 ) {
			// 異常終了	LOG
printf("fwrite error\n");
			return( RTN_NG );
		}

		// 結果修正フラグをカウントアップ（最大'9'）
		if ( pKekkaArray[iKekkaLoop].kkassflg == ED203_DATA_SPACE ) {
			pKekkaArray[iKekkaLoop].kkassflg = '0';
		} else if ( pKekkaArray[iKekkaLoop].kkassflg
					!= pKekkaArray[iKekkaLoop].kkassflg ) {
			++pKekkaArray[iKekkaLoop].kkassflg;
		}
		// 報告日時は関数内で設定

		// 検査フラグ←報告済
		pKekkaArray[iKekkaLoop].knsflg = ED203_DB_KNSFLG_DONE;

		// 情報更新日時は関数内で設定

		// 検査結果情報を更新
		iRet = ZdbKekkaED203Update( &pKekkaArray[iKekkaLoop] );
		if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
printf("ZdbKekkaED203Update error(%d)\n", iRet);
			// ロールバック
			ZdbRollback();
			// 異常終了	LOG
		}
	}

	// ファイルクローズ	
	fclose( fp );

	// ファイル拡張子名変更
	iRet = rename( cFileNameTemp, cFileName );
	if ( iRet != 0 ) {
		// 異常終了	LOG
printf("rename status:[%d]\n", iRet);
		gintErrorCode = ED203_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：sFncShmCrt()												  */
/*　機能概要　：共有メモリ生成												  */
/*　入　　力　：															  */
/*　　第１引数：ED203Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：なし														  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
static int sFncShmCrt( ED203Env *pEnv )
{
	int	 *shmData;

	// 取得
	pEnv->shm_Id = shmget( (key_t)pEnv->shm_Key,
							ED203_SHM_SIZE,
							0666 | IPC_CREAT );
	if ( pEnv->shm_Id < 0 ) {
		// 異常終了	LOG
		gintErrorCode = ED203_STSCODE_ERR_SHM_GET;
		return( RTN_NG );
	}

	// アタッチ
	shmData = ( int * ) shmat( pEnv->shm_Id, 0 , 0 );
	if ( shmData == ( int * )-1 ) {
		// 異常終了	LOG
		gintErrorCode = ED203_STSCODE_ERR_SHM_AT;
		return( RTN_NG );
	}
loging ( "stocker : 共有メモリ[CRT] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n",
		 pEnv->shm_Key, pEnv->shm_Id, *shmData, shmData );

	// 値設定
	*shmData = 0;

	// デタッチ
	if ( shmdt( shmData ) == -1 ) {
		// 異常終了	LOG
		gintErrorCode = ED203_STSCODE_ERR_SHM_DT;
		return( RTN_NG );
	}

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：sFncShmGet()												  */
/*　機能概要　：共有メモリ取得												  */
/*　入　　力　：															  */
/*　　第１引数：ED203Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　　第２引数：int *pshmData		値										  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
static int sFncShmGet( ED203Env *pEnv, int *pshmData )
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
		gintErrorCode = ED203_STSCODE_ERR_SHM_AT;
		return( RTN_NG );
	}

	// 値設定
	*pshmData = *shmData;

loging ( "stocker : 共有メモリ[GET] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n",
		 pEnv->shm_Key, pEnv->shm_Id, *shmData, shmData );
	// デタッチ
	if ( shmdt( shmData ) == -1 ) {
		// 異常終了	LOG
		gintErrorCode = ED203_STSCODE_ERR_SHM_DT;
		return( RTN_NG );
	}

	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：sFncShmDel()												  */
/*　機能概要　：共有メモリ削除												  */
/*　入　　力　：															  */
/*　　第１引数：ED203Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
static int sFncShmDel( ED203Env *pEnv )
{
	int	 *shmData;

loging ( "%s : 共有メモリ[DEL] shmKey[%d]-ID[%d]\n",
		 MYAPP_APP_NAME, pEnv->shm_Key, pEnv->shm_Id);
	// 削除
	if ( shmctl( pEnv->shm_Id, IPC_RMID, NULL) < 0 ) {
		// 異常終了	LOG
		gintErrorCode = ED203_STSCODE_ERR_SHM_DEL;
		return( RTN_NG );
	}
	return( RTN_OK );
}

/******************************************************************************/
/*　関 数 名　：_sFncEnvDip()												  */
/*　機能概要　：プログラム環境変数出力関数【トレース用】					  */
/*　入　　力　：															  */
/*　　第１引数：ED203Env *pEnv		プログラム環境構造体					  */
/*　出　　力　：															  */
/*　復帰情報　：無し														  */
/******************************************************************************/
static void _sFncEnvDip( ED203Env *pEnv )
{
//#if defined ( _TRACE )
	loging( "########## ED203 - _sFncEnvDip ##########\n" );
	loging( "\t%s : [%s]\n", ED203_PRM_DBNAME,		 pEnv->cDBName );
	loging( "\t%s : [%s]\n", ED203_PRM_DBUSER,		 pEnv->cDBUser );
	loging( "\t%s : [%s]\n", ED203_PRM_DBPAWD,		 pEnv->cDBPawd );
	loging( "\t%s : [%s]\n", ED203_PRM_DIR_DATAFILE,   pEnv->cDirDataFile );
	loging( "\t%s : [%s]\n", ED203_PRM_SLEEP_SEC,	  pEnv->iSleepSec );
	loging( "\t%s : [%s]\n", ED203_PRM_SHM_KEY,	pEnv->shm_Key );
	loging( "\t%s : [%s]\n", ED203_PRM_FILE_DBG,	pEnv->cDebugLogName );
	loging( "\t%s : [%s]\n", ED203_PRM_FILE_TR,	pEnv->cTraceLogName );
	loging( "\t%s : [%s]\n", ED203_PRM_FILE_ACS,	pEnv->cAccessLogName );
	loging( "\t%s : [%s]\n", ED203_PRM_FILE_ERR,	pEnv->cErrorLogName );
	loging( "\t%s : [%s]\n", ED203_PRM_UP_ID,		pEnv->cUpdateId );
	loging( "\t%s : [%s]\n", ED203_PRM_UP_NM,		pEnv->cUpdateName );
	loging( "\t%s : [%s]\n", ED203_PRM_PROC_MD,	pEnv->proc_mode );
	loging( "########## ED203 - _sFncEnvDip ##########\n" );
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
	ED203Env	stEnv;

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


