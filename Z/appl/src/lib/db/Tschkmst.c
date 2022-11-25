static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,54,65,87,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,55,52,90,84,83,67,72,32,0,0,0,0,0,0,0,0,
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


#line 1 "Tschkmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Tschkmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Tschkmst.h"
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


#line 24 "Tschkmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Tschkmst.sqc"

	char    kmkcdzen[8];
	char    kmkcdgo[8];
	char    tskchktyp;
	char    maxval[21];
	char    minval[21];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 39 "Tschkmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Tschkmst

BmlDMMInfo	TschkmstArray[] = {
	DMM_SSTRING( kmkcdzen ),
	DMM_SSTRING( kmkcdgo ),
	DMM_SCHAR( tskchktyp ),
	DMM_SSTRING( maxval ),
	DMM_SSTRING( minval ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbTschkmstSelectAll()
 *    TSCHKMST レコード全件取得
 * ■引数
 *    [O]  Tschkmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbTschkmstSelectAll( Tschkmst** arrayOut, int* numOut )
{
    Tschkmst*   array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 76 "Tschkmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KMKCDZEN,
		KMKCDGO,
		TSKCHKTYP,
		MAXVAL,
		MINVAL,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        TSCHKMST FOR READ ONLY;
*/

#line 90 "Tschkmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 92 "Tschkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 92 "Tschkmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 92 "Tschkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 92 "Tschkmst.sqc"
  sqlastop(0L);
}

#line 92 "Tschkmst.sqc"


    while( 1 ) {
        Tschkmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:kmkcdzen,
			:kmkcdgo,
			:tskchktyp,
			:maxval,
			:minval,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 106 "Tschkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 106 "Tschkmst.sqc"
  sqlaaloc(3,9,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 106 "Tschkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 106 "Tschkmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcdzen;
#line 106 "Tschkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 106 "Tschkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 106 "Tschkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcdgo;
#line 106 "Tschkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 106 "Tschkmst.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 106 "Tschkmst.sqc"
      sql_setdlist[2].sqldata = (void*)&tskchktyp;
#line 106 "Tschkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 106 "Tschkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 21;
#line 106 "Tschkmst.sqc"
      sql_setdlist[3].sqldata = (void*)maxval;
#line 106 "Tschkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 106 "Tschkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 21;
#line 106 "Tschkmst.sqc"
      sql_setdlist[4].sqldata = (void*)minval;
#line 106 "Tschkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 106 "Tschkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 106 "Tschkmst.sqc"
      sql_setdlist[5].sqldata = (void*)kaiymd;
#line 106 "Tschkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 106 "Tschkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 106 "Tschkmst.sqc"
      sql_setdlist[6].sqldata = (void*)haiymd;
#line 106 "Tschkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 106 "Tschkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 106 "Tschkmst.sqc"
      sql_setdlist[7].sqldata = (void*)hnktntid;
#line 106 "Tschkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 106 "Tschkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 106 "Tschkmst.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 106 "Tschkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 106 "Tschkmst.sqc"
      sqlasetdata(3,0,9,sql_setdlist,0L,0L);
    }
#line 106 "Tschkmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 106 "Tschkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 106 "Tschkmst.sqc"
  sqlastop(0L);
}

#line 106 "Tschkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Tschkmst*)ZbmlRealloc( array,
                                    sizeof( Tschkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Tschkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, TschkmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 121 "Tschkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 121 "Tschkmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 121 "Tschkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 121 "Tschkmst.sqc"
  sqlastop(0L);
}

#line 121 "Tschkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 129 "Tschkmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbTschkmstSelectKey()
 *    TSCHKMST レコードKey条件取得
 * ■引数
 *    [I]  Tschkmst* pKey       取得するレコードのキー
 *    [O]  Tschkmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbTschkmstSelectKey( Tschkmst* pKey, Tschkmst** arrayOut, int* numOut )
{
    Tschkmst*   array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, TschkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 155 "Tschkmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KMKCDZEN,
		KMKCDGO,
		TSKCHKTYP,
		MAXVAL,
		MINVAL,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        TSCHKMST
    WHERE
		KMKCDZEN = :kmkcdzen AND
		KMKCDGO = :kmkcdgo AND
		TSKCHKTYP = :tskchktyp AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 174 "Tschkmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 176 "Tschkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 176 "Tschkmst.sqc"
  sqlaaloc(2,4,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 176 "Tschkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 176 "Tschkmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcdzen;
#line 176 "Tschkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 176 "Tschkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 176 "Tschkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcdgo;
#line 176 "Tschkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 176 "Tschkmst.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 176 "Tschkmst.sqc"
      sql_setdlist[2].sqldata = (void*)&tskchktyp;
#line 176 "Tschkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 176 "Tschkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 176 "Tschkmst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 176 "Tschkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 176 "Tschkmst.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 176 "Tschkmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 176 "Tschkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 176 "Tschkmst.sqc"
  sqlastop(0L);
}

#line 176 "Tschkmst.sqc"


    while( 1 ) {
        Tschkmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:kmkcdzen,
			:kmkcdgo,
			:tskchktyp,
			:maxval,
			:minval,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 190 "Tschkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 190 "Tschkmst.sqc"
  sqlaaloc(3,9,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 190 "Tschkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 190 "Tschkmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcdzen;
#line 190 "Tschkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 190 "Tschkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 190 "Tschkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcdgo;
#line 190 "Tschkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 190 "Tschkmst.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 190 "Tschkmst.sqc"
      sql_setdlist[2].sqldata = (void*)&tskchktyp;
#line 190 "Tschkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 190 "Tschkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 21;
#line 190 "Tschkmst.sqc"
      sql_setdlist[3].sqldata = (void*)maxval;
#line 190 "Tschkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 190 "Tschkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 21;
#line 190 "Tschkmst.sqc"
      sql_setdlist[4].sqldata = (void*)minval;
#line 190 "Tschkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 190 "Tschkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 190 "Tschkmst.sqc"
      sql_setdlist[5].sqldata = (void*)kaiymd;
#line 190 "Tschkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 190 "Tschkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 190 "Tschkmst.sqc"
      sql_setdlist[6].sqldata = (void*)haiymd;
#line 190 "Tschkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 190 "Tschkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 190 "Tschkmst.sqc"
      sql_setdlist[7].sqldata = (void*)hnktntid;
#line 190 "Tschkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 190 "Tschkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 190 "Tschkmst.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 190 "Tschkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 190 "Tschkmst.sqc"
      sqlasetdata(3,0,9,sql_setdlist,0L,0L);
    }
#line 190 "Tschkmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 190 "Tschkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 190 "Tschkmst.sqc"
  sqlastop(0L);
}

#line 190 "Tschkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Tschkmst*)ZbmlRealloc( array,
                                    sizeof( Tschkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Tschkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, TschkmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 205 "Tschkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 205 "Tschkmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 205 "Tschkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 205 "Tschkmst.sqc"
  sqlastop(0L);
}

#line 205 "Tschkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 213 "Tschkmst.sqc"

    return sqlca.sqlcode;
}
long ZdbTschkmstSelectKey2( Tschkmst* pKey, Tschkmst** arrayOut, int* numOut )
{
    Tschkmst*   array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, TschkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 227 "Tschkmst.sqc"


    
/*
EXEC SQL DECLARE c3 CURSOR FOR
    SELECT
		KMKCDZEN,
		KMKCDGO,
		TSKCHKTYP,
		MAXVAL,
		MINVAL,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        TSCHKMST
    WHERE
		((KMKCDZEN = :kmkcdzen) OR
		 (KMKCDGO = :kmkcdgo)) AND
		KAIYMD <= CURRENT DATE FOR READ ONLY;
*/

#line 245 "Tschkmst.sqc"


    
/*
EXEC SQL OPEN c3;
*/

{
#line 247 "Tschkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 247 "Tschkmst.sqc"
  sqlaaloc(2,2,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 247 "Tschkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 247 "Tschkmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcdzen;
#line 247 "Tschkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 247 "Tschkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 247 "Tschkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcdgo;
#line 247 "Tschkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 247 "Tschkmst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 247 "Tschkmst.sqc"
  sqlacall((unsigned short)26,3,2,0,0L);
#line 247 "Tschkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 247 "Tschkmst.sqc"
  sqlastop(0L);
}

#line 247 "Tschkmst.sqc"


    while( 1 ) {
        Tschkmst* rec;

        
/*
EXEC SQL FETCH c3 INTO
			:kmkcdzen,
			:kmkcdgo,
			:tskchktyp,
			:maxval,
			:minval,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 261 "Tschkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 261 "Tschkmst.sqc"
  sqlaaloc(3,9,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 261 "Tschkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 261 "Tschkmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcdzen;
#line 261 "Tschkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 261 "Tschkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 261 "Tschkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcdgo;
#line 261 "Tschkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 261 "Tschkmst.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 261 "Tschkmst.sqc"
      sql_setdlist[2].sqldata = (void*)&tskchktyp;
#line 261 "Tschkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 261 "Tschkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 21;
#line 261 "Tschkmst.sqc"
      sql_setdlist[3].sqldata = (void*)maxval;
#line 261 "Tschkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 261 "Tschkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 21;
#line 261 "Tschkmst.sqc"
      sql_setdlist[4].sqldata = (void*)minval;
#line 261 "Tschkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 261 "Tschkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 261 "Tschkmst.sqc"
      sql_setdlist[5].sqldata = (void*)kaiymd;
#line 261 "Tschkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 261 "Tschkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 261 "Tschkmst.sqc"
      sql_setdlist[6].sqldata = (void*)haiymd;
#line 261 "Tschkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 261 "Tschkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 261 "Tschkmst.sqc"
      sql_setdlist[7].sqldata = (void*)hnktntid;
#line 261 "Tschkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 261 "Tschkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 261 "Tschkmst.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 261 "Tschkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 261 "Tschkmst.sqc"
      sqlasetdata(3,0,9,sql_setdlist,0L,0L);
    }
#line 261 "Tschkmst.sqc"
  sqlacall((unsigned short)25,3,0,3,0L);
#line 261 "Tschkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 261 "Tschkmst.sqc"
  sqlastop(0L);
}

#line 261 "Tschkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Tschkmst*)ZbmlRealloc( array,
                                    sizeof( Tschkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Tschkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, TschkmstArray );
    }

    
/*
EXEC SQL CLOSE c3;
*/

{
#line 276 "Tschkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 276 "Tschkmst.sqc"
  sqlacall((unsigned short)20,3,0,0,0L);
#line 276 "Tschkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 276 "Tschkmst.sqc"
  sqlastop(0L);
}

#line 276 "Tschkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 284 "Tschkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbTschkmstInsert()
 *    TSCHKMST レコードを挿入する
 * ■引数
 *    [I]  Tschkmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbTschkmstInsert( Tschkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, TschkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 307 "Tschkmst.sqc"


    
/*
EXEC SQL INSERT INTO TSCHKMST
    (
		KMKCDZEN,
		KMKCDGO,
		TSKCHKTYP,
		MAXVAL,
		MINVAL,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:kmkcdzen,
		:kmkcdgo,
		:tskchktyp,
		:maxval,
		:minval,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 330 "Tschkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 330 "Tschkmst.sqc"
  sqlaaloc(2,9,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 330 "Tschkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 330 "Tschkmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcdzen;
#line 330 "Tschkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 330 "Tschkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 330 "Tschkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcdgo;
#line 330 "Tschkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 330 "Tschkmst.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 330 "Tschkmst.sqc"
      sql_setdlist[2].sqldata = (void*)&tskchktyp;
#line 330 "Tschkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 330 "Tschkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 21;
#line 330 "Tschkmst.sqc"
      sql_setdlist[3].sqldata = (void*)maxval;
#line 330 "Tschkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 330 "Tschkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 21;
#line 330 "Tschkmst.sqc"
      sql_setdlist[4].sqldata = (void*)minval;
#line 330 "Tschkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 330 "Tschkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 330 "Tschkmst.sqc"
      sql_setdlist[5].sqldata = (void*)kaiymd;
#line 330 "Tschkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 330 "Tschkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 330 "Tschkmst.sqc"
      sql_setdlist[6].sqldata = (void*)haiymd;
#line 330 "Tschkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 330 "Tschkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 330 "Tschkmst.sqc"
      sql_setdlist[7].sqldata = (void*)hnktntid;
#line 330 "Tschkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 330 "Tschkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 330 "Tschkmst.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 330 "Tschkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 330 "Tschkmst.sqc"
      sqlasetdata(2,0,9,sql_setdlist,0L,0L);
    }
#line 330 "Tschkmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 330 "Tschkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 330 "Tschkmst.sqc"
  sqlastop(0L);
}

#line 330 "Tschkmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 335 "Tschkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbTschkmstUpdate()
 *    TSCHKMST レコードを更新する
 * ■引数
 *    [I]  Tschkmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbTschkmstUpdate( Tschkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, TschkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 359 "Tschkmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 360 "Tschkmst.sqc"


    
/*
EXEC SQL UPDATE TSCHKMST
    SET (
		MAXVAL,
		MINVAL,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:maxval,
		:minval,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		KMKCDZEN = :kmkcdzen AND
		KMKCDGO = :kmkcdgo AND
		TSKCHKTYP = :tskchktyp AND
		KAIYMD = :kaiymd;
*/

{
#line 379 "Tschkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 379 "Tschkmst.sqc"
  sqlaaloc(2,9,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 379 "Tschkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 21;
#line 379 "Tschkmst.sqc"
      sql_setdlist[0].sqldata = (void*)maxval;
#line 379 "Tschkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 379 "Tschkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 379 "Tschkmst.sqc"
      sql_setdlist[1].sqldata = (void*)minval;
#line 379 "Tschkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 379 "Tschkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 379 "Tschkmst.sqc"
      sql_setdlist[2].sqldata = (void*)haiymd;
#line 379 "Tschkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 379 "Tschkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 9;
#line 379 "Tschkmst.sqc"
      sql_setdlist[3].sqldata = (void*)hnktntid;
#line 379 "Tschkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 379 "Tschkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 27;
#line 379 "Tschkmst.sqc"
      sql_setdlist[4].sqldata = (void*)ksndh;
#line 379 "Tschkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 379 "Tschkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 379 "Tschkmst.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcdzen;
#line 379 "Tschkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 379 "Tschkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 379 "Tschkmst.sqc"
      sql_setdlist[6].sqldata = (void*)kmkcdgo;
#line 379 "Tschkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 379 "Tschkmst.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 379 "Tschkmst.sqc"
      sql_setdlist[7].sqldata = (void*)&tskchktyp;
#line 379 "Tschkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 379 "Tschkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 379 "Tschkmst.sqc"
      sql_setdlist[8].sqldata = (void*)kaiymd;
#line 379 "Tschkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 379 "Tschkmst.sqc"
      sqlasetdata(2,0,9,sql_setdlist,0L,0L);
    }
#line 379 "Tschkmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 379 "Tschkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 379 "Tschkmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 379 "Tschkmst.sqc"
  sqlastop(0L);
}

#line 379 "Tschkmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 384 "Tschkmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 388 "Tschkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbTschkmstDelete()
 *    TSCHKMST レコードを削除する
 * ■引数
 *    [I]  Tschkmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbTschkmstDelete( Tschkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, TschkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 412 "Tschkmst.sqc"


    
/*
EXEC SQL DELETE FROM TSCHKMST
    WHERE
		KMKCDZEN = :kmkcdzen AND
		KMKCDGO = :kmkcdgo AND
		TSKCHKTYP = :tskchktyp AND
		KAIYMD = :kaiymd;
*/

{
#line 419 "Tschkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 419 "Tschkmst.sqc"
  sqlaaloc(2,4,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 419 "Tschkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 419 "Tschkmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcdzen;
#line 419 "Tschkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 419 "Tschkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 419 "Tschkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcdgo;
#line 419 "Tschkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 419 "Tschkmst.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 419 "Tschkmst.sqc"
      sql_setdlist[2].sqldata = (void*)&tskchktyp;
#line 419 "Tschkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 419 "Tschkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 419 "Tschkmst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 419 "Tschkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 419 "Tschkmst.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 419 "Tschkmst.sqc"
  sqlacall((unsigned short)24,6,2,0,0L);
#line 419 "Tschkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 419 "Tschkmst.sqc"
  sqlastop(0L);
}

#line 419 "Tschkmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 424 "Tschkmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
