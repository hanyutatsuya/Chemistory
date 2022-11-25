static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,101,66,82,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,50,49,90,70,75,80,84,32,0,0,0,0,0,0,0,0,
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


#line 1 "Fkptchkmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Fkptchkmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Fkptchkmst.h"
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


#line 24 "Fkptchkmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Fkptchkmst.sqc"

	char    knsgrp[17];
	char    oyakmkcd[8];
	char    chk1;
	char    chk2;
	char    chk3;
	char    chk4;
	char    chk5;
	char    chk6;
	char    chk7;
	char    chk8;
	char    chk9;
	char    chk10;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 46 "Fkptchkmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Fkptchkmst

BmlDMMInfo	FkptchkmstArray[] = {
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( oyakmkcd ),
	DMM_SCHAR( chk1 ),
	DMM_SCHAR( chk2 ),
	DMM_SCHAR( chk3 ),
	DMM_SCHAR( chk4 ),
	DMM_SCHAR( chk5 ),
	DMM_SCHAR( chk6 ),
	DMM_SCHAR( chk7 ),
	DMM_SCHAR( chk8 ),
	DMM_SCHAR( chk9 ),
	DMM_SCHAR( chk10 ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbFkptchkmstSelectAll()
 *    FKPTCHKMST レコード全件取得
 * ■引数
 *    [O]  Fkptchkmst** arrayOu 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbFkptchkmstSelectAll( Fkptchkmst** arrayOut, int* numOut )
{
    Fkptchkmst* array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 90 "Fkptchkmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSGRP,
		OYAKMKCD,
		CHK1,
		CHK2,
		CHK3,
		CHK4,
		CHK5,
		CHK6,
		CHK7,
		CHK8,
		CHK9,
		CHK10,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        FKPTCHKMST FOR READ ONLY;
*/

#line 111 "Fkptchkmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 113 "Fkptchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 113 "Fkptchkmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 113 "Fkptchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 113 "Fkptchkmst.sqc"
  sqlastop(0L);
}

#line 113 "Fkptchkmst.sqc"


    while( 1 ) {
        Fkptchkmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knsgrp,
			:oyakmkcd,
			:chk1,
			:chk2,
			:chk3,
			:chk4,
			:chk5,
			:chk6,
			:chk7,
			:chk8,
			:chk9,
			:chk10,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 134 "Fkptchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 134 "Fkptchkmst.sqc"
  sqlaaloc(3,16,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[16];
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)oyakmkcd;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)&chk1;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[3].sqldata = (void*)&chk2;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[4].sqldata = (void*)&chk3;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[5].sqldata = (void*)&chk4;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[6].sqldata = (void*)&chk5;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[7].sqldata = (void*)&chk6;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[8].sqldata = (void*)&chk7;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[9].sqldata = (void*)&chk8;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[10].sqldata = (void*)&chk9;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[11].sqldata = (void*)&chk10;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[12].sqldata = (void*)kaiymd;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[13].sqldata = (void*)haiymd;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 9;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[14].sqldata = (void*)hnktntid;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[15].sqldata = (void*)ksndh;
#line 134 "Fkptchkmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 134 "Fkptchkmst.sqc"
      sqlasetdata(3,0,16,sql_setdlist,0L,0L);
    }
#line 134 "Fkptchkmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 134 "Fkptchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 134 "Fkptchkmst.sqc"
  sqlastop(0L);
}

#line 134 "Fkptchkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Fkptchkmst*)ZbmlRealloc( array,
                                    sizeof( Fkptchkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Fkptchkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, FkptchkmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 149 "Fkptchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 149 "Fkptchkmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 149 "Fkptchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 149 "Fkptchkmst.sqc"
  sqlastop(0L);
}

#line 149 "Fkptchkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 157 "Fkptchkmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbFkptchkmstSelectKey()
 *    FKPTCHKMST レコードKey条件取得
 * ■引数
 *    [I]  Fkptchkmst* pKey     取得するレコードのキー
 *    [O]  Fkptchkmst** arrayOu 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbFkptchkmstSelectKey( Fkptchkmst* pKey, Fkptchkmst** arrayOut, int* numOut )
{
    Fkptchkmst* array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, FkptchkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 183 "Fkptchkmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSGRP,
		OYAKMKCD,
		CHK1,
		CHK2,
		CHK3,
		CHK4,
		CHK5,
		CHK6,
		CHK7,
		CHK8,
		CHK9,
		CHK10,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        FKPTCHKMST
    WHERE
		KNSGRP = :knsgrp AND
		OYAKMKCD = :oyakmkcd AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 208 "Fkptchkmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 210 "Fkptchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 210 "Fkptchkmst.sqc"
  sqlaaloc(2,3,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 210 "Fkptchkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 210 "Fkptchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 210 "Fkptchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 210 "Fkptchkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 210 "Fkptchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)oyakmkcd;
#line 210 "Fkptchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 210 "Fkptchkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 210 "Fkptchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 210 "Fkptchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 210 "Fkptchkmst.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 210 "Fkptchkmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 210 "Fkptchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 210 "Fkptchkmst.sqc"
  sqlastop(0L);
}

#line 210 "Fkptchkmst.sqc"


    while( 1 ) {
        Fkptchkmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knsgrp,
			:oyakmkcd,
			:chk1,
			:chk2,
			:chk3,
			:chk4,
			:chk5,
			:chk6,
			:chk7,
			:chk8,
			:chk9,
			:chk10,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 231 "Fkptchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 231 "Fkptchkmst.sqc"
  sqlaaloc(3,16,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[16];
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)oyakmkcd;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)&chk1;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[3].sqldata = (void*)&chk2;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[4].sqldata = (void*)&chk3;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[5].sqldata = (void*)&chk4;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[6].sqldata = (void*)&chk5;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[7].sqldata = (void*)&chk6;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[8].sqldata = (void*)&chk7;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[9].sqldata = (void*)&chk8;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[10].sqldata = (void*)&chk9;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[11].sqldata = (void*)&chk10;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[12].sqldata = (void*)kaiymd;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[13].sqldata = (void*)haiymd;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 9;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[14].sqldata = (void*)hnktntid;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[15].sqldata = (void*)ksndh;
#line 231 "Fkptchkmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 231 "Fkptchkmst.sqc"
      sqlasetdata(3,0,16,sql_setdlist,0L,0L);
    }
#line 231 "Fkptchkmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 231 "Fkptchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 231 "Fkptchkmst.sqc"
  sqlastop(0L);
}

#line 231 "Fkptchkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Fkptchkmst*)ZbmlRealloc( array,
                                    sizeof( Fkptchkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Fkptchkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, FkptchkmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 246 "Fkptchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 246 "Fkptchkmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 246 "Fkptchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 246 "Fkptchkmst.sqc"
  sqlastop(0L);
}

#line 246 "Fkptchkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 254 "Fkptchkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbFkptchkmstInsert()
 *    FKPTCHKMST レコードを挿入する
 * ■引数
 *    [I]  Fkptchkmst* rec      挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbFkptchkmstInsert( Fkptchkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, FkptchkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 277 "Fkptchkmst.sqc"


    
/*
EXEC SQL INSERT INTO FKPTCHKMST
    (
		KNSGRP,
		OYAKMKCD,
		CHK1,
		CHK2,
		CHK3,
		CHK4,
		CHK5,
		CHK6,
		CHK7,
		CHK8,
		CHK9,
		CHK10,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:knsgrp,
		:oyakmkcd,
		:chk1,
		:chk2,
		:chk3,
		:chk4,
		:chk5,
		:chk6,
		:chk7,
		:chk8,
		:chk9,
		:chk10,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 314 "Fkptchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 314 "Fkptchkmst.sqc"
  sqlaaloc(2,16,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[16];
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)oyakmkcd;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)&chk1;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[3].sqldata = (void*)&chk2;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[4].sqldata = (void*)&chk3;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[5].sqldata = (void*)&chk4;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[6].sqldata = (void*)&chk5;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[7].sqldata = (void*)&chk6;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[8].sqldata = (void*)&chk7;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[9].sqldata = (void*)&chk8;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[10].sqldata = (void*)&chk9;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[11].sqldata = (void*)&chk10;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[12].sqldata = (void*)kaiymd;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[13].sqldata = (void*)haiymd;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 9;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[14].sqldata = (void*)hnktntid;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[15].sqldata = (void*)ksndh;
#line 314 "Fkptchkmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 314 "Fkptchkmst.sqc"
      sqlasetdata(2,0,16,sql_setdlist,0L,0L);
    }
#line 314 "Fkptchkmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 314 "Fkptchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 314 "Fkptchkmst.sqc"
  sqlastop(0L);
}

#line 314 "Fkptchkmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 319 "Fkptchkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbFkptchkmstUpdate()
 *    FKPTCHKMST レコードを更新する
 * ■引数
 *    [I]  Fkptchkmst* rec      更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbFkptchkmstUpdate( Fkptchkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, FkptchkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 343 "Fkptchkmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 344 "Fkptchkmst.sqc"


    
/*
EXEC SQL UPDATE FKPTCHKMST
    SET (
		CHK1,
		CHK2,
		CHK3,
		CHK4,
		CHK5,
		CHK6,
		CHK7,
		CHK8,
		CHK9,
		CHK10,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:chk1,
		:chk2,
		:chk3,
		:chk4,
		:chk5,
		:chk6,
		:chk7,
		:chk8,
		:chk9,
		:chk10,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		KNSGRP = :knsgrp AND
		OYAKMKCD = :oyakmkcd AND
		KAIYMD = :kaiymd;
*/

{
#line 378 "Fkptchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 378 "Fkptchkmst.sqc"
  sqlaaloc(2,16,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[16];
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)&chk1;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)&chk2;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)&chk3;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[3].sqldata = (void*)&chk4;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[4].sqldata = (void*)&chk5;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[5].sqldata = (void*)&chk6;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[6].sqldata = (void*)&chk7;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[7].sqldata = (void*)&chk8;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[8].sqldata = (void*)&chk9;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[9].sqldata = (void*)&chk10;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[10].sqldata = (void*)haiymd;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[11].sqldata = (void*)hnktntid;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 27;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[12].sqldata = (void*)ksndh;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 17;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[13].sqldata = (void*)knsgrp;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 8;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[14].sqldata = (void*)oyakmkcd;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 11;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[15].sqldata = (void*)kaiymd;
#line 378 "Fkptchkmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 378 "Fkptchkmst.sqc"
      sqlasetdata(2,0,16,sql_setdlist,0L,0L);
    }
#line 378 "Fkptchkmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 378 "Fkptchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 378 "Fkptchkmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 378 "Fkptchkmst.sqc"
  sqlastop(0L);
}

#line 378 "Fkptchkmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 383 "Fkptchkmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 387 "Fkptchkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbFkptchkmstDelete()
 *    FKPTCHKMST レコードを削除する
 * ■引数
 *    [I]  Fkptchkmst* rec      削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbFkptchkmstDelete( Fkptchkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, FkptchkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 411 "Fkptchkmst.sqc"


    
/*
EXEC SQL DELETE FROM FKPTCHKMST
    WHERE
		KNSGRP = :knsgrp AND
		OYAKMKCD = :oyakmkcd AND
		KAIYMD = :kaiymd;
*/

{
#line 417 "Fkptchkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 417 "Fkptchkmst.sqc"
  sqlaaloc(2,3,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 417 "Fkptchkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 417 "Fkptchkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 417 "Fkptchkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 417 "Fkptchkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 417 "Fkptchkmst.sqc"
      sql_setdlist[1].sqldata = (void*)oyakmkcd;
#line 417 "Fkptchkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 417 "Fkptchkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 417 "Fkptchkmst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 417 "Fkptchkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 417 "Fkptchkmst.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 417 "Fkptchkmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 417 "Fkptchkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 417 "Fkptchkmst.sqc"
  sqlastop(0L);
}

#line 417 "Fkptchkmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 422 "Fkptchkmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
