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
#ifndef _Skchkmst_h_
#define _Skchkmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Skchkmst {
	char    knsgrp[17];
	char    kmkcd[8];
	char    sstcd[8];
	char    zaicd[5];
	short   krknsgrp[11];
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

long ZdbSkchkmstSelectAll( Skchkmst** arrayOut, int* numOut );
long ZdbSkchkmstSelectKey( Skchkmst* pKey, Skchkmst** arrayOut, int* numOut );
long ZdbSkchkmstInsert( Skchkmst* rec );
long ZdbSkchkmstUpdate( Skchkmst* rec );
long ZdbSkchkmstDelete( Skchkmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
