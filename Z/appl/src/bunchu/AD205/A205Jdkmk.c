static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,102,65,67,86,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,65,50,48,53,74,68,75,77,0,0,0,0,0,0,0,0,
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


#line 1 "A205Jdkmk.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Jdkmkmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "A205Jdkmk.h"
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


#line 24 "A205Jdkmk.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "A205Jdkmk.sqc"

	char    knsgrp[17];
	char    kmkcd[8];
	char    jknsgrp[17];
	char    jkmkcd[8];
	char    hhkumflg;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 39 "A205Jdkmk.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Jdkmkmst

BmlDMMInfo	JdkmkmstArray[] = {
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( jknsgrp ),
	DMM_SSTRING( jkmkcd ),
	DMM_SCHAR( hhkumflg ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbJdkmkmstSelectKey()
 *    JDKMKMST レコードKey条件取得
 * ■引数
 *    [I]  Jdkmkmst* pKey       取得するレコードのキー
 *    [O]  Jdkmkmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long A205JdkmkSelKey( Jdkmkmst* pKey, Jdkmkmst** arrayOut, int* numOut )
{
    Jdkmkmst*   array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, JdkmkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 83 "A205Jdkmk.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSGRP,
		KMKCD,
		JKNSGRP,
		JKMKCD,
		HHKUMFLG,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        JDKMKMST
    WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KAIYMD <= :kaiymd AND 
		HAIYMD >= :kaiymd
		FOR READ ONLY;
*/

#line 103 "A205Jdkmk.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 105 "A205Jdkmk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 105 "A205Jdkmk.sqc"
  sqlaaloc(2,4,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 105 "A205Jdkmk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 105 "A205Jdkmk.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 105 "A205Jdkmk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 105 "A205Jdkmk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 105 "A205Jdkmk.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 105 "A205Jdkmk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 105 "A205Jdkmk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 105 "A205Jdkmk.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 105 "A205Jdkmk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 105 "A205Jdkmk.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 105 "A205Jdkmk.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 105 "A205Jdkmk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 105 "A205Jdkmk.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 105 "A205Jdkmk.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 105 "A205Jdkmk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 105 "A205Jdkmk.sqc"
  sqlastop(0L);
}

#line 105 "A205Jdkmk.sqc"


    while( 1 ) {
        Jdkmkmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knsgrp,
			:kmkcd,
			:jknsgrp,
			:jkmkcd,
			:hhkumflg,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 119 "A205Jdkmk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 119 "A205Jdkmk.sqc"
  sqlaaloc(3,9,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 17;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[2].sqldata = (void*)jknsgrp;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[3].sqldata = (void*)jkmkcd;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[4].sqldata = (void*)&hhkumflg;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[5].sqldata = (void*)kaiymd;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[6].sqldata = (void*)haiymd;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[7].sqldata = (void*)hnktntid;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 119 "A205Jdkmk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 119 "A205Jdkmk.sqc"
      sqlasetdata(3,0,9,sql_setdlist,0L,0L);
    }
#line 119 "A205Jdkmk.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 119 "A205Jdkmk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 119 "A205Jdkmk.sqc"
  sqlastop(0L);
}

#line 119 "A205Jdkmk.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Jdkmkmst*)ZbmlRealloc( array,
                                    sizeof( Jdkmkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Jdkmkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, JdkmkmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 134 "A205Jdkmk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 134 "A205Jdkmk.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 134 "A205Jdkmk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 134 "A205Jdkmk.sqc"
  sqlastop(0L);
}

#line 134 "A205Jdkmk.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 142 "A205Jdkmk.sqc"

    return sqlca.sqlcode;
}

long A205JdkmkSelAll( Jdkmkmst** arrayOut, int* numOut )
{
    Jdkmkmst*   array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 151 "A205Jdkmk.sqc"


    
/*
EXEC SQL DECLARE c3 CURSOR FOR
    SELECT
		KNSGRP,
		KMKCD,
		JKNSGRP,
		JKMKCD,
		HHKUMFLG,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        JDKMKMST
	FOR READ ONLY;
*/

#line 166 "A205Jdkmk.sqc"


    
/*
EXEC SQL OPEN c3;
*/

{
#line 168 "A205Jdkmk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 168 "A205Jdkmk.sqc"
  sqlacall((unsigned short)26,2,0,0,0L);
#line 168 "A205Jdkmk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 168 "A205Jdkmk.sqc"
  sqlastop(0L);
}

#line 168 "A205Jdkmk.sqc"


    while( 1 ) {
        Jdkmkmst* rec;

        
/*
EXEC SQL FETCH c3 INTO
			:knsgrp,
			:kmkcd,
			:jknsgrp,
			:jkmkcd,
			:hhkumflg,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 182 "A205Jdkmk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 182 "A205Jdkmk.sqc"
  sqlaaloc(3,9,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 17;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[2].sqldata = (void*)jknsgrp;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[3].sqldata = (void*)jkmkcd;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[4].sqldata = (void*)&hhkumflg;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[5].sqldata = (void*)kaiymd;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[6].sqldata = (void*)haiymd;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[7].sqldata = (void*)hnktntid;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 182 "A205Jdkmk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 182 "A205Jdkmk.sqc"
      sqlasetdata(3,0,9,sql_setdlist,0L,0L);
    }
#line 182 "A205Jdkmk.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 182 "A205Jdkmk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 182 "A205Jdkmk.sqc"
  sqlastop(0L);
}

#line 182 "A205Jdkmk.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Jdkmkmst*)ZbmlRealloc( array,
                                    sizeof( Jdkmkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Jdkmkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, JdkmkmstArray );
    }

    
/*
EXEC SQL CLOSE c3;
*/

{
#line 197 "A205Jdkmk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 197 "A205Jdkmk.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 197 "A205Jdkmk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 197 "A205Jdkmk.sqc"
  sqlastop(0L);
}

#line 197 "A205Jdkmk.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 205 "A205Jdkmk.sqc"

    return sqlca.sqlcode;
}

/** End of File *********************************************************/
