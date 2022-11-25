static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,76,65,82,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,49,49,90,67,72,75,49,32,0,0,0,0,0,0,0,0,
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


#line 1 "Chk100mst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Chk100mst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Chk100mst.h"
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


#line 24 "Chk100mst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Chk100mst.sqc"

	char    knsgrp[17];
	char    kmkcd[8];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 36 "Chk100mst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Chk100mst

BmlDMMInfo	Chk100mstArray[] = {
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbChk100mstSelectAll()
 *    CHK100MST レコード全件取得
 * ■引数
 *    [O]  Chk100mst** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbChk100mstSelectAll( Chk100mst** arrayOut, int* numOut )
{
    Chk100mst*  array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 70 "Chk100mst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSGRP,
		KMKCD,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        CHK100MST FOR READ ONLY;
*/

#line 81 "Chk100mst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 83 "Chk100mst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 83 "Chk100mst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 83 "Chk100mst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 83 "Chk100mst.sqc"
  sqlastop(0L);
}

#line 83 "Chk100mst.sqc"


    while( 1 ) {
        Chk100mst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knsgrp,
			:kmkcd,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 94 "Chk100mst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 94 "Chk100mst.sqc"
  sqlaaloc(3,6,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 94 "Chk100mst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 94 "Chk100mst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 94 "Chk100mst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 94 "Chk100mst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 94 "Chk100mst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 94 "Chk100mst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 94 "Chk100mst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 94 "Chk100mst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 94 "Chk100mst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 94 "Chk100mst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 94 "Chk100mst.sqc"
      sql_setdlist[3].sqldata = (void*)haiymd;
#line 94 "Chk100mst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 94 "Chk100mst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 9;
#line 94 "Chk100mst.sqc"
      sql_setdlist[4].sqldata = (void*)hnktntid;
#line 94 "Chk100mst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 94 "Chk100mst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 27;
#line 94 "Chk100mst.sqc"
      sql_setdlist[5].sqldata = (void*)ksndh;
#line 94 "Chk100mst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 94 "Chk100mst.sqc"
      sqlasetdata(3,0,6,sql_setdlist,0L,0L);
    }
#line 94 "Chk100mst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 94 "Chk100mst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 94 "Chk100mst.sqc"
  sqlastop(0L);
}

#line 94 "Chk100mst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Chk100mst*)ZbmlRealloc( array,
                                    sizeof( Chk100mst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Chk100mst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, Chk100mstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 109 "Chk100mst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 109 "Chk100mst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 109 "Chk100mst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 109 "Chk100mst.sqc"
  sqlastop(0L);
}

#line 109 "Chk100mst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 117 "Chk100mst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbChk100mstSelectKey()
 *    CHK100MST レコードKey条件取得
 * ■引数
 *    [I]  Chk100mst* pKey      取得するレコードのキー
 *    [O]  Chk100mst** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbChk100mstSelectKey( Chk100mst* pKey, Chk100mst** arrayOut, int* numOut )
{
    Chk100mst*  array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, Chk100mstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 143 "Chk100mst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSGRP,
		KMKCD,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        CHK100MST
    WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 158 "Chk100mst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 160 "Chk100mst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 160 "Chk100mst.sqc"
  sqlaaloc(2,3,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 160 "Chk100mst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 160 "Chk100mst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 160 "Chk100mst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 160 "Chk100mst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 160 "Chk100mst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 160 "Chk100mst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 160 "Chk100mst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 160 "Chk100mst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 160 "Chk100mst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 160 "Chk100mst.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 160 "Chk100mst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 160 "Chk100mst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 160 "Chk100mst.sqc"
  sqlastop(0L);
}

#line 160 "Chk100mst.sqc"


    while( 1 ) {
        Chk100mst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knsgrp,
			:kmkcd,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 171 "Chk100mst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 171 "Chk100mst.sqc"
  sqlaaloc(3,6,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 171 "Chk100mst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 171 "Chk100mst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 171 "Chk100mst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 171 "Chk100mst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 171 "Chk100mst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 171 "Chk100mst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 171 "Chk100mst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 171 "Chk100mst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 171 "Chk100mst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 171 "Chk100mst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 171 "Chk100mst.sqc"
      sql_setdlist[3].sqldata = (void*)haiymd;
#line 171 "Chk100mst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 171 "Chk100mst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 9;
#line 171 "Chk100mst.sqc"
      sql_setdlist[4].sqldata = (void*)hnktntid;
#line 171 "Chk100mst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 171 "Chk100mst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 27;
#line 171 "Chk100mst.sqc"
      sql_setdlist[5].sqldata = (void*)ksndh;
#line 171 "Chk100mst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 171 "Chk100mst.sqc"
      sqlasetdata(3,0,6,sql_setdlist,0L,0L);
    }
#line 171 "Chk100mst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 171 "Chk100mst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 171 "Chk100mst.sqc"
  sqlastop(0L);
}

#line 171 "Chk100mst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Chk100mst*)ZbmlRealloc( array,
                                    sizeof( Chk100mst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Chk100mst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, Chk100mstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 186 "Chk100mst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 186 "Chk100mst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 186 "Chk100mst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 186 "Chk100mst.sqc"
  sqlastop(0L);
}

#line 186 "Chk100mst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 194 "Chk100mst.sqc"

    return sqlca.sqlcode;
}
long ZdbChk100mstSelectGrp( Chk100mst* pKey, Chk100mst** arrayOut, int* numOut )
{
    Chk100mst*  array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, Chk100mstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 208 "Chk100mst.sqc"


    
/*
EXEC SQL DECLARE c3 CURSOR FOR
    SELECT
		KNSGRP,
		KMKCD,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        CHK100MST
    WHERE
		KNSGRP = :knsgrp AND
		KAIYMD <= CURRENT DATE AND
		HAIYMD >= CURRENT DATE FOR READ ONLY;
*/

#line 223 "Chk100mst.sqc"


    
/*
EXEC SQL OPEN c3;
*/

{
#line 225 "Chk100mst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 225 "Chk100mst.sqc"
  sqlaaloc(2,1,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 225 "Chk100mst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 225 "Chk100mst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 225 "Chk100mst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 225 "Chk100mst.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 225 "Chk100mst.sqc"
  sqlacall((unsigned short)26,3,2,0,0L);
#line 225 "Chk100mst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 225 "Chk100mst.sqc"
  sqlastop(0L);
}

#line 225 "Chk100mst.sqc"


    while( 1 ) {
        Chk100mst* rec;

        
/*
EXEC SQL FETCH c3 INTO
			:knsgrp,
			:kmkcd,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 236 "Chk100mst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 236 "Chk100mst.sqc"
  sqlaaloc(3,6,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 236 "Chk100mst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 236 "Chk100mst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 236 "Chk100mst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 236 "Chk100mst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 236 "Chk100mst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 236 "Chk100mst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 236 "Chk100mst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 236 "Chk100mst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 236 "Chk100mst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 236 "Chk100mst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 236 "Chk100mst.sqc"
      sql_setdlist[3].sqldata = (void*)haiymd;
#line 236 "Chk100mst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 236 "Chk100mst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 9;
#line 236 "Chk100mst.sqc"
      sql_setdlist[4].sqldata = (void*)hnktntid;
#line 236 "Chk100mst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 236 "Chk100mst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 27;
#line 236 "Chk100mst.sqc"
      sql_setdlist[5].sqldata = (void*)ksndh;
#line 236 "Chk100mst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 236 "Chk100mst.sqc"
      sqlasetdata(3,0,6,sql_setdlist,0L,0L);
    }
#line 236 "Chk100mst.sqc"
  sqlacall((unsigned short)25,3,0,3,0L);
#line 236 "Chk100mst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 236 "Chk100mst.sqc"
  sqlastop(0L);
}

#line 236 "Chk100mst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Chk100mst*)ZbmlRealloc( array,
                                    sizeof( Chk100mst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Chk100mst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, Chk100mstArray );
    }

    
/*
EXEC SQL CLOSE c3;
*/

{
#line 251 "Chk100mst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 251 "Chk100mst.sqc"
  sqlacall((unsigned short)20,3,0,0,0L);
#line 251 "Chk100mst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 251 "Chk100mst.sqc"
  sqlastop(0L);
}

#line 251 "Chk100mst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 259 "Chk100mst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbChk100mstInsert()
 *    CHK100MST レコードを挿入する
 * ■引数
 *    [I]  Chk100mst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbChk100mstInsert( Chk100mst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, Chk100mstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 282 "Chk100mst.sqc"


    
/*
EXEC SQL INSERT INTO CHK100MST
    (
		KNSGRP,
		KMKCD,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:knsgrp,
		:kmkcd,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 299 "Chk100mst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 299 "Chk100mst.sqc"
  sqlaaloc(2,6,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 299 "Chk100mst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 299 "Chk100mst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 299 "Chk100mst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 299 "Chk100mst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 299 "Chk100mst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 299 "Chk100mst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 299 "Chk100mst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 299 "Chk100mst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 299 "Chk100mst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 299 "Chk100mst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 299 "Chk100mst.sqc"
      sql_setdlist[3].sqldata = (void*)haiymd;
#line 299 "Chk100mst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 299 "Chk100mst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 9;
#line 299 "Chk100mst.sqc"
      sql_setdlist[4].sqldata = (void*)hnktntid;
#line 299 "Chk100mst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 299 "Chk100mst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 27;
#line 299 "Chk100mst.sqc"
      sql_setdlist[5].sqldata = (void*)ksndh;
#line 299 "Chk100mst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 299 "Chk100mst.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 299 "Chk100mst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 299 "Chk100mst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 299 "Chk100mst.sqc"
  sqlastop(0L);
}

#line 299 "Chk100mst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 304 "Chk100mst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbChk100mstUpdate()
 *    CHK100MST レコードを更新する
 * ■引数
 *    [I]  Chk100mst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbChk100mstUpdate( Chk100mst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, Chk100mstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 328 "Chk100mst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 329 "Chk100mst.sqc"


    
/*
EXEC SQL UPDATE CHK100MST
    SET (
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KAIYMD = :kaiymd;
*/

{
#line 343 "Chk100mst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 343 "Chk100mst.sqc"
  sqlaaloc(2,6,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 343 "Chk100mst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 343 "Chk100mst.sqc"
      sql_setdlist[0].sqldata = (void*)haiymd;
#line 343 "Chk100mst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 343 "Chk100mst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 9;
#line 343 "Chk100mst.sqc"
      sql_setdlist[1].sqldata = (void*)hnktntid;
#line 343 "Chk100mst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 343 "Chk100mst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 27;
#line 343 "Chk100mst.sqc"
      sql_setdlist[2].sqldata = (void*)ksndh;
#line 343 "Chk100mst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 343 "Chk100mst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 343 "Chk100mst.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 343 "Chk100mst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 343 "Chk100mst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 343 "Chk100mst.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 343 "Chk100mst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 343 "Chk100mst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 343 "Chk100mst.sqc"
      sql_setdlist[5].sqldata = (void*)kaiymd;
#line 343 "Chk100mst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 343 "Chk100mst.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 343 "Chk100mst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 343 "Chk100mst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 343 "Chk100mst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 343 "Chk100mst.sqc"
  sqlastop(0L);
}

#line 343 "Chk100mst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 348 "Chk100mst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 352 "Chk100mst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbChk100mstDelete()
 *    CHK100MST レコードを削除する
 * ■引数
 *    [I]  Chk100mst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbChk100mstDelete( Chk100mst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, Chk100mstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 376 "Chk100mst.sqc"


    
/*
EXEC SQL DELETE FROM CHK100MST
    WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KAIYMD = :kaiymd;
*/

{
#line 382 "Chk100mst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 382 "Chk100mst.sqc"
  sqlaaloc(2,3,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 382 "Chk100mst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 382 "Chk100mst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 382 "Chk100mst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 382 "Chk100mst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 382 "Chk100mst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 382 "Chk100mst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 382 "Chk100mst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 382 "Chk100mst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 382 "Chk100mst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 382 "Chk100mst.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 382 "Chk100mst.sqc"
  sqlacall((unsigned short)24,6,2,0,0L);
#line 382 "Chk100mst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 382 "Chk100mst.sqc"
  sqlastop(0L);
}

#line 382 "Chk100mst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 387 "Chk100mst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
