/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：A205Kmkmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Kmkmst_h_
#define _Kmkmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Kmkmst {
	char    knsgrp[17];
	char    kmkcd[8];
	char    kmknm[37];
	char    kmknmj[47];
	char    kmkrs[17];
	char    kmkrsj[21];
	char    kmknme[51];
	char    kmkhsknmj[21];
	char    fkkmknm[37];
	char    fkkmknmj[47];
	char    smpcd[8];
	char    oyakmkcd[8];
	char    korrn[8];
	char    seccd[3];
	char    stnflg;
	short   sstnksu;
	char    assay[41];
	short   fkjbn;
	char    fkbnkkb;
	char    tskflg[3];
	char    tktflg[3];
	char    ltmmnflg;
	char    zrkbn;
	sqlint32  bcrtj;
	sqlint32  bcrsr;
	sqlint32  bcrsn;
	char    yknknsflg;
	short   hrynsu;
	char    jdhskka[13];
	short   hyjijn;
	char    ksnkmkflg;
	char    hsiumflg;
	char    gmin[9];
	char    ghaba[9];
	short   rrkhzn;
	char    nyuyouflg;
	char    tstrflg;
	char    kmksbt;
	char    sgchkflg;
	char    ksjhflg;
	char    kssgflg;
	char    xmskflg;
	char    xmchkflg;
	short   xmcount;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Kmkmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long A205KmkmstSelKey( Kmkmst* pKey, Kmkmst** arrayOut, int* numOut );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
