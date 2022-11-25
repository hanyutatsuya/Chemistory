/******************************************************************************/
/* 　ＢＭＬ様向け検査システム  							*/
/*                             							*/
/* 　システム名：次世代システム							*/
/* 　ファイル名：LD105.c              						*/
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

#include "bmllog.h"
#include "bmlprm.h"
#include "bml_misc.h"
#include "bml_date.h"

#include "sql.h"

#include "LD105.h"

/******************************************************************************/
/* Define定義                                                                 */
/******************************************************************************/
//	TRACE
#if defined ( _TRACE )
#define malloc(a)   _malloc(a, __FILE__, __LINE__)
#define free(p)     _free(p, __FILE__, __LINE__)
#endif

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
static	int	sFncShmGet ( int *) ;
static	int	sFncShmDel() ;


//	その他
static	int     FileFilter( struct dirent *namelist );
static	void	endFunction();
void	sFncTrim( char *, char * );

/******************************************************************************/
/*  関 数 名　：initFunction()							*/
/*  機能概要　：初期処理関数							*/
/*  入　　力　：                                                              */
/*　 第１引数 ：struct	env *  	プログラム環境構造体。		 		*/
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
	memset ( &pAppEnv , '\0', sizeof( pAppEnv ) ) ;

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
        //      ファイル処理ディレクトリ
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DIR_INPUT, pAppEnv.cInputDir ) != 0 ) {
		//      異常終了        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_INPUT ) ;
		return ( -1 ) ;
	}
	//      処理済みファイル移動ディレクトリ
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DIR_OK, pAppEnv.cEndFileDirOK ) != 0 ) {
		//      異常終了        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_OK ) ;
		return ( -1 ) ;
	}
	//      処理エラーファイル移動ディレクトリ
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DIR_NG, pAppEnv.cEndFileDirNG ) != 0 ) {
		//      異常終了        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_NG ) ;
		return ( -1 ) ;
	}
	//      処理対象ファイルプレフィックス
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_FILE_PRX, pAppEnv.cFilePrx ) != 0 ) {
		//      異常終了        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_FILE_PRX ) ;
		return ( -1 ) ;
	}
	//      ロックファイル
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_LOCK_FILE, pAppEnv.cLockFile ) != 0 ) {
		//      異常終了        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_LOCK_FILE ) ;
		return ( -1 ) ;
	}
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
	if ( sFncShmCrt ( pAppEnv ) < 0 ) {
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

	char	w_infilenm[256];	// 処理前ファイル名(フルパス)
	char	w_endfilenm[256];	// 処理終了ファイル名(フルパス)
	char	w_filenm[256];		// 処理終了ファイル名
	struct	dirent  **namelist;	// get input file
	FILE	*fp;			// 読込ﾌｧｲﾙﾎﾟｲﾝﾀ

	my_stSYSKNR     pSysKnr;        //

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
			if ( sFncSelSysKnr( &pSysKnr ) !=  RTN_OK ){
				return( RTN_NG );
			}
			// 分注ＥＮＤがきている場合、日次処理の開始チェックを行う
			if ( strcmp( pSysKnr.bchendflg, "1" ) == 0 ){
				/* 日次処理が始まっていたら終了 */
				if( strcmp( pSysKnr.unyflg, "1" ) == 0 ) {
					sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						     "日次処理の開始を確認しました。");
					return( RTN_OK );
				}
			}
		}

                // 対象ファイルの取得
                file_cnt = scandir( pAppEnv.cInputDir, &namelist, (void*)FileFilter, alphasort);
                if ( file_cnt < 0){
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "他サテライト結果情報ファイルの取得(scandir)に失敗しました。") ;
                        continue;
                }

		for( i=0; i < file_cnt; i++ ){
			sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				     "ファイル処理開始 [%s]", namelist[i]->d_name ) ;
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

			// メイン処理
			li_retSts = mainProc( fp , &li_stopFlg);
			if( li_retSts == RTN_NG ){
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"処理中にエラーが発生しました。[FILE_NAME:%s]", w_infilenm ) ;
			}

			// INPUT FILE CLOSE
			fclose( fp );

			// 処理済ファイルの名称変更
			// 変更ファイル名作成
			if ( li_stopFlg == RTN_OK ){
				sprintf( w_endfilenm, "%s/%s" , pAppEnv.cEndFileDirOK,  w_filenm );
			} else {
				sprintf( w_endfilenm, "%s/%s" , pAppEnv.cEndFileDirNG,  w_filenm );
			}
			// 変更ファイルと同名のファイルが存在しないか
			for( ;; ){
				if( open( w_endfilenm, O_RDONLY, 0 ) == EOF ){
					break;
				}
				strcat( w_endfilenm, "_" );
                        }

			// ファイル名変更
			if ( rename( w_infilenm, w_endfilenm ) != 0) {
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "ファイルの移動に失敗しました。[%s]->[%s]:%s", w_infilenm , w_endfilenm, strerror(errno) );
				continue;
			}
			sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				     "ファイル処理終了 [%s]", namelist[i]->d_name ) ;
		}
		// ロックのファイルを作成
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
/*  機能概要  ：他サテライト結果情報ファイル処理                              */
/*  入    力  ：                                                              */
/*   第１引数 ： FILE   pfp     : 入力ファイル識別子                          */
//   第2 引数 :  int    errValue : エラー識別子                               */　
/*  出    力  ： なし                                                         */
/*  復帰情報  ： INT                                                          */
/*               RTN_OK     : 成功                                            */
/*               RTN_NG     : 失敗                                            */
/******************************************************************************/
int	mainProc( pfp , errValue)
FILE	*pfp;
int	*errValue;
{
	/* 依頼受信 */
	my_stFileOTHERKKA	file_kka;	/*  */
	my_stDbOTHERKKA		db_kka;		/* 結果情報	*/

	char    rbuf[RECORDSIZE*2+1];          /* 読み込みｴﾘｱ          */
	int 	li_retSts = 0;

        /* ﾌｧｲﾙの読込 */
        while( ReadFile( rbuf, pfp ) != EOF ){  // read while start ----------->

		/* レコードサイズチェック */
		if( strlen( rbuf ) != ( RECORDSIZE )){
			// ERROR
			*errValue = RTN_NG;
			sFncPutLog( TRCKIND_ERROR, __FILE__, "mainProc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "読み込みレコードサイズエラー[%d]", strlen( rbuf ));
			continue;
		}
		/* ヘッダを読み飛ばす */
		if( strncmp( rbuf, "HD", 2 ) == 0 ){
			continue;
		}
		/* トレーラーを読み飛ばす */
		if( strncmp( rbuf, "TR", 2 ) == 0 ){
			continue;
		}
		
		/* --------------------------------	*/
		/*	処理 							*/
		/* --------------------------------	*/
		memcpy( &file_kka,	rbuf, sizeof( my_stFileOTHERKKA ));
		memset( &db_kka,	0x00, sizeof( my_stDbOTHERKKA ));
		if (file_kka.kkajkcd[0] == '3'){
			/* 編集 */
			li_retSts = EditKekka( &file_kka, &db_kka );
			if (li_retSts != RTN_OK ){
				*errValue = RTN_NG;
				continue;
			}
			/* 他サテライト結果情報へInsertする */
			li_retSts = sFncInsKekka( &db_kka );
			if( li_retSts != RTN_OK ){
				*errValue = RTN_NG;
				continue;
			}
		}
	}

	return( RTN_OK );
}


/******************************************************************************/
/*  関 数 名  ：ReadFile                                                      */
/*  機能概要  ：ファイル読み込み                                              */
/*  入    力  ：                                                              */
/*   第１引数 ： char	file_nm[]	: 入力ファイルポインタ                */
/*  出    力  ： char	rbuf[];		: 読み込みバッファ                    */
/*  復帰情報  ： 0以上			: 正常終了(読込サイズ)                */
/*               EOF			: FILE END                            */
/*               以外			: 失敗                                */
/******************************************************************************/
int     ReadFile( rbuf, pfp )
char		rbuf[];				/* ﾚｺｰﾄﾞ読み込みﾊﾞｯﾌｧ */
FILE		*pfp;				/* ﾌｧｲﾙ識別子 */
{
 	char    func_nm[MYAPP_LEN_FNCNM+1];	/* 関数名称     */

 	/* 初期処理     */
 	strcpy( func_nm, "ReadFile" );

	memset( rbuf, 0x00, sizeof( rbuf ));
	if( fgets( rbuf, FILE_RECSIZE + 1, pfp ) == NULL ){
		/* ﾃﾞｰﾀなし	*/
		return( EOF );
	}
	return( strlen( rbuf ) );
}

/******************************************************************************/
/*  関 数 名  ：EditKekka                                                     */
/*  機能概要  ：結果情報編集 ＆　チェック                                     */
/*  入    力  ：                                                              */
/*   第１引数 ：struct	my_stFileOTHERKKA  *file_kka;   : PNC依頼情報         */
/*  出    力  ：                                                              */
/*   第２引数 ：struct	my_stDbOTHERKKA    *db_kka;     : 結果情報            */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int     EditKekka( file_kka, db_kka )
my_stFileOTHERKKA	*file_kka;	/* ファイル情報  */
my_stDbOTHERKKA		*db_kka;	/* 結果情報構造体 */
{
	//=========================================
	//  EDIT
	//=========================================
	// 1 ＢＭＬ受付年月日
	sprintf( db_kka->utkymd,	"%.4s-%.2s-%.2s",	file_kka->utkymd, &file_kka->utkymd[4], &file_kka->utkymd[6] );
	// 2 依頼書Ｎｏ
	sprintf( db_kka->irino,		"00%-3.3s%-6.6s",	file_kka->irino, &file_kka->irino[5] );
	// 3 項目コード
	memcpy( db_kka->kmkcd,		file_kka->kmkcd,	sizeof( file_kka->kmkcd ));
	// 4 処理日
	sprintf( db_kka->sriymd,	"%.4s-%.2s-%.2s",	file_kka->sriymd, &file_kka->sriymd[4], &file_kka->sriymd[6] );
	// 5 検体Ｎｏ
	sprintf( db_kka->kntno,		"00%-3.3s%-6.6s",	file_kka->kntno, &file_kka->kntno[5] );
	// 6 チェック文字
	memcpy( db_kka->chkmj,		file_kka->chkmj,	sizeof( file_kka->chkmj ));
	// 7 推定材料コード
	memcpy( db_kka->stzrcd,		file_kka->stzrcd,	sizeof( file_kka->stzrcd ));
	// 8 項目略称
	memcpy( db_kka->kmkrs,		file_kka->kmkrs,	sizeof( file_kka->kmkrs ));
	// 9 親項目コード
	memcpy( db_kka->oyakmkcd,	file_kka->oyakmkcd,	sizeof( file_kka->oyakmkcd ));
	// 10 セクションコード
	memcpy( db_kka->seccd,		file_kka->seccd,	sizeof( file_kka->seccd ));
	// 11 分画負荷区分
	memcpy( db_kka->bkfkkbn,	file_kka->bkfkkbn,	sizeof( file_kka->bkfkkbn ));
	// 12 検査実施ラボコード
	memcpy( db_kka->knsjslbcd,	file_kka->knslabcd,	sizeof( file_kka->knslabcd ));
	// 13 結果状況コード
	memcpy( db_kka->kkajkcd,	file_kka->kkajkcd,	sizeof( file_kka->kkajkcd ));
	// 14 パニックレンジフラグ
	memcpy( db_kka->pncrgflg,	file_kka->pncrgflg,	sizeof( file_kka->pncrgflg ));
	// 15 結果換算フラグ
	memcpy( db_kka->kkaksflg,	file_kka->kkaksflg,	sizeof( file_kka->kkaksflg ));
	// 16 結果修正フラグ
	memcpy( db_kka->kkassflg,	file_kka->kkassflg,	sizeof( file_kka->kkassflg ));
	// 17 検査結果１
	memcpy( db_kka->knskka1,	file_kka->knskka1,	sizeof( file_kka->knskka1 ));
	// 18 検査結果２
	memcpy( db_kka->knskka2,	file_kka->knskka2,	sizeof( file_kka->knskka2 ));
	// 19 検査結果２区分
	memcpy( db_kka->knskka2kbn,	file_kka->knskka2kbn,	sizeof( file_kka->knskka2kbn ));
	// 20 結果補足コード
	memcpy( db_kka->kkahskcd,	file_kka->kkahskcd,	sizeof( file_kka->kkahskcd ));
	// 21 結果コメント１
	memcpy( db_kka->kkacmt1,	file_kka->kkacmt1,	sizeof( file_kka->kkacmt1 ));
	// 22 結果コメント２
	memcpy( db_kka->kkacmt2,	file_kka->kkacmt2,	sizeof( file_kka->kkacmt2 ));
	// 23 異常値区分（男）
	memcpy( db_kka->ijkbnm,		file_kka->ijkbnm,	sizeof( file_kka->ijkbnm ));
	// 24 異常値区分（女）
	memcpy( db_kka->ijkbnf,		file_kka->ijkbnf,	sizeof( file_kka->ijkbnf ));
	// 25 異常値区分（不明 
	memcpy( db_kka->ijkbnn,		file_kka->ijkbnn,	sizeof( file_kka->ijkbnn ));
	// 26 指数
	memcpy( db_kka->sdi,		file_kka->sdi,		sizeof( file_kka->sdi ));
	// 27 報告結果
	memcpy( db_kka->hkkki,		file_kka->hkkhjkka,	sizeof( file_kka->hkkhjkka ));
	// 28 報告結果漢字
	memcpy( db_kka->hkkkiknj,	file_kka->hkkhjkkakj,	sizeof( file_kka->hkkhjkkakj ));
	// 29 基準値Ｎｏ
	memcpy( db_kka->kjno,		file_kka->kjntino,	sizeof( file_kka->kjntino ));
	// 30 サンプリングコード
	memcpy( db_kka->smpcd,		file_kka->wscd,		sizeof( file_kka->wscd ));
	// 31 検査ＳＥＱ
	char tmpbuf1[6+1] ,tmpbuf2[6+1];
	memset(tmpbuf1, '\0', sizeof( tmpbuf1 ));
	strncpy( tmpbuf1, file_kka->seq, sizeof( file_kka->seq ));
	sFncTrim( tmpbuf2, tmpbuf1) ;
	if( isCorrectChar( tmpbuf2 ) == RTN_OK ) {
		db_kka->knsseq = atoi( tmpbuf2 );
	} else {
		db_kka->knsseq = 0;
	}
	// 32 更新日
	// 33 登録日

	return( RTN_OK );
}

/********************************************************************************/
/*  関 数 名  ：sFncTrim                                                        */
/*  機能概要  ：指定文字列の前後のスペースを取り除いて文字列をコピーする        */
/*  入    力  ：                                                                */
/*   第２引数 ：char * 変換元文字列                                             */
/*  出    力  ：                                                                */
/*   第１引数 ：char * 変換後文字列                                             */
/********************************************************************************/
void sFncTrim(char *dst, char *src) {
	int dstCnt;
	int srcCnt;
	int Flg;

	for(dstCnt = 0, srcCnt = 0, Flg = 0; src[srcCnt] != '\0'; srcCnt ++) {
		if ((dstCnt == 0) && (src[srcCnt] == '\x20')) {
			continue;
		}
		dst[dstCnt++] = src[srcCnt];
		if (src[srcCnt] != '\x20') {
			Flg = dstCnt;
		}
	}
	dst[Flg] = '\0';
}

/**************************************************************************/
/*      関 数 名  ：isCorrectChar                                         */
/*      機能概要  ：患者属性数値エリアチェック                            */
/*      入        力  ：                                                  */
/*       第１引数 ： char       In[];   : チェック文字列                  */
/*      出        力  ：                                                  */
/*      復帰情報  ： RTN_OK             : 正常終了                        */
/*                               以外   : 失敗                            */
/**************************************************************************/
int isCorrectChar(char *In)
{
	int	ret = RTN_OK;
	int	i = 0;
	int	nSuziFlg =0; /*初めが数字かとうか検索 */
	int	nMaxNum = strlen(In);

	for( i = 0 ; i < nMaxNum ; i++ ) {
		if(In[i] == ' '){
			if(nSuziFlg == 1){
				// DEBUG
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "数値 数字中にSPACE[%s]", In );
				// ERROR
				ret=RTN_NG;
				break;
			}
		}
		else if(In[i] == '.'){
			if(i==0){
				// DEBUG
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "数値 先頭.不可[%s]", In );
				// ERROR
				ret=RTN_NG;
				break;
			}
			if(nSuziFlg == 0){
				// DEBUG
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "数値 先頭.不可[%s]" , In );
				// ERROR
				ret=RTN_NG;
				break;
			}
		}
		else if(In[i] >= '0' && In[i] <= '9'){
			nSuziFlg = 1;
		}
		else{
			// DEBUG
			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "数値 空白.以外不可[%s]" , In );
			// ERROR
			ret=RTN_NG;
			break;
		}
	}

	if(i == nMaxNum){
		ret=RTN_OK;
	}

	return( ret );
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
		return ( 1 );
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
	remove ( pAppEnv.cLockFile );

	/*	データベースクローズ */
	ZdbDisConnect() ;

	/*	共有メモリ削除	*/
	sFncShmDel() ;

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
	char	 cMsg[1024] ;

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
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmget", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}

	//	アタッチ	
	shmData = ( int * ) shmat ( pAppEnv.shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmat", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}

	//	値設定	
	*shmData = 0 ;

	//	デタッチ	
	if ( shmdt ( shmData ) == -1 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
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
int	*pshmData ;
{
	int		*shmData ;

	//	アタッチ	
	shmData = ( int * ) shmat ( pAppEnv.shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmat", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}

	//	値設定	
	*pshmData = *shmData ;

	//	デタッチ	
	if ( shmdt ( shmData ) == -1 ) {
		//	異常終了	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/********************************************************************************/
/*  関 数 名　：sFncShmDel()							*/
/*  機能概要　：共有メモリ削除							*/
/*  入　　力　：                                                                */
/*　 第１引数 ：struct appEnv *	プログラム環境構造体。		 		*/
/*  出　　力　：                                                                */
/*  復帰情報　：int								*/
/*		 0	正常							*/
/*		-1	異常							*/
/********************************************************************************/
static int
sFncShmDel()
{
	int		*shmData ;

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
	endFunction () ;
}
/** End of File ***************************************************************/
