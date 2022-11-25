/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Irai.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Irai_h_
#define _Irai_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Irai {
	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    knsgrp[17];
	char    kmkcd[8];
	char    irihsmkbn;
	char    irikbn;
	char    ksktkbn;
	char    sriymd[11];
	char    kntno[14];
	char    kntketflg;
	char    chkmj[5];
	char    stsrcd[5];
	char    kmkrs[17];
	char    oyakmkcd[8];
	char    smpcd[8];
	char    setkmkcd[8];
	char    srinycd;
	char    seccd[3];
	char    skchkflg;
	char    bkfkkbn;
	char    ysnlbl[3];
	char    skflg;
	char    tkflg;
	char    sjflg;
	char    jktkflg;
	char    kjno[4];
	char    fkhkknohjkbn;
	char    tbkjno[4];
	char    tbkjflg;
	char    htkfkhms[25];
	char    tskflg[3];
	char    tktflg[3];
	char    bnckbn;
	char    nbnckbn;
	char    knskisyymd[11];
	char    knskryymd[11];
	char    knskrytme[9];
	char    kkhkkflg;
	char    kkiriflg;
	short   kkirilotno;
	char    kktoutkid[5];
	short   knssu;
	char    odrssflg;
	char    ytiksbr[16];
	char    hhkjkflg;
	char    ksndh[27];
	char    trkdh[27];
}	Irai;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbIraiSelectAll( Irai** arrayOut, int* numOut );
long ZdbIraiSelectKey( Irai* pKey, Irai** arrayOut, int* numOut );
long ZdbIraiInsert( Irai* rec );
long ZdbIraiUpdate( Irai* rec );
long ZdbIraiDelete( Irai* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
