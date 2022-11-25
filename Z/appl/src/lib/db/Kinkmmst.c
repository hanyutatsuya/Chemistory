static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,77,65,84,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,51,52,90,75,73,78,75,32,0,0,0,0,0,0,0,0,
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


#line 1 "Kinkmmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Kinkmmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Kinkmmst.h"
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


#line 24 "Kinkmmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Kinkmmst.sqc"

	char    kmkcd[8];
	char    smpcd[8];
	char    seccd[3];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 37 "Kinkmmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Kinkmmst

BmlDMMInfo	KinkmmstArray[] = {
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( smpcd ),
	DMM_SSTRING( seccd ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKinkmmstSelectAll()
 *    KINKMMST レコード全件取得
 * ■引数
 *    [O]  Kinkmmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKinkmmstSelectAll( Kinkmmst** arrayOut, int* numOut )
{
    Kinkmmst*   array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 72 "Kinkmmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KMKCD,
		SMPCD,
		SECCD,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        KINKMMST FOR READ ONLY;
*/

#line 84 "Kinkmmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 86 "Kinkmmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 86 "Kinkmmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 86 "Kinkmmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 86 "Kinkmmst.sqc"
  sqlastop(0L);
}

#line 86 "Kinkmmst.sqc"


    while( 1 ) {
        Kinkmmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:kmkcd,
			:smpcd,
			:seccd,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 98 "Kinkmmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 98 "Kinkmmst.sqc"
  sqlaaloc(3,7,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 98 "Kinkmmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 98 "Kinkmmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcd;
#line 98 "Kinkmmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 98 "Kinkmmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 98 "Kinkmmst.sqc"
      sql_setdlist[1].sqldata = (void*)smpcd;
#line 98 "Kinkmmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 98 "Kinkmmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 98 "Kinkmmst.sqc"
      sql_setdlist[2].sqldata = (void*)seccd;
#line 98 "Kinkmmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 98 "Kinkmmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 98 "Kinkmmst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 98 "Kinkmmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 98 "Kinkmmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 98 "Kinkmmst.sqc"
      sql_setdlist[4].sqldata = (void*)haiymd;
#line 98 "Kinkmmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 98 "Kinkmmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 9;
#line 98 "Kinkmmst.sqc"
      sql_setdlist[5].sqldata = (void*)hnktntid;
#line 98 "Kinkmmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 98 "Kinkmmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 98 "Kinkmmst.sqc"
      sql_setdlist[6].sqldata = (void*)ksndh;
#line 98 "Kinkmmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 98 "Kinkmmst.sqc"
      sqlasetdata(3,0,7,sql_setdlist,0L,0L);
    }
#line 98 "Kinkmmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 98 "Kinkmmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 98 "Kinkmmst.sqc"
  sqlastop(0L);
}

#line 98 "Kinkmmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kinkmmst*)ZbmlRealloc( array,
                                    sizeof( Kinkmmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kinkmmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KinkmmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 113 "Kinkmmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 113 "Kinkmmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 113 "Kinkmmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 113 "Kinkmmst.sqc"
  sqlastop(0L);
}

#line 113 "Kinkmmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 121 "Kinkmmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKinkmmstSelectKey()
 *    KINKMMST レコードKey条件取得
 * ■引数
 *    [I]  Kinkmmst* pKey       取得するレコードのキー
 *    [O]  Kinkmmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKinkmmstSelectKey( Kinkmmst* pKey, Kinkmmst** arrayOut, int* numOut )
{
    Kinkmmst*   array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KinkmmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 147 "Kinkmmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KMKCD,
		SMPCD,
		SECCD,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        KINKMMST
    WHERE
		KMKCD = :kmkcd AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 162 "Kinkmmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 164 "Kinkmmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 164 "Kinkmmst.sqc"
  sqlaaloc(2,2,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 164 "Kinkmmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 164 "Kinkmmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcd;
#line 164 "Kinkmmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 164 "Kinkmmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 164 "Kinkmmst.sqc"
      sql_setdlist[1].sqldata = (void*)kaiymd;
#line 164 "Kinkmmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 164 "Kinkmmst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 164 "Kinkmmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 164 "Kinkmmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 164 "Kinkmmst.sqc"
  sqlastop(0L);
}

#line 164 "Kinkmmst.sqc"


    while( 1 ) {
        Kinkmmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:kmkcd,
			:smpcd,
			:seccd,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 176 "Kinkmmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 176 "Kinkmmst.sqc"
  sqlaaloc(3,7,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 176 "Kinkmmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 176 "Kinkmmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcd;
#line 176 "Kinkmmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 176 "Kinkmmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 176 "Kinkmmst.sqc"
      sql_setdlist[1].sqldata = (void*)smpcd;
#line 176 "Kinkmmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 176 "Kinkmmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 176 "Kinkmmst.sqc"
      sql_setdlist[2].sqldata = (void*)seccd;
#line 176 "Kinkmmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 176 "Kinkmmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 176 "Kinkmmst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 176 "Kinkmmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 176 "Kinkmmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 176 "Kinkmmst.sqc"
      sql_setdlist[4].sqldata = (void*)haiymd;
#line 176 "Kinkmmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 176 "Kinkmmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 9;
#line 176 "Kinkmmst.sqc"
      sql_setdlist[5].sqldata = (void*)hnktntid;
#line 176 "Kinkmmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 176 "Kinkmmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 176 "Kinkmmst.sqc"
      sql_setdlist[6].sqldata = (void*)ksndh;
#line 176 "Kinkmmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 176 "Kinkmmst.sqc"
      sqlasetdata(3,0,7,sql_setdlist,0L,0L);
    }
#line 176 "Kinkmmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 176 "Kinkmmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 176 "Kinkmmst.sqc"
  sqlastop(0L);
}

#line 176 "Kinkmmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kinkmmst*)ZbmlRealloc( array,
                                    sizeof( Kinkmmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kinkmmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KinkmmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 191 "Kinkmmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 191 "Kinkmmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 191 "Kinkmmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 191 "Kinkmmst.sqc"
  sqlastop(0L);
}

#line 191 "Kinkmmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 199 "Kinkmmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKinkmmstInsert()
 *    KINKMMST レコードを挿入する
 * ■引数
 *    [I]  Kinkmmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKinkmmstInsert( Kinkmmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KinkmmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 222 "Kinkmmst.sqc"


    
/*
EXEC SQL INSERT INTO KINKMMST
    (
		KMKCD,
		SMPCD,
		SECCD,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:kmkcd,
		:smpcd,
		:seccd,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 241 "Kinkmmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 241 "Kinkmmst.sqc"
  sqlaaloc(2,7,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 241 "Kinkmmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 241 "Kinkmmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcd;
#line 241 "Kinkmmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 241 "Kinkmmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 241 "Kinkmmst.sqc"
      sql_setdlist[1].sqldata = (void*)smpcd;
#line 241 "Kinkmmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 241 "Kinkmmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 241 "Kinkmmst.sqc"
      sql_setdlist[2].sqldata = (void*)seccd;
#line 241 "Kinkmmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 241 "Kinkmmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 241 "Kinkmmst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 241 "Kinkmmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 241 "Kinkmmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 241 "Kinkmmst.sqc"
      sql_setdlist[4].sqldata = (void*)haiymd;
#line 241 "Kinkmmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 241 "Kinkmmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 9;
#line 241 "Kinkmmst.sqc"
      sql_setdlist[5].sqldata = (void*)hnktntid;
#line 241 "Kinkmmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 241 "Kinkmmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 241 "Kinkmmst.sqc"
      sql_setdlist[6].sqldata = (void*)ksndh;
#line 241 "Kinkmmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 241 "Kinkmmst.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 241 "Kinkmmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 241 "Kinkmmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 241 "Kinkmmst.sqc"
  sqlastop(0L);
}

#line 241 "Kinkmmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 246 "Kinkmmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKinkmmstUpdate()
 *    KINKMMST レコードを更新する
 * ■引数
 *    [I]  Kinkmmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKinkmmstUpdate( Kinkmmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KinkmmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 270 "Kinkmmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 271 "Kinkmmst.sqc"


    
/*
EXEC SQL UPDATE KINKMMST
    SET (
		SMPCD,
		SECCD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:smpcd,
		:seccd,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		KMKCD = :kmkcd AND
		KAIYMD = :kaiymd;
*/

{
#line 288 "Kinkmmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 288 "Kinkmmst.sqc"
  sqlaaloc(2,7,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 288 "Kinkmmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 288 "Kinkmmst.sqc"
      sql_setdlist[0].sqldata = (void*)smpcd;
#line 288 "Kinkmmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 288 "Kinkmmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 288 "Kinkmmst.sqc"
      sql_setdlist[1].sqldata = (void*)seccd;
#line 288 "Kinkmmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 288 "Kinkmmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 288 "Kinkmmst.sqc"
      sql_setdlist[2].sqldata = (void*)haiymd;
#line 288 "Kinkmmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 288 "Kinkmmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 9;
#line 288 "Kinkmmst.sqc"
      sql_setdlist[3].sqldata = (void*)hnktntid;
#line 288 "Kinkmmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 288 "Kinkmmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 27;
#line 288 "Kinkmmst.sqc"
      sql_setdlist[4].sqldata = (void*)ksndh;
#line 288 "Kinkmmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 288 "Kinkmmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 288 "Kinkmmst.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 288 "Kinkmmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 288 "Kinkmmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 288 "Kinkmmst.sqc"
      sql_setdlist[6].sqldata = (void*)kaiymd;
#line 288 "Kinkmmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 288 "Kinkmmst.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 288 "Kinkmmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 288 "Kinkmmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 288 "Kinkmmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 288 "Kinkmmst.sqc"
  sqlastop(0L);
}

#line 288 "Kinkmmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 293 "Kinkmmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 297 "Kinkmmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKinkmmstDelete()
 *    KINKMMST レコードを削除する
 * ■引数
 *    [I]  Kinkmmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKinkmmstDelete( Kinkmmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KinkmmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 321 "Kinkmmst.sqc"


    
/*
EXEC SQL DELETE FROM KINKMMST
    WHERE
		KMKCD = :kmkcd AND
		KAIYMD = :kaiymd;
*/

{
#line 326 "Kinkmmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 326 "Kinkmmst.sqc"
  sqlaaloc(2,2,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 326 "Kinkmmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 326 "Kinkmmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcd;
#line 326 "Kinkmmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 326 "Kinkmmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 326 "Kinkmmst.sqc"
      sql_setdlist[1].sqldata = (void*)kaiymd;
#line 326 "Kinkmmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 326 "Kinkmmst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 326 "Kinkmmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 326 "Kinkmmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 326 "Kinkmmst.sqc"
  sqlastop(0L);
}

#line 326 "Kinkmmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 331 "Kinkmmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
