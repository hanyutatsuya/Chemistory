/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Calckmkmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Calckmkmst_h_
#define _Calckmkmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Calckmkmst {
	char    knsgrp[17];
	char    kmkcd[8];
	char    sstcd[8];
	char    zaicd[5];
	char    ksnsk[129];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Calckmkmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbCalckmkmstSelectAll( Calckmkmst** arrayOut, int* numOut );
long ZdbCalckmkmstSelectKey( Calckmkmst* pKey, Calckmkmst** arrayOut, int* numOut );
long ZdbCalckmkmstInsert( Calckmkmst* rec );
long ZdbCalckmkmstUpdate( Calckmkmst* rec );
long ZdbCalckmkmstDelete( Calckmkmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
