/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：A205kjnmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _A205kjnmst_h_
#define _A205kjnmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Kjnmst {
	char    kmkcd[8];
	char    kjno[4];
	char    kjsdino[3];
	char    zrcd[5];
	char    agerngkbn[3];
	char    etckbn[4];
	char    nichilw[6];
	char    nichihi[6];
	char    kjnmlw[9];
	char    kjnmhi[9];
	char    kjnflw[9];
	char    kjnfhi[9];
	char    kjnelw[9];
	char    kjnehi[9];
	char    genmlw[9];
	char    genmhi[9];
	char    genflw[9];
	char    genfhi[9];
	char    genelw[9];
	char    genehi[9];
	short   kjsstnksu;
	char    kjnmhkn[25];
	char    kjnmhkj[25];
	char    kjnfhkn[25];
	char    kjnfhkj[25];
	char    kjnohkn[25];
	char    kjnohkj[25];
	char    lwm1[9];
	char    lwm2[9];
	char    kjm1[9];
	char    kjm2[9];
	char    him1[9];
	char    him2[9];
	char    lwf1[9];
	char    lwf2[9];
	char    kjnnaf1[9];
	char    kjnnaf2[9];
	char    hif1[9];
	char    hif2[9];
	char    lwe1[9];
	char    lwe2[9];
	char    kje1[9];
	char    kje2[9];
	char    hie1[9];
	char    hie2[9];
	char    tankn[17];
	char    tankj[17];
	char    stjyken[61];
	char    kymstjn;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Kjnmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ABunKjnNoSel( Kjnmst* pKey, Kjnmst** arrayOut, int* numOut );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
