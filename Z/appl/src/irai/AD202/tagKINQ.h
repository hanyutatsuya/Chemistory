/******************************************************************************/
/*   ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/*   システム名：次世代システム                                               */
/*   ファイル名：tagKINQ.h                                                    */
/*   概      要：AS400緊急依頼受信ファイル構造体定義                          */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/03/03     INTEC.INC      CREATE                             */
/*  2.00     2009/01/05     Merits K.Ameno 施設コード増桁 通信仕様変更対応    */
/******************************************************************************/
#ifndef _TAGKINQ_H
#define _TAGKINQ_H

/* #define KINQ_RECSIZE 1144 */	/*	構造体の総サイズ"1201Byte" - FILLERサイズ"57Byte"	*/
#define KINQ_RECSIZE 		( sizeof(struct AS4IRAI) - KINQ_FILLER_SIZE )
								/* Ver 2.00 1800 - 32Byte */
#define KINQ_FILLER_SIZE	32	/* FILLERのサイズ 構造体：AS4IRAI のfiller2のサイズ */
#define	IKOM_MAX			200

/*** 受信ファイルフィールド位置定義(1ライン1次元配列化時のダイレクトアクセス用) ***/
#define	KINQ_POS_ID			0				/* ID							 */
#define	KINQ_POS_STAT		2				/* ステータス					 */
#define	KINQ_POS_ECODE		3				/* 営業所コード					 */
#define	KINQ_POS_UCODE		8				/* 施設コード					 */
#define	KINQ_POS_UDATE		15				/* 受付日付						 */
#define	KINQ_POS_KENNO		23				/* 検体No						 */
#define	KINQ_POS_NAME		34				/* 患者名						 */
#define	KINQ_POS_KARUTE		50				/* カルテNo						 */
#define	KINQ_POS_BYOTO		62				/* 病棟							 */
#define	KINQ_POS_DOCTOR		67				/* 担当医						 */
#define	KINQ_POS_CARD		73				/* カード区分					 */
#define	KINQ_POS_NYUGAI		75				/* 入外区分						 */
#define	KINQ_POS_SINRYO		76				/* 診療科コード					 */
#define	KINQ_POS_SEX		79				/* 性別							 */
#define	KINQ_POS_AGE		80				/* 年齢							 */
#define	KINQ_POS_HOKEN		83				/* 保険コード					 */
#define	KINQ_POS_SDATE		84				/* 採取日						 */
#define	KINQ_POS_ZAI		88				/* 材料コード					 */
#define	KINQ_POS_NRYO		91				/* 蓄尿量						 */
#define	KINQ_POS_NTIME		95				/* 蓄尿時間						 */
#define	KINQ_POS_UCMT		97				/* 受付コメント					 */
#define	KINQ_POS_KINFLG		99				/* 緊急フラグ					 */
#define	KINQ_POS_HGRP		100				/* 当時報告グループ				 */
#define	KINQ_POS_TUIKA		102				/* 項目追加フラグ				 */
#define	KINQ_POS_KCOUNT		103				/* 項目数						 */
#define	KINQ_POS_FCOUNT		106				/* 負荷数						 */
#define	KINQ_POS_FIL		107				/* FILLER						 */
#define	KINQ_POS_CH			108				/* チェック文字					 */
#define	KINQ_POS_LCODE		110				/* ラボコード					 */

#define	KINQ_POS_KCODE1		112				/* 項目コード 001				 */
#define	KINQ_POS_LABO1		119				/* ラボ対象フラグ 001			 */

#define	KINQ_POS_FKCODE1	1712			/* 負荷項目コード 001			 */
#define	KINQ_POS_FLABO1		1719			/* 負荷項目ラボ対象フラグ 001	 */

#define	KINQ_POS_LOT		1744			/* ロット						 */
#define	KINQ_POS_UNAME		1746			/* 施設名						 */
#define	KINQ_POS_NEFLG		1766			/* NEフラグ						 */
#define	KINQ_POS_FIL2		1767			/* FILLER2						 */

/******************************************************************************/
/* 構造体定義                                                                 */
/******************************************************************************/
/*===============================================================*/
/*		依頼													 */
/*===============================================================*/
/*--- S-JIS用構造体 ---*/

struct	AS4IKOM {			/* PNC送受信項目 	*/
	char	c_koumoku_cd[7];	// 項目ｺｰﾄﾞ Ver 02.00 4->7桁へ拡張
	char	c_labo_flg[1];		// ラボフラグ
};

struct	AS4IRAI {
/*** 本構造体の定義を変更した場合、必ずKINQ_RECSIZEのチューニングが必要！ ***/
/*** 基本的には、sizeof と Defineを使用しているので、Defineの変更のみで   ***/
/*** で対応可能なはずだが、要チェック！                                   ***/
	char	c_sbt[2];			// ID
	char	c_status[1];		// ステータス
	char	c_eigyo_cd[5];		// 営業所コード Ver 02.00 2->5桁へ拡張
	char	c_siset_cd[7];		// 施設コード Ver 02.00 5->7桁へ拡張
	char	c_bml_ymd[8];		// 受付年月日 Ver 02.00 6->8桁へ拡張
	char	c_kentai_no[11];	// 検体No Ver 02.00 6->11桁へ拡張
	char	c_kanja_nm[16];		// 患者名
	char	c_karte_no[12];		// カルテNo
	char	c_byoto_nm[5];		// 病棟(名)
	char	c_dr_nm[6];			// 担当医(名)
	char	c_card1_kbn[2];		// カード区分
	char	c_ng_kbn[1];		// 入院外来区分
	char	c_ka_cd[3];			// 診療科コード Ver 02.00 2->3桁へ拡張
	char	c_sex[1];			// 性別区分
	char	c_age[3];			// 年齢
	char	c_hoken_cd[1];		// 保険コード
	char	c_saisyu_bi[4];		// 採取日
	char	c_zairyo_cd[3];		// 材料コード Ver 02.00 2->3桁へ拡張
	char	c_nyoryo[4];		// 蓄尿量
	char	c_nyotime[2];		// 蓄尿時間
	char	c_ukecmt_cd[2];		// 受付コメント
	char	c_kinkyu_flg[1];	// 緊急フラグ
	char	c_hokokug[2];		// 当時報告グループ
	char	c_add_flg[1];		// 項目追加フラグ
	char	c_kmcnt[3];			// 一般項目数
	char	c_fukacnt[1];		// 負荷項目数
	char	c_filler[1];		// ＦＩＬＥＥＲ
	char	c_kentai_ch[2];		// チェック文字
	char	c_labocd[2];		// ラボコード
    struct  AS4IKOM	ikm[IKOM_MAX];
	char	c_fukaoya1[7];		// 負荷親項目１ Ver 02.00 4->7桁へ拡張
	char	c_fukano1[1];		// 負荷Ｎｏ．1
	char	c_fukaoya2[7];		// 負荷親項目２ Ver 02.00 4->7桁へ拡張
	char	c_fukano2[1];		// 負荷Ｎｏ．２
	char	c_fukaoya3[7];		// 負荷親項目３ Ver 02.00 4->7桁へ拡張
	char	c_fukano3[1];		// 負荷Ｎｏ．３
	char	c_fukaoya4[7];		// 負荷親項目４ Ver 02.00 4->7桁へ拡張
	char	c_fukano4[1];		// 負荷Ｎｏ．４
	char	c_lotno[2];			// ロットＮｏ．
	char	c_sisetr_knm[20];	// 施設名
	char	c_ne_kbn[1];		// ＮＥフラグ
	char	c_filler2[KINQ_FILLER_SIZE];		// ＦＩＬＥＥＲ Ver 02.00 レコード長調整 57->32桁 同時にサイズをDefine化
	char	c_kaigyo[1];		/* 改行ｺｰﾄﾞ		*/ 
};


#endif
