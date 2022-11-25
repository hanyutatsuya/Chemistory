static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,89,65,85,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,52,55,90,75,78,84,73,32,0,0,0,0,0,0,0,0,
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


#line 1 "Kntidunknown.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Kntidunknown.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Kntidunknown.h"
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


#line 24 "Kntidunknown.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Kntidunknown.sqc"

	char    knskisymd[11];
	char    bskkbn[11];
	char    bsklne[11];
	char    bskgok[6];
	char    bskmjno[6];
	sqlint32  bskseq;
	sqlint32  nbkmkcd;
	char    knshu[41];
	char    bskerrsts[3];
	char    rawdata[31];
	char    sktdh[27];
	sqlint32  ctrlno;
	char    ksbr[9];
	char    nbdolbl[9];
	char    nbdoerr[4];
	char    ykdolbl[9];
	char    ykdoerr[4];
	char    etclbl[9];
	char    etcerr[4];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 50 "Kntidunknown.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Kntidunknown

BmlDMMInfo	KntidunknownArray[] = {
	DMM_SDATE( knskisymd ),
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( bsklne ),
	DMM_SSTRING( bskgok ),
	DMM_SSTRING( bskmjno ),
	DMM_SLONG( bskseq ),
	DMM_SLONG( nbkmkcd ),
	DMM_SSTRING( knshu ),
	DMM_SSTRING( bskerrsts ),
	DMM_SSTRING( rawdata ),
	DMM_STIMESTAMP( sktdh ),
	DMM_SLONG( ctrlno ),
	DMM_SSTRING( ksbr ),
	DMM_SSTRING( nbdolbl ),
	DMM_SSTRING( nbdoerr ),
	DMM_SSTRING( ykdolbl ),
	DMM_SSTRING( ykdoerr ),
	DMM_SSTRING( etclbl ),
	DMM_SSTRING( etcerr ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKntidunknownSelectAll()
 *    KNTIDUNKNOWN レコード全件取得
 * ■引数
 *    [O]  Kntidunknown** array 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKntidunknownSelectAll( Kntidunknown** arrayOut, int* numOut )
{
    Kntidunknown* array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 98 "Kntidunknown.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSKISYMD,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		BSKMJNO,
		BSKSEQ,
		NBKMKCD,
		KNSHU,
		BSKERRSTS,
		RAWDATA,
		SKTDH,
		CTRLNO,
		KSBR,
		NBDOLBL,
		NBDOERR,
		YKDOLBL,
		YKDOERR,
		ETCLBL,
		ETCERR,
		KSNDH
    FROM
        KNTIDUNKNOWN FOR READ ONLY;
*/

#line 123 "Kntidunknown.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 125 "Kntidunknown.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 125 "Kntidunknown.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 125 "Kntidunknown.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 125 "Kntidunknown.sqc"
  sqlastop(0L);
}

#line 125 "Kntidunknown.sqc"


    while( 1 ) {
        Kntidunknown* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knskisymd,
			:bskkbn,
			:bsklne,
			:bskgok,
			:bskmjno,
			:bskseq,
			:nbkmkcd,
			:knshu,
			:bskerrsts,
			:rawdata,
			:sktdh,
			:ctrlno,
			:ksbr,
			:nbdolbl,
			:nbdoerr,
			:ykdolbl,
			:ykdoerr,
			:etclbl,
			:etcerr,
			:ksndh;
*/

{
#line 150 "Kntidunknown.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 150 "Kntidunknown.sqc"
  sqlaaloc(3,20,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[20];
#line 150 "Kntidunknown.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 6;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 6;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[4].sqldata = (void*)bskmjno;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[5].sqldata = (void*)&bskseq;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[6].sqldata = (void*)&nbkmkcd;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 41;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[7].sqldata = (void*)knshu;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 3;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[8].sqldata = (void*)bskerrsts;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 31;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[9].sqldata = (void*)rawdata;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 27;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[10].sqldata = (void*)sktdh;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[11].sqldata = (void*)&ctrlno;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[12].sqldata = (void*)ksbr;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[13].sqldata = (void*)nbdolbl;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 4;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[14].sqldata = (void*)nbdoerr;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[15].sqldata = (void*)ykdolbl;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 4;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[16].sqldata = (void*)ykdoerr;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 9;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[17].sqldata = (void*)etclbl;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 4;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[18].sqldata = (void*)etcerr;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[19].sqldata = (void*)ksndh;
#line 150 "Kntidunknown.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 150 "Kntidunknown.sqc"
      sqlasetdata(3,0,20,sql_setdlist,0L,0L);
    }
#line 150 "Kntidunknown.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 150 "Kntidunknown.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 150 "Kntidunknown.sqc"
  sqlastop(0L);
}

#line 150 "Kntidunknown.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kntidunknown*)ZbmlRealloc( array,
                                    sizeof( Kntidunknown ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kntidunknown ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KntidunknownArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 165 "Kntidunknown.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 165 "Kntidunknown.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 165 "Kntidunknown.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 165 "Kntidunknown.sqc"
  sqlastop(0L);
}

#line 165 "Kntidunknown.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 173 "Kntidunknown.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKntidunknownSelectKey()
 *    KNTIDUNKNOWN レコードKey条件取得
 * ■引数
 *    [I]  Kntidunknown* pKey   取得するレコードのキー
 *    [O]  Kntidunknown** array 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKntidunknownSelectKey( Kntidunknown* pKey, Kntidunknown** arrayOut, int* numOut )
{
    Kntidunknown* array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KntidunknownArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 199 "Kntidunknown.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSKISYMD,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		BSKMJNO,
		BSKSEQ,
		NBKMKCD,
		KNSHU,
		BSKERRSTS,
		RAWDATA,
		SKTDH,
		CTRLNO,
		KSBR,
		NBDOLBL,
		NBDOERR,
		YKDOLBL,
		YKDOERR,
		ETCLBL,
		ETCERR,
		KSNDH
    FROM
        KNTIDUNKNOWN
    WHERE
		KNSKISYMD = :knskisymd AND
		BSKKBN = :bskkbn AND
		BSKLNE = :bsklne AND
		BSKGOK = :bskgok AND
		BSKMJNO = :bskmjno AND
		BSKSEQ = :bskseq AND
		NBKMKCD = :nbkmkcd FOR READ ONLY;
*/

#line 232 "Kntidunknown.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 234 "Kntidunknown.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 234 "Kntidunknown.sqc"
  sqlaaloc(2,7,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 234 "Kntidunknown.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 234 "Kntidunknown.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 234 "Kntidunknown.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 234 "Kntidunknown.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 234 "Kntidunknown.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 234 "Kntidunknown.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 234 "Kntidunknown.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 234 "Kntidunknown.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 234 "Kntidunknown.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 234 "Kntidunknown.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 6;
#line 234 "Kntidunknown.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 234 "Kntidunknown.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 234 "Kntidunknown.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 6;
#line 234 "Kntidunknown.sqc"
      sql_setdlist[4].sqldata = (void*)bskmjno;
#line 234 "Kntidunknown.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 234 "Kntidunknown.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 234 "Kntidunknown.sqc"
      sql_setdlist[5].sqldata = (void*)&bskseq;
#line 234 "Kntidunknown.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 234 "Kntidunknown.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 234 "Kntidunknown.sqc"
      sql_setdlist[6].sqldata = (void*)&nbkmkcd;
#line 234 "Kntidunknown.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 234 "Kntidunknown.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 234 "Kntidunknown.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 234 "Kntidunknown.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 234 "Kntidunknown.sqc"
  sqlastop(0L);
}

#line 234 "Kntidunknown.sqc"


    while( 1 ) {
        Kntidunknown* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knskisymd,
			:bskkbn,
			:bsklne,
			:bskgok,
			:bskmjno,
			:bskseq,
			:nbkmkcd,
			:knshu,
			:bskerrsts,
			:rawdata,
			:sktdh,
			:ctrlno,
			:ksbr,
			:nbdolbl,
			:nbdoerr,
			:ykdolbl,
			:ykdoerr,
			:etclbl,
			:etcerr,
			:ksndh;
*/

{
#line 259 "Kntidunknown.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 259 "Kntidunknown.sqc"
  sqlaaloc(3,20,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[20];
#line 259 "Kntidunknown.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 6;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 6;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[4].sqldata = (void*)bskmjno;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[5].sqldata = (void*)&bskseq;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[6].sqldata = (void*)&nbkmkcd;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 41;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[7].sqldata = (void*)knshu;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 3;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[8].sqldata = (void*)bskerrsts;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 31;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[9].sqldata = (void*)rawdata;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 27;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[10].sqldata = (void*)sktdh;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[11].sqldata = (void*)&ctrlno;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[12].sqldata = (void*)ksbr;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[13].sqldata = (void*)nbdolbl;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 4;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[14].sqldata = (void*)nbdoerr;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[15].sqldata = (void*)ykdolbl;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 4;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[16].sqldata = (void*)ykdoerr;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 9;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[17].sqldata = (void*)etclbl;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 4;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[18].sqldata = (void*)etcerr;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[19].sqldata = (void*)ksndh;
#line 259 "Kntidunknown.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 259 "Kntidunknown.sqc"
      sqlasetdata(3,0,20,sql_setdlist,0L,0L);
    }
#line 259 "Kntidunknown.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 259 "Kntidunknown.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 259 "Kntidunknown.sqc"
  sqlastop(0L);
}

#line 259 "Kntidunknown.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kntidunknown*)ZbmlRealloc( array,
                                    sizeof( Kntidunknown ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kntidunknown ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KntidunknownArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 274 "Kntidunknown.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 274 "Kntidunknown.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 274 "Kntidunknown.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 274 "Kntidunknown.sqc"
  sqlastop(0L);
}

#line 274 "Kntidunknown.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 282 "Kntidunknown.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKntidunknownInsert()
 *    KNTIDUNKNOWN レコードを挿入する
 * ■引数
 *    [I]  Kntidunknown* rec    挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKntidunknownInsert( Kntidunknown* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KntidunknownArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 305 "Kntidunknown.sqc"


    
/*
EXEC SQL INSERT INTO KNTIDUNKNOWN
    (
		KNSKISYMD,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		BSKMJNO,
		BSKSEQ,
		NBKMKCD,
		KNSHU,
		BSKERRSTS,
		RAWDATA,
		SKTDH,
		CTRLNO,
		KSBR,
		NBDOLBL,
		NBDOERR,
		YKDOLBL,
		YKDOERR,
		ETCLBL,
		ETCERR,
		KSNDH
    ) VALUES (
		:knskisymd,
		:bskkbn,
		:bsklne,
		:bskgok,
		:bskmjno,
		:bskseq,
		:nbkmkcd,
		:knshu,
		:bskerrsts,
		:rawdata,
		:sktdh,
		:ctrlno,
		:ksbr,
		:nbdolbl,
		:nbdoerr,
		:ykdolbl,
		:ykdoerr,
		:etclbl,
		:etcerr,
		:ksndh
    );
*/

{
#line 350 "Kntidunknown.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 350 "Kntidunknown.sqc"
  sqlaaloc(2,20,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[20];
#line 350 "Kntidunknown.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 6;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 6;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[4].sqldata = (void*)bskmjno;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[5].sqldata = (void*)&bskseq;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[6].sqldata = (void*)&nbkmkcd;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 41;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[7].sqldata = (void*)knshu;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 3;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[8].sqldata = (void*)bskerrsts;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 31;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[9].sqldata = (void*)rawdata;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 27;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[10].sqldata = (void*)sktdh;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[11].sqldata = (void*)&ctrlno;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[12].sqldata = (void*)ksbr;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[13].sqldata = (void*)nbdolbl;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 4;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[14].sqldata = (void*)nbdoerr;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[15].sqldata = (void*)ykdolbl;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 4;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[16].sqldata = (void*)ykdoerr;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 9;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[17].sqldata = (void*)etclbl;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 4;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[18].sqldata = (void*)etcerr;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[19].sqldata = (void*)ksndh;
#line 350 "Kntidunknown.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 350 "Kntidunknown.sqc"
      sqlasetdata(2,0,20,sql_setdlist,0L,0L);
    }
#line 350 "Kntidunknown.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 350 "Kntidunknown.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 350 "Kntidunknown.sqc"
  sqlastop(0L);
}

#line 350 "Kntidunknown.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 355 "Kntidunknown.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKntidunknownUpdate()
 *    KNTIDUNKNOWN レコードを更新する
 * ■引数
 *    [I]  Kntidunknown* rec    更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKntidunknownUpdate( Kntidunknown* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KntidunknownArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 379 "Kntidunknown.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 380 "Kntidunknown.sqc"


    
/*
EXEC SQL UPDATE KNTIDUNKNOWN
    SET (
		KNSHU,
		BSKERRSTS,
		RAWDATA,
		SKTDH,
		CTRLNO,
		KSBR,
		NBDOLBL,
		NBDOERR,
		YKDOLBL,
		YKDOERR,
		ETCLBL,
		ETCERR,
		KSNDH
    ) = (
		:knshu,
		:bskerrsts,
		:rawdata,
		:sktdh,
		:ctrlno,
		:ksbr,
		:nbdolbl,
		:nbdoerr,
		:ykdolbl,
		:ykdoerr,
		:etclbl,
		:etcerr,
		:ksndh
    ) WHERE
		KNSKISYMD = :knskisymd AND
		BSKKBN = :bskkbn AND
		BSKLNE = :bsklne AND
		BSKGOK = :bskgok AND
		BSKMJNO = :bskmjno AND
		BSKSEQ = :bskseq AND
		NBKMKCD = :nbkmkcd;
*/

{
#line 418 "Kntidunknown.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 418 "Kntidunknown.sqc"
  sqlaaloc(2,20,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[20];
#line 418 "Kntidunknown.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 41;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[0].sqldata = (void*)knshu;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[1].sqldata = (void*)bskerrsts;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 31;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[2].sqldata = (void*)rawdata;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 27;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[3].sqldata = (void*)sktdh;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[4].sqldata = (void*)&ctrlno;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 9;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[5].sqldata = (void*)ksbr;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 9;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[6].sqldata = (void*)nbdolbl;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 4;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[7].sqldata = (void*)nbdoerr;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[8].sqldata = (void*)ykdolbl;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 4;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[9].sqldata = (void*)ykdoerr;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 9;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[10].sqldata = (void*)etclbl;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 4;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[11].sqldata = (void*)etcerr;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 27;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[12].sqldata = (void*)ksndh;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[13].sqldata = (void*)knskisymd;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 11;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[14].sqldata = (void*)bskkbn;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 11;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[15].sqldata = (void*)bsklne;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 6;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[16].sqldata = (void*)bskgok;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 6;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[17].sqldata = (void*)bskmjno;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[18].sqltype = 496; sql_setdlist[18].sqllen = 4;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[18].sqldata = (void*)&bskseq;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[19].sqltype = 496; sql_setdlist[19].sqllen = 4;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[19].sqldata = (void*)&nbkmkcd;
#line 418 "Kntidunknown.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 418 "Kntidunknown.sqc"
      sqlasetdata(2,0,20,sql_setdlist,0L,0L);
    }
#line 418 "Kntidunknown.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 418 "Kntidunknown.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 418 "Kntidunknown.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 418 "Kntidunknown.sqc"
  sqlastop(0L);
}

#line 418 "Kntidunknown.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 423 "Kntidunknown.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 427 "Kntidunknown.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKntidunknownDelete()
 *    KNTIDUNKNOWN レコードを削除する
 * ■引数
 *    [I]  Kntidunknown* rec    削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKntidunknownDelete( Kntidunknown* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KntidunknownArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 451 "Kntidunknown.sqc"


    
/*
EXEC SQL DELETE FROM KNTIDUNKNOWN
    WHERE
		KNSKISYMD = :knskisymd AND
		BSKKBN = :bskkbn AND
		BSKLNE = :bsklne AND
		BSKGOK = :bskgok AND
		BSKMJNO = :bskmjno AND
		BSKSEQ = :bskseq AND
		NBKMKCD = :nbkmkcd;
*/

{
#line 461 "Kntidunknown.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 461 "Kntidunknown.sqc"
  sqlaaloc(2,7,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 461 "Kntidunknown.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 461 "Kntidunknown.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 461 "Kntidunknown.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 461 "Kntidunknown.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 461 "Kntidunknown.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 461 "Kntidunknown.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 461 "Kntidunknown.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 461 "Kntidunknown.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 461 "Kntidunknown.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 461 "Kntidunknown.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 6;
#line 461 "Kntidunknown.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 461 "Kntidunknown.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 461 "Kntidunknown.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 6;
#line 461 "Kntidunknown.sqc"
      sql_setdlist[4].sqldata = (void*)bskmjno;
#line 461 "Kntidunknown.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 461 "Kntidunknown.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 461 "Kntidunknown.sqc"
      sql_setdlist[5].sqldata = (void*)&bskseq;
#line 461 "Kntidunknown.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 461 "Kntidunknown.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 461 "Kntidunknown.sqc"
      sql_setdlist[6].sqldata = (void*)&nbkmkcd;
#line 461 "Kntidunknown.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 461 "Kntidunknown.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 461 "Kntidunknown.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 461 "Kntidunknown.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 461 "Kntidunknown.sqc"
  sqlastop(0L);
}

#line 461 "Kntidunknown.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 466 "Kntidunknown.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
