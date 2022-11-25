/******************************************************************************/
/*   ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/*   システム名：次世代システム                                               */
/*   ファイル名：tagAD102.h                                                   */
/*   概      要：患者情報テーブル構造体定義                                   */
/*   特記事項  ：DB2のホスト変数にも使用するためtypedef使用不可               */
/*               またstructの最後で変数名を宣言すること                       */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/08     INTEC.INC      CREATE                             */
/*  1.01     2006/05/01     INTEC.INC      SJIS,項目追加(親施設,登録日時)対応 */
/******************************************************************************/
#ifndef _TAGAD102_H
#define _TAGAD102_H

/******************************************************************************/
/* データ構造体定義                                                           */
/******************************************************************************/
// <<   依頼情報テーブル      >>
struct	_IRAI {
	char	utkymd[10+1];		// 1 ＢＭＬ受付年月日
	char	irino[11+1];		// 2 依頼書Ｎｏ
	char	iriketflg[1+1];		// 3 依頼書Ｎｏ桁数フラグ
	short	zssdino;			// 4 属性世代Ｎｏ
	char	knsgrp[16+1];		// 5 検査グループ
	char	kmkcd[7+1];			// 6 項目コード
	char	irihsmkbn[1+1];		// 7 依頼発生元区分
	char	irikbn[1+1];		// 8 依頼区分
	char	ksktkbn[1+1];		// 9 検査工程区分
	char	sriymd[10+1];		// 10 処理日
	char	kntno[13+1];		// 11 検体Ｎｏ（やっぱり必要）
	char	kntketflg[1+1];		// 12 検体Ｎｏ桁数フラグ
	char	chkmj[4+1];			// 13 チェック文字（やっぱり必要）
	char	stsrcd[4+1];		// 14 推定材料コード
	char	kmkrs[16+1];		// 15 項目略称
	char	oyakmkcd[7+1];		// 16 親項目コード
	char	smpcd[7+1];			// 17 サンプリングコード
	char	setkmkcd[7+1];		// 18 セット項目コード
	char	srinycd[1+1];		// 19 処理内容コード
	char	seccd[2+1];			// 20 セクションコード
	char	skchkflg[1+1];		// 21 出荷チェックフラグ
	char	bkfkkbn[1+1];		// 22 分画負荷区分
	char	ysnlbl[2+1];		// 23 優先レベル
	char	skflg[1+1];			// 24 集検フラグ
	char	tkflg[1+1];			// 25 追加フラグ
	char	sjflg[1+1];			// 26 削除フラグ
	char	jktkflg[1+1];		// 27 条件追加フラグ
	char	kjno[3+1];			// 28 基準値ＮＯ
	char	fkhkknohjkbn[1+1];	// 29 負荷報告ＮＯ表示区分
	char	tbkjno[3+1];		// 30 特別基準値ＮＯ
	char	tbkjflg[1+1];		// 31 特別基準値フラグ
	char	htkfkhms[24+1];		// 32 非定型負荷時間
	char	tskflg[2+1];		// 33 透析フラグ
	char	tktflg[2+1];		// 34 凍結フラグ
	char	bnckbn[1+1];		// 35 分注区分
	char	nbnckbn[1+1];		// 36 尿分注区分
	char	knskisyymd[10+1];	// 37 検査開始予定日
	char	knskryymd[10+1];	// 38 検査完了予定日
	char	knskrytme[8+1];		// 39 検査完了予定時間
	char	kkhkkflg[1+1];		// 40 緊急報告フラグ
	char	kkiriflg[1+1];		// 41 緊急依頼フラグ
	short	kkirilotno;			// 42 緊急依頼ロットＮｏ
	char	kktoutkid[4+1];		// 43 緊急対応受付ＩＤ
	short	knssu;				// 44 検査回数
	char	odrssflg[1+1];		// 45 オーダ作成フラグ
	char	ytiksbr[15+1];		// 46 予定希釈倍率
	char	hhkjkflg[1+1];		// 47 報告状況フラグ
	char	ksndh[26+1];		// 48 情報更新日時
	char	trkdh[26+1];		// 1.01 ADD 49 登録日時
} hirai;	

/******************************************************************************/
/* マスタ構造体定義                                                           */
/******************************************************************************/
// <<   システム管理マスタ     >>
struct  _SYSKNRMST {
	char	kjnsriymd[11];		// 基準処理年月日
	char	nxirisriymd[11];	// 次依頼処理年月日
	char	iriendflg[2];		// 依頼ENDフラグ
} hsysknrmst;

// <<   基準値マスタ     >>
struct	_KJNMST {
	char	kmkcd[7+1];			// 1 項目コード
	char	kjno[3+1];			// 2 基準値NO
	char	zrcd[4+1];			// 4 材料コード      
	char	etckbn[3+1];		// 6 その他区分      
	char	nichilw[5+1];		// 7 日齢（下）      
	char	nichihi[5+1];		// 8 日齢（上）      
	char    kkey[14+1];			// 0 検索キー(MYAPP)
	sqlint32	knlow;			// 0 検索キー(日齢下)
	sqlint32	knhigh;			// 0 検索キー(日齢上)
} hkjnmst;	

// 1.04 ADD
// <<   項目マスタ >>
struct	_KMKMST {
	char	knsgrp[16+1];		// 1  検査グループコード
	char	kmkcd[7+1];			// 2  項目コード
	char	kmkrs[16+1];		// 5  項目略称
	char	smpcd[7+1];			// 11 サンプリングコード
	char	oyakmkcd[7+1];		// 12 親項目コード
	char	fkbnkkb[1+1];		// 19 負荷分画区分
	char	skflg[1+1];			// 0  集検フラグ
} hkmkmst;	

// <<   自動発生項目マスタ >>
struct	_JDKMKMST {
	char	knsgrp[16+1];		// 1  検査グループコード
	char	kmkcd[7+1];			// 2  項目コード
	char	jknsgrp[16+1];		// 3  自動発生検査グループコード
	char	jkmkcd[7+1];		// 4  自動発生項目コード
	char	hhkumflg[1+1];		// 5  報告有無フラグ
} hjdkmkmst;	

#endif
