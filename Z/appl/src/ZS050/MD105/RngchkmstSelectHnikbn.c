static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,84,65,76,106,84,81,70,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,49,48,90,84,85,78,69,50,0,0,0,0,0,0,0,0,
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


#line 1 "RngchkmstSelectHnikbn.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： ShougoChk.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2009-09-17                    Create
 **********************************************************************/
#include <stdio.h>

#include "Rngchkmst.h"
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


#line 24 "RngchkmstSelectHnikbn.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "RngchkmstSelectHnikbn.sqc"

	char    hnikbn;
	char    knsgrp[17];
	char    kmkcd[8];
	char    zaicd[5];
	char    sstcd[8];
	char    sbt;
	char    ssa;
	char    zen_kyoyou;
	char    hrng[21];
	char    lrng[21];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

	char    sel_knskisymd[11];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 46 "RngchkmstSelectHnikbn.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Rngchkmst

BmlDMMInfo	RngchkmstHnikbnArray[] = {
	DMM_SCHAR( hnikbn ),
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( zaicd ),
	DMM_SSTRING( sstcd ),
	DMM_SCHAR( sbt ),
	DMM_SCHAR( ssa ),
	DMM_SCHAR( zen_kyoyou ),
	DMM_SSTRING( hrng ),
	DMM_SSTRING( lrng ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbRngchkmstSelectHnikbn()
 *    RNGCHKMST レコードKey条件取得
 * ■引数
 *    [I]  Rngchkmst* pKey      取得するレコードのキー
 *    [O]  Rngchkmst** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbRngchkmstSelectHnikbn( char * aKnskisymd, Rngchkmst* pKey, Rngchkmst** arrayOut, int* numOut )
{
    Rngchkmst*  array = NULL;
    int         num = 0;

	/* 変数の初期化 */
	memset( sel_knskisymd, '\0',sizeof(sel_knskisymd) ) ;

	/* ホスト変数へ複写 */
	strcpy ( sel_knskisymd, aKnskisymd ) ;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, RngchkmstHnikbnArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 101 "RngchkmstSelectHnikbn.sqc"


    
/*
EXEC SQL DECLARE c3 CURSOR FOR
    SELECT
		HNIKBN,
		KNSGRP,
		KMKCD,
		ZAICD,
		SSTCD,
		SBT,
		SSA,
		ZEN_KYOYOU,
		HRNG,
		LRNG,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        RNGCHKMST
    WHERE
		HNIKBN = :hnikbn AND
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		ZAICD = :zaicd AND
		SSTCD = :sstcd AND
		SBT = :sbt AND
		KAIYMD <= :sel_knskisymd AND 
		HAIYMD >= :sel_knskisymd
	FOR READ ONLY;
*/

#line 130 "RngchkmstSelectHnikbn.sqc"


    
/*
EXEC SQL OPEN c3;
*/

{
#line 132 "RngchkmstSelectHnikbn.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 132 "RngchkmstSelectHnikbn.sqc"
  sqlaaloc(2,8,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 132 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 132 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[0].sqldata = (void*)&hnikbn;
#line 132 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 132 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 132 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 132 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 132 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 132 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 132 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 132 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 132 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[3].sqldata = (void*)zaicd;
#line 132 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 132 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 132 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[4].sqldata = (void*)sstcd;
#line 132 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 132 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 132 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[5].sqldata = (void*)&sbt;
#line 132 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 132 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 132 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[6].sqldata = (void*)sel_knskisymd;
#line 132 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 132 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 132 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[7].sqldata = (void*)sel_knskisymd;
#line 132 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 132 "RngchkmstSelectHnikbn.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 132 "RngchkmstSelectHnikbn.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 132 "RngchkmstSelectHnikbn.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 132 "RngchkmstSelectHnikbn.sqc"
  sqlastop(0L);
}

#line 132 "RngchkmstSelectHnikbn.sqc"


    while( 1 ) {
        Rngchkmst* rec;

        
/*
EXEC SQL FETCH c3 INTO
			:hnikbn,
			:knsgrp,
			:kmkcd,
			:zaicd,
			:sstcd,
			:sbt,
			:ssa,
			:zen_kyoyou,
			:hrng,
			:lrng,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 151 "RngchkmstSelectHnikbn.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 151 "RngchkmstSelectHnikbn.sqc"
  sqlaaloc(3,14,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[14];
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[0].sqldata = (void*)&hnikbn;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[3].sqldata = (void*)zaicd;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[4].sqldata = (void*)sstcd;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[5].sqldata = (void*)&sbt;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[6].sqldata = (void*)&ssa;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[7].sqldata = (void*)&zen_kyoyou;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 21;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[8].sqldata = (void*)hrng;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 21;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[9].sqldata = (void*)lrng;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[10].sqldata = (void*)kaiymd;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[11].sqldata = (void*)haiymd;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[12].sqldata = (void*)hnktntid;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 27;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[13].sqldata = (void*)ksndh;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 151 "RngchkmstSelectHnikbn.sqc"
      sqlasetdata(3,0,14,sql_setdlist,0L,0L);
    }
#line 151 "RngchkmstSelectHnikbn.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 151 "RngchkmstSelectHnikbn.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 151 "RngchkmstSelectHnikbn.sqc"
  sqlastop(0L);
}

#line 151 "RngchkmstSelectHnikbn.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Rngchkmst*)ZbmlRealloc( array,
                                    sizeof( Rngchkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Rngchkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, RngchkmstHnikbnArray );
    }

    
/*
EXEC SQL CLOSE c3;
*/

{
#line 166 "RngchkmstSelectHnikbn.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 166 "RngchkmstSelectHnikbn.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 166 "RngchkmstSelectHnikbn.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 166 "RngchkmstSelectHnikbn.sqc"
  sqlastop(0L);
}

#line 166 "RngchkmstSelectHnikbn.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 174 "RngchkmstSelectHnikbn.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
