/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Knkmhmzk.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Knkmhmzk_h_
#define _Knkmhmzk_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Knkmhmzk {
	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    kmkcd[8];
	char    sriymd1[11];
	char    kntno1[14];
	char    knt1ketflg;
	char    knsgslbcd1[4];
	short   kntzssdino1;
	char    sriymd2[11];
	char    kntno2[14];
	char    knt2ketflg;
	char    knsgslbcd2[4];
	short   kntzssdino2;
	char    sriymd3[11];
	char    kntno3[14];
	char    knt3ketflg;
	char    knsgslbcd3[4];
	short   kntzssdino3;
	char    sriymd4[11];
	char    kntno4[14];
	char    knt4ketflg;
	char    knsgslbcd4[4];
	short   kntzssdino4;
	char    sriymd5[11];
	char    kntno5[14];
	char    knt5ketflg;
	char    knsgslbcd5[4];
	short   kntzssdino5;
	char    ksndh[27];
}	Knkmhmzk;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKnkmhmzkSelectAll( Knkmhmzk** arrayOut, int* numOut );
long ZdbKnkmhmzkSelectKey( Knkmhmzk* pKey, Knkmhmzk** arrayOut, int* numOut );
long ZdbKnkmhmzkInsert( Knkmhmzk* rec );
long ZdbKnkmhmzkUpdate( Knkmhmzk* rec );
long ZdbKnkmhmzkDelete( Knkmhmzk* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
