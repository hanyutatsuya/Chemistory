/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Secmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Secmst_h_
#define _Secmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Secmst {
	char    seccd[3];
	char    secnm[21];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Secmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbSecmstSelectAll( Secmst** arrayOut, int* numOut );
long ZdbSecmstSelectKey( Secmst* pKey, Secmst** arrayOut, int* numOut );
long ZdbSecmstInsert( Secmst* rec );
long ZdbSecmstUpdate( Secmst* rec );
long ZdbSecmstDelete( Secmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
