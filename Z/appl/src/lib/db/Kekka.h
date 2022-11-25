/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Kekka.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Kekka_h_
#define _Kekka_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Kekka {
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
	char    bsklne[5];
	char    bskgok[7];
	sqlint32  bskseq;
	char    bskerrsts[3];
	char    sktdh[27];
	char    nbkmkcd[8];
	char    tstrflg;
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
	char    jisksbr[16];
	char    kkflg;
	char    kkiriflg;
	short   kkirilotno;
	char    hsykflg;
	char    hskflg;
	char    hhkkflg;
	char    rawdata[21];
	char    knskka1[13];
	char    knskka2[25];
	char    knskka2kbn[3];
	char    kkahskcd[4];
	char    hjkka[25];
	char    sdi[4];
	char    kkacmt1[6];
	char    kkacmt2[6];
	char    kkajkcd;
	char    pncrgflg;
	char    knspncrgflg;
	char    kkaksflg;
	char    kkassflg;
	char    ijkbnm;
	char    ijkbnf;
	char    ijkbnn;
	char    tbijkbnm;
	char    tbijkbnf;
	char    tbijkbnn;
	char    nbdolbl[3];
	char    nbdoerr[4];
	char    ykdolbl[3];
	char    ykdoerr[4];
	char    etclbl[3];
	char    etcerr[4];
	sqlint32  ctrlno;
	sqlint32  knsseq;
	short   bthno;
	sqlint32  pltno;
	sqlint32  pltseq;
	char    dtnrtts[9];
	char    dtnrdh[27];
	char    knskrdh[27];
	char    hkkdh[27];
	char    hkkkbdh[9];
	char    zkhkkyymd[11];
	char    zkhkkytme[5];
	char    frkkaflg;
	char    gzbsflg;
	char    hsiflg;
	char    kkaysnflg;
	char    tnyrkflg;
	char    siyflg;
	char    knsflg;
	char    renjicflg;
	char    soukn1flg;
	char    kanrenflg;
	char    bunkkuflg;
	char    kesseiflg;
	char    rirekiflg;
	char    syougoflg;
	char    keisanflg;
	char    per100flg;
	char    tousekflg;
	char    kisyakflg;
	char    kouseiflg;
	char    syoungflg;
	char    soukn2flg;
	char    fukaptflg;
	char    yobiflg01;
	char    tobiflg02;
	char    yobiflg03;
	char    yobiflg04;
	char    yobiflg05;
	char    skrycda[4];
	char    skrycdb[4];
	char    skrycdc[4];
	char    ksndh[27];
	char	trkdh[27];
	char	skkka[25];
}	Kekka;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKekkaSelectAll( Kekka** arrayOut, int* numOut );
long ZdbKekkaSelectKey( Kekka* pKey, Kekka** arrayOut, int* numOut );
long ZdbKekkaInsert( Kekka* rec );
long ZdbKekkaUpdate( Kekka* rec );
long ZdbKekkaDelete( Kekka* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
