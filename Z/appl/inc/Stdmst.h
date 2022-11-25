/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Stdmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Stdmst_h_
#define _Stdmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Stdmst {
	char    bskkbn[5];
	char    nbkmkcd[8];
	short   stdsbt;
	char    kmkcd[8];
	char    stdnm[41];
	char    stdrk[21];
	char    stdx[9];
	char    stdsd[9];
	char    stdcv[9];
	char    valuer[9];
	char    maxr[9];
	short   place;
	short   unit[17];
	short   facter1[9];
	short   facter2[9];
	char    base1[9];
	char    base2[9];
	sqlint32  filenum;
	char    kigen[27];
	short   ctlstart;
	short   ctlcnt;
	short   ctlpos;
	short   ctlitv;
	short   ctllv;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Stdmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbStdmstSelectAll( Stdmst** arrayOut, int* numOut );
long ZdbStdmstSelectKey( Stdmst* pKey, Stdmst** arrayOut, int* numOut );
long ZdbStdmstInsert( Stdmst* rec );
long ZdbStdmstUpdate( Stdmst* rec );
long ZdbStdmstDelete( Stdmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
