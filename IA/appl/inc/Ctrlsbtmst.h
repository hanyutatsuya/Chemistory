/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Ctrlsbtmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Ctrlsbtmst_h_
#define _Ctrlsbtmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Ctrlsbtmst {
	char    bskkbn[5];
	char    ctrlsbt[21];
	char    stirckid[11];
	short   stirckpos;
	char    ctrliti;
	short   ctrlcnt;
	short   ctrlstart;
	short   ctrlitv;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Ctrlsbtmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbCtrlsbtmstSelectAll( Ctrlsbtmst** arrayOut, int* numOut );
long ZdbCtrlsbtmstSelectKey( Ctrlsbtmst* pKey, Ctrlsbtmst** arrayOut, int* numOut );
long ZdbCtrlsbtmstInsert( Ctrlsbtmst* rec );
long ZdbCtrlsbtmstUpdate( Ctrlsbtmst* rec );
long ZdbCtrlsbtmstDelete( Ctrlsbtmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
