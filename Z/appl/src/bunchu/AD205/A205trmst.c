static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,88,66,78,86,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,65,50,48,53,84,82,77,83,0,0,0,0,0,0,0,0,
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


#line 1 "A205trmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Trmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 *  1.01     2007-02-28                    Copy from Trmst.sqc(LIB)
 **********************************************************************/
#include <stdio.h>

#include "A205trmst.h"
#include "bml_misc.h"
#include "bml_db.h"
#include "bml_dmm.h"

#include "bmllog.h"

#define ALLOC_UNIT		1


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 27 "A205trmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 32 "A205trmst.sqc"

	char    trhdid[11];
	char    trsbt;
	char    trnm[21];
	short   trknhsu;
	short   trrcksu;
	char    filskdir[129];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 43 "A205trmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Trmst

BmlDMMInfo	TrmstArray[] = {
	DMM_SSTRING( trhdid ),
	DMM_SCHAR( trsbt ),
	DMM_SSTRING( trnm ),
	DMM_SSHORT( trknhsu ),
	DMM_SSHORT( trrcksu ),
	DMM_SSTRING( filskdir ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbTrmstSelectKey()
 *    TRMST レコードKey条件取得
 * ■引数
 *    [I]  Trmst* pKey       取得するレコードのキー
 *    [O]  Trmst** arrayOut     取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long A205trmstSelectKey( Trmst* pKey, Trmst** arrayOut, int* numOut )
{
    Trmst*      array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, TrmstArray ) )
        return HRC_INVALID_VALUE;

/*** ameno ***/
	sFncPutLog ( TRCKIND_WARNING, __FILE__, "A205trmstSelectKey", __LINE__,
		EXEFLG_NON, "00000000",
		"トレーマスタSELECT トレーID(%s) 処理日(%s)", trhdid, kaiymd );
/*** ameno ***/

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 94 "A205trmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		TRHDID,
		TRSBT,
		TRNM,
		TRKNHSU,
		TRRCKSU,
		FILSKDIR,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        TRMST
    WHERE
		TRHDID = :trhdid AND
		KAIYMD <= :kaiymd AND
		HAIYMD >= :kaiymd 
		FOR READ ONLY;
*/

#line 114 "A205trmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 116 "A205trmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 116 "A205trmst.sqc"
  sqlaaloc(2,3,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 116 "A205trmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 116 "A205trmst.sqc"
      sql_setdlist[0].sqldata = (void*)trhdid;
#line 116 "A205trmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 116 "A205trmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 116 "A205trmst.sqc"
      sql_setdlist[1].sqldata = (void*)kaiymd;
#line 116 "A205trmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 116 "A205trmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 116 "A205trmst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 116 "A205trmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 116 "A205trmst.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 116 "A205trmst.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 116 "A205trmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 116 "A205trmst.sqc"
  sqlastop(0L);
}

#line 116 "A205trmst.sqc"


    while( 1 ) {
        Trmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:trhdid,
			:trsbt,
			:trnm,
			:trknhsu,
			:trrcksu,
			:filskdir,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 131 "A205trmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 131 "A205trmst.sqc"
  sqlaaloc(3,10,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 131 "A205trmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 131 "A205trmst.sqc"
      sql_setdlist[0].sqldata = (void*)trhdid;
#line 131 "A205trmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 131 "A205trmst.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 131 "A205trmst.sqc"
      sql_setdlist[1].sqldata = (void*)&trsbt;
#line 131 "A205trmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 131 "A205trmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 131 "A205trmst.sqc"
      sql_setdlist[2].sqldata = (void*)trnm;
#line 131 "A205trmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 131 "A205trmst.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 131 "A205trmst.sqc"
      sql_setdlist[3].sqldata = (void*)&trknhsu;
#line 131 "A205trmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 131 "A205trmst.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 131 "A205trmst.sqc"
      sql_setdlist[4].sqldata = (void*)&trrcksu;
#line 131 "A205trmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 131 "A205trmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 129;
#line 131 "A205trmst.sqc"
      sql_setdlist[5].sqldata = (void*)filskdir;
#line 131 "A205trmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 131 "A205trmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 131 "A205trmst.sqc"
      sql_setdlist[6].sqldata = (void*)kaiymd;
#line 131 "A205trmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 131 "A205trmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 131 "A205trmst.sqc"
      sql_setdlist[7].sqldata = (void*)haiymd;
#line 131 "A205trmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 131 "A205trmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 131 "A205trmst.sqc"
      sql_setdlist[8].sqldata = (void*)hnktntid;
#line 131 "A205trmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 131 "A205trmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 131 "A205trmst.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 131 "A205trmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 131 "A205trmst.sqc"
      sqlasetdata(3,0,10,sql_setdlist,0L,0L);
    }
#line 131 "A205trmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 131 "A205trmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 131 "A205trmst.sqc"
  sqlastop(0L);
}

#line 131 "A205trmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Trmst*)ZbmlRealloc( array,
                                    sizeof( Trmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Trmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, TrmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 146 "A205trmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 146 "A205trmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 146 "A205trmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 146 "A205trmst.sqc"
  sqlastop(0L);
}

#line 146 "A205trmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 154 "A205trmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
