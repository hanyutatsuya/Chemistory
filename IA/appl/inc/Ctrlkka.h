/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Ctrlkka.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Ctrlkka_h_
#define _Ctrlkka_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Ctrlkka {
	char    knskisymd[11];
	char    bskkbn[5];
	char    bsklne[5];
	char    bskgok[7];
	char    knsgrp[17];
	char    kmkcd[8];
	char    nbkmkcd[8];
	sqlint32  ctrlno;
	char    ctrlsbt[21];
	short   ctrlsbteda;
	char    ctrllbl[3];
	char    tstrflg;
	char    asyrckid[11];
	short   asyrckpos;
	sqlint32  knsseq;
	sqlint32  bskseq;
	short   bthno;
	sqlint32  bthrckjbn;
	char    syklotno[21];
	char    sktti[25];
	char    knzti[25];
	char    knztistflg;
	char    sktdh[27];
	short   ctrljti;
	char    chkzmflg;
	char    facter[13];
	char    base[13];
	char    kosijt;
	char    kositts[9];
	char    kosidh[27];
	char    ksndh[27];
}	Ctrlkka;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbCtrlkkaSelectAll( Ctrlkka** arrayOut, int* numOut );
long ZdbCtrlkkaSelectKey( Ctrlkka* pKey, Ctrlkka** arrayOut, int* numOut );
long ZdbCtrlkkaInsert( Ctrlkka* rec );
long ZdbCtrlkkaUpdate( Ctrlkka* rec );
long ZdbCtrlkkaDelete( Ctrlkka* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
