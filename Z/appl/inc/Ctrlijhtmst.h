/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Ctrlijhtmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Ctrlijhtmst_h_
#define _Ctrlijhtmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Ctrlijhtmst {
	char    bskkbn[5];
	char    nbkmkcd[8];
	short   ctrlhnsu;
	char    kyuhniflg;
	short   sjhnsu;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Ctrlijhtmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbCtrlijhtmstSelectAll( Ctrlijhtmst** arrayOut, int* numOut );
long ZdbCtrlijhtmstSelectKey( Ctrlijhtmst* pKey, Ctrlijhtmst** arrayOut, int* numOut );
long ZdbCtrlijhtmstInsert( Ctrlijhtmst* rec );
long ZdbCtrlijhtmstUpdate( Ctrlijhtmst* rec );
long ZdbCtrlijhtmstDelete( Ctrlijhtmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
