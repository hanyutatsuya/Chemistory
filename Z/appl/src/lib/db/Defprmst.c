static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,83,66,82,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,49,57,90,68,69,70,80,32,0,0,0,0,0,0,0,0,
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


#line 1 "Defprmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Defprmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Defprmst.h"
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


#line 24 "Defprmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Defprmst.sqc"

	char    compnm[21];
	char    tyhyoid[21];
	char    prntrnm[21];
	char    cstno;
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 36 "Defprmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Defprmst

BmlDMMInfo	DefprmstArray[] = {
	DMM_SSTRING( compnm ),
	DMM_SSTRING( tyhyoid ),
	DMM_SSTRING( prntrnm ),
	DMM_SCHAR( cstno ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbDefprmstSelectAll()
 *    DEFPRMST レコード全件取得
 * ■引数
 *    [O]  Defprmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbDefprmstSelectAll( Defprmst** arrayOut, int* numOut )
{
    Defprmst*   array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 70 "Defprmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		COMPNM,
		TYHYOID,
		PRNTRNM,
		CSTNO,
		HNKTNTID,
		KSNDH
    FROM
        DEFPRMST FOR READ ONLY;
*/

#line 81 "Defprmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 83 "Defprmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 83 "Defprmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 83 "Defprmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 83 "Defprmst.sqc"
  sqlastop(0L);
}

#line 83 "Defprmst.sqc"


    while( 1 ) {
        Defprmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:compnm,
			:tyhyoid,
			:prntrnm,
			:cstno,
			:hnktntid,
			:ksndh;
*/

{
#line 94 "Defprmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 94 "Defprmst.sqc"
  sqlaaloc(3,6,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 94 "Defprmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 21;
#line 94 "Defprmst.sqc"
      sql_setdlist[0].sqldata = (void*)compnm;
#line 94 "Defprmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 94 "Defprmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 94 "Defprmst.sqc"
      sql_setdlist[1].sqldata = (void*)tyhyoid;
#line 94 "Defprmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 94 "Defprmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 94 "Defprmst.sqc"
      sql_setdlist[2].sqldata = (void*)prntrnm;
#line 94 "Defprmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 94 "Defprmst.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 94 "Defprmst.sqc"
      sql_setdlist[3].sqldata = (void*)&cstno;
#line 94 "Defprmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 94 "Defprmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 9;
#line 94 "Defprmst.sqc"
      sql_setdlist[4].sqldata = (void*)hnktntid;
#line 94 "Defprmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 94 "Defprmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 27;
#line 94 "Defprmst.sqc"
      sql_setdlist[5].sqldata = (void*)ksndh;
#line 94 "Defprmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 94 "Defprmst.sqc"
      sqlasetdata(3,0,6,sql_setdlist,0L,0L);
    }
#line 94 "Defprmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 94 "Defprmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 94 "Defprmst.sqc"
  sqlastop(0L);
}

#line 94 "Defprmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Defprmst*)ZbmlRealloc( array,
                                    sizeof( Defprmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Defprmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, DefprmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 109 "Defprmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 109 "Defprmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 109 "Defprmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 109 "Defprmst.sqc"
  sqlastop(0L);
}

#line 109 "Defprmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 117 "Defprmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbDefprmstSelectKey()
 *    DEFPRMST レコードKey条件取得
 * ■引数
 *    [I]  Defprmst* pKey       取得するレコードのキー
 *    [O]  Defprmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbDefprmstSelectKey( Defprmst* pKey, Defprmst** arrayOut, int* numOut )
{
    Defprmst*   array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, DefprmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 143 "Defprmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		COMPNM,
		TYHYOID,
		PRNTRNM,
		CSTNO,
		HNKTNTID,
		KSNDH
    FROM
        DEFPRMST
    WHERE
		COMPNM = :compnm FOR READ ONLY;
*/

#line 156 "Defprmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 158 "Defprmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 158 "Defprmst.sqc"
  sqlaaloc(2,1,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 158 "Defprmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 21;
#line 158 "Defprmst.sqc"
      sql_setdlist[0].sqldata = (void*)compnm;
#line 158 "Defprmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 158 "Defprmst.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 158 "Defprmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 158 "Defprmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 158 "Defprmst.sqc"
  sqlastop(0L);
}

#line 158 "Defprmst.sqc"


    while( 1 ) {
        Defprmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:compnm,
			:tyhyoid,
			:prntrnm,
			:cstno,
			:hnktntid,
			:ksndh;
*/

{
#line 169 "Defprmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 169 "Defprmst.sqc"
  sqlaaloc(3,6,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 169 "Defprmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 21;
#line 169 "Defprmst.sqc"
      sql_setdlist[0].sqldata = (void*)compnm;
#line 169 "Defprmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 169 "Defprmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 169 "Defprmst.sqc"
      sql_setdlist[1].sqldata = (void*)tyhyoid;
#line 169 "Defprmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 169 "Defprmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 169 "Defprmst.sqc"
      sql_setdlist[2].sqldata = (void*)prntrnm;
#line 169 "Defprmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 169 "Defprmst.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 169 "Defprmst.sqc"
      sql_setdlist[3].sqldata = (void*)&cstno;
#line 169 "Defprmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 169 "Defprmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 9;
#line 169 "Defprmst.sqc"
      sql_setdlist[4].sqldata = (void*)hnktntid;
#line 169 "Defprmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 169 "Defprmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 27;
#line 169 "Defprmst.sqc"
      sql_setdlist[5].sqldata = (void*)ksndh;
#line 169 "Defprmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 169 "Defprmst.sqc"
      sqlasetdata(3,0,6,sql_setdlist,0L,0L);
    }
#line 169 "Defprmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 169 "Defprmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 169 "Defprmst.sqc"
  sqlastop(0L);
}

#line 169 "Defprmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Defprmst*)ZbmlRealloc( array,
                                    sizeof( Defprmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Defprmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, DefprmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 184 "Defprmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 184 "Defprmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 184 "Defprmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 184 "Defprmst.sqc"
  sqlastop(0L);
}

#line 184 "Defprmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 192 "Defprmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbDefprmstInsert()
 *    DEFPRMST レコードを挿入する
 * ■引数
 *    [I]  Defprmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbDefprmstInsert( Defprmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, DefprmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 215 "Defprmst.sqc"


    
/*
EXEC SQL INSERT INTO DEFPRMST
    (
		COMPNM,
		TYHYOID,
		PRNTRNM,
		CSTNO,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:compnm,
		:tyhyoid,
		:prntrnm,
		:cstno,
		:hnktntid,
		:ksndh
    );
*/

{
#line 232 "Defprmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 232 "Defprmst.sqc"
  sqlaaloc(2,6,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 232 "Defprmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 21;
#line 232 "Defprmst.sqc"
      sql_setdlist[0].sqldata = (void*)compnm;
#line 232 "Defprmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 232 "Defprmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 232 "Defprmst.sqc"
      sql_setdlist[1].sqldata = (void*)tyhyoid;
#line 232 "Defprmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 232 "Defprmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 232 "Defprmst.sqc"
      sql_setdlist[2].sqldata = (void*)prntrnm;
#line 232 "Defprmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 232 "Defprmst.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 232 "Defprmst.sqc"
      sql_setdlist[3].sqldata = (void*)&cstno;
#line 232 "Defprmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 232 "Defprmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 9;
#line 232 "Defprmst.sqc"
      sql_setdlist[4].sqldata = (void*)hnktntid;
#line 232 "Defprmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 232 "Defprmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 27;
#line 232 "Defprmst.sqc"
      sql_setdlist[5].sqldata = (void*)ksndh;
#line 232 "Defprmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 232 "Defprmst.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 232 "Defprmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 232 "Defprmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 232 "Defprmst.sqc"
  sqlastop(0L);
}

#line 232 "Defprmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 237 "Defprmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbDefprmstUpdate()
 *    DEFPRMST レコードを更新する
 * ■引数
 *    [I]  Defprmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbDefprmstUpdate( Defprmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, DefprmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 261 "Defprmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 262 "Defprmst.sqc"


    
/*
EXEC SQL UPDATE DEFPRMST
    SET (
		TYHYOID,
		PRNTRNM,
		CSTNO,
		HNKTNTID,
		KSNDH
    ) = (
		:tyhyoid,
		:prntrnm,
		:cstno,
		:hnktntid,
		:ksndh
    ) WHERE
		COMPNM = :compnm;
*/

{
#line 278 "Defprmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 278 "Defprmst.sqc"
  sqlaaloc(2,6,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 278 "Defprmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 21;
#line 278 "Defprmst.sqc"
      sql_setdlist[0].sqldata = (void*)tyhyoid;
#line 278 "Defprmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 278 "Defprmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 278 "Defprmst.sqc"
      sql_setdlist[1].sqldata = (void*)prntrnm;
#line 278 "Defprmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 278 "Defprmst.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 278 "Defprmst.sqc"
      sql_setdlist[2].sqldata = (void*)&cstno;
#line 278 "Defprmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 278 "Defprmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 9;
#line 278 "Defprmst.sqc"
      sql_setdlist[3].sqldata = (void*)hnktntid;
#line 278 "Defprmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 278 "Defprmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 27;
#line 278 "Defprmst.sqc"
      sql_setdlist[4].sqldata = (void*)ksndh;
#line 278 "Defprmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 278 "Defprmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 278 "Defprmst.sqc"
      sql_setdlist[5].sqldata = (void*)compnm;
#line 278 "Defprmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 278 "Defprmst.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 278 "Defprmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 278 "Defprmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 278 "Defprmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 278 "Defprmst.sqc"
  sqlastop(0L);
}

#line 278 "Defprmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 283 "Defprmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 287 "Defprmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbDefprmstDelete()
 *    DEFPRMST レコードを削除する
 * ■引数
 *    [I]  Defprmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbDefprmstDelete( Defprmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, DefprmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 311 "Defprmst.sqc"


    
/*
EXEC SQL DELETE FROM DEFPRMST
    WHERE
		COMPNM = :compnm;
*/

{
#line 315 "Defprmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 315 "Defprmst.sqc"
  sqlaaloc(2,1,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 315 "Defprmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 21;
#line 315 "Defprmst.sqc"
      sql_setdlist[0].sqldata = (void*)compnm;
#line 315 "Defprmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 315 "Defprmst.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 315 "Defprmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 315 "Defprmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 315 "Defprmst.sqc"
  sqlastop(0L);
}

#line 315 "Defprmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 320 "Defprmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
