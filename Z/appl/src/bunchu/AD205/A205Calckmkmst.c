static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,118,65,83,86,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,65,50,48,53,67,65,76,67,0,0,0,0,0,0,0,0,
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


#line 1 "A205Calckmkmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Calckmkmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Calckmkmst.h"
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


#line 24 "A205Calckmkmst.sqc"


// DBラップ変数定義

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 27 "A205Calckmkmst.sqc"

	char    knsgrp[17];
	char    kmkcd[8];
	char    sstcd[8];
	char    zaicd[5];
	char    ksnsk[129];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 37 "A205Calckmkmst.sqc"



// DMM定義
#define DMM_STRUCT	Calckmkmst

BmlDMMInfo	CalckmkmstArray2[] = {
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( sstcd ),
	DMM_SSTRING( zaicd ),
	DMM_SSTRING( ksnsk ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

long A205CalckmkmstSelectKey2( Calckmkmst* pKey, Calckmkmst** arrayOut, int* numOut )
{
    Calckmkmst* array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, CalckmkmstArray2 ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 67 "A205Calckmkmst.sqc"


    
/*
EXEC SQL DECLARE c3 CURSOR FOR
    SELECT
		KNSGRP,
		KMKCD,
		SSTCD,
		ZAICD,
		KSNSK,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        CALCKMKMST
    WHERE
		KNSGRP = :knsgrp AND
		KSNSK LIKE :ksnsk AND
--		KAIYMD <= CURRENT DATE 
		KAIYMD <= :kaiymd AND
		HAIYMD >= :kaiymd
		FOR READ ONLY;
*/

#line 88 "A205Calckmkmst.sqc"


    
/*
EXEC SQL OPEN c3;
*/

{
#line 90 "A205Calckmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 90 "A205Calckmkmst.sqc"
  sqlaaloc(2,4,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 90 "A205Calckmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 90 "A205Calckmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 90 "A205Calckmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 90 "A205Calckmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 129;
#line 90 "A205Calckmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)ksnsk;
#line 90 "A205Calckmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 90 "A205Calckmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 90 "A205Calckmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 90 "A205Calckmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 90 "A205Calckmkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 90 "A205Calckmkmst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 90 "A205Calckmkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 90 "A205Calckmkmst.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 90 "A205Calckmkmst.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 90 "A205Calckmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 90 "A205Calckmkmst.sqc"
  sqlastop(0L);
}

#line 90 "A205Calckmkmst.sqc"


    while( 1 ) {
        Calckmkmst* rec;

        
/*
EXEC SQL FETCH c3 INTO
			:knsgrp,
			:kmkcd,
			:sstcd,
			:zaicd,
			:ksnsk,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 104 "A205Calckmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 104 "A205Calckmkmst.sqc"
  sqlaaloc(3,9,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)sstcd;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[3].sqldata = (void*)zaicd;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 129;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[4].sqldata = (void*)ksnsk;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[5].sqldata = (void*)kaiymd;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[6].sqldata = (void*)haiymd;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[7].sqldata = (void*)hnktntid;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 104 "A205Calckmkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 104 "A205Calckmkmst.sqc"
      sqlasetdata(3,0,9,sql_setdlist,0L,0L);
    }
#line 104 "A205Calckmkmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 104 "A205Calckmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 104 "A205Calckmkmst.sqc"
  sqlastop(0L);
}

#line 104 "A205Calckmkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Calckmkmst*)ZbmlRealloc( array,
                                    sizeof( Calckmkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Calckmkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, CalckmkmstArray2 );
    }

    
/*
EXEC SQL CLOSE c3;
*/

{
#line 119 "A205Calckmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 119 "A205Calckmkmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 119 "A205Calckmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 119 "A205Calckmkmst.sqc"
  sqlastop(0L);
}

#line 119 "A205Calckmkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 127 "A205Calckmkmst.sqc"

    return sqlca.sqlcode;
}

