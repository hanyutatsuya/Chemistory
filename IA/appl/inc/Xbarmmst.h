/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Xbarmmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Xbarmmst_h_
#define _Xbarmmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Xbarmmst {
	char    knsgrp[17];
	char    kmkcd[8];
	char    minval[11];
	char    minart[11];
	char    avgval[11];
	char    maxart[11];
	char    maxval[11];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Xbarmmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbXbarmmstSelectAll( Xbarmmst** arrayOut, int* numOut );
long ZdbXbarmmstSelectKey( Xbarmmst* pKey, Xbarmmst** arrayOut, int* numOut );
long ZdbXbarmmstInsert( Xbarmmst* rec );
long ZdbXbarmmstUpdate( Xbarmmst* rec );
long ZdbXbarmmstDelete( Xbarmmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
