static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,109,65,82,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,49,52,90,67,84,82,76,32,0,0,0,0,0,0,0,0,
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


#line 1 "Ctrlijhtmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Ctrlijhtmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Ctrlijhtmst.h"
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


#line 24 "Ctrlijhtmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Ctrlijhtmst.sqc"

	char    bskkbn[5];
	char    nbkmkcd[8];
	short   ctrlhnsu;
	char    kyuhniflg;
	short   sjhnsu;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 39 "Ctrlijhtmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Ctrlijhtmst

BmlDMMInfo	CtrlijhtmstArray[] = {
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( nbkmkcd ),
	DMM_SSHORT( ctrlhnsu ),
	DMM_SCHAR( kyuhniflg ),
	DMM_SSHORT( sjhnsu ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbCtrlijhtmstSelectAll()
 *    CTRLIJHTMST レコード全件取得
 * ■引数
 *    [O]  Ctrlijhtmst** arrayO 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCtrlijhtmstSelectAll( Ctrlijhtmst** arrayOut, int* numOut )
{
    Ctrlijhtmst* array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 76 "Ctrlijhtmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		BSKKBN,
		NBKMKCD,
		CTRLHNSU,
		KYUHNIFLG,
		SJHNSU,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        CTRLIJHTMST FOR READ ONLY;
*/

#line 90 "Ctrlijhtmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 92 "Ctrlijhtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 92 "Ctrlijhtmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 92 "Ctrlijhtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 92 "Ctrlijhtmst.sqc"
  sqlastop(0L);
}

#line 92 "Ctrlijhtmst.sqc"


    while( 1 ) {
        Ctrlijhtmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:bskkbn,
			:nbkmkcd,
			:ctrlhnsu,
			:kyuhniflg,
			:sjhnsu,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 106 "Ctrlijhtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 106 "Ctrlijhtmst.sqc"
  sqlaaloc(3,9,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[1].sqldata = (void*)nbkmkcd;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[2].sqldata = (void*)&ctrlhnsu;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[3].sqldata = (void*)&kyuhniflg;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[4].sqldata = (void*)&sjhnsu;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[5].sqldata = (void*)kaiymd;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[6].sqldata = (void*)haiymd;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[7].sqldata = (void*)hnktntid;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 106 "Ctrlijhtmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 106 "Ctrlijhtmst.sqc"
      sqlasetdata(3,0,9,sql_setdlist,0L,0L);
    }
#line 106 "Ctrlijhtmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 106 "Ctrlijhtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 106 "Ctrlijhtmst.sqc"
  sqlastop(0L);
}

#line 106 "Ctrlijhtmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Ctrlijhtmst*)ZbmlRealloc( array,
                                    sizeof( Ctrlijhtmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Ctrlijhtmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, CtrlijhtmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 121 "Ctrlijhtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 121 "Ctrlijhtmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 121 "Ctrlijhtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 121 "Ctrlijhtmst.sqc"
  sqlastop(0L);
}

#line 121 "Ctrlijhtmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 129 "Ctrlijhtmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbCtrlijhtmstSelectKey()
 *    CTRLIJHTMST レコードKey条件取得
 * ■引数
 *    [I]  Ctrlijhtmst* pKey    取得するレコードのキー
 *    [O]  Ctrlijhtmst** arrayO 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCtrlijhtmstSelectKey( Ctrlijhtmst* pKey, Ctrlijhtmst** arrayOut, int* numOut )
{
    Ctrlijhtmst* array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, CtrlijhtmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 155 "Ctrlijhtmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		BSKKBN,
		NBKMKCD,
		CTRLHNSU,
		KYUHNIFLG,
		SJHNSU,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        CTRLIJHTMST
    WHERE
		BSKKBN = :bskkbn AND
		NBKMKCD = :nbkmkcd AND
		CTRLHNSU = :ctrlhnsu AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 174 "Ctrlijhtmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 176 "Ctrlijhtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 176 "Ctrlijhtmst.sqc"
  sqlaaloc(2,4,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 176 "Ctrlijhtmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 176 "Ctrlijhtmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 176 "Ctrlijhtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 176 "Ctrlijhtmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 176 "Ctrlijhtmst.sqc"
      sql_setdlist[1].sqldata = (void*)nbkmkcd;
#line 176 "Ctrlijhtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 176 "Ctrlijhtmst.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 176 "Ctrlijhtmst.sqc"
      sql_setdlist[2].sqldata = (void*)&ctrlhnsu;
#line 176 "Ctrlijhtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 176 "Ctrlijhtmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 176 "Ctrlijhtmst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 176 "Ctrlijhtmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 176 "Ctrlijhtmst.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 176 "Ctrlijhtmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 176 "Ctrlijhtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 176 "Ctrlijhtmst.sqc"
  sqlastop(0L);
}

#line 176 "Ctrlijhtmst.sqc"


    while( 1 ) {
        Ctrlijhtmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:bskkbn,
			:nbkmkcd,
			:ctrlhnsu,
			:kyuhniflg,
			:sjhnsu,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 190 "Ctrlijhtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 190 "Ctrlijhtmst.sqc"
  sqlaaloc(3,9,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[1].sqldata = (void*)nbkmkcd;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[2].sqldata = (void*)&ctrlhnsu;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[3].sqldata = (void*)&kyuhniflg;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[4].sqldata = (void*)&sjhnsu;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[5].sqldata = (void*)kaiymd;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[6].sqldata = (void*)haiymd;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[7].sqldata = (void*)hnktntid;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 190 "Ctrlijhtmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 190 "Ctrlijhtmst.sqc"
      sqlasetdata(3,0,9,sql_setdlist,0L,0L);
    }
#line 190 "Ctrlijhtmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 190 "Ctrlijhtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 190 "Ctrlijhtmst.sqc"
  sqlastop(0L);
}

#line 190 "Ctrlijhtmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Ctrlijhtmst*)ZbmlRealloc( array,
                                    sizeof( Ctrlijhtmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Ctrlijhtmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, CtrlijhtmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 205 "Ctrlijhtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 205 "Ctrlijhtmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 205 "Ctrlijhtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 205 "Ctrlijhtmst.sqc"
  sqlastop(0L);
}

#line 205 "Ctrlijhtmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 213 "Ctrlijhtmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbCtrlijhtmstInsert()
 *    CTRLIJHTMST レコードを挿入する
 * ■引数
 *    [I]  Ctrlijhtmst* rec     挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCtrlijhtmstInsert( Ctrlijhtmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, CtrlijhtmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 236 "Ctrlijhtmst.sqc"


    
/*
EXEC SQL INSERT INTO CTRLIJHTMST
    (
		BSKKBN,
		NBKMKCD,
		CTRLHNSU,
		KYUHNIFLG,
		SJHNSU,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:bskkbn,
		:nbkmkcd,
		:ctrlhnsu,
		:kyuhniflg,
		:sjhnsu,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 259 "Ctrlijhtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 259 "Ctrlijhtmst.sqc"
  sqlaaloc(2,9,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[1].sqldata = (void*)nbkmkcd;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[2].sqldata = (void*)&ctrlhnsu;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[3].sqldata = (void*)&kyuhniflg;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[4].sqldata = (void*)&sjhnsu;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[5].sqldata = (void*)kaiymd;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[6].sqldata = (void*)haiymd;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[7].sqldata = (void*)hnktntid;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 259 "Ctrlijhtmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 259 "Ctrlijhtmst.sqc"
      sqlasetdata(2,0,9,sql_setdlist,0L,0L);
    }
#line 259 "Ctrlijhtmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 259 "Ctrlijhtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 259 "Ctrlijhtmst.sqc"
  sqlastop(0L);
}

#line 259 "Ctrlijhtmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 264 "Ctrlijhtmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbCtrlijhtmstUpdate()
 *    CTRLIJHTMST レコードを更新する
 * ■引数
 *    [I]  Ctrlijhtmst* rec     更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCtrlijhtmstUpdate( Ctrlijhtmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, CtrlijhtmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 288 "Ctrlijhtmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 289 "Ctrlijhtmst.sqc"


    
/*
EXEC SQL UPDATE CTRLIJHTMST
    SET (
		KYUHNIFLG,
		SJHNSU,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:kyuhniflg,
		:sjhnsu,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		BSKKBN = :bskkbn AND
		NBKMKCD = :nbkmkcd AND
		CTRLHNSU = :ctrlhnsu AND
		KAIYMD = :kaiymd;
*/

{
#line 308 "Ctrlijhtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 308 "Ctrlijhtmst.sqc"
  sqlaaloc(2,9,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[0].sqldata = (void*)&kyuhniflg;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[1].sqltype = 500; sql_setdlist[1].sqllen = 2;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[1].sqldata = (void*)&sjhnsu;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[2].sqldata = (void*)haiymd;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 9;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[3].sqldata = (void*)hnktntid;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 27;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[4].sqldata = (void*)ksndh;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 5;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[5].sqldata = (void*)bskkbn;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[6].sqldata = (void*)nbkmkcd;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[7].sqldata = (void*)&ctrlhnsu;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[8].sqldata = (void*)kaiymd;
#line 308 "Ctrlijhtmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 308 "Ctrlijhtmst.sqc"
      sqlasetdata(2,0,9,sql_setdlist,0L,0L);
    }
#line 308 "Ctrlijhtmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 308 "Ctrlijhtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 308 "Ctrlijhtmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 308 "Ctrlijhtmst.sqc"
  sqlastop(0L);
}

#line 308 "Ctrlijhtmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 313 "Ctrlijhtmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 317 "Ctrlijhtmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbCtrlijhtmstDelete()
 *    CTRLIJHTMST レコードを削除する
 * ■引数
 *    [I]  Ctrlijhtmst* rec     削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCtrlijhtmstDelete( Ctrlijhtmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, CtrlijhtmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 341 "Ctrlijhtmst.sqc"


    
/*
EXEC SQL DELETE FROM CTRLIJHTMST
    WHERE
		BSKKBN = :bskkbn AND
		NBKMKCD = :nbkmkcd AND
		CTRLHNSU = :ctrlhnsu AND
		KAIYMD = :kaiymd;
*/

{
#line 348 "Ctrlijhtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 348 "Ctrlijhtmst.sqc"
  sqlaaloc(2,4,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 348 "Ctrlijhtmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 348 "Ctrlijhtmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 348 "Ctrlijhtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 348 "Ctrlijhtmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 348 "Ctrlijhtmst.sqc"
      sql_setdlist[1].sqldata = (void*)nbkmkcd;
#line 348 "Ctrlijhtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 348 "Ctrlijhtmst.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 348 "Ctrlijhtmst.sqc"
      sql_setdlist[2].sqldata = (void*)&ctrlhnsu;
#line 348 "Ctrlijhtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 348 "Ctrlijhtmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 348 "Ctrlijhtmst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 348 "Ctrlijhtmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 348 "Ctrlijhtmst.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 348 "Ctrlijhtmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 348 "Ctrlijhtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 348 "Ctrlijhtmst.sqc"
  sqlastop(0L);
}

#line 348 "Ctrlijhtmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 353 "Ctrlijhtmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
