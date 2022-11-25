/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Skchkmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _A105sknchk_h_
#define _A105sknchk_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Skchkmst {
	char    knsgrp[17];
	char    kmkcd[8];
	char    sstcd[8];
	char    zaicd[5];
	short   krknsgrp;
	char    soukan[129];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Skchkmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long AD105sknchkSelKey( Skchkmst* pKey, Skchkmst** arrayOut, int* numOut );
long AD105sknchkSelAll( Skchkmst** arrayOut, int* numOut );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
