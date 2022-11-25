/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Kmkgmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Kmkgmst_h_
#define _Kmkgmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Kmkgmst {
	char    kmkgrp[17];
	char    kmkgrpnm[41];
	char    kmkgrprs[21];
	char    knsgrp[17];
	char    kmkcd[8];
	short   hyjijn;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Kmkgmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKmkgmstSelectAll( Kmkgmst** arrayOut, int* numOut );
long ZdbKmkgmstSelectKey( Kmkgmst* pKey, Kmkgmst** arrayOut, int* numOut );
long ZdbKmkgmstInsert( Kmkgmst* rec );
long ZdbKmkgmstUpdate( Kmkgmst* rec );
long ZdbKmkgmstDelete( Kmkgmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
