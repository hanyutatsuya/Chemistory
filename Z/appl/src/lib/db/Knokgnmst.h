/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Knokgnmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Knokgnmst_h_
#define _Knokgnmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Knokgnmst {
	char    userid[9];
	char    systemid[11];
	char    sykiokflg;
	char    nrykokflg;
	char    sysiokflg;
	char    sntnokflg;
	char    knjaokflg;
	char    generalflg[101];
	char    staymd[11];
	char    endymd[11];
	char    trkymd[11];
	char    hnkymd[11];
}	Knokgnmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKnokgnmstSelectAll( Knokgnmst** arrayOut, int* numOut );
long ZdbKnokgnmstSelectKey( Knokgnmst* pKey, Knokgnmst** arrayOut, int* numOut );
long ZdbKnokgnmstInsert( Knokgnmst* rec );
long ZdbKnokgnmstUpdate( Knokgnmst* rec );
long ZdbKnokgnmstDelete( Knokgnmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
