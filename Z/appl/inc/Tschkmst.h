/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Tschkmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Tschkmst_h_
#define _Tschkmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Tschkmst {
	char    kmkcdzen[8];
	char    kmkcdgo[8];
	char    tskchktyp;
	char    maxval[21];
	char    minval[21];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Tschkmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbTschkmstSelectAll( Tschkmst** arrayOut, int* numOut );
long ZdbTschkmstSelectKey( Tschkmst* pKey, Tschkmst** arrayOut, int* numOut );
long ZdbTschkmstInsert( Tschkmst* rec );
long ZdbTschkmstUpdate( Tschkmst* rec );
long ZdbTschkmstDelete( Tschkmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
