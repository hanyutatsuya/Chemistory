static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,66,66,82,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,49,55,90,67,84,82,76,32,0,0,0,0,0,0,0,0,
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


#line 1 "Ctrlmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Ctrlmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Ctrlmst.h"
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


#line 24 "Ctrlmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Ctrlmst.sqc"

	char    bskkbn[5];
	char    nbkmkcd[8];
	char    ctrlsbt[21];
	char    ctrlnm[41];
	char    ctrlrs[21];
	char    syklotno[21];
	char    ctrllbl[3];
	char    ctrlx[13];
	char    ctrlsd[13];
	char    ctrlcv[13];
	char    valuer[13];
	char    maxr[13];
	short   sstnksu;
	char    tankj[17];
	char    facterjd1[13];
	char    facterjd2[13];
	char    factersd1[13];
	char    factersd2[13];
	char    basejd1[13];
	char    basejd2[13];
	char    basesd1[13];
	char    basesd2[13];
	sqlint32  ksikjnspsu;
	char    shrnglwhf[13];
	char    shrnghihf[13];
	char    shrnglwhb[13];
	char    shrnghihb[13];
	char    hstkjntn[13];
	char    hstkzmhb[13];
	short   hstkaikyu;
	sqlint32  filenum;
	char    ykkigen[11];
	char    gktks[13];
	short   ctrlhyjn;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 68 "Ctrlmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Ctrlmst

BmlDMMInfo	CtrlmstArray[] = {
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( nbkmkcd ),
	DMM_SSTRING( ctrlsbt ),
	DMM_SSTRING( ctrlnm ),
	DMM_SSTRING( ctrlrs ),
	DMM_SSTRING( syklotno ),
	DMM_SSTRING( ctrllbl ),
	DMM_SSTRING( ctrlx ),
	DMM_SSTRING( ctrlsd ),
	DMM_SSTRING( ctrlcv ),
	DMM_SSTRING( valuer ),
	DMM_SSTRING( maxr ),
	DMM_SSHORT( sstnksu ),
	DMM_SSTRING( tankj ),
	DMM_SSTRING( facterjd1 ),
	DMM_SSTRING( facterjd2 ),
	DMM_SSTRING( factersd1 ),
	DMM_SSTRING( factersd2 ),
	DMM_SSTRING( basejd1 ),
	DMM_SSTRING( basejd2 ),
	DMM_SSTRING( basesd1 ),
	DMM_SSTRING( basesd2 ),
	DMM_SLONG( ksikjnspsu ),
	DMM_SSTRING( shrnglwhf ),
	DMM_SSTRING( shrnghihf ),
	DMM_SSTRING( shrnglwhb ),
	DMM_SSTRING( shrnghihb ),
	DMM_SSTRING( hstkjntn ),
	DMM_SSTRING( hstkzmhb ),
	DMM_SSHORT( hstkaikyu ),
	DMM_SLONG( filenum ),
	DMM_SDATE( ykkigen ),
	DMM_SSTRING( gktks ),
	DMM_SSHORT( ctrlhyjn ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbCtrlmstSelectAll()
 *    CTRLMST レコード全件取得
 * ■引数
 *    [O]  Ctrlmst** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCtrlmstSelectAll( Ctrlmst** arrayOut, int* numOut )
{
    Ctrlmst*    array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 134 "Ctrlmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		BSKKBN,
		NBKMKCD,
		CTRLSBT,
		CTRLNM,
		CTRLRS,
		SYKLOTNO,
		CTRLLBL,
		CTRLX,
		CTRLSD,
		CTRLCV,
		VALUER,
		MAXR,
		SSTNKSU,
		TANKJ,
		FACTERJD1,
		FACTERJD2,
		FACTERSD1,
		FACTERSD2,
		BASEJD1,
		BASEJD2,
		BASESD1,
		BASESD2,
		KSIKJNSPSU,
		SHRNGLWHF,
		SHRNGHIHF,
		SHRNGLWHB,
		SHRNGHIHB,
		HSTKJNTN,
		HSTKZMHB,
		HSTKAIKYU,
		FILENUM,
		YKKIGEN,
		GKTKS,
		CTRLHYJN,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        CTRLMST FOR READ ONLY;
*/

#line 177 "Ctrlmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 179 "Ctrlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 179 "Ctrlmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 179 "Ctrlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 179 "Ctrlmst.sqc"
  sqlastop(0L);
}

#line 179 "Ctrlmst.sqc"


    while( 1 ) {
        Ctrlmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:bskkbn,
			:nbkmkcd,
			:ctrlsbt,
			:ctrlnm,
			:ctrlrs,
			:syklotno,
			:ctrllbl,
			:ctrlx,
			:ctrlsd,
			:ctrlcv,
			:valuer,
			:maxr,
			:sstnksu,
			:tankj,
			:facterjd1,
			:facterjd2,
			:factersd1,
			:factersd2,
			:basejd1,
			:basejd2,
			:basesd1,
			:basesd2,
			:ksikjnspsu,
			:shrnglwhf,
			:shrnghihf,
			:shrnglwhb,
			:shrnghihb,
			:hstkjntn,
			:hstkzmhb,
			:hstkaikyu,
			:filenum,
			:ykkigen,
			:gktks,
			:ctrlhyjn,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 222 "Ctrlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 222 "Ctrlmst.sqc"
  sqlaaloc(3,38,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[38];
#line 222 "Ctrlmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[1].sqldata = (void*)nbkmkcd;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[2].sqldata = (void*)ctrlsbt;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 41;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[3].sqldata = (void*)ctrlnm;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 21;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[4].sqldata = (void*)ctrlrs;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[5].sqldata = (void*)syklotno;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 3;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[6].sqldata = (void*)ctrllbl;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 13;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[7].sqldata = (void*)ctrlx;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 13;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[8].sqldata = (void*)ctrlsd;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 13;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[9].sqldata = (void*)ctrlcv;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 13;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[10].sqldata = (void*)valuer;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 13;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[11].sqldata = (void*)maxr;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[12].sqldata = (void*)&sstnksu;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 17;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[13].sqldata = (void*)tankj;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 13;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[14].sqldata = (void*)facterjd1;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 13;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[15].sqldata = (void*)facterjd2;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 13;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[16].sqldata = (void*)factersd1;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 13;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[17].sqldata = (void*)factersd2;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 13;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[18].sqldata = (void*)basejd1;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 13;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[19].sqldata = (void*)basejd2;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 13;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[20].sqldata = (void*)basesd1;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 13;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[21].sqldata = (void*)basesd2;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[22].sqltype = 496; sql_setdlist[22].sqllen = 4;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[22].sqldata = (void*)&ksikjnspsu;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 13;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[23].sqldata = (void*)shrnglwhf;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 13;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[24].sqldata = (void*)shrnghihf;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 13;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[25].sqldata = (void*)shrnglwhb;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 13;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[26].sqldata = (void*)shrnghihb;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 13;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[27].sqldata = (void*)hstkjntn;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 13;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[28].sqldata = (void*)hstkzmhb;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[29].sqltype = 500; sql_setdlist[29].sqllen = 2;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[29].sqldata = (void*)&hstkaikyu;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[30].sqltype = 496; sql_setdlist[30].sqllen = 4;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[30].sqldata = (void*)&filenum;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 11;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[31].sqldata = (void*)ykkigen;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 13;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[32].sqldata = (void*)gktks;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[33].sqltype = 500; sql_setdlist[33].sqllen = 2;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[33].sqldata = (void*)&ctrlhyjn;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 11;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[34].sqldata = (void*)kaiymd;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 11;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[35].sqldata = (void*)haiymd;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 9;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[36].sqldata = (void*)hnktntid;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 27;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[37].sqldata = (void*)ksndh;
#line 222 "Ctrlmst.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 222 "Ctrlmst.sqc"
      sqlasetdata(3,0,38,sql_setdlist,0L,0L);
    }
#line 222 "Ctrlmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 222 "Ctrlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 222 "Ctrlmst.sqc"
  sqlastop(0L);
}

#line 222 "Ctrlmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Ctrlmst*)ZbmlRealloc( array,
                                    sizeof( Ctrlmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Ctrlmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, CtrlmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 237 "Ctrlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 237 "Ctrlmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 237 "Ctrlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 237 "Ctrlmst.sqc"
  sqlastop(0L);
}

#line 237 "Ctrlmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 245 "Ctrlmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbCtrlmstSelectKey()
 *    CTRLMST レコードKey条件取得
 * ■引数
 *    [I]  Ctrlmst* pKey       取得するレコードのキー
 *    [O]  Ctrlmst** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCtrlmstSelectKey( Ctrlmst* pKey, Ctrlmst** arrayOut, int* numOut )
{
    Ctrlmst*    array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, CtrlmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 271 "Ctrlmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		BSKKBN,
		NBKMKCD,
		CTRLSBT,
		CTRLNM,
		CTRLRS,
		SYKLOTNO,
		CTRLLBL,
		CTRLX,
		CTRLSD,
		CTRLCV,
		VALUER,
		MAXR,
		SSTNKSU,
		TANKJ,
		FACTERJD1,
		FACTERJD2,
		FACTERSD1,
		FACTERSD2,
		BASEJD1,
		BASEJD2,
		BASESD1,
		BASESD2,
		KSIKJNSPSU,
		SHRNGLWHF,
		SHRNGHIHF,
		SHRNGLWHB,
		SHRNGHIHB,
		HSTKJNTN,
		HSTKZMHB,
		HSTKAIKYU,
		FILENUM,
		YKKIGEN,
		GKTKS,
		CTRLHYJN,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        CTRLMST
    WHERE
		BSKKBN = :bskkbn AND
		NBKMKCD = :nbkmkcd AND
		CTRLSBT = :ctrlsbt AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 319 "Ctrlmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 321 "Ctrlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 321 "Ctrlmst.sqc"
  sqlaaloc(2,4,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 321 "Ctrlmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 321 "Ctrlmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 321 "Ctrlmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 321 "Ctrlmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 321 "Ctrlmst.sqc"
      sql_setdlist[1].sqldata = (void*)nbkmkcd;
#line 321 "Ctrlmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 321 "Ctrlmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 321 "Ctrlmst.sqc"
      sql_setdlist[2].sqldata = (void*)ctrlsbt;
#line 321 "Ctrlmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 321 "Ctrlmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 321 "Ctrlmst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 321 "Ctrlmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 321 "Ctrlmst.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 321 "Ctrlmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 321 "Ctrlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 321 "Ctrlmst.sqc"
  sqlastop(0L);
}

#line 321 "Ctrlmst.sqc"


    while( 1 ) {
        Ctrlmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:bskkbn,
			:nbkmkcd,
			:ctrlsbt,
			:ctrlnm,
			:ctrlrs,
			:syklotno,
			:ctrllbl,
			:ctrlx,
			:ctrlsd,
			:ctrlcv,
			:valuer,
			:maxr,
			:sstnksu,
			:tankj,
			:facterjd1,
			:facterjd2,
			:factersd1,
			:factersd2,
			:basejd1,
			:basejd2,
			:basesd1,
			:basesd2,
			:ksikjnspsu,
			:shrnglwhf,
			:shrnghihf,
			:shrnglwhb,
			:shrnghihb,
			:hstkjntn,
			:hstkzmhb,
			:hstkaikyu,
			:filenum,
			:ykkigen,
			:gktks,
			:ctrlhyjn,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 364 "Ctrlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 364 "Ctrlmst.sqc"
  sqlaaloc(3,38,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[38];
#line 364 "Ctrlmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[1].sqldata = (void*)nbkmkcd;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[2].sqldata = (void*)ctrlsbt;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 41;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[3].sqldata = (void*)ctrlnm;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 21;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[4].sqldata = (void*)ctrlrs;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[5].sqldata = (void*)syklotno;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 3;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[6].sqldata = (void*)ctrllbl;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 13;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[7].sqldata = (void*)ctrlx;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 13;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[8].sqldata = (void*)ctrlsd;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 13;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[9].sqldata = (void*)ctrlcv;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 13;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[10].sqldata = (void*)valuer;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 13;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[11].sqldata = (void*)maxr;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[12].sqldata = (void*)&sstnksu;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 17;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[13].sqldata = (void*)tankj;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 13;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[14].sqldata = (void*)facterjd1;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 13;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[15].sqldata = (void*)facterjd2;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 13;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[16].sqldata = (void*)factersd1;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 13;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[17].sqldata = (void*)factersd2;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 13;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[18].sqldata = (void*)basejd1;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 13;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[19].sqldata = (void*)basejd2;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 13;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[20].sqldata = (void*)basesd1;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 13;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[21].sqldata = (void*)basesd2;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[22].sqltype = 496; sql_setdlist[22].sqllen = 4;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[22].sqldata = (void*)&ksikjnspsu;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 13;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[23].sqldata = (void*)shrnglwhf;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 13;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[24].sqldata = (void*)shrnghihf;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 13;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[25].sqldata = (void*)shrnglwhb;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 13;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[26].sqldata = (void*)shrnghihb;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 13;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[27].sqldata = (void*)hstkjntn;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 13;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[28].sqldata = (void*)hstkzmhb;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[29].sqltype = 500; sql_setdlist[29].sqllen = 2;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[29].sqldata = (void*)&hstkaikyu;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[30].sqltype = 496; sql_setdlist[30].sqllen = 4;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[30].sqldata = (void*)&filenum;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 11;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[31].sqldata = (void*)ykkigen;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 13;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[32].sqldata = (void*)gktks;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[33].sqltype = 500; sql_setdlist[33].sqllen = 2;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[33].sqldata = (void*)&ctrlhyjn;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 11;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[34].sqldata = (void*)kaiymd;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 11;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[35].sqldata = (void*)haiymd;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 9;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[36].sqldata = (void*)hnktntid;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 27;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[37].sqldata = (void*)ksndh;
#line 364 "Ctrlmst.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 364 "Ctrlmst.sqc"
      sqlasetdata(3,0,38,sql_setdlist,0L,0L);
    }
#line 364 "Ctrlmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 364 "Ctrlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 364 "Ctrlmst.sqc"
  sqlastop(0L);
}

#line 364 "Ctrlmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Ctrlmst*)ZbmlRealloc( array,
                                    sizeof( Ctrlmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Ctrlmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, CtrlmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 379 "Ctrlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 379 "Ctrlmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 379 "Ctrlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 379 "Ctrlmst.sqc"
  sqlastop(0L);
}

#line 379 "Ctrlmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 387 "Ctrlmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbCtrlmstInsert()
 *    CTRLMST レコードを挿入する
 * ■引数
 *    [I]  Ctrlmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCtrlmstInsert( Ctrlmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, CtrlmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 410 "Ctrlmst.sqc"


    
/*
EXEC SQL INSERT INTO CTRLMST
    (
		BSKKBN,
		NBKMKCD,
		CTRLSBT,
		CTRLNM,
		CTRLRS,
		SYKLOTNO,
		CTRLLBL,
		CTRLX,
		CTRLSD,
		CTRLCV,
		VALUER,
		MAXR,
		SSTNKSU,
		TANKJ,
		FACTERJD1,
		FACTERJD2,
		FACTERSD1,
		FACTERSD2,
		BASEJD1,
		BASEJD2,
		BASESD1,
		BASESD2,
		KSIKJNSPSU,
		SHRNGLWHF,
		SHRNGHIHF,
		SHRNGLWHB,
		SHRNGHIHB,
		HSTKJNTN,
		HSTKZMHB,
		HSTKAIKYU,
		FILENUM,
		YKKIGEN,
		GKTKS,
		CTRLHYJN,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:bskkbn,
		:nbkmkcd,
		:ctrlsbt,
		:ctrlnm,
		:ctrlrs,
		:syklotno,
		:ctrllbl,
		:ctrlx,
		:ctrlsd,
		:ctrlcv,
		:valuer,
		:maxr,
		:sstnksu,
		:tankj,
		:facterjd1,
		:facterjd2,
		:factersd1,
		:factersd2,
		:basejd1,
		:basejd2,
		:basesd1,
		:basesd2,
		:ksikjnspsu,
		:shrnglwhf,
		:shrnghihf,
		:shrnglwhb,
		:shrnghihb,
		:hstkjntn,
		:hstkzmhb,
		:hstkaikyu,
		:filenum,
		:ykkigen,
		:gktks,
		:ctrlhyjn,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 491 "Ctrlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 491 "Ctrlmst.sqc"
  sqlaaloc(2,38,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[38];
#line 491 "Ctrlmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[1].sqldata = (void*)nbkmkcd;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[2].sqldata = (void*)ctrlsbt;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 41;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[3].sqldata = (void*)ctrlnm;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 21;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[4].sqldata = (void*)ctrlrs;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[5].sqldata = (void*)syklotno;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 3;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[6].sqldata = (void*)ctrllbl;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 13;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[7].sqldata = (void*)ctrlx;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 13;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[8].sqldata = (void*)ctrlsd;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 13;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[9].sqldata = (void*)ctrlcv;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 13;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[10].sqldata = (void*)valuer;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 13;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[11].sqldata = (void*)maxr;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[12].sqldata = (void*)&sstnksu;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 17;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[13].sqldata = (void*)tankj;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 13;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[14].sqldata = (void*)facterjd1;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 13;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[15].sqldata = (void*)facterjd2;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 13;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[16].sqldata = (void*)factersd1;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 13;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[17].sqldata = (void*)factersd2;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 13;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[18].sqldata = (void*)basejd1;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 13;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[19].sqldata = (void*)basejd2;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 13;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[20].sqldata = (void*)basesd1;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 13;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[21].sqldata = (void*)basesd2;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[22].sqltype = 496; sql_setdlist[22].sqllen = 4;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[22].sqldata = (void*)&ksikjnspsu;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 13;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[23].sqldata = (void*)shrnglwhf;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 13;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[24].sqldata = (void*)shrnghihf;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 13;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[25].sqldata = (void*)shrnglwhb;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 13;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[26].sqldata = (void*)shrnghihb;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 13;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[27].sqldata = (void*)hstkjntn;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 13;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[28].sqldata = (void*)hstkzmhb;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[29].sqltype = 500; sql_setdlist[29].sqllen = 2;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[29].sqldata = (void*)&hstkaikyu;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[30].sqltype = 496; sql_setdlist[30].sqllen = 4;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[30].sqldata = (void*)&filenum;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 11;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[31].sqldata = (void*)ykkigen;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 13;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[32].sqldata = (void*)gktks;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[33].sqltype = 500; sql_setdlist[33].sqllen = 2;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[33].sqldata = (void*)&ctrlhyjn;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 11;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[34].sqldata = (void*)kaiymd;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 11;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[35].sqldata = (void*)haiymd;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 9;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[36].sqldata = (void*)hnktntid;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 27;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[37].sqldata = (void*)ksndh;
#line 491 "Ctrlmst.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 491 "Ctrlmst.sqc"
      sqlasetdata(2,0,38,sql_setdlist,0L,0L);
    }
#line 491 "Ctrlmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 491 "Ctrlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 491 "Ctrlmst.sqc"
  sqlastop(0L);
}

#line 491 "Ctrlmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 496 "Ctrlmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbCtrlmstUpdate()
 *    CTRLMST レコードを更新する
 * ■引数
 *    [I]  Ctrlmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCtrlmstUpdate( Ctrlmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, CtrlmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 520 "Ctrlmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 521 "Ctrlmst.sqc"


    
/*
EXEC SQL UPDATE CTRLMST
    SET (
		CTRLNM,
		CTRLRS,
		SYKLOTNO,
		CTRLLBL,
		CTRLX,
		CTRLSD,
		CTRLCV,
		VALUER,
		MAXR,
		SSTNKSU,
		TANKJ,
		FACTERJD1,
		FACTERJD2,
		FACTERSD1,
		FACTERSD2,
		BASEJD1,
		BASEJD2,
		BASESD1,
		BASESD2,
		KSIKJNSPSU,
		SHRNGLWHF,
		SHRNGHIHF,
		SHRNGLWHB,
		SHRNGHIHB,
		HSTKJNTN,
		HSTKZMHB,
		HSTKAIKYU,
		FILENUM,
		YKKIGEN,
		GKTKS,
		CTRLHYJN,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:ctrlnm,
		:ctrlrs,
		:syklotno,
		:ctrllbl,
		:ctrlx,
		:ctrlsd,
		:ctrlcv,
		:valuer,
		:maxr,
		:sstnksu,
		:tankj,
		:facterjd1,
		:facterjd2,
		:factersd1,
		:factersd2,
		:basejd1,
		:basejd2,
		:basesd1,
		:basesd2,
		:ksikjnspsu,
		:shrnglwhf,
		:shrnghihf,
		:shrnglwhb,
		:shrnghihb,
		:hstkjntn,
		:hstkzmhb,
		:hstkaikyu,
		:filenum,
		:ykkigen,
		:gktks,
		:ctrlhyjn,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		BSKKBN = :bskkbn AND
		NBKMKCD = :nbkmkcd AND
		CTRLSBT = :ctrlsbt AND
		KAIYMD = :kaiymd;
*/

{
#line 598 "Ctrlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 598 "Ctrlmst.sqc"
  sqlaaloc(2,38,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[38];
#line 598 "Ctrlmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 41;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[0].sqldata = (void*)ctrlnm;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[1].sqldata = (void*)ctrlrs;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[2].sqldata = (void*)syklotno;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[3].sqldata = (void*)ctrllbl;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 13;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[4].sqldata = (void*)ctrlx;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 13;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[5].sqldata = (void*)ctrlsd;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 13;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[6].sqldata = (void*)ctrlcv;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 13;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[7].sqldata = (void*)valuer;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 13;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[8].sqldata = (void*)maxr;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[9].sqldata = (void*)&sstnksu;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 17;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[10].sqldata = (void*)tankj;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 13;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[11].sqldata = (void*)facterjd1;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 13;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[12].sqldata = (void*)facterjd2;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 13;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[13].sqldata = (void*)factersd1;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 13;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[14].sqldata = (void*)factersd2;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 13;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[15].sqldata = (void*)basejd1;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 13;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[16].sqldata = (void*)basejd2;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 13;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[17].sqldata = (void*)basesd1;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 13;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[18].sqldata = (void*)basesd2;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[19].sqltype = 496; sql_setdlist[19].sqllen = 4;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[19].sqldata = (void*)&ksikjnspsu;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 13;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[20].sqldata = (void*)shrnglwhf;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 13;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[21].sqldata = (void*)shrnghihf;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 13;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[22].sqldata = (void*)shrnglwhb;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 13;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[23].sqldata = (void*)shrnghihb;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 13;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[24].sqldata = (void*)hstkjntn;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 13;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[25].sqldata = (void*)hstkzmhb;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[26].sqltype = 500; sql_setdlist[26].sqllen = 2;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[26].sqldata = (void*)&hstkaikyu;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[27].sqltype = 496; sql_setdlist[27].sqllen = 4;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[27].sqldata = (void*)&filenum;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 11;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[28].sqldata = (void*)ykkigen;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 13;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[29].sqldata = (void*)gktks;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[30].sqltype = 500; sql_setdlist[30].sqllen = 2;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[30].sqldata = (void*)&ctrlhyjn;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 11;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[31].sqldata = (void*)haiymd;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 9;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[32].sqldata = (void*)hnktntid;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 27;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[33].sqldata = (void*)ksndh;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 5;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[34].sqldata = (void*)bskkbn;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 8;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[35].sqldata = (void*)nbkmkcd;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 21;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[36].sqldata = (void*)ctrlsbt;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 11;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[37].sqldata = (void*)kaiymd;
#line 598 "Ctrlmst.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 598 "Ctrlmst.sqc"
      sqlasetdata(2,0,38,sql_setdlist,0L,0L);
    }
#line 598 "Ctrlmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 598 "Ctrlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 598 "Ctrlmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 598 "Ctrlmst.sqc"
  sqlastop(0L);
}

#line 598 "Ctrlmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 603 "Ctrlmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 607 "Ctrlmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbCtrlmstDelete()
 *    CTRLMST レコードを削除する
 * ■引数
 *    [I]  Ctrlmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbCtrlmstDelete( Ctrlmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, CtrlmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 631 "Ctrlmst.sqc"


    
/*
EXEC SQL DELETE FROM CTRLMST
    WHERE
		BSKKBN = :bskkbn AND
		NBKMKCD = :nbkmkcd AND
		CTRLSBT = :ctrlsbt AND
		KAIYMD = :kaiymd;
*/

{
#line 638 "Ctrlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 638 "Ctrlmst.sqc"
  sqlaaloc(2,4,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 638 "Ctrlmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 638 "Ctrlmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 638 "Ctrlmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 638 "Ctrlmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 638 "Ctrlmst.sqc"
      sql_setdlist[1].sqldata = (void*)nbkmkcd;
#line 638 "Ctrlmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 638 "Ctrlmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 638 "Ctrlmst.sqc"
      sql_setdlist[2].sqldata = (void*)ctrlsbt;
#line 638 "Ctrlmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 638 "Ctrlmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 638 "Ctrlmst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 638 "Ctrlmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 638 "Ctrlmst.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 638 "Ctrlmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 638 "Ctrlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 638 "Ctrlmst.sqc"
  sqlastop(0L);
}

#line 638 "Ctrlmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 643 "Ctrlmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
