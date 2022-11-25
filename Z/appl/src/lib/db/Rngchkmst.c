static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,97,65,86,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,53,57,90,82,78,71,67,32,0,0,0,0,0,0,0,0,
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


#line 1 "Rngchkmst.sqc"
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

#include "Rngchkmst.h"
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


#line 24 "Rngchkmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Rngchkmst.sqc"

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

#line 44 "Rngchkmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Rngchkmst

BmlDMMInfo	RngchkmstArray[] = {
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
 * ZdbRngchkmstSelectAll()
 *    RNGCHKMST レコード全件取得
 * ■引数
 *    [O]  Rngchkmst** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbRngchkmstSelectAll( Rngchkmst** arrayOut, int* numOut )
{
    Rngchkmst*  array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 86 "Rngchkmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
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
        RNGCHKMST FOR READ ONLY;
*/

#line 105 "Rngchkmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 107 "Rngchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 107 "Rngchkmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 107 "Rngchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 107 "Rngchkmst.sqc"
  sqlastop(0L);
}

#line 107 "Rngchkmst.sqc"


    while( 1 ) {
        Rngchkmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
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
#line 126 "Rngchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 126 "Rngchkmst.sqc"
  sqlaaloc(3,14,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[14];
#line 126 "Rngchkmst.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)&hnikbn;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[3].sqldata = (void*)zaicd;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[4].sqldata = (void*)sstcd;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[5].sqldata = (void*)&sbt;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[6].sqldata = (void*)&ssa;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[7].sqldata = (void*)&zen_kyoyou;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 21;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[8].sqldata = (void*)hrng;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 21;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[9].sqldata = (void*)lrng;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[10].sqldata = (void*)kaiymd;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[11].sqldata = (void*)haiymd;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[12].sqldata = (void*)hnktntid;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 27;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[13].sqldata = (void*)ksndh;
#line 126 "Rngchkmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 126 "Rngchkmst.sqc"
      sqlasetdata(3,0,14,sql_setdlist,0L,0L);
    }
#line 126 "Rngchkmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 126 "Rngchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 126 "Rngchkmst.sqc"
  sqlastop(0L);
}

#line 126 "Rngchkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Rngchkmst*)ZbmlRealloc( array,
                                    sizeof( Rngchkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Rngchkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, RngchkmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 141 "Rngchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 141 "Rngchkmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 141 "Rngchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 141 "Rngchkmst.sqc"
  sqlastop(0L);
}

#line 141 "Rngchkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 149 "Rngchkmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbRngchkmstSelectKey()
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
long ZdbRngchkmstSelectKey( Rngchkmst* pKey, Rngchkmst** arrayOut, int* numOut )
{
    Rngchkmst*  array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, RngchkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 175 "Rngchkmst.sqc"


    
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
		SSA           = :ssa           AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 203 "Rngchkmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 205 "Rngchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 205 "Rngchkmst.sqc"
  sqlaaloc(2,8,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 205 "Rngchkmst.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 205 "Rngchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)&hnikbn;
#line 205 "Rngchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 205 "Rngchkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 205 "Rngchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 205 "Rngchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 205 "Rngchkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 205 "Rngchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 205 "Rngchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 205 "Rngchkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 205 "Rngchkmst.sqc"
      sql_setdlist[3].sqldata = (void*)zaicd;
#line 205 "Rngchkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 205 "Rngchkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 205 "Rngchkmst.sqc"
      sql_setdlist[4].sqldata = (void*)sstcd;
#line 205 "Rngchkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 205 "Rngchkmst.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 205 "Rngchkmst.sqc"
      sql_setdlist[5].sqldata = (void*)&sbt;
#line 205 "Rngchkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 205 "Rngchkmst.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 205 "Rngchkmst.sqc"
      sql_setdlist[6].sqldata = (void*)&ssa;
#line 205 "Rngchkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 205 "Rngchkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 205 "Rngchkmst.sqc"
      sql_setdlist[7].sqldata = (void*)kaiymd;
#line 205 "Rngchkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 205 "Rngchkmst.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 205 "Rngchkmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 205 "Rngchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 205 "Rngchkmst.sqc"
  sqlastop(0L);
}

#line 205 "Rngchkmst.sqc"


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
#line 224 "Rngchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 224 "Rngchkmst.sqc"
  sqlaaloc(3,14,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[14];
#line 224 "Rngchkmst.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)&hnikbn;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[3].sqldata = (void*)zaicd;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[4].sqldata = (void*)sstcd;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[5].sqldata = (void*)&sbt;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[6].sqldata = (void*)&ssa;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[7].sqldata = (void*)&zen_kyoyou;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 21;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[8].sqldata = (void*)hrng;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 21;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[9].sqldata = (void*)lrng;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[10].sqldata = (void*)kaiymd;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[11].sqldata = (void*)haiymd;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[12].sqldata = (void*)hnktntid;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 27;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[13].sqldata = (void*)ksndh;
#line 224 "Rngchkmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 224 "Rngchkmst.sqc"
      sqlasetdata(3,0,14,sql_setdlist,0L,0L);
    }
#line 224 "Rngchkmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 224 "Rngchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 224 "Rngchkmst.sqc"
  sqlastop(0L);
}

#line 224 "Rngchkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Rngchkmst*)ZbmlRealloc( array,
                                    sizeof( Rngchkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Rngchkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, RngchkmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 239 "Rngchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 239 "Rngchkmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 239 "Rngchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 239 "Rngchkmst.sqc"
  sqlastop(0L);
}

#line 239 "Rngchkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 247 "Rngchkmst.sqc"

    return sqlca.sqlcode;
}
long ZdbRngchkmstSelectKey2( Rngchkmst* pKey, Rngchkmst** arrayOut, int* numOut )
{
    Rngchkmst*  array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, RngchkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 261 "Rngchkmst.sqc"


    
/*
EXEC SQL DECLARE c3 CURSOR FOR
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
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		ZAICD = :zaicd AND
		SSTCD = :sstcd AND
		SBT = :sbt AND
		KAIYMD <= CURRENT DATE FOR READ ONLY;
*/

#line 287 "Rngchkmst.sqc"


    
/*
EXEC SQL OPEN c3;
*/

{
#line 289 "Rngchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 289 "Rngchkmst.sqc"
  sqlaaloc(2,5,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 289 "Rngchkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 289 "Rngchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 289 "Rngchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 289 "Rngchkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 289 "Rngchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 289 "Rngchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 289 "Rngchkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 289 "Rngchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)zaicd;
#line 289 "Rngchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 289 "Rngchkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 289 "Rngchkmst.sqc"
      sql_setdlist[3].sqldata = (void*)sstcd;
#line 289 "Rngchkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 289 "Rngchkmst.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 289 "Rngchkmst.sqc"
      sql_setdlist[4].sqldata = (void*)&sbt;
#line 289 "Rngchkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 289 "Rngchkmst.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 289 "Rngchkmst.sqc"
  sqlacall((unsigned short)26,3,2,0,0L);
#line 289 "Rngchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 289 "Rngchkmst.sqc"
  sqlastop(0L);
}

#line 289 "Rngchkmst.sqc"


    while( 1 ) {
        Rngchkmst* rec;

        
/*
EXEC SQL FETCH c3 INTO
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
#line 308 "Rngchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 308 "Rngchkmst.sqc"
  sqlaaloc(3,14,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[14];
#line 308 "Rngchkmst.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)&hnikbn;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[3].sqldata = (void*)zaicd;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[4].sqldata = (void*)sstcd;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[5].sqldata = (void*)&sbt;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[6].sqldata = (void*)&ssa;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[7].sqldata = (void*)&zen_kyoyou;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 21;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[8].sqldata = (void*)hrng;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 21;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[9].sqldata = (void*)lrng;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[10].sqldata = (void*)kaiymd;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[11].sqldata = (void*)haiymd;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[12].sqldata = (void*)hnktntid;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 27;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[13].sqldata = (void*)ksndh;
#line 308 "Rngchkmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 308 "Rngchkmst.sqc"
      sqlasetdata(3,0,14,sql_setdlist,0L,0L);
    }
#line 308 "Rngchkmst.sqc"
  sqlacall((unsigned short)25,3,0,3,0L);
#line 308 "Rngchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 308 "Rngchkmst.sqc"
  sqlastop(0L);
}

#line 308 "Rngchkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Rngchkmst*)ZbmlRealloc( array,
                                    sizeof( Rngchkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Rngchkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, RngchkmstArray );
    }

    
/*
EXEC SQL CLOSE c3;
*/

{
#line 323 "Rngchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 323 "Rngchkmst.sqc"
  sqlacall((unsigned short)20,3,0,0,0L);
#line 323 "Rngchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 323 "Rngchkmst.sqc"
  sqlastop(0L);
}

#line 323 "Rngchkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 331 "Rngchkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbRngchkmstInsert()
 *    RNGCHKMST レコードを挿入する
 * ■引数
 *    [I]  Rngchkmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbRngchkmstInsert( Rngchkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, RngchkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 354 "Rngchkmst.sqc"


    
/*
EXEC SQL INSERT INTO RNGCHKMST
    (
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
    ) VALUES (
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
		:ksndh
    );
*/

{
#line 387 "Rngchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 387 "Rngchkmst.sqc"
  sqlaaloc(2,14,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[14];
#line 387 "Rngchkmst.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)&hnikbn;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[3].sqldata = (void*)zaicd;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[4].sqldata = (void*)sstcd;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[5].sqldata = (void*)&sbt;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[6].sqldata = (void*)&ssa;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[7].sqldata = (void*)&zen_kyoyou;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 21;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[8].sqldata = (void*)hrng;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 21;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[9].sqldata = (void*)lrng;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[10].sqldata = (void*)kaiymd;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[11].sqldata = (void*)haiymd;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[12].sqldata = (void*)hnktntid;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 27;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[13].sqldata = (void*)ksndh;
#line 387 "Rngchkmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 387 "Rngchkmst.sqc"
      sqlasetdata(2,0,14,sql_setdlist,0L,0L);
    }
#line 387 "Rngchkmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 387 "Rngchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 387 "Rngchkmst.sqc"
  sqlastop(0L);
}

#line 387 "Rngchkmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 392 "Rngchkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbRngchkmstUpdate()
 *    RNGCHKMST レコードを更新する
 * ■引数
 *    [I]  Rngchkmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbRngchkmstUpdate( Rngchkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, RngchkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 416 "Rngchkmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 417 "Rngchkmst.sqc"


    
/*
EXEC SQL UPDATE RNGCHKMST
    SET (
		ZEN_KYOYOU,
		HRNG,
		LRNG,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:zen_kyoyou,
		:hrng,
		:lrng,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		HNIKBN = :hnikbn AND
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		ZAICD = :zaicd AND
		SSTCD = :sstcd AND
		SBT = :sbt AND
		SSA           = :ssa           AND
		KAIYMD = :kaiymd;
*/

{
#line 442 "Rngchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 442 "Rngchkmst.sqc"
  sqlaaloc(2,14,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[14];
#line 442 "Rngchkmst.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)&zen_kyoyou;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)hrng;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)lrng;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[3].sqldata = (void*)haiymd;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 9;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[4].sqldata = (void*)hnktntid;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 27;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[5].sqldata = (void*)ksndh;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[6].sqldata = (void*)&hnikbn;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 17;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[7].sqldata = (void*)knsgrp;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 8;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[8].sqldata = (void*)kmkcd;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 5;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[9].sqldata = (void*)zaicd;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 8;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[10].sqldata = (void*)sstcd;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[11].sqldata = (void*)&sbt;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[12].sqltype = 452; sql_setdlist[12].sqllen = 1;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[12].sqldata = (void*)&ssa;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[13].sqldata = (void*)kaiymd;
#line 442 "Rngchkmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 442 "Rngchkmst.sqc"
      sqlasetdata(2,0,14,sql_setdlist,0L,0L);
    }
#line 442 "Rngchkmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 442 "Rngchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 442 "Rngchkmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 442 "Rngchkmst.sqc"
  sqlastop(0L);
}

#line 442 "Rngchkmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 447 "Rngchkmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 451 "Rngchkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbRngchkmstDelete()
 *    RNGCHKMST レコードを削除する
 * ■引数
 *    [I]  Rngchkmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbRngchkmstDelete( Rngchkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, RngchkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 475 "Rngchkmst.sqc"


    
/*
EXEC SQL DELETE FROM RNGCHKMST
    WHERE
		HNIKBN = :hnikbn AND
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		ZAICD = :zaicd AND
		SSTCD = :sstcd AND
		SBT = :sbt AND
		SSA           = :ssa           AND
		KAIYMD = :kaiymd;
*/

{
#line 486 "Rngchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 486 "Rngchkmst.sqc"
  sqlaaloc(2,8,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 486 "Rngchkmst.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 486 "Rngchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)&hnikbn;
#line 486 "Rngchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 486 "Rngchkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 486 "Rngchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 486 "Rngchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 486 "Rngchkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 486 "Rngchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 486 "Rngchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 486 "Rngchkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 486 "Rngchkmst.sqc"
      sql_setdlist[3].sqldata = (void*)zaicd;
#line 486 "Rngchkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 486 "Rngchkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 486 "Rngchkmst.sqc"
      sql_setdlist[4].sqldata = (void*)sstcd;
#line 486 "Rngchkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 486 "Rngchkmst.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 486 "Rngchkmst.sqc"
      sql_setdlist[5].sqldata = (void*)&sbt;
#line 486 "Rngchkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 486 "Rngchkmst.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 486 "Rngchkmst.sqc"
      sql_setdlist[6].sqldata = (void*)&ssa;
#line 486 "Rngchkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 486 "Rngchkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 486 "Rngchkmst.sqc"
      sql_setdlist[7].sqldata = (void*)kaiymd;
#line 486 "Rngchkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 486 "Rngchkmst.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 486 "Rngchkmst.sqc"
  sqlacall((unsigned short)24,6,2,0,0L);
#line 486 "Rngchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 486 "Rngchkmst.sqc"
  sqlastop(0L);
}

#line 486 "Rngchkmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 491 "Rngchkmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
