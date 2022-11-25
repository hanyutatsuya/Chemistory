static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,53,65,112,85,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,65,50,48,53,90,79,75,85,0,0,0,0,0,0,0,0,
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


#line 1 "A205zoku.sqc"
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
 *  1.00     2006-02-10                    Create
 *  4.01     2009-02-10     K.Ameno        緊急SUN EOSL対応
 **********************************************************************/
#include <stdio.h>

#include "A205zoku.h"
#include "bml_misc.h"
#include "bml_db.h"
#include "bml_dmm.h"
#include "bmllog.h"

#define ALLOC_UNIT		1


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 26 "A205zoku.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 31 "A205zoku.sqc"

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
	char    ykzrcd[4];
	char    hzzrcd[4];
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
	char    zrcd[4];
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
	char    trkdh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 88 "A205zoku.sqc"



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
 * AZokuSel()
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
long AZokuSel( Kenzok* pKey, Kenzok** arrayOut, int* numOut )
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

#line 179 "A205zoku.sqc"


    
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
		KNTNO = :kntno AND
		KNSGSLBCD = :knsgslbcd AND
		KNTZSSDINO = :kntzssdino AND
		SRIYMD = :sriymd FOR READ ONLY;
*/

#line 245 "A205zoku.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 247 "A205zoku.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 247 "A205zoku.sqc"
  sqlaaloc(2,4,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 247 "A205zoku.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 14;
#line 247 "A205zoku.sqc"
      sql_setdlist[0].sqldata = (void*)kntno;
#line 247 "A205zoku.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 247 "A205zoku.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 4;
#line 247 "A205zoku.sqc"
      sql_setdlist[1].sqldata = (void*)knsgslbcd;
#line 247 "A205zoku.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 247 "A205zoku.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 247 "A205zoku.sqc"
      sql_setdlist[2].sqldata = (void*)&kntzssdino;
#line 247 "A205zoku.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 247 "A205zoku.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 247 "A205zoku.sqc"
      sql_setdlist[3].sqldata = (void*)sriymd;
#line 247 "A205zoku.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 247 "A205zoku.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 247 "A205zoku.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 247 "A205zoku.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 247 "A205zoku.sqc"
  sqlastop(0L);
}

#line 247 "A205zoku.sqc"


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
#line 308 "A205zoku.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 308 "A205zoku.sqc"
  sqlaaloc(3,56,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[56];
#line 308 "A205zoku.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 308 "A205zoku.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 308 "A205zoku.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 308 "A205zoku.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 308 "A205zoku.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 308 "A205zoku.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 308 "A205zoku.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 308 "A205zoku.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 308 "A205zoku.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 308 "A205zoku.sqc"
      sql_setdlist[4].sqldata = (void*)sriymd;
#line 308 "A205zoku.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 14;
#line 308 "A205zoku.sqc"
      sql_setdlist[5].sqldata = (void*)kntno;
#line 308 "A205zoku.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 308 "A205zoku.sqc"
      sql_setdlist[6].sqldata = (void*)&kntketflg;
#line 308 "A205zoku.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 4;
#line 308 "A205zoku.sqc"
      sql_setdlist[7].sqldata = (void*)knsgslbcd;
#line 308 "A205zoku.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 308 "A205zoku.sqc"
      sql_setdlist[8].sqldata = (void*)&kntzssdino;
#line 308 "A205zoku.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 308 "A205zoku.sqc"
      sql_setdlist[9].sqldata = (void*)knttcyymd;
#line 308 "A205zoku.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 3;
#line 308 "A205zoku.sqc"
      sql_setdlist[10].sqldata = (void*)fszrgrp;
#line 308 "A205zoku.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 6;
#line 308 "A205zoku.sqc"
      sql_setdlist[11].sqldata = (void*)irikntryo;
#line 308 "A205zoku.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[12].sqltype = 452; sql_setdlist[12].sqllen = 1;
#line 308 "A205zoku.sqc"
      sql_setdlist[12].sqldata = (void*)&irikntryotni;
#line 308 "A205zoku.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 6;
#line 308 "A205zoku.sqc"
      sql_setdlist[13].sqldata = (void*)gnkntryo;
#line 308 "A205zoku.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 308 "A205zoku.sqc"
      sql_setdlist[14].sqldata = (void*)&gnkntryotni;
#line 308 "A205zoku.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 5;
#line 308 "A205zoku.sqc"
      sql_setdlist[15].sqldata = (void*)chkmj;
#line 308 "A205zoku.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 3;
#line 308 "A205zoku.sqc"
      sql_setdlist[16].sqldata = (void*)rucd;
#line 308 "A205zoku.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 21;
#line 308 "A205zoku.sqc"
      sql_setdlist[17].sqldata = (void*)ykcd;
#line 308 "A205zoku.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 308 "A205zoku.sqc"
      sql_setdlist[18].sqldata = (void*)&htkfkiri;
#line 308 "A205zoku.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 308 "A205zoku.sqc"
      sql_setdlist[19].sqldata = (void*)&ysnflg;
#line 308 "A205zoku.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 308 "A205zoku.sqc"
      sql_setdlist[20].sqldata = (void*)&kntfrflg;
#line 308 "A205zoku.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 4;
#line 308 "A205zoku.sqc"
      sql_setdlist[21].sqldata = (void*)ykzrcd;
#line 308 "A205zoku.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 4;
#line 308 "A205zoku.sqc"
      sql_setdlist[22].sqldata = (void*)hzzrcd;
#line 308 "A205zoku.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 308 "A205zoku.sqc"
      sql_setdlist[23].sqldata = (void*)&kntjtflg;
#line 308 "A205zoku.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 308 "A205zoku.sqc"
      sql_setdlist[24].sqldata = (void*)&knttktkbn;
#line 308 "A205zoku.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 308 "A205zoku.sqc"
      sql_setdlist[25].sqldata = (void*)&hbncflg;
#line 308 "A205zoku.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 308 "A205zoku.sqc"
      sql_setdlist[26].sqldata = (void*)&kntzsssflg;
#line 308 "A205zoku.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 27;
#line 308 "A205zoku.sqc"
      sql_setdlist[27].sqldata = (void*)kntzstrdh;
#line 308 "A205zoku.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 27;
#line 308 "A205zoku.sqc"
      sql_setdlist[28].sqldata = (void*)kntzsssdh;
#line 308 "A205zoku.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 308 "A205zoku.sqc"
      sql_setdlist[29].sqldata = (void*)stlkntzsssdh;
#line 308 "A205zoku.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 16;
#line 308 "A205zoku.sqc"
      sql_setdlist[30].sqldata = (void*)stlkntzsssip;
#line 308 "A205zoku.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 9;
#line 308 "A205zoku.sqc"
      sql_setdlist[31].sqldata = (void*)stlkntzssssyaid;
#line 308 "A205zoku.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 308 "A205zoku.sqc"
      sql_setdlist[32].sqldata = (void*)&sklblflg;
#line 308 "A205zoku.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 4;
#line 308 "A205zoku.sqc"
      sql_setdlist[33].sqldata = (void*)zrcd;
#line 308 "A205zoku.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 9;
#line 308 "A205zoku.sqc"
      sql_setdlist[34].sqldata = (void*)sstme;
#line 308 "A205zoku.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 11;
#line 308 "A205zoku.sqc"
      sql_setdlist[35].sqldata = (void*)ssymd;
#line 308 "A205zoku.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 5;
#line 308 "A205zoku.sqc"
      sql_setdlist[36].sqldata = (void*)tntme;
#line 308 "A205zoku.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 308 "A205zoku.sqc"
      sql_setdlist[37].sqldata = (void*)&tntni;
#line 308 "A205zoku.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 6;
#line 308 "A205zoku.sqc"
      sql_setdlist[38].sqldata = (void*)tnryo;
#line 308 "A205zoku.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 308 "A205zoku.sqc"
      sql_setdlist[39].sqldata = (void*)&tnryotni;
#line 308 "A205zoku.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 21;
#line 308 "A205zoku.sqc"
      sql_setdlist[40].sqldata = (void*)ssbi;
#line 308 "A205zoku.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 21;
#line 308 "A205zoku.sqc"
      sql_setdlist[41].sqldata = (void*)sshhu;
#line 308 "A205zoku.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 3;
#line 308 "A205zoku.sqc"
      sql_setdlist[42].sqldata = (void*)hkflg;
#line 308 "A205zoku.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 11;
#line 308 "A205zoku.sqc"
      sql_setdlist[43].sqldata = (void*)msriymd;
#line 308 "A205zoku.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 14;
#line 308 "A205zoku.sqc"
      sql_setdlist[44].sqldata = (void*)mkntno;
#line 308 "A205zoku.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 11;
#line 308 "A205zoku.sqc"
      sql_setdlist[45].sqldata = (void*)id2;
#line 308 "A205zoku.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[46].sqltype = 500; sql_setdlist[46].sqllen = 2;
#line 308 "A205zoku.sqc"
      sql_setdlist[46].sqldata = (void*)&id2pos;
#line 308 "A205zoku.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 11;
#line 308 "A205zoku.sqc"
      sql_setdlist[47].sqldata = (void*)id3;
#line 308 "A205zoku.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[48].sqltype = 500; sql_setdlist[48].sqllen = 2;
#line 308 "A205zoku.sqc"
      sql_setdlist[48].sqldata = (void*)&id3pos;
#line 308 "A205zoku.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 11;
#line 308 "A205zoku.sqc"
      sql_setdlist[49].sqldata = (void*)sntrno;
#line 308 "A205zoku.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 11;
#line 308 "A205zoku.sqc"
      sql_setdlist[50].sqldata = (void*)sntnno;
#line 308 "A205zoku.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[51].sqltype = 452; sql_setdlist[51].sqllen = 1;
#line 308 "A205zoku.sqc"
      sql_setdlist[51].sqldata = (void*)&nstsgflg;
#line 308 "A205zoku.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[52].sqltype = 452; sql_setdlist[52].sqllen = 1;
#line 308 "A205zoku.sqc"
      sql_setdlist[52].sqldata = (void*)&hknjk;
#line 308 "A205zoku.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 27;
#line 308 "A205zoku.sqc"
      sql_setdlist[53].sqldata = (void*)hknjkksndh;
#line 308 "A205zoku.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 27;
#line 308 "A205zoku.sqc"
      sql_setdlist[54].sqldata = (void*)ksndh;
#line 308 "A205zoku.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 27;
#line 308 "A205zoku.sqc"
      sql_setdlist[55].sqldata = (void*)trkdh;
#line 308 "A205zoku.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 308 "A205zoku.sqc"
      sqlasetdata(3,0,56,sql_setdlist,0L,0L);
    }
#line 308 "A205zoku.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 308 "A205zoku.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 308 "A205zoku.sqc"
  sqlastop(0L);
}

#line 308 "A205zoku.sqc"


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
#line 323 "A205zoku.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 323 "A205zoku.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 323 "A205zoku.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 323 "A205zoku.sqc"
  sqlastop(0L);
}

#line 323 "A205zoku.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 331 "A205zoku.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * AdbKzokInsert()
 *    KENZOK レコードを挿入する
 * ■引数
 *    [I]  Kenzok* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long AZokuInsert( Kenzok* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KenzokArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 354 "A205zoku.sqc"


    
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
		CURRENT TIMESTAMP,
		CURRENT TIMESTAMP,
		CURRENT TIMESTAMP,
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
		CURRENT TIMESTAMP,
		CURRENT TIMESTAMP,
		CURRENT TIMESTAMP
    );
*/

{
#line 471 "A205zoku.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 471 "A205zoku.sqc"
  sqlaaloc(2,50,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[50];
#line 471 "A205zoku.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 471 "A205zoku.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 471 "A205zoku.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 471 "A205zoku.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 471 "A205zoku.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 471 "A205zoku.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 471 "A205zoku.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 471 "A205zoku.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 471 "A205zoku.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 471 "A205zoku.sqc"
      sql_setdlist[4].sqldata = (void*)sriymd;
#line 471 "A205zoku.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 14;
#line 471 "A205zoku.sqc"
      sql_setdlist[5].sqldata = (void*)kntno;
#line 471 "A205zoku.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 471 "A205zoku.sqc"
      sql_setdlist[6].sqldata = (void*)&kntketflg;
#line 471 "A205zoku.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 4;
#line 471 "A205zoku.sqc"
      sql_setdlist[7].sqldata = (void*)knsgslbcd;
#line 471 "A205zoku.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 471 "A205zoku.sqc"
      sql_setdlist[8].sqldata = (void*)&kntzssdino;
#line 471 "A205zoku.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 471 "A205zoku.sqc"
      sql_setdlist[9].sqldata = (void*)knttcyymd;
#line 471 "A205zoku.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 3;
#line 471 "A205zoku.sqc"
      sql_setdlist[10].sqldata = (void*)fszrgrp;
#line 471 "A205zoku.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 6;
#line 471 "A205zoku.sqc"
      sql_setdlist[11].sqldata = (void*)irikntryo;
#line 471 "A205zoku.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[12].sqltype = 452; sql_setdlist[12].sqllen = 1;
#line 471 "A205zoku.sqc"
      sql_setdlist[12].sqldata = (void*)&irikntryotni;
#line 471 "A205zoku.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 6;
#line 471 "A205zoku.sqc"
      sql_setdlist[13].sqldata = (void*)gnkntryo;
#line 471 "A205zoku.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 471 "A205zoku.sqc"
      sql_setdlist[14].sqldata = (void*)&gnkntryotni;
#line 471 "A205zoku.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 5;
#line 471 "A205zoku.sqc"
      sql_setdlist[15].sqldata = (void*)chkmj;
#line 471 "A205zoku.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 3;
#line 471 "A205zoku.sqc"
      sql_setdlist[16].sqldata = (void*)rucd;
#line 471 "A205zoku.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 21;
#line 471 "A205zoku.sqc"
      sql_setdlist[17].sqldata = (void*)ykcd;
#line 471 "A205zoku.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 471 "A205zoku.sqc"
      sql_setdlist[18].sqldata = (void*)&htkfkiri;
#line 471 "A205zoku.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 471 "A205zoku.sqc"
      sql_setdlist[19].sqldata = (void*)&ysnflg;
#line 471 "A205zoku.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 471 "A205zoku.sqc"
      sql_setdlist[20].sqldata = (void*)&kntfrflg;
#line 471 "A205zoku.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 4;
#line 471 "A205zoku.sqc"
      sql_setdlist[21].sqldata = (void*)ykzrcd;
#line 471 "A205zoku.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 4;
#line 471 "A205zoku.sqc"
      sql_setdlist[22].sqldata = (void*)hzzrcd;
#line 471 "A205zoku.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 471 "A205zoku.sqc"
      sql_setdlist[23].sqldata = (void*)&kntjtflg;
#line 471 "A205zoku.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 471 "A205zoku.sqc"
      sql_setdlist[24].sqldata = (void*)&knttktkbn;
#line 471 "A205zoku.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 471 "A205zoku.sqc"
      sql_setdlist[25].sqldata = (void*)&hbncflg;
#line 471 "A205zoku.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 471 "A205zoku.sqc"
      sql_setdlist[26].sqldata = (void*)&kntzsssflg;
#line 471 "A205zoku.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 16;
#line 471 "A205zoku.sqc"
      sql_setdlist[27].sqldata = (void*)stlkntzsssip;
#line 471 "A205zoku.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 9;
#line 471 "A205zoku.sqc"
      sql_setdlist[28].sqldata = (void*)stlkntzssssyaid;
#line 471 "A205zoku.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 471 "A205zoku.sqc"
      sql_setdlist[29].sqldata = (void*)&sklblflg;
#line 471 "A205zoku.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 4;
#line 471 "A205zoku.sqc"
      sql_setdlist[30].sqldata = (void*)zrcd;
#line 471 "A205zoku.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 9;
#line 471 "A205zoku.sqc"
      sql_setdlist[31].sqldata = (void*)sstme;
#line 471 "A205zoku.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 11;
#line 471 "A205zoku.sqc"
      sql_setdlist[32].sqldata = (void*)ssymd;
#line 471 "A205zoku.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 5;
#line 471 "A205zoku.sqc"
      sql_setdlist[33].sqldata = (void*)tntme;
#line 471 "A205zoku.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 471 "A205zoku.sqc"
      sql_setdlist[34].sqldata = (void*)&tntni;
#line 471 "A205zoku.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 6;
#line 471 "A205zoku.sqc"
      sql_setdlist[35].sqldata = (void*)tnryo;
#line 471 "A205zoku.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 471 "A205zoku.sqc"
      sql_setdlist[36].sqldata = (void*)&tnryotni;
#line 471 "A205zoku.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 21;
#line 471 "A205zoku.sqc"
      sql_setdlist[37].sqldata = (void*)ssbi;
#line 471 "A205zoku.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 21;
#line 471 "A205zoku.sqc"
      sql_setdlist[38].sqldata = (void*)sshhu;
#line 471 "A205zoku.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 3;
#line 471 "A205zoku.sqc"
      sql_setdlist[39].sqldata = (void*)hkflg;
#line 471 "A205zoku.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 11;
#line 471 "A205zoku.sqc"
      sql_setdlist[40].sqldata = (void*)msriymd;
#line 471 "A205zoku.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 14;
#line 471 "A205zoku.sqc"
      sql_setdlist[41].sqldata = (void*)mkntno;
#line 471 "A205zoku.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 11;
#line 471 "A205zoku.sqc"
      sql_setdlist[42].sqldata = (void*)id2;
#line 471 "A205zoku.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[43].sqltype = 500; sql_setdlist[43].sqllen = 2;
#line 471 "A205zoku.sqc"
      sql_setdlist[43].sqldata = (void*)&id2pos;
#line 471 "A205zoku.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 11;
#line 471 "A205zoku.sqc"
      sql_setdlist[44].sqldata = (void*)id3;
#line 471 "A205zoku.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[45].sqltype = 500; sql_setdlist[45].sqllen = 2;
#line 471 "A205zoku.sqc"
      sql_setdlist[45].sqldata = (void*)&id3pos;
#line 471 "A205zoku.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 11;
#line 471 "A205zoku.sqc"
      sql_setdlist[46].sqldata = (void*)sntrno;
#line 471 "A205zoku.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 11;
#line 471 "A205zoku.sqc"
      sql_setdlist[47].sqldata = (void*)sntnno;
#line 471 "A205zoku.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 471 "A205zoku.sqc"
      sql_setdlist[48].sqldata = (void*)&nstsgflg;
#line 471 "A205zoku.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sql_setdlist[49].sqltype = 452; sql_setdlist[49].sqllen = 1;
#line 471 "A205zoku.sqc"
      sql_setdlist[49].sqldata = (void*)&hknjk;
#line 471 "A205zoku.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 471 "A205zoku.sqc"
      sqlasetdata(2,0,50,sql_setdlist,0L,0L);
    }
#line 471 "A205zoku.sqc"
  sqlacall((unsigned short)24,2,2,0,0L);
#line 471 "A205zoku.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 471 "A205zoku.sqc"
  sqlastop(0L);
}

#line 471 "A205zoku.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 476 "A205zoku.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * AZokuUpdate()
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
long AZokuUpdate( Kenzok* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KenzokArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 500 "A205zoku.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 501 "A205zoku.sqc"


    
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
		KSNDH
--		TRKDH					// 登録日時はUPDATE対象外
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
--		:kntzstrdh,				// 3.02 UPDATE ではあるがCURRENTを設定
--		:kntzsssdh,				// 3.02 UPDATE ではあるがCURRENTを設定
--		:stlkntzsssdh,			// 3.02 UPDATE ではあるがCURRENTを設定
		CURRENT TIMESTAMP,
		CURRENT TIMESTAMP,
		CURRENT TIMESTAMP,
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
--		:hknjkksndh,
--		:ksndh,
--		:trkdh
		CURRENT TIMESTAMP,
		CURRENT TIMESTAMP
--		CURRENT TIMESTAMP
    ) WHERE
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		KNSGSLBCD = :knsgslbcd AND
		KNTZSSDINO = :kntzssdino;
*/

{
#line 620 "A205zoku.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 620 "A205zoku.sqc"
  sqlaaloc(2,50,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[50];
#line 620 "A205zoku.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 620 "A205zoku.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 620 "A205zoku.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 620 "A205zoku.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 620 "A205zoku.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 620 "A205zoku.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 620 "A205zoku.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 620 "A205zoku.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 620 "A205zoku.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 620 "A205zoku.sqc"
      sql_setdlist[4].sqldata = (void*)&kntketflg;
#line 620 "A205zoku.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 620 "A205zoku.sqc"
      sql_setdlist[5].sqldata = (void*)knttcyymd;
#line 620 "A205zoku.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 3;
#line 620 "A205zoku.sqc"
      sql_setdlist[6].sqldata = (void*)fszrgrp;
#line 620 "A205zoku.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 6;
#line 620 "A205zoku.sqc"
      sql_setdlist[7].sqldata = (void*)irikntryo;
#line 620 "A205zoku.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 620 "A205zoku.sqc"
      sql_setdlist[8].sqldata = (void*)&irikntryotni;
#line 620 "A205zoku.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 6;
#line 620 "A205zoku.sqc"
      sql_setdlist[9].sqldata = (void*)gnkntryo;
#line 620 "A205zoku.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 620 "A205zoku.sqc"
      sql_setdlist[10].sqldata = (void*)&gnkntryotni;
#line 620 "A205zoku.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 5;
#line 620 "A205zoku.sqc"
      sql_setdlist[11].sqldata = (void*)chkmj;
#line 620 "A205zoku.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 3;
#line 620 "A205zoku.sqc"
      sql_setdlist[12].sqldata = (void*)rucd;
#line 620 "A205zoku.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 620 "A205zoku.sqc"
      sql_setdlist[13].sqldata = (void*)ykcd;
#line 620 "A205zoku.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 620 "A205zoku.sqc"
      sql_setdlist[14].sqldata = (void*)&htkfkiri;
#line 620 "A205zoku.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[15].sqltype = 452; sql_setdlist[15].sqllen = 1;
#line 620 "A205zoku.sqc"
      sql_setdlist[15].sqldata = (void*)&ysnflg;
#line 620 "A205zoku.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 620 "A205zoku.sqc"
      sql_setdlist[16].sqldata = (void*)&kntfrflg;
#line 620 "A205zoku.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 4;
#line 620 "A205zoku.sqc"
      sql_setdlist[17].sqldata = (void*)ykzrcd;
#line 620 "A205zoku.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 4;
#line 620 "A205zoku.sqc"
      sql_setdlist[18].sqldata = (void*)hzzrcd;
#line 620 "A205zoku.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 620 "A205zoku.sqc"
      sql_setdlist[19].sqldata = (void*)&kntjtflg;
#line 620 "A205zoku.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 620 "A205zoku.sqc"
      sql_setdlist[20].sqldata = (void*)&knttktkbn;
#line 620 "A205zoku.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 620 "A205zoku.sqc"
      sql_setdlist[21].sqldata = (void*)&hbncflg;
#line 620 "A205zoku.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 620 "A205zoku.sqc"
      sql_setdlist[22].sqldata = (void*)&kntzsssflg;
#line 620 "A205zoku.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 16;
#line 620 "A205zoku.sqc"
      sql_setdlist[23].sqldata = (void*)stlkntzsssip;
#line 620 "A205zoku.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 9;
#line 620 "A205zoku.sqc"
      sql_setdlist[24].sqldata = (void*)stlkntzssssyaid;
#line 620 "A205zoku.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 620 "A205zoku.sqc"
      sql_setdlist[25].sqldata = (void*)&sklblflg;
#line 620 "A205zoku.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 4;
#line 620 "A205zoku.sqc"
      sql_setdlist[26].sqldata = (void*)zrcd;
#line 620 "A205zoku.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 9;
#line 620 "A205zoku.sqc"
      sql_setdlist[27].sqldata = (void*)sstme;
#line 620 "A205zoku.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 11;
#line 620 "A205zoku.sqc"
      sql_setdlist[28].sqldata = (void*)ssymd;
#line 620 "A205zoku.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 5;
#line 620 "A205zoku.sqc"
      sql_setdlist[29].sqldata = (void*)tntme;
#line 620 "A205zoku.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 620 "A205zoku.sqc"
      sql_setdlist[30].sqldata = (void*)&tntni;
#line 620 "A205zoku.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 6;
#line 620 "A205zoku.sqc"
      sql_setdlist[31].sqldata = (void*)tnryo;
#line 620 "A205zoku.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 620 "A205zoku.sqc"
      sql_setdlist[32].sqldata = (void*)&tnryotni;
#line 620 "A205zoku.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 21;
#line 620 "A205zoku.sqc"
      sql_setdlist[33].sqldata = (void*)ssbi;
#line 620 "A205zoku.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 21;
#line 620 "A205zoku.sqc"
      sql_setdlist[34].sqldata = (void*)sshhu;
#line 620 "A205zoku.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 3;
#line 620 "A205zoku.sqc"
      sql_setdlist[35].sqldata = (void*)hkflg;
#line 620 "A205zoku.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 11;
#line 620 "A205zoku.sqc"
      sql_setdlist[36].sqldata = (void*)msriymd;
#line 620 "A205zoku.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 14;
#line 620 "A205zoku.sqc"
      sql_setdlist[37].sqldata = (void*)mkntno;
#line 620 "A205zoku.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 11;
#line 620 "A205zoku.sqc"
      sql_setdlist[38].sqldata = (void*)id2;
#line 620 "A205zoku.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[39].sqltype = 500; sql_setdlist[39].sqllen = 2;
#line 620 "A205zoku.sqc"
      sql_setdlist[39].sqldata = (void*)&id2pos;
#line 620 "A205zoku.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 11;
#line 620 "A205zoku.sqc"
      sql_setdlist[40].sqldata = (void*)id3;
#line 620 "A205zoku.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[41].sqltype = 500; sql_setdlist[41].sqllen = 2;
#line 620 "A205zoku.sqc"
      sql_setdlist[41].sqldata = (void*)&id3pos;
#line 620 "A205zoku.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 11;
#line 620 "A205zoku.sqc"
      sql_setdlist[42].sqldata = (void*)sntrno;
#line 620 "A205zoku.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 11;
#line 620 "A205zoku.sqc"
      sql_setdlist[43].sqldata = (void*)sntnno;
#line 620 "A205zoku.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 620 "A205zoku.sqc"
      sql_setdlist[44].sqldata = (void*)&nstsgflg;
#line 620 "A205zoku.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[45].sqltype = 452; sql_setdlist[45].sqllen = 1;
#line 620 "A205zoku.sqc"
      sql_setdlist[45].sqldata = (void*)&hknjk;
#line 620 "A205zoku.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 11;
#line 620 "A205zoku.sqc"
      sql_setdlist[46].sqldata = (void*)sriymd;
#line 620 "A205zoku.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 14;
#line 620 "A205zoku.sqc"
      sql_setdlist[47].sqldata = (void*)kntno;
#line 620 "A205zoku.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 4;
#line 620 "A205zoku.sqc"
      sql_setdlist[48].sqldata = (void*)knsgslbcd;
#line 620 "A205zoku.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sql_setdlist[49].sqltype = 500; sql_setdlist[49].sqllen = 2;
#line 620 "A205zoku.sqc"
      sql_setdlist[49].sqldata = (void*)&kntzssdino;
#line 620 "A205zoku.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 620 "A205zoku.sqc"
      sqlasetdata(2,0,50,sql_setdlist,0L,0L);
    }
#line 620 "A205zoku.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 620 "A205zoku.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 620 "A205zoku.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 620 "A205zoku.sqc"
  sqlastop(0L);
}

#line 620 "A205zoku.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 625 "A205zoku.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 629 "A205zoku.sqc"


    return sqlca.sqlcode;
}

/******************************************************************************
 * AZokuDelete()
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
long AZokuDelete( Kenzok* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KenzokArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 654 "A205zoku.sqc"


    
/*
EXEC SQL DELETE FROM KENZOK
    WHERE
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		KNSGSLBCD = :knsgslbcd AND
		KNTZSSDINO = :kntzssdino;
*/

{
#line 661 "A205zoku.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 661 "A205zoku.sqc"
  sqlaaloc(2,4,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 661 "A205zoku.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 661 "A205zoku.sqc"
      sql_setdlist[0].sqldata = (void*)sriymd;
#line 661 "A205zoku.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 661 "A205zoku.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 14;
#line 661 "A205zoku.sqc"
      sql_setdlist[1].sqldata = (void*)kntno;
#line 661 "A205zoku.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 661 "A205zoku.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 4;
#line 661 "A205zoku.sqc"
      sql_setdlist[2].sqldata = (void*)knsgslbcd;
#line 661 "A205zoku.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 661 "A205zoku.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 661 "A205zoku.sqc"
      sql_setdlist[3].sqldata = (void*)&kntzssdino;
#line 661 "A205zoku.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 661 "A205zoku.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 661 "A205zoku.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 661 "A205zoku.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 661 "A205zoku.sqc"
  sqlastop(0L);
}

#line 661 "A205zoku.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 666 "A205zoku.sqc"


    return sqlca.sqlcode;
}

/******************************************************************************
 * AZokuSelId2()
 *    KENZOK ID2/ID2POSを取得する
 * ■引数
 *    [I]  char *pSriymd        処理日
 *    [I]  char *pKntno         検体No
 *    [I]  int   iZssdino       属性世代No
 *    [O]  char *pRetId2        ID2
 *    [O]  char *pRetId2pos     ID2POS
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long AZokuSelId2( char* pSriymd, char* pKntno, int iZssdino, char* pRetId2, int* iRetId2pos )
{

	int		iCursorFlg = 0 ;

	
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 692 "A205zoku.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 693 "A205zoku.sqc"


	// 検索キー設定
	strcpy ( sriymd, pSriymd ) ;
	strcpy ( kntno,  pKntno ) ;
	zssdino = iZssdino ;

	// 検索結果設定
	memset(id2, 0, sizeof(id2)) ;
	id2pos = *iRetId2pos ;

	
/*
EXEC SQL DECLARE c_zok_id2 CURSOR FOR
	SELECT
		ID2,
		ID2POS
	FROM
		KENZOK
	WHERE
		KNTNO  = :kntno AND
		SRIYMD = :sriymd AND
		ZSSDINO = :zssdino
	FETCH FIRST 1 ROWS ONLY
	FOR READ ONLY ;
*/

#line 715 "A205zoku.sqc"


	
/*
EXEC SQL OPEN c_zok_id2 ;
*/

{
#line 717 "A205zoku.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 717 "A205zoku.sqc"
  sqlaaloc(2,3,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 717 "A205zoku.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 14;
#line 717 "A205zoku.sqc"
      sql_setdlist[0].sqldata = (void*)kntno;
#line 717 "A205zoku.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 717 "A205zoku.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 717 "A205zoku.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 717 "A205zoku.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 717 "A205zoku.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 717 "A205zoku.sqc"
      sql_setdlist[2].sqldata = (void*)&zssdino;
#line 717 "A205zoku.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 717 "A205zoku.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 717 "A205zoku.sqc"
  sqlacall((unsigned short)26,5,2,0,0L);
#line 717 "A205zoku.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 717 "A205zoku.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 717 "A205zoku.sqc"
  sqlastop(0L);
}

#line 717 "A205zoku.sqc"

	iCursorFlg = 1 ;

	
/*
EXEC SQL FETCH c_zok_id2 INTO :id2, :id2pos ;
*/

{
#line 720 "A205zoku.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 720 "A205zoku.sqc"
  sqlaaloc(3,2,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 720 "A205zoku.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 720 "A205zoku.sqc"
      sql_setdlist[0].sqldata = (void*)id2;
#line 720 "A205zoku.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 720 "A205zoku.sqc"
      sql_setdlist[1].sqltype = 500; sql_setdlist[1].sqllen = 2;
#line 720 "A205zoku.sqc"
      sql_setdlist[1].sqldata = (void*)&id2pos;
#line 720 "A205zoku.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 720 "A205zoku.sqc"
      sqlasetdata(3,0,2,sql_setdlist,0L,0L);
    }
#line 720 "A205zoku.sqc"
  sqlacall((unsigned short)25,5,0,3,0L);
#line 720 "A205zoku.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 720 "A205zoku.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 720 "A205zoku.sqc"
  sqlastop(0L);
}

#line 720 "A205zoku.sqc"


	
/*
EXEC SQL CLOSE c_zok_id2 ;
*/

{
#line 722 "A205zoku.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 722 "A205zoku.sqc"
  sqlacall((unsigned short)20,5,0,0,0L);
#line 722 "A205zoku.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 722 "A205zoku.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 722 "A205zoku.sqc"
  sqlastop(0L);
}

#line 722 "A205zoku.sqc"


	memcpy(pRetId2, id2, sizeof(id2));
	*iRetId2pos = id2pos ;

	return HRC_SQL_NORMAL ;

notfound:
	
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 730 "A205zoku.sqc"


	sFncPutLog ( TRCKIND_TRACE, __FILE__, "AZokuSelId2	", __LINE__, EXEFLG_SEL, "00000000",
				 "NOT FOUND CONTINUE" );

	// カーソルがオープンされている場合、クローズする
	if ( iCursorFlg )
	{
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "AZokuSelId2	", __LINE__, EXEFLG_SEL, "00000000",
					 "CURSOR CLOSE BEFORE (NOT FOUND)" );

		
/*
EXEC SQL CLOSE c_zok_id2 ;
*/

{
#line 741 "A205zoku.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 741 "A205zoku.sqc"
  sqlacall((unsigned short)20,5,0,0,0L);
#line 741 "A205zoku.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 741 "A205zoku.sqc"
  sqlastop(0L);
}

#line 741 "A205zoku.sqc"


		sFncPutLog ( TRCKIND_TRACE, __FILE__, "AZokuSelId2	", __LINE__, EXEFLG_SEL, "00000000",
					 "CURSOR CLOSE AFTER (NOT FOUND)" );
	}

	return HRC_SQL_NOT_FOUND;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 750 "A205zoku.sqc"


	sFncPutLog ( TRCKIND_TRACE, __FILE__, "AZokuSelId2	", __LINE__, EXEFLG_SEL, "00000000",
				 "SQLERROR CONTINUE" );

	// カーソルがオープンされている場合、クローズする
	if ( iCursorFlg )
	{
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "AZokuSelId2	", __LINE__, EXEFLG_SEL, "00000000",
					 "CURSOR CLOSE BEFORE (SQLERROR)" );

		
/*
EXEC SQL CLOSE c_zok_id2 ;
*/

{
#line 761 "A205zoku.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 761 "A205zoku.sqc"
  sqlacall((unsigned short)20,5,0,0,0L);
#line 761 "A205zoku.sqc"
  sqlastop(0L);
}

#line 761 "A205zoku.sqc"


		sFncPutLog ( TRCKIND_TRACE, __FILE__, "AZokuSelId2	", __LINE__, EXEFLG_SEL, "00000000",
					 "CURSOR CLOSE AFTER (SQLERROR)" );
	}

	return sqlca.sqlcode;
}
/** End of File *********************************************************/
