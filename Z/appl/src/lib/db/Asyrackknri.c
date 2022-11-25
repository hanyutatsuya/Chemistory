static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,90,66,80,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,50,90,65,83,89,82,32,32,0,0,0,0,0,0,0,0,
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


#line 1 "Asyrackknri.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Asyrackknri.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Asyrackknri.h"
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


#line 24 "Asyrackknri.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Asyrackknri.sqc"

	char    knskisymd[11];
	char    asyrckid[11];
	char    knskbn[3];
	char    rakbri[3];
	char    bskkbn[5];
	char    bsklne[5];
	char    bskgok[7];
	char    knsgrp[17];
	short   bthno;
	sqlint32  bthrckjbn;
	char    id2[11];
	char    id3[11];
	char    lnetndh[27];
	char    lnehsdh[27];
	char    rakjtflg;
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 46 "Asyrackknri.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Asyrackknri

BmlDMMInfo	AsyrackknriArray[] = {
	DMM_SDATE( knskisymd ),
	DMM_SSTRING( asyrckid ),
	DMM_SSTRING( knskbn ),
	DMM_SSTRING( rakbri ),
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( bsklne ),
	DMM_SSTRING( bskgok ),
	DMM_SSTRING( knsgrp ),
	DMM_SSHORT( bthno ),
	DMM_SLONG( bthrckjbn ),
	DMM_SSTRING( id2 ),
	DMM_SSTRING( id3 ),
	DMM_STIMESTAMP( lnetndh ),
	DMM_STIMESTAMP( lnehsdh ),
	DMM_SCHAR( rakjtflg ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbAsyrackknriSelectAll()
 *    ASYRACKKNRI レコード全件取得
 * ■引数
 *    [O]  Asyrackknri** arrayO 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbAsyrackknriSelectAll( Asyrackknri** arrayOut, int* numOut )
{
    Asyrackknri* array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 90 "Asyrackknri.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSKISYMD,
		ASYRCKID,
		KNSKBN,
		RAKBRI,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		KNSGRP,
		BTHNO,
		BTHRCKJBN,
		ID2,
		ID3,
		LNETNDH,
		LNEHSDH,
		RAKJTFLG,
		KSNDH
    FROM
        ASYRACKKNRI FOR READ ONLY;
*/

#line 111 "Asyrackknri.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 113 "Asyrackknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 113 "Asyrackknri.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 113 "Asyrackknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 113 "Asyrackknri.sqc"
  sqlastop(0L);
}

#line 113 "Asyrackknri.sqc"


    while( 1 ) {
        Asyrackknri* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knskisymd,
			:asyrckid,
			:knskbn,
			:rakbri,
			:bskkbn,
			:bsklne,
			:bskgok,
			:knsgrp,
			:bthno,
			:bthrckjbn,
			:id2,
			:id3,
			:lnetndh,
			:lnehsdh,
			:rakjtflg,
			:ksndh;
*/

{
#line 134 "Asyrackknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 134 "Asyrackknri.sqc"
  sqlaaloc(3,16,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[16];
#line 134 "Asyrackknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[1].sqldata = (void*)asyrckid;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[2].sqldata = (void*)knskbn;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[3].sqldata = (void*)rakbri;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 5;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[4].sqldata = (void*)bskkbn;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 5;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[5].sqldata = (void*)bsklne;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 7;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[6].sqldata = (void*)bskgok;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 17;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[7].sqldata = (void*)knsgrp;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[8].sqldata = (void*)&bthno;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[9].sqldata = (void*)&bthrckjbn;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[10].sqldata = (void*)id2;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[11].sqldata = (void*)id3;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 27;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[12].sqldata = (void*)lnetndh;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 27;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[13].sqldata = (void*)lnehsdh;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[14].sqldata = (void*)&rakjtflg;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[15].sqldata = (void*)ksndh;
#line 134 "Asyrackknri.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 134 "Asyrackknri.sqc"
      sqlasetdata(3,0,16,sql_setdlist,0L,0L);
    }
#line 134 "Asyrackknri.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 134 "Asyrackknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 134 "Asyrackknri.sqc"
  sqlastop(0L);
}

#line 134 "Asyrackknri.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Asyrackknri*)ZbmlRealloc( array,
                                    sizeof( Asyrackknri ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Asyrackknri ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, AsyrackknriArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 149 "Asyrackknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 149 "Asyrackknri.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 149 "Asyrackknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 149 "Asyrackknri.sqc"
  sqlastop(0L);
}

#line 149 "Asyrackknri.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 157 "Asyrackknri.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbAsyrackknriSelectKey()
 *    ASYRACKKNRI レコードKey条件取得
 * ■引数
 *    [I]  Asyrackknri* pKey    取得するレコードのキー
 *    [O]  Asyrackknri** arrayO 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbAsyrackknriSelectKey( Asyrackknri* pKey, Asyrackknri** arrayOut, int* numOut )
{
    Asyrackknri* array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, AsyrackknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 183 "Asyrackknri.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSKISYMD,
		ASYRCKID,
		KNSKBN,
		RAKBRI,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		KNSGRP,
		BTHNO,
		BTHRCKJBN,
		ID2,
		ID3,
		LNETNDH,
		LNEHSDH,
		RAKJTFLG,
		KSNDH
    FROM
        ASYRACKKNRI
    WHERE
		KNSKISYMD = :knskisymd AND
		ASYRCKID = :asyrckid FOR READ ONLY;
*/

#line 207 "Asyrackknri.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 209 "Asyrackknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 209 "Asyrackknri.sqc"
  sqlaaloc(2,2,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 209 "Asyrackknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 209 "Asyrackknri.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 209 "Asyrackknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 209 "Asyrackknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 209 "Asyrackknri.sqc"
      sql_setdlist[1].sqldata = (void*)asyrckid;
#line 209 "Asyrackknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 209 "Asyrackknri.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 209 "Asyrackknri.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 209 "Asyrackknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 209 "Asyrackknri.sqc"
  sqlastop(0L);
}

#line 209 "Asyrackknri.sqc"


    while( 1 ) {
        Asyrackknri* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knskisymd,
			:asyrckid,
			:knskbn,
			:rakbri,
			:bskkbn,
			:bsklne,
			:bskgok,
			:knsgrp,
			:bthno,
			:bthrckjbn,
			:id2,
			:id3,
			:lnetndh,
			:lnehsdh,
			:rakjtflg,
			:ksndh;
*/

{
#line 230 "Asyrackknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 230 "Asyrackknri.sqc"
  sqlaaloc(3,16,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[16];
#line 230 "Asyrackknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[1].sqldata = (void*)asyrckid;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[2].sqldata = (void*)knskbn;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[3].sqldata = (void*)rakbri;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 5;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[4].sqldata = (void*)bskkbn;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 5;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[5].sqldata = (void*)bsklne;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 7;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[6].sqldata = (void*)bskgok;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 17;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[7].sqldata = (void*)knsgrp;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[8].sqldata = (void*)&bthno;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[9].sqldata = (void*)&bthrckjbn;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[10].sqldata = (void*)id2;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[11].sqldata = (void*)id3;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 27;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[12].sqldata = (void*)lnetndh;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 27;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[13].sqldata = (void*)lnehsdh;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[14].sqldata = (void*)&rakjtflg;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[15].sqldata = (void*)ksndh;
#line 230 "Asyrackknri.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 230 "Asyrackknri.sqc"
      sqlasetdata(3,0,16,sql_setdlist,0L,0L);
    }
#line 230 "Asyrackknri.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 230 "Asyrackknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 230 "Asyrackknri.sqc"
  sqlastop(0L);
}

#line 230 "Asyrackknri.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Asyrackknri*)ZbmlRealloc( array,
                                    sizeof( Asyrackknri ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Asyrackknri ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, AsyrackknriArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 245 "Asyrackknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 245 "Asyrackknri.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 245 "Asyrackknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 245 "Asyrackknri.sqc"
  sqlastop(0L);
}

#line 245 "Asyrackknri.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 253 "Asyrackknri.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbAsyrackknriInsert()
 *    ASYRACKKNRI レコードを挿入する
 * ■引数
 *    [I]  Asyrackknri* rec     挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbAsyrackknriInsert( Asyrackknri* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, AsyrackknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 276 "Asyrackknri.sqc"


    
/*
EXEC SQL INSERT INTO ASYRACKKNRI
    (
		KNSKISYMD,
		ASYRCKID,
		KNSKBN,
		RAKBRI,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		KNSGRP,
		BTHNO,
		BTHRCKJBN,
		ID2,
		ID3,
		LNETNDH,
		LNEHSDH,
		RAKJTFLG,
		KSNDH
    ) VALUES (
		:knskisymd,
		:asyrckid,
		:knskbn,
		:rakbri,
		:bskkbn,
		:bsklne,
		:bskgok,
		:knsgrp,
		:bthno,
		:bthrckjbn,
		:id2,
		:id3,
		:lnetndh,
		:lnehsdh,
		:rakjtflg,
		:ksndh
    );
*/

{
#line 313 "Asyrackknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 313 "Asyrackknri.sqc"
  sqlaaloc(2,16,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[16];
#line 313 "Asyrackknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[1].sqldata = (void*)asyrckid;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[2].sqldata = (void*)knskbn;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[3].sqldata = (void*)rakbri;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 5;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[4].sqldata = (void*)bskkbn;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 5;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[5].sqldata = (void*)bsklne;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 7;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[6].sqldata = (void*)bskgok;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 17;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[7].sqldata = (void*)knsgrp;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[8].sqldata = (void*)&bthno;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[9].sqldata = (void*)&bthrckjbn;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[10].sqldata = (void*)id2;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[11].sqldata = (void*)id3;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 27;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[12].sqldata = (void*)lnetndh;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 27;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[13].sqldata = (void*)lnehsdh;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[14].sqldata = (void*)&rakjtflg;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[15].sqldata = (void*)ksndh;
#line 313 "Asyrackknri.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 313 "Asyrackknri.sqc"
      sqlasetdata(2,0,16,sql_setdlist,0L,0L);
    }
#line 313 "Asyrackknri.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 313 "Asyrackknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 313 "Asyrackknri.sqc"
  sqlastop(0L);
}

#line 313 "Asyrackknri.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 318 "Asyrackknri.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbAsyrackknriUpdate()
 *    ASYRACKKNRI レコードを更新する
 * ■引数
 *    [I]  Asyrackknri* rec     更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbAsyrackknriUpdate( Asyrackknri* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, AsyrackknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 342 "Asyrackknri.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 343 "Asyrackknri.sqc"


    
/*
EXEC SQL UPDATE ASYRACKKNRI
    SET (
		KNSKBN,
		RAKBRI,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		KNSGRP,
		BTHNO,
		BTHRCKJBN,
		ID2,
		ID3,
		LNETNDH,
		LNEHSDH,
		RAKJTFLG,
		KSNDH
    ) = (
		:knskbn,
		:rakbri,
		:bskkbn,
		:bsklne,
		:bskgok,
		:knsgrp,
		:bthno,
		:bthrckjbn,
		:id2,
		:id3,
		:lnetndh,
		:lnehsdh,
		:rakjtflg,
		:ksndh
    ) WHERE
		KNSKISYMD = :knskisymd AND
		ASYRCKID = :asyrckid;
*/

{
#line 378 "Asyrackknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 378 "Asyrackknri.sqc"
  sqlaaloc(2,16,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[16];
#line 378 "Asyrackknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[0].sqldata = (void*)knskbn;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[1].sqldata = (void*)rakbri;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[2].sqldata = (void*)bskkbn;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[3].sqldata = (void*)bsklne;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 7;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[4].sqldata = (void*)bskgok;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 17;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[5].sqldata = (void*)knsgrp;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[6].sqldata = (void*)&bthno;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[7].sqldata = (void*)&bthrckjbn;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[8].sqldata = (void*)id2;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[9].sqldata = (void*)id3;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 27;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[10].sqldata = (void*)lnetndh;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 27;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[11].sqldata = (void*)lnehsdh;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[12].sqltype = 452; sql_setdlist[12].sqllen = 1;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[12].sqldata = (void*)&rakjtflg;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 27;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[13].sqldata = (void*)ksndh;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 11;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[14].sqldata = (void*)knskisymd;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 11;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[15].sqldata = (void*)asyrckid;
#line 378 "Asyrackknri.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 378 "Asyrackknri.sqc"
      sqlasetdata(2,0,16,sql_setdlist,0L,0L);
    }
#line 378 "Asyrackknri.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 378 "Asyrackknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 378 "Asyrackknri.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 378 "Asyrackknri.sqc"
  sqlastop(0L);
}

#line 378 "Asyrackknri.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 383 "Asyrackknri.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 387 "Asyrackknri.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbAsyrackknriDelete()
 *    ASYRACKKNRI レコードを削除する
 * ■引数
 *    [I]  Asyrackknri* rec     削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbAsyrackknriDelete( Asyrackknri* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, AsyrackknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 411 "Asyrackknri.sqc"


    
/*
EXEC SQL DELETE FROM ASYRACKKNRI
    WHERE
		KNSKISYMD = :knskisymd AND
		ASYRCKID = :asyrckid;
*/

{
#line 416 "Asyrackknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 416 "Asyrackknri.sqc"
  sqlaaloc(2,2,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 416 "Asyrackknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 416 "Asyrackknri.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 416 "Asyrackknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 416 "Asyrackknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 416 "Asyrackknri.sqc"
      sql_setdlist[1].sqldata = (void*)asyrckid;
#line 416 "Asyrackknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 416 "Asyrackknri.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 416 "Asyrackknri.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 416 "Asyrackknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 416 "Asyrackknri.sqc"
  sqlastop(0L);
}

#line 416 "Asyrackknri.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 421 "Asyrackknri.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
