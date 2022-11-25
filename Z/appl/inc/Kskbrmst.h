/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Kskbrmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Kskbrmst_h_
#define _Kskbrmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Kskbrmst {
	char    bskkbn[5];
	char    knsgrp[17];
	char    kmkcd[8];
	char    ksbr[16];
	char    kmin[21];
	char    kmax[21];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Kskbrmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKskbrmstSelectAll( Kskbrmst** arrayOut, int* numOut );
long ZdbKskbrmstSelectKey( Kskbrmst* pKey, Kskbrmst** arrayOut, int* numOut );
long ZdbKskbrmstInsert( Kskbrmst* rec );
long ZdbKskbrmstUpdate( Kskbrmst* rec );
long ZdbKskbrmstDelete( Kskbrmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
