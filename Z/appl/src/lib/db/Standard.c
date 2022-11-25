static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,68,65,87,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,54,56,90,83,84,65,78,32,0,0,0,0,0,0,0,0,
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


#line 1 "Standard.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Standard.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Standard.h"
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


#line 24 "Standard.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Standard.sqc"

	char    knskisymd[11];
	char    bskkbn[11];
	char    bsklne[11];
	char    bskgok[7];
	char    bskmjno[6];
	char    knsgrp[11];
	sqlint32  bthno;
	short   stdsbt;
	char    asyrckid[11];
	short   asyrckpos;
	sqlint32  knsseq;
	sqlint32  bskseq;
	char    lotno[11];
	char    sktti[21];
	sqlint32  ktgrt;
	char    sktdh[27];
	char    stdjkflg;
	char    hkkokflg;
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 49 "Standard.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Standard

BmlDMMInfo	StandardArray[] = {
	DMM_SDATE( knskisymd ),
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( bsklne ),
	DMM_SSTRING( bskgok ),
	DMM_SSTRING( bskmjno ),
	DMM_SSTRING( knsgrp ),
	DMM_SLONG( bthno ),
	DMM_SSHORT( stdsbt ),
	DMM_SSTRING( asyrckid ),
	DMM_SSHORT( asyrckpos ),
	DMM_SLONG( knsseq ),
	DMM_SLONG( bskseq ),
	DMM_SSTRING( lotno ),
	DMM_SSTRING( sktti ),
	DMM_SLONG( ktgrt ),
	DMM_STIMESTAMP( sktdh ),
	DMM_SCHAR( stdjkflg ),
	DMM_SCHAR( hkkokflg ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbStandardSelectAll()
 *    STANDARD レコード全件取得
 * ■引数
 *    [O]  Standard** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbStandardSelectAll( Standard** arrayOut, int* numOut )
{
    Standard*   array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 96 "Standard.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSKISYMD,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		BSKMJNO,
		KNSGRP,
		BTHNO,
		STDSBT,
		ASYRCKID,
		ASYRCKPOS,
		KNSSEQ,
		BSKSEQ,
		LOTNO,
		SKTTI,
		KTGRT,
		SKTDH,
		STDJKFLG,
		HKKOKFLG,
		KSNDH
    FROM
        STANDARD FOR READ ONLY;
*/

#line 120 "Standard.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 122 "Standard.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 122 "Standard.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 122 "Standard.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 122 "Standard.sqc"
  sqlastop(0L);
}

#line 122 "Standard.sqc"


    while( 1 ) {
        Standard* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knskisymd,
			:bskkbn,
			:bsklne,
			:bskgok,
			:bskmjno,
			:knsgrp,
			:bthno,
			:stdsbt,
			:asyrckid,
			:asyrckpos,
			:knsseq,
			:bskseq,
			:lotno,
			:sktti,
			:ktgrt,
			:sktdh,
			:stdjkflg,
			:hkkokflg,
			:ksndh;
*/

{
#line 146 "Standard.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 146 "Standard.sqc"
  sqlaaloc(3,19,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[19];
#line 146 "Standard.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 146 "Standard.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 146 "Standard.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 146 "Standard.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 146 "Standard.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 146 "Standard.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 146 "Standard.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 146 "Standard.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 146 "Standard.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 146 "Standard.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 7;
#line 146 "Standard.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 146 "Standard.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 146 "Standard.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 6;
#line 146 "Standard.sqc"
      sql_setdlist[4].sqldata = (void*)bskmjno;
#line 146 "Standard.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 146 "Standard.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 146 "Standard.sqc"
      sql_setdlist[5].sqldata = (void*)knsgrp;
#line 146 "Standard.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 146 "Standard.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 146 "Standard.sqc"
      sql_setdlist[6].sqldata = (void*)&bthno;
#line 146 "Standard.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 146 "Standard.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 146 "Standard.sqc"
      sql_setdlist[7].sqldata = (void*)&stdsbt;
#line 146 "Standard.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 146 "Standard.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 146 "Standard.sqc"
      sql_setdlist[8].sqldata = (void*)asyrckid;
#line 146 "Standard.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 146 "Standard.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 146 "Standard.sqc"
      sql_setdlist[9].sqldata = (void*)&asyrckpos;
#line 146 "Standard.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 146 "Standard.sqc"
      sql_setdlist[10].sqltype = 496; sql_setdlist[10].sqllen = 4;
#line 146 "Standard.sqc"
      sql_setdlist[10].sqldata = (void*)&knsseq;
#line 146 "Standard.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 146 "Standard.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 146 "Standard.sqc"
      sql_setdlist[11].sqldata = (void*)&bskseq;
#line 146 "Standard.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 146 "Standard.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 146 "Standard.sqc"
      sql_setdlist[12].sqldata = (void*)lotno;
#line 146 "Standard.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 146 "Standard.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 146 "Standard.sqc"
      sql_setdlist[13].sqldata = (void*)sktti;
#line 146 "Standard.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 146 "Standard.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 146 "Standard.sqc"
      sql_setdlist[14].sqldata = (void*)&ktgrt;
#line 146 "Standard.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 146 "Standard.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 146 "Standard.sqc"
      sql_setdlist[15].sqldata = (void*)sktdh;
#line 146 "Standard.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 146 "Standard.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 146 "Standard.sqc"
      sql_setdlist[16].sqldata = (void*)&stdjkflg;
#line 146 "Standard.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 146 "Standard.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 146 "Standard.sqc"
      sql_setdlist[17].sqldata = (void*)&hkkokflg;
#line 146 "Standard.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 146 "Standard.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 146 "Standard.sqc"
      sql_setdlist[18].sqldata = (void*)ksndh;
#line 146 "Standard.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 146 "Standard.sqc"
      sqlasetdata(3,0,19,sql_setdlist,0L,0L);
    }
#line 146 "Standard.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 146 "Standard.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 146 "Standard.sqc"
  sqlastop(0L);
}

#line 146 "Standard.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Standard*)ZbmlRealloc( array,
                                    sizeof( Standard ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Standard ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, StandardArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 161 "Standard.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 161 "Standard.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 161 "Standard.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 161 "Standard.sqc"
  sqlastop(0L);
}

#line 161 "Standard.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 169 "Standard.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbStandardSelectKey()
 *    STANDARD レコードKey条件取得
 * ■引数
 *    [I]  Standard* pKey       取得するレコードのキー
 *    [O]  Standard** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbStandardSelectKey( Standard* pKey, Standard** arrayOut, int* numOut )
{
    Standard*   array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, StandardArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 195 "Standard.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSKISYMD,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		BSKMJNO,
		KNSGRP,
		BTHNO,
		STDSBT,
		ASYRCKID,
		ASYRCKPOS,
		KNSSEQ,
		BSKSEQ,
		LOTNO,
		SKTTI,
		KTGRT,
		SKTDH,
		STDJKFLG,
		HKKOKFLG,
		KSNDH
    FROM
        STANDARD
    WHERE
		KNSKISYMD = :knskisymd AND
		BSKKBN = :bskkbn AND
		BSKLNE = :bsklne AND
		BSKGOK = :bskgok AND
		BSKMJNO = :bskmjno AND
		KNSGRP         = :knsgrp         AND
		BTHNO = :bthno FOR READ ONLY;
*/

#line 227 "Standard.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 229 "Standard.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 229 "Standard.sqc"
  sqlaaloc(2,7,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 229 "Standard.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 229 "Standard.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 229 "Standard.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 229 "Standard.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 229 "Standard.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 229 "Standard.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 229 "Standard.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 229 "Standard.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 229 "Standard.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 229 "Standard.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 7;
#line 229 "Standard.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 229 "Standard.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 229 "Standard.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 6;
#line 229 "Standard.sqc"
      sql_setdlist[4].sqldata = (void*)bskmjno;
#line 229 "Standard.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 229 "Standard.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 229 "Standard.sqc"
      sql_setdlist[5].sqldata = (void*)knsgrp;
#line 229 "Standard.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 229 "Standard.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 229 "Standard.sqc"
      sql_setdlist[6].sqldata = (void*)&bthno;
#line 229 "Standard.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 229 "Standard.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 229 "Standard.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 229 "Standard.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 229 "Standard.sqc"
  sqlastop(0L);
}

#line 229 "Standard.sqc"


    while( 1 ) {
        Standard* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knskisymd,
			:bskkbn,
			:bsklne,
			:bskgok,
			:bskmjno,
			:knsgrp,
			:bthno,
			:stdsbt,
			:asyrckid,
			:asyrckpos,
			:knsseq,
			:bskseq,
			:lotno,
			:sktti,
			:ktgrt,
			:sktdh,
			:stdjkflg,
			:hkkokflg,
			:ksndh;
*/

{
#line 253 "Standard.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 253 "Standard.sqc"
  sqlaaloc(3,19,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[19];
#line 253 "Standard.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 253 "Standard.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 253 "Standard.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 253 "Standard.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 253 "Standard.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 253 "Standard.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 253 "Standard.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 253 "Standard.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 253 "Standard.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 253 "Standard.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 7;
#line 253 "Standard.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 253 "Standard.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 253 "Standard.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 6;
#line 253 "Standard.sqc"
      sql_setdlist[4].sqldata = (void*)bskmjno;
#line 253 "Standard.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 253 "Standard.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 253 "Standard.sqc"
      sql_setdlist[5].sqldata = (void*)knsgrp;
#line 253 "Standard.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 253 "Standard.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 253 "Standard.sqc"
      sql_setdlist[6].sqldata = (void*)&bthno;
#line 253 "Standard.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 253 "Standard.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 253 "Standard.sqc"
      sql_setdlist[7].sqldata = (void*)&stdsbt;
#line 253 "Standard.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 253 "Standard.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 253 "Standard.sqc"
      sql_setdlist[8].sqldata = (void*)asyrckid;
#line 253 "Standard.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 253 "Standard.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 253 "Standard.sqc"
      sql_setdlist[9].sqldata = (void*)&asyrckpos;
#line 253 "Standard.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 253 "Standard.sqc"
      sql_setdlist[10].sqltype = 496; sql_setdlist[10].sqllen = 4;
#line 253 "Standard.sqc"
      sql_setdlist[10].sqldata = (void*)&knsseq;
#line 253 "Standard.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 253 "Standard.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 253 "Standard.sqc"
      sql_setdlist[11].sqldata = (void*)&bskseq;
#line 253 "Standard.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 253 "Standard.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 253 "Standard.sqc"
      sql_setdlist[12].sqldata = (void*)lotno;
#line 253 "Standard.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 253 "Standard.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 253 "Standard.sqc"
      sql_setdlist[13].sqldata = (void*)sktti;
#line 253 "Standard.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 253 "Standard.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 253 "Standard.sqc"
      sql_setdlist[14].sqldata = (void*)&ktgrt;
#line 253 "Standard.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 253 "Standard.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 253 "Standard.sqc"
      sql_setdlist[15].sqldata = (void*)sktdh;
#line 253 "Standard.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 253 "Standard.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 253 "Standard.sqc"
      sql_setdlist[16].sqldata = (void*)&stdjkflg;
#line 253 "Standard.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 253 "Standard.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 253 "Standard.sqc"
      sql_setdlist[17].sqldata = (void*)&hkkokflg;
#line 253 "Standard.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 253 "Standard.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 253 "Standard.sqc"
      sql_setdlist[18].sqldata = (void*)ksndh;
#line 253 "Standard.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 253 "Standard.sqc"
      sqlasetdata(3,0,19,sql_setdlist,0L,0L);
    }
#line 253 "Standard.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 253 "Standard.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 253 "Standard.sqc"
  sqlastop(0L);
}

#line 253 "Standard.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Standard*)ZbmlRealloc( array,
                                    sizeof( Standard ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Standard ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, StandardArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 268 "Standard.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 268 "Standard.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 268 "Standard.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 268 "Standard.sqc"
  sqlastop(0L);
}

#line 268 "Standard.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 276 "Standard.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbStandardInsert()
 *    STANDARD レコードを挿入する
 * ■引数
 *    [I]  Standard* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbStandardInsert( Standard* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, StandardArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 299 "Standard.sqc"


    
/*
EXEC SQL INSERT INTO STANDARD
    (
		KNSKISYMD,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		BSKMJNO,
		KNSGRP,
		BTHNO,
		STDSBT,
		ASYRCKID,
		ASYRCKPOS,
		KNSSEQ,
		BSKSEQ,
		LOTNO,
		SKTTI,
		KTGRT,
		SKTDH,
		STDJKFLG,
		HKKOKFLG,
		KSNDH
    ) VALUES (
		:knskisymd,
		:bskkbn,
		:bsklne,
		:bskgok,
		:bskmjno,
		:knsgrp,
		:bthno,
		:stdsbt,
		:asyrckid,
		:asyrckpos,
		:knsseq,
		:bskseq,
		:lotno,
		:sktti,
		:ktgrt,
		:sktdh,
		:stdjkflg,
		:hkkokflg,
		:ksndh
    );
*/

{
#line 342 "Standard.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 342 "Standard.sqc"
  sqlaaloc(2,19,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[19];
#line 342 "Standard.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 342 "Standard.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 342 "Standard.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 342 "Standard.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 342 "Standard.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 342 "Standard.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 342 "Standard.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 342 "Standard.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 342 "Standard.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 342 "Standard.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 7;
#line 342 "Standard.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 342 "Standard.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 342 "Standard.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 6;
#line 342 "Standard.sqc"
      sql_setdlist[4].sqldata = (void*)bskmjno;
#line 342 "Standard.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 342 "Standard.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 342 "Standard.sqc"
      sql_setdlist[5].sqldata = (void*)knsgrp;
#line 342 "Standard.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 342 "Standard.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 342 "Standard.sqc"
      sql_setdlist[6].sqldata = (void*)&bthno;
#line 342 "Standard.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 342 "Standard.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 342 "Standard.sqc"
      sql_setdlist[7].sqldata = (void*)&stdsbt;
#line 342 "Standard.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 342 "Standard.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 342 "Standard.sqc"
      sql_setdlist[8].sqldata = (void*)asyrckid;
#line 342 "Standard.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 342 "Standard.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 342 "Standard.sqc"
      sql_setdlist[9].sqldata = (void*)&asyrckpos;
#line 342 "Standard.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 342 "Standard.sqc"
      sql_setdlist[10].sqltype = 496; sql_setdlist[10].sqllen = 4;
#line 342 "Standard.sqc"
      sql_setdlist[10].sqldata = (void*)&knsseq;
#line 342 "Standard.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 342 "Standard.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 342 "Standard.sqc"
      sql_setdlist[11].sqldata = (void*)&bskseq;
#line 342 "Standard.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 342 "Standard.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 342 "Standard.sqc"
      sql_setdlist[12].sqldata = (void*)lotno;
#line 342 "Standard.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 342 "Standard.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 342 "Standard.sqc"
      sql_setdlist[13].sqldata = (void*)sktti;
#line 342 "Standard.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 342 "Standard.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 342 "Standard.sqc"
      sql_setdlist[14].sqldata = (void*)&ktgrt;
#line 342 "Standard.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 342 "Standard.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 342 "Standard.sqc"
      sql_setdlist[15].sqldata = (void*)sktdh;
#line 342 "Standard.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 342 "Standard.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 342 "Standard.sqc"
      sql_setdlist[16].sqldata = (void*)&stdjkflg;
#line 342 "Standard.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 342 "Standard.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 342 "Standard.sqc"
      sql_setdlist[17].sqldata = (void*)&hkkokflg;
#line 342 "Standard.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 342 "Standard.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 342 "Standard.sqc"
      sql_setdlist[18].sqldata = (void*)ksndh;
#line 342 "Standard.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 342 "Standard.sqc"
      sqlasetdata(2,0,19,sql_setdlist,0L,0L);
    }
#line 342 "Standard.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 342 "Standard.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 342 "Standard.sqc"
  sqlastop(0L);
}

#line 342 "Standard.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 347 "Standard.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbStandardUpdate()
 *    STANDARD レコードを更新する
 * ■引数
 *    [I]  Standard* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbStandardUpdate( Standard* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, StandardArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 371 "Standard.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 372 "Standard.sqc"


    
/*
EXEC SQL UPDATE STANDARD
    SET (
		STDSBT,
		ASYRCKID,
		ASYRCKPOS,
		KNSSEQ,
		BSKSEQ,
		LOTNO,
		SKTTI,
		KTGRT,
		SKTDH,
		STDJKFLG,
		HKKOKFLG,
		KSNDH
    ) = (
		:stdsbt,
		:asyrckid,
		:asyrckpos,
		:knsseq,
		:bskseq,
		:lotno,
		:sktti,
		:ktgrt,
		:sktdh,
		:stdjkflg,
		:hkkokflg,
		:ksndh
    ) WHERE
		KNSKISYMD = :knskisymd AND
		BSKKBN = :bskkbn AND
		BSKLNE = :bsklne AND
		BSKGOK = :bskgok AND
		BSKMJNO = :bskmjno AND
		KNSGRP         = :knsgrp         AND
		BTHNO = :bthno;
*/

{
#line 408 "Standard.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 408 "Standard.sqc"
  sqlaaloc(2,19,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[19];
#line 408 "Standard.sqc"
      sql_setdlist[0].sqltype = 500; sql_setdlist[0].sqllen = 2;
#line 408 "Standard.sqc"
      sql_setdlist[0].sqldata = (void*)&stdsbt;
#line 408 "Standard.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 408 "Standard.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 408 "Standard.sqc"
      sql_setdlist[1].sqldata = (void*)asyrckid;
#line 408 "Standard.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 408 "Standard.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 408 "Standard.sqc"
      sql_setdlist[2].sqldata = (void*)&asyrckpos;
#line 408 "Standard.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 408 "Standard.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 408 "Standard.sqc"
      sql_setdlist[3].sqldata = (void*)&knsseq;
#line 408 "Standard.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 408 "Standard.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 408 "Standard.sqc"
      sql_setdlist[4].sqldata = (void*)&bskseq;
#line 408 "Standard.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 408 "Standard.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 408 "Standard.sqc"
      sql_setdlist[5].sqldata = (void*)lotno;
#line 408 "Standard.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 408 "Standard.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 21;
#line 408 "Standard.sqc"
      sql_setdlist[6].sqldata = (void*)sktti;
#line 408 "Standard.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 408 "Standard.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 408 "Standard.sqc"
      sql_setdlist[7].sqldata = (void*)&ktgrt;
#line 408 "Standard.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 408 "Standard.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 408 "Standard.sqc"
      sql_setdlist[8].sqldata = (void*)sktdh;
#line 408 "Standard.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 408 "Standard.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 408 "Standard.sqc"
      sql_setdlist[9].sqldata = (void*)&stdjkflg;
#line 408 "Standard.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 408 "Standard.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 408 "Standard.sqc"
      sql_setdlist[10].sqldata = (void*)&hkkokflg;
#line 408 "Standard.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 408 "Standard.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 27;
#line 408 "Standard.sqc"
      sql_setdlist[11].sqldata = (void*)ksndh;
#line 408 "Standard.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 408 "Standard.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 408 "Standard.sqc"
      sql_setdlist[12].sqldata = (void*)knskisymd;
#line 408 "Standard.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 408 "Standard.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 408 "Standard.sqc"
      sql_setdlist[13].sqldata = (void*)bskkbn;
#line 408 "Standard.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 408 "Standard.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 11;
#line 408 "Standard.sqc"
      sql_setdlist[14].sqldata = (void*)bsklne;
#line 408 "Standard.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 408 "Standard.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 7;
#line 408 "Standard.sqc"
      sql_setdlist[15].sqldata = (void*)bskgok;
#line 408 "Standard.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 408 "Standard.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 6;
#line 408 "Standard.sqc"
      sql_setdlist[16].sqldata = (void*)bskmjno;
#line 408 "Standard.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 408 "Standard.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 11;
#line 408 "Standard.sqc"
      sql_setdlist[17].sqldata = (void*)knsgrp;
#line 408 "Standard.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 408 "Standard.sqc"
      sql_setdlist[18].sqltype = 496; sql_setdlist[18].sqllen = 4;
#line 408 "Standard.sqc"
      sql_setdlist[18].sqldata = (void*)&bthno;
#line 408 "Standard.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 408 "Standard.sqc"
      sqlasetdata(2,0,19,sql_setdlist,0L,0L);
    }
#line 408 "Standard.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 408 "Standard.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 408 "Standard.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 408 "Standard.sqc"
  sqlastop(0L);
}

#line 408 "Standard.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 413 "Standard.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 417 "Standard.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbStandardDelete()
 *    STANDARD レコードを削除する
 * ■引数
 *    [I]  Standard* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbStandardDelete( Standard* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, StandardArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 441 "Standard.sqc"


    
/*
EXEC SQL DELETE FROM STANDARD
    WHERE
		KNSKISYMD = :knskisymd AND
		BSKKBN = :bskkbn AND
		BSKLNE = :bsklne AND
		BSKGOK = :bskgok AND
		BSKMJNO = :bskmjno AND
		KNSGRP         = :knsgrp         AND
		BTHNO = :bthno;
*/

{
#line 451 "Standard.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 451 "Standard.sqc"
  sqlaaloc(2,7,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 451 "Standard.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 451 "Standard.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 451 "Standard.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 451 "Standard.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 451 "Standard.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 451 "Standard.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 451 "Standard.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 451 "Standard.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 451 "Standard.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 451 "Standard.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 7;
#line 451 "Standard.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 451 "Standard.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 451 "Standard.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 6;
#line 451 "Standard.sqc"
      sql_setdlist[4].sqldata = (void*)bskmjno;
#line 451 "Standard.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 451 "Standard.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 451 "Standard.sqc"
      sql_setdlist[5].sqldata = (void*)knsgrp;
#line 451 "Standard.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 451 "Standard.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 451 "Standard.sqc"
      sql_setdlist[6].sqldata = (void*)&bthno;
#line 451 "Standard.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 451 "Standard.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 451 "Standard.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 451 "Standard.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 451 "Standard.sqc"
  sqlastop(0L);
}

#line 451 "Standard.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 456 "Standard.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
