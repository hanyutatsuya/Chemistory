/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：Messagemst.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Messagemst_h_
#define _Messagemst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Messagemst {
	char    msgcd[9];
	char    status;
	char    msgniyo[101];
	sqlint32  msgbtn;
	sqlint32  msgico;
	char    hnktntid[9];
	char    ksndh[27];
}	Messagemst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbMessagemstSelectAll( Messagemst** arrayOut, int* numOut );
long ZdbMessagemstSelectKey( Messagemst* pKey, Messagemst** arrayOut, int* numOut );
long ZdbMessagemstInsert( Messagemst* rec );
long ZdbMessagemstUpdate( Messagemst* rec );
long ZdbMessagemstDelete( Messagemst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
