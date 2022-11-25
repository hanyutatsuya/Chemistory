/******************************************************************************/
/* 　ＢＭＬ様向け検査システム  							*/
/*                             							*/
/* 　システム名：次世代システム							*/
/* 　ファイル名：LD103.c              						*/
/* 　概　　　要：	        						*/
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
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
#include <stdbool.h>

#include "bmllog.h"
#include "bmlprm.h"
#include "bml_misc.h"
#include "bml_date.h"
#include "bml_DBCom.h"

#include "sql.h"
#include "LD103.h"

/******************************************************************************/
/* Define定義                                                                 */
/******************************************************************************/

/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/
struct stcLogMember	gstLogMem ;		//	ログ出力情報

/******************************************************************************/
/* 関数宣言                                                                   */
/******************************************************************************/
//	ファイル・データベース出力関数

//	共有メモリ操作関数
static	int	sFncShmCrt() ;
static	int	sFncShmGet(int *) ;
static	int	sFncShmDel() ;


//	その他
static  int     FileFilter( struct dirent *namelist );

static	int	initFunction(int , char**);
static	int	mainProc(FILE * );
static  void	endFunction() ;

int	ReadFile(char *, FILE *);
int	chkUpdateKanjya(my_stDbKanjya *, my_stCHKZOK *);
int	ChkErrZok(my_stCHKZOK *);

int	sFncSelSysKnr(my_stSYSKNR *);
int	sFncChkZok(char *, char *, my_stCHKZOK **, int *);
int	sFncRuiChkZok(char *, char *, my_stCHKZOK **, int *);
int	sFncMoveRuiTou(char *, char *);
int	sFncUpdateKanjya(my_stCHKZOK *);
int	InsHkHrIrai(my_stCHKZOK *, int);
int	sFncCntOrder(my_stCHKZOK *, int *);
int	sFncInsRecalc(my_stCHKZOK *);

/******************************************************************************/
/*  関 数 名　：initFunction()							*/
/*  機能概要　：初期処理関数							*/
/*  入　　力　：                                                              */
/*　 第１引数 ：struct	env *   	プログラム環境構造体。		 	*/
/*  出　　力　：                                                              */
/*  復帰情報　：  0     : 成功							*/
/* 　　　　　　　-1     : 失敗							*/
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
	memset ( &pAppEnv , '\0', sizeof ( pAppEnv ) ) ;

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
	//	ファイル取得用シェル
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_FILE_GET_SHELL, pAppEnv.cFileGetSH ) != 0 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_FILE_GET_SHELL ) ;
		return ( -1 ) ;
	}
	//	ファイル処理ディレクトリ
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DIR_INPUT, pAppEnv.cInputDir ) != 0 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_INPUT ) ;
		return ( -1 ) ;
	}
	//	処理済みファイル移動ディレクトリ
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DIR_OK, pAppEnv.cEndFileDirOK ) != 0 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_OK ) ;
		return ( -1 ) ;
	}
	//	処理エラーファイル移動ディレクトリ
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DIR_NG, pAppEnv.cEndFileDirNG ) != 0 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_NG ) ;
		return ( -1 ) ;
	}
	//	処理対象ファイルプレフィックス
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_FILE_PRX, pAppEnv.cFilePrx ) != 0 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_FILE_PRX ) ;
		return ( -1 ) ;
	}
	//	ロックファイル。LD101(属性エラーチェック情報作成) 起動トリガー。最初の処理が終わったら作成。
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_LOCK_FILE, pAppEnv.cLockFile ) != 0 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_LOCK_FILE ) ;
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
	//	SLEEP時間取得(分)
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_SLEEP_MIN, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_SLEEP_MIN ) ;
		return ( -1 ) ;
	}
	pAppEnv.SleepMin= atoi ( lc_prmBuf ) ;

	//	パラメータファイルクローズ	
	ZbmlPrmClose ( pAppEnv.bp ) ;

	/***
	 ***	共有メモリ生成	
	 ***/
	if ( sFncShmCrt() < 0 ) {
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
/*  出　　力　：								*/
/*  復帰情報　：  0     : 成功							*/
/* 　　　　　　　-1     : 失敗							*/
/********************************************************************************/
int
mainFunction()
{
	int	li_retSts = 0;
	int	li_stopFlg = 0;

	int	i = 0;
	int	file_cnt = 0;

	int	min = 0;

	char	cmd[1024];
	char	w_infilenm[256];	// 処理前ファイル名(フルパス)
	char	w_endfilenm[256];	// 処理終了ファイル名(フルパス)
	char	w_filenm[256];		// 処理終了ファイル名
	struct	dirent  **namelist;	// get input file
	FILE	*fp;			// 読込ﾌｧｲﾙﾎﾟｲﾝﾀ

	my_stSYSKNR	pSysKnr;	//

	/***
	 ***		永久ループ
	 ***		停止コマンドで終了
	 ***/
	while ( 1 ) {
		/* 1分ごとに停止コマンドを確認しながら設定された時間スリープ */
		for ( min=0; min < pAppEnv.SleepMin; min++ ) {
			sleep ( 60 ) ;
			/* 停止コマンド確認 */
			if ( sFncShmGet ( &li_stopFlg ) != 0 ) {
	        		return( RTN_NG );
			}
			if ( li_stopFlg == 1 ) {
	        		return( RTN_OK );
			}
			/* システム管理マスタ 検索 */
			if ( sFncSelSysKnr( &pSysKnr ) !=  RTN_OK ){
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "システム管理情報の取得に失敗しました");
		        	return( RTN_NG );
			}
			/* 依頼ＥＮＤが来ている時は日次処理の開始確認を行う。 */
			if( strcmp( pSysKnr.iriendflg, "1" ) == 0 ) {
				/* 日次処理が始まっていたら終了 */
				if( strcmp( pSysKnr.unyflg, "1" ) == 0 ) {
					sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						     "日次処理の開始を確認しました。");
					return( RTN_OK );
				}
			}
		}

		/* システム管理マスタ 検索 */
		if ( sFncSelSysKnr( &pSysKnr ) !=  RTN_OK ){
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "システム管理情報の取得に失敗しました");
	        	return( RTN_NG );
		}
		/* 依頼ＥＮＤが来るまで待機 */
		if( strcmp( pSysKnr.iriendflg, "1" ) != 0 ) {
			continue;
		}

		sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "FTP コマンドを開始します。");

		// FTPコマンド用シェルの実行
		sprintf( cmd, "sh %s", pAppEnv.cFileGetSH);
		system( cmd );

                // 対象ファイルの取得
                file_cnt = scandir( pAppEnv.cInputDir, &namelist, (void*)FileFilter, alphasort);
                if ( file_cnt < 0){
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				     "ファイルの情報取得(scandir)に失敗しました。") ;
                        break;
		} else if ( file_cnt == 0 ) {
			sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "属性修正情報は存在しませんでした。");
			// LD101スタートトリガーのファイルを作成
			if( ( fp = fopen( pAppEnv.cLockFile, "w" ) ) == NULL ){
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "ロックファイルの作成に失敗しました。[%s]", pAppEnv.cLockFile ) ;
			}
			fclose( fp );
			continue;
                }

		for( i=0; i < file_cnt; i++ ){
			strcpy( w_filenm, namelist[i]->d_name );
			// scadirファイル名のfree
			free( namelist[i] );

			// ファイル名作成
			memset( w_infilenm,  '\0',sizeof( w_infilenm ));
			memset( w_endfilenm, '\0',sizeof( w_endfilenm ));
			sprintf( w_infilenm, "%s/%s", pAppEnv.cInputDir, w_filenm );
			// INPUT FILE OPEN
			if( ( fp = fopen( w_infilenm, "r" ) ) == NULL ){
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "ファイルオープンに失敗しました。[FILE_NAME:%s]", w_infilenm ) ;
				continue;
			}

			sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "属性修正情報ファイルの処理を開始します。[%s]", w_infilenm );

			// メイン処理
                        li_retSts = mainProc( fp );
                        if( li_retSts == RTN_NG ){
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "処理中にエラーが発生しました。[FILE_NAME:%s]", w_infilenm ) ;
				if ( fp != NULL ) {
					fclose( fp );
				}
				/* エラーディレクトリへ移動 */
				sprintf( w_endfilenm, "%s/%s" , pAppEnv.cEndFileDirNG,  w_filenm );
				// 変更ファイルと同名のファイルが存在しないか
				for( ;; ){
					if( open( w_endfilenm, O_RDONLY, 0 ) == EOF ){
						break;
					}
					strcat( w_endfilenm, "_" );
				}
				rename( w_infilenm, w_endfilenm );
				continue;
			}
			// INPUT FILE CLOSE
			fclose( fp );

			// 処理済ディレクトリへ移動
			sprintf( w_endfilenm, "%s/%s" , pAppEnv.cEndFileDirOK,  w_filenm );
			// 変更ファイルと同名のファイルが存在しないか
			for( ;; ){
				if( open( w_endfilenm, O_RDONLY, 0 ) == EOF ){
					break;
				}
				strcat( w_endfilenm, "_" );
			}
			rename( w_infilenm, w_endfilenm );

			sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "ファイル処理が終了しました。[%s]", w_infilenm );
		}

		// LD101スタートトリガーのファイルを作成
		if( ( fp = fopen( pAppEnv.cLockFile, "w" ) ) == NULL ){
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "ロックファイルの作成に失敗しました。[%s]", pAppEnv.cLockFile ) ;
			continue;
		}
		fclose( fp );

	}

	return ( 0 ) ;
}

/******************************************************************************/
/*  関 数 名  ：mainProc                                                      */
/*  機能概要  ：患者情報ファイル処理                                          */
/*  入    力  ：                                                              */
/*   第１引数 ： FILE   pfp     : 入力ファイル識別子                          */
/*  出    力  ： なし                                                         */
/*  復帰情報  ： INT                                                          */
/*               RTN_OK     : 成功                                            */
/*               RTN_NG     : 失敗                                            */
/******************************************************************************/
int	mainProc( pfp )
FILE	*pfp;
{
	my_stFileKanjya		pInpFile;	/* 属性修正ファイル情報 */
	my_stDbKanjya		pInpDB;		/* 属性修正ファイル情報 DB形式へコンバートした情報 */
	my_stCHKZOK		*pChkZok;	/* 更新チェック用DB患者情報     */

	char    rbuf[RECORDSIZE*2+1];		/* 読み込みエリア */
	int 	li_retSts = 0;			/* 戻り値チェック用 */
	int	i = 0;				/* カウンタ */
	int	rec_cnt = 0;			/* 検索結果件数 */
	int	cnt = 0;			/* オーダーカウント件数 */
	bool 	rui_flg = false;		/* 累積対象チェックフラグ */
	int 	intHkkhrKbn = 0;		/* 報告保留区分 */

        /* ﾌｧｲﾙの読込 */
        while( ReadFile( rbuf, pfp ) != EOF ){  // read while start ----------->
		/* レコードサイズチェック */
		if( strlen( rbuf ) != ( RECORDSIZE )){
			// ERROR
			sFncPutLog( TRCKIND_ERROR, __FILE__, "mainProc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "読み込みレコードサイズエラー[%d]", strlen( rbuf ));
			continue;
		}
		/* --------------------------------     */
		/*      初期処理                        */
		/* --------------------------------     */
		memcpy( &pInpFile,	rbuf, sizeof( my_stFileKanjya ) );
		memset( &pInpDB,	0x00, sizeof( my_stDbKanjya ));
		pChkZok = NULL;
		rec_cnt = 0;
		cnt = 0;
		rui_flg = false;
		intHkkhrKbn = 0;

		/* 編集 */
		li_retSts = EditPncKanjya( &pInpFile, &pInpDB );
		if ( li_retSts != RTN_OK ){
			sFncPutLog( TRCKIND_ERROR, __FILE__, "mainProc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "EditPncKanjya"  );
			break;
		}
		/* 共通箇所の編集 */
		li_retSts = EditCommonKanjya( &pInpDB );
		if ( li_retSts != RTN_OK ){
			sFncPutLog( TRCKIND_ERROR, __FILE__, "mainProc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "EditCommonKanjya"  );
			break;
		}
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "ファイル読込。[utkymd:%s irino:%s]", pInpDB.utkymd, pInpDB.irino );
		/* 当日テーブルから依頼、属性の有無、及び、存在する項目と属性の値を取得 */
		li_retSts = sFncChkZok( pInpDB.utkymd, pInpDB.irino, &pChkZok, &rec_cnt);
		if ( li_retSts != RTN_OK ){
			sFncPutLog( TRCKIND_ERROR, __FILE__, "mainProc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "sFncChkZok"  );
			break;
		}
		/* 当日に依頼が存在しない場合は、累積テーブルから結果の有無をチェック */
		if( rec_cnt == 0) {
			li_retSts = sFncRuiChkZok( pInpDB.utkymd, pInpDB.irino, &pChkZok, &rec_cnt);
			if ( li_retSts != RTN_OK ){
				sFncPutLog( TRCKIND_ERROR, __FILE__, "mainProc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "sFncRuiChkZok"  );
				break;
			}
			if( rec_cnt > 0) {
				/* 累積情報に存在していた場合は当日分へ戻す */
				li_retSts = sFncMoveRuiTou( pInpDB.utkymd, pInpDB.irino );
				if( li_retSts != RTN_OK ){
					sFncPutLog( TRCKIND_ERROR, __FILE__, "mainProc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "sFncMoveRuiTou"  );
					break;
				}
				sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "累積分の情報を当日分へ戻しました。[utkymd:%s irino:%s]", pInpDB.utkymd, pInpDB.irino );
				rui_flg = true;
			} else {
				/* 累積にも対象がない場合次へ */
				sFncPutLog( TRCKIND_ERROR, __FILE__, "mainProc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
					    "属性が存在しません。[utkymd:%s irino:%s]", pInpDB.utkymd, pInpDB.irino );
				continue;
			}
		}

		for ( i = 0; i < rec_cnt; i++ ){
			/* 依頼、属性情報が取れた場合、計算に使用する属性が変更されているか確認 */
			/* pChkZok へ属性の修正内容を反映させる */
			li_retSts  = chkUpdateKanjya( &pInpDB, &pChkZok[i] );
			if( li_retSts == RTN_NONE ){
				/* 再計算対象なし。次のレコードへ */
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "再計算対象なし。[utkymd:%s irino:%s]", pInpDB.utkymd, pInpDB.irino );
				continue;
			}

			/* 再計算対象有り。*/
			sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "再計算対象有り [utkymd:%s irino:%s kmkcd:%s]", pChkZok[i].utkymd, pChkZok[i].irino, pChkZok[i].kmkcd );

			/* 属性情報のUPDATE */
			li_retSts  = sFncUpdateKanjya( &pChkZok[i] );
			if( li_retSts != RTN_OK ){
				break;
			}
			intHkkhrKbn = 0;	/* 報告保留区分 */
			/* 属性エラーチェック確認 */
			li_retSts = ChkErrZok( &pChkZok[i] );
			if( li_retSts == RTN_OK ){
				/* 属性エラーが無かった場合、再計算対象かの確認を行う */
				if( rui_flg == true ) {
					/* 過去分だった場合、再計算対象 */
					intHkkhrKbn = MYAPP_HKKHR_CALC;
				} else {
					/* 当日分だった場合、オーダー出力前かどうかの確認 */
					li_retSts  = sFncCntOrder( &pChkZok[i], &cnt );
					if( li_retSts != RTN_OK ){
						break;
					}
					if( cnt == 0) {
						/* オーダー出力前であれば、修正された情報を元に計算されるので保留解除 */
						intHkkhrKbn = MYAPP_HKKHR_OK;
					} else {
						/* オーダー出力後であれば、再計算対象 */
						intHkkhrKbn = MYAPP_HKKHR_CALC;
					}
				}
			}else{
				/* 属性エラーがあった場合はエラー内容で登録 */
				if( strcmp(pChkZok[i].scflg, MYAPP_ZOK_NG ) == 0 ||
				    strcmp(pChkZok[i].tjflg, MYAPP_ZOK_NG ) == 0 ||
				    strcmp(pChkZok[i].tjtniflg, MYAPP_ZOK_NG ) == 0 ||
				    strcmp(pChkZok[i].sbtkbnflg, MYAPP_ZOK_NG ) == 0 ||
				    strcmp(pChkZok[i].ageflg, MYAPP_ZOK_NG ) == 0 ||
				    strcmp(pChkZok[i].agekbnflg, MYAPP_ZOK_NG ) == 0 ) {
					intHkkhrKbn = MYAPP_HKKHR_NG ;
				}
			        else if( strcmp(pChkZok[i].scflg, MYAPP_ZOK_ERR ) == 0 ||
					 strcmp(pChkZok[i].tjflg, MYAPP_ZOK_ERR ) == 0 ||
					 strcmp(pChkZok[i].tjtniflg, MYAPP_ZOK_ERR ) == 0 ||
					 strcmp(pChkZok[i].sbtkbnflg, MYAPP_ZOK_ERR ) == 0 ||
					 strcmp(pChkZok[i].ageflg, MYAPP_ZOK_ERR ) == 0 ||
					 strcmp(pChkZok[i].agekbnflg, MYAPP_ZOK_ERR ) == 0 ) {
					intHkkhrKbn = MYAPP_HKKHR_ERR ;
				}
			}
			sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "報告保留フラグを更新します。[utkymd:%s, irino:%s, hkkhrKbn:%d]", pInpDB.utkymd, pInpDB.irino, intHkkhrKbn );
			/* 報告保留情報の更新 */
			li_retSts = InsHkHrIrai( &pChkZok[i], intHkkhrKbn );
			if( li_retSts != RTN_OK ){
				break;
			}

			ZdbCommit() ;
		}
	}
	return( RTN_OK );
}

/******************************************************************************/
/*  関 数 名  ：ReadFile							*/
/*  機能概要  ：属性ファイル読み込み						*/
/*  入    力  ：                                                              */
/*   第１引数 ： char   file_nm[]	: 入力ファイルポインタ			*/
/*  出    力  ： char   rbuf[];		: 読み込みバッファ			*/
/*  復帰情報  ： 0以上			: 正常終了(読込サイズ)			*/
/*               EOF			: FILE END				*/
/*               以外			: 失敗					*/
/******************************************************************************/
int	ReadFile( rbuf, pfp )
char		rbuf[];		/* ﾚｺｰﾄﾞ読み込みﾊﾞｯﾌｧ */
FILE		*pfp;		/* ﾌｧｲﾙ識別子 */
{
	/* 初期処理     */
	memset( rbuf, 0x00, strlen( rbuf ));
	if( fgets( rbuf, RECORDSIZE + 1, pfp ) == NULL ){
		/* ﾃﾞｰﾀなし     */
		return( EOF );
	}

	return( strlen( rbuf ) );
}

/******************************************************************************/
/*  関 数 名  ：chkUpdateKanjya                                               */
/*  機能概要  ：患者情報ファイル処理                                          */
/*  入    力  ：                                                              */
/*   第１引数 ： FILE   pfp     : 入力ファイル識別子                          */
/*   第２引数 ： int    stopValue : 終了識別子                                */
/*  出    力  ： なし                                                         */
/*  復帰情報  ： INT                                                          */
/*               RTN_OK     : 成功                                            */
/*               RTN_NG     : 失敗                                            */
/******************************************************************************/
int
chkUpdateKanjya( pInpDB, pChkZok )
my_stDbKanjya	*pInpDB ;
my_stCHKZOK	*pChkZok ;
{
	int	ret = RTN_NONE;
	char	sc_InpDB[6];
	char	sc_ChkZok[6];
	char	tj_InpDB[6];
	char	tj_ChkZok[6];
	char	age_InpDB[4];
	char	age_ChkZok[4];

	sFncTrim( sc_InpDB, pInpDB->sc );
	sFncTrim( sc_ChkZok, pChkZok->sc );
	sFncTrim( tj_InpDB, pInpDB->tj );
	sFncTrim( tj_ChkZok, pChkZok->tj );
	sFncTrim( age_InpDB, pInpDB->age );
	sFncTrim( age_ChkZok, pChkZok->age );

	if( strcmp( pChkZok->scflg, MYAPP_ZOK_CHK ) == 0 ){
		if( strcmp( sc_InpDB, sc_ChkZok ) != 0 ) {
			/* 更新内容を反映させる */
			strcpy( pChkZok->sc, pInpDB->sc ); 
			ret = RTN_OK;
		}
	}

	if( strcmp( pChkZok->tjflg, MYAPP_ZOK_CHK ) == 0 ){
		if( strcmp(tj_InpDB, tj_ChkZok ) != 0 ) {
			/* 更新内容を反映させる */
			strcpy( pChkZok->tj, pInpDB->tj ); 
			ret = RTN_OK;
		}
	}

	if( strcmp( pChkZok->tjtniflg, MYAPP_ZOK_CHK ) == 0 ){
		if( strcmp(pInpDB->tjtni, pChkZok->tjtni) != 0 ) {
			/* 更新内容を反映させる */
			strcpy( pChkZok->tjtni, pInpDB->tjtni ); 
			ret = RTN_OK;
		}
	}

	if( strcmp( pChkZok->sbtkbnflg, MYAPP_ZOK_CHK ) == 0 ){
		if( strcmp( pInpDB->sbtkbn, pChkZok->sbtkbn ) != 0 ) {
			/* 更新内容を反映させる */
			strcpy( pChkZok->sbtkbn, pInpDB->sbtkbn ); 
			ret = RTN_OK;
		}
	}

	if( strcmp( pChkZok->ageflg, MYAPP_ZOK_CHK ) == 0 ){
		if( strcmp( age_InpDB, age_ChkZok ) != 0 ) {
			/* 更新内容を反映させる */
			strcpy( pChkZok->age, pInpDB->age ); 
			ret = RTN_OK;
		}
	}

	if( strcmp( pChkZok->agekbnflg, MYAPP_ZOK_CHK ) == 0 ){
		if( strcmp( pInpDB->agekbn, pChkZok->agekbn ) != 0 ) {
			/* 更新内容を反映させる */
			strcpy( pChkZok->agekbn, pInpDB->agekbn ); 
			ret = RTN_OK;
		}
	}

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "sc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "chkUpdateKanjya,%s,%s,%s,%s,%s,", pChkZok->scflg, pChkZok->sc, pInpDB->sc, sc_ChkZok, sc_InpDB );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "tj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "chkUpdateKanjya,%s,%s,%s,%s,%s,", pChkZok->tjflg, pChkZok->tj, pInpDB->tj, tj_ChkZok, tj_InpDB );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "tjtni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "chkUpdateKanjya,%s,%s,%s,", pChkZok->tjtniflg, pChkZok->tjtni, pInpDB->tjtni );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "sbtkbn", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "chkUpdateKanjya.%s,%s,%s,", pChkZok->sbtkbnflg, pChkZok->sbtkbn, pInpDB->sbtkbn );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "age", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "chkUpdateKanjya,%s,%s,%s,%s,%s", pChkZok->ageflg, pChkZok->age, pInpDB->age, age_ChkZok, age_InpDB );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "agekbn", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "chkUpdateKanjya,%s,%s,%s,", pChkZok->agekbnflg, pChkZok->agekbn, pInpDB->agekbn );
	return( ret );
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

/******************************************************************************/
/*  関 数 名  ：FileFilter                                                    */
/*  機能概要  ：ファイルフィルター【コールバック関数】                        */
/*  入    力  ：                                                              */
/*   第１引数 ：struct          dirent *     ディレクトリ構造体               */
/*  出    力  ：なし                                                          */
/*  復帰情報  ： INT                                                          */
/*               0              : 対象外ファイル                              */
/*               1              : 対象ファイル                                */
/******************************************************************************/
static  int     FileFilter( namelist )
struct	dirent  *namelist ;
{
	char    w_fnm[256];
	struct  stat    statbuf;                                // get input file status

	// ディレクトリは除く
	sprintf( w_fnm, "%s/%s", pAppEnv.cInputDir, namelist->d_name );
	stat( w_fnm, &statbuf );
	if( S_ISDIR( statbuf.st_mode )){
		// 対象外
		return( 0 );
	}
	// 対象ファイルの先頭による判断
	if(( strcmp( pAppEnv.cFilePrx, "" ) != 0 )
 	 &&( memcmp( namelist->d_name, pAppEnv.cFilePrx , strlen( pAppEnv.cFilePrx )) == 0 )){
		// OK
		return( 1 );
	}

	return ( 0 );
}

/******************************************************************************/
/*  関 数 名　：endFunction()							*/
/*  機能概要　：終了処理関数							*/
/*  入　　力　：                                                              */
/*  出　　力　：                                                              */
/*  復帰情報　：  0     : 成功							*/
/* 　　　　　　　-1     : 失敗							*/
/******************************************************************************/
void
endFunction()
{
	/*	ロックファイル削除 */
	remove( pAppEnv.cLockFile );

	/*	データベースクローズ */
	ZdbDisConnect() ;

	/*	共有メモリ削除	*/
	sFncShmDel () ;

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
/*　 第１引数 ：int *   	値						*/
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

	exit ( 0 ) ;
}
/** End of File ***************************************************************/
