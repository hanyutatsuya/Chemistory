static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,74,65,85,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,52,53,90,75,78,83,83,32,0,0,0,0,0,0,0,0,
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


#line 1 "Knsseqknri.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Knsseqknri.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-03-23                    Create
 **********************************************************************/
#include <stdio.h>

#include "Knsseqknri.h"
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


#line 24 "Knsseqknri.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Knsseqknri.sqc"

	char    knskisymd[11];
	char    knsgrp[17];
	char    traykbn;
	char    wssbt[11];
	sqlint32  wsno;
	sqlint32  knsseqmax;
	sqlint32  sytrymax;
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 38 "Knsseqknri.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Knsseqknri

BmlDMMInfo	KnsseqknriArray[] = {
	DMM_SDATE( knskisymd ),
	DMM_SSTRING( knsgrp ),
	DMM_SCHAR( traykbn ),
	DMM_SSTRING( wssbt ),
	DMM_SLONG( wsno ),
	DMM_SLONG( knsseqmax ),
	DMM_SLONG( sytrymax ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKnsseqknriSelectAll()
 *    KNSSEQKNRI レコード全件取得
 * ■引数
 *    [O]  Knsseqknri** arrayOu 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKnsseqknriSelectAll( Knsseqknri** arrayOut, int* numOut )
{
    Knsseqknri* array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 74 "Knsseqknri.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSKISYMD,
		KNSGRP,
		TRAYKBN,
		WSSBT,
		WSNO,
		KNSSEQMAX,
		SYTRYMAX,
		KSNDH
    FROM
        KNSSEQKNRI FOR READ ONLY;
*/

#line 87 "Knsseqknri.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 89 "Knsseqknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 89 "Knsseqknri.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 89 "Knsseqknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 89 "Knsseqknri.sqc"
  sqlastop(0L);
}

#line 89 "Knsseqknri.sqc"


    while( 1 ) {
        Knsseqknri* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knskisymd,
			:knsgrp,
			:traykbn,
			:wssbt,
			:wsno,
			:knsseqmax,
			:sytrymax,
			:ksndh;
*/

{
#line 102 "Knsseqknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 102 "Knsseqknri.sqc"
  sqlaaloc(3,8,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 102 "Knsseqknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 102 "Knsseqknri.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 102 "Knsseqknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 102 "Knsseqknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 102 "Knsseqknri.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 102 "Knsseqknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 102 "Knsseqknri.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 102 "Knsseqknri.sqc"
      sql_setdlist[2].sqldata = (void*)&traykbn;
#line 102 "Knsseqknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 102 "Knsseqknri.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 102 "Knsseqknri.sqc"
      sql_setdlist[3].sqldata = (void*)wssbt;
#line 102 "Knsseqknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 102 "Knsseqknri.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 102 "Knsseqknri.sqc"
      sql_setdlist[4].sqldata = (void*)&wsno;
#line 102 "Knsseqknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 102 "Knsseqknri.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 102 "Knsseqknri.sqc"
      sql_setdlist[5].sqldata = (void*)&knsseqmax;
#line 102 "Knsseqknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 102 "Knsseqknri.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 102 "Knsseqknri.sqc"
      sql_setdlist[6].sqldata = (void*)&sytrymax;
#line 102 "Knsseqknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 102 "Knsseqknri.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 102 "Knsseqknri.sqc"
      sql_setdlist[7].sqldata = (void*)ksndh;
#line 102 "Knsseqknri.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 102 "Knsseqknri.sqc"
      sqlasetdata(3,0,8,sql_setdlist,0L,0L);
    }
#line 102 "Knsseqknri.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 102 "Knsseqknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 102 "Knsseqknri.sqc"
  sqlastop(0L);
}

#line 102 "Knsseqknri.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Knsseqknri*)ZbmlRealloc( array,
                                    sizeof( Knsseqknri ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Knsseqknri ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KnsseqknriArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 117 "Knsseqknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 117 "Knsseqknri.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 117 "Knsseqknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 117 "Knsseqknri.sqc"
  sqlastop(0L);
}

#line 117 "Knsseqknri.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 125 "Knsseqknri.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKnsseqknriSelectKey()
 *    KNSSEQKNRI レコードKey条件取得
 * ■引数
 *    [I]  Knsseqknri* pKey     取得するレコードのキー
 *    [O]  Knsseqknri** arrayOu 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKnsseqknriSelectKey( Knsseqknri* pKey, Knsseqknri** arrayOut, int* numOut )
{
    Knsseqknri* array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KnsseqknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 151 "Knsseqknri.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSKISYMD,
		KNSGRP,
		TRAYKBN,
		WSSBT,
		WSNO,
		KNSSEQMAX,
		SYTRYMAX,
		KSNDH
    FROM
        KNSSEQKNRI
    WHERE
		KNSKISYMD = :knskisymd AND
		KNSGRP         = :knsgrp         AND
		TRAYKBN = :traykbn FOR READ ONLY;
*/

#line 168 "Knsseqknri.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 170 "Knsseqknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 170 "Knsseqknri.sqc"
  sqlaaloc(2,3,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 170 "Knsseqknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 170 "Knsseqknri.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 170 "Knsseqknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 170 "Knsseqknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 170 "Knsseqknri.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 170 "Knsseqknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 170 "Knsseqknri.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 170 "Knsseqknri.sqc"
      sql_setdlist[2].sqldata = (void*)&traykbn;
#line 170 "Knsseqknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 170 "Knsseqknri.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 170 "Knsseqknri.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 170 "Knsseqknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 170 "Knsseqknri.sqc"
  sqlastop(0L);
}

#line 170 "Knsseqknri.sqc"


    while( 1 ) {
        Knsseqknri* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knskisymd,
			:knsgrp,
			:traykbn,
			:wssbt,
			:wsno,
			:knsseqmax,
			:sytrymax,
			:ksndh;
*/

{
#line 183 "Knsseqknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 183 "Knsseqknri.sqc"
  sqlaaloc(3,8,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 183 "Knsseqknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 183 "Knsseqknri.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 183 "Knsseqknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 183 "Knsseqknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 183 "Knsseqknri.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 183 "Knsseqknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 183 "Knsseqknri.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 183 "Knsseqknri.sqc"
      sql_setdlist[2].sqldata = (void*)&traykbn;
#line 183 "Knsseqknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 183 "Knsseqknri.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 183 "Knsseqknri.sqc"
      sql_setdlist[3].sqldata = (void*)wssbt;
#line 183 "Knsseqknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 183 "Knsseqknri.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 183 "Knsseqknri.sqc"
      sql_setdlist[4].sqldata = (void*)&wsno;
#line 183 "Knsseqknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 183 "Knsseqknri.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 183 "Knsseqknri.sqc"
      sql_setdlist[5].sqldata = (void*)&knsseqmax;
#line 183 "Knsseqknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 183 "Knsseqknri.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 183 "Knsseqknri.sqc"
      sql_setdlist[6].sqldata = (void*)&sytrymax;
#line 183 "Knsseqknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 183 "Knsseqknri.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 183 "Knsseqknri.sqc"
      sql_setdlist[7].sqldata = (void*)ksndh;
#line 183 "Knsseqknri.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 183 "Knsseqknri.sqc"
      sqlasetdata(3,0,8,sql_setdlist,0L,0L);
    }
#line 183 "Knsseqknri.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 183 "Knsseqknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 183 "Knsseqknri.sqc"
  sqlastop(0L);
}

#line 183 "Knsseqknri.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Knsseqknri*)ZbmlRealloc( array,
                                    sizeof( Knsseqknri ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Knsseqknri ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KnsseqknriArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 198 "Knsseqknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 198 "Knsseqknri.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 198 "Knsseqknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 198 "Knsseqknri.sqc"
  sqlastop(0L);
}

#line 198 "Knsseqknri.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 206 "Knsseqknri.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKnsseqknriInsert()
 *    KNSSEQKNRI レコードを挿入する
 * ■引数
 *    [I]  Knsseqknri* rec      挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKnsseqknriInsert( Knsseqknri* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KnsseqknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 229 "Knsseqknri.sqc"


    
/*
EXEC SQL INSERT INTO KNSSEQKNRI
    (
		KNSKISYMD,
		KNSGRP,
		TRAYKBN,
		WSSBT,
		WSNO,
		KNSSEQMAX,
		SYTRYMAX,
		KSNDH
    ) VALUES (
		:knskisymd,
		:knsgrp,
		:traykbn,
		:wssbt,
		:wsno,
		:knsseqmax,
		:sytrymax,
		CURRENT TIMESTAMP
    );
*/

{
#line 250 "Knsseqknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 250 "Knsseqknri.sqc"
  sqlaaloc(2,7,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 250 "Knsseqknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 250 "Knsseqknri.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 250 "Knsseqknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 250 "Knsseqknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 250 "Knsseqknri.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 250 "Knsseqknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 250 "Knsseqknri.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 250 "Knsseqknri.sqc"
      sql_setdlist[2].sqldata = (void*)&traykbn;
#line 250 "Knsseqknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 250 "Knsseqknri.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 250 "Knsseqknri.sqc"
      sql_setdlist[3].sqldata = (void*)wssbt;
#line 250 "Knsseqknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 250 "Knsseqknri.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 250 "Knsseqknri.sqc"
      sql_setdlist[4].sqldata = (void*)&wsno;
#line 250 "Knsseqknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 250 "Knsseqknri.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 250 "Knsseqknri.sqc"
      sql_setdlist[5].sqldata = (void*)&knsseqmax;
#line 250 "Knsseqknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 250 "Knsseqknri.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 250 "Knsseqknri.sqc"
      sql_setdlist[6].sqldata = (void*)&sytrymax;
#line 250 "Knsseqknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 250 "Knsseqknri.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 250 "Knsseqknri.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 250 "Knsseqknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 250 "Knsseqknri.sqc"
  sqlastop(0L);
}

#line 250 "Knsseqknri.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 255 "Knsseqknri.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKnsseqknriUpdate()
 *    KNSSEQKNRI レコードを更新する
 * ■引数
 *    [I]  Knsseqknri* rec      更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKnsseqknriUpdate( Knsseqknri* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KnsseqknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 279 "Knsseqknri.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 280 "Knsseqknri.sqc"


    
/*
EXEC SQL UPDATE KNSSEQKNRI
    SET (
		WSSBT,
		WSNO,
		KNSSEQMAX,
		SYTRYMAX,
		KSNDH
    ) = (
		:wssbt,
		:wsno,
		:knsseqmax,
		:sytrymax,
		CURRENT TIMESTAMP
    ) WHERE
		KNSKISYMD = :knskisymd AND
		KNSGRP         = :knsgrp         AND
		TRAYKBN = :traykbn;
*/

{
#line 298 "Knsseqknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 298 "Knsseqknri.sqc"
  sqlaaloc(2,7,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 298 "Knsseqknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 298 "Knsseqknri.sqc"
      sql_setdlist[0].sqldata = (void*)wssbt;
#line 298 "Knsseqknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 298 "Knsseqknri.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 298 "Knsseqknri.sqc"
      sql_setdlist[1].sqldata = (void*)&wsno;
#line 298 "Knsseqknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 298 "Knsseqknri.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 298 "Knsseqknri.sqc"
      sql_setdlist[2].sqldata = (void*)&knsseqmax;
#line 298 "Knsseqknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 298 "Knsseqknri.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 298 "Knsseqknri.sqc"
      sql_setdlist[3].sqldata = (void*)&sytrymax;
#line 298 "Knsseqknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 298 "Knsseqknri.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 298 "Knsseqknri.sqc"
      sql_setdlist[4].sqldata = (void*)knskisymd;
#line 298 "Knsseqknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 298 "Knsseqknri.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 17;
#line 298 "Knsseqknri.sqc"
      sql_setdlist[5].sqldata = (void*)knsgrp;
#line 298 "Knsseqknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 298 "Knsseqknri.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 298 "Knsseqknri.sqc"
      sql_setdlist[6].sqldata = (void*)&traykbn;
#line 298 "Knsseqknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 298 "Knsseqknri.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 298 "Knsseqknri.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 298 "Knsseqknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 298 "Knsseqknri.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 298 "Knsseqknri.sqc"
  sqlastop(0L);
}

#line 298 "Knsseqknri.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 303 "Knsseqknri.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 307 "Knsseqknri.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKnsseqknriDelete()
 *    KNSSEQKNRI レコードを削除する
 * ■引数
 *    [I]  Knsseqknri* rec      削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKnsseqknriDelete( Knsseqknri* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KnsseqknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 331 "Knsseqknri.sqc"


    
/*
EXEC SQL DELETE FROM KNSSEQKNRI
    WHERE
		KNSKISYMD = :knskisymd AND
		KNSGRP         = :knsgrp         AND
		TRAYKBN = :traykbn;
*/

{
#line 337 "Knsseqknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 337 "Knsseqknri.sqc"
  sqlaaloc(2,3,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 337 "Knsseqknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 337 "Knsseqknri.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 337 "Knsseqknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 337 "Knsseqknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 337 "Knsseqknri.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 337 "Knsseqknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 337 "Knsseqknri.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 337 "Knsseqknri.sqc"
      sql_setdlist[2].sqldata = (void*)&traykbn;
#line 337 "Knsseqknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 337 "Knsseqknri.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 337 "Knsseqknri.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 337 "Knsseqknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 337 "Knsseqknri.sqc"
  sqlastop(0L);
}

#line 337 "Knsseqknri.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 342 "Knsseqknri.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
