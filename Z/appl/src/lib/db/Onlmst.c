static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,99,66,85,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,53,53,90,79,78,76,77,32,0,0,0,0,0,0,0,0,
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


#line 1 "Onlmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Onlmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Onlmst.h"
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


#line 24 "Onlmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Onlmst.sqc"

	short   oncode;
	char    kbn[11];
	char    bskkbn[5];
	char    bsklne[5];
	char    bskgok[7];
	short   protocol;
	char    wsname[17];
	short   opentype;
	sqlint32  portno;
	char    onpath[129];
	short   approtocol;
	sqlint32  errorlevel;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 46 "Onlmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Onlmst

BmlDMMInfo	OnlmstArray[] = {
	DMM_SSHORT( oncode ),
	DMM_SSTRING( kbn ),
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( bsklne ),
	DMM_SSTRING( bskgok ),
	DMM_SSHORT( protocol ),
	DMM_SSTRING( wsname ),
	DMM_SSHORT( opentype ),
	DMM_SLONG( portno ),
	DMM_SSTRING( onpath ),
	DMM_SSHORT( approtocol ),
	DMM_SLONG( errorlevel ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbOnlmstSelectAll()
 *    ONLMST レコード全件取得
 * ■引数
 *    [O]  Onlmst** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbOnlmstSelectAll( Onlmst** arrayOut, int* numOut )
{
    Onlmst*     array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 90 "Onlmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		ONCODE,
		KBN,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		PROTOCOL,
		WSNAME,
		OPENTYPE,
		PORTNO,
		ONPATH,
		APPROTOCOL,
		ERRORLEVEL,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        ONLMST FOR READ ONLY;
*/

#line 111 "Onlmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 113 "Onlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 113 "Onlmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 113 "Onlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 113 "Onlmst.sqc"
  sqlastop(0L);
}

#line 113 "Onlmst.sqc"


    while( 1 ) {
        Onlmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:oncode,
			:kbn,
			:bskkbn,
			:bsklne,
			:bskgok,
			:protocol,
			:wsname,
			:opentype,
			:portno,
			:onpath,
			:approtocol,
			:errorlevel,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 134 "Onlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 134 "Onlmst.sqc"
  sqlaaloc(3,16,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[16];
#line 134 "Onlmst.sqc"
      sql_setdlist[0].sqltype = 500; sql_setdlist[0].sqllen = 2;
#line 134 "Onlmst.sqc"
      sql_setdlist[0].sqldata = (void*)&oncode;
#line 134 "Onlmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 134 "Onlmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 134 "Onlmst.sqc"
      sql_setdlist[1].sqldata = (void*)kbn;
#line 134 "Onlmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 134 "Onlmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 134 "Onlmst.sqc"
      sql_setdlist[2].sqldata = (void*)bskkbn;
#line 134 "Onlmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 134 "Onlmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 134 "Onlmst.sqc"
      sql_setdlist[3].sqldata = (void*)bsklne;
#line 134 "Onlmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 134 "Onlmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 7;
#line 134 "Onlmst.sqc"
      sql_setdlist[4].sqldata = (void*)bskgok;
#line 134 "Onlmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 134 "Onlmst.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 134 "Onlmst.sqc"
      sql_setdlist[5].sqldata = (void*)&protocol;
#line 134 "Onlmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 134 "Onlmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 17;
#line 134 "Onlmst.sqc"
      sql_setdlist[6].sqldata = (void*)wsname;
#line 134 "Onlmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 134 "Onlmst.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 134 "Onlmst.sqc"
      sql_setdlist[7].sqldata = (void*)&opentype;
#line 134 "Onlmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 134 "Onlmst.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 134 "Onlmst.sqc"
      sql_setdlist[8].sqldata = (void*)&portno;
#line 134 "Onlmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 134 "Onlmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 129;
#line 134 "Onlmst.sqc"
      sql_setdlist[9].sqldata = (void*)onpath;
#line 134 "Onlmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 134 "Onlmst.sqc"
      sql_setdlist[10].sqltype = 500; sql_setdlist[10].sqllen = 2;
#line 134 "Onlmst.sqc"
      sql_setdlist[10].sqldata = (void*)&approtocol;
#line 134 "Onlmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 134 "Onlmst.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 134 "Onlmst.sqc"
      sql_setdlist[11].sqldata = (void*)&errorlevel;
#line 134 "Onlmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 134 "Onlmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 134 "Onlmst.sqc"
      sql_setdlist[12].sqldata = (void*)kaiymd;
#line 134 "Onlmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 134 "Onlmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 134 "Onlmst.sqc"
      sql_setdlist[13].sqldata = (void*)haiymd;
#line 134 "Onlmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 134 "Onlmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 9;
#line 134 "Onlmst.sqc"
      sql_setdlist[14].sqldata = (void*)hnktntid;
#line 134 "Onlmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 134 "Onlmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 134 "Onlmst.sqc"
      sql_setdlist[15].sqldata = (void*)ksndh;
#line 134 "Onlmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 134 "Onlmst.sqc"
      sqlasetdata(3,0,16,sql_setdlist,0L,0L);
    }
#line 134 "Onlmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 134 "Onlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 134 "Onlmst.sqc"
  sqlastop(0L);
}

#line 134 "Onlmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Onlmst*)ZbmlRealloc( array,
                                    sizeof( Onlmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Onlmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, OnlmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 149 "Onlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 149 "Onlmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 149 "Onlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 149 "Onlmst.sqc"
  sqlastop(0L);
}

#line 149 "Onlmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 157 "Onlmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbOnlmstSelectKey()
 *    ONLMST レコードKey条件取得
 * ■引数
 *    [I]  Onlmst* pKey       取得するレコードのキー
 *    [O]  Onlmst** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbOnlmstSelectKey( Onlmst* pKey, Onlmst** arrayOut, int* numOut )
{
    Onlmst*     array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, OnlmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 183 "Onlmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		ONCODE,
		KBN,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		PROTOCOL,
		WSNAME,
		OPENTYPE,
		PORTNO,
		ONPATH,
		APPROTOCOL,
		ERRORLEVEL,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        ONLMST
    WHERE
		ONCODE = :oncode AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 207 "Onlmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 209 "Onlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 209 "Onlmst.sqc"
  sqlaaloc(2,2,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 209 "Onlmst.sqc"
      sql_setdlist[0].sqltype = 500; sql_setdlist[0].sqllen = 2;
#line 209 "Onlmst.sqc"
      sql_setdlist[0].sqldata = (void*)&oncode;
#line 209 "Onlmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 209 "Onlmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 209 "Onlmst.sqc"
      sql_setdlist[1].sqldata = (void*)kaiymd;
#line 209 "Onlmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 209 "Onlmst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 209 "Onlmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 209 "Onlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 209 "Onlmst.sqc"
  sqlastop(0L);
}

#line 209 "Onlmst.sqc"


    while( 1 ) {
        Onlmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:oncode,
			:kbn,
			:bskkbn,
			:bsklne,
			:bskgok,
			:protocol,
			:wsname,
			:opentype,
			:portno,
			:onpath,
			:approtocol,
			:errorlevel,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 230 "Onlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 230 "Onlmst.sqc"
  sqlaaloc(3,16,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[16];
#line 230 "Onlmst.sqc"
      sql_setdlist[0].sqltype = 500; sql_setdlist[0].sqllen = 2;
#line 230 "Onlmst.sqc"
      sql_setdlist[0].sqldata = (void*)&oncode;
#line 230 "Onlmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 230 "Onlmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 230 "Onlmst.sqc"
      sql_setdlist[1].sqldata = (void*)kbn;
#line 230 "Onlmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 230 "Onlmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 230 "Onlmst.sqc"
      sql_setdlist[2].sqldata = (void*)bskkbn;
#line 230 "Onlmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 230 "Onlmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 230 "Onlmst.sqc"
      sql_setdlist[3].sqldata = (void*)bsklne;
#line 230 "Onlmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 230 "Onlmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 7;
#line 230 "Onlmst.sqc"
      sql_setdlist[4].sqldata = (void*)bskgok;
#line 230 "Onlmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 230 "Onlmst.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 230 "Onlmst.sqc"
      sql_setdlist[5].sqldata = (void*)&protocol;
#line 230 "Onlmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 230 "Onlmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 17;
#line 230 "Onlmst.sqc"
      sql_setdlist[6].sqldata = (void*)wsname;
#line 230 "Onlmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 230 "Onlmst.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 230 "Onlmst.sqc"
      sql_setdlist[7].sqldata = (void*)&opentype;
#line 230 "Onlmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 230 "Onlmst.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 230 "Onlmst.sqc"
      sql_setdlist[8].sqldata = (void*)&portno;
#line 230 "Onlmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 230 "Onlmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 129;
#line 230 "Onlmst.sqc"
      sql_setdlist[9].sqldata = (void*)onpath;
#line 230 "Onlmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 230 "Onlmst.sqc"
      sql_setdlist[10].sqltype = 500; sql_setdlist[10].sqllen = 2;
#line 230 "Onlmst.sqc"
      sql_setdlist[10].sqldata = (void*)&approtocol;
#line 230 "Onlmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 230 "Onlmst.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 230 "Onlmst.sqc"
      sql_setdlist[11].sqldata = (void*)&errorlevel;
#line 230 "Onlmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 230 "Onlmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 230 "Onlmst.sqc"
      sql_setdlist[12].sqldata = (void*)kaiymd;
#line 230 "Onlmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 230 "Onlmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 230 "Onlmst.sqc"
      sql_setdlist[13].sqldata = (void*)haiymd;
#line 230 "Onlmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 230 "Onlmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 9;
#line 230 "Onlmst.sqc"
      sql_setdlist[14].sqldata = (void*)hnktntid;
#line 230 "Onlmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 230 "Onlmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 230 "Onlmst.sqc"
      sql_setdlist[15].sqldata = (void*)ksndh;
#line 230 "Onlmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 230 "Onlmst.sqc"
      sqlasetdata(3,0,16,sql_setdlist,0L,0L);
    }
#line 230 "Onlmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 230 "Onlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 230 "Onlmst.sqc"
  sqlastop(0L);
}

#line 230 "Onlmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Onlmst*)ZbmlRealloc( array,
                                    sizeof( Onlmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Onlmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, OnlmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 245 "Onlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 245 "Onlmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 245 "Onlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 245 "Onlmst.sqc"
  sqlastop(0L);
}

#line 245 "Onlmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 253 "Onlmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbOnlmstInsert()
 *    ONLMST レコードを挿入する
 * ■引数
 *    [I]  Onlmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbOnlmstInsert( Onlmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, OnlmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 276 "Onlmst.sqc"


    
/*
EXEC SQL INSERT INTO ONLMST
    (
		ONCODE,
		KBN,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		PROTOCOL,
		WSNAME,
		OPENTYPE,
		PORTNO,
		ONPATH,
		APPROTOCOL,
		ERRORLEVEL,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:oncode,
		:kbn,
		:bskkbn,
		:bsklne,
		:bskgok,
		:protocol,
		:wsname,
		:opentype,
		:portno,
		:onpath,
		:approtocol,
		:errorlevel,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 313 "Onlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 313 "Onlmst.sqc"
  sqlaaloc(2,16,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[16];
#line 313 "Onlmst.sqc"
      sql_setdlist[0].sqltype = 500; sql_setdlist[0].sqllen = 2;
#line 313 "Onlmst.sqc"
      sql_setdlist[0].sqldata = (void*)&oncode;
#line 313 "Onlmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 313 "Onlmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 313 "Onlmst.sqc"
      sql_setdlist[1].sqldata = (void*)kbn;
#line 313 "Onlmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 313 "Onlmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 313 "Onlmst.sqc"
      sql_setdlist[2].sqldata = (void*)bskkbn;
#line 313 "Onlmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 313 "Onlmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 313 "Onlmst.sqc"
      sql_setdlist[3].sqldata = (void*)bsklne;
#line 313 "Onlmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 313 "Onlmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 7;
#line 313 "Onlmst.sqc"
      sql_setdlist[4].sqldata = (void*)bskgok;
#line 313 "Onlmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 313 "Onlmst.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 313 "Onlmst.sqc"
      sql_setdlist[5].sqldata = (void*)&protocol;
#line 313 "Onlmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 313 "Onlmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 17;
#line 313 "Onlmst.sqc"
      sql_setdlist[6].sqldata = (void*)wsname;
#line 313 "Onlmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 313 "Onlmst.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 313 "Onlmst.sqc"
      sql_setdlist[7].sqldata = (void*)&opentype;
#line 313 "Onlmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 313 "Onlmst.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 313 "Onlmst.sqc"
      sql_setdlist[8].sqldata = (void*)&portno;
#line 313 "Onlmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 313 "Onlmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 129;
#line 313 "Onlmst.sqc"
      sql_setdlist[9].sqldata = (void*)onpath;
#line 313 "Onlmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 313 "Onlmst.sqc"
      sql_setdlist[10].sqltype = 500; sql_setdlist[10].sqllen = 2;
#line 313 "Onlmst.sqc"
      sql_setdlist[10].sqldata = (void*)&approtocol;
#line 313 "Onlmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 313 "Onlmst.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 313 "Onlmst.sqc"
      sql_setdlist[11].sqldata = (void*)&errorlevel;
#line 313 "Onlmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 313 "Onlmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 313 "Onlmst.sqc"
      sql_setdlist[12].sqldata = (void*)kaiymd;
#line 313 "Onlmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 313 "Onlmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 313 "Onlmst.sqc"
      sql_setdlist[13].sqldata = (void*)haiymd;
#line 313 "Onlmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 313 "Onlmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 9;
#line 313 "Onlmst.sqc"
      sql_setdlist[14].sqldata = (void*)hnktntid;
#line 313 "Onlmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 313 "Onlmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 313 "Onlmst.sqc"
      sql_setdlist[15].sqldata = (void*)ksndh;
#line 313 "Onlmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 313 "Onlmst.sqc"
      sqlasetdata(2,0,16,sql_setdlist,0L,0L);
    }
#line 313 "Onlmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 313 "Onlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 313 "Onlmst.sqc"
  sqlastop(0L);
}

#line 313 "Onlmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 318 "Onlmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbOnlmstUpdate()
 *    ONLMST レコードを更新する
 * ■引数
 *    [I]  Onlmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbOnlmstUpdate( Onlmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, OnlmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 342 "Onlmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 343 "Onlmst.sqc"


    
/*
EXEC SQL UPDATE ONLMST
    SET (
		KBN,
		BSKKBN,
		BSKLNE,
		BSKGOK,
		PROTOCOL,
		WSNAME,
		OPENTYPE,
		PORTNO,
		ONPATH,
		APPROTOCOL,
		ERRORLEVEL,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:kbn,
		:bskkbn,
		:bsklne,
		:bskgok,
		:protocol,
		:wsname,
		:opentype,
		:portno,
		:onpath,
		:approtocol,
		:errorlevel,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		ONCODE = :oncode AND
		KAIYMD = :kaiymd;
*/

{
#line 378 "Onlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 378 "Onlmst.sqc"
  sqlaaloc(2,16,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[16];
#line 378 "Onlmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 378 "Onlmst.sqc"
      sql_setdlist[0].sqldata = (void*)kbn;
#line 378 "Onlmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 378 "Onlmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 378 "Onlmst.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 378 "Onlmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 378 "Onlmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 378 "Onlmst.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 378 "Onlmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 378 "Onlmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 7;
#line 378 "Onlmst.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 378 "Onlmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 378 "Onlmst.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 378 "Onlmst.sqc"
      sql_setdlist[4].sqldata = (void*)&protocol;
#line 378 "Onlmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 378 "Onlmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 17;
#line 378 "Onlmst.sqc"
      sql_setdlist[5].sqldata = (void*)wsname;
#line 378 "Onlmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 378 "Onlmst.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 378 "Onlmst.sqc"
      sql_setdlist[6].sqldata = (void*)&opentype;
#line 378 "Onlmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 378 "Onlmst.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 378 "Onlmst.sqc"
      sql_setdlist[7].sqldata = (void*)&portno;
#line 378 "Onlmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 378 "Onlmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 129;
#line 378 "Onlmst.sqc"
      sql_setdlist[8].sqldata = (void*)onpath;
#line 378 "Onlmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 378 "Onlmst.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 378 "Onlmst.sqc"
      sql_setdlist[9].sqldata = (void*)&approtocol;
#line 378 "Onlmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 378 "Onlmst.sqc"
      sql_setdlist[10].sqltype = 496; sql_setdlist[10].sqllen = 4;
#line 378 "Onlmst.sqc"
      sql_setdlist[10].sqldata = (void*)&errorlevel;
#line 378 "Onlmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 378 "Onlmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 378 "Onlmst.sqc"
      sql_setdlist[11].sqldata = (void*)haiymd;
#line 378 "Onlmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 378 "Onlmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 378 "Onlmst.sqc"
      sql_setdlist[12].sqldata = (void*)hnktntid;
#line 378 "Onlmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 378 "Onlmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 27;
#line 378 "Onlmst.sqc"
      sql_setdlist[13].sqldata = (void*)ksndh;
#line 378 "Onlmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 378 "Onlmst.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 378 "Onlmst.sqc"
      sql_setdlist[14].sqldata = (void*)&oncode;
#line 378 "Onlmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 378 "Onlmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 11;
#line 378 "Onlmst.sqc"
      sql_setdlist[15].sqldata = (void*)kaiymd;
#line 378 "Onlmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 378 "Onlmst.sqc"
      sqlasetdata(2,0,16,sql_setdlist,0L,0L);
    }
#line 378 "Onlmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 378 "Onlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 378 "Onlmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 378 "Onlmst.sqc"
  sqlastop(0L);
}

#line 378 "Onlmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 383 "Onlmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 387 "Onlmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbOnlmstDelete()
 *    ONLMST レコードを削除する
 * ■引数
 *    [I]  Onlmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbOnlmstDelete( Onlmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, OnlmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 411 "Onlmst.sqc"


    
/*
EXEC SQL DELETE FROM ONLMST
    WHERE
		ONCODE = :oncode AND
		KAIYMD = :kaiymd;
*/

{
#line 416 "Onlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 416 "Onlmst.sqc"
  sqlaaloc(2,2,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 416 "Onlmst.sqc"
      sql_setdlist[0].sqltype = 500; sql_setdlist[0].sqllen = 2;
#line 416 "Onlmst.sqc"
      sql_setdlist[0].sqldata = (void*)&oncode;
#line 416 "Onlmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 416 "Onlmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 416 "Onlmst.sqc"
      sql_setdlist[1].sqldata = (void*)kaiymd;
#line 416 "Onlmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 416 "Onlmst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 416 "Onlmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 416 "Onlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 416 "Onlmst.sqc"
  sqlastop(0L);
}

#line 416 "Onlmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 421 "Onlmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
