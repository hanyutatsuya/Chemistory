/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：GetKenorder.h                                                */
/* 　概　　　要：検査オーダー取得ヘッダ	                                      */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/31     A.Yamada       新規作成                           */
/******************************************************************************/
#ifndef _getkenorder_h
#define _getkenorder_h
/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
//#include "define.h"
#include "DD203.h"

/**********************************************************************/
/*  外部参照関数                                                      */
/**********************************************************************/
extern int GetKenorder(SOCKET_INF*,int, int*);

#endif /* GetKenorder.h */
