/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Standard.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Standard_h_
#define _Standard_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Standard {
	char    knskisymd[11];
	char    bskkbn[11];
	char    bsklne[11];
	char    bskgok[7];
	char    bskmjno[6];
	char    knsgrp[11];
	sqlint32  bthno;
	short   stdsbt;
	char    asyrckid[11];
	short   asyrckpos;
	sqlint32  knsseq;
	sqlint32  bskseq;
	char    lotno[11];
	char    sktti[21];
	sqlint32  ktgrt;
	char    sktdh[27];
	char    stdjkflg;
	char    hkkokflg;
	char    ksndh[27];
}	Standard;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbStandardSelectAll( Standard** arrayOut, int* numOut );
long ZdbStandardSelectKey( Standard* pKey, Standard** arrayOut, int* numOut );
long ZdbStandardInsert( Standard* rec );
long ZdbStandardUpdate( Standard* rec );
long ZdbStandardDelete( Standard* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
