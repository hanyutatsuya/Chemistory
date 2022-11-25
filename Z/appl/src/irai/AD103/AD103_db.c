static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,104,66,97,69,85,87,67,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,65,68,49,48,51,95,68,66,0,0,0,0,0,0,0,0,
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


#line 1 "AD103_db.sqc"
/*****************************************************************************/
/*   ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/*   システム名：次世代システム                                               */
/*   ファイル名：AD103_db.sqc                                                 */
/*   概      要：ＤＢアクセス                                                 */
/*   OS        ：SUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   言語      ：DB2/C                                                        */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/08     INTEC.INC      CREATE                             */
/*  1.01     2006/05/01     INTEC.INC      SJIS,項目追加(親施設,登録日時)対応 */
/*  1.03     2006/06/10     INTEC.INC      患者属性修正時依頼情報世代No更新   */
/*  1.04     2009/06/29     Merits K.Ameno 障害管理No:0904031814/0904031719対応*/
/*                                         SelKanjya関数追加/DelKanjya関数追加*/
/*                                         InsShusei_Kanjya関数追加           */
/******************************************************************************/

/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include	<stdio.h>
#include 	<stdlib.h>
#include 	<string.h>
#include	<sqlca.h>
#include	"AD103.h"


/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 30 "AD103_db.sqc"


/*
EXEC SQL INCLUDE 'tagAD103.h';
*/

#line 1 "/home/kea00sys/appl/src/irai/AD103/tagAD103.h"
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

#line 31 "AD103_db.sqc"

	char		hst_ymd[11];
	char		hst_utkymd[10+1]; 
    char    	hst_irino[11+1];
	sqlint32	hst_zssdino;
	short		ind_zssdino;
	sqlint32	hst_cnt;
	short		ind_cnt;

/*
EXEC SQL END DECLARE SECTION;
*/

#line 39 "AD103_db.sqc"


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
		 	kjnsriymd
			, nxirisriymd
			, iriendflg
	INTO	:hsysknrmst.kjnsriymd
			, :hsysknrmst.nxirisriymd
			, :hsysknrmst.iriendflg
	FROM	sysknrmst
	;
*/

{
#line 72 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 72 "AD103_db.sqc"
  sqlaaloc(3,3,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 72 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 72 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hsysknrmst.kjnsriymd;
#line 72 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 72 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 72 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hsysknrmst.nxirisriymd;
#line 72 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 72 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 72 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hsysknrmst.iriendflg;
#line 72 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 72 "AD103_db.sqc"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 72 "AD103_db.sqc"
  sqlacall((unsigned short)24,1,0,3,0L);
#line 72 "AD103_db.sqc"
  sqlastop(0L);
}

#line 72 "AD103_db.sqc"


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
	sprintf( G_msg, "SELECT kjnsriymd FROM sysknrmst" );
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
#line 126 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 126 "AD103_db.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 126 "AD103_db.sqc"
  sqlastop(0L);
}

#line 126 "AD103_db.sqc"


	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  関 数 名  ：SelEigmst                                                     */
/*  機能概要  ：営業所マスタ SELECT                                           */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  _EIGMST    *egm;   : 営業所マスタ                     */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		SelEigmst( egm )
struct		_EIGMST		*egm;			/* 営業所マスタ */
{

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 144 "AD103_db.sqc"

	char		hst_shcd[3];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 146 "AD103_db.sqc"

	int		ret;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* 関数名称	*/
	struct	sqlca	sqlca;

	/* 初期処理	*/
	strcpy( func_nm, "SelEigmst" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ホスト変数へのキー項目セット	*/
	memset( &heigmst,		'\0', sizeof( struct _EIGMST ));
	strcpy( heigmst.ecd,	egm->ecd );
	strcpy( hst_shcd,		egm->shcdfr );
	strcpy( hst_ymd,		egm->kaiymd );


/*
EXEC SQL SELECT	
			  shcdfr
			, shcdto
			, yjhkkbn
			, kaiymd
			, haiymd
	INTO	  :heigmst.shcdfr
		  	, :heigmst.shcdto
		  	, :heigmst.yjhkkbn
			, :heigmst.kaiymd
			, :heigmst.haiymd
	FROM	eigmst
	WHERE	ecd		=  :heigmst.ecd
	AND		shcdfr	<= :hst_shcd
	AND		shcdto	>= :hst_shcd
	AND		kaiymd	<= :hst_ymd
	AND		haiymd	>= :hst_ymd
	;
*/

{
#line 178 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 178 "AD103_db.sqc"
  sqlaaloc(2,5,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 178 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 4;
#line 178 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)heigmst.ecd;
#line 178 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 178 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 178 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_shcd;
#line 178 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 178 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 178 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hst_shcd;
#line 178 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 178 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 178 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)hst_ymd;
#line 178 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 178 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 178 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)hst_ymd;
#line 178 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 178 "AD103_db.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 178 "AD103_db.sqc"
  sqlaaloc(3,5,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 178 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 178 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)heigmst.shcdfr;
#line 178 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 178 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 178 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)heigmst.shcdto;
#line 178 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 178 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 178 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)heigmst.yjhkkbn;
#line 178 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 178 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 178 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)heigmst.kaiymd;
#line 178 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 178 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 178 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)heigmst.haiymd;
#line 178 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 178 "AD103_db.sqc"
      sqlasetdata(3,0,5,sql_setdlist,0L,0L);
    }
#line 178 "AD103_db.sqc"
  sqlacall((unsigned short)24,2,2,3,0L);
#line 178 "AD103_db.sqc"
  sqlastop(0L);
}

#line 178 "AD103_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "SELECT eigmst : ecd[%s]shcd[%s]ymd[%s]",
		egm->ecd, egm->shcdfr, egm->kaiymd );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if ( sqlca.sqlcode == 0 ) {		/* OK */
		memcpy( egm, &heigmst,	sizeof( struct _EIGMST ));
		ret = RTN_OK;
	} else {
		if ( sqlca.sqlcode == 100 ){	/* NOT FOUND */
			/* SQLCODE +100, SQLSTATE '02000' */
			sprintf( G_msg,
				"営業所マスタが存在しません。営業所[%s]集配[%s]基準日[%s]"
				,egm->ecd, egm->shcdfr, egm->kaiymd );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

			ret=RTN_ZERO;
		} else {
			/* SQLCODE > 0 -> WARNING */
			/* SQLCODE < 0 -> ERROR */
			sprintf( G_msg,
				"営業マスタ SELECT で不具合が発生しました。"
				"営業所[%s]集配[%s]基準日[%s]"
				,egm->ecd, egm->shcdfr, egm->kaiymd );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			 
			ret=RTN_DBERR;
		}
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  関 数 名  ：InsKanjya                                                     */
/*  機能概要  ：属性属性　INSERT                                              */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  _KANJYA     *zok;   : 患者情報                        */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		InsKanjya( kan )
struct		_KANJYA	*kan;			/* 属性データ */
{
	struct	sqlca	sqlca;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/
	int	ret;

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
		, oyasstcd				-- 1.01 ADD
		, trkdh					-- 1.01 ADD
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
#line 424 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 424 "AD103_db.sqc"
  sqlaaloc(2,87,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 424 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 424 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.utkymd;
#line 424 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 424 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.irino;
#line 424 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkanjya.iriketflg;
#line 424 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)&hkanjya.zssdino;
#line 424 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 424 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkanjya.sstcd;
#line 424 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 5;
#line 424 "AD103_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkanjya.subsstcd;
#line 424 "AD103_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 3;
#line 424 "AD103_db.sqc"
      sql_setdlist[6].sqldata = (void*)hkanjya.cdkbn1;
#line 424 "AD103_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 424 "AD103_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkanjya.cdkbn2;
#line 424 "AD103_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 41;
#line 424 "AD103_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkanjya.irimkey;
#line 424 "AD103_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 4;
#line 424 "AD103_db.sqc"
      sql_setdlist[9].sqldata = (void*)hkanjya.srkcd;
#line 424 "AD103_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 31;
#line 424 "AD103_db.sqc"
      sql_setdlist[10].sqldata = (void*)hkanjya.srknm;
#line 424 "AD103_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 424 "AD103_db.sqc"
      sql_setdlist[11].sqldata = (void*)hkanjya.tticd;
#line 424 "AD103_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 41;
#line 424 "AD103_db.sqc"
      sql_setdlist[12].sqldata = (void*)hkanjya.ttinm;
#line 424 "AD103_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 424 "AD103_db.sqc"
      sql_setdlist[13].sqldata = (void*)hkanjya.gpcd;
#line 424 "AD103_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 41;
#line 424 "AD103_db.sqc"
      sql_setdlist[14].sqldata = (void*)hkanjya.gpnm;
#line 424 "AD103_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 424 "AD103_db.sqc"
      sql_setdlist[15].sqldata = (void*)hkanjya.skicd;
#line 424 "AD103_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 41;
#line 424 "AD103_db.sqc"
      sql_setdlist[16].sqldata = (void*)hkanjya.skinm;
#line 424 "AD103_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 41;
#line 424 "AD103_db.sqc"
      sql_setdlist[17].sqldata = (void*)hkanjya.krtno;
#line 424 "AD103_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 16;
#line 424 "AD103_db.sqc"
      sql_setdlist[18].sqldata = (void*)hkanjya.knjid;
#line 424 "AD103_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 61;
#line 424 "AD103_db.sqc"
      sql_setdlist[19].sqldata = (void*)hkanjya.knjnmn;
#line 424 "AD103_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 31;
#line 424 "AD103_db.sqc"
      sql_setdlist[20].sqldata = (void*)hkanjya.knjnmk;
#line 424 "AD103_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 61;
#line 424 "AD103_db.sqc"
      sql_setdlist[21].sqldata = (void*)hkanjya.knjnmkey;
#line 424 "AD103_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 6;
#line 424 "AD103_db.sqc"
      sql_setdlist[22].sqldata = (void*)hkanjya.sc;
#line 424 "AD103_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 6;
#line 424 "AD103_db.sqc"
      sql_setdlist[23].sqldata = (void*)hkanjya.tj;
#line 424 "AD103_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[24].sqldata = (void*)hkanjya.tjtni;
#line 424 "AD103_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[25].sqldata = (void*)hkanjya.sbtkbn;
#line 424 "AD103_db.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 9;
#line 424 "AD103_db.sqc"
      sql_setdlist[26].sqldata = (void*)hkanjya.birthday;
#line 424 "AD103_db.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[27].sqldata = (void*)hkanjya.birthdaykbn;
#line 424 "AD103_db.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 4;
#line 424 "AD103_db.sqc"
      sql_setdlist[28].sqldata = (void*)hkanjya.age;
#line 424 "AD103_db.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[29].sqldata = (void*)hkanjya.agekbn;
#line 424 "AD103_db.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 11;
#line 424 "AD103_db.sqc"
      sql_setdlist[30].sqldata = (void*)hkanjya.btcd;
#line 424 "AD103_db.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 31;
#line 424 "AD103_db.sqc"
      sql_setdlist[31].sqldata = (void*)hkanjya.btnm;
#line 424 "AD103_db.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 424 "AD103_db.sqc"
      sql_setdlist[32].sqldata = (void*)hkanjya.utkcmtcd1;
#line 424 "AD103_db.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 424 "AD103_db.sqc"
      sql_setdlist[33].sqldata = (void*)hkanjya.utkcmtcd2;
#line 424 "AD103_db.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 3;
#line 424 "AD103_db.sqc"
      sql_setdlist[34].sqldata = (void*)hkanjya.utkcmtcd3;
#line 424 "AD103_db.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 71;
#line 424 "AD103_db.sqc"
      sql_setdlist[35].sqldata = (void*)hkanjya.utkcmtfr1;
#line 424 "AD103_db.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 71;
#line 424 "AD103_db.sqc"
      sql_setdlist[36].sqldata = (void*)hkanjya.utkcmtfr2;
#line 424 "AD103_db.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[37].sqldata = (void*)hkanjya.utkcmtfrflg;
#line 424 "AD103_db.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[38].sqldata = (void*)hkanjya.ngkbn;
#line 424 "AD103_db.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 3;
#line 424 "AD103_db.sqc"
      sql_setdlist[39].sqldata = (void*)hkanjya.nsssu;
#line 424 "AD103_db.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[40].sqldata = (void*)hkanjya.hkncd;
#line 424 "AD103_db.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 424 "AD103_db.sqc"
      sql_setdlist[41].sqldata = (void*)hkanjya.ktshsu;
#line 424 "AD103_db.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 11;
#line 424 "AD103_db.sqc"
      sql_setdlist[42].sqldata = (void*)hkanjya.iniriymd;
#line 424 "AD103_db.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[43].sqldata = (void*)hkanjya.zssflg;
#line 424 "AD103_db.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[44].sqldata = (void*)hkanjya.kkiriflg;
#line 424 "AD103_db.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[45].sqldata = (void*)hkanjya.hknskbn;
#line 424 "AD103_db.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[46].sqldata = (void*)hkanjya.utkkbn;
#line 424 "AD103_db.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[47].sqldata = (void*)hkanjya.nekbn;
#line 424 "AD103_db.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[48].sqldata = (void*)hkanjya.inknskbn;
#line 424 "AD103_db.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[49].sqldata = (void*)hkanjya.utkjkkbn;
#line 424 "AD103_db.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[50].sqldata = (void*)hkanjya.krflg;
#line 424 "AD103_db.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[51].sqldata = (void*)hkanjya.fdhhkkflg;
#line 424 "AD103_db.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 9;
#line 424 "AD103_db.sqc"
      sql_setdlist[52].sqldata = (void*)hkanjya.utkdh;
#line 424 "AD103_db.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 11;
#line 424 "AD103_db.sqc"
      sql_setdlist[53].sqldata = (void*)hkanjya.mutkymd;
#line 424 "AD103_db.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 12;
#line 424 "AD103_db.sqc"
      sql_setdlist[54].sqldata = (void*)hkanjya.mirino;
#line 424 "AD103_db.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 424 "AD103_db.sqc"
      sql_setdlist[55].sqldata = (void*)hkanjya.knsjslbcd1;
#line 424 "AD103_db.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 4;
#line 424 "AD103_db.sqc"
      sql_setdlist[56].sqldata = (void*)hkanjya.knsjslbcd2;
#line 424 "AD103_db.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 4;
#line 424 "AD103_db.sqc"
      sql_setdlist[57].sqldata = (void*)hkanjya.knsjslbcd3;
#line 424 "AD103_db.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[58].sqltype = 460; sql_setdlist[58].sqllen = 4;
#line 424 "AD103_db.sqc"
      sql_setdlist[58].sqldata = (void*)hkanjya.knsjslbcd4;
#line 424 "AD103_db.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[59].sqltype = 460; sql_setdlist[59].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[59].sqldata = (void*)hkanjya.ymhkkflg;
#line 424 "AD103_db.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[60].sqltype = 460; sql_setdlist[60].sqllen = 9;
#line 424 "AD103_db.sqc"
      sql_setdlist[60].sqldata = (void*)hkanjya.hkkkbdh;
#line 424 "AD103_db.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[61].sqltype = 460; sql_setdlist[61].sqllen = 4;
#line 424 "AD103_db.sqc"
      sql_setdlist[61].sqldata = (void*)hkanjya.ecd;
#line 424 "AD103_db.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[62].sqltype = 460; sql_setdlist[62].sqllen = 3;
#line 424 "AD103_db.sqc"
      sql_setdlist[62].sqldata = (void*)hkanjya.shcd;
#line 424 "AD103_db.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[63].sqltype = 460; sql_setdlist[63].sqllen = 41;
#line 424 "AD103_db.sqc"
      sql_setdlist[63].sqldata = (void*)hkanjya.sstssnmj;
#line 424 "AD103_db.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sqlasetdata(2,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[23];
#line 424 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 41;
#line 424 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.sstssnmn;
#line 424 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 424 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.sstrsj;
#line 424 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 424 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkanjya.sstrsn;
#line 424 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 424 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)hkanjya.sstsbt;
#line 424 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkanjya.ttsstflg;
#line 424 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 424 "AD103_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkanjya.rucd;
#line 424 "AD103_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[6].sqldata = (void*)&hkanjya.irikmksu;
#line 424 "AD103_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 424 "AD103_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkanjya.bmskn;
#line 424 "AD103_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 3;
#line 424 "AD103_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkanjya.irinrsbt;
#line 424 "AD103_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[9].sqldata = (void*)hkanjya.irihsmkbn;
#line 424 "AD103_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[10].sqldata = (void*)hkanjya.caresstflg;
#line 424 "AD103_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[11].sqldata = (void*)hkanjya.tktyflg;
#line 424 "AD103_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 14;
#line 424 "AD103_db.sqc"
      sql_setdlist[12].sqldata = (void*)hkanjya.apkntino;
#line 424 "AD103_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 424 "AD103_db.sqc"
      sql_setdlist[13].sqldata = (void*)hkanjya.sdnm;
#line 424 "AD103_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 21;
#line 424 "AD103_db.sqc"
      sql_setdlist[14].sqldata = (void*)hkanjya.bko1;
#line 424 "AD103_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 21;
#line 424 "AD103_db.sqc"
      sql_setdlist[15].sqldata = (void*)hkanjya.bko2;
#line 424 "AD103_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 21;
#line 424 "AD103_db.sqc"
      sql_setdlist[16].sqldata = (void*)hkanjya.bko3;
#line 424 "AD103_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 424 "AD103_db.sqc"
      sql_setdlist[17].sqldata = (void*)hkanjya.zstrdh;
#line 424 "AD103_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 424 "AD103_db.sqc"
      sql_setdlist[18].sqldata = (void*)hkanjya.zsssdh;
#line 424 "AD103_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 424 "AD103_db.sqc"
      sql_setdlist[19].sqldata = (void*)hkanjya.stlzsssdh;
#line 424 "AD103_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 16;
#line 424 "AD103_db.sqc"
      sql_setdlist[20].sqldata = (void*)hkanjya.stlzsssip;
#line 424 "AD103_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 9;
#line 424 "AD103_db.sqc"
      sql_setdlist[21].sqldata = (void*)hkanjya.stlzssssyaid;
#line 424 "AD103_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 8;
#line 424 "AD103_db.sqc"
      sql_setdlist[22].sqldata = (void*)hkanjya.oyasstcd;
#line 424 "AD103_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sqlasetdata(2,64,23,sql_setdlist,0L,0L);
    }
#line 424 "AD103_db.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 424 "AD103_db.sqc"
  sqlastop(0L);
}

#line 424 "AD103_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "INSERT kanjya : utkymd[%s]irino[%s]zssdino[%d]",
		kan->utkymd, kan->irino, kan->zssdino );
	LogOut( LT_DBG, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if ( sqlca.sqlcode == 0 ) {		/* OK */
		ret = RTN_OK;
	} else {
		if ( sqlca.sqlcode == MYAPP_RTN_DUP ) {	// duplicate
			sprintf( G_msg,
				"患者情報(kanjya)は既に存在しています。"
				"BML受付年月日[%s]依頼書NO[%s]属性世代NO[%d]"
				,kan->utkymd, kan->irino, kan->zssdino );
			/* ERROR */
			ret=MYAPP_RTN_DUP;
		} else {
			sprintf( G_msg,
				"患者情報(kanjya)の INSERT に失敗しました。"
				"BML受付年月日[%s]依頼書NO[%s]属性世代NO[%d]"
				,kan->utkymd, kan->irino, kan->zssdino );
			/* ERROR */
			ret=RTN_DBERR;
		}
		EditCsvMsg( G_msg );
		LogOut( LT_TRC, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__ );
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  関 数 名  ：SelKanjyaZssdinoMax                                           */
/*  機能概要  ：患者情報．属性世代NO　MAX取得                                 */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  _KANJYA    *kan;   : 患者情報                         */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：以外         異常終了                                         */
/******************************************************************************/
int		SelKanjyaZssdinoMax( kan )
struct		_KANJYA		*kan;			// 患者情報
{
	int		ret;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* 関数名称	*/
	struct	sqlca	sqlca;

	/* 初期処理	*/
	strcpy( func_nm, "SelKanjyaZssdinoMax" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ホスト変数へのキー項目セット	*/
	memcpy( &hkanjya, kan, sizeof( struct _KANJYA ));
	hst_zssdino=0;
	ind_zssdino=0;


/*
EXEC SQL SELECT	MAX( zssdino )
	INTO	  :hst_zssdino	INDICATOR :ind_zssdino
	FROM	kanjya
	WHERE	utkymd	= :hkanjya.utkymd
	AND		irino	= :hkanjya.irino
	;
*/

{
#line 491 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 491 "AD103_db.sqc"
  sqlaaloc(2,2,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 491 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 491 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.utkymd;
#line 491 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 491 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 491 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.irino;
#line 491 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 491 "AD103_db.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 491 "AD103_db.sqc"
  sqlaaloc(3,1,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 491 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 497; sql_setdlist[0].sqllen = 4;
#line 491 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)&hst_zssdino;
#line 491 "AD103_db.sqc"
      sql_setdlist[0].sqlind = &ind_zssdino;
#line 491 "AD103_db.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 491 "AD103_db.sqc"
  sqlacall((unsigned short)24,4,2,3,0L);
#line 491 "AD103_db.sqc"
  sqlastop(0L);
}

#line 491 "AD103_db.sqc"


	/* SQLCODE */
	// edit sqlcacode for LogOut errcode
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "SELECT MAX(zssdino) FROM kanjya : "
		"utkymd[%s]irino[%s] indicator[%d] sqlcode[%s]",
		kan->utkymd, kan->irino, ind_zssdino, G_err );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	// 標識変数による判断
		// sqlcode=0 indicator=0  -> FOUND
		// sqlcode=0 indicator=-1 -> NOT FOUND
		// sqlcode<>0 -> DB ERROR
	if (sqlca.sqlcode == 0) {		/* OK */
		if( ind_zssdino == 0 ) {
			kan->zssdino=hst_zssdino;
			ret = RTN_OK;
		} else if( ind_zssdino == -1 ){	/* NOT FOUND */
			kan->zssdino=0;
			ret = RTN_ZERO;
		}
	} else {
		sprintf( G_msg,
			"修正対象の患者情報(kanjya)のMAX( 属性世代NO )取得に失敗しました。"
			"BML受付年月日[%s]依頼書NO[%s] SELECT INDICATOR[%d]"
			,kan->utkymd, kan->irino, ind_zssdino );
		EditCsvMsg( G_msg );
		LogOut( LT_TRC, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		kan->zssdino=0;
		ret=RTN_NG;
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  関 数 名  ：UpdKanjyaTktyflg                                              */
/*  機能概要  ：患者情報.治験拡張フラグ UPDATE                                */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  _KANJYA    *kan;   : 患者情報                         */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/*  特記事項  ：INSERT と　同一transaction内のupdateのためselectしない        */
/******************************************************************************/
int		UpdKanjyaTktyflg( kan )
struct		_KANJYA		*kan;			/* 患者情報 */
{
	int		ret;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* 関数名称	*/
	struct	sqlca	sqlca;

	/* 初期処理	*/
	strcpy( func_nm, "UpdKanjyaTktyflg" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ホスト変数へのキー項目セット	*/
	memcpy( &hkanjya, kan, sizeof( struct _KANJYA ));


/*
EXEC SQL UPDATE	kanjya	
	SET		tktyflg = '1'
	WHERE	utkymd	= :hkanjya.utkymd
	AND		irino	= :hkanjya.irino
	AND		zssdino	= :hkanjya.zssdino
	;
*/

{
#line 559 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 559 "AD103_db.sqc"
  sqlaaloc(2,3,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 559 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 559 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.utkymd;
#line 559 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 559 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 559 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.irino;
#line 559 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 559 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 559 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)&hkanjya.zssdino;
#line 559 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 559 "AD103_db.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 559 "AD103_db.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 559 "AD103_db.sqc"
  sqlastop(0L);
}

#line 559 "AD103_db.sqc"


    /* not found --> SQLCODE = +100, SQLSTATE == '02000' */
	/* many rows --> ERROR!!         SQLSTATE == '21000' */

	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "UPDATE kanjya : utkymd[%s]irino[%s]zssdino[%d]",
		kan->utkymd, kan->irino, kan->zssdino );
	LogOut( LT_DBG, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if (sqlca.sqlcode == 0) {		/* OK */
		ret = RTN_OK;
	} else {
		/* SQLCODE > 0 -> WARNING */
		/* SQLCODE < 0 -> ERROR */
		sprintf( G_msg,
			"患者情報(kanjya)の UPDATE に失敗しました。"
			"BML受付年月日[%s]依頼書NO[%s]属性世代NO[%d]"
			,kan->utkymd, kan->irino, kan->zssdino );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		ret=RTN_DBERR;
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  関 数 名  ：UpdKinkyuKanjya                                               */
/*  機能概要  ：AS400後日依頼対応　患者情報 UPDATE                            */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  _KANJYA    *kan;   : 患者情報                         */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		UpdKinkyuKanjya( kan )
struct		_KANJYA		*kan;			/* 患者情報 */
{
	int		ret;
	char	func_nm[30];				/* 関数名称	*/
	char	wbuf[30];					// 1.01 登録日時退避用
	struct	sqlca	sqlca;

	/* 初期処理	*/
	strcpy( func_nm, "UpdKinkyuKanjya" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ホスト変数へのキー項目セット	*/
	memset( &hkanjya, '\0', sizeof( struct _KANJYA ));
	strcpy( hkanjya.utkymd,	kan->utkymd );
	strcpy( hkanjya.irino,	kan->irino );
	hkanjya.zssdino=kan->zssdino;

// ----- SELECT  ------------------------------------------------------------
	// 対象データのSELECT

/*
EXEC SQL SELECT	* INTO
		  :hkanjya.utkymd
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
		, :hkanjya.ksndh
		, :hkanjya.oyasstcd				-- 1.01 ADD
		, :hkanjya.trkdh				-- 1.01 ADD
	FROM	kanjya
	WHERE	utkymd	= :hkanjya.utkymd
	AND		irino	= :hkanjya.irino
	AND		zssdino	= :hkanjya.zssdino
	;
*/

{
#line 715 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 715 "AD103_db.sqc"
  sqlaaloc(2,3,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 715 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 715 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.utkymd;
#line 715 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 715 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.irino;
#line 715 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)&hkanjya.zssdino;
#line 715 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 715 "AD103_db.sqc"
  sqlaaloc(3,89,9,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 715 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 715 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.utkymd;
#line 715 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 715 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.irino;
#line 715 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkanjya.iriketflg;
#line 715 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)&hkanjya.zssdino;
#line 715 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 715 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkanjya.sstcd;
#line 715 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 5;
#line 715 "AD103_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkanjya.subsstcd;
#line 715 "AD103_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 3;
#line 715 "AD103_db.sqc"
      sql_setdlist[6].sqldata = (void*)hkanjya.cdkbn1;
#line 715 "AD103_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 715 "AD103_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkanjya.cdkbn2;
#line 715 "AD103_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 41;
#line 715 "AD103_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkanjya.irimkey;
#line 715 "AD103_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 4;
#line 715 "AD103_db.sqc"
      sql_setdlist[9].sqldata = (void*)hkanjya.srkcd;
#line 715 "AD103_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 31;
#line 715 "AD103_db.sqc"
      sql_setdlist[10].sqldata = (void*)hkanjya.srknm;
#line 715 "AD103_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 715 "AD103_db.sqc"
      sql_setdlist[11].sqldata = (void*)hkanjya.tticd;
#line 715 "AD103_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 41;
#line 715 "AD103_db.sqc"
      sql_setdlist[12].sqldata = (void*)hkanjya.ttinm;
#line 715 "AD103_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 715 "AD103_db.sqc"
      sql_setdlist[13].sqldata = (void*)hkanjya.gpcd;
#line 715 "AD103_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 41;
#line 715 "AD103_db.sqc"
      sql_setdlist[14].sqldata = (void*)hkanjya.gpnm;
#line 715 "AD103_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 715 "AD103_db.sqc"
      sql_setdlist[15].sqldata = (void*)hkanjya.skicd;
#line 715 "AD103_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 41;
#line 715 "AD103_db.sqc"
      sql_setdlist[16].sqldata = (void*)hkanjya.skinm;
#line 715 "AD103_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 41;
#line 715 "AD103_db.sqc"
      sql_setdlist[17].sqldata = (void*)hkanjya.krtno;
#line 715 "AD103_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 16;
#line 715 "AD103_db.sqc"
      sql_setdlist[18].sqldata = (void*)hkanjya.knjid;
#line 715 "AD103_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 61;
#line 715 "AD103_db.sqc"
      sql_setdlist[19].sqldata = (void*)hkanjya.knjnmn;
#line 715 "AD103_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 31;
#line 715 "AD103_db.sqc"
      sql_setdlist[20].sqldata = (void*)hkanjya.knjnmk;
#line 715 "AD103_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 61;
#line 715 "AD103_db.sqc"
      sql_setdlist[21].sqldata = (void*)hkanjya.knjnmkey;
#line 715 "AD103_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 6;
#line 715 "AD103_db.sqc"
      sql_setdlist[22].sqldata = (void*)hkanjya.sc;
#line 715 "AD103_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 6;
#line 715 "AD103_db.sqc"
      sql_setdlist[23].sqldata = (void*)hkanjya.tj;
#line 715 "AD103_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[24].sqldata = (void*)hkanjya.tjtni;
#line 715 "AD103_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[25].sqldata = (void*)hkanjya.sbtkbn;
#line 715 "AD103_db.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 9;
#line 715 "AD103_db.sqc"
      sql_setdlist[26].sqldata = (void*)hkanjya.birthday;
#line 715 "AD103_db.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[27].sqldata = (void*)hkanjya.birthdaykbn;
#line 715 "AD103_db.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 4;
#line 715 "AD103_db.sqc"
      sql_setdlist[28].sqldata = (void*)hkanjya.age;
#line 715 "AD103_db.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[29].sqldata = (void*)hkanjya.agekbn;
#line 715 "AD103_db.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 11;
#line 715 "AD103_db.sqc"
      sql_setdlist[30].sqldata = (void*)hkanjya.btcd;
#line 715 "AD103_db.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 31;
#line 715 "AD103_db.sqc"
      sql_setdlist[31].sqldata = (void*)hkanjya.btnm;
#line 715 "AD103_db.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 715 "AD103_db.sqc"
      sql_setdlist[32].sqldata = (void*)hkanjya.utkcmtcd1;
#line 715 "AD103_db.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 715 "AD103_db.sqc"
      sql_setdlist[33].sqldata = (void*)hkanjya.utkcmtcd2;
#line 715 "AD103_db.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 3;
#line 715 "AD103_db.sqc"
      sql_setdlist[34].sqldata = (void*)hkanjya.utkcmtcd3;
#line 715 "AD103_db.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 71;
#line 715 "AD103_db.sqc"
      sql_setdlist[35].sqldata = (void*)hkanjya.utkcmtfr1;
#line 715 "AD103_db.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 71;
#line 715 "AD103_db.sqc"
      sql_setdlist[36].sqldata = (void*)hkanjya.utkcmtfr2;
#line 715 "AD103_db.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[37].sqldata = (void*)hkanjya.utkcmtfrflg;
#line 715 "AD103_db.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[38].sqldata = (void*)hkanjya.ngkbn;
#line 715 "AD103_db.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 3;
#line 715 "AD103_db.sqc"
      sql_setdlist[39].sqldata = (void*)hkanjya.nsssu;
#line 715 "AD103_db.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[40].sqldata = (void*)hkanjya.hkncd;
#line 715 "AD103_db.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 715 "AD103_db.sqc"
      sql_setdlist[41].sqldata = (void*)hkanjya.ktshsu;
#line 715 "AD103_db.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 11;
#line 715 "AD103_db.sqc"
      sql_setdlist[42].sqldata = (void*)hkanjya.iniriymd;
#line 715 "AD103_db.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[43].sqldata = (void*)hkanjya.zssflg;
#line 715 "AD103_db.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[44].sqldata = (void*)hkanjya.kkiriflg;
#line 715 "AD103_db.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[45].sqldata = (void*)hkanjya.hknskbn;
#line 715 "AD103_db.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[46].sqldata = (void*)hkanjya.utkkbn;
#line 715 "AD103_db.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[47].sqldata = (void*)hkanjya.nekbn;
#line 715 "AD103_db.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[48].sqldata = (void*)hkanjya.inknskbn;
#line 715 "AD103_db.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[49].sqldata = (void*)hkanjya.utkjkkbn;
#line 715 "AD103_db.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[50].sqldata = (void*)hkanjya.krflg;
#line 715 "AD103_db.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[51].sqldata = (void*)hkanjya.fdhhkkflg;
#line 715 "AD103_db.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 9;
#line 715 "AD103_db.sqc"
      sql_setdlist[52].sqldata = (void*)hkanjya.utkdh;
#line 715 "AD103_db.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 11;
#line 715 "AD103_db.sqc"
      sql_setdlist[53].sqldata = (void*)hkanjya.mutkymd;
#line 715 "AD103_db.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 12;
#line 715 "AD103_db.sqc"
      sql_setdlist[54].sqldata = (void*)hkanjya.mirino;
#line 715 "AD103_db.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 715 "AD103_db.sqc"
      sql_setdlist[55].sqldata = (void*)hkanjya.knsjslbcd1;
#line 715 "AD103_db.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 4;
#line 715 "AD103_db.sqc"
      sql_setdlist[56].sqldata = (void*)hkanjya.knsjslbcd2;
#line 715 "AD103_db.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 4;
#line 715 "AD103_db.sqc"
      sql_setdlist[57].sqldata = (void*)hkanjya.knsjslbcd3;
#line 715 "AD103_db.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[58].sqltype = 460; sql_setdlist[58].sqllen = 4;
#line 715 "AD103_db.sqc"
      sql_setdlist[58].sqldata = (void*)hkanjya.knsjslbcd4;
#line 715 "AD103_db.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[59].sqltype = 460; sql_setdlist[59].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[59].sqldata = (void*)hkanjya.ymhkkflg;
#line 715 "AD103_db.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[60].sqltype = 460; sql_setdlist[60].sqllen = 9;
#line 715 "AD103_db.sqc"
      sql_setdlist[60].sqldata = (void*)hkanjya.hkkkbdh;
#line 715 "AD103_db.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[61].sqltype = 460; sql_setdlist[61].sqllen = 4;
#line 715 "AD103_db.sqc"
      sql_setdlist[61].sqldata = (void*)hkanjya.ecd;
#line 715 "AD103_db.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[62].sqltype = 460; sql_setdlist[62].sqllen = 3;
#line 715 "AD103_db.sqc"
      sql_setdlist[62].sqldata = (void*)hkanjya.shcd;
#line 715 "AD103_db.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[63].sqltype = 460; sql_setdlist[63].sqllen = 41;
#line 715 "AD103_db.sqc"
      sql_setdlist[63].sqldata = (void*)hkanjya.sstssnmj;
#line 715 "AD103_db.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sqlasetdata(3,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[25];
#line 715 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 41;
#line 715 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.sstssnmn;
#line 715 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 715 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.sstrsj;
#line 715 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 715 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkanjya.sstrsn;
#line 715 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 715 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)hkanjya.sstsbt;
#line 715 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkanjya.ttsstflg;
#line 715 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 715 "AD103_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkanjya.rucd;
#line 715 "AD103_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[6].sqldata = (void*)&hkanjya.irikmksu;
#line 715 "AD103_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 715 "AD103_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkanjya.bmskn;
#line 715 "AD103_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 3;
#line 715 "AD103_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkanjya.irinrsbt;
#line 715 "AD103_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[9].sqldata = (void*)hkanjya.irihsmkbn;
#line 715 "AD103_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[10].sqldata = (void*)hkanjya.caresstflg;
#line 715 "AD103_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[11].sqldata = (void*)hkanjya.tktyflg;
#line 715 "AD103_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 14;
#line 715 "AD103_db.sqc"
      sql_setdlist[12].sqldata = (void*)hkanjya.apkntino;
#line 715 "AD103_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 715 "AD103_db.sqc"
      sql_setdlist[13].sqldata = (void*)hkanjya.sdnm;
#line 715 "AD103_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 21;
#line 715 "AD103_db.sqc"
      sql_setdlist[14].sqldata = (void*)hkanjya.bko1;
#line 715 "AD103_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 21;
#line 715 "AD103_db.sqc"
      sql_setdlist[15].sqldata = (void*)hkanjya.bko2;
#line 715 "AD103_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 21;
#line 715 "AD103_db.sqc"
      sql_setdlist[16].sqldata = (void*)hkanjya.bko3;
#line 715 "AD103_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 715 "AD103_db.sqc"
      sql_setdlist[17].sqldata = (void*)hkanjya.zstrdh;
#line 715 "AD103_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 715 "AD103_db.sqc"
      sql_setdlist[18].sqldata = (void*)hkanjya.zsssdh;
#line 715 "AD103_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 715 "AD103_db.sqc"
      sql_setdlist[19].sqldata = (void*)hkanjya.stlzsssdh;
#line 715 "AD103_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 16;
#line 715 "AD103_db.sqc"
      sql_setdlist[20].sqldata = (void*)hkanjya.stlzsssip;
#line 715 "AD103_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 9;
#line 715 "AD103_db.sqc"
      sql_setdlist[21].sqldata = (void*)hkanjya.stlzssssyaid;
#line 715 "AD103_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 27;
#line 715 "AD103_db.sqc"
      sql_setdlist[22].sqldata = (void*)hkanjya.ksndh;
#line 715 "AD103_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 715 "AD103_db.sqc"
      sql_setdlist[23].sqldata = (void*)hkanjya.oyasstcd;
#line 715 "AD103_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 27;
#line 715 "AD103_db.sqc"
      sql_setdlist[24].sqldata = (void*)hkanjya.trkdh;
#line 715 "AD103_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sqlasetdata(3,64,25,sql_setdlist,0L,0L);
    }
#line 715 "AD103_db.sqc"
  sqlacall((unsigned short)24,6,2,3,0L);
#line 715 "AD103_db.sqc"
  sqlastop(0L);
}

#line 715 "AD103_db.sqc"


	/* SQLCODE */
	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "SELECT * FROM kanjya before update: "
		"utkymd[%s]irino[%s]zssdino[%d]",
		kan->utkymd, kan->irino, kan->zssdino );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if ( sqlca.sqlcode == 0 ) {		/* OK */
		// 更新前情報のLOG出力
		EditCsvKanjya( &hkanjya );
		LogOut( LT_TRC, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
	} else {
		if ( sqlca.sqlcode == 100 ){	/* NOT FOUND */
			/* SQLCODE +100, SQLSTATE '02000' */
			sprintf( G_msg, "更新対象の患者情報(kanjya)が存在しません。" );
			// NOT FOUND
			ret=RTN_ZERO;
		} else {
			/* SQLCODE > 0 -> WARNING */
			/* SQLCODE < 0 -> ERROR */
			sprintf( G_msg, "更新対象の患者情報(kanjya) SELECT で"
				"不具合が発生しました。" );
			ret=RTN_DBERR;
		}
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
	}
	/* ホスト変数セット	*/
		// 1.01 ADD 登録日時は更新前の値を引き継ぐ
	strcpy( wbuf,			hkanjya.trkdh );
	memcpy( &hkanjya, kan,	sizeof( struct _KANJYA ));
	strcpy( hkanjya.trkdh,	wbuf );				// 1.01 ADD
	if( stcPRM.myp_debug == 1 ){
		zoku_pr( &hkanjya );
	}

// ----- UPDATE ------------------------------------------------------------

/*
EXEC SQL UPDATE	kanjya	
	SET	  iriketflg	= :hkanjya.iriketflg
		, sstcd		= :hkanjya.sstcd
		, subsstcd	= :hkanjya.subsstcd
		, cdkbn1	= :hkanjya.cdkbn1
		, cdkbn2	= :hkanjya.cdkbn2
		, irimkey	= :hkanjya.irimkey
		, srkcd		= :hkanjya.srkcd
		, srknm		= :hkanjya.srknm
		, tticd		= :hkanjya.tticd
		, ttinm		= :hkanjya.ttinm
		, gpcd		= :hkanjya.gpcd
		, gpnm		= :hkanjya.gpnm
		, skicd		= :hkanjya.skicd
		, skinm		= :hkanjya.skinm
		, krtno		= :hkanjya.krtno
		, knjid		= :hkanjya.knjid
		, knjnmn	= :hkanjya.knjnmn
		, knjnmk	= :hkanjya.knjnmk
		, knjnmkey	= :hkanjya.knjnmkey
		, sc		= :hkanjya.sc
		, tj		= :hkanjya.tj
		, tjtni		= :hkanjya.tjtni
		, sbtkbn	= :hkanjya.sbtkbn
		, birthday	= :hkanjya.birthday
		, birthdaykbn	= :hkanjya.birthdaykbn
		, age		= :hkanjya.age
		, agekbn	= :hkanjya.agekbn
		, btcd		= :hkanjya.btcd
		, btnm		= :hkanjya.btnm
		, utkcmtcd1	= :hkanjya.utkcmtcd1
		, utkcmtcd2	= :hkanjya.utkcmtcd2
		, utkcmtcd3	= :hkanjya.utkcmtcd3
		, utkcmtfr1	= :hkanjya.utkcmtfr1
		, utkcmtfr2	= :hkanjya.utkcmtfr2
		, utkcmtfrflg	= :hkanjya.utkcmtfrflg
		, ngkbn		= :hkanjya.ngkbn
		, nsssu		= :hkanjya.nsssu
		, hkncd		= :hkanjya.hkncd
		, ktshsu	= :hkanjya.ktshsu
		, iniriymd	= :hkanjya.iniriymd
		, zssflg	= :hkanjya.zssflg
		, kkiriflg	= :hkanjya.kkiriflg
		, hknskbn	= :hkanjya.hknskbn
		, utkkbn	= :hkanjya.utkkbn
		, nekbn		= :hkanjya.nekbn
		, inknskbn	= :hkanjya.inknskbn
		, utkjkkbn	= :hkanjya.utkjkkbn
		, krflg		= :hkanjya.krflg
		, fdhhkkflg	= :hkanjya.fdhhkkflg
		, utkdh		= :hkanjya.utkdh
		, mutkymd	= :hkanjya.mutkymd
		, mirino	= :hkanjya.mirino
		, knsjslbcd1= :hkanjya.knsjslbcd1
		, knsjslbcd2= :hkanjya.knsjslbcd2
		, knsjslbcd3= :hkanjya.knsjslbcd3
		, knsjslbcd4= :hkanjya.knsjslbcd4
		, ymhkkflg	= :hkanjya.ymhkkflg
		, hkkkbdh	= :hkanjya.hkkkbdh
		, ecd		= :hkanjya.ecd
		, shcd		= :hkanjya.shcd
		, sstssnmj	= :hkanjya.sstssnmj
		, sstssnmn	= :hkanjya.sstssnmn
		, sstrsj	= :hkanjya.sstrsj
		, sstrsn	= :hkanjya.sstrsn
		, sstsbt	= :hkanjya.sstsbt
		, ttsstflg	= :hkanjya.ttsstflg
		, rucd		= :hkanjya.rucd
		, irikmksu	= :hkanjya.irikmksu
		, bmskn		= :hkanjya.bmskn
		, irinrsbt	= :hkanjya.irinrsbt
		, irihsmkbn	= :hkanjya.irihsmkbn
		, caresstflg= :hkanjya.caresstflg
		, tktyflg	= :hkanjya.tktyflg
		, apkntino	= :hkanjya.apkntino
		, sdnm		= :hkanjya.sdnm
		, bko1		= :hkanjya.bko1
		, bko2		= :hkanjya.bko2
		, bko3		= :hkanjya.bko3
		, zstrdh	= :hkanjya.zstrdh
		, zsssdh	= :hkanjya.zsssdh
		, stlzsssdh	= :hkanjya.stlzsssdh
		, stlzsssip	= :hkanjya.stlzsssip
		, stlzssssyaid= :hkanjya.stlzssssyaid
		, ksndh		= CURRENT TIMESTAMP
		, oyasstcd	= :hkanjya.oyasstcd			-- 1.01 ADD
		, trkdh		= :hkanjya.trkdh			-- 1.01 ADD
	WHERE	utkymd	= :hkanjya.utkymd
	AND		irino	= :hkanjya.irino
	AND		zssdino	= :hkanjya.zssdino
	;
*/

{
#line 849 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 849 "AD103_db.sqc"
  sqlaaloc(2,88,10,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 849 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.iriketflg;
#line 849 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 849 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.sstcd;
#line 849 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 849 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkanjya.subsstcd;
#line 849 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 849 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)hkanjya.cdkbn1;
#line 849 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 3;
#line 849 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkanjya.cdkbn2;
#line 849 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 41;
#line 849 "AD103_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkanjya.irimkey;
#line 849 "AD103_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 4;
#line 849 "AD103_db.sqc"
      sql_setdlist[6].sqldata = (void*)hkanjya.srkcd;
#line 849 "AD103_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 31;
#line 849 "AD103_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkanjya.srknm;
#line 849 "AD103_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 849 "AD103_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkanjya.tticd;
#line 849 "AD103_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 41;
#line 849 "AD103_db.sqc"
      sql_setdlist[9].sqldata = (void*)hkanjya.ttinm;
#line 849 "AD103_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 9;
#line 849 "AD103_db.sqc"
      sql_setdlist[10].sqldata = (void*)hkanjya.gpcd;
#line 849 "AD103_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 41;
#line 849 "AD103_db.sqc"
      sql_setdlist[11].sqldata = (void*)hkanjya.gpnm;
#line 849 "AD103_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 849 "AD103_db.sqc"
      sql_setdlist[12].sqldata = (void*)hkanjya.skicd;
#line 849 "AD103_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 41;
#line 849 "AD103_db.sqc"
      sql_setdlist[13].sqldata = (void*)hkanjya.skinm;
#line 849 "AD103_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 41;
#line 849 "AD103_db.sqc"
      sql_setdlist[14].sqldata = (void*)hkanjya.krtno;
#line 849 "AD103_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 16;
#line 849 "AD103_db.sqc"
      sql_setdlist[15].sqldata = (void*)hkanjya.knjid;
#line 849 "AD103_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 61;
#line 849 "AD103_db.sqc"
      sql_setdlist[16].sqldata = (void*)hkanjya.knjnmn;
#line 849 "AD103_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 31;
#line 849 "AD103_db.sqc"
      sql_setdlist[17].sqldata = (void*)hkanjya.knjnmk;
#line 849 "AD103_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 61;
#line 849 "AD103_db.sqc"
      sql_setdlist[18].sqldata = (void*)hkanjya.knjnmkey;
#line 849 "AD103_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 6;
#line 849 "AD103_db.sqc"
      sql_setdlist[19].sqldata = (void*)hkanjya.sc;
#line 849 "AD103_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 6;
#line 849 "AD103_db.sqc"
      sql_setdlist[20].sqldata = (void*)hkanjya.tj;
#line 849 "AD103_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[21].sqldata = (void*)hkanjya.tjtni;
#line 849 "AD103_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[22].sqldata = (void*)hkanjya.sbtkbn;
#line 849 "AD103_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 9;
#line 849 "AD103_db.sqc"
      sql_setdlist[23].sqldata = (void*)hkanjya.birthday;
#line 849 "AD103_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[24].sqldata = (void*)hkanjya.birthdaykbn;
#line 849 "AD103_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 4;
#line 849 "AD103_db.sqc"
      sql_setdlist[25].sqldata = (void*)hkanjya.age;
#line 849 "AD103_db.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[26].sqldata = (void*)hkanjya.agekbn;
#line 849 "AD103_db.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 11;
#line 849 "AD103_db.sqc"
      sql_setdlist[27].sqldata = (void*)hkanjya.btcd;
#line 849 "AD103_db.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 31;
#line 849 "AD103_db.sqc"
      sql_setdlist[28].sqldata = (void*)hkanjya.btnm;
#line 849 "AD103_db.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 3;
#line 849 "AD103_db.sqc"
      sql_setdlist[29].sqldata = (void*)hkanjya.utkcmtcd1;
#line 849 "AD103_db.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 3;
#line 849 "AD103_db.sqc"
      sql_setdlist[30].sqldata = (void*)hkanjya.utkcmtcd2;
#line 849 "AD103_db.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 3;
#line 849 "AD103_db.sqc"
      sql_setdlist[31].sqldata = (void*)hkanjya.utkcmtcd3;
#line 849 "AD103_db.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 71;
#line 849 "AD103_db.sqc"
      sql_setdlist[32].sqldata = (void*)hkanjya.utkcmtfr1;
#line 849 "AD103_db.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 71;
#line 849 "AD103_db.sqc"
      sql_setdlist[33].sqldata = (void*)hkanjya.utkcmtfr2;
#line 849 "AD103_db.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[34].sqldata = (void*)hkanjya.utkcmtfrflg;
#line 849 "AD103_db.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[35].sqldata = (void*)hkanjya.ngkbn;
#line 849 "AD103_db.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 3;
#line 849 "AD103_db.sqc"
      sql_setdlist[36].sqldata = (void*)hkanjya.nsssu;
#line 849 "AD103_db.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[37].sqldata = (void*)hkanjya.hkncd;
#line 849 "AD103_db.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 3;
#line 849 "AD103_db.sqc"
      sql_setdlist[38].sqldata = (void*)hkanjya.ktshsu;
#line 849 "AD103_db.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 11;
#line 849 "AD103_db.sqc"
      sql_setdlist[39].sqldata = (void*)hkanjya.iniriymd;
#line 849 "AD103_db.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[40].sqldata = (void*)hkanjya.zssflg;
#line 849 "AD103_db.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[41].sqldata = (void*)hkanjya.kkiriflg;
#line 849 "AD103_db.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[42].sqldata = (void*)hkanjya.hknskbn;
#line 849 "AD103_db.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[43].sqldata = (void*)hkanjya.utkkbn;
#line 849 "AD103_db.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[44].sqldata = (void*)hkanjya.nekbn;
#line 849 "AD103_db.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[45].sqldata = (void*)hkanjya.inknskbn;
#line 849 "AD103_db.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[46].sqldata = (void*)hkanjya.utkjkkbn;
#line 849 "AD103_db.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[47].sqldata = (void*)hkanjya.krflg;
#line 849 "AD103_db.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[48].sqldata = (void*)hkanjya.fdhhkkflg;
#line 849 "AD103_db.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 9;
#line 849 "AD103_db.sqc"
      sql_setdlist[49].sqldata = (void*)hkanjya.utkdh;
#line 849 "AD103_db.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 11;
#line 849 "AD103_db.sqc"
      sql_setdlist[50].sqldata = (void*)hkanjya.mutkymd;
#line 849 "AD103_db.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 12;
#line 849 "AD103_db.sqc"
      sql_setdlist[51].sqldata = (void*)hkanjya.mirino;
#line 849 "AD103_db.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 4;
#line 849 "AD103_db.sqc"
      sql_setdlist[52].sqldata = (void*)hkanjya.knsjslbcd1;
#line 849 "AD103_db.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 4;
#line 849 "AD103_db.sqc"
      sql_setdlist[53].sqldata = (void*)hkanjya.knsjslbcd2;
#line 849 "AD103_db.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 4;
#line 849 "AD103_db.sqc"
      sql_setdlist[54].sqldata = (void*)hkanjya.knsjslbcd3;
#line 849 "AD103_db.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 849 "AD103_db.sqc"
      sql_setdlist[55].sqldata = (void*)hkanjya.knsjslbcd4;
#line 849 "AD103_db.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[56].sqldata = (void*)hkanjya.ymhkkflg;
#line 849 "AD103_db.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 9;
#line 849 "AD103_db.sqc"
      sql_setdlist[57].sqldata = (void*)hkanjya.hkkkbdh;
#line 849 "AD103_db.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[58].sqltype = 460; sql_setdlist[58].sqllen = 4;
#line 849 "AD103_db.sqc"
      sql_setdlist[58].sqldata = (void*)hkanjya.ecd;
#line 849 "AD103_db.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[59].sqltype = 460; sql_setdlist[59].sqllen = 3;
#line 849 "AD103_db.sqc"
      sql_setdlist[59].sqldata = (void*)hkanjya.shcd;
#line 849 "AD103_db.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[60].sqltype = 460; sql_setdlist[60].sqllen = 41;
#line 849 "AD103_db.sqc"
      sql_setdlist[60].sqldata = (void*)hkanjya.sstssnmj;
#line 849 "AD103_db.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[61].sqltype = 460; sql_setdlist[61].sqllen = 41;
#line 849 "AD103_db.sqc"
      sql_setdlist[61].sqldata = (void*)hkanjya.sstssnmn;
#line 849 "AD103_db.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[62].sqltype = 460; sql_setdlist[62].sqllen = 21;
#line 849 "AD103_db.sqc"
      sql_setdlist[62].sqldata = (void*)hkanjya.sstrsj;
#line 849 "AD103_db.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[63].sqltype = 460; sql_setdlist[63].sqllen = 21;
#line 849 "AD103_db.sqc"
      sql_setdlist[63].sqldata = (void*)hkanjya.sstrsn;
#line 849 "AD103_db.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sqlasetdata(2,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[24];
#line 849 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 849 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.sstsbt;
#line 849 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.ttsstflg;
#line 849 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 849 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkanjya.rucd;
#line 849 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)&hkanjya.irikmksu;
#line 849 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 51;
#line 849 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkanjya.bmskn;
#line 849 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 849 "AD103_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkanjya.irinrsbt;
#line 849 "AD103_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[6].sqldata = (void*)hkanjya.irihsmkbn;
#line 849 "AD103_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkanjya.caresstflg;
#line 849 "AD103_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkanjya.tktyflg;
#line 849 "AD103_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 14;
#line 849 "AD103_db.sqc"
      sql_setdlist[9].sqldata = (void*)hkanjya.apkntino;
#line 849 "AD103_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 21;
#line 849 "AD103_db.sqc"
      sql_setdlist[10].sqldata = (void*)hkanjya.sdnm;
#line 849 "AD103_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 21;
#line 849 "AD103_db.sqc"
      sql_setdlist[11].sqldata = (void*)hkanjya.bko1;
#line 849 "AD103_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 21;
#line 849 "AD103_db.sqc"
      sql_setdlist[12].sqldata = (void*)hkanjya.bko2;
#line 849 "AD103_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 849 "AD103_db.sqc"
      sql_setdlist[13].sqldata = (void*)hkanjya.bko3;
#line 849 "AD103_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 27;
#line 849 "AD103_db.sqc"
      sql_setdlist[14].sqldata = (void*)hkanjya.zstrdh;
#line 849 "AD103_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 849 "AD103_db.sqc"
      sql_setdlist[15].sqldata = (void*)hkanjya.zsssdh;
#line 849 "AD103_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 27;
#line 849 "AD103_db.sqc"
      sql_setdlist[16].sqldata = (void*)hkanjya.stlzsssdh;
#line 849 "AD103_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 16;
#line 849 "AD103_db.sqc"
      sql_setdlist[17].sqldata = (void*)hkanjya.stlzsssip;
#line 849 "AD103_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 9;
#line 849 "AD103_db.sqc"
      sql_setdlist[18].sqldata = (void*)hkanjya.stlzssssyaid;
#line 849 "AD103_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 8;
#line 849 "AD103_db.sqc"
      sql_setdlist[19].sqldata = (void*)hkanjya.oyasstcd;
#line 849 "AD103_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 27;
#line 849 "AD103_db.sqc"
      sql_setdlist[20].sqldata = (void*)hkanjya.trkdh;
#line 849 "AD103_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 11;
#line 849 "AD103_db.sqc"
      sql_setdlist[21].sqldata = (void*)hkanjya.utkymd;
#line 849 "AD103_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 12;
#line 849 "AD103_db.sqc"
      sql_setdlist[22].sqldata = (void*)hkanjya.irino;
#line 849 "AD103_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[23].sqltype = 500; sql_setdlist[23].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[23].sqldata = (void*)&hkanjya.zssdino;
#line 849 "AD103_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sqlasetdata(2,64,24,sql_setdlist,0L,0L);
    }
#line 849 "AD103_db.sqc"
  sqlacall((unsigned short)24,7,2,0,0L);
#line 849 "AD103_db.sqc"
  sqlastop(0L);
}

#line 849 "AD103_db.sqc"


	/* SQLCODE */
	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "UPDATE kanjya kinkyu : "
		"utkymd[%s]irino[%s]zssdino[%d]",
		kan->utkymd, kan->irino, kan->zssdino );
	LogOut( LT_DBG, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if (sqlca.sqlcode == 0) {		/* OK */
		ret = RTN_OK;
	} else {
        if( sqlca.sqlcode == -911 ){        // LOCK
            switch( sqlca.sqlerrd[2] ){
            case     2 :
                strcpy( G_msg, "AS400後日依頼情報対応の患者情報(kanjya)の "
					"UPDATE で DEAD LOCK が発生しました。" );
                break;
            case    68 :
                strcpy( G_msg, "AS400後日依頼情報対応の患者情報(kanjya)の "
                    "UPDATE で TIMETOUT が発生しました。" );
                break;
            default :
                strcpy( G_msg, "AS400後日依頼情報対応の患者情報(kanjya)の "
                    "不具合が発生しました。" );
                break;
            }
		} else {
			/* SQLCODE > 0 -> WARNING */
			/* SQLCODE < 0 -> ERROR */
			sprintf( G_msg,
			"AS400後日依頼情報対応の患者情報(kanjya)の UPDATE に失敗しました。"
				"BML受付年月日[%s]依頼書NO[%s]属性世代NO[%d]"
				,kan->utkymd, kan->irino, kan->zssdino );
		}
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		ret=RTN_DBERR;
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  関 数 名  ：InsChikenzok                                                  */
/*  機能概要  ：治験拡張　INSERT                                              */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  _CHIKENZOK     *try;   : ：治験拡張                   */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		InsChikenzok( try )
struct		_CHIKENZOK	*try;			/* 属性データ */
{
	struct	sqlca	sqlca;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/
	int	ret;

	/* 初期処理	*/
	strcpy(func_nm, "InsChikenzok" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ホスト変数へのセット	*/
	memcpy( &hchikenzok, try, sizeof( struct _CHIKENZOK ));
	strcpy( hchikenzok.ksndh, "2006/02/08 19:40:00" );


/*
EXEC SQL INSERT	INTO	chikenzok
		( utkymd
		, irino
		, iriketflg
		, zssdino
		, prtclno
		, kosstcd
		, tytme
		, tyryo
		, tyryotni
		, yzfktme
		, ikasflg
		, kntsu
		, kmksu
		, sspit
		, zrcd01
		, zrcd02
		, zrcd03
		, zrcd04
		, zrcd05
		, zrcd06
		, zrkg01
		, zrkg02
		, zrkg03
		, zrkg04
		, zrkg05
		, zrkg06
		, hrseq
		, kntksflg
		, gcpflg
		, prtclnm
		, ksndh
		)
	VALUES	( :hchikenzok.utkymd
		, :hchikenzok.irino
		, :hchikenzok.iriketflg
		, :hchikenzok.zssdino
		, :hchikenzok.prtclno
		, :hchikenzok.kosstcd
		, :hchikenzok.tytme
		, :hchikenzok.tyryo
		, :hchikenzok.tyryotni
		, :hchikenzok.yzfktme
		, :hchikenzok.ikasflg
		, :hchikenzok.kntsu
		, :hchikenzok.kmksu
		, :hchikenzok.sspit
		, :hchikenzok.zrcd01
		, :hchikenzok.zrcd02
		, :hchikenzok.zrcd03
		, :hchikenzok.zrcd04
		, :hchikenzok.zrcd05
		, :hchikenzok.zrcd06
		, :hchikenzok.zrkg01
		, :hchikenzok.zrkg02
		, :hchikenzok.zrkg03
		, :hchikenzok.zrkg04
		, :hchikenzok.zrkg05
		, :hchikenzok.zrkg06
		, :hchikenzok.hrseq
		, :hchikenzok.kntksflg
		, :hchikenzok.gcpflg
		, :hchikenzok.prtclnm
		, CURRENT TIMESTAMP
		)
	;
*/

{
#line 986 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 986 "AD103_db.sqc"
  sqlaaloc(2,30,11,0L);
    {
      struct sqla_setdata_list sql_setdlist[30];
#line 986 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 986 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hchikenzok.utkymd;
#line 986 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 986 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hchikenzok.irino;
#line 986 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 986 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hchikenzok.iriketflg;
#line 986 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 986 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)&hchikenzok.zssdino;
#line 986 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 12;
#line 986 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)hchikenzok.prtclno;
#line 986 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 986 "AD103_db.sqc"
      sql_setdlist[5].sqldata = (void*)hchikenzok.kosstcd;
#line 986 "AD103_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 5;
#line 986 "AD103_db.sqc"
      sql_setdlist[6].sqldata = (void*)hchikenzok.tytme;
#line 986 "AD103_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 6;
#line 986 "AD103_db.sqc"
      sql_setdlist[7].sqldata = (void*)hchikenzok.tyryo;
#line 986 "AD103_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 986 "AD103_db.sqc"
      sql_setdlist[8].sqldata = (void*)hchikenzok.tyryotni;
#line 986 "AD103_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 5;
#line 986 "AD103_db.sqc"
      sql_setdlist[9].sqldata = (void*)hchikenzok.yzfktme;
#line 986 "AD103_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 2;
#line 986 "AD103_db.sqc"
      sql_setdlist[10].sqldata = (void*)hchikenzok.ikasflg;
#line 986 "AD103_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 986 "AD103_db.sqc"
      sql_setdlist[11].sqldata = (void*)&hchikenzok.kntsu;
#line 986 "AD103_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 986 "AD103_db.sqc"
      sql_setdlist[12].sqldata = (void*)&hchikenzok.kmksu;
#line 986 "AD103_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 3;
#line 986 "AD103_db.sqc"
      sql_setdlist[13].sqldata = (void*)hchikenzok.sspit;
#line 986 "AD103_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 6;
#line 986 "AD103_db.sqc"
      sql_setdlist[14].sqldata = (void*)hchikenzok.zrcd01;
#line 986 "AD103_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 6;
#line 986 "AD103_db.sqc"
      sql_setdlist[15].sqldata = (void*)hchikenzok.zrcd02;
#line 986 "AD103_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 6;
#line 986 "AD103_db.sqc"
      sql_setdlist[16].sqldata = (void*)hchikenzok.zrcd03;
#line 986 "AD103_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 6;
#line 986 "AD103_db.sqc"
      sql_setdlist[17].sqldata = (void*)hchikenzok.zrcd04;
#line 986 "AD103_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 6;
#line 986 "AD103_db.sqc"
      sql_setdlist[18].sqldata = (void*)hchikenzok.zrcd05;
#line 986 "AD103_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 6;
#line 986 "AD103_db.sqc"
      sql_setdlist[19].sqldata = (void*)hchikenzok.zrcd06;
#line 986 "AD103_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 3;
#line 986 "AD103_db.sqc"
      sql_setdlist[20].sqldata = (void*)hchikenzok.zrkg01;
#line 986 "AD103_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 3;
#line 986 "AD103_db.sqc"
      sql_setdlist[21].sqldata = (void*)hchikenzok.zrkg02;
#line 986 "AD103_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 3;
#line 986 "AD103_db.sqc"
      sql_setdlist[22].sqldata = (void*)hchikenzok.zrkg03;
#line 986 "AD103_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 3;
#line 986 "AD103_db.sqc"
      sql_setdlist[23].sqldata = (void*)hchikenzok.zrkg04;
#line 986 "AD103_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 3;
#line 986 "AD103_db.sqc"
      sql_setdlist[24].sqldata = (void*)hchikenzok.zrkg05;
#line 986 "AD103_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 3;
#line 986 "AD103_db.sqc"
      sql_setdlist[25].sqldata = (void*)hchikenzok.zrkg06;
#line 986 "AD103_db.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 5;
#line 986 "AD103_db.sqc"
      sql_setdlist[26].sqldata = (void*)hchikenzok.hrseq;
#line 986 "AD103_db.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 2;
#line 986 "AD103_db.sqc"
      sql_setdlist[27].sqldata = (void*)hchikenzok.kntksflg;
#line 986 "AD103_db.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 2;
#line 986 "AD103_db.sqc"
      sql_setdlist[28].sqldata = (void*)hchikenzok.gcpflg;
#line 986 "AD103_db.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 41;
#line 986 "AD103_db.sqc"
      sql_setdlist[29].sqldata = (void*)hchikenzok.prtclnm;
#line 986 "AD103_db.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sqlasetdata(2,0,30,sql_setdlist,0L,0L);
    }
#line 986 "AD103_db.sqc"
  sqlacall((unsigned short)24,8,2,0,0L);
#line 986 "AD103_db.sqc"
  sqlastop(0L);
}

#line 986 "AD103_db.sqc"


	/* SQLCODE */
	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "INSERT chikenzok : utkymd[%s]irino[%s]zssdino[%d]",
		try->utkymd, try->irino, try->zssdino );
	LogOut( LT_DBG, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if (sqlca.sqlcode == 0) {		/* OK */
		ret = RTN_OK;
	} else {
		if ( sqlca.sqlcode == -803 ) {	// duplicate
			sprintf( G_msg,
				"治験拡張属性(chikenzok)は既に存在しています。"
				"BML受付年月日[%s]依頼書NO[%s]属性世代NO[%d]"
				,try->utkymd, try->irino, try->zssdino );
			ret=RTN_NG;
		} else {
			sprintf( G_msg,
				"治験拡張属性(chikenzok)の INSERT に失敗しました。"
				"BML受付年月日[%s]依頼書NO[%s]属性世代NO[%d]"
				,try->utkymd, try->irino, try->zssdino );
			ret=RTN_DBERR;
		}
		// ERROR
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__ );
	}

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  関 数 名  ：SelKinkyuIrai                                                 */
/*  機能概要  ：AS/400からの依頼項目が存在するかチェックする                  */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  _KANJYA    *kan;   : 患者情報                         */
/*  出    力  ：                                                              */
/*  復帰情報  ：COUNT結果    正常終了                                         */
/*            ：0 未満       異常終了                                         */
/******************************************************************************/
int		SelKinkyuIrai( kan )
struct		_KANJYA		*kan;			// 患者情報
{
	int		ret;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/
	struct	sqlca	sqlca;

	/* 初期処理	*/
	strcpy( func_nm, "SelKinkyuIrai" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ホスト変数へのキー項目セット	*/
	strcpy( hst_utkymd,	kan->utkymd );
	strcpy( hst_irino,	kan->irino );
	hst_cnt=0;
	ind_cnt=0;

	// 削除フラグは考慮しない

/*
EXEC SQL SELECT	COUNT( irikbn )
	INTO	  :hst_cnt	INDICATOR :ind_cnt
	FROM	irai
	WHERE	utkymd	= :hst_utkymd
	AND		irino	= :hst_irino
	AND		irikbn	= 'K'
	;
*/

{
#line 1057 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1057 "AD103_db.sqc"
  sqlaaloc(2,2,12,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 1057 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1057 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hst_utkymd;
#line 1057 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1057 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1057 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_irino;
#line 1057 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1057 "AD103_db.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 1057 "AD103_db.sqc"
  sqlaaloc(3,1,13,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 1057 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 497; sql_setdlist[0].sqllen = 4;
#line 1057 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)&hst_cnt;
#line 1057 "AD103_db.sqc"
      sql_setdlist[0].sqlind = &ind_cnt;
#line 1057 "AD103_db.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 1057 "AD103_db.sqc"
  sqlacall((unsigned short)24,9,2,3,0L);
#line 1057 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1057 "AD103_db.sqc"


    /* not found --> SQLCODE = +100, SQLSTATE == '02000' */
	/* many rows --> ERROR!!         SQLSTATE == '21000' */

	/* SQLCODE */
	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "SELECT COUNT( irikbn ) FROM irai WHERE ___ irikbn='K' : "
		"utkymd[%s]irino[%s] indicator[%d] sqlcode[%s]",
		kan->utkymd, kan->irino, ind_cnt, G_err );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	// 標識変数による判断
	if( ind_cnt == 0 ) {
		// COUNT結果を返す（0もあり）
		ret = hst_cnt;
	} else {
		sprintf( G_msg,
			"AS400依頼項目情報(irai)取得に失敗しました。"
			"BML受付年月日[%s]依頼書NO[%s] SELECT INDICATOR[%d]"
			,kan->utkymd, kan->irino, ind_cnt );
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

/******************************************************************************/
/*  関 数 名  ：UpdIraiZssdino                                                */
/*  機能概要  ：属性修正対象に紐づく依頼情報.世代No更新(オーダ未作成のみ)     */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  _KANJYA    *kan;   : 患者情報                         */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		UpdIraiZssdino( kan )
struct		_KANJYA		*kan;			/* 患者情報 */
{

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 1108 "AD103_db.sqc"

	char		hst_kmkcd[7+1];
	char		hst_smpcd[7+1];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 1111 "AD103_db.sqc"

	int		ret;
	int		i;
	char	func_nm[30];				/* 関数名称	*/
	char	wbuf[30];
	struct	sqlca	sqlca;

	/* 初期処理	*/
	strcpy( func_nm, "UpdIraiZssdino" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ホスト変数へのキー項目セット	*/
	strcpy( hst_utkymd,	kan->utkymd );
	strcpy( hst_irino,	kan->irino );
	hst_zssdino = kan->zssdino;
	hst_cnt=0;
	ind_cnt=0;
	hkanjya.zssdino = kan->zssdino;

	// オーダ未作成の依頼情報の存在チェック

/*
EXEC SQL SELECT	COUNT( zssdino )
	INTO	  :hst_cnt	INDICATOR :ind_cnt
	FROM	irai
	WHERE	utkymd	= :hst_utkymd
	AND		irino	= :hst_irino
--	AND		knsgrp  = ' '			// 依頼展開での検査G付加に伴い条件外
	AND		odrssflg= ' '
	;
*/

{
#line 1138 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1138 "AD103_db.sqc"
  sqlaaloc(2,2,14,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 1138 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1138 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hst_utkymd;
#line 1138 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1138 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1138 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_irino;
#line 1138 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1138 "AD103_db.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 1138 "AD103_db.sqc"
  sqlaaloc(3,1,15,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 1138 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 497; sql_setdlist[0].sqllen = 4;
#line 1138 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)&hst_cnt;
#line 1138 "AD103_db.sqc"
      sql_setdlist[0].sqlind = &ind_cnt;
#line 1138 "AD103_db.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 1138 "AD103_db.sqc"
  sqlacall((unsigned short)24,10,2,3,0L);
#line 1138 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1138 "AD103_db.sqc"


	/* SQLCODE */
	// edit sqlcacode for LogOut errcode
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "SELECT COUNT( zssdino ) FROM irai WHERE _ odrssflg=' ' : "
		"utkymd[%s]irino[%s] indicator[%d] sqlcod[%s]",
		kan->utkymd, kan->irino, ind_cnt, G_err );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if( sqlca.sqlcode == 0 ) {
		// 件数による判断
		if( hst_cnt == 0 ){
			// 該当無し
			return( RTN_OK );
		}
    } else {
		sprintf( G_msg,
			"患者属性更新対象依頼項目情報(irai)取得に失敗しました。"
			"BML受付年月日[%s]依頼書NO[%s] SELECT INDICATOR[%d]"
			,kan->utkymd, kan->irino, ind_cnt );
		EditCsvMsg( G_msg );
		LogOut( LT_TRC, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		return( RTN_NG );
	}
	// 更新対象存在
// ----- UPDATE  ------------------------------------------------------------


/*
EXEC SQL DECLARE    iri_cur CURSOR  FOR
    SELECT  zssdino
            , kmkcd
            , smpcd
	FROM	irai
	WHERE	utkymd	= :hst_utkymd
	AND		irino	= :hst_irino
--	AND		knsgrp  = ' '				// 依頼展開での検査G付加に伴い条件外
	AND		odrssflg= ' '
	FOR UPDATE
	;
*/

#line 1178 "AD103_db.sqc"


/*
EXEC SQL OPEN iri_cur;
*/

{
#line 1179 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1179 "AD103_db.sqc"
  sqlaaloc(2,2,16,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 1179 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1179 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hst_utkymd;
#line 1179 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1179 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1179 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_irino;
#line 1179 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1179 "AD103_db.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 1179 "AD103_db.sqc"
  sqlacall((unsigned short)26,11,2,0,0L);
#line 1179 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1179 "AD103_db.sqc"


    i=0;

    while( sqlca.sqlcode == 0 ){
        
/*
EXEC SQL    FETCH   iri_cur
                    INTO      :hst_zssdino
                            , :hst_kmkcd
                            , :hst_smpcd
                    ;
*/

{
#line 1188 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1188 "AD103_db.sqc"
  sqlaaloc(3,3,17,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 1188 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 1188 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)&hst_zssdino;
#line 1188 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1188 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 1188 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_kmkcd;
#line 1188 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1188 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 1188 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hst_smpcd;
#line 1188 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1188 "AD103_db.sqc"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 1188 "AD103_db.sqc"
  sqlacall((unsigned short)25,11,0,3,0L);
#line 1188 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1188 "AD103_db.sqc"


		/* SQLCODE */
		// edit sqlcacode for LogOut errcode
		sprintf( G_err, "%d", sqlca.sqlcode );
		// DEBUG
		sprintf( G_msg, "FETCH irai zssdino : "
			"utkymd[%s]irino[%s]zssdino[%d]kmkcd[%s]smpcd[%s]"
			, hst_utkymd, hst_irino, hst_zssdino, hst_kmkcd, hst_smpcd );
		LogOut( LT_DBG, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		if (sqlca.sqlcode == 0) {		
			ret=RTN_OK;
		} else if (sqlca.sqlcode == 100) {		
			ret=RTN_OK;
			break;
		} else {
			/* SQLCODE > 0 -> WARNING */
			/* SQLCODE < 0 -> ERROR */
			sprintf( G_msg,
				"依頼情報(irai)のFETCH に失敗しました。"
				"受付日[%s]依頼書NO[%s]元世代No[%d]項目[%s]"
				, hst_utkymd, hst_irino, hst_zssdino, hst_kmkcd );
        	EditCsvMsg( G_msg );
			LogOut( LT_DBG, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
        	ret=RTN_DBERR;
			break;
       }

		
/*
EXEC SQL    UPDATE  irai
					SET     zssdino   = :hkanjya.zssdino
					WHERE	CURRENT OF iri_cur
					;
*/

{
#line 1220 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1220 "AD103_db.sqc"
  sqlaaloc(2,1,18,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 1220 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 500; sql_setdlist[0].sqllen = 2;
#line 1220 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)&hkanjya.zssdino;
#line 1220 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1220 "AD103_db.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 1220 "AD103_db.sqc"
  sqlacall((unsigned short)24,12,2,0,0L);
#line 1220 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1220 "AD103_db.sqc"

/* =================================================
            WHERE   utkymd  = :hst_utkymd
            AND     irino   = :hst_irino
			AND		zssdino	= :hst_zssdino
			AND		knsgrp  = ' '
			AND		kmkcd	= :hst_kmkcd
			AND		odrssflg= ' '
            ;
===================================================*/

		/* SQLCODE */
		// edit sqlcacode for LogOut errcode
		sprintf( G_err, "%d", sqlca.sqlcode );
		// DEBUG
		sprintf( G_msg, "UPDATE irai zssdino : "
			"utkymd[%s]irino[%s]zssdino[%d]kmkcd[%s]smpcd[%s]"
			, hst_utkymd, hst_irino, hst_zssdino, hst_kmkcd, hst_smpcd );
		LogOut( LT_DBG, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		if (sqlca.sqlcode == 0) {
			// TRACE
			sprintf( G_msg, "属性修正に合わせ依頼情報の世代Noを更新しました : "
				"受付日[%s]依頼書NO[%s]元世代No[%d]項目[%s]"
				, hst_utkymd, hst_irino, hst_zssdino, hst_kmkcd );
			ret=RTN_OK;
			EditCsvMsg( G_msg );
			LogOut( LT_TRC, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		} else {
			/* SQLCODE > 0 -> WARNING */
			/* SQLCODE < 0 -> ERROR */
			sprintf( G_msg,
				"依頼情報(irai)の属性世代No UPDATE に失敗しました。"
				"受付日[%s]依頼書NO[%s]元世代No[%d]項目[%s]"
				, hst_utkymd, hst_irino, hst_zssdino, hst_kmkcd );
        	ret=RTN_DBERR;
			EditCsvMsg( G_msg );
			LogOut( LT_ERR, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
       }
    }

/*
EXEC SQL CLOSE iri_cur;
*/

{
#line 1260 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1260 "AD103_db.sqc"
  sqlacall((unsigned short)20,11,0,0,0L);
#line 1260 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1260 "AD103_db.sqc"


	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/*  1.04     2009/06/29     Merits K.Ameno 障害管理No:0904031814/0904031719対応 --> */

/******************************************************************************/
/*  関 数 名  ：SelKanjya                                                     */
/*  機能概要  ：患者情報から同じ患者情報が既にあるかをチェックする            */
/*  入    力  ：                                                              */
/*  第１引数  ：struct  _KANJYA    *kan;   : 患者情報                         */
/*  出    力  ：取得出来ればSELECT結果をhkanjyaに格納して応答(RTN_OK)         */
/*            ：取得できなかったら、何も格納しない                            */
/*  復帰情報  ：RTN_OK       正常終了(取得成功)                               */
/*            ：RTN_ZERO     正常終了(該当レコードなし)                       */
/*            ：RTN_DBERR    異常終了(DBエラー発生)                           */
/******************************************************************************/
int		SelKanjya( kan )
struct		_KANJYA		*kan;							/* 患者情報 */
{
	int		ret;										/* 実行結果 */
	char	func_nm[30];								/* 関数名称	*/
	char	wbuf[30];									/* ワークバッファ */
	struct	sqlca	sqlca;								/* SQL実行コード */

	/* 初期処理	*/
	strcpy( func_nm, "SelKanjya" );						/* 実行関数名を設定 */
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
														/* LOG出力 */

	/* ホスト変数へのキー項目セット	*/
	memset( &hkanjya, '\0', sizeof( struct _KANJYA ));	/* 変数初期化 */
	strcpy( hkanjya.utkymd,	kan->utkymd );				/* 受け日を設定 */
	strcpy( hkanjya.irino,	kan->irino );				/* 依頼書Noを設定 */

/*----- SELECT ここから ------------------------------------------------------------*/
	/* 対象データ(受け日,依頼書No)のSELECT */
	/* 2016.04.18 ２件ヒットしてエラーとなる不具合に対する対応 */
	/* FETCH FIRST と ORDER BY を組み合わせて、属性修正フラグ 1 のレコードのみ SELECT 対象とする。*/

/*
EXEC SQL SELECT	* INTO
		  :hkanjya.utkymd
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
		, :hkanjya.ksndh
		, :hkanjya.oyasstcd
		, :hkanjya.trkdh
	FROM	KANJYA
	WHERE	utkymd	= :hkanjya.utkymd
	AND		irino	= :hkanjya.irino
	ORDER BY zssflg DESC, zssdino DESC
	FETCH FIRST 1 ROWS ONLY
	;
*/

{
#line 1396 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1396 "AD103_db.sqc"
  sqlaaloc(2,2,19,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 1396 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1396 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.utkymd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1396 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.irino;
#line 1396 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 1396 "AD103_db.sqc"
  sqlaaloc(3,89,20,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 1396 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1396 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.utkymd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1396 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.irino;
#line 1396 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkanjya.iriketflg;
#line 1396 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)&hkanjya.zssdino;
#line 1396 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 1396 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkanjya.sstcd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 5;
#line 1396 "AD103_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkanjya.subsstcd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[6].sqldata = (void*)hkanjya.cdkbn1;
#line 1396 "AD103_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkanjya.cdkbn2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 41;
#line 1396 "AD103_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkanjya.irimkey;
#line 1396 "AD103_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 4;
#line 1396 "AD103_db.sqc"
      sql_setdlist[9].sqldata = (void*)hkanjya.srkcd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 31;
#line 1396 "AD103_db.sqc"
      sql_setdlist[10].sqldata = (void*)hkanjya.srknm;
#line 1396 "AD103_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 1396 "AD103_db.sqc"
      sql_setdlist[11].sqldata = (void*)hkanjya.tticd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 41;
#line 1396 "AD103_db.sqc"
      sql_setdlist[12].sqldata = (void*)hkanjya.ttinm;
#line 1396 "AD103_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 1396 "AD103_db.sqc"
      sql_setdlist[13].sqldata = (void*)hkanjya.gpcd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 41;
#line 1396 "AD103_db.sqc"
      sql_setdlist[14].sqldata = (void*)hkanjya.gpnm;
#line 1396 "AD103_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 1396 "AD103_db.sqc"
      sql_setdlist[15].sqldata = (void*)hkanjya.skicd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 41;
#line 1396 "AD103_db.sqc"
      sql_setdlist[16].sqldata = (void*)hkanjya.skinm;
#line 1396 "AD103_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 41;
#line 1396 "AD103_db.sqc"
      sql_setdlist[17].sqldata = (void*)hkanjya.krtno;
#line 1396 "AD103_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 16;
#line 1396 "AD103_db.sqc"
      sql_setdlist[18].sqldata = (void*)hkanjya.knjid;
#line 1396 "AD103_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 61;
#line 1396 "AD103_db.sqc"
      sql_setdlist[19].sqldata = (void*)hkanjya.knjnmn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 31;
#line 1396 "AD103_db.sqc"
      sql_setdlist[20].sqldata = (void*)hkanjya.knjnmk;
#line 1396 "AD103_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 61;
#line 1396 "AD103_db.sqc"
      sql_setdlist[21].sqldata = (void*)hkanjya.knjnmkey;
#line 1396 "AD103_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 6;
#line 1396 "AD103_db.sqc"
      sql_setdlist[22].sqldata = (void*)hkanjya.sc;
#line 1396 "AD103_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 6;
#line 1396 "AD103_db.sqc"
      sql_setdlist[23].sqldata = (void*)hkanjya.tj;
#line 1396 "AD103_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[24].sqldata = (void*)hkanjya.tjtni;
#line 1396 "AD103_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[25].sqldata = (void*)hkanjya.sbtkbn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 9;
#line 1396 "AD103_db.sqc"
      sql_setdlist[26].sqldata = (void*)hkanjya.birthday;
#line 1396 "AD103_db.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[27].sqldata = (void*)hkanjya.birthdaykbn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 4;
#line 1396 "AD103_db.sqc"
      sql_setdlist[28].sqldata = (void*)hkanjya.age;
#line 1396 "AD103_db.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[29].sqldata = (void*)hkanjya.agekbn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 11;
#line 1396 "AD103_db.sqc"
      sql_setdlist[30].sqldata = (void*)hkanjya.btcd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 31;
#line 1396 "AD103_db.sqc"
      sql_setdlist[31].sqldata = (void*)hkanjya.btnm;
#line 1396 "AD103_db.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[32].sqldata = (void*)hkanjya.utkcmtcd1;
#line 1396 "AD103_db.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[33].sqldata = (void*)hkanjya.utkcmtcd2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[34].sqldata = (void*)hkanjya.utkcmtcd3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 71;
#line 1396 "AD103_db.sqc"
      sql_setdlist[35].sqldata = (void*)hkanjya.utkcmtfr1;
#line 1396 "AD103_db.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 71;
#line 1396 "AD103_db.sqc"
      sql_setdlist[36].sqldata = (void*)hkanjya.utkcmtfr2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[37].sqldata = (void*)hkanjya.utkcmtfrflg;
#line 1396 "AD103_db.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[38].sqldata = (void*)hkanjya.ngkbn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[39].sqldata = (void*)hkanjya.nsssu;
#line 1396 "AD103_db.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[40].sqldata = (void*)hkanjya.hkncd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[41].sqldata = (void*)hkanjya.ktshsu;
#line 1396 "AD103_db.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 11;
#line 1396 "AD103_db.sqc"
      sql_setdlist[42].sqldata = (void*)hkanjya.iniriymd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[43].sqldata = (void*)hkanjya.zssflg;
#line 1396 "AD103_db.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[44].sqldata = (void*)hkanjya.kkiriflg;
#line 1396 "AD103_db.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[45].sqldata = (void*)hkanjya.hknskbn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[46].sqldata = (void*)hkanjya.utkkbn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[47].sqldata = (void*)hkanjya.nekbn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[48].sqldata = (void*)hkanjya.inknskbn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[49].sqldata = (void*)hkanjya.utkjkkbn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[50].sqldata = (void*)hkanjya.krflg;
#line 1396 "AD103_db.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[51].sqldata = (void*)hkanjya.fdhhkkflg;
#line 1396 "AD103_db.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 9;
#line 1396 "AD103_db.sqc"
      sql_setdlist[52].sqldata = (void*)hkanjya.utkdh;
#line 1396 "AD103_db.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 11;
#line 1396 "AD103_db.sqc"
      sql_setdlist[53].sqldata = (void*)hkanjya.mutkymd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 12;
#line 1396 "AD103_db.sqc"
      sql_setdlist[54].sqldata = (void*)hkanjya.mirino;
#line 1396 "AD103_db.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 1396 "AD103_db.sqc"
      sql_setdlist[55].sqldata = (void*)hkanjya.knsjslbcd1;
#line 1396 "AD103_db.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 4;
#line 1396 "AD103_db.sqc"
      sql_setdlist[56].sqldata = (void*)hkanjya.knsjslbcd2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 4;
#line 1396 "AD103_db.sqc"
      sql_setdlist[57].sqldata = (void*)hkanjya.knsjslbcd3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[58].sqltype = 460; sql_setdlist[58].sqllen = 4;
#line 1396 "AD103_db.sqc"
      sql_setdlist[58].sqldata = (void*)hkanjya.knsjslbcd4;
#line 1396 "AD103_db.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[59].sqltype = 460; sql_setdlist[59].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[59].sqldata = (void*)hkanjya.ymhkkflg;
#line 1396 "AD103_db.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[60].sqltype = 460; sql_setdlist[60].sqllen = 9;
#line 1396 "AD103_db.sqc"
      sql_setdlist[60].sqldata = (void*)hkanjya.hkkkbdh;
#line 1396 "AD103_db.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[61].sqltype = 460; sql_setdlist[61].sqllen = 4;
#line 1396 "AD103_db.sqc"
      sql_setdlist[61].sqldata = (void*)hkanjya.ecd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[62].sqltype = 460; sql_setdlist[62].sqllen = 3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[62].sqldata = (void*)hkanjya.shcd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[63].sqltype = 460; sql_setdlist[63].sqllen = 41;
#line 1396 "AD103_db.sqc"
      sql_setdlist[63].sqldata = (void*)hkanjya.sstssnmj;
#line 1396 "AD103_db.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sqlasetdata(3,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[25];
#line 1396 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 41;
#line 1396 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.sstssnmn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 1396 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.sstrsj;
#line 1396 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 1396 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkanjya.sstrsn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)hkanjya.sstsbt;
#line 1396 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkanjya.ttsstflg;
#line 1396 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkanjya.rucd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[6].sqldata = (void*)&hkanjya.irikmksu;
#line 1396 "AD103_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 1396 "AD103_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkanjya.bmskn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkanjya.irinrsbt;
#line 1396 "AD103_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[9].sqldata = (void*)hkanjya.irihsmkbn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[10].sqldata = (void*)hkanjya.caresstflg;
#line 1396 "AD103_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[11].sqldata = (void*)hkanjya.tktyflg;
#line 1396 "AD103_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 14;
#line 1396 "AD103_db.sqc"
      sql_setdlist[12].sqldata = (void*)hkanjya.apkntino;
#line 1396 "AD103_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 1396 "AD103_db.sqc"
      sql_setdlist[13].sqldata = (void*)hkanjya.sdnm;
#line 1396 "AD103_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 21;
#line 1396 "AD103_db.sqc"
      sql_setdlist[14].sqldata = (void*)hkanjya.bko1;
#line 1396 "AD103_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 21;
#line 1396 "AD103_db.sqc"
      sql_setdlist[15].sqldata = (void*)hkanjya.bko2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 21;
#line 1396 "AD103_db.sqc"
      sql_setdlist[16].sqldata = (void*)hkanjya.bko3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 1396 "AD103_db.sqc"
      sql_setdlist[17].sqldata = (void*)hkanjya.zstrdh;
#line 1396 "AD103_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 1396 "AD103_db.sqc"
      sql_setdlist[18].sqldata = (void*)hkanjya.zsssdh;
#line 1396 "AD103_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 1396 "AD103_db.sqc"
      sql_setdlist[19].sqldata = (void*)hkanjya.stlzsssdh;
#line 1396 "AD103_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 16;
#line 1396 "AD103_db.sqc"
      sql_setdlist[20].sqldata = (void*)hkanjya.stlzsssip;
#line 1396 "AD103_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 9;
#line 1396 "AD103_db.sqc"
      sql_setdlist[21].sqldata = (void*)hkanjya.stlzssssyaid;
#line 1396 "AD103_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 27;
#line 1396 "AD103_db.sqc"
      sql_setdlist[22].sqldata = (void*)hkanjya.ksndh;
#line 1396 "AD103_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 1396 "AD103_db.sqc"
      sql_setdlist[23].sqldata = (void*)hkanjya.oyasstcd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 27;
#line 1396 "AD103_db.sqc"
      sql_setdlist[24].sqldata = (void*)hkanjya.trkdh;
#line 1396 "AD103_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sqlasetdata(3,64,25,sql_setdlist,0L,0L);
    }
#line 1396 "AD103_db.sqc"
  sqlacall((unsigned short)24,13,2,3,0L);
#line 1396 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1396 "AD103_db.sqc"

/*----- SELECT ここまで ------------------------------------------------------------*/
	sprintf( G_err, "%d", sqlca.sqlcode );
	sprintf( G_msg, "SELECT * FROM KANJYA : "
		"utkymd[%s]irino[%s]zssdino[%d]",
		hkanjya.utkymd, hkanjya.irino, hkanjya.zssdino );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
														/* LOG出力 */
	if ( sqlca.sqlcode == 0 ) {							/* SQL実行OK */
		EditCsvKanjya( &hkanjya );						/* 更新前情報のLOG出力 */
		LogOut( LT_TRC, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		ret = RTN_OK;									/* 実行結果 OK */
	}
	else{												/* SQL実行NG */
		if ( sqlca.sqlcode == 100 ){					/* 対象レコードが見つからなかった(NOT FOUND) */
			/* SQLCODE +100, SQLSTATE '02000' */
			sprintf( G_msg, "患者情報(KANJYA)が存在しません。" );
			EditCsvMsg( G_msg );
			LogOut( LT_ERR, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			ret = RTN_ZERO;								/* 実行結果 NOT FOUND */
		}
		else{
			/* SQLCODE > 0 -> WARNING */
			/* SQLCODE < 0 -> ERROR */
			sprintf( G_msg, "患者情報(KANJYA) SELECT で"
				"不具合が発生しました。" );
			EditCsvMsg( G_msg );
			LogOut( LT_ERR, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			ret = RTN_DBERR;							/* 実行結果 DB ERROR */
		}

	}
	return(ret);										/* 実行結果を応答 */
}

/******************************************************************************/
/*  関 数 名  ：InsShusei_Kanjya                                              */
/*  機能概要  ：修正属性 INSERT                                               */
/*  入    力  ：ホスト変数：hkanjya                                           */
/*            ：コール前にhkanjyaに患者情報を取得すること                     */
/*  第１引数  ：NONE                                                          */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK        正常終了                                        */
/*            ：MYAPP_RTN_DUP 異常終了(重複エラー発生) *これはありえない      */
/*            ：RTN_DBERR     異常終了(DBエラー発生)                          */
/******************************************************************************/
int		InsShusei_Kanjya()
{
	struct	sqlca	sqlca;								/* SQL実行コード */
	char	func_nm[MYAPP_LEN_FNCNM+1];					/* 関数名称	*/
	int	ret;											/* 実行結果 */

	/* 初期処理	*/
	strcpy(func_nm, "InsShusei_Kanjya" );				/* 実行関数名を設定 */
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
														/* LOG出力 */
/*----- INSERT ここから ------------------------------------------------------------*/

/*
EXEC SQL INSERT	INTO	SHUSEI_KANJYA
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
		, oyasstcd
		, trkdh
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
		, :hkanjya.oyasstcd
		, CURRENT TIMESTAMP
		)
	;
*/

{
#line 1634 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1634 "AD103_db.sqc"
  sqlaaloc(2,87,21,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 1634 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1634 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.utkymd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1634 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.irino;
#line 1634 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkanjya.iriketflg;
#line 1634 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)&hkanjya.zssdino;
#line 1634 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 1634 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkanjya.sstcd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 5;
#line 1634 "AD103_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkanjya.subsstcd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[6].sqldata = (void*)hkanjya.cdkbn1;
#line 1634 "AD103_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkanjya.cdkbn2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 41;
#line 1634 "AD103_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkanjya.irimkey;
#line 1634 "AD103_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 4;
#line 1634 "AD103_db.sqc"
      sql_setdlist[9].sqldata = (void*)hkanjya.srkcd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 31;
#line 1634 "AD103_db.sqc"
      sql_setdlist[10].sqldata = (void*)hkanjya.srknm;
#line 1634 "AD103_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 1634 "AD103_db.sqc"
      sql_setdlist[11].sqldata = (void*)hkanjya.tticd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 41;
#line 1634 "AD103_db.sqc"
      sql_setdlist[12].sqldata = (void*)hkanjya.ttinm;
#line 1634 "AD103_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 1634 "AD103_db.sqc"
      sql_setdlist[13].sqldata = (void*)hkanjya.gpcd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 41;
#line 1634 "AD103_db.sqc"
      sql_setdlist[14].sqldata = (void*)hkanjya.gpnm;
#line 1634 "AD103_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 1634 "AD103_db.sqc"
      sql_setdlist[15].sqldata = (void*)hkanjya.skicd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 41;
#line 1634 "AD103_db.sqc"
      sql_setdlist[16].sqldata = (void*)hkanjya.skinm;
#line 1634 "AD103_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 41;
#line 1634 "AD103_db.sqc"
      sql_setdlist[17].sqldata = (void*)hkanjya.krtno;
#line 1634 "AD103_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 16;
#line 1634 "AD103_db.sqc"
      sql_setdlist[18].sqldata = (void*)hkanjya.knjid;
#line 1634 "AD103_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 61;
#line 1634 "AD103_db.sqc"
      sql_setdlist[19].sqldata = (void*)hkanjya.knjnmn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 31;
#line 1634 "AD103_db.sqc"
      sql_setdlist[20].sqldata = (void*)hkanjya.knjnmk;
#line 1634 "AD103_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 61;
#line 1634 "AD103_db.sqc"
      sql_setdlist[21].sqldata = (void*)hkanjya.knjnmkey;
#line 1634 "AD103_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 6;
#line 1634 "AD103_db.sqc"
      sql_setdlist[22].sqldata = (void*)hkanjya.sc;
#line 1634 "AD103_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 6;
#line 1634 "AD103_db.sqc"
      sql_setdlist[23].sqldata = (void*)hkanjya.tj;
#line 1634 "AD103_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[24].sqldata = (void*)hkanjya.tjtni;
#line 1634 "AD103_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[25].sqldata = (void*)hkanjya.sbtkbn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 9;
#line 1634 "AD103_db.sqc"
      sql_setdlist[26].sqldata = (void*)hkanjya.birthday;
#line 1634 "AD103_db.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[27].sqldata = (void*)hkanjya.birthdaykbn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 4;
#line 1634 "AD103_db.sqc"
      sql_setdlist[28].sqldata = (void*)hkanjya.age;
#line 1634 "AD103_db.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[29].sqldata = (void*)hkanjya.agekbn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 11;
#line 1634 "AD103_db.sqc"
      sql_setdlist[30].sqldata = (void*)hkanjya.btcd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 31;
#line 1634 "AD103_db.sqc"
      sql_setdlist[31].sqldata = (void*)hkanjya.btnm;
#line 1634 "AD103_db.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[32].sqldata = (void*)hkanjya.utkcmtcd1;
#line 1634 "AD103_db.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[33].sqldata = (void*)hkanjya.utkcmtcd2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[34].sqldata = (void*)hkanjya.utkcmtcd3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 71;
#line 1634 "AD103_db.sqc"
      sql_setdlist[35].sqldata = (void*)hkanjya.utkcmtfr1;
#line 1634 "AD103_db.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 71;
#line 1634 "AD103_db.sqc"
      sql_setdlist[36].sqldata = (void*)hkanjya.utkcmtfr2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[37].sqldata = (void*)hkanjya.utkcmtfrflg;
#line 1634 "AD103_db.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[38].sqldata = (void*)hkanjya.ngkbn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[39].sqldata = (void*)hkanjya.nsssu;
#line 1634 "AD103_db.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[40].sqldata = (void*)hkanjya.hkncd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[41].sqldata = (void*)hkanjya.ktshsu;
#line 1634 "AD103_db.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 11;
#line 1634 "AD103_db.sqc"
      sql_setdlist[42].sqldata = (void*)hkanjya.iniriymd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[43].sqldata = (void*)hkanjya.zssflg;
#line 1634 "AD103_db.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[44].sqldata = (void*)hkanjya.kkiriflg;
#line 1634 "AD103_db.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[45].sqldata = (void*)hkanjya.hknskbn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[46].sqldata = (void*)hkanjya.utkkbn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[47].sqldata = (void*)hkanjya.nekbn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[48].sqldata = (void*)hkanjya.inknskbn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[49].sqldata = (void*)hkanjya.utkjkkbn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[50].sqldata = (void*)hkanjya.krflg;
#line 1634 "AD103_db.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[51].sqldata = (void*)hkanjya.fdhhkkflg;
#line 1634 "AD103_db.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 9;
#line 1634 "AD103_db.sqc"
      sql_setdlist[52].sqldata = (void*)hkanjya.utkdh;
#line 1634 "AD103_db.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 11;
#line 1634 "AD103_db.sqc"
      sql_setdlist[53].sqldata = (void*)hkanjya.mutkymd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 12;
#line 1634 "AD103_db.sqc"
      sql_setdlist[54].sqldata = (void*)hkanjya.mirino;
#line 1634 "AD103_db.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 1634 "AD103_db.sqc"
      sql_setdlist[55].sqldata = (void*)hkanjya.knsjslbcd1;
#line 1634 "AD103_db.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 4;
#line 1634 "AD103_db.sqc"
      sql_setdlist[56].sqldata = (void*)hkanjya.knsjslbcd2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 4;
#line 1634 "AD103_db.sqc"
      sql_setdlist[57].sqldata = (void*)hkanjya.knsjslbcd3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[58].sqltype = 460; sql_setdlist[58].sqllen = 4;
#line 1634 "AD103_db.sqc"
      sql_setdlist[58].sqldata = (void*)hkanjya.knsjslbcd4;
#line 1634 "AD103_db.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[59].sqltype = 460; sql_setdlist[59].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[59].sqldata = (void*)hkanjya.ymhkkflg;
#line 1634 "AD103_db.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[60].sqltype = 460; sql_setdlist[60].sqllen = 9;
#line 1634 "AD103_db.sqc"
      sql_setdlist[60].sqldata = (void*)hkanjya.hkkkbdh;
#line 1634 "AD103_db.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[61].sqltype = 460; sql_setdlist[61].sqllen = 4;
#line 1634 "AD103_db.sqc"
      sql_setdlist[61].sqldata = (void*)hkanjya.ecd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[62].sqltype = 460; sql_setdlist[62].sqllen = 3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[62].sqldata = (void*)hkanjya.shcd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[63].sqltype = 460; sql_setdlist[63].sqllen = 41;
#line 1634 "AD103_db.sqc"
      sql_setdlist[63].sqldata = (void*)hkanjya.sstssnmj;
#line 1634 "AD103_db.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sqlasetdata(2,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[23];
#line 1634 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 41;
#line 1634 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.sstssnmn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 1634 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.sstrsj;
#line 1634 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 1634 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkanjya.sstrsn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)hkanjya.sstsbt;
#line 1634 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkanjya.ttsstflg;
#line 1634 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkanjya.rucd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[6].sqldata = (void*)&hkanjya.irikmksu;
#line 1634 "AD103_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 1634 "AD103_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkanjya.bmskn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkanjya.irinrsbt;
#line 1634 "AD103_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[9].sqldata = (void*)hkanjya.irihsmkbn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[10].sqldata = (void*)hkanjya.caresstflg;
#line 1634 "AD103_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[11].sqldata = (void*)hkanjya.tktyflg;
#line 1634 "AD103_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 14;
#line 1634 "AD103_db.sqc"
      sql_setdlist[12].sqldata = (void*)hkanjya.apkntino;
#line 1634 "AD103_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 1634 "AD103_db.sqc"
      sql_setdlist[13].sqldata = (void*)hkanjya.sdnm;
#line 1634 "AD103_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 21;
#line 1634 "AD103_db.sqc"
      sql_setdlist[14].sqldata = (void*)hkanjya.bko1;
#line 1634 "AD103_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 21;
#line 1634 "AD103_db.sqc"
      sql_setdlist[15].sqldata = (void*)hkanjya.bko2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 21;
#line 1634 "AD103_db.sqc"
      sql_setdlist[16].sqldata = (void*)hkanjya.bko3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 1634 "AD103_db.sqc"
      sql_setdlist[17].sqldata = (void*)hkanjya.zstrdh;
#line 1634 "AD103_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 1634 "AD103_db.sqc"
      sql_setdlist[18].sqldata = (void*)hkanjya.zsssdh;
#line 1634 "AD103_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 1634 "AD103_db.sqc"
      sql_setdlist[19].sqldata = (void*)hkanjya.stlzsssdh;
#line 1634 "AD103_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 16;
#line 1634 "AD103_db.sqc"
      sql_setdlist[20].sqldata = (void*)hkanjya.stlzsssip;
#line 1634 "AD103_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 9;
#line 1634 "AD103_db.sqc"
      sql_setdlist[21].sqldata = (void*)hkanjya.stlzssssyaid;
#line 1634 "AD103_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 8;
#line 1634 "AD103_db.sqc"
      sql_setdlist[22].sqldata = (void*)hkanjya.oyasstcd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sqlasetdata(2,64,23,sql_setdlist,0L,0L);
    }
#line 1634 "AD103_db.sqc"
  sqlacall((unsigned short)24,14,2,0,0L);
#line 1634 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1634 "AD103_db.sqc"

/*----- INSERT ここまで ------------------------------------------------------------*/

	sprintf( G_err, "%d", sqlca.sqlcode );
	sprintf( G_msg, "INSERT kanjya : utkymd[%s]irino[%s]zssdino[%d]",
		hkanjya.utkymd, hkanjya.irino, hkanjya.zssdino );
	LogOut( LT_DBG, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__ );
														/* LOG出力 */
	if ( sqlca.sqlcode == 0 ) {							/* SQL実行OK */
		ret = RTN_OK;
	}
	else {
		if ( sqlca.sqlcode == MYAPP_RTN_DUP ) {			/* SQL実行 重複エラー */
														/* ★但し、ここでは絶対にありえないはず！★ */
			sprintf( G_msg,
				"属性修正情報(SHUSEI_KANJYA)は既に存在しています。"
				"BML受付年月日[%s]依頼書NO[%s]属性世代NO[%d]"
				,hkanjya.utkymd, hkanjya.irino, hkanjya.zssdino );
			/* ERROR */
			ret=MYAPP_RTN_DUP;							/* 実行結果 重複エラー */
		}
		else{
			sprintf( G_msg,
				"属性修正情報(SHUSEI_KANJYA)の INSERT に失敗しました。"
				"BML受付年月日[%s]依頼書NO[%s]属性世代NO[%d]"
				,hkanjya.utkymd, hkanjya.irino, hkanjya.zssdino );
			/* ERROR */
			ret=RTN_DBERR;								/* 実行結果 DB ERROR */
		}
		EditCsvMsg( G_msg );
		LogOut( LT_TRC, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__ );
														/* LOG出力 */

	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
														/* LOG出力 */
	return( ret );										/* 実行結果を応答 */
}

/******************************************************************************/
/*  関 数 名  ：DelKanjya                                                     */
/*  機能概要  ：属性修正のあった患者情報を削除する                            */
/*  入    力  ：                                                              */
/*  第１引数  ：struct  _KANJYA    *kan;   : 患者情報                         */
/*  出    力  ：NODE                                                          */
/*  復帰情報  ：RTN_OK       正常終了(DELETE成功)                             */
/*            ：RTN_ZERO     異常終了(該当レコードなし)                       */
/*            ：RTN_DBERR    異常終了(DBエラー発生)                           */
/******************************************************************************/
int		DelKanjya( kan )
struct		_KANJYA		*kan;							/* 患者情報 */
{
	int		ret;										/* 実行結果 */
	char	func_nm[30];								/* 関数名称	*/
	char	wbuf[30];									/* ワークバッファ */
	struct	sqlca	sqlca;								/* SQL実行コード */

	/* 初期処理	*/
	strcpy( func_nm, "DelKanjya" );						/* 実行関数名を設定 */
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
														/* LOG出力 */

	/* ホスト変数へのキー項目セット	*/
	memset( &hkanjya, '\0', sizeof( struct _KANJYA ));	/* 変数初期化 */
	strcpy( hkanjya.utkymd,	kan->utkymd );				/* 受け日を設定 */
	strcpy( hkanjya.irino,	kan->irino );				/* 依頼書Noを設定 */

/*----- DELETE ここから ------------------------------------------------------------*/
	/* 対象データ(受け日,依頼書No)でDELETE */
	
/*
EXEC SQL DELETE FROM KANJYA
		WHERE	utkymd	= :hkanjya.utkymd
		AND		irino	= :hkanjya.irino
		;
*/

{
#line 1706 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1706 "AD103_db.sqc"
  sqlaaloc(2,2,22,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 1706 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1706 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.utkymd;
#line 1706 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1706 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1706 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.irino;
#line 1706 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1706 "AD103_db.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 1706 "AD103_db.sqc"
  sqlacall((unsigned short)24,15,2,0,0L);
#line 1706 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1706 "AD103_db.sqc"


/*----- DELETE ここまで ------------------------------------------------------------*/
	if ( sqlca.sqlcode == 0 ) {							/* SQL実行OK */
		ret = RTN_OK;									/* 実行結果 OK */
	}
	else{												/* SQL実行NG */
		if ( sqlca.sqlcode == 100 ){					/* 対象レコードが見つからなかった(NOT FOUND) */
		/* SQLCODE +100, SQLSTATE '02000' */
		sprintf( G_msg, "削除患者情報(KANJYA)が存在しません。" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		ret = RTN_ZERO;									/* 実行結果 NOT FOUND */
		}
		else{											/* SQL実行NG */
			/* SQLCODE > 0 -> WARNING */
			/* SQLCODE < 0 -> ERROR */
			sprintf( G_msg, "患者情報(KANJYA) DELETE で"
								"不具合が発生しました。" );
			EditCsvMsg( G_msg );
			LogOut( LT_ERR, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			ret = RTN_DBERR;							/* 実行結果 DB ERROR */
		}
	}
	return(ret);										/* 実行結果を応答 */
}

/*  1.04     2009/06/29     Merits K.Ameno 障害管理No:0904031814/0904031719対応 <-- */

//****************************************************************************
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
#line 1746 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1746 "AD103_db.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 1746 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1746 "AD103_db.sqc"


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
#line 1772 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1772 "AD103_db.sqc"
  sqlacall((unsigned short)28,0,0,0,0L);
#line 1772 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1772 "AD103_db.sqc"


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

#line 1799 "AD103_db.sqc"

	char	dbAlias[15];
	char	user[129];
	char	pswd[15];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 1803 "AD103_db.sqc"


	strcpy( func_nm, "Ydbconn" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	strcpy( dbAlias,	stcPRM.dbp_dbAlias );
	strcpy( user,		stcPRM.dbp_user );
	strcpy( pswd,		stcPRM.dbp_pswd );

	
/*
EXEC SQL CONNECT TO :dbAlias USER :user USING :pswd;
*/

{
#line 1812 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1812 "AD103_db.sqc"
  sqlaaloc(2,3,23,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 1812 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 15;
#line 1812 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)dbAlias;
#line 1812 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1812 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 129;
#line 1812 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)user;
#line 1812 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1812 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 15;
#line 1812 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)pswd;
#line 1812 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1812 "AD103_db.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 1812 "AD103_db.sqc"
  sqlacall((unsigned short)29,5,2,0,0L);
#line 1812 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1812 "AD103_db.sqc"


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
#line 1845 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1845 "AD103_db.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 1845 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1845 "AD103_db.sqc"


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
#line 1856 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1856 "AD103_db.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 1856 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1856 "AD103_db.sqc"


	// edit sqlcacode for LogOut errcode
	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );
	// DEBUG
	LogOut( LT_DBG, LX_NON, G_err, "CONNECT RESET",func_nm, __FILE__, __LINE__);

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
  	return( RTN_OK );
} /* DbDisconn */
/** End of File ***************************************************************/
