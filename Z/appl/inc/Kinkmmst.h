/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Kinkmmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Kinkmmst_h_
#define _Kinkmmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Kinkmmst {
	char    kmkcd[8];
	char    smpcd[8];
	char    seccd[3];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Kinkmmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKinkmmstSelectAll( Kinkmmst** arrayOut, int* numOut );
long ZdbKinkmmstSelectKey( Kinkmmst* pKey, Kinkmmst** arrayOut, int* numOut );
long ZdbKinkmmstInsert( Kinkmmst* rec );
long ZdbKinkmmstUpdate( Kinkmmst* rec );
long ZdbKinkmmstDelete( Kinkmmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
