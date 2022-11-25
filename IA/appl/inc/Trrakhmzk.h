/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Trrakhmzk.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Trrakhmzk_h_
#define _Trrakhmzk_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Trrakhmzk {
	char    knskisymd[11];
	char    bnctrid[11];
	short   bnctrpos;
	char    asyrckid[11];
	short   asyrckpos;
	char    jhstksk;
	char    knsstflg;
	char    ksndh[27];
}	Trrakhmzk;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbTrrakhmzkSelectAll( Trrakhmzk** arrayOut, int* numOut );
long ZdbTrrakhmzkSelectKey( Trrakhmzk* pKey, Trrakhmzk** arrayOut, int* numOut );
long ZdbTrrakhmzkInsert( Trrakhmzk* rec );
long ZdbTrrakhmzkUpdate( Trrakhmzk* rec );
long ZdbTrrakhmzkDelete( Trrakhmzk* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
