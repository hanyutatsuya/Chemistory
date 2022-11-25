/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Kekkafree.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Kekkafree_h_
#define _Kekkafree_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Kekkafree {
	char    knskisymd[11];
	char    sriymd[11];
	char    kntno[14];
	char    kntketflg;
	char    knsgrp[17];
	char    kmkcd[8];
	short   knssu;
	short   knssueda;
	char    frsb;
	char    freetext[16385];
	char    ssssflg;
	char    ssknsflg;
	char    dtnrtts[9];
	char    dtnrdh[27];
	char    ksndh[27];
}	Kekkafree;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKekkafreeSelectAll( Kekkafree** arrayOut, int* numOut );
long ZdbKekkafreeSelectKey( Kekkafree* pKey, Kekkafree** arrayOut, int* numOut );
long ZdbKekkafreeInsert( Kekkafree* rec );
long ZdbKekkafreeUpdate( Kekkafree* rec );
long ZdbKekkafreeDelete( Kekkafree* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
