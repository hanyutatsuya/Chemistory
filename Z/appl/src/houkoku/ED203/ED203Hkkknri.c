static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,69,66,67,89,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,69,68,50,48,51,72,75,75,0,0,0,0,0,0,0,0,
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


#line 1 "ED203Hkkknri.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： ED203Hkkknri.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-03-10                    Create
 **********************************************************************/
#include <stdio.h>

#include "ED203Hkkknri.h"
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


#line 24 "ED203Hkkknri.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "ED203Hkkknri.sqc"

	char    hkksjymd[11];
	sqlint32  hkksjno;
	char    hkkkbn;
	char    hkkjkn;
	char    knskisymd[11];
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

#line 58 "ED203Hkkknri.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Hkkknri

BmlDMMInfo	HkkknriArray[] = {
	DMM_SDATE( hkksjymd ),
	DMM_SLONG( hkksjno ),
	DMM_SCHAR( hkkkbn ),
	DMM_SCHAR( hkkjkn ),
	DMM_SDATE( knskisymd ),
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
 * ZdbHkkknriED203SelectAll()
 *    HKKKNRI レコード全件取得
 * ■引数
 *    [O]  Hkkknri** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbHkkknriED203SelectAll( Hkkknri** arrayOut, int* numOut )
{
    Hkkknri*    array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 114 "ED203Hkkknri.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		HKKSJYMD,
		HKKSJNO,
		HKKKBN,
		HKKJKN,
		KNSKISYMD,
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
			HKKJKFLG = '0'
		AND HKKJKN = '7'
		FOR READ ONLY;
*/

#line 151 "ED203Hkkknri.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 153 "ED203Hkkknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 153 "ED203Hkkknri.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 153 "ED203Hkkknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 153 "ED203Hkkknri.sqc"
  sqlastop(0L);
}

#line 153 "ED203Hkkknri.sqc"


    while( 1 ) {
        Hkkknri* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:hkksjymd,
			:hkksjno,
			:hkkkbn,
			:hkkjkn,
			:knskisymd,
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
#line 186 "ED203Hkkknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 186 "ED203Hkkknri.sqc"
  sqlaaloc(3,28,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[28];
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[0].sqldata = (void*)hkksjymd;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[1].sqldata = (void*)&hkksjno;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[2].sqldata = (void*)&hkkkbn;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[3].sqldata = (void*)&hkkjkn;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[4].sqldata = (void*)knskisymd;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[5].sqldata = (void*)utkymd;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[6].sqldata = (void*)sriymd;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 17;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[7].sqldata = (void*)knsgrp;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 8;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[8].sqldata = (void*)kmkcd;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 5;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[9].sqldata = (void*)bskkbn;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 7;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[10].sqldata = (void*)bskgok;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 21;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[11].sqldata = (void*)hkkjknst;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 21;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[12].sqldata = (void*)hkkjkned;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 3;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[13].sqldata = (void*)seccd;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 51;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[14].sqldata = (void*)hkkflnm;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[15].sqldata = (void*)hkksjtts;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 27;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[16].sqldata = (void*)hkkdh;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[17].sqldata = (void*)hkkstdh;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[18].sqldata = (void*)hkkeddh;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[19].sqldata = (void*)tnsstdh;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 27;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[20].sqldata = (void*)tnseddh;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[21].sqltype = 496; sql_setdlist[21].sqllen = 4;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[21].sqldata = (void*)&hkkssknsu;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[22].sqltype = 496; sql_setdlist[22].sqllen = 4;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[22].sqldata = (void*)&hkkhrysu;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 13;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[23].sqldata = (void*)ssnmtfilid;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 3;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[24].sqldata = (void*)hkkjkflg;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 9;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[25].sqldata = (void*)hkkerrcode;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[26].sqltype = 500; sql_setdlist[26].sqllen = 2;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[26].sqldata = (void*)&kkirilotno;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 27;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[27].sqldata = (void*)ksndh;
#line 186 "ED203Hkkknri.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 186 "ED203Hkkknri.sqc"
      sqlasetdata(3,0,28,sql_setdlist,0L,0L);
    }
#line 186 "ED203Hkkknri.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 186 "ED203Hkkknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 186 "ED203Hkkknri.sqc"
  sqlastop(0L);
}

#line 186 "ED203Hkkknri.sqc"


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
#line 201 "ED203Hkkknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 201 "ED203Hkkknri.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 201 "ED203Hkkknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 201 "ED203Hkkknri.sqc"
  sqlastop(0L);
}

#line 201 "ED203Hkkknri.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 209 "ED203Hkkknri.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbHkkknriED203Update()
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
long ZdbHkkknriED203Update( Hkkknri* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, HkkknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 233 "ED203Hkkknri.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 234 "ED203Hkkknri.sqc"


    
/*
EXEC SQL UPDATE HKKKNRI
    SET (
		HKKKBN,
		HKKJKN,
		KNSKISYMD,
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
		:knskisymd,
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
		current timestamp
    ) WHERE
		HKKSJYMD = :hkksjymd AND
		HKKSJNO = :hkksjno;
*/

{
#line 293 "ED203Hkkknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 293 "ED203Hkkknri.sqc"
  sqlaaloc(2,27,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[27];
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[0].sqldata = (void*)&hkkkbn;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[1].sqldata = (void*)&hkkjkn;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[2].sqldata = (void*)knskisymd;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[3].sqldata = (void*)utkymd;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[4].sqldata = (void*)sriymd;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 17;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[5].sqldata = (void*)knsgrp;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[6].sqldata = (void*)kmkcd;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 5;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[7].sqldata = (void*)bskkbn;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 7;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[8].sqldata = (void*)bskgok;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 21;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[9].sqldata = (void*)hkkjknst;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 21;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[10].sqldata = (void*)hkkjkned;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 3;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[11].sqldata = (void*)seccd;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 51;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[12].sqldata = (void*)hkkflnm;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[13].sqldata = (void*)hkksjtts;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 27;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[14].sqldata = (void*)hkkdh;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[15].sqldata = (void*)hkkstdh;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 27;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[16].sqldata = (void*)hkkeddh;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[17].sqldata = (void*)tnsstdh;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[18].sqldata = (void*)tnseddh;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[19].sqltype = 496; sql_setdlist[19].sqllen = 4;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[19].sqldata = (void*)&hkkssknsu;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[20].sqltype = 496; sql_setdlist[20].sqllen = 4;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[20].sqldata = (void*)&hkkhrysu;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 13;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[21].sqldata = (void*)ssnmtfilid;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 3;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[22].sqldata = (void*)hkkjkflg;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 9;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[23].sqldata = (void*)hkkerrcode;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[24].sqltype = 500; sql_setdlist[24].sqllen = 2;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[24].sqldata = (void*)&kkirilotno;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 11;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[25].sqldata = (void*)hkksjymd;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[26].sqltype = 496; sql_setdlist[26].sqllen = 4;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[26].sqldata = (void*)&hkksjno;
#line 293 "ED203Hkkknri.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 293 "ED203Hkkknri.sqc"
      sqlasetdata(2,0,27,sql_setdlist,0L,0L);
    }
#line 293 "ED203Hkkknri.sqc"
  sqlacall((unsigned short)24,2,2,0,0L);
#line 293 "ED203Hkkknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 293 "ED203Hkkknri.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 293 "ED203Hkkknri.sqc"
  sqlastop(0L);
}

#line 293 "ED203Hkkknri.sqc"


printf("Update HRC_SQL_NORMAL\n");
    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 299 "ED203Hkkknri.sqc"

printf("Update HRC_SQL_NOT_FOUND\n");
    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 304 "ED203Hkkknri.sqc"

printf("Update %d-%s\n", sqlca.sqlcode, sqlca.sqlerrmc);
    return sqlca.sqlcode;
}
/** End of File *********************************************************/
