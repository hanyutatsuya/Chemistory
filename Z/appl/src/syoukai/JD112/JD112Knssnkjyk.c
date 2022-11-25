static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,108,66,66,53,81,74,77,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,74,68,49,49,50,75,78,83,0,0,0,0,0,0,0,0,
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


#line 1 "JD112Knssnkjyk.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： JD112Knssnkjyk.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-03-23                    Create
 **********************************************************************/
#include <stdio.h>

#include "JD112Knssnkjyk.h"
#include "bml_misc.h"
#include "bml_db.h"
#include "bml_dmm.h"

#define ALLOC_UNIT		1
#define MAX_DATE		"2100-12-31"				// ADD 1.05


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 25 "JD112Knssnkjyk.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 30 "JD112Knssnkjyk.sqc"

	char    knskisymd[11];
	sqlint32  keikseq;
	char    koteikbn;
	char    datazok;
	char    bskkbn[5];
	char    bskgok[7];
	sqlint32  syukka;
	char    jikan[5];
	char    ksndh[27];
	char    knskisymd2[27];					// ADD

/*
EXEC SQL END DECLARE SECTION;
*/

#line 41 "JD112Knssnkjyk.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Knssnkjyk

BmlDMMInfo	KnssnkjykArray[] = {
	DMM_SDATE( knskisymd ),
	DMM_SLONG( keikseq ),
	DMM_SCHAR( koteikbn ),
	DMM_SCHAR( datazok ),
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( bskgok ),
	DMM_SLONG( syukka ),
	DMM_SSTRING( jikan ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKnssnkjykJD112SelectJikan()
 *    KNSSNKJYK 同一時間帯のレコード取得
 * ■引数
 *    [I]  Knssnkjyk* pKey		取得するレコードのキー
 *    [O]  Knssnkjyk* pRec		取得レコード配列格納領域
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKnssnkjykJD112SelectJikan( Knssnkjyk* pKey, Knssnkjyk* pRec )
{
    if( !pKey || !pRec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KnssnkjykArray ) )
        return HRC_INVALID_VALUE;

	
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 81 "JD112Knssnkjyk.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 82 "JD112Knssnkjyk.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSKISYMD,
		KEIKSEQ,
		KOTEIKBN,
		DATAZOK,
		BSKKBN,
		BSKGOK,
		SYUKKA,
		JIKAN,
		KSNDH
    FROM
        KNSSNKJYK
    WHERE
		KNSKISYMD = :knskisymd AND
		KOTEIKBN = :koteikbn AND
		DATAZOK = :datazok AND
		BSKKBN = :bskkbn AND
		BSKGOK = :bskgok AND
		JIKAN = :jikan
		FOR READ ONLY;
*/

#line 104 "JD112Knssnkjyk.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 106 "JD112Knssnkjyk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 106 "JD112Knssnkjyk.sqc"
  sqlaaloc(2,6,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 106 "JD112Knssnkjyk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 106 "JD112Knssnkjyk.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 106 "JD112Knssnkjyk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 106 "JD112Knssnkjyk.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 106 "JD112Knssnkjyk.sqc"
      sql_setdlist[1].sqldata = (void*)&koteikbn;
#line 106 "JD112Knssnkjyk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 106 "JD112Knssnkjyk.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 106 "JD112Knssnkjyk.sqc"
      sql_setdlist[2].sqldata = (void*)&datazok;
#line 106 "JD112Knssnkjyk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 106 "JD112Knssnkjyk.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 106 "JD112Knssnkjyk.sqc"
      sql_setdlist[3].sqldata = (void*)bskkbn;
#line 106 "JD112Knssnkjyk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 106 "JD112Knssnkjyk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 7;
#line 106 "JD112Knssnkjyk.sqc"
      sql_setdlist[4].sqldata = (void*)bskgok;
#line 106 "JD112Knssnkjyk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 106 "JD112Knssnkjyk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 5;
#line 106 "JD112Knssnkjyk.sqc"
      sql_setdlist[5].sqldata = (void*)jikan;
#line 106 "JD112Knssnkjyk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 106 "JD112Knssnkjyk.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 106 "JD112Knssnkjyk.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 106 "JD112Knssnkjyk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 106 "JD112Knssnkjyk.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 106 "JD112Knssnkjyk.sqc"
  sqlastop(0L);
}

#line 106 "JD112Knssnkjyk.sqc"


	
/*
EXEC SQL FETCH c1 INTO
			:knskisymd,
			:keikseq,
			:koteikbn,
			:datazok,
			:bskkbn,
			:bskgok,
			:syukka,
			:jikan,
			:ksndh;
*/

{
#line 117 "JD112Knssnkjyk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 117 "JD112Knssnkjyk.sqc"
  sqlaaloc(3,9,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[1].sqldata = (void*)&keikseq;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[2].sqldata = (void*)&koteikbn;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[3].sqldata = (void*)&datazok;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 5;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[4].sqldata = (void*)bskkbn;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 7;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[5].sqldata = (void*)bskgok;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[6].sqldata = (void*)&syukka;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 5;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[7].sqldata = (void*)jikan;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 117 "JD112Knssnkjyk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 117 "JD112Knssnkjyk.sqc"
      sqlasetdata(3,0,9,sql_setdlist,0L,0L);
    }
#line 117 "JD112Knssnkjyk.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 117 "JD112Knssnkjyk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 117 "JD112Knssnkjyk.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 117 "JD112Knssnkjyk.sqc"
  sqlastop(0L);
}

#line 117 "JD112Knssnkjyk.sqc"


	ZbmlMapHostToStruct( (char*)pRec, KnssnkjykArray );

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 121 "JD112Knssnkjyk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 121 "JD112Knssnkjyk.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 121 "JD112Knssnkjyk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 121 "JD112Knssnkjyk.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 121 "JD112Knssnkjyk.sqc"
  sqlastop(0L);
}

#line 121 "JD112Knssnkjyk.sqc"


    return HRC_SQL_NORMAL;

notfound:
	
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 126 "JD112Knssnkjyk.sqc"

	return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 130 "JD112Knssnkjyk.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKnssnkjykInsert()
 *    KNSSNKJYK レコードを挿入する
 * ■引数
 *    [I]  Knssnkjyk* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKnssnkjykInsert( Knssnkjyk* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KnssnkjykArray ) )
        return HRC_INVALID_VALUE;

	// ADD
	strcpy( knskisymd2,	MAX_DATE );

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 156 "JD112Knssnkjyk.sqc"


    
/*
EXEC SQL INSERT INTO KNSSNKJYK
    (
		KNSKISYMD,
		KEIKSEQ,
		KOTEIKBN,
		DATAZOK,
		BSKKBN,
		BSKGOK,
		SYUKKA,
		JIKAN,
		KSNDH
		, KNSKISYMD2		
    ) VALUES (
		:knskisymd,
		:keikseq,
		:koteikbn,
		:datazok,
		:bskkbn,
		:bskgok,
		:syukka,
		:jikan,
--		:ksndh
		CURRENT TIMESTAMP
		,:knskisymd2	
    );
*/

{
#line 182 "JD112Knssnkjyk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 182 "JD112Knssnkjyk.sqc"
  sqlaaloc(2,9,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[1].sqldata = (void*)&keikseq;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[2].sqldata = (void*)&koteikbn;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[3].sqldata = (void*)&datazok;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 5;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[4].sqldata = (void*)bskkbn;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 7;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[5].sqldata = (void*)bskgok;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[6].sqldata = (void*)&syukka;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 5;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[7].sqldata = (void*)jikan;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[8].sqldata = (void*)knskisymd2;
#line 182 "JD112Knssnkjyk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 182 "JD112Knssnkjyk.sqc"
      sqlasetdata(2,0,9,sql_setdlist,0L,0L);
    }
#line 182 "JD112Knssnkjyk.sqc"
  sqlacall((unsigned short)24,2,2,0,0L);
#line 182 "JD112Knssnkjyk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 182 "JD112Knssnkjyk.sqc"
  sqlastop(0L);
}

#line 182 "JD112Knssnkjyk.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 187 "JD112Knssnkjyk.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKnssnkjykUpdate()
 *    KNSSNKJYK レコードを更新する
 * ■引数
 *    [I]  Knssnkjyk* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKnssnkjykUpdate( Knssnkjyk* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KnssnkjykArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 211 "JD112Knssnkjyk.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 212 "JD112Knssnkjyk.sqc"


    
/*
EXEC SQL UPDATE KNSSNKJYK
    SET (
		SYUKKA,
		JIKAN,
		KSNDH
    ) = (
		:syukka,
		:jikan,
--		:ksndh
		CURRENT TIMESTAMP
    ) WHERE
		KNSKISYMD = :knskisymd AND
		KEIKSEQ = :keikseq AND
		KOTEIKBN = :koteikbn AND
		DATAZOK = :datazok AND
		BSKKBN = :bskkbn AND
		BSKGOK = :bskgok;
*/

{
#line 230 "JD112Knssnkjyk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 230 "JD112Knssnkjyk.sqc"
  sqlaaloc(2,8,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 230 "JD112Knssnkjyk.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 230 "JD112Knssnkjyk.sqc"
      sql_setdlist[0].sqldata = (void*)&syukka;
#line 230 "JD112Knssnkjyk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 230 "JD112Knssnkjyk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 230 "JD112Knssnkjyk.sqc"
      sql_setdlist[1].sqldata = (void*)jikan;
#line 230 "JD112Knssnkjyk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 230 "JD112Knssnkjyk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 230 "JD112Knssnkjyk.sqc"
      sql_setdlist[2].sqldata = (void*)knskisymd;
#line 230 "JD112Knssnkjyk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 230 "JD112Knssnkjyk.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 230 "JD112Knssnkjyk.sqc"
      sql_setdlist[3].sqldata = (void*)&keikseq;
#line 230 "JD112Knssnkjyk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 230 "JD112Knssnkjyk.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 230 "JD112Knssnkjyk.sqc"
      sql_setdlist[4].sqldata = (void*)&koteikbn;
#line 230 "JD112Knssnkjyk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 230 "JD112Knssnkjyk.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 230 "JD112Knssnkjyk.sqc"
      sql_setdlist[5].sqldata = (void*)&datazok;
#line 230 "JD112Knssnkjyk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 230 "JD112Knssnkjyk.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 5;
#line 230 "JD112Knssnkjyk.sqc"
      sql_setdlist[6].sqldata = (void*)bskkbn;
#line 230 "JD112Knssnkjyk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 230 "JD112Knssnkjyk.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 7;
#line 230 "JD112Knssnkjyk.sqc"
      sql_setdlist[7].sqldata = (void*)bskgok;
#line 230 "JD112Knssnkjyk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 230 "JD112Knssnkjyk.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 230 "JD112Knssnkjyk.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 230 "JD112Knssnkjyk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 230 "JD112Knssnkjyk.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 230 "JD112Knssnkjyk.sqc"
  sqlastop(0L);
}

#line 230 "JD112Knssnkjyk.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 235 "JD112Knssnkjyk.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 239 "JD112Knssnkjyk.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKnssnkjykDelete()
 *    KNSSNKJYK レコードを削除する
 * ■引数
 *    [I]  Knssnkjyk* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKnssnkjykDelete( Knssnkjyk* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KnssnkjykArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 263 "JD112Knssnkjyk.sqc"


    
/*
EXEC SQL DELETE FROM KNSSNKJYK
    WHERE
		KNSKISYMD = :knskisymd AND
		KEIKSEQ = :keikseq AND
		KOTEIKBN = :koteikbn AND
		DATAZOK = :datazok AND
		BSKKBN = :bskkbn AND
		BSKGOK = :bskgok;
*/

{
#line 272 "JD112Knssnkjyk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 272 "JD112Knssnkjyk.sqc"
  sqlaaloc(2,6,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 272 "JD112Knssnkjyk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 272 "JD112Knssnkjyk.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 272 "JD112Knssnkjyk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 272 "JD112Knssnkjyk.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 272 "JD112Knssnkjyk.sqc"
      sql_setdlist[1].sqldata = (void*)&keikseq;
#line 272 "JD112Knssnkjyk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 272 "JD112Knssnkjyk.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 272 "JD112Knssnkjyk.sqc"
      sql_setdlist[2].sqldata = (void*)&koteikbn;
#line 272 "JD112Knssnkjyk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 272 "JD112Knssnkjyk.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 272 "JD112Knssnkjyk.sqc"
      sql_setdlist[3].sqldata = (void*)&datazok;
#line 272 "JD112Knssnkjyk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 272 "JD112Knssnkjyk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 5;
#line 272 "JD112Knssnkjyk.sqc"
      sql_setdlist[4].sqldata = (void*)bskkbn;
#line 272 "JD112Knssnkjyk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 272 "JD112Knssnkjyk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 7;
#line 272 "JD112Knssnkjyk.sqc"
      sql_setdlist[5].sqldata = (void*)bskgok;
#line 272 "JD112Knssnkjyk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 272 "JD112Knssnkjyk.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 272 "JD112Knssnkjyk.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 272 "JD112Knssnkjyk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 272 "JD112Knssnkjyk.sqc"
  sqlastop(0L);
}

#line 272 "JD112Knssnkjyk.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 277 "JD112Knssnkjyk.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
