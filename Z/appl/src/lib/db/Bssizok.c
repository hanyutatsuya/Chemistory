static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,79,66,81,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,55,90,66,83,83,73,32,32,0,0,0,0,0,0,0,0,
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


#line 1 "Bssizok.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Bssizok.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Bssizok.h"
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


#line 24 "Bssizok.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Bssizok.sqc"

	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   bssino;
	char    ecd[4];
	char    sstcd[8];
	char    srknm[31];
	char    knjnmn[61];
	char    ngkbn;
	char    krtno[41];
	char    knjid[16];
	char    btnm[31];
	char    knjnmkey[61];
	char    ttinm[41];
	char    sbtkbn;
	char    birthday[9];
	char    birthdaykbn;
	char    age[4];
	char    agekbn;
	char    zrcd[5];
	char    sstme[9];
	char    ssymd[11];
	char    tntme[5];
	char    tntni;
	char    tnryo[6];
	char    tnryotni;
	char    bshdh[27];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 58 "Bssizok.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Bssizok

BmlDMMInfo	BssizokArray[] = {
	DMM_SDATE( utkymd ),
	DMM_SSTRING( irino ),
	DMM_SCHAR( iriketflg ),
	DMM_SSHORT( bssino ),
	DMM_SSTRING( ecd ),
	DMM_SSTRING( sstcd ),
	DMM_SSTRING( srknm ),
	DMM_SSTRING( knjnmn ),
	DMM_SCHAR( ngkbn ),
	DMM_SSTRING( krtno ),
	DMM_SSTRING( knjid ),
	DMM_SSTRING( btnm ),
	DMM_SSTRING( knjnmkey ),
	DMM_SSTRING( ttinm ),
	DMM_SCHAR( sbtkbn ),
	DMM_SSTRING( birthday ),
	DMM_SCHAR( birthdaykbn ),
	DMM_SSTRING( age ),
	DMM_SCHAR( agekbn ),
	DMM_SSTRING( zrcd ),
	DMM_STIME( sstme ),
	DMM_SDATE( ssymd ),
	DMM_SSTRING( tntme ),
	DMM_SCHAR( tntni ),
	DMM_SSTRING( tnryo ),
	DMM_SCHAR( tnryotni ),
	DMM_STIMESTAMP( bshdh ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbBssizokSelectAll()
 *    BSSIZOK レコード全件取得
 * ■引数
 *    [O]  Bssizok** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbBssizokSelectAll( Bssizok** arrayOut, int* numOut )
{
    Bssizok*    array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 114 "Bssizok.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		UTKYMD,
		IRINO,
		IRIKETFLG,
		BSSINO,
		ECD,
		SSTCD,
		SRKNM,
		KNJNMN,
		NGKBN,
		KRTNO,
		KNJID,
		BTNM,
		KNJNMKEY,
		TTINM,
		SBTKBN,
		BIRTHDAY,
		BIRTHDAYKBN,
		AGE,
		AGEKBN,
		ZRCD,
		SSTME,
		SSYMD,
		TNTME,
		TNTNI,
		TNRYO,
		TNRYOTNI,
		BSHDH,
		KSNDH
    FROM
        BSSIZOK FOR READ ONLY;
*/

#line 147 "Bssizok.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 149 "Bssizok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 149 "Bssizok.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 149 "Bssizok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 149 "Bssizok.sqc"
  sqlastop(0L);
}

#line 149 "Bssizok.sqc"


    while( 1 ) {
        Bssizok* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:utkymd,
			:irino,
			:iriketflg,
			:bssino,
			:ecd,
			:sstcd,
			:srknm,
			:knjnmn,
			:ngkbn,
			:krtno,
			:knjid,
			:btnm,
			:knjnmkey,
			:ttinm,
			:sbtkbn,
			:birthday,
			:birthdaykbn,
			:age,
			:agekbn,
			:zrcd,
			:sstme,
			:ssymd,
			:tntme,
			:tntni,
			:tnryo,
			:tnryotni,
			:bshdh,
			:ksndh;
*/

{
#line 182 "Bssizok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 182 "Bssizok.sqc"
  sqlaaloc(3,28,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[28];
#line 182 "Bssizok.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 182 "Bssizok.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 182 "Bssizok.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 182 "Bssizok.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 182 "Bssizok.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 182 "Bssizok.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 182 "Bssizok.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 182 "Bssizok.sqc"
      sql_setdlist[3].sqldata = (void*)&bssino;
#line 182 "Bssizok.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 4;
#line 182 "Bssizok.sqc"
      sql_setdlist[4].sqldata = (void*)ecd;
#line 182 "Bssizok.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 182 "Bssizok.sqc"
      sql_setdlist[5].sqldata = (void*)sstcd;
#line 182 "Bssizok.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 31;
#line 182 "Bssizok.sqc"
      sql_setdlist[6].sqldata = (void*)srknm;
#line 182 "Bssizok.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 61;
#line 182 "Bssizok.sqc"
      sql_setdlist[7].sqldata = (void*)knjnmn;
#line 182 "Bssizok.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 182 "Bssizok.sqc"
      sql_setdlist[8].sqldata = (void*)&ngkbn;
#line 182 "Bssizok.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 41;
#line 182 "Bssizok.sqc"
      sql_setdlist[9].sqldata = (void*)krtno;
#line 182 "Bssizok.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 16;
#line 182 "Bssizok.sqc"
      sql_setdlist[10].sqldata = (void*)knjid;
#line 182 "Bssizok.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 31;
#line 182 "Bssizok.sqc"
      sql_setdlist[11].sqldata = (void*)btnm;
#line 182 "Bssizok.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 61;
#line 182 "Bssizok.sqc"
      sql_setdlist[12].sqldata = (void*)knjnmkey;
#line 182 "Bssizok.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 41;
#line 182 "Bssizok.sqc"
      sql_setdlist[13].sqldata = (void*)ttinm;
#line 182 "Bssizok.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 182 "Bssizok.sqc"
      sql_setdlist[14].sqldata = (void*)&sbtkbn;
#line 182 "Bssizok.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 182 "Bssizok.sqc"
      sql_setdlist[15].sqldata = (void*)birthday;
#line 182 "Bssizok.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 182 "Bssizok.sqc"
      sql_setdlist[16].sqldata = (void*)&birthdaykbn;
#line 182 "Bssizok.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 4;
#line 182 "Bssizok.sqc"
      sql_setdlist[17].sqldata = (void*)age;
#line 182 "Bssizok.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 182 "Bssizok.sqc"
      sql_setdlist[18].sqldata = (void*)&agekbn;
#line 182 "Bssizok.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 5;
#line 182 "Bssizok.sqc"
      sql_setdlist[19].sqldata = (void*)zrcd;
#line 182 "Bssizok.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 9;
#line 182 "Bssizok.sqc"
      sql_setdlist[20].sqldata = (void*)sstme;
#line 182 "Bssizok.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 11;
#line 182 "Bssizok.sqc"
      sql_setdlist[21].sqldata = (void*)ssymd;
#line 182 "Bssizok.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 5;
#line 182 "Bssizok.sqc"
      sql_setdlist[22].sqldata = (void*)tntme;
#line 182 "Bssizok.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 182 "Bssizok.sqc"
      sql_setdlist[23].sqldata = (void*)&tntni;
#line 182 "Bssizok.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 6;
#line 182 "Bssizok.sqc"
      sql_setdlist[24].sqldata = (void*)tnryo;
#line 182 "Bssizok.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 182 "Bssizok.sqc"
      sql_setdlist[25].sqldata = (void*)&tnryotni;
#line 182 "Bssizok.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 27;
#line 182 "Bssizok.sqc"
      sql_setdlist[26].sqldata = (void*)bshdh;
#line 182 "Bssizok.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 27;
#line 182 "Bssizok.sqc"
      sql_setdlist[27].sqldata = (void*)ksndh;
#line 182 "Bssizok.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 182 "Bssizok.sqc"
      sqlasetdata(3,0,28,sql_setdlist,0L,0L);
    }
#line 182 "Bssizok.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 182 "Bssizok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 182 "Bssizok.sqc"
  sqlastop(0L);
}

#line 182 "Bssizok.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Bssizok*)ZbmlRealloc( array,
                                    sizeof( Bssizok ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Bssizok ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, BssizokArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 197 "Bssizok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 197 "Bssizok.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 197 "Bssizok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 197 "Bssizok.sqc"
  sqlastop(0L);
}

#line 197 "Bssizok.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 205 "Bssizok.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbBssizokSelectKey()
 *    BSSIZOK レコードKey条件取得
 * ■引数
 *    [I]  Bssizok* pKey       取得するレコードのキー
 *    [O]  Bssizok** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbBssizokSelectKey( Bssizok* pKey, Bssizok** arrayOut, int* numOut )
{
    Bssizok*    array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, BssizokArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 231 "Bssizok.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		UTKYMD,
		IRINO,
		IRIKETFLG,
		BSSINO,
		ECD,
		SSTCD,
		SRKNM,
		KNJNMN,
		NGKBN,
		KRTNO,
		KNJID,
		BTNM,
		KNJNMKEY,
		TTINM,
		SBTKBN,
		BIRTHDAY,
		BIRTHDAYKBN,
		AGE,
		AGEKBN,
		ZRCD,
		SSTME,
		SSYMD,
		TNTME,
		TNTNI,
		TNRYO,
		TNRYOTNI,
		BSHDH,
		KSNDH
    FROM
        BSSIZOK
    WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		BSSINO = :bssino FOR READ ONLY;
*/

#line 268 "Bssizok.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 270 "Bssizok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 270 "Bssizok.sqc"
  sqlaaloc(2,3,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 270 "Bssizok.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 270 "Bssizok.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 270 "Bssizok.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 270 "Bssizok.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 270 "Bssizok.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 270 "Bssizok.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 270 "Bssizok.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 270 "Bssizok.sqc"
      sql_setdlist[2].sqldata = (void*)&bssino;
#line 270 "Bssizok.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 270 "Bssizok.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 270 "Bssizok.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 270 "Bssizok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 270 "Bssizok.sqc"
  sqlastop(0L);
}

#line 270 "Bssizok.sqc"


    while( 1 ) {
        Bssizok* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:utkymd,
			:irino,
			:iriketflg,
			:bssino,
			:ecd,
			:sstcd,
			:srknm,
			:knjnmn,
			:ngkbn,
			:krtno,
			:knjid,
			:btnm,
			:knjnmkey,
			:ttinm,
			:sbtkbn,
			:birthday,
			:birthdaykbn,
			:age,
			:agekbn,
			:zrcd,
			:sstme,
			:ssymd,
			:tntme,
			:tntni,
			:tnryo,
			:tnryotni,
			:bshdh,
			:ksndh;
*/

{
#line 303 "Bssizok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 303 "Bssizok.sqc"
  sqlaaloc(3,28,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[28];
#line 303 "Bssizok.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 303 "Bssizok.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 303 "Bssizok.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 303 "Bssizok.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 303 "Bssizok.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 303 "Bssizok.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 303 "Bssizok.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 303 "Bssizok.sqc"
      sql_setdlist[3].sqldata = (void*)&bssino;
#line 303 "Bssizok.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 4;
#line 303 "Bssizok.sqc"
      sql_setdlist[4].sqldata = (void*)ecd;
#line 303 "Bssizok.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 303 "Bssizok.sqc"
      sql_setdlist[5].sqldata = (void*)sstcd;
#line 303 "Bssizok.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 31;
#line 303 "Bssizok.sqc"
      sql_setdlist[6].sqldata = (void*)srknm;
#line 303 "Bssizok.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 61;
#line 303 "Bssizok.sqc"
      sql_setdlist[7].sqldata = (void*)knjnmn;
#line 303 "Bssizok.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 303 "Bssizok.sqc"
      sql_setdlist[8].sqldata = (void*)&ngkbn;
#line 303 "Bssizok.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 41;
#line 303 "Bssizok.sqc"
      sql_setdlist[9].sqldata = (void*)krtno;
#line 303 "Bssizok.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 16;
#line 303 "Bssizok.sqc"
      sql_setdlist[10].sqldata = (void*)knjid;
#line 303 "Bssizok.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 31;
#line 303 "Bssizok.sqc"
      sql_setdlist[11].sqldata = (void*)btnm;
#line 303 "Bssizok.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 61;
#line 303 "Bssizok.sqc"
      sql_setdlist[12].sqldata = (void*)knjnmkey;
#line 303 "Bssizok.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 41;
#line 303 "Bssizok.sqc"
      sql_setdlist[13].sqldata = (void*)ttinm;
#line 303 "Bssizok.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 303 "Bssizok.sqc"
      sql_setdlist[14].sqldata = (void*)&sbtkbn;
#line 303 "Bssizok.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 303 "Bssizok.sqc"
      sql_setdlist[15].sqldata = (void*)birthday;
#line 303 "Bssizok.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 303 "Bssizok.sqc"
      sql_setdlist[16].sqldata = (void*)&birthdaykbn;
#line 303 "Bssizok.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 4;
#line 303 "Bssizok.sqc"
      sql_setdlist[17].sqldata = (void*)age;
#line 303 "Bssizok.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 303 "Bssizok.sqc"
      sql_setdlist[18].sqldata = (void*)&agekbn;
#line 303 "Bssizok.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 5;
#line 303 "Bssizok.sqc"
      sql_setdlist[19].sqldata = (void*)zrcd;
#line 303 "Bssizok.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 9;
#line 303 "Bssizok.sqc"
      sql_setdlist[20].sqldata = (void*)sstme;
#line 303 "Bssizok.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 11;
#line 303 "Bssizok.sqc"
      sql_setdlist[21].sqldata = (void*)ssymd;
#line 303 "Bssizok.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 5;
#line 303 "Bssizok.sqc"
      sql_setdlist[22].sqldata = (void*)tntme;
#line 303 "Bssizok.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 303 "Bssizok.sqc"
      sql_setdlist[23].sqldata = (void*)&tntni;
#line 303 "Bssizok.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 6;
#line 303 "Bssizok.sqc"
      sql_setdlist[24].sqldata = (void*)tnryo;
#line 303 "Bssizok.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 303 "Bssizok.sqc"
      sql_setdlist[25].sqldata = (void*)&tnryotni;
#line 303 "Bssizok.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 27;
#line 303 "Bssizok.sqc"
      sql_setdlist[26].sqldata = (void*)bshdh;
#line 303 "Bssizok.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 27;
#line 303 "Bssizok.sqc"
      sql_setdlist[27].sqldata = (void*)ksndh;
#line 303 "Bssizok.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 303 "Bssizok.sqc"
      sqlasetdata(3,0,28,sql_setdlist,0L,0L);
    }
#line 303 "Bssizok.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 303 "Bssizok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 303 "Bssizok.sqc"
  sqlastop(0L);
}

#line 303 "Bssizok.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Bssizok*)ZbmlRealloc( array,
                                    sizeof( Bssizok ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Bssizok ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, BssizokArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 318 "Bssizok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 318 "Bssizok.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 318 "Bssizok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 318 "Bssizok.sqc"
  sqlastop(0L);
}

#line 318 "Bssizok.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 326 "Bssizok.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbBssizokInsert()
 *    BSSIZOK レコードを挿入する
 * ■引数
 *    [I]  Bssizok* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbBssizokInsert( Bssizok* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, BssizokArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 349 "Bssizok.sqc"


    
/*
EXEC SQL INSERT INTO BSSIZOK
    (
		UTKYMD,
		IRINO,
		IRIKETFLG,
		BSSINO,
		ECD,
		SSTCD,
		SRKNM,
		KNJNMN,
		NGKBN,
		KRTNO,
		KNJID,
		BTNM,
		KNJNMKEY,
		TTINM,
		SBTKBN,
		BIRTHDAY,
		BIRTHDAYKBN,
		AGE,
		AGEKBN,
		ZRCD,
		SSTME,
		SSYMD,
		TNTME,
		TNTNI,
		TNRYO,
		TNRYOTNI,
		BSHDH,
		KSNDH
    ) VALUES (
		:utkymd,
		:irino,
		:iriketflg,
		:bssino,
		:ecd,
		:sstcd,
		:srknm,
		:knjnmn,
		:ngkbn,
		:krtno,
		:knjid,
		:btnm,
		:knjnmkey,
		:ttinm,
		:sbtkbn,
		:birthday,
		:birthdaykbn,
		:age,
		:agekbn,
		:zrcd,
		:sstme,
		:ssymd,
		:tntme,
		:tntni,
		:tnryo,
		:tnryotni,
		:bshdh,
		:ksndh
    );
*/

{
#line 410 "Bssizok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 410 "Bssizok.sqc"
  sqlaaloc(2,28,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[28];
#line 410 "Bssizok.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 410 "Bssizok.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 410 "Bssizok.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 410 "Bssizok.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 410 "Bssizok.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 410 "Bssizok.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 410 "Bssizok.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 410 "Bssizok.sqc"
      sql_setdlist[3].sqldata = (void*)&bssino;
#line 410 "Bssizok.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 4;
#line 410 "Bssizok.sqc"
      sql_setdlist[4].sqldata = (void*)ecd;
#line 410 "Bssizok.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 410 "Bssizok.sqc"
      sql_setdlist[5].sqldata = (void*)sstcd;
#line 410 "Bssizok.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 31;
#line 410 "Bssizok.sqc"
      sql_setdlist[6].sqldata = (void*)srknm;
#line 410 "Bssizok.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 61;
#line 410 "Bssizok.sqc"
      sql_setdlist[7].sqldata = (void*)knjnmn;
#line 410 "Bssizok.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 410 "Bssizok.sqc"
      sql_setdlist[8].sqldata = (void*)&ngkbn;
#line 410 "Bssizok.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 41;
#line 410 "Bssizok.sqc"
      sql_setdlist[9].sqldata = (void*)krtno;
#line 410 "Bssizok.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 16;
#line 410 "Bssizok.sqc"
      sql_setdlist[10].sqldata = (void*)knjid;
#line 410 "Bssizok.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 31;
#line 410 "Bssizok.sqc"
      sql_setdlist[11].sqldata = (void*)btnm;
#line 410 "Bssizok.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 61;
#line 410 "Bssizok.sqc"
      sql_setdlist[12].sqldata = (void*)knjnmkey;
#line 410 "Bssizok.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 41;
#line 410 "Bssizok.sqc"
      sql_setdlist[13].sqldata = (void*)ttinm;
#line 410 "Bssizok.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 410 "Bssizok.sqc"
      sql_setdlist[14].sqldata = (void*)&sbtkbn;
#line 410 "Bssizok.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 410 "Bssizok.sqc"
      sql_setdlist[15].sqldata = (void*)birthday;
#line 410 "Bssizok.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 410 "Bssizok.sqc"
      sql_setdlist[16].sqldata = (void*)&birthdaykbn;
#line 410 "Bssizok.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 4;
#line 410 "Bssizok.sqc"
      sql_setdlist[17].sqldata = (void*)age;
#line 410 "Bssizok.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 410 "Bssizok.sqc"
      sql_setdlist[18].sqldata = (void*)&agekbn;
#line 410 "Bssizok.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 5;
#line 410 "Bssizok.sqc"
      sql_setdlist[19].sqldata = (void*)zrcd;
#line 410 "Bssizok.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 9;
#line 410 "Bssizok.sqc"
      sql_setdlist[20].sqldata = (void*)sstme;
#line 410 "Bssizok.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 11;
#line 410 "Bssizok.sqc"
      sql_setdlist[21].sqldata = (void*)ssymd;
#line 410 "Bssizok.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 5;
#line 410 "Bssizok.sqc"
      sql_setdlist[22].sqldata = (void*)tntme;
#line 410 "Bssizok.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 410 "Bssizok.sqc"
      sql_setdlist[23].sqldata = (void*)&tntni;
#line 410 "Bssizok.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 6;
#line 410 "Bssizok.sqc"
      sql_setdlist[24].sqldata = (void*)tnryo;
#line 410 "Bssizok.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 410 "Bssizok.sqc"
      sql_setdlist[25].sqldata = (void*)&tnryotni;
#line 410 "Bssizok.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 27;
#line 410 "Bssizok.sqc"
      sql_setdlist[26].sqldata = (void*)bshdh;
#line 410 "Bssizok.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 27;
#line 410 "Bssizok.sqc"
      sql_setdlist[27].sqldata = (void*)ksndh;
#line 410 "Bssizok.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 410 "Bssizok.sqc"
      sqlasetdata(2,0,28,sql_setdlist,0L,0L);
    }
#line 410 "Bssizok.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 410 "Bssizok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 410 "Bssizok.sqc"
  sqlastop(0L);
}

#line 410 "Bssizok.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 415 "Bssizok.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbBssizokUpdate()
 *    BSSIZOK レコードを更新する
 * ■引数
 *    [I]  Bssizok* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbBssizokUpdate( Bssizok* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, BssizokArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 439 "Bssizok.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 440 "Bssizok.sqc"


    
/*
EXEC SQL UPDATE BSSIZOK
    SET (
		IRIKETFLG,
		ECD,
		SSTCD,
		SRKNM,
		KNJNMN,
		NGKBN,
		KRTNO,
		KNJID,
		BTNM,
		KNJNMKEY,
		TTINM,
		SBTKBN,
		BIRTHDAY,
		BIRTHDAYKBN,
		AGE,
		AGEKBN,
		ZRCD,
		SSTME,
		SSYMD,
		TNTME,
		TNTNI,
		TNRYO,
		TNRYOTNI,
		BSHDH,
		KSNDH
    ) = (
		:iriketflg,
		:ecd,
		:sstcd,
		:srknm,
		:knjnmn,
		:ngkbn,
		:krtno,
		:knjid,
		:btnm,
		:knjnmkey,
		:ttinm,
		:sbtkbn,
		:birthday,
		:birthdaykbn,
		:age,
		:agekbn,
		:zrcd,
		:sstme,
		:ssymd,
		:tntme,
		:tntni,
		:tnryo,
		:tnryotni,
		:bshdh,
		:ksndh
    ) WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		BSSINO = :bssino;
*/

{
#line 498 "Bssizok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 498 "Bssizok.sqc"
  sqlaaloc(2,28,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[28];
#line 498 "Bssizok.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 498 "Bssizok.sqc"
      sql_setdlist[0].sqldata = (void*)&iriketflg;
#line 498 "Bssizok.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 4;
#line 498 "Bssizok.sqc"
      sql_setdlist[1].sqldata = (void*)ecd;
#line 498 "Bssizok.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 498 "Bssizok.sqc"
      sql_setdlist[2].sqldata = (void*)sstcd;
#line 498 "Bssizok.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 31;
#line 498 "Bssizok.sqc"
      sql_setdlist[3].sqldata = (void*)srknm;
#line 498 "Bssizok.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 61;
#line 498 "Bssizok.sqc"
      sql_setdlist[4].sqldata = (void*)knjnmn;
#line 498 "Bssizok.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 498 "Bssizok.sqc"
      sql_setdlist[5].sqldata = (void*)&ngkbn;
#line 498 "Bssizok.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 41;
#line 498 "Bssizok.sqc"
      sql_setdlist[6].sqldata = (void*)krtno;
#line 498 "Bssizok.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 16;
#line 498 "Bssizok.sqc"
      sql_setdlist[7].sqldata = (void*)knjid;
#line 498 "Bssizok.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 31;
#line 498 "Bssizok.sqc"
      sql_setdlist[8].sqldata = (void*)btnm;
#line 498 "Bssizok.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 61;
#line 498 "Bssizok.sqc"
      sql_setdlist[9].sqldata = (void*)knjnmkey;
#line 498 "Bssizok.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 41;
#line 498 "Bssizok.sqc"
      sql_setdlist[10].sqldata = (void*)ttinm;
#line 498 "Bssizok.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 498 "Bssizok.sqc"
      sql_setdlist[11].sqldata = (void*)&sbtkbn;
#line 498 "Bssizok.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 498 "Bssizok.sqc"
      sql_setdlist[12].sqldata = (void*)birthday;
#line 498 "Bssizok.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 498 "Bssizok.sqc"
      sql_setdlist[13].sqldata = (void*)&birthdaykbn;
#line 498 "Bssizok.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 4;
#line 498 "Bssizok.sqc"
      sql_setdlist[14].sqldata = (void*)age;
#line 498 "Bssizok.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[15].sqltype = 452; sql_setdlist[15].sqllen = 1;
#line 498 "Bssizok.sqc"
      sql_setdlist[15].sqldata = (void*)&agekbn;
#line 498 "Bssizok.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 5;
#line 498 "Bssizok.sqc"
      sql_setdlist[16].sqldata = (void*)zrcd;
#line 498 "Bssizok.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 9;
#line 498 "Bssizok.sqc"
      sql_setdlist[17].sqldata = (void*)sstme;
#line 498 "Bssizok.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 11;
#line 498 "Bssizok.sqc"
      sql_setdlist[18].sqldata = (void*)ssymd;
#line 498 "Bssizok.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 5;
#line 498 "Bssizok.sqc"
      sql_setdlist[19].sqldata = (void*)tntme;
#line 498 "Bssizok.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 498 "Bssizok.sqc"
      sql_setdlist[20].sqldata = (void*)&tntni;
#line 498 "Bssizok.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 6;
#line 498 "Bssizok.sqc"
      sql_setdlist[21].sqldata = (void*)tnryo;
#line 498 "Bssizok.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 498 "Bssizok.sqc"
      sql_setdlist[22].sqldata = (void*)&tnryotni;
#line 498 "Bssizok.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 27;
#line 498 "Bssizok.sqc"
      sql_setdlist[23].sqldata = (void*)bshdh;
#line 498 "Bssizok.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 27;
#line 498 "Bssizok.sqc"
      sql_setdlist[24].sqldata = (void*)ksndh;
#line 498 "Bssizok.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 11;
#line 498 "Bssizok.sqc"
      sql_setdlist[25].sqldata = (void*)utkymd;
#line 498 "Bssizok.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 12;
#line 498 "Bssizok.sqc"
      sql_setdlist[26].sqldata = (void*)irino;
#line 498 "Bssizok.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sql_setdlist[27].sqltype = 500; sql_setdlist[27].sqllen = 2;
#line 498 "Bssizok.sqc"
      sql_setdlist[27].sqldata = (void*)&bssino;
#line 498 "Bssizok.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 498 "Bssizok.sqc"
      sqlasetdata(2,0,28,sql_setdlist,0L,0L);
    }
#line 498 "Bssizok.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 498 "Bssizok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 498 "Bssizok.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 498 "Bssizok.sqc"
  sqlastop(0L);
}

#line 498 "Bssizok.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 503 "Bssizok.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 507 "Bssizok.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbBssizokDelete()
 *    BSSIZOK レコードを削除する
 * ■引数
 *    [I]  Bssizok* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbBssizokDelete( Bssizok* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, BssizokArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 531 "Bssizok.sqc"


    
/*
EXEC SQL DELETE FROM BSSIZOK
    WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		BSSINO = :bssino;
*/

{
#line 537 "Bssizok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 537 "Bssizok.sqc"
  sqlaaloc(2,3,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 537 "Bssizok.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 537 "Bssizok.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 537 "Bssizok.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 537 "Bssizok.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 537 "Bssizok.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 537 "Bssizok.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 537 "Bssizok.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 537 "Bssizok.sqc"
      sql_setdlist[2].sqldata = (void*)&bssino;
#line 537 "Bssizok.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 537 "Bssizok.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 537 "Bssizok.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 537 "Bssizok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 537 "Bssizok.sqc"
  sqlastop(0L);
}

#line 537 "Bssizok.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 542 "Bssizok.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
