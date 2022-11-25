/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Soukan.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Soukan_h_
#define _Soukan_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Soukan {
	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    knsgrp[17];
	char    kmkcd[8];
	char    skskmkcd[8];
	char    sriymd[11];
	char    kntno[14];
	char    kntketflg;
	char    skssriymd[11];
	char    skskntno[14];
	char    sksknsgslbcd[4];
	char    rawdata[21];
	char    knskka1[13];
	char    knskka2[25];
	char    knskka2kbn[3];
	char    kkahskcd[4];
	char    sdi[4];
	char    kkacmt1[6];
	char    kkacmt2[6];
	char    kkajkcd;
	char    ksbr[16];
	char    nbdo[3];
	char    ykdo[3];
	char    ksndh[27];
	char    trkdh[27];
}	Soukan;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbSoukanSelectAll( Soukan** arrayOut, int* numOut );
long ZdbSoukanSelectKey( Soukan* pKey, Soukan** arrayOut, int* numOut );
long ZdbSoukanInsert( Soukan* rec );
long ZdbSoukanUpdate( Soukan* rec );
long ZdbSoukanDelete( Soukan* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
