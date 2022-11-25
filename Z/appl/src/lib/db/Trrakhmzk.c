static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,119,65,87,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,55,51,90,84,82,82,65,32,0,0,0,0,0,0,0,0,
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


#line 1 "Trrakhmzk.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Trrakhmzk.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Trrakhmzk.h"
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


#line 24 "Trrakhmzk.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Trrakhmzk.sqc"

	char    knskisymd[11];
	char    bnctrid[11];
	short   bnctrpos;
	char    asyrckid[11];
	short   asyrckpos;
	char    jhstksk;
	char    knsstflg;
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 38 "Trrakhmzk.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Trrakhmzk

BmlDMMInfo	TrrakhmzkArray[] = {
	DMM_SDATE( knskisymd ),
	DMM_SSTRING( bnctrid ),
	DMM_SSHORT( bnctrpos ),
	DMM_SSTRING( asyrckid ),
	DMM_SSHORT( asyrckpos ),
	DMM_SCHAR( jhstksk ),
	DMM_SCHAR( knsstflg ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbTrrakhmzkSelectAll()
 *    TRRAKHMZK レコード全件取得
 * ■引数
 *    [O]  Trrakhmzk** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbTrrakhmzkSelectAll( Trrakhmzk** arrayOut, int* numOut )
{
    Trrakhmzk*  array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 74 "Trrakhmzk.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSKISYMD,
		BNCTRID,
		BNCTRPOS,
		ASYRCKID,
		ASYRCKPOS,
		JHSTKSK,
		KNSSTFLG,
		KSNDH
    FROM
        TRRAKHMZK FOR READ ONLY;
*/

#line 87 "Trrakhmzk.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 89 "Trrakhmzk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 89 "Trrakhmzk.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 89 "Trrakhmzk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 89 "Trrakhmzk.sqc"
  sqlastop(0L);
}

#line 89 "Trrakhmzk.sqc"


    while( 1 ) {
        Trrakhmzk* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knskisymd,
			:bnctrid,
			:bnctrpos,
			:asyrckid,
			:asyrckpos,
			:jhstksk,
			:knsstflg,
			:ksndh;
*/

{
#line 102 "Trrakhmzk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 102 "Trrakhmzk.sqc"
  sqlaaloc(3,8,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 102 "Trrakhmzk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 102 "Trrakhmzk.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 102 "Trrakhmzk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 102 "Trrakhmzk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 102 "Trrakhmzk.sqc"
      sql_setdlist[1].sqldata = (void*)bnctrid;
#line 102 "Trrakhmzk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 102 "Trrakhmzk.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 102 "Trrakhmzk.sqc"
      sql_setdlist[2].sqldata = (void*)&bnctrpos;
#line 102 "Trrakhmzk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 102 "Trrakhmzk.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 102 "Trrakhmzk.sqc"
      sql_setdlist[3].sqldata = (void*)asyrckid;
#line 102 "Trrakhmzk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 102 "Trrakhmzk.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 102 "Trrakhmzk.sqc"
      sql_setdlist[4].sqldata = (void*)&asyrckpos;
#line 102 "Trrakhmzk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 102 "Trrakhmzk.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 102 "Trrakhmzk.sqc"
      sql_setdlist[5].sqldata = (void*)&jhstksk;
#line 102 "Trrakhmzk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 102 "Trrakhmzk.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 102 "Trrakhmzk.sqc"
      sql_setdlist[6].sqldata = (void*)&knsstflg;
#line 102 "Trrakhmzk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 102 "Trrakhmzk.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 102 "Trrakhmzk.sqc"
      sql_setdlist[7].sqldata = (void*)ksndh;
#line 102 "Trrakhmzk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 102 "Trrakhmzk.sqc"
      sqlasetdata(3,0,8,sql_setdlist,0L,0L);
    }
#line 102 "Trrakhmzk.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 102 "Trrakhmzk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 102 "Trrakhmzk.sqc"
  sqlastop(0L);
}

#line 102 "Trrakhmzk.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Trrakhmzk*)ZbmlRealloc( array,
                                    sizeof( Trrakhmzk ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Trrakhmzk ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, TrrakhmzkArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 117 "Trrakhmzk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 117 "Trrakhmzk.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 117 "Trrakhmzk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 117 "Trrakhmzk.sqc"
  sqlastop(0L);
}

#line 117 "Trrakhmzk.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 125 "Trrakhmzk.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbTrrakhmzkSelectKey()
 *    TRRAKHMZK レコードKey条件取得
 * ■引数
 *    [I]  Trrakhmzk* pKey      取得するレコードのキー
 *    [O]  Trrakhmzk** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbTrrakhmzkSelectKey( Trrakhmzk* pKey, Trrakhmzk** arrayOut, int* numOut )
{
    Trrakhmzk*  array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, TrrakhmzkArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 151 "Trrakhmzk.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSKISYMD,
		BNCTRID,
		BNCTRPOS,
		ASYRCKID,
		ASYRCKPOS,
		JHSTKSK,
		KNSSTFLG,
		KSNDH
    FROM
        TRRAKHMZK
    WHERE
		KNSKISYMD = :knskisymd FOR READ ONLY;
*/

#line 166 "Trrakhmzk.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 168 "Trrakhmzk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 168 "Trrakhmzk.sqc"
  sqlaaloc(2,1,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 168 "Trrakhmzk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 168 "Trrakhmzk.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 168 "Trrakhmzk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 168 "Trrakhmzk.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 168 "Trrakhmzk.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 168 "Trrakhmzk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 168 "Trrakhmzk.sqc"
  sqlastop(0L);
}

#line 168 "Trrakhmzk.sqc"


    while( 1 ) {
        Trrakhmzk* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knskisymd,
			:bnctrid,
			:bnctrpos,
			:asyrckid,
			:asyrckpos,
			:jhstksk,
			:knsstflg,
			:ksndh;
*/

{
#line 181 "Trrakhmzk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 181 "Trrakhmzk.sqc"
  sqlaaloc(3,8,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 181 "Trrakhmzk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 181 "Trrakhmzk.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 181 "Trrakhmzk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 181 "Trrakhmzk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 181 "Trrakhmzk.sqc"
      sql_setdlist[1].sqldata = (void*)bnctrid;
#line 181 "Trrakhmzk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 181 "Trrakhmzk.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 181 "Trrakhmzk.sqc"
      sql_setdlist[2].sqldata = (void*)&bnctrpos;
#line 181 "Trrakhmzk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 181 "Trrakhmzk.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 181 "Trrakhmzk.sqc"
      sql_setdlist[3].sqldata = (void*)asyrckid;
#line 181 "Trrakhmzk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 181 "Trrakhmzk.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 181 "Trrakhmzk.sqc"
      sql_setdlist[4].sqldata = (void*)&asyrckpos;
#line 181 "Trrakhmzk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 181 "Trrakhmzk.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 181 "Trrakhmzk.sqc"
      sql_setdlist[5].sqldata = (void*)&jhstksk;
#line 181 "Trrakhmzk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 181 "Trrakhmzk.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 181 "Trrakhmzk.sqc"
      sql_setdlist[6].sqldata = (void*)&knsstflg;
#line 181 "Trrakhmzk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 181 "Trrakhmzk.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 181 "Trrakhmzk.sqc"
      sql_setdlist[7].sqldata = (void*)ksndh;
#line 181 "Trrakhmzk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 181 "Trrakhmzk.sqc"
      sqlasetdata(3,0,8,sql_setdlist,0L,0L);
    }
#line 181 "Trrakhmzk.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 181 "Trrakhmzk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 181 "Trrakhmzk.sqc"
  sqlastop(0L);
}

#line 181 "Trrakhmzk.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Trrakhmzk*)ZbmlRealloc( array,
                                    sizeof( Trrakhmzk ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Trrakhmzk ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, TrrakhmzkArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 196 "Trrakhmzk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 196 "Trrakhmzk.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 196 "Trrakhmzk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 196 "Trrakhmzk.sqc"
  sqlastop(0L);
}

#line 196 "Trrakhmzk.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 204 "Trrakhmzk.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbTrrakhmzkInsert()
 *    TRRAKHMZK レコードを挿入する
 * ■引数
 *    [I]  Trrakhmzk* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbTrrakhmzkInsert( Trrakhmzk* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, TrrakhmzkArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 227 "Trrakhmzk.sqc"


    
/*
EXEC SQL INSERT INTO TRRAKHMZK
    (
		KNSKISYMD,
		BNCTRID,
		BNCTRPOS,
		ASYRCKID,
		ASYRCKPOS,
		JHSTKSK,
		KNSSTFLG,
		KSNDH
    ) VALUES (
		:knskisymd,
		:bnctrid,
		:bnctrpos,
		:asyrckid,
		:asyrckpos,
		:jhstksk,
		:knsstflg,
		:ksndh
    );
*/

{
#line 248 "Trrakhmzk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 248 "Trrakhmzk.sqc"
  sqlaaloc(2,8,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 248 "Trrakhmzk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 248 "Trrakhmzk.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 248 "Trrakhmzk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 248 "Trrakhmzk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 248 "Trrakhmzk.sqc"
      sql_setdlist[1].sqldata = (void*)bnctrid;
#line 248 "Trrakhmzk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 248 "Trrakhmzk.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 248 "Trrakhmzk.sqc"
      sql_setdlist[2].sqldata = (void*)&bnctrpos;
#line 248 "Trrakhmzk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 248 "Trrakhmzk.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 248 "Trrakhmzk.sqc"
      sql_setdlist[3].sqldata = (void*)asyrckid;
#line 248 "Trrakhmzk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 248 "Trrakhmzk.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 248 "Trrakhmzk.sqc"
      sql_setdlist[4].sqldata = (void*)&asyrckpos;
#line 248 "Trrakhmzk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 248 "Trrakhmzk.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 248 "Trrakhmzk.sqc"
      sql_setdlist[5].sqldata = (void*)&jhstksk;
#line 248 "Trrakhmzk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 248 "Trrakhmzk.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 248 "Trrakhmzk.sqc"
      sql_setdlist[6].sqldata = (void*)&knsstflg;
#line 248 "Trrakhmzk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 248 "Trrakhmzk.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 248 "Trrakhmzk.sqc"
      sql_setdlist[7].sqldata = (void*)ksndh;
#line 248 "Trrakhmzk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 248 "Trrakhmzk.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 248 "Trrakhmzk.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 248 "Trrakhmzk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 248 "Trrakhmzk.sqc"
  sqlastop(0L);
}

#line 248 "Trrakhmzk.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 253 "Trrakhmzk.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbTrrakhmzkUpdate()
 *    TRRAKHMZK レコードを更新する
 * ■引数
 *    [I]  Trrakhmzk* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbTrrakhmzkUpdate( Trrakhmzk* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, TrrakhmzkArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 277 "Trrakhmzk.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 278 "Trrakhmzk.sqc"


    
/*
EXEC SQL UPDATE TRRAKHMZK
    SET (
		BNCTRID,
		BNCTRPOS,
		ASYRCKID,
		ASYRCKPOS,
		JHSTKSK,
		KNSSTFLG,
		KSNDH
    ) = (
		:bnctrid,
		:bnctrpos,
		:asyrckid,
		:asyrckpos,
		:jhstksk,
		:knsstflg,
		:ksndh
    ) WHERE
		KNSKISYMD = :knskisymd;
*/

{
#line 298 "Trrakhmzk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 298 "Trrakhmzk.sqc"
  sqlaaloc(2,8,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 298 "Trrakhmzk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 298 "Trrakhmzk.sqc"
      sql_setdlist[0].sqldata = (void*)bnctrid;
#line 298 "Trrakhmzk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 298 "Trrakhmzk.sqc"
      sql_setdlist[1].sqltype = 500; sql_setdlist[1].sqllen = 2;
#line 298 "Trrakhmzk.sqc"
      sql_setdlist[1].sqldata = (void*)&bnctrpos;
#line 298 "Trrakhmzk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 298 "Trrakhmzk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 298 "Trrakhmzk.sqc"
      sql_setdlist[2].sqldata = (void*)asyrckid;
#line 298 "Trrakhmzk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 298 "Trrakhmzk.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 298 "Trrakhmzk.sqc"
      sql_setdlist[3].sqldata = (void*)&asyrckpos;
#line 298 "Trrakhmzk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 298 "Trrakhmzk.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 298 "Trrakhmzk.sqc"
      sql_setdlist[4].sqldata = (void*)&jhstksk;
#line 298 "Trrakhmzk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 298 "Trrakhmzk.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 298 "Trrakhmzk.sqc"
      sql_setdlist[5].sqldata = (void*)&knsstflg;
#line 298 "Trrakhmzk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 298 "Trrakhmzk.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 298 "Trrakhmzk.sqc"
      sql_setdlist[6].sqldata = (void*)ksndh;
#line 298 "Trrakhmzk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 298 "Trrakhmzk.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 298 "Trrakhmzk.sqc"
      sql_setdlist[7].sqldata = (void*)knskisymd;
#line 298 "Trrakhmzk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 298 "Trrakhmzk.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 298 "Trrakhmzk.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 298 "Trrakhmzk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 298 "Trrakhmzk.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 298 "Trrakhmzk.sqc"
  sqlastop(0L);
}

#line 298 "Trrakhmzk.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 303 "Trrakhmzk.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 307 "Trrakhmzk.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbTrrakhmzkDelete()
 *    TRRAKHMZK レコードを削除する
 * ■引数
 *    [I]  Trrakhmzk* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbTrrakhmzkDelete( Trrakhmzk* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, TrrakhmzkArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 331 "Trrakhmzk.sqc"


    
/*
EXEC SQL DELETE FROM TRRAKHMZK
    WHERE
		KNSKISYMD = :knskisymd;
*/

{
#line 335 "Trrakhmzk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 335 "Trrakhmzk.sqc"
  sqlaaloc(2,1,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 335 "Trrakhmzk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 335 "Trrakhmzk.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 335 "Trrakhmzk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 335 "Trrakhmzk.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 335 "Trrakhmzk.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 335 "Trrakhmzk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 335 "Trrakhmzk.sqc"
  sqlastop(0L);
}

#line 335 "Trrakhmzk.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 340 "Trrakhmzk.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
