/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Kntidunknown.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Kntidunknown_h_
#define _Kntidunknown_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Kntidunknown {
	char    knskisymd[11];
	char    bskkbn[11];
	char    bsklne[11];
	char    bskgok[6];
	char    bskmjno[6];
	sqlint32  bskseq;
	sqlint32  nbkmkcd;
	char    knshu[41];
	char    bskerrsts[3];
	char    rawdata[31];
	char    sktdh[27];
	sqlint32  ctrlno;
	char    ksbr[9];
	char    nbdolbl[9];
	char    nbdoerr[4];
	char    ykdolbl[9];
	char    ykdoerr[4];
	char    etclbl[9];
	char    etcerr[4];
	char    ksndh[27];
}	Kntidunknown;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKntidunknownSelectAll( Kntidunknown** arrayOut, int* numOut );
long ZdbKntidunknownSelectKey( Kntidunknown* pKey, Kntidunknown** arrayOut, int* numOut );
long ZdbKntidunknownInsert( Kntidunknown* rec );
long ZdbKntidunknownUpdate( Kntidunknown* rec );
long ZdbKntidunknownDelete( Kntidunknown* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
