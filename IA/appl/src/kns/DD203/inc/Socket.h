/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：Socket.h                                                     */
/* 　概　　　要：ソケット制御ヘッダ   	                                      */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/31     A.Yamada       新規作成                           */
/******************************************************************************/
#ifndef _socket_h
#define _socket_h
/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include "DD203.h"

/**********************************************************************/
/*  変数宣言                                                           */
/**********************************************************************/
typedef int SOCKET;
#define SOCK_ERR		0xffff	/* ソケットエラー			*/
#define NO_FLAGS_SET    0           /*  */

/**********************************************************************/
/*  外部参照関数                                                      */
/**********************************************************************/
extern SOCKET			ClientInit(char *hostname, int port);
extern int				readAll(SOCKET, char *);
extern SOCKET			isSelect(SOCKET sd[], long sec);
extern int				writen(SOCKET, char *, long);

#endif /* Socket.h */
