/******************************************************************************/
/*   ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/*   システム名：次世代システム                                               */
/*   ファイル名：AD103.c                                                      */
/*   概      要：検査受付（依頼展開）患者情報・治験拡張登録                   */
/*	 OS        ：SUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   言語      ：DB2/C                                                        */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/08     INTEC.INC      CREATE                             */
/*  1.01     2006/05/01     INTEC.INC      SJIS,項目追加対応                  */
/*  1.02     2006/05/03     INTEC.INC      UPDATE 引数としてINIファイル指定   */
/*  1.03     2006/06/10     INTEC.INC      患者属性修正時依頼情報世代No更新   */
/*  1.04     2006/12/12     INTEC.INC      DBエラー時異常終了させる           */
/*  1.05     2009/06/29     Merits K.Ameno 障害管理No:0904031814/0904031719対応*/
/*                                         属性世代No展開不具合修正           */
/******************************************************************************/

/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "bmllog.h"
#include "AD103.h"

/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/
iconv_t		G_ic;						// with iconv
char		G_fnm[256];					// InputFileName
char		G_err[MYAPP_LEN_ERR+1];		// LogMessage(errcode)
char		G_msg[MYAPP_LEN_MSG+1];		// LogMessage
char		G_utkymd[10+1];				// LogMessage(csv)
char		G_irino[13+1];				// LogMessage(csv)
int			G_zssdino;					// LogMessage(csv)
int			G_line;						// InputFileLineNo

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
	G_zssdino=0;
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
			sprintf( G_msg, "依頼ファイルの情報取得(scandir)に失敗しました。" );
			EditCsvMsg( G_msg );
			LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			ret=1;
			break;
		} 

		for( i=0; i < inp_cnt; i++ ){	// <------------------ファイルの件数分
			//------------------
			// 	基準日取得
			//------------------
			if( GetKjnymd( ) != RTN_OK ){
				sprintf( G_msg, "基準処理年月日の取得に失敗しました。" );
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
				// INI FILE GENERATION PARAM での処理判断
			if( strcmp( stcPRM.myp_gene, "PNC" ) == 0 ){

                //2006.12.08 Kim Jinsuk エラー時異常終了させる
				//ret = PncProc( fp );
				ret = PncProc( fp , &li_stopFlg);
				//2006.12.08 Kim Jinsuk　エラー時異常終了させる

			} else {
				ret = NxtProc( fp );
			}
			if( ret == RTN_NG ){
				//printf("#### li_stopFlg %d", li_stopFlg);
				sprintf( G_msg, "[%s]処理中にエラーが発生しました。"
					,w_infilenm );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm
						, __FILE__, __LINE__ );

                //==> 2006.12.08 Kim Jinsuk DBエラー時異常終了させる
                if(li_stopFlg == 1)
				{
					sprintf(G_msg, "[[DB ERROR]]");
 					//printf("li_stopFlg %d", li_stopFlg);
                    LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm
                        , __FILE__, __LINE__ );
					fclose( fp );
					break;
				}
                //<== 2006.12.08 Kim Jinsuk DBエラー時異常終了させる				
			}

			//------------------
			// INPUT FILE CLOSE
			//------------------
			fclose( fp );

			//---------------------------
			// 処理済ファイルの名称変更
			//---------------------------
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
			sprintf( G_msg, "処理済依頼ファイル[%s]の名前を[%s]に変更しました。"
					, w_infilenm, w_endfilenm );
			LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

			//------------------
			// 終了判断
			//------------------
				// 共有メモリ取得

			//==> 2006.12.08 Kim Jinsuk DBエラー時異常終了させる
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
			//<== 2006.12.08 Kim Jinsuk DBエラー時異常終了させる
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

		//==> 2006.12.08 Kim Jinsuk DBエラー時異常終了させる
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
		//<== 2006.12.08 Kim Jinsuk DBエラー時異常終了させる
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
fprintf(stderr,"説明:患者情報登録処理\n" );
fprintf(stderr,"    :検査受付（依頼展開）患者情報・治験拡張データを登録します\n" );
fprintf(stderr,"     依頼属性取得ディレクトリ[%s]\n", stcPRM.ifp_indir );
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
	char    *p_fini;                    /* 1.02 INI FILE 名称    */
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
	sprintf( stcPRM.lgp_flog, "%s.log", stcPRM.myp_exefile );
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
    cp = GetIniFile( "MYAPP.PARA", "MYAPP_GENE", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", &stcPRM.myp_gene );
    }
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
	sprintf( G_msg, "app_gene   [%s]",  stcPRM.myp_gene );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "G_zairyo  [%s]",	stcPRM.myp_zairyo );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  関 数 名  ：GetKjnymd                                                     */
/*  機能概要  ：基準日取得                                                    */
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
	struct	{
		int	yyyy;
		int	mm;
		int	dd;
	} BmlDate;

	/* 初期設定	*/
	strcpy( func_nm,	"GetKjnymd" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	// 基準処理日の取得
	memset( &knr,	'\0',	sizeof( struct _SYSKNRMST ) );
	if(( ret = SelSysknrmst( &knr )) == RTN_OK ){
		if( knr.iriendflg[0] == '0' ){ 	// 0:受信前 1:受信後
			strcpy( stcPRM.myp_kjnymd,	knr.kjnsriymd );

			sprintf( G_msg, "基準処理日[%s]を基準日とします。"
				, stcPRM.myp_kjnymd );
		} else {

			// 依頼ENDフラグ受信済みで 次依頼処理年月日が初期値以外
		 	if( strcmp( knr.nxirisriymd, INIT_DATE ) == 0 ){
				strcpy( stcPRM.myp_kjnymd,	knr.kjnsriymd );

				sprintf( G_msg,
					"依頼END受信済ですが次依頼処理年月日が初期値のため、"
					"基準処理日[%s]を基準日とします。"
					, stcPRM.myp_kjnymd );
			} else {
				strcpy( stcPRM.myp_kjnymd,	knr.nxirisriymd );

				sprintf( G_msg, 
					"依頼END受信済のため次依頼処理年月日[%s]を基準日とします。"
					, stcPRM.myp_kjnymd );
			}
		}
		// TRACE
		LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

	} else {
		ZbmlDateGetToday( &BmlDate );
		sprintf( stcPRM.myp_kjnymd, "%04d-%02d-%02d",
			BmlDate.yyyy, BmlDate.mm, BmlDate.dd );
		// WARNING
		sprintf( G_msg, 
			"基準処理日取得に失敗したため基準日をシステム日付[%s]とします。"
			, stcPRM.myp_kjnymd );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	}
	
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
/*  関 数 名  ：PncProc                                                       */
/*  機能概要  ：ＰＮＣ依頼ファイル処理                                        */
/*  入    力  ：                                                              */
/*   第１引数 ： FILE	pfp	: 入力ファイル識別子                              */
//   第2 引数 :  int    stopValue : 終了識別子　　　　　  　　　　　　　　　　*/　
/*  出    力  ： なし                                                         */
/*  復帰情報  ： INT                                                          */
/*               RTN_OK     : 成功                                            */
/*               RTN_NG     : 失敗                                            */
/******************************************************************************/
//==> 2006.12.08 Kim Jinsuk
//int       PncProc( pfp )
int     PncProc( pfp , stopValue)
//<== 2006.12.08 Kim Jinsuk
FILE    	*pfp;
int         *stopValue;
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称		*/
	int		ret;							/* 関数戻り値	*/

	/* 依頼受信PNC format(S-JIS) */
	struct	Z01SJTR			z01sjitr;	/* PNC受信トレーラー(S-JIS) */
	struct	Z02SJIR1		z02sjir1;	/* PNC受信属性(S-JIS) */
	struct	Z04SJIR2		z04sjir2;	/* PNC受信治験(S-JIS) */

	struct	_KANJYA			kan;		/* 患者情報	*/
	struct	_CHIKENZOK		try;		/* 治験拡張属性	*/
	struct	CNT				stcCNT;		/* 件数情報		*/

	char	rbuf[PNC_RECSIZE*2+1];		/* 読み込みｴﾘｱ		*/
	char	w_key[MYAPP_LEN_KEY+1];
	int		w_key_r2=0;
	char	w_str[200];
	int		wcnt_kan=0;					/* 患者情報登録件数*/
	int		wcnt_try=0;					/* 治験拡張属性登録件数	*/
	int		w_cnt;
	int		i,j;						/* index		*/

    //2006.12.08 Kim Jinsuk DBエラー時
	int     nSQLErrorValue;

	/* 初期設定	*/
	strcpy( func_nm,	"PncProc" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ｸﾘｱ	*/
	ret = RTN_OK;

	stcCNT.cnt_irai	= stcCNT.cnt_irai_err = stcCNT.cnt_irai_del = 0;
	stcCNT.cnt_hd = stcCNT.cnt_tr = stcCNT.cnt_r1 = stcCNT.cnt_r2 = 0;
	stcCNT.cnt_kanjya = stcCNT.cnt_chiken = 0;
	memset( w_key, '\0', sizeof( w_key ));

	sprintf( G_msg,	"受付（依頼展開） 患者情報・治験拡張属性テーブル"
					"作成開始 : 依頼属性ファイル名[%s]", G_fnm );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	// DEBUG
	sprintf( G_msg, "INFILE[%s] START!!----->", G_fnm );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	/* ﾌｧｲﾙの読込(S-JIS)とﾚｺｰﾄﾞ識別子の判定	*/
	while( ReadPnc( rbuf, pfp ) != EOF ){	// read while start ----------->
		/* ﾌﾗｸﾞ類ｸﾘｱ	*/
		stcCNT.cnt_irai++;	/* 入力件数     */
		G_line=stcCNT.cnt_irai;
		memset( G_utkymd,	'\0', sizeof( G_utkymd ));
		memset( G_irino,	'\0', sizeof( G_irino ));
		G_zssdino=0;

		// DEBUG
		strcpy( G_msg, "}" );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
		sprintf( G_msg, "入力件数(%d) size(%d) sbt[%.2s] ===============>{"
				, stcCNT.cnt_irai, strlen( rbuf ), rbuf );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

		/* --------------------------------	*/
		/*	PNC ファイル読み込みチェック	*/
		/* --------------------------------	*/
		// レコードサイズチェック
		if( strlen( rbuf ) != ( PNC_RECSIZE )){
			// ERROR
			stcCNT.cnt_irai_err++;
			sprintf( G_msg, "読み込みレコードサイズエラー[%d]", strlen( rbuf ));
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			continue;
		}
		// ヘッダー
		if( strncmp( rbuf, "HD", 2 ) == 0 ){
			stcCNT.cnt_hd++;
			// １件目はヘッダー	
			if( stcCNT.cnt_irai != 1 ){
				// ERROR
				sprintf( G_msg, "１件目がヘッダーではありません。[%.2s]", rbuf);
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, 
								__FILE__, __LINE__);
			}
			// DEBUG
			strcpy( G_msg, "ヘッダー情報 SKIP" );
			LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

			continue;
		} else
		// トレーラー レコード数チェック
		if( strncmp( rbuf, "TR", 2 ) == 0 ){
			stcCNT.cnt_tr++;
			memcpy( &z01sjitr, rbuf, sizeof( struct Z01SJTR ) );
			if( memcmp( z01sjitr.c_reccnt, MYAPP_SPACE10, 8 ) == 0 ){
				// ERROR
				sprintf( G_msg, "トレーラーの物理レコード数が未設定です。"
						"[%.8s]", z01sjitr.c_reccnt );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, 
								__FILE__, __LINE__);
				continue;
			}
			// 物理件数チェック
			memset( w_str, '\0', sizeof( w_str ));
			w_cnt = atol( strncpy( w_str, z01sjitr.c_reccnt, 8 ));
			if( stcCNT.cnt_irai != w_cnt ){
				// ERROR
				sprintf( G_msg, "トレーラーの物理レコード数と一致しません。"
						"TR   [%d]->[%d]", w_cnt, stcCNT.cnt_irai );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, 
								__FILE__, __LINE__);
			}
			// 論理件数チェック
			memset( w_str, '\0', sizeof( w_str ));
			w_cnt = atol( strncpy( w_str, z01sjitr.c_reccnt01, 8 ));
			if( stcCNT.cnt_r1 != w_cnt ){
				// ERROR
				sprintf( G_msg, "トレーラーの論理レコード数と一致しません。"
						"TR-R1[%d]->[%d]", w_cnt, stcCNT.cnt_r1 );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, 
								__FILE__, __LINE__);
			}
			memset( w_str, '\0', sizeof( w_str ));
			w_cnt = atol( strncpy( w_str, z01sjitr.c_reccnt02, 8 ));
			if( stcCNT.cnt_r2 != w_cnt ){
				// ERROR
				sprintf( G_msg, "トレーラーの論理レコード数と一致しません。"
						"TR-R2[%d]->[%d]", w_cnt, stcCNT.cnt_r2 );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, 
								__FILE__, __LINE__);
			}
			// DEBUG
			sprintf( G_msg, "トレーラー情報 SKIP" );
			LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

			// トレーラーは強制的に KEY-BREAK
			memset( w_key, '9', MYAPP_LEN_KEY );
		}

		// トレーラー後のレコード存在はエラー
		if(( stcCNT.cnt_tr == 1 )&&( strncmp( rbuf, "TR", 2 ) != 0 )){
			// ERROR
			sprintf( G_msg, "トレーラー後にレコードが含まれています。[%.2s]"
					,rbuf );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}

		// 1件目はKEY-BREAKさせない
		if( stcCNT.cnt_irai == 2 ){
			memcpy( w_key, &rbuf[2], MYAPP_LEN_KEY );
		}
		// R2の次にR1を読み込んだ場合は 強制的にKEY-BREAK
		if( w_key_r2 != 0 ){
			memset( w_key, '9', MYAPP_LEN_KEY );
		}
		/* --------------------------------	*/
		/*	処理 							*/
		/* --------------------------------	*/
		// DEBUG
		sprintf( G_msg, "処理 sbt[%.2s]in[%.19s] key[%s]"
				, rbuf, &rbuf[2], w_key );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

//-----< R1,R2で1TRANSACTIONとするためKEYの比較を行う >------------------
		if( memcmp( w_key, &rbuf[2], MYAPP_LEN_KEY ) != 0 ){
			// DEBUG
			sprintf( G_msg, "KEY-BREAK処理 : ret[%d]kan[%d]try[%d]", 
					ret, wcnt_kan, wcnt_try );
			LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

			/* エラー発生チェック	*/
			if( ret == RTN_OK ){
				if(( ret = Ydbcommit( )) != RTN_OK ){
						// ERROR
					strcpy( G_msg, "DB2のCOMMITに失敗しました。\n" );
					EditCsvMsg( G_msg );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__ );
					stcCNT.cnt_kanjya -= wcnt_kan;
					stcCNT.cnt_chiken -= wcnt_try;
				}
				stcCNT.cnt_kanjya += wcnt_kan;
				stcCNT.cnt_chiken += wcnt_try;
			} else {
				// ERROR
				strcpy( G_msg, "データ処理でエラーが発生しました。" );
				EditCsvMsg( G_msg );
				LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__);

		        //2006.12.08 Kim Jinsuk DBエラー時異常終了させる
        		nSQLErrorValue = atoi(G_err);

				if(( ret = Ydbrollback( )) != RTN_OK ){
						// ERROR
					strcpy( G_msg, "DB2のROLLBACKに失敗しました。\n"  );
					EditCsvMsg( G_msg );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm,__FILE__, __LINE__);
				}

        		//==> 2006.12.08 Kim Jinsuk DBエラー時異常終了させる
        		if((nSQLErrorValue< 0)&& (nSQLErrorValue != -911)&&(nSQLErrorValue !=-803))
        		{
            		*stopValue = 1;
            		sprintf(G_msg, "##### DBエラー　発生　##### %d", nSQLErrorValue);

            		//printf("nSQLErrorValue %d stopValue %d \n",nSQLErrorValue, stopValue);
            		return(RTN_NG);
        		}
        		//<== 2006.12.08 Kim Jinsuk DBエラー時異常終了させる

			}
			// commit 処理
			wcnt_kan = wcnt_try = 0;
			memcpy( w_key, &rbuf[2], MYAPP_LEN_KEY );
			w_key_r2=0;
		}
//-----< R1 >---------------------------------------------------------------
		ret = RTN_OK;
		if( strncmp( rbuf, "R1", 2 ) == 0 ){	// 患者属性
			stcCNT.cnt_r1++;
			memcpy( &z02sjir1,	rbuf, sizeof( struct Z02SJIR1 ) );
			memset( &kan,		0x00, sizeof( struct _KANJYA ));
			do {		/* Do-whileは１回のみ実行	　	*/
				/* 編集 */
				if(( ret= EditPncKanjya( &z02sjir1, &kan )) != RTN_OK ){
					if( ret == RTN_SKIP ){
						// 削除依頼受信
						stcCNT.cnt_irai_del++;
						ret = RTN_OK;
						break;
					} else {
						/* ｴﾗｰ*/
						ret = RTN_NG;
						break;
					}
				}
				/* 共通箇所の編集 */
				if( EditCommonKanjya( &kan ) != RTN_OK ){
					/* ｴﾗｰ*/
					ret = RTN_NG;
					strcpy( G_msg, "EditCommonKanjya ==== \n"  );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm,__FILE__, __LINE__);
					break;
				}

/*  1.05     2009/06/29     Merits K.Ameno 障害管理No:0904031814/0904031719対応 -->*/
			/*** 					<<<<<<<NOTE>>>>>>>						  ***/
			/*** 属性修正FLGが立っている場合、既存情報を別テーブルへ退避して  ***/
			/*** Insertする。その時の属性世代Noは固定。当日分なら0            ***/
			/*** 翌日持越し分なら100                                          ***/
			/*** することはせず、既存のレコードを更新する。その際、属性世代No ***/
			/*** 最新のものでUpdateする                                       ***/
				if( kan.zssflg[0] == '1' ){			/* 属性修正FLGが立っている場合 */
				/* 属性修正　自動計算起動の導入に伴い、属性修正情報は取り込まないように変更  */
					ret = RTN_OK;
					break;
					
//					ret = SelKanjya( &kan);			/* 当日テーブルから同患者属性情報を取得 */
//					if ( ret == RTN_OK ){			/* 属性情報が取れた！(既に存在した) */
//				/*** 既存情報の退避処理 ***/
//						ret = InsShusei_Kanjya();	/* 属性修正テーブルへ取ってきた情報をInsert */
//						if( ret != RTN_OK ){		/* Insertに失敗した */
//							ret = RTN_NG;			/* 実行結果をNGにする */
//							break;					/* 処理終了 */
//						}
//				/*** 既存情報の削除処理 ***/
//						ret = DelKanjya( &kan );	/* 患者テーブルから既存情報を削除 */
//						if( ret != RTN_OK ){		/* Deleteに失敗した */
//							ret = RTN_NG;			/* 実行結果をNGにする */
//							break;					/* 処理終了 */
//						}
//					}
//					else if( ret == RTN_DBERR ){	/* DBエラーだった場合 */
//						ret = RTN_NG;				/* 実行結果をNGにする */
//						break;						/* 処理終了 */
//					}
//					/*** 当日テーブルからDBエラーを起こしていないのに取れない ***/
//					/*** 翌日持越し確定なので、そのまま展開する。世代Noは100  ***/
				}									/* 通常の属性展開 And 重複時退避処理完了 */
				ret = InsKanjya( &kan );			/* 患者属性へInsertする */

				if( ret != RTN_OK ){				/* 患者属性情報更新が失敗していたら */
/*  1.05     2009/06/29     Merits K.Ameno 障害管理No:0904031814/0904031719対応 <--*/
					/* INSERT */
// 				if(( ret = InsKanjya( &kan )) != RTN_OK ){
					if( ret != MYAPP_RTN_DUP ){
						// ERROR
						strcpy( G_msg,
							"患者情報登録時にエラーが発生しました。" );
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_INS, G_err, G_msg, func_nm, 
										__FILE__, __LINE__);
						ret = RTN_NG;
						break;
					}
					// AS/400からの後日依頼はUPDATE
						// AS/400からの後日依頼か?
					if( SelKinkyuIrai( &kan ) <= 0 ){
						// 緊急項目が存在しない＝データ重複
						strcpy( G_msg, "既に患者情報が存在します。" );
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, 
									__FILE__, __LINE__);
						ret = RTN_NG;
						break;
					}
						//	属性世代Noの最大値取得
					if( SelKanjyaZssdinoMax( &kan ) != RTN_OK ){
						// ERROR
						strcpy( G_msg, 
							"AS/400後日依頼の患者情報更新対象取得に"
							"失敗しました。" );
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, 
									__FILE__, __LINE__);
						ret = RTN_NG;
						break;
					}
					if( UpdKinkyuKanjya( &kan ) != RTN_OK ){
						// ERROR -> LOG OUT は.sqcにて
						//strcpy( G_msg,
						//	"AS/400後日依頼の患者情報更新に失敗しました。" );
						//EditCsvMsg( G_msg );
						//LogOut( LT_ERR, LX_INS, G_err, G_msg, func_nm, 
						//				__FILE__, __LINE__);
						ret = RTN_NG;
						break;
					} 
					ret = RTN_OK;
				}
//				/* 1.03 属性修正時は依頼情報.世代Noも更新する */
//				if( kan.zssflg[0] == '1' ){
//					if( UpdIraiZssdino( &kan ) != RTN_OK ){
//						// ERROR
//						strcpy( G_msg, 
//							"患者情報更新対象の依頼情報世代No更新に"
//							"失敗しました。" );
//						EditCsvMsg( G_msg );
//						LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, 
//									__FILE__, __LINE__);
//						ret = RTN_NG;
//						break;
//					}
//				} 
				wcnt_kan++;
			} while( wcnt_kan < 1 );
//-----< R2 >---------------------------------------------------------------
		} else if( strncmp( rbuf, "R2", 2 ) == 0 ){ // 治験拡張
			stcCNT.cnt_r2++;
			w_key_r2++;
			memcpy( &z04sjir2, rbuf, sizeof( struct Z04SJIR2 ) );
			memset( &try,   0x00, sizeof( struct _CHIKENZOK ));
			do {		/* Do-whileは１回のみ実行   　  */
				/* 編集 */
				if( EditPncChikenzok( &z04sjir2, &try ) != RTN_OK ){
					/* ｴﾗｰ*/
					ret = RTN_NG;
					break;
				}
				// 患者属性の世代NOを引き継ぐ
				try.zssdino = kan.zssdino;
				/* 共通箇所の編集 */
				if( EditCommonChikenzok( &try ) != RTN_OK ){
					/* ｴﾗｰ*/
					ret = RTN_NG;
					break;
				}
				// R1無しでR2のみはエラー
				if( wcnt_kan == 0 ){
					// error
					ret = RTN_NG;
					break;
				}
				// Kanjya.tktyflg UPDATE
				if( UpdKanjyaTktyflg( &kan ) != RTN_OK ){
					/* ｴﾗｰ*/
					ret = RTN_NG;
					break;
				}
				/* INSERT */
				if( InsChikenzok( &try ) != RTN_OK ){
					/* ｴﾗｰ*/
					ret = RTN_NG;
					break;
				}
				wcnt_try++;
			} while( wcnt_try < 1 );
		}
		if( ret != RTN_OK ){
			// ERROR
			stcCNT.cnt_irai_err++ ;	 /* error */
		}
	}   // <---------------------------------------------------read while end

//-----< 1FILE READ END >-------------------------------------------------------
	// トレーラー無しはエラー
	if( stcCNT.cnt_tr == 0 ){
		// error msg
		// ERROR
		strcpy( G_msg, "トレーラーがありません。" );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
	}
	// トレーラー無しでCOMMITが必要な場合の考慮
		/* エラー発生チェック	*/
	if( ret == RTN_OK ){
		if(( wcnt_kan != 0 ) || ( wcnt_try != 0 )){
        	if(( ret = Ydbcommit( )) != RTN_OK ){
				sprintf( G_msg, "DB2のCOMMITに失敗しました\n" );
				EditCsvMsg( G_msg );
				LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
								__FILE__, __LINE__);
				stcCNT.cnt_kanjya -= wcnt_kan;
				stcCNT.cnt_chiken -= wcnt_try;
			}
			stcCNT.cnt_kanjya += wcnt_kan;
			stcCNT.cnt_chiken += wcnt_try;
		}
	} else {
		strcpy( G_msg,"データ処理でエラーが発生しました。" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__);
       

		//2006.12.08 Kim Jinsuk DBエラー時異常終了させる
       	nSQLErrorValue = atoi(G_err);

 	   if(( ret = Ydbrollback( )) != RTN_OK ){
			sprintf( G_msg, "DB2のROLLBACKに失敗しました\n"  );
			EditCsvMsg( G_msg );
				LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
		}
       
		
		//==> 2006.12.08 Kim Jinsuk DBエラー時異常終了させる
       	if((nSQLErrorValue< 0)&& (nSQLErrorValue != -911)&&(nSQLErrorValue !=-803))
       	{
           	*stopValue = 1;
			sprintf(G_msg, "##### DBエラー　発生　##### %d", nSQLErrorValue);
        
			//printf("nSQLErrorValue %d stopValue %d \n",nSQLErrorValue, stopValue);
			return(RTN_NG);
        }
		//<== 2006.12.08 Kim Jinsuk DBエラー時異常終了させる

	}
	// DEBUG
	sprintf( G_msg, "最終入力件数(%d)kan[%d]chiken[%d]", 
		stcCNT.cnt_irai,stcCNT.cnt_kanjya,stcCNT.cnt_chiken  );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	memset( G_utkymd,	'\0', sizeof( G_utkymd ));
	memset( G_irino,	'\0', sizeof( G_irino ));
	G_zssdino=0;
	G_line=0;

	// TRACE
    sprintf( G_msg, "    患者情報・治験拡張テーブル作成処理が終了しました" );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "        全依頼件数                  ：%10d件"
														,stcCNT.cnt_irai );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            HD(SKIP)                ：%10d件"
        												,stcCNT.cnt_hd );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            TR(SKIP)                ：%10d件"
        												,stcCNT.cnt_tr );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            削除依頼件数(SKIP)      ：%10d件"
														,stcCNT.cnt_irai_del );
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

    sprintf( G_msg, "            治験拡張情報登録件数    ：%10dﾚｺｰﾄﾞ"
														,stcCNT.cnt_chiken );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  関 数 名  ：ReadPnc                                                       */
/*  機能概要  ：ＰＮＣ依頼ファイル読み込み                                    */
/*  入    力  ：                                                              */
/*   第１引数 ： char	file_nm[]	: 入力ファイルポインタ                    */
/*  出    力  ： char	rbuf[];		: 読み込みバッファ                        */
/*  復帰情報  ： 0以上				: 正常終了(読込サイズ)                    */
/*               EOF				: FILE END                                */
/*               以外				: 失敗                                    */
/******************************************************************************/
int     ReadPnc( rbuf, pfp )
char		rbuf[];				/* ﾚｺｰﾄﾞ読み込みﾊﾞｯﾌｧ */
FILE		*pfp;				/* ﾌｧｲﾙ識別子 */
{
 	char    func_nm[MYAPP_LEN_FNCNM+1];	/* 関数名称     */

 	/* 初期処理     */
 	strcpy( func_nm, "ReadPnc" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	memset( rbuf, 0x00, sizeof( rbuf ));
	if( fgets( rbuf, PNC_RECSIZE + 1, pfp ) == NULL ){
		/* ﾃﾞｰﾀなし	*/
		return( EOF );
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( strlen( rbuf ) );
}

/******************************************************************************/
/*  関 数 名  ：NxtProc                                                       */
/*  機能概要  ：次世代依頼ファイル処理                                        */
/*  入    力  ：                                                              */
/*   第１引数 ： FILE	fp	: 入力ファイル識別子                              */
/*  出    力  ： なし                                                         */
/*  復帰情報  ： INT                                                          */
/*               RTN_OK     : 成功                                            */
/*               RTN_NG     : 失敗                                            */
/******************************************************************************/
int		NxtProc( nfp )
FILE    	*nfp;
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称		*/
	int		ret;							/* 関数戻り値	*/

	/* 初期設定	*/
	strcpy( func_nm, "NxtProc" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  関 数 名  ：ReadNxt                                                       */
/*  機能概要  ：次世代依頼ファイル読み込み                                    */
/*  入    力  ：                                                              */
/*   第１引数 ： char	file_nm[]	: 入力ファイルポインタ                    */
/*  出    力  ： char	rbuf[];		: 読み込みバッファ                        */
/*  復帰情報  ： 0以上				: 正常終了(読込サイズ)                    */
/*               EOF				: FILE END                                */
/*               以外				: 失敗                                    */
/******************************************************************************/
int     ReadNxt( rbuf, nfp )
char		rbuf[];				/* ﾚｺｰﾄﾞ読み込みﾊﾞｯﾌｧ */
FILE		*nfp;				/* ﾌｧｲﾙ識別子 */
{
 	char    func_nm[MYAPP_LEN_FNCNM+1];            /* 関数名称     */

 	/* 初期処理     */
 	strcpy( func_nm, "ReadNxt" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	memset( rbuf, 0x00, sizeof( rbuf ));
	if( fgets( rbuf, NXT_RECSIZE + 1, nfp ) == NULL ){
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
