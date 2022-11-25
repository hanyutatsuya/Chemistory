static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,98,66,107,85,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,65,50,48,53,73,82,65,73,0,0,0,0,0,0,0,0,
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


#line 1 "A205irai.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： A205irai.sqc
 *     機能概要  ：依頼情報テーブルアクセス(分注展開用)
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-13                    Create
 *  2.00     2009-01-07     Merits K.Ameno 施設コード増桁 通信仕様変更対応
 **********************************************************************/

/********************************************************************/
/*  インクルード宣言                                                */
/********************************************************************/
#include <stdio.h>

#include "A205irai.h"
#include "bml_misc.h"
#include "bml_db.h"
#include "bml_dmm.h"

// add 20070521 waj ロック対応
#include "bmllog.h"
#define RETRY           3
#define ERR_LOCK        -911
#define LOCK_WAIT_SEC   5	// 単位：秒

#define ALLOC_UNIT		1


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 35 "A205irai.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 40 "A205irai.sqc"

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
	char    trkdh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 90 "A205irai.sqc"



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
 * ABunIriSel()
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
long ABunIriSel( Irai* pKey, Irai** arrayOut, int* numOut )
{
    Irai*       array = NULL;
    int         num = 0;
	// add 20070521 waj ロック対応
	int         error = 0;


    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, IraiArray ) )
        return HRC_INVALID_VALUE;

/*** ameno ***/
	sFncPutLog ( TRCKIND_WARNING, __FILE__, "ABunIriSel", __LINE__,
		EXEFLG_NON, "00000000",
		"依頼SELECT 受付日(%s) 依頼書No(%s) 属性世代No(%d)", utkymd, irino, zssdino );
/*** ameno ***/

	// del 20070521 waj リトライを行うため割込みを禁止する
	//                  FETCHでエラーが発生するとCLOSEが実行されない
    // EXEC SQL WHENEVER SQLERROR GO TO error;

	// add 20070521 waj リトライ用ループ設定
	int i;
	for (i = 0; i <= RETRY; i++) {
		error = 0;

	    
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
			IRINO = :irino AND
			ZSSDINO = :zssdino AND
			UTKYMD = :utkymd
			FOR READ ONLY;
*/

#line 249 "A205irai.sqc"


	    
/*
EXEC SQL OPEN c2;
*/

{
#line 251 "A205irai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 251 "A205irai.sqc"
  sqlaaloc(2,3,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 251 "A205irai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 12;
#line 251 "A205irai.sqc"
      sql_setdlist[0].sqldata = (void*)irino;
#line 251 "A205irai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 251 "A205irai.sqc"
      sql_setdlist[1].sqltype = 500; sql_setdlist[1].sqllen = 2;
#line 251 "A205irai.sqc"
      sql_setdlist[1].sqldata = (void*)&zssdino;
#line 251 "A205irai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 251 "A205irai.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 251 "A205irai.sqc"
      sql_setdlist[2].sqldata = (void*)utkymd;
#line 251 "A205irai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 251 "A205irai.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 251 "A205irai.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 251 "A205irai.sqc"
  sqlastop(0L);
}

#line 251 "A205irai.sqc"


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
#line 305 "A205irai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 305 "A205irai.sqc"
  sqlaaloc(3,49,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[49];
#line 305 "A205irai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 305 "A205irai.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 305 "A205irai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 305 "A205irai.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 305 "A205irai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 305 "A205irai.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 305 "A205irai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 305 "A205irai.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 305 "A205irai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 305 "A205irai.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 305 "A205irai.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 305 "A205irai.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 305 "A205irai.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 305 "A205irai.sqc"
      sql_setdlist[6].sqldata = (void*)&irihsmkbn;
#line 305 "A205irai.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 305 "A205irai.sqc"
      sql_setdlist[7].sqldata = (void*)&irikbn;
#line 305 "A205irai.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 305 "A205irai.sqc"
      sql_setdlist[8].sqldata = (void*)&ksktkbn;
#line 305 "A205irai.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 305 "A205irai.sqc"
      sql_setdlist[9].sqldata = (void*)sriymd;
#line 305 "A205irai.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 14;
#line 305 "A205irai.sqc"
      sql_setdlist[10].sqldata = (void*)kntno;
#line 305 "A205irai.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 305 "A205irai.sqc"
      sql_setdlist[11].sqldata = (void*)&kntketflg;
#line 305 "A205irai.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 5;
#line 305 "A205irai.sqc"
      sql_setdlist[12].sqldata = (void*)chkmj;
#line 305 "A205irai.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 5;
#line 305 "A205irai.sqc"
      sql_setdlist[13].sqldata = (void*)stsrcd;
#line 305 "A205irai.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 17;
#line 305 "A205irai.sqc"
      sql_setdlist[14].sqldata = (void*)kmkrs;
#line 305 "A205irai.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 305 "A205irai.sqc"
      sql_setdlist[15].sqldata = (void*)oyakmkcd;
#line 305 "A205irai.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 8;
#line 305 "A205irai.sqc"
      sql_setdlist[16].sqldata = (void*)smpcd;
#line 305 "A205irai.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 8;
#line 305 "A205irai.sqc"
      sql_setdlist[17].sqldata = (void*)setkmkcd;
#line 305 "A205irai.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 305 "A205irai.sqc"
      sql_setdlist[18].sqldata = (void*)&srinycd;
#line 305 "A205irai.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 3;
#line 305 "A205irai.sqc"
      sql_setdlist[19].sqldata = (void*)seccd;
#line 305 "A205irai.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 305 "A205irai.sqc"
      sql_setdlist[20].sqldata = (void*)&skchkflg;
#line 305 "A205irai.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 305 "A205irai.sqc"
      sql_setdlist[21].sqldata = (void*)&bkfkkbn;
#line 305 "A205irai.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 3;
#line 305 "A205irai.sqc"
      sql_setdlist[22].sqldata = (void*)ysnlbl;
#line 305 "A205irai.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 305 "A205irai.sqc"
      sql_setdlist[23].sqldata = (void*)&skflg;
#line 305 "A205irai.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 305 "A205irai.sqc"
      sql_setdlist[24].sqldata = (void*)&tkflg;
#line 305 "A205irai.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 305 "A205irai.sqc"
      sql_setdlist[25].sqldata = (void*)&sjflg;
#line 305 "A205irai.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 305 "A205irai.sqc"
      sql_setdlist[26].sqldata = (void*)&jktkflg;
#line 305 "A205irai.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 4;
#line 305 "A205irai.sqc"
      sql_setdlist[27].sqldata = (void*)kjno;
#line 305 "A205irai.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 305 "A205irai.sqc"
      sql_setdlist[28].sqldata = (void*)&fkhkknohjkbn;
#line 305 "A205irai.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 4;
#line 305 "A205irai.sqc"
      sql_setdlist[29].sqldata = (void*)tbkjno;
#line 305 "A205irai.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 305 "A205irai.sqc"
      sql_setdlist[30].sqldata = (void*)&tbkjflg;
#line 305 "A205irai.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 25;
#line 305 "A205irai.sqc"
      sql_setdlist[31].sqldata = (void*)htkfkhms;
#line 305 "A205irai.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 305 "A205irai.sqc"
      sql_setdlist[32].sqldata = (void*)tskflg;
#line 305 "A205irai.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 305 "A205irai.sqc"
      sql_setdlist[33].sqldata = (void*)tktflg;
#line 305 "A205irai.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 305 "A205irai.sqc"
      sql_setdlist[34].sqldata = (void*)&bnckbn;
#line 305 "A205irai.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 305 "A205irai.sqc"
      sql_setdlist[35].sqldata = (void*)&nbnckbn;
#line 305 "A205irai.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 11;
#line 305 "A205irai.sqc"
      sql_setdlist[36].sqldata = (void*)knskisyymd;
#line 305 "A205irai.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 11;
#line 305 "A205irai.sqc"
      sql_setdlist[37].sqldata = (void*)knskryymd;
#line 305 "A205irai.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 9;
#line 305 "A205irai.sqc"
      sql_setdlist[38].sqldata = (void*)knskrytme;
#line 305 "A205irai.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 305 "A205irai.sqc"
      sql_setdlist[39].sqldata = (void*)&kkhkkflg;
#line 305 "A205irai.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 305 "A205irai.sqc"
      sql_setdlist[40].sqldata = (void*)&kkiriflg;
#line 305 "A205irai.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[41].sqltype = 500; sql_setdlist[41].sqllen = 2;
#line 305 "A205irai.sqc"
      sql_setdlist[41].sqldata = (void*)&kkirilotno;
#line 305 "A205irai.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 5;
#line 305 "A205irai.sqc"
      sql_setdlist[42].sqldata = (void*)kktoutkid;
#line 305 "A205irai.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[43].sqltype = 500; sql_setdlist[43].sqllen = 2;
#line 305 "A205irai.sqc"
      sql_setdlist[43].sqldata = (void*)&knssu;
#line 305 "A205irai.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 305 "A205irai.sqc"
      sql_setdlist[44].sqldata = (void*)&odrssflg;
#line 305 "A205irai.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 16;
#line 305 "A205irai.sqc"
      sql_setdlist[45].sqldata = (void*)ytiksbr;
#line 305 "A205irai.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 305 "A205irai.sqc"
      sql_setdlist[46].sqldata = (void*)&hhkjkflg;
#line 305 "A205irai.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 27;
#line 305 "A205irai.sqc"
      sql_setdlist[47].sqldata = (void*)ksndh;
#line 305 "A205irai.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 305 "A205irai.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 27;
#line 305 "A205irai.sqc"
      sql_setdlist[48].sqldata = (void*)trkdh;
#line 305 "A205irai.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 305 "A205irai.sqc"
      sqlasetdata(3,0,49,sql_setdlist,0L,0L);
    }
#line 305 "A205irai.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 305 "A205irai.sqc"
  sqlastop(0L);
}

#line 305 "A205irai.sqc"

	
	        if( SQLCODE == 100 )
	            break;
	
			// add 20070521 waj ロック時のリトライ対応
			if (sqlca.sqlcode < 0) {
				// エラー発生時は領域解放してブレイク
				if (array != NULL) {
					ZbmlFree(array);
					array = NULL;
					num   = 0;
				}
				error = sqlca.sqlcode;
                sFncPutLog ( TRCKIND_ERROR, __FILE__, "ABunIriSel", __LINE__,
                             EXEFLG_NON, "020", "DBエラー発生 [sqlcode : %d]", sqlca.sqlcode ) ;
				break;
			}

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
#line 334 "A205irai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 334 "A205irai.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 334 "A205irai.sqc"
  sqlastop(0L);
}

#line 334 "A205irai.sqc"

	
		// add 20070521 waj ロック時のリトライ対応
		//                  ロックの場合はリトライ、ロック以外のエラーはデータ無しで終了
		//                  リトライは５秒待ってから
		if (error == ERR_LOCK) {
            sFncPutLog ( TRCKIND_ERROR, __FILE__, "ABunIriSel", __LINE__,
                         EXEFLG_NON, "020", "ロックによるリトライ[%d]回目", i ) ;
			sleep(LOCK_WAIT_SEC);
			continue;
		}

	    *arrayOut = array;
	    *numOut   = num;
	
	    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;
	
	// add 20070521 waj リトライ用ループ終端
	}

    // add 20070521 waj リトライしてもエラーの場合、データ無しで終了
	*arrayOut = NULL;
	*numOut   = 0;
    return HRC_SQL_NOT_FOUND;

// del 20070521 waj リトライを行うため割込みを禁止する
// error:
//     EXEC SQL WHENEVER SQLERROR CONTINUE;
//     return sqlca.sqlcode;
}

/******************************************************************************
 * ABunKnsgrpUpdate()
 *    IRAIの検査グループを更新する
 * ■引数
 *    [I]  Irai* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ABunKnsgrpUpdate( Irai* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, IraiArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 385 "A205irai.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 386 "A205irai.sqc"


    
/*
EXEC SQL UPDATE IRAI
    SET (
		KNSGRP,
		ODRSSFLG,
		SRINYCD,
		KNSKISYYMD,
		KJNO,
		KSNDH
    ) = (
		:knsgrp,
		:odrssflg,
		:srinycd,
		:knskisyymd,
		:kjno,
		CURRENT TIMESTAMP
    ) WHERE
		IRINO = :irino AND
		ZSSDINO = :zssdino AND
		KMKCD = :kmkcd AND
		UTKYMD = :utkymd;
*/

{
#line 407 "A205irai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 407 "A205irai.sqc"
  sqlaaloc(2,9,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 407 "A205irai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 407 "A205irai.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 407 "A205irai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 407 "A205irai.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 407 "A205irai.sqc"
      sql_setdlist[1].sqldata = (void*)&odrssflg;
#line 407 "A205irai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 407 "A205irai.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 407 "A205irai.sqc"
      sql_setdlist[2].sqldata = (void*)&srinycd;
#line 407 "A205irai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 407 "A205irai.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 407 "A205irai.sqc"
      sql_setdlist[3].sqldata = (void*)knskisyymd;
#line 407 "A205irai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 407 "A205irai.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 4;
#line 407 "A205irai.sqc"
      sql_setdlist[4].sqldata = (void*)kjno;
#line 407 "A205irai.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 407 "A205irai.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 12;
#line 407 "A205irai.sqc"
      sql_setdlist[5].sqldata = (void*)irino;
#line 407 "A205irai.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 407 "A205irai.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 407 "A205irai.sqc"
      sql_setdlist[6].sqldata = (void*)&zssdino;
#line 407 "A205irai.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 407 "A205irai.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 8;
#line 407 "A205irai.sqc"
      sql_setdlist[7].sqldata = (void*)kmkcd;
#line 407 "A205irai.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 407 "A205irai.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 407 "A205irai.sqc"
      sql_setdlist[8].sqldata = (void*)utkymd;
#line 407 "A205irai.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 407 "A205irai.sqc"
      sqlasetdata(2,0,9,sql_setdlist,0L,0L);
    }
#line 407 "A205irai.sqc"
  sqlacall((unsigned short)24,2,2,0,0L);
#line 407 "A205irai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 407 "A205irai.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 407 "A205irai.sqc"
  sqlastop(0L);
}

#line 407 "A205irai.sqc"


    return sqlca.sqlcode;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 412 "A205irai.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 416 "A205irai.sqc"


    return sqlca.sqlcode;
}

long A1BunKnsgrpUpdate( Irai* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, IraiArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 429 "A205irai.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 430 "A205irai.sqc"


    
/*
EXEC SQL UPDATE IRAI
    SET (
		SRIYMD,
		KNSSU,
		ODRSSFLG,
		KSNDH
    ) = (
		:sriymd,
		:knssu,
		:odrssflg,
		CURRENT TIMESTAMP
    ) WHERE
		IRINO = :irino AND
		ZSSDINO = :zssdino AND
		KNSGRP = :knsgrp		AND
		KMKCD = :kmkcd AND
		UTKYMD = :utkymd;
*/

{
#line 448 "A205irai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 448 "A205irai.sqc"
  sqlaaloc(2,8,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 448 "A205irai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 448 "A205irai.sqc"
      sql_setdlist[0].sqldata = (void*)sriymd;
#line 448 "A205irai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 448 "A205irai.sqc"
      sql_setdlist[1].sqltype = 500; sql_setdlist[1].sqllen = 2;
#line 448 "A205irai.sqc"
      sql_setdlist[1].sqldata = (void*)&knssu;
#line 448 "A205irai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 448 "A205irai.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 448 "A205irai.sqc"
      sql_setdlist[2].sqldata = (void*)&odrssflg;
#line 448 "A205irai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 448 "A205irai.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 12;
#line 448 "A205irai.sqc"
      sql_setdlist[3].sqldata = (void*)irino;
#line 448 "A205irai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 448 "A205irai.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 448 "A205irai.sqc"
      sql_setdlist[4].sqldata = (void*)&zssdino;
#line 448 "A205irai.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 448 "A205irai.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 17;
#line 448 "A205irai.sqc"
      sql_setdlist[5].sqldata = (void*)knsgrp;
#line 448 "A205irai.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 448 "A205irai.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 448 "A205irai.sqc"
      sql_setdlist[6].sqldata = (void*)kmkcd;
#line 448 "A205irai.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 448 "A205irai.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 448 "A205irai.sqc"
      sql_setdlist[7].sqldata = (void*)utkymd;
#line 448 "A205irai.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 448 "A205irai.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 448 "A205irai.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 448 "A205irai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 448 "A205irai.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 448 "A205irai.sqc"
  sqlastop(0L);
}

#line 448 "A205irai.sqc"


    return sqlca.sqlcode;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 453 "A205irai.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 457 "A205irai.sqc"


    return sqlca.sqlcode;
}
long ABunIridummy( Irai** arrayOut, int* numOut )
{
    Irai*       array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 466 "A205irai.sqc"


    
/*
EXEC SQL DECLARE c4 CURSOR FOR
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
		KSNDH
    FROM
        IRAI
    WHERE
		ODRSSFLG = 'A' AND
		KSKTKBN IN ('K','T')
		FOR READ ONLY;
*/

#line 523 "A205irai.sqc"


    
/*
EXEC SQL OPEN c4;
*/

{
#line 525 "A205irai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 525 "A205irai.sqc"
  sqlacall((unsigned short)26,4,0,0,0L);
#line 525 "A205irai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 525 "A205irai.sqc"
  sqlastop(0L);
}

#line 525 "A205irai.sqc"


    while( 1 ) {
        Irai* rec;

        
/*
EXEC SQL FETCH c4 INTO
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
			:ksndh;
*/

{
#line 578 "A205irai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 578 "A205irai.sqc"
  sqlaaloc(3,48,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[48];
#line 578 "A205irai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 578 "A205irai.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 578 "A205irai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 578 "A205irai.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 578 "A205irai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 578 "A205irai.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 578 "A205irai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 578 "A205irai.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 578 "A205irai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 578 "A205irai.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 578 "A205irai.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 578 "A205irai.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 578 "A205irai.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 578 "A205irai.sqc"
      sql_setdlist[6].sqldata = (void*)&irihsmkbn;
#line 578 "A205irai.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 578 "A205irai.sqc"
      sql_setdlist[7].sqldata = (void*)&irikbn;
#line 578 "A205irai.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 578 "A205irai.sqc"
      sql_setdlist[8].sqldata = (void*)&ksktkbn;
#line 578 "A205irai.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 578 "A205irai.sqc"
      sql_setdlist[9].sqldata = (void*)sriymd;
#line 578 "A205irai.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 14;
#line 578 "A205irai.sqc"
      sql_setdlist[10].sqldata = (void*)kntno;
#line 578 "A205irai.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 578 "A205irai.sqc"
      sql_setdlist[11].sqldata = (void*)&kntketflg;
#line 578 "A205irai.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 5;
#line 578 "A205irai.sqc"
      sql_setdlist[12].sqldata = (void*)chkmj;
#line 578 "A205irai.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 5;
#line 578 "A205irai.sqc"
      sql_setdlist[13].sqldata = (void*)stsrcd;
#line 578 "A205irai.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 17;
#line 578 "A205irai.sqc"
      sql_setdlist[14].sqldata = (void*)kmkrs;
#line 578 "A205irai.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 578 "A205irai.sqc"
      sql_setdlist[15].sqldata = (void*)oyakmkcd;
#line 578 "A205irai.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 8;
#line 578 "A205irai.sqc"
      sql_setdlist[16].sqldata = (void*)smpcd;
#line 578 "A205irai.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 8;
#line 578 "A205irai.sqc"
      sql_setdlist[17].sqldata = (void*)setkmkcd;
#line 578 "A205irai.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 578 "A205irai.sqc"
      sql_setdlist[18].sqldata = (void*)&srinycd;
#line 578 "A205irai.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 3;
#line 578 "A205irai.sqc"
      sql_setdlist[19].sqldata = (void*)seccd;
#line 578 "A205irai.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 578 "A205irai.sqc"
      sql_setdlist[20].sqldata = (void*)&skchkflg;
#line 578 "A205irai.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 578 "A205irai.sqc"
      sql_setdlist[21].sqldata = (void*)&bkfkkbn;
#line 578 "A205irai.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 3;
#line 578 "A205irai.sqc"
      sql_setdlist[22].sqldata = (void*)ysnlbl;
#line 578 "A205irai.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 578 "A205irai.sqc"
      sql_setdlist[23].sqldata = (void*)&skflg;
#line 578 "A205irai.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 578 "A205irai.sqc"
      sql_setdlist[24].sqldata = (void*)&tkflg;
#line 578 "A205irai.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 578 "A205irai.sqc"
      sql_setdlist[25].sqldata = (void*)&sjflg;
#line 578 "A205irai.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 578 "A205irai.sqc"
      sql_setdlist[26].sqldata = (void*)&jktkflg;
#line 578 "A205irai.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 4;
#line 578 "A205irai.sqc"
      sql_setdlist[27].sqldata = (void*)kjno;
#line 578 "A205irai.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 578 "A205irai.sqc"
      sql_setdlist[28].sqldata = (void*)&fkhkknohjkbn;
#line 578 "A205irai.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 4;
#line 578 "A205irai.sqc"
      sql_setdlist[29].sqldata = (void*)tbkjno;
#line 578 "A205irai.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 578 "A205irai.sqc"
      sql_setdlist[30].sqldata = (void*)&tbkjflg;
#line 578 "A205irai.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 25;
#line 578 "A205irai.sqc"
      sql_setdlist[31].sqldata = (void*)htkfkhms;
#line 578 "A205irai.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 578 "A205irai.sqc"
      sql_setdlist[32].sqldata = (void*)tskflg;
#line 578 "A205irai.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 578 "A205irai.sqc"
      sql_setdlist[33].sqldata = (void*)tktflg;
#line 578 "A205irai.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 578 "A205irai.sqc"
      sql_setdlist[34].sqldata = (void*)&bnckbn;
#line 578 "A205irai.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 578 "A205irai.sqc"
      sql_setdlist[35].sqldata = (void*)&nbnckbn;
#line 578 "A205irai.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 11;
#line 578 "A205irai.sqc"
      sql_setdlist[36].sqldata = (void*)knskisyymd;
#line 578 "A205irai.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 11;
#line 578 "A205irai.sqc"
      sql_setdlist[37].sqldata = (void*)knskryymd;
#line 578 "A205irai.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 9;
#line 578 "A205irai.sqc"
      sql_setdlist[38].sqldata = (void*)knskrytme;
#line 578 "A205irai.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 578 "A205irai.sqc"
      sql_setdlist[39].sqldata = (void*)&kkhkkflg;
#line 578 "A205irai.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 578 "A205irai.sqc"
      sql_setdlist[40].sqldata = (void*)&kkiriflg;
#line 578 "A205irai.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[41].sqltype = 500; sql_setdlist[41].sqllen = 2;
#line 578 "A205irai.sqc"
      sql_setdlist[41].sqldata = (void*)&kkirilotno;
#line 578 "A205irai.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 5;
#line 578 "A205irai.sqc"
      sql_setdlist[42].sqldata = (void*)kktoutkid;
#line 578 "A205irai.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[43].sqltype = 500; sql_setdlist[43].sqllen = 2;
#line 578 "A205irai.sqc"
      sql_setdlist[43].sqldata = (void*)&knssu;
#line 578 "A205irai.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 578 "A205irai.sqc"
      sql_setdlist[44].sqldata = (void*)&odrssflg;
#line 578 "A205irai.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 16;
#line 578 "A205irai.sqc"
      sql_setdlist[45].sqldata = (void*)ytiksbr;
#line 578 "A205irai.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 578 "A205irai.sqc"
      sql_setdlist[46].sqldata = (void*)&hhkjkflg;
#line 578 "A205irai.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 578 "A205irai.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 27;
#line 578 "A205irai.sqc"
      sql_setdlist[47].sqldata = (void*)ksndh;
#line 578 "A205irai.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 578 "A205irai.sqc"
      sqlasetdata(3,0,48,sql_setdlist,0L,0L);
    }
#line 578 "A205irai.sqc"
  sqlacall((unsigned short)25,4,0,3,0L);
#line 578 "A205irai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 578 "A205irai.sqc"
  sqlastop(0L);
}

#line 578 "A205irai.sqc"


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
EXEC SQL CLOSE c4;
*/

{
#line 593 "A205irai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 593 "A205irai.sqc"
  sqlacall((unsigned short)20,4,0,0,0L);
#line 593 "A205irai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 593 "A205irai.sqc"
  sqlastop(0L);
}

#line 593 "A205irai.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 601 "A205irai.sqc"

    return sqlca.sqlcode;
}

long A205insIrai( Irai* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, IraiArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 613 "A205irai.sqc"


    
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
#line 716 "A205irai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 716 "A205irai.sqc"
  sqlaaloc(2,47,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[47];
#line 716 "A205irai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 716 "A205irai.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 716 "A205irai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 716 "A205irai.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 716 "A205irai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 716 "A205irai.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 716 "A205irai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 716 "A205irai.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 716 "A205irai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 716 "A205irai.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 716 "A205irai.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 716 "A205irai.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 716 "A205irai.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 716 "A205irai.sqc"
      sql_setdlist[6].sqldata = (void*)&irihsmkbn;
#line 716 "A205irai.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 716 "A205irai.sqc"
      sql_setdlist[7].sqldata = (void*)&irikbn;
#line 716 "A205irai.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 716 "A205irai.sqc"
      sql_setdlist[8].sqldata = (void*)&ksktkbn;
#line 716 "A205irai.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 716 "A205irai.sqc"
      sql_setdlist[9].sqldata = (void*)sriymd;
#line 716 "A205irai.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 14;
#line 716 "A205irai.sqc"
      sql_setdlist[10].sqldata = (void*)kntno;
#line 716 "A205irai.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 716 "A205irai.sqc"
      sql_setdlist[11].sqldata = (void*)&kntketflg;
#line 716 "A205irai.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 5;
#line 716 "A205irai.sqc"
      sql_setdlist[12].sqldata = (void*)chkmj;
#line 716 "A205irai.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 5;
#line 716 "A205irai.sqc"
      sql_setdlist[13].sqldata = (void*)stsrcd;
#line 716 "A205irai.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 17;
#line 716 "A205irai.sqc"
      sql_setdlist[14].sqldata = (void*)kmkrs;
#line 716 "A205irai.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 716 "A205irai.sqc"
      sql_setdlist[15].sqldata = (void*)oyakmkcd;
#line 716 "A205irai.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 8;
#line 716 "A205irai.sqc"
      sql_setdlist[16].sqldata = (void*)smpcd;
#line 716 "A205irai.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 8;
#line 716 "A205irai.sqc"
      sql_setdlist[17].sqldata = (void*)setkmkcd;
#line 716 "A205irai.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 716 "A205irai.sqc"
      sql_setdlist[18].sqldata = (void*)&srinycd;
#line 716 "A205irai.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 3;
#line 716 "A205irai.sqc"
      sql_setdlist[19].sqldata = (void*)seccd;
#line 716 "A205irai.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 716 "A205irai.sqc"
      sql_setdlist[20].sqldata = (void*)&skchkflg;
#line 716 "A205irai.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 716 "A205irai.sqc"
      sql_setdlist[21].sqldata = (void*)&bkfkkbn;
#line 716 "A205irai.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 3;
#line 716 "A205irai.sqc"
      sql_setdlist[22].sqldata = (void*)ysnlbl;
#line 716 "A205irai.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 716 "A205irai.sqc"
      sql_setdlist[23].sqldata = (void*)&skflg;
#line 716 "A205irai.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 716 "A205irai.sqc"
      sql_setdlist[24].sqldata = (void*)&tkflg;
#line 716 "A205irai.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 716 "A205irai.sqc"
      sql_setdlist[25].sqldata = (void*)&sjflg;
#line 716 "A205irai.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 716 "A205irai.sqc"
      sql_setdlist[26].sqldata = (void*)&jktkflg;
#line 716 "A205irai.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 4;
#line 716 "A205irai.sqc"
      sql_setdlist[27].sqldata = (void*)kjno;
#line 716 "A205irai.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 716 "A205irai.sqc"
      sql_setdlist[28].sqldata = (void*)&fkhkknohjkbn;
#line 716 "A205irai.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 4;
#line 716 "A205irai.sqc"
      sql_setdlist[29].sqldata = (void*)tbkjno;
#line 716 "A205irai.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 716 "A205irai.sqc"
      sql_setdlist[30].sqldata = (void*)&tbkjflg;
#line 716 "A205irai.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 25;
#line 716 "A205irai.sqc"
      sql_setdlist[31].sqldata = (void*)htkfkhms;
#line 716 "A205irai.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 716 "A205irai.sqc"
      sql_setdlist[32].sqldata = (void*)tskflg;
#line 716 "A205irai.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 716 "A205irai.sqc"
      sql_setdlist[33].sqldata = (void*)tktflg;
#line 716 "A205irai.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 716 "A205irai.sqc"
      sql_setdlist[34].sqldata = (void*)&bnckbn;
#line 716 "A205irai.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 716 "A205irai.sqc"
      sql_setdlist[35].sqldata = (void*)&nbnckbn;
#line 716 "A205irai.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 11;
#line 716 "A205irai.sqc"
      sql_setdlist[36].sqldata = (void*)knskisyymd;
#line 716 "A205irai.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 11;
#line 716 "A205irai.sqc"
      sql_setdlist[37].sqldata = (void*)knskryymd;
#line 716 "A205irai.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 9;
#line 716 "A205irai.sqc"
      sql_setdlist[38].sqldata = (void*)knskrytme;
#line 716 "A205irai.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 716 "A205irai.sqc"
      sql_setdlist[39].sqldata = (void*)&kkhkkflg;
#line 716 "A205irai.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 716 "A205irai.sqc"
      sql_setdlist[40].sqldata = (void*)&kkiriflg;
#line 716 "A205irai.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[41].sqltype = 500; sql_setdlist[41].sqllen = 2;
#line 716 "A205irai.sqc"
      sql_setdlist[41].sqldata = (void*)&kkirilotno;
#line 716 "A205irai.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 5;
#line 716 "A205irai.sqc"
      sql_setdlist[42].sqldata = (void*)kktoutkid;
#line 716 "A205irai.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[43].sqltype = 500; sql_setdlist[43].sqllen = 2;
#line 716 "A205irai.sqc"
      sql_setdlist[43].sqldata = (void*)&knssu;
#line 716 "A205irai.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 716 "A205irai.sqc"
      sql_setdlist[44].sqldata = (void*)&odrssflg;
#line 716 "A205irai.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 16;
#line 716 "A205irai.sqc"
      sql_setdlist[45].sqldata = (void*)ytiksbr;
#line 716 "A205irai.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 716 "A205irai.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 716 "A205irai.sqc"
      sql_setdlist[46].sqldata = (void*)&hhkjkflg;
#line 716 "A205irai.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 716 "A205irai.sqc"
      sqlasetdata(2,0,47,sql_setdlist,0L,0L);
    }
#line 716 "A205irai.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 716 "A205irai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 716 "A205irai.sqc"
  sqlastop(0L);
}

#line 716 "A205irai.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 721 "A205irai.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ABunIriKmkSel()
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
long ABunIriKmkSel( Irai* pKey, Irai** arrayOut, int* numOut )
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

#line 748 "A205irai.sqc"


    
/*
EXEC SQL DECLARE c5 CURSOR FOR
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
		IRINO = :irino AND
		ZSSDINO = :zssdino AND
		UTKYMD = :utkymd AND
		KMKCD = :kmkcd
		FOR READ ONLY;
*/

#line 808 "A205irai.sqc"


    
/*
EXEC SQL OPEN c5;
*/

{
#line 810 "A205irai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 810 "A205irai.sqc"
  sqlaaloc(2,4,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 810 "A205irai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 12;
#line 810 "A205irai.sqc"
      sql_setdlist[0].sqldata = (void*)irino;
#line 810 "A205irai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 810 "A205irai.sqc"
      sql_setdlist[1].sqltype = 500; sql_setdlist[1].sqllen = 2;
#line 810 "A205irai.sqc"
      sql_setdlist[1].sqldata = (void*)&zssdino;
#line 810 "A205irai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 810 "A205irai.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 810 "A205irai.sqc"
      sql_setdlist[2].sqldata = (void*)utkymd;
#line 810 "A205irai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 810 "A205irai.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 810 "A205irai.sqc"
      sql_setdlist[3].sqldata = (void*)kmkcd;
#line 810 "A205irai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 810 "A205irai.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 810 "A205irai.sqc"
  sqlacall((unsigned short)26,6,2,0,0L);
#line 810 "A205irai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 810 "A205irai.sqc"
  sqlastop(0L);
}

#line 810 "A205irai.sqc"


    while( 1 ) {
        Irai* rec;

        
/*
EXEC SQL FETCH c5 INTO
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
#line 864 "A205irai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 864 "A205irai.sqc"
  sqlaaloc(3,49,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[49];
#line 864 "A205irai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 864 "A205irai.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 864 "A205irai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 864 "A205irai.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 864 "A205irai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 864 "A205irai.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 864 "A205irai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 864 "A205irai.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 864 "A205irai.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 864 "A205irai.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 864 "A205irai.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 864 "A205irai.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 864 "A205irai.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 864 "A205irai.sqc"
      sql_setdlist[6].sqldata = (void*)&irihsmkbn;
#line 864 "A205irai.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 864 "A205irai.sqc"
      sql_setdlist[7].sqldata = (void*)&irikbn;
#line 864 "A205irai.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 864 "A205irai.sqc"
      sql_setdlist[8].sqldata = (void*)&ksktkbn;
#line 864 "A205irai.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 864 "A205irai.sqc"
      sql_setdlist[9].sqldata = (void*)sriymd;
#line 864 "A205irai.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 14;
#line 864 "A205irai.sqc"
      sql_setdlist[10].sqldata = (void*)kntno;
#line 864 "A205irai.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 864 "A205irai.sqc"
      sql_setdlist[11].sqldata = (void*)&kntketflg;
#line 864 "A205irai.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 5;
#line 864 "A205irai.sqc"
      sql_setdlist[12].sqldata = (void*)chkmj;
#line 864 "A205irai.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 5;
#line 864 "A205irai.sqc"
      sql_setdlist[13].sqldata = (void*)stsrcd;
#line 864 "A205irai.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 17;
#line 864 "A205irai.sqc"
      sql_setdlist[14].sqldata = (void*)kmkrs;
#line 864 "A205irai.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 864 "A205irai.sqc"
      sql_setdlist[15].sqldata = (void*)oyakmkcd;
#line 864 "A205irai.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 8;
#line 864 "A205irai.sqc"
      sql_setdlist[16].sqldata = (void*)smpcd;
#line 864 "A205irai.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 8;
#line 864 "A205irai.sqc"
      sql_setdlist[17].sqldata = (void*)setkmkcd;
#line 864 "A205irai.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 864 "A205irai.sqc"
      sql_setdlist[18].sqldata = (void*)&srinycd;
#line 864 "A205irai.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 3;
#line 864 "A205irai.sqc"
      sql_setdlist[19].sqldata = (void*)seccd;
#line 864 "A205irai.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 864 "A205irai.sqc"
      sql_setdlist[20].sqldata = (void*)&skchkflg;
#line 864 "A205irai.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 864 "A205irai.sqc"
      sql_setdlist[21].sqldata = (void*)&bkfkkbn;
#line 864 "A205irai.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 3;
#line 864 "A205irai.sqc"
      sql_setdlist[22].sqldata = (void*)ysnlbl;
#line 864 "A205irai.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 864 "A205irai.sqc"
      sql_setdlist[23].sqldata = (void*)&skflg;
#line 864 "A205irai.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 864 "A205irai.sqc"
      sql_setdlist[24].sqldata = (void*)&tkflg;
#line 864 "A205irai.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 864 "A205irai.sqc"
      sql_setdlist[25].sqldata = (void*)&sjflg;
#line 864 "A205irai.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 864 "A205irai.sqc"
      sql_setdlist[26].sqldata = (void*)&jktkflg;
#line 864 "A205irai.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 4;
#line 864 "A205irai.sqc"
      sql_setdlist[27].sqldata = (void*)kjno;
#line 864 "A205irai.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 864 "A205irai.sqc"
      sql_setdlist[28].sqldata = (void*)&fkhkknohjkbn;
#line 864 "A205irai.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 4;
#line 864 "A205irai.sqc"
      sql_setdlist[29].sqldata = (void*)tbkjno;
#line 864 "A205irai.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 864 "A205irai.sqc"
      sql_setdlist[30].sqldata = (void*)&tbkjflg;
#line 864 "A205irai.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 25;
#line 864 "A205irai.sqc"
      sql_setdlist[31].sqldata = (void*)htkfkhms;
#line 864 "A205irai.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 864 "A205irai.sqc"
      sql_setdlist[32].sqldata = (void*)tskflg;
#line 864 "A205irai.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 864 "A205irai.sqc"
      sql_setdlist[33].sqldata = (void*)tktflg;
#line 864 "A205irai.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 864 "A205irai.sqc"
      sql_setdlist[34].sqldata = (void*)&bnckbn;
#line 864 "A205irai.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 864 "A205irai.sqc"
      sql_setdlist[35].sqldata = (void*)&nbnckbn;
#line 864 "A205irai.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 11;
#line 864 "A205irai.sqc"
      sql_setdlist[36].sqldata = (void*)knskisyymd;
#line 864 "A205irai.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 11;
#line 864 "A205irai.sqc"
      sql_setdlist[37].sqldata = (void*)knskryymd;
#line 864 "A205irai.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 9;
#line 864 "A205irai.sqc"
      sql_setdlist[38].sqldata = (void*)knskrytme;
#line 864 "A205irai.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 864 "A205irai.sqc"
      sql_setdlist[39].sqldata = (void*)&kkhkkflg;
#line 864 "A205irai.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 864 "A205irai.sqc"
      sql_setdlist[40].sqldata = (void*)&kkiriflg;
#line 864 "A205irai.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[41].sqltype = 500; sql_setdlist[41].sqllen = 2;
#line 864 "A205irai.sqc"
      sql_setdlist[41].sqldata = (void*)&kkirilotno;
#line 864 "A205irai.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 5;
#line 864 "A205irai.sqc"
      sql_setdlist[42].sqldata = (void*)kktoutkid;
#line 864 "A205irai.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[43].sqltype = 500; sql_setdlist[43].sqllen = 2;
#line 864 "A205irai.sqc"
      sql_setdlist[43].sqldata = (void*)&knssu;
#line 864 "A205irai.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 864 "A205irai.sqc"
      sql_setdlist[44].sqldata = (void*)&odrssflg;
#line 864 "A205irai.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 16;
#line 864 "A205irai.sqc"
      sql_setdlist[45].sqldata = (void*)ytiksbr;
#line 864 "A205irai.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 864 "A205irai.sqc"
      sql_setdlist[46].sqldata = (void*)&hhkjkflg;
#line 864 "A205irai.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 27;
#line 864 "A205irai.sqc"
      sql_setdlist[47].sqldata = (void*)ksndh;
#line 864 "A205irai.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 864 "A205irai.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 27;
#line 864 "A205irai.sqc"
      sql_setdlist[48].sqldata = (void*)trkdh;
#line 864 "A205irai.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 864 "A205irai.sqc"
      sqlasetdata(3,0,49,sql_setdlist,0L,0L);
    }
#line 864 "A205irai.sqc"
  sqlacall((unsigned short)25,6,0,3,0L);
#line 864 "A205irai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 864 "A205irai.sqc"
  sqlastop(0L);
}

#line 864 "A205irai.sqc"


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
EXEC SQL CLOSE c5;
*/

{
#line 879 "A205irai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 879 "A205irai.sqc"
  sqlacall((unsigned short)20,6,0,0,0L);
#line 879 "A205irai.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 879 "A205irai.sqc"
  sqlastop(0L);
}

#line 879 "A205irai.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 887 "A205irai.sqc"

    return sqlca.sqlcode;
}

/*  2.00     2009-01-07     Merits K.Ameno 施設コード増桁 通信仕様変更対応 追加 */
/******************************************************************************
 * ABunIriKmkCdSel()
 *    IRAI レコードKey条件取得
 * ■引数
 *    [I]  Irai* pKey       取得するレコードのキー
 *    [O]  char** arrayOut      取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ABunIriKmkCdSel( Irai* pKey, Irai** arrayOut, int* numOut )
{
    Irai*       array = NULL;
    int         num = 0;
	int         error = 0;


    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, IraiArray ) )
        return HRC_INVALID_VALUE;

/*** ameno ***/
	sFncPutLog ( TRCKIND_WARNING, __FILE__, "ABunIriKmkCdSel", __LINE__,
		EXEFLG_NON, "00000000",
		"依頼から項目コードSELECT 受付日(%s) 依頼書No(%s) サンプリングコード(%s)", utkymd, irino, smpcd );
/*** ameno ***/

	int i;
	for (i = 0; i <= RETRY; i++) {
		error = 0;

	    
/*
EXEC SQL DECLARE c6 CURSOR FOR
		SELECT DISTINCT
			KMKCD
		FROM
			IRAI
		WHERE
			IRINO = :irino AND
			UTKYMD = :utkymd AND
			SMPCD = :smpcd
		ORDER BY
			KMKCD
		FOR READ ONLY;
*/

#line 938 "A205irai.sqc"


	    
/*
EXEC SQL OPEN c6;
*/

{
#line 940 "A205irai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 940 "A205irai.sqc"
  sqlaaloc(2,3,9,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 940 "A205irai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 12;
#line 940 "A205irai.sqc"
      sql_setdlist[0].sqldata = (void*)irino;
#line 940 "A205irai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 940 "A205irai.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 940 "A205irai.sqc"
      sql_setdlist[1].sqldata = (void*)utkymd;
#line 940 "A205irai.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 940 "A205irai.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 940 "A205irai.sqc"
      sql_setdlist[2].sqldata = (void*)smpcd;
#line 940 "A205irai.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 940 "A205irai.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 940 "A205irai.sqc"
  sqlacall((unsigned short)26,7,2,0,0L);
#line 940 "A205irai.sqc"
  sqlastop(0L);
}

#line 940 "A205irai.sqc"


	    while( 1 ) {
	        Irai* rec;

			
/*
EXEC SQL FETCH c6 INTO
				:kmkcd;
*/

{
#line 946 "A205irai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 946 "A205irai.sqc"
  sqlaaloc(3,1,10,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 946 "A205irai.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 946 "A205irai.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcd;
#line 946 "A205irai.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 946 "A205irai.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 946 "A205irai.sqc"
  sqlacall((unsigned short)25,7,0,3,0L);
#line 946 "A205irai.sqc"
  sqlastop(0L);
}

#line 946 "A205irai.sqc"


			if( SQLCODE == 100 )
				break;
			
			if (sqlca.sqlcode < 0) {
				// エラー発生時は領域解放してブレイク
				if (array != NULL) {
					ZbmlFree(array);
					array = NULL;
					num   = 0;
				}
				error = sqlca.sqlcode;
                sFncPutLog ( TRCKIND_ERROR, __FILE__, "ABunIriKmkCdSel", __LINE__,
                             EXEFLG_NON, "020", "DBエラー発生 [sqlcode : %d]", sqlca.sqlcode ) ;
				break;
			}

	        if( num % ALLOC_UNIT == 0 ) {
	            array = (Irai*)ZbmlRealloc( array,
	                                    sizeof( Irai ) * ( num + ALLOC_UNIT ) );
	            memset( array + num, 0, sizeof( Irai ) * ALLOC_UNIT );
	        }
	
	
	        rec = array + num++;
	        ZbmlMapHostToStruct( (char*)rec, IraiArray );
	    }
	
	    
/*
EXEC SQL CLOSE c6;
*/

{
#line 975 "A205irai.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 975 "A205irai.sqc"
  sqlacall((unsigned short)20,7,0,0,0L);
#line 975 "A205irai.sqc"
  sqlastop(0L);
}

#line 975 "A205irai.sqc"


		// ロックの場合はリトライ、ロック以外のエラーはデータ無しで終了
		// リトライは５秒待ってから
		if (error == ERR_LOCK) {
            sFncPutLog ( TRCKIND_ERROR, __FILE__, "ABunIriKmkCdSel", __LINE__,
                         EXEFLG_NON, "020", "ロックによるリトライ[%d]回目", i ) ;
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
