/******************************************************************************/
/* 　ＢＭＬ様向け検査システム  							*/
/*                             							*/
/* 　システム名：次世代システム							*/
/* 　ファイル名：ND102.c              						*/
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

#include "ND102.h"

/******************************************************************************/
/* Define定義                                                                 */
/******************************************************************************/
//	TRACE
#if defined ( _TRACE )
#define malloc(a)   _malloc(a, __FILE__, __LINE__)
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
	//      処理対象ファイル拡張子
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_FILE_EXT, pAppEnv.cFileExt ) != 0 ) {
		//      異常終了        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_FILE_EXT ) ;
		return ( -1 ) ;
	}

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

	char	w_infilenm[256];	// 処理前ファイル名(フルパス)
	char	w_endfilenm[256];	// 処理終了ファイル名(フルパス)
	char	w_endfilenm_base[256];	// 処理終了ファイル名
	char	w_filenm[256];		// 処理ファイル名
	struct	dirent  **namelist;	// get input file
	FILE	*fp;			// 読込ﾌｧｲﾙﾎﾟｲﾝﾀ

	/***
	 ***		永久ループ
	 ***		停止コマンドで終了
	 ***/
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
				     "他サテライト結果情報ファイルの取得(scandir)に失敗しました。") ;
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

			sFncPutLog ( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "ファイル処理開始[%s]", w_infilenm );

			// INPUT FILE OPEN
			if( ( fp = fopen( w_infilenm, "r" ) ) == NULL ){
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "ファイルオープンに失敗しました。[FILE_NAME:%s]", w_infilenm ) ;
				continue;
			}

			// メイン処理
			li_retSts = mainProc( fp );
			if( li_retSts == RTN_NG ){
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"処理中にエラーが発生しました。[FILE_NAME:%s]", w_infilenm ) ;
			}

			// INPUT FILE CLOSE
			fclose( fp );

			// 処理済ファイルの名称変更
			// 変更ファイル名作成
			if ( li_retSts == RTN_OK ){
				sprintf( w_endfilenm, "%s/%s" , pAppEnv.cEndFileDirOK,  w_filenm );
			} else {
				sprintf( w_endfilenm, "%s/%s" , pAppEnv.cEndFileDirNG,  w_filenm );
			}
			// 変更ファイルと同名のファイルが存在しないか
			int cnt = 0;
			strcpy ( w_endfilenm_base, w_endfilenm );
			for( ;; ){
				int fd = open( w_endfilenm, O_RDONLY, 0 );
				if( fd == EOF ){
					break;
				} else {
					close( fd );
				}
				sFncPutLog ( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "重複ファイル有り[%s]", w_endfilenm );
				cnt++;
				sprintf ( w_endfilenm, "%s.%d", w_endfilenm_base, cnt );
                        }

			// ファイル名変更
			if ( rename( w_infilenm, w_endfilenm ) != 0) {
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "ファイルの移動に失敗しました。[%s]->[%s]:%s", w_infilenm , w_endfilenm, strerror(errno) );
				continue;
			}

			sFncPutLog ( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "ファイル処理完了[%s]", w_endfilenm );
		}
		sleep( 1 );
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
int	mainProc( pfp )
FILE	*pfp;
{
	/* 依頼受信 */
	my_stORDERRACK	file_kka;	/* ファイル情報 */

	char    rbuf[RECORDSIZE*2+1];          /* 読み込みｴﾘｱ          */
	int 	li_retSts = 0;

        /* ﾌｧｲﾙの読込 */
	while( fgets( rbuf, FILE_RECSIZE + 1, pfp ) != NULL ){	// read while start ----------->
		
		/* --------------------------------	*/
		/*	処理 				*/
		/* --------------------------------	*/
		/* ファイルレコードを取得する */
		li_retSts = sFncGetFileRecord( rbuf, &file_kka );
		if( li_retSts != RTN_OK ){
			return( RTN_NG );
		}

		/* 他サテライト結果情報へInsertする */
		li_retSts = sFncInsRackOeder( &file_kka );
		if( li_retSts != RTN_OK ){
			return( RTN_NG );
		}
	}

	return( RTN_OK );
}

/********************************************************************************/
/*  関 数 名  ：sFncGetFileRecord						*/
/*  機能概要  ：ファイルレコード取得						*/
/*  入    力  ：								*/
/*   第１引数 ：char	*  	ファイルレコード情報				*/
/*   第２引数 ：struct	*	ファイル情報構造体				*/
/*  出    力  ：なし								*/
/*  復帰情報  ： INT								*/
/*		 0		: 正常終了					*/
/*		 1		: 異常終了    					*/	
/********************************************************************************/
int sFncGetFileRecord(buff, pOrderRack)
char			*buff;
my_stORDERRACK		*pOrderRack;
{
	char	*pFld[128];
	int	cnt;
	int	offset;

	memset( pFld, '\0', sizeof( pFld ) );
	/* カンマ区切りのレコードを分割し、DBレコードの構造体に設定する。 */
	cnt = 0;
	offset = 0;;
	pFld[cnt] = &buff[cnt];
	cnt++;
	while (buff[offset] != '\0') {
		if (buff[offset] == ',') {
			pFld[cnt++] = &buff[offset+1];
			buff[offset] = '\0';
		}
		if (buff[offset] == '\n') {
			buff[offset] = '\0';
		}
		offset++;
	}

	if (cnt != 2) {
		/* フィールド数が一致しない */
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncGetFileRecord", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		             "ファイルのフィールド数が合致しません。" ) ;
		return -1;
	}

	/* 各フィールドを格納する。 */
        sprintf( pOrderRack->knskisymd, pFld[0], sizeof( pOrderRack->knskisymd )-1 );
	strncpy( pOrderRack->asyrckid, pFld[1], sizeof( pOrderRack->asyrckid )-1 );     /* ラックID */

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

	// 対象ファイルの拡張子による判断
	if( strcmp( pAppEnv.cFileExt, "" ) != 0 ) {
		w_fext = strrchr( namelist->d_name, '.' ) ;
		if( strcmp( w_fext, pAppEnv.cFileExt ) == 0 ){
			// OK
			return ( 1 );
		}
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
	exit ( 0 ) ;
}
/** End of File ***************************************************************/
