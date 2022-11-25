/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Kgymdmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Kgymdmst_h_
#define _Kgymdmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Kgymdmst {
	char    kgymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Kgymdmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKgymdmstSelectAll( Kgymdmst** arrayOut, int* numOut );
long ZdbKgymdmstSelectKey( Kgymdmst* pKey, Kgymdmst** arrayOut, int* numOut );
long ZdbKgymdmstInsert( Kgymdmst* rec );
long ZdbKgymdmstUpdate( Kgymdmst* rec );
long ZdbKgymdmstDelete( Kgymdmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
