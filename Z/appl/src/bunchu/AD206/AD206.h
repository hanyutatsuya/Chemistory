/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：AD206.h                                                      */
/* 　概　　　要：緊急分注結果レイアウト変換処理                               */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  x.xx     2007/06/01     INTEC          新規作成                           */
/*  1.00     2009/01/06     Merits K.Ameno 施設コード増桁 通信仕様変更対応    */
/******************************************************************************/
#ifndef _AD206_H
#define _AD206_H
/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <sys/shm.h>
#include "bmlprm.h"
#include "bmllog.h"
#include "Sysknrmst.h"

#include "tagDB.h"
/******************************************************************************/
/* Define定義                                                                */
/******************************************************************************/
#define	MYAPP_APP_NAME			"AD206"
#define	MYAPP_APP_NAME_JP		"AD206"
#define	MYAPP_LOGINIFILE		"AD206_LOG.ini"

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
#define MYAPP_SQL_DEADLOCK          -911
#define MYAPP_SQL_DUPLICATION       -803

//	次世代システム切替定義
typedef enum {
	MYAPP_SYSTEM_NEW,
	MYAPP_SYSTEM_OLD
} MYAPP_SYSTEM_VERSION ;

//	パラメータ文字列
#define	MYAPP_PRM_DIR_BUNCHU		"DIR_BUNCHU"
#define	MYAPP_PRM_DIR_BUNCHU_OK		"DIR_BUNCHU_OK"
#define	MYAPP_PRM_DIR_BUNCHU_ERR	"DIR_BUNCHU_ERR"
#define	MYAPP_PRM_DIR_NR_LOG		"DIR_NR_LOG"		//未使用
#define	MYAPP_PRM_DIR_TRAY_INFO		"DIR_TRAY_INFO"
#define	MYAPP_PRM_DIR_TRAY_INFO_OK	"DIR_TRAY_INFO_OK"
#define	MYAPP_PRM_DIR_TRAY_INFO_NG	"DIR_TRAY_INFO_NG"
#define	MYAPP_PRM_SHM_KEY			"SHM_KEY"
#define	MYAPP_PRM_SLEEP_SEC			"SLEEP_SEC"
#define	MYAPP_PRM_DB_NAME			"DB_NAME"
#define	MYAPP_PRM_DB_USER			"DB_USER"
#define	MYAPP_PRM_DB_PASSWD			"DB_PASSWD"
#define	MYAPP_PRM_VERSION			"VERSION"			//未使用
#define	MYAPP_PRM_DIR_IA_DAT		"DIR_IA_DAT"
#define	MYAPP_PRM_DIR_IA_IDX		"DIR_IA_IDX"
#define	MYAPP_PRM_FILE_RETRY		"FILE_RETRY"


//	ディレクトリ格納サイズ
#define	MYAPP_PATH_SIZE			(1024)

//	共有メモリサイズ
#define	MYAPP_SHM_SIZE			sizeof ( int )

//	受信ファイル関連
#define	MYAPP_RECV_KIND			"RE"					//未使用
#define	MYAPP_RECV_SFX			".dat"					//未使用
#define	MYAPP_RECV_RECSIZE		(63 + 1)				/* 1レコードのサイズ - FILLER(12) - LF(1) + 1コード*/

//  送信ファイル関連
#define MYAPP_SEND_KIND_CH		"CHK"					//OUTPUT先頭文字列
#define MYAPP_SEND_SFX          ".dat"					//OUTPUT拡張子(AD205INPUT条件)

//	データサイズ
#define	MYAPP_TRNO_SIZE			(10+1)	
#define	MYAPP_STKNO_SIZE		(6+1)	
#define	MYAPP_DATE_SIZE			(10+1)	
#define	MYAPP_RKNO_SIZE			(10+1)	
#define	MYAPP_DEOF_SIZE			(20+1)	


#define MYAPP_PNC_MAX_SIZE			1024
#define MYAPP_KMKCD_START_POS		63
//	次世代システム
#define	MYAPP_VERSION			"NEXTGENE"

#define	MYAPP_COMMAND_RM		"/bin/rm"


/******************************************************************************/
/* 構造体定義                                                                 */
/******************************************************************************/
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
	char	 			 cDirNR_Col[MYAPP_PATH_SIZE] ;	
	char				 cDirNR_ColOk[MYAPP_PATH_SIZE] ;
	char				 cDirNR_ColErr[MYAPP_PATH_SIZE] ;
	char				 cDirIA_Dat[MYAPP_PATH_SIZE] ;
	char				 cDirIA_Idx[MYAPP_PATH_SIZE] ;
//	char				 cDirNR_Log[MYAPP_PATH_SIZE] ;		//未使用
	char				 cDirTryinfo[MYAPP_PATH_SIZE] ;		//未使用
	char				 cDirTryinfoOK[MYAPP_PATH_SIZE] ;		//未使用
	char				 cDirTryinfoNG[MYAPP_PATH_SIZE] ;		//未使用


//	char				 cVersion[32+1] ;					//未使用
} ;

// 緊急分注結果
typedef struct my_stINPUT
{
	char 	utkymd[9];				/* 受付日付 8桁+1コード		 */
	char 	kntno[12];				/* 検体No 11桁+1コード		 */
	char	eda[3];					/* 予備 2桁+1コード			 */
	char	sincode[8];				/* 親項目コード 7桁+1コード	 */
	char 	kmkcd[8];				/* 項目コード 7桁+1コード	 */
	char	wscd[5];				/* WSコード 4桁+1コード		 */
	char 	scheduleno[5];			/* SEQ番号 4桁+1コード		 */
	char 	motorackid[9];			/* 元ラックID 8桁+1コード	 */
	char 	motorackpos[3];			/* 元ポジション 2桁+1コード	 */
	char 	bunchurackid[9];		/* ラックID 8桁+1コード		 */
	char 	bunchurackpos[3];		/* ポジション 2+1コード		 */

}stINPUT_DATA;
// 緊急分注結果
typedef struct my_stOUTPUT
{
    char    syokubetumozi[2];
    char    transactionID[6];
    char    altuseiRackID[8];
    char    utkymd[8];
    char    iti1[3];
    char    BMLutkymd[8];
    char    iraino[11];
    char    kntno[11];
    char    kntchkmozi[2];
    char    WS[1];
    char    sbkbn[1];
    char    nrkbn[1];
    char    nr[3];
    char    nyoutime[4];
    char    nyoutime_tan[1];
    char    nyouryou[5];
    char    nyouryou_tan[1];
    char    sstcd[7];
    char    egyoucd[3];
    char    motoRackID[8];
    char    motoRackPos[3];
    char    wscd[4];
    char    kmkcd[64][7];
    char    bckID[3];
    char    jtflg[1];
    char    kssr[1];
    char    tgennflg[1];
    char    kkirflg[1];
    char    btkka[1];
    char    Filler[466];
	char 	LF;

	short	nPos;	//項目POSITION
	char	KeyKntno[12];//最初もらった検体番号
	char	KeyEda[3];//最初もらった検体枝番
	FILE	*fp;		//Output File	
}stOUTPUT_DATA;
/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/

/******************************************************************************/
/* プロトタイプ宣言                                                           */
/******************************************************************************/
void    sFncPutLog ( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... )  ;
#endif
/** End of File ***************************************************************/
