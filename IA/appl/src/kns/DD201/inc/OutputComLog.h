/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：OutputComLog.h                                               */
/* 　概　　　要：通信ログ出力ヘッダ    	                                      */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/31     A.Yamada       新規作成                           */
/******************************************************************************/
#ifndef _outputcomlog_h
#define _outputcomlog_h
/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include "DD201.h"

/**********************************************************************/
/*  外部参照関数                                                      */
/**********************************************************************/
extern int OutputComLog(SOCKET_INF* ,int, char*);

#endif /* OutputComLog.h */
