/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Bssizok.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Bssizok_h_
#define _Bssizok_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Bssizok {
	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   bssino;
	char    ecd[4];
	char    sstcd[8];
	char    srknm[31];
	char    knjnmn[61];
	char    ngkbn;
	char    krtno[41];
	char    knjid[16];
	char    btnm[31];
	char    knjnmkey[61];
	char    ttinm[41];
	char    sbtkbn;
	char    birthday[9];
	char    birthdaykbn;
	char    age[4];
	char    agekbn;
	char    zrcd[5];
	char    sstme[9];
	char    ssymd[11];
	char    tntme[5];
	char    tntni;
	char    tnryo[6];
	char    tnryotni;
	char    bshdh[27];
	char    ksndh[27];
}	Bssizok;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbBssizokSelectAll( Bssizok** arrayOut, int* numOut );
long ZdbBssizokSelectKey( Bssizok* pKey, Bssizok** arrayOut, int* numOut );
long ZdbBssizokInsert( Bssizok* rec );
long ZdbBssizokUpdate( Bssizok* rec );
long ZdbBssizokDelete( Bssizok* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
