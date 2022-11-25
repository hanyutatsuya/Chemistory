static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,69,65,82,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,49,48,90,67,72,73,75,32,0,0,0,0,0,0,0,0,
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


#line 1 "Chikenzok.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Chikenzok.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Chikenzok.h"
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


#line 24 "Chikenzok.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Chikenzok.sqc"

	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    prtclno[12];
	char    kosstcd[8];
	char    tytme[5];
	char    tyryo[6];
	char    tyryotni[4];
	char    yzfktme[5];
	char    ikasflg;
	short   kntsu;
	short   kmksu;
	char    sspit[3];
	char    zrcd01[6];
	char    zrcd02[6];
	char    zrcd03[6];
	char    zrcd04[6];
	char    zrcd05[6];
	char    zrcd06[6];
	char    zrkg01[3];
	char    zrkg02[3];
	char    zrkg03[3];
	char    zrkg04[3];
	char    zrkg05[3];
	char    zrkg06[3];
	char    hrseq[5];
	char    kntksflg;
	char    gcpflg;
	char    prtclnm[41];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 61 "Chikenzok.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Chikenzok

BmlDMMInfo	ChikenzokArray[] = {
	DMM_SDATE( utkymd ),
	DMM_SSTRING( irino ),
	DMM_SCHAR( iriketflg ),
	DMM_SSHORT( zssdino ),
	DMM_SSTRING( prtclno ),
	DMM_SSTRING( kosstcd ),
	DMM_SSTRING( tytme ),
	DMM_SSTRING( tyryo ),
	DMM_SSTRING( tyryotni ),
	DMM_SSTRING( yzfktme ),
	DMM_SCHAR( ikasflg ),
	DMM_SSHORT( kntsu ),
	DMM_SSHORT( kmksu ),
	DMM_SSTRING( sspit ),
	DMM_SSTRING( zrcd01 ),
	DMM_SSTRING( zrcd02 ),
	DMM_SSTRING( zrcd03 ),
	DMM_SSTRING( zrcd04 ),
	DMM_SSTRING( zrcd05 ),
	DMM_SSTRING( zrcd06 ),
	DMM_SSTRING( zrkg01 ),
	DMM_SSTRING( zrkg02 ),
	DMM_SSTRING( zrkg03 ),
	DMM_SSTRING( zrkg04 ),
	DMM_SSTRING( zrkg05 ),
	DMM_SSTRING( zrkg06 ),
	DMM_SSTRING( hrseq ),
	DMM_SCHAR( kntksflg ),
	DMM_SCHAR( gcpflg ),
	DMM_SSTRING( prtclnm ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbChikenzokSelectAll()
 *    CHIKENZOK レコード全件取得
 * ■引数
 *    [O]  Chikenzok** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbChikenzokSelectAll( Chikenzok** arrayOut, int* numOut )
{
    Chikenzok*  array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 120 "Chikenzok.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		PRTCLNO,
		KOSSTCD,
		TYTME,
		TYRYO,
		TYRYOTNI,
		YZFKTME,
		IKASFLG,
		KNTSU,
		KMKSU,
		SSPIT,
		ZRCD01,
		ZRCD02,
		ZRCD03,
		ZRCD04,
		ZRCD05,
		ZRCD06,
		ZRKG01,
		ZRKG02,
		ZRKG03,
		ZRKG04,
		ZRKG05,
		ZRKG06,
		HRSEQ,
		KNTKSFLG,
		GCPFLG,
		PRTCLNM,
		KSNDH
    FROM
        CHIKENZOK FOR READ ONLY;
*/

#line 156 "Chikenzok.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 158 "Chikenzok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 158 "Chikenzok.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 158 "Chikenzok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 158 "Chikenzok.sqc"
  sqlastop(0L);
}

#line 158 "Chikenzok.sqc"


    while( 1 ) {
        Chikenzok* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:prtclno,
			:kosstcd,
			:tytme,
			:tyryo,
			:tyryotni,
			:yzfktme,
			:ikasflg,
			:kntsu,
			:kmksu,
			:sspit,
			:zrcd01,
			:zrcd02,
			:zrcd03,
			:zrcd04,
			:zrcd05,
			:zrcd06,
			:zrkg01,
			:zrkg02,
			:zrkg03,
			:zrkg04,
			:zrkg05,
			:zrkg06,
			:hrseq,
			:kntksflg,
			:gcpflg,
			:prtclnm,
			:ksndh;
*/

{
#line 194 "Chikenzok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 194 "Chikenzok.sqc"
  sqlaaloc(3,31,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[31];
#line 194 "Chikenzok.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 194 "Chikenzok.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 194 "Chikenzok.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 194 "Chikenzok.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 194 "Chikenzok.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 194 "Chikenzok.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 194 "Chikenzok.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 194 "Chikenzok.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 194 "Chikenzok.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 12;
#line 194 "Chikenzok.sqc"
      sql_setdlist[4].sqldata = (void*)prtclno;
#line 194 "Chikenzok.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 194 "Chikenzok.sqc"
      sql_setdlist[5].sqldata = (void*)kosstcd;
#line 194 "Chikenzok.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 5;
#line 194 "Chikenzok.sqc"
      sql_setdlist[6].sqldata = (void*)tytme;
#line 194 "Chikenzok.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 6;
#line 194 "Chikenzok.sqc"
      sql_setdlist[7].sqldata = (void*)tyryo;
#line 194 "Chikenzok.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 194 "Chikenzok.sqc"
      sql_setdlist[8].sqldata = (void*)tyryotni;
#line 194 "Chikenzok.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 5;
#line 194 "Chikenzok.sqc"
      sql_setdlist[9].sqldata = (void*)yzfktme;
#line 194 "Chikenzok.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 194 "Chikenzok.sqc"
      sql_setdlist[10].sqldata = (void*)&ikasflg;
#line 194 "Chikenzok.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 194 "Chikenzok.sqc"
      sql_setdlist[11].sqldata = (void*)&kntsu;
#line 194 "Chikenzok.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 194 "Chikenzok.sqc"
      sql_setdlist[12].sqldata = (void*)&kmksu;
#line 194 "Chikenzok.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 3;
#line 194 "Chikenzok.sqc"
      sql_setdlist[13].sqldata = (void*)sspit;
#line 194 "Chikenzok.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 6;
#line 194 "Chikenzok.sqc"
      sql_setdlist[14].sqldata = (void*)zrcd01;
#line 194 "Chikenzok.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 6;
#line 194 "Chikenzok.sqc"
      sql_setdlist[15].sqldata = (void*)zrcd02;
#line 194 "Chikenzok.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 6;
#line 194 "Chikenzok.sqc"
      sql_setdlist[16].sqldata = (void*)zrcd03;
#line 194 "Chikenzok.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 6;
#line 194 "Chikenzok.sqc"
      sql_setdlist[17].sqldata = (void*)zrcd04;
#line 194 "Chikenzok.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 6;
#line 194 "Chikenzok.sqc"
      sql_setdlist[18].sqldata = (void*)zrcd05;
#line 194 "Chikenzok.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 6;
#line 194 "Chikenzok.sqc"
      sql_setdlist[19].sqldata = (void*)zrcd06;
#line 194 "Chikenzok.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 3;
#line 194 "Chikenzok.sqc"
      sql_setdlist[20].sqldata = (void*)zrkg01;
#line 194 "Chikenzok.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 3;
#line 194 "Chikenzok.sqc"
      sql_setdlist[21].sqldata = (void*)zrkg02;
#line 194 "Chikenzok.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 3;
#line 194 "Chikenzok.sqc"
      sql_setdlist[22].sqldata = (void*)zrkg03;
#line 194 "Chikenzok.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 3;
#line 194 "Chikenzok.sqc"
      sql_setdlist[23].sqldata = (void*)zrkg04;
#line 194 "Chikenzok.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 3;
#line 194 "Chikenzok.sqc"
      sql_setdlist[24].sqldata = (void*)zrkg05;
#line 194 "Chikenzok.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 3;
#line 194 "Chikenzok.sqc"
      sql_setdlist[25].sqldata = (void*)zrkg06;
#line 194 "Chikenzok.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 5;
#line 194 "Chikenzok.sqc"
      sql_setdlist[26].sqldata = (void*)hrseq;
#line 194 "Chikenzok.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 194 "Chikenzok.sqc"
      sql_setdlist[27].sqldata = (void*)&kntksflg;
#line 194 "Chikenzok.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 194 "Chikenzok.sqc"
      sql_setdlist[28].sqldata = (void*)&gcpflg;
#line 194 "Chikenzok.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 41;
#line 194 "Chikenzok.sqc"
      sql_setdlist[29].sqldata = (void*)prtclnm;
#line 194 "Chikenzok.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 27;
#line 194 "Chikenzok.sqc"
      sql_setdlist[30].sqldata = (void*)ksndh;
#line 194 "Chikenzok.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 194 "Chikenzok.sqc"
      sqlasetdata(3,0,31,sql_setdlist,0L,0L);
    }
#line 194 "Chikenzok.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 194 "Chikenzok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 194 "Chikenzok.sqc"
  sqlastop(0L);
}

#line 194 "Chikenzok.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Chikenzok*)ZbmlRealloc( array,
                                    sizeof( Chikenzok ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Chikenzok ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, ChikenzokArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 209 "Chikenzok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 209 "Chikenzok.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 209 "Chikenzok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 209 "Chikenzok.sqc"
  sqlastop(0L);
}

#line 209 "Chikenzok.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 217 "Chikenzok.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbChikenzokSelectKey()
 *    CHIKENZOK レコードKey条件取得
 * ■引数
 *    [I]  Chikenzok* pKey      取得するレコードのキー
 *    [O]  Chikenzok** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbChikenzokSelectKey( Chikenzok* pKey, Chikenzok** arrayOut, int* numOut )
{
    Chikenzok*  array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, ChikenzokArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 243 "Chikenzok.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		PRTCLNO,
		KOSSTCD,
		TYTME,
		TYRYO,
		TYRYOTNI,
		YZFKTME,
		IKASFLG,
		KNTSU,
		KMKSU,
		SSPIT,
		ZRCD01,
		ZRCD02,
		ZRCD03,
		ZRCD04,
		ZRCD05,
		ZRCD06,
		ZRKG01,
		ZRKG02,
		ZRKG03,
		ZRKG04,
		ZRKG05,
		ZRKG06,
		HRSEQ,
		KNTKSFLG,
		GCPFLG,
		PRTCLNM,
		KSNDH
    FROM
        CHIKENZOK
    WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		ZSSDINO = :zssdino FOR READ ONLY;
*/

#line 283 "Chikenzok.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 285 "Chikenzok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 285 "Chikenzok.sqc"
  sqlaaloc(2,3,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 285 "Chikenzok.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 285 "Chikenzok.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 285 "Chikenzok.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 285 "Chikenzok.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 285 "Chikenzok.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 285 "Chikenzok.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 285 "Chikenzok.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 285 "Chikenzok.sqc"
      sql_setdlist[2].sqldata = (void*)&zssdino;
#line 285 "Chikenzok.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 285 "Chikenzok.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 285 "Chikenzok.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 285 "Chikenzok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 285 "Chikenzok.sqc"
  sqlastop(0L);
}

#line 285 "Chikenzok.sqc"


    while( 1 ) {
        Chikenzok* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:prtclno,
			:kosstcd,
			:tytme,
			:tyryo,
			:tyryotni,
			:yzfktme,
			:ikasflg,
			:kntsu,
			:kmksu,
			:sspit,
			:zrcd01,
			:zrcd02,
			:zrcd03,
			:zrcd04,
			:zrcd05,
			:zrcd06,
			:zrkg01,
			:zrkg02,
			:zrkg03,
			:zrkg04,
			:zrkg05,
			:zrkg06,
			:hrseq,
			:kntksflg,
			:gcpflg,
			:prtclnm,
			:ksndh;
*/

{
#line 321 "Chikenzok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 321 "Chikenzok.sqc"
  sqlaaloc(3,31,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[31];
#line 321 "Chikenzok.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 321 "Chikenzok.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 321 "Chikenzok.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 321 "Chikenzok.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 321 "Chikenzok.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 321 "Chikenzok.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 321 "Chikenzok.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 321 "Chikenzok.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 321 "Chikenzok.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 12;
#line 321 "Chikenzok.sqc"
      sql_setdlist[4].sqldata = (void*)prtclno;
#line 321 "Chikenzok.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 321 "Chikenzok.sqc"
      sql_setdlist[5].sqldata = (void*)kosstcd;
#line 321 "Chikenzok.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 5;
#line 321 "Chikenzok.sqc"
      sql_setdlist[6].sqldata = (void*)tytme;
#line 321 "Chikenzok.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 6;
#line 321 "Chikenzok.sqc"
      sql_setdlist[7].sqldata = (void*)tyryo;
#line 321 "Chikenzok.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 321 "Chikenzok.sqc"
      sql_setdlist[8].sqldata = (void*)tyryotni;
#line 321 "Chikenzok.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 5;
#line 321 "Chikenzok.sqc"
      sql_setdlist[9].sqldata = (void*)yzfktme;
#line 321 "Chikenzok.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 321 "Chikenzok.sqc"
      sql_setdlist[10].sqldata = (void*)&ikasflg;
#line 321 "Chikenzok.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 321 "Chikenzok.sqc"
      sql_setdlist[11].sqldata = (void*)&kntsu;
#line 321 "Chikenzok.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 321 "Chikenzok.sqc"
      sql_setdlist[12].sqldata = (void*)&kmksu;
#line 321 "Chikenzok.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 3;
#line 321 "Chikenzok.sqc"
      sql_setdlist[13].sqldata = (void*)sspit;
#line 321 "Chikenzok.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 6;
#line 321 "Chikenzok.sqc"
      sql_setdlist[14].sqldata = (void*)zrcd01;
#line 321 "Chikenzok.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 6;
#line 321 "Chikenzok.sqc"
      sql_setdlist[15].sqldata = (void*)zrcd02;
#line 321 "Chikenzok.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 6;
#line 321 "Chikenzok.sqc"
      sql_setdlist[16].sqldata = (void*)zrcd03;
#line 321 "Chikenzok.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 6;
#line 321 "Chikenzok.sqc"
      sql_setdlist[17].sqldata = (void*)zrcd04;
#line 321 "Chikenzok.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 6;
#line 321 "Chikenzok.sqc"
      sql_setdlist[18].sqldata = (void*)zrcd05;
#line 321 "Chikenzok.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 6;
#line 321 "Chikenzok.sqc"
      sql_setdlist[19].sqldata = (void*)zrcd06;
#line 321 "Chikenzok.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 3;
#line 321 "Chikenzok.sqc"
      sql_setdlist[20].sqldata = (void*)zrkg01;
#line 321 "Chikenzok.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 3;
#line 321 "Chikenzok.sqc"
      sql_setdlist[21].sqldata = (void*)zrkg02;
#line 321 "Chikenzok.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 3;
#line 321 "Chikenzok.sqc"
      sql_setdlist[22].sqldata = (void*)zrkg03;
#line 321 "Chikenzok.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 3;
#line 321 "Chikenzok.sqc"
      sql_setdlist[23].sqldata = (void*)zrkg04;
#line 321 "Chikenzok.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 3;
#line 321 "Chikenzok.sqc"
      sql_setdlist[24].sqldata = (void*)zrkg05;
#line 321 "Chikenzok.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 3;
#line 321 "Chikenzok.sqc"
      sql_setdlist[25].sqldata = (void*)zrkg06;
#line 321 "Chikenzok.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 5;
#line 321 "Chikenzok.sqc"
      sql_setdlist[26].sqldata = (void*)hrseq;
#line 321 "Chikenzok.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 321 "Chikenzok.sqc"
      sql_setdlist[27].sqldata = (void*)&kntksflg;
#line 321 "Chikenzok.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 321 "Chikenzok.sqc"
      sql_setdlist[28].sqldata = (void*)&gcpflg;
#line 321 "Chikenzok.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 41;
#line 321 "Chikenzok.sqc"
      sql_setdlist[29].sqldata = (void*)prtclnm;
#line 321 "Chikenzok.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 27;
#line 321 "Chikenzok.sqc"
      sql_setdlist[30].sqldata = (void*)ksndh;
#line 321 "Chikenzok.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 321 "Chikenzok.sqc"
      sqlasetdata(3,0,31,sql_setdlist,0L,0L);
    }
#line 321 "Chikenzok.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 321 "Chikenzok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 321 "Chikenzok.sqc"
  sqlastop(0L);
}

#line 321 "Chikenzok.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Chikenzok*)ZbmlRealloc( array,
                                    sizeof( Chikenzok ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Chikenzok ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, ChikenzokArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 336 "Chikenzok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 336 "Chikenzok.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 336 "Chikenzok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 336 "Chikenzok.sqc"
  sqlastop(0L);
}

#line 336 "Chikenzok.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 344 "Chikenzok.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbChikenzokInsert()
 *    CHIKENZOK レコードを挿入する
 * ■引数
 *    [I]  Chikenzok* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbChikenzokInsert( Chikenzok* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, ChikenzokArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 367 "Chikenzok.sqc"


    
/*
EXEC SQL INSERT INTO CHIKENZOK
    (
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		PRTCLNO,
		KOSSTCD,
		TYTME,
		TYRYO,
		TYRYOTNI,
		YZFKTME,
		IKASFLG,
		KNTSU,
		KMKSU,
		SSPIT,
		ZRCD01,
		ZRCD02,
		ZRCD03,
		ZRCD04,
		ZRCD05,
		ZRCD06,
		ZRKG01,
		ZRKG02,
		ZRKG03,
		ZRKG04,
		ZRKG05,
		ZRKG06,
		HRSEQ,
		KNTKSFLG,
		GCPFLG,
		PRTCLNM,
		KSNDH
    ) VALUES (
		:utkymd,
		:irino,
		:iriketflg,
		:zssdino,
		:prtclno,
		:kosstcd,
		:tytme,
		:tyryo,
		:tyryotni,
		:yzfktme,
		:ikasflg,
		:kntsu,
		:kmksu,
		:sspit,
		:zrcd01,
		:zrcd02,
		:zrcd03,
		:zrcd04,
		:zrcd05,
		:zrcd06,
		:zrkg01,
		:zrkg02,
		:zrkg03,
		:zrkg04,
		:zrkg05,
		:zrkg06,
		:hrseq,
		:kntksflg,
		:gcpflg,
		:prtclnm,
		:ksndh
    );
*/

{
#line 434 "Chikenzok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 434 "Chikenzok.sqc"
  sqlaaloc(2,31,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[31];
#line 434 "Chikenzok.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 434 "Chikenzok.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 434 "Chikenzok.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 434 "Chikenzok.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 434 "Chikenzok.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 434 "Chikenzok.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 434 "Chikenzok.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 434 "Chikenzok.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 434 "Chikenzok.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 12;
#line 434 "Chikenzok.sqc"
      sql_setdlist[4].sqldata = (void*)prtclno;
#line 434 "Chikenzok.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 434 "Chikenzok.sqc"
      sql_setdlist[5].sqldata = (void*)kosstcd;
#line 434 "Chikenzok.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 5;
#line 434 "Chikenzok.sqc"
      sql_setdlist[6].sqldata = (void*)tytme;
#line 434 "Chikenzok.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 6;
#line 434 "Chikenzok.sqc"
      sql_setdlist[7].sqldata = (void*)tyryo;
#line 434 "Chikenzok.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 434 "Chikenzok.sqc"
      sql_setdlist[8].sqldata = (void*)tyryotni;
#line 434 "Chikenzok.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 5;
#line 434 "Chikenzok.sqc"
      sql_setdlist[9].sqldata = (void*)yzfktme;
#line 434 "Chikenzok.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 434 "Chikenzok.sqc"
      sql_setdlist[10].sqldata = (void*)&ikasflg;
#line 434 "Chikenzok.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 434 "Chikenzok.sqc"
      sql_setdlist[11].sqldata = (void*)&kntsu;
#line 434 "Chikenzok.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 434 "Chikenzok.sqc"
      sql_setdlist[12].sqldata = (void*)&kmksu;
#line 434 "Chikenzok.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 3;
#line 434 "Chikenzok.sqc"
      sql_setdlist[13].sqldata = (void*)sspit;
#line 434 "Chikenzok.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 6;
#line 434 "Chikenzok.sqc"
      sql_setdlist[14].sqldata = (void*)zrcd01;
#line 434 "Chikenzok.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 6;
#line 434 "Chikenzok.sqc"
      sql_setdlist[15].sqldata = (void*)zrcd02;
#line 434 "Chikenzok.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 6;
#line 434 "Chikenzok.sqc"
      sql_setdlist[16].sqldata = (void*)zrcd03;
#line 434 "Chikenzok.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 6;
#line 434 "Chikenzok.sqc"
      sql_setdlist[17].sqldata = (void*)zrcd04;
#line 434 "Chikenzok.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 6;
#line 434 "Chikenzok.sqc"
      sql_setdlist[18].sqldata = (void*)zrcd05;
#line 434 "Chikenzok.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 6;
#line 434 "Chikenzok.sqc"
      sql_setdlist[19].sqldata = (void*)zrcd06;
#line 434 "Chikenzok.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 3;
#line 434 "Chikenzok.sqc"
      sql_setdlist[20].sqldata = (void*)zrkg01;
#line 434 "Chikenzok.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 3;
#line 434 "Chikenzok.sqc"
      sql_setdlist[21].sqldata = (void*)zrkg02;
#line 434 "Chikenzok.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 3;
#line 434 "Chikenzok.sqc"
      sql_setdlist[22].sqldata = (void*)zrkg03;
#line 434 "Chikenzok.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 3;
#line 434 "Chikenzok.sqc"
      sql_setdlist[23].sqldata = (void*)zrkg04;
#line 434 "Chikenzok.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 3;
#line 434 "Chikenzok.sqc"
      sql_setdlist[24].sqldata = (void*)zrkg05;
#line 434 "Chikenzok.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 3;
#line 434 "Chikenzok.sqc"
      sql_setdlist[25].sqldata = (void*)zrkg06;
#line 434 "Chikenzok.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 5;
#line 434 "Chikenzok.sqc"
      sql_setdlist[26].sqldata = (void*)hrseq;
#line 434 "Chikenzok.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 434 "Chikenzok.sqc"
      sql_setdlist[27].sqldata = (void*)&kntksflg;
#line 434 "Chikenzok.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 434 "Chikenzok.sqc"
      sql_setdlist[28].sqldata = (void*)&gcpflg;
#line 434 "Chikenzok.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 41;
#line 434 "Chikenzok.sqc"
      sql_setdlist[29].sqldata = (void*)prtclnm;
#line 434 "Chikenzok.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 27;
#line 434 "Chikenzok.sqc"
      sql_setdlist[30].sqldata = (void*)ksndh;
#line 434 "Chikenzok.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 434 "Chikenzok.sqc"
      sqlasetdata(2,0,31,sql_setdlist,0L,0L);
    }
#line 434 "Chikenzok.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 434 "Chikenzok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 434 "Chikenzok.sqc"
  sqlastop(0L);
}

#line 434 "Chikenzok.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 439 "Chikenzok.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbChikenzokUpdate()
 *    CHIKENZOK レコードを更新する
 * ■引数
 *    [I]  Chikenzok* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbChikenzokUpdate( Chikenzok* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, ChikenzokArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 463 "Chikenzok.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 464 "Chikenzok.sqc"


    
/*
EXEC SQL UPDATE CHIKENZOK
    SET (
		IRIKETFLG,
		PRTCLNO,
		KOSSTCD,
		TYTME,
		TYRYO,
		TYRYOTNI,
		YZFKTME,
		IKASFLG,
		KNTSU,
		KMKSU,
		SSPIT,
		ZRCD01,
		ZRCD02,
		ZRCD03,
		ZRCD04,
		ZRCD05,
		ZRCD06,
		ZRKG01,
		ZRKG02,
		ZRKG03,
		ZRKG04,
		ZRKG05,
		ZRKG06,
		HRSEQ,
		KNTKSFLG,
		GCPFLG,
		PRTCLNM,
		KSNDH
    ) = (
		:iriketflg,
		:prtclno,
		:kosstcd,
		:tytme,
		:tyryo,
		:tyryotni,
		:yzfktme,
		:ikasflg,
		:kntsu,
		:kmksu,
		:sspit,
		:zrcd01,
		:zrcd02,
		:zrcd03,
		:zrcd04,
		:zrcd05,
		:zrcd06,
		:zrkg01,
		:zrkg02,
		:zrkg03,
		:zrkg04,
		:zrkg05,
		:zrkg06,
		:hrseq,
		:kntksflg,
		:gcpflg,
		:prtclnm,
		:ksndh
    ) WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		ZSSDINO = :zssdino;
*/

{
#line 528 "Chikenzok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 528 "Chikenzok.sqc"
  sqlaaloc(2,31,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[31];
#line 528 "Chikenzok.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 528 "Chikenzok.sqc"
      sql_setdlist[0].sqldata = (void*)&iriketflg;
#line 528 "Chikenzok.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 528 "Chikenzok.sqc"
      sql_setdlist[1].sqldata = (void*)prtclno;
#line 528 "Chikenzok.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 528 "Chikenzok.sqc"
      sql_setdlist[2].sqldata = (void*)kosstcd;
#line 528 "Chikenzok.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 528 "Chikenzok.sqc"
      sql_setdlist[3].sqldata = (void*)tytme;
#line 528 "Chikenzok.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 6;
#line 528 "Chikenzok.sqc"
      sql_setdlist[4].sqldata = (void*)tyryo;
#line 528 "Chikenzok.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 4;
#line 528 "Chikenzok.sqc"
      sql_setdlist[5].sqldata = (void*)tyryotni;
#line 528 "Chikenzok.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 5;
#line 528 "Chikenzok.sqc"
      sql_setdlist[6].sqldata = (void*)yzfktme;
#line 528 "Chikenzok.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 528 "Chikenzok.sqc"
      sql_setdlist[7].sqldata = (void*)&ikasflg;
#line 528 "Chikenzok.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 528 "Chikenzok.sqc"
      sql_setdlist[8].sqldata = (void*)&kntsu;
#line 528 "Chikenzok.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 528 "Chikenzok.sqc"
      sql_setdlist[9].sqldata = (void*)&kmksu;
#line 528 "Chikenzok.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 3;
#line 528 "Chikenzok.sqc"
      sql_setdlist[10].sqldata = (void*)sspit;
#line 528 "Chikenzok.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 6;
#line 528 "Chikenzok.sqc"
      sql_setdlist[11].sqldata = (void*)zrcd01;
#line 528 "Chikenzok.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 6;
#line 528 "Chikenzok.sqc"
      sql_setdlist[12].sqldata = (void*)zrcd02;
#line 528 "Chikenzok.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 6;
#line 528 "Chikenzok.sqc"
      sql_setdlist[13].sqldata = (void*)zrcd03;
#line 528 "Chikenzok.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 6;
#line 528 "Chikenzok.sqc"
      sql_setdlist[14].sqldata = (void*)zrcd04;
#line 528 "Chikenzok.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 6;
#line 528 "Chikenzok.sqc"
      sql_setdlist[15].sqldata = (void*)zrcd05;
#line 528 "Chikenzok.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 6;
#line 528 "Chikenzok.sqc"
      sql_setdlist[16].sqldata = (void*)zrcd06;
#line 528 "Chikenzok.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 3;
#line 528 "Chikenzok.sqc"
      sql_setdlist[17].sqldata = (void*)zrkg01;
#line 528 "Chikenzok.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 3;
#line 528 "Chikenzok.sqc"
      sql_setdlist[18].sqldata = (void*)zrkg02;
#line 528 "Chikenzok.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 3;
#line 528 "Chikenzok.sqc"
      sql_setdlist[19].sqldata = (void*)zrkg03;
#line 528 "Chikenzok.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 3;
#line 528 "Chikenzok.sqc"
      sql_setdlist[20].sqldata = (void*)zrkg04;
#line 528 "Chikenzok.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 3;
#line 528 "Chikenzok.sqc"
      sql_setdlist[21].sqldata = (void*)zrkg05;
#line 528 "Chikenzok.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 3;
#line 528 "Chikenzok.sqc"
      sql_setdlist[22].sqldata = (void*)zrkg06;
#line 528 "Chikenzok.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 5;
#line 528 "Chikenzok.sqc"
      sql_setdlist[23].sqldata = (void*)hrseq;
#line 528 "Chikenzok.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 528 "Chikenzok.sqc"
      sql_setdlist[24].sqldata = (void*)&kntksflg;
#line 528 "Chikenzok.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 528 "Chikenzok.sqc"
      sql_setdlist[25].sqldata = (void*)&gcpflg;
#line 528 "Chikenzok.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 41;
#line 528 "Chikenzok.sqc"
      sql_setdlist[26].sqldata = (void*)prtclnm;
#line 528 "Chikenzok.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 27;
#line 528 "Chikenzok.sqc"
      sql_setdlist[27].sqldata = (void*)ksndh;
#line 528 "Chikenzok.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 11;
#line 528 "Chikenzok.sqc"
      sql_setdlist[28].sqldata = (void*)utkymd;
#line 528 "Chikenzok.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 12;
#line 528 "Chikenzok.sqc"
      sql_setdlist[29].sqldata = (void*)irino;
#line 528 "Chikenzok.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sql_setdlist[30].sqltype = 500; sql_setdlist[30].sqllen = 2;
#line 528 "Chikenzok.sqc"
      sql_setdlist[30].sqldata = (void*)&zssdino;
#line 528 "Chikenzok.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 528 "Chikenzok.sqc"
      sqlasetdata(2,0,31,sql_setdlist,0L,0L);
    }
#line 528 "Chikenzok.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 528 "Chikenzok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 528 "Chikenzok.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 528 "Chikenzok.sqc"
  sqlastop(0L);
}

#line 528 "Chikenzok.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 533 "Chikenzok.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 537 "Chikenzok.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbChikenzokDelete()
 *    CHIKENZOK レコードを削除する
 * ■引数
 *    [I]  Chikenzok* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbChikenzokDelete( Chikenzok* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, ChikenzokArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 561 "Chikenzok.sqc"


    
/*
EXEC SQL DELETE FROM CHIKENZOK
    WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		ZSSDINO = :zssdino;
*/

{
#line 567 "Chikenzok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 567 "Chikenzok.sqc"
  sqlaaloc(2,3,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 567 "Chikenzok.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 567 "Chikenzok.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 567 "Chikenzok.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 567 "Chikenzok.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 567 "Chikenzok.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 567 "Chikenzok.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 567 "Chikenzok.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 567 "Chikenzok.sqc"
      sql_setdlist[2].sqldata = (void*)&zssdino;
#line 567 "Chikenzok.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 567 "Chikenzok.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 567 "Chikenzok.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 567 "Chikenzok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 567 "Chikenzok.sqc"
  sqlastop(0L);
}

#line 567 "Chikenzok.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 572 "Chikenzok.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
