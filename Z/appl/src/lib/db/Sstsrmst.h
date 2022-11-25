/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Sstsrmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Sstsrmst_h_
#define _Sstsrmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Sstsrmst {
	char    sstcd[8];
	char    knsgrp[17];
	char    kmkcd[8];
	char    syrsbt[4];
	char    prm1[51];
	char    prm2[51];
	char    prm3[51];
	char    prm4[51];
	char    prm5[51];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Sstsrmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbSstsrmstSelectAll( Sstsrmst** arrayOut, int* numOut );
long ZdbSstsrmstSelectKey( Sstsrmst* pKey, Sstsrmst** arrayOut, int* numOut );
long ZdbSstsrmstInsert( Sstsrmst* rec );
long ZdbSstsrmstUpdate( Sstsrmst* rec );
long ZdbSstsrmstDelete( Sstsrmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
