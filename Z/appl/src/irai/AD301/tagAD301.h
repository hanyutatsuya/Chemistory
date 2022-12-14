/******************************************************************************/
/*   ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/*   システム名：次世代システム                                               */
/*   ファイル名：tagAD301.h                                                   */
/*   概      要：患者情報テーブル構造体定義                                   */
/*   特記事項  ：DB2のホスト変数にも使用するためtypedef使用不可               */
/*               またstructの最後で変数名を宣言すること                       */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/08     INTEC.INC      CREATE                             */
/******************************************************************************/
#ifndef _TAGAD301_H
#define _TAGAD301_H

/******************************************************************************/
/* データ構造体定義                                                           */
/******************************************************************************/
/******************************************************************************/
/* マスタ構造体定義                                                           */
/******************************************************************************/
// <<   システム管理マスタ     >>
struct  _SYSKNRMST {
	char	sateid[3];			// サテライトＩＤ
	char	kjnsriymd[11];		// 基準処理年月日
	char	iriendflg[2];		// 依頼ENDフラグ
	char	bchendflg[2];		// 分注ENDフラグ
	sqlint32	ssntubn;		// 送信通番
	char	ksndh[26];			// 更新年月日
} hsysknrmst;

#endif
