static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,108,66,82,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,50,50,90,72,75,75,75,32,0,0,0,0,0,0,0,0,
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


#line 1 "Hkkknri.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Hkkknri.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Hkkknri.h"
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


#line 24 "Hkkknri.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Hkkknri.sqc"

	char    hkksjymd[11];
	sqlint32  hkksjno;
	char    hkkkbn;
	char    hkkjkn;
	char    utkymd[11];
	char    sriymd[11];
	char    knsgrp[17];
	char    kmkcd[8];
	char    bskkbn[5];
	char    bskgok[7];
	char    hkkjknst[21];
	char    hkkjkned[21];
	char    seccd[3];
	char    hkkflnm[51];
	char    hkksjtts[9];
	char    hkkdh[27];
	char    hkkstdh[27];
	char    hkkeddh[27];
	char    tnsstdh[27];
	char    tnseddh[27];
	sqlint32  hkkssknsu;
	sqlint32  hkkhrysu;
	char    ssnmtfilid[13];
	char    hkkjkflg[3];
	char    hkkerrcode[9];
	short   kkirilotno;
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 57 "Hkkknri.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Hkkknri

BmlDMMInfo	HkkknriArray[] = {
	DMM_SDATE( hkksjymd ),
	DMM_SLONG( hkksjno ),
	DMM_SCHAR( hkkkbn ),
	DMM_SCHAR( hkkjkn ),
	DMM_SDATE( utkymd ),
	DMM_SDATE( sriymd ),
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( bskgok ),
	DMM_SSTRING( hkkjknst ),
	DMM_SSTRING( hkkjkned ),
	DMM_SSTRING( seccd ),
	DMM_SSTRING( hkkflnm ),
	DMM_SSTRING( hkksjtts ),
	DMM_STIMESTAMP( hkkdh ),
	DMM_STIMESTAMP( hkkstdh ),
	DMM_STIMESTAMP( hkkeddh ),
	DMM_STIMESTAMP( tnsstdh ),
	DMM_STIMESTAMP( tnseddh ),
	DMM_SLONG( hkkssknsu ),
	DMM_SLONG( hkkhrysu ),
	DMM_SSTRING( ssnmtfilid ),
	DMM_SSTRING( hkkjkflg ),
	DMM_SSTRING( hkkerrcode ),
	DMM_SSHORT( kkirilotno ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbHkkknriSelectAll()
 *    HKKKNRI レコード全件取得
 * ■引数
 *    [O]  Hkkknri** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbHkkknriSelectAll( Hkkknri** arrayOut, int* numOut )
{
    Hkkknri*    array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 112 "Hkkknri.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		HKKSJYMD,
		HKKSJNO,
		HKKKBN,
		HKKJKN,
		UTKYMD,
		SRIYMD,
		KNSGRP,
		KMKCD,
		BSKKBN,
		BSKGOK,
		HKKJKNST,
		HKKJKNED,
		SECCD,
		HKKFLNM,
		HKKSJTTS,
		HKKDH,
		HKKSTDH,
		HKKEDDH,
		TNSSTDH,
		TNSEDDH,
		HKKSSKNSU,
		HKKHRYSU,
		SSNMTFILID,
		HKKJKFLG,
		HKKERRCODE,
		KKIRILOTNO,
		KSNDH
    FROM
        HKKKNRI FOR READ ONLY;
*/

#line 144 "Hkkknri.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 146 "Hkkknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 146 "Hkkknri.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 146 "Hkkknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 146 "Hkkknri.sqc"
  sqlastop(0L);
}

#line 146 "Hkkknri.sqc"


    while( 1 ) {
        Hkkknri* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:hkksjymd,
			:hkksjno,
			:hkkkbn,
			:hkkjkn,
			:utkymd,
			:sriymd,
			:knsgrp,
			:kmkcd,
			:bskkbn,
			:bskgok,
			:hkkjknst,
			:hkkjkned,
			:seccd,
			:hkkflnm,
			:hkksjtts,
			:hkkdh,
			:hkkstdh,
			:hkkeddh,
			:tnsstdh,
			:tnseddh,
			:hkkssknsu,
			:hkkhrysu,
			:ssnmtfilid,
			:hkkjkflg,
			:hkkerrcode,
			:kkirilotno,
			:ksndh;
*/

{
#line 178 "Hkkknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 178 "Hkkknri.sqc"
  sqlaaloc(3,27,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[27];
#line 178 "Hkkknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 178 "Hkkknri.sqc"
      sql_setdlist[0].sqldata = (void*)hkksjymd;
#line 178 "Hkkknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 178 "Hkkknri.sqc"
      sql_setdlist[1].sqldata = (void*)&hkksjno;
#line 178 "Hkkknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 178 "Hkkknri.sqc"
      sql_setdlist[2].sqldata = (void*)&hkkkbn;
#line 178 "Hkkknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 178 "Hkkknri.sqc"
      sql_setdlist[3].sqldata = (void*)&hkkjkn;
#line 178 "Hkkknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 178 "Hkkknri.sqc"
      sql_setdlist[4].sqldata = (void*)utkymd;
#line 178 "Hkkknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 178 "Hkkknri.sqc"
      sql_setdlist[5].sqldata = (void*)sriymd;
#line 178 "Hkkknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 17;
#line 178 "Hkkknri.sqc"
      sql_setdlist[6].sqldata = (void*)knsgrp;
#line 178 "Hkkknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 8;
#line 178 "Hkkknri.sqc"
      sql_setdlist[7].sqldata = (void*)kmkcd;
#line 178 "Hkkknri.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 5;
#line 178 "Hkkknri.sqc"
      sql_setdlist[8].sqldata = (void*)bskkbn;
#line 178 "Hkkknri.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 7;
#line 178 "Hkkknri.sqc"
      sql_setdlist[9].sqldata = (void*)bskgok;
#line 178 "Hkkknri.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 21;
#line 178 "Hkkknri.sqc"
      sql_setdlist[10].sqldata = (void*)hkkjknst;
#line 178 "Hkkknri.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 21;
#line 178 "Hkkknri.sqc"
      sql_setdlist[11].sqldata = (void*)hkkjkned;
#line 178 "Hkkknri.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 3;
#line 178 "Hkkknri.sqc"
      sql_setdlist[12].sqldata = (void*)seccd;
#line 178 "Hkkknri.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 51;
#line 178 "Hkkknri.sqc"
      sql_setdlist[13].sqldata = (void*)hkkflnm;
#line 178 "Hkkknri.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 9;
#line 178 "Hkkknri.sqc"
      sql_setdlist[14].sqldata = (void*)hkksjtts;
#line 178 "Hkkknri.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 178 "Hkkknri.sqc"
      sql_setdlist[15].sqldata = (void*)hkkdh;
#line 178 "Hkkknri.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 27;
#line 178 "Hkkknri.sqc"
      sql_setdlist[16].sqldata = (void*)hkkstdh;
#line 178 "Hkkknri.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 178 "Hkkknri.sqc"
      sql_setdlist[17].sqldata = (void*)hkkeddh;
#line 178 "Hkkknri.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 178 "Hkkknri.sqc"
      sql_setdlist[18].sqldata = (void*)tnsstdh;
#line 178 "Hkkknri.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 178 "Hkkknri.sqc"
      sql_setdlist[19].sqldata = (void*)tnseddh;
#line 178 "Hkkknri.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[20].sqltype = 496; sql_setdlist[20].sqllen = 4;
#line 178 "Hkkknri.sqc"
      sql_setdlist[20].sqldata = (void*)&hkkssknsu;
#line 178 "Hkkknri.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[21].sqltype = 496; sql_setdlist[21].sqllen = 4;
#line 178 "Hkkknri.sqc"
      sql_setdlist[21].sqldata = (void*)&hkkhrysu;
#line 178 "Hkkknri.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 13;
#line 178 "Hkkknri.sqc"
      sql_setdlist[22].sqldata = (void*)ssnmtfilid;
#line 178 "Hkkknri.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 3;
#line 178 "Hkkknri.sqc"
      sql_setdlist[23].sqldata = (void*)hkkjkflg;
#line 178 "Hkkknri.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 9;
#line 178 "Hkkknri.sqc"
      sql_setdlist[24].sqldata = (void*)hkkerrcode;
#line 178 "Hkkknri.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[25].sqltype = 500; sql_setdlist[25].sqllen = 2;
#line 178 "Hkkknri.sqc"
      sql_setdlist[25].sqldata = (void*)&kkirilotno;
#line 178 "Hkkknri.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 27;
#line 178 "Hkkknri.sqc"
      sql_setdlist[26].sqldata = (void*)ksndh;
#line 178 "Hkkknri.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 178 "Hkkknri.sqc"
      sqlasetdata(3,0,27,sql_setdlist,0L,0L);
    }
#line 178 "Hkkknri.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 178 "Hkkknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 178 "Hkkknri.sqc"
  sqlastop(0L);
}

#line 178 "Hkkknri.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Hkkknri*)ZbmlRealloc( array,
                                    sizeof( Hkkknri ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Hkkknri ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, HkkknriArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 193 "Hkkknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 193 "Hkkknri.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 193 "Hkkknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 193 "Hkkknri.sqc"
  sqlastop(0L);
}

#line 193 "Hkkknri.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 201 "Hkkknri.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbHkkknriSelectKey()
 *    HKKKNRI レコードKey条件取得
 * ■引数
 *    [I]  Hkkknri* pKey       取得するレコードのキー
 *    [O]  Hkkknri** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbHkkknriSelectKey( Hkkknri* pKey, Hkkknri** arrayOut, int* numOut )
{
    Hkkknri*    array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, HkkknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 227 "Hkkknri.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		HKKSJYMD,
		HKKSJNO,
		HKKKBN,
		HKKJKN,
		UTKYMD,
		SRIYMD,
		KNSGRP,
		KMKCD,
		BSKKBN,
		BSKGOK,
		HKKJKNST,
		HKKJKNED,
		SECCD,
		HKKFLNM,
		HKKSJTTS,
		HKKDH,
		HKKSTDH,
		HKKEDDH,
		TNSSTDH,
		TNSEDDH,
		HKKSSKNSU,
		HKKHRYSU,
		SSNMTFILID,
		HKKJKFLG,
		HKKERRCODE,
		KKIRILOTNO,
		KSNDH
    FROM
        HKKKNRI
    WHERE
		HKKSJYMD = :hkksjymd AND
		HKKSJNO = :hkksjno FOR READ ONLY;
*/

#line 262 "Hkkknri.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 264 "Hkkknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 264 "Hkkknri.sqc"
  sqlaaloc(2,2,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 264 "Hkkknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 264 "Hkkknri.sqc"
      sql_setdlist[0].sqldata = (void*)hkksjymd;
#line 264 "Hkkknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 264 "Hkkknri.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 264 "Hkkknri.sqc"
      sql_setdlist[1].sqldata = (void*)&hkksjno;
#line 264 "Hkkknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 264 "Hkkknri.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 264 "Hkkknri.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 264 "Hkkknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 264 "Hkkknri.sqc"
  sqlastop(0L);
}

#line 264 "Hkkknri.sqc"


    while( 1 ) {
        Hkkknri* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:hkksjymd,
			:hkksjno,
			:hkkkbn,
			:hkkjkn,
			:utkymd,
			:sriymd,
			:knsgrp,
			:kmkcd,
			:bskkbn,
			:bskgok,
			:hkkjknst,
			:hkkjkned,
			:seccd,
			:hkkflnm,
			:hkksjtts,
			:hkkdh,
			:hkkstdh,
			:hkkeddh,
			:tnsstdh,
			:tnseddh,
			:hkkssknsu,
			:hkkhrysu,
			:ssnmtfilid,
			:hkkjkflg,
			:hkkerrcode,
			:kkirilotno,
			:ksndh;
*/

{
#line 296 "Hkkknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 296 "Hkkknri.sqc"
  sqlaaloc(3,27,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[27];
#line 296 "Hkkknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 296 "Hkkknri.sqc"
      sql_setdlist[0].sqldata = (void*)hkksjymd;
#line 296 "Hkkknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 296 "Hkkknri.sqc"
      sql_setdlist[1].sqldata = (void*)&hkksjno;
#line 296 "Hkkknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 296 "Hkkknri.sqc"
      sql_setdlist[2].sqldata = (void*)&hkkkbn;
#line 296 "Hkkknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 296 "Hkkknri.sqc"
      sql_setdlist[3].sqldata = (void*)&hkkjkn;
#line 296 "Hkkknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 296 "Hkkknri.sqc"
      sql_setdlist[4].sqldata = (void*)utkymd;
#line 296 "Hkkknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 296 "Hkkknri.sqc"
      sql_setdlist[5].sqldata = (void*)sriymd;
#line 296 "Hkkknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 17;
#line 296 "Hkkknri.sqc"
      sql_setdlist[6].sqldata = (void*)knsgrp;
#line 296 "Hkkknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 8;
#line 296 "Hkkknri.sqc"
      sql_setdlist[7].sqldata = (void*)kmkcd;
#line 296 "Hkkknri.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 5;
#line 296 "Hkkknri.sqc"
      sql_setdlist[8].sqldata = (void*)bskkbn;
#line 296 "Hkkknri.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 7;
#line 296 "Hkkknri.sqc"
      sql_setdlist[9].sqldata = (void*)bskgok;
#line 296 "Hkkknri.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 21;
#line 296 "Hkkknri.sqc"
      sql_setdlist[10].sqldata = (void*)hkkjknst;
#line 296 "Hkkknri.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 21;
#line 296 "Hkkknri.sqc"
      sql_setdlist[11].sqldata = (void*)hkkjkned;
#line 296 "Hkkknri.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 3;
#line 296 "Hkkknri.sqc"
      sql_setdlist[12].sqldata = (void*)seccd;
#line 296 "Hkkknri.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 51;
#line 296 "Hkkknri.sqc"
      sql_setdlist[13].sqldata = (void*)hkkflnm;
#line 296 "Hkkknri.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 9;
#line 296 "Hkkknri.sqc"
      sql_setdlist[14].sqldata = (void*)hkksjtts;
#line 296 "Hkkknri.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 296 "Hkkknri.sqc"
      sql_setdlist[15].sqldata = (void*)hkkdh;
#line 296 "Hkkknri.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 27;
#line 296 "Hkkknri.sqc"
      sql_setdlist[16].sqldata = (void*)hkkstdh;
#line 296 "Hkkknri.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 296 "Hkkknri.sqc"
      sql_setdlist[17].sqldata = (void*)hkkeddh;
#line 296 "Hkkknri.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 296 "Hkkknri.sqc"
      sql_setdlist[18].sqldata = (void*)tnsstdh;
#line 296 "Hkkknri.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 296 "Hkkknri.sqc"
      sql_setdlist[19].sqldata = (void*)tnseddh;
#line 296 "Hkkknri.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[20].sqltype = 496; sql_setdlist[20].sqllen = 4;
#line 296 "Hkkknri.sqc"
      sql_setdlist[20].sqldata = (void*)&hkkssknsu;
#line 296 "Hkkknri.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[21].sqltype = 496; sql_setdlist[21].sqllen = 4;
#line 296 "Hkkknri.sqc"
      sql_setdlist[21].sqldata = (void*)&hkkhrysu;
#line 296 "Hkkknri.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 13;
#line 296 "Hkkknri.sqc"
      sql_setdlist[22].sqldata = (void*)ssnmtfilid;
#line 296 "Hkkknri.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 3;
#line 296 "Hkkknri.sqc"
      sql_setdlist[23].sqldata = (void*)hkkjkflg;
#line 296 "Hkkknri.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 9;
#line 296 "Hkkknri.sqc"
      sql_setdlist[24].sqldata = (void*)hkkerrcode;
#line 296 "Hkkknri.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[25].sqltype = 500; sql_setdlist[25].sqllen = 2;
#line 296 "Hkkknri.sqc"
      sql_setdlist[25].sqldata = (void*)&kkirilotno;
#line 296 "Hkkknri.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 27;
#line 296 "Hkkknri.sqc"
      sql_setdlist[26].sqldata = (void*)ksndh;
#line 296 "Hkkknri.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 296 "Hkkknri.sqc"
      sqlasetdata(3,0,27,sql_setdlist,0L,0L);
    }
#line 296 "Hkkknri.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 296 "Hkkknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 296 "Hkkknri.sqc"
  sqlastop(0L);
}

#line 296 "Hkkknri.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Hkkknri*)ZbmlRealloc( array,
                                    sizeof( Hkkknri ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Hkkknri ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, HkkknriArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 311 "Hkkknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 311 "Hkkknri.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 311 "Hkkknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 311 "Hkkknri.sqc"
  sqlastop(0L);
}

#line 311 "Hkkknri.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 319 "Hkkknri.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbHkkknriInsert()
 *    HKKKNRI レコードを挿入する
 * ■引数
 *    [I]  Hkkknri* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbHkkknriInsert( Hkkknri* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, HkkknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 342 "Hkkknri.sqc"


    
/*
EXEC SQL INSERT INTO HKKKNRI
    (
		HKKSJYMD,
		HKKSJNO,
		HKKKBN,
		HKKJKN,
		UTKYMD,
		SRIYMD,
		KNSGRP,
		KMKCD,
		BSKKBN,
		BSKGOK,
		HKKJKNST,
		HKKJKNED,
		SECCD,
		HKKFLNM,
		HKKSJTTS,
		HKKDH,
		HKKSTDH,
		HKKEDDH,
		TNSSTDH,
		TNSEDDH,
		HKKSSKNSU,
		HKKHRYSU,
		SSNMTFILID,
		HKKJKFLG,
		HKKERRCODE,
		KKIRILOTNO,
		KSNDH
    ) VALUES (
		:hkksjymd,
		:hkksjno,
		:hkkkbn,
		:hkkjkn,
		:utkymd,
		:sriymd,
		:knsgrp,
		:kmkcd,
		:bskkbn,
		:bskgok,
		:hkkjknst,
		:hkkjkned,
		:seccd,
		:hkkflnm,
		:hkksjtts,
		:hkkdh,
		:hkkstdh,
		:hkkeddh,
		:tnsstdh,
		:tnseddh,
		:hkkssknsu,
		:hkkhrysu,
		:ssnmtfilid,
		:hkkjkflg,
		:hkkerrcode,
		:kkirilotno,
		:ksndh
    );
*/

{
#line 401 "Hkkknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 401 "Hkkknri.sqc"
  sqlaaloc(2,27,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[27];
#line 401 "Hkkknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 401 "Hkkknri.sqc"
      sql_setdlist[0].sqldata = (void*)hkksjymd;
#line 401 "Hkkknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 401 "Hkkknri.sqc"
      sql_setdlist[1].sqldata = (void*)&hkksjno;
#line 401 "Hkkknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 401 "Hkkknri.sqc"
      sql_setdlist[2].sqldata = (void*)&hkkkbn;
#line 401 "Hkkknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 401 "Hkkknri.sqc"
      sql_setdlist[3].sqldata = (void*)&hkkjkn;
#line 401 "Hkkknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 401 "Hkkknri.sqc"
      sql_setdlist[4].sqldata = (void*)utkymd;
#line 401 "Hkkknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 401 "Hkkknri.sqc"
      sql_setdlist[5].sqldata = (void*)sriymd;
#line 401 "Hkkknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 17;
#line 401 "Hkkknri.sqc"
      sql_setdlist[6].sqldata = (void*)knsgrp;
#line 401 "Hkkknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 8;
#line 401 "Hkkknri.sqc"
      sql_setdlist[7].sqldata = (void*)kmkcd;
#line 401 "Hkkknri.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 5;
#line 401 "Hkkknri.sqc"
      sql_setdlist[8].sqldata = (void*)bskkbn;
#line 401 "Hkkknri.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 7;
#line 401 "Hkkknri.sqc"
      sql_setdlist[9].sqldata = (void*)bskgok;
#line 401 "Hkkknri.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 21;
#line 401 "Hkkknri.sqc"
      sql_setdlist[10].sqldata = (void*)hkkjknst;
#line 401 "Hkkknri.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 21;
#line 401 "Hkkknri.sqc"
      sql_setdlist[11].sqldata = (void*)hkkjkned;
#line 401 "Hkkknri.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 3;
#line 401 "Hkkknri.sqc"
      sql_setdlist[12].sqldata = (void*)seccd;
#line 401 "Hkkknri.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 51;
#line 401 "Hkkknri.sqc"
      sql_setdlist[13].sqldata = (void*)hkkflnm;
#line 401 "Hkkknri.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 9;
#line 401 "Hkkknri.sqc"
      sql_setdlist[14].sqldata = (void*)hkksjtts;
#line 401 "Hkkknri.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 401 "Hkkknri.sqc"
      sql_setdlist[15].sqldata = (void*)hkkdh;
#line 401 "Hkkknri.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 27;
#line 401 "Hkkknri.sqc"
      sql_setdlist[16].sqldata = (void*)hkkstdh;
#line 401 "Hkkknri.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 401 "Hkkknri.sqc"
      sql_setdlist[17].sqldata = (void*)hkkeddh;
#line 401 "Hkkknri.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 401 "Hkkknri.sqc"
      sql_setdlist[18].sqldata = (void*)tnsstdh;
#line 401 "Hkkknri.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 401 "Hkkknri.sqc"
      sql_setdlist[19].sqldata = (void*)tnseddh;
#line 401 "Hkkknri.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[20].sqltype = 496; sql_setdlist[20].sqllen = 4;
#line 401 "Hkkknri.sqc"
      sql_setdlist[20].sqldata = (void*)&hkkssknsu;
#line 401 "Hkkknri.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[21].sqltype = 496; sql_setdlist[21].sqllen = 4;
#line 401 "Hkkknri.sqc"
      sql_setdlist[21].sqldata = (void*)&hkkhrysu;
#line 401 "Hkkknri.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 13;
#line 401 "Hkkknri.sqc"
      sql_setdlist[22].sqldata = (void*)ssnmtfilid;
#line 401 "Hkkknri.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 3;
#line 401 "Hkkknri.sqc"
      sql_setdlist[23].sqldata = (void*)hkkjkflg;
#line 401 "Hkkknri.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 9;
#line 401 "Hkkknri.sqc"
      sql_setdlist[24].sqldata = (void*)hkkerrcode;
#line 401 "Hkkknri.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[25].sqltype = 500; sql_setdlist[25].sqllen = 2;
#line 401 "Hkkknri.sqc"
      sql_setdlist[25].sqldata = (void*)&kkirilotno;
#line 401 "Hkkknri.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 27;
#line 401 "Hkkknri.sqc"
      sql_setdlist[26].sqldata = (void*)ksndh;
#line 401 "Hkkknri.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 401 "Hkkknri.sqc"
      sqlasetdata(2,0,27,sql_setdlist,0L,0L);
    }
#line 401 "Hkkknri.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 401 "Hkkknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 401 "Hkkknri.sqc"
  sqlastop(0L);
}

#line 401 "Hkkknri.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 406 "Hkkknri.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbHkkknriUpdate()
 *    HKKKNRI レコードを更新する
 * ■引数
 *    [I]  Hkkknri* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbHkkknriUpdate( Hkkknri* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, HkkknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 430 "Hkkknri.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 431 "Hkkknri.sqc"


    
/*
EXEC SQL UPDATE HKKKNRI
    SET (
		HKKKBN,
		HKKJKN,
		UTKYMD,
		SRIYMD,
		KNSGRP,
		KMKCD,
		BSKKBN,
		BSKGOK,
		HKKJKNST,
		HKKJKNED,
		SECCD,
		HKKFLNM,
		HKKSJTTS,
		HKKDH,
		HKKSTDH,
		HKKEDDH,
		TNSSTDH,
		TNSEDDH,
		HKKSSKNSU,
		HKKHRYSU,
		SSNMTFILID,
		HKKJKFLG,
		HKKERRCODE,
		KKIRILOTNO,
		KSNDH
    ) = (
		:hkkkbn,
		:hkkjkn,
		:utkymd,
		:sriymd,
		:knsgrp,
		:kmkcd,
		:bskkbn,
		:bskgok,
		:hkkjknst,
		:hkkjkned,
		:seccd,
		:hkkflnm,
		:hkksjtts,
		:hkkdh,
		:hkkstdh,
		:hkkeddh,
		:tnsstdh,
		:tnseddh,
		:hkkssknsu,
		:hkkhrysu,
		:ssnmtfilid,
		:hkkjkflg,
		:hkkerrcode,
		:kkirilotno,
		:ksndh
    ) WHERE
		HKKSJYMD = :hkksjymd AND
		HKKSJNO = :hkksjno;
*/

{
#line 488 "Hkkknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 488 "Hkkknri.sqc"
  sqlaaloc(2,27,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[27];
#line 488 "Hkkknri.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 488 "Hkkknri.sqc"
      sql_setdlist[0].sqldata = (void*)&hkkkbn;
#line 488 "Hkkknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 488 "Hkkknri.sqc"
      sql_setdlist[1].sqldata = (void*)&hkkjkn;
#line 488 "Hkkknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 488 "Hkkknri.sqc"
      sql_setdlist[2].sqldata = (void*)utkymd;
#line 488 "Hkkknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 488 "Hkkknri.sqc"
      sql_setdlist[3].sqldata = (void*)sriymd;
#line 488 "Hkkknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 488 "Hkkknri.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 488 "Hkkknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 488 "Hkkknri.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 488 "Hkkknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 5;
#line 488 "Hkkknri.sqc"
      sql_setdlist[6].sqldata = (void*)bskkbn;
#line 488 "Hkkknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 7;
#line 488 "Hkkknri.sqc"
      sql_setdlist[7].sqldata = (void*)bskgok;
#line 488 "Hkkknri.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 21;
#line 488 "Hkkknri.sqc"
      sql_setdlist[8].sqldata = (void*)hkkjknst;
#line 488 "Hkkknri.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 21;
#line 488 "Hkkknri.sqc"
      sql_setdlist[9].sqldata = (void*)hkkjkned;
#line 488 "Hkkknri.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 3;
#line 488 "Hkkknri.sqc"
      sql_setdlist[10].sqldata = (void*)seccd;
#line 488 "Hkkknri.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 51;
#line 488 "Hkkknri.sqc"
      sql_setdlist[11].sqldata = (void*)hkkflnm;
#line 488 "Hkkknri.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 488 "Hkkknri.sqc"
      sql_setdlist[12].sqldata = (void*)hkksjtts;
#line 488 "Hkkknri.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 27;
#line 488 "Hkkknri.sqc"
      sql_setdlist[13].sqldata = (void*)hkkdh;
#line 488 "Hkkknri.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 27;
#line 488 "Hkkknri.sqc"
      sql_setdlist[14].sqldata = (void*)hkkstdh;
#line 488 "Hkkknri.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 488 "Hkkknri.sqc"
      sql_setdlist[15].sqldata = (void*)hkkeddh;
#line 488 "Hkkknri.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 27;
#line 488 "Hkkknri.sqc"
      sql_setdlist[16].sqldata = (void*)tnsstdh;
#line 488 "Hkkknri.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 488 "Hkkknri.sqc"
      sql_setdlist[17].sqldata = (void*)tnseddh;
#line 488 "Hkkknri.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[18].sqltype = 496; sql_setdlist[18].sqllen = 4;
#line 488 "Hkkknri.sqc"
      sql_setdlist[18].sqldata = (void*)&hkkssknsu;
#line 488 "Hkkknri.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[19].sqltype = 496; sql_setdlist[19].sqllen = 4;
#line 488 "Hkkknri.sqc"
      sql_setdlist[19].sqldata = (void*)&hkkhrysu;
#line 488 "Hkkknri.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 13;
#line 488 "Hkkknri.sqc"
      sql_setdlist[20].sqldata = (void*)ssnmtfilid;
#line 488 "Hkkknri.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 3;
#line 488 "Hkkknri.sqc"
      sql_setdlist[21].sqldata = (void*)hkkjkflg;
#line 488 "Hkkknri.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 9;
#line 488 "Hkkknri.sqc"
      sql_setdlist[22].sqldata = (void*)hkkerrcode;
#line 488 "Hkkknri.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[23].sqltype = 500; sql_setdlist[23].sqllen = 2;
#line 488 "Hkkknri.sqc"
      sql_setdlist[23].sqldata = (void*)&kkirilotno;
#line 488 "Hkkknri.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 27;
#line 488 "Hkkknri.sqc"
      sql_setdlist[24].sqldata = (void*)ksndh;
#line 488 "Hkkknri.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 11;
#line 488 "Hkkknri.sqc"
      sql_setdlist[25].sqldata = (void*)hkksjymd;
#line 488 "Hkkknri.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sql_setdlist[26].sqltype = 496; sql_setdlist[26].sqllen = 4;
#line 488 "Hkkknri.sqc"
      sql_setdlist[26].sqldata = (void*)&hkksjno;
#line 488 "Hkkknri.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 488 "Hkkknri.sqc"
      sqlasetdata(2,0,27,sql_setdlist,0L,0L);
    }
#line 488 "Hkkknri.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 488 "Hkkknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 488 "Hkkknri.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 488 "Hkkknri.sqc"
  sqlastop(0L);
}

#line 488 "Hkkknri.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 493 "Hkkknri.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 497 "Hkkknri.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbHkkknriDelete()
 *    HKKKNRI レコードを削除する
 * ■引数
 *    [I]  Hkkknri* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbHkkknriDelete( Hkkknri* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, HkkknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 521 "Hkkknri.sqc"


    
/*
EXEC SQL DELETE FROM HKKKNRI
    WHERE
		HKKSJYMD = :hkksjymd AND
		HKKSJNO = :hkksjno;
*/

{
#line 526 "Hkkknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 526 "Hkkknri.sqc"
  sqlaaloc(2,2,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 526 "Hkkknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 526 "Hkkknri.sqc"
      sql_setdlist[0].sqldata = (void*)hkksjymd;
#line 526 "Hkkknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 526 "Hkkknri.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 526 "Hkkknri.sqc"
      sql_setdlist[1].sqldata = (void*)&hkksjno;
#line 526 "Hkkknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 526 "Hkkknri.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 526 "Hkkknri.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 526 "Hkkknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 526 "Hkkknri.sqc"
  sqlastop(0L);
}

#line 526 "Hkkknri.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 531 "Hkkknri.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
