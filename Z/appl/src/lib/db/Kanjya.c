static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,110,65,83,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,50,55,90,75,65,78,74,32,0,0,0,0,0,0,0,0,
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


#line 1 "Kanjya.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Kanjya.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Kanjya.h"
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


#line 24 "Kanjya.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Kanjya.sqc"

	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    sstcd[8];
	char    subsstcd[5];
	char    cdkbn1[3];
	char    cdkbn2[3];
	char    irimkey[41];
	char    srkcd[4];
	char    srknm[31];
	char    tticd[9];
	char    ttinm[41];
	char    gpcd[9];
	char    gpnm[41];
	char    skicd[9];
	char    skinm[41];
	char    krtno[41];
	char    knjid[16];
	char    knjnmn[61];
	char    knjnmk[31];
	char    knjnmkey[61];
	char    sc[6];
	char    tj[6];
	char    tjtni;
	char    sbtkbn;
	char    birthday[9];
	char    birthdaykbn;
	char    age[4];
	char    agekbn;
	char    btcd[11];
	char    btnm[31];
	char    utkcmtcd1[3];
	char    utkcmtcd2[3];
	char    utkcmtcd3[3];
	char    utkcmtfr1[71];
	char    utkcmtfr2[71];
	char    utkcmtfrflg;
	char    ngkbn;
	char    nsssu[3];
	char    hkncd;
	char    ktshsu[3];
	char    iniriymd[11];
	char    zssflg;
	char    kkiriflg;
	char    hknskbn;
	char    utkkbn;
	char    nekbn;
	char    inknskbn;
	char    utkjkkbn;
	char    krflg;
	char    fdhhkkflg;
	char    utkdh[9];
	char    mutkymd[11];
	char    mirino[12];
	char    knsjslbcd1[4];
	char    knsjslbcd2[4];
	char    knsjslbcd3[4];
	char    knsjslbcd4[4];
	char    ymhkkflg;
	char    hkkkbdh[9];
	char    ecd[4];
	char    shcd[3];
	char    sstssnmj[41];
	char    sstssnmn[41];
	char    sstrsj[21];
	char    sstrsn[21];
	char    sstsbt[3];
	char    ttsstflg;
	char    rucd[3];
	short   irikmksu;
	char    bmskn[51];
	char    irinrsbt[3];
	char    irihsmkbn;
	char    caresstflg;
	char    tktyflg;
	char    apkntino[14];
	char    sdnm[21];
	char    bko1[21];
	char    bko2[21];
	char    bko3[21];
	char    zstrdh[27];
	char    zsssdh[27];
	char    stlzsssdh[27];
	char    stlzsssip[16];
	char    stlzssssyaid[9];
	char    ksndh[27];
	char    oyasstcd[8];
	char    trkdh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 119 "Kanjya.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Kanjya

BmlDMMInfo	KanjyaArray[] = {
	DMM_SDATE( utkymd ),
	DMM_SSTRING( irino ),
	DMM_SCHAR( iriketflg ),
	DMM_SSHORT( zssdino ),
	DMM_SSTRING( sstcd ),
	DMM_SSTRING( subsstcd ),
	DMM_SSTRING( cdkbn1 ),
	DMM_SSTRING( cdkbn2 ),
	DMM_SSTRING( irimkey ),
	DMM_SSTRING( srkcd ),
	DMM_SSTRING( srknm ),
	DMM_SSTRING( tticd ),
	DMM_SSTRING( ttinm ),
	DMM_SSTRING( gpcd ),
	DMM_SSTRING( gpnm ),
	DMM_SSTRING( skicd ),
	DMM_SSTRING( skinm ),
	DMM_SSTRING( krtno ),
	DMM_SSTRING( knjid ),
	DMM_SSTRING( knjnmn ),
	DMM_SSTRING( knjnmk ),
	DMM_SSTRING( knjnmkey ),
	DMM_SSTRING( sc ),
	DMM_SSTRING( tj ),
	DMM_SCHAR( tjtni ),
	DMM_SCHAR( sbtkbn ),
	DMM_SSTRING( birthday ),
	DMM_SCHAR( birthdaykbn ),
	DMM_SSTRING( age ),
	DMM_SCHAR( agekbn ),
	DMM_SSTRING( btcd ),
	DMM_SSTRING( btnm ),
	DMM_SSTRING( utkcmtcd1 ),
	DMM_SSTRING( utkcmtcd2 ),
	DMM_SSTRING( utkcmtcd3 ),
	DMM_SSTRING( utkcmtfr1 ),
	DMM_SSTRING( utkcmtfr2 ),
	DMM_SCHAR( utkcmtfrflg ),
	DMM_SCHAR( ngkbn ),
	DMM_SSTRING( nsssu ),
	DMM_SCHAR( hkncd ),
	DMM_SSTRING( ktshsu ),
	DMM_SDATE( iniriymd ),
	DMM_SCHAR( zssflg ),
	DMM_SCHAR( kkiriflg ),
	DMM_SCHAR( hknskbn ),
	DMM_SCHAR( utkkbn ),
	DMM_SCHAR( nekbn ),
	DMM_SCHAR( inknskbn ),
	DMM_SCHAR( utkjkkbn ),
	DMM_SCHAR( krflg ),
	DMM_SCHAR( fdhhkkflg ),
	DMM_STIME( utkdh ),
	DMM_SDATE( mutkymd ),
	DMM_SSTRING( mirino ),
	DMM_SSTRING( knsjslbcd1 ),
	DMM_SSTRING( knsjslbcd2 ),
	DMM_SSTRING( knsjslbcd3 ),
	DMM_SSTRING( knsjslbcd4 ),
	DMM_SCHAR( ymhkkflg ),
	DMM_STIME( hkkkbdh ),
	DMM_SSTRING( ecd ),
	DMM_SSTRING( shcd ),
	DMM_SSTRING( sstssnmj ),
	DMM_SSTRING( sstssnmn ),
	DMM_SSTRING( sstrsj ),
	DMM_SSTRING( sstrsn ),
	DMM_SSTRING( sstsbt ),
	DMM_SCHAR( ttsstflg ),
	DMM_SSTRING( rucd ),
	DMM_SSHORT( irikmksu ),
	DMM_SSTRING( bmskn ),
	DMM_SSTRING( irinrsbt ),
	DMM_SCHAR( irihsmkbn ),
	DMM_SCHAR( caresstflg ),
	DMM_SCHAR( tktyflg ),
	DMM_SSTRING( apkntino ),
	DMM_SSTRING( sdnm ),
	DMM_SSTRING( bko1 ),
	DMM_SSTRING( bko2 ),
	DMM_SSTRING( bko3 ),
	DMM_STIMESTAMP( zstrdh ),
	DMM_STIMESTAMP( zsssdh ),
	DMM_STIMESTAMP( stlzsssdh ),
	DMM_SSTRING( stlzsssip ),
	DMM_SSTRING( stlzssssyaid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_SSTRING( oyasstcd ),
	DMM_STIMESTAMP( trkdh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKanjyaSelectAll()
 *    KANJYA レコード全件取得
 * ■引数
 *    [O]  Kanjya** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKanjyaSelectAll( Kanjya** arrayOut, int* numOut )
{
    Kanjya*     array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 236 "Kanjya.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		SSTCD,
		SUBSSTCD,
		CDKBN1,
		CDKBN2,
		IRIMKEY,
		SRKCD,
		SRKNM,
		TTICD,
		TTINM,
		GPCD,
		GPNM,
		SKICD,
		SKINM,
		KRTNO,
		KNJID,
		KNJNMN,
		KNJNMK,
		KNJNMKEY,
		SC,
		TJ,
		TJTNI,
		SBTKBN,
		BIRTHDAY,
		BIRTHDAYKBN,
		AGE,
		AGEKBN,
		BTCD,
		BTNM,
		UTKCMTCD1,
		UTKCMTCD2,
		UTKCMTCD3,
		UTKCMTFR1,
		UTKCMTFR2,
		UTKCMTFRFLG,
		NGKBN,
		NSSSU,
		HKNCD,
		KTSHSU,
		INIRIYMD,
		ZSSFLG,
		KKIRIFLG,
		HKNSKBN,
		UTKKBN,
		NEKBN,
		INKNSKBN,
		UTKJKKBN,
		KRFLG,
		FDHHKKFLG,
		UTKDH,
		MUTKYMD,
		MIRINO,
		KNSJSLBCD1,
		KNSJSLBCD2,
		KNSJSLBCD3,
		KNSJSLBCD4,
		YMHKKFLG,
		HKKKBDH,
		ECD,
		SHCD,
		SSTSSNMJ,
		SSTSSNMN,
		SSTRSJ,
		SSTRSN,
		SSTSBT,
		TTSSTFLG,
		RUCD,
		IRIKMKSU,
		BMSKN,
		IRINRSBT,
		IRIHSMKBN,
		CARESSTFLG,
		TKTYFLG,
		APKNTINO,
		SDNM,
		BKO1,
		BKO2,
		BKO3,
		ZSTRDH,
		ZSSSDH,
		STLZSSSDH,
		STLZSSSIP,
		STLZSSSSYAID,
		KSNDH,
		OYASSTCD,
		TRKDH
    FROM
        KANJYA FOR READ ONLY;
*/

#line 330 "Kanjya.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 332 "Kanjya.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 332 "Kanjya.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 332 "Kanjya.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 332 "Kanjya.sqc"
  sqlastop(0L);
}

#line 332 "Kanjya.sqc"


    while( 1 ) {
        Kanjya* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:sstcd,
			:subsstcd,
			:cdkbn1,
			:cdkbn2,
			:irimkey,
			:srkcd,
			:srknm,
			:tticd,
			:ttinm,
			:gpcd,
			:gpnm,
			:skicd,
			:skinm,
			:krtno,
			:knjid,
			:knjnmn,
			:knjnmk,
			:knjnmkey,
			:sc,
			:tj,
			:tjtni,
			:sbtkbn,
			:birthday,
			:birthdaykbn,
			:age,
			:agekbn,
			:btcd,
			:btnm,
			:utkcmtcd1,
			:utkcmtcd2,
			:utkcmtcd3,
			:utkcmtfr1,
			:utkcmtfr2,
			:utkcmtfrflg,
			:ngkbn,
			:nsssu,
			:hkncd,
			:ktshsu,
			:iniriymd,
			:zssflg,
			:kkiriflg,
			:hknskbn,
			:utkkbn,
			:nekbn,
			:inknskbn,
			:utkjkkbn,
			:krflg,
			:fdhhkkflg,
			:utkdh,
			:mutkymd,
			:mirino,
			:knsjslbcd1,
			:knsjslbcd2,
			:knsjslbcd3,
			:knsjslbcd4,
			:ymhkkflg,
			:hkkkbdh,
			:ecd,
			:shcd,
			:sstssnmj,
			:sstssnmn,
			:sstrsj,
			:sstrsn,
			:sstsbt,
			:ttsstflg,
			:rucd,
			:irikmksu,
			:bmskn,
			:irinrsbt,
			:irihsmkbn,
			:caresstflg,
			:tktyflg,
			:apkntino,
			:sdnm,
			:bko1,
			:bko2,
			:bko3,
			:zstrdh,
			:zsssdh,
			:stlzsssdh,
			:stlzsssip,
			:stlzssssyaid,
			:ksndh,
			:oyasstcd,
			:trkdh;
*/

{
#line 426 "Kanjya.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 426 "Kanjya.sqc"
  sqlaaloc(3,89,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 426 "Kanjya.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 426 "Kanjya.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 426 "Kanjya.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 426 "Kanjya.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 426 "Kanjya.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 426 "Kanjya.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 426 "Kanjya.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 426 "Kanjya.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 426 "Kanjya.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 426 "Kanjya.sqc"
      sql_setdlist[4].sqldata = (void*)sstcd;
#line 426 "Kanjya.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 5;
#line 426 "Kanjya.sqc"
      sql_setdlist[5].sqldata = (void*)subsstcd;
#line 426 "Kanjya.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 3;
#line 426 "Kanjya.sqc"
      sql_setdlist[6].sqldata = (void*)cdkbn1;
#line 426 "Kanjya.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 426 "Kanjya.sqc"
      sql_setdlist[7].sqldata = (void*)cdkbn2;
#line 426 "Kanjya.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 41;
#line 426 "Kanjya.sqc"
      sql_setdlist[8].sqldata = (void*)irimkey;
#line 426 "Kanjya.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 4;
#line 426 "Kanjya.sqc"
      sql_setdlist[9].sqldata = (void*)srkcd;
#line 426 "Kanjya.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 31;
#line 426 "Kanjya.sqc"
      sql_setdlist[10].sqldata = (void*)srknm;
#line 426 "Kanjya.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 426 "Kanjya.sqc"
      sql_setdlist[11].sqldata = (void*)tticd;
#line 426 "Kanjya.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 41;
#line 426 "Kanjya.sqc"
      sql_setdlist[12].sqldata = (void*)ttinm;
#line 426 "Kanjya.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 426 "Kanjya.sqc"
      sql_setdlist[13].sqldata = (void*)gpcd;
#line 426 "Kanjya.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 41;
#line 426 "Kanjya.sqc"
      sql_setdlist[14].sqldata = (void*)gpnm;
#line 426 "Kanjya.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 426 "Kanjya.sqc"
      sql_setdlist[15].sqldata = (void*)skicd;
#line 426 "Kanjya.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 41;
#line 426 "Kanjya.sqc"
      sql_setdlist[16].sqldata = (void*)skinm;
#line 426 "Kanjya.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 41;
#line 426 "Kanjya.sqc"
      sql_setdlist[17].sqldata = (void*)krtno;
#line 426 "Kanjya.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 16;
#line 426 "Kanjya.sqc"
      sql_setdlist[18].sqldata = (void*)knjid;
#line 426 "Kanjya.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 61;
#line 426 "Kanjya.sqc"
      sql_setdlist[19].sqldata = (void*)knjnmn;
#line 426 "Kanjya.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 31;
#line 426 "Kanjya.sqc"
      sql_setdlist[20].sqldata = (void*)knjnmk;
#line 426 "Kanjya.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 61;
#line 426 "Kanjya.sqc"
      sql_setdlist[21].sqldata = (void*)knjnmkey;
#line 426 "Kanjya.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 6;
#line 426 "Kanjya.sqc"
      sql_setdlist[22].sqldata = (void*)sc;
#line 426 "Kanjya.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 6;
#line 426 "Kanjya.sqc"
      sql_setdlist[23].sqldata = (void*)tj;
#line 426 "Kanjya.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 426 "Kanjya.sqc"
      sql_setdlist[24].sqldata = (void*)&tjtni;
#line 426 "Kanjya.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 426 "Kanjya.sqc"
      sql_setdlist[25].sqldata = (void*)&sbtkbn;
#line 426 "Kanjya.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 9;
#line 426 "Kanjya.sqc"
      sql_setdlist[26].sqldata = (void*)birthday;
#line 426 "Kanjya.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 426 "Kanjya.sqc"
      sql_setdlist[27].sqldata = (void*)&birthdaykbn;
#line 426 "Kanjya.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 4;
#line 426 "Kanjya.sqc"
      sql_setdlist[28].sqldata = (void*)age;
#line 426 "Kanjya.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 426 "Kanjya.sqc"
      sql_setdlist[29].sqldata = (void*)&agekbn;
#line 426 "Kanjya.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 11;
#line 426 "Kanjya.sqc"
      sql_setdlist[30].sqldata = (void*)btcd;
#line 426 "Kanjya.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 31;
#line 426 "Kanjya.sqc"
      sql_setdlist[31].sqldata = (void*)btnm;
#line 426 "Kanjya.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 426 "Kanjya.sqc"
      sql_setdlist[32].sqldata = (void*)utkcmtcd1;
#line 426 "Kanjya.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 426 "Kanjya.sqc"
      sql_setdlist[33].sqldata = (void*)utkcmtcd2;
#line 426 "Kanjya.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 3;
#line 426 "Kanjya.sqc"
      sql_setdlist[34].sqldata = (void*)utkcmtcd3;
#line 426 "Kanjya.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 71;
#line 426 "Kanjya.sqc"
      sql_setdlist[35].sqldata = (void*)utkcmtfr1;
#line 426 "Kanjya.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 71;
#line 426 "Kanjya.sqc"
      sql_setdlist[36].sqldata = (void*)utkcmtfr2;
#line 426 "Kanjya.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 426 "Kanjya.sqc"
      sql_setdlist[37].sqldata = (void*)&utkcmtfrflg;
#line 426 "Kanjya.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 426 "Kanjya.sqc"
      sql_setdlist[38].sqldata = (void*)&ngkbn;
#line 426 "Kanjya.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 3;
#line 426 "Kanjya.sqc"
      sql_setdlist[39].sqldata = (void*)nsssu;
#line 426 "Kanjya.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 426 "Kanjya.sqc"
      sql_setdlist[40].sqldata = (void*)&hkncd;
#line 426 "Kanjya.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 426 "Kanjya.sqc"
      sql_setdlist[41].sqldata = (void*)ktshsu;
#line 426 "Kanjya.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 11;
#line 426 "Kanjya.sqc"
      sql_setdlist[42].sqldata = (void*)iniriymd;
#line 426 "Kanjya.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 426 "Kanjya.sqc"
      sql_setdlist[43].sqldata = (void*)&zssflg;
#line 426 "Kanjya.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 426 "Kanjya.sqc"
      sql_setdlist[44].sqldata = (void*)&kkiriflg;
#line 426 "Kanjya.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[45].sqltype = 452; sql_setdlist[45].sqllen = 1;
#line 426 "Kanjya.sqc"
      sql_setdlist[45].sqldata = (void*)&hknskbn;
#line 426 "Kanjya.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 426 "Kanjya.sqc"
      sql_setdlist[46].sqldata = (void*)&utkkbn;
#line 426 "Kanjya.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 426 "Kanjya.sqc"
      sql_setdlist[47].sqldata = (void*)&nekbn;
#line 426 "Kanjya.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 426 "Kanjya.sqc"
      sql_setdlist[48].sqldata = (void*)&inknskbn;
#line 426 "Kanjya.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[49].sqltype = 452; sql_setdlist[49].sqllen = 1;
#line 426 "Kanjya.sqc"
      sql_setdlist[49].sqldata = (void*)&utkjkkbn;
#line 426 "Kanjya.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[50].sqltype = 452; sql_setdlist[50].sqllen = 1;
#line 426 "Kanjya.sqc"
      sql_setdlist[50].sqldata = (void*)&krflg;
#line 426 "Kanjya.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[51].sqltype = 452; sql_setdlist[51].sqllen = 1;
#line 426 "Kanjya.sqc"
      sql_setdlist[51].sqldata = (void*)&fdhhkkflg;
#line 426 "Kanjya.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 9;
#line 426 "Kanjya.sqc"
      sql_setdlist[52].sqldata = (void*)utkdh;
#line 426 "Kanjya.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 11;
#line 426 "Kanjya.sqc"
      sql_setdlist[53].sqldata = (void*)mutkymd;
#line 426 "Kanjya.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 12;
#line 426 "Kanjya.sqc"
      sql_setdlist[54].sqldata = (void*)mirino;
#line 426 "Kanjya.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 426 "Kanjya.sqc"
      sql_setdlist[55].sqldata = (void*)knsjslbcd1;
#line 426 "Kanjya.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 4;
#line 426 "Kanjya.sqc"
      sql_setdlist[56].sqldata = (void*)knsjslbcd2;
#line 426 "Kanjya.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 4;
#line 426 "Kanjya.sqc"
      sql_setdlist[57].sqldata = (void*)knsjslbcd3;
#line 426 "Kanjya.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[58].sqltype = 460; sql_setdlist[58].sqllen = 4;
#line 426 "Kanjya.sqc"
      sql_setdlist[58].sqldata = (void*)knsjslbcd4;
#line 426 "Kanjya.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[59].sqltype = 452; sql_setdlist[59].sqllen = 1;
#line 426 "Kanjya.sqc"
      sql_setdlist[59].sqldata = (void*)&ymhkkflg;
#line 426 "Kanjya.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[60].sqltype = 460; sql_setdlist[60].sqllen = 9;
#line 426 "Kanjya.sqc"
      sql_setdlist[60].sqldata = (void*)hkkkbdh;
#line 426 "Kanjya.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[61].sqltype = 460; sql_setdlist[61].sqllen = 4;
#line 426 "Kanjya.sqc"
      sql_setdlist[61].sqldata = (void*)ecd;
#line 426 "Kanjya.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[62].sqltype = 460; sql_setdlist[62].sqllen = 3;
#line 426 "Kanjya.sqc"
      sql_setdlist[62].sqldata = (void*)shcd;
#line 426 "Kanjya.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[63].sqltype = 460; sql_setdlist[63].sqllen = 41;
#line 426 "Kanjya.sqc"
      sql_setdlist[63].sqldata = (void*)sstssnmj;
#line 426 "Kanjya.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sqlasetdata(3,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[25];
#line 426 "Kanjya.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 41;
#line 426 "Kanjya.sqc"
      sql_setdlist[0].sqldata = (void*)sstssnmn;
#line 426 "Kanjya.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 426 "Kanjya.sqc"
      sql_setdlist[1].sqldata = (void*)sstrsj;
#line 426 "Kanjya.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 426 "Kanjya.sqc"
      sql_setdlist[2].sqldata = (void*)sstrsn;
#line 426 "Kanjya.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 426 "Kanjya.sqc"
      sql_setdlist[3].sqldata = (void*)sstsbt;
#line 426 "Kanjya.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 426 "Kanjya.sqc"
      sql_setdlist[4].sqldata = (void*)&ttsstflg;
#line 426 "Kanjya.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 426 "Kanjya.sqc"
      sql_setdlist[5].sqldata = (void*)rucd;
#line 426 "Kanjya.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 426 "Kanjya.sqc"
      sql_setdlist[6].sqldata = (void*)&irikmksu;
#line 426 "Kanjya.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 426 "Kanjya.sqc"
      sql_setdlist[7].sqldata = (void*)bmskn;
#line 426 "Kanjya.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 3;
#line 426 "Kanjya.sqc"
      sql_setdlist[8].sqldata = (void*)irinrsbt;
#line 426 "Kanjya.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 426 "Kanjya.sqc"
      sql_setdlist[9].sqldata = (void*)&irihsmkbn;
#line 426 "Kanjya.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 426 "Kanjya.sqc"
      sql_setdlist[10].sqldata = (void*)&caresstflg;
#line 426 "Kanjya.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 426 "Kanjya.sqc"
      sql_setdlist[11].sqldata = (void*)&tktyflg;
#line 426 "Kanjya.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 14;
#line 426 "Kanjya.sqc"
      sql_setdlist[12].sqldata = (void*)apkntino;
#line 426 "Kanjya.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 426 "Kanjya.sqc"
      sql_setdlist[13].sqldata = (void*)sdnm;
#line 426 "Kanjya.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 21;
#line 426 "Kanjya.sqc"
      sql_setdlist[14].sqldata = (void*)bko1;
#line 426 "Kanjya.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 21;
#line 426 "Kanjya.sqc"
      sql_setdlist[15].sqldata = (void*)bko2;
#line 426 "Kanjya.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 21;
#line 426 "Kanjya.sqc"
      sql_setdlist[16].sqldata = (void*)bko3;
#line 426 "Kanjya.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 426 "Kanjya.sqc"
      sql_setdlist[17].sqldata = (void*)zstrdh;
#line 426 "Kanjya.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 426 "Kanjya.sqc"
      sql_setdlist[18].sqldata = (void*)zsssdh;
#line 426 "Kanjya.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 426 "Kanjya.sqc"
      sql_setdlist[19].sqldata = (void*)stlzsssdh;
#line 426 "Kanjya.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 16;
#line 426 "Kanjya.sqc"
      sql_setdlist[20].sqldata = (void*)stlzsssip;
#line 426 "Kanjya.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 9;
#line 426 "Kanjya.sqc"
      sql_setdlist[21].sqldata = (void*)stlzssssyaid;
#line 426 "Kanjya.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 27;
#line 426 "Kanjya.sqc"
      sql_setdlist[22].sqldata = (void*)ksndh;
#line 426 "Kanjya.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 426 "Kanjya.sqc"
      sql_setdlist[23].sqldata = (void*)oyasstcd;
#line 426 "Kanjya.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 27;
#line 426 "Kanjya.sqc"
      sql_setdlist[24].sqldata = (void*)trkdh;
#line 426 "Kanjya.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 426 "Kanjya.sqc"
      sqlasetdata(3,64,25,sql_setdlist,0L,0L);
    }
#line 426 "Kanjya.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 426 "Kanjya.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 426 "Kanjya.sqc"
  sqlastop(0L);
}

#line 426 "Kanjya.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kanjya*)ZbmlRealloc( array,
                                    sizeof( Kanjya ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kanjya ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KanjyaArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 441 "Kanjya.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 441 "Kanjya.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 441 "Kanjya.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 441 "Kanjya.sqc"
  sqlastop(0L);
}

#line 441 "Kanjya.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 449 "Kanjya.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKanjyaSelectKey()
 *    KANJYA レコードKey条件取得
 * ■引数
 *    [I]  Kanjya* pKey       取得するレコードのキー
 *    [O]  Kanjya** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKanjyaSelectKey( Kanjya* pKey, Kanjya** arrayOut, int* numOut )
{
    Kanjya*     array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KanjyaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 475 "Kanjya.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		SSTCD,
		SUBSSTCD,
		CDKBN1,
		CDKBN2,
		IRIMKEY,
		SRKCD,
		SRKNM,
		TTICD,
		TTINM,
		GPCD,
		GPNM,
		SKICD,
		SKINM,
		KRTNO,
		KNJID,
		KNJNMN,
		KNJNMK,
		KNJNMKEY,
		SC,
		TJ,
		TJTNI,
		SBTKBN,
		BIRTHDAY,
		BIRTHDAYKBN,
		AGE,
		AGEKBN,
		BTCD,
		BTNM,
		UTKCMTCD1,
		UTKCMTCD2,
		UTKCMTCD3,
		UTKCMTFR1,
		UTKCMTFR2,
		UTKCMTFRFLG,
		NGKBN,
		NSSSU,
		HKNCD,
		KTSHSU,
		INIRIYMD,
		ZSSFLG,
		KKIRIFLG,
		HKNSKBN,
		UTKKBN,
		NEKBN,
		INKNSKBN,
		UTKJKKBN,
		KRFLG,
		FDHHKKFLG,
		UTKDH,
		MUTKYMD,
		MIRINO,
		KNSJSLBCD1,
		KNSJSLBCD2,
		KNSJSLBCD3,
		KNSJSLBCD4,
		YMHKKFLG,
		HKKKBDH,
		ECD,
		SHCD,
		SSTSSNMJ,
		SSTSSNMN,
		SSTRSJ,
		SSTRSN,
		SSTSBT,
		TTSSTFLG,
		RUCD,
		IRIKMKSU,
		BMSKN,
		IRINRSBT,
		IRIHSMKBN,
		CARESSTFLG,
		TKTYFLG,
		APKNTINO,
		SDNM,
		BKO1,
		BKO2,
		BKO3,
		ZSTRDH,
		ZSSSDH,
		STLZSSSDH,
		STLZSSSIP,
		STLZSSSSYAID,
		KSNDH,
		OYASSTCD,
		TRKDH
    FROM
        KANJYA
    WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		ZSSDINO = :zssdino FOR READ ONLY;
*/

#line 573 "Kanjya.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 575 "Kanjya.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 575 "Kanjya.sqc"
  sqlaaloc(2,3,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 575 "Kanjya.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 575 "Kanjya.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 575 "Kanjya.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 575 "Kanjya.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 575 "Kanjya.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 575 "Kanjya.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 575 "Kanjya.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 575 "Kanjya.sqc"
      sql_setdlist[2].sqldata = (void*)&zssdino;
#line 575 "Kanjya.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 575 "Kanjya.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 575 "Kanjya.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 575 "Kanjya.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 575 "Kanjya.sqc"
  sqlastop(0L);
}

#line 575 "Kanjya.sqc"


    while( 1 ) {
        Kanjya* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:sstcd,
			:subsstcd,
			:cdkbn1,
			:cdkbn2,
			:irimkey,
			:srkcd,
			:srknm,
			:tticd,
			:ttinm,
			:gpcd,
			:gpnm,
			:skicd,
			:skinm,
			:krtno,
			:knjid,
			:knjnmn,
			:knjnmk,
			:knjnmkey,
			:sc,
			:tj,
			:tjtni,
			:sbtkbn,
			:birthday,
			:birthdaykbn,
			:age,
			:agekbn,
			:btcd,
			:btnm,
			:utkcmtcd1,
			:utkcmtcd2,
			:utkcmtcd3,
			:utkcmtfr1,
			:utkcmtfr2,
			:utkcmtfrflg,
			:ngkbn,
			:nsssu,
			:hkncd,
			:ktshsu,
			:iniriymd,
			:zssflg,
			:kkiriflg,
			:hknskbn,
			:utkkbn,
			:nekbn,
			:inknskbn,
			:utkjkkbn,
			:krflg,
			:fdhhkkflg,
			:utkdh,
			:mutkymd,
			:mirino,
			:knsjslbcd1,
			:knsjslbcd2,
			:knsjslbcd3,
			:knsjslbcd4,
			:ymhkkflg,
			:hkkkbdh,
			:ecd,
			:shcd,
			:sstssnmj,
			:sstssnmn,
			:sstrsj,
			:sstrsn,
			:sstsbt,
			:ttsstflg,
			:rucd,
			:irikmksu,
			:bmskn,
			:irinrsbt,
			:irihsmkbn,
			:caresstflg,
			:tktyflg,
			:apkntino,
			:sdnm,
			:bko1,
			:bko2,
			:bko3,
			:zstrdh,
			:zsssdh,
			:stlzsssdh,
			:stlzsssip,
			:stlzssssyaid,
			:ksndh,
			:oyasstcd,
			:trkdh;
*/

{
#line 669 "Kanjya.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 669 "Kanjya.sqc"
  sqlaaloc(3,89,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 669 "Kanjya.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 669 "Kanjya.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 669 "Kanjya.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 669 "Kanjya.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 669 "Kanjya.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 669 "Kanjya.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 669 "Kanjya.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 669 "Kanjya.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 669 "Kanjya.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 669 "Kanjya.sqc"
      sql_setdlist[4].sqldata = (void*)sstcd;
#line 669 "Kanjya.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 5;
#line 669 "Kanjya.sqc"
      sql_setdlist[5].sqldata = (void*)subsstcd;
#line 669 "Kanjya.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 3;
#line 669 "Kanjya.sqc"
      sql_setdlist[6].sqldata = (void*)cdkbn1;
#line 669 "Kanjya.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 669 "Kanjya.sqc"
      sql_setdlist[7].sqldata = (void*)cdkbn2;
#line 669 "Kanjya.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 41;
#line 669 "Kanjya.sqc"
      sql_setdlist[8].sqldata = (void*)irimkey;
#line 669 "Kanjya.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 4;
#line 669 "Kanjya.sqc"
      sql_setdlist[9].sqldata = (void*)srkcd;
#line 669 "Kanjya.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 31;
#line 669 "Kanjya.sqc"
      sql_setdlist[10].sqldata = (void*)srknm;
#line 669 "Kanjya.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 669 "Kanjya.sqc"
      sql_setdlist[11].sqldata = (void*)tticd;
#line 669 "Kanjya.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 41;
#line 669 "Kanjya.sqc"
      sql_setdlist[12].sqldata = (void*)ttinm;
#line 669 "Kanjya.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 669 "Kanjya.sqc"
      sql_setdlist[13].sqldata = (void*)gpcd;
#line 669 "Kanjya.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 41;
#line 669 "Kanjya.sqc"
      sql_setdlist[14].sqldata = (void*)gpnm;
#line 669 "Kanjya.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 669 "Kanjya.sqc"
      sql_setdlist[15].sqldata = (void*)skicd;
#line 669 "Kanjya.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 41;
#line 669 "Kanjya.sqc"
      sql_setdlist[16].sqldata = (void*)skinm;
#line 669 "Kanjya.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 41;
#line 669 "Kanjya.sqc"
      sql_setdlist[17].sqldata = (void*)krtno;
#line 669 "Kanjya.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 16;
#line 669 "Kanjya.sqc"
      sql_setdlist[18].sqldata = (void*)knjid;
#line 669 "Kanjya.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 61;
#line 669 "Kanjya.sqc"
      sql_setdlist[19].sqldata = (void*)knjnmn;
#line 669 "Kanjya.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 31;
#line 669 "Kanjya.sqc"
      sql_setdlist[20].sqldata = (void*)knjnmk;
#line 669 "Kanjya.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 61;
#line 669 "Kanjya.sqc"
      sql_setdlist[21].sqldata = (void*)knjnmkey;
#line 669 "Kanjya.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 6;
#line 669 "Kanjya.sqc"
      sql_setdlist[22].sqldata = (void*)sc;
#line 669 "Kanjya.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 6;
#line 669 "Kanjya.sqc"
      sql_setdlist[23].sqldata = (void*)tj;
#line 669 "Kanjya.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 669 "Kanjya.sqc"
      sql_setdlist[24].sqldata = (void*)&tjtni;
#line 669 "Kanjya.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 669 "Kanjya.sqc"
      sql_setdlist[25].sqldata = (void*)&sbtkbn;
#line 669 "Kanjya.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 9;
#line 669 "Kanjya.sqc"
      sql_setdlist[26].sqldata = (void*)birthday;
#line 669 "Kanjya.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 669 "Kanjya.sqc"
      sql_setdlist[27].sqldata = (void*)&birthdaykbn;
#line 669 "Kanjya.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 4;
#line 669 "Kanjya.sqc"
      sql_setdlist[28].sqldata = (void*)age;
#line 669 "Kanjya.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 669 "Kanjya.sqc"
      sql_setdlist[29].sqldata = (void*)&agekbn;
#line 669 "Kanjya.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 11;
#line 669 "Kanjya.sqc"
      sql_setdlist[30].sqldata = (void*)btcd;
#line 669 "Kanjya.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 31;
#line 669 "Kanjya.sqc"
      sql_setdlist[31].sqldata = (void*)btnm;
#line 669 "Kanjya.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 669 "Kanjya.sqc"
      sql_setdlist[32].sqldata = (void*)utkcmtcd1;
#line 669 "Kanjya.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 669 "Kanjya.sqc"
      sql_setdlist[33].sqldata = (void*)utkcmtcd2;
#line 669 "Kanjya.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 3;
#line 669 "Kanjya.sqc"
      sql_setdlist[34].sqldata = (void*)utkcmtcd3;
#line 669 "Kanjya.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 71;
#line 669 "Kanjya.sqc"
      sql_setdlist[35].sqldata = (void*)utkcmtfr1;
#line 669 "Kanjya.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 71;
#line 669 "Kanjya.sqc"
      sql_setdlist[36].sqldata = (void*)utkcmtfr2;
#line 669 "Kanjya.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 669 "Kanjya.sqc"
      sql_setdlist[37].sqldata = (void*)&utkcmtfrflg;
#line 669 "Kanjya.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 669 "Kanjya.sqc"
      sql_setdlist[38].sqldata = (void*)&ngkbn;
#line 669 "Kanjya.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 3;
#line 669 "Kanjya.sqc"
      sql_setdlist[39].sqldata = (void*)nsssu;
#line 669 "Kanjya.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 669 "Kanjya.sqc"
      sql_setdlist[40].sqldata = (void*)&hkncd;
#line 669 "Kanjya.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 669 "Kanjya.sqc"
      sql_setdlist[41].sqldata = (void*)ktshsu;
#line 669 "Kanjya.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 11;
#line 669 "Kanjya.sqc"
      sql_setdlist[42].sqldata = (void*)iniriymd;
#line 669 "Kanjya.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 669 "Kanjya.sqc"
      sql_setdlist[43].sqldata = (void*)&zssflg;
#line 669 "Kanjya.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 669 "Kanjya.sqc"
      sql_setdlist[44].sqldata = (void*)&kkiriflg;
#line 669 "Kanjya.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[45].sqltype = 452; sql_setdlist[45].sqllen = 1;
#line 669 "Kanjya.sqc"
      sql_setdlist[45].sqldata = (void*)&hknskbn;
#line 669 "Kanjya.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 669 "Kanjya.sqc"
      sql_setdlist[46].sqldata = (void*)&utkkbn;
#line 669 "Kanjya.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 669 "Kanjya.sqc"
      sql_setdlist[47].sqldata = (void*)&nekbn;
#line 669 "Kanjya.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 669 "Kanjya.sqc"
      sql_setdlist[48].sqldata = (void*)&inknskbn;
#line 669 "Kanjya.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[49].sqltype = 452; sql_setdlist[49].sqllen = 1;
#line 669 "Kanjya.sqc"
      sql_setdlist[49].sqldata = (void*)&utkjkkbn;
#line 669 "Kanjya.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[50].sqltype = 452; sql_setdlist[50].sqllen = 1;
#line 669 "Kanjya.sqc"
      sql_setdlist[50].sqldata = (void*)&krflg;
#line 669 "Kanjya.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[51].sqltype = 452; sql_setdlist[51].sqllen = 1;
#line 669 "Kanjya.sqc"
      sql_setdlist[51].sqldata = (void*)&fdhhkkflg;
#line 669 "Kanjya.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 9;
#line 669 "Kanjya.sqc"
      sql_setdlist[52].sqldata = (void*)utkdh;
#line 669 "Kanjya.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 11;
#line 669 "Kanjya.sqc"
      sql_setdlist[53].sqldata = (void*)mutkymd;
#line 669 "Kanjya.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 12;
#line 669 "Kanjya.sqc"
      sql_setdlist[54].sqldata = (void*)mirino;
#line 669 "Kanjya.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 669 "Kanjya.sqc"
      sql_setdlist[55].sqldata = (void*)knsjslbcd1;
#line 669 "Kanjya.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 4;
#line 669 "Kanjya.sqc"
      sql_setdlist[56].sqldata = (void*)knsjslbcd2;
#line 669 "Kanjya.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 4;
#line 669 "Kanjya.sqc"
      sql_setdlist[57].sqldata = (void*)knsjslbcd3;
#line 669 "Kanjya.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[58].sqltype = 460; sql_setdlist[58].sqllen = 4;
#line 669 "Kanjya.sqc"
      sql_setdlist[58].sqldata = (void*)knsjslbcd4;
#line 669 "Kanjya.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[59].sqltype = 452; sql_setdlist[59].sqllen = 1;
#line 669 "Kanjya.sqc"
      sql_setdlist[59].sqldata = (void*)&ymhkkflg;
#line 669 "Kanjya.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[60].sqltype = 460; sql_setdlist[60].sqllen = 9;
#line 669 "Kanjya.sqc"
      sql_setdlist[60].sqldata = (void*)hkkkbdh;
#line 669 "Kanjya.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[61].sqltype = 460; sql_setdlist[61].sqllen = 4;
#line 669 "Kanjya.sqc"
      sql_setdlist[61].sqldata = (void*)ecd;
#line 669 "Kanjya.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[62].sqltype = 460; sql_setdlist[62].sqllen = 3;
#line 669 "Kanjya.sqc"
      sql_setdlist[62].sqldata = (void*)shcd;
#line 669 "Kanjya.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[63].sqltype = 460; sql_setdlist[63].sqllen = 41;
#line 669 "Kanjya.sqc"
      sql_setdlist[63].sqldata = (void*)sstssnmj;
#line 669 "Kanjya.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sqlasetdata(3,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[25];
#line 669 "Kanjya.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 41;
#line 669 "Kanjya.sqc"
      sql_setdlist[0].sqldata = (void*)sstssnmn;
#line 669 "Kanjya.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 669 "Kanjya.sqc"
      sql_setdlist[1].sqldata = (void*)sstrsj;
#line 669 "Kanjya.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 669 "Kanjya.sqc"
      sql_setdlist[2].sqldata = (void*)sstrsn;
#line 669 "Kanjya.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 669 "Kanjya.sqc"
      sql_setdlist[3].sqldata = (void*)sstsbt;
#line 669 "Kanjya.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 669 "Kanjya.sqc"
      sql_setdlist[4].sqldata = (void*)&ttsstflg;
#line 669 "Kanjya.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 669 "Kanjya.sqc"
      sql_setdlist[5].sqldata = (void*)rucd;
#line 669 "Kanjya.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 669 "Kanjya.sqc"
      sql_setdlist[6].sqldata = (void*)&irikmksu;
#line 669 "Kanjya.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 669 "Kanjya.sqc"
      sql_setdlist[7].sqldata = (void*)bmskn;
#line 669 "Kanjya.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 3;
#line 669 "Kanjya.sqc"
      sql_setdlist[8].sqldata = (void*)irinrsbt;
#line 669 "Kanjya.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 669 "Kanjya.sqc"
      sql_setdlist[9].sqldata = (void*)&irihsmkbn;
#line 669 "Kanjya.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 669 "Kanjya.sqc"
      sql_setdlist[10].sqldata = (void*)&caresstflg;
#line 669 "Kanjya.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 669 "Kanjya.sqc"
      sql_setdlist[11].sqldata = (void*)&tktyflg;
#line 669 "Kanjya.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 14;
#line 669 "Kanjya.sqc"
      sql_setdlist[12].sqldata = (void*)apkntino;
#line 669 "Kanjya.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 669 "Kanjya.sqc"
      sql_setdlist[13].sqldata = (void*)sdnm;
#line 669 "Kanjya.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 21;
#line 669 "Kanjya.sqc"
      sql_setdlist[14].sqldata = (void*)bko1;
#line 669 "Kanjya.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 21;
#line 669 "Kanjya.sqc"
      sql_setdlist[15].sqldata = (void*)bko2;
#line 669 "Kanjya.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 21;
#line 669 "Kanjya.sqc"
      sql_setdlist[16].sqldata = (void*)bko3;
#line 669 "Kanjya.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 669 "Kanjya.sqc"
      sql_setdlist[17].sqldata = (void*)zstrdh;
#line 669 "Kanjya.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 669 "Kanjya.sqc"
      sql_setdlist[18].sqldata = (void*)zsssdh;
#line 669 "Kanjya.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 669 "Kanjya.sqc"
      sql_setdlist[19].sqldata = (void*)stlzsssdh;
#line 669 "Kanjya.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 16;
#line 669 "Kanjya.sqc"
      sql_setdlist[20].sqldata = (void*)stlzsssip;
#line 669 "Kanjya.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 9;
#line 669 "Kanjya.sqc"
      sql_setdlist[21].sqldata = (void*)stlzssssyaid;
#line 669 "Kanjya.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 27;
#line 669 "Kanjya.sqc"
      sql_setdlist[22].sqldata = (void*)ksndh;
#line 669 "Kanjya.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 669 "Kanjya.sqc"
      sql_setdlist[23].sqldata = (void*)oyasstcd;
#line 669 "Kanjya.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 27;
#line 669 "Kanjya.sqc"
      sql_setdlist[24].sqldata = (void*)trkdh;
#line 669 "Kanjya.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 669 "Kanjya.sqc"
      sqlasetdata(3,64,25,sql_setdlist,0L,0L);
    }
#line 669 "Kanjya.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 669 "Kanjya.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 669 "Kanjya.sqc"
  sqlastop(0L);
}

#line 669 "Kanjya.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kanjya*)ZbmlRealloc( array,
                                    sizeof( Kanjya ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kanjya ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KanjyaArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 684 "Kanjya.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 684 "Kanjya.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 684 "Kanjya.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 684 "Kanjya.sqc"
  sqlastop(0L);
}

#line 684 "Kanjya.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 692 "Kanjya.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKanjyaInsert()
 *    KANJYA レコードを挿入する
 * ■引数
 *    [I]  Kanjya* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKanjyaInsert( Kanjya* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KanjyaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 715 "Kanjya.sqc"


    
/*
EXEC SQL INSERT INTO KANJYA
    (
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		SSTCD,
		SUBSSTCD,
		CDKBN1,
		CDKBN2,
		IRIMKEY,
		SRKCD,
		SRKNM,
		TTICD,
		TTINM,
		GPCD,
		GPNM,
		SKICD,
		SKINM,
		KRTNO,
		KNJID,
		KNJNMN,
		KNJNMK,
		KNJNMKEY,
		SC,
		TJ,
		TJTNI,
		SBTKBN,
		BIRTHDAY,
		BIRTHDAYKBN,
		AGE,
		AGEKBN,
		BTCD,
		BTNM,
		UTKCMTCD1,
		UTKCMTCD2,
		UTKCMTCD3,
		UTKCMTFR1,
		UTKCMTFR2,
		UTKCMTFRFLG,
		NGKBN,
		NSSSU,
		HKNCD,
		KTSHSU,
		INIRIYMD,
		ZSSFLG,
		KKIRIFLG,
		HKNSKBN,
		UTKKBN,
		NEKBN,
		INKNSKBN,
		UTKJKKBN,
		KRFLG,
		FDHHKKFLG,
		UTKDH,
		MUTKYMD,
		MIRINO,
		KNSJSLBCD1,
		KNSJSLBCD2,
		KNSJSLBCD3,
		KNSJSLBCD4,
		YMHKKFLG,
		HKKKBDH,
		ECD,
		SHCD,
		SSTSSNMJ,
		SSTSSNMN,
		SSTRSJ,
		SSTRSN,
		SSTSBT,
		TTSSTFLG,
		RUCD,
		IRIKMKSU,
		BMSKN,
		IRINRSBT,
		IRIHSMKBN,
		CARESSTFLG,
		TKTYFLG,
		APKNTINO,
		SDNM,
		BKO1,
		BKO2,
		BKO3,
		ZSTRDH,
		ZSSSDH,
		STLZSSSDH,
		STLZSSSIP,
		STLZSSSSYAID,
		KSNDH,
		OYASSTCD,
		TRKDH
    ) VALUES (
		:utkymd,
		:irino,
		:iriketflg,
		:zssdino,
		:sstcd,
		:subsstcd,
		:cdkbn1,
		:cdkbn2,
		:irimkey,
		:srkcd,
		:srknm,
		:tticd,
		:ttinm,
		:gpcd,
		:gpnm,
		:skicd,
		:skinm,
		:krtno,
		:knjid,
		:knjnmn,
		:knjnmk,
		:knjnmkey,
		:sc,
		:tj,
		:tjtni,
		:sbtkbn,
		:birthday,
		:birthdaykbn,
		:age,
		:agekbn,
		:btcd,
		:btnm,
		:utkcmtcd1,
		:utkcmtcd2,
		:utkcmtcd3,
		:utkcmtfr1,
		:utkcmtfr2,
		:utkcmtfrflg,
		:ngkbn,
		:nsssu,
		:hkncd,
		:ktshsu,
		:iniriymd,
		:zssflg,
		:kkiriflg,
		:hknskbn,
		:utkkbn,
		:nekbn,
		:inknskbn,
		:utkjkkbn,
		:krflg,
		:fdhhkkflg,
		:utkdh,
		:mutkymd,
		:mirino,
		:knsjslbcd1,
		:knsjslbcd2,
		:knsjslbcd3,
		:knsjslbcd4,
		:ymhkkflg,
		:hkkkbdh,
		:ecd,
		:shcd,
		:sstssnmj,
		:sstssnmn,
		:sstrsj,
		:sstrsn,
		:sstsbt,
		:ttsstflg,
		:rucd,
		:irikmksu,
		:bmskn,
		:irinrsbt,
		:irihsmkbn,
		:caresstflg,
		:tktyflg,
		:apkntino,
		:sdnm,
		:bko1,
		:bko2,
		:bko3,
		:zstrdh,
		:zsssdh,
		:stlzsssdh,
		:stlzsssip,
		:stlzssssyaid,
		CURRENT TIMESTAMP,
		:oyasstcd,
		CURRENT TIMESTAMP
    );
*/

{
#line 898 "Kanjya.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 898 "Kanjya.sqc"
  sqlaaloc(2,87,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 898 "Kanjya.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 898 "Kanjya.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 898 "Kanjya.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 898 "Kanjya.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 898 "Kanjya.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 898 "Kanjya.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 898 "Kanjya.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 898 "Kanjya.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 898 "Kanjya.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 898 "Kanjya.sqc"
      sql_setdlist[4].sqldata = (void*)sstcd;
#line 898 "Kanjya.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 5;
#line 898 "Kanjya.sqc"
      sql_setdlist[5].sqldata = (void*)subsstcd;
#line 898 "Kanjya.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 3;
#line 898 "Kanjya.sqc"
      sql_setdlist[6].sqldata = (void*)cdkbn1;
#line 898 "Kanjya.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 898 "Kanjya.sqc"
      sql_setdlist[7].sqldata = (void*)cdkbn2;
#line 898 "Kanjya.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 41;
#line 898 "Kanjya.sqc"
      sql_setdlist[8].sqldata = (void*)irimkey;
#line 898 "Kanjya.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 4;
#line 898 "Kanjya.sqc"
      sql_setdlist[9].sqldata = (void*)srkcd;
#line 898 "Kanjya.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 31;
#line 898 "Kanjya.sqc"
      sql_setdlist[10].sqldata = (void*)srknm;
#line 898 "Kanjya.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 898 "Kanjya.sqc"
      sql_setdlist[11].sqldata = (void*)tticd;
#line 898 "Kanjya.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 41;
#line 898 "Kanjya.sqc"
      sql_setdlist[12].sqldata = (void*)ttinm;
#line 898 "Kanjya.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 898 "Kanjya.sqc"
      sql_setdlist[13].sqldata = (void*)gpcd;
#line 898 "Kanjya.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 41;
#line 898 "Kanjya.sqc"
      sql_setdlist[14].sqldata = (void*)gpnm;
#line 898 "Kanjya.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 898 "Kanjya.sqc"
      sql_setdlist[15].sqldata = (void*)skicd;
#line 898 "Kanjya.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 41;
#line 898 "Kanjya.sqc"
      sql_setdlist[16].sqldata = (void*)skinm;
#line 898 "Kanjya.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 41;
#line 898 "Kanjya.sqc"
      sql_setdlist[17].sqldata = (void*)krtno;
#line 898 "Kanjya.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 16;
#line 898 "Kanjya.sqc"
      sql_setdlist[18].sqldata = (void*)knjid;
#line 898 "Kanjya.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 61;
#line 898 "Kanjya.sqc"
      sql_setdlist[19].sqldata = (void*)knjnmn;
#line 898 "Kanjya.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 31;
#line 898 "Kanjya.sqc"
      sql_setdlist[20].sqldata = (void*)knjnmk;
#line 898 "Kanjya.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 61;
#line 898 "Kanjya.sqc"
      sql_setdlist[21].sqldata = (void*)knjnmkey;
#line 898 "Kanjya.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 6;
#line 898 "Kanjya.sqc"
      sql_setdlist[22].sqldata = (void*)sc;
#line 898 "Kanjya.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 6;
#line 898 "Kanjya.sqc"
      sql_setdlist[23].sqldata = (void*)tj;
#line 898 "Kanjya.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 898 "Kanjya.sqc"
      sql_setdlist[24].sqldata = (void*)&tjtni;
#line 898 "Kanjya.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 898 "Kanjya.sqc"
      sql_setdlist[25].sqldata = (void*)&sbtkbn;
#line 898 "Kanjya.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 9;
#line 898 "Kanjya.sqc"
      sql_setdlist[26].sqldata = (void*)birthday;
#line 898 "Kanjya.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 898 "Kanjya.sqc"
      sql_setdlist[27].sqldata = (void*)&birthdaykbn;
#line 898 "Kanjya.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 4;
#line 898 "Kanjya.sqc"
      sql_setdlist[28].sqldata = (void*)age;
#line 898 "Kanjya.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 898 "Kanjya.sqc"
      sql_setdlist[29].sqldata = (void*)&agekbn;
#line 898 "Kanjya.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 11;
#line 898 "Kanjya.sqc"
      sql_setdlist[30].sqldata = (void*)btcd;
#line 898 "Kanjya.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 31;
#line 898 "Kanjya.sqc"
      sql_setdlist[31].sqldata = (void*)btnm;
#line 898 "Kanjya.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 898 "Kanjya.sqc"
      sql_setdlist[32].sqldata = (void*)utkcmtcd1;
#line 898 "Kanjya.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 898 "Kanjya.sqc"
      sql_setdlist[33].sqldata = (void*)utkcmtcd2;
#line 898 "Kanjya.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 3;
#line 898 "Kanjya.sqc"
      sql_setdlist[34].sqldata = (void*)utkcmtcd3;
#line 898 "Kanjya.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 71;
#line 898 "Kanjya.sqc"
      sql_setdlist[35].sqldata = (void*)utkcmtfr1;
#line 898 "Kanjya.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 71;
#line 898 "Kanjya.sqc"
      sql_setdlist[36].sqldata = (void*)utkcmtfr2;
#line 898 "Kanjya.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 898 "Kanjya.sqc"
      sql_setdlist[37].sqldata = (void*)&utkcmtfrflg;
#line 898 "Kanjya.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 898 "Kanjya.sqc"
      sql_setdlist[38].sqldata = (void*)&ngkbn;
#line 898 "Kanjya.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 3;
#line 898 "Kanjya.sqc"
      sql_setdlist[39].sqldata = (void*)nsssu;
#line 898 "Kanjya.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 898 "Kanjya.sqc"
      sql_setdlist[40].sqldata = (void*)&hkncd;
#line 898 "Kanjya.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 898 "Kanjya.sqc"
      sql_setdlist[41].sqldata = (void*)ktshsu;
#line 898 "Kanjya.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 11;
#line 898 "Kanjya.sqc"
      sql_setdlist[42].sqldata = (void*)iniriymd;
#line 898 "Kanjya.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 898 "Kanjya.sqc"
      sql_setdlist[43].sqldata = (void*)&zssflg;
#line 898 "Kanjya.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 898 "Kanjya.sqc"
      sql_setdlist[44].sqldata = (void*)&kkiriflg;
#line 898 "Kanjya.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[45].sqltype = 452; sql_setdlist[45].sqllen = 1;
#line 898 "Kanjya.sqc"
      sql_setdlist[45].sqldata = (void*)&hknskbn;
#line 898 "Kanjya.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 898 "Kanjya.sqc"
      sql_setdlist[46].sqldata = (void*)&utkkbn;
#line 898 "Kanjya.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 898 "Kanjya.sqc"
      sql_setdlist[47].sqldata = (void*)&nekbn;
#line 898 "Kanjya.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 898 "Kanjya.sqc"
      sql_setdlist[48].sqldata = (void*)&inknskbn;
#line 898 "Kanjya.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[49].sqltype = 452; sql_setdlist[49].sqllen = 1;
#line 898 "Kanjya.sqc"
      sql_setdlist[49].sqldata = (void*)&utkjkkbn;
#line 898 "Kanjya.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[50].sqltype = 452; sql_setdlist[50].sqllen = 1;
#line 898 "Kanjya.sqc"
      sql_setdlist[50].sqldata = (void*)&krflg;
#line 898 "Kanjya.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[51].sqltype = 452; sql_setdlist[51].sqllen = 1;
#line 898 "Kanjya.sqc"
      sql_setdlist[51].sqldata = (void*)&fdhhkkflg;
#line 898 "Kanjya.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 9;
#line 898 "Kanjya.sqc"
      sql_setdlist[52].sqldata = (void*)utkdh;
#line 898 "Kanjya.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 11;
#line 898 "Kanjya.sqc"
      sql_setdlist[53].sqldata = (void*)mutkymd;
#line 898 "Kanjya.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 12;
#line 898 "Kanjya.sqc"
      sql_setdlist[54].sqldata = (void*)mirino;
#line 898 "Kanjya.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 898 "Kanjya.sqc"
      sql_setdlist[55].sqldata = (void*)knsjslbcd1;
#line 898 "Kanjya.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 4;
#line 898 "Kanjya.sqc"
      sql_setdlist[56].sqldata = (void*)knsjslbcd2;
#line 898 "Kanjya.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 4;
#line 898 "Kanjya.sqc"
      sql_setdlist[57].sqldata = (void*)knsjslbcd3;
#line 898 "Kanjya.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[58].sqltype = 460; sql_setdlist[58].sqllen = 4;
#line 898 "Kanjya.sqc"
      sql_setdlist[58].sqldata = (void*)knsjslbcd4;
#line 898 "Kanjya.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[59].sqltype = 452; sql_setdlist[59].sqllen = 1;
#line 898 "Kanjya.sqc"
      sql_setdlist[59].sqldata = (void*)&ymhkkflg;
#line 898 "Kanjya.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[60].sqltype = 460; sql_setdlist[60].sqllen = 9;
#line 898 "Kanjya.sqc"
      sql_setdlist[60].sqldata = (void*)hkkkbdh;
#line 898 "Kanjya.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[61].sqltype = 460; sql_setdlist[61].sqllen = 4;
#line 898 "Kanjya.sqc"
      sql_setdlist[61].sqldata = (void*)ecd;
#line 898 "Kanjya.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[62].sqltype = 460; sql_setdlist[62].sqllen = 3;
#line 898 "Kanjya.sqc"
      sql_setdlist[62].sqldata = (void*)shcd;
#line 898 "Kanjya.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[63].sqltype = 460; sql_setdlist[63].sqllen = 41;
#line 898 "Kanjya.sqc"
      sql_setdlist[63].sqldata = (void*)sstssnmj;
#line 898 "Kanjya.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sqlasetdata(2,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[23];
#line 898 "Kanjya.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 41;
#line 898 "Kanjya.sqc"
      sql_setdlist[0].sqldata = (void*)sstssnmn;
#line 898 "Kanjya.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 898 "Kanjya.sqc"
      sql_setdlist[1].sqldata = (void*)sstrsj;
#line 898 "Kanjya.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 898 "Kanjya.sqc"
      sql_setdlist[2].sqldata = (void*)sstrsn;
#line 898 "Kanjya.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 898 "Kanjya.sqc"
      sql_setdlist[3].sqldata = (void*)sstsbt;
#line 898 "Kanjya.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 898 "Kanjya.sqc"
      sql_setdlist[4].sqldata = (void*)&ttsstflg;
#line 898 "Kanjya.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 898 "Kanjya.sqc"
      sql_setdlist[5].sqldata = (void*)rucd;
#line 898 "Kanjya.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 898 "Kanjya.sqc"
      sql_setdlist[6].sqldata = (void*)&irikmksu;
#line 898 "Kanjya.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 898 "Kanjya.sqc"
      sql_setdlist[7].sqldata = (void*)bmskn;
#line 898 "Kanjya.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 3;
#line 898 "Kanjya.sqc"
      sql_setdlist[8].sqldata = (void*)irinrsbt;
#line 898 "Kanjya.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 898 "Kanjya.sqc"
      sql_setdlist[9].sqldata = (void*)&irihsmkbn;
#line 898 "Kanjya.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 898 "Kanjya.sqc"
      sql_setdlist[10].sqldata = (void*)&caresstflg;
#line 898 "Kanjya.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 898 "Kanjya.sqc"
      sql_setdlist[11].sqldata = (void*)&tktyflg;
#line 898 "Kanjya.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 14;
#line 898 "Kanjya.sqc"
      sql_setdlist[12].sqldata = (void*)apkntino;
#line 898 "Kanjya.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 898 "Kanjya.sqc"
      sql_setdlist[13].sqldata = (void*)sdnm;
#line 898 "Kanjya.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 21;
#line 898 "Kanjya.sqc"
      sql_setdlist[14].sqldata = (void*)bko1;
#line 898 "Kanjya.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 21;
#line 898 "Kanjya.sqc"
      sql_setdlist[15].sqldata = (void*)bko2;
#line 898 "Kanjya.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 21;
#line 898 "Kanjya.sqc"
      sql_setdlist[16].sqldata = (void*)bko3;
#line 898 "Kanjya.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 898 "Kanjya.sqc"
      sql_setdlist[17].sqldata = (void*)zstrdh;
#line 898 "Kanjya.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 898 "Kanjya.sqc"
      sql_setdlist[18].sqldata = (void*)zsssdh;
#line 898 "Kanjya.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 898 "Kanjya.sqc"
      sql_setdlist[19].sqldata = (void*)stlzsssdh;
#line 898 "Kanjya.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 16;
#line 898 "Kanjya.sqc"
      sql_setdlist[20].sqldata = (void*)stlzsssip;
#line 898 "Kanjya.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 9;
#line 898 "Kanjya.sqc"
      sql_setdlist[21].sqldata = (void*)stlzssssyaid;
#line 898 "Kanjya.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 8;
#line 898 "Kanjya.sqc"
      sql_setdlist[22].sqldata = (void*)oyasstcd;
#line 898 "Kanjya.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 898 "Kanjya.sqc"
      sqlasetdata(2,64,23,sql_setdlist,0L,0L);
    }
#line 898 "Kanjya.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 898 "Kanjya.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 898 "Kanjya.sqc"
  sqlastop(0L);
}

#line 898 "Kanjya.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 903 "Kanjya.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKanjyaUpdate()
 *    KANJYA レコードを更新する
 * ■引数
 *    [I]  Kanjya* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKanjyaUpdate( Kanjya* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KanjyaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 927 "Kanjya.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 928 "Kanjya.sqc"


    
/*
EXEC SQL UPDATE KANJYA
    SET (
		IRIKETFLG,
		SSTCD,
		SUBSSTCD,
		CDKBN1,
		CDKBN2,
		IRIMKEY,
		SRKCD,
		SRKNM,
		TTICD,
		TTINM,
		GPCD,
		GPNM,
		SKICD,
		SKINM,
		KRTNO,
		KNJID,
		KNJNMN,
		KNJNMK,
		KNJNMKEY,
		SC,
		TJ,
		TJTNI,
		SBTKBN,
		BIRTHDAY,
		BIRTHDAYKBN,
		AGE,
		AGEKBN,
		BTCD,
		BTNM,
		UTKCMTCD1,
		UTKCMTCD2,
		UTKCMTCD3,
		UTKCMTFR1,
		UTKCMTFR2,
		UTKCMTFRFLG,
		NGKBN,
		NSSSU,
		HKNCD,
		KTSHSU,
		INIRIYMD,
		ZSSFLG,
		KKIRIFLG,
		HKNSKBN,
		UTKKBN,
		NEKBN,
		INKNSKBN,
		UTKJKKBN,
		KRFLG,
		FDHHKKFLG,
		UTKDH,
		MUTKYMD,
		MIRINO,
		KNSJSLBCD1,
		KNSJSLBCD2,
		KNSJSLBCD3,
		KNSJSLBCD4,
		YMHKKFLG,
		HKKKBDH,
		ECD,
		SHCD,
		SSTSSNMJ,
		SSTSSNMN,
		SSTRSJ,
		SSTRSN,
		SSTSBT,
		TTSSTFLG,
		RUCD,
		IRIKMKSU,
		BMSKN,
		IRINRSBT,
		IRIHSMKBN,
		CARESSTFLG,
		TKTYFLG,
		APKNTINO,
		SDNM,
		BKO1,
		BKO2,
		BKO3,
		ZSTRDH,
		ZSSSDH,
		STLZSSSDH,
		STLZSSSIP,
		STLZSSSSYAID,
		KSNDH,
		OYASSTCD,
		TRKDH
    ) = (
		:iriketflg,
		:sstcd,
		:subsstcd,
		:cdkbn1,
		:cdkbn2,
		:irimkey,
		:srkcd,
		:srknm,
		:tticd,
		:ttinm,
		:gpcd,
		:gpnm,
		:skicd,
		:skinm,
		:krtno,
		:knjid,
		:knjnmn,
		:knjnmk,
		:knjnmkey,
		:sc,
		:tj,
		:tjtni,
		:sbtkbn,
		:birthday,
		:birthdaykbn,
		:age,
		:agekbn,
		:btcd,
		:btnm,
		:utkcmtcd1,
		:utkcmtcd2,
		:utkcmtcd3,
		:utkcmtfr1,
		:utkcmtfr2,
		:utkcmtfrflg,
		:ngkbn,
		:nsssu,
		:hkncd,
		:ktshsu,
		:iniriymd,
		:zssflg,
		:kkiriflg,
		:hknskbn,
		:utkkbn,
		:nekbn,
		:inknskbn,
		:utkjkkbn,
		:krflg,
		:fdhhkkflg,
		:utkdh,
		:mutkymd,
		:mirino,
		:knsjslbcd1,
		:knsjslbcd2,
		:knsjslbcd3,
		:knsjslbcd4,
		:ymhkkflg,
		:hkkkbdh,
		:ecd,
		:shcd,
		:sstssnmj,
		:sstssnmn,
		:sstrsj,
		:sstrsn,
		:sstsbt,
		:ttsstflg,
		:rucd,
		:irikmksu,
		:bmskn,
		:irinrsbt,
		:irihsmkbn,
		:caresstflg,
		:tktyflg,
		:apkntino,
		:sdnm,
		:bko1,
		:bko2,
		:bko3,
		:zstrdh,
		:zsssdh,
		:stlzsssdh,
		:stlzsssip,
		:stlzssssyaid,
		CURRENT TIMESTAMP,
		:oyasstcd,
		:trkdh
    ) WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		ZSSDINO = :zssdino;
*/

{
#line 1108 "Kanjya.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1108 "Kanjya.sqc"
  sqlaaloc(2,88,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 1108 "Kanjya.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[0].sqldata = (void*)&iriketflg;
#line 1108 "Kanjya.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 1108 "Kanjya.sqc"
      sql_setdlist[1].sqldata = (void*)sstcd;
#line 1108 "Kanjya.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 1108 "Kanjya.sqc"
      sql_setdlist[2].sqldata = (void*)subsstcd;
#line 1108 "Kanjya.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 1108 "Kanjya.sqc"
      sql_setdlist[3].sqldata = (void*)cdkbn1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 3;
#line 1108 "Kanjya.sqc"
      sql_setdlist[4].sqldata = (void*)cdkbn2;
#line 1108 "Kanjya.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 41;
#line 1108 "Kanjya.sqc"
      sql_setdlist[5].sqldata = (void*)irimkey;
#line 1108 "Kanjya.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 4;
#line 1108 "Kanjya.sqc"
      sql_setdlist[6].sqldata = (void*)srkcd;
#line 1108 "Kanjya.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 31;
#line 1108 "Kanjya.sqc"
      sql_setdlist[7].sqldata = (void*)srknm;
#line 1108 "Kanjya.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 1108 "Kanjya.sqc"
      sql_setdlist[8].sqldata = (void*)tticd;
#line 1108 "Kanjya.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 41;
#line 1108 "Kanjya.sqc"
      sql_setdlist[9].sqldata = (void*)ttinm;
#line 1108 "Kanjya.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 9;
#line 1108 "Kanjya.sqc"
      sql_setdlist[10].sqldata = (void*)gpcd;
#line 1108 "Kanjya.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 41;
#line 1108 "Kanjya.sqc"
      sql_setdlist[11].sqldata = (void*)gpnm;
#line 1108 "Kanjya.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 1108 "Kanjya.sqc"
      sql_setdlist[12].sqldata = (void*)skicd;
#line 1108 "Kanjya.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 41;
#line 1108 "Kanjya.sqc"
      sql_setdlist[13].sqldata = (void*)skinm;
#line 1108 "Kanjya.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 41;
#line 1108 "Kanjya.sqc"
      sql_setdlist[14].sqldata = (void*)krtno;
#line 1108 "Kanjya.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 16;
#line 1108 "Kanjya.sqc"
      sql_setdlist[15].sqldata = (void*)knjid;
#line 1108 "Kanjya.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 61;
#line 1108 "Kanjya.sqc"
      sql_setdlist[16].sqldata = (void*)knjnmn;
#line 1108 "Kanjya.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 31;
#line 1108 "Kanjya.sqc"
      sql_setdlist[17].sqldata = (void*)knjnmk;
#line 1108 "Kanjya.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 61;
#line 1108 "Kanjya.sqc"
      sql_setdlist[18].sqldata = (void*)knjnmkey;
#line 1108 "Kanjya.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 6;
#line 1108 "Kanjya.sqc"
      sql_setdlist[19].sqldata = (void*)sc;
#line 1108 "Kanjya.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 6;
#line 1108 "Kanjya.sqc"
      sql_setdlist[20].sqldata = (void*)tj;
#line 1108 "Kanjya.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[21].sqldata = (void*)&tjtni;
#line 1108 "Kanjya.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[22].sqldata = (void*)&sbtkbn;
#line 1108 "Kanjya.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 9;
#line 1108 "Kanjya.sqc"
      sql_setdlist[23].sqldata = (void*)birthday;
#line 1108 "Kanjya.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[24].sqldata = (void*)&birthdaykbn;
#line 1108 "Kanjya.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 4;
#line 1108 "Kanjya.sqc"
      sql_setdlist[25].sqldata = (void*)age;
#line 1108 "Kanjya.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[26].sqldata = (void*)&agekbn;
#line 1108 "Kanjya.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 11;
#line 1108 "Kanjya.sqc"
      sql_setdlist[27].sqldata = (void*)btcd;
#line 1108 "Kanjya.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 31;
#line 1108 "Kanjya.sqc"
      sql_setdlist[28].sqldata = (void*)btnm;
#line 1108 "Kanjya.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 3;
#line 1108 "Kanjya.sqc"
      sql_setdlist[29].sqldata = (void*)utkcmtcd1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 3;
#line 1108 "Kanjya.sqc"
      sql_setdlist[30].sqldata = (void*)utkcmtcd2;
#line 1108 "Kanjya.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 3;
#line 1108 "Kanjya.sqc"
      sql_setdlist[31].sqldata = (void*)utkcmtcd3;
#line 1108 "Kanjya.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 71;
#line 1108 "Kanjya.sqc"
      sql_setdlist[32].sqldata = (void*)utkcmtfr1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 71;
#line 1108 "Kanjya.sqc"
      sql_setdlist[33].sqldata = (void*)utkcmtfr2;
#line 1108 "Kanjya.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[34].sqldata = (void*)&utkcmtfrflg;
#line 1108 "Kanjya.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[35].sqldata = (void*)&ngkbn;
#line 1108 "Kanjya.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 3;
#line 1108 "Kanjya.sqc"
      sql_setdlist[36].sqldata = (void*)nsssu;
#line 1108 "Kanjya.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[37].sqldata = (void*)&hkncd;
#line 1108 "Kanjya.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 3;
#line 1108 "Kanjya.sqc"
      sql_setdlist[38].sqldata = (void*)ktshsu;
#line 1108 "Kanjya.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 11;
#line 1108 "Kanjya.sqc"
      sql_setdlist[39].sqldata = (void*)iniriymd;
#line 1108 "Kanjya.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[40].sqldata = (void*)&zssflg;
#line 1108 "Kanjya.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[41].sqldata = (void*)&kkiriflg;
#line 1108 "Kanjya.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[42].sqltype = 452; sql_setdlist[42].sqllen = 1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[42].sqldata = (void*)&hknskbn;
#line 1108 "Kanjya.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[43].sqldata = (void*)&utkkbn;
#line 1108 "Kanjya.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[44].sqldata = (void*)&nekbn;
#line 1108 "Kanjya.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[45].sqltype = 452; sql_setdlist[45].sqllen = 1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[45].sqldata = (void*)&inknskbn;
#line 1108 "Kanjya.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[46].sqldata = (void*)&utkjkkbn;
#line 1108 "Kanjya.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[47].sqldata = (void*)&krflg;
#line 1108 "Kanjya.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[48].sqldata = (void*)&fdhhkkflg;
#line 1108 "Kanjya.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 9;
#line 1108 "Kanjya.sqc"
      sql_setdlist[49].sqldata = (void*)utkdh;
#line 1108 "Kanjya.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 11;
#line 1108 "Kanjya.sqc"
      sql_setdlist[50].sqldata = (void*)mutkymd;
#line 1108 "Kanjya.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 12;
#line 1108 "Kanjya.sqc"
      sql_setdlist[51].sqldata = (void*)mirino;
#line 1108 "Kanjya.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 4;
#line 1108 "Kanjya.sqc"
      sql_setdlist[52].sqldata = (void*)knsjslbcd1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 4;
#line 1108 "Kanjya.sqc"
      sql_setdlist[53].sqldata = (void*)knsjslbcd2;
#line 1108 "Kanjya.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 4;
#line 1108 "Kanjya.sqc"
      sql_setdlist[54].sqldata = (void*)knsjslbcd3;
#line 1108 "Kanjya.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 1108 "Kanjya.sqc"
      sql_setdlist[55].sqldata = (void*)knsjslbcd4;
#line 1108 "Kanjya.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[56].sqltype = 452; sql_setdlist[56].sqllen = 1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[56].sqldata = (void*)&ymhkkflg;
#line 1108 "Kanjya.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 9;
#line 1108 "Kanjya.sqc"
      sql_setdlist[57].sqldata = (void*)hkkkbdh;
#line 1108 "Kanjya.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[58].sqltype = 460; sql_setdlist[58].sqllen = 4;
#line 1108 "Kanjya.sqc"
      sql_setdlist[58].sqldata = (void*)ecd;
#line 1108 "Kanjya.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[59].sqltype = 460; sql_setdlist[59].sqllen = 3;
#line 1108 "Kanjya.sqc"
      sql_setdlist[59].sqldata = (void*)shcd;
#line 1108 "Kanjya.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[60].sqltype = 460; sql_setdlist[60].sqllen = 41;
#line 1108 "Kanjya.sqc"
      sql_setdlist[60].sqldata = (void*)sstssnmj;
#line 1108 "Kanjya.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[61].sqltype = 460; sql_setdlist[61].sqllen = 41;
#line 1108 "Kanjya.sqc"
      sql_setdlist[61].sqldata = (void*)sstssnmn;
#line 1108 "Kanjya.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[62].sqltype = 460; sql_setdlist[62].sqllen = 21;
#line 1108 "Kanjya.sqc"
      sql_setdlist[62].sqldata = (void*)sstrsj;
#line 1108 "Kanjya.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[63].sqltype = 460; sql_setdlist[63].sqllen = 21;
#line 1108 "Kanjya.sqc"
      sql_setdlist[63].sqldata = (void*)sstrsn;
#line 1108 "Kanjya.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sqlasetdata(2,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[24];
#line 1108 "Kanjya.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 1108 "Kanjya.sqc"
      sql_setdlist[0].sqldata = (void*)sstsbt;
#line 1108 "Kanjya.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[1].sqldata = (void*)&ttsstflg;
#line 1108 "Kanjya.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 1108 "Kanjya.sqc"
      sql_setdlist[2].sqldata = (void*)rucd;
#line 1108 "Kanjya.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 1108 "Kanjya.sqc"
      sql_setdlist[3].sqldata = (void*)&irikmksu;
#line 1108 "Kanjya.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 51;
#line 1108 "Kanjya.sqc"
      sql_setdlist[4].sqldata = (void*)bmskn;
#line 1108 "Kanjya.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 1108 "Kanjya.sqc"
      sql_setdlist[5].sqldata = (void*)irinrsbt;
#line 1108 "Kanjya.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[6].sqldata = (void*)&irihsmkbn;
#line 1108 "Kanjya.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[7].sqldata = (void*)&caresstflg;
#line 1108 "Kanjya.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[8].sqldata = (void*)&tktyflg;
#line 1108 "Kanjya.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 14;
#line 1108 "Kanjya.sqc"
      sql_setdlist[9].sqldata = (void*)apkntino;
#line 1108 "Kanjya.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 21;
#line 1108 "Kanjya.sqc"
      sql_setdlist[10].sqldata = (void*)sdnm;
#line 1108 "Kanjya.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 21;
#line 1108 "Kanjya.sqc"
      sql_setdlist[11].sqldata = (void*)bko1;
#line 1108 "Kanjya.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 21;
#line 1108 "Kanjya.sqc"
      sql_setdlist[12].sqldata = (void*)bko2;
#line 1108 "Kanjya.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 1108 "Kanjya.sqc"
      sql_setdlist[13].sqldata = (void*)bko3;
#line 1108 "Kanjya.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 27;
#line 1108 "Kanjya.sqc"
      sql_setdlist[14].sqldata = (void*)zstrdh;
#line 1108 "Kanjya.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 1108 "Kanjya.sqc"
      sql_setdlist[15].sqldata = (void*)zsssdh;
#line 1108 "Kanjya.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 27;
#line 1108 "Kanjya.sqc"
      sql_setdlist[16].sqldata = (void*)stlzsssdh;
#line 1108 "Kanjya.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 16;
#line 1108 "Kanjya.sqc"
      sql_setdlist[17].sqldata = (void*)stlzsssip;
#line 1108 "Kanjya.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 9;
#line 1108 "Kanjya.sqc"
      sql_setdlist[18].sqldata = (void*)stlzssssyaid;
#line 1108 "Kanjya.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 8;
#line 1108 "Kanjya.sqc"
      sql_setdlist[19].sqldata = (void*)oyasstcd;
#line 1108 "Kanjya.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 27;
#line 1108 "Kanjya.sqc"
      sql_setdlist[20].sqldata = (void*)trkdh;
#line 1108 "Kanjya.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 11;
#line 1108 "Kanjya.sqc"
      sql_setdlist[21].sqldata = (void*)utkymd;
#line 1108 "Kanjya.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 12;
#line 1108 "Kanjya.sqc"
      sql_setdlist[22].sqldata = (void*)irino;
#line 1108 "Kanjya.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sql_setdlist[23].sqltype = 500; sql_setdlist[23].sqllen = 2;
#line 1108 "Kanjya.sqc"
      sql_setdlist[23].sqldata = (void*)&zssdino;
#line 1108 "Kanjya.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1108 "Kanjya.sqc"
      sqlasetdata(2,64,24,sql_setdlist,0L,0L);
    }
#line 1108 "Kanjya.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 1108 "Kanjya.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1108 "Kanjya.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 1108 "Kanjya.sqc"
  sqlastop(0L);
}

#line 1108 "Kanjya.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 1113 "Kanjya.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 1117 "Kanjya.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKanjyaDelete()
 *    KANJYA レコードを削除する
 * ■引数
 *    [I]  Kanjya* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKanjyaDelete( Kanjya* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KanjyaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 1141 "Kanjya.sqc"


    
/*
EXEC SQL DELETE FROM KANJYA
    WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		ZSSDINO = :zssdino;
*/

{
#line 1147 "Kanjya.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1147 "Kanjya.sqc"
  sqlaaloc(2,3,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 1147 "Kanjya.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1147 "Kanjya.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 1147 "Kanjya.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1147 "Kanjya.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1147 "Kanjya.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 1147 "Kanjya.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1147 "Kanjya.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 1147 "Kanjya.sqc"
      sql_setdlist[2].sqldata = (void*)&zssdino;
#line 1147 "Kanjya.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1147 "Kanjya.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 1147 "Kanjya.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 1147 "Kanjya.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 1147 "Kanjya.sqc"
  sqlastop(0L);
}

#line 1147 "Kanjya.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 1152 "Kanjya.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
