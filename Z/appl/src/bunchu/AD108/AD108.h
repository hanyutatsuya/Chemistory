/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：AD108.h                                                      */
/* 　概　　　要：３ＩＤ情報展開                                               */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2008/02/12     moriya         新規作成                           */
/*  1.01     2008/11/13     sekiya         薬剤ＷＳの並び順がおかしくなること */
/*                                         に対する対応                       */
/*  1.02     2008/12/22     sekiya         SKIPファイルを出力している時に、   */
/*                                         AD107がアクセスしないように        */
/*                                         １度、tmpに出力してリネームする    */
/*                                         ように仕様を変更                   */
/******************************************************************************/
#ifndef _stocker_h
#define _stocker_h
/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <sys/shm.h>
#include "bmlprm.h"
#include "bmllog.h"
#include "bml_DBCom.h"

/******************************************************************************/
/* Define定義                                                                */
/******************************************************************************/
#define	MYAPP_APP_NAME			"AD108"
#define	MYAPP_APP_NAME_JP		"AD108"
#define	MYAPP_LOGINIFILE		"/home/kea00sys/bin/AD108_LOG.ini"
#define	MYAPP_AD105SORTINIFILE	"/home/kea00sys/bin/AD105_SORT.ini"

//  内部ステータスコード定義
typedef enum {
	MYAPP_STSCODE_NML,
	MYAPP_STSCODE_ERR_USEGE,
	MYAPP_STSCODE_ERR_PRM,
	MYAPP_STSCODE_ERR_SHM,
	MYAPP_STSCODE_ERR_DIR,
	MYAPP_STSCODE_ERR_TR_FILE,
	MYAPP_STSCODE_ERR_DB,
	MYAPP_STSCODE_NML_START,
	MYAPP_STSCODE_NML_END
} MYAPP_STSCODE ;

//	エラーコード定義
#define	MYAPP_LOG_ERRCODE_NON		"00000000"

//	エラーコード詳細
#define MYAPP_SQL_DEADLOCK			-911
#define MYAPP_SQL_DUPLICATION		-803
#define MYAPP_SQL_NOTFOUND			100

//	次世代システム切替定義
typedef enum {
	MYAPP_SYSTEM_NEW,
	MYAPP_SYSTEM_OLD
} MYAPP_SYSTEM_VERSION ;

//	パラメータ文字列
#define	MYAPP_PRM_DIR_3ID			"DIR_3ID"
#define	MYAPP_PRM_DIR_3ID_OK		"DIR_3ID_OK"
#define	MYAPP_PRM_DIR_3ID_NG		"DIR_3ID_NG"
#define	MYAPP_PRM_DIR_3ID_SKIP		"DIR_3ID_SKIP"
#define	MYAPP_PRM_SHM_KEY			"SHM_KEY"
#define	MYAPP_PRM_SLEEP_SEC			"SLEEP_SEC"
#define	MYAPP_PRM_DB_NAME			"DB_NAME"
#define	MYAPP_PRM_DB_USER			"DB_USER"
#define	MYAPP_PRM_DB_PASSWD			"DB_PASSWD"
#define	MYAPP_PRM_LABOCD			"LABOCD"
#define	MYAPP_PRM_SATECD			"SATECD"
#define	MYAPP_PRM_FILE_RETRY		"FILE_RETRY"


//	ディレクトリ格納サイズ
#define	MYAPP_PATH_SIZE			(1024)

//	共有メモリサイズ
#define	MYAPP_SHM_SIZE			sizeof ( int )

//	受信ファイル関連
#define	MYAPP_RECV_KIND_POS		"POS"
#define	MYAPP_RECV_KIND_SKIP	"SKIP"
/* 1.02 一時ファイルの出力名 */
#define MYAPP_RECV_KIND_TMP    "TMP"
#define	MYAPP_RECV_SFX			".dat"
#define	MYAPP_RECV_RECSIZE		(512)
#define	MYAPP_RECV_COLCNT		(23)
#define	MYAPP_RACK_MAXCNT		(20)

//  送信ファイル関連
#define MYAPP_SEND_KIND_OD		"OD"		//検査オーダー情報
#define MYAPP_SEND_KIND_CH		"CH"		//即時チェック情報
#define MYAPP_SEND_SFX          ".dat"

//	データサイズ
#define	MYAPP_TRNO_SIZE			(10+1)	
#define	MYAPP_STKNO_SIZE		(6+1)	
#define	MYAPP_DATE_SIZE			(10+1)	
#define	MYAPP_RKNO_SIZE			(10+1)	
#define	MYAPP_DEOF_SIZE			(20+1)	

//	次世代システム
#define	MYAPP_VERSION			"NEXTGENE"

#define	MYAPP_COMMAND_RM		"/bin/rm"

#define		RECLEN_3RDID		65		/* １レコード長	*/

#define		RECEND_3RDID		"END"	/* ＥＮＤレコード	*/


/******************************************************************************/
/* 構造体定義                                                                 */
/******************************************************************************/
/* AD105_SORT.iniファイル用構造体 */
typedef struct {
	char	sData[4+1] ;
	char	sKey[3+1] ;
} BUNSORT;

// プログラム環境構造体
struct	appEnv	{
	BMLPRM				*bp	;
	char				*pcFielNamePRM ;
	int					 fileRetry ;
	int					 shm_Id ;
	key_t				 shm_Key ;
	int					 sleep_Sec ;
	char				 cDb_Name[32+1] ;
	char				 cDb_User[32+1] ;
	char				 cDb_Passwd[32+1] ;
	char				 cLbcd[3+1] ;
	char				 cSateid[3+1] ;
	char	 			 cDir3Id[MYAPP_PATH_SIZE] ;
	char				 cDir3IdOk[MYAPP_PATH_SIZE] ;
	char				 cDir3IdNg[MYAPP_PATH_SIZE] ;
	char				 cDir3IdSkip[MYAPP_PATH_SIZE] ;
	int					 pSortNo ;
	BUNSORT				*pSort ;
} ;

/* 受信ファイルのデータレコード(固定長) */
typedef struct {
	char	cUtkymd[8] ;
	char	cIrino[11] ;
	char	cSriymd[8] ;
	char	cKntno[11] ;
	char	cRackId[8] ;
	char	cRackPos[3] ;
	char	cYobi[15] ;
	char	cLf[1] ;
} ID3Info;

/* テーブル更新用構造体 */
/* サンプリングコードをみることになったので */
/* ソートキーのみ、別に構造体を作成した */
typedef struct {
	char	cUtkymd[8+1] ;
	char	cIrino[11+1] ;
	char	cSriymd[8+1] ;
	char	cKntno[11+1] ;
	char	cRackId[8+1] ;
	char	cRackPos[3+1] ;
	char	cYobi[15+1] ;
	char	cLf[1+1] ;
} ID3TB;

/* ソートキー更新用構造体 */
typedef struct {
	char	cSmpcd[7+1] ;
	char	cBnckka ;
	int     iSrtkey ;
} SORTInfo;


/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/

/******************************************************************************/
/* プロトタイプ宣言                                                           */
/******************************************************************************/
void    sFncPutLog ( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... )  ;
#endif
/** End of File ***************************************************************/
