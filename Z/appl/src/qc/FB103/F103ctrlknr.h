/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：F103ctrlknr.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-27                    Create
 **********************************************************************/
#ifndef _F103ctrlknr_h_
#define _F103ctrlknr_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Ctrlknr {
	char	knskisymd[11];
	char	bskkbn[5];
	char	bsklne[5];
	char	bskgok[7];
	long	ctrlno;
	char	ctrlhdflg;
	char	ctrlktflg;
	char	ksndh[27];
}	Ctrlknr;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long FKtflgUpdate( Ctrlknr* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
