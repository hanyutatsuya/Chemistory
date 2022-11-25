static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,106,66,81,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,57,90,67,65,76,67,32,32,0,0,0,0,0,0,0,0,
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


#line 1 "Calckmkmst.sqc"
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


#line 24 "Calckmkmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Calckmkmst.sqc"

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

#line 39 "Calckmkmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Calckmkmst

BmlDMMInfo	CalckmkmstArray[] = {
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

/******************************************************************************
 * ZdbCalckmkmstSelectAll()
 *    CALCKMKMST レコード全件取得
 * ■引数
 *    [O]  Calckmkmst** arrayOu 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCalckmkmstSelectAll( Calckmkmst** arrayOut, int* numOut )
{
    Calckmkmst* array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 76 "Calckmkmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
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
        CALCKMKMST FOR READ ONLY;
*/

#line 90 "Calckmkmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 92 "Calckmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 92 "Calckmkmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 92 "Calckmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 92 "Calckmkmst.sqc"
  sqlastop(0L);
}

#line 92 "Calckmkmst.sqc"


    while( 1 ) {
        Calckmkmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
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
#line 106 "Calckmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 106 "Calckmkmst.sqc"
  sqlaaloc(3,9,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 106 "Calckmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)sstcd;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[3].sqldata = (void*)zaicd;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 129;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[4].sqldata = (void*)ksnsk;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[5].sqldata = (void*)kaiymd;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[6].sqldata = (void*)haiymd;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[7].sqldata = (void*)hnktntid;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 106 "Calckmkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 106 "Calckmkmst.sqc"
      sqlasetdata(3,0,9,sql_setdlist,0L,0L);
    }
#line 106 "Calckmkmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 106 "Calckmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 106 "Calckmkmst.sqc"
  sqlastop(0L);
}

#line 106 "Calckmkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Calckmkmst*)ZbmlRealloc( array,
                                    sizeof( Calckmkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Calckmkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, CalckmkmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 121 "Calckmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 121 "Calckmkmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 121 "Calckmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 121 "Calckmkmst.sqc"
  sqlastop(0L);
}

#line 121 "Calckmkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 129 "Calckmkmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbCalckmkmstSelectKey()
 *    CALCKMKMST レコードKey条件取得
 * ■引数
 *    [I]  Calckmkmst* pKey     取得するレコードのキー
 *    [O]  Calckmkmst** arrayOu 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCalckmkmstSelectKey( Calckmkmst* pKey, Calckmkmst** arrayOut, int* numOut )
{
    Calckmkmst* array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, CalckmkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 155 "Calckmkmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
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
		KMKCD = :kmkcd AND
		SSTCD = :sstcd AND
		ZAICD = :zaicd AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 175 "Calckmkmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 177 "Calckmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 177 "Calckmkmst.sqc"
  sqlaaloc(2,5,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 177 "Calckmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 177 "Calckmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 177 "Calckmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 177 "Calckmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 177 "Calckmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 177 "Calckmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 177 "Calckmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 177 "Calckmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)sstcd;
#line 177 "Calckmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 177 "Calckmkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 177 "Calckmkmst.sqc"
      sql_setdlist[3].sqldata = (void*)zaicd;
#line 177 "Calckmkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 177 "Calckmkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 177 "Calckmkmst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 177 "Calckmkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 177 "Calckmkmst.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 177 "Calckmkmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 177 "Calckmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 177 "Calckmkmst.sqc"
  sqlastop(0L);
}

#line 177 "Calckmkmst.sqc"


    while( 1 ) {
        Calckmkmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
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
#line 191 "Calckmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 191 "Calckmkmst.sqc"
  sqlaaloc(3,9,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 191 "Calckmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)sstcd;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[3].sqldata = (void*)zaicd;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 129;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[4].sqldata = (void*)ksnsk;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[5].sqldata = (void*)kaiymd;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[6].sqldata = (void*)haiymd;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[7].sqldata = (void*)hnktntid;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 191 "Calckmkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 191 "Calckmkmst.sqc"
      sqlasetdata(3,0,9,sql_setdlist,0L,0L);
    }
#line 191 "Calckmkmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 191 "Calckmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 191 "Calckmkmst.sqc"
  sqlastop(0L);
}

#line 191 "Calckmkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Calckmkmst*)ZbmlRealloc( array,
                                    sizeof( Calckmkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Calckmkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, CalckmkmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 206 "Calckmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 206 "Calckmkmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 206 "Calckmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 206 "Calckmkmst.sqc"
  sqlastop(0L);
}

#line 206 "Calckmkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 214 "Calckmkmst.sqc"

    return sqlca.sqlcode;
}
long ZdbCalckmkmstSelectKey2( Calckmkmst* pKey, Calckmkmst** arrayOut, int* numOut )
{
    Calckmkmst* array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, CalckmkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 228 "Calckmkmst.sqc"


    
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
		KAIYMD <= CURRENT DATE FOR READ ONLY;
*/

#line 246 "Calckmkmst.sqc"


    
/*
EXEC SQL OPEN c3;
*/

{
#line 248 "Calckmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 248 "Calckmkmst.sqc"
  sqlaaloc(2,2,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 248 "Calckmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 248 "Calckmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 248 "Calckmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 248 "Calckmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 129;
#line 248 "Calckmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)ksnsk;
#line 248 "Calckmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 248 "Calckmkmst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 248 "Calckmkmst.sqc"
  sqlacall((unsigned short)26,3,2,0,0L);
#line 248 "Calckmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 248 "Calckmkmst.sqc"
  sqlastop(0L);
}

#line 248 "Calckmkmst.sqc"


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
#line 262 "Calckmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 262 "Calckmkmst.sqc"
  sqlaaloc(3,9,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 262 "Calckmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)sstcd;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[3].sqldata = (void*)zaicd;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 129;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[4].sqldata = (void*)ksnsk;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[5].sqldata = (void*)kaiymd;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[6].sqldata = (void*)haiymd;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[7].sqldata = (void*)hnktntid;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 262 "Calckmkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 262 "Calckmkmst.sqc"
      sqlasetdata(3,0,9,sql_setdlist,0L,0L);
    }
#line 262 "Calckmkmst.sqc"
  sqlacall((unsigned short)25,3,0,3,0L);
#line 262 "Calckmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 262 "Calckmkmst.sqc"
  sqlastop(0L);
}

#line 262 "Calckmkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Calckmkmst*)ZbmlRealloc( array,
                                    sizeof( Calckmkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Calckmkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, CalckmkmstArray );
    }

    
/*
EXEC SQL CLOSE c3;
*/

{
#line 277 "Calckmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 277 "Calckmkmst.sqc"
  sqlacall((unsigned short)20,3,0,0,0L);
#line 277 "Calckmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 277 "Calckmkmst.sqc"
  sqlastop(0L);
}

#line 277 "Calckmkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 285 "Calckmkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbCalckmkmstInsert()
 *    CALCKMKMST レコードを挿入する
 * ■引数
 *    [I]  Calckmkmst* rec      挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCalckmkmstInsert( Calckmkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, CalckmkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 308 "Calckmkmst.sqc"


    
/*
EXEC SQL INSERT INTO CALCKMKMST
    (
		KNSGRP,
		KMKCD,
		SSTCD,
		ZAICD,
		KSNSK,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:knsgrp,
		:kmkcd,
		:sstcd,
		:zaicd,
		:ksnsk,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 331 "Calckmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 331 "Calckmkmst.sqc"
  sqlaaloc(2,9,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 331 "Calckmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)sstcd;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[3].sqldata = (void*)zaicd;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 129;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[4].sqldata = (void*)ksnsk;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[5].sqldata = (void*)kaiymd;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[6].sqldata = (void*)haiymd;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[7].sqldata = (void*)hnktntid;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 331 "Calckmkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 331 "Calckmkmst.sqc"
      sqlasetdata(2,0,9,sql_setdlist,0L,0L);
    }
#line 331 "Calckmkmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 331 "Calckmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 331 "Calckmkmst.sqc"
  sqlastop(0L);
}

#line 331 "Calckmkmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 336 "Calckmkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbCalckmkmstUpdate()
 *    CALCKMKMST レコードを更新する
 * ■引数
 *    [I]  Calckmkmst* rec      更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCalckmkmstUpdate( Calckmkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, CalckmkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 360 "Calckmkmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 361 "Calckmkmst.sqc"


    
/*
EXEC SQL UPDATE CALCKMKMST
    SET (
		KSNSK,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:ksnsk,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		SSTCD = :sstcd AND
		ZAICD = :zaicd AND
		KAIYMD = :kaiymd;
*/

{
#line 379 "Calckmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 379 "Calckmkmst.sqc"
  sqlaaloc(2,9,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 379 "Calckmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 129;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)ksnsk;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)haiymd;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 9;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)hnktntid;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 27;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[3].sqldata = (void*)ksndh;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[6].sqldata = (void*)sstcd;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 5;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[7].sqldata = (void*)zaicd;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[8].sqldata = (void*)kaiymd;
#line 379 "Calckmkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 379 "Calckmkmst.sqc"
      sqlasetdata(2,0,9,sql_setdlist,0L,0L);
    }
#line 379 "Calckmkmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 379 "Calckmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 379 "Calckmkmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 379 "Calckmkmst.sqc"
  sqlastop(0L);
}

#line 379 "Calckmkmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 384 "Calckmkmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 388 "Calckmkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbCalckmkmstDelete()
 *    CALCKMKMST レコードを削除する
 * ■引数
 *    [I]  Calckmkmst* rec      削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCalckmkmstDelete( Calckmkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, CalckmkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 412 "Calckmkmst.sqc"


    
/*
EXEC SQL DELETE FROM CALCKMKMST
    WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		SSTCD = :sstcd AND
		ZAICD = :zaicd AND
		KAIYMD = :kaiymd;
*/

{
#line 420 "Calckmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 420 "Calckmkmst.sqc"
  sqlaaloc(2,5,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 420 "Calckmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 420 "Calckmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 420 "Calckmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 420 "Calckmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 420 "Calckmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 420 "Calckmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 420 "Calckmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 420 "Calckmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)sstcd;
#line 420 "Calckmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 420 "Calckmkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 420 "Calckmkmst.sqc"
      sql_setdlist[3].sqldata = (void*)zaicd;
#line 420 "Calckmkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 420 "Calckmkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 420 "Calckmkmst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 420 "Calckmkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 420 "Calckmkmst.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 420 "Calckmkmst.sqc"
  sqlacall((unsigned short)24,6,2,0,0L);
#line 420 "Calckmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 420 "Calckmkmst.sqc"
  sqlastop(0L);
}

#line 420 "Calckmkmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 425 "Calckmkmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
