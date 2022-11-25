static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,105,65,83,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,50,54,90,74,68,75,77,32,0,0,0,0,0,0,0,0,
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


#line 1 "Jdkmkmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Jdkmkmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Jdkmkmst.h"
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


#line 24 "Jdkmkmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Jdkmkmst.sqc"

	char    knsgrp[17];
	char    kmkcd[8];
	char    jknsgrp[17];
	char    jkmkcd[8];
	char    hhkumflg;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 39 "Jdkmkmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Jdkmkmst

BmlDMMInfo	JdkmkmstArray[] = {
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( jknsgrp ),
	DMM_SSTRING( jkmkcd ),
	DMM_SCHAR( hhkumflg ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbJdkmkmstSelectAll()
 *    JDKMKMST レコード全件取得
 * ■引数
 *    [O]  Jdkmkmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbJdkmkmstSelectAll( Jdkmkmst** arrayOut, int* numOut )
{
    Jdkmkmst*   array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 76 "Jdkmkmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSGRP,
		KMKCD,
		JKNSGRP,
		JKMKCD,
		HHKUMFLG,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        JDKMKMST FOR READ ONLY;
*/

#line 90 "Jdkmkmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 92 "Jdkmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 92 "Jdkmkmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 92 "Jdkmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 92 "Jdkmkmst.sqc"
  sqlastop(0L);
}

#line 92 "Jdkmkmst.sqc"


    while( 1 ) {
        Jdkmkmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knsgrp,
			:kmkcd,
			:jknsgrp,
			:jkmkcd,
			:hhkumflg,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 106 "Jdkmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 106 "Jdkmkmst.sqc"
  sqlaaloc(3,9,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 17;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)jknsgrp;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[3].sqldata = (void*)jkmkcd;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[4].sqldata = (void*)&hhkumflg;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[5].sqldata = (void*)kaiymd;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[6].sqldata = (void*)haiymd;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[7].sqldata = (void*)hnktntid;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 106 "Jdkmkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 106 "Jdkmkmst.sqc"
      sqlasetdata(3,0,9,sql_setdlist,0L,0L);
    }
#line 106 "Jdkmkmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 106 "Jdkmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 106 "Jdkmkmst.sqc"
  sqlastop(0L);
}

#line 106 "Jdkmkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Jdkmkmst*)ZbmlRealloc( array,
                                    sizeof( Jdkmkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Jdkmkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, JdkmkmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 121 "Jdkmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 121 "Jdkmkmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 121 "Jdkmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 121 "Jdkmkmst.sqc"
  sqlastop(0L);
}

#line 121 "Jdkmkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 129 "Jdkmkmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbJdkmkmstSelectKey()
 *    JDKMKMST レコードKey条件取得
 * ■引数
 *    [I]  Jdkmkmst* pKey       取得するレコードのキー
 *    [O]  Jdkmkmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbJdkmkmstSelectKey( Jdkmkmst* pKey, Jdkmkmst** arrayOut, int* numOut )
{
    Jdkmkmst*   array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, JdkmkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 155 "Jdkmkmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSGRP,
		KMKCD,
		JKNSGRP,
		JKMKCD,
		HHKUMFLG,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        JDKMKMST
    WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		JKNSGRP = :jknsgrp AND
		JKMKCD = :jkmkcd AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 175 "Jdkmkmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 177 "Jdkmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 177 "Jdkmkmst.sqc"
  sqlaaloc(2,5,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 177 "Jdkmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 177 "Jdkmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 177 "Jdkmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 177 "Jdkmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 177 "Jdkmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 177 "Jdkmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 177 "Jdkmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 17;
#line 177 "Jdkmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)jknsgrp;
#line 177 "Jdkmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 177 "Jdkmkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 177 "Jdkmkmst.sqc"
      sql_setdlist[3].sqldata = (void*)jkmkcd;
#line 177 "Jdkmkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 177 "Jdkmkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 177 "Jdkmkmst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 177 "Jdkmkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 177 "Jdkmkmst.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 177 "Jdkmkmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 177 "Jdkmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 177 "Jdkmkmst.sqc"
  sqlastop(0L);
}

#line 177 "Jdkmkmst.sqc"


    while( 1 ) {
        Jdkmkmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knsgrp,
			:kmkcd,
			:jknsgrp,
			:jkmkcd,
			:hhkumflg,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 191 "Jdkmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 191 "Jdkmkmst.sqc"
  sqlaaloc(3,9,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 17;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)jknsgrp;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[3].sqldata = (void*)jkmkcd;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[4].sqldata = (void*)&hhkumflg;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[5].sqldata = (void*)kaiymd;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[6].sqldata = (void*)haiymd;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[7].sqldata = (void*)hnktntid;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 191 "Jdkmkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 191 "Jdkmkmst.sqc"
      sqlasetdata(3,0,9,sql_setdlist,0L,0L);
    }
#line 191 "Jdkmkmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 191 "Jdkmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 191 "Jdkmkmst.sqc"
  sqlastop(0L);
}

#line 191 "Jdkmkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Jdkmkmst*)ZbmlRealloc( array,
                                    sizeof( Jdkmkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Jdkmkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, JdkmkmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 206 "Jdkmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 206 "Jdkmkmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 206 "Jdkmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 206 "Jdkmkmst.sqc"
  sqlastop(0L);
}

#line 206 "Jdkmkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 214 "Jdkmkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbJdkmkmstInsert()
 *    JDKMKMST レコードを挿入する
 * ■引数
 *    [I]  Jdkmkmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbJdkmkmstInsert( Jdkmkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, JdkmkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 237 "Jdkmkmst.sqc"


    
/*
EXEC SQL INSERT INTO JDKMKMST
    (
		KNSGRP,
		KMKCD,
		JKNSGRP,
		JKMKCD,
		HHKUMFLG,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:knsgrp,
		:kmkcd,
		:jknsgrp,
		:jkmkcd,
		:hhkumflg,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 260 "Jdkmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 260 "Jdkmkmst.sqc"
  sqlaaloc(2,9,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 17;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)jknsgrp;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[3].sqldata = (void*)jkmkcd;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[4].sqldata = (void*)&hhkumflg;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[5].sqldata = (void*)kaiymd;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[6].sqldata = (void*)haiymd;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[7].sqldata = (void*)hnktntid;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 260 "Jdkmkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 260 "Jdkmkmst.sqc"
      sqlasetdata(2,0,9,sql_setdlist,0L,0L);
    }
#line 260 "Jdkmkmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 260 "Jdkmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 260 "Jdkmkmst.sqc"
  sqlastop(0L);
}

#line 260 "Jdkmkmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 265 "Jdkmkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbJdkmkmstUpdate()
 *    JDKMKMST レコードを更新する
 * ■引数
 *    [I]  Jdkmkmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbJdkmkmstUpdate( Jdkmkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, JdkmkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 289 "Jdkmkmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 290 "Jdkmkmst.sqc"


    
/*
EXEC SQL UPDATE JDKMKMST
    SET (
		HHKUMFLG,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:hhkumflg,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		JKNSGRP = :jknsgrp AND
		JKMKCD = :jkmkcd AND
		KAIYMD = :kaiymd;
*/

{
#line 308 "Jdkmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 308 "Jdkmkmst.sqc"
  sqlaaloc(2,9,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)&hhkumflg;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)haiymd;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 9;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)hnktntid;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 27;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[3].sqldata = (void*)ksndh;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 17;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[6].sqldata = (void*)jknsgrp;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 8;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[7].sqldata = (void*)jkmkcd;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[8].sqldata = (void*)kaiymd;
#line 308 "Jdkmkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 308 "Jdkmkmst.sqc"
      sqlasetdata(2,0,9,sql_setdlist,0L,0L);
    }
#line 308 "Jdkmkmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 308 "Jdkmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 308 "Jdkmkmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 308 "Jdkmkmst.sqc"
  sqlastop(0L);
}

#line 308 "Jdkmkmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 313 "Jdkmkmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 317 "Jdkmkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbJdkmkmstDelete()
 *    JDKMKMST レコードを削除する
 * ■引数
 *    [I]  Jdkmkmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbJdkmkmstDelete( Jdkmkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, JdkmkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 341 "Jdkmkmst.sqc"


    
/*
EXEC SQL DELETE FROM JDKMKMST
    WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		JKNSGRP = :jknsgrp AND
		JKMKCD = :jkmkcd AND
		KAIYMD = :kaiymd;
*/

{
#line 349 "Jdkmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 349 "Jdkmkmst.sqc"
  sqlaaloc(2,5,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 349 "Jdkmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 349 "Jdkmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 349 "Jdkmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 349 "Jdkmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 349 "Jdkmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 349 "Jdkmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 349 "Jdkmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 17;
#line 349 "Jdkmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)jknsgrp;
#line 349 "Jdkmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 349 "Jdkmkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 349 "Jdkmkmst.sqc"
      sql_setdlist[3].sqldata = (void*)jkmkcd;
#line 349 "Jdkmkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 349 "Jdkmkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 349 "Jdkmkmst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 349 "Jdkmkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 349 "Jdkmkmst.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 349 "Jdkmkmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 349 "Jdkmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 349 "Jdkmkmst.sqc"
  sqlastop(0L);
}

#line 349 "Jdkmkmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 354 "Jdkmkmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
