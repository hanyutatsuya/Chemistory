static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,78,66,86,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,54,53,90,83,79,85,75,32,0,0,0,0,0,0,0,0,
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


#line 1 "Soukan.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Soukan.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Soukan.h"
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


#line 24 "Soukan.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Soukan.sqc"

	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    knsgrp[17];
	char    kmkcd[8];
	char    skskmkcd[8];
	char    sriymd[11];
	char    kntno[14];
	char    kntketflg;
	char    skssriymd[11];
	char    skskntno[14];
	char    sksknsgslbcd[4];
	char    rawdata[21];
	char    knskka1[13];
	char    knskka2[25];
	char    knskka2kbn[3];
	char    kkahskcd[4];
	char    sdi[4];
	char    kkacmt1[6];
	char    kkacmt2[6];
	char    kkajkcd;
	char    ksbr[16];
	char    nbdo[3];
	char    ykdo[3];
	char    ksndh[27];
	char    trkdh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 57 "Soukan.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Soukan

BmlDMMInfo	SoukanArray[] = {
	DMM_SDATE( utkymd ),
	DMM_SSTRING( irino ),
	DMM_SCHAR( iriketflg ),
	DMM_SSHORT( zssdino ),
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( skskmkcd ),
	DMM_SDATE( sriymd ),
	DMM_SSTRING( kntno ),
	DMM_SCHAR( kntketflg ),
	DMM_SDATE( skssriymd ),
	DMM_SSTRING( skskntno ),
	DMM_SSTRING( sksknsgslbcd ),
	DMM_SSTRING( rawdata ),
	DMM_SSTRING( knskka1 ),
	DMM_SSTRING( knskka2 ),
	DMM_SSTRING( knskka2kbn ),
	DMM_SSTRING( kkahskcd ),
	DMM_SSTRING( sdi ),
	DMM_SSTRING( kkacmt1 ),
	DMM_SSTRING( kkacmt2 ),
	DMM_SCHAR( kkajkcd ),
	DMM_SSTRING( ksbr ),
	DMM_SSTRING( nbdo ),
	DMM_SSTRING( ykdo ),
	DMM_STIMESTAMP( ksndh ),
	DMM_STIMESTAMP( trkdh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbSoukanSelectAll()
 *    SOUKAN レコード全件取得
 * ■引数
 *    [O]  Soukan** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbSoukanSelectAll( Soukan** arrayOut, int* numOut )
{
    Soukan*     array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 112 "Soukan.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		KNSGRP,
		KMKCD,
		SKSKMKCD,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		SKSSRIYMD,
		SKSKNTNO,
		SKSKNSGSLBCD,
		RAWDATA,
		KNSKKA1,
		KNSKKA2,
		KNSKKA2KBN,
		KKAHSKCD,
		SDI,
		KKACMT1,
		KKACMT2,
		KKAJKCD,
		KSBR,
		NBDO,
		YKDO,
		KSNDH,
		TRKDH
    FROM
        SOUKAN FOR READ ONLY;
*/

#line 144 "Soukan.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 146 "Soukan.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 146 "Soukan.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 146 "Soukan.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 146 "Soukan.sqc"
  sqlastop(0L);
}

#line 146 "Soukan.sqc"


    while( 1 ) {
        Soukan* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:knsgrp,
			:kmkcd,
			:skskmkcd,
			:sriymd,
			:kntno,
			:kntketflg,
			:skssriymd,
			:skskntno,
			:sksknsgslbcd,
			:rawdata,
			:knskka1,
			:knskka2,
			:knskka2kbn,
			:kkahskcd,
			:sdi,
			:kkacmt1,
			:kkacmt2,
			:kkajkcd,
			:ksbr,
			:nbdo,
			:ykdo,
			:ksndh,
			:trkdh;
*/

{
#line 178 "Soukan.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 178 "Soukan.sqc"
  sqlaaloc(3,27,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[27];
#line 178 "Soukan.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 178 "Soukan.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 178 "Soukan.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 178 "Soukan.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 178 "Soukan.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 178 "Soukan.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 178 "Soukan.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 178 "Soukan.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 178 "Soukan.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 178 "Soukan.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 178 "Soukan.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 178 "Soukan.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 178 "Soukan.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 178 "Soukan.sqc"
      sql_setdlist[6].sqldata = (void*)skskmkcd;
#line 178 "Soukan.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 178 "Soukan.sqc"
      sql_setdlist[7].sqldata = (void*)sriymd;
#line 178 "Soukan.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 14;
#line 178 "Soukan.sqc"
      sql_setdlist[8].sqldata = (void*)kntno;
#line 178 "Soukan.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 178 "Soukan.sqc"
      sql_setdlist[9].sqldata = (void*)&kntketflg;
#line 178 "Soukan.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 178 "Soukan.sqc"
      sql_setdlist[10].sqldata = (void*)skssriymd;
#line 178 "Soukan.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 14;
#line 178 "Soukan.sqc"
      sql_setdlist[11].sqldata = (void*)skskntno;
#line 178 "Soukan.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 4;
#line 178 "Soukan.sqc"
      sql_setdlist[12].sqldata = (void*)sksknsgslbcd;
#line 178 "Soukan.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 178 "Soukan.sqc"
      sql_setdlist[13].sqldata = (void*)rawdata;
#line 178 "Soukan.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 13;
#line 178 "Soukan.sqc"
      sql_setdlist[14].sqldata = (void*)knskka1;
#line 178 "Soukan.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 25;
#line 178 "Soukan.sqc"
      sql_setdlist[15].sqldata = (void*)knskka2;
#line 178 "Soukan.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 3;
#line 178 "Soukan.sqc"
      sql_setdlist[16].sqldata = (void*)knskka2kbn;
#line 178 "Soukan.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 4;
#line 178 "Soukan.sqc"
      sql_setdlist[17].sqldata = (void*)kkahskcd;
#line 178 "Soukan.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 4;
#line 178 "Soukan.sqc"
      sql_setdlist[18].sqldata = (void*)sdi;
#line 178 "Soukan.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 6;
#line 178 "Soukan.sqc"
      sql_setdlist[19].sqldata = (void*)kkacmt1;
#line 178 "Soukan.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 6;
#line 178 "Soukan.sqc"
      sql_setdlist[20].sqldata = (void*)kkacmt2;
#line 178 "Soukan.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 178 "Soukan.sqc"
      sql_setdlist[21].sqldata = (void*)&kkajkcd;
#line 178 "Soukan.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 16;
#line 178 "Soukan.sqc"
      sql_setdlist[22].sqldata = (void*)ksbr;
#line 178 "Soukan.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 3;
#line 178 "Soukan.sqc"
      sql_setdlist[23].sqldata = (void*)nbdo;
#line 178 "Soukan.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 3;
#line 178 "Soukan.sqc"
      sql_setdlist[24].sqldata = (void*)ykdo;
#line 178 "Soukan.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 27;
#line 178 "Soukan.sqc"
      sql_setdlist[25].sqldata = (void*)ksndh;
#line 178 "Soukan.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 178 "Soukan.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 27;
#line 178 "Soukan.sqc"
      sql_setdlist[26].sqldata = (void*)trkdh;
#line 178 "Soukan.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 178 "Soukan.sqc"
      sqlasetdata(3,0,27,sql_setdlist,0L,0L);
    }
#line 178 "Soukan.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 178 "Soukan.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 178 "Soukan.sqc"
  sqlastop(0L);
}

#line 178 "Soukan.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Soukan*)ZbmlRealloc( array,
                                    sizeof( Soukan ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Soukan ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, SoukanArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 193 "Soukan.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 193 "Soukan.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 193 "Soukan.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 193 "Soukan.sqc"
  sqlastop(0L);
}

#line 193 "Soukan.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 201 "Soukan.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbSoukanSelectKey()
 *    SOUKAN レコードKey条件取得
 * ■引数
 *    [I]  Soukan* pKey       取得するレコードのキー
 *    [O]  Soukan** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbSoukanSelectKey( Soukan* pKey, Soukan** arrayOut, int* numOut )
{
    Soukan*     array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, SoukanArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 227 "Soukan.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		KNSGRP,
		KMKCD,
		SKSKMKCD,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		SKSSRIYMD,
		SKSKNTNO,
		SKSKNSGSLBCD,
		RAWDATA,
		KNSKKA1,
		KNSKKA2,
		KNSKKA2KBN,
		KKAHSKCD,
		SDI,
		KKACMT1,
		KKACMT2,
		KKAJKCD,
		KSBR,
		NBDO,
		YKDO,
		KSNDH,
		TRKDH
    FROM
        SOUKAN
    WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		ZSSDINO = :zssdino AND
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd FOR READ ONLY;
*/

#line 265 "Soukan.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 267 "Soukan.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 267 "Soukan.sqc"
  sqlaaloc(2,5,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 267 "Soukan.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 267 "Soukan.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 267 "Soukan.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 267 "Soukan.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 267 "Soukan.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 267 "Soukan.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 267 "Soukan.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 267 "Soukan.sqc"
      sql_setdlist[2].sqldata = (void*)&zssdino;
#line 267 "Soukan.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 267 "Soukan.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 267 "Soukan.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 267 "Soukan.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 267 "Soukan.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 267 "Soukan.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 267 "Soukan.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 267 "Soukan.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 267 "Soukan.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 267 "Soukan.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 267 "Soukan.sqc"
  sqlastop(0L);
}

#line 267 "Soukan.sqc"


    while( 1 ) {
        Soukan* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:knsgrp,
			:kmkcd,
			:skskmkcd,
			:sriymd,
			:kntno,
			:kntketflg,
			:skssriymd,
			:skskntno,
			:sksknsgslbcd,
			:rawdata,
			:knskka1,
			:knskka2,
			:knskka2kbn,
			:kkahskcd,
			:sdi,
			:kkacmt1,
			:kkacmt2,
			:kkajkcd,
			:ksbr,
			:nbdo,
			:ykdo,
			:ksndh,
			:trkdh;
*/

{
#line 299 "Soukan.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 299 "Soukan.sqc"
  sqlaaloc(3,27,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[27];
#line 299 "Soukan.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 299 "Soukan.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 299 "Soukan.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 299 "Soukan.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 299 "Soukan.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 299 "Soukan.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 299 "Soukan.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 299 "Soukan.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 299 "Soukan.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 299 "Soukan.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 299 "Soukan.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 299 "Soukan.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 299 "Soukan.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 299 "Soukan.sqc"
      sql_setdlist[6].sqldata = (void*)skskmkcd;
#line 299 "Soukan.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 299 "Soukan.sqc"
      sql_setdlist[7].sqldata = (void*)sriymd;
#line 299 "Soukan.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 14;
#line 299 "Soukan.sqc"
      sql_setdlist[8].sqldata = (void*)kntno;
#line 299 "Soukan.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 299 "Soukan.sqc"
      sql_setdlist[9].sqldata = (void*)&kntketflg;
#line 299 "Soukan.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 299 "Soukan.sqc"
      sql_setdlist[10].sqldata = (void*)skssriymd;
#line 299 "Soukan.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 14;
#line 299 "Soukan.sqc"
      sql_setdlist[11].sqldata = (void*)skskntno;
#line 299 "Soukan.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 4;
#line 299 "Soukan.sqc"
      sql_setdlist[12].sqldata = (void*)sksknsgslbcd;
#line 299 "Soukan.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 299 "Soukan.sqc"
      sql_setdlist[13].sqldata = (void*)rawdata;
#line 299 "Soukan.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 13;
#line 299 "Soukan.sqc"
      sql_setdlist[14].sqldata = (void*)knskka1;
#line 299 "Soukan.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 25;
#line 299 "Soukan.sqc"
      sql_setdlist[15].sqldata = (void*)knskka2;
#line 299 "Soukan.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 3;
#line 299 "Soukan.sqc"
      sql_setdlist[16].sqldata = (void*)knskka2kbn;
#line 299 "Soukan.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 4;
#line 299 "Soukan.sqc"
      sql_setdlist[17].sqldata = (void*)kkahskcd;
#line 299 "Soukan.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 4;
#line 299 "Soukan.sqc"
      sql_setdlist[18].sqldata = (void*)sdi;
#line 299 "Soukan.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 6;
#line 299 "Soukan.sqc"
      sql_setdlist[19].sqldata = (void*)kkacmt1;
#line 299 "Soukan.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 6;
#line 299 "Soukan.sqc"
      sql_setdlist[20].sqldata = (void*)kkacmt2;
#line 299 "Soukan.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 299 "Soukan.sqc"
      sql_setdlist[21].sqldata = (void*)&kkajkcd;
#line 299 "Soukan.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 16;
#line 299 "Soukan.sqc"
      sql_setdlist[22].sqldata = (void*)ksbr;
#line 299 "Soukan.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 3;
#line 299 "Soukan.sqc"
      sql_setdlist[23].sqldata = (void*)nbdo;
#line 299 "Soukan.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 3;
#line 299 "Soukan.sqc"
      sql_setdlist[24].sqldata = (void*)ykdo;
#line 299 "Soukan.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 27;
#line 299 "Soukan.sqc"
      sql_setdlist[25].sqldata = (void*)ksndh;
#line 299 "Soukan.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 299 "Soukan.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 27;
#line 299 "Soukan.sqc"
      sql_setdlist[26].sqldata = (void*)trkdh;
#line 299 "Soukan.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 299 "Soukan.sqc"
      sqlasetdata(3,0,27,sql_setdlist,0L,0L);
    }
#line 299 "Soukan.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 299 "Soukan.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 299 "Soukan.sqc"
  sqlastop(0L);
}

#line 299 "Soukan.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Soukan*)ZbmlRealloc( array,
                                    sizeof( Soukan ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Soukan ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, SoukanArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 314 "Soukan.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 314 "Soukan.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 314 "Soukan.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 314 "Soukan.sqc"
  sqlastop(0L);
}

#line 314 "Soukan.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 322 "Soukan.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbSoukanInsert()
 *    SOUKAN レコードを挿入する
 * ■引数
 *    [I]  Soukan* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbSoukanInsert( Soukan* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, SoukanArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 345 "Soukan.sqc"


    
/*
EXEC SQL INSERT INTO SOUKAN
    (
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		KNSGRP,
		KMKCD,
		SKSKMKCD,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		SKSSRIYMD,
		SKSKNTNO,
		SKSKNSGSLBCD,
		RAWDATA,
		KNSKKA1,
		KNSKKA2,
		KNSKKA2KBN,
		KKAHSKCD,
		SDI,
		KKACMT1,
		KKACMT2,
		KKAJKCD,
		KSBR,
		NBDO,
		YKDO,
		KSNDH,
		TRKDH
    ) VALUES (
		:utkymd,
		:irino,
		:iriketflg,
		:zssdino,
		:knsgrp,
		:kmkcd,
		:skskmkcd,
		:sriymd,
		:kntno,
		:kntketflg,
		:skssriymd,
		:skskntno,
		:sksknsgslbcd,
		:rawdata,
		:knskka1,
		:knskka2,
		:knskka2kbn,
		:kkahskcd,
		:sdi,
		:kkacmt1,
		:kkacmt2,
		:kkajkcd,
		:ksbr,
		:nbdo,
		:ykdo,
		CURRENT TIMESTAMP,
		CURRENT TIMESTAMP
    );
*/

{
#line 404 "Soukan.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 404 "Soukan.sqc"
  sqlaaloc(2,25,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[25];
#line 404 "Soukan.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 404 "Soukan.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 404 "Soukan.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 404 "Soukan.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 404 "Soukan.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 404 "Soukan.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 404 "Soukan.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 404 "Soukan.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 404 "Soukan.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 404 "Soukan.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 404 "Soukan.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 404 "Soukan.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 404 "Soukan.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 404 "Soukan.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 404 "Soukan.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 404 "Soukan.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 404 "Soukan.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 404 "Soukan.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 404 "Soukan.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 404 "Soukan.sqc"
      sql_setdlist[6].sqldata = (void*)skskmkcd;
#line 404 "Soukan.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 404 "Soukan.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 404 "Soukan.sqc"
      sql_setdlist[7].sqldata = (void*)sriymd;
#line 404 "Soukan.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 404 "Soukan.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 14;
#line 404 "Soukan.sqc"
      sql_setdlist[8].sqldata = (void*)kntno;
#line 404 "Soukan.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 404 "Soukan.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 404 "Soukan.sqc"
      sql_setdlist[9].sqldata = (void*)&kntketflg;
#line 404 "Soukan.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 404 "Soukan.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 404 "Soukan.sqc"
      sql_setdlist[10].sqldata = (void*)skssriymd;
#line 404 "Soukan.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 404 "Soukan.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 14;
#line 404 "Soukan.sqc"
      sql_setdlist[11].sqldata = (void*)skskntno;
#line 404 "Soukan.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 404 "Soukan.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 4;
#line 404 "Soukan.sqc"
      sql_setdlist[12].sqldata = (void*)sksknsgslbcd;
#line 404 "Soukan.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 404 "Soukan.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 404 "Soukan.sqc"
      sql_setdlist[13].sqldata = (void*)rawdata;
#line 404 "Soukan.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 404 "Soukan.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 13;
#line 404 "Soukan.sqc"
      sql_setdlist[14].sqldata = (void*)knskka1;
#line 404 "Soukan.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 404 "Soukan.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 25;
#line 404 "Soukan.sqc"
      sql_setdlist[15].sqldata = (void*)knskka2;
#line 404 "Soukan.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 404 "Soukan.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 3;
#line 404 "Soukan.sqc"
      sql_setdlist[16].sqldata = (void*)knskka2kbn;
#line 404 "Soukan.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 404 "Soukan.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 4;
#line 404 "Soukan.sqc"
      sql_setdlist[17].sqldata = (void*)kkahskcd;
#line 404 "Soukan.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 404 "Soukan.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 4;
#line 404 "Soukan.sqc"
      sql_setdlist[18].sqldata = (void*)sdi;
#line 404 "Soukan.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 404 "Soukan.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 6;
#line 404 "Soukan.sqc"
      sql_setdlist[19].sqldata = (void*)kkacmt1;
#line 404 "Soukan.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 404 "Soukan.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 6;
#line 404 "Soukan.sqc"
      sql_setdlist[20].sqldata = (void*)kkacmt2;
#line 404 "Soukan.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 404 "Soukan.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 404 "Soukan.sqc"
      sql_setdlist[21].sqldata = (void*)&kkajkcd;
#line 404 "Soukan.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 404 "Soukan.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 16;
#line 404 "Soukan.sqc"
      sql_setdlist[22].sqldata = (void*)ksbr;
#line 404 "Soukan.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 404 "Soukan.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 3;
#line 404 "Soukan.sqc"
      sql_setdlist[23].sqldata = (void*)nbdo;
#line 404 "Soukan.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 404 "Soukan.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 3;
#line 404 "Soukan.sqc"
      sql_setdlist[24].sqldata = (void*)ykdo;
#line 404 "Soukan.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 404 "Soukan.sqc"
      sqlasetdata(2,0,25,sql_setdlist,0L,0L);
    }
#line 404 "Soukan.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 404 "Soukan.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 404 "Soukan.sqc"
  sqlastop(0L);
}

#line 404 "Soukan.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 409 "Soukan.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbSoukanUpdate()
 *    SOUKAN レコードを更新する
 * ■引数
 *    [I]  Soukan* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbSoukanUpdate( Soukan* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, SoukanArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 433 "Soukan.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 434 "Soukan.sqc"


    
/*
EXEC SQL UPDATE SOUKAN
    SET (
		IRIKETFLG,
		SKSKMKCD,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		SKSSRIYMD,
		SKSKNTNO,
		SKSKNSGSLBCD,
		RAWDATA,
		KNSKKA1,
		KNSKKA2,
		KNSKKA2KBN,
		KKAHSKCD,
		SDI,
		KKACMT1,
		KKACMT2,
		KKAJKCD,
		KSBR,
		NBDO,
		YKDO,
		KSNDH,
		TRKDH
    ) = (
		:iriketflg,
		:skskmkcd,
		:sriymd,
		:kntno,
		:kntketflg,
		:skssriymd,
		:skskntno,
		:sksknsgslbcd,
		:rawdata,
		:knskka1,
		:knskka2,
		:knskka2kbn,
		:kkahskcd,
		:sdi,
		:kkacmt1,
		:kkacmt2,
		:kkajkcd,
		:ksbr,
		:nbdo,
		:ykdo,
		CURRENT TIMESTAMP,
		:trkdh
    ) WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		ZSSDINO = :zssdino AND
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd;
*/

{
#line 488 "Soukan.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 488 "Soukan.sqc"
  sqlaaloc(2,26,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[26];
#line 488 "Soukan.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 488 "Soukan.sqc"
      sql_setdlist[0].sqldata = (void*)&iriketflg;
#line 488 "Soukan.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 488 "Soukan.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 488 "Soukan.sqc"
      sql_setdlist[1].sqldata = (void*)skskmkcd;
#line 488 "Soukan.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 488 "Soukan.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 488 "Soukan.sqc"
      sql_setdlist[2].sqldata = (void*)sriymd;
#line 488 "Soukan.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 488 "Soukan.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 14;
#line 488 "Soukan.sqc"
      sql_setdlist[3].sqldata = (void*)kntno;
#line 488 "Soukan.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 488 "Soukan.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 488 "Soukan.sqc"
      sql_setdlist[4].sqldata = (void*)&kntketflg;
#line 488 "Soukan.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 488 "Soukan.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 488 "Soukan.sqc"
      sql_setdlist[5].sqldata = (void*)skssriymd;
#line 488 "Soukan.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 488 "Soukan.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 14;
#line 488 "Soukan.sqc"
      sql_setdlist[6].sqldata = (void*)skskntno;
#line 488 "Soukan.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 488 "Soukan.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 4;
#line 488 "Soukan.sqc"
      sql_setdlist[7].sqldata = (void*)sksknsgslbcd;
#line 488 "Soukan.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 488 "Soukan.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 21;
#line 488 "Soukan.sqc"
      sql_setdlist[8].sqldata = (void*)rawdata;
#line 488 "Soukan.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 488 "Soukan.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 13;
#line 488 "Soukan.sqc"
      sql_setdlist[9].sqldata = (void*)knskka1;
#line 488 "Soukan.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 488 "Soukan.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 25;
#line 488 "Soukan.sqc"
      sql_setdlist[10].sqldata = (void*)knskka2;
#line 488 "Soukan.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 488 "Soukan.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 3;
#line 488 "Soukan.sqc"
      sql_setdlist[11].sqldata = (void*)knskka2kbn;
#line 488 "Soukan.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 488 "Soukan.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 4;
#line 488 "Soukan.sqc"
      sql_setdlist[12].sqldata = (void*)kkahskcd;
#line 488 "Soukan.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 488 "Soukan.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 4;
#line 488 "Soukan.sqc"
      sql_setdlist[13].sqldata = (void*)sdi;
#line 488 "Soukan.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 488 "Soukan.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 6;
#line 488 "Soukan.sqc"
      sql_setdlist[14].sqldata = (void*)kkacmt1;
#line 488 "Soukan.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 488 "Soukan.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 6;
#line 488 "Soukan.sqc"
      sql_setdlist[15].sqldata = (void*)kkacmt2;
#line 488 "Soukan.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 488 "Soukan.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 488 "Soukan.sqc"
      sql_setdlist[16].sqldata = (void*)&kkajkcd;
#line 488 "Soukan.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 488 "Soukan.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 16;
#line 488 "Soukan.sqc"
      sql_setdlist[17].sqldata = (void*)ksbr;
#line 488 "Soukan.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 488 "Soukan.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 3;
#line 488 "Soukan.sqc"
      sql_setdlist[18].sqldata = (void*)nbdo;
#line 488 "Soukan.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 488 "Soukan.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 3;
#line 488 "Soukan.sqc"
      sql_setdlist[19].sqldata = (void*)ykdo;
#line 488 "Soukan.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 488 "Soukan.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 27;
#line 488 "Soukan.sqc"
      sql_setdlist[20].sqldata = (void*)trkdh;
#line 488 "Soukan.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 488 "Soukan.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 11;
#line 488 "Soukan.sqc"
      sql_setdlist[21].sqldata = (void*)utkymd;
#line 488 "Soukan.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 488 "Soukan.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 12;
#line 488 "Soukan.sqc"
      sql_setdlist[22].sqldata = (void*)irino;
#line 488 "Soukan.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 488 "Soukan.sqc"
      sql_setdlist[23].sqltype = 500; sql_setdlist[23].sqllen = 2;
#line 488 "Soukan.sqc"
      sql_setdlist[23].sqldata = (void*)&zssdino;
#line 488 "Soukan.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 488 "Soukan.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 17;
#line 488 "Soukan.sqc"
      sql_setdlist[24].sqldata = (void*)knsgrp;
#line 488 "Soukan.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 488 "Soukan.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 8;
#line 488 "Soukan.sqc"
      sql_setdlist[25].sqldata = (void*)kmkcd;
#line 488 "Soukan.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 488 "Soukan.sqc"
      sqlasetdata(2,0,26,sql_setdlist,0L,0L);
    }
#line 488 "Soukan.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 488 "Soukan.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 488 "Soukan.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 488 "Soukan.sqc"
  sqlastop(0L);
}

#line 488 "Soukan.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 493 "Soukan.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 497 "Soukan.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbSoukanDelete()
 *    SOUKAN レコードを削除する
 * ■引数
 *    [I]  Soukan* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbSoukanDelete( Soukan* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, SoukanArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 521 "Soukan.sqc"


    
/*
EXEC SQL DELETE FROM SOUKAN
    WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		ZSSDINO = :zssdino AND
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd;
*/

{
#line 529 "Soukan.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 529 "Soukan.sqc"
  sqlaaloc(2,5,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 529 "Soukan.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 529 "Soukan.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 529 "Soukan.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 529 "Soukan.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 529 "Soukan.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 529 "Soukan.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 529 "Soukan.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 529 "Soukan.sqc"
      sql_setdlist[2].sqldata = (void*)&zssdino;
#line 529 "Soukan.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 529 "Soukan.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 529 "Soukan.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 529 "Soukan.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 529 "Soukan.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 529 "Soukan.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 529 "Soukan.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 529 "Soukan.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 529 "Soukan.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 529 "Soukan.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 529 "Soukan.sqc"
  sqlastop(0L);
}

#line 529 "Soukan.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 534 "Soukan.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
