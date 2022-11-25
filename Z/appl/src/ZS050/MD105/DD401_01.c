static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,115,65,75,106,84,81,70,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,49,90,84,85,78,69,50,32,0,0,0,0,0,0,0,0,
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


#line 1 "DD401_01.sqc"
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


#line 24 "DD401_01.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "DD401_01.sqc"

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
	sqlint32        cnt;

/*
EXEC SQL END DECLARE SECTION;
*/

#line 151 "DD401_01.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Kekka

BmlDMMInfo	KekkaArrayDD401_10[] = {
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
 * ZdbKekkaSelectTnyrkCount()
 *    手入力結果データ件数検索
 * ■引数
 *    [I]  Kekka* pKey       取得するレコードのキー
 * ■戻り値
 *    (long) レコード数
 * ■備考
 *    ADD 2006/07/29  Haga  insertDBで使用する
 ******************************************************************************/
long ZdbKekkaSelectTnyrkCount( Kekka* pKey )
{
    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KekkaArrayDD401_10) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 301 "DD401_01.sqc"


    
/*
EXEC SQL DECLARE C1 CURSOR FOR
    SELECT
		Count(*)
    FROM
        KEKKA
    WHERE
		KNTNO     = :kntno     AND
		KNSGRP    = :knsgrp    AND
		KMKCD     = :kmkcd	   AND
		KNSSU     = :knssu	   AND
		KNSSUEDA  = :knssueda  AND
		KNSKISYMD = :knskisymd AND
		TNYRKFLG  = '1'		   AND
		KKAYSNFLG = '1'		   AND
		SRIYMD    = :sriymd FOR READ ONLY;
*/

#line 317 "DD401_01.sqc"


    
/*
EXEC SQL OPEN C1;
*/

{
#line 319 "DD401_01.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 319 "DD401_01.sqc"
  sqlaaloc(2,7,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 319 "DD401_01.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 14;
#line 319 "DD401_01.sqc"
      sql_setdlist[0].sqldata = (void*)kntno;
#line 319 "DD401_01.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 319 "DD401_01.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 319 "DD401_01.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 319 "DD401_01.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 319 "DD401_01.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 319 "DD401_01.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 319 "DD401_01.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 319 "DD401_01.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 319 "DD401_01.sqc"
      sql_setdlist[3].sqldata = (void*)&knssu;
#line 319 "DD401_01.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 319 "DD401_01.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 319 "DD401_01.sqc"
      sql_setdlist[4].sqldata = (void*)&knssueda;
#line 319 "DD401_01.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 319 "DD401_01.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 319 "DD401_01.sqc"
      sql_setdlist[5].sqldata = (void*)knskisymd;
#line 319 "DD401_01.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 319 "DD401_01.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 319 "DD401_01.sqc"
      sql_setdlist[6].sqldata = (void*)sriymd;
#line 319 "DD401_01.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 319 "DD401_01.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 319 "DD401_01.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 319 "DD401_01.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 319 "DD401_01.sqc"
  sqlastop(0L);
}

#line 319 "DD401_01.sqc"


    
/*
EXEC SQL FETCH C1 INTO :cnt;
*/

{
#line 321 "DD401_01.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 321 "DD401_01.sqc"
  sqlaaloc(3,1,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 321 "DD401_01.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 321 "DD401_01.sqc"
      sql_setdlist[0].sqldata = (void*)&cnt;
#line 321 "DD401_01.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 321 "DD401_01.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 321 "DD401_01.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 321 "DD401_01.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 321 "DD401_01.sqc"
  sqlastop(0L);
}

#line 321 "DD401_01.sqc"


    
/*
EXEC SQL CLOSE C1;
*/

{
#line 323 "DD401_01.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 323 "DD401_01.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 323 "DD401_01.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 323 "DD401_01.sqc"
  sqlastop(0L);
}

#line 323 "DD401_01.sqc"


    return cnt;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 328 "DD401_01.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKekkaSelectNyubiCount()
 *    乳び結果データ件数検索
 * ■引数
 *    [I]  Kekka* pKey       取得するレコードのキー
 * ■戻り値
 *    (long) レコード数
 * ■備考
 *    ADD 2006/07/29  Haga  insertDBで使用する
 ******************************************************************************/
long ZdbKekkaSelectNyubiCount( Kekka* pKey )
{
    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KekkaArrayDD401_10) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 350 "DD401_01.sqc"


    
/*
EXEC SQL DECLARE C2 CURSOR FOR
    SELECT
		Count(*)
    FROM
        KEKKA
    WHERE
		KNTNO     =  :kntno     AND
		KNSGRP    =  :knsgrp    AND
		KMKCD     =  :kmkcd	    AND
		KNSSU     =  :knssu	    AND
		KNSSUEDA  =  :knssueda  AND
		KNSKISYMD =  :knskisymd AND
		NBDOLBL   != '  '       AND
		SRIYMD    =  :sriymd FOR READ ONLY;
*/

#line 365 "DD401_01.sqc"


    
/*
EXEC SQL OPEN C2;
*/

{
#line 367 "DD401_01.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 367 "DD401_01.sqc"
  sqlaaloc(2,7,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 367 "DD401_01.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 14;
#line 367 "DD401_01.sqc"
      sql_setdlist[0].sqldata = (void*)kntno;
#line 367 "DD401_01.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 367 "DD401_01.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 367 "DD401_01.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 367 "DD401_01.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 367 "DD401_01.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 367 "DD401_01.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 367 "DD401_01.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 367 "DD401_01.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 367 "DD401_01.sqc"
      sql_setdlist[3].sqldata = (void*)&knssu;
#line 367 "DD401_01.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 367 "DD401_01.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 367 "DD401_01.sqc"
      sql_setdlist[4].sqldata = (void*)&knssueda;
#line 367 "DD401_01.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 367 "DD401_01.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 367 "DD401_01.sqc"
      sql_setdlist[5].sqldata = (void*)knskisymd;
#line 367 "DD401_01.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 367 "DD401_01.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 367 "DD401_01.sqc"
      sql_setdlist[6].sqldata = (void*)sriymd;
#line 367 "DD401_01.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 367 "DD401_01.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 367 "DD401_01.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 367 "DD401_01.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 367 "DD401_01.sqc"
  sqlastop(0L);
}

#line 367 "DD401_01.sqc"


    
/*
EXEC SQL FETCH C2 INTO :cnt;
*/

{
#line 369 "DD401_01.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 369 "DD401_01.sqc"
  sqlaaloc(3,1,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 369 "DD401_01.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 369 "DD401_01.sqc"
      sql_setdlist[0].sqldata = (void*)&cnt;
#line 369 "DD401_01.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 369 "DD401_01.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 369 "DD401_01.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 369 "DD401_01.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 369 "DD401_01.sqc"
  sqlastop(0L);
}

#line 369 "DD401_01.sqc"


    
/*
EXEC SQL CLOSE C2;
*/

{
#line 371 "DD401_01.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 371 "DD401_01.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 371 "DD401_01.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 371 "DD401_01.sqc"
  sqlastop(0L);
}

#line 371 "DD401_01.sqc"


    return cnt;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 376 "DD401_01.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKekkaUpdateRep()
 *    結果データを無効にする
 *		結果状況コード＝１（中間）
 *		結果優先フラグ＝ブランク
 *		検査フラグ＝Ｍ（未報告完了）
 * ■引数
 *    [I]  Kekka* pKey       取得するレコードのキー
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 * ■備考
 *    ADD 2006/07/29  Haga  insertDBで使用する
 *    ADD 2006/08/03  Osada [報告済み]は対象外とする
 *    MOD 2006/08/10  Hiwa  前回のみ無効にする
 ******************************************************************************/
long ZdbKekkaUpdateRep( Kekka* pKey )
{
    if( !ZbmlMapStructToHost( (char*)pKey, KekkaArrayDD401_10 ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 402 "DD401_01.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 403 "DD401_01.sqc"

    
/*
EXEC SQL UPDATE KEKKA
	SET KKAJKCD   = '1',
		KKAYSNFLG = ' ',
		KNSFLG    = 'M'
    WHERE
		KNSKISYMD =  :knskisymd	AND
		SRIYMD    =  :sriymd	AND
		KNTNO     =  :kntno		AND
		KNSGRP    =  :knsgrp	AND
		KMKCD     =  :kmkcd		AND
		KNSSU     =  :knssu		AND
		KNSSUEDA  =  :knssueda  AND
		KNSFLG	 !=	 'E';
*/

{
#line 416 "DD401_01.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 416 "DD401_01.sqc"
  sqlaaloc(2,7,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 416 "DD401_01.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 416 "DD401_01.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 416 "DD401_01.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 416 "DD401_01.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 416 "DD401_01.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 416 "DD401_01.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 416 "DD401_01.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 416 "DD401_01.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 416 "DD401_01.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 416 "DD401_01.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 416 "DD401_01.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 416 "DD401_01.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 416 "DD401_01.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 416 "DD401_01.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 416 "DD401_01.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 416 "DD401_01.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 416 "DD401_01.sqc"
      sql_setdlist[5].sqldata = (void*)&knssu;
#line 416 "DD401_01.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 416 "DD401_01.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 416 "DD401_01.sqc"
      sql_setdlist[6].sqldata = (void*)&knssueda;
#line 416 "DD401_01.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 416 "DD401_01.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 416 "DD401_01.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 416 "DD401_01.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 416 "DD401_01.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 416 "DD401_01.sqc"
  sqlastop(0L);
}

#line 416 "DD401_01.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 421 "DD401_01.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 425 "DD401_01.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKekkaSelectKKAYSN()
 *    結果優先フラグが1:優先結果のデータを取得する 
 * ■引数
 *    [I]  Kekka* pKey       	取得するレコードのキー
 *    [O]  Kekka** arrayOut     取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 * ■備考
 *    ADD 2006/07/29  Haga  shougoChkで使用する
 ******************************************************************************/
long ZdbKekkaSelectKKAYSN ( Kekka* pKey, Kekka** arrayOut, int* numOut )
{
    Kekka*      array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KekkaArrayDD401_10 ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 454 "DD401_01.sqc"


    
/*
EXEC SQL DECLARE C3 CURSOR FOR
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
		KNSKISYMD = :knskisymd	AND
		SRIYMD    = :sriymd		AND
		KNTNO     = :kntno		AND
		KNSGRP    = :knsgrp		AND
		KMKCD     = :kmkcd		AND
		KNSSU     = :knssu		AND
		KKAYSNFLG = '1'			AND
		KNSSUEDA  = :knssueda 
    FOR READ ONLY;
*/

#line 589 "DD401_01.sqc"


    
/*
EXEC SQL OPEN C3;
*/

{
#line 591 "DD401_01.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 591 "DD401_01.sqc"
  sqlaaloc(2,7,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 591 "DD401_01.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 591 "DD401_01.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 591 "DD401_01.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 591 "DD401_01.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 591 "DD401_01.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 591 "DD401_01.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 591 "DD401_01.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 591 "DD401_01.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 591 "DD401_01.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 591 "DD401_01.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 591 "DD401_01.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 591 "DD401_01.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 591 "DD401_01.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 591 "DD401_01.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 591 "DD401_01.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 591 "DD401_01.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 591 "DD401_01.sqc"
      sql_setdlist[5].sqldata = (void*)&knssu;
#line 591 "DD401_01.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 591 "DD401_01.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 591 "DD401_01.sqc"
      sql_setdlist[6].sqldata = (void*)&knssueda;
#line 591 "DD401_01.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 591 "DD401_01.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 591 "DD401_01.sqc"
  sqlacall((unsigned short)26,4,2,0,0L);
#line 591 "DD401_01.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 591 "DD401_01.sqc"
  sqlastop(0L);
}

#line 591 "DD401_01.sqc"


    while( 1 ) {
        Kekka* rec;

        
/*
EXEC SQL FETCH C3 INTO
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
#line 716 "DD401_01.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 716 "DD401_01.sqc"
  sqlaaloc(3,120,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 716 "DD401_01.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 716 "DD401_01.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 716 "DD401_01.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 716 "DD401_01.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 716 "DD401_01.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 716 "DD401_01.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 716 "DD401_01.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 716 "DD401_01.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 716 "DD401_01.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 716 "DD401_01.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 716 "DD401_01.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 716 "DD401_01.sqc"
      sql_setdlist[6].sqldata = (void*)&knssu;
#line 716 "DD401_01.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 716 "DD401_01.sqc"
      sql_setdlist[7].sqldata = (void*)&knssueda;
#line 716 "DD401_01.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[8].sqldata = (void*)&irihsmkbn;
#line 716 "DD401_01.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[9].sqldata = (void*)&irikbn;
#line 716 "DD401_01.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[10].sqldata = (void*)&ksktkbn;
#line 716 "DD401_01.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 716 "DD401_01.sqc"
      sql_setdlist[11].sqldata = (void*)utkymd;
#line 716 "DD401_01.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 12;
#line 716 "DD401_01.sqc"
      sql_setdlist[12].sqldata = (void*)irino;
#line 716 "DD401_01.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[13].sqldata = (void*)&iriketflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 716 "DD401_01.sqc"
      sql_setdlist[14].sqldata = (void*)&zssdino;
#line 716 "DD401_01.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 716 "DD401_01.sqc"
      sql_setdlist[15].sqldata = (void*)sstcd;
#line 716 "DD401_01.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 11;
#line 716 "DD401_01.sqc"
      sql_setdlist[16].sqldata = (void*)trid;
#line 716 "DD401_01.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[17].sqltype = 500; sql_setdlist[17].sqllen = 2;
#line 716 "DD401_01.sqc"
      sql_setdlist[17].sqldata = (void*)&trpos;
#line 716 "DD401_01.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 11;
#line 716 "DD401_01.sqc"
      sql_setdlist[18].sqldata = (void*)asyrckid;
#line 716 "DD401_01.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 716 "DD401_01.sqc"
      sql_setdlist[19].sqldata = (void*)&asyrckpos;
#line 716 "DD401_01.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 8;
#line 716 "DD401_01.sqc"
      sql_setdlist[20].sqldata = (void*)oyakmkcd;
#line 716 "DD401_01.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 3;
#line 716 "DD401_01.sqc"
      sql_setdlist[21].sqldata = (void*)seccd;
#line 716 "DD401_01.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[22].sqldata = (void*)&bkfkkbn;
#line 716 "DD401_01.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 716 "DD401_01.sqc"
      sql_setdlist[23].sqldata = (void*)smpcd;
#line 716 "DD401_01.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 5;
#line 716 "DD401_01.sqc"
      sql_setdlist[24].sqldata = (void*)bskkbn;
#line 716 "DD401_01.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 5;
#line 716 "DD401_01.sqc"
      sql_setdlist[25].sqldata = (void*)bsklne;
#line 716 "DD401_01.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 7;
#line 716 "DD401_01.sqc"
      sql_setdlist[26].sqldata = (void*)bskgok;
#line 716 "DD401_01.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[27].sqltype = 496; sql_setdlist[27].sqllen = 4;
#line 716 "DD401_01.sqc"
      sql_setdlist[27].sqldata = (void*)&bskseq;
#line 716 "DD401_01.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 3;
#line 716 "DD401_01.sqc"
      sql_setdlist[28].sqldata = (void*)bskerrsts;
#line 716 "DD401_01.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 716 "DD401_01.sqc"
      sql_setdlist[29].sqldata = (void*)sktdh;
#line 716 "DD401_01.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 8;
#line 716 "DD401_01.sqc"
      sql_setdlist[30].sqldata = (void*)nbkmkcd;
#line 716 "DD401_01.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[31].sqldata = (void*)&tstrflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 5;
#line 716 "DD401_01.sqc"
      sql_setdlist[32].sqldata = (void*)zrcd;
#line 716 "DD401_01.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 716 "DD401_01.sqc"
      sql_setdlist[33].sqldata = (void*)ysnlbl;
#line 716 "DD401_01.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 4;
#line 716 "DD401_01.sqc"
      sql_setdlist[34].sqldata = (void*)kjno;
#line 716 "DD401_01.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[35].sqldata = (void*)&fkhkknohjkbn;
#line 716 "DD401_01.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 4;
#line 716 "DD401_01.sqc"
      sql_setdlist[36].sqldata = (void*)tbkjno;
#line 716 "DD401_01.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[37].sqldata = (void*)&tbkjflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 25;
#line 716 "DD401_01.sqc"
      sql_setdlist[38].sqldata = (void*)htkfkhms;
#line 716 "DD401_01.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[39].sqldata = (void*)&skflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 3;
#line 716 "DD401_01.sqc"
      sql_setdlist[40].sqldata = (void*)tskflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 716 "DD401_01.sqc"
      sql_setdlist[41].sqldata = (void*)tktflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 16;
#line 716 "DD401_01.sqc"
      sql_setdlist[42].sqldata = (void*)jisksbr;
#line 716 "DD401_01.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[43].sqldata = (void*)&kkflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[44].sqldata = (void*)&kkiriflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[45].sqltype = 500; sql_setdlist[45].sqllen = 2;
#line 716 "DD401_01.sqc"
      sql_setdlist[45].sqldata = (void*)&kkirilotno;
#line 716 "DD401_01.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[46].sqldata = (void*)&hsykflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[47].sqldata = (void*)&hskflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[48].sqldata = (void*)&hhkkflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 21;
#line 716 "DD401_01.sqc"
      sql_setdlist[49].sqldata = (void*)rawdata;
#line 716 "DD401_01.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 13;
#line 716 "DD401_01.sqc"
      sql_setdlist[50].sqldata = (void*)knskka1;
#line 716 "DD401_01.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 25;
#line 716 "DD401_01.sqc"
      sql_setdlist[51].sqldata = (void*)knskka2;
#line 716 "DD401_01.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 3;
#line 716 "DD401_01.sqc"
      sql_setdlist[52].sqldata = (void*)knskka2kbn;
#line 716 "DD401_01.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 4;
#line 716 "DD401_01.sqc"
      sql_setdlist[53].sqldata = (void*)kkahskcd;
#line 716 "DD401_01.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 25;
#line 716 "DD401_01.sqc"
      sql_setdlist[54].sqldata = (void*)hjkka;
#line 716 "DD401_01.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 716 "DD401_01.sqc"
      sql_setdlist[55].sqldata = (void*)sdi;
#line 716 "DD401_01.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 6;
#line 716 "DD401_01.sqc"
      sql_setdlist[56].sqldata = (void*)kkacmt1;
#line 716 "DD401_01.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 6;
#line 716 "DD401_01.sqc"
      sql_setdlist[57].sqldata = (void*)kkacmt2;
#line 716 "DD401_01.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[58].sqltype = 452; sql_setdlist[58].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[58].sqldata = (void*)&kkajkcd;
#line 716 "DD401_01.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[59].sqltype = 452; sql_setdlist[59].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[59].sqldata = (void*)&pncrgflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[60].sqltype = 452; sql_setdlist[60].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[60].sqldata = (void*)&knspncrgflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[61].sqltype = 452; sql_setdlist[61].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[61].sqldata = (void*)&kkaksflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[62].sqltype = 452; sql_setdlist[62].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[62].sqldata = (void*)&kkassflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[63].sqltype = 452; sql_setdlist[63].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[63].sqldata = (void*)&ijkbnm;
#line 716 "DD401_01.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sqlasetdata(3,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[56];
#line 716 "DD401_01.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[0].sqldata = (void*)&ijkbnf;
#line 716 "DD401_01.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[1].sqldata = (void*)&ijkbnn;
#line 716 "DD401_01.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[2].sqldata = (void*)&tbijkbnm;
#line 716 "DD401_01.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[3].sqldata = (void*)&tbijkbnf;
#line 716 "DD401_01.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[4].sqldata = (void*)&tbijkbnn;
#line 716 "DD401_01.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 716 "DD401_01.sqc"
      sql_setdlist[5].sqldata = (void*)nbdolbl;
#line 716 "DD401_01.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 4;
#line 716 "DD401_01.sqc"
      sql_setdlist[6].sqldata = (void*)nbdoerr;
#line 716 "DD401_01.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 716 "DD401_01.sqc"
      sql_setdlist[7].sqldata = (void*)ykdolbl;
#line 716 "DD401_01.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 716 "DD401_01.sqc"
      sql_setdlist[8].sqldata = (void*)ykdoerr;
#line 716 "DD401_01.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 3;
#line 716 "DD401_01.sqc"
      sql_setdlist[9].sqldata = (void*)etclbl;
#line 716 "DD401_01.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 4;
#line 716 "DD401_01.sqc"
      sql_setdlist[10].sqldata = (void*)etcerr;
#line 716 "DD401_01.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 716 "DD401_01.sqc"
      sql_setdlist[11].sqldata = (void*)&ctrlno;
#line 716 "DD401_01.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 716 "DD401_01.sqc"
      sql_setdlist[12].sqldata = (void*)&knsseq;
#line 716 "DD401_01.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 716 "DD401_01.sqc"
      sql_setdlist[13].sqldata = (void*)&bthno;
#line 716 "DD401_01.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 716 "DD401_01.sqc"
      sql_setdlist[14].sqldata = (void*)&pltno;
#line 716 "DD401_01.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 716 "DD401_01.sqc"
      sql_setdlist[15].sqldata = (void*)&pltseq;
#line 716 "DD401_01.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 9;
#line 716 "DD401_01.sqc"
      sql_setdlist[16].sqldata = (void*)dtnrtts;
#line 716 "DD401_01.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 716 "DD401_01.sqc"
      sql_setdlist[17].sqldata = (void*)dtnrdh;
#line 716 "DD401_01.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 716 "DD401_01.sqc"
      sql_setdlist[18].sqldata = (void*)knskrdh;
#line 716 "DD401_01.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 716 "DD401_01.sqc"
      sql_setdlist[19].sqldata = (void*)hkkdh;
#line 716 "DD401_01.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 9;
#line 716 "DD401_01.sqc"
      sql_setdlist[20].sqldata = (void*)hkkkbdh;
#line 716 "DD401_01.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 11;
#line 716 "DD401_01.sqc"
      sql_setdlist[21].sqldata = (void*)zkhkkyymd;
#line 716 "DD401_01.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 5;
#line 716 "DD401_01.sqc"
      sql_setdlist[22].sqldata = (void*)zkhkkytme;
#line 716 "DD401_01.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[23].sqldata = (void*)&frkkaflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[24].sqldata = (void*)&gzbsflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[25].sqldata = (void*)&hsiflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[26].sqldata = (void*)&kkaysnflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[27].sqldata = (void*)&tnyrkflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[28].sqldata = (void*)&siyflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[29].sqldata = (void*)&knsflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[30].sqldata = (void*)&renjicflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[31].sqldata = (void*)&soukn1flg;
#line 716 "DD401_01.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[32].sqldata = (void*)&kanrenflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[33].sqldata = (void*)&bunkkuflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[34].sqldata = (void*)&kesseiflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[35].sqldata = (void*)&rirekiflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[36].sqldata = (void*)&syougoflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[37].sqldata = (void*)&keisanflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[38].sqldata = (void*)&per100flg;
#line 716 "DD401_01.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[39].sqldata = (void*)&tousekflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[40].sqldata = (void*)&kisyakflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[41].sqldata = (void*)&kouseiflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[42].sqltype = 452; sql_setdlist[42].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[42].sqldata = (void*)&syoungflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[43].sqldata = (void*)&soukn2flg;
#line 716 "DD401_01.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[44].sqldata = (void*)&fukaptflg;
#line 716 "DD401_01.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[45].sqltype = 452; sql_setdlist[45].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[45].sqldata = (void*)&yobiflg01;
#line 716 "DD401_01.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[46].sqldata = (void*)&tobiflg02;
#line 716 "DD401_01.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[47].sqldata = (void*)&yobiflg03;
#line 716 "DD401_01.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[48].sqldata = (void*)&yobiflg04;
#line 716 "DD401_01.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[49].sqltype = 452; sql_setdlist[49].sqllen = 1;
#line 716 "DD401_01.sqc"
      sql_setdlist[49].sqldata = (void*)&yobiflg05;
#line 716 "DD401_01.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 4;
#line 716 "DD401_01.sqc"
      sql_setdlist[50].sqldata = (void*)skrycda;
#line 716 "DD401_01.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 4;
#line 716 "DD401_01.sqc"
      sql_setdlist[51].sqldata = (void*)skrycdb;
#line 716 "DD401_01.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 4;
#line 716 "DD401_01.sqc"
      sql_setdlist[52].sqldata = (void*)skrycdc;
#line 716 "DD401_01.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 27;
#line 716 "DD401_01.sqc"
      sql_setdlist[53].sqldata = (void*)ksndh;
#line 716 "DD401_01.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 27;
#line 716 "DD401_01.sqc"
      sql_setdlist[54].sqldata = (void*)trkdh;
#line 716 "DD401_01.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 25;
#line 716 "DD401_01.sqc"
      sql_setdlist[55].sqldata = (void*)skkka;
#line 716 "DD401_01.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 716 "DD401_01.sqc"
      sqlasetdata(3,64,56,sql_setdlist,0L,0L);
    }
#line 716 "DD401_01.sqc"
  sqlacall((unsigned short)25,4,0,3,0L);
#line 716 "DD401_01.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 716 "DD401_01.sqc"
  sqlastop(0L);
}

#line 716 "DD401_01.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kekka*)ZbmlRealloc( array,
                                    sizeof( Kekka ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kekka ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KekkaArrayDD401_10 );
    }

    
/*
EXEC SQL CLOSE C3;
*/

{
#line 731 "DD401_01.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 731 "DD401_01.sqc"
  sqlacall((unsigned short)20,4,0,0,0L);
#line 731 "DD401_01.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 731 "DD401_01.sqc"
  sqlastop(0L);
}

#line 731 "DD401_01.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 739 "DD401_01.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKekkaSelectFukusuCount()
 *    複数本分の測定結果データ検索
 * ■引数
 *    [I]  Kekka* pKey       取得するレコードのキー
 * ■戻り値
 *    (long) レコード数
 * ■備考
 ******************************************************************************/
long ZdbKekkaSelectFukusuCount( Kekka* pKey )
{
	if( !pKey )
		return HRC_NULL_POINTER;

	if( !ZbmlMapStructToHost( (char*)pKey, KekkaArrayDD401_10) )
		return HRC_INVALID_VALUE;

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 759 "DD401_01.sqc"


	
/*
EXEC SQL DECLARE C4 CURSOR FOR
	SELECT
		Count(*)
	FROM
		KEKKA
	WHERE
		UTKYMD    = :utkymd    AND
		IRINO     = :irino     AND
        KNTNO    != :kntno     AND
		KNSGRP    = :knsgrp    AND
		KMKCD     = :kmkcd     AND
		SRIYMD    = :sriymd    AND
		KNSFLG   != 'M'        AND
		KKAJKCD   = '3' FOR READ ONLY;
*/

#line 774 "DD401_01.sqc"


    
/*
EXEC SQL OPEN C4;
*/

{
#line 776 "DD401_01.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 776 "DD401_01.sqc"
  sqlaaloc(2,6,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 776 "DD401_01.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 776 "DD401_01.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 776 "DD401_01.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 776 "DD401_01.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 776 "DD401_01.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 776 "DD401_01.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 776 "DD401_01.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 776 "DD401_01.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 776 "DD401_01.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 776 "DD401_01.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 776 "DD401_01.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 776 "DD401_01.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 776 "DD401_01.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 776 "DD401_01.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 776 "DD401_01.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 776 "DD401_01.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 776 "DD401_01.sqc"
      sql_setdlist[5].sqldata = (void*)sriymd;
#line 776 "DD401_01.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 776 "DD401_01.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 776 "DD401_01.sqc"
  sqlacall((unsigned short)26,5,2,0,0L);
#line 776 "DD401_01.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 776 "DD401_01.sqc"
  sqlastop(0L);
}

#line 776 "DD401_01.sqc"


	
/*
EXEC SQL FETCH C4 INTO :cnt;
*/

{
#line 778 "DD401_01.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 778 "DD401_01.sqc"
  sqlaaloc(3,1,9,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 778 "DD401_01.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 778 "DD401_01.sqc"
      sql_setdlist[0].sqldata = (void*)&cnt;
#line 778 "DD401_01.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 778 "DD401_01.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 778 "DD401_01.sqc"
  sqlacall((unsigned short)25,5,0,3,0L);
#line 778 "DD401_01.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 778 "DD401_01.sqc"
  sqlastop(0L);
}

#line 778 "DD401_01.sqc"


	
/*
EXEC SQL CLOSE C4;
*/

{
#line 780 "DD401_01.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 780 "DD401_01.sqc"
  sqlacall((unsigned short)20,5,0,0,0L);
#line 780 "DD401_01.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 780 "DD401_01.sqc"
  sqlastop(0L);
}

#line 780 "DD401_01.sqc"


	return cnt;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 785 "DD401_01.sqc"

	return sqlca.sqlcode;
}
/** End of File *********************************************************/
