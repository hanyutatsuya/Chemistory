static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,121,65,86,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,54,50,90,83,75,67,72,32,0,0,0,0,0,0,0,0,
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


#line 1 "Skchkmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Skchkmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Skchkmst.h"
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


#line 24 "Skchkmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Skchkmst.sqc"

	char    knsgrp[17];
	char    kmkcd[8];
	char    sstcd[8];
	char    zaicd[5];
	short   krknsgrp[11];
	char    soukan[129];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 40 "Skchkmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Skchkmst

BmlDMMInfo	SkchkmstArray[] = {
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( sstcd ),
	DMM_SSTRING( zaicd ),
	DMM_SSHORT( krknsgrp ),
	DMM_SSTRING( soukan ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbSkchkmstSelectAll()
 *    SKCHKMST レコード全件取得
 * ■引数
 *    [O]  Skchkmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbSkchkmstSelectAll( Skchkmst** arrayOut, int* numOut )
{
    Skchkmst*   array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 78 "Skchkmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSGRP,
		KMKCD,
		SSTCD,
		ZAICD,
		KRKNSGRP,
		SOUKAN,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        SKCHKMST FOR READ ONLY;
*/

#line 93 "Skchkmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 95 "Skchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 95 "Skchkmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 95 "Skchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 95 "Skchkmst.sqc"
  sqlastop(0L);
}

#line 95 "Skchkmst.sqc"


    while( 1 ) {
        Skchkmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knsgrp,
			:kmkcd,
			:sstcd,
			:zaicd,
			:krknsgrp,
			:soukan,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 110 "Skchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 110 "Skchkmst.sqc"
  sqlaaloc(3,10,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 110 "Skchkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 110 "Skchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 110 "Skchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 110 "Skchkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 110 "Skchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 110 "Skchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 110 "Skchkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 110 "Skchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)sstcd;
#line 110 "Skchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 110 "Skchkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 110 "Skchkmst.sqc"
      sql_setdlist[3].sqldata = (void*)zaicd;
#line 110 "Skchkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 110 "Skchkmst.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 110 "Skchkmst.sqc"
      sql_setdlist[4].sqldata = (void*)&krknsgrp[0];
#line 110 "Skchkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 110 "Skchkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 129;
#line 110 "Skchkmst.sqc"
      sql_setdlist[5].sqldata = (void*)soukan;
#line 110 "Skchkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 110 "Skchkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 110 "Skchkmst.sqc"
      sql_setdlist[6].sqldata = (void*)kaiymd;
#line 110 "Skchkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 110 "Skchkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 110 "Skchkmst.sqc"
      sql_setdlist[7].sqldata = (void*)haiymd;
#line 110 "Skchkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 110 "Skchkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 110 "Skchkmst.sqc"
      sql_setdlist[8].sqldata = (void*)hnktntid;
#line 110 "Skchkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 110 "Skchkmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 110 "Skchkmst.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 110 "Skchkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 110 "Skchkmst.sqc"
      sqlasetdata(3,0,10,sql_setdlist,0L,0L);
    }
#line 110 "Skchkmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 110 "Skchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 110 "Skchkmst.sqc"
  sqlastop(0L);
}

#line 110 "Skchkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Skchkmst*)ZbmlRealloc( array,
                                    sizeof( Skchkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Skchkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, SkchkmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 125 "Skchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 125 "Skchkmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 125 "Skchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 125 "Skchkmst.sqc"
  sqlastop(0L);
}

#line 125 "Skchkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 133 "Skchkmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbSkchkmstSelectKey()
 *    SKCHKMST レコードKey条件取得
 * ■引数
 *    [I]  Skchkmst* pKey       取得するレコードのキー
 *    [O]  Skchkmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbSkchkmstSelectKey( Skchkmst* pKey, Skchkmst** arrayOut, int* numOut )
{
    Skchkmst*   array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, SkchkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 159 "Skchkmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSGRP,
		KMKCD,
		SSTCD,
		ZAICD,
		KRKNSGRP,
		SOUKAN,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        SKCHKMST
    WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		SSTCD = :sstcd AND
		ZAICD = :zaicd AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 180 "Skchkmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 182 "Skchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 182 "Skchkmst.sqc"
  sqlaaloc(2,5,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 182 "Skchkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 182 "Skchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 182 "Skchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 182 "Skchkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 182 "Skchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 182 "Skchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 182 "Skchkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 182 "Skchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)sstcd;
#line 182 "Skchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 182 "Skchkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 182 "Skchkmst.sqc"
      sql_setdlist[3].sqldata = (void*)zaicd;
#line 182 "Skchkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 182 "Skchkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 182 "Skchkmst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 182 "Skchkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 182 "Skchkmst.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 182 "Skchkmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 182 "Skchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 182 "Skchkmst.sqc"
  sqlastop(0L);
}

#line 182 "Skchkmst.sqc"


    while( 1 ) {
        Skchkmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knsgrp,
			:kmkcd,
			:sstcd,
			:zaicd,
			:krknsgrp,
			:soukan,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 197 "Skchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 197 "Skchkmst.sqc"
  sqlaaloc(3,10,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 197 "Skchkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 197 "Skchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 197 "Skchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 197 "Skchkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 197 "Skchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 197 "Skchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 197 "Skchkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 197 "Skchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)sstcd;
#line 197 "Skchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 197 "Skchkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 197 "Skchkmst.sqc"
      sql_setdlist[3].sqldata = (void*)zaicd;
#line 197 "Skchkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 197 "Skchkmst.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 197 "Skchkmst.sqc"
      sql_setdlist[4].sqldata = (void*)&krknsgrp[0];
#line 197 "Skchkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 197 "Skchkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 129;
#line 197 "Skchkmst.sqc"
      sql_setdlist[5].sqldata = (void*)soukan;
#line 197 "Skchkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 197 "Skchkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 197 "Skchkmst.sqc"
      sql_setdlist[6].sqldata = (void*)kaiymd;
#line 197 "Skchkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 197 "Skchkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 197 "Skchkmst.sqc"
      sql_setdlist[7].sqldata = (void*)haiymd;
#line 197 "Skchkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 197 "Skchkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 197 "Skchkmst.sqc"
      sql_setdlist[8].sqldata = (void*)hnktntid;
#line 197 "Skchkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 197 "Skchkmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 197 "Skchkmst.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 197 "Skchkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 197 "Skchkmst.sqc"
      sqlasetdata(3,0,10,sql_setdlist,0L,0L);
    }
#line 197 "Skchkmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 197 "Skchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 197 "Skchkmst.sqc"
  sqlastop(0L);
}

#line 197 "Skchkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Skchkmst*)ZbmlRealloc( array,
                                    sizeof( Skchkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Skchkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, SkchkmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 212 "Skchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 212 "Skchkmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 212 "Skchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 212 "Skchkmst.sqc"
  sqlastop(0L);
}

#line 212 "Skchkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 220 "Skchkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbSkchkmstInsert()
 *    SKCHKMST レコードを挿入する
 * ■引数
 *    [I]  Skchkmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbSkchkmstInsert( Skchkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, SkchkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 243 "Skchkmst.sqc"


    
/*
EXEC SQL INSERT INTO SKCHKMST
    (
		KNSGRP,
		KMKCD,
		SSTCD,
		ZAICD,
		KRKNSGRP,
		SOUKAN,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:knsgrp,
		:kmkcd,
		:sstcd,
		:zaicd,
		:krknsgrp,
		:soukan,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 268 "Skchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 268 "Skchkmst.sqc"
  sqlaaloc(2,10,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 268 "Skchkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 268 "Skchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 268 "Skchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 268 "Skchkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 268 "Skchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 268 "Skchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 268 "Skchkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 268 "Skchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)sstcd;
#line 268 "Skchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 268 "Skchkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 268 "Skchkmst.sqc"
      sql_setdlist[3].sqldata = (void*)zaicd;
#line 268 "Skchkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 268 "Skchkmst.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 268 "Skchkmst.sqc"
      sql_setdlist[4].sqldata = (void*)&krknsgrp[0];
#line 268 "Skchkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 268 "Skchkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 129;
#line 268 "Skchkmst.sqc"
      sql_setdlist[5].sqldata = (void*)soukan;
#line 268 "Skchkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 268 "Skchkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 268 "Skchkmst.sqc"
      sql_setdlist[6].sqldata = (void*)kaiymd;
#line 268 "Skchkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 268 "Skchkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 268 "Skchkmst.sqc"
      sql_setdlist[7].sqldata = (void*)haiymd;
#line 268 "Skchkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 268 "Skchkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 268 "Skchkmst.sqc"
      sql_setdlist[8].sqldata = (void*)hnktntid;
#line 268 "Skchkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 268 "Skchkmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 268 "Skchkmst.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 268 "Skchkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 268 "Skchkmst.sqc"
      sqlasetdata(2,0,10,sql_setdlist,0L,0L);
    }
#line 268 "Skchkmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 268 "Skchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 268 "Skchkmst.sqc"
  sqlastop(0L);
}

#line 268 "Skchkmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 273 "Skchkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbSkchkmstUpdate()
 *    SKCHKMST レコードを更新する
 * ■引数
 *    [I]  Skchkmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbSkchkmstUpdate( Skchkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, SkchkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 297 "Skchkmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 298 "Skchkmst.sqc"


    
/*
EXEC SQL UPDATE SKCHKMST
    SET (
		KRKNSGRP,
		SOUKAN,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:krknsgrp,
		:soukan,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		SSTCD = :sstcd AND
		ZAICD = :zaicd AND
		KAIYMD = :kaiymd;
*/

{
#line 318 "Skchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 318 "Skchkmst.sqc"
  sqlaaloc(2,10,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 318 "Skchkmst.sqc"
      sql_setdlist[0].sqltype = 500; sql_setdlist[0].sqllen = 2;
#line 318 "Skchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)&krknsgrp[0];
#line 318 "Skchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 318 "Skchkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 129;
#line 318 "Skchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)soukan;
#line 318 "Skchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 318 "Skchkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 318 "Skchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)haiymd;
#line 318 "Skchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 318 "Skchkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 9;
#line 318 "Skchkmst.sqc"
      sql_setdlist[3].sqldata = (void*)hnktntid;
#line 318 "Skchkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 318 "Skchkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 27;
#line 318 "Skchkmst.sqc"
      sql_setdlist[4].sqldata = (void*)ksndh;
#line 318 "Skchkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 318 "Skchkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 17;
#line 318 "Skchkmst.sqc"
      sql_setdlist[5].sqldata = (void*)knsgrp;
#line 318 "Skchkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 318 "Skchkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 318 "Skchkmst.sqc"
      sql_setdlist[6].sqldata = (void*)kmkcd;
#line 318 "Skchkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 318 "Skchkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 8;
#line 318 "Skchkmst.sqc"
      sql_setdlist[7].sqldata = (void*)sstcd;
#line 318 "Skchkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 318 "Skchkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 5;
#line 318 "Skchkmst.sqc"
      sql_setdlist[8].sqldata = (void*)zaicd;
#line 318 "Skchkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 318 "Skchkmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 318 "Skchkmst.sqc"
      sql_setdlist[9].sqldata = (void*)kaiymd;
#line 318 "Skchkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 318 "Skchkmst.sqc"
      sqlasetdata(2,0,10,sql_setdlist,0L,0L);
    }
#line 318 "Skchkmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 318 "Skchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 318 "Skchkmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 318 "Skchkmst.sqc"
  sqlastop(0L);
}

#line 318 "Skchkmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 323 "Skchkmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 327 "Skchkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbSkchkmstDelete()
 *    SKCHKMST レコードを削除する
 * ■引数
 *    [I]  Skchkmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbSkchkmstDelete( Skchkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, SkchkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 351 "Skchkmst.sqc"


    
/*
EXEC SQL DELETE FROM SKCHKMST
    WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		SSTCD = :sstcd AND
		ZAICD = :zaicd AND
		KAIYMD = :kaiymd;
*/

{
#line 359 "Skchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 359 "Skchkmst.sqc"
  sqlaaloc(2,5,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 359 "Skchkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 359 "Skchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 359 "Skchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 359 "Skchkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 359 "Skchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 359 "Skchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 359 "Skchkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 359 "Skchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)sstcd;
#line 359 "Skchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 359 "Skchkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 359 "Skchkmst.sqc"
      sql_setdlist[3].sqldata = (void*)zaicd;
#line 359 "Skchkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 359 "Skchkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 359 "Skchkmst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 359 "Skchkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 359 "Skchkmst.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 359 "Skchkmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 359 "Skchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 359 "Skchkmst.sqc"
  sqlastop(0L);
}

#line 359 "Skchkmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 364 "Skchkmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
