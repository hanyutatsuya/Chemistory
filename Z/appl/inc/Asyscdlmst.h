/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Asyscdlmst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Asyscdlmst_h_
#define _Asyscdlmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Asyscdlmst {
	char    knsgrp[17];
	char    asystartymd[11];
	char    asyendymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Asyscdlmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbAsyscdlmstSelectAll( Asyscdlmst** arrayOut, int* numOut );
long ZdbAsyscdlmstSelectKey( Asyscdlmst* pKey, Asyscdlmst** arrayOut, int* numOut );
long ZdbAsyscdlmstInsert( Asyscdlmst* rec );
long ZdbAsyscdlmstUpdate( Asyscdlmst* rec );
long ZdbAsyscdlmstDelete( Asyscdlmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
