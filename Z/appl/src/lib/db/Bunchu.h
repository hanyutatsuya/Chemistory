/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Bunchu.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Bunchu_h_
#define _Bunchu_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Bunchu {
	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    sriymd[11];
	char    kntno[14];
	char    kntketflg;
	char    smpcd[8];
	char    kmkcd[8];
	short   smpcditno;
	char    chkmj[5];
	char    trid[11];
	short   trpos;
	char    asyrckid[11];
	short   asyrckpos;
	char    id2[11];
	short   id2pos;
	char    sbtkbn;
	char    age[4];
	char    agekbn;
	char    tntme[5];
	char    tntni;
	char    tnryo[6];
	char    tnryotni;
	char    sstcd[8];
	char    ecd[4];
	char    bckid[4];
	char    jtflg;
	char    knssyr;
	char    tknflg;
	char    ttkkflg;
	char    bnckka;
	short   srtkey;
	char    ksndh[27];
	char    trkdh[27];
}	Bunchu;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbBunchuSelectAll( Bunchu** arrayOut, int* numOut );
long ZdbBunchuSelectKey( Bunchu* pKey, Bunchu** arrayOut, int* numOut );
long ZdbBunchuInsert( Bunchu* rec );
long ZdbBunchuUpdate( Bunchu* rec );
long ZdbBunchuDelete( Bunchu* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
