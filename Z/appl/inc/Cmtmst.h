/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Cmtmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Cmtmst_h_
#define _Cmtmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Cmtmst {
	char    cmcd[6];
	char    cmtkg[3];
	char    cmtnm[83];
	char    cmtnmj[81];
	char    knskka1[13];
	char    kkahskcd[4];
	char    akaden;
	char    ijouchi;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Cmtmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbCmtmstSelectAll( Cmtmst** arrayOut, int* numOut );
long ZdbCmtmstSelectKey( Cmtmst* pKey, Cmtmst** arrayOut, int* numOut );
long ZdbCmtmstInsert( Cmtmst* rec );
long ZdbCmtmstUpdate( Cmtmst* rec );
long ZdbCmtmstDelete( Cmtmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
