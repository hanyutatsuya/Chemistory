static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,66,65,85,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,52,52,90,75,78,83,71,32,0,0,0,0,0,0,0,0,
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


#line 1 "Knsgmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Knsgmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Knsgmst.h"
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


#line 24 "Knsgmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Knsgmst.sqc"

	char    knsgrp[17];
	char    knsgrpnm[41];
	char    knsgrprs[21];
	char    seccd[3];
	char    knshokbn[41];
	char    knssbt;
	char    bgroup;
	char    unyokbn;
	short   seqkthsok;
	short   seqkthsng;
	char    wsssksok;
	char    wsssksng;
	short   minryo;
	short   maxryo;
	char    skitray[11];
	char    mbttray[11];
	char    skntray[11];
	char    ssttray[11];
	char    knsyb[8];
	char    ykcd[5];
	char    skiwsid[21];
	char    sknwsid[21];
	char    kkalstid[21];
	char    splblid[21];
	char    lstyb1[21];
	char    lstyb2[21];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 60 "Knsgmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Knsgmst

BmlDMMInfo	KnsgmstArray[] = {
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( knsgrpnm ),
	DMM_SSTRING( knsgrprs ),
	DMM_SSTRING( seccd ),
	DMM_SSTRING( knshokbn ),
	DMM_SCHAR( knssbt ),
	DMM_SCHAR( bgroup ),
	DMM_SCHAR( unyokbn ),
	DMM_SSHORT( seqkthsok ),
	DMM_SSHORT( seqkthsng ),
	DMM_SCHAR( wsssksok ),
	DMM_SCHAR( wsssksng ),
	DMM_SSHORT( minryo ),
	DMM_SSHORT( maxryo ),
	DMM_SSTRING( skitray ),
	DMM_SSTRING( mbttray ),
	DMM_SSTRING( skntray ),
	DMM_SSTRING( ssttray ),
	DMM_SSTRING( knsyb ),
	DMM_SSTRING( ykcd ),
	DMM_SSTRING( skiwsid ),
	DMM_SSTRING( sknwsid ),
	DMM_SSTRING( kkalstid ),
	DMM_SSTRING( splblid ),
	DMM_SSTRING( lstyb1 ),
	DMM_SSTRING( lstyb2 ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKnsgmstSelectAll()
 *    KNSGMST レコード全件取得
 * ■引数
 *    [O]  Knsgmst** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKnsgmstSelectAll( Knsgmst** arrayOut, int* numOut )
{
    Knsgmst*    array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 118 "Knsgmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSGRP,
		KNSGRPNM,
		KNSGRPRS,
		SECCD,
		KNSHOKBN,
		KNSSBT,
		BGROUP,
		UNYOKBN,
		SEQKTHSOK,
		SEQKTHSNG,
		WSSSKSOK,
		WSSSKSNG,
		MINRYO,
		MAXRYO,
		SKITRAY,
		MBTTRAY,
		SKNTRAY,
		SSTTRAY,
		KNSYB,
		YKCD,
		SKIWSID,
		SKNWSID,
		KKALSTID,
		SPLBLID,
		LSTYB1,
		LSTYB2,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        KNSGMST FOR READ ONLY;
*/

#line 153 "Knsgmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 155 "Knsgmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 155 "Knsgmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 155 "Knsgmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 155 "Knsgmst.sqc"
  sqlastop(0L);
}

#line 155 "Knsgmst.sqc"


    while( 1 ) {
        Knsgmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knsgrp,
			:knsgrpnm,
			:knsgrprs,
			:seccd,
			:knshokbn,
			:knssbt,
			:bgroup,
			:unyokbn,
			:seqkthsok,
			:seqkthsng,
			:wsssksok,
			:wsssksng,
			:minryo,
			:maxryo,
			:skitray,
			:mbttray,
			:skntray,
			:ssttray,
			:knsyb,
			:ykcd,
			:skiwsid,
			:sknwsid,
			:kkalstid,
			:splblid,
			:lstyb1,
			:lstyb2,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 190 "Knsgmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 190 "Knsgmst.sqc"
  sqlaaloc(3,30,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[30];
#line 190 "Knsgmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 190 "Knsgmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 190 "Knsgmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 41;
#line 190 "Knsgmst.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrpnm;
#line 190 "Knsgmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 190 "Knsgmst.sqc"
      sql_setdlist[2].sqldata = (void*)knsgrprs;
#line 190 "Knsgmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 190 "Knsgmst.sqc"
      sql_setdlist[3].sqldata = (void*)seccd;
#line 190 "Knsgmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 41;
#line 190 "Knsgmst.sqc"
      sql_setdlist[4].sqldata = (void*)knshokbn;
#line 190 "Knsgmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 190 "Knsgmst.sqc"
      sql_setdlist[5].sqldata = (void*)&knssbt;
#line 190 "Knsgmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 190 "Knsgmst.sqc"
      sql_setdlist[6].sqldata = (void*)&bgroup;
#line 190 "Knsgmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 190 "Knsgmst.sqc"
      sql_setdlist[7].sqldata = (void*)&unyokbn;
#line 190 "Knsgmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 190 "Knsgmst.sqc"
      sql_setdlist[8].sqldata = (void*)&seqkthsok;
#line 190 "Knsgmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 190 "Knsgmst.sqc"
      sql_setdlist[9].sqldata = (void*)&seqkthsng;
#line 190 "Knsgmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 190 "Knsgmst.sqc"
      sql_setdlist[10].sqldata = (void*)&wsssksok;
#line 190 "Knsgmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 190 "Knsgmst.sqc"
      sql_setdlist[11].sqldata = (void*)&wsssksng;
#line 190 "Knsgmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 190 "Knsgmst.sqc"
      sql_setdlist[12].sqldata = (void*)&minryo;
#line 190 "Knsgmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 190 "Knsgmst.sqc"
      sql_setdlist[13].sqldata = (void*)&maxryo;
#line 190 "Knsgmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 11;
#line 190 "Knsgmst.sqc"
      sql_setdlist[14].sqldata = (void*)skitray;
#line 190 "Knsgmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 11;
#line 190 "Knsgmst.sqc"
      sql_setdlist[15].sqldata = (void*)mbttray;
#line 190 "Knsgmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 11;
#line 190 "Knsgmst.sqc"
      sql_setdlist[16].sqldata = (void*)skntray;
#line 190 "Knsgmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 11;
#line 190 "Knsgmst.sqc"
      sql_setdlist[17].sqldata = (void*)ssttray;
#line 190 "Knsgmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 8;
#line 190 "Knsgmst.sqc"
      sql_setdlist[18].sqldata = (void*)knsyb;
#line 190 "Knsgmst.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 5;
#line 190 "Knsgmst.sqc"
      sql_setdlist[19].sqldata = (void*)ykcd;
#line 190 "Knsgmst.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 21;
#line 190 "Knsgmst.sqc"
      sql_setdlist[20].sqldata = (void*)skiwsid;
#line 190 "Knsgmst.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 21;
#line 190 "Knsgmst.sqc"
      sql_setdlist[21].sqldata = (void*)sknwsid;
#line 190 "Knsgmst.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 21;
#line 190 "Knsgmst.sqc"
      sql_setdlist[22].sqldata = (void*)kkalstid;
#line 190 "Knsgmst.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 21;
#line 190 "Knsgmst.sqc"
      sql_setdlist[23].sqldata = (void*)splblid;
#line 190 "Knsgmst.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 21;
#line 190 "Knsgmst.sqc"
      sql_setdlist[24].sqldata = (void*)lstyb1;
#line 190 "Knsgmst.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 21;
#line 190 "Knsgmst.sqc"
      sql_setdlist[25].sqldata = (void*)lstyb2;
#line 190 "Knsgmst.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 11;
#line 190 "Knsgmst.sqc"
      sql_setdlist[26].sqldata = (void*)kaiymd;
#line 190 "Knsgmst.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 11;
#line 190 "Knsgmst.sqc"
      sql_setdlist[27].sqldata = (void*)haiymd;
#line 190 "Knsgmst.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 9;
#line 190 "Knsgmst.sqc"
      sql_setdlist[28].sqldata = (void*)hnktntid;
#line 190 "Knsgmst.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 190 "Knsgmst.sqc"
      sql_setdlist[29].sqldata = (void*)ksndh;
#line 190 "Knsgmst.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 190 "Knsgmst.sqc"
      sqlasetdata(3,0,30,sql_setdlist,0L,0L);
    }
#line 190 "Knsgmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 190 "Knsgmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 190 "Knsgmst.sqc"
  sqlastop(0L);
}

#line 190 "Knsgmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Knsgmst*)ZbmlRealloc( array,
                                    sizeof( Knsgmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Knsgmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KnsgmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 205 "Knsgmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 205 "Knsgmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 205 "Knsgmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 205 "Knsgmst.sqc"
  sqlastop(0L);
}

#line 205 "Knsgmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 213 "Knsgmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKnsgmstSelectKey()
 *    KNSGMST レコードKey条件取得
 * ■引数
 *    [I]  Knsgmst* pKey       取得するレコードのキー
 *    [O]  Knsgmst** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKnsgmstSelectKey( Knsgmst* pKey, Knsgmst** arrayOut, int* numOut )
{
    Knsgmst*    array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KnsgmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 239 "Knsgmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSGRP,
		KNSGRPNM,
		KNSGRPRS,
		SECCD,
		KNSHOKBN,
		KNSSBT,
		BGROUP,
		UNYOKBN,
		SEQKTHSOK,
		SEQKTHSNG,
		WSSSKSOK,
		WSSSKSNG,
		MINRYO,
		MAXRYO,
		SKITRAY,
		MBTTRAY,
		SKNTRAY,
		SSTTRAY,
		KNSYB,
		YKCD,
		SKIWSID,
		SKNWSID,
		KKALSTID,
		SPLBLID,
		LSTYB1,
		LSTYB2,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        KNSGMST
    WHERE
		KNSGRP = :knsgrp AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 277 "Knsgmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 279 "Knsgmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 279 "Knsgmst.sqc"
  sqlaaloc(2,2,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 279 "Knsgmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 279 "Knsgmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 279 "Knsgmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 279 "Knsgmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 279 "Knsgmst.sqc"
      sql_setdlist[1].sqldata = (void*)kaiymd;
#line 279 "Knsgmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 279 "Knsgmst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 279 "Knsgmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 279 "Knsgmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 279 "Knsgmst.sqc"
  sqlastop(0L);
}

#line 279 "Knsgmst.sqc"


    while( 1 ) {
        Knsgmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knsgrp,
			:knsgrpnm,
			:knsgrprs,
			:seccd,
			:knshokbn,
			:knssbt,
			:bgroup,
			:unyokbn,
			:seqkthsok,
			:seqkthsng,
			:wsssksok,
			:wsssksng,
			:minryo,
			:maxryo,
			:skitray,
			:mbttray,
			:skntray,
			:ssttray,
			:knsyb,
			:ykcd,
			:skiwsid,
			:sknwsid,
			:kkalstid,
			:splblid,
			:lstyb1,
			:lstyb2,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 314 "Knsgmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 314 "Knsgmst.sqc"
  sqlaaloc(3,30,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[30];
#line 314 "Knsgmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 314 "Knsgmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 314 "Knsgmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 41;
#line 314 "Knsgmst.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrpnm;
#line 314 "Knsgmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 314 "Knsgmst.sqc"
      sql_setdlist[2].sqldata = (void*)knsgrprs;
#line 314 "Knsgmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 314 "Knsgmst.sqc"
      sql_setdlist[3].sqldata = (void*)seccd;
#line 314 "Knsgmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 41;
#line 314 "Knsgmst.sqc"
      sql_setdlist[4].sqldata = (void*)knshokbn;
#line 314 "Knsgmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 314 "Knsgmst.sqc"
      sql_setdlist[5].sqldata = (void*)&knssbt;
#line 314 "Knsgmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 314 "Knsgmst.sqc"
      sql_setdlist[6].sqldata = (void*)&bgroup;
#line 314 "Knsgmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 314 "Knsgmst.sqc"
      sql_setdlist[7].sqldata = (void*)&unyokbn;
#line 314 "Knsgmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 314 "Knsgmst.sqc"
      sql_setdlist[8].sqldata = (void*)&seqkthsok;
#line 314 "Knsgmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 314 "Knsgmst.sqc"
      sql_setdlist[9].sqldata = (void*)&seqkthsng;
#line 314 "Knsgmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 314 "Knsgmst.sqc"
      sql_setdlist[10].sqldata = (void*)&wsssksok;
#line 314 "Knsgmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 314 "Knsgmst.sqc"
      sql_setdlist[11].sqldata = (void*)&wsssksng;
#line 314 "Knsgmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 314 "Knsgmst.sqc"
      sql_setdlist[12].sqldata = (void*)&minryo;
#line 314 "Knsgmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 314 "Knsgmst.sqc"
      sql_setdlist[13].sqldata = (void*)&maxryo;
#line 314 "Knsgmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 11;
#line 314 "Knsgmst.sqc"
      sql_setdlist[14].sqldata = (void*)skitray;
#line 314 "Knsgmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 11;
#line 314 "Knsgmst.sqc"
      sql_setdlist[15].sqldata = (void*)mbttray;
#line 314 "Knsgmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 11;
#line 314 "Knsgmst.sqc"
      sql_setdlist[16].sqldata = (void*)skntray;
#line 314 "Knsgmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 11;
#line 314 "Knsgmst.sqc"
      sql_setdlist[17].sqldata = (void*)ssttray;
#line 314 "Knsgmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 8;
#line 314 "Knsgmst.sqc"
      sql_setdlist[18].sqldata = (void*)knsyb;
#line 314 "Knsgmst.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 5;
#line 314 "Knsgmst.sqc"
      sql_setdlist[19].sqldata = (void*)ykcd;
#line 314 "Knsgmst.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 21;
#line 314 "Knsgmst.sqc"
      sql_setdlist[20].sqldata = (void*)skiwsid;
#line 314 "Knsgmst.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 21;
#line 314 "Knsgmst.sqc"
      sql_setdlist[21].sqldata = (void*)sknwsid;
#line 314 "Knsgmst.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 21;
#line 314 "Knsgmst.sqc"
      sql_setdlist[22].sqldata = (void*)kkalstid;
#line 314 "Knsgmst.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 21;
#line 314 "Knsgmst.sqc"
      sql_setdlist[23].sqldata = (void*)splblid;
#line 314 "Knsgmst.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 21;
#line 314 "Knsgmst.sqc"
      sql_setdlist[24].sqldata = (void*)lstyb1;
#line 314 "Knsgmst.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 21;
#line 314 "Knsgmst.sqc"
      sql_setdlist[25].sqldata = (void*)lstyb2;
#line 314 "Knsgmst.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 11;
#line 314 "Knsgmst.sqc"
      sql_setdlist[26].sqldata = (void*)kaiymd;
#line 314 "Knsgmst.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 11;
#line 314 "Knsgmst.sqc"
      sql_setdlist[27].sqldata = (void*)haiymd;
#line 314 "Knsgmst.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 9;
#line 314 "Knsgmst.sqc"
      sql_setdlist[28].sqldata = (void*)hnktntid;
#line 314 "Knsgmst.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 314 "Knsgmst.sqc"
      sql_setdlist[29].sqldata = (void*)ksndh;
#line 314 "Knsgmst.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 314 "Knsgmst.sqc"
      sqlasetdata(3,0,30,sql_setdlist,0L,0L);
    }
#line 314 "Knsgmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 314 "Knsgmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 314 "Knsgmst.sqc"
  sqlastop(0L);
}

#line 314 "Knsgmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Knsgmst*)ZbmlRealloc( array,
                                    sizeof( Knsgmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Knsgmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KnsgmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 329 "Knsgmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 329 "Knsgmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 329 "Knsgmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 329 "Knsgmst.sqc"
  sqlastop(0L);
}

#line 329 "Knsgmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 337 "Knsgmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKnsgmstInsert()
 *    KNSGMST レコードを挿入する
 * ■引数
 *    [I]  Knsgmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKnsgmstInsert( Knsgmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KnsgmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 360 "Knsgmst.sqc"


    
/*
EXEC SQL INSERT INTO KNSGMST
    (
		KNSGRP,
		KNSGRPNM,
		KNSGRPRS,
		SECCD,
		KNSHOKBN,
		KNSSBT,
		BGROUP,
		UNYOKBN,
		SEQKTHSOK,
		SEQKTHSNG,
		WSSSKSOK,
		WSSSKSNG,
		MINRYO,
		MAXRYO,
		SKITRAY,
		MBTTRAY,
		SKNTRAY,
		SSTTRAY,
		KNSYB,
		YKCD,
		SKIWSID,
		SKNWSID,
		KKALSTID,
		SPLBLID,
		LSTYB1,
		LSTYB2,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:knsgrp,
		:knsgrpnm,
		:knsgrprs,
		:seccd,
		:knshokbn,
		:knssbt,
		:bgroup,
		:unyokbn,
		:seqkthsok,
		:seqkthsng,
		:wsssksok,
		:wsssksng,
		:minryo,
		:maxryo,
		:skitray,
		:mbttray,
		:skntray,
		:ssttray,
		:knsyb,
		:ykcd,
		:skiwsid,
		:sknwsid,
		:kkalstid,
		:splblid,
		:lstyb1,
		:lstyb2,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 425 "Knsgmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 425 "Knsgmst.sqc"
  sqlaaloc(2,30,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[30];
#line 425 "Knsgmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 425 "Knsgmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 425 "Knsgmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 41;
#line 425 "Knsgmst.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrpnm;
#line 425 "Knsgmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 425 "Knsgmst.sqc"
      sql_setdlist[2].sqldata = (void*)knsgrprs;
#line 425 "Knsgmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 425 "Knsgmst.sqc"
      sql_setdlist[3].sqldata = (void*)seccd;
#line 425 "Knsgmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 41;
#line 425 "Knsgmst.sqc"
      sql_setdlist[4].sqldata = (void*)knshokbn;
#line 425 "Knsgmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 425 "Knsgmst.sqc"
      sql_setdlist[5].sqldata = (void*)&knssbt;
#line 425 "Knsgmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 425 "Knsgmst.sqc"
      sql_setdlist[6].sqldata = (void*)&bgroup;
#line 425 "Knsgmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 425 "Knsgmst.sqc"
      sql_setdlist[7].sqldata = (void*)&unyokbn;
#line 425 "Knsgmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 425 "Knsgmst.sqc"
      sql_setdlist[8].sqldata = (void*)&seqkthsok;
#line 425 "Knsgmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 425 "Knsgmst.sqc"
      sql_setdlist[9].sqldata = (void*)&seqkthsng;
#line 425 "Knsgmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 425 "Knsgmst.sqc"
      sql_setdlist[10].sqldata = (void*)&wsssksok;
#line 425 "Knsgmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 425 "Knsgmst.sqc"
      sql_setdlist[11].sqldata = (void*)&wsssksng;
#line 425 "Knsgmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 425 "Knsgmst.sqc"
      sql_setdlist[12].sqldata = (void*)&minryo;
#line 425 "Knsgmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 425 "Knsgmst.sqc"
      sql_setdlist[13].sqldata = (void*)&maxryo;
#line 425 "Knsgmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 11;
#line 425 "Knsgmst.sqc"
      sql_setdlist[14].sqldata = (void*)skitray;
#line 425 "Knsgmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 11;
#line 425 "Knsgmst.sqc"
      sql_setdlist[15].sqldata = (void*)mbttray;
#line 425 "Knsgmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 11;
#line 425 "Knsgmst.sqc"
      sql_setdlist[16].sqldata = (void*)skntray;
#line 425 "Knsgmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 11;
#line 425 "Knsgmst.sqc"
      sql_setdlist[17].sqldata = (void*)ssttray;
#line 425 "Knsgmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 8;
#line 425 "Knsgmst.sqc"
      sql_setdlist[18].sqldata = (void*)knsyb;
#line 425 "Knsgmst.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 5;
#line 425 "Knsgmst.sqc"
      sql_setdlist[19].sqldata = (void*)ykcd;
#line 425 "Knsgmst.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 21;
#line 425 "Knsgmst.sqc"
      sql_setdlist[20].sqldata = (void*)skiwsid;
#line 425 "Knsgmst.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 21;
#line 425 "Knsgmst.sqc"
      sql_setdlist[21].sqldata = (void*)sknwsid;
#line 425 "Knsgmst.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 21;
#line 425 "Knsgmst.sqc"
      sql_setdlist[22].sqldata = (void*)kkalstid;
#line 425 "Knsgmst.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 21;
#line 425 "Knsgmst.sqc"
      sql_setdlist[23].sqldata = (void*)splblid;
#line 425 "Knsgmst.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 21;
#line 425 "Knsgmst.sqc"
      sql_setdlist[24].sqldata = (void*)lstyb1;
#line 425 "Knsgmst.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 21;
#line 425 "Knsgmst.sqc"
      sql_setdlist[25].sqldata = (void*)lstyb2;
#line 425 "Knsgmst.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 11;
#line 425 "Knsgmst.sqc"
      sql_setdlist[26].sqldata = (void*)kaiymd;
#line 425 "Knsgmst.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 11;
#line 425 "Knsgmst.sqc"
      sql_setdlist[27].sqldata = (void*)haiymd;
#line 425 "Knsgmst.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 9;
#line 425 "Knsgmst.sqc"
      sql_setdlist[28].sqldata = (void*)hnktntid;
#line 425 "Knsgmst.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 425 "Knsgmst.sqc"
      sql_setdlist[29].sqldata = (void*)ksndh;
#line 425 "Knsgmst.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 425 "Knsgmst.sqc"
      sqlasetdata(2,0,30,sql_setdlist,0L,0L);
    }
#line 425 "Knsgmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 425 "Knsgmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 425 "Knsgmst.sqc"
  sqlastop(0L);
}

#line 425 "Knsgmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 430 "Knsgmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKnsgmstUpdate()
 *    KNSGMST レコードを更新する
 * ■引数
 *    [I]  Knsgmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKnsgmstUpdate( Knsgmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KnsgmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 454 "Knsgmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 455 "Knsgmst.sqc"


    
/*
EXEC SQL UPDATE KNSGMST
    SET (
		KNSGRPNM,
		KNSGRPRS,
		SECCD,
		KNSHOKBN,
		KNSSBT,
		BGROUP,
		UNYOKBN,
		SEQKTHSOK,
		SEQKTHSNG,
		WSSSKSOK,
		WSSSKSNG,
		MINRYO,
		MAXRYO,
		SKITRAY,
		MBTTRAY,
		SKNTRAY,
		SSTTRAY,
		KNSYB,
		YKCD,
		SKIWSID,
		SKNWSID,
		KKALSTID,
		SPLBLID,
		LSTYB1,
		LSTYB2,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:knsgrpnm,
		:knsgrprs,
		:seccd,
		:knshokbn,
		:knssbt,
		:bgroup,
		:unyokbn,
		:seqkthsok,
		:seqkthsng,
		:wsssksok,
		:wsssksng,
		:minryo,
		:maxryo,
		:skitray,
		:mbttray,
		:skntray,
		:ssttray,
		:knsyb,
		:ykcd,
		:skiwsid,
		:sknwsid,
		:kkalstid,
		:splblid,
		:lstyb1,
		:lstyb2,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		KNSGRP = :knsgrp AND
		KAIYMD = :kaiymd;
*/

{
#line 518 "Knsgmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 518 "Knsgmst.sqc"
  sqlaaloc(2,30,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[30];
#line 518 "Knsgmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 41;
#line 518 "Knsgmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrpnm;
#line 518 "Knsgmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 518 "Knsgmst.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrprs;
#line 518 "Knsgmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 518 "Knsgmst.sqc"
      sql_setdlist[2].sqldata = (void*)seccd;
#line 518 "Knsgmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 41;
#line 518 "Knsgmst.sqc"
      sql_setdlist[3].sqldata = (void*)knshokbn;
#line 518 "Knsgmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 518 "Knsgmst.sqc"
      sql_setdlist[4].sqldata = (void*)&knssbt;
#line 518 "Knsgmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 518 "Knsgmst.sqc"
      sql_setdlist[5].sqldata = (void*)&bgroup;
#line 518 "Knsgmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 518 "Knsgmst.sqc"
      sql_setdlist[6].sqldata = (void*)&unyokbn;
#line 518 "Knsgmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 518 "Knsgmst.sqc"
      sql_setdlist[7].sqldata = (void*)&seqkthsok;
#line 518 "Knsgmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 518 "Knsgmst.sqc"
      sql_setdlist[8].sqldata = (void*)&seqkthsng;
#line 518 "Knsgmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 518 "Knsgmst.sqc"
      sql_setdlist[9].sqldata = (void*)&wsssksok;
#line 518 "Knsgmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 518 "Knsgmst.sqc"
      sql_setdlist[10].sqldata = (void*)&wsssksng;
#line 518 "Knsgmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 518 "Knsgmst.sqc"
      sql_setdlist[11].sqldata = (void*)&minryo;
#line 518 "Knsgmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 518 "Knsgmst.sqc"
      sql_setdlist[12].sqldata = (void*)&maxryo;
#line 518 "Knsgmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 518 "Knsgmst.sqc"
      sql_setdlist[13].sqldata = (void*)skitray;
#line 518 "Knsgmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 11;
#line 518 "Knsgmst.sqc"
      sql_setdlist[14].sqldata = (void*)mbttray;
#line 518 "Knsgmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 11;
#line 518 "Knsgmst.sqc"
      sql_setdlist[15].sqldata = (void*)skntray;
#line 518 "Knsgmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 11;
#line 518 "Knsgmst.sqc"
      sql_setdlist[16].sqldata = (void*)ssttray;
#line 518 "Knsgmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 8;
#line 518 "Knsgmst.sqc"
      sql_setdlist[17].sqldata = (void*)knsyb;
#line 518 "Knsgmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 5;
#line 518 "Knsgmst.sqc"
      sql_setdlist[18].sqldata = (void*)ykcd;
#line 518 "Knsgmst.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 21;
#line 518 "Knsgmst.sqc"
      sql_setdlist[19].sqldata = (void*)skiwsid;
#line 518 "Knsgmst.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 21;
#line 518 "Knsgmst.sqc"
      sql_setdlist[20].sqldata = (void*)sknwsid;
#line 518 "Knsgmst.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 21;
#line 518 "Knsgmst.sqc"
      sql_setdlist[21].sqldata = (void*)kkalstid;
#line 518 "Knsgmst.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 21;
#line 518 "Knsgmst.sqc"
      sql_setdlist[22].sqldata = (void*)splblid;
#line 518 "Knsgmst.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 21;
#line 518 "Knsgmst.sqc"
      sql_setdlist[23].sqldata = (void*)lstyb1;
#line 518 "Knsgmst.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 21;
#line 518 "Knsgmst.sqc"
      sql_setdlist[24].sqldata = (void*)lstyb2;
#line 518 "Knsgmst.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 11;
#line 518 "Knsgmst.sqc"
      sql_setdlist[25].sqldata = (void*)haiymd;
#line 518 "Knsgmst.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 9;
#line 518 "Knsgmst.sqc"
      sql_setdlist[26].sqldata = (void*)hnktntid;
#line 518 "Knsgmst.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 27;
#line 518 "Knsgmst.sqc"
      sql_setdlist[27].sqldata = (void*)ksndh;
#line 518 "Knsgmst.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 17;
#line 518 "Knsgmst.sqc"
      sql_setdlist[28].sqldata = (void*)knsgrp;
#line 518 "Knsgmst.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 11;
#line 518 "Knsgmst.sqc"
      sql_setdlist[29].sqldata = (void*)kaiymd;
#line 518 "Knsgmst.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 518 "Knsgmst.sqc"
      sqlasetdata(2,0,30,sql_setdlist,0L,0L);
    }
#line 518 "Knsgmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 518 "Knsgmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 518 "Knsgmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 518 "Knsgmst.sqc"
  sqlastop(0L);
}

#line 518 "Knsgmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 523 "Knsgmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 527 "Knsgmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKnsgmstDelete()
 *    KNSGMST レコードを削除する
 * ■引数
 *    [I]  Knsgmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKnsgmstDelete( Knsgmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KnsgmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 551 "Knsgmst.sqc"


    
/*
EXEC SQL DELETE FROM KNSGMST
    WHERE
		KNSGRP = :knsgrp AND
		KAIYMD = :kaiymd;
*/

{
#line 556 "Knsgmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 556 "Knsgmst.sqc"
  sqlaaloc(2,2,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 556 "Knsgmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 556 "Knsgmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 556 "Knsgmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 556 "Knsgmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 556 "Knsgmst.sqc"
      sql_setdlist[1].sqldata = (void*)kaiymd;
#line 556 "Knsgmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 556 "Knsgmst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 556 "Knsgmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 556 "Knsgmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 556 "Knsgmst.sqc"
  sqlastop(0L);
}

#line 556 "Knsgmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 561 "Knsgmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
