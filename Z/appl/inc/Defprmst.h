/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Defprmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Defprmst_h_
#define _Defprmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Defprmst {
	char    compnm[21];
	char    tyhyoid[21];
	char    prntrnm[21];
	char    cstno;
	char    hnktntid[9];
	char    ksndh[27];
}	Defprmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbDefprmstSelectAll( Defprmst** arrayOut, int* numOut );
long ZdbDefprmstSelectKey( Defprmst* pKey, Defprmst** arrayOut, int* numOut );
long ZdbDefprmstInsert( Defprmst* rec );
long ZdbDefprmstUpdate( Defprmst* rec );
long ZdbDefprmstDelete( Defprmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
