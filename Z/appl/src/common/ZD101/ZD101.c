/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：ZD101.c                                                      */
/* 　概　　　要：ログデータベース出力デーモン                                 */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/15     芳賀弘幸       新規作成                           */
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
#include <syslog.h>

#include "bmlprm.h"
#include "bmllog.h"
#include "bml_misc.h"
#include "bml_misc.h"
#include "bml_date.h"
#include "ZD101.h"

/******************************************************************************/
/* Define定義                                                                 */
/******************************************************************************/
//	TRACE
#if defined ( _TRACE )
#define malloc(a)   _malloc(a, __FILE__, __LINE__)
#define free(p)     _free(p, __FILE__, __LINE__)
#endif

//  フラグ定義
typedef enum {
    LC_false,
    LC_true
} LC_BOOLEAN ;

/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/
MYAPP_STSCODE			 gintErrorCode ;

/******************************************************************************/
/* 関数宣言                                                                   */
/******************************************************************************/
//	ＤＢ出力関数
static	int		sFncDbWrite ( char * ) ;

//	共有メモリ操作関数
static	int		sFncShmCrt ( struct appEnv * ) ;
static	int		sFncShmGet ( struct appEnv * , int *) ;
static	int		sFncShmDel ( struct appEnv * ) ;

//	コールバック関数
static	int		sFncFileFillter ( struct dirent * ) ;

//	システムログ出力
static	void	sFncSyslog ( int, char *, char * ) ;

//	トレース用
static	void	_sFncApllogDisp ( struct stcLogAPLLOG * ) ;

/******************************************************************************/
/*  関 数 名　：initFunction()												  */
/*  機能概要　：初期処理関数												  */
/*  入　　力　：                                                              */
/*　 第１引数 ：int				   	メインパラメータ数						  */
/*　 第２引数 ：char *   			メインパラメータ						  */
/*　 第３引数 ：struct	appEnv *   	プログラム環境構造体		 			  */
/*  出　　力　：                                                              */
/*  復帰情報　：  0     : 成功												  */
/* 　　　　　　　-1     : 失敗												  */
/******************************************************************************/
int
initFunction( argc, argv, pAppEnv )
int					 argc ;
char				*argv[] ;
struct appEnv	*pAppEnv ;
{
	long	 ll_retSts ;
	BMLPRM	*bp ;
	char	 lc_prmBuf[256] ;
	char	 lc_logBuf[1024] ;

	/***
	 ***	初期化	
	 ***/
	//	エラーステータス変更
	gintErrorCode = 0 ;

	//	プログラム環境変数初期化
	memset ( pAppEnv , '\0', sizeof ( struct appEnv ) ) ;


	/***
	 ***	引数チェック	
	 ***/
	//	引数数チェック	
	if ( argc != 2 ) {
		//	異常終了	LOG
		sFncSyslog ( LOG_ERR, "", "A parameter file is not appointed." ) ;
		return ( -1 ) ;
	}

	/***
	 ***	パラメータファイル情報退避
	 ***/
	//	パラメータファイルオープン	
	bp = ZbmlPrmOpen ( argv[1] ) ;		
	if ( bp == NULL ) {
		gintErrorCode = MYAPP_STSCODE_ERR_PRM;
		sprintf ( lc_logBuf, "Parameter file cannot open.[%s]", argv[1] ) ;
		sFncSyslog ( LOG_ERR, "ZbmlPrmOpen()", lc_logBuf ) ;
		return ( -1 ) ;
	}

	//	データベース名
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_DB_NAME, 
						pAppEnv->cDb_Name ) != 0 ) {
		gintErrorCode = MYAPP_STSCODE_ERR_PRM;
		sprintf ( lc_logBuf, "Failed in the acquisition of a parameter value.[%s]", MYAPP_PRM_DB_NAME ) ;
		sFncSyslog ( LOG_ERR, "ZbmlPrmGetVal()", lc_logBuf ) ;
		return ( -1 ) ;
	}
	//	ユーザ名	
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_DB_USER, 
						pAppEnv->cDb_User ) != 0 ) {
		gintErrorCode = MYAPP_STSCODE_ERR_PRM;
		sprintf ( lc_logBuf, "Failed in the acquisition of a parameter value.[%s]", MYAPP_PRM_DB_USER ) ;
		sFncSyslog ( LOG_ERR, "ZbmlPrmGetVal()", lc_logBuf ) ;
		return ( -1 ) ;
	}
	//	パスワード名
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_DB_PASSWD, 
						pAppEnv->cDb_Passwd ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM;
		sprintf ( lc_logBuf, "Failed in the acquisition of a parameter value.[%s]", MYAPP_PRM_DB_PASSWD ) ;
		sFncSyslog ( LOG_ERR, "ZbmlPrmGetVal()", lc_logBuf ) ;
		return ( -1 ) ;
	}
	//	監視ディレクトリ	
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_DIR_WATCH, 
						pAppEnv->cDir_Watch ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM;
		sprintf ( lc_logBuf, "Failed in the acquisition of a parameter value.[%s]", MYAPP_PRM_DIR_WATCH ) ;
		sFncSyslog ( LOG_ERR, "ZbmlPrmGetVal()", lc_logBuf ) ;
		return ( -1 ) ;
	}
	//	共有メモリキー取得
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_SHM_KEY, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM;
		sprintf ( lc_logBuf, "Failed in the acquisition of a parameter value.[%s]", MYAPP_PRM_SHM_KEY ) ;
		sFncSyslog ( LOG_ERR, "ZbmlPrmGetVal()", lc_logBuf ) ;
		return ( -1 ) ;
	}
	pAppEnv->shm_Key = atoi ( lc_prmBuf ) ;
	//	SLEEPSEC取得
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_SLEEP_SEC, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM;
		sprintf ( lc_logBuf, "Failed in the acquisition of a parameter value.[%s]", MYAPP_PRM_SLEEP_SEC ) ;
		sFncSyslog ( LOG_ERR, "ZbmlPrmGetVal()", lc_logBuf ) ;
		return ( -1 ) ;
	}
	pAppEnv->sleep_Sec= atoi ( lc_prmBuf ) ;

	//	パラメータファイルクローズ	
	ZbmlPrmClose ( bp ) ;

	/***
	 ***	共有メモリ生成	
	 ***/
	if ( sFncShmCrt ( pAppEnv ) < 0 ) {
		return ( -1 ) ;
	}

	/***
	 ***	データベースオープン
	 ***/
	ll_retSts = ZdbConnect( pAppEnv->cDb_Name, 
							pAppEnv->cDb_User, pAppEnv->cDb_Passwd ) ;
	if ( ll_retSts != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_DB ;
		sprintf ( lc_logBuf, "Cannot be connected to a database.[DB=%s USR=%s PASS=%s]", pAppEnv->cDb_Name, pAppEnv->cDb_User, pAppEnv->cDb_Passwd ) ;
		sFncSyslog ( LOG_ERR, "ZdbConnect()", lc_logBuf ) ;
		return ( -1 ) ;
	}

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
/******************************************************************************/
int
mainFunction( pAppEnv )
struct appEnv	*pAppEnv ;
{
	int					  li_retSts ;
	long				  ll_retSts ;

	int					  li_idx ;	
	int					  li_stopFlg ;

	//	ディレクトリ情報 
	DIR					 *lt_dp ;
	struct dirent		**lpst_dirBuf ;
	int					  li_fileCnt ;				
	char				  lc_fileName[1024] ;
	struct stat			  lst_statBuf ;
	char	 			  lc_logBuf[1024] ;


	/***
	 ***	ログ情報ディレクトリ監視	
	 ***		永久ループ
	 ***		停止コマンドで終了
	 ***/
	while ( 1 ) {

		//	ファイル名取得
		if ( ( li_fileCnt = scandir ( pAppEnv->cDir_Watch, 
									  &lpst_dirBuf,
									  (void*)sFncFileFillter,
					   				  alphasort ) ) < 0 ) {
			//	異常終了	LOG
			gintErrorCode = MYAPP_STSCODE_ERR_DIR;
			sFncSyslog ( LOG_ERR, "scandir()", "Cannot acquire a file name." ) ;
			return ( -1 ) ;
		}

		//	ＤＢ出力ループ
		for ( li_idx = 0 ; li_idx < li_fileCnt ; li_idx ++ ) {
			sprintf ( lc_fileName, "%s/%s", pAppEnv->cDir_Watch, 
											lpst_dirBuf[li_idx]->d_name ) ;

			//  通常ファイルのみ処理を行う
			if ( stat ( lc_fileName, &lst_statBuf ) < 0 ) {
				//  異常終了    LOG
				gintErrorCode = MYAPP_STSCODE_ERR_DIR;
				sFncSyslog ( LOG_ERR, "stat()", "Cannot acquire a file information." ) ;
				return ( -1 ) ;
			}
			if ( !S_ISREG ( lst_statBuf.st_mode ) ) {
				continue ;
			}

			if ( sFncDbWrite ( lc_fileName ) < 0 ) {
loging ( "ロールバック\n" ) ;
				ZdbRollback () ;					//	ロールバック
			} else {
loging ( "コミット\n" ) ;
				ZdbCommit () ; 						//	コミット
				unlink ( lc_fileName ) ;			//	ファイル削除
			}
				
			//	解放
			free ( lpst_dirBuf[li_idx] ) ;

			//	
			if ( sFncShmGet ( pAppEnv, &li_stopFlg ) < 0 ) {
				return ( -1 ) ;
			}
			if ( li_stopFlg == 1 ) {
				break ;
			}
		}
//break ;

		/***
		 *** 停止コマンド確認
		 ***/
		if ( sFncShmGet ( pAppEnv, &li_stopFlg ) < 0 ) {
			return ( -1 ) ;
		}
		if ( li_stopFlg == 1 ) {
			break ;
		}

		/***
		 *** スリープ
		 ***/
		sleep ( pAppEnv->sleep_Sec ) ;
	}


	return ( 0 ) ;
}
/******************************************************************************/
/*  関 数 名　：endFunction()												  */
/*  機能概要　：終了処理関数												  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct	env *   	プログラム環境構造体。		 			  */
/*  出　　力　：                                                              */
/*  復帰情報　：  0     : 成功												  */
/* 　　　　　　　-1     : 失敗												  */
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
	if ( sFncShmDel ( pAppEnv ) < 0 ) {
		return ;
	}
	
	return ;
}
/******************************************************************************/
/*  関 数 名　：sFncDbWrite()			 									  */
/*  機能概要　：データベース出力							  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *			   		ファイル名							  */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
/******************************************************************************/
static	int
sFncDbWrite ( pc_trFileName )
char			*pc_trFileName ;
{
	FILE				*lfp ;
	long				 ll_retSts ;
	char				 lc_logBuf[1024] ;
	struct stcLogAPLLOG  recAPLLOG ;

	//	オープン	
	lfp  = fopen ( pc_trFileName, "rb" ) ;
	if ( lfp == NULL ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
		sprintf ( lc_logBuf, "Cannot open a file .[%s]",pc_trFileName ) ;
		sFncSyslog ( LOG_ERR, "fopen()", lc_logBuf ) ;
		return ( -1 ) ;
	}

	//	ＤＢ出力ループ
	while ( 1 ) {
		if ( fread ( &recAPLLOG, sizeof ( recAPLLOG ), 1, lfp ) < 1 ) {
			if ( ferror ( lfp ) ) {
				gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
				sprintf ( lc_logBuf, "Cannot read a file .[%s]", pc_trFileName ) ;
				sFncSyslog ( LOG_ERR, "fread()", lc_logBuf ) ;
				fclose ( lfp ) ;
				return ( -1 ) ;
			}
			if ( feof ( lfp ) ) {
				break ;
			}
		}
_sFncApllogDisp ( &recAPLLOG ) ;
		ll_retSts = sFncInsKENPOS ( &recAPLLOG )  ;
		if ( ll_retSts != 0 ) {
			gintErrorCode = MYAPP_STSCODE_ERR_DB ;
			sFncSyslog ( LOG_ERR, "sFncInsKENPOS()", "Cannot insert Apllog." ) ;
			fclose ( lfp ) ;
			return ( -1 ) ;
		}
	}
	
	//	クローズ	
	fclose ( lfp ) ;

	//	コミット

	return ( 0 ) ;
}
/******************************************************************************/
/*  関 数 名　：sFncSyslog()				 								  */
/*  機能概要　：システムログ出力							  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：int 			   	プライオリティー						  */
/*　 第２引数 ：char *   			関数名									  */
/*　 第３引数 ：char * 		  		メッセージ								  */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
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
/*  関 数 名　：sFncShmCrt()				 								  */
/*  機能概要　：共有メモリ生成								  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体		 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
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
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		sFncSyslog ( LOG_ERR, "shmget()", "Cannot assign shared memory." ) ;
		return ( -1 ) ;
	}

	//	アタッチ	
	shmData = ( int * ) shmat ( pAppEnv->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		sFncSyslog ( LOG_ERR, "shmat()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}
loging ( "%s : 共有メモリ[CRT] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n", MYAPP_APP_NAME, pAppEnv->shm_Key, pAppEnv->shm_Id, *shmData, shmData ) ;

	//	値設定	
	*shmData = 0 ;

	//	デタッチ	
	if ( shmdt ( shmData ) == -1 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		sFncSyslog ( LOG_ERR, "shmdt()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*  関 数 名　：sFncShmGet()				 								  */
/*  機能概要　：共有メモリ取得								  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体			 	      */
/*　 第２引数 ：int *   			値								 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
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
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		sFncSyslog ( LOG_ERR, "shmat()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}

	//	値設定	
	*pshmData = *shmData ;

loging ( "%s : 共有メモリ[GET] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n", MYAPP_APP_NAME, pAppEnv->shm_Key, pAppEnv->shm_Id, *shmData, shmData ) ;
	//	デタッチ	
	if ( shmdt ( shmData ) == -1 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		sFncSyslog ( LOG_ERR, "shmdt()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*  関 数 名　：sFncShmDel()				 								  */
/*  機能概要　：共有メモリ削除								  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体			 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
/******************************************************************************/
static int
sFncShmDel ( pAppEnv )
struct appEnv	*pAppEnv ;
{
	int		*shmData ;

loging ( "%s : 共有メモリ[DEL] shmKey[%d]-ID[%d]\n", MYAPP_APP_NAME, pAppEnv->shm_Key, pAppEnv->shm_Id) ;
	//	削除	
	if ( shmctl ( pAppEnv->shm_Id, IPC_RMID, NULL) < 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		sFncSyslog ( LOG_ERR, "shmctl()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
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
		int		li_len ;


		//ファイルタイプチェック
/*
		if ( pdirEnt->d_type != DT_REG ) {
			return ( 0 ) ;
		}	
*/

		//文字列長
		li_len = strlen ( pdirEnt->d_name )  ;

		//拡張子チェック
		if ( memcmp ( &(pdirEnt->d_name[li_len-strlen(MYAPP_LOG_SFX)]), 
					  MYAPP_LOG_SFX, 
					  strlen ( MYAPP_LOG_SFX ) ) != 0 ) {
			return ( 0 ) ;
		}
		return ( 1 ) ;
}

/******************************************************************************/
/*  関 数 名　：_sFncEnvDip()				 								  */
/*  機能概要　：プログラム環境変数出力関数【トレース用】	  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体。		 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：無し														  */
/******************************************************************************/
static void
_sFncEnvDip( pAppEnv )
struct appEnv	*pAppEnv ;
{
#if defined ( _TRACE )
loging ( "########## %s  - パラメータ ##########\n", MYAPP_APP_NAME ) ;
loging ( "\t%s : [%s]\n", MYAPP_PRM_DB_NAME,   pAppEnv->cDb_Name ) ;
loging ( "\t%s : [%s]\n", MYAPP_PRM_DB_USER,   pAppEnv->cDb_User ) ;
loging ( "\t%s : [%s]\n", MYAPP_PRM_DB_PASSWD, pAppEnv->cDb_Passwd ) ;
loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_WATCH, pAppEnv->cDir_Watch ) ;
loging ( "\t%s : [%d]\n", MYAPP_PRM_SHM_KEY,   pAppEnv->shm_Key ) ;
loging ( "\t%s : [%d]\n", MYAPP_PRM_SLEEP_SEC, pAppEnv->sleep_Sec ) ;
loging ( "########## %s  - パラメータ ##########\n", MYAPP_APP_NAME ) ;
#endif
}
/******************************************************************************/
/*  関 数 名　：_sFncKenorderDisp()			 								  */
/*  機能概要　：検査オーダー情報出力関数【トレース用】  					  */
/*  入　　力　：                                                              */
/*　 第１引数 ：Kenorder *   	検査オーダー情報構造体				 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：無し														  */
/******************************************************************************/
static void
_sFncApllogDisp ( precApllog )
struct stcLogAPLLOG	*precApllog ;
{
#if defined ( _TRACE )
loging ( "#################################################################\n" ) ;
loging ( "# sydate      : [%s]\n",  precApllog->sydate ) ;
loging ( "# sytime      : [%s]\n",  precApllog->sytime ) ;
loging ( "# tracekbn    : [%c]\n",  precApllog->tracekbn ) ;
loging ( "# pcname      : [%s]\n",  precApllog->pcname ) ;
loging ( "# proccessid  : [%ld]\n", precApllog->proccessid ) ;
loging ( "# loginid     : [%s]\n",  precApllog->loginid ) ;
loging ( "# wkupapp     : [%s]\n",  precApllog->wkupapp ) ;
loging ( "# srcname     : [%s]\n",  precApllog->srcname ) ;
loging ( "# funcname    : [%s]\n",  precApllog->funcname ) ;
loging ( "# getline     : [%d]\n",  precApllog->getline ) ;
loging ( "# procflg     : [%s]\n",  precApllog->procflg ) ;
loging ( "# errcode     : [%s]\n",  precApllog->errcode ) ;
loging ( "# message     : [%s]\n",  precApllog->message.data ) ;
#endif
}

/******************************************************************************/
/*  関 数 名　：main()														  */
/*  機能概要　：メイン関数													  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *pcLogName    	【任意】ログファイル名を指定する。		  */
/*									※NULLを指定した場合はINIファイルより	  */
/*									  ログ情報を取得する。					  */
/*  出　　力　：                                                              */
/*  復帰情報　：  0     : 成功												  */
/* 　　　　　　　-1     : 失敗												  */
/******************************************************************************/
int 
main( argc, argv )
int		 argc ;
char	*argv[] ;
{

	struct appEnv	 sEnv ;

	/***
	 ***	バックグラウンド実行
	 ***/
	if ( daemon ( 1, 0 ) < 0 ) {
		exit ( 9 ) ;
	}

	/***
	 ***	初期処理	
	 ***/
	if ( initFunction ( argc, argv, &sEnv )  != 0 ) {
		fprintf ( stderr, "%s : Error initFunction [%d]\n", MYAPP_APP_NAME, gintErrorCode ) ;
		exit ( 9 ) ;
	}
	_sFncEnvDip ( &sEnv ) ;
	
	/***
	 ***	主処理	
	 ***/
	if ( mainFunction ( &sEnv )  != 0 ) {
		fprintf ( stderr, "%s : Error mainFunction [%d]\n", MYAPP_APP_NAME, gintErrorCode ) ;
		exit ( 9 ) ;
	}

	/***
	 ***	終了処理	
	 ***/
	endFunction ( &sEnv ) ;
	fprintf ( stderr, "%s : Error mainFunction [%d]\n", MYAPP_APP_NAME, gintErrorCode ) ;
}

/** End of File ***************************************************************/
