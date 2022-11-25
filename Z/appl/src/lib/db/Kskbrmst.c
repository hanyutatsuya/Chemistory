static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,109,65,85,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,52,57,90,75,83,75,66,32,0,0,0,0,0,0,0,0,
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


#line 1 "Kskbrmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Kskbrmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Kskbrmst.h"
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


#line 24 "Kskbrmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Kskbrmst.sqc"

	char    bskkbn[5];
	char    knsgrp[17];
	char    kmkcd[8];
	char    ksbr[16];
	char    kmin[21];
	char    kmax[21];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 40 "Kskbrmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Kskbrmst

BmlDMMInfo	KskbrmstArray[] = {
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( ksbr ),
	DMM_SSTRING( kmin ),
	DMM_SSTRING( kmax ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKskbrmstSelectAll()
 *    KSKBRMST レコード全件取得
 * ■引数
 *    [O]  Kskbrmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKskbrmstSelectAll( Kskbrmst** arrayOut, int* numOut )
{
    Kskbrmst*   array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 78 "Kskbrmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		BSKKBN,
		KNSGRP,
		KMKCD,
		KSBR,
		KMIN,
		KMAX,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        KSKBRMST FOR READ ONLY;
*/

#line 93 "Kskbrmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 95 "Kskbrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 95 "Kskbrmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 95 "Kskbrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 95 "Kskbrmst.sqc"
  sqlastop(0L);
}

#line 95 "Kskbrmst.sqc"


    while( 1 ) {
        Kskbrmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:bskkbn,
			:knsgrp,
			:kmkcd,
			:ksbr,
			:kmin,
			:kmax,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 110 "Kskbrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 110 "Kskbrmst.sqc"
  sqlaaloc(3,10,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 110 "Kskbrmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 16;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[3].sqldata = (void*)ksbr;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 21;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[4].sqldata = (void*)kmin;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[5].sqldata = (void*)kmax;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[6].sqldata = (void*)kaiymd;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[7].sqldata = (void*)haiymd;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[8].sqldata = (void*)hnktntid;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 110 "Kskbrmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 110 "Kskbrmst.sqc"
      sqlasetdata(3,0,10,sql_setdlist,0L,0L);
    }
#line 110 "Kskbrmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 110 "Kskbrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 110 "Kskbrmst.sqc"
  sqlastop(0L);
}

#line 110 "Kskbrmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kskbrmst*)ZbmlRealloc( array,
                                    sizeof( Kskbrmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kskbrmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KskbrmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 125 "Kskbrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 125 "Kskbrmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 125 "Kskbrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 125 "Kskbrmst.sqc"
  sqlastop(0L);
}

#line 125 "Kskbrmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 133 "Kskbrmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKskbrmstSelectKey()
 *    KSKBRMST レコードKey条件取得
 * ■引数
 *    [I]  Kskbrmst* pKey       取得するレコードのキー
 *    [O]  Kskbrmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKskbrmstSelectKey( Kskbrmst* pKey, Kskbrmst** arrayOut, int* numOut )
{
    Kskbrmst*   array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KskbrmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 159 "Kskbrmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		BSKKBN,
		KNSGRP,
		KMKCD,
		KSBR,
		KMIN,
		KMAX,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        KSKBRMST
    WHERE
		BSKKBN = :bskkbn AND
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KSBR = :ksbr AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 180 "Kskbrmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 182 "Kskbrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 182 "Kskbrmst.sqc"
  sqlaaloc(2,5,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 182 "Kskbrmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 182 "Kskbrmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 182 "Kskbrmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 182 "Kskbrmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 182 "Kskbrmst.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 182 "Kskbrmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 182 "Kskbrmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 182 "Kskbrmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 182 "Kskbrmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 182 "Kskbrmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 16;
#line 182 "Kskbrmst.sqc"
      sql_setdlist[3].sqldata = (void*)ksbr;
#line 182 "Kskbrmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 182 "Kskbrmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 182 "Kskbrmst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 182 "Kskbrmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 182 "Kskbrmst.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 182 "Kskbrmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 182 "Kskbrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 182 "Kskbrmst.sqc"
  sqlastop(0L);
}

#line 182 "Kskbrmst.sqc"


    while( 1 ) {
        Kskbrmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:bskkbn,
			:knsgrp,
			:kmkcd,
			:ksbr,
			:kmin,
			:kmax,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 197 "Kskbrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 197 "Kskbrmst.sqc"
  sqlaaloc(3,10,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 197 "Kskbrmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 16;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[3].sqldata = (void*)ksbr;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 21;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[4].sqldata = (void*)kmin;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[5].sqldata = (void*)kmax;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[6].sqldata = (void*)kaiymd;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[7].sqldata = (void*)haiymd;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[8].sqldata = (void*)hnktntid;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 197 "Kskbrmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 197 "Kskbrmst.sqc"
      sqlasetdata(3,0,10,sql_setdlist,0L,0L);
    }
#line 197 "Kskbrmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 197 "Kskbrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 197 "Kskbrmst.sqc"
  sqlastop(0L);
}

#line 197 "Kskbrmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kskbrmst*)ZbmlRealloc( array,
                                    sizeof( Kskbrmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kskbrmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KskbrmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 212 "Kskbrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 212 "Kskbrmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 212 "Kskbrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 212 "Kskbrmst.sqc"
  sqlastop(0L);
}

#line 212 "Kskbrmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 220 "Kskbrmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKskbrmstInsert()
 *    KSKBRMST レコードを挿入する
 * ■引数
 *    [I]  Kskbrmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKskbrmstInsert( Kskbrmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KskbrmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 243 "Kskbrmst.sqc"


    
/*
EXEC SQL INSERT INTO KSKBRMST
    (
		BSKKBN,
		KNSGRP,
		KMKCD,
		KSBR,
		KMIN,
		KMAX,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:bskkbn,
		:knsgrp,
		:kmkcd,
		:ksbr,
		:kmin,
		:kmax,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 268 "Kskbrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 268 "Kskbrmst.sqc"
  sqlaaloc(2,10,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 268 "Kskbrmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 16;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[3].sqldata = (void*)ksbr;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 21;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[4].sqldata = (void*)kmin;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[5].sqldata = (void*)kmax;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[6].sqldata = (void*)kaiymd;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[7].sqldata = (void*)haiymd;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[8].sqldata = (void*)hnktntid;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 268 "Kskbrmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 268 "Kskbrmst.sqc"
      sqlasetdata(2,0,10,sql_setdlist,0L,0L);
    }
#line 268 "Kskbrmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 268 "Kskbrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 268 "Kskbrmst.sqc"
  sqlastop(0L);
}

#line 268 "Kskbrmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 273 "Kskbrmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKskbrmstUpdate()
 *    KSKBRMST レコードを更新する
 * ■引数
 *    [I]  Kskbrmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKskbrmstUpdate( Kskbrmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KskbrmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 297 "Kskbrmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 298 "Kskbrmst.sqc"


    
/*
EXEC SQL UPDATE KSKBRMST
    SET (
		KMIN,
		KMAX,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:kmin,
		:kmax,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		BSKKBN = :bskkbn AND
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KSBR = :ksbr AND
		KAIYMD = :kaiymd;
*/

{
#line 318 "Kskbrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 318 "Kskbrmst.sqc"
  sqlaaloc(2,10,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 318 "Kskbrmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 21;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmin;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmax;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[2].sqldata = (void*)haiymd;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 9;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[3].sqldata = (void*)hnktntid;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 27;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[4].sqldata = (void*)ksndh;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 5;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[5].sqldata = (void*)bskkbn;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 17;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[6].sqldata = (void*)knsgrp;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 8;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[7].sqldata = (void*)kmkcd;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 16;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[8].sqldata = (void*)ksbr;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[9].sqldata = (void*)kaiymd;
#line 318 "Kskbrmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 318 "Kskbrmst.sqc"
      sqlasetdata(2,0,10,sql_setdlist,0L,0L);
    }
#line 318 "Kskbrmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 318 "Kskbrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 318 "Kskbrmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 318 "Kskbrmst.sqc"
  sqlastop(0L);
}

#line 318 "Kskbrmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 323 "Kskbrmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 327 "Kskbrmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKskbrmstDelete()
 *    KSKBRMST レコードを削除する
 * ■引数
 *    [I]  Kskbrmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKskbrmstDelete( Kskbrmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KskbrmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 351 "Kskbrmst.sqc"


    
/*
EXEC SQL DELETE FROM KSKBRMST
    WHERE
		BSKKBN = :bskkbn AND
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KSBR = :ksbr AND
		KAIYMD = :kaiymd;
*/

{
#line 359 "Kskbrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 359 "Kskbrmst.sqc"
  sqlaaloc(2,5,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 359 "Kskbrmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 359 "Kskbrmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 359 "Kskbrmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 359 "Kskbrmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 359 "Kskbrmst.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 359 "Kskbrmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 359 "Kskbrmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 359 "Kskbrmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 359 "Kskbrmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 359 "Kskbrmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 16;
#line 359 "Kskbrmst.sqc"
      sql_setdlist[3].sqldata = (void*)ksbr;
#line 359 "Kskbrmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 359 "Kskbrmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 359 "Kskbrmst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 359 "Kskbrmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 359 "Kskbrmst.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 359 "Kskbrmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 359 "Kskbrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 359 "Kskbrmst.sqc"
  sqlastop(0L);
}

#line 359 "Kskbrmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 364 "Kskbrmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
