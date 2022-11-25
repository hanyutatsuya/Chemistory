static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,102,65,85,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,52,56,90,75,82,75,77,32,0,0,0,0,0,0,0,0,
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


#line 1 "Krkmkmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Krkmkmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Krkmkmst.h"
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


#line 24 "Krkmkmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Krkmkmst.sqc"

	char    kmkcd[8];
	char    krkmkcd[8];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 36 "Krkmkmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Krkmkmst

BmlDMMInfo	KrkmkmstArray[] = {
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( krkmkcd ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKrkmkmstSelectAll()
 *    KRKMKMST レコード全件取得
 * ■引数
 *    [O]  Krkmkmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKrkmkmstSelectAll( Krkmkmst** arrayOut, int* numOut )
{
    Krkmkmst*   array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 70 "Krkmkmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KMKCD,
		KRKMKCD,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        KRKMKMST FOR READ ONLY;
*/

#line 81 "Krkmkmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 83 "Krkmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 83 "Krkmkmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 83 "Krkmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 83 "Krkmkmst.sqc"
  sqlastop(0L);
}

#line 83 "Krkmkmst.sqc"


    while( 1 ) {
        Krkmkmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:kmkcd,
			:krkmkcd,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 94 "Krkmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 94 "Krkmkmst.sqc"
  sqlaaloc(3,6,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 94 "Krkmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 94 "Krkmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcd;
#line 94 "Krkmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 94 "Krkmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 94 "Krkmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)krkmkcd;
#line 94 "Krkmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 94 "Krkmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 94 "Krkmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 94 "Krkmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 94 "Krkmkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 94 "Krkmkmst.sqc"
      sql_setdlist[3].sqldata = (void*)haiymd;
#line 94 "Krkmkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 94 "Krkmkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 9;
#line 94 "Krkmkmst.sqc"
      sql_setdlist[4].sqldata = (void*)hnktntid;
#line 94 "Krkmkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 94 "Krkmkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 27;
#line 94 "Krkmkmst.sqc"
      sql_setdlist[5].sqldata = (void*)ksndh;
#line 94 "Krkmkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 94 "Krkmkmst.sqc"
      sqlasetdata(3,0,6,sql_setdlist,0L,0L);
    }
#line 94 "Krkmkmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 94 "Krkmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 94 "Krkmkmst.sqc"
  sqlastop(0L);
}

#line 94 "Krkmkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Krkmkmst*)ZbmlRealloc( array,
                                    sizeof( Krkmkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Krkmkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KrkmkmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 109 "Krkmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 109 "Krkmkmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 109 "Krkmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 109 "Krkmkmst.sqc"
  sqlastop(0L);
}

#line 109 "Krkmkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 117 "Krkmkmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKrkmkmstSelectKey()
 *    KRKMKMST レコードKey条件取得
 * ■引数
 *    [I]  Krkmkmst* pKey       取得するレコードのキー
 *    [O]  Krkmkmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKrkmkmstSelectKey( Krkmkmst* pKey, Krkmkmst** arrayOut, int* numOut )
{
    Krkmkmst*   array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KrkmkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 143 "Krkmkmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KMKCD,
		KRKMKCD,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        KRKMKMST
    WHERE
		KMKCD = :kmkcd AND
		KRKMKCD = :krkmkcd AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 158 "Krkmkmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 160 "Krkmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 160 "Krkmkmst.sqc"
  sqlaaloc(2,3,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 160 "Krkmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 160 "Krkmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcd;
#line 160 "Krkmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 160 "Krkmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 160 "Krkmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)krkmkcd;
#line 160 "Krkmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 160 "Krkmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 160 "Krkmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 160 "Krkmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 160 "Krkmkmst.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 160 "Krkmkmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 160 "Krkmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 160 "Krkmkmst.sqc"
  sqlastop(0L);
}

#line 160 "Krkmkmst.sqc"


    while( 1 ) {
        Krkmkmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:kmkcd,
			:krkmkcd,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 171 "Krkmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 171 "Krkmkmst.sqc"
  sqlaaloc(3,6,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 171 "Krkmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 171 "Krkmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcd;
#line 171 "Krkmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 171 "Krkmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 171 "Krkmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)krkmkcd;
#line 171 "Krkmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 171 "Krkmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 171 "Krkmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 171 "Krkmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 171 "Krkmkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 171 "Krkmkmst.sqc"
      sql_setdlist[3].sqldata = (void*)haiymd;
#line 171 "Krkmkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 171 "Krkmkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 9;
#line 171 "Krkmkmst.sqc"
      sql_setdlist[4].sqldata = (void*)hnktntid;
#line 171 "Krkmkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 171 "Krkmkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 27;
#line 171 "Krkmkmst.sqc"
      sql_setdlist[5].sqldata = (void*)ksndh;
#line 171 "Krkmkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 171 "Krkmkmst.sqc"
      sqlasetdata(3,0,6,sql_setdlist,0L,0L);
    }
#line 171 "Krkmkmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 171 "Krkmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 171 "Krkmkmst.sqc"
  sqlastop(0L);
}

#line 171 "Krkmkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Krkmkmst*)ZbmlRealloc( array,
                                    sizeof( Krkmkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Krkmkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KrkmkmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 186 "Krkmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 186 "Krkmkmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 186 "Krkmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 186 "Krkmkmst.sqc"
  sqlastop(0L);
}

#line 186 "Krkmkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 194 "Krkmkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKrkmkmstInsert()
 *    KRKMKMST レコードを挿入する
 * ■引数
 *    [I]  Krkmkmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKrkmkmstInsert( Krkmkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KrkmkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 217 "Krkmkmst.sqc"


    
/*
EXEC SQL INSERT INTO KRKMKMST
    (
		KMKCD,
		KRKMKCD,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:kmkcd,
		:krkmkcd,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 234 "Krkmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 234 "Krkmkmst.sqc"
  sqlaaloc(2,6,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 234 "Krkmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 234 "Krkmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcd;
#line 234 "Krkmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 234 "Krkmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 234 "Krkmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)krkmkcd;
#line 234 "Krkmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 234 "Krkmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 234 "Krkmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 234 "Krkmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 234 "Krkmkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 234 "Krkmkmst.sqc"
      sql_setdlist[3].sqldata = (void*)haiymd;
#line 234 "Krkmkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 234 "Krkmkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 9;
#line 234 "Krkmkmst.sqc"
      sql_setdlist[4].sqldata = (void*)hnktntid;
#line 234 "Krkmkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 234 "Krkmkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 27;
#line 234 "Krkmkmst.sqc"
      sql_setdlist[5].sqldata = (void*)ksndh;
#line 234 "Krkmkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 234 "Krkmkmst.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 234 "Krkmkmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 234 "Krkmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 234 "Krkmkmst.sqc"
  sqlastop(0L);
}

#line 234 "Krkmkmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 239 "Krkmkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKrkmkmstUpdate()
 *    KRKMKMST レコードを更新する
 * ■引数
 *    [I]  Krkmkmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKrkmkmstUpdate( Krkmkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KrkmkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 263 "Krkmkmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 264 "Krkmkmst.sqc"


    
/*
EXEC SQL UPDATE KRKMKMST
    SET (
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		KMKCD = :kmkcd AND
		KRKMKCD = :krkmkcd AND
		KAIYMD = :kaiymd;
*/

{
#line 278 "Krkmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 278 "Krkmkmst.sqc"
  sqlaaloc(2,6,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 278 "Krkmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 278 "Krkmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)haiymd;
#line 278 "Krkmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 278 "Krkmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 9;
#line 278 "Krkmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)hnktntid;
#line 278 "Krkmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 278 "Krkmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 27;
#line 278 "Krkmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)ksndh;
#line 278 "Krkmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 278 "Krkmkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 278 "Krkmkmst.sqc"
      sql_setdlist[3].sqldata = (void*)kmkcd;
#line 278 "Krkmkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 278 "Krkmkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 278 "Krkmkmst.sqc"
      sql_setdlist[4].sqldata = (void*)krkmkcd;
#line 278 "Krkmkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 278 "Krkmkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 278 "Krkmkmst.sqc"
      sql_setdlist[5].sqldata = (void*)kaiymd;
#line 278 "Krkmkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 278 "Krkmkmst.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 278 "Krkmkmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 278 "Krkmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 278 "Krkmkmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 278 "Krkmkmst.sqc"
  sqlastop(0L);
}

#line 278 "Krkmkmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 283 "Krkmkmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 287 "Krkmkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKrkmkmstDelete()
 *    KRKMKMST レコードを削除する
 * ■引数
 *    [I]  Krkmkmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKrkmkmstDelete( Krkmkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KrkmkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 311 "Krkmkmst.sqc"


    
/*
EXEC SQL DELETE FROM KRKMKMST
    WHERE
		KMKCD = :kmkcd AND
		KRKMKCD = :krkmkcd AND
		KAIYMD = :kaiymd;
*/

{
#line 317 "Krkmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 317 "Krkmkmst.sqc"
  sqlaaloc(2,3,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 317 "Krkmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 317 "Krkmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcd;
#line 317 "Krkmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 317 "Krkmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 317 "Krkmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)krkmkcd;
#line 317 "Krkmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 317 "Krkmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 317 "Krkmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 317 "Krkmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 317 "Krkmkmst.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 317 "Krkmkmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 317 "Krkmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 317 "Krkmkmst.sqc"
  sqlastop(0L);
}

#line 317 "Krkmkmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 322 "Krkmkmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
