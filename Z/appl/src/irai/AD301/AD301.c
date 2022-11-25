/******************************************************************************/
/*   ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/*   システム名：次世代システム                                               */
/*   ファイル名：AD301.c                                                      */
/*   概      要：検査受付（要求カード送信）要求カード作成                     */
/*	 OS        ：SUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   言語      ：DB2/C                                                        */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/04/03     INTEC.INC      CREATE                             */
/*  1.01     2006/05/03     INTEC.INC      UPDATE 引数としてINIファイル指定   */
/******************************************************************************/

/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "bmllog.h"
#include "AD301.h"

/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/
iconv_t     G_ic;                       // with iconv
char		G_err[MYAPP_LEN_ERR+1];		// LogMessage(errcode)
char		G_msg[MYAPP_LEN_MSG+1];		// LogMessage
int			G_line;						// InputFileLineNo

char		G_otdir[256+1];				// 出力DIRECTRY
char		G_ext[10+1];				// 出力ファイル拡張子

struct		_SYSKNRMST	pKnr;			// システム管理マスタ

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
	int		iri,kan;						// Loop
	int		kan_cnt, kan_end_cnt, iri_cnt = 0;
	int		ini_flg = 0;

	struct	Z00SJHD		z00;			// HD ヘッダ
	struct	Z01SJTR		z01;			// TR トレーラー
	struct	Z12SJR1		z12;			// R1 要求カード

	struct	SHM stcShm;					// 終了判断共有メモリ
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
	memset( &pKnr,		'\0', sizeof( struct _SYSKNRMST ) );
	G_line=0;

	// パラメータ取得
	if( ParamCheckProc( argc, argv, &stcShm ) != RTN_OK ){
		/* ﾍﾙﾌﾟﾒｯｾｰｼﾞ出力	*/
		DispHelpMsg( argc, argv );
		exit( 1 );
	}

	/* 2重起動チェック	*/
	if( DaemonCheckProc( argc, argv ) != RTN_OK ){
		sprintf( G_msg, "２重起動防止のため、処理を終了します。" );
		LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
		exit( 1 );
	}

	// 共有メモリ生成
	if( sFncShmCrt ( &stcShm ) < 0 ) {
		sprintf( G_msg, "共有メモリ生成に失敗したため、処理を終了します。" );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		exit( 1 );
	}

    // DB2との接続 
	if(( ret = Ydbconn( )) != RTN_OK ){
		sprintf( G_msg, "DB2との接続に失敗しました。" );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		exit( 1 );
     }

	/* FILE OPEN FOR ICONV */
//    G_ic = iconv_open( "EUC-JP", "SHIFT-JIS" );

	// 	システム管理マスタ取得
	SelSysknrmst( &pKnr );

	// HD,TR,R1 編集
	memset( &z00,	'\0',	sizeof( struct	Z00SJHD ));
	memset( &z01,	'\0',	sizeof( struct	Z01SJTR ));
	memset( &z12,	'\0',	sizeof( struct	Z12SJR1 ));
	EditInitRequest( &z00, &z01, &z12 );

	// LOOP 回数取得 各ファイルを何秒に１回作成するか
	// 分注作成タイミングを１単位とし、何単位毎に依頼、患者を作成するか
	iri_cnt = stcPRM.ifp_iri_time / stcPRM.ifp_bun_time;
	if( iri_cnt == 0 ){
		iri_cnt = 1;
	}
	kan_cnt = stcPRM.ifp_kan_time / stcPRM.ifp_bun_time;
	if( kan_cnt == 0 ){
		kan_cnt = 1;
	}

	sprintf( G_msg, "LOOP 回数 iri_cnt[%d] kan_cnt[%d]\n", iri_cnt, kan_cnt );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	/*=====================================================*/
	/* メインルーティン                                    */
	/*=====================================================*/
	iri = kan = kan_end_cnt = 0;
	for( ; ; ){		// ......................................... daemon start
		sprintf( G_msg, "MainLoop iend[%s]bend[%s]ecnt[%d]================>\n", 
			pKnr.iriendflg, pKnr.bchendflg, kan_end_cnt );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

		// =============================================
		// 依頼＆分注END受信済み
		// 依頼END受信後患者要求3回送信済み
		// =============================================
		if(( strcmp( pKnr.iriendflg, "1" ) == 0 )
		 &&( strcmp( pKnr.bchendflg, "1" ) == 0 )
		 &&( kan_end_cnt >= 3 )){
			// 処理終了
			break;
		}

		// =============================================
		// 分注結果　要求カード作成
		// =============================================
		if( WriteRequestFile( MYAPP_BUN, &z00, &z01, &z12 ) == RTN_NG ){
			// ERROR
			strcpy( G_msg, "分注結果　要求カード作成処理にて"
				"エラーが発生しました。");
			LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}

		iri++;
		kan++;

		// =============================================
		// 	初回　or　分注を？回出力　->　依頼要求作成
		// =============================================
		if(( ini_flg == 0 )||( iri == iri_cnt )){
			iri=0;
			// 依頼情報　要求カード作成
			if( WriteRequestFile( MYAPP_IRI, &z00, &z01, &z12 ) == RTN_NG ){
				// ERROR
				strcpy( G_msg, "依頼情報　要求カード作成処理にて"
					"エラーが発生しました。");
				LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, 
						__FILE__, __LINE__);
			}
		}

		// ===========================================================
		// 	初回　or　分注を？回出力　or　依頼END後患者要求回送信済み
		//	-> 患者要求作成
		// ===========================================================
		if(( ini_flg == 0 )||( kan == kan_cnt )){
			if( kan_end_cnt < 3 ){
				kan=0;
				// 患者情報　要求カード作成
				if( WriteRequestFile( MYAPP_KAN, &z00, &z01, &z12 ) == RTN_NG ){
					// ERROR
					strcpy( G_msg, "患者情報　要求カード作成処理にて"
						"エラーが発生しました。");
					LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, 
							__FILE__, __LINE__);
				}
			}
			if( strcmp( pKnr.iriendflg, "1" ) == 0 ){
				kan_end_cnt++;
			}
		}
		// 初期フラグをONに
		if( ini_flg == 0 ){
			ini_flg = 1;
		}

		// SLEEP
		sprintf( G_msg, "SLEEP .....BUN_SLEEP_TIME[%d]", stcPRM.ifp_bun_time );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

		sleep( stcPRM.ifp_bun_time );
	
		//------------------
		// 終了判断
		//------------------
			// 共有メモリ取得
		if( sFncShmGet ( &stcShm, &li_stopFlg ) < 0 ){
			// WARNING
			sprintf( G_msg,
				"共有メモリ生成に失敗したため、処理を終了します。" );
			LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			break;
		}
		if( li_stopFlg == 1 ){
				// TRACE
			sprintf( G_msg, "終了指示が出たため、処理を終了します。");
			LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			break;
		} 

		// DAEMON SLEEP
		sprintf( G_msg, "SLEEP ..............[%d]", stcPRM.myp_sleep );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

		sleep( stcPRM.myp_sleep );
	
	}	// ...................................................... daemon for

	/*=====================================================*/
	/*	終了処理                                           */
	/*=====================================================*/
	// ICONV CLOSE
//    iconv_close( G_ic );

	/* DB2との接続解除 */
	if(( ret = Ydbdisconn( )) != RTN_OK ){
		// ERROR
		sprintf( G_msg, "DB2との接続解除に失敗しました。" );
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
fprintf(stderr,"説明:要求カード作成処理\n" );
fprintf(stderr,"    :検査受付（要求カード送信）要求カードを作成します\n" );
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
	char	*p_fini;					/* 1.01 INI FILE 名称	 */
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
	// 1.01 INI FILE を引数から受取る
	if( argc >= 2 ){
		p_fini = argv[1];
	} else {
		p_fini = MYAPP_INIFILE;
	}
	strncpy( stcPRM.myp_exefile, cp, sizeof( stcPRM.myp_exefile ) - 1 );
	strcpy( stcPRM.ifp_fprefix, "REQ" );
	stcPRM.myp_debug=0;
	stcPRM.myp_sleep=0;
	stcPRM.ifp_bun_time=120;
	stcPRM.ifp_iri_time=600;
	stcPRM.ifp_kan_time=1200;
	
	//-------------------------------
	// LOG出力初期処理
	//-------------------------------
	//cp = GetIniFile( "SERVER.LOG", "LOGINI", MYAPP_INIFILE );
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
		// 分注結果要求
    cp = GetIniFile( "HOST.PARA", "BUN_OTDIR", p_fini );
    if( cp != NULL ) {
		// 環境変数($HOME)を展開してからセット
		strcpy( stcPRM.ifp_bun_otdir, EnvRef( cp ));
    }
    cp = GetIniFile( "HOST.PARA", "BUN_EXT", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_bun_ext );
    }
    cp = GetIniFile( "HOST.PARA", "BUN_YKKBN", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_bun_ykkbn );
    }
    cp = GetIniFile( "HOST.PARA", "BUN_TIME", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%d", &stcPRM.ifp_bun_time );
    }

		// 依頼情報要求
    cp = GetIniFile( "HOST.PARA", "IRI_OTDIR", p_fini );
    if( cp != NULL ) {
		// 環境変数($HOME)を展開してからセット
		strcpy( stcPRM.ifp_iri_otdir, EnvRef( cp ));
    }
    cp = GetIniFile( "HOST.PARA", "IRI_EXT", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_iri_ext );
    }
    cp = GetIniFile( "HOST.PARA", "IRI_YKKBN", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_iri_ykkbn );
    }
    cp = GetIniFile( "HOST.PARA", "IRI_TIME", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%d", &stcPRM.ifp_iri_time );
    }

		// 患者情報要求
    cp = GetIniFile( "HOST.PARA", "KAN_OTDIR", p_fini );
    if( cp != NULL ) {
		// 環境変数($HOME)を展開してからセット
		strcpy( stcPRM.ifp_kan_otdir, EnvRef( cp ));
    }
    cp = GetIniFile( "HOST.PARA", "KAN_EXT", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_kan_ext );
    }
    cp = GetIniFile( "HOST.PARA", "KAN_YKKBN", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_kan_ykkbn );
    }
    cp = GetIniFile( "HOST.PARA", "KAN_TIME", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%d", &stcPRM.ifp_kan_time );
    }

		// HD,TR 編集情報
    cp = GetIniFile( "HOST.PARA", "FPREFIX", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_fprefix );
    }
    cp = GetIniFile( "HOST.PARA", "SOSINSAKI", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_sosinsaki );
    }
    cp = GetIniFile( "HOST.PARA", "SOSINMOTO", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_sosinmoto );
    }
    cp = GetIniFile( "HOST.PARA", "KAN_DFLOW", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_kan_dflow );
    }
    cp = GetIniFile( "HOST.PARA", "IRI_DFLOW", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_iri_dflow );
    }
    cp = GetIniFile( "HOST.PARA", "BUN_DFLOW", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_bun_dflow );
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
    cp = GetIniFile( "MYAPP.PARA", "MYAPP_SLEEP", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%d", &stcPRM.myp_sleep );
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

	sprintf( G_msg, "BUNCYU   [%s][%s][%s][%d]"
		,stcPRM.ifp_bun_otdir	,stcPRM.ifp_bun_ext
		,stcPRM.ifp_bun_ykkbn,stcPRM.ifp_bun_time );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "IRAI     [%s][%s][%s][%d]"
		,stcPRM.ifp_iri_otdir	,stcPRM.ifp_iri_ext
		,stcPRM.ifp_iri_ykkbn,stcPRM.ifp_iri_time );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "KANJYA   [%s][%s][%s][%d]"
		,stcPRM.ifp_kan_otdir	,stcPRM.ifp_kan_ext
		,stcPRM.ifp_kan_ykkbn,stcPRM.ifp_kan_time );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	sprintf( G_msg, "Dflow    [%s][%s][%s]", stcPRM.ifp_bun_dflow
			, stcPRM.ifp_iri_dflow, stcPRM.ifp_kan_dflow );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	sprintf( G_msg, "G_sleep   [%d]",	stcPRM.myp_sleep );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "app_gene   [%s]",	stcPRM.myp_gene );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  関 数 名  ：EditInitRequest                                               */
/*  機能概要  ：ＰＮＣ送信用ヘッダー、トレーラ、要求カード編集処理            */
/*	構文  : int	Lmk_hdtr( syok, pg, dflow, z00, z01 )                         */
/*  入    力  ：                                                              */
/*	引数  : (in) 	char	*syok;	 	職員ｺｰﾄﾞ                              */
/*		(in)	char	*pg;		PG_ID                                     */
/*		(in)	char	*dflow;	 	ﾃﾞｰﾀﾌﾛｰID	                              */
/*		(out)	struct  Z00SJHD	*z00;  	PNC送受信ﾍｯﾀﾞｰ構造体	              */
/*		(out)	struct 	Z01SJTR *z01;   PNC送受信ﾄﾚｰﾗｰ構造体                  */
/*                                                                            */
/*	ﾘﾀ-ﾝ値:  0  :正常終了                                                     */
/*		-1  :ｴﾗｰ                                                              */
/*                                                                            */
/*   第１引数 ：struct		dirent *     ディレクトリ構造体                   */
/*  出    力  ：なし                                                          */
/*  復帰情報  ： INT                                                          */
/*               0		: 対象外ファイル                                      */
/*               1		: 対象ファイル                                        */
/******************************************************************************/
int	EditInitRequest( z00, z01, z12 )
struct  Z00SJHD		*z00;    	/* PNC送受信ﾍｯﾀﾞｰ構造体	*/
struct 	Z01SJTR 	*z01;    	/* PNC送受信ﾄﾚｰﾗｰ構造体 */ 
struct 	Z12SJR1 	*z12;    	/* PNC送受信ﾄﾚｰﾗｰ構造体 */ 
{
#define	SQL_LOCK -54			/* record lock by other user	*//* ADD H001 */
#define	MAX_LOCK 50			/* ﾛｯｸ実行最大回数 	*//* ADD H001 */
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	 */
	char	w_fnm[256];

	int     ret;
	char    cbuf[512];
	char    dbuf[512];
	int	rcnt;			/* ﾛｯｸ実行回数		*//* ADD H001 */

	rcnt = 0;						 /* ADD H001 */

	strcpy( func_nm, "EditInitReqest" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	//====================================
	// PNC送受信 ヘッダ、トレーラー作成 
	//====================================
	memset( z00, ' ', sizeof( struct Z00SJHD ) );
    memset( z01, ' ', sizeof( struct Z01SJTR ) );
	memset( z12, ' ', sizeof( struct Z12SJR1 ) );

	/* ﾚｺｰﾄﾞ識別子		*/
   	memcpy( z00->c_sbt, "HD", sizeof( z00->c_sbt ));
    memcpy( z01->c_sbt, "TR", sizeof( z01->c_sbt ));
   	memcpy( z12->c_sbt, "R1", sizeof( z12->c_sbt ));

	/* 送信先               */
	memcpy( z00->c_sosinsaki,	stcPRM.ifp_sosinsaki, 
								strlen( stcPRM.ifp_sosinsaki ));
	memcpy( z01->c_sosinsaki,	stcPRM.ifp_sosinsaki, 
								strlen( stcPRM.ifp_sosinsaki));

	/* 送信元               */
	memcpy( z00->c_sosinmoto,	stcPRM.ifp_sosinmoto, 
								strlen( stcPRM.ifp_sosinmoto ));
	memcpy( z01->c_sosinmoto,	stcPRM.ifp_sosinmoto, 
								strlen( stcPRM.ifp_sosinmoto ));

	/* 送信元処理年月日     */
	memset( cbuf, '\0',	sizeof( cbuf ));
	sprintf( cbuf, "%.4s%.2s%.2s", 
		pKnr.kjnsriymd, &pKnr.kjnsriymd[5], &pKnr.kjnsriymd[8] );
	memcpy( z00->c_opedate, cbuf, sizeof( z00->c_opedate ));
	memcpy( z01->c_opedate, cbuf, sizeof( z01->c_opedate ));
	memcpy( z12->c_opedate, cbuf, sizeof( z12->c_opedate ));

	/* 通番                 */
	/* ﾃﾞｰﾀﾌﾛｰID		*/
		// 送信ファイル作成時に編集	

	/* 物理ﾚｺｰﾄﾞ件数 & 論理ﾚｺｰﾄﾞ件数１～１５ */
	/* '0' 編集(件数初期化用) */
	memset( cbuf, '0', sizeof( z01->c_reccnt ) );

	/* 物理ﾚｺｰﾄﾞ件数	<- 3REC 固定	*/
   	memcpy( z01->c_reccnt, cbuf, sizeof( z01->c_reccnt ));
	z01->c_reccnt[7] = '3';
	/* 論理ﾚｺｰﾄﾞ件数１～１５*/
		// R1 			<- 1REC 固定
	memcpy( z01->c_reccnt01, cbuf, sizeof( z01->c_reccnt01 ));
	z01->c_reccnt01[7] = '1';
	memcpy( z01->c_reccnt02, cbuf, sizeof( z01->c_reccnt02 ));
	memcpy( z01->c_reccnt03, cbuf, sizeof( z01->c_reccnt03 ));
	memcpy( z01->c_reccnt04, cbuf, sizeof( z01->c_reccnt04 ));
	memcpy( z01->c_reccnt05, cbuf, sizeof( z01->c_reccnt05 ));
	memcpy( z01->c_reccnt06, cbuf, sizeof( z01->c_reccnt06 ));
	memcpy( z01->c_reccnt07, cbuf, sizeof( z01->c_reccnt07 ));
	memcpy( z01->c_reccnt08, cbuf, sizeof( z01->c_reccnt08 ));
	memcpy( z01->c_reccnt09, cbuf, sizeof( z01->c_reccnt09 ));
	memcpy( z01->c_reccnt10, cbuf, sizeof( z01->c_reccnt10 ));
	memcpy( z01->c_reccnt11, cbuf, sizeof( z01->c_reccnt11 ));
	memcpy( z01->c_reccnt12, cbuf, sizeof( z01->c_reccnt12 ));
	memcpy( z01->c_reccnt13, cbuf, sizeof( z01->c_reccnt13 ));
	memcpy( z01->c_reccnt14, cbuf, sizeof( z01->c_reccnt14 ));
	memcpy( z01->c_reccnt15, cbuf, sizeof( z01->c_reccnt15 ));

	/* ﾊﾟﾗﾒｰﾀ1              */
	memset( z00->c_param1, ' ', sizeof( z00->c_param1 ));
	/* ﾊﾟﾗﾒｰﾀ2              */
	memset( z00->c_param2, ' ', sizeof( z00->c_param2 ));

	// 検査サテライト
	memcpy( z12->c_sateraito, pKnr.sateid, sizeof( z12->c_sateraito ));
		// 要求区分	<-送信ファイル作成時に編集
	
	/* 予備                 */
	memset( z00->c_yobi, ' ', sizeof( z00->c_yobi ));
	memset( z01->c_yobi, ' ', sizeof( z01->c_yobi ));

	/* FILLER               */
	memset( z00->c_filler, ' ', sizeof( z00->c_filler ));
	memset( z01->c_filler, ' ', sizeof( z01->c_filler ));
	memset( z12->c_filler, ' ', sizeof( z12->c_filler ));
	
	/* 改行ｺｰﾄﾞ             */
	memcpy( z00->c_kaigyo, "\n", sizeof( z00->c_kaigyo ));
	memcpy( z01->c_kaigyo, "\n", sizeof( z01->c_kaigyo ));
	memcpy( z12->c_kaigyo, "\n", sizeof( z12->c_kaigyo ));

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  関 数 名  ：WriteRequestFile                                              */
/*  機能概要  ：ＰＮＣ要求カード出力処理                                      */
/*  入    力  ：                                                              */
/*   第１引数 ： FILE	pfp	: 入力ファイル識別子                              */
/*  出    力  ： なし                                                         */
/*  復帰情報  ： INT                                                          */
/*               RTN_OK     : 成功                                            */
/*               RTN_NG     : 失敗                                            */
/******************************************************************************/
int		WriteRequestFile( kbn, z00, z01, z12 )
int		kbn;
struct	Z00SJHD		*z00;
struct	Z01SJTR		*z01;
struct	Z12SJR1		*z12;
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称		*/
	int		ret;							/* 関数戻り値	*/
	int		inp_cnt;
	int		i,j;							/* index		*/
	char	w_ofile[256+1];					// OutPutFile
	char	wbuf[256+1];					// work area
	char	w_modenm[10+1];				// work area

	FILE	*fp;						// 読込ﾌｧｲﾙﾎﾟｲﾝﾀ
	struct	dirent	**namelist;			// get input file
	struct	stat	statbuf;			// get input file status

	/* 初期設定	*/
	strcpy( func_nm,	"WriteRequestFile" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	if( stcPRM.myp_debug == 1 ){
		if( kbn == MYAPP_BUN ){
			strcpy( w_modenm, "分注要求" );
		} else if( kbn == MYAPP_IRI ){
			strcpy( w_modenm, "依頼要求" );
		} else if( kbn == MYAPP_KAN ){
			strcpy( w_modenm, "患者要求" );
		}
	}

	/* ｸﾘｱ	*/
	ret = RTN_OK;
	fp = NULL;

	//===================
	// ファイル作成判断
	//===================

	// 未送信ファイル有無チェック ++++++++++++++++++++++++++++++++++++
	memset( G_otdir,	'\0',	sizeof( G_otdir ));
	memset( G_ext,		'\0',	sizeof( G_ext ));

	switch( kbn ){
	case	MYAPP_BUN :
		strcpy( G_otdir,	stcPRM.ifp_bun_otdir );	
		strcpy( G_ext,		stcPRM.ifp_bun_ext );	
		break;
	case	MYAPP_IRI :
		strcpy( G_otdir,	stcPRM.ifp_iri_otdir );	
		strcpy( G_ext,		stcPRM.ifp_iri_ext );	
		break;
	case	MYAPP_KAN :
		strcpy( G_otdir,	stcPRM.ifp_kan_otdir );	
		strcpy( G_ext,		stcPRM.ifp_kan_ext );	
		break;
	default:
		break;
	}

	inp_cnt = scandir( G_otdir, &namelist, (void*)FileFilter, alphasort);
	if( inp_cnt > 0 ){
			// DEBUG LOG
		sprintf( G_msg, "[%s]未送信ファイルの有->SKIP", w_modenm );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

		// 未送信ファイルが存在するためSKIP
		return( RTN_SKIP );

	} else if( inp_cnt < 0){
			// ERROR LOG
		sprintf( G_err, "%d", errno );
		sprintf( G_msg, "出力ファイルの有無取得(scandir)に失敗しました。" );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		return( RTN_NG );
	} 
	// scandir ファイル名のfree
	free( namelist );

	// END情報判断 +++++++++++++++++++++++++++++++++++++++++++++
		// システム管理情報取得
	if( SelSysknrmst( &pKnr ) != RTN_OK ){
		sprintf( G_msg, "基準処理年月日の取得に失敗しました。" );
		LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		return( RTN_NG );
	}
		// 分注
	if(( kbn == MYAPP_BUN )&&( pKnr.bchendflg[0] == '1' )){
			// DEBUG LOG
		sprintf( G_msg, "[%s]END情報受信済み", w_modenm );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

		return( RTN_SKIP );
	}
		// 依頼	( 患者はEND情報出力後回数で判断）
	if(( kbn == MYAPP_IRI )&&( pKnr.iriendflg[0] == '1' )){
			// DEBUG LOG
		sprintf( G_msg, "[%s]END情報受信済み", w_modenm );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

		return( RTN_SKIP );
	}

	//===================
	// ファイル作成準備
	//===================
	// 通番UPDATE
	// Sysknrmst.ssntub UPDATE & COMMIT
	if(( pKnr.ssntubn = UpdSysknrmstSsntubn( )) < 0 ){
		return( RTN_NG );
	}

	//------------------
	// OUTPUT FILE OPEN
	//------------------
		// ファイル名作成
		//	PREFIX + 基準処理年月日 + 通番 + 時分.拡張子
	memset( w_ofile,	'\0',	sizeof( w_ofile ));
	sprintf( w_ofile, "%s/%s%.8s%04d%.2s%.2s.%s"
		, G_otdir, stcPRM.ifp_fprefix, z00->c_opedate, pKnr.ssntubn
		, &pKnr.ksndh[11], &pKnr.ksndh[14], G_ext );

		// OUTPUT FILE OPEN
	if(( fp = fopen( w_ofile, "w" )) == NULL ){
		// ERROR
		sprintf( G_err, "%d", errno );
		sprintf( G_msg, "[%s]ファイルオープンに失敗しました。", w_ofile );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		return( RTN_NG );
	}

	//------------------
	// EDIT
	//------------------
		// 通番
	memset( wbuf,	'\0',	sizeof( wbuf ));
	sprintf( wbuf, "%0*d",	sizeof( z00->c_tuban ), pKnr.ssntubn );
	memcpy( z00->c_tuban,	wbuf,	sizeof( z00->c_tuban ));
	memcpy( z01->c_tuban,	wbuf,	sizeof( z01->c_tuban ));
	
	switch( kbn ){
	case	MYAPP_BUN :
		memcpy( z00->c_dflow,	stcPRM.ifp_bun_dflow,	
								strlen( stcPRM.ifp_bun_dflow ));
		memcpy( z01->c_dflow,	stcPRM.ifp_bun_dflow,
								strlen( stcPRM.ifp_bun_dflow ));
		memcpy( z12->c_yokyu_kbn,
			stcPRM.ifp_bun_ykkbn,	sizeof( z12->c_yokyu_kbn ));
		break;
	case	MYAPP_IRI :
		memcpy( z00->c_dflow,	stcPRM.ifp_iri_dflow,
								strlen( stcPRM.ifp_iri_dflow ));
		memcpy( z01->c_dflow,	stcPRM.ifp_iri_dflow,
								strlen( stcPRM.ifp_iri_dflow ));
		memcpy( z12->c_yokyu_kbn,
			stcPRM.ifp_iri_ykkbn,	sizeof( z12->c_yokyu_kbn ));
		break;
	case	MYAPP_KAN :
		memcpy( z00->c_dflow,	stcPRM.ifp_kan_dflow,
								strlen( stcPRM.ifp_kan_dflow ));
		memcpy( z01->c_dflow,	stcPRM.ifp_kan_dflow,
								strlen( stcPRM.ifp_kan_dflow ));
		memcpy( z12->c_yokyu_kbn,
			stcPRM.ifp_kan_ykkbn,	sizeof( z12->c_yokyu_kbn ));
		break;
	default:
		break;
	}

		// HD
	if( fwrite( z00, sizeof( struct Z00SJHD ), 1, fp ) < 1 ){
			// ERROR LOG
		sprintf( G_err, "%d", errno );
		sprintf( G_msg,"[%s]ファイル出力に失敗しました。[%s]",w_modenm,w_ofile);
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		fclose( fp );
		if( stat( w_ofile, &statbuf ) == 0 ){
			unlink( w_ofile );
		}
		return( RTN_NG );
	}

		// R1
	if( fwrite( z12, sizeof( struct Z12SJR1 ), 1, fp ) < 1 ){
			// ERROR LOG
		sprintf( G_err, "%d", errno );
		sprintf( G_msg,"[%s]ファイル出力に失敗しました。[%s]",w_modenm,w_ofile);
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		fclose( fp );
		if( stat( w_ofile, &statbuf ) == 0 ){
			unlink( w_ofile );
		}
		return( RTN_NG );
	}

		// TR
	if( fwrite( z01, sizeof( struct Z01SJTR ), 1, fp ) < 1 ){
			// ERROR LOG
		sprintf( G_err, "%d", errno );
		sprintf( G_msg,"[%s]ファイル出力に失敗しました。[%s]",w_modenm,w_ofile);
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		fclose( fp );
		if( stat( w_ofile, &statbuf ) == 0 ){
			unlink( w_ofile );
		}
		return( RTN_NG );
	}

	//------------------
	// OUTPUT FILE CLOSE
	//------------------
	fclose( fp );

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
	char	wbuf[25];
	struct	stat	statbuf;				// get input file status

	strcpy( func_nm, "FileFilter" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	// ディレクトリは除く
	sprintf( w_fnm, "%s/%s", G_otdir, namelist->d_name );
	stat( w_fnm, &statbuf );
	if( S_ISDIR( statbuf.st_mode )){
		// DEBUG
		sprintf( G_msg, "DIR SKIP mode: 0%o [%s]" ,statbuf.st_mode, w_fnm );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
		// 対象外
		return( 0 );
	}
	// 対象ファイルの先頭 AND 拡張子による判断
	if( memcmp( namelist->d_name, stcPRM.ifp_fprefix 
					, strlen( stcPRM.ifp_fprefix )) == 0 ){
		memset( wbuf,	'\0',	sizeof( wbuf ));
		sprintf( wbuf, ".%s", G_ext );
		if( memcmp( strrchr( namelist->d_name, '.' ) , wbuf
						, strlen( G_ext ) + 1 ) == 0 ){
			// DEBUG
			sprintf( G_msg, "処理対象 mode: 0%o [%s]" ,statbuf.st_mode, w_fnm );
			LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// OK
			return ( 1 );
		}
	}

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return ( 0 );
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
