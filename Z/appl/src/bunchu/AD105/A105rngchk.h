/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Rngchkmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _A105rngchk_h_
#define _A105rngchk_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Rngchkmst {
	char    hnikbn;
	char    knsgrp[17];
	char    kmkcd[8];
	char    zaicd[5];
	char    sstcd[8];
	char    sbt;
	char    ssa;
	char    zen_kyoyou;
	char    hrng[21];
	char    lrng[21];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Rngchkmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long A105rngchkSelKey( Rngchkmst* pKey, Rngchkmst** arrayOut, int* numOut );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
