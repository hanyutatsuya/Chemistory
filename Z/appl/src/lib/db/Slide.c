static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,69,66,86,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,54,52,90,83,76,73,68,32,0,0,0,0,0,0,0,0,
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


#line 1 "Slide.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Slide.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Slide.h"
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


#line 24 "Slide.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Slide.sqc"

	char    knskisymd[11];
	char    sriymd[11];
	char    kntno[21];
	char    kntketflg;
	char    knsgrp[11];
	char    skssbt[3];
	sqlint32  knsseq;
	char    stkbn[11];
	short   stno;
	char    cstid[11];
	short   cstpos;
	char    hhnjtflg;
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 43 "Slide.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Slide

BmlDMMInfo	SlideArray[] = {
	DMM_SDATE( knskisymd ),
	DMM_SDATE( sriymd ),
	DMM_SSTRING( kntno ),
	DMM_SCHAR( kntketflg ),
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( skssbt ),
	DMM_SLONG( knsseq ),
	DMM_SSTRING( stkbn ),
	DMM_SSHORT( stno ),
	DMM_SSTRING( cstid ),
	DMM_SSHORT( cstpos ),
	DMM_SCHAR( hhnjtflg ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbSlideSelectAll()
 *    SLIDE レコード全件取得
 * ■引数
 *    [O]  Slide** arrayOut     取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbSlideSelectAll( Slide** arrayOut, int* numOut )
{
    Slide*      array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 84 "Slide.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSKISYMD,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		KNSGRP,
		SKSSBT,
		KNSSEQ,
		STKBN,
		STNO,
		CSTID,
		CSTPOS,
		HHNJTFLG,
		KSNDH
    FROM
        SLIDE FOR READ ONLY;
*/

#line 102 "Slide.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 104 "Slide.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 104 "Slide.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 104 "Slide.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 104 "Slide.sqc"
  sqlastop(0L);
}

#line 104 "Slide.sqc"


    while( 1 ) {
        Slide* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knskisymd,
			:sriymd,
			:kntno,
			:kntketflg,
			:knsgrp,
			:skssbt,
			:knsseq,
			:stkbn,
			:stno,
			:cstid,
			:cstpos,
			:hhnjtflg,
			:ksndh;
*/

{
#line 122 "Slide.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 122 "Slide.sqc"
  sqlaaloc(3,13,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[13];
#line 122 "Slide.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 122 "Slide.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 122 "Slide.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 122 "Slide.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 122 "Slide.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 122 "Slide.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 122 "Slide.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 122 "Slide.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 122 "Slide.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 122 "Slide.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 122 "Slide.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 122 "Slide.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 122 "Slide.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 122 "Slide.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 122 "Slide.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 122 "Slide.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 122 "Slide.sqc"
      sql_setdlist[5].sqldata = (void*)skssbt;
#line 122 "Slide.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 122 "Slide.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 122 "Slide.sqc"
      sql_setdlist[6].sqldata = (void*)&knsseq;
#line 122 "Slide.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 122 "Slide.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 122 "Slide.sqc"
      sql_setdlist[7].sqldata = (void*)stkbn;
#line 122 "Slide.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 122 "Slide.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 122 "Slide.sqc"
      sql_setdlist[8].sqldata = (void*)&stno;
#line 122 "Slide.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 122 "Slide.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 122 "Slide.sqc"
      sql_setdlist[9].sqldata = (void*)cstid;
#line 122 "Slide.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 122 "Slide.sqc"
      sql_setdlist[10].sqltype = 500; sql_setdlist[10].sqllen = 2;
#line 122 "Slide.sqc"
      sql_setdlist[10].sqldata = (void*)&cstpos;
#line 122 "Slide.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 122 "Slide.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 122 "Slide.sqc"
      sql_setdlist[11].sqldata = (void*)&hhnjtflg;
#line 122 "Slide.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 122 "Slide.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 27;
#line 122 "Slide.sqc"
      sql_setdlist[12].sqldata = (void*)ksndh;
#line 122 "Slide.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 122 "Slide.sqc"
      sqlasetdata(3,0,13,sql_setdlist,0L,0L);
    }
#line 122 "Slide.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 122 "Slide.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 122 "Slide.sqc"
  sqlastop(0L);
}

#line 122 "Slide.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Slide*)ZbmlRealloc( array,
                                    sizeof( Slide ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Slide ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, SlideArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 137 "Slide.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 137 "Slide.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 137 "Slide.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 137 "Slide.sqc"
  sqlastop(0L);
}

#line 137 "Slide.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 145 "Slide.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbSlideSelectKey()
 *    SLIDE レコードKey条件取得
 * ■引数
 *    [I]  Slide* pKey       取得するレコードのキー
 *    [O]  Slide** arrayOut     取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbSlideSelectKey( Slide* pKey, Slide** arrayOut, int* numOut )
{
    Slide*      array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, SlideArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 171 "Slide.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSKISYMD,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		KNSGRP,
		SKSSBT,
		KNSSEQ,
		STKBN,
		STNO,
		CSTID,
		CSTPOS,
		HHNJTFLG,
		KSNDH
    FROM
        SLIDE
    WHERE
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		KNSGRP         = :knsgrp         AND
		SKSSBT = :skssbt FOR READ ONLY;
*/

#line 195 "Slide.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 197 "Slide.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 197 "Slide.sqc"
  sqlaaloc(2,5,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 197 "Slide.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 197 "Slide.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 197 "Slide.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 197 "Slide.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 197 "Slide.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 197 "Slide.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 197 "Slide.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 197 "Slide.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 197 "Slide.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 197 "Slide.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 197 "Slide.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 197 "Slide.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 197 "Slide.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 3;
#line 197 "Slide.sqc"
      sql_setdlist[4].sqldata = (void*)skssbt;
#line 197 "Slide.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 197 "Slide.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 197 "Slide.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 197 "Slide.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 197 "Slide.sqc"
  sqlastop(0L);
}

#line 197 "Slide.sqc"


    while( 1 ) {
        Slide* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knskisymd,
			:sriymd,
			:kntno,
			:kntketflg,
			:knsgrp,
			:skssbt,
			:knsseq,
			:stkbn,
			:stno,
			:cstid,
			:cstpos,
			:hhnjtflg,
			:ksndh;
*/

{
#line 215 "Slide.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 215 "Slide.sqc"
  sqlaaloc(3,13,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[13];
#line 215 "Slide.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 215 "Slide.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 215 "Slide.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 215 "Slide.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 215 "Slide.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 215 "Slide.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 215 "Slide.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 215 "Slide.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 215 "Slide.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 215 "Slide.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 215 "Slide.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 215 "Slide.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 215 "Slide.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 215 "Slide.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 215 "Slide.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 215 "Slide.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 215 "Slide.sqc"
      sql_setdlist[5].sqldata = (void*)skssbt;
#line 215 "Slide.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 215 "Slide.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 215 "Slide.sqc"
      sql_setdlist[6].sqldata = (void*)&knsseq;
#line 215 "Slide.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 215 "Slide.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 215 "Slide.sqc"
      sql_setdlist[7].sqldata = (void*)stkbn;
#line 215 "Slide.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 215 "Slide.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 215 "Slide.sqc"
      sql_setdlist[8].sqldata = (void*)&stno;
#line 215 "Slide.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 215 "Slide.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 215 "Slide.sqc"
      sql_setdlist[9].sqldata = (void*)cstid;
#line 215 "Slide.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 215 "Slide.sqc"
      sql_setdlist[10].sqltype = 500; sql_setdlist[10].sqllen = 2;
#line 215 "Slide.sqc"
      sql_setdlist[10].sqldata = (void*)&cstpos;
#line 215 "Slide.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 215 "Slide.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 215 "Slide.sqc"
      sql_setdlist[11].sqldata = (void*)&hhnjtflg;
#line 215 "Slide.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 215 "Slide.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 27;
#line 215 "Slide.sqc"
      sql_setdlist[12].sqldata = (void*)ksndh;
#line 215 "Slide.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 215 "Slide.sqc"
      sqlasetdata(3,0,13,sql_setdlist,0L,0L);
    }
#line 215 "Slide.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 215 "Slide.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 215 "Slide.sqc"
  sqlastop(0L);
}

#line 215 "Slide.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Slide*)ZbmlRealloc( array,
                                    sizeof( Slide ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Slide ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, SlideArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 230 "Slide.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 230 "Slide.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 230 "Slide.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 230 "Slide.sqc"
  sqlastop(0L);
}

#line 230 "Slide.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 238 "Slide.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbSlideInsert()
 *    SLIDE レコードを挿入する
 * ■引数
 *    [I]  Slide* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbSlideInsert( Slide* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, SlideArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 261 "Slide.sqc"


    
/*
EXEC SQL INSERT INTO SLIDE
    (
		KNSKISYMD,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		KNSGRP,
		SKSSBT,
		KNSSEQ,
		STKBN,
		STNO,
		CSTID,
		CSTPOS,
		HHNJTFLG,
		KSNDH
    ) VALUES (
		:knskisymd,
		:sriymd,
		:kntno,
		:kntketflg,
		:knsgrp,
		:skssbt,
		:knsseq,
		:stkbn,
		:stno,
		:cstid,
		:cstpos,
		:hhnjtflg,
		:ksndh
    );
*/

{
#line 292 "Slide.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 292 "Slide.sqc"
  sqlaaloc(2,13,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[13];
#line 292 "Slide.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 292 "Slide.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 292 "Slide.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 292 "Slide.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 292 "Slide.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 292 "Slide.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 292 "Slide.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 292 "Slide.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 292 "Slide.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 292 "Slide.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 292 "Slide.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 292 "Slide.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 292 "Slide.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 292 "Slide.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 292 "Slide.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 292 "Slide.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 292 "Slide.sqc"
      sql_setdlist[5].sqldata = (void*)skssbt;
#line 292 "Slide.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 292 "Slide.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 292 "Slide.sqc"
      sql_setdlist[6].sqldata = (void*)&knsseq;
#line 292 "Slide.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 292 "Slide.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 292 "Slide.sqc"
      sql_setdlist[7].sqldata = (void*)stkbn;
#line 292 "Slide.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 292 "Slide.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 292 "Slide.sqc"
      sql_setdlist[8].sqldata = (void*)&stno;
#line 292 "Slide.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 292 "Slide.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 292 "Slide.sqc"
      sql_setdlist[9].sqldata = (void*)cstid;
#line 292 "Slide.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 292 "Slide.sqc"
      sql_setdlist[10].sqltype = 500; sql_setdlist[10].sqllen = 2;
#line 292 "Slide.sqc"
      sql_setdlist[10].sqldata = (void*)&cstpos;
#line 292 "Slide.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 292 "Slide.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 292 "Slide.sqc"
      sql_setdlist[11].sqldata = (void*)&hhnjtflg;
#line 292 "Slide.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 292 "Slide.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 27;
#line 292 "Slide.sqc"
      sql_setdlist[12].sqldata = (void*)ksndh;
#line 292 "Slide.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 292 "Slide.sqc"
      sqlasetdata(2,0,13,sql_setdlist,0L,0L);
    }
#line 292 "Slide.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 292 "Slide.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 292 "Slide.sqc"
  sqlastop(0L);
}

#line 292 "Slide.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 297 "Slide.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbSlideUpdate()
 *    SLIDE レコードを更新する
 * ■引数
 *    [I]  Slide* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbSlideUpdate( Slide* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, SlideArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 321 "Slide.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 322 "Slide.sqc"


    
/*
EXEC SQL UPDATE SLIDE
    SET (
		KNTKETFLG,
		KNSSEQ,
		STKBN,
		STNO,
		CSTID,
		CSTPOS,
		HHNJTFLG,
		KSNDH
    ) = (
		:kntketflg,
		:knsseq,
		:stkbn,
		:stno,
		:cstid,
		:cstpos,
		:hhnjtflg,
		:ksndh
    ) WHERE
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		KNSGRP         = :knsgrp         AND
		SKSSBT = :skssbt;
*/

{
#line 348 "Slide.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 348 "Slide.sqc"
  sqlaaloc(2,13,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[13];
#line 348 "Slide.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 348 "Slide.sqc"
      sql_setdlist[0].sqldata = (void*)&kntketflg;
#line 348 "Slide.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 348 "Slide.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 348 "Slide.sqc"
      sql_setdlist[1].sqldata = (void*)&knsseq;
#line 348 "Slide.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 348 "Slide.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 348 "Slide.sqc"
      sql_setdlist[2].sqldata = (void*)stkbn;
#line 348 "Slide.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 348 "Slide.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 348 "Slide.sqc"
      sql_setdlist[3].sqldata = (void*)&stno;
#line 348 "Slide.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 348 "Slide.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 348 "Slide.sqc"
      sql_setdlist[4].sqldata = (void*)cstid;
#line 348 "Slide.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 348 "Slide.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 348 "Slide.sqc"
      sql_setdlist[5].sqldata = (void*)&cstpos;
#line 348 "Slide.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 348 "Slide.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 348 "Slide.sqc"
      sql_setdlist[6].sqldata = (void*)&hhnjtflg;
#line 348 "Slide.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 348 "Slide.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 348 "Slide.sqc"
      sql_setdlist[7].sqldata = (void*)ksndh;
#line 348 "Slide.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 348 "Slide.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 348 "Slide.sqc"
      sql_setdlist[8].sqldata = (void*)knskisymd;
#line 348 "Slide.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 348 "Slide.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 348 "Slide.sqc"
      sql_setdlist[9].sqldata = (void*)sriymd;
#line 348 "Slide.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 348 "Slide.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 21;
#line 348 "Slide.sqc"
      sql_setdlist[10].sqldata = (void*)kntno;
#line 348 "Slide.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 348 "Slide.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 348 "Slide.sqc"
      sql_setdlist[11].sqldata = (void*)knsgrp;
#line 348 "Slide.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 348 "Slide.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 3;
#line 348 "Slide.sqc"
      sql_setdlist[12].sqldata = (void*)skssbt;
#line 348 "Slide.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 348 "Slide.sqc"
      sqlasetdata(2,0,13,sql_setdlist,0L,0L);
    }
#line 348 "Slide.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 348 "Slide.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 348 "Slide.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 348 "Slide.sqc"
  sqlastop(0L);
}

#line 348 "Slide.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 353 "Slide.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 357 "Slide.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbSlideDelete()
 *    SLIDE レコードを削除する
 * ■引数
 *    [I]  Slide* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbSlideDelete( Slide* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, SlideArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 381 "Slide.sqc"


    
/*
EXEC SQL DELETE FROM SLIDE
    WHERE
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		KNSGRP         = :knsgrp         AND
		SKSSBT = :skssbt;
*/

{
#line 389 "Slide.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 389 "Slide.sqc"
  sqlaaloc(2,5,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 389 "Slide.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 389 "Slide.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 389 "Slide.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 389 "Slide.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 389 "Slide.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 389 "Slide.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 389 "Slide.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 389 "Slide.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 389 "Slide.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 389 "Slide.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 389 "Slide.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 389 "Slide.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 389 "Slide.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 3;
#line 389 "Slide.sqc"
      sql_setdlist[4].sqldata = (void*)skssbt;
#line 389 "Slide.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 389 "Slide.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 389 "Slide.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 389 "Slide.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 389 "Slide.sqc"
  sqlastop(0L);
}

#line 389 "Slide.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 394 "Slide.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
