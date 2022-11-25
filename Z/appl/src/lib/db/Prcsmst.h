/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Prcsmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Prcsmst_h_
#define _Prcsmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Prcsmst {
	short   pgid;
	char    prno[11];
	char    lmname[21];
	char    krknsgrp[11];
	short   lmtype;
	char    wsname[17];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Prcsmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbPrcsmstSelectAll( Prcsmst** arrayOut, int* numOut );
long ZdbPrcsmstSelectKey( Prcsmst* pKey, Prcsmst** arrayOut, int* numOut );
long ZdbPrcsmstInsert( Prcsmst* rec );
long ZdbPrcsmstUpdate( Prcsmst* rec );
long ZdbPrcsmstDelete( Prcsmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
