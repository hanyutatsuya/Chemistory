static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,118,65,85,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,53,48,90,77,69,67,72,32,0,0,0,0,0,0,0,0,
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


#line 1 "Mechmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Mechmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Mechmst.h"
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


#line 24 "Mechmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Mechmst.sqc"

	char    bskkbn[5];
	char    nbkmcd[8];
	char    chnm[17];
	char    kmkcd[8];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 38 "Mechmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Mechmst

BmlDMMInfo	MechmstArray[] = {
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( nbkmcd ),
	DMM_SSTRING( chnm ),
	DMM_SSTRING( kmkcd ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbMechmstSelectAll()
 *    MECHMST レコード全件取得
 * ■引数
 *    [O]  Mechmst** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbMechmstSelectAll( Mechmst** arrayOut, int* numOut )
{
    Mechmst*    array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 74 "Mechmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		BSKKBN,
		NBKMCD,
		CHNM,
		KMKCD,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        MECHMST FOR READ ONLY;
*/

#line 87 "Mechmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 89 "Mechmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 89 "Mechmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 89 "Mechmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 89 "Mechmst.sqc"
  sqlastop(0L);
}

#line 89 "Mechmst.sqc"


    while( 1 ) {
        Mechmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:bskkbn,
			:nbkmcd,
			:chnm,
			:kmkcd,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 102 "Mechmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 102 "Mechmst.sqc"
  sqlaaloc(3,8,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 102 "Mechmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 102 "Mechmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 102 "Mechmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 102 "Mechmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 102 "Mechmst.sqc"
      sql_setdlist[1].sqldata = (void*)nbkmcd;
#line 102 "Mechmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 102 "Mechmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 17;
#line 102 "Mechmst.sqc"
      sql_setdlist[2].sqldata = (void*)chnm;
#line 102 "Mechmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 102 "Mechmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 102 "Mechmst.sqc"
      sql_setdlist[3].sqldata = (void*)kmkcd;
#line 102 "Mechmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 102 "Mechmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 102 "Mechmst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 102 "Mechmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 102 "Mechmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 102 "Mechmst.sqc"
      sql_setdlist[5].sqldata = (void*)haiymd;
#line 102 "Mechmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 102 "Mechmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 9;
#line 102 "Mechmst.sqc"
      sql_setdlist[6].sqldata = (void*)hnktntid;
#line 102 "Mechmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 102 "Mechmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 102 "Mechmst.sqc"
      sql_setdlist[7].sqldata = (void*)ksndh;
#line 102 "Mechmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 102 "Mechmst.sqc"
      sqlasetdata(3,0,8,sql_setdlist,0L,0L);
    }
#line 102 "Mechmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 102 "Mechmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 102 "Mechmst.sqc"
  sqlastop(0L);
}

#line 102 "Mechmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Mechmst*)ZbmlRealloc( array,
                                    sizeof( Mechmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Mechmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, MechmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 117 "Mechmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 117 "Mechmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 117 "Mechmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 117 "Mechmst.sqc"
  sqlastop(0L);
}

#line 117 "Mechmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 125 "Mechmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbMechmstSelectKey()
 *    MECHMST レコードKey条件取得
 * ■引数
 *    [I]  Mechmst* pKey       取得するレコードのキー
 *    [O]  Mechmst** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbMechmstSelectKey( Mechmst* pKey, Mechmst** arrayOut, int* numOut )
{
    Mechmst*    array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, MechmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 151 "Mechmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		BSKKBN,
		NBKMCD,
		CHNM,
		KMKCD,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        MECHMST
    WHERE
		BSKKBN = :bskkbn AND
		KMKCD = :kmkcd AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 168 "Mechmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 170 "Mechmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 170 "Mechmst.sqc"
  sqlaaloc(2,3,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 170 "Mechmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 170 "Mechmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 170 "Mechmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 170 "Mechmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 170 "Mechmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 170 "Mechmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 170 "Mechmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 170 "Mechmst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 170 "Mechmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 170 "Mechmst.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 170 "Mechmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 170 "Mechmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 170 "Mechmst.sqc"
  sqlastop(0L);
}

#line 170 "Mechmst.sqc"


    while( 1 ) {
        Mechmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:bskkbn,
			:nbkmcd,
			:chnm,
			:kmkcd,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 183 "Mechmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 183 "Mechmst.sqc"
  sqlaaloc(3,8,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 183 "Mechmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 183 "Mechmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 183 "Mechmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 183 "Mechmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 183 "Mechmst.sqc"
      sql_setdlist[1].sqldata = (void*)nbkmcd;
#line 183 "Mechmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 183 "Mechmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 17;
#line 183 "Mechmst.sqc"
      sql_setdlist[2].sqldata = (void*)chnm;
#line 183 "Mechmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 183 "Mechmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 183 "Mechmst.sqc"
      sql_setdlist[3].sqldata = (void*)kmkcd;
#line 183 "Mechmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 183 "Mechmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 183 "Mechmst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 183 "Mechmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 183 "Mechmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 183 "Mechmst.sqc"
      sql_setdlist[5].sqldata = (void*)haiymd;
#line 183 "Mechmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 183 "Mechmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 9;
#line 183 "Mechmst.sqc"
      sql_setdlist[6].sqldata = (void*)hnktntid;
#line 183 "Mechmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 183 "Mechmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 183 "Mechmst.sqc"
      sql_setdlist[7].sqldata = (void*)ksndh;
#line 183 "Mechmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 183 "Mechmst.sqc"
      sqlasetdata(3,0,8,sql_setdlist,0L,0L);
    }
#line 183 "Mechmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 183 "Mechmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 183 "Mechmst.sqc"
  sqlastop(0L);
}

#line 183 "Mechmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Mechmst*)ZbmlRealloc( array,
                                    sizeof( Mechmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Mechmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, MechmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 198 "Mechmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 198 "Mechmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 198 "Mechmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 198 "Mechmst.sqc"
  sqlastop(0L);
}

#line 198 "Mechmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 206 "Mechmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbMechmstInsert()
 *    MECHMST レコードを挿入する
 * ■引数
 *    [I]  Mechmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbMechmstInsert( Mechmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, MechmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 229 "Mechmst.sqc"


    
/*
EXEC SQL INSERT INTO MECHMST
    (
		BSKKBN,
		NBKMCD,
		CHNM,
		KMKCD,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:bskkbn,
		:nbkmcd,
		:chnm,
		:kmkcd,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 250 "Mechmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 250 "Mechmst.sqc"
  sqlaaloc(2,8,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 250 "Mechmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 250 "Mechmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 250 "Mechmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 250 "Mechmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 250 "Mechmst.sqc"
      sql_setdlist[1].sqldata = (void*)nbkmcd;
#line 250 "Mechmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 250 "Mechmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 17;
#line 250 "Mechmst.sqc"
      sql_setdlist[2].sqldata = (void*)chnm;
#line 250 "Mechmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 250 "Mechmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 250 "Mechmst.sqc"
      sql_setdlist[3].sqldata = (void*)kmkcd;
#line 250 "Mechmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 250 "Mechmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 250 "Mechmst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 250 "Mechmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 250 "Mechmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 250 "Mechmst.sqc"
      sql_setdlist[5].sqldata = (void*)haiymd;
#line 250 "Mechmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 250 "Mechmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 9;
#line 250 "Mechmst.sqc"
      sql_setdlist[6].sqldata = (void*)hnktntid;
#line 250 "Mechmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 250 "Mechmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 250 "Mechmst.sqc"
      sql_setdlist[7].sqldata = (void*)ksndh;
#line 250 "Mechmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 250 "Mechmst.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 250 "Mechmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 250 "Mechmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 250 "Mechmst.sqc"
  sqlastop(0L);
}

#line 250 "Mechmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 255 "Mechmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbMechmstUpdate()
 *    MECHMST レコードを更新する
 * ■引数
 *    [I]  Mechmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbMechmstUpdate( Mechmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, MechmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 279 "Mechmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 280 "Mechmst.sqc"


    
/*
EXEC SQL UPDATE MECHMST
    SET (
		NBKMCD,
		CHNM,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:nbkmcd,
		:chnm,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		BSKKBN = :bskkbn AND
		KMKCD = :kmkcd AND
		KAIYMD = :kaiymd;
*/

{
#line 298 "Mechmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 298 "Mechmst.sqc"
  sqlaaloc(2,8,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 298 "Mechmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 298 "Mechmst.sqc"
      sql_setdlist[0].sqldata = (void*)nbkmcd;
#line 298 "Mechmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 298 "Mechmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 298 "Mechmst.sqc"
      sql_setdlist[1].sqldata = (void*)chnm;
#line 298 "Mechmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 298 "Mechmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 298 "Mechmst.sqc"
      sql_setdlist[2].sqldata = (void*)haiymd;
#line 298 "Mechmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 298 "Mechmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 9;
#line 298 "Mechmst.sqc"
      sql_setdlist[3].sqldata = (void*)hnktntid;
#line 298 "Mechmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 298 "Mechmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 27;
#line 298 "Mechmst.sqc"
      sql_setdlist[4].sqldata = (void*)ksndh;
#line 298 "Mechmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 298 "Mechmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 5;
#line 298 "Mechmst.sqc"
      sql_setdlist[5].sqldata = (void*)bskkbn;
#line 298 "Mechmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 298 "Mechmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 298 "Mechmst.sqc"
      sql_setdlist[6].sqldata = (void*)kmkcd;
#line 298 "Mechmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 298 "Mechmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 298 "Mechmst.sqc"
      sql_setdlist[7].sqldata = (void*)kaiymd;
#line 298 "Mechmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 298 "Mechmst.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 298 "Mechmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 298 "Mechmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 298 "Mechmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 298 "Mechmst.sqc"
  sqlastop(0L);
}

#line 298 "Mechmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 303 "Mechmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 307 "Mechmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbMechmstDelete()
 *    MECHMST レコードを削除する
 * ■引数
 *    [I]  Mechmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbMechmstDelete( Mechmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, MechmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 331 "Mechmst.sqc"


    
/*
EXEC SQL DELETE FROM MECHMST
    WHERE
		BSKKBN = :bskkbn AND
		KMKCD = :kmkcd AND
		KAIYMD = :kaiymd;
*/

{
#line 337 "Mechmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 337 "Mechmst.sqc"
  sqlaaloc(2,3,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 337 "Mechmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 337 "Mechmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 337 "Mechmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 337 "Mechmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 337 "Mechmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 337 "Mechmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 337 "Mechmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 337 "Mechmst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 337 "Mechmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 337 "Mechmst.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 337 "Mechmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 337 "Mechmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 337 "Mechmst.sqc"
  sqlastop(0L);
}

#line 337 "Mechmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 342 "Mechmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
