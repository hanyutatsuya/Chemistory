/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：OutputCtrlkka.h                                              */
/* 　概　　　要：結果情報出力ヘッダ    	                                      */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/31     A.Yamada       新規作成                           */
/******************************************************************************/
#ifndef _outputctrlkka_h
#define _outputctrlkka_h
/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include "DD203.h"

/**********************************************************************/
/*  外部参照関数                                                      */
/**********************************************************************/
extern int OutputCtrlkka(SOCKET_INF*);			/* コントロール結果結果出力処理 */

#endif /* OutputCtrlkka.h */
