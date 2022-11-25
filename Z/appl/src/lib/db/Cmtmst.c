static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,99,65,82,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,49,51,90,67,77,84,77,32,0,0,0,0,0,0,0,0,
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


#line 1 "Cmtmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Cmtmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Cmtmst.h"
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


#line 24 "Cmtmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Cmtmst.sqc"

	char    cmcd[6];
	char    cmtkg[3];
	char    cmtnm[83];
	char    cmtnmj[81];
	char    knskka1[13];
	char    kkahskcd[4];
	char    akaden;
	char    ijouchi;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 42 "Cmtmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Cmtmst

BmlDMMInfo	CmtmstArray[] = {
	DMM_SSTRING( cmcd ),
	DMM_SSTRING( cmtkg ),
	DMM_SSTRING( cmtnm ),
	DMM_SSTRING( cmtnmj ),
	DMM_SSTRING( knskka1 ),
	DMM_SSTRING( kkahskcd ),
	DMM_SCHAR( akaden ),
	DMM_SCHAR( ijouchi ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbCmtmstSelectAll()
 *    CMTMST レコード全件取得
 * ■引数
 *    [O]  Cmtmst** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCmtmstSelectAll( Cmtmst** arrayOut, int* numOut )
{
    Cmtmst*     array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 82 "Cmtmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		CMCD,
		CMTKG,
		CMTNM,
		CMTNMJ,
		KNSKKA1,
		KKAHSKCD,
		AKADEN,
		IJOUCHI,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        CMTMST FOR READ ONLY;
*/

#line 99 "Cmtmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 101 "Cmtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 101 "Cmtmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 101 "Cmtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 101 "Cmtmst.sqc"
  sqlastop(0L);
}

#line 101 "Cmtmst.sqc"


    while( 1 ) {
        Cmtmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:cmcd,
			:cmtkg,
			:cmtnm,
			:cmtnmj,
			:knskka1,
			:kkahskcd,
			:akaden,
			:ijouchi,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 118 "Cmtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 118 "Cmtmst.sqc"
  sqlaaloc(3,12,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[12];
#line 118 "Cmtmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 6;
#line 118 "Cmtmst.sqc"
      sql_setdlist[0].sqldata = (void*)cmcd;
#line 118 "Cmtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 118 "Cmtmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 118 "Cmtmst.sqc"
      sql_setdlist[1].sqldata = (void*)cmtkg;
#line 118 "Cmtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 118 "Cmtmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 83;
#line 118 "Cmtmst.sqc"
      sql_setdlist[2].sqldata = (void*)cmtnm;
#line 118 "Cmtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 118 "Cmtmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 81;
#line 118 "Cmtmst.sqc"
      sql_setdlist[3].sqldata = (void*)cmtnmj;
#line 118 "Cmtmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 118 "Cmtmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 13;
#line 118 "Cmtmst.sqc"
      sql_setdlist[4].sqldata = (void*)knskka1;
#line 118 "Cmtmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 118 "Cmtmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 4;
#line 118 "Cmtmst.sqc"
      sql_setdlist[5].sqldata = (void*)kkahskcd;
#line 118 "Cmtmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 118 "Cmtmst.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 118 "Cmtmst.sqc"
      sql_setdlist[6].sqldata = (void*)&akaden;
#line 118 "Cmtmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 118 "Cmtmst.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 118 "Cmtmst.sqc"
      sql_setdlist[7].sqldata = (void*)&ijouchi;
#line 118 "Cmtmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 118 "Cmtmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 118 "Cmtmst.sqc"
      sql_setdlist[8].sqldata = (void*)kaiymd;
#line 118 "Cmtmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 118 "Cmtmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 118 "Cmtmst.sqc"
      sql_setdlist[9].sqldata = (void*)haiymd;
#line 118 "Cmtmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 118 "Cmtmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 9;
#line 118 "Cmtmst.sqc"
      sql_setdlist[10].sqldata = (void*)hnktntid;
#line 118 "Cmtmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 118 "Cmtmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 27;
#line 118 "Cmtmst.sqc"
      sql_setdlist[11].sqldata = (void*)ksndh;
#line 118 "Cmtmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 118 "Cmtmst.sqc"
      sqlasetdata(3,0,12,sql_setdlist,0L,0L);
    }
#line 118 "Cmtmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 118 "Cmtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 118 "Cmtmst.sqc"
  sqlastop(0L);
}

#line 118 "Cmtmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Cmtmst*)ZbmlRealloc( array,
                                    sizeof( Cmtmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Cmtmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, CmtmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 133 "Cmtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 133 "Cmtmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 133 "Cmtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 133 "Cmtmst.sqc"
  sqlastop(0L);
}

#line 133 "Cmtmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 141 "Cmtmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbCmtmstSelectKey()
 *    CMTMST レコードKey条件取得
 * ■引数
 *    [I]  Cmtmst* pKey       取得するレコードのキー
 *    [O]  Cmtmst** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCmtmstSelectKey( Cmtmst* pKey, Cmtmst** arrayOut, int* numOut )
{
    Cmtmst*     array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, CmtmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 167 "Cmtmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		CMCD,
		CMTKG,
		CMTNM,
		CMTNMJ,
		KNSKKA1,
		KKAHSKCD,
		AKADEN,
		IJOUCHI,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        CMTMST
    WHERE
		CMCD = :cmcd AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 187 "Cmtmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 189 "Cmtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 189 "Cmtmst.sqc"
  sqlaaloc(2,2,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 189 "Cmtmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 6;
#line 189 "Cmtmst.sqc"
      sql_setdlist[0].sqldata = (void*)cmcd;
#line 189 "Cmtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 189 "Cmtmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 189 "Cmtmst.sqc"
      sql_setdlist[1].sqldata = (void*)kaiymd;
#line 189 "Cmtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 189 "Cmtmst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 189 "Cmtmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 189 "Cmtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 189 "Cmtmst.sqc"
  sqlastop(0L);
}

#line 189 "Cmtmst.sqc"


    while( 1 ) {
        Cmtmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:cmcd,
			:cmtkg,
			:cmtnm,
			:cmtnmj,
			:knskka1,
			:kkahskcd,
			:akaden,
			:ijouchi,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 206 "Cmtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 206 "Cmtmst.sqc"
  sqlaaloc(3,12,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[12];
#line 206 "Cmtmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 6;
#line 206 "Cmtmst.sqc"
      sql_setdlist[0].sqldata = (void*)cmcd;
#line 206 "Cmtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 206 "Cmtmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 206 "Cmtmst.sqc"
      sql_setdlist[1].sqldata = (void*)cmtkg;
#line 206 "Cmtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 206 "Cmtmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 83;
#line 206 "Cmtmst.sqc"
      sql_setdlist[2].sqldata = (void*)cmtnm;
#line 206 "Cmtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 206 "Cmtmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 81;
#line 206 "Cmtmst.sqc"
      sql_setdlist[3].sqldata = (void*)cmtnmj;
#line 206 "Cmtmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 206 "Cmtmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 13;
#line 206 "Cmtmst.sqc"
      sql_setdlist[4].sqldata = (void*)knskka1;
#line 206 "Cmtmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 206 "Cmtmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 4;
#line 206 "Cmtmst.sqc"
      sql_setdlist[5].sqldata = (void*)kkahskcd;
#line 206 "Cmtmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 206 "Cmtmst.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 206 "Cmtmst.sqc"
      sql_setdlist[6].sqldata = (void*)&akaden;
#line 206 "Cmtmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 206 "Cmtmst.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 206 "Cmtmst.sqc"
      sql_setdlist[7].sqldata = (void*)&ijouchi;
#line 206 "Cmtmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 206 "Cmtmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 206 "Cmtmst.sqc"
      sql_setdlist[8].sqldata = (void*)kaiymd;
#line 206 "Cmtmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 206 "Cmtmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 206 "Cmtmst.sqc"
      sql_setdlist[9].sqldata = (void*)haiymd;
#line 206 "Cmtmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 206 "Cmtmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 9;
#line 206 "Cmtmst.sqc"
      sql_setdlist[10].sqldata = (void*)hnktntid;
#line 206 "Cmtmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 206 "Cmtmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 27;
#line 206 "Cmtmst.sqc"
      sql_setdlist[11].sqldata = (void*)ksndh;
#line 206 "Cmtmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 206 "Cmtmst.sqc"
      sqlasetdata(3,0,12,sql_setdlist,0L,0L);
    }
#line 206 "Cmtmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 206 "Cmtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 206 "Cmtmst.sqc"
  sqlastop(0L);
}

#line 206 "Cmtmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Cmtmst*)ZbmlRealloc( array,
                                    sizeof( Cmtmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Cmtmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, CmtmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 221 "Cmtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 221 "Cmtmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 221 "Cmtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 221 "Cmtmst.sqc"
  sqlastop(0L);
}

#line 221 "Cmtmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 229 "Cmtmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbCmtmstInsert()
 *    CMTMST レコードを挿入する
 * ■引数
 *    [I]  Cmtmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCmtmstInsert( Cmtmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, CmtmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 252 "Cmtmst.sqc"


    
/*
EXEC SQL INSERT INTO CMTMST
    (
		CMCD,
		CMTKG,
		CMTNM,
		CMTNMJ,
		KNSKKA1,
		KKAHSKCD,
		AKADEN,
		IJOUCHI,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:cmcd,
		:cmtkg,
		:cmtnm,
		:cmtnmj,
		:knskka1,
		:kkahskcd,
		:akaden,
		:ijouchi,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 281 "Cmtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 281 "Cmtmst.sqc"
  sqlaaloc(2,12,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[12];
#line 281 "Cmtmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 6;
#line 281 "Cmtmst.sqc"
      sql_setdlist[0].sqldata = (void*)cmcd;
#line 281 "Cmtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 281 "Cmtmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 281 "Cmtmst.sqc"
      sql_setdlist[1].sqldata = (void*)cmtkg;
#line 281 "Cmtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 281 "Cmtmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 83;
#line 281 "Cmtmst.sqc"
      sql_setdlist[2].sqldata = (void*)cmtnm;
#line 281 "Cmtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 281 "Cmtmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 81;
#line 281 "Cmtmst.sqc"
      sql_setdlist[3].sqldata = (void*)cmtnmj;
#line 281 "Cmtmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 281 "Cmtmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 13;
#line 281 "Cmtmst.sqc"
      sql_setdlist[4].sqldata = (void*)knskka1;
#line 281 "Cmtmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 281 "Cmtmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 4;
#line 281 "Cmtmst.sqc"
      sql_setdlist[5].sqldata = (void*)kkahskcd;
#line 281 "Cmtmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 281 "Cmtmst.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 281 "Cmtmst.sqc"
      sql_setdlist[6].sqldata = (void*)&akaden;
#line 281 "Cmtmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 281 "Cmtmst.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 281 "Cmtmst.sqc"
      sql_setdlist[7].sqldata = (void*)&ijouchi;
#line 281 "Cmtmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 281 "Cmtmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 281 "Cmtmst.sqc"
      sql_setdlist[8].sqldata = (void*)kaiymd;
#line 281 "Cmtmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 281 "Cmtmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 281 "Cmtmst.sqc"
      sql_setdlist[9].sqldata = (void*)haiymd;
#line 281 "Cmtmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 281 "Cmtmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 9;
#line 281 "Cmtmst.sqc"
      sql_setdlist[10].sqldata = (void*)hnktntid;
#line 281 "Cmtmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 281 "Cmtmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 27;
#line 281 "Cmtmst.sqc"
      sql_setdlist[11].sqldata = (void*)ksndh;
#line 281 "Cmtmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 281 "Cmtmst.sqc"
      sqlasetdata(2,0,12,sql_setdlist,0L,0L);
    }
#line 281 "Cmtmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 281 "Cmtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 281 "Cmtmst.sqc"
  sqlastop(0L);
}

#line 281 "Cmtmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 286 "Cmtmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbCmtmstUpdate()
 *    CMTMST レコードを更新する
 * ■引数
 *    [I]  Cmtmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCmtmstUpdate( Cmtmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, CmtmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 310 "Cmtmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 311 "Cmtmst.sqc"


    
/*
EXEC SQL UPDATE CMTMST
    SET (
		CMTKG,
		CMTNM,
		CMTNMJ,
		KNSKKA1,
		KKAHSKCD,
		AKADEN,
		IJOUCHI,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:cmtkg,
		:cmtnm,
		:cmtnmj,
		:knskka1,
		:kkahskcd,
		:akaden,
		:ijouchi,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		CMCD = :cmcd AND
		KAIYMD = :kaiymd;
*/

{
#line 338 "Cmtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 338 "Cmtmst.sqc"
  sqlaaloc(2,12,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[12];
#line 338 "Cmtmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 338 "Cmtmst.sqc"
      sql_setdlist[0].sqldata = (void*)cmtkg;
#line 338 "Cmtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 338 "Cmtmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 83;
#line 338 "Cmtmst.sqc"
      sql_setdlist[1].sqldata = (void*)cmtnm;
#line 338 "Cmtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 338 "Cmtmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 81;
#line 338 "Cmtmst.sqc"
      sql_setdlist[2].sqldata = (void*)cmtnmj;
#line 338 "Cmtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 338 "Cmtmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 13;
#line 338 "Cmtmst.sqc"
      sql_setdlist[3].sqldata = (void*)knskka1;
#line 338 "Cmtmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 338 "Cmtmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 4;
#line 338 "Cmtmst.sqc"
      sql_setdlist[4].sqldata = (void*)kkahskcd;
#line 338 "Cmtmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 338 "Cmtmst.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 338 "Cmtmst.sqc"
      sql_setdlist[5].sqldata = (void*)&akaden;
#line 338 "Cmtmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 338 "Cmtmst.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 338 "Cmtmst.sqc"
      sql_setdlist[6].sqldata = (void*)&ijouchi;
#line 338 "Cmtmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 338 "Cmtmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 338 "Cmtmst.sqc"
      sql_setdlist[7].sqldata = (void*)haiymd;
#line 338 "Cmtmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 338 "Cmtmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 338 "Cmtmst.sqc"
      sql_setdlist[8].sqldata = (void*)hnktntid;
#line 338 "Cmtmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 338 "Cmtmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 338 "Cmtmst.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 338 "Cmtmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 338 "Cmtmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 6;
#line 338 "Cmtmst.sqc"
      sql_setdlist[10].sqldata = (void*)cmcd;
#line 338 "Cmtmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 338 "Cmtmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 338 "Cmtmst.sqc"
      sql_setdlist[11].sqldata = (void*)kaiymd;
#line 338 "Cmtmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 338 "Cmtmst.sqc"
      sqlasetdata(2,0,12,sql_setdlist,0L,0L);
    }
#line 338 "Cmtmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 338 "Cmtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 338 "Cmtmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 338 "Cmtmst.sqc"
  sqlastop(0L);
}

#line 338 "Cmtmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 343 "Cmtmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 347 "Cmtmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbCmtmstDelete()
 *    CMTMST レコードを削除する
 * ■引数
 *    [I]  Cmtmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCmtmstDelete( Cmtmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, CmtmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 371 "Cmtmst.sqc"


    
/*
EXEC SQL DELETE FROM CMTMST
    WHERE
		CMCD = :cmcd AND
		KAIYMD = :kaiymd;
*/

{
#line 376 "Cmtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 376 "Cmtmst.sqc"
  sqlaaloc(2,2,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 376 "Cmtmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 6;
#line 376 "Cmtmst.sqc"
      sql_setdlist[0].sqldata = (void*)cmcd;
#line 376 "Cmtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 376 "Cmtmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 376 "Cmtmst.sqc"
      sql_setdlist[1].sqldata = (void*)kaiymd;
#line 376 "Cmtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 376 "Cmtmst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 376 "Cmtmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 376 "Cmtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 376 "Cmtmst.sqc"
  sqlastop(0L);
}

#line 376 "Cmtmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 381 "Cmtmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
