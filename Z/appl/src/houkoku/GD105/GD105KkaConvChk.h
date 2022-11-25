/********************************************************************/
/*																	*/
/*		ＢＭＬ様向け検査システム									*/
/*																	*/
/*		システム名	：次世代システム								*/
/*		ファイル名	：GD105KkaConvChk.h								*/
/*		概要		：報告データファイル作成ヘッダーファイル		*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	作成日			名前			修正内容				*/
/* ---------------------------------------------------------------- */
/*  2.00	2009/05/19		K.Moriya		結果変換マスタ対応		*/
/********************************************************************/
#ifndef _GD105KkaConvChk_h
#define _GD105KkaConvChk_h

/********************************************************************/
/*  インクルード宣言												*/
/********************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <dirent.h>
#include <sys/shm.h>
#include "bml_base.h"
#include "GD105Kanjya.h"
#include "GD105Kenzok.h"
#include "GD105KekkaConv.h"
#include "GD105Kkaconvmst.h"
#include "GD105Kkaconvknr.h"

/******************************************************************************/
/* Define定義																  */
/******************************************************************************/

//データ識別子
#define GD105_SSTCD_LOOP_CNT		2
#define GD105_CALC_KEY				2
#define GD105_SSTCD_ALL_ZERO		"0000000"
#define GD105_NULL					'\0'
#define GD105_SPACE_MARK			'@'
#define GD105_EXCLAMATION_MARK		'!'
#define GD105_CONVCHK_OK			1
#define GD105_CONVCHK_NG			0
#define GD105_CONVCHK_SKIP			-1

/******************************************************************************/
/* 構造体定義																  */
/******************************************************************************/
/* 結果変換マスタ条件式展開用構造体 */
typedef struct _Calc {
	char	cShiki[2+1];
	char	cFrom[15+1];
	char	cTo[15+1];
} Calc;

/******************************************************************************/
/* グローバル宣言															  */
/******************************************************************************/
// extern

/******************************************************************************/
/* プロトタイプ宣言															  */
/******************************************************************************/
/* 結果変換チェック関数 */
int GD105KkaConvChk(Kekka *pKekka, Kkaconvmst *pKkaconvmst, char *pSstcd);
/* 性別区分チェック */
int GD105ConvChkSbtkbn(char cKanjyaSbtkbn, char cKkaconvmstSbtkbn);
/* 年齢チェック */
int GD105ConvChkAge(char *pKanjyaAge, char *pKkaconvmstAge);
/* 年齢区分チェック */
int GD105ConvChkAgekbn(char cKanjyaAgekbn, char cKkaconvmstAgekbn);
/* 身長チェック */
int GD105ConvChkSc(char *pKanjyaSc, char *pKkaconvmstSc);
/* 体重チェック */
int GD105ConvChkTj(char *pKanjyaTj, char *pKkaconvmstTj);
/* 体重区分チェック */
int GD105ConvChkTjtni(char cKanjyaTjtni, char cKkaconvmstTjtni);
/* 蓄尿時間チェック */
int GD105ConvChkTntme(char *pKenzokTntme, char *pKkaconvmstTntme);
/* 蓄尿時間区分チェック */
int GD105ConvChkTntni(char cKenzokTntni, char cKkaconvmstTntni);
/* 蓄尿量チェック */
int GD105ConvChkTnryo(char *pKenzokTnryo, char *pKkaconvmstTnryo);
/* 蓄尿量区分チェック */
int GD105ConvChkTnryotni(char cKenzokTnryotni, char cKkaconvmstTnryotni);
/* 結果変換管理情報テーブル用構造体設定 */
int GD105SetKkaconvknr(Kkaconvknr *pKkaconvknr, Kekka *pKekka, Kanjya *pKanjya, Kenzok *pKenzok, char *pSstcd);
/* 結果情報テーブル更新用構造体設定 */
int GD105SetKekkaConv(KekkaConv *pKekkaConv, Kekka *pKekka, Kkaconvmst *pKkaconvmst, char *pDtnrtts);
/* 結果変換マスタ条件式展開 */
int GD105CalcConv(Calc *pCalc, char *pstrCalc);
/* 数値かどうかチェック */
int GD105IsNumeric(const char *pstrTarget);
/* 条件式数値チェック(共通) */
int GD105NumChk(Calc *pCalc, char *pstrNum);
/* トリム関数 */
void GD105Trim(char *dst, char *src);
#endif
/** End of File ***************************************************************/
