static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,66,65,88,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,55,57,90,88,69,69,82,32,0,0,0,0,0,0,0,0,
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


#line 1 "Xeerrmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Xeerrmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Xeerrmst.h"
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


#line 24 "Xeerrmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Xeerrmst.sqc"

	short   errflg;
	char    flgsbt[11];
	char    errname[33];
	short   sksri;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 38 "Xeerrmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Xeerrmst

BmlDMMInfo	XeerrmstArray[] = {
	DMM_SSHORT( errflg ),
	DMM_SSTRING( flgsbt ),
	DMM_SSTRING( errname ),
	DMM_SSHORT( sksri ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbXeerrmstSelectAll()
 *    XEERRMST レコード全件取得
 * ■引数
 *    [O]  Xeerrmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbXeerrmstSelectAll( Xeerrmst** arrayOut, int* numOut )
{
    Xeerrmst*   array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 74 "Xeerrmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		ERRFLG,
		FLGSBT,
		ERRNAME,
		SKSRI,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        XEERRMST FOR READ ONLY;
*/

#line 87 "Xeerrmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 89 "Xeerrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 89 "Xeerrmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 89 "Xeerrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 89 "Xeerrmst.sqc"
  sqlastop(0L);
}

#line 89 "Xeerrmst.sqc"


    while( 1 ) {
        Xeerrmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:errflg,
			:flgsbt,
			:errname,
			:sksri,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 102 "Xeerrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 102 "Xeerrmst.sqc"
  sqlaaloc(3,8,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 102 "Xeerrmst.sqc"
      sql_setdlist[0].sqltype = 500; sql_setdlist[0].sqllen = 2;
#line 102 "Xeerrmst.sqc"
      sql_setdlist[0].sqldata = (void*)&errflg;
#line 102 "Xeerrmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 102 "Xeerrmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 102 "Xeerrmst.sqc"
      sql_setdlist[1].sqldata = (void*)flgsbt;
#line 102 "Xeerrmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 102 "Xeerrmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 33;
#line 102 "Xeerrmst.sqc"
      sql_setdlist[2].sqldata = (void*)errname;
#line 102 "Xeerrmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 102 "Xeerrmst.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 102 "Xeerrmst.sqc"
      sql_setdlist[3].sqldata = (void*)&sksri;
#line 102 "Xeerrmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 102 "Xeerrmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 102 "Xeerrmst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 102 "Xeerrmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 102 "Xeerrmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 102 "Xeerrmst.sqc"
      sql_setdlist[5].sqldata = (void*)haiymd;
#line 102 "Xeerrmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 102 "Xeerrmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 9;
#line 102 "Xeerrmst.sqc"
      sql_setdlist[6].sqldata = (void*)hnktntid;
#line 102 "Xeerrmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 102 "Xeerrmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 102 "Xeerrmst.sqc"
      sql_setdlist[7].sqldata = (void*)ksndh;
#line 102 "Xeerrmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 102 "Xeerrmst.sqc"
      sqlasetdata(3,0,8,sql_setdlist,0L,0L);
    }
#line 102 "Xeerrmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 102 "Xeerrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 102 "Xeerrmst.sqc"
  sqlastop(0L);
}

#line 102 "Xeerrmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Xeerrmst*)ZbmlRealloc( array,
                                    sizeof( Xeerrmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Xeerrmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, XeerrmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 117 "Xeerrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 117 "Xeerrmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 117 "Xeerrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 117 "Xeerrmst.sqc"
  sqlastop(0L);
}

#line 117 "Xeerrmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 125 "Xeerrmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbXeerrmstSelectKey()
 *    XEERRMST レコードKey条件取得
 * ■引数
 *    [I]  Xeerrmst* pKey       取得するレコードのキー
 *    [O]  Xeerrmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbXeerrmstSelectKey( Xeerrmst* pKey, Xeerrmst** arrayOut, int* numOut )
{
    Xeerrmst*   array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, XeerrmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 151 "Xeerrmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		ERRFLG,
		FLGSBT,
		ERRNAME,
		SKSRI,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        XEERRMST
    WHERE
		ERRFLG = :errflg AND
		FLGSBT = :flgsbt AND
		ERRNAME      = :errname      AND
		SKSRI = :sksri AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 170 "Xeerrmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 172 "Xeerrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 172 "Xeerrmst.sqc"
  sqlaaloc(2,5,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 172 "Xeerrmst.sqc"
      sql_setdlist[0].sqltype = 500; sql_setdlist[0].sqllen = 2;
#line 172 "Xeerrmst.sqc"
      sql_setdlist[0].sqldata = (void*)&errflg;
#line 172 "Xeerrmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 172 "Xeerrmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 172 "Xeerrmst.sqc"
      sql_setdlist[1].sqldata = (void*)flgsbt;
#line 172 "Xeerrmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 172 "Xeerrmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 33;
#line 172 "Xeerrmst.sqc"
      sql_setdlist[2].sqldata = (void*)errname;
#line 172 "Xeerrmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 172 "Xeerrmst.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 172 "Xeerrmst.sqc"
      sql_setdlist[3].sqldata = (void*)&sksri;
#line 172 "Xeerrmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 172 "Xeerrmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 172 "Xeerrmst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 172 "Xeerrmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 172 "Xeerrmst.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 172 "Xeerrmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 172 "Xeerrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 172 "Xeerrmst.sqc"
  sqlastop(0L);
}

#line 172 "Xeerrmst.sqc"


    while( 1 ) {
        Xeerrmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:errflg,
			:flgsbt,
			:errname,
			:sksri,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 185 "Xeerrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 185 "Xeerrmst.sqc"
  sqlaaloc(3,8,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 185 "Xeerrmst.sqc"
      sql_setdlist[0].sqltype = 500; sql_setdlist[0].sqllen = 2;
#line 185 "Xeerrmst.sqc"
      sql_setdlist[0].sqldata = (void*)&errflg;
#line 185 "Xeerrmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 185 "Xeerrmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 185 "Xeerrmst.sqc"
      sql_setdlist[1].sqldata = (void*)flgsbt;
#line 185 "Xeerrmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 185 "Xeerrmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 33;
#line 185 "Xeerrmst.sqc"
      sql_setdlist[2].sqldata = (void*)errname;
#line 185 "Xeerrmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 185 "Xeerrmst.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 185 "Xeerrmst.sqc"
      sql_setdlist[3].sqldata = (void*)&sksri;
#line 185 "Xeerrmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 185 "Xeerrmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 185 "Xeerrmst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 185 "Xeerrmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 185 "Xeerrmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 185 "Xeerrmst.sqc"
      sql_setdlist[5].sqldata = (void*)haiymd;
#line 185 "Xeerrmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 185 "Xeerrmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 9;
#line 185 "Xeerrmst.sqc"
      sql_setdlist[6].sqldata = (void*)hnktntid;
#line 185 "Xeerrmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 185 "Xeerrmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 185 "Xeerrmst.sqc"
      sql_setdlist[7].sqldata = (void*)ksndh;
#line 185 "Xeerrmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 185 "Xeerrmst.sqc"
      sqlasetdata(3,0,8,sql_setdlist,0L,0L);
    }
#line 185 "Xeerrmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 185 "Xeerrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 185 "Xeerrmst.sqc"
  sqlastop(0L);
}

#line 185 "Xeerrmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Xeerrmst*)ZbmlRealloc( array,
                                    sizeof( Xeerrmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Xeerrmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, XeerrmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 200 "Xeerrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 200 "Xeerrmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 200 "Xeerrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 200 "Xeerrmst.sqc"
  sqlastop(0L);
}

#line 200 "Xeerrmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 208 "Xeerrmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbXeerrmstInsert()
 *    XEERRMST レコードを挿入する
 * ■引数
 *    [I]  Xeerrmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbXeerrmstInsert( Xeerrmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, XeerrmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 231 "Xeerrmst.sqc"


    
/*
EXEC SQL INSERT INTO XEERRMST
    (
		ERRFLG,
		FLGSBT,
		ERRNAME,
		SKSRI,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:errflg,
		:flgsbt,
		:errname,
		:sksri,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 252 "Xeerrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 252 "Xeerrmst.sqc"
  sqlaaloc(2,8,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 252 "Xeerrmst.sqc"
      sql_setdlist[0].sqltype = 500; sql_setdlist[0].sqllen = 2;
#line 252 "Xeerrmst.sqc"
      sql_setdlist[0].sqldata = (void*)&errflg;
#line 252 "Xeerrmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 252 "Xeerrmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 252 "Xeerrmst.sqc"
      sql_setdlist[1].sqldata = (void*)flgsbt;
#line 252 "Xeerrmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 252 "Xeerrmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 33;
#line 252 "Xeerrmst.sqc"
      sql_setdlist[2].sqldata = (void*)errname;
#line 252 "Xeerrmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 252 "Xeerrmst.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 252 "Xeerrmst.sqc"
      sql_setdlist[3].sqldata = (void*)&sksri;
#line 252 "Xeerrmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 252 "Xeerrmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 252 "Xeerrmst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 252 "Xeerrmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 252 "Xeerrmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 252 "Xeerrmst.sqc"
      sql_setdlist[5].sqldata = (void*)haiymd;
#line 252 "Xeerrmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 252 "Xeerrmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 9;
#line 252 "Xeerrmst.sqc"
      sql_setdlist[6].sqldata = (void*)hnktntid;
#line 252 "Xeerrmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 252 "Xeerrmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 252 "Xeerrmst.sqc"
      sql_setdlist[7].sqldata = (void*)ksndh;
#line 252 "Xeerrmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 252 "Xeerrmst.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 252 "Xeerrmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 252 "Xeerrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 252 "Xeerrmst.sqc"
  sqlastop(0L);
}

#line 252 "Xeerrmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 257 "Xeerrmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbXeerrmstUpdate()
 *    XEERRMST レコードを更新する
 * ■引数
 *    [I]  Xeerrmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbXeerrmstUpdate( Xeerrmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, XeerrmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 281 "Xeerrmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 282 "Xeerrmst.sqc"


    
/*
EXEC SQL UPDATE XEERRMST
    SET (
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		ERRFLG = :errflg AND
		FLGSBT = :flgsbt AND
		ERRNAME      = :errname      AND
		SKSRI = :sksri AND
		KAIYMD = :kaiymd;
*/

{
#line 298 "Xeerrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 298 "Xeerrmst.sqc"
  sqlaaloc(2,8,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 298 "Xeerrmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 298 "Xeerrmst.sqc"
      sql_setdlist[0].sqldata = (void*)haiymd;
#line 298 "Xeerrmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 298 "Xeerrmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 9;
#line 298 "Xeerrmst.sqc"
      sql_setdlist[1].sqldata = (void*)hnktntid;
#line 298 "Xeerrmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 298 "Xeerrmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 27;
#line 298 "Xeerrmst.sqc"
      sql_setdlist[2].sqldata = (void*)ksndh;
#line 298 "Xeerrmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 298 "Xeerrmst.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 298 "Xeerrmst.sqc"
      sql_setdlist[3].sqldata = (void*)&errflg;
#line 298 "Xeerrmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 298 "Xeerrmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 298 "Xeerrmst.sqc"
      sql_setdlist[4].sqldata = (void*)flgsbt;
#line 298 "Xeerrmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 298 "Xeerrmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 33;
#line 298 "Xeerrmst.sqc"
      sql_setdlist[5].sqldata = (void*)errname;
#line 298 "Xeerrmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 298 "Xeerrmst.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 298 "Xeerrmst.sqc"
      sql_setdlist[6].sqldata = (void*)&sksri;
#line 298 "Xeerrmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 298 "Xeerrmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 298 "Xeerrmst.sqc"
      sql_setdlist[7].sqldata = (void*)kaiymd;
#line 298 "Xeerrmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 298 "Xeerrmst.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 298 "Xeerrmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 298 "Xeerrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 298 "Xeerrmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 298 "Xeerrmst.sqc"
  sqlastop(0L);
}

#line 298 "Xeerrmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 303 "Xeerrmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 307 "Xeerrmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbXeerrmstDelete()
 *    XEERRMST レコードを削除する
 * ■引数
 *    [I]  Xeerrmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbXeerrmstDelete( Xeerrmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, XeerrmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 331 "Xeerrmst.sqc"


    
/*
EXEC SQL DELETE FROM XEERRMST
    WHERE
		ERRFLG = :errflg AND
		FLGSBT = :flgsbt AND
		ERRNAME      = :errname      AND
		SKSRI = :sksri AND
		KAIYMD = :kaiymd;
*/

{
#line 339 "Xeerrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 339 "Xeerrmst.sqc"
  sqlaaloc(2,5,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 339 "Xeerrmst.sqc"
      sql_setdlist[0].sqltype = 500; sql_setdlist[0].sqllen = 2;
#line 339 "Xeerrmst.sqc"
      sql_setdlist[0].sqldata = (void*)&errflg;
#line 339 "Xeerrmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 339 "Xeerrmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 339 "Xeerrmst.sqc"
      sql_setdlist[1].sqldata = (void*)flgsbt;
#line 339 "Xeerrmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 339 "Xeerrmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 33;
#line 339 "Xeerrmst.sqc"
      sql_setdlist[2].sqldata = (void*)errname;
#line 339 "Xeerrmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 339 "Xeerrmst.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 339 "Xeerrmst.sqc"
      sql_setdlist[3].sqldata = (void*)&sksri;
#line 339 "Xeerrmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 339 "Xeerrmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 339 "Xeerrmst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 339 "Xeerrmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 339 "Xeerrmst.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 339 "Xeerrmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 339 "Xeerrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 339 "Xeerrmst.sqc"
  sqlastop(0L);
}

#line 339 "Xeerrmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 344 "Xeerrmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
