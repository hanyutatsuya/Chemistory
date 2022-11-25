static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,74,65,88,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,56,48,90,90,65,73,82,32,0,0,0,0,0,0,0,0,
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


#line 1 "Zairmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Zairmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Zairmst.h"
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


#line 24 "Zairmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Zairmst.sqc"

	char    zaicd[5];
	char    zainmkn[11];
	char    zainmkj[21];
	char    zainmej[41];
	char    zaikg[3];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 39 "Zairmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Zairmst

BmlDMMInfo	ZairmstArray[] = {
	DMM_SSTRING( zaicd ),
	DMM_SSTRING( zainmkn ),
	DMM_SSTRING( zainmkj ),
	DMM_SSTRING( zainmej ),
	DMM_SSTRING( zaikg ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbZairmstSelectAll()
 *    ZAIRMST レコード全件取得
 * ■引数
 *    [O]  Zairmst** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbZairmstSelectAll( Zairmst** arrayOut, int* numOut )
{
    Zairmst*    array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 76 "Zairmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		ZAICD,
		ZAINMKN,
		ZAINMKJ,
		ZAINMEJ,
		ZAIKG,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        ZAIRMST FOR READ ONLY;
*/

#line 90 "Zairmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 92 "Zairmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 92 "Zairmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 92 "Zairmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 92 "Zairmst.sqc"
  sqlastop(0L);
}

#line 92 "Zairmst.sqc"


    while( 1 ) {
        Zairmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:zaicd,
			:zainmkn,
			:zainmkj,
			:zainmej,
			:zaikg,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 106 "Zairmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 106 "Zairmst.sqc"
  sqlaaloc(3,9,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 106 "Zairmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 106 "Zairmst.sqc"
      sql_setdlist[0].sqldata = (void*)zaicd;
#line 106 "Zairmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 106 "Zairmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 106 "Zairmst.sqc"
      sql_setdlist[1].sqldata = (void*)zainmkn;
#line 106 "Zairmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 106 "Zairmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 106 "Zairmst.sqc"
      sql_setdlist[2].sqldata = (void*)zainmkj;
#line 106 "Zairmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 106 "Zairmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 41;
#line 106 "Zairmst.sqc"
      sql_setdlist[3].sqldata = (void*)zainmej;
#line 106 "Zairmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 106 "Zairmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 3;
#line 106 "Zairmst.sqc"
      sql_setdlist[4].sqldata = (void*)zaikg;
#line 106 "Zairmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 106 "Zairmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 106 "Zairmst.sqc"
      sql_setdlist[5].sqldata = (void*)kaiymd;
#line 106 "Zairmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 106 "Zairmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 106 "Zairmst.sqc"
      sql_setdlist[6].sqldata = (void*)haiymd;
#line 106 "Zairmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 106 "Zairmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 106 "Zairmst.sqc"
      sql_setdlist[7].sqldata = (void*)hnktntid;
#line 106 "Zairmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 106 "Zairmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 106 "Zairmst.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 106 "Zairmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 106 "Zairmst.sqc"
      sqlasetdata(3,0,9,sql_setdlist,0L,0L);
    }
#line 106 "Zairmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 106 "Zairmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 106 "Zairmst.sqc"
  sqlastop(0L);
}

#line 106 "Zairmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Zairmst*)ZbmlRealloc( array,
                                    sizeof( Zairmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Zairmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, ZairmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 121 "Zairmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 121 "Zairmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 121 "Zairmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 121 "Zairmst.sqc"
  sqlastop(0L);
}

#line 121 "Zairmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 129 "Zairmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbZairmstSelectKey()
 *    ZAIRMST レコードKey条件取得
 * ■引数
 *    [I]  Zairmst* pKey       取得するレコードのキー
 *    [O]  Zairmst** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbZairmstSelectKey( Zairmst* pKey, Zairmst** arrayOut, int* numOut )
{
    Zairmst*    array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, ZairmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 155 "Zairmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		ZAICD,
		ZAINMKN,
		ZAINMKJ,
		ZAINMEJ,
		ZAIKG,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        ZAIRMST
    WHERE
		ZAICD = :zaicd AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 172 "Zairmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 174 "Zairmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 174 "Zairmst.sqc"
  sqlaaloc(2,2,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 174 "Zairmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 174 "Zairmst.sqc"
      sql_setdlist[0].sqldata = (void*)zaicd;
#line 174 "Zairmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 174 "Zairmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 174 "Zairmst.sqc"
      sql_setdlist[1].sqldata = (void*)kaiymd;
#line 174 "Zairmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 174 "Zairmst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 174 "Zairmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 174 "Zairmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 174 "Zairmst.sqc"
  sqlastop(0L);
}

#line 174 "Zairmst.sqc"


    while( 1 ) {
        Zairmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:zaicd,
			:zainmkn,
			:zainmkj,
			:zainmej,
			:zaikg,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 188 "Zairmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 188 "Zairmst.sqc"
  sqlaaloc(3,9,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 188 "Zairmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 188 "Zairmst.sqc"
      sql_setdlist[0].sqldata = (void*)zaicd;
#line 188 "Zairmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 188 "Zairmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 188 "Zairmst.sqc"
      sql_setdlist[1].sqldata = (void*)zainmkn;
#line 188 "Zairmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 188 "Zairmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 188 "Zairmst.sqc"
      sql_setdlist[2].sqldata = (void*)zainmkj;
#line 188 "Zairmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 188 "Zairmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 41;
#line 188 "Zairmst.sqc"
      sql_setdlist[3].sqldata = (void*)zainmej;
#line 188 "Zairmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 188 "Zairmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 3;
#line 188 "Zairmst.sqc"
      sql_setdlist[4].sqldata = (void*)zaikg;
#line 188 "Zairmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 188 "Zairmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 188 "Zairmst.sqc"
      sql_setdlist[5].sqldata = (void*)kaiymd;
#line 188 "Zairmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 188 "Zairmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 188 "Zairmst.sqc"
      sql_setdlist[6].sqldata = (void*)haiymd;
#line 188 "Zairmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 188 "Zairmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 188 "Zairmst.sqc"
      sql_setdlist[7].sqldata = (void*)hnktntid;
#line 188 "Zairmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 188 "Zairmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 188 "Zairmst.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 188 "Zairmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 188 "Zairmst.sqc"
      sqlasetdata(3,0,9,sql_setdlist,0L,0L);
    }
#line 188 "Zairmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 188 "Zairmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 188 "Zairmst.sqc"
  sqlastop(0L);
}

#line 188 "Zairmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Zairmst*)ZbmlRealloc( array,
                                    sizeof( Zairmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Zairmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, ZairmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 203 "Zairmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 203 "Zairmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 203 "Zairmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 203 "Zairmst.sqc"
  sqlastop(0L);
}

#line 203 "Zairmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 211 "Zairmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbZairmstInsert()
 *    ZAIRMST レコードを挿入する
 * ■引数
 *    [I]  Zairmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbZairmstInsert( Zairmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, ZairmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 234 "Zairmst.sqc"


    
/*
EXEC SQL INSERT INTO ZAIRMST
    (
		ZAICD,
		ZAINMKN,
		ZAINMKJ,
		ZAINMEJ,
		ZAIKG,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:zaicd,
		:zainmkn,
		:zainmkj,
		:zainmej,
		:zaikg,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 257 "Zairmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 257 "Zairmst.sqc"
  sqlaaloc(2,9,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 257 "Zairmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 257 "Zairmst.sqc"
      sql_setdlist[0].sqldata = (void*)zaicd;
#line 257 "Zairmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 257 "Zairmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 257 "Zairmst.sqc"
      sql_setdlist[1].sqldata = (void*)zainmkn;
#line 257 "Zairmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 257 "Zairmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 257 "Zairmst.sqc"
      sql_setdlist[2].sqldata = (void*)zainmkj;
#line 257 "Zairmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 257 "Zairmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 41;
#line 257 "Zairmst.sqc"
      sql_setdlist[3].sqldata = (void*)zainmej;
#line 257 "Zairmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 257 "Zairmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 3;
#line 257 "Zairmst.sqc"
      sql_setdlist[4].sqldata = (void*)zaikg;
#line 257 "Zairmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 257 "Zairmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 257 "Zairmst.sqc"
      sql_setdlist[5].sqldata = (void*)kaiymd;
#line 257 "Zairmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 257 "Zairmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 257 "Zairmst.sqc"
      sql_setdlist[6].sqldata = (void*)haiymd;
#line 257 "Zairmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 257 "Zairmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 257 "Zairmst.sqc"
      sql_setdlist[7].sqldata = (void*)hnktntid;
#line 257 "Zairmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 257 "Zairmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 257 "Zairmst.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 257 "Zairmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 257 "Zairmst.sqc"
      sqlasetdata(2,0,9,sql_setdlist,0L,0L);
    }
#line 257 "Zairmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 257 "Zairmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 257 "Zairmst.sqc"
  sqlastop(0L);
}

#line 257 "Zairmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 262 "Zairmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbZairmstUpdate()
 *    ZAIRMST レコードを更新する
 * ■引数
 *    [I]  Zairmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbZairmstUpdate( Zairmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, ZairmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 286 "Zairmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 287 "Zairmst.sqc"


    
/*
EXEC SQL UPDATE ZAIRMST
    SET (
		ZAINMKN,
		ZAINMKJ,
		ZAINMEJ,
		ZAIKG,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:zainmkn,
		:zainmkj,
		:zainmej,
		:zaikg,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		ZAICD = :zaicd AND
		KAIYMD = :kaiymd;
*/

{
#line 308 "Zairmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 308 "Zairmst.sqc"
  sqlaaloc(2,9,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 308 "Zairmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 308 "Zairmst.sqc"
      sql_setdlist[0].sqldata = (void*)zainmkn;
#line 308 "Zairmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 308 "Zairmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 308 "Zairmst.sqc"
      sql_setdlist[1].sqldata = (void*)zainmkj;
#line 308 "Zairmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 308 "Zairmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 41;
#line 308 "Zairmst.sqc"
      sql_setdlist[2].sqldata = (void*)zainmej;
#line 308 "Zairmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 308 "Zairmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 308 "Zairmst.sqc"
      sql_setdlist[3].sqldata = (void*)zaikg;
#line 308 "Zairmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 308 "Zairmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 308 "Zairmst.sqc"
      sql_setdlist[4].sqldata = (void*)haiymd;
#line 308 "Zairmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 308 "Zairmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 9;
#line 308 "Zairmst.sqc"
      sql_setdlist[5].sqldata = (void*)hnktntid;
#line 308 "Zairmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 308 "Zairmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 308 "Zairmst.sqc"
      sql_setdlist[6].sqldata = (void*)ksndh;
#line 308 "Zairmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 308 "Zairmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 5;
#line 308 "Zairmst.sqc"
      sql_setdlist[7].sqldata = (void*)zaicd;
#line 308 "Zairmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 308 "Zairmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 308 "Zairmst.sqc"
      sql_setdlist[8].sqldata = (void*)kaiymd;
#line 308 "Zairmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 308 "Zairmst.sqc"
      sqlasetdata(2,0,9,sql_setdlist,0L,0L);
    }
#line 308 "Zairmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 308 "Zairmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 308 "Zairmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 308 "Zairmst.sqc"
  sqlastop(0L);
}

#line 308 "Zairmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 313 "Zairmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 317 "Zairmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbZairmstDelete()
 *    ZAIRMST レコードを削除する
 * ■引数
 *    [I]  Zairmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbZairmstDelete( Zairmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, ZairmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 341 "Zairmst.sqc"


    
/*
EXEC SQL DELETE FROM ZAIRMST
    WHERE
		ZAICD = :zaicd AND
		KAIYMD = :kaiymd;
*/

{
#line 346 "Zairmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 346 "Zairmst.sqc"
  sqlaaloc(2,2,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 346 "Zairmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 346 "Zairmst.sqc"
      sql_setdlist[0].sqldata = (void*)zaicd;
#line 346 "Zairmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 346 "Zairmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 346 "Zairmst.sqc"
      sql_setdlist[1].sqldata = (void*)kaiymd;
#line 346 "Zairmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 346 "Zairmst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 346 "Zairmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 346 "Zairmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 346 "Zairmst.sqc"
  sqlastop(0L);
}

#line 346 "Zairmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 351 "Zairmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
