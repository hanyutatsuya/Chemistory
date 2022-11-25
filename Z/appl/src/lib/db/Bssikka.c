static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,70,66,81,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,54,90,66,83,83,73,32,32,0,0,0,0,0,0,0,0,
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


#line 1 "Bssikka.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Bssikka.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Bssikka.h"
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


#line 24 "Bssikka.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Bssikka.sqc"

	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   bssino;
	short   gyono;
	char    bssidt[129];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 37 "Bssikka.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Bssikka

BmlDMMInfo	BssikkaArray[] = {
	DMM_SDATE( utkymd ),
	DMM_SSTRING( irino ),
	DMM_SCHAR( iriketflg ),
	DMM_SSHORT( bssino ),
	DMM_SSHORT( gyono ),
	DMM_SSTRING( bssidt ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbBssikkaSelectAll()
 *    BSSIKKA レコード全件取得
 * ■引数
 *    [O]  Bssikka** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbBssikkaSelectAll( Bssikka** arrayOut, int* numOut )
{
    Bssikka*    array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 72 "Bssikka.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		UTKYMD,
		IRINO,
		IRIKETFLG,
		BSSINO,
		GYONO,
		BSSIDT,
		KSNDH
    FROM
        BSSIKKA FOR READ ONLY;
*/

#line 84 "Bssikka.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 86 "Bssikka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 86 "Bssikka.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 86 "Bssikka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 86 "Bssikka.sqc"
  sqlastop(0L);
}

#line 86 "Bssikka.sqc"


    while( 1 ) {
        Bssikka* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:utkymd,
			:irino,
			:iriketflg,
			:bssino,
			:gyono,
			:bssidt,
			:ksndh;
*/

{
#line 98 "Bssikka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 98 "Bssikka.sqc"
  sqlaaloc(3,7,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 98 "Bssikka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 98 "Bssikka.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 98 "Bssikka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 98 "Bssikka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 98 "Bssikka.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 98 "Bssikka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 98 "Bssikka.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 98 "Bssikka.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 98 "Bssikka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 98 "Bssikka.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 98 "Bssikka.sqc"
      sql_setdlist[3].sqldata = (void*)&bssino;
#line 98 "Bssikka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 98 "Bssikka.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 98 "Bssikka.sqc"
      sql_setdlist[4].sqldata = (void*)&gyono;
#line 98 "Bssikka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 98 "Bssikka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 129;
#line 98 "Bssikka.sqc"
      sql_setdlist[5].sqldata = (void*)bssidt;
#line 98 "Bssikka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 98 "Bssikka.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 98 "Bssikka.sqc"
      sql_setdlist[6].sqldata = (void*)ksndh;
#line 98 "Bssikka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 98 "Bssikka.sqc"
      sqlasetdata(3,0,7,sql_setdlist,0L,0L);
    }
#line 98 "Bssikka.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 98 "Bssikka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 98 "Bssikka.sqc"
  sqlastop(0L);
}

#line 98 "Bssikka.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Bssikka*)ZbmlRealloc( array,
                                    sizeof( Bssikka ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Bssikka ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, BssikkaArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 113 "Bssikka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 113 "Bssikka.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 113 "Bssikka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 113 "Bssikka.sqc"
  sqlastop(0L);
}

#line 113 "Bssikka.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 121 "Bssikka.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbBssikkaSelectKey()
 *    BSSIKKA レコードKey条件取得
 * ■引数
 *    [I]  Bssikka* pKey       取得するレコードのキー
 *    [O]  Bssikka** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbBssikkaSelectKey( Bssikka* pKey, Bssikka** arrayOut, int* numOut )
{
    Bssikka*    array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, BssikkaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 147 "Bssikka.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		UTKYMD,
		IRINO,
		IRIKETFLG,
		BSSINO,
		GYONO,
		BSSIDT,
		KSNDH
    FROM
        BSSIKKA
    WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		BSSINO = :bssino AND
		GYONO = :gyono FOR READ ONLY;
*/

#line 164 "Bssikka.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 166 "Bssikka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 166 "Bssikka.sqc"
  sqlaaloc(2,4,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 166 "Bssikka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 166 "Bssikka.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 166 "Bssikka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 166 "Bssikka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 166 "Bssikka.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 166 "Bssikka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 166 "Bssikka.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 166 "Bssikka.sqc"
      sql_setdlist[2].sqldata = (void*)&bssino;
#line 166 "Bssikka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 166 "Bssikka.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 166 "Bssikka.sqc"
      sql_setdlist[3].sqldata = (void*)&gyono;
#line 166 "Bssikka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 166 "Bssikka.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 166 "Bssikka.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 166 "Bssikka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 166 "Bssikka.sqc"
  sqlastop(0L);
}

#line 166 "Bssikka.sqc"


    while( 1 ) {
        Bssikka* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:utkymd,
			:irino,
			:iriketflg,
			:bssino,
			:gyono,
			:bssidt,
			:ksndh;
*/

{
#line 178 "Bssikka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 178 "Bssikka.sqc"
  sqlaaloc(3,7,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 178 "Bssikka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 178 "Bssikka.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 178 "Bssikka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 178 "Bssikka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 178 "Bssikka.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 178 "Bssikka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 178 "Bssikka.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 178 "Bssikka.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 178 "Bssikka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 178 "Bssikka.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 178 "Bssikka.sqc"
      sql_setdlist[3].sqldata = (void*)&bssino;
#line 178 "Bssikka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 178 "Bssikka.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 178 "Bssikka.sqc"
      sql_setdlist[4].sqldata = (void*)&gyono;
#line 178 "Bssikka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 178 "Bssikka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 129;
#line 178 "Bssikka.sqc"
      sql_setdlist[5].sqldata = (void*)bssidt;
#line 178 "Bssikka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 178 "Bssikka.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 178 "Bssikka.sqc"
      sql_setdlist[6].sqldata = (void*)ksndh;
#line 178 "Bssikka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 178 "Bssikka.sqc"
      sqlasetdata(3,0,7,sql_setdlist,0L,0L);
    }
#line 178 "Bssikka.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 178 "Bssikka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 178 "Bssikka.sqc"
  sqlastop(0L);
}

#line 178 "Bssikka.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Bssikka*)ZbmlRealloc( array,
                                    sizeof( Bssikka ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Bssikka ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, BssikkaArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 193 "Bssikka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 193 "Bssikka.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 193 "Bssikka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 193 "Bssikka.sqc"
  sqlastop(0L);
}

#line 193 "Bssikka.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 201 "Bssikka.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbBssikkaInsert()
 *    BSSIKKA レコードを挿入する
 * ■引数
 *    [I]  Bssikka* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbBssikkaInsert( Bssikka* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, BssikkaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 224 "Bssikka.sqc"


    
/*
EXEC SQL INSERT INTO BSSIKKA
    (
		UTKYMD,
		IRINO,
		IRIKETFLG,
		BSSINO,
		GYONO,
		BSSIDT,
		KSNDH
    ) VALUES (
		:utkymd,
		:irino,
		:iriketflg,
		:bssino,
		:gyono,
		:bssidt,
		:ksndh
    );
*/

{
#line 243 "Bssikka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 243 "Bssikka.sqc"
  sqlaaloc(2,7,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 243 "Bssikka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 243 "Bssikka.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 243 "Bssikka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 243 "Bssikka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 243 "Bssikka.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 243 "Bssikka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 243 "Bssikka.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 243 "Bssikka.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 243 "Bssikka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 243 "Bssikka.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 243 "Bssikka.sqc"
      sql_setdlist[3].sqldata = (void*)&bssino;
#line 243 "Bssikka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 243 "Bssikka.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 243 "Bssikka.sqc"
      sql_setdlist[4].sqldata = (void*)&gyono;
#line 243 "Bssikka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 243 "Bssikka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 129;
#line 243 "Bssikka.sqc"
      sql_setdlist[5].sqldata = (void*)bssidt;
#line 243 "Bssikka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 243 "Bssikka.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 243 "Bssikka.sqc"
      sql_setdlist[6].sqldata = (void*)ksndh;
#line 243 "Bssikka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 243 "Bssikka.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 243 "Bssikka.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 243 "Bssikka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 243 "Bssikka.sqc"
  sqlastop(0L);
}

#line 243 "Bssikka.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 248 "Bssikka.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbBssikkaUpdate()
 *    BSSIKKA レコードを更新する
 * ■引数
 *    [I]  Bssikka* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbBssikkaUpdate( Bssikka* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, BssikkaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 272 "Bssikka.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 273 "Bssikka.sqc"


    
/*
EXEC SQL UPDATE BSSIKKA
    SET (
		IRIKETFLG,
		BSSIDT,
		KSNDH
    ) = (
		:iriketflg,
		:bssidt,
		:ksndh
    ) WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		BSSINO = :bssino AND
		GYONO = :gyono;
*/

{
#line 288 "Bssikka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 288 "Bssikka.sqc"
  sqlaaloc(2,7,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 288 "Bssikka.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 288 "Bssikka.sqc"
      sql_setdlist[0].sqldata = (void*)&iriketflg;
#line 288 "Bssikka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 288 "Bssikka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 129;
#line 288 "Bssikka.sqc"
      sql_setdlist[1].sqldata = (void*)bssidt;
#line 288 "Bssikka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 288 "Bssikka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 27;
#line 288 "Bssikka.sqc"
      sql_setdlist[2].sqldata = (void*)ksndh;
#line 288 "Bssikka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 288 "Bssikka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 288 "Bssikka.sqc"
      sql_setdlist[3].sqldata = (void*)utkymd;
#line 288 "Bssikka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 288 "Bssikka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 12;
#line 288 "Bssikka.sqc"
      sql_setdlist[4].sqldata = (void*)irino;
#line 288 "Bssikka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 288 "Bssikka.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 288 "Bssikka.sqc"
      sql_setdlist[5].sqldata = (void*)&bssino;
#line 288 "Bssikka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 288 "Bssikka.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 288 "Bssikka.sqc"
      sql_setdlist[6].sqldata = (void*)&gyono;
#line 288 "Bssikka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 288 "Bssikka.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 288 "Bssikka.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 288 "Bssikka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 288 "Bssikka.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 288 "Bssikka.sqc"
  sqlastop(0L);
}

#line 288 "Bssikka.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 293 "Bssikka.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 297 "Bssikka.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbBssikkaDelete()
 *    BSSIKKA レコードを削除する
 * ■引数
 *    [I]  Bssikka* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbBssikkaDelete( Bssikka* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, BssikkaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 321 "Bssikka.sqc"


    
/*
EXEC SQL DELETE FROM BSSIKKA
    WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		BSSINO = :bssino AND
		GYONO = :gyono;
*/

{
#line 328 "Bssikka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 328 "Bssikka.sqc"
  sqlaaloc(2,4,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 328 "Bssikka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 328 "Bssikka.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 328 "Bssikka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 328 "Bssikka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 328 "Bssikka.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 328 "Bssikka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 328 "Bssikka.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 328 "Bssikka.sqc"
      sql_setdlist[2].sqldata = (void*)&bssino;
#line 328 "Bssikka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 328 "Bssikka.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 328 "Bssikka.sqc"
      sql_setdlist[3].sqldata = (void*)&gyono;
#line 328 "Bssikka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 328 "Bssikka.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 328 "Bssikka.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 328 "Bssikka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 328 "Bssikka.sqc"
  sqlastop(0L);
}

#line 328 "Bssikka.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 333 "Bssikka.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
