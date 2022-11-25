static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,118,65,84,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,51,56,90,75,77,75,66,32,0,0,0,0,0,0,0,0,
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


#line 1 "Kmkbtutest.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Kmkbtutest.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Kmkbtutest.h"
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


#line 24 "Kmkbtutest.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Kmkbtutest.sqc"

	char    knskisymd[11];
	char    knsgrp[17];
	char    kmkcd[8];
	sqlint32  iriallsu;
	sqlint32  irijsnsu;
	sqlint32  kensasu;
	sqlint32  stadsu;
	sqlint32  ctrlsu;
	sqlint32  testsu;
	sqlint32  savysu;
	sqlint32  kbrtsu;
	sqlint32  kstatsu;
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 43 "Kmkbtutest.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Kmkbtutest

BmlDMMInfo	KmkbtutestArray[] = {
	DMM_SDATE( knskisymd ),
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SLONG( iriallsu ),
	DMM_SLONG( irijsnsu ),
	DMM_SLONG( kensasu ),
	DMM_SLONG( stadsu ),
	DMM_SLONG( ctrlsu ),
	DMM_SLONG( testsu ),
	DMM_SLONG( savysu ),
	DMM_SLONG( kbrtsu ),
	DMM_SLONG( kstatsu ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKmkbtutestSelectAll()
 *    KMKBTUTEST レコード全件取得
 * ■引数
 *    [O]  Kmkbtutest** arrayOu 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKmkbtutestSelectAll( Kmkbtutest** arrayOut, int* numOut )
{
    Kmkbtutest* array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 84 "Kmkbtutest.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSKISYMD,
		KNSGRP,
		KMKCD,
		IRIALLSU,
		IRIJSNSU,
		KENSASU,
		STADSU,
		CTRLSU,
		TESTSU,
		SAVYSU,
		KBRTSU,
		KSTATSU,
		KSNDH
    FROM
        KMKBTUTEST FOR READ ONLY;
*/

#line 102 "Kmkbtutest.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 104 "Kmkbtutest.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 104 "Kmkbtutest.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 104 "Kmkbtutest.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 104 "Kmkbtutest.sqc"
  sqlastop(0L);
}

#line 104 "Kmkbtutest.sqc"


    while( 1 ) {
        Kmkbtutest* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knskisymd,
			:knsgrp,
			:kmkcd,
			:iriallsu,
			:irijsnsu,
			:kensasu,
			:stadsu,
			:ctrlsu,
			:testsu,
			:savysu,
			:kbrtsu,
			:kstatsu,
			:ksndh;
*/

{
#line 122 "Kmkbtutest.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 122 "Kmkbtutest.sqc"
  sqlaaloc(3,13,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[13];
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[3].sqldata = (void*)&iriallsu;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[4].sqldata = (void*)&irijsnsu;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[5].sqldata = (void*)&kensasu;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[6].sqldata = (void*)&stadsu;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[7].sqldata = (void*)&ctrlsu;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[8].sqldata = (void*)&testsu;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[9].sqldata = (void*)&savysu;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[10].sqltype = 496; sql_setdlist[10].sqllen = 4;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[10].sqldata = (void*)&kbrtsu;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[11].sqldata = (void*)&kstatsu;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 27;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[12].sqldata = (void*)ksndh;
#line 122 "Kmkbtutest.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 122 "Kmkbtutest.sqc"
      sqlasetdata(3,0,13,sql_setdlist,0L,0L);
    }
#line 122 "Kmkbtutest.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 122 "Kmkbtutest.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 122 "Kmkbtutest.sqc"
  sqlastop(0L);
}

#line 122 "Kmkbtutest.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kmkbtutest*)ZbmlRealloc( array,
                                    sizeof( Kmkbtutest ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kmkbtutest ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KmkbtutestArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 137 "Kmkbtutest.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 137 "Kmkbtutest.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 137 "Kmkbtutest.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 137 "Kmkbtutest.sqc"
  sqlastop(0L);
}

#line 137 "Kmkbtutest.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 145 "Kmkbtutest.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKmkbtutestSelectKey()
 *    KMKBTUTEST レコードKey条件取得
 * ■引数
 *    [I]  Kmkbtutest* pKey     取得するレコードのキー
 *    [O]  Kmkbtutest** arrayOu 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKmkbtutestSelectKey( Kmkbtutest* pKey, Kmkbtutest** arrayOut, int* numOut )
{
    Kmkbtutest* array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KmkbtutestArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 171 "Kmkbtutest.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSKISYMD,
		KNSGRP,
		KMKCD,
		IRIALLSU,
		IRIJSNSU,
		KENSASU,
		STADSU,
		CTRLSU,
		TESTSU,
		SAVYSU,
		KBRTSU,
		KSTATSU,
		KSNDH
    FROM
        KMKBTUTEST
    WHERE
		KNSKISYMD = :knskisymd AND
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd FOR READ ONLY;
*/

#line 193 "Kmkbtutest.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 195 "Kmkbtutest.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 195 "Kmkbtutest.sqc"
  sqlaaloc(2,3,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 195 "Kmkbtutest.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 195 "Kmkbtutest.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 195 "Kmkbtutest.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 195 "Kmkbtutest.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 195 "Kmkbtutest.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 195 "Kmkbtutest.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 195 "Kmkbtutest.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 195 "Kmkbtutest.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 195 "Kmkbtutest.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 195 "Kmkbtutest.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 195 "Kmkbtutest.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 195 "Kmkbtutest.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 195 "Kmkbtutest.sqc"
  sqlastop(0L);
}

#line 195 "Kmkbtutest.sqc"


    while( 1 ) {
        Kmkbtutest* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knskisymd,
			:knsgrp,
			:kmkcd,
			:iriallsu,
			:irijsnsu,
			:kensasu,
			:stadsu,
			:ctrlsu,
			:testsu,
			:savysu,
			:kbrtsu,
			:kstatsu,
			:ksndh;
*/

{
#line 213 "Kmkbtutest.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 213 "Kmkbtutest.sqc"
  sqlaaloc(3,13,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[13];
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[3].sqldata = (void*)&iriallsu;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[4].sqldata = (void*)&irijsnsu;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[5].sqldata = (void*)&kensasu;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[6].sqldata = (void*)&stadsu;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[7].sqldata = (void*)&ctrlsu;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[8].sqldata = (void*)&testsu;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[9].sqldata = (void*)&savysu;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[10].sqltype = 496; sql_setdlist[10].sqllen = 4;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[10].sqldata = (void*)&kbrtsu;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[11].sqldata = (void*)&kstatsu;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 27;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[12].sqldata = (void*)ksndh;
#line 213 "Kmkbtutest.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 213 "Kmkbtutest.sqc"
      sqlasetdata(3,0,13,sql_setdlist,0L,0L);
    }
#line 213 "Kmkbtutest.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 213 "Kmkbtutest.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 213 "Kmkbtutest.sqc"
  sqlastop(0L);
}

#line 213 "Kmkbtutest.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kmkbtutest*)ZbmlRealloc( array,
                                    sizeof( Kmkbtutest ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kmkbtutest ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KmkbtutestArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 228 "Kmkbtutest.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 228 "Kmkbtutest.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 228 "Kmkbtutest.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 228 "Kmkbtutest.sqc"
  sqlastop(0L);
}

#line 228 "Kmkbtutest.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 236 "Kmkbtutest.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKmkbtutestInsert()
 *    KMKBTUTEST レコードを挿入する
 * ■引数
 *    [I]  Kmkbtutest* rec      挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKmkbtutestInsert( Kmkbtutest* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KmkbtutestArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 259 "Kmkbtutest.sqc"


    
/*
EXEC SQL INSERT INTO KMKBTUTEST
    (
		KNSKISYMD,
		KNSGRP,
		KMKCD,
		IRIALLSU,
		IRIJSNSU,
		KENSASU,
		STADSU,
		CTRLSU,
		TESTSU,
		SAVYSU,
		KBRTSU,
		KSTATSU,
		KSNDH
    ) VALUES (
		:knskisymd,
		:knsgrp,
		:kmkcd,
		:iriallsu,
		:irijsnsu,
		:kensasu,
		:stadsu,
		:ctrlsu,
		:testsu,
		:savysu,
		:kbrtsu,
		:kstatsu,
		:ksndh
    );
*/

{
#line 290 "Kmkbtutest.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 290 "Kmkbtutest.sqc"
  sqlaaloc(2,13,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[13];
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[3].sqldata = (void*)&iriallsu;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[4].sqldata = (void*)&irijsnsu;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[5].sqldata = (void*)&kensasu;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[6].sqldata = (void*)&stadsu;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[7].sqldata = (void*)&ctrlsu;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[8].sqldata = (void*)&testsu;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[9].sqldata = (void*)&savysu;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[10].sqltype = 496; sql_setdlist[10].sqllen = 4;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[10].sqldata = (void*)&kbrtsu;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[11].sqldata = (void*)&kstatsu;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 27;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[12].sqldata = (void*)ksndh;
#line 290 "Kmkbtutest.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 290 "Kmkbtutest.sqc"
      sqlasetdata(2,0,13,sql_setdlist,0L,0L);
    }
#line 290 "Kmkbtutest.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 290 "Kmkbtutest.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 290 "Kmkbtutest.sqc"
  sqlastop(0L);
}

#line 290 "Kmkbtutest.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 295 "Kmkbtutest.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKmkbtutestUpdate()
 *    KMKBTUTEST レコードを更新する
 * ■引数
 *    [I]  Kmkbtutest* rec      更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKmkbtutestUpdate( Kmkbtutest* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KmkbtutestArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 319 "Kmkbtutest.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 320 "Kmkbtutest.sqc"


    
/*
EXEC SQL UPDATE KMKBTUTEST
    SET (
		IRIALLSU,
		IRIJSNSU,
		KENSASU,
		STADSU,
		CTRLSU,
		TESTSU,
		SAVYSU,
		KBRTSU,
		KSTATSU,
		KSNDH
    ) = (
		:iriallsu,
		:irijsnsu,
		:kensasu,
		:stadsu,
		:ctrlsu,
		:testsu,
		:savysu,
		:kbrtsu,
		:kstatsu,
		:ksndh
    ) WHERE
		KNSKISYMD = :knskisymd AND
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd;
*/

{
#line 348 "Kmkbtutest.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 348 "Kmkbtutest.sqc"
  sqlaaloc(2,13,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[13];
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[0].sqldata = (void*)&iriallsu;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[1].sqldata = (void*)&irijsnsu;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[2].sqldata = (void*)&kensasu;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[3].sqldata = (void*)&stadsu;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[4].sqldata = (void*)&ctrlsu;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[5].sqldata = (void*)&testsu;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[6].sqldata = (void*)&savysu;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[7].sqldata = (void*)&kbrtsu;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[8].sqldata = (void*)&kstatsu;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[10].sqldata = (void*)knskisymd;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 17;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[11].sqldata = (void*)knsgrp;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 8;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[12].sqldata = (void*)kmkcd;
#line 348 "Kmkbtutest.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 348 "Kmkbtutest.sqc"
      sqlasetdata(2,0,13,sql_setdlist,0L,0L);
    }
#line 348 "Kmkbtutest.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 348 "Kmkbtutest.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 348 "Kmkbtutest.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 348 "Kmkbtutest.sqc"
  sqlastop(0L);
}

#line 348 "Kmkbtutest.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 353 "Kmkbtutest.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 357 "Kmkbtutest.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKmkbtutestDelete()
 *    KMKBTUTEST レコードを削除する
 * ■引数
 *    [I]  Kmkbtutest* rec      削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKmkbtutestDelete( Kmkbtutest* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KmkbtutestArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 381 "Kmkbtutest.sqc"


    
/*
EXEC SQL DELETE FROM KMKBTUTEST
    WHERE
		KNSKISYMD = :knskisymd AND
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd;
*/

{
#line 387 "Kmkbtutest.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 387 "Kmkbtutest.sqc"
  sqlaaloc(2,3,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 387 "Kmkbtutest.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 387 "Kmkbtutest.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 387 "Kmkbtutest.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 387 "Kmkbtutest.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 387 "Kmkbtutest.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 387 "Kmkbtutest.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 387 "Kmkbtutest.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 387 "Kmkbtutest.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 387 "Kmkbtutest.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 387 "Kmkbtutest.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 387 "Kmkbtutest.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 387 "Kmkbtutest.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 387 "Kmkbtutest.sqc"
  sqlastop(0L);
}

#line 387 "Kmkbtutest.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 392 "Kmkbtutest.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
