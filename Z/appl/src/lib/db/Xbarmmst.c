static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,86,66,87,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,55,55,90,88,66,65,82,32,0,0,0,0,0,0,0,0,
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


#line 1 "Xbarmmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Xbarmmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Xbarmmst.h"
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


#line 24 "Xbarmmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Xbarmmst.sqc"

	char    knsgrp[17];
	char    kmkcd[8];
	char    minval[11];
	char    minart[11];
	char    avgval[11];
	char    maxart[11];
	char    maxval[11];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 41 "Xbarmmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Xbarmmst

BmlDMMInfo	XbarmmstArray[] = {
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( minval ),
	DMM_SSTRING( minart ),
	DMM_SSTRING( avgval ),
	DMM_SSTRING( maxart ),
	DMM_SSTRING( maxval ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbXbarmmstSelectAll()
 *    XBARMMST レコード全件取得
 * ■引数
 *    [O]  Xbarmmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbXbarmmstSelectAll( Xbarmmst** arrayOut, int* numOut )
{
    Xbarmmst*   array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 80 "Xbarmmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSGRP,
		KMKCD,
		MINVAL,
		MINART,
		AVGVAL,
		MAXART,
		MAXVAL,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        XBARMMST FOR READ ONLY;
*/

#line 96 "Xbarmmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 98 "Xbarmmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 98 "Xbarmmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 98 "Xbarmmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 98 "Xbarmmst.sqc"
  sqlastop(0L);
}

#line 98 "Xbarmmst.sqc"


    while( 1 ) {
        Xbarmmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knsgrp,
			:kmkcd,
			:minval,
			:minart,
			:avgval,
			:maxart,
			:maxval,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 114 "Xbarmmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 114 "Xbarmmst.sqc"
  sqlaaloc(3,11,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[11];
#line 114 "Xbarmmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[2].sqldata = (void*)minval;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[3].sqldata = (void*)minart;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[4].sqldata = (void*)avgval;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[5].sqldata = (void*)maxart;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[6].sqldata = (void*)maxval;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[7].sqldata = (void*)kaiymd;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[8].sqldata = (void*)haiymd;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 9;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[9].sqldata = (void*)hnktntid;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 27;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[10].sqldata = (void*)ksndh;
#line 114 "Xbarmmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 114 "Xbarmmst.sqc"
      sqlasetdata(3,0,11,sql_setdlist,0L,0L);
    }
#line 114 "Xbarmmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 114 "Xbarmmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 114 "Xbarmmst.sqc"
  sqlastop(0L);
}

#line 114 "Xbarmmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Xbarmmst*)ZbmlRealloc( array,
                                    sizeof( Xbarmmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Xbarmmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, XbarmmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 129 "Xbarmmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 129 "Xbarmmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 129 "Xbarmmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 129 "Xbarmmst.sqc"
  sqlastop(0L);
}

#line 129 "Xbarmmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 137 "Xbarmmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbXbarmmstSelectKey()
 *    XBARMMST レコードKey条件取得
 * ■引数
 *    [I]  Xbarmmst* pKey       取得するレコードのキー
 *    [O]  Xbarmmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbXbarmmstSelectKey( Xbarmmst* pKey, Xbarmmst** arrayOut, int* numOut )
{
    Xbarmmst*   array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, XbarmmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 163 "Xbarmmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSGRP,
		KMKCD,
		MINVAL,
		MINART,
		AVGVAL,
		MAXART,
		MAXVAL,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        XBARMMST
    WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 183 "Xbarmmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 185 "Xbarmmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 185 "Xbarmmst.sqc"
  sqlaaloc(2,3,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 185 "Xbarmmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 185 "Xbarmmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 185 "Xbarmmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 185 "Xbarmmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 185 "Xbarmmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 185 "Xbarmmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 185 "Xbarmmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 185 "Xbarmmst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 185 "Xbarmmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 185 "Xbarmmst.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 185 "Xbarmmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 185 "Xbarmmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 185 "Xbarmmst.sqc"
  sqlastop(0L);
}

#line 185 "Xbarmmst.sqc"


    while( 1 ) {
        Xbarmmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knsgrp,
			:kmkcd,
			:minval,
			:minart,
			:avgval,
			:maxart,
			:maxval,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 201 "Xbarmmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 201 "Xbarmmst.sqc"
  sqlaaloc(3,11,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[11];
#line 201 "Xbarmmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[2].sqldata = (void*)minval;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[3].sqldata = (void*)minart;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[4].sqldata = (void*)avgval;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[5].sqldata = (void*)maxart;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[6].sqldata = (void*)maxval;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[7].sqldata = (void*)kaiymd;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[8].sqldata = (void*)haiymd;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 9;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[9].sqldata = (void*)hnktntid;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 27;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[10].sqldata = (void*)ksndh;
#line 201 "Xbarmmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 201 "Xbarmmst.sqc"
      sqlasetdata(3,0,11,sql_setdlist,0L,0L);
    }
#line 201 "Xbarmmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 201 "Xbarmmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 201 "Xbarmmst.sqc"
  sqlastop(0L);
}

#line 201 "Xbarmmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Xbarmmst*)ZbmlRealloc( array,
                                    sizeof( Xbarmmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Xbarmmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, XbarmmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 216 "Xbarmmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 216 "Xbarmmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 216 "Xbarmmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 216 "Xbarmmst.sqc"
  sqlastop(0L);
}

#line 216 "Xbarmmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 224 "Xbarmmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbXbarmmstInsert()
 *    XBARMMST レコードを挿入する
 * ■引数
 *    [I]  Xbarmmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbXbarmmstInsert( Xbarmmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, XbarmmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 247 "Xbarmmst.sqc"


    
/*
EXEC SQL INSERT INTO XBARMMST
    (
		KNSGRP,
		KMKCD,
		MINVAL,
		MINART,
		AVGVAL,
		MAXART,
		MAXVAL,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:knsgrp,
		:kmkcd,
		:minval,
		:minart,
		:avgval,
		:maxart,
		:maxval,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 274 "Xbarmmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 274 "Xbarmmst.sqc"
  sqlaaloc(2,11,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[11];
#line 274 "Xbarmmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[2].sqldata = (void*)minval;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[3].sqldata = (void*)minart;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[4].sqldata = (void*)avgval;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[5].sqldata = (void*)maxart;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[6].sqldata = (void*)maxval;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[7].sqldata = (void*)kaiymd;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[8].sqldata = (void*)haiymd;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 9;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[9].sqldata = (void*)hnktntid;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 27;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[10].sqldata = (void*)ksndh;
#line 274 "Xbarmmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 274 "Xbarmmst.sqc"
      sqlasetdata(2,0,11,sql_setdlist,0L,0L);
    }
#line 274 "Xbarmmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 274 "Xbarmmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 274 "Xbarmmst.sqc"
  sqlastop(0L);
}

#line 274 "Xbarmmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 279 "Xbarmmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbXbarmmstUpdate()
 *    XBARMMST レコードを更新する
 * ■引数
 *    [I]  Xbarmmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbXbarmmstUpdate( Xbarmmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, XbarmmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 303 "Xbarmmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 304 "Xbarmmst.sqc"


    
/*
EXEC SQL UPDATE XBARMMST
    SET (
		MINVAL,
		MINART,
		AVGVAL,
		MAXART,
		MAXVAL,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:minval,
		:minart,
		:avgval,
		:maxart,
		:maxval,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KAIYMD = :kaiymd;
*/

{
#line 328 "Xbarmmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 328 "Xbarmmst.sqc"
  sqlaaloc(2,11,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[11];
#line 328 "Xbarmmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[0].sqldata = (void*)minval;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[1].sqldata = (void*)minart;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[2].sqldata = (void*)avgval;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[3].sqldata = (void*)maxart;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[4].sqldata = (void*)maxval;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[5].sqldata = (void*)haiymd;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 9;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[6].sqldata = (void*)hnktntid;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[7].sqldata = (void*)ksndh;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 17;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[8].sqldata = (void*)knsgrp;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 8;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[9].sqldata = (void*)kmkcd;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[10].sqldata = (void*)kaiymd;
#line 328 "Xbarmmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 328 "Xbarmmst.sqc"
      sqlasetdata(2,0,11,sql_setdlist,0L,0L);
    }
#line 328 "Xbarmmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 328 "Xbarmmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 328 "Xbarmmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 328 "Xbarmmst.sqc"
  sqlastop(0L);
}

#line 328 "Xbarmmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 333 "Xbarmmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 337 "Xbarmmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbXbarmmstDelete()
 *    XBARMMST レコードを削除する
 * ■引数
 *    [I]  Xbarmmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbXbarmmstDelete( Xbarmmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, XbarmmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 361 "Xbarmmst.sqc"


    
/*
EXEC SQL DELETE FROM XBARMMST
    WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KAIYMD = :kaiymd;
*/

{
#line 367 "Xbarmmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 367 "Xbarmmst.sqc"
  sqlaaloc(2,3,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 367 "Xbarmmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 367 "Xbarmmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 367 "Xbarmmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 367 "Xbarmmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 367 "Xbarmmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 367 "Xbarmmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 367 "Xbarmmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 367 "Xbarmmst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 367 "Xbarmmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 367 "Xbarmmst.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 367 "Xbarmmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 367 "Xbarmmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 367 "Xbarmmst.sqc"
  sqlastop(0L);
}

#line 367 "Xbarmmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 372 "Xbarmmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
