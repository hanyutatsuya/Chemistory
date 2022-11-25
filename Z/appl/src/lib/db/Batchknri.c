static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,120,65,81,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,52,90,66,65,84,67,32,32,0,0,0,0,0,0,0,0,
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


#line 1 "Batchknri.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Batchknri.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Batchknri.h"
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


#line 24 "Batchknri.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Batchknri.sqc"

	char    knskisymd[11];
	char    bskkbn[11];
	char    bsklne[11];
	char    bskgok[6];
	char    bskmjno[6];
	char    knsgrp[11];
	sqlint32  bthno;
	char    lotno[11];
	char    bthjkflg;
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 40 "Batchknri.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Batchknri

BmlDMMInfo	BatchknriArray[] = {
	DMM_SDATE( knskisymd ),
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( bsklne ),
	DMM_SSTRING( bskgok ),
	DMM_SSTRING( bskmjno ),
	DMM_SSTRING( knsgrp ),
	DMM_SLONG( bthno ),
	DMM_SSTRING( lotno ),
	DMM_SCHAR( bthjkflg ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbBatchknriSelectAll()
 *    BATCHKNRI レコード全件取得
 * ■引数
 *    [O]  Batchknri** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbBatchknriSelectAll( Batchknri** arrayOut, int* numOut )
{
    Batchknri*  array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 78 "Batchknri.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSKISYMD,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		BSKMJNO,
		KNSGRP,
		BTHNO,
		LOTNO,
		BTHJKFLG,
		KSNDH
    FROM
        BATCHKNRI FOR READ ONLY;
*/

#line 93 "Batchknri.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 95 "Batchknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 95 "Batchknri.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 95 "Batchknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 95 "Batchknri.sqc"
  sqlastop(0L);
}

#line 95 "Batchknri.sqc"


    while( 1 ) {
        Batchknri* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knskisymd,
			:bskkbn,
			:bsklne,
			:bskgok,
			:bskmjno,
			:knsgrp,
			:bthno,
			:lotno,
			:bthjkflg,
			:ksndh;
*/

{
#line 110 "Batchknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 110 "Batchknri.sqc"
  sqlaaloc(3,10,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 110 "Batchknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 110 "Batchknri.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 110 "Batchknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 110 "Batchknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 110 "Batchknri.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 110 "Batchknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 110 "Batchknri.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 110 "Batchknri.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 110 "Batchknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 110 "Batchknri.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 6;
#line 110 "Batchknri.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 110 "Batchknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 110 "Batchknri.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 6;
#line 110 "Batchknri.sqc"
      sql_setdlist[4].sqldata = (void*)bskmjno;
#line 110 "Batchknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 110 "Batchknri.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 110 "Batchknri.sqc"
      sql_setdlist[5].sqldata = (void*)knsgrp;
#line 110 "Batchknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 110 "Batchknri.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 110 "Batchknri.sqc"
      sql_setdlist[6].sqldata = (void*)&bthno;
#line 110 "Batchknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 110 "Batchknri.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 110 "Batchknri.sqc"
      sql_setdlist[7].sqldata = (void*)lotno;
#line 110 "Batchknri.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 110 "Batchknri.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 110 "Batchknri.sqc"
      sql_setdlist[8].sqldata = (void*)&bthjkflg;
#line 110 "Batchknri.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 110 "Batchknri.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 110 "Batchknri.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 110 "Batchknri.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 110 "Batchknri.sqc"
      sqlasetdata(3,0,10,sql_setdlist,0L,0L);
    }
#line 110 "Batchknri.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 110 "Batchknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 110 "Batchknri.sqc"
  sqlastop(0L);
}

#line 110 "Batchknri.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Batchknri*)ZbmlRealloc( array,
                                    sizeof( Batchknri ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Batchknri ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, BatchknriArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 125 "Batchknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 125 "Batchknri.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 125 "Batchknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 125 "Batchknri.sqc"
  sqlastop(0L);
}

#line 125 "Batchknri.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 133 "Batchknri.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbBatchknriSelectKey()
 *    BATCHKNRI レコードKey条件取得
 * ■引数
 *    [I]  Batchknri* pKey      取得するレコードのキー
 *    [O]  Batchknri** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbBatchknriSelectKey( Batchknri* pKey, Batchknri** arrayOut, int* numOut )
{
    Batchknri*  array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, BatchknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 159 "Batchknri.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSKISYMD,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		BSKMJNO,
		KNSGRP,
		BTHNO,
		LOTNO,
		BTHJKFLG,
		KSNDH
    FROM
        BATCHKNRI
    WHERE
		KNSKISYMD = :knskisymd AND
		BSKKBN = :bskkbn AND
		BSKLNE = :bsklne AND
		BSKGOK = :bskgok AND
		BSKMJNO = :bskmjno AND
		KNSGRP         = :knsgrp         AND
		BTHNO = :bthno FOR READ ONLY;
*/

#line 182 "Batchknri.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 184 "Batchknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 184 "Batchknri.sqc"
  sqlaaloc(2,7,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 184 "Batchknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 184 "Batchknri.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 184 "Batchknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 184 "Batchknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 184 "Batchknri.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 184 "Batchknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 184 "Batchknri.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 184 "Batchknri.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 184 "Batchknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 184 "Batchknri.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 6;
#line 184 "Batchknri.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 184 "Batchknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 184 "Batchknri.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 6;
#line 184 "Batchknri.sqc"
      sql_setdlist[4].sqldata = (void*)bskmjno;
#line 184 "Batchknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 184 "Batchknri.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 184 "Batchknri.sqc"
      sql_setdlist[5].sqldata = (void*)knsgrp;
#line 184 "Batchknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 184 "Batchknri.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 184 "Batchknri.sqc"
      sql_setdlist[6].sqldata = (void*)&bthno;
#line 184 "Batchknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 184 "Batchknri.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 184 "Batchknri.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 184 "Batchknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 184 "Batchknri.sqc"
  sqlastop(0L);
}

#line 184 "Batchknri.sqc"


    while( 1 ) {
        Batchknri* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knskisymd,
			:bskkbn,
			:bsklne,
			:bskgok,
			:bskmjno,
			:knsgrp,
			:bthno,
			:lotno,
			:bthjkflg,
			:ksndh;
*/

{
#line 199 "Batchknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 199 "Batchknri.sqc"
  sqlaaloc(3,10,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 199 "Batchknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 199 "Batchknri.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 199 "Batchknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 199 "Batchknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 199 "Batchknri.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 199 "Batchknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 199 "Batchknri.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 199 "Batchknri.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 199 "Batchknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 199 "Batchknri.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 6;
#line 199 "Batchknri.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 199 "Batchknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 199 "Batchknri.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 6;
#line 199 "Batchknri.sqc"
      sql_setdlist[4].sqldata = (void*)bskmjno;
#line 199 "Batchknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 199 "Batchknri.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 199 "Batchknri.sqc"
      sql_setdlist[5].sqldata = (void*)knsgrp;
#line 199 "Batchknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 199 "Batchknri.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 199 "Batchknri.sqc"
      sql_setdlist[6].sqldata = (void*)&bthno;
#line 199 "Batchknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 199 "Batchknri.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 199 "Batchknri.sqc"
      sql_setdlist[7].sqldata = (void*)lotno;
#line 199 "Batchknri.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 199 "Batchknri.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 199 "Batchknri.sqc"
      sql_setdlist[8].sqldata = (void*)&bthjkflg;
#line 199 "Batchknri.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 199 "Batchknri.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 199 "Batchknri.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 199 "Batchknri.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 199 "Batchknri.sqc"
      sqlasetdata(3,0,10,sql_setdlist,0L,0L);
    }
#line 199 "Batchknri.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 199 "Batchknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 199 "Batchknri.sqc"
  sqlastop(0L);
}

#line 199 "Batchknri.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Batchknri*)ZbmlRealloc( array,
                                    sizeof( Batchknri ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Batchknri ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, BatchknriArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 214 "Batchknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 214 "Batchknri.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 214 "Batchknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 214 "Batchknri.sqc"
  sqlastop(0L);
}

#line 214 "Batchknri.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 222 "Batchknri.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbBatchknriInsert()
 *    BATCHKNRI レコードを挿入する
 * ■引数
 *    [I]  Batchknri* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbBatchknriInsert( Batchknri* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, BatchknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 245 "Batchknri.sqc"


    
/*
EXEC SQL INSERT INTO BATCHKNRI
    (
		KNSKISYMD,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		BSKMJNO,
		KNSGRP,
		BTHNO,
		LOTNO,
		BTHJKFLG,
		KSNDH
    ) VALUES (
		:knskisymd,
		:bskkbn,
		:bsklne,
		:bskgok,
		:bskmjno,
		:knsgrp,
		:bthno,
		:lotno,
		:bthjkflg,
		:ksndh
    );
*/

{
#line 270 "Batchknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 270 "Batchknri.sqc"
  sqlaaloc(2,10,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 270 "Batchknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 270 "Batchknri.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 270 "Batchknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 270 "Batchknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 270 "Batchknri.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 270 "Batchknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 270 "Batchknri.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 270 "Batchknri.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 270 "Batchknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 270 "Batchknri.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 6;
#line 270 "Batchknri.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 270 "Batchknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 270 "Batchknri.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 6;
#line 270 "Batchknri.sqc"
      sql_setdlist[4].sqldata = (void*)bskmjno;
#line 270 "Batchknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 270 "Batchknri.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 270 "Batchknri.sqc"
      sql_setdlist[5].sqldata = (void*)knsgrp;
#line 270 "Batchknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 270 "Batchknri.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 270 "Batchknri.sqc"
      sql_setdlist[6].sqldata = (void*)&bthno;
#line 270 "Batchknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 270 "Batchknri.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 270 "Batchknri.sqc"
      sql_setdlist[7].sqldata = (void*)lotno;
#line 270 "Batchknri.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 270 "Batchknri.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 270 "Batchknri.sqc"
      sql_setdlist[8].sqldata = (void*)&bthjkflg;
#line 270 "Batchknri.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 270 "Batchknri.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 270 "Batchknri.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 270 "Batchknri.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 270 "Batchknri.sqc"
      sqlasetdata(2,0,10,sql_setdlist,0L,0L);
    }
#line 270 "Batchknri.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 270 "Batchknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 270 "Batchknri.sqc"
  sqlastop(0L);
}

#line 270 "Batchknri.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 275 "Batchknri.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbBatchknriUpdate()
 *    BATCHKNRI レコードを更新する
 * ■引数
 *    [I]  Batchknri* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbBatchknriUpdate( Batchknri* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, BatchknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 299 "Batchknri.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 300 "Batchknri.sqc"


    
/*
EXEC SQL UPDATE BATCHKNRI
    SET (
		LOTNO,
		BTHJKFLG,
		KSNDH
    ) = (
		:lotno,
		:bthjkflg,
		:ksndh
    ) WHERE
		KNSKISYMD = :knskisymd AND
		BSKKBN = :bskkbn AND
		BSKLNE = :bsklne AND
		BSKGOK = :bskgok AND
		BSKMJNO = :bskmjno AND
		KNSGRP         = :knsgrp         AND
		BTHNO = :bthno;
*/

{
#line 318 "Batchknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 318 "Batchknri.sqc"
  sqlaaloc(2,10,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 318 "Batchknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 318 "Batchknri.sqc"
      sql_setdlist[0].sqldata = (void*)lotno;
#line 318 "Batchknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 318 "Batchknri.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 318 "Batchknri.sqc"
      sql_setdlist[1].sqldata = (void*)&bthjkflg;
#line 318 "Batchknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 318 "Batchknri.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 27;
#line 318 "Batchknri.sqc"
      sql_setdlist[2].sqldata = (void*)ksndh;
#line 318 "Batchknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 318 "Batchknri.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 318 "Batchknri.sqc"
      sql_setdlist[3].sqldata = (void*)knskisymd;
#line 318 "Batchknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 318 "Batchknri.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 318 "Batchknri.sqc"
      sql_setdlist[4].sqldata = (void*)bskkbn;
#line 318 "Batchknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 318 "Batchknri.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 318 "Batchknri.sqc"
      sql_setdlist[5].sqldata = (void*)bsklne;
#line 318 "Batchknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 318 "Batchknri.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 6;
#line 318 "Batchknri.sqc"
      sql_setdlist[6].sqldata = (void*)bskgok;
#line 318 "Batchknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 318 "Batchknri.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 6;
#line 318 "Batchknri.sqc"
      sql_setdlist[7].sqldata = (void*)bskmjno;
#line 318 "Batchknri.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 318 "Batchknri.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 318 "Batchknri.sqc"
      sql_setdlist[8].sqldata = (void*)knsgrp;
#line 318 "Batchknri.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 318 "Batchknri.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 318 "Batchknri.sqc"
      sql_setdlist[9].sqldata = (void*)&bthno;
#line 318 "Batchknri.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 318 "Batchknri.sqc"
      sqlasetdata(2,0,10,sql_setdlist,0L,0L);
    }
#line 318 "Batchknri.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 318 "Batchknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 318 "Batchknri.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 318 "Batchknri.sqc"
  sqlastop(0L);
}

#line 318 "Batchknri.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 323 "Batchknri.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 327 "Batchknri.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbBatchknriDelete()
 *    BATCHKNRI レコードを削除する
 * ■引数
 *    [I]  Batchknri* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbBatchknriDelete( Batchknri* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, BatchknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 351 "Batchknri.sqc"


    
/*
EXEC SQL DELETE FROM BATCHKNRI
    WHERE
		KNSKISYMD = :knskisymd AND
		BSKKBN = :bskkbn AND
		BSKLNE = :bsklne AND
		BSKGOK = :bskgok AND
		BSKMJNO = :bskmjno AND
		KNSGRP         = :knsgrp         AND
		BTHNO = :bthno;
*/

{
#line 361 "Batchknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 361 "Batchknri.sqc"
  sqlaaloc(2,7,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 361 "Batchknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 361 "Batchknri.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 361 "Batchknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 361 "Batchknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 361 "Batchknri.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 361 "Batchknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 361 "Batchknri.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 361 "Batchknri.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 361 "Batchknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 361 "Batchknri.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 6;
#line 361 "Batchknri.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 361 "Batchknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 361 "Batchknri.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 6;
#line 361 "Batchknri.sqc"
      sql_setdlist[4].sqldata = (void*)bskmjno;
#line 361 "Batchknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 361 "Batchknri.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 361 "Batchknri.sqc"
      sql_setdlist[5].sqldata = (void*)knsgrp;
#line 361 "Batchknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 361 "Batchknri.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 361 "Batchknri.sqc"
      sql_setdlist[6].sqldata = (void*)&bthno;
#line 361 "Batchknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 361 "Batchknri.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 361 "Batchknri.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 361 "Batchknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 361 "Batchknri.sqc"
  sqlastop(0L);
}

#line 361 "Batchknri.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 366 "Batchknri.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
