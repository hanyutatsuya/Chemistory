static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,84,65,84,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,51,53,90,75,74,78,77,32,0,0,0,0,0,0,0,0,
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


#line 1 "Kjnmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Kjnmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Kjnmst.h"
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


#line 24 "Kjnmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Kjnmst.sqc"

	char    kmkcd[8];
	char    kjno[4];
	char    kjsdino[3];
	char    zrcd[5];
	char    agerngkbn[3];
	char    etckbn[4];
	char    nichilw[6];
	char    nichihi[6];
	char    kjnmlw[9];
	char    kjnmhi[9];
	char    kjnflw[9];
	char    kjnfhi[9];
	char    kjnelw[9];
	char    kjnehi[9];
	char    genmlw[9];
	char    genmhi[9];
	char    genflw[9];
	char    genfhi[9];
	char    genelw[9];
	char    genehi[9];
	short   kjsstnksu;
	char    kjnmhkn[25];
	char    kjnmhkj[25];
	char    kjnfhkn[25];
	char    kjnfhkj[25];
	char    kjnohkn[25];
	char    kjnohkj[25];
	char    lwm1[9];
	char    lwm2[9];
	char    kjm1[9];
	char    kjm2[9];
	char    him1[9];
	char    him2[9];
	char    lwf1[9];
	char    lwf2[9];
	char    kjnnaf1[9];
	char    kjnnaf2[9];
	char    hif1[9];
	char    hif2[9];
	char    lwe1[9];
	char    lwe2[9];
	char    kje1[9];
	char    kje2[9];
	char    hie1[9];
	char    hie2[9];
	char    tankn[17];
	char    tankj[17];
	char    stjyken[61];
	char    kymstjn;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 83 "Kjnmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Kjnmst

BmlDMMInfo	KjnmstArray[] = {
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( kjno ),
	DMM_SSTRING( kjsdino ),
	DMM_SSTRING( zrcd ),
	DMM_SSTRING( agerngkbn ),
	DMM_SSTRING( etckbn ),
	DMM_SSTRING( nichilw ),
	DMM_SSTRING( nichihi ),
	DMM_SSTRING( kjnmlw ),
	DMM_SSTRING( kjnmhi ),
	DMM_SSTRING( kjnflw ),
	DMM_SSTRING( kjnfhi ),
	DMM_SSTRING( kjnelw ),
	DMM_SSTRING( kjnehi ),
	DMM_SSTRING( genmlw ),
	DMM_SSTRING( genmhi ),
	DMM_SSTRING( genflw ),
	DMM_SSTRING( genfhi ),
	DMM_SSTRING( genelw ),
	DMM_SSTRING( genehi ),
	DMM_SSHORT( kjsstnksu ),
	DMM_SSTRING( kjnmhkn ),
	DMM_SSTRING( kjnmhkj ),
	DMM_SSTRING( kjnfhkn ),
	DMM_SSTRING( kjnfhkj ),
	DMM_SSTRING( kjnohkn ),
	DMM_SSTRING( kjnohkj ),
	DMM_SSTRING( lwm1 ),
	DMM_SSTRING( lwm2 ),
	DMM_SSTRING( kjm1 ),
	DMM_SSTRING( kjm2 ),
	DMM_SSTRING( him1 ),
	DMM_SSTRING( him2 ),
	DMM_SSTRING( lwf1 ),
	DMM_SSTRING( lwf2 ),
	DMM_SSTRING( kjnnaf1 ),
	DMM_SSTRING( kjnnaf2 ),
	DMM_SSTRING( hif1 ),
	DMM_SSTRING( hif2 ),
	DMM_SSTRING( lwe1 ),
	DMM_SSTRING( lwe2 ),
	DMM_SSTRING( kje1 ),
	DMM_SSTRING( kje2 ),
	DMM_SSTRING( hie1 ),
	DMM_SSTRING( hie2 ),
	DMM_SSTRING( tankn ),
	DMM_SSTRING( tankj ),
	DMM_SSTRING( stjyken ),
	DMM_SCHAR( kymstjn ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKjnmstSelectAll()
 *    KJNMST レコード全件取得
 * ■引数
 *    [O]  Kjnmst** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKjnmstSelectAll( Kjnmst** arrayOut, int* numOut )
{
    Kjnmst*     array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 164 "Kjnmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KMKCD,
		KJNO,
		KJSDINO,
		ZRCD,
		AGERNGKBN,
		ETCKBN,
		NICHILW,
		NICHIHI,
		KJNMLW,
		KJNMHI,
		KJNFLW,
		KJNFHI,
		KJNELW,
		KJNEHI,
		GENMLW,
		GENMHI,
		GENFLW,
		GENFHI,
		GENELW,
		GENEHI,
		KJSSTNKSU,
		KJNMHKN,
		KJNMHKJ,
		KJNFHKN,
		KJNFHKJ,
		KJNOHKN,
		KJNOHKJ,
		LWM1,
		LWM2,
		KJM1,
		KJM2,
		HIM1,
		HIM2,
		LWF1,
		LWF2,
		KJNNAF1,
		KJNNAF2,
		HIF1,
		HIF2,
		LWE1,
		LWE2,
		KJE1,
		KJE2,
		HIE1,
		HIE2,
		TANKN,
		TANKJ,
		STJYKEN,
		KYMSTJN,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        KJNMST FOR READ ONLY;
*/

#line 222 "Kjnmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 224 "Kjnmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 224 "Kjnmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 224 "Kjnmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 224 "Kjnmst.sqc"
  sqlastop(0L);
}

#line 224 "Kjnmst.sqc"


    while( 1 ) {
        Kjnmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:kmkcd,
			:kjno,
			:kjsdino,
			:zrcd,
			:agerngkbn,
			:etckbn,
			:nichilw,
			:nichihi,
			:kjnmlw,
			:kjnmhi,
			:kjnflw,
			:kjnfhi,
			:kjnelw,
			:kjnehi,
			:genmlw,
			:genmhi,
			:genflw,
			:genfhi,
			:genelw,
			:genehi,
			:kjsstnksu,
			:kjnmhkn,
			:kjnmhkj,
			:kjnfhkn,
			:kjnfhkj,
			:kjnohkn,
			:kjnohkj,
			:lwm1,
			:lwm2,
			:kjm1,
			:kjm2,
			:him1,
			:him2,
			:lwf1,
			:lwf2,
			:kjnnaf1,
			:kjnnaf2,
			:hif1,
			:hif2,
			:lwe1,
			:lwe2,
			:kje1,
			:kje2,
			:hie1,
			:hie2,
			:tankn,
			:tankj,
			:stjyken,
			:kymstjn,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 282 "Kjnmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 282 "Kjnmst.sqc"
  sqlaaloc(3,53,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[53];
#line 282 "Kjnmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 282 "Kjnmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcd;
#line 282 "Kjnmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 4;
#line 282 "Kjnmst.sqc"
      sql_setdlist[1].sqldata = (void*)kjno;
#line 282 "Kjnmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 282 "Kjnmst.sqc"
      sql_setdlist[2].sqldata = (void*)kjsdino;
#line 282 "Kjnmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 282 "Kjnmst.sqc"
      sql_setdlist[3].sqldata = (void*)zrcd;
#line 282 "Kjnmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 3;
#line 282 "Kjnmst.sqc"
      sql_setdlist[4].sqldata = (void*)agerngkbn;
#line 282 "Kjnmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 4;
#line 282 "Kjnmst.sqc"
      sql_setdlist[5].sqldata = (void*)etckbn;
#line 282 "Kjnmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 6;
#line 282 "Kjnmst.sqc"
      sql_setdlist[6].sqldata = (void*)nichilw;
#line 282 "Kjnmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 6;
#line 282 "Kjnmst.sqc"
      sql_setdlist[7].sqldata = (void*)nichihi;
#line 282 "Kjnmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[8].sqldata = (void*)kjnmlw;
#line 282 "Kjnmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[9].sqldata = (void*)kjnmhi;
#line 282 "Kjnmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[10].sqldata = (void*)kjnflw;
#line 282 "Kjnmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[11].sqldata = (void*)kjnfhi;
#line 282 "Kjnmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[12].sqldata = (void*)kjnelw;
#line 282 "Kjnmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[13].sqldata = (void*)kjnehi;
#line 282 "Kjnmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[14].sqldata = (void*)genmlw;
#line 282 "Kjnmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[15].sqldata = (void*)genmhi;
#line 282 "Kjnmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[16].sqldata = (void*)genflw;
#line 282 "Kjnmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[17].sqldata = (void*)genfhi;
#line 282 "Kjnmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[18].sqldata = (void*)genelw;
#line 282 "Kjnmst.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[19].sqldata = (void*)genehi;
#line 282 "Kjnmst.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[20].sqltype = 500; sql_setdlist[20].sqllen = 2;
#line 282 "Kjnmst.sqc"
      sql_setdlist[20].sqldata = (void*)&kjsstnksu;
#line 282 "Kjnmst.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 25;
#line 282 "Kjnmst.sqc"
      sql_setdlist[21].sqldata = (void*)kjnmhkn;
#line 282 "Kjnmst.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 25;
#line 282 "Kjnmst.sqc"
      sql_setdlist[22].sqldata = (void*)kjnmhkj;
#line 282 "Kjnmst.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 25;
#line 282 "Kjnmst.sqc"
      sql_setdlist[23].sqldata = (void*)kjnfhkn;
#line 282 "Kjnmst.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 25;
#line 282 "Kjnmst.sqc"
      sql_setdlist[24].sqldata = (void*)kjnfhkj;
#line 282 "Kjnmst.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 25;
#line 282 "Kjnmst.sqc"
      sql_setdlist[25].sqldata = (void*)kjnohkn;
#line 282 "Kjnmst.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 25;
#line 282 "Kjnmst.sqc"
      sql_setdlist[26].sqldata = (void*)kjnohkj;
#line 282 "Kjnmst.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[27].sqldata = (void*)lwm1;
#line 282 "Kjnmst.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[28].sqldata = (void*)lwm2;
#line 282 "Kjnmst.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[29].sqldata = (void*)kjm1;
#line 282 "Kjnmst.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[30].sqldata = (void*)kjm2;
#line 282 "Kjnmst.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[31].sqldata = (void*)him1;
#line 282 "Kjnmst.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[32].sqldata = (void*)him2;
#line 282 "Kjnmst.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[33].sqldata = (void*)lwf1;
#line 282 "Kjnmst.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[34].sqldata = (void*)lwf2;
#line 282 "Kjnmst.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[35].sqldata = (void*)kjnnaf1;
#line 282 "Kjnmst.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[36].sqldata = (void*)kjnnaf2;
#line 282 "Kjnmst.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[37].sqldata = (void*)hif1;
#line 282 "Kjnmst.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[38].sqldata = (void*)hif2;
#line 282 "Kjnmst.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[39].sqldata = (void*)lwe1;
#line 282 "Kjnmst.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[40].sqldata = (void*)lwe2;
#line 282 "Kjnmst.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[41].sqldata = (void*)kje1;
#line 282 "Kjnmst.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[42].sqldata = (void*)kje2;
#line 282 "Kjnmst.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[43].sqldata = (void*)hie1;
#line 282 "Kjnmst.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[44].sqldata = (void*)hie2;
#line 282 "Kjnmst.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 17;
#line 282 "Kjnmst.sqc"
      sql_setdlist[45].sqldata = (void*)tankn;
#line 282 "Kjnmst.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 17;
#line 282 "Kjnmst.sqc"
      sql_setdlist[46].sqldata = (void*)tankj;
#line 282 "Kjnmst.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 61;
#line 282 "Kjnmst.sqc"
      sql_setdlist[47].sqldata = (void*)stjyken;
#line 282 "Kjnmst.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 282 "Kjnmst.sqc"
      sql_setdlist[48].sqldata = (void*)&kymstjn;
#line 282 "Kjnmst.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 11;
#line 282 "Kjnmst.sqc"
      sql_setdlist[49].sqldata = (void*)kaiymd;
#line 282 "Kjnmst.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 11;
#line 282 "Kjnmst.sqc"
      sql_setdlist[50].sqldata = (void*)haiymd;
#line 282 "Kjnmst.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 9;
#line 282 "Kjnmst.sqc"
      sql_setdlist[51].sqldata = (void*)hnktntid;
#line 282 "Kjnmst.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 27;
#line 282 "Kjnmst.sqc"
      sql_setdlist[52].sqldata = (void*)ksndh;
#line 282 "Kjnmst.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 282 "Kjnmst.sqc"
      sqlasetdata(3,0,53,sql_setdlist,0L,0L);
    }
#line 282 "Kjnmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 282 "Kjnmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 282 "Kjnmst.sqc"
  sqlastop(0L);
}

#line 282 "Kjnmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kjnmst*)ZbmlRealloc( array,
                                    sizeof( Kjnmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kjnmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KjnmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 297 "Kjnmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 297 "Kjnmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 297 "Kjnmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 297 "Kjnmst.sqc"
  sqlastop(0L);
}

#line 297 "Kjnmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 305 "Kjnmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKjnmstSelectKey()
 *    KJNMST レコードKey条件取得
 * ■引数
 *    [I]  Kjnmst* pKey       取得するレコードのキー
 *    [O]  Kjnmst** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKjnmstSelectKey( Kjnmst* pKey, Kjnmst** arrayOut, int* numOut )
{
    Kjnmst*     array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KjnmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 331 "Kjnmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KMKCD,
		KJNO,
		KJSDINO,
		ZRCD,
		AGERNGKBN,
		ETCKBN,
		NICHILW,
		NICHIHI,
		KJNMLW,
		KJNMHI,
		KJNFLW,
		KJNFHI,
		KJNELW,
		KJNEHI,
		GENMLW,
		GENMHI,
		GENFLW,
		GENFHI,
		GENELW,
		GENEHI,
		KJSSTNKSU,
		KJNMHKN,
		KJNMHKJ,
		KJNFHKN,
		KJNFHKJ,
		KJNOHKN,
		KJNOHKJ,
		LWM1,
		LWM2,
		KJM1,
		KJM2,
		HIM1,
		HIM2,
		LWF1,
		LWF2,
		KJNNAF1,
		KJNNAF2,
		HIF1,
		HIF2,
		LWE1,
		LWE2,
		KJE1,
		KJE2,
		HIE1,
		HIE2,
		TANKN,
		TANKJ,
		STJYKEN,
		KYMSTJN,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        KJNMST
    WHERE
		KMKCD = :kmkcd AND
		KJNO = :kjno AND
		KJSDINO       = :kjsdino       AND
		ZRCD = :zrcd AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 395 "Kjnmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 397 "Kjnmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 397 "Kjnmst.sqc"
  sqlaaloc(2,5,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 397 "Kjnmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 397 "Kjnmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcd;
#line 397 "Kjnmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 397 "Kjnmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 4;
#line 397 "Kjnmst.sqc"
      sql_setdlist[1].sqldata = (void*)kjno;
#line 397 "Kjnmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 397 "Kjnmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 397 "Kjnmst.sqc"
      sql_setdlist[2].sqldata = (void*)kjsdino;
#line 397 "Kjnmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 397 "Kjnmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 397 "Kjnmst.sqc"
      sql_setdlist[3].sqldata = (void*)zrcd;
#line 397 "Kjnmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 397 "Kjnmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 397 "Kjnmst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 397 "Kjnmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 397 "Kjnmst.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 397 "Kjnmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 397 "Kjnmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 397 "Kjnmst.sqc"
  sqlastop(0L);
}

#line 397 "Kjnmst.sqc"


    while( 1 ) {
        Kjnmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:kmkcd,
			:kjno,
			:kjsdino,
			:zrcd,
			:agerngkbn,
			:etckbn,
			:nichilw,
			:nichihi,
			:kjnmlw,
			:kjnmhi,
			:kjnflw,
			:kjnfhi,
			:kjnelw,
			:kjnehi,
			:genmlw,
			:genmhi,
			:genflw,
			:genfhi,
			:genelw,
			:genehi,
			:kjsstnksu,
			:kjnmhkn,
			:kjnmhkj,
			:kjnfhkn,
			:kjnfhkj,
			:kjnohkn,
			:kjnohkj,
			:lwm1,
			:lwm2,
			:kjm1,
			:kjm2,
			:him1,
			:him2,
			:lwf1,
			:lwf2,
			:kjnnaf1,
			:kjnnaf2,
			:hif1,
			:hif2,
			:lwe1,
			:lwe2,
			:kje1,
			:kje2,
			:hie1,
			:hie2,
			:tankn,
			:tankj,
			:stjyken,
			:kymstjn,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 455 "Kjnmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 455 "Kjnmst.sqc"
  sqlaaloc(3,53,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[53];
#line 455 "Kjnmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 455 "Kjnmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcd;
#line 455 "Kjnmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 4;
#line 455 "Kjnmst.sqc"
      sql_setdlist[1].sqldata = (void*)kjno;
#line 455 "Kjnmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 455 "Kjnmst.sqc"
      sql_setdlist[2].sqldata = (void*)kjsdino;
#line 455 "Kjnmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 455 "Kjnmst.sqc"
      sql_setdlist[3].sqldata = (void*)zrcd;
#line 455 "Kjnmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 3;
#line 455 "Kjnmst.sqc"
      sql_setdlist[4].sqldata = (void*)agerngkbn;
#line 455 "Kjnmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 4;
#line 455 "Kjnmst.sqc"
      sql_setdlist[5].sqldata = (void*)etckbn;
#line 455 "Kjnmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 6;
#line 455 "Kjnmst.sqc"
      sql_setdlist[6].sqldata = (void*)nichilw;
#line 455 "Kjnmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 6;
#line 455 "Kjnmst.sqc"
      sql_setdlist[7].sqldata = (void*)nichihi;
#line 455 "Kjnmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[8].sqldata = (void*)kjnmlw;
#line 455 "Kjnmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[9].sqldata = (void*)kjnmhi;
#line 455 "Kjnmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[10].sqldata = (void*)kjnflw;
#line 455 "Kjnmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[11].sqldata = (void*)kjnfhi;
#line 455 "Kjnmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[12].sqldata = (void*)kjnelw;
#line 455 "Kjnmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[13].sqldata = (void*)kjnehi;
#line 455 "Kjnmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[14].sqldata = (void*)genmlw;
#line 455 "Kjnmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[15].sqldata = (void*)genmhi;
#line 455 "Kjnmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[16].sqldata = (void*)genflw;
#line 455 "Kjnmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[17].sqldata = (void*)genfhi;
#line 455 "Kjnmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[18].sqldata = (void*)genelw;
#line 455 "Kjnmst.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[19].sqldata = (void*)genehi;
#line 455 "Kjnmst.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[20].sqltype = 500; sql_setdlist[20].sqllen = 2;
#line 455 "Kjnmst.sqc"
      sql_setdlist[20].sqldata = (void*)&kjsstnksu;
#line 455 "Kjnmst.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 25;
#line 455 "Kjnmst.sqc"
      sql_setdlist[21].sqldata = (void*)kjnmhkn;
#line 455 "Kjnmst.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 25;
#line 455 "Kjnmst.sqc"
      sql_setdlist[22].sqldata = (void*)kjnmhkj;
#line 455 "Kjnmst.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 25;
#line 455 "Kjnmst.sqc"
      sql_setdlist[23].sqldata = (void*)kjnfhkn;
#line 455 "Kjnmst.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 25;
#line 455 "Kjnmst.sqc"
      sql_setdlist[24].sqldata = (void*)kjnfhkj;
#line 455 "Kjnmst.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 25;
#line 455 "Kjnmst.sqc"
      sql_setdlist[25].sqldata = (void*)kjnohkn;
#line 455 "Kjnmst.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 25;
#line 455 "Kjnmst.sqc"
      sql_setdlist[26].sqldata = (void*)kjnohkj;
#line 455 "Kjnmst.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[27].sqldata = (void*)lwm1;
#line 455 "Kjnmst.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[28].sqldata = (void*)lwm2;
#line 455 "Kjnmst.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[29].sqldata = (void*)kjm1;
#line 455 "Kjnmst.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[30].sqldata = (void*)kjm2;
#line 455 "Kjnmst.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[31].sqldata = (void*)him1;
#line 455 "Kjnmst.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[32].sqldata = (void*)him2;
#line 455 "Kjnmst.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[33].sqldata = (void*)lwf1;
#line 455 "Kjnmst.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[34].sqldata = (void*)lwf2;
#line 455 "Kjnmst.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[35].sqldata = (void*)kjnnaf1;
#line 455 "Kjnmst.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[36].sqldata = (void*)kjnnaf2;
#line 455 "Kjnmst.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[37].sqldata = (void*)hif1;
#line 455 "Kjnmst.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[38].sqldata = (void*)hif2;
#line 455 "Kjnmst.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[39].sqldata = (void*)lwe1;
#line 455 "Kjnmst.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[40].sqldata = (void*)lwe2;
#line 455 "Kjnmst.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[41].sqldata = (void*)kje1;
#line 455 "Kjnmst.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[42].sqldata = (void*)kje2;
#line 455 "Kjnmst.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[43].sqldata = (void*)hie1;
#line 455 "Kjnmst.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[44].sqldata = (void*)hie2;
#line 455 "Kjnmst.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 17;
#line 455 "Kjnmst.sqc"
      sql_setdlist[45].sqldata = (void*)tankn;
#line 455 "Kjnmst.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 17;
#line 455 "Kjnmst.sqc"
      sql_setdlist[46].sqldata = (void*)tankj;
#line 455 "Kjnmst.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 61;
#line 455 "Kjnmst.sqc"
      sql_setdlist[47].sqldata = (void*)stjyken;
#line 455 "Kjnmst.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 455 "Kjnmst.sqc"
      sql_setdlist[48].sqldata = (void*)&kymstjn;
#line 455 "Kjnmst.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 11;
#line 455 "Kjnmst.sqc"
      sql_setdlist[49].sqldata = (void*)kaiymd;
#line 455 "Kjnmst.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 11;
#line 455 "Kjnmst.sqc"
      sql_setdlist[50].sqldata = (void*)haiymd;
#line 455 "Kjnmst.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 9;
#line 455 "Kjnmst.sqc"
      sql_setdlist[51].sqldata = (void*)hnktntid;
#line 455 "Kjnmst.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 27;
#line 455 "Kjnmst.sqc"
      sql_setdlist[52].sqldata = (void*)ksndh;
#line 455 "Kjnmst.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 455 "Kjnmst.sqc"
      sqlasetdata(3,0,53,sql_setdlist,0L,0L);
    }
#line 455 "Kjnmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 455 "Kjnmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 455 "Kjnmst.sqc"
  sqlastop(0L);
}

#line 455 "Kjnmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kjnmst*)ZbmlRealloc( array,
                                    sizeof( Kjnmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kjnmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KjnmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 470 "Kjnmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 470 "Kjnmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 470 "Kjnmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 470 "Kjnmst.sqc"
  sqlastop(0L);
}

#line 470 "Kjnmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 478 "Kjnmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKjnmstInsert()
 *    KJNMST レコードを挿入する
 * ■引数
 *    [I]  Kjnmst* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKjnmstInsert( Kjnmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KjnmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 501 "Kjnmst.sqc"


    
/*
EXEC SQL INSERT INTO KJNMST
    (
		KMKCD,
		KJNO,
		KJSDINO,
		ZRCD,
		AGERNGKBN,
		ETCKBN,
		NICHILW,
		NICHIHI,
		KJNMLW,
		KJNMHI,
		KJNFLW,
		KJNFHI,
		KJNELW,
		KJNEHI,
		GENMLW,
		GENMHI,
		GENFLW,
		GENFHI,
		GENELW,
		GENEHI,
		KJSSTNKSU,
		KJNMHKN,
		KJNMHKJ,
		KJNFHKN,
		KJNFHKJ,
		KJNOHKN,
		KJNOHKJ,
		LWM1,
		LWM2,
		KJM1,
		KJM2,
		HIM1,
		HIM2,
		LWF1,
		LWF2,
		KJNNAF1,
		KJNNAF2,
		HIF1,
		HIF2,
		LWE1,
		LWE2,
		KJE1,
		KJE2,
		HIE1,
		HIE2,
		TANKN,
		TANKJ,
		STJYKEN,
		KYMSTJN,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:kmkcd,
		:kjno,
		:kjsdino,
		:zrcd,
		:agerngkbn,
		:etckbn,
		:nichilw,
		:nichihi,
		:kjnmlw,
		:kjnmhi,
		:kjnflw,
		:kjnfhi,
		:kjnelw,
		:kjnehi,
		:genmlw,
		:genmhi,
		:genflw,
		:genfhi,
		:genelw,
		:genehi,
		:kjsstnksu,
		:kjnmhkn,
		:kjnmhkj,
		:kjnfhkn,
		:kjnfhkj,
		:kjnohkn,
		:kjnohkj,
		:lwm1,
		:lwm2,
		:kjm1,
		:kjm2,
		:him1,
		:him2,
		:lwf1,
		:lwf2,
		:kjnnaf1,
		:kjnnaf2,
		:hif1,
		:hif2,
		:lwe1,
		:lwe2,
		:kje1,
		:kje2,
		:hie1,
		:hie2,
		:tankn,
		:tankj,
		:stjyken,
		:kymstjn,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 612 "Kjnmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 612 "Kjnmst.sqc"
  sqlaaloc(2,53,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[53];
#line 612 "Kjnmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 612 "Kjnmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcd;
#line 612 "Kjnmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 4;
#line 612 "Kjnmst.sqc"
      sql_setdlist[1].sqldata = (void*)kjno;
#line 612 "Kjnmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 612 "Kjnmst.sqc"
      sql_setdlist[2].sqldata = (void*)kjsdino;
#line 612 "Kjnmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 612 "Kjnmst.sqc"
      sql_setdlist[3].sqldata = (void*)zrcd;
#line 612 "Kjnmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 3;
#line 612 "Kjnmst.sqc"
      sql_setdlist[4].sqldata = (void*)agerngkbn;
#line 612 "Kjnmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 4;
#line 612 "Kjnmst.sqc"
      sql_setdlist[5].sqldata = (void*)etckbn;
#line 612 "Kjnmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 6;
#line 612 "Kjnmst.sqc"
      sql_setdlist[6].sqldata = (void*)nichilw;
#line 612 "Kjnmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 6;
#line 612 "Kjnmst.sqc"
      sql_setdlist[7].sqldata = (void*)nichihi;
#line 612 "Kjnmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[8].sqldata = (void*)kjnmlw;
#line 612 "Kjnmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[9].sqldata = (void*)kjnmhi;
#line 612 "Kjnmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[10].sqldata = (void*)kjnflw;
#line 612 "Kjnmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[11].sqldata = (void*)kjnfhi;
#line 612 "Kjnmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[12].sqldata = (void*)kjnelw;
#line 612 "Kjnmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[13].sqldata = (void*)kjnehi;
#line 612 "Kjnmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[14].sqldata = (void*)genmlw;
#line 612 "Kjnmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[15].sqldata = (void*)genmhi;
#line 612 "Kjnmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[16].sqldata = (void*)genflw;
#line 612 "Kjnmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[17].sqldata = (void*)genfhi;
#line 612 "Kjnmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[18].sqldata = (void*)genelw;
#line 612 "Kjnmst.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[19].sqldata = (void*)genehi;
#line 612 "Kjnmst.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[20].sqltype = 500; sql_setdlist[20].sqllen = 2;
#line 612 "Kjnmst.sqc"
      sql_setdlist[20].sqldata = (void*)&kjsstnksu;
#line 612 "Kjnmst.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 25;
#line 612 "Kjnmst.sqc"
      sql_setdlist[21].sqldata = (void*)kjnmhkn;
#line 612 "Kjnmst.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 25;
#line 612 "Kjnmst.sqc"
      sql_setdlist[22].sqldata = (void*)kjnmhkj;
#line 612 "Kjnmst.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 25;
#line 612 "Kjnmst.sqc"
      sql_setdlist[23].sqldata = (void*)kjnfhkn;
#line 612 "Kjnmst.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 25;
#line 612 "Kjnmst.sqc"
      sql_setdlist[24].sqldata = (void*)kjnfhkj;
#line 612 "Kjnmst.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 25;
#line 612 "Kjnmst.sqc"
      sql_setdlist[25].sqldata = (void*)kjnohkn;
#line 612 "Kjnmst.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 25;
#line 612 "Kjnmst.sqc"
      sql_setdlist[26].sqldata = (void*)kjnohkj;
#line 612 "Kjnmst.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[27].sqldata = (void*)lwm1;
#line 612 "Kjnmst.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[28].sqldata = (void*)lwm2;
#line 612 "Kjnmst.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[29].sqldata = (void*)kjm1;
#line 612 "Kjnmst.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[30].sqldata = (void*)kjm2;
#line 612 "Kjnmst.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[31].sqldata = (void*)him1;
#line 612 "Kjnmst.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[32].sqldata = (void*)him2;
#line 612 "Kjnmst.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[33].sqldata = (void*)lwf1;
#line 612 "Kjnmst.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[34].sqldata = (void*)lwf2;
#line 612 "Kjnmst.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[35].sqldata = (void*)kjnnaf1;
#line 612 "Kjnmst.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[36].sqldata = (void*)kjnnaf2;
#line 612 "Kjnmst.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[37].sqldata = (void*)hif1;
#line 612 "Kjnmst.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[38].sqldata = (void*)hif2;
#line 612 "Kjnmst.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[39].sqldata = (void*)lwe1;
#line 612 "Kjnmst.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[40].sqldata = (void*)lwe2;
#line 612 "Kjnmst.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[41].sqldata = (void*)kje1;
#line 612 "Kjnmst.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[42].sqldata = (void*)kje2;
#line 612 "Kjnmst.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[43].sqldata = (void*)hie1;
#line 612 "Kjnmst.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[44].sqldata = (void*)hie2;
#line 612 "Kjnmst.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 17;
#line 612 "Kjnmst.sqc"
      sql_setdlist[45].sqldata = (void*)tankn;
#line 612 "Kjnmst.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 17;
#line 612 "Kjnmst.sqc"
      sql_setdlist[46].sqldata = (void*)tankj;
#line 612 "Kjnmst.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 61;
#line 612 "Kjnmst.sqc"
      sql_setdlist[47].sqldata = (void*)stjyken;
#line 612 "Kjnmst.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 612 "Kjnmst.sqc"
      sql_setdlist[48].sqldata = (void*)&kymstjn;
#line 612 "Kjnmst.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 11;
#line 612 "Kjnmst.sqc"
      sql_setdlist[49].sqldata = (void*)kaiymd;
#line 612 "Kjnmst.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 11;
#line 612 "Kjnmst.sqc"
      sql_setdlist[50].sqldata = (void*)haiymd;
#line 612 "Kjnmst.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 9;
#line 612 "Kjnmst.sqc"
      sql_setdlist[51].sqldata = (void*)hnktntid;
#line 612 "Kjnmst.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 27;
#line 612 "Kjnmst.sqc"
      sql_setdlist[52].sqldata = (void*)ksndh;
#line 612 "Kjnmst.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 612 "Kjnmst.sqc"
      sqlasetdata(2,0,53,sql_setdlist,0L,0L);
    }
#line 612 "Kjnmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 612 "Kjnmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 612 "Kjnmst.sqc"
  sqlastop(0L);
}

#line 612 "Kjnmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 617 "Kjnmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKjnmstUpdate()
 *    KJNMST レコードを更新する
 * ■引数
 *    [I]  Kjnmst* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKjnmstUpdate( Kjnmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KjnmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 641 "Kjnmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 642 "Kjnmst.sqc"


    
/*
EXEC SQL UPDATE KJNMST
    SET (
		AGERNGKBN,
		ETCKBN,
		NICHILW,
		NICHIHI,
		KJNMLW,
		KJNMHI,
		KJNFLW,
		KJNFHI,
		KJNELW,
		KJNEHI,
		GENMLW,
		GENMHI,
		GENFLW,
		GENFHI,
		GENELW,
		GENEHI,
		KJSSTNKSU,
		KJNMHKN,
		KJNMHKJ,
		KJNFHKN,
		KJNFHKJ,
		KJNOHKN,
		KJNOHKJ,
		LWM1,
		LWM2,
		KJM1,
		KJM2,
		HIM1,
		HIM2,
		LWF1,
		LWF2,
		KJNNAF1,
		KJNNAF2,
		HIF1,
		HIF2,
		LWE1,
		LWE2,
		KJE1,
		KJE2,
		HIE1,
		HIE2,
		TANKN,
		TANKJ,
		STJYKEN,
		KYMSTJN,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:agerngkbn,
		:etckbn,
		:nichilw,
		:nichihi,
		:kjnmlw,
		:kjnmhi,
		:kjnflw,
		:kjnfhi,
		:kjnelw,
		:kjnehi,
		:genmlw,
		:genmhi,
		:genflw,
		:genfhi,
		:genelw,
		:genehi,
		:kjsstnksu,
		:kjnmhkn,
		:kjnmhkj,
		:kjnfhkn,
		:kjnfhkj,
		:kjnohkn,
		:kjnohkj,
		:lwm1,
		:lwm2,
		:kjm1,
		:kjm2,
		:him1,
		:him2,
		:lwf1,
		:lwf2,
		:kjnnaf1,
		:kjnnaf2,
		:hif1,
		:hif2,
		:lwe1,
		:lwe2,
		:kje1,
		:kje2,
		:hie1,
		:hie2,
		:tankn,
		:tankj,
		:stjyken,
		:kymstjn,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		KMKCD = :kmkcd AND
		KJNO = :kjno AND
		KJSDINO       = :kjsdino       AND
		ZRCD = :zrcd AND
		KAIYMD = :kaiymd;
*/

{
#line 748 "Kjnmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 748 "Kjnmst.sqc"
  sqlaaloc(2,53,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[53];
#line 748 "Kjnmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 748 "Kjnmst.sqc"
      sql_setdlist[0].sqldata = (void*)agerngkbn;
#line 748 "Kjnmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 4;
#line 748 "Kjnmst.sqc"
      sql_setdlist[1].sqldata = (void*)etckbn;
#line 748 "Kjnmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 6;
#line 748 "Kjnmst.sqc"
      sql_setdlist[2].sqldata = (void*)nichilw;
#line 748 "Kjnmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 6;
#line 748 "Kjnmst.sqc"
      sql_setdlist[3].sqldata = (void*)nichihi;
#line 748 "Kjnmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[4].sqldata = (void*)kjnmlw;
#line 748 "Kjnmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[5].sqldata = (void*)kjnmhi;
#line 748 "Kjnmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[6].sqldata = (void*)kjnflw;
#line 748 "Kjnmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[7].sqldata = (void*)kjnfhi;
#line 748 "Kjnmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[8].sqldata = (void*)kjnelw;
#line 748 "Kjnmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[9].sqldata = (void*)kjnehi;
#line 748 "Kjnmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[10].sqldata = (void*)genmlw;
#line 748 "Kjnmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[11].sqldata = (void*)genmhi;
#line 748 "Kjnmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[12].sqldata = (void*)genflw;
#line 748 "Kjnmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[13].sqldata = (void*)genfhi;
#line 748 "Kjnmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[14].sqldata = (void*)genelw;
#line 748 "Kjnmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[15].sqldata = (void*)genehi;
#line 748 "Kjnmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[16].sqltype = 500; sql_setdlist[16].sqllen = 2;
#line 748 "Kjnmst.sqc"
      sql_setdlist[16].sqldata = (void*)&kjsstnksu;
#line 748 "Kjnmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 25;
#line 748 "Kjnmst.sqc"
      sql_setdlist[17].sqldata = (void*)kjnmhkn;
#line 748 "Kjnmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 25;
#line 748 "Kjnmst.sqc"
      sql_setdlist[18].sqldata = (void*)kjnmhkj;
#line 748 "Kjnmst.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 25;
#line 748 "Kjnmst.sqc"
      sql_setdlist[19].sqldata = (void*)kjnfhkn;
#line 748 "Kjnmst.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 25;
#line 748 "Kjnmst.sqc"
      sql_setdlist[20].sqldata = (void*)kjnfhkj;
#line 748 "Kjnmst.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 25;
#line 748 "Kjnmst.sqc"
      sql_setdlist[21].sqldata = (void*)kjnohkn;
#line 748 "Kjnmst.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 25;
#line 748 "Kjnmst.sqc"
      sql_setdlist[22].sqldata = (void*)kjnohkj;
#line 748 "Kjnmst.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[23].sqldata = (void*)lwm1;
#line 748 "Kjnmst.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[24].sqldata = (void*)lwm2;
#line 748 "Kjnmst.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[25].sqldata = (void*)kjm1;
#line 748 "Kjnmst.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[26].sqldata = (void*)kjm2;
#line 748 "Kjnmst.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[27].sqldata = (void*)him1;
#line 748 "Kjnmst.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[28].sqldata = (void*)him2;
#line 748 "Kjnmst.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[29].sqldata = (void*)lwf1;
#line 748 "Kjnmst.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[30].sqldata = (void*)lwf2;
#line 748 "Kjnmst.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[31].sqldata = (void*)kjnnaf1;
#line 748 "Kjnmst.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[32].sqldata = (void*)kjnnaf2;
#line 748 "Kjnmst.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[33].sqldata = (void*)hif1;
#line 748 "Kjnmst.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[34].sqldata = (void*)hif2;
#line 748 "Kjnmst.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[35].sqldata = (void*)lwe1;
#line 748 "Kjnmst.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[36].sqldata = (void*)lwe2;
#line 748 "Kjnmst.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[37].sqldata = (void*)kje1;
#line 748 "Kjnmst.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[38].sqldata = (void*)kje2;
#line 748 "Kjnmst.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[39].sqldata = (void*)hie1;
#line 748 "Kjnmst.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[40].sqldata = (void*)hie2;
#line 748 "Kjnmst.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 17;
#line 748 "Kjnmst.sqc"
      sql_setdlist[41].sqldata = (void*)tankn;
#line 748 "Kjnmst.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 17;
#line 748 "Kjnmst.sqc"
      sql_setdlist[42].sqldata = (void*)tankj;
#line 748 "Kjnmst.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 61;
#line 748 "Kjnmst.sqc"
      sql_setdlist[43].sqldata = (void*)stjyken;
#line 748 "Kjnmst.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 748 "Kjnmst.sqc"
      sql_setdlist[44].sqldata = (void*)&kymstjn;
#line 748 "Kjnmst.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 11;
#line 748 "Kjnmst.sqc"
      sql_setdlist[45].sqldata = (void*)haiymd;
#line 748 "Kjnmst.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 9;
#line 748 "Kjnmst.sqc"
      sql_setdlist[46].sqldata = (void*)hnktntid;
#line 748 "Kjnmst.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 27;
#line 748 "Kjnmst.sqc"
      sql_setdlist[47].sqldata = (void*)ksndh;
#line 748 "Kjnmst.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 8;
#line 748 "Kjnmst.sqc"
      sql_setdlist[48].sqldata = (void*)kmkcd;
#line 748 "Kjnmst.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 4;
#line 748 "Kjnmst.sqc"
      sql_setdlist[49].sqldata = (void*)kjno;
#line 748 "Kjnmst.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 3;
#line 748 "Kjnmst.sqc"
      sql_setdlist[50].sqldata = (void*)kjsdino;
#line 748 "Kjnmst.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 5;
#line 748 "Kjnmst.sqc"
      sql_setdlist[51].sqldata = (void*)zrcd;
#line 748 "Kjnmst.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 11;
#line 748 "Kjnmst.sqc"
      sql_setdlist[52].sqldata = (void*)kaiymd;
#line 748 "Kjnmst.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 748 "Kjnmst.sqc"
      sqlasetdata(2,0,53,sql_setdlist,0L,0L);
    }
#line 748 "Kjnmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 748 "Kjnmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 748 "Kjnmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 748 "Kjnmst.sqc"
  sqlastop(0L);
}

#line 748 "Kjnmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 753 "Kjnmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 757 "Kjnmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKjnmstDelete()
 *    KJNMST レコードを削除する
 * ■引数
 *    [I]  Kjnmst* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKjnmstDelete( Kjnmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KjnmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 781 "Kjnmst.sqc"


    
/*
EXEC SQL DELETE FROM KJNMST
    WHERE
		KMKCD = :kmkcd AND
		KJNO = :kjno AND
		KJSDINO       = :kjsdino       AND
		ZRCD = :zrcd AND
		KAIYMD = :kaiymd;
*/

{
#line 789 "Kjnmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 789 "Kjnmst.sqc"
  sqlaaloc(2,5,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 789 "Kjnmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 789 "Kjnmst.sqc"
      sql_setdlist[0].sqldata = (void*)kmkcd;
#line 789 "Kjnmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 789 "Kjnmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 4;
#line 789 "Kjnmst.sqc"
      sql_setdlist[1].sqldata = (void*)kjno;
#line 789 "Kjnmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 789 "Kjnmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 789 "Kjnmst.sqc"
      sql_setdlist[2].sqldata = (void*)kjsdino;
#line 789 "Kjnmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 789 "Kjnmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 5;
#line 789 "Kjnmst.sqc"
      sql_setdlist[3].sqldata = (void*)zrcd;
#line 789 "Kjnmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 789 "Kjnmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 789 "Kjnmst.sqc"
      sql_setdlist[4].sqldata = (void*)kaiymd;
#line 789 "Kjnmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 789 "Kjnmst.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 789 "Kjnmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 789 "Kjnmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 789 "Kjnmst.sqc"
  sqlastop(0L);
}

#line 789 "Kjnmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 794 "Kjnmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
