/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Ijyosya.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Ijyosya_h_
#define _Ijyosya_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Ijyosya {
	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    knsgrp[17];
	char    kmkcd[8];
	char    sstcd[8];
	char    knjnmn[61];
	char    rawdata[21];
	char    knskka1[13];
	char    knskka2[25];
	char    knskka2kbn[3];
	char    kkahskcd[4];
	char    sdi[4];
	char    kkacmt1[6];
	char    kkacmt2[6];
	char    ijkbnm;
	char    ijkbnf;
	char    ijkbnn;
	char    tbijkbnm;
	char    tbijkbnf;
	char    tbijkbnn;
	char    ksbr[16];
	char    nbdo[3];
	char    ykdo[3];
	char    hkkdh[27];
	char    ksndh[27];
	char    oyasstcd[8];
}	Ijyosya;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbIjyosyaSelectAll( Ijyosya** arrayOut, int* numOut );
long ZdbIjyosyaSelectKey( Ijyosya* pKey, Ijyosya** arrayOut, int* numOut );
long ZdbIjyosyaInsert( Ijyosya* rec );
long ZdbIjyosyaUpdate( Ijyosya* rec );
long ZdbIjyosyaDelete( Ijyosya* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
