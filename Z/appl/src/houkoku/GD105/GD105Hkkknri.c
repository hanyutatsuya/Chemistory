static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,77,66,68,52,85,97,68,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,50,71,49,48,53,32,32,32,0,0,0,0,0,0,0,0,
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


#line 1 "GD105Hkkknri.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： GD105Hkkknri.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-03-06                    Create
 *  1.12     2006-09-04                    INTEC.INC エラー時保留件数更新
 **********************************************************************/
#include <stdio.h>

#include "GD105Hkkknri.h"
#include "bml_misc.h"
#include "bml_db.h"
#include "bml_dmm.h"

#include "bmllog.h"					// 1.06 ADD

#define ALLOC_UNIT		1


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 27 "GD105Hkkknri.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 32 "GD105Hkkknri.sqc"

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
	char    stsflnm[51];
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

#line 62 "GD105Hkkknri.sqc"



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
	DMM_SSTRING( stsflnm ),
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
 * ZdbHkkknriGD105SelectAll()
 *    HKKKNRI レコード全件取得
 * ■引数
 *    [O]  Hkkknri** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbHkkknriGD105SelectAll( Hkkknri** arrayOut, int* numOut )
{
    Hkkknri*    array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 119 "GD105Hkkknri.sqc"


    
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
		STSFLNM,
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
			( HKKJKN <> '7' AND HKKJKFLG = '0' )
		OR  ( HKKJKN = '8' AND HKKJKFLG = '3' )
		FOR READ ONLY;
*/

#line 157 "GD105Hkkknri.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 159 "GD105Hkkknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 159 "GD105Hkkknri.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 159 "GD105Hkkknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 159 "GD105Hkkknri.sqc"
  sqlastop(0L);
}

#line 159 "GD105Hkkknri.sqc"


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
			:stsflnm,
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
#line 193 "GD105Hkkknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 193 "GD105Hkkknri.sqc"
  sqlaaloc(3,29,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[29];
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[0].sqldata = (void*)hkksjymd;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[1].sqldata = (void*)&hkksjno;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[2].sqldata = (void*)&hkkkbn;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[3].sqldata = (void*)&hkkjkn;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[4].sqldata = (void*)knskisymd;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[5].sqldata = (void*)utkymd;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[6].sqldata = (void*)sriymd;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 17;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[7].sqldata = (void*)knsgrp;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 8;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[8].sqldata = (void*)kmkcd;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 5;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[9].sqldata = (void*)bskkbn;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 7;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[10].sqldata = (void*)bskgok;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 21;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[11].sqldata = (void*)hkkjknst;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 21;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[12].sqldata = (void*)hkkjkned;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 51;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[13].sqldata = (void*)stsflnm;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 3;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[14].sqldata = (void*)seccd;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 51;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[15].sqldata = (void*)hkkflnm;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 9;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[16].sqldata = (void*)hkksjtts;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[17].sqldata = (void*)hkkdh;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[18].sqldata = (void*)hkkstdh;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[19].sqldata = (void*)hkkeddh;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 27;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[20].sqldata = (void*)tnsstdh;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 27;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[21].sqldata = (void*)tnseddh;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[22].sqltype = 496; sql_setdlist[22].sqllen = 4;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[22].sqldata = (void*)&hkkssknsu;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[23].sqltype = 496; sql_setdlist[23].sqllen = 4;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[23].sqldata = (void*)&hkkhrysu;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 13;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[24].sqldata = (void*)ssnmtfilid;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 3;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[25].sqldata = (void*)hkkjkflg;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 9;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[26].sqldata = (void*)hkkerrcode;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[27].sqltype = 500; sql_setdlist[27].sqllen = 2;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[27].sqldata = (void*)&kkirilotno;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 27;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[28].sqldata = (void*)ksndh;
#line 193 "GD105Hkkknri.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 193 "GD105Hkkknri.sqc"
      sqlasetdata(3,0,29,sql_setdlist,0L,0L);
    }
#line 193 "GD105Hkkknri.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 193 "GD105Hkkknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 193 "GD105Hkkknri.sqc"
  sqlastop(0L);
}

#line 193 "GD105Hkkknri.sqc"


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
#line 208 "GD105Hkkknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 208 "GD105Hkkknri.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 208 "GD105Hkkknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 208 "GD105Hkkknri.sqc"
  sqlastop(0L);
}

#line 208 "GD105Hkkknri.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 216 "GD105Hkkknri.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbHkkknriGD105UpdateNormal()
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
long ZdbHkkknriGD105UpdateNormal( Hkkknri* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, HkkknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 240 "GD105Hkkknri.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 241 "GD105Hkkknri.sqc"


    
/*
EXEC SQL UPDATE HKKKNRI
    SET (
		STSFLNM,
		HKKFLNM,
		HKKSTDH,
		HKKEDDH,
		HKKSSKNSU,
		HKKHRYSU,
		SSNMTFILID,
		HKKJKFLG,
		KSNDH
    ) = (
		:stsflnm,
		:hkkflnm,
		:hkkstdh,
		:hkkeddh,
		:hkkssknsu,
		:hkkhrysu,
		:ssnmtfilid,
		:hkkjkflg,
		current timestamp
    ) WHERE
		HKKSJYMD = :hkksjymd AND
		HKKSJNO = :hkksjno;
*/

{
#line 266 "GD105Hkkknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 266 "GD105Hkkknri.sqc"
  sqlaaloc(2,10,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 51;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[0].sqldata = (void*)stsflnm;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 51;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[1].sqldata = (void*)hkkflnm;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 27;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[2].sqldata = (void*)hkkstdh;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 27;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[3].sqldata = (void*)hkkeddh;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[4].sqldata = (void*)&hkkssknsu;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[5].sqldata = (void*)&hkkhrysu;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 13;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[6].sqldata = (void*)ssnmtfilid;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[7].sqldata = (void*)hkkjkflg;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[8].sqldata = (void*)hkksjymd;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[9].sqldata = (void*)&hkksjno;
#line 266 "GD105Hkkknri.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 266 "GD105Hkkknri.sqc"
      sqlasetdata(2,0,10,sql_setdlist,0L,0L);
    }
#line 266 "GD105Hkkknri.sqc"
  sqlacall((unsigned short)24,2,2,0,0L);
#line 266 "GD105Hkkknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 266 "GD105Hkkknri.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 266 "GD105Hkkknri.sqc"
  sqlastop(0L);
}

#line 266 "GD105Hkkknri.sqc"


#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "ZdbHkkknriGD105UpdateNormal", __LINE__, EXEFLG_UPD, "00000000",
				"Update HRC_SQL_NORMAL" );
#endif

    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 276 "GD105Hkkknri.sqc"


	sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbHkkknriGD105UpdateNormal", __LINE__, EXEFLG_UPD, "020",
				"Update HRC_SQL_NOT_FOUND" );

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 284 "GD105Hkkknri.sqc"


	sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbHkkknriGD105UpdateNormal", __LINE__, EXEFLG_UPD, "020",
				"Update [%d-%s]", sqlca.sqlcode, sqlca.sqlerrmc );

    return sqlca.sqlcode;
}


/******************************************************************************
 * ZdbHkkknriGD105UpdateSts()
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
long ZdbHkkknriGD105UpdateSts( Hkkknri* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, HkkknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 313 "GD105Hkkknri.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 314 "GD105Hkkknri.sqc"


    
/*
EXEC SQL UPDATE HKKKNRI
    SET (
		HKKJKFLG,
		HKKERRCODE,
		HKKSSKNSU,
		HKKHRYSU,
		KSNDH
    ) = (
		:hkkjkflg,
		:hkkerrcode,
		:hkkssknsu,
		:hkkhrysu,
		current timestamp
    ) WHERE
		HKKSJYMD = :hkksjymd AND
		HKKSJNO = :hkksjno;
*/

{
#line 331 "GD105Hkkknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 331 "GD105Hkkknri.sqc"
  sqlaaloc(2,6,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 331 "GD105Hkkknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 331 "GD105Hkkknri.sqc"
      sql_setdlist[0].sqldata = (void*)hkkjkflg;
#line 331 "GD105Hkkknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 331 "GD105Hkkknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 9;
#line 331 "GD105Hkkknri.sqc"
      sql_setdlist[1].sqldata = (void*)hkkerrcode;
#line 331 "GD105Hkkknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 331 "GD105Hkkknri.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 331 "GD105Hkkknri.sqc"
      sql_setdlist[2].sqldata = (void*)&hkkssknsu;
#line 331 "GD105Hkkknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 331 "GD105Hkkknri.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 331 "GD105Hkkknri.sqc"
      sql_setdlist[3].sqldata = (void*)&hkkhrysu;
#line 331 "GD105Hkkknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 331 "GD105Hkkknri.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 331 "GD105Hkkknri.sqc"
      sql_setdlist[4].sqldata = (void*)hkksjymd;
#line 331 "GD105Hkkknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 331 "GD105Hkkknri.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 331 "GD105Hkkknri.sqc"
      sql_setdlist[5].sqldata = (void*)&hkksjno;
#line 331 "GD105Hkkknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 331 "GD105Hkkknri.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 331 "GD105Hkkknri.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 331 "GD105Hkkknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 331 "GD105Hkkknri.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 331 "GD105Hkkknri.sqc"
  sqlastop(0L);
}

#line 331 "GD105Hkkknri.sqc"


#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "ZdbHkkknriGD105UpdateSts", __LINE__, EXEFLG_UPD, "00000000",
				"Update HRC_SQL_NORMAL" );
#endif

    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 341 "GD105Hkkknri.sqc"


	sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbHkkknriGD105UpdateSts", __LINE__, EXEFLG_UPD, "020",
				"Update HRC_SQL_NOT_FOUND" );

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 349 "GD105Hkkknri.sqc"


	sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbHkkknriGD105UpdateSts", __LINE__, EXEFLG_UPD, "020",
				"Update [%d-%s]", sqlca.sqlcode, sqlca.sqlerrmc );

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
