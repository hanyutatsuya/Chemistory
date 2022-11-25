/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Xeerrmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Xeerrmst_h_
#define _Xeerrmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Xeerrmst {
	short   errflg;
	char    flgsbt[11];
	char    errname[33];
	short   sksri;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Xeerrmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbXeerrmstSelectAll( Xeerrmst** arrayOut, int* numOut );
long ZdbXeerrmstSelectKey( Xeerrmst* pKey, Xeerrmst** arrayOut, int* numOut );
long ZdbXeerrmstInsert( Xeerrmst* rec );
long ZdbXeerrmstUpdate( Xeerrmst* rec );
long ZdbXeerrmstDelete( Xeerrmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
