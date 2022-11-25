/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Skrymst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Skrymst_h_
#define _Skrymst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Skrymst {
	char    skerr[4];
	char    skry[21];
	char    tkhkkbn;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Skrymst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbSkrymstSelectAll( Skrymst** arrayOut, int* numOut );
long ZdbSkrymstSelectKey( Skrymst* pKey, Skrymst** arrayOut, int* numOut );
long ZdbSkrymstInsert( Skrymst* rec );
long ZdbSkrymstUpdate( Skrymst* rec );
long ZdbSkrymstDelete( Skrymst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
