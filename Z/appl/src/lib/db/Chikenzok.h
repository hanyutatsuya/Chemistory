/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Chikenzok.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Chikenzok_h_
#define _Chikenzok_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Chikenzok {
	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    prtclno[12];
	char    kosstcd[8];
	char    tytme[5];
	char    tyryo[6];
	char    tyryotni[4];
	char    yzfktme[5];
	char    ikasflg;
	short   kntsu;
	short   kmksu;
	char    sspit[3];
	char    zrcd01[6];
	char    zrcd02[6];
	char    zrcd03[6];
	char    zrcd04[6];
	char    zrcd05[6];
	char    zrcd06[6];
	char    zrkg01[3];
	char    zrkg02[3];
	char    zrkg03[3];
	char    zrkg04[3];
	char    zrkg05[3];
	char    zrkg06[3];
	char    hrseq[5];
	char    kntksflg;
	char    gcpflg;
	char    prtclnm[41];
	char    ksndh[27];
}	Chikenzok;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbChikenzokSelectAll( Chikenzok** arrayOut, int* numOut );
long ZdbChikenzokSelectKey( Chikenzok* pKey, Chikenzok** arrayOut, int* numOut );
long ZdbChikenzokInsert( Chikenzok* rec );
long ZdbChikenzokUpdate( Chikenzok* rec );
long ZdbChikenzokDelete( Chikenzok* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
