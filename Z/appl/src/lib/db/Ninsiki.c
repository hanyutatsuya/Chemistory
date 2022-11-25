static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,86,66,85,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,53,52,90,78,73,78,83,32,0,0,0,0,0,0,0,0,
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


#line 1 "Ninsiki.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Ninsiki.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Ninsiki.h"
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


#line 24 "Ninsiki.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Ninsiki.sqc"

	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    sriymd[11];
	char    kntno[14];
	char    kntketflg;
	char    chkmj[5];
	char    asyrckid[11];
	short   asyrckpos;
	char    id2[11];
	short   id2pos;
	char    id3[11];
	short   id3pos;
	char    fuksuhn;
	char    ksndh[27];
	char    trkdh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 47 "Ninsiki.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Ninsiki

BmlDMMInfo	NinsikiArray[] = {
	DMM_SDATE( utkymd ),
	DMM_SSTRING( irino ),
	DMM_SCHAR( iriketflg ),
	DMM_SSHORT( zssdino ),
	DMM_SDATE( sriymd ),
	DMM_SSTRING( kntno ),
	DMM_SCHAR( kntketflg ),
	DMM_SSTRING( chkmj ),
	DMM_SSTRING( asyrckid ),
	DMM_SSHORT( asyrckpos ),
	DMM_SSTRING( id2 ),
	DMM_SSHORT( id2pos ),
	DMM_SSTRING( id3 ),
	DMM_SSHORT( id3pos ),
	DMM_SCHAR( fuksuhn ),
	DMM_STIMESTAMP( ksndh ),
	DMM_STIMESTAMP( trkdh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbNinsikiSelectAll()
 *    NINSIKI レコード全件取得
 * ■引数
 *    [O]  Ninsiki** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbNinsikiSelectAll( Ninsiki** arrayOut, int* numOut )
{
    Ninsiki*    array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 92 "Ninsiki.sqc"


    
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
		CHKMJ,
		ASYRCKID,
		ASYRCKPOS,
		ID2,
		ID2POS,
		ID3,
		ID3POS,
		FUKSUHN,
		KSNDH,
		TRKDH
    FROM
        NINSIKI FOR READ ONLY;
*/

#line 114 "Ninsiki.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 116 "Ninsiki.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 116 "Ninsiki.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 116 "Ninsiki.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 116 "Ninsiki.sqc"
  sqlastop(0L);
}

#line 116 "Ninsiki.sqc"


    while( 1 ) {
        Ninsiki* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:sriymd,
			:kntno,
			:kntketflg,
			:chkmj,
			:asyrckid,
			:asyrckpos,
			:id2,
			:id2pos,
			:id3,
			:id3pos,
			:fuksuhn,
			:ksndh,
			:trkdh;
*/

{
#line 138 "Ninsiki.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 138 "Ninsiki.sqc"
  sqlaaloc(3,17,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[17];
#line 138 "Ninsiki.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 138 "Ninsiki.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 138 "Ninsiki.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 138 "Ninsiki.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 138 "Ninsiki.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 138 "Ninsiki.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 138 "Ninsiki.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 138 "Ninsiki.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 138 "Ninsiki.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 138 "Ninsiki.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 138 "Ninsiki.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 138 "Ninsiki.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 138 "Ninsiki.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 138 "Ninsiki.sqc"
      sql_setdlist[4].sqldata = (void*)sriymd;
#line 138 "Ninsiki.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 138 "Ninsiki.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 14;
#line 138 "Ninsiki.sqc"
      sql_setdlist[5].sqldata = (void*)kntno;
#line 138 "Ninsiki.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 138 "Ninsiki.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 138 "Ninsiki.sqc"
      sql_setdlist[6].sqldata = (void*)&kntketflg;
#line 138 "Ninsiki.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 138 "Ninsiki.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 5;
#line 138 "Ninsiki.sqc"
      sql_setdlist[7].sqldata = (void*)chkmj;
#line 138 "Ninsiki.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 138 "Ninsiki.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 138 "Ninsiki.sqc"
      sql_setdlist[8].sqldata = (void*)asyrckid;
#line 138 "Ninsiki.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 138 "Ninsiki.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 138 "Ninsiki.sqc"
      sql_setdlist[9].sqldata = (void*)&asyrckpos;
#line 138 "Ninsiki.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 138 "Ninsiki.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 138 "Ninsiki.sqc"
      sql_setdlist[10].sqldata = (void*)id2;
#line 138 "Ninsiki.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 138 "Ninsiki.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 138 "Ninsiki.sqc"
      sql_setdlist[11].sqldata = (void*)&id2pos;
#line 138 "Ninsiki.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 138 "Ninsiki.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 138 "Ninsiki.sqc"
      sql_setdlist[12].sqldata = (void*)id3;
#line 138 "Ninsiki.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 138 "Ninsiki.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 138 "Ninsiki.sqc"
      sql_setdlist[13].sqldata = (void*)&id3pos;
#line 138 "Ninsiki.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 138 "Ninsiki.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 138 "Ninsiki.sqc"
      sql_setdlist[14].sqldata = (void*)&fuksuhn;
#line 138 "Ninsiki.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 138 "Ninsiki.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 138 "Ninsiki.sqc"
      sql_setdlist[15].sqldata = (void*)ksndh;
#line 138 "Ninsiki.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 138 "Ninsiki.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 27;
#line 138 "Ninsiki.sqc"
      sql_setdlist[16].sqldata = (void*)trkdh;
#line 138 "Ninsiki.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 138 "Ninsiki.sqc"
      sqlasetdata(3,0,17,sql_setdlist,0L,0L);
    }
#line 138 "Ninsiki.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 138 "Ninsiki.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 138 "Ninsiki.sqc"
  sqlastop(0L);
}

#line 138 "Ninsiki.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Ninsiki*)ZbmlRealloc( array,
                                    sizeof( Ninsiki ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Ninsiki ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, NinsikiArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 153 "Ninsiki.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 153 "Ninsiki.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 153 "Ninsiki.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 153 "Ninsiki.sqc"
  sqlastop(0L);
}

#line 153 "Ninsiki.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 161 "Ninsiki.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbNinsikiSelectKey()
 *    NINSIKI レコードKey条件取得
 * ■引数
 *    [I]  Ninsiki* pKey       取得するレコードのキー
 *    [O]  Ninsiki** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbNinsikiSelectKey( Ninsiki* pKey, Ninsiki** arrayOut, int* numOut )
{
    Ninsiki*    array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, NinsikiArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 187 "Ninsiki.sqc"


    
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
		CHKMJ,
		ASYRCKID,
		ASYRCKPOS,
		ID2,
		ID2POS,
		ID3,
		ID3POS,
		FUKSUHN,
		KSNDH,
		TRKDH
    FROM
        NINSIKI
    WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		ZSSDINO = :zssdino AND
		SRIYMD = :sriymd AND
		KNTNO = :kntno FOR READ ONLY;
*/

#line 215 "Ninsiki.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 217 "Ninsiki.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 217 "Ninsiki.sqc"
  sqlaaloc(2,5,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 217 "Ninsiki.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 217 "Ninsiki.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 217 "Ninsiki.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 217 "Ninsiki.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 217 "Ninsiki.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 217 "Ninsiki.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 217 "Ninsiki.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 217 "Ninsiki.sqc"
      sql_setdlist[2].sqldata = (void*)&zssdino;
#line 217 "Ninsiki.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 217 "Ninsiki.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 217 "Ninsiki.sqc"
      sql_setdlist[3].sqldata = (void*)sriymd;
#line 217 "Ninsiki.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 217 "Ninsiki.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 14;
#line 217 "Ninsiki.sqc"
      sql_setdlist[4].sqldata = (void*)kntno;
#line 217 "Ninsiki.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 217 "Ninsiki.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 217 "Ninsiki.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 217 "Ninsiki.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 217 "Ninsiki.sqc"
  sqlastop(0L);
}

#line 217 "Ninsiki.sqc"


    while( 1 ) {
        Ninsiki* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:sriymd,
			:kntno,
			:kntketflg,
			:chkmj,
			:asyrckid,
			:asyrckpos,
			:id2,
			:id2pos,
			:id3,
			:id3pos,
			:fuksuhn,
			:ksndh,
			:trkdh;
*/

{
#line 239 "Ninsiki.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 239 "Ninsiki.sqc"
  sqlaaloc(3,17,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[17];
#line 239 "Ninsiki.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 239 "Ninsiki.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 239 "Ninsiki.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 239 "Ninsiki.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 239 "Ninsiki.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 239 "Ninsiki.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 239 "Ninsiki.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 239 "Ninsiki.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 239 "Ninsiki.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 239 "Ninsiki.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 239 "Ninsiki.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 239 "Ninsiki.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 239 "Ninsiki.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 239 "Ninsiki.sqc"
      sql_setdlist[4].sqldata = (void*)sriymd;
#line 239 "Ninsiki.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 239 "Ninsiki.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 14;
#line 239 "Ninsiki.sqc"
      sql_setdlist[5].sqldata = (void*)kntno;
#line 239 "Ninsiki.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 239 "Ninsiki.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 239 "Ninsiki.sqc"
      sql_setdlist[6].sqldata = (void*)&kntketflg;
#line 239 "Ninsiki.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 239 "Ninsiki.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 5;
#line 239 "Ninsiki.sqc"
      sql_setdlist[7].sqldata = (void*)chkmj;
#line 239 "Ninsiki.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 239 "Ninsiki.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 239 "Ninsiki.sqc"
      sql_setdlist[8].sqldata = (void*)asyrckid;
#line 239 "Ninsiki.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 239 "Ninsiki.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 239 "Ninsiki.sqc"
      sql_setdlist[9].sqldata = (void*)&asyrckpos;
#line 239 "Ninsiki.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 239 "Ninsiki.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 239 "Ninsiki.sqc"
      sql_setdlist[10].sqldata = (void*)id2;
#line 239 "Ninsiki.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 239 "Ninsiki.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 239 "Ninsiki.sqc"
      sql_setdlist[11].sqldata = (void*)&id2pos;
#line 239 "Ninsiki.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 239 "Ninsiki.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 239 "Ninsiki.sqc"
      sql_setdlist[12].sqldata = (void*)id3;
#line 239 "Ninsiki.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 239 "Ninsiki.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 239 "Ninsiki.sqc"
      sql_setdlist[13].sqldata = (void*)&id3pos;
#line 239 "Ninsiki.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 239 "Ninsiki.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 239 "Ninsiki.sqc"
      sql_setdlist[14].sqldata = (void*)&fuksuhn;
#line 239 "Ninsiki.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 239 "Ninsiki.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 239 "Ninsiki.sqc"
      sql_setdlist[15].sqldata = (void*)ksndh;
#line 239 "Ninsiki.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 239 "Ninsiki.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 27;
#line 239 "Ninsiki.sqc"
      sql_setdlist[16].sqldata = (void*)trkdh;
#line 239 "Ninsiki.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 239 "Ninsiki.sqc"
      sqlasetdata(3,0,17,sql_setdlist,0L,0L);
    }
#line 239 "Ninsiki.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 239 "Ninsiki.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 239 "Ninsiki.sqc"
  sqlastop(0L);
}

#line 239 "Ninsiki.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Ninsiki*)ZbmlRealloc( array,
                                    sizeof( Ninsiki ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Ninsiki ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, NinsikiArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 254 "Ninsiki.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 254 "Ninsiki.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 254 "Ninsiki.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 254 "Ninsiki.sqc"
  sqlastop(0L);
}

#line 254 "Ninsiki.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 262 "Ninsiki.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbNinsikiInsert()
 *    NINSIKI レコードを挿入する
 * ■引数
 *    [I]  Ninsiki* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbNinsikiInsert( Ninsiki* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, NinsikiArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 285 "Ninsiki.sqc"


    
/*
EXEC SQL INSERT INTO NINSIKI
    (
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		CHKMJ,
		ASYRCKID,
		ASYRCKPOS,
		ID2,
		ID2POS,
		ID3,
		ID3POS,
		FUKSUHN,
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
		:chkmj,
		:asyrckid,
		:asyrckpos,
		:id2,
		:id2pos,
		:id3,
		:id3pos,
		:fuksuhn,
		CURRENT TIMESTAMP,
		CURRENT TIMESTAMP
    );
*/

{
#line 324 "Ninsiki.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 324 "Ninsiki.sqc"
  sqlaaloc(2,15,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[15];
#line 324 "Ninsiki.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 324 "Ninsiki.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 324 "Ninsiki.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 324 "Ninsiki.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 324 "Ninsiki.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 324 "Ninsiki.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 324 "Ninsiki.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 324 "Ninsiki.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 324 "Ninsiki.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 324 "Ninsiki.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 324 "Ninsiki.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 324 "Ninsiki.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 324 "Ninsiki.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 324 "Ninsiki.sqc"
      sql_setdlist[4].sqldata = (void*)sriymd;
#line 324 "Ninsiki.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 324 "Ninsiki.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 14;
#line 324 "Ninsiki.sqc"
      sql_setdlist[5].sqldata = (void*)kntno;
#line 324 "Ninsiki.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 324 "Ninsiki.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 324 "Ninsiki.sqc"
      sql_setdlist[6].sqldata = (void*)&kntketflg;
#line 324 "Ninsiki.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 324 "Ninsiki.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 5;
#line 324 "Ninsiki.sqc"
      sql_setdlist[7].sqldata = (void*)chkmj;
#line 324 "Ninsiki.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 324 "Ninsiki.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 324 "Ninsiki.sqc"
      sql_setdlist[8].sqldata = (void*)asyrckid;
#line 324 "Ninsiki.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 324 "Ninsiki.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 324 "Ninsiki.sqc"
      sql_setdlist[9].sqldata = (void*)&asyrckpos;
#line 324 "Ninsiki.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 324 "Ninsiki.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 324 "Ninsiki.sqc"
      sql_setdlist[10].sqldata = (void*)id2;
#line 324 "Ninsiki.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 324 "Ninsiki.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 324 "Ninsiki.sqc"
      sql_setdlist[11].sqldata = (void*)&id2pos;
#line 324 "Ninsiki.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 324 "Ninsiki.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 324 "Ninsiki.sqc"
      sql_setdlist[12].sqldata = (void*)id3;
#line 324 "Ninsiki.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 324 "Ninsiki.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 324 "Ninsiki.sqc"
      sql_setdlist[13].sqldata = (void*)&id3pos;
#line 324 "Ninsiki.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 324 "Ninsiki.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 324 "Ninsiki.sqc"
      sql_setdlist[14].sqldata = (void*)&fuksuhn;
#line 324 "Ninsiki.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 324 "Ninsiki.sqc"
      sqlasetdata(2,0,15,sql_setdlist,0L,0L);
    }
#line 324 "Ninsiki.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 324 "Ninsiki.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 324 "Ninsiki.sqc"
  sqlastop(0L);
}

#line 324 "Ninsiki.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 329 "Ninsiki.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbNinsikiUpdate()
 *    NINSIKI レコードを更新する
 * ■引数
 *    [I]  Ninsiki* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbNinsikiUpdate( Ninsiki* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, NinsikiArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 353 "Ninsiki.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 354 "Ninsiki.sqc"


    
/*
EXEC SQL UPDATE NINSIKI
    SET (
		IRIKETFLG,
		KNTKETFLG,
		CHKMJ,
		ASYRCKID,
		ASYRCKPOS,
		ID2,
		ID2POS,
		ID3,
		ID3POS,
		FUKSUHN,
		KSNDH,
		TRKDH
    ) = (
		:iriketflg,
		:kntketflg,
		:chkmj,
		:asyrckid,
		:asyrckpos,
		:id2,
		:id2pos,
		:id3,
		:id3pos,
		:fuksuhn,
		CURRENT TIMESTAMP,
		:trkdh
    ) WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		ZSSDINO = :zssdino AND
		SRIYMD = :sriymd AND
		KNTNO = :kntno;
*/

{
#line 388 "Ninsiki.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 388 "Ninsiki.sqc"
  sqlaaloc(2,16,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[16];
#line 388 "Ninsiki.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 388 "Ninsiki.sqc"
      sql_setdlist[0].sqldata = (void*)&iriketflg;
#line 388 "Ninsiki.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 388 "Ninsiki.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 388 "Ninsiki.sqc"
      sql_setdlist[1].sqldata = (void*)&kntketflg;
#line 388 "Ninsiki.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 388 "Ninsiki.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 388 "Ninsiki.sqc"
      sql_setdlist[2].sqldata = (void*)chkmj;
#line 388 "Ninsiki.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 388 "Ninsiki.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 388 "Ninsiki.sqc"
      sql_setdlist[3].sqldata = (void*)asyrckid;
#line 388 "Ninsiki.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 388 "Ninsiki.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 388 "Ninsiki.sqc"
      sql_setdlist[4].sqldata = (void*)&asyrckpos;
#line 388 "Ninsiki.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 388 "Ninsiki.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 388 "Ninsiki.sqc"
      sql_setdlist[5].sqldata = (void*)id2;
#line 388 "Ninsiki.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 388 "Ninsiki.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 388 "Ninsiki.sqc"
      sql_setdlist[6].sqldata = (void*)&id2pos;
#line 388 "Ninsiki.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 388 "Ninsiki.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 388 "Ninsiki.sqc"
      sql_setdlist[7].sqldata = (void*)id3;
#line 388 "Ninsiki.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 388 "Ninsiki.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 388 "Ninsiki.sqc"
      sql_setdlist[8].sqldata = (void*)&id3pos;
#line 388 "Ninsiki.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 388 "Ninsiki.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 388 "Ninsiki.sqc"
      sql_setdlist[9].sqldata = (void*)&fuksuhn;
#line 388 "Ninsiki.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 388 "Ninsiki.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 27;
#line 388 "Ninsiki.sqc"
      sql_setdlist[10].sqldata = (void*)trkdh;
#line 388 "Ninsiki.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 388 "Ninsiki.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 388 "Ninsiki.sqc"
      sql_setdlist[11].sqldata = (void*)utkymd;
#line 388 "Ninsiki.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 388 "Ninsiki.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 12;
#line 388 "Ninsiki.sqc"
      sql_setdlist[12].sqldata = (void*)irino;
#line 388 "Ninsiki.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 388 "Ninsiki.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 388 "Ninsiki.sqc"
      sql_setdlist[13].sqldata = (void*)&zssdino;
#line 388 "Ninsiki.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 388 "Ninsiki.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 11;
#line 388 "Ninsiki.sqc"
      sql_setdlist[14].sqldata = (void*)sriymd;
#line 388 "Ninsiki.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 388 "Ninsiki.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 14;
#line 388 "Ninsiki.sqc"
      sql_setdlist[15].sqldata = (void*)kntno;
#line 388 "Ninsiki.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 388 "Ninsiki.sqc"
      sqlasetdata(2,0,16,sql_setdlist,0L,0L);
    }
#line 388 "Ninsiki.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 388 "Ninsiki.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 388 "Ninsiki.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 388 "Ninsiki.sqc"
  sqlastop(0L);
}

#line 388 "Ninsiki.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 393 "Ninsiki.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 397 "Ninsiki.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbNinsikiDelete()
 *    NINSIKI レコードを削除する
 * ■引数
 *    [I]  Ninsiki* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbNinsikiDelete( Ninsiki* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, NinsikiArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 421 "Ninsiki.sqc"


    
/*
EXEC SQL DELETE FROM NINSIKI
    WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		ZSSDINO = :zssdino AND
		SRIYMD = :sriymd AND
		KNTNO = :kntno;
*/

{
#line 429 "Ninsiki.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 429 "Ninsiki.sqc"
  sqlaaloc(2,5,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 429 "Ninsiki.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 429 "Ninsiki.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 429 "Ninsiki.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 429 "Ninsiki.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 429 "Ninsiki.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 429 "Ninsiki.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 429 "Ninsiki.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 429 "Ninsiki.sqc"
      sql_setdlist[2].sqldata = (void*)&zssdino;
#line 429 "Ninsiki.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 429 "Ninsiki.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 429 "Ninsiki.sqc"
      sql_setdlist[3].sqldata = (void*)sriymd;
#line 429 "Ninsiki.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 429 "Ninsiki.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 14;
#line 429 "Ninsiki.sqc"
      sql_setdlist[4].sqldata = (void*)kntno;
#line 429 "Ninsiki.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 429 "Ninsiki.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 429 "Ninsiki.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 429 "Ninsiki.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 429 "Ninsiki.sqc"
  sqlastop(0L);
}

#line 429 "Ninsiki.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 434 "Ninsiki.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
