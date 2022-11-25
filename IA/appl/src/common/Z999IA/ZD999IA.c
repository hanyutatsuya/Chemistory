/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：BD401.c                                                      */
/* 　概　　　要：サンプラーデーモン 	                                      */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/31     芳賀弘幸       新規作成                           */
/******************************************************************************/

/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <syslog.h>
#include <dirent.h>

#include "bmlprm.h"
#include "ZD999IA.h"

/******************************************************************************/
/* Define宣言       	                                                      */
/******************************************************************************/

/******************************************************************************/
/* 構造体宣言       	                                                      */
/******************************************************************************/

/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/

/******************************************************************************/
/* 関数宣言 		                                                          */
/******************************************************************************/
//	受信処理関連	
static	int		sFncRcevMain ( struct appEnv *, int ) ;
void sFncCOMMAND_EXEC_LABO ( int, struct dataRec * ) ;
void sFncCOMMAND_EXEC_LABO_NYOU ( int, struct dataRec * ) ;
void sFncCOMMAND_EXEC_BM ( int, struct dataRec * ) ;
void sFncCOMMAND_KILL ( int, struct dataRec * ) ;
void sFncCOMMAND_PS ( int ) ;
void sFncCOMMAND_BACK ( ) ;

//  子プロセス処理
static int  sFncChild ( int ) ;

//  子プロセス埋葬
static void sFncWait ( int ) ;


/******************************************************************************/
/*  関 数 名　：initFunction()												  */
/*  機能概要　：初期処理関数												  */
/*  入　　力　：                                                              */
/*　 第１引数 ：int   				メインパラメータ数			 			  */
/*　 第２引数 ：char *   			メインパラメータ			 			  */
/*  出　　力　：                                                              */
/*　 第３引数 ：struct	appEnv *   	プログラム環境構造体		 			  */
/*  復帰情報　： 0		: 成功											  */
/* 　　　　　　　-1		: 失敗											  */
/******************************************************************************/
int
initFunction( argc, argv, pAppEnv )
int					 argc ;
char				*argv[] ;
struct appEnv		*pAppEnv ;
{
	long	 	 ll_retSts ;
	int	 		 li_retSts ;
	BMLPRM		*bp ;
	char	 	 lc_prmBuf[256] ;

	/***
	 ***    引数チェック
	 ***/
	if ( argc != 2 ) {
		fprintf ( stderr, "%s : There is an error in a command parameter\n", MYAPP_APP_NAME ) ;
		return ( -1 ) ;
	}

	/***
	 ***	初期化	
	 ***/
	memset ( pAppEnv , '\0', sizeof ( struct appEnv ) ) ;

	/***
	 ***	パラメータファイル情報退避
	 ***/
	//	パラメータファイルオープン	
	bp = ZbmlPrmOpen ( argv[1] ) ;		
	if ( bp == NULL ) {
		return ( -1 ) ;
	}
	//	ポート	
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_PORT, lc_prmBuf ) != 0 ) {
		return ( -1 ) ;
	}
	pAppEnv->Port = atoi ( lc_prmBuf ) ;
	//	タイムアウト時間取得
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_TIMEOUT_SEC, lc_prmBuf ) != 0 ) {
		return ( -1 ) ;
	}
	pAppEnv->timeout_Sec= atol ( lc_prmBuf ) ;
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_TIMEOUT_USEC, lc_prmBuf ) != 0 ) {
		return ( -1 ) ;
	}
	pAppEnv->timeout_uSec= atol ( lc_prmBuf ) ;

	//	パラメータファイルクローズ	
	ZbmlPrmClose ( bp ) ;

	return ( 0 ) ; 
}

/******************************************************************************/
/*  関 数 名　：mainFunction()												  */
/*  機能概要　：メイン処理関数												  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct	appEnv *   	プログラム環境構造体		 			  */
/*  出　　力　：                                                              */
/*  復帰情報　：  0     : 成功												  */
/* 　　　　　　　-1     : 失敗												  */
/*  復帰情報　： 0		: 成功											  */
/* 　　　　　　　-1		: 失敗											  */
/******************************************************************************/
int
mainFunction( pAppEnv )
struct appEnv	*pAppEnv ;
{
    struct hostent          *sHostent ;
    struct sockaddr_in       sSockaddr ;
    struct sockaddr_in       cCladdr ;
    socklen_t                iCladdrLen ;
    int                      fh ;
    int                      cfh ;
    fd_set                   iMask ;
    fd_set                   iRead ;
    int                      iWatch ;

    char                     cHostname[256+1] ;
    pid_t                    tPid ;

    struct timeval           stTimeval ;

    int                      retval ;
    int                      li_stopFlg ;
    int                      on ;

    /***
     ***    通信初期処理
     ***/
    //  ソケット作成
    fh = socket ( PF_INET, SOCK_STREAM, 0 ) ;
    if ( fh < 0 ) {
        return ( -1 ) ;
    }

    //  アドレス即時再利用
    on = 1;
    setsockopt( fh, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );

    //  ホスト名取得
    gethostname ( cHostname, sizeof ( cHostname ) ) ;

    //  IPアドレス取得
    sHostent = gethostbyname ( cHostname ) ;
    if ( sHostent == NULL ) {
        return ( -1 ) ;
    }

    //  自ホスト情報セット
    memset ( &sSockaddr, '\0', sizeof ( sSockaddr ) ) ;
    sSockaddr.sin_family = PF_INET ;
    sSockaddr.sin_port   = htons(pAppEnv->Port); ;
    memcpy ( &( sSockaddr.sin_addr ), sHostent->h_addr, sHostent->h_length ) ;

	printf ( "addr[%d]" , *(unsigned int *)sHostent->h_addr_list[0] );

    //  ソケットバインド
    if ( bind ( fh, ( struct sockaddr * )&sSockaddr, sizeof ( sSockaddr ) ) == -1 ) {
        if ( errno == EADDRINUSE ) {
            fprintf ( stderr, "EADDRINUSE\n" ) ;
        }
        fprintf ( stderr, "errno[%d]\n", EADDRINUSE ) ;
        fprintf ( stderr, "errno[%d]\n", errno ) ;
        return ( -1 ) ;
    }

    // バッファ確保
    if ( listen ( fh, 10) == -1 ) {
        return ( -1 ) ;
    }

    //  子プロセス終了監視
    signal ( SIGCHLD, sFncWait ) ;

    //  監視ソケット設定
    FD_ZERO ( &iMask ) ;
    FD_SET ( fh, &iMask ) ;
    iWatch = fh + 1 ;

    /***
     ***    受信メイン処理
     ***/
    while ( 1 ) {
        //  接続待ち
        iRead = iMask;
        stTimeval.tv_sec = 0 ;
        stTimeval.tv_usec = 100 ;
        retval = select ( iWatch, &iRead, NULL, NULL, &stTimeval ) ;
        if ( retval == -1 ) {
            if ( errno == SIGILL ) {
                continue ;
            }
            return ( -1 ) ;
        } else if ( retval ) {
            //  クライアント接続
            if ( FD_ISSET ( fh, &iRead ) ) {
                iCladdrLen = sizeof ( cCladdr ) ;
                cfh = accept ( fh, ( struct sockaddr * )&cCladdr, &iCladdrLen ) ;
                if ( cfh == -1 ) {
                    return ( -1 ) ;
                }
                //  フォーク
                tPid = fork() ;
                if ( tPid  == 0 ) {
                    //  成功
                    close ( fh ) ;
                    //  子プロセス
                    if ( sFncChild ( cfh ) < 0 ) {
                        close ( cfh ) ;
                        return ( -1 ) ;
                    } else {
                        close ( cfh ) ;
                        break ;
                    }
                } else if ( tPid == -1 ) {
                    break ;
                } else {
                    //  親プロセス
                    close ( cfh ) ;
                }
            }
        }
    }

	/**
        if ( sFncShmGet ( pAppEnv, &li_stopFlg ) < 0 ) {
            return ( -1 ) ;
        }
        if ( li_stopFlg == 1 ) {
            close ( fh ) ;
            sFncShmDel ( pAppEnv ) ;
        }
	**/
    return ( 0 ) ;


}

/******************************************************************************/
/*  関 数 名　：endFunction()												  */
/*  機能概要　：終了処理関数												  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct	appEnv *   	プログラム環境構造体		 			  */
/*  出　　力　：                                                              */
/*  復帰情報　：無し			 											  */
/******************************************************************************/
void
endFunction( pAppEnv )
struct appEnv	*pAppEnv ;
{
	return ;
}
/******************************************************************************/
/*  関 数 名　：sFncChild()                                                   */
/*  機能概要　：子プロセス処理                                                */
/*              ログ情報データベース更新                                      */
/*  入　　力　：                                                              */
/*　 第１引数 ：int     ソケットハンドラ                                      */
/*  出　　力　：                                                              */
/*  復帰情報　：  0     : 成功                                                */
/* 　　　　　　　-1     : 失敗                                                */
/******************************************************************************/
static int
sFncChild ( pcfh )
int      pcfh ;
{

    fd_set               iMask ;
    fd_set               iRead ;
    int                  iWatch ;

    int                  iReadsize ;

    struct dataRec	 stDataRec ;

    /***
     ***    初期化
     ***/
    //  監視ソケット設定
    FD_ZERO ( &iMask ) ;
    FD_SET ( pcfh, &iMask ) ;
    iWatch = pcfh + 1 ;
    //  受信バッファ初期化
    memset ( &stDataRec, '\0', sizeof ( stDataRec ) ) ;
    /***
     ***    受信処理
     ***/
    //  受信待機
    iRead = iMask;
    if ( select ( iWatch, &iRead, NULL, NULL, NULL ) == -1 ) {
        return ( -1 ) ;
    }

    //  受信
    if ( FD_ISSET ( pcfh, &iRead ) ) {
        iReadsize = read ( pcfh, &stDataRec, sizeof ( stDataRec ) ) ;
        if ( iReadsize <= 0 ) {
            return ( -1 ) ;
	}
    }

    /***
     ***	送信処理
     ***/
fprintf ( stderr, "[%d]\n", stDataRec.command ) ;
    switch ( stDataRec.command ) {
	case COMMAND_PS :
	    sFncCOMMAND_PS( pcfh ) ;
	    break ;
	case COMMAND_EXEC_LABO :
	    close ( pcfh ) ;
	    sFncCOMMAND_EXEC_LABO( pcfh, &stDataRec ) ;
	    break ;
	case COMMAND_EXEC_LABO_NYOU :
	    close ( pcfh ) ;
	    sFncCOMMAND_EXEC_LABO_NYOU( pcfh, &stDataRec ) ;
	    break ;
	case COMMAND_EXEC_BM :
	    close ( pcfh ) ;
	    sFncCOMMAND_EXEC_BM( pcfh, &stDataRec ) ;
	    break ;
	case COMMAND_KILL :
	    close ( pcfh ) ;
	    sFncCOMMAND_KILL( pcfh, &stDataRec ) ;
	    break ;
	case COMMAND_KILL_DM :
	    close ( pcfh ) ;
	    return ( 9 ) ;
	case COMMAND_EXEC_BACK :
		sFncCOMMAND_BACK() ;
	default :
	    break ;
    }
    return ( 0 ) ;

}

void sFncCOMMAND_EXEC_LABO ( pcfh, pDataRec )
int			 pcfh ;
struct dataRec		*pDataRec ;
{
	struct dataRec	 stDataRec ;
	char		 iniFile[256] ;
	char		 cCommand[256] ;

	memset ( &stDataRec, '\0', sizeof ( stDataRec ) ) ;
	stDataRec.command = pDataRec->command ;
	stDataRec.sts = '0' ;

	strcpy ( iniFile, pDataRec->prmBuf ) ;
	sprintf ( cCommand, "%s %s", MYAPP_COM_EXEC_LABO, iniFile  ) ;
fprintf ( stderr, "#####[%s]\n" , cCommand ) ;
	if ( system( cCommand ) == -1 ) {
		stDataRec.sts = '9' ;
	}
	//write ( pcfh, &stDataRec, sizeof ( stDataRec ) ) ;
}
void sFncCOMMAND_EXEC_LABO_NYOU ( pcfh, pDataRec )
int			 pcfh ;
struct dataRec		*pDataRec ;
{
	struct dataRec	 stDataRec ;
	char		 iniFile[256] ;
	char		 cCommand[256] ;

	memset ( &stDataRec, '\0', sizeof ( stDataRec ) ) ;
	stDataRec.command = pDataRec->command ;
	stDataRec.sts = '0' ;

	strcpy ( iniFile, pDataRec->prmBuf ) ;
	sprintf ( cCommand, "%s %s", MYAPP_COM_EXEC_LABO_NYOU, iniFile  ) ;
fprintf ( stderr, "#####[%s]\n" , cCommand ) ;
	if ( system( cCommand ) == -1 ) {
		stDataRec.sts = '9' ;
	}
	//write ( pcfh, &stDataRec, sizeof ( stDataRec ) ) ;
}
void sFncCOMMAND_EXEC_BM ( pcfh, pDataRec )
int			 pcfh ;
struct dataRec		*pDataRec ;
{
	struct dataRec	 stDataRec ;
	char		 iniFile[256] ;
	char		 cCommand[256] ;

	memset ( &stDataRec, '\0', sizeof ( stDataRec ) ) ;
	stDataRec.command = pDataRec->command ;
	stDataRec.sts = '0' ;
	strcpy ( iniFile, pDataRec->prmBuf ) ;
	sprintf ( cCommand, "%s %s", MYAPP_COM_EXEC_BM, iniFile  ) ;
fprintf ( stderr, "#####[%s]\n" , cCommand ) ;
	if ( system( cCommand ) == -1 ) {
		stDataRec.sts = '9' ;
	}
	//write ( pcfh, &stDataRec, sizeof ( stDataRec ) ) ;
}
void sFncCOMMAND_KILL ( pcfh, pDataRec )
int			 pcfh ;
struct dataRec		*pDataRec ;
{
	struct dataRec	 stDataRec ;
	char		 shmKey[256] ;
	char		 cCommand[256] ;

	memset ( &stDataRec, '\0', sizeof ( stDataRec ) ) ;
	stDataRec.command = pDataRec->command ;
	stDataRec.sts = '0' ;

	strcpy ( shmKey, pDataRec->prmBuf ) ;
	sprintf ( cCommand, "%s %s", MYAPP_COM_KILL, shmKey ) ;
fprintf ( stderr, "#####[%s]\n" , cCommand ) ;
	if ( system( cCommand ) == -1 ) {
		stDataRec.sts = '9' ;
	}
	//write ( pcfh, &stDataRec, sizeof ( stDataRec ) ) ;
}
void sFncCOMMAND_PS ( pcfh )
int	pcfh ;
{
	FILE				*fp ;
	char	 			 cCommand[256] ;
	char				 cBuff[257] ;

	strcpy ( cCommand, "ps -ef" ) ;
	fp = popen ( cCommand , "r" ) ;
	if ( fp == NULL ) {
		return ;
	}
	while ( 1 ) {
		memset ( cBuff, '\0', sizeof ( cBuff ) ) ;
		if ( fread ( cBuff, sizeof ( cBuff ) -1, 1, fp )  <= 0 ) {
			break ;
		}
		write ( pcfh, cBuff, strlen ( cBuff ) ) ;
	}
	write ( pcfh, cBuff, strlen ( cBuff ) ) ;
	pclose ( fp ) ;
}
void sFncCOMMAND_BACK ( )
{
	system (MYAPP_COM_BACK) ;
}

/******************************************************************************/
/*  関 数 名　：sFncWait()                                                    */
/*  機能概要　：子プロセス終了監視                                            */
/*  入　　力　：                                                              */
/*  出　　力　：                                                              */
/*  復帰情報　：無し                                                          */
/******************************************************************************/
static void
sFncWait ( sig )
int      sig ;
{
    while ( waitpid ( -1, NULL,WNOHANG ) > 0 ) ;
    signal ( SIGCHLD, sFncWait ) ;
}


/******************************************************************************/
/*  関 数 名　：main()														  */
/*  機能概要　：初期処理関数												  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct	env *   	プログラム環境構造体。		 			  */
/*  出　　力　：                                                              */
/*  復帰情報　：  0     : 成功												  */
/* 　　　　　　　-1     : 失敗												  */
/******************************************************************************/
int
main ( argc, argv )
int		 argc ;
char	*argv[] ;
{
	struct appEnv		sAppEnv ;

    /***
     ***    バックグラウンド実行
     ***/
	if ( daemon ( 1, 1 ) < 0 ) {
		exit ( 9 ) ;
	}

	/***
	 ***	初期処理
	 ***/
	if ( initFunction ( argc, argv, &sAppEnv )  != 0 ) {
		fprintf ( stderr, "%s : Error initFunction \n", MYAPP_APP_NAME ) ;
		exit ( 9 ) ;
	}

	/***
	 ***	メイン処理	
	 ***/
	if ( mainFunction ( &sAppEnv )  != 0 ) {
		fprintf ( stderr, "%s : Error mainFunction \n", MYAPP_APP_NAME ) ;
		exit ( 9 ) ;
	}

	/***
	 ***	終了処理
	 ***/
	endFunction ( &sAppEnv ) ;

	exit ( 0 ) ;
}
