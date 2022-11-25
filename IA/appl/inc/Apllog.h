/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Apllog.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Apllog_h_
#define _Apllog_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Apllog {
	char    sydate[11];
	char    sytime[9];
	char    tracekbn;
	char    pcname[33];
	sqlint32  proccessid;
	char    loginid[9];
	char    wkupapp[33];
	char    srcname[33];
	char    funcname[33];
	sqlint32  getline;
	char    procflg[3];
	char    errcode[9];
	char    message[1025];
}	Apllog;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbApllogSelectAll( Apllog** arrayOut, int* numOut );
long ZdbApllogSelectKey( Apllog* pKey, Apllog** arrayOut, int* numOut );
long ZdbApllogInsert( Apllog* rec );
long ZdbApllogUpdate( Apllog* rec );
long ZdbApllogDelete( Apllog* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
