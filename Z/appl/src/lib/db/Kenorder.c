static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,80,66,83,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,51,48,90,75,69,78,79,32,0,0,0,0,0,0,0,0,
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


#line 1 "Kenorder.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Kenorder.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Kenorder.h"
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


#line 24 "Kenorder.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Kenorder.sqc"

	char    knskisymd[11];
	char    sriymd[11];
	char    kntno[14];
	char    kntketflg;
	char    knsgrp[17];
	char    kmkcd[8];
	short   knssu;
	short   knssueda;
	char    irihsmkbn;
	char    irikbn;
	char    ksktkbn;
	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    sstcd[8];
	char    trid[11];
	short   trpos;
	char    asyrckid[11];
	short   asyrckpos;
	char    oyakmkcd[8];
	char    seccd[3];
	char    bkfkkbn;
	char    smpcd[8];
	char    bskkbn[5];
	char    nbkmkcd[8];
	char    zrcd[5];
	char    ysnlbl[3];
	char    kjno[4];
	char    fkhkknohjkbn;
	char    tbkjno[4];
	char    tbkjflg;
	char    htkfkhms[25];
	char    skflg;
	char    tskflg[3];
	char    tktflg[3];
	char    ytiksbr[16];
	char    kkflg;
	char    kkiriflg;
	short   kkirilotno;
	char    sc[6];
	char    tj[6];
	char    tjtni;
	char    sbtkbn;
	char    birthday[9];
	char    birthdaykbn;
	char    age[4];
	char    agekbn;
	char    sstme[9];
	char    ssymd[11];
	char    tntme[5];
	char    tntni;
	char    tnryo[6];
	char    tnryotni;
	sqlint32  knsseq;
	short   bthno;
	char    knsjkflg;
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 88 "Kenorder.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Kenorder

BmlDMMInfo	KenorderArray[] = {
	DMM_SDATE( knskisymd ),
	DMM_SDATE( sriymd ),
	DMM_SSTRING( kntno ),
	DMM_SCHAR( kntketflg ),
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSHORT( knssu ),
	DMM_SSHORT( knssueda ),
	DMM_SCHAR( irihsmkbn ),
	DMM_SCHAR( irikbn ),
	DMM_SCHAR( ksktkbn ),
	DMM_SDATE( utkymd ),
	DMM_SSTRING( irino ),
	DMM_SCHAR( iriketflg ),
	DMM_SSHORT( zssdino ),
	DMM_SSTRING( sstcd ),
	DMM_SSTRING( trid ),
	DMM_SSHORT( trpos ),
	DMM_SSTRING( asyrckid ),
	DMM_SSHORT( asyrckpos ),
	DMM_SSTRING( oyakmkcd ),
	DMM_SSTRING( seccd ),
	DMM_SCHAR( bkfkkbn ),
	DMM_SSTRING( smpcd ),
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( nbkmkcd ),
	DMM_SSTRING( zrcd ),
	DMM_SSTRING( ysnlbl ),
	DMM_SSTRING( kjno ),
	DMM_SCHAR( fkhkknohjkbn ),
	DMM_SSTRING( tbkjno ),
	DMM_SCHAR( tbkjflg ),
	DMM_SSTRING( htkfkhms ),
	DMM_SCHAR( skflg ),
	DMM_SSTRING( tskflg ),
	DMM_SSTRING( tktflg ),
	DMM_SSTRING( ytiksbr ),
	DMM_SCHAR( kkflg ),
	DMM_SCHAR( kkiriflg ),
	DMM_SSHORT( kkirilotno ),
	DMM_SSTRING( sc ),
	DMM_SSTRING( tj ),
	DMM_SCHAR( tjtni ),
	DMM_SCHAR( sbtkbn ),
	DMM_SSTRING( birthday ),
	DMM_SCHAR( birthdaykbn ),
	DMM_SSTRING( age ),
	DMM_SCHAR( agekbn ),
	DMM_STIME( sstme ),
	DMM_SDATE( ssymd ),
	DMM_SSTRING( tntme ),
	DMM_SCHAR( tntni ),
	DMM_SSTRING( tnryo ),
	DMM_SCHAR( tnryotni ),
	DMM_SLONG( knsseq ),
	DMM_SSHORT( bthno ),
	DMM_SCHAR( knsjkflg ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKenorderSelectAll()
 *    KENORDER レコード全件取得
 * ■引数
 *    [O]  Kenorder** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKenorderSelectAll( Kenorder** arrayOut, int* numOut )
{
    Kenorder*   array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 174 "Kenorder.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSKISYMD,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		KNSGRP,
		KMKCD,
		KNSSU,
		KNSSUEDA,
		IRIHSMKBN,
		IRIKBN,
		KSKTKBN,
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		SSTCD,
		TRID,
		TRPOS,
		ASYRCKID,
		ASYRCKPOS,
		OYAKMKCD,
		SECCD,
		BKFKKBN,
		SMPCD,
		BSKKBN,
		NBKMKCD,
		ZRCD,
		YSNLBL,
		KJNO,
		FKHKKNOHJKBN,
		TBKJNO,
		TBKJFLG,
		HTKFKHMS,
		SKFLG,
		TSKFLG,
		TKTFLG,
		YTIKSBR,
		KKFLG,
		KKIRIFLG,
		KKIRILOTNO,
		SC,
		TJ,
		TJTNI,
		SBTKBN,
		BIRTHDAY,
		BIRTHDAYKBN,
		AGE,
		AGEKBN,
		SSTME,
		SSYMD,
		TNTME,
		TNTNI,
		TNRYO,
		TNRYOTNI,
		KNSSEQ,
		BTHNO,
		KNSJKFLG,
		KSNDH
    FROM
        KENORDER FOR READ ONLY;
*/

#line 237 "Kenorder.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 239 "Kenorder.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 239 "Kenorder.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 239 "Kenorder.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 239 "Kenorder.sqc"
  sqlastop(0L);
}

#line 239 "Kenorder.sqc"


    while( 1 ) {
        Kenorder* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knskisymd,
			:sriymd,
			:kntno,
			:kntketflg,
			:knsgrp,
			:kmkcd,
			:knssu,
			:knssueda,
			:irihsmkbn,
			:irikbn,
			:ksktkbn,
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:sstcd,
			:trid,
			:trpos,
			:asyrckid,
			:asyrckpos,
			:oyakmkcd,
			:seccd,
			:bkfkkbn,
			:smpcd,
			:bskkbn,
			:nbkmkcd,
			:zrcd,
			:ysnlbl,
			:kjno,
			:fkhkknohjkbn,
			:tbkjno,
			:tbkjflg,
			:htkfkhms,
			:skflg,
			:tskflg,
			:tktflg,
			:ytiksbr,
			:kkflg,
			:kkiriflg,
			:kkirilotno,
			:sc,
			:tj,
			:tjtni,
			:sbtkbn,
			:birthday,
			:birthdaykbn,
			:age,
			:agekbn,
			:sstme,
			:ssymd,
			:tntme,
			:tntni,
			:tnryo,
			:tnryotni,
			:knsseq,
			:bthno,
			:knsjkflg,
			:ksndh;
*/

{
#line 302 "Kenorder.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 302 "Kenorder.sqc"
  sqlaaloc(3,58,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[58];
#line 302 "Kenorder.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 302 "Kenorder.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 302 "Kenorder.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 302 "Kenorder.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 302 "Kenorder.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 302 "Kenorder.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 302 "Kenorder.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 302 "Kenorder.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 302 "Kenorder.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 302 "Kenorder.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 302 "Kenorder.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 302 "Kenorder.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 302 "Kenorder.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 302 "Kenorder.sqc"
      sql_setdlist[6].sqldata = (void*)&knssu;
#line 302 "Kenorder.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 302 "Kenorder.sqc"
      sql_setdlist[7].sqldata = (void*)&knssueda;
#line 302 "Kenorder.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 302 "Kenorder.sqc"
      sql_setdlist[8].sqldata = (void*)&irihsmkbn;
#line 302 "Kenorder.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 302 "Kenorder.sqc"
      sql_setdlist[9].sqldata = (void*)&irikbn;
#line 302 "Kenorder.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 302 "Kenorder.sqc"
      sql_setdlist[10].sqldata = (void*)&ksktkbn;
#line 302 "Kenorder.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 302 "Kenorder.sqc"
      sql_setdlist[11].sqldata = (void*)utkymd;
#line 302 "Kenorder.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 12;
#line 302 "Kenorder.sqc"
      sql_setdlist[12].sqldata = (void*)irino;
#line 302 "Kenorder.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 302 "Kenorder.sqc"
      sql_setdlist[13].sqldata = (void*)&iriketflg;
#line 302 "Kenorder.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 302 "Kenorder.sqc"
      sql_setdlist[14].sqldata = (void*)&zssdino;
#line 302 "Kenorder.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 302 "Kenorder.sqc"
      sql_setdlist[15].sqldata = (void*)sstcd;
#line 302 "Kenorder.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 11;
#line 302 "Kenorder.sqc"
      sql_setdlist[16].sqldata = (void*)trid;
#line 302 "Kenorder.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[17].sqltype = 500; sql_setdlist[17].sqllen = 2;
#line 302 "Kenorder.sqc"
      sql_setdlist[17].sqldata = (void*)&trpos;
#line 302 "Kenorder.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 11;
#line 302 "Kenorder.sqc"
      sql_setdlist[18].sqldata = (void*)asyrckid;
#line 302 "Kenorder.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 302 "Kenorder.sqc"
      sql_setdlist[19].sqldata = (void*)&asyrckpos;
#line 302 "Kenorder.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 8;
#line 302 "Kenorder.sqc"
      sql_setdlist[20].sqldata = (void*)oyakmkcd;
#line 302 "Kenorder.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 3;
#line 302 "Kenorder.sqc"
      sql_setdlist[21].sqldata = (void*)seccd;
#line 302 "Kenorder.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 302 "Kenorder.sqc"
      sql_setdlist[22].sqldata = (void*)&bkfkkbn;
#line 302 "Kenorder.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 302 "Kenorder.sqc"
      sql_setdlist[23].sqldata = (void*)smpcd;
#line 302 "Kenorder.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 5;
#line 302 "Kenorder.sqc"
      sql_setdlist[24].sqldata = (void*)bskkbn;
#line 302 "Kenorder.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 8;
#line 302 "Kenorder.sqc"
      sql_setdlist[25].sqldata = (void*)nbkmkcd;
#line 302 "Kenorder.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 5;
#line 302 "Kenorder.sqc"
      sql_setdlist[26].sqldata = (void*)zrcd;
#line 302 "Kenorder.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 3;
#line 302 "Kenorder.sqc"
      sql_setdlist[27].sqldata = (void*)ysnlbl;
#line 302 "Kenorder.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 4;
#line 302 "Kenorder.sqc"
      sql_setdlist[28].sqldata = (void*)kjno;
#line 302 "Kenorder.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 302 "Kenorder.sqc"
      sql_setdlist[29].sqldata = (void*)&fkhkknohjkbn;
#line 302 "Kenorder.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 4;
#line 302 "Kenorder.sqc"
      sql_setdlist[30].sqldata = (void*)tbkjno;
#line 302 "Kenorder.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 302 "Kenorder.sqc"
      sql_setdlist[31].sqldata = (void*)&tbkjflg;
#line 302 "Kenorder.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 25;
#line 302 "Kenorder.sqc"
      sql_setdlist[32].sqldata = (void*)htkfkhms;
#line 302 "Kenorder.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 302 "Kenorder.sqc"
      sql_setdlist[33].sqldata = (void*)&skflg;
#line 302 "Kenorder.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 3;
#line 302 "Kenorder.sqc"
      sql_setdlist[34].sqldata = (void*)tskflg;
#line 302 "Kenorder.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 3;
#line 302 "Kenorder.sqc"
      sql_setdlist[35].sqldata = (void*)tktflg;
#line 302 "Kenorder.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 16;
#line 302 "Kenorder.sqc"
      sql_setdlist[36].sqldata = (void*)ytiksbr;
#line 302 "Kenorder.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 302 "Kenorder.sqc"
      sql_setdlist[37].sqldata = (void*)&kkflg;
#line 302 "Kenorder.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 302 "Kenorder.sqc"
      sql_setdlist[38].sqldata = (void*)&kkiriflg;
#line 302 "Kenorder.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[39].sqltype = 500; sql_setdlist[39].sqllen = 2;
#line 302 "Kenorder.sqc"
      sql_setdlist[39].sqldata = (void*)&kkirilotno;
#line 302 "Kenorder.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 6;
#line 302 "Kenorder.sqc"
      sql_setdlist[40].sqldata = (void*)sc;
#line 302 "Kenorder.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 6;
#line 302 "Kenorder.sqc"
      sql_setdlist[41].sqldata = (void*)tj;
#line 302 "Kenorder.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[42].sqltype = 452; sql_setdlist[42].sqllen = 1;
#line 302 "Kenorder.sqc"
      sql_setdlist[42].sqldata = (void*)&tjtni;
#line 302 "Kenorder.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 302 "Kenorder.sqc"
      sql_setdlist[43].sqldata = (void*)&sbtkbn;
#line 302 "Kenorder.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 9;
#line 302 "Kenorder.sqc"
      sql_setdlist[44].sqldata = (void*)birthday;
#line 302 "Kenorder.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[45].sqltype = 452; sql_setdlist[45].sqllen = 1;
#line 302 "Kenorder.sqc"
      sql_setdlist[45].sqldata = (void*)&birthdaykbn;
#line 302 "Kenorder.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 4;
#line 302 "Kenorder.sqc"
      sql_setdlist[46].sqldata = (void*)age;
#line 302 "Kenorder.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 302 "Kenorder.sqc"
      sql_setdlist[47].sqldata = (void*)&agekbn;
#line 302 "Kenorder.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 9;
#line 302 "Kenorder.sqc"
      sql_setdlist[48].sqldata = (void*)sstme;
#line 302 "Kenorder.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 11;
#line 302 "Kenorder.sqc"
      sql_setdlist[49].sqldata = (void*)ssymd;
#line 302 "Kenorder.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 5;
#line 302 "Kenorder.sqc"
      sql_setdlist[50].sqldata = (void*)tntme;
#line 302 "Kenorder.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[51].sqltype = 452; sql_setdlist[51].sqllen = 1;
#line 302 "Kenorder.sqc"
      sql_setdlist[51].sqldata = (void*)&tntni;
#line 302 "Kenorder.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 6;
#line 302 "Kenorder.sqc"
      sql_setdlist[52].sqldata = (void*)tnryo;
#line 302 "Kenorder.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[53].sqltype = 452; sql_setdlist[53].sqllen = 1;
#line 302 "Kenorder.sqc"
      sql_setdlist[53].sqldata = (void*)&tnryotni;
#line 302 "Kenorder.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[54].sqltype = 496; sql_setdlist[54].sqllen = 4;
#line 302 "Kenorder.sqc"
      sql_setdlist[54].sqldata = (void*)&knsseq;
#line 302 "Kenorder.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[55].sqltype = 500; sql_setdlist[55].sqllen = 2;
#line 302 "Kenorder.sqc"
      sql_setdlist[55].sqldata = (void*)&bthno;
#line 302 "Kenorder.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[56].sqltype = 452; sql_setdlist[56].sqllen = 1;
#line 302 "Kenorder.sqc"
      sql_setdlist[56].sqldata = (void*)&knsjkflg;
#line 302 "Kenorder.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 27;
#line 302 "Kenorder.sqc"
      sql_setdlist[57].sqldata = (void*)ksndh;
#line 302 "Kenorder.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 302 "Kenorder.sqc"
      sqlasetdata(3,0,58,sql_setdlist,0L,0L);
    }
#line 302 "Kenorder.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 302 "Kenorder.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 302 "Kenorder.sqc"
  sqlastop(0L);
}

#line 302 "Kenorder.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kenorder*)ZbmlRealloc( array,
                                    sizeof( Kenorder ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kenorder ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KenorderArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 317 "Kenorder.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 317 "Kenorder.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 317 "Kenorder.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 317 "Kenorder.sqc"
  sqlastop(0L);
}

#line 317 "Kenorder.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 325 "Kenorder.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKenorderSelectKey()
 *    KENORDER レコードKey条件取得
 * ■引数
 *    [I]  Kenorder* pKey       取得するレコードのキー
 *    [O]  Kenorder** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKenorderSelectKey( Kenorder* pKey, Kenorder** arrayOut, int* numOut )
{
    Kenorder*   array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KenorderArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 351 "Kenorder.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSKISYMD,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		KNSGRP,
		KMKCD,
		KNSSU,
		KNSSUEDA,
		IRIHSMKBN,
		IRIKBN,
		KSKTKBN,
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		SSTCD,
		TRID,
		TRPOS,
		ASYRCKID,
		ASYRCKPOS,
		OYAKMKCD,
		SECCD,
		BKFKKBN,
		SMPCD,
		BSKKBN,
		NBKMKCD,
		ZRCD,
		YSNLBL,
		KJNO,
		FKHKKNOHJKBN,
		TBKJNO,
		TBKJFLG,
		HTKFKHMS,
		SKFLG,
		TSKFLG,
		TKTFLG,
		YTIKSBR,
		KKFLG,
		KKIRIFLG,
		KKIRILOTNO,
		SC,
		TJ,
		TJTNI,
		SBTKBN,
		BIRTHDAY,
		BIRTHDAYKBN,
		AGE,
		AGEKBN,
		SSTME,
		SSYMD,
		TNTME,
		TNTNI,
		TNRYO,
		TNRYOTNI,
		KNSSEQ,
		BTHNO,
		KNSJKFLG,
		KSNDH
    FROM
        KENORDER
    WHERE
		KNTNO = :kntno AND
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd AND
		KNSSU = :knssu AND
		KNSSUEDA = :knssueda AND
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd FOR READ ONLY;
*/

#line 422 "Kenorder.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 424 "Kenorder.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 424 "Kenorder.sqc"
  sqlaaloc(2,7,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 424 "Kenorder.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 14;
#line 424 "Kenorder.sqc"
      sql_setdlist[0].sqldata = (void*)kntno;
#line 424 "Kenorder.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 424 "Kenorder.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 424 "Kenorder.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 424 "Kenorder.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 424 "Kenorder.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 424 "Kenorder.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 424 "Kenorder.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 424 "Kenorder.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 424 "Kenorder.sqc"
      sql_setdlist[3].sqldata = (void*)&knssu;
#line 424 "Kenorder.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 424 "Kenorder.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 424 "Kenorder.sqc"
      sql_setdlist[4].sqldata = (void*)&knssueda;
#line 424 "Kenorder.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 424 "Kenorder.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 424 "Kenorder.sqc"
      sql_setdlist[5].sqldata = (void*)knskisymd;
#line 424 "Kenorder.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 424 "Kenorder.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 424 "Kenorder.sqc"
      sql_setdlist[6].sqldata = (void*)sriymd;
#line 424 "Kenorder.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 424 "Kenorder.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 424 "Kenorder.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 424 "Kenorder.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 424 "Kenorder.sqc"
  sqlastop(0L);
}

#line 424 "Kenorder.sqc"


    while( 1 ) {
        Kenorder* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knskisymd,
			:sriymd,
			:kntno,
			:kntketflg,
			:knsgrp,
			:kmkcd,
			:knssu,
			:knssueda,
			:irihsmkbn,
			:irikbn,
			:ksktkbn,
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:sstcd,
			:trid,
			:trpos,
			:asyrckid,
			:asyrckpos,
			:oyakmkcd,
			:seccd,
			:bkfkkbn,
			:smpcd,
			:bskkbn,
			:nbkmkcd,
			:zrcd,
			:ysnlbl,
			:kjno,
			:fkhkknohjkbn,
			:tbkjno,
			:tbkjflg,
			:htkfkhms,
			:skflg,
			:tskflg,
			:tktflg,
			:ytiksbr,
			:kkflg,
			:kkiriflg,
			:kkirilotno,
			:sc,
			:tj,
			:tjtni,
			:sbtkbn,
			:birthday,
			:birthdaykbn,
			:age,
			:agekbn,
			:sstme,
			:ssymd,
			:tntme,
			:tntni,
			:tnryo,
			:tnryotni,
			:knsseq,
			:bthno,
			:knsjkflg,
			:ksndh;
*/

{
#line 487 "Kenorder.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 487 "Kenorder.sqc"
  sqlaaloc(3,58,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[58];
#line 487 "Kenorder.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 487 "Kenorder.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 487 "Kenorder.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 487 "Kenorder.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 487 "Kenorder.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 487 "Kenorder.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 487 "Kenorder.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 487 "Kenorder.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 487 "Kenorder.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 487 "Kenorder.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 487 "Kenorder.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 487 "Kenorder.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 487 "Kenorder.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 487 "Kenorder.sqc"
      sql_setdlist[6].sqldata = (void*)&knssu;
#line 487 "Kenorder.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 487 "Kenorder.sqc"
      sql_setdlist[7].sqldata = (void*)&knssueda;
#line 487 "Kenorder.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 487 "Kenorder.sqc"
      sql_setdlist[8].sqldata = (void*)&irihsmkbn;
#line 487 "Kenorder.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 487 "Kenorder.sqc"
      sql_setdlist[9].sqldata = (void*)&irikbn;
#line 487 "Kenorder.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 487 "Kenorder.sqc"
      sql_setdlist[10].sqldata = (void*)&ksktkbn;
#line 487 "Kenorder.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 487 "Kenorder.sqc"
      sql_setdlist[11].sqldata = (void*)utkymd;
#line 487 "Kenorder.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 12;
#line 487 "Kenorder.sqc"
      sql_setdlist[12].sqldata = (void*)irino;
#line 487 "Kenorder.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 487 "Kenorder.sqc"
      sql_setdlist[13].sqldata = (void*)&iriketflg;
#line 487 "Kenorder.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 487 "Kenorder.sqc"
      sql_setdlist[14].sqldata = (void*)&zssdino;
#line 487 "Kenorder.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 487 "Kenorder.sqc"
      sql_setdlist[15].sqldata = (void*)sstcd;
#line 487 "Kenorder.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 11;
#line 487 "Kenorder.sqc"
      sql_setdlist[16].sqldata = (void*)trid;
#line 487 "Kenorder.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[17].sqltype = 500; sql_setdlist[17].sqllen = 2;
#line 487 "Kenorder.sqc"
      sql_setdlist[17].sqldata = (void*)&trpos;
#line 487 "Kenorder.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 11;
#line 487 "Kenorder.sqc"
      sql_setdlist[18].sqldata = (void*)asyrckid;
#line 487 "Kenorder.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 487 "Kenorder.sqc"
      sql_setdlist[19].sqldata = (void*)&asyrckpos;
#line 487 "Kenorder.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 8;
#line 487 "Kenorder.sqc"
      sql_setdlist[20].sqldata = (void*)oyakmkcd;
#line 487 "Kenorder.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 3;
#line 487 "Kenorder.sqc"
      sql_setdlist[21].sqldata = (void*)seccd;
#line 487 "Kenorder.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 487 "Kenorder.sqc"
      sql_setdlist[22].sqldata = (void*)&bkfkkbn;
#line 487 "Kenorder.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 487 "Kenorder.sqc"
      sql_setdlist[23].sqldata = (void*)smpcd;
#line 487 "Kenorder.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 5;
#line 487 "Kenorder.sqc"
      sql_setdlist[24].sqldata = (void*)bskkbn;
#line 487 "Kenorder.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 8;
#line 487 "Kenorder.sqc"
      sql_setdlist[25].sqldata = (void*)nbkmkcd;
#line 487 "Kenorder.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 5;
#line 487 "Kenorder.sqc"
      sql_setdlist[26].sqldata = (void*)zrcd;
#line 487 "Kenorder.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 3;
#line 487 "Kenorder.sqc"
      sql_setdlist[27].sqldata = (void*)ysnlbl;
#line 487 "Kenorder.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 4;
#line 487 "Kenorder.sqc"
      sql_setdlist[28].sqldata = (void*)kjno;
#line 487 "Kenorder.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 487 "Kenorder.sqc"
      sql_setdlist[29].sqldata = (void*)&fkhkknohjkbn;
#line 487 "Kenorder.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 4;
#line 487 "Kenorder.sqc"
      sql_setdlist[30].sqldata = (void*)tbkjno;
#line 487 "Kenorder.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 487 "Kenorder.sqc"
      sql_setdlist[31].sqldata = (void*)&tbkjflg;
#line 487 "Kenorder.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 25;
#line 487 "Kenorder.sqc"
      sql_setdlist[32].sqldata = (void*)htkfkhms;
#line 487 "Kenorder.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 487 "Kenorder.sqc"
      sql_setdlist[33].sqldata = (void*)&skflg;
#line 487 "Kenorder.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 3;
#line 487 "Kenorder.sqc"
      sql_setdlist[34].sqldata = (void*)tskflg;
#line 487 "Kenorder.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 3;
#line 487 "Kenorder.sqc"
      sql_setdlist[35].sqldata = (void*)tktflg;
#line 487 "Kenorder.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 16;
#line 487 "Kenorder.sqc"
      sql_setdlist[36].sqldata = (void*)ytiksbr;
#line 487 "Kenorder.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 487 "Kenorder.sqc"
      sql_setdlist[37].sqldata = (void*)&kkflg;
#line 487 "Kenorder.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 487 "Kenorder.sqc"
      sql_setdlist[38].sqldata = (void*)&kkiriflg;
#line 487 "Kenorder.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[39].sqltype = 500; sql_setdlist[39].sqllen = 2;
#line 487 "Kenorder.sqc"
      sql_setdlist[39].sqldata = (void*)&kkirilotno;
#line 487 "Kenorder.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 6;
#line 487 "Kenorder.sqc"
      sql_setdlist[40].sqldata = (void*)sc;
#line 487 "Kenorder.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 6;
#line 487 "Kenorder.sqc"
      sql_setdlist[41].sqldata = (void*)tj;
#line 487 "Kenorder.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[42].sqltype = 452; sql_setdlist[42].sqllen = 1;
#line 487 "Kenorder.sqc"
      sql_setdlist[42].sqldata = (void*)&tjtni;
#line 487 "Kenorder.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 487 "Kenorder.sqc"
      sql_setdlist[43].sqldata = (void*)&sbtkbn;
#line 487 "Kenorder.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 9;
#line 487 "Kenorder.sqc"
      sql_setdlist[44].sqldata = (void*)birthday;
#line 487 "Kenorder.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[45].sqltype = 452; sql_setdlist[45].sqllen = 1;
#line 487 "Kenorder.sqc"
      sql_setdlist[45].sqldata = (void*)&birthdaykbn;
#line 487 "Kenorder.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 4;
#line 487 "Kenorder.sqc"
      sql_setdlist[46].sqldata = (void*)age;
#line 487 "Kenorder.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 487 "Kenorder.sqc"
      sql_setdlist[47].sqldata = (void*)&agekbn;
#line 487 "Kenorder.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 9;
#line 487 "Kenorder.sqc"
      sql_setdlist[48].sqldata = (void*)sstme;
#line 487 "Kenorder.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 11;
#line 487 "Kenorder.sqc"
      sql_setdlist[49].sqldata = (void*)ssymd;
#line 487 "Kenorder.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 5;
#line 487 "Kenorder.sqc"
      sql_setdlist[50].sqldata = (void*)tntme;
#line 487 "Kenorder.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[51].sqltype = 452; sql_setdlist[51].sqllen = 1;
#line 487 "Kenorder.sqc"
      sql_setdlist[51].sqldata = (void*)&tntni;
#line 487 "Kenorder.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 6;
#line 487 "Kenorder.sqc"
      sql_setdlist[52].sqldata = (void*)tnryo;
#line 487 "Kenorder.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[53].sqltype = 452; sql_setdlist[53].sqllen = 1;
#line 487 "Kenorder.sqc"
      sql_setdlist[53].sqldata = (void*)&tnryotni;
#line 487 "Kenorder.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[54].sqltype = 496; sql_setdlist[54].sqllen = 4;
#line 487 "Kenorder.sqc"
      sql_setdlist[54].sqldata = (void*)&knsseq;
#line 487 "Kenorder.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[55].sqltype = 500; sql_setdlist[55].sqllen = 2;
#line 487 "Kenorder.sqc"
      sql_setdlist[55].sqldata = (void*)&bthno;
#line 487 "Kenorder.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[56].sqltype = 452; sql_setdlist[56].sqllen = 1;
#line 487 "Kenorder.sqc"
      sql_setdlist[56].sqldata = (void*)&knsjkflg;
#line 487 "Kenorder.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 27;
#line 487 "Kenorder.sqc"
      sql_setdlist[57].sqldata = (void*)ksndh;
#line 487 "Kenorder.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 487 "Kenorder.sqc"
      sqlasetdata(3,0,58,sql_setdlist,0L,0L);
    }
#line 487 "Kenorder.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 487 "Kenorder.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 487 "Kenorder.sqc"
  sqlastop(0L);
}

#line 487 "Kenorder.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kenorder*)ZbmlRealloc( array,
                                    sizeof( Kenorder ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kenorder ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KenorderArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 502 "Kenorder.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 502 "Kenorder.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 502 "Kenorder.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 502 "Kenorder.sqc"
  sqlastop(0L);
}

#line 502 "Kenorder.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 510 "Kenorder.sqc"

    return sqlca.sqlcode;
}

long ZdbKenorderSelectKey3( Kenorder* pKey, Kenorder** arrayOut, int* numOut )
{
    Kenorder*   array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KenorderArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 525 "Kenorder.sqc"


    
/*
EXEC SQL DECLARE c3 CURSOR FOR
    SELECT
		ZRCD,
		SBTKBN,
		KSKTKBN,
		SC,
		TJ,
		TJTNI,
		SSTME,
		TNRYO,
		TNRYOTNI
    FROM
        KENORDER
    WHERE
		KNTNO = :kntno AND
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd AND
		KNSSU = :knssu AND
		KNSSUEDA = :knssueda AND
		KNSKISYMD = :knskisymd FOR READ ONLY;
*/

#line 546 "Kenorder.sqc"


    
/*
EXEC SQL OPEN c3;
*/

{
#line 548 "Kenorder.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 548 "Kenorder.sqc"
  sqlaaloc(2,6,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 548 "Kenorder.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 14;
#line 548 "Kenorder.sqc"
      sql_setdlist[0].sqldata = (void*)kntno;
#line 548 "Kenorder.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 548 "Kenorder.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 548 "Kenorder.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 548 "Kenorder.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 548 "Kenorder.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 548 "Kenorder.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 548 "Kenorder.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 548 "Kenorder.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 548 "Kenorder.sqc"
      sql_setdlist[3].sqldata = (void*)&knssu;
#line 548 "Kenorder.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 548 "Kenorder.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 548 "Kenorder.sqc"
      sql_setdlist[4].sqldata = (void*)&knssueda;
#line 548 "Kenorder.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 548 "Kenorder.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 548 "Kenorder.sqc"
      sql_setdlist[5].sqldata = (void*)knskisymd;
#line 548 "Kenorder.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 548 "Kenorder.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 548 "Kenorder.sqc"
  sqlacall((unsigned short)26,3,2,0,0L);
#line 548 "Kenorder.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 548 "Kenorder.sqc"
  sqlastop(0L);
}

#line 548 "Kenorder.sqc"


    while( 1 ) {
        Kenorder* rec;

        
/*
EXEC SQL FETCH c3 INTO
			:zrcd,
			:sbtkbn,
			:ksktkbn,
			:sc,
			:tj,
			:tjtni,
			:sstme,
			:tnryo,
			:tnryotni;
*/

{
#line 562 "Kenorder.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 562 "Kenorder.sqc"
  sqlaaloc(3,9,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 562 "Kenorder.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 562 "Kenorder.sqc"
      sql_setdlist[0].sqldata = (void*)zrcd;
#line 562 "Kenorder.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 562 "Kenorder.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 562 "Kenorder.sqc"
      sql_setdlist[1].sqldata = (void*)&sbtkbn;
#line 562 "Kenorder.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 562 "Kenorder.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 562 "Kenorder.sqc"
      sql_setdlist[2].sqldata = (void*)&ksktkbn;
#line 562 "Kenorder.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 562 "Kenorder.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 6;
#line 562 "Kenorder.sqc"
      sql_setdlist[3].sqldata = (void*)sc;
#line 562 "Kenorder.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 562 "Kenorder.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 6;
#line 562 "Kenorder.sqc"
      sql_setdlist[4].sqldata = (void*)tj;
#line 562 "Kenorder.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 562 "Kenorder.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 562 "Kenorder.sqc"
      sql_setdlist[5].sqldata = (void*)&tjtni;
#line 562 "Kenorder.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 562 "Kenorder.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 9;
#line 562 "Kenorder.sqc"
      sql_setdlist[6].sqldata = (void*)sstme;
#line 562 "Kenorder.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 562 "Kenorder.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 6;
#line 562 "Kenorder.sqc"
      sql_setdlist[7].sqldata = (void*)tnryo;
#line 562 "Kenorder.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 562 "Kenorder.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 562 "Kenorder.sqc"
      sql_setdlist[8].sqldata = (void*)&tnryotni;
#line 562 "Kenorder.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 562 "Kenorder.sqc"
      sqlasetdata(3,0,9,sql_setdlist,0L,0L);
    }
#line 562 "Kenorder.sqc"
  sqlacall((unsigned short)25,3,0,3,0L);
#line 562 "Kenorder.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 562 "Kenorder.sqc"
  sqlastop(0L);
}

#line 562 "Kenorder.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kenorder*)ZbmlRealloc( array,
                                    sizeof( Kenorder ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kenorder ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KenorderArray );
    }

    
/*
EXEC SQL CLOSE c3;
*/

{
#line 577 "Kenorder.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 577 "Kenorder.sqc"
  sqlacall((unsigned short)20,3,0,0,0L);
#line 577 "Kenorder.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 577 "Kenorder.sqc"
  sqlastop(0L);
}

#line 577 "Kenorder.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 585 "Kenorder.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKenorderInsert()
 *    KENORDER レコードを挿入する
 * ■引数
 *    [I]  Kenorder* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKenorderInsert( Kenorder* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KenorderArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 607 "Kenorder.sqc"


    
/*
EXEC SQL INSERT INTO KENORDER
    (
		KNSKISYMD,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		KNSGRP,
		KMKCD,
		KNSSU,
		KNSSUEDA,
		IRIHSMKBN,
		IRIKBN,
		KSKTKBN,
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		SSTCD,
		TRID,
		TRPOS,
		ASYRCKID,
		ASYRCKPOS,
		OYAKMKCD,
		SECCD,
		BKFKKBN,
		SMPCD,
		BSKKBN,
		NBKMKCD,
		ZRCD,
		YSNLBL,
		KJNO,
		FKHKKNOHJKBN,
		TBKJNO,
		TBKJFLG,
		HTKFKHMS,
		SKFLG,
		TSKFLG,
		TKTFLG,
		YTIKSBR,
		KKFLG,
		KKIRIFLG,
		KKIRILOTNO,
		SC,
		TJ,
		TJTNI,
		SBTKBN,
		BIRTHDAY,
		BIRTHDAYKBN,
		AGE,
		AGEKBN,
		SSTME,
		SSYMD,
		TNTME,
		TNTNI,
		TNRYO,
		TNRYOTNI,
		KNSSEQ,
		BTHNO,
		KNSJKFLG,
		KSNDH
    ) VALUES (
		:knskisymd,
		:sriymd,
		:kntno,
		:kntketflg,
		:knsgrp,
		:kmkcd,
		:knssu,
		:knssueda,
		:irihsmkbn,
		:irikbn,
		:ksktkbn,
		:utkymd,
		:irino,
		:iriketflg,
		:zssdino,
		:sstcd,
		:trid,
		:trpos,
		:asyrckid,
		:asyrckpos,
		:oyakmkcd,
		:seccd,
		:bkfkkbn,
		:smpcd,
		:bskkbn,
		:nbkmkcd,
		:zrcd,
		:ysnlbl,
		:kjno,
		:fkhkknohjkbn,
		:tbkjno,
		:tbkjflg,
		:htkfkhms,
		:skflg,
		:tskflg,
		:tktflg,
		:ytiksbr,
		:kkflg,
		:kkiriflg,
		:kkirilotno,
		:sc,
		:tj,
		:tjtni,
		:sbtkbn,
		:birthday,
		:birthdaykbn,
		:age,
		:agekbn,
		:sstme,
		:ssymd,
		:tntme,
		:tntni,
		:tnryo,
		:tnryotni,
		:knsseq,
		:bthno,
		:knsjkflg,
		:ksndh
    );
*/

{
#line 728 "Kenorder.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 728 "Kenorder.sqc"
  sqlaaloc(2,58,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[58];
#line 728 "Kenorder.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 728 "Kenorder.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 728 "Kenorder.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 728 "Kenorder.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 728 "Kenorder.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 728 "Kenorder.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 728 "Kenorder.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 728 "Kenorder.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 728 "Kenorder.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 728 "Kenorder.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 728 "Kenorder.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 728 "Kenorder.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 728 "Kenorder.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 728 "Kenorder.sqc"
      sql_setdlist[6].sqldata = (void*)&knssu;
#line 728 "Kenorder.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 728 "Kenorder.sqc"
      sql_setdlist[7].sqldata = (void*)&knssueda;
#line 728 "Kenorder.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 728 "Kenorder.sqc"
      sql_setdlist[8].sqldata = (void*)&irihsmkbn;
#line 728 "Kenorder.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 728 "Kenorder.sqc"
      sql_setdlist[9].sqldata = (void*)&irikbn;
#line 728 "Kenorder.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 728 "Kenorder.sqc"
      sql_setdlist[10].sqldata = (void*)&ksktkbn;
#line 728 "Kenorder.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 728 "Kenorder.sqc"
      sql_setdlist[11].sqldata = (void*)utkymd;
#line 728 "Kenorder.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 12;
#line 728 "Kenorder.sqc"
      sql_setdlist[12].sqldata = (void*)irino;
#line 728 "Kenorder.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 728 "Kenorder.sqc"
      sql_setdlist[13].sqldata = (void*)&iriketflg;
#line 728 "Kenorder.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 728 "Kenorder.sqc"
      sql_setdlist[14].sqldata = (void*)&zssdino;
#line 728 "Kenorder.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 728 "Kenorder.sqc"
      sql_setdlist[15].sqldata = (void*)sstcd;
#line 728 "Kenorder.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 11;
#line 728 "Kenorder.sqc"
      sql_setdlist[16].sqldata = (void*)trid;
#line 728 "Kenorder.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[17].sqltype = 500; sql_setdlist[17].sqllen = 2;
#line 728 "Kenorder.sqc"
      sql_setdlist[17].sqldata = (void*)&trpos;
#line 728 "Kenorder.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 11;
#line 728 "Kenorder.sqc"
      sql_setdlist[18].sqldata = (void*)asyrckid;
#line 728 "Kenorder.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 728 "Kenorder.sqc"
      sql_setdlist[19].sqldata = (void*)&asyrckpos;
#line 728 "Kenorder.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 8;
#line 728 "Kenorder.sqc"
      sql_setdlist[20].sqldata = (void*)oyakmkcd;
#line 728 "Kenorder.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 3;
#line 728 "Kenorder.sqc"
      sql_setdlist[21].sqldata = (void*)seccd;
#line 728 "Kenorder.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 728 "Kenorder.sqc"
      sql_setdlist[22].sqldata = (void*)&bkfkkbn;
#line 728 "Kenorder.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 728 "Kenorder.sqc"
      sql_setdlist[23].sqldata = (void*)smpcd;
#line 728 "Kenorder.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 5;
#line 728 "Kenorder.sqc"
      sql_setdlist[24].sqldata = (void*)bskkbn;
#line 728 "Kenorder.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 8;
#line 728 "Kenorder.sqc"
      sql_setdlist[25].sqldata = (void*)nbkmkcd;
#line 728 "Kenorder.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 5;
#line 728 "Kenorder.sqc"
      sql_setdlist[26].sqldata = (void*)zrcd;
#line 728 "Kenorder.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 3;
#line 728 "Kenorder.sqc"
      sql_setdlist[27].sqldata = (void*)ysnlbl;
#line 728 "Kenorder.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 4;
#line 728 "Kenorder.sqc"
      sql_setdlist[28].sqldata = (void*)kjno;
#line 728 "Kenorder.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 728 "Kenorder.sqc"
      sql_setdlist[29].sqldata = (void*)&fkhkknohjkbn;
#line 728 "Kenorder.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 4;
#line 728 "Kenorder.sqc"
      sql_setdlist[30].sqldata = (void*)tbkjno;
#line 728 "Kenorder.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 728 "Kenorder.sqc"
      sql_setdlist[31].sqldata = (void*)&tbkjflg;
#line 728 "Kenorder.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 25;
#line 728 "Kenorder.sqc"
      sql_setdlist[32].sqldata = (void*)htkfkhms;
#line 728 "Kenorder.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 728 "Kenorder.sqc"
      sql_setdlist[33].sqldata = (void*)&skflg;
#line 728 "Kenorder.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 3;
#line 728 "Kenorder.sqc"
      sql_setdlist[34].sqldata = (void*)tskflg;
#line 728 "Kenorder.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 3;
#line 728 "Kenorder.sqc"
      sql_setdlist[35].sqldata = (void*)tktflg;
#line 728 "Kenorder.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 16;
#line 728 "Kenorder.sqc"
      sql_setdlist[36].sqldata = (void*)ytiksbr;
#line 728 "Kenorder.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 728 "Kenorder.sqc"
      sql_setdlist[37].sqldata = (void*)&kkflg;
#line 728 "Kenorder.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 728 "Kenorder.sqc"
      sql_setdlist[38].sqldata = (void*)&kkiriflg;
#line 728 "Kenorder.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[39].sqltype = 500; sql_setdlist[39].sqllen = 2;
#line 728 "Kenorder.sqc"
      sql_setdlist[39].sqldata = (void*)&kkirilotno;
#line 728 "Kenorder.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 6;
#line 728 "Kenorder.sqc"
      sql_setdlist[40].sqldata = (void*)sc;
#line 728 "Kenorder.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 6;
#line 728 "Kenorder.sqc"
      sql_setdlist[41].sqldata = (void*)tj;
#line 728 "Kenorder.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[42].sqltype = 452; sql_setdlist[42].sqllen = 1;
#line 728 "Kenorder.sqc"
      sql_setdlist[42].sqldata = (void*)&tjtni;
#line 728 "Kenorder.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 728 "Kenorder.sqc"
      sql_setdlist[43].sqldata = (void*)&sbtkbn;
#line 728 "Kenorder.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 9;
#line 728 "Kenorder.sqc"
      sql_setdlist[44].sqldata = (void*)birthday;
#line 728 "Kenorder.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[45].sqltype = 452; sql_setdlist[45].sqllen = 1;
#line 728 "Kenorder.sqc"
      sql_setdlist[45].sqldata = (void*)&birthdaykbn;
#line 728 "Kenorder.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 4;
#line 728 "Kenorder.sqc"
      sql_setdlist[46].sqldata = (void*)age;
#line 728 "Kenorder.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 728 "Kenorder.sqc"
      sql_setdlist[47].sqldata = (void*)&agekbn;
#line 728 "Kenorder.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 9;
#line 728 "Kenorder.sqc"
      sql_setdlist[48].sqldata = (void*)sstme;
#line 728 "Kenorder.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 11;
#line 728 "Kenorder.sqc"
      sql_setdlist[49].sqldata = (void*)ssymd;
#line 728 "Kenorder.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 5;
#line 728 "Kenorder.sqc"
      sql_setdlist[50].sqldata = (void*)tntme;
#line 728 "Kenorder.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[51].sqltype = 452; sql_setdlist[51].sqllen = 1;
#line 728 "Kenorder.sqc"
      sql_setdlist[51].sqldata = (void*)&tntni;
#line 728 "Kenorder.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 6;
#line 728 "Kenorder.sqc"
      sql_setdlist[52].sqldata = (void*)tnryo;
#line 728 "Kenorder.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[53].sqltype = 452; sql_setdlist[53].sqllen = 1;
#line 728 "Kenorder.sqc"
      sql_setdlist[53].sqldata = (void*)&tnryotni;
#line 728 "Kenorder.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[54].sqltype = 496; sql_setdlist[54].sqllen = 4;
#line 728 "Kenorder.sqc"
      sql_setdlist[54].sqldata = (void*)&knsseq;
#line 728 "Kenorder.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[55].sqltype = 500; sql_setdlist[55].sqllen = 2;
#line 728 "Kenorder.sqc"
      sql_setdlist[55].sqldata = (void*)&bthno;
#line 728 "Kenorder.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[56].sqltype = 452; sql_setdlist[56].sqllen = 1;
#line 728 "Kenorder.sqc"
      sql_setdlist[56].sqldata = (void*)&knsjkflg;
#line 728 "Kenorder.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 27;
#line 728 "Kenorder.sqc"
      sql_setdlist[57].sqldata = (void*)ksndh;
#line 728 "Kenorder.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 728 "Kenorder.sqc"
      sqlasetdata(2,0,58,sql_setdlist,0L,0L);
    }
#line 728 "Kenorder.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 728 "Kenorder.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 728 "Kenorder.sqc"
  sqlastop(0L);
}

#line 728 "Kenorder.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 733 "Kenorder.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKenorderUpdate()
 *    KENORDER レコードを更新する
 * ■引数
 *    [I]  Kenorder* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKenorderUpdate( Kenorder* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KenorderArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 757 "Kenorder.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 758 "Kenorder.sqc"


    
/*
EXEC SQL UPDATE KENORDER
    SET (
		KNTKETFLG,
		IRIHSMKBN,
		IRIKBN,
		KSKTKBN,
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		SSTCD,
		TRID,
		TRPOS,
		ASYRCKID,
		ASYRCKPOS,
		OYAKMKCD,
		SECCD,
		BKFKKBN,
		SMPCD,
		BSKKBN,
		NBKMKCD,
		ZRCD,
		YSNLBL,
		KJNO,
		FKHKKNOHJKBN,
		TBKJNO,
		TBKJFLG,
		HTKFKHMS,
		SKFLG,
		TSKFLG,
		TKTFLG,
		YTIKSBR,
		KKFLG,
		KKIRIFLG,
		KKIRILOTNO,
		SC,
		TJ,
		TJTNI,
		SBTKBN,
		BIRTHDAY,
		BIRTHDAYKBN,
		AGE,
		AGEKBN,
		SSTME,
		SSYMD,
		TNTME,
		TNTNI,
		TNRYO,
		TNRYOTNI,
		KNSSEQ,
		BTHNO,
		KNSJKFLG,
		KSNDH
    ) = (
		:kntketflg,
		:irihsmkbn,
		:irikbn,
		:ksktkbn,
		:utkymd,
		:irino,
		:iriketflg,
		:zssdino,
		:sstcd,
		:trid,
		:trpos,
		:asyrckid,
		:asyrckpos,
		:oyakmkcd,
		:seccd,
		:bkfkkbn,
		:smpcd,
		:bskkbn,
		:nbkmkcd,
		:zrcd,
		:ysnlbl,
		:kjno,
		:fkhkknohjkbn,
		:tbkjno,
		:tbkjflg,
		:htkfkhms,
		:skflg,
		:tskflg,
		:tktflg,
		:ytiksbr,
		:kkflg,
		:kkiriflg,
		:kkirilotno,
		:sc,
		:tj,
		:tjtni,
		:sbtkbn,
		:birthday,
		:birthdaykbn,
		:age,
		:agekbn,
		:sstme,
		:ssymd,
		:tntme,
		:tntni,
		:tnryo,
		:tnryotni,
		:knsseq,
		:bthno,
		:knsjkflg,
		:ksndh
    ) WHERE
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd AND
		KNSSU = :knssu AND
		KNSSUEDA = :knssueda;
*/

{
#line 872 "Kenorder.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 872 "Kenorder.sqc"
  sqlaaloc(2,58,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[58];
#line 872 "Kenorder.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 872 "Kenorder.sqc"
      sql_setdlist[0].sqldata = (void*)&kntketflg;
#line 872 "Kenorder.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 872 "Kenorder.sqc"
      sql_setdlist[1].sqldata = (void*)&irihsmkbn;
#line 872 "Kenorder.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 872 "Kenorder.sqc"
      sql_setdlist[2].sqldata = (void*)&irikbn;
#line 872 "Kenorder.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 872 "Kenorder.sqc"
      sql_setdlist[3].sqldata = (void*)&ksktkbn;
#line 872 "Kenorder.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 872 "Kenorder.sqc"
      sql_setdlist[4].sqldata = (void*)utkymd;
#line 872 "Kenorder.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 12;
#line 872 "Kenorder.sqc"
      sql_setdlist[5].sqldata = (void*)irino;
#line 872 "Kenorder.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 872 "Kenorder.sqc"
      sql_setdlist[6].sqldata = (void*)&iriketflg;
#line 872 "Kenorder.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 872 "Kenorder.sqc"
      sql_setdlist[7].sqldata = (void*)&zssdino;
#line 872 "Kenorder.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 8;
#line 872 "Kenorder.sqc"
      sql_setdlist[8].sqldata = (void*)sstcd;
#line 872 "Kenorder.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 872 "Kenorder.sqc"
      sql_setdlist[9].sqldata = (void*)trid;
#line 872 "Kenorder.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[10].sqltype = 500; sql_setdlist[10].sqllen = 2;
#line 872 "Kenorder.sqc"
      sql_setdlist[10].sqldata = (void*)&trpos;
#line 872 "Kenorder.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 872 "Kenorder.sqc"
      sql_setdlist[11].sqldata = (void*)asyrckid;
#line 872 "Kenorder.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 872 "Kenorder.sqc"
      sql_setdlist[12].sqldata = (void*)&asyrckpos;
#line 872 "Kenorder.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 8;
#line 872 "Kenorder.sqc"
      sql_setdlist[13].sqldata = (void*)oyakmkcd;
#line 872 "Kenorder.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 3;
#line 872 "Kenorder.sqc"
      sql_setdlist[14].sqldata = (void*)seccd;
#line 872 "Kenorder.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[15].sqltype = 452; sql_setdlist[15].sqllen = 1;
#line 872 "Kenorder.sqc"
      sql_setdlist[15].sqldata = (void*)&bkfkkbn;
#line 872 "Kenorder.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 8;
#line 872 "Kenorder.sqc"
      sql_setdlist[16].sqldata = (void*)smpcd;
#line 872 "Kenorder.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 5;
#line 872 "Kenorder.sqc"
      sql_setdlist[17].sqldata = (void*)bskkbn;
#line 872 "Kenorder.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 8;
#line 872 "Kenorder.sqc"
      sql_setdlist[18].sqldata = (void*)nbkmkcd;
#line 872 "Kenorder.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 5;
#line 872 "Kenorder.sqc"
      sql_setdlist[19].sqldata = (void*)zrcd;
#line 872 "Kenorder.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 3;
#line 872 "Kenorder.sqc"
      sql_setdlist[20].sqldata = (void*)ysnlbl;
#line 872 "Kenorder.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 4;
#line 872 "Kenorder.sqc"
      sql_setdlist[21].sqldata = (void*)kjno;
#line 872 "Kenorder.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 872 "Kenorder.sqc"
      sql_setdlist[22].sqldata = (void*)&fkhkknohjkbn;
#line 872 "Kenorder.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 4;
#line 872 "Kenorder.sqc"
      sql_setdlist[23].sqldata = (void*)tbkjno;
#line 872 "Kenorder.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 872 "Kenorder.sqc"
      sql_setdlist[24].sqldata = (void*)&tbkjflg;
#line 872 "Kenorder.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 25;
#line 872 "Kenorder.sqc"
      sql_setdlist[25].sqldata = (void*)htkfkhms;
#line 872 "Kenorder.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 872 "Kenorder.sqc"
      sql_setdlist[26].sqldata = (void*)&skflg;
#line 872 "Kenorder.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 3;
#line 872 "Kenorder.sqc"
      sql_setdlist[27].sqldata = (void*)tskflg;
#line 872 "Kenorder.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 3;
#line 872 "Kenorder.sqc"
      sql_setdlist[28].sqldata = (void*)tktflg;
#line 872 "Kenorder.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 16;
#line 872 "Kenorder.sqc"
      sql_setdlist[29].sqldata = (void*)ytiksbr;
#line 872 "Kenorder.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 872 "Kenorder.sqc"
      sql_setdlist[30].sqldata = (void*)&kkflg;
#line 872 "Kenorder.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 872 "Kenorder.sqc"
      sql_setdlist[31].sqldata = (void*)&kkiriflg;
#line 872 "Kenorder.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[32].sqltype = 500; sql_setdlist[32].sqllen = 2;
#line 872 "Kenorder.sqc"
      sql_setdlist[32].sqldata = (void*)&kkirilotno;
#line 872 "Kenorder.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 6;
#line 872 "Kenorder.sqc"
      sql_setdlist[33].sqldata = (void*)sc;
#line 872 "Kenorder.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 6;
#line 872 "Kenorder.sqc"
      sql_setdlist[34].sqldata = (void*)tj;
#line 872 "Kenorder.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 872 "Kenorder.sqc"
      sql_setdlist[35].sqldata = (void*)&tjtni;
#line 872 "Kenorder.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 872 "Kenorder.sqc"
      sql_setdlist[36].sqldata = (void*)&sbtkbn;
#line 872 "Kenorder.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 9;
#line 872 "Kenorder.sqc"
      sql_setdlist[37].sqldata = (void*)birthday;
#line 872 "Kenorder.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 872 "Kenorder.sqc"
      sql_setdlist[38].sqldata = (void*)&birthdaykbn;
#line 872 "Kenorder.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 4;
#line 872 "Kenorder.sqc"
      sql_setdlist[39].sqldata = (void*)age;
#line 872 "Kenorder.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 872 "Kenorder.sqc"
      sql_setdlist[40].sqldata = (void*)&agekbn;
#line 872 "Kenorder.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 9;
#line 872 "Kenorder.sqc"
      sql_setdlist[41].sqldata = (void*)sstme;
#line 872 "Kenorder.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 11;
#line 872 "Kenorder.sqc"
      sql_setdlist[42].sqldata = (void*)ssymd;
#line 872 "Kenorder.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 5;
#line 872 "Kenorder.sqc"
      sql_setdlist[43].sqldata = (void*)tntme;
#line 872 "Kenorder.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 872 "Kenorder.sqc"
      sql_setdlist[44].sqldata = (void*)&tntni;
#line 872 "Kenorder.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 6;
#line 872 "Kenorder.sqc"
      sql_setdlist[45].sqldata = (void*)tnryo;
#line 872 "Kenorder.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 872 "Kenorder.sqc"
      sql_setdlist[46].sqldata = (void*)&tnryotni;
#line 872 "Kenorder.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[47].sqltype = 496; sql_setdlist[47].sqllen = 4;
#line 872 "Kenorder.sqc"
      sql_setdlist[47].sqldata = (void*)&knsseq;
#line 872 "Kenorder.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[48].sqltype = 500; sql_setdlist[48].sqllen = 2;
#line 872 "Kenorder.sqc"
      sql_setdlist[48].sqldata = (void*)&bthno;
#line 872 "Kenorder.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[49].sqltype = 452; sql_setdlist[49].sqllen = 1;
#line 872 "Kenorder.sqc"
      sql_setdlist[49].sqldata = (void*)&knsjkflg;
#line 872 "Kenorder.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 27;
#line 872 "Kenorder.sqc"
      sql_setdlist[50].sqldata = (void*)ksndh;
#line 872 "Kenorder.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 11;
#line 872 "Kenorder.sqc"
      sql_setdlist[51].sqldata = (void*)knskisymd;
#line 872 "Kenorder.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 11;
#line 872 "Kenorder.sqc"
      sql_setdlist[52].sqldata = (void*)sriymd;
#line 872 "Kenorder.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 14;
#line 872 "Kenorder.sqc"
      sql_setdlist[53].sqldata = (void*)kntno;
#line 872 "Kenorder.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 17;
#line 872 "Kenorder.sqc"
      sql_setdlist[54].sqldata = (void*)knsgrp;
#line 872 "Kenorder.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 8;
#line 872 "Kenorder.sqc"
      sql_setdlist[55].sqldata = (void*)kmkcd;
#line 872 "Kenorder.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[56].sqltype = 500; sql_setdlist[56].sqllen = 2;
#line 872 "Kenorder.sqc"
      sql_setdlist[56].sqldata = (void*)&knssu;
#line 872 "Kenorder.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sql_setdlist[57].sqltype = 500; sql_setdlist[57].sqllen = 2;
#line 872 "Kenorder.sqc"
      sql_setdlist[57].sqldata = (void*)&knssueda;
#line 872 "Kenorder.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 872 "Kenorder.sqc"
      sqlasetdata(2,0,58,sql_setdlist,0L,0L);
    }
#line 872 "Kenorder.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 872 "Kenorder.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 872 "Kenorder.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 872 "Kenorder.sqc"
  sqlastop(0L);
}

#line 872 "Kenorder.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 877 "Kenorder.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 881 "Kenorder.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKenorderDelete()
 *    KENORDER レコードを削除する
 * ■引数
 *    [I]  Kenorder* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKenorderDelete( Kenorder* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KenorderArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 905 "Kenorder.sqc"


    
/*
EXEC SQL DELETE FROM KENORDER
    WHERE
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd AND
		KNSSU = :knssu AND
		KNSSUEDA = :knssueda;
*/

{
#line 915 "Kenorder.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 915 "Kenorder.sqc"
  sqlaaloc(2,7,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 915 "Kenorder.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 915 "Kenorder.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 915 "Kenorder.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 915 "Kenorder.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 915 "Kenorder.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 915 "Kenorder.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 915 "Kenorder.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 915 "Kenorder.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 915 "Kenorder.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 915 "Kenorder.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 915 "Kenorder.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 915 "Kenorder.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 915 "Kenorder.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 915 "Kenorder.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 915 "Kenorder.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 915 "Kenorder.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 915 "Kenorder.sqc"
      sql_setdlist[5].sqldata = (void*)&knssu;
#line 915 "Kenorder.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 915 "Kenorder.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 915 "Kenorder.sqc"
      sql_setdlist[6].sqldata = (void*)&knssueda;
#line 915 "Kenorder.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 915 "Kenorder.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 915 "Kenorder.sqc"
  sqlacall((unsigned short)24,6,2,0,0L);
#line 915 "Kenorder.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 915 "Kenorder.sqc"
  sqlastop(0L);
}

#line 915 "Kenorder.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 920 "Kenorder.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
