/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：BD401.h                                                      */
/* 　概　　　要：サンプラーデーモン                                           */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  x.xx     2006/01/15     芳賀弘幸       新規作成                           */
/******************************************************************************/
#ifndef _dmlog_h
#define _dmlog_h
/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <sys/shm.h>
#include "bmlprm.h"
#include "bmllog.h"

/******************************************************************************/
/* Define定義                                                                */
/******************************************************************************/
#define	MYAPP_APP_NAME			"BD401"
#define	MYAPP_APP_NAME_JP		"BD401"
#define	MYAPP_LOGINIFILE		"BD401_LOG.ini"

//  内部ステータスコード定義
typedef enum {
	MYAPP_STSCODE_NML,
	MYAPP_STSCODE_ERR_USEGE,
	MYAPP_STSCODE_ERR_PRM,
	MYAPP_STSCODE_ERR_SHM,
	MYAPP_STSCODE_ERR_DIR,
	MYAPP_STSCODE_ERR_FILE,
	MYAPP_STSCODE_ERR_SOCKET,
	MYAPP_STSCODE_ERR_DATA,
	MYAPP_STSCODE_ERR_FORK,
	MYAPP_STSCODE_ERR_DB
} MYAPP_STSCODE ;

//  エラーコード定義
#define MYAPP_LOG_ERRCODE_NON		"00000000"

//  エラーコード詳細
#define MYAPP_SQL_DEADLOCK          -911
#define MYAPP_SQL_DUPLICATION       -803

//	パラメータ文字列
#define	MYAPP_PRM_DB_NAME			"DB_NAME"
#define	MYAPP_PRM_DB_USER			"DB_USER"
#define	MYAPP_PRM_DB_PASSWD			"DB_PASSWD"
#define	MYAPP_PRM_PORT				"PORT"
#define	MYAPP_PRM_SHM_KEY			"SHM_KEY"
#define	MYAPP_PRM_TIMEOUT_SEC		"TIMEOUT_SEC"
#define	MYAPP_PRM_TIMEOUT_USEC		"TIMEOUT_USEC"
#define	MYAPP_PRM_DIR_IA_DAT		"DIR_IA_DAT"
#define	MYAPP_PRM_DIR_IA_IDX		"DIR_IA_IDX"
#define	MYAPP_PRM_IA_SERVER_DIR		"DIR_IA_SERVER"


//  送信ファイル関連
#define MYAPP_SEND_KIND_OD		"OD"		//検査オーダー情報
#define MYAPP_SEND_KIND_CH		"CH"		//即時チェック情報
#define MYAPP_SEND_SFX          ".dat"
#define MYAPP_SEND_RECSIZE      (512)


//	ディレクトリ格納サイズ
#define	MYAPP_PATH_SIZE			(1024)

//	共有メモリサイズ
#define	MYAPP_SHM_SIZE			sizeof ( int )

//	受信データサイズ
#define MYAPP_RCV_SIZE			(128)

//	データサイズ
#define MYAPP_SMPNO_SIZE		(8+1)
#define MYAPP_RCKNO_SIZE		(10+1)

//	ファイル名長
#define	MYAPP_OD_FILE_LEN		(20)
#define	MYAPP_CH_FILE_LEN		(20)

//#define	MYAPP_OD_FILE_LEN		(33)
//#define	MYAPP_CH_FILE_LEN		(33)

//	コマンド定義
#define	MYAPP_COMMAND_MV		"/bin/mv"
#define	MYAPP_COMMAND_CP		"/bin/cp"

/******************************************************************************/
/* 構造体定義                                                                 */
/******************************************************************************/
// ＩＡサーバ情報格納構造体
struct	my_infoIA	{
	char	smpNo[MYAPP_SMPNO_SIZE] ;
	char	dirIA_DAT[MYAPP_PATH_SIZE] ;
	char	dirIA_IDX[MYAPP_PATH_SIZE] ;
} ;

// プログラム環境構造体
struct	appEnv	{
	int					 shm_Id ;
	key_t				 shm_Key ;
	long				 timeout_Sec ;
	long				 timeout_uSec ;
	int					 Port ;
	char				 cDb_Name[32+1] ; 
	char				 cDb_User[32+1] ; 
	char				 cDb_Passwd[32+1] ; 
	char				 cDirIA_Dat[MYAPP_PATH_SIZE] ;
	char				 cDirIA_Idx[MYAPP_PATH_SIZE] ;
	int					 CntInfoIA ;
	struct my_infoIA	*infoIA ;
} ;


/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/

/******************************************************************************/
/* プロトタイプ宣言                                                           */
/******************************************************************************/
void    sFncPutLog ( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... )  ;
#endif
/** End of File ***************************************************************/
