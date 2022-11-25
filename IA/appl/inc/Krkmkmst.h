/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Krkmkmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Krkmkmst_h_
#define _Krkmkmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Krkmkmst {
	char    kmkcd[8];
	char    krkmkcd[8];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Krkmkmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKrkmkmstSelectAll( Krkmkmst** arrayOut, int* numOut );
long ZdbKrkmkmstSelectKey( Krkmkmst* pKey, Krkmkmst** arrayOut, int* numOut );
long ZdbKrkmkmstInsert( Krkmkmst* rec );
long ZdbKrkmkmstUpdate( Krkmkmst* rec );
long ZdbKrkmkmstDelete( Krkmkmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
