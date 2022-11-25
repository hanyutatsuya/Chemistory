static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,103,65,87,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,55,49,90,84,82,65,89,32,0,0,0,0,0,0,0,0,
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


#line 1 "Trayknri.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Trayknri.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Trayknri.h"
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


#line 24 "Trayknri.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Trayknri.sqc"

	char    knskisymd[11];
	char    trid[11];
	char    uktrdh[27];
	char    uktrtts[9];
	char    instkdh[27];
	char    instkno[11];
	short   instksu;
	char    outstkdh[27];
	char    outstkno[11];
	short   outsksu;
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 41 "Trayknri.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Trayknri

BmlDMMInfo	TrayknriArray[] = {
	DMM_SDATE( knskisymd ),
	DMM_SSTRING( trid ),
	DMM_STIMESTAMP( uktrdh ),
	DMM_SSTRING( uktrtts ),
	DMM_STIMESTAMP( instkdh ),
	DMM_SSTRING( instkno ),
	DMM_SSHORT( instksu ),
	DMM_STIMESTAMP( outstkdh ),
	DMM_SSTRING( outstkno ),
	DMM_SSHORT( outsksu ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbTrayknriSelectAll()
 *    TRAYKNRI レコード全件取得
 * ■引数
 *    [O]  Trayknri** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbTrayknriSelectAll( Trayknri** arrayOut, int* numOut )
{
    Trayknri*   array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 80 "Trayknri.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSKISYMD,
		TRID,
		UKTRDH,
		UKTRTTS,
		INSTKDH,
		INSTKNO,
		INSTKSU,
		OUTSTKDH,
		OUTSTKNO,
		OUTSKSU,
		KSNDH
    FROM
        TRAYKNRI FOR READ ONLY;
*/

#line 96 "Trayknri.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 98 "Trayknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 98 "Trayknri.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 98 "Trayknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 98 "Trayknri.sqc"
  sqlastop(0L);
}

#line 98 "Trayknri.sqc"


    while( 1 ) {
        Trayknri* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knskisymd,
			:trid,
			:uktrdh,
			:uktrtts,
			:instkdh,
			:instkno,
			:instksu,
			:outstkdh,
			:outstkno,
			:outsksu,
			:ksndh;
*/

{
#line 114 "Trayknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 114 "Trayknri.sqc"
  sqlaaloc(3,11,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[11];
#line 114 "Trayknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 114 "Trayknri.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 114 "Trayknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 114 "Trayknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 114 "Trayknri.sqc"
      sql_setdlist[1].sqldata = (void*)trid;
#line 114 "Trayknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 114 "Trayknri.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 27;
#line 114 "Trayknri.sqc"
      sql_setdlist[2].sqldata = (void*)uktrdh;
#line 114 "Trayknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 114 "Trayknri.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 9;
#line 114 "Trayknri.sqc"
      sql_setdlist[3].sqldata = (void*)uktrtts;
#line 114 "Trayknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 114 "Trayknri.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 27;
#line 114 "Trayknri.sqc"
      sql_setdlist[4].sqldata = (void*)instkdh;
#line 114 "Trayknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 114 "Trayknri.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 114 "Trayknri.sqc"
      sql_setdlist[5].sqldata = (void*)instkno;
#line 114 "Trayknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 114 "Trayknri.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 114 "Trayknri.sqc"
      sql_setdlist[6].sqldata = (void*)&instksu;
#line 114 "Trayknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 114 "Trayknri.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 114 "Trayknri.sqc"
      sql_setdlist[7].sqldata = (void*)outstkdh;
#line 114 "Trayknri.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 114 "Trayknri.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 114 "Trayknri.sqc"
      sql_setdlist[8].sqldata = (void*)outstkno;
#line 114 "Trayknri.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 114 "Trayknri.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 114 "Trayknri.sqc"
      sql_setdlist[9].sqldata = (void*)&outsksu;
#line 114 "Trayknri.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 114 "Trayknri.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 27;
#line 114 "Trayknri.sqc"
      sql_setdlist[10].sqldata = (void*)ksndh;
#line 114 "Trayknri.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 114 "Trayknri.sqc"
      sqlasetdata(3,0,11,sql_setdlist,0L,0L);
    }
#line 114 "Trayknri.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 114 "Trayknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 114 "Trayknri.sqc"
  sqlastop(0L);
}

#line 114 "Trayknri.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Trayknri*)ZbmlRealloc( array,
                                    sizeof( Trayknri ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Trayknri ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, TrayknriArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 129 "Trayknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 129 "Trayknri.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 129 "Trayknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 129 "Trayknri.sqc"
  sqlastop(0L);
}

#line 129 "Trayknri.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 137 "Trayknri.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbTrayknriSelectKey()
 *    TRAYKNRI レコードKey条件取得
 * ■引数
 *    [I]  Trayknri* pKey       取得するレコードのキー
 *    [O]  Trayknri** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbTrayknriSelectKey( Trayknri* pKey, Trayknri** arrayOut, int* numOut )
{
    Trayknri*   array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, TrayknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 163 "Trayknri.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSKISYMD,
		TRID,
		UKTRDH,
		UKTRTTS,
		INSTKDH,
		INSTKNO,
		INSTKSU,
		OUTSTKDH,
		OUTSTKNO,
		OUTSKSU,
		KSNDH
    FROM
        TRAYKNRI
    WHERE
		KNSKISYMD = :knskisymd AND
		TRID = :trid FOR READ ONLY;
*/

#line 182 "Trayknri.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 184 "Trayknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 184 "Trayknri.sqc"
  sqlaaloc(2,2,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 184 "Trayknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 184 "Trayknri.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 184 "Trayknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 184 "Trayknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 184 "Trayknri.sqc"
      sql_setdlist[1].sqldata = (void*)trid;
#line 184 "Trayknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 184 "Trayknri.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 184 "Trayknri.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 184 "Trayknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 184 "Trayknri.sqc"
  sqlastop(0L);
}

#line 184 "Trayknri.sqc"


    while( 1 ) {
        Trayknri* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knskisymd,
			:trid,
			:uktrdh,
			:uktrtts,
			:instkdh,
			:instkno,
			:instksu,
			:outstkdh,
			:outstkno,
			:outsksu,
			:ksndh;
*/

{
#line 200 "Trayknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 200 "Trayknri.sqc"
  sqlaaloc(3,11,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[11];
#line 200 "Trayknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 200 "Trayknri.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 200 "Trayknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 200 "Trayknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 200 "Trayknri.sqc"
      sql_setdlist[1].sqldata = (void*)trid;
#line 200 "Trayknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 200 "Trayknri.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 27;
#line 200 "Trayknri.sqc"
      sql_setdlist[2].sqldata = (void*)uktrdh;
#line 200 "Trayknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 200 "Trayknri.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 9;
#line 200 "Trayknri.sqc"
      sql_setdlist[3].sqldata = (void*)uktrtts;
#line 200 "Trayknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 200 "Trayknri.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 27;
#line 200 "Trayknri.sqc"
      sql_setdlist[4].sqldata = (void*)instkdh;
#line 200 "Trayknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 200 "Trayknri.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 200 "Trayknri.sqc"
      sql_setdlist[5].sqldata = (void*)instkno;
#line 200 "Trayknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 200 "Trayknri.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 200 "Trayknri.sqc"
      sql_setdlist[6].sqldata = (void*)&instksu;
#line 200 "Trayknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 200 "Trayknri.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 200 "Trayknri.sqc"
      sql_setdlist[7].sqldata = (void*)outstkdh;
#line 200 "Trayknri.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 200 "Trayknri.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 200 "Trayknri.sqc"
      sql_setdlist[8].sqldata = (void*)outstkno;
#line 200 "Trayknri.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 200 "Trayknri.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 200 "Trayknri.sqc"
      sql_setdlist[9].sqldata = (void*)&outsksu;
#line 200 "Trayknri.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 200 "Trayknri.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 27;
#line 200 "Trayknri.sqc"
      sql_setdlist[10].sqldata = (void*)ksndh;
#line 200 "Trayknri.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 200 "Trayknri.sqc"
      sqlasetdata(3,0,11,sql_setdlist,0L,0L);
    }
#line 200 "Trayknri.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 200 "Trayknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 200 "Trayknri.sqc"
  sqlastop(0L);
}

#line 200 "Trayknri.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Trayknri*)ZbmlRealloc( array,
                                    sizeof( Trayknri ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Trayknri ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, TrayknriArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 215 "Trayknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 215 "Trayknri.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 215 "Trayknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 215 "Trayknri.sqc"
  sqlastop(0L);
}

#line 215 "Trayknri.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 223 "Trayknri.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbTrayknriInsert()
 *    TRAYKNRI レコードを挿入する
 * ■引数
 *    [I]  Trayknri* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbTrayknriInsert( Trayknri* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, TrayknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 246 "Trayknri.sqc"


    
/*
EXEC SQL INSERT INTO TRAYKNRI
    (
		KNSKISYMD,
		TRID,
		UKTRDH,
		UKTRTTS,
		INSTKDH,
		INSTKNO,
		INSTKSU,
		OUTSTKDH,
		OUTSTKNO,
		OUTSKSU,
		KSNDH
    ) VALUES (
		:knskisymd,
		:trid,
		:uktrdh,
		:uktrtts,
		:instkdh,
		:instkno,
		:instksu,
		:outstkdh,
		:outstkno,
		:outsksu,
		:ksndh
    );
*/

{
#line 273 "Trayknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 273 "Trayknri.sqc"
  sqlaaloc(2,11,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[11];
#line 273 "Trayknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 273 "Trayknri.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 273 "Trayknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 273 "Trayknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 273 "Trayknri.sqc"
      sql_setdlist[1].sqldata = (void*)trid;
#line 273 "Trayknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 273 "Trayknri.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 27;
#line 273 "Trayknri.sqc"
      sql_setdlist[2].sqldata = (void*)uktrdh;
#line 273 "Trayknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 273 "Trayknri.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 9;
#line 273 "Trayknri.sqc"
      sql_setdlist[3].sqldata = (void*)uktrtts;
#line 273 "Trayknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 273 "Trayknri.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 27;
#line 273 "Trayknri.sqc"
      sql_setdlist[4].sqldata = (void*)instkdh;
#line 273 "Trayknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 273 "Trayknri.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 273 "Trayknri.sqc"
      sql_setdlist[5].sqldata = (void*)instkno;
#line 273 "Trayknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 273 "Trayknri.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 273 "Trayknri.sqc"
      sql_setdlist[6].sqldata = (void*)&instksu;
#line 273 "Trayknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 273 "Trayknri.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 273 "Trayknri.sqc"
      sql_setdlist[7].sqldata = (void*)outstkdh;
#line 273 "Trayknri.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 273 "Trayknri.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 273 "Trayknri.sqc"
      sql_setdlist[8].sqldata = (void*)outstkno;
#line 273 "Trayknri.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 273 "Trayknri.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 273 "Trayknri.sqc"
      sql_setdlist[9].sqldata = (void*)&outsksu;
#line 273 "Trayknri.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 273 "Trayknri.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 27;
#line 273 "Trayknri.sqc"
      sql_setdlist[10].sqldata = (void*)ksndh;
#line 273 "Trayknri.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 273 "Trayknri.sqc"
      sqlasetdata(2,0,11,sql_setdlist,0L,0L);
    }
#line 273 "Trayknri.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 273 "Trayknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 273 "Trayknri.sqc"
  sqlastop(0L);
}

#line 273 "Trayknri.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 278 "Trayknri.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbTrayknriUpdate()
 *    TRAYKNRI レコードを更新する
 * ■引数
 *    [I]  Trayknri* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbTrayknriUpdate( Trayknri* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, TrayknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 302 "Trayknri.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 303 "Trayknri.sqc"


    
/*
EXEC SQL UPDATE TRAYKNRI
    SET (
		UKTRDH,
		UKTRTTS,
		INSTKDH,
		INSTKNO,
		INSTKSU,
		OUTSTKDH,
		OUTSTKNO,
		OUTSKSU,
		KSNDH
    ) = (
		:uktrdh,
		:uktrtts,
		:instkdh,
		:instkno,
		:instksu,
		:outstkdh,
		:outstkno,
		:outsksu,
		:ksndh
    ) WHERE
		KNSKISYMD = :knskisymd AND
		TRID = :trid;
*/

{
#line 328 "Trayknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 328 "Trayknri.sqc"
  sqlaaloc(2,11,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[11];
#line 328 "Trayknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 27;
#line 328 "Trayknri.sqc"
      sql_setdlist[0].sqldata = (void*)uktrdh;
#line 328 "Trayknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 328 "Trayknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 9;
#line 328 "Trayknri.sqc"
      sql_setdlist[1].sqldata = (void*)uktrtts;
#line 328 "Trayknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 328 "Trayknri.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 27;
#line 328 "Trayknri.sqc"
      sql_setdlist[2].sqldata = (void*)instkdh;
#line 328 "Trayknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 328 "Trayknri.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 328 "Trayknri.sqc"
      sql_setdlist[3].sqldata = (void*)instkno;
#line 328 "Trayknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 328 "Trayknri.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 328 "Trayknri.sqc"
      sql_setdlist[4].sqldata = (void*)&instksu;
#line 328 "Trayknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 328 "Trayknri.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 27;
#line 328 "Trayknri.sqc"
      sql_setdlist[5].sqldata = (void*)outstkdh;
#line 328 "Trayknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 328 "Trayknri.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 328 "Trayknri.sqc"
      sql_setdlist[6].sqldata = (void*)outstkno;
#line 328 "Trayknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 328 "Trayknri.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 328 "Trayknri.sqc"
      sql_setdlist[7].sqldata = (void*)&outsksu;
#line 328 "Trayknri.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 328 "Trayknri.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 328 "Trayknri.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 328 "Trayknri.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 328 "Trayknri.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 328 "Trayknri.sqc"
      sql_setdlist[9].sqldata = (void*)knskisymd;
#line 328 "Trayknri.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 328 "Trayknri.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 328 "Trayknri.sqc"
      sql_setdlist[10].sqldata = (void*)trid;
#line 328 "Trayknri.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 328 "Trayknri.sqc"
      sqlasetdata(2,0,11,sql_setdlist,0L,0L);
    }
#line 328 "Trayknri.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 328 "Trayknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 328 "Trayknri.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 328 "Trayknri.sqc"
  sqlastop(0L);
}

#line 328 "Trayknri.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 333 "Trayknri.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 337 "Trayknri.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbTrayknriDelete()
 *    TRAYKNRI レコードを削除する
 * ■引数
 *    [I]  Trayknri* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbTrayknriDelete( Trayknri* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, TrayknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 361 "Trayknri.sqc"


    
/*
EXEC SQL DELETE FROM TRAYKNRI
    WHERE
		KNSKISYMD = :knskisymd AND
		TRID = :trid;
*/

{
#line 366 "Trayknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 366 "Trayknri.sqc"
  sqlaaloc(2,2,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 366 "Trayknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 366 "Trayknri.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 366 "Trayknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 366 "Trayknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 366 "Trayknri.sqc"
      sql_setdlist[1].sqldata = (void*)trid;
#line 366 "Trayknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 366 "Trayknri.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 366 "Trayknri.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 366 "Trayknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 366 "Trayknri.sqc"
  sqlastop(0L);
}

#line 366 "Trayknri.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 371 "Trayknri.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
