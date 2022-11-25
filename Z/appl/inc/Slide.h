/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Slide.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Slide_h_
#define _Slide_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Slide {
	char    knskisymd[11];
	char    sriymd[11];
	char    kntno[21];
	char    kntketflg;
	char    knsgrp[11];
	char    skssbt[3];
	sqlint32  knsseq;
	char    stkbn[11];
	short   stno;
	char    cstid[11];
	short   cstpos;
	char    hhnjtflg;
	char    ksndh[27];
}	Slide;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbSlideSelectAll( Slide** arrayOut, int* numOut );
long ZdbSlideSelectKey( Slide* pKey, Slide** arrayOut, int* numOut );
long ZdbSlideInsert( Slide* rec );
long ZdbSlideUpdate( Slide* rec );
long ZdbSlideDelete( Slide* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
