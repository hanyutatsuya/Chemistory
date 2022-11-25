static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,72,66,83,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,50,57,90,75,69,75,75,32,0,0,0,0,0,0,0,0,
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


#line 1 "Kekkafree.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Kekkafree.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Kekkafree.h"
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


#line 24 "Kekkafree.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Kekkafree.sqc"

	char    knskisymd[11];
	char    sriymd[11];
	char    kntno[14];
	char    kntketflg;
	char    knsgrp[17];
	char    kmkcd[8];
	short   knssu;
	short   knssueda;
	char    frsb;
	char    freetext[16385];
	char    ssssflg;
	char    ssknsflg;
	char    dtnrtts[9];
	char    dtnrdh[27];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 45 "Kekkafree.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Kekkafree

BmlDMMInfo	KekkafreeArray[] = {
	DMM_SDATE( knskisymd ),
	DMM_SDATE( sriymd ),
	DMM_SSTRING( kntno ),
	DMM_SCHAR( kntketflg ),
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSHORT( knssu ),
	DMM_SSHORT( knssueda ),
	DMM_SCHAR( frsb ),
	DMM_SSTRING( freetext ),
	DMM_SCHAR( ssssflg ),
	DMM_SCHAR( ssknsflg ),
	DMM_SSTRING( dtnrtts ),
	DMM_STIMESTAMP( dtnrdh ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKekkafreeSelectAll()
 *    KEKKAFREE レコード全件取得
 * ■引数
 *    [O]  Kekkafree** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKekkafreeSelectAll( Kekkafree** arrayOut, int* numOut )
{
    Kekkafree*  array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 88 "Kekkafree.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSKISYMD,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		KNSGRP,
		KMKCD,
		KNSSU,
		KNSSUEDA,
		FRSB,
		FREETEXT,
		SSSSFLG,
		SSKNSFLG,
		DTNRTTS,
		DTNRDH,
		KSNDH
    FROM
        KEKKAFREE FOR READ ONLY;
*/

#line 108 "Kekkafree.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 110 "Kekkafree.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 110 "Kekkafree.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 110 "Kekkafree.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 110 "Kekkafree.sqc"
  sqlastop(0L);
}

#line 110 "Kekkafree.sqc"


    while( 1 ) {
        Kekkafree* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knskisymd,
			:sriymd,
			:kntno,
			:kntketflg,
			:knsgrp,
			:kmkcd,
			:knssu,
			:knssueda,
			:frsb,
			:freetext,
			:ssssflg,
			:ssknsflg,
			:dtnrtts,
			:dtnrdh,
			:ksndh;
*/

{
#line 130 "Kekkafree.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 130 "Kekkafree.sqc"
  sqlaaloc(3,15,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[15];
#line 130 "Kekkafree.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 130 "Kekkafree.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 130 "Kekkafree.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 130 "Kekkafree.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 130 "Kekkafree.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 130 "Kekkafree.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 130 "Kekkafree.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 130 "Kekkafree.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 130 "Kekkafree.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 130 "Kekkafree.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 130 "Kekkafree.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 130 "Kekkafree.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 130 "Kekkafree.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 130 "Kekkafree.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 130 "Kekkafree.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 130 "Kekkafree.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 130 "Kekkafree.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 130 "Kekkafree.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 130 "Kekkafree.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 130 "Kekkafree.sqc"
      sql_setdlist[6].sqldata = (void*)&knssu;
#line 130 "Kekkafree.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 130 "Kekkafree.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 130 "Kekkafree.sqc"
      sql_setdlist[7].sqldata = (void*)&knssueda;
#line 130 "Kekkafree.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 130 "Kekkafree.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 130 "Kekkafree.sqc"
      sql_setdlist[8].sqldata = (void*)&frsb;
#line 130 "Kekkafree.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 130 "Kekkafree.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 16385;
#line 130 "Kekkafree.sqc"
      sql_setdlist[9].sqldata = (void*)freetext;
#line 130 "Kekkafree.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 130 "Kekkafree.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 130 "Kekkafree.sqc"
      sql_setdlist[10].sqldata = (void*)&ssssflg;
#line 130 "Kekkafree.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 130 "Kekkafree.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 130 "Kekkafree.sqc"
      sql_setdlist[11].sqldata = (void*)&ssknsflg;
#line 130 "Kekkafree.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 130 "Kekkafree.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 130 "Kekkafree.sqc"
      sql_setdlist[12].sqldata = (void*)dtnrtts;
#line 130 "Kekkafree.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 130 "Kekkafree.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 27;
#line 130 "Kekkafree.sqc"
      sql_setdlist[13].sqldata = (void*)dtnrdh;
#line 130 "Kekkafree.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 130 "Kekkafree.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 27;
#line 130 "Kekkafree.sqc"
      sql_setdlist[14].sqldata = (void*)ksndh;
#line 130 "Kekkafree.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 130 "Kekkafree.sqc"
      sqlasetdata(3,0,15,sql_setdlist,0L,0L);
    }
#line 130 "Kekkafree.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 130 "Kekkafree.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 130 "Kekkafree.sqc"
  sqlastop(0L);
}

#line 130 "Kekkafree.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kekkafree*)ZbmlRealloc( array,
                                    sizeof( Kekkafree ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kekkafree ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KekkafreeArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 145 "Kekkafree.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 145 "Kekkafree.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 145 "Kekkafree.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 145 "Kekkafree.sqc"
  sqlastop(0L);
}

#line 145 "Kekkafree.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 153 "Kekkafree.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKekkafreeSelectKey()
 *    KEKKAFREE レコードKey条件取得
 * ■引数
 *    [I]  Kekkafree* pKey      取得するレコードのキー
 *    [O]  Kekkafree** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKekkafreeSelectKey( Kekkafree* pKey, Kekkafree** arrayOut, int* numOut )
{
    Kekkafree*  array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KekkafreeArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 179 "Kekkafree.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSKISYMD,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		KNSGRP,
		KMKCD,
		KNSSU,
		KNSSUEDA,
		FRSB,
		FREETEXT,
		SSSSFLG,
		SSKNSFLG,
		DTNRTTS,
		DTNRDH,
		KSNDH
    FROM
        KEKKAFREE
    WHERE
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd AND
		KNSSU = :knssu AND
		KNSSUEDA = :knssueda AND
		FRSB = :frsb FOR READ ONLY;
*/

#line 208 "Kekkafree.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 210 "Kekkafree.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 210 "Kekkafree.sqc"
  sqlaaloc(2,8,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 210 "Kekkafree.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 210 "Kekkafree.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 210 "Kekkafree.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 210 "Kekkafree.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 210 "Kekkafree.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 210 "Kekkafree.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 210 "Kekkafree.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 210 "Kekkafree.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 210 "Kekkafree.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 210 "Kekkafree.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 210 "Kekkafree.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 210 "Kekkafree.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 210 "Kekkafree.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 210 "Kekkafree.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 210 "Kekkafree.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 210 "Kekkafree.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 210 "Kekkafree.sqc"
      sql_setdlist[5].sqldata = (void*)&knssu;
#line 210 "Kekkafree.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 210 "Kekkafree.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 210 "Kekkafree.sqc"
      sql_setdlist[6].sqldata = (void*)&knssueda;
#line 210 "Kekkafree.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 210 "Kekkafree.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 210 "Kekkafree.sqc"
      sql_setdlist[7].sqldata = (void*)&frsb;
#line 210 "Kekkafree.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 210 "Kekkafree.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 210 "Kekkafree.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 210 "Kekkafree.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 210 "Kekkafree.sqc"
  sqlastop(0L);
}

#line 210 "Kekkafree.sqc"


    while( 1 ) {
        Kekkafree* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knskisymd,
			:sriymd,
			:kntno,
			:kntketflg,
			:knsgrp,
			:kmkcd,
			:knssu,
			:knssueda,
			:frsb,
			:freetext,
			:ssssflg,
			:ssknsflg,
			:dtnrtts,
			:dtnrdh,
			:ksndh;
*/

{
#line 230 "Kekkafree.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 230 "Kekkafree.sqc"
  sqlaaloc(3,15,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[15];
#line 230 "Kekkafree.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 230 "Kekkafree.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 230 "Kekkafree.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 230 "Kekkafree.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 230 "Kekkafree.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 230 "Kekkafree.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 230 "Kekkafree.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 230 "Kekkafree.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 230 "Kekkafree.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 230 "Kekkafree.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 230 "Kekkafree.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 230 "Kekkafree.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 230 "Kekkafree.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 230 "Kekkafree.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 230 "Kekkafree.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 230 "Kekkafree.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 230 "Kekkafree.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 230 "Kekkafree.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 230 "Kekkafree.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 230 "Kekkafree.sqc"
      sql_setdlist[6].sqldata = (void*)&knssu;
#line 230 "Kekkafree.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 230 "Kekkafree.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 230 "Kekkafree.sqc"
      sql_setdlist[7].sqldata = (void*)&knssueda;
#line 230 "Kekkafree.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 230 "Kekkafree.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 230 "Kekkafree.sqc"
      sql_setdlist[8].sqldata = (void*)&frsb;
#line 230 "Kekkafree.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 230 "Kekkafree.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 16385;
#line 230 "Kekkafree.sqc"
      sql_setdlist[9].sqldata = (void*)freetext;
#line 230 "Kekkafree.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 230 "Kekkafree.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 230 "Kekkafree.sqc"
      sql_setdlist[10].sqldata = (void*)&ssssflg;
#line 230 "Kekkafree.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 230 "Kekkafree.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 230 "Kekkafree.sqc"
      sql_setdlist[11].sqldata = (void*)&ssknsflg;
#line 230 "Kekkafree.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 230 "Kekkafree.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 230 "Kekkafree.sqc"
      sql_setdlist[12].sqldata = (void*)dtnrtts;
#line 230 "Kekkafree.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 230 "Kekkafree.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 27;
#line 230 "Kekkafree.sqc"
      sql_setdlist[13].sqldata = (void*)dtnrdh;
#line 230 "Kekkafree.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 230 "Kekkafree.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 27;
#line 230 "Kekkafree.sqc"
      sql_setdlist[14].sqldata = (void*)ksndh;
#line 230 "Kekkafree.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 230 "Kekkafree.sqc"
      sqlasetdata(3,0,15,sql_setdlist,0L,0L);
    }
#line 230 "Kekkafree.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 230 "Kekkafree.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 230 "Kekkafree.sqc"
  sqlastop(0L);
}

#line 230 "Kekkafree.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kekkafree*)ZbmlRealloc( array,
                                    sizeof( Kekkafree ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kekkafree ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KekkafreeArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 245 "Kekkafree.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 245 "Kekkafree.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 245 "Kekkafree.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 245 "Kekkafree.sqc"
  sqlastop(0L);
}

#line 245 "Kekkafree.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 253 "Kekkafree.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKekkafreeInsert()
 *    KEKKAFREE レコードを挿入する
 * ■引数
 *    [I]  Kekkafree* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKekkafreeInsert( Kekkafree* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KekkafreeArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 276 "Kekkafree.sqc"


    
/*
EXEC SQL INSERT INTO KEKKAFREE
    (
		KNSKISYMD,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		KNSGRP,
		KMKCD,
		KNSSU,
		KNSSUEDA,
		FRSB,
		FREETEXT,
		SSSSFLG,
		SSKNSFLG,
		DTNRTTS,
		DTNRDH,
		KSNDH
    ) VALUES (
		:knskisymd,
		:sriymd,
		:kntno,
		:kntketflg,
		:knsgrp,
		:kmkcd,
		:knssu,
		:knssueda,
		:frsb,
		:freetext,
		:ssssflg,
		:ssknsflg,
		:dtnrtts,
		:dtnrdh,
		:ksndh
    );
*/

{
#line 311 "Kekkafree.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 311 "Kekkafree.sqc"
  sqlaaloc(2,15,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[15];
#line 311 "Kekkafree.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 311 "Kekkafree.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 311 "Kekkafree.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 311 "Kekkafree.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 311 "Kekkafree.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 311 "Kekkafree.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 311 "Kekkafree.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 311 "Kekkafree.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 311 "Kekkafree.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 311 "Kekkafree.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 311 "Kekkafree.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 311 "Kekkafree.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 311 "Kekkafree.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 311 "Kekkafree.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 311 "Kekkafree.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 311 "Kekkafree.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 311 "Kekkafree.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 311 "Kekkafree.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 311 "Kekkafree.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 311 "Kekkafree.sqc"
      sql_setdlist[6].sqldata = (void*)&knssu;
#line 311 "Kekkafree.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 311 "Kekkafree.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 311 "Kekkafree.sqc"
      sql_setdlist[7].sqldata = (void*)&knssueda;
#line 311 "Kekkafree.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 311 "Kekkafree.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 311 "Kekkafree.sqc"
      sql_setdlist[8].sqldata = (void*)&frsb;
#line 311 "Kekkafree.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 311 "Kekkafree.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 16385;
#line 311 "Kekkafree.sqc"
      sql_setdlist[9].sqldata = (void*)freetext;
#line 311 "Kekkafree.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 311 "Kekkafree.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 311 "Kekkafree.sqc"
      sql_setdlist[10].sqldata = (void*)&ssssflg;
#line 311 "Kekkafree.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 311 "Kekkafree.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 311 "Kekkafree.sqc"
      sql_setdlist[11].sqldata = (void*)&ssknsflg;
#line 311 "Kekkafree.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 311 "Kekkafree.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 311 "Kekkafree.sqc"
      sql_setdlist[12].sqldata = (void*)dtnrtts;
#line 311 "Kekkafree.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 311 "Kekkafree.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 27;
#line 311 "Kekkafree.sqc"
      sql_setdlist[13].sqldata = (void*)dtnrdh;
#line 311 "Kekkafree.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 311 "Kekkafree.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 27;
#line 311 "Kekkafree.sqc"
      sql_setdlist[14].sqldata = (void*)ksndh;
#line 311 "Kekkafree.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 311 "Kekkafree.sqc"
      sqlasetdata(2,0,15,sql_setdlist,0L,0L);
    }
#line 311 "Kekkafree.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 311 "Kekkafree.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 311 "Kekkafree.sqc"
  sqlastop(0L);
}

#line 311 "Kekkafree.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 316 "Kekkafree.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKekkafreeUpdate()
 *    KEKKAFREE レコードを更新する
 * ■引数
 *    [I]  Kekkafree* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKekkafreeUpdate( Kekkafree* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KekkafreeArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 340 "Kekkafree.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 341 "Kekkafree.sqc"


    
/*
EXEC SQL UPDATE KEKKAFREE
    SET (
		KNTKETFLG,
		FREETEXT,
		SSSSFLG,
		SSKNSFLG,
		DTNRTTS,
		DTNRDH,
		KSNDH
    ) = (
		:kntketflg,
		:freetext,
		:ssssflg,
		:ssknsflg,
		:dtnrtts,
		:dtnrdh,
		:ksndh
    ) WHERE
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd AND
		KNSSU = :knssu AND
		KNSSUEDA = :knssueda AND
		FRSB = :frsb;
*/

{
#line 368 "Kekkafree.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 368 "Kekkafree.sqc"
  sqlaaloc(2,15,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[15];
#line 368 "Kekkafree.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 368 "Kekkafree.sqc"
      sql_setdlist[0].sqldata = (void*)&kntketflg;
#line 368 "Kekkafree.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 368 "Kekkafree.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 16385;
#line 368 "Kekkafree.sqc"
      sql_setdlist[1].sqldata = (void*)freetext;
#line 368 "Kekkafree.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 368 "Kekkafree.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 368 "Kekkafree.sqc"
      sql_setdlist[2].sqldata = (void*)&ssssflg;
#line 368 "Kekkafree.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 368 "Kekkafree.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 368 "Kekkafree.sqc"
      sql_setdlist[3].sqldata = (void*)&ssknsflg;
#line 368 "Kekkafree.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 368 "Kekkafree.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 9;
#line 368 "Kekkafree.sqc"
      sql_setdlist[4].sqldata = (void*)dtnrtts;
#line 368 "Kekkafree.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 368 "Kekkafree.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 27;
#line 368 "Kekkafree.sqc"
      sql_setdlist[5].sqldata = (void*)dtnrdh;
#line 368 "Kekkafree.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 368 "Kekkafree.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 368 "Kekkafree.sqc"
      sql_setdlist[6].sqldata = (void*)ksndh;
#line 368 "Kekkafree.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 368 "Kekkafree.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 368 "Kekkafree.sqc"
      sql_setdlist[7].sqldata = (void*)knskisymd;
#line 368 "Kekkafree.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 368 "Kekkafree.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 368 "Kekkafree.sqc"
      sql_setdlist[8].sqldata = (void*)sriymd;
#line 368 "Kekkafree.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 368 "Kekkafree.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 14;
#line 368 "Kekkafree.sqc"
      sql_setdlist[9].sqldata = (void*)kntno;
#line 368 "Kekkafree.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 368 "Kekkafree.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 17;
#line 368 "Kekkafree.sqc"
      sql_setdlist[10].sqldata = (void*)knsgrp;
#line 368 "Kekkafree.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 368 "Kekkafree.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 8;
#line 368 "Kekkafree.sqc"
      sql_setdlist[11].sqldata = (void*)kmkcd;
#line 368 "Kekkafree.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 368 "Kekkafree.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 368 "Kekkafree.sqc"
      sql_setdlist[12].sqldata = (void*)&knssu;
#line 368 "Kekkafree.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 368 "Kekkafree.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 368 "Kekkafree.sqc"
      sql_setdlist[13].sqldata = (void*)&knssueda;
#line 368 "Kekkafree.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 368 "Kekkafree.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 368 "Kekkafree.sqc"
      sql_setdlist[14].sqldata = (void*)&frsb;
#line 368 "Kekkafree.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 368 "Kekkafree.sqc"
      sqlasetdata(2,0,15,sql_setdlist,0L,0L);
    }
#line 368 "Kekkafree.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 368 "Kekkafree.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 368 "Kekkafree.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 368 "Kekkafree.sqc"
  sqlastop(0L);
}

#line 368 "Kekkafree.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 373 "Kekkafree.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 377 "Kekkafree.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKekkafreeDelete()
 *    KEKKAFREE レコードを削除する
 * ■引数
 *    [I]  Kekkafree* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKekkafreeDelete( Kekkafree* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KekkafreeArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 401 "Kekkafree.sqc"


    
/*
EXEC SQL DELETE FROM KEKKAFREE
    WHERE
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd AND
		KNSSU = :knssu AND
		KNSSUEDA = :knssueda AND
		FRSB = :frsb;
*/

{
#line 412 "Kekkafree.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 412 "Kekkafree.sqc"
  sqlaaloc(2,8,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 412 "Kekkafree.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 412 "Kekkafree.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 412 "Kekkafree.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 412 "Kekkafree.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 412 "Kekkafree.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 412 "Kekkafree.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 412 "Kekkafree.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 412 "Kekkafree.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 412 "Kekkafree.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 412 "Kekkafree.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 412 "Kekkafree.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 412 "Kekkafree.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 412 "Kekkafree.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 412 "Kekkafree.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 412 "Kekkafree.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 412 "Kekkafree.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 412 "Kekkafree.sqc"
      sql_setdlist[5].sqldata = (void*)&knssu;
#line 412 "Kekkafree.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 412 "Kekkafree.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 412 "Kekkafree.sqc"
      sql_setdlist[6].sqldata = (void*)&knssueda;
#line 412 "Kekkafree.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 412 "Kekkafree.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 412 "Kekkafree.sqc"
      sql_setdlist[7].sqldata = (void*)&frsb;
#line 412 "Kekkafree.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 412 "Kekkafree.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 412 "Kekkafree.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 412 "Kekkafree.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 412 "Kekkafree.sqc"
  sqlastop(0L);
}

#line 412 "Kekkafree.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 417 "Kekkafree.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
