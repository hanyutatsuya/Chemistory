/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：GD105Kenzok.h
 *     機能概要  ：検体属性情報アクセス関数(報告処理)
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2009-05-11                    Create
 **********************************************************************/
#ifndef _GD105Kenzok_h_
#define _GD105Kenzok_h_

/********************************************************************/
/*  インクルード宣言                                                */
/********************************************************************/
#include "bml_DBCom.h"

/********************************************************************/
/* テーブル構造体定義                                               */
/********************************************************************/
typedef struct _Kenzok {
	char    utkymd[10+1];
	char    irino[11+1];
	char    iriketflg;
	short   zssdino;
	char    sriymd[10+1];
	char    kntno[13+1];
	char    kntketflg;
	char    knsgslbcd[3+1];
	short   kntzssdino;
	char    knttcyymd[10+1];
	char    fszrgrp[2+1];
	char    irikntryo[5+1];
	char    irikntryotni;
	char    gnkntryo[5+1];
	char    gnkntryotni;
	char    chkmj[4+1];
	char    rucd[2+1];
	char    ykcd[20+1];
	char    htkfkiri;
	char    ysnflg;
	char    kntfrflg;
	char    ykzrcd[4+1];
	char    hzzrcd[4+1];
	char    kntjtflg;
	char    knttktkbn;
	char    hbncflg;
	char    kntzsssflg;
	char    kntzstrdh[26+1];
	char    kntzsssdh[26+1];
	char    stlkntzsssdh[26+1];
	char    stlkntzsssip[15+1];
	char    stlkntzssssyaid[8+1];
	char    sklblflg;
	char    zrcd[4+1];
	char    sstme[8+1];
	char    ssymd[10+1];
	char    tntme[4+1];
	char    tntni;
	char    tnryo[5+1];
	char    tnryotni;
	char    ssbi[20+1];
	char    sshhu[20+1];
	char    hkflg[2+1];
	char    msriymd[10+1];
	char    mkntno[13+1];
	char    id2[10+1];
	short   id2pos;
	char    id3[10+1];
	short   id3pos;
	char    sntrno[10+1];
	char    sntnno[10+1];
	char    nstsgflg;
	char    hknjk;
	char    hknjkksndh[26+1];
	char    ksndh[26+1];
	char    trkdh[26+1];
}	Kenzok;

/******************************************************************************/
/* プロトタイプ宣言                                                           */
/******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

long dGD105_KENZOK_Sel_latestZSSDINO( Kenzok* pKey, Kenzok** arrayOut, int* numOut );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
