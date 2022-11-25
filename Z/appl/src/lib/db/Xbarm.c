static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,76,66,87,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,55,54,90,88,66,65,82,32,0,0,0,0,0,0,0,0,
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


#line 1 "Xbarm.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Xbarm.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Xbarm.h"
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


#line 24 "Xbarm.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Xbarm.sqc"

	char    knskisymd[11];
	char    bskkbn[5];
	char    bsklne[5];
	char    bskgok[7];
	char    knsgrp[17];
	char    kmkcd[8];
	char    nbkmkcd[8];
	sqlint32  pltno;
	sqlint32  knsseqst;
	sqlint32  knsseqed;
	sqlint32  bskseqst;
	sqlint32  bskseqed;
	short   pltseqst;
	short   pltseqed;
	short   pltsu;
	char    xbarmkka[25];
	char    xbarmjtkbn;
	char    xbarmjkflg;
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 49 "Xbarm.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Xbarm

BmlDMMInfo	XbarmArray[] = {
	DMM_SDATE( knskisymd ),
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( bsklne ),
	DMM_SSTRING( bskgok ),
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( nbkmkcd ),
	DMM_SLONG( pltno ),
	DMM_SLONG( knsseqst ),
	DMM_SLONG( knsseqed ),
	DMM_SLONG( bskseqst ),
	DMM_SLONG( bskseqed ),
	DMM_SSHORT( pltseqst ),
	DMM_SSHORT( pltseqed ),
	DMM_SSHORT( pltsu ),
	DMM_SSTRING( xbarmkka ),
	DMM_SCHAR( xbarmjtkbn ),
	DMM_SCHAR( xbarmjkflg ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbXbarmSelectAll()
 *    XBARM レコード全件取得
 * ■引数
 *    [O]  Xbarm** arrayOut     取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbXbarmSelectAll( Xbarm** arrayOut, int* numOut )
{
    Xbarm*      array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 96 "Xbarm.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSKISYMD,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		KNSGRP,
		KMKCD,
		NBKMKCD,
		PLTNO,
		KNSSEQST,
		KNSSEQED,
		BSKSEQST,
		BSKSEQED,
		PLTSEQST,
		PLTSEQED,
		PLTSU,
		XBARMKKA,
		XBARMJTKBN,
		XBARMJKFLG,
		KSNDH
    FROM
        XBARM FOR READ ONLY;
*/

#line 120 "Xbarm.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 122 "Xbarm.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 122 "Xbarm.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 122 "Xbarm.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 122 "Xbarm.sqc"
  sqlastop(0L);
}

#line 122 "Xbarm.sqc"


    while( 1 ) {
        Xbarm* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knskisymd,
			:bskkbn,
			:bsklne,
			:bskgok,
			:knsgrp,
			:kmkcd,
			:nbkmkcd,
			:pltno,
			:knsseqst,
			:knsseqed,
			:bskseqst,
			:bskseqed,
			:pltseqst,
			:pltseqed,
			:pltsu,
			:xbarmkka,
			:xbarmjtkbn,
			:xbarmjkflg,
			:ksndh;
*/

{
#line 146 "Xbarm.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 146 "Xbarm.sqc"
  sqlaaloc(3,19,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[19];
#line 146 "Xbarm.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 146 "Xbarm.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 146 "Xbarm.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 146 "Xbarm.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 146 "Xbarm.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 146 "Xbarm.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 146 "Xbarm.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 146 "Xbarm.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 146 "Xbarm.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 146 "Xbarm.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 7;
#line 146 "Xbarm.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 146 "Xbarm.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 146 "Xbarm.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 146 "Xbarm.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 146 "Xbarm.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 146 "Xbarm.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 146 "Xbarm.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 146 "Xbarm.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 146 "Xbarm.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 146 "Xbarm.sqc"
      sql_setdlist[6].sqldata = (void*)nbkmkcd;
#line 146 "Xbarm.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 146 "Xbarm.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 146 "Xbarm.sqc"
      sql_setdlist[7].sqldata = (void*)&pltno;
#line 146 "Xbarm.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 146 "Xbarm.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 146 "Xbarm.sqc"
      sql_setdlist[8].sqldata = (void*)&knsseqst;
#line 146 "Xbarm.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 146 "Xbarm.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 146 "Xbarm.sqc"
      sql_setdlist[9].sqldata = (void*)&knsseqed;
#line 146 "Xbarm.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 146 "Xbarm.sqc"
      sql_setdlist[10].sqltype = 496; sql_setdlist[10].sqllen = 4;
#line 146 "Xbarm.sqc"
      sql_setdlist[10].sqldata = (void*)&bskseqst;
#line 146 "Xbarm.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 146 "Xbarm.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 146 "Xbarm.sqc"
      sql_setdlist[11].sqldata = (void*)&bskseqed;
#line 146 "Xbarm.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 146 "Xbarm.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 146 "Xbarm.sqc"
      sql_setdlist[12].sqldata = (void*)&pltseqst;
#line 146 "Xbarm.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 146 "Xbarm.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 146 "Xbarm.sqc"
      sql_setdlist[13].sqldata = (void*)&pltseqed;
#line 146 "Xbarm.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 146 "Xbarm.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 146 "Xbarm.sqc"
      sql_setdlist[14].sqldata = (void*)&pltsu;
#line 146 "Xbarm.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 146 "Xbarm.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 25;
#line 146 "Xbarm.sqc"
      sql_setdlist[15].sqldata = (void*)xbarmkka;
#line 146 "Xbarm.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 146 "Xbarm.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 146 "Xbarm.sqc"
      sql_setdlist[16].sqldata = (void*)&xbarmjtkbn;
#line 146 "Xbarm.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 146 "Xbarm.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 146 "Xbarm.sqc"
      sql_setdlist[17].sqldata = (void*)&xbarmjkflg;
#line 146 "Xbarm.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 146 "Xbarm.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 146 "Xbarm.sqc"
      sql_setdlist[18].sqldata = (void*)ksndh;
#line 146 "Xbarm.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 146 "Xbarm.sqc"
      sqlasetdata(3,0,19,sql_setdlist,0L,0L);
    }
#line 146 "Xbarm.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 146 "Xbarm.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 146 "Xbarm.sqc"
  sqlastop(0L);
}

#line 146 "Xbarm.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Xbarm*)ZbmlRealloc( array,
                                    sizeof( Xbarm ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Xbarm ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, XbarmArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 161 "Xbarm.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 161 "Xbarm.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 161 "Xbarm.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 161 "Xbarm.sqc"
  sqlastop(0L);
}

#line 161 "Xbarm.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 169 "Xbarm.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbXbarmSelectKey()
 *    XBARM レコードKey条件取得
 * ■引数
 *    [I]  Xbarm* pKey       取得するレコードのキー
 *    [O]  Xbarm** arrayOut     取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbXbarmSelectKey( Xbarm* pKey, Xbarm** arrayOut, int* numOut )
{
    Xbarm*      array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, XbarmArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 195 "Xbarm.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSKISYMD,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		KNSGRP,
		KMKCD,
		NBKMKCD,
		PLTNO,
		KNSSEQST,
		KNSSEQED,
		BSKSEQST,
		BSKSEQED,
		PLTSEQST,
		PLTSEQED,
		PLTSU,
		XBARMKKA,
		XBARMJTKBN,
		XBARMJKFLG,
		KSNDH
    FROM
        XBARM
    WHERE
		KNSKISYMD = :knskisymd AND
		BSKKBN = :bskkbn AND
		BSKGOK = :bskgok AND
		KMKCD = :kmkcd AND
		PLTNO = :pltno FOR READ ONLY;
*/

#line 225 "Xbarm.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 227 "Xbarm.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 227 "Xbarm.sqc"
  sqlaaloc(2,5,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 227 "Xbarm.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 227 "Xbarm.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 227 "Xbarm.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 227 "Xbarm.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 227 "Xbarm.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 227 "Xbarm.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 227 "Xbarm.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 7;
#line 227 "Xbarm.sqc"
      sql_setdlist[2].sqldata = (void*)bskgok;
#line 227 "Xbarm.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 227 "Xbarm.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 227 "Xbarm.sqc"
      sql_setdlist[3].sqldata = (void*)kmkcd;
#line 227 "Xbarm.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 227 "Xbarm.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 227 "Xbarm.sqc"
      sql_setdlist[4].sqldata = (void*)&pltno;
#line 227 "Xbarm.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 227 "Xbarm.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 227 "Xbarm.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 227 "Xbarm.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 227 "Xbarm.sqc"
  sqlastop(0L);
}

#line 227 "Xbarm.sqc"


    while( 1 ) {
        Xbarm* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knskisymd,
			:bskkbn,
			:bsklne,
			:bskgok,
			:knsgrp,
			:kmkcd,
			:nbkmkcd,
			:pltno,
			:knsseqst,
			:knsseqed,
			:bskseqst,
			:bskseqed,
			:pltseqst,
			:pltseqed,
			:pltsu,
			:xbarmkka,
			:xbarmjtkbn,
			:xbarmjkflg,
			:ksndh;
*/

{
#line 251 "Xbarm.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 251 "Xbarm.sqc"
  sqlaaloc(3,19,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[19];
#line 251 "Xbarm.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 251 "Xbarm.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 251 "Xbarm.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 251 "Xbarm.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 251 "Xbarm.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 251 "Xbarm.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 251 "Xbarm.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 251 "Xbarm.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 251 "Xbarm.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 251 "Xbarm.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 7;
#line 251 "Xbarm.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 251 "Xbarm.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 251 "Xbarm.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 251 "Xbarm.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 251 "Xbarm.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 251 "Xbarm.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 251 "Xbarm.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 251 "Xbarm.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 251 "Xbarm.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 251 "Xbarm.sqc"
      sql_setdlist[6].sqldata = (void*)nbkmkcd;
#line 251 "Xbarm.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 251 "Xbarm.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 251 "Xbarm.sqc"
      sql_setdlist[7].sqldata = (void*)&pltno;
#line 251 "Xbarm.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 251 "Xbarm.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 251 "Xbarm.sqc"
      sql_setdlist[8].sqldata = (void*)&knsseqst;
#line 251 "Xbarm.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 251 "Xbarm.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 251 "Xbarm.sqc"
      sql_setdlist[9].sqldata = (void*)&knsseqed;
#line 251 "Xbarm.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 251 "Xbarm.sqc"
      sql_setdlist[10].sqltype = 496; sql_setdlist[10].sqllen = 4;
#line 251 "Xbarm.sqc"
      sql_setdlist[10].sqldata = (void*)&bskseqst;
#line 251 "Xbarm.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 251 "Xbarm.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 251 "Xbarm.sqc"
      sql_setdlist[11].sqldata = (void*)&bskseqed;
#line 251 "Xbarm.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 251 "Xbarm.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 251 "Xbarm.sqc"
      sql_setdlist[12].sqldata = (void*)&pltseqst;
#line 251 "Xbarm.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 251 "Xbarm.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 251 "Xbarm.sqc"
      sql_setdlist[13].sqldata = (void*)&pltseqed;
#line 251 "Xbarm.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 251 "Xbarm.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 251 "Xbarm.sqc"
      sql_setdlist[14].sqldata = (void*)&pltsu;
#line 251 "Xbarm.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 251 "Xbarm.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 25;
#line 251 "Xbarm.sqc"
      sql_setdlist[15].sqldata = (void*)xbarmkka;
#line 251 "Xbarm.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 251 "Xbarm.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 251 "Xbarm.sqc"
      sql_setdlist[16].sqldata = (void*)&xbarmjtkbn;
#line 251 "Xbarm.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 251 "Xbarm.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 251 "Xbarm.sqc"
      sql_setdlist[17].sqldata = (void*)&xbarmjkflg;
#line 251 "Xbarm.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 251 "Xbarm.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 251 "Xbarm.sqc"
      sql_setdlist[18].sqldata = (void*)ksndh;
#line 251 "Xbarm.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 251 "Xbarm.sqc"
      sqlasetdata(3,0,19,sql_setdlist,0L,0L);
    }
#line 251 "Xbarm.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 251 "Xbarm.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 251 "Xbarm.sqc"
  sqlastop(0L);
}

#line 251 "Xbarm.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Xbarm*)ZbmlRealloc( array,
                                    sizeof( Xbarm ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Xbarm ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, XbarmArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 266 "Xbarm.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 266 "Xbarm.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 266 "Xbarm.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 266 "Xbarm.sqc"
  sqlastop(0L);
}

#line 266 "Xbarm.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 274 "Xbarm.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbXbarmInsert()
 *    XBARM レコードを挿入する
 * ■引数
 *    [I]  Xbarm* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbXbarmInsert( Xbarm* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, XbarmArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 297 "Xbarm.sqc"


    
/*
EXEC SQL INSERT INTO XBARM
    (
		KNSKISYMD,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		KNSGRP,
		KMKCD,
		NBKMKCD,
		PLTNO,
		KNSSEQST,
		KNSSEQED,
		BSKSEQST,
		BSKSEQED,
		PLTSEQST,
		PLTSEQED,
		PLTSU,
		XBARMKKA,
		XBARMJTKBN,
		XBARMJKFLG,
		KSNDH
    ) VALUES (
		:knskisymd,
		:bskkbn,
		:bsklne,
		:bskgok,
		:knsgrp,
		:kmkcd,
		:nbkmkcd,
		:pltno,
		:knsseqst,
		:knsseqed,
		:bskseqst,
		:bskseqed,
		:pltseqst,
		:pltseqed,
		:pltsu,
		:xbarmkka,
		:xbarmjtkbn,
		:xbarmjkflg,
		:ksndh
    );
*/

{
#line 340 "Xbarm.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 340 "Xbarm.sqc"
  sqlaaloc(2,19,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[19];
#line 340 "Xbarm.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 340 "Xbarm.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 340 "Xbarm.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 340 "Xbarm.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 340 "Xbarm.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 340 "Xbarm.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 340 "Xbarm.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 340 "Xbarm.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 340 "Xbarm.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 340 "Xbarm.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 7;
#line 340 "Xbarm.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 340 "Xbarm.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 340 "Xbarm.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 340 "Xbarm.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 340 "Xbarm.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 340 "Xbarm.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 340 "Xbarm.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 340 "Xbarm.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 340 "Xbarm.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 340 "Xbarm.sqc"
      sql_setdlist[6].sqldata = (void*)nbkmkcd;
#line 340 "Xbarm.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 340 "Xbarm.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 340 "Xbarm.sqc"
      sql_setdlist[7].sqldata = (void*)&pltno;
#line 340 "Xbarm.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 340 "Xbarm.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 340 "Xbarm.sqc"
      sql_setdlist[8].sqldata = (void*)&knsseqst;
#line 340 "Xbarm.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 340 "Xbarm.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 340 "Xbarm.sqc"
      sql_setdlist[9].sqldata = (void*)&knsseqed;
#line 340 "Xbarm.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 340 "Xbarm.sqc"
      sql_setdlist[10].sqltype = 496; sql_setdlist[10].sqllen = 4;
#line 340 "Xbarm.sqc"
      sql_setdlist[10].sqldata = (void*)&bskseqst;
#line 340 "Xbarm.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 340 "Xbarm.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 340 "Xbarm.sqc"
      sql_setdlist[11].sqldata = (void*)&bskseqed;
#line 340 "Xbarm.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 340 "Xbarm.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 340 "Xbarm.sqc"
      sql_setdlist[12].sqldata = (void*)&pltseqst;
#line 340 "Xbarm.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 340 "Xbarm.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 340 "Xbarm.sqc"
      sql_setdlist[13].sqldata = (void*)&pltseqed;
#line 340 "Xbarm.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 340 "Xbarm.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 340 "Xbarm.sqc"
      sql_setdlist[14].sqldata = (void*)&pltsu;
#line 340 "Xbarm.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 340 "Xbarm.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 25;
#line 340 "Xbarm.sqc"
      sql_setdlist[15].sqldata = (void*)xbarmkka;
#line 340 "Xbarm.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 340 "Xbarm.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 340 "Xbarm.sqc"
      sql_setdlist[16].sqldata = (void*)&xbarmjtkbn;
#line 340 "Xbarm.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 340 "Xbarm.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 340 "Xbarm.sqc"
      sql_setdlist[17].sqldata = (void*)&xbarmjkflg;
#line 340 "Xbarm.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 340 "Xbarm.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 340 "Xbarm.sqc"
      sql_setdlist[18].sqldata = (void*)ksndh;
#line 340 "Xbarm.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 340 "Xbarm.sqc"
      sqlasetdata(2,0,19,sql_setdlist,0L,0L);
    }
#line 340 "Xbarm.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 340 "Xbarm.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 340 "Xbarm.sqc"
  sqlastop(0L);
}

#line 340 "Xbarm.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 345 "Xbarm.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbXbarmUpdate()
 *    XBARM レコードを更新する
 * ■引数
 *    [I]  Xbarm* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbXbarmUpdate( Xbarm* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, XbarmArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 369 "Xbarm.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 370 "Xbarm.sqc"


    
/*
EXEC SQL UPDATE XBARM
    SET (
		BSKLNE,
		KNSGRP,
		NBKMKCD,
		KNSSEQST,
		KNSSEQED,
		BSKSEQST,
		BSKSEQED,
		PLTSEQST,
		PLTSEQED,
		PLTSU,
		XBARMKKA,
		XBARMJTKBN,
		XBARMJKFLG,
		KSNDH
    ) = (
		:bsklne,
		:knsgrp,
		:nbkmkcd,
		:knsseqst,
		:knsseqed,
		:bskseqst,
		:bskseqed,
		:pltseqst,
		:pltseqed,
		:pltsu,
		:xbarmkka,
		:xbarmjtkbn,
		:xbarmjkflg,
		:ksndh
    ) WHERE
		KNSKISYMD = :knskisymd AND
		BSKKBN = :bskkbn AND
		BSKGOK = :bskgok AND
		KMKCD = :kmkcd AND
		PLTNO = :pltno;
*/

{
#line 408 "Xbarm.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 408 "Xbarm.sqc"
  sqlaaloc(2,19,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[19];
#line 408 "Xbarm.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 408 "Xbarm.sqc"
      sql_setdlist[0].sqldata = (void*)bsklne;
#line 408 "Xbarm.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 408 "Xbarm.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 408 "Xbarm.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 408 "Xbarm.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 408 "Xbarm.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 408 "Xbarm.sqc"
      sql_setdlist[2].sqldata = (void*)nbkmkcd;
#line 408 "Xbarm.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 408 "Xbarm.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 408 "Xbarm.sqc"
      sql_setdlist[3].sqldata = (void*)&knsseqst;
#line 408 "Xbarm.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 408 "Xbarm.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 408 "Xbarm.sqc"
      sql_setdlist[4].sqldata = (void*)&knsseqed;
#line 408 "Xbarm.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 408 "Xbarm.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 408 "Xbarm.sqc"
      sql_setdlist[5].sqldata = (void*)&bskseqst;
#line 408 "Xbarm.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 408 "Xbarm.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 408 "Xbarm.sqc"
      sql_setdlist[6].sqldata = (void*)&bskseqed;
#line 408 "Xbarm.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 408 "Xbarm.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 408 "Xbarm.sqc"
      sql_setdlist[7].sqldata = (void*)&pltseqst;
#line 408 "Xbarm.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 408 "Xbarm.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 408 "Xbarm.sqc"
      sql_setdlist[8].sqldata = (void*)&pltseqed;
#line 408 "Xbarm.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 408 "Xbarm.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 408 "Xbarm.sqc"
      sql_setdlist[9].sqldata = (void*)&pltsu;
#line 408 "Xbarm.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 408 "Xbarm.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 25;
#line 408 "Xbarm.sqc"
      sql_setdlist[10].sqldata = (void*)xbarmkka;
#line 408 "Xbarm.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 408 "Xbarm.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 408 "Xbarm.sqc"
      sql_setdlist[11].sqldata = (void*)&xbarmjtkbn;
#line 408 "Xbarm.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 408 "Xbarm.sqc"
      sql_setdlist[12].sqltype = 452; sql_setdlist[12].sqllen = 1;
#line 408 "Xbarm.sqc"
      sql_setdlist[12].sqldata = (void*)&xbarmjkflg;
#line 408 "Xbarm.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 408 "Xbarm.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 27;
#line 408 "Xbarm.sqc"
      sql_setdlist[13].sqldata = (void*)ksndh;
#line 408 "Xbarm.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 408 "Xbarm.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 11;
#line 408 "Xbarm.sqc"
      sql_setdlist[14].sqldata = (void*)knskisymd;
#line 408 "Xbarm.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 408 "Xbarm.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 5;
#line 408 "Xbarm.sqc"
      sql_setdlist[15].sqldata = (void*)bskkbn;
#line 408 "Xbarm.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 408 "Xbarm.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 7;
#line 408 "Xbarm.sqc"
      sql_setdlist[16].sqldata = (void*)bskgok;
#line 408 "Xbarm.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 408 "Xbarm.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 8;
#line 408 "Xbarm.sqc"
      sql_setdlist[17].sqldata = (void*)kmkcd;
#line 408 "Xbarm.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 408 "Xbarm.sqc"
      sql_setdlist[18].sqltype = 496; sql_setdlist[18].sqllen = 4;
#line 408 "Xbarm.sqc"
      sql_setdlist[18].sqldata = (void*)&pltno;
#line 408 "Xbarm.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 408 "Xbarm.sqc"
      sqlasetdata(2,0,19,sql_setdlist,0L,0L);
    }
#line 408 "Xbarm.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 408 "Xbarm.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 408 "Xbarm.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 408 "Xbarm.sqc"
  sqlastop(0L);
}

#line 408 "Xbarm.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 413 "Xbarm.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 417 "Xbarm.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbXbarmDelete()
 *    XBARM レコードを削除する
 * ■引数
 *    [I]  Xbarm* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbXbarmDelete( Xbarm* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, XbarmArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 441 "Xbarm.sqc"


    
/*
EXEC SQL DELETE FROM XBARM
    WHERE
		KNSKISYMD = :knskisymd AND
		BSKKBN = :bskkbn AND
		BSKGOK = :bskgok AND
		KMKCD = :kmkcd AND
		PLTNO = :pltno;
*/

{
#line 449 "Xbarm.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 449 "Xbarm.sqc"
  sqlaaloc(2,5,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 449 "Xbarm.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 449 "Xbarm.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 449 "Xbarm.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 449 "Xbarm.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 449 "Xbarm.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 449 "Xbarm.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 449 "Xbarm.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 7;
#line 449 "Xbarm.sqc"
      sql_setdlist[2].sqldata = (void*)bskgok;
#line 449 "Xbarm.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 449 "Xbarm.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 449 "Xbarm.sqc"
      sql_setdlist[3].sqldata = (void*)kmkcd;
#line 449 "Xbarm.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 449 "Xbarm.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 449 "Xbarm.sqc"
      sql_setdlist[4].sqldata = (void*)&pltno;
#line 449 "Xbarm.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 449 "Xbarm.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 449 "Xbarm.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 449 "Xbarm.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 449 "Xbarm.sqc"
  sqlastop(0L);
}

#line 449 "Xbarm.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 454 "Xbarm.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
