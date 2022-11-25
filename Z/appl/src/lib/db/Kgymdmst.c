static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,69,65,84,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,51,51,90,75,71,89,77,32,0,0,0,0,0,0,0,0,
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


#line 1 "Kgymdmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Kgymdmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Kgymdmst.h"
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


#line 24 "Kgymdmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Kgymdmst.sqc"

	char    kgymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 33 "Kgymdmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Kgymdmst

BmlDMMInfo	KgymdmstArray[] = {
	DMM_SDATE( kgymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKgymdmstSelectAll()
 *    KGYMDMST レコード全件取得
 * ■引数
 *    [O]  Kgymdmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKgymdmstSelectAll( Kgymdmst** arrayOut, int* numOut )
{
    Kgymdmst*   array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 64 "Kgymdmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KGYMD,
		HNKTNTID,
		KSNDH
    FROM
        KGYMDMST FOR READ ONLY;
*/

#line 72 "Kgymdmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 74 "Kgymdmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 74 "Kgymdmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 74 "Kgymdmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 74 "Kgymdmst.sqc"
  sqlastop(0L);
}

#line 74 "Kgymdmst.sqc"


    while( 1 ) {
        Kgymdmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:kgymd,
			:hnktntid,
			:ksndh;
*/

{
#line 82 "Kgymdmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 82 "Kgymdmst.sqc"
  sqlaaloc(3,3,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 82 "Kgymdmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 82 "Kgymdmst.sqc"
      sql_setdlist[0].sqldata = (void*)kgymd;
#line 82 "Kgymdmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 82 "Kgymdmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 9;
#line 82 "Kgymdmst.sqc"
      sql_setdlist[1].sqldata = (void*)hnktntid;
#line 82 "Kgymdmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 82 "Kgymdmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 27;
#line 82 "Kgymdmst.sqc"
      sql_setdlist[2].sqldata = (void*)ksndh;
#line 82 "Kgymdmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 82 "Kgymdmst.sqc"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 82 "Kgymdmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 82 "Kgymdmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 82 "Kgymdmst.sqc"
  sqlastop(0L);
}

#line 82 "Kgymdmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kgymdmst*)ZbmlRealloc( array,
                                    sizeof( Kgymdmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kgymdmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KgymdmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 97 "Kgymdmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 97 "Kgymdmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 97 "Kgymdmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 97 "Kgymdmst.sqc"
  sqlastop(0L);
}

#line 97 "Kgymdmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 105 "Kgymdmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKgymdmstSelectKey()
 *    KGYMDMST レコードKey条件取得
 * ■引数
 *    [I]  Kgymdmst* pKey       取得するレコードのキー
 *    [O]  Kgymdmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKgymdmstSelectKey( Kgymdmst* pKey, Kgymdmst** arrayOut, int* numOut )
{
    Kgymdmst*   array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KgymdmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 131 "Kgymdmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KGYMD,
		HNKTNTID,
		KSNDH
    FROM
        KGYMDMST
    WHERE
		KGYMD = :kgymd FOR READ ONLY;
*/

#line 141 "Kgymdmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 143 "Kgymdmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 143 "Kgymdmst.sqc"
  sqlaaloc(2,1,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 143 "Kgymdmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 143 "Kgymdmst.sqc"
      sql_setdlist[0].sqldata = (void*)kgymd;
#line 143 "Kgymdmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 143 "Kgymdmst.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 143 "Kgymdmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 143 "Kgymdmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 143 "Kgymdmst.sqc"
  sqlastop(0L);
}

#line 143 "Kgymdmst.sqc"


    while( 1 ) {
        Kgymdmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:kgymd,
			:hnktntid,
			:ksndh;
*/

{
#line 151 "Kgymdmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 151 "Kgymdmst.sqc"
  sqlaaloc(3,3,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 151 "Kgymdmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 151 "Kgymdmst.sqc"
      sql_setdlist[0].sqldata = (void*)kgymd;
#line 151 "Kgymdmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 151 "Kgymdmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 9;
#line 151 "Kgymdmst.sqc"
      sql_setdlist[1].sqldata = (void*)hnktntid;
#line 151 "Kgymdmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 151 "Kgymdmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 27;
#line 151 "Kgymdmst.sqc"
      sql_setdlist[2].sqldata = (void*)ksndh;
#line 151 "Kgymdmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 151 "Kgymdmst.sqc"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 151 "Kgymdmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 151 "Kgymdmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 151 "Kgymdmst.sqc"
  sqlastop(0L);
}

#line 151 "Kgymdmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kgymdmst*)ZbmlRealloc( array,
                                    sizeof( Kgymdmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kgymdmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KgymdmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 166 "Kgymdmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 166 "Kgymdmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 166 "Kgymdmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 166 "Kgymdmst.sqc"
  sqlastop(0L);
}

#line 166 "Kgymdmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 174 "Kgymdmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKgymdmstInsert()
 *    KGYMDMST レコードを挿入する
 * ■引数
 *    [I]  Kgymdmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKgymdmstInsert( Kgymdmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KgymdmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 197 "Kgymdmst.sqc"


    
/*
EXEC SQL INSERT INTO KGYMDMST
    (
		KGYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:kgymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 208 "Kgymdmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 208 "Kgymdmst.sqc"
  sqlaaloc(2,3,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 208 "Kgymdmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 208 "Kgymdmst.sqc"
      sql_setdlist[0].sqldata = (void*)kgymd;
#line 208 "Kgymdmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 208 "Kgymdmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 9;
#line 208 "Kgymdmst.sqc"
      sql_setdlist[1].sqldata = (void*)hnktntid;
#line 208 "Kgymdmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 208 "Kgymdmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 27;
#line 208 "Kgymdmst.sqc"
      sql_setdlist[2].sqldata = (void*)ksndh;
#line 208 "Kgymdmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 208 "Kgymdmst.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 208 "Kgymdmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 208 "Kgymdmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 208 "Kgymdmst.sqc"
  sqlastop(0L);
}

#line 208 "Kgymdmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 213 "Kgymdmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKgymdmstUpdate()
 *    KGYMDMST レコードを更新する
 * ■引数
 *    [I]  Kgymdmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKgymdmstUpdate( Kgymdmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KgymdmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 237 "Kgymdmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 238 "Kgymdmst.sqc"


    
/*
EXEC SQL UPDATE KGYMDMST
    SET (
		HNKTNTID,
		KSNDH
    ) = (
		:hnktntid,
		:ksndh
    ) WHERE
		KGYMD = :kgymd;
*/

{
#line 248 "Kgymdmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 248 "Kgymdmst.sqc"
  sqlaaloc(2,3,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 248 "Kgymdmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 9;
#line 248 "Kgymdmst.sqc"
      sql_setdlist[0].sqldata = (void*)hnktntid;
#line 248 "Kgymdmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 248 "Kgymdmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 27;
#line 248 "Kgymdmst.sqc"
      sql_setdlist[1].sqldata = (void*)ksndh;
#line 248 "Kgymdmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 248 "Kgymdmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 248 "Kgymdmst.sqc"
      sql_setdlist[2].sqldata = (void*)kgymd;
#line 248 "Kgymdmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 248 "Kgymdmst.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 248 "Kgymdmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 248 "Kgymdmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 248 "Kgymdmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 248 "Kgymdmst.sqc"
  sqlastop(0L);
}

#line 248 "Kgymdmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 253 "Kgymdmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 257 "Kgymdmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKgymdmstDelete()
 *    KGYMDMST レコードを削除する
 * ■引数
 *    [I]  Kgymdmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKgymdmstDelete( Kgymdmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KgymdmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 281 "Kgymdmst.sqc"


    
/*
EXEC SQL DELETE FROM KGYMDMST
    WHERE
		KGYMD = :kgymd;
*/

{
#line 285 "Kgymdmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 285 "Kgymdmst.sqc"
  sqlaaloc(2,1,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 285 "Kgymdmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 285 "Kgymdmst.sqc"
      sql_setdlist[0].sqldata = (void*)kgymd;
#line 285 "Kgymdmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 285 "Kgymdmst.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 285 "Kgymdmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 285 "Kgymdmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 285 "Kgymdmst.sqc"
  sqlastop(0L);
}

#line 285 "Kgymdmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 290 "Kgymdmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
