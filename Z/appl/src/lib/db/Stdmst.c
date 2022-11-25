static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,77,65,87,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,54,57,90,83,84,68,77,32,0,0,0,0,0,0,0,0,
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


#line 1 "Stdmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Stdmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Stdmst.h"
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


#line 24 "Stdmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Stdmst.sqc"

	char    bskkbn[5];
	char    nbkmkcd[8];
	short   stdsbt;
	char    kmkcd[8];
	char    stdnm[41];
	char    stdrk[21];
	char    stdx[9];
	char    stdsd[9];
	char    stdcv[9];
	char    valuer[9];
	char    maxr[9];
	short   place;
	short   unit[17];
	short   facter1[9];
	short   facter2[9];
	char    base1[9];
	char    base2[9];
	sqlint32  filenum;
	char    kigen[27];
	short   ctlstart;
	short   ctlcnt;
	short   ctlpos;
	short   ctlitv;
	short   ctllv;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 58 "Stdmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Stdmst

BmlDMMInfo	StdmstArray[] = {
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( nbkmkcd ),
	DMM_SSHORT( stdsbt ),
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( stdnm ),
	DMM_SSTRING( stdrk ),
	DMM_SSTRING( stdx ),
	DMM_SSTRING( stdsd ),
	DMM_SSTRING( stdcv ),
	DMM_SSTRING( valuer ),
	DMM_SSTRING( maxr ),
	DMM_SSHORT( place ),
	DMM_SSHORT( unit ),
	DMM_SSHORT( facter1 ),
	DMM_SSHORT( facter2 ),
	DMM_SSTRING( base1 ),
	DMM_SSTRING( base2 ),
	DMM_SLONG( filenum ),
	DMM_STIMESTAMP( kigen ),
	DMM_SSHORT( ctlstart ),
	DMM_SSHORT( ctlcnt ),
	DMM_SSHORT( ctlpos ),
	DMM_SSHORT( ctlitv ),
	DMM_SSHORT( ctllv ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbStdmstSelectAll()
 *    STDMST レコード全件取得
 * ■引数
 *    [O]  Stdmst** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbStdmstSelectAll( Stdmst** arrayOut, int* numOut )
{
    Stdmst*     array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 114 "Stdmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		BSKKBN,
		NBKMKCD,
		STDSBT,
		KMKCD,
		STDNM,
		STDRK,
		STDX,
		STDSD,
		STDCV,
		VALUER,
		MAXR,
		PLACE,
		UNIT,
		FACTER1,
		FACTER2,
		BASE1,
		BASE2,
		FILENUM,
		KIGEN,
		CTLSTART,
		CTLCNT,
		CTLPOS,
		CTLITV,
		CTLLV,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        STDMST FOR READ ONLY;
*/

#line 147 "Stdmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 149 "Stdmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 149 "Stdmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 149 "Stdmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 149 "Stdmst.sqc"
  sqlastop(0L);
}

#line 149 "Stdmst.sqc"


    while( 1 ) {
        Stdmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:bskkbn,
			:nbkmkcd,
			:stdsbt,
			:kmkcd,
			:stdnm,
			:stdrk,
			:stdx,
			:stdsd,
			:stdcv,
			:valuer,
			:maxr,
			:place,
			:unit,
			:facter1,
			:facter2,
			:base1,
			:base2,
			:filenum,
			:kigen,
			:ctlstart,
			:ctlcnt,
			:ctlpos,
			:ctlitv,
			:ctllv,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 182 "Stdmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 182 "Stdmst.sqc"
  sqlaaloc(3,28,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[28];
#line 182 "Stdmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 182 "Stdmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 182 "Stdmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 182 "Stdmst.sqc"
      sql_setdlist[1].sqldata = (void*)nbkmkcd;
#line 182 "Stdmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 182 "Stdmst.sqc"
      sql_setdlist[2].sqldata = (void*)&stdsbt;
#line 182 "Stdmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 182 "Stdmst.sqc"
      sql_setdlist[3].sqldata = (void*)kmkcd;
#line 182 "Stdmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 41;
#line 182 "Stdmst.sqc"
      sql_setdlist[4].sqldata = (void*)stdnm;
#line 182 "Stdmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 182 "Stdmst.sqc"
      sql_setdlist[5].sqldata = (void*)stdrk;
#line 182 "Stdmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 9;
#line 182 "Stdmst.sqc"
      sql_setdlist[6].sqldata = (void*)stdx;
#line 182 "Stdmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 182 "Stdmst.sqc"
      sql_setdlist[7].sqldata = (void*)stdsd;
#line 182 "Stdmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 182 "Stdmst.sqc"
      sql_setdlist[8].sqldata = (void*)stdcv;
#line 182 "Stdmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 9;
#line 182 "Stdmst.sqc"
      sql_setdlist[9].sqldata = (void*)valuer;
#line 182 "Stdmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 9;
#line 182 "Stdmst.sqc"
      sql_setdlist[10].sqldata = (void*)maxr;
#line 182 "Stdmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 182 "Stdmst.sqc"
      sql_setdlist[11].sqldata = (void*)&place;
#line 182 "Stdmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 182 "Stdmst.sqc"
      sql_setdlist[12].sqldata = (void*)&unit[0];
#line 182 "Stdmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 182 "Stdmst.sqc"
      sql_setdlist[13].sqldata = (void*)&facter1[0];
#line 182 "Stdmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 182 "Stdmst.sqc"
      sql_setdlist[14].sqldata = (void*)&facter2[0];
#line 182 "Stdmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 182 "Stdmst.sqc"
      sql_setdlist[15].sqldata = (void*)base1;
#line 182 "Stdmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 9;
#line 182 "Stdmst.sqc"
      sql_setdlist[16].sqldata = (void*)base2;
#line 182 "Stdmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 182 "Stdmst.sqc"
      sql_setdlist[17].sqldata = (void*)&filenum;
#line 182 "Stdmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 182 "Stdmst.sqc"
      sql_setdlist[18].sqldata = (void*)kigen;
#line 182 "Stdmst.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 182 "Stdmst.sqc"
      sql_setdlist[19].sqldata = (void*)&ctlstart;
#line 182 "Stdmst.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[20].sqltype = 500; sql_setdlist[20].sqllen = 2;
#line 182 "Stdmst.sqc"
      sql_setdlist[20].sqldata = (void*)&ctlcnt;
#line 182 "Stdmst.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[21].sqltype = 500; sql_setdlist[21].sqllen = 2;
#line 182 "Stdmst.sqc"
      sql_setdlist[21].sqldata = (void*)&ctlpos;
#line 182 "Stdmst.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[22].sqltype = 500; sql_setdlist[22].sqllen = 2;
#line 182 "Stdmst.sqc"
      sql_setdlist[22].sqldata = (void*)&ctlitv;
#line 182 "Stdmst.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[23].sqltype = 500; sql_setdlist[23].sqllen = 2;
#line 182 "Stdmst.sqc"
      sql_setdlist[23].sqldata = (void*)&ctllv;
#line 182 "Stdmst.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 11;
#line 182 "Stdmst.sqc"
      sql_setdlist[24].sqldata = (void*)kaiymd;
#line 182 "Stdmst.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 11;
#line 182 "Stdmst.sqc"
      sql_setdlist[25].sqldata = (void*)haiymd;
#line 182 "Stdmst.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 9;
#line 182 "Stdmst.sqc"
      sql_setdlist[26].sqldata = (void*)hnktntid;
#line 182 "Stdmst.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 27;
#line 182 "Stdmst.sqc"
      sql_setdlist[27].sqldata = (void*)ksndh;
#line 182 "Stdmst.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 182 "Stdmst.sqc"
      sqlasetdata(3,0,28,sql_setdlist,0L,0L);
    }
#line 182 "Stdmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 182 "Stdmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 182 "Stdmst.sqc"
  sqlastop(0L);
}

#line 182 "Stdmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Stdmst*)ZbmlRealloc( array,
                                    sizeof( Stdmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Stdmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, StdmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 197 "Stdmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 197 "Stdmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 197 "Stdmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 197 "Stdmst.sqc"
  sqlastop(0L);
}

#line 197 "Stdmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 205 "Stdmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbStdmstSelectKey()
 *    STDMST レコードKey条件取得
 * ■引数
 *    [I]  Stdmst* pKey       取得するレコードのキー
 *    [O]  Stdmst** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbStdmstSelectKey( Stdmst* pKey, Stdmst** arrayOut, int* numOut )
{
    Stdmst*     array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, StdmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 231 "Stdmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		BSKKBN,
		NBKMKCD,
		STDSBT,
		KMKCD,
		STDNM,
		STDRK,
		STDX,
		STDSD,
		STDCV,
		VALUER,
		MAXR,
		PLACE,
		UNIT,
		FACTER1,
		FACTER2,
		BASE1,
		BASE2,
		FILENUM,
		KIGEN,
		CTLSTART,
		CTLCNT,
		CTLPOS,
		CTLITV,
		CTLLV,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        STDMST
    WHERE
		BSKKBN = :bskkbn AND
		NBKMKCD = :nbkmkcd AND
		STDSBT = :stdsbt AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 269 "Stdmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 271 "Stdmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 271 "Stdmst.sqc"
  sqlaaloc(2,4,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 271 "Stdmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 271 "Stdmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 271 "Stdmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 271 "Stdmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 271 "Stdmst.sqc"
      sql_setdlist[1].sqldata = (void*)nbkmkcd;
#line 271 "Stdmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 271 "Stdmst.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 271 "Stdmst.sqc"
      sql_setdlist[2].sqldata = (void*)&stdsbt;
#line 271 "Stdmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 271 "Stdmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 271 "Stdmst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 271 "Stdmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 271 "Stdmst.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 271 "Stdmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 271 "Stdmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 271 "Stdmst.sqc"
  sqlastop(0L);
}

#line 271 "Stdmst.sqc"


    while( 1 ) {
        Stdmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:bskkbn,
			:nbkmkcd,
			:stdsbt,
			:kmkcd,
			:stdnm,
			:stdrk,
			:stdx,
			:stdsd,
			:stdcv,
			:valuer,
			:maxr,
			:place,
			:unit,
			:facter1,
			:facter2,
			:base1,
			:base2,
			:filenum,
			:kigen,
			:ctlstart,
			:ctlcnt,
			:ctlpos,
			:ctlitv,
			:ctllv,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 304 "Stdmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 304 "Stdmst.sqc"
  sqlaaloc(3,28,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[28];
#line 304 "Stdmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 304 "Stdmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 304 "Stdmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 304 "Stdmst.sqc"
      sql_setdlist[1].sqldata = (void*)nbkmkcd;
#line 304 "Stdmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 304 "Stdmst.sqc"
      sql_setdlist[2].sqldata = (void*)&stdsbt;
#line 304 "Stdmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 304 "Stdmst.sqc"
      sql_setdlist[3].sqldata = (void*)kmkcd;
#line 304 "Stdmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 41;
#line 304 "Stdmst.sqc"
      sql_setdlist[4].sqldata = (void*)stdnm;
#line 304 "Stdmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 304 "Stdmst.sqc"
      sql_setdlist[5].sqldata = (void*)stdrk;
#line 304 "Stdmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 9;
#line 304 "Stdmst.sqc"
      sql_setdlist[6].sqldata = (void*)stdx;
#line 304 "Stdmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 304 "Stdmst.sqc"
      sql_setdlist[7].sqldata = (void*)stdsd;
#line 304 "Stdmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 304 "Stdmst.sqc"
      sql_setdlist[8].sqldata = (void*)stdcv;
#line 304 "Stdmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 9;
#line 304 "Stdmst.sqc"
      sql_setdlist[9].sqldata = (void*)valuer;
#line 304 "Stdmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 9;
#line 304 "Stdmst.sqc"
      sql_setdlist[10].sqldata = (void*)maxr;
#line 304 "Stdmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 304 "Stdmst.sqc"
      sql_setdlist[11].sqldata = (void*)&place;
#line 304 "Stdmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 304 "Stdmst.sqc"
      sql_setdlist[12].sqldata = (void*)&unit[0];
#line 304 "Stdmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 304 "Stdmst.sqc"
      sql_setdlist[13].sqldata = (void*)&facter1[0];
#line 304 "Stdmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 304 "Stdmst.sqc"
      sql_setdlist[14].sqldata = (void*)&facter2[0];
#line 304 "Stdmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 304 "Stdmst.sqc"
      sql_setdlist[15].sqldata = (void*)base1;
#line 304 "Stdmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 9;
#line 304 "Stdmst.sqc"
      sql_setdlist[16].sqldata = (void*)base2;
#line 304 "Stdmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 304 "Stdmst.sqc"
      sql_setdlist[17].sqldata = (void*)&filenum;
#line 304 "Stdmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 304 "Stdmst.sqc"
      sql_setdlist[18].sqldata = (void*)kigen;
#line 304 "Stdmst.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 304 "Stdmst.sqc"
      sql_setdlist[19].sqldata = (void*)&ctlstart;
#line 304 "Stdmst.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[20].sqltype = 500; sql_setdlist[20].sqllen = 2;
#line 304 "Stdmst.sqc"
      sql_setdlist[20].sqldata = (void*)&ctlcnt;
#line 304 "Stdmst.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[21].sqltype = 500; sql_setdlist[21].sqllen = 2;
#line 304 "Stdmst.sqc"
      sql_setdlist[21].sqldata = (void*)&ctlpos;
#line 304 "Stdmst.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[22].sqltype = 500; sql_setdlist[22].sqllen = 2;
#line 304 "Stdmst.sqc"
      sql_setdlist[22].sqldata = (void*)&ctlitv;
#line 304 "Stdmst.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[23].sqltype = 500; sql_setdlist[23].sqllen = 2;
#line 304 "Stdmst.sqc"
      sql_setdlist[23].sqldata = (void*)&ctllv;
#line 304 "Stdmst.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 11;
#line 304 "Stdmst.sqc"
      sql_setdlist[24].sqldata = (void*)kaiymd;
#line 304 "Stdmst.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 11;
#line 304 "Stdmst.sqc"
      sql_setdlist[25].sqldata = (void*)haiymd;
#line 304 "Stdmst.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 9;
#line 304 "Stdmst.sqc"
      sql_setdlist[26].sqldata = (void*)hnktntid;
#line 304 "Stdmst.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 27;
#line 304 "Stdmst.sqc"
      sql_setdlist[27].sqldata = (void*)ksndh;
#line 304 "Stdmst.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 304 "Stdmst.sqc"
      sqlasetdata(3,0,28,sql_setdlist,0L,0L);
    }
#line 304 "Stdmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 304 "Stdmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 304 "Stdmst.sqc"
  sqlastop(0L);
}

#line 304 "Stdmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Stdmst*)ZbmlRealloc( array,
                                    sizeof( Stdmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Stdmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, StdmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 319 "Stdmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 319 "Stdmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 319 "Stdmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 319 "Stdmst.sqc"
  sqlastop(0L);
}

#line 319 "Stdmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 327 "Stdmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbStdmstInsert()
 *    STDMST レコードを挿入する
 * ■引数
 *    [I]  Stdmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbStdmstInsert( Stdmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, StdmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 350 "Stdmst.sqc"


    
/*
EXEC SQL INSERT INTO STDMST
    (
		BSKKBN,
		NBKMKCD,
		STDSBT,
		KMKCD,
		STDNM,
		STDRK,
		STDX,
		STDSD,
		STDCV,
		VALUER,
		MAXR,
		PLACE,
		UNIT,
		FACTER1,
		FACTER2,
		BASE1,
		BASE2,
		FILENUM,
		KIGEN,
		CTLSTART,
		CTLCNT,
		CTLPOS,
		CTLITV,
		CTLLV,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:bskkbn,
		:nbkmkcd,
		:stdsbt,
		:kmkcd,
		:stdnm,
		:stdrk,
		:stdx,
		:stdsd,
		:stdcv,
		:valuer,
		:maxr,
		:place,
		:unit,
		:facter1,
		:facter2,
		:base1,
		:base2,
		:filenum,
		:kigen,
		:ctlstart,
		:ctlcnt,
		:ctlpos,
		:ctlitv,
		:ctllv,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 411 "Stdmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 411 "Stdmst.sqc"
  sqlaaloc(2,28,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[28];
#line 411 "Stdmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 411 "Stdmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 411 "Stdmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 411 "Stdmst.sqc"
      sql_setdlist[1].sqldata = (void*)nbkmkcd;
#line 411 "Stdmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 411 "Stdmst.sqc"
      sql_setdlist[2].sqldata = (void*)&stdsbt;
#line 411 "Stdmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 411 "Stdmst.sqc"
      sql_setdlist[3].sqldata = (void*)kmkcd;
#line 411 "Stdmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 41;
#line 411 "Stdmst.sqc"
      sql_setdlist[4].sqldata = (void*)stdnm;
#line 411 "Stdmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 411 "Stdmst.sqc"
      sql_setdlist[5].sqldata = (void*)stdrk;
#line 411 "Stdmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 9;
#line 411 "Stdmst.sqc"
      sql_setdlist[6].sqldata = (void*)stdx;
#line 411 "Stdmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 411 "Stdmst.sqc"
      sql_setdlist[7].sqldata = (void*)stdsd;
#line 411 "Stdmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 411 "Stdmst.sqc"
      sql_setdlist[8].sqldata = (void*)stdcv;
#line 411 "Stdmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 9;
#line 411 "Stdmst.sqc"
      sql_setdlist[9].sqldata = (void*)valuer;
#line 411 "Stdmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 9;
#line 411 "Stdmst.sqc"
      sql_setdlist[10].sqldata = (void*)maxr;
#line 411 "Stdmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 411 "Stdmst.sqc"
      sql_setdlist[11].sqldata = (void*)&place;
#line 411 "Stdmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 411 "Stdmst.sqc"
      sql_setdlist[12].sqldata = (void*)&unit[0];
#line 411 "Stdmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 411 "Stdmst.sqc"
      sql_setdlist[13].sqldata = (void*)&facter1[0];
#line 411 "Stdmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 411 "Stdmst.sqc"
      sql_setdlist[14].sqldata = (void*)&facter2[0];
#line 411 "Stdmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 411 "Stdmst.sqc"
      sql_setdlist[15].sqldata = (void*)base1;
#line 411 "Stdmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 9;
#line 411 "Stdmst.sqc"
      sql_setdlist[16].sqldata = (void*)base2;
#line 411 "Stdmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 411 "Stdmst.sqc"
      sql_setdlist[17].sqldata = (void*)&filenum;
#line 411 "Stdmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 411 "Stdmst.sqc"
      sql_setdlist[18].sqldata = (void*)kigen;
#line 411 "Stdmst.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 411 "Stdmst.sqc"
      sql_setdlist[19].sqldata = (void*)&ctlstart;
#line 411 "Stdmst.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[20].sqltype = 500; sql_setdlist[20].sqllen = 2;
#line 411 "Stdmst.sqc"
      sql_setdlist[20].sqldata = (void*)&ctlcnt;
#line 411 "Stdmst.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[21].sqltype = 500; sql_setdlist[21].sqllen = 2;
#line 411 "Stdmst.sqc"
      sql_setdlist[21].sqldata = (void*)&ctlpos;
#line 411 "Stdmst.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[22].sqltype = 500; sql_setdlist[22].sqllen = 2;
#line 411 "Stdmst.sqc"
      sql_setdlist[22].sqldata = (void*)&ctlitv;
#line 411 "Stdmst.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[23].sqltype = 500; sql_setdlist[23].sqllen = 2;
#line 411 "Stdmst.sqc"
      sql_setdlist[23].sqldata = (void*)&ctllv;
#line 411 "Stdmst.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 11;
#line 411 "Stdmst.sqc"
      sql_setdlist[24].sqldata = (void*)kaiymd;
#line 411 "Stdmst.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 11;
#line 411 "Stdmst.sqc"
      sql_setdlist[25].sqldata = (void*)haiymd;
#line 411 "Stdmst.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 9;
#line 411 "Stdmst.sqc"
      sql_setdlist[26].sqldata = (void*)hnktntid;
#line 411 "Stdmst.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 27;
#line 411 "Stdmst.sqc"
      sql_setdlist[27].sqldata = (void*)ksndh;
#line 411 "Stdmst.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 411 "Stdmst.sqc"
      sqlasetdata(2,0,28,sql_setdlist,0L,0L);
    }
#line 411 "Stdmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 411 "Stdmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 411 "Stdmst.sqc"
  sqlastop(0L);
}

#line 411 "Stdmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 416 "Stdmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbStdmstUpdate()
 *    STDMST レコードを更新する
 * ■引数
 *    [I]  Stdmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbStdmstUpdate( Stdmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, StdmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 440 "Stdmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 441 "Stdmst.sqc"


    
/*
EXEC SQL UPDATE STDMST
    SET (
		KMKCD,
		STDNM,
		STDRK,
		STDX,
		STDSD,
		STDCV,
		VALUER,
		MAXR,
		PLACE,
		UNIT,
		FACTER1,
		FACTER2,
		BASE1,
		BASE2,
		FILENUM,
		KIGEN,
		CTLSTART,
		CTLCNT,
		CTLPOS,
		CTLITV,
		CTLLV,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:kmkcd,
		:stdnm,
		:stdrk,
		:stdx,
		:stdsd,
		:stdcv,
		:valuer,
		:maxr,
		:place,
		:unit,
		:facter1,
		:facter2,
		:base1,
		:base2,
		:filenum,
		:kigen,
		:ctlstart,
		:ctlcnt,
		:ctlpos,
		:ctlitv,
		:ctllv,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		BSKKBN = :bskkbn AND
		NBKMKCD = :nbkmkcd AND
		STDSBT = :stdsbt AND
		KAIYMD = :kaiymd;
*/

{
#line 498 "Stdmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 498 "Stdmst.sqc"
  sqlaaloc(2,28,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[28];
#line 498 "Stdmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 498 "Stdmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcd;
#line 498 "Stdmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 41;
#line 498 "Stdmst.sqc"
      sql_setdlist[1].sqldata = (void*)stdnm;
#line 498 "Stdmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 498 "Stdmst.sqc"
      sql_setdlist[2].sqldata = (void*)stdrk;
#line 498 "Stdmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 9;
#line 498 "Stdmst.sqc"
      sql_setdlist[3].sqldata = (void*)stdx;
#line 498 "Stdmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 9;
#line 498 "Stdmst.sqc"
      sql_setdlist[4].sqldata = (void*)stdsd;
#line 498 "Stdmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 9;
#line 498 "Stdmst.sqc"
      sql_setdlist[5].sqldata = (void*)stdcv;
#line 498 "Stdmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 9;
#line 498 "Stdmst.sqc"
      sql_setdlist[6].sqldata = (void*)valuer;
#line 498 "Stdmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 498 "Stdmst.sqc"
      sql_setdlist[7].sqldata = (void*)maxr;
#line 498 "Stdmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 498 "Stdmst.sqc"
      sql_setdlist[8].sqldata = (void*)&place;
#line 498 "Stdmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 498 "Stdmst.sqc"
      sql_setdlist[9].sqldata = (void*)&unit[0];
#line 498 "Stdmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[10].sqltype = 500; sql_setdlist[10].sqllen = 2;
#line 498 "Stdmst.sqc"
      sql_setdlist[10].sqldata = (void*)&facter1[0];
#line 498 "Stdmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 498 "Stdmst.sqc"
      sql_setdlist[11].sqldata = (void*)&facter2[0];
#line 498 "Stdmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 498 "Stdmst.sqc"
      sql_setdlist[12].sqldata = (void*)base1;
#line 498 "Stdmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 498 "Stdmst.sqc"
      sql_setdlist[13].sqldata = (void*)base2;
#line 498 "Stdmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 498 "Stdmst.sqc"
      sql_setdlist[14].sqldata = (void*)&filenum;
#line 498 "Stdmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 498 "Stdmst.sqc"
      sql_setdlist[15].sqldata = (void*)kigen;
#line 498 "Stdmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[16].sqltype = 500; sql_setdlist[16].sqllen = 2;
#line 498 "Stdmst.sqc"
      sql_setdlist[16].sqldata = (void*)&ctlstart;
#line 498 "Stdmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[17].sqltype = 500; sql_setdlist[17].sqllen = 2;
#line 498 "Stdmst.sqc"
      sql_setdlist[17].sqldata = (void*)&ctlcnt;
#line 498 "Stdmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[18].sqltype = 500; sql_setdlist[18].sqllen = 2;
#line 498 "Stdmst.sqc"
      sql_setdlist[18].sqldata = (void*)&ctlpos;
#line 498 "Stdmst.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 498 "Stdmst.sqc"
      sql_setdlist[19].sqldata = (void*)&ctlitv;
#line 498 "Stdmst.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[20].sqltype = 500; sql_setdlist[20].sqllen = 2;
#line 498 "Stdmst.sqc"
      sql_setdlist[20].sqldata = (void*)&ctllv;
#line 498 "Stdmst.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 11;
#line 498 "Stdmst.sqc"
      sql_setdlist[21].sqldata = (void*)haiymd;
#line 498 "Stdmst.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 9;
#line 498 "Stdmst.sqc"
      sql_setdlist[22].sqldata = (void*)hnktntid;
#line 498 "Stdmst.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 27;
#line 498 "Stdmst.sqc"
      sql_setdlist[23].sqldata = (void*)ksndh;
#line 498 "Stdmst.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 5;
#line 498 "Stdmst.sqc"
      sql_setdlist[24].sqldata = (void*)bskkbn;
#line 498 "Stdmst.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 8;
#line 498 "Stdmst.sqc"
      sql_setdlist[25].sqldata = (void*)nbkmkcd;
#line 498 "Stdmst.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[26].sqltype = 500; sql_setdlist[26].sqllen = 2;
#line 498 "Stdmst.sqc"
      sql_setdlist[26].sqldata = (void*)&stdsbt;
#line 498 "Stdmst.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 11;
#line 498 "Stdmst.sqc"
      sql_setdlist[27].sqldata = (void*)kaiymd;
#line 498 "Stdmst.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 498 "Stdmst.sqc"
      sqlasetdata(2,0,28,sql_setdlist,0L,0L);
    }
#line 498 "Stdmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 498 "Stdmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 498 "Stdmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 498 "Stdmst.sqc"
  sqlastop(0L);
}

#line 498 "Stdmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 503 "Stdmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 507 "Stdmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbStdmstDelete()
 *    STDMST レコードを削除する
 * ■引数
 *    [I]  Stdmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbStdmstDelete( Stdmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, StdmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 531 "Stdmst.sqc"


    
/*
EXEC SQL DELETE FROM STDMST
    WHERE
		BSKKBN = :bskkbn AND
		NBKMKCD = :nbkmkcd AND
		STDSBT = :stdsbt AND
		KAIYMD = :kaiymd;
*/

{
#line 538 "Stdmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 538 "Stdmst.sqc"
  sqlaaloc(2,4,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 538 "Stdmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 538 "Stdmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 538 "Stdmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 538 "Stdmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 538 "Stdmst.sqc"
      sql_setdlist[1].sqldata = (void*)nbkmkcd;
#line 538 "Stdmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 538 "Stdmst.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 538 "Stdmst.sqc"
      sql_setdlist[2].sqldata = (void*)&stdsbt;
#line 538 "Stdmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 538 "Stdmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 538 "Stdmst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 538 "Stdmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 538 "Stdmst.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 538 "Stdmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 538 "Stdmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 538 "Stdmst.sqc"
  sqlastop(0L);
}

#line 538 "Stdmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 543 "Stdmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
