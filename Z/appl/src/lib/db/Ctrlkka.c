static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,118,65,82,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,49,53,90,67,84,82,76,32,0,0,0,0,0,0,0,0,
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


#line 1 "Ctrlkka.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Ctrlkka.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Ctrlkka.h"
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


#line 24 "Ctrlkka.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Ctrlkka.sqc"

	char    knskisymd[11];
	char    bskkbn[5];
	char    bsklne[5];
	char    bskgok[7];
	char    knsgrp[17];
	char    kmkcd[8];
	char    nbkmkcd[8];
	sqlint32  ctrlno;
	char    ctrlsbt[21];
	short   ctrlsbteda;
	char    ctrllbl[3];
	char    tstrflg;
	char    asyrckid[11];
	short   asyrckpos;
	sqlint32  knsseq;
	sqlint32  bskseq;
	short   bthno;
	sqlint32  bthrckjbn;
	char    syklotno[21];
	char    sktti[25];
	char    knzti[25];
	char    knztistflg;
	char    sktdh[27];
	short   ctrljti;
	char    chkzmflg;
	char    facter[13];
	char    base[13];
	char    kosijt;
	char    kositts[9];
	char    kosidh[27];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 61 "Ctrlkka.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Ctrlkka

BmlDMMInfo	CtrlkkaArray[] = {
	DMM_SDATE( knskisymd ),
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( bsklne ),
	DMM_SSTRING( bskgok ),
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( nbkmkcd ),
	DMM_SLONG( ctrlno ),
	DMM_SSTRING( ctrlsbt ),
	DMM_SSHORT( ctrlsbteda ),
	DMM_SSTRING( ctrllbl ),
	DMM_SCHAR( tstrflg ),
	DMM_SSTRING( asyrckid ),
	DMM_SSHORT( asyrckpos ),
	DMM_SLONG( knsseq ),
	DMM_SLONG( bskseq ),
	DMM_SSHORT( bthno ),
	DMM_SLONG( bthrckjbn ),
	DMM_SSTRING( syklotno ),
	DMM_SSTRING( sktti ),
	DMM_SSTRING( knzti ),
	DMM_SCHAR( knztistflg ),
	DMM_STIMESTAMP( sktdh ),
	DMM_SSHORT( ctrljti ),
	DMM_SCHAR( chkzmflg ),
	DMM_SSTRING( facter ),
	DMM_SSTRING( base ),
	DMM_SCHAR( kosijt ),
	DMM_SSTRING( kositts ),
	DMM_STIMESTAMP( kosidh ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbCtrlkkaSelectAll()
 *    CTRLKKA レコード全件取得
 * ■引数
 *    [O]  Ctrlkka** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCtrlkkaSelectAll( Ctrlkka** arrayOut, int* numOut )
{
    Ctrlkka*    array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 120 "Ctrlkka.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSKISYMD,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		KNSGRP,
		KMKCD,
		NBKMKCD,
		CTRLNO,
		CTRLSBT,
		CTRLSBTEDA,
		CTRLLBL,
		TSTRFLG,
		ASYRCKID,
		ASYRCKPOS,
		KNSSEQ,
		BSKSEQ,
		BTHNO,
		BTHRCKJBN,
		SYKLOTNO,
		SKTTI,
		KNZTI,
		KNZTISTFLG,
		SKTDH,
		CTRLJTI,
		CHKZMFLG,
		FACTER,
		BASE,
		KOSIJT,
		KOSITTS,
		KOSIDH,
		KSNDH
    FROM
        CTRLKKA FOR READ ONLY;
*/

#line 156 "Ctrlkka.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 158 "Ctrlkka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 158 "Ctrlkka.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 158 "Ctrlkka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 158 "Ctrlkka.sqc"
  sqlastop(0L);
}

#line 158 "Ctrlkka.sqc"


    while( 1 ) {
        Ctrlkka* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knskisymd,
			:bskkbn,
			:bsklne,
			:bskgok,
			:knsgrp,
			:kmkcd,
			:nbkmkcd,
			:ctrlno,
			:ctrlsbt,
			:ctrlsbteda,
			:ctrllbl,
			:tstrflg,
			:asyrckid,
			:asyrckpos,
			:knsseq,
			:bskseq,
			:bthno,
			:bthrckjbn,
			:syklotno,
			:sktti,
			:knzti,
			:knztistflg,
			:sktdh,
			:ctrljti,
			:chkzmflg,
			:facter,
			:base,
			:kosijt,
			:kositts,
			:kosidh,
			:ksndh;
*/

{
#line 194 "Ctrlkka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 194 "Ctrlkka.sqc"
  sqlaaloc(3,31,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[31];
#line 194 "Ctrlkka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 7;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[6].sqldata = (void*)nbkmkcd;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[7].sqldata = (void*)&ctrlno;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 21;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[8].sqldata = (void*)ctrlsbt;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[9].sqldata = (void*)&ctrlsbteda;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 3;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[10].sqldata = (void*)ctrllbl;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[11].sqldata = (void*)&tstrflg;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[12].sqldata = (void*)asyrckid;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[13].sqldata = (void*)&asyrckpos;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[14].sqldata = (void*)&knsseq;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[15].sqldata = (void*)&bskseq;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[16].sqltype = 500; sql_setdlist[16].sqllen = 2;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[16].sqldata = (void*)&bthno;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[17].sqldata = (void*)&bthrckjbn;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 21;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[18].sqldata = (void*)syklotno;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 25;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[19].sqldata = (void*)sktti;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 25;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[20].sqldata = (void*)knzti;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[21].sqldata = (void*)&knztistflg;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 27;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[22].sqldata = (void*)sktdh;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[23].sqltype = 500; sql_setdlist[23].sqllen = 2;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[23].sqldata = (void*)&ctrljti;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[24].sqldata = (void*)&chkzmflg;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 13;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[25].sqldata = (void*)facter;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 13;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[26].sqldata = (void*)base;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[27].sqldata = (void*)&kosijt;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 9;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[28].sqldata = (void*)kositts;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[29].sqldata = (void*)kosidh;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 27;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[30].sqldata = (void*)ksndh;
#line 194 "Ctrlkka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 194 "Ctrlkka.sqc"
      sqlasetdata(3,0,31,sql_setdlist,0L,0L);
    }
#line 194 "Ctrlkka.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 194 "Ctrlkka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 194 "Ctrlkka.sqc"
  sqlastop(0L);
}

#line 194 "Ctrlkka.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Ctrlkka*)ZbmlRealloc( array,
                                    sizeof( Ctrlkka ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Ctrlkka ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, CtrlkkaArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 209 "Ctrlkka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 209 "Ctrlkka.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 209 "Ctrlkka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 209 "Ctrlkka.sqc"
  sqlastop(0L);
}

#line 209 "Ctrlkka.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 217 "Ctrlkka.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbCtrlkkaSelectKey()
 *    CTRLKKA レコードKey条件取得
 * ■引数
 *    [I]  Ctrlkka* pKey       取得するレコードのキー
 *    [O]  Ctrlkka** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCtrlkkaSelectKey( Ctrlkka* pKey, Ctrlkka** arrayOut, int* numOut )
{
    Ctrlkka*    array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, CtrlkkaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 243 "Ctrlkka.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSKISYMD,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		KNSGRP,
		KMKCD,
		NBKMKCD,
		CTRLNO,
		CTRLSBT,
		CTRLSBTEDA,
		CTRLLBL,
		TSTRFLG,
		ASYRCKID,
		ASYRCKPOS,
		KNSSEQ,
		BSKSEQ,
		BTHNO,
		BTHRCKJBN,
		SYKLOTNO,
		SKTTI,
		KNZTI,
		KNZTISTFLG,
		SKTDH,
		CTRLJTI,
		CHKZMFLG,
		FACTER,
		BASE,
		KOSIJT,
		KOSITTS,
		KOSIDH,
		KSNDH
    FROM
        CTRLKKA
    WHERE
		KNSKISYMD = :knskisymd AND
		BSKKBN = :bskkbn AND
		BSKGOK = :bskgok AND
		KMKCD = :kmkcd AND
		CTRLNO = :ctrlno AND
		CTRLSBT = :ctrlsbt AND
		CTRLSBTEDA = :ctrlsbteda FOR READ ONLY;
*/

#line 287 "Ctrlkka.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 289 "Ctrlkka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 289 "Ctrlkka.sqc"
  sqlaaloc(2,7,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 289 "Ctrlkka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 289 "Ctrlkka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 289 "Ctrlkka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 289 "Ctrlkka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 289 "Ctrlkka.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 289 "Ctrlkka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 289 "Ctrlkka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 7;
#line 289 "Ctrlkka.sqc"
      sql_setdlist[2].sqldata = (void*)bskgok;
#line 289 "Ctrlkka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 289 "Ctrlkka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 289 "Ctrlkka.sqc"
      sql_setdlist[3].sqldata = (void*)kmkcd;
#line 289 "Ctrlkka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 289 "Ctrlkka.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 289 "Ctrlkka.sqc"
      sql_setdlist[4].sqldata = (void*)&ctrlno;
#line 289 "Ctrlkka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 289 "Ctrlkka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 289 "Ctrlkka.sqc"
      sql_setdlist[5].sqldata = (void*)ctrlsbt;
#line 289 "Ctrlkka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 289 "Ctrlkka.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 289 "Ctrlkka.sqc"
      sql_setdlist[6].sqldata = (void*)&ctrlsbteda;
#line 289 "Ctrlkka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 289 "Ctrlkka.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 289 "Ctrlkka.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 289 "Ctrlkka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 289 "Ctrlkka.sqc"
  sqlastop(0L);
}

#line 289 "Ctrlkka.sqc"


    while( 1 ) {
        Ctrlkka* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knskisymd,
			:bskkbn,
			:bsklne,
			:bskgok,
			:knsgrp,
			:kmkcd,
			:nbkmkcd,
			:ctrlno,
			:ctrlsbt,
			:ctrlsbteda,
			:ctrllbl,
			:tstrflg,
			:asyrckid,
			:asyrckpos,
			:knsseq,
			:bskseq,
			:bthno,
			:bthrckjbn,
			:syklotno,
			:sktti,
			:knzti,
			:knztistflg,
			:sktdh,
			:ctrljti,
			:chkzmflg,
			:facter,
			:base,
			:kosijt,
			:kositts,
			:kosidh,
			:ksndh;
*/

{
#line 325 "Ctrlkka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 325 "Ctrlkka.sqc"
  sqlaaloc(3,31,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[31];
#line 325 "Ctrlkka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 7;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[6].sqldata = (void*)nbkmkcd;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[7].sqldata = (void*)&ctrlno;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 21;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[8].sqldata = (void*)ctrlsbt;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[9].sqldata = (void*)&ctrlsbteda;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 3;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[10].sqldata = (void*)ctrllbl;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[11].sqldata = (void*)&tstrflg;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[12].sqldata = (void*)asyrckid;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[13].sqldata = (void*)&asyrckpos;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[14].sqldata = (void*)&knsseq;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[15].sqldata = (void*)&bskseq;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[16].sqltype = 500; sql_setdlist[16].sqllen = 2;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[16].sqldata = (void*)&bthno;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[17].sqldata = (void*)&bthrckjbn;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 21;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[18].sqldata = (void*)syklotno;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 25;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[19].sqldata = (void*)sktti;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 25;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[20].sqldata = (void*)knzti;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[21].sqldata = (void*)&knztistflg;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 27;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[22].sqldata = (void*)sktdh;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[23].sqltype = 500; sql_setdlist[23].sqllen = 2;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[23].sqldata = (void*)&ctrljti;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[24].sqldata = (void*)&chkzmflg;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 13;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[25].sqldata = (void*)facter;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 13;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[26].sqldata = (void*)base;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[27].sqldata = (void*)&kosijt;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 9;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[28].sqldata = (void*)kositts;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[29].sqldata = (void*)kosidh;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 27;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[30].sqldata = (void*)ksndh;
#line 325 "Ctrlkka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 325 "Ctrlkka.sqc"
      sqlasetdata(3,0,31,sql_setdlist,0L,0L);
    }
#line 325 "Ctrlkka.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 325 "Ctrlkka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 325 "Ctrlkka.sqc"
  sqlastop(0L);
}

#line 325 "Ctrlkka.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Ctrlkka*)ZbmlRealloc( array,
                                    sizeof( Ctrlkka ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Ctrlkka ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, CtrlkkaArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 340 "Ctrlkka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 340 "Ctrlkka.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 340 "Ctrlkka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 340 "Ctrlkka.sqc"
  sqlastop(0L);
}

#line 340 "Ctrlkka.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 348 "Ctrlkka.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbCtrlkkaInsert()
 *    CTRLKKA レコードを挿入する
 * ■引数
 *    [I]  Ctrlkka* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCtrlkkaInsert( Ctrlkka* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, CtrlkkaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 371 "Ctrlkka.sqc"


    
/*
EXEC SQL INSERT INTO CTRLKKA
    (
		KNSKISYMD,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		KNSGRP,
		KMKCD,
		NBKMKCD,
		CTRLNO,
		CTRLSBT,
		CTRLSBTEDA,
		CTRLLBL,
		TSTRFLG,
		ASYRCKID,
		ASYRCKPOS,
		KNSSEQ,
		BSKSEQ,
		BTHNO,
		BTHRCKJBN,
		SYKLOTNO,
		SKTTI,
		KNZTI,
		KNZTISTFLG,
		SKTDH,
		CTRLJTI,
		CHKZMFLG,
		FACTER,
		BASE,
		KOSIJT,
		KOSITTS,
		KOSIDH,
		KSNDH
    ) VALUES (
		:knskisymd,
		:bskkbn,
		:bsklne,
		:bskgok,
		:knsgrp,
		:kmkcd,
		:nbkmkcd,
		:ctrlno,
		:ctrlsbt,
		:ctrlsbteda,
		:ctrllbl,
		:tstrflg,
		:asyrckid,
		:asyrckpos,
		:knsseq,
		:bskseq,
		:bthno,
		:bthrckjbn,
		:syklotno,
		:sktti,
		:knzti,
		:knztistflg,
		:sktdh,
		:ctrljti,
		:chkzmflg,
		:facter,
		:base,
		:kosijt,
		:kositts,
		:kosidh,
		:ksndh
    );
*/

{
#line 438 "Ctrlkka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 438 "Ctrlkka.sqc"
  sqlaaloc(2,31,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[31];
#line 438 "Ctrlkka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 7;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[6].sqldata = (void*)nbkmkcd;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[7].sqldata = (void*)&ctrlno;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 21;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[8].sqldata = (void*)ctrlsbt;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[9].sqldata = (void*)&ctrlsbteda;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 3;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[10].sqldata = (void*)ctrllbl;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[11].sqldata = (void*)&tstrflg;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[12].sqldata = (void*)asyrckid;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[13].sqldata = (void*)&asyrckpos;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[14].sqldata = (void*)&knsseq;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[15].sqldata = (void*)&bskseq;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[16].sqltype = 500; sql_setdlist[16].sqllen = 2;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[16].sqldata = (void*)&bthno;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[17].sqldata = (void*)&bthrckjbn;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 21;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[18].sqldata = (void*)syklotno;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 25;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[19].sqldata = (void*)sktti;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 25;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[20].sqldata = (void*)knzti;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[21].sqldata = (void*)&knztistflg;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 27;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[22].sqldata = (void*)sktdh;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[23].sqltype = 500; sql_setdlist[23].sqllen = 2;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[23].sqldata = (void*)&ctrljti;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[24].sqldata = (void*)&chkzmflg;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 13;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[25].sqldata = (void*)facter;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 13;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[26].sqldata = (void*)base;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[27].sqldata = (void*)&kosijt;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 9;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[28].sqldata = (void*)kositts;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[29].sqldata = (void*)kosidh;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 27;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[30].sqldata = (void*)ksndh;
#line 438 "Ctrlkka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 438 "Ctrlkka.sqc"
      sqlasetdata(2,0,31,sql_setdlist,0L,0L);
    }
#line 438 "Ctrlkka.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 438 "Ctrlkka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 438 "Ctrlkka.sqc"
  sqlastop(0L);
}

#line 438 "Ctrlkka.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 443 "Ctrlkka.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbCtrlkkaUpdate()
 *    CTRLKKA レコードを更新する
 * ■引数
 *    [I]  Ctrlkka* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCtrlkkaUpdate( Ctrlkka* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, CtrlkkaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 467 "Ctrlkka.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 468 "Ctrlkka.sqc"


    
/*
EXEC SQL UPDATE CTRLKKA
    SET (
		BSKLNE,
		KNSGRP,
		NBKMKCD,
		CTRLLBL,
		TSTRFLG,
		ASYRCKID,
		ASYRCKPOS,
		KNSSEQ,
		BSKSEQ,
		BTHNO,
		BTHRCKJBN,
		SYKLOTNO,
		SKTTI,
		KNZTI,
		KNZTISTFLG,
		SKTDH,
		CTRLJTI,
		CHKZMFLG,
		FACTER,
		BASE,
		KOSIJT,
		KOSITTS,
		KOSIDH,
		KSNDH
    ) = (
		:bsklne,
		:knsgrp,
		:nbkmkcd,
		:ctrllbl,
		:tstrflg,
		:asyrckid,
		:asyrckpos,
		:knsseq,
		:bskseq,
		:bthno,
		:bthrckjbn,
		:syklotno,
		:sktti,
		:knzti,
		:knztistflg,
		:sktdh,
		:ctrljti,
		:chkzmflg,
		:facter,
		:base,
		:kosijt,
		:kositts,
		:kosidh,
		:ksndh
    ) WHERE
		KNSKISYMD = :knskisymd AND
		BSKKBN = :bskkbn AND
		BSKGOK = :bskgok AND
		KMKCD = :kmkcd AND
		CTRLNO = :ctrlno AND
		CTRLSBT = :ctrlsbt AND
		CTRLSBTEDA = :ctrlsbteda;
*/

{
#line 528 "Ctrlkka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 528 "Ctrlkka.sqc"
  sqlaaloc(2,31,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[31];
#line 528 "Ctrlkka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[0].sqldata = (void*)bsklne;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[2].sqldata = (void*)nbkmkcd;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[3].sqldata = (void*)ctrllbl;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[4].sqldata = (void*)&tstrflg;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[5].sqldata = (void*)asyrckid;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[6].sqldata = (void*)&asyrckpos;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[7].sqldata = (void*)&knsseq;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[8].sqldata = (void*)&bskseq;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[9].sqldata = (void*)&bthno;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[10].sqltype = 496; sql_setdlist[10].sqllen = 4;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[10].sqldata = (void*)&bthrckjbn;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 21;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[11].sqldata = (void*)syklotno;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 25;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[12].sqldata = (void*)sktti;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 25;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[13].sqldata = (void*)knzti;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[14].sqldata = (void*)&knztistflg;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[15].sqldata = (void*)sktdh;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[16].sqltype = 500; sql_setdlist[16].sqllen = 2;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[16].sqldata = (void*)&ctrljti;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[17].sqldata = (void*)&chkzmflg;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 13;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[18].sqldata = (void*)facter;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 13;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[19].sqldata = (void*)base;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[20].sqldata = (void*)&kosijt;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 9;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[21].sqldata = (void*)kositts;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 27;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[22].sqldata = (void*)kosidh;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 27;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[23].sqldata = (void*)ksndh;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 11;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[24].sqldata = (void*)knskisymd;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 5;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[25].sqldata = (void*)bskkbn;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 7;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[26].sqldata = (void*)bskgok;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 8;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[27].sqldata = (void*)kmkcd;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[28].sqltype = 496; sql_setdlist[28].sqllen = 4;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[28].sqldata = (void*)&ctrlno;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 21;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[29].sqldata = (void*)ctrlsbt;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[30].sqltype = 500; sql_setdlist[30].sqllen = 2;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[30].sqldata = (void*)&ctrlsbteda;
#line 528 "Ctrlkka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 528 "Ctrlkka.sqc"
      sqlasetdata(2,0,31,sql_setdlist,0L,0L);
    }
#line 528 "Ctrlkka.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 528 "Ctrlkka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 528 "Ctrlkka.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 528 "Ctrlkka.sqc"
  sqlastop(0L);
}

#line 528 "Ctrlkka.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 533 "Ctrlkka.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 537 "Ctrlkka.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbCtrlkkaDelete()
 *    CTRLKKA レコードを削除する
 * ■引数
 *    [I]  Ctrlkka* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCtrlkkaDelete( Ctrlkka* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, CtrlkkaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 561 "Ctrlkka.sqc"


    
/*
EXEC SQL DELETE FROM CTRLKKA
    WHERE
		KNSKISYMD = :knskisymd AND
		BSKKBN = :bskkbn AND
		BSKGOK = :bskgok AND
		KMKCD = :kmkcd AND
		CTRLNO = :ctrlno AND
		CTRLSBT = :ctrlsbt AND
		CTRLSBTEDA = :ctrlsbteda;
*/

{
#line 571 "Ctrlkka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 571 "Ctrlkka.sqc"
  sqlaaloc(2,7,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 571 "Ctrlkka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 571 "Ctrlkka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 571 "Ctrlkka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 571 "Ctrlkka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 571 "Ctrlkka.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 571 "Ctrlkka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 571 "Ctrlkka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 7;
#line 571 "Ctrlkka.sqc"
      sql_setdlist[2].sqldata = (void*)bskgok;
#line 571 "Ctrlkka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 571 "Ctrlkka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 571 "Ctrlkka.sqc"
      sql_setdlist[3].sqldata = (void*)kmkcd;
#line 571 "Ctrlkka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 571 "Ctrlkka.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 571 "Ctrlkka.sqc"
      sql_setdlist[4].sqldata = (void*)&ctrlno;
#line 571 "Ctrlkka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 571 "Ctrlkka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 571 "Ctrlkka.sqc"
      sql_setdlist[5].sqldata = (void*)ctrlsbt;
#line 571 "Ctrlkka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 571 "Ctrlkka.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 571 "Ctrlkka.sqc"
      sql_setdlist[6].sqldata = (void*)&ctrlsbteda;
#line 571 "Ctrlkka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 571 "Ctrlkka.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 571 "Ctrlkka.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 571 "Ctrlkka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 571 "Ctrlkka.sqc"
  sqlastop(0L);
}

#line 571 "Ctrlkka.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 576 "Ctrlkka.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
