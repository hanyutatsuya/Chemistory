/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Knssnkjyk.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Knssnkjyk_h_
#define _Knssnkjyk_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Knssnkjyk {
	char    knskisymd[11];
	sqlint32  keikseq;
	char    koteikbn;
	char    datazok;
	char    bskkbn[5];
	char    bskgok[7];
	sqlint32  syukka;
	char    jikan[5];
	char    ksndh[27];
}	Knssnkjyk;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKnssnkjykSelectAll( Knssnkjyk** arrayOut, int* numOut );
long ZdbKnssnkjykSelectKey( Knssnkjyk* pKey, Knssnkjyk** arrayOut, int* numOut );
long ZdbKnssnkjykInsert( Knssnkjyk* rec );
long ZdbKnssnkjykUpdate( Knssnkjyk* rec );
long ZdbKnssnkjykDelete( Knssnkjyk* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
