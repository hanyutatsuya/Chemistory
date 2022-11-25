static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,120,65,119,85,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,65,50,48,53,78,73,78,83,0,0,0,0,0,0,0,0,
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


#line 1 "A205ninsiki.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： A205ninsiki.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "A205ninsiki.h"
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


#line 24 "A205ninsiki.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "A205ninsiki.sqc"

	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    sriymd[11];
	char    kntno[14];
	char    kntketflg;
	char    chkmj[5];
	char    asyrckid[11];
	short   asyrckpos;
	char    id2[11];
	short   id2pos;
	char    id3[11];
	short   id3pos;
	char    fuksuhn;
	char    ksndh[27];
	char    trkdh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 47 "A205ninsiki.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Ninsiki

BmlDMMInfo	NinsikiArray[] = {
	DMM_SDATE( utkymd ),
	DMM_SSTRING( irino ),
	DMM_SCHAR( iriketflg ),
	DMM_SSHORT( zssdino ),
	DMM_SDATE( sriymd ),
	DMM_SSTRING( kntno ),
	DMM_SCHAR( kntketflg ),
	DMM_SSTRING( chkmj ),
	DMM_SSTRING( asyrckid ),
	DMM_SSHORT( asyrckpos ),
	DMM_SSTRING( id2 ),
	DMM_SSHORT( id2pos ),
	DMM_SSTRING( id3 ),
	DMM_SSHORT( id3pos ),
	DMM_SCHAR( fuksuhn ),
	DMM_STIMESTAMP( ksndh ),
	DMM_STIMESTAMP( trkdh ),
	DMM_NULL
};

/******************************************************************************
 * ABunNnskIns()
 *    NINSIKI レコードを挿入する
 * ■引数
 *    [I]  Ninsiki* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ABunNnskIns( Ninsiki* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, NinsikiArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 95 "A205ninsiki.sqc"


    
/*
EXEC SQL INSERT INTO NINSIKI
    (
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		CHKMJ,
		ASYRCKID,
		ASYRCKPOS,
		ID2,
		ID2POS,
		ID3,
		ID3POS,
		FUKSUHN,
		KSNDH,
		TRKDH
    ) VALUES (
		:utkymd,
		:irino,
		:iriketflg,
		:zssdino,
		:sriymd,
		:kntno,
		:kntketflg,
		:chkmj,
		:asyrckid,
		:asyrckpos,
		:id2,
		:id2pos,
		:id3,
		:id3pos,
		:fuksuhn,
		CURRENT TIMESTAMP,
		CURRENT TIMESTAMP
    );
*/

{
#line 134 "A205ninsiki.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 134 "A205ninsiki.sqc"
  sqlaaloc(2,15,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[15];
#line 134 "A205ninsiki.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[4].sqldata = (void*)sriymd;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 14;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[5].sqldata = (void*)kntno;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[6].sqldata = (void*)&kntketflg;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 5;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[7].sqldata = (void*)chkmj;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[8].sqldata = (void*)asyrckid;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[9].sqldata = (void*)&asyrckpos;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[10].sqldata = (void*)id2;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[11].sqldata = (void*)&id2pos;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[12].sqldata = (void*)id3;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[13].sqldata = (void*)&id3pos;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[14].sqldata = (void*)&fuksuhn;
#line 134 "A205ninsiki.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 134 "A205ninsiki.sqc"
      sqlasetdata(2,0,15,sql_setdlist,0L,0L);
    }
#line 134 "A205ninsiki.sqc"
  sqlacall((unsigned short)24,1,2,0,0L);
#line 134 "A205ninsiki.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 134 "A205ninsiki.sqc"
  sqlastop(0L);
}

#line 134 "A205ninsiki.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 139 "A205ninsiki.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ABunNinUp()
 *    NINSIKI レコードを更新する
 * ■引数
 *    [I]  Ninsiki* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ABunNinUp( Ninsiki* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, NinsikiArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 163 "A205ninsiki.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 164 "A205ninsiki.sqc"


    
/*
EXEC SQL UPDATE NINSIKI
    SET (
		FUKSUHN,
		KSNDH
    ) = (
		'W',
		CURRENT TIMESTAMP
    ) WHERE
		KNTNO = :kntno AND
		IRINO = :irino AND
		ZSSDINO = :zssdino AND
		SRIYMD = :sriymd AND
		UTKYMD = :utkymd;
*/

{
#line 178 "A205ninsiki.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 178 "A205ninsiki.sqc"
  sqlaaloc(2,5,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 178 "A205ninsiki.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 14;
#line 178 "A205ninsiki.sqc"
      sql_setdlist[0].sqldata = (void*)kntno;
#line 178 "A205ninsiki.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 178 "A205ninsiki.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 178 "A205ninsiki.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 178 "A205ninsiki.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 178 "A205ninsiki.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 178 "A205ninsiki.sqc"
      sql_setdlist[2].sqldata = (void*)&zssdino;
#line 178 "A205ninsiki.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 178 "A205ninsiki.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 178 "A205ninsiki.sqc"
      sql_setdlist[3].sqldata = (void*)sriymd;
#line 178 "A205ninsiki.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 178 "A205ninsiki.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 178 "A205ninsiki.sqc"
      sql_setdlist[4].sqldata = (void*)utkymd;
#line 178 "A205ninsiki.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 178 "A205ninsiki.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 178 "A205ninsiki.sqc"
  sqlacall((unsigned short)24,2,2,0,0L);
#line 178 "A205ninsiki.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 178 "A205ninsiki.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 178 "A205ninsiki.sqc"
  sqlastop(0L);
}

#line 178 "A205ninsiki.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 183 "A205ninsiki.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 187 "A205ninsiki.sqc"

    return sqlca.sqlcode;
}
long ABunNinUpAll( Ninsiki* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, NinsikiArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 198 "A205ninsiki.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 199 "A205ninsiki.sqc"


    
/*
EXEC SQL UPDATE NINSIKI
    SET (
		FUKSUHN,
		KSNDH
    ) = (
		'W',
		CURRENT TIMESTAMP
    ) WHERE
		IRINO = :irino AND
		ZSSDINO = :zssdino AND
		SRIYMD = :sriymd AND
		UTKYMD = :utkymd;
*/

{
#line 212 "A205ninsiki.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 212 "A205ninsiki.sqc"
  sqlaaloc(2,4,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 212 "A205ninsiki.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 12;
#line 212 "A205ninsiki.sqc"
      sql_setdlist[0].sqldata = (void*)irino;
#line 212 "A205ninsiki.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 212 "A205ninsiki.sqc"
      sql_setdlist[1].sqltype = 500; sql_setdlist[1].sqllen = 2;
#line 212 "A205ninsiki.sqc"
      sql_setdlist[1].sqldata = (void*)&zssdino;
#line 212 "A205ninsiki.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 212 "A205ninsiki.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 212 "A205ninsiki.sqc"
      sql_setdlist[2].sqldata = (void*)sriymd;
#line 212 "A205ninsiki.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 212 "A205ninsiki.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 212 "A205ninsiki.sqc"
      sql_setdlist[3].sqldata = (void*)utkymd;
#line 212 "A205ninsiki.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 212 "A205ninsiki.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 212 "A205ninsiki.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 212 "A205ninsiki.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 212 "A205ninsiki.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 212 "A205ninsiki.sqc"
  sqlastop(0L);
}

#line 212 "A205ninsiki.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 217 "A205ninsiki.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 221 "A205ninsiki.sqc"

    return sqlca.sqlcode;
}

// 3.02 ADD STA
/******************************************************************************
 * ANnskUpdate()
 *    NINSIKI レコードを更新する
 * ■引数
 *    [I]  Ninsiki* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ANnskUpdate( Ninsiki* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, NinsikiArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 246 "A205ninsiki.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 247 "A205ninsiki.sqc"


    
/*
EXEC SQL UPDATE NINSIKI
    SET (
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		CHKMJ,
		ASYRCKID,
		ASYRCKPOS,
		ID2,
		ID2POS,
		ID3,
		ID3POS,
		FUKSUHN,
		KSNDH
--		TRKDH			// 登録日時はUPDATE対象外
    ) = (
		:utkymd,
		:irino,
		:iriketflg,
		:zssdino,
		:sriymd,
		:kntno,
		:kntketflg,
		:chkmj,
		:asyrckid,
		:asyrckpos,
		:id2,
		:id2pos,
		:id3,
		:id3pos,
		:fuksuhn,
		CURRENT TIMESTAMP
--		CURRENT TIMESTAMP
    ) WHERE
		KNTNO = :kntno AND
		IRINO = :irino AND
		ZSSDINO = :zssdino AND
		SRIYMD = :sriymd AND
		UTKYMD = :utkymd;
*/

{
#line 291 "A205ninsiki.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 291 "A205ninsiki.sqc"
  sqlaaloc(2,20,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[20];
#line 291 "A205ninsiki.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[4].sqldata = (void*)sriymd;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 14;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[5].sqldata = (void*)kntno;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[6].sqldata = (void*)&kntketflg;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 5;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[7].sqldata = (void*)chkmj;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[8].sqldata = (void*)asyrckid;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[9].sqldata = (void*)&asyrckpos;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[10].sqldata = (void*)id2;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[11].sqldata = (void*)&id2pos;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[12].sqldata = (void*)id3;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[13].sqldata = (void*)&id3pos;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[14].sqldata = (void*)&fuksuhn;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 14;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[15].sqldata = (void*)kntno;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 12;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[16].sqldata = (void*)irino;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[17].sqltype = 500; sql_setdlist[17].sqllen = 2;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[17].sqldata = (void*)&zssdino;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 11;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[18].sqldata = (void*)sriymd;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 11;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[19].sqldata = (void*)utkymd;
#line 291 "A205ninsiki.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 291 "A205ninsiki.sqc"
      sqlasetdata(2,0,20,sql_setdlist,0L,0L);
    }
#line 291 "A205ninsiki.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 291 "A205ninsiki.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 291 "A205ninsiki.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 291 "A205ninsiki.sqc"
  sqlastop(0L);
}

#line 291 "A205ninsiki.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 296 "A205ninsiki.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 300 "A205ninsiki.sqc"

    return sqlca.sqlcode;
}
// 3.02 ADD END
/******************************************************************************
 * ABunNinSelKey()
 *    NINSIKI レコードKey条件取得
 * ■引数
 *    [I]  Ninsiki* pKey       取得するレコードのキー
 *    [O]  Ninsiki** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ABunNinSelKey( Ninsiki* pKey, Ninsiki** arrayOut, int* numOut )
{
    Ninsiki*    array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, NinsikiArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 327 "A205ninsiki.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		CHKMJ,
		ASYRCKID,
		ASYRCKPOS,
		ID2,
		ID2POS,
		ID3,
		ID3POS,
		FUKSUHN,
		KSNDH,
		TRKDH
    FROM
        NINSIKI
    WHERE
		IRINO = :irino AND
		ZSSDINO = :zssdino AND
		SRIYMD = :sriymd AND
		UTKYMD = :utkymd FOR READ ONLY;
*/

#line 354 "A205ninsiki.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 356 "A205ninsiki.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 356 "A205ninsiki.sqc"
  sqlaaloc(2,4,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 356 "A205ninsiki.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 12;
#line 356 "A205ninsiki.sqc"
      sql_setdlist[0].sqldata = (void*)irino;
#line 356 "A205ninsiki.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 356 "A205ninsiki.sqc"
      sql_setdlist[1].sqltype = 500; sql_setdlist[1].sqllen = 2;
#line 356 "A205ninsiki.sqc"
      sql_setdlist[1].sqldata = (void*)&zssdino;
#line 356 "A205ninsiki.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 356 "A205ninsiki.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 356 "A205ninsiki.sqc"
      sql_setdlist[2].sqldata = (void*)sriymd;
#line 356 "A205ninsiki.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 356 "A205ninsiki.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 356 "A205ninsiki.sqc"
      sql_setdlist[3].sqldata = (void*)utkymd;
#line 356 "A205ninsiki.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 356 "A205ninsiki.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 356 "A205ninsiki.sqc"
  sqlacall((unsigned short)26,5,2,0,0L);
#line 356 "A205ninsiki.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 356 "A205ninsiki.sqc"
  sqlastop(0L);
}

#line 356 "A205ninsiki.sqc"


    while( 1 ) {
        Ninsiki* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:sriymd,
			:kntno,
			:kntketflg,
			:chkmj,
			:asyrckid,
			:asyrckpos,
			:id2,
			:id2pos,
			:id3,
			:id3pos,
			:fuksuhn,
			:ksndh,
			:trkdh;
*/

{
#line 378 "A205ninsiki.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 378 "A205ninsiki.sqc"
  sqlaaloc(3,17,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[17];
#line 378 "A205ninsiki.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[4].sqldata = (void*)sriymd;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 14;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[5].sqldata = (void*)kntno;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[6].sqldata = (void*)&kntketflg;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 5;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[7].sqldata = (void*)chkmj;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[8].sqldata = (void*)asyrckid;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[9].sqldata = (void*)&asyrckpos;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[10].sqldata = (void*)id2;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[11].sqldata = (void*)&id2pos;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[12].sqldata = (void*)id3;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[13].sqldata = (void*)&id3pos;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[14].sqldata = (void*)&fuksuhn;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[15].sqldata = (void*)ksndh;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 27;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[16].sqldata = (void*)trkdh;
#line 378 "A205ninsiki.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 378 "A205ninsiki.sqc"
      sqlasetdata(3,0,17,sql_setdlist,0L,0L);
    }
#line 378 "A205ninsiki.sqc"
  sqlacall((unsigned short)25,5,0,3,0L);
#line 378 "A205ninsiki.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 378 "A205ninsiki.sqc"
  sqlastop(0L);
}

#line 378 "A205ninsiki.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Ninsiki*)ZbmlRealloc( array,
                                    sizeof( Ninsiki ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Ninsiki ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, NinsikiArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 393 "A205ninsiki.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 393 "A205ninsiki.sqc"
  sqlacall((unsigned short)20,5,0,0,0L);
#line 393 "A205ninsiki.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 393 "A205ninsiki.sqc"
  sqlastop(0L);
}

#line 393 "A205ninsiki.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 401 "A205ninsiki.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
