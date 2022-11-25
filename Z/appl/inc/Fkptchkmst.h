/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Fkptchkmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Fkptchkmst_h_
#define _Fkptchkmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Fkptchkmst {
	char    knsgrp[17];
	char    oyakmkcd[8];
	char    chk1;
	char    chk2;
	char    chk3;
	char    chk4;
	char    chk5;
	char    chk6;
	char    chk7;
	char    chk8;
	char    chk9;
	char    chk10;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Fkptchkmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbFkptchkmstSelectAll( Fkptchkmst** arrayOut, int* numOut );
long ZdbFkptchkmstSelectKey( Fkptchkmst* pKey, Fkptchkmst** arrayOut, int* numOut );
long ZdbFkptchkmstInsert( Fkptchkmst* rec );
long ZdbFkptchkmstUpdate( Fkptchkmst* rec );
long ZdbFkptchkmstDelete( Fkptchkmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
