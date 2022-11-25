/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：GD105KekkaConv.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2009-05-19     K.Moriya       結果変換マスタ対応
 **********************************************************************/
#ifndef _GD105KekkaConv_h_
#define _GD105KekkaConv_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _KekkaConv {
    char    knskisymd[10+1];
    char    sriymd[10+1];
    char    kntno[13+1];
    char    knsgrp[16+1];
    char    kmkcd[7+1];
    short   knssu;
    short   knssueda;
    char    knskka1[12+1];
    char    knskka2[24+1];
    char    knskka2kbn[2+1];
    char    kkahskcd[3+1];
    char    dtnrtts[8+1];
    char    skkka[24+1];
}   KekkaConv;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long dGD105UpdKekkaConv( KekkaConv* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
