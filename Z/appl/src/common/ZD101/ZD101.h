/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：ZD101.h                                                      */
/* 　概　　　要：ログデータベース出力デーモン                                 */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  x.xx     2006/01/15     芳賀弘幸       新規作成                           */
/******************************************************************************/
#ifndef _stocker_h
#define _stocker_h
/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/

/******************************************************************************/
/* Define定義                                                                */
/******************************************************************************/
//	アプリケーション名
#define	MYAPP_APP_NAME			"ZD101"

//	パラメータ文字列
#define	MYAPP_PRM_DB_NAME		"DB_NAME"
#define	MYAPP_PRM_DB_USER		"DB_USER"
#define	MYAPP_PRM_DB_PASSWD		"DB_PASSWD"
#define	MYAPP_PRM_DIR_WATCH		"DIR_WATCH"
#define MYAPP_PRM_SHM_KEY		"SHM_KEY"
#define MYAPP_PRM_SLEEP_SEC		"SLEEP_SEC"

//	ディレクトリ格納サイズ
#define	MYAPP_PATH_SIZE			(1024)

//	共有メモリサイズ
#define	MYAPP_SHM_SIZE			sizeof ( int )
#define	MYAPP_LOG_SFX			".log"

//  内部ステータスコード定義
typedef enum {
	MYAPP_STSCODE_NORMAL,
	MYAPP_STSCODE_ERR_USEGE,
	MYAPP_STSCODE_ERR_PRM,
	MYAPP_STSCODE_ERR_SHM,
	MYAPP_STSCODE_ERR_DIR,
	MYAPP_STSCODE_ERR_DB,
	MYAPP_STSCODE_ERR_FILE
} MYAPP_STSCODE ;


/******************************************************************************/
/* 構造体定義                                                                 */
/******************************************************************************/
// プログラム環境構造体
struct	appEnv	{
	char				*pcFielNamePRM ;
	int					 shm_Id ;
	key_t				 shm_Key ;
	int					 sleep_Sec ;
	char				 cDb_Name[32+1] ; 
	char				 cDb_User[32+1] ; 
	char				 cDb_Passwd[32+1] ; 
	char				 cDir_Watch[MYAPP_PATH_SIZE] ;
} ;


/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/

/******************************************************************************/
/* プロトタイプ宣言                                                           */
/******************************************************************************/
#endif
/** End of File ***************************************************************/
