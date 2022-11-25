static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,102,66,84,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,52,51,90,75,78,79,75,32,0,0,0,0,0,0,0,0,
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


#line 1 "Knokgnmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Knokgnmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Knokgnmst.h"
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


#line 24 "Knokgnmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Knokgnmst.sqc"

	char    userid[9];
	char    systemid[11];
	char    sykiokflg;
	char    nrykokflg;
	char    sysiokflg;
	char    sntnokflg;
	char    knjaokflg;
	char    generalflg[101];
	char    staymd[11];
	char    endymd[11];
	char    trkymd[11];
	char    hnkymd[11];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 42 "Knokgnmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Knokgnmst

BmlDMMInfo	KnokgnmstArray[] = {
	DMM_SSTRING( userid ),
	DMM_SSTRING( systemid ),
	DMM_SCHAR( sykiokflg ),
	DMM_SCHAR( nrykokflg ),
	DMM_SCHAR( sysiokflg ),
	DMM_SCHAR( sntnokflg ),
	DMM_SCHAR( knjaokflg ),
	DMM_SSTRING( generalflg ),
	DMM_SDATE( staymd ),
	DMM_SDATE( endymd ),
	DMM_SDATE( trkymd ),
	DMM_SDATE( hnkymd ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKnokgnmstSelectAll()
 *    KNOKGNMST レコード全件取得
 * ■引数
 *    [O]  Knokgnmst** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKnokgnmstSelectAll( Knokgnmst** arrayOut, int* numOut )
{
    Knokgnmst*  array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 82 "Knokgnmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		USERID,
		SYSTEMID,
		SYKIOKFLG,
		NRYKOKFLG,
		SYSIOKFLG,
		SNTNOKFLG,
		KNJAOKFLG,
		GENERALFLG,
		STAYMD,
		ENDYMD,
		TRKYMD,
		HNKYMD
    FROM
        KNOKGNMST FOR READ ONLY;
*/

#line 99 "Knokgnmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 101 "Knokgnmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 101 "Knokgnmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 101 "Knokgnmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 101 "Knokgnmst.sqc"
  sqlastop(0L);
}

#line 101 "Knokgnmst.sqc"


    while( 1 ) {
        Knokgnmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:userid,
			:systemid,
			:sykiokflg,
			:nrykokflg,
			:sysiokflg,
			:sntnokflg,
			:knjaokflg,
			:generalflg,
			:staymd,
			:endymd,
			:trkymd,
			:hnkymd;
*/

{
#line 118 "Knokgnmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 118 "Knokgnmst.sqc"
  sqlaaloc(3,12,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[12];
#line 118 "Knokgnmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 9;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[0].sqldata = (void*)userid;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[1].sqldata = (void*)systemid;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[2].sqldata = (void*)&sykiokflg;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[3].sqldata = (void*)&nrykokflg;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[4].sqldata = (void*)&sysiokflg;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[5].sqldata = (void*)&sntnokflg;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[6].sqldata = (void*)&knjaokflg;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 101;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[7].sqldata = (void*)generalflg;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[8].sqldata = (void*)staymd;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[9].sqldata = (void*)endymd;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[10].sqldata = (void*)trkymd;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[11].sqldata = (void*)hnkymd;
#line 118 "Knokgnmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 118 "Knokgnmst.sqc"
      sqlasetdata(3,0,12,sql_setdlist,0L,0L);
    }
#line 118 "Knokgnmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 118 "Knokgnmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 118 "Knokgnmst.sqc"
  sqlastop(0L);
}

#line 118 "Knokgnmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Knokgnmst*)ZbmlRealloc( array,
                                    sizeof( Knokgnmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Knokgnmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KnokgnmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 133 "Knokgnmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 133 "Knokgnmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 133 "Knokgnmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 133 "Knokgnmst.sqc"
  sqlastop(0L);
}

#line 133 "Knokgnmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 141 "Knokgnmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKnokgnmstSelectKey()
 *    KNOKGNMST レコードKey条件取得
 * ■引数
 *    [I]  Knokgnmst* pKey      取得するレコードのキー
 *    [O]  Knokgnmst** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKnokgnmstSelectKey( Knokgnmst* pKey, Knokgnmst** arrayOut, int* numOut )
{
    Knokgnmst*  array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KnokgnmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 167 "Knokgnmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		USERID,
		SYSTEMID,
		SYKIOKFLG,
		NRYKOKFLG,
		SYSIOKFLG,
		SNTNOKFLG,
		KNJAOKFLG,
		GENERALFLG,
		STAYMD,
		ENDYMD,
		TRKYMD,
		HNKYMD
    FROM
        KNOKGNMST
    WHERE
		USERID = :userid AND
		SYSTEMID = :systemid AND
		STAYMD <= :staymd FOR READ ONLY;
*/

#line 188 "Knokgnmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 190 "Knokgnmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 190 "Knokgnmst.sqc"
  sqlaaloc(2,3,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 190 "Knokgnmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 9;
#line 190 "Knokgnmst.sqc"
      sql_setdlist[0].sqldata = (void*)userid;
#line 190 "Knokgnmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 190 "Knokgnmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 190 "Knokgnmst.sqc"
      sql_setdlist[1].sqldata = (void*)systemid;
#line 190 "Knokgnmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 190 "Knokgnmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 190 "Knokgnmst.sqc"
      sql_setdlist[2].sqldata = (void*)staymd;
#line 190 "Knokgnmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 190 "Knokgnmst.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 190 "Knokgnmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 190 "Knokgnmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 190 "Knokgnmst.sqc"
  sqlastop(0L);
}

#line 190 "Knokgnmst.sqc"


    while( 1 ) {
        Knokgnmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:userid,
			:systemid,
			:sykiokflg,
			:nrykokflg,
			:sysiokflg,
			:sntnokflg,
			:knjaokflg,
			:generalflg,
			:staymd,
			:endymd,
			:trkymd,
			:hnkymd;
*/

{
#line 207 "Knokgnmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 207 "Knokgnmst.sqc"
  sqlaaloc(3,12,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[12];
#line 207 "Knokgnmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 9;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[0].sqldata = (void*)userid;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[1].sqldata = (void*)systemid;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[2].sqldata = (void*)&sykiokflg;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[3].sqldata = (void*)&nrykokflg;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[4].sqldata = (void*)&sysiokflg;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[5].sqldata = (void*)&sntnokflg;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[6].sqldata = (void*)&knjaokflg;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 101;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[7].sqldata = (void*)generalflg;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[8].sqldata = (void*)staymd;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[9].sqldata = (void*)endymd;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[10].sqldata = (void*)trkymd;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[11].sqldata = (void*)hnkymd;
#line 207 "Knokgnmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 207 "Knokgnmst.sqc"
      sqlasetdata(3,0,12,sql_setdlist,0L,0L);
    }
#line 207 "Knokgnmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 207 "Knokgnmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 207 "Knokgnmst.sqc"
  sqlastop(0L);
}

#line 207 "Knokgnmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Knokgnmst*)ZbmlRealloc( array,
                                    sizeof( Knokgnmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Knokgnmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KnokgnmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 222 "Knokgnmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 222 "Knokgnmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 222 "Knokgnmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 222 "Knokgnmst.sqc"
  sqlastop(0L);
}

#line 222 "Knokgnmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 230 "Knokgnmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKnokgnmstInsert()
 *    KNOKGNMST レコードを挿入する
 * ■引数
 *    [I]  Knokgnmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKnokgnmstInsert( Knokgnmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KnokgnmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 253 "Knokgnmst.sqc"


    
/*
EXEC SQL INSERT INTO KNOKGNMST
    (
		USERID,
		SYSTEMID,
		SYKIOKFLG,
		NRYKOKFLG,
		SYSIOKFLG,
		SNTNOKFLG,
		KNJAOKFLG,
		GENERALFLG,
		STAYMD,
		ENDYMD,
		TRKYMD,
		HNKYMD
    ) VALUES (
		:userid,
		:systemid,
		:sykiokflg,
		:nrykokflg,
		:sysiokflg,
		:sntnokflg,
		:knjaokflg,
		:generalflg,
		:staymd,
		:endymd,
		:trkymd,
		:hnkymd
    );
*/

{
#line 282 "Knokgnmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 282 "Knokgnmst.sqc"
  sqlaaloc(2,12,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[12];
#line 282 "Knokgnmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 9;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[0].sqldata = (void*)userid;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[1].sqldata = (void*)systemid;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[2].sqldata = (void*)&sykiokflg;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[3].sqldata = (void*)&nrykokflg;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[4].sqldata = (void*)&sysiokflg;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[5].sqldata = (void*)&sntnokflg;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[6].sqldata = (void*)&knjaokflg;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 101;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[7].sqldata = (void*)generalflg;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[8].sqldata = (void*)staymd;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[9].sqldata = (void*)endymd;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[10].sqldata = (void*)trkymd;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[11].sqldata = (void*)hnkymd;
#line 282 "Knokgnmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 282 "Knokgnmst.sqc"
      sqlasetdata(2,0,12,sql_setdlist,0L,0L);
    }
#line 282 "Knokgnmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 282 "Knokgnmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 282 "Knokgnmst.sqc"
  sqlastop(0L);
}

#line 282 "Knokgnmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 287 "Knokgnmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKnokgnmstUpdate()
 *    KNOKGNMST レコードを更新する
 * ■引数
 *    [I]  Knokgnmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKnokgnmstUpdate( Knokgnmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KnokgnmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 311 "Knokgnmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 312 "Knokgnmst.sqc"


    
/*
EXEC SQL UPDATE KNOKGNMST
    SET (
		SYKIOKFLG,
		NRYKOKFLG,
		SYSIOKFLG,
		SNTNOKFLG,
		KNJAOKFLG,
		GENERALFLG,
		ENDYMD,
		TRKYMD,
		HNKYMD
    ) = (
		:sykiokflg,
		:nrykokflg,
		:sysiokflg,
		:sntnokflg,
		:knjaokflg,
		:generalflg,
		:endymd,
		:trkymd,
		:hnkymd
    ) WHERE
		USERID = :userid AND
		SYSTEMID = :systemid AND
		STAYMD = :staymd;
*/

{
#line 338 "Knokgnmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 338 "Knokgnmst.sqc"
  sqlaaloc(2,12,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[12];
#line 338 "Knokgnmst.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[0].sqldata = (void*)&sykiokflg;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[1].sqldata = (void*)&nrykokflg;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[2].sqldata = (void*)&sysiokflg;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[3].sqldata = (void*)&sntnokflg;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[4].sqldata = (void*)&knjaokflg;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 101;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[5].sqldata = (void*)generalflg;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[6].sqldata = (void*)endymd;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[7].sqldata = (void*)trkymd;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[8].sqldata = (void*)hnkymd;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 9;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[9].sqldata = (void*)userid;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[10].sqldata = (void*)systemid;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[11].sqldata = (void*)staymd;
#line 338 "Knokgnmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 338 "Knokgnmst.sqc"
      sqlasetdata(2,0,12,sql_setdlist,0L,0L);
    }
#line 338 "Knokgnmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 338 "Knokgnmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 338 "Knokgnmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 338 "Knokgnmst.sqc"
  sqlastop(0L);
}

#line 338 "Knokgnmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 343 "Knokgnmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 347 "Knokgnmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKnokgnmstDelete()
 *    KNOKGNMST レコードを削除する
 * ■引数
 *    [I]  Knokgnmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKnokgnmstDelete( Knokgnmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KnokgnmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 371 "Knokgnmst.sqc"


    
/*
EXEC SQL DELETE FROM KNOKGNMST
    WHERE
		USERID = :userid AND
		SYSTEMID = :systemid AND
		STAYMD = :staymd;
*/

{
#line 377 "Knokgnmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 377 "Knokgnmst.sqc"
  sqlaaloc(2,3,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 377 "Knokgnmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 9;
#line 377 "Knokgnmst.sqc"
      sql_setdlist[0].sqldata = (void*)userid;
#line 377 "Knokgnmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 377 "Knokgnmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 377 "Knokgnmst.sqc"
      sql_setdlist[1].sqldata = (void*)systemid;
#line 377 "Knokgnmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 377 "Knokgnmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 377 "Knokgnmst.sqc"
      sql_setdlist[2].sqldata = (void*)staymd;
#line 377 "Knokgnmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 377 "Knokgnmst.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 377 "Knokgnmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 377 "Knokgnmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 377 "Knokgnmst.sqc"
  sqlastop(0L);
}

#line 377 "Knokgnmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 382 "Knokgnmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
