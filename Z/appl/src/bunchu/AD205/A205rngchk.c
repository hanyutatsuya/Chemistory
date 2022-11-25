static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,76,66,54,85,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,65,50,48,53,82,78,71,67,0,0,0,0,0,0,0,0,
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


#line 1 "A205rngchk.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Rngchkmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "A205rngchk.h"
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


#line 23 "A205rngchk.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 28 "A205rngchk.sqc"

	char    hnikbn;
	char    knsgrp[17];
	char    kmkcd[8];
	char    zaicd[5];
	char    sstcd[8];
	char    sbt;
	char    ssa;
	char    zen_kyoyou;
	char    hrng[21];
	char    lrng[21];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 43 "A205rngchk.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Rngchkmst

BmlDMMInfo	RngchkmstArray1[] = {
	DMM_SCHAR( hnikbn ),
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( zaicd ),
	DMM_SSTRING( sstcd ),
	DMM_SCHAR( sbt ),
	DMM_SCHAR( ssa ),
	DMM_SCHAR( zen_kyoyou ),
	DMM_SSTRING( hrng ),
	DMM_SSTRING( lrng ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * A205rngchkSelKey()
 *    RNGCHKMST レコードKey条件取得
 * ■引数
 *    [I]  Rngchkmst* pKey      取得するレコードのキー
 *    [O]  Rngchkmst** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long A205rngchkSelKey( Rngchkmst* pKey, Rngchkmst** arrayOut, int* numOut )
{
    Rngchkmst*  array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, RngchkmstArray1 ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 92 "A205rngchk.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		HNIKBN,
		KNSGRP,
		KMKCD,
		ZAICD,
		SSTCD,
		SBT,
		SSA,
		ZEN_KYOYOU,
		HRNG,
		LRNG,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        RNGCHKMST
    WHERE
		HNIKBN = :hnikbn AND
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		ZAICD = :zaicd AND
		SSTCD = :sstcd AND 
		SBT = :sbt AND
		KAIYMD <= :kaiymd AND 
		HAIYMD >= :kaiymd

		FOR READ ONLY;
*/

#line 122 "A205rngchk.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 124 "A205rngchk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 124 "A205rngchk.sqc"
  sqlaaloc(2,8,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 124 "A205rngchk.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 124 "A205rngchk.sqc"
      sql_setdlist[0].sqldata = (void*)&hnikbn;
#line 124 "A205rngchk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 124 "A205rngchk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 124 "A205rngchk.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 124 "A205rngchk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 124 "A205rngchk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 124 "A205rngchk.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 124 "A205rngchk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 124 "A205rngchk.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 124 "A205rngchk.sqc"
      sql_setdlist[3].sqldata = (void*)zaicd;
#line 124 "A205rngchk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 124 "A205rngchk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 124 "A205rngchk.sqc"
      sql_setdlist[4].sqldata = (void*)sstcd;
#line 124 "A205rngchk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 124 "A205rngchk.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 124 "A205rngchk.sqc"
      sql_setdlist[5].sqldata = (void*)&sbt;
#line 124 "A205rngchk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 124 "A205rngchk.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 124 "A205rngchk.sqc"
      sql_setdlist[6].sqldata = (void*)kaiymd;
#line 124 "A205rngchk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 124 "A205rngchk.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 124 "A205rngchk.sqc"
      sql_setdlist[7].sqldata = (void*)kaiymd;
#line 124 "A205rngchk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 124 "A205rngchk.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 124 "A205rngchk.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 124 "A205rngchk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 124 "A205rngchk.sqc"
  sqlastop(0L);
}

#line 124 "A205rngchk.sqc"


    while( 1 ) {
        Rngchkmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:hnikbn,
			:knsgrp,
			:kmkcd,
			:zaicd,
			:sstcd,
			:sbt,
			:ssa,
			:zen_kyoyou,
			:hrng,
			:lrng,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 143 "A205rngchk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 143 "A205rngchk.sqc"
  sqlaaloc(3,14,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[14];
#line 143 "A205rngchk.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 143 "A205rngchk.sqc"
      sql_setdlist[0].sqldata = (void*)&hnikbn;
#line 143 "A205rngchk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 143 "A205rngchk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 143 "A205rngchk.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 143 "A205rngchk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 143 "A205rngchk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 143 "A205rngchk.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 143 "A205rngchk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 143 "A205rngchk.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 143 "A205rngchk.sqc"
      sql_setdlist[3].sqldata = (void*)zaicd;
#line 143 "A205rngchk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 143 "A205rngchk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 143 "A205rngchk.sqc"
      sql_setdlist[4].sqldata = (void*)sstcd;
#line 143 "A205rngchk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 143 "A205rngchk.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 143 "A205rngchk.sqc"
      sql_setdlist[5].sqldata = (void*)&sbt;
#line 143 "A205rngchk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 143 "A205rngchk.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 143 "A205rngchk.sqc"
      sql_setdlist[6].sqldata = (void*)&ssa;
#line 143 "A205rngchk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 143 "A205rngchk.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 143 "A205rngchk.sqc"
      sql_setdlist[7].sqldata = (void*)&zen_kyoyou;
#line 143 "A205rngchk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 143 "A205rngchk.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 21;
#line 143 "A205rngchk.sqc"
      sql_setdlist[8].sqldata = (void*)hrng;
#line 143 "A205rngchk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 143 "A205rngchk.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 21;
#line 143 "A205rngchk.sqc"
      sql_setdlist[9].sqldata = (void*)lrng;
#line 143 "A205rngchk.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 143 "A205rngchk.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 143 "A205rngchk.sqc"
      sql_setdlist[10].sqldata = (void*)kaiymd;
#line 143 "A205rngchk.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 143 "A205rngchk.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 143 "A205rngchk.sqc"
      sql_setdlist[11].sqldata = (void*)haiymd;
#line 143 "A205rngchk.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 143 "A205rngchk.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 143 "A205rngchk.sqc"
      sql_setdlist[12].sqldata = (void*)hnktntid;
#line 143 "A205rngchk.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 143 "A205rngchk.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 27;
#line 143 "A205rngchk.sqc"
      sql_setdlist[13].sqldata = (void*)ksndh;
#line 143 "A205rngchk.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 143 "A205rngchk.sqc"
      sqlasetdata(3,0,14,sql_setdlist,0L,0L);
    }
#line 143 "A205rngchk.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 143 "A205rngchk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 143 "A205rngchk.sqc"
  sqlastop(0L);
}

#line 143 "A205rngchk.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Rngchkmst*)ZbmlRealloc( array,
                                    sizeof( Rngchkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Rngchkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, RngchkmstArray1 );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 158 "A205rngchk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 158 "A205rngchk.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 158 "A205rngchk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 158 "A205rngchk.sqc"
  sqlastop(0L);
}

#line 158 "A205rngchk.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 166 "A205rngchk.sqc"

    return sqlca.sqlcode;
}

/** End of File *********************************************************/
