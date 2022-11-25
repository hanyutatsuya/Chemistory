/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：main.c
 *     機能概要  ：自動校正判定処理
 **********************************************************************/

/**********************************************************************/
/*  Ver.     Date           Name           History                    */
/* -------------------------------------------------------------------*/
/*  1.00     2007-04-05                    Create                     */
/* -------------------------------------------------------------------*/
/*  Ver.     Date           Name           History                    */
/* -------------------------------------------------------------------*/
/*  2.00     2008-10-09     K.Ameno        自動校正                   */
/*  2.01     2009-03-04     R.Mizu         判定結果が正しく入らないことへの対応 */
/**********************************************************************/

/********************************************************************/
/*  インクルード宣言                                                */
/********************************************************************/
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <time.h>
#include "bml_base.h"
#include "bmllog.h"
#include "FD103.h"

/* 終了制御フラグ */
int     EndFlg = 0;

/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/
char        G_err[MYAPP_LEN_ERR+1];     /* LogMessage(errcode) */
char        G_msg[MYAPP_LEN_MSG+1];     /* LogMessage */

/*:KH-------------------------------------------------------------------------*/
/*:K  関数名   : EnvRef                                                       */
/*----------------------------------------------------------------------------*/
/*:A  機能概要 : ＄環境変数を展開する                                         */
/*----------------------------------------------------------------------------*/
/*:I  入力     : char    *src_cp  : 展開前文字列                              */
/*:O  出力     : 無し             : 無し                                      */
/*:R  戻り値   : char *           : 展開後文字列                              */
/*:C  特記事項 :                                                              */
/*----------------------------------------------------------------------------*/
char    *EnvRef( src_cp )
char        *src_cp;
{
	char	func_nm[MYAPP_LEN_FNCNM+1]; /* 関数名称 */
static char value[256];                 /* 展開後文字列 */
    char    *dst_cp;                    /* 展開後文字列 */
    char    buf[256];                   /* ＄環境変数 */
    char    *env_cp;                    /* ＄環境変数 */

    strcpy( func_nm, "EnvRef" );
    LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

    dst_cp = value;
    while( *src_cp != 0 ) {
        if( *src_cp == '$' ) {
            env_cp = buf;
            *env_cp++ = *src_cp++;
            while( *src_cp != 0
                && *src_cp != ' ' && *src_cp != '\t'
                && *src_cp != '$' && *src_cp != '/' && *src_cp != '\\' ) {
                *env_cp++ = *src_cp++;
            }
            *env_cp = 0;
            if( (env_cp = getenv( &buf[1] )) == NULL ) {
                env_cp = buf;
            }
            while( *env_cp != 0 ) {
                *dst_cp++ = *env_cp++;
            }
        } else {
            *dst_cp++ = *src_cp++;
        }
    }
    *dst_cp = 0;

    LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
    return( value );
}

/*:KH-------------------------------------------------------------------------*/
/*:K  関数名   : GetIniFile                                                   */
/*----------------------------------------------------------------------------*/
/*:A  機能概要 : 設定ファイルから値を取得する                                 */
/*----------------------------------------------------------------------------*/
/*:I  入力     : char    *section : セクション名                              */
/*             : char    *key     : キー名                                    */
/*             : char    *profile : 設定ファイル名                            */
/*:O  出力     : 無し             : 無し                                      */
/*:R  戻り値   : char *           : キー値（文字列）                          */
/*:C  特記事項 :                                                              */
/*----------------------------------------------------------------------------*/
char    *GetIniFile( section, key, profile )
char        *section;
char        *key;
char        *profile;
{
char        func_nm[MYAPP_LEN_FNCNM+1];     /* 関数名称 */
static char value[256];                     /* 環境変数値 */
    FILE    *fp;                            /* FILEポインタ */
    char    buf[256];                       /* 読込みバッファ */
    int     sec_len;                        /* セクション名長 */
    int     key_len;                        /* キー名長 */
    int     value_len;                      /* キー値長 */
    int     i;                              /* 添え字 */

    strcpy( func_nm, "GetIniFile" );
    LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

    /*==========================*/
    /*  設定ファイルのオープン  */
    /*==========================*/

    if(( fp = fopen( EnvRef( profile ), "rt" )) == NULL ) {
    	LogOut( LT_END, LX_NON, LE_NON, "FOPEN ERROR", func_nm, __FILE__, __LINE__ );
        printf( "FOPEN ERROR:%s\n", profile );
        return( NULL );
    }

    /*==================*/
    /*  セクション検索  */
    /*==================*/
    sec_len = strlen( section );
    key_len = 0;
    buf[sizeof( buf ) - 1] = 0;
    while( fgets( buf, sizeof( buf ) - 1, fp ) != NULL ) {
        for( i = 0; i < sizeof( buf ); i++ ) {
            if( buf[i] != ' ' && buf[i] != '\t' ) break;
        }
        if( buf[i] == '[' ) {
            for( i++; i < sizeof( buf ); i++ ) {
                if( buf[i] != ' ' && buf[i] != '\t' ) break;
            }
            if( strncmp( &buf[i], section, sec_len ) == 0 ) {
                for( i += sec_len; i < sizeof( buf ); i++ ) {
                    if( buf[i] != ' ' && buf[i] != '\t' ) break;
                }
                if( buf[i] == ']' ) {
                    /*================*/
                    /* 見つかった場合 */
                    /*================*/
                    key_len = strlen( key );
                    break;
                }
            }
        }
    }
    /*======================*/
    /* 見つからなかった場合 */
    /*======================*/
    if( key_len <= 0 ) {
    	LogOut( LT_END, LX_NON, LE_NON, "NO FILE", func_nm, __FILE__, __LINE__ );
        fclose( fp );
        return( NULL );
    }

    /*============*/
    /*  キー検索  */
    /*============*/
    while( fgets( buf, sizeof( buf ) - 1, fp ) != NULL ) {
        for( i = 0; i < sizeof( buf ); i++ ) {
            if( buf[i] != ' ' && buf[i] != '\t' ) break;
        }
        if( buf[i] == '[' ) break;
        if( strncmp( &buf[i], key, key_len ) == 0 ) {
            for( i += key_len; i < sizeof( buf ); i++ ) {
                if( buf[i] != ' ' && buf[i] != '\t' ) break;
            }
            if( buf[i] == '=' ) {
                /*================*/
                /* 見つかった場合 */
                /*================*/
                for( i++; i < sizeof( buf ); i++ ) {
                    if( buf[i] != ' ' && buf[i] != '\t' ) break;
                }
                strcpy( value, &buf[i] );
                value_len = strlen( value );
                if( value[value_len - 1] == '\n' ) {
                    value[value_len - 1] = 0;
                }
                fclose( fp );
    			LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
                return( EnvRef( value ) );
            }
        }
    }
    /*======================*/
    /* 見つからなかった場合 */
    /*======================*/
    fclose( fp );

    LogOut( LT_END, LX_NON, LE_NON, "NO FILE", func_nm, __FILE__, __LINE__ );
    return( NULL );
}

/******************************************************************************/
/*  関 数 名  ：Log_out                                                       */
/*  機能概要  ：ログファイル出力                                              */
/*  入    力  ：                                                              */
/*   第１引数 ： char   file_nm[]   : 入力ファイルポインタ                    */
/*  出    力  ： char   rbuf[];     : 読み込みバッファ                        */
/*  復帰情報  ： 0以上              : 正常終了(読込サイズ)                    */
/*               EOF                : FILE END                                */
/*               以外               : 失敗                                    */
/******************************************************************************/
int     LogOut( sbt, flg, ecd, msg, fncnm, file, line )
char        sbt[];
char        flg[];
char        ecd[];
char        msg[];
char        fncnm[] ;
char        file[] ;
long        line ;
{
        int     ret=RTN_OK;
static  int     init_flg = 0;               /* ｲﾆｼｬﾙﾌﾗｸﾞ    */
static  struct  stcLogMember    gstLogMem ; /* ログ出力情報 */

/*------ 1 ----------------------------------------------------------*/
    if( init_flg == 0 ){
        /* ログ情報初期設定 */
        memset ( &gstLogMem, '\0', sizeof ( gstLogMem ) ) ;
        strcpy ( gstLogMem.pcAppName,   stcPRM.myp_exefile ) ;
        strcpy ( gstLogMem.pcLoginId,   "DAEMON" ) ;
        init_flg = 1;
    }
/*------ 1 ----------------------------------------------------------*/
    /* トレース種別 */
    gstLogMem.eTrcKind=sbt[0];
    /* 実行フラグ */
    strcpy ( gstLogMem.pcExeFlg,    flg ) ;
    /* エラーコード */
    strcpy ( gstLogMem.pcErrCode,   ecd ) ;
    /* メッセージ */
    strcpy ( gstLogMem.pcMsg,       msg );
    /* 関数名 */
    strcpy ( gstLogMem.pcFncName,   fncnm ) ;

    if(( strcmp( sbt, LT_STA )) == 0 ){
        gstLogMem.eTrcKind='T';
        strcpy( gstLogMem.pcMsg, "start" );
    } else if( strcmp( sbt, LT_END ) == 0 ){
        gstLogMem.eTrcKind='T';
        strcpy( gstLogMem.pcMsg, "end " );
    }

    /* LOGOUT */
    ret = _ZbmlPutLog( &gstLogMem,  file, line );

    /* inifile debug DEBUG */
    if( stcPRM.myp_debug == 1 ){
        if( strcmp( ecd, LE_NON ) == 0 ){
            printf( "sbt[%.1s] pcFncName[%s] pcMsg : %s\n"
                ,sbt,gstLogMem.pcFncName, gstLogMem.pcMsg );
        } else {
            printf( "sbt[%.1s] pcFncName[%s] pcErrCode[%s] pcMsg : %s\n"
                ,sbt,gstLogMem.pcFncName,gstLogMem.pcErrCode,gstLogMem.pcMsg);
        }
    }

    return( RTN_OK );
}

/******************************************************************************/
/*  関 数 名　：sFncShmCrt()                                                  */
/*  機能概要　：共有メモリ生成                                                */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct stcShm *     共有メモリ構造体                          */
/*  出　　力　：                                                              */
/*  復帰情報　：int                                                           */
/*                   0  正常                                                  */
/*                  -1  異常                                                  */
/******************************************************************************/
int     sFncShmCrt ( stcShm )
struct      SHM     *stcShm;
{
	char	func_nm[MYAPP_LEN_FNCNM+1]; /* 関数名称 */
    int     *shmData ;

    /*トレースログ出力 */
    strcpy( func_nm, "sFncShmCrt" );
    LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

    /*  取得 */
    stcShm->shm_Id = shmget ( (key_t)stcShm->shm_Key,
                    MYAPP_SHM_SIZE, 0666 | IPC_CREAT ) ;
    if ( stcShm->shm_Id < 0 ) {
        /*  異常終了    LOG */
    	LogOut( LT_ERR, LX_NON, LE_NON, "共有メモリの取得(shmget)に失敗しました。",
				func_nm, __FILE__, __LINE__ );
        return ( RTN_NG ) ;
    }

    /*  アタッチ */
    shmData = ( int * ) shmat ( stcShm->shm_Id, 0 , 0 ) ;
    if ( shmData == ( int * )-1 ) {
        /*  異常終了    LOG */
   		LogOut( LT_ERR, LX_NON, LE_NON, "共有メモリのアタッチ(shmat)に失敗しました。",
				func_nm, __FILE__, __LINE__ );
        return ( RTN_NG ) ;
    }

    /*  値設定 */
    *shmData = 0 ;

    /*  デタッチ */
    if ( shmdt ( shmData ) == -1 ) {
        /*  異常終了    LOG */
    	LogOut( LT_ERR, LX_NON, LE_NON, "共有メモリの値設定(shmdt)に失敗しました。",
				func_nm, __FILE__, __LINE__ );
        return ( RTN_NG ) ;
    }
    LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
    return ( RTN_OK ) ;
}

/******************************************************************************/
/*  関 数 名　：sFncShmGet()                                                  */
/*  機能概要　：共有メモリ取得                                                */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct stcShm *     共有メモリ構造体                          */
/*　 第２引数 ：int *                   値                                    */
/*  出　　力　：                                                              */
/*  復帰情報　：int                                                           */
/*                   0  正常                                                  */
/*                  -1  異常                                                  */
/******************************************************************************/
int     sFncShmGet ( stcShm, pshmData )
struct      SHM     *stcShm;
int         *pshmData ;
{
	char	func_nm[MYAPP_LEN_FNCNM+1]; /* 関数名称 */
    int     *shmData ;

    /* トレースログ出力 */
    strcpy( func_nm, "sFncShmGet" );
    LogOut( LT_DBG, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

    /* アタッチ */
//printf("ATTACH : %d\n",stcShm->shm_Id);
    shmData = ( int * ) shmat ( stcShm->shm_Id, 0 , 0 ) ;
    if ( shmData == ( int * )-1 ) {
        /* 異常終了    LOG */
    	LogOut( LT_ERR, LX_NON, LE_NON, "共有メモリの操作(shmget)に失敗しました。",
				func_nm, __FILE__, __LINE__ );
        return ( RTN_NG ) ;
    }

    /* 値設定 */
    *pshmData = *shmData ;

    /* デタッチ */
    if ( shmdt ( shmData ) == -1 ) {
        /* 異常終了    LOG */
    	LogOut( LT_ERR, LX_NON, LE_NON, "共有メモリの操作(shmget)に失敗しました。",
				func_nm, __FILE__, __LINE__ );
        return ( RTN_NG ) ;
    }
    LogOut( LT_DBG, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
    return ( RTN_OK ) ;
}

/******************************************************************************/
/*  関 数 名　：sFncShmDel()                                                  */
/*  機能概要　：共有メモリ削除                                                */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct stcShm *     共有メモリ構造体                          */
/*  出　　力　：                                                              */
/*  復帰情報　：int                                                           */
/*                   0  正常                                                  */
/*                  -1  異常                                                  */
/******************************************************************************/
int     sFncShmDel ( stcShm )
struct      SHM     *stcShm;
{
	char	func_nm[MYAPP_LEN_FNCNM+1]; /* 関数名称 */
    int     *shmData ;

    /* トレースログ出力 */
    strcpy( func_nm, "sFncShmDel" );
    LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

    /* 削除 */
    if ( shmctl ( stcShm->shm_Id, IPC_RMID, NULL) < 0 ) {
        /* 異常終了    LOG */
    	LogOut( LT_ERR, LX_NON, LE_NON, "共有メモリの操作(shmdel)に失敗しました。",
				func_nm, __FILE__, __LINE__ );
        return ( RTN_NG ) ;
    }
    LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
    return ( RTN_OK ) ;
}
/******************************************************************************/
/*  関 数 名  ：DaemonCheckProc                                               */
/*  機能概要  ：デーモン重複起動チェック                                      */
/*  入    力  ：                                                              */
/*   第１引数 ：int     argc    : パラメタ数                                  */
/*   第２引数 ：char    *argv[] : パラメタリスト                              */
/*   第３引数 ：PENV    *pEnv   : 環境変数域                                  */
/*  出    力  ：なし                                                          */
/*  復帰情報  ： INT                                                          */
/*               RTN_OK     : 成功                                            */
/*               RTN_NG     : 失敗                                            */
/******************************************************************************/
int     DaemonCheckProc( argc, argv, pEnv )
int         argc;
char        *argv[];
PENV		pEnv;
{
    int     ret = RTN_OK;           /* 復帰値 */
    int     cnt;                    /* カウント */
    char    func_nm[MYAPP_LEN_FNCNM+1];         /* 関数名称  */
    char    buf[128];               /* 読込みバッファ */
    char    cmd[128];               /* コマンド */
    char    tmp[80];                /* 作業ファイル */
    FILE    *tfp;                   /* FILEポインタ */

    strcpy( func_nm, "DaemonCheckProc" );
    LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

    /* コマンド実行 */
    sprintf( tmp, "/tmp/%s.%d.tmp", stcPRM.myp_exefile, getpid() );
    sprintf( cmd, "ps -e | grep %s | grep -v grep | wc > ", pEnv->stLogMem.pcAppName);
    strcat( cmd, tmp );
    system( cmd );

    /* TRACE */
    sprintf( G_msg, "重複起動チェックでコマンド[%s]を実行", cmd );
    LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    /* 起動数の読込み */
    if( (tfp = fopen( tmp, "r" )) == NULL ) {
        /* ERROR */
        sprintf( G_msg,"重複起動チェックコマンド結果ファイル オープンエラー", tmp );
        LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

        return  RTN_NG;
    }
    if( fgets( buf, sizeof( buf ), tfp ) == NULL ) {
        strcpy( buf, "0");
        /* ERROR */
        sprintf( G_msg,"重複起動チェックで実行したコマンド結果を取得できない" );
        LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
    }
    fclose( tfp );
    unlink( tmp );

    /* 起動数チェック */
    cnt = 0;
    sscanf( buf, "%d", &cnt );

    /* TRACE */
    sprintf( G_msg, "重複起動チェックで%s"
        , (cnt>1)?"重複している" :"重複していない" );
    LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    if( cnt > 1 ) {
        return( RTN_NG );
    }
    LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
    return RTN_OK;
}
/**********************************************************************/
/*                                                                    */
/*   function name : sigcatch                                         */
/*                                                                    */
/*   purpose : シグナル取得処理                                       */
/*                                                                    */
/*   data : 2006.01.26                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
void sigcatch(int sig)
{
  fprintf(stdout,"catch signal %d\n",sig);
  EndFlg = 1;
  /* シグナルハンドラをデフォルトに戻す */
  signal(sig,SIG_DFL);
}

/********************************************************************/
/*  関数名      ：main()                                            */
/*  機能概要    ：自動校正処理メイン                                */
/*  入力        ：                                                  */
/*   第１引数   ：int       argc    パラメータ数                    */
/*   第２引数   ：char**    argv    パラメータ値                    */
/*  出力        ：                                                  */
/*   正常：0                                                        */
/*   異常：1以上                                                    */
/********************************************************************/
int main(int argc, char** argv)
{
	char	func_nm[MYAPP_LEN_FNCNM+1]; /* 関数名称 */
    /*
    *   ローカル変数定義
    */
    ENV     Env;
    int     rc;

    /***
     ***    バックグラウンド実行
     ***/
    if (daemon(1, 1) < 0) {
        exit (9);
    }

    /* man 7 signal で確認 */
    if(SIG_ERR == signal(SIGINT,sigcatch)){
        fprintf(stderr,"failed to set signalhandler.\n");
        exit(1);
    }

    /*
    *   初期化処理
    */
    rc = initFunction(argc, argv, &Env);
    if(rc != ERROR_CODE_NORMAL)
    {
        fprintf(stderr, "jidokousei : Error InitFunction [%d]\n", rc);
        return(rc);
    }

    memcpy( &stEnv, &Env, sizeof( ENV ));

    /*
	 *   メイン処理
	 */
	rc = mainFunction(&Env);
	if(rc != ERROR_CODE_NORMAL)
	{
	    /* データベース切断 */
	    ZdbDisConnect();
	    fprintf(stderr, "jidokousei : Error mainFunction [%d]\n", rc);
	    return(rc);
	}

    /*
    *   終了処理
    */
    rc = endFunction(&Env);
    if(rc != ERROR_CODE_NORMAL)
    {
        fprintf(stderr, "jidokousei : Error endFunction [%d]\n", rc);
        return(rc);
    }

    return(ERROR_CODE_NORMAL);
}

/********************************************************************/
/*  関数名      ：keyComp                                           */
/*  機能概要    ：キー部比較                                        */
/*  入力        ：                                                  */
/*   第１引数   ：KTLIST*   a       比較元校正対象リスト            */
/*   第２引数   ：KTLIST*   b       比較先校正対象リスト            */
/*  出力        ：                                                  */
/*   同一  ：0                                                      */
/*   異なる：0以外                                                  */
/********************************************************************/
int keyComp(KTLIST* a, KTLIST* b)
{
	/* 32 : knskisymd + bskkbn + bsklne + bskgok + ctrlno */
	return memcmp(a, b, 32);
}

/********************************************************************/
/*  関数名      ：channelComp                                       */
/*  機能概要    ：キー部比較（内部項目コード含む）                  */
/*  入力        ：                                                  */
/*   第１引数   ：KTLIST*   a       比較元校正対象リスト            */
/*   第２引数   ：KTLIST*   b       比較先校正対象リスト            */
/*  出力        ：                                                  */
/*   同一  ：0                                                      */
/*   異なる：0以外                                                  */
/********************************************************************/
int channelComp(KTLIST* a, KTLIST* b)
{
	/* 40 : knskisymd + bskkbn + bsklne + bskgok + ctrlno + nbkmkcd */
	return memcmp(a, b, 40);
}

/********************************************************************/
/*  関数名      ：SetControlNG                                      */
/*  機能概要    ：コントロール丸ごとNG設定                          */
/*  入力        ：                                                  */
/*   第１引数   ：KTLIST*   kt      校正対象リスト                  */
/*   第２引数   ：int       ng      エラー発生位置（校正対象リスト）*/
/*   第３引数   ：ATKSTS*   at      エラー情報                      */
/*   第４引数   ：int       kensu   校正対象リスト件数              */
/*  出力        ：                                                  */
/*   次のコントロールの先頭位置                                     */
/********************************************************************/
int SetControlNG(KTLIST* kt, int ng, ATKSTS* at, int kensu)
{
	char	func_nm[MYAPP_LEN_FNCNM+1]; /* 関数名称 */
	int     top  = 0;
	int     next = 0;
	int     j;

    /*トレースログ出力 */
    strcpy( func_nm, "SetControlNG" );
    LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* コントロール範囲取得 */
	top  = SearchTopControlPosition(kt, ng, 1);
	next = SearchNextControlPosition(kt, ng, kensu, 1);

	/* 既に登録されている校正対象データについては、事由コードを設定し対象外とする */
	UpdateATKSTS(at);

	/* コントロール全体をNGに設定 */
	for (j = top; j < next; j++) {
		ATKSTS wk;
		/* 書き込み用データ作成 */
		ConvKTLIST2ATKSTS(kt+j, &wk);
		/* エラー情報は全てエラーが発生したチャネルの内容を引継ぐ */
		strcpy(wk.autokosiflg, at->autokosiflg);
		strcpy(wk.causecd, at->causecd);

		InsertATKSTS(&wk);
	}

    LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return next;
}

/********************************************************************/
/*  関数名      ：checkJidoKousei                                   */
/*  機能概要    ：自動校正判定処理                                  */
/*  入力        ：なし                                              */
/*  出力        ：なし                                              */
/********************************************************************/
void checkJidoKousei()
{
	char	func_nm[MYAPP_LEN_FNCNM+1]; /* 関数名称 */
	KTLIST* kt;							/* 校正対象リスト */
	KTLIST  oldKt;						/* 校正対象リスト・コントロール確認用 */
	ATKSTS  at;							/* 自動校正対象コントロールテーブルイメージ */
	int		histCnt;					/* ヒスト階級数 */
	int*	histBefore;					/* ヒストグラム(補正前） */
	int*	histAfter;					/* ヒストグラム(補正後） */
	int		kensu;						/* 校正対象リスト件数 */
	int		ret;						/* 関数戻り値 */
	int		i;							/* ループカウンタ */
	int		j;							/* ループカウンタ */
	int		prev;						/* 前コントロール位置 */
	int		next;						/* 次コントロール位置 */
	int		top;						/* コントロール先頭位置 */

    /*トレースログ出力 */
    strcpy( func_nm, "checkJidoKousei" );
    LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	kt    = NULL;
	kensu = 0;
	top   = 0;
	
	/* 校正対象リスト取得 */
	ret = selectKouseiTaisho(&kt, &kensu);
	/* エラーの場合件数を0とする */
	if (ret != RTN_OK) {
		kensu = 0;
	} else {
		oldKt = *kt;
	}

	/* 件数分ループする(チャネル単位でカウントアップ) */
	for (i = 0; i < kensu; i = SearchNextControlPosition(kt, i, kensu, 0)) {
		memset(&at, 0, sizeof(ATKSTS));
		ConvKTLIST2ATKSTS(kt+i, &at);

		/* ＤＢ確定・キー（分析機・コントロールＮＯ）が変わったら確定（COMMIT） */
		if (keyComp(kt+i, &oldKt) != 0)
			Commit();

		/* コントロール精度異常情報設定 */
		if (SetCtrlERROR(kt+i, &at) != KSTS_OK) {
			sprintf(G_msg, "コントロール精度異常（bskgok[%s], nbkmkcd[%s], ctrlno[%d])",
					(kt+i)->bskgok,(kt+i)->nbkmkcd,(kt+i)->ctrlno);
    		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

			/* 自動校正対象コントロールテーブルに登録                  */
			/* ※ SetCtrlERRORで以下のように更新                       */
			/*    ・autokosiflg(自動校正対象フラグ) = '0' (校正対象外) */
			/*    ・causecd(校正対象外事由コード)   = KSTS_CTRLNO (2)  */
			InsertATKSTS(&at);
			continue;
		}

		/* 最終データでなく、キー内の最終データでも無い場合は */
		/* コントロール本数異常情報を設定する */
		if (i < (kensu-1) && keyComp(kt+i, kt+i+1) == 0) {
			if (SetNoneCount(kt+i, &at) != KSTS_OK) {
				sprintf(G_msg, "コントロール本数異常（bskgok[%s], nbkmkcd[%s], ctrlno[%d]）",
					(kt+i)->bskgok,(kt+i)->nbkmkcd,(kt+i)->ctrlno);
    			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

				/* 自動校正対象コントロールテーブルに登録                   */
				/* ※ SetNoneCountで以下のように更新                        */
				/*    ・autokosiflg(自動校正対象フラグ) = '0' (校正対象外)  */
				/*    ・causecd(校正対象外事由コード)   = KSTS_CTRLNONE (3) */
				InsertATKSTS(&at);
				continue;
			}
		}

		/* 前コントロールがある時だけ校正可否判定対象とする */
		if ((prev = SearchPrevControlPosition(kt, i, 0)) < 0) {
			/* 自動校正対象コントロール情報の最終コントロールがこれに該当する事が多く、 */
			/* うるさいのでここを止めておく */
    		/*LogOut( LT_WRN, LX_NON, LE_NON, "前コントロール無し", func_nm, __FILE__, __LINE__ ); */
			continue;
		}

		/* 校正可否判定 */
		ret = KoseiKaHi(kt, i, prev, &at, &next, kensu);

		/* 校正可否がNGだった場合、コントロール全体をNGとする */
		if (ret != RH_KOUSEI) {

            /* エラーか正常の場合に処理（正常は校正対象外とするため） */
			if (ret == RH_SAIKEN) {
				/* 2009.2.3 Nagata start */
				/* 自動校正対象コントロールテーブルに登録                   */
				/* ※ 再測定の必要がある場合、以下のように更新                        */
				/*    ・autokosiflg(自動校正対象フラグ) = '0'  */
				/*    ・causecd(校正対象外事由コード)   = KSTS_SAISOKU (12) */
		        strcpy(at.autokosiflg, "0");
        		sprintf(at.causecd, "%d", KSTS_SAISOKU);
				InsertATKSTS(&at);
			}
			else{
				if (ret == RH_NORMAL) {
					sprintf(G_msg, "校正可否・正常（校正対象外）（bskgok[%s], nbkmkcd[%s], ctrlno[%d]）",
						(kt+i)->bskgok,(kt+i)->nbkmkcd,(kt+i)->ctrlno);
    				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
					/* 2009-03-04 Mizu ADD Start --- 判定結果が正しく入らないことへの対応 */
					InsertATKSTS(&at);
					/* 2009-03-04 Mizu ADD End */
				} else {
					sprintf(G_msg, "校正可否・エラー（校正対象外）（bskgok[%s], nbkmkcd[%s], ctrlno[%d]）",
						(kt+i)->bskgok,(kt+i)->nbkmkcd,(kt+i)->ctrlno);
    				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
					/* 2009-03-04 Mizu ADD Start --- 判定結果が正しく入らないことへの対応 */
					InsertATKSTS(&at);
					/* 2009-03-04 Mizu ADD End */
				}
				
				/* 2009-03-04 Mizu DEL Start --- 判定結果が正しく入らないことへの対応 */
				/* next = SetControlNG(kt, i, &at, kensu); */

				/*  ループカウンタをコントロールブロックの終端に設定 */
				/*  後続する同一コントロールデータをスキップ */
				/* i = next - 1; */
				/* 2009-03-04 Mizu DEL End */
			}
			continue;
		
		}

		/* ヒストグラム作成（校正前・校正後） */
		{
			int total = 0;
			int count;

			/* 校正前 */
			ret = MakeHistgramBefore(kt+i, kt+prev, &histBefore);
			if (ret != RTN_OK) {
				sprintf(G_msg, "校正前ヒストグラム作成不可（bskgok[%s], nbkmkcd[%s], ctrlno[%d]）",
					(kt+i)->bskgok,(kt+i)->nbkmkcd,(kt+i)->ctrlno);
    			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

				/* ヒストが作れない場合は、コントロール全体をスキップ */
				next = SearchNextControlPosition(kt, i, kensu, 1);
				i = next - 1;
				continue;
			}

			/* 校正後 */
			ret = MakeHistgramAfter(kt+i, kt+prev, &histAfter, at.facter, at.base);
			if (ret != RTN_OK) {
				sprintf(G_msg, "校正後ヒストグラム作成不可（bskgok[%s], nbkmkcd[%s], ctrlno[%d]）",
					(kt+i)->bskgok,(kt+i)->nbkmkcd,(kt+i)->ctrlno);
    			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

				/* ヒストが作れない場合は、コントロール全体をスキップ */
				next = SearchNextControlPosition(kt, i, kensu, 1);
				i = next - 1;
				continue;
			}

			/* サンプル数チェック */
			for (count = 0; count < (kt+i)->hstkaikyu; count++) {
				total += histBefore[count];
			}
			if (total < (kt+i)->ksikjnspsu) {
				sprintf(G_msg, "サンプル数未達（bskgok[%s], nbkmkcd[%s], ctrlno[%d], ksikjnspsu[%d]）：total[%d]",
					(kt+i)->bskgok,(kt+i)->nbkmkcd,(kt+i)->ctrlno,(kt+i)->ksikjnspsu, total);
    			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

				/* 2009.2.3 Nagata start */
				/* 自動校正対象コントロールテーブルに登録                   */
				/* ※ SetNoneCountで以下のように更新                        */
				/*    ・autokosiflg(自動校正対象フラグ) = '0' (サンプル数未達)  */
				/*    ・causecd(校正対象外事由コード)   = KSTS_COUNT (11) */
		        strcpy(at.autokosiflg, "0");
        		sprintf(at.causecd, "%d", KSTS_COUNT);

				InsertATKSTS(&at);

				/* サンプル数が足りない場合は、コントロール全体をスキップ */
				/* next = SearchNextControlPosition(kt, i, kensu, 1);
				i = next - 1; */
				/* 2009.2.3 Nagata end */

				/* ヒストグラム領域開放 */
				if (histBefore != NULL) {
					free(histBefore);
					histBefore = NULL;
				}

				continue;
			}
		}

#	ifndef DEBUG_DET
		{/* DEBUG WRITE */
			char tmp[80];
			int l;
			sprintf(tmp, "ヒストグラム bskkbn[%s] bskgok[%s] nbkmkcd[%s] ctrlno[%d]\n",
					(kt+i)->bskkbn, (kt+i)->bskgok, (kt+i)->nbkmkcd, (kt+i)->ctrlno);
			strcpy(G_msg, tmp);
			sprintf(tmp, "校正前 ");
			strcat(G_msg, tmp);
			for (l = 0; l < (kt+i)->hstkaikyu; l++) {
				sprintf(tmp, "%4d ", histBefore[l]);
				strcat(G_msg, tmp);
			}
			sprintf(tmp, "\n");
			strcat(G_msg, tmp);
			sprintf(tmp, "校正後 ");
			strcat(G_msg, tmp);
			for (l = 0; l < (kt+i)->hstkaikyu; l++) {
				sprintf(tmp, "%4d ", histAfter[l]);
				strcat(G_msg, tmp);
			}
			sprintf(tmp, "\n");
			strcat(G_msg, tmp);
			
    		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
		}
#	endif

		/* ヒストグラムチェック */
		{
			/* 二峰性判定（校正前） */
			ret = NihoCheck(kt+i, histBefore);

			if (ret != RTN_OK) { 
				sprintf(G_msg, "二峰性(bskgok[%s], nbkmkcd[%s], ctrlno[%d]) hstkjntn[%f], hstkzmhb[%f]",
					(kt+i)->bskgok, (kt+i)->nbkmkcd, (kt+i)->ctrlno, (kt+i)->hstkjntn, (kt+i)->hstkzmhb);
    			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

				strcpy(at.autokosiflg, "0");
				sprintf(at.causecd, "%d", KSTS_2HOUSEI);

				/* 二峰性データが存在したコントロールは全てＮＧとする */
				/* next = SetControlNG(kt, i, &at, kensu); */
				/* ループカウンタをコントロールブロックの終端に設定 */
				/* 後続する同一コントロールデータをスキップ */
				/* i = next - 1 ;*/
				/* 上記の処理をとりやめて、ニ峰性データが存在したレコードのみＮＧとするように変更 */
				InsertATKSTS(&at);

				/* ヒストグラム領域開放 */
				if (histAfter != NULL) {
					free(histAfter);
					histAfter = NULL;
				}
				if (histBefore != NULL) {
					free(histBefore);
					histBefore = NULL;
				}

				continue;
			}

			/* 最頻判定（校正前・校正後） */
			ret = SaihinCheck(kt+i, histBefore, histAfter);

			if (ret != RTN_OK) {
				sprintf(G_msg, "最頻判定（校正前・校正後）(bskgok[%s], nbkmkcd[%s], ctrlno[%d]) (hstkjntn[%f], hstkzmhb[%f]) shrnglwhf[%f] < data < shrnghihf[%f]",
					(kt+i)->bskgok, (kt+i)->nbkmkcd, (kt+i)->ctrlno, (kt+i)->hstkjntn, (kt+i)->hstkzmhb,
					(kt+i)->shrnglwhf, (kt+i)->shrnghihf);
    			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

				strcpy(at.autokosiflg, "0");
				sprintf(at.causecd, "%d", KSTS_SAIHIN);

				/* 最頻判定エラーが存在したコントロールは全てＮＧとする */
				/* next = SetControlNG(kt, i, &at, kensu); */
				/* ループカウンタをコントロールブロックの終端に設定 */
				/* 後続する同一コントロールデータをスキップ */
				/* i = next - 1; */
				/* 上記の処理をとりやめて、最頻エラーデータが存在したレコードのみＮＧとするように変更 */
				InsertATKSTS(&at);


				/* ヒストグラム領域開放 */
				if (histAfter != NULL) {
					free(histAfter);
					histAfter = NULL;
				}
				if (histBefore != NULL) {
					free(histBefore);
					histBefore = NULL;
				}

				continue;
			}
		}

		/* ヒストグラム領域開放 */
		if (histAfter != NULL) {
			free(histAfter);
			histAfter = NULL;
		}

		if (histBefore != NULL) {
			free(histBefore);
			histBefore = NULL;
		}

		/* 全ての検査がパスしたデータは校正対象として登録 */
		/* autokosiflg(自動校正対象フラグ) = '1' (自動校正対象) */
		/* causecd(校正対象外事由コード)   = KSTS_OK (0)        */
		strcpy(at.autokosiflg, "1");
		sprintf(at.causecd, "%d", KSTS_OK);
		InsertATKSTS(&at);
	}

	if (kt != NULL) {
		free(kt);
		kt = NULL;
	}

    LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
}

/******************************************************************************/
/*  関 数 名  ：sFncSleepEx()                                                 */
/*  機能概要  ：スリープ                                                      */
/*  入    力  ：                                                              */
/*   第１引数 ：       PENV  pEnv    プログラム管理構造体                     */
/*   第２引数 ：struct SHM  *stcShm  共有メモリ管理構造体                     */
/*  出    力  ：                                                              */
/*  復帰情報  ：  0     : 正常                                                */
/*            ：  1     : 停止コマンド受信                                    */
/******************************************************************************/
int sFncSleepEx ( PENV pEnv, struct SHM *stcShm )
{
	int		iStopFlg = 0 ;					/* 終了フラグ */
	time_t	sleepTm ;						/* スリープ時間 */
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称 */
	
	/* スリープする時間取得 */
	sleepTm = time(NULL) + (time_t)pEnv->sleepInterval ;
	
	while( time(NULL) < sleepTm )
	{
		/***                        ***/
		/***    停止コマンド確認    ***/
		/***                        ***/
		if ( sFncShmGet ( stcShm, &iStopFlg ) == 0 ) {
			if ( iStopFlg == 1 ) {
				strcpy( func_nm, "sFncSleepEx" );
				LogOut( LT_OPT, LX_NON, LE_NON, "停止コマンド受信", func_nm, __FILE__, __LINE__ );
				break ;
			}
		}

		/* 1秒スリープ */
		sleep ( 1 );
	}

	return iStopFlg;
}

/********************************************************************/
/*  関数名      ：initFunction()                                    */
/*  機能概要    ：初期化処理                                        */
/*  入力        ：                                                  */
/*   第１引数   ：int       argc    パラメータ数                    */
/*   第２引数   ：char**    argv    パラメータ値                    */
/*   第３引数   ：PENV      pEnv    プログラム管理構造体            */
/*  出力        ：                                                  */
/*   正常：0                                                        */
/*   異常：0以外                                                    */
/********************************************************************/
int initFunction(int argc, char** argv, PENV pEnv)
{
	char	func_nm[MYAPP_LEN_FNCNM+1]; /* 関数名称 */
    /*
    *   ローカル変数定義
    */
    int     rc;
    char    tmp[12];

    /*
    *   初期化
    */

    /*プログラム管理構造体初期化 */
    memset(pEnv, 0, sizeof(ENV));

    /* ログファイルオープン */
    rc = ZbmlOpenLog( EnvRef(LOGINIFILE) );
    if(rc != 0)
    {
        LogOut( LT_ERR, LX_NON, LE_NON, "ログファイルがオープンできませんでした。", func_nm, __FILE__, __LINE__ );
        return(ERROR_CODE_LOG_OPEN_ERROR);
    }

    /* ログ情報初期化設定 */
    memset(&pEnv->stLogMem, '\0', sizeof(pEnv->stLogMem)) ;

    char    *cp;                        /* 対象パラメタ */
    /* 実行プログラム名の設定 */
    for( cp = argv[0], cp += strlen( cp ); cp != argv[0]; --cp ) {
        if( *cp == '/' || *cp == '\\' ) {
            cp++;
            break;
        }
    }
    /* プログラム名セット */
    strcpy(pEnv->stLogMem.pcAppName, cp);

    /* プログラム開始ログ出力 */
    strcpy( func_nm, "initFunction" );
    LogOut( LT_OPT, LX_NON, LE_NON, "プログラム起動", func_nm, __FILE__, __LINE__ );

    /* 2重起動チェック  
    if( DaemonCheckProc(argc, argv, pEnv) != RTN_OK ){
        sprintf( G_msg, "２重起動防止のため、処理を終了します。" );
        LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
        return(ERROR_MULTI_RUN);
    }
    */

    /* コマンドライン引数チェック */
    /* ※第2引数にパラメータファイルのパスが入力されていなければエラー */
    if(argc != 2)
    {
    	LogOut( LT_ERR, LX_NON, LE_NON, "コマンドライン引数が不正です。",
				func_nm, __FILE__, __LINE__ );
        return(ERROR_CODE_CMD_PRM_ERROR);
    }

    /* パラメータファイルオープン */
    pEnv->bp = ZbmlPrmOpen(argv[1]) ;
    if(pEnv->bp == NULL)
    {
    	LogOut( LT_ERR, LX_NON, LE_NON, "パラメータファイルのオープンに失敗しました。",
				func_nm, __FILE__, __LINE__ );
        return(ERROR_CODE_PRM_OPEN_ERROR);
    }

    /*
    *   パラメータ取得
    */

    /* データベース名取得 */
    if(ZbmlPrmGetVal(pEnv->bp, PRM_DB_NAME, pEnv->cDbName) != 0)
    {
		sprintf(G_msg, "パラメータの取得に失敗しました。(%s : %s)", PRM_DB_NAME, pEnv->cDbName);
    	LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
        return(ERROR_CODE_PRM_GET_ERROR);
    }
	sprintf(G_msg, "%s     : %s", PRM_DB_NAME, pEnv->cDbName);
    LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    /* ＤＢユーザＩＤ取得 */
    if(ZbmlPrmGetVal(pEnv->bp, PRM_DB_USER_ID, pEnv->cDbUserId) != 0)
    {
		sprintf(G_msg, "パラメータの取得に失敗しました。(%s : %s)", PRM_DB_USER_ID, pEnv->cDbUserId);
    	LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
        return(ERROR_CODE_PRM_GET_ERROR);
    }
	sprintf(G_msg, "%s  : %s", PRM_DB_USER_ID, pEnv->cDbUserId);
    LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    /*ＤＢパスワード取得 */
    if(ZbmlPrmGetVal(pEnv->bp, PRM_DB_PASSWORD, pEnv->cDbPassword) != 0)
    {
		sprintf(G_msg, "パラメータの取得に失敗しました。(%s : %s)", PRM_DB_PASSWORD, pEnv->cDbPassword);
    	LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
        return(ERROR_CODE_PRM_GET_ERROR);
    }
	sprintf(G_msg, "%s : %s", PRM_DB_PASSWORD, pEnv->cDbPassword);
    LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    /* スリープ(秒)取得 */
    if(ZbmlPrmGetVal(pEnv->bp, PRM_SLEEP_SEC, tmp) != 0)
    {
		sprintf(G_msg, "パラメータの取得に失敗しました。(%s : %s)", PRM_SLEEP_SEC, tmp);
    	LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
        return(ERROR_CODE_PRM_GET_ERROR);
    }
	sprintf(G_msg, "%s   : %s", PRM_SLEEP_SEC, tmp);
    LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
    /* SLEEP_SEC */
    pEnv->sleepInterval = atoi(tmp);

    /* 1.01 SHM_KEY GET */
    if(ZbmlPrmGetVal(pEnv->bp, PRM_SHM_KEY, tmp) != 0)
    {
		sprintf(G_msg, "パラメータの取得に失敗しました。(%s : %s)", PRM_SHM_KEY, tmp);
    	LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
        return(ERROR_CODE_PRM_GET_ERROR);
    }
	sprintf(G_msg, "%s     : %s", PRM_SHM_KEY, tmp);
    LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
    /* SHM_KEY */
    pEnv->shm_Key = atoi(tmp);

    /* パラメータファイルクローズ */
    ZbmlPrmClose(pEnv->bp);

    LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
    return(ERROR_CODE_NORMAL);
}

/********************************************************************/
/*  関数名      ：mainFunction()                                    */
/*  機能概要    ：メイン処理                                        */
/*  入力        ：                                                  */
/*   第１引数   ：PENV      pEnv    プログラム管理構造体            */
/*  出力        ：                                                  */
/*   正常：0                                                        */
/*   異常：0以外                                                    */
/********************************************************************/
int
mainFunction(PENV pEnv)
{
	char	func_nm[MYAPP_LEN_FNCNM+1]; /* 関数名称 */
    /*
    *   ローカル変数定義
    */
    int     rc;
    struct  SHM stcShm;                 /* 1.01 終了判断共有メモリ */
    int     li_stopFlg = 0;             /* 1.01 終了判断 */

    //トレースログ出力
    strcpy( func_nm, "mainFunction" );
    LogOut( LT_OPT, LX_NON, LE_NON, "mainFunction START", func_nm, __FILE__, __LINE__ );

    /*
    *   初期化
    */

    /* 1.01 共有メモリ生成 */
    stcShm.shm_Key = pEnv->shm_Key;
    if( sFncShmCrt ( &stcShm ) < 0 ) {
        char ebuf[10];
        sprintf( ebuf, "共有メモリ生成失敗:shmkey[%d]", errno );
    	LogOut( LT_ERR, LX_NON, LE_NON, ebuf, func_nm, __FILE__, __LINE__ );
        return( ERROR_FUNC_ERROR );
    }

    /*
    *   データベース接続
    */
    rc = ZdbConnect(pEnv->cDbName, pEnv->cDbUserId, pEnv->cDbPassword);
    if(rc != 0)
    {
    	LogOut( LT_ERR, LX_NON, LE_NON, "データベースの接続に失敗しました。",
				func_nm, __FILE__, __LINE__ );

		sFncShmDel ( &stcShm ) ;

        return(ERROR_CODE_DB_CONNECT_ERROR);
    }

    /*
    *   精度管理異常チェック処理
    */
    while(1) {
        /* 終了シグナルをチェック */
        if ( EndFlg ) {
            break;
        }

	    /* 自動校正判定 */
		checkJidoKousei();

        /***
         *** 停止コマンド確認
         ***/
		/* 頻繁に回す必要が無いのでFD103.iniのSLEEP_SECで設定した秒数毎にSLEEPする */
		if ( sFncSleepEx ( pEnv, &stcShm ) != 0 ) {
			break;
		}
	}

    ZdbDisConnect();

    sFncShmDel ( &stcShm ) ;

    LogOut( LT_OPT, LX_NON, LE_NON, "mainFunction END", func_nm, __FILE__, __LINE__ );
    return(ERROR_CODE_NORMAL);
}

/********************************************************************/
/*  関数名      ：endFunction()                                     */
/*  機能概要    ：終了処理                                          */
/*  入力        ：                                                  */
/*   第１引数   ：PENV      pEnv    プログラム管理構造体            */
/*  出力        ：                                                  */
/*   正常：0                                                        */
/*   異常：0以外                                                    */
/********************************************************************/
int endFunction(PENV pEnv)
{
	char	func_nm[MYAPP_LEN_FNCNM+1]; /* 関数名称 */
    /*
    *   ローカル変数定義
    */

    /* トレースログ出力 */
    strcpy( func_nm, "endFunction " );
    LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

    /*
    *   初期化
    */

    LogOut( LT_OPT, LX_NON, LE_NON, "プログラム終了", func_nm, __FILE__, __LINE__ );

    LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

    ZbmlCloseLog( );

    return(ERROR_CODE_NORMAL);
}

/** End of File ***************************************************************/
