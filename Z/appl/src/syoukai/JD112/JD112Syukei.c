static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,49,65,70,53,81,74,77,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,74,68,49,49,50,83,89,85,0,0,0,0,0,0,0,0,
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


#line 1 "JD112Syukei.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： JS112Syukei.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-03-23                    Create
 *  1.01     2006-04-26     H.Suyama       BSKGOK→BSKLNEに変更
 *  1.04     2006-06-17     INTEC          経過SEQは10分単位に作成
 *  1.05     2006-07-04     INTEC          測定は結果のみで検体単位に集計
 **********************************************************************/
#include <stdio.h>

#include "JD112Syukei.h"
#include "bml_misc.h"
#include "bml_db.h"
#include "bml_dmm.h"

#define ALLOC_UNIT		1
#define STA_POS			1					// 1.04 ADD
#define JIKAN_LEN		15					// 1.04 ADD


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 29 "JD112Syukei.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 34 "JD112Syukei.sqc"

/* 1.03 DELL
DEL	char		jikan[3];
*/
	char		jikan[27];
	char		skflg;
	sqlint32	count;
	char		bskkbn[5];
	char		bskgok[7];

	char		bsklne[5];

	char		fromdh[27];
	char		fromdatetime[19];
	char		todh[27];
	char		todatetime[19];
	char		wkupapp[33];
	char		knsjkflg;

	sqlint32	pos;
	sqlint32	len;

/*
EXEC SQL END DECLARE SECTION;
*/

#line 55 "JD112Syukei.sqc"


/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	JD112Syukei

BmlDMMInfo	JD112SyukeiArray[] = {
	DMM_SSTRING( jikan ),
	DMM_SCHAR( skflg ),
	DMM_SLONG( count ),
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( bskgok ),
	DMM_SSTRING( bsklne ),
	DMM_NULL
};

/******************************************************************************
 * ZdbJD112SelectCountA()
 *    依頼数集計
 * ■引数
 *    [I]  char* pFromDh			検索対象日時From
 *    [I]  char* pToDh				検索対象日時To
 *    [O]  JD112Syukei** arrayOut	取得レコード配列格納領域
 *    [O]  int* numOut				取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbJD112SelectCountA( char *pFromDh, char *pToDh, JD112Syukei** arrayOut, int* numOut )
{
	JD112Syukei	*array = NULL;
	int			num = 0;

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 90 "JD112Syukei.sqc"


	if ( ZbmlCopyToHostData( fromdh, pFromDh, sizeof( fromdh ) -1 ) == FALSE )
		return HRC_INVALID_VALUE;
	if ( ZbmlCopyToHostData( todh, pToDh, sizeof( todh ) -1 ) == FALSE )
		return HRC_INVALID_VALUE;

	
/*
EXEC SQL DECLARE c1 CURSOR FOR
	SELECT
		SUBSTR(TO_CHAR(TRKDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15),
		SKFLG,
		COUNT(TRKDH)
	FROM
		IRAI
	WHERE
			TRKDH >= :fromdh
		AND TRKDH < :todh
	GROUP BY
		SUBSTR(TO_CHAR(TRKDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15),
		SKFLG
	ORDER BY
		SUBSTR(TO_CHAR(TRKDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15),
		SKFLG
		FOR READ ONLY;
*/

#line 113 "JD112Syukei.sqc"


	
/*
EXEC SQL OPEN c1;
*/

{
#line 115 "JD112Syukei.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 115 "JD112Syukei.sqc"
  sqlaaloc(2,2,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 115 "JD112Syukei.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 27;
#line 115 "JD112Syukei.sqc"
      sql_setdlist[0].sqldata = (void*)fromdh;
#line 115 "JD112Syukei.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 115 "JD112Syukei.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 27;
#line 115 "JD112Syukei.sqc"
      sql_setdlist[1].sqldata = (void*)todh;
#line 115 "JD112Syukei.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 115 "JD112Syukei.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 115 "JD112Syukei.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 115 "JD112Syukei.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 115 "JD112Syukei.sqc"
  sqlastop(0L);
}

#line 115 "JD112Syukei.sqc"


	while( 1 ) {
		JD112Syukei* rec;

		
/*
EXEC SQL FETCH c1 INTO
			:jikan,
			:skflg,
			:count;
*/

{
#line 123 "JD112Syukei.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 123 "JD112Syukei.sqc"
  sqlaaloc(3,3,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 123 "JD112Syukei.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 27;
#line 123 "JD112Syukei.sqc"
      sql_setdlist[0].sqldata = (void*)jikan;
#line 123 "JD112Syukei.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 123 "JD112Syukei.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 123 "JD112Syukei.sqc"
      sql_setdlist[1].sqldata = (void*)&skflg;
#line 123 "JD112Syukei.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 123 "JD112Syukei.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 123 "JD112Syukei.sqc"
      sql_setdlist[2].sqldata = (void*)&count;
#line 123 "JD112Syukei.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 123 "JD112Syukei.sqc"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 123 "JD112Syukei.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 123 "JD112Syukei.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 123 "JD112Syukei.sqc"
  sqlastop(0L);
}

#line 123 "JD112Syukei.sqc"


		if( SQLCODE == 100 )
			break;

		if( num % ALLOC_UNIT == 0 ) {
			array = (JD112Syukei *)ZbmlRealloc( array,
												sizeof( JD112Syukei ) * ( num + ALLOC_UNIT ) );
			memset( array + num, 0, sizeof( JD112Syukei ) * ALLOC_UNIT );
		}

		rec = array + num++;
		ZbmlMapHostToStruct( (char*)rec, JD112SyukeiArray );
	}

	
/*
EXEC SQL CLOSE c1;
*/

{
#line 138 "JD112Syukei.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 138 "JD112Syukei.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 138 "JD112Syukei.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 138 "JD112Syukei.sqc"
  sqlastop(0L);
}

#line 138 "JD112Syukei.sqc"


	*arrayOut = array;
	*numOut   = num;

	return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 146 "JD112Syukei.sqc"

	return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbJD112SelectCountB()
 *    患者数集計
 * ■引数
 *    [I]  char* pFromDh			検索対象日時From
 *    [I]  char* pToDh				検索対象日時To
 *    [O]  JD112Syukei** arrayOut	取得レコード配列格納領域
 *    [O]  int* numOut				取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbJD112SelectCountB( char *pFromDh, char *pToDh, JD112Syukei** arrayOut, int* numOut )
{
	JD112Syukei	*array = NULL;
	int			num = 0;

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 168 "JD112Syukei.sqc"


	if ( ZbmlCopyToHostData( fromdh, pFromDh, sizeof( fromdh ) -1 ) == FALSE )
		return HRC_INVALID_VALUE;
	if ( ZbmlCopyToHostData( todh, pToDh, sizeof( todh ) -1 ) == FALSE )
		return HRC_INVALID_VALUE;

	
/*
EXEC SQL DECLARE c2 CURSOR FOR
	SELECT
		SUBSTR(TO_CHAR(KNJ.TRKDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15),
		COALESCE(IRI.SKFLG, '0'),
		COUNT(KNJ.TRKDH)
	FROM
		KANJYA KNJ
		LEFT OUTER JOIN
			(
				SELECT DISTINCT
					UTKYMD,
					IRINO,
					SKFLG
				FROM
					IRAI
			) IRI
		ON	KNJ.UTKYMD = IRI.UTKYMD
		AND KNJ.IRINO = IRI.IRINO
	WHERE
			KNJ.TRKDH >= :fromdh
		AND KNJ.TRKDH < :todh
	GROUP BY
		SUBSTR(TO_CHAR(KNJ.TRKDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15),
		IRI.SKFLG
	ORDER BY
		SUBSTR(TO_CHAR(KNJ.TRKDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15),
		IRI.SKFLG
		FOR READ ONLY;
*/

#line 202 "JD112Syukei.sqc"


	
/*
EXEC SQL OPEN c2;
*/

{
#line 204 "JD112Syukei.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 204 "JD112Syukei.sqc"
  sqlaaloc(2,2,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 204 "JD112Syukei.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 27;
#line 204 "JD112Syukei.sqc"
      sql_setdlist[0].sqldata = (void*)fromdh;
#line 204 "JD112Syukei.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 204 "JD112Syukei.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 27;
#line 204 "JD112Syukei.sqc"
      sql_setdlist[1].sqldata = (void*)todh;
#line 204 "JD112Syukei.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 204 "JD112Syukei.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 204 "JD112Syukei.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 204 "JD112Syukei.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 204 "JD112Syukei.sqc"
  sqlastop(0L);
}

#line 204 "JD112Syukei.sqc"


	while( 1 ) {
		JD112Syukei* rec;

		
/*
EXEC SQL FETCH c2 INTO
			:jikan,
			:skflg,
			:count;
*/

{
#line 212 "JD112Syukei.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 212 "JD112Syukei.sqc"
  sqlaaloc(3,3,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 212 "JD112Syukei.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 27;
#line 212 "JD112Syukei.sqc"
      sql_setdlist[0].sqldata = (void*)jikan;
#line 212 "JD112Syukei.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 212 "JD112Syukei.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 212 "JD112Syukei.sqc"
      sql_setdlist[1].sqldata = (void*)&skflg;
#line 212 "JD112Syukei.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 212 "JD112Syukei.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 212 "JD112Syukei.sqc"
      sql_setdlist[2].sqldata = (void*)&count;
#line 212 "JD112Syukei.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 212 "JD112Syukei.sqc"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 212 "JD112Syukei.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 212 "JD112Syukei.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 212 "JD112Syukei.sqc"
  sqlastop(0L);
}

#line 212 "JD112Syukei.sqc"


		if( SQLCODE == 100 )
			break;

		if( num % ALLOC_UNIT == 0 ) {
			array = (JD112Syukei *)ZbmlRealloc( array,
												sizeof( JD112Syukei ) * ( num + ALLOC_UNIT ) );
			memset( array + num, 0, sizeof( JD112Syukei ) * ALLOC_UNIT );
		}

		rec = array + num++;
		ZbmlMapHostToStruct( (char*)rec, JD112SyukeiArray );
	}

	
/*
EXEC SQL CLOSE c2;
*/

{
#line 227 "JD112Syukei.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 227 "JD112Syukei.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 227 "JD112Syukei.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 227 "JD112Syukei.sqc"
  sqlastop(0L);
}

#line 227 "JD112Syukei.sqc"


	*arrayOut = array;
	*numOut   = num;

	return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 235 "JD112Syukei.sqc"

	return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbJD112SelectCountC()
 *    分注数集計
 * ■引数
 *    [I]  char* pFromDh			検索対象日時From
 *    [I]  char* pToDh				検索対象日時To
 *    [O]  JD112Syukei** arrayOut	取得レコード配列格納領域
 *    [O]  int* numOut				取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbJD112SelectCountC( char *pFromDh, char *pToDh, JD112Syukei** arrayOut, int* numOut )
{
	JD112Syukei	*array = NULL;
	int			num = 0;

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 257 "JD112Syukei.sqc"


	if ( ZbmlCopyToHostData( fromdh, pFromDh, sizeof( fromdh ) -1 ) == FALSE )
		return HRC_INVALID_VALUE;
	if ( ZbmlCopyToHostData( todh, pToDh, sizeof( todh ) -1 ) == FALSE )
		return HRC_INVALID_VALUE;

	
/*
EXEC SQL DECLARE c3 CURSOR FOR
	SELECT
		SUBSTR(TO_CHAR(BNC.TRKDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15),
		COALESCE(IRI.SKFLG, '0'),
		COUNT(BNC.TRKDH)
	FROM
		(
				SELECT
					UTKYMD,
					IRINO,
					SRIYMD,
					KNTNO,
					SMPCD,
					MAX(TRKDH) AS TRKDH
				FROM
					BUNCHU
				GROUP BY
					UTKYMD,
					IRINO,
					SRIYMD,
					KNTNO,
					SMPCD
		) BNC
		LEFT OUTER JOIN
			(
				SELECT DISTINCT
					UTKYMD,
					IRINO,
					SKFLG
				FROM
					IRAI
			) IRI
		ON	BNC.UTKYMD = IRI.UTKYMD
		AND BNC.IRINO = IRI.IRINO
	WHERE
			BNC.TRKDH >= :fromdh
		AND BNC.TRKDH < :todh
	GROUP BY
		SUBSTR(TO_CHAR(BNC.TRKDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15),
		IRI.SKFLG
	ORDER BY
		SUBSTR(TO_CHAR(BNC.TRKDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15),
		IRI.SKFLG
		FOR READ ONLY;
*/

#line 307 "JD112Syukei.sqc"


	
/*
EXEC SQL OPEN c3;
*/

{
#line 309 "JD112Syukei.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 309 "JD112Syukei.sqc"
  sqlaaloc(2,2,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 309 "JD112Syukei.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 27;
#line 309 "JD112Syukei.sqc"
      sql_setdlist[0].sqldata = (void*)fromdh;
#line 309 "JD112Syukei.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 309 "JD112Syukei.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 27;
#line 309 "JD112Syukei.sqc"
      sql_setdlist[1].sqldata = (void*)todh;
#line 309 "JD112Syukei.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 309 "JD112Syukei.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 309 "JD112Syukei.sqc"
  sqlacall((unsigned short)26,3,2,0,0L);
#line 309 "JD112Syukei.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 309 "JD112Syukei.sqc"
  sqlastop(0L);
}

#line 309 "JD112Syukei.sqc"


	while( 1 ) {
		JD112Syukei* rec;

		
/*
EXEC SQL FETCH c3 INTO
			:jikan,
			:skflg,
			:count;
*/

{
#line 317 "JD112Syukei.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 317 "JD112Syukei.sqc"
  sqlaaloc(3,3,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 317 "JD112Syukei.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 27;
#line 317 "JD112Syukei.sqc"
      sql_setdlist[0].sqldata = (void*)jikan;
#line 317 "JD112Syukei.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 317 "JD112Syukei.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 317 "JD112Syukei.sqc"
      sql_setdlist[1].sqldata = (void*)&skflg;
#line 317 "JD112Syukei.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 317 "JD112Syukei.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 317 "JD112Syukei.sqc"
      sql_setdlist[2].sqldata = (void*)&count;
#line 317 "JD112Syukei.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 317 "JD112Syukei.sqc"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 317 "JD112Syukei.sqc"
  sqlacall((unsigned short)25,3,0,3,0L);
#line 317 "JD112Syukei.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 317 "JD112Syukei.sqc"
  sqlastop(0L);
}

#line 317 "JD112Syukei.sqc"


		if( SQLCODE == 100 )
			break;

		if( num % ALLOC_UNIT == 0 ) {
			array = (JD112Syukei *)ZbmlRealloc( array,
												sizeof( JD112Syukei ) * ( num + ALLOC_UNIT ) );
			memset( array + num, 0, sizeof( JD112Syukei ) * ALLOC_UNIT );
		}

		rec = array + num++;
		ZbmlMapHostToStruct( (char*)rec, JD112SyukeiArray );
	}

	
/*
EXEC SQL CLOSE c3;
*/

{
#line 332 "JD112Syukei.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 332 "JD112Syukei.sqc"
  sqlacall((unsigned short)20,3,0,0,0L);
#line 332 "JD112Syukei.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 332 "JD112Syukei.sqc"
  sqlastop(0L);
}

#line 332 "JD112Syukei.sqc"


	*arrayOut = array;
	*numOut   = num;

	return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 340 "JD112Syukei.sqc"

	return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbJD112SelectCountD()
 *    認識数集計
 * ■引数
 *    [I]  char* pFromDh			検索対象日時From
 *    [I]  char* pToDh				検索対象日時To
 *    [O]  JD112Syukei** arrayOut	取得レコード配列格納領域
 *    [O]  int* numOut				取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbJD112SelectCountD( char *pFromDh, char *pToDh, JD112Syukei** arrayOut, int* numOut )
{
	JD112Syukei	*array = NULL;
	int			num = 0;

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 362 "JD112Syukei.sqc"


	if ( ZbmlCopyToHostData( fromdh, pFromDh, sizeof( fromdh ) -1 ) == FALSE )
		return HRC_INVALID_VALUE;
	if ( ZbmlCopyToHostData( todh, pToDh, sizeof( todh ) -1 ) == FALSE )
		return HRC_INVALID_VALUE;

	
/*
EXEC SQL DECLARE c4 CURSOR FOR
	SELECT
		SUBSTR(TO_CHAR(NIN.TRKDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15),
		COALESCE(IRI.SKFLG, '0'),
		COUNT(NIN.TRKDH)
	FROM
		NINSIKI NIN
		LEFT OUTER JOIN
			(
				SELECT DISTINCT
					UTKYMD,
					IRINO,
					SKFLG
				FROM
					IRAI
			) IRI
		ON	NIN.UTKYMD = IRI.UTKYMD
		AND NIN.IRINO = IRI.IRINO
	WHERE
			NIN.TRKDH >= :fromdh
		AND NIN.TRKDH < :todh
	GROUP BY
		SUBSTR(TO_CHAR(NIN.TRKDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15),
		IRI.SKFLG
	ORDER BY
		SUBSTR(TO_CHAR(NIN.TRKDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15),
		IRI.SKFLG
		FOR READ ONLY;
*/

#line 396 "JD112Syukei.sqc"


	
/*
EXEC SQL OPEN c4;
*/

{
#line 398 "JD112Syukei.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 398 "JD112Syukei.sqc"
  sqlaaloc(2,2,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 398 "JD112Syukei.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 27;
#line 398 "JD112Syukei.sqc"
      sql_setdlist[0].sqldata = (void*)fromdh;
#line 398 "JD112Syukei.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 398 "JD112Syukei.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 27;
#line 398 "JD112Syukei.sqc"
      sql_setdlist[1].sqldata = (void*)todh;
#line 398 "JD112Syukei.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 398 "JD112Syukei.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 398 "JD112Syukei.sqc"
  sqlacall((unsigned short)26,4,2,0,0L);
#line 398 "JD112Syukei.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 398 "JD112Syukei.sqc"
  sqlastop(0L);
}

#line 398 "JD112Syukei.sqc"


	while( 1 ) {
		JD112Syukei* rec;

		
/*
EXEC SQL FETCH c4 INTO
			:jikan,
			:skflg,
			:count;
*/

{
#line 406 "JD112Syukei.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 406 "JD112Syukei.sqc"
  sqlaaloc(3,3,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 406 "JD112Syukei.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 27;
#line 406 "JD112Syukei.sqc"
      sql_setdlist[0].sqldata = (void*)jikan;
#line 406 "JD112Syukei.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 406 "JD112Syukei.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 406 "JD112Syukei.sqc"
      sql_setdlist[1].sqldata = (void*)&skflg;
#line 406 "JD112Syukei.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 406 "JD112Syukei.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 406 "JD112Syukei.sqc"
      sql_setdlist[2].sqldata = (void*)&count;
#line 406 "JD112Syukei.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 406 "JD112Syukei.sqc"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 406 "JD112Syukei.sqc"
  sqlacall((unsigned short)25,4,0,3,0L);
#line 406 "JD112Syukei.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 406 "JD112Syukei.sqc"
  sqlastop(0L);
}

#line 406 "JD112Syukei.sqc"


		if( SQLCODE == 100 )
			break;

		if( num % ALLOC_UNIT == 0 ) {
			array = (JD112Syukei *)ZbmlRealloc( array,
												sizeof( JD112Syukei ) * ( num + ALLOC_UNIT ) );
			memset( array + num, 0, sizeof( JD112Syukei ) * ALLOC_UNIT );
		}

		rec = array + num++;
		ZbmlMapHostToStruct( (char*)rec, JD112SyukeiArray );
	}

	
/*
EXEC SQL CLOSE c4;
*/

{
#line 421 "JD112Syukei.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 421 "JD112Syukei.sqc"
  sqlacall((unsigned short)20,4,0,0,0L);
#line 421 "JD112Syukei.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 421 "JD112Syukei.sqc"
  sqlastop(0L);
}

#line 421 "JD112Syukei.sqc"


	*arrayOut = array;
	*numOut   = num;

	return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 429 "JD112Syukei.sqc"

	return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbJD112SelectCountE()
 *    患者数集計
 * ■引数
 *    [I]  char* pFromDh			検索対象日時From
 *    [I]  char* pToDh				検索対象日時To
 *    [O]  JD112Syukei** arrayOut	取得レコード配列格納領域
 *    [O]  int* numOut				取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbJD112SelectCountE( char *pFromDh, char *pToDh, JD112Syukei** arrayOut, int* numOut )
{
	JD112Syukei	*array = NULL;
	int			num = 0;

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 451 "JD112Syukei.sqc"


	if ( ZbmlCopyToHostData( fromdh, pFromDh, sizeof( fromdh ) -1 ) == FALSE )
		return HRC_INVALID_VALUE;
	if ( ZbmlCopyToHostData( todh, pToDh, sizeof( todh ) -1 ) == FALSE )
		return HRC_INVALID_VALUE;

	
/*
EXEC SQL DECLARE c5 CURSOR FOR
	SELECT
		SUBSTR(TO_CHAR(KZK.TRKDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15),
		COALESCE(IRI.SKFLG, '0'),
		COUNT(KZK.TRKDH)
	FROM
		KENZOK KZK
		LEFT OUTER JOIN
			(
				SELECT DISTINCT
					UTKYMD,
					IRINO,
					SKFLG
				FROM
					IRAI
			) IRI
		ON	KZK.UTKYMD = IRI.UTKYMD
		AND KZK.IRINO = IRI.IRINO
	WHERE
			KZK.TRKDH >= :fromdh
		AND KZK.TRKDH < :todh
	GROUP BY
		SUBSTR(TO_CHAR(KZK.TRKDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15),
		IRI.SKFLG
	ORDER BY
		SUBSTR(TO_CHAR(KZK.TRKDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15),
		IRI.SKFLG
		FOR READ ONLY;
*/

#line 485 "JD112Syukei.sqc"


	
/*
EXEC SQL OPEN c5;
*/

{
#line 487 "JD112Syukei.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 487 "JD112Syukei.sqc"
  sqlaaloc(2,2,9,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 487 "JD112Syukei.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 27;
#line 487 "JD112Syukei.sqc"
      sql_setdlist[0].sqldata = (void*)fromdh;
#line 487 "JD112Syukei.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 487 "JD112Syukei.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 27;
#line 487 "JD112Syukei.sqc"
      sql_setdlist[1].sqldata = (void*)todh;
#line 487 "JD112Syukei.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 487 "JD112Syukei.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 487 "JD112Syukei.sqc"
  sqlacall((unsigned short)26,5,2,0,0L);
#line 487 "JD112Syukei.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 487 "JD112Syukei.sqc"
  sqlastop(0L);
}

#line 487 "JD112Syukei.sqc"


	while( 1 ) {
		JD112Syukei* rec;

		
/*
EXEC SQL FETCH c5 INTO
			:jikan,
			:skflg,
			:count;
*/

{
#line 495 "JD112Syukei.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 495 "JD112Syukei.sqc"
  sqlaaloc(3,3,10,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 495 "JD112Syukei.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 27;
#line 495 "JD112Syukei.sqc"
      sql_setdlist[0].sqldata = (void*)jikan;
#line 495 "JD112Syukei.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 495 "JD112Syukei.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 495 "JD112Syukei.sqc"
      sql_setdlist[1].sqldata = (void*)&skflg;
#line 495 "JD112Syukei.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 495 "JD112Syukei.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 495 "JD112Syukei.sqc"
      sql_setdlist[2].sqldata = (void*)&count;
#line 495 "JD112Syukei.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 495 "JD112Syukei.sqc"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 495 "JD112Syukei.sqc"
  sqlacall((unsigned short)25,5,0,3,0L);
#line 495 "JD112Syukei.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 495 "JD112Syukei.sqc"
  sqlastop(0L);
}

#line 495 "JD112Syukei.sqc"


		if( SQLCODE == 100 )
			break;

		if( num % ALLOC_UNIT == 0 ) {
			array = (JD112Syukei *)ZbmlRealloc( array,
												sizeof( JD112Syukei ) * ( num + ALLOC_UNIT ) );
			memset( array + num, 0, sizeof( JD112Syukei ) * ALLOC_UNIT );
		}

		rec = array + num++;
		ZbmlMapHostToStruct( (char*)rec, JD112SyukeiArray );
	}

	
/*
EXEC SQL CLOSE c5;
*/

{
#line 510 "JD112Syukei.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 510 "JD112Syukei.sqc"
  sqlacall((unsigned short)20,5,0,0,0L);
#line 510 "JD112Syukei.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 510 "JD112Syukei.sqc"
  sqlastop(0L);
}

#line 510 "JD112Syukei.sqc"


	*arrayOut = array;
	*numOut   = num;

	return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 518 "JD112Syukei.sqc"

	return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbJD112SelectCountFGHIJ()
 *    患者数集計
 * ■引数
 *    [I]  char* pFromDt			検索対象日時From
 *    [I]  char* pToDt				検索対象日時To
 *    [I]  char* pWkupApp			起動アプリ名
 *    [O]  JD112Syukei** arrayOut	取得レコード配列格納領域
 *    [O]  int* numOut				取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbJD112SelectCountFGHIJ( char *pFromDt, char *pToDt, char *pWkupApp,
							   JD112Syukei** arrayOut, int* numOut )
{
	JD112Syukei	*array = NULL;
	int			num = 0;

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 542 "JD112Syukei.sqc"


/* 1.04 DELL
//	if ( ZbmlCopyToHostData( fromdatetime, pFromDt, sizeof( fromdatetime ) -1 ) == FALSE )
//		return HRC_INVALID_VALUE;
//	if ( ZbmlCopyToHostData( todatetime, pToDt, sizeof( todatetime ) -1 ) == FALSE )
//		return HRC_INVALID_VALUE;
*/
	
/* DELL
	sprintf( fromdatetime,	"%.8s%.8s", pFromDt,	&pFromDt[11] );
	sprintf( todatetime,	"%.8s%.8s", pToDt,		&pToDt[11] );
*/
	sprintf( fromdatetime,	"%.10s%.8s", pFromDt,	&pFromDt[11] );
	sprintf( todatetime,	"%.10s%.8s", pToDt,		&pToDt[11] );

	if ( ZbmlCopyToHostData( wkupapp, pWkupApp, sizeof( wkupapp ) -1 ) == FALSE )
		return HRC_INVALID_VALUE;

/* 1.04 DELL
	EXEC SQL DECLARE c6 CURSOR FOR
	SELECT
		SUBSTR(CHAR(SYTIME), 1, 2),
		COUNT(*)
	FROM
		APLLOG
	WHERE
			CHAR(SYDATE) || CHAR(SYTIME) >= :fromdatetime
		AND CHAR(SYDATE) || CHAR(SYTIME) < :todatetime
		AND TRACEKBN IN ('W', 'E', 'A')
		AND WKUPAPP = :wkupapp
	GROUP BY
		SUBSTR(CHAR(SYTIME), 1, 2)
	ORDER BY
		SUBSTR(CHAR(SYTIME), 1, 2)
		FOR READ ONLY;
*/

	
/*
EXEC SQL DECLARE c6 CURSOR FOR
	SELECT
		CHAR(SYDATE) || ' ' || SUBSTR(CHAR(SYTIME), 1, 4),
		COUNT(*)
	FROM
		APLLOG
	WHERE
			CHAR(SYDATE) || CHAR(SYTIME) >= :fromdatetime
		AND CHAR(SYDATE) || CHAR(SYTIME) < :todatetime
		AND TRACEKBN IN ('W', 'E', 'A')
		AND WKUPAPP = :wkupapp
	GROUP BY
		CHAR(SYDATE) || ' ' || SUBSTR(CHAR(SYTIME), 1, 4)
	ORDER BY
		CHAR(SYDATE) || ' ' || SUBSTR(CHAR(SYTIME), 1, 4)
	FOR READ ONLY;
*/

#line 595 "JD112Syukei.sqc"


	
/*
EXEC SQL OPEN c6;
*/

{
#line 597 "JD112Syukei.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 597 "JD112Syukei.sqc"
  sqlaaloc(2,3,11,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 597 "JD112Syukei.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 19;
#line 597 "JD112Syukei.sqc"
      sql_setdlist[0].sqldata = (void*)fromdatetime;
#line 597 "JD112Syukei.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 597 "JD112Syukei.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 19;
#line 597 "JD112Syukei.sqc"
      sql_setdlist[1].sqldata = (void*)todatetime;
#line 597 "JD112Syukei.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 597 "JD112Syukei.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 33;
#line 597 "JD112Syukei.sqc"
      sql_setdlist[2].sqldata = (void*)wkupapp;
#line 597 "JD112Syukei.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 597 "JD112Syukei.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 597 "JD112Syukei.sqc"
  sqlacall((unsigned short)26,6,2,0,0L);
#line 597 "JD112Syukei.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 597 "JD112Syukei.sqc"
  sqlastop(0L);
}

#line 597 "JD112Syukei.sqc"


	while( 1 ) {
		JD112Syukei* rec;

		
/*
EXEC SQL FETCH c6 INTO
			:jikan,
			:count;
*/

{
#line 604 "JD112Syukei.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 604 "JD112Syukei.sqc"
  sqlaaloc(3,2,12,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 604 "JD112Syukei.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 27;
#line 604 "JD112Syukei.sqc"
      sql_setdlist[0].sqldata = (void*)jikan;
#line 604 "JD112Syukei.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 604 "JD112Syukei.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 604 "JD112Syukei.sqc"
      sql_setdlist[1].sqldata = (void*)&count;
#line 604 "JD112Syukei.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 604 "JD112Syukei.sqc"
      sqlasetdata(3,0,2,sql_setdlist,0L,0L);
    }
#line 604 "JD112Syukei.sqc"
  sqlacall((unsigned short)25,6,0,3,0L);
#line 604 "JD112Syukei.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 604 "JD112Syukei.sqc"
  sqlastop(0L);
}

#line 604 "JD112Syukei.sqc"


		if( SQLCODE == 100 )
			break;

		if( num % ALLOC_UNIT == 0 ) {
			array = (JD112Syukei *)ZbmlRealloc( array,
												sizeof( JD112Syukei ) * ( num + ALLOC_UNIT ) );
			memset( array + num, 0, sizeof( JD112Syukei ) * ALLOC_UNIT );
		}

		rec = array + num++;
		ZbmlMapHostToStruct( (char*)rec, JD112SyukeiArray );
	}

	
/*
EXEC SQL CLOSE c6;
*/

{
#line 619 "JD112Syukei.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 619 "JD112Syukei.sqc"
  sqlacall((unsigned short)20,6,0,0,0L);
#line 619 "JD112Syukei.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 619 "JD112Syukei.sqc"
  sqlastop(0L);
}

#line 619 "JD112Syukei.sqc"


	*arrayOut = array;
	*numOut   = num;

	return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 627 "JD112Syukei.sqc"

	return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbJD112SelectCountKM()
 *    投入数、測定数集計
 * ■引数
 *    [I]  char* pFromDh			検索対象日時From
 *    [I]  char* pToDh				検索対象日時To
 *    [I]  char cKnsJkFlg			検査状況フラグ
 *    [O]  JD112Syukei** arrayOut	取得レコード配列格納領域
 *    [O]  int* numOut				取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbJD112SelectCountKM( char *pFromDh, char *pToDh, char cKnsJkFlg, JD112Syukei** arrayOut, int* numOut )
{
	JD112Syukei	*array = NULL;
	int			num = 0;

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 650 "JD112Syukei.sqc"


	if ( ZbmlCopyToHostData( fromdh, pFromDh, sizeof( fromdh ) -1 ) == FALSE )
		return HRC_INVALID_VALUE;
	if ( ZbmlCopyToHostData( todh, pToDh, sizeof( todh ) -1 ) == FALSE )
		return HRC_INVALID_VALUE;
	knsjkflg = cKnsJkFlg;

	
/*
EXEC SQL DECLARE c7 CURSOR FOR
	SELECT
		SUBSTR(TO_CHAR(POS.TRKDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15),
		COALESCE(IRI.SKFLG, '0'),
		COUNT(POS.TRKDH)
	FROM
		KENPOS POS
		LEFT OUTER JOIN
			(
				SELECT DISTINCT
					UTKYMD,
					IRINO,
					SKFLG
				FROM
					IRAI
			) IRI
		ON	POS.UTKYMD = IRI.UTKYMD
		AND POS.IRINO = IRI.IRINO
	WHERE
			POS.TRKDH >= :fromdh
		AND POS.TRKDH < :todh
		AND POS.RAKITJHO = :knsjkflg
	GROUP BY
		SUBSTR(TO_CHAR(POS.TRKDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15),
		IRI.SKFLG
	ORDER BY
		SUBSTR(TO_CHAR(POS.TRKDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15),
		IRI.SKFLG
		FOR READ ONLY;
*/

#line 686 "JD112Syukei.sqc"


	
/*
EXEC SQL OPEN c7;
*/

{
#line 688 "JD112Syukei.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 688 "JD112Syukei.sqc"
  sqlaaloc(2,3,13,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 688 "JD112Syukei.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 27;
#line 688 "JD112Syukei.sqc"
      sql_setdlist[0].sqldata = (void*)fromdh;
#line 688 "JD112Syukei.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 688 "JD112Syukei.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 27;
#line 688 "JD112Syukei.sqc"
      sql_setdlist[1].sqldata = (void*)todh;
#line 688 "JD112Syukei.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 688 "JD112Syukei.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 688 "JD112Syukei.sqc"
      sql_setdlist[2].sqldata = (void*)&knsjkflg;
#line 688 "JD112Syukei.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 688 "JD112Syukei.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 688 "JD112Syukei.sqc"
  sqlacall((unsigned short)26,7,2,0,0L);
#line 688 "JD112Syukei.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 688 "JD112Syukei.sqc"
  sqlastop(0L);
}

#line 688 "JD112Syukei.sqc"


	while( 1 ) {
		JD112Syukei* rec;

		
/*
EXEC SQL FETCH c7 INTO
			:jikan,
			:skflg,
			:count;
*/

{
#line 696 "JD112Syukei.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 696 "JD112Syukei.sqc"
  sqlaaloc(3,3,14,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 696 "JD112Syukei.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 27;
#line 696 "JD112Syukei.sqc"
      sql_setdlist[0].sqldata = (void*)jikan;
#line 696 "JD112Syukei.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 696 "JD112Syukei.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 696 "JD112Syukei.sqc"
      sql_setdlist[1].sqldata = (void*)&skflg;
#line 696 "JD112Syukei.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 696 "JD112Syukei.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 696 "JD112Syukei.sqc"
      sql_setdlist[2].sqldata = (void*)&count;
#line 696 "JD112Syukei.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 696 "JD112Syukei.sqc"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 696 "JD112Syukei.sqc"
  sqlacall((unsigned short)25,7,0,3,0L);
#line 696 "JD112Syukei.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 696 "JD112Syukei.sqc"
  sqlastop(0L);
}

#line 696 "JD112Syukei.sqc"


		if( SQLCODE == 100 )
			break;

		if( num % ALLOC_UNIT == 0 ) {
			array = (JD112Syukei *)ZbmlRealloc( array,
												sizeof( JD112Syukei ) * ( num + ALLOC_UNIT ) );
			memset( array + num, 0, sizeof( JD112Syukei ) * ALLOC_UNIT );
		}

		rec = array + num++;
		ZbmlMapHostToStruct( (char*)rec, JD112SyukeiArray );
	}

	
/*
EXEC SQL CLOSE c7;
*/

{
#line 711 "JD112Syukei.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 711 "JD112Syukei.sqc"
  sqlacall((unsigned short)20,7,0,0,0L);
#line 711 "JD112Syukei.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 711 "JD112Syukei.sqc"
  sqlastop(0L);
}

#line 711 "JD112Syukei.sqc"


	*arrayOut = array;
	*numOut   = num;

	return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 719 "JD112Syukei.sqc"

	return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbJD112SelectCountL()
 *    依頼数集計
 * ■引数
 *    [I]  char* pFromDh			検索対象日時From
 *    [I]  char* pToDh				検索対象日時To
 *    [O]  JD112Syukei** arrayOut	取得レコード配列格納領域
 *    [O]  int* numOut				取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbJD112SelectCountL( char *pFromDh, char *pToDh, JD112Syukei** arrayOut, int* numOut )
{
	JD112Syukei	*array = NULL;
	int			num = 0;

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 741 "JD112Syukei.sqc"


	if ( ZbmlCopyToHostData( fromdh, pFromDh, sizeof( fromdh ) -1 ) == FALSE )
		return HRC_INVALID_VALUE;
	if ( ZbmlCopyToHostData( todh, pToDh, sizeof( todh ) -1 ) == FALSE )
		return HRC_INVALID_VALUE;

/* 1.05 DELL STA ===========================================================
	EXEC SQL DECLARE c8 CURSOR FOR

	SELECT
		BSKKBN,
		BSKLNE,
		JIKAN,
		SKFLG,
		SUM(CNT)
	FROM
		(
			SELECT
				BSKKBN,
				BSKLNE,
				SUBSTR(TO_CHAR(TRKDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15) AS JIKAN,
				SKFLG,
				COUNT(TRKDH) AS CNT
			FROM
				KEKKA
			WHERE
					TRKDH >= :fromdh
				AND TRKDH < :todh
			GROUP BY
				BSKKBN,
				BSKLNE,
				SUBSTR(TO_CHAR(TRKDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15),
				SKFLG
			UNION ALL
			SELECT
				BSKKBN,
				BSKLNE,
				SUBSTR(TO_CHAR(KSNDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15) AS JIKAN,
				'0' AS SKFLG,
				COUNT(KSNDH) AS CNT 
			FROM
				CTRLKKA
			WHERE
					KSNDH >= :fromdh
				AND KSNDH < :todh
			GROUP BY
				BSKKBN,
				BSKLNE,
				SUBSTR(TO_CHAR(KSNDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15)
			UNION ALL
			SELECT
				BSKKBN,
				BSKLNE,
				SUBSTR(TO_CHAR(KSNDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15) AS JIKAN,
				'0' AS SKFLG,
				COUNT(KSNDH) AS CNT 
			FROM
				STANDARD
			WHERE
					KSNDH >= :fromdh
				AND KSNDH < :todh
			GROUP BY
				BSKKBN,
				BSKLNE,
				SUBSTR(TO_CHAR(KSNDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15)
		) AS TEMP
	GROUP BY
		BSKKBN,
		BSKLNE,
		JIKAN,
		SKFLG
	ORDER BY
		BSKKBN,
		BSKLNE,
		JIKAN,
		SKFLG
		FOR READ ONLY;
 1.05 DELL END ==================================================*/
	// 1.05 初回結果のみを対象として検体NO単位に集計する
	// 1.06 結果の集検フラグは空白も存在するためcase文でまとめる
	
/*
EXEC SQL DECLARE c8 CURSOR FOR

	SELECT
		BSKKBN,
		BSKLNE,
		SUBSTR(TO_CHAR(TRKDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15) AS JIKAN,
		SKFLG,
--		( case SKFLG when ' ' then '0' else  SKFLG end ) as SKFLG,
		COUNT(DISTINCT KNTNO)
	FROM
		(
		SELECT
			BSKKBN,
			BSKLNE,
--			SKFLG,									-- 1.06 
			( case SKFLG when '1' then '1' else '0' end ) as SKFLG,
			KNTNO,
			TRKDH
		FROM
			KEKKA
		WHERE
			TRKDH >= :fromdh
			AND TRKDH < :todh
			AND KNSSU=1
		
	) AS TEMP
	GROUP BY
		BSKKBN,
		BSKLNE,
		SUBSTR(TO_CHAR(TRKDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15) ,
		SKFLG
	ORDER BY
		BSKKBN,
		BSKLNE,
		SUBSTR(TO_CHAR(TRKDH, 'YYYY-MM-DD HH24:MI:SS'), 1, 15) ,
		SKFLG
		FOR READ ONLY;
*/

#line 858 "JD112Syukei.sqc"


	
/*
EXEC SQL OPEN c8;
*/

{
#line 860 "JD112Syukei.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 860 "JD112Syukei.sqc"
  sqlaaloc(2,2,15,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 860 "JD112Syukei.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 27;
#line 860 "JD112Syukei.sqc"
      sql_setdlist[0].sqldata = (void*)fromdh;
#line 860 "JD112Syukei.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 860 "JD112Syukei.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 27;
#line 860 "JD112Syukei.sqc"
      sql_setdlist[1].sqldata = (void*)todh;
#line 860 "JD112Syukei.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 860 "JD112Syukei.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 860 "JD112Syukei.sqc"
  sqlacall((unsigned short)26,8,2,0,0L);
#line 860 "JD112Syukei.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 860 "JD112Syukei.sqc"
  sqlastop(0L);
}

#line 860 "JD112Syukei.sqc"


	while( 1 ) {
		JD112Syukei* rec;

		
/*
EXEC SQL FETCH c8 INTO
			:bskkbn,
			:bsklne,
			:jikan,
			:skflg,
			:count;
*/

{
#line 870 "JD112Syukei.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 870 "JD112Syukei.sqc"
  sqlaaloc(3,5,16,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 870 "JD112Syukei.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 870 "JD112Syukei.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 870 "JD112Syukei.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 870 "JD112Syukei.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 870 "JD112Syukei.sqc"
      sql_setdlist[1].sqldata = (void*)bsklne;
#line 870 "JD112Syukei.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 870 "JD112Syukei.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 27;
#line 870 "JD112Syukei.sqc"
      sql_setdlist[2].sqldata = (void*)jikan;
#line 870 "JD112Syukei.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 870 "JD112Syukei.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 870 "JD112Syukei.sqc"
      sql_setdlist[3].sqldata = (void*)&skflg;
#line 870 "JD112Syukei.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 870 "JD112Syukei.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 870 "JD112Syukei.sqc"
      sql_setdlist[4].sqldata = (void*)&count;
#line 870 "JD112Syukei.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 870 "JD112Syukei.sqc"
      sqlasetdata(3,0,5,sql_setdlist,0L,0L);
    }
#line 870 "JD112Syukei.sqc"
  sqlacall((unsigned short)25,8,0,3,0L);
#line 870 "JD112Syukei.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 870 "JD112Syukei.sqc"
  sqlastop(0L);
}

#line 870 "JD112Syukei.sqc"


		if( SQLCODE == 100 )
			break;

		if( num % ALLOC_UNIT == 0 ) {
			array = (JD112Syukei *)ZbmlRealloc( array,
												sizeof( JD112Syukei ) * ( num + ALLOC_UNIT ) );
			memset( array + num, 0, sizeof( JD112Syukei ) * ALLOC_UNIT );
		}

		rec = array + num++;
		ZbmlMapHostToStruct( (char*)rec, JD112SyukeiArray );
	}

	
/*
EXEC SQL CLOSE c8;
*/

{
#line 885 "JD112Syukei.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 885 "JD112Syukei.sqc"
  sqlacall((unsigned short)20,8,0,0,0L);
#line 885 "JD112Syukei.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 885 "JD112Syukei.sqc"
  sqlastop(0L);
}

#line 885 "JD112Syukei.sqc"


	*arrayOut = array;
	*numOut   = num;

	return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 893 "JD112Syukei.sqc"

	return sqlca.sqlcode;
}
/** End of File *********************************************************/
