static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,101,66,68,52,85,97,68,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,51,71,49,48,53,32,32,32,0,0,0,0,0,0,0,0,
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


#line 1 "GD105Kanjya.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：GD105Kanjya.sqc
 *     機能概要  ：患者情報アクセス関数(報告処理)
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2009-05-11                    Create
 **********************************************************************/

/********************************************************************/
/*  インクルード宣言                                                */
/********************************************************************/
#include <stdio.h>
#include "GD105Kanjya.h"
#include "bml_misc.h"
#include "bml_db.h"
#include "bml_dmm.h"
#include "bmllog.h"

#define	RETRY			3		// リトライ回数
#define	ERR_LOCK		-911	// デッドロック時エラーコード
#define	LOCK_WAIT_SEC	5		// スリープ単位：秒

#define	ALLOC_UNIT		1


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 33 "GD105Kanjya.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 38 "GD105Kanjya.sqc"

	char    utkymd[10+1];
	char    irino[11+1];
	char    iriketflg;
	short   zssdino;
	char    sstcd[7+1];
	char    subsstcd[4+1];
	char    cdkbn1[2+1];
	char    cdkbn2[2+1];
	char    irimkey[40+1];
	char    srkcd[3+1];
	char    srknm[30+1];
	char    tticd[8+1];
	char    ttinm[40+1];
	char    gpcd[8+1];
	char    gpnm[40+1];
	char    skicd[8+1];
	char    skinm[40+1];
	char    krtno[40+1];
	char    knjid[15+1];
	char    knjnmn[60+1];
	char    knjnmk[30+1];
	char    knjnmkey[60+1];
	char    sc[5+1];
	char    tj[5+1];
	char    tjtni;
	char    sbtkbn;
	char    birthday[8+1];
	char    birthdaykbn;
	char    age[3+1];
	char    agekbn;
	char    btcd[10+1];
	char    btnm[30+1];
	char    utkcmtcd1[2+1];
	char    utkcmtcd2[2+1];
	char    utkcmtcd3[2+1];
	char    utkcmtfr1[70+1];
	char    utkcmtfr2[70+1];
	char    utkcmtfrflg;
	char    ngkbn;
	char    nsssu[2+1];
	char    hkncd;
	char    ktshsu[2+1];
	char    iniriymd[10+1];
	char    zssflg;
	char    kkiriflg;
	char    hknskbn;
	char    utkkbn;
	char    nekbn;
	char    inknskbn;
	char    utkjkkbn;
	char    krflg;
	char    fdhhkkflg;
	char    utkdh[8+1];
	char    mutkymd[10+1];
	char    mirino[11+1];
	char    knsjslbcd1[3+1];
	char    knsjslbcd2[3+1];
	char    knsjslbcd3[3+1];
	char    knsjslbcd4[3+1];
	char    ymhkkflg;
	char    hkkkbdh[8+1];
	char    ecd[3+1];
	char    shcd[2+1];
	char    sstssnmj[40+1];
	char    sstssnmn[40+1];
	char    sstrsj[20+1];
	char    sstrsn[20+1];
	char    sstsbt[2+1];
	char    ttsstflg;
	char    rucd[2+1];
	short   irikmksu;
	char    bmskn[50+1];
	char    irinrsbt[2+1];
	char    irihsmkbn;
	char    caresstflg;
	char    tktyflg;
	char    apkntino[13+1];
	char    sdnm[20+1];
	char    bko1[20+1];
	char    bko2[20+1];
	char    bko3[20+1];
	char    zstrdh[26+1];
	char    zsssdh[26+1];
	char    stlzsssdh[26+1];
	char    stlzsssip[15+1];
	char    stlzssssyaid[8+1];
	char    ksndh[26+1];
	char    oyasstcd[7+1];
	char    trkdh[26+1];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 128 "GD105Kanjya.sqc"



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
 * dGD105_KANJYA_Sel_latestZSSDINO()
 *    KANJYA レコードKey条件取得
 * ■引数
 *    [I]    Kanjya*  pKey          取得するレコードのキー
 *    [O]    Kanjya** arrayOut      取得レコード配列格納領域
 *    [O]    int* numOut            取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL(0)      正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND(100) レコードなし
 *           HRC_SQL_ERR(-2)        DBエラー
 ******************************************************************************/
long dGD105_KANJYA_Sel_latestZSSDINO( Kanjya* pKey, Kanjya** arrayOut, int* numOut )
{
	Kanjya*		array = NULL;
	int			num = 0;
	int			error = 0;

	if( !pKey ) {
		return HRC_NULL_POINTER;
	}

	if( !ZbmlMapStructToHost( (char*)pKey, KanjyaArray ) ) {
		return HRC_INVALID_VALUE;
	}

	// リトライ用ループ設定
	int i;
	for (i = 0; i <= RETRY; i++) {
		error = 0;

		
/*
EXEC SQL DECLARE cur_kanjya CURSOR FOR
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
			IRINO  = :irino
		ORDER BY
			ZSSDINO DESC
		FETCH FIRST 1 ROWS ONLY
		FOR READ ONLY;
*/

#line 359 "GD105Kanjya.sqc"


	    
/*
EXEC SQL OPEN cur_kanjya;
*/

{
#line 361 "GD105Kanjya.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 361 "GD105Kanjya.sqc"
  sqlaaloc(2,2,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 361 "GD105Kanjya.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 361 "GD105Kanjya.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 361 "GD105Kanjya.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 361 "GD105Kanjya.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 361 "GD105Kanjya.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 361 "GD105Kanjya.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 361 "GD105Kanjya.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 361 "GD105Kanjya.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 361 "GD105Kanjya.sqc"
  sqlastop(0L);
}

#line 361 "GD105Kanjya.sqc"


		while( 1 ) {
			Kanjya* rec;

			
/*
EXEC SQL FETCH cur_kanjya INTO
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
#line 455 "GD105Kanjya.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 455 "GD105Kanjya.sqc"
  sqlaaloc(3,89,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[4].sqldata = (void*)sstcd;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 5;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[5].sqldata = (void*)subsstcd;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 3;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[6].sqldata = (void*)cdkbn1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[7].sqldata = (void*)cdkbn2;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 41;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[8].sqldata = (void*)irimkey;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 4;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[9].sqldata = (void*)srkcd;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 31;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[10].sqldata = (void*)srknm;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[11].sqldata = (void*)tticd;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 41;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[12].sqldata = (void*)ttinm;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[13].sqldata = (void*)gpcd;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 41;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[14].sqldata = (void*)gpnm;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[15].sqldata = (void*)skicd;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 41;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[16].sqldata = (void*)skinm;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 41;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[17].sqldata = (void*)krtno;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 16;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[18].sqldata = (void*)knjid;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 61;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[19].sqldata = (void*)knjnmn;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 31;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[20].sqldata = (void*)knjnmk;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 61;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[21].sqldata = (void*)knjnmkey;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 6;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[22].sqldata = (void*)sc;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 6;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[23].sqldata = (void*)tj;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[24].sqldata = (void*)&tjtni;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[25].sqldata = (void*)&sbtkbn;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 9;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[26].sqldata = (void*)birthday;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[27].sqldata = (void*)&birthdaykbn;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 4;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[28].sqldata = (void*)age;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[29].sqldata = (void*)&agekbn;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 11;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[30].sqldata = (void*)btcd;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 31;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[31].sqldata = (void*)btnm;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[32].sqldata = (void*)utkcmtcd1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[33].sqldata = (void*)utkcmtcd2;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 3;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[34].sqldata = (void*)utkcmtcd3;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 71;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[35].sqldata = (void*)utkcmtfr1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 71;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[36].sqldata = (void*)utkcmtfr2;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[37].sqldata = (void*)&utkcmtfrflg;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[38].sqldata = (void*)&ngkbn;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 3;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[39].sqldata = (void*)nsssu;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[40].sqldata = (void*)&hkncd;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[41].sqldata = (void*)ktshsu;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 11;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[42].sqldata = (void*)iniriymd;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[43].sqldata = (void*)&zssflg;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[44].sqldata = (void*)&kkiriflg;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[45].sqltype = 452; sql_setdlist[45].sqllen = 1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[45].sqldata = (void*)&hknskbn;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[46].sqldata = (void*)&utkkbn;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[47].sqldata = (void*)&nekbn;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[48].sqldata = (void*)&inknskbn;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[49].sqltype = 452; sql_setdlist[49].sqllen = 1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[49].sqldata = (void*)&utkjkkbn;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[50].sqltype = 452; sql_setdlist[50].sqllen = 1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[50].sqldata = (void*)&krflg;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[51].sqltype = 452; sql_setdlist[51].sqllen = 1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[51].sqldata = (void*)&fdhhkkflg;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 9;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[52].sqldata = (void*)utkdh;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 11;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[53].sqldata = (void*)mutkymd;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 12;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[54].sqldata = (void*)mirino;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[55].sqldata = (void*)knsjslbcd1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 4;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[56].sqldata = (void*)knsjslbcd2;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 4;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[57].sqldata = (void*)knsjslbcd3;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[58].sqltype = 460; sql_setdlist[58].sqllen = 4;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[58].sqldata = (void*)knsjslbcd4;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[59].sqltype = 452; sql_setdlist[59].sqllen = 1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[59].sqldata = (void*)&ymhkkflg;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[60].sqltype = 460; sql_setdlist[60].sqllen = 9;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[60].sqldata = (void*)hkkkbdh;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[61].sqltype = 460; sql_setdlist[61].sqllen = 4;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[61].sqldata = (void*)ecd;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[62].sqltype = 460; sql_setdlist[62].sqllen = 3;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[62].sqldata = (void*)shcd;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[63].sqltype = 460; sql_setdlist[63].sqllen = 41;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[63].sqldata = (void*)sstssnmj;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sqlasetdata(3,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[25];
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 41;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[0].sqldata = (void*)sstssnmn;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[1].sqldata = (void*)sstrsj;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[2].sqldata = (void*)sstrsn;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[3].sqldata = (void*)sstsbt;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[4].sqldata = (void*)&ttsstflg;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[5].sqldata = (void*)rucd;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[6].sqldata = (void*)&irikmksu;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[7].sqldata = (void*)bmskn;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 3;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[8].sqldata = (void*)irinrsbt;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[9].sqldata = (void*)&irihsmkbn;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[10].sqldata = (void*)&caresstflg;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[11].sqldata = (void*)&tktyflg;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 14;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[12].sqldata = (void*)apkntino;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[13].sqldata = (void*)sdnm;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 21;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[14].sqldata = (void*)bko1;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 21;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[15].sqldata = (void*)bko2;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 21;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[16].sqldata = (void*)bko3;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[17].sqldata = (void*)zstrdh;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[18].sqldata = (void*)zsssdh;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[19].sqldata = (void*)stlzsssdh;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 16;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[20].sqldata = (void*)stlzsssip;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 9;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[21].sqldata = (void*)stlzssssyaid;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 27;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[22].sqldata = (void*)ksndh;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[23].sqldata = (void*)oyasstcd;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 27;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[24].sqldata = (void*)trkdh;
#line 455 "GD105Kanjya.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 455 "GD105Kanjya.sqc"
      sqlasetdata(3,64,25,sql_setdlist,0L,0L);
    }
#line 455 "GD105Kanjya.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 455 "GD105Kanjya.sqc"
  sqlastop(0L);
}

#line 455 "GD105Kanjya.sqc"


			if( SQLCODE == HRC_SQL_NOT_FOUND ) {
				break;
			}

			// ロック時のリトライ対応
			if (sqlca.sqlcode < 0) {
				// エラー発生時は領域解放してブレイク
				if (array != NULL) {
					ZbmlFree(array);
					array = NULL;
					num   = 0;
				}
				error = sqlca.sqlcode;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "dGD105_KANJYA_Sel_latestZSSDINO",
							 __LINE__,
							 EXEFLG_SEL, "020",
							 "DBエラー発生 [sqlcode : %d]", sqlca.sqlcode ) ;
				break;
			}

			if( num % ALLOC_UNIT == 0 ) {
				array = (Kanjya*)ZbmlRealloc( array, sizeof( Kanjya ) * ( num + ALLOC_UNIT ) );
				memset( array + num, 0, sizeof( Kanjya ) * ALLOC_UNIT );
			}

			rec = array + num++;
			ZbmlMapHostToStruct( (char*)rec, KanjyaArray );
		}

		
/*
EXEC SQL CLOSE cur_kanjya;
*/

{
#line 486 "GD105Kanjya.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 486 "GD105Kanjya.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 486 "GD105Kanjya.sqc"
  sqlastop(0L);
}

#line 486 "GD105Kanjya.sqc"


		// ロック時のリトライ対応
		// ロックの場合はリトライ、ロック以外のエラーはデータ無しで終了
		// リトライは５秒待ってから
		if (error == ERR_LOCK) {
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "dGD105_KANJYA_Sel_latestZSSDINO",
						 __LINE__,
						 EXEFLG_NON, "020",
						 "ロックによるリトライ[%d]回目", i ) ;
			sleep(LOCK_WAIT_SEC);
			continue;
		}

		*arrayOut = array;
		*numOut   = num;

		return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

	// リトライ用ループ終端
	}

	// リトライしてもエラーの場合、データ無しで終了
	*arrayOut = NULL;
	*numOut   = 0;
	return HRC_SQL_NOT_FOUND;

}

/** End of File *********************************************************/
