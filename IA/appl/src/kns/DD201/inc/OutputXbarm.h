/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：OutputXbarm.h                                                */
/* 　概　　　要：X-M結果情報出力ヘッダ 	                                      */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/03/20     A.Yamada       新規作成                           */
/******************************************************************************/
#ifndef _outputxbarm_h
#define _outputxbarm_h
/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include "DD201.h"

/**********************************************************************/
/*  外部参照関数                                                      */
/**********************************************************************/
extern int OutputXbarm(SOCKET_INF*);			/* X-M結果結果出力処理 */

#endif /* OutputXbarm.h */
