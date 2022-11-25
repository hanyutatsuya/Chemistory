/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Usermst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Usermst_h_
#define _Usermst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Usermst {
	char    userid[9];
	char    cardid[31];
	char    pswd[11];
	char    usernm[21];
	char    oldpswd[111];
	char    pswdykkgn[11];
	char    logindh[27];
	char    loginykkgn[11];
	char    seccd[3];
	char    sykiskbn;
	char    sykindh[27];
	char    rnrdelflg;
	char    staymd[11];
	char    endymd[11];
	char    trkymd[11];
	char    hnkymd[11];
}	Usermst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbUsermstSelectAll( Usermst** arrayOut, int* numOut );
long ZdbUsermstSelectKey( Usermst* pKey, Usermst** arrayOut, int* numOut );
long ZdbUsermstInsert( Usermst* rec );
long ZdbUsermstUpdate( Usermst* rec );
long ZdbUsermstDelete( Usermst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
