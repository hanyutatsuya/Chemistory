static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,53,65,85,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,53,49,90,77,69,76,73,32,0,0,0,0,0,0,0,0,
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


#line 1 "Melinemst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Melinemst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Melinemst.h"
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


#line 24 "Melinemst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Melinemst.sqc"

	char    bsklne[5];
	char    bskkbn[11];
	short   memax;
	char    linenm[11];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 38 "Melinemst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Melinemst

BmlDMMInfo	MelinemstArray[] = {
	DMM_SSTRING( bsklne ),
	DMM_SSTRING( bskkbn ),
	DMM_SSHORT( memax ),
	DMM_SSTRING( linenm ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbMelinemstSelectAll()
 *    MELINEMST レコード全件取得
 * ■引数
 *    [O]  Melinemst** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbMelinemstSelectAll( Melinemst** arrayOut, int* numOut )
{
    Melinemst*  array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 74 "Melinemst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		BSKLNE,
		BSKKBN,
		MEMAX,
		LINENM,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        MELINEMST FOR READ ONLY;
*/

#line 87 "Melinemst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 89 "Melinemst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 89 "Melinemst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 89 "Melinemst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 89 "Melinemst.sqc"
  sqlastop(0L);
}

#line 89 "Melinemst.sqc"


    while( 1 ) {
        Melinemst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:bsklne,
			:bskkbn,
			:memax,
			:linenm,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 102 "Melinemst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 102 "Melinemst.sqc"
  sqlaaloc(3,8,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 102 "Melinemst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 102 "Melinemst.sqc"
      sql_setdlist[0].sqldata = (void*)bsklne;
#line 102 "Melinemst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 102 "Melinemst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 102 "Melinemst.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 102 "Melinemst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 102 "Melinemst.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 102 "Melinemst.sqc"
      sql_setdlist[2].sqldata = (void*)&memax;
#line 102 "Melinemst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 102 "Melinemst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 102 "Melinemst.sqc"
      sql_setdlist[3].sqldata = (void*)linenm;
#line 102 "Melinemst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 102 "Melinemst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 102 "Melinemst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 102 "Melinemst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 102 "Melinemst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 102 "Melinemst.sqc"
      sql_setdlist[5].sqldata = (void*)haiymd;
#line 102 "Melinemst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 102 "Melinemst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 9;
#line 102 "Melinemst.sqc"
      sql_setdlist[6].sqldata = (void*)hnktntid;
#line 102 "Melinemst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 102 "Melinemst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 102 "Melinemst.sqc"
      sql_setdlist[7].sqldata = (void*)ksndh;
#line 102 "Melinemst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 102 "Melinemst.sqc"
      sqlasetdata(3,0,8,sql_setdlist,0L,0L);
    }
#line 102 "Melinemst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 102 "Melinemst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 102 "Melinemst.sqc"
  sqlastop(0L);
}

#line 102 "Melinemst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Melinemst*)ZbmlRealloc( array,
                                    sizeof( Melinemst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Melinemst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, MelinemstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 117 "Melinemst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 117 "Melinemst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 117 "Melinemst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 117 "Melinemst.sqc"
  sqlastop(0L);
}

#line 117 "Melinemst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 125 "Melinemst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbMelinemstSelectKey()
 *    MELINEMST レコードKey条件取得
 * ■引数
 *    [I]  Melinemst* pKey      取得するレコードのキー
 *    [O]  Melinemst** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbMelinemstSelectKey( Melinemst* pKey, Melinemst** arrayOut, int* numOut )
{
    Melinemst*  array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, MelinemstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 151 "Melinemst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		BSKLNE,
		BSKKBN,
		MEMAX,
		LINENM,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        MELINEMST
    WHERE
		BSKLNE = :bsklne AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 167 "Melinemst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 169 "Melinemst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 169 "Melinemst.sqc"
  sqlaaloc(2,2,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 169 "Melinemst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 169 "Melinemst.sqc"
      sql_setdlist[0].sqldata = (void*)bsklne;
#line 169 "Melinemst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 169 "Melinemst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 169 "Melinemst.sqc"
      sql_setdlist[1].sqldata = (void*)kaiymd;
#line 169 "Melinemst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 169 "Melinemst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 169 "Melinemst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 169 "Melinemst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 169 "Melinemst.sqc"
  sqlastop(0L);
}

#line 169 "Melinemst.sqc"


    while( 1 ) {
        Melinemst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:bsklne,
			:bskkbn,
			:memax,
			:linenm,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 182 "Melinemst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 182 "Melinemst.sqc"
  sqlaaloc(3,8,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 182 "Melinemst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 182 "Melinemst.sqc"
      sql_setdlist[0].sqldata = (void*)bsklne;
#line 182 "Melinemst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 182 "Melinemst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 182 "Melinemst.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 182 "Melinemst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 182 "Melinemst.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 182 "Melinemst.sqc"
      sql_setdlist[2].sqldata = (void*)&memax;
#line 182 "Melinemst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 182 "Melinemst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 182 "Melinemst.sqc"
      sql_setdlist[3].sqldata = (void*)linenm;
#line 182 "Melinemst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 182 "Melinemst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 182 "Melinemst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 182 "Melinemst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 182 "Melinemst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 182 "Melinemst.sqc"
      sql_setdlist[5].sqldata = (void*)haiymd;
#line 182 "Melinemst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 182 "Melinemst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 9;
#line 182 "Melinemst.sqc"
      sql_setdlist[6].sqldata = (void*)hnktntid;
#line 182 "Melinemst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 182 "Melinemst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 182 "Melinemst.sqc"
      sql_setdlist[7].sqldata = (void*)ksndh;
#line 182 "Melinemst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 182 "Melinemst.sqc"
      sqlasetdata(3,0,8,sql_setdlist,0L,0L);
    }
#line 182 "Melinemst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 182 "Melinemst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 182 "Melinemst.sqc"
  sqlastop(0L);
}

#line 182 "Melinemst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Melinemst*)ZbmlRealloc( array,
                                    sizeof( Melinemst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Melinemst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, MelinemstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 197 "Melinemst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 197 "Melinemst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 197 "Melinemst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 197 "Melinemst.sqc"
  sqlastop(0L);
}

#line 197 "Melinemst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 205 "Melinemst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbMelinemstInsert()
 *    MELINEMST レコードを挿入する
 * ■引数
 *    [I]  Melinemst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbMelinemstInsert( Melinemst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, MelinemstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 228 "Melinemst.sqc"


    
/*
EXEC SQL INSERT INTO MELINEMST
    (
		BSKLNE,
		BSKKBN,
		MEMAX,
		LINENM,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:bsklne,
		:bskkbn,
		:memax,
		:linenm,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 249 "Melinemst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 249 "Melinemst.sqc"
  sqlaaloc(2,8,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 249 "Melinemst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 249 "Melinemst.sqc"
      sql_setdlist[0].sqldata = (void*)bsklne;
#line 249 "Melinemst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 249 "Melinemst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 249 "Melinemst.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 249 "Melinemst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 249 "Melinemst.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 249 "Melinemst.sqc"
      sql_setdlist[2].sqldata = (void*)&memax;
#line 249 "Melinemst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 249 "Melinemst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 249 "Melinemst.sqc"
      sql_setdlist[3].sqldata = (void*)linenm;
#line 249 "Melinemst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 249 "Melinemst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 249 "Melinemst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 249 "Melinemst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 249 "Melinemst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 249 "Melinemst.sqc"
      sql_setdlist[5].sqldata = (void*)haiymd;
#line 249 "Melinemst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 249 "Melinemst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 9;
#line 249 "Melinemst.sqc"
      sql_setdlist[6].sqldata = (void*)hnktntid;
#line 249 "Melinemst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 249 "Melinemst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 249 "Melinemst.sqc"
      sql_setdlist[7].sqldata = (void*)ksndh;
#line 249 "Melinemst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 249 "Melinemst.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 249 "Melinemst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 249 "Melinemst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 249 "Melinemst.sqc"
  sqlastop(0L);
}

#line 249 "Melinemst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 254 "Melinemst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbMelinemstUpdate()
 *    MELINEMST レコードを更新する
 * ■引数
 *    [I]  Melinemst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbMelinemstUpdate( Melinemst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, MelinemstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 278 "Melinemst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 279 "Melinemst.sqc"


    
/*
EXEC SQL UPDATE MELINEMST
    SET (
		BSKKBN,
		MEMAX,
		LINENM,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:bskkbn,
		:memax,
		:linenm,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		BSKLNE = :bsklne AND
		KAIYMD = :kaiymd;
*/

{
#line 298 "Melinemst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 298 "Melinemst.sqc"
  sqlaaloc(2,8,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 298 "Melinemst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 298 "Melinemst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 298 "Melinemst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 298 "Melinemst.sqc"
      sql_setdlist[1].sqltype = 500; sql_setdlist[1].sqllen = 2;
#line 298 "Melinemst.sqc"
      sql_setdlist[1].sqldata = (void*)&memax;
#line 298 "Melinemst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 298 "Melinemst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 298 "Melinemst.sqc"
      sql_setdlist[2].sqldata = (void*)linenm;
#line 298 "Melinemst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 298 "Melinemst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 298 "Melinemst.sqc"
      sql_setdlist[3].sqldata = (void*)haiymd;
#line 298 "Melinemst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 298 "Melinemst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 9;
#line 298 "Melinemst.sqc"
      sql_setdlist[4].sqldata = (void*)hnktntid;
#line 298 "Melinemst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 298 "Melinemst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 27;
#line 298 "Melinemst.sqc"
      sql_setdlist[5].sqldata = (void*)ksndh;
#line 298 "Melinemst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 298 "Melinemst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 5;
#line 298 "Melinemst.sqc"
      sql_setdlist[6].sqldata = (void*)bsklne;
#line 298 "Melinemst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 298 "Melinemst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 298 "Melinemst.sqc"
      sql_setdlist[7].sqldata = (void*)kaiymd;
#line 298 "Melinemst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 298 "Melinemst.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 298 "Melinemst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 298 "Melinemst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 298 "Melinemst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 298 "Melinemst.sqc"
  sqlastop(0L);
}

#line 298 "Melinemst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 303 "Melinemst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 307 "Melinemst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbMelinemstDelete()
 *    MELINEMST レコードを削除する
 * ■引数
 *    [I]  Melinemst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbMelinemstDelete( Melinemst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, MelinemstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 331 "Melinemst.sqc"


    
/*
EXEC SQL DELETE FROM MELINEMST
    WHERE
		BSKLNE = :bsklne AND
		KAIYMD = :kaiymd;
*/

{
#line 336 "Melinemst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 336 "Melinemst.sqc"
  sqlaaloc(2,2,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 336 "Melinemst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 336 "Melinemst.sqc"
      sql_setdlist[0].sqldata = (void*)bsklne;
#line 336 "Melinemst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 336 "Melinemst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 336 "Melinemst.sqc"
      sql_setdlist[1].sqldata = (void*)kaiymd;
#line 336 "Melinemst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 336 "Melinemst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 336 "Melinemst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 336 "Melinemst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 336 "Melinemst.sqc"
  sqlastop(0L);
}

#line 336 "Melinemst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 341 "Melinemst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
