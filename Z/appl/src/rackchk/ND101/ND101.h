/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：ND101.h                                                      */
/* 　概　　　要：パラメータ取得ヘッダ                                         */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/******************************************************************************/
#ifndef _ND101_h
#define _ND101_h
/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <sys/shm.h>
#include <stdbool.h>

#include "bmlprm.h"
#include "bmllog.h"
#include "bml_dbrc.h"
#include "bml_DBCom.h"
#include "bml_misc.h"
#include "bml_date.h"

#include "sql.h"

/******************************************************************************/
/* Define定義                                                                */
/******************************************************************************/
#define	MYAPP_APP_NAME			"ND101"

//  内部ステータスコード定義
typedef enum {
	MYAPP_STSCODE_NML,
	MYAPP_STSCODE_ERR_USEGE,
	MYAPP_STSCODE_ERR_PRM,
	MYAPP_STSCODE_ERR_SHM,
	MYAPP_STSCODE_ERR_DIR,
	MYAPP_STSCODE_ERR_FILE,
	MYAPP_STSCODE_ERR_DB,
	MYAPP_STSCODE_NML_START,
	MYAPP_STSCODE_NML_END
} MYAPP_STSCODE ;

//	エラーコード定義
#define	MYAPP_LOG_ERRCODE_NON	"00000000"
#define	MYAPP_LOG_ERRCODE_APP	"010"
#define	MYAPP_LOG_ERRCODE_DB	"020"
#define	MYAPP_LOG_ERRCODE_ETC	"0Z0"

//	エラーコード詳細
#define MYAPP_SQL_DEADLOCK	-911
#define MYAPP_SQL_DUPLICATION	-803

//	パラメータ文字列
#define	MYAPP_PRM_SHM_KEY	"SHM_KEY"
#define	MYAPP_PRM_DB_NAME	"DB_NAME"
#define	MYAPP_PRM_DB_USER	"DB_USER"
#define	MYAPP_PRM_DB_PASSWD	"DB_PASSWD"
#define MYAPP_PRM_DIR_INPUT	"INPUT_DIR"
#define MYAPP_PRM_DIR_OK	"END_DIR_OK"
#define MYAPP_PRM_DIR_NG	"END_DIR_NG"
#define MYAPP_PRM_DIR_SKIP	"END_DIR_SKIP"
#define MYAPP_PRM_FILE_EXT	"FILE_EXT"
#define MYAPP_PRM_FILE_EXT_TRG	"FILE_EXT_TRG"
#define MYAPP_PRM_SKIP_FILE_PRE	"SKIP_FILE_PRE"

//	ＥＮＤレコード定義
#define MYAPP_RECORD_END	"END"

//	ディレクトリ格納サイズ
#define	MYAPP_PATH_SIZE		(1024)

//	最大レコード長
#define MYAPP_RECORD_SIZE	1024

//	共有メモリサイズ
#define	MYAPP_SHM_SIZE		sizeof ( int )

/******************************************************************************/
/* 構造体定義                                                                 */
/******************************************************************************/
// プログラム環境構造体
struct	appEnv {
	BMLPRM	*bp	;
	char	*pcFielNamePRM ;
	int	 shm_Id ;
	key_t	 shm_Key ;
	char	 cInputDir[MYAPP_PATH_SIZE] ;
	char	 cEndFileDirOK[MYAPP_PATH_SIZE] ;
	char	 cEndFileDirNG[MYAPP_PATH_SIZE] ;
	char	 cEndFileDirSKIP[MYAPP_PATH_SIZE] ;
	char	 cFileExt[MYAPP_PATH_SIZE] ;
	char	 cFileExtTrg[MYAPP_PATH_SIZE] ;
	char	 cSkipFilePre[MYAPP_PATH_SIZE] ;
	char	 cDb_Name[32+1] ; 
	char	 cDb_User[32+1] ; 
	char	 cDb_Passwd[32+1] ; 
} pAppEnv;
/******************************************************************************/
/* ファイル構造体定義                                                           */
/******************************************************************************/
// <<   フロンティアラック情報ファイル      >>
typedef struct file_fronrack {
	char	sriymd[10+1];
	char	hkkbn[3+1];
	char	asyrckid[10+1];
	char	irino[11+1];
} my_stFileFRONRACK;

/******************************************************************************/
/* データ構造体定義                                                           */
/******************************************************************************/
// <<   フロンティアラック情報テーブル      >>
typedef struct	db_fronrack {
	char	knskisymd[10+1];
	char	asyrckid[10+1];
	int	asyrckpos;
	char	utkymd[10+1];
	char	irino[11+1];
	char	knsgrp[16+1];
	char	hkkbn[3+1];
	char	ksndh[26+1];
	char	trkdh[26+1];
} my_stDbFRONRACK;

/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/

/******************************************************************************/
/* プロトタイプ宣言                                                           */
/******************************************************************************/
void    sFncPutLog ( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... )  ;

int	sFncGetFileRecord( char *, my_stFileFRONRACK * );
int	sFncSelKenOrder( char *, char *, char *, my_stDbFRONRACK **, int * );
int	sFncInsFronRack( my_stDbFRONRACK * );
int	sFncMakeEndFileName( char *, char *, char *, char * ) ;
int	sFncMakeSkipFile( char *, char *, char * );
int	sFncInsEnd( char *, char *, char * );

int	mainProc( FILE *, bool, int * );

/** End of File ***************************************************************/

#endif
