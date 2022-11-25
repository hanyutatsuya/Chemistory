static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,54,65,84,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,51,57,90,75,77,75,71,32,0,0,0,0,0,0,0,0,
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


#line 1 "Kmkgmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Kmkgmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Kmkgmst.h"
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


#line 24 "Kmkgmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Kmkgmst.sqc"

	char    kmkgrp[17];
	char    kmkgrpnm[41];
	char    kmkgrprs[21];
	char    knsgrp[17];
	char    kmkcd[8];
	short   hyjijn;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 40 "Kmkgmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Kmkgmst

BmlDMMInfo	KmkgmstArray[] = {
	DMM_SSTRING( kmkgrp ),
	DMM_SSTRING( kmkgrpnm ),
	DMM_SSTRING( kmkgrprs ),
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSHORT( hyjijn ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKmkgmstSelectAll()
 *    KMKGMST レコード全件取得
 * ■引数
 *    [O]  Kmkgmst** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKmkgmstSelectAll( Kmkgmst** arrayOut, int* numOut )
{
    Kmkgmst*    array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 78 "Kmkgmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KMKGRP,
		KMKGRPNM,
		KMKGRPRS,
		KNSGRP,
		KMKCD,
		HYJIJN,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        KMKGMST FOR READ ONLY;
*/

#line 93 "Kmkgmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 95 "Kmkgmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 95 "Kmkgmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 95 "Kmkgmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 95 "Kmkgmst.sqc"
  sqlastop(0L);
}

#line 95 "Kmkgmst.sqc"


    while( 1 ) {
        Kmkgmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:kmkgrp,
			:kmkgrpnm,
			:kmkgrprs,
			:knsgrp,
			:kmkcd,
			:hyjijn,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 110 "Kmkgmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 110 "Kmkgmst.sqc"
  sqlaaloc(3,10,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 110 "Kmkgmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkgrp;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 41;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkgrpnm;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmkgrprs;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[5].sqldata = (void*)&hyjijn;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[6].sqldata = (void*)kaiymd;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[7].sqldata = (void*)haiymd;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[8].sqldata = (void*)hnktntid;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 110 "Kmkgmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 110 "Kmkgmst.sqc"
      sqlasetdata(3,0,10,sql_setdlist,0L,0L);
    }
#line 110 "Kmkgmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 110 "Kmkgmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 110 "Kmkgmst.sqc"
  sqlastop(0L);
}

#line 110 "Kmkgmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kmkgmst*)ZbmlRealloc( array,
                                    sizeof( Kmkgmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kmkgmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KmkgmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 125 "Kmkgmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 125 "Kmkgmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 125 "Kmkgmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 125 "Kmkgmst.sqc"
  sqlastop(0L);
}

#line 125 "Kmkgmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 133 "Kmkgmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKmkgmstSelectKey()
 *    KMKGMST レコードKey条件取得
 * ■引数
 *    [I]  Kmkgmst* pKey       取得するレコードのキー
 *    [O]  Kmkgmst** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKmkgmstSelectKey( Kmkgmst* pKey, Kmkgmst** arrayOut, int* numOut )
{
    Kmkgmst*    array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KmkgmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 159 "Kmkgmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KMKGRP,
		KMKGRPNM,
		KMKGRPRS,
		KNSGRP,
		KMKCD,
		HYJIJN,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        KMKGMST
    WHERE
		KMKGRP = :kmkgrp AND
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 179 "Kmkgmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 181 "Kmkgmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 181 "Kmkgmst.sqc"
  sqlaaloc(2,4,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 181 "Kmkgmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 181 "Kmkgmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkgrp;
#line 181 "Kmkgmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 181 "Kmkgmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 181 "Kmkgmst.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 181 "Kmkgmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 181 "Kmkgmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 181 "Kmkgmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 181 "Kmkgmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 181 "Kmkgmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 181 "Kmkgmst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 181 "Kmkgmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 181 "Kmkgmst.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 181 "Kmkgmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 181 "Kmkgmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 181 "Kmkgmst.sqc"
  sqlastop(0L);
}

#line 181 "Kmkgmst.sqc"


    while( 1 ) {
        Kmkgmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:kmkgrp,
			:kmkgrpnm,
			:kmkgrprs,
			:knsgrp,
			:kmkcd,
			:hyjijn,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 196 "Kmkgmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 196 "Kmkgmst.sqc"
  sqlaaloc(3,10,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 196 "Kmkgmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkgrp;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 41;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkgrpnm;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmkgrprs;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[5].sqldata = (void*)&hyjijn;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[6].sqldata = (void*)kaiymd;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[7].sqldata = (void*)haiymd;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[8].sqldata = (void*)hnktntid;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 196 "Kmkgmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 196 "Kmkgmst.sqc"
      sqlasetdata(3,0,10,sql_setdlist,0L,0L);
    }
#line 196 "Kmkgmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 196 "Kmkgmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 196 "Kmkgmst.sqc"
  sqlastop(0L);
}

#line 196 "Kmkgmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kmkgmst*)ZbmlRealloc( array,
                                    sizeof( Kmkgmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kmkgmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KmkgmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 211 "Kmkgmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 211 "Kmkgmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 211 "Kmkgmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 211 "Kmkgmst.sqc"
  sqlastop(0L);
}

#line 211 "Kmkgmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 219 "Kmkgmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKmkgmstInsert()
 *    KMKGMST レコードを挿入する
 * ■引数
 *    [I]  Kmkgmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKmkgmstInsert( Kmkgmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KmkgmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 242 "Kmkgmst.sqc"


    
/*
EXEC SQL INSERT INTO KMKGMST
    (
		KMKGRP,
		KMKGRPNM,
		KMKGRPRS,
		KNSGRP,
		KMKCD,
		HYJIJN,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:kmkgrp,
		:kmkgrpnm,
		:kmkgrprs,
		:knsgrp,
		:kmkcd,
		:hyjijn,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 267 "Kmkgmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 267 "Kmkgmst.sqc"
  sqlaaloc(2,10,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 267 "Kmkgmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkgrp;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 41;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkgrpnm;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmkgrprs;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[5].sqldata = (void*)&hyjijn;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[6].sqldata = (void*)kaiymd;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[7].sqldata = (void*)haiymd;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[8].sqldata = (void*)hnktntid;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 267 "Kmkgmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 267 "Kmkgmst.sqc"
      sqlasetdata(2,0,10,sql_setdlist,0L,0L);
    }
#line 267 "Kmkgmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 267 "Kmkgmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 267 "Kmkgmst.sqc"
  sqlastop(0L);
}

#line 267 "Kmkgmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 272 "Kmkgmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKmkgmstUpdate()
 *    KMKGMST レコードを更新する
 * ■引数
 *    [I]  Kmkgmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKmkgmstUpdate( Kmkgmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KmkgmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 296 "Kmkgmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 297 "Kmkgmst.sqc"


    
/*
EXEC SQL UPDATE KMKGMST
    SET (
		KMKGRPNM,
		KMKGRPRS,
		HYJIJN,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:kmkgrpnm,
		:kmkgrprs,
		:hyjijn,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		KMKGRP = :kmkgrp AND
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KAIYMD = :kaiymd;
*/

{
#line 318 "Kmkgmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 318 "Kmkgmst.sqc"
  sqlaaloc(2,10,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 318 "Kmkgmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 41;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkgrpnm;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkgrprs;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[2].sqldata = (void*)&hyjijn;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[3].sqldata = (void*)haiymd;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 9;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[4].sqldata = (void*)hnktntid;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 27;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[5].sqldata = (void*)ksndh;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 17;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[6].sqldata = (void*)kmkgrp;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 17;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[7].sqldata = (void*)knsgrp;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 8;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[8].sqldata = (void*)kmkcd;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[9].sqldata = (void*)kaiymd;
#line 318 "Kmkgmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 318 "Kmkgmst.sqc"
      sqlasetdata(2,0,10,sql_setdlist,0L,0L);
    }
#line 318 "Kmkgmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 318 "Kmkgmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 318 "Kmkgmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 318 "Kmkgmst.sqc"
  sqlastop(0L);
}

#line 318 "Kmkgmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 323 "Kmkgmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 327 "Kmkgmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKmkgmstDelete()
 *    KMKGMST レコードを削除する
 * ■引数
 *    [I]  Kmkgmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKmkgmstDelete( Kmkgmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KmkgmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 351 "Kmkgmst.sqc"


    
/*
EXEC SQL DELETE FROM KMKGMST
    WHERE
		KMKGRP = :kmkgrp AND
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KAIYMD = :kaiymd;
*/

{
#line 358 "Kmkgmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 358 "Kmkgmst.sqc"
  sqlaaloc(2,4,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 358 "Kmkgmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 358 "Kmkgmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkgrp;
#line 358 "Kmkgmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 358 "Kmkgmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 358 "Kmkgmst.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 358 "Kmkgmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 358 "Kmkgmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 358 "Kmkgmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 358 "Kmkgmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 358 "Kmkgmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 358 "Kmkgmst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 358 "Kmkgmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 358 "Kmkgmst.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 358 "Kmkgmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 358 "Kmkgmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 358 "Kmkgmst.sqc"
  sqlastop(0L);
}

#line 358 "Kmkgmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 363 "Kmkgmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
