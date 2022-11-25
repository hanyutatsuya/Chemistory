static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,74,66,69,114,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,71,68,50,48,53,75,69,75,0,0,0,0,0,0,0,0,
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


#line 1 "GD205Kekka.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： GD205Kekka.sqc
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
 **********************************************************************/
#include <stdio.h>

#include "GD205Kekka.h"
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


#line 31 "GD205Kekka.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 36 "GD205Kekka.sqc"

	char    knskisymd[11];
	char    sriymd[11];
	char    kntno[14];
	char    kntketflg;
	char    knsgrp[17];
	char    kmkcd[8];
	short   knssu;
	short   knssueda;
	char    irihsmkbn;
	char    irikbn;
	char    ksktkbn;
	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    sstcd[8];
	char    trid[11];
	short   trpos;
	char    asyrckid[11];
	short   asyrckpos;
	char    oyakmkcd[8];
	char    seccd[3];
	char    bkfkkbn;
	char    smpcd[8];
	char    bskkbn[5];
	char    bsklne[5];
	char    bskgok[7];
	sqlint32  bskseq;
	char    bskerrsts[3];
	char    sktdh[27];
	char    nbkmkcd[8];
	char    tstrflg;
	char    zrcd[5];
	char    ysnlbl[3];
	char    kjno[4];
	char    fkhkknohjkbn;
	char    tbkjno[4];
	char    tbkjflg;
	char    htkfkhms[25];
	char    skflg;
	char    tskflg[3];
	char    tktflg[3];
	char    jisksbr[16];
	char    kkflg;
	char    kkiriflg;
	short   kkirilotno;
	char    hsykflg;
	char    hskflg;
	char    hhkkflg;
	char    rawdata[21];
	char    knskka1[13];
	char    knskka2[25];
	char    knskka2kbn[3];
	char    kkahskcd[4];
	char    hjkka[25];
	char    sdi[4];
	char    kkacmt1[6];
	char    kkacmt2[6];
	char    kkajkcd;
	char    pncrgflg;
	char    knspncrgflg;
	char    kkaksflg;
	char    kkassflg;
	char    ijkbnm;
	char    ijkbnf;
	char    ijkbnn;
	char    tbijkbnm;
	char    tbijkbnf;
	char    tbijkbnn;
	char    nbdolbl[3];
	char    nbdoerr[4];
	char    ykdolbl[3];
	char    ykdoerr[4];
	char    etclbl[3];
	char    etcerr[4];
	sqlint32  ctrlno;
	sqlint32  knsseq;
	short   bthno;
	sqlint32  pltno;
	sqlint32  pltseq;
	char    dtnrtts[9];
	char    dtnrdh[27];
	char    knskrdh[27];
	char    hkkdh[27];
	char    hkkkbdh[9];
	char    zkhkkyymd[11];
	char    zkhkkytme[5];
	char    frkkaflg;
	char    gzbsflg;
	char    hsiflg;
	char    kkaysnflg;
	char    tnyrkflg;
	char    siyflg;
	char    knsflg;
	char    renjicflg;
	char    soukn1flg;
	char    kanrenflg;
	char    bunkkuflg;
	char    kesseiflg;
	char    rirekiflg;
	char    syougoflg;
	char    keisanflg;
	char    per100flg;
	char    tousekflg;
	char    kisyakflg;
	char    kouseiflg;
	char    syoungflg;
	char    soukn2flg;
	char    fukaptflg;
	char    yobiflg01;
	char    tobiflg02;
	char    yobiflg03;
	char    yobiflg04;
	char    yobiflg05;
	char    skrycda[4];
	char    skrycdb[4];
	char    skrycdc[4];
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


/*
EXEC SQL END DECLARE SECTION;
*/

#line 186 "GD205Kekka.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Kekka

BmlDMMInfo	KekkaArray[] = {
	DMM_SDATE( knskisymd ),
	DMM_SDATE( sriymd ),
	DMM_SSTRING( kntno ),
	DMM_SCHAR( kntketflg ),
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSHORT( knssu ),
	DMM_SSHORT( knssueda ),
	DMM_SCHAR( irihsmkbn ),
	DMM_SCHAR( irikbn ),
	DMM_SCHAR( ksktkbn ),
	DMM_SDATE( utkymd ),
	DMM_SSTRING( irino ),
	DMM_SCHAR( iriketflg ),
	DMM_SSHORT( zssdino ),
	DMM_SSTRING( sstcd ),
	DMM_SSTRING( trid ),
	DMM_SSHORT( trpos ),
	DMM_SSTRING( asyrckid ),
	DMM_SSHORT( asyrckpos ),
	DMM_SSTRING( oyakmkcd ),
	DMM_SSTRING( seccd ),
	DMM_SCHAR( bkfkkbn ),
	DMM_SSTRING( smpcd ),
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( bsklne ),
	DMM_SSTRING( bskgok ),
	DMM_SLONG( bskseq ),
	DMM_SSTRING( bskerrsts ),
	DMM_STIMESTAMP( sktdh ),
	DMM_SSTRING( nbkmkcd ),
	DMM_SCHAR( tstrflg ),
	DMM_SSTRING( zrcd ),
	DMM_SSTRING( ysnlbl ),
	DMM_SSTRING( kjno ),
	DMM_SCHAR( fkhkknohjkbn ),
	DMM_SSTRING( tbkjno ),
	DMM_SCHAR( tbkjflg ),
	DMM_SSTRING( htkfkhms ),
	DMM_SCHAR( skflg ),
	DMM_SSTRING( tskflg ),
	DMM_SSTRING( tktflg ),
	DMM_SSTRING( jisksbr ),
	DMM_SCHAR( kkflg ),
	DMM_SCHAR( kkiriflg ),
	DMM_SSHORT( kkirilotno ),
	DMM_SCHAR( hsykflg ),
	DMM_SCHAR( hskflg ),
	DMM_SCHAR( hhkkflg ),
	DMM_SSTRING( rawdata ),
	DMM_SSTRING( knskka1 ),
	DMM_SSTRING( knskka2 ),
	DMM_SSTRING( knskka2kbn ),
	DMM_SSTRING( kkahskcd ),
	DMM_SSTRING( hjkka ),
	DMM_SSTRING( sdi ),
	DMM_SSTRING( kkacmt1 ),
	DMM_SSTRING( kkacmt2 ),
	DMM_SCHAR( kkajkcd ),
	DMM_SCHAR( pncrgflg ),
	DMM_SCHAR( knspncrgflg ),
	DMM_SCHAR( kkaksflg ),
	DMM_SCHAR( kkassflg ),
	DMM_SCHAR( ijkbnm ),
	DMM_SCHAR( ijkbnf ),
	DMM_SCHAR( ijkbnn ),
	DMM_SCHAR( tbijkbnm ),
	DMM_SCHAR( tbijkbnf ),
	DMM_SCHAR( tbijkbnn ),
	DMM_SSTRING( nbdolbl ),
	DMM_SSTRING( nbdoerr ),
	DMM_SSTRING( ykdolbl ),
	DMM_SSTRING( ykdoerr ),
	DMM_SSTRING( etclbl ),
	DMM_SSTRING( etcerr ),
	DMM_SLONG( ctrlno ),
	DMM_SLONG( knsseq ),
	DMM_SSHORT( bthno ),
	DMM_SLONG( pltno ),
	DMM_SLONG( pltseq ),
	DMM_SSTRING( dtnrtts ),
	DMM_STIMESTAMP( dtnrdh ),
	DMM_STIMESTAMP( knskrdh ),
	DMM_STIMESTAMP( hkkdh ),
	DMM_STIME( hkkkbdh ),
	DMM_SDATE( zkhkkyymd ),
	DMM_SSTRING( zkhkkytme ),
	DMM_SCHAR( frkkaflg ),
	DMM_SCHAR( gzbsflg ),
	DMM_SCHAR( hsiflg ),
	DMM_SCHAR( kkaysnflg ),
	DMM_SCHAR( tnyrkflg ),
	DMM_SCHAR( siyflg ),
	DMM_SCHAR( knsflg ),
	DMM_SCHAR( renjicflg ),
	DMM_SCHAR( soukn1flg ),
	DMM_SCHAR( kanrenflg ),
	DMM_SCHAR( bunkkuflg ),
	DMM_SCHAR( kesseiflg ),
	DMM_SCHAR( rirekiflg ),
	DMM_SCHAR( syougoflg ),
	DMM_SCHAR( keisanflg ),
	DMM_SCHAR( per100flg ),
	DMM_SCHAR( tousekflg ),
	DMM_SCHAR( kisyakflg ),
	DMM_SCHAR( kouseiflg ),
	DMM_SCHAR( syoungflg ),
	DMM_SCHAR( soukn2flg ),
	DMM_SCHAR( fukaptflg ),
	DMM_SCHAR( yobiflg01 ),
	DMM_SCHAR( tobiflg02 ),
	DMM_SCHAR( yobiflg03 ),
	DMM_SCHAR( yobiflg04 ),
	DMM_SCHAR( yobiflg05 ),
	DMM_SSTRING( skrycda ),
	DMM_SSTRING( skrycdb ),
	DMM_SSTRING( skrycdc ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

extern BmlDMMInfo      HkkknriArray[];

/******************************************************************************
 * ZdbKekkaGD205SelectByCtrlNo()
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
long ZdbKekkaGD205SelectByCtrlNo( Hkkknri* pKey, Kekka** arrayOut, int* numOut )
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

#line 344 "GD205Kekka.sqc"


	
/*
EXEC SQL DECLARE c3 CURSOR FOR
	SELECT
		KKA.KNSKISYMD,
		KKA.SRIYMD,
		KKA.KNTNO,
		KKA.KNTKETFLG,
		KKA.KNSGRP,
		KKA.KMKCD,
		KKA.KNSSU,
		KKA.KNSSUEDA,
		KKA.IRIHSMKBN,
		KKA.IRIKBN,
		KKA.KSKTKBN,
		KKA.UTKYMD,
		KKA.IRINO,
		KKA.IRIKETFLG,
		KKA.ZSSDINO,
		KKA.SSTCD,
		KKA.TRID,
		KKA.TRPOS,
		KKA.ASYRCKID,
		KKA.ASYRCKPOS,
		KKA.OYAKMKCD,
		KKA.SECCD,
		KKA.BKFKKBN,
		KKA.SMPCD,
		KKA.BSKKBN,
		KKA.BSKLNE,
		KKA.BSKGOK,
		KKA.BSKSEQ,
		KKA.BSKERRSTS,
		KKA.SKTDH,
		KKA.NBKMKCD,
		KKA.TSTRFLG,
		KKA.ZRCD,
		KKA.YSNLBL,
		KKA.KJNO,
		KKA.FKHKKNOHJKBN,
		KKA.TBKJNO,
		KKA.TBKJFLG,
		KKA.HTKFKHMS,
		KKA.SKFLG,
		KKA.TSKFLG,
		KKA.TKTFLG,
		KKA.JISKSBR,
		KKA.KKFLG,
		KKA.KKIRIFLG,
		KKA.KKIRILOTNO,
		KKA.HSYKFLG,
		KKA.HSKFLG,
		KKA.HHKKFLG,
		KKA.RAWDATA,
		KKA.KNSKKA1,
		KKA.KNSKKA2,
		KKA.KNSKKA2KBN,
		KKA.KKAHSKCD,
		KKA.HJKKA,
		KKA.SDI,
		KKA.KKACMT1,
		KKA.KKACMT2,
		KKA.KKAJKCD,
		KKA.PNCRGFLG,
		KKA.KNSPNCRGFLG,
		KKA.KKAKSFLG,
		KKA.KKASSFLG,
		KKA.IJKBNM,
		KKA.IJKBNF,
		KKA.IJKBNN,
		KKA.TBIJKBNM,
		KKA.TBIJKBNF,
		KKA.TBIJKBNN,
		KKA.NBDOLBL,
		KKA.NBDOERR,
		KKA.YKDOLBL,
		KKA.YKDOERR,
		KKA.ETCLBL,
		KKA.ETCERR,
		KKA.CTRLNO,
		KKA.KNSSEQ,
		KKA.BTHNO,
		KKA.PLTNO,
		KKA.PLTSEQ,
		KKA.DTNRTTS,
		KKA.DTNRDH,
		KKA.KNSKRDH,
		KKA.HKKDH,
		KKA.HKKKBDH,
		KKA.ZKHKKYYMD,
		KKA.ZKHKKYTME,
		KKA.FRKKAFLG,
		KKA.GZBSFLG,
		KKA.HSIFLG,
		KKA.KKAYSNFLG,
		KKA.TNYRKFLG,
		KKA.SIYFLG,
		KKA.KNSFLG,
		KKA.RENJICFLG,
		KKA.SOUKN1FLG,
		KKA.KANRENFLG,
		KKA.BUNKKUFLG,
		KKA.KESSEIFLG,
		KKA.RIREKIFLG,
		KKA.SYOUGOFLG,
		KKA.KEISANFLG,
		KKA.PER100FLG,
		KKA.TOUSEKFLG,
		KKA.KISYAKFLG,
		KKA.KOUSEIFLG,
		KKA.SYOUNGFLG,
		KKA.SOUKN2FLG,
		KKA.FUKAPTFLG,
		KKA.YOBIFLG01,
		KKA.TOBIFLG02,
		KKA.YOBIFLG03,
		KKA.YOBIFLG04,
		KKA.YOBIFLG05,
		KKA.SKRYCDA,
		KKA.SKRYCDB,
		KKA.SKRYCDC,
		KKA.KSNDH
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
				(SELECT KKKJSRIYMD FROM SYSKNRMST) AS KNSKISYMD,
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
			KKA.KNSKISYMD	= :knskisymd
		AND KKA.BSKKBN		= :bskkbn
		AND KKA.BSKLNE		= :bskgok
		AND KKA.KNSGRP      = :knsgrp
		AND KKA.CTRLNO		>= :ctrlnost
		AND KKA.CTRLNO		<= :ctrlnoed
		AND KKA.KKAJKCD		= :hkkkbn
		AND KKA.SECCD		= :seccd
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
	FOR READ ONLY;
*/

/*
SQL0204N  "DB2INST1.VCTRLCHK" は未定義の名前です。 
SQLSTATE=42704

*/

#line 566 "GD205Kekka.sqc"


	
/*
EXEC SQL OPEN c3;
*/

{
#line 568 "GD205Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 568 "GD205Kekka.sqc"
  sqlaaloc(2,8,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 568 "GD205Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 568 "GD205Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 568 "GD205Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 568 "GD205Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 568 "GD205Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 568 "GD205Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 568 "GD205Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 7;
#line 568 "GD205Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)bskgok;
#line 568 "GD205Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 568 "GD205Kekka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 568 "GD205Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 568 "GD205Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 568 "GD205Kekka.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 568 "GD205Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)&ctrlnost;
#line 568 "GD205Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 568 "GD205Kekka.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 568 "GD205Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)&ctrlnoed;
#line 568 "GD205Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 568 "GD205Kekka.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 568 "GD205Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&hkkkbn;
#line 568 "GD205Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 568 "GD205Kekka.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 568 "GD205Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)seccd;
#line 568 "GD205Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 568 "GD205Kekka.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 568 "GD205Kekka.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 568 "GD205Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 568 "GD205Kekka.sqc"
  sqlastop(0L);
}

#line 568 "GD205Kekka.sqc"


	while( 1 ) {
		Kekka* rec;

		
/*
EXEC SQL FETCH c3 INTO
			:knskisymd,
			:sriymd,
			:kntno,
			:kntketflg,
			:knsgrp,
			:kmkcd,
			:knssu,
			:knssueda,
			:irihsmkbn,
			:irikbn,
			:ksktkbn,
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:sstcd,
			:trid,
			:trpos,
			:asyrckid,
			:asyrckpos,
			:oyakmkcd,
			:seccd,
			:bkfkkbn,
			:smpcd,
			:bskkbn,
			:bsklne,
			:bskgok,
			:bskseq,
			:bskerrsts,
			:sktdh,
			:nbkmkcd,
			:tstrflg,
			:zrcd,
			:ysnlbl,
			:kjno,
			:fkhkknohjkbn,
			:tbkjno,
			:tbkjflg,
			:htkfkhms,
			:skflg,
			:tskflg,
			:tktflg,
			:jisksbr,
			:kkflg,
			:kkiriflg,
			:kkirilotno,
			:hsykflg,
			:hskflg,
			:hhkkflg,
			:rawdata,
			:knskka1,
			:knskka2,
			:knskka2kbn,
			:kkahskcd,
			:hjkka,
			:sdi,
			:kkacmt1,
			:kkacmt2,
			:kkajkcd,
			:pncrgflg,
			:knspncrgflg,
			:kkaksflg,
			:kkassflg,
			:ijkbnm,
			:ijkbnf,
			:ijkbnn,
			:tbijkbnm,
			:tbijkbnf,
			:tbijkbnn,
			:nbdolbl,
			:nbdoerr,
			:ykdolbl,
			:ykdoerr,
			:etclbl,
			:etcerr,
			:ctrlno,
			:knsseq,
			:bthno,
			:pltno,
			:pltseq,
			:dtnrtts,
			:dtnrdh,
			:knskrdh,
			:hkkdh,
			:hkkkbdh,
			:zkhkkyymd,
			:zkhkkytme,
			:frkkaflg,
			:gzbsflg,
			:hsiflg,
			:kkaysnflg,
			:tnyrkflg,
			:siyflg,
			:knsflg,
			:renjicflg,
			:soukn1flg,
			:kanrenflg,
			:bunkkuflg,
			:kesseiflg,
			:rirekiflg,
			:syougoflg,
			:keisanflg,
			:per100flg,
			:tousekflg,
			:kisyakflg,
			:kouseiflg,
			:syoungflg,
			:soukn2flg,
			:fukaptflg,
			:yobiflg01,
			:tobiflg02,
			:yobiflg03,
			:yobiflg04,
			:yobiflg05,
			:skrycda,
			:skrycdb,
			:skrycdc,
			:ksndh;
*/

{
#line 691 "GD205Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 691 "GD205Kekka.sqc"
  sqlaaloc(3,118,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 691 "GD205Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&knssu;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)&knssueda;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)&irihsmkbn;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)&irikbn;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)&ksktkbn;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)utkymd;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 12;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)irino;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)&iriketflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)&zssdino;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)sstcd;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 11;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)trid;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[17].sqltype = 500; sql_setdlist[17].sqllen = 2;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)&trpos;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 11;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)asyrckid;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)&asyrckpos;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 8;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)oyakmkcd;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 3;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)seccd;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)&bkfkkbn;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)smpcd;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 5;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)bskkbn;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 5;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)bsklne;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 7;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)bskgok;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[27].sqltype = 496; sql_setdlist[27].sqllen = 4;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)&bskseq;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 3;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)bskerrsts;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)sktdh;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 8;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)nbkmkcd;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&tstrflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 5;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)zrcd;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)ysnlbl;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 4;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)kjno;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&fkhkknohjkbn;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 4;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)tbkjno;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&tbkjflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 25;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)htkfkhms;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&skflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 3;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)tskflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)tktflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 16;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)jisksbr;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)&kkflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[44].sqldata = (void*)&kkiriflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[45].sqltype = 500; sql_setdlist[45].sqllen = 2;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[45].sqldata = (void*)&kkirilotno;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[46].sqldata = (void*)&hsykflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[47].sqldata = (void*)&hskflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[48].sqldata = (void*)&hhkkflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 21;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[49].sqldata = (void*)rawdata;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 13;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[50].sqldata = (void*)knskka1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 25;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[51].sqldata = (void*)knskka2;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 3;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[52].sqldata = (void*)knskka2kbn;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 4;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[53].sqldata = (void*)kkahskcd;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 25;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[54].sqldata = (void*)hjkka;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[55].sqldata = (void*)sdi;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 6;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[56].sqldata = (void*)kkacmt1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 6;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[57].sqldata = (void*)kkacmt2;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[58].sqltype = 452; sql_setdlist[58].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[58].sqldata = (void*)&kkajkcd;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[59].sqltype = 452; sql_setdlist[59].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[59].sqldata = (void*)&pncrgflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[60].sqltype = 452; sql_setdlist[60].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[60].sqldata = (void*)&knspncrgflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[61].sqltype = 452; sql_setdlist[61].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[61].sqldata = (void*)&kkaksflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[62].sqltype = 452; sql_setdlist[62].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[62].sqldata = (void*)&kkassflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[63].sqltype = 452; sql_setdlist[63].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[63].sqldata = (void*)&ijkbnm;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sqlasetdata(3,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[54];
#line 691 "GD205Kekka.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)&ijkbnf;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)&ijkbnn;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)&tbijkbnm;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)&tbijkbnf;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)&tbijkbnn;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)nbdolbl;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 4;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)nbdoerr;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)ykdolbl;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)ykdoerr;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 3;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)etclbl;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 4;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)etcerr;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)&ctrlno;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)&knsseq;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)&bthno;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)&pltno;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)&pltseq;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 9;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)dtnrtts;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)dtnrdh;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)knskrdh;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)hkkdh;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 9;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)hkkkbdh;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 11;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)zkhkkyymd;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 5;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)zkhkkytme;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)&frkkaflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)&gzbsflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)&hsiflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)&kkaysnflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)&tnyrkflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)&siyflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)&knsflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)&renjicflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&soukn1flg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)&kanrenflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)&bunkkuflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)&kesseiflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&rirekiflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)&syougoflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&keisanflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)&per100flg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&tousekflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)&kisyakflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)&kouseiflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[42].sqltype = 452; sql_setdlist[42].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)&syoungflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)&soukn2flg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[44].sqldata = (void*)&fukaptflg;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[45].sqltype = 452; sql_setdlist[45].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[45].sqldata = (void*)&yobiflg01;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[46].sqldata = (void*)&tobiflg02;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[47].sqldata = (void*)&yobiflg03;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[48].sqldata = (void*)&yobiflg04;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[49].sqltype = 452; sql_setdlist[49].sqllen = 1;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[49].sqldata = (void*)&yobiflg05;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 4;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[50].sqldata = (void*)skrycda;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 4;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[51].sqldata = (void*)skrycdb;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 4;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[52].sqldata = (void*)skrycdc;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 27;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[53].sqldata = (void*)ksndh;
#line 691 "GD205Kekka.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 691 "GD205Kekka.sqc"
      sqlasetdata(3,64,54,sql_setdlist,0L,0L);
    }
#line 691 "GD205Kekka.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 691 "GD205Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 691 "GD205Kekka.sqc"
  sqlastop(0L);
}

#line 691 "GD205Kekka.sqc"


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
EXEC SQL CLOSE c3;
*/

{
#line 706 "GD205Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 706 "GD205Kekka.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 706 "GD205Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 706 "GD205Kekka.sqc"
  sqlastop(0L);
}

#line 706 "GD205Kekka.sqc"


	*arrayOut = array;
	*numOut   = num;

	return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 714 "GD205Kekka.sqc"

printf("SQLERR : [%s]\n", sqlca.sqlerrmc);
	// 1.06 DEBUG    LOG
    sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbKekkaGD205SelectByCtrlNo",
                __LINE__,
                EXEFLG_SEL, "020",
                "SQLERR : [%s]", sqlca.sqlerrmc );

	return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKekkaGD205SelectByPltNo()
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
long ZdbKekkaGD205SelectByPltNo( Hkkknri* pKey, Kekka** arrayOut, int* numOut )
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

#line 751 "GD205Kekka.sqc"


	
/*
EXEC SQL DECLARE c4 CURSOR FOR
	SELECT
		KKA.KNSKISYMD,
		KKA.SRIYMD,
		KKA.KNTNO,
		KKA.KNTKETFLG,
		KKA.KNSGRP,
		KKA.KMKCD,
		KKA.KNSSU,
		KKA.KNSSUEDA,
		KKA.IRIHSMKBN,
		KKA.IRIKBN,
		KKA.KSKTKBN,
		KKA.UTKYMD,
		KKA.IRINO,
		KKA.IRIKETFLG,
		KKA.ZSSDINO,
		KKA.SSTCD,
		KKA.TRID,
		KKA.TRPOS,
		KKA.ASYRCKID,
		KKA.ASYRCKPOS,
		KKA.OYAKMKCD,
		KKA.SECCD,
		KKA.BKFKKBN,
		KKA.SMPCD,
		KKA.BSKKBN,
		KKA.BSKLNE,
		KKA.BSKGOK,
		KKA.BSKSEQ,
		KKA.BSKERRSTS,
		KKA.SKTDH,
		KKA.NBKMKCD,
		KKA.TSTRFLG,
		KKA.ZRCD,
		KKA.YSNLBL,
		KKA.KJNO,
		KKA.FKHKKNOHJKBN,
		KKA.TBKJNO,
		KKA.TBKJFLG,
		KKA.HTKFKHMS,
		KKA.SKFLG,
		KKA.TSKFLG,
		KKA.TKTFLG,
		KKA.JISKSBR,
		KKA.KKFLG,
		KKA.KKIRIFLG,
		KKA.KKIRILOTNO,
		KKA.HSYKFLG,
		KKA.HSKFLG,
		KKA.HHKKFLG,
		KKA.RAWDATA,
		KKA.KNSKKA1,
		KKA.KNSKKA2,
		KKA.KNSKKA2KBN,
		KKA.KKAHSKCD,
		KKA.HJKKA,
		KKA.SDI,
		KKA.KKACMT1,
		KKA.KKACMT2,
		KKA.KKAJKCD,
		KKA.PNCRGFLG,
		KKA.KNSPNCRGFLG,
		KKA.KKAKSFLG,
		KKA.KKASSFLG,
		KKA.IJKBNM,
		KKA.IJKBNF,
		KKA.IJKBNN,
		KKA.TBIJKBNM,
		KKA.TBIJKBNF,
		KKA.TBIJKBNN,
		KKA.NBDOLBL,
		KKA.NBDOERR,
		KKA.YKDOLBL,
		KKA.YKDOERR,
		KKA.ETCLBL,
		KKA.ETCERR,
		KKA.CTRLNO,
		KKA.KNSSEQ,
		KKA.BTHNO,
		KKA.PLTNO,
		KKA.PLTSEQ,
		KKA.DTNRTTS,
		KKA.DTNRDH,
		KKA.KNSKRDH,
		KKA.HKKDH,
		KKA.HKKKBDH,
		KKA.ZKHKKYYMD,
		KKA.ZKHKKYTME,
		KKA.FRKKAFLG,
		KKA.GZBSFLG,
		KKA.HSIFLG,
		KKA.KKAYSNFLG,
		KKA.TNYRKFLG,
		KKA.SIYFLG,
		KKA.KNSFLG,
		KKA.RENJICFLG,
		KKA.SOUKN1FLG,
		KKA.KANRENFLG,
		KKA.BUNKKUFLG,
		KKA.KESSEIFLG,
		KKA.RIREKIFLG,
		KKA.SYOUGOFLG,
		KKA.KEISANFLG,
		KKA.PER100FLG,
		KKA.TOUSEKFLG,
		KKA.KISYAKFLG,
		KKA.KOUSEIFLG,
		KKA.SYOUNGFLG,
		KKA.SOUKN2FLG,
		KKA.FUKAPTFLG,
		KKA.YOBIFLG01,
		KKA.TOBIFLG02,
		KKA.YOBIFLG03,
		KKA.YOBIFLG04,
		KKA.YOBIFLG05,
		KKA.SKRYCDA,
		KKA.SKRYCDB,
		KKA.SKRYCDC,
		KKA.KSNDH
	FROM
		KEKKA KKA
		LEFT OUTER JOIN (
			SELECT
				(SELECT KKKJSRIYMD FROM SYSKNRMST) AS KNSKISYMD,
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
			KKA.KNSKISYMD	= :knskisymd
		AND KKA.BSKKBN		= :bskkbn
		AND KKA.BSKLNE		= :bskgok
		AND KKA.KNSGRP		= :knsgrp
		AND KKA.KMKCD		= :kmkcd
		AND KKA.PLTNO		>= :pltnost
		AND KKA.PLTNO		<= :pltnoed
		AND KKA.KKAJKCD		= :hkkkbn
		AND KKA.SECCD		= :seccd
		AND ( KKA.IRIHSMKBN IN ('0', '1') )
		AND (
			KKA.KNSFLG = 'S'
			OR
			(
				KKA.KNSFLG = 'X'
				AND XBM.XBARMJKFLG IS NULL
			)
		)
	FOR READ ONLY;
*/

#line 916 "GD205Kekka.sqc"


	
/*
EXEC SQL OPEN c4;
*/

{
#line 918 "GD205Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 918 "GD205Kekka.sqc"
  sqlaaloc(2,9,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 918 "GD205Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 7;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)bskgok;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)&pltnost;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&pltnoed;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)&hkkkbn;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 3;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)seccd;
#line 918 "GD205Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 918 "GD205Kekka.sqc"
      sqlasetdata(2,0,9,sql_setdlist,0L,0L);
    }
#line 918 "GD205Kekka.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 918 "GD205Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 918 "GD205Kekka.sqc"
  sqlastop(0L);
}

#line 918 "GD205Kekka.sqc"


	while( 1 ) {
		Kekka* rec;

		
/*
EXEC SQL FETCH c4 INTO
			:knskisymd,
			:sriymd,
			:kntno,
			:kntketflg,
			:knsgrp,
			:kmkcd,
			:knssu,
			:knssueda,
			:irihsmkbn,
			:irikbn,
			:ksktkbn,
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:sstcd,
			:trid,
			:trpos,
			:asyrckid,
			:asyrckpos,
			:oyakmkcd,
			:seccd,
			:bkfkkbn,
			:smpcd,
			:bskkbn,
			:bsklne,
			:bskgok,
			:bskseq,
			:bskerrsts,
			:sktdh,
			:nbkmkcd,
			:tstrflg,
			:zrcd,
			:ysnlbl,
			:kjno,
			:fkhkknohjkbn,
			:tbkjno,
			:tbkjflg,
			:htkfkhms,
			:skflg,
			:tskflg,
			:tktflg,
			:jisksbr,
			:kkflg,
			:kkiriflg,
			:kkirilotno,
			:hsykflg,
			:hskflg,
			:hhkkflg,
			:rawdata,
			:knskka1,
			:knskka2,
			:knskka2kbn,
			:kkahskcd,
			:hjkka,
			:sdi,
			:kkacmt1,
			:kkacmt2,
			:kkajkcd,
			:pncrgflg,
			:knspncrgflg,
			:kkaksflg,
			:kkassflg,
			:ijkbnm,
			:ijkbnf,
			:ijkbnn,
			:tbijkbnm,
			:tbijkbnf,
			:tbijkbnn,
			:nbdolbl,
			:nbdoerr,
			:ykdolbl,
			:ykdoerr,
			:etclbl,
			:etcerr,
			:ctrlno,
			:knsseq,
			:bthno,
			:pltno,
			:pltseq,
			:dtnrtts,
			:dtnrdh,
			:knskrdh,
			:hkkdh,
			:hkkkbdh,
			:zkhkkyymd,
			:zkhkkytme,
			:frkkaflg,
			:gzbsflg,
			:hsiflg,
			:kkaysnflg,
			:tnyrkflg,
			:siyflg,
			:knsflg,
			:renjicflg,
			:soukn1flg,
			:kanrenflg,
			:bunkkuflg,
			:kesseiflg,
			:rirekiflg,
			:syougoflg,
			:keisanflg,
			:per100flg,
			:tousekflg,
			:kisyakflg,
			:kouseiflg,
			:syoungflg,
			:soukn2flg,
			:fukaptflg,
			:yobiflg01,
			:tobiflg02,
			:yobiflg03,
			:yobiflg04,
			:yobiflg05,
			:skrycda,
			:skrycdb,
			:skrycdc,
			:ksndh;
*/

{
#line 1041 "GD205Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1041 "GD205Kekka.sqc"
  sqlaaloc(3,118,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&knssu;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)&knssueda;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)&irihsmkbn;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)&irikbn;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)&ksktkbn;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)utkymd;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 12;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)irino;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)&iriketflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)&zssdino;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)sstcd;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 11;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)trid;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[17].sqltype = 500; sql_setdlist[17].sqllen = 2;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)&trpos;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 11;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)asyrckid;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)&asyrckpos;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 8;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)oyakmkcd;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 3;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)seccd;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)&bkfkkbn;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)smpcd;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 5;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)bskkbn;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 5;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)bsklne;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 7;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)bskgok;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[27].sqltype = 496; sql_setdlist[27].sqllen = 4;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)&bskseq;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 3;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)bskerrsts;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)sktdh;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 8;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)nbkmkcd;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&tstrflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 5;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)zrcd;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)ysnlbl;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 4;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)kjno;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&fkhkknohjkbn;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 4;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)tbkjno;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&tbkjflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 25;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)htkfkhms;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&skflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 3;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)tskflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)tktflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 16;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)jisksbr;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)&kkflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[44].sqldata = (void*)&kkiriflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[45].sqltype = 500; sql_setdlist[45].sqllen = 2;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[45].sqldata = (void*)&kkirilotno;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[46].sqldata = (void*)&hsykflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[47].sqldata = (void*)&hskflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[48].sqldata = (void*)&hhkkflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 21;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[49].sqldata = (void*)rawdata;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 13;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[50].sqldata = (void*)knskka1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 25;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[51].sqldata = (void*)knskka2;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 3;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[52].sqldata = (void*)knskka2kbn;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 4;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[53].sqldata = (void*)kkahskcd;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 25;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[54].sqldata = (void*)hjkka;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[55].sqldata = (void*)sdi;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 6;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[56].sqldata = (void*)kkacmt1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 6;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[57].sqldata = (void*)kkacmt2;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[58].sqltype = 452; sql_setdlist[58].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[58].sqldata = (void*)&kkajkcd;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[59].sqltype = 452; sql_setdlist[59].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[59].sqldata = (void*)&pncrgflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[60].sqltype = 452; sql_setdlist[60].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[60].sqldata = (void*)&knspncrgflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[61].sqltype = 452; sql_setdlist[61].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[61].sqldata = (void*)&kkaksflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[62].sqltype = 452; sql_setdlist[62].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[62].sqldata = (void*)&kkassflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[63].sqltype = 452; sql_setdlist[63].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[63].sqldata = (void*)&ijkbnm;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sqlasetdata(3,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[54];
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)&ijkbnf;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)&ijkbnn;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)&tbijkbnm;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)&tbijkbnf;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)&tbijkbnn;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)nbdolbl;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 4;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)nbdoerr;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)ykdolbl;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)ykdoerr;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 3;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)etclbl;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 4;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)etcerr;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)&ctrlno;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)&knsseq;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)&bthno;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)&pltno;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)&pltseq;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 9;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)dtnrtts;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)dtnrdh;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)knskrdh;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)hkkdh;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 9;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)hkkkbdh;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 11;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)zkhkkyymd;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 5;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)zkhkkytme;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)&frkkaflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)&gzbsflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)&hsiflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)&kkaysnflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)&tnyrkflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)&siyflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)&knsflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)&renjicflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&soukn1flg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)&kanrenflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)&bunkkuflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)&kesseiflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&rirekiflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)&syougoflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&keisanflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)&per100flg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&tousekflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)&kisyakflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)&kouseiflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[42].sqltype = 452; sql_setdlist[42].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)&syoungflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)&soukn2flg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[44].sqldata = (void*)&fukaptflg;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[45].sqltype = 452; sql_setdlist[45].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[45].sqldata = (void*)&yobiflg01;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[46].sqldata = (void*)&tobiflg02;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[47].sqldata = (void*)&yobiflg03;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[48].sqldata = (void*)&yobiflg04;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[49].sqltype = 452; sql_setdlist[49].sqllen = 1;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[49].sqldata = (void*)&yobiflg05;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 4;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[50].sqldata = (void*)skrycda;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 4;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[51].sqldata = (void*)skrycdb;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 4;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[52].sqldata = (void*)skrycdc;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 27;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[53].sqldata = (void*)ksndh;
#line 1041 "GD205Kekka.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 1041 "GD205Kekka.sqc"
      sqlasetdata(3,64,54,sql_setdlist,0L,0L);
    }
#line 1041 "GD205Kekka.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 1041 "GD205Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1041 "GD205Kekka.sqc"
  sqlastop(0L);
}

#line 1041 "GD205Kekka.sqc"


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
#line 1056 "GD205Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1056 "GD205Kekka.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 1056 "GD205Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1056 "GD205Kekka.sqc"
  sqlastop(0L);
}

#line 1056 "GD205Kekka.sqc"


	*arrayOut = array;
	*numOut   = num;

	return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 1064 "GD205Kekka.sqc"

//1.06 DELL printf("SQLERR : [%s]\n", sqlca.sqlerrmc);
	// 1.06 DEBUG    LOG
    sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbKekkaGD205SelectByPltNo",
                __LINE__,
                EXEFLG_SEL, "020",
                "SQLERR : [%s]", sqlca.sqlerrmc );

	return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKekkaGD205SelectByKnsSeq()
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
long ZdbKekkaGD205SelectByKnsSeq( Hkkknri* pKey, Kekka** arrayOut, int* numOut )
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

#line 1101 "GD205Kekka.sqc"


	
/*
EXEC SQL DECLARE c5 CURSOR FOR
	SELECT
		KKA.KNSKISYMD,
		KKA.SRIYMD,
		KKA.KNTNO,
		KKA.KNTKETFLG,
		KKA.KNSGRP,
		KKA.KMKCD,
		KKA.KNSSU,
		KKA.KNSSUEDA,
		KKA.IRIHSMKBN,
		KKA.IRIKBN,
		KKA.KSKTKBN,
		KKA.UTKYMD,
		KKA.IRINO,
		KKA.IRIKETFLG,
		KKA.ZSSDINO,
		KKA.SSTCD,
		KKA.TRID,
		KKA.TRPOS,
		KKA.ASYRCKID,
		KKA.ASYRCKPOS,
		KKA.OYAKMKCD,
		KKA.SECCD,
		KKA.BKFKKBN,
		KKA.SMPCD,
		KKA.BSKKBN,
		KKA.BSKLNE,
		KKA.BSKGOK,
		KKA.BSKSEQ,
		KKA.BSKERRSTS,
		KKA.SKTDH,
		KKA.NBKMKCD,
		KKA.TSTRFLG,
		KKA.ZRCD,
		KKA.YSNLBL,
		KKA.KJNO,
		KKA.FKHKKNOHJKBN,
		KKA.TBKJNO,
		KKA.TBKJFLG,
		KKA.HTKFKHMS,
		KKA.SKFLG,
		KKA.TSKFLG,
		KKA.TKTFLG,
		KKA.JISKSBR,
		KKA.KKFLG,
		KKA.KKIRIFLG,
		KKA.KKIRILOTNO,
		KKA.HSYKFLG,
		KKA.HSKFLG,
		KKA.HHKKFLG,
		KKA.RAWDATA,
		KKA.KNSKKA1,
		KKA.KNSKKA2,
		KKA.KNSKKA2KBN,
		KKA.KKAHSKCD,
		KKA.HJKKA,
		KKA.SDI,
		KKA.KKACMT1,
		KKA.KKACMT2,
		KKA.KKAJKCD,
		KKA.PNCRGFLG,
		KKA.KNSPNCRGFLG,
		KKA.KKAKSFLG,
		KKA.KKASSFLG,
		KKA.IJKBNM,
		KKA.IJKBNF,
		KKA.IJKBNN,
		KKA.TBIJKBNM,
		KKA.TBIJKBNF,
		KKA.TBIJKBNN,
		KKA.NBDOLBL,
		KKA.NBDOERR,
		KKA.YKDOLBL,
		KKA.YKDOERR,
		KKA.ETCLBL,
		KKA.ETCERR,
		KKA.CTRLNO,
		KKA.KNSSEQ,
		KKA.BTHNO,
		KKA.PLTNO,
		KKA.PLTSEQ,
		KKA.DTNRTTS,
		KKA.DTNRDH,
		KKA.KNSKRDH,
		KKA.HKKDH,
		KKA.HKKKBDH,
		KKA.ZKHKKYYMD,
		KKA.ZKHKKYTME,
		KKA.FRKKAFLG,
		KKA.GZBSFLG,
		KKA.HSIFLG,
		KKA.KKAYSNFLG,
		KKA.TNYRKFLG,
		KKA.SIYFLG,
		KKA.KNSFLG,
		KKA.RENJICFLG,
		KKA.SOUKN1FLG,
		KKA.KANRENFLG,
		KKA.BUNKKUFLG,
		KKA.KESSEIFLG,
		KKA.RIREKIFLG,
		KKA.SYOUGOFLG,
		KKA.KEISANFLG,
		KKA.PER100FLG,
		KKA.TOUSEKFLG,
		KKA.KISYAKFLG,
		KKA.KOUSEIFLG,
		KKA.SYOUNGFLG,
		KKA.SOUKN2FLG,
		KKA.FUKAPTFLG,
		KKA.YOBIFLG01,
		KKA.TOBIFLG02,
		KKA.YOBIFLG03,
		KKA.YOBIFLG04,
		KKA.YOBIFLG05,
		KKA.SKRYCDA,
		KKA.SKRYCDB,
		KKA.SKRYCDC,
		KKA.KSNDH
	FROM
		KEKKA KKA
		LEFT OUTER JOIN VCTRLCHK CTC
			ON KKA.KNSKISYMD = CTC.KNSKISYMD
			AND KKA.BSKKBN = CTC.BSKKBN
			AND KKA.BSKLNE = CTC.BSKLNE
			AND KKA.CTRLNO = CTC.CTRLNO
		LEFT OUTER JOIN (
			SELECT
				(SELECT KKKJSRIYMD FROM SYSKNRMST) AS KNSKISYMD,
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
			KKA.KNSKISYMD	= :knskisymd
		AND KKA.KNSGRP		= :knsgrp
		AND KKA.KNSSEQ		>= :knsseqst
		AND KKA.KNSSEQ		<= :knsseqed
		AND KKA.KKAJKCD		= :hkkkbn
		AND KKA.SECCD		= :seccd
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
	FOR READ ONLY;
*/

/*
SQL0204N  "DB2INST1.VCTRLCHK" は未定義の名前です。 
SQLSTATE=42704

*/

#line 1271 "GD205Kekka.sqc"


	
/*
EXEC SQL OPEN c5;
*/

{
#line 1273 "GD205Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1273 "GD205Kekka.sqc"
  sqlaaloc(2,6,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 1273 "GD205Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1273 "GD205Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 1273 "GD205Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1273 "GD205Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 1273 "GD205Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 1273 "GD205Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1273 "GD205Kekka.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 1273 "GD205Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)&knsseqst;
#line 1273 "GD205Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1273 "GD205Kekka.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 1273 "GD205Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)&knsseqed;
#line 1273 "GD205Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1273 "GD205Kekka.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 1273 "GD205Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)&hkkkbn;
#line 1273 "GD205Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1273 "GD205Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 1273 "GD205Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)seccd;
#line 1273 "GD205Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1273 "GD205Kekka.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 1273 "GD205Kekka.sqc"
  sqlacall((unsigned short)26,3,2,0,0L);
#line 1273 "GD205Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1273 "GD205Kekka.sqc"
  sqlastop(0L);
}

#line 1273 "GD205Kekka.sqc"


	while( 1 ) {
		Kekka* rec;

		
/*
EXEC SQL FETCH c5 INTO
			:knskisymd,
			:sriymd,
			:kntno,
			:kntketflg,
			:knsgrp,
			:kmkcd,
			:knssu,
			:knssueda,
			:irihsmkbn,
			:irikbn,
			:ksktkbn,
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:sstcd,
			:trid,
			:trpos,
			:asyrckid,
			:asyrckpos,
			:oyakmkcd,
			:seccd,
			:bkfkkbn,
			:smpcd,
			:bskkbn,
			:bsklne,
			:bskgok,
			:bskseq,
			:bskerrsts,
			:sktdh,
			:nbkmkcd,
			:tstrflg,
			:zrcd,
			:ysnlbl,
			:kjno,
			:fkhkknohjkbn,
			:tbkjno,
			:tbkjflg,
			:htkfkhms,
			:skflg,
			:tskflg,
			:tktflg,
			:jisksbr,
			:kkflg,
			:kkiriflg,
			:kkirilotno,
			:hsykflg,
			:hskflg,
			:hhkkflg,
			:rawdata,
			:knskka1,
			:knskka2,
			:knskka2kbn,
			:kkahskcd,
			:hjkka,
			:sdi,
			:kkacmt1,
			:kkacmt2,
			:kkajkcd,
			:pncrgflg,
			:knspncrgflg,
			:kkaksflg,
			:kkassflg,
			:ijkbnm,
			:ijkbnf,
			:ijkbnn,
			:tbijkbnm,
			:tbijkbnf,
			:tbijkbnn,
			:nbdolbl,
			:nbdoerr,
			:ykdolbl,
			:ykdoerr,
			:etclbl,
			:etcerr,
			:ctrlno,
			:knsseq,
			:bthno,
			:pltno,
			:pltseq,
			:dtnrtts,
			:dtnrdh,
			:knskrdh,
			:hkkdh,
			:hkkkbdh,
			:zkhkkyymd,
			:zkhkkytme,
			:frkkaflg,
			:gzbsflg,
			:hsiflg,
			:kkaysnflg,
			:tnyrkflg,
			:siyflg,
			:knsflg,
			:renjicflg,
			:soukn1flg,
			:kanrenflg,
			:bunkkuflg,
			:kesseiflg,
			:rirekiflg,
			:syougoflg,
			:keisanflg,
			:per100flg,
			:tousekflg,
			:kisyakflg,
			:kouseiflg,
			:syoungflg,
			:soukn2flg,
			:fukaptflg,
			:yobiflg01,
			:tobiflg02,
			:yobiflg03,
			:yobiflg04,
			:yobiflg05,
			:skrycda,
			:skrycdb,
			:skrycdc,
			:ksndh;
*/

{
#line 1396 "GD205Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1396 "GD205Kekka.sqc"
  sqlaaloc(3,118,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&knssu;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)&knssueda;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)&irihsmkbn;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)&irikbn;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)&ksktkbn;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)utkymd;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 12;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)irino;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)&iriketflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)&zssdino;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)sstcd;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 11;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)trid;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[17].sqltype = 500; sql_setdlist[17].sqllen = 2;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)&trpos;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 11;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)asyrckid;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)&asyrckpos;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 8;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)oyakmkcd;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 3;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)seccd;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)&bkfkkbn;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)smpcd;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 5;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)bskkbn;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 5;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)bsklne;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 7;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)bskgok;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[27].sqltype = 496; sql_setdlist[27].sqllen = 4;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)&bskseq;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 3;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)bskerrsts;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)sktdh;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 8;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)nbkmkcd;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&tstrflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 5;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)zrcd;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)ysnlbl;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 4;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)kjno;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&fkhkknohjkbn;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 4;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)tbkjno;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&tbkjflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 25;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)htkfkhms;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&skflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 3;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)tskflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)tktflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 16;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)jisksbr;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)&kkflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[44].sqldata = (void*)&kkiriflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[45].sqltype = 500; sql_setdlist[45].sqllen = 2;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[45].sqldata = (void*)&kkirilotno;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[46].sqldata = (void*)&hsykflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[47].sqldata = (void*)&hskflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[48].sqldata = (void*)&hhkkflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 21;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[49].sqldata = (void*)rawdata;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 13;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[50].sqldata = (void*)knskka1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 25;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[51].sqldata = (void*)knskka2;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 3;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[52].sqldata = (void*)knskka2kbn;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 4;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[53].sqldata = (void*)kkahskcd;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 25;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[54].sqldata = (void*)hjkka;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[55].sqldata = (void*)sdi;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 6;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[56].sqldata = (void*)kkacmt1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 6;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[57].sqldata = (void*)kkacmt2;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[58].sqltype = 452; sql_setdlist[58].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[58].sqldata = (void*)&kkajkcd;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[59].sqltype = 452; sql_setdlist[59].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[59].sqldata = (void*)&pncrgflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[60].sqltype = 452; sql_setdlist[60].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[60].sqldata = (void*)&knspncrgflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[61].sqltype = 452; sql_setdlist[61].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[61].sqldata = (void*)&kkaksflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[62].sqltype = 452; sql_setdlist[62].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[62].sqldata = (void*)&kkassflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[63].sqltype = 452; sql_setdlist[63].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[63].sqldata = (void*)&ijkbnm;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sqlasetdata(3,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[54];
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)&ijkbnf;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)&ijkbnn;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)&tbijkbnm;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)&tbijkbnf;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)&tbijkbnn;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)nbdolbl;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 4;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)nbdoerr;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)ykdolbl;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)ykdoerr;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 3;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)etclbl;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 4;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)etcerr;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)&ctrlno;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)&knsseq;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)&bthno;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)&pltno;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)&pltseq;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 9;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)dtnrtts;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)dtnrdh;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)knskrdh;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)hkkdh;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 9;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)hkkkbdh;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 11;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)zkhkkyymd;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 5;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)zkhkkytme;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)&frkkaflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)&gzbsflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)&hsiflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)&kkaysnflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)&tnyrkflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)&siyflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)&knsflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)&renjicflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&soukn1flg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)&kanrenflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)&bunkkuflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)&kesseiflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&rirekiflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)&syougoflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&keisanflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)&per100flg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&tousekflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)&kisyakflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)&kouseiflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[42].sqltype = 452; sql_setdlist[42].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)&syoungflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)&soukn2flg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[44].sqldata = (void*)&fukaptflg;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[45].sqltype = 452; sql_setdlist[45].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[45].sqldata = (void*)&yobiflg01;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[46].sqldata = (void*)&tobiflg02;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[47].sqldata = (void*)&yobiflg03;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[48].sqldata = (void*)&yobiflg04;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[49].sqltype = 452; sql_setdlist[49].sqllen = 1;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[49].sqldata = (void*)&yobiflg05;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 4;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[50].sqldata = (void*)skrycda;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 4;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[51].sqldata = (void*)skrycdb;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 4;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[52].sqldata = (void*)skrycdc;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 27;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[53].sqldata = (void*)ksndh;
#line 1396 "GD205Kekka.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 1396 "GD205Kekka.sqc"
      sqlasetdata(3,64,54,sql_setdlist,0L,0L);
    }
#line 1396 "GD205Kekka.sqc"
  sqlacall((unsigned short)25,3,0,3,0L);
#line 1396 "GD205Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1396 "GD205Kekka.sqc"
  sqlastop(0L);
}

#line 1396 "GD205Kekka.sqc"


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
#line 1411 "GD205Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1411 "GD205Kekka.sqc"
  sqlacall((unsigned short)20,3,0,0,0L);
#line 1411 "GD205Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1411 "GD205Kekka.sqc"
  sqlastop(0L);
}

#line 1411 "GD205Kekka.sqc"


	*arrayOut = array;
	*numOut   = num;

	return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 1419 "GD205Kekka.sqc"

//1.06 DELL printf("SQLERR : [%s]\n", sqlca.sqlerrmc);
	// 1.06 DEBUG    LOG
    sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbKekkaGD205SelectByKnsSeq",
                __LINE__,
                EXEFLG_SEL, "020",
                "SQLERR : [%s]", sqlca.sqlerrmc );

	return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKekkaGD205SelectByIriNo()
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
long ZdbKekkaGD205SelectByIriNo( Hkkknri* pKey, Kekka** arrayOut, int* numOut )
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

#line 1458 "GD205Kekka.sqc"


	
/*
EXEC SQL DECLARE c6 CURSOR FOR
	SELECT
		KKA.KNSKISYMD,
		KKA.SRIYMD,
		KKA.KNTNO,
		KKA.KNTKETFLG,
		KKA.KNSGRP,
		KKA.KMKCD,
		KKA.KNSSU,
		KKA.KNSSUEDA,
		KKA.IRIHSMKBN,
		KKA.IRIKBN,
		KKA.KSKTKBN,
		KKA.UTKYMD,
		KKA.IRINO,
		KKA.IRIKETFLG,
		KKA.ZSSDINO,
		KKA.SSTCD,
		KKA.TRID,
		KKA.TRPOS,
		KKA.ASYRCKID,
		KKA.ASYRCKPOS,
		KKA.OYAKMKCD,
		KKA.SECCD,
		KKA.BKFKKBN,
		KKA.SMPCD,
		KKA.BSKKBN,
		KKA.BSKLNE,
		KKA.BSKGOK,
		KKA.BSKSEQ,
		KKA.BSKERRSTS,
		KKA.SKTDH,
		KKA.NBKMKCD,
		KKA.TSTRFLG,
		KKA.ZRCD,
		KKA.YSNLBL,
		KKA.KJNO,
		KKA.FKHKKNOHJKBN,
		KKA.TBKJNO,
		KKA.TBKJFLG,
		KKA.HTKFKHMS,
		KKA.SKFLG,
		KKA.TSKFLG,
		KKA.TKTFLG,
		KKA.JISKSBR,
		KKA.KKFLG,
		KKA.KKIRIFLG,
		KKA.KKIRILOTNO,
		KKA.HSYKFLG,
		KKA.HSKFLG,
		KKA.HHKKFLG,
		KKA.RAWDATA,
		KKA.KNSKKA1,
		KKA.KNSKKA2,
		KKA.KNSKKA2KBN,
		KKA.KKAHSKCD,
		KKA.HJKKA,
		KKA.SDI,
		KKA.KKACMT1,
		KKA.KKACMT2,
		KKA.KKAJKCD,
		KKA.PNCRGFLG,
		KKA.KNSPNCRGFLG,
		KKA.KKAKSFLG,
		KKA.KKASSFLG,
		KKA.IJKBNM,
		KKA.IJKBNF,
		KKA.IJKBNN,
		KKA.TBIJKBNM,
		KKA.TBIJKBNF,
		KKA.TBIJKBNN,
		KKA.NBDOLBL,
		KKA.NBDOERR,
		KKA.YKDOLBL,
		KKA.YKDOERR,
		KKA.ETCLBL,
		KKA.ETCERR,
		KKA.CTRLNO,
		KKA.KNSSEQ,
		KKA.BTHNO,
		KKA.PLTNO,
		KKA.PLTSEQ,
		KKA.DTNRTTS,
		KKA.DTNRDH,
		KKA.KNSKRDH,
		KKA.HKKDH,
		KKA.HKKKBDH,
		KKA.ZKHKKYYMD,
		KKA.ZKHKKYTME,
		KKA.FRKKAFLG,
		KKA.GZBSFLG,
		KKA.HSIFLG,
		KKA.KKAYSNFLG,
		KKA.TNYRKFLG,
		KKA.SIYFLG,
		KKA.KNSFLG,
		KKA.RENJICFLG,
		KKA.SOUKN1FLG,
		KKA.KANRENFLG,
		KKA.BUNKKUFLG,
		KKA.KESSEIFLG,
		KKA.RIREKIFLG,
		KKA.SYOUGOFLG,
		KKA.KEISANFLG,
		KKA.PER100FLG,
		KKA.TOUSEKFLG,
		KKA.KISYAKFLG,
		KKA.KOUSEIFLG,
		KKA.SYOUNGFLG,
		KKA.SOUKN2FLG,
		KKA.FUKAPTFLG,
		KKA.YOBIFLG01,
		KKA.TOBIFLG02,
		KKA.YOBIFLG03,
		KKA.YOBIFLG04,
		KKA.YOBIFLG05,
		KKA.SKRYCDA,
		KKA.SKRYCDB,
		KKA.SKRYCDC,
		KKA.KSNDH
	FROM
		KEKKA KKA
		LEFT OUTER JOIN VCTRLCHK CTC
			ON KKA.KNSKISYMD = CTC.KNSKISYMD
			AND KKA.BSKKBN = CTC.BSKKBN
			AND KKA.BSKLNE = CTC.BSKLNE
			AND KKA.CTRLNO = CTC.CTRLNO
		LEFT OUTER JOIN (
			SELECT
				(SELECT KKKJSRIYMD FROM SYSKNRMST) AS KNSKISYMD,
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
			KKA.UTKYMD		= :utkymd
		AND KKA.KNSGRP		= :knsgrp
		AND KKA.IRINO		>= :irinost
		AND KKA.IRINO		<= :irinoed
		AND KKA.KKAJKCD		= :hkkkbn
		AND KKA.SECCD		= :seccd
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
	FOR READ ONLY;
*/

/*
SQL0204N  "DB2INST1.VCTRLCHK" は未定義の名前です。 
SQLSTATE=42704

*/

#line 1628 "GD205Kekka.sqc"


	
/*
EXEC SQL OPEN c6;
*/

{
#line 1630 "GD205Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1630 "GD205Kekka.sqc"
  sqlaaloc(2,6,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 1630 "GD205Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1630 "GD205Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 1630 "GD205Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1630 "GD205Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 1630 "GD205Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 1630 "GD205Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1630 "GD205Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 12;
#line 1630 "GD205Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)irinost;
#line 1630 "GD205Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1630 "GD205Kekka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 12;
#line 1630 "GD205Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)irinoed;
#line 1630 "GD205Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1630 "GD205Kekka.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 1630 "GD205Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)&hkkkbn;
#line 1630 "GD205Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1630 "GD205Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 1630 "GD205Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)seccd;
#line 1630 "GD205Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1630 "GD205Kekka.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 1630 "GD205Kekka.sqc"
  sqlacall((unsigned short)26,4,2,0,0L);
#line 1630 "GD205Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1630 "GD205Kekka.sqc"
  sqlastop(0L);
}

#line 1630 "GD205Kekka.sqc"


	while( 1 ) {
		Kekka* rec;

		
/*
EXEC SQL FETCH c6 INTO
			:knskisymd,
			:sriymd,
			:kntno,
			:kntketflg,
			:knsgrp,
			:kmkcd,
			:knssu,
			:knssueda,
			:irihsmkbn,
			:irikbn,
			:ksktkbn,
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:sstcd,
			:trid,
			:trpos,
			:asyrckid,
			:asyrckpos,
			:oyakmkcd,
			:seccd,
			:bkfkkbn,
			:smpcd,
			:bskkbn,
			:bsklne,
			:bskgok,
			:bskseq,
			:bskerrsts,
			:sktdh,
			:nbkmkcd,
			:tstrflg,
			:zrcd,
			:ysnlbl,
			:kjno,
			:fkhkknohjkbn,
			:tbkjno,
			:tbkjflg,
			:htkfkhms,
			:skflg,
			:tskflg,
			:tktflg,
			:jisksbr,
			:kkflg,
			:kkiriflg,
			:kkirilotno,
			:hsykflg,
			:hskflg,
			:hhkkflg,
			:rawdata,
			:knskka1,
			:knskka2,
			:knskka2kbn,
			:kkahskcd,
			:hjkka,
			:sdi,
			:kkacmt1,
			:kkacmt2,
			:kkajkcd,
			:pncrgflg,
			:knspncrgflg,
			:kkaksflg,
			:kkassflg,
			:ijkbnm,
			:ijkbnf,
			:ijkbnn,
			:tbijkbnm,
			:tbijkbnf,
			:tbijkbnn,
			:nbdolbl,
			:nbdoerr,
			:ykdolbl,
			:ykdoerr,
			:etclbl,
			:etcerr,
			:ctrlno,
			:knsseq,
			:bthno,
			:pltno,
			:pltseq,
			:dtnrtts,
			:dtnrdh,
			:knskrdh,
			:hkkdh,
			:hkkkbdh,
			:zkhkkyymd,
			:zkhkkytme,
			:frkkaflg,
			:gzbsflg,
			:hsiflg,
			:kkaysnflg,
			:tnyrkflg,
			:siyflg,
			:knsflg,
			:renjicflg,
			:soukn1flg,
			:kanrenflg,
			:bunkkuflg,
			:kesseiflg,
			:rirekiflg,
			:syougoflg,
			:keisanflg,
			:per100flg,
			:tousekflg,
			:kisyakflg,
			:kouseiflg,
			:syoungflg,
			:soukn2flg,
			:fukaptflg,
			:yobiflg01,
			:tobiflg02,
			:yobiflg03,
			:yobiflg04,
			:yobiflg05,
			:skrycda,
			:skrycdb,
			:skrycdc,
			:ksndh;
*/

{
#line 1753 "GD205Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1753 "GD205Kekka.sqc"
  sqlaaloc(3,118,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&knssu;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)&knssueda;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)&irihsmkbn;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)&irikbn;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)&ksktkbn;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)utkymd;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 12;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)irino;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)&iriketflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)&zssdino;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)sstcd;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 11;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)trid;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[17].sqltype = 500; sql_setdlist[17].sqllen = 2;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)&trpos;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 11;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)asyrckid;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)&asyrckpos;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 8;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)oyakmkcd;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 3;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)seccd;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)&bkfkkbn;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)smpcd;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 5;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)bskkbn;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 5;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)bsklne;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 7;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)bskgok;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[27].sqltype = 496; sql_setdlist[27].sqllen = 4;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)&bskseq;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 3;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)bskerrsts;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)sktdh;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 8;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)nbkmkcd;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&tstrflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 5;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)zrcd;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)ysnlbl;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 4;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)kjno;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&fkhkknohjkbn;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 4;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)tbkjno;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&tbkjflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 25;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)htkfkhms;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&skflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 3;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)tskflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)tktflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 16;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)jisksbr;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)&kkflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[44].sqldata = (void*)&kkiriflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[45].sqltype = 500; sql_setdlist[45].sqllen = 2;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[45].sqldata = (void*)&kkirilotno;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[46].sqldata = (void*)&hsykflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[47].sqldata = (void*)&hskflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[48].sqldata = (void*)&hhkkflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 21;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[49].sqldata = (void*)rawdata;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 13;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[50].sqldata = (void*)knskka1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 25;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[51].sqldata = (void*)knskka2;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 3;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[52].sqldata = (void*)knskka2kbn;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 4;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[53].sqldata = (void*)kkahskcd;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 25;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[54].sqldata = (void*)hjkka;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[55].sqldata = (void*)sdi;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 6;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[56].sqldata = (void*)kkacmt1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 6;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[57].sqldata = (void*)kkacmt2;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[58].sqltype = 452; sql_setdlist[58].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[58].sqldata = (void*)&kkajkcd;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[59].sqltype = 452; sql_setdlist[59].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[59].sqldata = (void*)&pncrgflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[60].sqltype = 452; sql_setdlist[60].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[60].sqldata = (void*)&knspncrgflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[61].sqltype = 452; sql_setdlist[61].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[61].sqldata = (void*)&kkaksflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[62].sqltype = 452; sql_setdlist[62].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[62].sqldata = (void*)&kkassflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[63].sqltype = 452; sql_setdlist[63].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[63].sqldata = (void*)&ijkbnm;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sqlasetdata(3,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[54];
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)&ijkbnf;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)&ijkbnn;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)&tbijkbnm;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)&tbijkbnf;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)&tbijkbnn;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)nbdolbl;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 4;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)nbdoerr;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)ykdolbl;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)ykdoerr;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 3;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)etclbl;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 4;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)etcerr;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)&ctrlno;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)&knsseq;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)&bthno;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)&pltno;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)&pltseq;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 9;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)dtnrtts;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)dtnrdh;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)knskrdh;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)hkkdh;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 9;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)hkkkbdh;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 11;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)zkhkkyymd;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 5;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)zkhkkytme;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)&frkkaflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)&gzbsflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)&hsiflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)&kkaysnflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)&tnyrkflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)&siyflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)&knsflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)&renjicflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&soukn1flg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)&kanrenflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)&bunkkuflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)&kesseiflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&rirekiflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)&syougoflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&keisanflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)&per100flg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&tousekflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)&kisyakflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)&kouseiflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[42].sqltype = 452; sql_setdlist[42].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)&syoungflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)&soukn2flg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[44].sqldata = (void*)&fukaptflg;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[45].sqltype = 452; sql_setdlist[45].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[45].sqldata = (void*)&yobiflg01;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[46].sqldata = (void*)&tobiflg02;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[47].sqldata = (void*)&yobiflg03;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[48].sqldata = (void*)&yobiflg04;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[49].sqltype = 452; sql_setdlist[49].sqllen = 1;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[49].sqldata = (void*)&yobiflg05;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 4;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[50].sqldata = (void*)skrycda;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 4;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[51].sqldata = (void*)skrycdb;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 4;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[52].sqldata = (void*)skrycdc;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 27;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[53].sqldata = (void*)ksndh;
#line 1753 "GD205Kekka.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 1753 "GD205Kekka.sqc"
      sqlasetdata(3,64,54,sql_setdlist,0L,0L);
    }
#line 1753 "GD205Kekka.sqc"
  sqlacall((unsigned short)25,4,0,3,0L);
#line 1753 "GD205Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1753 "GD205Kekka.sqc"
  sqlastop(0L);
}

#line 1753 "GD205Kekka.sqc"


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
#line 1768 "GD205Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1768 "GD205Kekka.sqc"
  sqlacall((unsigned short)20,4,0,0,0L);
#line 1768 "GD205Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1768 "GD205Kekka.sqc"
  sqlastop(0L);
}

#line 1768 "GD205Kekka.sqc"


	*arrayOut = array;
	*numOut   = num;

	return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 1776 "GD205Kekka.sqc"

//1.06 DELL printf("SQLERR : [%s]\n", sqlca.sqlerrmc);
	// 1.06 DEBUG    LOG
    sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbKekkaGD205SelectByIriNo",
                __LINE__,
                EXEFLG_SEL, "020",
                "SQLERR : [%s]", sqlca.sqlerrmc );

	return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKekkaGD205SelectByKntNo()
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
long ZdbKekkaGD205SelectByKntNo( Hkkknri* pKey, Kekka** arrayOut, int* numOut )
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

#line 1815 "GD205Kekka.sqc"


	
/*
EXEC SQL DECLARE c7 CURSOR FOR
	SELECT
		KKA.KNSKISYMD,
		KKA.SRIYMD,
		KKA.KNTNO,
		KKA.KNTKETFLG,
		KKA.KNSGRP,
		KKA.KMKCD,
		KKA.KNSSU,
		KKA.KNSSUEDA,
		KKA.IRIHSMKBN,
		KKA.IRIKBN,
		KKA.KSKTKBN,
		KKA.UTKYMD,
		KKA.IRINO,
		KKA.IRIKETFLG,
		KKA.ZSSDINO,
		KKA.SSTCD,
		KKA.TRID,
		KKA.TRPOS,
		KKA.ASYRCKID,
		KKA.ASYRCKPOS,
		KKA.OYAKMKCD,
		KKA.SECCD,
		KKA.BKFKKBN,
		KKA.SMPCD,
		KKA.BSKKBN,
		KKA.BSKLNE,
		KKA.BSKGOK,
		KKA.BSKSEQ,
		KKA.BSKERRSTS,
		KKA.SKTDH,
		KKA.NBKMKCD,
		KKA.TSTRFLG,
		KKA.ZRCD,
		KKA.YSNLBL,
		KKA.KJNO,
		KKA.FKHKKNOHJKBN,
		KKA.TBKJNO,
		KKA.TBKJFLG,
		KKA.HTKFKHMS,
		KKA.SKFLG,
		KKA.TSKFLG,
		KKA.TKTFLG,
		KKA.JISKSBR,
		KKA.KKFLG,
		KKA.KKIRIFLG,
		KKA.KKIRILOTNO,
		KKA.HSYKFLG,
		KKA.HSKFLG,
		KKA.HHKKFLG,
		KKA.RAWDATA,
		KKA.KNSKKA1,
		KKA.KNSKKA2,
		KKA.KNSKKA2KBN,
		KKA.KKAHSKCD,
		KKA.HJKKA,
		KKA.SDI,
		KKA.KKACMT1,
		KKA.KKACMT2,
		KKA.KKAJKCD,
		KKA.PNCRGFLG,
		KKA.KNSPNCRGFLG,
		KKA.KKAKSFLG,
		KKA.KKASSFLG,
		KKA.IJKBNM,
		KKA.IJKBNF,
		KKA.IJKBNN,
		KKA.TBIJKBNM,
		KKA.TBIJKBNF,
		KKA.TBIJKBNN,
		KKA.NBDOLBL,
		KKA.NBDOERR,
		KKA.YKDOLBL,
		KKA.YKDOERR,
		KKA.ETCLBL,
		KKA.ETCERR,
		KKA.CTRLNO,
		KKA.KNSSEQ,
		KKA.BTHNO,
		KKA.PLTNO,
		KKA.PLTSEQ,
		KKA.DTNRTTS,
		KKA.DTNRDH,
		KKA.KNSKRDH,
		KKA.HKKDH,
		KKA.HKKKBDH,
		KKA.ZKHKKYYMD,
		KKA.ZKHKKYTME,
		KKA.FRKKAFLG,
		KKA.GZBSFLG,
		KKA.HSIFLG,
		KKA.KKAYSNFLG,
		KKA.TNYRKFLG,
		KKA.SIYFLG,
		KKA.KNSFLG,
		KKA.RENJICFLG,
		KKA.SOUKN1FLG,
		KKA.KANRENFLG,
		KKA.BUNKKUFLG,
		KKA.KESSEIFLG,
		KKA.RIREKIFLG,
		KKA.SYOUGOFLG,
		KKA.KEISANFLG,
		KKA.PER100FLG,
		KKA.TOUSEKFLG,
		KKA.KISYAKFLG,
		KKA.KOUSEIFLG,
		KKA.SYOUNGFLG,
		KKA.SOUKN2FLG,
		KKA.FUKAPTFLG,
		KKA.YOBIFLG01,
		KKA.TOBIFLG02,
		KKA.YOBIFLG03,
		KKA.YOBIFLG04,
		KKA.YOBIFLG05,
		KKA.SKRYCDA,
		KKA.SKRYCDB,
		KKA.SKRYCDC,
		KKA.KSNDH
	FROM
		KEKKA KKA
		LEFT OUTER JOIN VCTRLCHK CTC
			ON KKA.KNSKISYMD = CTC.KNSKISYMD
			AND KKA.BSKKBN = CTC.BSKKBN
			AND KKA.BSKLNE = CTC.BSKLNE
			AND KKA.CTRLNO = CTC.CTRLNO
		LEFT OUTER JOIN (
			SELECT
				(SELECT KKKJSRIYMD FROM SYSKNRMST) AS KNSKISYMD,
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
			KKA.SRIYMD		= :sriymd
		AND KKA.KNSGRP		= :knsgrp
		AND KKA.KNTNO		>= :kntnost
		AND KKA.KNTNO		<= :kntnoed
		AND KKA.KKAJKCD		= :hkkkbn
		AND KKA.SECCD		= :seccd
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
	FOR READ ONLY;
*/

/*
SQL0204N  "DB2INST1.VCTRLCHK" は未定義の名前です。 
SQLSTATE=42704

*/

#line 1985 "GD205Kekka.sqc"


	
/*
EXEC SQL OPEN c7;
*/

{
#line 1987 "GD205Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1987 "GD205Kekka.sqc"
  sqlaaloc(2,6,9,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 1987 "GD205Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1987 "GD205Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)sriymd;
#line 1987 "GD205Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1987 "GD205Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 1987 "GD205Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 1987 "GD205Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1987 "GD205Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 1987 "GD205Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)kntnost;
#line 1987 "GD205Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1987 "GD205Kekka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 14;
#line 1987 "GD205Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)kntnoed;
#line 1987 "GD205Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1987 "GD205Kekka.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 1987 "GD205Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)&hkkkbn;
#line 1987 "GD205Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1987 "GD205Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 1987 "GD205Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)seccd;
#line 1987 "GD205Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1987 "GD205Kekka.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 1987 "GD205Kekka.sqc"
  sqlacall((unsigned short)26,5,2,0,0L);
#line 1987 "GD205Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1987 "GD205Kekka.sqc"
  sqlastop(0L);
}

#line 1987 "GD205Kekka.sqc"


	while( 1 ) {
		Kekka* rec;

		
/*
EXEC SQL FETCH c7 INTO
			:knskisymd,
			:sriymd,
			:kntno,
			:kntketflg,
			:knsgrp,
			:kmkcd,
			:knssu,
			:knssueda,
			:irihsmkbn,
			:irikbn,
			:ksktkbn,
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:sstcd,
			:trid,
			:trpos,
			:asyrckid,
			:asyrckpos,
			:oyakmkcd,
			:seccd,
			:bkfkkbn,
			:smpcd,
			:bskkbn,
			:bsklne,
			:bskgok,
			:bskseq,
			:bskerrsts,
			:sktdh,
			:nbkmkcd,
			:tstrflg,
			:zrcd,
			:ysnlbl,
			:kjno,
			:fkhkknohjkbn,
			:tbkjno,
			:tbkjflg,
			:htkfkhms,
			:skflg,
			:tskflg,
			:tktflg,
			:jisksbr,
			:kkflg,
			:kkiriflg,
			:kkirilotno,
			:hsykflg,
			:hskflg,
			:hhkkflg,
			:rawdata,
			:knskka1,
			:knskka2,
			:knskka2kbn,
			:kkahskcd,
			:hjkka,
			:sdi,
			:kkacmt1,
			:kkacmt2,
			:kkajkcd,
			:pncrgflg,
			:knspncrgflg,
			:kkaksflg,
			:kkassflg,
			:ijkbnm,
			:ijkbnf,
			:ijkbnn,
			:tbijkbnm,
			:tbijkbnf,
			:tbijkbnn,
			:nbdolbl,
			:nbdoerr,
			:ykdolbl,
			:ykdoerr,
			:etclbl,
			:etcerr,
			:ctrlno,
			:knsseq,
			:bthno,
			:pltno,
			:pltseq,
			:dtnrtts,
			:dtnrdh,
			:knskrdh,
			:hkkdh,
			:hkkkbdh,
			:zkhkkyymd,
			:zkhkkytme,
			:frkkaflg,
			:gzbsflg,
			:hsiflg,
			:kkaysnflg,
			:tnyrkflg,
			:siyflg,
			:knsflg,
			:renjicflg,
			:soukn1flg,
			:kanrenflg,
			:bunkkuflg,
			:kesseiflg,
			:rirekiflg,
			:syougoflg,
			:keisanflg,
			:per100flg,
			:tousekflg,
			:kisyakflg,
			:kouseiflg,
			:syoungflg,
			:soukn2flg,
			:fukaptflg,
			:yobiflg01,
			:tobiflg02,
			:yobiflg03,
			:yobiflg04,
			:yobiflg05,
			:skrycda,
			:skrycdb,
			:skrycdc,
			:ksndh;
*/

{
#line 2110 "GD205Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 2110 "GD205Kekka.sqc"
  sqlaaloc(3,118,10,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&knssu;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)&knssueda;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)&irihsmkbn;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)&irikbn;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)&ksktkbn;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)utkymd;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 12;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)irino;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)&iriketflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)&zssdino;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)sstcd;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 11;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)trid;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[17].sqltype = 500; sql_setdlist[17].sqllen = 2;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)&trpos;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 11;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)asyrckid;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)&asyrckpos;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 8;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)oyakmkcd;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 3;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)seccd;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)&bkfkkbn;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)smpcd;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 5;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)bskkbn;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 5;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)bsklne;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 7;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)bskgok;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[27].sqltype = 496; sql_setdlist[27].sqllen = 4;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)&bskseq;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 3;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)bskerrsts;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)sktdh;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 8;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)nbkmkcd;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&tstrflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 5;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)zrcd;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)ysnlbl;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 4;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)kjno;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&fkhkknohjkbn;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 4;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)tbkjno;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&tbkjflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 25;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)htkfkhms;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&skflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 3;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)tskflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)tktflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 16;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)jisksbr;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)&kkflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[44].sqldata = (void*)&kkiriflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[45].sqltype = 500; sql_setdlist[45].sqllen = 2;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[45].sqldata = (void*)&kkirilotno;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[46].sqldata = (void*)&hsykflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[47].sqldata = (void*)&hskflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[48].sqldata = (void*)&hhkkflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 21;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[49].sqldata = (void*)rawdata;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 13;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[50].sqldata = (void*)knskka1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 25;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[51].sqldata = (void*)knskka2;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 3;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[52].sqldata = (void*)knskka2kbn;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 4;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[53].sqldata = (void*)kkahskcd;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 25;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[54].sqldata = (void*)hjkka;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[55].sqldata = (void*)sdi;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 6;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[56].sqldata = (void*)kkacmt1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 6;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[57].sqldata = (void*)kkacmt2;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[58].sqltype = 452; sql_setdlist[58].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[58].sqldata = (void*)&kkajkcd;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[59].sqltype = 452; sql_setdlist[59].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[59].sqldata = (void*)&pncrgflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[60].sqltype = 452; sql_setdlist[60].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[60].sqldata = (void*)&knspncrgflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[61].sqltype = 452; sql_setdlist[61].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[61].sqldata = (void*)&kkaksflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[62].sqltype = 452; sql_setdlist[62].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[62].sqldata = (void*)&kkassflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[63].sqltype = 452; sql_setdlist[63].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[63].sqldata = (void*)&ijkbnm;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sqlasetdata(3,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[54];
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)&ijkbnf;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)&ijkbnn;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)&tbijkbnm;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)&tbijkbnf;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)&tbijkbnn;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)nbdolbl;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 4;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)nbdoerr;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)ykdolbl;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)ykdoerr;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 3;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)etclbl;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 4;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)etcerr;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)&ctrlno;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)&knsseq;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)&bthno;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)&pltno;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)&pltseq;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 9;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)dtnrtts;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)dtnrdh;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)knskrdh;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)hkkdh;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 9;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)hkkkbdh;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 11;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)zkhkkyymd;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 5;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)zkhkkytme;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)&frkkaflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)&gzbsflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)&hsiflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)&kkaysnflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)&tnyrkflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)&siyflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)&knsflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)&renjicflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&soukn1flg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)&kanrenflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)&bunkkuflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)&kesseiflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&rirekiflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)&syougoflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&keisanflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)&per100flg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&tousekflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)&kisyakflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)&kouseiflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[42].sqltype = 452; sql_setdlist[42].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)&syoungflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)&soukn2flg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[44].sqldata = (void*)&fukaptflg;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[45].sqltype = 452; sql_setdlist[45].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[45].sqldata = (void*)&yobiflg01;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[46].sqldata = (void*)&tobiflg02;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[47].sqldata = (void*)&yobiflg03;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[48].sqldata = (void*)&yobiflg04;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[49].sqltype = 452; sql_setdlist[49].sqllen = 1;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[49].sqldata = (void*)&yobiflg05;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 4;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[50].sqldata = (void*)skrycda;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 4;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[51].sqldata = (void*)skrycdb;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 4;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[52].sqldata = (void*)skrycdc;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 27;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[53].sqldata = (void*)ksndh;
#line 2110 "GD205Kekka.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 2110 "GD205Kekka.sqc"
      sqlasetdata(3,64,54,sql_setdlist,0L,0L);
    }
#line 2110 "GD205Kekka.sqc"
  sqlacall((unsigned short)25,5,0,3,0L);
#line 2110 "GD205Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 2110 "GD205Kekka.sqc"
  sqlastop(0L);
}

#line 2110 "GD205Kekka.sqc"


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
#line 2125 "GD205Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 2125 "GD205Kekka.sqc"
  sqlacall((unsigned short)20,5,0,0,0L);
#line 2125 "GD205Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 2125 "GD205Kekka.sqc"
  sqlastop(0L);
}

#line 2125 "GD205Kekka.sqc"


	*arrayOut = array;
	*numOut   = num;

	return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 2133 "GD205Kekka.sqc"

//1.06 DELL printf("SQLERR : [%s]\n", sqlca.sqlerrmc);
	// 1.06 DEBUG    LOG
    sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbKekkaGD205SelectByKntNo",
                __LINE__,
                EXEFLG_SEL, "020",
                "SQLERR : [%s]", sqlca.sqlerrmc );

	return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKekkaGD205Update()
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
long ZdbKekkaGD205Update( Kekka* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KekkaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 2164 "GD205Kekka.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 2165 "GD205Kekka.sqc"


    
/*
EXEC SQL UPDATE KEKKA
    SET (
/- 1.06 DELL
		KNTKETFLG,
		IRIHSMKBN,
		IRIKBN,
		KSKTKBN,
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		SSTCD,
		TRID,
		TRPOS,
		ASYRCKID,
		ASYRCKPOS,
		OYAKMKCD,
		SECCD,
		BKFKKBN,
		SMPCD,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		BSKSEQ,
		BSKERRSTS,
		SKTDH,
		NBKMKCD,
		TSTRFLG,
		ZRCD,
		YSNLBL,
		KJNO,
		FKHKKNOHJKBN,
		TBKJNO,
		TBKJFLG,
		HTKFKHMS,
		SKFLG,
		TSKFLG,
		TKTFLG,
		JISKSBR,
		KKFLG,
		KKIRIFLG,
		KKIRILOTNO,
		HSYKFLG,
		HSKFLG,
		HHKKFLG,
		RAWDATA,
		KNSKKA1,
		KNSKKA2,
		KNSKKA2KBN,
		KKAHSKCD,
		HJKKA,
		SDI,
		KKACMT1,
		KKACMT2,
		KKAJKCD,
		PNCRGFLG,
		KNSPNCRGFLG,
		KKAKSFLG,
		IJKBNM,
		IJKBNF,
		IJKBNN,
		TBIJKBNM,
		TBIJKBNF,
		TBIJKBNN,
		NBDOLBL,
		NBDOERR,
		YKDOLBL,
		YKDOERR,
		ETCLBL,
		ETCERR,
		CTRLNO,
		KNSSEQ,
		BTHNO,
		PLTNO,
		PLTSEQ,
		DTNRTTS,
		DTNRDH,
		KNSKRDH,
		HKKKBDH,
		ZKHKKYYMD,
		ZKHKKYTME,
		FRKKAFLG,
		GZBSFLG,
		HSIFLG,
		KKAYSNFLG,
		TNYRKFLG,
		SIYFLG,
		RENJICFLG,
		SOUKN1FLG,
		KANRENFLG,
		BUNKKUFLG,
		KESSEIFLG,
		RIREKIFLG,
		SYOUGOFLG,
		KEISANFLG,
		PER100FLG,
		TOUSEKFLG,
		KISYAKFLG,
		KOUSEIFLG,
		SYOUNGFLG,
		SOUKN2FLG,
		FUKAPTFLG,
		YOBIFLG01,
		TOBIFLG02,
		YOBIFLG03,
		YOBIFLG04,
		YOBIFLG05,
		SKRYCDA,
		SKRYCDB,
		SKRYCDC,
-/
 		KKASSFLG,
 		HKKDH,
 		KNSFLG,
 		KSNDH
    ) = (
/- 1.06 DELL
		:kntketflg,
		:irihsmkbn,
		:irikbn,
		:ksktkbn,
		:utkymd,
		:irino,
		:iriketflg,
		:zssdino,
		:sstcd,
		:trid,
		:trpos,
		:asyrckid,
		:asyrckpos,
		:oyakmkcd,
		:seccd,
		:bkfkkbn,
		:smpcd,
		:bskkbn,
		:bsklne,
		:bskgok,
		:bskseq,
		:bskerrsts,
		:sktdh,
		:nbkmkcd,
		:tstrflg,
		:zrcd,
		:ysnlbl,
		:kjno,
		:fkhkknohjkbn,
		:tbkjno,
		:tbkjflg,
		:htkfkhms,
		:skflg,
		:tskflg,
		:tktflg,
		:jisksbr,
		:kkflg,
		:kkiriflg,
		:kkirilotno,
		:hsykflg,
		:hskflg,
		:hhkkflg,
		:rawdata,
		:knskka1,
		:knskka2,
		:knskka2kbn,
		:kkahskcd,
		:hjkka,
		:sdi,
		:kkacmt1,
		:kkacmt2,
		:kkajkcd,
		:pncrgflg,
		:knspncrgflg,
		:kkaksflg,
		:ijkbnm,
		:ijkbnf,
		:ijkbnn,
		:tbijkbnm,
		:tbijkbnf,
		:tbijkbnn,
		:nbdolbl,
		:nbdoerr,
		:ykdolbl,
		:ykdoerr,
		:etclbl,
		:etcerr,
		:ctrlno,
		:knsseq,
		:bthno,
		:pltno,
		:pltseq,
		:dtnrtts,
		:dtnrdh,
		:knskrdh,
		:hkkkbdh,
		:zkhkkyymd,
		:zkhkkytme,
		:frkkaflg,
		:gzbsflg,
		:hsiflg,
		:kkaysnflg,
		:tnyrkflg,
		:siyflg,
		:renjicflg,
		:soukn1flg,
		:kanrenflg,
		:bunkkuflg,
		:kesseiflg,
		:rirekiflg,
		:syougoflg,
		:keisanflg,
		:per100flg,
		:tousekflg,
		:kisyakflg,
		:kouseiflg,
		:syoungflg,
		:soukn2flg,
		:fukaptflg,
		:yobiflg01,
		:tobiflg02,
		:yobiflg03,
		:yobiflg04,
		:yobiflg05,
		:skrycda,
		:skrycdb,
		:skrycdc,
-/
		:kkassflg,
		current timestamp,
		:knsflg,
		current timestamp
    ) WHERE
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd AND
		KNSSU = :knssu AND
		KNSSUEDA = :knssueda;
*/

{
#line 2403 "GD205Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 2403 "GD205Kekka.sqc"
  sqlaaloc(2,9,11,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)&kkassflg;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)&knsflg;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)knskisymd;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)sriymd;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 14;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)kntno;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 17;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)knsgrp;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)kmkcd;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)&knssu;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)&knssueda;
#line 2403 "GD205Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 2403 "GD205Kekka.sqc"
      sqlasetdata(2,0,9,sql_setdlist,0L,0L);
    }
#line 2403 "GD205Kekka.sqc"
  sqlacall((unsigned short)24,6,2,0,0L);
#line 2403 "GD205Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 2403 "GD205Kekka.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 2403 "GD205Kekka.sqc"
  sqlastop(0L);
}

#line 2403 "GD205Kekka.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 2408 "GD205Kekka.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 2412 "GD205Kekka.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKekkaGD205UpdateOthers()
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
long ZdbKekkaGD205UpdateOthers( Kekka* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KekkaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 2436 "GD205Kekka.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 2437 "GD205Kekka.sqc"


    
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
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd AND
		KNSFLG <> 'E';
*/

{
#line 2452 "GD205Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 2452 "GD205Kekka.sqc"
  sqlaaloc(2,5,12,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 2452 "GD205Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 2452 "GD205Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 2452 "GD205Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 2452 "GD205Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 2452 "GD205Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 2452 "GD205Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 2452 "GD205Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 2452 "GD205Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 2452 "GD205Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 2452 "GD205Kekka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 2452 "GD205Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 2452 "GD205Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 2452 "GD205Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 2452 "GD205Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 2452 "GD205Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 2452 "GD205Kekka.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 2452 "GD205Kekka.sqc"
  sqlacall((unsigned short)24,7,2,0,0L);
#line 2452 "GD205Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 2452 "GD205Kekka.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 2452 "GD205Kekka.sqc"
  sqlastop(0L);
}

#line 2452 "GD205Kekka.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 2457 "GD205Kekka.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 2461 "GD205Kekka.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
