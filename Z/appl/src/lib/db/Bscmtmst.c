static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,55,65,81,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,53,90,66,83,67,77,32,32,0,0,0,0,0,0,0,0,
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


#line 1 "Bscmtmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Bscmtmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Bscmtmst.h"
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


#line 24 "Bscmtmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Bscmtmst.sqc"

	sqlint32  bscmtcd;
	sqlint32  gyono;
	char    bscmt[101];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 37 "Bscmtmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Bscmtmst

BmlDMMInfo	BscmtmstArray[] = {
	DMM_SLONG( bscmtcd ),
	DMM_SLONG( gyono ),
	DMM_SSTRING( bscmt ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbBscmtmstSelectAll()
 *    BSCMTMST レコード全件取得
 * ■引数
 *    [O]  Bscmtmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbBscmtmstSelectAll( Bscmtmst** arrayOut, int* numOut )
{
    Bscmtmst*   array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 72 "Bscmtmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		BSCMTCD,
		GYONO,
		BSCMT,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        BSCMTMST FOR READ ONLY;
*/

#line 84 "Bscmtmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 86 "Bscmtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 86 "Bscmtmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 86 "Bscmtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 86 "Bscmtmst.sqc"
  sqlastop(0L);
}

#line 86 "Bscmtmst.sqc"


    while( 1 ) {
        Bscmtmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:bscmtcd,
			:gyono,
			:bscmt,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 98 "Bscmtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 98 "Bscmtmst.sqc"
  sqlaaloc(3,7,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 98 "Bscmtmst.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 98 "Bscmtmst.sqc"
      sql_setdlist[0].sqldata = (void*)&bscmtcd;
#line 98 "Bscmtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 98 "Bscmtmst.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 98 "Bscmtmst.sqc"
      sql_setdlist[1].sqldata = (void*)&gyono;
#line 98 "Bscmtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 98 "Bscmtmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 101;
#line 98 "Bscmtmst.sqc"
      sql_setdlist[2].sqldata = (void*)bscmt;
#line 98 "Bscmtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 98 "Bscmtmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 98 "Bscmtmst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 98 "Bscmtmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 98 "Bscmtmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 98 "Bscmtmst.sqc"
      sql_setdlist[4].sqldata = (void*)haiymd;
#line 98 "Bscmtmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 98 "Bscmtmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 9;
#line 98 "Bscmtmst.sqc"
      sql_setdlist[5].sqldata = (void*)hnktntid;
#line 98 "Bscmtmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 98 "Bscmtmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 98 "Bscmtmst.sqc"
      sql_setdlist[6].sqldata = (void*)ksndh;
#line 98 "Bscmtmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 98 "Bscmtmst.sqc"
      sqlasetdata(3,0,7,sql_setdlist,0L,0L);
    }
#line 98 "Bscmtmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 98 "Bscmtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 98 "Bscmtmst.sqc"
  sqlastop(0L);
}

#line 98 "Bscmtmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Bscmtmst*)ZbmlRealloc( array,
                                    sizeof( Bscmtmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Bscmtmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, BscmtmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 113 "Bscmtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 113 "Bscmtmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 113 "Bscmtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 113 "Bscmtmst.sqc"
  sqlastop(0L);
}

#line 113 "Bscmtmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 121 "Bscmtmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbBscmtmstSelectKey()
 *    BSCMTMST レコードKey条件取得
 * ■引数
 *    [I]  Bscmtmst* pKey       取得するレコードのキー
 *    [O]  Bscmtmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbBscmtmstSelectKey( Bscmtmst* pKey, Bscmtmst** arrayOut, int* numOut )
{
    Bscmtmst*   array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, BscmtmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 147 "Bscmtmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		BSCMTCD,
		GYONO,
		BSCMT,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        BSCMTMST
    WHERE
		BSCMTCD = :bscmtcd AND
		GYONO = :gyono AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 163 "Bscmtmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 165 "Bscmtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 165 "Bscmtmst.sqc"
  sqlaaloc(2,3,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 165 "Bscmtmst.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 165 "Bscmtmst.sqc"
      sql_setdlist[0].sqldata = (void*)&bscmtcd;
#line 165 "Bscmtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 165 "Bscmtmst.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 165 "Bscmtmst.sqc"
      sql_setdlist[1].sqldata = (void*)&gyono;
#line 165 "Bscmtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 165 "Bscmtmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 165 "Bscmtmst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 165 "Bscmtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 165 "Bscmtmst.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 165 "Bscmtmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 165 "Bscmtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 165 "Bscmtmst.sqc"
  sqlastop(0L);
}

#line 165 "Bscmtmst.sqc"


    while( 1 ) {
        Bscmtmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:bscmtcd,
			:gyono,
			:bscmt,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 177 "Bscmtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 177 "Bscmtmst.sqc"
  sqlaaloc(3,7,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 177 "Bscmtmst.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 177 "Bscmtmst.sqc"
      sql_setdlist[0].sqldata = (void*)&bscmtcd;
#line 177 "Bscmtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 177 "Bscmtmst.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 177 "Bscmtmst.sqc"
      sql_setdlist[1].sqldata = (void*)&gyono;
#line 177 "Bscmtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 177 "Bscmtmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 101;
#line 177 "Bscmtmst.sqc"
      sql_setdlist[2].sqldata = (void*)bscmt;
#line 177 "Bscmtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 177 "Bscmtmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 177 "Bscmtmst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 177 "Bscmtmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 177 "Bscmtmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 177 "Bscmtmst.sqc"
      sql_setdlist[4].sqldata = (void*)haiymd;
#line 177 "Bscmtmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 177 "Bscmtmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 9;
#line 177 "Bscmtmst.sqc"
      sql_setdlist[5].sqldata = (void*)hnktntid;
#line 177 "Bscmtmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 177 "Bscmtmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 177 "Bscmtmst.sqc"
      sql_setdlist[6].sqldata = (void*)ksndh;
#line 177 "Bscmtmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 177 "Bscmtmst.sqc"
      sqlasetdata(3,0,7,sql_setdlist,0L,0L);
    }
#line 177 "Bscmtmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 177 "Bscmtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 177 "Bscmtmst.sqc"
  sqlastop(0L);
}

#line 177 "Bscmtmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Bscmtmst*)ZbmlRealloc( array,
                                    sizeof( Bscmtmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Bscmtmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, BscmtmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 192 "Bscmtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 192 "Bscmtmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 192 "Bscmtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 192 "Bscmtmst.sqc"
  sqlastop(0L);
}

#line 192 "Bscmtmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 200 "Bscmtmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbBscmtmstInsert()
 *    BSCMTMST レコードを挿入する
 * ■引数
 *    [I]  Bscmtmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbBscmtmstInsert( Bscmtmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, BscmtmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 223 "Bscmtmst.sqc"


    
/*
EXEC SQL INSERT INTO BSCMTMST
    (
		BSCMTCD,
		GYONO,
		BSCMT,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:bscmtcd,
		:gyono,
		:bscmt,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 242 "Bscmtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 242 "Bscmtmst.sqc"
  sqlaaloc(2,7,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 242 "Bscmtmst.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 242 "Bscmtmst.sqc"
      sql_setdlist[0].sqldata = (void*)&bscmtcd;
#line 242 "Bscmtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 242 "Bscmtmst.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 242 "Bscmtmst.sqc"
      sql_setdlist[1].sqldata = (void*)&gyono;
#line 242 "Bscmtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 242 "Bscmtmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 101;
#line 242 "Bscmtmst.sqc"
      sql_setdlist[2].sqldata = (void*)bscmt;
#line 242 "Bscmtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 242 "Bscmtmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 242 "Bscmtmst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 242 "Bscmtmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 242 "Bscmtmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 242 "Bscmtmst.sqc"
      sql_setdlist[4].sqldata = (void*)haiymd;
#line 242 "Bscmtmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 242 "Bscmtmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 9;
#line 242 "Bscmtmst.sqc"
      sql_setdlist[5].sqldata = (void*)hnktntid;
#line 242 "Bscmtmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 242 "Bscmtmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 242 "Bscmtmst.sqc"
      sql_setdlist[6].sqldata = (void*)ksndh;
#line 242 "Bscmtmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 242 "Bscmtmst.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 242 "Bscmtmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 242 "Bscmtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 242 "Bscmtmst.sqc"
  sqlastop(0L);
}

#line 242 "Bscmtmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 247 "Bscmtmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbBscmtmstUpdate()
 *    BSCMTMST レコードを更新する
 * ■引数
 *    [I]  Bscmtmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbBscmtmstUpdate( Bscmtmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, BscmtmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 271 "Bscmtmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 272 "Bscmtmst.sqc"


    
/*
EXEC SQL UPDATE BSCMTMST
    SET (
		BSCMT,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:bscmt,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		BSCMTCD = :bscmtcd AND
		GYONO = :gyono AND
		KAIYMD = :kaiymd;
*/

{
#line 288 "Bscmtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 288 "Bscmtmst.sqc"
  sqlaaloc(2,7,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 288 "Bscmtmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 101;
#line 288 "Bscmtmst.sqc"
      sql_setdlist[0].sqldata = (void*)bscmt;
#line 288 "Bscmtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 288 "Bscmtmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 288 "Bscmtmst.sqc"
      sql_setdlist[1].sqldata = (void*)haiymd;
#line 288 "Bscmtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 288 "Bscmtmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 9;
#line 288 "Bscmtmst.sqc"
      sql_setdlist[2].sqldata = (void*)hnktntid;
#line 288 "Bscmtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 288 "Bscmtmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 27;
#line 288 "Bscmtmst.sqc"
      sql_setdlist[3].sqldata = (void*)ksndh;
#line 288 "Bscmtmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 288 "Bscmtmst.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 288 "Bscmtmst.sqc"
      sql_setdlist[4].sqldata = (void*)&bscmtcd;
#line 288 "Bscmtmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 288 "Bscmtmst.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 288 "Bscmtmst.sqc"
      sql_setdlist[5].sqldata = (void*)&gyono;
#line 288 "Bscmtmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 288 "Bscmtmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 288 "Bscmtmst.sqc"
      sql_setdlist[6].sqldata = (void*)kaiymd;
#line 288 "Bscmtmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 288 "Bscmtmst.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 288 "Bscmtmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 288 "Bscmtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 288 "Bscmtmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 288 "Bscmtmst.sqc"
  sqlastop(0L);
}

#line 288 "Bscmtmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 293 "Bscmtmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 297 "Bscmtmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbBscmtmstDelete()
 *    BSCMTMST レコードを削除する
 * ■引数
 *    [I]  Bscmtmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbBscmtmstDelete( Bscmtmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, BscmtmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 321 "Bscmtmst.sqc"


    
/*
EXEC SQL DELETE FROM BSCMTMST
    WHERE
		BSCMTCD = :bscmtcd AND
		GYONO = :gyono AND
		KAIYMD = :kaiymd;
*/

{
#line 327 "Bscmtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 327 "Bscmtmst.sqc"
  sqlaaloc(2,3,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 327 "Bscmtmst.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 327 "Bscmtmst.sqc"
      sql_setdlist[0].sqldata = (void*)&bscmtcd;
#line 327 "Bscmtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 327 "Bscmtmst.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 327 "Bscmtmst.sqc"
      sql_setdlist[1].sqldata = (void*)&gyono;
#line 327 "Bscmtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 327 "Bscmtmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 327 "Bscmtmst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 327 "Bscmtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 327 "Bscmtmst.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 327 "Bscmtmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 327 "Bscmtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 327 "Bscmtmst.sqc"
  sqlastop(0L);
}

#line 327 "Bscmtmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 332 "Bscmtmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
