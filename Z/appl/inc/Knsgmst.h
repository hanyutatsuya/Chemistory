/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Knsgmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Knsgmst_h_
#define _Knsgmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Knsgmst {
	char    knsgrp[17];
	char    knsgrpnm[41];
	char    knsgrprs[21];
	char    seccd[3];
	char    knshokbn[41];
	char    knssbt;
	char    bgroup;
	char    unyokbn;
	short   seqkthsok;
	short   seqkthsng;
	char    wsssksok;
	char    wsssksng;
	short   minryo;
	short   maxryo;
	char    skitray[11];
	char    mbttray[11];
	char    skntray[11];
	char    ssttray[11];
	char    knsyb[8];
	char    ykcd[5];
	char    skiwsid[21];
	char    sknwsid[21];
	char    kkalstid[21];
	char    splblid[21];
	char    lstyb1[21];
	char    lstyb2[21];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Knsgmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKnsgmstSelectAll( Knsgmst** arrayOut, int* numOut );
long ZdbKnsgmstSelectKey( Knsgmst* pKey, Knsgmst** arrayOut, int* numOut );
long ZdbKnsgmstInsert( Knsgmst* rec );
long ZdbKnsgmstUpdate( Knsgmst* rec );
long ZdbKnsgmstDelete( Knsgmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
