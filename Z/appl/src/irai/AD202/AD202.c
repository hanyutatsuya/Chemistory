/******************************************************************************/
/*   ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/*   システム名：次世代システム                                               */
/*   ファイル名：AD202.c                                                      */
/*   概      要：検査受付（緊急検査依頼展開）緊急検査情報展開                 */
/*	 OS        ：SUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   言語      ：DB2/C                                                        */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/03/03     INTEC.INC      CREATE                             */
/*  1.01     2006/05/01     INTEC.INC      SJIS,項目追加対応                  */
/*  1.02     2006/05/03     INTEC.INC      UPDATE 引数としてINIファイル指定   */
/*  1.04     2007/06/01     INTEC.INC      DBエラー時異常終了させる           */
/*  3.01     2007/06/01     INTEC.INC      緊急運用変更に伴う追加修正         */
/*  4.00     2009/01/06     Merits K.Ameno 施設コード増桁 通信仕様変更対応    */
/******************************************************************************/

/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "bmllog.h"
#include "AD202.h"

/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/
iconv_t		G_ic;						// with iconv
char		G_fnm[256];					// InputFileName
char		G_err[MYAPP_LEN_ERR+1];		// LogMessage(errcode)
char		G_msg[MYAPP_LEN_MSG+1];		// LogMessage
char		G_utkymd[10+1];				// LogMessage(csv)
char		G_irino[11+1];				// LogMessage(csv)
char		G_kntno[13+1];				// LogMessage(csv)
int			G_zssdino;					// 1.04 LogMessage(csv)
char		G_kmkcd[7+1];				// LogMessage(csv)
int			G_line;						// InputFileLineNo

struct      _KJNMST     *pKjn;

/******************************************************************************/
/*  関 数 名  ：main                                                          */
/*  機能概要  ：デーモン用主制御                                              */
/*  入    力  ：                                                              */
/*   第１引数 ：int		argc	: パラメタ数                                  */
/*   第２引数 ：char	*argv[]	: パラメタリスト                              */
/*  出    力  ：                                                              */
/*   なし                                                                     */
/*  復帰情報  ：0       正常終了                                              */
/*            ：1		異常終了                                              */
/******************************************************************************/
int		main( argc, argv )
int			argc;
char		*argv[];
{
	char	func_nm[MYAPP_LEN_FNCNM+1];	// 関数名称
	int		ret;						// 関数戻り値
	int		inp_cnt, i;
	char	w_infilenm[256];			// 処理前ファイル名
	char	w_endfilenm[256];			// 処理終了ファイル名
	struct	dirent	**namelist;			// get input file
	FILE	*fp;						// 読込ﾌｧｲﾙﾎﾟｲﾝﾀ

	struct	SHM	stcShm;					// 終了判断共有メモリ
	int		li_stopFlg = 0;				// 終了判断
	
	/*=====================================================*/
	/*	バックグラウンド実行                               */
	/*=====================================================*/
	//if ( daemon ( 0, 0 ) < 0 ) {
	//		exit( 1 );
	//}

	/*=====================================================*/
	/*	初期設定                                           */
	/*=====================================================*/
	strcpy( func_nm,	"main" );
	memset( G_msg,		'\0', sizeof( G_msg ) );
	memset( G_utkymd,	'\0', sizeof( G_utkymd ) );
	memset( G_irino,	'\0', sizeof( G_irino ) );
	memset( G_kntno,    '\0', sizeof( G_kntno ) );
	memset( G_kmkcd,    '\0', sizeof( G_kmkcd ) );
	G_line=0;
	fp = NULL;

	// パラメータ取得
	if( ParamCheckProc( argc, argv, &stcShm ) != RTN_OK ){
		/* ﾍﾙﾌﾟﾒｯｾｰｼﾞ出力	*/
		DispHelpMsg( argc, argv );
		exit( 1 );
	}

	/* 2重起動チェック	*/
	if( DaemonCheckProc( argc, argv ) != RTN_OK ){
		sprintf( G_msg, "２重起動防止のため、処理を終了します。" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
		exit( 1 );
	}

	// 共有メモリ生成
	if( sFncShmCrt ( &stcShm ) < 0 ) {
		sprintf( G_msg, "共有メモリ生成に失敗したため、処理を終了します。" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		exit( 1 );
	}

    // DB2との接続 
	if(( ret = Ydbconn( )) != RTN_OK ){
		sprintf( G_err, "sqlcode=[%d]", ret );
		sprintf( G_msg, "DB2との接続に失敗しました。" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		exit( 1 );
     }

    //  基準日取得
    GetKjnymd( );

	// 基準値マスタ取得 (緊急項目)
	if( GetKjnmst( NULL ) != RTN_OK ){
		sprintf( G_msg, "基準値マスタの取得に失敗しました。" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		Ydbdisconn( );
		exit( 1 );
	}

	/* FILE OPEN FOR ICONV */
	// 1.01 DELL	G_ic = iconv_open( "EUC-JP", "SHIFT-JIS" );

	/*=====================================================*/
	/* メインルーティン                                    */
	/*=====================================================*/
	for( ; ; ){		//  ......................................... daemon start
		// 対象ファイルの取得
		inp_cnt = scandir( stcPRM.ifp_indir, &namelist, 
					(void*)FileFilter, alphasort);
		if ( inp_cnt < 0){
			sprintf( G_err, "%d", errno );
			sprintf( G_msg, "緊急依頼ファイルの情報取得(scandir)に"
							"失敗しました。" );
			EditCsvMsg( G_msg );
			LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			ret=1;
			break;
		} 

		for( i=0; i < inp_cnt; i++ ){	// <------------------ファイルの件数分
			//------------------
			// 	緊急受付日取得
			//------------------
			if( GetKjnymd( ) != RTN_OK ){
				sprintf( G_msg, "緊急受付年月日の取得に失敗しました。" );
				EditCsvMsg( G_msg );
				LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, 
												__FILE__, __LINE__ );
				break;
			}

			//------------------
			// INPUT FILE OPEN
			//------------------
				// ファイル名作成
			memset( w_infilenm,		'\0',sizeof( w_infilenm ));
			memset( w_endfilenm,	'\0',sizeof( w_endfilenm ));
			sprintf( w_infilenm, "%s/%s", 
					stcPRM.ifp_indir, namelist[i]->d_name );

				// INPUT FILE OPEN
			if( ( fp = fopen( w_infilenm, "r" ) ) == NULL ){
				ret = RTN_NG;
					// WARNING
				sprintf( G_err, "%d", errno );
				sprintf( G_msg, 
					"[%s]ファイルオープンに失敗しました。", w_infilenm );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm
						, __FILE__, __LINE__ );
				continue;
			}
			strcpy( G_fnm, namelist[i]->d_name );

				// scadirファイル名のfree
			free( namelist[i] );

			//------------------
			// 登録処理 
			//------------------
/* UPD 1.04
DEL			ret = KinqProc( fp );
*/
			ret = KinqProc( fp , &li_stopFlg );
			if( ret == RTN_NG ){
				sprintf( G_msg, "[%s]処理中にエラーが発生しました。"
					,w_infilenm );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm
						, __FILE__, __LINE__ );

				// 1.04 DBエラー時異常終了させる
                if(li_stopFlg == 1)
                {
                    sprintf(G_msg, "[[DB ERROR]]");
                    //printf("li_stopFlg %d", li_stopFlg);
                    LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm
                        , __FILE__, __LINE__ );
                    fclose( fp );
                    break;
                }
			}

			//------------------
			// INPUT FILE CLOSE
			//------------------
			fclose( fp );

			//---------------------------
			// 処理済ファイルの名称変更
			// ＊SKIP LOT有の場合はrenameしない
			//---------------------------
			if( ret != RTN_SKIP ){
					// 変更ファイル名作成
				sprintf( w_endfilenm, "%s/%s%s" 
					,stcPRM.ifp_indir , stcPRM.ifp_endfprx,  G_fnm );
				
					// 変更するファイルが存在しないか
				for( ;; ){
					if( open( w_endfilenm, O_RDONLY, 0 ) == EOF ){
						break;
					}
					strcat( w_endfilenm, "_" );
				}
					// ファイル名変更
				rename( w_infilenm, w_endfilenm );

					// TRACE
				sprintf( G_msg, 
					"処理済依頼ファイル[%s]の名前を[%s]に変更しました。"
					, w_infilenm, w_endfilenm );
				LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, 
						__FILE__, __LINE__);
			}

			//------------------
			// 終了判断
			//------------------
				// 共有メモリ取得
			// 1.04 DBエラー時異常終了させる
            if(li_stopFlg != 1)
            {
			if( sFncShmGet ( &stcShm, &li_stopFlg ) < 0 ){
					// 終了
				li_stopFlg = 1;

					// WARNING
				sprintf( G_msg, 
					"共有メモリ生成に失敗したため、処理を抜けます。" );
				EditCsvMsg( G_msg );
				LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
									__FILE__, __LINE__ );
			}
			}
			if( li_stopFlg == 1 ){
				break;
			} 
		} 	// ---------------------------------------------> ファイルの件数分

		// scandir ファイル名の free
		free( namelist );

		//------------------
		// 終了判断
		//------------------
			// 共有メモリ取得

		// 1.04 DBエラー時異常終了させる
		if(li_stopFlg != 1)
		{
		if( sFncShmGet ( &stcShm, &li_stopFlg ) < 0 ){
				// WARNING
			sprintf( G_msg, "共有メモリ生成に失敗したため、処理を終了します。");
			EditCsvMsg( G_msg );
			LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			break;
		}
		}
		if( li_stopFlg == 1 ){
				// TRACE
			sprintf( G_msg, "終了指示が出たため、処理を終了します。");
			LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			break;
		} 

		// CONTINUE
			// DEBUG
		sprintf( G_msg, "SLEEP.....[%d]", stcPRM.myp_sleep );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

		sleep( stcPRM.myp_sleep );

	}	// ...................................................... daemon end

	/*=====================================================*/
	/*	終了処理                                           */
	/*=====================================================*/
	// ICONV CLOSE
	// 1.01 DELL	iconv_close( G_ic );

	// DB2との接続解除
	if(( ret = Ydbdisconn( )) != RTN_OK ){
		// ERROR
		sprintf( G_msg, "DB2との接続解除に失敗しました。" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);

		ret=1;
	}
	
	// 基準値マスタの領域を解放
	if( pKjn != NULL ){
		// TRACE
		strcpy( G_msg, "基準値マスタの領域を解放。" );
		LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

		 free( pKjn );
	}

	// 共有メモリ削除
	sFncShmDel ( &stcShm ) ;

	// TRACE
	strcpy( G_msg, "ログ出力終了。" );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

    /* LOG CLOSE */
	ZbmlCloseLog( );

	exit( ret );
}

/******************************************************************************/
/*  関 数 名  ：DispHelpMsg                                                   */
/*  機能概要  ：HELPメッセージ出力                                            */
/*  入    力  ：                                                              */
/*   第１引数 ：int		argc	: パラメタ数                                  */
/*   第２引数 ：char	*argv[]	: パラメタリスト                              */
/*  出    力  ：なし                                                          */
/*  復帰情報  ： INT                                                          */
/*               RTN_OK     : 成功                                            */
/*               RTN_NG     : 失敗                                            */
/******************************************************************************/
void	DispHelpMsg( argc, argv )
int			argc;
char		*argv[];
{
fprintf(stderr,"説明:緊急検査情報展開\n" );
fprintf(stderr,"    :検査受付（緊急検査依頼展開）患者情報・依頼情報を登録します\n" );
fprintf(stderr,"     緊急依頼取得ディレクトリ[%s]\n", stcPRM.ifp_indir );
fprintf(stderr," \n" );
fprintf(stderr,"   :tst_zok\n" );
fprintf(stderr,"     -LG ログファイル名(省略時:%s.log)\n", stcPRM.myp_exefile );
fprintf(stderr,"     -SD 世代番号(省略時:01)\n" );
fprintf(stderr,"\t[-dbg|-DBG]\n");
	return;
}

/******************************************************************************/
/*  関 数 名  ：ParamCheckProc                                                */
/*  機能概要  ：パラメータ取得＆チェック                                      */
/*  入    力  ：                                                              */
/*   第１引数 ：int		argc	: パラメタ数                                  */
/*   第２引数 ：char	*argv[]	: パラメタリスト                              */
/*  出    力  ：なし                                                          */
/*  復帰情報  ： INT                                                          */
/*               RTN_OK     : 成功                                            */
/*               RTN_NG     : 失敗                                            */
/******************************************************************************/
int		ParamCheckProc( argc, argv, stcShm )
int			argc;
char		*argv[];
struct		SHM		*stcShm;
{
	char	func_nm[MYAPP_LEN_FNCNM+1];	/* 関数名称	 */
	char	*p_fini;					/* 1.02 INI FILE 名称    */
	char	*cp;						/* 対象パラメタ */
	int		ret=RTN_OK;
	int		i;

	/* 初期設定	*/
	strcpy( func_nm,	"ParamCheckProc" );
	memset( &stcPRM,	'\0', sizeof( stcPRM ));

	/* 実行プログラム名の設定 */
	for( cp = argv[0], cp += strlen( cp ); cp != argv[0]; --cp ) {
		if( *cp == '/' || *cp == '\\' ) {
			cp++;
			break;
		}
	}
	// 1.02 INI FILE を引数から受取る
    if( argc >= 2 ){
        p_fini = argv[1];
    } else {
        p_fini = MYAPP_INIFILE;
    }
	strncpy( stcPRM.myp_exefile, cp, sizeof( stcPRM.myp_exefile ) - 1 );
	stcPRM.myp_debug=0;
	stcPRM.myp_sleep=10;
	stcPRM.myp_sedai=0;
	
	//-------------------------------
	// LOG出力初期処理
	//-------------------------------
    cp = GetIniFile( "SERVER.LOG", "LOGINI", p_fini );
    if( cp != NULL ) {
		// 環境変数($HOME)を展開してからセット
		strcpy( stcPRM.lgp_comlog, EnvRef( cp ));
    }
		// ログiniファイルオープン
	if ( ZbmlOpenLog( stcPRM.lgp_comlog ) != 0 ){
			return( RTN_NG );
	}
	strcpy( G_msg, "ログ出力開始" );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	//-------------------------------
	// DB PARAM
	//-------------------------------
    cp = GetIniFile( "DB2.CNCT", "DBALIAS", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.dbp_dbAlias );
    }
    cp = GetIniFile( "DB2.CNCT", "USER", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.dbp_user );
    }
    cp = GetIniFile( "DB2.CNCT", "PSWD", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.dbp_pswd );
    }

	//-------------------------------
	// HOST  PARAM
	//-------------------------------
    cp = GetIniFile( "HOST.PARA", "HOSTDIR", p_fini );
    if( cp != NULL ) {
		// 環境変数($HOME)を展開してからセット
		strcpy( stcPRM.ifp_indir, EnvRef( cp ));
    }
    cp = GetIniFile( "HOST.PARA", "INFPRX", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_infprx );
    }
    cp = GetIniFile( "HOST.PARA", "ENDFPRX", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_endfprx );
    }

	//-------------------------------
	// 共有メモリキー取得
	//-------------------------------
	cp = GetIniFile( "MYAPP.PARA", "MYAPP_SHMKEY", p_fini );
    if( cp != NULL ) {
		stcShm->shm_Key = atoi ( cp ) ;
    }

	//-------------------------------
	// MYAPP PARAM
	//-------------------------------
    cp = GetIniFile( "MYAPP.PARA", "MYAPP_SLEEP", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%d", &stcPRM.myp_sleep );
    }
    cp = GetIniFile( "MYAPP.PARA", "MYAPP_SEDAI", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%d", &stcPRM.myp_sedai );
    }
    cp = GetIniFile( "MYAPP.PARA", "MYAPP_ZAIRYO", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", &stcPRM.myp_zairyo );
    }
    cp = GetIniFile( "MYAPP.PARA", "MYAPP_DEBUG", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%d", &stcPRM.myp_debug );
    }

	sprintf( G_msg, "G_exefile [%s]",	stcPRM.myp_exefile );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "DBP       [%s-%s-%s]"
		, stcPRM.dbp_dbAlias, stcPRM.dbp_user, stcPRM.dbp_pswd );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "HOSTDIR   [%s]",	stcPRM.ifp_indir );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "INFPRX    [%s]",	stcPRM.ifp_infprx );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "ENDFPRX   [%s]",	stcPRM.ifp_endfprx );

	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "logini    [%s]",	stcPRM.lgp_comlog );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "G_sleep   [%d]",	stcPRM.myp_sleep );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "G_sedai   [%d]",	stcPRM.myp_sedai );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "G_zairyo  [%s]",	stcPRM.myp_zairyo );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  関 数 名  ：GetKjnymd                                                     */
/*  機能概要  ：緊急受付日取得                                                */
/*  入    力  ：なし                                                          */
/*  出    力  ：なし                                                          */
/*  復帰情報  ： INT                                                          */
/*               RTN_OK     : 成功                                            */
/*               RTN_NG     : 失敗                                            */
/******************************************************************************/
int		GetKjnymd( )
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	 */
	int		ret=RTN_OK;

	struct	_SYSKNRMST	knr;

	/* 初期設定	*/
	strcpy( func_nm,	"GetKjnymd" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	// 緊急受付日の取得
	memset( &knr,	'\0',	sizeof( struct _SYSKNRMST ) );
	if(( ret = SelSysknrmst( &knr )) == RTN_OK ){
		strcpy( stcPRM.myp_kjnymd,	knr.kkkjsriymd );
		sprintf( G_msg, "緊急受付日を[%s]とします。" ,stcPRM.myp_kjnymd );
	}
	// TRACE
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  関 数 名  ：FileFilter                                                    */
/*  機能概要  ：ファイルフィルター【コールバック関数】                        */
/*  入    力  ：                                                              */
/*   第１引数 ：struct		dirent *     ディレクトリ構造体                   */
/*  出    力  ：なし                                                          */
/*  復帰情報  ： INT                                                          */
/*               0		: 対象外ファイル                                      */
/*               1		: 対象ファイル                                        */
/******************************************************************************/
static	int		FileFilter( namelist )
struct	dirent	*namelist ;
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	 */
	char	w_fnm[256];
	struct	stat	statbuf;				// get input file status

	strcpy( func_nm, "FileFilter" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	// ディレクトリは除く
	sprintf( w_fnm, "%s/%s", stcPRM.ifp_indir, namelist->d_name );
	stat( w_fnm, &statbuf );
	if( S_ISDIR( statbuf.st_mode )){
		// DEBUG
		sprintf( G_msg, "DIR SKIP mode: 0%o [%s]" ,statbuf.st_mode, w_fnm );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
		// 対象外
		return( 0 );
	}
	// 処理済PREFIXに合致するものは除く
	if(( strcmp( stcPRM.ifp_endfprx, "" ) != 0 )
	 &&( memcmp( namelist->d_name, stcPRM.ifp_endfprx
					, strlen( stcPRM.ifp_endfprx )) == 0 )){
		// DEBUG
		sprintf( G_msg, "END FILE SKIP mode: 0%o [%s]" ,statbuf.st_mode, w_fnm);
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
		// 対象外
		return( 0 );
	}
	// 対象ファイルの先頭or拡張子による判断
	if( memcmp( namelist->d_name, stcPRM.ifp_infprx
					, strlen( stcPRM.ifp_infprx )) == 0 ){
		// DEBUG
		sprintf( G_msg, "処理対象 mode: 0%o [%s]" ,statbuf.st_mode, w_fnm );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
		// OK
		return ( 1 );
	}
	// DEBUG
	sprintf( G_msg, "先頭文字列が異なる[%s]" , namelist->d_name );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return ( 0 );
}

/******************************************************************************/
/*  関 数 名  ：KinqProc                                                      */
/*  機能概要  ：AS400 緊急依頼ファイル処理                                    */
/*  入    力  ：                                                              */
/*   第１引数 ： FILE	pfp	: 入力ファイル識別子                              */
/*  出    力  ： なし                                                         */
/*  復帰情報  ： INT                                                          */
/*               RTN_OK     : 成功                                            */
/*               RTN_NG     : 失敗                                            */
/******************************************************************************/
//1.04 int		KinqProc( pfp )
int		KinqProc( pfp , stopValue )
FILE    	*pfp;
int			*stopValue;						// 1.04 ADD
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称		*/
	int		ret;							/* 関数戻り値	*/

	/* 依頼受信KINQ format(S-JIS) */
	struct	AS4IRAI			kinq;		/* PNC受信トレーラー(S-JIS) */

	struct	_KANJYA			kan;		/* 患者情報	*/
	struct	_IRAI			irai;		/* 依頼情報	*/
	struct	KOMST			*kom;		/* 依頼項目情報構造体 */
	struct  JIDOIRAI        *pJir;      // 1.04 ADD 自動発生項目情報
	struct	CNT				stcCNT;		/* 件数情報		*/

	char	rbuf[KINQ_RECSIZE+1];		/* 読み込みｴﾘｱ		*/
	char	key_uymd[8+1];				/* Ver 4.00 8桁に拡張 */
	char	key_kntno[11+1];			/* Ver 4.00 11桁に拡張 */
	char	key_lot[2+1];
	char	w_ymd[7];
	char	w_str[200];
	int		wcnt_kan=0;					/* 患者情報登録件数*/
	int		wcnt_iri=0;					/* 依頼情報登録件数*/
	int		wcnt_lot=0;					/* LOT患者情報登録件数*/
	int		i,j;						/* index		*/
	int		kmax = IKOM_MAX, lotno;

	int		nSQLErrorValue;				// 1.04 DBエラー時異常終了させる
    int     jd_max;                     // 1.04 ADD 自動発生項目数
    char    w_age[3+1];                 /* 1.04 ADD 年齢         */
    char    w_age_kbn[1+1];             /* 1.04 ADD 年齢区分         */
	int     KnkyulotIns_Ret = 0;        /* 緊急LOTNOテーブルINSERT結果取得領域 */
	int     KanjyaIns_Ret = 0;          /* 患者テーブルINSERT結果取得領域 */
	int     IraiIns_Ret = 0;            /* 依頼テーブルINSERT結果取得領域 */

	/* 初期設定	*/
	strcpy( func_nm,	"KinqProc" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ｸﾘｱ	*/
	ret = RTN_OK;

	stcCNT.cnt_irai = stcCNT.cnt_irai_err = 0;
	stcCNT.cnt_skip = stcCNT.cnt_exc = stcCNT.cnt_sumi = 0;
	stcCNT.cnt_kanjya=stcCNT.cnt_dbirai=0;
	wcnt_kan = wcnt_iri = wcnt_lot = 0;
	memset( key_uymd, '\0', sizeof( key_uymd ));
	memset( key_kntno, '\0', sizeof( key_kntno ));
	memset( key_lot,  '\0', sizeof( key_lot ));

	// 緊急受付日の退避	(YYYYMMDD　に変更)
	sprintf( key_uymd,	"%.4s%.2s%.2s", &stcPRM.myp_kjnymd[0]
				,&stcPRM.myp_kjnymd[5], &stcPRM.myp_kjnymd[8] );

	sprintf( G_msg,	"受付（緊急検査依頼展開） 患者情報・依頼情報登録開始"
		" : 緊急依頼ファイル名[%s]", G_fnm );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	// DEBUG
	sprintf( G_msg, "INFILE[%s] START!!----->", G_fnm );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	while( 1 ){								// read while start ----------->
		/* ﾌｧｲﾙの読込(S-JIS)	*/
		if ( ReadKinq( rbuf, pfp ) != EOF ){
			/* ﾌﾗｸﾞ類ｸﾘｱ	*/
			stcCNT.cnt_irai++;	/* 入力件数     */
			G_line=stcCNT.cnt_irai;
			memset( G_utkymd,	'\0', sizeof( G_utkymd ));
			memset( G_irino,	'\0', sizeof( G_irino ));
			memset( G_kntno,	'\0', sizeof( G_kntno ));
			memset( G_kmkcd,	'\0', sizeof( G_kmkcd ));
			G_zssdino=0;

			// DEBUG
			strcpy( G_msg, "}" );
			LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
			sprintf( G_msg, "入力件数(%d) size(%d) ===============>{"
					, stcCNT.cnt_irai, strlen( rbuf ) );
			LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

			// レコードサイズチェック
			if( strlen( rbuf ) != ( KINQ_RECSIZE )){
				// ERROR
				stcCNT.cnt_irai_err++;
				sprintf( G_msg, "読み込みレコードサイズエラー[%d]", strlen( rbuf ));
				EditCsvMsg( G_msg );
				LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
				continue;
			}
			// 1件目はCOMMIT対象外
			if( stcCNT.cnt_irai == 1 ){
				ret=RTN_SKIP;
			}
		} else {
			memset( rbuf,	'\0', sizeof( rbuf ));
		}

//-----< 同一BML受日・依頼書NO,LOTNO が等しいものを
//                          1TRANSACTIONとするためKEYの比較を行う >------------
		   // 同一キーならばCOMMITしない
        if(( memcmp( key_uymd, &rbuf[KINQ_POS_UDATE],   8 ) != 0 ) /* 受付日付 */
        || ( memcmp( key_kntno,&rbuf[KINQ_POS_KENNO],   11 ) != 0 )/* 検体No */
        || ( memcmp( key_lot,  &rbuf[KINQ_POS_LOT], 2 ) != 0 ))    /* ロット */
		{
			// DEBUG
            sprintf( G_msg, "KEY-BREAK処理 [%8.8s][%11.11s][%2.2s]---------------",
					&rbuf[KINQ_POS_UDATE], &rbuf[KINQ_POS_KENNO], &rbuf[KINQ_POS_LOT] );
            LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// 1.04 ADD 自動発生処理　STA ===================================
			do {		/* Do-whileは１回のみ実行	　	*/
				jd_max=0;
				
				// エラーがある場合は行わない
				if( ret != RTN_OK ){
					break;
				}
				// INSERT件数が０の場合は抜ける
				if( wcnt_iri == 0 ){
					break;
				}
				// 自動発生項目の有無チェック
        		if(( jd_max=SelCountJkmkmst( irai.utkymd
											, irai.irino, irai.sriymd )) < 1 ){
					// 自動発生対象項目　存在せず
					break;
				}
				// 領域確保
				if(( pJir = ((struct JIDOIRAI *)malloc(
							sizeof(struct JIDOIRAI) * jd_max ))) == NULL ){
					sprintf( G_err, "%d", errno );
					sprintf( G_msg, "自動発生項目の領域確保に失敗しました。" );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm,
								__FILE__, __LINE__ );
					ret=RTN_NG;
					break;
				}
				// 自動発生項目領域の初期化
        		memset( pJir, '\0', sizeof( struct JIDOIRAI ) * jd_max );
				// 依頼構造体１件目に受日＋依頼書NOをセット
				strcpy( pJir[0].sIri.utkymd,		irai.utkymd );
				strcpy( pJir[0].sIri.irino,			irai.irino );
				strcpy( pJir[0].sIri.sriymd,		irai.sriymd );
				// 対象データ情報の取得
				if( SelJidoirai( pJir, jd_max ) !=  RTN_OK ){
					sprintf( G_err, "%d", errno );
					sprintf( G_msg, "自動発生項目のの読み込みに失敗しました。" );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm,
									__FILE__, __LINE__ );
					free( pJir );
					ret=RTN_NG;
					break;
				}
				for( i = 0; i < jd_max; i++ ){
					// EDIT
					strcpy( pJir[i].age,		kan.age );
					strcpy( pJir[i].agekbn,		kan.agekbn );
					if( EditJidoIrai( &(pJir[i]) ) != RTN_OK ){
						// ERROR
						strcpy( G_msg, "自動発生依頼情報編集時にエラーが発生しました。" );
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__);
						ret = RTN_NG;

						break;
					}
					memcpy( &irai, &pJir[i].sIri, sizeof( struct _IRAI ));

					// iniファイルでのDEBUG指定時のみprint処理を実行
					if( stcPRM.myp_debug == 1 ){
						 irai_pr( &irai );
					}

					/* INSERT */
					if( InsIrai( &irai ) != RTN_OK ){
						// ERROR
						strcpy( G_msg, "自動発生依頼情報登録時にエラーが発生しました。" );
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__);
						ret = RTN_NG;

						break;
					}
				}
				free( pJir );
				break;
			} while( 1 );
			// 1.04 ADD 自動発生処理　END ===================================

			/* エラー発生チェック	*/
			if( ret == RTN_OK ){
				if( Ydbcommit( ) != RTN_OK ){
						// ERROR
					strcpy( G_msg, "DB2のCOMMITに失敗しました。\n" );
					EditCsvMsg( G_msg );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__ );
					stcCNT.cnt_kanjya -= wcnt_kan;
					stcCNT.cnt_dbirai -= wcnt_iri;
				}
				stcCNT.cnt_kanjya += wcnt_kan;
				stcCNT.cnt_dbirai += wcnt_iri;
				wcnt_lot++;
			} else if ( ret == RTN_SKIP ){
			} else {
				// ERROR
				strcpy( G_msg, "データ処理でエラーが発生しました。" );
				EditCsvMsg( G_msg );
				LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__);

				// 1.04 DBエラー時異常終了させる
                nSQLErrorValue = atoi(G_err);

				if( Ydbrollback( ) != RTN_OK ){
						// ERROR
					strcpy( G_msg, "DB2のROLLBACKに失敗しました。"  );
					EditCsvMsg( G_msg );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__);
				}
				// 1.04 DBエラー時異常終了させる
                if((nSQLErrorValue< 0)&& (nSQLErrorValue != -911)&&(nSQLErrorValue !=-803))
                {
                    sprintf(G_msg, "##### DBエラー　発生　##### %d", nSQLErrorValue);
					EditCsvMsg( G_msg );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__);
                    *stopValue = 1;
                    return(RTN_NG);
                }
			}

			// INIT
			wcnt_kan = wcnt_iri = 0;

			// DEBUG
            strcpy( G_msg, "KEY-BREAK KNTNO 処理 END ---------------------->" );
            LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}

		// KEY LOT
		if(( memcmp( key_uymd, &rbuf[KINQ_POS_UDATE],   8 ) != 0 ) /* 受付日付 */
		|| ( memcmp( key_lot,  &rbuf[KINQ_POS_LOT], 2 ) != 0 ))    /* ロット */
		{
			// 緊急ロットNOの登録 (キーのLOTNOにて)
			if( wcnt_lot > 0 ){
				lotno = atoi( key_lot );
				KnkyulotIns_Ret = InsKnkyulot( stcPRM.myp_kjnymd, lotno );	/* 緊急LOT INSERT */
				if( KnkyulotIns_Ret != RTN_OK ){							/* INSERTに失敗した？ */
					// WARNING
					if( KnkyulotIns_Ret == MYAPP_RTN_DUP ){					/* 失敗理由が重複の場合 */
						sprintf( G_msg, 
							"登録済みの緊急LOTNOです。依頼追加が考えられます。"
							":受付年月日[%8.8s] ロットNO[%s]", key_uymd, key_lot );
						EditCsvMsg( G_msg );
						LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm,  __FILE__, __LINE__);
					}
					else{													/* 失敗理由が重複以外 */
						sprintf( G_msg, 
							"緊急ロットNOの登録に失敗しました。"
							":受付年月日[%8.8s] ロットNO[%s]", key_uymd, key_lot );
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm,  __FILE__, __LINE__);
					}
					nSQLErrorValue = atoi(G_err);							/* DBエラー時異常終了させる為、エラーコードセット */

					if( Ydbrollback( ) != RTN_OK ){
							// ERROR
						strcpy( G_msg, "DB2のROLLBACKに失敗しました。"  );
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
								__FILE__, __LINE__);
					}
					if((nSQLErrorValue< 0) && (nSQLErrorValue != -911) && (nSQLErrorValue !=-803)){
																			/* エラーコードチェック */
						sprintf(G_msg, "##### DBエラー　発生　##### %d", nSQLErrorValue);
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
								__FILE__, __LINE__);
						*stopValue = 1;
						return(RTN_NG);
					}
				} else {
					if( Ydbcommit( ) != RTN_OK ){
							// ERROR
						strcpy( G_msg, "緊急ロットNO DB2のCOMMITに失敗しました。" );
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
								__FILE__, __LINE__ );
					}
				}
			}
			// INIT 
			wcnt_lot = 0;
		}

		// EOF
        if( rbuf[0] == '\0' ){
            break;
        }

		// 日付チェック
		if( memcmp( key_uymd, &rbuf[KINQ_POS_UDATE], 8 ) != 0 ){ /* 受付日付 */
			// SKIP
			sprintf( G_msg, 
				"受付年月日[%.8s]が緊急依頼展開対象日[%s]と合致しません。"
				":LOTNO[%.2s]",
				&rbuf[KINQ_POS_UDATE],	key_uymd, &rbuf[KINQ_POS_LOT] );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, 
							__FILE__, __LINE__);

			// 3.01 ADD ERROR情報をLOTNO=0に設定
			if( UpdKnkyulot( MYAPP_DEF_ERR01 ) != RTN_OK ){
				// WARNING
				sprintf( G_msg, 
					"緊急ロットNOの更新に失敗しました。"
					":受付年月日[%8.8s] ロットNO=0", key_uymd );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, 
								__FILE__, __LINE__);

				// 1.04 DBエラー時異常終了させる
				nSQLErrorValue = atoi(G_err);

				if( Ydbrollback( ) != RTN_OK ){
						// ERROR
					strcpy( G_msg, "DB2のROLLBACKに失敗しました。"  );
					EditCsvMsg( G_msg );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__);
				}
				if((nSQLErrorValue< 0)&& (nSQLErrorValue != -911)&&(nSQLErrorValue !=-803))
				{
					sprintf(G_msg, "##### DBエラー　発生　##### %d", nSQLErrorValue);
					EditCsvMsg( G_msg );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
								__FILE__, __LINE__);
					*stopValue = 1;
					return(RTN_NG);
				}
			} else {
				if( Ydbcommit( ) != RTN_OK ){
					// ERROR
					strcpy( G_msg, "緊急ロットNO DB2のCOMMITに失敗しました。" );
					EditCsvMsg( G_msg );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__ );
				}
			}
			
			// 3.01 受付日が異なる場合はPGを終了する
			//		途中のデータはそのまま有効にする
			stcCNT.cnt_skip++;
			//continue;
			*stopValue = 1;
			return(RTN_SKIP);
		}

		// LOTNO CHECK
		if ( memcmp( key_lot,  &rbuf[KINQ_POS_LOT], 2 ) != 0 ) /* ロット */
		{
			// 処理済LOTNOチェック (読み込みデータのLOTNOにて)
			memset( w_str,	'\0',	sizeof( w_str ));
			memcpy( w_str,	&rbuf[KINQ_POS_LOT],	2 ); /* ロット */
			lotno = atoi( w_str );
			if( lotno == 0 ){
				// ERROR
				sprintf( G_msg, "緊急ロットNO が正しくありません。 "
					" 検体No[%11.11s] 緊急ロットNO[%2.2s]"
					,&rbuf[KINQ_POS_KENNO], &rbuf[KINQ_POS_LOT] );
				EditCsvMsg( G_msg );
				LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
						__FILE__, __LINE__ );
				// 3.01 受付日が異なる場合はPGを終了する
				//		途中のデータはそのまま有効にする
				stcCNT.cnt_skip++;
				*stopValue = 1;
				return(RTN_SKIP);
			}
				// 該当レコード件数を戻す
/*			if( GetKnkyulot( stcPRM.myp_kjnymd, lotno ) > 0 ){
				// 緊急ロット情報登録済み -> SKIP
				stcCNT.cnt_sumi++;
				continue;
			}*/
		}

		// KEY SET
		memcpy( key_lot,	&rbuf[KINQ_POS_LOT],	2 );  /* ロット */
		memcpy( key_uymd,	&rbuf[KINQ_POS_UDATE],	8 );  /* 受付日付 */
		memcpy( key_kntno,  &rbuf[KINQ_POS_KENNO],  11 ); /* 検体No */

		/* --------------------------------	*/
		/*	処理 							*/
		/* --------------------------------	*/
		// DEBUG
		sprintf( G_msg, "処理 uymd[%s] kntno[%s] lot[%.2s]"
				, key_uymd, key_kntno, key_lot );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

		ret = RTN_OK;
		memcpy( &kinq,	rbuf, sizeof( struct AS4IRAI ) );
		do {		/* Do-whileは１回のみ実行	　	*/
			// 患者属性編集
			memset( &kan,	0x00, sizeof( struct _KANJYA ));
			if(( ret= EditKinqKanjya( &kinq, &kan )) != RTN_OK ){
				/* ｴﾗｰ*/
				ret = RTN_SKIP;
				// do-while
				break;
			}

			// 依頼情報 
			if(( kom =  ( struct KOMST *)malloc( 
					sizeof( struct KOMST ) * kmax )) == NULL ){
				sprintf( G_err, "%d", errno );
				strcpy( G_msg, "緊急対応項目情報の領域確保に失敗しました。" );
				EditCsvMsg( G_msg );
				LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
									__FILE__, __LINE__);
				ret = RTN_NG;
				// do-while
				break;
			}
			memset( kom,	'\0',	sizeof( struct KOMST ) * kmax );
			memset( &irai,	'\0',	sizeof( struct _IRAI ));

			EditKinqIrai( &kinq, &kan, &irai );

			for( i = j = 0; i < kmax; i++ ){
				// 項目コードがスペースならば抜ける
				if( memcmp( kinq.ikm[i].c_koumoku_cd, MYAPP_SPACE10, 
					sizeof( kinq.ikm[i].c_koumoku_cd )) == 0 ){
					// for
					break;
				}
				// ラボフラグによる対象判断
				if( kinq.ikm[i].c_labo_flg[0] != '1' ){
					// for
					continue;
				}
				// マスタによる対象判断、マスタ情報取得
					// 0->0
				sprintf( kom[j].kmkcd, "%-7.7s", kinq.ikm[i].c_koumoku_cd );

				// 3.01 緊急対応項目(SMPCD取得)→項目マスタ→検査Gマスタ取得まで
				//      存在しない場合はSKIPする
				if( EditKinqIraiKomoku( &(kom[j]), irai.stsrcd, kan.age, irai.skflg ) 
									== RTN_SKIP ){
					// for
					continue;
				}
				j++;
			}
			// 該当依頼が無い場合は患者属性も登録しない
			if( j == 0 ){
				stcCNT.cnt_exc++;
				sprintf( G_msg, "当ラボ対象の依頼項目がありません。:KNTNO[%s]", 
						key_kntno );
				EditCsvMsg( G_msg );
				LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, 
									__FILE__, __LINE__);
				if( wcnt_kan > 0 || wcnt_iri > 0 ){
					// 同一KEYでKANJYA INSERT OK
					ret = RTN_OK;
				} else {
					ret = RTN_SKIP;
				}
				// do-while
				break;
			}
//-----< 登録 >----------------------------------------------------------------
			/* KANJYA INSERT */
				/* 同一キーで1レコード目のみ対象	 */
			if( wcnt_kan == 0 ){
				KanjyaIns_Ret = InsKanjya( &kan );			/* 患者テーブルのINSERT */
				if( KanjyaIns_Ret != RTN_OK ){				/* 患者情報INSERTに失敗？ */
					if( KanjyaIns_Ret != MYAPP_RTN_DUP ){	/* 失敗理由が重複エラーではない場合 */
						/* ERROR LOG */
						strcpy( G_msg, "患者情報登録時にエラーが発生しました。" );
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__);
						ret = RTN_NG;
						// do-while
						break;								/* 重複エラー以外は処理を終了 */
					}
					else{									/* 重複エラーの場合 */
						/* WARNING LOG */
						sprintf( G_msg,
								"登録済みの患者です。依頼追加が考えられます。"
								":受付年月日[%s] 依頼書NO[%s]",
								kan.utkymd, kan.irino );
						EditCsvMsg( G_msg );
						LogOut( LT_WRN, LX_INS, G_err, G_msg, func_nm,  __FILE__, __LINE__);
							;								/* 重複エラーの場合は何もしないでワーニングLOGを吐く*/
															/* 過去LOT分の依頼追加対応 */
					}
				}
				else{										/* INSERTが正常に終了した場合 */
					ret = RTN_OK;
					wcnt_kan++;
				}
			}

			/* IRAI INSERT */
			for( i = 0; i < j; i++ ){
				strcpy( irai.knsgrp,	kom[i].knsgrp );
				strcpy( irai.kmkcd,		kom[i].kmkcd );
				strcpy( irai.kmkrs,		kom[i].kmkrs );
				strcpy( irai.oyakmkcd,	kom[i].oyakmkcd );
				strcpy( irai.bkfkkbn,	kom[i].fkbnkkb );
				strcpy( irai.seccd,		kom[i].seccd );
				strcpy( irai.smpcd,		kom[i].smpcd );
				strcpy( irai.kjno,		kom[i].kjno );

				// iniファイルでのDEBUG指定時のみprint処理を実行
				if( stcPRM.myp_debug == 1 ){
					 irai_pr( &irai );
				}

				IraiIns_Ret = InsIrai( &irai ); /* 依頼テーブルのINSERT */
				if( IraiIns_Ret != RTN_OK ){    /* INSERTに失敗した？*/
					/* ｴﾗｰ*/
/*** 過去LOT分の依頼追加対応 ***/
					if ( IraiIns_Ret == MYAPP_RTN_DUP ){/* 失敗理由が重複エラーの場合 */
						/* WARNING LOG */
						sprintf( G_msg, 
							"登録済みの項目です。依頼追加が考えられます。"
							":受付年月日[%s] 依頼書NO[%s] 項目コード[%s]",
							irai.utkymd, irai.irino, irai.kmkcd );
						EditCsvMsg( G_msg );
						LogOut( LT_WRN, LX_INS, G_err, G_msg, func_nm,  __FILE__, __LINE__);
							;								/* 重複エラーの場合は何もしないでワーニングLOGを吐く*/
															/* 過去LOT分の依頼追加対応 */

						continue;
					}
					else{		/* 重複エラー以外の場合はマズイので、止める */
						ret = RTN_NG;
						break;
					}
				}
				wcnt_iri++;	
			}
			// 必ず
			break;
		} while( wcnt_kan < 1 );
		if( kom != NULL ){
			free( kom );
		}
	}	// <---------------------------------------------------read while end

//-----< 1FILE READ END >-------------------------------------------------------
	// DEBUG
	sprintf( G_msg, "最終入力件数(%d)kan[%d]dbirai[%d]", 
		stcCNT.cnt_irai ,stcCNT.cnt_kanjya ,stcCNT.cnt_dbirai );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	memset( G_utkymd,	'\0', sizeof( G_utkymd ));
	memset( G_irino,	'\0', sizeof( G_irino ));
	memset( G_kntno,	'\0', sizeof( G_kntno ));
	memset( G_kmkcd,	'\0', sizeof( G_kmkcd ));
	G_line=0;

	// TRACE
    sprintf( G_msg, "緊急  患者情報・依頼情報登録処理が終了しました" );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "        全依頼件数                  ：%10d件"
														,stcCNT.cnt_irai );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            日付対象外依頼件数(SKIP)：%10d件"
														,stcCNT.cnt_skip );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            項目対象外依頼件数(SKIP)：%10d件"
														,stcCNT.cnt_exc );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            処理済依頼件数(SKIP)    ：%10d件"
														,stcCNT.cnt_sumi );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            エラー依頼件数(SKIP)    ：%10d件"
														,stcCNT.cnt_irai_err );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            患者属性登録件数        ：%10dﾚｺｰﾄﾞ"
														,stcCNT.cnt_kanjya );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
    sprintf( G_msg, "            依頼情報登録件数        ：%10dﾚｺｰﾄﾞ"
														,stcCNT.cnt_dbirai );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	if( stcCNT.cnt_skip == 0 ){
		ret = RTN_OK;
	} else {
		ret = RTN_SKIP;
	}
	return( ret );
}

/******************************************************************************/
/*  関 数 名  ：ReadKinq                                                      */
/*  機能概要  ：緊急依頼ファイル読み込み                                      */
/*  入    力  ：                                                              */
/*   第１引数 ： char	file_nm[]	: 入力ファイルポインタ                    */
/*  出    力  ： char	rbuf[];		: 読み込みバッファ                        */
/*  復帰情報  ： 0以上				: 正常終了(読込サイズ)                    */
/*               EOF				: FILE END                                */
/*               以外				: 失敗                                    */
/******************************************************************************/
int     ReadKinq( rbuf, pfp )
char		rbuf[];				/* ﾚｺｰﾄﾞ読み込みﾊﾞｯﾌｧ */
FILE		*pfp;				/* ﾌｧｲﾙ識別子 */
{
 	char    func_nm[MYAPP_LEN_FNCNM+1];	/* 関数名称     */

 	/* 初期処理     */
 	strcpy( func_nm, "ReadKinq" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	memset( rbuf, 0x00, sizeof( rbuf ));
	if( fgets( rbuf, KINQ_RECSIZE + 1, pfp ) == NULL ){
		/* ﾃﾞｰﾀなし	*/
		return( EOF );
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( strlen( rbuf ) );
}

/******************************************************************************/
/*  関 数 名  ：Log_out                                                       */
/*  機能概要  ：ログファイル出力                                    */
/*  入    力  ：                                                              */
/*   第１引数 ： char	file_nm[]	: 入力ファイルポインタ                    */
/*  出    力  ： char	rbuf[];		: 読み込みバッファ                        */
/*  復帰情報  ： 0以上				: 正常終了(読込サイズ)                    */
/*               EOF				: FILE END                                */
/*               以外				: 失敗                                    */
/******************************************************************************/
int		LogOut( sbt, flg, ecd, msg, fncnm, file, line )
char		sbt[];	
char		flg[];	
char		ecd[];	
char		msg[];	
char		fncnm[] ;
char		file[] ;
long    	line ;
{
		int		ret=RTN_OK;
static	int		init_flg = 0;           /* ｲﾆｼｬﾙﾌﾗｸﾞ    */
static	struct	stcLogMember	gstLogMem ; //  ログ出力情報

//------ 1 ----------------------------------------------------------
	if( init_flg == 0 ){
		//  ログ情報初期設定	
		memset ( &gstLogMem, '\0', sizeof ( gstLogMem ) ) ;
		strcpy ( gstLogMem.pcAppName,	stcPRM.myp_exefile ) ;
		strcpy ( gstLogMem.pcLoginId,	"DAEMON" ) ;
		init_flg = 1;
	}
//------ 1 ----------------------------------------------------------
	// トレース種別
	gstLogMem.eTrcKind=sbt[0];
	// 実行フラグ
	strcpy ( gstLogMem.pcExeFlg,	flg ) ;
	// エラーコード
	strcpy ( gstLogMem.pcErrCode,	ecd ) ;
	// メッセージ
	strcpy ( gstLogMem.pcMsg,		msg );
	// 関数名
	strcpy ( gstLogMem.pcFncName,	fncnm ) ;

	if(( strcmp( sbt, LT_STA )) == 0 ){
		gstLogMem.eTrcKind='T';
		strcpy( gstLogMem.pcMsg, "start" );
	} else if( strcmp( sbt, LT_END ) == 0 ){
		gstLogMem.eTrcKind='T';
		strcpy( gstLogMem.pcMsg, "end " );
	}

	// LOGOUT
	ret = _ZbmlPutLog( &gstLogMem,	file, line );

	// inifile debug DEBUG
	if( stcPRM.myp_debug == 1 ){
		if( strcmp( ecd, LE_NON ) == 0 ){
			printf( "[%.1s][%s]%s\n"
				,sbt,gstLogMem.pcFncName, gstLogMem.pcMsg );
		} else {
			printf( "[%.1s][%s][%s]%s\n"
				,sbt,gstLogMem.pcFncName,gstLogMem.pcErrCode,gstLogMem.pcMsg);
		}
	}

	return( RTN_OK );
}
/** End of File ***************************************************************/
