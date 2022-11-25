static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,66,65,86,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,53,54,90,80,82,67,83,32,0,0,0,0,0,0,0,0,
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


#line 1 "Prcsmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Prcsmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Prcsmst.h"
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


#line 24 "Prcsmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Prcsmst.sqc"

	short   pgid;
	char    prno[11];
	char    lmname[21];
	char    krknsgrp[11];
	short   lmtype;
	char    wsname[17];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 40 "Prcsmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Prcsmst

BmlDMMInfo	PrcsmstArray[] = {
	DMM_SSHORT( pgid ),
	DMM_SSTRING( prno ),
	DMM_SSTRING( lmname ),
	DMM_SSTRING( krknsgrp ),
	DMM_SSHORT( lmtype ),
	DMM_SSTRING( wsname ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbPrcsmstSelectAll()
 *    PRCSMST レコード全件取得
 * ■引数
 *    [O]  Prcsmst** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbPrcsmstSelectAll( Prcsmst** arrayOut, int* numOut )
{
    Prcsmst*    array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 78 "Prcsmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		PGID,
		PRNO,
		LMNAME,
		KRKNSGRP,
		LMTYPE,
		WSNAME,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        PRCSMST FOR READ ONLY;
*/

#line 93 "Prcsmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 95 "Prcsmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 95 "Prcsmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 95 "Prcsmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 95 "Prcsmst.sqc"
  sqlastop(0L);
}

#line 95 "Prcsmst.sqc"


    while( 1 ) {
        Prcsmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:pgid,
			:prno,
			:lmname,
			:krknsgrp,
			:lmtype,
			:wsname,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 110 "Prcsmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 110 "Prcsmst.sqc"
  sqlaaloc(3,10,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 110 "Prcsmst.sqc"
      sql_setdlist[0].sqltype = 500; sql_setdlist[0].sqllen = 2;
#line 110 "Prcsmst.sqc"
      sql_setdlist[0].sqldata = (void*)&pgid;
#line 110 "Prcsmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 110 "Prcsmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 110 "Prcsmst.sqc"
      sql_setdlist[1].sqldata = (void*)prno;
#line 110 "Prcsmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 110 "Prcsmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 110 "Prcsmst.sqc"
      sql_setdlist[2].sqldata = (void*)lmname;
#line 110 "Prcsmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 110 "Prcsmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 110 "Prcsmst.sqc"
      sql_setdlist[3].sqldata = (void*)krknsgrp;
#line 110 "Prcsmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 110 "Prcsmst.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 110 "Prcsmst.sqc"
      sql_setdlist[4].sqldata = (void*)&lmtype;
#line 110 "Prcsmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 110 "Prcsmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 17;
#line 110 "Prcsmst.sqc"
      sql_setdlist[5].sqldata = (void*)wsname;
#line 110 "Prcsmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 110 "Prcsmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 110 "Prcsmst.sqc"
      sql_setdlist[6].sqldata = (void*)kaiymd;
#line 110 "Prcsmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 110 "Prcsmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 110 "Prcsmst.sqc"
      sql_setdlist[7].sqldata = (void*)haiymd;
#line 110 "Prcsmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 110 "Prcsmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 110 "Prcsmst.sqc"
      sql_setdlist[8].sqldata = (void*)hnktntid;
#line 110 "Prcsmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 110 "Prcsmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 110 "Prcsmst.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 110 "Prcsmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 110 "Prcsmst.sqc"
      sqlasetdata(3,0,10,sql_setdlist,0L,0L);
    }
#line 110 "Prcsmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 110 "Prcsmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 110 "Prcsmst.sqc"
  sqlastop(0L);
}

#line 110 "Prcsmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Prcsmst*)ZbmlRealloc( array,
                                    sizeof( Prcsmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Prcsmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, PrcsmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 125 "Prcsmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 125 "Prcsmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 125 "Prcsmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 125 "Prcsmst.sqc"
  sqlastop(0L);
}

#line 125 "Prcsmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 133 "Prcsmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbPrcsmstSelectKey()
 *    PRCSMST レコードKey条件取得
 * ■引数
 *    [I]  Prcsmst* pKey       取得するレコードのキー
 *    [O]  Prcsmst** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbPrcsmstSelectKey( Prcsmst* pKey, Prcsmst** arrayOut, int* numOut )
{
    Prcsmst*    array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, PrcsmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 159 "Prcsmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		PGID,
		PRNO,
		LMNAME,
		KRKNSGRP,
		LMTYPE,
		WSNAME,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        PRCSMST
    WHERE
		PGID         = :pgid         AND
		PRNO = :prno AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 178 "Prcsmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 180 "Prcsmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 180 "Prcsmst.sqc"
  sqlaaloc(2,3,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 180 "Prcsmst.sqc"
      sql_setdlist[0].sqltype = 500; sql_setdlist[0].sqllen = 2;
#line 180 "Prcsmst.sqc"
      sql_setdlist[0].sqldata = (void*)&pgid;
#line 180 "Prcsmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 180 "Prcsmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 180 "Prcsmst.sqc"
      sql_setdlist[1].sqldata = (void*)prno;
#line 180 "Prcsmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 180 "Prcsmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 180 "Prcsmst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 180 "Prcsmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 180 "Prcsmst.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 180 "Prcsmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 180 "Prcsmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 180 "Prcsmst.sqc"
  sqlastop(0L);
}

#line 180 "Prcsmst.sqc"


    while( 1 ) {
        Prcsmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:pgid,
			:prno,
			:lmname,
			:krknsgrp,
			:lmtype,
			:wsname,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 195 "Prcsmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 195 "Prcsmst.sqc"
  sqlaaloc(3,10,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 195 "Prcsmst.sqc"
      sql_setdlist[0].sqltype = 500; sql_setdlist[0].sqllen = 2;
#line 195 "Prcsmst.sqc"
      sql_setdlist[0].sqldata = (void*)&pgid;
#line 195 "Prcsmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 195 "Prcsmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 195 "Prcsmst.sqc"
      sql_setdlist[1].sqldata = (void*)prno;
#line 195 "Prcsmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 195 "Prcsmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 195 "Prcsmst.sqc"
      sql_setdlist[2].sqldata = (void*)lmname;
#line 195 "Prcsmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 195 "Prcsmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 195 "Prcsmst.sqc"
      sql_setdlist[3].sqldata = (void*)krknsgrp;
#line 195 "Prcsmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 195 "Prcsmst.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 195 "Prcsmst.sqc"
      sql_setdlist[4].sqldata = (void*)&lmtype;
#line 195 "Prcsmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 195 "Prcsmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 17;
#line 195 "Prcsmst.sqc"
      sql_setdlist[5].sqldata = (void*)wsname;
#line 195 "Prcsmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 195 "Prcsmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 195 "Prcsmst.sqc"
      sql_setdlist[6].sqldata = (void*)kaiymd;
#line 195 "Prcsmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 195 "Prcsmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 195 "Prcsmst.sqc"
      sql_setdlist[7].sqldata = (void*)haiymd;
#line 195 "Prcsmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 195 "Prcsmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 195 "Prcsmst.sqc"
      sql_setdlist[8].sqldata = (void*)hnktntid;
#line 195 "Prcsmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 195 "Prcsmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 195 "Prcsmst.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 195 "Prcsmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 195 "Prcsmst.sqc"
      sqlasetdata(3,0,10,sql_setdlist,0L,0L);
    }
#line 195 "Prcsmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 195 "Prcsmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 195 "Prcsmst.sqc"
  sqlastop(0L);
}

#line 195 "Prcsmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Prcsmst*)ZbmlRealloc( array,
                                    sizeof( Prcsmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Prcsmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, PrcsmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 210 "Prcsmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 210 "Prcsmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 210 "Prcsmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 210 "Prcsmst.sqc"
  sqlastop(0L);
}

#line 210 "Prcsmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 218 "Prcsmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbPrcsmstInsert()
 *    PRCSMST レコードを挿入する
 * ■引数
 *    [I]  Prcsmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbPrcsmstInsert( Prcsmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, PrcsmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 241 "Prcsmst.sqc"


    
/*
EXEC SQL INSERT INTO PRCSMST
    (
		PGID,
		PRNO,
		LMNAME,
		KRKNSGRP,
		LMTYPE,
		WSNAME,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:pgid,
		:prno,
		:lmname,
		:krknsgrp,
		:lmtype,
		:wsname,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 266 "Prcsmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 266 "Prcsmst.sqc"
  sqlaaloc(2,10,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 266 "Prcsmst.sqc"
      sql_setdlist[0].sqltype = 500; sql_setdlist[0].sqllen = 2;
#line 266 "Prcsmst.sqc"
      sql_setdlist[0].sqldata = (void*)&pgid;
#line 266 "Prcsmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 266 "Prcsmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 266 "Prcsmst.sqc"
      sql_setdlist[1].sqldata = (void*)prno;
#line 266 "Prcsmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 266 "Prcsmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 266 "Prcsmst.sqc"
      sql_setdlist[2].sqldata = (void*)lmname;
#line 266 "Prcsmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 266 "Prcsmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 266 "Prcsmst.sqc"
      sql_setdlist[3].sqldata = (void*)krknsgrp;
#line 266 "Prcsmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 266 "Prcsmst.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 266 "Prcsmst.sqc"
      sql_setdlist[4].sqldata = (void*)&lmtype;
#line 266 "Prcsmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 266 "Prcsmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 17;
#line 266 "Prcsmst.sqc"
      sql_setdlist[5].sqldata = (void*)wsname;
#line 266 "Prcsmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 266 "Prcsmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 266 "Prcsmst.sqc"
      sql_setdlist[6].sqldata = (void*)kaiymd;
#line 266 "Prcsmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 266 "Prcsmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 266 "Prcsmst.sqc"
      sql_setdlist[7].sqldata = (void*)haiymd;
#line 266 "Prcsmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 266 "Prcsmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 266 "Prcsmst.sqc"
      sql_setdlist[8].sqldata = (void*)hnktntid;
#line 266 "Prcsmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 266 "Prcsmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 266 "Prcsmst.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 266 "Prcsmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 266 "Prcsmst.sqc"
      sqlasetdata(2,0,10,sql_setdlist,0L,0L);
    }
#line 266 "Prcsmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 266 "Prcsmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 266 "Prcsmst.sqc"
  sqlastop(0L);
}

#line 266 "Prcsmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 271 "Prcsmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbPrcsmstUpdate()
 *    PRCSMST レコードを更新する
 * ■引数
 *    [I]  Prcsmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbPrcsmstUpdate( Prcsmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, PrcsmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 295 "Prcsmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 296 "Prcsmst.sqc"


    
/*
EXEC SQL UPDATE PRCSMST
    SET (
		LMNAME,
		KRKNSGRP,
		LMTYPE,
		WSNAME,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:lmname,
		:krknsgrp,
		:lmtype,
		:wsname,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		PGID         = :pgid         AND
		PRNO = :prno AND
		KAIYMD = :kaiymd;
*/

{
#line 318 "Prcsmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 318 "Prcsmst.sqc"
  sqlaaloc(2,10,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 318 "Prcsmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 21;
#line 318 "Prcsmst.sqc"
      sql_setdlist[0].sqldata = (void*)lmname;
#line 318 "Prcsmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 318 "Prcsmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 318 "Prcsmst.sqc"
      sql_setdlist[1].sqldata = (void*)krknsgrp;
#line 318 "Prcsmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 318 "Prcsmst.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 318 "Prcsmst.sqc"
      sql_setdlist[2].sqldata = (void*)&lmtype;
#line 318 "Prcsmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 318 "Prcsmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 318 "Prcsmst.sqc"
      sql_setdlist[3].sqldata = (void*)wsname;
#line 318 "Prcsmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 318 "Prcsmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 318 "Prcsmst.sqc"
      sql_setdlist[4].sqldata = (void*)haiymd;
#line 318 "Prcsmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 318 "Prcsmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 9;
#line 318 "Prcsmst.sqc"
      sql_setdlist[5].sqldata = (void*)hnktntid;
#line 318 "Prcsmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 318 "Prcsmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 318 "Prcsmst.sqc"
      sql_setdlist[6].sqldata = (void*)ksndh;
#line 318 "Prcsmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 318 "Prcsmst.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 318 "Prcsmst.sqc"
      sql_setdlist[7].sqldata = (void*)&pgid;
#line 318 "Prcsmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 318 "Prcsmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 318 "Prcsmst.sqc"
      sql_setdlist[8].sqldata = (void*)prno;
#line 318 "Prcsmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 318 "Prcsmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 318 "Prcsmst.sqc"
      sql_setdlist[9].sqldata = (void*)kaiymd;
#line 318 "Prcsmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 318 "Prcsmst.sqc"
      sqlasetdata(2,0,10,sql_setdlist,0L,0L);
    }
#line 318 "Prcsmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 318 "Prcsmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 318 "Prcsmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 318 "Prcsmst.sqc"
  sqlastop(0L);
}

#line 318 "Prcsmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 323 "Prcsmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 327 "Prcsmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbPrcsmstDelete()
 *    PRCSMST レコードを削除する
 * ■引数
 *    [I]  Prcsmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbPrcsmstDelete( Prcsmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, PrcsmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 351 "Prcsmst.sqc"


    
/*
EXEC SQL DELETE FROM PRCSMST
    WHERE
		PGID         = :pgid         AND
		PRNO = :prno AND
		KAIYMD = :kaiymd;
*/

{
#line 357 "Prcsmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 357 "Prcsmst.sqc"
  sqlaaloc(2,3,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 357 "Prcsmst.sqc"
      sql_setdlist[0].sqltype = 500; sql_setdlist[0].sqllen = 2;
#line 357 "Prcsmst.sqc"
      sql_setdlist[0].sqldata = (void*)&pgid;
#line 357 "Prcsmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 357 "Prcsmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 357 "Prcsmst.sqc"
      sql_setdlist[1].sqldata = (void*)prno;
#line 357 "Prcsmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 357 "Prcsmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 357 "Prcsmst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 357 "Prcsmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 357 "Prcsmst.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 357 "Prcsmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 357 "Prcsmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 357 "Prcsmst.sqc"
  sqlastop(0L);
}

#line 357 "Prcsmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 362 "Prcsmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
