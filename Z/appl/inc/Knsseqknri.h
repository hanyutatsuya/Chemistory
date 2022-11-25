/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Knsseqknri.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-03-23                    Create
 **********************************************************************/
#ifndef _Knsseqknri_h_
#define _Knsseqknri_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Knsseqknri {
	char    knskisymd[11];
	char    knsgrp[17];
	char    traykbn;
	char    wssbt[11];
	sqlint32  wsno;
	sqlint32  knsseqmax;
	sqlint32  sytrymax;
	char    ksndh[27];
}	Knsseqknri;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKnsseqknriSelectAll( Knsseqknri** arrayOut, int* numOut );
long ZdbKnsseqknriSelectKey( Knsseqknri* pKey, Knsseqknri** arrayOut, int* numOut );
long ZdbKnsseqknriInsert( Knsseqknri* rec );
long ZdbKnsseqknriUpdate( Knsseqknri* rec );
long ZdbKnsseqknriDelete( Knsseqknri* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
