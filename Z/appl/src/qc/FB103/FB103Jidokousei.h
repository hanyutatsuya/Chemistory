/********************************************************************/
/*																	*/
/*		ＢＭＬ様向け検査システム									*/
/*																	*/
/*		システム名	：次世代システム								*/
/*		ファイル名	：FB103Jidokousei.h								*/
/*		概要		：自動校正処理									*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	作成日			名前			修正内容				*/
/* ----------------------------------------------------------------	*/
/*  1.00	2006/02/27		E.Osada			Create					*/
/********************************************************************/

#ifndef _FB103Jidokousei_h_
#define _FB103Jidokousei_h_

/********************************************************************/
/*	インクルード宣言												*/
/********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmllog.h"
#include "bmlprm.h"
#include "bml_date.h"
#include "bml_DBCom.h"
#include "bml_misc.h"
#include "F103ctrlkka.h"
#include "F103ctrlknr.h"
#include "F103kekka.h"

/******************************************************************************/
/* 定数定義	                                                                  */
/******************************************************************************/

//プログラム名
#define APP_NAME	"FB103"

//ログファイルINIファイル
#ifdef WIN32
#define LOGINIFILE ".\\FB103_LOG.log"
#else
#define LOGINIFILE "./FB103_LOG.ini"
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

//パラメータキー
#define PRM_DB_NAME					"DB_NAME"
#define PRM_DB_USER_ID				"DB_USER_ID"
#define	PRM_DB_PASSWORD				"DB_PASSWORD"

#ifdef WIN32
#define snprintf _snprintf
#endif

//トレース
#ifdef _TEST
#define mcrPutTrace(p, tt, fn, ef, ec, msg)		{	(p)->stLogMem.eTrcKind = (tt);														\
													printf("%c %s %s %s %s\n", (tt), (fn), (ef), (ec), (msg));	\
												}
#else
#define mcrPutTrace(p, tt, fn, ef, ec, msg)		{	(p)->stLogMem.eTrcKind = (tt) ;				\
													strcpy((p)->stLogMem.pcFncName, (fn)) ;		\
													strcpy((p)->stLogMem.pcExeFlg,  (ef)) ;		\
													strcpy((p)->stLogMem.pcErrCode, (ec)) ;		\
													strcpy((p)->stLogMem.pcMsg, (msg)) ;		\
													ZbmlPutLog(&(p)->stLogMem) ;				\
												}
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
} ENV, *PENV;


#endif
/** End of File ***************************************************************/
