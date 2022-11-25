static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,104,66,86,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,54,55,90,83,83,84,83,32,0,0,0,0,0,0,0,0,
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


#line 1 "Sstsrmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Sstsrmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Sstsrmst.h"
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


#line 24 "Sstsrmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Sstsrmst.sqc"

	char    sstcd[8];
	char    knsgrp[17];
	char    kmkcd[8];
	char    syrsbt[4];
	char    prm1[51];
	char    prm2[51];
	char    prm3[51];
	char    prm4[51];
	char    prm5[51];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 43 "Sstsrmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Sstsrmst

BmlDMMInfo	SstsrmstArray[] = {
	DMM_SSTRING( sstcd ),
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( syrsbt ),
	DMM_SSTRING( prm1 ),
	DMM_SSTRING( prm2 ),
	DMM_SSTRING( prm3 ),
	DMM_SSTRING( prm4 ),
	DMM_SSTRING( prm5 ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbSstsrmstSelectAll()
 *    SSTSRMST レコード全件取得
 * ■引数
 *    [O]  Sstsrmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbSstsrmstSelectAll( Sstsrmst** arrayOut, int* numOut )
{
    Sstsrmst*   array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 84 "Sstsrmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		SSTCD,
		KNSGRP,
		KMKCD,
		SYRSBT,
		PRM1,
		PRM2,
		PRM3,
		PRM4,
		PRM5,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        SSTSRMST FOR READ ONLY;
*/

#line 102 "Sstsrmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 104 "Sstsrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 104 "Sstsrmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 104 "Sstsrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 104 "Sstsrmst.sqc"
  sqlastop(0L);
}

#line 104 "Sstsrmst.sqc"


    while( 1 ) {
        Sstsrmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:sstcd,
			:knsgrp,
			:kmkcd,
			:syrsbt,
			:prm1,
			:prm2,
			:prm3,
			:prm4,
			:prm5,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 122 "Sstsrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 122 "Sstsrmst.sqc"
  sqlaaloc(3,13,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[13];
#line 122 "Sstsrmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[0].sqldata = (void*)sstcd;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 4;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[3].sqldata = (void*)syrsbt;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 51;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[4].sqldata = (void*)prm1;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 51;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[5].sqldata = (void*)prm2;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 51;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[6].sqldata = (void*)prm3;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[7].sqldata = (void*)prm4;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 51;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[8].sqldata = (void*)prm5;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[9].sqldata = (void*)kaiymd;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[10].sqldata = (void*)haiymd;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[11].sqldata = (void*)hnktntid;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 27;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[12].sqldata = (void*)ksndh;
#line 122 "Sstsrmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 122 "Sstsrmst.sqc"
      sqlasetdata(3,0,13,sql_setdlist,0L,0L);
    }
#line 122 "Sstsrmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 122 "Sstsrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 122 "Sstsrmst.sqc"
  sqlastop(0L);
}

#line 122 "Sstsrmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Sstsrmst*)ZbmlRealloc( array,
                                    sizeof( Sstsrmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Sstsrmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, SstsrmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 137 "Sstsrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 137 "Sstsrmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 137 "Sstsrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 137 "Sstsrmst.sqc"
  sqlastop(0L);
}

#line 137 "Sstsrmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 145 "Sstsrmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbSstsrmstSelectKey()
 *    SSTSRMST レコードKey条件取得
 * ■引数
 *    [I]  Sstsrmst* pKey       取得するレコードのキー
 *    [O]  Sstsrmst** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbSstsrmstSelectKey( Sstsrmst* pKey, Sstsrmst** arrayOut, int* numOut )
{
    Sstsrmst*   array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, SstsrmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 171 "Sstsrmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		SSTCD,
		KNSGRP,
		KMKCD,
		SYRSBT,
		PRM1,
		PRM2,
		PRM3,
		PRM4,
		PRM5,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        SSTSRMST
    WHERE
		SSTCD = :sstcd AND
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		SYRSBT = :syrsbt AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 195 "Sstsrmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 197 "Sstsrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 197 "Sstsrmst.sqc"
  sqlaaloc(2,5,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 197 "Sstsrmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 197 "Sstsrmst.sqc"
      sql_setdlist[0].sqldata = (void*)sstcd;
#line 197 "Sstsrmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 197 "Sstsrmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 197 "Sstsrmst.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 197 "Sstsrmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 197 "Sstsrmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 197 "Sstsrmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 197 "Sstsrmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 197 "Sstsrmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 4;
#line 197 "Sstsrmst.sqc"
      sql_setdlist[3].sqldata = (void*)syrsbt;
#line 197 "Sstsrmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 197 "Sstsrmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 197 "Sstsrmst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 197 "Sstsrmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 197 "Sstsrmst.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 197 "Sstsrmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 197 "Sstsrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 197 "Sstsrmst.sqc"
  sqlastop(0L);
}

#line 197 "Sstsrmst.sqc"


    while( 1 ) {
        Sstsrmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:sstcd,
			:knsgrp,
			:kmkcd,
			:syrsbt,
			:prm1,
			:prm2,
			:prm3,
			:prm4,
			:prm5,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 215 "Sstsrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 215 "Sstsrmst.sqc"
  sqlaaloc(3,13,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[13];
#line 215 "Sstsrmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[0].sqldata = (void*)sstcd;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 4;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[3].sqldata = (void*)syrsbt;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 51;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[4].sqldata = (void*)prm1;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 51;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[5].sqldata = (void*)prm2;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 51;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[6].sqldata = (void*)prm3;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[7].sqldata = (void*)prm4;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 51;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[8].sqldata = (void*)prm5;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[9].sqldata = (void*)kaiymd;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[10].sqldata = (void*)haiymd;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[11].sqldata = (void*)hnktntid;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 27;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[12].sqldata = (void*)ksndh;
#line 215 "Sstsrmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 215 "Sstsrmst.sqc"
      sqlasetdata(3,0,13,sql_setdlist,0L,0L);
    }
#line 215 "Sstsrmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 215 "Sstsrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 215 "Sstsrmst.sqc"
  sqlastop(0L);
}

#line 215 "Sstsrmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Sstsrmst*)ZbmlRealloc( array,
                                    sizeof( Sstsrmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Sstsrmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, SstsrmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 230 "Sstsrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 230 "Sstsrmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 230 "Sstsrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 230 "Sstsrmst.sqc"
  sqlastop(0L);
}

#line 230 "Sstsrmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 238 "Sstsrmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbSstsrmstInsert()
 *    SSTSRMST レコードを挿入する
 * ■引数
 *    [I]  Sstsrmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbSstsrmstInsert( Sstsrmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, SstsrmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 261 "Sstsrmst.sqc"


    
/*
EXEC SQL INSERT INTO SSTSRMST
    (
		SSTCD,
		KNSGRP,
		KMKCD,
		SYRSBT,
		PRM1,
		PRM2,
		PRM3,
		PRM4,
		PRM5,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:sstcd,
		:knsgrp,
		:kmkcd,
		:syrsbt,
		:prm1,
		:prm2,
		:prm3,
		:prm4,
		:prm5,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 292 "Sstsrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 292 "Sstsrmst.sqc"
  sqlaaloc(2,13,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[13];
#line 292 "Sstsrmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[0].sqldata = (void*)sstcd;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 4;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[3].sqldata = (void*)syrsbt;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 51;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[4].sqldata = (void*)prm1;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 51;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[5].sqldata = (void*)prm2;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 51;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[6].sqldata = (void*)prm3;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[7].sqldata = (void*)prm4;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 51;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[8].sqldata = (void*)prm5;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[9].sqldata = (void*)kaiymd;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[10].sqldata = (void*)haiymd;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[11].sqldata = (void*)hnktntid;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 27;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[12].sqldata = (void*)ksndh;
#line 292 "Sstsrmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 292 "Sstsrmst.sqc"
      sqlasetdata(2,0,13,sql_setdlist,0L,0L);
    }
#line 292 "Sstsrmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 292 "Sstsrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 292 "Sstsrmst.sqc"
  sqlastop(0L);
}

#line 292 "Sstsrmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 297 "Sstsrmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbSstsrmstUpdate()
 *    SSTSRMST レコードを更新する
 * ■引数
 *    [I]  Sstsrmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbSstsrmstUpdate( Sstsrmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, SstsrmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 321 "Sstsrmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 322 "Sstsrmst.sqc"


    
/*
EXEC SQL UPDATE SSTSRMST
    SET (
		PRM1,
		PRM2,
		PRM3,
		PRM4,
		PRM5,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:prm1,
		:prm2,
		:prm3,
		:prm4,
		:prm5,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		SSTCD = :sstcd AND
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		SYRSBT = :syrsbt AND
		KAIYMD = :kaiymd;
*/

{
#line 348 "Sstsrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 348 "Sstsrmst.sqc"
  sqlaaloc(2,13,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[13];
#line 348 "Sstsrmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 51;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[0].sqldata = (void*)prm1;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 51;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[1].sqldata = (void*)prm2;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 51;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[2].sqldata = (void*)prm3;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 51;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[3].sqldata = (void*)prm4;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 51;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[4].sqldata = (void*)prm5;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[5].sqldata = (void*)haiymd;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 9;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[6].sqldata = (void*)hnktntid;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[7].sqldata = (void*)ksndh;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 8;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[8].sqldata = (void*)sstcd;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 17;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[9].sqldata = (void*)knsgrp;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 8;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[10].sqldata = (void*)kmkcd;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 4;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[11].sqldata = (void*)syrsbt;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[12].sqldata = (void*)kaiymd;
#line 348 "Sstsrmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 348 "Sstsrmst.sqc"
      sqlasetdata(2,0,13,sql_setdlist,0L,0L);
    }
#line 348 "Sstsrmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 348 "Sstsrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 348 "Sstsrmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 348 "Sstsrmst.sqc"
  sqlastop(0L);
}

#line 348 "Sstsrmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 353 "Sstsrmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 357 "Sstsrmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbSstsrmstDelete()
 *    SSTSRMST レコードを削除する
 * ■引数
 *    [I]  Sstsrmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbSstsrmstDelete( Sstsrmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, SstsrmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 381 "Sstsrmst.sqc"


    
/*
EXEC SQL DELETE FROM SSTSRMST
    WHERE
		SSTCD = :sstcd AND
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		SYRSBT = :syrsbt AND
		KAIYMD = :kaiymd;
*/

{
#line 389 "Sstsrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 389 "Sstsrmst.sqc"
  sqlaaloc(2,5,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 389 "Sstsrmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 389 "Sstsrmst.sqc"
      sql_setdlist[0].sqldata = (void*)sstcd;
#line 389 "Sstsrmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 389 "Sstsrmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 389 "Sstsrmst.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 389 "Sstsrmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 389 "Sstsrmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 389 "Sstsrmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 389 "Sstsrmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 389 "Sstsrmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 4;
#line 389 "Sstsrmst.sqc"
      sql_setdlist[3].sqldata = (void*)syrsbt;
#line 389 "Sstsrmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 389 "Sstsrmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 389 "Sstsrmst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 389 "Sstsrmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 389 "Sstsrmst.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 389 "Sstsrmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 389 "Sstsrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 389 "Sstsrmst.sqc"
  sqlastop(0L);
}

#line 389 "Sstsrmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 394 "Sstsrmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
