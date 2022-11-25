static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,108,65,84,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,51,55,90,75,75,65,72,32,0,0,0,0,0,0,0,0,
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


#line 1 "Kkahskmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Kkahskmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Kkahskmst.h"
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


#line 24 "Kkahskmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Kkahskmst.sqc"

	char    kkahskcd[4];
	char    kkahsknm[17];
	char    kkahsknmj[33];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 37 "Kkahskmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Kkahskmst

BmlDMMInfo	KkahskmstArray[] = {
	DMM_SSTRING( kkahskcd ),
	DMM_SSTRING( kkahsknm ),
	DMM_SSTRING( kkahsknmj ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKkahskmstSelectAll()
 *    KKAHSKMST レコード全件取得
 * ■引数
 *    [O]  Kkahskmst** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKkahskmstSelectAll( Kkahskmst** arrayOut, int* numOut )
{
    Kkahskmst*  array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 72 "Kkahskmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KKAHSKCD,
		KKAHSKNM,
		KKAHSKNMJ,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        KKAHSKMST FOR READ ONLY;
*/

#line 84 "Kkahskmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 86 "Kkahskmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 86 "Kkahskmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 86 "Kkahskmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 86 "Kkahskmst.sqc"
  sqlastop(0L);
}

#line 86 "Kkahskmst.sqc"


    while( 1 ) {
        Kkahskmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:kkahskcd,
			:kkahsknm,
			:kkahsknmj,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 98 "Kkahskmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 98 "Kkahskmst.sqc"
  sqlaaloc(3,7,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 98 "Kkahskmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 4;
#line 98 "Kkahskmst.sqc"
      sql_setdlist[0].sqldata = (void*)kkahskcd;
#line 98 "Kkahskmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 98 "Kkahskmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 98 "Kkahskmst.sqc"
      sql_setdlist[1].sqldata = (void*)kkahsknm;
#line 98 "Kkahskmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 98 "Kkahskmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 33;
#line 98 "Kkahskmst.sqc"
      sql_setdlist[2].sqldata = (void*)kkahsknmj;
#line 98 "Kkahskmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 98 "Kkahskmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 98 "Kkahskmst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 98 "Kkahskmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 98 "Kkahskmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 98 "Kkahskmst.sqc"
      sql_setdlist[4].sqldata = (void*)haiymd;
#line 98 "Kkahskmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 98 "Kkahskmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 9;
#line 98 "Kkahskmst.sqc"
      sql_setdlist[5].sqldata = (void*)hnktntid;
#line 98 "Kkahskmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 98 "Kkahskmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 98 "Kkahskmst.sqc"
      sql_setdlist[6].sqldata = (void*)ksndh;
#line 98 "Kkahskmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 98 "Kkahskmst.sqc"
      sqlasetdata(3,0,7,sql_setdlist,0L,0L);
    }
#line 98 "Kkahskmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 98 "Kkahskmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 98 "Kkahskmst.sqc"
  sqlastop(0L);
}

#line 98 "Kkahskmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kkahskmst*)ZbmlRealloc( array,
                                    sizeof( Kkahskmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kkahskmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KkahskmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 113 "Kkahskmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 113 "Kkahskmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 113 "Kkahskmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 113 "Kkahskmst.sqc"
  sqlastop(0L);
}

#line 113 "Kkahskmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 121 "Kkahskmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKkahskmstSelectKey()
 *    KKAHSKMST レコードKey条件取得
 * ■引数
 *    [I]  Kkahskmst* pKey      取得するレコードのキー
 *    [O]  Kkahskmst** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKkahskmstSelectKey( Kkahskmst* pKey, Kkahskmst** arrayOut, int* numOut )
{
    Kkahskmst*  array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KkahskmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 147 "Kkahskmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KKAHSKCD,
		KKAHSKNM,
		KKAHSKNMJ,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        KKAHSKMST
    WHERE
		KKAHSKCD = :kkahskcd AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 162 "Kkahskmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 164 "Kkahskmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 164 "Kkahskmst.sqc"
  sqlaaloc(2,2,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 164 "Kkahskmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 4;
#line 164 "Kkahskmst.sqc"
      sql_setdlist[0].sqldata = (void*)kkahskcd;
#line 164 "Kkahskmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 164 "Kkahskmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 164 "Kkahskmst.sqc"
      sql_setdlist[1].sqldata = (void*)kaiymd;
#line 164 "Kkahskmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 164 "Kkahskmst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 164 "Kkahskmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 164 "Kkahskmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 164 "Kkahskmst.sqc"
  sqlastop(0L);
}

#line 164 "Kkahskmst.sqc"


    while( 1 ) {
        Kkahskmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:kkahskcd,
			:kkahsknm,
			:kkahsknmj,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 176 "Kkahskmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 176 "Kkahskmst.sqc"
  sqlaaloc(3,7,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 176 "Kkahskmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 4;
#line 176 "Kkahskmst.sqc"
      sql_setdlist[0].sqldata = (void*)kkahskcd;
#line 176 "Kkahskmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 176 "Kkahskmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 176 "Kkahskmst.sqc"
      sql_setdlist[1].sqldata = (void*)kkahsknm;
#line 176 "Kkahskmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 176 "Kkahskmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 33;
#line 176 "Kkahskmst.sqc"
      sql_setdlist[2].sqldata = (void*)kkahsknmj;
#line 176 "Kkahskmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 176 "Kkahskmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 176 "Kkahskmst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 176 "Kkahskmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 176 "Kkahskmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 176 "Kkahskmst.sqc"
      sql_setdlist[4].sqldata = (void*)haiymd;
#line 176 "Kkahskmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 176 "Kkahskmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 9;
#line 176 "Kkahskmst.sqc"
      sql_setdlist[5].sqldata = (void*)hnktntid;
#line 176 "Kkahskmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 176 "Kkahskmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 176 "Kkahskmst.sqc"
      sql_setdlist[6].sqldata = (void*)ksndh;
#line 176 "Kkahskmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 176 "Kkahskmst.sqc"
      sqlasetdata(3,0,7,sql_setdlist,0L,0L);
    }
#line 176 "Kkahskmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 176 "Kkahskmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 176 "Kkahskmst.sqc"
  sqlastop(0L);
}

#line 176 "Kkahskmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kkahskmst*)ZbmlRealloc( array,
                                    sizeof( Kkahskmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kkahskmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KkahskmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 191 "Kkahskmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 191 "Kkahskmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 191 "Kkahskmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 191 "Kkahskmst.sqc"
  sqlastop(0L);
}

#line 191 "Kkahskmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 199 "Kkahskmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKkahskmstInsert()
 *    KKAHSKMST レコードを挿入する
 * ■引数
 *    [I]  Kkahskmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKkahskmstInsert( Kkahskmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KkahskmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 222 "Kkahskmst.sqc"


    
/*
EXEC SQL INSERT INTO KKAHSKMST
    (
		KKAHSKCD,
		KKAHSKNM,
		KKAHSKNMJ,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:kkahskcd,
		:kkahsknm,
		:kkahsknmj,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 241 "Kkahskmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 241 "Kkahskmst.sqc"
  sqlaaloc(2,7,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 241 "Kkahskmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 4;
#line 241 "Kkahskmst.sqc"
      sql_setdlist[0].sqldata = (void*)kkahskcd;
#line 241 "Kkahskmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 241 "Kkahskmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 241 "Kkahskmst.sqc"
      sql_setdlist[1].sqldata = (void*)kkahsknm;
#line 241 "Kkahskmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 241 "Kkahskmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 33;
#line 241 "Kkahskmst.sqc"
      sql_setdlist[2].sqldata = (void*)kkahsknmj;
#line 241 "Kkahskmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 241 "Kkahskmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 241 "Kkahskmst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 241 "Kkahskmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 241 "Kkahskmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 241 "Kkahskmst.sqc"
      sql_setdlist[4].sqldata = (void*)haiymd;
#line 241 "Kkahskmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 241 "Kkahskmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 9;
#line 241 "Kkahskmst.sqc"
      sql_setdlist[5].sqldata = (void*)hnktntid;
#line 241 "Kkahskmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 241 "Kkahskmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 241 "Kkahskmst.sqc"
      sql_setdlist[6].sqldata = (void*)ksndh;
#line 241 "Kkahskmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 241 "Kkahskmst.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 241 "Kkahskmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 241 "Kkahskmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 241 "Kkahskmst.sqc"
  sqlastop(0L);
}

#line 241 "Kkahskmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 246 "Kkahskmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKkahskmstUpdate()
 *    KKAHSKMST レコードを更新する
 * ■引数
 *    [I]  Kkahskmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKkahskmstUpdate( Kkahskmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KkahskmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 270 "Kkahskmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 271 "Kkahskmst.sqc"


    
/*
EXEC SQL UPDATE KKAHSKMST
    SET (
		KKAHSKNM,
		KKAHSKNMJ,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:kkahsknm,
		:kkahsknmj,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		KKAHSKCD = :kkahskcd AND
		KAIYMD = :kaiymd;
*/

{
#line 288 "Kkahskmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 288 "Kkahskmst.sqc"
  sqlaaloc(2,7,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 288 "Kkahskmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 288 "Kkahskmst.sqc"
      sql_setdlist[0].sqldata = (void*)kkahsknm;
#line 288 "Kkahskmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 288 "Kkahskmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 33;
#line 288 "Kkahskmst.sqc"
      sql_setdlist[1].sqldata = (void*)kkahsknmj;
#line 288 "Kkahskmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 288 "Kkahskmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 288 "Kkahskmst.sqc"
      sql_setdlist[2].sqldata = (void*)haiymd;
#line 288 "Kkahskmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 288 "Kkahskmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 9;
#line 288 "Kkahskmst.sqc"
      sql_setdlist[3].sqldata = (void*)hnktntid;
#line 288 "Kkahskmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 288 "Kkahskmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 27;
#line 288 "Kkahskmst.sqc"
      sql_setdlist[4].sqldata = (void*)ksndh;
#line 288 "Kkahskmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 288 "Kkahskmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 4;
#line 288 "Kkahskmst.sqc"
      sql_setdlist[5].sqldata = (void*)kkahskcd;
#line 288 "Kkahskmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 288 "Kkahskmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 288 "Kkahskmst.sqc"
      sql_setdlist[6].sqldata = (void*)kaiymd;
#line 288 "Kkahskmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 288 "Kkahskmst.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 288 "Kkahskmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 288 "Kkahskmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 288 "Kkahskmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 288 "Kkahskmst.sqc"
  sqlastop(0L);
}

#line 288 "Kkahskmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 293 "Kkahskmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 297 "Kkahskmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKkahskmstDelete()
 *    KKAHSKMST レコードを削除する
 * ■引数
 *    [I]  Kkahskmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKkahskmstDelete( Kkahskmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KkahskmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 321 "Kkahskmst.sqc"


    
/*
EXEC SQL DELETE FROM KKAHSKMST
    WHERE
		KKAHSKCD = :kkahskcd AND
		KAIYMD = :kaiymd;
*/

{
#line 326 "Kkahskmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 326 "Kkahskmst.sqc"
  sqlaaloc(2,2,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 326 "Kkahskmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 4;
#line 326 "Kkahskmst.sqc"
      sql_setdlist[0].sqldata = (void*)kkahskcd;
#line 326 "Kkahskmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 326 "Kkahskmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 326 "Kkahskmst.sqc"
      sql_setdlist[1].sqldata = (void*)kaiymd;
#line 326 "Kkahskmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 326 "Kkahskmst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 326 "Kkahskmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 326 "Kkahskmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 326 "Kkahskmst.sqc"
  sqlastop(0L);
}

#line 326 "Kkahskmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 331 "Kkahskmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
