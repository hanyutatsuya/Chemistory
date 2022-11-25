/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Kanjya.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Kanjya_h_
#define _Kanjya_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Kanjya {
	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    sstcd[8];
	char    subsstcd[5];
	char    cdkbn1[3];
	char    cdkbn2[3];
	char    irimkey[41];
	char    srkcd[4];
	char    srknm[31];
	char    tticd[9];
	char    ttinm[41];
	char    gpcd[9];
	char    gpnm[41];
	char    skicd[9];
	char    skinm[41];
	char    krtno[41];
	char    knjid[16];
	char    knjnmn[61];
	char    knjnmk[31];
	char    knjnmkey[61];
	char    sc[6];
	char    tj[6];
	char    tjtni;
	char    sbtkbn;
	char    birthday[9];
	char    birthdaykbn;
	char    age[4];
	char    agekbn;
	char    btcd[11];
	char    btnm[31];
	char    utkcmtcd1[3];
	char    utkcmtcd2[3];
	char    utkcmtcd3[3];
	char    utkcmtfr1[71];
	char    utkcmtfr2[71];
	char    utkcmtfrflg;
	char    ngkbn;
	char    nsssu[3];
	char    hkncd;
	char    ktshsu[3];
	char    iniriymd[11];
	char    zssflg;
	char    kkiriflg;
	char    hknskbn;
	char    utkkbn;
	char    nekbn;
	char    inknskbn;
	char    utkjkkbn;
	char    krflg;
	char    fdhhkkflg;
	char    utkdh[9];
	char    mutkymd[11];
	char    mirino[12];
	char    knsjslbcd1[4];
	char    knsjslbcd2[4];
	char    knsjslbcd3[4];
	char    knsjslbcd4[4];
	char    ymhkkflg;
	char    hkkkbdh[9];
	char    ecd[4];
	char    shcd[3];
	char    sstssnmj[41];
	char    sstssnmn[41];
	char    sstrsj[21];
	char    sstrsn[21];
	char    sstsbt[3];
	char    ttsstflg;
	char    rucd[3];
	short   irikmksu;
	char    bmskn[51];
	char    irinrsbt[3];
	char    irihsmkbn;
	char    caresstflg;
	char    tktyflg;
	char    apkntino[14];
	char    sdnm[21];
	char    bko1[21];
	char    bko2[21];
	char    bko3[21];
	char    zstrdh[27];
	char    zsssdh[27];
	char    stlzsssdh[27];
	char    stlzsssip[16];
	char    stlzssssyaid[9];
	char    ksndh[27];
	char    oyasstcd[8];
	char    trkdh[27];
}	Kanjya;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKanjyaSelectAll( Kanjya** arrayOut, int* numOut );
long ZdbKanjyaSelectKey( Kanjya* pKey, Kanjya** arrayOut, int* numOut );
long ZdbKanjyaInsert( Kanjya* rec );
long ZdbKanjyaUpdate( Kanjya* rec );
long ZdbKanjyaDelete( Kanjya* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
