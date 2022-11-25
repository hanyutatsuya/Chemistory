/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Kenzok.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-10                    Create
 **********************************************************************/
#ifndef _A205Kenzok_h_
#define _A205Kenzok_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Kenzok {
	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    sriymd[11];
	char    kntno[14];
	char    kntketflg;
	char    knsgslbcd[4];
	short   kntzssdino;
	char    knttcyymd[11];
	char    fszrgrp[3];
	char    irikntryo[6];
	char    irikntryotni;
	char    gnkntryo[6];
	char    gnkntryotni;
	char    chkmj[5];
	char    rucd[3];
	char    ykcd[21];
	char    htkfkiri;
	char    ysnflg;
	char    kntfrflg;
	char    ykzrcd[4];
	char    hzzrcd[4];
	char    kntjtflg;
	char    knttktkbn;
	char    hbncflg;
	char    kntzsssflg;
	char    kntzstrdh[27];
	char    kntzsssdh[27];
	char    stlkntzsssdh[27];
	char    stlkntzsssip[16];
	char    stlkntzssssyaid[9];
	char    sklblflg;
	char    zrcd[4];
	char    sstme[9];
	char    ssymd[11];
	char    tntme[5];
	char    tntni;
	char    tnryo[6];
	char    tnryotni;
	char    ssbi[21];
	char    sshhu[21];
	char    hkflg[3];
	char    msriymd[11];
	char    mkntno[14];
	char    id2[11];
	short   id2pos;
	char    id3[11];
	short   id3pos;
	char    sntrno[11];
	char    sntnno[11];
	char    nstsgflg;
	char    hknjk;
	char    hknjkksndh[27];
	char    ksndh[27];
	char    trkdh[27];
}	Kenzok;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long AZokuSel( Kenzok* pKey, Kenzok** arrayOut, int* numOut );
long AZokuInsert( Kenzok* rec );
long AZokuUpdate( Kenzok* rec );
long AZokuDelete( Kenzok* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
