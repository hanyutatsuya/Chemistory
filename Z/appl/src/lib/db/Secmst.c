static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,114,65,86,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,54,49,90,83,69,67,77,32,0,0,0,0,0,0,0,0,
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


#line 1 "Secmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Secmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Secmst.h"
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


#line 24 "Secmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Secmst.sqc"

	char    seccd[3];
	char    secnm[21];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 36 "Secmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Secmst

BmlDMMInfo	SecmstArray[] = {
	DMM_SSTRING( seccd ),
	DMM_SSTRING( secnm ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbSecmstSelectAll()
 *    SECMST レコード全件取得
 * ■引数
 *    [O]  Secmst** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbSecmstSelectAll( Secmst** arrayOut, int* numOut )
{
    Secmst*     array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 70 "Secmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		SECCD,
		SECNM,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        SECMST FOR READ ONLY;
*/

#line 81 "Secmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 83 "Secmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 83 "Secmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 83 "Secmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 83 "Secmst.sqc"
  sqlastop(0L);
}

#line 83 "Secmst.sqc"


    while( 1 ) {
        Secmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:seccd,
			:secnm,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 94 "Secmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 94 "Secmst.sqc"
  sqlaaloc(3,6,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 94 "Secmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 94 "Secmst.sqc"
      sql_setdlist[0].sqldata = (void*)seccd;
#line 94 "Secmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 94 "Secmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 94 "Secmst.sqc"
      sql_setdlist[1].sqldata = (void*)secnm;
#line 94 "Secmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 94 "Secmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 94 "Secmst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 94 "Secmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 94 "Secmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 94 "Secmst.sqc"
      sql_setdlist[3].sqldata = (void*)haiymd;
#line 94 "Secmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 94 "Secmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 9;
#line 94 "Secmst.sqc"
      sql_setdlist[4].sqldata = (void*)hnktntid;
#line 94 "Secmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 94 "Secmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 27;
#line 94 "Secmst.sqc"
      sql_setdlist[5].sqldata = (void*)ksndh;
#line 94 "Secmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 94 "Secmst.sqc"
      sqlasetdata(3,0,6,sql_setdlist,0L,0L);
    }
#line 94 "Secmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 94 "Secmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 94 "Secmst.sqc"
  sqlastop(0L);
}

#line 94 "Secmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Secmst*)ZbmlRealloc( array,
                                    sizeof( Secmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Secmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, SecmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 109 "Secmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 109 "Secmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 109 "Secmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 109 "Secmst.sqc"
  sqlastop(0L);
}

#line 109 "Secmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 117 "Secmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbSecmstSelectKey()
 *    SECMST レコードKey条件取得
 * ■引数
 *    [I]  Secmst* pKey       取得するレコードのキー
 *    [O]  Secmst** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbSecmstSelectKey( Secmst* pKey, Secmst** arrayOut, int* numOut )
{
    Secmst*     array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, SecmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 143 "Secmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		SECCD,
		SECNM,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        SECMST
    WHERE
		SECCD = :seccd AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 157 "Secmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 159 "Secmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 159 "Secmst.sqc"
  sqlaaloc(2,2,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 159 "Secmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 159 "Secmst.sqc"
      sql_setdlist[0].sqldata = (void*)seccd;
#line 159 "Secmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 159 "Secmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 159 "Secmst.sqc"
      sql_setdlist[1].sqldata = (void*)kaiymd;
#line 159 "Secmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 159 "Secmst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 159 "Secmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 159 "Secmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 159 "Secmst.sqc"
  sqlastop(0L);
}

#line 159 "Secmst.sqc"


    while( 1 ) {
        Secmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:seccd,
			:secnm,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 170 "Secmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 170 "Secmst.sqc"
  sqlaaloc(3,6,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 170 "Secmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 170 "Secmst.sqc"
      sql_setdlist[0].sqldata = (void*)seccd;
#line 170 "Secmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 170 "Secmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 170 "Secmst.sqc"
      sql_setdlist[1].sqldata = (void*)secnm;
#line 170 "Secmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 170 "Secmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 170 "Secmst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 170 "Secmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 170 "Secmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 170 "Secmst.sqc"
      sql_setdlist[3].sqldata = (void*)haiymd;
#line 170 "Secmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 170 "Secmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 9;
#line 170 "Secmst.sqc"
      sql_setdlist[4].sqldata = (void*)hnktntid;
#line 170 "Secmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 170 "Secmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 27;
#line 170 "Secmst.sqc"
      sql_setdlist[5].sqldata = (void*)ksndh;
#line 170 "Secmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 170 "Secmst.sqc"
      sqlasetdata(3,0,6,sql_setdlist,0L,0L);
    }
#line 170 "Secmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 170 "Secmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 170 "Secmst.sqc"
  sqlastop(0L);
}

#line 170 "Secmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Secmst*)ZbmlRealloc( array,
                                    sizeof( Secmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Secmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, SecmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 185 "Secmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 185 "Secmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 185 "Secmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 185 "Secmst.sqc"
  sqlastop(0L);
}

#line 185 "Secmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 193 "Secmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbSecmstInsert()
 *    SECMST レコードを挿入する
 * ■引数
 *    [I]  Secmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbSecmstInsert( Secmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, SecmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 216 "Secmst.sqc"


    
/*
EXEC SQL INSERT INTO SECMST
    (
		SECCD,
		SECNM,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:seccd,
		:secnm,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 233 "Secmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 233 "Secmst.sqc"
  sqlaaloc(2,6,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 233 "Secmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 233 "Secmst.sqc"
      sql_setdlist[0].sqldata = (void*)seccd;
#line 233 "Secmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 233 "Secmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 233 "Secmst.sqc"
      sql_setdlist[1].sqldata = (void*)secnm;
#line 233 "Secmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 233 "Secmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 233 "Secmst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 233 "Secmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 233 "Secmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 233 "Secmst.sqc"
      sql_setdlist[3].sqldata = (void*)haiymd;
#line 233 "Secmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 233 "Secmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 9;
#line 233 "Secmst.sqc"
      sql_setdlist[4].sqldata = (void*)hnktntid;
#line 233 "Secmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 233 "Secmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 27;
#line 233 "Secmst.sqc"
      sql_setdlist[5].sqldata = (void*)ksndh;
#line 233 "Secmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 233 "Secmst.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 233 "Secmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 233 "Secmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 233 "Secmst.sqc"
  sqlastop(0L);
}

#line 233 "Secmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 238 "Secmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbSecmstUpdate()
 *    SECMST レコードを更新する
 * ■引数
 *    [I]  Secmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbSecmstUpdate( Secmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, SecmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 262 "Secmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 263 "Secmst.sqc"


    
/*
EXEC SQL UPDATE SECMST
    SET (
		SECNM,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:secnm,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		SECCD = :seccd AND
		KAIYMD = :kaiymd;
*/

{
#line 278 "Secmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 278 "Secmst.sqc"
  sqlaaloc(2,6,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 278 "Secmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 21;
#line 278 "Secmst.sqc"
      sql_setdlist[0].sqldata = (void*)secnm;
#line 278 "Secmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 278 "Secmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 278 "Secmst.sqc"
      sql_setdlist[1].sqldata = (void*)haiymd;
#line 278 "Secmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 278 "Secmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 9;
#line 278 "Secmst.sqc"
      sql_setdlist[2].sqldata = (void*)hnktntid;
#line 278 "Secmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 278 "Secmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 27;
#line 278 "Secmst.sqc"
      sql_setdlist[3].sqldata = (void*)ksndh;
#line 278 "Secmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 278 "Secmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 3;
#line 278 "Secmst.sqc"
      sql_setdlist[4].sqldata = (void*)seccd;
#line 278 "Secmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 278 "Secmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 278 "Secmst.sqc"
      sql_setdlist[5].sqldata = (void*)kaiymd;
#line 278 "Secmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 278 "Secmst.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 278 "Secmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 278 "Secmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 278 "Secmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 278 "Secmst.sqc"
  sqlastop(0L);
}

#line 278 "Secmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 283 "Secmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 287 "Secmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbSecmstDelete()
 *    SECMST レコードを削除する
 * ■引数
 *    [I]  Secmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbSecmstDelete( Secmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, SecmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 311 "Secmst.sqc"


    
/*
EXEC SQL DELETE FROM SECMST
    WHERE
		SECCD = :seccd AND
		KAIYMD = :kaiymd;
*/

{
#line 316 "Secmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 316 "Secmst.sqc"
  sqlaaloc(2,2,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 316 "Secmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 316 "Secmst.sqc"
      sql_setdlist[0].sqldata = (void*)seccd;
#line 316 "Secmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 316 "Secmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 316 "Secmst.sqc"
      sql_setdlist[1].sqldata = (void*)kaiymd;
#line 316 "Secmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 316 "Secmst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 316 "Secmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 316 "Secmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 316 "Secmst.sqc"
  sqlastop(0L);
}

#line 316 "Secmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 321 "Secmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
