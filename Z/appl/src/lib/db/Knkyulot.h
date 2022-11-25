/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Knkyulot.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Knkyulot_h_
#define _Knkyulot_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Knkyulot {
	char    knskisymd[11];
	char    seccd[3];
	short   kkirilotno;
	char    jsndh[27];
	char    hkkdh[27];
	char    ksndh[27];
}	Knkyulot;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKnkyulotSelectAll( Knkyulot** arrayOut, int* numOut );
long ZdbKnkyulotSelectKey( Knkyulot* pKey, Knkyulot** arrayOut, int* numOut );
long ZdbKnkyulotInsert( Knkyulot* rec );
long ZdbKnkyulotUpdate( Knkyulot* rec );
long ZdbKnkyulotDelete( Knkyulot* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
