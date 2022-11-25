static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,74,65,86,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,53,55,90,82,69,65,76,32,0,0,0,0,0,0,0,0,
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


#line 1 "Realchk.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Realchk.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Realchk.h"
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


#line 24 "Realchk.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Realchk.sqc"

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

#line 89 "Realchk.sqc"



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
 * ZdbRealchkSelectAll()
 *    REALCHK レコード全件取得
 * ■引数
 *    [O]  Realchk** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbRealchkSelectAll( Realchk** arrayOut, int* numOut )
{
    Realchk*    array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 176 "Realchk.sqc"


    
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
    FROM
        REALCHK FOR READ ONLY;
*/

#line 240 "Realchk.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 242 "Realchk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 242 "Realchk.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 242 "Realchk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 242 "Realchk.sqc"
  sqlastop(0L);
}

#line 242 "Realchk.sqc"


    while( 1 ) {
        Realchk* rec;

        
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
			:ksndh;
*/

{
#line 306 "Realchk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 306 "Realchk.sqc"
  sqlaaloc(3,59,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[59];
#line 306 "Realchk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 306 "Realchk.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 306 "Realchk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 306 "Realchk.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 306 "Realchk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 306 "Realchk.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 306 "Realchk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 306 "Realchk.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 306 "Realchk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 306 "Realchk.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 306 "Realchk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 306 "Realchk.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 306 "Realchk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 306 "Realchk.sqc"
      sql_setdlist[6].sqldata = (void*)&knssu;
#line 306 "Realchk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 306 "Realchk.sqc"
      sql_setdlist[7].sqldata = (void*)&knssueda;
#line 306 "Realchk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 306 "Realchk.sqc"
      sql_setdlist[8].sqldata = (void*)utkymd;
#line 306 "Realchk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 12;
#line 306 "Realchk.sqc"
      sql_setdlist[9].sqldata = (void*)irino;
#line 306 "Realchk.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 306 "Realchk.sqc"
      sql_setdlist[10].sqldata = (void*)&iriketflg;
#line 306 "Realchk.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 306 "Realchk.sqc"
      sql_setdlist[11].sqldata = (void*)&zssdino;
#line 306 "Realchk.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 306 "Realchk.sqc"
      sql_setdlist[12].sqldata = (void*)trid;
#line 306 "Realchk.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 306 "Realchk.sqc"
      sql_setdlist[13].sqldata = (void*)&trpos;
#line 306 "Realchk.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 11;
#line 306 "Realchk.sqc"
      sql_setdlist[14].sqldata = (void*)asyrckid;
#line 306 "Realchk.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[15].sqltype = 500; sql_setdlist[15].sqllen = 2;
#line 306 "Realchk.sqc"
      sql_setdlist[15].sqldata = (void*)&asyrckpos;
#line 306 "Realchk.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 5;
#line 306 "Realchk.sqc"
      sql_setdlist[16].sqldata = (void*)bskkbn;
#line 306 "Realchk.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 8;
#line 306 "Realchk.sqc"
      sql_setdlist[17].sqldata = (void*)nbkmkcd;
#line 306 "Realchk.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 306 "Realchk.sqc"
      sql_setdlist[18].sqldata = (void*)&renjicflg;
#line 306 "Realchk.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 306 "Realchk.sqc"
      sql_setdlist[19].sqldata = (void*)&soukn1flg;
#line 306 "Realchk.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 306 "Realchk.sqc"
      sql_setdlist[20].sqldata = (void*)&kanrenflg;
#line 306 "Realchk.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 306 "Realchk.sqc"
      sql_setdlist[21].sqldata = (void*)&bunkkuflg;
#line 306 "Realchk.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 306 "Realchk.sqc"
      sql_setdlist[22].sqldata = (void*)&kesseiflg;
#line 306 "Realchk.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 306 "Realchk.sqc"
      sql_setdlist[23].sqldata = (void*)&rirekiflg;
#line 306 "Realchk.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 306 "Realchk.sqc"
      sql_setdlist[24].sqldata = (void*)&syougoflg;
#line 306 "Realchk.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 306 "Realchk.sqc"
      sql_setdlist[25].sqldata = (void*)&keisanflg;
#line 306 "Realchk.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 306 "Realchk.sqc"
      sql_setdlist[26].sqldata = (void*)&per100flg;
#line 306 "Realchk.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 306 "Realchk.sqc"
      sql_setdlist[27].sqldata = (void*)&tousekflg;
#line 306 "Realchk.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 306 "Realchk.sqc"
      sql_setdlist[28].sqldata = (void*)&kisyakflg;
#line 306 "Realchk.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 306 "Realchk.sqc"
      sql_setdlist[29].sqldata = (void*)&kouseiflg;
#line 306 "Realchk.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 306 "Realchk.sqc"
      sql_setdlist[30].sqldata = (void*)&syoungflg;
#line 306 "Realchk.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 306 "Realchk.sqc"
      sql_setdlist[31].sqldata = (void*)&soukn2flg;
#line 306 "Realchk.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 306 "Realchk.sqc"
      sql_setdlist[32].sqldata = (void*)&fukaptflg;
#line 306 "Realchk.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 306 "Realchk.sqc"
      sql_setdlist[33].sqldata = (void*)&yobiflg01;
#line 306 "Realchk.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 306 "Realchk.sqc"
      sql_setdlist[34].sqldata = (void*)&tobiflg02;
#line 306 "Realchk.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 306 "Realchk.sqc"
      sql_setdlist[35].sqldata = (void*)&yobiflg03;
#line 306 "Realchk.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 306 "Realchk.sqc"
      sql_setdlist[36].sqldata = (void*)&yobiflg04;
#line 306 "Realchk.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 306 "Realchk.sqc"
      sql_setdlist[37].sqldata = (void*)&yobiflg05;
#line 306 "Realchk.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 257;
#line 306 "Realchk.sqc"
      sql_setdlist[38].sqldata = (void*)renjicpara;
#line 306 "Realchk.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 257;
#line 306 "Realchk.sqc"
      sql_setdlist[39].sqldata = (void*)soukn1para;
#line 306 "Realchk.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 257;
#line 306 "Realchk.sqc"
      sql_setdlist[40].sqldata = (void*)kanrenpara;
#line 306 "Realchk.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 257;
#line 306 "Realchk.sqc"
      sql_setdlist[41].sqldata = (void*)bunkkupara;
#line 306 "Realchk.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 257;
#line 306 "Realchk.sqc"
      sql_setdlist[42].sqldata = (void*)kesseipara;
#line 306 "Realchk.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 257;
#line 306 "Realchk.sqc"
      sql_setdlist[43].sqldata = (void*)rirekipara;
#line 306 "Realchk.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 257;
#line 306 "Realchk.sqc"
      sql_setdlist[44].sqldata = (void*)syougopara;
#line 306 "Realchk.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 257;
#line 306 "Realchk.sqc"
      sql_setdlist[45].sqldata = (void*)keisanpara;
#line 306 "Realchk.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 257;
#line 306 "Realchk.sqc"
      sql_setdlist[46].sqldata = (void*)per100para;
#line 306 "Realchk.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 257;
#line 306 "Realchk.sqc"
      sql_setdlist[47].sqldata = (void*)tousekpara;
#line 306 "Realchk.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 257;
#line 306 "Realchk.sqc"
      sql_setdlist[48].sqldata = (void*)kisyakpara;
#line 306 "Realchk.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 257;
#line 306 "Realchk.sqc"
      sql_setdlist[49].sqldata = (void*)kouseipara;
#line 306 "Realchk.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 257;
#line 306 "Realchk.sqc"
      sql_setdlist[50].sqldata = (void*)syoungpara;
#line 306 "Realchk.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 257;
#line 306 "Realchk.sqc"
      sql_setdlist[51].sqldata = (void*)soukn2para;
#line 306 "Realchk.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 257;
#line 306 "Realchk.sqc"
      sql_setdlist[52].sqldata = (void*)fukaptpara;
#line 306 "Realchk.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 257;
#line 306 "Realchk.sqc"
      sql_setdlist[53].sqldata = (void*)yobipara01;
#line 306 "Realchk.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 257;
#line 306 "Realchk.sqc"
      sql_setdlist[54].sqldata = (void*)yobipara02;
#line 306 "Realchk.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 257;
#line 306 "Realchk.sqc"
      sql_setdlist[55].sqldata = (void*)yobipara03;
#line 306 "Realchk.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 257;
#line 306 "Realchk.sqc"
      sql_setdlist[56].sqldata = (void*)yobipara04;
#line 306 "Realchk.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 257;
#line 306 "Realchk.sqc"
      sql_setdlist[57].sqldata = (void*)yobipara05;
#line 306 "Realchk.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 306 "Realchk.sqc"
      sql_setdlist[58].sqltype = 460; sql_setdlist[58].sqllen = 27;
#line 306 "Realchk.sqc"
      sql_setdlist[58].sqldata = (void*)ksndh;
#line 306 "Realchk.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 306 "Realchk.sqc"
      sqlasetdata(3,0,59,sql_setdlist,0L,0L);
    }
#line 306 "Realchk.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 306 "Realchk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 306 "Realchk.sqc"
  sqlastop(0L);
}

#line 306 "Realchk.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Realchk*)ZbmlRealloc( array,
                                    sizeof( Realchk ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Realchk ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, RealchkArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 321 "Realchk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 321 "Realchk.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 321 "Realchk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 321 "Realchk.sqc"
  sqlastop(0L);
}

#line 321 "Realchk.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 329 "Realchk.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbRealchkSelectKey()
 *    REALCHK レコードKey条件取得
 * ■引数
 *    [I]  Realchk* pKey       取得するレコードのキー
 *    [O]  Realchk** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbRealchkSelectKey( Realchk* pKey, Realchk** arrayOut, int* numOut )
{
    Realchk*    array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, RealchkArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 355 "Realchk.sqc"


    
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
    FROM
        REALCHK
    WHERE
		KNTNO = :kntno AND
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd AND
		KNSSU = :knssu AND
		KNSSUEDA = :knssueda AND
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd FOR READ ONLY;
*/

#line 427 "Realchk.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 429 "Realchk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 429 "Realchk.sqc"
  sqlaaloc(2,7,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 429 "Realchk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 14;
#line 429 "Realchk.sqc"
      sql_setdlist[0].sqldata = (void*)kntno;
#line 429 "Realchk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 429 "Realchk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 429 "Realchk.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 429 "Realchk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 429 "Realchk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 429 "Realchk.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 429 "Realchk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 429 "Realchk.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 429 "Realchk.sqc"
      sql_setdlist[3].sqldata = (void*)&knssu;
#line 429 "Realchk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 429 "Realchk.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 429 "Realchk.sqc"
      sql_setdlist[4].sqldata = (void*)&knssueda;
#line 429 "Realchk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 429 "Realchk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 429 "Realchk.sqc"
      sql_setdlist[5].sqldata = (void*)knskisymd;
#line 429 "Realchk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 429 "Realchk.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 429 "Realchk.sqc"
      sql_setdlist[6].sqldata = (void*)sriymd;
#line 429 "Realchk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 429 "Realchk.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 429 "Realchk.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 429 "Realchk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 429 "Realchk.sqc"
  sqlastop(0L);
}

#line 429 "Realchk.sqc"


    while( 1 ) {
        Realchk* rec;

        
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
			:ksndh;
*/

{
#line 493 "Realchk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 493 "Realchk.sqc"
  sqlaaloc(3,59,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[59];
#line 493 "Realchk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 493 "Realchk.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 493 "Realchk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 493 "Realchk.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 493 "Realchk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 493 "Realchk.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 493 "Realchk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 493 "Realchk.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 493 "Realchk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 493 "Realchk.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 493 "Realchk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 493 "Realchk.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 493 "Realchk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 493 "Realchk.sqc"
      sql_setdlist[6].sqldata = (void*)&knssu;
#line 493 "Realchk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 493 "Realchk.sqc"
      sql_setdlist[7].sqldata = (void*)&knssueda;
#line 493 "Realchk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 493 "Realchk.sqc"
      sql_setdlist[8].sqldata = (void*)utkymd;
#line 493 "Realchk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 12;
#line 493 "Realchk.sqc"
      sql_setdlist[9].sqldata = (void*)irino;
#line 493 "Realchk.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 493 "Realchk.sqc"
      sql_setdlist[10].sqldata = (void*)&iriketflg;
#line 493 "Realchk.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 493 "Realchk.sqc"
      sql_setdlist[11].sqldata = (void*)&zssdino;
#line 493 "Realchk.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 493 "Realchk.sqc"
      sql_setdlist[12].sqldata = (void*)trid;
#line 493 "Realchk.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 493 "Realchk.sqc"
      sql_setdlist[13].sqldata = (void*)&trpos;
#line 493 "Realchk.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 11;
#line 493 "Realchk.sqc"
      sql_setdlist[14].sqldata = (void*)asyrckid;
#line 493 "Realchk.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[15].sqltype = 500; sql_setdlist[15].sqllen = 2;
#line 493 "Realchk.sqc"
      sql_setdlist[15].sqldata = (void*)&asyrckpos;
#line 493 "Realchk.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 5;
#line 493 "Realchk.sqc"
      sql_setdlist[16].sqldata = (void*)bskkbn;
#line 493 "Realchk.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 8;
#line 493 "Realchk.sqc"
      sql_setdlist[17].sqldata = (void*)nbkmkcd;
#line 493 "Realchk.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 493 "Realchk.sqc"
      sql_setdlist[18].sqldata = (void*)&renjicflg;
#line 493 "Realchk.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 493 "Realchk.sqc"
      sql_setdlist[19].sqldata = (void*)&soukn1flg;
#line 493 "Realchk.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 493 "Realchk.sqc"
      sql_setdlist[20].sqldata = (void*)&kanrenflg;
#line 493 "Realchk.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 493 "Realchk.sqc"
      sql_setdlist[21].sqldata = (void*)&bunkkuflg;
#line 493 "Realchk.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 493 "Realchk.sqc"
      sql_setdlist[22].sqldata = (void*)&kesseiflg;
#line 493 "Realchk.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 493 "Realchk.sqc"
      sql_setdlist[23].sqldata = (void*)&rirekiflg;
#line 493 "Realchk.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 493 "Realchk.sqc"
      sql_setdlist[24].sqldata = (void*)&syougoflg;
#line 493 "Realchk.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 493 "Realchk.sqc"
      sql_setdlist[25].sqldata = (void*)&keisanflg;
#line 493 "Realchk.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 493 "Realchk.sqc"
      sql_setdlist[26].sqldata = (void*)&per100flg;
#line 493 "Realchk.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 493 "Realchk.sqc"
      sql_setdlist[27].sqldata = (void*)&tousekflg;
#line 493 "Realchk.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 493 "Realchk.sqc"
      sql_setdlist[28].sqldata = (void*)&kisyakflg;
#line 493 "Realchk.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 493 "Realchk.sqc"
      sql_setdlist[29].sqldata = (void*)&kouseiflg;
#line 493 "Realchk.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 493 "Realchk.sqc"
      sql_setdlist[30].sqldata = (void*)&syoungflg;
#line 493 "Realchk.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 493 "Realchk.sqc"
      sql_setdlist[31].sqldata = (void*)&soukn2flg;
#line 493 "Realchk.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 493 "Realchk.sqc"
      sql_setdlist[32].sqldata = (void*)&fukaptflg;
#line 493 "Realchk.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 493 "Realchk.sqc"
      sql_setdlist[33].sqldata = (void*)&yobiflg01;
#line 493 "Realchk.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 493 "Realchk.sqc"
      sql_setdlist[34].sqldata = (void*)&tobiflg02;
#line 493 "Realchk.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 493 "Realchk.sqc"
      sql_setdlist[35].sqldata = (void*)&yobiflg03;
#line 493 "Realchk.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 493 "Realchk.sqc"
      sql_setdlist[36].sqldata = (void*)&yobiflg04;
#line 493 "Realchk.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 493 "Realchk.sqc"
      sql_setdlist[37].sqldata = (void*)&yobiflg05;
#line 493 "Realchk.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 257;
#line 493 "Realchk.sqc"
      sql_setdlist[38].sqldata = (void*)renjicpara;
#line 493 "Realchk.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 257;
#line 493 "Realchk.sqc"
      sql_setdlist[39].sqldata = (void*)soukn1para;
#line 493 "Realchk.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 257;
#line 493 "Realchk.sqc"
      sql_setdlist[40].sqldata = (void*)kanrenpara;
#line 493 "Realchk.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 257;
#line 493 "Realchk.sqc"
      sql_setdlist[41].sqldata = (void*)bunkkupara;
#line 493 "Realchk.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 257;
#line 493 "Realchk.sqc"
      sql_setdlist[42].sqldata = (void*)kesseipara;
#line 493 "Realchk.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 257;
#line 493 "Realchk.sqc"
      sql_setdlist[43].sqldata = (void*)rirekipara;
#line 493 "Realchk.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 257;
#line 493 "Realchk.sqc"
      sql_setdlist[44].sqldata = (void*)syougopara;
#line 493 "Realchk.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 257;
#line 493 "Realchk.sqc"
      sql_setdlist[45].sqldata = (void*)keisanpara;
#line 493 "Realchk.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 257;
#line 493 "Realchk.sqc"
      sql_setdlist[46].sqldata = (void*)per100para;
#line 493 "Realchk.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 257;
#line 493 "Realchk.sqc"
      sql_setdlist[47].sqldata = (void*)tousekpara;
#line 493 "Realchk.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 257;
#line 493 "Realchk.sqc"
      sql_setdlist[48].sqldata = (void*)kisyakpara;
#line 493 "Realchk.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 257;
#line 493 "Realchk.sqc"
      sql_setdlist[49].sqldata = (void*)kouseipara;
#line 493 "Realchk.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 257;
#line 493 "Realchk.sqc"
      sql_setdlist[50].sqldata = (void*)syoungpara;
#line 493 "Realchk.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 257;
#line 493 "Realchk.sqc"
      sql_setdlist[51].sqldata = (void*)soukn2para;
#line 493 "Realchk.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 257;
#line 493 "Realchk.sqc"
      sql_setdlist[52].sqldata = (void*)fukaptpara;
#line 493 "Realchk.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 257;
#line 493 "Realchk.sqc"
      sql_setdlist[53].sqldata = (void*)yobipara01;
#line 493 "Realchk.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 257;
#line 493 "Realchk.sqc"
      sql_setdlist[54].sqldata = (void*)yobipara02;
#line 493 "Realchk.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 257;
#line 493 "Realchk.sqc"
      sql_setdlist[55].sqldata = (void*)yobipara03;
#line 493 "Realchk.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 257;
#line 493 "Realchk.sqc"
      sql_setdlist[56].sqldata = (void*)yobipara04;
#line 493 "Realchk.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 257;
#line 493 "Realchk.sqc"
      sql_setdlist[57].sqldata = (void*)yobipara05;
#line 493 "Realchk.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 493 "Realchk.sqc"
      sql_setdlist[58].sqltype = 460; sql_setdlist[58].sqllen = 27;
#line 493 "Realchk.sqc"
      sql_setdlist[58].sqldata = (void*)ksndh;
#line 493 "Realchk.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 493 "Realchk.sqc"
      sqlasetdata(3,0,59,sql_setdlist,0L,0L);
    }
#line 493 "Realchk.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 493 "Realchk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 493 "Realchk.sqc"
  sqlastop(0L);
}

#line 493 "Realchk.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Realchk*)ZbmlRealloc( array,
                                    sizeof( Realchk ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Realchk ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, RealchkArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 508 "Realchk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 508 "Realchk.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 508 "Realchk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 508 "Realchk.sqc"
  sqlastop(0L);
}

#line 508 "Realchk.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 516 "Realchk.sqc"

    return sqlca.sqlcode;
}

long ZdbRealchkSelectKey2( Realchk* pKey, Realchk** arrayOut, int* numOut )
{
    Realchk*    array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, RealchkArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 531 "Realchk.sqc"


    
/*
EXEC SQL DECLARE c3 CURSOR FOR
    SELECT
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
		YOBIFLG05
    FROM
        REALCHK
    WHERE
		KNTNO = :kntno AND
		KNSGRP         = :knsgrp         AND
		KMKCD = :kmkcd AND
		KNSSU = :knssu AND
		KNSSUEDA = :knssueda AND
		KNSKISYMD = :knskisymd FOR READ ONLY;
*/

#line 563 "Realchk.sqc"


    
/*
EXEC SQL OPEN c3;
*/

{
#line 565 "Realchk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 565 "Realchk.sqc"
  sqlaaloc(2,6,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 565 "Realchk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 14;
#line 565 "Realchk.sqc"
      sql_setdlist[0].sqldata = (void*)kntno;
#line 565 "Realchk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 565 "Realchk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 565 "Realchk.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 565 "Realchk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 565 "Realchk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 565 "Realchk.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 565 "Realchk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 565 "Realchk.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 565 "Realchk.sqc"
      sql_setdlist[3].sqldata = (void*)&knssu;
#line 565 "Realchk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 565 "Realchk.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 565 "Realchk.sqc"
      sql_setdlist[4].sqldata = (void*)&knssueda;
#line 565 "Realchk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 565 "Realchk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 565 "Realchk.sqc"
      sql_setdlist[5].sqldata = (void*)knskisymd;
#line 565 "Realchk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 565 "Realchk.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 565 "Realchk.sqc"
  sqlacall((unsigned short)26,3,2,0,0L);
#line 565 "Realchk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 565 "Realchk.sqc"
  sqlastop(0L);
}

#line 565 "Realchk.sqc"


    while( 1 ) {
        Realchk* rec;

        
/*
EXEC SQL FETCH c3 INTO
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
			:yobiflg05;
*/

{
#line 590 "Realchk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 590 "Realchk.sqc"
  sqlaaloc(3,20,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[20];
#line 590 "Realchk.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 590 "Realchk.sqc"
      sql_setdlist[0].sqldata = (void*)&renjicflg;
#line 590 "Realchk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 590 "Realchk.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 590 "Realchk.sqc"
      sql_setdlist[1].sqldata = (void*)&soukn1flg;
#line 590 "Realchk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 590 "Realchk.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 590 "Realchk.sqc"
      sql_setdlist[2].sqldata = (void*)&kanrenflg;
#line 590 "Realchk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 590 "Realchk.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 590 "Realchk.sqc"
      sql_setdlist[3].sqldata = (void*)&bunkkuflg;
#line 590 "Realchk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 590 "Realchk.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 590 "Realchk.sqc"
      sql_setdlist[4].sqldata = (void*)&kesseiflg;
#line 590 "Realchk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 590 "Realchk.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 590 "Realchk.sqc"
      sql_setdlist[5].sqldata = (void*)&rirekiflg;
#line 590 "Realchk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 590 "Realchk.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 590 "Realchk.sqc"
      sql_setdlist[6].sqldata = (void*)&syougoflg;
#line 590 "Realchk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 590 "Realchk.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 590 "Realchk.sqc"
      sql_setdlist[7].sqldata = (void*)&keisanflg;
#line 590 "Realchk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 590 "Realchk.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 590 "Realchk.sqc"
      sql_setdlist[8].sqldata = (void*)&per100flg;
#line 590 "Realchk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 590 "Realchk.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 590 "Realchk.sqc"
      sql_setdlist[9].sqldata = (void*)&tousekflg;
#line 590 "Realchk.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 590 "Realchk.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 590 "Realchk.sqc"
      sql_setdlist[10].sqldata = (void*)&kisyakflg;
#line 590 "Realchk.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 590 "Realchk.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 590 "Realchk.sqc"
      sql_setdlist[11].sqldata = (void*)&kouseiflg;
#line 590 "Realchk.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 590 "Realchk.sqc"
      sql_setdlist[12].sqltype = 452; sql_setdlist[12].sqllen = 1;
#line 590 "Realchk.sqc"
      sql_setdlist[12].sqldata = (void*)&syoungflg;
#line 590 "Realchk.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 590 "Realchk.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 590 "Realchk.sqc"
      sql_setdlist[13].sqldata = (void*)&soukn2flg;
#line 590 "Realchk.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 590 "Realchk.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 590 "Realchk.sqc"
      sql_setdlist[14].sqldata = (void*)&fukaptflg;
#line 590 "Realchk.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 590 "Realchk.sqc"
      sql_setdlist[15].sqltype = 452; sql_setdlist[15].sqllen = 1;
#line 590 "Realchk.sqc"
      sql_setdlist[15].sqldata = (void*)&yobiflg01;
#line 590 "Realchk.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 590 "Realchk.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 590 "Realchk.sqc"
      sql_setdlist[16].sqldata = (void*)&tobiflg02;
#line 590 "Realchk.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 590 "Realchk.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 590 "Realchk.sqc"
      sql_setdlist[17].sqldata = (void*)&yobiflg03;
#line 590 "Realchk.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 590 "Realchk.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 590 "Realchk.sqc"
      sql_setdlist[18].sqldata = (void*)&yobiflg04;
#line 590 "Realchk.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 590 "Realchk.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 590 "Realchk.sqc"
      sql_setdlist[19].sqldata = (void*)&yobiflg05;
#line 590 "Realchk.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 590 "Realchk.sqc"
      sqlasetdata(3,0,20,sql_setdlist,0L,0L);
    }
#line 590 "Realchk.sqc"
  sqlacall((unsigned short)25,3,0,3,0L);
#line 590 "Realchk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 590 "Realchk.sqc"
  sqlastop(0L);
}

#line 590 "Realchk.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Realchk*)ZbmlRealloc( array,
                                    sizeof( Realchk ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Realchk ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, RealchkArray );
    }

    
/*
EXEC SQL CLOSE c3;
*/

{
#line 605 "Realchk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 605 "Realchk.sqc"
  sqlacall((unsigned short)20,3,0,0,0L);
#line 605 "Realchk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 605 "Realchk.sqc"
  sqlastop(0L);
}

#line 605 "Realchk.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 613 "Realchk.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbRealchkInsert()
 *    REALCHK レコードを挿入する
 * ■引数
 *    [I]  Realchk* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbRealchkInsert( Realchk* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, RealchkArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 635 "Realchk.sqc"


    
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
		:ksndh
    );
*/

{
#line 758 "Realchk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 758 "Realchk.sqc"
  sqlaaloc(2,59,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[59];
#line 758 "Realchk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 758 "Realchk.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 758 "Realchk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 758 "Realchk.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 758 "Realchk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 758 "Realchk.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 758 "Realchk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 758 "Realchk.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 758 "Realchk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 758 "Realchk.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 758 "Realchk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 758 "Realchk.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 758 "Realchk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 758 "Realchk.sqc"
      sql_setdlist[6].sqldata = (void*)&knssu;
#line 758 "Realchk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 758 "Realchk.sqc"
      sql_setdlist[7].sqldata = (void*)&knssueda;
#line 758 "Realchk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 758 "Realchk.sqc"
      sql_setdlist[8].sqldata = (void*)utkymd;
#line 758 "Realchk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 12;
#line 758 "Realchk.sqc"
      sql_setdlist[9].sqldata = (void*)irino;
#line 758 "Realchk.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 758 "Realchk.sqc"
      sql_setdlist[10].sqldata = (void*)&iriketflg;
#line 758 "Realchk.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 758 "Realchk.sqc"
      sql_setdlist[11].sqldata = (void*)&zssdino;
#line 758 "Realchk.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 758 "Realchk.sqc"
      sql_setdlist[12].sqldata = (void*)trid;
#line 758 "Realchk.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 758 "Realchk.sqc"
      sql_setdlist[13].sqldata = (void*)&trpos;
#line 758 "Realchk.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 11;
#line 758 "Realchk.sqc"
      sql_setdlist[14].sqldata = (void*)asyrckid;
#line 758 "Realchk.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[15].sqltype = 500; sql_setdlist[15].sqllen = 2;
#line 758 "Realchk.sqc"
      sql_setdlist[15].sqldata = (void*)&asyrckpos;
#line 758 "Realchk.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 5;
#line 758 "Realchk.sqc"
      sql_setdlist[16].sqldata = (void*)bskkbn;
#line 758 "Realchk.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 8;
#line 758 "Realchk.sqc"
      sql_setdlist[17].sqldata = (void*)nbkmkcd;
#line 758 "Realchk.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 758 "Realchk.sqc"
      sql_setdlist[18].sqldata = (void*)&renjicflg;
#line 758 "Realchk.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 758 "Realchk.sqc"
      sql_setdlist[19].sqldata = (void*)&soukn1flg;
#line 758 "Realchk.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 758 "Realchk.sqc"
      sql_setdlist[20].sqldata = (void*)&kanrenflg;
#line 758 "Realchk.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 758 "Realchk.sqc"
      sql_setdlist[21].sqldata = (void*)&bunkkuflg;
#line 758 "Realchk.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 758 "Realchk.sqc"
      sql_setdlist[22].sqldata = (void*)&kesseiflg;
#line 758 "Realchk.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 758 "Realchk.sqc"
      sql_setdlist[23].sqldata = (void*)&rirekiflg;
#line 758 "Realchk.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 758 "Realchk.sqc"
      sql_setdlist[24].sqldata = (void*)&syougoflg;
#line 758 "Realchk.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 758 "Realchk.sqc"
      sql_setdlist[25].sqldata = (void*)&keisanflg;
#line 758 "Realchk.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 758 "Realchk.sqc"
      sql_setdlist[26].sqldata = (void*)&per100flg;
#line 758 "Realchk.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 758 "Realchk.sqc"
      sql_setdlist[27].sqldata = (void*)&tousekflg;
#line 758 "Realchk.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 758 "Realchk.sqc"
      sql_setdlist[28].sqldata = (void*)&kisyakflg;
#line 758 "Realchk.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 758 "Realchk.sqc"
      sql_setdlist[29].sqldata = (void*)&kouseiflg;
#line 758 "Realchk.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 758 "Realchk.sqc"
      sql_setdlist[30].sqldata = (void*)&syoungflg;
#line 758 "Realchk.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 758 "Realchk.sqc"
      sql_setdlist[31].sqldata = (void*)&soukn2flg;
#line 758 "Realchk.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 758 "Realchk.sqc"
      sql_setdlist[32].sqldata = (void*)&fukaptflg;
#line 758 "Realchk.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 758 "Realchk.sqc"
      sql_setdlist[33].sqldata = (void*)&yobiflg01;
#line 758 "Realchk.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 758 "Realchk.sqc"
      sql_setdlist[34].sqldata = (void*)&tobiflg02;
#line 758 "Realchk.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 758 "Realchk.sqc"
      sql_setdlist[35].sqldata = (void*)&yobiflg03;
#line 758 "Realchk.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 758 "Realchk.sqc"
      sql_setdlist[36].sqldata = (void*)&yobiflg04;
#line 758 "Realchk.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 758 "Realchk.sqc"
      sql_setdlist[37].sqldata = (void*)&yobiflg05;
#line 758 "Realchk.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 257;
#line 758 "Realchk.sqc"
      sql_setdlist[38].sqldata = (void*)renjicpara;
#line 758 "Realchk.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 257;
#line 758 "Realchk.sqc"
      sql_setdlist[39].sqldata = (void*)soukn1para;
#line 758 "Realchk.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 257;
#line 758 "Realchk.sqc"
      sql_setdlist[40].sqldata = (void*)kanrenpara;
#line 758 "Realchk.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 257;
#line 758 "Realchk.sqc"
      sql_setdlist[41].sqldata = (void*)bunkkupara;
#line 758 "Realchk.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 257;
#line 758 "Realchk.sqc"
      sql_setdlist[42].sqldata = (void*)kesseipara;
#line 758 "Realchk.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 257;
#line 758 "Realchk.sqc"
      sql_setdlist[43].sqldata = (void*)rirekipara;
#line 758 "Realchk.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 257;
#line 758 "Realchk.sqc"
      sql_setdlist[44].sqldata = (void*)syougopara;
#line 758 "Realchk.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 257;
#line 758 "Realchk.sqc"
      sql_setdlist[45].sqldata = (void*)keisanpara;
#line 758 "Realchk.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 257;
#line 758 "Realchk.sqc"
      sql_setdlist[46].sqldata = (void*)per100para;
#line 758 "Realchk.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 257;
#line 758 "Realchk.sqc"
      sql_setdlist[47].sqldata = (void*)tousekpara;
#line 758 "Realchk.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 257;
#line 758 "Realchk.sqc"
      sql_setdlist[48].sqldata = (void*)kisyakpara;
#line 758 "Realchk.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 257;
#line 758 "Realchk.sqc"
      sql_setdlist[49].sqldata = (void*)kouseipara;
#line 758 "Realchk.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 257;
#line 758 "Realchk.sqc"
      sql_setdlist[50].sqldata = (void*)syoungpara;
#line 758 "Realchk.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 257;
#line 758 "Realchk.sqc"
      sql_setdlist[51].sqldata = (void*)soukn2para;
#line 758 "Realchk.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 257;
#line 758 "Realchk.sqc"
      sql_setdlist[52].sqldata = (void*)fukaptpara;
#line 758 "Realchk.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 257;
#line 758 "Realchk.sqc"
      sql_setdlist[53].sqldata = (void*)yobipara01;
#line 758 "Realchk.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 257;
#line 758 "Realchk.sqc"
      sql_setdlist[54].sqldata = (void*)yobipara02;
#line 758 "Realchk.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 257;
#line 758 "Realchk.sqc"
      sql_setdlist[55].sqldata = (void*)yobipara03;
#line 758 "Realchk.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 257;
#line 758 "Realchk.sqc"
      sql_setdlist[56].sqldata = (void*)yobipara04;
#line 758 "Realchk.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 257;
#line 758 "Realchk.sqc"
      sql_setdlist[57].sqldata = (void*)yobipara05;
#line 758 "Realchk.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 758 "Realchk.sqc"
      sql_setdlist[58].sqltype = 460; sql_setdlist[58].sqllen = 27;
#line 758 "Realchk.sqc"
      sql_setdlist[58].sqldata = (void*)ksndh;
#line 758 "Realchk.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 758 "Realchk.sqc"
      sqlasetdata(2,0,59,sql_setdlist,0L,0L);
    }
#line 758 "Realchk.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 758 "Realchk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 758 "Realchk.sqc"
  sqlastop(0L);
}

#line 758 "Realchk.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 763 "Realchk.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbRealchkUpdate()
 *    REALCHK レコードを更新する
 * ■引数
 *    [I]  Realchk* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbRealchkUpdate( Realchk* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, RealchkArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 787 "Realchk.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 788 "Realchk.sqc"


    
/*
EXEC SQL UPDATE REALCHK
    SET (
		KNTKETFLG,
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
    ) = (
		:kntketflg,
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
#line 904 "Realchk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 904 "Realchk.sqc"
  sqlaaloc(2,59,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[59];
#line 904 "Realchk.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 904 "Realchk.sqc"
      sql_setdlist[0].sqldata = (void*)&kntketflg;
#line 904 "Realchk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 904 "Realchk.sqc"
      sql_setdlist[1].sqldata = (void*)utkymd;
#line 904 "Realchk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 12;
#line 904 "Realchk.sqc"
      sql_setdlist[2].sqldata = (void*)irino;
#line 904 "Realchk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 904 "Realchk.sqc"
      sql_setdlist[3].sqldata = (void*)&iriketflg;
#line 904 "Realchk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 904 "Realchk.sqc"
      sql_setdlist[4].sqldata = (void*)&zssdino;
#line 904 "Realchk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 904 "Realchk.sqc"
      sql_setdlist[5].sqldata = (void*)trid;
#line 904 "Realchk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 904 "Realchk.sqc"
      sql_setdlist[6].sqldata = (void*)&trpos;
#line 904 "Realchk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 904 "Realchk.sqc"
      sql_setdlist[7].sqldata = (void*)asyrckid;
#line 904 "Realchk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 904 "Realchk.sqc"
      sql_setdlist[8].sqldata = (void*)&asyrckpos;
#line 904 "Realchk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 5;
#line 904 "Realchk.sqc"
      sql_setdlist[9].sqldata = (void*)bskkbn;
#line 904 "Realchk.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 8;
#line 904 "Realchk.sqc"
      sql_setdlist[10].sqldata = (void*)nbkmkcd;
#line 904 "Realchk.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 904 "Realchk.sqc"
      sql_setdlist[11].sqldata = (void*)&renjicflg;
#line 904 "Realchk.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[12].sqltype = 452; sql_setdlist[12].sqllen = 1;
#line 904 "Realchk.sqc"
      sql_setdlist[12].sqldata = (void*)&soukn1flg;
#line 904 "Realchk.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 904 "Realchk.sqc"
      sql_setdlist[13].sqldata = (void*)&kanrenflg;
#line 904 "Realchk.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 904 "Realchk.sqc"
      sql_setdlist[14].sqldata = (void*)&bunkkuflg;
#line 904 "Realchk.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[15].sqltype = 452; sql_setdlist[15].sqllen = 1;
#line 904 "Realchk.sqc"
      sql_setdlist[15].sqldata = (void*)&kesseiflg;
#line 904 "Realchk.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 904 "Realchk.sqc"
      sql_setdlist[16].sqldata = (void*)&rirekiflg;
#line 904 "Realchk.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 904 "Realchk.sqc"
      sql_setdlist[17].sqldata = (void*)&syougoflg;
#line 904 "Realchk.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 904 "Realchk.sqc"
      sql_setdlist[18].sqldata = (void*)&keisanflg;
#line 904 "Realchk.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 904 "Realchk.sqc"
      sql_setdlist[19].sqldata = (void*)&per100flg;
#line 904 "Realchk.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 904 "Realchk.sqc"
      sql_setdlist[20].sqldata = (void*)&tousekflg;
#line 904 "Realchk.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 904 "Realchk.sqc"
      sql_setdlist[21].sqldata = (void*)&kisyakflg;
#line 904 "Realchk.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 904 "Realchk.sqc"
      sql_setdlist[22].sqldata = (void*)&kouseiflg;
#line 904 "Realchk.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 904 "Realchk.sqc"
      sql_setdlist[23].sqldata = (void*)&syoungflg;
#line 904 "Realchk.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 904 "Realchk.sqc"
      sql_setdlist[24].sqldata = (void*)&soukn2flg;
#line 904 "Realchk.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 904 "Realchk.sqc"
      sql_setdlist[25].sqldata = (void*)&fukaptflg;
#line 904 "Realchk.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 904 "Realchk.sqc"
      sql_setdlist[26].sqldata = (void*)&yobiflg01;
#line 904 "Realchk.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 904 "Realchk.sqc"
      sql_setdlist[27].sqldata = (void*)&tobiflg02;
#line 904 "Realchk.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 904 "Realchk.sqc"
      sql_setdlist[28].sqldata = (void*)&yobiflg03;
#line 904 "Realchk.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 904 "Realchk.sqc"
      sql_setdlist[29].sqldata = (void*)&yobiflg04;
#line 904 "Realchk.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 904 "Realchk.sqc"
      sql_setdlist[30].sqldata = (void*)&yobiflg05;
#line 904 "Realchk.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 257;
#line 904 "Realchk.sqc"
      sql_setdlist[31].sqldata = (void*)renjicpara;
#line 904 "Realchk.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 257;
#line 904 "Realchk.sqc"
      sql_setdlist[32].sqldata = (void*)soukn1para;
#line 904 "Realchk.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 257;
#line 904 "Realchk.sqc"
      sql_setdlist[33].sqldata = (void*)kanrenpara;
#line 904 "Realchk.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 257;
#line 904 "Realchk.sqc"
      sql_setdlist[34].sqldata = (void*)bunkkupara;
#line 904 "Realchk.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 257;
#line 904 "Realchk.sqc"
      sql_setdlist[35].sqldata = (void*)kesseipara;
#line 904 "Realchk.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 257;
#line 904 "Realchk.sqc"
      sql_setdlist[36].sqldata = (void*)rirekipara;
#line 904 "Realchk.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 257;
#line 904 "Realchk.sqc"
      sql_setdlist[37].sqldata = (void*)syougopara;
#line 904 "Realchk.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 257;
#line 904 "Realchk.sqc"
      sql_setdlist[38].sqldata = (void*)keisanpara;
#line 904 "Realchk.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 257;
#line 904 "Realchk.sqc"
      sql_setdlist[39].sqldata = (void*)per100para;
#line 904 "Realchk.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 257;
#line 904 "Realchk.sqc"
      sql_setdlist[40].sqldata = (void*)tousekpara;
#line 904 "Realchk.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 257;
#line 904 "Realchk.sqc"
      sql_setdlist[41].sqldata = (void*)kisyakpara;
#line 904 "Realchk.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 257;
#line 904 "Realchk.sqc"
      sql_setdlist[42].sqldata = (void*)kouseipara;
#line 904 "Realchk.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 257;
#line 904 "Realchk.sqc"
      sql_setdlist[43].sqldata = (void*)syoungpara;
#line 904 "Realchk.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 257;
#line 904 "Realchk.sqc"
      sql_setdlist[44].sqldata = (void*)soukn2para;
#line 904 "Realchk.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 257;
#line 904 "Realchk.sqc"
      sql_setdlist[45].sqldata = (void*)fukaptpara;
#line 904 "Realchk.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 257;
#line 904 "Realchk.sqc"
      sql_setdlist[46].sqldata = (void*)yobipara01;
#line 904 "Realchk.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 257;
#line 904 "Realchk.sqc"
      sql_setdlist[47].sqldata = (void*)yobipara02;
#line 904 "Realchk.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 257;
#line 904 "Realchk.sqc"
      sql_setdlist[48].sqldata = (void*)yobipara03;
#line 904 "Realchk.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 257;
#line 904 "Realchk.sqc"
      sql_setdlist[49].sqldata = (void*)yobipara04;
#line 904 "Realchk.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 257;
#line 904 "Realchk.sqc"
      sql_setdlist[50].sqldata = (void*)yobipara05;
#line 904 "Realchk.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 27;
#line 904 "Realchk.sqc"
      sql_setdlist[51].sqldata = (void*)ksndh;
#line 904 "Realchk.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 11;
#line 904 "Realchk.sqc"
      sql_setdlist[52].sqldata = (void*)knskisymd;
#line 904 "Realchk.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 11;
#line 904 "Realchk.sqc"
      sql_setdlist[53].sqldata = (void*)sriymd;
#line 904 "Realchk.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 14;
#line 904 "Realchk.sqc"
      sql_setdlist[54].sqldata = (void*)kntno;
#line 904 "Realchk.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 17;
#line 904 "Realchk.sqc"
      sql_setdlist[55].sqldata = (void*)knsgrp;
#line 904 "Realchk.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 8;
#line 904 "Realchk.sqc"
      sql_setdlist[56].sqldata = (void*)kmkcd;
#line 904 "Realchk.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[57].sqltype = 500; sql_setdlist[57].sqllen = 2;
#line 904 "Realchk.sqc"
      sql_setdlist[57].sqldata = (void*)&knssu;
#line 904 "Realchk.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 904 "Realchk.sqc"
      sql_setdlist[58].sqltype = 500; sql_setdlist[58].sqllen = 2;
#line 904 "Realchk.sqc"
      sql_setdlist[58].sqldata = (void*)&knssueda;
#line 904 "Realchk.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 904 "Realchk.sqc"
      sqlasetdata(2,0,59,sql_setdlist,0L,0L);
    }
#line 904 "Realchk.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 904 "Realchk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 904 "Realchk.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 904 "Realchk.sqc"
  sqlastop(0L);
}

#line 904 "Realchk.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 909 "Realchk.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 913 "Realchk.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbRealchkDelete()
 *    REALCHK レコードを削除する
 * ■引数
 *    [I]  Realchk* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbRealchkDelete( Realchk* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, RealchkArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 937 "Realchk.sqc"


    
/*
EXEC SQL DELETE FROM REALCHK
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
#line 947 "Realchk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 947 "Realchk.sqc"
  sqlaaloc(2,7,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 947 "Realchk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 947 "Realchk.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 947 "Realchk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 947 "Realchk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 947 "Realchk.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 947 "Realchk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 947 "Realchk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 947 "Realchk.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 947 "Realchk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 947 "Realchk.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 947 "Realchk.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 947 "Realchk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 947 "Realchk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 947 "Realchk.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 947 "Realchk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 947 "Realchk.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 947 "Realchk.sqc"
      sql_setdlist[5].sqldata = (void*)&knssu;
#line 947 "Realchk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 947 "Realchk.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 947 "Realchk.sqc"
      sql_setdlist[6].sqldata = (void*)&knssueda;
#line 947 "Realchk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 947 "Realchk.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 947 "Realchk.sqc"
  sqlacall((unsigned short)24,6,2,0,0L);
#line 947 "Realchk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 947 "Realchk.sqc"
  sqlastop(0L);
}

#line 947 "Realchk.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 952 "Realchk.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
