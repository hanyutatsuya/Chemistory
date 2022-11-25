/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Bssikka.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Bssikka_h_
#define _Bssikka_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Bssikka {
	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   bssino;
	short   gyono;
	char    bssidt[129];
	char    ksndh[27];
}	Bssikka;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbBssikkaSelectAll( Bssikka** arrayOut, int* numOut );
long ZdbBssikkaSelectKey( Bssikka* pKey, Bssikka** arrayOut, int* numOut );
long ZdbBssikkaInsert( Bssikka* rec );
long ZdbBssikkaUpdate( Bssikka* rec );
long ZdbBssikkaDelete( Bssikka* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
