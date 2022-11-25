static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,101,66,87,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,55,56,90,88,69,66,83,32,0,0,0,0,0,0,0,0,
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


#line 1 "Xebskflg.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Xebskflg.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Xebskflg.h"
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


#line 24 "Xebskflg.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Xebskflg.sqc"

	char    knskisymd[11];
	char    sriymd[11];
	char    kntno[21];
	char    kntketflg;
	sqlint32  smpcd;
	short   knssu;
	short   knssueda;
	char    flgsbt[3];
	char    bskkbn[11];
	char    bsklne[11];
	char    bskgok[6];
	char    bskmjno[6];
	char    asyrckid[11];
	short   asyrckpos;
	char    xeflg01;
	char    xeflg02;
	char    xeflg03;
	char    xeflg04;
	char    xeflg05;
	char    xeflg06;
	char    xeflg07;
	char    xeflg08;
	char    xeflg09;
	char    xeflg10;
	char    xeflg11;
	char    xeflg12;
	char    xeflg13;
	char    xeflg14;
	char    xeflg15;
	char    xeflg16;
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 61 "Xebskflg.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Xebskflg

BmlDMMInfo	XebskflgArray[] = {
	DMM_SDATE( knskisymd ),
	DMM_SDATE( sriymd ),
	DMM_SSTRING( kntno ),
	DMM_SCHAR( kntketflg ),
	DMM_SLONG( smpcd ),
	DMM_SSHORT( knssu ),
	DMM_SSHORT( knssueda ),
	DMM_SSTRING( flgsbt ),
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( bsklne ),
	DMM_SSTRING( bskgok ),
	DMM_SSTRING( bskmjno ),
	DMM_SSTRING( asyrckid ),
	DMM_SSHORT( asyrckpos ),
	DMM_SCHAR( xeflg01 ),
	DMM_SCHAR( xeflg02 ),
	DMM_SCHAR( xeflg03 ),
	DMM_SCHAR( xeflg04 ),
	DMM_SCHAR( xeflg05 ),
	DMM_SCHAR( xeflg06 ),
	DMM_SCHAR( xeflg07 ),
	DMM_SCHAR( xeflg08 ),
	DMM_SCHAR( xeflg09 ),
	DMM_SCHAR( xeflg10 ),
	DMM_SCHAR( xeflg11 ),
	DMM_SCHAR( xeflg12 ),
	DMM_SCHAR( xeflg13 ),
	DMM_SCHAR( xeflg14 ),
	DMM_SCHAR( xeflg15 ),
	DMM_SCHAR( xeflg16 ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbXebskflgSelectAll()
 *    XEBSKFLG レコード全件取得
 * ■引数
 *    [O]  Xebskflg** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbXebskflgSelectAll( Xebskflg** arrayOut, int* numOut )
{
    Xebskflg*   array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 120 "Xebskflg.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSKISYMD,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		SMPCD,
		KNSSU,
		KNSSUEDA,
		FLGSBT,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		BSKMJNO,
		ASYRCKID,
		ASYRCKPOS,
		XEFLG01,
		XEFLG02,
		XEFLG03,
		XEFLG04,
		XEFLG05,
		XEFLG06,
		XEFLG07,
		XEFLG08,
		XEFLG09,
		XEFLG10,
		XEFLG11,
		XEFLG12,
		XEFLG13,
		XEFLG14,
		XEFLG15,
		XEFLG16,
		KSNDH
    FROM
        XEBSKFLG FOR READ ONLY;
*/

#line 156 "Xebskflg.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 158 "Xebskflg.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 158 "Xebskflg.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 158 "Xebskflg.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 158 "Xebskflg.sqc"
  sqlastop(0L);
}

#line 158 "Xebskflg.sqc"


    while( 1 ) {
        Xebskflg* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knskisymd,
			:sriymd,
			:kntno,
			:kntketflg,
			:smpcd,
			:knssu,
			:knssueda,
			:flgsbt,
			:bskkbn,
			:bsklne,
			:bskgok,
			:bskmjno,
			:asyrckid,
			:asyrckpos,
			:xeflg01,
			:xeflg02,
			:xeflg03,
			:xeflg04,
			:xeflg05,
			:xeflg06,
			:xeflg07,
			:xeflg08,
			:xeflg09,
			:xeflg10,
			:xeflg11,
			:xeflg12,
			:xeflg13,
			:xeflg14,
			:xeflg15,
			:xeflg16,
			:ksndh;
*/

{
#line 194 "Xebskflg.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 194 "Xebskflg.sqc"
  sqlaaloc(3,31,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[31];
#line 194 "Xebskflg.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 194 "Xebskflg.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 194 "Xebskflg.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 194 "Xebskflg.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 194 "Xebskflg.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 194 "Xebskflg.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 194 "Xebskflg.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 194 "Xebskflg.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 194 "Xebskflg.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 194 "Xebskflg.sqc"
      sql_setdlist[4].sqldata = (void*)&smpcd;
#line 194 "Xebskflg.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 194 "Xebskflg.sqc"
      sql_setdlist[5].sqldata = (void*)&knssu;
#line 194 "Xebskflg.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 194 "Xebskflg.sqc"
      sql_setdlist[6].sqldata = (void*)&knssueda;
#line 194 "Xebskflg.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 194 "Xebskflg.sqc"
      sql_setdlist[7].sqldata = (void*)flgsbt;
#line 194 "Xebskflg.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 194 "Xebskflg.sqc"
      sql_setdlist[8].sqldata = (void*)bskkbn;
#line 194 "Xebskflg.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 194 "Xebskflg.sqc"
      sql_setdlist[9].sqldata = (void*)bsklne;
#line 194 "Xebskflg.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 6;
#line 194 "Xebskflg.sqc"
      sql_setdlist[10].sqldata = (void*)bskgok;
#line 194 "Xebskflg.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 6;
#line 194 "Xebskflg.sqc"
      sql_setdlist[11].sqldata = (void*)bskmjno;
#line 194 "Xebskflg.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 194 "Xebskflg.sqc"
      sql_setdlist[12].sqldata = (void*)asyrckid;
#line 194 "Xebskflg.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 194 "Xebskflg.sqc"
      sql_setdlist[13].sqldata = (void*)&asyrckpos;
#line 194 "Xebskflg.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 194 "Xebskflg.sqc"
      sql_setdlist[14].sqldata = (void*)&xeflg01;
#line 194 "Xebskflg.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[15].sqltype = 452; sql_setdlist[15].sqllen = 1;
#line 194 "Xebskflg.sqc"
      sql_setdlist[15].sqldata = (void*)&xeflg02;
#line 194 "Xebskflg.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 194 "Xebskflg.sqc"
      sql_setdlist[16].sqldata = (void*)&xeflg03;
#line 194 "Xebskflg.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 194 "Xebskflg.sqc"
      sql_setdlist[17].sqldata = (void*)&xeflg04;
#line 194 "Xebskflg.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 194 "Xebskflg.sqc"
      sql_setdlist[18].sqldata = (void*)&xeflg05;
#line 194 "Xebskflg.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 194 "Xebskflg.sqc"
      sql_setdlist[19].sqldata = (void*)&xeflg06;
#line 194 "Xebskflg.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 194 "Xebskflg.sqc"
      sql_setdlist[20].sqldata = (void*)&xeflg07;
#line 194 "Xebskflg.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 194 "Xebskflg.sqc"
      sql_setdlist[21].sqldata = (void*)&xeflg08;
#line 194 "Xebskflg.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 194 "Xebskflg.sqc"
      sql_setdlist[22].sqldata = (void*)&xeflg09;
#line 194 "Xebskflg.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 194 "Xebskflg.sqc"
      sql_setdlist[23].sqldata = (void*)&xeflg10;
#line 194 "Xebskflg.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 194 "Xebskflg.sqc"
      sql_setdlist[24].sqldata = (void*)&xeflg11;
#line 194 "Xebskflg.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 194 "Xebskflg.sqc"
      sql_setdlist[25].sqldata = (void*)&xeflg12;
#line 194 "Xebskflg.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 194 "Xebskflg.sqc"
      sql_setdlist[26].sqldata = (void*)&xeflg13;
#line 194 "Xebskflg.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 194 "Xebskflg.sqc"
      sql_setdlist[27].sqldata = (void*)&xeflg14;
#line 194 "Xebskflg.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 194 "Xebskflg.sqc"
      sql_setdlist[28].sqldata = (void*)&xeflg15;
#line 194 "Xebskflg.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 194 "Xebskflg.sqc"
      sql_setdlist[29].sqldata = (void*)&xeflg16;
#line 194 "Xebskflg.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 27;
#line 194 "Xebskflg.sqc"
      sql_setdlist[30].sqldata = (void*)ksndh;
#line 194 "Xebskflg.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 194 "Xebskflg.sqc"
      sqlasetdata(3,0,31,sql_setdlist,0L,0L);
    }
#line 194 "Xebskflg.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 194 "Xebskflg.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 194 "Xebskflg.sqc"
  sqlastop(0L);
}

#line 194 "Xebskflg.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Xebskflg*)ZbmlRealloc( array,
                                    sizeof( Xebskflg ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Xebskflg ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, XebskflgArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 209 "Xebskflg.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 209 "Xebskflg.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 209 "Xebskflg.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 209 "Xebskflg.sqc"
  sqlastop(0L);
}

#line 209 "Xebskflg.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 217 "Xebskflg.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbXebskflgSelectKey()
 *    XEBSKFLG レコードKey条件取得
 * ■引数
 *    [I]  Xebskflg* pKey       取得するレコードのキー
 *    [O]  Xebskflg** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbXebskflgSelectKey( Xebskflg* pKey, Xebskflg** arrayOut, int* numOut )
{
    Xebskflg*   array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, XebskflgArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 243 "Xebskflg.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSKISYMD,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		SMPCD,
		KNSSU,
		KNSSUEDA,
		FLGSBT,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		BSKMJNO,
		ASYRCKID,
		ASYRCKPOS,
		XEFLG01,
		XEFLG02,
		XEFLG03,
		XEFLG04,
		XEFLG05,
		XEFLG06,
		XEFLG07,
		XEFLG08,
		XEFLG09,
		XEFLG10,
		XEFLG11,
		XEFLG12,
		XEFLG13,
		XEFLG14,
		XEFLG15,
		XEFLG16,
		KSNDH
    FROM
        XEBSKFLG
    WHERE
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		SMPCD = :smpcd AND
		KNSSU = :knssu AND
		KNSSUEDA = :knssueda AND
		FLGSBT = :flgsbt FOR READ ONLY;
*/

#line 287 "Xebskflg.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 289 "Xebskflg.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 289 "Xebskflg.sqc"
  sqlaaloc(2,7,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 289 "Xebskflg.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 289 "Xebskflg.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 289 "Xebskflg.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 289 "Xebskflg.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 289 "Xebskflg.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 289 "Xebskflg.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 289 "Xebskflg.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 289 "Xebskflg.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 289 "Xebskflg.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 289 "Xebskflg.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 289 "Xebskflg.sqc"
      sql_setdlist[3].sqldata = (void*)&smpcd;
#line 289 "Xebskflg.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 289 "Xebskflg.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 289 "Xebskflg.sqc"
      sql_setdlist[4].sqldata = (void*)&knssu;
#line 289 "Xebskflg.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 289 "Xebskflg.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 289 "Xebskflg.sqc"
      sql_setdlist[5].sqldata = (void*)&knssueda;
#line 289 "Xebskflg.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 289 "Xebskflg.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 3;
#line 289 "Xebskflg.sqc"
      sql_setdlist[6].sqldata = (void*)flgsbt;
#line 289 "Xebskflg.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 289 "Xebskflg.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 289 "Xebskflg.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 289 "Xebskflg.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 289 "Xebskflg.sqc"
  sqlastop(0L);
}

#line 289 "Xebskflg.sqc"


    while( 1 ) {
        Xebskflg* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knskisymd,
			:sriymd,
			:kntno,
			:kntketflg,
			:smpcd,
			:knssu,
			:knssueda,
			:flgsbt,
			:bskkbn,
			:bsklne,
			:bskgok,
			:bskmjno,
			:asyrckid,
			:asyrckpos,
			:xeflg01,
			:xeflg02,
			:xeflg03,
			:xeflg04,
			:xeflg05,
			:xeflg06,
			:xeflg07,
			:xeflg08,
			:xeflg09,
			:xeflg10,
			:xeflg11,
			:xeflg12,
			:xeflg13,
			:xeflg14,
			:xeflg15,
			:xeflg16,
			:ksndh;
*/

{
#line 325 "Xebskflg.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 325 "Xebskflg.sqc"
  sqlaaloc(3,31,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[31];
#line 325 "Xebskflg.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 325 "Xebskflg.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 325 "Xebskflg.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 325 "Xebskflg.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 325 "Xebskflg.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 325 "Xebskflg.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 325 "Xebskflg.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 325 "Xebskflg.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 325 "Xebskflg.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 325 "Xebskflg.sqc"
      sql_setdlist[4].sqldata = (void*)&smpcd;
#line 325 "Xebskflg.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 325 "Xebskflg.sqc"
      sql_setdlist[5].sqldata = (void*)&knssu;
#line 325 "Xebskflg.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 325 "Xebskflg.sqc"
      sql_setdlist[6].sqldata = (void*)&knssueda;
#line 325 "Xebskflg.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 325 "Xebskflg.sqc"
      sql_setdlist[7].sqldata = (void*)flgsbt;
#line 325 "Xebskflg.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 325 "Xebskflg.sqc"
      sql_setdlist[8].sqldata = (void*)bskkbn;
#line 325 "Xebskflg.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 325 "Xebskflg.sqc"
      sql_setdlist[9].sqldata = (void*)bsklne;
#line 325 "Xebskflg.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 6;
#line 325 "Xebskflg.sqc"
      sql_setdlist[10].sqldata = (void*)bskgok;
#line 325 "Xebskflg.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 6;
#line 325 "Xebskflg.sqc"
      sql_setdlist[11].sqldata = (void*)bskmjno;
#line 325 "Xebskflg.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 325 "Xebskflg.sqc"
      sql_setdlist[12].sqldata = (void*)asyrckid;
#line 325 "Xebskflg.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 325 "Xebskflg.sqc"
      sql_setdlist[13].sqldata = (void*)&asyrckpos;
#line 325 "Xebskflg.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 325 "Xebskflg.sqc"
      sql_setdlist[14].sqldata = (void*)&xeflg01;
#line 325 "Xebskflg.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[15].sqltype = 452; sql_setdlist[15].sqllen = 1;
#line 325 "Xebskflg.sqc"
      sql_setdlist[15].sqldata = (void*)&xeflg02;
#line 325 "Xebskflg.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 325 "Xebskflg.sqc"
      sql_setdlist[16].sqldata = (void*)&xeflg03;
#line 325 "Xebskflg.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 325 "Xebskflg.sqc"
      sql_setdlist[17].sqldata = (void*)&xeflg04;
#line 325 "Xebskflg.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 325 "Xebskflg.sqc"
      sql_setdlist[18].sqldata = (void*)&xeflg05;
#line 325 "Xebskflg.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 325 "Xebskflg.sqc"
      sql_setdlist[19].sqldata = (void*)&xeflg06;
#line 325 "Xebskflg.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 325 "Xebskflg.sqc"
      sql_setdlist[20].sqldata = (void*)&xeflg07;
#line 325 "Xebskflg.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 325 "Xebskflg.sqc"
      sql_setdlist[21].sqldata = (void*)&xeflg08;
#line 325 "Xebskflg.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 325 "Xebskflg.sqc"
      sql_setdlist[22].sqldata = (void*)&xeflg09;
#line 325 "Xebskflg.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 325 "Xebskflg.sqc"
      sql_setdlist[23].sqldata = (void*)&xeflg10;
#line 325 "Xebskflg.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 325 "Xebskflg.sqc"
      sql_setdlist[24].sqldata = (void*)&xeflg11;
#line 325 "Xebskflg.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 325 "Xebskflg.sqc"
      sql_setdlist[25].sqldata = (void*)&xeflg12;
#line 325 "Xebskflg.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 325 "Xebskflg.sqc"
      sql_setdlist[26].sqldata = (void*)&xeflg13;
#line 325 "Xebskflg.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 325 "Xebskflg.sqc"
      sql_setdlist[27].sqldata = (void*)&xeflg14;
#line 325 "Xebskflg.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 325 "Xebskflg.sqc"
      sql_setdlist[28].sqldata = (void*)&xeflg15;
#line 325 "Xebskflg.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 325 "Xebskflg.sqc"
      sql_setdlist[29].sqldata = (void*)&xeflg16;
#line 325 "Xebskflg.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 27;
#line 325 "Xebskflg.sqc"
      sql_setdlist[30].sqldata = (void*)ksndh;
#line 325 "Xebskflg.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 325 "Xebskflg.sqc"
      sqlasetdata(3,0,31,sql_setdlist,0L,0L);
    }
#line 325 "Xebskflg.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 325 "Xebskflg.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 325 "Xebskflg.sqc"
  sqlastop(0L);
}

#line 325 "Xebskflg.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Xebskflg*)ZbmlRealloc( array,
                                    sizeof( Xebskflg ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Xebskflg ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, XebskflgArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 340 "Xebskflg.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 340 "Xebskflg.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 340 "Xebskflg.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 340 "Xebskflg.sqc"
  sqlastop(0L);
}

#line 340 "Xebskflg.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 348 "Xebskflg.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbXebskflgInsert()
 *    XEBSKFLG レコードを挿入する
 * ■引数
 *    [I]  Xebskflg* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbXebskflgInsert( Xebskflg* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, XebskflgArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 371 "Xebskflg.sqc"


    
/*
EXEC SQL INSERT INTO XEBSKFLG
    (
		KNSKISYMD,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		SMPCD,
		KNSSU,
		KNSSUEDA,
		FLGSBT,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		BSKMJNO,
		ASYRCKID,
		ASYRCKPOS,
		XEFLG01,
		XEFLG02,
		XEFLG03,
		XEFLG04,
		XEFLG05,
		XEFLG06,
		XEFLG07,
		XEFLG08,
		XEFLG09,
		XEFLG10,
		XEFLG11,
		XEFLG12,
		XEFLG13,
		XEFLG14,
		XEFLG15,
		XEFLG16,
		KSNDH
    ) VALUES (
		:knskisymd,
		:sriymd,
		:kntno,
		:kntketflg,
		:smpcd,
		:knssu,
		:knssueda,
		:flgsbt,
		:bskkbn,
		:bsklne,
		:bskgok,
		:bskmjno,
		:asyrckid,
		:asyrckpos,
		:xeflg01,
		:xeflg02,
		:xeflg03,
		:xeflg04,
		:xeflg05,
		:xeflg06,
		:xeflg07,
		:xeflg08,
		:xeflg09,
		:xeflg10,
		:xeflg11,
		:xeflg12,
		:xeflg13,
		:xeflg14,
		:xeflg15,
		:xeflg16,
		:ksndh
    );
*/

{
#line 438 "Xebskflg.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 438 "Xebskflg.sqc"
  sqlaaloc(2,31,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[31];
#line 438 "Xebskflg.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 438 "Xebskflg.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 438 "Xebskflg.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 438 "Xebskflg.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 438 "Xebskflg.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 438 "Xebskflg.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 438 "Xebskflg.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 438 "Xebskflg.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 438 "Xebskflg.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 438 "Xebskflg.sqc"
      sql_setdlist[4].sqldata = (void*)&smpcd;
#line 438 "Xebskflg.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 438 "Xebskflg.sqc"
      sql_setdlist[5].sqldata = (void*)&knssu;
#line 438 "Xebskflg.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 438 "Xebskflg.sqc"
      sql_setdlist[6].sqldata = (void*)&knssueda;
#line 438 "Xebskflg.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 438 "Xebskflg.sqc"
      sql_setdlist[7].sqldata = (void*)flgsbt;
#line 438 "Xebskflg.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 438 "Xebskflg.sqc"
      sql_setdlist[8].sqldata = (void*)bskkbn;
#line 438 "Xebskflg.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 438 "Xebskflg.sqc"
      sql_setdlist[9].sqldata = (void*)bsklne;
#line 438 "Xebskflg.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 6;
#line 438 "Xebskflg.sqc"
      sql_setdlist[10].sqldata = (void*)bskgok;
#line 438 "Xebskflg.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 6;
#line 438 "Xebskflg.sqc"
      sql_setdlist[11].sqldata = (void*)bskmjno;
#line 438 "Xebskflg.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 438 "Xebskflg.sqc"
      sql_setdlist[12].sqldata = (void*)asyrckid;
#line 438 "Xebskflg.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 438 "Xebskflg.sqc"
      sql_setdlist[13].sqldata = (void*)&asyrckpos;
#line 438 "Xebskflg.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 438 "Xebskflg.sqc"
      sql_setdlist[14].sqldata = (void*)&xeflg01;
#line 438 "Xebskflg.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[15].sqltype = 452; sql_setdlist[15].sqllen = 1;
#line 438 "Xebskflg.sqc"
      sql_setdlist[15].sqldata = (void*)&xeflg02;
#line 438 "Xebskflg.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 438 "Xebskflg.sqc"
      sql_setdlist[16].sqldata = (void*)&xeflg03;
#line 438 "Xebskflg.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 438 "Xebskflg.sqc"
      sql_setdlist[17].sqldata = (void*)&xeflg04;
#line 438 "Xebskflg.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 438 "Xebskflg.sqc"
      sql_setdlist[18].sqldata = (void*)&xeflg05;
#line 438 "Xebskflg.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 438 "Xebskflg.sqc"
      sql_setdlist[19].sqldata = (void*)&xeflg06;
#line 438 "Xebskflg.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 438 "Xebskflg.sqc"
      sql_setdlist[20].sqldata = (void*)&xeflg07;
#line 438 "Xebskflg.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 438 "Xebskflg.sqc"
      sql_setdlist[21].sqldata = (void*)&xeflg08;
#line 438 "Xebskflg.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 438 "Xebskflg.sqc"
      sql_setdlist[22].sqldata = (void*)&xeflg09;
#line 438 "Xebskflg.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 438 "Xebskflg.sqc"
      sql_setdlist[23].sqldata = (void*)&xeflg10;
#line 438 "Xebskflg.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 438 "Xebskflg.sqc"
      sql_setdlist[24].sqldata = (void*)&xeflg11;
#line 438 "Xebskflg.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 438 "Xebskflg.sqc"
      sql_setdlist[25].sqldata = (void*)&xeflg12;
#line 438 "Xebskflg.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 438 "Xebskflg.sqc"
      sql_setdlist[26].sqldata = (void*)&xeflg13;
#line 438 "Xebskflg.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 438 "Xebskflg.sqc"
      sql_setdlist[27].sqldata = (void*)&xeflg14;
#line 438 "Xebskflg.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 438 "Xebskflg.sqc"
      sql_setdlist[28].sqldata = (void*)&xeflg15;
#line 438 "Xebskflg.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 438 "Xebskflg.sqc"
      sql_setdlist[29].sqldata = (void*)&xeflg16;
#line 438 "Xebskflg.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 27;
#line 438 "Xebskflg.sqc"
      sql_setdlist[30].sqldata = (void*)ksndh;
#line 438 "Xebskflg.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 438 "Xebskflg.sqc"
      sqlasetdata(2,0,31,sql_setdlist,0L,0L);
    }
#line 438 "Xebskflg.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 438 "Xebskflg.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 438 "Xebskflg.sqc"
  sqlastop(0L);
}

#line 438 "Xebskflg.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 443 "Xebskflg.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbXebskflgUpdate()
 *    XEBSKFLG レコードを更新する
 * ■引数
 *    [I]  Xebskflg* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbXebskflgUpdate( Xebskflg* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, XebskflgArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 467 "Xebskflg.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 468 "Xebskflg.sqc"


    
/*
EXEC SQL UPDATE XEBSKFLG
    SET (
		KNTKETFLG,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		BSKMJNO,
		ASYRCKID,
		ASYRCKPOS,
		XEFLG01,
		XEFLG02,
		XEFLG03,
		XEFLG04,
		XEFLG05,
		XEFLG06,
		XEFLG07,
		XEFLG08,
		XEFLG09,
		XEFLG10,
		XEFLG11,
		XEFLG12,
		XEFLG13,
		XEFLG14,
		XEFLG15,
		XEFLG16,
		KSNDH
    ) = (
		:kntketflg,
		:bskkbn,
		:bsklne,
		:bskgok,
		:bskmjno,
		:asyrckid,
		:asyrckpos,
		:xeflg01,
		:xeflg02,
		:xeflg03,
		:xeflg04,
		:xeflg05,
		:xeflg06,
		:xeflg07,
		:xeflg08,
		:xeflg09,
		:xeflg10,
		:xeflg11,
		:xeflg12,
		:xeflg13,
		:xeflg14,
		:xeflg15,
		:xeflg16,
		:ksndh
    ) WHERE
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		SMPCD = :smpcd AND
		KNSSU = :knssu AND
		KNSSUEDA = :knssueda AND
		FLGSBT = :flgsbt;
*/

{
#line 528 "Xebskflg.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 528 "Xebskflg.sqc"
  sqlaaloc(2,31,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[31];
#line 528 "Xebskflg.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 528 "Xebskflg.sqc"
      sql_setdlist[0].sqldata = (void*)&kntketflg;
#line 528 "Xebskflg.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 528 "Xebskflg.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 528 "Xebskflg.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 528 "Xebskflg.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 528 "Xebskflg.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 6;
#line 528 "Xebskflg.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 528 "Xebskflg.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 6;
#line 528 "Xebskflg.sqc"
      sql_setdlist[4].sqldata = (void*)bskmjno;
#line 528 "Xebskflg.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 528 "Xebskflg.sqc"
      sql_setdlist[5].sqldata = (void*)asyrckid;
#line 528 "Xebskflg.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 528 "Xebskflg.sqc"
      sql_setdlist[6].sqldata = (void*)&asyrckpos;
#line 528 "Xebskflg.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 528 "Xebskflg.sqc"
      sql_setdlist[7].sqldata = (void*)&xeflg01;
#line 528 "Xebskflg.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 528 "Xebskflg.sqc"
      sql_setdlist[8].sqldata = (void*)&xeflg02;
#line 528 "Xebskflg.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 528 "Xebskflg.sqc"
      sql_setdlist[9].sqldata = (void*)&xeflg03;
#line 528 "Xebskflg.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 528 "Xebskflg.sqc"
      sql_setdlist[10].sqldata = (void*)&xeflg04;
#line 528 "Xebskflg.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 528 "Xebskflg.sqc"
      sql_setdlist[11].sqldata = (void*)&xeflg05;
#line 528 "Xebskflg.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[12].sqltype = 452; sql_setdlist[12].sqllen = 1;
#line 528 "Xebskflg.sqc"
      sql_setdlist[12].sqldata = (void*)&xeflg06;
#line 528 "Xebskflg.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 528 "Xebskflg.sqc"
      sql_setdlist[13].sqldata = (void*)&xeflg07;
#line 528 "Xebskflg.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 528 "Xebskflg.sqc"
      sql_setdlist[14].sqldata = (void*)&xeflg08;
#line 528 "Xebskflg.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[15].sqltype = 452; sql_setdlist[15].sqllen = 1;
#line 528 "Xebskflg.sqc"
      sql_setdlist[15].sqldata = (void*)&xeflg09;
#line 528 "Xebskflg.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 528 "Xebskflg.sqc"
      sql_setdlist[16].sqldata = (void*)&xeflg10;
#line 528 "Xebskflg.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 528 "Xebskflg.sqc"
      sql_setdlist[17].sqldata = (void*)&xeflg11;
#line 528 "Xebskflg.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 528 "Xebskflg.sqc"
      sql_setdlist[18].sqldata = (void*)&xeflg12;
#line 528 "Xebskflg.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 528 "Xebskflg.sqc"
      sql_setdlist[19].sqldata = (void*)&xeflg13;
#line 528 "Xebskflg.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 528 "Xebskflg.sqc"
      sql_setdlist[20].sqldata = (void*)&xeflg14;
#line 528 "Xebskflg.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 528 "Xebskflg.sqc"
      sql_setdlist[21].sqldata = (void*)&xeflg15;
#line 528 "Xebskflg.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 528 "Xebskflg.sqc"
      sql_setdlist[22].sqldata = (void*)&xeflg16;
#line 528 "Xebskflg.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 27;
#line 528 "Xebskflg.sqc"
      sql_setdlist[23].sqldata = (void*)ksndh;
#line 528 "Xebskflg.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 11;
#line 528 "Xebskflg.sqc"
      sql_setdlist[24].sqldata = (void*)knskisymd;
#line 528 "Xebskflg.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 11;
#line 528 "Xebskflg.sqc"
      sql_setdlist[25].sqldata = (void*)sriymd;
#line 528 "Xebskflg.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 21;
#line 528 "Xebskflg.sqc"
      sql_setdlist[26].sqldata = (void*)kntno;
#line 528 "Xebskflg.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[27].sqltype = 496; sql_setdlist[27].sqllen = 4;
#line 528 "Xebskflg.sqc"
      sql_setdlist[27].sqldata = (void*)&smpcd;
#line 528 "Xebskflg.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[28].sqltype = 500; sql_setdlist[28].sqllen = 2;
#line 528 "Xebskflg.sqc"
      sql_setdlist[28].sqldata = (void*)&knssu;
#line 528 "Xebskflg.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[29].sqltype = 500; sql_setdlist[29].sqllen = 2;
#line 528 "Xebskflg.sqc"
      sql_setdlist[29].sqldata = (void*)&knssueda;
#line 528 "Xebskflg.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 3;
#line 528 "Xebskflg.sqc"
      sql_setdlist[30].sqldata = (void*)flgsbt;
#line 528 "Xebskflg.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 528 "Xebskflg.sqc"
      sqlasetdata(2,0,31,sql_setdlist,0L,0L);
    }
#line 528 "Xebskflg.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 528 "Xebskflg.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 528 "Xebskflg.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 528 "Xebskflg.sqc"
  sqlastop(0L);
}

#line 528 "Xebskflg.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 533 "Xebskflg.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 537 "Xebskflg.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbXebskflgDelete()
 *    XEBSKFLG レコードを削除する
 * ■引数
 *    [I]  Xebskflg* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbXebskflgDelete( Xebskflg* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, XebskflgArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 561 "Xebskflg.sqc"


    
/*
EXEC SQL DELETE FROM XEBSKFLG
    WHERE
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		SMPCD = :smpcd AND
		KNSSU = :knssu AND
		KNSSUEDA = :knssueda AND
		FLGSBT = :flgsbt;
*/

{
#line 571 "Xebskflg.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 571 "Xebskflg.sqc"
  sqlaaloc(2,7,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 571 "Xebskflg.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 571 "Xebskflg.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 571 "Xebskflg.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 571 "Xebskflg.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 571 "Xebskflg.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 571 "Xebskflg.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 571 "Xebskflg.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 571 "Xebskflg.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 571 "Xebskflg.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 571 "Xebskflg.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 571 "Xebskflg.sqc"
      sql_setdlist[3].sqldata = (void*)&smpcd;
#line 571 "Xebskflg.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 571 "Xebskflg.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 571 "Xebskflg.sqc"
      sql_setdlist[4].sqldata = (void*)&knssu;
#line 571 "Xebskflg.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 571 "Xebskflg.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 571 "Xebskflg.sqc"
      sql_setdlist[5].sqldata = (void*)&knssueda;
#line 571 "Xebskflg.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 571 "Xebskflg.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 3;
#line 571 "Xebskflg.sqc"
      sql_setdlist[6].sqldata = (void*)flgsbt;
#line 571 "Xebskflg.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 571 "Xebskflg.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 571 "Xebskflg.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 571 "Xebskflg.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 571 "Xebskflg.sqc"
  sqlastop(0L);
}

#line 571 "Xebskflg.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 576 "Xebskflg.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
