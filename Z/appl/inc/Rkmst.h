/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Rkmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2008-01-07                    Create
 **********************************************************************/
#ifndef _Rkmst_h_
#define _Rkmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Rkmst {
	char    smpcd[8];
	char    rksbt;
	char    rknm[21];
	short   rkknhsu;
	short   trrcksu;
	char    filskdir[129];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Rkmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbRkmstSelectAll( Rkmst** arrayOut, int* numOut );
long ZdbRkmstSelectKey( Rkmst* pKey, Rkmst** arrayOut, int* numOut );
long ZdbRkmstInsert( Rkmst* rec );
long ZdbRkmstUpdate( Rkmst* rec );
long ZdbRkmstDelete( Rkmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
