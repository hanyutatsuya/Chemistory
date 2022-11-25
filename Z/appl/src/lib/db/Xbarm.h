/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Xbarm.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Xbarm_h_
#define _Xbarm_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Xbarm {
	char    knskisymd[11];
	char    bskkbn[5];
	char    bsklne[5];
	char    bskgok[7];
	char    knsgrp[17];
	char    kmkcd[8];
	char    nbkmkcd[8];
	sqlint32  pltno;
	sqlint32  knsseqst;
	sqlint32  knsseqed;
	sqlint32  bskseqst;
	sqlint32  bskseqed;
	short   pltseqst;
	short   pltseqed;
	short   pltsu;
	char    xbarmkka[25];
	char    xbarmjtkbn;
	char    xbarmjkflg;
	char    ksndh[27];
}	Xbarm;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbXbarmSelectAll( Xbarm** arrayOut, int* numOut );
long ZdbXbarmSelectKey( Xbarm* pKey, Xbarm** arrayOut, int* numOut );
long ZdbXbarmInsert( Xbarm* rec );
long ZdbXbarmUpdate( Xbarm* rec );
long ZdbXbarmDelete( Xbarm* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
