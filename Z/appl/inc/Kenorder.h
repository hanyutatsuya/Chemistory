/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Kenorder.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Kenorder_h_
#define _Kenorder_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Kenorder {
	char    knskisymd[11];
	char    sriymd[11];
	char    kntno[14];
	char    kntketflg;
	char    knsgrp[17];
	char    kmkcd[8];
	short   knssu;
	short   knssueda;
	char    irihsmkbn;
	char    irikbn;
	char    ksktkbn;
	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    sstcd[8];
	char    trid[11];
	short   trpos;
	char    asyrckid[11];
	short   asyrckpos;
	char    oyakmkcd[8];
	char    seccd[3];
	char    bkfkkbn;
	char    smpcd[8];
	char    bskkbn[5];
	char    nbkmkcd[8];
	char    zrcd[5];
	char    ysnlbl[3];
	char    kjno[4];
	char    fkhkknohjkbn;
	char    tbkjno[4];
	char    tbkjflg;
	char    htkfkhms[25];
	char    skflg;
	char    tskflg[3];
	char    tktflg[3];
	char    ytiksbr[16];
	char    kkflg;
	char    kkiriflg;
	short   kkirilotno;
	char    sc[6];
	char    tj[6];
	char    tjtni;
	char    sbtkbn;
	char    birthday[9];
	char    birthdaykbn;
	char    age[4];
	char    agekbn;
	char    sstme[9];
	char    ssymd[11];
	char    tntme[5];
	char    tntni;
	char    tnryo[6];
	char    tnryotni;
	sqlint32  knsseq;
	short   bthno;
	char    knsjkflg;
	char    ksndh[27];
}	Kenorder;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKenorderSelectAll( Kenorder** arrayOut, int* numOut );
long ZdbKenorderSelectKey( Kenorder* pKey, Kenorder** arrayOut, int* numOut );
long ZdbKenorderSelectKey3( Kenorder* pKey, Kenorder** arrayOut, int* numOut );
long ZdbKenorderInsert( Kenorder* rec );
long ZdbKenorderUpdate( Kenorder* rec );
long ZdbKenorderDelete( Kenorder* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
