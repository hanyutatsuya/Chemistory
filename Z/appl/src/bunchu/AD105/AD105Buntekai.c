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
/*  2.01	2006/10/24		INTEC  			分注OK分オーダ作成		*/
/*  2.01	2006/12/16		YOON  			SQL ERROR 修正			*/
/*  3.02    2007/04/12      INTEC           Buntekai -803の後続追加 */
/*  4.01                    k.moriya        新フロンティア対応      */
/*  4.02    2009/03/24      h.sekiya        優先順の設定不具合対応  */
/********************************************************************/

/********************************************************************/
/*	インクルード宣言												*/
/********************************************************************/
#include "AD105Buntekai.h"

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
#define NYO_KNSGRP "0003"
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
extern int g_iJdkmk;
extern Jdkmkmst *g_strJdkmk;
extern Sysknrmst *g_strSysknr;
osada(struct bunchuEnv *pEnv)
{
}
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

	// ソートキー情報の取得
	if( (pEnv->pSortNo = AgetSortInfo(&pEnv->pSort)) < 0 ) {
		//	異常終了	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}

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

	int				  li_fileCnt ;
	char			  lc_fileName[1024] ;
	struct stat		  lst_statBuf ;
	char	sFileOK[1024], sFileNG[1024];
	char	sDttm[128];

	Flbun	  lst_trInfo ;

	//トレースログ
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "Start Main Function");

    //if( ret = ZdbConnect( "labokns", "nxtgene", "nxtgene" ) ) [
    if( ret = ZdbConnect( pEnv->sDbName, pEnv->sDbUser, pEnv->sDbPswd ) ) {
        printf("DB connect error (%d)", ret);
        return( -1 );
    }

	G_ic = iconv_open( "EUC-JP", "SHIFT-JIS" );

	//マスタ事前読み込み
	int nRet = 0;
	nRet = GetMstDate();
	if(nRet == 0)
	{	//2007-04-02 YOON エラー処理追加
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                 "Master Tables do not setup and exit program");
		exit(1);
	} 

	/***
	 ***	分注情報ディレクトリ監視	
	 ***		永久ループ
	 ***		停止コマンドで終了
	 ***/
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
		if( li_fileCnt ) {
			//トレースログ
			memset(sDttm, 0, sizeof(sDttm));
			nowdateget1( sDttm );
    		sFncPutLog ( TRCKIND_OPT, "", "", 0,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "処理開始(%s) ファイル数(%d)", sDttm, li_fileCnt);
		}
		while ( li_idx < li_fileCnt ) {
			sprintf (lc_fileName, "%s/%s",pEnv->cDirBunchu, lpst_dirBuf[li_idx]->d_name ) ;

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
			if ( S_ISREG ( lst_statBuf.st_mode ) ) 
			{
				ret = sFncTrFileRead ( pEnv, lc_fileName, &lst_trInfo );
				if ( ret < 0 ) {
					sprintf(sFileOK,"%s/%s",pEnv->cDirBunchuNG,lpst_dirBuf[li_idx]->d_name);
					sFncPutLog ( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__,
                	EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                	"MOVE File POS [%s], DIRECTORY [%s]", sFileOK,pEnv->cDirBunchuNG);
				} else {
					sprintf(sFileOK,"%s/%s",pEnv->cDirBunchuOK,lpst_dirBuf[li_idx]->d_name);
				}
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__,
                EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "MOVE File RET:<%d>,POS [%s]",ret, sFileOK);

				//	解放
				free ( lpst_dirBuf[li_idx] ) ;
				// ファイル移動
				if( rename( lc_fileName, sFileOK) < 0 ) {
//					printf("rename error %s -> %s\n", lc_fileName, sFileOK);
					sFncPutLog ( TRCKIND_OPT, __FILE__, "mainFunction", __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"rename error %s -> %s\n", lc_fileName, sFileOK);
					return( -1 );
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

		if( li_fileCnt ) {
			//トレースログ
			memset(sDttm, 0, sizeof(sDttm));
			nowdateget1( sDttm );
    		sFncPutLog ( TRCKIND_OPT, "", "", 0,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "処理終了(%s)", sDttm);
		}

		/***
	 	*** 停止コマンド確認
	 	***/
		if( li_stopFlg != 1 ) {
			if ( sFncShmGet ( pEnv, &li_stopFlg ) < 0 ) {
				return ( -1 ) ;
			}
		}
		if ( li_stopFlg == 1 ) {
			break ;
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
/******************************************************************************/
/*  関 数 名　：dBunCrTryfile()				 								  */
/*  機能概要　：トレー先付け情報ファイル作成								  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *					分注情報							  */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
/******************************************************************************/
int
dBunCrTryfile(pst_Env, strKenPos, iKenPos)
struct bunchuEnv    *pst_Env;
// 2008-01-07 新フロンティア対応 UPD START
//TRAY *strKenPos;
RACK *strKenPos;
// 2008-01-07 新フロンティア対応 UPD END
int	iKenPos;
{
	char	sysdate[128], systime[128];
	char	sTryFilenmTMP[128], sTryFilenmDAT[128];
// 2008-01-07 新フロンティア対応 UPD START
//	char	sBuf[2048], sBuf1[1024];
	char	sBuf[9];
// 2008-01-07 新フロンティア対応 UPD END
	int		i, j;
	FILE	*fp;

	//トレースログ
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "dBunCrTryfile", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "Start Function");

	memset(sBuf, 0, sizeof(sBuf));
	for( i=0; i < iKenPos ;++i ) {
		memset(sysdate, 0, sizeof(sysdate));
		memset(systime, 0, sizeof(systime));
		memset(sTryFilenmTMP, 0, sizeof(sTryFilenmTMP));
		memset(sTryFilenmDAT, 0, sizeof(sTryFilenmDAT));
		memset(systime, 0, sizeof(systime));

		nowdateget(sysdate, systime);

// 2008-01-07 新フロンティア対応 INS START
		memset(sBuf, 0, sizeof(sBuf));
		sprintf(sBuf, "%08d", atoi((strKenPos+i)->sRackID));
// 2008-01-07 新フロンティア対応 INS END
		if( pst_Env->sPutDir ) {
/* BUG 2006.04.06
			sprintf(sTryFilenmTMP, "%s/%s/TR_%s%s_%s.tmp", pst_Env->cDirTryinfo, pst_Env->sPutDir, &sysdate[2], systime, (strKenPos+i)->sTryID);
			sprintf(sTryFilenmDAT, "%s/%s/TR_%s%s_%s.dat", pst_Env->cDirTryinfo, pst_Env->sPutDir, &sysdate[2], systime, (strKenPos+i)->sTryID);
*/
// 2008-01-07 新フロンティア対応 UPD START
//			sprintf(sTryFilenmTMP, "%s/%s/TR_%s%s_%s.tmp", pst_Env->cDirTryinfo
//				,(strKenPos+i)->sPutDir, &sysdate[2], systime, (strKenPos+i)->sTryID);
//			sprintf(sTryFilenmDAT, "%s/%s/TR_%s%s_%s.dat", pst_Env->cDirTryinfo
//				,(strKenPos+i)->sPutDir, &sysdate[2], systime, (strKenPos+i)->sTryID);
			sprintf(sTryFilenmTMP, "%s/%s/RK_%s%s_%08s.tmp", pst_Env->cDirTryinfo, (strKenPos+i)->sPutDir, &sysdate[2], systime, sBuf);
			sprintf(sTryFilenmDAT, "%s/%s/RK_%s%s_%08s.dat", pst_Env->cDirTryinfo, (strKenPos+i)->sPutDir, &sysdate[2], systime, sBuf);
// 2008-01-07 新フロンティア対応 UPD END
		} else {
// 2008-01-07 新フロンティア対応 UPD START
//			sprintf(sTryFilenmTMP, "%s/TR_%s%s_%s.tmp", pst_Env->cDirTryinfo, &sysdate[2], systime, (strKenPos+i)->sTryID);
//			sprintf(sTryFilenmDAT, "%s/TR_%s%s_%s.dat", pst_Env->cDirTryinfo, &sysdate[2], systime, (strKenPos+i)->sTryID);
			sprintf(sTryFilenmTMP, "%s/RK_%s%s_%08s.tmp", pst_Env->cDirTryinfo, &sysdate[2], systime, sBuf);
			sprintf(sTryFilenmDAT, "%s/RK_%s%s_%08s.dat", pst_Env->cDirTryinfo, &sysdate[2], systime, sBuf);
// 2008-01-07 新フロンティア対応 UPD END
		}
	
		if( (fp = fopen(sTryFilenmTMP, "w")) == NULL ) {
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "dBunCrTryfile", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                 "Fail Directory:%s",sTryFilenmTMP);
			//ログ出力
			return( -1 );
		}
// 2008-01-07 新フロンティア対応 UPD START
//		//sprintf(sBuf, "%s,%s", (strKenPos+i)->sTryID, (strKenPos+i)->sStDate);
//		fprintf(fp, "%s,%s", (strKenPos+i)->sTryID, (strKenPos+i)->sStDate);
//		for( j=1; j <= MAXPOSOLD ;++j ) {
		fprintf(fp, "%s,%s", (strKenPos+i)->sRackID, (strKenPos+i)->sStDate);
		for( j=1; j <= MAXPOS ;++j ) {
// 2008-01-07 新フロンティア対応 UPD END
		//	memset(sBuf1, 0, sizeof(sBuf1));
		//	sprintf(sBuf1, ",%s,%s,%s,%s", 
			fprintf(fp, ",%s,%s,%s,%s", 
				(strKenPos+i)->strPosInfo[j].sUkeDate, (strKenPos+i)->strPosInfo[j].sKentaiID,
				(strKenPos+i)->strPosInfo[j].sIraiNo, (strKenPos+i)->strPosInfo[j].sKenSybt);
		//	strcat(sBuf, sBuf1);
		}
		fprintf(fp, ",%4.4s/%2.2s/%2.2s %2.2s:%2.2s:%2.2s\n", 
				sysdate, &sysdate[4], &sysdate[6], systime, &systime[2], &systime[4]);
		fclose(fp);

// 2008-01-07 新フロンティア対応 UPD START
//		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunCrTryfile", __LINE__,
//                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//                 "Toray Directory:%s",sTryFilenmDAT);
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunCrTryfile", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                 "Tray Directory:%s",sTryFilenmDAT);
// 2008-01-07 新フロンティア対応 UPD END

		//ファイル名変更
		if( rename( sTryFilenmTMP, sTryFilenmDAT ) < 0 ) {
// 2008-01-07 新フロンティア対応 INS START
			//ログ出力
			sFncPutLog ( TRCKIND_OPT, __FILE__, "dBunCrTryfile", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                 "Rename Error:[%s] --> [%s]", sTryFilenmTMP, sTryFilenmDAT);
// 2008-01-07 新フロンティア対応 INS END
		}

// 2008-01-07 新フロンティア対応 DEL (BD301に移行) START
//		memset(sBuf1, 0, sizeof(sBuf1));
//		memset(sBuf1, ' ', 16);
//		//初回WSレコードの登録
//		if( insWsseqknri((strKenPos+i)->sStDate, sBuf1, (strKenPos+i)->sTryID,
//				(strKenPos+i)->iKntSuu, (strKenPos+i)->iMinSeq, (strKenPos+i)->iMaxSeq ) < 0 ) {
//			return( -1 );
//		}
// 2008-01-07 新フロンティア対応 DEL (BD301に移行) END
	}

	//トレースログ
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "dBunCrTryfile", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function");

	return( 0 );
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
// 2008-01-07 新フロンティア対応 UPD START
//TRAY **strKenPos;
RACK **strKenPos;
// 2008-01-07 新フロンティア対応 UPD END
int		*iKenPos;
char	*sFLname;
int		iFLcnt;
{
	FILE	*fp;
	Flbun *pBunchu;			//分注結果情報ファイル構造体
	Bunchu	strBunchuTB, pBunW;	//分注結果情報テーブル構造体
	Kanjya	strKanjyaTB;	//患者情報テーブルKEY構造体
	Kanjya	*pKanjya = NULL;		//患者情報テーブル格納構造体
	Irai	strIraiTB;		//依頼情報テーブルKEY構造体
	Irai	*pIrai = NULL;			//依頼情報テーブル格納構造体
	Irai	*pIrai2 = NULL;			//依頼情報テーブル格納構造体 2008-01-07 項目コード 64項目以上対応 追加
	Irai	pIraiW;			//依頼情報テーブル格納構造体
	Irai	pIraiW1 ;			//依頼情報テーブル格納構造体
	Irai	pIraiW2 ;			//依頼情報テーブル格納構造体 2008-01-07 項目コード 64項目以上対応 追加
	Kenorder pOrder;		//検査オーダテーブル格納構造体
	//Kenorder *pOrder = NULL;		//検査オーダテーブル格納構造体
	Realchk	*pReal = NULL;		//即時チェック格納構造体
	char	buf[1024], buf1[1024], buf2[128];		//ワーク
	BmlDate	today;
	char	sDay[20], sysdate[128], systime[128];
	char	*pKmkCd, *pKmkCd1;
	int		i, num, iIrai, j, iOrder, cnt, iHit, k,l,m;
	long	ret;
	char	sWknsgrp[17], sWknsStart[11];
	char 	tmpiraino[12] = {0,};
	TRAY *pTray;
	RACK *pRack;			// 2008-01-07 新フロンティア対応 追加
	char ialloc, iPoint;
	int		iWs, iEda;
	Sysknrmst strSyskn, *pSyskn = NULL;
	int		iSkipFlg;
	int iRet;
	char	sWork[10];
	char	sWork1[10];
	int		iJidoFlg;
	int 	iOldFlg;
	char	sKjNo[10];
	int		iOya;
	int		iOdrMkFlg;
//YOON 2007-02-17
	int 	iDBBunUpflg = 1; //分注更新フラグ(chkBunchu関数で使います。)
	char	sKeito[3];
	char	sBkfkkbn;
	char	cOdrssflg;
	int		iKetasu;
	int		iFukuFlg;
	Ninsiki	strNinsiki;
	int 	sakitukeFileFlg;	//先付けファイル作成(0:しない,1:する)
	int 	iBgroupFlg;			// 3.02 ADD Bgroup=='3'(0:<>'3',1:='3')
	int 	iDupFlg;			// 3.02 ADD -803後続処理対応(0:しない,1:する)
	int		iKmkCd;				// 2008-01-07 新フロンティア対応 追加
	int		iMotokenFlg;		// 2008-01-07 新フロンティア対応 追加
	char	cId2[11];			// 2008-03-24 新フロンティア対応 追加
	int		iId2pos;			// 2008-03-24 新フロンティア対応 追加

	Bunchu *pBunF = NULL;
	Ninsiki strNin; /* 認識テーブル格納構造体 */
	int iCnt;

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
		ZdbRollback();
		return( 10 );
	}

	//分注ファイル識別子チェック(ヘッダーレコード)
	if( !memcmp(pBunchu->sDataSybt, BUNCHU_SYBT_HED, 2) ) {
		//トレースログ
    	sFncPutLog ( TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function(ヘッダーレコード)");
		return( 0 );
	}
	//分注ファイル識別子チェック(終了レコード)
	if( !memcmp(pBunchu->sDataSybt, BUNCHU_SYBT_STP, 2) ) {
		//トレースログ
    	sFncPutLog ( TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function(終了レコード)");
		return( 0 );
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
		ZdbRollback();
		return( 10 );
	}
	
	//分注ファイル識別子チェック(分注END)
	if( !memcmp(pBunchu->sDataSybt, BUNCHU_SYBT_END, 2) ) {
		memset(buf2, 0, sizeof(buf2));
		memcpy(buf2, pBunchu->sTranId, sizeof(pBunchu->sTranId));
		if( dBunEnd( pst_Env, buf2 ) < 0 ) {
			sFncPutLog ( TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                 "dBunEnd 失敗");
			ZdbRollback();
			return( -1 );
		}

		//コミット
		ZdbCommit();

		//トレースログ
    	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function(分注END)");
		return( 0 );
	}

	iSkipFlg = ialloc = 0;

	//系統確認
	memset(sKeito, 0, sizeof(sKeito));
	if( !memcmp(pBunchu->sTranId, "SDATA0", 6) ) {
		memcpy(sKeito, "U0", 2 );
	} else if( !memcmp(pBunchu->sTranId, "SDATA1", 6) ) {
		memcpy(sKeito, "A1", 2 );
	} else if( !memcmp(pBunchu->sTranId, "SDATA2", 6) ) {
		memcpy(sKeito, "A2", 2 );
	} else if( !memcmp(pBunchu->sTranId, "SDATA3", 6) ) {
		memcpy(sKeito, "B1", 2 );
	} else if( !memcmp(pBunchu->sTranId, "SDATA4", 6) ) {
		memcpy(sKeito, "B2", 2 );
	}

	//当日日付取得
	memset(&today, 0, sizeof(BmlDate));
	memset(sDay, 0, sizeof(sDay));
	memset(sysdate, 0, sizeof(sysdate));
	ZbmlDateGetToday(&today);
	ZbmlDateAsString(&today, sDay);
	ZbmlChgAPDate(sysdate, sDay);

	memset(buf, 0, sizeof(buf));
	memset(buf1, 0, sizeof(buf1));
	memset(&strBunchuTB, 0, sizeof(Bunchu));
	memset(&strKanjyaTB, 0, sizeof(Kanjya));
	memset(&strIraiTB, 0, sizeof(Irai));
	
	//BML受付年月日 YYYYMMDD → YYYY-MM-DDに変換
	memcpy(buf, pBunchu->sUkebiBML, sizeof(pBunchu->sUkebiBML));
	//ZbmlChgDBDate( buf1, buf, sizeof(buf)-1);
	sprintf(buf1, "%4.4s-%2.2s-%2.2s", buf, &buf[4],&buf[6]);
	strcpy(strBunchuTB.utkymd, buf1);
	strcpy(strKanjyaTB.utkymd, buf1);
	strcpy(strIraiTB.utkymd, buf1);
	//依頼書No
	if( pst_Env->proc_mode ) {
		//次世代
		memcpy(strIraiTB.irino, pBunchu->sIraiNo, sizeof(pBunchu->sIraiNo));
	} else {
		//過渡期
		memset(buf, 0, sizeof(buf));
		memset(buf1, 0, sizeof(buf1));
		memcpy(buf, pBunchu->sIraiNo, sizeof(pBunchu->sIraiNo));
		sprintf(buf1,"00%-3.3s%-6.6s", &buf[0], &buf[5]);
		strcpy(strBunchuTB.irino, buf1);
		strcpy(strKanjyaTB.irino, buf1);
		strcpy(strIraiTB.irino, buf1);

    	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"依頼書No変換 %s -> %s", buf, strBunchuTB.irino);
	}


	//属性世代No　0固定
	strBunchuTB.zssdino = 0;
	//処理日　システム管理マスタから取得
	ret = getShoribi(pst_Env->sLbcd, pst_Env->sSateid, strBunchuTB.sriymd);
	if( ret == 0 ) {
	//if( (ret = getShoribi(pst_Env->sLbcd, pst_Env->sSateid, strBunchuTB.sriymd)) == 0 ) {
		strcpy(strBunchuTB.sriymd, sDay);
	}
	//検体No
	if( pst_Env->proc_mode ) {
		//次世代
		memcpy(strBunchuTB.kntno, pBunchu->sKentaiNo, sizeof(pBunchu->sKentaiNo));
		strcat(strBunchuTB.kntno, "00");
	} else {
		//過渡期
		memset(buf, 0, sizeof(buf));
		memset(buf1, 0, sizeof(buf1));
		ZbmlInfocpy(buf, pBunchu->sKentaiNo, sizeof(pBunchu->sKentaiNo)+1);
		sprintf(buf1,"00%-3.3s%-6.6s", &buf[0], &buf[5]);
    	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"検体No %s", buf, strBunchuTB.irino);

		//枝番がない場合は9桁でくるので0を追加
		if( strlen(buf1) < 11 ) strcat(buf1, "00");

		strcpy(strBunchuTB.kntno, buf1);

    	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"検体No変換 %s -> %s", buf, strBunchuTB.kntno);

		memset(buf, 0, sizeof(buf));
		memcpy(buf, pBunchu->sWS, sizeof(pBunchu->sWS));
		if( !memcmp(buf, "0151", 4) || !memcmp(buf, "0152", 4) ) 
		{
// 2008-07-02 新フロンティア対応 UPD START
//			if( (pBunchu->sMotoKenRk[0] == 'X') || (pBunchu->sMotoKenRk[0] == 'Y') 
			if( (pBunchu->sMotoKenRk[0] == 'V') || (pBunchu->sMotoKenRk[0] == 'X') || (pBunchu->sMotoKenRk[0] == 'Y') 
// 2008-07-02 新フロンティア対応 UPD END
				|| (pBunchu->sMotoKenRk[0] == 'Z') ) 
			{
				/* 2006-04-23 この処理削除
				memcpy( &strBunchuTB.kntno[9], "00", 2);
				*/
			} 
			else 
			{
				//読み飛ばしチェック１
				memset(buf1, 0, sizeof(buf1));
				memcpy(buf1, &strBunchuTB.kntno[9], 2);
				iEda = atoi(buf1) % 2;	
				if( !memcmp(buf, "0151", 4) ) {
					if( (atoi(buf1) > 0) && (iEda == 0) ) {
						//枝番間違い
    					sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"枝番間違い 依頼書No(%s) 検体No(%s)", strBunchuTB.irino, strBunchuTB.kntno);
/*
						sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, 
							strBunchuTB.utkymd, strIraiTB.kntno, strIraiTB.irino,
							"", "枝番間違い WS[%s]", buf);
*/
						iSkipFlg = 1;
						ZdbRollback();
						return( 11 );
					}
				} else {
					if( (atoi(buf1) == 0) && (iEda != 0) ) {
						//枝番間違い
    					sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"枝番間違い 依頼書No(%s) 検体No(%s)", strBunchuTB.irino, strIraiTB.kntno);
/*
						sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, 
							strBunchuTB.utkymd, strIraiTB.kntno, strIraiTB.irino,
							"", "枝番間違い WS[%s]", buf);
*/
						iSkipFlg = 1;
						ZdbRollback();
						return( 11 );
					}
				}
			}
		}

		//読み飛ばしチェック２
		if( !memcmp(buf, "0952", 4) || !memcmp(buf, "0959", 4)) {
			if( memcmp(pBunchu->sTranId, "SDATA0", sizeof(pBunchu->sTranId)) ) {
				if( (pBunchu->sMotoKenRk[0] == ' ') || (pBunchu->sMotoKenRk[0] == 'Z') ) {
    				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"データスキップ 依頼書No(%s) 検体No(%s)", strBunchuTB.irino, strIraiTB.irino);
/*
					sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, 
						strBunchuTB.utkymd, strIraiTB.kntno, strIraiTB.irino,
						"", "非展開データ WS[%s]", buf);
*/
					iSkipFlg = 1;
					ZdbRollback();
					return( 10 );
				}
			}
		}
		//memcpy(strBunchuTB.kntno, pBunchu->sKentaiNo, sizeof(pBunchu->sKentaiNo));
		//strcat(strBunchuTB.kntno, "00");
	}
	//サンプリングコード
	memcpy(strBunchuTB.smpcd, pBunchu->sWS, sizeof(pBunchu->sWS));
	//サンプリングコード内位置No　0固定
	strBunchuTB.smpcditno = 0;
	memset(sWork, 0, sizeof(sWork));
	memset(sWork1, 0, sizeof(sWork1));
	//チェック文字
	//memcpy(sWork1, pBunchu->sKenChkChar, sizeof(pBunchu->sKenChkChar));
	//sj2euc(sWork, sWork1, sizeof(strBunchuTB.chkmj));
	memcpy(strBunchuTB.chkmj, pBunchu->sKenChkChar, sizeof(pBunchu->sKenChkChar));
	//memcpy(strBunchuTB.chkmj, pBunchu->sKenChkChar, sizeof(strBunchuTB.chkmj));
	//トレーID
	// 2008-01-07 新フロンティア対応 UPD START
	//memcpy(strBunchuTB.trid, pBunchu->sRackId, sizeof(pBunchu->sRackId));
	memcpy(strBunchuTB.trid, TRID_BLANK, sizeof(pBunchu->sRackId));
	//トレーポジション
	//memset(buf, 0, sizeof(buf));
	//memcpy(buf, pBunchu->sIchi, sizeof(pBunchu->sIchi));
	//strBunchuTB.trpos = atoi(buf);
	strBunchuTB.trpos = 0;
	// 2008-01-07 新フロンティア対応 UPD END
	if( strBunchuTB.trpos == 0 ) {	//ポジション0はオーダ作成しない
    	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"データスキップ(ポジション０) 依頼書No(%s) 検体No(%s)", 
			strBunchuTB.irino, strBunchuTB.kntno);
/*
		sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, strBunchuTB.utkymd, 
			strIraiTB.kntno, strIraiTB.irino, "", "非オーダ作成(ポジション０)");
		iSkipFlg = 1;
*/
	}


	//アッセイラックID
	memcpy(strBunchuTB.asyrckid, pBunchu->sRackId, sizeof(pBunchu->sRackId));
	// 2008-01-07 新フロンティア対応 DEL START
	//memset(strBunchuTB.asyrckid, ' ', sizeof(pBunchu->sRackId));
	// 2008-01-07 新フロンティア対応 DEL END
	//アッセイラックポジション
	memset(buf, 0, sizeof(buf));
	memcpy(buf, pBunchu->sIchi, sizeof(pBunchu->sIchi));
	strBunchuTB.asyrckpos = atoi(buf);


	//元検体ラックID
	memset(buf2, 0, sizeof(buf2));
	memset(buf2, ' ', sizeof(pBunchu->sMotoKenRk));
	//オールスペースと先頭が'Z'の場合は編集しない
	/* 2006-04-06 この処理削除
	if( !( !memcmp(pBunchu->sMotoKenRk, buf2, sizeof(pBunchu->sMotoKenRk)) && (pBunchu->sMotoKenRk[0] == 'Z')) ) {
		memset(buf2, 0, sizeof(buf2));
		memcpy(buf2, pBunchu->sMotoKenRk, sizeof(pBunchu->sMotoKenRk));
		switch(buf2[0]) {
		case 'x':
		case 'X':
			sprintf(strBunchuTB.id2, "XXXX%s", &buf2[4]);
			break;
		case 'y':
		case 'Y':
			sprintf(strBunchuTB.id2, "YYYY%s", &buf2[4]);
			break;
		default:
			memcpy(strBunchuTB.id2, pBunchu->sMotoKenRk, sizeof(pBunchu->sMotoKenRk));
			break;
		}
	}
	*/
	// DEL E.Osada 2006-09-12
//#if 0
//	/* 復活 2006-08-27 */
//	if( !memcmp(pBunchu->sMotoKenRk, buf2, sizeof(pBunchu->sMotoKenRk)) ) {
//		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
//            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//            "pBunchu->sMotoKenRk (%s),buf2(%s)"pBunchu->sMotoKenRk, buf2);
//		
//		iSkipFlg = 1;
//		ZdbRollback();
//		return( 10 );
//	}
//	//
//#endif

	// 2008-01-07 新フロンティア対応 UPD START
	//memcpy(strBunchuTB.id2, pBunchu->sMotoKenRk, sizeof(pBunchu->sMotoKenRk));
	iMotokenFlg = 0 ;
	//元検体ラックIDがオールスペースの場合はそのままを設定
	if( !memcmp(pBunchu->sMotoKenRk, buf2, sizeof(pBunchu->sMotoKenRk)) )
	{
		memcpy(strBunchuTB.id2, pBunchu->sMotoKenRk, sizeof(pBunchu->sMotoKenRk));
		iMotokenFlg = 2 ;
	}
	//元検体ラックIDがオール数値の場合(2ID)は、'____0000'を設定
	else if( !sFncChkDigit( pBunchu->sMotoKenRk ) )
	{
		memcpy(strBunchuTB.id2, TRID_BLANK, sizeof(pBunchu->sMotoKenRk));
		iMotokenFlg = 1 ;
	} else {
		memcpy(strBunchuTB.id2, pBunchu->sMotoKenRk, sizeof(pBunchu->sMotoKenRk));
	}
	// 2008-01-07 新フロンティア対応 UPD END
	//元検体ポジション
	memset(buf, 0, sizeof(buf));
	memcpy(buf, pBunchu->sMotoKenPos, sizeof(pBunchu->sMotoKenPos));
	// 2008-01-07 新フロンティア対応 UPD START
	//strBunchuTB.id2pos = atoi(buf);
	//元検体ラックIDがオール数値 or オールスペースの場合(2ID)は、0を設定
	if( iMotokenFlg ) {
		strBunchuTB.id2pos = 0;
	} else {
		strBunchuTB.id2pos = atoi(buf);
	}
	// 2008-01-07 新フロンティア対応 UPD END

	// 2008-03-10 新フロンティア対応 UPD START
	//患者情報確認
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		"患者情報確認");

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
		sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, strBunchuTB.utkymd, 
			strIraiTB.kntno, strIraiTB.irino, "", "患者情報無し");
		ZdbRollback();
		return 12;
	}
//	//性別区分
//	strBunchuTB.sbtkbn = pBunchu->sSexKbn[0];
//	//年齢
//	memcpy(strBunchuTB.age, pBunchu->sAge, sizeof(pBunchu->sAge));
//	//年齢区分
//	strBunchuTB.agekbn = pBunchu->sAgeKbn[0];
//	//施設コード
//	memcpy(strBunchuTB.sstcd, pBunchu->sSisetuCd, sizeof(pBunchu->sSisetuCd));
//	//営業所コード
//	memcpy(strBunchuTB.ecd, pBunchu->sEigyoCd, sizeof(pBunchu->sEigyoCd));
	//性別区分
	strBunchuTB.sbtkbn = pKanjya->sbtkbn;
	//年齢
	memcpy(strBunchuTB.age, pKanjya->age, sizeof(pKanjya->age));
	//年齢区分
	strBunchuTB.agekbn = pKanjya->agekbn;
	//施設コード
	memcpy(strBunchuTB.sstcd, pKanjya->sstcd, sizeof(pKanjya->sstcd));
	//営業所コード
	memcpy(strBunchuTB.ecd, pKanjya->ecd, sizeof(pKanjya->ecd));
	// 2008-03-10 新フロンティア対応 UPD END
	//分注機ID　スペース
	memset(strBunchuTB.bckid, ' ', sizeof(strBunchuTB.bckid)-1);
	//状態フラグ
	strBunchuTB.jtflg = pBunchu->sStsFlg[0];
	//検査種類
	strBunchuTB.knssyr = pBunchu->sKnsSyrui[0];
	//治験フラグ
	strBunchuTB.tknflg = pBunchu->sChiKenFlg[0];
	//特定・緊急フラグ
	strBunchuTB.ttkkflg = pBunchu->sKnkyFlg[0];
	//分注結果
	strBunchuTB.bnckka = pBunchu->sBunKekka[0];

	//尿フロから不明で送られてきた分注情報は取り込まない。 2016/06/10 ADD
	if( !strncmp(strBunchuTB.smpcd, NYO_KNSGRP, 4) && (strBunchuTB.bnckka == 'G') ){
    	sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"尿電解質 不明検体スキップ 依頼書No(%s) 検体No(%s)", strBunchuTB.irino, strIraiTB.irino);
		iSkipFlg = 1;
		ZdbRollback();
		return( 10 );
	}

	//分注OKのもののみオーダ作成する為の判断
	if( (strBunchuTB.bnckka == '0') || (strBunchuTB.bnckka == '4') ) {
		iOdrMkFlg = 0;		//分注OK：オーダ作成
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "分注OK：オーダ作成 iOdrMkFlg(%d)",iOdrMkFlg);
	} 
	else if( strBunchuTB.bnckka == '1' ) 
	{
		iOdrMkFlg = 2;		//複数本取り：オーダ作成しない
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "複数本取り：オーダ作成しない iOdrMkFlg(%d)",iOdrMkFlg);
	} else {
		iOdrMkFlg = 1;		//分注OKでない：オーダしない
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "分注OKでない：オーダしない iOdrMkFlg(%d)",iOdrMkFlg);
	}
	//ソートキー　0固定
	strBunchuTB.srtkey = AbunGetSort(pst_Env, strBunchuTB.id2, strBunchuTB.bnckka);

// 2008-03-10 新フロンティア対応 DEL START
// ↑の性別区分等を設定する直前に移動
//	//患者情報確認
//	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
//		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//		"患者情報確認");
//
//	if( (ret = ABunKnjSel(&strKanjyaTB, &pKanjya, &cnt)) < 0 ) {
//		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
//			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//			"SELECT KANJYA[SQLCODE=%d]", ret ) ;
//		ZdbRollback();
//		return( -1 );
//	}
//	if( cnt == 0 ) {
//		//患者情報が無い場合はスキップ
//		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
//			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//			"患者情報 NOT FOUND BML受付日(%s) 依頼書No(%s)", strIraiTB.utkymd, strIraiTB.irino ) ;
//		sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, strBunchuTB.utkymd, 
//			strIraiTB.kntno, strIraiTB.irino, "", "患者情報無し");
//		ZdbRollback();
//		return 12;
//	}
// 2008-03-10 新フロンティア対応 DEL END

	// 患者情報の備考2から畜尿情報編集
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
        EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "患者情報の備考2から畜尿情報編集");
	memset(buf, 0, sizeof(buf));
	iHit = j = 0;
	memset(buf, 0, sizeof(buf));
	for( i=0; i < sizeof(pKanjya->bko2) ;++i ) {
		if( pKanjya->bko2[i] != '!' ) {
				buf[j++] = pKanjya->bko2[i];
		} else {
			switch(iHit) {
			case 0:		//畜尿時間
				memcpy(strBunchuTB.tntme, buf, sizeof(pBunchu->sChikuTm));
				break;
			case 1:		//畜尿時間単位
				strBunchuTB.tntni = buf[0];
				break;
			case 2:		//畜尿量
				memcpy(strBunchuTB.tnryo, buf, sizeof(pBunchu->sChikuRyo));
				break;
			case 3:		//畜尿量区分（ありえない！？）
				strBunchuTB.tnryotni = buf[0];
				break;
			}
			memset(buf, 0, sizeof(buf));
			iHit++;
			j = 0;
		}
	}
	if( iHit == 3 ) {
		//畜尿量区分
		strBunchuTB.tnryotni = buf[0];
	}

	//属性世代No取得
	strIraiTB.zssdino = pKanjya->zssdino;
	strBunchuTB.zssdino = pKanjya->zssdino;

	//依頼情報テーブル取得
	if( (ret = ABunIriSel(&strIraiTB, &pIrai, &iIrai)) < 0 ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"SELECT IRAI[SQLCODE=%d]", ret ) ;
		ZdbRollback();
		if( pKanjya != NULL ) {
			ZbmlFree(pKanjya);
			pKanjya = NULL;
		}
		return( 0 );
	}
	if( iIrai == 0 ) {
		//依頼情報が無い
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"依頼情報 NOT FOUND BML受付日(%s) 依頼書No(%s) 属性世代No(%d) 項目コード(%s)",
			strBunchuTB.utkymd, strBunchuTB.irino, strBunchuTB.zssdino, strIraiTB.kmkcd ) ;
		sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, strBunchuTB.utkymd, 
			strBunchuTB.kntno, strBunchuTB.irino, "", "依頼情報無し");
		ZdbRollback();
		if( pKanjya != NULL ) {
			ZbmlFree(pKanjya);
			pKanjya = NULL;
		}
		// Update 2007.04.05 return( 10 );
		return( 12 );
	}

// 2008-01-07 項目コード 64項目以上対応 INS START
	//依頼情報コピー
	memset(&pIraiW2, 0, sizeof(Irai));
	memcpy(&pIraiW2, pIrai, sizeof(Irai));
	memcpy(pIraiW2.smpcd, strBunchuTB.smpcd, sizeof(strBunchuTB.smpcd));
	//依頼情報テーブルから項目コードのみ取得 (select key:utkymd, irino, smpcd)
	if( (ret = ABunIriKmkCdSel(&pIraiW2, &pIrai2, &iKmkCd)) < 0 ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"SELECT IRAI[SQLCODE=%d]", ret ) ;
		ZdbRollback();
		if( pKanjya != NULL ) {
			ZbmlFree(pKanjya);
			pKanjya = NULL;
		}
		return( 0 );
	}
	if( iKmkCd == 0 ) {
		//依頼情報に項目コードが無い
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"依頼情報 NOT FOUND BML受付日(%s) 依頼書No(%s) 属性世代No(%d) 項目コード(%s)",
			strBunchuTB.utkymd, strBunchuTB.irino, strBunchuTB.zssdino, strIraiTB.kmkcd ) ;
		sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, strBunchuTB.utkymd, 
			strBunchuTB.kntno, strBunchuTB.irino, "", "依頼情報無し");
		ZdbRollback();
		if( pKanjya != NULL ) {
			ZbmlFree(pKanjya);
			pKanjya = NULL;
		}

		return( 12 );
	}
//sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
//    EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//    "iKmkCd <%d>",iKmkCd);
//for( i=0; i < iKmkCd ;++i ) {
//	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
//	    EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//	    "KmkCd <%s>",(pIrai2+i)->kmkcd);
//}
// 2008-01-07 項目コード 64項目以上対応 INS END

	// 3.02 ADD STA
	iBgroupFlg = 0;
	iDupFlg = 0;
	// 3.02 ADD END

	if(iOdrMkFlg == 0)	
			sakitukeFileFlg = 1;
	else
			sakitukeFileFlg = 0;
	iOrder = 0;
	iOldFlg = iOdrMkFlg;
	//項目コード分INSERTする
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
        EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "項目コード分INSERTする iOdrMkFlg <%d>",iOdrMkFlg);

// 2008-01-07 項目コード 64項目以上対応 UPD START
//	for( i=0; i < BUNCHU_KMK_MAX ;++i ) {
	for( i=0; i < iKmkCd ;++i ) {
// 2008-01-07 項目コード 64項目以上対応 UPD END
		iOdrMkFlg = iOldFlg;
// 2008-01-07 項目コード 64項目以上対応 UPD START
//		pKmkCd1 = pKmkCd + (i * BUNCHU_KMK_SZ);
		pKmkCd1 = (pIrai2+i)->kmkcd;
//sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
//    EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//    "pKmkCd1 <%s>",pKmkCd1);
// 2008-01-07 項目コード 64項目以上対応 UPD END
		memset(buf2, 0, sizeof(buf2));
		memcpy(buf2, pKmkCd1, BUNCHU_KMK_SZ);
		if( pKmkCd1 == NULL ) {
			//ログ出力
			sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
            	EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            	"pKmkCd1 == NULL");
			ZdbRollback();
			return(-1);
		}
		//依頼TBからの情報と比べる
		if( !memcmp(buf2, "       ", BUNCHU_KMK_SZ) ) {
			//スペースだったら処理スキップ
			continue;
		}
		//項目コード検索
		for( k=0; k < iIrai ;++k ) {
			if( !memcmp((pIrai+k)->kmkcd, buf2, 7) ) {
				//ヒット！！
				//pIraiW = (pIrai+k);
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"一致する項目コード発見(%s)",buf2);
				break;
			}
		}
		if( k >= iIrai ){
			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"一致する項目コードなし(%s)",buf2);
			continue;
		}

		if( (pIrai+k)->odrssflg == 'F' ) {
			//既に自動発生で済みの為スキップ
			continue;
		}

		strBunchuTB.bnckka = pBunchu->sBunKekka[0];

		//検査グループ展開
		memset(sWknsgrp, 0, sizeof(sWknsgrp));
		//項目マスタ検索
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"項目マスタ検索");
		if( (ret = ABunGetKnsgrp(&strBunchuTB, pKanjya, buf2, sWknsgrp)) < 0 ) {
			sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"項目マスタ NOT FOUND 項目コード(%s) サンプリングコード(%s) 開始年月日(%s)",
				buf2, strBunchuTB.smpcd, strBunchuTB.sriymd ) ;
   			sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
				"項目マスタなし IRINO(%s) KNTNO(%s)", strBunchuTB.irino, strBunchuTB.kntno);
			ZdbRollback();
			if( pKanjya != NULL ) {
				ZbmlFree(pKanjya);
				pKanjya = NULL;
			}
			ZdbRollback();
			return(10);
		}
		if( ret == 0 ) {
			//項目マスタに検査グループが存在しない場合はスキップ
			sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"項目マスタ NOT FOUND 項目コード(%s) サンプリングコード(%s) 開始年月日(%s)",
				buf2, strBunchuTB.smpcd, strBunchuTB.sriymd ) ;
			sFuncPutErrlist(pst_Env,sFLname,iFLcnt,strBunchuTB.sriymd,strBunchuTB.utkymd, 
				strBunchuTB.kntno, strBunchuTB.irino, buf2, "項目マスタ無し");
			if( pKanjya != NULL ) {
				ZbmlFree(pKanjya);
				pKanjya = NULL;
			}
			ZdbRollback();
			return( 10 );
		}
//YOON 2007-02-01　関数の中で消しています。
//		if( ret == 2 ) {
//			sFuncPutErrlist(pst_Env,sFLname,iFLcnt,strBunchuTB.sriymd,strBunchuTB.utkymd, 
//				strBunchuTB.kntno, strBunchuTB.irino, buf2, "項目マスタ無し");
//		}
		
		//YOON 2007-02-01
		if( ret == 3 ) {
			iOdrMkFlg = 1;				//オーダがなし
   			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"分注区分＝３処理 iOdrMkFlgを<1>に変更");
			//YOON
			sakitukeFileFlg = 0;
			// 3.02 ADD -803後続処理判断用
			iBgroupFlg = 1;
		}
		//検査グループ設定
		memcpy((pIrai+k)->knsgrp, sWknsgrp, 16);
		//系統設定
		memcpy(strBunchuTB.bckid, sKeito, 2);
		//検査項目コード
		memset(strBunchuTB.kmkcd, 0, sizeof(strBunchuTB.kmkcd));
		memcpy(strBunchuTB.kmkcd, pKmkCd1, BUNCHU_KMK_SZ);

		//ソートキー再計算
		strBunchuTB.srtkey = AbunGetSort(pst_Env, strBunchuTB.id2, strBunchuTB.bnckka);

		iFukuFlg = 0;
		//分注情報セーブ
		memset(&pBunW, 0, sizeof(Bunchu));
		memcpy(&pBunW, &strBunchuTB, sizeof(Bunchu));

		//依頼.オーダ作成状況フラグ更新
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"依頼.オーダ作成状況フラグ更新 odrssflg:<%c>",(pIrai+k)->odrssflg);
		if( (pIrai+k)->odrssflg == ' ' ) {	//依頼が初期状態
			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"依頼が初期状態");
			if( iOdrMkFlg == 0 ) {
				(pIrai+k)->odrssflg = '2';
			} else if( iOdrMkFlg == 2 ) {
				(pIrai+k)->odrssflg = '1';
				//複数本フラグON ADD 2006-07-17 E.Osada
				memset(&strNinsiki, 0, sizeof(Ninsiki));
				strcpy(strNinsiki.utkymd, strBunchuTB.utkymd);
				strcpy(strNinsiki.sriymd, strBunchuTB.sriymd);
				strcpy(strNinsiki.irino, strBunchuTB.irino);
				strcpy(strNinsiki.kntno, strBunchuTB.kntno);
				strNinsiki.zssdino = strBunchuTB.zssdino;
				if( (ret = ABunNinUpAll( &strNinsiki )) < 0 ) {
					//エラーログ出力
					sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"UPDATE NINSIKI(W)[%s %s %s %s %s] [SQLCODE=%d]", 
						strBunchuTB.sriymd, strBunchuTB.utkymd, 
						strIraiTB.kntno, strIraiTB.irino, (pIrai+k)->kmkcd, ret);
					ZdbRollback();
					return( -1 );
				}
				//
			} else {
				(pIrai+k)->odrssflg = '1';
			}
		} else {	//依頼は既に分注展開処理を行っている
			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"複数本取り確認 irino:%s,kmkcd:%s",(pIrai+k)->irino,(pIrai+k)->kmkcd);
			// 複数本取り確認
			//if( ((pIrai+k)->odrssflg == '2') && (iOdrMkFlg == 0) )
			memset(sWork, 0, sizeof(sWork));
			ZbmlInfocpy(sWork, (pIrai+k)->smpcd, sizeof((pIrai+k)->smpcd));
			if( !strcmp(strBunchuTB.smpcd, sWork) ) 
			{ // サンプリングコードチェック
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"サンプリングコードチェック");

				/* 2.01 ADD STA /////////////////////////////////////////////
				// 分注NG->WS出力->分注OKの場合は、OKのオーダも作成する
				// -> 取得した依頼情報.オーダ作成ﾌﾗｸﾞを指示状態(=1)に置換
				if( ((pIrai+k)->odrssflg == '2') && (iOdrMkFlg == 0) ) { */
				/*  4.02 上記の対応では分注NGの結果が再検に回っていると駄目なので、条件を追加
					  (検査工程区分が A (初回)以外の場合 → WSを一度は出力している)  */
				if( ( ((pIrai+k)->odrssflg == '2') || !((pIrai+k)->ksktkbn == 'A') ) && (iOdrMkFlg == 0) ) {
					if( cntBunchuOk( &strBunchuTB ) == 0 ) 
					{
						// 分注OKの分注結果情報が存在しない->オーダ作成
						(pIrai+k)->odrssflg = '1';
				
						//YOON 2007-02-15 odrssflgを利用しない。
						iDBBunUpflg = 0;						
				
						//2006-12-13 YOON 検体一つ当一つログ出力
						if(strcmp(strIraiTB.irino,tmpiraino))
						{
						sFncPutLog(TRCKIND_ERROR, __FILE__
							, "dBunchu_ins", __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"分注NG->WS出力->分注OK [%s %s kntno(%s) irino(%s) kmkcd(%s)]", 
							strBunchuTB.sriymd, strBunchuTB.utkymd, 
							strIraiTB.kntno, strIraiTB.irino,(pIrai+k)->kmkcd );
							strcpy(tmpiraino,strIraiTB.irino);
						}
					}
				}
				// 2.01 ADD END /////////////////////////////////////////////

				/* 2007-08-07 Nagata ///////////////////////////////////////////////////////
				分注NG → WS作成 → 非分注　の場合は後から来た分注結果を複数本扱いとする
				if( ((pIrai+k)->odrssflg == '2') && (iOdrMkFlg == 0) ) {
				if( ((pIrai+k)->odrssflg == '2') && (iOdrMkFlg == 0 || iOdrMkFlg == 1) ) { */
				/* 4.02 上記の対応では分注NGの結果が再検に回っていると駄目なので、条件を追加
						(検査工程区分が初回以外で自分が非分注の場合)  */
				if( ( ((pIrai+k)->odrssflg == '2') && (iOdrMkFlg == 0 || iOdrMkFlg == 1) ) ||
						(!((pIrai+k)->ksktkbn == 'A') && iOdrMkFlg == 1) ) {
					//複数本取り！！
					strBunchuTB.bnckka = '1';
					//複数本フラグ更新
					if( (ret = ABunSelKey( &strBunchuTB, &pBunF, &iCnt )) < 0 ) {
							sFncPutLog ( TRCKIND_WARNING, __FILE__, "chkBunchu", __LINE__,
										 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
										 "分注情報SELECT ERROR IRINO(%s) KNTNO(%s) KMKCD(%s) SQLCODE(%d)",
										 strBunchuTB.irino, strBunchuTB.kntno, strBunchuTB.kmkcd, ret);
					}
					if( iCnt > 0 ) {
						memset(&strNin, 0, sizeof(Ninsiki));
						strcpy(strNin.utkymd, pBunF->utkymd);
						strcpy(strNin.sriymd, pBunF->sriymd);
						strcpy(strNin.irino, pBunF->irino);
						strcpy(strNin.kntno, pBunF->kntno);
						strNin.zssdino = pBunF->zssdino;
						if( (ret = ABunNinUp( &strNin )) < 0 ) {
								sFncPutLog ( TRCKIND_WARNING, __FILE__, "chkBunchu", __LINE__,
											 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
											 "認識情報SELECT ERROR IRINO(%s) KNTNO(%s) KMKCD(%s) SQLCODE(%d)",
											 strBunchuTB.irino, strBunchuTB.kntno, strBunchuTB.kmkcd, ret);
						}
					}
	
					//ソートキー再計算
					strBunchuTB.srtkey = AbunGetSort(pst_Env, strBunchuTB.id2, strBunchuTB.bnckka);
					iOdrMkFlg = 3;
				} 
				else 
				{
					if( ((pIrai+k)->odrssflg == '1') && (iOdrMkFlg == 0) ) {
						//後から分注ＯＫがきたのでオーダ発行する
						(pIrai+k)->odrssflg = '2';
						iOdrMkFlg = 0;
					} else {
						sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"複数本取り fileno(%d) odrssflg(%c) kntno(%s) kmkcd(%s) smpcdI(%s) smpcdB(%s)",
							iFLcnt, pIraiW.odrssflg, strBunchuTB.kntno, (pIrai+k)->kmkcd,
							(pIrai+k)->smpcd, strBunchuTB.smpcd);
					}
					iFukuFlg = 1;
					//複数本優先度確認
					// 2.01 DELL if( (iRet = chkBunchu( pst_Env, iOdrMkFlg, &strBunchuTB, (pIrai+k)->knsgrp )) < 0 ) [
						/*DEBUG STA --------------------------------------------*/
						sFncPutLog ( TRCKIND_DEBUG, __FILE__
							, "dBunchu_ins", __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"chkBunchu IN 1 [%d][%s %s %s %s %s]", 
							iDBBunUpflg,
							strBunchuTB.sriymd, strBunchuTB.utkymd, 
							strIraiTB.kntno, strIraiTB.irino,(pIrai+k)->kmkcd );
						/*DEBUG END --------------------------------------------*/
					//YOON 2007-02-15
					if((iRet = chkBunchu(pst_Env,iOdrMkFlg,&strBunchuTB, 
						(pIrai+k)->knsgrp,iDBBunUpflg)) < 0 ) 
					{
						sFncPutLog ( TRCKIND_DEBUG, __FILE__
                            , "dBunchu_ins", __LINE__,
                            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                            "chkBunchu 失敗");
						ZdbRollback();
						return( -1 );
					}
					if( iOdrMkFlg != 0 ) {
						if( (pIrai+k)->odrssflg != '2' )
							(pIrai+k)->odrssflg = '1';
						// CHG E.Osada 2006-08-30
						//if( iRet == 1 ) [
						if( iRet != 2 ) {
							iOdrMkFlg = 1;
						} else {
							//複数本取り対象の場合は分注結果に'1'をセット 2006-06-13 E.osada
							strBunchuTB.bnckka = '1';
							//ソートキー再計算
							strBunchuTB.srtkey = AbunGetSort(pst_Env, strBunchuTB.id2, 
													strBunchuTB.bnckka);
							iOdrMkFlg = 3;
						}
					}
				}
			} else {
				//サンプリングコードが違うのでオーダを作成(06/04/16で判明したパターン)
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"サンプリングコード違い fileno(%d) ssflg(%c) kntno(%s) kmkcd(%s) smpcd1(%s) smpcd2(%s)",
					iFLcnt, pIraiW.odrssflg, strBunchuTB.kntno, strBunchuTB.kmkcd, sWork, strBunchuTB.smpcd);
				if( iOdrMkFlg == 0 ) {
					(pIrai+k)->odrssflg = '2';
				} else {
					(pIrai+k)->odrssflg = '1';
				}
//サンプリングコードが違っている場合は複数本取りではない
#if 0
				//複数本フラグON ADD 2006-07-17 E.Osada
				//サンプリングコードが違っていても認識情報には"W"をセットする
				memset(&strNinsiki, 0, sizeof(Ninsiki));
				strcpy(strNinsiki.utkymd, strBunchuTB.utkymd);
				strcpy(strNinsiki.sriymd, strBunchuTB.sriymd);
				strcpy(strNinsiki.irino, strBunchuTB.irino);
				strcpy(strNinsiki.kntno, strBunchuTB.kntno);
				strNinsiki.zssdino = strBunchuTB.zssdino;
				if( (ret = ABunNinUp( &strNinsiki )) < 0 ) {
					//エラーログ出力
					sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"UPDATE NINSIKI(W)[%s %s %s %s %s] [SQLCODE=%d]", 
						strBunchuTB.sriymd, strBunchuTB.utkymd, 
						strIraiTB.kntno, strIraiTB.irino, (pIrai+k)->kmkcd, ret);
					ZdbRollback();
					return( -1 );
				}
#endif
			}
		}
	
		strcpy((pIrai+k)->knsgrp, sWknsgrp);
		strcpy((pIrai+k)->sriymd, strBunchuTB.sriymd);
		
		//検査開始日取得
		memset(sWknsStart, 0, sizeof(sWknsStart));
		//YOON 2007-02-01
		//getKnsKaisibi((pIrai+k)->knsgrp, strBunchuTB.sriymd, sWknsStart);
		getShoribi(pst_Env->sLbcd, pst_Env->sSateid,sWknsStart);
		strcpy((pIrai+k)->knskisyymd, sWknsStart);

		//依頼情報コピー
		memset(&pIraiW, 0, sizeof(Irai));
		memcpy(&pIraiW, (pIrai+k), sizeof(Irai));
		
		//依頼テーブル更新
		if( iOdrMkFlg != 3 ) {
			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"依頼テーブル更新 iOdrMkFlg:%d",iOdrMkFlg);

			if( (ret = ABunKnsgrpUpdate( &pIraiW )) < 0 ) {
				if( ret != -803 ) {
					//エラーログ出力
					sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, 
						strBunchuTB.utkymd, 
						strIraiTB.kntno, strIraiTB.irino, (pIrai+k)->kmkcd, 
						"依頼情報更新エラー[%d] KNSGRP[%s]", 
						ret, (pIrai+k)->knsgrp);
					ZdbRollback();
					if( pIrai != NULL ) {
						ZbmlFree(pIrai);
						pIrai = NULL;
					}
					if( pKanjya != NULL ) {
						ZbmlFree(pKanjya);
						pKanjya = NULL;
					}
// 2008-01-07 新フロンティア対応 INS START
					if( pIrai2 != NULL ) {
						ZbmlFree(pIrai2);
						pIrai2 = NULL;
					}
// 2008-01-07 新フロンティア対応 INS END
					sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"UPDATE IRAI[%s %s %s %s] [SQLCODE=%d]", 
						strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.smpcd, 
						strBunchuTB.kmkcd, ret );
					ZdbRollback();
					return( 10 );
				}
			}
		}

		l = 0;
		//pIraiW1 = NULL;
		iOya = 0;
		iSkipFlg = 1;
		while(1) 
		{
			if(iSkipFlg == 1) 
			{
				// 2008-03-24 新フロンティア対応 INS START
				//検体属性テーブルからID2を取得
				if( iMotokenFlg == 1 )
				{
					sFncPutLog(TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"検体属性テーブルからID2を取得");

					// ID2が見つかった場合、分注結果情報テーブルにINSERTするID2, ID2POSを書き換える
					memset(cId2, 0, sizeof(cId2));
					ret = AZokuSelId2(strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.zssdino, cId2, &iId2pos);

					if( ret == HRC_SQL_NORMAL )
					{
						sFncPutLog(TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"分注結果ファイルデータ        [id2 = '%s', id2pos = %d]", 
							strBunchuTB.id2, strBunchuTB.id2pos );

						sFncPutLog(TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"検体属性テーブルからID2を取得 [id2 = '%s', id2pos = %d] BUNCHU[UTKYMD='%s', IRINO='%s', ZSSDINO=%d, SRIYMD='%s', KNTNO='%s', SMPCD='%s', KMKCD='%s']",
							cId2, iId2pos, strBunchuTB.utkymd, strBunchuTB.irino, strBunchuTB.zssdino, strBunchuTB.sriymd,
							strBunchuTB.kntno, strBunchuTB.smpcd, strBunchuTB.kmkcd);

						// ID2, ID2POSを書き換える
						memcpy(strBunchuTB.id2, cId2, sizeof(cId2));
						strBunchuTB.id2pos = iId2pos;
						//ソートキー再計算
						strBunchuTB.srtkey = AbunGetSort(pst_Env, strBunchuTB.id2, strBunchuTB.bnckka);
					} else {
						if( ret < 0 )
						{
							if( pIrai != NULL ) {
								ZbmlFree(pIrai);
								pIrai = NULL;
							}
							if( pKanjya != NULL ) {
								ZbmlFree(pKanjya);
								pKanjya = NULL;
							}
							if( pIrai2 != NULL ) {
								ZbmlFree(pIrai2);
								pIrai2 = NULL;
							}
							sFncPutLog(TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"SELECT KENZOK[%s %s %d] [SQLCODE=%d]", 
								strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.zssdino, ret );
							ZdbRollback();
							return( 10 );
						}
						else if( ret == HRC_SQL_NOT_FOUND )
						{
							sFncPutLog(TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"検体属性テーブルにレコードが見つからないので、ID2変更なし");
						} else {
							sFncPutLog(TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"検体属性テーブル SELECT ret[%d]", ret);
						}
					}
				}
				// 2008-03-24 新フロンティア対応 INS END
				
				ABunchuChk(&strBunchuTB);
				//分注結果情報テーブルにINSERT
				sFncPutLog(TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"分注結果情報テーブルにINSERT");
				if( (ret = ABunBunIns(&strBunchuTB)) != HRC_SQL_NORMAL ) 
				{
					if( ret != -803 ) {	//2006-04-23 BUGG FIX
						if( pIrai != NULL ) {
							ZbmlFree(pIrai);
							pIrai = NULL;
						}
						if( pKanjya != NULL ) {
							ZbmlFree(pKanjya);
							pKanjya = NULL;
						}
						// 2008-01-07 新フロンティア対応 INS START
						if( pIrai2 != NULL ) {
							ZbmlFree(pIrai2);
							pIrai2 = NULL;
						}
						// 2008-01-07 新フロンティア対応 INS END
						sFncPutLog(TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"INSERT BUNCHU[%s %s %s %s] [SQLCODE=%d]", 
							strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.smpcd, 
							strBunchuTB.kmkcd, ret );
						ZdbRollback();
						return(10);
					} else {
						//分注OKの場合はUPDATEする
						sFncPutLog(TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
                            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                            "iOdrMkFlg<%d==0>なら分注OKの場合はUPDATEする",iOdrMkFlg);
						if( iOdrMkFlg == 0 ) {
							if( (ret=ABunUpdate( &strBunchuTB )) != HRC_SQL_NORMAL ) {
								if( pIrai != NULL ) {
									ZbmlFree(pIrai);
									pIrai = NULL;
								}
								if( pKanjya != NULL ) {
									ZbmlFree(pKanjya);
									pKanjya = NULL;
								}
								// 2008-01-07 新フロンティア対応 INS START
								if( pIrai2 != NULL ) {
									ZbmlFree(pIrai2);
									pIrai2 = NULL;
								}
								// 2008-01-07 新フロンティア対応 INS END
								sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
									EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"INSERT BUNCHU[%s %s %s %s] [SQLCODE=%d]", 
									strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.smpcd, 
									strBunchuTB.kmkcd, ret );
								ZdbRollback();
								return(10);
							}
						} else {
							// 3.02 ADD STA
							// 事前検体対応 bgroup=='3' AND bnckka=='OK' -> UPDATE
							if (( iBgroupFlg == 1 )
								&& (( strBunchuTB.bnckka=='0' )||(strBunchuTB.bnckka=='4' ))){
								sFncPutLog(TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
									EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"事前対応 UPDATE BUNCHU[%s %s %s %s]", 
									strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.smpcd, 
									strBunchuTB.kmkcd );
								// -803対応を行ったFLGセット(KENZOK,NINSIKIも同様の考慮を行うため)
								iDupFlg=1;
								if( (ret=ABunUpdate( &strBunchuTB )) != HRC_SQL_NORMAL ) {
									if( pIrai != NULL ) {
										ZbmlFree(pIrai);
										pIrai = NULL;
									}
									if( pKanjya != NULL ) {
										ZbmlFree(pKanjya);
										pKanjya = NULL;
									}
									// 2008-01-07 新フロンティア対応 INS START
									if( pIrai2 != NULL ) {
										ZbmlFree(pIrai2);
										pIrai2 = NULL;
									}
									// 2008-01-07 新フロンティア対応 INS END
									sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
										EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
										"INSERT BUNCHU[%s %s %s %s] [SQLCODE=%d]", 
										strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.smpcd, 
										strBunchuTB.kmkcd, ret );
									ZdbRollback();
									return(10);
								}
							} else {
							// 3.02 ADD END

								if( pIrai != NULL ) {
									ZbmlFree(pIrai);
									pIrai = NULL;
								}
								if( pKanjya != NULL ) {
									ZbmlFree(pKanjya);
									pKanjya = NULL;
								}
								// 2008-01-07 新フロンティア対応 INS START
								if( pIrai2 != NULL ) {
									ZbmlFree(pIrai2);
									pIrai2 = NULL;
								}
								// 2008-01-07 新フロンティア対応 INS END
								//エラーファイルに書き込む
								sFncPutLog(TRCKIND_WARNING,__FILE__,"dBunchu_ins",__LINE__,
									EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"INSERT BUNCHU[処理日:%s 検体:%s smpcd:%s kmkcd:%s] [SQLCODE=%d]", 
									strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.smpcd,
									strBunchuTB.kmkcd, ret ); 
								ZdbRollback();
								return(8);
							} // 3.02 ADD
						}
					}
				}
				//YOON 2007-02-19
				if( iOdrMkFlg == 3 ) {
					sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"分注のみ作成モード(iOdrMkFlg=%d)",iOdrMkFlg);
					break;		//分注のみ作成モード
				}
				if( iOdrMkFlg == 0 ) 
				{		
					//検査オーダ情報作成
					sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
                        EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                        "検査オーダ情報作成(iOdrMkFlg:%d)",iOdrMkFlg);
					if( (ret = AbufInsOrder(pst_Env, &pIraiW, &strBunchuTB, pKanjya, &pOrder)) < 0 ) {
						if( ret != -803 ) {
							sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, 
								strBunchuTB.utkymd, strIraiTB.kntno, strIraiTB.irino,
								"", "検査オーダ情報作成エラー");
							ZdbRollback();
							if( pIrai != NULL ) {
								ZbmlFree(pIrai);
								pIrai = NULL;
							}
							if( pKanjya != NULL ) {
								ZbmlFree(pKanjya);
								pKanjya = NULL;
							}
							// 2008-01-07 新フロンティア対応 INS START
							if( pIrai2 != NULL ) {
								ZbmlFree(pIrai2);
								pIrai2 = NULL;
							}
							// 2008-01-07 新フロンティア対応 INS END
							sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"INSERT KENORDER[%s %s %s %s] [SQLCODE=%d]", 
								strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.smpcd, 
								strBunchuTB.kmkcd, ret );
							return( 10 );
						} else {
							sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, strBunchuTB.utkymd, 
								strBunchuTB.kntno, strBunchuTB.irino, buf2, "検査オーダ重複");
						}
					}
					//即時チェック情報作成
					if( AbunInsChk(pst_Env, &pOrder,  pKanjya) < 0 ) {
						if( ret != -803 ) {
							//エラーログ出力
							sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, strBunchuTB.utkymd, 
								strIraiTB.kntno, strIraiTB.irino, buf2, "検査オーダ追加エラー[%d]", ret);
							ZdbRollback();
							if( pIrai != NULL ) {
								ZbmlFree(pIrai);
								pIrai = NULL;
							}
							if( pKanjya != NULL ) {
								ZbmlFree(pKanjya);
								pKanjya = NULL;
							}
							// 2008-01-07 新フロンティア対応 INS START
							if( pIrai2 != NULL ) {
								ZbmlFree(pIrai2);
								pIrai2 = NULL;
							}
							// 2008-01-07 新フロンティア対応 INS END
							sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"INSERT REALCHK[%s %s %s %s] [SQLCODE=%d]", 
								strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.smpcd, 
								strBunchuTB.kmkcd, ret );
							return( 10 );
						} else {
							sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, strBunchuTB.utkymd, 
								strBunchuTB.kntno, strBunchuTB.irino, buf2, "即時チェック重複");
						}
					}
				}
			}
			iSkipFlg = 0;
			//元に戻す
			//if( pIraiW1 != NULL ) pIraiW = pIraiW1;
			memset(&pIraiW, 0, sizeof(Irai));
			memcpy(&pIraiW, (pIrai+k), sizeof(Irai));
			//自動依頼発生処理
			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"自動依頼発生処理");

			for( ; l < g_iJdkmk ;++l ) {
				if( !memcmp(pIraiW.knsgrp, (g_strJdkmk+l)->knsgrp, 16) &&
					!memcmp(pIraiW.kmkcd, (g_strJdkmk+l)->kmkcd, 7) &&
					(memcmp(pIraiW.sriymd, (g_strJdkmk+l)->kaiymd, 10) >= 0) )
					break;
			}

			if( l < g_iJdkmk ) {
				//取得依頼の中に含まれているかを確認
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"取得依頼の中に含まれているかを確認");
	
				for( m=0; m < iIrai ;++m ) {
					if( !memcmp((pIrai+m)->kmkcd,  (g_strJdkmk+l)->jkmkcd, 7) ){
						//pIraiW1 = pIraiW;
						//pIraiW = pIrai+m;
						//処理済み記しがある場合は処理スキップ
						if( (pIrai+m)->odrssflg == 'F' ) {
							iSkipFlg = 2;
							break;
						}
/*
						if( iOdrMkFlg == 0 ) [
							(pIrai+m)->odrssflg = '2';
						] else [
							(pIrai+m)->odrssflg = '1';
						]
*/
						//元に戻す
						memset(&strBunchuTB, 0, sizeof(Bunchu));
						memcpy(&strBunchuTB, &pBunW, sizeof(Bunchu));
						(pIrai+m)->odrssflg = pIraiW.odrssflg;
						strcpy((pIrai+m)->sriymd, strBunchuTB.sriymd);
						strcpy((pIrai+m)->knskisyymd, sWknsStart);
						memcpy((pIrai+m)->knsgrp, (g_strJdkmk+l)->jknsgrp, 16);

						memset(&pIraiW, 0, sizeof(Irai));
						memcpy(&pIraiW, (pIrai+m), sizeof(Irai));
						(pIrai+m)->odrssflg = 'F';	//もうやったよ。
						memcpy(strBunchuTB.kmkcd, (g_strJdkmk+l)->jkmkcd, 7);
						iSkipFlg = 1;
						if( iFukuFlg == 1 ) {
							//複数本優先度確認
							// 2.01 DELL if( (iRet = chkBunchu( pst_Env, iOdrMkFlg, &strBunchuTB, pIraiW.knsgrp )) < 0 ) [
							/*DEBUG STA -----------------------------------------------*/
							sFncPutLog ( TRCKIND_DEBUG, __FILE__
								, "dBunchu_ins", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"chkBunchu IN 自動依頼発生処理 [%d][%s %s %s %s %s]", 
								iDBBunUpflg,
								strBunchuTB.sriymd, strBunchuTB.utkymd, 
								strIraiTB.kntno, strIraiTB.irino,(pIrai+k)->kmkcd );
							/*DEBUG END -----------------------------------------------*/
							//YOON 2007-02-15
							if((iRet = chkBunchu(pst_Env,iOdrMkFlg,&strBunchuTB, 
								pIraiW.knsgrp,iDBBunUpflg)) < 0 ) {
								sFncPutLog ( TRCKIND_DEBUG, __FILE__
                                	, "dBunchu_ins", __LINE__,
                                	EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                                	"chkBunchu IN 処理エーら");
								ZdbRollback();
								return( -1 );
							}
							if( iOdrMkFlg != 0 ) {
								if( pIraiW.odrssflg != '2' )
									pIraiW.odrssflg = '1';
								// CHG E.Osada 2006-08-30
								//if( iRet == 1 ) [
								if( iRet != 2 ) {
									iOdrMkFlg = 1;
								} else {
									//複数本取り対象の場合は分注結果に'1'をセット 2006-06-13 E.osada
									strBunchuTB.bnckka = '1';
									//ソートキー再計算
									strBunchuTB.srtkey=AbunGetSort(pst_Env,strBunchuTB.id2, 
												strBunchuTB.bnckka);
									iOdrMkFlg = 3;
								}
							}
						}
						break;
					}
				}
/*
				if( iSkipFlg = 2 ) {
					iSkipFlg = 0;
					break;
				}
*/
				if( !iSkipFlg ) {
					//pIraiW1 = pIraiW;
					//元に戻す
					memset(&strBunchuTB, 0, sizeof(Bunchu));
					memcpy(&strBunchuTB, &pBunW, sizeof(Bunchu));
					memcpy(strBunchuTB.kmkcd, (g_strJdkmk+l)->jkmkcd, 7);
					memcpy(pIraiW.kmkcd, (g_strJdkmk+l)->jkmkcd, 7);
					memcpy(pIraiW.oyakmkcd, (g_strJdkmk+l)->jkmkcd, 7);
					memcpy(pIraiW.knsgrp, (g_strJdkmk+l)->jknsgrp, 16);
					pIraiW.irihsmkbn = '2';
					pIraiW.srinycd = '2';
					pIraiW.bkfkkbn = '0';
					//基準値No取得
					memset(sKjNo, 0, sizeof(sKjNo));
					iKetasu = 0;
					if( GetKjnNo(pIraiW.kmkcd, pIraiW.stsrcd,pKanjya->age,pKanjya->agekbn,
							pIraiW.sriymd, sKjNo, &iKetasu) == 1) {
						strcpy(pIraiW.kjno, sKjNo);
					}
					if( iFukuFlg == 1 ) {
						//複数本優先度確認
						// 2.01 DELL if( (iRet = chkBunchu( pst_Env, iOdrMkFlg, &strBunchuTB, pIraiW.knsgrp )) < 0 ) [
						/*DEBUG STA ---------------------------------------------------*/
						sFncPutLog ( TRCKIND_DEBUG, __FILE__
							, "dBunchu_ins", __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"chkBunchu IN 依頼関連 [%d][%s %s %s %s %s]", 
							iDBBunUpflg,
							strBunchuTB.sriymd, strBunchuTB.utkymd, 
							strIraiTB.kntno, strIraiTB.irino,(pIrai+k)->kmkcd );
						/*DEBUG END ---------------------------------------------------*/
						//YOON 2007-02-15
						if((iRet = chkBunchu(pst_Env,iOdrMkFlg,&strBunchuTB, 
							pIraiW.knsgrp,iDBBunUpflg)) < 0 ) {
							sFncPutLog ( TRCKIND_DEBUG, __FILE__
                                    , "dBunchu_ins", __LINE__,
                                    EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                                    "chkBunchu IN 処理エーら");
							ZdbRollback();
							return( -1 );
						}
						if( iOdrMkFlg != 0 ) {
							if( pIraiW.odrssflg != '2' )
								pIraiW.odrssflg = '1';
							// CHG E.Osada 2006-08-30
							//if( iRet == 1 ) [
							if( iRet != 2 ) {
								iOdrMkFlg = 1;
							
							} else {
								//複数本取り対象の場合は分注結果に'1'をセット 2006-06-13 E.osada
								strBunchuTB.bnckka = '1';
								//ソートキー再計算
								strBunchuTB.srtkey = AbunGetSort(pst_Env, strBunchuTB.id2, 
											strBunchuTB.bnckka);
								iOdrMkFlg = 3;
							}
						}
					}
					
					//取得依頼にない場合はINSERTする
					if( (ret = A105insIrai(&pIraiW)) < 0 ) {
						if( ret != -803 ) {
							//エラーログ出力
							sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, strBunchuTB.utkymd, 
							strIraiTB.kntno, strIraiTB.irino, buf2, "検査オーダ追加エラー[%d]", ret);
							ZdbRollback();
							if( pIrai != NULL ) {
								ZbmlFree(pIrai);
								pIrai = NULL;
							}
							if( pKanjya != NULL ) {
								ZbmlFree(pKanjya);
								pKanjya = NULL;
							}
							// 2008-01-07 新フロンティア対応 INS START
							if( pIrai2 != NULL ) {
								ZbmlFree(pIrai2);
								pIrai2 = NULL;
							}
							// 2008-01-07 新フロンティア対応 INS END
							sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"INSERT IRAI[%s %s %s %s] [SQLCODE=%d]", 
								strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.smpcd, 
								strBunchuTB.kmkcd, ret );
							return( 10 );
						}
					}
					iSkipFlg = 1;
				} else if( iSkipFlg == 1 ) {
					//依頼テーブル更新
					if( (ret = ABunKnsgrpUpdate( &pIraiW )) < 0 ) {
						if( ret != -803 ) {
							//エラーログ出力
							sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, 
								strBunchuTB.utkymd, strIraiTB.kntno, strIraiTB.irino, 
								(pIrai+k)->kmkcd, "依頼情報更新エラー[%d] KNSGRP[%s]", 
								ret, (pIrai+k)->knsgrp);
							ZdbRollback();
							if( pIrai != NULL ) {
								ZbmlFree(pIrai);
								pIrai = NULL;
							}
							if( pKanjya != NULL ) {
								ZbmlFree(pKanjya);
								pKanjya = NULL;
							}
							// 2008-01-07 新フロンティア対応 INS START
							if( pIrai2 != NULL ) {
								ZbmlFree(pIrai2);
								pIrai2 = NULL;
							}
							// 2008-01-07 新フロンティア対応 INS END
							sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"UPDATE IRAI[%s %s %s %s] [SQLCODE=%d]", 
								strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.smpcd, 
								strBunchuTB.kmkcd, ret );
							return( 10 );
						}
					}
				}
				++l;
			}

			if( !iSkipFlg & !iOya ) {
				//親子関係の場合は親も展開する			
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"親子関係の場合は親も展開する iOdrMkFlg:%d",iOdrMkFlg);
				if( memcmp(pIraiW.kmkcd, pIraiW.oyakmkcd, 7) ) 
				{
					//取得依頼の中に含まれている親を取り出す
					sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"取得依頼の中に含まれている親を取り出す");
				
					for( m=0; m < iIrai ;++m ) {
						if( !memcmp((pIrai+m)->kmkcd,  pIraiW.oyakmkcd, 7) ){
							//pIraiW1 = pIraiW;
							//pIraiW = pIrai+m;
							//memcpy(pIraiW->kmkcd, pIraiW1->oyakmkcd, 7);
							//memcpy(pIraiW->knsgrp, pIraiW1->knsgrp, 16);
							//処理済み記しがある場合は処理スキップ
							if( (pIrai+m)->odrssflg == 'F' ) {
								iSkipFlg = 0;
								break;
							}
							//元に戻す
							memset(&strBunchuTB, 0, sizeof(Bunchu));
							memcpy(&strBunchuTB, &pBunW, sizeof(Bunchu));
							memcpy((pIrai+m)->knsgrp, sWknsgrp, 16);
							if( iOdrMkFlg == 0 ) {
								(pIrai+m)->odrssflg = '2';
							} else {
								(pIrai+m)->odrssflg = '1';
							}
							strcpy((pIrai+m)->knskisyymd, sWknsStart);
							memset(&pIraiW, 0, sizeof(Irai));
							memcpy(&pIraiW, (pIrai+m), sizeof(Irai));
							(pIrai+m)->odrssflg = 'F';	//もうやったよ。
							memcpy(strBunchuTB.kmkcd, pIraiW.kmkcd, 7);
							iSkipFlg = 1;
							break;
						}
					}
					if( iSkipFlg == 1 ) {
						if( iFukuFlg == 1 ) {
							//複数本優先度確認
							// 2.01 DELL if( (iRet = chkBunchu( pst_Env, iOdrMkFlg, &strBunchuTB, pIraiW.knsgrp )) < 0 ) [
							/*DEBUG STA ----------------------------------------------*/
							sFncPutLog ( TRCKIND_DEBUG, __FILE__
								, "dBunchu_ins", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"chkBunchu IN 親子関係 [%d][%s %s %s %s %s]", 
								iDBBunUpflg,
								strBunchuTB.sriymd, strBunchuTB.utkymd, 
								strIraiTB.kntno, strIraiTB.irino,(pIrai+k)->kmkcd );
							/*DEBUG END ----------------------------------------------*/
							//YOON 2007-02-15
							if((iRet=chkBunchu(pst_Env,iOdrMkFlg,&strBunchuTB, 
								pIraiW.knsgrp,iDBBunUpflg)) < 0 ) {
								sFncPutLog ( TRCKIND_DEBUG, __FILE__
                                    , "dBunchu_ins", __LINE__,
                                    EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                                    "chkBunchu IN 処理エラー");							
	
								ZdbRollback();
								return( -1 );
							}
							if( iOdrMkFlg != 0 ) {
								if( pIraiW.odrssflg != '2' )
									pIraiW.odrssflg = '1';
								// CHG E.Osada 2006-08-30
								//if( iRet == 1 ) [
								if( iRet != 2 ) {
									iOdrMkFlg = 1;
								} else {
									//複数本取り対象の場合は分注結果に'1'をセット 2006-06-13 E.osada
									strBunchuTB.bnckka = '1';
									//ソートキー再計算
									strBunchuTB.srtkey = AbunGetSort(pst_Env, strBunchuTB.id2, 
												strBunchuTB.bnckka);
									iOdrMkFlg = 3;
								}
							}
						}
						//依頼テーブル更新
						if( (ret = ABunKnsgrpUpdate( &pIraiW )) < 0 ) {
							if( ret != -803 ) {
								//エラーログ出力
								sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, 
									strBunchuTB.utkymd, strIraiTB.kntno, strIraiTB.irino, 
									pIraiW.kmkcd, "依頼情報更新エラー[%d] KNSGRP[%s]", 
									ret, pIraiW.knsgrp);
								ZdbRollback();
								if( pIrai != NULL ) {
									ZbmlFree(pIrai);
									pIrai = NULL;
								}
								if( pKanjya != NULL ) {
									ZbmlFree(pKanjya);
									pKanjya = NULL;
								}
								// 2008-01-07 新フロンティア対応 INS START
								if( pIrai2 != NULL ) {
									ZbmlFree(pIrai2);
									pIrai2 = NULL;
								}
								// 2008-01-07 新フロンティア対応 INS END
								sFncPutLog(TRCKIND_WARNING,__FILE__,"dBunchu_ins",__LINE__,
									EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"UPDATE IRAI[%s %s %s %s] [SQLCODE=%d]", 
									strBunchuTB.sriymd,strBunchuTB.kntno,strBunchuTB.smpcd, 
									strBunchuTB.kmkcd, ret );
								return( 10 );
							}
						}
					}
				}
			}
			if( !iSkipFlg )
			{
				break;
			}
		}
		//コミット 性能UPのため実行 2006-06-22 E.Osada
//		ZdbCommit();
//		 sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
//                EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//                "COMMIT");
		//処理済み記しをする。
		(pIrai+k)->odrssflg = 'F';

	}
	//元に戻す
	memset(&strBunchuTB, 0, sizeof(Bunchu));
	memcpy(&strBunchuTB, &pBunW, sizeof(Bunchu));

	//検体属性情報作成
	// 3.02 UPD 事前対応-803の判定はAbunInsZokuseiにて行う
	//if( (ret = AbunInsZokusei(pst_Env, &strBunchuTB, pKanjya)) < 0 ) [
	if( (ret = AbunInsZokusei(pst_Env, &strBunchuTB, pKanjya, iDupFlg )) < 0 ) {
		if( ret != -803 ) {
			sFuncPutErrlist(pst_Env,sFLname,iFLcnt,strBunchuTB.sriymd, strBunchuTB.utkymd, 
				strIraiTB.kntno, strIraiTB.irino, buf2, "検体属性情報追加エラー[%d]", ret);
			ZdbRollback();
			if( pIrai != NULL ) {
				ZbmlFree(pIrai);
				pIrai = NULL;
			}
			if( pKanjya != NULL ) {
				ZbmlFree(pKanjya);
				pKanjya = NULL;
			}
			// 2008-01-07 新フロンティア対応 INS START
			if( pIrai2 != NULL ) {
				ZbmlFree(pIrai2);
				pIrai2 = NULL;
			}
			// 2008-01-07 新フロンティア対応 INS END
			sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"INSERT KENZOK[%s %s %s %s] [SQLCODE=%d]", 
				strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.smpcd, 
				strBunchuTB.kmkcd, ret );
			return( 10 );
		}
	}

	//認識情報作成
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		"認識情報作成 複数(1)と同じ(%d)ならiOdrMkFlgを(2)にセット",iFukuFlg);
	iOldFlg = iOdrMkFlg;
	if( iFukuFlg == 1 ){	
 
		iOdrMkFlg = 2;
	}
	// 3.02 UPD 事前対応-803の判定はAbunInsZokuseiにて行う
	//if( (ret = AbunInsNinsiki(pst_Env, &strBunchuTB, iOdrMkFlg)) < 0 ) [
	if( (ret = AbunInsNinsiki(pst_Env, &strBunchuTB, iOdrMkFlg, iDupFlg )) < 0 ) {
		if( ret != -803 ) {
			sFuncPutErrlist(pst_Env, sFLname,iFLcnt,strBunchuTB.sriymd, strBunchuTB.utkymd, 
				strIraiTB.kntno, strIraiTB.irino, buf2, "認識情報追加エラー[%d]", ret);
			ZdbRollback();
			if( pIrai != NULL ) {
				ZbmlFree(pIrai);
				pIrai = NULL;
			}
			if( pKanjya != NULL ) {
				ZbmlFree(pKanjya);
				pKanjya = NULL;
			}
			// 2008-01-07 新フロンティア対応 INS START
			if( pIrai2 != NULL ) {
				ZbmlFree(pIrai2);
				pIrai2 = NULL;
			}
			// 2008-01-07 新フロンティア対応 INS END
			sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"INSERT NINSIKI[%s %s %s %s] [SQLCODE=%d]", 
				strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.smpcd, 
				strBunchuTB.kmkcd, ret );
			return( 10 );
		}
	}

	iOdrMkFlg = iOldFlg;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		"iOdrMkFlg(%d)==0ならトレー＆ラック情報編集処理",iOdrMkFlg);

//	if( !iOdrMkFlg ) 
// Upd 2007.05.10 waj
//	if( sakitukeFileFlg) 
// 2008-01-07 新フロンティア対応 UPD START
//	if( (!iOdrMkFlg) && (iBgroupFlg == 0) )
//	{	//分注エラーの場合はオーダ作成しない
//		//トレー＆ラック情報編集処理(搬送機への先付け情報送信用)
//		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
//			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//			"トレー＆ラック情報編集処理(搬送機への先付け情報送信用");
//		if( *strKenPos != NULL ) {
//			for( i=0; i < *iKenPos ;++i ) {
//				if( !strcmp((*strKenPos+i)->sTryID, strBunchuTB.trid) ) {
//					ialloc = 1;
//					iPoint = i;
//					pTray = *strKenPos;
//					break;
//				}
//				if( ialloc == 1 ) break;
//			}
//		}
//		if( ialloc == 0 ) {
//			//*strKenPos = (TRAY *)ZbmlRealloc((TRAY *)*strKenPos, sizeof(TRAY) * (*iKenPos + 1));
//			*strKenPos = (TRAY *)realloc((TRAY *)*strKenPos, sizeof(TRAY) * (*iKenPos + 1));
//			*iKenPos += 1;
//			iPoint = *iKenPos - 1;
//			pTray = *strKenPos;
//			memset((pTray+iPoint), 0, sizeof(TRAY));
//			strcpy((pTray+iPoint)->sTryID, strBunchuTB.trid);
//			ZbmlChgAPDate((pTray+iPoint)->sStDate, strBunchuTB.sriymd);
//			// Upd 2007.05.10 waj
//			// strcpy((pTray+iPoint)->sPutDir, pst_Env->sPutDir);
//			{ // ここで先付情報ファイル格納ディレクトリをトレイ情報から取得し設定する
//			    Trmst   strTr,  *pTr = NULL;
//				int		num = 0;
//
//			    memset(&strTr, 0, sizeof(Trmst));
//			    memcpy(strTr.trhdid, strBunchuTB.trid, 4);
//			    strcpy(strTr.kaiymd,  strBunchuTB.sriymd);
//			    if( ret = A105trmstSelectKey(&strTr, &pTr, &num) != 0 ) {
//			        sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
//			            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//			            "SELECT Trmst[SQLCODE=%d]", ret ) ;
//			        return( -1 );
//			    }
//        		strcpy(pst_Env->sPutDir, pTr->filskdir);
//				strcpy((pTray+iPoint)->sPutDir, pst_Env->sPutDir);
//		        ZbmlFree(pTr);
//		        pTr = NULL;
//			}
//			strcpy((pTray+iPoint)->sPutDir, pst_Env->sPutDir);
//			(pTray+iPoint)->iMaxSeq = 0;
//			(pTray+iPoint)->iMinSeq = 99999;
//			(pTray+iPoint)->iKntSuu = 0;
//			for ( i=0; i < MAXPOSOLD+1 ;++i ) {
//				memset( (pTray+iPoint)->strPosInfo[i].sUkeDate, ' ', 
//						sizeof((pTray+iPoint)->strPosInfo[i].sUkeDate)-1);
//				memset( (pTray+iPoint)->strPosInfo[i].sKentaiID, ' ', 
//						sizeof((pTray+iPoint)->strPosInfo[i].sKentaiID)-1);
//				memset( (pTray+iPoint)->strPosInfo[i].sIraiNo, ' ', 
//						sizeof((pTray+iPoint)->strPosInfo[i].sIraiNo)-1);
//				memset( (pTray+iPoint)->strPosInfo[i].sKenSybt, ' ', 
//						sizeof((pTray+iPoint)->strPosInfo[i].sKenSybt)-1);
//			}
//		}
//		(pTray+iPoint)->iKntSuu += 1;
//		if( (pTray+iPoint)->iMaxSeq <= pOrder.knsseq )
//			(pTray+iPoint)->iMaxSeq = pOrder.knsseq;
//		if( (pTray+iPoint)->iMinSeq >= pOrder.knsseq )
//			(pTray+iPoint)->iMinSeq = pOrder.knsseq;
//		ZbmlStrCpy((pTray+iPoint)->strPosInfo[strBunchuTB.asyrckpos].sUkeDate, 
//			pBunchu->sUkebiBML, sizeof(pBunchu->sUkebiBML));
//		ZbmlStrCpy((pTray+iPoint)->strPosInfo[strBunchuTB.asyrckpos].sKentaiID, strBunchuTB.kntno, sizeof(strBunchuTB.kntno)-1);
//		ZbmlStrCpy((pTray+iPoint)->strPosInfo[strBunchuTB.asyrckpos].sIraiNo, strIraiTB.irino, sizeof(strIraiTB.irino)-1);
//		(pTray+iPoint)->strPosInfo[strBunchuTB.asyrckpos].sKenSybt[0] = pBunchu->sKnsSyrui[0];
//	}
	if( (!iOdrMkFlg) && (iBgroupFlg == 0) )
	{	//分注エラーの場合はオーダ作成しない
		//トレー＆ラック情報編集処理(搬送機への先付け情報送信用)
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"トレー＆ラック情報編集処理(搬送機への先付け情報送信用)");
		if( *strKenPos != NULL ) {
			for( i=0; i < *iKenPos ;++i ) {
				if( !strcmp((*strKenPos+i)->sRackID, strBunchuTB.asyrckid) ) {
					ialloc = 1;
					iPoint = i;
					pRack = *strKenPos;
					break;
				}
				if( ialloc == 1 ) break;
			}
		}
		if( ialloc == 0 ) {
			*strKenPos = (RACK *)realloc((RACK *)*strKenPos, sizeof(RACK) * (*iKenPos + 1));
			*iKenPos += 1;
			iPoint = *iKenPos - 1;
			pRack = *strKenPos;
			memset((pRack+iPoint), 0, sizeof(RACK));
			strcpy((pRack+iPoint)->sRackID, strBunchuTB.asyrckid);
			ZbmlChgAPDate((pRack+iPoint)->sStDate, strBunchuTB.sriymd);
			{ // ここで先付情報ファイル格納ディレクトリをラック管理マスタから取得し設定する
			    Rkmst   strRk,  *pRk = NULL;
				int		num = 0;

				memset(&strRk, 0, sizeof(Rkmst));
				memcpy(strRk.smpcd, strBunchuTB.smpcd, 4);
				strcpy(strRk.kaiymd,  strBunchuTB.sriymd);
				if( ret = A105rkmstSelectKey(&strRk, &pRk, &num) != 0 ) {
					sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"SELECT Rkmst[SQLCODE=%d]", ret ) ;
					return( -1 );
			    }
				strcpy(pst_Env->sPutDir, pRk->filskdir);
				strcpy((pRack+iPoint)->sPutDir, pst_Env->sPutDir);
				ZbmlFree(pRk);
				pRk = NULL;
			}
			strcpy((pRack+iPoint)->sPutDir, pst_Env->sPutDir);
			(pRack+iPoint)->iMaxSeq = 0;
			(pRack+iPoint)->iMinSeq = 99999;
			(pRack+iPoint)->iKntSuu = 0;
			for ( i=0; i < MAXPOS+1 ;++i ) {
				memset( (pRack+iPoint)->strPosInfo[i].sUkeDate, ' ', 
						sizeof((pRack+iPoint)->strPosInfo[i].sUkeDate)-1);
				memset( (pRack+iPoint)->strPosInfo[i].sKentaiID, ' ', 
						sizeof((pRack+iPoint)->strPosInfo[i].sKentaiID)-1);
				memset( (pRack+iPoint)->strPosInfo[i].sIraiNo, ' ', 
						sizeof((pRack+iPoint)->strPosInfo[i].sIraiNo)-1);
				memset( (pRack+iPoint)->strPosInfo[i].sKenSybt, ' ', 
						sizeof((pRack+iPoint)->strPosInfo[i].sKenSybt)-1);
			}
		}
		(pRack+iPoint)->iKntSuu += 1;
		if( (pRack+iPoint)->iMaxSeq <= pOrder.knsseq )
			(pRack+iPoint)->iMaxSeq = pOrder.knsseq;
		if( (pRack+iPoint)->iMinSeq >= pOrder.knsseq )
			(pRack+iPoint)->iMinSeq = pOrder.knsseq;
		ZbmlStrCpy((pRack+iPoint)->strPosInfo[strBunchuTB.asyrckpos].sUkeDate, 
			pBunchu->sUkebiBML, sizeof(pBunchu->sUkebiBML));
		ZbmlStrCpy((pRack+iPoint)->strPosInfo[strBunchuTB.asyrckpos].sKentaiID, strBunchuTB.kntno, sizeof(strBunchuTB.kntno)-1);
		ZbmlStrCpy((pRack+iPoint)->strPosInfo[strBunchuTB.asyrckpos].sIraiNo, strIraiTB.irino, sizeof(strIraiTB.irino)-1);
		(pRack+iPoint)->strPosInfo[strBunchuTB.asyrckpos].sKenSybt[0] = pBunchu->sKnsSyrui[0];
	}
// 2008-01-07 新フロンティア対応 UPD END
	//コミット
	ZdbCommit();
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"TRANSACTION COMMIT");

	// ADD E.Osada 2006-09-16
	if( pIrai != NULL ) {
		ZbmlFree(pIrai);
		pIrai = NULL;
	}
	if( pKanjya != NULL ) {
		ZbmlFree(pKanjya);
		pKanjya = NULL;
	}
// 2008-01-07 新フロンティア対応 INS START
	if( pIrai2 != NULL ) {
		ZbmlFree(pIrai2);
		pIrai2 = NULL;
	}
// 2008-01-07 新フロンティア対応 INS END
	//
	//トレースログ
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function");

	//fclose(fp);

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
sFncTrFileRead ( pst_Env, pc_trFileName, pst_trInfo )
struct bunchuEnv	*pst_Env ;
char				*pc_trFileName ;
Flbun  		*pst_trInfo ;
{
	FILE	*lfp ;
	char	 lc_recBuf[BUNCHU_RECV_RECSIZE+1] ;
	char	sTrFileName[1024];
	char	*lpc_p ;
	char	 lcbuf[256] ;
	int		 li_idx, iRet, i, ilen, iRecCnt;
// 2008-01-07 新フロンティア対応 UPD START
//	TRAY *strKenPos;
	RACK *strKenPos;
// 2008-01-07 新フロンティア対応 UPD END
	int		iKenPos;
	int 	iLine;
	char	sDttm[128];

	//トレースログ
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "sFncTrFileRead", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "Start Function filename=%s", pc_trFileName);

	// 2008-02-18 ファイルのクローズが入っていない箇所が多数あったので追加

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

	memset(sDttm, 0, sizeof(sDttm));
	nowdateget1( sDttm );
   	sFncPutLog ( TRCKIND_OPT, "", "", 0,
         EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		 "    START(%s) 【%s】", sDttm, sTrFileName);
	iRecCnt = 0;
	//	読み込み
	while ( fgets ( lc_recBuf, sizeof ( lc_recBuf ), lfp ) != NULL ) {
		iLine++;
		if((iRet=dBunchu_ins(pst_Env,lc_recBuf,&strKenPos,&iKenPos,sTrFileName,iLine))<0){
			//2006-12-14 YOON
			AerrFilePut4( pst_Env,lc_recBuf,sTrFileName);
			if ( lfp != NULL ) {
				//	ファイルクローズ
				fclose ( lfp ) ;
			}
			return(iRet);
		}

		if( iRet == 10 ) {
			if( AerrFilePut1(pst_Env, lc_recBuf) < 0 ) {
				if ( lfp != NULL ) {
					//	ファイルクローズ	
					fclose ( lfp ) ;
				}
				return( -1 );
			}
		} else if( iRet == 11 ) {
			if( AerrFilePut2(pst_Env, lc_recBuf) < 0 ) {
				if ( lfp != NULL ) {
					//	ファイルクローズ	
					fclose ( lfp ) ;
				}
				return( -1 );
			}
		} else if( iRet == 8 ) {
			if( AerrFilePut3(pst_Env, lc_recBuf) < 0 ) {
				if ( lfp != NULL ) {
					//	ファイルクローズ	
					fclose ( lfp ) ;
				}
				return( -1 );
			}
		} else {
			if( iRet ) {
				if( AerrFilePut(pst_Env, lc_recBuf) < 0 ) {
					if ( lfp != NULL ) {
						//	ファイルクローズ	
						fclose ( lfp ) ;
					}
					return( -1 );
				}
			}
		}
		++iRecCnt;
		memset(lc_recBuf, 0, BUNCHU_FILE_SIZE+1);
	}
	memset(sDttm, 0, sizeof(sDttm));
	nowdateget1( sDttm );
   	sFncPutLog ( TRCKIND_OPT, __FILE__, "", __LINE__,
         EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		 "    END(%s)   【%s RECORD No %d 】", sDttm, sTrFileName, iRecCnt);

	if( iKenPos == 0 ){
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__,
			 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "iKenPosが0と同じですので0を返します。");

		if ( lfp != NULL ) {
			//	ファイルクローズ	
			fclose ( lfp ) ;
		}

		return( 0 );
	}
	
	//トレーNoファイル作成(過渡期)
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__,
         EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
         "トレーNoファイル作成(過渡期)");
	if( dBunCrTryfile(pst_Env, strKenPos, iKenPos) < 0 ) {
		//エラーログ出力
	}
	ZbmlFree(strKenPos);

	//	ファイルクローズ	
	fclose ( lfp ) ;

	//トレースログ
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "sFncTrFileRead", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function");

	return ( 0 ) ;
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

/*
		//識別チェック
		if ( memcmp ( pdirEnt->d_name, 
					  BUNCHU_RECV_KIND, 
					  strlen ( BUNCHU_RECV_KIND ) ) != 0 ) {
			return ( 0 ) ;
		}
*/
		//拡張子チェック
		if ( memcmp ( &(pdirEnt->d_name[li_len-strlen(BUNCHU_RECV_SFX)]), 
					  BUNCHU_RECV_SFX, 
					  strlen ( BUNCHU_RECV_SFX ) ) != 0 ) {
			return ( 0 ) ;
		}

		return ( 1 ) ;
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

#ifdef _DEBUG_
	printf("%d,%s\n",plLineNo,gstLogMem.pcMsg);
#endif

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
/******************************************************************************/
/*  関 数 名　：sFncChkDigit()												  */
/*  機能概要　：元検体ラックID数値チェック関数								  */
/*  入　　力　：															  */
/*　 第１引数 ：char * 		チェック文字列									  */
/*  出　　力　：															  */
/*  復帰情報　：int															  */
/*					0		オール数値										  */
/*					0以外	数値以外が混ざっている							  */
/******************************************************************************/
int
sFncChkDigit( pChkStr )
char	*pChkStr ;
{
	
	int		i, err ;
	char	cMotoRackId[11];

	// 変数初期化
	err = 0 ;
	memset( cMotoRackId, 0, sizeof(cMotoRackId) );

	// 不要なスペースを消す
	ZbmlInfocpy( cMotoRackId, pChkStr, sizeof(cMotoRackId) );

	// 数値かどうかチェック
	for (i = 0; i < strlen(cMotoRackId); i++)
	{
		//数値で無い場合
		if (cMotoRackId[i] < '0' || cMotoRackId[i] > '9')
		{
			err++ ;
		}
	}

	// 全て数値の場合、errは'0'を返す
	// 1つでも数値以外の文字がある場合、errはその文字数を返す
	return ( err ) ;

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
}

/** End of File ***************************************************************/
