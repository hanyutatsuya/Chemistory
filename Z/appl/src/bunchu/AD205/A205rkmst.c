static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,81,66,85,86,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,65,50,48,53,82,75,77,83,0,0,0,0,0,0,0,0,
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


#line 1 "A205rkmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Rkmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2008-01-07                    Create(新フロンティア対応)
 *  4.01     2009-02-10     K.Ameno        緊急SUN EOSL対応        
 *                                         AD105を複製して作成
**********************************************************************/
#include <stdio.h>

#include "A205rkmst.h"
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


#line 26 "A205rkmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 31 "A205rkmst.sqc"

	char    smpcd[8];
	char    rksbt;
	char    rknm[21];
	short   rkknhsu;
	short   trrcksu;
	char    filskdir[129];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 42 "A205rkmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Rkmst

BmlDMMInfo	RkmstArray[] = {
	DMM_SSTRING( smpcd ),
	DMM_SCHAR( rksbt ),
	DMM_SSTRING( rknm ),
	DMM_SSHORT( rkknhsu ),
	DMM_SSHORT( trrcksu ),
	DMM_SSTRING( filskdir ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * A205rkmstSelectKey()
 *    RKMST レコードKey条件取得
 * ■引数
 *    [I]  Rkmst* pKey       取得するレコードのキー
 *    [O]  Rkmst** arrayOut     取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long A205rkmstSelectKey( Rkmst* pKey, Rkmst** arrayOut, int* numOut )
{
    Rkmst*      array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, RkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 87 "A205rkmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		SMPCD,
		RKSBT,
		RKNM,
		RKKNHSU,
		TRRCKSU,
		FILSKDIR,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        RKMST
    WHERE
		SMPCD = :smpcd AND
		KAIYMD <= :kaiymd AND
		HAIYMD >= :kaiymd 
		FOR READ ONLY;
*/

#line 107 "A205rkmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 109 "A205rkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 109 "A205rkmst.sqc"
  sqlaaloc(2,3,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 109 "A205rkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 109 "A205rkmst.sqc"
      sql_setdlist[0].sqldata = (void*)smpcd;
#line 109 "A205rkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 109 "A205rkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 109 "A205rkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kaiymd;
#line 109 "A205rkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 109 "A205rkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 109 "A205rkmst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 109 "A205rkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 109 "A205rkmst.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 109 "A205rkmst.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 109 "A205rkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 109 "A205rkmst.sqc"
  sqlastop(0L);
}

#line 109 "A205rkmst.sqc"


    while( 1 ) {
        Rkmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:smpcd,
			:rksbt,
			:rknm,
			:rkknhsu,
			:trrcksu,
			:filskdir,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 124 "A205rkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 124 "A205rkmst.sqc"
  sqlaaloc(3,10,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 124 "A205rkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 124 "A205rkmst.sqc"
      sql_setdlist[0].sqldata = (void*)smpcd;
#line 124 "A205rkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 124 "A205rkmst.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 124 "A205rkmst.sqc"
      sql_setdlist[1].sqldata = (void*)&rksbt;
#line 124 "A205rkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 124 "A205rkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 124 "A205rkmst.sqc"
      sql_setdlist[2].sqldata = (void*)rknm;
#line 124 "A205rkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 124 "A205rkmst.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 124 "A205rkmst.sqc"
      sql_setdlist[3].sqldata = (void*)&rkknhsu;
#line 124 "A205rkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 124 "A205rkmst.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 124 "A205rkmst.sqc"
      sql_setdlist[4].sqldata = (void*)&trrcksu;
#line 124 "A205rkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 124 "A205rkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 129;
#line 124 "A205rkmst.sqc"
      sql_setdlist[5].sqldata = (void*)filskdir;
#line 124 "A205rkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 124 "A205rkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 124 "A205rkmst.sqc"
      sql_setdlist[6].sqldata = (void*)kaiymd;
#line 124 "A205rkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 124 "A205rkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 124 "A205rkmst.sqc"
      sql_setdlist[7].sqldata = (void*)haiymd;
#line 124 "A205rkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 124 "A205rkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 124 "A205rkmst.sqc"
      sql_setdlist[8].sqldata = (void*)hnktntid;
#line 124 "A205rkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 124 "A205rkmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 124 "A205rkmst.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 124 "A205rkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 124 "A205rkmst.sqc"
      sqlasetdata(3,0,10,sql_setdlist,0L,0L);
    }
#line 124 "A205rkmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 124 "A205rkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 124 "A205rkmst.sqc"
  sqlastop(0L);
}

#line 124 "A205rkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Rkmst*)ZbmlRealloc( array,
                                    sizeof( Rkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Rkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, RkmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 139 "A205rkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 139 "A205rkmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 139 "A205rkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 139 "A205rkmst.sqc"
  sqlastop(0L);
}

#line 139 "A205rkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 147 "A205rkmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
