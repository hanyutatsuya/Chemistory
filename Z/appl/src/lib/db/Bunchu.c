static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,99,66,81,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,56,90,66,85,78,67,32,32,0,0,0,0,0,0,0,0,
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


#line 1 "Bunchu.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Bunchu.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Bunchu.h"
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


#line 24 "Bunchu.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Bunchu.sqc"

	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    sriymd[11];
	char    kntno[14];
	char    kntketflg;
	char    smpcd[8];
	char    kmkcd[8];
	short   smpcditno;
	char    chkmj[5];
	char    trid[11];
	short   trpos;
	char    asyrckid[11];
	short   asyrckpos;
	char    id2[11];
	short   id2pos;
	char    sbtkbn;
	char    age[4];
	char    agekbn;
	char    tntme[5];
	char    tntni;
	char    tnryo[6];
	char    tnryotni;
	char    sstcd[8];
	char    ecd[4];
	char    bckid[4];
	char    jtflg;
	char    knssyr;
	char    tknflg;
	char    ttkkflg;
	char    bnckka;
	short   srtkey;
	char    ksndh[27];
	char    trkdh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 65 "Bunchu.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Bunchu

BmlDMMInfo	BunchuArray[] = {
	DMM_SDATE( utkymd ),
	DMM_SSTRING( irino ),
	DMM_SCHAR( iriketflg ),
	DMM_SSHORT( zssdino ),
	DMM_SDATE( sriymd ),
	DMM_SSTRING( kntno ),
	DMM_SCHAR( kntketflg ),
	DMM_SSTRING( smpcd ),
	DMM_SSTRING( kmkcd ),
	DMM_SSHORT( smpcditno ),
	DMM_SSTRING( chkmj ),
	DMM_SSTRING( trid ),
	DMM_SSHORT( trpos ),
	DMM_SSTRING( asyrckid ),
	DMM_SSHORT( asyrckpos ),
	DMM_SSTRING( id2 ),
	DMM_SSHORT( id2pos ),
	DMM_SCHAR( sbtkbn ),
	DMM_SSTRING( age ),
	DMM_SCHAR( agekbn ),
	DMM_SSTRING( tntme ),
	DMM_SCHAR( tntni ),
	DMM_SSTRING( tnryo ),
	DMM_SCHAR( tnryotni ),
	DMM_SSTRING( sstcd ),
	DMM_SSTRING( ecd ),
	DMM_SSTRING( bckid ),
	DMM_SCHAR( jtflg ),
	DMM_SCHAR( knssyr ),
	DMM_SCHAR( tknflg ),
	DMM_SCHAR( ttkkflg ),
	DMM_SCHAR( bnckka ),
	DMM_SSHORT( srtkey ),
	DMM_STIMESTAMP( ksndh ),
	DMM_STIMESTAMP( trkdh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbBunchuSelectAll()
 *    BUNCHU レコード全件取得
 * ■引数
 *    [O]  Bunchu** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbBunchuSelectAll( Bunchu** arrayOut, int* numOut )
{
    Bunchu*     array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 128 "Bunchu.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		SMPCD,
		KMKCD,
		SMPCDITNO,
		CHKMJ,
		TRID,
		TRPOS,
		ASYRCKID,
		ASYRCKPOS,
		ID2,
		ID2POS,
		SBTKBN,
		AGE,
		AGEKBN,
		TNTME,
		TNTNI,
		TNRYO,
		TNRYOTNI,
		SSTCD,
		ECD,
		BCKID,
		JTFLG,
		KNSSYR,
		TKNFLG,
		TTKKFLG,
		BNCKKA,
		SRTKEY,
		KSNDH,
		TRKDH
    FROM
        BUNCHU FOR READ ONLY;
*/

#line 168 "Bunchu.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 170 "Bunchu.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 170 "Bunchu.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 170 "Bunchu.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 170 "Bunchu.sqc"
  sqlastop(0L);
}

#line 170 "Bunchu.sqc"


    while( 1 ) {
        Bunchu* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:sriymd,
			:kntno,
			:kntketflg,
			:smpcd,
			:kmkcd,
			:smpcditno,
			:chkmj,
			:trid,
			:trpos,
			:asyrckid,
			:asyrckpos,
			:id2,
			:id2pos,
			:sbtkbn,
			:age,
			:agekbn,
			:tntme,
			:tntni,
			:tnryo,
			:tnryotni,
			:sstcd,
			:ecd,
			:bckid,
			:jtflg,
			:knssyr,
			:tknflg,
			:ttkkflg,
			:bnckka,
			:srtkey,
			:ksndh,
			:trkdh;
*/

{
#line 210 "Bunchu.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 210 "Bunchu.sqc"
  sqlaaloc(3,35,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[35];
#line 210 "Bunchu.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 210 "Bunchu.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 210 "Bunchu.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 210 "Bunchu.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 210 "Bunchu.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 210 "Bunchu.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 210 "Bunchu.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 210 "Bunchu.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 210 "Bunchu.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 210 "Bunchu.sqc"
      sql_setdlist[4].sqldata = (void*)sriymd;
#line 210 "Bunchu.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 14;
#line 210 "Bunchu.sqc"
      sql_setdlist[5].sqldata = (void*)kntno;
#line 210 "Bunchu.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 210 "Bunchu.sqc"
      sql_setdlist[6].sqldata = (void*)&kntketflg;
#line 210 "Bunchu.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 8;
#line 210 "Bunchu.sqc"
      sql_setdlist[7].sqldata = (void*)smpcd;
#line 210 "Bunchu.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 8;
#line 210 "Bunchu.sqc"
      sql_setdlist[8].sqldata = (void*)kmkcd;
#line 210 "Bunchu.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 210 "Bunchu.sqc"
      sql_setdlist[9].sqldata = (void*)&smpcditno;
#line 210 "Bunchu.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 5;
#line 210 "Bunchu.sqc"
      sql_setdlist[10].sqldata = (void*)chkmj;
#line 210 "Bunchu.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 210 "Bunchu.sqc"
      sql_setdlist[11].sqldata = (void*)trid;
#line 210 "Bunchu.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 210 "Bunchu.sqc"
      sql_setdlist[12].sqldata = (void*)&trpos;
#line 210 "Bunchu.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 210 "Bunchu.sqc"
      sql_setdlist[13].sqldata = (void*)asyrckid;
#line 210 "Bunchu.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 210 "Bunchu.sqc"
      sql_setdlist[14].sqldata = (void*)&asyrckpos;
#line 210 "Bunchu.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 11;
#line 210 "Bunchu.sqc"
      sql_setdlist[15].sqldata = (void*)id2;
#line 210 "Bunchu.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[16].sqltype = 500; sql_setdlist[16].sqllen = 2;
#line 210 "Bunchu.sqc"
      sql_setdlist[16].sqldata = (void*)&id2pos;
#line 210 "Bunchu.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 210 "Bunchu.sqc"
      sql_setdlist[17].sqldata = (void*)&sbtkbn;
#line 210 "Bunchu.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 4;
#line 210 "Bunchu.sqc"
      sql_setdlist[18].sqldata = (void*)age;
#line 210 "Bunchu.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 210 "Bunchu.sqc"
      sql_setdlist[19].sqldata = (void*)&agekbn;
#line 210 "Bunchu.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 5;
#line 210 "Bunchu.sqc"
      sql_setdlist[20].sqldata = (void*)tntme;
#line 210 "Bunchu.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 210 "Bunchu.sqc"
      sql_setdlist[21].sqldata = (void*)&tntni;
#line 210 "Bunchu.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 6;
#line 210 "Bunchu.sqc"
      sql_setdlist[22].sqldata = (void*)tnryo;
#line 210 "Bunchu.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 210 "Bunchu.sqc"
      sql_setdlist[23].sqldata = (void*)&tnryotni;
#line 210 "Bunchu.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 8;
#line 210 "Bunchu.sqc"
      sql_setdlist[24].sqldata = (void*)sstcd;
#line 210 "Bunchu.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 4;
#line 210 "Bunchu.sqc"
      sql_setdlist[25].sqldata = (void*)ecd;
#line 210 "Bunchu.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 4;
#line 210 "Bunchu.sqc"
      sql_setdlist[26].sqldata = (void*)bckid;
#line 210 "Bunchu.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 210 "Bunchu.sqc"
      sql_setdlist[27].sqldata = (void*)&jtflg;
#line 210 "Bunchu.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 210 "Bunchu.sqc"
      sql_setdlist[28].sqldata = (void*)&knssyr;
#line 210 "Bunchu.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 210 "Bunchu.sqc"
      sql_setdlist[29].sqldata = (void*)&tknflg;
#line 210 "Bunchu.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 210 "Bunchu.sqc"
      sql_setdlist[30].sqldata = (void*)&ttkkflg;
#line 210 "Bunchu.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 210 "Bunchu.sqc"
      sql_setdlist[31].sqldata = (void*)&bnckka;
#line 210 "Bunchu.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[32].sqltype = 500; sql_setdlist[32].sqllen = 2;
#line 210 "Bunchu.sqc"
      sql_setdlist[32].sqldata = (void*)&srtkey;
#line 210 "Bunchu.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 27;
#line 210 "Bunchu.sqc"
      sql_setdlist[33].sqldata = (void*)ksndh;
#line 210 "Bunchu.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 27;
#line 210 "Bunchu.sqc"
      sql_setdlist[34].sqldata = (void*)trkdh;
#line 210 "Bunchu.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 210 "Bunchu.sqc"
      sqlasetdata(3,0,35,sql_setdlist,0L,0L);
    }
#line 210 "Bunchu.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 210 "Bunchu.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 210 "Bunchu.sqc"
  sqlastop(0L);
}

#line 210 "Bunchu.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Bunchu*)ZbmlRealloc( array,
                                    sizeof( Bunchu ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Bunchu ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, BunchuArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 225 "Bunchu.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 225 "Bunchu.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 225 "Bunchu.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 225 "Bunchu.sqc"
  sqlastop(0L);
}

#line 225 "Bunchu.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 233 "Bunchu.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbBunchuSelectKey()
 *    BUNCHU レコードKey条件取得
 * ■引数
 *    [I]  Bunchu* pKey       取得するレコードのキー
 *    [O]  Bunchu** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbBunchuSelectKey( Bunchu* pKey, Bunchu** arrayOut, int* numOut )
{
    Bunchu*     array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, BunchuArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 259 "Bunchu.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		SMPCD,
		KMKCD,
		SMPCDITNO,
		CHKMJ,
		TRID,
		TRPOS,
		ASYRCKID,
		ASYRCKPOS,
		ID2,
		ID2POS,
		SBTKBN,
		AGE,
		AGEKBN,
		TNTME,
		TNTNI,
		TNRYO,
		TNRYOTNI,
		SSTCD,
		ECD,
		BCKID,
		JTFLG,
		KNSSYR,
		TKNFLG,
		TTKKFLG,
		BNCKKA,
		SRTKEY,
		KSNDH,
		TRKDH
    FROM
        BUNCHU
    WHERE
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		SMPCD = :smpcd AND
		KMKCD = :kmkcd FOR READ ONLY;
*/

#line 304 "Bunchu.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 306 "Bunchu.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 306 "Bunchu.sqc"
  sqlaaloc(2,4,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 306 "Bunchu.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 306 "Bunchu.sqc"
      sql_setdlist[0].sqldata = (void*)sriymd;
#line 306 "Bunchu.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 306 "Bunchu.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 14;
#line 306 "Bunchu.sqc"
      sql_setdlist[1].sqldata = (void*)kntno;
#line 306 "Bunchu.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 306 "Bunchu.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 306 "Bunchu.sqc"
      sql_setdlist[2].sqldata = (void*)smpcd;
#line 306 "Bunchu.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 306 "Bunchu.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 306 "Bunchu.sqc"
      sql_setdlist[3].sqldata = (void*)kmkcd;
#line 306 "Bunchu.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 306 "Bunchu.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 306 "Bunchu.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 306 "Bunchu.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 306 "Bunchu.sqc"
  sqlastop(0L);
}

#line 306 "Bunchu.sqc"


    while( 1 ) {
        Bunchu* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:sriymd,
			:kntno,
			:kntketflg,
			:smpcd,
			:kmkcd,
			:smpcditno,
			:chkmj,
			:trid,
			:trpos,
			:asyrckid,
			:asyrckpos,
			:id2,
			:id2pos,
			:sbtkbn,
			:age,
			:agekbn,
			:tntme,
			:tntni,
			:tnryo,
			:tnryotni,
			:sstcd,
			:ecd,
			:bckid,
			:jtflg,
			:knssyr,
			:tknflg,
			:ttkkflg,
			:bnckka,
			:srtkey,
			:ksndh,
			:trkdh;
*/

{
#line 346 "Bunchu.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 346 "Bunchu.sqc"
  sqlaaloc(3,35,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[35];
#line 346 "Bunchu.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 346 "Bunchu.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 346 "Bunchu.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 346 "Bunchu.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 346 "Bunchu.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 346 "Bunchu.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 346 "Bunchu.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 346 "Bunchu.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 346 "Bunchu.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 346 "Bunchu.sqc"
      sql_setdlist[4].sqldata = (void*)sriymd;
#line 346 "Bunchu.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 14;
#line 346 "Bunchu.sqc"
      sql_setdlist[5].sqldata = (void*)kntno;
#line 346 "Bunchu.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 346 "Bunchu.sqc"
      sql_setdlist[6].sqldata = (void*)&kntketflg;
#line 346 "Bunchu.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 8;
#line 346 "Bunchu.sqc"
      sql_setdlist[7].sqldata = (void*)smpcd;
#line 346 "Bunchu.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 8;
#line 346 "Bunchu.sqc"
      sql_setdlist[8].sqldata = (void*)kmkcd;
#line 346 "Bunchu.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 346 "Bunchu.sqc"
      sql_setdlist[9].sqldata = (void*)&smpcditno;
#line 346 "Bunchu.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 5;
#line 346 "Bunchu.sqc"
      sql_setdlist[10].sqldata = (void*)chkmj;
#line 346 "Bunchu.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 346 "Bunchu.sqc"
      sql_setdlist[11].sqldata = (void*)trid;
#line 346 "Bunchu.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 346 "Bunchu.sqc"
      sql_setdlist[12].sqldata = (void*)&trpos;
#line 346 "Bunchu.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 346 "Bunchu.sqc"
      sql_setdlist[13].sqldata = (void*)asyrckid;
#line 346 "Bunchu.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 346 "Bunchu.sqc"
      sql_setdlist[14].sqldata = (void*)&asyrckpos;
#line 346 "Bunchu.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 11;
#line 346 "Bunchu.sqc"
      sql_setdlist[15].sqldata = (void*)id2;
#line 346 "Bunchu.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[16].sqltype = 500; sql_setdlist[16].sqllen = 2;
#line 346 "Bunchu.sqc"
      sql_setdlist[16].sqldata = (void*)&id2pos;
#line 346 "Bunchu.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 346 "Bunchu.sqc"
      sql_setdlist[17].sqldata = (void*)&sbtkbn;
#line 346 "Bunchu.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 4;
#line 346 "Bunchu.sqc"
      sql_setdlist[18].sqldata = (void*)age;
#line 346 "Bunchu.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 346 "Bunchu.sqc"
      sql_setdlist[19].sqldata = (void*)&agekbn;
#line 346 "Bunchu.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 5;
#line 346 "Bunchu.sqc"
      sql_setdlist[20].sqldata = (void*)tntme;
#line 346 "Bunchu.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 346 "Bunchu.sqc"
      sql_setdlist[21].sqldata = (void*)&tntni;
#line 346 "Bunchu.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 6;
#line 346 "Bunchu.sqc"
      sql_setdlist[22].sqldata = (void*)tnryo;
#line 346 "Bunchu.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 346 "Bunchu.sqc"
      sql_setdlist[23].sqldata = (void*)&tnryotni;
#line 346 "Bunchu.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 8;
#line 346 "Bunchu.sqc"
      sql_setdlist[24].sqldata = (void*)sstcd;
#line 346 "Bunchu.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 4;
#line 346 "Bunchu.sqc"
      sql_setdlist[25].sqldata = (void*)ecd;
#line 346 "Bunchu.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 4;
#line 346 "Bunchu.sqc"
      sql_setdlist[26].sqldata = (void*)bckid;
#line 346 "Bunchu.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 346 "Bunchu.sqc"
      sql_setdlist[27].sqldata = (void*)&jtflg;
#line 346 "Bunchu.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 346 "Bunchu.sqc"
      sql_setdlist[28].sqldata = (void*)&knssyr;
#line 346 "Bunchu.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 346 "Bunchu.sqc"
      sql_setdlist[29].sqldata = (void*)&tknflg;
#line 346 "Bunchu.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 346 "Bunchu.sqc"
      sql_setdlist[30].sqldata = (void*)&ttkkflg;
#line 346 "Bunchu.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 346 "Bunchu.sqc"
      sql_setdlist[31].sqldata = (void*)&bnckka;
#line 346 "Bunchu.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[32].sqltype = 500; sql_setdlist[32].sqllen = 2;
#line 346 "Bunchu.sqc"
      sql_setdlist[32].sqldata = (void*)&srtkey;
#line 346 "Bunchu.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 27;
#line 346 "Bunchu.sqc"
      sql_setdlist[33].sqldata = (void*)ksndh;
#line 346 "Bunchu.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 27;
#line 346 "Bunchu.sqc"
      sql_setdlist[34].sqldata = (void*)trkdh;
#line 346 "Bunchu.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 346 "Bunchu.sqc"
      sqlasetdata(3,0,35,sql_setdlist,0L,0L);
    }
#line 346 "Bunchu.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 346 "Bunchu.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 346 "Bunchu.sqc"
  sqlastop(0L);
}

#line 346 "Bunchu.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Bunchu*)ZbmlRealloc( array,
                                    sizeof( Bunchu ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Bunchu ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, BunchuArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 361 "Bunchu.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 361 "Bunchu.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 361 "Bunchu.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 361 "Bunchu.sqc"
  sqlastop(0L);
}

#line 361 "Bunchu.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 369 "Bunchu.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbBunchuInsert()
 *    BUNCHU レコードを挿入する
 * ■引数
 *    [I]  Bunchu* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbBunchuInsert( Bunchu* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, BunchuArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 392 "Bunchu.sqc"


    
/*
EXEC SQL INSERT INTO BUNCHU
    (
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		SMPCD,
		KMKCD,
		SMPCDITNO,
		CHKMJ,
		TRID,
		TRPOS,
		ASYRCKID,
		ASYRCKPOS,
		ID2,
		ID2POS,
		SBTKBN,
		AGE,
		AGEKBN,
		TNTME,
		TNTNI,
		TNRYO,
		TNRYOTNI,
		SSTCD,
		ECD,
		BCKID,
		JTFLG,
		KNSSYR,
		TKNFLG,
		TTKKFLG,
		BNCKKA,
		SRTKEY,
		KSNDH,
		TRKDH
    ) VALUES (
		:utkymd,
		:irino,
		:iriketflg,
		:zssdino,
		:sriymd,
		:kntno,
		:kntketflg,
		:smpcd,
		:kmkcd,
		:smpcditno,
		:chkmj,
		:trid,
		:trpos,
		:asyrckid,
		:asyrckpos,
		:id2,
		:id2pos,
		:sbtkbn,
		:age,
		:agekbn,
		:tntme,
		:tntni,
		:tnryo,
		:tnryotni,
		:sstcd,
		:ecd,
		:bckid,
		:jtflg,
		:knssyr,
		:tknflg,
		:ttkkflg,
		:bnckka,
		:srtkey,
		CURRENT TIMESTAMP,
		CURRENT TIMESTAMP
    );
*/

{
#line 467 "Bunchu.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 467 "Bunchu.sqc"
  sqlaaloc(2,33,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[33];
#line 467 "Bunchu.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 467 "Bunchu.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 467 "Bunchu.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 467 "Bunchu.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 467 "Bunchu.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 467 "Bunchu.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 467 "Bunchu.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 467 "Bunchu.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 467 "Bunchu.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 467 "Bunchu.sqc"
      sql_setdlist[4].sqldata = (void*)sriymd;
#line 467 "Bunchu.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 14;
#line 467 "Bunchu.sqc"
      sql_setdlist[5].sqldata = (void*)kntno;
#line 467 "Bunchu.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 467 "Bunchu.sqc"
      sql_setdlist[6].sqldata = (void*)&kntketflg;
#line 467 "Bunchu.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 8;
#line 467 "Bunchu.sqc"
      sql_setdlist[7].sqldata = (void*)smpcd;
#line 467 "Bunchu.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 8;
#line 467 "Bunchu.sqc"
      sql_setdlist[8].sqldata = (void*)kmkcd;
#line 467 "Bunchu.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 467 "Bunchu.sqc"
      sql_setdlist[9].sqldata = (void*)&smpcditno;
#line 467 "Bunchu.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 5;
#line 467 "Bunchu.sqc"
      sql_setdlist[10].sqldata = (void*)chkmj;
#line 467 "Bunchu.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 467 "Bunchu.sqc"
      sql_setdlist[11].sqldata = (void*)trid;
#line 467 "Bunchu.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 467 "Bunchu.sqc"
      sql_setdlist[12].sqldata = (void*)&trpos;
#line 467 "Bunchu.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 467 "Bunchu.sqc"
      sql_setdlist[13].sqldata = (void*)asyrckid;
#line 467 "Bunchu.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 467 "Bunchu.sqc"
      sql_setdlist[14].sqldata = (void*)&asyrckpos;
#line 467 "Bunchu.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 11;
#line 467 "Bunchu.sqc"
      sql_setdlist[15].sqldata = (void*)id2;
#line 467 "Bunchu.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[16].sqltype = 500; sql_setdlist[16].sqllen = 2;
#line 467 "Bunchu.sqc"
      sql_setdlist[16].sqldata = (void*)&id2pos;
#line 467 "Bunchu.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 467 "Bunchu.sqc"
      sql_setdlist[17].sqldata = (void*)&sbtkbn;
#line 467 "Bunchu.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 4;
#line 467 "Bunchu.sqc"
      sql_setdlist[18].sqldata = (void*)age;
#line 467 "Bunchu.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 467 "Bunchu.sqc"
      sql_setdlist[19].sqldata = (void*)&agekbn;
#line 467 "Bunchu.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 5;
#line 467 "Bunchu.sqc"
      sql_setdlist[20].sqldata = (void*)tntme;
#line 467 "Bunchu.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 467 "Bunchu.sqc"
      sql_setdlist[21].sqldata = (void*)&tntni;
#line 467 "Bunchu.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 6;
#line 467 "Bunchu.sqc"
      sql_setdlist[22].sqldata = (void*)tnryo;
#line 467 "Bunchu.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 467 "Bunchu.sqc"
      sql_setdlist[23].sqldata = (void*)&tnryotni;
#line 467 "Bunchu.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 8;
#line 467 "Bunchu.sqc"
      sql_setdlist[24].sqldata = (void*)sstcd;
#line 467 "Bunchu.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 4;
#line 467 "Bunchu.sqc"
      sql_setdlist[25].sqldata = (void*)ecd;
#line 467 "Bunchu.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 4;
#line 467 "Bunchu.sqc"
      sql_setdlist[26].sqldata = (void*)bckid;
#line 467 "Bunchu.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 467 "Bunchu.sqc"
      sql_setdlist[27].sqldata = (void*)&jtflg;
#line 467 "Bunchu.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 467 "Bunchu.sqc"
      sql_setdlist[28].sqldata = (void*)&knssyr;
#line 467 "Bunchu.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 467 "Bunchu.sqc"
      sql_setdlist[29].sqldata = (void*)&tknflg;
#line 467 "Bunchu.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 467 "Bunchu.sqc"
      sql_setdlist[30].sqldata = (void*)&ttkkflg;
#line 467 "Bunchu.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 467 "Bunchu.sqc"
      sql_setdlist[31].sqldata = (void*)&bnckka;
#line 467 "Bunchu.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sql_setdlist[32].sqltype = 500; sql_setdlist[32].sqllen = 2;
#line 467 "Bunchu.sqc"
      sql_setdlist[32].sqldata = (void*)&srtkey;
#line 467 "Bunchu.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 467 "Bunchu.sqc"
      sqlasetdata(2,0,33,sql_setdlist,0L,0L);
    }
#line 467 "Bunchu.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 467 "Bunchu.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 467 "Bunchu.sqc"
  sqlastop(0L);
}

#line 467 "Bunchu.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 472 "Bunchu.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbBunchuUpdate()
 *    BUNCHU レコードを更新する
 * ■引数
 *    [I]  Bunchu* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbBunchuUpdate( Bunchu* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, BunchuArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 496 "Bunchu.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 497 "Bunchu.sqc"


    
/*
EXEC SQL UPDATE BUNCHU
    SET (
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		KNTKETFLG,
		SMPCDITNO,
		CHKMJ,
		TRID,
		TRPOS,
		ASYRCKID,
		ASYRCKPOS,
		ID2,
		ID2POS,
		SBTKBN,
		AGE,
		AGEKBN,
		TNTME,
		TNTNI,
		TNRYO,
		TNRYOTNI,
		SSTCD,
		ECD,
		BCKID,
		JTFLG,
		KNSSYR,
		TKNFLG,
		TTKKFLG,
		BNCKKA,
		SRTKEY,
		KSNDH,
		TRKDH
    ) = (
		:utkymd,
		:irino,
		:iriketflg,
		:zssdino,
		:kntketflg,
		:smpcditno,
		:chkmj,
		:trid,
		:trpos,
		:asyrckid,
		:asyrckpos,
		:id2,
		:id2pos,
		:sbtkbn,
		:age,
		:agekbn,
		:tntme,
		:tntni,
		:tnryo,
		:tnryotni,
		:sstcd,
		:ecd,
		:bckid,
		:jtflg,
		:knssyr,
		:tknflg,
		:ttkkflg,
		:bnckka,
		:srtkey,
		CURRENT TIMESTAMP,
		:trkdh
    ) WHERE
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		SMPCD = :smpcd AND
		KMKCD = :kmkcd;
*/

{
#line 568 "Bunchu.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 568 "Bunchu.sqc"
  sqlaaloc(2,34,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[34];
#line 568 "Bunchu.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 568 "Bunchu.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 568 "Bunchu.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 568 "Bunchu.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 568 "Bunchu.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 568 "Bunchu.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 568 "Bunchu.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 568 "Bunchu.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 568 "Bunchu.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 568 "Bunchu.sqc"
      sql_setdlist[4].sqldata = (void*)&kntketflg;
#line 568 "Bunchu.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 568 "Bunchu.sqc"
      sql_setdlist[5].sqldata = (void*)&smpcditno;
#line 568 "Bunchu.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 5;
#line 568 "Bunchu.sqc"
      sql_setdlist[6].sqldata = (void*)chkmj;
#line 568 "Bunchu.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 568 "Bunchu.sqc"
      sql_setdlist[7].sqldata = (void*)trid;
#line 568 "Bunchu.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 568 "Bunchu.sqc"
      sql_setdlist[8].sqldata = (void*)&trpos;
#line 568 "Bunchu.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 568 "Bunchu.sqc"
      sql_setdlist[9].sqldata = (void*)asyrckid;
#line 568 "Bunchu.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[10].sqltype = 500; sql_setdlist[10].sqllen = 2;
#line 568 "Bunchu.sqc"
      sql_setdlist[10].sqldata = (void*)&asyrckpos;
#line 568 "Bunchu.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 568 "Bunchu.sqc"
      sql_setdlist[11].sqldata = (void*)id2;
#line 568 "Bunchu.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 568 "Bunchu.sqc"
      sql_setdlist[12].sqldata = (void*)&id2pos;
#line 568 "Bunchu.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 568 "Bunchu.sqc"
      sql_setdlist[13].sqldata = (void*)&sbtkbn;
#line 568 "Bunchu.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 4;
#line 568 "Bunchu.sqc"
      sql_setdlist[14].sqldata = (void*)age;
#line 568 "Bunchu.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[15].sqltype = 452; sql_setdlist[15].sqllen = 1;
#line 568 "Bunchu.sqc"
      sql_setdlist[15].sqldata = (void*)&agekbn;
#line 568 "Bunchu.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 5;
#line 568 "Bunchu.sqc"
      sql_setdlist[16].sqldata = (void*)tntme;
#line 568 "Bunchu.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 568 "Bunchu.sqc"
      sql_setdlist[17].sqldata = (void*)&tntni;
#line 568 "Bunchu.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 6;
#line 568 "Bunchu.sqc"
      sql_setdlist[18].sqldata = (void*)tnryo;
#line 568 "Bunchu.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 568 "Bunchu.sqc"
      sql_setdlist[19].sqldata = (void*)&tnryotni;
#line 568 "Bunchu.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 8;
#line 568 "Bunchu.sqc"
      sql_setdlist[20].sqldata = (void*)sstcd;
#line 568 "Bunchu.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 4;
#line 568 "Bunchu.sqc"
      sql_setdlist[21].sqldata = (void*)ecd;
#line 568 "Bunchu.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 4;
#line 568 "Bunchu.sqc"
      sql_setdlist[22].sqldata = (void*)bckid;
#line 568 "Bunchu.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 568 "Bunchu.sqc"
      sql_setdlist[23].sqldata = (void*)&jtflg;
#line 568 "Bunchu.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 568 "Bunchu.sqc"
      sql_setdlist[24].sqldata = (void*)&knssyr;
#line 568 "Bunchu.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 568 "Bunchu.sqc"
      sql_setdlist[25].sqldata = (void*)&tknflg;
#line 568 "Bunchu.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 568 "Bunchu.sqc"
      sql_setdlist[26].sqldata = (void*)&ttkkflg;
#line 568 "Bunchu.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 568 "Bunchu.sqc"
      sql_setdlist[27].sqldata = (void*)&bnckka;
#line 568 "Bunchu.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[28].sqltype = 500; sql_setdlist[28].sqllen = 2;
#line 568 "Bunchu.sqc"
      sql_setdlist[28].sqldata = (void*)&srtkey;
#line 568 "Bunchu.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 568 "Bunchu.sqc"
      sql_setdlist[29].sqldata = (void*)trkdh;
#line 568 "Bunchu.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 11;
#line 568 "Bunchu.sqc"
      sql_setdlist[30].sqldata = (void*)sriymd;
#line 568 "Bunchu.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 14;
#line 568 "Bunchu.sqc"
      sql_setdlist[31].sqldata = (void*)kntno;
#line 568 "Bunchu.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 8;
#line 568 "Bunchu.sqc"
      sql_setdlist[32].sqldata = (void*)smpcd;
#line 568 "Bunchu.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 8;
#line 568 "Bunchu.sqc"
      sql_setdlist[33].sqldata = (void*)kmkcd;
#line 568 "Bunchu.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 568 "Bunchu.sqc"
      sqlasetdata(2,0,34,sql_setdlist,0L,0L);
    }
#line 568 "Bunchu.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 568 "Bunchu.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 568 "Bunchu.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 568 "Bunchu.sqc"
  sqlastop(0L);
}

#line 568 "Bunchu.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 573 "Bunchu.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 577 "Bunchu.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbBunchuDelete()
 *    BUNCHU レコードを削除する
 * ■引数
 *    [I]  Bunchu* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbBunchuDelete( Bunchu* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, BunchuArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 601 "Bunchu.sqc"


    
/*
EXEC SQL DELETE FROM BUNCHU
    WHERE
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		SMPCD = :smpcd AND
		KMKCD = :kmkcd;
*/

{
#line 608 "Bunchu.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 608 "Bunchu.sqc"
  sqlaaloc(2,4,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 608 "Bunchu.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 608 "Bunchu.sqc"
      sql_setdlist[0].sqldata = (void*)sriymd;
#line 608 "Bunchu.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 608 "Bunchu.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 14;
#line 608 "Bunchu.sqc"
      sql_setdlist[1].sqldata = (void*)kntno;
#line 608 "Bunchu.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 608 "Bunchu.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 608 "Bunchu.sqc"
      sql_setdlist[2].sqldata = (void*)smpcd;
#line 608 "Bunchu.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 608 "Bunchu.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 608 "Bunchu.sqc"
      sql_setdlist[3].sqldata = (void*)kmkcd;
#line 608 "Bunchu.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 608 "Bunchu.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 608 "Bunchu.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 608 "Bunchu.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 608 "Bunchu.sqc"
  sqlastop(0L);
}

#line 608 "Bunchu.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 613 "Bunchu.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
