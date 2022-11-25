static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,105,66,69,89,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,69,68,50,48,51,75,69,75,0,0,0,0,0,0,0,0,
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


#line 1 "ED203Kekka.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： ED203Kekka.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-03-13                    Create
 **********************************************************************/
#include <stdio.h>

#include "ED203Kekka.h"
#include "bml_misc.h"
#include "bml_db.h"
#include "bml_dmm.h"

#define ALLOC_UNIT		1


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 24 "ED203Kekka.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "ED203Kekka.sqc"

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

#line 179 "ED203Kekka.sqc"



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
 * ZdbKekkaED203SelectByKkIriLotNo()
 *    KEKKA レコード条件取得（緊急依頼ロットNo）
 * ■引数
 *    [I]  Kekka* pKey       取得するレコードのキー
 *    [O]  Kekka** arrayOut     取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKekkaED203SelectByKkIriLotNo( Hkkknri* pKey, Kekka** arrayOut, int* numOut )
{
	Kekka*      array = NULL;
	int         num = 0;

	if( !pKey )
		return HRC_NULL_POINTER;

	if( !ZbmlMapStructToHost( (char*)pKey, HkkknriArray ) )
		return HRC_INVALID_VALUE;

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 334 "ED203Kekka.sqc"


	
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
		, CTRLKNR CKR
		, XBARM XBM
	WHERE
			KKA.KNSKISYMD	= CKR.KNSKISYMD
		AND KKA.BSKKBN		= CKR.BSKKBN
		AND KKA.BSKGOK		= CKR.BSKGOK
		AND KKA.CTRLNO		= CKR.CTRLNO
		AND KKA.KNSKISYMD	= XBM.KNSKISYMD
		AND KKA.BSKKBN		= XBM.BSKKBN
		AND KKA.BSKGOK		= XBM.BSKGOK
		AND KKA.KMKCD		= XBM.KMKCD
		AND KKA.PLTNO		= XBM.PLTNO
		AND KKA.UTKYMD		= :utkymd
		AND KKA.SECCD		= :seccd
		AND KKA.KKIRILOTNO	= :kkirilotno
		AND ( KKA.IRIHSMKBN = '0' OR KKA.IRIHSMKBN = '1')
		AND (  ( KKA.KNSFLG = 'X' AND CKR.CTRLKTFLG = '1' AND XBM.XBARMJKFLG = '1' )
			OR ( KKA.KNSFLG = 'S')
			OR ( KKA.KNSFLG = 'H') )
	FOR READ ONLY;
*/

#line 477 "ED203Kekka.sqc"


	
/*
EXEC SQL OPEN c3;
*/

{
#line 479 "ED203Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 479 "ED203Kekka.sqc"
  sqlaaloc(2,3,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 479 "ED203Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 479 "ED203Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 479 "ED203Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 479 "ED203Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 479 "ED203Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)seccd;
#line 479 "ED203Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 479 "ED203Kekka.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 479 "ED203Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)&kkirilotno;
#line 479 "ED203Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 479 "ED203Kekka.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 479 "ED203Kekka.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 479 "ED203Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 479 "ED203Kekka.sqc"
  sqlastop(0L);
}

#line 479 "ED203Kekka.sqc"


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
#line 602 "ED203Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 602 "ED203Kekka.sqc"
  sqlaaloc(3,118,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 602 "ED203Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&knssu;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)&knssueda;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)&irihsmkbn;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)&irikbn;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)&ksktkbn;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)utkymd;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 12;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)irino;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)&iriketflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)&zssdino;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)sstcd;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 11;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)trid;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[17].sqltype = 500; sql_setdlist[17].sqllen = 2;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)&trpos;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 11;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)asyrckid;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)&asyrckpos;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 8;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)oyakmkcd;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 3;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)seccd;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)&bkfkkbn;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)smpcd;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 5;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)bskkbn;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 5;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)bsklne;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 7;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)bskgok;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[27].sqltype = 496; sql_setdlist[27].sqllen = 4;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)&bskseq;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 3;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)bskerrsts;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)sktdh;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 8;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)nbkmkcd;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&tstrflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 5;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)zrcd;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)ysnlbl;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 4;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)kjno;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&fkhkknohjkbn;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 4;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)tbkjno;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&tbkjflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 25;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)htkfkhms;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&skflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 3;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)tskflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)tktflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 16;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)jisksbr;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)&kkflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[44].sqldata = (void*)&kkiriflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[45].sqltype = 500; sql_setdlist[45].sqllen = 2;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[45].sqldata = (void*)&kkirilotno;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[46].sqldata = (void*)&hsykflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[47].sqldata = (void*)&hskflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[48].sqldata = (void*)&hhkkflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 21;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[49].sqldata = (void*)rawdata;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 13;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[50].sqldata = (void*)knskka1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 25;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[51].sqldata = (void*)knskka2;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 3;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[52].sqldata = (void*)knskka2kbn;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 4;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[53].sqldata = (void*)kkahskcd;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 25;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[54].sqldata = (void*)hjkka;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[55].sqldata = (void*)sdi;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 6;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[56].sqldata = (void*)kkacmt1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 6;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[57].sqldata = (void*)kkacmt2;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[58].sqltype = 452; sql_setdlist[58].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[58].sqldata = (void*)&kkajkcd;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[59].sqltype = 452; sql_setdlist[59].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[59].sqldata = (void*)&pncrgflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[60].sqltype = 452; sql_setdlist[60].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[60].sqldata = (void*)&knspncrgflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[61].sqltype = 452; sql_setdlist[61].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[61].sqldata = (void*)&kkaksflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[62].sqltype = 452; sql_setdlist[62].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[62].sqldata = (void*)&kkassflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[63].sqltype = 452; sql_setdlist[63].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[63].sqldata = (void*)&ijkbnm;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sqlasetdata(3,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[54];
#line 602 "ED203Kekka.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)&ijkbnf;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)&ijkbnn;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)&tbijkbnm;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)&tbijkbnf;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)&tbijkbnn;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)nbdolbl;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 4;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)nbdoerr;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)ykdolbl;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)ykdoerr;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 3;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)etclbl;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 4;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)etcerr;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)&ctrlno;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)&knsseq;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)&bthno;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)&pltno;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)&pltseq;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 9;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)dtnrtts;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)dtnrdh;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)knskrdh;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)hkkdh;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 9;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)hkkkbdh;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 11;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)zkhkkyymd;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 5;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)zkhkkytme;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)&frkkaflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)&gzbsflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)&hsiflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)&kkaysnflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)&tnyrkflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)&siyflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)&knsflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)&renjicflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&soukn1flg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)&kanrenflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)&bunkkuflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)&kesseiflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&rirekiflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)&syougoflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&keisanflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)&per100flg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&tousekflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)&kisyakflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)&kouseiflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[42].sqltype = 452; sql_setdlist[42].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)&syoungflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)&soukn2flg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[44].sqldata = (void*)&fukaptflg;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[45].sqltype = 452; sql_setdlist[45].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[45].sqldata = (void*)&yobiflg01;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[46].sqldata = (void*)&tobiflg02;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[47].sqldata = (void*)&yobiflg03;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[48].sqldata = (void*)&yobiflg04;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[49].sqltype = 452; sql_setdlist[49].sqllen = 1;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[49].sqldata = (void*)&yobiflg05;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 4;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[50].sqldata = (void*)skrycda;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 4;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[51].sqldata = (void*)skrycdb;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 4;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[52].sqldata = (void*)skrycdc;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 27;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[53].sqldata = (void*)ksndh;
#line 602 "ED203Kekka.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 602 "ED203Kekka.sqc"
      sqlasetdata(3,64,54,sql_setdlist,0L,0L);
    }
#line 602 "ED203Kekka.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 602 "ED203Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 602 "ED203Kekka.sqc"
  sqlastop(0L);
}

#line 602 "ED203Kekka.sqc"


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
#line 617 "ED203Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 617 "ED203Kekka.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 617 "ED203Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 617 "ED203Kekka.sqc"
  sqlastop(0L);
}

#line 617 "ED203Kekka.sqc"


	*arrayOut = array;
	*numOut   = num;

	return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 625 "ED203Kekka.sqc"

printf("SQLERR : [%s]\n", sqlca.sqlerrmc);
	return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKekkaED203Update()
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
long ZdbKekkaED203Update( Kekka* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KekkaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 650 "ED203Kekka.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 651 "ED203Kekka.sqc"


    
/*
EXEC SQL UPDATE KEKKA
    SET (
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
		KKASSFLG,
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
		HKKDH,
		HKKKBDH,
		ZKHKKYYMD,
		ZKHKKYTME,
		FRKKAFLG,
		GZBSFLG,
		HSIFLG,
		KKAYSNFLG,
		TNYRKFLG,
		SIYFLG,
		KNSFLG,
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
		KSNDH
    ) = (
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
		current timestamp,
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
#line 885 "ED203Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 885 "ED203Kekka.sqc"
  sqlaaloc(2,116,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 885 "ED203Kekka.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)&kntketflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)&irihsmkbn;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)&irikbn;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)&ksktkbn;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)utkymd;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 12;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)irino;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&iriketflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)&zssdino;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 8;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)sstcd;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)trid;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[10].sqltype = 500; sql_setdlist[10].sqllen = 2;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)&trpos;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)asyrckid;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)&asyrckpos;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 8;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)oyakmkcd;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 3;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)seccd;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[15].sqltype = 452; sql_setdlist[15].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)&bkfkkbn;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 8;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)smpcd;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 5;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)bskkbn;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 5;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)bsklne;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 7;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)bskgok;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[20].sqltype = 496; sql_setdlist[20].sqllen = 4;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)&bskseq;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 3;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)bskerrsts;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 27;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)sktdh;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)nbkmkcd;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)&tstrflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 5;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)zrcd;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 3;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)ysnlbl;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 4;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)kjno;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)&fkhkknohjkbn;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 4;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)tbkjno;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)&tbkjflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 25;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)htkfkhms;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)&skflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)tskflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 3;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)tktflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 16;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)jisksbr;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)&kkflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&kkiriflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[38].sqltype = 500; sql_setdlist[38].sqllen = 2;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)&kkirilotno;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&hsykflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)&hskflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)&hhkkflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 21;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)rawdata;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 13;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)knskka1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 25;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[44].sqldata = (void*)knskka2;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 3;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[45].sqldata = (void*)knskka2kbn;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 4;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[46].sqldata = (void*)kkahskcd;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 25;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[47].sqldata = (void*)hjkka;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 4;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[48].sqldata = (void*)sdi;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 6;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[49].sqldata = (void*)kkacmt1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 6;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[50].sqldata = (void*)kkacmt2;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[51].sqltype = 452; sql_setdlist[51].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[51].sqldata = (void*)&kkajkcd;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[52].sqltype = 452; sql_setdlist[52].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[52].sqldata = (void*)&pncrgflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[53].sqltype = 452; sql_setdlist[53].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[53].sqldata = (void*)&knspncrgflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[54].sqltype = 452; sql_setdlist[54].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[54].sqldata = (void*)&kkaksflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[55].sqltype = 452; sql_setdlist[55].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[55].sqldata = (void*)&kkassflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[56].sqltype = 452; sql_setdlist[56].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[56].sqldata = (void*)&ijkbnm;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[57].sqltype = 452; sql_setdlist[57].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[57].sqldata = (void*)&ijkbnf;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[58].sqltype = 452; sql_setdlist[58].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[58].sqldata = (void*)&ijkbnn;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[59].sqltype = 452; sql_setdlist[59].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[59].sqldata = (void*)&tbijkbnm;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[60].sqltype = 452; sql_setdlist[60].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[60].sqldata = (void*)&tbijkbnf;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[61].sqltype = 452; sql_setdlist[61].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[61].sqldata = (void*)&tbijkbnn;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[62].sqltype = 460; sql_setdlist[62].sqllen = 3;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[62].sqldata = (void*)nbdolbl;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[63].sqltype = 460; sql_setdlist[63].sqllen = 4;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[63].sqldata = (void*)nbdoerr;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sqlasetdata(2,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[52];
#line 885 "ED203Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)ykdolbl;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 4;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)ykdoerr;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)etclbl;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 4;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)etcerr;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)&ctrlno;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)&knsseq;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&bthno;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)&pltno;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)&pltseq;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 9;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)dtnrtts;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 27;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)dtnrdh;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 27;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)knskrdh;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)hkkkbdh;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)zkhkkyymd;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 5;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)zkhkkytme;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[15].sqltype = 452; sql_setdlist[15].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)&frkkaflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)&gzbsflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)&hsiflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)&kkaysnflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)&tnyrkflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)&siyflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)&knsflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)&renjicflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)&soukn1flg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)&kanrenflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)&bunkkuflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)&kesseiflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)&rirekiflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)&syougoflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)&keisanflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)&per100flg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&tousekflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)&kisyakflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)&kouseiflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)&syoungflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&soukn2flg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)&fukaptflg;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&yobiflg01;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)&tobiflg02;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&yobiflg03;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)&yobiflg04;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)&yobiflg05;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 4;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)skrycda;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 4;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)skrycdb;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 4;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[44].sqldata = (void*)skrycdc;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 11;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[45].sqldata = (void*)knskisymd;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 11;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[46].sqldata = (void*)sriymd;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 14;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[47].sqldata = (void*)kntno;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 17;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[48].sqldata = (void*)knsgrp;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 8;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[49].sqldata = (void*)kmkcd;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[50].sqltype = 500; sql_setdlist[50].sqllen = 2;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[50].sqldata = (void*)&knssu;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[51].sqltype = 500; sql_setdlist[51].sqllen = 2;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[51].sqldata = (void*)&knssueda;
#line 885 "ED203Kekka.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 885 "ED203Kekka.sqc"
      sqlasetdata(2,64,52,sql_setdlist,0L,0L);
    }
#line 885 "ED203Kekka.sqc"
  sqlacall((unsigned short)24,2,2,0,0L);
#line 885 "ED203Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 885 "ED203Kekka.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 885 "ED203Kekka.sqc"
  sqlastop(0L);
}

#line 885 "ED203Kekka.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 890 "ED203Kekka.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 894 "ED203Kekka.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
