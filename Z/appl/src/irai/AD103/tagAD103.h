/******************************************************************************/
/*   ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/*   システム名：次世代システム                                               */
/*   ファイル名：tagAD103.h                                                   */
/*   概      要：患者情報テーブル構造体定義                                   */
/*   特記事項  ：DB2のホスト変数にも使用するためtypedef使用不可               */
/*               またstructの最後で変数名を宣言すること                       */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/08     INTEC.INC      CREATE                             */
/*  1.01     2006/05/01     INTEC.INC      SJIS,項目追加(親施設,登録日時)対応 *
/******************************************************************************/
#ifndef _TAGAD103_H
#define _TAGAD103_H

/******************************************************************************/
/* データ構造体定義                                                           */
/******************************************************************************/
// <<   患者情報テーブル      >>
struct	_KANJYA {
	char	utkymd[10+1];		// 1 ＢＭＬ受付年月日 
	char	irino[11+1];		// 2 依頼書Ｎｏ 
	char	iriketflg[1+1];		// 3 依頼書Ｎｏ桁数フラグ 
	short	zssdino;			// 4 属性世代Ｎｏ 
	char	sstcd[7+1];			// 5 施設コード 
	char	subsstcd[4+1];		// 6 サブ施設コード 
	char	cdkbn1[2+1];		// 7 カード区分1 
	char	cdkbn2[2+1];		// 8 カード区分2 
	char	irimkey[40+1];		// 9 依頼元キー 
	char	srkcd[3+1];			// 10 診療科コード 
	char	srknm[30+1];		// 11 診療科名 
	char	tticd[8+1];			// 12 担当医コード 
	char	ttinm[40+1];		// 13 担当医名 
	char	gpcd[8+1];			// 14 主治医コード 
	char	gpnm[40+1];			// 15 主治医名 
	char	skicd[8+1];			// 16 紹介医コード 
	char	skinm[40+1];		// 17 紹介医名 
	char	krtno[40+1];		// 18 カルテＮｏ          
	char	knjid[15+1];		// 19 患者ＩＤ 
	char	knjnmn[60+1];		// 20 患者名（カナ） 
	char	knjnmk[30+1];		// 21 患者名（漢字） 
	char	knjnmkey[60+1];		// 22 患者名キー 
	char	sc[5+1];			// 23 身長  
	char	tj[5+1];			// 24 体重  
	char	tjtni[1+1];			// 25 体重区分 
	char	sbtkbn[1+1];		// 26 性別区分 
	char	birthday[8+1];		// 27 生年月日  
	char	birthdaykbn[1+1];	// 28 生年月日区分 
	char	age[3+1];			// 29 年齢  
	char	agekbn[1+1];		// 30 年齢区分 
	char	btcd[10+1];			// 31 病棟コード 
	char	btnm[30+1];			// 32 病棟名 
	char	utkcmtcd1[2+1];		// 33 受付コメント1  
	char	utkcmtcd2[2+1];		// 34 受付コメント2  
	char	utkcmtcd3[2+1];		// 35 受付コメント3  
	char	utkcmtfr1[70+1];	// 36 受付コメントフリー1  
	char	utkcmtfr2[70+1];	// 37 受付コメントフリー2  
	char	utkcmtfrflg[1+1];	// 38 受付コメントフリーフラグ 
	char	ngkbn[1+1];			// 39 入院外来区分           
	char	nsssu[2+1];			// 40 妊娠週数  
	char	hkncd[1+1];			// 41 保険コード 
	char	ktshsu[2+1];		// 42 検体総本数 
	char	iniriymd[10+1];		// 43 院内依頼日 
	char	zssflg[1+1];		// 44 属性修正フラグ 
	char	kkiriflg[1+1];		// 45 緊急依頼フラグ 
	char	hknskbn[1+1];		// 46 非検査区分 
	char	utkkbn[1+1];		// 47 受付区分 
	char	nekbn[1+1];			// 48 ＮＥ区分 
	char	inknskbn[1+1];		// 49 院内検査区分 
	char	utkjkkbn[1+1];		// 50 受付状態区分 
	char	krflg[1+1];			// 51 完了フラグ 
	char	fdhhkkflg[1+1];		// 52 ＦＤ非報告フラグ 
	char	utkdh[8+1];			// 53 受付時刻 
	char	mutkymd[10+1];		// 54 元ＢＭＬ受付日 
	char	mirino[11+1];		// 55 元依頼書Ｎｏ 
	char	knsjslbcd1[3+1];	// 56 検査実施ラボコード１ 
	char	knsjslbcd2[3+1];	// 57 検査実施ラボコード２ 
	char	knsjslbcd3[3+1];	// 58 検査実施ラボコード３ 
	char	knsjslbcd4[3+1];	// 59 検査実施ラボコード４ 
	char	ymhkkflg[1+1];		// 60 翌日未報告フラグ 
	char	hkkkbdh[8+1];		// 61 報告希望時間 
	char	ecd[3+1];			// 62 営業所コード 
	char	shcd[2+1];			// 63 集配コード 
	char	sstssnmj[40+1];		// 64 施設名正式名称 
	char	sstssnmn[40+1];		// 65 施設名正式名称（カナ） 
	char	sstrsj[20+1];		// 66 施設名略称 
	char	sstrsn[20+1];		// 67 施設名略称（カナ） 
	char	sstsbt[2+1];		// 68 施設種別 
	char	ttsstflg[1+1];		// 69 特定施設フラグ 
	char	rucd[2+1];			// 70 理由コード 
	short	irikmksu;			// 71 依頼項目数 
	char	bmskn[50+1];		// 72 病名及び所見 
	char	irinrsbt[2+1];		// 73 依頼入力種別 
	char	irihsmkbn[1+1];		// 74 依頼発生元区分 
	char	caresstflg[1+1];	// 75 特別注意施設フラグ 
	char	tktyflg[1+1];		// 76 治験拡張フラグ 
	char	apkntino[13+1];		// 77 AUTO-P検体Ｎｏ 
	char	sdnm[20+1];			// 78 診断名 
	char	bko1[20+1];			// 79 備考１ 
	char	bko2[20+1];			// 80 備考２ 
	char	bko3[20+1];			// 81 備考３ 
	char	zstrdh[26+1];		// 82 属性登録日時 
	char	zsssdh[26+1];		// 83 属性修正日時 
	char	stlzsssdh[26+1];	// 84 サテライト内属性修正日時 
	char	stlzsssip[15+1];	// 85 サテライト内属性修正端末IP 
	char	stlzssssyaid[8+1];	// 86 サテライト内属性修正入力者 
	char	ksndh[26+1];		// 87 情報更新日時 
	char	oyasstcd[7+1];		// 1.01 ADD	88 親施設コード 
	char	trkdh[26+1];		// 1.01 ADD	89 登録日時 
} hkanjya;	

// <<   治験拡張属性テーブル      >>
struct	_CHIKENZOK {
	char	utkymd[10+1];		// 1 ＢＭＬ受付年月日 
	char	irino[11+1];		// 2 依頼書Ｎｏ 
	char	iriketflg[1+1];		// 3 依頼書Ｎｏ桁数フラグ 
	short	zssdino;			// 4 属性世代Ｎｏ 
	char	prtclno[11+1];		// 5 治験・プロトコルＮｏ 
	char	kosstcd[7+1];		// 6 治験・子施設コード  
	char	tytme[4+1];			// 7 治験・投与時間  
	char	tyryo[5+1];			// 8 治験・投与量(量) 
	char	tyryotni[3+1];		// 9 治験・投与量(単位) 
	char	yzfktme[4+1];		// 10 治験・薬剤負荷時間 
	char	ikasflg[1+1];		// 11 治験・一括アッセイフラグ 
	short	kntsu;				// 12 治験・検体数 
	short	kmksu;				// 13 治験・項目数 
	char	sspit[2+1];			// 14 治験・採取ポイント 
	char	zrcd01[5+1];		// 15 治験・材料コード１ 
	char	zrcd02[5+1];		// 16 治験・材料コード２ 
	char	zrcd03[5+1];		// 17 治験・材料コード３ 
	char	zrcd04[5+1];		// 18 治験・材料コード４ 
	char	zrcd05[5+1];		// 19 治験・材料コード５ 
	char	zrcd06[5+1];		// 20 治験・材料コード６ 
	char	zrkg01[2+1];		// 21 治験・材料記号１ 
	char	zrkg02[2+1];		// 22 治験・材料記号２ 
	char	zrkg03[2+1];		// 23 治験・材料記号３ 
	char	zrkg04[2+1];		// 24 治験・材料記号４ 
	char	zrkg05[2+1];		// 25 治験・材料記号５ 
	char	zrkg06[2+1];		// 26 治験・材料記号６ 
	char	hrseq[4+1];			// 27 治験・保留シーケンス 
	char	kntksflg[1+1];		// 28 治験・検体回収フラグ 
	char	gcpflg[1+1];		// 29 治験・ＧＣＰフラグ 
	char	prtclnm[40+1];		// 30 治験・プロトコル名称 
	char	ksndh[26+1];		// 31 情報更新日時 
} hchikenzok;	

/******************************************************************************/
/* マスタ構造体定義                                                           */
/******************************************************************************/
// <<   システム管理マスタ     >>
struct	_SYSKNRMST {
	char	kjnsriymd[11];		// 基準処理年月日
	char	nxirisriymd[11];	// 次依頼処理年月日
	char	iriendflg[2];		// 依頼ENDフラグ
} hsysknrmst;	


// <<   営業所マスタ     >>
struct	_EIGMST {
	char	ecd[4];
	char	shcdfr[3];
	char	shcdto[3];
	char	yjhkkbn[2];
	char	kaiymd[11];
	char	haiymd[11];
} heigmst;	

#endif
