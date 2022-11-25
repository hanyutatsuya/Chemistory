static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,51,65,75,106,84,81,70,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,50,90,84,85,78,69,50,32,0,0,0,0,0,0,0,0,
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


#line 1 "KekkaCount.sqc"
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


#line 24 "KekkaCount.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "KekkaCount.sqc"

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
	sqlint32	cnt;

/*
EXEC SQL END DECLARE SECTION;
*/

#line 151 "KekkaCount.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Kekka

BmlDMMInfo	KekkaArrayCount[] = {
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
	DMM_STIMESTAMP( skkka ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKekkaSelectKeyCount()
 *    KEKKA レコードKey条件取得
 * ■引数
 *    [I]  Kekka* pKey       取得するレコードのキー
 * ■戻り値
 *    (long) レコード数
 ******************************************************************************/
long ZdbKekkaSelectKeyCount( Kekka* pKey )
{
    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KekkaArrayCount ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 299 "KekkaCount.sqc"


    
/*
EXEC SQL DECLARE cc2 CURSOR FOR
    SELECT
		Count(*)
    FROM
        KEKKA
    WHERE
		KNTNO = :kntno AND
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KNSSU = :knssu AND
		KNSSUEDA = :knssueda AND
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd FOR READ ONLY;
*/

#line 313 "KekkaCount.sqc"


    
/*
EXEC SQL OPEN cc2;
*/

{
#line 315 "KekkaCount.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 315 "KekkaCount.sqc"
  sqlaaloc(2,7,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 315 "KekkaCount.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 14;
#line 315 "KekkaCount.sqc"
      sql_setdlist[0].sqldata = (void*)kntno;
#line 315 "KekkaCount.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 315 "KekkaCount.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 315 "KekkaCount.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 315 "KekkaCount.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 315 "KekkaCount.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 315 "KekkaCount.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 315 "KekkaCount.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 315 "KekkaCount.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 315 "KekkaCount.sqc"
      sql_setdlist[3].sqldata = (void*)&knssu;
#line 315 "KekkaCount.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 315 "KekkaCount.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 315 "KekkaCount.sqc"
      sql_setdlist[4].sqldata = (void*)&knssueda;
#line 315 "KekkaCount.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 315 "KekkaCount.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 315 "KekkaCount.sqc"
      sql_setdlist[5].sqldata = (void*)knskisymd;
#line 315 "KekkaCount.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 315 "KekkaCount.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 315 "KekkaCount.sqc"
      sql_setdlist[6].sqldata = (void*)sriymd;
#line 315 "KekkaCount.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 315 "KekkaCount.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 315 "KekkaCount.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 315 "KekkaCount.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 315 "KekkaCount.sqc"
  sqlastop(0L);
}

#line 315 "KekkaCount.sqc"


    
/*
EXEC SQL FETCH cc2 INTO :cnt;
*/

{
#line 317 "KekkaCount.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 317 "KekkaCount.sqc"
  sqlaaloc(3,1,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 317 "KekkaCount.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 317 "KekkaCount.sqc"
      sql_setdlist[0].sqldata = (void*)&cnt;
#line 317 "KekkaCount.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 317 "KekkaCount.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 317 "KekkaCount.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 317 "KekkaCount.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 317 "KekkaCount.sqc"
  sqlastop(0L);
}

#line 317 "KekkaCount.sqc"


    
/*
EXEC SQL CLOSE cc2;
*/

{
#line 319 "KekkaCount.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 319 "KekkaCount.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 319 "KekkaCount.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 319 "KekkaCount.sqc"
  sqlastop(0L);
}

#line 319 "KekkaCount.sqc"


    return cnt;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 324 "KekkaCount.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
