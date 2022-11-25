static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,48,65,75,106,84,81,70,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,51,90,84,85,78,69,50,32,0,0,0,0,0,0,0,0,
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


#line 1 "KekkaIrai.sqc"
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


#line 24 "KekkaIrai.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "KekkaIrai.sqc"

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

	/* ADD 2006-09-09 Nagata */
	char    skkacmt1[6];
	char    skkacmt2[6];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 154 "KekkaIrai.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Kekka

BmlDMMInfo	KekkaIraiArray[] = {
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
long ZdbKekkaSelectIrai( Kekka* pKey, Kekka** arrayOut, int* numOut )
{
    Kekka*      array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KekkaIraiArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 309 "KekkaIrai.sqc"


    
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
		IRINO = :irino AND
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KKAYSNFLG = '1' AND
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd FOR READ ONLY;
*/

#line 441 "KekkaIrai.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 443 "KekkaIrai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 443 "KekkaIrai.sqc"
  sqlaaloc(2,5,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 443 "KekkaIrai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 12;
#line 443 "KekkaIrai.sqc"
      sql_setdlist[0].sqldata = (void*)irino;
#line 443 "KekkaIrai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 443 "KekkaIrai.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 443 "KekkaIrai.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 443 "KekkaIrai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 443 "KekkaIrai.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 443 "KekkaIrai.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 443 "KekkaIrai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 443 "KekkaIrai.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 443 "KekkaIrai.sqc"
      sql_setdlist[3].sqldata = (void*)knskisymd;
#line 443 "KekkaIrai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 443 "KekkaIrai.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 443 "KekkaIrai.sqc"
      sql_setdlist[4].sqldata = (void*)sriymd;
#line 443 "KekkaIrai.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 443 "KekkaIrai.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 443 "KekkaIrai.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 443 "KekkaIrai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 443 "KekkaIrai.sqc"
  sqlastop(0L);
}

#line 443 "KekkaIrai.sqc"


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
#line 568 "KekkaIrai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 568 "KekkaIrai.sqc"
  sqlaaloc(3,120,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 568 "KekkaIrai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[6].sqldata = (void*)&knssu;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[7].sqldata = (void*)&knssueda;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[8].sqldata = (void*)&irihsmkbn;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[9].sqldata = (void*)&irikbn;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[10].sqldata = (void*)&ksktkbn;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[11].sqldata = (void*)utkymd;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 12;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[12].sqldata = (void*)irino;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[13].sqldata = (void*)&iriketflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[14].sqldata = (void*)&zssdino;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[15].sqldata = (void*)sstcd;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 11;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[16].sqldata = (void*)trid;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[17].sqltype = 500; sql_setdlist[17].sqllen = 2;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[17].sqldata = (void*)&trpos;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 11;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[18].sqldata = (void*)asyrckid;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[19].sqldata = (void*)&asyrckpos;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 8;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[20].sqldata = (void*)oyakmkcd;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 3;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[21].sqldata = (void*)seccd;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[22].sqldata = (void*)&bkfkkbn;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[23].sqldata = (void*)smpcd;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 5;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[24].sqldata = (void*)bskkbn;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 5;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[25].sqldata = (void*)bsklne;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 7;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[26].sqldata = (void*)bskgok;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[27].sqltype = 496; sql_setdlist[27].sqllen = 4;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[27].sqldata = (void*)&bskseq;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 3;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[28].sqldata = (void*)bskerrsts;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[29].sqldata = (void*)sktdh;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 8;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[30].sqldata = (void*)nbkmkcd;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[31].sqldata = (void*)&tstrflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 5;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[32].sqldata = (void*)zrcd;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[33].sqldata = (void*)ysnlbl;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 4;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[34].sqldata = (void*)kjno;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[35].sqldata = (void*)&fkhkknohjkbn;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 4;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[36].sqldata = (void*)tbkjno;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[37].sqldata = (void*)&tbkjflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 25;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[38].sqldata = (void*)htkfkhms;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[39].sqldata = (void*)&skflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 3;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[40].sqldata = (void*)tskflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[41].sqldata = (void*)tktflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 16;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[42].sqldata = (void*)jisksbr;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[43].sqldata = (void*)&kkflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[44].sqldata = (void*)&kkiriflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[45].sqltype = 500; sql_setdlist[45].sqllen = 2;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[45].sqldata = (void*)&kkirilotno;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[46].sqldata = (void*)&hsykflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[47].sqldata = (void*)&hskflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[48].sqldata = (void*)&hhkkflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 21;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[49].sqldata = (void*)rawdata;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 13;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[50].sqldata = (void*)knskka1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 25;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[51].sqldata = (void*)knskka2;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 3;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[52].sqldata = (void*)knskka2kbn;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 4;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[53].sqldata = (void*)kkahskcd;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 25;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[54].sqldata = (void*)hjkka;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[55].sqldata = (void*)sdi;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 6;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[56].sqldata = (void*)kkacmt1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 6;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[57].sqldata = (void*)kkacmt2;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[58].sqltype = 452; sql_setdlist[58].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[58].sqldata = (void*)&kkajkcd;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[59].sqltype = 452; sql_setdlist[59].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[59].sqldata = (void*)&pncrgflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[60].sqltype = 452; sql_setdlist[60].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[60].sqldata = (void*)&knspncrgflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[61].sqltype = 452; sql_setdlist[61].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[61].sqldata = (void*)&kkaksflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[62].sqltype = 452; sql_setdlist[62].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[62].sqldata = (void*)&kkassflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[63].sqltype = 452; sql_setdlist[63].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[63].sqldata = (void*)&ijkbnm;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sqlasetdata(3,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[56];
#line 568 "KekkaIrai.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[0].sqldata = (void*)&ijkbnf;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[1].sqldata = (void*)&ijkbnn;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[2].sqldata = (void*)&tbijkbnm;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[3].sqldata = (void*)&tbijkbnf;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[4].sqldata = (void*)&tbijkbnn;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[5].sqldata = (void*)nbdolbl;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 4;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[6].sqldata = (void*)nbdoerr;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[7].sqldata = (void*)ykdolbl;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[8].sqldata = (void*)ykdoerr;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 3;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[9].sqldata = (void*)etclbl;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 4;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[10].sqldata = (void*)etcerr;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[11].sqldata = (void*)&ctrlno;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[12].sqldata = (void*)&knsseq;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[13].sqldata = (void*)&bthno;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[14].sqldata = (void*)&pltno;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[15].sqldata = (void*)&pltseq;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 9;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[16].sqldata = (void*)dtnrtts;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[17].sqldata = (void*)dtnrdh;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[18].sqldata = (void*)knskrdh;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[19].sqldata = (void*)hkkdh;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 9;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[20].sqldata = (void*)hkkkbdh;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 11;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[21].sqldata = (void*)zkhkkyymd;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 5;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[22].sqldata = (void*)zkhkkytme;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[23].sqldata = (void*)&frkkaflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[24].sqldata = (void*)&gzbsflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[25].sqldata = (void*)&hsiflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[26].sqldata = (void*)&kkaysnflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[27].sqldata = (void*)&tnyrkflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[28].sqldata = (void*)&siyflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[29].sqldata = (void*)&knsflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[30].sqldata = (void*)&renjicflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[31].sqldata = (void*)&soukn1flg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[32].sqldata = (void*)&kanrenflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[33].sqldata = (void*)&bunkkuflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[34].sqldata = (void*)&kesseiflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[35].sqldata = (void*)&rirekiflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[36].sqldata = (void*)&syougoflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[37].sqldata = (void*)&keisanflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[38].sqldata = (void*)&per100flg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[39].sqldata = (void*)&tousekflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[40].sqldata = (void*)&kisyakflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[41].sqldata = (void*)&kouseiflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[42].sqltype = 452; sql_setdlist[42].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[42].sqldata = (void*)&syoungflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[43].sqldata = (void*)&soukn2flg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[44].sqldata = (void*)&fukaptflg;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[45].sqltype = 452; sql_setdlist[45].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[45].sqldata = (void*)&yobiflg01;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[46].sqldata = (void*)&tobiflg02;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[47].sqldata = (void*)&yobiflg03;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[48].sqldata = (void*)&yobiflg04;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[49].sqltype = 452; sql_setdlist[49].sqllen = 1;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[49].sqldata = (void*)&yobiflg05;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 4;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[50].sqldata = (void*)skrycda;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 4;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[51].sqldata = (void*)skrycdb;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 4;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[52].sqldata = (void*)skrycdc;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 27;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[53].sqldata = (void*)ksndh;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 27;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[54].sqldata = (void*)trkdh;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 25;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[55].sqldata = (void*)skkka;
#line 568 "KekkaIrai.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 568 "KekkaIrai.sqc"
      sqlasetdata(3,64,56,sql_setdlist,0L,0L);
    }
#line 568 "KekkaIrai.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 568 "KekkaIrai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 568 "KekkaIrai.sqc"
  sqlastop(0L);
}

#line 568 "KekkaIrai.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kekka*)ZbmlRealloc( array,
                                    sizeof( Kekka ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kekka ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KekkaIraiArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 583 "KekkaIrai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 583 "KekkaIrai.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 583 "KekkaIrai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 583 "KekkaIrai.sqc"
  sqlastop(0L);
}

#line 583 "KekkaIrai.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 591 "KekkaIrai.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKekkaUpdateJKCD()
 *    KEKKA 状況コードの初期化
 * ■引数
 *    [I]  Kekka* pKey       取得するレコードのキー
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 *    ADD 2006/08/03  Osada [報告済み]は対象外とする
 ******************************************************************************/
long ZdbKekkaUpdateJKCD( Kekka* pKey )
{
    if( !ZbmlMapStructToHost( (char*)pKey, KekkaIraiArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 611 "KekkaIrai.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 612 "KekkaIrai.sqc"


    
/*
EXEC SQL UPDATE KEKKA
	SET KKAJKCD = '1',
		KKAYSNFLG = ' ',
		SIYFLG = ' '
    WHERE
		KNTNO = :kntno AND
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd	AND
		KNSFLG != 'E';
*/

{
#line 624 "KekkaIrai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 624 "KekkaIrai.sqc"
  sqlaaloc(2,5,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 624 "KekkaIrai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 14;
#line 624 "KekkaIrai.sqc"
      sql_setdlist[0].sqldata = (void*)kntno;
#line 624 "KekkaIrai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 624 "KekkaIrai.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 624 "KekkaIrai.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 624 "KekkaIrai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 624 "KekkaIrai.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 624 "KekkaIrai.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 624 "KekkaIrai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 624 "KekkaIrai.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 624 "KekkaIrai.sqc"
      sql_setdlist[3].sqldata = (void*)knskisymd;
#line 624 "KekkaIrai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 624 "KekkaIrai.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 624 "KekkaIrai.sqc"
      sql_setdlist[4].sqldata = (void*)sriymd;
#line 624 "KekkaIrai.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 624 "KekkaIrai.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 624 "KekkaIrai.sqc"
  sqlacall((unsigned short)24,2,2,0,0L);
#line 624 "KekkaIrai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 624 "KekkaIrai.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 624 "KekkaIrai.sqc"
  sqlastop(0L);
}

#line 624 "KekkaIrai.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 629 "KekkaIrai.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 633 "KekkaIrai.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKekkaUpdateNbYk()
 *    KEKKA 乳び溶血セット
 * ■引数
 *    [I]  Kekka* pKey       取得するレコードのキー
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 *2006-09-05 Nagata 既に入っている場合は更新しない
 ******************************************************************************/
long ZdbKekkaUpdateNbYk( Kekka* pKey )
{
    if( !ZbmlMapStructToHost( (char*)pKey, KekkaIraiArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 653 "KekkaIrai.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 654 "KekkaIrai.sqc"


    
/*
EXEC SQL UPDATE KEKKA
	SET	NBDOLBL	= :nbdolbl,
		NBDOERR	= :nbdoerr,
		YKDOLBL	= :ykdolbl,
		YKDOERR	= :ykdoerr,
		ETCLBL	= :etclbl,
		ETCERR	= :etcerr
    WHERE
		KNSKISYMD	= :knskisymd	AND
		ASYRCKID	= :asyrckid		AND
		ASYRCKPOS	= :asyrckpos	AND
		NBDOLBL = ' ' AND
		KNSFLG != 'E';
*/

{
#line 668 "KekkaIrai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 668 "KekkaIrai.sqc"
  sqlaaloc(2,9,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 668 "KekkaIrai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[0].sqldata = (void*)nbdolbl;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 4;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[1].sqldata = (void*)nbdoerr;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[2].sqldata = (void*)ykdolbl;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 4;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[3].sqldata = (void*)ykdoerr;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 3;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[4].sqldata = (void*)etclbl;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 4;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[5].sqldata = (void*)etcerr;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[6].sqldata = (void*)knskisymd;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[7].sqldata = (void*)asyrckid;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[8].sqldata = (void*)&asyrckpos;
#line 668 "KekkaIrai.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 668 "KekkaIrai.sqc"
      sqlasetdata(2,0,9,sql_setdlist,0L,0L);
    }
#line 668 "KekkaIrai.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 668 "KekkaIrai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 668 "KekkaIrai.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 668 "KekkaIrai.sqc"
  sqlastop(0L);
}

#line 668 "KekkaIrai.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 673 "KekkaIrai.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 677 "KekkaIrai.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKekkaSelectRckPos
 *    KEKKA 同ラックID、同ポジションデータ取得
 * ■引数
 *    [I]  Kekka* pKey       取得するレコードのキー
 *    [O]  Kekka** arrayOut     取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKekkaSelectRckPos( Kekka* pKey, Kekka** arrayOut, int* numOut )
{
    Kekka*      array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KekkaIraiArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 703 "KekkaIrai.sqc"


    
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
		KNSKISYMD	= :knskisymd	AND
		/- 2006-08-23 Nagata -/
		/- KNSSU		= :knssu		AND -/
		ASYRCKID	= :asyrckid		AND
		ASYRCKPOS	= :asyrckpos AND
		/- 2006-08-24 Nagata -/
		KNSFLG not in ('E','M')
		ORDER BY KNSSU DESC;
*/

#line 837 "KekkaIrai.sqc"


    
/*
EXEC SQL OPEN c3;
*/

{
#line 839 "KekkaIrai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 839 "KekkaIrai.sqc"
  sqlaaloc(2,3,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 839 "KekkaIrai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 839 "KekkaIrai.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 839 "KekkaIrai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 839 "KekkaIrai.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 839 "KekkaIrai.sqc"
      sql_setdlist[1].sqldata = (void*)asyrckid;
#line 839 "KekkaIrai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 839 "KekkaIrai.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 839 "KekkaIrai.sqc"
      sql_setdlist[2].sqldata = (void*)&asyrckpos;
#line 839 "KekkaIrai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 839 "KekkaIrai.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 839 "KekkaIrai.sqc"
  sqlacall((unsigned short)26,4,2,0,0L);
#line 839 "KekkaIrai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 839 "KekkaIrai.sqc"
  sqlastop(0L);
}

#line 839 "KekkaIrai.sqc"


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
#line 964 "KekkaIrai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 964 "KekkaIrai.sqc"
  sqlaaloc(3,120,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 964 "KekkaIrai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[6].sqldata = (void*)&knssu;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[7].sqldata = (void*)&knssueda;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[8].sqldata = (void*)&irihsmkbn;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[9].sqldata = (void*)&irikbn;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[10].sqldata = (void*)&ksktkbn;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[11].sqldata = (void*)utkymd;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 12;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[12].sqldata = (void*)irino;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[13].sqldata = (void*)&iriketflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[14].sqldata = (void*)&zssdino;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[15].sqldata = (void*)sstcd;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 11;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[16].sqldata = (void*)trid;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[17].sqltype = 500; sql_setdlist[17].sqllen = 2;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[17].sqldata = (void*)&trpos;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 11;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[18].sqldata = (void*)asyrckid;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[19].sqldata = (void*)&asyrckpos;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 8;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[20].sqldata = (void*)oyakmkcd;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 3;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[21].sqldata = (void*)seccd;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[22].sqldata = (void*)&bkfkkbn;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[23].sqldata = (void*)smpcd;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 5;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[24].sqldata = (void*)bskkbn;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 5;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[25].sqldata = (void*)bsklne;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 7;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[26].sqldata = (void*)bskgok;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[27].sqltype = 496; sql_setdlist[27].sqllen = 4;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[27].sqldata = (void*)&bskseq;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 3;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[28].sqldata = (void*)bskerrsts;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[29].sqldata = (void*)sktdh;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 8;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[30].sqldata = (void*)nbkmkcd;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[31].sqldata = (void*)&tstrflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 5;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[32].sqldata = (void*)zrcd;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[33].sqldata = (void*)ysnlbl;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 4;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[34].sqldata = (void*)kjno;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[35].sqldata = (void*)&fkhkknohjkbn;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 4;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[36].sqldata = (void*)tbkjno;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[37].sqldata = (void*)&tbkjflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 25;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[38].sqldata = (void*)htkfkhms;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[39].sqldata = (void*)&skflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 3;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[40].sqldata = (void*)tskflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[41].sqldata = (void*)tktflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 16;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[42].sqldata = (void*)jisksbr;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[43].sqldata = (void*)&kkflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[44].sqldata = (void*)&kkiriflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[45].sqltype = 500; sql_setdlist[45].sqllen = 2;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[45].sqldata = (void*)&kkirilotno;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[46].sqldata = (void*)&hsykflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[47].sqldata = (void*)&hskflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[48].sqldata = (void*)&hhkkflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 21;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[49].sqldata = (void*)rawdata;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 13;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[50].sqldata = (void*)knskka1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 25;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[51].sqldata = (void*)knskka2;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 3;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[52].sqldata = (void*)knskka2kbn;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 4;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[53].sqldata = (void*)kkahskcd;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 25;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[54].sqldata = (void*)hjkka;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[55].sqldata = (void*)sdi;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 6;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[56].sqldata = (void*)kkacmt1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 6;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[57].sqldata = (void*)kkacmt2;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[58].sqltype = 452; sql_setdlist[58].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[58].sqldata = (void*)&kkajkcd;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[59].sqltype = 452; sql_setdlist[59].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[59].sqldata = (void*)&pncrgflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[60].sqltype = 452; sql_setdlist[60].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[60].sqldata = (void*)&knspncrgflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[61].sqltype = 452; sql_setdlist[61].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[61].sqldata = (void*)&kkaksflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[62].sqltype = 452; sql_setdlist[62].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[62].sqldata = (void*)&kkassflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[63].sqltype = 452; sql_setdlist[63].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[63].sqldata = (void*)&ijkbnm;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sqlasetdata(3,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[56];
#line 964 "KekkaIrai.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[0].sqldata = (void*)&ijkbnf;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[1].sqldata = (void*)&ijkbnn;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[2].sqldata = (void*)&tbijkbnm;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[3].sqldata = (void*)&tbijkbnf;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[4].sqldata = (void*)&tbijkbnn;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[5].sqldata = (void*)nbdolbl;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 4;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[6].sqldata = (void*)nbdoerr;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[7].sqldata = (void*)ykdolbl;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[8].sqldata = (void*)ykdoerr;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 3;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[9].sqldata = (void*)etclbl;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 4;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[10].sqldata = (void*)etcerr;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[11].sqldata = (void*)&ctrlno;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[12].sqldata = (void*)&knsseq;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[13].sqldata = (void*)&bthno;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[14].sqldata = (void*)&pltno;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[15].sqldata = (void*)&pltseq;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 9;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[16].sqldata = (void*)dtnrtts;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[17].sqldata = (void*)dtnrdh;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[18].sqldata = (void*)knskrdh;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[19].sqldata = (void*)hkkdh;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 9;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[20].sqldata = (void*)hkkkbdh;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 11;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[21].sqldata = (void*)zkhkkyymd;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 5;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[22].sqldata = (void*)zkhkkytme;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[23].sqldata = (void*)&frkkaflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[24].sqldata = (void*)&gzbsflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[25].sqldata = (void*)&hsiflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[26].sqldata = (void*)&kkaysnflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[27].sqldata = (void*)&tnyrkflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[28].sqldata = (void*)&siyflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[29].sqldata = (void*)&knsflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[30].sqldata = (void*)&renjicflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[31].sqldata = (void*)&soukn1flg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[32].sqldata = (void*)&kanrenflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[33].sqldata = (void*)&bunkkuflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[34].sqldata = (void*)&kesseiflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[35].sqldata = (void*)&rirekiflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[36].sqldata = (void*)&syougoflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[37].sqldata = (void*)&keisanflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[38].sqldata = (void*)&per100flg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[39].sqldata = (void*)&tousekflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[40].sqldata = (void*)&kisyakflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[41].sqldata = (void*)&kouseiflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[42].sqltype = 452; sql_setdlist[42].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[42].sqldata = (void*)&syoungflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[43].sqldata = (void*)&soukn2flg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[44].sqldata = (void*)&fukaptflg;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[45].sqltype = 452; sql_setdlist[45].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[45].sqldata = (void*)&yobiflg01;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[46].sqldata = (void*)&tobiflg02;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[47].sqldata = (void*)&yobiflg03;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[48].sqldata = (void*)&yobiflg04;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[49].sqltype = 452; sql_setdlist[49].sqllen = 1;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[49].sqldata = (void*)&yobiflg05;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 4;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[50].sqldata = (void*)skrycda;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 4;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[51].sqldata = (void*)skrycdb;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 4;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[52].sqldata = (void*)skrycdc;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 27;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[53].sqldata = (void*)ksndh;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 27;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[54].sqldata = (void*)trkdh;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 25;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[55].sqldata = (void*)skkka;
#line 964 "KekkaIrai.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 964 "KekkaIrai.sqc"
      sqlasetdata(3,64,56,sql_setdlist,0L,0L);
    }
#line 964 "KekkaIrai.sqc"
  sqlacall((unsigned short)25,4,0,3,0L);
#line 964 "KekkaIrai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 964 "KekkaIrai.sqc"
  sqlastop(0L);
}

#line 964 "KekkaIrai.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kekka*)ZbmlRealloc( array,
                                    sizeof( Kekka ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kekka ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KekkaIraiArray );
    }

    
/*
EXEC SQL CLOSE c3;
*/

{
#line 979 "KekkaIrai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 979 "KekkaIrai.sqc"
  sqlacall((unsigned short)20,4,0,0,0L);
#line 979 "KekkaIrai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 979 "KekkaIrai.sqc"
  sqlastop(0L);
}

#line 979 "KekkaIrai.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 987 "KekkaIrai.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKekkaUpdateCmt12()
 *    KEKKA コメントコード更新
 * ■引数
 *    [I]  Kekka* pKey       取得するレコードのキー
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 *    ADD 2006/08/03  Osada [報告済み]は対象外とする
 *    ADD 2006-09-09 コメント１，２取得カーソルループを作成し、
 *					 一旦コメントを取得。血清コメントを付けなおして
					 再び更新する
 ******************************************************************************/
long ZdbKekkaUpdateCmt12( Kekka* pKey )
{
	
    if( !ZbmlMapStructToHost( (char*)pKey, KekkaIraiArray ) )
        return HRC_INVALID_VALUE;

    /* EXEC SQL WHENEVER NOT FOUND GO TO notfound; */
    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 1012 "KekkaIrai.sqc"


    
/*
EXEC SQL DECLARE c_selCmt CURSOR FOR
    SELECT  KKACMT1,
			KKACMT2,
            KNSSU,
            KNSSUEDA
     FROM   KEKKA
     WHERE
		KNTNO     = :kntno AND
        KNSGRP    = :knsgrp AND
        KMKCD     = :kmkcd AND
        KNSKISYMD = :knskisymd AND
        SRIYMD    = :sriymd    AND
        KNSFLG    not in( 'E','M')
    	FOR READ ONLY ;
*/

#line 1027 "KekkaIrai.sqc"


    
/*
EXEC SQL OPEN c_selCmt ;
*/

{
#line 1029 "KekkaIrai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1029 "KekkaIrai.sqc"
  sqlaaloc(2,5,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 1029 "KekkaIrai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 14;
#line 1029 "KekkaIrai.sqc"
      sql_setdlist[0].sqldata = (void*)kntno;
#line 1029 "KekkaIrai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1029 "KekkaIrai.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 1029 "KekkaIrai.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 1029 "KekkaIrai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1029 "KekkaIrai.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 1029 "KekkaIrai.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 1029 "KekkaIrai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1029 "KekkaIrai.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 1029 "KekkaIrai.sqc"
      sql_setdlist[3].sqldata = (void*)knskisymd;
#line 1029 "KekkaIrai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1029 "KekkaIrai.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 1029 "KekkaIrai.sqc"
      sql_setdlist[4].sqldata = (void*)sriymd;
#line 1029 "KekkaIrai.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1029 "KekkaIrai.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 1029 "KekkaIrai.sqc"
  sqlacall((unsigned short)26,5,2,0,0L);
#line 1029 "KekkaIrai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1029 "KekkaIrai.sqc"
  sqlastop(0L);
}

#line 1029 "KekkaIrai.sqc"

    while( 1 ) {
        
/*
EXEC SQL FETCH c_selCmt INTO
                    :skkacmt1 , 
					:skkacmt2 , 
					:knssu , 
					:knssueda ;
*/

{
#line 1035 "KekkaIrai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1035 "KekkaIrai.sqc"
  sqlaaloc(3,4,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 1035 "KekkaIrai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 6;
#line 1035 "KekkaIrai.sqc"
      sql_setdlist[0].sqldata = (void*)skkacmt1;
#line 1035 "KekkaIrai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1035 "KekkaIrai.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 6;
#line 1035 "KekkaIrai.sqc"
      sql_setdlist[1].sqldata = (void*)skkacmt2;
#line 1035 "KekkaIrai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1035 "KekkaIrai.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 1035 "KekkaIrai.sqc"
      sql_setdlist[2].sqldata = (void*)&knssu;
#line 1035 "KekkaIrai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1035 "KekkaIrai.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 1035 "KekkaIrai.sqc"
      sql_setdlist[3].sqldata = (void*)&knssueda;
#line 1035 "KekkaIrai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1035 "KekkaIrai.sqc"
      sqlasetdata(3,0,4,sql_setdlist,0L,0L);
    }
#line 1035 "KekkaIrai.sqc"
  sqlacall((unsigned short)25,5,0,3,0L);
#line 1035 "KekkaIrai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1035 "KekkaIrai.sqc"
  sqlastop(0L);
}

#line 1035 "KekkaIrai.sqc"

        if ( SQLCODE == 100 ) {
            break;
        }
		if(atoi(skkacmt1) == 101 || atoi(skkacmt2) == 101){
			if(atoi(kkacmt1) == 104 || atoi(kkacmt1) == 105){	
				if(atoi(kkacmt2) == 104 || atoi(kkacmt2) == 105){	
					// セットする場所が無いため、何もしない
				}
				else{
					strcpy(kkacmt2,"0101");
				}
			}
			else{
				strcpy(kkacmt1,"0101");
			}
		}

    	
/*
EXEC SQL UPDATE KEKKA

		SET KKACMT1 = :kkacmt1,
			KKACMT2 = :kkacmt2,
			KESSEIFLG = :kesseiflg

    	WHERE
			KNTNO = :kntno AND
			KNSGRP = :knsgrp AND
			KMKCD = :kmkcd AND
			KNSKISYMD = :knskisymd AND
			SRIYMD = :sriymd	AND
			KNSSU  = :knssu AND
			KNSSUEDA = :knssueda AND
			KNSFLG not in( 'E','M');
*/

{
#line 1067 "KekkaIrai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1067 "KekkaIrai.sqc"
  sqlaaloc(2,10,9,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 6;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[0].sqldata = (void*)kkacmt1;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 6;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[1].sqldata = (void*)kkacmt2;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[2].sqldata = (void*)&kesseiflg;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 14;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[3].sqldata = (void*)kntno;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[6].sqldata = (void*)knskisymd;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[7].sqldata = (void*)sriymd;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[8].sqldata = (void*)&knssu;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[9].sqldata = (void*)&knssueda;
#line 1067 "KekkaIrai.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1067 "KekkaIrai.sqc"
      sqlasetdata(2,0,10,sql_setdlist,0L,0L);
    }
#line 1067 "KekkaIrai.sqc"
  sqlacall((unsigned short)24,6,2,0,0L);
#line 1067 "KekkaIrai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1067 "KekkaIrai.sqc"
  sqlastop(0L);
}

#line 1067 "KekkaIrai.sqc"

	}

    
/*
EXEC SQL CLOSE c_selCmt;
*/

{
#line 1070 "KekkaIrai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1070 "KekkaIrai.sqc"
  sqlacall((unsigned short)20,5,0,0,0L);
#line 1070 "KekkaIrai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1070 "KekkaIrai.sqc"
  sqlastop(0L);
}

#line 1070 "KekkaIrai.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 1075 "KekkaIrai.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 1079 "KekkaIrai.sqc"

    return sqlca.sqlcode;
}
// ADD 2006/08/14 S.Ueda 乳び・溶血チェック <<

/******************************************************************************
 * ZdbKekkaUpdateKnsFlg()
 *    KEKKA 検査フラグ更新
 * ■引数
 *    [I]  Kekka* pKey       取得するレコードのキー
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 *    ADD 2006-08-31 Nagata 新規追加
 *    ADD 2006-09-01 Nagata 新規追加 'H'→'X'にするのみ
 ******************************************************************************/
long ZdbKekkaUpdateKnsFlg( Kekka* pKey )
{
    if( !ZbmlMapStructToHost( (char*)pKey, KekkaIraiArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 1101 "KekkaIrai.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 1102 "KekkaIrai.sqc"


    
/*
EXEC SQL UPDATE KEKKA
	SET	KNSFLG = 'X'

    WHERE
		KNTNO = :kntno AND
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd	AND
		KESSEIFLG != '2' AND
		KNSFLG = 'H';
*/

{
#line 1114 "KekkaIrai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1114 "KekkaIrai.sqc"
  sqlaaloc(2,5,10,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 1114 "KekkaIrai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 14;
#line 1114 "KekkaIrai.sqc"
      sql_setdlist[0].sqldata = (void*)kntno;
#line 1114 "KekkaIrai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1114 "KekkaIrai.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 1114 "KekkaIrai.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 1114 "KekkaIrai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1114 "KekkaIrai.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 1114 "KekkaIrai.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 1114 "KekkaIrai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1114 "KekkaIrai.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 1114 "KekkaIrai.sqc"
      sql_setdlist[3].sqldata = (void*)knskisymd;
#line 1114 "KekkaIrai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1114 "KekkaIrai.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 1114 "KekkaIrai.sqc"
      sql_setdlist[4].sqldata = (void*)sriymd;
#line 1114 "KekkaIrai.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1114 "KekkaIrai.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 1114 "KekkaIrai.sqc"
  sqlacall((unsigned short)24,7,2,0,0L);
#line 1114 "KekkaIrai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1114 "KekkaIrai.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 1114 "KekkaIrai.sqc"
  sqlastop(0L);
}

#line 1114 "KekkaIrai.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 1119 "KekkaIrai.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 1123 "KekkaIrai.sqc"

    return sqlca.sqlcode;
}
// ADD E.Osada 2006-09-12
/******************************************************************************
 * updKkaYsn()
 *    KEKKA 検査フラグ更新
 * ■引数
 *    [I]  Kekka* pKey       取得するレコードのキー
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long updKkaYsn( Kekka* pKey )
{
    if( !ZbmlMapStructToHost( (char*)pKey, KekkaIraiArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 1142 "KekkaIrai.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 1143 "KekkaIrai.sqc"


    
/*
EXEC SQL UPDATE KEKKA
	SET KNSFLG = 'X'
    WHERE
		KNTNO     = :kntno      AND
		KNSGRP    = :knsgrp     AND
		KMKCD     = :kmkcd      AND
		KNSSU     = :knssu      AND
		KKAYSNFLG = '1'         AND
		KNSSUEDA  = :knssueda   AND
		KNSFLG    = 'A'         AND
		KANRENFLG = '2'			AND
		RENJICFLG != '2'		AND
		SOUKN1FLG != '2'		AND
		KISYAKFLG != '2'		AND
		BUNKKUFLG != '2'		AND
		PER100FLG != '2'		AND
		YOBIFLG01 != '2'		AND
		NBKMKCD   = '       '   AND
		KNSKISYMD = :knskisymd  AND
		SRIYMD    = :sriymd;
*/

{
#line 1164 "KekkaIrai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1164 "KekkaIrai.sqc"
  sqlaaloc(2,7,11,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 1164 "KekkaIrai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 14;
#line 1164 "KekkaIrai.sqc"
      sql_setdlist[0].sqldata = (void*)kntno;
#line 1164 "KekkaIrai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1164 "KekkaIrai.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 1164 "KekkaIrai.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 1164 "KekkaIrai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1164 "KekkaIrai.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 1164 "KekkaIrai.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 1164 "KekkaIrai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1164 "KekkaIrai.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 1164 "KekkaIrai.sqc"
      sql_setdlist[3].sqldata = (void*)&knssu;
#line 1164 "KekkaIrai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1164 "KekkaIrai.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 1164 "KekkaIrai.sqc"
      sql_setdlist[4].sqldata = (void*)&knssueda;
#line 1164 "KekkaIrai.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1164 "KekkaIrai.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 1164 "KekkaIrai.sqc"
      sql_setdlist[5].sqldata = (void*)knskisymd;
#line 1164 "KekkaIrai.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1164 "KekkaIrai.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 1164 "KekkaIrai.sqc"
      sql_setdlist[6].sqldata = (void*)sriymd;
#line 1164 "KekkaIrai.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1164 "KekkaIrai.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 1164 "KekkaIrai.sqc"
  sqlacall((unsigned short)24,8,2,0,0L);
#line 1164 "KekkaIrai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1164 "KekkaIrai.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 1164 "KekkaIrai.sqc"
  sqlastop(0L);
}

#line 1164 "KekkaIrai.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 1169 "KekkaIrai.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 1173 "KekkaIrai.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
