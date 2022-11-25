static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,85,65,82,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,49,50,90,67,72,75,83,32,0,0,0,0,0,0,0,0,
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


#line 1 "Chksbtmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Chksbtmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Chksbtmst.h"
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


#line 24 "Chksbtmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Chksbtmst.sqc"

	char    chksbt[3];
	char    chkkmmn[21];
	short   chktmg;
	short   chkkbn;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 38 "Chksbtmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Chksbtmst

BmlDMMInfo	ChksbtmstArray[] = {
	DMM_SSTRING( chksbt ),
	DMM_SSTRING( chkkmmn ),
	DMM_SSHORT( chktmg ),
	DMM_SSHORT( chkkbn ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbChksbtmstSelectAll()
 *    CHKSBTMST レコード全件取得
 * ■引数
 *    [O]  Chksbtmst** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbChksbtmstSelectAll( Chksbtmst** arrayOut, int* numOut )
{
    Chksbtmst*  array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 74 "Chksbtmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		CHKSBT,
		CHKKMMN,
		CHKTMG,
		CHKKBN,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        CHKSBTMST FOR READ ONLY;
*/

#line 87 "Chksbtmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 89 "Chksbtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 89 "Chksbtmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 89 "Chksbtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 89 "Chksbtmst.sqc"
  sqlastop(0L);
}

#line 89 "Chksbtmst.sqc"


    while( 1 ) {
        Chksbtmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:chksbt,
			:chkkmmn,
			:chktmg,
			:chkkbn,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 102 "Chksbtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 102 "Chksbtmst.sqc"
  sqlaaloc(3,8,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 102 "Chksbtmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 102 "Chksbtmst.sqc"
      sql_setdlist[0].sqldata = (void*)chksbt;
#line 102 "Chksbtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 102 "Chksbtmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 102 "Chksbtmst.sqc"
      sql_setdlist[1].sqldata = (void*)chkkmmn;
#line 102 "Chksbtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 102 "Chksbtmst.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 102 "Chksbtmst.sqc"
      sql_setdlist[2].sqldata = (void*)&chktmg;
#line 102 "Chksbtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 102 "Chksbtmst.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 102 "Chksbtmst.sqc"
      sql_setdlist[3].sqldata = (void*)&chkkbn;
#line 102 "Chksbtmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 102 "Chksbtmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 102 "Chksbtmst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 102 "Chksbtmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 102 "Chksbtmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 102 "Chksbtmst.sqc"
      sql_setdlist[5].sqldata = (void*)haiymd;
#line 102 "Chksbtmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 102 "Chksbtmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 9;
#line 102 "Chksbtmst.sqc"
      sql_setdlist[6].sqldata = (void*)hnktntid;
#line 102 "Chksbtmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 102 "Chksbtmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 102 "Chksbtmst.sqc"
      sql_setdlist[7].sqldata = (void*)ksndh;
#line 102 "Chksbtmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 102 "Chksbtmst.sqc"
      sqlasetdata(3,0,8,sql_setdlist,0L,0L);
    }
#line 102 "Chksbtmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 102 "Chksbtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 102 "Chksbtmst.sqc"
  sqlastop(0L);
}

#line 102 "Chksbtmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Chksbtmst*)ZbmlRealloc( array,
                                    sizeof( Chksbtmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Chksbtmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, ChksbtmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 117 "Chksbtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 117 "Chksbtmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 117 "Chksbtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 117 "Chksbtmst.sqc"
  sqlastop(0L);
}

#line 117 "Chksbtmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 125 "Chksbtmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbChksbtmstSelectKey()
 *    CHKSBTMST レコードKey条件取得
 * ■引数
 *    [I]  Chksbtmst* pKey      取得するレコードのキー
 *    [O]  Chksbtmst** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbChksbtmstSelectKey( Chksbtmst* pKey, Chksbtmst** arrayOut, int* numOut )
{
    Chksbtmst*  array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, ChksbtmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 151 "Chksbtmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		CHKSBT,
		CHKKMMN,
		CHKTMG,
		CHKKBN,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        CHKSBTMST
    WHERE
		CHKSBT = :chksbt AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 167 "Chksbtmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 169 "Chksbtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 169 "Chksbtmst.sqc"
  sqlaaloc(2,2,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 169 "Chksbtmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 169 "Chksbtmst.sqc"
      sql_setdlist[0].sqldata = (void*)chksbt;
#line 169 "Chksbtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 169 "Chksbtmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 169 "Chksbtmst.sqc"
      sql_setdlist[1].sqldata = (void*)kaiymd;
#line 169 "Chksbtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 169 "Chksbtmst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 169 "Chksbtmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 169 "Chksbtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 169 "Chksbtmst.sqc"
  sqlastop(0L);
}

#line 169 "Chksbtmst.sqc"


    while( 1 ) {
        Chksbtmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:chksbt,
			:chkkmmn,
			:chktmg,
			:chkkbn,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 182 "Chksbtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 182 "Chksbtmst.sqc"
  sqlaaloc(3,8,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 182 "Chksbtmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 182 "Chksbtmst.sqc"
      sql_setdlist[0].sqldata = (void*)chksbt;
#line 182 "Chksbtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 182 "Chksbtmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 182 "Chksbtmst.sqc"
      sql_setdlist[1].sqldata = (void*)chkkmmn;
#line 182 "Chksbtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 182 "Chksbtmst.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 182 "Chksbtmst.sqc"
      sql_setdlist[2].sqldata = (void*)&chktmg;
#line 182 "Chksbtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 182 "Chksbtmst.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 182 "Chksbtmst.sqc"
      sql_setdlist[3].sqldata = (void*)&chkkbn;
#line 182 "Chksbtmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 182 "Chksbtmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 182 "Chksbtmst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 182 "Chksbtmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 182 "Chksbtmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 182 "Chksbtmst.sqc"
      sql_setdlist[5].sqldata = (void*)haiymd;
#line 182 "Chksbtmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 182 "Chksbtmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 9;
#line 182 "Chksbtmst.sqc"
      sql_setdlist[6].sqldata = (void*)hnktntid;
#line 182 "Chksbtmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 182 "Chksbtmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 182 "Chksbtmst.sqc"
      sql_setdlist[7].sqldata = (void*)ksndh;
#line 182 "Chksbtmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 182 "Chksbtmst.sqc"
      sqlasetdata(3,0,8,sql_setdlist,0L,0L);
    }
#line 182 "Chksbtmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 182 "Chksbtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 182 "Chksbtmst.sqc"
  sqlastop(0L);
}

#line 182 "Chksbtmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Chksbtmst*)ZbmlRealloc( array,
                                    sizeof( Chksbtmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Chksbtmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, ChksbtmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 197 "Chksbtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 197 "Chksbtmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 197 "Chksbtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 197 "Chksbtmst.sqc"
  sqlastop(0L);
}

#line 197 "Chksbtmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 205 "Chksbtmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbChksbtmstInsert()
 *    CHKSBTMST レコードを挿入する
 * ■引数
 *    [I]  Chksbtmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbChksbtmstInsert( Chksbtmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, ChksbtmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 228 "Chksbtmst.sqc"


    
/*
EXEC SQL INSERT INTO CHKSBTMST
    (
		CHKSBT,
		CHKKMMN,
		CHKTMG,
		CHKKBN,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:chksbt,
		:chkkmmn,
		:chktmg,
		:chkkbn,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 249 "Chksbtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 249 "Chksbtmst.sqc"
  sqlaaloc(2,8,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 249 "Chksbtmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 249 "Chksbtmst.sqc"
      sql_setdlist[0].sqldata = (void*)chksbt;
#line 249 "Chksbtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 249 "Chksbtmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 249 "Chksbtmst.sqc"
      sql_setdlist[1].sqldata = (void*)chkkmmn;
#line 249 "Chksbtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 249 "Chksbtmst.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 249 "Chksbtmst.sqc"
      sql_setdlist[2].sqldata = (void*)&chktmg;
#line 249 "Chksbtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 249 "Chksbtmst.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 249 "Chksbtmst.sqc"
      sql_setdlist[3].sqldata = (void*)&chkkbn;
#line 249 "Chksbtmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 249 "Chksbtmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 249 "Chksbtmst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 249 "Chksbtmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 249 "Chksbtmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 249 "Chksbtmst.sqc"
      sql_setdlist[5].sqldata = (void*)haiymd;
#line 249 "Chksbtmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 249 "Chksbtmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 9;
#line 249 "Chksbtmst.sqc"
      sql_setdlist[6].sqldata = (void*)hnktntid;
#line 249 "Chksbtmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 249 "Chksbtmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 249 "Chksbtmst.sqc"
      sql_setdlist[7].sqldata = (void*)ksndh;
#line 249 "Chksbtmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 249 "Chksbtmst.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 249 "Chksbtmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 249 "Chksbtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 249 "Chksbtmst.sqc"
  sqlastop(0L);
}

#line 249 "Chksbtmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 254 "Chksbtmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbChksbtmstUpdate()
 *    CHKSBTMST レコードを更新する
 * ■引数
 *    [I]  Chksbtmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbChksbtmstUpdate( Chksbtmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, ChksbtmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 278 "Chksbtmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 279 "Chksbtmst.sqc"


    
/*
EXEC SQL UPDATE CHKSBTMST
    SET (
		CHKKMMN,
		CHKTMG,
		CHKKBN,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:chkkmmn,
		:chktmg,
		:chkkbn,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		CHKSBT = :chksbt AND
		KAIYMD = :kaiymd;
*/

{
#line 298 "Chksbtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 298 "Chksbtmst.sqc"
  sqlaaloc(2,8,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 298 "Chksbtmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 21;
#line 298 "Chksbtmst.sqc"
      sql_setdlist[0].sqldata = (void*)chkkmmn;
#line 298 "Chksbtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 298 "Chksbtmst.sqc"
      sql_setdlist[1].sqltype = 500; sql_setdlist[1].sqllen = 2;
#line 298 "Chksbtmst.sqc"
      sql_setdlist[1].sqldata = (void*)&chktmg;
#line 298 "Chksbtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 298 "Chksbtmst.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 298 "Chksbtmst.sqc"
      sql_setdlist[2].sqldata = (void*)&chkkbn;
#line 298 "Chksbtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 298 "Chksbtmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 298 "Chksbtmst.sqc"
      sql_setdlist[3].sqldata = (void*)haiymd;
#line 298 "Chksbtmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 298 "Chksbtmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 9;
#line 298 "Chksbtmst.sqc"
      sql_setdlist[4].sqldata = (void*)hnktntid;
#line 298 "Chksbtmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 298 "Chksbtmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 27;
#line 298 "Chksbtmst.sqc"
      sql_setdlist[5].sqldata = (void*)ksndh;
#line 298 "Chksbtmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 298 "Chksbtmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 3;
#line 298 "Chksbtmst.sqc"
      sql_setdlist[6].sqldata = (void*)chksbt;
#line 298 "Chksbtmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 298 "Chksbtmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 298 "Chksbtmst.sqc"
      sql_setdlist[7].sqldata = (void*)kaiymd;
#line 298 "Chksbtmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 298 "Chksbtmst.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 298 "Chksbtmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 298 "Chksbtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 298 "Chksbtmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 298 "Chksbtmst.sqc"
  sqlastop(0L);
}

#line 298 "Chksbtmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 303 "Chksbtmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 307 "Chksbtmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbChksbtmstDelete()
 *    CHKSBTMST レコードを削除する
 * ■引数
 *    [I]  Chksbtmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbChksbtmstDelete( Chksbtmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, ChksbtmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 331 "Chksbtmst.sqc"


    
/*
EXEC SQL DELETE FROM CHKSBTMST
    WHERE
		CHKSBT = :chksbt AND
		KAIYMD = :kaiymd;
*/

{
#line 336 "Chksbtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 336 "Chksbtmst.sqc"
  sqlaaloc(2,2,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 336 "Chksbtmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 336 "Chksbtmst.sqc"
      sql_setdlist[0].sqldata = (void*)chksbt;
#line 336 "Chksbtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 336 "Chksbtmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 336 "Chksbtmst.sqc"
      sql_setdlist[1].sqldata = (void*)kaiymd;
#line 336 "Chksbtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 336 "Chksbtmst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 336 "Chksbtmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 336 "Chksbtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 336 "Chksbtmst.sqc"
  sqlastop(0L);
}

#line 336 "Chksbtmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 341 "Chksbtmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
