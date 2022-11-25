/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Melinemst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Melinemst_h_
#define _Melinemst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Melinemst {
	char    bsklne[5];
	char    bskkbn[11];
	short   memax;
	char    linenm[11];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Melinemst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbMelinemstSelectAll( Melinemst** arrayOut, int* numOut );
long ZdbMelinemstSelectKey( Melinemst* pKey, Melinemst** arrayOut, int* numOut );
long ZdbMelinemstInsert( Melinemst* rec );
long ZdbMelinemstUpdate( Melinemst* rec );
long ZdbMelinemstDelete( Melinemst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
