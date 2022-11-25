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
/*  1.01     2006/12/06   YOON JONG JIN    エラー追加                         */
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

#include "bml_base.h"
#include "bmllog.h"
#include "bmlprm.h"
#include "BD401.h"

/******************************************************************************/
/* Define宣言       	                                                      */
/******************************************************************************/
//	TRACE
/*
#if defined ( _TRACE )
#define malloc(a)   _malloc(a, __FILE__, __LINE__)
#define free(p)     _free(p, __FILE__, __LINE__)
#endif
*

/******************************************************************************/
/* 構造体宣言       	                                                      */
/******************************************************************************/

/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/
MYAPP_STSCODE		 gintErrorCode ;
static  char		*gpToken ;						//  sFncToken用静的ポインタ
struct stcLogMember	 gstLogMem ;					//  ログ出力情報

static	char		 gMatchOrder[256] ;
static	char		 gDirIA_Idx[MYAPP_PATH_SIZE] ;

/******************************************************************************/
/* 関数宣言 		                                                          */
/******************************************************************************/
//	受信処理関連	
static	int		sFncRcevMain ( struct appEnv *, int ) ;
static	int		sFncOederFileMove ( struct appEnv *, char *, char *) ;

//	ファイル検索関連【コールバック】
static	int		sFncFileCompar ( struct dirent **, struct dirent ** )  ;
static	int		sFncFileFillter ( struct dirent * ) ;

//	共有メモリ操作関数
static	int		sFncShmCrt ( struct appEnv * ) ;
static	int		sFncShmGet ( struct appEnv *, int *) ;
static	int		sFncShmDel ( struct appEnv * ) ;

//  システムログ出力
static  void    sFncSyslog ( int, char *, char * ) ;

//	その他関数
static  char*   sFncToken ( char * ) ;
static  int     sFncFileRename ( char *, char *, char *, char * ) ;
static	void	sFncTrim ( char * ) ;

/******************************************************************************/
/*  関 数 名　：initFunction()												  */
/*  機能概要　：初期処理関数												  */
/*  入　　力　：                                                              */
/*　 第１引数 ：int   				メインパラメータ数			 			  */
/*　 第２引数 ：char *   			メインパラメータ			 			  */
/*  出　　力　：                                                              */
/*　 第３引数 ：struct	appEnv *   	プログラム環境構造体		 			  */
/*  復帰情報　： RTN_OK		: 成功											  */
/* 　　　　　　　RTN_NG		: 失敗											  */
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
	char		*lc_login ;

	char	   **bufPrmIA ;
	int			 cntPrmIA ;
	char		*bufToken ;
	int			 idx ;

	/***
	 ***    引数チェック
	 ***/
    if ( argc != 2 ) {
        fprintf ( stderr, "%s : There is an error in a command parameter\n", MYAPP_APP_NAME ) ;
        return ( RTN_NG ) ;
    }

	/***
	 ***	ログオープン
	 ***/
	if ( ZbmlOpenLog ( argv[1] ) != 0 ) {
		return ( RTN_NG ) ;
	}

	//	ログ情報初期設定
	memset ( &gstLogMem, '\0', sizeof ( gstLogMem ) ) ;
	if ( ( lc_login = getenv( "LOGNAME" ) ) != NULL ) {
		strcpy ( gstLogMem.pcLoginId, lc_login ) ;
	}
	strcpy ( gstLogMem.pcAppName, MYAPP_APP_NAME ) ;

	//	開始ログ出力
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__,
				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "プログラム起動" ) ;

	/***
	 ***	初期化	
	 ***/
	//	エラーステータス変更
	gintErrorCode = 0 ;
	//	プログラム環境変数初期化
	memset ( pAppEnv , '\0', sizeof ( struct appEnv ) ) ;


	/***
	 ***	引数チェック	
	if ( argc != 2 ) {
		gintErrorCode = MYAPP_STSCODE_ERR_USEGE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "initFunction", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "コマンドパラメータに誤りがあります" ) ;
		return ( RTN_NG ) ;
	}
	 ***/

	/***
	 ***	パラメータファイル情報退避
	 ***/
	//	パラメータファイルオープン	
	bp = ZbmlPrmOpen ( argv[1] ) ;		
	if ( bp == NULL ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmOpen", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータファイルのオープンに失敗しました[%s]", argv[1] ) ;
		return ( RTN_NG ) ;
	}
	//	ポート	
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_PORT, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_PORT ) ;
		return ( RTN_NG ) ;
	}
	pAppEnv->Port = atoi ( lc_prmBuf ) ;

	//	データベース名
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_DB_NAME, pAppEnv->cDb_Name ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DB_NAME ) ;
		return ( RTN_NG ) ;
	}
	//	データベースユーザ
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_DB_USER, pAppEnv->cDb_User ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DB_USER ) ;
		return ( RTN_NG ) ;
	}
	//	データベースパスワード
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_DB_PASSWD, pAppEnv->cDb_Passwd ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DB_PASSWD ) ;
		return ( RTN_NG ) ;
	}
	//	共有メモリキー取得
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_SHM_KEY, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_SHM_KEY ) ;
		return ( RTN_NG ) ;
	}
	pAppEnv->shm_Key = atoi ( lc_prmBuf ) ;
	//	タイムアウト時間取得
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_TIMEOUT_SEC, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_TIMEOUT_SEC ) ;
		return ( RTN_NG ) ;
	}
	pAppEnv->timeout_Sec= atol ( lc_prmBuf ) ;
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_TIMEOUT_USEC, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_TIMEOUT_USEC ) ;
		return ( RTN_NG ) ;
	}
	pAppEnv->timeout_uSec= atol ( lc_prmBuf ) ;

	//	オーダーデータ
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_DIR_IA_DAT, pAppEnv->cDirIA_Dat ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_IA_DAT ) ;
		return ( RTN_NG ) ;
	}
	//	作成完了データ
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_DIR_IA_IDX, pAppEnv->cDirIA_Idx ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_DIR_IA_IDX ) ;
		return ( RTN_NG ) ;
	}

	//	ＩＡサーバディレクトリ
	bufPrmIA = 0 ;
	li_retSts= ZbmlPrmGetValList ( bp, MYAPP_PRM_IA_SERVER_DIR, &cntPrmIA, &bufPrmIA )  ;
	if ( li_retSts != 0 || cntPrmIA == 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetValList", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "パラメータが取得できませんでした[%s]", MYAPP_PRM_IA_SERVER_DIR ) ;
		return ( RTN_NG ) ;
	}
	pAppEnv->CntInfoIA = cntPrmIA ;
	pAppEnv->infoIA = ( struct my_infoIA * ) malloc ( sizeof ( struct my_infoIA ) * cntPrmIA ) ;	
	if ( pAppEnv->infoIA == NULL ) {
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "malloc", __LINE__,
			 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 "メモリアロケーション失敗[%d:%s]", errno, strerror ( errno ) ) ;
		return ( RTN_NG ) ;
	}
	for ( idx = 0 ; idx < cntPrmIA ; idx ++ ) {
		bufToken = strtok ( bufPrmIA[idx], "\t" ) ;
		if ( bufToken == NULL ) {
			gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetValList", __LINE__,
					 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 		"パラメータが取得できませんでした[%s]", MYAPP_PRM_IA_SERVER_DIR ) ;
			return ( RTN_NG ) ;
		}
		strcpy ( pAppEnv->infoIA[idx].smpNo, bufToken ) ; 
		bufToken = strtok ( NULL, "\t" ) ;
		if ( bufToken == NULL ) {
			gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetValList", __LINE__,
					 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 		"パラメータが取得できませんでした[%s]", MYAPP_PRM_IA_SERVER_DIR ) ;
			return ( RTN_NG ) ;
		}
		strcpy ( pAppEnv->infoIA[idx].dirIA_DAT, bufToken ) ; 
		bufToken = strtok ( NULL, "\t" ) ;
		if ( bufToken == NULL ) {
			gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetValList", __LINE__,
					 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 		"パラメータが取得できませんでした[%s]", MYAPP_PRM_IA_SERVER_DIR ) ;
			return ( RTN_NG ) ;
		}
		strcpy ( pAppEnv->infoIA[idx].dirIA_IDX, bufToken ) ; 
		free ( bufPrmIA[idx] ) ;
	}
	free ( bufPrmIA ) ;

	//	パラメータファイルクローズ	
	ZbmlPrmClose ( bp ) ;

	/***
	 ***	共有メモリ生成	
	 ***/
	if ( sFncShmCrt ( pAppEnv ) != RTN_OK ) {
		return ( RTN_NG ) ;
	}

	/***
	 ***	データベースオープン
	 ***/
	ll_retSts = ZdbConnect( pAppEnv->cDb_Name, 
							pAppEnv->cDb_User, pAppEnv->cDb_Passwd ) ;
	if ( ll_retSts != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_DB ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZdbConnect", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "データベースオープンに失敗しました[DB=%s USER=%s PASS=%s]", pAppEnv->cDb_Name, pAppEnv->cDb_User, pAppEnv->cDb_Passwd ) ;
		return ( RTN_NG ) ;
	}

	return ( RTN_OK ) ; 
}

/******************************************************************************/
/*  関 数 名　：mainFunction()												  */
/*  機能概要　：メイン処理関数												  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct	appEnv *   	プログラム環境構造体		 			  */
/*  出　　力　：                                                              */
/*  復帰情報　：  0     : 成功												  */
/* 　　　　　　　-1     : 失敗												  */
/*  復帰情報　： RTN_OK		: 成功											  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
int
mainFunction( pAppEnv )
struct appEnv	*pAppEnv ;
{

	//	ソケット関連
	struct hostent			*sHostent ;
	struct sockaddr_in		 sSockaddr ;
	struct sockaddr_in		 cCladdr ;
	socklen_t				 iCladdrLen ;
	int						 fh ;
	int						 cfh ;
	char					 cHostname[256+1] ;
	int						 on ;
	//	ソケット監視
	fd_set				 	 iMask ;
	fd_set				 	 iRead ;
	int					 	 iWatch ;
	struct timeval			 stTimeval ;
	int						 retval ;
	//	その他
	int						 li_stopFlg ;
	int						 iRetSts ;
char	trcBuff[4] ;

	/***
	 ***	通信初期処理
	 ***/
loging ( "mainFunction : 通信初期処理\n" ) ;
	//	ソケット作成
	fh = socket ( PF_INET, SOCK_STREAM, 0 ) ;
	if ( fh < 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SOCKET ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "socket", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "ソケットの作成に失敗しました[error=%d]", errno ) ;
		return ( RTN_NG ) ;
	}

	//	アドレス即時再利用
	on = 1; 
	setsockopt( fh, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );

	//	ホスト名取得	
	gethostname ( cHostname, sizeof ( cHostname ) ) ;

	//	IPアドレス取得
	sHostent = gethostbyname ( cHostname ) ;
	if ( sHostent == NULL ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SOCKET ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "socket", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "ＩＰアドレスの取得に失敗しました[hostneme=%s error=%d]", cHostname, errno ) ;
		return ( RTN_NG ) ;
	}

	//	自ホスト情報セット
	memset ( &sSockaddr, '\0', sizeof ( sSockaddr ) ) ;
	sSockaddr.sin_family = PF_INET ;
	sSockaddr.sin_port	 = htons(pAppEnv->Port); ;
	memcpy ( &( sSockaddr.sin_addr ), sHostent->h_addr, sHostent->h_length ) ;
loging ( "    HostName : [%s]\n", cHostname ) ;
loging ( "    Port     : [%d]\n", pAppEnv->Port ) ;
loging ( "    IP       : [%u.%u.%u.%u]\n", *(sHostent->h_addr),
										  *(sHostent->h_addr+1),
										  *(sHostent->h_addr+2),
										  *(sHostent->h_addr+3)) ;

	//	ソケットバインド
	iRetSts =  bind ( fh, ( struct sockaddr * )&sSockaddr, sizeof ( sSockaddr ) ) ;
	if ( iRetSts == -1 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SOCKET ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "bind", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "バインドに失敗しました[error=%d]", errno ) ;
		return ( RTN_NG ) ;
	}
//loging ( "    ソケットバインド : [bind]\n") ;
	
	// バッファ確保
	iRetSts = listen ( fh, 10 ) ;
	if ( iRetSts == -1 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SOCKET ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "listen", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "バッファの確保に失敗しました[error=%d]", errno ) ;
		return ( RTN_NG ) ;
	}
//loging ( "    バッファ確保 : [listen]\n") ;

	//	監視ソケット設定
	FD_ZERO ( &iMask ) ;
	FD_SET ( fh, &iMask ) ;
	iWatch = fh + 1 ;

	/***
	 ***	受信メイン処理
	 ***/
//loging ( "    ###### 受信メイン処理 ######\n") ;
	while ( 1 ) {
		//	接続待ち
//loging ( "    接続待ち\n") ;
		iRead = iMask;
		stTimeval.tv_sec  = pAppEnv->timeout_Sec ;
		stTimeval.tv_usec = pAppEnv->timeout_uSec ;
		retval = select ( iWatch, &iRead, NULL, NULL, &stTimeval ) ;
		if ( retval == -1 ) {
			if ( errno == SIGILL ) {
				continue ;
			}
			//	異常終了	LOG
			gintErrorCode = MYAPP_STSCODE_ERR_SOCKET ;
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "select", __LINE__,
					 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 	 "ソケット監視で失敗しました[error=%d]", errno ) ;
			return ( RTN_NG ) ;
		} else if ( retval ) {
			//	クライアント接続
			if ( FD_ISSET ( fh, &iRead ) ) {
				iCladdrLen = sizeof ( cCladdr ) ;
				cfh = accept ( fh, ( struct sockaddr * )&cCladdr, &iCladdrLen ) ;
				if ( cfh == -1 ) {
					//	異常終了	LOG
					gintErrorCode = MYAPP_STSCODE_ERR_SOCKET ;
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "accept", __LINE__,
							 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 			 "クライアント接続で失敗しました[error=%d]", errno ) ;
					return ( RTN_NG ) ;
				}
loging ( "    !!!! クライアント接続 !!!!\n") ;
memcpy ( trcBuff, &cCladdr.sin_addr, sizeof ( trcBuff ) ) ;
loging ( "    IP       : [%u.%u.%u.%u]\n", trcBuff[0],
										   trcBuff[1],
										   trcBuff[2],
										   trcBuff[3] ) ;
				//	ＩＡサーバ転送処理	
				iRetSts = sFncRcevMain ( pAppEnv, cfh ) ;
				if ( iRetSts == RTN_NG ) {
					return ( -1 ) ;
				} else if ( iRetSts == RTN_SKIP ) {
					close ( cfh ) ;
				} else if ( iRetSts == 2 ) {
					//	停止
					close ( fh ) ;
					close ( cfh ) ;
					break ;
				}
			}
		}

		/***
		 *** 停止コマンド確認
		 ***/
		sFncShmGet ( pAppEnv, &li_stopFlg ) ;
		if ( li_stopFlg == 1 ) {
			close ( fh ) ;
			break ;
		}
	}

	return ( RTN_OK ) ;
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
	/***
	 ***	データベースクローズ
	 ***/
	ZdbDisConnect() ;

	/***
	 ***	共有メモリ削除	
	 ***/
	sFncShmDel ( pAppEnv ) ;

	/***
	 ***	ログクロース
	 ***/
	//	開始ログ出力
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__,
				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "プログラム終了" ) ;
	ZbmlCloseLog() ;

	return ;
}

/******************************************************************************/
/*  関 数 名　：sFncRcevMain()	    										  */
/*  機能概要　：受信メイン処理												  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct	appEnv *   	プログラム環境構造体		 			  */
/*　 第２引数 ：int					ソケットハンドラ						  */
/*  出　　力　：                                                              */
/*  復帰情報　： RTN_OK		: 成功											  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/* 　　　　　　　2		    : 終了（停止コマンド発行）						  */
/******************************************************************************/
static int
sFncRcevMain ( pAppEnv, pcfh )
struct appEnv	*pAppEnv ;
int				 pcfh ;
{
	int				  	 li_retSts ;

	fd_set				 iMask ;
	fd_set				 iRead ;
	int					 iWatch ;

	int					 iReadsize ;
	char				 cChar ;
	char				 cRcvBuf[MYAPP_RCV_SIZE+1] ;
	int				 	 iidx ;

	char				 cSmpno[8+1] ;
	char				 cRckno[MYAPP_RCKNO_SIZE] ;
	char				*pToken ;

	int					 li_stopFlg ;
	int					 retval ;
	struct timeval		 stTimeval ;

	/***
	 ***	初期化
	 ***/
	//	監視ソケット設定
	FD_ZERO ( &iMask ) ;
	FD_SET ( pcfh, &iMask ) ;
	iWatch = pcfh + 1 ;
	//	受信バッファ初期化
	memset ( cRcvBuf, '\0', sizeof ( cRcvBuf ) ) ;
	iidx = 0 ;

	/***
	 ***	受信処理
	 ***/
	while ( 1 )  {
		//	受信待機
		iRead = iMask;
		stTimeval.tv_sec  = pAppEnv->timeout_Sec ;
		stTimeval.tv_usec = pAppEnv->timeout_uSec ;
		retval = select ( iWatch, &iRead, NULL, NULL, &stTimeval ) ;
		if ( retval == -1 ) {
			if ( errno == SIGILL ) {
				continue ;
			}
			//	異常終了	LOG
			gintErrorCode = MYAPP_STSCODE_ERR_SOCKET ;
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "select", __LINE__,
					 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 	 "ソケット監視で失敗しました[error=%d]", errno ) ;
			return ( RTN_SKIP ) ;
		} else if ( retval ) {
			//	受信
			if ( FD_ISSET ( pcfh, &iRead ) ) {
				iReadsize = read ( pcfh, &cChar, sizeof ( cChar ) ) ;
				if ( iReadsize < 0 ) {
					//	異常終了	LOG
					gintErrorCode = MYAPP_STSCODE_ERR_SOCKET ;
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "read", __LINE__,
							 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 			 "受信に失敗しました[error=%d]", errno ) ;
					return ( RTN_SKIP ) ;
				} else if ( iReadsize == 0 ) {
					//	異常終了	LOG
					gintErrorCode = MYAPP_STSCODE_ERR_SOCKET ;
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "read", __LINE__,
							 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 			 "クライアントと接続が切れました[error=%d]", errno ) ;
					return ( RTN_SKIP ) ;
				}
loging ( "    受信: [%d][%c][%x][%d]\n", iidx, cChar, cChar, iReadsize ) ;
				//	受信データサイズチェック
				if ( iidx >= MYAPP_RCV_SIZE ) {
loging ( "    受信: 受信データサイズオーバーフロー\n"  ) ;
					//	異常終了	LOG
					gintErrorCode = MYAPP_STSCODE_ERR_DATA ;
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "read", __LINE__,
							 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 			 "受信データサイズオーバーフロー" ) ;
					memset ( cRcvBuf, '\0', sizeof ( cRcvBuf ) ) ;
					iidx = 0 ;
					continue ;
				}
				//	受信バッファ格納
				if (  cChar != 0x0a  &&  cChar != 0x0d ) {
					cRcvBuf[iidx] = cChar ;	
					iidx ++ ;
				}
				//	データ終端
				if ( cChar == 0x0a ) {
	 				//	受信データ展開
loging ( "    ■■■受信データ■■■\n") ;
loging ( "    ファイルハンドル : [%d]\n", pcfh ) ;
loging ( "    受信データ       : [%s]\n", cRcvBuf ) ;
					sFncPutLog ( TRCKIND_TRACE, __FILE__, "read", __LINE__,
							 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 			 "受信電文[%s]", cRcvBuf ) ;
					memset ( cSmpno,  '\0', sizeof ( cSmpno ) ) ;
					memset ( cRckno,  '\0', sizeof ( cRckno ) ) ;
					pToken =  sFncToken ( cRcvBuf ) ;
					if ( pToken != NULL ) {
						memcpy ( cSmpno, pToken, sizeof ( cSmpno )-1 ) ;
					}
					pToken =  sFncToken ( NULL ) ;
					if ( pToken != NULL ) {
						memcpy ( cRckno, pToken, sizeof ( cRckno )-1 ) ;
					}
loging ( "    サンプラ号機     : [%s]\n", cSmpno ) ;
loging ( "    ラックＮＯ       : [%s]\n", cRckno ) ;

					//	コピー処理
//my_loging ( "STR : %s\n", cRckno ) ;
					li_retSts = sFncOederFileMove ( pAppEnv, cSmpno, cRckno ) ;
					if ( li_retSts < 0 ) {
						//return ( RTN_SKIP ) ;
						//return ( RTN_NG ) ;
					}
//my_loging ( "END : %s\n", cRckno ) ;
					memset ( cRcvBuf, '\0', sizeof ( cRcvBuf ) ) ;
					iidx = 0  ;
				}
			} 
		} 

		//	停止コマンド確認
		sFncShmGet ( pAppEnv, &li_stopFlg ) ;
		if ( li_stopFlg == 1 ) {
			return ( 2 ) ;
		}
	}

	return ( RTN_OK ) ;
}

/******************************************************************************/
/*  関 数 名　：sFncOederFileMove()	 										  */
/*  機能概要　：オーダーファイル移動処理					  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct	appEnv *   	プログラム環境構造体		 			  */
/*　 第２引数 ：char *   			サンプラＮＯ					 	      */
/*　 第３引数 ：char *   			ラックＮＯ						 	      */
/*  出　　力　：                                                              */
/*  復帰情報　： RTN_OK		: 成功											  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
static	int
sFncOederFileMove ( pAppEnv, pSmpno, pRckno )
struct appEnv	*pAppEnv ;
char			*pSmpno ;
char			*pRckno ;
{

	int				  li_retSts ;

	struct dirent	**ldirBuf ;
	long			  lfileCnt ;
	long			  idx ;
	char			 *dirIA_DAT ;
	char			 *dirIA_IDX ;
	char			  rlFileName[MYAPP_PATH_SIZE] ;

	FILE			 *fp ;
	char			  koFileName[MYAPP_PATH_SIZE] ;
	char	  		  recBuf[512] ;
	char			  knskisymd[10+1] ;
	char			 *pToken ;

	char			  idxFileName[MYAPP_PATH_SIZE] ;
	/***
	 ***	初期設定
	 ***/
	//	コールバック関数内参照値設定
	// NEW sprintf ( gMatchOrder, "%s_%s", MYAPP_SEND_KIND_OD, pRckno ) ;
	memset ( gMatchOrder, '\0', sizeof ( gMatchOrder )  ) ;
	memset ( gMatchOrder, '_', sizeof ( gMatchOrder ) - 1 ) ;
	memcpy ( gMatchOrder, pRckno, strlen ( pRckno )  ) ;
	strcpy ( gDirIA_Idx, pAppEnv->cDirIA_Idx ) ;
	//	移動先ディレクトリ取得
	dirIA_DAT = NULL ;
	dirIA_IDX = NULL ;
	for ( idx = 0 ; idx < pAppEnv->CntInfoIA ; idx ++ ) {
		if ( strcmp ( pSmpno, pAppEnv->infoIA[idx].smpNo ) == 0 ) {
			dirIA_DAT = pAppEnv->infoIA[idx].dirIA_DAT ;
			dirIA_IDX = pAppEnv->infoIA[idx].dirIA_IDX ;
			break ;
		}
	}

	if ( dirIA_DAT == NULL || dirIA_IDX == NULL ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOederFileMove", __LINE__,
			 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 "ＩＡサーバのディレクトリが存在しません[SNO=%s RNO=%s]", pSmpno, pRckno ) ;
		return ( RTN_NG ) ;
	}

	/***
	 ***	ファイル存在チェック
	 ***/
//    sFncPutLog ( TRCKIND_DEBUG, __FILE__, "read", __LINE__,
//        EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//        "探すDIRECTORY[%s]", gDirIA_Idx ) ;	
	if ( ( lfileCnt = scandir ( pAppEnv->cDirIA_Idx, &ldirBuf,
								(void*)sFncFileFillter, alphasort ) ) < 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_DIR;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "scandir", __LINE__,
			 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 "検査オーダーファイル情報の取得に失敗しました[SNO=%s RNO=%s]", pSmpno, pRckno ) ;
		return ( RTN_NG ) ;
	}
	if ( lfileCnt == 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOederFileMove", __LINE__,
			 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 "検査オーダ情報ファイルが存在しません[SNO=%s RNO=%s]", pSmpno, pRckno ) ;
		return ( RTN_NG ) ;
	}

	/***
	 ***	検査開始日取得
	 ***		検査オーダ情報ファイルの最初の１件から取得
	 ***/
	sprintf ( koFileName, "%s/%s", pAppEnv->cDirIA_Dat, ldirBuf[0]->d_name ) ;
	//	ファイルオープン
	fp = fopen ( koFileName, "r" ) ;
	if ( fp == NULL ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "fopen", __LINE__,
			 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 "ファイルのオープンに失敗しました[%s]", koFileName ) ;
		return ( RTN_NG ) ;
	}
//    sFncPutLog ( TRCKIND_DEBUG, __FILE__, "read", __LINE__,
//        EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//        "ファイルオープン完了" ) ;

	//	読み込み
	if ( fgets ( recBuf, sizeof ( recBuf ), fp ) == NULL ) {
		fclose ( fp ) ;
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "fgets", __LINE__,
			 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 "ファイルの読み込みに失敗しました[%s]", koFileName ) ;
		return ( RTN_NG ) ;
	}

	//	クローズ
	fclose ( fp ) ;

	//	検査開始日取得	
	pToken = strtok ( recBuf, "," ) ;
	if ( pToken == NULL ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "fgets", __LINE__,
			 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 "検査開始日時の取得に失敗しました[SNO=%s RNO=%s]", pSmpno, pRckno ) ;
		return ( RTN_NG ) ;
	}
	strcpy ( knskisymd, pToken ) ;
	sFncTrim ( knskisymd ) ;

	/***
	 ***	ファイル移動
	 ***/

//    sFncPutLog ( TRCKIND_DEBUG, __FILE__, "read", __LINE__,
//        EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//        "ファイル移動" ) ;
	for ( idx = 0 ; idx < lfileCnt ; idx ++ ) {
		//	検査オーダー情報ファイル
		if ( sFncFileRename ( pAppEnv->cDirIA_Dat, ldirBuf[idx]->d_name,
							  dirIA_DAT, ldirBuf[idx]->d_name ) != RTN_OK ) {
			return ( RTN_NG ) ;
		}
		//	即時チェック情報ファイル
		sprintf ( rlFileName, "%s%s", MYAPP_SEND_KIND_CH, 
									  &(ldirBuf[idx]->d_name[2]) ) ;
		if ( sFncFileRename ( pAppEnv->cDirIA_Dat, rlFileName,
							  dirIA_DAT, rlFileName ) != RTN_OK  ) {
			return ( RTN_NG ) ;
		}
		//	移動完了ファイル
		if ( sFncFileRename ( pAppEnv->cDirIA_Idx, ldirBuf[idx]->d_name,
							  dirIA_IDX, ldirBuf[idx]->d_name ) != RTN_OK ) {
			return ( RTN_NG ) ;
		}
		//sprintf ( idxFileName, "%s/%s", pAppEnv->cDirIA_Idx, ldirBuf[idx]->d_name ) ;
		//unlink ( idxFileName ) ;
	}

	/***
	 ***	検体ポジション管理追加
	 ***/
//	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "read", __LINE__,
//        EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//        "検体ポジション管理追加" ) ;
	li_retSts = sFncInsKENPOS ( knskisymd, pRckno, pSmpno ) ;
	//20070105 YOON
    if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
    {   //デッドロックor重複
       	ZdbRollback () ;
		return ( RTN_OK ) ;
		 
    }
	else if ( li_retSts < 0 ) {
		//	ロールバック
		ZdbRollback () ;
		return ( RTN_NG ) ;
	}

	//	コミット
	ZdbCommit () ;
	return ( RTN_OK ) ;

}

/******************************************************************************/
/*  関 数 名　：sFncFileRename()  			 								  */
/*  機能概要　：ファイルを移動する							  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *   	移動元ディレクトリ						 	      */
/*　 第２引数 ：char *   	移動元ファイル名						 	      */
/*　 第３引数 ：char *   	移動先ディレクトリ						 	      */
/*　 第４引数 ：char *   	移動先ファイル							 	      */
/*  出　　力　：                                                              */
/*  復帰情報　： RTN_OK		: 成功											  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
static int
sFncFileRename ( pc_fromDir, pc_fromFileName, pc_toDir, pc_toFileName )
char	*pc_fromDir ;
char	*pc_fromFileName ;
char	*pc_toDir ;
char	*pc_toFileName ;
{
	char	lc_fromPath[MYAPP_PATH_SIZE] ;
	char	lc_toPath[MYAPP_PATH_SIZE] ;
	char	lc_command[1024] ;

	sprintf ( lc_fromPath, "%s/%s", pc_fromDir, pc_fromFileName ) ;
	sprintf ( lc_toPath,   "%s/%s", pc_toDir,   pc_toFileName ) ;
	sprintf ( lc_command, "%s %s %s", MYAPP_COMMAND_CP, lc_fromPath, lc_toPath ) ;

	if ( system ( lc_command ) == -1 ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "rename", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "ファイルのコピーに失敗しました[%s->%s]", lc_fromPath, lc_toPath ) ;
        return ( RTN_NG ) ;
    }

    /***  NFS Mount
	if ( rename ( lc_fromPath, lc_toPath ) < 0 ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "rename", __LINE__,
 	 	 			 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
 	 	 			 "ファイルの移動に失敗しました[%s->%s]", lc_fromPath, lc_toPath ) ;
		return ( RTN_NG ) ;
	}
	***/
	
	return ( RTN_OK ) ;
}
/******************************************************************************/
/*  関 数 名　：sFncFileFillter()			 								  */
/*  機能概要　：ファイルフィルター【コールバック関数】		  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct dirent *   	ディレクトリ構造体				 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	対象外ファイル										  */
/*					 1	対象ファイル										  */
/******************************************************************************/
static	int
sFncFileFillter ( pdirEnt ) 
struct dirent *pdirEnt ;
{

	int			 li_len ;

	//printf("yoon d_name:%s,gMatchOrder:%s\n",pdirEnt->d_name,gMatchOrder);
/*DELL 20070120
//  sFncPutLog ( TRCKIND_DEBUG, __FILE__, "read", __LINE__,
//      EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//      "ディレクトリチェック d_name:%s,gMatchOrder:%s",
//		pdirEnt->d_name,gMatchOrder);
*/
	
	//ディレクトリチェック
	if ( strcmp ( pdirEnt->d_name, "." ) == 0 ||
		 strcmp ( pdirEnt->d_name, ".." ) == 0 ) {
		return ( 0 ) ;
	}

	//文字列長チェック
	li_len = strlen ( pdirEnt->d_name )  ;
	if ( li_len  != MYAPP_OD_FILE_LEN ) {
		return ( 0 ) ;
	}

	//	ラックＮＯチェック
	if ( memcmp ( &(pdirEnt->d_name[3]), gMatchOrder, sizeof  ( char ) * 10) != 0 ) {
/* OLD
	if ( memcmp ( &(pdirEnt->d_name[16]), gMatchOrder, sizeof ( char ) * 10 ) != 0 ) {
*/
		return ( 0 ) ;
	}


	//拡張子チェック
	if ( memcmp ( &(pdirEnt->d_name[li_len-strlen(MYAPP_SEND_SFX)]), 
				  MYAPP_SEND_SFX, 
				  strlen ( MYAPP_SEND_SFX ) ) != 0 ) {
		return ( 0 ) ;
	}


	return ( 1 ) ;
}
/******************************************************************************/
/*  関 数 名　：sFncSyslog()				 								  */
/*  機能概要　：システムログ出力							  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：int 			   	プライオリティー						  */
/*　 第２引数 ：char *   			関数名									  */
/*　 第３引数 ：char * 		  		メッセージ								  */
/*  出　　力　：                                                              */
/*  復帰情報　：無し														  */
/******************************************************************************/
static void
sFncSyslog ( piPri, pcFncname, pcMsg ) 
int		 piPri ;
char	*pcFncname ;
char	*pcMsg ;
{
#if defined ( _SYSLOGOUT )
	if ( errno != 0 ) {
		syslog ( piPri, "Error: Function %s %s (errno=%d msg=%m)",
						pcFncname, pcMsg, errno ) ;
	} else {
		syslog ( piPri, "Error: Function %s %s (errno=%d)",
						pcFncname, pcMsg, errno ) ;
	}
#endif
#if defined ( _TRACE )
	if ( errno != 0 ) {
		fprintf ( stderr, "Error: Function %s %s (errno=%d msg=%s)\n",
							pcFncname, pcMsg, errno, strerror ( errno ) ) ;
	} else {
		fprintf ( stderr, "Error: Function %s %s (errno=%d)\n",
							pcFncname, pcMsg, errno ) ;
	}
#endif
}
/******************************************************************************/
/*  関 数 名　：sFncToken()			 										  */
/*  機能概要　：トークン分割								  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *   	文字列									 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：char *														  */
/*					 NULL	終端											  */
/*					 NULL以外	文字列										  */
/******************************************************************************/
static	char*
sFncToken ( pString )
char	*pString ;
{
	char	*p ;
	char	*pRet ;
	int		 liIdx ;

	//	分割文字列ポインター設定
	if ( pString == NULL ) {
		p = gpToken ;	
	}
	else {
		gpToken = pString ;
		p = pString ;	
	}

	//	終端チェック（最終カンマ以降を最後の値と取得するため）	
	if ( p == NULL ) {
		return ( NULL ) ;
	}

	//	トークン分割
	gpToken = NULL ;	//最終カンマ以降を最後の値と取得するため
	pRet = p ;
	while ( *p ) {
		if ( *p == ',' ) {
			*p  = '\0' ;
			gpToken =  p + 1 ;
			break  ;
		}	
		p++ ;
	}
	return ( pRet ) ;
}

/******************************************************************************/
/*  関 数 名　：sFncTrim()  			 									  */
/*  機能概要　：文字列前後のスペースを削除する				  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *   	編集文字列								 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：無し														  */
/******************************************************************************/
static	void
sFncTrim ( s )
char	*s ;
{
	int		i ;

    i = strlen ( s ) ;

    while ( --i >= 0 && isspace ( (unsigned char)s[i] ) ) ;
    s[i+1] = '\0';
    for (i = 0; isspace((unsigned char)s[i]); i++) ;
    if ( i != 0 ) {
		strcpy ( s, s + i ) ;
	}
}

/******************************************************************************/
/*  関 数 名　：sFncShmCrt()				 								  */
/*  機能概要　：共有メモリ生成								  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体			 	      */
/*  出　　力　：                                                              */
/*  復帰情報　： RTN_OK		: 成功											  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
static int
sFncShmCrt ( pAppEnv )
struct appEnv	*pAppEnv ;
{
	int		*shmData ;

	//	取得
	pAppEnv->shm_Id = shmget ( (key_t)pAppEnv->shm_Key, 
							MYAPP_SHM_SIZE, 
							0666 | IPC_CREAT ) ;
	if ( pAppEnv->shm_Id < 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmget", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "共有メモリの操作に失敗しました" ) ;
		return ( RTN_NG ) ;
	}

	//	アタッチ	
	shmData = ( int * ) shmat ( pAppEnv->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmat", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "共有メモリの操作に失敗しました" ) ;
		return ( RTN_NG ) ;
	}
loging ( "stocker : 共有メモリ[CRT] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n", pAppEnv->shm_Key, pAppEnv->shm_Id, *shmData, shmData ) ;

	//	値設定	
	*shmData = 0 ;

	//	デタッチ	
	if ( shmdt ( shmData ) == -1 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "共有メモリの操作に失敗しました" ) ;
		return ( RTN_NG ) ;
	}
	return ( RTN_OK ) ;
}

/******************************************************************************/
/*  関 数 名　：sFncShmGet()				 								  */
/*  機能概要　：共有メモリ取得								  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体		 		      */
/*　 第２引数 ：int *   			値							 		      */
/*  出　　力　：                                                              */
/*  復帰情報　： RTN_OK		: 成功											  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
static int
sFncShmGet ( pAppEnv, pshmData )
struct appEnv	*pAppEnv ;
int					*pshmData ;
{
	int		*shmData ;

	//	アタッチ	
	shmData = ( int * ) shmat ( pAppEnv->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmat", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "共有メモリの操作に失敗しました" ) ;
		return ( RTN_NG ) ;
	}

	//	値設定	
	*pshmData = *shmData ;

loging ( "stocker : 共有メモリ[GET] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n", pAppEnv->shm_Key, pAppEnv->shm_Id, *shmData, shmData ) ;
	//	デタッチ	
	if ( shmdt ( shmData ) == -1 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "共有メモリの操作に失敗しました" ) ;
		return ( RTN_NG ) ;
	}
	return ( RTN_OK ) ;
}

/******************************************************************************/
/*  関 数 名　：sFncShmDel()				 								  */
/*  機能概要　：共有メモリ削除								  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体。		 		      */
/*  出　　力　：                                                              */
/*  復帰情報　： RTN_OK		: 成功											  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
static int
sFncShmDel ( pAppEnv )
struct appEnv	*pAppEnv ;
{
	int		*shmData ;

loging ( "stocker : 共有メモリ[DEL] shmKey[%d]-ID[%d]\n", pAppEnv->shm_Key, pAppEnv->shm_Id) ;
	//	削除	
	if ( shmctl ( pAppEnv->shm_Id, IPC_RMID, NULL) < 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		//sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmctl", __LINE__,
		//		 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		//		 	 "共有メモリの操作に失敗しました" ) ;
		return ( RTN_NG ) ;
	}
	return ( RTN_OK ) ;
}	
/******************************************************************************/
/*  関 数 名　：sFncPutLog()  			 									  */
/*  機能概要　：アプリケーションログ出力					  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *   	編集文字列								 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：無し														  */
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
	//strcpy ( gstLogMem.pcSrcName, pcSrcName ) ;
	strcpy ( gstLogMem.pcFncName, pcFncName ) ;
	//gstLogMem.lLineNo = plLineNo ;
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
/******************************************************************************/
/*  関 数 名　：_sFncEnvDip()				 								  */
/*  機能概要　：プログラム環境変数出力関数【トレース用】	  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体			 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：無し														  */
/******************************************************************************/
static void
_sFncEnvDip( pAppEnv )
struct appEnv	*pAppEnv ;
{
	int		i ;
#if defined ( _TRACE )
	loging ( "########## SMPR - _sFncEnvDip ##########\n" ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_IA_DAT,     pAppEnv->cDirIA_Dat ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_IA_IDX,     pAppEnv->cDirIA_Idx ) ;
	for ( i = 0 ; i < pAppEnv->CntInfoIA ; i ++ ) {
		loging ( "\t%s : [%s][%s][%s]\n", MYAPP_PRM_IA_SERVER_DIR,  
									      pAppEnv->infoIA[i].smpNo,
									      pAppEnv->infoIA[i].dirIA_DAT,
									      pAppEnv->infoIA[i].dirIA_IDX ) ;
	}
	loging ( "\t【共有メモリ構成】\n" ) ;
	loging ( "\t%s : [%d]\n", MYAPP_PRM_SHM_KEY,		pAppEnv->shm_Key ) ;
	loging ( "\t【通信構成】\n" ) ;
	loging ( "\t%s : [%d]\n", MYAPP_PRM_PORT,			pAppEnv->Port ) ;
	loging ( "\t%s : [%ld]\n", MYAPP_PRM_TIMEOUT_SEC,	pAppEnv->timeout_Sec ) ;
	loging ( "\t%s : [%ld]\n", MYAPP_PRM_TIMEOUT_USEC,	pAppEnv->timeout_uSec) ;
	loging ( "\t【ＤＢ関連構成】\n" ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DB_NAME,        pAppEnv->cDb_Name ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DB_USER,        pAppEnv->cDb_User ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DB_PASSWD,      pAppEnv->cDb_Passwd ) ;
	loging ( "########## Stocker - _sFncEnvDip ##########\n" ) ;
#endif
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
	if ( daemon ( 0, 1 ) < 0 ) {
		exit ( 9 ) ;
	}

	/***
	 ***	初期処理
	 ***/
	if ( initFunction ( argc, argv, &sAppEnv )  != 0 ) {
		fprintf ( stderr,"%s : Error initFunction [%d]\n", MYAPP_APP_NAME, gintErrorCode ) ;
		exit ( 9 ) ;
	}
_sFncEnvDip ( &sAppEnv ) ;

	/***
	 ***	メイン処理	
	 ***/
	if ( mainFunction ( &sAppEnv )  != 0 ) {
		fprintf ( stderr,"%s : Error mainFunction [%d]\n", MYAPP_APP_NAME, gintErrorCode ) ;
		endFunction ( &sAppEnv ) ;
		exit ( 9 ) ;
	}

	/***
	 ***	終了処理
	 ***/
	endFunction ( &sAppEnv ) ;

	exit ( 0 ) ;
}
