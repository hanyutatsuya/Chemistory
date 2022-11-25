static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,76,66,98,75,85,97,68,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,49,76,68,49,48,52,32,32,0,0,0,0,0,0,0,0,
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


#line 1 "LD104GetKekka.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： LD104GetKekka.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 **********************************************************************/
#include <stdio.h>

#include "LD104GetKekka.h"
#include "bml_misc.h"
#include "bml_db.h"
#include "bml_dmm.h"

#include "bmllog.h"

#define ALLOC_UNIT		1


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 25 "LD104GetKekka.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 30 "LD104GetKekka.sqc"

	char    utkymd[11];
	char    irino[12];
	char    kmkcd[8];
	char    sriymd[11];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 35 "LD104GetKekka.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	GetKekka

BmlDMMInfo	GetKekkaArray[] = {
	DMM_SDATE( utkymd ),
	DMM_SSTRING( irino ),
	DMM_SSTRING( kmkcd ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKekkaLD104Select()
 *    KEKKA レコード条件取得（検体No）
 * ■引数
 *    [I]  Kekka* pKey       取得するレコードのキー
 *    [O]  Kekka** arrayOut     取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKekkaLD104Select( char* pSysknrmst, GetKekka** arrayOut, int* numOut )
{
	GetKekka*	array = NULL;
	int		num = 0;

	memset( sriymd, 0, sizeof( sriymd ) );
	strcpy( sriymd, pSysknrmst );

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 70 "LD104GetKekka.sqc"


	/* 計算元項目のうち、ケミストリーに依頼が来ておらず、結果取得済みではない項目 */
	
/*
EXEC SQL DECLARE c7 CURSOR FOR
	SELECT
		IRI.UTKYMD,
		IRI.IRINO,
		GETKKA.YKKMKCD
	FROM
		GETSYSKKAMST GETKKA
		INNER JOIN IRAI IRI
			 ON IRI.KMKCD = GETKKA.KMKCD
			AND IRI.UTKYMD >= GETKKA.KAIYMD
			AND IRI.UTKYMD <= GETKKA.HAIYMD
	WHERE
		IRI.SRIYMD >= :sriymd
		AND NOT EXISTS (
				SELECT
					*
				FROM
					KEKKA KKA
				WHERE
					    IRI.UTKYMD = KKA.UTKYMD
					AND IRI.IRINO = KKA.IRINO
					AND IRI.KMKCD = KKA.KMKCD
			)
		AND NOT EXISTS (
				SELECT
					*
				FROM
					OTHERKKA OTHKKA
				WHERE
					    IRI.UTKYMD = OTHKKA.UTKYMD
					AND IRI.IRINO = OTHKKA.IRINO
					AND OTHKKA.KMKCD = GETKKA.YKKMKCD
			)
		AND NOT EXISTS (
				SELECT
					*
				FROM
					IRAI IRI_MOTO
				WHERE
					     IRI_MOTO.UTKYMD = IRI.UTKYMD
					 AND IRI_MOTO.IRINO = IRI.IRINO
					 AND IRI_MOTO.KMKCD = GETKKA.YKKMKCD
		)
	ORDER BY IRI.UTKYMD,IRI.IRINO,IRI.KMKCD,GETKKA.YKKMKCD
	FOR READ ONLY;
*/

#line 117 "LD104GetKekka.sqc"


	
/*
EXEC SQL OPEN c7;
*/

{
#line 119 "LD104GetKekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 119 "LD104GetKekka.sqc"
  sqlaaloc(2,1,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 119 "LD104GetKekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 119 "LD104GetKekka.sqc"
      sql_setdlist[0].sqldata = (void*)sriymd;
#line 119 "LD104GetKekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 119 "LD104GetKekka.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 119 "LD104GetKekka.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 119 "LD104GetKekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 119 "LD104GetKekka.sqc"
  sqlastop(0L);
}

#line 119 "LD104GetKekka.sqc"


	while( 1 ) {
		GetKekka* rec;

		
/*
EXEC SQL FETCH c7 INTO
			:utkymd,
			:irino,
			:kmkcd;
*/

{
#line 127 "LD104GetKekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 127 "LD104GetKekka.sqc"
  sqlaaloc(3,3,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 127 "LD104GetKekka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 127 "LD104GetKekka.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 127 "LD104GetKekka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 127 "LD104GetKekka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 127 "LD104GetKekka.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 127 "LD104GetKekka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 127 "LD104GetKekka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 127 "LD104GetKekka.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 127 "LD104GetKekka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 127 "LD104GetKekka.sqc"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 127 "LD104GetKekka.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 127 "LD104GetKekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 127 "LD104GetKekka.sqc"
  sqlastop(0L);
}

#line 127 "LD104GetKekka.sqc"


		if( SQLCODE == 100 )
			break;

		if( num % ALLOC_UNIT == 0 ) {
			array = (GetKekka*)ZbmlRealloc( array, sizeof( GetKekka ) * ( num + ALLOC_UNIT ) );
			memset( array + num, 0, sizeof( GetKekka ) * ALLOC_UNIT );
		}

		rec = array + num++;
		ZbmlMapHostToStruct( (char*)rec, GetKekkaArray );
	}

	
/*
EXEC SQL CLOSE c7;
*/

{
#line 141 "LD104GetKekka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 141 "LD104GetKekka.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 141 "LD104GetKekka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 141 "LD104GetKekka.sqc"
  sqlastop(0L);
}

#line 141 "LD104GetKekka.sqc"


	*arrayOut = array;
	*numOut   = num;

	return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 149 "LD104GetKekka.sqc"


    	sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbKekkaLD104Select", __LINE__, EXEFLG_SEL, "020", "SQLERR : [%s]", sqlca.sqlerrmc ); 
	return sqlca.sqlcode;
}

/** End of File *********************************************************/
