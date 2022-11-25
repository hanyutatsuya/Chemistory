/******************************************************************************/
/* 　ＢＭＬ様向け検査システム  							*/
/*                             							*/
/* 　システム名：次世代システム							*/
/* 　ファイル名：ND101.c              						*/
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

#include "ND101.h"

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
static	int	sFncShmGet ( int *) ;
static	int	sFncShmDel() ;


//	その他
static	int     FileFilter( struct dirent *namelist );
static	void	endFunction();

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
	//      処理スキップファイル移動ディレクトリ
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DIR_SKIP, pAppEnv.cEndFileDirSKIP ) != 0 ) {
		//      異常終了        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_SKIP ) ;
		return ( -1 ) ;
	}
	//      処理対象ファイル拡張子
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_FILE_EXT, pAppEnv.cFileExt ) != 0 ) {
		//      異常終了        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_FILE_EXT ) ;
		return ( -1 ) ;
	}
	//      スキップファイル接頭辞
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_SKIP_FILE_PRE, pAppEnv.cSkipFilePre ) != 0 ) {
		//      異常終了        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_SKIP_FILE_PRE ) ;
		return ( -1 ) ;
	}
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_FILE_EXT_TRG, pAppEnv.cFileExtTrg ) != 0 ) {
		//      異常終了        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_FILE_EXT_TRG ) ;
		return ( -1 ) ;
	}

	//	パラメータファイルクローズ	
	ZbmlPrmClose ( pAppEnv.bp ) ;

	/***
	 ***	共有メモリ生成	
	 ***/
	if ( sFncShmCrt ( ) < 0 ) {
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
int mainFunction()
{
	int	li_retSts = 0;
	int	li_stopFlg = 0;

	int	i = 0;
	char	*p;				// 作業用の文字列ポインタ
	int	file_cnt = 0;
	int	ins_row_cnt = 0;
	bool	flg_skip_file = 0;		// 処理ファイルがスキップファイルかどうか(0:通常 1:スキップファイル)
	char	w_filenm[256];			// 処理ファイル名(拡張子を除く)
	char	w_filenm_trg[256];		// トリガーファイル名(フルパス)
	char	w_infilenm[256];		// 処理前ファイル名(フルパス)
	char	w_endfilenm[256];		// 処理終了ファイル名(フルパス)
	struct	dirent  **namelist;		// get input file
	FILE	*fp;				// 読込ﾌｧｲﾙﾎﾟｲﾝﾀ

	/*	永久ループ 停止コマンドで終了 */
	while ( 1 ) {
		/* 停止コマンド確認 */
		if ( sFncShmGet ( &li_stopFlg ) != 0 ) {
			return( RTN_NG );
		}
		if ( li_stopFlg == 1 ) {
			return( RTN_OK );
		}
                // 対象ファイルの取得
                file_cnt = scandir( pAppEnv.cInputDir, &namelist, (void*)FileFilter, alphasort);
                if ( file_cnt < 0){
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "フロンティアラック情報ファイルの取得(scandir)に失敗しました。") ;
                        continue;
                }
                // 取得した対象ファイル分ループ
		for( i=0; i < file_cnt; i++ ){
			strcpy( w_filenm, namelist[i]->d_name );
			// scadirファイル名のfree
			free( namelist[i] );
			// スキップファイルかどうかを接頭語で判断
			if( strncmp( pAppEnv.cSkipFilePre, w_filenm , strlen( pAppEnv.cSkipFilePre) ) == 0 ) {
				flg_skip_file = 1; // スキップファイル
			} else {
				flg_skip_file = 0; // 通常ファイル
			}
			// 拡張子の削除
			p = strrchr( w_filenm, '.' );
			if ( p != NULL ) {
				*p = 0x00;
			}
			// ファイル名作成
			memset( w_infilenm,  '\0',sizeof( w_infilenm ));
			memset( w_endfilenm, '\0',sizeof( w_endfilenm ));
			sprintf( w_infilenm, "%s/%s%s", pAppEnv.cInputDir, w_filenm, pAppEnv.cFileExt );

			sFncPutLog ( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				     "ファイル処理開始[%s]", w_infilenm ) ;
			// FILE OPEN
			if( ( fp = fopen( w_infilenm, "r" ) ) == NULL ){
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "ファイルオープンに失敗しました。[FILE_NAME:%s]", w_infilenm ) ;
				continue;
			}
			// メイン処理
			li_retSts = mainProc( fp, flg_skip_file, &ins_row_cnt );
			// FILE CLOSE
			fclose( fp );
			// 処理済ファイル名の取得
			if ( li_retSts == RTN_OK ){
				// 処理ファイルがスキップファイルで、さらにスキップする場合は、ファイルを移動して次のファイルを処理する。
				if( flg_skip_file == 1 && ins_row_cnt == 0 ){
					sprintf( w_endfilenm, "%s/%s%s", pAppEnv.cEndFileDirSKIP, w_filenm, pAppEnv.cFileExt );
					if ( rename( w_infilenm, w_endfilenm ) == 0) {
						sFncPutLog ( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
							     "ファイルスキップ[%s]", w_endfilenm ) ;
					} else {
						sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
							     "ファイルスキップ失敗[%s]", w_infilenm ) ;
					}
					continue;
				} else {
					li_retSts = sFncMakeEndFileName( pAppEnv.cEndFileDirOK, w_filenm, pAppEnv.cFileExt, w_endfilenm ) ;
				}
			} else {
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"処理中にエラーが発生しました。[FILE_NAME:%s]", w_infilenm ) ;
				li_retSts = sFncMakeEndFileName( pAppEnv.cEndFileDirNG, w_filenm, pAppEnv.cFileExt, w_endfilenm ) ;
			}
			// ファイル名の取得失敗
			if ( li_retSts != RTN_OK ){
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "ファイル名の取得に失敗しました。[%s]", w_infilenm );
				continue;
			}
			// ファイル名変更
			if ( rename( w_infilenm, w_endfilenm ) != 0) {
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "ファイルの移動に失敗しました。[%s]->[%s]:%s", w_infilenm , w_endfilenm, strerror(errno) );
				continue;
			}
			// 通常ファイルの場合、トリガーファイルが存在するので削除する。
			if( flg_skip_file == 0 ) {
				sprintf( w_filenm_trg, "%s/%s%s", pAppEnv.cInputDir, w_filenm, pAppEnv.cFileExtTrg );
				if ( remove( w_filenm_trg ) != 0 ) {
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						     "トリガーファイルの削除に失敗しました。[%s]", w_filenm_trg );
				}
			}
			sFncPutLog ( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				     "ファイル処理終了[%s%s] レコード数[%d]", w_filenm, pAppEnv.cFileExt, ins_row_cnt ) ;
		}
		sleep( 1 );
	}
	return ( RTN_OK ) ;
}

/******************************************************************************/
/*  関 数 名  ：mainProc                                                      */
/*  機能概要  ：ファイル処理                                                  */
/*  入    力  ：                                                              */
/*   第１引数 ： FILE	*pfp		: 入力ファイル識別子                  */
/*   第２引数 ： bool	flg_skip_file	: スキップファイルかどうか            */
/*  出    力  ： なし                                                         */
/*   第３引数 ： int	*rowCnt		: 処理行数                            */
/*  復帰情報  ： INT                                                          */
/*               RTN_OK     : 成功                                            */
/*               RTN_NG     : 失敗                                            */
/******************************************************************************/
int	mainProc( pfp, flg_skip_file, ins_row_cnt )
FILE	*pfp;
bool	 flg_skip_file;
int	*ins_row_cnt;
{
	/* 依頼受信 */
	my_stFileFRONRACK	pFileFronRack;	/* ファイルレコード情報 */
	my_stDbFRONRACK		*recFronRack;	/* フロンティアラック情報 */

	char    rbuf[MYAPP_RECORD_SIZE+1];		/* 読み込みエリア */
	char    tmp_rbuf[MYAPP_RECORD_SIZE+1];		/* 読み込みエリア */
	int 	li_retSts = 0;
	int 	i = 0;
	int 	recCnt = 0;
	int	rowCnt = 0;

	/* ファイルの読込 */
	while( fgets( rbuf, MYAPP_RECORD_SIZE+1, pfp ) != NULL ) {  // read while start ----------->
		/* スキップファイル出力用に元の文字列を退避する */
		strcpy( tmp_rbuf, rbuf );
		memset( &pFileFronRack, '\0', sizeof(pFileFronRack) );
		/* ファイルレコードを取得する */
		li_retSts = sFncGetFileRecord( rbuf, &pFileFronRack );
		if( li_retSts != RTN_OK ){
			goto error;
		}
		/* ＥＮＤ情報レコードだった場合、ＥＮＤ情報をInsertする */
		if ( strncmp ( pFileFronRack.hkkbn, MYAPP_RECORD_END, strlen( MYAPP_RECORD_END ) ) == 0 ){
			li_retSts = sFncInsEnd( pFileFronRack.sriymd, pFileFronRack.asyrckid, pFileFronRack.hkkbn );
			if( li_retSts != RTN_OK ){
				goto error;
			}
			rowCnt++;
			continue;
		}
		/* オーダー情報から必要な情報を取得する */
		li_retSts = sFncSelKenOrder( pFileFronRack.sriymd, pFileFronRack.asyrckid, pFileFronRack.hkkbn, &recFronRack, &recCnt );
		if( li_retSts != RTN_OK ){
			goto error;
		}
		/* 取得レコード数 */
		if( recCnt == 0 ){
			/* オーダー情報が存在せず、元ファイルがスキップファイルではない場合、スキップファイルを作成する */
			if( flg_skip_file == 0 ){
				li_retSts = sFncMakeSkipFile( pFileFronRack.sriymd, pFileFronRack.asyrckid, tmp_rbuf );
				if( li_retSts != RTN_OK ){
					goto error;
				}
			}
		} else {
			for ( i = 0; i < recCnt; i++ ){
				/* フロンティアラック情報へInsertする */
				li_retSts = sFncInsFronRack( &recFronRack[i] );
				if( li_retSts != RTN_OK ){
					goto error;
				}
			}
			/* フロンティアラック情報へ登録できたレコード数をカウントする */
			rowCnt++;
		}
	}
	/* ファイル読み込み中にエラーが発生していないかチェック */
	if ( feof( pfp ) == 0 ){
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			     "ファイル読み込み中にエラーが発生しています。");
		goto error;
	}

	ZbmlFree( recFronRack );

	/* 途中でエラーが発生しなかった場合はコミット */
	ZdbCommit();

	*ins_row_cnt = rowCnt;

	return( RTN_OK );
error:
	/* 途中でエラーが発生した場合はロールバック */
	ZdbRollback();

	return( RTN_NG );
}

/******************************************************************************/
/*  関 数 名  ：sFncGetFileRecord                                             */
/*  機能概要  ：ファイルレコード取得                                          */
/*  入    力  ：                                                              */
/*   第１引数 ：char *          ファイルレコード情報                          */
/*   第２引数 ：struct *        構造体                                        */
/*  出    力  ：なし                                                          */
/*  復帰情報  ： INT                                                          */
/*               0              : 正常終了                                    */
/*              -1              : 異常終了                                    */
/******************************************************************************/
int sFncGetFileRecord(buff, pFronRack)
char			*buff;
my_stFileFRONRACK	*pFronRack;
{
	char	*pFld[128];
	int	cnt;
	int	offset;
	char	tmpSriymd[8+1];

	memset( pFld, '\0', sizeof( pFld ) );
	/* カンマ区切りのレコードを分割し、DBレコードの構造体に設定する。 */
	cnt = 0;
	offset = 0;;
	pFld[cnt] = &buff[cnt];
	while (buff[offset] != '\0') {
		if (buff[offset] == ',') {
			buff[offset] = '\0';
			cnt++;
			pFld[cnt] = &buff[offset+1];
		}
		if (buff[offset] == '\n') {
			buff[offset] = '\0';
		}
		offset++;
	}

	/* フィールド数チェック。通常レコードかＥＮＤ情報かでチェックを変える。 */
	if ( strncmp (pFld[1], MYAPP_RECORD_END, strlen( MYAPP_RECORD_END ) ) == 0 ){
		if (cnt == 2) {
			sFncPutLog ( TRCKIND_TRACE, __FILE__, "sFncGetFileRecord", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				     "ＥＮＤ情報を受信しました。" ) ;
		} else {
			/* フィールド数が一致しない */
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncGetFileRecord", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "ファイルのフィールド数が合致しません。[%d]", cnt ) ;
			return -1;
		}
		memset( pFronRack->irino, '\0', sizeof( pFronRack->irino ) );
	} else {
		if (cnt != 3) {
			/* フィールド数が一致しない */
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncGetFileRecord", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "ファイルのフィールド数が合致しません。[%d]", cnt ) ;
			return -1;
		}
		strncpy( pFronRack->irino, pFld[3], sizeof( pFronRack->irino )-1 );
	}

	/* 各フィールドを格納する。 */
	strncpy( tmpSriymd, pFld[0], sizeof( tmpSriymd )-1 );
	sprintf( pFronRack->sriymd, "%4.4s-%2.2s-%2.2s", tmpSriymd, &tmpSriymd[4], &tmpSriymd[6]);
	strncpy( pFronRack->hkkbn, pFld[1], sizeof( pFronRack->hkkbn )-1 );
	strncpy( pFronRack->asyrckid, pFld[2], sizeof( pFronRack->asyrckid )-1 );     /* ラックID */

	return( 0 );
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
	char    *w_fext;
	struct  stat    statbuf;                                // get input file status

	// ディレクトリは除く
	sprintf( w_fnm, "%s/%s", pAppEnv.cInputDir, namelist->d_name );
	stat( w_fnm, &statbuf );
	if( S_ISDIR( statbuf.st_mode )){
		// 対象外
		return( 0 );
	}

	// 対象ファイルの拡張子による判断(トリガーファイル)
	w_fext = strrchr( namelist->d_name, '.' ) ;

	if( strcmp( w_fext, pAppEnv.cFileExtTrg ) == 0 ){
		// OK
		return ( 1 );
	}

	// スキップファイルの場合はトリガーファイルは存在しないため、データファイルを返す。
	if( strncmp( pAppEnv.cSkipFilePre, namelist->d_name, strlen( pAppEnv.cSkipFilePre ) ) == 0 ) {
		if( strcmp( w_fext, pAppEnv.cFileExt ) == 0 ){
			// OK
			return ( 1 );
		}
	}
	return ( 0 );
}

/******************************************************************************/
/*  関 数 名  ：sFncMakeEndFileName                                           */
/*  機能概要  ：終了ファイル名の作成                                          */
/*  入    力  ：                                                              */
/*   第１引数 ：char *          作成ディレクトリ                              */
/*   第２引数 ：char *          ファイル名(拡張子除く)                        */
/*   第３引数 ：char *          拡張子                                        */
/*  出    力  ：                                                              */
/*   第４引数 ：char *          ファイル名(フルパス)                          */
/*  復帰情報  ： INT                                                          */
/*               0              : 正常終了                                    */
/*              -1              : 異常終了                                    */
/******************************************************************************/
int sFncMakeEndFileName( pDirName, pFileNameBase, pFileNameExt, pEndFileName )
char	*pDirName;
char	*pFileNameBase;
char	*pFileNameExt;
char	*pEndFileName;
{
	int	cnt = 0;
	
	sprintf( pEndFileName, "%s/%s%s", pDirName, pFileNameBase, pFileNameExt );

	// 変更ファイルと同名のファイルが存在しないか
	for( ;; ){
		if( open( pEndFileName, O_RDONLY, 0 ) == EOF ){
			break;
		}
		cnt++;
		sprintf ( pEndFileName, "%s/%s_%d%s", pDirName, pFileNameBase, cnt , pFileNameExt);
	}

	return ( RTN_OK );
}

/******************************************************************************/
/*  関 数 名  ：sFncMakeSkipFile                                              */
/*  機能概要  ：スキップファイル出力                                          */
/*  入    力  ：                                                              */
/*   第１引数 ：char *          処理日(ファイル名設定用)                      */
/*   第２引数 ：char *          アッセイラックＩＤ(ファイル名設定用)          */
/*   第３引数 ：char *          ファイルレコード情報                          */
/*  出    力  ：なし                                                          */
/*  復帰情報  ： INT                                                          */
/*               0              : 正常終了                                    */
/*              -1              : 異常終了                                    */
/******************************************************************************/
int sFncMakeSkipFile( pSriymd, pAsyrckid, fileRecord )
char	*pSriymd ;
char	*pAsyrckid ;
char	*fileRecord ;
{
	int	li_retSts = 0;
	char	w_filenm_base[256];		// 処理ファイル名(拡張子を除く)
	char	w_filenm[256];			// 処理ファイル名(フルパス)
	FILE	*fp;				/* スキップファイル出力用 */

	sprintf( w_filenm_base, "%s_%4.4s%2.2s%2.2s_%s", pAppEnv.cSkipFilePre, pSriymd, &pSriymd[5], &pSriymd[8], pAsyrckid );
	li_retSts = sFncMakeEndFileName( pAppEnv.cEndFileDirSKIP, w_filenm_base, pAppEnv.cFileExt, w_filenm );
	if( li_retSts != RTN_OK ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncMakeSkipFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "スキップファイル名の取得に失敗しました。[SRIYMD:%s ASYRCKID:%s]", pSriymd, pAsyrckid ) ;
		return( RTN_NG );
	}

	if( ( fp = fopen( w_filenm, "w" ) ) == NULL ){
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncMakeSkipFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "スキップファイルオープンに失敗しました。[FILE_NAME:%s]", w_filenm ) ;
		return( RTN_NG );
	}

	if( fputs( fileRecord, fp ) < 0 ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncMakeSkipFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "スキップファイルの出力に失敗しました。[FILE_NAME:%s]", w_filenm ) ;
		return( RTN_NG );
	}
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "sFncMakeSkipFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			     "スキップファイルを出力しました。[FILE_NAME:%s]", w_filenm ) ;
	fclose( fp );

	return ( RTN_OK );
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
	pAppEnv.shm_Id = shmget ( (key_t)pAppEnv.shm_Key, MYAPP_SHM_SIZE, 0666 | IPC_CREAT ) ;
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

	exit( 0 );
}
/** End of File ***************************************************************/
