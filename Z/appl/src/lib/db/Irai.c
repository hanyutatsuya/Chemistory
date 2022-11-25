static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,90,65,83,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,50,53,90,73,82,65,73,32,0,0,0,0,0,0,0,0,
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


#line 1 "Irai.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Irai.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Irai.h"
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


#line 24 "Irai.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Irai.sqc"

	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    knsgrp[17];
	char    kmkcd[8];
	char    irihsmkbn;
	char    irikbn;
	char    ksktkbn;
	char    sriymd[11];
	char    kntno[14];
	char    kntketflg;
	char    chkmj[5];
	char    stsrcd[5];
	char    kmkrs[17];
	char    oyakmkcd[8];
	char    smpcd[8];
	char    setkmkcd[8];
	char    srinycd;
	char    seccd[3];
	char    skchkflg;
	char    bkfkkbn;
	char    ysnlbl[3];
	char    skflg;
	char    tkflg;
	char    sjflg;
	char    jktkflg;
	char    kjno[4];
	char    fkhkknohjkbn;
	char    tbkjno[4];
	char    tbkjflg;
	char    htkfkhms[25];
	char    tskflg[3];
	char    tktflg[3];
	char    bnckbn;
	char    nbnckbn;
	char    knskisyymd[11];
	char    knskryymd[11];
	char    knskrytme[9];
	char    kkhkkflg;
	char    kkiriflg;
	short   kkirilotno;
	char    kktoutkid[5];
	short   knssu;
	char    odrssflg;
	char    ytiksbr[16];
	char    hhkjkflg;
	char    ksndh[27];
	char	trkdh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 79 "Irai.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Irai

BmlDMMInfo	IraiArray[] = {
	DMM_SDATE( utkymd ),
	DMM_SSTRING( irino ),
	DMM_SCHAR( iriketflg ),
	DMM_SSHORT( zssdino ),
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SCHAR( irihsmkbn ),
	DMM_SCHAR( irikbn ),
	DMM_SCHAR( ksktkbn ),
	DMM_SDATE( sriymd ),
	DMM_SSTRING( kntno ),
	DMM_SCHAR( kntketflg ),
	DMM_SSTRING( chkmj ),
	DMM_SSTRING( stsrcd ),
	DMM_SSTRING( kmkrs ),
	DMM_SSTRING( oyakmkcd ),
	DMM_SSTRING( smpcd ),
	DMM_SSTRING( setkmkcd ),
	DMM_SCHAR( srinycd ),
	DMM_SSTRING( seccd ),
	DMM_SCHAR( skchkflg ),
	DMM_SCHAR( bkfkkbn ),
	DMM_SSTRING( ysnlbl ),
	DMM_SCHAR( skflg ),
	DMM_SCHAR( tkflg ),
	DMM_SCHAR( sjflg ),
	DMM_SCHAR( jktkflg ),
	DMM_SSTRING( kjno ),
	DMM_SCHAR( fkhkknohjkbn ),
	DMM_SSTRING( tbkjno ),
	DMM_SCHAR( tbkjflg ),
	DMM_SSTRING( htkfkhms ),
	DMM_SSTRING( tskflg ),
	DMM_SSTRING( tktflg ),
	DMM_SCHAR( bnckbn ),
	DMM_SCHAR( nbnckbn ),
	DMM_SDATE( knskisyymd ),
	DMM_SDATE( knskryymd ),
	DMM_STIME( knskrytme ),
	DMM_SCHAR( kkhkkflg ),
	DMM_SCHAR( kkiriflg ),
	DMM_SSHORT( kkirilotno ),
	DMM_SSTRING( kktoutkid ),
	DMM_SSHORT( knssu ),
	DMM_SCHAR( odrssflg ),
	DMM_SSTRING( ytiksbr ),
	DMM_SCHAR( hhkjkflg ),
	DMM_STIMESTAMP( ksndh ),
	DMM_STIMESTAMP( trkdh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbIraiSelectAll()
 *    IRAI レコード全件取得
 * ■引数
 *    [O]  Irai** arrayOut      取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbIraiSelectAll( Irai** arrayOut, int* numOut )
{
    Irai*       array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 156 "Irai.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		KNSGRP,
		KMKCD,
		IRIHSMKBN,
		IRIKBN,
		KSKTKBN,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		CHKMJ,
		STSRCD,
		KMKRS,
		OYAKMKCD,
		SMPCD,
		SETKMKCD,
		SRINYCD,
		SECCD,
		SKCHKFLG,
		BKFKKBN,
		YSNLBL,
		SKFLG,
		TKFLG,
		SJFLG,
		JKTKFLG,
		KJNO,
		FKHKKNOHJKBN,
		TBKJNO,
		TBKJFLG,
		HTKFKHMS,
		TSKFLG,
		TKTFLG,
		BNCKBN,
		NBNCKBN,
		KNSKISYYMD,
		KNSKRYYMD,
		KNSKRYTME,
		KKHKKFLG,
		KKIRIFLG,
		KKIRILOTNO,
		KKTOUTKID,
		KNSSU,
		ODRSSFLG,
		YTIKSBR,
		HHKJKFLG,
		KSNDH,
		TRKDH
    FROM
        IRAI FOR READ ONLY;
*/

#line 210 "Irai.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 212 "Irai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 212 "Irai.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 212 "Irai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 212 "Irai.sqc"
  sqlastop(0L);
}

#line 212 "Irai.sqc"


    while( 1 ) {
        Irai* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:knsgrp,
			:kmkcd,
			:irihsmkbn,
			:irikbn,
			:ksktkbn,
			:sriymd,
			:kntno,
			:kntketflg,
			:chkmj,
			:stsrcd,
			:kmkrs,
			:oyakmkcd,
			:smpcd,
			:setkmkcd,
			:srinycd,
			:seccd,
			:skchkflg,
			:bkfkkbn,
			:ysnlbl,
			:skflg,
			:tkflg,
			:sjflg,
			:jktkflg,
			:kjno,
			:fkhkknohjkbn,
			:tbkjno,
			:tbkjflg,
			:htkfkhms,
			:tskflg,
			:tktflg,
			:bnckbn,
			:nbnckbn,
			:knskisyymd,
			:knskryymd,
			:knskrytme,
			:kkhkkflg,
			:kkiriflg,
			:kkirilotno,
			:kktoutkid,
			:knssu,
			:odrssflg,
			:ytiksbr,
			:hhkjkflg,
			:ksndh,
			:trkdh;
*/

{
#line 266 "Irai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 266 "Irai.sqc"
  sqlaaloc(3,49,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[49];
#line 266 "Irai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 266 "Irai.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 266 "Irai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 266 "Irai.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 266 "Irai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 266 "Irai.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 266 "Irai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 266 "Irai.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 266 "Irai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 266 "Irai.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 266 "Irai.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 266 "Irai.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 266 "Irai.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 266 "Irai.sqc"
      sql_setdlist[6].sqldata = (void*)&irihsmkbn;
#line 266 "Irai.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 266 "Irai.sqc"
      sql_setdlist[7].sqldata = (void*)&irikbn;
#line 266 "Irai.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 266 "Irai.sqc"
      sql_setdlist[8].sqldata = (void*)&ksktkbn;
#line 266 "Irai.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 266 "Irai.sqc"
      sql_setdlist[9].sqldata = (void*)sriymd;
#line 266 "Irai.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 14;
#line 266 "Irai.sqc"
      sql_setdlist[10].sqldata = (void*)kntno;
#line 266 "Irai.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 266 "Irai.sqc"
      sql_setdlist[11].sqldata = (void*)&kntketflg;
#line 266 "Irai.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 5;
#line 266 "Irai.sqc"
      sql_setdlist[12].sqldata = (void*)chkmj;
#line 266 "Irai.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 5;
#line 266 "Irai.sqc"
      sql_setdlist[13].sqldata = (void*)stsrcd;
#line 266 "Irai.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 17;
#line 266 "Irai.sqc"
      sql_setdlist[14].sqldata = (void*)kmkrs;
#line 266 "Irai.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 266 "Irai.sqc"
      sql_setdlist[15].sqldata = (void*)oyakmkcd;
#line 266 "Irai.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 8;
#line 266 "Irai.sqc"
      sql_setdlist[16].sqldata = (void*)smpcd;
#line 266 "Irai.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 8;
#line 266 "Irai.sqc"
      sql_setdlist[17].sqldata = (void*)setkmkcd;
#line 266 "Irai.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 266 "Irai.sqc"
      sql_setdlist[18].sqldata = (void*)&srinycd;
#line 266 "Irai.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 3;
#line 266 "Irai.sqc"
      sql_setdlist[19].sqldata = (void*)seccd;
#line 266 "Irai.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 266 "Irai.sqc"
      sql_setdlist[20].sqldata = (void*)&skchkflg;
#line 266 "Irai.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 266 "Irai.sqc"
      sql_setdlist[21].sqldata = (void*)&bkfkkbn;
#line 266 "Irai.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 3;
#line 266 "Irai.sqc"
      sql_setdlist[22].sqldata = (void*)ysnlbl;
#line 266 "Irai.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 266 "Irai.sqc"
      sql_setdlist[23].sqldata = (void*)&skflg;
#line 266 "Irai.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 266 "Irai.sqc"
      sql_setdlist[24].sqldata = (void*)&tkflg;
#line 266 "Irai.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 266 "Irai.sqc"
      sql_setdlist[25].sqldata = (void*)&sjflg;
#line 266 "Irai.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 266 "Irai.sqc"
      sql_setdlist[26].sqldata = (void*)&jktkflg;
#line 266 "Irai.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 4;
#line 266 "Irai.sqc"
      sql_setdlist[27].sqldata = (void*)kjno;
#line 266 "Irai.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 266 "Irai.sqc"
      sql_setdlist[28].sqldata = (void*)&fkhkknohjkbn;
#line 266 "Irai.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 4;
#line 266 "Irai.sqc"
      sql_setdlist[29].sqldata = (void*)tbkjno;
#line 266 "Irai.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 266 "Irai.sqc"
      sql_setdlist[30].sqldata = (void*)&tbkjflg;
#line 266 "Irai.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 25;
#line 266 "Irai.sqc"
      sql_setdlist[31].sqldata = (void*)htkfkhms;
#line 266 "Irai.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 266 "Irai.sqc"
      sql_setdlist[32].sqldata = (void*)tskflg;
#line 266 "Irai.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 266 "Irai.sqc"
      sql_setdlist[33].sqldata = (void*)tktflg;
#line 266 "Irai.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 266 "Irai.sqc"
      sql_setdlist[34].sqldata = (void*)&bnckbn;
#line 266 "Irai.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 266 "Irai.sqc"
      sql_setdlist[35].sqldata = (void*)&nbnckbn;
#line 266 "Irai.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 11;
#line 266 "Irai.sqc"
      sql_setdlist[36].sqldata = (void*)knskisyymd;
#line 266 "Irai.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 11;
#line 266 "Irai.sqc"
      sql_setdlist[37].sqldata = (void*)knskryymd;
#line 266 "Irai.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 9;
#line 266 "Irai.sqc"
      sql_setdlist[38].sqldata = (void*)knskrytme;
#line 266 "Irai.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 266 "Irai.sqc"
      sql_setdlist[39].sqldata = (void*)&kkhkkflg;
#line 266 "Irai.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 266 "Irai.sqc"
      sql_setdlist[40].sqldata = (void*)&kkiriflg;
#line 266 "Irai.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[41].sqltype = 500; sql_setdlist[41].sqllen = 2;
#line 266 "Irai.sqc"
      sql_setdlist[41].sqldata = (void*)&kkirilotno;
#line 266 "Irai.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 5;
#line 266 "Irai.sqc"
      sql_setdlist[42].sqldata = (void*)kktoutkid;
#line 266 "Irai.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[43].sqltype = 500; sql_setdlist[43].sqllen = 2;
#line 266 "Irai.sqc"
      sql_setdlist[43].sqldata = (void*)&knssu;
#line 266 "Irai.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 266 "Irai.sqc"
      sql_setdlist[44].sqldata = (void*)&odrssflg;
#line 266 "Irai.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 16;
#line 266 "Irai.sqc"
      sql_setdlist[45].sqldata = (void*)ytiksbr;
#line 266 "Irai.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 266 "Irai.sqc"
      sql_setdlist[46].sqldata = (void*)&hhkjkflg;
#line 266 "Irai.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 27;
#line 266 "Irai.sqc"
      sql_setdlist[47].sqldata = (void*)ksndh;
#line 266 "Irai.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 266 "Irai.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 27;
#line 266 "Irai.sqc"
      sql_setdlist[48].sqldata = (void*)trkdh;
#line 266 "Irai.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 266 "Irai.sqc"
      sqlasetdata(3,0,49,sql_setdlist,0L,0L);
    }
#line 266 "Irai.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 266 "Irai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 266 "Irai.sqc"
  sqlastop(0L);
}

#line 266 "Irai.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Irai*)ZbmlRealloc( array,
                                    sizeof( Irai ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Irai ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, IraiArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 281 "Irai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 281 "Irai.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 281 "Irai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 281 "Irai.sqc"
  sqlastop(0L);
}

#line 281 "Irai.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 289 "Irai.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbIraiSelectKey()
 *    IRAI レコードKey条件取得
 * ■引数
 *    [I]  Irai* pKey       取得するレコードのキー
 *    [O]  Irai** arrayOut      取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbIraiSelectKey( Irai* pKey, Irai** arrayOut, int* numOut )
{
    Irai*       array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, IraiArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 315 "Irai.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		KNSGRP,
		KMKCD,
		IRIHSMKBN,
		IRIKBN,
		KSKTKBN,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		CHKMJ,
		STSRCD,
		KMKRS,
		OYAKMKCD,
		SMPCD,
		SETKMKCD,
		SRINYCD,
		SECCD,
		SKCHKFLG,
		BKFKKBN,
		YSNLBL,
		SKFLG,
		TKFLG,
		SJFLG,
		JKTKFLG,
		KJNO,
		FKHKKNOHJKBN,
		TBKJNO,
		TBKJFLG,
		HTKFKHMS,
		TSKFLG,
		TKTFLG,
		BNCKBN,
		NBNCKBN,
		KNSKISYYMD,
		KNSKRYYMD,
		KNSKRYTME,
		KKHKKFLG,
		KKIRIFLG,
		KKIRILOTNO,
		KKTOUTKID,
		KNSSU,
		ODRSSFLG,
		YTIKSBR,
		HHKJKFLG,
		KSNDH,
		TRKDH
    FROM
        IRAI
    WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		ZSSDINO = :zssdino AND
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd FOR READ ONLY;
*/

#line 375 "Irai.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 377 "Irai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 377 "Irai.sqc"
  sqlaaloc(2,5,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 377 "Irai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 377 "Irai.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 377 "Irai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 377 "Irai.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 377 "Irai.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 377 "Irai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 377 "Irai.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 377 "Irai.sqc"
      sql_setdlist[2].sqldata = (void*)&zssdino;
#line 377 "Irai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 377 "Irai.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 377 "Irai.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 377 "Irai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 377 "Irai.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 377 "Irai.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 377 "Irai.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 377 "Irai.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 377 "Irai.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 377 "Irai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 377 "Irai.sqc"
  sqlastop(0L);
}

#line 377 "Irai.sqc"


    while( 1 ) {
        Irai* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:knsgrp,
			:kmkcd,
			:irihsmkbn,
			:irikbn,
			:ksktkbn,
			:sriymd,
			:kntno,
			:kntketflg,
			:chkmj,
			:stsrcd,
			:kmkrs,
			:oyakmkcd,
			:smpcd,
			:setkmkcd,
			:srinycd,
			:seccd,
			:skchkflg,
			:bkfkkbn,
			:ysnlbl,
			:skflg,
			:tkflg,
			:sjflg,
			:jktkflg,
			:kjno,
			:fkhkknohjkbn,
			:tbkjno,
			:tbkjflg,
			:htkfkhms,
			:tskflg,
			:tktflg,
			:bnckbn,
			:nbnckbn,
			:knskisyymd,
			:knskryymd,
			:knskrytme,
			:kkhkkflg,
			:kkiriflg,
			:kkirilotno,
			:kktoutkid,
			:knssu,
			:odrssflg,
			:ytiksbr,
			:hhkjkflg,
			:ksndh,
			:trkdh;
*/

{
#line 431 "Irai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 431 "Irai.sqc"
  sqlaaloc(3,49,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[49];
#line 431 "Irai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 431 "Irai.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 431 "Irai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 431 "Irai.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 431 "Irai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 431 "Irai.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 431 "Irai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 431 "Irai.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 431 "Irai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 431 "Irai.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 431 "Irai.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 431 "Irai.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 431 "Irai.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 431 "Irai.sqc"
      sql_setdlist[6].sqldata = (void*)&irihsmkbn;
#line 431 "Irai.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 431 "Irai.sqc"
      sql_setdlist[7].sqldata = (void*)&irikbn;
#line 431 "Irai.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 431 "Irai.sqc"
      sql_setdlist[8].sqldata = (void*)&ksktkbn;
#line 431 "Irai.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 431 "Irai.sqc"
      sql_setdlist[9].sqldata = (void*)sriymd;
#line 431 "Irai.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 14;
#line 431 "Irai.sqc"
      sql_setdlist[10].sqldata = (void*)kntno;
#line 431 "Irai.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 431 "Irai.sqc"
      sql_setdlist[11].sqldata = (void*)&kntketflg;
#line 431 "Irai.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 5;
#line 431 "Irai.sqc"
      sql_setdlist[12].sqldata = (void*)chkmj;
#line 431 "Irai.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 5;
#line 431 "Irai.sqc"
      sql_setdlist[13].sqldata = (void*)stsrcd;
#line 431 "Irai.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 17;
#line 431 "Irai.sqc"
      sql_setdlist[14].sqldata = (void*)kmkrs;
#line 431 "Irai.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 431 "Irai.sqc"
      sql_setdlist[15].sqldata = (void*)oyakmkcd;
#line 431 "Irai.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 8;
#line 431 "Irai.sqc"
      sql_setdlist[16].sqldata = (void*)smpcd;
#line 431 "Irai.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 8;
#line 431 "Irai.sqc"
      sql_setdlist[17].sqldata = (void*)setkmkcd;
#line 431 "Irai.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 431 "Irai.sqc"
      sql_setdlist[18].sqldata = (void*)&srinycd;
#line 431 "Irai.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 3;
#line 431 "Irai.sqc"
      sql_setdlist[19].sqldata = (void*)seccd;
#line 431 "Irai.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 431 "Irai.sqc"
      sql_setdlist[20].sqldata = (void*)&skchkflg;
#line 431 "Irai.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 431 "Irai.sqc"
      sql_setdlist[21].sqldata = (void*)&bkfkkbn;
#line 431 "Irai.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 3;
#line 431 "Irai.sqc"
      sql_setdlist[22].sqldata = (void*)ysnlbl;
#line 431 "Irai.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 431 "Irai.sqc"
      sql_setdlist[23].sqldata = (void*)&skflg;
#line 431 "Irai.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 431 "Irai.sqc"
      sql_setdlist[24].sqldata = (void*)&tkflg;
#line 431 "Irai.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 431 "Irai.sqc"
      sql_setdlist[25].sqldata = (void*)&sjflg;
#line 431 "Irai.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 431 "Irai.sqc"
      sql_setdlist[26].sqldata = (void*)&jktkflg;
#line 431 "Irai.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 4;
#line 431 "Irai.sqc"
      sql_setdlist[27].sqldata = (void*)kjno;
#line 431 "Irai.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 431 "Irai.sqc"
      sql_setdlist[28].sqldata = (void*)&fkhkknohjkbn;
#line 431 "Irai.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 4;
#line 431 "Irai.sqc"
      sql_setdlist[29].sqldata = (void*)tbkjno;
#line 431 "Irai.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 431 "Irai.sqc"
      sql_setdlist[30].sqldata = (void*)&tbkjflg;
#line 431 "Irai.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 25;
#line 431 "Irai.sqc"
      sql_setdlist[31].sqldata = (void*)htkfkhms;
#line 431 "Irai.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 431 "Irai.sqc"
      sql_setdlist[32].sqldata = (void*)tskflg;
#line 431 "Irai.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 431 "Irai.sqc"
      sql_setdlist[33].sqldata = (void*)tktflg;
#line 431 "Irai.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 431 "Irai.sqc"
      sql_setdlist[34].sqldata = (void*)&bnckbn;
#line 431 "Irai.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 431 "Irai.sqc"
      sql_setdlist[35].sqldata = (void*)&nbnckbn;
#line 431 "Irai.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 11;
#line 431 "Irai.sqc"
      sql_setdlist[36].sqldata = (void*)knskisyymd;
#line 431 "Irai.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 11;
#line 431 "Irai.sqc"
      sql_setdlist[37].sqldata = (void*)knskryymd;
#line 431 "Irai.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 9;
#line 431 "Irai.sqc"
      sql_setdlist[38].sqldata = (void*)knskrytme;
#line 431 "Irai.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 431 "Irai.sqc"
      sql_setdlist[39].sqldata = (void*)&kkhkkflg;
#line 431 "Irai.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 431 "Irai.sqc"
      sql_setdlist[40].sqldata = (void*)&kkiriflg;
#line 431 "Irai.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[41].sqltype = 500; sql_setdlist[41].sqllen = 2;
#line 431 "Irai.sqc"
      sql_setdlist[41].sqldata = (void*)&kkirilotno;
#line 431 "Irai.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 5;
#line 431 "Irai.sqc"
      sql_setdlist[42].sqldata = (void*)kktoutkid;
#line 431 "Irai.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[43].sqltype = 500; sql_setdlist[43].sqllen = 2;
#line 431 "Irai.sqc"
      sql_setdlist[43].sqldata = (void*)&knssu;
#line 431 "Irai.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 431 "Irai.sqc"
      sql_setdlist[44].sqldata = (void*)&odrssflg;
#line 431 "Irai.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 16;
#line 431 "Irai.sqc"
      sql_setdlist[45].sqldata = (void*)ytiksbr;
#line 431 "Irai.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 431 "Irai.sqc"
      sql_setdlist[46].sqldata = (void*)&hhkjkflg;
#line 431 "Irai.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 27;
#line 431 "Irai.sqc"
      sql_setdlist[47].sqldata = (void*)ksndh;
#line 431 "Irai.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 431 "Irai.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 27;
#line 431 "Irai.sqc"
      sql_setdlist[48].sqldata = (void*)trkdh;
#line 431 "Irai.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 431 "Irai.sqc"
      sqlasetdata(3,0,49,sql_setdlist,0L,0L);
    }
#line 431 "Irai.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 431 "Irai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 431 "Irai.sqc"
  sqlastop(0L);
}

#line 431 "Irai.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Irai*)ZbmlRealloc( array,
                                    sizeof( Irai ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Irai ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, IraiArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 446 "Irai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 446 "Irai.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 446 "Irai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 446 "Irai.sqc"
  sqlastop(0L);
}

#line 446 "Irai.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 454 "Irai.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbIraiInsert()
 *    IRAI レコードを挿入する
 * ■引数
 *    [I]  Irai* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbIraiInsert( Irai* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, IraiArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 477 "Irai.sqc"


    
/*
EXEC SQL INSERT INTO IRAI
    (
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		KNSGRP,
		KMKCD,
		IRIHSMKBN,
		IRIKBN,
		KSKTKBN,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		CHKMJ,
		STSRCD,
		KMKRS,
		OYAKMKCD,
		SMPCD,
		SETKMKCD,
		SRINYCD,
		SECCD,
		SKCHKFLG,
		BKFKKBN,
		YSNLBL,
		SKFLG,
		TKFLG,
		SJFLG,
		JKTKFLG,
		KJNO,
		FKHKKNOHJKBN,
		TBKJNO,
		TBKJFLG,
		HTKFKHMS,
		TSKFLG,
		TKTFLG,
		BNCKBN,
		NBNCKBN,
		KNSKISYYMD,
		KNSKRYYMD,
		KNSKRYTME,
		KKHKKFLG,
		KKIRIFLG,
		KKIRILOTNO,
		KKTOUTKID,
		KNSSU,
		ODRSSFLG,
		YTIKSBR,
		HHKJKFLG,
		KSNDH,
		TRKDH
    ) VALUES (
		:utkymd,
		:irino,
		:iriketflg,
		:zssdino,
		:knsgrp,
		:kmkcd,
		:irihsmkbn,
		:irikbn,
		:ksktkbn,
		:sriymd,
		:kntno,
		:kntketflg,
		:chkmj,
		:stsrcd,
		:kmkrs,
		:oyakmkcd,
		:smpcd,
		:setkmkcd,
		:srinycd,
		:seccd,
		:skchkflg,
		:bkfkkbn,
		:ysnlbl,
		:skflg,
		:tkflg,
		:sjflg,
		:jktkflg,
		:kjno,
		:fkhkknohjkbn,
		:tbkjno,
		:tbkjflg,
		:htkfkhms,
		:tskflg,
		:tktflg,
		:bnckbn,
		:nbnckbn,
		:knskisyymd,
		:knskryymd,
		:knskrytme,
		:kkhkkflg,
		:kkiriflg,
		:kkirilotno,
		:kktoutkid,
		:knssu,
		:odrssflg,
		:ytiksbr,
		:hhkjkflg,
		CURRENT TIMESTAMP,
		CURRENT TIMESTAMP
    );
*/

{
#line 580 "Irai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 580 "Irai.sqc"
  sqlaaloc(2,47,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[47];
#line 580 "Irai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 580 "Irai.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 580 "Irai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 580 "Irai.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 580 "Irai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 580 "Irai.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 580 "Irai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 580 "Irai.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 580 "Irai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 580 "Irai.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 580 "Irai.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 580 "Irai.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 580 "Irai.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 580 "Irai.sqc"
      sql_setdlist[6].sqldata = (void*)&irihsmkbn;
#line 580 "Irai.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 580 "Irai.sqc"
      sql_setdlist[7].sqldata = (void*)&irikbn;
#line 580 "Irai.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 580 "Irai.sqc"
      sql_setdlist[8].sqldata = (void*)&ksktkbn;
#line 580 "Irai.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 580 "Irai.sqc"
      sql_setdlist[9].sqldata = (void*)sriymd;
#line 580 "Irai.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 14;
#line 580 "Irai.sqc"
      sql_setdlist[10].sqldata = (void*)kntno;
#line 580 "Irai.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 580 "Irai.sqc"
      sql_setdlist[11].sqldata = (void*)&kntketflg;
#line 580 "Irai.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 5;
#line 580 "Irai.sqc"
      sql_setdlist[12].sqldata = (void*)chkmj;
#line 580 "Irai.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 5;
#line 580 "Irai.sqc"
      sql_setdlist[13].sqldata = (void*)stsrcd;
#line 580 "Irai.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 17;
#line 580 "Irai.sqc"
      sql_setdlist[14].sqldata = (void*)kmkrs;
#line 580 "Irai.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 580 "Irai.sqc"
      sql_setdlist[15].sqldata = (void*)oyakmkcd;
#line 580 "Irai.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 8;
#line 580 "Irai.sqc"
      sql_setdlist[16].sqldata = (void*)smpcd;
#line 580 "Irai.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 8;
#line 580 "Irai.sqc"
      sql_setdlist[17].sqldata = (void*)setkmkcd;
#line 580 "Irai.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 580 "Irai.sqc"
      sql_setdlist[18].sqldata = (void*)&srinycd;
#line 580 "Irai.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 3;
#line 580 "Irai.sqc"
      sql_setdlist[19].sqldata = (void*)seccd;
#line 580 "Irai.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 580 "Irai.sqc"
      sql_setdlist[20].sqldata = (void*)&skchkflg;
#line 580 "Irai.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 580 "Irai.sqc"
      sql_setdlist[21].sqldata = (void*)&bkfkkbn;
#line 580 "Irai.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 3;
#line 580 "Irai.sqc"
      sql_setdlist[22].sqldata = (void*)ysnlbl;
#line 580 "Irai.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 580 "Irai.sqc"
      sql_setdlist[23].sqldata = (void*)&skflg;
#line 580 "Irai.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 580 "Irai.sqc"
      sql_setdlist[24].sqldata = (void*)&tkflg;
#line 580 "Irai.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 580 "Irai.sqc"
      sql_setdlist[25].sqldata = (void*)&sjflg;
#line 580 "Irai.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 580 "Irai.sqc"
      sql_setdlist[26].sqldata = (void*)&jktkflg;
#line 580 "Irai.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 4;
#line 580 "Irai.sqc"
      sql_setdlist[27].sqldata = (void*)kjno;
#line 580 "Irai.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 580 "Irai.sqc"
      sql_setdlist[28].sqldata = (void*)&fkhkknohjkbn;
#line 580 "Irai.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 4;
#line 580 "Irai.sqc"
      sql_setdlist[29].sqldata = (void*)tbkjno;
#line 580 "Irai.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 580 "Irai.sqc"
      sql_setdlist[30].sqldata = (void*)&tbkjflg;
#line 580 "Irai.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 25;
#line 580 "Irai.sqc"
      sql_setdlist[31].sqldata = (void*)htkfkhms;
#line 580 "Irai.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 580 "Irai.sqc"
      sql_setdlist[32].sqldata = (void*)tskflg;
#line 580 "Irai.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 580 "Irai.sqc"
      sql_setdlist[33].sqldata = (void*)tktflg;
#line 580 "Irai.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 580 "Irai.sqc"
      sql_setdlist[34].sqldata = (void*)&bnckbn;
#line 580 "Irai.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 580 "Irai.sqc"
      sql_setdlist[35].sqldata = (void*)&nbnckbn;
#line 580 "Irai.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 11;
#line 580 "Irai.sqc"
      sql_setdlist[36].sqldata = (void*)knskisyymd;
#line 580 "Irai.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 11;
#line 580 "Irai.sqc"
      sql_setdlist[37].sqldata = (void*)knskryymd;
#line 580 "Irai.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 9;
#line 580 "Irai.sqc"
      sql_setdlist[38].sqldata = (void*)knskrytme;
#line 580 "Irai.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 580 "Irai.sqc"
      sql_setdlist[39].sqldata = (void*)&kkhkkflg;
#line 580 "Irai.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 580 "Irai.sqc"
      sql_setdlist[40].sqldata = (void*)&kkiriflg;
#line 580 "Irai.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[41].sqltype = 500; sql_setdlist[41].sqllen = 2;
#line 580 "Irai.sqc"
      sql_setdlist[41].sqldata = (void*)&kkirilotno;
#line 580 "Irai.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 5;
#line 580 "Irai.sqc"
      sql_setdlist[42].sqldata = (void*)kktoutkid;
#line 580 "Irai.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[43].sqltype = 500; sql_setdlist[43].sqllen = 2;
#line 580 "Irai.sqc"
      sql_setdlist[43].sqldata = (void*)&knssu;
#line 580 "Irai.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 580 "Irai.sqc"
      sql_setdlist[44].sqldata = (void*)&odrssflg;
#line 580 "Irai.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 16;
#line 580 "Irai.sqc"
      sql_setdlist[45].sqldata = (void*)ytiksbr;
#line 580 "Irai.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 580 "Irai.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 580 "Irai.sqc"
      sql_setdlist[46].sqldata = (void*)&hhkjkflg;
#line 580 "Irai.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 580 "Irai.sqc"
      sqlasetdata(2,0,47,sql_setdlist,0L,0L);
    }
#line 580 "Irai.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 580 "Irai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 580 "Irai.sqc"
  sqlastop(0L);
}

#line 580 "Irai.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 585 "Irai.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbIraiUpdate()
 *    IRAI レコードを更新する
 * ■引数
 *    [I]  Irai* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbIraiUpdate( Irai* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, IraiArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 609 "Irai.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 610 "Irai.sqc"


    
/*
EXEC SQL UPDATE IRAI
    SET (
		IRIKETFLG,
		IRIHSMKBN,
		IRIKBN,
		KSKTKBN,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		CHKMJ,
		STSRCD,
		KMKRS,
		OYAKMKCD,
		SMPCD,
		SETKMKCD,
		SRINYCD,
		SECCD,
		SKCHKFLG,
		BKFKKBN,
		YSNLBL,
		SKFLG,
		TKFLG,
		SJFLG,
		JKTKFLG,
		KJNO,
		FKHKKNOHJKBN,
		TBKJNO,
		TBKJFLG,
		HTKFKHMS,
		TSKFLG,
		TKTFLG,
		BNCKBN,
		NBNCKBN,
		KNSKISYYMD,
		KNSKRYYMD,
		KNSKRYTME,
		KKHKKFLG,
		KKIRIFLG,
		KKIRILOTNO,
		KKTOUTKID,
		KNSSU,
		ODRSSFLG,
		YTIKSBR,
		HHKJKFLG,
		KSNDH,
		TRKDH
    ) = (
		:iriketflg,
		:irihsmkbn,
		:irikbn,
		:ksktkbn,
		:sriymd,
		:kntno,
		:kntketflg,
		:chkmj,
		:stsrcd,
		:kmkrs,
		:oyakmkcd,
		:smpcd,
		:setkmkcd,
		:srinycd,
		:seccd,
		:skchkflg,
		:bkfkkbn,
		:ysnlbl,
		:skflg,
		:tkflg,
		:sjflg,
		:jktkflg,
		:kjno,
		:fkhkknohjkbn,
		:tbkjno,
		:tbkjflg,
		:htkfkhms,
		:tskflg,
		:tktflg,
		:bnckbn,
		:nbnckbn,
		:knskisyymd,
		:knskryymd,
		:knskrytme,
		:kkhkkflg,
		:kkiriflg,
		:kkirilotno,
		:kktoutkid,
		:knssu,
		:odrssflg,
		:ytiksbr,
		:hhkjkflg,
		CURRENT TIMESTAMP,
		:trkdh
    ) WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		ZSSDINO = :zssdino AND
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd;
*/

{
#line 708 "Irai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 708 "Irai.sqc"
  sqlaaloc(2,48,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[48];
#line 708 "Irai.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 708 "Irai.sqc"
      sql_setdlist[0].sqldata = (void*)&iriketflg;
#line 708 "Irai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 708 "Irai.sqc"
      sql_setdlist[1].sqldata = (void*)&irihsmkbn;
#line 708 "Irai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 708 "Irai.sqc"
      sql_setdlist[2].sqldata = (void*)&irikbn;
#line 708 "Irai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 708 "Irai.sqc"
      sql_setdlist[3].sqldata = (void*)&ksktkbn;
#line 708 "Irai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 708 "Irai.sqc"
      sql_setdlist[4].sqldata = (void*)sriymd;
#line 708 "Irai.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 14;
#line 708 "Irai.sqc"
      sql_setdlist[5].sqldata = (void*)kntno;
#line 708 "Irai.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 708 "Irai.sqc"
      sql_setdlist[6].sqldata = (void*)&kntketflg;
#line 708 "Irai.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 5;
#line 708 "Irai.sqc"
      sql_setdlist[7].sqldata = (void*)chkmj;
#line 708 "Irai.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 5;
#line 708 "Irai.sqc"
      sql_setdlist[8].sqldata = (void*)stsrcd;
#line 708 "Irai.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 17;
#line 708 "Irai.sqc"
      sql_setdlist[9].sqldata = (void*)kmkrs;
#line 708 "Irai.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 8;
#line 708 "Irai.sqc"
      sql_setdlist[10].sqldata = (void*)oyakmkcd;
#line 708 "Irai.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 8;
#line 708 "Irai.sqc"
      sql_setdlist[11].sqldata = (void*)smpcd;
#line 708 "Irai.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 8;
#line 708 "Irai.sqc"
      sql_setdlist[12].sqldata = (void*)setkmkcd;
#line 708 "Irai.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 708 "Irai.sqc"
      sql_setdlist[13].sqldata = (void*)&srinycd;
#line 708 "Irai.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 3;
#line 708 "Irai.sqc"
      sql_setdlist[14].sqldata = (void*)seccd;
#line 708 "Irai.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[15].sqltype = 452; sql_setdlist[15].sqllen = 1;
#line 708 "Irai.sqc"
      sql_setdlist[15].sqldata = (void*)&skchkflg;
#line 708 "Irai.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 708 "Irai.sqc"
      sql_setdlist[16].sqldata = (void*)&bkfkkbn;
#line 708 "Irai.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 3;
#line 708 "Irai.sqc"
      sql_setdlist[17].sqldata = (void*)ysnlbl;
#line 708 "Irai.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 708 "Irai.sqc"
      sql_setdlist[18].sqldata = (void*)&skflg;
#line 708 "Irai.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 708 "Irai.sqc"
      sql_setdlist[19].sqldata = (void*)&tkflg;
#line 708 "Irai.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 708 "Irai.sqc"
      sql_setdlist[20].sqldata = (void*)&sjflg;
#line 708 "Irai.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 708 "Irai.sqc"
      sql_setdlist[21].sqldata = (void*)&jktkflg;
#line 708 "Irai.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 4;
#line 708 "Irai.sqc"
      sql_setdlist[22].sqldata = (void*)kjno;
#line 708 "Irai.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 708 "Irai.sqc"
      sql_setdlist[23].sqldata = (void*)&fkhkknohjkbn;
#line 708 "Irai.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 4;
#line 708 "Irai.sqc"
      sql_setdlist[24].sqldata = (void*)tbkjno;
#line 708 "Irai.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 708 "Irai.sqc"
      sql_setdlist[25].sqldata = (void*)&tbkjflg;
#line 708 "Irai.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 25;
#line 708 "Irai.sqc"
      sql_setdlist[26].sqldata = (void*)htkfkhms;
#line 708 "Irai.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 3;
#line 708 "Irai.sqc"
      sql_setdlist[27].sqldata = (void*)tskflg;
#line 708 "Irai.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 3;
#line 708 "Irai.sqc"
      sql_setdlist[28].sqldata = (void*)tktflg;
#line 708 "Irai.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 708 "Irai.sqc"
      sql_setdlist[29].sqldata = (void*)&bnckbn;
#line 708 "Irai.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 708 "Irai.sqc"
      sql_setdlist[30].sqldata = (void*)&nbnckbn;
#line 708 "Irai.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 11;
#line 708 "Irai.sqc"
      sql_setdlist[31].sqldata = (void*)knskisyymd;
#line 708 "Irai.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 11;
#line 708 "Irai.sqc"
      sql_setdlist[32].sqldata = (void*)knskryymd;
#line 708 "Irai.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 9;
#line 708 "Irai.sqc"
      sql_setdlist[33].sqldata = (void*)knskrytme;
#line 708 "Irai.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 708 "Irai.sqc"
      sql_setdlist[34].sqldata = (void*)&kkhkkflg;
#line 708 "Irai.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 708 "Irai.sqc"
      sql_setdlist[35].sqldata = (void*)&kkiriflg;
#line 708 "Irai.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[36].sqltype = 500; sql_setdlist[36].sqllen = 2;
#line 708 "Irai.sqc"
      sql_setdlist[36].sqldata = (void*)&kkirilotno;
#line 708 "Irai.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 5;
#line 708 "Irai.sqc"
      sql_setdlist[37].sqldata = (void*)kktoutkid;
#line 708 "Irai.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[38].sqltype = 500; sql_setdlist[38].sqllen = 2;
#line 708 "Irai.sqc"
      sql_setdlist[38].sqldata = (void*)&knssu;
#line 708 "Irai.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 708 "Irai.sqc"
      sql_setdlist[39].sqldata = (void*)&odrssflg;
#line 708 "Irai.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 16;
#line 708 "Irai.sqc"
      sql_setdlist[40].sqldata = (void*)ytiksbr;
#line 708 "Irai.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 708 "Irai.sqc"
      sql_setdlist[41].sqldata = (void*)&hhkjkflg;
#line 708 "Irai.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 27;
#line 708 "Irai.sqc"
      sql_setdlist[42].sqldata = (void*)trkdh;
#line 708 "Irai.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 11;
#line 708 "Irai.sqc"
      sql_setdlist[43].sqldata = (void*)utkymd;
#line 708 "Irai.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 12;
#line 708 "Irai.sqc"
      sql_setdlist[44].sqldata = (void*)irino;
#line 708 "Irai.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[45].sqltype = 500; sql_setdlist[45].sqllen = 2;
#line 708 "Irai.sqc"
      sql_setdlist[45].sqldata = (void*)&zssdino;
#line 708 "Irai.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 17;
#line 708 "Irai.sqc"
      sql_setdlist[46].sqldata = (void*)knsgrp;
#line 708 "Irai.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 708 "Irai.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 8;
#line 708 "Irai.sqc"
      sql_setdlist[47].sqldata = (void*)kmkcd;
#line 708 "Irai.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 708 "Irai.sqc"
      sqlasetdata(2,0,48,sql_setdlist,0L,0L);
    }
#line 708 "Irai.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 708 "Irai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 708 "Irai.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 708 "Irai.sqc"
  sqlastop(0L);
}

#line 708 "Irai.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 713 "Irai.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 717 "Irai.sqc"

    return sqlca.sqlcode;
}
// UPD 2006-08-21 S.Ueda >>
long ZdbIraiUpdateSaiken( Irai* rec, short aKnssu )
{

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 723 "Irai.sqc"

	short	hKnssu;	// 検査回数

/*
EXEC SQL END DECLARE SECTION;
*/

#line 725 "Irai.sqc"


	// 検査回数をホスト変数へセット
	hKnssu = aKnssu;
//long ZdbIraiUpdateSaiken( Irai* rec )
//{
// UPD 2006-08-21 S.Ueda <<
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, IraiArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 738 "Irai.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 739 "Irai.sqc"


// UPD 2006-08-21 S.Ueda >>
    
/*
EXEC SQL UPDATE IRAI
    SET 	KSKTKBN = 'K',
		ODRSSFLG = '1' ,
		KNSSU = KNSSU + :hKnssu,
		KSNDH = CURRENT TIMESTAMP
    WHERE
		IRINO = :irino AND
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		ZSSDINO = :zssdino AND
		UTKYMD = :utkymd;
*/

{
#line 752 "Irai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 752 "Irai.sqc"
  sqlaaloc(2,6,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 752 "Irai.sqc"
      sql_setdlist[0].sqltype = 500; sql_setdlist[0].sqllen = 2;
#line 752 "Irai.sqc"
      sql_setdlist[0].sqldata = (void*)&hKnssu;
#line 752 "Irai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 752 "Irai.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 752 "Irai.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 752 "Irai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 752 "Irai.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 17;
#line 752 "Irai.sqc"
      sql_setdlist[2].sqldata = (void*)knsgrp;
#line 752 "Irai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 752 "Irai.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 752 "Irai.sqc"
      sql_setdlist[3].sqldata = (void*)kmkcd;
#line 752 "Irai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 752 "Irai.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 752 "Irai.sqc"
      sql_setdlist[4].sqldata = (void*)&zssdino;
#line 752 "Irai.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 752 "Irai.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 752 "Irai.sqc"
      sql_setdlist[5].sqldata = (void*)utkymd;
#line 752 "Irai.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 752 "Irai.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 752 "Irai.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 752 "Irai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 752 "Irai.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 752 "Irai.sqc"
  sqlastop(0L);
}

#line 752 "Irai.sqc"

//    EXEC SQL UPDATE IRAI
//   SET 	KSKTKBN = 'K',
//		ODRSSFLG = '1' ,
//		KNSSU = KNSSU + 1,
//		KSNDH = CURRENT TIMESTAMP
//   WHERE
//		IRINO = :irino AND
//		KNSGRP = :knsgrp AND
//		KMKCD = :kmkcd AND
//		ZSSDINO = :zssdino AND
//		UTKYMD = :utkymd;
// UPD 2006-08-21 S.Ueda <<

    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 769 "Irai.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 773 "Irai.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbIraiDelete()
 *    IRAI レコードを削除する
 * ■引数
 *    [I]  Irai* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbIraiDelete( Irai* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, IraiArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 797 "Irai.sqc"


    
/*
EXEC SQL DELETE FROM IRAI
    WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		ZSSDINO = :zssdino AND
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd;
*/

{
#line 805 "Irai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 805 "Irai.sqc"
  sqlaaloc(2,5,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 805 "Irai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 805 "Irai.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 805 "Irai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 805 "Irai.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 805 "Irai.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 805 "Irai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 805 "Irai.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 805 "Irai.sqc"
      sql_setdlist[2].sqldata = (void*)&zssdino;
#line 805 "Irai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 805 "Irai.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 805 "Irai.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 805 "Irai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 805 "Irai.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 805 "Irai.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 805 "Irai.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 805 "Irai.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 805 "Irai.sqc"
  sqlacall((unsigned short)24,6,2,0,0L);
#line 805 "Irai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 805 "Irai.sqc"
  sqlastop(0L);
}

#line 805 "Irai.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 810 "Irai.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
