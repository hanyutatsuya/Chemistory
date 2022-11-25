static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,68,66,87,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,55,53,90,85,83,69,82,32,0,0,0,0,0,0,0,0,
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


#line 1 "Usermst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Usermst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Usermst.h"
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


#line 24 "Usermst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Usermst.sqc"

	char    userid[9];
	char    cardid[31];
	char    pswd[11];
	char    usernm[21];
	char    oldpswd[111];
	char    pswdykkgn[11];
	char    logindh[27];
	char    loginykkgn[11];
	char    seccd[3];
	char    sykiskbn;
	char    sykindh[27];
	char    rnrdelflg;
	char    staymd[11];
	char    endymd[11];
	char    trkymd[11];
	char    hnkymd[11];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 46 "Usermst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Usermst

BmlDMMInfo	UsermstArray[] = {
	DMM_SSTRING( userid ),
	DMM_SSTRING( cardid ),
	DMM_SSTRING( pswd ),
	DMM_SSTRING( usernm ),
	DMM_SSTRING( oldpswd ),
	DMM_SDATE( pswdykkgn ),
	DMM_STIMESTAMP( logindh ),
	DMM_SDATE( loginykkgn ),
	DMM_SSTRING( seccd ),
	DMM_SCHAR( sykiskbn ),
	DMM_STIMESTAMP( sykindh ),
	DMM_SCHAR( rnrdelflg ),
	DMM_SDATE( staymd ),
	DMM_SDATE( endymd ),
	DMM_SDATE( trkymd ),
	DMM_SDATE( hnkymd ),
	DMM_NULL
};

/******************************************************************************
 * ZdbUsermstSelectAll()
 *    USERMST レコード全件取得
 * ■引数
 *    [O]  Usermst** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbUsermstSelectAll( Usermst** arrayOut, int* numOut )
{
    Usermst*    array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 90 "Usermst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		USERID,
		CARDID,
		PSWD,
		USERNM,
		OLDPSWD,
		PSWDYKKGN,
		LOGINDH,
		LOGINYKKGN,
		SECCD,
		SYKISKBN,
		SYKINDH,
		RNRDELFLG,
		STAYMD,
		ENDYMD,
		TRKYMD,
		HNKYMD
    FROM
        USERMST FOR READ ONLY;
*/

#line 111 "Usermst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 113 "Usermst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 113 "Usermst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 113 "Usermst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 113 "Usermst.sqc"
  sqlastop(0L);
}

#line 113 "Usermst.sqc"


    while( 1 ) {
        Usermst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:userid,
			:cardid,
			:pswd,
			:usernm,
			:oldpswd,
			:pswdykkgn,
			:logindh,
			:loginykkgn,
			:seccd,
			:sykiskbn,
			:sykindh,
			:rnrdelflg,
			:staymd,
			:endymd,
			:trkymd,
			:hnkymd;
*/

{
#line 134 "Usermst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 134 "Usermst.sqc"
  sqlaaloc(3,16,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[16];
#line 134 "Usermst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 9;
#line 134 "Usermst.sqc"
      sql_setdlist[0].sqldata = (void*)userid;
#line 134 "Usermst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 134 "Usermst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 31;
#line 134 "Usermst.sqc"
      sql_setdlist[1].sqldata = (void*)cardid;
#line 134 "Usermst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 134 "Usermst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 134 "Usermst.sqc"
      sql_setdlist[2].sqldata = (void*)pswd;
#line 134 "Usermst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 134 "Usermst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 21;
#line 134 "Usermst.sqc"
      sql_setdlist[3].sqldata = (void*)usernm;
#line 134 "Usermst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 134 "Usermst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 111;
#line 134 "Usermst.sqc"
      sql_setdlist[4].sqldata = (void*)oldpswd;
#line 134 "Usermst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 134 "Usermst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 134 "Usermst.sqc"
      sql_setdlist[5].sqldata = (void*)pswdykkgn;
#line 134 "Usermst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 134 "Usermst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 134 "Usermst.sqc"
      sql_setdlist[6].sqldata = (void*)logindh;
#line 134 "Usermst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 134 "Usermst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 134 "Usermst.sqc"
      sql_setdlist[7].sqldata = (void*)loginykkgn;
#line 134 "Usermst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 134 "Usermst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 3;
#line 134 "Usermst.sqc"
      sql_setdlist[8].sqldata = (void*)seccd;
#line 134 "Usermst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 134 "Usermst.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 134 "Usermst.sqc"
      sql_setdlist[9].sqldata = (void*)&sykiskbn;
#line 134 "Usermst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 134 "Usermst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 27;
#line 134 "Usermst.sqc"
      sql_setdlist[10].sqldata = (void*)sykindh;
#line 134 "Usermst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 134 "Usermst.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 134 "Usermst.sqc"
      sql_setdlist[11].sqldata = (void*)&rnrdelflg;
#line 134 "Usermst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 134 "Usermst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 134 "Usermst.sqc"
      sql_setdlist[12].sqldata = (void*)staymd;
#line 134 "Usermst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 134 "Usermst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 134 "Usermst.sqc"
      sql_setdlist[13].sqldata = (void*)endymd;
#line 134 "Usermst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 134 "Usermst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 11;
#line 134 "Usermst.sqc"
      sql_setdlist[14].sqldata = (void*)trkymd;
#line 134 "Usermst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 134 "Usermst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 11;
#line 134 "Usermst.sqc"
      sql_setdlist[15].sqldata = (void*)hnkymd;
#line 134 "Usermst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 134 "Usermst.sqc"
      sqlasetdata(3,0,16,sql_setdlist,0L,0L);
    }
#line 134 "Usermst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 134 "Usermst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 134 "Usermst.sqc"
  sqlastop(0L);
}

#line 134 "Usermst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Usermst*)ZbmlRealloc( array,
                                    sizeof( Usermst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Usermst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, UsermstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 149 "Usermst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 149 "Usermst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 149 "Usermst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 149 "Usermst.sqc"
  sqlastop(0L);
}

#line 149 "Usermst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 157 "Usermst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbUsermstSelectKey()
 *    USERMST レコードKey条件取得
 * ■引数
 *    [I]  Usermst* pKey       取得するレコードのキー
 *    [O]  Usermst** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbUsermstSelectKey( Usermst* pKey, Usermst** arrayOut, int* numOut )
{
    Usermst*    array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, UsermstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 183 "Usermst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		USERID,
		CARDID,
		PSWD,
		USERNM,
		OLDPSWD,
		PSWDYKKGN,
		LOGINDH,
		LOGINYKKGN,
		SECCD,
		SYKISKBN,
		SYKINDH,
		RNRDELFLG,
		STAYMD,
		ENDYMD,
		TRKYMD,
		HNKYMD
    FROM
        USERMST
    WHERE
		USERID = :userid AND
		STAYMD <= :staymd FOR READ ONLY;
*/

#line 207 "Usermst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 209 "Usermst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 209 "Usermst.sqc"
  sqlaaloc(2,2,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 209 "Usermst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 9;
#line 209 "Usermst.sqc"
      sql_setdlist[0].sqldata = (void*)userid;
#line 209 "Usermst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 209 "Usermst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 209 "Usermst.sqc"
      sql_setdlist[1].sqldata = (void*)staymd;
#line 209 "Usermst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 209 "Usermst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 209 "Usermst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 209 "Usermst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 209 "Usermst.sqc"
  sqlastop(0L);
}

#line 209 "Usermst.sqc"


    while( 1 ) {
        Usermst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:userid,
			:cardid,
			:pswd,
			:usernm,
			:oldpswd,
			:pswdykkgn,
			:logindh,
			:loginykkgn,
			:seccd,
			:sykiskbn,
			:sykindh,
			:rnrdelflg,
			:staymd,
			:endymd,
			:trkymd,
			:hnkymd;
*/

{
#line 230 "Usermst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 230 "Usermst.sqc"
  sqlaaloc(3,16,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[16];
#line 230 "Usermst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 9;
#line 230 "Usermst.sqc"
      sql_setdlist[0].sqldata = (void*)userid;
#line 230 "Usermst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 230 "Usermst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 31;
#line 230 "Usermst.sqc"
      sql_setdlist[1].sqldata = (void*)cardid;
#line 230 "Usermst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 230 "Usermst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 230 "Usermst.sqc"
      sql_setdlist[2].sqldata = (void*)pswd;
#line 230 "Usermst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 230 "Usermst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 21;
#line 230 "Usermst.sqc"
      sql_setdlist[3].sqldata = (void*)usernm;
#line 230 "Usermst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 230 "Usermst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 111;
#line 230 "Usermst.sqc"
      sql_setdlist[4].sqldata = (void*)oldpswd;
#line 230 "Usermst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 230 "Usermst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 230 "Usermst.sqc"
      sql_setdlist[5].sqldata = (void*)pswdykkgn;
#line 230 "Usermst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 230 "Usermst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 230 "Usermst.sqc"
      sql_setdlist[6].sqldata = (void*)logindh;
#line 230 "Usermst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 230 "Usermst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 230 "Usermst.sqc"
      sql_setdlist[7].sqldata = (void*)loginykkgn;
#line 230 "Usermst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 230 "Usermst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 3;
#line 230 "Usermst.sqc"
      sql_setdlist[8].sqldata = (void*)seccd;
#line 230 "Usermst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 230 "Usermst.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 230 "Usermst.sqc"
      sql_setdlist[9].sqldata = (void*)&sykiskbn;
#line 230 "Usermst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 230 "Usermst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 27;
#line 230 "Usermst.sqc"
      sql_setdlist[10].sqldata = (void*)sykindh;
#line 230 "Usermst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 230 "Usermst.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 230 "Usermst.sqc"
      sql_setdlist[11].sqldata = (void*)&rnrdelflg;
#line 230 "Usermst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 230 "Usermst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 230 "Usermst.sqc"
      sql_setdlist[12].sqldata = (void*)staymd;
#line 230 "Usermst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 230 "Usermst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 230 "Usermst.sqc"
      sql_setdlist[13].sqldata = (void*)endymd;
#line 230 "Usermst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 230 "Usermst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 11;
#line 230 "Usermst.sqc"
      sql_setdlist[14].sqldata = (void*)trkymd;
#line 230 "Usermst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 230 "Usermst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 11;
#line 230 "Usermst.sqc"
      sql_setdlist[15].sqldata = (void*)hnkymd;
#line 230 "Usermst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 230 "Usermst.sqc"
      sqlasetdata(3,0,16,sql_setdlist,0L,0L);
    }
#line 230 "Usermst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 230 "Usermst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 230 "Usermst.sqc"
  sqlastop(0L);
}

#line 230 "Usermst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Usermst*)ZbmlRealloc( array,
                                    sizeof( Usermst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Usermst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, UsermstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 245 "Usermst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 245 "Usermst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 245 "Usermst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 245 "Usermst.sqc"
  sqlastop(0L);
}

#line 245 "Usermst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 253 "Usermst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbUsermstInsert()
 *    USERMST レコードを挿入する
 * ■引数
 *    [I]  Usermst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbUsermstInsert( Usermst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, UsermstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 276 "Usermst.sqc"


    
/*
EXEC SQL INSERT INTO USERMST
    (
		USERID,
		CARDID,
		PSWD,
		USERNM,
		OLDPSWD,
		PSWDYKKGN,
		LOGINDH,
		LOGINYKKGN,
		SECCD,
		SYKISKBN,
		SYKINDH,
		RNRDELFLG,
		STAYMD,
		ENDYMD,
		TRKYMD,
		HNKYMD
    ) VALUES (
		:userid,
		:cardid,
		:pswd,
		:usernm,
		:oldpswd,
		:pswdykkgn,
		:logindh,
		:loginykkgn,
		:seccd,
		:sykiskbn,
		:sykindh,
		:rnrdelflg,
		:staymd,
		:endymd,
		:trkymd,
		:hnkymd
    );
*/

{
#line 313 "Usermst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 313 "Usermst.sqc"
  sqlaaloc(2,16,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[16];
#line 313 "Usermst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 9;
#line 313 "Usermst.sqc"
      sql_setdlist[0].sqldata = (void*)userid;
#line 313 "Usermst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 313 "Usermst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 31;
#line 313 "Usermst.sqc"
      sql_setdlist[1].sqldata = (void*)cardid;
#line 313 "Usermst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 313 "Usermst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 313 "Usermst.sqc"
      sql_setdlist[2].sqldata = (void*)pswd;
#line 313 "Usermst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 313 "Usermst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 21;
#line 313 "Usermst.sqc"
      sql_setdlist[3].sqldata = (void*)usernm;
#line 313 "Usermst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 313 "Usermst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 111;
#line 313 "Usermst.sqc"
      sql_setdlist[4].sqldata = (void*)oldpswd;
#line 313 "Usermst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 313 "Usermst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 313 "Usermst.sqc"
      sql_setdlist[5].sqldata = (void*)pswdykkgn;
#line 313 "Usermst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 313 "Usermst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 313 "Usermst.sqc"
      sql_setdlist[6].sqldata = (void*)logindh;
#line 313 "Usermst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 313 "Usermst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 313 "Usermst.sqc"
      sql_setdlist[7].sqldata = (void*)loginykkgn;
#line 313 "Usermst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 313 "Usermst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 3;
#line 313 "Usermst.sqc"
      sql_setdlist[8].sqldata = (void*)seccd;
#line 313 "Usermst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 313 "Usermst.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 313 "Usermst.sqc"
      sql_setdlist[9].sqldata = (void*)&sykiskbn;
#line 313 "Usermst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 313 "Usermst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 27;
#line 313 "Usermst.sqc"
      sql_setdlist[10].sqldata = (void*)sykindh;
#line 313 "Usermst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 313 "Usermst.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 313 "Usermst.sqc"
      sql_setdlist[11].sqldata = (void*)&rnrdelflg;
#line 313 "Usermst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 313 "Usermst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 313 "Usermst.sqc"
      sql_setdlist[12].sqldata = (void*)staymd;
#line 313 "Usermst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 313 "Usermst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 313 "Usermst.sqc"
      sql_setdlist[13].sqldata = (void*)endymd;
#line 313 "Usermst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 313 "Usermst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 11;
#line 313 "Usermst.sqc"
      sql_setdlist[14].sqldata = (void*)trkymd;
#line 313 "Usermst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 313 "Usermst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 11;
#line 313 "Usermst.sqc"
      sql_setdlist[15].sqldata = (void*)hnkymd;
#line 313 "Usermst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 313 "Usermst.sqc"
      sqlasetdata(2,0,16,sql_setdlist,0L,0L);
    }
#line 313 "Usermst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 313 "Usermst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 313 "Usermst.sqc"
  sqlastop(0L);
}

#line 313 "Usermst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 318 "Usermst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbUsermstUpdate()
 *    USERMST レコードを更新する
 * ■引数
 *    [I]  Usermst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbUsermstUpdate( Usermst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, UsermstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 342 "Usermst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 343 "Usermst.sqc"


    
/*
EXEC SQL UPDATE USERMST
    SET (
		CARDID,
		PSWD,
		USERNM,
		OLDPSWD,
		PSWDYKKGN,
		LOGINDH,
		LOGINYKKGN,
		SECCD,
		SYKISKBN,
		SYKINDH,
		RNRDELFLG,
		ENDYMD,
		TRKYMD,
		HNKYMD
    ) = (
		:cardid,
		:pswd,
		:usernm,
		:oldpswd,
		:pswdykkgn,
		:logindh,
		:loginykkgn,
		:seccd,
		:sykiskbn,
		:sykindh,
		:rnrdelflg,
		:endymd,
		:trkymd,
		:hnkymd
    ) WHERE
		USERID = :userid AND
		STAYMD = :staymd;
*/

{
#line 378 "Usermst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 378 "Usermst.sqc"
  sqlaaloc(2,16,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[16];
#line 378 "Usermst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 31;
#line 378 "Usermst.sqc"
      sql_setdlist[0].sqldata = (void*)cardid;
#line 378 "Usermst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 378 "Usermst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 378 "Usermst.sqc"
      sql_setdlist[1].sqldata = (void*)pswd;
#line 378 "Usermst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 378 "Usermst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 378 "Usermst.sqc"
      sql_setdlist[2].sqldata = (void*)usernm;
#line 378 "Usermst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 378 "Usermst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 111;
#line 378 "Usermst.sqc"
      sql_setdlist[3].sqldata = (void*)oldpswd;
#line 378 "Usermst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 378 "Usermst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 378 "Usermst.sqc"
      sql_setdlist[4].sqldata = (void*)pswdykkgn;
#line 378 "Usermst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 378 "Usermst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 27;
#line 378 "Usermst.sqc"
      sql_setdlist[5].sqldata = (void*)logindh;
#line 378 "Usermst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 378 "Usermst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 378 "Usermst.sqc"
      sql_setdlist[6].sqldata = (void*)loginykkgn;
#line 378 "Usermst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 378 "Usermst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 378 "Usermst.sqc"
      sql_setdlist[7].sqldata = (void*)seccd;
#line 378 "Usermst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 378 "Usermst.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 378 "Usermst.sqc"
      sql_setdlist[8].sqldata = (void*)&sykiskbn;
#line 378 "Usermst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 378 "Usermst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 378 "Usermst.sqc"
      sql_setdlist[9].sqldata = (void*)sykindh;
#line 378 "Usermst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 378 "Usermst.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 378 "Usermst.sqc"
      sql_setdlist[10].sqldata = (void*)&rnrdelflg;
#line 378 "Usermst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 378 "Usermst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 378 "Usermst.sqc"
      sql_setdlist[11].sqldata = (void*)endymd;
#line 378 "Usermst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 378 "Usermst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 378 "Usermst.sqc"
      sql_setdlist[12].sqldata = (void*)trkymd;
#line 378 "Usermst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 378 "Usermst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 378 "Usermst.sqc"
      sql_setdlist[13].sqldata = (void*)hnkymd;
#line 378 "Usermst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 378 "Usermst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 9;
#line 378 "Usermst.sqc"
      sql_setdlist[14].sqldata = (void*)userid;
#line 378 "Usermst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 378 "Usermst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 11;
#line 378 "Usermst.sqc"
      sql_setdlist[15].sqldata = (void*)staymd;
#line 378 "Usermst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 378 "Usermst.sqc"
      sqlasetdata(2,0,16,sql_setdlist,0L,0L);
    }
#line 378 "Usermst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 378 "Usermst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 378 "Usermst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 378 "Usermst.sqc"
  sqlastop(0L);
}

#line 378 "Usermst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 383 "Usermst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 387 "Usermst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbUsermstDelete()
 *    USERMST レコードを削除する
 * ■引数
 *    [I]  Usermst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbUsermstDelete( Usermst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, UsermstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 411 "Usermst.sqc"


    
/*
EXEC SQL DELETE FROM USERMST
    WHERE
		USERID = :userid AND
		STAYMD = :staymd;
*/

{
#line 416 "Usermst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 416 "Usermst.sqc"
  sqlaaloc(2,2,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 416 "Usermst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 9;
#line 416 "Usermst.sqc"
      sql_setdlist[0].sqldata = (void*)userid;
#line 416 "Usermst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 416 "Usermst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 416 "Usermst.sqc"
      sql_setdlist[1].sqldata = (void*)staymd;
#line 416 "Usermst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 416 "Usermst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 416 "Usermst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 416 "Usermst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 416 "Usermst.sqc"
  sqlastop(0L);
}

#line 416 "Usermst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 421 "Usermst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
