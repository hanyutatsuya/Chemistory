static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,89,66,82,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,50,48,90,69,73,71,77,32,0,0,0,0,0,0,0,0,
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


#line 1 "Eigmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Eigmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Eigmst.h"
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


#line 24 "Eigmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Eigmst.sqc"

	char    ecd[4];
	char    shcdfr[3];
	char    shcdto[3];
	char    skecd[4];
	char    skshcd[3];
	char    skcsnm[21];
	char    eigkn[21];
	char    eigkj[21];
	char    eitelno[13];
	char    eifaxno[13];
	char    yjhkkbn;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 45 "Eigmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Eigmst

BmlDMMInfo	EigmstArray[] = {
	DMM_SSTRING( ecd ),
	DMM_SSTRING( shcdfr ),
	DMM_SSTRING( shcdto ),
	DMM_SSTRING( skecd ),
	DMM_SSTRING( skshcd ),
	DMM_SSTRING( skcsnm ),
	DMM_SSTRING( eigkn ),
	DMM_SSTRING( eigkj ),
	DMM_SSTRING( eitelno ),
	DMM_SSTRING( eifaxno ),
	DMM_SCHAR( yjhkkbn ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbEigmstSelectAll()
 *    EIGMST レコード全件取得
 * ■引数
 *    [O]  Eigmst** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbEigmstSelectAll( Eigmst** arrayOut, int* numOut )
{
    Eigmst*     array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 88 "Eigmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		ECD,
		SHCDFR,
		SHCDTO,
		SKECD,
		SKSHCD,
		SKCSNM,
		EIGKN,
		EIGKJ,
		EITELNO,
		EIFAXNO,
		YJHKKBN,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        EIGMST FOR READ ONLY;
*/

#line 108 "Eigmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 110 "Eigmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 110 "Eigmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 110 "Eigmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 110 "Eigmst.sqc"
  sqlastop(0L);
}

#line 110 "Eigmst.sqc"


    while( 1 ) {
        Eigmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:ecd,
			:shcdfr,
			:shcdto,
			:skecd,
			:skshcd,
			:skcsnm,
			:eigkn,
			:eigkj,
			:eitelno,
			:eifaxno,
			:yjhkkbn,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 130 "Eigmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 130 "Eigmst.sqc"
  sqlaaloc(3,15,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[15];
#line 130 "Eigmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 4;
#line 130 "Eigmst.sqc"
      sql_setdlist[0].sqldata = (void*)ecd;
#line 130 "Eigmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 130 "Eigmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 130 "Eigmst.sqc"
      sql_setdlist[1].sqldata = (void*)shcdfr;
#line 130 "Eigmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 130 "Eigmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 130 "Eigmst.sqc"
      sql_setdlist[2].sqldata = (void*)shcdto;
#line 130 "Eigmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 130 "Eigmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 4;
#line 130 "Eigmst.sqc"
      sql_setdlist[3].sqldata = (void*)skecd;
#line 130 "Eigmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 130 "Eigmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 3;
#line 130 "Eigmst.sqc"
      sql_setdlist[4].sqldata = (void*)skshcd;
#line 130 "Eigmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 130 "Eigmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 130 "Eigmst.sqc"
      sql_setdlist[5].sqldata = (void*)skcsnm;
#line 130 "Eigmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 130 "Eigmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 21;
#line 130 "Eigmst.sqc"
      sql_setdlist[6].sqldata = (void*)eigkn;
#line 130 "Eigmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 130 "Eigmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 21;
#line 130 "Eigmst.sqc"
      sql_setdlist[7].sqldata = (void*)eigkj;
#line 130 "Eigmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 130 "Eigmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 13;
#line 130 "Eigmst.sqc"
      sql_setdlist[8].sqldata = (void*)eitelno;
#line 130 "Eigmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 130 "Eigmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 13;
#line 130 "Eigmst.sqc"
      sql_setdlist[9].sqldata = (void*)eifaxno;
#line 130 "Eigmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 130 "Eigmst.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 130 "Eigmst.sqc"
      sql_setdlist[10].sqldata = (void*)&yjhkkbn;
#line 130 "Eigmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 130 "Eigmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 130 "Eigmst.sqc"
      sql_setdlist[11].sqldata = (void*)kaiymd;
#line 130 "Eigmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 130 "Eigmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 130 "Eigmst.sqc"
      sql_setdlist[12].sqldata = (void*)haiymd;
#line 130 "Eigmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 130 "Eigmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 130 "Eigmst.sqc"
      sql_setdlist[13].sqldata = (void*)hnktntid;
#line 130 "Eigmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 130 "Eigmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 27;
#line 130 "Eigmst.sqc"
      sql_setdlist[14].sqldata = (void*)ksndh;
#line 130 "Eigmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 130 "Eigmst.sqc"
      sqlasetdata(3,0,15,sql_setdlist,0L,0L);
    }
#line 130 "Eigmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 130 "Eigmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 130 "Eigmst.sqc"
  sqlastop(0L);
}

#line 130 "Eigmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Eigmst*)ZbmlRealloc( array,
                                    sizeof( Eigmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Eigmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, EigmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 145 "Eigmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 145 "Eigmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 145 "Eigmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 145 "Eigmst.sqc"
  sqlastop(0L);
}

#line 145 "Eigmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 153 "Eigmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbEigmstSelectKey()
 *    EIGMST レコードKey条件取得
 * ■引数
 *    [I]  Eigmst* pKey       取得するレコードのキー
 *    [O]  Eigmst** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbEigmstSelectKey( Eigmst* pKey, Eigmst** arrayOut, int* numOut )
{
    Eigmst*     array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, EigmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 179 "Eigmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		ECD,
		SHCDFR,
		SHCDTO,
		SKECD,
		SKSHCD,
		SKCSNM,
		EIGKN,
		EIGKJ,
		EITELNO,
		EIFAXNO,
		YJHKKBN,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        EIGMST
    WHERE
		ECD = :ecd AND
		SHCDFR = :shcdfr AND
		SHCDTO = :shcdto AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 204 "Eigmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 206 "Eigmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 206 "Eigmst.sqc"
  sqlaaloc(2,4,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 206 "Eigmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 4;
#line 206 "Eigmst.sqc"
      sql_setdlist[0].sqldata = (void*)ecd;
#line 206 "Eigmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 206 "Eigmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 206 "Eigmst.sqc"
      sql_setdlist[1].sqldata = (void*)shcdfr;
#line 206 "Eigmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 206 "Eigmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 206 "Eigmst.sqc"
      sql_setdlist[2].sqldata = (void*)shcdto;
#line 206 "Eigmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 206 "Eigmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 206 "Eigmst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 206 "Eigmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 206 "Eigmst.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 206 "Eigmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 206 "Eigmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 206 "Eigmst.sqc"
  sqlastop(0L);
}

#line 206 "Eigmst.sqc"


    while( 1 ) {
        Eigmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:ecd,
			:shcdfr,
			:shcdto,
			:skecd,
			:skshcd,
			:skcsnm,
			:eigkn,
			:eigkj,
			:eitelno,
			:eifaxno,
			:yjhkkbn,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 226 "Eigmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 226 "Eigmst.sqc"
  sqlaaloc(3,15,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[15];
#line 226 "Eigmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 4;
#line 226 "Eigmst.sqc"
      sql_setdlist[0].sqldata = (void*)ecd;
#line 226 "Eigmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 226 "Eigmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 226 "Eigmst.sqc"
      sql_setdlist[1].sqldata = (void*)shcdfr;
#line 226 "Eigmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 226 "Eigmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 226 "Eigmst.sqc"
      sql_setdlist[2].sqldata = (void*)shcdto;
#line 226 "Eigmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 226 "Eigmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 4;
#line 226 "Eigmst.sqc"
      sql_setdlist[3].sqldata = (void*)skecd;
#line 226 "Eigmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 226 "Eigmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 3;
#line 226 "Eigmst.sqc"
      sql_setdlist[4].sqldata = (void*)skshcd;
#line 226 "Eigmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 226 "Eigmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 226 "Eigmst.sqc"
      sql_setdlist[5].sqldata = (void*)skcsnm;
#line 226 "Eigmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 226 "Eigmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 21;
#line 226 "Eigmst.sqc"
      sql_setdlist[6].sqldata = (void*)eigkn;
#line 226 "Eigmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 226 "Eigmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 21;
#line 226 "Eigmst.sqc"
      sql_setdlist[7].sqldata = (void*)eigkj;
#line 226 "Eigmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 226 "Eigmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 13;
#line 226 "Eigmst.sqc"
      sql_setdlist[8].sqldata = (void*)eitelno;
#line 226 "Eigmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 226 "Eigmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 13;
#line 226 "Eigmst.sqc"
      sql_setdlist[9].sqldata = (void*)eifaxno;
#line 226 "Eigmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 226 "Eigmst.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 226 "Eigmst.sqc"
      sql_setdlist[10].sqldata = (void*)&yjhkkbn;
#line 226 "Eigmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 226 "Eigmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 226 "Eigmst.sqc"
      sql_setdlist[11].sqldata = (void*)kaiymd;
#line 226 "Eigmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 226 "Eigmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 226 "Eigmst.sqc"
      sql_setdlist[12].sqldata = (void*)haiymd;
#line 226 "Eigmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 226 "Eigmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 226 "Eigmst.sqc"
      sql_setdlist[13].sqldata = (void*)hnktntid;
#line 226 "Eigmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 226 "Eigmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 27;
#line 226 "Eigmst.sqc"
      sql_setdlist[14].sqldata = (void*)ksndh;
#line 226 "Eigmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 226 "Eigmst.sqc"
      sqlasetdata(3,0,15,sql_setdlist,0L,0L);
    }
#line 226 "Eigmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 226 "Eigmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 226 "Eigmst.sqc"
  sqlastop(0L);
}

#line 226 "Eigmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Eigmst*)ZbmlRealloc( array,
                                    sizeof( Eigmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Eigmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, EigmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 241 "Eigmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 241 "Eigmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 241 "Eigmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 241 "Eigmst.sqc"
  sqlastop(0L);
}

#line 241 "Eigmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 249 "Eigmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbEigmstInsert()
 *    EIGMST レコードを挿入する
 * ■引数
 *    [I]  Eigmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbEigmstInsert( Eigmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, EigmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 272 "Eigmst.sqc"


    
/*
EXEC SQL INSERT INTO EIGMST
    (
		ECD,
		SHCDFR,
		SHCDTO,
		SKECD,
		SKSHCD,
		SKCSNM,
		EIGKN,
		EIGKJ,
		EITELNO,
		EIFAXNO,
		YJHKKBN,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:ecd,
		:shcdfr,
		:shcdto,
		:skecd,
		:skshcd,
		:skcsnm,
		:eigkn,
		:eigkj,
		:eitelno,
		:eifaxno,
		:yjhkkbn,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 307 "Eigmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 307 "Eigmst.sqc"
  sqlaaloc(2,15,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[15];
#line 307 "Eigmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 4;
#line 307 "Eigmst.sqc"
      sql_setdlist[0].sqldata = (void*)ecd;
#line 307 "Eigmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 307 "Eigmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 307 "Eigmst.sqc"
      sql_setdlist[1].sqldata = (void*)shcdfr;
#line 307 "Eigmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 307 "Eigmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 307 "Eigmst.sqc"
      sql_setdlist[2].sqldata = (void*)shcdto;
#line 307 "Eigmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 307 "Eigmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 4;
#line 307 "Eigmst.sqc"
      sql_setdlist[3].sqldata = (void*)skecd;
#line 307 "Eigmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 307 "Eigmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 3;
#line 307 "Eigmst.sqc"
      sql_setdlist[4].sqldata = (void*)skshcd;
#line 307 "Eigmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 307 "Eigmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 307 "Eigmst.sqc"
      sql_setdlist[5].sqldata = (void*)skcsnm;
#line 307 "Eigmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 307 "Eigmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 21;
#line 307 "Eigmst.sqc"
      sql_setdlist[6].sqldata = (void*)eigkn;
#line 307 "Eigmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 307 "Eigmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 21;
#line 307 "Eigmst.sqc"
      sql_setdlist[7].sqldata = (void*)eigkj;
#line 307 "Eigmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 307 "Eigmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 13;
#line 307 "Eigmst.sqc"
      sql_setdlist[8].sqldata = (void*)eitelno;
#line 307 "Eigmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 307 "Eigmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 13;
#line 307 "Eigmst.sqc"
      sql_setdlist[9].sqldata = (void*)eifaxno;
#line 307 "Eigmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 307 "Eigmst.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 307 "Eigmst.sqc"
      sql_setdlist[10].sqldata = (void*)&yjhkkbn;
#line 307 "Eigmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 307 "Eigmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 307 "Eigmst.sqc"
      sql_setdlist[11].sqldata = (void*)kaiymd;
#line 307 "Eigmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 307 "Eigmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 307 "Eigmst.sqc"
      sql_setdlist[12].sqldata = (void*)haiymd;
#line 307 "Eigmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 307 "Eigmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 307 "Eigmst.sqc"
      sql_setdlist[13].sqldata = (void*)hnktntid;
#line 307 "Eigmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 307 "Eigmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 27;
#line 307 "Eigmst.sqc"
      sql_setdlist[14].sqldata = (void*)ksndh;
#line 307 "Eigmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 307 "Eigmst.sqc"
      sqlasetdata(2,0,15,sql_setdlist,0L,0L);
    }
#line 307 "Eigmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 307 "Eigmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 307 "Eigmst.sqc"
  sqlastop(0L);
}

#line 307 "Eigmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 312 "Eigmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbEigmstUpdate()
 *    EIGMST レコードを更新する
 * ■引数
 *    [I]  Eigmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbEigmstUpdate( Eigmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, EigmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 336 "Eigmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 337 "Eigmst.sqc"


    
/*
EXEC SQL UPDATE EIGMST
    SET (
		SKECD,
		SKSHCD,
		SKCSNM,
		EIGKN,
		EIGKJ,
		EITELNO,
		EIFAXNO,
		YJHKKBN,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:skecd,
		:skshcd,
		:skcsnm,
		:eigkn,
		:eigkj,
		:eitelno,
		:eifaxno,
		:yjhkkbn,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		ECD = :ecd AND
		SHCDFR = :shcdfr AND
		SHCDTO = :shcdto AND
		KAIYMD = :kaiymd;
*/

{
#line 368 "Eigmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 368 "Eigmst.sqc"
  sqlaaloc(2,15,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[15];
#line 368 "Eigmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 4;
#line 368 "Eigmst.sqc"
      sql_setdlist[0].sqldata = (void*)skecd;
#line 368 "Eigmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 368 "Eigmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 368 "Eigmst.sqc"
      sql_setdlist[1].sqldata = (void*)skshcd;
#line 368 "Eigmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 368 "Eigmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 368 "Eigmst.sqc"
      sql_setdlist[2].sqldata = (void*)skcsnm;
#line 368 "Eigmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 368 "Eigmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 21;
#line 368 "Eigmst.sqc"
      sql_setdlist[3].sqldata = (void*)eigkn;
#line 368 "Eigmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 368 "Eigmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 21;
#line 368 "Eigmst.sqc"
      sql_setdlist[4].sqldata = (void*)eigkj;
#line 368 "Eigmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 368 "Eigmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 13;
#line 368 "Eigmst.sqc"
      sql_setdlist[5].sqldata = (void*)eitelno;
#line 368 "Eigmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 368 "Eigmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 13;
#line 368 "Eigmst.sqc"
      sql_setdlist[6].sqldata = (void*)eifaxno;
#line 368 "Eigmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 368 "Eigmst.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 368 "Eigmst.sqc"
      sql_setdlist[7].sqldata = (void*)&yjhkkbn;
#line 368 "Eigmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 368 "Eigmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 368 "Eigmst.sqc"
      sql_setdlist[8].sqldata = (void*)haiymd;
#line 368 "Eigmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 368 "Eigmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 9;
#line 368 "Eigmst.sqc"
      sql_setdlist[9].sqldata = (void*)hnktntid;
#line 368 "Eigmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 368 "Eigmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 27;
#line 368 "Eigmst.sqc"
      sql_setdlist[10].sqldata = (void*)ksndh;
#line 368 "Eigmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 368 "Eigmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 4;
#line 368 "Eigmst.sqc"
      sql_setdlist[11].sqldata = (void*)ecd;
#line 368 "Eigmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 368 "Eigmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 3;
#line 368 "Eigmst.sqc"
      sql_setdlist[12].sqldata = (void*)shcdfr;
#line 368 "Eigmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 368 "Eigmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 3;
#line 368 "Eigmst.sqc"
      sql_setdlist[13].sqldata = (void*)shcdto;
#line 368 "Eigmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 368 "Eigmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 11;
#line 368 "Eigmst.sqc"
      sql_setdlist[14].sqldata = (void*)kaiymd;
#line 368 "Eigmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 368 "Eigmst.sqc"
      sqlasetdata(2,0,15,sql_setdlist,0L,0L);
    }
#line 368 "Eigmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 368 "Eigmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 368 "Eigmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 368 "Eigmst.sqc"
  sqlastop(0L);
}

#line 368 "Eigmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 373 "Eigmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 377 "Eigmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbEigmstDelete()
 *    EIGMST レコードを削除する
 * ■引数
 *    [I]  Eigmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbEigmstDelete( Eigmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, EigmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 401 "Eigmst.sqc"


    
/*
EXEC SQL DELETE FROM EIGMST
    WHERE
		ECD = :ecd AND
		SHCDFR = :shcdfr AND
		SHCDTO = :shcdto AND
		KAIYMD = :kaiymd;
*/

{
#line 408 "Eigmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 408 "Eigmst.sqc"
  sqlaaloc(2,4,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 408 "Eigmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 4;
#line 408 "Eigmst.sqc"
      sql_setdlist[0].sqldata = (void*)ecd;
#line 408 "Eigmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 408 "Eigmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 408 "Eigmst.sqc"
      sql_setdlist[1].sqldata = (void*)shcdfr;
#line 408 "Eigmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 408 "Eigmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 408 "Eigmst.sqc"
      sql_setdlist[2].sqldata = (void*)shcdto;
#line 408 "Eigmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 408 "Eigmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 408 "Eigmst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 408 "Eigmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 408 "Eigmst.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 408 "Eigmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 408 "Eigmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 408 "Eigmst.sqc"
  sqlastop(0L);
}

#line 408 "Eigmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 413 "Eigmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
