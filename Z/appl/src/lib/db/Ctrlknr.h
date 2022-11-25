/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Ctrlknr.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Ctrlknr_h_
#define _Ctrlknr_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Ctrlknr {
	char    knskisymd[11];
	char    bskkbn[5];
	char    bsklne[5];
	char    bskgok[7];
	sqlint32  ctrlno;
	char    ctrlhdflg;
	char    ctrlktflg;
	char    ksndh[27];
}	Ctrlknr;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbCtrlknrSelectAll( Ctrlknr** arrayOut, int* numOut );
long ZdbCtrlknrSelectKey( Ctrlknr* pKey, Ctrlknr** arrayOut, int* numOut );
long ZdbCtrlknrInsert( Ctrlknr* rec );
long ZdbCtrlknrUpdate( Ctrlknr* rec );
long ZdbCtrlknrDelete( Ctrlknr* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
