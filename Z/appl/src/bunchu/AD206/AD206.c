/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：AD206.c                                                      */
/* 　概　　　要：分注結果変換処理                                             */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2007/06/01     YOON           新規作成                           */
/*  2.00     2009/01/06     Merits K.Ameno 施設コード増桁 通信仕様変更対応    */
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

#include "AD206.h"

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
MYAPP_STSCODE			 gintErrorCode ;
MYAPP_SYSTEM_VERSION	 gtSystemVersion ;
static	char			*gpToken ;			//	sFncTrFileToken用静的ポインタ
struct stcLogMember		 gstLogMem ;		//	ログ出力情報

int g_nKinkmmst;
struct S_KINKMMST *g_strKinkmmst ;

int g_iSyaknr;
Sysknrmst *g_strSysknr = NULL;
/* チェック文字配列 */
static char *moji[] = {
    "ｱｲ","ｵｶ","ｹｻ","ﾀｲ","ﾆｸ","ﾍｲ","ﾕｶ","ｳﾘ","ｸｲ","ｽﾐ","ﾄﾗ","ﾂｴ","ﾏﾕ","ﾘｽ","ﾎﾔ",
    "ﾆﾚ","ｱｼ","ｺﾏ","ﾀﾙ","ﾗﾝ","ｷﾈ","ｳﾀ","ｲｶ","ｻﾒ","ﾂｷ","ﾐｿ","ﾓﾔ","ﾌﾀ","ﾅﾂ","ｶｻ",
    "ﾃﾗ","ﾊﾄ","ﾐﾐ","ﾏｽ","ﾈｺ","ｵﾆ","ｱﾘ","ﾊﾀ","ﾑﾗ","ﾕﾒ","ｵﾉ","ﾕｷ","ﾊﾈ","ｶﾜ","ｲﾄ",
    "ﾁﾘ","ﾀﾈ","ﾆﾗ","ﾏﾂ","ﾖﾙ","ｱﾐ","ｲﾜ","ｸﾂ","ｽｽ","ｶｵ","ﾋﾙ","ﾑｼ","ﾀﾗ","ｺﾄ","ｵﾘ",
    "ｱｷ","ﾀｹ","ｷﾘ","ｳﾏ","ｻﾜ","ｸﾗ","ﾊｽ","ﾔﾈ","ﾕﾐ","ﾆｼ","ｺｲ","ｵｹ","ｱﾒ","ﾂﾘ","ｳﾒ",
    "ｽﾅ","ﾌｶ","ﾔﾘ","ｿﾗ","ｾﾐ","ｻｶ","ｶﾆ","ﾂﾉ","ﾏﾘ","ｶﾒ","ｼｵ","ｲﾓ","ﾊﾙ","ﾓﾁ","ﾌﾅ",
    "ﾕﾘ","ｶﾐ","ｲｼ","ｳﾆ","ｵﾔ","ｸﾘ","ｱﾕ","ﾀﾆ","ﾎｼ","ﾓﾓ","ﾌﾛ","ﾅｽ","ｸﾏ","ｽｼ","ﾃﾂ",
    "ｶﾏ","ｳｼ","ﾔﾏ","ﾅﾗ","ﾌｷ","ｳﾁ","ﾐﾂ","ﾜﾗ","ｵﾄ","ｲﾇ","ｸﾆ","ｼｶ","ﾂﾒ","ﾊｹ","ﾏﾄ",
    "ﾀｺ","ｱｻ","ｲﾀ","ｺｹ","ﾀﾏ","ﾇｶ","ﾓﾘ","ｳｽ","ｴｷ","ｸﾁ","ｼｼ","ﾊﾅ","ﾆｽ","ﾀｶ","ﾉﾘ",
    "ｻｹ","ｶﾈ","ｻﾗ","ｲﾈ","ﾊｼ","ｻｻ","ﾊﾑ","ｻｲ","ﾔｼ","ﾌﾈ","ｱﾜ","ﾀﾅ","ﾖｼ","ｿﾘ","ｸﾜ",
    "ｳﾐ","ｲｹ","ﾈﾂ","ﾎﾘ","ﾘｸ","ﾋﾓ","ﾅﾀ","ﾌｴ","ﾄﾘ","ｷｸ","ｲｴ","ﾀｷ","ﾍﾗ","ﾊﾘ","ｾｷ",
    "ｴﾗ","ｷﾇ","ｶﾓ","ｻﾙ","ｺﾅ","ﾂﾕ","ﾊﾁ","ﾏﾙ","ﾋﾚ","ｾﾘ","ﾅﾜ","ｵﾕ","ｸｼ","ﾂﾙ","ｸｻ",
    "ﾌﾕ","ﾇﾏ","ｶｷ","ｼﾏ","ﾋﾅ","ﾐﾁ","ｶｲ","ﾓﾐ","ﾄｷ","ｻｵ","ﾆﾜ","ﾉﾐ","ｽｷ","ｶﾝ","ﾏﾁ","ｶｻ","ﾂﾀ"
    };
/******************************************************************************/
/* 関数宣言                                                                   */
/******************************************************************************/
//	トレー・ラック紐付け情報関連関数
static	char*	sFncTrFileToken ( char * ) ;

//	ファイル削除
static	void	sDelOrderFile ( char *, char *, char *, char * ) ;

//	共有メモリ操作関数
static	int		sFncShmCrt ( struct appEnv * ) ;
static	int		sFncShmGet ( struct appEnv * , int *) ;
static	int		sFncShmDel ( struct appEnv * ) ;

//	コールバック関数
static	int		sFncFileCompar ( struct dirent **, struct dirent ** )  ;
static	int		sFncFileFillter ( struct dirent * ) ;

//	その他
static	int		sFncFileRename ( char *, char *, char *, char * ) ;

//	トレース用
static	void	_sFncEnvDip ( struct appEnv * ) ;

extern long KinkmmstSelectKey( char *,struct  S_KINKMMST** arrayOut, int* numOut );
//extern int selectIRAI(char *utkymd,char *irino,char *smpcd,
//		struct S_IRAI ** pRecv,int *pRecCnt);
extern int selectIRAI(char *utkymd,char *irino,char *smpcd,char *kmkcd,
		int *nLotno,int *pRecCnt);
extern int selectKANJYA(char *utkymd, char *irino,struct S_KANJYA *pRecv,int *pRecCnt);
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
initFunction( argc, argv, pAppEnv )
int					 argc ;
char				*argv[] ;
struct appEnv	*pAppEnv ;
{
	char	 lc_prmBuf[256] ;
	long	 ll_retSts ;
	char	*lc_login ;

    /***
     ***    引数チェック
     ***/
	if ( argc != 2 ) {
		fprintf ( stderr, 
			"%s(Line:%d) : There is an error in a command parameter\n", 
			MYAPP_APP_NAME,__LINE__ ) ;
		return ( -1 ) ;
	}

	/***
	 ***	ログオープン
	 ***/
	if ( ZbmlOpenLog ( argv[1] ) != 0 ) {
		printf("LogOpen Error(Line:%d)\n",__LINE__);
		return ( -1 ) ;
	}
	char *array = NULL;
	ZbmlRealloc( array, (10 )); 
	//	ログ情報初期設定
	memset ( &gstLogMem, '\0', sizeof ( gstLogMem ) ) ;
	if ( ( lc_login = getenv( "LOGNAME" ) ) != NULL ) {
		strcpy ( gstLogMem.pcLoginId, lc_login ) ;
	}
	strcpy ( gstLogMem.pcAppName, MYAPP_APP_NAME ) ;

	//	開始ログ出力
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__,
				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "プログラム起動" ) ;

	/***
	 ***	初期化	
	 ***/
	//	エラーステータス変更
	gintErrorCode = 0 ;

	//	プログラム環境変数初期化
	memset ( pAppEnv , '\0', sizeof ( struct appEnv ) ) ;

	/***
	 ***	引数チェック	
	if ( argc != 2 ) {
		gintErrorCode = MYAPP_STSCODE_ERR_USEGE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "initFunction", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "コマンドパラメータに誤りがあります" ) ;
		return ( -1 ) ;
	}
	 ***/

	/***
	 ***	パラメータファイル情報退避
	 ***/
	//	パラメータファイル名退避
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

	//	受信回収
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_BUNCHU,
						pAppEnv->cDirNR_Col ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_BUNCHU) ;
		return ( -1 ) ;
	}
	//	受信回収既読
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_BUNCHU_OK, 
						pAppEnv->cDirNR_ColOk ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_BUNCHU_OK ) ;
		return ( -1 ) ;
	}
	//	受信回収エラー
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_BUNCHU_ERR, 
						pAppEnv->cDirNR_ColErr ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_BUNCHU_ERR ) ;
		return ( -1 ) ;
	}

    // トレーNo情報ファイル格納ディレクト
    if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_TRAY_INFO,
                        pAppEnv->cDirTryinfo ) != 0 ) {
        //  異常終了    LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_TRAY_INFO ) ;
        return ( -1 ) ;
    }
    //トレーNo情報ファイル格納ディレクトリ(既読)
    if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_TRAY_INFO_OK,
                        pAppEnv->cDirTryinfoOK ) != 0 ) {
        //  異常終了    LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "トレーNo情報ファイル格納ディレクトリ(既読)取得失敗");
        return ( -1 ) ;
    }
//    //トレーNo情報ファイル格納ディレクトリ(エラー)
//    if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_TRAY_INFO_NG,
//                        pAppEnv->cDirTryinfoNG ) != 0 ) {
//        //  異常終了    LOG
//		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
//		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
//				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//				 	 "トレーNo情報ファイル格納ディレクトリ");
//       return ( -1 ) ;
//    }


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
	//	データベース名
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DB_NAME, 
						pAppEnv->cDb_Name ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DB_NAME ) ;
		return ( -1 ) ;
	}
	//	データベースユーザ
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DB_USER, 
						pAppEnv->cDb_User ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DB_USER ) ;
		return ( -1 ) ;
	}
	//	データベースパスワード
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DB_PASSWD, 
						pAppEnv->cDb_Passwd ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DB_PASSWD ) ;
		return ( -1 ) ;
	}
	//	ファイル読込リトライ回数
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_FILE_RETRY, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_FILE_RETRY ) ;
		return ( -1 ) ;
	}
	pAppEnv->fileRetry = atoi ( lc_prmBuf ) ;
	//	バージョン情報（次世代対応）	
//DEL	gtSystemVersion = MYAPP_SYSTEM_NEW ;
//DEL	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_VERSION, 
//DEL						pAppEnv->cVersion ) != 0 ) {
//DEL		gtSystemVersion = MYAPP_SYSTEM_OLD ;
//DEL	}

	//	パラメータファイルクローズ	
	ZbmlPrmClose ( pAppEnv->bp ) ;

	/***
	 ***	共有メモリ生成	
	 ***/
	if ( sFncShmCrt ( pAppEnv ) < 0 ) {
		return ( -1 ) ;
	}

	/***
	 ***	データベースオープン
	 ***/
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "ZdbConnect", __LINE__,
		 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		 "データベースオープンします[DB=%s USER=%s PASS=%s]"
		, pAppEnv->cDb_Name, pAppEnv->cDb_User, pAppEnv->cDb_Passwd ) ;
	ll_retSts = ZdbConnect( pAppEnv->cDb_Name, pAppEnv->cDb_User, pAppEnv->cDb_Passwd ) ;
	if ( ll_retSts != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_DB ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZdbConnect", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "データベースオープンに失敗しました[DB=%s USER=%s PASS=%s]", pAppEnv->cDb_Name, pAppEnv->cDb_User, pAppEnv->cDb_Passwd ) ;
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
	int					  li_retSts ;
	long				  ll_retSts ;

	int					  li_idx ;	
	int					  li_stopFlg ;

	int 				  li_of_idx;

	//	ディレクトリ情報 
	DIR					 *lt_dp ;
	struct dirent		**lpst_dirBuf ;

	//	トレーラック情報関連
	int					  li_fileCnt ;				

	FILE *fp;
	char recBuf[128] = {0,};
	int lRet =0;


//システム管理マスタ
	g_strSysknr = NULL;
	g_iSyaknr = 0;

	if( g_strSysknr != NULL ) {
        ZbmlFree(g_strSysknr);
        g_strSysknr = NULL;
    }

	if( (lRet = ABunSyskanSelKey(&g_strSysknr, &g_iSyaknr)) < 0 ) {
        sFncPutLog ( TRCKIND_DEBUG, __FILE__, "ABunGetKnsgrp", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "システム管理マスタ SQL ERROR(%d)",lRet);
        return 0;
    }

    if(g_iSyaknr != 1){
        sFncPutLog ( TRCKIND_DEBUG, __FILE__, "ABunGetKnsgrp", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "システム管理マスタ 数が間違います。(%d)",g_iSyaknr);
        return 0;
    }

	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "while start", __LINE__,
		 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		 "File Dir<%s>\n",pAppEnv->cDirNR_Col);

	while ( 1 ) 
	{

		if ( ( li_fileCnt = scandir ( pAppEnv->cDirNR_Col, 
									  &lpst_dirBuf,
									  (void*)sFncFileFillter,
					   				  (void*)sFncFileCompar ) ) < 0 ) {
			//	異常終了	LOG
			gintErrorCode = MYAPP_STSCODE_ERR_DIR;
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "scandir", __LINE__,
				 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 	 "緊急分注結果情報ファイルの取得に失敗しました" ) ;
			return ( -1 ) ;
		}

		li_idx = 0 ;
		stOUTPUT_DATA stOutput;
		memset(&stOutput,0,sizeof(stOUTPUT_DATA));
		stOutput.nPos = MYAPP_KMKCD_START_POS;

		char filename[1024] = {0,};
		for ( li_idx = 0 ; li_idx < li_fileCnt ; li_idx ++ ) {

			sprintf(filename,"%s/%s",pAppEnv->cDirNR_Col,lpst_dirBuf[li_idx]->d_name);
			//fp  = fopen ( lpst_dirBuf[li_idx]->d_name, "r" ) ;
			fp  = fopen ( filename, "r" ) ;
			if ( fp == NULL ) {
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "fopen", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "FILE Open ERROR Directory:<%s>",filename);
				return(0);
			}
			sFncPutLog ( TRCKIND_OPT, __FILE__, "fopen", __LINE__,
				 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 	 "ファイルオープン<%s>",filename);


			FILE *fp_out;
			char Chkfilename[1024] = {0,};
			int nBreakFlg = 0;
			int nOseq  = 1;					// ADD 2007.06.27
			char sOutChgFlg[2];				// ADD 2007.06.27
			memset(sOutChgFlg,0,sizeof(sOutChgFlg));
			sOutChgFlg[0]='0';	

			// OUTPUT FILE NAME CHK_INPUTFILENAME_nOseq.dat
			//		1FILE分の処理終了までは、INPUT_DIRにファイル出力する
			sprintf(Chkfilename,"%s/%s_%s_%03d.dat"
				,pAppEnv->cDirNR_Col
				,MYAPP_SEND_KIND_CH, lpst_dirBuf[li_idx]->d_name, nOseq );
			fp_out  = fopen ( Chkfilename, "aw" ) ;
			if(fp_out == NULL)
			{
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "fopen", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "FILE Open ERROR Directory:<%s>",Chkfilename);
				return(0);
			}

			stOutput.fp = fp_out;
			//  読み込み
			while(1){
				memset(recBuf,0,sizeof(recBuf));
				nBreakFlg =fgets ( recBuf, sizeof( recBuf ), fp );

				if(nBreakFlg== 0) 
				{
					break;
				}
				lRet = strlen(recBuf);
				if(lRet != MYAPP_RECV_RECSIZE)
				{
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "read", __LINE__,
						 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						 "レコードサイズが合致しません。<%d>",lRet);
					
					break;
				}
					
				// 1INPUT -> TrayID毎に1OUTPUT
				// lRet = procFile(pAppEnv,lpst_dirBuf[li_idx]->d_name,recBuf,&stOutput);
				lRet = procFile(pAppEnv,lpst_dirBuf[li_idx]->d_name,recBuf,&stOutput,sOutChgFlg);
				if(lRet == 0){
					sFncPutLog ( TRCKIND_WARNING, __FILE__, "procFile", __LINE__,
						 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						 "DB条件が探せない。");
					break;
				}

				// FILE OUTPUT BREAK CHECK
				if ( sOutChgFlg[0] == '1' ){
					// file close
					fclose (stOutput.fp);	
					sFncPutLog ( TRCKIND_DEBUG, __FILE__, "fclose", __LINE__,
						 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						 "正常ファイル処理しました。<output:%s>",Chkfilename );
					// next file open
					sOutChgFlg[0] = '0';
					nOseq++;
					sprintf(Chkfilename,"%s/%s_%s_%03d.dat"
						,pAppEnv->cDirNR_Col
						,MYAPP_SEND_KIND_CH, lpst_dirBuf[li_idx]->d_name, nOseq );
					fp_out  = fopen ( Chkfilename, "aw" ) ;
					if(fp_out == NULL)
					{
						sFncPutLog ( TRCKIND_ERROR, __FILE__, "fopen", __LINE__,
							 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							 "FILE Open ERROR Directory:<%s>",Chkfilename);
						break;
					}
					stOutput.fp = fp_out;
				}

			}

			fclose ( fp ) ;
			if(nBreakFlg == 0){

				//正常終了
				//	LAST 1 RECORD
				fwrite(&stOutput,MYAPP_PNC_MAX_SIZE,1,stOutput.fp);
				memset(&stOutput,0,MYAPP_PNC_MAX_SIZE);
				stOutput.nPos = MYAPP_KMKCD_START_POS;
				memset(stOutput.KeyKntno,0,sizeof(stOutput.KeyKntno));
				memset(stOutput.KeyEda,0,sizeof(stOutput.KeyEda));
				
				fclose (stOutput.fp);	
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "fclose", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "正常ファイル処理しました。<output:%s>",Chkfilename );

				// INPUT FILE  -> OK
				sFncFileRename ( pAppEnv->cDirNR_Col,lpst_dirBuf[li_idx]->d_name 
						, pAppEnv->cDirNR_ColOk,lpst_dirBuf[li_idx]->d_name );

				// OUTPUT -> OUTPUT DIR
				for ( li_of_idx=1; li_of_idx <= nOseq; li_of_idx++ ){
					sprintf(Chkfilename,"%s_%s_%03d.dat"
						,MYAPP_SEND_KIND_CH, lpst_dirBuf[li_idx]->d_name, li_of_idx );
					sFncFileRename ( pAppEnv->cDirNR_Col,Chkfilename
							, pAppEnv->cDirTryinfo, Chkfilename );
					sFncPutLog ( TRCKIND_OPT, __FILE__, "rename", __LINE__,
						 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						 "正常ファイル処理しました。<MOVE:%s%s>",
							pAppEnv->cDirTryinfo, Chkfilename );
				}
			}
			else{

				fclose (stOutput.fp);	

				// エラー時INPUT はそのままのディレクトリに残す
				// エラー時OUTPUT は削除する
				for ( li_of_idx=1; li_of_idx <= nOseq; li_of_idx++ ){
					sprintf(Chkfilename,"%s/%s_%s_%03d.dat"
						,pAppEnv->cDirNR_Col
						,MYAPP_SEND_KIND_CH, lpst_dirBuf[li_idx]->d_name, li_of_idx );
					remove(Chkfilename);
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "remove", __LINE__,
						 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						 "REMOVE FILE<%s>",Chkfilename);
				}
			}
		}

		/***
		 *** 停止コマンド確認
		 ***/
		if ( sFncShmGet ( pAppEnv, &li_stopFlg ) == 0 ) {
			if ( li_stopFlg == 1 ) {
				break ;
			}
		}

		/***
		 *** スリープ
		 ***/
		sleep ( pAppEnv->sleep_Sec ) ;
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
	/***
	 ***	データベースクローズ
	 ***/
	ZdbDisConnect() ;

	/***
	 ***	共有メモリ削除	
	 ***/
	sFncShmDel ( pAppEnv ) ;

	/***
	 ***	ログクロース
	 ***/
	//	開始ログ出力
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__,
				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "プログラム終了" ) ;
	ZbmlCloseLog() ;
	exit(9);	
	return ;
}

/******************************************************************************/
/*  関 数 名　：procFile()                                                    */
/*  機能概要　：文字列前後のスペースを削除する                                */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *      編集文字列                                        */
/*  出　　力　：                                                              */
/*  復帰情報　：無し                                                          */
/*  特記事項  ：同一検体番号においては、サンプリングコードが必ず一致するという*/
/*              前提で、初回の項目のみをKINKMMSTよりSELECTし、サンプリングコー*/
/*              ドを取得する。また、緊急SUNより受信した分注結果ファイルにある */
/*              項目コードは、展開せずにAD205側で依頼情報より取得する。       */
/******************************************************************************/
//int procFile(struct appEnv *pAppEnv,char *filename,char *sRecv,stOUTPUT_DATA *stOutput)
int procFile(struct appEnv *pAppEnv,char *filename,char *sRecv,stOUTPUT_DATA *stOutput, char *sOutChgFlg)
{
	char kmkcd[8] = {0,};
	char edaban[3] = {0,};					// ADD
	stINPUT_DATA stINPUT;
	memset(&stINPUT,0,sizeof(stINPUT_DATA));
    int cur=0;

/*** ファイル情報を内部構造体へ展開 ***/
	memcpy( stINPUT.utkymd, sRecv + cur, 8 );				/* 受付日付 取得 						*/
	cur += 8;												/* 受信ファイルポインタをREADした分移動 */
	memcpy( stINPUT.kntno, sRecv + cur, 11 );				/* 検体No 取得 							*/
	cur += 11;												/* 受信ファイルポインタをREADした分移動 */
	memcpy( stINPUT.eda, sRecv + cur, 2 );					/* 予備 取得 							*/
	cur += 2;												/* 受信ファイルポインタをREADした分移動 */
	memcpy( stINPUT.sincode, sRecv + cur, 7 );				/* 親項目コード 取得 					*/
	cur += 7;												/* 受信ファイルポインタをREADした分移動 */
	memcpy( stINPUT.kmkcd, sRecv + cur, 7 );				/* 項目コード 取得 						*/
	cur += 7;												/* 受信ファイルポインタをREADした分移動 */
	memcpy( stINPUT.wscd, sRecv + cur, 4 );					/* WSコード 取得 						*/
	cur += 4;												/* 受信ファイルポインタをREADした分移動 */
	memcpy( stINPUT.scheduleno, sRecv + cur, 4 );			/* SEQ番号 取得 						*/
	cur += 4;												/* 受信ファイルポインタをREADした分移動 */
	memcpy( stINPUT.motorackid, sRecv + cur, 8 );			/* 元ラックID 取得 						*/
	cur += 8;												/* 受信ファイルポインタをREADした分移動 */
	memcpy( stINPUT.motorackpos, sRecv + cur, 2 );			/* 元ポジション 取得 					*/
	cur += 2;												/* 受信ファイルポインタをREADした分移動 */
	memcpy( stINPUT.bunchurackid, sRecv + cur, 8 );			/* ラックID 取得 						*/
	cur += 8;												/* 受信ファイルポインタをREADした分移動 */
	memcpy( stINPUT.bunchurackpos, sRecv + cur, 2 );		/* ポジション 取得 						*/
	cur += 2;												/* 受信ファイルポインタをREADした分移動 */

	char rackpos[4] = {0,};
	sprintf(rackpos,"%03d",atoi(stINPUT.bunchurackpos));

/*** 64項目制限対応 上位からの要求(ファイル)を無視して、IRAI情報から項目を作る -> ***/
	if(stOutput->nPos == MYAPP_KMKCD_START_POS){	/* 初回処理後、nPosをデクリメントして判定に使用 */
		//初回処理－何もしない	*/
	}
	else if( strcmp(stOutput->KeyKntno,stINPUT.kntno)==0
//	&& strcmp(stOutput->KeyEda,stINPUT.eda) ==0
		&& strncmp(stOutput->utkymd,stINPUT.utkymd,sizeof(stOutput->utkymd)) ==0
		&& strncmp(stOutput->altuseiRackID,stINPUT.bunchurackid,sizeof(stOutput->altuseiRackID)) ==0
		&& strncmp(stOutput->iti1,rackpos,sizeof(stOutput->iti1)) == 0)
	{	//同じ検体番号	*/
		memset(kmkcd,0,sizeof(kmkcd));
		memcpy(kmkcd, stINPUT.kmkcd, 7);				/* 項目コードを取得 */

/*		memcpy(stOutput->kmkcd[stOutput->nPos] , kmkcd, 7);	*//* 取得した項目コードを出力先にSET */
	/* 項目コードは設定しない */
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"項目追加[%d],<項目:%s>",stOutput->nPos, kmkcd);
/*		stOutput->nPos --;*//* カウントしない */
		return 1;
	}
	else
	{	//新しい検体番号
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"FILE WRITE");
		fwrite(stOutput,MYAPP_PNC_MAX_SIZE,1,stOutput->fp);

		// ADD bunchurackid が変わったら出力ファイルを分ける
		if (strncmp(stOutput->altuseiRackID,stINPUT.bunchurackid,sizeof(stOutput->altuseiRackID))!=0 ){
			sOutChgFlg[0] = '1';
		}

		// 出力系の初期化
		memset(stOutput,0,MYAPP_PNC_MAX_SIZE);
		stOutput->nPos = MYAPP_KMKCD_START_POS;
		memset(stOutput->KeyKntno,0,sizeof(stOutput->KeyKntno));
		memset(stOutput->KeyEda,0,sizeof(stOutput->KeyEda));
	}
/*** 64項目制限対応 上位からの要求(ファイル)を無視して、IRAI情報から項目を作る <- ***/

	//  基本検索キー設定
	char utkymd[12] = {0,};
	char irino[12] = {0,};
	int nRecCnt =0;
	int lRet =0;
	struct S_KANJYA sKanjya;

	sprintf ( utkymd , "%4.4s-%2.2s-%2.2s",						/* 受付日付の取得 */
		  stINPUT.utkymd,&stINPUT.utkymd[4],&stINPUT.utkymd[6]);

	sprintf (irino,"00%-3.3s%-4.4s00",stINPUT.kntno, &stINPUT.kntno[5]);
																/* 検体Noから依頼書Noの取得(00xxxxxxx00形式) */

	if(strcmp(g_strSysknr->kkkjsriymd,utkymd) != 0){
	 	sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__,
			 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "システム管理マスタの緊急基準処理日(%s)と受付日(%s)が違います。"
			,g_strSysknr->kkkjsriymd,utkymd);
		return 0;
	}

	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "患者情報テーブル検索<受付日:%s><依頼NO:%s>",utkymd,irino);

	lRet=selectKANJYA(utkymd,irino,&sKanjya,&nRecCnt);

	if(lRet == MYAPP_SQL_DEADLOCK || lRet== MYAPP_SQL_DUPLICATION)
	{

		//  ロールバック
	 	sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__,
			 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "SELECT ERROR(%d)",lRet);
		ZdbRollback () ;
		endFunction( pAppEnv );
	}
	else if(lRet<0){

		sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__,
			 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "SELECT ERROR(%d)",lRet);
		ZdbRollback () ;
		endFunction( pAppEnv );
	}

	// 属性修正考慮で1件以上も発生する可能性あり
	//if(nRecCnt != 1)[
	if(nRecCnt < 1){
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "", __LINE__,
             EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
             "患者テーブルの中で検索されない <検体番号:%s>",irino);
		return 0;
	}

	g_strKinkmmst= NULL;
    g_nKinkmmst = 0;
/*** 分注結果ファイルの項目から緊急項目マスタのサンプリングコードを取得する --> ***/
	sprintf(kmkcd,"%s",stINPUT.kmkcd);					/* 分注結果から項目コードを取得 */
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "緊急項目マスタ検索<項目コード:%s>",kmkcd);
	lRet = KinkmmstSelectKey(kmkcd, &g_strKinkmmst,&g_nKinkmmst);	/* 緊急項目マスタSELECT */

	if(lRet == MYAPP_SQL_DEADLOCK || lRet== MYAPP_SQL_DUPLICATION)
    {

		sFncPutLog ( TRCKIND_ERROR, __FILE__, "KinkmmstSelectKey", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "緊急マスタSQL ERROR(%d)",lRet);
        ZdbRollback () ;
        endFunction( pAppEnv );
    }
	else if(lRet<0){

        sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__,
             EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
             "SELECT ERROR(%d)",lRet);
        ZdbRollback () ;
        endFunction( pAppEnv );
    }

	if(g_nKinkmmst<= 0){
        sFncPutLog ( TRCKIND_WARNING, __FILE__, "", __LINE__,
             EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
             "緊急項目マスタテーブルの中で検索されない ");
        return 0;
    }

	char tmp_smpcd[8] = {0,};
	strcpy(tmp_smpcd,g_strKinkmmst[0].smpcd);		/*	緊急項目マスタから取得したサンプリングコードをコピー */
	free(g_strKinkmmst);							/* SELECT結果 Free */

#if 0	/* 分注結果の項目と依頼テーブルの整合チェックは、項目を見ない(64項目制限対応) */
		/* ように変更した為、不要。よって以下の削除!!!                                */
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "依頼情報検索<utkymd:%s><irino:%s><smpcd:%s>"
			,utkymd, irino,tmp_smpcd);
	struct S_IRAI *pIrai = NULL;
	nRecCnt =0;
	int	nLotno=0;

	lRet=selectIRAI(utkymd, irino, tmp_smpcd, kmkcd, &nLotno, &nRecCnt);
	if(lRet == MYAPP_SQL_DEADLOCK || lRet== MYAPP_SQL_DUPLICATION)
	{

		//  ロールバック
	 	sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__,
			 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "SELECT ERROR(%d)",lRet);
		ZdbRollback () ;
		endFunction( pAppEnv );
		
	}
	else if(lRet<0){

	 	sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__,
			 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "SELECT ERROR(%d)",lRet);
		ZdbRollback () ;
		endFunction( pAppEnv );
	}
	if(nRecCnt <= 0){
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "", __LINE__,
             EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
             "依頼テーブルの中で検索されない ");
		return 0;
	}
	// 緊急依頼ロットNo退避
	sprintf( edaban, "%.02d", nLotno );
	
	free(pIrai);
#endif
	/* <--ここまで、依頼テーブル参照ロジックを削除 -->*/

	// チェック文字取得
	char strKntno[3]={0,};
	bmlConvBarcode(stINPUT.kntno,strKntno);

/*** Ver 2.00 検体Noの受信形式をPNC形式11桁化した為、edaは使用しない様に変更 ***/
/*	char barcd[12] = {0,}; */
/*	sprintf(barcd,"0%2.2s00%4.4s%2.2s" */
/*		,stINPUT.kntno, &stINPUT.kntno[2], stINPUT.eda);	 */
	// 枝番が空白の場合は緊急依頼ロットNoを編集
/*	if(stINPUT.eda[0] == ' ' ){ */
/*		memcpy( &barcd[9], edaban, 2 );	*/
/*	}*/
/***																		 ***/
/*** 分注結果ファイルの依頼は見ない <-- ***/

	memset(stOutput,' ',MYAPP_PNC_MAX_SIZE);
	stOutput->nPos = MYAPP_KMKCD_START_POS;

	memcpy(stOutput->syokubetumozi ,"R1",2);
	memcpy(stOutput->transactionID ,"SDATA1",6);
	memcpy(stOutput->altuseiRackID ,stINPUT.bunchurackid,8);
	memcpy(stOutput->utkymd ,stINPUT.utkymd,8);
	memcpy(stOutput->iti1 ,rackpos,3);
	memcpy(stOutput->BMLutkymd ,stINPUT.utkymd,8);
/*	memcpy(stOutput->iraino ,barcd,11); */						/* kntnoからダイレクトに取得するように変更 */
	sprintf(stOutput->iraino,"%-9.9s00",stINPUT.kntno);			/* 検体Noから依頼書Noの取得(kntnoの枝番をマスク) */
/*	memcpy(stOutput->kntno ,barcd,11); */						/* kntnoからダイレクトに取得するように変更 */
	memcpy(stOutput->kntno ,stINPUT.kntno,11);					/* 受信データのkntnoをそのまま設定 */
	memcpy(stOutput->kntchkmozi ,strKntno,2);
	memcpy(stOutput->WS ," ",1);
	memcpy(stOutput->sbkbn ,sKanjya.sbtkbn,1);
	memcpy(stOutput->nrkbn ,sKanjya.agekbn,1);
	memcpy(stOutput->nr ,sKanjya.age,3);

	memcpy(stOutput->nyoutime ,sKanjya.bko2,4);
	memcpy(stOutput->nyoutime_tan ,&sKanjya.bko2[5],1);
	memcpy(stOutput->nyouryou ,&sKanjya.bko2[7],5);
	memcpy(stOutput->nyouryou_tan ,&sKanjya.bko2[13],1);

	memcpy(stOutput->sstcd ,sKanjya.sstcd,7);
	memcpy(stOutput->egyoucd ,sKanjya.ecd,3);
	memcpy(stOutput->motoRackID ,stINPUT.motorackid,8);
	sprintf(rackpos,"%03d",atoi(stINPUT.motorackpos));
	memcpy(stOutput->motoRackPos ,rackpos,3);
	memcpy(stOutput->wscd ,tmp_smpcd,4);

/*** 64項目制限対応 上位からの要求(ファイル)を無視して、IRAI情報から項目を作る ***/
/*	memcpy(stOutput->kmkcd[stOutput->nPos] ,stINPUT.kmkcd, 7);	*/

	memcpy(stOutput->bckID,"   ",3);
	memcpy(stOutput->jtflg," ",1);
	memcpy(stOutput->kssr,"1",1);
	memcpy(stOutput->tgennflg ," ",1);
	memcpy(stOutput->kkirflg ," ",1);
	memcpy(stOutput->btkka ,"0",1);
	memset(stOutput->Filler,' ',466);
	stOutput->Filler[466] = '0';
	stOutput->LF = '\n';

/*** 64項目制限対応 上位からの要求(ファイル)を無視して、IRAI情報から項目を作る -> ***/
	stOutput->nPos--;						/* 初回と区別する為にデクリメント。判定以外には使わない */
	strcpy(stOutput->KeyKntno,stINPUT.kntno);	
	strcpy(stOutput->KeyEda,stINPUT.eda);	

	return 1;
}

/******************************************************************************/
/*  関 数 名　：sFncPutLog()  			 									  */
/*  機能概要　：文字列前後のスペースを削除する				  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *   	編集文字列								 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：無し														  */
/******************************************************************************/
void
sFncPutLog ( LOG_TRCKIND peTrcKind, char * pcSrcName, char * pcFncName, int plLineNo, char * pcExeFlg, char * pcErrCode, char * pcfmt, ... ) 
{
	va_list	 ap ;
	char	 cMsg[1024] ;

	/***
	 ***	ログ初期値設定
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
	 ***	ログ出力
	 ***/
#ifdef _DEBUG_LOG
	printf("(%d)%s\n",plLineNo,gstLogMem.pcMsg);
#endif

	_ZbmlPutLog ( &gstLogMem, pcSrcName, plLineNo) ;
	return ;
	
}

////////////////////////////////////////////////////////////////////////////////
//  関 数 名　：bmlConvBarcode ()
//  機能概要　：バーコードより、検体チェック文字を取得する。
//  入　　力　：
//　 第１引数 ：char *pIn_data バーコード
//  出　　力　：なし
//　 第１引数 ：char *pOut_data 検体チェック文字
//  復帰情報　： int
//　　　　　　　 RET_OK  : 正常
// 　　　　　　　RET_ERR : 異常
////////////////////////////////////////////////////////////////////////////////
int bmlConvBarcode(char *pIn_data, char *pOut_data)
{
    char   ken[16];
    int    i,chk_flg;
    int    amr=0;
    int    ukentai = 0;

    ukentai = atoi(pIn_data);
    chk_flg = 0;

    memset(ken, 0x0, sizeof(ken));
    strcpy(ken, pIn_data);


    for(i=0; i<strlen(ken); i++){
        if(isdigit(ken[i]) == 0){   /* 数字でない */
            chk_flg=1;
            break;
        }
    }
    if(chk_flg == 1){
        strcpy(pOut_data,"    ");
        return(-1);
    }

    amr = ukentai % 197;
    strcpy(pOut_data,moji[amr]);

    return 1;
}

/******************************************************************************/
/*  関 数 名　：sFncTrFileToken()			 								  */
/*  機能概要　：トークン分割								  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *   	文字列									 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：char *														  */
/*					 NULL	終端											  */
/*					 NULL以外	文字列										  */
/******************************************************************************/
static	char*
sFncTrFileToken ( pString )
char	*pString ;
{
	char	*p ;
	char	*pRet ;
	int		 liIdx ;

	//	分割文字列ポインター設定
	if ( pString == NULL ) {
		p = gpToken ;	
	}
	else {
		gpToken = pString ;
		p = pString ;	
	}

	//	終端チェック（最終カンマ以降を最後の値と取得するため）	
	if ( p == NULL ) {
		return ( NULL ) ;
	}

	//	トークン分割
	gpToken = NULL ;	//最終カンマ以降を最後の値と取得するため
	pRet = p ;
	while ( *p ) {
		if ( *p == ',' ) {
			*p  = '\0' ;
			gpToken =  p + 1 ;
			break  ;
		}	
		p++ ;
	}
	return ( pRet ) ;
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
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "rename", __LINE__,
 	 	 			 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
 	 	 			 "ファイルの移動に失敗しました[%s->%s]", lc_fromPath, lc_toPath ) ;
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
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmget", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}

	//	アタッチ	
	shmData = ( int * ) shmat ( pAppEnv->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
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
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
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
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
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
		//sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmctl", __LINE__,
		//		 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		//		 	 "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}	
/******************************************************************************/
/*  関 数 名　：sFncFileCompar()			 								  */
/*  機能概要　：ファイル名比較【コールバック関数】			  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *   	比較文字列								 	      */
/*　 第２引数 ：char *   	比較文字列								 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/******************************************************************************/
static	int
sFncFileCompar ( a, b ) 
struct dirent	**a ;
struct dirent	**b ;
{
		char	*p1 ;
		char	*p2 ;

		p1 = strchr ( (*a)->d_name, '_' ) ;
		if ( p1 == NULL ) {
			p1 = (*a)->d_name ;
		}
		p2 = strchr ( (*b)->d_name, '_' ) ;
		if ( p2 == NULL ) {
			p2 = (*b)->d_name ;
		}
		return ( strcoll ( p1, p2 ) ) ;
		
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
/*			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "scandir", __LINE__,*/
/*				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,*/
/*				 "ファイルサイズが5以下です。<%s>",pdirEnt->d_name);*/
			return ( 0 ) ;
		}

		//識別チェック
			// OUTPUT先頭文字列に合致するものは対象外とする
		if ( memcmp ( pdirEnt->d_name, 
					  MYAPP_SEND_KIND_CH, 
					  strlen ( MYAPP_SEND_KIND_CH ) ) == 0 ) {
			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "scandir", __LINE__,
				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "識別チェックで間違いました。<元:%s><%s>",
				MYAPP_SEND_KIND_CH,pdirEnt->d_name);
			return ( 0 ) ;
		}

		return ( 1 ) ;
}
/******************************************************************************/
/*  関 数 名　：_sFncEnvDip()				 								  */
/*  機能概要　：プログラム環境変数出力関数【トレース用】	  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体			 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：無し														  */
/******************************************************************************/
static void
_sFncEnvDip( pAppEnv )
struct appEnv	*pAppEnv ;
{
#if defined ( _TRACE )
	loging ( "########## Stocker - _sFncEnvDip ##########\n" ) ;
	loging ( "\t【共有ディレクトリ構成】\n" ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_BUNCHU,     pAppEnv->cDirNR_Col ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_BUNCHU_OK,  pAppEnv->cDirNR_ColOk ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_BUNCHU_ERR, pAppEnv->cDirNR_ColErr ) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_NR_LOG,     pAppEnv->cDirNR_Log ) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_TRAY_INFO,     pAppEnv->cDirTryinfo) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_TRAY_INFO_OK,     pAppEnv->cDirTryinfoOK) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_TRAY_INFO_NG,     pAppEnv->cDirTryinfoNG) ;
	loging ( "\t%s : [%d]\n", MYAPP_PRM_SHM_KEY,        pAppEnv->shm_Key ) ;
	loging ( "\t%s : [%d]\n", MYAPP_PRM_SLEEP_SEC,      pAppEnv->sleep_Sec ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DB_NAME,        pAppEnv->cDb_Name ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DB_USER,        pAppEnv->cDb_User ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DB_PASSWD,      pAppEnv->cDb_Passwd ) ;
	loging ( "########## Stocker - _sFncEnvDip ##########\n" ) ;
#endif
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

	/***
	 ***    バックグラウンド実行
	 ***/
	if ( daemon ( 0, 1 ) < 0 ) {
		printf("ログファイル名を指定されてない");
		exit ( 9 ) ;
	}


	/***
	 ***	初期処理	
	 ***/
	if ( initFunction ( argc, argv, &sAppEnv )  != 0 ) {
		endFunction ( &sAppEnv ) ;
		exit ( 9 ) ;
	}
_sFncEnvDip ( &sAppEnv ) ;
	
	/***
	 ***	主処理	
	 ***/
	if ( mainFunction ( &sAppEnv )  != 0 ) {
		endFunction ( &sAppEnv ) ;
		exit ( 9 ) ;
	}

	/***
	 ***	終了処理	
	 ***/
	endFunction ( &sAppEnv ) ;
	exit(9);
}

/** End of File ***************************************************************/
