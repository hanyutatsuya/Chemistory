static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,90,65,74,86,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,65,50,48,53,87,83,83,69,0,0,0,0,0,0,0,0,
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


#line 1 "A205wsseq.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： A205wsseq.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "A205wsseq.h"
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


#line 24 "A205wsseq.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "A205wsseq.sqc"

    sqlint32 wstbnknr;
    char    knskisymd[11];
    char    knsgrp[17];
    char    wssbt[11];
    sqlint32  wsno;
    sqlint32  knsseqst;
    sqlint32  knsseqed;
    sqlint32  knsseqsu;
    char    ksktkbn;
    char    dtnrtts[9];
    char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 41 "A205wsseq.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Wsseqknri

BmlDMMInfo	WsseqknriArray[] = {
	DMM_SLONG( wstbnknr ),
	DMM_SDATE( knskisymd ),
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( wssbt ),
	DMM_SLONG( wsno ),
	DMM_SLONG( knsseqst ),
	DMM_SLONG( knsseqed ),
	DMM_SLONG( knsseqsu ),
	DMM_SCHAR( ksktkbn ),
	DMM_SSTRING( dtnrtts ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * A205wsAllSel()
 *    WSSEQKNRI レコード全件取得
 * ■引数
 *    [O]  Wsseqknri** arrayOut 取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long A205wsAllSel( Wsseqknri** arrayOut, int* numOut )
{
    Wsseqknri*  array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 80 "A205wsseq.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		WSTBNKNR,
		KNSKISYMD,
		KNSGRP,
		WSSBT,
		WSNO,
		KNSSEQST,
		KNSSEQED,
		KNSSEQSU,
		KSKTKBN,
		DTNRTTS,
		KSNDH
    FROM
        WSSEQKNRI FOR READ ONLY;
*/

#line 96 "A205wsseq.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 98 "A205wsseq.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 98 "A205wsseq.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 98 "A205wsseq.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 98 "A205wsseq.sqc"
  sqlastop(0L);
}

#line 98 "A205wsseq.sqc"


    while( 1 ) {
        Wsseqknri* rec;

        
/*
EXEC SQL FETCH c1 INTO
		:wstbnknr,
		:knskisymd,
		:knsgrp,
		:wssbt,
		:wsno,
		:knsseqst,
		:knsseqed,
		:knsseqsu,
		:ksktkbn,
		:dtnrtts,
		:ksndh;
*/

{
#line 114 "A205wsseq.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 114 "A205wsseq.sqc"
  sqlaaloc(3,11,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[11];
#line 114 "A205wsseq.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 114 "A205wsseq.sqc"
      sql_setdlist[0].sqldata = (void*)&wstbnknr;
#line 114 "A205wsseq.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 114 "A205wsseq.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 114 "A205wsseq.sqc"
      sql_setdlist[1].sqldata = (void*)knskisymd;
#line 114 "A205wsseq.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 114 "A205wsseq.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 17;
#line 114 "A205wsseq.sqc"
      sql_setdlist[2].sqldata = (void*)knsgrp;
#line 114 "A205wsseq.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 114 "A205wsseq.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 114 "A205wsseq.sqc"
      sql_setdlist[3].sqldata = (void*)wssbt;
#line 114 "A205wsseq.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 114 "A205wsseq.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 114 "A205wsseq.sqc"
      sql_setdlist[4].sqldata = (void*)&wsno;
#line 114 "A205wsseq.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 114 "A205wsseq.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 114 "A205wsseq.sqc"
      sql_setdlist[5].sqldata = (void*)&knsseqst;
#line 114 "A205wsseq.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 114 "A205wsseq.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 114 "A205wsseq.sqc"
      sql_setdlist[6].sqldata = (void*)&knsseqed;
#line 114 "A205wsseq.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 114 "A205wsseq.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 114 "A205wsseq.sqc"
      sql_setdlist[7].sqldata = (void*)&knsseqsu;
#line 114 "A205wsseq.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 114 "A205wsseq.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 114 "A205wsseq.sqc"
      sql_setdlist[8].sqldata = (void*)&ksktkbn;
#line 114 "A205wsseq.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 114 "A205wsseq.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 9;
#line 114 "A205wsseq.sqc"
      sql_setdlist[9].sqldata = (void*)dtnrtts;
#line 114 "A205wsseq.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 114 "A205wsseq.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 27;
#line 114 "A205wsseq.sqc"
      sql_setdlist[10].sqldata = (void*)ksndh;
#line 114 "A205wsseq.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 114 "A205wsseq.sqc"
      sqlasetdata(3,0,11,sql_setdlist,0L,0L);
    }
#line 114 "A205wsseq.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 114 "A205wsseq.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 114 "A205wsseq.sqc"
  sqlastop(0L);
}

#line 114 "A205wsseq.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Wsseqknri*)ZbmlRealloc( array,
                                    sizeof( Wsseqknri ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Wsseqknri ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, WsseqknriArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 129 "A205wsseq.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 129 "A205wsseq.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 129 "A205wsseq.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 129 "A205wsseq.sqc"
  sqlastop(0L);
}

#line 129 "A205wsseq.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 137 "A205wsseq.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * A205wsInsert()
 *    WSSEQKNRI レコードを挿入する
 * ■引数
 *    [I]  Wsseqknri* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long A205wsInsert( Wsseqknri* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, WsseqknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 160 "A205wsseq.sqc"


    
/*
EXEC SQL INSERT INTO WSSEQKNRI
    (
		WSTBNKNR,
		KNSKISYMD,
		KNSGRP,
		WSSBT,
		WSNO,
		KNSSEQST,
		KNSSEQED,
		KNSSEQSU,
		KSKTKBN,
		DTNRTTS,
		KSNDH
    ) VALUES (
		:wstbnknr,
		:knskisymd,
		:knsgrp,
		:wssbt,
		:wsno,
		:knsseqst,
		:knsseqed,
		:knsseqsu,
		:ksktkbn,
		:dtnrtts,
		CURRENT TIMESTAMP
    );
*/

{
#line 187 "A205wsseq.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 187 "A205wsseq.sqc"
  sqlaaloc(2,10,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 187 "A205wsseq.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 187 "A205wsseq.sqc"
      sql_setdlist[0].sqldata = (void*)&wstbnknr;
#line 187 "A205wsseq.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 187 "A205wsseq.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 187 "A205wsseq.sqc"
      sql_setdlist[1].sqldata = (void*)knskisymd;
#line 187 "A205wsseq.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 187 "A205wsseq.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 17;
#line 187 "A205wsseq.sqc"
      sql_setdlist[2].sqldata = (void*)knsgrp;
#line 187 "A205wsseq.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 187 "A205wsseq.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 187 "A205wsseq.sqc"
      sql_setdlist[3].sqldata = (void*)wssbt;
#line 187 "A205wsseq.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 187 "A205wsseq.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 187 "A205wsseq.sqc"
      sql_setdlist[4].sqldata = (void*)&wsno;
#line 187 "A205wsseq.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 187 "A205wsseq.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 187 "A205wsseq.sqc"
      sql_setdlist[5].sqldata = (void*)&knsseqst;
#line 187 "A205wsseq.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 187 "A205wsseq.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 187 "A205wsseq.sqc"
      sql_setdlist[6].sqldata = (void*)&knsseqed;
#line 187 "A205wsseq.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 187 "A205wsseq.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 187 "A205wsseq.sqc"
      sql_setdlist[7].sqldata = (void*)&knsseqsu;
#line 187 "A205wsseq.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 187 "A205wsseq.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 187 "A205wsseq.sqc"
      sql_setdlist[8].sqldata = (void*)&ksktkbn;
#line 187 "A205wsseq.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 187 "A205wsseq.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 9;
#line 187 "A205wsseq.sqc"
      sql_setdlist[9].sqldata = (void*)dtnrtts;
#line 187 "A205wsseq.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 187 "A205wsseq.sqc"
      sqlasetdata(2,0,10,sql_setdlist,0L,0L);
    }
#line 187 "A205wsseq.sqc"
  sqlacall((unsigned short)24,2,2,0,0L);
#line 187 "A205wsseq.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 187 "A205wsseq.sqc"
  sqlastop(0L);
}

#line 187 "A205wsseq.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 192 "A205wsseq.sqc"

    return sqlca.sqlcode;
}

/** End of File *********************************************************/
