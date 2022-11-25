/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Kmkbtutest.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Kmkbtutest_h_
#define _Kmkbtutest_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Kmkbtutest {
	char    knskisymd[11];
	char    knsgrp[17];
	char    kmkcd[8];
	sqlint32  iriallsu;
	sqlint32  irijsnsu;
	sqlint32  kensasu;
	sqlint32  stadsu;
	sqlint32  ctrlsu;
	sqlint32  testsu;
	sqlint32  savysu;
	sqlint32  kbrtsu;
	sqlint32  kstatsu;
	char    ksndh[27];
}	Kmkbtutest;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKmkbtutestSelectAll( Kmkbtutest** arrayOut, int* numOut );
long ZdbKmkbtutestSelectKey( Kmkbtutest* pKey, Kmkbtutest** arrayOut, int* numOut );
long ZdbKmkbtutestInsert( Kmkbtutest* rec );
long ZdbKmkbtutestUpdate( Kmkbtutest* rec );
long ZdbKmkbtutestDelete( Kmkbtutest* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
