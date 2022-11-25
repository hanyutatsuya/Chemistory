static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,82,66,75,106,84,81,70,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,52,90,84,85,78,69,50,32,0,0,0,0,0,0,0,0,
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


#line 1 "KenorderCount.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Kenorder.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Kenorder.h"
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


#line 24 "KenorderCount.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "KenorderCount.sqc"

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
	char    nbkmkcd[8];
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
	char    ytiksbr[16];
	char    kkflg;
	char    kkiriflg;
	short   kkirilotno;
	char    sc[6];
	char    tj[6];
	char    tjtni;
	char    sbtkbn;
	char    birthday[9];
	char    birthdaykbn;
	char    age[4];
	char    agekbn;
	char    sstme[9];
	char    ssymd[11];
	char    tntme[5];
	char    tntni;
	char    tnryo[6];
	char    tnryotni;
	sqlint32  knsseq;
	short   bthno;
	char    knsjkflg;
	char    ksndh[27];
	sqlint32 Cnt;

/*
EXEC SQL END DECLARE SECTION;
*/

#line 89 "KenorderCount.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Kenorder

BmlDMMInfo	KenorderArrayCount[] = {
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
	DMM_SSTRING( nbkmkcd ),
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
	DMM_SSTRING( ytiksbr ),
	DMM_SCHAR( kkflg ),
	DMM_SCHAR( kkiriflg ),
	DMM_SSHORT( kkirilotno ),
	DMM_SSTRING( sc ),
	DMM_SSTRING( tj ),
	DMM_SCHAR( tjtni ),
	DMM_SCHAR( sbtkbn ),
	DMM_SSTRING( birthday ),
	DMM_SCHAR( birthdaykbn ),
	DMM_SSTRING( age ),
	DMM_SCHAR( agekbn ),
	DMM_STIME( sstme ),
	DMM_SDATE( ssymd ),
	DMM_SSTRING( tntme ),
	DMM_SCHAR( tntni ),
	DMM_SSTRING( tnryo ),
	DMM_SCHAR( tnryotni ),
	DMM_SLONG( knsseq ),
	DMM_SSHORT( bthno ),
	DMM_SCHAR( knsjkflg ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKenorderSelectKeyCount()
 *    KENORDER レコードKey条件取得
 * ■引数
 *    [I]  Kenorder* pKey       取得するレコードのキー
 * ■戻り値
 *    (long)   レコード数
 ******************************************************************************/
long ZdbKenorderSelectKeyCount( Kenorder* pKey )
{
    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KenorderArrayCount ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 175 "KenorderCount.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		Count(*)
    FROM
        KENORDER
    WHERE
		KNTNO = :kntno AND
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KNSSU = :knssu AND
		KNSSUEDA = :knssueda AND
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd FOR READ ONLY;
*/

#line 189 "KenorderCount.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 191 "KenorderCount.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 191 "KenorderCount.sqc"
  sqlaaloc(2,7,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 191 "KenorderCount.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 14;
#line 191 "KenorderCount.sqc"
      sql_setdlist[0].sqldata = (void*)kntno;
#line 191 "KenorderCount.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 191 "KenorderCount.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 191 "KenorderCount.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 191 "KenorderCount.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 191 "KenorderCount.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 191 "KenorderCount.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 191 "KenorderCount.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 191 "KenorderCount.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 191 "KenorderCount.sqc"
      sql_setdlist[3].sqldata = (void*)&knssu;
#line 191 "KenorderCount.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 191 "KenorderCount.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 191 "KenorderCount.sqc"
      sql_setdlist[4].sqldata = (void*)&knssueda;
#line 191 "KenorderCount.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 191 "KenorderCount.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 191 "KenorderCount.sqc"
      sql_setdlist[5].sqldata = (void*)knskisymd;
#line 191 "KenorderCount.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 191 "KenorderCount.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 191 "KenorderCount.sqc"
      sql_setdlist[6].sqldata = (void*)sriymd;
#line 191 "KenorderCount.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 191 "KenorderCount.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 191 "KenorderCount.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 191 "KenorderCount.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 191 "KenorderCount.sqc"
  sqlastop(0L);
}

#line 191 "KenorderCount.sqc"


    
/*
EXEC SQL FETCH c2 INTO	:Cnt;
*/

{
#line 193 "KenorderCount.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 193 "KenorderCount.sqc"
  sqlaaloc(3,1,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 193 "KenorderCount.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 193 "KenorderCount.sqc"
      sql_setdlist[0].sqldata = (void*)&Cnt;
#line 193 "KenorderCount.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 193 "KenorderCount.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 193 "KenorderCount.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 193 "KenorderCount.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 193 "KenorderCount.sqc"
  sqlastop(0L);
}

#line 193 "KenorderCount.sqc"


    
/*
EXEC SQL CLOSE c2;
*/

{
#line 195 "KenorderCount.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 195 "KenorderCount.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 195 "KenorderCount.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 195 "KenorderCount.sqc"
  sqlastop(0L);
}

#line 195 "KenorderCount.sqc"


    return Cnt;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 200 "KenorderCount.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
