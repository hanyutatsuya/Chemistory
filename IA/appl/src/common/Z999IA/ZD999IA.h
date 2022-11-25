/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：ZD999IA.h                                                    */
/* 　概　　　要：ＩＡサーバ監視デーモン                                       */
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

/******************************************************************************/
/* Define定義                                                                */
/******************************************************************************/
#define	MYAPP_APP_NAME			"ZD999IA"
#define	MYAPP_APP_NAME_JP		"ZD999IA"

//	パラメータ文字列
#define	MYAPP_PRM_PORT				"PORT"
#define	MYAPP_PRM_TIMEOUT_SEC		"TIMEOUT_SEC"
#define	MYAPP_PRM_TIMEOUT_USEC		"TIMEOUT_USEC"

#define COMMAND_PS			'0'
#define COMMAND_EXEC_LABO	'1'
#define COMMAND_EXEC_LABO_NYOU	'5'
#define COMMAND_EXEC_BM		'2'
#define COMMAND_KILL		'3'
#define COMMAND_EXEC_BACK	'4'
#define COMMAND_KILL_DM		'Q'

#define	MYAPP_COM_KILL		"/home/kea00sys/bin/ZD999stop"
#define	MYAPP_COM_BACK		"/home/kea00sys/shell/data_back_del.sh"
#define	MYAPP_COM_EXEC_PATH	"/home/kea00sys/appl/bin"
//CHG E.Osada 2006-08-23
//#define	MYAPP_COM_EXEC_LABO	"DD203.a"
//#define	MYAPP_COM_EXEC_BM	"DD201.a"
#define	MYAPP_COM_EXEC_LABO		"DD203"
#define	MYAPP_COM_EXEC_BM		"DD201"
#define	MYAPP_COM_EXEC_LABO_NYOU	"DD204"

//	受信データサイズ
#define MY_COM_SIZE sizeof ( char )

/******************************************************************************/
/* 構造体定義                                                                 */
/******************************************************************************/
// プログラム環境構造体
struct	appEnv	{
	long				 timeout_Sec ;
	long				 timeout_uSec ;
	int				 Port ;
} ;
struct dataRec {
	char	command ;
	char	sts ;
	char	prmBuf[256] ;
} ;
/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/

/******************************************************************************/
/* プロトタイプ宣言                                                           */
/******************************************************************************/
#endif
/** End of File ***************************************************************/
