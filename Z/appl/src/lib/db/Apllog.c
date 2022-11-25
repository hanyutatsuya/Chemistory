static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,79,66,80,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,49,90,65,80,76,76,32,32,0,0,0,0,0,0,0,0,
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


#line 1 "Apllog.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Apllog.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Apllog.h"
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


#line 24 "Apllog.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Apllog.sqc"

	char    sydate[11];
	char    sytime[9];
	char    tracekbn;
	char    pcname[33];
	sqlint32  proccessid;
	char    loginid[9];
	char    wkupapp[33];
	char    srcname[33];
	char    funcname[33];
	sqlint32  getline1;
	char    procflg[3];
	char    errcode[9];
	char    message[1025];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 43 "Apllog.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Apllog

BmlDMMInfo	ApllogArray[] = {
	DMM_SDATE( sydate ),
	DMM_STIME( sytime ),
	DMM_SCHAR( tracekbn ),
	DMM_SSTRING( pcname ),
	DMM_SLONG( proccessid ),
	DMM_SSTRING( loginid ),
	DMM_SSTRING( wkupapp ),
	DMM_SSTRING( srcname ),
	DMM_SSTRING( funcname ),
	DMM_SLONG( getline1 ),
	DMM_SSTRING( procflg ),
	DMM_SSTRING( errcode ),
	DMM_SSTRING( message ),
	DMM_NULL
};

/******************************************************************************
 * ZdbApllogSelectAll()
 *    APLLOG レコード全件取得
 * ■引数
 *    [O]  Apllog** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbApllogSelectAll( Apllog** arrayOut, int* numOut )
{
    Apllog*     array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 84 "Apllog.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		SYDATE,
		SYTIME,
		TRACEKBN,
		PCNAME,
		PROCCESSID,
		LOGINID,
		WKUPAPP,
		SRCNAME,
		FUNCNAME,
		GETLINE,
		PROCFLG,
		ERRCODE,
		MESSAGE
    FROM
        APLLOG FOR READ ONLY;
*/

#line 102 "Apllog.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 104 "Apllog.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 104 "Apllog.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 104 "Apllog.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 104 "Apllog.sqc"
  sqlastop(0L);
}

#line 104 "Apllog.sqc"


    while( 1 ) {
        Apllog* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:sydate,
			:sytime,
			:tracekbn,
			:pcname,
			:proccessid,
			:loginid,
			:wkupapp,
			:srcname,
			:funcname,
			:getline1,
			:procflg,
			:errcode,
			:message;
*/

{
#line 122 "Apllog.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 122 "Apllog.sqc"
  sqlaaloc(3,13,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[13];
#line 122 "Apllog.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 122 "Apllog.sqc"
      sql_setdlist[0].sqldata = (void*)sydate;
#line 122 "Apllog.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 122 "Apllog.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 9;
#line 122 "Apllog.sqc"
      sql_setdlist[1].sqldata = (void*)sytime;
#line 122 "Apllog.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 122 "Apllog.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 122 "Apllog.sqc"
      sql_setdlist[2].sqldata = (void*)&tracekbn;
#line 122 "Apllog.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 122 "Apllog.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 33;
#line 122 "Apllog.sqc"
      sql_setdlist[3].sqldata = (void*)pcname;
#line 122 "Apllog.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 122 "Apllog.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 122 "Apllog.sqc"
      sql_setdlist[4].sqldata = (void*)&proccessid;
#line 122 "Apllog.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 122 "Apllog.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 9;
#line 122 "Apllog.sqc"
      sql_setdlist[5].sqldata = (void*)loginid;
#line 122 "Apllog.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 122 "Apllog.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 33;
#line 122 "Apllog.sqc"
      sql_setdlist[6].sqldata = (void*)wkupapp;
#line 122 "Apllog.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 122 "Apllog.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 33;
#line 122 "Apllog.sqc"
      sql_setdlist[7].sqldata = (void*)srcname;
#line 122 "Apllog.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 122 "Apllog.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 33;
#line 122 "Apllog.sqc"
      sql_setdlist[8].sqldata = (void*)funcname;
#line 122 "Apllog.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 122 "Apllog.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 122 "Apllog.sqc"
      sql_setdlist[9].sqldata = (void*)&getline1;
#line 122 "Apllog.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 122 "Apllog.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 3;
#line 122 "Apllog.sqc"
      sql_setdlist[10].sqldata = (void*)procflg;
#line 122 "Apllog.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 122 "Apllog.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 122 "Apllog.sqc"
      sql_setdlist[11].sqldata = (void*)errcode;
#line 122 "Apllog.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 122 "Apllog.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 1025;
#line 122 "Apllog.sqc"
      sql_setdlist[12].sqldata = (void*)message;
#line 122 "Apllog.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 122 "Apllog.sqc"
      sqlasetdata(3,0,13,sql_setdlist,0L,0L);
    }
#line 122 "Apllog.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 122 "Apllog.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 122 "Apllog.sqc"
  sqlastop(0L);
}

#line 122 "Apllog.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Apllog*)ZbmlRealloc( array,
                                    sizeof( Apllog ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Apllog ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, ApllogArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 137 "Apllog.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 137 "Apllog.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 137 "Apllog.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 137 "Apllog.sqc"
  sqlastop(0L);
}

#line 137 "Apllog.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 145 "Apllog.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbApllogSelectKey()
 *    APLLOG レコードKey条件取得
 * ■引数
 *    [I]  Apllog* pKey       取得するレコードのキー
 *    [O]  Apllog** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbApllogSelectKey( Apllog* pKey, Apllog** arrayOut, int* numOut )
{
    Apllog*     array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, ApllogArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 171 "Apllog.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		SYDATE,
		SYTIME,
		TRACEKBN,
		PCNAME,
		PROCCESSID,
		LOGINID,
		WKUPAPP,
		SRCNAME,
		FUNCNAME,
		GETLINE,
		PROCFLG,
		ERRCODE,
		MESSAGE
    FROM
        APLLOG
    WHERE
		SYDATE = :sydate AND
		SYTIME = :sytime AND
		TRACEKBN = :tracekbn AND
		PCNAME = :pcname AND
		PROCCESSID = :proccessid FOR READ ONLY;
*/

#line 195 "Apllog.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 197 "Apllog.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 197 "Apllog.sqc"
  sqlaaloc(2,5,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 197 "Apllog.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 197 "Apllog.sqc"
      sql_setdlist[0].sqldata = (void*)sydate;
#line 197 "Apllog.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 197 "Apllog.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 9;
#line 197 "Apllog.sqc"
      sql_setdlist[1].sqldata = (void*)sytime;
#line 197 "Apllog.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 197 "Apllog.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 197 "Apllog.sqc"
      sql_setdlist[2].sqldata = (void*)&tracekbn;
#line 197 "Apllog.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 197 "Apllog.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 33;
#line 197 "Apllog.sqc"
      sql_setdlist[3].sqldata = (void*)pcname;
#line 197 "Apllog.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 197 "Apllog.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 197 "Apllog.sqc"
      sql_setdlist[4].sqldata = (void*)&proccessid;
#line 197 "Apllog.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 197 "Apllog.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 197 "Apllog.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 197 "Apllog.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 197 "Apllog.sqc"
  sqlastop(0L);
}

#line 197 "Apllog.sqc"


    while( 1 ) {
        Apllog* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:sydate,
			:sytime,
			:tracekbn,
			:pcname,
			:proccessid,
			:loginid,
			:wkupapp,
			:srcname,
			:funcname,
			:getline1,
			:procflg,
			:errcode,
			:message;
*/

{
#line 215 "Apllog.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 215 "Apllog.sqc"
  sqlaaloc(3,13,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[13];
#line 215 "Apllog.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 215 "Apllog.sqc"
      sql_setdlist[0].sqldata = (void*)sydate;
#line 215 "Apllog.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 215 "Apllog.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 9;
#line 215 "Apllog.sqc"
      sql_setdlist[1].sqldata = (void*)sytime;
#line 215 "Apllog.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 215 "Apllog.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 215 "Apllog.sqc"
      sql_setdlist[2].sqldata = (void*)&tracekbn;
#line 215 "Apllog.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 215 "Apllog.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 33;
#line 215 "Apllog.sqc"
      sql_setdlist[3].sqldata = (void*)pcname;
#line 215 "Apllog.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 215 "Apllog.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 215 "Apllog.sqc"
      sql_setdlist[4].sqldata = (void*)&proccessid;
#line 215 "Apllog.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 215 "Apllog.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 9;
#line 215 "Apllog.sqc"
      sql_setdlist[5].sqldata = (void*)loginid;
#line 215 "Apllog.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 215 "Apllog.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 33;
#line 215 "Apllog.sqc"
      sql_setdlist[6].sqldata = (void*)wkupapp;
#line 215 "Apllog.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 215 "Apllog.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 33;
#line 215 "Apllog.sqc"
      sql_setdlist[7].sqldata = (void*)srcname;
#line 215 "Apllog.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 215 "Apllog.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 33;
#line 215 "Apllog.sqc"
      sql_setdlist[8].sqldata = (void*)funcname;
#line 215 "Apllog.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 215 "Apllog.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 215 "Apllog.sqc"
      sql_setdlist[9].sqldata = (void*)&getline1;
#line 215 "Apllog.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 215 "Apllog.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 3;
#line 215 "Apllog.sqc"
      sql_setdlist[10].sqldata = (void*)procflg;
#line 215 "Apllog.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 215 "Apllog.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 215 "Apllog.sqc"
      sql_setdlist[11].sqldata = (void*)errcode;
#line 215 "Apllog.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 215 "Apllog.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 1025;
#line 215 "Apllog.sqc"
      sql_setdlist[12].sqldata = (void*)message;
#line 215 "Apllog.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 215 "Apllog.sqc"
      sqlasetdata(3,0,13,sql_setdlist,0L,0L);
    }
#line 215 "Apllog.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 215 "Apllog.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 215 "Apllog.sqc"
  sqlastop(0L);
}

#line 215 "Apllog.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Apllog*)ZbmlRealloc( array,
                                    sizeof( Apllog ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Apllog ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, ApllogArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 230 "Apllog.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 230 "Apllog.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 230 "Apllog.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 230 "Apllog.sqc"
  sqlastop(0L);
}

#line 230 "Apllog.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 238 "Apllog.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbApllogInsert()
 *    APLLOG レコードを挿入する
 * ■引数
 *    [I]  Apllog* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbApllogInsert( Apllog* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, ApllogArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 261 "Apllog.sqc"


    
/*
EXEC SQL INSERT INTO APLLOG
    (
		SYDATE,
		SYTIME,
		TRACEKBN,
		PCNAME,
		PROCCESSID,
		LOGINID,
		WKUPAPP,
		SRCNAME,
		FUNCNAME,
		GETLINE,
		PROCFLG,
		ERRCODE,
		MESSAGE
    ) VALUES (
		:sydate,
		:sytime,
		:tracekbn,
		:pcname,
		:proccessid,
		:loginid,
		:wkupapp,
		:srcname,
		:funcname,
		:getline1,
		:procflg,
		:errcode,
		:message
    );
*/

{
#line 292 "Apllog.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 292 "Apllog.sqc"
  sqlaaloc(2,13,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[13];
#line 292 "Apllog.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 292 "Apllog.sqc"
      sql_setdlist[0].sqldata = (void*)sydate;
#line 292 "Apllog.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 292 "Apllog.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 9;
#line 292 "Apllog.sqc"
      sql_setdlist[1].sqldata = (void*)sytime;
#line 292 "Apllog.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 292 "Apllog.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 292 "Apllog.sqc"
      sql_setdlist[2].sqldata = (void*)&tracekbn;
#line 292 "Apllog.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 292 "Apllog.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 33;
#line 292 "Apllog.sqc"
      sql_setdlist[3].sqldata = (void*)pcname;
#line 292 "Apllog.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 292 "Apllog.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 292 "Apllog.sqc"
      sql_setdlist[4].sqldata = (void*)&proccessid;
#line 292 "Apllog.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 292 "Apllog.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 9;
#line 292 "Apllog.sqc"
      sql_setdlist[5].sqldata = (void*)loginid;
#line 292 "Apllog.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 292 "Apllog.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 33;
#line 292 "Apllog.sqc"
      sql_setdlist[6].sqldata = (void*)wkupapp;
#line 292 "Apllog.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 292 "Apllog.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 33;
#line 292 "Apllog.sqc"
      sql_setdlist[7].sqldata = (void*)srcname;
#line 292 "Apllog.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 292 "Apllog.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 33;
#line 292 "Apllog.sqc"
      sql_setdlist[8].sqldata = (void*)funcname;
#line 292 "Apllog.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 292 "Apllog.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 292 "Apllog.sqc"
      sql_setdlist[9].sqldata = (void*)&getline1;
#line 292 "Apllog.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 292 "Apllog.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 3;
#line 292 "Apllog.sqc"
      sql_setdlist[10].sqldata = (void*)procflg;
#line 292 "Apllog.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 292 "Apllog.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 292 "Apllog.sqc"
      sql_setdlist[11].sqldata = (void*)errcode;
#line 292 "Apllog.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 292 "Apllog.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 1025;
#line 292 "Apllog.sqc"
      sql_setdlist[12].sqldata = (void*)message;
#line 292 "Apllog.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 292 "Apllog.sqc"
      sqlasetdata(2,0,13,sql_setdlist,0L,0L);
    }
#line 292 "Apllog.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 292 "Apllog.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 292 "Apllog.sqc"
  sqlastop(0L);
}

#line 292 "Apllog.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 297 "Apllog.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbApllogUpdate()
 *    APLLOG レコードを更新する
 * ■引数
 *    [I]  Apllog* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbApllogUpdate( Apllog* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, ApllogArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 321 "Apllog.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 322 "Apllog.sqc"


    
/*
EXEC SQL UPDATE APLLOG
    SET (
		LOGINID,
		WKUPAPP,
		SRCNAME,
		FUNCNAME,
		GETLINE,
		PROCFLG,
		ERRCODE,
		MESSAGE
    ) = (
		:loginid,
		:wkupapp,
		:srcname,
		:funcname,
		:getline1,
		:procflg,
		:errcode,
		:message
    ) WHERE
		SYDATE = :sydate AND
		SYTIME = :sytime AND
		TRACEKBN = :tracekbn AND
		PCNAME = :pcname AND
		PROCCESSID = :proccessid;
*/

{
#line 348 "Apllog.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 348 "Apllog.sqc"
  sqlaaloc(2,13,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[13];
#line 348 "Apllog.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 9;
#line 348 "Apllog.sqc"
      sql_setdlist[0].sqldata = (void*)loginid;
#line 348 "Apllog.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 348 "Apllog.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 33;
#line 348 "Apllog.sqc"
      sql_setdlist[1].sqldata = (void*)wkupapp;
#line 348 "Apllog.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 348 "Apllog.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 33;
#line 348 "Apllog.sqc"
      sql_setdlist[2].sqldata = (void*)srcname;
#line 348 "Apllog.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 348 "Apllog.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 33;
#line 348 "Apllog.sqc"
      sql_setdlist[3].sqldata = (void*)funcname;
#line 348 "Apllog.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 348 "Apllog.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 348 "Apllog.sqc"
      sql_setdlist[4].sqldata = (void*)&getline1;
#line 348 "Apllog.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 348 "Apllog.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 348 "Apllog.sqc"
      sql_setdlist[5].sqldata = (void*)procflg;
#line 348 "Apllog.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 348 "Apllog.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 9;
#line 348 "Apllog.sqc"
      sql_setdlist[6].sqldata = (void*)errcode;
#line 348 "Apllog.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 348 "Apllog.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 1025;
#line 348 "Apllog.sqc"
      sql_setdlist[7].sqldata = (void*)message;
#line 348 "Apllog.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 348 "Apllog.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 348 "Apllog.sqc"
      sql_setdlist[8].sqldata = (void*)sydate;
#line 348 "Apllog.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 348 "Apllog.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 9;
#line 348 "Apllog.sqc"
      sql_setdlist[9].sqldata = (void*)sytime;
#line 348 "Apllog.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 348 "Apllog.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 348 "Apllog.sqc"
      sql_setdlist[10].sqldata = (void*)&tracekbn;
#line 348 "Apllog.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 348 "Apllog.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 33;
#line 348 "Apllog.sqc"
      sql_setdlist[11].sqldata = (void*)pcname;
#line 348 "Apllog.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 348 "Apllog.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 348 "Apllog.sqc"
      sql_setdlist[12].sqldata = (void*)&proccessid;
#line 348 "Apllog.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 348 "Apllog.sqc"
      sqlasetdata(2,0,13,sql_setdlist,0L,0L);
    }
#line 348 "Apllog.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 348 "Apllog.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 348 "Apllog.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 348 "Apllog.sqc"
  sqlastop(0L);
}

#line 348 "Apllog.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 353 "Apllog.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 357 "Apllog.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbApllogDelete()
 *    APLLOG レコードを削除する
 * ■引数
 *    [I]  Apllog* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbApllogDelete( Apllog* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, ApllogArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 381 "Apllog.sqc"


    
/*
EXEC SQL DELETE FROM APLLOG
    WHERE
		SYDATE = :sydate AND
		SYTIME = :sytime AND
		TRACEKBN = :tracekbn AND
		PCNAME = :pcname AND
		PROCCESSID = :proccessid;
*/

{
#line 389 "Apllog.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 389 "Apllog.sqc"
  sqlaaloc(2,5,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 389 "Apllog.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 389 "Apllog.sqc"
      sql_setdlist[0].sqldata = (void*)sydate;
#line 389 "Apllog.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 389 "Apllog.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 9;
#line 389 "Apllog.sqc"
      sql_setdlist[1].sqldata = (void*)sytime;
#line 389 "Apllog.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 389 "Apllog.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 389 "Apllog.sqc"
      sql_setdlist[2].sqldata = (void*)&tracekbn;
#line 389 "Apllog.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 389 "Apllog.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 33;
#line 389 "Apllog.sqc"
      sql_setdlist[3].sqldata = (void*)pcname;
#line 389 "Apllog.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 389 "Apllog.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 389 "Apllog.sqc"
      sql_setdlist[4].sqldata = (void*)&proccessid;
#line 389 "Apllog.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 389 "Apllog.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 389 "Apllog.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 389 "Apllog.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 389 "Apllog.sqc"
  sqlastop(0L);
}

#line 389 "Apllog.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 394 "Apllog.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
