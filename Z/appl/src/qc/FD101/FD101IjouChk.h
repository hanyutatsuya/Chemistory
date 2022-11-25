/********************************************************************/
/*																	*/
/*		ＢＭＬ様向け検査システム									*/
/*																	*/
/*		システム名	：次世代システム								*/
/*		ファイル名	：FD101IjouChk.h								*/
/*		概要		：精度管理異常チェック							*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	作成日			名前			修正内容				*/
/* ----------------------------------------------------------------	*/
/*  1.00	2006/02/27		E.Osada			Create					*/
/********************************************************************/

#ifndef _FD101IjouChk_h_
#define _FD101IjouChk_h_

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

#include "F101ctrlijhmst.h"
#include "F101ctrlkka.h"

/******************************************************************************/
/* 定数定義	                                                                  */
/******************************************************************************/

//プログラム名
#define APP_NAME	"FD101"

//ログファイルINIファイル
#ifdef WIN32
#define LOGINIFILE ".\\FD101_LOG.log"
#else
/* 1.01 INTEC DELL
DEL#define LOGINIFILE "./FD101_LOG.ini"
*/
#define LOGINIFILE "$HOME/appl/src/qc/FD101/FD101_LOG.ini"
#endif

//エラーコード

//  ログエラーコード定義
#define MYAPP_LOG_ERRCODE_NON       "00000000"
#define MYAPP_LOG_ERRCODE_APP       "010"
#define MYAPP_LOG_ERRCODE_DB        "020"
#define MYAPP_LOG_ERRCODE_ETC       "0Z0"

//	プログラムエラーコード定義
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

//パラメータキー
#define PRM_DB_NAME					"DB_NAME"
#define PRM_DB_USER_ID				"DB_USER_ID"
#define	PRM_DB_PASSWORD				"DB_PASSWORD"
#define PRM_SLEEP_SEC				"SLEEP_SEC"
#define PRM_SHM_KEY					"SHM_KEY"		// 1.01 INTEC ADD
#define PRM_SEL_MAX					"SEL_MAX"		// 1.01 INTEC ADD

// 1.01 INTEC ADD SHM_KEY_SIZE
#define         MYAPP_SHM_SIZE          sizeof ( int )

#ifdef WIN32
#define snprintf	_snprintf
#define sleep(n)	(Sleep((n) * 1000))
#endif

//トレース
#define mcrPutTrace(p, tt, fn, ef, ec, msg)		{	(p)->stLogMem.eTrcKind = (tt) ;				\
													strcpy((p)->stLogMem.pcFncName, (fn)) ;		\
													strcpy((p)->stLogMem.pcExeFlg,  (ef)) ;		\
													strcpy((p)->stLogMem.pcErrCode, (ec)) ;		\
													strcpy((p)->stLogMem.pcMsg, (msg)) ;		\
													ZbmlPutLog(&(p)->stLogMem) ;				\
												}

//コントロール管理テーブル関連
#define CTRLHDFLG_SEIJOU			'S'
#define CTRLHDFLG_IJOU				'I'
#define CTRLHDFLG_KOUSEI_IJOU		'K'

#define CTRLKTFLG_KAKUTEI_MAE		'0'
#define CTRLKTFLG_KAKUTEI_SUMI		'1'


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
	,KOUSEI_IJOU
}RANGE_HANTEI;

#ifdef WIN32
#define JIDOU_KOUSEI_EXE	"FB103.exe FB103.ini"
#else
#define JIDOU_KOUSEI_EXE	"FB103 FB103.ini &"
#endif

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
	char		cUpdateId[128];						//更新者ID
	char		cUpdateName[128];					//更新者
	char		cLogName[128];						//ログ
	int			sleepInterval;						//実行間隔(ミリ秒)
	int			shm_Key;							//共有メモリKEY
	int			sel_Max;							//CTRL結果読込最大件数
	
} ENV, *PENV;

// INTEC ADD
ENV		stEnv;

// 共有メモリ管理構造体
struct  SHM {
    int     shm_Id ;
    key_t   shm_Key ;
};

#endif
/** End of File ***************************************************************/
