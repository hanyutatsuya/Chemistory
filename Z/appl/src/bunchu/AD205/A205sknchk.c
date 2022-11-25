static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,65,65,65,86,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,65,50,48,53,83,75,78,67,0,0,0,0,0,0,0,0,
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


#line 1 "A205sknchk.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Skchkmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "A205sknchk.h"
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


#line 24 "A205sknchk.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "A205sknchk.sqc"

	char    knsgrp[17];
	char    kmkcd[8];
	char    sstcd[8];
	char    zaicd[5];
	short   krknsgrp;
	char    soukan[129];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 40 "A205sknchk.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Skchkmst

BmlDMMInfo	SkchkmstArray[] = {
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( sstcd ),
	DMM_SSTRING( zaicd ),
	DMM_SSHORT( krknsgrp ),
	DMM_SSTRING( soukan ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * AD205sknchkSelKey()
 *    SKCHKMST レコードKey条件取得
 * ■引数
 *    [I]  Skchkmst* pKey       取得するレコードのキー
 *    [O]  Skchkmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long AD205sknchkSelKey( Skchkmst* pKey, Skchkmst** arrayOut, int* numOut )
{
    Skchkmst*   array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, SkchkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 85 "A205sknchk.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSGRP,
		KMKCD,
		SSTCD,
		ZAICD,
		KRKNSGRP,
		SOUKAN,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        SKCHKMST
    WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
			(SSTCD = :sstcd OR
			 SSTCD = '0000000') AND
		ZAICD = :zaicd AND
		KAIYMD <= :kaiymd AND
		HAIYMD >= :kaiymd
		FOR READ ONLY;
*/

#line 109 "A205sknchk.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 111 "A205sknchk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 111 "A205sknchk.sqc"
  sqlaaloc(2,6,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 111 "A205sknchk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 111 "A205sknchk.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 111 "A205sknchk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 111 "A205sknchk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 111 "A205sknchk.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 111 "A205sknchk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 111 "A205sknchk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 111 "A205sknchk.sqc"
      sql_setdlist[2].sqldata = (void*)sstcd;
#line 111 "A205sknchk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 111 "A205sknchk.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 111 "A205sknchk.sqc"
      sql_setdlist[3].sqldata = (void*)zaicd;
#line 111 "A205sknchk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 111 "A205sknchk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 111 "A205sknchk.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 111 "A205sknchk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 111 "A205sknchk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 111 "A205sknchk.sqc"
      sql_setdlist[5].sqldata = (void*)kaiymd;
#line 111 "A205sknchk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 111 "A205sknchk.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 111 "A205sknchk.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 111 "A205sknchk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 111 "A205sknchk.sqc"
  sqlastop(0L);
}

#line 111 "A205sknchk.sqc"


    while( 1 ) {
        Skchkmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knsgrp,
			:kmkcd,
			:sstcd,
			:zaicd,
			:krknsgrp,
			:soukan,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 126 "A205sknchk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 126 "A205sknchk.sqc"
  sqlaaloc(3,10,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 126 "A205sknchk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 126 "A205sknchk.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 126 "A205sknchk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 126 "A205sknchk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 126 "A205sknchk.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 126 "A205sknchk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 126 "A205sknchk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 126 "A205sknchk.sqc"
      sql_setdlist[2].sqldata = (void*)sstcd;
#line 126 "A205sknchk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 126 "A205sknchk.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 126 "A205sknchk.sqc"
      sql_setdlist[3].sqldata = (void*)zaicd;
#line 126 "A205sknchk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 126 "A205sknchk.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 126 "A205sknchk.sqc"
      sql_setdlist[4].sqldata = (void*)&krknsgrp;
#line 126 "A205sknchk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 126 "A205sknchk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 129;
#line 126 "A205sknchk.sqc"
      sql_setdlist[5].sqldata = (void*)soukan;
#line 126 "A205sknchk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 126 "A205sknchk.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 126 "A205sknchk.sqc"
      sql_setdlist[6].sqldata = (void*)kaiymd;
#line 126 "A205sknchk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 126 "A205sknchk.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 126 "A205sknchk.sqc"
      sql_setdlist[7].sqldata = (void*)haiymd;
#line 126 "A205sknchk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 126 "A205sknchk.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 126 "A205sknchk.sqc"
      sql_setdlist[8].sqldata = (void*)hnktntid;
#line 126 "A205sknchk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 126 "A205sknchk.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 126 "A205sknchk.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 126 "A205sknchk.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 126 "A205sknchk.sqc"
      sqlasetdata(3,0,10,sql_setdlist,0L,0L);
    }
#line 126 "A205sknchk.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 126 "A205sknchk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 126 "A205sknchk.sqc"
  sqlastop(0L);
}

#line 126 "A205sknchk.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Skchkmst*)ZbmlRealloc( array,
                                    sizeof( Skchkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Skchkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, SkchkmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 141 "A205sknchk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 141 "A205sknchk.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 141 "A205sknchk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 141 "A205sknchk.sqc"
  sqlastop(0L);
}

#line 141 "A205sknchk.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 149 "A205sknchk.sqc"

    return sqlca.sqlcode;
}

long AD205sknchkSelAll( Skchkmst** arrayOut, int* numOut )
{
    Skchkmst*   array = NULL;
    int         num = 0;


    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 159 "A205sknchk.sqc"


    
/*
EXEC SQL DECLARE c3 CURSOR FOR
    SELECT
		KNSGRP,
		KMKCD,
		SSTCD,
		ZAICD,
		KRKNSGRP,
		SOUKAN,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        SKCHKMST
	FOR READ ONLY;
*/

#line 175 "A205sknchk.sqc"


    
/*
EXEC SQL OPEN c3;
*/

{
#line 177 "A205sknchk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 177 "A205sknchk.sqc"
  sqlacall((unsigned short)26,2,0,0,0L);
#line 177 "A205sknchk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 177 "A205sknchk.sqc"
  sqlastop(0L);
}

#line 177 "A205sknchk.sqc"


    while( 1 ) {
        Skchkmst* rec;

        
/*
EXEC SQL FETCH c3 INTO
			:knsgrp,
			:kmkcd,
			:sstcd,
			:zaicd,
			:krknsgrp,
			:soukan,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 192 "A205sknchk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 192 "A205sknchk.sqc"
  sqlaaloc(3,10,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 192 "A205sknchk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 192 "A205sknchk.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 192 "A205sknchk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 192 "A205sknchk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 192 "A205sknchk.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 192 "A205sknchk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 192 "A205sknchk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 192 "A205sknchk.sqc"
      sql_setdlist[2].sqldata = (void*)sstcd;
#line 192 "A205sknchk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 192 "A205sknchk.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 192 "A205sknchk.sqc"
      sql_setdlist[3].sqldata = (void*)zaicd;
#line 192 "A205sknchk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 192 "A205sknchk.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 192 "A205sknchk.sqc"
      sql_setdlist[4].sqldata = (void*)&krknsgrp;
#line 192 "A205sknchk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 192 "A205sknchk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 129;
#line 192 "A205sknchk.sqc"
      sql_setdlist[5].sqldata = (void*)soukan;
#line 192 "A205sknchk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 192 "A205sknchk.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 192 "A205sknchk.sqc"
      sql_setdlist[6].sqldata = (void*)kaiymd;
#line 192 "A205sknchk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 192 "A205sknchk.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 192 "A205sknchk.sqc"
      sql_setdlist[7].sqldata = (void*)haiymd;
#line 192 "A205sknchk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 192 "A205sknchk.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 192 "A205sknchk.sqc"
      sql_setdlist[8].sqldata = (void*)hnktntid;
#line 192 "A205sknchk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 192 "A205sknchk.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 192 "A205sknchk.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 192 "A205sknchk.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 192 "A205sknchk.sqc"
      sqlasetdata(3,0,10,sql_setdlist,0L,0L);
    }
#line 192 "A205sknchk.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 192 "A205sknchk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 192 "A205sknchk.sqc"
  sqlastop(0L);
}

#line 192 "A205sknchk.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Skchkmst*)ZbmlRealloc( array,
                                    sizeof( Skchkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Skchkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, SkchkmstArray );
    }

    
/*
EXEC SQL CLOSE c3;
*/

{
#line 207 "A205sknchk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 207 "A205sknchk.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 207 "A205sknchk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 207 "A205sknchk.sqc"
  sqlastop(0L);
}

#line 207 "A205sknchk.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 215 "A205sknchk.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
