/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Chksbtmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Chksbtmst_h_
#define _Chksbtmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Chksbtmst {
	char    chksbt[3];
	char    chkkmmn[21];
	short   chktmg;
	short   chkkbn;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Chksbtmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbChksbtmstSelectAll( Chksbtmst** arrayOut, int* numOut );
long ZdbChksbtmstSelectKey( Chksbtmst* pKey, Chksbtmst** arrayOut, int* numOut );
long ZdbChksbtmstInsert( Chksbtmst* rec );
long ZdbChksbtmstUpdate( Chksbtmst* rec );
long ZdbChksbtmstDelete( Chksbtmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
