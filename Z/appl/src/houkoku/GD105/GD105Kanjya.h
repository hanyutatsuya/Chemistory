/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：GD105Kanjya.h
 *     機能概要  ：患者情報アクセス関数(報告処理)
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2009-05-11                    Create
 **********************************************************************/
#ifndef _GD105Kanjya_h_
#define _GD105Kanjya_h_

/********************************************************************/
/*  インクルード宣言                                                */
/********************************************************************/
#include "bml_DBCom.h"

/********************************************************************/
/* テーブル構造体定義                                               */
/********************************************************************/
typedef struct _Kanjya {
	char    utkymd[10+1];
	char    irino[11+1];
	char    iriketflg;
	short   zssdino;
	char    sstcd[7+1];
	char    subsstcd[4+1];
	char    cdkbn1[2+1];
	char    cdkbn2[2+1];
	char    irimkey[40+1];
	char    srkcd[3+1];
	char    srknm[30+1];
	char    tticd[8+1];
	char    ttinm[40+1];
	char    gpcd[8+1];
	char    gpnm[40+1];
	char    skicd[8+1];
	char    skinm[40+1];
	char    krtno[40+1];
	char    knjid[15+1];
	char    knjnmn[60+1];
	char    knjnmk[30+1];
	char    knjnmkey[60+1];
	char    sc[5+1];
	char    tj[5+1];
	char    tjtni;
	char    sbtkbn;
	char    birthday[8+1];
	char    birthdaykbn;
	char    age[3+1];
	char    agekbn;
	char    btcd[10+1];
	char    btnm[30+1];
	char    utkcmtcd1[2+1];
	char    utkcmtcd2[2+1];
	char    utkcmtcd3[2+1];
	char    utkcmtfr1[70+1];
	char    utkcmtfr2[70+1];
	char    utkcmtfrflg;
	char    ngkbn;
	char    nsssu[2+1];
	char    hkncd;
	char    ktshsu[2+1];
	char    iniriymd[10+1];
	char    zssflg;
	char    kkiriflg;
	char    hknskbn;
	char    utkkbn;
	char    nekbn;
	char    inknskbn;
	char    utkjkkbn;
	char    krflg;
	char    fdhhkkflg;
	char    utkdh[8+1];
	char    mutkymd[10+1];
	char    mirino[11+1];
	char    knsjslbcd1[3+1];
	char    knsjslbcd2[3+1];
	char    knsjslbcd3[3+1];
	char    knsjslbcd4[3+1];
	char    ymhkkflg;
	char    hkkkbdh[8+1];
	char    ecd[3+1];
	char    shcd[2+1];
	char    sstssnmj[40+1];
	char    sstssnmn[40+1];
	char    sstrsj[20+1];
	char    sstrsn[20+1];
	char    sstsbt[2+1];
	char    ttsstflg;
	char    rucd[2+1];
	short   irikmksu;
	char    bmskn[50+1];
	char    irinrsbt[2+1];
	char    irihsmkbn;
	char    caresstflg;
	char    tktyflg;
	char    apkntino[13+1];
	char    sdnm[20+1];
	char    bko1[20+1];
	char    bko2[20+1];
	char    bko3[20+1];
	char    zstrdh[26+1];
	char    zsssdh[26+1];
	char    stlzsssdh[26+1];
	char    stlzsssip[15+1];
	char    stlzssssyaid[8+1];
	char    ksndh[26+1];
	char    oyasstcd[7+1];
	char    trkdh[26+1];
}	Kanjya;

/******************************************************************************/
/* プロトタイプ宣言                                                           */
/******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

long dGD105_KANJYA_Sel_latestZSSDINO( Kanjya* pKey, Kanjya** arrayOut, int* numOut );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
