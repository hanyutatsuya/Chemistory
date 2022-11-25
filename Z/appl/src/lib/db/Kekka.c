static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,121,65,83,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,50,56,90,75,69,75,75,32,0,0,0,0,0,0,0,0,
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


#line 1 "Kekka.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Kekka.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Kekka.h"
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


#line 24 "Kekka.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Kekka.sqc"

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
	char    trkdh[27];
	char	skkka[25];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 150 "Kekka.sqc"



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
	DMM_STIMESTAMP( trkdh ),
	DMM_SSTRING( skkka ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKekkaSelectAll()
 *    KEKKA レコード全件取得
 * ■引数
 *    [O]  Kekka** arrayOut     取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKekkaSelectAll( Kekka** arrayOut, int* numOut )
{
    Kekka*      array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 298 "Kekka.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSKISYMD,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		KNSGRP,
		KMKCD,
		KNSSU,
		KNSSUEDA,
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
		KSNDH,
		TRKDH,
		SKKKA
    FROM
        KEKKA FOR READ ONLY;
*/

#line 423 "Kekka.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 425 "Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 425 "Kekka.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 425 "Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 425 "Kekka.sqc"
  sqlastop(0L);
}

#line 425 "Kekka.sqc"


    while( 1 ) {
        Kekka* rec;

        
/*
EXEC SQL FETCH c1 INTO
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
			:ksndh,
			:trkdh,
			:skkka;
*/

{
#line 550 "Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 550 "Kekka.sqc"
  sqlaaloc(3,120,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 550 "Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 550 "Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 550 "Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 550 "Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 550 "Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 550 "Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 550 "Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 550 "Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 550 "Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 550 "Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 550 "Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 550 "Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 550 "Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&knssu;
#line 550 "Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 550 "Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)&knssueda;
#line 550 "Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)&irihsmkbn;
#line 550 "Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)&irikbn;
#line 550 "Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)&ksktkbn;
#line 550 "Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 550 "Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)utkymd;
#line 550 "Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 12;
#line 550 "Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)irino;
#line 550 "Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)&iriketflg;
#line 550 "Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 550 "Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)&zssdino;
#line 550 "Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 550 "Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)sstcd;
#line 550 "Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 11;
#line 550 "Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)trid;
#line 550 "Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[17].sqltype = 500; sql_setdlist[17].sqllen = 2;
#line 550 "Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)&trpos;
#line 550 "Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 11;
#line 550 "Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)asyrckid;
#line 550 "Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 550 "Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)&asyrckpos;
#line 550 "Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 8;
#line 550 "Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)oyakmkcd;
#line 550 "Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 3;
#line 550 "Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)seccd;
#line 550 "Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)&bkfkkbn;
#line 550 "Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 550 "Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)smpcd;
#line 550 "Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 5;
#line 550 "Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)bskkbn;
#line 550 "Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 5;
#line 550 "Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)bsklne;
#line 550 "Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 7;
#line 550 "Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)bskgok;
#line 550 "Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[27].sqltype = 496; sql_setdlist[27].sqllen = 4;
#line 550 "Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)&bskseq;
#line 550 "Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 3;
#line 550 "Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)bskerrsts;
#line 550 "Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 550 "Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)sktdh;
#line 550 "Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 8;
#line 550 "Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)nbkmkcd;
#line 550 "Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&tstrflg;
#line 550 "Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 5;
#line 550 "Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)zrcd;
#line 550 "Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 550 "Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)ysnlbl;
#line 550 "Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 4;
#line 550 "Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)kjno;
#line 550 "Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&fkhkknohjkbn;
#line 550 "Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 4;
#line 550 "Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)tbkjno;
#line 550 "Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&tbkjflg;
#line 550 "Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 25;
#line 550 "Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)htkfkhms;
#line 550 "Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&skflg;
#line 550 "Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 3;
#line 550 "Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)tskflg;
#line 550 "Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 550 "Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)tktflg;
#line 550 "Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 16;
#line 550 "Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)jisksbr;
#line 550 "Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)&kkflg;
#line 550 "Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[44].sqldata = (void*)&kkiriflg;
#line 550 "Kekka.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[45].sqltype = 500; sql_setdlist[45].sqllen = 2;
#line 550 "Kekka.sqc"
      sql_setdlist[45].sqldata = (void*)&kkirilotno;
#line 550 "Kekka.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[46].sqldata = (void*)&hsykflg;
#line 550 "Kekka.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[47].sqldata = (void*)&hskflg;
#line 550 "Kekka.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[48].sqldata = (void*)&hhkkflg;
#line 550 "Kekka.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 21;
#line 550 "Kekka.sqc"
      sql_setdlist[49].sqldata = (void*)rawdata;
#line 550 "Kekka.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 13;
#line 550 "Kekka.sqc"
      sql_setdlist[50].sqldata = (void*)knskka1;
#line 550 "Kekka.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 25;
#line 550 "Kekka.sqc"
      sql_setdlist[51].sqldata = (void*)knskka2;
#line 550 "Kekka.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 3;
#line 550 "Kekka.sqc"
      sql_setdlist[52].sqldata = (void*)knskka2kbn;
#line 550 "Kekka.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 4;
#line 550 "Kekka.sqc"
      sql_setdlist[53].sqldata = (void*)kkahskcd;
#line 550 "Kekka.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 25;
#line 550 "Kekka.sqc"
      sql_setdlist[54].sqldata = (void*)hjkka;
#line 550 "Kekka.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 550 "Kekka.sqc"
      sql_setdlist[55].sqldata = (void*)sdi;
#line 550 "Kekka.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 6;
#line 550 "Kekka.sqc"
      sql_setdlist[56].sqldata = (void*)kkacmt1;
#line 550 "Kekka.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 6;
#line 550 "Kekka.sqc"
      sql_setdlist[57].sqldata = (void*)kkacmt2;
#line 550 "Kekka.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[58].sqltype = 452; sql_setdlist[58].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[58].sqldata = (void*)&kkajkcd;
#line 550 "Kekka.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[59].sqltype = 452; sql_setdlist[59].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[59].sqldata = (void*)&pncrgflg;
#line 550 "Kekka.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[60].sqltype = 452; sql_setdlist[60].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[60].sqldata = (void*)&knspncrgflg;
#line 550 "Kekka.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[61].sqltype = 452; sql_setdlist[61].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[61].sqldata = (void*)&kkaksflg;
#line 550 "Kekka.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[62].sqltype = 452; sql_setdlist[62].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[62].sqldata = (void*)&kkassflg;
#line 550 "Kekka.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[63].sqltype = 452; sql_setdlist[63].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[63].sqldata = (void*)&ijkbnm;
#line 550 "Kekka.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 550 "Kekka.sqc"
      sqlasetdata(3,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[56];
#line 550 "Kekka.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)&ijkbnf;
#line 550 "Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)&ijkbnn;
#line 550 "Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)&tbijkbnm;
#line 550 "Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)&tbijkbnf;
#line 550 "Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)&tbijkbnn;
#line 550 "Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 550 "Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)nbdolbl;
#line 550 "Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 4;
#line 550 "Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)nbdoerr;
#line 550 "Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 550 "Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)ykdolbl;
#line 550 "Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 550 "Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)ykdoerr;
#line 550 "Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 3;
#line 550 "Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)etclbl;
#line 550 "Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 4;
#line 550 "Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)etcerr;
#line 550 "Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 550 "Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)&ctrlno;
#line 550 "Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 550 "Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)&knsseq;
#line 550 "Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 550 "Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)&bthno;
#line 550 "Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 550 "Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)&pltno;
#line 550 "Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 550 "Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)&pltseq;
#line 550 "Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 9;
#line 550 "Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)dtnrtts;
#line 550 "Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 550 "Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)dtnrdh;
#line 550 "Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 550 "Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)knskrdh;
#line 550 "Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 550 "Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)hkkdh;
#line 550 "Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 9;
#line 550 "Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)hkkkbdh;
#line 550 "Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 11;
#line 550 "Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)zkhkkyymd;
#line 550 "Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 5;
#line 550 "Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)zkhkkytme;
#line 550 "Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)&frkkaflg;
#line 550 "Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)&gzbsflg;
#line 550 "Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)&hsiflg;
#line 550 "Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)&kkaysnflg;
#line 550 "Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)&tnyrkflg;
#line 550 "Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)&siyflg;
#line 550 "Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)&knsflg;
#line 550 "Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)&renjicflg;
#line 550 "Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&soukn1flg;
#line 550 "Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)&kanrenflg;
#line 550 "Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)&bunkkuflg;
#line 550 "Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)&kesseiflg;
#line 550 "Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&rirekiflg;
#line 550 "Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)&syougoflg;
#line 550 "Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&keisanflg;
#line 550 "Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)&per100flg;
#line 550 "Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&tousekflg;
#line 550 "Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)&kisyakflg;
#line 550 "Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)&kouseiflg;
#line 550 "Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[42].sqltype = 452; sql_setdlist[42].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)&syoungflg;
#line 550 "Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)&soukn2flg;
#line 550 "Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[44].sqldata = (void*)&fukaptflg;
#line 550 "Kekka.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[45].sqltype = 452; sql_setdlist[45].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[45].sqldata = (void*)&yobiflg01;
#line 550 "Kekka.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[46].sqldata = (void*)&tobiflg02;
#line 550 "Kekka.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[47].sqldata = (void*)&yobiflg03;
#line 550 "Kekka.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[48].sqldata = (void*)&yobiflg04;
#line 550 "Kekka.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[49].sqltype = 452; sql_setdlist[49].sqllen = 1;
#line 550 "Kekka.sqc"
      sql_setdlist[49].sqldata = (void*)&yobiflg05;
#line 550 "Kekka.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 4;
#line 550 "Kekka.sqc"
      sql_setdlist[50].sqldata = (void*)skrycda;
#line 550 "Kekka.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 4;
#line 550 "Kekka.sqc"
      sql_setdlist[51].sqldata = (void*)skrycdb;
#line 550 "Kekka.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 4;
#line 550 "Kekka.sqc"
      sql_setdlist[52].sqldata = (void*)skrycdc;
#line 550 "Kekka.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 27;
#line 550 "Kekka.sqc"
      sql_setdlist[53].sqldata = (void*)ksndh;
#line 550 "Kekka.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 27;
#line 550 "Kekka.sqc"
      sql_setdlist[54].sqldata = (void*)trkdh;
#line 550 "Kekka.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 550 "Kekka.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 25;
#line 550 "Kekka.sqc"
      sql_setdlist[55].sqldata = (void*)skkka;
#line 550 "Kekka.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 550 "Kekka.sqc"
      sqlasetdata(3,64,56,sql_setdlist,0L,0L);
    }
#line 550 "Kekka.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 550 "Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 550 "Kekka.sqc"
  sqlastop(0L);
}

#line 550 "Kekka.sqc"


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
EXEC SQL CLOSE c1;
*/

{
#line 565 "Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 565 "Kekka.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 565 "Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 565 "Kekka.sqc"
  sqlastop(0L);
}

#line 565 "Kekka.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 573 "Kekka.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKekkaSelectKey()
 *    KEKKA レコードKey条件取得
 * ■引数
 *    [I]  Kekka* pKey       取得するレコードのキー
 *    [O]  Kekka** arrayOut     取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKekkaSelectKey( Kekka* pKey, Kekka** arrayOut, int* numOut )
{
    Kekka*      array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KekkaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 599 "Kekka.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSKISYMD,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		KNSGRP,
		KMKCD,
		KNSSU,
		KNSSUEDA,
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
		KSNDH,
		TRKDH,
		SKKKA
    FROM
        KEKKA
    WHERE
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd AND
		KNSSU = :knssu AND
		KNSSUEDA = :knssueda FOR READ ONLY;
*/

#line 732 "Kekka.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 734 "Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 734 "Kekka.sqc"
  sqlaaloc(2,7,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 734 "Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 734 "Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 734 "Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 734 "Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 734 "Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 734 "Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 734 "Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 734 "Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 734 "Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 734 "Kekka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 734 "Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 734 "Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 734 "Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 734 "Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 734 "Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 734 "Kekka.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 734 "Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)&knssu;
#line 734 "Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 734 "Kekka.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 734 "Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&knssueda;
#line 734 "Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 734 "Kekka.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 734 "Kekka.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 734 "Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 734 "Kekka.sqc"
  sqlastop(0L);
}

#line 734 "Kekka.sqc"


    while( 1 ) {
        Kekka* rec;

        
/*
EXEC SQL FETCH c2 INTO
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
			:ksndh,
			:trkdh,
			:skkka;
*/

{
#line 859 "Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 859 "Kekka.sqc"
  sqlaaloc(3,120,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 859 "Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 859 "Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 859 "Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 859 "Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 859 "Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 859 "Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 859 "Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 859 "Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 859 "Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 859 "Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 859 "Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 859 "Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 859 "Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&knssu;
#line 859 "Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 859 "Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)&knssueda;
#line 859 "Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)&irihsmkbn;
#line 859 "Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)&irikbn;
#line 859 "Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)&ksktkbn;
#line 859 "Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 859 "Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)utkymd;
#line 859 "Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 12;
#line 859 "Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)irino;
#line 859 "Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)&iriketflg;
#line 859 "Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 859 "Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)&zssdino;
#line 859 "Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 859 "Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)sstcd;
#line 859 "Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 11;
#line 859 "Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)trid;
#line 859 "Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[17].sqltype = 500; sql_setdlist[17].sqllen = 2;
#line 859 "Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)&trpos;
#line 859 "Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 11;
#line 859 "Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)asyrckid;
#line 859 "Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 859 "Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)&asyrckpos;
#line 859 "Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 8;
#line 859 "Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)oyakmkcd;
#line 859 "Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 3;
#line 859 "Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)seccd;
#line 859 "Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)&bkfkkbn;
#line 859 "Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 859 "Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)smpcd;
#line 859 "Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 5;
#line 859 "Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)bskkbn;
#line 859 "Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 5;
#line 859 "Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)bsklne;
#line 859 "Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 7;
#line 859 "Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)bskgok;
#line 859 "Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[27].sqltype = 496; sql_setdlist[27].sqllen = 4;
#line 859 "Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)&bskseq;
#line 859 "Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 3;
#line 859 "Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)bskerrsts;
#line 859 "Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 859 "Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)sktdh;
#line 859 "Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 8;
#line 859 "Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)nbkmkcd;
#line 859 "Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&tstrflg;
#line 859 "Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 5;
#line 859 "Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)zrcd;
#line 859 "Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 859 "Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)ysnlbl;
#line 859 "Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 4;
#line 859 "Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)kjno;
#line 859 "Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&fkhkknohjkbn;
#line 859 "Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 4;
#line 859 "Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)tbkjno;
#line 859 "Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&tbkjflg;
#line 859 "Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 25;
#line 859 "Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)htkfkhms;
#line 859 "Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&skflg;
#line 859 "Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 3;
#line 859 "Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)tskflg;
#line 859 "Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 859 "Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)tktflg;
#line 859 "Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 16;
#line 859 "Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)jisksbr;
#line 859 "Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)&kkflg;
#line 859 "Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[44].sqldata = (void*)&kkiriflg;
#line 859 "Kekka.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[45].sqltype = 500; sql_setdlist[45].sqllen = 2;
#line 859 "Kekka.sqc"
      sql_setdlist[45].sqldata = (void*)&kkirilotno;
#line 859 "Kekka.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[46].sqldata = (void*)&hsykflg;
#line 859 "Kekka.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[47].sqldata = (void*)&hskflg;
#line 859 "Kekka.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[48].sqldata = (void*)&hhkkflg;
#line 859 "Kekka.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 21;
#line 859 "Kekka.sqc"
      sql_setdlist[49].sqldata = (void*)rawdata;
#line 859 "Kekka.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 13;
#line 859 "Kekka.sqc"
      sql_setdlist[50].sqldata = (void*)knskka1;
#line 859 "Kekka.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 25;
#line 859 "Kekka.sqc"
      sql_setdlist[51].sqldata = (void*)knskka2;
#line 859 "Kekka.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 3;
#line 859 "Kekka.sqc"
      sql_setdlist[52].sqldata = (void*)knskka2kbn;
#line 859 "Kekka.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 4;
#line 859 "Kekka.sqc"
      sql_setdlist[53].sqldata = (void*)kkahskcd;
#line 859 "Kekka.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 25;
#line 859 "Kekka.sqc"
      sql_setdlist[54].sqldata = (void*)hjkka;
#line 859 "Kekka.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 859 "Kekka.sqc"
      sql_setdlist[55].sqldata = (void*)sdi;
#line 859 "Kekka.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 6;
#line 859 "Kekka.sqc"
      sql_setdlist[56].sqldata = (void*)kkacmt1;
#line 859 "Kekka.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 6;
#line 859 "Kekka.sqc"
      sql_setdlist[57].sqldata = (void*)kkacmt2;
#line 859 "Kekka.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[58].sqltype = 452; sql_setdlist[58].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[58].sqldata = (void*)&kkajkcd;
#line 859 "Kekka.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[59].sqltype = 452; sql_setdlist[59].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[59].sqldata = (void*)&pncrgflg;
#line 859 "Kekka.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[60].sqltype = 452; sql_setdlist[60].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[60].sqldata = (void*)&knspncrgflg;
#line 859 "Kekka.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[61].sqltype = 452; sql_setdlist[61].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[61].sqldata = (void*)&kkaksflg;
#line 859 "Kekka.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[62].sqltype = 452; sql_setdlist[62].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[62].sqldata = (void*)&kkassflg;
#line 859 "Kekka.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[63].sqltype = 452; sql_setdlist[63].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[63].sqldata = (void*)&ijkbnm;
#line 859 "Kekka.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 859 "Kekka.sqc"
      sqlasetdata(3,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[56];
#line 859 "Kekka.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)&ijkbnf;
#line 859 "Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)&ijkbnn;
#line 859 "Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)&tbijkbnm;
#line 859 "Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)&tbijkbnf;
#line 859 "Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)&tbijkbnn;
#line 859 "Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 859 "Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)nbdolbl;
#line 859 "Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 4;
#line 859 "Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)nbdoerr;
#line 859 "Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 859 "Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)ykdolbl;
#line 859 "Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 859 "Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)ykdoerr;
#line 859 "Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 3;
#line 859 "Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)etclbl;
#line 859 "Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 4;
#line 859 "Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)etcerr;
#line 859 "Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 859 "Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)&ctrlno;
#line 859 "Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 859 "Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)&knsseq;
#line 859 "Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 859 "Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)&bthno;
#line 859 "Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 859 "Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)&pltno;
#line 859 "Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 859 "Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)&pltseq;
#line 859 "Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 9;
#line 859 "Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)dtnrtts;
#line 859 "Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 859 "Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)dtnrdh;
#line 859 "Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 859 "Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)knskrdh;
#line 859 "Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 859 "Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)hkkdh;
#line 859 "Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 9;
#line 859 "Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)hkkkbdh;
#line 859 "Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 11;
#line 859 "Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)zkhkkyymd;
#line 859 "Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 5;
#line 859 "Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)zkhkkytme;
#line 859 "Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)&frkkaflg;
#line 859 "Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)&gzbsflg;
#line 859 "Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)&hsiflg;
#line 859 "Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)&kkaysnflg;
#line 859 "Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)&tnyrkflg;
#line 859 "Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)&siyflg;
#line 859 "Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)&knsflg;
#line 859 "Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)&renjicflg;
#line 859 "Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&soukn1flg;
#line 859 "Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)&kanrenflg;
#line 859 "Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)&bunkkuflg;
#line 859 "Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)&kesseiflg;
#line 859 "Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&rirekiflg;
#line 859 "Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)&syougoflg;
#line 859 "Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&keisanflg;
#line 859 "Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)&per100flg;
#line 859 "Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&tousekflg;
#line 859 "Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)&kisyakflg;
#line 859 "Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)&kouseiflg;
#line 859 "Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[42].sqltype = 452; sql_setdlist[42].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)&syoungflg;
#line 859 "Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)&soukn2flg;
#line 859 "Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[44].sqldata = (void*)&fukaptflg;
#line 859 "Kekka.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[45].sqltype = 452; sql_setdlist[45].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[45].sqldata = (void*)&yobiflg01;
#line 859 "Kekka.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[46].sqldata = (void*)&tobiflg02;
#line 859 "Kekka.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[47].sqldata = (void*)&yobiflg03;
#line 859 "Kekka.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[48].sqldata = (void*)&yobiflg04;
#line 859 "Kekka.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[49].sqltype = 452; sql_setdlist[49].sqllen = 1;
#line 859 "Kekka.sqc"
      sql_setdlist[49].sqldata = (void*)&yobiflg05;
#line 859 "Kekka.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 4;
#line 859 "Kekka.sqc"
      sql_setdlist[50].sqldata = (void*)skrycda;
#line 859 "Kekka.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 4;
#line 859 "Kekka.sqc"
      sql_setdlist[51].sqldata = (void*)skrycdb;
#line 859 "Kekka.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 4;
#line 859 "Kekka.sqc"
      sql_setdlist[52].sqldata = (void*)skrycdc;
#line 859 "Kekka.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 27;
#line 859 "Kekka.sqc"
      sql_setdlist[53].sqldata = (void*)ksndh;
#line 859 "Kekka.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 27;
#line 859 "Kekka.sqc"
      sql_setdlist[54].sqldata = (void*)trkdh;
#line 859 "Kekka.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 859 "Kekka.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 25;
#line 859 "Kekka.sqc"
      sql_setdlist[55].sqldata = (void*)skkka;
#line 859 "Kekka.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 859 "Kekka.sqc"
      sqlasetdata(3,64,56,sql_setdlist,0L,0L);
    }
#line 859 "Kekka.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 859 "Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 859 "Kekka.sqc"
  sqlastop(0L);
}

#line 859 "Kekka.sqc"


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
EXEC SQL CLOSE c2;
*/

{
#line 874 "Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 874 "Kekka.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 874 "Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 874 "Kekka.sqc"
  sqlastop(0L);
}

#line 874 "Kekka.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 882 "Kekka.sqc"

    return sqlca.sqlcode;
}
long ZdbKekkaSelectKey2( Kekka* pKey, Kekka** arrayOut, int* numOut )
{
    Kekka*      array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KekkaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 896 "Kekka.sqc"


    
/*
EXEC SQL DECLARE c3 CURSOR FOR
    SELECT
		KNSKISYMD,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		KNSGRP,
		KMKCD,
		KNSSU,
		KNSSUEDA,
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
		KSNDH,
		TRKDH,
		SKKKA
    FROM
        KEKKA
    WHERE
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KKAYSNFLG = '1' FOR READ ONLY;
*/

#line 1028 "Kekka.sqc"


    
/*
EXEC SQL OPEN c3;
*/

{
#line 1030 "Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1030 "Kekka.sqc"
  sqlaaloc(2,5,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 1030 "Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1030 "Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 1030 "Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1030 "Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 1030 "Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 1030 "Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1030 "Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 1030 "Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 1030 "Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1030 "Kekka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 1030 "Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 1030 "Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1030 "Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 1030 "Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 1030 "Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1030 "Kekka.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 1030 "Kekka.sqc"
  sqlacall((unsigned short)26,3,2,0,0L);
#line 1030 "Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1030 "Kekka.sqc"
  sqlastop(0L);
}

#line 1030 "Kekka.sqc"


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
			:ksndh,
			:trkdh,
			:skkka;
*/

{
#line 1155 "Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1155 "Kekka.sqc"
  sqlaaloc(3,120,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 1155 "Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1155 "Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 1155 "Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 1155 "Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 1155 "Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 1155 "Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 1155 "Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 1155 "Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 1155 "Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 1155 "Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 1155 "Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 1155 "Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&knssu;
#line 1155 "Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 1155 "Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)&knssueda;
#line 1155 "Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)&irihsmkbn;
#line 1155 "Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)&irikbn;
#line 1155 "Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)&ksktkbn;
#line 1155 "Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 1155 "Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)utkymd;
#line 1155 "Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 12;
#line 1155 "Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)irino;
#line 1155 "Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)&iriketflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 1155 "Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)&zssdino;
#line 1155 "Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 1155 "Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)sstcd;
#line 1155 "Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 11;
#line 1155 "Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)trid;
#line 1155 "Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[17].sqltype = 500; sql_setdlist[17].sqllen = 2;
#line 1155 "Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)&trpos;
#line 1155 "Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 11;
#line 1155 "Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)asyrckid;
#line 1155 "Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 1155 "Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)&asyrckpos;
#line 1155 "Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 8;
#line 1155 "Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)oyakmkcd;
#line 1155 "Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 3;
#line 1155 "Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)seccd;
#line 1155 "Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)&bkfkkbn;
#line 1155 "Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 1155 "Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)smpcd;
#line 1155 "Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 5;
#line 1155 "Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)bskkbn;
#line 1155 "Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 5;
#line 1155 "Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)bsklne;
#line 1155 "Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 7;
#line 1155 "Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)bskgok;
#line 1155 "Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[27].sqltype = 496; sql_setdlist[27].sqllen = 4;
#line 1155 "Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)&bskseq;
#line 1155 "Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 3;
#line 1155 "Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)bskerrsts;
#line 1155 "Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 1155 "Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)sktdh;
#line 1155 "Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 8;
#line 1155 "Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)nbkmkcd;
#line 1155 "Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&tstrflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 5;
#line 1155 "Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)zrcd;
#line 1155 "Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 1155 "Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)ysnlbl;
#line 1155 "Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 4;
#line 1155 "Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)kjno;
#line 1155 "Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&fkhkknohjkbn;
#line 1155 "Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 4;
#line 1155 "Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)tbkjno;
#line 1155 "Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&tbkjflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 25;
#line 1155 "Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)htkfkhms;
#line 1155 "Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&skflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 3;
#line 1155 "Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)tskflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 1155 "Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)tktflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 16;
#line 1155 "Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)jisksbr;
#line 1155 "Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)&kkflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[44].sqldata = (void*)&kkiriflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[45].sqltype = 500; sql_setdlist[45].sqllen = 2;
#line 1155 "Kekka.sqc"
      sql_setdlist[45].sqldata = (void*)&kkirilotno;
#line 1155 "Kekka.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[46].sqldata = (void*)&hsykflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[47].sqldata = (void*)&hskflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[48].sqldata = (void*)&hhkkflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 21;
#line 1155 "Kekka.sqc"
      sql_setdlist[49].sqldata = (void*)rawdata;
#line 1155 "Kekka.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 13;
#line 1155 "Kekka.sqc"
      sql_setdlist[50].sqldata = (void*)knskka1;
#line 1155 "Kekka.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 25;
#line 1155 "Kekka.sqc"
      sql_setdlist[51].sqldata = (void*)knskka2;
#line 1155 "Kekka.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 3;
#line 1155 "Kekka.sqc"
      sql_setdlist[52].sqldata = (void*)knskka2kbn;
#line 1155 "Kekka.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 4;
#line 1155 "Kekka.sqc"
      sql_setdlist[53].sqldata = (void*)kkahskcd;
#line 1155 "Kekka.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 25;
#line 1155 "Kekka.sqc"
      sql_setdlist[54].sqldata = (void*)hjkka;
#line 1155 "Kekka.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 1155 "Kekka.sqc"
      sql_setdlist[55].sqldata = (void*)sdi;
#line 1155 "Kekka.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 6;
#line 1155 "Kekka.sqc"
      sql_setdlist[56].sqldata = (void*)kkacmt1;
#line 1155 "Kekka.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 6;
#line 1155 "Kekka.sqc"
      sql_setdlist[57].sqldata = (void*)kkacmt2;
#line 1155 "Kekka.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[58].sqltype = 452; sql_setdlist[58].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[58].sqldata = (void*)&kkajkcd;
#line 1155 "Kekka.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[59].sqltype = 452; sql_setdlist[59].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[59].sqldata = (void*)&pncrgflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[60].sqltype = 452; sql_setdlist[60].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[60].sqldata = (void*)&knspncrgflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[61].sqltype = 452; sql_setdlist[61].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[61].sqldata = (void*)&kkaksflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[62].sqltype = 452; sql_setdlist[62].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[62].sqldata = (void*)&kkassflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[63].sqltype = 452; sql_setdlist[63].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[63].sqldata = (void*)&ijkbnm;
#line 1155 "Kekka.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sqlasetdata(3,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[56];
#line 1155 "Kekka.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)&ijkbnf;
#line 1155 "Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)&ijkbnn;
#line 1155 "Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)&tbijkbnm;
#line 1155 "Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)&tbijkbnf;
#line 1155 "Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)&tbijkbnn;
#line 1155 "Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 1155 "Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)nbdolbl;
#line 1155 "Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 4;
#line 1155 "Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)nbdoerr;
#line 1155 "Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 1155 "Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)ykdolbl;
#line 1155 "Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 1155 "Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)ykdoerr;
#line 1155 "Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 3;
#line 1155 "Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)etclbl;
#line 1155 "Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 4;
#line 1155 "Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)etcerr;
#line 1155 "Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 1155 "Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)&ctrlno;
#line 1155 "Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 1155 "Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)&knsseq;
#line 1155 "Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 1155 "Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)&bthno;
#line 1155 "Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 1155 "Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)&pltno;
#line 1155 "Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 1155 "Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)&pltseq;
#line 1155 "Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 9;
#line 1155 "Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)dtnrtts;
#line 1155 "Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 1155 "Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)dtnrdh;
#line 1155 "Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 1155 "Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)knskrdh;
#line 1155 "Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 1155 "Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)hkkdh;
#line 1155 "Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 9;
#line 1155 "Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)hkkkbdh;
#line 1155 "Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 11;
#line 1155 "Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)zkhkkyymd;
#line 1155 "Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 5;
#line 1155 "Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)zkhkkytme;
#line 1155 "Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)&frkkaflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)&gzbsflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)&hsiflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)&kkaysnflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)&tnyrkflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)&siyflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)&knsflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)&renjicflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&soukn1flg;
#line 1155 "Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)&kanrenflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)&bunkkuflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)&kesseiflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&rirekiflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)&syougoflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&keisanflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)&per100flg;
#line 1155 "Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&tousekflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)&kisyakflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)&kouseiflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[42].sqltype = 452; sql_setdlist[42].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)&syoungflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)&soukn2flg;
#line 1155 "Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[44].sqldata = (void*)&fukaptflg;
#line 1155 "Kekka.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[45].sqltype = 452; sql_setdlist[45].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[45].sqldata = (void*)&yobiflg01;
#line 1155 "Kekka.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[46].sqldata = (void*)&tobiflg02;
#line 1155 "Kekka.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[47].sqldata = (void*)&yobiflg03;
#line 1155 "Kekka.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[48].sqldata = (void*)&yobiflg04;
#line 1155 "Kekka.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[49].sqltype = 452; sql_setdlist[49].sqllen = 1;
#line 1155 "Kekka.sqc"
      sql_setdlist[49].sqldata = (void*)&yobiflg05;
#line 1155 "Kekka.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 4;
#line 1155 "Kekka.sqc"
      sql_setdlist[50].sqldata = (void*)skrycda;
#line 1155 "Kekka.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 4;
#line 1155 "Kekka.sqc"
      sql_setdlist[51].sqldata = (void*)skrycdb;
#line 1155 "Kekka.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 4;
#line 1155 "Kekka.sqc"
      sql_setdlist[52].sqldata = (void*)skrycdc;
#line 1155 "Kekka.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 27;
#line 1155 "Kekka.sqc"
      sql_setdlist[53].sqldata = (void*)ksndh;
#line 1155 "Kekka.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 27;
#line 1155 "Kekka.sqc"
      sql_setdlist[54].sqldata = (void*)trkdh;
#line 1155 "Kekka.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 25;
#line 1155 "Kekka.sqc"
      sql_setdlist[55].sqldata = (void*)skkka;
#line 1155 "Kekka.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 1155 "Kekka.sqc"
      sqlasetdata(3,64,56,sql_setdlist,0L,0L);
    }
#line 1155 "Kekka.sqc"
  sqlacall((unsigned short)25,3,0,3,0L);
#line 1155 "Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1155 "Kekka.sqc"
  sqlastop(0L);
}

#line 1155 "Kekka.sqc"


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
#line 1170 "Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1170 "Kekka.sqc"
  sqlacall((unsigned short)20,3,0,0,0L);
#line 1170 "Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1170 "Kekka.sqc"
  sqlastop(0L);
}

#line 1170 "Kekka.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 1178 "Kekka.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKekkaInsert()
 *    KEKKA レコードを挿入する
 * ■引数
 *    [I]  Kekka* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKekkaInsert( Kekka* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KekkaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 1201 "Kekka.sqc"


    
/*
EXEC SQL INSERT INTO KEKKA
    (
		KNSKISYMD,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		KNSGRP,
		KMKCD,
		KNSSU,
		KNSSUEDA,
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
		KSNDH,
		TRKDH,
		SKKKA
    ) VALUES (
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
		CURRENT TIMESTAMP,
		CURRENT TIME,
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
		CURRENT TIMESTAMP,
		CURRENT TIMESTAMP,
		:skkka
	);
*/

{
#line 1446 "Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1446 "Kekka.sqc"
  sqlaaloc(2,116,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 1446 "Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1446 "Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 1446 "Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 1446 "Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 1446 "Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 1446 "Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 1446 "Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 1446 "Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 1446 "Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 1446 "Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 1446 "Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 1446 "Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&knssu;
#line 1446 "Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 1446 "Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)&knssueda;
#line 1446 "Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)&irihsmkbn;
#line 1446 "Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)&irikbn;
#line 1446 "Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)&ksktkbn;
#line 1446 "Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 1446 "Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)utkymd;
#line 1446 "Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 12;
#line 1446 "Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)irino;
#line 1446 "Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)&iriketflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 1446 "Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)&zssdino;
#line 1446 "Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 1446 "Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)sstcd;
#line 1446 "Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 11;
#line 1446 "Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)trid;
#line 1446 "Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[17].sqltype = 500; sql_setdlist[17].sqllen = 2;
#line 1446 "Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)&trpos;
#line 1446 "Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 11;
#line 1446 "Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)asyrckid;
#line 1446 "Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 1446 "Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)&asyrckpos;
#line 1446 "Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 8;
#line 1446 "Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)oyakmkcd;
#line 1446 "Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 3;
#line 1446 "Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)seccd;
#line 1446 "Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)&bkfkkbn;
#line 1446 "Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 1446 "Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)smpcd;
#line 1446 "Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 5;
#line 1446 "Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)bskkbn;
#line 1446 "Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 5;
#line 1446 "Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)bsklne;
#line 1446 "Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 7;
#line 1446 "Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)bskgok;
#line 1446 "Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[27].sqltype = 496; sql_setdlist[27].sqllen = 4;
#line 1446 "Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)&bskseq;
#line 1446 "Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 3;
#line 1446 "Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)bskerrsts;
#line 1446 "Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 1446 "Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)sktdh;
#line 1446 "Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 8;
#line 1446 "Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)nbkmkcd;
#line 1446 "Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&tstrflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 5;
#line 1446 "Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)zrcd;
#line 1446 "Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 1446 "Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)ysnlbl;
#line 1446 "Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 4;
#line 1446 "Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)kjno;
#line 1446 "Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&fkhkknohjkbn;
#line 1446 "Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 4;
#line 1446 "Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)tbkjno;
#line 1446 "Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&tbkjflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 25;
#line 1446 "Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)htkfkhms;
#line 1446 "Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&skflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 3;
#line 1446 "Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)tskflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 1446 "Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)tktflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 16;
#line 1446 "Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)jisksbr;
#line 1446 "Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)&kkflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[44].sqldata = (void*)&kkiriflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[45].sqltype = 500; sql_setdlist[45].sqllen = 2;
#line 1446 "Kekka.sqc"
      sql_setdlist[45].sqldata = (void*)&kkirilotno;
#line 1446 "Kekka.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[46].sqldata = (void*)&hsykflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[47].sqldata = (void*)&hskflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[48].sqldata = (void*)&hhkkflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 21;
#line 1446 "Kekka.sqc"
      sql_setdlist[49].sqldata = (void*)rawdata;
#line 1446 "Kekka.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 13;
#line 1446 "Kekka.sqc"
      sql_setdlist[50].sqldata = (void*)knskka1;
#line 1446 "Kekka.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 25;
#line 1446 "Kekka.sqc"
      sql_setdlist[51].sqldata = (void*)knskka2;
#line 1446 "Kekka.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 3;
#line 1446 "Kekka.sqc"
      sql_setdlist[52].sqldata = (void*)knskka2kbn;
#line 1446 "Kekka.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 4;
#line 1446 "Kekka.sqc"
      sql_setdlist[53].sqldata = (void*)kkahskcd;
#line 1446 "Kekka.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 25;
#line 1446 "Kekka.sqc"
      sql_setdlist[54].sqldata = (void*)hjkka;
#line 1446 "Kekka.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 1446 "Kekka.sqc"
      sql_setdlist[55].sqldata = (void*)sdi;
#line 1446 "Kekka.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 6;
#line 1446 "Kekka.sqc"
      sql_setdlist[56].sqldata = (void*)kkacmt1;
#line 1446 "Kekka.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 6;
#line 1446 "Kekka.sqc"
      sql_setdlist[57].sqldata = (void*)kkacmt2;
#line 1446 "Kekka.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[58].sqltype = 452; sql_setdlist[58].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[58].sqldata = (void*)&kkajkcd;
#line 1446 "Kekka.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[59].sqltype = 452; sql_setdlist[59].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[59].sqldata = (void*)&pncrgflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[60].sqltype = 452; sql_setdlist[60].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[60].sqldata = (void*)&knspncrgflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[61].sqltype = 452; sql_setdlist[61].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[61].sqldata = (void*)&kkaksflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[62].sqltype = 452; sql_setdlist[62].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[62].sqldata = (void*)&kkassflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[63].sqltype = 452; sql_setdlist[63].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[63].sqldata = (void*)&ijkbnm;
#line 1446 "Kekka.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sqlasetdata(2,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[52];
#line 1446 "Kekka.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)&ijkbnf;
#line 1446 "Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)&ijkbnn;
#line 1446 "Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)&tbijkbnm;
#line 1446 "Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)&tbijkbnf;
#line 1446 "Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)&tbijkbnn;
#line 1446 "Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 1446 "Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)nbdolbl;
#line 1446 "Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 4;
#line 1446 "Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)nbdoerr;
#line 1446 "Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 1446 "Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)ykdolbl;
#line 1446 "Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 1446 "Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)ykdoerr;
#line 1446 "Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 3;
#line 1446 "Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)etclbl;
#line 1446 "Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 4;
#line 1446 "Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)etcerr;
#line 1446 "Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 1446 "Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)&ctrlno;
#line 1446 "Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 1446 "Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)&knsseq;
#line 1446 "Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 1446 "Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)&bthno;
#line 1446 "Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 1446 "Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)&pltno;
#line 1446 "Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 1446 "Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)&pltseq;
#line 1446 "Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 9;
#line 1446 "Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)dtnrtts;
#line 1446 "Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 1446 "Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)dtnrdh;
#line 1446 "Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 1446 "Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)knskrdh;
#line 1446 "Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 11;
#line 1446 "Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)zkhkkyymd;
#line 1446 "Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 5;
#line 1446 "Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)zkhkkytme;
#line 1446 "Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)&frkkaflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)&gzbsflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)&hsiflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)&kkaysnflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)&tnyrkflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)&siyflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)&knsflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)&renjicflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)&soukn1flg;
#line 1446 "Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)&kanrenflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&bunkkuflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)&kesseiflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)&rirekiflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)&syougoflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&keisanflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)&per100flg;
#line 1446 "Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&tousekflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)&kisyakflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&kouseiflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)&syoungflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)&soukn2flg;
#line 1446 "Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[42].sqltype = 452; sql_setdlist[42].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)&fukaptflg;
#line 1446 "Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)&yobiflg01;
#line 1446 "Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[44].sqldata = (void*)&tobiflg02;
#line 1446 "Kekka.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[45].sqltype = 452; sql_setdlist[45].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[45].sqldata = (void*)&yobiflg03;
#line 1446 "Kekka.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[46].sqldata = (void*)&yobiflg04;
#line 1446 "Kekka.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 1446 "Kekka.sqc"
      sql_setdlist[47].sqldata = (void*)&yobiflg05;
#line 1446 "Kekka.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 4;
#line 1446 "Kekka.sqc"
      sql_setdlist[48].sqldata = (void*)skrycda;
#line 1446 "Kekka.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 4;
#line 1446 "Kekka.sqc"
      sql_setdlist[49].sqldata = (void*)skrycdb;
#line 1446 "Kekka.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 4;
#line 1446 "Kekka.sqc"
      sql_setdlist[50].sqldata = (void*)skrycdc;
#line 1446 "Kekka.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 25;
#line 1446 "Kekka.sqc"
      sql_setdlist[51].sqldata = (void*)skkka;
#line 1446 "Kekka.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 1446 "Kekka.sqc"
      sqlasetdata(2,64,52,sql_setdlist,0L,0L);
    }
#line 1446 "Kekka.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 1446 "Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1446 "Kekka.sqc"
  sqlastop(0L);
}

#line 1446 "Kekka.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 1451 "Kekka.sqc"

    return sqlca.sqlcode;
}

// 結果情報をオーダー情報から作成しインサートする。
long ZdbKekkaInsert2( Kekka* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KekkaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 1464 "Kekka.sqc"


    
/*
EXEC SQL INSERT INTO KEKKA
    (SELECT 
		KNSKISYMD,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		KNSGRP,
		KMKCD,
		KNSSU,
		KNSSUEDA,
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
		(' ') as BSKKBN,
		(' ') as BSKLNE,
		(' ') as BSKGOK,
		(0) as BSKSEQ,
		(' ') as BSKERRSTS,
		(CURRENT TIMESTAMP) as SKTDH,
		(' ') as NBKMKCD,
		(SELECT TSTRFLG FROM KMKMST WHERE KMKMST.KNSGRP = KENORDER.KNSGRP AND KMKMST.KMKCD = KENORDER.KMKCD) as TSTRFLG,
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
		(' ') as JISKSBR,
		KKFLG,
		KKIRIFLG,
		KKIRILOTNO,
		(' ') as HSYKFLG,
		(' ') as HSKFLG,
		(' ') as HHKKFLG,
		(' ') as RAWDATA,
		(' ') as KNSKKA1,
		(' ') as KNSKKA2,
		(' ') as KNSKKA2KBN,
		(' ') as KKAHSKCD,
		(' ') as HJKKA,
		('   ') as SDI,
		(' ') as KKACMT1,
		(' ') as KKACMT2,
		('3') as KKAJKCD,
		('0') as PNCRGFLG,
		('0') as KNSPNCRGFLG,
		('0') as KKAKSFLG,
		('0') as KKASSFLG,
		(' ') as IJKBNM,
		(' ') as IJKBNF,
		(' ') as IJKBNN,
		(' ') as TBIJKBNM,
		(' ') as TBIJKBNF,
		(' ') as TBIJKBNN,
		(' ') as NBDOLBL,
		(' ') as NBDOERR,
		(' ') as YKDOLBL,
		(' ') as YKDOERR,
		(' ') as ETCLBL,
		(' ') as ETCERR,
		(0) as CTRLNO,
		KNSSEQ,
		BTHNO,
		(0) as PLTNO,
		(0) as PLTSEQ,
		(' ') as DTNRTTS,
		(CURRENT TIMESTAMP) as DTNRDH,
		('1000-01-01 00:00:01') as KNSKRDH,
		('1000-01-01 00:00:01') as HKKDH,
		('00:00:01') as HKKKBDH,
		('1000-01-01') as ZKHKKYYMD,
		('    ') as ZKHKKYTME,
		('0') as FRKKAFLG,
		('0') as GZBSFLG,
		('1') as HSIFLG,
		('1') as KKAYSNFLG,
		(' ') as TNYRKFLG,
		('1') as SIYFLG,
		('K') as KNSFLG,
		('0') as GENKAIFLG,
		('0') as SOUKN1FLG,
		('0') as KANRENFLG,
		('0') as BUNKKUFLG,
		('0') as KESSEIFLG,
		('0') as RIREKIFLG,
		('0') as SYOUGOFLG,
		('0') as KEISANFLG,
		('0') as PER100FLG,
		('0') as TOUSEKFLG,
		('0') as KISYAKFLG,
		('0') as KOUSEIFLG,
		('0') as SYOUNGFLG,
		('0') as SOUKN2FLG,
		('0') as FUKAPTFLG,
		('0') as YOBIFLG01,
		('0') as TOBIFLG02,
		('0') as YOBIFLG03,
		('0') as YOBIFLG04,
		('0') as YOBIFLG05,
		(' ') as SKRYCDA,
		(' ') as SKRYCDB,
		(' ') as SKRYCDC,
		(CURRENT TIMESTAMP) as KSNDH,
		(CURRENT TIMESTAMP) as TRKDH,
		(' ') as SKKKA
	FROM KENORDER WHERE
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KNSSU = :knssu AND
		KNSSUEDA = :knssueda
    );
*/

{
#line 1596 "Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1596 "Kekka.sqc"
  sqlaaloc(2,7,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 1596 "Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1596 "Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 1596 "Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1596 "Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 1596 "Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 1596 "Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1596 "Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 1596 "Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 1596 "Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1596 "Kekka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 1596 "Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 1596 "Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1596 "Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 1596 "Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 1596 "Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1596 "Kekka.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 1596 "Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)&knssu;
#line 1596 "Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1596 "Kekka.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 1596 "Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&knssueda;
#line 1596 "Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1596 "Kekka.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 1596 "Kekka.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 1596 "Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1596 "Kekka.sqc"
  sqlastop(0L);
}

#line 1596 "Kekka.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 1601 "Kekka.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKekkaUpdate()
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
long ZdbKekkaUpdate( Kekka* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KekkaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 1625 "Kekka.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 1626 "Kekka.sqc"


    
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
		KSNDH,
		SKKKA
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
		CURRENT TIMESTAMP,
		:skkka
    ) WHERE
		KNTNO = :kntno AND
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd AND
		KNSSU = :knssu AND
		KNSSUEDA = :knssueda AND
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd;
*/

{
#line 1862 "Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1862 "Kekka.sqc"
  sqlaaloc(2,118,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 1862 "Kekka.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)&kntketflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)&irihsmkbn;
#line 1862 "Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)&irikbn;
#line 1862 "Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)&ksktkbn;
#line 1862 "Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 1862 "Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)utkymd;
#line 1862 "Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 12;
#line 1862 "Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)irino;
#line 1862 "Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&iriketflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 1862 "Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)&zssdino;
#line 1862 "Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 8;
#line 1862 "Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)sstcd;
#line 1862 "Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 1862 "Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)trid;
#line 1862 "Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[10].sqltype = 500; sql_setdlist[10].sqllen = 2;
#line 1862 "Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)&trpos;
#line 1862 "Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 1862 "Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)asyrckid;
#line 1862 "Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 1862 "Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)&asyrckpos;
#line 1862 "Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 8;
#line 1862 "Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)oyakmkcd;
#line 1862 "Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 3;
#line 1862 "Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)seccd;
#line 1862 "Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[15].sqltype = 452; sql_setdlist[15].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)&bkfkkbn;
#line 1862 "Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 8;
#line 1862 "Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)smpcd;
#line 1862 "Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 5;
#line 1862 "Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)bskkbn;
#line 1862 "Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 5;
#line 1862 "Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)bsklne;
#line 1862 "Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 7;
#line 1862 "Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)bskgok;
#line 1862 "Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[20].sqltype = 496; sql_setdlist[20].sqllen = 4;
#line 1862 "Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)&bskseq;
#line 1862 "Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 3;
#line 1862 "Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)bskerrsts;
#line 1862 "Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 27;
#line 1862 "Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)sktdh;
#line 1862 "Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 1862 "Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)nbkmkcd;
#line 1862 "Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)&tstrflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 5;
#line 1862 "Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)zrcd;
#line 1862 "Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 3;
#line 1862 "Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)ysnlbl;
#line 1862 "Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 4;
#line 1862 "Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)kjno;
#line 1862 "Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)&fkhkknohjkbn;
#line 1862 "Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 4;
#line 1862 "Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)tbkjno;
#line 1862 "Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)&tbkjflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 25;
#line 1862 "Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)htkfkhms;
#line 1862 "Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)&skflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 1862 "Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)tskflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 3;
#line 1862 "Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)tktflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 16;
#line 1862 "Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)jisksbr;
#line 1862 "Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)&kkflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&kkiriflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[38].sqltype = 500; sql_setdlist[38].sqllen = 2;
#line 1862 "Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)&kkirilotno;
#line 1862 "Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&hsykflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)&hskflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)&hhkkflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 21;
#line 1862 "Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)rawdata;
#line 1862 "Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 13;
#line 1862 "Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)knskka1;
#line 1862 "Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 25;
#line 1862 "Kekka.sqc"
      sql_setdlist[44].sqldata = (void*)knskka2;
#line 1862 "Kekka.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 3;
#line 1862 "Kekka.sqc"
      sql_setdlist[45].sqldata = (void*)knskka2kbn;
#line 1862 "Kekka.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 4;
#line 1862 "Kekka.sqc"
      sql_setdlist[46].sqldata = (void*)kkahskcd;
#line 1862 "Kekka.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 25;
#line 1862 "Kekka.sqc"
      sql_setdlist[47].sqldata = (void*)hjkka;
#line 1862 "Kekka.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 4;
#line 1862 "Kekka.sqc"
      sql_setdlist[48].sqldata = (void*)sdi;
#line 1862 "Kekka.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 6;
#line 1862 "Kekka.sqc"
      sql_setdlist[49].sqldata = (void*)kkacmt1;
#line 1862 "Kekka.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 6;
#line 1862 "Kekka.sqc"
      sql_setdlist[50].sqldata = (void*)kkacmt2;
#line 1862 "Kekka.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[51].sqltype = 452; sql_setdlist[51].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[51].sqldata = (void*)&kkajkcd;
#line 1862 "Kekka.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[52].sqltype = 452; sql_setdlist[52].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[52].sqldata = (void*)&pncrgflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[53].sqltype = 452; sql_setdlist[53].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[53].sqldata = (void*)&knspncrgflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[54].sqltype = 452; sql_setdlist[54].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[54].sqldata = (void*)&kkaksflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[55].sqltype = 452; sql_setdlist[55].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[55].sqldata = (void*)&kkassflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[56].sqltype = 452; sql_setdlist[56].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[56].sqldata = (void*)&ijkbnm;
#line 1862 "Kekka.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[57].sqltype = 452; sql_setdlist[57].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[57].sqldata = (void*)&ijkbnf;
#line 1862 "Kekka.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[58].sqltype = 452; sql_setdlist[58].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[58].sqldata = (void*)&ijkbnn;
#line 1862 "Kekka.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[59].sqltype = 452; sql_setdlist[59].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[59].sqldata = (void*)&tbijkbnm;
#line 1862 "Kekka.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[60].sqltype = 452; sql_setdlist[60].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[60].sqldata = (void*)&tbijkbnf;
#line 1862 "Kekka.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[61].sqltype = 452; sql_setdlist[61].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[61].sqldata = (void*)&tbijkbnn;
#line 1862 "Kekka.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[62].sqltype = 460; sql_setdlist[62].sqllen = 3;
#line 1862 "Kekka.sqc"
      sql_setdlist[62].sqldata = (void*)nbdolbl;
#line 1862 "Kekka.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[63].sqltype = 460; sql_setdlist[63].sqllen = 4;
#line 1862 "Kekka.sqc"
      sql_setdlist[63].sqldata = (void*)nbdoerr;
#line 1862 "Kekka.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sqlasetdata(2,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[54];
#line 1862 "Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 1862 "Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)ykdolbl;
#line 1862 "Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 4;
#line 1862 "Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)ykdoerr;
#line 1862 "Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 1862 "Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)etclbl;
#line 1862 "Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 4;
#line 1862 "Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)etcerr;
#line 1862 "Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 1862 "Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)&ctrlno;
#line 1862 "Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 1862 "Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)&knsseq;
#line 1862 "Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 1862 "Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&bthno;
#line 1862 "Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 1862 "Kekka.sqc"
      sql_setdlist[7].sqldata = (void*)&pltno;
#line 1862 "Kekka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 1862 "Kekka.sqc"
      sql_setdlist[8].sqldata = (void*)&pltseq;
#line 1862 "Kekka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 9;
#line 1862 "Kekka.sqc"
      sql_setdlist[9].sqldata = (void*)dtnrtts;
#line 1862 "Kekka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 27;
#line 1862 "Kekka.sqc"
      sql_setdlist[10].sqldata = (void*)dtnrdh;
#line 1862 "Kekka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 27;
#line 1862 "Kekka.sqc"
      sql_setdlist[11].sqldata = (void*)knskrdh;
#line 1862 "Kekka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 27;
#line 1862 "Kekka.sqc"
      sql_setdlist[12].sqldata = (void*)hkkdh;
#line 1862 "Kekka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 1862 "Kekka.sqc"
      sql_setdlist[13].sqldata = (void*)hkkkbdh;
#line 1862 "Kekka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 11;
#line 1862 "Kekka.sqc"
      sql_setdlist[14].sqldata = (void*)zkhkkyymd;
#line 1862 "Kekka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 5;
#line 1862 "Kekka.sqc"
      sql_setdlist[15].sqldata = (void*)zkhkkytme;
#line 1862 "Kekka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[16].sqldata = (void*)&frkkaflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[17].sqldata = (void*)&gzbsflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[18].sqldata = (void*)&hsiflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[19].sqldata = (void*)&kkaysnflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[20].sqldata = (void*)&tnyrkflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[21].sqldata = (void*)&siyflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[22].sqldata = (void*)&knsflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[23].sqldata = (void*)&renjicflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[24].sqldata = (void*)&soukn1flg;
#line 1862 "Kekka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[25].sqldata = (void*)&kanrenflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[26].sqldata = (void*)&bunkkuflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[27].sqldata = (void*)&kesseiflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[28].sqldata = (void*)&rirekiflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[29].sqldata = (void*)&syougoflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[30].sqldata = (void*)&keisanflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[31].sqldata = (void*)&per100flg;
#line 1862 "Kekka.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[32].sqldata = (void*)&tousekflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[33].sqldata = (void*)&kisyakflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[34].sqldata = (void*)&kouseiflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[35].sqldata = (void*)&syoungflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[36].sqldata = (void*)&soukn2flg;
#line 1862 "Kekka.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[37].sqldata = (void*)&fukaptflg;
#line 1862 "Kekka.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[38].sqldata = (void*)&yobiflg01;
#line 1862 "Kekka.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[39].sqldata = (void*)&tobiflg02;
#line 1862 "Kekka.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[40].sqldata = (void*)&yobiflg03;
#line 1862 "Kekka.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[41].sqldata = (void*)&yobiflg04;
#line 1862 "Kekka.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[42].sqltype = 452; sql_setdlist[42].sqllen = 1;
#line 1862 "Kekka.sqc"
      sql_setdlist[42].sqldata = (void*)&yobiflg05;
#line 1862 "Kekka.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 4;
#line 1862 "Kekka.sqc"
      sql_setdlist[43].sqldata = (void*)skrycda;
#line 1862 "Kekka.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 4;
#line 1862 "Kekka.sqc"
      sql_setdlist[44].sqldata = (void*)skrycdb;
#line 1862 "Kekka.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 4;
#line 1862 "Kekka.sqc"
      sql_setdlist[45].sqldata = (void*)skrycdc;
#line 1862 "Kekka.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 25;
#line 1862 "Kekka.sqc"
      sql_setdlist[46].sqldata = (void*)skkka;
#line 1862 "Kekka.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 14;
#line 1862 "Kekka.sqc"
      sql_setdlist[47].sqldata = (void*)kntno;
#line 1862 "Kekka.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 17;
#line 1862 "Kekka.sqc"
      sql_setdlist[48].sqldata = (void*)knsgrp;
#line 1862 "Kekka.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 8;
#line 1862 "Kekka.sqc"
      sql_setdlist[49].sqldata = (void*)kmkcd;
#line 1862 "Kekka.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[50].sqltype = 500; sql_setdlist[50].sqllen = 2;
#line 1862 "Kekka.sqc"
      sql_setdlist[50].sqldata = (void*)&knssu;
#line 1862 "Kekka.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[51].sqltype = 500; sql_setdlist[51].sqllen = 2;
#line 1862 "Kekka.sqc"
      sql_setdlist[51].sqldata = (void*)&knssueda;
#line 1862 "Kekka.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 11;
#line 1862 "Kekka.sqc"
      sql_setdlist[52].sqldata = (void*)knskisymd;
#line 1862 "Kekka.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 11;
#line 1862 "Kekka.sqc"
      sql_setdlist[53].sqldata = (void*)sriymd;
#line 1862 "Kekka.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 1862 "Kekka.sqc"
      sqlasetdata(2,64,54,sql_setdlist,0L,0L);
    }
#line 1862 "Kekka.sqc"
  sqlacall((unsigned short)24,6,2,0,0L);
#line 1862 "Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1862 "Kekka.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 1862 "Kekka.sqc"
  sqlastop(0L);
}

#line 1862 "Kekka.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 1867 "Kekka.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 1871 "Kekka.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKekkaDelete()
 *    KEKKA レコードを削除する
 * ■引数
 *    [I]  Kekka* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKekkaDelete( Kekka* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KekkaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 1895 "Kekka.sqc"


    
/*
EXEC SQL DELETE FROM KEKKA
    WHERE
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd AND
		KNSSU = :knssu AND
		KNSSUEDA = :knssueda;
*/

{
#line 1905 "Kekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1905 "Kekka.sqc"
  sqlaaloc(2,7,9,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 1905 "Kekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1905 "Kekka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 1905 "Kekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1905 "Kekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 1905 "Kekka.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 1905 "Kekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1905 "Kekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 1905 "Kekka.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 1905 "Kekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1905 "Kekka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 1905 "Kekka.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 1905 "Kekka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1905 "Kekka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 1905 "Kekka.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 1905 "Kekka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1905 "Kekka.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 1905 "Kekka.sqc"
      sql_setdlist[5].sqldata = (void*)&knssu;
#line 1905 "Kekka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1905 "Kekka.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 1905 "Kekka.sqc"
      sql_setdlist[6].sqldata = (void*)&knssueda;
#line 1905 "Kekka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1905 "Kekka.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 1905 "Kekka.sqc"
  sqlacall((unsigned short)24,7,2,0,0L);
#line 1905 "Kekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1905 "Kekka.sqc"
  sqlastop(0L);
}

#line 1905 "Kekka.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 1910 "Kekka.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
