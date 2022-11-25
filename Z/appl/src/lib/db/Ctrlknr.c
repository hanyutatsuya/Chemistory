static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,54,65,82,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,49,54,90,67,84,82,76,32,0,0,0,0,0,0,0,0,
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


#line 1 "Ctrlknr.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Ctrlknr.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Ctrlknr.h"
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


#line 24 "Ctrlknr.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Ctrlknr.sqc"

	char    knskisymd[11];
	char    bskkbn[5];
	char    bsklne[5];
	char    bskgok[7];
	sqlint32  ctrlno;
	char    ctrlhdflg;
	char    ctrlktflg;
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 38 "Ctrlknr.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Ctrlknr

BmlDMMInfo	CtrlknrArray[] = {
	DMM_SDATE( knskisymd ),
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( bsklne ),
	DMM_SSTRING( bskgok ),
	DMM_SLONG( ctrlno ),
	DMM_SCHAR( ctrlhdflg ),
	DMM_SCHAR( ctrlktflg ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbCtrlknrSelectAll()
 *    CTRLKNR レコード全件取得
 * ■引数
 *    [O]  Ctrlknr** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCtrlknrSelectAll( Ctrlknr** arrayOut, int* numOut )
{
    Ctrlknr*    array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 74 "Ctrlknr.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSKISYMD,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		CTRLNO,
		CTRLHDFLG,
		CTRLKTFLG,
		KSNDH
    FROM
        CTRLKNR FOR READ ONLY;
*/

#line 87 "Ctrlknr.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 89 "Ctrlknr.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 89 "Ctrlknr.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 89 "Ctrlknr.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 89 "Ctrlknr.sqc"
  sqlastop(0L);
}

#line 89 "Ctrlknr.sqc"


    while( 1 ) {
        Ctrlknr* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knskisymd,
			:bskkbn,
			:bsklne,
			:bskgok,
			:ctrlno,
			:ctrlhdflg,
			:ctrlktflg,
			:ksndh;
*/

{
#line 102 "Ctrlknr.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 102 "Ctrlknr.sqc"
  sqlaaloc(3,8,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 102 "Ctrlknr.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 102 "Ctrlknr.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 102 "Ctrlknr.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 102 "Ctrlknr.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 102 "Ctrlknr.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 102 "Ctrlknr.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 102 "Ctrlknr.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 102 "Ctrlknr.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 102 "Ctrlknr.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 102 "Ctrlknr.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 7;
#line 102 "Ctrlknr.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 102 "Ctrlknr.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 102 "Ctrlknr.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 102 "Ctrlknr.sqc"
      sql_setdlist[4].sqldata = (void*)&ctrlno;
#line 102 "Ctrlknr.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 102 "Ctrlknr.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 102 "Ctrlknr.sqc"
      sql_setdlist[5].sqldata = (void*)&ctrlhdflg;
#line 102 "Ctrlknr.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 102 "Ctrlknr.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 102 "Ctrlknr.sqc"
      sql_setdlist[6].sqldata = (void*)&ctrlktflg;
#line 102 "Ctrlknr.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 102 "Ctrlknr.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 102 "Ctrlknr.sqc"
      sql_setdlist[7].sqldata = (void*)ksndh;
#line 102 "Ctrlknr.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 102 "Ctrlknr.sqc"
      sqlasetdata(3,0,8,sql_setdlist,0L,0L);
    }
#line 102 "Ctrlknr.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 102 "Ctrlknr.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 102 "Ctrlknr.sqc"
  sqlastop(0L);
}

#line 102 "Ctrlknr.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Ctrlknr*)ZbmlRealloc( array,
                                    sizeof( Ctrlknr ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Ctrlknr ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, CtrlknrArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 117 "Ctrlknr.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 117 "Ctrlknr.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 117 "Ctrlknr.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 117 "Ctrlknr.sqc"
  sqlastop(0L);
}

#line 117 "Ctrlknr.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 125 "Ctrlknr.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbCtrlknrSelectKey()
 *    CTRLKNR レコードKey条件取得
 * ■引数
 *    [I]  Ctrlknr* pKey       取得するレコードのキー
 *    [O]  Ctrlknr** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCtrlknrSelectKey( Ctrlknr* pKey, Ctrlknr** arrayOut, int* numOut )
{
    Ctrlknr*    array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, CtrlknrArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 151 "Ctrlknr.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSKISYMD,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		CTRLNO,
		CTRLHDFLG,
		CTRLKTFLG,
		KSNDH
    FROM
        CTRLKNR
    WHERE
		KNSKISYMD = :knskisymd AND
		BSKKBN = :bskkbn AND
		BSKGOK = :bskgok AND
		CTRLNO = :ctrlno FOR READ ONLY;
*/

#line 169 "Ctrlknr.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 171 "Ctrlknr.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 171 "Ctrlknr.sqc"
  sqlaaloc(2,4,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 171 "Ctrlknr.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 171 "Ctrlknr.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 171 "Ctrlknr.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 171 "Ctrlknr.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 171 "Ctrlknr.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 171 "Ctrlknr.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 171 "Ctrlknr.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 7;
#line 171 "Ctrlknr.sqc"
      sql_setdlist[2].sqldata = (void*)bskgok;
#line 171 "Ctrlknr.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 171 "Ctrlknr.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 171 "Ctrlknr.sqc"
      sql_setdlist[3].sqldata = (void*)&ctrlno;
#line 171 "Ctrlknr.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 171 "Ctrlknr.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 171 "Ctrlknr.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 171 "Ctrlknr.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 171 "Ctrlknr.sqc"
  sqlastop(0L);
}

#line 171 "Ctrlknr.sqc"


    while( 1 ) {
        Ctrlknr* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knskisymd,
			:bskkbn,
			:bsklne,
			:bskgok,
			:ctrlno,
			:ctrlhdflg,
			:ctrlktflg,
			:ksndh;
*/

{
#line 184 "Ctrlknr.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 184 "Ctrlknr.sqc"
  sqlaaloc(3,8,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 184 "Ctrlknr.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 184 "Ctrlknr.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 184 "Ctrlknr.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 184 "Ctrlknr.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 184 "Ctrlknr.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 184 "Ctrlknr.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 184 "Ctrlknr.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 184 "Ctrlknr.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 184 "Ctrlknr.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 184 "Ctrlknr.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 7;
#line 184 "Ctrlknr.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 184 "Ctrlknr.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 184 "Ctrlknr.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 184 "Ctrlknr.sqc"
      sql_setdlist[4].sqldata = (void*)&ctrlno;
#line 184 "Ctrlknr.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 184 "Ctrlknr.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 184 "Ctrlknr.sqc"
      sql_setdlist[5].sqldata = (void*)&ctrlhdflg;
#line 184 "Ctrlknr.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 184 "Ctrlknr.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 184 "Ctrlknr.sqc"
      sql_setdlist[6].sqldata = (void*)&ctrlktflg;
#line 184 "Ctrlknr.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 184 "Ctrlknr.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 184 "Ctrlknr.sqc"
      sql_setdlist[7].sqldata = (void*)ksndh;
#line 184 "Ctrlknr.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 184 "Ctrlknr.sqc"
      sqlasetdata(3,0,8,sql_setdlist,0L,0L);
    }
#line 184 "Ctrlknr.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 184 "Ctrlknr.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 184 "Ctrlknr.sqc"
  sqlastop(0L);
}

#line 184 "Ctrlknr.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Ctrlknr*)ZbmlRealloc( array,
                                    sizeof( Ctrlknr ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Ctrlknr ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, CtrlknrArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 199 "Ctrlknr.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 199 "Ctrlknr.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 199 "Ctrlknr.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 199 "Ctrlknr.sqc"
  sqlastop(0L);
}

#line 199 "Ctrlknr.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 207 "Ctrlknr.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbCtrlknrInsert()
 *    CTRLKNR レコードを挿入する
 * ■引数
 *    [I]  Ctrlknr* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCtrlknrInsert( Ctrlknr* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, CtrlknrArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 230 "Ctrlknr.sqc"


    
/*
EXEC SQL INSERT INTO CTRLKNR
    (
		KNSKISYMD,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		CTRLNO,
		CTRLHDFLG,
		CTRLKTFLG,
		KSNDH
    ) VALUES (
		:knskisymd,
		:bskkbn,
		:bsklne,
		:bskgok,
		:ctrlno,
		:ctrlhdflg,
		:ctrlktflg,
		:ksndh
    );
*/

{
#line 251 "Ctrlknr.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 251 "Ctrlknr.sqc"
  sqlaaloc(2,8,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 251 "Ctrlknr.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 251 "Ctrlknr.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 251 "Ctrlknr.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 251 "Ctrlknr.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 251 "Ctrlknr.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 251 "Ctrlknr.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 251 "Ctrlknr.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 251 "Ctrlknr.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 251 "Ctrlknr.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 251 "Ctrlknr.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 7;
#line 251 "Ctrlknr.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 251 "Ctrlknr.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 251 "Ctrlknr.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 251 "Ctrlknr.sqc"
      sql_setdlist[4].sqldata = (void*)&ctrlno;
#line 251 "Ctrlknr.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 251 "Ctrlknr.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 251 "Ctrlknr.sqc"
      sql_setdlist[5].sqldata = (void*)&ctrlhdflg;
#line 251 "Ctrlknr.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 251 "Ctrlknr.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 251 "Ctrlknr.sqc"
      sql_setdlist[6].sqldata = (void*)&ctrlktflg;
#line 251 "Ctrlknr.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 251 "Ctrlknr.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 251 "Ctrlknr.sqc"
      sql_setdlist[7].sqldata = (void*)ksndh;
#line 251 "Ctrlknr.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 251 "Ctrlknr.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 251 "Ctrlknr.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 251 "Ctrlknr.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 251 "Ctrlknr.sqc"
  sqlastop(0L);
}

#line 251 "Ctrlknr.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 256 "Ctrlknr.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbCtrlknrUpdate()
 *    CTRLKNR レコードを更新する
 * ■引数
 *    [I]  Ctrlknr* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCtrlknrUpdate( Ctrlknr* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, CtrlknrArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 280 "Ctrlknr.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 281 "Ctrlknr.sqc"


    
/*
EXEC SQL UPDATE CTRLKNR
    SET (
		BSKLNE,
		CTRLHDFLG,
		CTRLKTFLG,
		KSNDH
    ) = (
		:bsklne,
		:ctrlhdflg,
		:ctrlktflg,
		:ksndh
    ) WHERE
		KNSKISYMD = :knskisymd AND
		BSKKBN = :bskkbn AND
		BSKGOK = :bskgok AND
		CTRLNO = :ctrlno;
*/

{
#line 298 "Ctrlknr.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 298 "Ctrlknr.sqc"
  sqlaaloc(2,8,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 298 "Ctrlknr.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 298 "Ctrlknr.sqc"
      sql_setdlist[0].sqldata = (void*)bsklne;
#line 298 "Ctrlknr.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 298 "Ctrlknr.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 298 "Ctrlknr.sqc"
      sql_setdlist[1].sqldata = (void*)&ctrlhdflg;
#line 298 "Ctrlknr.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 298 "Ctrlknr.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 298 "Ctrlknr.sqc"
      sql_setdlist[2].sqldata = (void*)&ctrlktflg;
#line 298 "Ctrlknr.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 298 "Ctrlknr.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 27;
#line 298 "Ctrlknr.sqc"
      sql_setdlist[3].sqldata = (void*)ksndh;
#line 298 "Ctrlknr.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 298 "Ctrlknr.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 298 "Ctrlknr.sqc"
      sql_setdlist[4].sqldata = (void*)knskisymd;
#line 298 "Ctrlknr.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 298 "Ctrlknr.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 5;
#line 298 "Ctrlknr.sqc"
      sql_setdlist[5].sqldata = (void*)bskkbn;
#line 298 "Ctrlknr.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 298 "Ctrlknr.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 7;
#line 298 "Ctrlknr.sqc"
      sql_setdlist[6].sqldata = (void*)bskgok;
#line 298 "Ctrlknr.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 298 "Ctrlknr.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 298 "Ctrlknr.sqc"
      sql_setdlist[7].sqldata = (void*)&ctrlno;
#line 298 "Ctrlknr.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 298 "Ctrlknr.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 298 "Ctrlknr.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 298 "Ctrlknr.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 298 "Ctrlknr.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 298 "Ctrlknr.sqc"
  sqlastop(0L);
}

#line 298 "Ctrlknr.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 303 "Ctrlknr.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 307 "Ctrlknr.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbCtrlknrDelete()
 *    CTRLKNR レコードを削除する
 * ■引数
 *    [I]  Ctrlknr* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCtrlknrDelete( Ctrlknr* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, CtrlknrArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 331 "Ctrlknr.sqc"


    
/*
EXEC SQL DELETE FROM CTRLKNR
    WHERE
		KNSKISYMD = :knskisymd AND
		BSKKBN = :bskkbn AND
		BSKGOK = :bskgok AND
		CTRLNO = :ctrlno;
*/

{
#line 338 "Ctrlknr.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 338 "Ctrlknr.sqc"
  sqlaaloc(2,4,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 338 "Ctrlknr.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 338 "Ctrlknr.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 338 "Ctrlknr.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 338 "Ctrlknr.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 338 "Ctrlknr.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 338 "Ctrlknr.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 338 "Ctrlknr.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 7;
#line 338 "Ctrlknr.sqc"
      sql_setdlist[2].sqldata = (void*)bskgok;
#line 338 "Ctrlknr.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 338 "Ctrlknr.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 338 "Ctrlknr.sqc"
      sql_setdlist[3].sqldata = (void*)&ctrlno;
#line 338 "Ctrlknr.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 338 "Ctrlknr.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 338 "Ctrlknr.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 338 "Ctrlknr.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 338 "Ctrlknr.sqc"
  sqlastop(0L);
}

#line 338 "Ctrlknr.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 343 "Ctrlknr.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
