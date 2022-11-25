static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,75,66,82,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,49,56,90,67,84,82,76,32,0,0,0,0,0,0,0,0,
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


#line 1 "Ctrlsbtmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Ctrlsbtmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Ctrlsbtmst.h"
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


#line 24 "Ctrlsbtmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Ctrlsbtmst.sqc"

	char    bskkbn[5];
	char    ctrlsbt[21];
	char    stirckid[11];
	short   stirckpos;
	char    ctrliti;
	short   ctrlcnt;
	short   ctrlstart;
	short   ctrlitv;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 42 "Ctrlsbtmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Ctrlsbtmst

BmlDMMInfo	CtrlsbtmstArray[] = {
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( ctrlsbt ),
	DMM_SSTRING( stirckid ),
	DMM_SSHORT( stirckpos ),
	DMM_SCHAR( ctrliti ),
	DMM_SSHORT( ctrlcnt ),
	DMM_SSHORT( ctrlstart ),
	DMM_SSHORT( ctrlitv ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbCtrlsbtmstSelectAll()
 *    CTRLSBTMST レコード全件取得
 * ■引数
 *    [O]  Ctrlsbtmst** arrayOu 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCtrlsbtmstSelectAll( Ctrlsbtmst** arrayOut, int* numOut )
{
    Ctrlsbtmst* array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 82 "Ctrlsbtmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		BSKKBN,
		CTRLSBT,
		STIRCKID,
		STIRCKPOS,
		CTRLITI,
		CTRLCNT,
		CTRLSTART,
		CTRLITV,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        CTRLSBTMST FOR READ ONLY;
*/

#line 99 "Ctrlsbtmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 101 "Ctrlsbtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 101 "Ctrlsbtmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 101 "Ctrlsbtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 101 "Ctrlsbtmst.sqc"
  sqlastop(0L);
}

#line 101 "Ctrlsbtmst.sqc"


    while( 1 ) {
        Ctrlsbtmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:bskkbn,
			:ctrlsbt,
			:stirckid,
			:stirckpos,
			:ctrliti,
			:ctrlcnt,
			:ctrlstart,
			:ctrlitv,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 118 "Ctrlsbtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 118 "Ctrlsbtmst.sqc"
  sqlaaloc(3,12,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[12];
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[1].sqldata = (void*)ctrlsbt;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[2].sqldata = (void*)stirckid;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[3].sqldata = (void*)&stirckpos;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[4].sqldata = (void*)&ctrliti;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[5].sqldata = (void*)&ctrlcnt;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[6].sqldata = (void*)&ctrlstart;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[7].sqldata = (void*)&ctrlitv;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[8].sqldata = (void*)kaiymd;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[9].sqldata = (void*)haiymd;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 9;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[10].sqldata = (void*)hnktntid;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 27;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[11].sqldata = (void*)ksndh;
#line 118 "Ctrlsbtmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 118 "Ctrlsbtmst.sqc"
      sqlasetdata(3,0,12,sql_setdlist,0L,0L);
    }
#line 118 "Ctrlsbtmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 118 "Ctrlsbtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 118 "Ctrlsbtmst.sqc"
  sqlastop(0L);
}

#line 118 "Ctrlsbtmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Ctrlsbtmst*)ZbmlRealloc( array,
                                    sizeof( Ctrlsbtmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Ctrlsbtmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, CtrlsbtmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 133 "Ctrlsbtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 133 "Ctrlsbtmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 133 "Ctrlsbtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 133 "Ctrlsbtmst.sqc"
  sqlastop(0L);
}

#line 133 "Ctrlsbtmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 141 "Ctrlsbtmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbCtrlsbtmstSelectKey()
 *    CTRLSBTMST レコードKey条件取得
 * ■引数
 *    [I]  Ctrlsbtmst* pKey     取得するレコードのキー
 *    [O]  Ctrlsbtmst** arrayOu 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCtrlsbtmstSelectKey( Ctrlsbtmst* pKey, Ctrlsbtmst** arrayOut, int* numOut )
{
    Ctrlsbtmst* array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, CtrlsbtmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 167 "Ctrlsbtmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		BSKKBN,
		CTRLSBT,
		STIRCKID,
		STIRCKPOS,
		CTRLITI,
		CTRLCNT,
		CTRLSTART,
		CTRLITV,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        CTRLSBTMST
    WHERE
		BSKKBN = :bskkbn AND
		CTRLSBT = :ctrlsbt AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 188 "Ctrlsbtmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 190 "Ctrlsbtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 190 "Ctrlsbtmst.sqc"
  sqlaaloc(2,3,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 190 "Ctrlsbtmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 190 "Ctrlsbtmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 190 "Ctrlsbtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 190 "Ctrlsbtmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 190 "Ctrlsbtmst.sqc"
      sql_setdlist[1].sqldata = (void*)ctrlsbt;
#line 190 "Ctrlsbtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 190 "Ctrlsbtmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 190 "Ctrlsbtmst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 190 "Ctrlsbtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 190 "Ctrlsbtmst.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 190 "Ctrlsbtmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 190 "Ctrlsbtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 190 "Ctrlsbtmst.sqc"
  sqlastop(0L);
}

#line 190 "Ctrlsbtmst.sqc"


    while( 1 ) {
        Ctrlsbtmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:bskkbn,
			:ctrlsbt,
			:stirckid,
			:stirckpos,
			:ctrliti,
			:ctrlcnt,
			:ctrlstart,
			:ctrlitv,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 207 "Ctrlsbtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 207 "Ctrlsbtmst.sqc"
  sqlaaloc(3,12,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[12];
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[1].sqldata = (void*)ctrlsbt;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[2].sqldata = (void*)stirckid;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[3].sqldata = (void*)&stirckpos;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[4].sqldata = (void*)&ctrliti;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[5].sqldata = (void*)&ctrlcnt;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[6].sqldata = (void*)&ctrlstart;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[7].sqldata = (void*)&ctrlitv;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[8].sqldata = (void*)kaiymd;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[9].sqldata = (void*)haiymd;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 9;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[10].sqldata = (void*)hnktntid;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 27;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[11].sqldata = (void*)ksndh;
#line 207 "Ctrlsbtmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 207 "Ctrlsbtmst.sqc"
      sqlasetdata(3,0,12,sql_setdlist,0L,0L);
    }
#line 207 "Ctrlsbtmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 207 "Ctrlsbtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 207 "Ctrlsbtmst.sqc"
  sqlastop(0L);
}

#line 207 "Ctrlsbtmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Ctrlsbtmst*)ZbmlRealloc( array,
                                    sizeof( Ctrlsbtmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Ctrlsbtmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, CtrlsbtmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 222 "Ctrlsbtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 222 "Ctrlsbtmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 222 "Ctrlsbtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 222 "Ctrlsbtmst.sqc"
  sqlastop(0L);
}

#line 222 "Ctrlsbtmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 230 "Ctrlsbtmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbCtrlsbtmstInsert()
 *    CTRLSBTMST レコードを挿入する
 * ■引数
 *    [I]  Ctrlsbtmst* rec      挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCtrlsbtmstInsert( Ctrlsbtmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, CtrlsbtmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 253 "Ctrlsbtmst.sqc"


    
/*
EXEC SQL INSERT INTO CTRLSBTMST
    (
		BSKKBN,
		CTRLSBT,
		STIRCKID,
		STIRCKPOS,
		CTRLITI,
		CTRLCNT,
		CTRLSTART,
		CTRLITV,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:bskkbn,
		:ctrlsbt,
		:stirckid,
		:stirckpos,
		:ctrliti,
		:ctrlcnt,
		:ctrlstart,
		:ctrlitv,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 282 "Ctrlsbtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 282 "Ctrlsbtmst.sqc"
  sqlaaloc(2,12,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[12];
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[1].sqldata = (void*)ctrlsbt;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[2].sqldata = (void*)stirckid;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[3].sqldata = (void*)&stirckpos;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[4].sqldata = (void*)&ctrliti;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[5].sqldata = (void*)&ctrlcnt;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[6].sqldata = (void*)&ctrlstart;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[7].sqldata = (void*)&ctrlitv;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[8].sqldata = (void*)kaiymd;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[9].sqldata = (void*)haiymd;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 9;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[10].sqldata = (void*)hnktntid;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 27;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[11].sqldata = (void*)ksndh;
#line 282 "Ctrlsbtmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 282 "Ctrlsbtmst.sqc"
      sqlasetdata(2,0,12,sql_setdlist,0L,0L);
    }
#line 282 "Ctrlsbtmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 282 "Ctrlsbtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 282 "Ctrlsbtmst.sqc"
  sqlastop(0L);
}

#line 282 "Ctrlsbtmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 287 "Ctrlsbtmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbCtrlsbtmstUpdate()
 *    CTRLSBTMST レコードを更新する
 * ■引数
 *    [I]  Ctrlsbtmst* rec      更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCtrlsbtmstUpdate( Ctrlsbtmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, CtrlsbtmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 311 "Ctrlsbtmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 312 "Ctrlsbtmst.sqc"


    
/*
EXEC SQL UPDATE CTRLSBTMST
    SET (
		STIRCKID,
		STIRCKPOS,
		CTRLITI,
		CTRLCNT,
		CTRLSTART,
		CTRLITV,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:stirckid,
		:stirckpos,
		:ctrliti,
		:ctrlcnt,
		:ctrlstart,
		:ctrlitv,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		BSKKBN = :bskkbn AND
		CTRLSBT = :ctrlsbt AND
		KAIYMD = :kaiymd;
*/

{
#line 338 "Ctrlsbtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 338 "Ctrlsbtmst.sqc"
  sqlaaloc(2,12,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[12];
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[0].sqldata = (void*)stirckid;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[1].sqltype = 500; sql_setdlist[1].sqllen = 2;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[1].sqldata = (void*)&stirckpos;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[2].sqldata = (void*)&ctrliti;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[3].sqldata = (void*)&ctrlcnt;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[4].sqldata = (void*)&ctrlstart;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[5].sqldata = (void*)&ctrlitv;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[6].sqldata = (void*)haiymd;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[7].sqldata = (void*)hnktntid;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 5;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[9].sqldata = (void*)bskkbn;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 21;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[10].sqldata = (void*)ctrlsbt;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[11].sqldata = (void*)kaiymd;
#line 338 "Ctrlsbtmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 338 "Ctrlsbtmst.sqc"
      sqlasetdata(2,0,12,sql_setdlist,0L,0L);
    }
#line 338 "Ctrlsbtmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 338 "Ctrlsbtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 338 "Ctrlsbtmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 338 "Ctrlsbtmst.sqc"
  sqlastop(0L);
}

#line 338 "Ctrlsbtmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 343 "Ctrlsbtmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 347 "Ctrlsbtmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbCtrlsbtmstDelete()
 *    CTRLSBTMST レコードを削除する
 * ■引数
 *    [I]  Ctrlsbtmst* rec      削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCtrlsbtmstDelete( Ctrlsbtmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, CtrlsbtmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 371 "Ctrlsbtmst.sqc"


    
/*
EXEC SQL DELETE FROM CTRLSBTMST
    WHERE
		BSKKBN = :bskkbn AND
		CTRLSBT = :ctrlsbt AND
		KAIYMD = :kaiymd;
*/

{
#line 377 "Ctrlsbtmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 377 "Ctrlsbtmst.sqc"
  sqlaaloc(2,3,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 377 "Ctrlsbtmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 377 "Ctrlsbtmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 377 "Ctrlsbtmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 377 "Ctrlsbtmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 377 "Ctrlsbtmst.sqc"
      sql_setdlist[1].sqldata = (void*)ctrlsbt;
#line 377 "Ctrlsbtmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 377 "Ctrlsbtmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 377 "Ctrlsbtmst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 377 "Ctrlsbtmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 377 "Ctrlsbtmst.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 377 "Ctrlsbtmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 377 "Ctrlsbtmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 377 "Ctrlsbtmst.sqc"
  sqlastop(0L);
}

#line 377 "Ctrlsbtmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 382 "Ctrlsbtmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
