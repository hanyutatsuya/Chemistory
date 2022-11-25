static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,69,66,84,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,52,48,90,75,77,75,77,32,0,0,0,0,0,0,0,0,
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


#line 1 "Kmkmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Kmkmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Kmkmst.h"
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


#line 24 "Kmkmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Kmkmst.sqc"

	char    knsgrp[17];
	char    kmkcd[8];
	char    kmknm[37];
	char    kmknmj[47];
	char    kmkrs[17];
	char    kmkrsj[21];
	char    kmknme[51];
	char    kmkhsknmj[21];
	char    fkkmknm[37];
	char    fkkmknmj[47];
	char    smpcd[8];
	char    oyakmkcd[8];
	char    korrn[8];
	char    seccd[3];
	char    stnflg;
	short   sstnksu;
	char    assay[41];
	short   fkjbn;
	char    fkbnkkb;
	char    tskflg[3];
	char    tktflg[3];
	char    ltmmnflg;
	char    zrkbn;
	sqlint32  bcrtj;
	sqlint32  bcrsr;
	sqlint32  bcrsn;
	char    yknknsflg;
	short   hrynsu;
	char    jdhskka[13];
	short   hyjijn;
	char    ksnkmkflg;
	char    hsiumflg;
	char    gmin[9];
	char    ghaba[9];
	short   rrkhzn;
	char    nyuyouflg;
	char    tstrflg;
	char    kmksbt;
	char    sgchkflg;
	char    ksjhflg;
	char    kssgflg;
	char    xmskflg;
	char    xmchkflg;
	short   xmcount;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 78 "Kmkmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Kmkmst

BmlDMMInfo	KmkmstArray[] = {
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( kmknm ),
	DMM_SSTRING( kmknmj ),
	DMM_SSTRING( kmkrs ),
	DMM_SSTRING( kmkrsj ),
	DMM_SSTRING( kmknme ),
	DMM_SSTRING( kmkhsknmj ),
	DMM_SSTRING( fkkmknm ),
	DMM_SSTRING( fkkmknmj ),
	DMM_SSTRING( smpcd ),
	DMM_SSTRING( oyakmkcd ),
	DMM_SSTRING( korrn ),
	DMM_SSTRING( seccd ),
	DMM_SCHAR( stnflg ),
	DMM_SSHORT( sstnksu ),
	DMM_SSTRING( assay ),
	DMM_SSHORT( fkjbn ),
	DMM_SCHAR( fkbnkkb ),
	DMM_SSTRING( tskflg ),
	DMM_SSTRING( tktflg ),
	DMM_SCHAR( ltmmnflg ),
	DMM_SCHAR( zrkbn ),
	DMM_SLONG( bcrtj ),
	DMM_SLONG( bcrsr ),
	DMM_SLONG( bcrsn ),
	DMM_SCHAR( yknknsflg ),
	DMM_SSHORT( hrynsu ),
	DMM_SSTRING( jdhskka ),
	DMM_SSHORT( hyjijn ),
	DMM_SCHAR( ksnkmkflg ),
	DMM_SCHAR( hsiumflg ),
	DMM_SSTRING( gmin ),
	DMM_SSTRING( ghaba ),
	DMM_SSHORT( rrkhzn ),
	DMM_SCHAR( nyuyouflg ),
	DMM_SCHAR( tstrflg ),
	DMM_SCHAR( kmksbt ),
	DMM_SCHAR( sgchkflg ),
	DMM_SCHAR( ksjhflg ),
	DMM_SCHAR( kssgflg ),
	DMM_SCHAR( xmskflg ),
	DMM_SCHAR( xmchkflg ),
	DMM_SSHORT( xmcount ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKmkmstSelectAll()
 *    KMKMST レコード全件取得
 * ■引数
 *    [O]  Kmkmst** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKmkmstSelectAll( Kmkmst** arrayOut, int* numOut )
{
    Kmkmst*     array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 154 "Kmkmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSGRP,
		KMKCD,
		KMKNM,
		KMKNMJ,
		KMKRS,
		KMKRSJ,
		KMKNME,
		KMKHSKNMJ,
		FKKMKNM,
		FKKMKNMJ,
		SMPCD,
		OYAKMKCD,
		KORRN,
		SECCD,
		STNFLG,
		SSTNKSU,
		ASSAY,
		FKJBN,
		FKBNKKB,
		TSKFLG,
		TKTFLG,
		LTMMNFLG,
		ZRKBN,
		BCRTJ,
		BCRSR,
		BCRSN,
		YKNKNSFLG,
		HRYNSU,
		JDHSKKA,
		HYJIJN,
		KSNKMKFLG,
		HSIUMFLG,
		GMIN,
		GHABA,
		RRKHZN,
		NYUYOUFLG,
		TSTRFLG,
		KMKSBT,
		SGCHKFLG,
		KSJHFLG,
		KSSGFLG,
		XMSKFLG,
		XMCHKFLG,
		XMCOUNT,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        KMKMST FOR READ ONLY;
*/

#line 207 "Kmkmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 209 "Kmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 209 "Kmkmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 209 "Kmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 209 "Kmkmst.sqc"
  sqlastop(0L);
}

#line 209 "Kmkmst.sqc"


    while( 1 ) {
        Kmkmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knsgrp,
			:kmkcd,
			:kmknm,
			:kmknmj,
			:kmkrs,
			:kmkrsj,
			:kmknme,
			:kmkhsknmj,
			:fkkmknm,
			:fkkmknmj,
			:smpcd,
			:oyakmkcd,
			:korrn,
			:seccd,
			:stnflg,
			:sstnksu,
			:assay,
			:fkjbn,
			:fkbnkkb,
			:tskflg,
			:tktflg,
			:ltmmnflg,
			:zrkbn,
			:bcrtj,
			:bcrsr,
			:bcrsn,
			:yknknsflg,
			:hrynsu,
			:jdhskka,
			:hyjijn,
			:ksnkmkflg,
			:hsiumflg,
			:gmin,
			:ghaba,
			:rrkhzn,
			:nyuyouflg,
			:tstrflg,
			:kmksbt,
			:sgchkflg,
			:ksjhflg,
			:kssgflg,
			:xmskflg,
			:xmchkflg,
			:xmcount,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 262 "Kmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 262 "Kmkmst.sqc"
  sqlaaloc(3,48,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[48];
#line 262 "Kmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 262 "Kmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 262 "Kmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 262 "Kmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 262 "Kmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 37;
#line 262 "Kmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmknm;
#line 262 "Kmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 47;
#line 262 "Kmkmst.sqc"
      sql_setdlist[3].sqldata = (void*)kmknmj;
#line 262 "Kmkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 262 "Kmkmst.sqc"
      sql_setdlist[4].sqldata = (void*)kmkrs;
#line 262 "Kmkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 262 "Kmkmst.sqc"
      sql_setdlist[5].sqldata = (void*)kmkrsj;
#line 262 "Kmkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 51;
#line 262 "Kmkmst.sqc"
      sql_setdlist[6].sqldata = (void*)kmknme;
#line 262 "Kmkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 21;
#line 262 "Kmkmst.sqc"
      sql_setdlist[7].sqldata = (void*)kmkhsknmj;
#line 262 "Kmkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 37;
#line 262 "Kmkmst.sqc"
      sql_setdlist[8].sqldata = (void*)fkkmknm;
#line 262 "Kmkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 47;
#line 262 "Kmkmst.sqc"
      sql_setdlist[9].sqldata = (void*)fkkmknmj;
#line 262 "Kmkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 8;
#line 262 "Kmkmst.sqc"
      sql_setdlist[10].sqldata = (void*)smpcd;
#line 262 "Kmkmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 8;
#line 262 "Kmkmst.sqc"
      sql_setdlist[11].sqldata = (void*)oyakmkcd;
#line 262 "Kmkmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 8;
#line 262 "Kmkmst.sqc"
      sql_setdlist[12].sqldata = (void*)korrn;
#line 262 "Kmkmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 3;
#line 262 "Kmkmst.sqc"
      sql_setdlist[13].sqldata = (void*)seccd;
#line 262 "Kmkmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 262 "Kmkmst.sqc"
      sql_setdlist[14].sqldata = (void*)&stnflg;
#line 262 "Kmkmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[15].sqltype = 500; sql_setdlist[15].sqllen = 2;
#line 262 "Kmkmst.sqc"
      sql_setdlist[15].sqldata = (void*)&sstnksu;
#line 262 "Kmkmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 41;
#line 262 "Kmkmst.sqc"
      sql_setdlist[16].sqldata = (void*)assay;
#line 262 "Kmkmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[17].sqltype = 500; sql_setdlist[17].sqllen = 2;
#line 262 "Kmkmst.sqc"
      sql_setdlist[17].sqldata = (void*)&fkjbn;
#line 262 "Kmkmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 262 "Kmkmst.sqc"
      sql_setdlist[18].sqldata = (void*)&fkbnkkb;
#line 262 "Kmkmst.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 3;
#line 262 "Kmkmst.sqc"
      sql_setdlist[19].sqldata = (void*)tskflg;
#line 262 "Kmkmst.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 3;
#line 262 "Kmkmst.sqc"
      sql_setdlist[20].sqldata = (void*)tktflg;
#line 262 "Kmkmst.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 262 "Kmkmst.sqc"
      sql_setdlist[21].sqldata = (void*)&ltmmnflg;
#line 262 "Kmkmst.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 262 "Kmkmst.sqc"
      sql_setdlist[22].sqldata = (void*)&zrkbn;
#line 262 "Kmkmst.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[23].sqltype = 496; sql_setdlist[23].sqllen = 4;
#line 262 "Kmkmst.sqc"
      sql_setdlist[23].sqldata = (void*)&bcrtj;
#line 262 "Kmkmst.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[24].sqltype = 496; sql_setdlist[24].sqllen = 4;
#line 262 "Kmkmst.sqc"
      sql_setdlist[24].sqldata = (void*)&bcrsr;
#line 262 "Kmkmst.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[25].sqltype = 496; sql_setdlist[25].sqllen = 4;
#line 262 "Kmkmst.sqc"
      sql_setdlist[25].sqldata = (void*)&bcrsn;
#line 262 "Kmkmst.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 262 "Kmkmst.sqc"
      sql_setdlist[26].sqldata = (void*)&yknknsflg;
#line 262 "Kmkmst.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[27].sqltype = 500; sql_setdlist[27].sqllen = 2;
#line 262 "Kmkmst.sqc"
      sql_setdlist[27].sqldata = (void*)&hrynsu;
#line 262 "Kmkmst.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 13;
#line 262 "Kmkmst.sqc"
      sql_setdlist[28].sqldata = (void*)jdhskka;
#line 262 "Kmkmst.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[29].sqltype = 500; sql_setdlist[29].sqllen = 2;
#line 262 "Kmkmst.sqc"
      sql_setdlist[29].sqldata = (void*)&hyjijn;
#line 262 "Kmkmst.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 262 "Kmkmst.sqc"
      sql_setdlist[30].sqldata = (void*)&ksnkmkflg;
#line 262 "Kmkmst.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 262 "Kmkmst.sqc"
      sql_setdlist[31].sqldata = (void*)&hsiumflg;
#line 262 "Kmkmst.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 9;
#line 262 "Kmkmst.sqc"
      sql_setdlist[32].sqldata = (void*)gmin;
#line 262 "Kmkmst.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 9;
#line 262 "Kmkmst.sqc"
      sql_setdlist[33].sqldata = (void*)ghaba;
#line 262 "Kmkmst.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[34].sqltype = 500; sql_setdlist[34].sqllen = 2;
#line 262 "Kmkmst.sqc"
      sql_setdlist[34].sqldata = (void*)&rrkhzn;
#line 262 "Kmkmst.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 262 "Kmkmst.sqc"
      sql_setdlist[35].sqldata = (void*)&nyuyouflg;
#line 262 "Kmkmst.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 262 "Kmkmst.sqc"
      sql_setdlist[36].sqldata = (void*)&tstrflg;
#line 262 "Kmkmst.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 262 "Kmkmst.sqc"
      sql_setdlist[37].sqldata = (void*)&kmksbt;
#line 262 "Kmkmst.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 262 "Kmkmst.sqc"
      sql_setdlist[38].sqldata = (void*)&sgchkflg;
#line 262 "Kmkmst.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 262 "Kmkmst.sqc"
      sql_setdlist[39].sqldata = (void*)&ksjhflg;
#line 262 "Kmkmst.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 262 "Kmkmst.sqc"
      sql_setdlist[40].sqldata = (void*)&kssgflg;
#line 262 "Kmkmst.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 262 "Kmkmst.sqc"
      sql_setdlist[41].sqldata = (void*)&xmskflg;
#line 262 "Kmkmst.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[42].sqltype = 452; sql_setdlist[42].sqllen = 1;
#line 262 "Kmkmst.sqc"
      sql_setdlist[42].sqldata = (void*)&xmchkflg;
#line 262 "Kmkmst.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[43].sqltype = 500; sql_setdlist[43].sqllen = 2;
#line 262 "Kmkmst.sqc"
      sql_setdlist[43].sqldata = (void*)&xmcount;
#line 262 "Kmkmst.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 11;
#line 262 "Kmkmst.sqc"
      sql_setdlist[44].sqldata = (void*)kaiymd;
#line 262 "Kmkmst.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 11;
#line 262 "Kmkmst.sqc"
      sql_setdlist[45].sqldata = (void*)haiymd;
#line 262 "Kmkmst.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 9;
#line 262 "Kmkmst.sqc"
      sql_setdlist[46].sqldata = (void*)hnktntid;
#line 262 "Kmkmst.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 27;
#line 262 "Kmkmst.sqc"
      sql_setdlist[47].sqldata = (void*)ksndh;
#line 262 "Kmkmst.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 262 "Kmkmst.sqc"
      sqlasetdata(3,0,48,sql_setdlist,0L,0L);
    }
#line 262 "Kmkmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 262 "Kmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 262 "Kmkmst.sqc"
  sqlastop(0L);
}

#line 262 "Kmkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kmkmst*)ZbmlRealloc( array,
                                    sizeof( Kmkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kmkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KmkmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 277 "Kmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 277 "Kmkmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 277 "Kmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 277 "Kmkmst.sqc"
  sqlastop(0L);
}

#line 277 "Kmkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 285 "Kmkmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKmkmstSelectKey()
 *    KMKMST レコードKey条件取得
 * ■引数
 *    [I]  Kmkmst* pKey       取得するレコードのキー
 *    [O]  Kmkmst** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKmkmstSelectKey( Kmkmst* pKey, Kmkmst** arrayOut, int* numOut )
{
    Kmkmst*     array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KmkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 311 "Kmkmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSGRP,
		KMKCD,
		KMKNM,
		KMKNMJ,
		KMKRS,
		KMKRSJ,
		KMKNME,
		KMKHSKNMJ,
		FKKMKNM,
		FKKMKNMJ,
		SMPCD,
		OYAKMKCD,
		KORRN,
		SECCD,
		STNFLG,
		SSTNKSU,
		ASSAY,
		FKJBN,
		FKBNKKB,
		TSKFLG,
		TKTFLG,
		LTMMNFLG,
		ZRKBN,
		BCRTJ,
		BCRSR,
		BCRSN,
		YKNKNSFLG,
		HRYNSU,
		JDHSKKA,
		HYJIJN,
		KSNKMKFLG,
		HSIUMFLG,
		GMIN,
		GHABA,
		RRKHZN,
		NYUYOUFLG,
		TSTRFLG,
		KMKSBT,
		SGCHKFLG,
		KSJHFLG,
		KSSGFLG,
		XMSKFLG,
		XMCHKFLG,
		XMCOUNT,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        KMKMST
    WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KAIYMD <= CURRENT DATE  FOR READ ONLY;
*/

#line 368 "Kmkmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 370 "Kmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 370 "Kmkmst.sqc"
  sqlaaloc(2,2,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 370 "Kmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 370 "Kmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 370 "Kmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 370 "Kmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 370 "Kmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 370 "Kmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 370 "Kmkmst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 370 "Kmkmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 370 "Kmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 370 "Kmkmst.sqc"
  sqlastop(0L);
}

#line 370 "Kmkmst.sqc"


    while( 1 ) {
        Kmkmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knsgrp,
			:kmkcd,
			:kmknm,
			:kmknmj,
			:kmkrs,
			:kmkrsj,
			:kmknme,
			:kmkhsknmj,
			:fkkmknm,
			:fkkmknmj,
			:smpcd,
			:oyakmkcd,
			:korrn,
			:seccd,
			:stnflg,
			:sstnksu,
			:assay,
			:fkjbn,
			:fkbnkkb,
			:tskflg,
			:tktflg,
			:ltmmnflg,
			:zrkbn,
			:bcrtj,
			:bcrsr,
			:bcrsn,
			:yknknsflg,
			:hrynsu,
			:jdhskka,
			:hyjijn,
			:ksnkmkflg,
			:hsiumflg,
			:gmin,
			:ghaba,
			:rrkhzn,
			:nyuyouflg,
			:tstrflg,
			:kmksbt,
			:sgchkflg,
			:ksjhflg,
			:kssgflg,
			:xmskflg,
			:xmchkflg,
			:xmcount,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 423 "Kmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 423 "Kmkmst.sqc"
  sqlaaloc(3,48,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[48];
#line 423 "Kmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 423 "Kmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 423 "Kmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 423 "Kmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 423 "Kmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 37;
#line 423 "Kmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmknm;
#line 423 "Kmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 47;
#line 423 "Kmkmst.sqc"
      sql_setdlist[3].sqldata = (void*)kmknmj;
#line 423 "Kmkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 423 "Kmkmst.sqc"
      sql_setdlist[4].sqldata = (void*)kmkrs;
#line 423 "Kmkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 423 "Kmkmst.sqc"
      sql_setdlist[5].sqldata = (void*)kmkrsj;
#line 423 "Kmkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 51;
#line 423 "Kmkmst.sqc"
      sql_setdlist[6].sqldata = (void*)kmknme;
#line 423 "Kmkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 21;
#line 423 "Kmkmst.sqc"
      sql_setdlist[7].sqldata = (void*)kmkhsknmj;
#line 423 "Kmkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 37;
#line 423 "Kmkmst.sqc"
      sql_setdlist[8].sqldata = (void*)fkkmknm;
#line 423 "Kmkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 47;
#line 423 "Kmkmst.sqc"
      sql_setdlist[9].sqldata = (void*)fkkmknmj;
#line 423 "Kmkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 8;
#line 423 "Kmkmst.sqc"
      sql_setdlist[10].sqldata = (void*)smpcd;
#line 423 "Kmkmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 8;
#line 423 "Kmkmst.sqc"
      sql_setdlist[11].sqldata = (void*)oyakmkcd;
#line 423 "Kmkmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 8;
#line 423 "Kmkmst.sqc"
      sql_setdlist[12].sqldata = (void*)korrn;
#line 423 "Kmkmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 3;
#line 423 "Kmkmst.sqc"
      sql_setdlist[13].sqldata = (void*)seccd;
#line 423 "Kmkmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 423 "Kmkmst.sqc"
      sql_setdlist[14].sqldata = (void*)&stnflg;
#line 423 "Kmkmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[15].sqltype = 500; sql_setdlist[15].sqllen = 2;
#line 423 "Kmkmst.sqc"
      sql_setdlist[15].sqldata = (void*)&sstnksu;
#line 423 "Kmkmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 41;
#line 423 "Kmkmst.sqc"
      sql_setdlist[16].sqldata = (void*)assay;
#line 423 "Kmkmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[17].sqltype = 500; sql_setdlist[17].sqllen = 2;
#line 423 "Kmkmst.sqc"
      sql_setdlist[17].sqldata = (void*)&fkjbn;
#line 423 "Kmkmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 423 "Kmkmst.sqc"
      sql_setdlist[18].sqldata = (void*)&fkbnkkb;
#line 423 "Kmkmst.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 3;
#line 423 "Kmkmst.sqc"
      sql_setdlist[19].sqldata = (void*)tskflg;
#line 423 "Kmkmst.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 3;
#line 423 "Kmkmst.sqc"
      sql_setdlist[20].sqldata = (void*)tktflg;
#line 423 "Kmkmst.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 423 "Kmkmst.sqc"
      sql_setdlist[21].sqldata = (void*)&ltmmnflg;
#line 423 "Kmkmst.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 423 "Kmkmst.sqc"
      sql_setdlist[22].sqldata = (void*)&zrkbn;
#line 423 "Kmkmst.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[23].sqltype = 496; sql_setdlist[23].sqllen = 4;
#line 423 "Kmkmst.sqc"
      sql_setdlist[23].sqldata = (void*)&bcrtj;
#line 423 "Kmkmst.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[24].sqltype = 496; sql_setdlist[24].sqllen = 4;
#line 423 "Kmkmst.sqc"
      sql_setdlist[24].sqldata = (void*)&bcrsr;
#line 423 "Kmkmst.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[25].sqltype = 496; sql_setdlist[25].sqllen = 4;
#line 423 "Kmkmst.sqc"
      sql_setdlist[25].sqldata = (void*)&bcrsn;
#line 423 "Kmkmst.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 423 "Kmkmst.sqc"
      sql_setdlist[26].sqldata = (void*)&yknknsflg;
#line 423 "Kmkmst.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[27].sqltype = 500; sql_setdlist[27].sqllen = 2;
#line 423 "Kmkmst.sqc"
      sql_setdlist[27].sqldata = (void*)&hrynsu;
#line 423 "Kmkmst.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 13;
#line 423 "Kmkmst.sqc"
      sql_setdlist[28].sqldata = (void*)jdhskka;
#line 423 "Kmkmst.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[29].sqltype = 500; sql_setdlist[29].sqllen = 2;
#line 423 "Kmkmst.sqc"
      sql_setdlist[29].sqldata = (void*)&hyjijn;
#line 423 "Kmkmst.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 423 "Kmkmst.sqc"
      sql_setdlist[30].sqldata = (void*)&ksnkmkflg;
#line 423 "Kmkmst.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 423 "Kmkmst.sqc"
      sql_setdlist[31].sqldata = (void*)&hsiumflg;
#line 423 "Kmkmst.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 9;
#line 423 "Kmkmst.sqc"
      sql_setdlist[32].sqldata = (void*)gmin;
#line 423 "Kmkmst.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 9;
#line 423 "Kmkmst.sqc"
      sql_setdlist[33].sqldata = (void*)ghaba;
#line 423 "Kmkmst.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[34].sqltype = 500; sql_setdlist[34].sqllen = 2;
#line 423 "Kmkmst.sqc"
      sql_setdlist[34].sqldata = (void*)&rrkhzn;
#line 423 "Kmkmst.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 423 "Kmkmst.sqc"
      sql_setdlist[35].sqldata = (void*)&nyuyouflg;
#line 423 "Kmkmst.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 423 "Kmkmst.sqc"
      sql_setdlist[36].sqldata = (void*)&tstrflg;
#line 423 "Kmkmst.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 423 "Kmkmst.sqc"
      sql_setdlist[37].sqldata = (void*)&kmksbt;
#line 423 "Kmkmst.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 423 "Kmkmst.sqc"
      sql_setdlist[38].sqldata = (void*)&sgchkflg;
#line 423 "Kmkmst.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 423 "Kmkmst.sqc"
      sql_setdlist[39].sqldata = (void*)&ksjhflg;
#line 423 "Kmkmst.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 423 "Kmkmst.sqc"
      sql_setdlist[40].sqldata = (void*)&kssgflg;
#line 423 "Kmkmst.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 423 "Kmkmst.sqc"
      sql_setdlist[41].sqldata = (void*)&xmskflg;
#line 423 "Kmkmst.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[42].sqltype = 452; sql_setdlist[42].sqllen = 1;
#line 423 "Kmkmst.sqc"
      sql_setdlist[42].sqldata = (void*)&xmchkflg;
#line 423 "Kmkmst.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[43].sqltype = 500; sql_setdlist[43].sqllen = 2;
#line 423 "Kmkmst.sqc"
      sql_setdlist[43].sqldata = (void*)&xmcount;
#line 423 "Kmkmst.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 11;
#line 423 "Kmkmst.sqc"
      sql_setdlist[44].sqldata = (void*)kaiymd;
#line 423 "Kmkmst.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 11;
#line 423 "Kmkmst.sqc"
      sql_setdlist[45].sqldata = (void*)haiymd;
#line 423 "Kmkmst.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 9;
#line 423 "Kmkmst.sqc"
      sql_setdlist[46].sqldata = (void*)hnktntid;
#line 423 "Kmkmst.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 27;
#line 423 "Kmkmst.sqc"
      sql_setdlist[47].sqldata = (void*)ksndh;
#line 423 "Kmkmst.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 423 "Kmkmst.sqc"
      sqlasetdata(3,0,48,sql_setdlist,0L,0L);
    }
#line 423 "Kmkmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 423 "Kmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 423 "Kmkmst.sqc"
  sqlastop(0L);
}

#line 423 "Kmkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kmkmst*)ZbmlRealloc( array,
                                    sizeof( Kmkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kmkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KmkmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 438 "Kmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 438 "Kmkmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 438 "Kmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 438 "Kmkmst.sqc"
  sqlastop(0L);
}

#line 438 "Kmkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 446 "Kmkmst.sqc"

    return sqlca.sqlcode;
}
long ZdbKmkmstSelectKey4( Kmkmst* pKey, Kmkmst** arrayOut, int* numOut )
{
    Kmkmst*     array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KmkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 460 "Kmkmst.sqc"


    
/*
EXEC SQL DECLARE c5 CURSOR FOR
    SELECT
		KNSGRP,
		KMKCD,
		KMKNM,
		KMKNMJ,
		KMKRS,
		KMKRSJ,
		KMKNME,
		KMKHSKNMJ,
		FKKMKNM,
		FKKMKNMJ,
		SMPCD,
		OYAKMKCD,
		KORRN,
		SECCD,
		STNFLG,
		SSTNKSU,
		ASSAY,
		FKJBN,
		FKBNKKB,
		TSKFLG,
		TKTFLG,
		LTMMNFLG,
		ZRKBN,
		BCRTJ,
		BCRSR,
		BCRSN,
		YKNKNSFLG,
		HRYNSU,
		JDHSKKA,
		HYJIJN,
		KSNKMKFLG,
		HSIUMFLG,
		GMIN,
		GHABA,
		RRKHZN,
		NYUYOUFLG,
		TSTRFLG,
		KMKSBT,
		SGCHKFLG,
		KSJHFLG,
		KSSGFLG,
		XMSKFLG,
		XMCHKFLG,
		XMCOUNT,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        KMKMST
    WHERE
		KMKCD = :kmkcd AND
		OYAKMKCD = :oyakmkcd AND
		KAIYMD <= CURRENT DATE FOR READ ONLY;
*/

#line 517 "Kmkmst.sqc"


    
/*
EXEC SQL OPEN c5;
*/

{
#line 519 "Kmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 519 "Kmkmst.sqc"
  sqlaaloc(2,2,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 519 "Kmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 519 "Kmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcd;
#line 519 "Kmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 519 "Kmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 519 "Kmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)oyakmkcd;
#line 519 "Kmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 519 "Kmkmst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 519 "Kmkmst.sqc"
  sqlacall((unsigned short)26,3,2,0,0L);
#line 519 "Kmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 519 "Kmkmst.sqc"
  sqlastop(0L);
}

#line 519 "Kmkmst.sqc"


    while( 1 ) {
        Kmkmst* rec;

        
/*
EXEC SQL FETCH c5 INTO
			:knsgrp,
			:kmkcd,
			:kmknm,
			:kmknmj,
			:kmkrs,
			:kmkrsj,
			:kmknme,
			:kmkhsknmj,
			:fkkmknm,
			:fkkmknmj,
			:smpcd,
			:oyakmkcd,
			:korrn,
			:seccd,
			:stnflg,
			:sstnksu,
			:assay,
			:fkjbn,
			:fkbnkkb,
			:tskflg,
			:tktflg,
			:ltmmnflg,
			:zrkbn,
			:bcrtj,
			:bcrsr,
			:bcrsn,
			:yknknsflg,
			:hrynsu,
			:jdhskka,
			:hyjijn,
			:ksnkmkflg,
			:hsiumflg,
			:gmin,
			:ghaba,
			:rrkhzn,
			:nyuyouflg,
			:tstrflg,
			:kmksbt,
			:sgchkflg,
			:ksjhflg,
			:kssgflg,
			:xmskflg,
			:xmchkflg,
			:xmcount,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 572 "Kmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 572 "Kmkmst.sqc"
  sqlaaloc(3,48,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[48];
#line 572 "Kmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 572 "Kmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 572 "Kmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 572 "Kmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 572 "Kmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 37;
#line 572 "Kmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmknm;
#line 572 "Kmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 47;
#line 572 "Kmkmst.sqc"
      sql_setdlist[3].sqldata = (void*)kmknmj;
#line 572 "Kmkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 572 "Kmkmst.sqc"
      sql_setdlist[4].sqldata = (void*)kmkrs;
#line 572 "Kmkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 572 "Kmkmst.sqc"
      sql_setdlist[5].sqldata = (void*)kmkrsj;
#line 572 "Kmkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 51;
#line 572 "Kmkmst.sqc"
      sql_setdlist[6].sqldata = (void*)kmknme;
#line 572 "Kmkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 21;
#line 572 "Kmkmst.sqc"
      sql_setdlist[7].sqldata = (void*)kmkhsknmj;
#line 572 "Kmkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 37;
#line 572 "Kmkmst.sqc"
      sql_setdlist[8].sqldata = (void*)fkkmknm;
#line 572 "Kmkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 47;
#line 572 "Kmkmst.sqc"
      sql_setdlist[9].sqldata = (void*)fkkmknmj;
#line 572 "Kmkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 8;
#line 572 "Kmkmst.sqc"
      sql_setdlist[10].sqldata = (void*)smpcd;
#line 572 "Kmkmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 8;
#line 572 "Kmkmst.sqc"
      sql_setdlist[11].sqldata = (void*)oyakmkcd;
#line 572 "Kmkmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 8;
#line 572 "Kmkmst.sqc"
      sql_setdlist[12].sqldata = (void*)korrn;
#line 572 "Kmkmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 3;
#line 572 "Kmkmst.sqc"
      sql_setdlist[13].sqldata = (void*)seccd;
#line 572 "Kmkmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 572 "Kmkmst.sqc"
      sql_setdlist[14].sqldata = (void*)&stnflg;
#line 572 "Kmkmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[15].sqltype = 500; sql_setdlist[15].sqllen = 2;
#line 572 "Kmkmst.sqc"
      sql_setdlist[15].sqldata = (void*)&sstnksu;
#line 572 "Kmkmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 41;
#line 572 "Kmkmst.sqc"
      sql_setdlist[16].sqldata = (void*)assay;
#line 572 "Kmkmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[17].sqltype = 500; sql_setdlist[17].sqllen = 2;
#line 572 "Kmkmst.sqc"
      sql_setdlist[17].sqldata = (void*)&fkjbn;
#line 572 "Kmkmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 572 "Kmkmst.sqc"
      sql_setdlist[18].sqldata = (void*)&fkbnkkb;
#line 572 "Kmkmst.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 3;
#line 572 "Kmkmst.sqc"
      sql_setdlist[19].sqldata = (void*)tskflg;
#line 572 "Kmkmst.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 3;
#line 572 "Kmkmst.sqc"
      sql_setdlist[20].sqldata = (void*)tktflg;
#line 572 "Kmkmst.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 572 "Kmkmst.sqc"
      sql_setdlist[21].sqldata = (void*)&ltmmnflg;
#line 572 "Kmkmst.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 572 "Kmkmst.sqc"
      sql_setdlist[22].sqldata = (void*)&zrkbn;
#line 572 "Kmkmst.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[23].sqltype = 496; sql_setdlist[23].sqllen = 4;
#line 572 "Kmkmst.sqc"
      sql_setdlist[23].sqldata = (void*)&bcrtj;
#line 572 "Kmkmst.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[24].sqltype = 496; sql_setdlist[24].sqllen = 4;
#line 572 "Kmkmst.sqc"
      sql_setdlist[24].sqldata = (void*)&bcrsr;
#line 572 "Kmkmst.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[25].sqltype = 496; sql_setdlist[25].sqllen = 4;
#line 572 "Kmkmst.sqc"
      sql_setdlist[25].sqldata = (void*)&bcrsn;
#line 572 "Kmkmst.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 572 "Kmkmst.sqc"
      sql_setdlist[26].sqldata = (void*)&yknknsflg;
#line 572 "Kmkmst.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[27].sqltype = 500; sql_setdlist[27].sqllen = 2;
#line 572 "Kmkmst.sqc"
      sql_setdlist[27].sqldata = (void*)&hrynsu;
#line 572 "Kmkmst.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 13;
#line 572 "Kmkmst.sqc"
      sql_setdlist[28].sqldata = (void*)jdhskka;
#line 572 "Kmkmst.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[29].sqltype = 500; sql_setdlist[29].sqllen = 2;
#line 572 "Kmkmst.sqc"
      sql_setdlist[29].sqldata = (void*)&hyjijn;
#line 572 "Kmkmst.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 572 "Kmkmst.sqc"
      sql_setdlist[30].sqldata = (void*)&ksnkmkflg;
#line 572 "Kmkmst.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 572 "Kmkmst.sqc"
      sql_setdlist[31].sqldata = (void*)&hsiumflg;
#line 572 "Kmkmst.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 9;
#line 572 "Kmkmst.sqc"
      sql_setdlist[32].sqldata = (void*)gmin;
#line 572 "Kmkmst.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 9;
#line 572 "Kmkmst.sqc"
      sql_setdlist[33].sqldata = (void*)ghaba;
#line 572 "Kmkmst.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[34].sqltype = 500; sql_setdlist[34].sqllen = 2;
#line 572 "Kmkmst.sqc"
      sql_setdlist[34].sqldata = (void*)&rrkhzn;
#line 572 "Kmkmst.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 572 "Kmkmst.sqc"
      sql_setdlist[35].sqldata = (void*)&nyuyouflg;
#line 572 "Kmkmst.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 572 "Kmkmst.sqc"
      sql_setdlist[36].sqldata = (void*)&tstrflg;
#line 572 "Kmkmst.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 572 "Kmkmst.sqc"
      sql_setdlist[37].sqldata = (void*)&kmksbt;
#line 572 "Kmkmst.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 572 "Kmkmst.sqc"
      sql_setdlist[38].sqldata = (void*)&sgchkflg;
#line 572 "Kmkmst.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 572 "Kmkmst.sqc"
      sql_setdlist[39].sqldata = (void*)&ksjhflg;
#line 572 "Kmkmst.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 572 "Kmkmst.sqc"
      sql_setdlist[40].sqldata = (void*)&kssgflg;
#line 572 "Kmkmst.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 572 "Kmkmst.sqc"
      sql_setdlist[41].sqldata = (void*)&xmskflg;
#line 572 "Kmkmst.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[42].sqltype = 452; sql_setdlist[42].sqllen = 1;
#line 572 "Kmkmst.sqc"
      sql_setdlist[42].sqldata = (void*)&xmchkflg;
#line 572 "Kmkmst.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[43].sqltype = 500; sql_setdlist[43].sqllen = 2;
#line 572 "Kmkmst.sqc"
      sql_setdlist[43].sqldata = (void*)&xmcount;
#line 572 "Kmkmst.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 11;
#line 572 "Kmkmst.sqc"
      sql_setdlist[44].sqldata = (void*)kaiymd;
#line 572 "Kmkmst.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 11;
#line 572 "Kmkmst.sqc"
      sql_setdlist[45].sqldata = (void*)haiymd;
#line 572 "Kmkmst.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 9;
#line 572 "Kmkmst.sqc"
      sql_setdlist[46].sqldata = (void*)hnktntid;
#line 572 "Kmkmst.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 27;
#line 572 "Kmkmst.sqc"
      sql_setdlist[47].sqldata = (void*)ksndh;
#line 572 "Kmkmst.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 572 "Kmkmst.sqc"
      sqlasetdata(3,0,48,sql_setdlist,0L,0L);
    }
#line 572 "Kmkmst.sqc"
  sqlacall((unsigned short)25,3,0,3,0L);
#line 572 "Kmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 572 "Kmkmst.sqc"
  sqlastop(0L);
}

#line 572 "Kmkmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kmkmst*)ZbmlRealloc( array,
                                    sizeof( Kmkmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kmkmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KmkmstArray );
    }

    
/*
EXEC SQL CLOSE c5;
*/

{
#line 587 "Kmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 587 "Kmkmst.sqc"
  sqlacall((unsigned short)20,3,0,0,0L);
#line 587 "Kmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 587 "Kmkmst.sqc"
  sqlastop(0L);
}

#line 587 "Kmkmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 595 "Kmkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKmkmstInsert()
 *    KMKMST レコードを挿入する
 * ■引数
 *    [I]  Kmkmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKmkmstInsert( Kmkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KmkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 618 "Kmkmst.sqc"


    
/*
EXEC SQL INSERT INTO KMKMST
    (
		KNSGRP,
		KMKCD,
		KMKNM,
		KMKNMJ,
		KMKRS,
		KMKRSJ,
		KMKNME,
		KMKHSKNMJ,
		FKKMKNM,
		FKKMKNMJ,
		SMPCD,
		OYAKMKCD,
		KORRN,
		SECCD,
		STNFLG,
		SSTNKSU,
		ASSAY,
		FKJBN,
		FKBNKKB,
		TSKFLG,
		TKTFLG,
		LTMMNFLG,
		ZRKBN,
		BCRTJ,
		BCRSR,
		BCRSN,
		YKNKNSFLG,
		HRYNSU,
		JDHSKKA,
		HYJIJN,
		KSNKMKFLG,
		HSIUMFLG,
		GMIN,
		GHABA,
		RRKHZN,
		NYUYOUFLG,
		TSTRFLG,
		KMKSBT,
		SGCHKFLG,
		KSJHFLG,
		KSSGFLG,
		XMSKFLG,
		XMCHKFLG,
		XMCOUNT,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:knsgrp,
		:kmkcd,
		:kmknm,
		:kmknmj,
		:kmkrs,
		:kmkrsj,
		:kmknme,
		:kmkhsknmj,
		:fkkmknm,
		:fkkmknmj,
		:smpcd,
		:oyakmkcd,
		:korrn,
		:seccd,
		:stnflg,
		:sstnksu,
		:assay,
		:fkjbn,
		:fkbnkkb,
		:tskflg,
		:tktflg,
		:ltmmnflg,
		:zrkbn,
		:bcrtj,
		:bcrsr,
		:bcrsn,
		:yknknsflg,
		:hrynsu,
		:jdhskka,
		:hyjijn,
		:ksnkmkflg,
		:hsiumflg,
		:gmin,
		:ghaba,
		:rrkhzn,
		:nyuyouflg,
		:tstrflg,
		:kmksbt,
		:sgchkflg,
		:ksjhflg,
		:kssgflg,
		:xmskflg,
		:xmchkflg,
		:xmcount,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 719 "Kmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 719 "Kmkmst.sqc"
  sqlaaloc(2,48,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[48];
#line 719 "Kmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 719 "Kmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 719 "Kmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 719 "Kmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 719 "Kmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 37;
#line 719 "Kmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmknm;
#line 719 "Kmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 47;
#line 719 "Kmkmst.sqc"
      sql_setdlist[3].sqldata = (void*)kmknmj;
#line 719 "Kmkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 719 "Kmkmst.sqc"
      sql_setdlist[4].sqldata = (void*)kmkrs;
#line 719 "Kmkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 719 "Kmkmst.sqc"
      sql_setdlist[5].sqldata = (void*)kmkrsj;
#line 719 "Kmkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 51;
#line 719 "Kmkmst.sqc"
      sql_setdlist[6].sqldata = (void*)kmknme;
#line 719 "Kmkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 21;
#line 719 "Kmkmst.sqc"
      sql_setdlist[7].sqldata = (void*)kmkhsknmj;
#line 719 "Kmkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 37;
#line 719 "Kmkmst.sqc"
      sql_setdlist[8].sqldata = (void*)fkkmknm;
#line 719 "Kmkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 47;
#line 719 "Kmkmst.sqc"
      sql_setdlist[9].sqldata = (void*)fkkmknmj;
#line 719 "Kmkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 8;
#line 719 "Kmkmst.sqc"
      sql_setdlist[10].sqldata = (void*)smpcd;
#line 719 "Kmkmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 8;
#line 719 "Kmkmst.sqc"
      sql_setdlist[11].sqldata = (void*)oyakmkcd;
#line 719 "Kmkmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 8;
#line 719 "Kmkmst.sqc"
      sql_setdlist[12].sqldata = (void*)korrn;
#line 719 "Kmkmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 3;
#line 719 "Kmkmst.sqc"
      sql_setdlist[13].sqldata = (void*)seccd;
#line 719 "Kmkmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 719 "Kmkmst.sqc"
      sql_setdlist[14].sqldata = (void*)&stnflg;
#line 719 "Kmkmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[15].sqltype = 500; sql_setdlist[15].sqllen = 2;
#line 719 "Kmkmst.sqc"
      sql_setdlist[15].sqldata = (void*)&sstnksu;
#line 719 "Kmkmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 41;
#line 719 "Kmkmst.sqc"
      sql_setdlist[16].sqldata = (void*)assay;
#line 719 "Kmkmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[17].sqltype = 500; sql_setdlist[17].sqllen = 2;
#line 719 "Kmkmst.sqc"
      sql_setdlist[17].sqldata = (void*)&fkjbn;
#line 719 "Kmkmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 719 "Kmkmst.sqc"
      sql_setdlist[18].sqldata = (void*)&fkbnkkb;
#line 719 "Kmkmst.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 3;
#line 719 "Kmkmst.sqc"
      sql_setdlist[19].sqldata = (void*)tskflg;
#line 719 "Kmkmst.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 3;
#line 719 "Kmkmst.sqc"
      sql_setdlist[20].sqldata = (void*)tktflg;
#line 719 "Kmkmst.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 719 "Kmkmst.sqc"
      sql_setdlist[21].sqldata = (void*)&ltmmnflg;
#line 719 "Kmkmst.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 719 "Kmkmst.sqc"
      sql_setdlist[22].sqldata = (void*)&zrkbn;
#line 719 "Kmkmst.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[23].sqltype = 496; sql_setdlist[23].sqllen = 4;
#line 719 "Kmkmst.sqc"
      sql_setdlist[23].sqldata = (void*)&bcrtj;
#line 719 "Kmkmst.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[24].sqltype = 496; sql_setdlist[24].sqllen = 4;
#line 719 "Kmkmst.sqc"
      sql_setdlist[24].sqldata = (void*)&bcrsr;
#line 719 "Kmkmst.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[25].sqltype = 496; sql_setdlist[25].sqllen = 4;
#line 719 "Kmkmst.sqc"
      sql_setdlist[25].sqldata = (void*)&bcrsn;
#line 719 "Kmkmst.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 719 "Kmkmst.sqc"
      sql_setdlist[26].sqldata = (void*)&yknknsflg;
#line 719 "Kmkmst.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[27].sqltype = 500; sql_setdlist[27].sqllen = 2;
#line 719 "Kmkmst.sqc"
      sql_setdlist[27].sqldata = (void*)&hrynsu;
#line 719 "Kmkmst.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 13;
#line 719 "Kmkmst.sqc"
      sql_setdlist[28].sqldata = (void*)jdhskka;
#line 719 "Kmkmst.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[29].sqltype = 500; sql_setdlist[29].sqllen = 2;
#line 719 "Kmkmst.sqc"
      sql_setdlist[29].sqldata = (void*)&hyjijn;
#line 719 "Kmkmst.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 719 "Kmkmst.sqc"
      sql_setdlist[30].sqldata = (void*)&ksnkmkflg;
#line 719 "Kmkmst.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 719 "Kmkmst.sqc"
      sql_setdlist[31].sqldata = (void*)&hsiumflg;
#line 719 "Kmkmst.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 9;
#line 719 "Kmkmst.sqc"
      sql_setdlist[32].sqldata = (void*)gmin;
#line 719 "Kmkmst.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 9;
#line 719 "Kmkmst.sqc"
      sql_setdlist[33].sqldata = (void*)ghaba;
#line 719 "Kmkmst.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[34].sqltype = 500; sql_setdlist[34].sqllen = 2;
#line 719 "Kmkmst.sqc"
      sql_setdlist[34].sqldata = (void*)&rrkhzn;
#line 719 "Kmkmst.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 719 "Kmkmst.sqc"
      sql_setdlist[35].sqldata = (void*)&nyuyouflg;
#line 719 "Kmkmst.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 719 "Kmkmst.sqc"
      sql_setdlist[36].sqldata = (void*)&tstrflg;
#line 719 "Kmkmst.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 719 "Kmkmst.sqc"
      sql_setdlist[37].sqldata = (void*)&kmksbt;
#line 719 "Kmkmst.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 719 "Kmkmst.sqc"
      sql_setdlist[38].sqldata = (void*)&sgchkflg;
#line 719 "Kmkmst.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 719 "Kmkmst.sqc"
      sql_setdlist[39].sqldata = (void*)&ksjhflg;
#line 719 "Kmkmst.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 719 "Kmkmst.sqc"
      sql_setdlist[40].sqldata = (void*)&kssgflg;
#line 719 "Kmkmst.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 719 "Kmkmst.sqc"
      sql_setdlist[41].sqldata = (void*)&xmskflg;
#line 719 "Kmkmst.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[42].sqltype = 452; sql_setdlist[42].sqllen = 1;
#line 719 "Kmkmst.sqc"
      sql_setdlist[42].sqldata = (void*)&xmchkflg;
#line 719 "Kmkmst.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[43].sqltype = 500; sql_setdlist[43].sqllen = 2;
#line 719 "Kmkmst.sqc"
      sql_setdlist[43].sqldata = (void*)&xmcount;
#line 719 "Kmkmst.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 11;
#line 719 "Kmkmst.sqc"
      sql_setdlist[44].sqldata = (void*)kaiymd;
#line 719 "Kmkmst.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 11;
#line 719 "Kmkmst.sqc"
      sql_setdlist[45].sqldata = (void*)haiymd;
#line 719 "Kmkmst.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 9;
#line 719 "Kmkmst.sqc"
      sql_setdlist[46].sqldata = (void*)hnktntid;
#line 719 "Kmkmst.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 27;
#line 719 "Kmkmst.sqc"
      sql_setdlist[47].sqldata = (void*)ksndh;
#line 719 "Kmkmst.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 719 "Kmkmst.sqc"
      sqlasetdata(2,0,48,sql_setdlist,0L,0L);
    }
#line 719 "Kmkmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 719 "Kmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 719 "Kmkmst.sqc"
  sqlastop(0L);
}

#line 719 "Kmkmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 724 "Kmkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKmkmstUpdate()
 *    KMKMST レコードを更新する
 * ■引数
 *    [I]  Kmkmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKmkmstUpdate( Kmkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KmkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 748 "Kmkmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 749 "Kmkmst.sqc"


    
/*
EXEC SQL UPDATE KMKMST
    SET (
		KMKNM,
		KMKNMJ,
		KMKRS,
		KMKRSJ,
		KMKNME,
		KMKHSKNMJ,
		FKKMKNM,
		FKKMKNMJ,
		SMPCD,
		OYAKMKCD,
		KORRN,
		SECCD,
		STNFLG,
		SSTNKSU,
		ASSAY,
		FKJBN,
		FKBNKKB,
		TSKFLG,
		TKTFLG,
		LTMMNFLG,
		ZRKBN,
		BCRTJ,
		BCRSR,
		BCRSN,
		YKNKNSFLG,
		HRYNSU,
		JDHSKKA,
		HYJIJN,
		KSNKMKFLG,
		HSIUMFLG,
		GMIN,
		GHABA,
		RRKHZN,
		NYUYOUFLG,
		TSTRFLG,
		KMKSBT,
		SGCHKFLG,
		KSJHFLG,
		KSSGFLG,
		XMSKFLG,
		XMCHKFLG,
		XMCOUNT,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:kmknm,
		:kmknmj,
		:kmkrs,
		:kmkrsj,
		:kmknme,
		:kmkhsknmj,
		:fkkmknm,
		:fkkmknmj,
		:smpcd,
		:oyakmkcd,
		:korrn,
		:seccd,
		:stnflg,
		:sstnksu,
		:assay,
		:fkjbn,
		:fkbnkkb,
		:tskflg,
		:tktflg,
		:ltmmnflg,
		:zrkbn,
		:bcrtj,
		:bcrsr,
		:bcrsn,
		:yknknsflg,
		:hrynsu,
		:jdhskka,
		:hyjijn,
		:ksnkmkflg,
		:hsiumflg,
		:gmin,
		:ghaba,
		:rrkhzn,
		:nyuyouflg,
		:tstrflg,
		:kmksbt,
		:sgchkflg,
		:ksjhflg,
		:kssgflg,
		:xmskflg,
		:xmchkflg,
		:xmcount,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KAIYMD = :kaiymd;
*/

{
#line 847 "Kmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 847 "Kmkmst.sqc"
  sqlaaloc(2,48,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[48];
#line 847 "Kmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 37;
#line 847 "Kmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmknm;
#line 847 "Kmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 47;
#line 847 "Kmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmknmj;
#line 847 "Kmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 17;
#line 847 "Kmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)kmkrs;
#line 847 "Kmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 21;
#line 847 "Kmkmst.sqc"
      sql_setdlist[3].sqldata = (void*)kmkrsj;
#line 847 "Kmkmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 51;
#line 847 "Kmkmst.sqc"
      sql_setdlist[4].sqldata = (void*)kmknme;
#line 847 "Kmkmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 847 "Kmkmst.sqc"
      sql_setdlist[5].sqldata = (void*)kmkhsknmj;
#line 847 "Kmkmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 37;
#line 847 "Kmkmst.sqc"
      sql_setdlist[6].sqldata = (void*)fkkmknm;
#line 847 "Kmkmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 47;
#line 847 "Kmkmst.sqc"
      sql_setdlist[7].sqldata = (void*)fkkmknmj;
#line 847 "Kmkmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 8;
#line 847 "Kmkmst.sqc"
      sql_setdlist[8].sqldata = (void*)smpcd;
#line 847 "Kmkmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 8;
#line 847 "Kmkmst.sqc"
      sql_setdlist[9].sqldata = (void*)oyakmkcd;
#line 847 "Kmkmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 8;
#line 847 "Kmkmst.sqc"
      sql_setdlist[10].sqldata = (void*)korrn;
#line 847 "Kmkmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 3;
#line 847 "Kmkmst.sqc"
      sql_setdlist[11].sqldata = (void*)seccd;
#line 847 "Kmkmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[12].sqltype = 452; sql_setdlist[12].sqllen = 1;
#line 847 "Kmkmst.sqc"
      sql_setdlist[12].sqldata = (void*)&stnflg;
#line 847 "Kmkmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 847 "Kmkmst.sqc"
      sql_setdlist[13].sqldata = (void*)&sstnksu;
#line 847 "Kmkmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 41;
#line 847 "Kmkmst.sqc"
      sql_setdlist[14].sqldata = (void*)assay;
#line 847 "Kmkmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[15].sqltype = 500; sql_setdlist[15].sqllen = 2;
#line 847 "Kmkmst.sqc"
      sql_setdlist[15].sqldata = (void*)&fkjbn;
#line 847 "Kmkmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 847 "Kmkmst.sqc"
      sql_setdlist[16].sqldata = (void*)&fkbnkkb;
#line 847 "Kmkmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 3;
#line 847 "Kmkmst.sqc"
      sql_setdlist[17].sqldata = (void*)tskflg;
#line 847 "Kmkmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 3;
#line 847 "Kmkmst.sqc"
      sql_setdlist[18].sqldata = (void*)tktflg;
#line 847 "Kmkmst.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 847 "Kmkmst.sqc"
      sql_setdlist[19].sqldata = (void*)&ltmmnflg;
#line 847 "Kmkmst.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 847 "Kmkmst.sqc"
      sql_setdlist[20].sqldata = (void*)&zrkbn;
#line 847 "Kmkmst.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[21].sqltype = 496; sql_setdlist[21].sqllen = 4;
#line 847 "Kmkmst.sqc"
      sql_setdlist[21].sqldata = (void*)&bcrtj;
#line 847 "Kmkmst.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[22].sqltype = 496; sql_setdlist[22].sqllen = 4;
#line 847 "Kmkmst.sqc"
      sql_setdlist[22].sqldata = (void*)&bcrsr;
#line 847 "Kmkmst.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[23].sqltype = 496; sql_setdlist[23].sqllen = 4;
#line 847 "Kmkmst.sqc"
      sql_setdlist[23].sqldata = (void*)&bcrsn;
#line 847 "Kmkmst.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 847 "Kmkmst.sqc"
      sql_setdlist[24].sqldata = (void*)&yknknsflg;
#line 847 "Kmkmst.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[25].sqltype = 500; sql_setdlist[25].sqllen = 2;
#line 847 "Kmkmst.sqc"
      sql_setdlist[25].sqldata = (void*)&hrynsu;
#line 847 "Kmkmst.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 13;
#line 847 "Kmkmst.sqc"
      sql_setdlist[26].sqldata = (void*)jdhskka;
#line 847 "Kmkmst.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[27].sqltype = 500; sql_setdlist[27].sqllen = 2;
#line 847 "Kmkmst.sqc"
      sql_setdlist[27].sqldata = (void*)&hyjijn;
#line 847 "Kmkmst.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 847 "Kmkmst.sqc"
      sql_setdlist[28].sqldata = (void*)&ksnkmkflg;
#line 847 "Kmkmst.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 847 "Kmkmst.sqc"
      sql_setdlist[29].sqldata = (void*)&hsiumflg;
#line 847 "Kmkmst.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 9;
#line 847 "Kmkmst.sqc"
      sql_setdlist[30].sqldata = (void*)gmin;
#line 847 "Kmkmst.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 9;
#line 847 "Kmkmst.sqc"
      sql_setdlist[31].sqldata = (void*)ghaba;
#line 847 "Kmkmst.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[32].sqltype = 500; sql_setdlist[32].sqllen = 2;
#line 847 "Kmkmst.sqc"
      sql_setdlist[32].sqldata = (void*)&rrkhzn;
#line 847 "Kmkmst.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 847 "Kmkmst.sqc"
      sql_setdlist[33].sqldata = (void*)&nyuyouflg;
#line 847 "Kmkmst.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 847 "Kmkmst.sqc"
      sql_setdlist[34].sqldata = (void*)&tstrflg;
#line 847 "Kmkmst.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 847 "Kmkmst.sqc"
      sql_setdlist[35].sqldata = (void*)&kmksbt;
#line 847 "Kmkmst.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 847 "Kmkmst.sqc"
      sql_setdlist[36].sqldata = (void*)&sgchkflg;
#line 847 "Kmkmst.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 847 "Kmkmst.sqc"
      sql_setdlist[37].sqldata = (void*)&ksjhflg;
#line 847 "Kmkmst.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 847 "Kmkmst.sqc"
      sql_setdlist[38].sqldata = (void*)&kssgflg;
#line 847 "Kmkmst.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 847 "Kmkmst.sqc"
      sql_setdlist[39].sqldata = (void*)&xmskflg;
#line 847 "Kmkmst.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 847 "Kmkmst.sqc"
      sql_setdlist[40].sqldata = (void*)&xmchkflg;
#line 847 "Kmkmst.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[41].sqltype = 500; sql_setdlist[41].sqllen = 2;
#line 847 "Kmkmst.sqc"
      sql_setdlist[41].sqldata = (void*)&xmcount;
#line 847 "Kmkmst.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 11;
#line 847 "Kmkmst.sqc"
      sql_setdlist[42].sqldata = (void*)haiymd;
#line 847 "Kmkmst.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 9;
#line 847 "Kmkmst.sqc"
      sql_setdlist[43].sqldata = (void*)hnktntid;
#line 847 "Kmkmst.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 27;
#line 847 "Kmkmst.sqc"
      sql_setdlist[44].sqldata = (void*)ksndh;
#line 847 "Kmkmst.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 17;
#line 847 "Kmkmst.sqc"
      sql_setdlist[45].sqldata = (void*)knsgrp;
#line 847 "Kmkmst.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 8;
#line 847 "Kmkmst.sqc"
      sql_setdlist[46].sqldata = (void*)kmkcd;
#line 847 "Kmkmst.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 11;
#line 847 "Kmkmst.sqc"
      sql_setdlist[47].sqldata = (void*)kaiymd;
#line 847 "Kmkmst.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 847 "Kmkmst.sqc"
      sqlasetdata(2,0,48,sql_setdlist,0L,0L);
    }
#line 847 "Kmkmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 847 "Kmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 847 "Kmkmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 847 "Kmkmst.sqc"
  sqlastop(0L);
}

#line 847 "Kmkmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 852 "Kmkmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 856 "Kmkmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKmkmstDelete()
 *    KMKMST レコードを削除する
 * ■引数
 *    [I]  Kmkmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKmkmstDelete( Kmkmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KmkmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 880 "Kmkmst.sqc"


    
/*
EXEC SQL DELETE FROM KMKMST
    WHERE
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KAIYMD = :kaiymd;
*/

{
#line 886 "Kmkmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 886 "Kmkmst.sqc"
  sqlaaloc(2,3,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 886 "Kmkmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 886 "Kmkmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 886 "Kmkmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 886 "Kmkmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 886 "Kmkmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 886 "Kmkmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 886 "Kmkmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 886 "Kmkmst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 886 "Kmkmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 886 "Kmkmst.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 886 "Kmkmst.sqc"
  sqlacall((unsigned short)24,6,2,0,0L);
#line 886 "Kmkmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 886 "Kmkmst.sqc"
  sqlastop(0L);
}

#line 886 "Kmkmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 891 "Kmkmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
