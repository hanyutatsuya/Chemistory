static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,104,66,83,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,51,50,90,75,69,78,90,32,0,0,0,0,0,0,0,0,
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


#line 1 "Kenzok.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Kenzok.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Kenzok.h"
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


#line 24 "Kenzok.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Kenzok.sqc"

	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    sriymd[11];
	char    kntno[14];
	char    kntketflg;
	char    knsgslbcd[4];
	short   kntzssdino;
	char    knttcyymd[11];
	char    fszrgrp[3];
	char    irikntryo[6];
	char    irikntryotni;
	char    gnkntryo[6];
	char    gnkntryotni;
	char    chkmj[5];
	char    rucd[3];
	char    ykcd[21];
	char    htkfkiri;
	char    ysnflg;
	char    kntfrflg;
	char    ykzrcd[5];
	char    hzzrcd[5];
	char    kntjtflg;
	char    knttktkbn;
	char    hbncflg;
	char    kntzsssflg;
	char    kntzstrdh[27];
	char    kntzsssdh[27];
	char    stlkntzsssdh[27];
	char    stlkntzsssip[16];
	char    stlkntzssssyaid[9];
	char    sklblflg;
	char    zrcd[5];
	char    sstme[9];
	char    ssymd[11];
	char    tntme[5];
	char    tntni;
	char    tnryo[6];
	char    tnryotni;
	char    ssbi[21];
	char    sshhu[21];
	char    hkflg[3];
	char    msriymd[11];
	char    mkntno[14];
	char    id2[11];
	short   id2pos;
	char    id3[11];
	short   id3pos;
	char    sntrno[11];
	char    sntnno[11];
	char    nstsgflg;
	char    hknjk;
	char    hknjkksndh[27];
	char    ksndh[27];
	char	trkdh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 86 "Kenzok.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Kenzok

BmlDMMInfo	KenzokArray[] = {
	DMM_SDATE( utkymd ),
	DMM_SSTRING( irino ),
	DMM_SCHAR( iriketflg ),
	DMM_SSHORT( zssdino ),
	DMM_SDATE( sriymd ),
	DMM_SSTRING( kntno ),
	DMM_SCHAR( kntketflg ),
	DMM_SSTRING( knsgslbcd ),
	DMM_SSHORT( kntzssdino ),
	DMM_SDATE( knttcyymd ),
	DMM_SSTRING( fszrgrp ),
	DMM_SSTRING( irikntryo ),
	DMM_SCHAR( irikntryotni ),
	DMM_SSTRING( gnkntryo ),
	DMM_SCHAR( gnkntryotni ),
	DMM_SSTRING( chkmj ),
	DMM_SSTRING( rucd ),
	DMM_SSTRING( ykcd ),
	DMM_SCHAR( htkfkiri ),
	DMM_SCHAR( ysnflg ),
	DMM_SCHAR( kntfrflg ),
	DMM_SSTRING( ykzrcd ),
	DMM_SSTRING( hzzrcd ),
	DMM_SCHAR( kntjtflg ),
	DMM_SCHAR( knttktkbn ),
	DMM_SCHAR( hbncflg ),
	DMM_SCHAR( kntzsssflg ),
	DMM_STIMESTAMP( kntzstrdh ),
	DMM_STIMESTAMP( kntzsssdh ),
	DMM_STIMESTAMP( stlkntzsssdh ),
	DMM_SSTRING( stlkntzsssip ),
	DMM_SSTRING( stlkntzssssyaid ),
	DMM_SCHAR( sklblflg ),
	DMM_SSTRING( zrcd ),
	DMM_STIME( sstme ),
	DMM_SDATE( ssymd ),
	DMM_SSTRING( tntme ),
	DMM_SCHAR( tntni ),
	DMM_SSTRING( tnryo ),
	DMM_SCHAR( tnryotni ),
	DMM_SSTRING( ssbi ),
	DMM_SSTRING( sshhu ),
	DMM_SSTRING( hkflg ),
	DMM_SDATE( msriymd ),
	DMM_SSTRING( mkntno ),
	DMM_SSTRING( id2 ),
	DMM_SSHORT( id2pos ),
	DMM_SSTRING( id3 ),
	DMM_SSHORT( id3pos ),
	DMM_SSTRING( sntrno ),
	DMM_SSTRING( sntnno ),
	DMM_SCHAR( nstsgflg ),
	DMM_SCHAR( hknjk ),
	DMM_STIMESTAMP( hknjkksndh ),
	DMM_STIMESTAMP( ksndh ),
	DMM_STIMESTAMP( trkdh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKenzokSelectAll()
 *    KENZOK レコード全件取得
 * ■引数
 *    [O]  Kenzok** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKenzokSelectAll( Kenzok** arrayOut, int* numOut )
{
    Kenzok*     array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 170 "Kenzok.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		KNSGSLBCD,
		KNTZSSDINO,
		KNTTCYYMD,
		FSZRGRP,
		IRIKNTRYO,
		IRIKNTRYOTNI,
		GNKNTRYO,
		GNKNTRYOTNI,
		CHKMJ,
		RUCD,
		YKCD,
		HTKFKIRI,
		YSNFLG,
		KNTFRFLG,
		YKZRCD,
		HZZRCD,
		KNTJTFLG,
		KNTTKTKBN,
		HBNCFLG,
		KNTZSSSFLG,
		KNTZSTRDH,
		KNTZSSSDH,
		STLKNTZSSSDH,
		STLKNTZSSSIP,
		STLKNTZSSSSYAID,
		SKLBLFLG,
		ZRCD,
		SSTME,
		SSYMD,
		TNTME,
		TNTNI,
		TNRYO,
		TNRYOTNI,
		SSBI,
		SSHHU,
		HKFLG,
		MSRIYMD,
		MKNTNO,
		ID2,
		ID2POS,
		ID3,
		ID3POS,
		SNTRNO,
		SNTNNO,
		NSTSGFLG,
		HKNJK,
		HKNJKKSNDH,
		KSNDH,
		TRKDH
    FROM
        KENZOK FOR READ ONLY;
*/

#line 231 "Kenzok.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 233 "Kenzok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 233 "Kenzok.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 233 "Kenzok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 233 "Kenzok.sqc"
  sqlastop(0L);
}

#line 233 "Kenzok.sqc"


    while( 1 ) {
        Kenzok* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:sriymd,
			:kntno,
			:kntketflg,
			:knsgslbcd,
			:kntzssdino,
			:knttcyymd,
			:fszrgrp,
			:irikntryo,
			:irikntryotni,
			:gnkntryo,
			:gnkntryotni,
			:chkmj,
			:rucd,
			:ykcd,
			:htkfkiri,
			:ysnflg,
			:kntfrflg,
			:ykzrcd,
			:hzzrcd,
			:kntjtflg,
			:knttktkbn,
			:hbncflg,
			:kntzsssflg,
			:kntzstrdh,
			:kntzsssdh,
			:stlkntzsssdh,
			:stlkntzsssip,
			:stlkntzssssyaid,
			:sklblflg,
			:zrcd,
			:sstme,
			:ssymd,
			:tntme,
			:tntni,
			:tnryo,
			:tnryotni,
			:ssbi,
			:sshhu,
			:hkflg,
			:msriymd,
			:mkntno,
			:id2,
			:id2pos,
			:id3,
			:id3pos,
			:sntrno,
			:sntnno,
			:nstsgflg,
			:hknjk,
			:hknjkksndh,
			:ksndh,
			:trkdh;
*/

{
#line 294 "Kenzok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 294 "Kenzok.sqc"
  sqlaaloc(3,56,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[56];
#line 294 "Kenzok.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 294 "Kenzok.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 294 "Kenzok.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 294 "Kenzok.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 294 "Kenzok.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 294 "Kenzok.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 294 "Kenzok.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 294 "Kenzok.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 294 "Kenzok.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 294 "Kenzok.sqc"
      sql_setdlist[4].sqldata = (void*)sriymd;
#line 294 "Kenzok.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 14;
#line 294 "Kenzok.sqc"
      sql_setdlist[5].sqldata = (void*)kntno;
#line 294 "Kenzok.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 294 "Kenzok.sqc"
      sql_setdlist[6].sqldata = (void*)&kntketflg;
#line 294 "Kenzok.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 4;
#line 294 "Kenzok.sqc"
      sql_setdlist[7].sqldata = (void*)knsgslbcd;
#line 294 "Kenzok.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 294 "Kenzok.sqc"
      sql_setdlist[8].sqldata = (void*)&kntzssdino;
#line 294 "Kenzok.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 294 "Kenzok.sqc"
      sql_setdlist[9].sqldata = (void*)knttcyymd;
#line 294 "Kenzok.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 3;
#line 294 "Kenzok.sqc"
      sql_setdlist[10].sqldata = (void*)fszrgrp;
#line 294 "Kenzok.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 6;
#line 294 "Kenzok.sqc"
      sql_setdlist[11].sqldata = (void*)irikntryo;
#line 294 "Kenzok.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[12].sqltype = 452; sql_setdlist[12].sqllen = 1;
#line 294 "Kenzok.sqc"
      sql_setdlist[12].sqldata = (void*)&irikntryotni;
#line 294 "Kenzok.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 6;
#line 294 "Kenzok.sqc"
      sql_setdlist[13].sqldata = (void*)gnkntryo;
#line 294 "Kenzok.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 294 "Kenzok.sqc"
      sql_setdlist[14].sqldata = (void*)&gnkntryotni;
#line 294 "Kenzok.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 5;
#line 294 "Kenzok.sqc"
      sql_setdlist[15].sqldata = (void*)chkmj;
#line 294 "Kenzok.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 3;
#line 294 "Kenzok.sqc"
      sql_setdlist[16].sqldata = (void*)rucd;
#line 294 "Kenzok.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 21;
#line 294 "Kenzok.sqc"
      sql_setdlist[17].sqldata = (void*)ykcd;
#line 294 "Kenzok.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 294 "Kenzok.sqc"
      sql_setdlist[18].sqldata = (void*)&htkfkiri;
#line 294 "Kenzok.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 294 "Kenzok.sqc"
      sql_setdlist[19].sqldata = (void*)&ysnflg;
#line 294 "Kenzok.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 294 "Kenzok.sqc"
      sql_setdlist[20].sqldata = (void*)&kntfrflg;
#line 294 "Kenzok.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 5;
#line 294 "Kenzok.sqc"
      sql_setdlist[21].sqldata = (void*)ykzrcd;
#line 294 "Kenzok.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 5;
#line 294 "Kenzok.sqc"
      sql_setdlist[22].sqldata = (void*)hzzrcd;
#line 294 "Kenzok.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 294 "Kenzok.sqc"
      sql_setdlist[23].sqldata = (void*)&kntjtflg;
#line 294 "Kenzok.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 294 "Kenzok.sqc"
      sql_setdlist[24].sqldata = (void*)&knttktkbn;
#line 294 "Kenzok.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 294 "Kenzok.sqc"
      sql_setdlist[25].sqldata = (void*)&hbncflg;
#line 294 "Kenzok.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 294 "Kenzok.sqc"
      sql_setdlist[26].sqldata = (void*)&kntzsssflg;
#line 294 "Kenzok.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 27;
#line 294 "Kenzok.sqc"
      sql_setdlist[27].sqldata = (void*)kntzstrdh;
#line 294 "Kenzok.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 27;
#line 294 "Kenzok.sqc"
      sql_setdlist[28].sqldata = (void*)kntzsssdh;
#line 294 "Kenzok.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 294 "Kenzok.sqc"
      sql_setdlist[29].sqldata = (void*)stlkntzsssdh;
#line 294 "Kenzok.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 16;
#line 294 "Kenzok.sqc"
      sql_setdlist[30].sqldata = (void*)stlkntzsssip;
#line 294 "Kenzok.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 9;
#line 294 "Kenzok.sqc"
      sql_setdlist[31].sqldata = (void*)stlkntzssssyaid;
#line 294 "Kenzok.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 294 "Kenzok.sqc"
      sql_setdlist[32].sqldata = (void*)&sklblflg;
#line 294 "Kenzok.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 5;
#line 294 "Kenzok.sqc"
      sql_setdlist[33].sqldata = (void*)zrcd;
#line 294 "Kenzok.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 9;
#line 294 "Kenzok.sqc"
      sql_setdlist[34].sqldata = (void*)sstme;
#line 294 "Kenzok.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 11;
#line 294 "Kenzok.sqc"
      sql_setdlist[35].sqldata = (void*)ssymd;
#line 294 "Kenzok.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 5;
#line 294 "Kenzok.sqc"
      sql_setdlist[36].sqldata = (void*)tntme;
#line 294 "Kenzok.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 294 "Kenzok.sqc"
      sql_setdlist[37].sqldata = (void*)&tntni;
#line 294 "Kenzok.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 6;
#line 294 "Kenzok.sqc"
      sql_setdlist[38].sqldata = (void*)tnryo;
#line 294 "Kenzok.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 294 "Kenzok.sqc"
      sql_setdlist[39].sqldata = (void*)&tnryotni;
#line 294 "Kenzok.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 21;
#line 294 "Kenzok.sqc"
      sql_setdlist[40].sqldata = (void*)ssbi;
#line 294 "Kenzok.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 21;
#line 294 "Kenzok.sqc"
      sql_setdlist[41].sqldata = (void*)sshhu;
#line 294 "Kenzok.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 3;
#line 294 "Kenzok.sqc"
      sql_setdlist[42].sqldata = (void*)hkflg;
#line 294 "Kenzok.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 11;
#line 294 "Kenzok.sqc"
      sql_setdlist[43].sqldata = (void*)msriymd;
#line 294 "Kenzok.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 14;
#line 294 "Kenzok.sqc"
      sql_setdlist[44].sqldata = (void*)mkntno;
#line 294 "Kenzok.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 11;
#line 294 "Kenzok.sqc"
      sql_setdlist[45].sqldata = (void*)id2;
#line 294 "Kenzok.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[46].sqltype = 500; sql_setdlist[46].sqllen = 2;
#line 294 "Kenzok.sqc"
      sql_setdlist[46].sqldata = (void*)&id2pos;
#line 294 "Kenzok.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 11;
#line 294 "Kenzok.sqc"
      sql_setdlist[47].sqldata = (void*)id3;
#line 294 "Kenzok.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[48].sqltype = 500; sql_setdlist[48].sqllen = 2;
#line 294 "Kenzok.sqc"
      sql_setdlist[48].sqldata = (void*)&id3pos;
#line 294 "Kenzok.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 11;
#line 294 "Kenzok.sqc"
      sql_setdlist[49].sqldata = (void*)sntrno;
#line 294 "Kenzok.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 11;
#line 294 "Kenzok.sqc"
      sql_setdlist[50].sqldata = (void*)sntnno;
#line 294 "Kenzok.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[51].sqltype = 452; sql_setdlist[51].sqllen = 1;
#line 294 "Kenzok.sqc"
      sql_setdlist[51].sqldata = (void*)&nstsgflg;
#line 294 "Kenzok.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[52].sqltype = 452; sql_setdlist[52].sqllen = 1;
#line 294 "Kenzok.sqc"
      sql_setdlist[52].sqldata = (void*)&hknjk;
#line 294 "Kenzok.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 27;
#line 294 "Kenzok.sqc"
      sql_setdlist[53].sqldata = (void*)hknjkksndh;
#line 294 "Kenzok.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 27;
#line 294 "Kenzok.sqc"
      sql_setdlist[54].sqldata = (void*)ksndh;
#line 294 "Kenzok.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 27;
#line 294 "Kenzok.sqc"
      sql_setdlist[55].sqldata = (void*)trkdh;
#line 294 "Kenzok.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 294 "Kenzok.sqc"
      sqlasetdata(3,0,56,sql_setdlist,0L,0L);
    }
#line 294 "Kenzok.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 294 "Kenzok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 294 "Kenzok.sqc"
  sqlastop(0L);
}

#line 294 "Kenzok.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kenzok*)ZbmlRealloc( array,
                                    sizeof( Kenzok ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kenzok ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KenzokArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 309 "Kenzok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 309 "Kenzok.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 309 "Kenzok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 309 "Kenzok.sqc"
  sqlastop(0L);
}

#line 309 "Kenzok.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 317 "Kenzok.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKenzokSelectKey()
 *    KENZOK レコードKey条件取得
 * ■引数
 *    [I]  Kenzok* pKey       取得するレコードのキー
 *    [O]  Kenzok** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKenzokSelectKey( Kenzok* pKey, Kenzok** arrayOut, int* numOut )
{
    Kenzok*     array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KenzokArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 343 "Kenzok.sqc"


    
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
		KNSGSLBCD,
		KNTZSSDINO,
		KNTTCYYMD,
		FSZRGRP,
		IRIKNTRYO,
		IRIKNTRYOTNI,
		GNKNTRYO,
		GNKNTRYOTNI,
		CHKMJ,
		RUCD,
		YKCD,
		HTKFKIRI,
		YSNFLG,
		KNTFRFLG,
		YKZRCD,
		HZZRCD,
		KNTJTFLG,
		KNTTKTKBN,
		HBNCFLG,
		KNTZSSSFLG,
		KNTZSTRDH,
		KNTZSSSDH,
		STLKNTZSSSDH,
		STLKNTZSSSIP,
		STLKNTZSSSSYAID,
		SKLBLFLG,
		ZRCD,
		SSTME,
		SSYMD,
		TNTME,
		TNTNI,
		TNRYO,
		TNRYOTNI,
		SSBI,
		SSHHU,
		HKFLG,
		MSRIYMD,
		MKNTNO,
		ID2,
		ID2POS,
		ID3,
		ID3POS,
		SNTRNO,
		SNTNNO,
		NSTSGFLG,
		HKNJK,
		HKNJKKSNDH,
		KSNDH,
		TRKDH
    FROM
        KENZOK
    WHERE
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		KNSGSLBCD = :knsgslbcd AND
		KNTZSSDINO = :kntzssdino FOR READ ONLY;
*/

#line 409 "Kenzok.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 411 "Kenzok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 411 "Kenzok.sqc"
  sqlaaloc(2,4,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 411 "Kenzok.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 411 "Kenzok.sqc"
      sql_setdlist[0].sqldata = (void*)sriymd;
#line 411 "Kenzok.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 411 "Kenzok.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 14;
#line 411 "Kenzok.sqc"
      sql_setdlist[1].sqldata = (void*)kntno;
#line 411 "Kenzok.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 411 "Kenzok.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 4;
#line 411 "Kenzok.sqc"
      sql_setdlist[2].sqldata = (void*)knsgslbcd;
#line 411 "Kenzok.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 411 "Kenzok.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 411 "Kenzok.sqc"
      sql_setdlist[3].sqldata = (void*)&kntzssdino;
#line 411 "Kenzok.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 411 "Kenzok.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 411 "Kenzok.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 411 "Kenzok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 411 "Kenzok.sqc"
  sqlastop(0L);
}

#line 411 "Kenzok.sqc"


    while( 1 ) {
        Kenzok* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:sriymd,
			:kntno,
			:kntketflg,
			:knsgslbcd,
			:kntzssdino,
			:knttcyymd,
			:fszrgrp,
			:irikntryo,
			:irikntryotni,
			:gnkntryo,
			:gnkntryotni,
			:chkmj,
			:rucd,
			:ykcd,
			:htkfkiri,
			:ysnflg,
			:kntfrflg,
			:ykzrcd,
			:hzzrcd,
			:kntjtflg,
			:knttktkbn,
			:hbncflg,
			:kntzsssflg,
			:kntzstrdh,
			:kntzsssdh,
			:stlkntzsssdh,
			:stlkntzsssip,
			:stlkntzssssyaid,
			:sklblflg,
			:zrcd,
			:sstme,
			:ssymd,
			:tntme,
			:tntni,
			:tnryo,
			:tnryotni,
			:ssbi,
			:sshhu,
			:hkflg,
			:msriymd,
			:mkntno,
			:id2,
			:id2pos,
			:id3,
			:id3pos,
			:sntrno,
			:sntnno,
			:nstsgflg,
			:hknjk,
			:hknjkksndh,
			:ksndh,
			:trkdh;
*/

{
#line 472 "Kenzok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 472 "Kenzok.sqc"
  sqlaaloc(3,56,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[56];
#line 472 "Kenzok.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 472 "Kenzok.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 472 "Kenzok.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 472 "Kenzok.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 472 "Kenzok.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 472 "Kenzok.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 472 "Kenzok.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 472 "Kenzok.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 472 "Kenzok.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 472 "Kenzok.sqc"
      sql_setdlist[4].sqldata = (void*)sriymd;
#line 472 "Kenzok.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 14;
#line 472 "Kenzok.sqc"
      sql_setdlist[5].sqldata = (void*)kntno;
#line 472 "Kenzok.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 472 "Kenzok.sqc"
      sql_setdlist[6].sqldata = (void*)&kntketflg;
#line 472 "Kenzok.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 4;
#line 472 "Kenzok.sqc"
      sql_setdlist[7].sqldata = (void*)knsgslbcd;
#line 472 "Kenzok.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 472 "Kenzok.sqc"
      sql_setdlist[8].sqldata = (void*)&kntzssdino;
#line 472 "Kenzok.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 472 "Kenzok.sqc"
      sql_setdlist[9].sqldata = (void*)knttcyymd;
#line 472 "Kenzok.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 3;
#line 472 "Kenzok.sqc"
      sql_setdlist[10].sqldata = (void*)fszrgrp;
#line 472 "Kenzok.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 6;
#line 472 "Kenzok.sqc"
      sql_setdlist[11].sqldata = (void*)irikntryo;
#line 472 "Kenzok.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[12].sqltype = 452; sql_setdlist[12].sqllen = 1;
#line 472 "Kenzok.sqc"
      sql_setdlist[12].sqldata = (void*)&irikntryotni;
#line 472 "Kenzok.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 6;
#line 472 "Kenzok.sqc"
      sql_setdlist[13].sqldata = (void*)gnkntryo;
#line 472 "Kenzok.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 472 "Kenzok.sqc"
      sql_setdlist[14].sqldata = (void*)&gnkntryotni;
#line 472 "Kenzok.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 5;
#line 472 "Kenzok.sqc"
      sql_setdlist[15].sqldata = (void*)chkmj;
#line 472 "Kenzok.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 3;
#line 472 "Kenzok.sqc"
      sql_setdlist[16].sqldata = (void*)rucd;
#line 472 "Kenzok.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 21;
#line 472 "Kenzok.sqc"
      sql_setdlist[17].sqldata = (void*)ykcd;
#line 472 "Kenzok.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 472 "Kenzok.sqc"
      sql_setdlist[18].sqldata = (void*)&htkfkiri;
#line 472 "Kenzok.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 472 "Kenzok.sqc"
      sql_setdlist[19].sqldata = (void*)&ysnflg;
#line 472 "Kenzok.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 472 "Kenzok.sqc"
      sql_setdlist[20].sqldata = (void*)&kntfrflg;
#line 472 "Kenzok.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 5;
#line 472 "Kenzok.sqc"
      sql_setdlist[21].sqldata = (void*)ykzrcd;
#line 472 "Kenzok.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 5;
#line 472 "Kenzok.sqc"
      sql_setdlist[22].sqldata = (void*)hzzrcd;
#line 472 "Kenzok.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 472 "Kenzok.sqc"
      sql_setdlist[23].sqldata = (void*)&kntjtflg;
#line 472 "Kenzok.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 472 "Kenzok.sqc"
      sql_setdlist[24].sqldata = (void*)&knttktkbn;
#line 472 "Kenzok.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 472 "Kenzok.sqc"
      sql_setdlist[25].sqldata = (void*)&hbncflg;
#line 472 "Kenzok.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 472 "Kenzok.sqc"
      sql_setdlist[26].sqldata = (void*)&kntzsssflg;
#line 472 "Kenzok.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 27;
#line 472 "Kenzok.sqc"
      sql_setdlist[27].sqldata = (void*)kntzstrdh;
#line 472 "Kenzok.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 27;
#line 472 "Kenzok.sqc"
      sql_setdlist[28].sqldata = (void*)kntzsssdh;
#line 472 "Kenzok.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 472 "Kenzok.sqc"
      sql_setdlist[29].sqldata = (void*)stlkntzsssdh;
#line 472 "Kenzok.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 16;
#line 472 "Kenzok.sqc"
      sql_setdlist[30].sqldata = (void*)stlkntzsssip;
#line 472 "Kenzok.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 9;
#line 472 "Kenzok.sqc"
      sql_setdlist[31].sqldata = (void*)stlkntzssssyaid;
#line 472 "Kenzok.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 472 "Kenzok.sqc"
      sql_setdlist[32].sqldata = (void*)&sklblflg;
#line 472 "Kenzok.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 5;
#line 472 "Kenzok.sqc"
      sql_setdlist[33].sqldata = (void*)zrcd;
#line 472 "Kenzok.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 9;
#line 472 "Kenzok.sqc"
      sql_setdlist[34].sqldata = (void*)sstme;
#line 472 "Kenzok.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 11;
#line 472 "Kenzok.sqc"
      sql_setdlist[35].sqldata = (void*)ssymd;
#line 472 "Kenzok.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 5;
#line 472 "Kenzok.sqc"
      sql_setdlist[36].sqldata = (void*)tntme;
#line 472 "Kenzok.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 472 "Kenzok.sqc"
      sql_setdlist[37].sqldata = (void*)&tntni;
#line 472 "Kenzok.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 6;
#line 472 "Kenzok.sqc"
      sql_setdlist[38].sqldata = (void*)tnryo;
#line 472 "Kenzok.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 472 "Kenzok.sqc"
      sql_setdlist[39].sqldata = (void*)&tnryotni;
#line 472 "Kenzok.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 21;
#line 472 "Kenzok.sqc"
      sql_setdlist[40].sqldata = (void*)ssbi;
#line 472 "Kenzok.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 21;
#line 472 "Kenzok.sqc"
      sql_setdlist[41].sqldata = (void*)sshhu;
#line 472 "Kenzok.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 3;
#line 472 "Kenzok.sqc"
      sql_setdlist[42].sqldata = (void*)hkflg;
#line 472 "Kenzok.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 11;
#line 472 "Kenzok.sqc"
      sql_setdlist[43].sqldata = (void*)msriymd;
#line 472 "Kenzok.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 14;
#line 472 "Kenzok.sqc"
      sql_setdlist[44].sqldata = (void*)mkntno;
#line 472 "Kenzok.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 11;
#line 472 "Kenzok.sqc"
      sql_setdlist[45].sqldata = (void*)id2;
#line 472 "Kenzok.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[46].sqltype = 500; sql_setdlist[46].sqllen = 2;
#line 472 "Kenzok.sqc"
      sql_setdlist[46].sqldata = (void*)&id2pos;
#line 472 "Kenzok.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 11;
#line 472 "Kenzok.sqc"
      sql_setdlist[47].sqldata = (void*)id3;
#line 472 "Kenzok.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[48].sqltype = 500; sql_setdlist[48].sqllen = 2;
#line 472 "Kenzok.sqc"
      sql_setdlist[48].sqldata = (void*)&id3pos;
#line 472 "Kenzok.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 11;
#line 472 "Kenzok.sqc"
      sql_setdlist[49].sqldata = (void*)sntrno;
#line 472 "Kenzok.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 11;
#line 472 "Kenzok.sqc"
      sql_setdlist[50].sqldata = (void*)sntnno;
#line 472 "Kenzok.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[51].sqltype = 452; sql_setdlist[51].sqllen = 1;
#line 472 "Kenzok.sqc"
      sql_setdlist[51].sqldata = (void*)&nstsgflg;
#line 472 "Kenzok.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[52].sqltype = 452; sql_setdlist[52].sqllen = 1;
#line 472 "Kenzok.sqc"
      sql_setdlist[52].sqldata = (void*)&hknjk;
#line 472 "Kenzok.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 27;
#line 472 "Kenzok.sqc"
      sql_setdlist[53].sqldata = (void*)hknjkksndh;
#line 472 "Kenzok.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 27;
#line 472 "Kenzok.sqc"
      sql_setdlist[54].sqldata = (void*)ksndh;
#line 472 "Kenzok.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 27;
#line 472 "Kenzok.sqc"
      sql_setdlist[55].sqldata = (void*)trkdh;
#line 472 "Kenzok.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 472 "Kenzok.sqc"
      sqlasetdata(3,0,56,sql_setdlist,0L,0L);
    }
#line 472 "Kenzok.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 472 "Kenzok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 472 "Kenzok.sqc"
  sqlastop(0L);
}

#line 472 "Kenzok.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kenzok*)ZbmlRealloc( array,
                                    sizeof( Kenzok ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kenzok ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KenzokArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 487 "Kenzok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 487 "Kenzok.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 487 "Kenzok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 487 "Kenzok.sqc"
  sqlastop(0L);
}

#line 487 "Kenzok.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 495 "Kenzok.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKenzokInsert()
 *    KENZOK レコードを挿入する
 * ■引数
 *    [I]  Kenzok* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKenzokInsert( Kenzok* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KenzokArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 518 "Kenzok.sqc"


    
/*
EXEC SQL INSERT INTO KENZOK
    (
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		KNSGSLBCD,
		KNTZSSDINO,
		KNTTCYYMD,
		FSZRGRP,
		IRIKNTRYO,
		IRIKNTRYOTNI,
		GNKNTRYO,
		GNKNTRYOTNI,
		CHKMJ,
		RUCD,
		YKCD,
		HTKFKIRI,
		YSNFLG,
		KNTFRFLG,
		YKZRCD,
		HZZRCD,
		KNTJTFLG,
		KNTTKTKBN,
		HBNCFLG,
		KNTZSSSFLG,
		KNTZSTRDH,
		KNTZSSSDH,
		STLKNTZSSSDH,
		STLKNTZSSSIP,
		STLKNTZSSSSYAID,
		SKLBLFLG,
		ZRCD,
		SSTME,
		SSYMD,
		TNTME,
		TNTNI,
		TNRYO,
		TNRYOTNI,
		SSBI,
		SSHHU,
		HKFLG,
		MSRIYMD,
		MKNTNO,
		ID2,
		ID2POS,
		ID3,
		ID3POS,
		SNTRNO,
		SNTNNO,
		NSTSGFLG,
		HKNJK,
		HKNJKKSNDH,
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
		:knsgslbcd,
		:kntzssdino,
		:knttcyymd,
		:fszrgrp,
		:irikntryo,
		:irikntryotni,
		:gnkntryo,
		:gnkntryotni,
		:chkmj,
		:rucd,
		:ykcd,
		:htkfkiri,
		:ysnflg,
		:kntfrflg,
		:ykzrcd,
		:hzzrcd,
		:kntjtflg,
		:knttktkbn,
		:hbncflg,
		:kntzsssflg,
		:kntzstrdh,
		:kntzsssdh,
		:stlkntzsssdh,
		:stlkntzsssip,
		:stlkntzssssyaid,
		:sklblflg,
		:zrcd,
		:sstme,
		:ssymd,
		:tntme,
		:tntni,
		:tnryo,
		:tnryotni,
		:ssbi,
		:sshhu,
		:hkflg,
		:msriymd,
		:mkntno,
		:id2,
		:id2pos,
		:id3,
		:id3pos,
		:sntrno,
		:sntnno,
		:nstsgflg,
		:hknjk,
		:hknjkksndh,
		CURRENT TIMESTAMP,
		CURRENT TIMESTAMP
    );
*/

{
#line 635 "Kenzok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 635 "Kenzok.sqc"
  sqlaaloc(2,54,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[54];
#line 635 "Kenzok.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 635 "Kenzok.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 635 "Kenzok.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 635 "Kenzok.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 635 "Kenzok.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 635 "Kenzok.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 635 "Kenzok.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 635 "Kenzok.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 635 "Kenzok.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 635 "Kenzok.sqc"
      sql_setdlist[4].sqldata = (void*)sriymd;
#line 635 "Kenzok.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 14;
#line 635 "Kenzok.sqc"
      sql_setdlist[5].sqldata = (void*)kntno;
#line 635 "Kenzok.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 635 "Kenzok.sqc"
      sql_setdlist[6].sqldata = (void*)&kntketflg;
#line 635 "Kenzok.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 4;
#line 635 "Kenzok.sqc"
      sql_setdlist[7].sqldata = (void*)knsgslbcd;
#line 635 "Kenzok.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 635 "Kenzok.sqc"
      sql_setdlist[8].sqldata = (void*)&kntzssdino;
#line 635 "Kenzok.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 635 "Kenzok.sqc"
      sql_setdlist[9].sqldata = (void*)knttcyymd;
#line 635 "Kenzok.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 3;
#line 635 "Kenzok.sqc"
      sql_setdlist[10].sqldata = (void*)fszrgrp;
#line 635 "Kenzok.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 6;
#line 635 "Kenzok.sqc"
      sql_setdlist[11].sqldata = (void*)irikntryo;
#line 635 "Kenzok.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[12].sqltype = 452; sql_setdlist[12].sqllen = 1;
#line 635 "Kenzok.sqc"
      sql_setdlist[12].sqldata = (void*)&irikntryotni;
#line 635 "Kenzok.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 6;
#line 635 "Kenzok.sqc"
      sql_setdlist[13].sqldata = (void*)gnkntryo;
#line 635 "Kenzok.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 635 "Kenzok.sqc"
      sql_setdlist[14].sqldata = (void*)&gnkntryotni;
#line 635 "Kenzok.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 5;
#line 635 "Kenzok.sqc"
      sql_setdlist[15].sqldata = (void*)chkmj;
#line 635 "Kenzok.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 3;
#line 635 "Kenzok.sqc"
      sql_setdlist[16].sqldata = (void*)rucd;
#line 635 "Kenzok.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 21;
#line 635 "Kenzok.sqc"
      sql_setdlist[17].sqldata = (void*)ykcd;
#line 635 "Kenzok.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 635 "Kenzok.sqc"
      sql_setdlist[18].sqldata = (void*)&htkfkiri;
#line 635 "Kenzok.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 635 "Kenzok.sqc"
      sql_setdlist[19].sqldata = (void*)&ysnflg;
#line 635 "Kenzok.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 635 "Kenzok.sqc"
      sql_setdlist[20].sqldata = (void*)&kntfrflg;
#line 635 "Kenzok.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 5;
#line 635 "Kenzok.sqc"
      sql_setdlist[21].sqldata = (void*)ykzrcd;
#line 635 "Kenzok.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 5;
#line 635 "Kenzok.sqc"
      sql_setdlist[22].sqldata = (void*)hzzrcd;
#line 635 "Kenzok.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 635 "Kenzok.sqc"
      sql_setdlist[23].sqldata = (void*)&kntjtflg;
#line 635 "Kenzok.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 635 "Kenzok.sqc"
      sql_setdlist[24].sqldata = (void*)&knttktkbn;
#line 635 "Kenzok.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 635 "Kenzok.sqc"
      sql_setdlist[25].sqldata = (void*)&hbncflg;
#line 635 "Kenzok.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 635 "Kenzok.sqc"
      sql_setdlist[26].sqldata = (void*)&kntzsssflg;
#line 635 "Kenzok.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 27;
#line 635 "Kenzok.sqc"
      sql_setdlist[27].sqldata = (void*)kntzstrdh;
#line 635 "Kenzok.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 27;
#line 635 "Kenzok.sqc"
      sql_setdlist[28].sqldata = (void*)kntzsssdh;
#line 635 "Kenzok.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 635 "Kenzok.sqc"
      sql_setdlist[29].sqldata = (void*)stlkntzsssdh;
#line 635 "Kenzok.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 16;
#line 635 "Kenzok.sqc"
      sql_setdlist[30].sqldata = (void*)stlkntzsssip;
#line 635 "Kenzok.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 9;
#line 635 "Kenzok.sqc"
      sql_setdlist[31].sqldata = (void*)stlkntzssssyaid;
#line 635 "Kenzok.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 635 "Kenzok.sqc"
      sql_setdlist[32].sqldata = (void*)&sklblflg;
#line 635 "Kenzok.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 5;
#line 635 "Kenzok.sqc"
      sql_setdlist[33].sqldata = (void*)zrcd;
#line 635 "Kenzok.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 9;
#line 635 "Kenzok.sqc"
      sql_setdlist[34].sqldata = (void*)sstme;
#line 635 "Kenzok.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 11;
#line 635 "Kenzok.sqc"
      sql_setdlist[35].sqldata = (void*)ssymd;
#line 635 "Kenzok.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 5;
#line 635 "Kenzok.sqc"
      sql_setdlist[36].sqldata = (void*)tntme;
#line 635 "Kenzok.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 635 "Kenzok.sqc"
      sql_setdlist[37].sqldata = (void*)&tntni;
#line 635 "Kenzok.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 6;
#line 635 "Kenzok.sqc"
      sql_setdlist[38].sqldata = (void*)tnryo;
#line 635 "Kenzok.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 635 "Kenzok.sqc"
      sql_setdlist[39].sqldata = (void*)&tnryotni;
#line 635 "Kenzok.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 21;
#line 635 "Kenzok.sqc"
      sql_setdlist[40].sqldata = (void*)ssbi;
#line 635 "Kenzok.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 21;
#line 635 "Kenzok.sqc"
      sql_setdlist[41].sqldata = (void*)sshhu;
#line 635 "Kenzok.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 3;
#line 635 "Kenzok.sqc"
      sql_setdlist[42].sqldata = (void*)hkflg;
#line 635 "Kenzok.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 11;
#line 635 "Kenzok.sqc"
      sql_setdlist[43].sqldata = (void*)msriymd;
#line 635 "Kenzok.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 14;
#line 635 "Kenzok.sqc"
      sql_setdlist[44].sqldata = (void*)mkntno;
#line 635 "Kenzok.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 11;
#line 635 "Kenzok.sqc"
      sql_setdlist[45].sqldata = (void*)id2;
#line 635 "Kenzok.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[46].sqltype = 500; sql_setdlist[46].sqllen = 2;
#line 635 "Kenzok.sqc"
      sql_setdlist[46].sqldata = (void*)&id2pos;
#line 635 "Kenzok.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 11;
#line 635 "Kenzok.sqc"
      sql_setdlist[47].sqldata = (void*)id3;
#line 635 "Kenzok.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[48].sqltype = 500; sql_setdlist[48].sqllen = 2;
#line 635 "Kenzok.sqc"
      sql_setdlist[48].sqldata = (void*)&id3pos;
#line 635 "Kenzok.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 11;
#line 635 "Kenzok.sqc"
      sql_setdlist[49].sqldata = (void*)sntrno;
#line 635 "Kenzok.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 11;
#line 635 "Kenzok.sqc"
      sql_setdlist[50].sqldata = (void*)sntnno;
#line 635 "Kenzok.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[51].sqltype = 452; sql_setdlist[51].sqllen = 1;
#line 635 "Kenzok.sqc"
      sql_setdlist[51].sqldata = (void*)&nstsgflg;
#line 635 "Kenzok.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[52].sqltype = 452; sql_setdlist[52].sqllen = 1;
#line 635 "Kenzok.sqc"
      sql_setdlist[52].sqldata = (void*)&hknjk;
#line 635 "Kenzok.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 27;
#line 635 "Kenzok.sqc"
      sql_setdlist[53].sqldata = (void*)hknjkksndh;
#line 635 "Kenzok.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 635 "Kenzok.sqc"
      sqlasetdata(2,0,54,sql_setdlist,0L,0L);
    }
#line 635 "Kenzok.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 635 "Kenzok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 635 "Kenzok.sqc"
  sqlastop(0L);
}

#line 635 "Kenzok.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 640 "Kenzok.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKenzokUpdate()
 *    KENZOK レコードを更新する
 * ■引数
 *    [I]  Kenzok* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKenzokUpdate( Kenzok* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KenzokArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 664 "Kenzok.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 665 "Kenzok.sqc"


    
/*
EXEC SQL UPDATE KENZOK
    SET (
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		KNTKETFLG,
		KNTTCYYMD,
		FSZRGRP,
		IRIKNTRYO,
		IRIKNTRYOTNI,
		GNKNTRYO,
		GNKNTRYOTNI,
		CHKMJ,
		RUCD,
		YKCD,
		HTKFKIRI,
		YSNFLG,
		KNTFRFLG,
		YKZRCD,
		HZZRCD,
		KNTJTFLG,
		KNTTKTKBN,
		HBNCFLG,
		KNTZSSSFLG,
		KNTZSTRDH,
		KNTZSSSDH,
		STLKNTZSSSDH,
		STLKNTZSSSIP,
		STLKNTZSSSSYAID,
		SKLBLFLG,
		ZRCD,
		SSTME,
		SSYMD,
		TNTME,
		TNTNI,
		TNRYO,
		TNRYOTNI,
		SSBI,
		SSHHU,
		HKFLG,
		MSRIYMD,
		MKNTNO,
		ID2,
		ID2POS,
		ID3,
		ID3POS,
		SNTRNO,
		SNTNNO,
		NSTSGFLG,
		HKNJK,
		HKNJKKSNDH,
		KSNDH,
		TRKDH
    ) = (
		:utkymd,
		:irino,
		:iriketflg,
		:zssdino,
		:kntketflg,
		:knttcyymd,
		:fszrgrp,
		:irikntryo,
		:irikntryotni,
		:gnkntryo,
		:gnkntryotni,
		:chkmj,
		:rucd,
		:ykcd,
		:htkfkiri,
		:ysnflg,
		:kntfrflg,
		:ykzrcd,
		:hzzrcd,
		:kntjtflg,
		:knttktkbn,
		:hbncflg,
		:kntzsssflg,
		:kntzstrdh,
		:kntzsssdh,
		:stlkntzsssdh,
		:stlkntzsssip,
		:stlkntzssssyaid,
		:sklblflg,
		:zrcd,
		:sstme,
		:ssymd,
		:tntme,
		:tntni,
		:tnryo,
		:tnryotni,
		:ssbi,
		:sshhu,
		:hkflg,
		:msriymd,
		:mkntno,
		:id2,
		:id2pos,
		:id3,
		:id3pos,
		:sntrno,
		:sntnno,
		:nstsgflg,
		:hknjk,
		:hknjkksndh,
		CURRENT TIMESTAMP,
		:trkdh
    ) WHERE
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		KNSGSLBCD = :knsgslbcd AND
		KNTZSSDINO = :kntzssdino;
*/

{
#line 778 "Kenzok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 778 "Kenzok.sqc"
  sqlaaloc(2,55,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[55];
#line 778 "Kenzok.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 778 "Kenzok.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 778 "Kenzok.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 778 "Kenzok.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 778 "Kenzok.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 778 "Kenzok.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 778 "Kenzok.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 778 "Kenzok.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 778 "Kenzok.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 778 "Kenzok.sqc"
      sql_setdlist[4].sqldata = (void*)&kntketflg;
#line 778 "Kenzok.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 778 "Kenzok.sqc"
      sql_setdlist[5].sqldata = (void*)knttcyymd;
#line 778 "Kenzok.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 3;
#line 778 "Kenzok.sqc"
      sql_setdlist[6].sqldata = (void*)fszrgrp;
#line 778 "Kenzok.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 6;
#line 778 "Kenzok.sqc"
      sql_setdlist[7].sqldata = (void*)irikntryo;
#line 778 "Kenzok.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 778 "Kenzok.sqc"
      sql_setdlist[8].sqldata = (void*)&irikntryotni;
#line 778 "Kenzok.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 6;
#line 778 "Kenzok.sqc"
      sql_setdlist[9].sqldata = (void*)gnkntryo;
#line 778 "Kenzok.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 778 "Kenzok.sqc"
      sql_setdlist[10].sqldata = (void*)&gnkntryotni;
#line 778 "Kenzok.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 5;
#line 778 "Kenzok.sqc"
      sql_setdlist[11].sqldata = (void*)chkmj;
#line 778 "Kenzok.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 3;
#line 778 "Kenzok.sqc"
      sql_setdlist[12].sqldata = (void*)rucd;
#line 778 "Kenzok.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 778 "Kenzok.sqc"
      sql_setdlist[13].sqldata = (void*)ykcd;
#line 778 "Kenzok.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 778 "Kenzok.sqc"
      sql_setdlist[14].sqldata = (void*)&htkfkiri;
#line 778 "Kenzok.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[15].sqltype = 452; sql_setdlist[15].sqllen = 1;
#line 778 "Kenzok.sqc"
      sql_setdlist[15].sqldata = (void*)&ysnflg;
#line 778 "Kenzok.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 778 "Kenzok.sqc"
      sql_setdlist[16].sqldata = (void*)&kntfrflg;
#line 778 "Kenzok.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 5;
#line 778 "Kenzok.sqc"
      sql_setdlist[17].sqldata = (void*)ykzrcd;
#line 778 "Kenzok.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 5;
#line 778 "Kenzok.sqc"
      sql_setdlist[18].sqldata = (void*)hzzrcd;
#line 778 "Kenzok.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 778 "Kenzok.sqc"
      sql_setdlist[19].sqldata = (void*)&kntjtflg;
#line 778 "Kenzok.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 778 "Kenzok.sqc"
      sql_setdlist[20].sqldata = (void*)&knttktkbn;
#line 778 "Kenzok.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 778 "Kenzok.sqc"
      sql_setdlist[21].sqldata = (void*)&hbncflg;
#line 778 "Kenzok.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 778 "Kenzok.sqc"
      sql_setdlist[22].sqldata = (void*)&kntzsssflg;
#line 778 "Kenzok.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 27;
#line 778 "Kenzok.sqc"
      sql_setdlist[23].sqldata = (void*)kntzstrdh;
#line 778 "Kenzok.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 27;
#line 778 "Kenzok.sqc"
      sql_setdlist[24].sqldata = (void*)kntzsssdh;
#line 778 "Kenzok.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 27;
#line 778 "Kenzok.sqc"
      sql_setdlist[25].sqldata = (void*)stlkntzsssdh;
#line 778 "Kenzok.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 16;
#line 778 "Kenzok.sqc"
      sql_setdlist[26].sqldata = (void*)stlkntzsssip;
#line 778 "Kenzok.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 9;
#line 778 "Kenzok.sqc"
      sql_setdlist[27].sqldata = (void*)stlkntzssssyaid;
#line 778 "Kenzok.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 778 "Kenzok.sqc"
      sql_setdlist[28].sqldata = (void*)&sklblflg;
#line 778 "Kenzok.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 5;
#line 778 "Kenzok.sqc"
      sql_setdlist[29].sqldata = (void*)zrcd;
#line 778 "Kenzok.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 9;
#line 778 "Kenzok.sqc"
      sql_setdlist[30].sqldata = (void*)sstme;
#line 778 "Kenzok.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 11;
#line 778 "Kenzok.sqc"
      sql_setdlist[31].sqldata = (void*)ssymd;
#line 778 "Kenzok.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 5;
#line 778 "Kenzok.sqc"
      sql_setdlist[32].sqldata = (void*)tntme;
#line 778 "Kenzok.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 778 "Kenzok.sqc"
      sql_setdlist[33].sqldata = (void*)&tntni;
#line 778 "Kenzok.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 6;
#line 778 "Kenzok.sqc"
      sql_setdlist[34].sqldata = (void*)tnryo;
#line 778 "Kenzok.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 778 "Kenzok.sqc"
      sql_setdlist[35].sqldata = (void*)&tnryotni;
#line 778 "Kenzok.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 21;
#line 778 "Kenzok.sqc"
      sql_setdlist[36].sqldata = (void*)ssbi;
#line 778 "Kenzok.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 21;
#line 778 "Kenzok.sqc"
      sql_setdlist[37].sqldata = (void*)sshhu;
#line 778 "Kenzok.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 3;
#line 778 "Kenzok.sqc"
      sql_setdlist[38].sqldata = (void*)hkflg;
#line 778 "Kenzok.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 11;
#line 778 "Kenzok.sqc"
      sql_setdlist[39].sqldata = (void*)msriymd;
#line 778 "Kenzok.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 14;
#line 778 "Kenzok.sqc"
      sql_setdlist[40].sqldata = (void*)mkntno;
#line 778 "Kenzok.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 11;
#line 778 "Kenzok.sqc"
      sql_setdlist[41].sqldata = (void*)id2;
#line 778 "Kenzok.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[42].sqltype = 500; sql_setdlist[42].sqllen = 2;
#line 778 "Kenzok.sqc"
      sql_setdlist[42].sqldata = (void*)&id2pos;
#line 778 "Kenzok.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 11;
#line 778 "Kenzok.sqc"
      sql_setdlist[43].sqldata = (void*)id3;
#line 778 "Kenzok.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[44].sqltype = 500; sql_setdlist[44].sqllen = 2;
#line 778 "Kenzok.sqc"
      sql_setdlist[44].sqldata = (void*)&id3pos;
#line 778 "Kenzok.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 11;
#line 778 "Kenzok.sqc"
      sql_setdlist[45].sqldata = (void*)sntrno;
#line 778 "Kenzok.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 11;
#line 778 "Kenzok.sqc"
      sql_setdlist[46].sqldata = (void*)sntnno;
#line 778 "Kenzok.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 778 "Kenzok.sqc"
      sql_setdlist[47].sqldata = (void*)&nstsgflg;
#line 778 "Kenzok.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 778 "Kenzok.sqc"
      sql_setdlist[48].sqldata = (void*)&hknjk;
#line 778 "Kenzok.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 27;
#line 778 "Kenzok.sqc"
      sql_setdlist[49].sqldata = (void*)hknjkksndh;
#line 778 "Kenzok.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 27;
#line 778 "Kenzok.sqc"
      sql_setdlist[50].sqldata = (void*)trkdh;
#line 778 "Kenzok.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 11;
#line 778 "Kenzok.sqc"
      sql_setdlist[51].sqldata = (void*)sriymd;
#line 778 "Kenzok.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 14;
#line 778 "Kenzok.sqc"
      sql_setdlist[52].sqldata = (void*)kntno;
#line 778 "Kenzok.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 4;
#line 778 "Kenzok.sqc"
      sql_setdlist[53].sqldata = (void*)knsgslbcd;
#line 778 "Kenzok.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sql_setdlist[54].sqltype = 500; sql_setdlist[54].sqllen = 2;
#line 778 "Kenzok.sqc"
      sql_setdlist[54].sqldata = (void*)&kntzssdino;
#line 778 "Kenzok.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 778 "Kenzok.sqc"
      sqlasetdata(2,0,55,sql_setdlist,0L,0L);
    }
#line 778 "Kenzok.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 778 "Kenzok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 778 "Kenzok.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 778 "Kenzok.sqc"
  sqlastop(0L);
}

#line 778 "Kenzok.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 783 "Kenzok.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 787 "Kenzok.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKenzokDelete()
 *    KENZOK レコードを削除する
 * ■引数
 *    [I]  Kenzok* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKenzokDelete( Kenzok* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KenzokArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 811 "Kenzok.sqc"


    
/*
EXEC SQL DELETE FROM KENZOK
    WHERE
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		KNSGSLBCD = :knsgslbcd AND
		KNTZSSDINO = :kntzssdino;
*/

{
#line 818 "Kenzok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 818 "Kenzok.sqc"
  sqlaaloc(2,4,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 818 "Kenzok.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 818 "Kenzok.sqc"
      sql_setdlist[0].sqldata = (void*)sriymd;
#line 818 "Kenzok.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 818 "Kenzok.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 14;
#line 818 "Kenzok.sqc"
      sql_setdlist[1].sqldata = (void*)kntno;
#line 818 "Kenzok.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 818 "Kenzok.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 4;
#line 818 "Kenzok.sqc"
      sql_setdlist[2].sqldata = (void*)knsgslbcd;
#line 818 "Kenzok.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 818 "Kenzok.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 818 "Kenzok.sqc"
      sql_setdlist[3].sqldata = (void*)&kntzssdino;
#line 818 "Kenzok.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 818 "Kenzok.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 818 "Kenzok.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 818 "Kenzok.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 818 "Kenzok.sqc"
  sqlastop(0L);
}

#line 818 "Kenzok.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 823 "Kenzok.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
