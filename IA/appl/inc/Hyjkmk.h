/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Hyjkmk.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Hyjkmk_h_
#define _Hyjkmk_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Hyjkmk {
	char    defkbn;
	char    wkupapp[33];
	char    loginid[9];
	char    hyjniy01[51];
	char    hyjniy02[51];
	char    hyjniy03[51];
	char    hyjniy04[51];
	char    hyjniy05[51];
	char    hyjniy06[51];
	char    hyjniy07[51];
	char    hyjniy08[51];
	char    hyjniy09[51];
	char    hyjniy10[51];
	char    hyjniy11[51];
	char    hyjniy12[51];
	char    hyjniy13[51];
	char    hyjniy14[51];
	char    hyjniy15[51];
	char    hyjniy16[51];
	char    hyjniy17[51];
	char    hyjniy18[51];
	char    hyjniy19[51];
	char    hyjniy20[51];
	char    hyjniy21[51];
	char    hyjniy22[51];
	char    hyjniy23[51];
	char    hyjniy24[51];
	char    hyjniy25[51];
	char    hyjniy26[51];
	char    hyjniy27[51];
	char    hyjniy28[51];
	char    hyjniy29[51];
	char    hyjniy30[51];
	char    hyjniy31[51];
	char    hyjniy32[51];
	char    hyjniy33[51];
	char    hyjniy34[51];
	char    hyjniy35[51];
	char    hyjniy36[51];
	char    hyjniy37[51];
	char    hyjniy38[51];
	char    hyjniy39[51];
	char    hyjniy40[51];
	char    hyjniy41[51];
	char    hyjniy42[51];
	char    hyjniy43[51];
	char    hyjniy44[51];
	char    hyjniy45[51];
	char    hyjniy46[51];
	char    hyjniy47[51];
	char    hyjniy48[51];
	char    hyjniy49[51];
	char    hyjniy50[51];
	char    ksndh[27];
}	Hyjkmk;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbHyjkmkSelectAll( Hyjkmk** arrayOut, int* numOut );
long ZdbHyjkmkSelectKey( Hyjkmk* pKey, Hyjkmk** arrayOut, int* numOut );
long ZdbHyjkmkInsert( Hyjkmk* rec );
long ZdbHyjkmkUpdate( Hyjkmk* rec );
long ZdbHyjkmkDelete( Hyjkmk* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
