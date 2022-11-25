/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：A205wsseq.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _A205wsseq_h_
#define _A205wsseq_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Wsseqknri {
	sqlint32 wstbnknr;
	char    knskisymd[11];
	char    knsgrp[17];
	char    wssbt[11];
	sqlint32  wsno;
	sqlint32  knsseqst;
	sqlint32  knsseqed;
	sqlint32  knsseqsu;
	char    ksktkbn;
	char    dtnrtts[9];
	char    ksndh[27];
}	Wsseqknri;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long A205wsAllSel( Wsseqknri** arrayOut, int* numOut );
long A205wsInsert( Wsseqknri* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
