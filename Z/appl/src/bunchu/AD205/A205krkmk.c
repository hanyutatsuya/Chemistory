static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,55,65,76,86,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,65,50,48,53,75,82,75,77,0,0,0,0,0,0,0,0,
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


#line 1 "A205krkmk.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Krkmkmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Krkmkmst.h"
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


#line 24 "A205krkmk.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "A205krkmk.sqc"

	char    kmkcd[8];
	char    krkmkcd[8];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 36 "A205krkmk.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Krkmkmst

BmlDMMInfo	KrkmkmstArray1[] = {
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( krkmkcd ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * A205krkmkSelKey()
 *    KRKMKMST レコードKey条件取得
 * ■引数
 *    [I]  Krkmkmst* pKey       取得するレコードのキー
 *    [O]  Krkmkmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long A205krkmkSelKey( Krkmkmst* pKey, Krkmkmst** arrayOut, int* numOut )
{
    Krkmkmst*   array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KrkmkmstArray1 ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 77 "A205krkmk.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KMKCD,
		KRKMKCD,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        KRKMKMST
    WHERE
		KMKCD = :kmkcd AND
		KAIYMD <= :kaiymd AND 
		HAIYMD >= :kaiymd
		FOR READ ONLY;
*/

#line 93 "A205krkmk.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 95 "A205krkmk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 95 "A205krkmk.sqc"
  sqlaaloc(2,3,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 95 "A205krkmk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 95 "A205krkmk.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcd;
#line 95 "A205krkmk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 95 "A205krkmk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 95 "A205krkmk.sqc"
      sql_setdlist[1].sqldata = (void*)kaiymd;
#line 95 "A205krkmk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 95 "A205krkmk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 95 "A205krkmk.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 95 "A205krkmk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 95 "A205krkmk.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 95 "A205krkmk.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 95 "A205krkmk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 95 "A205krkmk.sqc"
  sqlastop(0L);
}

#line 95 "A205krkmk.sqc"


    while( 1 ) {
        Krkmkmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:kmkcd,
			:krkmkcd,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 106 "A205krkmk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 106 "A205krkmk.sqc"
  sqlaaloc(3,6,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 106 "A205krkmk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 106 "A205krkmk.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcd;
#line 106 "A205krkmk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 106 "A205krkmk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 106 "A205krkmk.sqc"
      sql_setdlist[1].sqldata = (void*)krkmkcd;
#line 106 "A205krkmk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 106 "A205krkmk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 106 "A205krkmk.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 106 "A205krkmk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 106 "A205krkmk.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 106 "A205krkmk.sqc"
      sql_setdlist[3].sqldata = (void*)haiymd;
#line 106 "A205krkmk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 106 "A205krkmk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 9;
#line 106 "A205krkmk.sqc"
      sql_setdlist[4].sqldata = (void*)hnktntid;
#line 106 "A205krkmk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 106 "A205krkmk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 27;
#line 106 "A205krkmk.sqc"
      sql_setdlist[5].sqldata = (void*)ksndh;
#line 106 "A205krkmk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 106 "A205krkmk.sqc"
      sqlasetdata(3,0,6,sql_setdlist,0L,0L);
    }
#line 106 "A205krkmk.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 106 "A205krkmk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 106 "A205krkmk.sqc"
  sqlastop(0L);
}

#line 106 "A205krkmk.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Krkmkmst*)ZbmlRealloc( array,
                                    sizeof( Krkmkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Krkmkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KrkmkmstArray1 );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 121 "A205krkmk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 121 "A205krkmk.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 121 "A205krkmk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 121 "A205krkmk.sqc"
  sqlastop(0L);
}

#line 121 "A205krkmk.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 129 "A205krkmk.sqc"

    return sqlca.sqlcode;
}

/** End of File *********************************************************/
