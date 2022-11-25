static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,99,65,84,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,51,54,90,75,75,65,70,32,0,0,0,0,0,0,0,0,
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


#line 1 "Kkafltmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Kkafltmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Kkafltmst.h"
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


#line 24 "Kkafltmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Kkafltmst.sqc"

	char    knsgrp[17];
	char    kmkcd[8];
	char    fltkka[25];
	char    minval[13];
	char    maxval[13];
	char    knskka1[13];
	char    knskka2[25];
	char    knskka2kbn[3];
	char    kkahskcd[4];
	char    hjkka[25];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 44 "Kkafltmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Kkafltmst

BmlDMMInfo	KkafltmstArray[] = {
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( fltkka ),
	DMM_SSTRING( minval ),
	DMM_SSTRING( maxval ),
	DMM_SSTRING( knskka1 ),
	DMM_SSTRING( knskka2 ),
	DMM_SSTRING( knskka2kbn ),
	DMM_SSTRING( kkahskcd ),
	DMM_SSTRING( hjkka ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKkafltmstSelectAll()
 *    KKAFLTMST レコード全件取得
 * ■引数
 *    [O]  Kkafltmst** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKkafltmstSelectAll( Kkafltmst** arrayOut, int* numOut )
{
    Kkafltmst*  array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 86 "Kkafltmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSGRP,
		KMKCD,
		FLTKKA,
		MINVAL,
		MAXVAL,
		KNSKKA1,
		KNSKKA2,
		KNSKKA2KBN,
		KKAHSKCD,
		HJKKA,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        KKAFLTMST FOR READ ONLY;
*/

#line 105 "Kkafltmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 107 "Kkafltmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 107 "Kkafltmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 107 "Kkafltmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 107 "Kkafltmst.sqc"
  sqlastop(0L);
}

#line 107 "Kkafltmst.sqc"


    while( 1 ) {
        Kkafltmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knsgrp,
			:kmkcd,
			:fltkka,
			:minval,
			:maxval,
			:knskka1,
			:knskka2,
			:knskka2kbn,
			:kkahskcd,
			:hjkka,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 126 "Kkafltmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 126 "Kkafltmst.sqc"
  sqlaaloc(3,14,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[14];
#line 126 "Kkafltmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 25;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[2].sqldata = (void*)fltkka;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 13;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[3].sqldata = (void*)minval;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 13;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[4].sqldata = (void*)maxval;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 13;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[5].sqldata = (void*)knskka1;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 25;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[6].sqldata = (void*)knskka2;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[7].sqldata = (void*)knskka2kbn;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[8].sqldata = (void*)kkahskcd;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 25;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[9].sqldata = (void*)hjkka;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[10].sqldata = (void*)kaiymd;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[11].sqldata = (void*)haiymd;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[12].sqldata = (void*)hnktntid;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 27;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[13].sqldata = (void*)ksndh;
#line 126 "Kkafltmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 126 "Kkafltmst.sqc"
      sqlasetdata(3,0,14,sql_setdlist,0L,0L);
    }
#line 126 "Kkafltmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 126 "Kkafltmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 126 "Kkafltmst.sqc"
  sqlastop(0L);
}

#line 126 "Kkafltmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kkafltmst*)ZbmlRealloc( array,
                                    sizeof( Kkafltmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kkafltmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KkafltmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 141 "Kkafltmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 141 "Kkafltmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 141 "Kkafltmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 141 "Kkafltmst.sqc"
  sqlastop(0L);
}

#line 141 "Kkafltmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 149 "Kkafltmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKkafltmstSelectKey()
 *    KKAFLTMST レコードKey条件取得
 * ■引数
 *    [I]  Kkafltmst* pKey      取得するレコードのキー
 *    [O]  Kkafltmst** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKkafltmstSelectKey( Kkafltmst* pKey, Kkafltmst** arrayOut, int* numOut )
{
    Kkafltmst*  array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KkafltmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 175 "Kkafltmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSGRP,
		KMKCD,
		FLTKKA,
		MINVAL,
		MAXVAL,
		KNSKKA1,
		KNSKKA2,
		KNSKKA2KBN,
		KKAHSKCD,
		HJKKA,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        KKAFLTMST
    WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		FLTKKA = :fltkka AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 199 "Kkafltmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 201 "Kkafltmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 201 "Kkafltmst.sqc"
  sqlaaloc(2,4,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 201 "Kkafltmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 201 "Kkafltmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 201 "Kkafltmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 201 "Kkafltmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 201 "Kkafltmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 201 "Kkafltmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 201 "Kkafltmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 25;
#line 201 "Kkafltmst.sqc"
      sql_setdlist[2].sqldata = (void*)fltkka;
#line 201 "Kkafltmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 201 "Kkafltmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 201 "Kkafltmst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 201 "Kkafltmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 201 "Kkafltmst.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 201 "Kkafltmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 201 "Kkafltmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 201 "Kkafltmst.sqc"
  sqlastop(0L);
}

#line 201 "Kkafltmst.sqc"


    while( 1 ) {
        Kkafltmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knsgrp,
			:kmkcd,
			:fltkka,
			:minval,
			:maxval,
			:knskka1,
			:knskka2,
			:knskka2kbn,
			:kkahskcd,
			:hjkka,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 220 "Kkafltmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 220 "Kkafltmst.sqc"
  sqlaaloc(3,14,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[14];
#line 220 "Kkafltmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 25;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[2].sqldata = (void*)fltkka;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 13;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[3].sqldata = (void*)minval;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 13;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[4].sqldata = (void*)maxval;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 13;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[5].sqldata = (void*)knskka1;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 25;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[6].sqldata = (void*)knskka2;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[7].sqldata = (void*)knskka2kbn;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[8].sqldata = (void*)kkahskcd;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 25;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[9].sqldata = (void*)hjkka;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[10].sqldata = (void*)kaiymd;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[11].sqldata = (void*)haiymd;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[12].sqldata = (void*)hnktntid;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 27;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[13].sqldata = (void*)ksndh;
#line 220 "Kkafltmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 220 "Kkafltmst.sqc"
      sqlasetdata(3,0,14,sql_setdlist,0L,0L);
    }
#line 220 "Kkafltmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 220 "Kkafltmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 220 "Kkafltmst.sqc"
  sqlastop(0L);
}

#line 220 "Kkafltmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kkafltmst*)ZbmlRealloc( array,
                                    sizeof( Kkafltmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kkafltmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KkafltmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 235 "Kkafltmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 235 "Kkafltmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 235 "Kkafltmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 235 "Kkafltmst.sqc"
  sqlastop(0L);
}

#line 235 "Kkafltmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 243 "Kkafltmst.sqc"

    return sqlca.sqlcode;
}
long ZdbKkafltmstSelectGRPKMKKey( Kkafltmst* pKey, Kkafltmst** arrayOut, int* numOut )
{
    Kkafltmst*  array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KkafltmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 257 "Kkafltmst.sqc"


    
/*
EXEC SQL DECLARE c3 CURSOR FOR
    SELECT
		KNSGRP,
		KMKCD,
		FLTKKA,
		MINVAL,
		MAXVAL,
		KNSKKA1,
		KNSKKA2,
		KNSKKA2KBN,
		KKAHSKCD,
		HJKKA,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        KKAFLTMST
    WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KAIYMD <= CURRENT DATE AND
		HAIYMD >= CURRENT DATE FOR READ ONLY;
*/

#line 281 "Kkafltmst.sqc"


    
/*
EXEC SQL OPEN c3;
*/

{
#line 283 "Kkafltmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 283 "Kkafltmst.sqc"
  sqlaaloc(2,2,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 283 "Kkafltmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 283 "Kkafltmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 283 "Kkafltmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 283 "Kkafltmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 283 "Kkafltmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 283 "Kkafltmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 283 "Kkafltmst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 283 "Kkafltmst.sqc"
  sqlacall((unsigned short)26,3,2,0,0L);
#line 283 "Kkafltmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 283 "Kkafltmst.sqc"
  sqlastop(0L);
}

#line 283 "Kkafltmst.sqc"


    while( 1 ) {
        Kkafltmst* rec;

        
/*
EXEC SQL FETCH c3 INTO
			:knsgrp,
			:kmkcd,
			:fltkka,
			:minval,
			:maxval,
			:knskka1,
			:knskka2,
			:knskka2kbn,
			:kkahskcd,
			:hjkka,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 302 "Kkafltmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 302 "Kkafltmst.sqc"
  sqlaaloc(3,14,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[14];
#line 302 "Kkafltmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 25;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[2].sqldata = (void*)fltkka;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 13;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[3].sqldata = (void*)minval;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 13;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[4].sqldata = (void*)maxval;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 13;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[5].sqldata = (void*)knskka1;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 25;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[6].sqldata = (void*)knskka2;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[7].sqldata = (void*)knskka2kbn;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[8].sqldata = (void*)kkahskcd;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 25;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[9].sqldata = (void*)hjkka;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[10].sqldata = (void*)kaiymd;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[11].sqldata = (void*)haiymd;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[12].sqldata = (void*)hnktntid;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 27;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[13].sqldata = (void*)ksndh;
#line 302 "Kkafltmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 302 "Kkafltmst.sqc"
      sqlasetdata(3,0,14,sql_setdlist,0L,0L);
    }
#line 302 "Kkafltmst.sqc"
  sqlacall((unsigned short)25,3,0,3,0L);
#line 302 "Kkafltmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 302 "Kkafltmst.sqc"
  sqlastop(0L);
}

#line 302 "Kkafltmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kkafltmst*)ZbmlRealloc( array,
                                    sizeof( Kkafltmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kkafltmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KkafltmstArray );
    }

    
/*
EXEC SQL CLOSE c3;
*/

{
#line 317 "Kkafltmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 317 "Kkafltmst.sqc"
  sqlacall((unsigned short)20,3,0,0,0L);
#line 317 "Kkafltmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 317 "Kkafltmst.sqc"
  sqlastop(0L);
}

#line 317 "Kkafltmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 325 "Kkafltmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKkafltmstInsert()
 *    KKAFLTMST レコードを挿入する
 * ■引数
 *    [I]  Kkafltmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKkafltmstInsert( Kkafltmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KkafltmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 348 "Kkafltmst.sqc"


    
/*
EXEC SQL INSERT INTO KKAFLTMST
    (
		KNSGRP,
		KMKCD,
		FLTKKA,
		MINVAL,
		MAXVAL,
		KNSKKA1,
		KNSKKA2,
		KNSKKA2KBN,
		KKAHSKCD,
		HJKKA,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:knsgrp,
		:kmkcd,
		:fltkka,
		:minval,
		:maxval,
		:knskka1,
		:knskka2,
		:knskka2kbn,
		:kkahskcd,
		:hjkka,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 381 "Kkafltmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 381 "Kkafltmst.sqc"
  sqlaaloc(2,14,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[14];
#line 381 "Kkafltmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 25;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[2].sqldata = (void*)fltkka;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 13;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[3].sqldata = (void*)minval;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 13;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[4].sqldata = (void*)maxval;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 13;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[5].sqldata = (void*)knskka1;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 25;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[6].sqldata = (void*)knskka2;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[7].sqldata = (void*)knskka2kbn;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[8].sqldata = (void*)kkahskcd;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 25;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[9].sqldata = (void*)hjkka;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[10].sqldata = (void*)kaiymd;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[11].sqldata = (void*)haiymd;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[12].sqldata = (void*)hnktntid;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 27;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[13].sqldata = (void*)ksndh;
#line 381 "Kkafltmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 381 "Kkafltmst.sqc"
      sqlasetdata(2,0,14,sql_setdlist,0L,0L);
    }
#line 381 "Kkafltmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 381 "Kkafltmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 381 "Kkafltmst.sqc"
  sqlastop(0L);
}

#line 381 "Kkafltmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 386 "Kkafltmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKkafltmstUpdate()
 *    KKAFLTMST レコードを更新する
 * ■引数
 *    [I]  Kkafltmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKkafltmstUpdate( Kkafltmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KkafltmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 410 "Kkafltmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 411 "Kkafltmst.sqc"


    
/*
EXEC SQL UPDATE KKAFLTMST
    SET (
		MINVAL,
		MAXVAL,
		KNSKKA1,
		KNSKKA2,
		KNSKKA2KBN,
		KKAHSKCD,
		HJKKA,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:minval,
		:maxval,
		:knskka1,
		:knskka2,
		:knskka2kbn,
		:kkahskcd,
		:hjkka,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		FLTKKA = :fltkka AND
		KAIYMD = :kaiymd;
*/

{
#line 440 "Kkafltmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 440 "Kkafltmst.sqc"
  sqlaaloc(2,14,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[14];
#line 440 "Kkafltmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 13;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[0].sqldata = (void*)minval;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 13;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[1].sqldata = (void*)maxval;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 13;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[2].sqldata = (void*)knskka1;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 25;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[3].sqldata = (void*)knskka2;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 3;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[4].sqldata = (void*)knskka2kbn;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 4;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[5].sqldata = (void*)kkahskcd;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 25;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[6].sqldata = (void*)hjkka;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[7].sqldata = (void*)haiymd;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[8].sqldata = (void*)hnktntid;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 17;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[10].sqldata = (void*)knsgrp;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 8;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[11].sqldata = (void*)kmkcd;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 25;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[12].sqldata = (void*)fltkka;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[13].sqldata = (void*)kaiymd;
#line 440 "Kkafltmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 440 "Kkafltmst.sqc"
      sqlasetdata(2,0,14,sql_setdlist,0L,0L);
    }
#line 440 "Kkafltmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 440 "Kkafltmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 440 "Kkafltmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 440 "Kkafltmst.sqc"
  sqlastop(0L);
}

#line 440 "Kkafltmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 445 "Kkafltmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 449 "Kkafltmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKkafltmstDelete()
 *    KKAFLTMST レコードを削除する
 * ■引数
 *    [I]  Kkafltmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKkafltmstDelete( Kkafltmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KkafltmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 473 "Kkafltmst.sqc"


    
/*
EXEC SQL DELETE FROM KKAFLTMST
    WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		FLTKKA = :fltkka AND
		KAIYMD = :kaiymd;
*/

{
#line 480 "Kkafltmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 480 "Kkafltmst.sqc"
  sqlaaloc(2,4,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 480 "Kkafltmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 480 "Kkafltmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 480 "Kkafltmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 480 "Kkafltmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 480 "Kkafltmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 480 "Kkafltmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 480 "Kkafltmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 25;
#line 480 "Kkafltmst.sqc"
      sql_setdlist[2].sqldata = (void*)fltkka;
#line 480 "Kkafltmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 480 "Kkafltmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 480 "Kkafltmst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 480 "Kkafltmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 480 "Kkafltmst.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 480 "Kkafltmst.sqc"
  sqlacall((unsigned short)24,6,2,0,0L);
#line 480 "Kkafltmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 480 "Kkafltmst.sqc"
  sqlastop(0L);
}

#line 480 "Kkafltmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 485 "Kkafltmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
