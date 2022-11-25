/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Jdkmkmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Jdkmkmst_h_
#define _Jdkmkmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Jdkmkmst {
	char    knsgrp[17];
	char    kmkcd[8];
	char    jknsgrp[17];
	char    jkmkcd[8];
	char    hhkumflg;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Jdkmkmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbJdkmkmstSelectAll( Jdkmkmst** arrayOut, int* numOut );
long ZdbJdkmkmstSelectKey( Jdkmkmst* pKey, Jdkmkmst** arrayOut, int* numOut );
long ZdbJdkmkmstInsert( Jdkmkmst* rec );
long ZdbJdkmkmstUpdate( Jdkmkmst* rec );
long ZdbJdkmkmstDelete( Jdkmkmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
