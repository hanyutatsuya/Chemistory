static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,105,65,86,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,54,48,90,82,82,75,67,32,0,0,0,0,0,0,0,0,
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


#line 1 "Rrkchkmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Rrkchkmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Rrkchkmst.h"
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


#line 24 "Rrkchkmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Rrkchkmst.sqc"

	char    knsgrp[17];
	char    kmkcd[8];
	char    krnkmk1[8];
	char    krnkmk2[8];
	char    krnkmk3[8];
	char    krnkmk4[8];
	char    krnkmk5[8];
	char    sstcd[8];
	short   week;
	char    sktlow[11];
	char    skthigh[11];
	char    kyukbn;
	char    kyulow[11];
	char    kyuhigh[11];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 48 "Rrkchkmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Rrkchkmst

BmlDMMInfo	RrkchkmstArray[] = {
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( krnkmk1 ),
	DMM_SSTRING( krnkmk2 ),
	DMM_SSTRING( krnkmk3 ),
	DMM_SSTRING( krnkmk4 ),
	DMM_SSTRING( krnkmk5 ),
	DMM_SSTRING( sstcd ),
	DMM_SSHORT( week ),
	DMM_SSTRING( sktlow ),
	DMM_SSTRING( skthigh ),
	DMM_SCHAR( kyukbn ),
	DMM_SSTRING( kyulow ),
	DMM_SSTRING( kyuhigh ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbRrkchkmstSelectAll()
 *    RRKCHKMST レコード全件取得
 * ■引数
 *    [O]  Rrkchkmst** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbRrkchkmstSelectAll( Rrkchkmst** arrayOut, int* numOut )
{
    Rrkchkmst*  array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 94 "Rrkchkmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSGRP,
		KMKCD,
		KRNKMK1,
		KRNKMK2,
		KRNKMK3,
		KRNKMK4,
		KRNKMK5,
		SSTCD,
		WEEK,
		SKTLOW,
		SKTHIGH,
		KYUKBN,
		KYULOW,
		KYUHIGH,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        RRKCHKMST FOR READ ONLY;
*/

#line 117 "Rrkchkmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 119 "Rrkchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 119 "Rrkchkmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 119 "Rrkchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 119 "Rrkchkmst.sqc"
  sqlastop(0L);
}

#line 119 "Rrkchkmst.sqc"


    while( 1 ) {
        Rrkchkmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knsgrp,
			:kmkcd,
			:krnkmk1,
			:krnkmk2,
			:krnkmk3,
			:krnkmk4,
			:krnkmk5,
			:sstcd,
			:week,
			:sktlow,
			:skthigh,
			:kyukbn,
			:kyulow,
			:kyuhigh,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 142 "Rrkchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 142 "Rrkchkmst.sqc"
  sqlaaloc(3,18,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[18];
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)krnkmk1;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[3].sqldata = (void*)krnkmk2;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[4].sqldata = (void*)krnkmk3;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[5].sqldata = (void*)krnkmk4;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[6].sqldata = (void*)krnkmk5;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 8;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[7].sqldata = (void*)sstcd;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[8].sqldata = (void*)&week;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[9].sqldata = (void*)sktlow;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[10].sqldata = (void*)skthigh;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[11].sqldata = (void*)&kyukbn;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[12].sqldata = (void*)kyulow;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[13].sqldata = (void*)kyuhigh;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 11;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[14].sqldata = (void*)kaiymd;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 11;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[15].sqldata = (void*)haiymd;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 9;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[16].sqldata = (void*)hnktntid;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[17].sqldata = (void*)ksndh;
#line 142 "Rrkchkmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 142 "Rrkchkmst.sqc"
      sqlasetdata(3,0,18,sql_setdlist,0L,0L);
    }
#line 142 "Rrkchkmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 142 "Rrkchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 142 "Rrkchkmst.sqc"
  sqlastop(0L);
}

#line 142 "Rrkchkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Rrkchkmst*)ZbmlRealloc( array,
                                    sizeof( Rrkchkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Rrkchkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, RrkchkmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 157 "Rrkchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 157 "Rrkchkmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 157 "Rrkchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 157 "Rrkchkmst.sqc"
  sqlastop(0L);
}

#line 157 "Rrkchkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 165 "Rrkchkmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbRrkchkmstSelectKey()
 *    RRKCHKMST レコードKey条件取得
 * ■引数
 *    [I]  Rrkchkmst* pKey      取得するレコードのキー
 *    [O]  Rrkchkmst** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbRrkchkmstSelectKey( Rrkchkmst* pKey, Rrkchkmst** arrayOut, int* numOut )
{
    Rrkchkmst*  array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, RrkchkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 191 "Rrkchkmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSGRP,
		KMKCD,
		KRNKMK1,
		KRNKMK2,
		KRNKMK3,
		KRNKMK4,
		KRNKMK5,
		SSTCD,
		WEEK,
		SKTLOW,
		SKTHIGH,
		KYUKBN,
		KYULOW,
		KYUHIGH,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        RRKCHKMST
    WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		SSTCD = :sstcd AND
		WEEK = :week AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 220 "Rrkchkmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 222 "Rrkchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 222 "Rrkchkmst.sqc"
  sqlaaloc(2,5,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 222 "Rrkchkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 222 "Rrkchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 222 "Rrkchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 222 "Rrkchkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 222 "Rrkchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 222 "Rrkchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 222 "Rrkchkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 222 "Rrkchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)sstcd;
#line 222 "Rrkchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 222 "Rrkchkmst.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 222 "Rrkchkmst.sqc"
      sql_setdlist[3].sqldata = (void*)&week;
#line 222 "Rrkchkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 222 "Rrkchkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 222 "Rrkchkmst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 222 "Rrkchkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 222 "Rrkchkmst.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 222 "Rrkchkmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 222 "Rrkchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 222 "Rrkchkmst.sqc"
  sqlastop(0L);
}

#line 222 "Rrkchkmst.sqc"


    while( 1 ) {
        Rrkchkmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knsgrp,
			:kmkcd,
			:krnkmk1,
			:krnkmk2,
			:krnkmk3,
			:krnkmk4,
			:krnkmk5,
			:sstcd,
			:week,
			:sktlow,
			:skthigh,
			:kyukbn,
			:kyulow,
			:kyuhigh,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 245 "Rrkchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 245 "Rrkchkmst.sqc"
  sqlaaloc(3,18,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[18];
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)krnkmk1;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[3].sqldata = (void*)krnkmk2;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[4].sqldata = (void*)krnkmk3;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[5].sqldata = (void*)krnkmk4;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[6].sqldata = (void*)krnkmk5;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 8;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[7].sqldata = (void*)sstcd;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[8].sqldata = (void*)&week;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[9].sqldata = (void*)sktlow;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[10].sqldata = (void*)skthigh;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[11].sqldata = (void*)&kyukbn;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[12].sqldata = (void*)kyulow;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[13].sqldata = (void*)kyuhigh;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 11;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[14].sqldata = (void*)kaiymd;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 11;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[15].sqldata = (void*)haiymd;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 9;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[16].sqldata = (void*)hnktntid;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[17].sqldata = (void*)ksndh;
#line 245 "Rrkchkmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 245 "Rrkchkmst.sqc"
      sqlasetdata(3,0,18,sql_setdlist,0L,0L);
    }
#line 245 "Rrkchkmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 245 "Rrkchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 245 "Rrkchkmst.sqc"
  sqlastop(0L);
}

#line 245 "Rrkchkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Rrkchkmst*)ZbmlRealloc( array,
                                    sizeof( Rrkchkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Rrkchkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, RrkchkmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 260 "Rrkchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 260 "Rrkchkmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 260 "Rrkchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 260 "Rrkchkmst.sqc"
  sqlastop(0L);
}

#line 260 "Rrkchkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 268 "Rrkchkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbRrkchkmstInsert()
 *    RRKCHKMST レコードを挿入する
 * ■引数
 *    [I]  Rrkchkmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbRrkchkmstInsert( Rrkchkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, RrkchkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 291 "Rrkchkmst.sqc"


    
/*
EXEC SQL INSERT INTO RRKCHKMST
    (
		KNSGRP,
		KMKCD,
		KRNKMK1,
		KRNKMK2,
		KRNKMK3,
		KRNKMK4,
		KRNKMK5,
		SSTCD,
		WEEK,
		SKTLOW,
		SKTHIGH,
		KYUKBN,
		KYULOW,
		KYUHIGH,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:knsgrp,
		:kmkcd,
		:krnkmk1,
		:krnkmk2,
		:krnkmk3,
		:krnkmk4,
		:krnkmk5,
		:sstcd,
		:week,
		:sktlow,
		:skthigh,
		:kyukbn,
		:kyulow,
		:kyuhigh,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 332 "Rrkchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 332 "Rrkchkmst.sqc"
  sqlaaloc(2,18,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[18];
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)krnkmk1;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[3].sqldata = (void*)krnkmk2;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[4].sqldata = (void*)krnkmk3;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[5].sqldata = (void*)krnkmk4;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[6].sqldata = (void*)krnkmk5;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 8;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[7].sqldata = (void*)sstcd;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[8].sqldata = (void*)&week;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[9].sqldata = (void*)sktlow;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[10].sqldata = (void*)skthigh;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[11].sqldata = (void*)&kyukbn;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[12].sqldata = (void*)kyulow;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[13].sqldata = (void*)kyuhigh;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 11;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[14].sqldata = (void*)kaiymd;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 11;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[15].sqldata = (void*)haiymd;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 9;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[16].sqldata = (void*)hnktntid;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[17].sqldata = (void*)ksndh;
#line 332 "Rrkchkmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 332 "Rrkchkmst.sqc"
      sqlasetdata(2,0,18,sql_setdlist,0L,0L);
    }
#line 332 "Rrkchkmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 332 "Rrkchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 332 "Rrkchkmst.sqc"
  sqlastop(0L);
}

#line 332 "Rrkchkmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 337 "Rrkchkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbRrkchkmstUpdate()
 *    RRKCHKMST レコードを更新する
 * ■引数
 *    [I]  Rrkchkmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbRrkchkmstUpdate( Rrkchkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, RrkchkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 361 "Rrkchkmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 362 "Rrkchkmst.sqc"


    
/*
EXEC SQL UPDATE RRKCHKMST
    SET (
		KRNKMK1,
		KRNKMK2,
		KRNKMK3,
		KRNKMK4,
		KRNKMK5,
		SKTLOW,
		SKTHIGH,
		KYUKBN,
		KYULOW,
		KYUHIGH,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:krnkmk1,
		:krnkmk2,
		:krnkmk3,
		:krnkmk4,
		:krnkmk5,
		:sktlow,
		:skthigh,
		:kyukbn,
		:kyulow,
		:kyuhigh,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		SSTCD = :sstcd AND
		WEEK = :week AND
		KAIYMD = :kaiymd;
*/

{
#line 398 "Rrkchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 398 "Rrkchkmst.sqc"
  sqlaaloc(2,18,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[18];
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)krnkmk1;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)krnkmk2;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)krnkmk3;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[3].sqldata = (void*)krnkmk4;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[4].sqldata = (void*)krnkmk5;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[5].sqldata = (void*)sktlow;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[6].sqldata = (void*)skthigh;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[7].sqldata = (void*)&kyukbn;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[8].sqldata = (void*)kyulow;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[9].sqldata = (void*)kyuhigh;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[10].sqldata = (void*)haiymd;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[11].sqldata = (void*)hnktntid;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 27;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[12].sqldata = (void*)ksndh;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 17;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[13].sqldata = (void*)knsgrp;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 8;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[14].sqldata = (void*)kmkcd;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[15].sqldata = (void*)sstcd;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[16].sqltype = 500; sql_setdlist[16].sqllen = 2;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[16].sqldata = (void*)&week;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 11;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[17].sqldata = (void*)kaiymd;
#line 398 "Rrkchkmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 398 "Rrkchkmst.sqc"
      sqlasetdata(2,0,18,sql_setdlist,0L,0L);
    }
#line 398 "Rrkchkmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 398 "Rrkchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 398 "Rrkchkmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 398 "Rrkchkmst.sqc"
  sqlastop(0L);
}

#line 398 "Rrkchkmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 403 "Rrkchkmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 407 "Rrkchkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbRrkchkmstDelete()
 *    RRKCHKMST レコードを削除する
 * ■引数
 *    [I]  Rrkchkmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbRrkchkmstDelete( Rrkchkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, RrkchkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 431 "Rrkchkmst.sqc"


    
/*
EXEC SQL DELETE FROM RRKCHKMST
    WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		SSTCD = :sstcd AND
		WEEK = :week AND
		KAIYMD = :kaiymd;
*/

{
#line 439 "Rrkchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 439 "Rrkchkmst.sqc"
  sqlaaloc(2,5,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 439 "Rrkchkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 439 "Rrkchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 439 "Rrkchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 439 "Rrkchkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 439 "Rrkchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 439 "Rrkchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 439 "Rrkchkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 439 "Rrkchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)sstcd;
#line 439 "Rrkchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 439 "Rrkchkmst.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 439 "Rrkchkmst.sqc"
      sql_setdlist[3].sqldata = (void*)&week;
#line 439 "Rrkchkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 439 "Rrkchkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 439 "Rrkchkmst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 439 "Rrkchkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 439 "Rrkchkmst.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 439 "Rrkchkmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 439 "Rrkchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 439 "Rrkchkmst.sqc"
  sqlastop(0L);
}

#line 439 "Rrkchkmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 444 "Rrkchkmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
