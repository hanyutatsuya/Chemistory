/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Mechmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Mechmst_h_
#define _Mechmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Mechmst {
	char    bskkbn[5];
	char    nbkmcd[8];
	char    chnm[17];
	char    kmkcd[8];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Mechmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbMechmstSelectAll( Mechmst** arrayOut, int* numOut );
long ZdbMechmstSelectKey( Mechmst* pKey, Mechmst** arrayOut, int* numOut );
long ZdbMechmstInsert( Mechmst* rec );
long ZdbMechmstUpdate( Mechmst* rec );
long ZdbMechmstDelete( Mechmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
