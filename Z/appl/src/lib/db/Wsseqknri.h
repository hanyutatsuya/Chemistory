/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Wsseqknri.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Wsseqknri_h_
#define _Wsseqknri_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Wsseqknri {
	char    knskisymd[11];
	char    knsgrp[11];
	sqlint32  kmkcd;
	sqlint32  ctrlno;
	sqlint32  knsseqst;
	sqlint32  knsseqed;
	sqlint32  knsseqsu;
	char    wsseqjkflg;
	char    ksndh[27];
}	Wsseqknri;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbWsseqknriSelectAll( Wsseqknri** arrayOut, int* numOut );
long ZdbWsseqknriSelectKey( Wsseqknri* pKey, Wsseqknri** arrayOut, int* numOut );
long ZdbWsseqknriInsert( Wsseqknri* rec );
long ZdbWsseqknriUpdate( Wsseqknri* rec );
long ZdbWsseqknriDelete( Wsseqknri* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
