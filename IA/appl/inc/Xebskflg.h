/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Xebskflg.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Xebskflg_h_
#define _Xebskflg_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Xebskflg {
	char    knskisymd[11];
	char    sriymd[11];
	char    kntno[21];
	char    kntketflg;
	sqlint32  smpcd;
	short   knssu;
	short   knssueda;
	char    flgsbt[3];
	char    bskkbn[11];
	char    bsklne[11];
	char    bskgok[6];
	char    bskmjno[6];
	char    asyrckid[11];
	short   asyrckpos;
	char    xeflg01;
	char    xeflg02;
	char    xeflg03;
	char    xeflg04;
	char    xeflg05;
	char    xeflg06;
	char    xeflg07;
	char    xeflg08;
	char    xeflg09;
	char    xeflg10;
	char    xeflg11;
	char    xeflg12;
	char    xeflg13;
	char    xeflg14;
	char    xeflg15;
	char    xeflg16;
	char    ksndh[27];
}	Xebskflg;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbXebskflgSelectAll( Xebskflg** arrayOut, int* numOut );
long ZdbXebskflgSelectKey( Xebskflg* pKey, Xebskflg** arrayOut, int* numOut );
long ZdbXebskflgInsert( Xebskflg* rec );
long ZdbXebskflgUpdate( Xebskflg* rec );
long ZdbXebskflgDelete( Xebskflg* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
