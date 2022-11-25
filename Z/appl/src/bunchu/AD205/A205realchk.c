static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,111,65,52,85,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,65,50,48,53,82,69,65,76,0,0,0,0,0,0,0,0,
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


#line 1 "A205realchk.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： A205realchk.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "A205realchk.h"
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


#line 24 "A205realchk.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "A205realchk.sqc"

	char    knskisymd[11];
	char    sriymd[11];
	char    kntno[14];
	char    kntketflg;
	char    knsgrp[17];
	char    kmkcd[8];
	short   knssu;
	short   knssueda;
	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    trid[11];
	short   trpos;
	char    asyrckid[11];
	short   asyrckpos;
	char    bskkbn[5];
	char    nbkmkcd[8];
	char    renjicflg;
	char    soukn1flg;
	char    kanrenflg;
	char    bunkkuflg;
	char    kesseiflg;
	char    rirekiflg;
	char    syougoflg;
	char    keisanflg;
	char    per100flg;
	char    tousekflg;
	char    kisyakflg;
	char    kouseiflg;
	char    syoungflg;
	char    soukn2flg;
	char    fukaptflg;
	char    yobiflg01;
	char    tobiflg02;
	char    yobiflg03;
	char    yobiflg04;
	char    yobiflg05;
	char    renjicpara[257];
	char    soukn1para[257];
	char    kanrenpara[257];
	char    bunkkupara[257];
	char    kesseipara[257];
	char    rirekipara[257];
	char    syougopara[257];
	char    keisanpara[257];
	char    per100para[257];
	char    tousekpara[257];
	char    kisyakpara[257];
	char    kouseipara[257];
	char    syoungpara[257];
	char    soukn2para[257];
	char    fukaptpara[257];
	char    yobipara01[257];
	char    yobipara02[257];
	char    yobipara03[257];
	char    yobipara04[257];
	char    yobipara05[257];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 89 "A205realchk.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Realchk

BmlDMMInfo	RealchkArray[] = {
	DMM_SDATE( knskisymd ),
	DMM_SDATE( sriymd ),
	DMM_SSTRING( kntno ),
	DMM_SCHAR( kntketflg ),
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSHORT( knssu ),
	DMM_SSHORT( knssueda ),
	DMM_SDATE( utkymd ),
	DMM_SSTRING( irino ),
	DMM_SCHAR( iriketflg ),
	DMM_SSHORT( zssdino ),
	DMM_SSTRING( trid ),
	DMM_SSHORT( trpos ),
	DMM_SSTRING( asyrckid ),
	DMM_SSHORT( asyrckpos ),
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( nbkmkcd ),
	DMM_SCHAR( renjicflg ),
	DMM_SCHAR( soukn1flg ),
	DMM_SCHAR( kanrenflg ),
	DMM_SCHAR( bunkkuflg ),
	DMM_SCHAR( kesseiflg ),
	DMM_SCHAR( rirekiflg ),
	DMM_SCHAR( syougoflg ),
	DMM_SCHAR( keisanflg ),
	DMM_SCHAR( per100flg ),
	DMM_SCHAR( tousekflg ),
	DMM_SCHAR( kisyakflg ),
	DMM_SCHAR( kouseiflg ),
	DMM_SCHAR( syoungflg ),
	DMM_SCHAR( soukn2flg ),
	DMM_SCHAR( fukaptflg ),
	DMM_SCHAR( yobiflg01 ),
	DMM_SCHAR( tobiflg02 ),
	DMM_SCHAR( yobiflg03 ),
	DMM_SCHAR( yobiflg04 ),
	DMM_SCHAR( yobiflg05 ),
	DMM_SSTRING( renjicpara ),
	DMM_SSTRING( soukn1para ),
	DMM_SSTRING( kanrenpara ),
	DMM_SSTRING( bunkkupara ),
	DMM_SSTRING( kesseipara ),
	DMM_SSTRING( rirekipara ),
	DMM_SSTRING( syougopara ),
	DMM_SSTRING( keisanpara ),
	DMM_SSTRING( per100para ),
	DMM_SSTRING( tousekpara ),
	DMM_SSTRING( kisyakpara ),
	DMM_SSTRING( kouseipara ),
	DMM_SSTRING( syoungpara ),
	DMM_SSTRING( soukn2para ),
	DMM_SSTRING( fukaptpara ),
	DMM_SSTRING( yobipara01 ),
	DMM_SSTRING( yobipara02 ),
	DMM_SSTRING( yobipara03 ),
	DMM_SSTRING( yobipara04 ),
	DMM_SSTRING( yobipara05 ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ABunRealInsert()
 *    REALCHK レコードを挿入する
 * ■引数
 *    [I]  Realchk* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ABunRealInsert( Realchk* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, RealchkArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 179 "A205realchk.sqc"


    
/*
EXEC SQL INSERT INTO REALCHK
    (
		KNSKISYMD,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		KNSGRP,
		KMKCD,
		KNSSU,
		KNSSUEDA,
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		TRID,
		TRPOS,
		ASYRCKID,
		ASYRCKPOS,
		BSKKBN,
		NBKMKCD,
		RENJICFLG,
		SOUKN1FLG,
		KANRENFLG,
		BUNKKUFLG,
		KESSEIFLG,
		RIREKIFLG,
		SYOUGOFLG,
		KEISANFLG,
		PER100FLG,
		TOUSEKFLG,
		KISYAKFLG,
		KOUSEIFLG,
		SYOUNGFLG,
		SOUKN2FLG,
		FUKAPTFLG,
		YOBIFLG01,
		TOBIFLG02,
		YOBIFLG03,
		YOBIFLG04,
		YOBIFLG05,
		RENJICPARA,
		SOUKN1PARA,
		KANRENPARA,
		BUNKKUPARA,
		KESSEIPARA,
		RIREKIPARA,
		SYOUGOPARA,
		KEISANPARA,
		PER100PARA,
		TOUSEKPARA,
		KISYAKPARA,
		KOUSEIPARA,
		SYOUNGPARA,
		SOUKN2PARA,
		FUKAPTPARA,
		YOBIPARA01,
		YOBIPARA02,
		YOBIPARA03,
		YOBIPARA04,
		YOBIPARA05,
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
		:utkymd,
		:irino,
		:iriketflg,
		:zssdino,
		:trid,
		:trpos,
		:asyrckid,
		:asyrckpos,
		:bskkbn,
		:nbkmkcd,
		:renjicflg,
		:soukn1flg,
		:kanrenflg,
		:bunkkuflg,
		:kesseiflg,
		:rirekiflg,
		:syougoflg,
		:keisanflg,
		:per100flg,
		:tousekflg,
		:kisyakflg,
		:kouseiflg,
		:syoungflg,
		:soukn2flg,
		:fukaptflg,
		:yobiflg01,
		:tobiflg02,
		:yobiflg03,
		:yobiflg04,
		:yobiflg05,
		:renjicpara,
		:soukn1para,
		:kanrenpara,
		:bunkkupara,
		:kesseipara,
		:rirekipara,
		:syougopara,
		:keisanpara,
		:per100para,
		:tousekpara,
		:kisyakpara,
		:kouseipara,
		:syoungpara,
		:soukn2para,
		:fukaptpara,
		:yobipara01,
		:yobipara02,
		:yobipara03,
		:yobipara04,
		:yobipara05,
		CURRENT TIMESTAMP
    );
*/

{
#line 302 "A205realchk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 302 "A205realchk.sqc"
  sqlaaloc(2,58,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[58];
#line 302 "A205realchk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 302 "A205realchk.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 302 "A205realchk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 302 "A205realchk.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 302 "A205realchk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 302 "A205realchk.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 302 "A205realchk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 302 "A205realchk.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 302 "A205realchk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 302 "A205realchk.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 302 "A205realchk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 302 "A205realchk.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 302 "A205realchk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 302 "A205realchk.sqc"
      sql_setdlist[6].sqldata = (void*)&knssu;
#line 302 "A205realchk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 302 "A205realchk.sqc"
      sql_setdlist[7].sqldata = (void*)&knssueda;
#line 302 "A205realchk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 302 "A205realchk.sqc"
      sql_setdlist[8].sqldata = (void*)utkymd;
#line 302 "A205realchk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 12;
#line 302 "A205realchk.sqc"
      sql_setdlist[9].sqldata = (void*)irino;
#line 302 "A205realchk.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 302 "A205realchk.sqc"
      sql_setdlist[10].sqldata = (void*)&iriketflg;
#line 302 "A205realchk.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 302 "A205realchk.sqc"
      sql_setdlist[11].sqldata = (void*)&zssdino;
#line 302 "A205realchk.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 302 "A205realchk.sqc"
      sql_setdlist[12].sqldata = (void*)trid;
#line 302 "A205realchk.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 302 "A205realchk.sqc"
      sql_setdlist[13].sqldata = (void*)&trpos;
#line 302 "A205realchk.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 11;
#line 302 "A205realchk.sqc"
      sql_setdlist[14].sqldata = (void*)asyrckid;
#line 302 "A205realchk.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[15].sqltype = 500; sql_setdlist[15].sqllen = 2;
#line 302 "A205realchk.sqc"
      sql_setdlist[15].sqldata = (void*)&asyrckpos;
#line 302 "A205realchk.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 5;
#line 302 "A205realchk.sqc"
      sql_setdlist[16].sqldata = (void*)bskkbn;
#line 302 "A205realchk.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 8;
#line 302 "A205realchk.sqc"
      sql_setdlist[17].sqldata = (void*)nbkmkcd;
#line 302 "A205realchk.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 302 "A205realchk.sqc"
      sql_setdlist[18].sqldata = (void*)&renjicflg;
#line 302 "A205realchk.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 302 "A205realchk.sqc"
      sql_setdlist[19].sqldata = (void*)&soukn1flg;
#line 302 "A205realchk.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 302 "A205realchk.sqc"
      sql_setdlist[20].sqldata = (void*)&kanrenflg;
#line 302 "A205realchk.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 302 "A205realchk.sqc"
      sql_setdlist[21].sqldata = (void*)&bunkkuflg;
#line 302 "A205realchk.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 302 "A205realchk.sqc"
      sql_setdlist[22].sqldata = (void*)&kesseiflg;
#line 302 "A205realchk.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 302 "A205realchk.sqc"
      sql_setdlist[23].sqldata = (void*)&rirekiflg;
#line 302 "A205realchk.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 302 "A205realchk.sqc"
      sql_setdlist[24].sqldata = (void*)&syougoflg;
#line 302 "A205realchk.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 302 "A205realchk.sqc"
      sql_setdlist[25].sqldata = (void*)&keisanflg;
#line 302 "A205realchk.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 302 "A205realchk.sqc"
      sql_setdlist[26].sqldata = (void*)&per100flg;
#line 302 "A205realchk.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 302 "A205realchk.sqc"
      sql_setdlist[27].sqldata = (void*)&tousekflg;
#line 302 "A205realchk.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 302 "A205realchk.sqc"
      sql_setdlist[28].sqldata = (void*)&kisyakflg;
#line 302 "A205realchk.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 302 "A205realchk.sqc"
      sql_setdlist[29].sqldata = (void*)&kouseiflg;
#line 302 "A205realchk.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 302 "A205realchk.sqc"
      sql_setdlist[30].sqldata = (void*)&syoungflg;
#line 302 "A205realchk.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 302 "A205realchk.sqc"
      sql_setdlist[31].sqldata = (void*)&soukn2flg;
#line 302 "A205realchk.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 302 "A205realchk.sqc"
      sql_setdlist[32].sqldata = (void*)&fukaptflg;
#line 302 "A205realchk.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 302 "A205realchk.sqc"
      sql_setdlist[33].sqldata = (void*)&yobiflg01;
#line 302 "A205realchk.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 302 "A205realchk.sqc"
      sql_setdlist[34].sqldata = (void*)&tobiflg02;
#line 302 "A205realchk.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 302 "A205realchk.sqc"
      sql_setdlist[35].sqldata = (void*)&yobiflg03;
#line 302 "A205realchk.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 302 "A205realchk.sqc"
      sql_setdlist[36].sqldata = (void*)&yobiflg04;
#line 302 "A205realchk.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 302 "A205realchk.sqc"
      sql_setdlist[37].sqldata = (void*)&yobiflg05;
#line 302 "A205realchk.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 257;
#line 302 "A205realchk.sqc"
      sql_setdlist[38].sqldata = (void*)renjicpara;
#line 302 "A205realchk.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 257;
#line 302 "A205realchk.sqc"
      sql_setdlist[39].sqldata = (void*)soukn1para;
#line 302 "A205realchk.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 257;
#line 302 "A205realchk.sqc"
      sql_setdlist[40].sqldata = (void*)kanrenpara;
#line 302 "A205realchk.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 257;
#line 302 "A205realchk.sqc"
      sql_setdlist[41].sqldata = (void*)bunkkupara;
#line 302 "A205realchk.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 257;
#line 302 "A205realchk.sqc"
      sql_setdlist[42].sqldata = (void*)kesseipara;
#line 302 "A205realchk.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 257;
#line 302 "A205realchk.sqc"
      sql_setdlist[43].sqldata = (void*)rirekipara;
#line 302 "A205realchk.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 257;
#line 302 "A205realchk.sqc"
      sql_setdlist[44].sqldata = (void*)syougopara;
#line 302 "A205realchk.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 257;
#line 302 "A205realchk.sqc"
      sql_setdlist[45].sqldata = (void*)keisanpara;
#line 302 "A205realchk.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 257;
#line 302 "A205realchk.sqc"
      sql_setdlist[46].sqldata = (void*)per100para;
#line 302 "A205realchk.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 257;
#line 302 "A205realchk.sqc"
      sql_setdlist[47].sqldata = (void*)tousekpara;
#line 302 "A205realchk.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 257;
#line 302 "A205realchk.sqc"
      sql_setdlist[48].sqldata = (void*)kisyakpara;
#line 302 "A205realchk.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 257;
#line 302 "A205realchk.sqc"
      sql_setdlist[49].sqldata = (void*)kouseipara;
#line 302 "A205realchk.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 257;
#line 302 "A205realchk.sqc"
      sql_setdlist[50].sqldata = (void*)syoungpara;
#line 302 "A205realchk.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 257;
#line 302 "A205realchk.sqc"
      sql_setdlist[51].sqldata = (void*)soukn2para;
#line 302 "A205realchk.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 257;
#line 302 "A205realchk.sqc"
      sql_setdlist[52].sqldata = (void*)fukaptpara;
#line 302 "A205realchk.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 257;
#line 302 "A205realchk.sqc"
      sql_setdlist[53].sqldata = (void*)yobipara01;
#line 302 "A205realchk.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 257;
#line 302 "A205realchk.sqc"
      sql_setdlist[54].sqldata = (void*)yobipara02;
#line 302 "A205realchk.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 257;
#line 302 "A205realchk.sqc"
      sql_setdlist[55].sqldata = (void*)yobipara03;
#line 302 "A205realchk.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 257;
#line 302 "A205realchk.sqc"
      sql_setdlist[56].sqldata = (void*)yobipara04;
#line 302 "A205realchk.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 257;
#line 302 "A205realchk.sqc"
      sql_setdlist[57].sqldata = (void*)yobipara05;
#line 302 "A205realchk.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 302 "A205realchk.sqc"
      sqlasetdata(2,0,58,sql_setdlist,0L,0L);
    }
#line 302 "A205realchk.sqc"
  sqlacall((unsigned short)24,1,2,0,0L);
#line 302 "A205realchk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 302 "A205realchk.sqc"
  sqlastop(0L);
}

#line 302 "A205realchk.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 307 "A205realchk.sqc"

    return sqlca.sqlcode;
}

/** End of File *********************************************************/
