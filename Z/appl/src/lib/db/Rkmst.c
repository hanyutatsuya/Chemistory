static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,84,65,86,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,53,56,90,82,75,77,83,32,0,0,0,0,0,0,0,0,
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


#line 1 "Rkmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Rkmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2008-01-07                    Create
 **********************************************************************/
#include <stdio.h>

#include "Rkmst.h"
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


#line 24 "Rkmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Rkmst.sqc"

	char    smpcd[8];
	char    rksbt;
	char    rknm[21];
	short   rkknhsu;
	short   trrcksu;
	char    filskdir[129];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 40 "Rkmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Rkmst

BmlDMMInfo	RkmstArray[] = {
	DMM_SSTRING( smpcd ),
	DMM_SCHAR( rksbt ),
	DMM_SSTRING( rknm ),
	DMM_SSHORT( rkknhsu ),
	DMM_SSHORT( trrcksu ),
	DMM_SSTRING( filskdir ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbRkmstSelectAll()
 *    RKMST レコード全件取得
 * ■引数
 *    [O]  Rkmst** arrayOut     取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbRkmstSelectAll( Rkmst** arrayOut, int* numOut )
{
    Rkmst*      array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 78 "Rkmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		SMPCD,
		RKSBT,
		RKNM,
		RKKNHSU,
		TRRCKSU,
		FILSKDIR,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        RKMST FOR READ ONLY;
*/

#line 93 "Rkmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 95 "Rkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 95 "Rkmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 95 "Rkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 95 "Rkmst.sqc"
  sqlastop(0L);
}

#line 95 "Rkmst.sqc"


    while( 1 ) {
        Rkmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:smpcd,
			:rksbt,
			:rknm,
			:rkknhsu,
			:trrcksu,
			:filskdir,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 110 "Rkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 110 "Rkmst.sqc"
  sqlaaloc(3,10,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 110 "Rkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 110 "Rkmst.sqc"
      sql_setdlist[0].sqldata = (void*)smpcd;
#line 110 "Rkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 110 "Rkmst.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 110 "Rkmst.sqc"
      sql_setdlist[1].sqldata = (void*)&rksbt;
#line 110 "Rkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 110 "Rkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 110 "Rkmst.sqc"
      sql_setdlist[2].sqldata = (void*)rknm;
#line 110 "Rkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 110 "Rkmst.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 110 "Rkmst.sqc"
      sql_setdlist[3].sqldata = (void*)&rkknhsu;
#line 110 "Rkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 110 "Rkmst.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 110 "Rkmst.sqc"
      sql_setdlist[4].sqldata = (void*)&trrcksu;
#line 110 "Rkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 110 "Rkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 129;
#line 110 "Rkmst.sqc"
      sql_setdlist[5].sqldata = (void*)filskdir;
#line 110 "Rkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 110 "Rkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 110 "Rkmst.sqc"
      sql_setdlist[6].sqldata = (void*)kaiymd;
#line 110 "Rkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 110 "Rkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 110 "Rkmst.sqc"
      sql_setdlist[7].sqldata = (void*)haiymd;
#line 110 "Rkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 110 "Rkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 110 "Rkmst.sqc"
      sql_setdlist[8].sqldata = (void*)hnktntid;
#line 110 "Rkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 110 "Rkmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 110 "Rkmst.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 110 "Rkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 110 "Rkmst.sqc"
      sqlasetdata(3,0,10,sql_setdlist,0L,0L);
    }
#line 110 "Rkmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 110 "Rkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 110 "Rkmst.sqc"
  sqlastop(0L);
}

#line 110 "Rkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Rkmst*)ZbmlRealloc( array,
                                    sizeof( Rkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Rkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, RkmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 125 "Rkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 125 "Rkmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 125 "Rkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 125 "Rkmst.sqc"
  sqlastop(0L);
}

#line 125 "Rkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 133 "Rkmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbRkmstSelectKey()
 *    RKMST レコードKey条件取得
 * ■引数
 *    [I]  Rkmst* pKey       取得するレコードのキー
 *    [O]  Rkmst** arrayOut     取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbRkmstSelectKey( Rkmst* pKey, Rkmst** arrayOut, int* numOut )
{
    Rkmst*      array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, RkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 159 "Rkmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		SMPCD,
		RKSBT,
		RKNM,
		RKKNHSU,
		TRRCKSU,
		FILSKDIR,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        RKMST
    WHERE
		SMPCD = :smpcd AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 177 "Rkmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 179 "Rkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 179 "Rkmst.sqc"
  sqlaaloc(2,2,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 179 "Rkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 179 "Rkmst.sqc"
      sql_setdlist[0].sqldata = (void*)smpcd;
#line 179 "Rkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 179 "Rkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 179 "Rkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kaiymd;
#line 179 "Rkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 179 "Rkmst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 179 "Rkmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 179 "Rkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 179 "Rkmst.sqc"
  sqlastop(0L);
}

#line 179 "Rkmst.sqc"


    while( 1 ) {
        Rkmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:smpcd,
			:rksbt,
			:rknm,
			:rkknhsu,
			:trrcksu,
			:filskdir,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 194 "Rkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 194 "Rkmst.sqc"
  sqlaaloc(3,10,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 194 "Rkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 194 "Rkmst.sqc"
      sql_setdlist[0].sqldata = (void*)smpcd;
#line 194 "Rkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 194 "Rkmst.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 194 "Rkmst.sqc"
      sql_setdlist[1].sqldata = (void*)&rksbt;
#line 194 "Rkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 194 "Rkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 194 "Rkmst.sqc"
      sql_setdlist[2].sqldata = (void*)rknm;
#line 194 "Rkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 194 "Rkmst.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 194 "Rkmst.sqc"
      sql_setdlist[3].sqldata = (void*)&rkknhsu;
#line 194 "Rkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 194 "Rkmst.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 194 "Rkmst.sqc"
      sql_setdlist[4].sqldata = (void*)&trrcksu;
#line 194 "Rkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 194 "Rkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 129;
#line 194 "Rkmst.sqc"
      sql_setdlist[5].sqldata = (void*)filskdir;
#line 194 "Rkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 194 "Rkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 194 "Rkmst.sqc"
      sql_setdlist[6].sqldata = (void*)kaiymd;
#line 194 "Rkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 194 "Rkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 194 "Rkmst.sqc"
      sql_setdlist[7].sqldata = (void*)haiymd;
#line 194 "Rkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 194 "Rkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 194 "Rkmst.sqc"
      sql_setdlist[8].sqldata = (void*)hnktntid;
#line 194 "Rkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 194 "Rkmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 194 "Rkmst.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 194 "Rkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 194 "Rkmst.sqc"
      sqlasetdata(3,0,10,sql_setdlist,0L,0L);
    }
#line 194 "Rkmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 194 "Rkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 194 "Rkmst.sqc"
  sqlastop(0L);
}

#line 194 "Rkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Rkmst*)ZbmlRealloc( array,
                                    sizeof( Rkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Rkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, RkmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 209 "Rkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 209 "Rkmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 209 "Rkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 209 "Rkmst.sqc"
  sqlastop(0L);
}

#line 209 "Rkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 217 "Rkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbRkmstInsert()
 *    RKMST レコードを挿入する
 * ■引数
 *    [I]  Rkmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbRkmstInsert( Rkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, RkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 240 "Rkmst.sqc"


    
/*
EXEC SQL INSERT INTO RKMST
    (
		SMPCD,
		RKSBT,
		RKNM,
		RKKNHSU,
		TRRCKSU,
		FILSKDIR,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:smpcd,
		:rksbt,
		:rknm,
		:rkknhsu,
		:trrcksu,
		:filskdir,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 265 "Rkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 265 "Rkmst.sqc"
  sqlaaloc(2,10,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 265 "Rkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 265 "Rkmst.sqc"
      sql_setdlist[0].sqldata = (void*)smpcd;
#line 265 "Rkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 265 "Rkmst.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 265 "Rkmst.sqc"
      sql_setdlist[1].sqldata = (void*)&rksbt;
#line 265 "Rkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 265 "Rkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 265 "Rkmst.sqc"
      sql_setdlist[2].sqldata = (void*)rknm;
#line 265 "Rkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 265 "Rkmst.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 265 "Rkmst.sqc"
      sql_setdlist[3].sqldata = (void*)&rkknhsu;
#line 265 "Rkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 265 "Rkmst.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 265 "Rkmst.sqc"
      sql_setdlist[4].sqldata = (void*)&trrcksu;
#line 265 "Rkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 265 "Rkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 129;
#line 265 "Rkmst.sqc"
      sql_setdlist[5].sqldata = (void*)filskdir;
#line 265 "Rkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 265 "Rkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 265 "Rkmst.sqc"
      sql_setdlist[6].sqldata = (void*)kaiymd;
#line 265 "Rkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 265 "Rkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 265 "Rkmst.sqc"
      sql_setdlist[7].sqldata = (void*)haiymd;
#line 265 "Rkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 265 "Rkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 265 "Rkmst.sqc"
      sql_setdlist[8].sqldata = (void*)hnktntid;
#line 265 "Rkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 265 "Rkmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 265 "Rkmst.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 265 "Rkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 265 "Rkmst.sqc"
      sqlasetdata(2,0,10,sql_setdlist,0L,0L);
    }
#line 265 "Rkmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 265 "Rkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 265 "Rkmst.sqc"
  sqlastop(0L);
}

#line 265 "Rkmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 270 "Rkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbRkmstUpdate()
 *    RKMST レコードを更新する
 * ■引数
 *    [I]  Rkmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbRkmstUpdate( Rkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, RkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 294 "Rkmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 295 "Rkmst.sqc"


    
/*
EXEC SQL UPDATE RKMST
    SET (
		RKSBT,
		RKNM,
		RKKNHSU,
		TRRCKSU,
		FILSKDIR,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:rksbt,
		:rknm,
		:rkknhsu,
		:trrcksu,
		:filskdir,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		SMPCD = :smpcd AND
		KAIYMD = :kaiymd;
*/

{
#line 318 "Rkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 318 "Rkmst.sqc"
  sqlaaloc(2,10,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 318 "Rkmst.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 318 "Rkmst.sqc"
      sql_setdlist[0].sqldata = (void*)&rksbt;
#line 318 "Rkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 318 "Rkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 318 "Rkmst.sqc"
      sql_setdlist[1].sqldata = (void*)rknm;
#line 318 "Rkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 318 "Rkmst.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 318 "Rkmst.sqc"
      sql_setdlist[2].sqldata = (void*)&rkknhsu;
#line 318 "Rkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 318 "Rkmst.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 318 "Rkmst.sqc"
      sql_setdlist[3].sqldata = (void*)&trrcksu;
#line 318 "Rkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 318 "Rkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 129;
#line 318 "Rkmst.sqc"
      sql_setdlist[4].sqldata = (void*)filskdir;
#line 318 "Rkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 318 "Rkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 318 "Rkmst.sqc"
      sql_setdlist[5].sqldata = (void*)haiymd;
#line 318 "Rkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 318 "Rkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 9;
#line 318 "Rkmst.sqc"
      sql_setdlist[6].sqldata = (void*)hnktntid;
#line 318 "Rkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 318 "Rkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 318 "Rkmst.sqc"
      sql_setdlist[7].sqldata = (void*)ksndh;
#line 318 "Rkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 318 "Rkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 8;
#line 318 "Rkmst.sqc"
      sql_setdlist[8].sqldata = (void*)smpcd;
#line 318 "Rkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 318 "Rkmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 318 "Rkmst.sqc"
      sql_setdlist[9].sqldata = (void*)kaiymd;
#line 318 "Rkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 318 "Rkmst.sqc"
      sqlasetdata(2,0,10,sql_setdlist,0L,0L);
    }
#line 318 "Rkmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 318 "Rkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 318 "Rkmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 318 "Rkmst.sqc"
  sqlastop(0L);
}

#line 318 "Rkmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 323 "Rkmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 327 "Rkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbRkmstDelete()
 *    RKMST レコードを削除する
 * ■引数
 *    [I]  Rkmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbRkmstDelete( Rkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, RkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 351 "Rkmst.sqc"


    
/*
EXEC SQL DELETE FROM RKMST
    WHERE
		SMPCD = :smpcd AND
		KAIYMD = :kaiymd;
*/

{
#line 356 "Rkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 356 "Rkmst.sqc"
  sqlaaloc(2,2,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 356 "Rkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 356 "Rkmst.sqc"
      sql_setdlist[0].sqldata = (void*)smpcd;
#line 356 "Rkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 356 "Rkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 356 "Rkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kaiymd;
#line 356 "Rkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 356 "Rkmst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 356 "Rkmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 356 "Rkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 356 "Rkmst.sqc"
  sqlastop(0L);
}

#line 356 "Rkmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 361 "Rkmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
