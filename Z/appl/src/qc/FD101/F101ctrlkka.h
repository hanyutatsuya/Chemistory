/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：F101ctrlkka.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-27                    Create
 **********************************************************************/
#ifndef _F101ctrlkka_h_
#define _F101ctrlkka_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Ctrlkka {
	char	knskisymd[11];
	char	bskkbn[5];
	char	bskgok[7];
	char	kmkcd[8];
	char	nbkmkcd[8];
	int		ctrlno;
/* INTEC DELL
DEL	long	ctrlno;
*/
/*
	short	ctrlno;
*/
	char	ctrlsbt[21];
	short	ctrlsbteda;
	short	ctrljti;
	char	chkzmflg;
}	Ctrlkka;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long FCtrlkkaSelectByKey(Ctrlkka** arrayOut, int* numOut, int fetchCnt);
long FCtrlUpdate( Ctrlkka* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
