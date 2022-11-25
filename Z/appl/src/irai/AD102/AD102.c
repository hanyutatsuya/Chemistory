/******************************************************************************/
/*   ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/*   システム名：次世代システム                                               */
/*   ファイル名：AD102.c                                                      */
/*   概      要：検査受付（依頼展開）依頼情報登録                             */
/*	 OS        ：SUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   言語      ：DB2/C                                                        */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/28     INTEC.INC      CREATE                             */
/*  1.01     2006/05/01     INTEC.INC      SJIS,項目追加対応                  */
/*  1.02     2006/05/03     INTEC.INC      UPDATE 引数としてINIファイル指定   */
/*  1.03     2006/06/10     INTEC.INC      患者属性修正時依頼情報世代No更新   */
/*  1.04     2006/06/26     INTEC.INC      自動発生項目登録＋検査G編集追加    */
/*  1.05     2006/08/15     INTEC.INC      未着再生の自動発生項目更新対応     */
/*  2.01     2006/09/28     INTEC.INC      集検万台404の追加                  */
/******************************************************************************/

/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "bmllog.h"
#include "AD102.h"

/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/
iconv_t		G_ic;						// with iconv
char		G_fnm[256];					// InputFileName
char		G_err[MYAPP_LEN_ERR+1];		// LogMessage(errcode)
char		G_msg[MYAPP_LEN_MSG+1];		// LogMessage
char		G_utkymd[10+1];				// LogMessage(csv)
char		G_irino[13+1];				// LogMessage(csv)
char		G_kntno[13+1];				// LogMessage(csv)
int			G_zssdino;					// LogMessage(csv)
char		G_kmkcd[7+1];				// LogMessage(csv)
int			G_line;						// InputFileLineNo

struct		_KJNMST		*pKjn;

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

	struct	SHM stcShm;					// 終了判断共有メモリ
	int		li_stopFlg = 0;				// 終了判断
	
	/*=====================================================*/
	/*	バックグラウンド実行                               */
	/*=====================================================*/

/*
	if ( daemon ( 0,  1) < 0 ) {
			exit( 1 );
	}
*/


	/*=====================================================*/
	/*	初期設定                                           */
	/*=====================================================*/
	strcpy( func_nm,	"main" );
	memset( G_msg,		'\0', sizeof( G_msg ) );
	memset( G_utkymd,	'\0', sizeof( G_utkymd ) );
	memset( G_irino,	'\0', sizeof( G_irino ) );
	memset( G_kntno,	'\0', sizeof( G_kntno ) );
	memset( G_kmkcd,	'\0', sizeof( G_kmkcd ) );
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
		sprintf( G_msg, "DB2との接続に失敗しました。" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		exit( 1 );
     }

	// 	基準日取得
	GetKjnymd( );

	// 基準値マスタ取得
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
	for( ; ; ){		// ......................................... daemon start
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
			//  基準日取得
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
				// 先頭１文字目での処理判断 N:次世代 P:PNC
				// INI FILE GENERATION PARAM での処理判断
			if( strcmp( stcPRM.myp_gene, "PNC" ) == 0 ){

                //2006.12.08 Kim Jinsuk 
				//ret = PncProc( fp );
                ret = PncProc(fp, &li_stopFlg);
                //2006.12.08 Kim Jinsuk

			} else {
				ret = NxtProc( fp );
			}
			if( ret == RTN_NG ){
				sprintf( G_msg, "[%s]処理中にエラーが発生しました。"
					,w_infilenm );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm
						, __FILE__, __LINE__ );

                //==> 2006.12.08 Kim Jinsuk DBエラー時
				if(li_stopFlg== 1) 
				{
                	sprintf(G_msg, "[[DB ERROR]]");
					//sprintf(G_msg, "li_stopFlg %d", li_stopFlg);
					//<== 2006.12.08 Kim Jinsuk DBエラー時
					LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm
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
		}		// -----------------------------------------> ファイルの件数分

		// scandir ファイル名のfree
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
				sprintf( G_msg,
					"共有メモリ生成に失敗したため、処理を終了します。" );
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

	}	// ...................................................... daemon for

	/*=====================================================*/
	/*	終了処理                                           */
	/*=====================================================*/
	// ICONV CLOSE
	// 1.01 DELL	iconv_close( G_ic );

	/* DB2との接続解除 */
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
fprintf(stderr,"説明:依頼情報登録処理\n" );
fprintf(stderr,"    :検査受付（依頼展開）依頼情報を登録します\n" );
fprintf(stderr,"     依頼取得ディレクトリ[%s]\n", stcPRM.ifp_indir );
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
	// ログオープン
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
        sscanf( cp, "%s", stcPRM.myp_gene );
    }
    cp = GetIniFile( "MYAPP.PARA", "MYAPP_LOGNM2", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.lgp_flog );
    }
    cp = GetIniFile( "MYAPP.PARA", "MYAPP_SLEEP", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%d", &stcPRM.myp_sleep );
    }
    cp = GetIniFile( "MYAPP.PARA", "MYAPP_SEDAI", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%d", &stcPRM.myp_sedai );
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
	sprintf( G_msg, "G_flog    [%s]",	stcPRM.lgp_flog );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "G_sleep   [%d]",	stcPRM.myp_sleep );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "app_gene   [%s]",	stcPRM.myp_gene );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "G_sedai   [%d]",	stcPRM.myp_sedai );
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

	struct  _SYSKNRMST  knr;
	struct	{
		int	yyyy;
		int	mm;
		int	dd;
	} BmlDate;

	/* 初期設定	*/
	strcpy( func_nm,	"GetKjnymd" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	// 基準処理日の取得
	memset( &knr,   '\0',   sizeof( struct _SYSKNRMST ) );
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
/*  出    力  ： なし                                                         */
/*  復帰情報  ： INT                                                          */
/*               RTN_OK     : 成功                                            */
/*               RTN_NG     : 失敗                                            */
/******************************************************************************/
//==> 2006.12.08 Kim Jinsuk
//int		PncProc( pfp )
int		PncProc( pfp , stopValue)
FILE    	*pfp;
int         *stopValue;
//<== 2006.12.08 Kim Jinsuk
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称		*/
	int		ret;							/* 関数戻り値	*/

	/* 依頼受信PNC format(S-JIS) */
	struct	Z01SJTR			z01sjitr;	/* PNC受信トレーラー(S-JIS) */
	struct	Z05SJIR1		z05sjir1;	/* PNC受信依頼(S-JIS) */
	struct	Z11SJIRF		z11sjirf;	/* PNC受信END(S-JIS) */

	struct	_IRAI			iri;		/* 依頼情報	*/
	struct	CNT				stcCNT;		/* 件数情報		*/

	struct	JIDOIRAI		*pJir;		// 1.04 ADD

	char	rbuf[PNC_RECSIZE*2+1];		/* 読み込みｴﾘｱ		*/
	char	w_key[MYAPP_LEN_KEY+1];
	char	w_key_del[1+1];
	char	w_str[200];
	int		w_max_zssdino;
	int		wcnt_iri=0;					/* 依頼情報登録件数*/
	int		wcnt_iri_del=0;				/* 依頼情報削除更新件数*/
	int		wcnt_rf=0;					/* 治験拡張属性登録件数	*/
	int		w_cnt;
	int		i,j;						/* index		*/
	int		jd_max;						// 1.04 ADD 自動発生項目数
	char    w_age[3+1];           		/* 1.04 ADD 年齢         */
    char    w_age_kbn[1+1];       		/* 1.04 ADD 年齢区分         */

	//2006.12.08 Kim Jinsuk DBエラー時
	int     nSQLErrFlag;                     

	/* 初期設定	*/
	strcpy( func_nm,	"PncProc" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ｸﾘｱ	*/
	ret = RTN_OK;

	stcCNT.cnt_irai=stcCNT.cnt_irai_err=0;
	stcCNT.cnt_hd=stcCNT.cnt_tr=stcCNT.cnt_r1=stcCNT.cnt_rf=stcCNT.cnt_oth=0;
	stcCNT.cnt_dbirai=stcCNT.cnt_dbirai_del=stcCNT.cnt_end=0;
	stcCNT.cnt_dbirai_jdi=0;
	memset( w_key, '\0', sizeof( w_key ));
	memset( w_key_del, '\0', sizeof( w_key_del ));

	sprintf( G_msg,	"受付（依頼展開） 依頼情報テーブル作成開始 : " 
					"依頼ファイル名[%s]", G_fnm );
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
		memset( G_kntno,	'\0', sizeof( G_kntno ));
		memset( G_kmkcd,	'\0', sizeof( G_kmkcd ));
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
		//if( strlen( rbuf ) != ( PNC_RECSIZE + 1 ))[
			// ERROR
			//stcCNT.cnt_irai_err++ ;	
			sprintf( G_msg, "読み込みレコードサイズエラー[%d]", strlen( rbuf ));
			EditCsvMsg( G_msg );
			LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

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
/*==============
DEL			memset( w_str, '\0', sizeof( w_str ));
DEL			w_cnt = atol( strncpy( w_str, z01sjitr.c_reccnt02, 8 ));
DEL			if( stcCNT.cnt_rf != w_cnt ){
DEL				// ERROR
DEL				sprintf( G_msg, "トレーラーの論理レコード数と一致しません。"
DEL						"TR-R2[%d]->[%d]", w_cnt, stcCNT.cnt_r2 );
DEL				EditCsvMsg( G_msg );
DEL				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, 
DEL								__FILE__, __LINE__);
DEL			}
*/
			// トレーラーは強制的に KEY-BREAK
			memset( w_key, '9', MYAPP_LEN_KEY );

		} else 
			// R2 治験拡張は読み飛ばし
		if( strncmp( rbuf, "R2", 2 ) == 0 ){
			stcCNT.cnt_oth++;
			continue;
		}

		// トレーラー後のレコード存在はエラー
		if(( stcCNT.cnt_tr == 1 )&&( strncmp( rbuf, "TR", 2 ) != 0 )){
			// ERROR
			sprintf( G_msg, "トレーラー後にレコードが含まれています。[%.2s]"
					,rbuf );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}
		// RF後のTR以外のレコード存在はエラー
		if(( ( stcCNT.cnt_end == 1 ) || ( wcnt_rf == 1 ))
	 	 &&( strncmp( rbuf, "TR", 2 ) != 0 )){
			// ERROR
			sprintf( G_msg, "依頼ＥＮＤの後にレコードが含まれています。[%.2s]"
					,rbuf );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}

		// 1件目はKEY-BREAKさせない
		if( stcCNT.cnt_irai == 2 ){
			memcpy( w_key,		&rbuf[2],	MYAPP_LEN_KEY );
			memcpy( w_key_del,	&rbuf[77],	1 );
		}
		/* --------------------------------	*/
		/*	処理 							*/
		/* --------------------------------	*/
		// DEBUG
		sprintf( G_msg, "処理 sbt[%.2s]in[%.19s] key[%s]"
				, rbuf, &rbuf[2], w_key );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

//-----< 同一BML受日・依頼書NOで削除フラグが等しいものを
//		                    1TRANSACTIONとするためKEYの比較を行う >------------
		if(( memcmp( w_key,		&rbuf[2],  MYAPP_LEN_KEY ) != 0 )
		 ||( memcmp( w_key_del, &rbuf[77], 1 ) != 0 )){
			// DEBUG
			sprintf( G_msg, "KEY-BREAK処理 : ret[%d]iri[%d]del[%d]rf[%d]"
					"------------------------",
					ret, wcnt_iri, wcnt_iri_del, wcnt_rf );
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
				// 削除の場合は、自動発生処理を行わない
				if( w_key_del[0] == 0 ){
					break;
				}
				// 自動発生項目の有無チェック
        		if(( jd_max=SelCountJkmkmst( iri.utkymd
											, iri.irino, iri.sriymd )) < 1 ){
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
				strcpy( pJir[0].sIri.utkymd,		iri.utkymd );
				strcpy( pJir[0].sIri.irino,			iri.irino );
				strcpy( pJir[0].sIri.sriymd,		iri.sriymd );
				// 対象データ情報の取得
				if( SelJidoirai( pJir, jd_max ) !=  RTN_OK ){
					sprintf( G_err, "%d", errno );
					sprintf( G_msg, "基準値マスタの読み込みに失敗しました。" );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm,
									__FILE__, __LINE__ );
					free( pJir );
					ret=RTN_NG;
					break;
				}
				for( i = 0; i < jd_max; i++ ){
					// EDIT
					strcpy( pJir[i].age,		w_age );
					strcpy( pJir[i].agekbn,		w_age_kbn );
					// if( EditJidoIrai( &pJir[i] ) != RTN_OK )[
					if( EditJidoIrai( &(pJir[i]) ) != RTN_OK ){
						// ERROR
						strcpy( G_msg,
							"自動発生依頼情報編集時にエラーが発生しました。" );
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, 
										__FILE__, __LINE__);
						ret = RTN_NG;

						break;
					}
					memcpy( &iri, &pJir[i].sIri, sizeof( struct _IRAI ));
					/* INSERT */
					if( InsIrai( &iri ) != RTN_OK ){
						// ERROR
						strcpy( G_msg,
							"自動発生依頼情報登録時にエラーが発生しました。" );
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, 
										__FILE__, __LINE__);
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
				if(( ret = Ydbcommit( )) != RTN_OK ){
						// ERROR
					strcpy( G_msg, "DB2のCOMMITに失敗しました。\n" );
					EditCsvMsg( G_msg );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__ );
					stcCNT.cnt_dbirai		-= wcnt_iri;
					stcCNT.cnt_dbirai_del	-= wcnt_iri_del;
					stcCNT.cnt_end			-= wcnt_rf;
					// 1.04 ADD
					stcCNT.cnt_dbirai_jdi	-= jd_max;
				}
				stcCNT.cnt_dbirai		+= wcnt_iri;
				stcCNT.cnt_dbirai_del	+= wcnt_iri_del;
				stcCNT.cnt_end			+= wcnt_rf;
					// 1.04 ADD
				stcCNT.cnt_dbirai_jdi	+= jd_max;
			} else {
				// ERROR
				strcpy( G_msg, "データ処理でエラーが発生しました。" );
				EditCsvMsg( G_msg );
				LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__);

			
			    //2006.12.08 Kim Jinsuk DBエラー時異常終了させる	
			    nSQLErrFlag = atoi(G_err);
				//nSQLErrFlag = -5000;
				sprintf(G_msg, "nSQLErrFlag %d", nSQLErrFlag);
				LogOut(LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);				
				
				
				if(( ret = Ydbrollback( )) != RTN_OK ){
						// ERROR
					strcpy( G_msg, "DB2のROLLBACKに失敗しました。\n"  );
					EditCsvMsg( G_msg );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm,
							__FILE__, __LINE__);
				}

				
				//==> 2006.12.08 Kim Jinsuk DBエラー時異常終了させる
		        if((nSQLErrFlag< 0)&& (nSQLErrFlag != -911)&&(nSQLErrFlag !=-803))
				{
				
					*stopValue = 1;

					sprintf(G_msg, "###### 自動発生処理後　DBエラー発生 #####");
                    LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm,
                            __FILE__, __LINE__);
					
					return (RTN_NG);	
				}
                //<== 2006.12.08 Kim Jinsuk DBエラー時異常終了させる

			}
			// KEY SET
			wcnt_iri = wcnt_iri_del = wcnt_rf = 0;

			memcpy( w_key,		&rbuf[2], MYAPP_LEN_KEY );
			memcpy( w_key_del,	&rbuf[77],1 );

			// DEBUG
			strcpy( G_msg, "KEY-BREAK処理 END ---------------------->" );
			LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}

		ret = RTN_OK;

//-----< R1 >---------------------------------------------------------------
			// 依頼 
		if(( strncmp( rbuf, "R1", 2 ) == 0 )&&( rbuf[77]!='1' )){
			stcCNT.cnt_r1++;
			memcpy( &z05sjir1,	rbuf, sizeof( struct Z05SJIR1 ) );
			memset( &iri,		'\0', sizeof( struct _IRAI ));
			do {		/* Do-whileは１回のみ実行	　	*/
				/* 編集 */
				if(( ret= EditPncIrai( &z05sjir1, &iri )) != RTN_OK ){
					/* ｴﾗｰ*/
					ret = RTN_NG;
					break;
				}
				/* 共通箇所の編集 */
				if( EditCommonIrai( &iri ) != RTN_OK ){
					/* ｴﾗｰ*/
					ret = RTN_NG;
					break;
				}
				// 1.03 患者属性の世代Noを取得する
				if( wcnt_iri == 0 ){
					if((	w_max_zssdino = SelKanjyaZssdinoMax( &iri )) < 0 ){
						w_max_zssdino = stcPRM.myp_sedai;;
					}
					// 1.04 ADD 自動発生項目基準値取得のため年齢を退避
					memset( w_age,		'\0',	sizeof( w_age ));
					memset( w_age_kbn,	'\0',	sizeof( w_age_kbn ));
					memcpy( w_age,		z05sjir1.c_age,	sizeof(z05sjir1.c_age));
					memcpy( w_age_kbn,	z05sjir1.c_age_kbn,	
										sizeof( z05sjir1.c_age_kbn ));
				}
				iri.zssdino = w_max_zssdino;
				/* INSERT */
				if(( ret = InsIrai( &iri )) != RTN_OK ){
					if( ret != MYAPP_RTN_DUP ){
						// ERROR
						strcpy( G_msg,
							"依頼情報登録時にエラーが発生しました。" );
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, 
									__FILE__, __LINE__);
						ret = RTN_NG;

						break;
					}
					// データ重複
					// 1.03 未着再生の依頼はUPDATE
					// 1.05 DELL if(( ret = UpdMichakuIrai( &iri )) != RTN_OK )[
					// 1.05 未着再生関連自動発生項目基準値再取得用に引数追加
					if(( ret = UpdMichakuIrai( &iri, w_age, w_age_kbn )) != RTN_OK ){
						if( ret == RTN_ZERO ){
							// 未着再生対象外　WARNING -> SKIP
							// 同一キーの他データ救済のためOKとする
							strcpy( G_msg, "既に依頼情報が存在します。" );
							EditCsvMsg( G_msg );
							LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, 
										__FILE__, __LINE__);
							stcCNT.cnt_irai_err++;
							ret = RTN_OK;
							break;
						} else {
							// ERROR
							strcpy( G_msg,
								"依頼情報登録時にエラーが発生しました。" );
							EditCsvMsg( G_msg );
							LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, 
										__FILE__, __LINE__);
						}
					}
				}
				wcnt_iri++;	
			} while( wcnt_iri < 1 );
//-----< R1 DEL>---------------------------------------------------------------
		} else if(( strncmp( rbuf, "R1", 2 ) == 0 )&&( rbuf[77]=='1' )){
			stcCNT.cnt_r1++;
			memcpy( &z05sjir1,	rbuf, sizeof( struct Z05SJIR1 ) );
			memset( &iri,		'\0', sizeof( struct _IRAI ));
			do {		/* Do-whileは１回のみ実行	　	*/
				/* 編集 */
				if(( ret= EditPncIrai( &z05sjir1, &iri )) != RTN_SKIP ){
					/* ｴﾗｰ*/
					ret = RTN_NG;
					break;
				}
				ret=RTN_OK;
				// Irai.tktyflg UPDATE
				if( UpdIraiSjflg( &iri ) != RTN_OK ){
					// ERROR -> Logは.sqcにて出力
					//strcpy( G_msg, 
					//	"依頼情報削除フラグ更新時にエラーが発生しました。" );
					//EditCsvMsg( G_msg );
					//LogOut( LT_ERR, LX_INS, G_err, G_msg, func_nm, 
					//				__FILE__, __LINE__);
					/* ｴﾗｰ*/
					ret = RTN_NG;
					break;
				}
				wcnt_iri_del++;	
			} while( wcnt_iri_del < 1 );
//-----< R2 >---------------------------------------------------------------
		} else if( strncmp( rbuf, "RF", 2 ) == 0 ){	// 依頼END
			stcCNT.cnt_rf++;
			memcpy( &z11sjirf, rbuf, sizeof( struct Z11SJIRF ) );
			do {		/* Do-whileは１回のみ実行	　	*/
				// WARNING
				sprintf( G_msg, 
					"基準処理年月日[%s]  依頼ＥＮＤ情報を受信しました。", 
					stcPRM.myp_kjnymd );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, 
							__FILE__, __LINE__);

				// Sysknrmst.iriendflg, irienddh UPDATE
						// 次依頼処理年月日は初期値をセット
				if( UpdSysknrmstIriend( INIT_DATE ) != RTN_OK ){
					/* ｴﾗｰ*/
					ret = RTN_NG;
					break;
				}
				wcnt_rf++;	
			} while( wcnt_rf < 1 );
		}
		if( ret != RTN_OK ){	
			stcCNT.cnt_irai_err++;
		}
	}	// <---------------------------------------------------read while end

//-----< 1FILE READ END >-------------------------------------------------------
	// トレーラー無しはエラー
	if( stcCNT.cnt_tr == 0 ){
		// ERROR
		strcpy( G_msg, "トレーラーがありません。" );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

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
			// 削除の場合は、自動発生処理を行わない
			if( w_key_del[0] == 0 ){
				break;
			}
			// 自動発生項目の有無チェック
       		if(( jd_max=SelCountJkmkmst( iri.utkymd
										, iri.irino, iri.sriymd )) < 1 ){
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
			strcpy( pJir[0].sIri.utkymd,		iri.utkymd );
			strcpy( pJir[0].sIri.irino,			iri.irino );
			strcpy( pJir[0].sIri.sriymd,		iri.sriymd );
			// 対象データ情報の取得
			if( SelJidoirai( pJir, jd_max ) !=  RTN_OK ){
				sprintf( G_err, "%d", errno );
				sprintf( G_msg, "基準値マスタの読み込みに失敗しました。" );
				LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm,
								__FILE__, __LINE__ );
				free( pJir );
				ret=RTN_NG;
				break;
			}
			for( i = 0; i < jd_max; i++ ){
				// EDIT
				strcpy( pJir[i].age,		w_age );
				strcpy( pJir[i].agekbn,		w_age_kbn );

				if( EditJidoIrai( &pJir[i] ) != RTN_OK ){
					// ERROR
					strcpy( G_msg,
						"自動発生依頼情報編集時にエラーが発生しました。" );
					EditCsvMsg( G_msg );
					LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, 
									__FILE__, __LINE__);
					ret = RTN_NG;
					break;
				}
				memcpy( &iri, &pJir[i].sIri, sizeof( struct _IRAI ));

				/* INSERT */
				if( InsIrai( &iri ) != RTN_OK ){
					// ERROR
					strcpy( G_msg,
						"自動発生依頼情報登録時にエラーが発生しました。" );
					EditCsvMsg( G_msg );
					LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, 
									__FILE__, __LINE__);
					ret = RTN_NG;
					break;
				}
			}
			free( pJir );
			break;
		} while( 1 );
		// 1.04 ADD 自動発生処理　END ===================================

	}
	// トレーラー無しでCOMMITが必要な場合の考慮
		/* エラー発生チェック	*/
	if( ret == RTN_OK ){
		if(( wcnt_iri > 0 )||( wcnt_iri_del > 0 )||( wcnt_rf > 0 )){
        	if(( ret = Ydbcommit( )) != RTN_OK ){
				sprintf( G_msg, "DB2のCOMMITに失敗しました\n" );
				EditCsvMsg( G_msg );
				LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
								__FILE__, __LINE__);
				stcCNT.cnt_dbirai -= wcnt_iri;
				stcCNT.cnt_dbirai_del -= wcnt_iri_del;
				stcCNT.cnt_end -= wcnt_rf;
			}
			stcCNT.cnt_dbirai += wcnt_iri;
			stcCNT.cnt_dbirai_del += wcnt_iri_del;
			stcCNT.cnt_end += wcnt_rf;
		}
	} else {
		// ERROR
		strcpy( G_msg,"データ処理でエラーが発生しました。" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);

      
       //2006.12.08 Kim Jinsuk DBエラー時異常終了させる	
		nSQLErrFlag = atoi(G_err);
		sprintf(G_msg,"nSQLErrFlag %d", nSQLErrFlag);
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
		

		if(( ret = Ydbrollback( )) != RTN_OK ){
			sprintf( G_msg, "DB2のROLLBACKに失敗しました\n"  );
			EditCsvMsg( G_msg );
			LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
		}
		
		//==> 2006.12.08 Kim Jinsuk DBエラー時異常終了させる
		if( (nSQLErrFlag< 0)&& (nSQLErrFlag != -911)&&(nSQLErrFlag !=-803))
		{
			*stopValue =1;
			sprintf(G_msg, "###### 自動発生処理後　DBエラー発生 #####");
			printf("###### 自動発生処理後　DBエラー発生 ######\n");
			printf("nSQLErrFlag %d\n", nSQLErrFlag);

			return (RTN_NG);
		}	
        //<== 2006.12.08 Kim Jinsuk DBエラー時異常終了させる
		
	}
	// DEBUG
	sprintf( G_msg, "最終入力件数(%d)iri[%d]end[%d]", 
		stcCNT.cnt_irai,stcCNT.cnt_dbirai,stcCNT.cnt_end  );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	memset( G_utkymd,	'\0', sizeof( G_utkymd ));
	memset( G_irino,	'\0', sizeof( G_irino ));
	memset( G_kntno,	'\0', sizeof( G_kntno ));
	memset( G_kmkcd,	'\0', sizeof( G_kmkcd ));
	G_zssdino=0;
	G_line=0;

	// TRACE
    sprintf( G_msg, "    依頼情報テーブル作成処理が終了しました" );
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

    sprintf( G_msg, "            OTHER(SKIP)             ：%10d件"
        												,stcCNT.cnt_oth );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            エラー依頼件数(SKIP)    ：%10d件"
														,stcCNT.cnt_irai_err );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            依頼情報登録件数        ：%10dﾚｺｰﾄﾞ"
														,stcCNT.cnt_dbirai );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            自動発生依頼情報登録件数：%10dﾚｺｰﾄﾞ"
														,stcCNT.cnt_dbirai_jdi);
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            削除依頼件数(UPD)       ：%10d件"
														,stcCNT.cnt_dbirai_del);
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            依頼ＥＮＤ情報更新      ：%10dﾚｺｰﾄﾞ"
														,stcCNT.cnt_end );
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

	memset( rbuf, '\0', sizeof( rbuf ));
	if( fgets( rbuf, PNC_RECSIZE+10, pfp ) == NULL ){
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

	memset( rbuf, '\0', sizeof( rbuf ));
	if( fgets( rbuf, NXT_RECSIZE, nfp ) == NULL ){
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
