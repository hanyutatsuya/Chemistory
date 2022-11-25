static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,55,65,82,118,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,65,68,50,48,50,95,68,66,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0
};

#include "sqladef.h"

static struct sqla_runtime_info sqla_rtinfo = 
{{'S','Q','L','A','R','T','I','N'}, sizeof(wchar_t), 0, {' ',' ',' ',' '}};


static const short sqlIsLiteral   = SQL_IS_LITERAL;
static const short sqlIsInputHvar = SQL_IS_INPUT_HVAR;


#line 1 "AD202_db.sqc"
/******************************************************************************/
/*   ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/*   システム名：次世代システム                                               */
/*   ファイル名：AD202_db.sqc                                                 */
/*   概      要：ＤＢアクセス                                                 */
/*   OS        ：SUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   言語      ：DB2/C                                                        */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/08     INTEC.INC      CREATE                             */
/*  1.01     2006/05/01     INTEC.INC      SJIS,項目追加(親施設,登録日時)対応 */
/*  2.00     2009/01/06     Merits K.Ameno 施設コード増桁 通信仕様変更対応    */
/******************************************************************************/

/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include	<stdio.h>
#include 	<stdlib.h>
#include 	<string.h>
#include	<sqlca.h>
#include	"AD202.h"


/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 27 "AD202_db.sqc"


/*
EXEC SQL INCLUDE 'tagAD202.h';
*/

#line 1 "/home/kea00sys/appl/src/irai/AD202/tagAD202.h"
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
/*  1.01     2006/05/01     INTEC.INC      SJIS,項目追加(親施設,登録日時)対応 */
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
	char	oyasstcd[7+1];		// 1.01 ADD	88 施設コード 
	char	trkdh[26+1];		// 1.01 ADD	89 情報更新日時 
} hkanjya;	

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
	char	trkdh[26+1];		// 1.01 ADD	49 情報更新日時 
} hirai;	

/******************************************************************************/
/* マスタ構造体定義                                                           */
/******************************************************************************/
// <<   システム管理マスタ     >>
struct  _SYSKNRMST {
	char	kkkjsriymd[11];		// 緊急基準処理年月日
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

// <<   緊急依頼項目情報構造体  >>
struct _KNKYUMST {
    char    knsgrp[16+1];               // 1.04 O 検査グループ
    char    kmkrs[16+1];                // O 項目略称
    char    oyakmkcd[7+1];              // O 親項目コード
    char    fkbnkkb[1+1];               // O 分画負荷区分
    char    seccd[2+1];                 // O セクションコード
    char    smpcd[7+1];                 // O サンプリングコード
	char    kmkcd[7+1];                 // I 項目コード
} hknkyumst;

// 1.04 ADD
// <<   項目マスタ >>
struct  _KMKMST {
    char    knsgrp[16+1];       // 1  検査グループコード
    char    kmkcd[7+1];         // 2  項目コード
    char    kmkrs[16+1];        // 5  項目略称
    char    smpcd[7+1];         // 11 サンプリングコード
    char    oyakmkcd[7+1];      // 12 親項目コード
    char    fkbnkkb[1+1];       // 19 負荷分画区分
    char    skflg[1+1];         // 0  集検フラグ
} hkmkmst;

// <<   自動発生項目マスタ >>
struct  _JDKMKMST {
    char    knsgrp[16+1];       // 1  検査グループコード
    char    kmkcd[7+1];         // 2  項目コード
    char    jknsgrp[16+1];      // 3  自動発生検査グループコード
    char    jkmkcd[7+1];        // 4  自動発生項目コード
    char    hhkumflg[1+1];      // 5  報告有無フラグ
} hjdkmkmst;
// 1.04 END

#endif

#line 28 "AD202_db.sqc"

	char		hst_ymd[11];
	char		hst_kmkcd[8];
	sqlint32	hst_cnt;					// マスタ件数
	short		ind_cnt;					// 標識変数
	sqlint32	hst_kkirilotno;				// 緊急依頼ロットＮｏ
    char        hst_utkymd[10+1];
    char        hst_irino[11+1];
    char        hst_errcd[8+1];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 37 "AD202_db.sqc"


/******************************************************************************/
/*  関 数 名  ：SelSysknrmst                                                  */
/*  機能概要  ：システム管理マスタ SELECT                                     */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  _SYSKNRMST *knr;   : システム管理マスタ               */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		SelSysknrmst( knr )
struct		_SYSKNRMST	*knr;
{
	int		ret;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* 関数名称	*/
	struct	sqlca	sqlca;

	/* 初期処理	*/
	strcpy( func_nm, "SelSysknrmst" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ホスト変数へのキー項目セット	*/
	memset( &hsysknrmst,	'\0',	sizeof( struct _SYSKNRMST ));


/*
EXEC SQL SELECT	
		 	kkkjsriymd
			, nxirisriymd
			, iriendflg
	INTO	:hsysknrmst.kkkjsriymd
			, :hsysknrmst.nxirisriymd
			, :hsysknrmst.iriendflg
	FROM	sysknrmst
	;
*/

{
#line 70 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 70 "AD202_db.sqc"
  sqlaaloc(3,3,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 70 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 70 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hsysknrmst.kkkjsriymd;
#line 70 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 70 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 70 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hsysknrmst.nxirisriymd;
#line 70 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 70 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 70 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hsysknrmst.iriendflg;
#line 70 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 70 "AD202_db.sqc"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 70 "AD202_db.sqc"
  sqlacall((unsigned short)24,1,0,3,0L);
#line 70 "AD202_db.sqc"
  sqlastop(0L);
}

#line 70 "AD202_db.sqc"


    /* not found --> SQLCODE = +100, SQLSTATE == '02000' */
    /* many rows --> ERROR!!         SQLSTATE == '21000' */
    /* duplicate --> SQLCODE = -803                      */
    /* dead lock --> SQLCODE = -911, SQLERRD[2]== 2      */
    /* time out  --> SQLCODE = -911, SQLERRD[2]== 68     */

	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "SELECT kkkjsriymd FROM sysknrmst" );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if ( sqlca.sqlcode == 0 ) {		/* OK */
		memcpy( knr, &hsysknrmst, sizeof( struct _SYSKNRMST ));
		ret = RTN_OK;
	} else if ( sqlca.sqlcode == 100 ){	/* NOT FOUND */
		/* SQLCODE +100, SQLSTATE '02000' */
		sprintf( G_msg, "システム管理マスタ(kjnsriymd)が存在しません。" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			
		ret=RTN_ZERO;
	} else {
		if( sqlca.sqlcode == -911 ){        // LOCK
			switch( sqlca.sqlerrd[2] ){
			case     2 :
				strcpy( G_msg, "システム管理マスタ(kjnsriymd) SELECT で"
					"DEAD LOCK が発生しました。" );
				break;
			case    68 :
				strcpy( G_msg, "システム管理マスタ(kjnsriymd) SELECT で"
					"TIMETOUT が発生しました。" );
				break;
			default :
				sprintf( G_msg, "システム管理マスタ(kjnsriymd) SELECT で"
					"不具合が発生しました。" );
				break;
			}
		} else {
			/* SQLCODE > 0 -> WARNING */
			/* SQLCODE < 0 -> ERROR */
			sprintf( G_msg, "システム管理マスタ(kjnsriymd) SELECT で"
				"不具合が発生しました。" );
		}
		ret=RTN_DBERR;
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
	}


/*
EXEC SQL COMMIT;
*/

{
#line 124 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 124 "AD202_db.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 124 "AD202_db.sqc"
  sqlastop(0L);
}

#line 124 "AD202_db.sqc"


	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  関 数 名  ：GetKnkyulot                                                   */
/*  機能概要  ：緊急ロット情報取得                                            */
/*  入    力  ：                                                              */
/*   第１引数 ：char	ymd[];	: 	基準処理日                                */
/*   第２引数 ：int		lotno;	: 	ロットＮｏ                                */
/*  出    力  ：                                                              */
/*  復帰情報  ：COUNT結果    正常終了                                         */
/*            ：0 未満       異常終了                                         */
/******************************************************************************/
int		GetKnkyulot( ymd, lotno )
char		ymd[];	
int			lotno;	
{
	int		ret;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/
	struct	sqlca	sqlca;

	/* 初期処理	*/
	strcpy( func_nm, "GetKnkyulot" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ホスト変数へのキー項目セット	*/
	strcpy( hst_ymd,	ymd );
	hst_kkirilotno = lotno;
	hst_cnt=0;
	ind_cnt=0;


/*
EXEC SQL SELECT	COUNT( seccd )
	INTO	:hst_cnt	INDICATOR :ind_cnt
	FROM	knkyulot 
	WHERE	knskisymd	= :hst_ymd
	AND		seccd		in ( SELECT seccd FROM secmst )
	AND		kkirilotno	= :hst_kkirilotno
	;
*/

{
#line 164 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 164 "AD202_db.sqc"
  sqlaaloc(2,2,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 164 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 164 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hst_ymd;
#line 164 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 164 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 164 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)&hst_kkirilotno;
#line 164 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 164 "AD202_db.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 164 "AD202_db.sqc"
  sqlaaloc(3,1,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 164 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 497; sql_setdlist[0].sqllen = 4;
#line 164 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)&hst_cnt;
#line 164 "AD202_db.sqc"
      sql_setdlist[0].sqlind = &ind_cnt;
#line 164 "AD202_db.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 164 "AD202_db.sqc"
  sqlacall((unsigned short)24,2,2,3,0L);
#line 164 "AD202_db.sqc"
  sqlastop(0L);
}

#line 164 "AD202_db.sqc"


	/* SQLCODE */
	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "SELECT COUNT( seccd ) FROM knkyulot : "
		"ymd[%s] lot[%d] cnt[%d] indicator[%d]",
		ymd, lotno, hst_cnt, ind_cnt );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	// 標識変数による判断
	if( ind_cnt == 0 ) {
		// COUNT結果を返す（0もあり）
		ret = hst_cnt;
	} else {
		sprintf( G_msg,
			"緊急ロット情報(knkyulot)の件数取得に失敗しました。"
			"緊急受付日[%s] SELECT INDICATOR[%d]"
			,ymd, ind_cnt );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		ret=RTN_NG;
	}
	// DEBUG
	sprintf( G_msg, "KNKYULOT COUNT[%d]", ret );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

//	1TRANSACTION内で呼ぶためコメント化
//EXEC SQL COMMIT;

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  関 数 名  ：InsKnkyulot                                                   */
/*  機能概要  ：緊急ロットNOの登録                                            */
/*  入    力  ：                                                              */
/*   第１引数 ：char	ymd[];   : 基準日                                     */
/*   第２引数 ：int		lotno;	: 	ロットＮｏ                                */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		InsKnkyulot( ymd, lotno )
char		ymd[];	
int			lotno;
{
	int		i;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* 関数名称	*/
	struct	sqlca	sqlca;

	/* 初期処理	*/
	strcpy( func_nm, "InsKnkyulot" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ホスト変数へのキー項目セット	*/
	strcpy( hst_ymd,	ymd );
	hst_kkirilotno = lotno;

	// 登録した依頼情報のセクションコード結合パターン

/*
EXEC SQL	INSERT	INTO	knkyulot
	SELECT	:hst_ymd
			, iri.seccd
			, :hst_kkirilotno
			, CURRENT TIMESTAMP
			, '1000-01-01 00:00:01'
			, CURRENT TIMESTAMP
			, ' '							-- errcd
			, '0'							-- almflg
	FROM	(	SELECT	DISTINCT seccd 
				FROM	irai
				WHERE	utkymd		= :hst_ymd
				AND		kkirilotno	= :hst_kkirilotno
			) iri
	;
*/

{
#line 244 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 244 "AD202_db.sqc"
  sqlaaloc(2,4,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 244 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 244 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hst_ymd;
#line 244 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 244 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 244 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)&hst_kkirilotno;
#line 244 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 244 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 244 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hst_ymd;
#line 244 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 244 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 244 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)&hst_kkirilotno;
#line 244 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 244 "AD202_db.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 244 "AD202_db.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 244 "AD202_db.sqc"
  sqlastop(0L);
}

#line 244 "AD202_db.sqc"


/*============================= セクションマスタ結合パターン
	SELECT	:hst_ymd
			, seccd
			, :hst_kkirilotno
			, CURRENT TIMESTAMP
			, '1000-01-01 00:00:01'
			, CURRENT TIMESTAMP
	FROM	secmst
	;
====================================== */

	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "INSERT knkyulot : lotno[%d] ymd[%s]", lotno, ymd );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if ( sqlca.sqlcode != 0 ) {		/* SQL実行OK以外？ */
		/* WARNING LOG */
		sprintf( G_msg,
			"緊急ロットNO(knkyulot)の INSERT に失敗しました。"
			"受付日[%s]LOTNO[%d]"
			,ymd, lotno );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__ );
	}
	return( sqlca.sqlcode );	/* SQLコードを呼び出し元に返す */
}

/******************************************************************************/
/*  関 数 名  ：UpdKnkyulot                                                   */
/*  機能概要  ：緊急ロット情報．ロットNO=0のエラーコード設定                  */
/*  入    力  ：                                                              */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/*  特記事項  ：                                                              */
/******************************************************************************/
int		UpdKnkyulot( errcd )
char		errcd[];					// 	エラーコード
{
	struct	sqlca	sqlca;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* 関数名称	*/
	int		ret;

	/* 初期処理	*/
	strcpy( func_nm, "UpdKnkyulot" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ホスト変数への項目セット	*/
	strcpy( hst_ymd,	stcPRM.myp_kjnymd );
	strcpy( hst_errcd,	errcd );


/*
EXEC SQL UPDATE	Knkyulot	
	SET		errcd		= :hst_errcd
			,almflg		= '0'
			,ksndh		= CURRENT TIMESTAMP
	WHERE	knskisymd	= :hst_ymd
	AND		kkirilotno	= 0
	;
*/

{
#line 308 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 308 "AD202_db.sqc"
  sqlaaloc(2,2,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 308 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 9;
#line 308 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hst_errcd;
#line 308 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 308 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 308 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_ymd;
#line 308 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 308 "AD202_db.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 308 "AD202_db.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 308 "AD202_db.sqc"
  sqlastop(0L);
}

#line 308 "AD202_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf(G_msg,"UPDATE Knkyulot : errcd[%s]ymd[%s]",hst_errcd,hst_ymd );
	LogOut( LT_DBG, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if (sqlca.sqlcode == 0) {		/* OK */
		ret = RTN_OK;
	} else {
		if( sqlca.sqlcode == -911 ){		// LOCK
			switch( sqlca.sqlerrd[2] ){
			case	 2 :
				strcpy( G_msg, "緊急ロット情報(Knkyulot) UPDATE で"
					"DEAD LOCK が発生しました。" );
				break;
			case	68 :
				strcpy( G_msg, "緊急ロット情報(Knkyulot) UPDATE で"
					"TIMETOUT が発生しました。" );
				break;
			default :
				sprintf( G_msg, "緊急ロット情報(Knkyulot) UPDATE で"
					"不具合が発生しました。" );
				break;
			}
		} else {
			/* SQLCODE > 0 -> WARNING */
			/* SQLCODE < 0 -> ERROR */
			sprintf( G_msg,
				"緊急ロット情報(Knkyulot)依頼END情報の UPDATE に"
				"失敗しました。緊急基準処理年月日[%s] LOTNO=0"
				,stcPRM.myp_kjnymd );
		}
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		ret=RTN_DBERR;
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  関 数 名  ：SelKinqKomokmst                                               */
/*  機能概要  ：緊急対応項目情報 SELECT                                       */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  KOMST    *kom;   :緊急対応項目情報                    */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
//int		SelKinqKomokmst( kom )
int		SelKinqKomokmst( kom, skflg )
struct		KOMST		*kom;			/* 緊急対応項目情報 */
char		skflg[];
{
	int		ret;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* 関数名称	*/
	struct	sqlca	sqlca;

	/* 初期処理	*/
	strcpy( func_nm, "SelKinqKomokmst" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ホスト変数へのキー項目セット	*/
	memset( &hknkyumst,			'\0', sizeof( struct _KNKYUMST ));
	strcpy( hknkyumst.kmkcd,	kom->kmkcd );
	strcpy( hst_ymd,			stcPRM.myp_kjnymd );

/* 1.04 検査グループも取得
EXEC SQL SELECT	
			kinq.smpcd
			, kinq.seccd
			, kom.kmkrs
			, kom.oyakmkcd
			, kom.fkbnkkb
	INTO	  :hknkyumst.smpcd
		  	, :hknkyumst.seccd
			, :hknkyumst.kmkrs
			, :hknkyumst.oyakmkcd
		  	, :hknkyumst.fkbnkkb
	FROM	kmkmst kom, kinkmmst kinq
	WHERE	kinq.kmkcd		=  :hknkyumst.kmkcd
	AND		kinq.kmkcd		=	kom.kmkcd
	AND		kinq.smpcd		=	kom.smpcd
	AND		kinq.kaiymd		<= :hst_ymd
	AND		kinq.haiymd		>= :hst_ymd
	AND		kom.kaiymd		<= :hst_ymd
	AND		kom.haiymd		>= :hst_ymd
	;
*/
   // 集検フラグによる対象検査グループ種別の判断
    if( skflg[0] == '1' ){              // 集検

/*
EXEC SQL SELECT		q.smpcd
					, q.seccd
					, m.knsgrp
					, m.kmkrs
					, m.oyakmkcd
					, m.fkbnkkb
			INTO	  :hknkyumst.smpcd
					, :hknkyumst.seccd
					, :hknkyumst.knsgrp
					, :hknkyumst.kmkrs
					, :hknkyumst.oyakmkcd
					, :hknkyumst.fkbnkkb
			FROM	knsgmst g
					, kmkmst m
					, kinkmmst q
			WHERE	q.kmkcd		=  :hknkyumst.kmkcd
			AND		q.kmkcd		=	m.kmkcd
			AND		q.smpcd		=	m.smpcd
			AND		q.kaiymd	<= :hst_ymd
			AND		q.haiymd	>= :hst_ymd
			AND		m.kaiymd	<= :hst_ymd
			AND		m.haiymd	>= :hst_ymd
			AND     m.knsgrp   =   g.knsgrp
			AND     g.knssbt   =   'S'
			AND     g.kaiymd   <= :hst_ymd
			AND     g.haiymd   >= :hst_ymd
			ORDER BY m.knsgrp
			FETCH FIRST 1 ROWS ONLY
		;
*/

{
#line 432 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 432 "AD202_db.sqc"
  sqlaaloc(2,7,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 432 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 432 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hknkyumst.kmkcd;
#line 432 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 432 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_ymd;
#line 432 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 432 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hst_ymd;
#line 432 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 432 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)hst_ymd;
#line 432 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 432 "AD202_db.sqc"
      sql_setdlist[4].sqldata = (void*)hst_ymd;
#line 432 "AD202_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 432 "AD202_db.sqc"
      sql_setdlist[5].sqldata = (void*)hst_ymd;
#line 432 "AD202_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 432 "AD202_db.sqc"
      sql_setdlist[6].sqldata = (void*)hst_ymd;
#line 432 "AD202_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 432 "AD202_db.sqc"
  sqlaaloc(3,6,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 432 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 432 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hknkyumst.smpcd;
#line 432 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 432 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hknkyumst.seccd;
#line 432 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 17;
#line 432 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hknkyumst.knsgrp;
#line 432 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 432 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)hknkyumst.kmkrs;
#line 432 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 432 "AD202_db.sqc"
      sql_setdlist[4].sqldata = (void*)hknkyumst.oyakmkcd;
#line 432 "AD202_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 2;
#line 432 "AD202_db.sqc"
      sql_setdlist[5].sqldata = (void*)hknkyumst.fkbnkkb;
#line 432 "AD202_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sqlasetdata(3,0,6,sql_setdlist,0L,0L);
    }
#line 432 "AD202_db.sqc"
  sqlacall((unsigned short)24,5,2,3,0L);
#line 432 "AD202_db.sqc"
  sqlastop(0L);
}

#line 432 "AD202_db.sqc"

	} else {					// 集検以外

/*
EXEC SQL SELECT		q.smpcd
					, q.seccd
					, m.knsgrp
					, m.kmkrs
					, m.oyakmkcd
					, m.fkbnkkb
			INTO	  :hknkyumst.smpcd
					, :hknkyumst.seccd
					, :hknkyumst.knsgrp
					, :hknkyumst.kmkrs
					, :hknkyumst.oyakmkcd
					, :hknkyumst.fkbnkkb
			FROM	knsgmst g
					, kmkmst m
					, kinkmmst q
			WHERE	q.kmkcd		=  :hknkyumst.kmkcd
			AND		q.kmkcd		=	m.kmkcd
			AND		q.smpcd		=	m.smpcd
			AND		q.kaiymd	<= :hst_ymd
			AND		q.haiymd	>= :hst_ymd
			AND		m.kaiymd	<= :hst_ymd
			AND		m.haiymd	>= :hst_ymd
			AND     m.knsgrp   =  g.knsgrp
			AND     g.knssbt   NOT IN ('S','T')
			AND     g.kaiymd   <= :hst_ymd
			AND     g.haiymd   >= :hst_ymd
			ORDER BY m.knsgrp
			FETCH FIRST 1 ROWS ONLY
			;
*/

{
#line 462 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 462 "AD202_db.sqc"
  sqlaaloc(2,7,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 462 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 462 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hknkyumst.kmkcd;
#line 462 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 462 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_ymd;
#line 462 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 462 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hst_ymd;
#line 462 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 462 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)hst_ymd;
#line 462 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 462 "AD202_db.sqc"
      sql_setdlist[4].sqldata = (void*)hst_ymd;
#line 462 "AD202_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 462 "AD202_db.sqc"
      sql_setdlist[5].sqldata = (void*)hst_ymd;
#line 462 "AD202_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 462 "AD202_db.sqc"
      sql_setdlist[6].sqldata = (void*)hst_ymd;
#line 462 "AD202_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 462 "AD202_db.sqc"
  sqlaaloc(3,6,9,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 462 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 462 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hknkyumst.smpcd;
#line 462 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 462 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hknkyumst.seccd;
#line 462 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 17;
#line 462 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hknkyumst.knsgrp;
#line 462 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 462 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)hknkyumst.kmkrs;
#line 462 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 462 "AD202_db.sqc"
      sql_setdlist[4].sqldata = (void*)hknkyumst.oyakmkcd;
#line 462 "AD202_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 2;
#line 462 "AD202_db.sqc"
      sql_setdlist[5].sqldata = (void*)hknkyumst.fkbnkkb;
#line 462 "AD202_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sqlasetdata(3,0,6,sql_setdlist,0L,0L);
    }
#line 462 "AD202_db.sqc"
  sqlacall((unsigned short)24,6,2,3,0L);
#line 462 "AD202_db.sqc"
  sqlastop(0L);
}

#line 462 "AD202_db.sqc"

	}

	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "SELECT knkyumst : kmkcd[%s]ymd[%s]",
		kom->kmkcd, stcPRM.myp_kjnymd );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if ( sqlca.sqlcode == 0 ) {		/* OK */
		strcpy( kom->knsgrp,	hknkyumst.knsgrp );
		strcpy( kom->kmkrs,		hknkyumst.kmkrs );
		strcpy( kom->oyakmkcd,	hknkyumst.oyakmkcd );
		strcpy( kom->fkbnkkb,	hknkyumst.fkbnkkb );
		strcpy( kom->seccd,		hknkyumst.seccd );
		strcpy( kom->smpcd,		hknkyumst.smpcd );
		ret = RTN_OK;
	} else {
		if ( sqlca.sqlcode == 100 ){	/* NOT FOUND */
			ret=RTN_SKIP;
		} else {
			/* SQLCODE > 0 -> WARNING */
			/* SQLCODE < 0 -> ERROR */
			sprintf( G_msg,
				"緊急依頼項目情報マスタ SELECT で不具合が発生しました。"
				"項目[%s]基準日[%s]"
				,kom->kmkcd, stcPRM.myp_kjnymd );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			 
			ret=RTN_DBERR;
		}
	}

//	1TRANSACTION内で呼ぶためコメント化
//EXEC SQL COMMIT;

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  関 数 名  ：SelCountKjnmst                                                */
/*  機能概要  ：基準値マスタ（緊急対応項目マスタ結合）件数取得                */
/*  入    力  ：                                                              */
/*   第１引数 ：char	ymd[];	: 	基準処理日                                */
/*  出    力  ：                                                              */
/*  復帰情報  ：COUNT結果    正常終了                                         */
/*            ：0 未満       異常終了                                         */
/******************************************************************************/
int		SelCountKjnmst( ymd )
char		ymd[];	
{
	int		ret;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/
	struct	sqlca	sqlca;

	/* 初期処理	*/
	strcpy( func_nm, "SelCountKjnmst" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ホスト変数へのキー項目セット	*/
	strcpy( hst_ymd,	ymd );
	hst_cnt=0;
	ind_cnt=0;


/*
EXEC SQL SELECT	COUNT( kj.kmkcd )
	INTO	:hst_cnt	INDICATOR :ind_cnt
	FROM	kjnmst kj, kinkmmst kinq
	WHERE	kj.kmkcd	= kinq.kmkcd
	AND		kj.kaiymd	<= :hst_ymd
	AND		kj.haiymd	>= :hst_ymd
	AND		kinq.kaiymd	<= :hst_ymd
	AND		kinq.haiymd	>= :hst_ymd
	;
*/

{
#line 540 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 540 "AD202_db.sqc"
  sqlaaloc(2,4,10,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 540 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 540 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hst_ymd;
#line 540 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 540 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 540 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_ymd;
#line 540 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 540 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 540 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hst_ymd;
#line 540 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 540 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 540 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)hst_ymd;
#line 540 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 540 "AD202_db.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 540 "AD202_db.sqc"
  sqlaaloc(3,1,11,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 540 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 497; sql_setdlist[0].sqllen = 4;
#line 540 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)&hst_cnt;
#line 540 "AD202_db.sqc"
      sql_setdlist[0].sqlind = &ind_cnt;
#line 540 "AD202_db.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 540 "AD202_db.sqc"
  sqlacall((unsigned short)24,7,2,3,0L);
#line 540 "AD202_db.sqc"
  sqlastop(0L);
}

#line 540 "AD202_db.sqc"


    /* not found --> SQLCODE = +100, SQLSTATE == '02000' */
	/* many rows --> ERROR!!         SQLSTATE == '21000' */

	/* SQLCODE */
	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "SELECT COUNT( kmkcd ) FROM kjnmst, kmkmst : "
		"ymd[%s] cnt[%d] indicator[%d]",
		ymd, hst_cnt, ind_cnt );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	// 標識変数による判断
	if( ind_cnt == 0 ) {
		// COUNT結果を返す（0もあり）
		ret = hst_cnt;
	} else {
		sprintf( G_msg,
			"基準値マスタ(kjnmst)の件数取得に失敗しました。"
			"基準処理年月日[%s] SELECT INDICATOR[%d]"
			,ymd, ind_cnt );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		ret=RTN_NG;
	}
	// DEBUG
	sprintf( G_msg, "KJNMST COUNT[%d]", ret );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  関 数 名  ：SelKjnmst                                                     */
/*  機能概要  ：基準値マスタ SELECT  （緊急対応項目マスタ結合）               */
/*  入    力  ：                                                              */
/*   第１引数 ：char	ymd[];   : 基準日                                     */
/*   第２引数 ：int		kensu;   : malloc件数                                 */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		SelKjnmst( ymd, kensu )
char		ymd[];	
int			kensu;
{
	int		ret;
	int		i;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* 関数名称	*/
	struct	sqlca	sqlca;

	/* 初期処理	*/
	strcpy( func_nm, "SelKjnmst" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ホスト変数へのキー項目セット	*/
	memset( &hkjnmst,	'\0', sizeof( struct _KJNMST ));
	strcpy( hst_ymd,	ymd );


/*
EXEC SQL DECLARE    kjn_cur CURSOR  FOR
	SELECT	kj.kmkcd
			, kjno
			, zrcd
			, etckbn
			, nichilw
			, nichihi
	FROM	kjnmst kj, kinkmmst kinq
	WHERE	kj.kmkcd	= kinq.kmkcd
	AND		kj.kaiymd	<= :hst_ymd
	AND		kj.haiymd	>= :hst_ymd
	AND		kinq.kaiymd	<= :hst_ymd
	AND		kinq.haiymd	>= :hst_ymd
	ORDER BY kj.kmkcd, kj.zrcd, nichilw, nichihi
	;
*/

#line 620 "AD202_db.sqc"



/*
EXEC SQL OPEN kjn_cur;
*/

{
#line 622 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 622 "AD202_db.sqc"
  sqlaaloc(2,4,12,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 622 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 622 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hst_ymd;
#line 622 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 622 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 622 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_ymd;
#line 622 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 622 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 622 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hst_ymd;
#line 622 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 622 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 622 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)hst_ymd;
#line 622 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 622 "AD202_db.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 622 "AD202_db.sqc"
  sqlacall((unsigned short)26,8,2,0,0L);
#line 622 "AD202_db.sqc"
  sqlastop(0L);
}

#line 622 "AD202_db.sqc"


	i=0;

	while( sqlca.sqlcode == 0 ){
		
/*
EXEC SQL    FETCH   kjn_cur
					INTO	  :hkjnmst.kmkcd
							, :hkjnmst.kjno
							, :hkjnmst.zrcd
							, :hkjnmst.etckbn
							, :hkjnmst.nichilw
							, :hkjnmst.nichihi
					;
*/

{
#line 634 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 634 "AD202_db.sqc"
  sqlaaloc(3,6,13,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 634 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 634 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkjnmst.kmkcd;
#line 634 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 634 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 4;
#line 634 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkjnmst.kjno;
#line 634 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 634 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 634 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkjnmst.zrcd;
#line 634 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 634 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 4;
#line 634 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)hkjnmst.etckbn;
#line 634 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 634 "AD202_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 6;
#line 634 "AD202_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkjnmst.nichilw;
#line 634 "AD202_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 634 "AD202_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 6;
#line 634 "AD202_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkjnmst.nichihi;
#line 634 "AD202_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 634 "AD202_db.sqc"
      sqlasetdata(3,0,6,sql_setdlist,0L,0L);
    }
#line 634 "AD202_db.sqc"
  sqlacall((unsigned short)25,8,0,3,0L);
#line 634 "AD202_db.sqc"
  sqlastop(0L);
}

#line 634 "AD202_db.sqc"

		if( i >= kensu ){
			break;
		}
		memcpy( &( pKjn[i] ), &hkjnmst, sizeof( struct _KJNMST ));
		i++;
	}
	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "FETCH kjnmst : ymd[%s]", ymd );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if ( sqlca.sqlcode == 100 ) {	// NOT FOUND or END
		if( i > 0 ){
			ret = RTN_OK;
		} else {
			sprintf( G_msg,
				"基準値マスタを取得できません。基準日[%s]", ymd );
			EditCsvMsg( G_msg );
			LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			ret = RTN_NG;
		}
	} else {
		/* SQLCODE > 0 -> WARNING */
		/* SQLCODE < 0 -> ERROR */
		sprintf( G_msg,
			"基準値マスタ FETCH で不具合が発生しました。基準日[%s]", ymd );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			 
		ret=RTN_DBERR;
	}

/*
EXEC SQL    CLOSE   kjn_cur;
*/

{
#line 670 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 670 "AD202_db.sqc"
  sqlacall((unsigned short)20,8,0,0,0L);
#line 670 "AD202_db.sqc"
  sqlastop(0L);
}

#line 670 "AD202_db.sqc"


/*
EXEC SQL	COMMIT;
*/

{
#line 671 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 671 "AD202_db.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 671 "AD202_db.sqc"
  sqlastop(0L);
}

#line 671 "AD202_db.sqc"


	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  関 数 名  ：InsKanjya                                                     */
/*  機能概要  ：患者属性　INSERT                                              */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  _KANJYA     *zok;   : 患者情報                        */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		InsKanjya( kan )
struct		_KANJYA	*kan;			/* 患者属性データ */
{
	struct	sqlca	sqlca;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/

	/* 初期処理	*/
	strcpy(func_nm, "InsKanjya" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ホスト変数へのセット	*/
	memcpy( &hkanjya, kan, sizeof( struct _KANJYA ));


/*
EXEC SQL INSERT	INTO	kanjya
		( utkymd
		, irino
		, iriketflg
		, zssdino
		, sstcd
		, subsstcd
		, cdkbn1
		, cdkbn2
		, irimkey
		, srkcd
		, srknm
		, tticd
		, ttinm
		, gpcd
		, gpnm
		, skicd
		, skinm
		, krtno
		, knjid
		, knjnmn
		, knjnmk
		, knjnmkey
		, sc
		, tj
		, tjtni
		, sbtkbn
		, birthday
		, birthdaykbn
		, age
		, agekbn
		, btcd
		, btnm
		, utkcmtcd1
		, utkcmtcd2
		, utkcmtcd3
		, utkcmtfr1
		, utkcmtfr2
		, utkcmtfrflg
		, ngkbn
		, nsssu
		, hkncd
		, ktshsu
		, iniriymd
		, zssflg
		, kkiriflg
		, hknskbn
		, utkkbn
		, nekbn
		, inknskbn
		, utkjkkbn
		, krflg
		, fdhhkkflg
		, utkdh
		, mutkymd
		, mirino
		, knsjslbcd1
		, knsjslbcd2
		, knsjslbcd3
		, knsjslbcd4
		, ymhkkflg
		, hkkkbdh
		, ecd
		, shcd
		, sstssnmj
		, sstssnmn
		, sstrsj
		, sstrsn
		, sstsbt
		, ttsstflg
		, rucd
		, irikmksu
		, bmskn
		, irinrsbt
		, irihsmkbn
		, caresstflg
		, tktyflg
		, apkntino
		, sdnm
		, bko1
		, bko2
		, bko3
		, zstrdh
		, zsssdh
		, stlzsssdh
		, stlzsssip
		, stlzssssyaid
		, ksndh
		, oyasstcd					-- 1.01 ADD
		, trkdh						-- 1.01 ADD
		)
	VALUES	( :hkanjya.utkymd
		, :hkanjya.irino
		, :hkanjya.iriketflg
		, :hkanjya.zssdino
		, :hkanjya.sstcd
		, :hkanjya.subsstcd
		, :hkanjya.cdkbn1
		, :hkanjya.cdkbn2
		, :hkanjya.irimkey
		, :hkanjya.srkcd
		, :hkanjya.srknm
		, :hkanjya.tticd
		, :hkanjya.ttinm
		, :hkanjya.gpcd
		, :hkanjya.gpnm
		, :hkanjya.skicd
		, :hkanjya.skinm
		, :hkanjya.krtno
		, :hkanjya.knjid
		, :hkanjya.knjnmn
		, :hkanjya.knjnmk
		, :hkanjya.knjnmkey
		, :hkanjya.sc
		, :hkanjya.tj
		, :hkanjya.tjtni
		, :hkanjya.sbtkbn
		, :hkanjya.birthday
		, :hkanjya.birthdaykbn
		, :hkanjya.age
		, :hkanjya.agekbn
		, :hkanjya.btcd
		, :hkanjya.btnm
		, :hkanjya.utkcmtcd1
		, :hkanjya.utkcmtcd2
		, :hkanjya.utkcmtcd3
		, :hkanjya.utkcmtfr1
		, :hkanjya.utkcmtfr2
		, :hkanjya.utkcmtfrflg
		, :hkanjya.ngkbn
		, :hkanjya.nsssu
		, :hkanjya.hkncd
		, :hkanjya.ktshsu
		, :hkanjya.iniriymd
		, :hkanjya.zssflg
		, :hkanjya.kkiriflg
		, :hkanjya.hknskbn
		, :hkanjya.utkkbn
		, :hkanjya.nekbn
		, :hkanjya.inknskbn
		, :hkanjya.utkjkkbn
		, :hkanjya.krflg
		, :hkanjya.fdhhkkflg
		, :hkanjya.utkdh
		, :hkanjya.mutkymd
		, :hkanjya.mirino
		, :hkanjya.knsjslbcd1
		, :hkanjya.knsjslbcd2
		, :hkanjya.knsjslbcd3
		, :hkanjya.knsjslbcd4
		, :hkanjya.ymhkkflg
		, :hkanjya.hkkkbdh
		, :hkanjya.ecd
		, :hkanjya.shcd
		, :hkanjya.sstssnmj
		, :hkanjya.sstssnmn
		, :hkanjya.sstrsj
		, :hkanjya.sstrsn
		, :hkanjya.sstsbt
		, :hkanjya.ttsstflg
		, :hkanjya.rucd
		, :hkanjya.irikmksu
		, :hkanjya.bmskn
		, :hkanjya.irinrsbt
		, :hkanjya.irihsmkbn
		, :hkanjya.caresstflg
		, :hkanjya.tktyflg
		, :hkanjya.apkntino
		, :hkanjya.sdnm
		, :hkanjya.bko1
		, :hkanjya.bko2
		, :hkanjya.bko3
		, :hkanjya.zstrdh
		, :hkanjya.zsssdh
		, :hkanjya.stlzsssdh
		, :hkanjya.stlzsssip
		, :hkanjya.stlzssssyaid
		, CURRENT TIMESTAMP
		, :hkanjya.oyasstcd				-- 1.01 ADD
		, CURRENT TIMESTAMP				-- 1.01 ADD
		)
	;
*/

{
#line 880 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 880 "AD202_db.sqc"
  sqlaaloc(2,87,14,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 880 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 880 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.utkymd;
#line 880 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 880 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.irino;
#line 880 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkanjya.iriketflg;
#line 880 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)&hkanjya.zssdino;
#line 880 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 880 "AD202_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkanjya.sstcd;
#line 880 "AD202_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 5;
#line 880 "AD202_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkanjya.subsstcd;
#line 880 "AD202_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 3;
#line 880 "AD202_db.sqc"
      sql_setdlist[6].sqldata = (void*)hkanjya.cdkbn1;
#line 880 "AD202_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 880 "AD202_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkanjya.cdkbn2;
#line 880 "AD202_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 41;
#line 880 "AD202_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkanjya.irimkey;
#line 880 "AD202_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 4;
#line 880 "AD202_db.sqc"
      sql_setdlist[9].sqldata = (void*)hkanjya.srkcd;
#line 880 "AD202_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 31;
#line 880 "AD202_db.sqc"
      sql_setdlist[10].sqldata = (void*)hkanjya.srknm;
#line 880 "AD202_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 880 "AD202_db.sqc"
      sql_setdlist[11].sqldata = (void*)hkanjya.tticd;
#line 880 "AD202_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 41;
#line 880 "AD202_db.sqc"
      sql_setdlist[12].sqldata = (void*)hkanjya.ttinm;
#line 880 "AD202_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 880 "AD202_db.sqc"
      sql_setdlist[13].sqldata = (void*)hkanjya.gpcd;
#line 880 "AD202_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 41;
#line 880 "AD202_db.sqc"
      sql_setdlist[14].sqldata = (void*)hkanjya.gpnm;
#line 880 "AD202_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 880 "AD202_db.sqc"
      sql_setdlist[15].sqldata = (void*)hkanjya.skicd;
#line 880 "AD202_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 41;
#line 880 "AD202_db.sqc"
      sql_setdlist[16].sqldata = (void*)hkanjya.skinm;
#line 880 "AD202_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 41;
#line 880 "AD202_db.sqc"
      sql_setdlist[17].sqldata = (void*)hkanjya.krtno;
#line 880 "AD202_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 16;
#line 880 "AD202_db.sqc"
      sql_setdlist[18].sqldata = (void*)hkanjya.knjid;
#line 880 "AD202_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 61;
#line 880 "AD202_db.sqc"
      sql_setdlist[19].sqldata = (void*)hkanjya.knjnmn;
#line 880 "AD202_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 31;
#line 880 "AD202_db.sqc"
      sql_setdlist[20].sqldata = (void*)hkanjya.knjnmk;
#line 880 "AD202_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 61;
#line 880 "AD202_db.sqc"
      sql_setdlist[21].sqldata = (void*)hkanjya.knjnmkey;
#line 880 "AD202_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 6;
#line 880 "AD202_db.sqc"
      sql_setdlist[22].sqldata = (void*)hkanjya.sc;
#line 880 "AD202_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 6;
#line 880 "AD202_db.sqc"
      sql_setdlist[23].sqldata = (void*)hkanjya.tj;
#line 880 "AD202_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[24].sqldata = (void*)hkanjya.tjtni;
#line 880 "AD202_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[25].sqldata = (void*)hkanjya.sbtkbn;
#line 880 "AD202_db.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 9;
#line 880 "AD202_db.sqc"
      sql_setdlist[26].sqldata = (void*)hkanjya.birthday;
#line 880 "AD202_db.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[27].sqldata = (void*)hkanjya.birthdaykbn;
#line 880 "AD202_db.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 4;
#line 880 "AD202_db.sqc"
      sql_setdlist[28].sqldata = (void*)hkanjya.age;
#line 880 "AD202_db.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[29].sqldata = (void*)hkanjya.agekbn;
#line 880 "AD202_db.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 11;
#line 880 "AD202_db.sqc"
      sql_setdlist[30].sqldata = (void*)hkanjya.btcd;
#line 880 "AD202_db.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 31;
#line 880 "AD202_db.sqc"
      sql_setdlist[31].sqldata = (void*)hkanjya.btnm;
#line 880 "AD202_db.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 880 "AD202_db.sqc"
      sql_setdlist[32].sqldata = (void*)hkanjya.utkcmtcd1;
#line 880 "AD202_db.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 880 "AD202_db.sqc"
      sql_setdlist[33].sqldata = (void*)hkanjya.utkcmtcd2;
#line 880 "AD202_db.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 3;
#line 880 "AD202_db.sqc"
      sql_setdlist[34].sqldata = (void*)hkanjya.utkcmtcd3;
#line 880 "AD202_db.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 71;
#line 880 "AD202_db.sqc"
      sql_setdlist[35].sqldata = (void*)hkanjya.utkcmtfr1;
#line 880 "AD202_db.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 71;
#line 880 "AD202_db.sqc"
      sql_setdlist[36].sqldata = (void*)hkanjya.utkcmtfr2;
#line 880 "AD202_db.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[37].sqldata = (void*)hkanjya.utkcmtfrflg;
#line 880 "AD202_db.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[38].sqldata = (void*)hkanjya.ngkbn;
#line 880 "AD202_db.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 3;
#line 880 "AD202_db.sqc"
      sql_setdlist[39].sqldata = (void*)hkanjya.nsssu;
#line 880 "AD202_db.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[40].sqldata = (void*)hkanjya.hkncd;
#line 880 "AD202_db.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 880 "AD202_db.sqc"
      sql_setdlist[41].sqldata = (void*)hkanjya.ktshsu;
#line 880 "AD202_db.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 11;
#line 880 "AD202_db.sqc"
      sql_setdlist[42].sqldata = (void*)hkanjya.iniriymd;
#line 880 "AD202_db.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[43].sqldata = (void*)hkanjya.zssflg;
#line 880 "AD202_db.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[44].sqldata = (void*)hkanjya.kkiriflg;
#line 880 "AD202_db.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[45].sqldata = (void*)hkanjya.hknskbn;
#line 880 "AD202_db.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[46].sqldata = (void*)hkanjya.utkkbn;
#line 880 "AD202_db.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[47].sqldata = (void*)hkanjya.nekbn;
#line 880 "AD202_db.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[48].sqldata = (void*)hkanjya.inknskbn;
#line 880 "AD202_db.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[49].sqldata = (void*)hkanjya.utkjkkbn;
#line 880 "AD202_db.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[50].sqldata = (void*)hkanjya.krflg;
#line 880 "AD202_db.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[51].sqldata = (void*)hkanjya.fdhhkkflg;
#line 880 "AD202_db.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 9;
#line 880 "AD202_db.sqc"
      sql_setdlist[52].sqldata = (void*)hkanjya.utkdh;
#line 880 "AD202_db.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 11;
#line 880 "AD202_db.sqc"
      sql_setdlist[53].sqldata = (void*)hkanjya.mutkymd;
#line 880 "AD202_db.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 12;
#line 880 "AD202_db.sqc"
      sql_setdlist[54].sqldata = (void*)hkanjya.mirino;
#line 880 "AD202_db.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 880 "AD202_db.sqc"
      sql_setdlist[55].sqldata = (void*)hkanjya.knsjslbcd1;
#line 880 "AD202_db.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 4;
#line 880 "AD202_db.sqc"
      sql_setdlist[56].sqldata = (void*)hkanjya.knsjslbcd2;
#line 880 "AD202_db.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 4;
#line 880 "AD202_db.sqc"
      sql_setdlist[57].sqldata = (void*)hkanjya.knsjslbcd3;
#line 880 "AD202_db.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[58].sqltype = 460; sql_setdlist[58].sqllen = 4;
#line 880 "AD202_db.sqc"
      sql_setdlist[58].sqldata = (void*)hkanjya.knsjslbcd4;
#line 880 "AD202_db.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[59].sqltype = 460; sql_setdlist[59].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[59].sqldata = (void*)hkanjya.ymhkkflg;
#line 880 "AD202_db.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[60].sqltype = 460; sql_setdlist[60].sqllen = 9;
#line 880 "AD202_db.sqc"
      sql_setdlist[60].sqldata = (void*)hkanjya.hkkkbdh;
#line 880 "AD202_db.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[61].sqltype = 460; sql_setdlist[61].sqllen = 4;
#line 880 "AD202_db.sqc"
      sql_setdlist[61].sqldata = (void*)hkanjya.ecd;
#line 880 "AD202_db.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[62].sqltype = 460; sql_setdlist[62].sqllen = 3;
#line 880 "AD202_db.sqc"
      sql_setdlist[62].sqldata = (void*)hkanjya.shcd;
#line 880 "AD202_db.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[63].sqltype = 460; sql_setdlist[63].sqllen = 41;
#line 880 "AD202_db.sqc"
      sql_setdlist[63].sqldata = (void*)hkanjya.sstssnmj;
#line 880 "AD202_db.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sqlasetdata(2,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[23];
#line 880 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 41;
#line 880 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.sstssnmn;
#line 880 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 880 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.sstrsj;
#line 880 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 880 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkanjya.sstrsn;
#line 880 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 880 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)hkanjya.sstsbt;
#line 880 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkanjya.ttsstflg;
#line 880 "AD202_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 880 "AD202_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkanjya.rucd;
#line 880 "AD202_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[6].sqldata = (void*)&hkanjya.irikmksu;
#line 880 "AD202_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 880 "AD202_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkanjya.bmskn;
#line 880 "AD202_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 3;
#line 880 "AD202_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkanjya.irinrsbt;
#line 880 "AD202_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[9].sqldata = (void*)hkanjya.irihsmkbn;
#line 880 "AD202_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[10].sqldata = (void*)hkanjya.caresstflg;
#line 880 "AD202_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[11].sqldata = (void*)hkanjya.tktyflg;
#line 880 "AD202_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 14;
#line 880 "AD202_db.sqc"
      sql_setdlist[12].sqldata = (void*)hkanjya.apkntino;
#line 880 "AD202_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 880 "AD202_db.sqc"
      sql_setdlist[13].sqldata = (void*)hkanjya.sdnm;
#line 880 "AD202_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 21;
#line 880 "AD202_db.sqc"
      sql_setdlist[14].sqldata = (void*)hkanjya.bko1;
#line 880 "AD202_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 21;
#line 880 "AD202_db.sqc"
      sql_setdlist[15].sqldata = (void*)hkanjya.bko2;
#line 880 "AD202_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 21;
#line 880 "AD202_db.sqc"
      sql_setdlist[16].sqldata = (void*)hkanjya.bko3;
#line 880 "AD202_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 880 "AD202_db.sqc"
      sql_setdlist[17].sqldata = (void*)hkanjya.zstrdh;
#line 880 "AD202_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 880 "AD202_db.sqc"
      sql_setdlist[18].sqldata = (void*)hkanjya.zsssdh;
#line 880 "AD202_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 880 "AD202_db.sqc"
      sql_setdlist[19].sqldata = (void*)hkanjya.stlzsssdh;
#line 880 "AD202_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 16;
#line 880 "AD202_db.sqc"
      sql_setdlist[20].sqldata = (void*)hkanjya.stlzsssip;
#line 880 "AD202_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 9;
#line 880 "AD202_db.sqc"
      sql_setdlist[21].sqldata = (void*)hkanjya.stlzssssyaid;
#line 880 "AD202_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 8;
#line 880 "AD202_db.sqc"
      sql_setdlist[22].sqldata = (void*)hkanjya.oyasstcd;
#line 880 "AD202_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sqlasetdata(2,64,23,sql_setdlist,0L,0L);
    }
#line 880 "AD202_db.sqc"
  sqlacall((unsigned short)24,9,2,0,0L);
#line 880 "AD202_db.sqc"
  sqlastop(0L);
}

#line 880 "AD202_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "INSERT kanjya : utkymd[%s]irino[%s]zssdino[%d]",
		kan->utkymd, kan->irino, kan->zssdino );
	LogOut( LT_DBG, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if ( sqlca.sqlcode != 0 ) {		/* OK */
		if ( sqlca.sqlcode == MYAPP_RTN_DUP ) {	// duplicate
			;						/* 今は何もしないが、今後重複エラーでLOG出力を */
									/* したい場合にはここに追加！                  */
		}
		else {
			sprintf( G_msg,
				"患者情報(kanjya)の INSERT に失敗しました。"
				"BML受付年月日[%s]依頼書NO[%s]属性世代NO[%d]"
				,kan->utkymd, kan->irino, kan->zssdino );
		}
		EditCsvMsg( G_msg );
		LogOut( LT_TRC, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__ );
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( sqlca.sqlcode );
}

/******************************************************************************/
/*  関 数 名  ：InsIrai                                                     */
/*  機能概要  ：依頼情報　INSERT                                              */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  _IRAI     *iri;   : 依頼情報                        */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		InsIrai( iri )
struct		_IRAI	*iri;			/* 依頼データ */
{
	struct	sqlca	sqlca;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/

	/* 初期処理	*/
	strcpy(func_nm, "InsIrai" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ホスト変数へのセット	*/
	memcpy( &hirai, iri, sizeof( struct _IRAI ));


/*
EXEC SQL INSERT	INTO	irai
		( utkymd
		, irino
		, iriketflg
		, zssdino
		, knsgrp
		, kmkcd
		, irihsmkbn
		, irikbn
		, ksktkbn
		, sriymd
		, kntno
		, kntketflg
		, chkmj
		, stsrcd
		, kmkrs
		, oyakmkcd
		, smpcd
		, setkmkcd
		, srinycd
		, seccd
		, skchkflg
		, bkfkkbn
		, ysnlbl
		, skflg
		, tkflg
		, sjflg
		, jktkflg
		, kjno
		, fkhkknohjkbn
		, tbkjno
		, tbkjflg
		, htkfkhms
		, tskflg
		, tktflg
		, bnckbn
		, nbnckbn
		, knskisyymd
		, knskryymd
		, knskrytme
		, kkhkkflg
		, kkiriflg
		, kkirilotno
		, kktoutkid
		, knssu
		, odrssflg
		, ytiksbr
		, hhkjkflg
		, ksndh
		, trkdh						-- 1.01 ADD
		)
	VALUES  ( :hirai.utkymd
		, :hirai.irino
		, :hirai.iriketflg
		, :hirai.zssdino
		, :hirai.knsgrp
		, :hirai.kmkcd
		, :hirai.irihsmkbn
		, :hirai.irikbn
		, :hirai.ksktkbn
		, :hirai.sriymd
		, :hirai.kntno
		, :hirai.kntketflg
		, :hirai.chkmj
		, :hirai.stsrcd
		, :hirai.kmkrs
		, :hirai.oyakmkcd
		, :hirai.smpcd
		, :hirai.setkmkcd
		, :hirai.srinycd
		, :hirai.seccd
		, :hirai.skchkflg
		, :hirai.bkfkkbn
		, :hirai.ysnlbl
		, :hirai.skflg
		, :hirai.tkflg
		, :hirai.sjflg
		, :hirai.jktkflg
		, :hirai.kjno
		, :hirai.fkhkknohjkbn
		, :hirai.tbkjno
		, :hirai.tbkjflg
		, :hirai.htkfkhms
		, :hirai.tskflg
		, :hirai.tktflg
		, :hirai.bnckbn
		, :hirai.nbnckbn
		, :hirai.knskisyymd
		, :hirai.knskryymd
		, :hirai.knskrytme
		, :hirai.kkhkkflg
		, :hirai.kkiriflg
		, :hirai.kkirilotno
		, :hirai.kktoutkid
		, :hirai.knssu
		, :hirai.odrssflg
		, :hirai.ytiksbr
		, :hirai.hhkjkflg
		, CURRENT TIMESTAMP
		, CURRENT TIMESTAMP					-- 1.01 ADD
		)
	;
*/

{
#line 1033 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1033 "AD202_db.sqc"
  sqlaaloc(2,47,15,0L);
    {
      struct sqla_setdata_list sql_setdlist[47];
#line 1033 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1033 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hirai.utkymd;
#line 1033 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1033 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hirai.irino;
#line 1033 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hirai.iriketflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)&hirai.zssdino;
#line 1033 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 1033 "AD202_db.sqc"
      sql_setdlist[4].sqldata = (void*)hirai.knsgrp;
#line 1033 "AD202_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 1033 "AD202_db.sqc"
      sql_setdlist[5].sqldata = (void*)hirai.kmkcd;
#line 1033 "AD202_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[6].sqldata = (void*)hirai.irihsmkbn;
#line 1033 "AD202_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[7].sqldata = (void*)hirai.irikbn;
#line 1033 "AD202_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[8].sqldata = (void*)hirai.ksktkbn;
#line 1033 "AD202_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 1033 "AD202_db.sqc"
      sql_setdlist[9].sqldata = (void*)hirai.sriymd;
#line 1033 "AD202_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 14;
#line 1033 "AD202_db.sqc"
      sql_setdlist[10].sqldata = (void*)hirai.kntno;
#line 1033 "AD202_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[11].sqldata = (void*)hirai.kntketflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 5;
#line 1033 "AD202_db.sqc"
      sql_setdlist[12].sqldata = (void*)hirai.chkmj;
#line 1033 "AD202_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 5;
#line 1033 "AD202_db.sqc"
      sql_setdlist[13].sqldata = (void*)hirai.stsrcd;
#line 1033 "AD202_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 17;
#line 1033 "AD202_db.sqc"
      sql_setdlist[14].sqldata = (void*)hirai.kmkrs;
#line 1033 "AD202_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 1033 "AD202_db.sqc"
      sql_setdlist[15].sqldata = (void*)hirai.oyakmkcd;
#line 1033 "AD202_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 8;
#line 1033 "AD202_db.sqc"
      sql_setdlist[16].sqldata = (void*)hirai.smpcd;
#line 1033 "AD202_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 8;
#line 1033 "AD202_db.sqc"
      sql_setdlist[17].sqldata = (void*)hirai.setkmkcd;
#line 1033 "AD202_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[18].sqldata = (void*)hirai.srinycd;
#line 1033 "AD202_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 3;
#line 1033 "AD202_db.sqc"
      sql_setdlist[19].sqldata = (void*)hirai.seccd;
#line 1033 "AD202_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[20].sqldata = (void*)hirai.skchkflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[21].sqldata = (void*)hirai.bkfkkbn;
#line 1033 "AD202_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 3;
#line 1033 "AD202_db.sqc"
      sql_setdlist[22].sqldata = (void*)hirai.ysnlbl;
#line 1033 "AD202_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[23].sqldata = (void*)hirai.skflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[24].sqldata = (void*)hirai.tkflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[25].sqldata = (void*)hirai.sjflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[26].sqldata = (void*)hirai.jktkflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 4;
#line 1033 "AD202_db.sqc"
      sql_setdlist[27].sqldata = (void*)hirai.kjno;
#line 1033 "AD202_db.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[28].sqldata = (void*)hirai.fkhkknohjkbn;
#line 1033 "AD202_db.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 4;
#line 1033 "AD202_db.sqc"
      sql_setdlist[29].sqldata = (void*)hirai.tbkjno;
#line 1033 "AD202_db.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[30].sqldata = (void*)hirai.tbkjflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 25;
#line 1033 "AD202_db.sqc"
      sql_setdlist[31].sqldata = (void*)hirai.htkfkhms;
#line 1033 "AD202_db.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 1033 "AD202_db.sqc"
      sql_setdlist[32].sqldata = (void*)hirai.tskflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 1033 "AD202_db.sqc"
      sql_setdlist[33].sqldata = (void*)hirai.tktflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[34].sqldata = (void*)hirai.bnckbn;
#line 1033 "AD202_db.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[35].sqldata = (void*)hirai.nbnckbn;
#line 1033 "AD202_db.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 11;
#line 1033 "AD202_db.sqc"
      sql_setdlist[36].sqldata = (void*)hirai.knskisyymd;
#line 1033 "AD202_db.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 11;
#line 1033 "AD202_db.sqc"
      sql_setdlist[37].sqldata = (void*)hirai.knskryymd;
#line 1033 "AD202_db.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 9;
#line 1033 "AD202_db.sqc"
      sql_setdlist[38].sqldata = (void*)hirai.knskrytme;
#line 1033 "AD202_db.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[39].sqldata = (void*)hirai.kkhkkflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[40].sqldata = (void*)hirai.kkiriflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[41].sqltype = 500; sql_setdlist[41].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[41].sqldata = (void*)&hirai.kkirilotno;
#line 1033 "AD202_db.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 5;
#line 1033 "AD202_db.sqc"
      sql_setdlist[42].sqldata = (void*)hirai.kktoutkid;
#line 1033 "AD202_db.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[43].sqltype = 500; sql_setdlist[43].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[43].sqldata = (void*)&hirai.knssu;
#line 1033 "AD202_db.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[44].sqldata = (void*)hirai.odrssflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 16;
#line 1033 "AD202_db.sqc"
      sql_setdlist[45].sqldata = (void*)hirai.ytiksbr;
#line 1033 "AD202_db.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[46].sqldata = (void*)hirai.hhkjkflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sqlasetdata(2,0,47,sql_setdlist,0L,0L);
    }
#line 1033 "AD202_db.sqc"
  sqlacall((unsigned short)24,10,2,0,0L);
#line 1033 "AD202_db.sqc"
  sqlastop(0L);
}

#line 1033 "AD202_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "INSERT irai : utkymd[%s]irino[%s]zssdino[%d]kmkcd[%s]",
		iri->utkymd, iri->irino, iri->zssdino, iri->kmkcd );
	LogOut( LT_DBG, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if ( sqlca.sqlcode != 0 ) {		/* OK */
		if ( sqlca.sqlcode == MYAPP_RTN_DUP ) {	// duplicate
			sprintf( G_msg,
				"依頼情報(irai)は既に存在しています。"
				"BML受付年月日[%s]依頼書NO[%s]依頼世代NO[%d]項目CD[%s]"
				,iri->utkymd, iri->irino, iri->zssdino, iri->kmkcd );
		}
		else {
			sprintf( G_msg,
				"依頼情報(irai)の INSERT に失敗しました。"
				"BML受付年月日[%s]依頼書NO[%s]依頼世代NO[%d]項目CD[%s]"
				,iri->utkymd, iri->irino, iri->zssdino, iri->kmkcd );
		}
		/* ERROR */
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__ );
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( sqlca.sqlcode );
}
// 3.01 ADD STA =============================================================
/******************************************************************************/
/*  関 数 名  ：SelKinkyuIrai                                                 */
/*  機能概要  ：AS/400からの依頼項目が存在するかチェックする                  */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  _KANJYA    *kan;   : 患者情報                         */
/*  出    力  ：                                                              */
/*  復帰情報  ：COUNT結果    正常終了                                         */
/*            ：0 未満       異常終了                                         */
/******************************************************************************/
int		SelKinkyuIrai( iri )
struct		_IRAI		*iri;			// 依頼情報
{
	int		ret;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/
	struct	sqlca	sqlca;

	/* 初期処理	*/
	strcpy( func_nm, "SelKinkyuIrai" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ホスト変数へのキー項目セット	*/
	strcpy( hst_utkymd,	iri->utkymd );
	strcpy( hst_irino,	iri->irino );
	hst_kkirilotno=iri->kkirilotno;
	hst_cnt=0;
	ind_cnt=0;

	// 削除フラグは考慮しない

/*
EXEC SQL SELECT	COUNT( kmkcd )
	INTO	  :hst_cnt	INDICATOR :ind_cnt
	FROM	irai
	WHERE	utkymd	= :hst_utkymd
	AND		irino	= :hst_irino
	AND	  ( kkirilotno = 0 or kkirilotno= :hst_kkirilotno )
	;
*/

{
#line 1100 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1100 "AD202_db.sqc"
  sqlaaloc(2,3,16,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 1100 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1100 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hst_utkymd;
#line 1100 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1100 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1100 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_irino;
#line 1100 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1100 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 1100 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)&hst_kkirilotno;
#line 1100 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1100 "AD202_db.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 1100 "AD202_db.sqc"
  sqlaaloc(3,1,17,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 1100 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 497; sql_setdlist[0].sqllen = 4;
#line 1100 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)&hst_cnt;
#line 1100 "AD202_db.sqc"
      sql_setdlist[0].sqlind = &ind_cnt;
#line 1100 "AD202_db.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 1100 "AD202_db.sqc"
  sqlacall((unsigned short)24,11,2,3,0L);
#line 1100 "AD202_db.sqc"
  sqlastop(0L);
}

#line 1100 "AD202_db.sqc"


    /* not found --> SQLCODE = +100, SQLSTATE == '02000' */
	/* many rows --> ERROR!!         SQLSTATE == '21000' */

	/* SQLCODE */
	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "SELECT COUNT( kmkcd ) FROM irai WHERE ___ kkirilotno : "
		"utkymd[%s]irino[%s] lotno[%d] indicator[%d] sqlcode[%s]",
		iri->utkymd, iri->irino, iri->kkirilotno, ind_cnt, G_err );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	// 標識変数による判断
	if( ind_cnt == 0 ) {
		// COUNT結果を返す（0もあり）
		ret = hst_cnt;
	} else {
		sprintf( G_msg,
			"AS400依頼項目情報(irai)取得に失敗しました。"
			"BML受付年月日[%s]依頼書NO[%s] SELECT INDICATOR[%d]"
			,iri->utkymd, iri->irino, ind_cnt );
		EditCsvMsg( G_msg );
		LogOut( LT_TRC, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		ret=RTN_NG;
	}
	// DEBUG
	sprintf( G_msg, "AS400 irai COUNT[%d]", ret );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

// 3.01 ADD END =============================================================

// 1.04 ADD STA =============================================================
/******************************************************************************/
/*  関 数 名  ：SelCountJkmkmst                                               */
/*  機能概要  ：自動発生項目 対象件数カウント                                 */
/*  入    力  ：                                                              */
/*   第１引数 ：char	utkymd[];	: 	BML受付日                             */
/*   第２引数 ：char	irino[];	: 	依頼書No                              */
/*   第３引数 ：char	sriymd[];	: 	処理日                                */
/*  出    力  ：                                                              */
/*  復帰情報  ：COUNT結果    正常終了                                         */
/*            ：0 未満       異常終了                                         */
/******************************************************************************/
int		SelCountJkmkmst( utkymd, irino, sriymd )
char		utkymd[];	
char		irino[];	
char		sriymd[];	
{
	int		ret;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/
	struct	sqlca	sqlca;

	/* 初期処理	*/
	strcpy( func_nm, "SelCountJkmkmst" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ホスト変数へのキー項目セット	*/
	strcpy( hst_utkymd,	utkymd );
	strcpy( hst_irino,	irino );
	strcpy( hst_ymd,	sriymd );
	hst_cnt=0;
	ind_cnt=0;


/*
EXEC SQL SELECT	COUNT( distinct jkmkcd )
	INTO	:hst_cnt	INDICATOR :ind_cnt
	FROM	jdkmkmst 
	WHERE	( knsgrp, kmkcd ) IN
				( SELECT	knsgrp, kmkcd 
					FROM	irai
					WHERE	utkymd	= :hst_utkymd
					AND		irino	= :hst_irino
				)
	AND		( jknsgrp, jkmkcd ) NOT IN
				( SELECT	knsgrp, kmkcd 
					FROM	irai
					WHERE	utkymd	= :hst_utkymd
					AND		irino	= :hst_irino
				)
	AND		kaiymd	<= :hst_ymd
	AND		haiymd	>= :hst_ymd
	;
*/

{
#line 1190 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1190 "AD202_db.sqc"
  sqlaaloc(2,6,18,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 1190 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1190 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hst_utkymd;
#line 1190 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1190 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1190 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_irino;
#line 1190 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1190 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 1190 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hst_utkymd;
#line 1190 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1190 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 12;
#line 1190 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)hst_irino;
#line 1190 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1190 "AD202_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 1190 "AD202_db.sqc"
      sql_setdlist[4].sqldata = (void*)hst_ymd;
#line 1190 "AD202_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1190 "AD202_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 1190 "AD202_db.sqc"
      sql_setdlist[5].sqldata = (void*)hst_ymd;
#line 1190 "AD202_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1190 "AD202_db.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 1190 "AD202_db.sqc"
  sqlaaloc(3,1,19,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 1190 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 497; sql_setdlist[0].sqllen = 4;
#line 1190 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)&hst_cnt;
#line 1190 "AD202_db.sqc"
      sql_setdlist[0].sqlind = &ind_cnt;
#line 1190 "AD202_db.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 1190 "AD202_db.sqc"
  sqlacall((unsigned short)24,12,2,3,0L);
#line 1190 "AD202_db.sqc"
  sqlastop(0L);
}

#line 1190 "AD202_db.sqc"


	/* SQLCODE */
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "SELECT COUNT( kmkcd ) FROM jdkmkmst : "
		"utkymd[%s]irino[%s]ymd[%s] cnt[%d] indicator[%d]",
		utkymd, irino, sriymd, hst_cnt, ind_cnt );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	// 標識変数による判断
	if( ind_cnt == 0 ) {
		// COUNT結果を返す（0もあり）
		ret = hst_cnt;
	} else {
		sprintf( G_msg,
			"自動発生マスタ(jdkmkmst)の対象件数取得に失敗しました。"
			"受日[%s]依頼書[%s]処理日[%s] SELECT INDICATOR[%d]"
			,utkymd, irino, sriymd, ind_cnt );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		ret=RTN_NG;
	}
	// DEBUG
	sprintf( G_msg, "JDKMKMST COUNT[%d]", ret );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  関 数 名  ：SelJidoirai                                                   */
/*  機能概要  ：自動発生依頼項目情報 SELECT                                   */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  JIDOIRAI	pJir[];   : 自動発生依頼項目情報          */
/*   第２引数 ：int		kensu;   : malloc件数                                 */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		SelJidoirai( jdi, kensu )
struct		JIDOIRAI		*jdi;	
int			kensu;
{
	int		ret;
	int		i;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* 関数名称	*/
	struct	sqlca	sqlca;

	/* 初期処理	*/
	strcpy( func_nm, "SelJidoirai" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ホスト変数へのキー項目セット	*/
	memset( &hjdkmkmst,	'\0', sizeof( struct _JDKMKMST ));
	memset( &hkmkmst,	'\0', sizeof( struct _KMKMST ));
	memset( &hirai	,	'\0', sizeof( struct _IRAI ));
	strcpy( hirai.utkymd,	jdi[0].sIri.utkymd );
	strcpy( hirai.irino,	jdi[0].sIri.irino );
	strcpy( hirai.sriymd,	jdi[0].sIri.sriymd );


/*
EXEC SQL DECLARE    jdi_cur CURSOR  FOR
	SELECT	jido.*
			, km.kmkrs 
			, km.oyakmkcd
			, km.smpcd
			, km.fkbnkkb
			, irai.*
	FROM
		( SELECT	knsgrp, kmkcd , jknsgrp , jkmkcd , hhkumflg
			FROM	jdkmkmst
			WHERE	( knsgrp, kmkcd ) IN
						( SELECT	knsgrp, kmkcd 
							FROM	irai
							WHERE	utkymd	= :hirai.utkymd
							AND		irino	= :hirai.irino
						)
			AND		( jknsgrp, jkmkcd ) NOT IN
						( SELECT	knsgrp, kmkcd 
							FROM	irai
							WHERE	utkymd	= :hirai.utkymd
							AND		irino	= :hirai.irino
						)
			AND		kaiymd	<= :hirai.sriymd
			AND		haiymd	>= :hirai.sriymd
		) jido
		, kmkmst km
		, irai
	WHERE	irai.utkymd	= :hirai.utkymd
	AND		irai.irino	= :hirai.irino
	AND		irai.knsgrp	= jido.knsgrp
	AND		irai.kmkcd	= jido.kmkcd
	AND		jido.jknsgrp	= km.knsgrp
	AND		jido.jkmkcd	= km.kmkcd
	AND		km.kaiymd	<= :hirai.sriymd
	AND		km.haiymd	>= :hirai.sriymd
	ORDER BY jido.jknsgrp, jido.jkmkcd, irai.knsgrp, irai.kmkcd
	FOR	READ ONLY
	;
*/

#line 1291 "AD202_db.sqc"



/*
EXEC SQL OPEN jdi_cur;
*/

{
#line 1293 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1293 "AD202_db.sqc"
  sqlaaloc(2,10,20,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 1293 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1293 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hirai.utkymd;
#line 1293 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1293 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1293 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hirai.irino;
#line 1293 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1293 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 1293 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hirai.utkymd;
#line 1293 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1293 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 12;
#line 1293 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)hirai.irino;
#line 1293 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1293 "AD202_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 1293 "AD202_db.sqc"
      sql_setdlist[4].sqldata = (void*)hirai.sriymd;
#line 1293 "AD202_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1293 "AD202_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 1293 "AD202_db.sqc"
      sql_setdlist[5].sqldata = (void*)hirai.sriymd;
#line 1293 "AD202_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1293 "AD202_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 1293 "AD202_db.sqc"
      sql_setdlist[6].sqldata = (void*)hirai.utkymd;
#line 1293 "AD202_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1293 "AD202_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 12;
#line 1293 "AD202_db.sqc"
      sql_setdlist[7].sqldata = (void*)hirai.irino;
#line 1293 "AD202_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1293 "AD202_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 1293 "AD202_db.sqc"
      sql_setdlist[8].sqldata = (void*)hirai.sriymd;
#line 1293 "AD202_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1293 "AD202_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 1293 "AD202_db.sqc"
      sql_setdlist[9].sqldata = (void*)hirai.sriymd;
#line 1293 "AD202_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1293 "AD202_db.sqc"
      sqlasetdata(2,0,10,sql_setdlist,0L,0L);
    }
#line 1293 "AD202_db.sqc"
  sqlacall((unsigned short)26,13,2,0,0L);
#line 1293 "AD202_db.sqc"
  sqlastop(0L);
}

#line 1293 "AD202_db.sqc"


	i=0;

	while( sqlca.sqlcode == 0 ){
		
/*
EXEC SQL    FETCH   jdi_cur
					INTO	  :hjdkmkmst
							, :hkmkmst.kmkrs
							, :hkmkmst.oyakmkcd
							, :hkmkmst.smpcd
							, :hkmkmst.fkbnkkb
							, :hirai
					;
*/

{
#line 1305 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1305 "AD202_db.sqc"
  sqlaaloc(3,58,21,0L);
    {
      struct sqla_setdata_list sql_setdlist[58];
#line 1305 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 1305 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hjdkmkmst.knsgrp;
#line 1305 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 1305 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hjdkmkmst.kmkcd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 17;
#line 1305 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hjdkmkmst.jknsgrp;
#line 1305 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 1305 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)hjdkmkmst.jkmkcd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[4].sqldata = (void*)hjdkmkmst.hhkumflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 17;
#line 1305 "AD202_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkmkmst.kmkrs;
#line 1305 "AD202_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 1305 "AD202_db.sqc"
      sql_setdlist[6].sqldata = (void*)hkmkmst.oyakmkcd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 8;
#line 1305 "AD202_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkmkmst.smpcd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkmkmst.fkbnkkb;
#line 1305 "AD202_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 1305 "AD202_db.sqc"
      sql_setdlist[9].sqldata = (void*)hirai.utkymd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 12;
#line 1305 "AD202_db.sqc"
      sql_setdlist[10].sqldata = (void*)hirai.irino;
#line 1305 "AD202_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[11].sqldata = (void*)hirai.iriketflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[12].sqldata = (void*)&hirai.zssdino;
#line 1305 "AD202_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 17;
#line 1305 "AD202_db.sqc"
      sql_setdlist[13].sqldata = (void*)hirai.knsgrp;
#line 1305 "AD202_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 8;
#line 1305 "AD202_db.sqc"
      sql_setdlist[14].sqldata = (void*)hirai.kmkcd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[15].sqldata = (void*)hirai.irihsmkbn;
#line 1305 "AD202_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[16].sqldata = (void*)hirai.irikbn;
#line 1305 "AD202_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[17].sqldata = (void*)hirai.ksktkbn;
#line 1305 "AD202_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 11;
#line 1305 "AD202_db.sqc"
      sql_setdlist[18].sqldata = (void*)hirai.sriymd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 14;
#line 1305 "AD202_db.sqc"
      sql_setdlist[19].sqldata = (void*)hirai.kntno;
#line 1305 "AD202_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[20].sqldata = (void*)hirai.kntketflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 5;
#line 1305 "AD202_db.sqc"
      sql_setdlist[21].sqldata = (void*)hirai.chkmj;
#line 1305 "AD202_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 5;
#line 1305 "AD202_db.sqc"
      sql_setdlist[22].sqldata = (void*)hirai.stsrcd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 17;
#line 1305 "AD202_db.sqc"
      sql_setdlist[23].sqldata = (void*)hirai.kmkrs;
#line 1305 "AD202_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 8;
#line 1305 "AD202_db.sqc"
      sql_setdlist[24].sqldata = (void*)hirai.oyakmkcd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 8;
#line 1305 "AD202_db.sqc"
      sql_setdlist[25].sqldata = (void*)hirai.smpcd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 8;
#line 1305 "AD202_db.sqc"
      sql_setdlist[26].sqldata = (void*)hirai.setkmkcd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[27].sqldata = (void*)hirai.srinycd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 3;
#line 1305 "AD202_db.sqc"
      sql_setdlist[28].sqldata = (void*)hirai.seccd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[29].sqldata = (void*)hirai.skchkflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[30].sqldata = (void*)hirai.bkfkkbn;
#line 1305 "AD202_db.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 3;
#line 1305 "AD202_db.sqc"
      sql_setdlist[31].sqldata = (void*)hirai.ysnlbl;
#line 1305 "AD202_db.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[32].sqldata = (void*)hirai.skflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[33].sqldata = (void*)hirai.tkflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[34].sqldata = (void*)hirai.sjflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[35].sqldata = (void*)hirai.jktkflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 4;
#line 1305 "AD202_db.sqc"
      sql_setdlist[36].sqldata = (void*)hirai.kjno;
#line 1305 "AD202_db.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[37].sqldata = (void*)hirai.fkhkknohjkbn;
#line 1305 "AD202_db.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 4;
#line 1305 "AD202_db.sqc"
      sql_setdlist[38].sqldata = (void*)hirai.tbkjno;
#line 1305 "AD202_db.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[39].sqldata = (void*)hirai.tbkjflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 25;
#line 1305 "AD202_db.sqc"
      sql_setdlist[40].sqldata = (void*)hirai.htkfkhms;
#line 1305 "AD202_db.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 1305 "AD202_db.sqc"
      sql_setdlist[41].sqldata = (void*)hirai.tskflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 3;
#line 1305 "AD202_db.sqc"
      sql_setdlist[42].sqldata = (void*)hirai.tktflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[43].sqldata = (void*)hirai.bnckbn;
#line 1305 "AD202_db.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[44].sqldata = (void*)hirai.nbnckbn;
#line 1305 "AD202_db.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 11;
#line 1305 "AD202_db.sqc"
      sql_setdlist[45].sqldata = (void*)hirai.knskisyymd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 11;
#line 1305 "AD202_db.sqc"
      sql_setdlist[46].sqldata = (void*)hirai.knskryymd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 9;
#line 1305 "AD202_db.sqc"
      sql_setdlist[47].sqldata = (void*)hirai.knskrytme;
#line 1305 "AD202_db.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[48].sqldata = (void*)hirai.kkhkkflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[49].sqldata = (void*)hirai.kkiriflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[50].sqltype = 500; sql_setdlist[50].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[50].sqldata = (void*)&hirai.kkirilotno;
#line 1305 "AD202_db.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 5;
#line 1305 "AD202_db.sqc"
      sql_setdlist[51].sqldata = (void*)hirai.kktoutkid;
#line 1305 "AD202_db.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[52].sqltype = 500; sql_setdlist[52].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[52].sqldata = (void*)&hirai.knssu;
#line 1305 "AD202_db.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[53].sqldata = (void*)hirai.odrssflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 16;
#line 1305 "AD202_db.sqc"
      sql_setdlist[54].sqldata = (void*)hirai.ytiksbr;
#line 1305 "AD202_db.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[55].sqldata = (void*)hirai.hhkjkflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 27;
#line 1305 "AD202_db.sqc"
      sql_setdlist[56].sqldata = (void*)hirai.ksndh;
#line 1305 "AD202_db.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 27;
#line 1305 "AD202_db.sqc"
      sql_setdlist[57].sqldata = (void*)hirai.trkdh;
#line 1305 "AD202_db.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sqlasetdata(3,0,58,sql_setdlist,0L,0L);
    }
#line 1305 "AD202_db.sqc"
  sqlacall((unsigned short)25,13,0,3,0L);
#line 1305 "AD202_db.sqc"
  sqlastop(0L);
}

#line 1305 "AD202_db.sqc"


		if( i >  kensu ){
			break;
		}

		// DEBUG
		sprintf( G_err, "%d", sqlca.sqlcode );
		sprintf( G_msg, "FETCH jirai: jkmk[%s]<= utkymd[%s]irino[%s]srimd[%s] "
			"kmk[%s], zno[%d] ken[%d] ", hjdkmkmst.jkmkcd, hirai.utkymd 
			,hirai.irino ,hirai.sriymd ,hirai.kmkcd ,hirai.zssdino, i);
		LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		// 複数依頼項目から同一自動発生項目に該当する場合の考慮
		if( i > 0 ){
			if(( strcmp( hjdkmkmst.jknsgrp,	jdi[i-1].sJdm.jknsgrp ) == 0 )
			 &&( strcmp( hjdkmkmst.jkmkcd,	jdi[i-1].sJdm.jkmkcd ) == 0 )){
				continue;
			}
		}

		memcpy( &( jdi[i].sJdm ),	&hjdkmkmst,	sizeof( struct _JDKMKMST ));
		memcpy( &( jdi[i].sKmk ),	&hkmkmst,	sizeof( struct _KMKMST ));
		memcpy( &( jdi[i].sIri ),	&hirai,		sizeof( struct _IRAI ));

		// INDEX UP
		i++;
	}

	if ( sqlca.sqlcode == 0 ) {
		// FETCH OK BUT CONTINUE 対象データの場合の考慮
			ret = RTN_OK;
	} else if ( sqlca.sqlcode == 100 ) {	// NOT FOUND or END
		if( i > 0 ){
			ret = RTN_OK;
		} else {
			sprintf( G_msg,
				"自動発生依頼情報を取得できません。"
				"UKTYMD[%s] IRINO[%s] SRIYMD[%s]"
				, jdi[0].sIri.utkymd ,jdi[0].sIri.irino ,jdi[0].sIri.sriymd );
			EditCsvMsg( G_msg );
			LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			ret = RTN_NG;
		}
	} else {
		/* SQLCODE > 0 -> WARNING */
		/* SQLCODE < 0 -> ERROR */
		sprintf( G_msg,
			"自動発生依頼情報FETCH で不具合が発生しました。"
			"UKTYMD[%s] IRINO[%s] SRIYMD[%s]"
			, jdi[0].sIri.utkymd ,jdi[0].sIri.irino ,jdi[0].sIri.sriymd );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			 
		ret=RTN_DBERR;
	}

/*
EXEC SQL    CLOSE   jdi_cur;
*/

{
#line 1361 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1361 "AD202_db.sqc"
  sqlacall((unsigned short)20,13,0,0,0L);
#line 1361 "AD202_db.sqc"
  sqlastop(0L);
}

#line 1361 "AD202_db.sqc"


	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}
// 1.04 ADD END =============================================================
/****************************************************************************
****************************************************************************/
//-----<Ydbcommit>----------------------------------------------------------
int Ydbcommit()
{
	char	func_nm[MYAPP_LEN_FNCNM+1];
	int		ret=RTN_OK;
	struct	sqlca sqlca;

	strcpy( func_nm, "Ydbcommit" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	
/*
EXEC SQL COMMIT;
*/

{
#line 1379 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1379 "AD202_db.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 1379 "AD202_db.sqc"
  sqlastop(0L);
}

#line 1379 "AD202_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	LogOut( LT_DBG, LX_NON, G_err, "COMMIT", func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
  	return( RTN_OK );

} /* DbDisconn */

//-----<Ydbrollback>----------------------------------------------------------
int Ydbrollback()
{
	char	func_nm[MYAPP_LEN_FNCNM+1];
	int		ret=RTN_OK;
	struct	sqlca sqlca;

	strcpy( func_nm, "Ydbrollback" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* rollback the transaction */
	
/*
EXEC SQL ROLLBACK;
*/

{
#line 1405 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1405 "AD202_db.sqc"
  sqlacall((unsigned short)28,0,0,0,0L);
#line 1405 "AD202_db.sqc"
  sqlastop(0L);
}

#line 1405 "AD202_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//		sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[2] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	LogOut( LT_DBG, LX_NON, G_err, "ROLLBACK", func_nm, __FILE__, __LINE__ );
/*  SqlInfoPrint("ROLLBACK", &sqlca, __LINE__, __FILE__);*/

	if (sqlca.sqlcode == 0) {
		sprintf( G_msg, "The transaction was rolled back." );
		LogOut( LT_TRC, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
	}

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
  	return( RTN_OK );
} /* TransRollback */

//-----<Ydbconn>----------------------------------------------------------
int Ydbconn()
{
	char	func_nm[MYAPP_LEN_FNCNM+1];
	int		ret=RTN_OK;
	struct	sqlca sqlca;


/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 1432 "AD202_db.sqc"

	char	dbAlias[15];
	char	user[129];
	char	pswd[15];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 1436 "AD202_db.sqc"


	strcpy( func_nm, "Ydbconn" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	strcpy( dbAlias,	stcPRM.dbp_dbAlias );
	strcpy( user,		stcPRM.dbp_user );
	strcpy( pswd,		stcPRM.dbp_pswd );

	
/*
EXEC SQL CONNECT TO :dbAlias USER :user USING :pswd;
*/

{
#line 1445 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1445 "AD202_db.sqc"
  sqlaaloc(2,3,22,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 1445 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 15;
#line 1445 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)dbAlias;
#line 1445 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1445 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 129;
#line 1445 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)user;
#line 1445 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1445 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 15;
#line 1445 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)pswd;
#line 1445 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1445 "AD202_db.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 1445 "AD202_db.sqc"
  sqlacall((unsigned short)29,5,2,0,0L);
#line 1445 "AD202_db.sqc"
  sqlastop(0L);
}

#line 1445 "AD202_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	LogOut( LT_DBG, LX_NON, G_err, "CONNECT", func_nm, __FILE__, __LINE__ );

	/* 本当は"00000"でcmpareしたい	*/
	if( memcmp( sqlca.sqlstate, "00000", 5 ) != 0 ){
		/* ERROR  */
		sprintf( G_msg, "ＤＢ２への接続に失敗しました。" );
		LogOut( LT_TRC, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		ret = RTN_NG;
	}

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
  	return( ret );
} /* DbConn */

//-----<Ydbdisconn>----------------------------------------------------------
int Ydbdisconn()
{
	struct sqlca sqlca;
	char	func_nm[MYAPP_LEN_FNCNM+1];
	int	ret=RTN_OK;

	strcpy( func_nm, "Ydbdisconn" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

  	/* Commit all non-committed transactions to release database locks */
	
/*
EXEC SQL COMMIT;
*/

{
#line 1478 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1478 "AD202_db.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 1478 "AD202_db.sqc"
  sqlastop(0L);
}

#line 1478 "AD202_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	LogOut( LT_DBG, LX_NON, G_err, "COMMIT BEFORE CONNECT RESET"
			, func_nm, __FILE__, __LINE__ );

	
/*
EXEC SQL CONNECT RESET;
*/

{
#line 1489 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1489 "AD202_db.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 1489 "AD202_db.sqc"
  sqlastop(0L);
}

#line 1489 "AD202_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	LogOut( LT_DBG, LX_NON, G_err, "CONNECT RESET",func_nm, __FILE__, __LINE__);

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
  	return( RTN_OK );
} /* DbDisconn */
/** End of File ***************************************************************/
