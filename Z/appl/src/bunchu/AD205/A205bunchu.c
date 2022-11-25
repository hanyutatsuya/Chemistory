static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,82,65,117,85,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,65,50,48,53,66,85,78,67,0,0,0,0,0,0,0,0,
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


#line 1 "A205bunchu.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： A205bunchu.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 *  2.01     2007-02-23                    Update WHEREにUTKYMD追加
 *  2.02     2007-05-08                    Update ABunSelAllKey関数追加
 **********************************************************************/
#include <stdio.h>

#include "A205bunchu.h"
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


#line 26 "A205bunchu.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 31 "A205bunchu.sqc"

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

#line 67 "A205bunchu.sqc"



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
long ABunSelKey( Bunchu* pKey, Bunchu** arrayOut, int* numOut )
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

#line 137 "A205bunchu.sqc"


    
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
		IRINO = :irino AND
		UTKYMD = :utkymd AND		-- 2.01 ADD
		SMPCD = :smpcd AND
		KMKCD = :kmkcd AND
		BNCKKA != '1' AND
		SRIYMD = :sriymd
		FOR READ ONLY;
*/

#line 185 "A205bunchu.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 187 "A205bunchu.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 187 "A205bunchu.sqc"
  sqlaaloc(2,5,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 187 "A205bunchu.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 12;
#line 187 "A205bunchu.sqc"
      sql_setdlist[0].sqldata = (void*)irino;
#line 187 "A205bunchu.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 187 "A205bunchu.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 187 "A205bunchu.sqc"
      sql_setdlist[1].sqldata = (void*)utkymd;
#line 187 "A205bunchu.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 187 "A205bunchu.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 187 "A205bunchu.sqc"
      sql_setdlist[2].sqldata = (void*)smpcd;
#line 187 "A205bunchu.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 187 "A205bunchu.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 187 "A205bunchu.sqc"
      sql_setdlist[3].sqldata = (void*)kmkcd;
#line 187 "A205bunchu.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 187 "A205bunchu.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 187 "A205bunchu.sqc"
      sql_setdlist[4].sqldata = (void*)sriymd;
#line 187 "A205bunchu.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 187 "A205bunchu.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 187 "A205bunchu.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 187 "A205bunchu.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 187 "A205bunchu.sqc"
  sqlastop(0L);
}

#line 187 "A205bunchu.sqc"


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
#line 227 "A205bunchu.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 227 "A205bunchu.sqc"
  sqlaaloc(3,35,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[35];
#line 227 "A205bunchu.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 227 "A205bunchu.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 227 "A205bunchu.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 227 "A205bunchu.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 227 "A205bunchu.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 227 "A205bunchu.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 227 "A205bunchu.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 227 "A205bunchu.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 227 "A205bunchu.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 227 "A205bunchu.sqc"
      sql_setdlist[4].sqldata = (void*)sriymd;
#line 227 "A205bunchu.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 14;
#line 227 "A205bunchu.sqc"
      sql_setdlist[5].sqldata = (void*)kntno;
#line 227 "A205bunchu.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 227 "A205bunchu.sqc"
      sql_setdlist[6].sqldata = (void*)&kntketflg;
#line 227 "A205bunchu.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 8;
#line 227 "A205bunchu.sqc"
      sql_setdlist[7].sqldata = (void*)smpcd;
#line 227 "A205bunchu.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 8;
#line 227 "A205bunchu.sqc"
      sql_setdlist[8].sqldata = (void*)kmkcd;
#line 227 "A205bunchu.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 227 "A205bunchu.sqc"
      sql_setdlist[9].sqldata = (void*)&smpcditno;
#line 227 "A205bunchu.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 5;
#line 227 "A205bunchu.sqc"
      sql_setdlist[10].sqldata = (void*)chkmj;
#line 227 "A205bunchu.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 227 "A205bunchu.sqc"
      sql_setdlist[11].sqldata = (void*)trid;
#line 227 "A205bunchu.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 227 "A205bunchu.sqc"
      sql_setdlist[12].sqldata = (void*)&trpos;
#line 227 "A205bunchu.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 227 "A205bunchu.sqc"
      sql_setdlist[13].sqldata = (void*)asyrckid;
#line 227 "A205bunchu.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 227 "A205bunchu.sqc"
      sql_setdlist[14].sqldata = (void*)&asyrckpos;
#line 227 "A205bunchu.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 11;
#line 227 "A205bunchu.sqc"
      sql_setdlist[15].sqldata = (void*)id2;
#line 227 "A205bunchu.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[16].sqltype = 500; sql_setdlist[16].sqllen = 2;
#line 227 "A205bunchu.sqc"
      sql_setdlist[16].sqldata = (void*)&id2pos;
#line 227 "A205bunchu.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 227 "A205bunchu.sqc"
      sql_setdlist[17].sqldata = (void*)&sbtkbn;
#line 227 "A205bunchu.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 4;
#line 227 "A205bunchu.sqc"
      sql_setdlist[18].sqldata = (void*)age;
#line 227 "A205bunchu.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 227 "A205bunchu.sqc"
      sql_setdlist[19].sqldata = (void*)&agekbn;
#line 227 "A205bunchu.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 5;
#line 227 "A205bunchu.sqc"
      sql_setdlist[20].sqldata = (void*)tntme;
#line 227 "A205bunchu.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 227 "A205bunchu.sqc"
      sql_setdlist[21].sqldata = (void*)&tntni;
#line 227 "A205bunchu.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 6;
#line 227 "A205bunchu.sqc"
      sql_setdlist[22].sqldata = (void*)tnryo;
#line 227 "A205bunchu.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 227 "A205bunchu.sqc"
      sql_setdlist[23].sqldata = (void*)&tnryotni;
#line 227 "A205bunchu.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 8;
#line 227 "A205bunchu.sqc"
      sql_setdlist[24].sqldata = (void*)sstcd;
#line 227 "A205bunchu.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 4;
#line 227 "A205bunchu.sqc"
      sql_setdlist[25].sqldata = (void*)ecd;
#line 227 "A205bunchu.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 4;
#line 227 "A205bunchu.sqc"
      sql_setdlist[26].sqldata = (void*)bckid;
#line 227 "A205bunchu.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 227 "A205bunchu.sqc"
      sql_setdlist[27].sqldata = (void*)&jtflg;
#line 227 "A205bunchu.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 227 "A205bunchu.sqc"
      sql_setdlist[28].sqldata = (void*)&knssyr;
#line 227 "A205bunchu.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 227 "A205bunchu.sqc"
      sql_setdlist[29].sqldata = (void*)&tknflg;
#line 227 "A205bunchu.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 227 "A205bunchu.sqc"
      sql_setdlist[30].sqldata = (void*)&ttkkflg;
#line 227 "A205bunchu.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 227 "A205bunchu.sqc"
      sql_setdlist[31].sqldata = (void*)&bnckka;
#line 227 "A205bunchu.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[32].sqltype = 500; sql_setdlist[32].sqllen = 2;
#line 227 "A205bunchu.sqc"
      sql_setdlist[32].sqldata = (void*)&srtkey;
#line 227 "A205bunchu.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 27;
#line 227 "A205bunchu.sqc"
      sql_setdlist[33].sqldata = (void*)ksndh;
#line 227 "A205bunchu.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 27;
#line 227 "A205bunchu.sqc"
      sql_setdlist[34].sqldata = (void*)trkdh;
#line 227 "A205bunchu.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 227 "A205bunchu.sqc"
      sqlasetdata(3,0,35,sql_setdlist,0L,0L);
    }
#line 227 "A205bunchu.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 227 "A205bunchu.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 227 "A205bunchu.sqc"
  sqlastop(0L);
}

#line 227 "A205bunchu.sqc"


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
#line 242 "A205bunchu.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 242 "A205bunchu.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 242 "A205bunchu.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 242 "A205bunchu.sqc"
  sqlastop(0L);
}

#line 242 "A205bunchu.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 250 "A205bunchu.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ABunBunIns()
 *    BUNCHU レコードを挿入する
 * ■引数
 *    [I]  Bunchu* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ABunBunIns( Bunchu* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, BunchuArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 272 "A205bunchu.sqc"


    
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
#line 347 "A205bunchu.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 347 "A205bunchu.sqc"
  sqlaaloc(2,33,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[33];
#line 347 "A205bunchu.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 347 "A205bunchu.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 347 "A205bunchu.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 347 "A205bunchu.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 347 "A205bunchu.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 347 "A205bunchu.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 347 "A205bunchu.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 347 "A205bunchu.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 347 "A205bunchu.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 347 "A205bunchu.sqc"
      sql_setdlist[4].sqldata = (void*)sriymd;
#line 347 "A205bunchu.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 14;
#line 347 "A205bunchu.sqc"
      sql_setdlist[5].sqldata = (void*)kntno;
#line 347 "A205bunchu.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 347 "A205bunchu.sqc"
      sql_setdlist[6].sqldata = (void*)&kntketflg;
#line 347 "A205bunchu.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 8;
#line 347 "A205bunchu.sqc"
      sql_setdlist[7].sqldata = (void*)smpcd;
#line 347 "A205bunchu.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 8;
#line 347 "A205bunchu.sqc"
      sql_setdlist[8].sqldata = (void*)kmkcd;
#line 347 "A205bunchu.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 347 "A205bunchu.sqc"
      sql_setdlist[9].sqldata = (void*)&smpcditno;
#line 347 "A205bunchu.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 5;
#line 347 "A205bunchu.sqc"
      sql_setdlist[10].sqldata = (void*)chkmj;
#line 347 "A205bunchu.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 347 "A205bunchu.sqc"
      sql_setdlist[11].sqldata = (void*)trid;
#line 347 "A205bunchu.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 347 "A205bunchu.sqc"
      sql_setdlist[12].sqldata = (void*)&trpos;
#line 347 "A205bunchu.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 347 "A205bunchu.sqc"
      sql_setdlist[13].sqldata = (void*)asyrckid;
#line 347 "A205bunchu.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 347 "A205bunchu.sqc"
      sql_setdlist[14].sqldata = (void*)&asyrckpos;
#line 347 "A205bunchu.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 11;
#line 347 "A205bunchu.sqc"
      sql_setdlist[15].sqldata = (void*)id2;
#line 347 "A205bunchu.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[16].sqltype = 500; sql_setdlist[16].sqllen = 2;
#line 347 "A205bunchu.sqc"
      sql_setdlist[16].sqldata = (void*)&id2pos;
#line 347 "A205bunchu.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 347 "A205bunchu.sqc"
      sql_setdlist[17].sqldata = (void*)&sbtkbn;
#line 347 "A205bunchu.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 4;
#line 347 "A205bunchu.sqc"
      sql_setdlist[18].sqldata = (void*)age;
#line 347 "A205bunchu.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 347 "A205bunchu.sqc"
      sql_setdlist[19].sqldata = (void*)&agekbn;
#line 347 "A205bunchu.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 5;
#line 347 "A205bunchu.sqc"
      sql_setdlist[20].sqldata = (void*)tntme;
#line 347 "A205bunchu.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 347 "A205bunchu.sqc"
      sql_setdlist[21].sqldata = (void*)&tntni;
#line 347 "A205bunchu.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 6;
#line 347 "A205bunchu.sqc"
      sql_setdlist[22].sqldata = (void*)tnryo;
#line 347 "A205bunchu.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 347 "A205bunchu.sqc"
      sql_setdlist[23].sqldata = (void*)&tnryotni;
#line 347 "A205bunchu.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 8;
#line 347 "A205bunchu.sqc"
      sql_setdlist[24].sqldata = (void*)sstcd;
#line 347 "A205bunchu.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 4;
#line 347 "A205bunchu.sqc"
      sql_setdlist[25].sqldata = (void*)ecd;
#line 347 "A205bunchu.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 4;
#line 347 "A205bunchu.sqc"
      sql_setdlist[26].sqldata = (void*)bckid;
#line 347 "A205bunchu.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 347 "A205bunchu.sqc"
      sql_setdlist[27].sqldata = (void*)&jtflg;
#line 347 "A205bunchu.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 347 "A205bunchu.sqc"
      sql_setdlist[28].sqldata = (void*)&knssyr;
#line 347 "A205bunchu.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 347 "A205bunchu.sqc"
      sql_setdlist[29].sqldata = (void*)&tknflg;
#line 347 "A205bunchu.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 347 "A205bunchu.sqc"
      sql_setdlist[30].sqldata = (void*)&ttkkflg;
#line 347 "A205bunchu.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 347 "A205bunchu.sqc"
      sql_setdlist[31].sqldata = (void*)&bnckka;
#line 347 "A205bunchu.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sql_setdlist[32].sqltype = 500; sql_setdlist[32].sqllen = 2;
#line 347 "A205bunchu.sqc"
      sql_setdlist[32].sqldata = (void*)&srtkey;
#line 347 "A205bunchu.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 347 "A205bunchu.sqc"
      sqlasetdata(2,0,33,sql_setdlist,0L,0L);
    }
#line 347 "A205bunchu.sqc"
  sqlacall((unsigned short)24,2,2,0,0L);
#line 347 "A205bunchu.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 347 "A205bunchu.sqc"
  sqlastop(0L);
}

#line 347 "A205bunchu.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 352 "A205bunchu.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ABunUpdate()
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
long ABunUpdate( Bunchu* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, BunchuArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 376 "A205bunchu.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 377 "A205bunchu.sqc"


    
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
		KSNDH
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
		CURRENT TIMESTAMP
    ) WHERE
		KNTNO = :kntno AND
		SMPCD = :smpcd AND
		KMKCD = :kmkcd AND
		SRIYMD = :sriymd;
*/

{
#line 446 "A205bunchu.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 446 "A205bunchu.sqc"
  sqlaaloc(2,33,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[33];
#line 446 "A205bunchu.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 446 "A205bunchu.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 446 "A205bunchu.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 446 "A205bunchu.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 446 "A205bunchu.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 446 "A205bunchu.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 446 "A205bunchu.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 446 "A205bunchu.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 446 "A205bunchu.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 446 "A205bunchu.sqc"
      sql_setdlist[4].sqldata = (void*)&kntketflg;
#line 446 "A205bunchu.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 446 "A205bunchu.sqc"
      sql_setdlist[5].sqldata = (void*)&smpcditno;
#line 446 "A205bunchu.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 5;
#line 446 "A205bunchu.sqc"
      sql_setdlist[6].sqldata = (void*)chkmj;
#line 446 "A205bunchu.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 446 "A205bunchu.sqc"
      sql_setdlist[7].sqldata = (void*)trid;
#line 446 "A205bunchu.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 446 "A205bunchu.sqc"
      sql_setdlist[8].sqldata = (void*)&trpos;
#line 446 "A205bunchu.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 446 "A205bunchu.sqc"
      sql_setdlist[9].sqldata = (void*)asyrckid;
#line 446 "A205bunchu.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[10].sqltype = 500; sql_setdlist[10].sqllen = 2;
#line 446 "A205bunchu.sqc"
      sql_setdlist[10].sqldata = (void*)&asyrckpos;
#line 446 "A205bunchu.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 446 "A205bunchu.sqc"
      sql_setdlist[11].sqldata = (void*)id2;
#line 446 "A205bunchu.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 446 "A205bunchu.sqc"
      sql_setdlist[12].sqldata = (void*)&id2pos;
#line 446 "A205bunchu.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 446 "A205bunchu.sqc"
      sql_setdlist[13].sqldata = (void*)&sbtkbn;
#line 446 "A205bunchu.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 4;
#line 446 "A205bunchu.sqc"
      sql_setdlist[14].sqldata = (void*)age;
#line 446 "A205bunchu.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[15].sqltype = 452; sql_setdlist[15].sqllen = 1;
#line 446 "A205bunchu.sqc"
      sql_setdlist[15].sqldata = (void*)&agekbn;
#line 446 "A205bunchu.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 5;
#line 446 "A205bunchu.sqc"
      sql_setdlist[16].sqldata = (void*)tntme;
#line 446 "A205bunchu.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 446 "A205bunchu.sqc"
      sql_setdlist[17].sqldata = (void*)&tntni;
#line 446 "A205bunchu.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 6;
#line 446 "A205bunchu.sqc"
      sql_setdlist[18].sqldata = (void*)tnryo;
#line 446 "A205bunchu.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 446 "A205bunchu.sqc"
      sql_setdlist[19].sqldata = (void*)&tnryotni;
#line 446 "A205bunchu.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 8;
#line 446 "A205bunchu.sqc"
      sql_setdlist[20].sqldata = (void*)sstcd;
#line 446 "A205bunchu.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 4;
#line 446 "A205bunchu.sqc"
      sql_setdlist[21].sqldata = (void*)ecd;
#line 446 "A205bunchu.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 4;
#line 446 "A205bunchu.sqc"
      sql_setdlist[22].sqldata = (void*)bckid;
#line 446 "A205bunchu.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 446 "A205bunchu.sqc"
      sql_setdlist[23].sqldata = (void*)&jtflg;
#line 446 "A205bunchu.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 446 "A205bunchu.sqc"
      sql_setdlist[24].sqldata = (void*)&knssyr;
#line 446 "A205bunchu.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 446 "A205bunchu.sqc"
      sql_setdlist[25].sqldata = (void*)&tknflg;
#line 446 "A205bunchu.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 446 "A205bunchu.sqc"
      sql_setdlist[26].sqldata = (void*)&ttkkflg;
#line 446 "A205bunchu.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 446 "A205bunchu.sqc"
      sql_setdlist[27].sqldata = (void*)&bnckka;
#line 446 "A205bunchu.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[28].sqltype = 500; sql_setdlist[28].sqllen = 2;
#line 446 "A205bunchu.sqc"
      sql_setdlist[28].sqldata = (void*)&srtkey;
#line 446 "A205bunchu.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 14;
#line 446 "A205bunchu.sqc"
      sql_setdlist[29].sqldata = (void*)kntno;
#line 446 "A205bunchu.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 8;
#line 446 "A205bunchu.sqc"
      sql_setdlist[30].sqldata = (void*)smpcd;
#line 446 "A205bunchu.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 8;
#line 446 "A205bunchu.sqc"
      sql_setdlist[31].sqldata = (void*)kmkcd;
#line 446 "A205bunchu.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 11;
#line 446 "A205bunchu.sqc"
      sql_setdlist[32].sqldata = (void*)sriymd;
#line 446 "A205bunchu.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 446 "A205bunchu.sqc"
      sqlasetdata(2,0,33,sql_setdlist,0L,0L);
    }
#line 446 "A205bunchu.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 446 "A205bunchu.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 446 "A205bunchu.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 446 "A205bunchu.sqc"
  sqlastop(0L);
}

#line 446 "A205bunchu.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 451 "A205bunchu.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 455 "A205bunchu.sqc"

    return sqlca.sqlcode;
}

// add 2007.05.08 waj
/******************************************************************************
 * ABunSelAllKey()
 *    BUNCHU レコードKey条件取得
 * ■引数
 *    [I]  Bunchu*  pKey        取得するレコードのキー
 *    [O]  Bunchu** arrayOut    取得レコード配列格納領域
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ABunSelAllKey( Bunchu* pKey, Bunchu** arrayOut )
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

#line 482 "A205bunchu.sqc"


    
/*
EXEC SQL DECLARE cBunAllKey CURSOR FOR
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
		KNTNO  = :kntno  AND
		KMKCD  = :kmkcd  AND
		SMPCD  = :smpcd 
		FOR READ ONLY;
*/

#line 528 "A205bunchu.sqc"


    
/*
EXEC SQL OPEN cBunAllKey;
*/

{
#line 530 "A205bunchu.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 530 "A205bunchu.sqc"
  sqlaaloc(2,4,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 530 "A205bunchu.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 530 "A205bunchu.sqc"
      sql_setdlist[0].sqldata = (void*)sriymd;
#line 530 "A205bunchu.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 530 "A205bunchu.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 14;
#line 530 "A205bunchu.sqc"
      sql_setdlist[1].sqldata = (void*)kntno;
#line 530 "A205bunchu.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 530 "A205bunchu.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 530 "A205bunchu.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 530 "A205bunchu.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 530 "A205bunchu.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 530 "A205bunchu.sqc"
      sql_setdlist[3].sqldata = (void*)smpcd;
#line 530 "A205bunchu.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 530 "A205bunchu.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 530 "A205bunchu.sqc"
  sqlacall((unsigned short)26,4,2,0,0L);
#line 530 "A205bunchu.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 530 "A205bunchu.sqc"
  sqlastop(0L);
}

#line 530 "A205bunchu.sqc"


    while( 1 ) {
        Bunchu* rec;

        
/*
EXEC SQL FETCH cBunAllKey INTO
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
#line 570 "A205bunchu.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 570 "A205bunchu.sqc"
  sqlaaloc(3,35,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[35];
#line 570 "A205bunchu.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 570 "A205bunchu.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 570 "A205bunchu.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 570 "A205bunchu.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 570 "A205bunchu.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 570 "A205bunchu.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 570 "A205bunchu.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 570 "A205bunchu.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 570 "A205bunchu.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 570 "A205bunchu.sqc"
      sql_setdlist[4].sqldata = (void*)sriymd;
#line 570 "A205bunchu.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 14;
#line 570 "A205bunchu.sqc"
      sql_setdlist[5].sqldata = (void*)kntno;
#line 570 "A205bunchu.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 570 "A205bunchu.sqc"
      sql_setdlist[6].sqldata = (void*)&kntketflg;
#line 570 "A205bunchu.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 8;
#line 570 "A205bunchu.sqc"
      sql_setdlist[7].sqldata = (void*)smpcd;
#line 570 "A205bunchu.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 8;
#line 570 "A205bunchu.sqc"
      sql_setdlist[8].sqldata = (void*)kmkcd;
#line 570 "A205bunchu.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 570 "A205bunchu.sqc"
      sql_setdlist[9].sqldata = (void*)&smpcditno;
#line 570 "A205bunchu.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 5;
#line 570 "A205bunchu.sqc"
      sql_setdlist[10].sqldata = (void*)chkmj;
#line 570 "A205bunchu.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 570 "A205bunchu.sqc"
      sql_setdlist[11].sqldata = (void*)trid;
#line 570 "A205bunchu.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 570 "A205bunchu.sqc"
      sql_setdlist[12].sqldata = (void*)&trpos;
#line 570 "A205bunchu.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 570 "A205bunchu.sqc"
      sql_setdlist[13].sqldata = (void*)asyrckid;
#line 570 "A205bunchu.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 570 "A205bunchu.sqc"
      sql_setdlist[14].sqldata = (void*)&asyrckpos;
#line 570 "A205bunchu.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 11;
#line 570 "A205bunchu.sqc"
      sql_setdlist[15].sqldata = (void*)id2;
#line 570 "A205bunchu.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[16].sqltype = 500; sql_setdlist[16].sqllen = 2;
#line 570 "A205bunchu.sqc"
      sql_setdlist[16].sqldata = (void*)&id2pos;
#line 570 "A205bunchu.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 570 "A205bunchu.sqc"
      sql_setdlist[17].sqldata = (void*)&sbtkbn;
#line 570 "A205bunchu.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 4;
#line 570 "A205bunchu.sqc"
      sql_setdlist[18].sqldata = (void*)age;
#line 570 "A205bunchu.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 570 "A205bunchu.sqc"
      sql_setdlist[19].sqldata = (void*)&agekbn;
#line 570 "A205bunchu.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 5;
#line 570 "A205bunchu.sqc"
      sql_setdlist[20].sqldata = (void*)tntme;
#line 570 "A205bunchu.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 570 "A205bunchu.sqc"
      sql_setdlist[21].sqldata = (void*)&tntni;
#line 570 "A205bunchu.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 6;
#line 570 "A205bunchu.sqc"
      sql_setdlist[22].sqldata = (void*)tnryo;
#line 570 "A205bunchu.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 570 "A205bunchu.sqc"
      sql_setdlist[23].sqldata = (void*)&tnryotni;
#line 570 "A205bunchu.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 8;
#line 570 "A205bunchu.sqc"
      sql_setdlist[24].sqldata = (void*)sstcd;
#line 570 "A205bunchu.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 4;
#line 570 "A205bunchu.sqc"
      sql_setdlist[25].sqldata = (void*)ecd;
#line 570 "A205bunchu.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 4;
#line 570 "A205bunchu.sqc"
      sql_setdlist[26].sqldata = (void*)bckid;
#line 570 "A205bunchu.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 570 "A205bunchu.sqc"
      sql_setdlist[27].sqldata = (void*)&jtflg;
#line 570 "A205bunchu.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 570 "A205bunchu.sqc"
      sql_setdlist[28].sqldata = (void*)&knssyr;
#line 570 "A205bunchu.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 570 "A205bunchu.sqc"
      sql_setdlist[29].sqldata = (void*)&tknflg;
#line 570 "A205bunchu.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 570 "A205bunchu.sqc"
      sql_setdlist[30].sqldata = (void*)&ttkkflg;
#line 570 "A205bunchu.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 570 "A205bunchu.sqc"
      sql_setdlist[31].sqldata = (void*)&bnckka;
#line 570 "A205bunchu.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[32].sqltype = 500; sql_setdlist[32].sqllen = 2;
#line 570 "A205bunchu.sqc"
      sql_setdlist[32].sqldata = (void*)&srtkey;
#line 570 "A205bunchu.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 27;
#line 570 "A205bunchu.sqc"
      sql_setdlist[33].sqldata = (void*)ksndh;
#line 570 "A205bunchu.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 27;
#line 570 "A205bunchu.sqc"
      sql_setdlist[34].sqldata = (void*)trkdh;
#line 570 "A205bunchu.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 570 "A205bunchu.sqc"
      sqlasetdata(3,0,35,sql_setdlist,0L,0L);
    }
#line 570 "A205bunchu.sqc"
  sqlacall((unsigned short)25,4,0,3,0L);
#line 570 "A205bunchu.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 570 "A205bunchu.sqc"
  sqlastop(0L);
}

#line 570 "A205bunchu.sqc"


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
EXEC SQL CLOSE cBunAllKey;
*/

{
#line 585 "A205bunchu.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 585 "A205bunchu.sqc"
  sqlacall((unsigned short)20,4,0,0,0L);
#line 585 "A205bunchu.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 585 "A205bunchu.sqc"
  sqlastop(0L);
}

#line 585 "A205bunchu.sqc"


    *arrayOut = array;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 592 "A205bunchu.sqc"

    return sqlca.sqlcode;
}

/** End of File *********************************************************/
