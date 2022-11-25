/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：A105realchk.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _A105realchk_h_
#define _Realchk_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Realchk {
	char    knskisymd[11];
	char    sriymd[11];
	char    kntno[14];
	char    kntketflg;
	char    knsgrp[17];
	char    kmkcd[8];
	short   knssu;
	short   knssueda;
	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    trid[11];
	short   trpos;
	char    asyrckid[11];
	short   asyrckpos;
	char    bskkbn[5];
	char    nbkmkcd[8];
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
	char    renjicpara[257];
	char    soukn1para[257];
	char    kanrenpara[257];
	char    bunkkupara[257];
	char    kesseipara[257];
	char    rirekipara[257];
	char    syougopara[257];
	char    keisanpara[1025];
	char    per100para[257];
	char    tousekpara[257];
	char    kisyakpara[257];
	char    kouseipara[257];
	char    syoungpara[257];
	char    soukn2para[257];
	char    fukaptpara[257];
	char    yobipara01[257];
	char    yobipara02[257];
	char    yobipara03[257];
	char    yobipara04[257];
	char    yobipara05[257];
	char    ksndh[27];
}	Realchk;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ABunRealInsert( Realchk* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
