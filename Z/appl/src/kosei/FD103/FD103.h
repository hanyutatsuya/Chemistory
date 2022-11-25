/********************************************************************/
/*																	*/
/*		ＢＭＬ様向け検査システム									*/
/*																	*/
/*		システム名	：次世代システム								*/
/*		ファイル名	：FD103.h										*/
/*		概要		：自動校正判定処理								*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	作成日			名前			修正内容				*/
/* ----------------------------------------------------------------	*/
/*  1.00	2007/04/06		T.Wajima		Create					*/
/* ----------------------------------------------------------------	*/
/*  Ver.	作成日			名前			修正内容				*/
/* ----------------------------------------------------------------	*/
/*  2.00	2008/10/09		K.Ameno			自動校正対応初版		*/
/********************************************************************/

#ifndef _FD103_h_
#define _FD103_h_

/********************************************************************/
/*	インクルード宣言												*/
/********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <math.h>
#include "bmllog.h"
#include "bmlprm.h"
#include "bml_date.h"
#include "bml_DBCom.h"
#include "bml_misc.h"

/******************************************************************************/
/* 定数定義	                                                                  */
/******************************************************************************/

/*プログラム名 */
#define APP_NAME	"FD103"

/* ログファイルINIファイル */
#define LOGINIFILE "/home/kea00sys/bin/FD103_LOG.ini"

/* エラーコード */

/* ログエラーコード定義 */
#define MYAPP_LOG_ERRCODE_NON       "00000000"
#define MYAPP_LOG_ERRCODE_APP       "010"
#define MYAPP_LOG_ERRCODE_DB        "020"
#define MYAPP_LOG_ERRCODE_ETC       "0Z0"

/* プログラムエラーコード定義 */
#define ERROR_CODE_NORMAL			 0
#define	ERROR_CODE_CMD_PRM_ERROR	-1
#define	ERROR_CODE_PRM_OPEN_ERROR	-2
#define ERROR_CODE_LOG_OPEN_ERROR	-3
#define ERROR_CODE_PRM_GET_ERROR	-4
#define ERROR_CODE_DB_CONNECT_ERROR	-5
#define ERROR_DB_ERROR				-6
#define ERROR_FUNC_ERROR			-7
#define ERROR_CTRL_COUNT			-8
#define ERROR_CHANNEL_HOSEI_FUYOU	-9
#define ERROR_MEMORY_ERROR			-10
#define ERROR_MULTI_RUN				-11

/* パラメータキー */
#define PRM_DB_NAME					"DB_NAME"
#define PRM_DB_USER_ID				"DB_USER_ID"
#define	PRM_DB_PASSWORD				"DB_PASSWORD"
#define PRM_SLEEP_SEC				"SLEEP_SEC"
#define PRM_SHM_KEY					"SHM_KEY"
#define PRM_SEL_MAX					"SEL_MAX"

#define         MYAPP_SHM_SIZE          sizeof ( int )

#define     MYAPP_LEN_MSG       1024
#define     MYAPP_LEN_ERR       32
#define     MYAPP_LEN_FNCNM     32

            /* トレース種別 */
#define     LT_DBG          "D"
#define     LT_TRC          "T"
#define     LT_OPT          "O"
#define     LT_WRN          "W"
#define     LT_ERR          "E"
#define     LT_SYS          "A"
#define     LT_STA          "STA"
#define     LT_END          "END"
            /* 実行フラグ */
#define     LX_SEL          "S"
#define     LX_INS          "I"
#define     LX_UPD          "U"
#define     LX_DEL          "D"
#define     LX_NON          " "
            /* エラーコード */
#define     LE_NON          " "

struct {
    char    dbp_dbAlias[15];            /*  DB */
    char    dbp_user[129];              /*  user */
    char    dbp_pswd[15];               /*  password */
    char    lgp_comlog[256];            /* LOG FILE NAME */
    char    myp_exefile[256];           /* LoadModuleName */
    int     myp_debug;
} stcPRM;


/******************************************************************************/
/* プロトタイプ宣言                                                           */
/******************************************************************************/
extern      char        G_msg[MYAPP_LEN_MSG+1]; /* LogMessage */
extern      char        G_err[MYAPP_LEN_ERR+1]; /* LogMessage(errcode) */

/******************************************************************************/
/* プロトタイプ宣言                                                           */
/******************************************************************************/
int         LogOut( char *sbt, char *flg, char *ecd, char *msg,
                    char *fncnm, char *file, long line );
/*/PG固有せず */
char        *EnvRef( char *src_cp );
char        *GetIniFile( char *section, char *key, char *profile );
int         chkLowHigh( double  hikaku1, double  hikaku2, int ketasu );

/* コントロール管理テーブル関連 */
#define CTRLHDFLG_SEIJOU			'S'
#define CTRLHDFLG_IJOU				'I'
#define CTRLHDFLG_KOUSEI_IJOU		'K'

#define CTRLKTFLG_KAKUTEI_MAE		'0'
#define CTRLKTFLG_KAKUTEI_SUMI		'1'

/* 領域確保関連 */
#define ALLOC_INIT		2000	/* 初回領域確保件数 */
#define ALLOC_ADD		200		/* 領域確保増分件数 */

/*校正対象外事由コード */
typedef enum
{
	 KSTS_OK 		=	0		/* 校正対象データ */
	,KSTS_NORMAL	=	1		/* 正常値（校正の必要なし） */
	,KSTS_CTRLNO	=	2		/* 対象外コントロールNO */
	,KSTS_CTRLNONE	=	3		/* コントロール本数未達（最新データ以外はNGとする） */
	,KSTS_CTRLNG	=	4		/* 対象外コントロール（前） */
	,KSTS_HIST		=	5		/* ヒスト階級数エラー（５未満） */
	,KSTS_RENGE		=	6		/* 対象外レンジ */
	,KSTS_FB_OVER	=	7		/* 対象外ファクタ/ベース範囲外・上限 */
	,KSTS_FB_CALC	=	8		/* 対象外ファクタ/ベース計算不可 */
	,KSTS_2HOUSEI	=	9		/* 二峰性データ */
	,KSTS_SAIHIN	=  10		/* 最頻値エラー */
	,KSTS_COUNT		=  11		/* サンプル数未達 2009.2.3 Nagata */
	,KSTS_SAISOKU	=  12		/* 再測定の必要有り（校正しない） 2009.2.6 Nagata */
} KSTSERR;

typedef enum
{
	 CV_NORMAL
	,CV_ABNORMAL
} CTRLVALUE;

typedef enum
{
	 KJ_KOUSEI_KA
	,KJ_KOUSEI_FUYOU
	,KJ_KOUSEI_FUKA
}KOUSEIJISSI;

typedef enum
{
	 RH_NORMAL
	,RH_KOUSEI
	,RH_SAIKEN
	,KOUSEI_IJOU
}RANGE_HANTEI;

/******************************************************************************/
/* 構造体定義                                                                 */
/******************************************************************************/

/* プログラム管理構造体 */
typedef struct
{
	BMLPRM*		bp;				
	struct		stcLogMember      stLogMem;
	char		cDbName[128];
	char		cDbUserId[128];
	char		cDbPassword[128];
	char		cUpdateId[128];						/* 更新者ID */
	char		cUpdateName[128];					/* 更新者 */
	char		cLogName[128];						/* ログ */
	int			sleepInterval;						/* 実行間隔(ミリ秒) */
	int			shm_Key;							/* 共有メモリKEY */
	int			sel_Max;							/* CTRL結果読込最大件数 */
	
} ENV, *PENV;

ENV		stEnv;

/* 共有メモリ管理構造体 */
struct  SHM {
    int     shm_Id ;
    key_t   shm_Key ;
};

/* 校正対象リスト */
typedef struct
{
	char   knskisymd[11];		/* 検査開始日 */
	char   bskkbn[5];			/* 分析機区分 */
	char   bsklne[5];			/* 分析機ライン */
	char   bskgok[7];			/* 分析機号機 */
	int    ctrlno;				/* コントロール番号 */
	char   nbkmkcd[8];			/* 内部項目コード */
	char   ctrlsbt[21];			/* コントロール種別 */
	char   sktti[25];			/* 測定値 */
	char   ctrlx[13];			/* 平均値 */
	int    sstnksu;				/* 小数点桁数 */
	char   facterjd1[13];		/* ファクター自動１ */
	char   facterjd2[13];		/* ファクター自動２ */
	char   basejd1[13];			/* ベース自動１ */
	char   basejd2[13];			/* ベース自動２ */
	int    nonecnt;				/* コントロール精度判定（０以外は本数未達） */
	int    ngcnt;				/* コントロール精度判定（０以外は精度異常） */
    double shrnglwhf;           /* 最頻レンジ下限値補正前 */
    double shrnghihf;           /* 最頻レンジ上限値補正前 */
    double shrnglwhb;           /* 最頻レンジ下限値補正後 */
    double shrnghihb;           /* 最頻レンジ上限値補正後 */
    double hstkjntn;            /* ヒスト作成基準点 */
    double hstkzmhb;            /* ヒスト刻み幅 */
    int    hstkaikyu;           /* ヒスト階級数 */
    int    ksikjnspsu;          /* 校正基準サンプル数 */
} KTLIST;

/* 自動校正対象コントロールテーブル */
typedef struct
{
	int    seq;
    char   knskisymd[11];
    char   bskkbn[5];
    char   bsklne[5];
    char   bskgok[7];
    char   nbkmkcd[8];
    int    ctrlnoFrom;
    int    ctrlnoTo;
	int    sstnksu;
    double facter;
    double base;
	char   autokosiflg[2];
	char   kosizmflg[2];
	char   causecd[9];
	char   kosierrcd[9];
	int    kensu;
	char   yobi1[11];
	char   yobi2[11];
	char   yobi3[11];
	char   termid[16];
	char   kosidh[22];
	char   sksdh[22];
	char   ksndh[22];
} ATKSTS;

/* 校正係数算出用パラメータ */
typedef struct  toukei_stat_area{
    int     n;
    double  sumx;
    double  sumy;
    double  sumxy;
    double  sumxx;
    double  sumyy;
}   TOUKEI_CALC;

#endif
/** End of File ***************************************************************/
