static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,82,65,83,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,50,52,90,73,74,89,79,32,0,0,0,0,0,0,0,0,
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


#line 1 "Ijyosya.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Ijyosya.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Ijyosya.h"
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


#line 24 "Ijyosya.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Ijyosya.sqc"

	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    knsgrp[17];
	char    kmkcd[8];
	char    sstcd[8];
	char    knjnmn[61];
	char    rawdata[21];
	char    knskka1[13];
	char    knskka2[25];
	char    knskka2kbn[3];
	char    kkahskcd[4];
	char    sdi[4];
	char    kkacmt1[6];
	char    kkacmt2[6];
	char    ijkbnm;
	char    ijkbnf;
	char    ijkbnn;
	char    tbijkbnm;
	char    tbijkbnf;
	char    tbijkbnn;
	char    ksbr[16];
	char    nbdo[3];
	char    ykdo[3];
	char    hkkdh[27];
	char    ksndh[27];
	char	oyasstcd[8];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 58 "Ijyosya.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Ijyosya

BmlDMMInfo	IjyosyaArray[] = {
	DMM_SDATE( utkymd ),
	DMM_SSTRING( irino ),
	DMM_SCHAR( iriketflg ),
	DMM_SSHORT( zssdino ),
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( sstcd ),
	DMM_SSTRING( knjnmn ),
	DMM_SSTRING( rawdata ),
	DMM_SSTRING( knskka1 ),
	DMM_SSTRING( knskka2 ),
	DMM_SSTRING( knskka2kbn ),
	DMM_SSTRING( kkahskcd ),
	DMM_SSTRING( sdi ),
	DMM_SSTRING( kkacmt1 ),
	DMM_SSTRING( kkacmt2 ),
	DMM_SCHAR( ijkbnm ),
	DMM_SCHAR( ijkbnf ),
	DMM_SCHAR( ijkbnn ),
	DMM_SCHAR( tbijkbnm ),
	DMM_SCHAR( tbijkbnf ),
	DMM_SCHAR( tbijkbnn ),
	DMM_SSTRING( ksbr ),
	DMM_SSTRING( nbdo ),
	DMM_SSTRING( ykdo ),
	DMM_STIMESTAMP( hkkdh ),
	DMM_STIMESTAMP( ksndh ),
	DMM_SSTRING( oyasstcd ),
	DMM_NULL
};

/******************************************************************************
 * ZdbIjyosyaSelectAll()
 *    IJYOSYA レコード全件取得
 * ■引数
 *    [O]  Ijyosya** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbIjyosyaSelectAll( Ijyosya** arrayOut, int* numOut )
{
    Ijyosya*    array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 114 "Ijyosya.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		KNSGRP,
		KMKCD,
		SSTCD,
		KNJNMN,
		RAWDATA,
		KNSKKA1,
		KNSKKA2,
		KNSKKA2KBN,
		KKAHSKCD,
		SDI,
		KKACMT1,
		KKACMT2,
		IJKBNM,
		IJKBNF,
		IJKBNN,
		TBIJKBNM,
		TBIJKBNF,
		TBIJKBNN,
		KSBR,
		NBDO,
		YKDO,
		HKKDH,
		KSNDH,
		OYASSTCD
    FROM
        IJYOSYA FOR READ ONLY;
*/

#line 147 "Ijyosya.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 149 "Ijyosya.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 149 "Ijyosya.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 149 "Ijyosya.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 149 "Ijyosya.sqc"
  sqlastop(0L);
}

#line 149 "Ijyosya.sqc"


    while( 1 ) {
        Ijyosya* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:knsgrp,
			:kmkcd,
			:sstcd,
			:knjnmn,
			:rawdata,
			:knskka1,
			:knskka2,
			:knskka2kbn,
			:kkahskcd,
			:sdi,
			:kkacmt1,
			:kkacmt2,
			:ijkbnm,
			:ijkbnf,
			:ijkbnn,
			:tbijkbnm,
			:tbijkbnf,
			:tbijkbnn,
			:ksbr,
			:nbdo,
			:ykdo,
			:hkkdh,
			:ksndh,
			:oyasstcd;
*/

{
#line 182 "Ijyosya.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 182 "Ijyosya.sqc"
  sqlaaloc(3,28,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[28];
#line 182 "Ijyosya.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 182 "Ijyosya.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 182 "Ijyosya.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 182 "Ijyosya.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 182 "Ijyosya.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 182 "Ijyosya.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 182 "Ijyosya.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 182 "Ijyosya.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 182 "Ijyosya.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 182 "Ijyosya.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 182 "Ijyosya.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 182 "Ijyosya.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 182 "Ijyosya.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 182 "Ijyosya.sqc"
      sql_setdlist[6].sqldata = (void*)sstcd;
#line 182 "Ijyosya.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 61;
#line 182 "Ijyosya.sqc"
      sql_setdlist[7].sqldata = (void*)knjnmn;
#line 182 "Ijyosya.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 21;
#line 182 "Ijyosya.sqc"
      sql_setdlist[8].sqldata = (void*)rawdata;
#line 182 "Ijyosya.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 13;
#line 182 "Ijyosya.sqc"
      sql_setdlist[9].sqldata = (void*)knskka1;
#line 182 "Ijyosya.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 25;
#line 182 "Ijyosya.sqc"
      sql_setdlist[10].sqldata = (void*)knskka2;
#line 182 "Ijyosya.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 3;
#line 182 "Ijyosya.sqc"
      sql_setdlist[11].sqldata = (void*)knskka2kbn;
#line 182 "Ijyosya.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 4;
#line 182 "Ijyosya.sqc"
      sql_setdlist[12].sqldata = (void*)kkahskcd;
#line 182 "Ijyosya.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 4;
#line 182 "Ijyosya.sqc"
      sql_setdlist[13].sqldata = (void*)sdi;
#line 182 "Ijyosya.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 6;
#line 182 "Ijyosya.sqc"
      sql_setdlist[14].sqldata = (void*)kkacmt1;
#line 182 "Ijyosya.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 6;
#line 182 "Ijyosya.sqc"
      sql_setdlist[15].sqldata = (void*)kkacmt2;
#line 182 "Ijyosya.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 182 "Ijyosya.sqc"
      sql_setdlist[16].sqldata = (void*)&ijkbnm;
#line 182 "Ijyosya.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 182 "Ijyosya.sqc"
      sql_setdlist[17].sqldata = (void*)&ijkbnf;
#line 182 "Ijyosya.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 182 "Ijyosya.sqc"
      sql_setdlist[18].sqldata = (void*)&ijkbnn;
#line 182 "Ijyosya.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 182 "Ijyosya.sqc"
      sql_setdlist[19].sqldata = (void*)&tbijkbnm;
#line 182 "Ijyosya.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 182 "Ijyosya.sqc"
      sql_setdlist[20].sqldata = (void*)&tbijkbnf;
#line 182 "Ijyosya.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 182 "Ijyosya.sqc"
      sql_setdlist[21].sqldata = (void*)&tbijkbnn;
#line 182 "Ijyosya.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 16;
#line 182 "Ijyosya.sqc"
      sql_setdlist[22].sqldata = (void*)ksbr;
#line 182 "Ijyosya.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 3;
#line 182 "Ijyosya.sqc"
      sql_setdlist[23].sqldata = (void*)nbdo;
#line 182 "Ijyosya.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 3;
#line 182 "Ijyosya.sqc"
      sql_setdlist[24].sqldata = (void*)ykdo;
#line 182 "Ijyosya.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 27;
#line 182 "Ijyosya.sqc"
      sql_setdlist[25].sqldata = (void*)hkkdh;
#line 182 "Ijyosya.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 27;
#line 182 "Ijyosya.sqc"
      sql_setdlist[26].sqldata = (void*)ksndh;
#line 182 "Ijyosya.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 8;
#line 182 "Ijyosya.sqc"
      sql_setdlist[27].sqldata = (void*)oyasstcd;
#line 182 "Ijyosya.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 182 "Ijyosya.sqc"
      sqlasetdata(3,0,28,sql_setdlist,0L,0L);
    }
#line 182 "Ijyosya.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 182 "Ijyosya.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 182 "Ijyosya.sqc"
  sqlastop(0L);
}

#line 182 "Ijyosya.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Ijyosya*)ZbmlRealloc( array,
                                    sizeof( Ijyosya ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Ijyosya ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, IjyosyaArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 197 "Ijyosya.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 197 "Ijyosya.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 197 "Ijyosya.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 197 "Ijyosya.sqc"
  sqlastop(0L);
}

#line 197 "Ijyosya.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 205 "Ijyosya.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbIjyosyaSelectKey()
 *    IJYOSYA レコードKey条件取得
 * ■引数
 *    [I]  Ijyosya* pKey       取得するレコードのキー
 *    [O]  Ijyosya** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbIjyosyaSelectKey( Ijyosya* pKey, Ijyosya** arrayOut, int* numOut )
{
    Ijyosya*    array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, IjyosyaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 231 "Ijyosya.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		KNSGRP,
		KMKCD,
		SSTCD,
		KNJNMN,
		RAWDATA,
		KNSKKA1,
		KNSKKA2,
		KNSKKA2KBN,
		KKAHSKCD,
		SDI,
		KKACMT1,
		KKACMT2,
		IJKBNM,
		IJKBNF,
		IJKBNN,
		TBIJKBNM,
		TBIJKBNF,
		TBIJKBNN,
		KSBR,
		NBDO,
		YKDO,
		HKKDH,
		KSNDH,
		OYASSTCD
    FROM
        IJYOSYA
    WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		ZSSDINO = :zssdino AND
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd FOR READ ONLY;
*/

#line 270 "Ijyosya.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 272 "Ijyosya.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 272 "Ijyosya.sqc"
  sqlaaloc(2,5,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 272 "Ijyosya.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 272 "Ijyosya.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 272 "Ijyosya.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 272 "Ijyosya.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 272 "Ijyosya.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 272 "Ijyosya.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 272 "Ijyosya.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 272 "Ijyosya.sqc"
      sql_setdlist[2].sqldata = (void*)&zssdino;
#line 272 "Ijyosya.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 272 "Ijyosya.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 272 "Ijyosya.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 272 "Ijyosya.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 272 "Ijyosya.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 272 "Ijyosya.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 272 "Ijyosya.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 272 "Ijyosya.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 272 "Ijyosya.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 272 "Ijyosya.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 272 "Ijyosya.sqc"
  sqlastop(0L);
}

#line 272 "Ijyosya.sqc"


    while( 1 ) {
        Ijyosya* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:knsgrp,
			:kmkcd,
			:sstcd,
			:knjnmn,
			:rawdata,
			:knskka1,
			:knskka2,
			:knskka2kbn,
			:kkahskcd,
			:sdi,
			:kkacmt1,
			:kkacmt2,
			:ijkbnm,
			:ijkbnf,
			:ijkbnn,
			:tbijkbnm,
			:tbijkbnf,
			:tbijkbnn,
			:ksbr,
			:nbdo,
			:ykdo,
			:hkkdh,
			:ksndh,
			:oyasstcd;
*/

{
#line 305 "Ijyosya.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 305 "Ijyosya.sqc"
  sqlaaloc(3,28,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[28];
#line 305 "Ijyosya.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 305 "Ijyosya.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 305 "Ijyosya.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 305 "Ijyosya.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 305 "Ijyosya.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 305 "Ijyosya.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 305 "Ijyosya.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 305 "Ijyosya.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 305 "Ijyosya.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 305 "Ijyosya.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 305 "Ijyosya.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 305 "Ijyosya.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 305 "Ijyosya.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 305 "Ijyosya.sqc"
      sql_setdlist[6].sqldata = (void*)sstcd;
#line 305 "Ijyosya.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 61;
#line 305 "Ijyosya.sqc"
      sql_setdlist[7].sqldata = (void*)knjnmn;
#line 305 "Ijyosya.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 21;
#line 305 "Ijyosya.sqc"
      sql_setdlist[8].sqldata = (void*)rawdata;
#line 305 "Ijyosya.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 13;
#line 305 "Ijyosya.sqc"
      sql_setdlist[9].sqldata = (void*)knskka1;
#line 305 "Ijyosya.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 25;
#line 305 "Ijyosya.sqc"
      sql_setdlist[10].sqldata = (void*)knskka2;
#line 305 "Ijyosya.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 3;
#line 305 "Ijyosya.sqc"
      sql_setdlist[11].sqldata = (void*)knskka2kbn;
#line 305 "Ijyosya.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 4;
#line 305 "Ijyosya.sqc"
      sql_setdlist[12].sqldata = (void*)kkahskcd;
#line 305 "Ijyosya.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 4;
#line 305 "Ijyosya.sqc"
      sql_setdlist[13].sqldata = (void*)sdi;
#line 305 "Ijyosya.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 6;
#line 305 "Ijyosya.sqc"
      sql_setdlist[14].sqldata = (void*)kkacmt1;
#line 305 "Ijyosya.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 6;
#line 305 "Ijyosya.sqc"
      sql_setdlist[15].sqldata = (void*)kkacmt2;
#line 305 "Ijyosya.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 305 "Ijyosya.sqc"
      sql_setdlist[16].sqldata = (void*)&ijkbnm;
#line 305 "Ijyosya.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 305 "Ijyosya.sqc"
      sql_setdlist[17].sqldata = (void*)&ijkbnf;
#line 305 "Ijyosya.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 305 "Ijyosya.sqc"
      sql_setdlist[18].sqldata = (void*)&ijkbnn;
#line 305 "Ijyosya.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 305 "Ijyosya.sqc"
      sql_setdlist[19].sqldata = (void*)&tbijkbnm;
#line 305 "Ijyosya.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 305 "Ijyosya.sqc"
      sql_setdlist[20].sqldata = (void*)&tbijkbnf;
#line 305 "Ijyosya.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 305 "Ijyosya.sqc"
      sql_setdlist[21].sqldata = (void*)&tbijkbnn;
#line 305 "Ijyosya.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 16;
#line 305 "Ijyosya.sqc"
      sql_setdlist[22].sqldata = (void*)ksbr;
#line 305 "Ijyosya.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 3;
#line 305 "Ijyosya.sqc"
      sql_setdlist[23].sqldata = (void*)nbdo;
#line 305 "Ijyosya.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 3;
#line 305 "Ijyosya.sqc"
      sql_setdlist[24].sqldata = (void*)ykdo;
#line 305 "Ijyosya.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 27;
#line 305 "Ijyosya.sqc"
      sql_setdlist[25].sqldata = (void*)hkkdh;
#line 305 "Ijyosya.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 27;
#line 305 "Ijyosya.sqc"
      sql_setdlist[26].sqldata = (void*)ksndh;
#line 305 "Ijyosya.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 8;
#line 305 "Ijyosya.sqc"
      sql_setdlist[27].sqldata = (void*)oyasstcd;
#line 305 "Ijyosya.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 305 "Ijyosya.sqc"
      sqlasetdata(3,0,28,sql_setdlist,0L,0L);
    }
#line 305 "Ijyosya.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 305 "Ijyosya.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 305 "Ijyosya.sqc"
  sqlastop(0L);
}

#line 305 "Ijyosya.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Ijyosya*)ZbmlRealloc( array,
                                    sizeof( Ijyosya ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Ijyosya ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, IjyosyaArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 320 "Ijyosya.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 320 "Ijyosya.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 320 "Ijyosya.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 320 "Ijyosya.sqc"
  sqlastop(0L);
}

#line 320 "Ijyosya.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 328 "Ijyosya.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbIjyosyaInsert()
 *    IJYOSYA レコードを挿入する
 * ■引数
 *    [I]  Ijyosya* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbIjyosyaInsert( Ijyosya* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, IjyosyaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 351 "Ijyosya.sqc"


    
/*
EXEC SQL INSERT INTO IJYOSYA
    (
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		KNSGRP,
		KMKCD,
		SSTCD,
		KNJNMN,
		RAWDATA,
		KNSKKA1,
		KNSKKA2,
		KNSKKA2KBN,
		KKAHSKCD,
		SDI,
		KKACMT1,
		KKACMT2,
		IJKBNM,
		IJKBNF,
		IJKBNN,
		TBIJKBNM,
		TBIJKBNF,
		TBIJKBNN,
		KSBR,
		NBDO,
		YKDO,
		HKKDH,
		KSNDH,
		OYASSTCD
    ) VALUES (
		:utkymd,
		:irino,
		:iriketflg,
		:zssdino,
		:knsgrp,
		:kmkcd,
		:sstcd,
		:knjnmn,
		:rawdata,
		:knskka1,
		:knskka2,
		:knskka2kbn,
		:kkahskcd,
		:sdi,
		:kkacmt1,
		:kkacmt2,
		:ijkbnm,
		:ijkbnf,
		:ijkbnn,
		:tbijkbnm,
		:tbijkbnf,
		:tbijkbnn,
		:ksbr,
		:nbdo,
		:ykdo,
		:hkkdh,
		CURRENT TIMESTAMP,
		:oyasstcd
    );
*/

{
#line 412 "Ijyosya.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 412 "Ijyosya.sqc"
  sqlaaloc(2,27,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[27];
#line 412 "Ijyosya.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 412 "Ijyosya.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 412 "Ijyosya.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 412 "Ijyosya.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 412 "Ijyosya.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 412 "Ijyosya.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 412 "Ijyosya.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 412 "Ijyosya.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 412 "Ijyosya.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 412 "Ijyosya.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 412 "Ijyosya.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 412 "Ijyosya.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 412 "Ijyosya.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 412 "Ijyosya.sqc"
      sql_setdlist[6].sqldata = (void*)sstcd;
#line 412 "Ijyosya.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 61;
#line 412 "Ijyosya.sqc"
      sql_setdlist[7].sqldata = (void*)knjnmn;
#line 412 "Ijyosya.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 21;
#line 412 "Ijyosya.sqc"
      sql_setdlist[8].sqldata = (void*)rawdata;
#line 412 "Ijyosya.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 13;
#line 412 "Ijyosya.sqc"
      sql_setdlist[9].sqldata = (void*)knskka1;
#line 412 "Ijyosya.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 25;
#line 412 "Ijyosya.sqc"
      sql_setdlist[10].sqldata = (void*)knskka2;
#line 412 "Ijyosya.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 3;
#line 412 "Ijyosya.sqc"
      sql_setdlist[11].sqldata = (void*)knskka2kbn;
#line 412 "Ijyosya.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 4;
#line 412 "Ijyosya.sqc"
      sql_setdlist[12].sqldata = (void*)kkahskcd;
#line 412 "Ijyosya.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 4;
#line 412 "Ijyosya.sqc"
      sql_setdlist[13].sqldata = (void*)sdi;
#line 412 "Ijyosya.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 6;
#line 412 "Ijyosya.sqc"
      sql_setdlist[14].sqldata = (void*)kkacmt1;
#line 412 "Ijyosya.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 6;
#line 412 "Ijyosya.sqc"
      sql_setdlist[15].sqldata = (void*)kkacmt2;
#line 412 "Ijyosya.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 412 "Ijyosya.sqc"
      sql_setdlist[16].sqldata = (void*)&ijkbnm;
#line 412 "Ijyosya.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 412 "Ijyosya.sqc"
      sql_setdlist[17].sqldata = (void*)&ijkbnf;
#line 412 "Ijyosya.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 412 "Ijyosya.sqc"
      sql_setdlist[18].sqldata = (void*)&ijkbnn;
#line 412 "Ijyosya.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 412 "Ijyosya.sqc"
      sql_setdlist[19].sqldata = (void*)&tbijkbnm;
#line 412 "Ijyosya.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 412 "Ijyosya.sqc"
      sql_setdlist[20].sqldata = (void*)&tbijkbnf;
#line 412 "Ijyosya.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 412 "Ijyosya.sqc"
      sql_setdlist[21].sqldata = (void*)&tbijkbnn;
#line 412 "Ijyosya.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 16;
#line 412 "Ijyosya.sqc"
      sql_setdlist[22].sqldata = (void*)ksbr;
#line 412 "Ijyosya.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 3;
#line 412 "Ijyosya.sqc"
      sql_setdlist[23].sqldata = (void*)nbdo;
#line 412 "Ijyosya.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 3;
#line 412 "Ijyosya.sqc"
      sql_setdlist[24].sqldata = (void*)ykdo;
#line 412 "Ijyosya.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 27;
#line 412 "Ijyosya.sqc"
      sql_setdlist[25].sqldata = (void*)hkkdh;
#line 412 "Ijyosya.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 8;
#line 412 "Ijyosya.sqc"
      sql_setdlist[26].sqldata = (void*)oyasstcd;
#line 412 "Ijyosya.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 412 "Ijyosya.sqc"
      sqlasetdata(2,0,27,sql_setdlist,0L,0L);
    }
#line 412 "Ijyosya.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 412 "Ijyosya.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 412 "Ijyosya.sqc"
  sqlastop(0L);
}

#line 412 "Ijyosya.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 417 "Ijyosya.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbIjyosyaUpdate()
 *    IJYOSYA レコードを更新する
 * ■引数
 *    [I]  Ijyosya* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbIjyosyaUpdate( Ijyosya* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, IjyosyaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 441 "Ijyosya.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 442 "Ijyosya.sqc"


    
/*
EXEC SQL UPDATE IJYOSYA
    SET (
		IRIKETFLG,
		SSTCD,
		KNJNMN,
		RAWDATA,
		KNSKKA1,
		KNSKKA2,
		KNSKKA2KBN,
		KKAHSKCD,
		SDI,
		KKACMT1,
		KKACMT2,
		IJKBNM,
		IJKBNF,
		IJKBNN,
		TBIJKBNM,
		TBIJKBNF,
		TBIJKBNN,
		KSBR,
		NBDO,
		YKDO,
		HKKDH,
		KSNDH,
		OYASSTCD
    ) = (
		:iriketflg,
		:sstcd,
		:knjnmn,
		:rawdata,
		:knskka1,
		:knskka2,
		:knskka2kbn,
		:kkahskcd,
		:sdi,
		:kkacmt1,
		:kkacmt2,
		:ijkbnm,
		:ijkbnf,
		:ijkbnn,
		:tbijkbnm,
		:tbijkbnf,
		:tbijkbnn,
		:ksbr,
		:nbdo,
		:ykdo,
		:hkkdh,
		CURRENT TIMESTAMP,
		:oyasstcd
    ) WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		ZSSDINO = :zssdino AND
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd;
*/

{
#line 498 "Ijyosya.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 498 "Ijyosya.sqc"
  sqlaaloc(2,27,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[27];
#line 498 "Ijyosya.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 498 "Ijyosya.sqc"
      sql_setdlist[0].sqldata = (void*)&iriketflg;
#line 498 "Ijyosya.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 498 "Ijyosya.sqc"
      sql_setdlist[1].sqldata = (void*)sstcd;
#line 498 "Ijyosya.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 61;
#line 498 "Ijyosya.sqc"
      sql_setdlist[2].sqldata = (void*)knjnmn;
#line 498 "Ijyosya.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 21;
#line 498 "Ijyosya.sqc"
      sql_setdlist[3].sqldata = (void*)rawdata;
#line 498 "Ijyosya.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 13;
#line 498 "Ijyosya.sqc"
      sql_setdlist[4].sqldata = (void*)knskka1;
#line 498 "Ijyosya.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 25;
#line 498 "Ijyosya.sqc"
      sql_setdlist[5].sqldata = (void*)knskka2;
#line 498 "Ijyosya.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 3;
#line 498 "Ijyosya.sqc"
      sql_setdlist[6].sqldata = (void*)knskka2kbn;
#line 498 "Ijyosya.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 4;
#line 498 "Ijyosya.sqc"
      sql_setdlist[7].sqldata = (void*)kkahskcd;
#line 498 "Ijyosya.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 498 "Ijyosya.sqc"
      sql_setdlist[8].sqldata = (void*)sdi;
#line 498 "Ijyosya.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 6;
#line 498 "Ijyosya.sqc"
      sql_setdlist[9].sqldata = (void*)kkacmt1;
#line 498 "Ijyosya.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 6;
#line 498 "Ijyosya.sqc"
      sql_setdlist[10].sqldata = (void*)kkacmt2;
#line 498 "Ijyosya.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 498 "Ijyosya.sqc"
      sql_setdlist[11].sqldata = (void*)&ijkbnm;
#line 498 "Ijyosya.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[12].sqltype = 452; sql_setdlist[12].sqllen = 1;
#line 498 "Ijyosya.sqc"
      sql_setdlist[12].sqldata = (void*)&ijkbnf;
#line 498 "Ijyosya.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 498 "Ijyosya.sqc"
      sql_setdlist[13].sqldata = (void*)&ijkbnn;
#line 498 "Ijyosya.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 498 "Ijyosya.sqc"
      sql_setdlist[14].sqldata = (void*)&tbijkbnm;
#line 498 "Ijyosya.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[15].sqltype = 452; sql_setdlist[15].sqllen = 1;
#line 498 "Ijyosya.sqc"
      sql_setdlist[15].sqldata = (void*)&tbijkbnf;
#line 498 "Ijyosya.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 498 "Ijyosya.sqc"
      sql_setdlist[16].sqldata = (void*)&tbijkbnn;
#line 498 "Ijyosya.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 16;
#line 498 "Ijyosya.sqc"
      sql_setdlist[17].sqldata = (void*)ksbr;
#line 498 "Ijyosya.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 3;
#line 498 "Ijyosya.sqc"
      sql_setdlist[18].sqldata = (void*)nbdo;
#line 498 "Ijyosya.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 3;
#line 498 "Ijyosya.sqc"
      sql_setdlist[19].sqldata = (void*)ykdo;
#line 498 "Ijyosya.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 27;
#line 498 "Ijyosya.sqc"
      sql_setdlist[20].sqldata = (void*)hkkdh;
#line 498 "Ijyosya.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 8;
#line 498 "Ijyosya.sqc"
      sql_setdlist[21].sqldata = (void*)oyasstcd;
#line 498 "Ijyosya.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 11;
#line 498 "Ijyosya.sqc"
      sql_setdlist[22].sqldata = (void*)utkymd;
#line 498 "Ijyosya.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 12;
#line 498 "Ijyosya.sqc"
      sql_setdlist[23].sqldata = (void*)irino;
#line 498 "Ijyosya.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[24].sqltype = 500; sql_setdlist[24].sqllen = 2;
#line 498 "Ijyosya.sqc"
      sql_setdlist[24].sqldata = (void*)&zssdino;
#line 498 "Ijyosya.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 17;
#line 498 "Ijyosya.sqc"
      sql_setdlist[25].sqldata = (void*)knsgrp;
#line 498 "Ijyosya.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 8;
#line 498 "Ijyosya.sqc"
      sql_setdlist[26].sqldata = (void*)kmkcd;
#line 498 "Ijyosya.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 498 "Ijyosya.sqc"
      sqlasetdata(2,0,27,sql_setdlist,0L,0L);
    }
#line 498 "Ijyosya.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 498 "Ijyosya.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 498 "Ijyosya.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 498 "Ijyosya.sqc"
  sqlastop(0L);
}

#line 498 "Ijyosya.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 503 "Ijyosya.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 507 "Ijyosya.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbIjyosyaDelete()
 *    IJYOSYA レコードを削除する
 * ■引数
 *    [I]  Ijyosya* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbIjyosyaDelete( Ijyosya* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, IjyosyaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 531 "Ijyosya.sqc"


    
/*
EXEC SQL DELETE FROM IJYOSYA
    WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		ZSSDINO = :zssdino AND
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd;
*/

{
#line 539 "Ijyosya.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 539 "Ijyosya.sqc"
  sqlaaloc(2,5,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 539 "Ijyosya.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 539 "Ijyosya.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 539 "Ijyosya.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 539 "Ijyosya.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 539 "Ijyosya.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 539 "Ijyosya.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 539 "Ijyosya.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 539 "Ijyosya.sqc"
      sql_setdlist[2].sqldata = (void*)&zssdino;
#line 539 "Ijyosya.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 539 "Ijyosya.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 539 "Ijyosya.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 539 "Ijyosya.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 539 "Ijyosya.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 539 "Ijyosya.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 539 "Ijyosya.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 539 "Ijyosya.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 539 "Ijyosya.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 539 "Ijyosya.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 539 "Ijyosya.sqc"
  sqlastop(0L);
}

#line 539 "Ijyosya.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 544 "Ijyosya.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
