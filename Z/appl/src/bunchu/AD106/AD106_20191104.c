/********************************************************************/
/*																	*/
/*		ＢＭＬ様向け検査システム									*/
/*																	*/
/*		システム名	：次世代システム								*/
/*		ファイル名	：AD105Buntekai.c								*/
/*		概要		：分注情報展開処理								*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	作成日			名前			修正内容				*/
/* ----------------------------------------------------------------	*/
/*  1.00	2006/01/19		E.Osada			Create					*/
/********************************************************************/

/********************************************************************/
/*	インクルード宣言												*/
/********************************************************************/
#include "AD106.h"

/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/


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
BUNCHU_STSCODE	gintErrorCode ;
static	char	*gpToken ;		//sFncTrFileToken用静的ポインタ
struct stcLogMember      gstLogMem ;
iconv_t     G_ic;
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
initFunction( argc, argv, pEnv )
int					 argc ;
char				*argv[] ;
struct bunchuEnv	*pEnv ;
{
	char	 cPrmBuf[256] ;
	char    *lc_login ;

	/***
	 ***	初期化	
	 ***/
	//	エラーステータス変更
	gintErrorCode = 0 ;
	//	プログラム環境変数初期化
	memset ( pEnv , '\0', sizeof ( struct bunchuEnv ) ) ;

	/***
	 ***	ログオープン
	 ***/
	if( ZbmlOpenLog( MYAPP_LOGINIFILE ) != 0 ) {
		return( -1 );
	}

    //  ログ情報初期設定
    memset ( &gstLogMem, '\0', sizeof ( gstLogMem ) ) ;
    if ( ( lc_login = getenv( "LOGNAME" ) ) != NULL ) {
        strcpy ( gstLogMem.pcLoginId, lc_login ) ;
    }
    strcpy ( gstLogMem.pcAppName, MYAPP_APP_NAME ) ;

    //  開始ログ出力
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                 "プログラム起動" ) ;

	/***
	 ***	引数チェック	
	 ***/
	//	引数数チェック	
	if ( argc != 2 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_USEGE ;
        sFncPutLog ( TRCKIND_ERROR, __FILE__, "initFunction", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "コマンドパラメータに誤りがあります" ) ;
		return ( -1 ) ;
	}

	/***
	 ***	パラメータファイル情報退避
	 ***/
	//	パラメータファイル名退避
	pEnv->pcFielNamePRM = argv[1] ;

	//	パラメータファイルオープン
	pEnv->bp = ZbmlPrmOpen ( pEnv->pcFielNamePRM ) ;
	if ( pEnv->bp == NULL ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_FILE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZZbmlPrmOpen", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"パラメータファイルのオープンに失敗しました[%s]", pEnv->pcFielNamePRM ) ;
		return ( -1 ) ;
	}

	//	分注情報ディレクトリ
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_DIR_BUNCHU,
						pEnv->cDirBunchu ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//	分注情報ディレクトリ(既読)
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_DIR_BUNCHU_OK,
						pEnv->cDirBunchuOK ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//	分注情報ディレクトリ(エラー)
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_DIR_BUNCHU_NG,
						pEnv->cDirBunchuNG ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	// トレーNo情報ファイル格納ディレクト
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_DIR_TRAY,
						pEnv->cDirTryinfo ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//トレーNo情報ファイル格納ディレクトリ(既読)
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_DIR_TRAY_OK,
						pEnv->cDirTryinfoOK ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//トレーNo情報ファイル格納ディレクトリ(エラー)
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_DIR_TRAY_NG,
						pEnv->cDirTryinfoNG ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//	ログディレクトリ
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_DIR_LOG, 
						pEnv->cDirLog ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//	デバッグログファイル
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_FILE_DBG, 
						pEnv->cDebugLogName ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//	トレースログファイル
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_FILE_TR, 
						pEnv->cTraceLogName ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//	アクセスログファイル
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_FILE_ACS, 
						pEnv->cAccessLogName ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//	エラーログファイル
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_FILE_ERR, 
						pEnv->cErrorLogName ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//	共有メモリキー取得
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_SHM_KEY, cPrmBuf ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	pEnv->shm_Key = atoi ( cPrmBuf ) ;
	//	SLEEPSEC取得
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_SLEEP_SEC, cPrmBuf ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	pEnv->sleep_Sec= atoi ( cPrmBuf ) ;
	//更新者ID
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_UP_ID, 
						pEnv->cUpdateId ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//更新者名
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_UP_NM, 
						pEnv->cUpdateName ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//実行モード
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_PROC_MD, cPrmBuf ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	pEnv->proc_mode= atoi ( cPrmBuf ) ;
	//DB名称
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_DB,
						pEnv->sDbName ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//DBログインID
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_UID,
						pEnv->sDbUser ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//DBパスワード
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_PWD,
						pEnv->sDbPswd ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//過渡期ラボコード
	if( ZbmlPrmGetVal( pEnv->bp, BUNCHU_PRM_LBCD,
						pEnv->sLbcd ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//過渡期サテライトコード
	if( ZbmlPrmGetVal( pEnv->bp, BUNCHU_PRM_STCD,
						pEnv->sSateid ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//	パラメータファイルクローズ	
	ZbmlPrmClose ( pEnv->bp ) ;

	/***
	 ***	共有メモリ生成	
	 ***/
	if ( sFncShmCrt ( pEnv ) < 0 ) {
		return ( -1 ) ;
	}

	//トレースログ
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "initFunction", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                 "End Function" ) ;
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
mainFunction( pEnv )
struct bunchuEnv	*pEnv ;
{

	int				  li_idx, ret;
	int				  li_stopFlg ;

	DIR				 *lt_dp ;
	struct dirent	**lpst_dirBuf ;

	int				  li_fileCnt, iLen ;
	char			  lc_fileName[1024] ;
	char			  buf[1024] ;
	struct stat		  lst_statBuf ;
	char	sFileOK[1024], sFileNG[1024];
	char	sDttm[128];

	int		iSeqCnt, iSeqCnt1;
	Flbun	  lst_trInfo ;
	int		iRet;

	//トレースログ
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "Start Function");

    //if( ret = ZdbConnect( "labokns", "nxtgene", "nxtgene" ) ) {
    if( ret = ZdbConnect( pEnv->sDbName, pEnv->sDbUser, pEnv->sDbPswd ) ) {
        printf("DB connect error (%d)", ret);
        return( -1 );
    }

	G_ic = iconv_open( "EUC-JP", "SHIFT-JIS" );

	/***
	 ***	分注情報ディレクトリ監視	
	 ***		永久ループ
	 ***		停止コマンドで終了
	 ***/
	iSeqCnt = 0;
	iSeqCnt1 = 0;
	while ( 1 ) {

		/***
		 *** ファイル名取得
		 ***/
		if ( ( li_fileCnt = scandir ( pEnv->cDirBunchu, 
									  &lpst_dirBuf,
									  (void*)sFncFileFillter,
					   				  alphasort ) ) < 0 ) {
			//	異常終了	LOG
			gintErrorCode = BUNCHU_STSCODE_ERR_DIR;
			return ( -1 ) ;
		}
		li_idx = 0 ;
		while ( li_idx < li_fileCnt ) {
			sprintf ( lc_fileName, "%s/%s", pEnv->cDirBunchu, lpst_dirBuf[li_idx]->d_name ) ;

    		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"File GET [%s]", lpst_dirBuf[li_idx]->d_name );
			if ( stat ( lc_fileName, &lst_statBuf ) < 0 ) {
				//	異常終了	LOG
				gintErrorCode = BUNCHU_STSCODE_ERR_DIR;
				return ( -1 ) ;
			}
			memset(sFileOK, 0, sizeof(sFileOK));
			memset(sFileNG, 0, sizeof(sFileNG));
			//通常ファイルのみ処理を行う
			if( iSeqCnt == 9999 ) iSeqCnt = 0;
			if ( S_ISREG ( lst_statBuf.st_mode ) ) {
				if ( (iRet = sFncTrFileRead ( pEnv, lc_fileName, &lst_trInfo, &iSeqCnt, &iSeqCnt1 )) < 0 ) {
					sprintf(sFileOK, "%s/%s", pEnv->cDirBunchuOK, lpst_dirBuf[li_idx]->d_name);
				} else {
					sprintf(sFileOK, "%s/%s", pEnv->cDirBunchuOK, lpst_dirBuf[li_idx]->d_name);
				}
				//	解放
				free ( lpst_dirBuf[li_idx] ) ;
				// ファイル移動
				if( memcmp(lpst_dirBuf[li_idx]->d_name, "CHK", 3) ) {
					if( rename( lc_fileName, sFileOK) < 0 ) {
						printf("rename error %s -> %s\n", lc_fileName, sFileOK);
						return( -1 );
					}
				} else if( iRet == 0) {
					sprintf(sFileOK, "%s/%s", pEnv->cDirTryinfo, lpst_dirBuf[li_idx]->d_name);
					if( rename( lc_fileName, sFileOK) < 0 ) {
						printf("rename error %s -> %s\n", lc_fileName, sFileOK);
						return( -1 );
					}
					memset(buf, 0, sizeof(buf));
					iLen = strlen(sFileOK) - 3;
					strcpy(buf, sFileOK);
					memcpy(&buf[iLen], "dat", 3);
					if( rename( sFileOK, buf) < 0 ) {
						printf("rename error %s -> %s\n", lc_fileName, sFileOK);
						return( -1 );
					}
				}
			}
			/***
		 	*** 停止コマンド確認
		 	***/
			if ( sFncShmGet ( pEnv, &li_stopFlg ) < 0 ) {
				return ( -1 ) ;
			}
			if ( li_stopFlg == 1 ) {
				break ;
			}
			li_idx ++ ;
		}

		if ( li_stopFlg == 1 ) {
			break ;
		} else {
			if ( sFncShmGet ( pEnv, &li_stopFlg ) < 0 ) {
				return ( -1 ) ;
			}
			if ( li_stopFlg == 1 ) {
				break ;
			}
		}
		/***
		 *** スリープ
		 ***/
		sleep ( pEnv->sleep_Sec ) ;
	}

	iconv_close( G_ic );

	//トレースログ
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function");
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
endFunction( pEnv )
struct bunchuEnv	*pEnv ;
{
	//トレースログ
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "endFunction", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "Start Function");
	/***
	 ***	共有メモリ削除	
	 ***/
	if ( sFncShmDel ( pEnv ) < 0 ) {
		return ;
	}
	
	//トレースログ
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "endFunction", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function");
	return ;
}
void
nowdateget( char *sysdate, char *systime )
{
        struct tm       *newtime ;
        long    ltime ;

        time( &ltime) ;
        newtime = localtime( &ltime ) ;
        sprintf( sysdate, "%04d%02d%02d", newtime->tm_year+1900,
                                newtime->tm_mon+1, newtime->tm_mday ) ;
        sprintf( systime, "%02d%02d%02d", newtime->tm_hour,
                                newtime->tm_min, newtime->tm_sec ) ;

        return ;
}
void
nowdateget1( char *sysdate )
{
        struct tm       *newtime ;
        long    ltime ;

        time( &ltime) ;
        newtime = localtime( &ltime ) ;
        sprintf( sysdate, "%04d-%02d-%02d %02d:%02d:%02d",
                          newtime->tm_year+1900, newtime->tm_mon+1, newtime->tm_mday,
                          newtime->tm_hour, newtime->tm_min, newtime->tm_sec ) ;
        return ;
}
/******************************************************************************/
/*  関 数 名　：dBunchu_ins()				 								  */
/*  機能概要　：分注情報作成処理											  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *					分注情報							  */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
/******************************************************************************/
int
dBunchu_ins(pst_Env, lc_recBuf, strKenPos, iKenPos, sFLname, iFLcnt)
struct bunchuEnv    *pst_Env;
char	*lc_recBuf;
TRAY **strKenPos;
int		*iKenPos;
char	*sFLname;
int		iFLcnt;
{
	FILE	*fp;
	Flbun *pBunchu;			//分注結果情報ファイル構造体
	Kanjya	strKanjyaTB;	//患者情報テーブルKEY構造体
	Kanjya	*pKanjya = NULL;		//患者情報テーブル格納構造体
	Irai	strIraiTB;		//依頼情報テーブルKEY構造体
	Irai	*pIrai = NULL;			//依頼情報テーブル格納構造体
	char	buf[1024], buf1[1024], buf2[128];		//ワーク
	BmlDate	today;
	char	sDay[20], sysdate[128], systime[128];
	char	*pKmkCd, *pKmkCd1;
	int		i, num, iIrai, j, iOrder, cnt, iHit;
	long	ret;
	char	sWknsgrp[17];
	char ialloc, iPoint;
	int		iWs, iEda;
	int		iSkipFlg;
	char	sWork[10];
	char	sWork1[10];
	int		iJidoFlg;
	int 	iOldFlg;
	char	sKjNo[10];
	int		iOya;
	int		iOdrMkFlg;

	//トレースログ
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "Start Function");

	pKmkCd = (lc_recBuf + BUNCHU_KMK_ADR);
	pBunchu = (Flbun *)lc_recBuf;

	//ファイルサイズチェック
	if( strlen(lc_recBuf) != BUNCHU_FILE_SIZE ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"分注情報ファイルエラー(サイズチェック) %d", strlen(lc_recBuf) );
		sFuncPutErrlist(pst_Env, sFLname, iFLcnt, "", "", "", "",
				"", "分注情報ファイルエラー(サイズチェック)[ %d ]", strlen(lc_recBuf));
		return( -1 );
	}

	//分注ファイル識別子チェック(ヘッダーレコード)
	if( !memcmp(pBunchu->sDataSybt, BUNCHU_SYBT_HED, 2) ) {
		//トレースログ
    	sFncPutLog ( TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function(ヘッダーレコード)");
		return( 1 );
	}
	//分注ファイル識別子チェック(終了レコード)
	if( !memcmp(pBunchu->sDataSybt, BUNCHU_SYBT_STP, 2) ) {
		//トレースログ
    	sFncPutLog ( TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function(終了レコード)");
		return( 1 );
	}
	//分注ファイル識別子チェック
	if( !(!memcmp(pBunchu->sDataSybt, BUNCHU_SYBT, 2) || 
		!memcmp(pBunchu->sDataSybt, BUNCHU_SYBT_END, 2)) ) {
		memset(buf, 0, sizeof(buf));
		memcpy(buf, pBunchu->sDataSybt, 2);
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"分注情報ファイルエラー(識別子) %s", buf);
		sFuncPutErrlist(pst_Env, sFLname, iFLcnt, "", "", "", "",
				"", "分注情報ファイルエラー(識別子)[%s]", buf);
		return( -1 );
	}
	
	//分注ファイル識別子チェック(分注END)
	if( !memcmp(pBunchu->sDataSybt, BUNCHU_SYBT_END, 2) ) {

		//トレースログ
    	sFncPutLog ( TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function(分注END)");
		return( 1 );
	}

		//トレーIDがスペースの場合は無条件に分注展開処理にまわす
	if( !memcmp(pBunchu->sRackId, "        ", sizeof(pBunchu->sRackId)) ) {
		return( 2 );
	}
	iSkipFlg = ialloc = 0;

	memset(&strIraiTB, 0, sizeof(Irai));
	memset(&strKanjyaTB, 0, sizeof(Kanjya));
	//BML受付年月日 YYYYMMDD → YYYY-MM-DDに変換
	memcpy(buf, pBunchu->sUkebiBML, sizeof(pBunchu->sUkebiBML));
	sprintf(buf1, "%4.4s-%2.2s-%2.2s", buf, &buf[4],&buf[6]);
	strcpy(strIraiTB.utkymd, buf1);
	strcpy(strKanjyaTB.utkymd, buf1);
	//依頼書No
	if( pst_Env->proc_mode ) {
		//次世代
		memcpy(strIraiTB.irino, pBunchu->sIraiNo, sizeof(pBunchu->sIraiNo));
		memcpy(strKanjyaTB.irino, pBunchu->sIraiNo, sizeof(pBunchu->sIraiNo));
	} else {
		//過渡期
		memset(buf, 0, sizeof(buf));
		memset(buf1, 0, sizeof(buf1));
		memcpy(buf, pBunchu->sIraiNo, sizeof(pBunchu->sIraiNo));
		sprintf(buf1,"00%-3.3s%-6.6s", &buf[0], &buf[5]);
		strcpy(strIraiTB.irino, buf1);
		strcpy(strKanjyaTB.irino, buf1);
	}

	//患者情報確認
	if( (ret = ABunKnjSel(&strKanjyaTB, &pKanjya, &cnt)) < 0 ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"SELECT KANJYA[SQLCODE=%d]", ret ) ;
		ZdbRollback();
		return( -1 );
	}
	if( cnt == 0 ) {
		//患者情報が無い場合はスキップ
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"患者情報 NOT FOUND BML受付日(%s) 依頼書No(%s)", strIraiTB.utkymd, strIraiTB.irino ) ;
		sFuncPutErrlist(pst_Env, sFLname, iFLcnt, "", strKanjyaTB.utkymd, 
			"", strIraiTB.irino, "", "患者情報無し");
		return 2;
	}
	
	//属性世代No取得
	strIraiTB.zssdino = pKanjya->zssdino;

	//依頼情報テーブル取得
	strcpy(strIraiTB.kmkcd, buf2);
	if( (ret = ABunIriSel(&strIraiTB, &pIrai, &iIrai)) < 0 ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"SELECT IRAI[SQLCODE=%d]", ret ) ;
		ZdbRollback();
		if( pKanjya != NULL ) {
			ZbmlFree(pKanjya);
			pKanjya = NULL;
		}
		return( -1 );
	}
	if( iIrai == 0 ) {
		//依頼情報が無い
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"依頼情報 NOT FOUND BML受付日(%s) 依頼書No(%s) 属性世代No(%d) 項目コード(%s)",
			strIraiTB.utkymd, strIraiTB.irino, strIraiTB.zssdino, strIraiTB.kmkcd ) ;
		sFuncPutErrlist(pst_Env, sFLname, iFLcnt, "", "", 
			strIraiTB.kntno, strIraiTB.irino, buf2, "依頼情報無し");
		ZdbRollback();
		if( pKanjya != NULL ) {
			ZbmlFree(pKanjya);
			pKanjya = NULL;
		}
		return( 2 );
	}

	if( pIrai != NULL ) {
		ZbmlFree(pIrai);
		pIrai = NULL;
	}
	if( pKanjya != NULL ) {
		ZbmlFree(pKanjya);
		pKanjya = NULL;
	}

	//コミット
	ZdbCommit();

	//トレースログ
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function");

	return(0);
}
int
BunFilePut(pst_Env, sBunTenFl, lc_recBuf)
struct bunchuEnv    *pst_Env;
char	*sBunTenFl;
char	*lc_recBuf;
{
	FILE	*fp;

	if( (fp = fopen(sBunTenFl,"a")) == NULL ) {
		return -1;
	}

	if( fputs(lc_recBuf, fp) == EOF ) {
		return -1;
	}

	fclose(fp);

	return(0);
}
/******************************************************************************/
/*  関 数 名　：sFncTrFileRead()			 								  */
/*  機能概要　：分注結果情報読込							  	 			  */
/*	特記事項  ：第２引数はfree												  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct bunchuEnv *   	プログラム環境構造体		 	      */
/*　 第２引数 ：char *  	 			分注結果情報ファイル名	 			  */
/*　 第３引数 ：Flbun *  	 			分注結果情報情報格納構造体			  */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
/******************************************************************************/
static	int
sFncTrFileRead ( pst_Env, pc_trFileName, pst_trInfo, iSeqCnt, iSeqCnt1 )
struct bunchuEnv	*pst_Env ;
char				*pc_trFileName ;
Flbun  		*pst_trInfo ;
int			*iSeqCnt;
int			*iSeqCnt1;
{
	FILE	*lfp ;
	char	 lc_recBuf[BUNCHU_RECV_RECSIZE+1] ;
	char	sTrFileName[1024];
	char	*lpc_p ;
	char	 lcbuf[256] ;
	int		 li_idx, iRet, i, ilen, iRecCnt;
	TRAY *strKenPos;
	int		iKenPos;
	int 	iLine;
	char	sDttm[128];
	Flbun	*strBun;
	char	sTray[11], sTray1[11], sTray2[11];
	int		iErrFlg;
	int		iSkip;
	char    sSysdate[128], sSystime[128];
	char	sBunTenFl[BUNCHU_FILE_SIZE];
	char	sBunTenFl1[BUNCHU_FILE_SIZE];
	char	sTmpFl[BUNCHU_FILE_SIZE];
	char	sTmpFl1[BUNCHU_FILE_SIZE];
	char	sNgFl[BUNCHU_FILE_SIZE];
	char	sSpFl[BUNCHU_FILE_SIZE];
	char	sSpFl1[BUNCHU_FILE_SIZE];
	int		iSpCnt;
	int 	iSpaceFlg;

	//トレースログ
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "sFncTrFileRead", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "Start Function filename=%s", pc_trFileName);

    memset(sDttm, 0, sizeof(sDttm));
    nowdateget1( sDttm );
    sFncPutLog ( TRCKIND_OPT, "", "", 0,
         EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
         "    START(%s) 【%s】", sDttm, pc_trFileName);


	//	ファイルオープン	
	lfp  = fopen ( pc_trFileName, "r" ) ;
	if ( lfp == NULL ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_FR_FILE ;
		return ( -1 ) ;
	}

	memset(sTrFileName, 0, sizeof(sTrFileName));
	ilen = strlen(pc_trFileName);
	for( i=ilen; i >= 0 ;--i ) {
		if( pc_trFileName[i] == '/' ) {
			++i;
			memcpy(sTrFileName, &pc_trFileName[i], ilen - i);
			break;
		}
	}
	strKenPos = NULL;
	iKenPos = iLine = 0;
	memset(lc_recBuf, 0, BUNCHU_FILE_SIZE);

	memset(sSysdate, 0, sizeof(sSysdate));
	memset(sSystime, 0, sizeof(sSystime));
	nowdateget(sSysdate, sSystime);
	memset(sNgFl, 0, sizeof(sNgFl));
	sprintf(sNgFl, "%s/NG%s.dat", pst_Env->cDirBunchuNG, sSysdate);
	iRecCnt = 0;
	iErrFlg = 0;
	iSkip = 0;
	iLine = 0;
	iSpCnt = 0;
	*iSeqCnt1 += 1;
	if( *iSeqCnt1 > 99999 ) *iSeqCnt1 = 1;
	memset(sSpFl, 0, sizeof(sSpFl));
	memset(sSpFl1, 0, sizeof(sSpFl1));
	memset(sSysdate, 0, sizeof(sSysdate));
	memset(sSystime, 0, sizeof(sSystime));
	nowdateget(sSysdate, sSystime);
	sprintf(sSpFl, "%s/HIBUN%s%s%04d.tmp", pst_Env->cDirTryinfo, sSysdate, sSystime, *iSeqCnt1);
	sprintf(sSpFl1, "%s/HIBUN%s%s%04d.dat", pst_Env->cDirTryinfo, sSysdate, sSystime, *iSeqCnt1);
	//	読み込み
	memset(sTray,0,sizeof(sTray));
	memset(sTray1,0,sizeof(sTray1));
	while ( fgets ( lc_recBuf, sizeof ( lc_recBuf ), lfp ) != NULL ) {
		strBun = (Flbun *)lc_recBuf;
		if( iLine == 0 ) {
			memset(sBunTenFl, 0, sizeof(sBunTenFl));
			memset(sTmpFl, 0, sizeof(sTmpFl));
			memset(sTmpFl1, 0, sizeof(sTmpFl1));
			memset(sSysdate, 0, sizeof(sSysdate));
			memset(sSystime, 0, sizeof(sSystime));
			nowdateget(sSysdate, sSystime);
			*iSeqCnt += 1;
			sprintf(sBunTenFl, "CHK%s%s%04d.tmp", sSysdate, sSystime, *iSeqCnt);
			sprintf(sBunTenFl1, "CHK%s%s%04d.dat", sSysdate, sSystime, *iSeqCnt);
			sprintf(sTmpFl, "%s/%s", pst_Env->cDirBunchu, sBunTenFl);
		}
		iLine++;
		if( memcmp(strBun->sRackId, "        ", sizeof(strBun->sRackId)) ) {
			memset(sTray2, 0, sizeof(sTray2));
			memcpy(sTray2, strBun->sRackId, sizeof(strBun->sRackId));
			if( (iErrFlg == 1) && !memcmp(sTray, sTray2, sizeof(strBun->sRackId)) ) {
				if( memcmp(sTrFileName, "CHK", 3) ) {
					if( BunFilePut(pst_Env, sTmpFl, lc_recBuf) < 0 ) {
						return( -1 );
					}
					iSkip = 1;
				}
				continue;
			}
		}
		if( (iRet = dBunchu_ins(pst_Env, lc_recBuf, &strKenPos, &iKenPos, sTrFileName, iLine)) < 0 ) {
			if( BunFilePut(pst_Env, sNgFl, lc_recBuf) < 0 ) {
				return( -1 );
			}
			return( iRet );
		}

		//ヘッダレコード及びトレーIDがスペースの場合は無条件に分注展開処理にまわす
		if( (iRet == 1) || !memcmp(strBun->sRackId, "        ", sizeof(strBun->sRackId)) ) {
			if( memcmp(sTrFileName, "CHK", 3) ) {
				if( BunFilePut(pst_Env, sTmpFl, lc_recBuf) < 0 ) {
					return( -1 );
				}
			}
			iSkip = 1;
			continue;
		}

		strBun = (Flbun *)lc_recBuf;
		memset(sTray1, 0, sizeof(sTray1));
		memcpy(sTray1, strBun->sRackId, sizeof(strBun->sRackId));
		if( iSpaceFlg && (strlen(sTray) != 0) && memcmp(sTray, sTray1, sizeof(strBun->sRackId)) ) {
			memset(sTmpFl1, 0, sizeof(sTmpFl1));
			//ファイル移動
			if( iErrFlg == 0 ) {
				if( memcmp(sTrFileName, "CHK", 3) ) {
					sprintf(sTmpFl1, "%s/%s", pst_Env->cDirTryinfo, sBunTenFl);
					rename(sTmpFl, sTmpFl1);
					memset(sTmpFl, 0, sizeof(sTmpFl));
					memset(sTmpFl1, 0, sizeof(sTmpFl1));
					sprintf(sTmpFl, "%s/%s", pst_Env->cDirTryinfo, sBunTenFl);
					sprintf(sTmpFl1, "%s/%s", pst_Env->cDirTryinfo, sBunTenFl1);
					//2007-04-06 rename時にスリープ
					sleep ( 1 ) ;
					rename(sTmpFl, sTmpFl1);
				}
			}
			memset(sBunTenFl, 0, sizeof(sBunTenFl));
			memset(sTmpFl, 0, sizeof(sTmpFl));
			memset(sSysdate, 0, sizeof(sSysdate));
			memset(sSystime, 0, sizeof(sSystime));
			nowdateget(sSysdate, sSystime);
			*iSeqCnt += 1;
			sprintf(sBunTenFl, "CHK%s%s%04d.tmp", sSysdate, sSystime, *iSeqCnt);
			sprintf(sBunTenFl1, "CHK%s%s%04d.dat", sSysdate, sSystime, *iSeqCnt);
			sprintf(sTmpFl, "%s/%s", pst_Env->cDirBunchu, sBunTenFl);
			//memcpy(sTray1, strBun->sRackId, sizeof(strBun->sRackId));
			iErrFlg = 0;
			iSkip = 0;
			memcpy(sTray, strBun->sRackId, sizeof(strBun->sRackId));
		}
		if( strlen(sTray) == 0 ) {
			memcpy(sTray, strBun->sRackId, sizeof(strBun->sRackId));
		}
		if( memcmp(sTrFileName, "CHK", 3) ) {
			if( BunFilePut(pst_Env, sTmpFl, lc_recBuf) < 0 ) {
				return( -1 );
			}
		}
		iSkip = 1;
		if( iRet == 0 ) {
			iErrFlg = 0;
		} else {
			iErrFlg = 1;
		}
		++iRecCnt;
		memset(lc_recBuf, 0, BUNCHU_FILE_SIZE+1);
	}
	if( iSkip && !iErrFlg ) {
		if( memcmp(sTrFileName, "CHK", 3) ) {
			sprintf(sTmpFl1, "%s/%s", pst_Env->cDirTryinfo, sBunTenFl);
			rename(sTmpFl, sTmpFl1);
			memset(sTmpFl, 0, sizeof(sTmpFl));
			memset(sTmpFl1, 0, sizeof(sTmpFl1));
			sprintf(sTmpFl, "%s/%s", pst_Env->cDirTryinfo, sBunTenFl);
			sprintf(sTmpFl1, "%s/%s", pst_Env->cDirTryinfo, sBunTenFl1);
			//2007-04-06 rename時にスリープ
			sleep ( 1 ) ;
			rename(sTmpFl, sTmpFl1);
		}
	}
	if( iSpCnt ) {
		rename(sSpFl, sSpFl1);
	}
	//	ファイルクローズ	
	fclose ( lfp ) ;

    memset(sDttm, 0, sizeof(sDttm));
    nowdateget1( sDttm );
    sFncPutLog ( TRCKIND_OPT, "", "", 0,
         EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
         "    END(%s)   【%s RECORD No %d 】", sDttm, sTrFileName, iRecCnt);

	//トレースログ
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "sFncTrFileRead", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function");

	return ( iErrFlg );
}
/******************************************************************************/
/*  関 数 名　：sFncShmCrt()				 								  */
/*  機能概要　：共有メモリ生成								  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct stockerEnv *   	プログラム環境構造体		 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
/******************************************************************************/
static	char*
sFncTrFileToken ( pString, pBuf )
char	*pString ;
char	*pBuf ;
{
	char	*p ;
	int		 liLen ;
	int		 liIdx ;

	*pBuf = '\0' ;
	if ( pString == NULL ) {
		p = gpToken ;	
	}
	else {
		p = pString ;	
	}
//loging ( "%s\n", p ) ;
/***
	if ( ( liLen = strlen ( p ) ) <= 0 ) {
		return ( NULL ) ;
	}
***/
	if (  *p == '\0' || *p == '\n' || *p == '\r' ) {
		return ( NULL ) ;
	}

	liIdx = 0 ;	
	while ( 1 ) {
	//fprintf ( stderr, "%c\n", *(p+liIdx) ) ;
		if ( *(p+liIdx) == ','  || 
			 *(p+liIdx) == '\0' || 
			 *(p+liIdx) == '\n' || 
			 *(p+liIdx) == '\r'  ) {
			break ;
		}	
		liIdx ++ ;
	}
	if ( liIdx > 0 ) {
		memset ( pBuf, '\0', liIdx + 1 ) ;
		memcpy ( pBuf, p, liIdx ) ;
	}
	if ( *(p+liIdx) == ',' ) {
		gpToken =  p + liIdx + 1 ;
	} 
	else {
		gpToken =  p + liIdx ;
	}
	return ( gpToken ) ;
}

/******************************************************************************/
/*  関 数 名　：sFncShmCrt()				 								  */
/*  機能概要　：共有メモリ生成								  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct stockerEnv *   	プログラム環境構造体		 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
/******************************************************************************/
static int
sFncShmCrt ( pEnv )
struct bunchuEnv	*pEnv ;
{
	int		*shmData ;

	//	取得
	pEnv->shm_Id = shmget ( (key_t)pEnv->shm_Key, 
							BUNCHU_SHM_SIZE, 
							0666 | IPC_CREAT ) ;
	if ( pEnv->shm_Id < 0 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_SHM_GET ;
		return ( -1 ) ;
	}

	//	アタッチ	
	shmData = ( int * ) shmat ( pEnv->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_SHM_AT ;
		return ( -1 ) ;
	}
loging ( "stocker : 共有メモリ[CRT] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n", pEnv->shm_Key, pEnv->shm_Id, *shmData, shmData ) ;

	//	値設定	
	*shmData = 0 ;

	//	デタッチ	
	if ( shmdt ( shmData ) == -1 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_SHM_DT ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*  関 数 名　：sFncShmGet()				 								  */
/*  機能概要　：共有メモリ取得								  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct stockerEnv *   	プログラム環境構造体。		 	      */
/*　 第２引数 ：int *   				値							 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
/******************************************************************************/
static int
sFncShmGet ( pEnv, pshmData )
struct bunchuEnv	*pEnv ;
int					*pshmData ;
{
	int		*shmData ;

	//	アタッチ	
	shmData = ( int * ) shmat ( pEnv->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_SHM_AT ;
		return ( -1 ) ;
	}

	//	値設定	
	*pshmData = *shmData ;

loging ( "stocker : 共有メモリ[GET] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n", pEnv->shm_Key, pEnv->shm_Id, *shmData, shmData ) ;
	//	デタッチ	
	if ( shmdt ( shmData ) == -1 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_SHM_DT ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*  関 数 名　：sFncShmDel()				 								  */
/*  機能概要　：共有メモリ削除								  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct stockerEnv *   	プログラム環境構造体。		 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
/******************************************************************************/
static int
sFncShmDel ( pEnv )
struct bunchuEnv	*pEnv ;
{
	int		*shmData ;

loging ( "bunchu : 共有メモリ[DEL] shmKey[%d]-ID[%d]\n", pEnv->shm_Key, pEnv->shm_Id) ;
	//	削除	
	if ( shmctl ( pEnv->shm_Id, IPC_RMID, NULL) < 0 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_SHM_DEL ;
		return ( -1 ) ;
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
		//識別チェック("BUN")
		if ( memcmp ( pdirEnt->d_name, 
					  BUNCHU_RECV_KIND, 
					  strlen ( BUNCHU_RECV_KIND ) ) == 0 ) {
			return ( 1 ) ;
		}
		//識別チェック("CHK")
		if ( memcmp ( pdirEnt->d_name, 
					  BUNCHU_RECV_KIND1, 
					  strlen ( BUNCHU_RECV_KIND ) ) == 0 ) {
			return ( 1 ) ;
		}
		//識別チェック("HIBUN")
		if ( memcmp ( pdirEnt->d_name, 
					  BUNCHU_RECV_KIND2, 
					  strlen ( BUNCHU_RECV_KIND ) ) == 0 ) {
			return ( 1 ) ;
		}
/*
		//拡張子チェック
		if ( memcmp ( &(pdirEnt->d_name[li_len-strlen(BUNCHU_RECV_SFX)]), 
					  BUNCHU_RECV_SFX, 
					  strlen ( BUNCHU_RECV_SFX ) ) != 0 ) {
			return ( 1 ) ;
		}
*/
		return ( 0 ) ;
}

/******************************************************************************/
/*  関 数 名　：_sFncEnvDip()				 								  */
/*  機能概要　：プログラム環境変数出力関数【トレース用】	  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct stockerEnv *   	プログラム環境構造体。		 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：無し														  */
/******************************************************************************/
static void
_sFncEnvDip( pEnv )
struct bunchuEnv	*pEnv ;
{
#if defined ( _TRACE )
	loging ( "########## Bunchu - _sFncEnvDip ##########\n" ) ;
	loging ( "\t【共有ディレクトリ】\n" ) ;
	loging ( "\t%s : [%s]\n", BUNCHU_PRM_DIR_BUNCHU,		pEnv->cDirBunchu ) ;
	loging ( "\t%s : [%s]\n", BUNCHU_PRM_DIR_LOG,			pEnv->cDirLog ) ;
	loging ( "\t%s : [%s]\n", BUNCHU_PRM_FILE_DBG,		pEnv->cDebugLogName ) ;
	loging ( "\t%s : [%s]\n", BUNCHU_PRM_FILE_TR,		pEnv->cTraceLogName ) ;
	loging ( "\t%s : [%s]\n", BUNCHU_PRM_FILE_ACS,		pEnv->cAccessLogName ) ;
	loging ( "\t%s : [%s]\n", BUNCHU_PRM_FILE_ERR,		pEnv->cErrorLogName ) ;
	loging ( "\t%s : [%d]\n", BUNCHU_PRM_SHM_KEY,        pEnv->shm_Key ) ;
	loging ( "\t%s : [%d]\n", BUNCHU_PRM_SLEEP_SEC,      pEnv->sleep_Sec ) ;
	loging ( "########## Bunchu - _sFncEnvDip ##########\n" ) ;
#endif
}
/******************************************************************************/
/*  関 数 名　：sFncPutLog()                                                  */
/*  機能概要　：アプリケーションログ出力                                      */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *      編集文字列                                        */
/*  出　　力　：                                                              */
/*  復帰情報　：無し                                                          */
/******************************************************************************/
void
sFncPutLog( LOG_TRCKIND peTrcKind, char * pcSrcName, char * pcFncName, int plLineNo, char * pcExeFlg, char * pcErrCode, char * pcfmt, ... )
{
    va_list  ap ;
    char     cMsg[1024] ;

    /***
     ***    ログ初期値設定
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
     ***    ログ出力
     ***/
    _ZbmlPutLog ( &gstLogMem, pcSrcName, plLineNo) ;
    return ;

}
void
sFuncPutErrlist( struct bunchuEnv *pEnv, char *sFile, int iLine, char *sSyriymd, char *sUkeymd,
				char *sKntno, char *sIrino, char *sKomoku, char *pcfmt, ... )
{
	va_list	ap;
	char	pcMsg[512];
	FILE	*fp;
	char	sListFile[1024], sysdate[128], systime[128];

	memset(sListFile, 0, sizeof(sListFile));
	memset(sysdate, 0, sizeof(sysdate));
	memset(systime, 0, sizeof(systime));
	nowdateget( sysdate, systime );
	sprintf(sListFile, "%s/%s%s.log", pEnv->cDirLog, MYAPP_APP_NAME, sysdate);

	if( (fp = fopen(sListFile, "a") ) == NULL ) {
		fprintf(stderr, "エラーリスト: fopen(\"%s\") エラー %d %s\n", sListFile, errno);
		return;
	}

	memset(pcMsg, 0, sizeof(pcMsg));
	va_start(ap, pcfmt);
	vsprintf(pcMsg, pcfmt, ap);
	va_end(ap);

	fprintf(fp, "%s!%s!%d!%s!%s!%s!%s!%s!%s\n",
		SYBT_BUNCH, sFile, iLine, sSyriymd, sUkeymd, sKntno, sIrino, sKomoku, pcMsg );

	fclose(fp);

	return;
}
/********************************************************************/
/*	関数名		：main()											*/
/*	機能概要	：分注情報展開処理メイン							*/
/* 	入力		：													*/
/*	 第１引数   ：int	argc		パラメータ数					*/
/*	 第２引数	：char	*argv[]		パラメータ値					*/
/*	出力		：													*/
/*   正常：0														*/
/*	 異常：1以上													*/
/********************************************************************/
int 
main( argc, argv )
int		 argc ;
char	*argv[] ;
{

	struct bunchuEnv	 sEnv ;

	/***
	 ***	バックグラウンド処理
	 ***/
	if( daemon( 0, 1 ) < 0 ) {
		fprintf ( stderr, "bunchu : Error daemon() [%d]\n", errno );
		exit( 9 );
	}

	/***
	 ***	初期処理	
	 ***/
	if ( initFunction ( argc, argv, &sEnv )  != 0 ) {
		fprintf ( stderr, "bunchu : Error initFunction [%d]\n", gintErrorCode ) ;
		exit ( 9 ) ;
	}
	_sFncEnvDip ( &sEnv ) ;
	
	/***
	 ***	主処理	
	 ***/
	if ( mainFunction ( &sEnv )  != 0 ) {
		fprintf ( stderr, "bunchu : Error mainFunction [%d]\n", gintErrorCode ) ;
		exit ( 9 ) ;
	}

	/***
	 ***	終了処理	
	 ***/
	endFunction ( &sEnv ) ;
	fprintf ( stderr, "bunchu : endFunction [%d]\n", gintErrorCode ) ;
}

/** End of File ***************************************************************/
