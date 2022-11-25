/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Ninsiki.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Ninsiki_h_
#define _Ninsiki_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Ninsiki {
	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    sriymd[11];
	char    kntno[14];
	char    kntketflg;
	char    chkmj[5];
	char    asyrckid[11];
	short   asyrckpos;
	char    id2[11];
	short   id2pos;
	char    id3[11];
	short   id3pos;
	char    fuksuhn;
	char    ksndh[27];
	char    trkdh[27];
}	Ninsiki;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbNinsikiSelectAll( Ninsiki** arrayOut, int* numOut );
long ZdbNinsikiSelectKey( Ninsiki* pKey, Ninsiki** arrayOut, int* numOut );
long ZdbNinsikiInsert( Ninsiki* rec );
long ZdbNinsikiUpdate( Ninsiki* rec );
long ZdbNinsikiDelete( Ninsiki* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
