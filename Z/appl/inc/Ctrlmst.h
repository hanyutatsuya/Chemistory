/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Ctrlmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Ctrlmst_h_
#define _Ctrlmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Ctrlmst {
	char    bskkbn[5];
	char    nbkmkcd[8];
	char    ctrlsbt[21];
	char    ctrlnm[41];
	char    ctrlrs[21];
	char    syklotno[21];
	char    ctrllbl[3];
	char    ctrlx[13];
	char    ctrlsd[13];
	char    ctrlcv[13];
	char    valuer[13];
	char    maxr[13];
	short   sstnksu;
	char    tankj[17];
	char    facterjd1[13];
	char    facterjd2[13];
	char    factersd1[13];
	char    factersd2[13];
	char    basejd1[13];
	char    basejd2[13];
	char    basesd1[13];
	char    basesd2[13];
	sqlint32  ksikjnspsu;
	char    shrnglwhf[13];
	char    shrnghihf[13];
	char    shrnglwhb[13];
	char    shrnghihb[13];
	char    hstkjntn[13];
	char    hstkzmhb[13];
	short   hstkaikyu;
	sqlint32  filenum;
	char    ykkigen[11];
	char    gktks[13];
	short   ctrlhyjn;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Ctrlmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbCtrlmstSelectAll( Ctrlmst** arrayOut, int* numOut );
long ZdbCtrlmstSelectKey( Ctrlmst* pKey, Ctrlmst** arrayOut, int* numOut );
long ZdbCtrlmstInsert( Ctrlmst* rec );
long ZdbCtrlmstUpdate( Ctrlmst* rec );
long ZdbCtrlmstDelete( Ctrlmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
