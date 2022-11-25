static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,106,65,70,52,85,97,68,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,54,71,49,48,53,32,32,32,0,0,0,0,0,0,0,0,
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


#line 1 "GD105Kenzok.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：GD105Kenzok.sqc
 *     機能概要  ：検体属性情報アクセス関数(報告処理)
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
#include "GD105Kenzok.h"
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


#line 33 "GD105Kenzok.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 38 "GD105Kenzok.sqc"

	char    utkymd[10+1];
	char    irino[11+1];
	char    iriketflg;
	short   zssdino;
	char    sriymd[10+1];
	char    kntno[13+1];
	char    kntketflg;
	char    knsgslbcd[3+1];
	short   kntzssdino;
	char    knttcyymd[10+1];
	char    fszrgrp[2+1];
	char    irikntryo[5+1];
	char    irikntryotni;
	char    gnkntryo[5+1];
	char    gnkntryotni;
	char    chkmj[4+1];
	char    rucd[2+1];
	char    ykcd[20+1];
	char    htkfkiri;
	char    ysnflg;
	char    kntfrflg;
	char    ykzrcd[4+1];
	char    hzzrcd[4+1];
	char    kntjtflg;
	char    knttktkbn;
	char    hbncflg;
	char    kntzsssflg;
	char    kntzstrdh[26+1];
	char    kntzsssdh[26+1];
	char    stlkntzsssdh[26+1];
	char    stlkntzsssip[15+1];
	char    stlkntzssssyaid[8+1];
	char    sklblflg;
	char    zrcd[4+1];
	char    sstme[8+1];
	char    ssymd[10+1];
	char    tntme[4+1];
	char    tntni;
	char    tnryo[5+1];
	char    tnryotni;
	char    ssbi[20+1];
	char    sshhu[20+1];
	char    hkflg[2+1];
	char    msriymd[10+1];
	char    mkntno[13+1];
	char    id2[10+1];
	short   id2pos;
	char    id3[10+1];
	short   id3pos;
	char    sntrno[10+1];
	char    sntnno[10+1];
	char    nstsgflg;
	char    hknjk;
	char    hknjkksndh[26+1];
	char    ksndh[26+1];
	char	trkdh[26+1];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 95 "GD105Kenzok.sqc"



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
 * dGD105_KENZOK_Sel_latestZSSDINO()
 *    KENZOK レコードKey条件取得
 * ■引数
 *    [I]    Kenzok*  pKey          取得するレコードのキー
 *    [O]    Kenzok** arrayOut      取得レコード配列格納領域
 *    [O]    int* numOut            取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL(0)      正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND(100) レコードなし
 *           HRC_SQL_ERR(-2)        DBエラー
 ******************************************************************************/
long dGD105_KENZOK_Sel_latestZSSDINO( Kenzok* pKey, Kenzok** arrayOut, int* numOut )
{
	Kenzok*		array = NULL;
	int			num = 0;
	int			error = 0;

	if( !pKey ) {
		return HRC_NULL_POINTER;
	}

	if( !ZbmlMapStructToHost( (char*)pKey, KenzokArray ) ) {
		return HRC_INVALID_VALUE;
	}

	// リトライ用ループ設定
	int i;
	for (i = 0; i <= RETRY; i++) {
		error = 0;

		
/*
EXEC SQL DECLARE cur_kenzok CURSOR FOR
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
			KNTNO = :kntno
		ORDER BY
			ZSSDINO DESC
		FETCH FIRST 1 ROWS ONLY
		FOR READ ONLY;
*/

#line 260 "GD105Kenzok.sqc"


		
/*
EXEC SQL OPEN cur_kenzok;
*/

{
#line 262 "GD105Kenzok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 262 "GD105Kenzok.sqc"
  sqlaaloc(2,2,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 262 "GD105Kenzok.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 262 "GD105Kenzok.sqc"
      sql_setdlist[0].sqldata = (void*)sriymd;
#line 262 "GD105Kenzok.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 262 "GD105Kenzok.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 14;
#line 262 "GD105Kenzok.sqc"
      sql_setdlist[1].sqldata = (void*)kntno;
#line 262 "GD105Kenzok.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 262 "GD105Kenzok.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 262 "GD105Kenzok.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 262 "GD105Kenzok.sqc"
  sqlastop(0L);
}

#line 262 "GD105Kenzok.sqc"


		while( 1 ) {
			Kenzok* rec;

			
/*
EXEC SQL FETCH cur_kenzok INTO
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
#line 323 "GD105Kenzok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 323 "GD105Kenzok.sqc"
  sqlaaloc(3,56,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[56];
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[4].sqldata = (void*)sriymd;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 14;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[5].sqldata = (void*)kntno;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[6].sqldata = (void*)&kntketflg;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 4;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[7].sqldata = (void*)knsgslbcd;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[8].sqldata = (void*)&kntzssdino;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[9].sqldata = (void*)knttcyymd;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 3;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[10].sqldata = (void*)fszrgrp;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 6;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[11].sqldata = (void*)irikntryo;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[12].sqltype = 452; sql_setdlist[12].sqllen = 1;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[12].sqldata = (void*)&irikntryotni;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 6;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[13].sqldata = (void*)gnkntryo;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[14].sqldata = (void*)&gnkntryotni;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 5;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[15].sqldata = (void*)chkmj;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 3;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[16].sqldata = (void*)rucd;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 21;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[17].sqldata = (void*)ykcd;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[18].sqldata = (void*)&htkfkiri;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[19].sqldata = (void*)&ysnflg;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[20].sqldata = (void*)&kntfrflg;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 5;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[21].sqldata = (void*)ykzrcd;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 5;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[22].sqldata = (void*)hzzrcd;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[23].sqldata = (void*)&kntjtflg;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[24].sqldata = (void*)&knttktkbn;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[25].sqldata = (void*)&hbncflg;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[26].sqldata = (void*)&kntzsssflg;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 27;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[27].sqldata = (void*)kntzstrdh;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 27;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[28].sqldata = (void*)kntzsssdh;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[29].sqldata = (void*)stlkntzsssdh;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 16;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[30].sqldata = (void*)stlkntzsssip;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 9;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[31].sqldata = (void*)stlkntzssssyaid;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[32].sqldata = (void*)&sklblflg;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 5;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[33].sqldata = (void*)zrcd;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 9;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[34].sqldata = (void*)sstme;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 11;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[35].sqldata = (void*)ssymd;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 5;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[36].sqldata = (void*)tntme;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[37].sqldata = (void*)&tntni;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 6;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[38].sqldata = (void*)tnryo;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[39].sqldata = (void*)&tnryotni;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 21;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[40].sqldata = (void*)ssbi;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 21;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[41].sqldata = (void*)sshhu;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 3;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[42].sqldata = (void*)hkflg;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 11;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[43].sqldata = (void*)msriymd;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 14;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[44].sqldata = (void*)mkntno;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 11;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[45].sqldata = (void*)id2;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[46].sqltype = 500; sql_setdlist[46].sqllen = 2;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[46].sqldata = (void*)&id2pos;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 11;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[47].sqldata = (void*)id3;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[48].sqltype = 500; sql_setdlist[48].sqllen = 2;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[48].sqldata = (void*)&id3pos;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 11;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[49].sqldata = (void*)sntrno;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 11;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[50].sqldata = (void*)sntnno;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[51].sqltype = 452; sql_setdlist[51].sqllen = 1;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[51].sqldata = (void*)&nstsgflg;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[52].sqltype = 452; sql_setdlist[52].sqllen = 1;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[52].sqldata = (void*)&hknjk;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 27;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[53].sqldata = (void*)hknjkksndh;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 27;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[54].sqldata = (void*)ksndh;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 27;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[55].sqldata = (void*)trkdh;
#line 323 "GD105Kenzok.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 323 "GD105Kenzok.sqc"
      sqlasetdata(3,0,56,sql_setdlist,0L,0L);
    }
#line 323 "GD105Kenzok.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 323 "GD105Kenzok.sqc"
  sqlastop(0L);
}

#line 323 "GD105Kenzok.sqc"


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
				sFncPutLog( TRCKIND_ERROR, __FILE__, "dGD105_KENZOK_Sel_latestZSSDINO", __LINE__, EXEFLG_SEL, "020",
							"DBエラー発生 [sqlcode : %d]", sqlca.sqlcode ) ;
				break;
			}

			if( num % ALLOC_UNIT == 0 ) {
				array = (Kenzok*)ZbmlRealloc( array, sizeof( Kenzok ) * ( num + ALLOC_UNIT ) );
				memset( array + num, 0, sizeof( Kenzok ) * ALLOC_UNIT );
			}

			rec = array + num++;
			ZbmlMapHostToStruct( (char*)rec, KenzokArray );
		}

		
/*
EXEC SQL CLOSE cur_kenzok;
*/

{
#line 352 "GD105Kenzok.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 352 "GD105Kenzok.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 352 "GD105Kenzok.sqc"
  sqlastop(0L);
}

#line 352 "GD105Kenzok.sqc"

	
		// ロック時のリトライ対応
		// ロックの場合はリトライ、ロック以外のエラーはデータ無しで終了
		// リトライは５秒待ってから
		if (error == ERR_LOCK) {
			sFncPutLog( TRCKIND_ERROR, __FILE__, "dGD105_KENZOK_Sel_latestZSSDINO", __LINE__, EXEFLG_SEL, "020",
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
