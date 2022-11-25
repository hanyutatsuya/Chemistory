/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Zairmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Zairmst_h_
#define _Zairmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Zairmst {
	char    zaicd[5];
	char    zainmkn[11];
	char    zainmkj[21];
	char    zainmej[41];
	char    zaikg[3];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Zairmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbZairmstSelectAll( Zairmst** arrayOut, int* numOut );
long ZdbZairmstSelectKey( Zairmst* pKey, Zairmst** arrayOut, int* numOut );
long ZdbZairmstInsert( Zairmst* rec );
long ZdbZairmstUpdate( Zairmst* rec );
long ZdbZairmstDelete( Zairmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
