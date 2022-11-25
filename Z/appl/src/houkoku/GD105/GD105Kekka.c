static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,71,65,69,52,85,97,68,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,52,71,49,48,53,32,32,32,0,0,0,0,0,0,0,0,
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


#line 1 "GD105Kekka.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： GD105Kekka.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-03-07     H.Suyama       Create
 *  1.01     2006-04-06     H.Suyama       検索条件にセクションコード追加
 *  1.02     2006-04-12     H.Suyama       テーブル結合条件を外部結合に変更
 *	1.03     2006-04-20     H.Suyama       コントロール精度保証変更
 *	                                       分析機号機→分析機ライン変更
 *	                                       検査フラグ更新関数追加
 *	1.04     2007-06-14     T.Wajima       速度アップのため、不要な項目を検索対象から削除
 *  1.05     2009-01-26     H.Sekiya       薬剤夜間対応　コントロール範囲で報告する時も
 *                                         検査グループを見るように変更
 *  2.00     2009-05-19     K.Moriya       結果変換マスタ対応
 **********************************************************************/
#include <stdio.h>

#include "GD105Kekka.h"
#include "bml_misc.h"
#include "bml_db.h"
#include "bml_dmm.h"

#include "bmllog.h"				// 1.06 ADD

#define ALLOC_UNIT		1


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 35 "GD105Kekka.sqc"


// upd 20070614 waj 速度アップのため、不要な項目を検索対象から削除

/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 42 "GD105Kekka.sqc"

	char    knskisymd[11];
	char    sriymd[11];
	char    kntno[14];
	char    knsgrp[17];
	char    kmkcd[8];
	short   knssu;
	short   knssueda;
	char    utkymd[11];
	char    irino[12];
	char    sstcd[8];
	char    oyakmkcd[8];
	char    seccd[3];
	char    smpcd[8];
	char    bskkbn[5];
	char    bskgok[7];
	char    zrcd[5];
	char    kjno[4];
	char    skflg;
	char    kkflg;
	short   kkirilotno;
	char    hsykflg;
	char    hskflg;
	char    hhkkflg;
	char    knskka1[13];
	char    knskka2[25];
	char    knskka2kbn[3];
	char    kkahskcd[4];
	char    sdi[4];
	char    kkacmt1[6];
	char    kkacmt2[6];
	char    kkajkcd;
	char    pncrgflg;
	char    kkaksflg;
	char    kkassflg;
	char    ijkbnm;
	char    ijkbnf;
	char    ijkbnn;
	sqlint32  ctrlno;
	sqlint32  knsseq;
	sqlint32  pltno;
	char    hkkdh[27];
	char    knsflg;
	char    ksndh[27];

	char    hkksjymd[11];
	sqlint32  hkksjno;
	char    hkkkbn;
	char    hkkjkn;
	char    hkkjknst[21];
	char    hkkjkned[21];
	char    hkkflnm[51];
	char    hkksjtts[9];
	char    hkkstdh[27];
	char    hkkeddh[27];
	char    tnsstdh[27];
	char    tnseddh[27];
	sqlint32  hkkssknsu;
	sqlint32  hkkhrysu;
	char    ssnmtfilid[13];
	char    hkkjkflg[3];
	char    hkkerrcode[9];

	// 範囲検索用
	sqlint32	ctrlnost;
	sqlint32	ctrlnoed;
	sqlint32	pltnost;
	sqlint32	pltnoed;
	sqlint32	knsseqst;
	sqlint32	knsseqed;
	char		irinost[12];
	char		irinoed[12];
	char		kntnost[14];
	char		kntnoed[14];

/* 2.00 2009.05.19 結果変換マスタ対応 START */
	char		skkka[24+1];
/* 2.00 2009.05.19 結果変換マスタ対応 END */

/*
EXEC SQL END DECLARE SECTION;
*/

#line 120 "GD105Kekka.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Kekka

BmlDMMInfo	KekkaArray[] = {
	DMM_SDATE( knskisymd ),
	DMM_SDATE( sriymd ),
	DMM_SSTRING( kntno ),
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSHORT( knssu ),
	DMM_SSHORT( knssueda ),
	DMM_SDATE( utkymd ),
	DMM_SSTRING( irino ),
	DMM_SSTRING( sstcd ),
	DMM_SSTRING( oyakmkcd ),
	DMM_SSTRING( seccd ),
	DMM_SSTRING( smpcd ),
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( bskgok ),
	DMM_SSTRING( zrcd ),
	DMM_SSTRING( kjno ),
	DMM_SCHAR( skflg ),
	DMM_SCHAR( kkflg ),
	DMM_SSHORT( kkirilotno ),
	DMM_SCHAR( hsykflg ),
	DMM_SCHAR( hskflg ),
	DMM_SCHAR( hhkkflg ),
	DMM_SSTRING( knskka1 ),
	DMM_SSTRING( knskka2 ),
	DMM_SSTRING( knskka2kbn ),
	DMM_SSTRING( kkahskcd ),
	DMM_SSTRING( sdi ),
	DMM_SSTRING( kkacmt1 ),
	DMM_SSTRING( kkacmt2 ),
	DMM_SCHAR( kkajkcd ),
	DMM_SCHAR( pncrgflg ),
	DMM_SCHAR( kkaksflg ),
	DMM_SCHAR( kkassflg ),
	DMM_SCHAR( ijkbnm ),
	DMM_SCHAR( ijkbnf ),
	DMM_SCHAR( ijkbnn ),
	DMM_SLONG( ctrlno ),
	DMM_SLONG( knsseq ),
	DMM_SLONG( pltno ),
	DMM_STIMESTAMP( hkkdh ),
	DMM_SCHAR( knsflg ),
	DMM_STIMESTAMP( ksndh ),
/* 2.00 2009.05.19 結果変換マスタ対応 START */
	DMM_SSTRING( skkka ),
/* 2.00 2009.05.19 結果変換マスタ対応 END */
	DMM_NULL
};

extern BmlDMMInfo      HkkknriArray[];

/******************************************************************************
 * ZdbKekkaGD105SelectByCtrlNo()
 *    KEKKA レコード条件取得（コントロールNo）
 * ■引数
 *    [I]  Kekka* pKey       取得するレコードのキー
 *    [O]  Kekka** arrayOut     取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKekkaGD105SelectByCtrlNo( Hkkknri* pKey, Kekka** arrayOut, int* numOut )
{
	Kekka*      array = NULL;
	int         num = 0;

	if( !pKey )
		return HRC_NULL_POINTER;

	if( !ZbmlMapStructToHost( (char*)pKey, HkkknriArray ) )
		return HRC_INVALID_VALUE;

	ctrlnost = atoi( hkkjknst );
	ctrlnoed = atoi( hkkjkned );

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 206 "GD105Kekka.sqc"


#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "ZdbKekkaGD105SelectByCtrlNo", __LINE__, EXEFLG_SEL, "020",
				"ctrlnost : [%d]  ctrlnoed : [%d]", ctrlnost, ctrlnoed );
#endif

	/* 1.05 2009.01.26 薬剤夜間対応 */ 
	/* コントロールNO範囲指定の時も検査グループ毎に報告できるよう変更 */
	/* VGS10101(VIEW)を使わないようにSQLを変更 */
	
/*
EXEC SQL DECLARE c3 CURSOR FOR
	SELECT
		KKA.KNSKISYMD,
		KKA.SRIYMD,
		KKA.KNTNO,
		KKA.KNSGRP,
		KKA.KMKCD,
		KKA.KNSSU,
		KKA.KNSSUEDA,
		KKA.UTKYMD,
		KKA.IRINO,
		KKA.SSTCD,
		KKA.OYAKMKCD,
		KKA.SECCD,
		KKA.SMPCD,
		KKA.BSKKBN,
		KKA.BSKGOK,
		KKA.ZRCD,
		KKA.KJNO,
		KKA.SKFLG,
		KKA.KKFLG,
		KKA.KKIRILOTNO,
		KKA.HSYKFLG,
		KKA.HSKFLG,
		KKA.HHKKFLG,
		KKA.KNSKKA1,
		KKA.KNSKKA2,
		KKA.KNSKKA2KBN,
		KKA.KKAHSKCD,
		KKA.SDI,
		KKA.KKACMT1,
		KKA.KKACMT2,
		KKA.KKAJKCD,
		KKA.PNCRGFLG,
		KKA.KKAKSFLG,
		KKA.KKASSFLG,
		KKA.IJKBNM,
		KKA.IJKBNF,
		KKA.IJKBNN,
		KKA.CTRLNO,
		KKA.KNSSEQ,
		KKA.PLTNO,
		KKA.HKKDH,
		KKA.KNSFLG,
		KKA.KSNDH,
		KKA.SKKKA
	FROM
		KEKKA KKA
		LEFT OUTER JOIN 
			(SELECT DISTINCT
				KKA_CNT.KNSKISYMD
				, KKA_CNT.BSKKBN
				, KKA_CNT.BSKLNE AS BSKGOK
				, KKA_CNT.CTRLNO
				, KKA_CNT.KNSGRP
				, COALESCE(VCHK.OKCNT, 0) AS OKCNT
				, COALESCE(VCHK.NGCNT, 0) AS NGCNT
				, COALESCE(VCHK.NONECNT, 0) AS NONECNT
				, COALESCE(KKA_ERR.FLGNGCNT, 0) AS FLGNGCNT
			FROM
				KEKKA  KKA_CNT
				LEFT OUTER JOIN VCTRLCHK VCHK
					ON KKA_CNT.KNSKISYMD = VCHK.KNSKISYMD
					AND KKA_CNT.BSKKBN = VCHK.BSKKBN
					AND KKA_CNT.BSKLNE = VCHK.BSKLNE
					AND KKA_CNT.CTRLNO = VCHK.CTRLNO
				LEFT OUTER JOIN
					(SELECT
						KNSKISYMD
						, BSKKBN
						, BSKLNE
						, CTRLNO
						, KNSGRP
						, COUNT(*) AS FLGNGCNT
					FROM
						KEKKA
					WHERE
						KNSFLG IN ('A', 'R', 'T')
						AND IRIKBN IN ('A','K')
						AND KKAJKCD = '3'
					GROUP BY
						KNSKISYMD
						, BSKKBN
						, BSKLNE
						, CTRLNO
						, KNSGRP
					) KKA_ERR 
					ON KKA_CNT.KNSKISYMD = KKA_ERR.KNSKISYMD
					AND KKA_CNT.BSKKBN = KKA_ERR.BSKKBN
					AND KKA_CNT.BSKLNE = KKA_ERR.BSKLNE
					AND KKA_CNT.CTRLNO = KKA_ERR.CTRLNO
					AND KKA_CNT.KNSGRP = KKA_ERR.KNSGRP
				WHERE
					KKA_CNT.IRIHSMKBN IN ('0', '1')
					AND KKA_CNT.KNSFLG <> 'E'
					AND KKA_CNT.KNSFLG <> 'M' 
			) AS CTC
			ON KKA.KNSKISYMD = CTC.KNSKISYMD
			AND KKA.BSKKBN = CTC.BSKKBN
			AND KKA.BSKLNE = CTC.BSKGOK
			AND KKA.CTRLNO = CTC.CTRLNO
			AND KKA.KNSGRP = CTC.KNSGRP
		LEFT OUTER JOIN (
			SELECT
				KNSKISYMD,
				BSKKBN,
				BSKGOK,
				KNSGRP,
				KMKCD,
				PLTNO,
				XBARMJTKBN,
				XBARMJKFLG
			FROM
				XBARM
		) XBM
			ON  KKA.KNSKISYMD	= XBM.KNSKISYMD
			AND KKA.BSKKBN		= XBM.BSKKBN
			AND KKA.BSKGOK		= XBM.BSKGOK
			AND KKA.KNSGRP		= XBM.KNSGRP
			AND KKA.KMKCD		= XBM.KMKCD
			AND KKA.PLTNO		= XBM.PLTNO
			AND KKA.KNSFLG 		= 'X'
			AND XBM.XBARMJKFLG	= '0'
			AND XBM.XBARMJTKBN IN ('K','T')
	WHERE
			KKA.KNSKISYMD	=  :knskisymd
		AND KKA.BSKKBN		=  :bskkbn
		AND KKA.BSKLNE		=  :bskgok
		AND KKA.KNSGRP		=  :knsgrp
		AND KKA.CTRLNO		>= :ctrlnost
		AND KKA.CTRLNO		<= :ctrlnoed
		AND KKA.KKAJKCD		=  :hkkkbn
		AND KKA.SECCD		=  :seccd
		AND ( KKA.IRIHSMKBN IN ('0', '1') )
		AND (
			KKA.KNSFLG = 'S'
			OR
			(
				KKA.KNSFLG = 'X' 
				AND COALESCE(CTC.OKCNT, 0) > 0
				AND COALESCE(CTC.NGCNT, 0) = 0
				AND COALESCE(CTC.NONECNT, 0) = 0
				AND FLGNGCNT = 0
				AND XBM.XBARMJKFLG IS NULL
			)
		)
		AND NOT EXISTS (
			SELECT 
				*
			FROM
				HKHRIRAI HKHR
			WHERE
				KKA.UTKYMD = HKHR.UTKYMD 
				AND KKA.IRINO = HKHR.IRINO
				AND KKA.KMKCD = HKHR.KMKCD
				AND HKHR.HKKHRKBN NOT IN ('0','4')
		)
	FOR READ ONLY;
*/

#line 373 "GD105Kekka.sqc"


#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "ZdbKekkaGD105SelectByCtrlNo", __LINE__, EXEFLG_SEL, "020",
				"knskisymd = [%s]", knskisymd );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "ZdbKekkaGD105SelectByCtrlNo", __LINE__, EXEFLG_SEL, "020",
				"bskkbn    = [%s]", bskkbn );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "ZdbKekkaGD105SelectByCtrlNo", __LINE__, EXEFLG_SEL, "020",
				"bskgok    = [%s]", bskgok );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "ZdbKekkaGD105SelectByCtrlNo", __LINE__, EXEFLG_SEL, "020",
				"knsgrp    = [%s]", knsgrp );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "ZdbKekkaGD105SelectByCtrlNo", __LINE__, EXEFLG_SEL, "020",
				"ctrlnost  = [%d]", ctrlnost );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "ZdbKekkaGD105SelectByCtrlNo", __LINE__, EXEFLG_SEL, "020",
				"ctrlnoed  = [%d]", ctrlnoed );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "ZdbKekkaGD105SelectByCtrlNo", __LINE__, EXEFLG_SEL, "020",
				"hkkkbn    = [%c]", hkkkbn );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "ZdbKekkaGD105SelectByCtrlNo", __LINE__, EXEFLG_SEL, "020",
				"seccd     = [%s]", seccd );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "ZdbKekkaGD105SelectByCtrlNo", __LINE__, EXEFLG_SEL, "020",
				"EXEC SQL OPEN c3 前" );
#endif

	
/*
EXEC SQL OPEN c3;
*/

{
#line 397 "GD105Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 397 "GD105Kekka.sqc"
  sqlaaloc(2,8,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 397 "GD105Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 397 "GD105Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 397 "GD105Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 397 "GD105Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 397 "GD105Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 397 "GD105Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 397 "GD105Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 7;
#line 397 "GD105Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)bskgok;
#line 397 "GD105Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 397 "GD105Kekka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 397 "GD105Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 397 "GD105Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 397 "GD105Kekka.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 397 "GD105Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)&ctrlnost;
#line 397 "GD105Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 397 "GD105Kekka.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 397 "GD105Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)&ctrlnoed;
#line 397 "GD105Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 397 "GD105Kekka.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 397 "GD105Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&hkkkbn;
#line 397 "GD105Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 397 "GD105Kekka.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 397 "GD105Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)seccd;
#line 397 "GD105Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 397 "GD105Kekka.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 397 "GD105Kekka.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 397 "GD105Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 397 "GD105Kekka.sqc"
  sqlastop(0L);
}

#line 397 "GD105Kekka.sqc"


#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "ZdbKekkaGD105SelectByCtrlNo", __LINE__, EXEFLG_SEL, "020",
				"EXEC SQL OPEN c3 後" );
#endif

	while( 1 ) {
		Kekka* rec;

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "ZdbKekkaGD105SelectByCtrlNo", __LINE__, EXEFLG_SEL, "020",
					"EXEC SQL FETCH c3 INTO 前" );
#endif

		
/*
EXEC SQL FETCH c3 INTO
			:knskisymd,
			:sriymd,
			:kntno,
			:knsgrp,
			:kmkcd,
			:knssu,
			:knssueda,
			:utkymd,
			:irino,
			:sstcd,
			:oyakmkcd,
			:seccd,
			:smpcd,
			:bskkbn,
			:bskgok,
			:zrcd,
			:kjno,
			:skflg,
			:kkflg,
			:kkirilotno,
			:hsykflg,
			:hskflg,
			:hhkkflg,
			:knskka1,
			:knskka2,
			:knskka2kbn,
			:kkahskcd,
			:sdi,
			:kkacmt1,
			:kkacmt2,
			:kkajkcd,
			:pncrgflg,
			:kkaksflg,
			:kkassflg,
			:ijkbnm,
			:ijkbnf,
			:ijkbnn,
			:ctrlno,
			:knsseq,
			:pltno,
			:hkkdh,
			:knsflg,
			:ksndh,
			:skkka;
*/

{
#line 456 "GD105Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 456 "GD105Kekka.sqc"
  sqlaaloc(3,44,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[44];
#line 456 "GD105Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)&knssu;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&knssueda;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)utkymd;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 12;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)irino;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 8;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)sstcd;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 8;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)oyakmkcd;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 3;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)seccd;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 8;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)smpcd;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 5;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)bskkbn;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 7;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)bskgok;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 5;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)zrcd;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 4;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)kjno;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)&skflg;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)&kkflg;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)&kkirilotno;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)&hsykflg;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)&hskflg;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)&hhkkflg;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 13;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)knskka1;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 25;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)knskka2;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 3;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)knskka2kbn;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 4;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)kkahskcd;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 4;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)sdi;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 6;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)kkacmt1;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 6;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)kkacmt2;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)&kkajkcd;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&pncrgflg;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)&kkaksflg;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)&kkassflg;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)&ijkbnm;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&ijkbnf;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)&ijkbnn;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[37].sqltype = 496; sql_setdlist[37].sqllen = 4;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&ctrlno;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[38].sqltype = 496; sql_setdlist[38].sqllen = 4;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)&knsseq;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[39].sqltype = 496; sql_setdlist[39].sqllen = 4;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&pltno;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 27;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)hkkdh;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)&knsflg;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 27;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)ksndh;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 25;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)skkka;
#line 456 "GD105Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 456 "GD105Kekka.sqc"
      sqlasetdata(3,0,44,sql_setdlist,0L,0L);
    }
#line 456 "GD105Kekka.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 456 "GD105Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 456 "GD105Kekka.sqc"
  sqlastop(0L);
}

#line 456 "GD105Kekka.sqc"


#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "ZdbKekkaGD105SelectByCtrlNo", __LINE__, EXEFLG_SEL, "020",
					"EXEC SQL FETCH c3 INTO 後" );
#endif

		if( SQLCODE == 100 )
			break;

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "ZdbKekkaGD105SelectByCtrlNo", __LINE__, EXEFLG_SEL, "020",
					"ZbmlRealloc 前" );
#endif

		if( num % ALLOC_UNIT == 0 ) {
			array = (Kekka*)ZbmlRealloc( array,
										 sizeof( Kekka ) * ( num + ALLOC_UNIT ) );
			memset( array + num, 0, sizeof( Kekka ) * ALLOC_UNIT );
		}

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "ZdbKekkaGD105SelectByCtrlNo", __LINE__, EXEFLG_SEL, "020",
					"ZbmlRealloc 後" );
#endif

		rec = array + num++;
		ZbmlMapHostToStruct( (char*)rec, KekkaArray );
	}

	
/*
EXEC SQL CLOSE c3;
*/

{
#line 486 "GD105Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 486 "GD105Kekka.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 486 "GD105Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 486 "GD105Kekka.sqc"
  sqlastop(0L);
}

#line 486 "GD105Kekka.sqc"


	*arrayOut = array;
	*numOut   = num;

	return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 494 "GD105Kekka.sqc"

printf("SQLERR : [%s]\n", sqlca.sqlerrmc);
	// 1.06 DEBUG    LOG
    sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbKekkaGD105SelectByCtrlNo",
                __LINE__,
                EXEFLG_SEL, "020",
                "SQLERR : [%s]", sqlca.sqlerrmc );

	return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKekkaGD105SelectByPltNo()
 *    KEKKA レコード条件取得（プロットNo）
 * ■引数
 *    [I]  Kekka* pKey       取得するレコードのキー
 *    [O]  Kekka** arrayOut     取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKekkaGD105SelectByPltNo( Hkkknri* pKey, Kekka** arrayOut, int* numOut )
{
	Kekka*      array = NULL;
	int         num = 0;

	if( !pKey )
		return HRC_NULL_POINTER;

	if( !ZbmlMapStructToHost( (char*)pKey, HkkknriArray ) )
		return HRC_INVALID_VALUE;

	pltnost = atoi( hkkjknst );
	pltnoed = atoi( hkkjkned );

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 531 "GD105Kekka.sqc"


	
/*
EXEC SQL DECLARE c4 CURSOR FOR
	SELECT
		KKA.KNSKISYMD,
		KKA.SRIYMD,
		KKA.KNTNO,
		KKA.KNSGRP,
		KKA.KMKCD,
		KKA.KNSSU,
		KKA.KNSSUEDA,
		KKA.UTKYMD,
		KKA.IRINO,
		KKA.SSTCD,
		KKA.OYAKMKCD,
		KKA.SECCD,
		KKA.SMPCD,
		KKA.BSKKBN,
		KKA.BSKGOK,
		KKA.ZRCD,
		KKA.KJNO,
		KKA.SKFLG,
		KKA.KKFLG,
		KKA.KKIRILOTNO,
		KKA.HSYKFLG,
		KKA.HSKFLG,
		KKA.HHKKFLG,
		KKA.KNSKKA1,
		KKA.KNSKKA2,
		KKA.KNSKKA2KBN,
		KKA.KKAHSKCD,
		KKA.SDI,
		KKA.KKACMT1,
		KKA.KKACMT2,
		KKA.KKAJKCD,
		KKA.PNCRGFLG,
		KKA.KKAKSFLG,
		KKA.KKASSFLG,
		KKA.IJKBNM,
		KKA.IJKBNF,
		KKA.IJKBNN,
		KKA.CTRLNO,
		KKA.KNSSEQ,
		KKA.PLTNO,
		KKA.HKKDH,
		KKA.KNSFLG,
		KKA.KSNDH,
		KKA.SKKKA
	FROM
		KEKKA KKA
		LEFT OUTER JOIN (
			SELECT
				KNSKISYMD,
				BSKKBN,
				BSKGOK,
				KNSGRP,
				KMKCD,
				PLTNO,
				XBARMJTKBN,
				XBARMJKFLG
			FROM
				XBARM
		) XBM
			ON  KKA.KNSKISYMD	= XBM.KNSKISYMD
			AND KKA.BSKKBN		= XBM.BSKKBN
			AND KKA.BSKGOK		= XBM.BSKGOK
			AND KKA.KNSGRP		= XBM.KNSGRP
			AND KKA.KMKCD		= XBM.KMKCD
			AND KKA.PLTNO		= XBM.PLTNO
			AND KKA.KNSFLG 		= 'X'
			AND XBM.XBARMJKFLG	= '0'
			AND XBM.XBARMJTKBN IN ('K','T')
	WHERE
			KKA.KNSKISYMD	=  :knskisymd
		AND KKA.BSKKBN		=  :bskkbn
		AND KKA.BSKLNE		=  :bskgok
		AND KKA.KNSGRP		=  :knsgrp
		AND KKA.KMKCD		=  :kmkcd
		AND KKA.PLTNO		>= :pltnost
		AND KKA.PLTNO		<= :pltnoed
		AND KKA.KKAJKCD		=  :hkkkbn
		AND KKA.SECCD		=  :seccd
		AND ( KKA.IRIHSMKBN IN ('0', '1') )
		AND (
			KKA.KNSFLG = 'S'
			OR
			(
				KKA.KNSFLG = 'X'
				AND XBM.XBARMJKFLG IS NULL
			)
		)
		AND NOT EXISTS (
			SELECT 
				*
			FROM
				HKHRIRAI HKHR
			WHERE
				KKA.UTKYMD = HKHR.UTKYMD 
				AND KKA.IRINO = HKHR.IRINO
				AND KKA.KMKCD = HKHR.KMKCD
				AND HKHR.HKKHRKBN NOT IN ('0','4')
		)
	FOR READ ONLY;
*/

#line 633 "GD105Kekka.sqc"


	
/*
EXEC SQL OPEN c4;
*/

{
#line 635 "GD105Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 635 "GD105Kekka.sqc"
  sqlaaloc(2,9,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 635 "GD105Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 7;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)bskgok;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)&pltnost;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&pltnoed;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)&hkkkbn;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 3;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)seccd;
#line 635 "GD105Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 635 "GD105Kekka.sqc"
      sqlasetdata(2,0,9,sql_setdlist,0L,0L);
    }
#line 635 "GD105Kekka.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 635 "GD105Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 635 "GD105Kekka.sqc"
  sqlastop(0L);
}

#line 635 "GD105Kekka.sqc"


	while( 1 ) {
		Kekka* rec;

		
/*
EXEC SQL FETCH c4 INTO
			:knskisymd,
			:sriymd,
			:kntno,
			:knsgrp,
			:kmkcd,
			:knssu,
			:knssueda,
			:utkymd,
			:irino,
			:sstcd,
			:oyakmkcd,
			:seccd,
			:smpcd,
			:bskkbn,
			:bskgok,
			:zrcd,
			:kjno,
			:skflg,
			:kkflg,
			:kkirilotno,
			:hsykflg,
			:hskflg,
			:hhkkflg,
			:knskka1,
			:knskka2,
			:knskka2kbn,
			:kkahskcd,
			:sdi,
			:kkacmt1,
			:kkacmt2,
			:kkajkcd,
			:pncrgflg,
			:kkaksflg,
			:kkassflg,
			:ijkbnm,
			:ijkbnf,
			:ijkbnn,
			:ctrlno,
			:knsseq,
			:pltno,
			:hkkdh,
			:knsflg,
			:ksndh,
			:skkka;
*/

{
#line 684 "GD105Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 684 "GD105Kekka.sqc"
  sqlaaloc(3,44,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[44];
#line 684 "GD105Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)&knssu;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&knssueda;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)utkymd;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 12;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)irino;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 8;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)sstcd;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 8;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)oyakmkcd;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 3;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)seccd;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 8;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)smpcd;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 5;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)bskkbn;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 7;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)bskgok;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 5;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)zrcd;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 4;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)kjno;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)&skflg;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)&kkflg;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)&kkirilotno;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)&hsykflg;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)&hskflg;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)&hhkkflg;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 13;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)knskka1;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 25;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)knskka2;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 3;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)knskka2kbn;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 4;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)kkahskcd;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 4;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)sdi;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 6;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)kkacmt1;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 6;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)kkacmt2;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)&kkajkcd;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&pncrgflg;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)&kkaksflg;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)&kkassflg;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)&ijkbnm;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&ijkbnf;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)&ijkbnn;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[37].sqltype = 496; sql_setdlist[37].sqllen = 4;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&ctrlno;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[38].sqltype = 496; sql_setdlist[38].sqllen = 4;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)&knsseq;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[39].sqltype = 496; sql_setdlist[39].sqllen = 4;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&pltno;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 27;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)hkkdh;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)&knsflg;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 27;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)ksndh;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 25;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)skkka;
#line 684 "GD105Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 684 "GD105Kekka.sqc"
      sqlasetdata(3,0,44,sql_setdlist,0L,0L);
    }
#line 684 "GD105Kekka.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 684 "GD105Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 684 "GD105Kekka.sqc"
  sqlastop(0L);
}

#line 684 "GD105Kekka.sqc"


		if( SQLCODE == 100 )
			break;

		if( num % ALLOC_UNIT == 0 ) {
			array = (Kekka*)ZbmlRealloc( array,
										 sizeof( Kekka ) * ( num + ALLOC_UNIT ) );
			memset( array + num, 0, sizeof( Kekka ) * ALLOC_UNIT );
		}

		rec = array + num++;
		ZbmlMapHostToStruct( (char*)rec, KekkaArray );
	}

	
/*
EXEC SQL CLOSE c4;
*/

{
#line 699 "GD105Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 699 "GD105Kekka.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 699 "GD105Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 699 "GD105Kekka.sqc"
  sqlastop(0L);
}

#line 699 "GD105Kekka.sqc"


	*arrayOut = array;
	*numOut   = num;

	return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 707 "GD105Kekka.sqc"

//1.06 DELL printf("SQLERR : [%s]\n", sqlca.sqlerrmc);
	// 1.06 DEBUG    LOG
    sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbKekkaGD105SelectByPltNo",
                __LINE__,
                EXEFLG_SEL, "020",
                "SQLERR : [%s]", sqlca.sqlerrmc );

	return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKekkaGD105SelectByKnsSeq()
 *    KEKKA レコード条件取得（検査SEQ）
 * ■引数
 *    [I]  Kekka* pKey       取得するレコードのキー
 *    [O]  Kekka** arrayOut     取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKekkaGD105SelectByKnsSeq( Hkkknri* pKey, Kekka** arrayOut, int* numOut )
{
	Kekka*      array = NULL;
	int         num = 0;

	if( !pKey )
		return HRC_NULL_POINTER;

	if( !ZbmlMapStructToHost( (char*)pKey, HkkknriArray ) )
		return HRC_INVALID_VALUE;

	knsseqst = atoi( hkkjknst );
	knsseqed = atoi( hkkjkned );

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 744 "GD105Kekka.sqc"


	
/*
EXEC SQL DECLARE c5 CURSOR FOR
	SELECT
		KKA.KNSKISYMD,
		KKA.SRIYMD,
		KKA.KNTNO,
		KKA.KNSGRP,
		KKA.KMKCD,
		KKA.KNSSU,
		KKA.KNSSUEDA,
		KKA.UTKYMD,
		KKA.IRINO,
		KKA.SSTCD,
		KKA.OYAKMKCD,
		KKA.SECCD,
		KKA.SMPCD,
		KKA.BSKKBN,
		KKA.BSKGOK,
		KKA.ZRCD,
		KKA.KJNO,
		KKA.SKFLG,
		KKA.KKFLG,
		KKA.KKIRILOTNO,
		KKA.HSYKFLG,
		KKA.HSKFLG,
		KKA.HHKKFLG,
		KKA.KNSKKA1,
		KKA.KNSKKA2,
		KKA.KNSKKA2KBN,
		KKA.KKAHSKCD,
		KKA.SDI,
		KKA.KKACMT1,
		KKA.KKACMT2,
		KKA.KKAJKCD,
		KKA.PNCRGFLG,
		KKA.KKAKSFLG,
		KKA.KKASSFLG,
		KKA.IJKBNM,
		KKA.IJKBNF,
		KKA.IJKBNN,
		KKA.CTRLNO,
		KKA.KNSSEQ,
		KKA.PLTNO,
		KKA.HKKDH,
		KKA.KNSFLG,
		KKA.KSNDH,
		KKA.SKKKA
	FROM
		KEKKA KKA
		LEFT OUTER JOIN VCTRLCHK CTC
			ON KKA.KNSKISYMD = CTC.KNSKISYMD
			AND KKA.BSKKBN = CTC.BSKKBN
			AND KKA.BSKLNE = CTC.BSKLNE
			AND KKA.CTRLNO = CTC.CTRLNO
		LEFT OUTER JOIN (
			SELECT
				KNSKISYMD,
				BSKKBN,
				BSKGOK,
				KNSGRP,
				KMKCD,
				PLTNO,
				XBARMJTKBN,
				XBARMJKFLG
			FROM
				XBARM
		) XBM
			ON  KKA.KNSKISYMD	= XBM.KNSKISYMD
			AND KKA.BSKKBN		= XBM.BSKKBN
			AND KKA.BSKGOK		= XBM.BSKGOK
			AND KKA.KNSGRP		= XBM.KNSGRP
			AND KKA.KMKCD		= XBM.KMKCD
			AND KKA.PLTNO		= XBM.PLTNO
			AND KKA.KNSFLG 		= 'X'
			AND XBM.XBARMJKFLG	= '0'
			AND XBM.XBARMJTKBN IN ('K','T')
	WHERE
			KKA.KNSKISYMD	=  :knskisymd
		AND KKA.KNSGRP		=  :knsgrp
		AND KKA.KNSSEQ		>= :knsseqst
		AND KKA.KNSSEQ		<= :knsseqed
		AND KKA.KKAJKCD		=  :hkkkbn
		AND KKA.SECCD		=  :seccd
		AND ( KKA.IRIHSMKBN IN ('0', '1') )
		AND (
			KKA.KNSFLG = 'S'
			OR
			(
				KKA.KNSFLG = 'X'
				AND COALESCE(CTC.OKCNT, 0) > 0
				AND COALESCE(CTC.NGCNT, 0) = 0
				AND COALESCE(CTC.NONECNT, 0) = 0
				AND XBM.XBARMJKFLG IS NULL
			)
		)
		AND NOT EXISTS (
			SELECT 
				*
			FROM
				HKHRIRAI HKHR
			WHERE
				KKA.UTKYMD = HKHR.UTKYMD 
				AND KKA.IRINO = HKHR.IRINO
				AND KKA.KMKCD = HKHR.KMKCD
				AND HKHR.HKKHRKBN NOT IN ('0','4')
		)
	FOR READ ONLY;
*/

#line 851 "GD105Kekka.sqc"


	
/*
EXEC SQL OPEN c5;
*/

{
#line 853 "GD105Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 853 "GD105Kekka.sqc"
  sqlaaloc(2,6,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 853 "GD105Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 853 "GD105Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 853 "GD105Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 853 "GD105Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 853 "GD105Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 853 "GD105Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 853 "GD105Kekka.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 853 "GD105Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)&knsseqst;
#line 853 "GD105Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 853 "GD105Kekka.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 853 "GD105Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)&knsseqed;
#line 853 "GD105Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 853 "GD105Kekka.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 853 "GD105Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)&hkkkbn;
#line 853 "GD105Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 853 "GD105Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 853 "GD105Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)seccd;
#line 853 "GD105Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 853 "GD105Kekka.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 853 "GD105Kekka.sqc"
  sqlacall((unsigned short)26,3,2,0,0L);
#line 853 "GD105Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 853 "GD105Kekka.sqc"
  sqlastop(0L);
}

#line 853 "GD105Kekka.sqc"


	while( 1 ) {
		Kekka* rec;

		
/*
EXEC SQL FETCH c5 INTO
			:knskisymd,
			:sriymd,
			:kntno,
			:knsgrp,
			:kmkcd,
			:knssu,
			:knssueda,
			:utkymd,
			:irino,
			:sstcd,
			:oyakmkcd,
			:seccd,
			:smpcd,
			:bskkbn,
			:bskgok,
			:zrcd,
			:kjno,
			:skflg,
			:kkflg,
			:kkirilotno,
			:hsykflg,
			:hskflg,
			:hhkkflg,
			:knskka1,
			:knskka2,
			:knskka2kbn,
			:kkahskcd,
			:sdi,
			:kkacmt1,
			:kkacmt2,
			:kkajkcd,
			:pncrgflg,
			:kkaksflg,
			:kkassflg,
			:ijkbnm,
			:ijkbnf,
			:ijkbnn,
			:ctrlno,
			:knsseq,
			:pltno,
			:hkkdh,
			:knsflg,
			:ksndh,
			:skkka;
*/

{
#line 902 "GD105Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 902 "GD105Kekka.sqc"
  sqlaaloc(3,44,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[44];
#line 902 "GD105Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)&knssu;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&knssueda;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)utkymd;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 12;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)irino;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 8;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)sstcd;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 8;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)oyakmkcd;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 3;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)seccd;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 8;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)smpcd;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 5;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)bskkbn;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 7;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)bskgok;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 5;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)zrcd;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 4;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)kjno;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)&skflg;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)&kkflg;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)&kkirilotno;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)&hsykflg;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)&hskflg;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)&hhkkflg;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 13;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)knskka1;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 25;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)knskka2;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 3;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)knskka2kbn;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 4;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)kkahskcd;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 4;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)sdi;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 6;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)kkacmt1;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 6;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)kkacmt2;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)&kkajkcd;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&pncrgflg;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)&kkaksflg;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)&kkassflg;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)&ijkbnm;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&ijkbnf;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)&ijkbnn;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[37].sqltype = 496; sql_setdlist[37].sqllen = 4;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&ctrlno;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[38].sqltype = 496; sql_setdlist[38].sqllen = 4;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)&knsseq;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[39].sqltype = 496; sql_setdlist[39].sqllen = 4;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&pltno;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 27;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)hkkdh;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)&knsflg;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 27;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)ksndh;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 25;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)skkka;
#line 902 "GD105Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 902 "GD105Kekka.sqc"
      sqlasetdata(3,0,44,sql_setdlist,0L,0L);
    }
#line 902 "GD105Kekka.sqc"
  sqlacall((unsigned short)25,3,0,3,0L);
#line 902 "GD105Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 902 "GD105Kekka.sqc"
  sqlastop(0L);
}

#line 902 "GD105Kekka.sqc"


		if( SQLCODE == 100 )
			break;

		if( num % ALLOC_UNIT == 0 ) {
			array = (Kekka*)ZbmlRealloc( array,
										 sizeof( Kekka ) * ( num + ALLOC_UNIT ) );
			memset( array + num, 0, sizeof( Kekka ) * ALLOC_UNIT );
		}

		rec = array + num++;
		ZbmlMapHostToStruct( (char*)rec, KekkaArray );
	}

	
/*
EXEC SQL CLOSE c5;
*/

{
#line 917 "GD105Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 917 "GD105Kekka.sqc"
  sqlacall((unsigned short)20,3,0,0,0L);
#line 917 "GD105Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 917 "GD105Kekka.sqc"
  sqlastop(0L);
}

#line 917 "GD105Kekka.sqc"


	*arrayOut = array;
	*numOut   = num;

	return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 925 "GD105Kekka.sqc"

//1.06 DELL printf("SQLERR : [%s]\n", sqlca.sqlerrmc);
	// 1.06 DEBUG    LOG
    sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbKekkaGD105SelectByKnsSeq",
                __LINE__,
                EXEFLG_SEL, "020",
                "SQLERR : [%s]", sqlca.sqlerrmc );

	return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKekkaGD105SelectByIriNo()
 *    KEKKA レコード条件取得（依頼No）
 * ■引数
 *    [I]  Kekka* pKey       取得するレコードのキー
 *    [O]  Kekka** arrayOut     取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKekkaGD105SelectByIriNo( Hkkknri* pKey, Kekka** arrayOut, int* numOut )
{
	Kekka*      array = NULL;
	int         num = 0;

	if( !pKey )
		return HRC_NULL_POINTER;

	if( !ZbmlMapStructToHost( (char*)pKey, HkkknriArray ) )
		return HRC_INVALID_VALUE;

	memset( irinost, 0, sizeof( irinost ) );
	memcpy( irinost, hkkjknst, sizeof( irinost ) );
	memset( irinoed, 0, sizeof( irinoed ) );
	memcpy( irinoed, hkkjkned, sizeof( irinoed ) );

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 964 "GD105Kekka.sqc"


	
/*
EXEC SQL DECLARE c6 CURSOR FOR
	SELECT
		KKA.KNSKISYMD,
		KKA.SRIYMD,
		KKA.KNTNO,
		KKA.KNSGRP,
		KKA.KMKCD,
		KKA.KNSSU,
		KKA.KNSSUEDA,
		KKA.UTKYMD,
		KKA.IRINO,
		KKA.SSTCD,
		KKA.OYAKMKCD,
		KKA.SECCD,
		KKA.SMPCD,
		KKA.BSKKBN,
		KKA.BSKGOK,
		KKA.ZRCD,
		KKA.KJNO,
		KKA.SKFLG,
		KKA.KKFLG,
		KKA.KKIRILOTNO,
		KKA.HSYKFLG,
		KKA.HSKFLG,
		KKA.HHKKFLG,
		KKA.KNSKKA1,
		KKA.KNSKKA2,
		KKA.KNSKKA2KBN,
		KKA.KKAHSKCD,
		KKA.SDI,
		KKA.KKACMT1,
		KKA.KKACMT2,
		KKA.KKAJKCD,
		KKA.PNCRGFLG,
		KKA.KKAKSFLG,
		KKA.KKASSFLG,
		KKA.IJKBNM,
		KKA.IJKBNF,
		KKA.IJKBNN,
		KKA.CTRLNO,
		KKA.KNSSEQ,
		KKA.PLTNO,
		KKA.HKKDH,
		KKA.KNSFLG,
		KKA.KSNDH,
		KKA.SKKKA
	FROM
		KEKKA KKA
		LEFT OUTER JOIN VCTRLCHK CTC
			ON KKA.KNSKISYMD = CTC.KNSKISYMD
			AND KKA.BSKKBN = CTC.BSKKBN
			AND KKA.BSKLNE = CTC.BSKLNE
			AND KKA.CTRLNO = CTC.CTRLNO
		LEFT OUTER JOIN (
			SELECT
				KNSKISYMD,
				BSKKBN,
				BSKGOK,
				KNSGRP,
				KMKCD,
				PLTNO,
				XBARMJTKBN,
				XBARMJKFLG
			FROM
				XBARM
		) XBM
			ON  KKA.KNSKISYMD	= XBM.KNSKISYMD
			AND KKA.BSKKBN		= XBM.BSKKBN
			AND KKA.BSKGOK		= XBM.BSKGOK
			AND KKA.KNSGRP		= XBM.KNSGRP
			AND KKA.KMKCD		= XBM.KMKCD
			AND KKA.PLTNO		= XBM.PLTNO
			AND KKA.KNSFLG 		= 'X'
			AND XBM.XBARMJKFLG	= '0'
			AND XBM.XBARMJTKBN IN ('K','T')
	WHERE
			KKA.UTKYMD		=  :utkymd
		AND KKA.KNSGRP		=  :knsgrp
		AND KKA.IRINO		>= :irinost
		AND KKA.IRINO		<= :irinoed
		AND KKA.KKAJKCD		=  :hkkkbn
		AND KKA.SECCD		=  :seccd
		AND ( KKA.IRIHSMKBN IN ('0', '1') )
		AND (
			KKA.KNSFLG = 'S'
			OR
			(
				KKA.KNSFLG = 'X'
				AND COALESCE(CTC.OKCNT, 0) > 0
				AND COALESCE(CTC.NGCNT, 0) = 0
				AND COALESCE(CTC.NONECNT, 0) = 0
				AND XBM.XBARMJKFLG IS NULL
			)
		)
		AND NOT EXISTS (
			SELECT 
				*
			FROM
				HKHRIRAI HKHR
			WHERE
				KKA.UTKYMD = HKHR.UTKYMD 
				AND KKA.IRINO = HKHR.IRINO
				AND KKA.KMKCD = HKHR.KMKCD
				AND HKHR.HKKHRKBN NOT IN ('0','4')
		)
	FOR READ ONLY;
*/

#line 1071 "GD105Kekka.sqc"


	
/*
EXEC SQL OPEN c6;
*/

{
#line 1073 "GD105Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1073 "GD105Kekka.sqc"
  sqlaaloc(2,6,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 1073 "GD105Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1073 "GD105Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 1073 "GD105Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1073 "GD105Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 1073 "GD105Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 1073 "GD105Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1073 "GD105Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 12;
#line 1073 "GD105Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)irinost;
#line 1073 "GD105Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1073 "GD105Kekka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 12;
#line 1073 "GD105Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)irinoed;
#line 1073 "GD105Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1073 "GD105Kekka.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 1073 "GD105Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)&hkkkbn;
#line 1073 "GD105Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1073 "GD105Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 1073 "GD105Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)seccd;
#line 1073 "GD105Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1073 "GD105Kekka.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 1073 "GD105Kekka.sqc"
  sqlacall((unsigned short)26,4,2,0,0L);
#line 1073 "GD105Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1073 "GD105Kekka.sqc"
  sqlastop(0L);
}

#line 1073 "GD105Kekka.sqc"


	while( 1 ) {
		Kekka* rec;

		
/*
EXEC SQL FETCH c6 INTO
			:knskisymd,
			:sriymd,
			:kntno,
			:knsgrp,
			:kmkcd,
			:knssu,
			:knssueda,
			:utkymd,
			:irino,
			:sstcd,
			:oyakmkcd,
			:seccd,
			:smpcd,
			:bskkbn,
			:bskgok,
			:zrcd,
			:kjno,
			:skflg,
			:kkflg,
			:kkirilotno,
			:hsykflg,
			:hskflg,
			:hhkkflg,
			:knskka1,
			:knskka2,
			:knskka2kbn,
			:kkahskcd,
			:sdi,
			:kkacmt1,
			:kkacmt2,
			:kkajkcd,
			:pncrgflg,
			:kkaksflg,
			:kkassflg,
			:ijkbnm,
			:ijkbnf,
			:ijkbnn,
			:ctrlno,
			:knsseq,
			:pltno,
			:hkkdh,
			:knsflg,
			:ksndh,
			:skkka;
*/

{
#line 1122 "GD105Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1122 "GD105Kekka.sqc"
  sqlaaloc(3,44,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[44];
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)&knssu;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&knssueda;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)utkymd;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 12;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)irino;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 8;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)sstcd;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 8;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)oyakmkcd;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 3;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)seccd;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 8;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)smpcd;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 5;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)bskkbn;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 7;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)bskgok;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 5;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)zrcd;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 4;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)kjno;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)&skflg;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)&kkflg;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)&kkirilotno;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)&hsykflg;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)&hskflg;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)&hhkkflg;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 13;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)knskka1;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 25;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)knskka2;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 3;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)knskka2kbn;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 4;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)kkahskcd;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 4;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)sdi;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 6;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)kkacmt1;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 6;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)kkacmt2;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)&kkajkcd;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&pncrgflg;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)&kkaksflg;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)&kkassflg;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)&ijkbnm;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&ijkbnf;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)&ijkbnn;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[37].sqltype = 496; sql_setdlist[37].sqllen = 4;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&ctrlno;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[38].sqltype = 496; sql_setdlist[38].sqllen = 4;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)&knsseq;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[39].sqltype = 496; sql_setdlist[39].sqllen = 4;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&pltno;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 27;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)hkkdh;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)&knsflg;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 27;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)ksndh;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 25;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)skkka;
#line 1122 "GD105Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 1122 "GD105Kekka.sqc"
      sqlasetdata(3,0,44,sql_setdlist,0L,0L);
    }
#line 1122 "GD105Kekka.sqc"
  sqlacall((unsigned short)25,4,0,3,0L);
#line 1122 "GD105Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1122 "GD105Kekka.sqc"
  sqlastop(0L);
}

#line 1122 "GD105Kekka.sqc"


		if( SQLCODE == 100 )
			break;

		if( num % ALLOC_UNIT == 0 ) {
			array = (Kekka*)ZbmlRealloc( array,
										 sizeof( Kekka ) * ( num + ALLOC_UNIT ) );
			memset( array + num, 0, sizeof( Kekka ) * ALLOC_UNIT );
		}

		rec = array + num++;
		ZbmlMapHostToStruct( (char*)rec, KekkaArray );
	}

	
/*
EXEC SQL CLOSE c6;
*/

{
#line 1137 "GD105Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1137 "GD105Kekka.sqc"
  sqlacall((unsigned short)20,4,0,0,0L);
#line 1137 "GD105Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1137 "GD105Kekka.sqc"
  sqlastop(0L);
}

#line 1137 "GD105Kekka.sqc"


	*arrayOut = array;
	*numOut   = num;

	return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 1145 "GD105Kekka.sqc"

//1.06 DELL printf("SQLERR : [%s]\n", sqlca.sqlerrmc);
	// 1.06 DEBUG    LOG
    sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbKekkaGD105SelectByIriNo",
                __LINE__,
                EXEFLG_SEL, "020",
                "SQLERR : [%s]", sqlca.sqlerrmc );

	return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKekkaGD105SelectByKntNo()
 *    KEKKA レコード条件取得（検体No）
 * ■引数
 *    [I]  Kekka* pKey       取得するレコードのキー
 *    [O]  Kekka** arrayOut     取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKekkaGD105SelectByKntNo( Hkkknri* pKey, Kekka** arrayOut, int* numOut )
{
	Kekka*      array = NULL;
	int         num = 0;

	if( !pKey )
		return HRC_NULL_POINTER;

	if( !ZbmlMapStructToHost( (char*)pKey, HkkknriArray ) )
		return HRC_INVALID_VALUE;

	memset( kntnost, 0, sizeof( kntnost ) );
	memcpy( kntnost, hkkjknst, sizeof( kntnost ) );
	memset( kntnoed, 0, sizeof( kntnoed ) );
	memcpy( kntnoed, hkkjkned, sizeof( kntnoed ) );

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 1184 "GD105Kekka.sqc"


	
/*
EXEC SQL DECLARE c7 CURSOR FOR
	SELECT
		KKA.KNSKISYMD,
		KKA.SRIYMD,
		KKA.KNTNO,
		KKA.KNSGRP,
		KKA.KMKCD,
		KKA.KNSSU,
		KKA.KNSSUEDA,
		KKA.UTKYMD,
		KKA.IRINO,
		KKA.SSTCD,
		KKA.OYAKMKCD,
		KKA.SECCD,
		KKA.SMPCD,
		KKA.BSKKBN,
		KKA.BSKGOK,
		KKA.ZRCD,
		KKA.KJNO,
		KKA.SKFLG,
		KKA.KKFLG,
		KKA.KKIRILOTNO,
		KKA.HSYKFLG,
		KKA.HSKFLG,
		KKA.HHKKFLG,
		KKA.KNSKKA1,
		KKA.KNSKKA2,
		KKA.KNSKKA2KBN,
		KKA.KKAHSKCD,
		KKA.SDI,
		KKA.KKACMT1,
		KKA.KKACMT2,
		KKA.KKAJKCD,
		KKA.PNCRGFLG,
		KKA.KKAKSFLG,
		KKA.KKASSFLG,
		KKA.IJKBNM,
		KKA.IJKBNF,
		KKA.IJKBNN,
		KKA.CTRLNO,
		KKA.KNSSEQ,
		KKA.PLTNO,
		KKA.HKKDH,
		KKA.KNSFLG,
		KKA.KSNDH,
		KKA.SKKKA
	FROM
		KEKKA KKA
		LEFT OUTER JOIN VCTRLCHK CTC
			ON KKA.KNSKISYMD = CTC.KNSKISYMD
			AND KKA.BSKKBN = CTC.BSKKBN
			AND KKA.BSKLNE = CTC.BSKLNE
			AND KKA.CTRLNO = CTC.CTRLNO
		LEFT OUTER JOIN (
			SELECT
				KNSKISYMD,
				BSKKBN,
				BSKGOK,
				KNSGRP,
				KMKCD,
				PLTNO,
				XBARMJTKBN,
				XBARMJKFLG
			FROM
				XBARM
		) XBM
			ON  KKA.KNSKISYMD	= XBM.KNSKISYMD
			AND KKA.BSKKBN		= XBM.BSKKBN
			AND KKA.BSKGOK		= XBM.BSKGOK
			AND KKA.KNSGRP		= XBM.KNSGRP
			AND KKA.KMKCD		= XBM.KMKCD
			AND KKA.PLTNO		= XBM.PLTNO
			AND KKA.KNSFLG 		= 'X'
			AND XBM.XBARMJKFLG	= '0'
			AND XBM.XBARMJTKBN IN ('K','T')
	WHERE
			KKA.SRIYMD		=  :sriymd
		AND KKA.KNSGRP		=  :knsgrp
		AND KKA.KNTNO		>= :kntnost
		AND KKA.KNTNO		<= :kntnoed
		AND KKA.KKAJKCD		=  :hkkkbn
		AND KKA.SECCD		=  :seccd
		AND ( KKA.IRIHSMKBN IN ('0', '1') )
		AND (
			KKA.KNSFLG = 'S'
			OR
			(
				KKA.KNSFLG = 'X'
				AND COALESCE(CTC.OKCNT, 0) > 0
				AND COALESCE(CTC.NGCNT, 0) = 0
				AND COALESCE(CTC.NONECNT, 0) = 0
				AND XBM.XBARMJKFLG IS NULL
			)
		)
		AND NOT EXISTS (
			SELECT 
				*
			FROM
				HKHRIRAI HKHR
			WHERE
				KKA.UTKYMD = HKHR.UTKYMD 
				AND KKA.IRINO = HKHR.IRINO
				AND KKA.KMKCD = HKHR.KMKCD
				AND HKHR.HKKHRKBN NOT IN ('0','4')
		)
	FOR READ ONLY;
*/

#line 1291 "GD105Kekka.sqc"


	
/*
EXEC SQL OPEN c7;
*/

{
#line 1293 "GD105Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1293 "GD105Kekka.sqc"
  sqlaaloc(2,6,9,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 1293 "GD105Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1293 "GD105Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)sriymd;
#line 1293 "GD105Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1293 "GD105Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 1293 "GD105Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 1293 "GD105Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1293 "GD105Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 1293 "GD105Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)kntnost;
#line 1293 "GD105Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1293 "GD105Kekka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 14;
#line 1293 "GD105Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)kntnoed;
#line 1293 "GD105Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1293 "GD105Kekka.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 1293 "GD105Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)&hkkkbn;
#line 1293 "GD105Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1293 "GD105Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 1293 "GD105Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)seccd;
#line 1293 "GD105Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1293 "GD105Kekka.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 1293 "GD105Kekka.sqc"
  sqlacall((unsigned short)26,5,2,0,0L);
#line 1293 "GD105Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1293 "GD105Kekka.sqc"
  sqlastop(0L);
}

#line 1293 "GD105Kekka.sqc"


	while( 1 ) {
		Kekka* rec;

		
/*
EXEC SQL FETCH c7 INTO
			:knskisymd,
			:sriymd,
			:kntno,
			:knsgrp,
			:kmkcd,
			:knssu,
			:knssueda,
			:utkymd,
			:irino,
			:sstcd,
			:oyakmkcd,
			:seccd,
			:smpcd,
			:bskkbn,
			:bskgok,
			:zrcd,
			:kjno,
			:skflg,
			:kkflg,
			:kkirilotno,
			:hsykflg,
			:hskflg,
			:hhkkflg,
			:knskka1,
			:knskka2,
			:knskka2kbn,
			:kkahskcd,
			:sdi,
			:kkacmt1,
			:kkacmt2,
			:kkajkcd,
			:pncrgflg,
			:kkaksflg,
			:kkassflg,
			:ijkbnm,
			:ijkbnf,
			:ijkbnn,
			:ctrlno,
			:knsseq,
			:pltno,
			:hkkdh,
			:knsflg,
			:ksndh,
			:skkka;
*/

{
#line 1342 "GD105Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1342 "GD105Kekka.sqc"
  sqlaaloc(3,44,10,0L);
    {
      struct sqla_setdata_list sql_setdlist[44];
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)&knssu;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&knssueda;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)utkymd;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 12;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)irino;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 8;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)sstcd;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 8;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)oyakmkcd;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 3;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)seccd;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 8;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)smpcd;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 5;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)bskkbn;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 7;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)bskgok;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 5;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)zrcd;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 4;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)kjno;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)&skflg;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)&kkflg;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)&kkirilotno;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)&hsykflg;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)&hskflg;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)&hhkkflg;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 13;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)knskka1;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 25;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)knskka2;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 3;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)knskka2kbn;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 4;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)kkahskcd;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 4;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)sdi;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 6;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)kkacmt1;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 6;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)kkacmt2;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)&kkajkcd;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&pncrgflg;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)&kkaksflg;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)&kkassflg;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)&ijkbnm;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&ijkbnf;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)&ijkbnn;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[37].sqltype = 496; sql_setdlist[37].sqllen = 4;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&ctrlno;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[38].sqltype = 496; sql_setdlist[38].sqllen = 4;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)&knsseq;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[39].sqltype = 496; sql_setdlist[39].sqllen = 4;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&pltno;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 27;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)hkkdh;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)&knsflg;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 27;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)ksndh;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 25;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)skkka;
#line 1342 "GD105Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 1342 "GD105Kekka.sqc"
      sqlasetdata(3,0,44,sql_setdlist,0L,0L);
    }
#line 1342 "GD105Kekka.sqc"
  sqlacall((unsigned short)25,5,0,3,0L);
#line 1342 "GD105Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1342 "GD105Kekka.sqc"
  sqlastop(0L);
}

#line 1342 "GD105Kekka.sqc"


		if( SQLCODE == 100 )
			break;

		if( num % ALLOC_UNIT == 0 ) {
			array = (Kekka*)ZbmlRealloc( array,
										 sizeof( Kekka ) * ( num + ALLOC_UNIT ) );
			memset( array + num, 0, sizeof( Kekka ) * ALLOC_UNIT );
		}

		rec = array + num++;
		ZbmlMapHostToStruct( (char*)rec, KekkaArray );
	}

	
/*
EXEC SQL CLOSE c7;
*/

{
#line 1357 "GD105Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1357 "GD105Kekka.sqc"
  sqlacall((unsigned short)20,5,0,0,0L);
#line 1357 "GD105Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1357 "GD105Kekka.sqc"
  sqlastop(0L);
}

#line 1357 "GD105Kekka.sqc"


	*arrayOut = array;
	*numOut   = num;

	return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 1365 "GD105Kekka.sqc"

//1.06 DELL printf("SQLERR : [%s]\n", sqlca.sqlerrmc);
	// 1.06 DEBUG    LOG
    sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbKekkaGD105SelectByKntNo",
                __LINE__,
                EXEFLG_SEL, "020",
                "SQLERR : [%s]", sqlca.sqlerrmc );

	return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKekkaGD105Update()
 *    KEKKA レコードを更新する
 * ■引数
 *    [I]  Kekka* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKekkaGD105Update( Kekka* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KekkaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 1396 "GD105Kekka.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 1397 "GD105Kekka.sqc"


    
/*
EXEC SQL UPDATE KEKKA
    SET (
/- 1.06 DELL
		UTKYMD,
		IRINO,
		SSTCD,
		OYAKMKCD,
		SECCD,
		SMPCD,
		BSKKBN,
		BSKGOK,
		ZRCD,
		KJNO,
		SKFLG,
		KKFLG,
		KKIRILOTNO,
		HSYKFLG,
		HSKFLG,
		HHKKFLG,
		KNSKKA1,
		KNSKKA2,
		KNSKKA2KBN,
		KKAHSKCD,
		SDI,
		KKACMT1,
		KKACMT2,
		KKAJKCD,
		PNCRGFLG,
		KKAKSFLG,
		IJKBNM,
		IJKBNF,
		IJKBNN,
		CTRLNO,
		KNSSEQ,
		PLTNO,
-/
 		KKASSFLG,
 		HKKDH,
 		KNSFLG,
 		KSNDH
    ) = (
/- 1.06 DELL
		:utkymd,
		:irino,
		:sstcd,
		:oyakmkcd,
		:seccd,
		:smpcd,
		:bskkbn,
		:bskgok,
		:zrcd,
		:kjno,
		:skflg,
		:kkflg,
		:kkirilotno,
		:hsykflg,
		:hskflg,
		:hhkkflg,
		:knskka1,
		:knskka2,
		:knskka2kbn,
		:kkahskcd,
		:sdi,
		:kkacmt1,
		:kkacmt2,
		:kkajkcd,
		:pncrgflg,
		:kkaksflg,
		:ijkbnm,
		:ijkbnf,
		:ijkbnn,
		:ctrlno,
		:knsseq,
		:pltno,
-/
		:kkassflg,
		current timestamp,
		:knsflg,
		current timestamp
    ) WHERE
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KNSSU = :knssu AND
		KNSSUEDA = :knssueda;
*/

{
#line 1485 "GD105Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1485 "GD105Kekka.sqc"
  sqlaaloc(2,9,11,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)&kkassflg;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)&knsflg;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)knskisymd;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)sriymd;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 14;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)kntno;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 17;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)knsgrp;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)kmkcd;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)&knssu;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)&knssueda;
#line 1485 "GD105Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1485 "GD105Kekka.sqc"
      sqlasetdata(2,0,9,sql_setdlist,0L,0L);
    }
#line 1485 "GD105Kekka.sqc"
  sqlacall((unsigned short)24,6,2,0,0L);
#line 1485 "GD105Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1485 "GD105Kekka.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 1485 "GD105Kekka.sqc"
  sqlastop(0L);
}

#line 1485 "GD105Kekka.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 1490 "GD105Kekka.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 1494 "GD105Kekka.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKekkaGD105UpdateOthers()
 *    KEKKA レコードを更新する
 * ■引数
 *    [I]  Kekka* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKekkaGD105UpdateOthers( Kekka* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KekkaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 1518 "GD105Kekka.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 1519 "GD105Kekka.sqc"


    
/*
EXEC SQL UPDATE KEKKA
    SET (
		KNSFLG,
		KSNDH
    ) = (
		'M',
		current timestamp
    ) WHERE
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KNSFLG <> 'E';
*/

{
#line 1534 "GD105Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1534 "GD105Kekka.sqc"
  sqlaaloc(2,5,12,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 1534 "GD105Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1534 "GD105Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 1534 "GD105Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1534 "GD105Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 1534 "GD105Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 1534 "GD105Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1534 "GD105Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 1534 "GD105Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 1534 "GD105Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1534 "GD105Kekka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 1534 "GD105Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 1534 "GD105Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1534 "GD105Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 1534 "GD105Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 1534 "GD105Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1534 "GD105Kekka.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 1534 "GD105Kekka.sqc"
  sqlacall((unsigned short)24,7,2,0,0L);
#line 1534 "GD105Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1534 "GD105Kekka.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 1534 "GD105Kekka.sqc"
  sqlastop(0L);
}

#line 1534 "GD105Kekka.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 1539 "GD105Kekka.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 1543 "GD105Kekka.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
