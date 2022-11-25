static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,105,66,98,75,85,97,68,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,50,76,68,49,48,52,32,32,0,0,0,0,0,0,0,0,
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


#line 1 "LD104Sysknrmst.sqc"
/**********************************************************************
 *
 *	 ＢＭＬ様向け検査システム
 *
 *	 システム名：次世代
 *	 ファイル名： LD104Sysknrmst.sqc
 *	 機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.	 Date		   Name		   History
 * --------------------------------------------------------------------
 **********************************************************************/
#include <stdio.h>

#include "LD104Sysknrmst.h"
#include "bml_misc.h"
#include "bml_db.h"
#include "bml_dmm.h"

#define ALLOC_UNIT	  1


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 23 "LD104Sysknrmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 28 "LD104Sysknrmst.sqc"

	char	lbcd[4];
	char	sateid[4];
	char	kjnsriymd[11];
	char	kkkjsriymd[11];
	char	nxirisriymd[11];
	char	ncnsksriymd[11];
	char	nxbchsriymd[11];
	char	iriendflg;
	char	irienddh[27];
	char	nskendflg;
	char	nskenddh[27];
	char	bchendflg;
	char	bchend0dh[27];
	char	bchend1dh[27];
	char	bchend2dh[27];
	char	bchend3dh[27];
	char	bchend4dh[27];
	char	unyflg;
	sqlint32  ssntubn;
	char	sriknflg01;
	char	sriknflg02;
	char	sriknflg03;
	char	sriknflg04;
	char	sriknflg05;
	char	sriknflg06;
	char	sriknflg07;
	char	sriknflg08;
	char	sriknflg09;
	char	sriknflg10;
	char	sriknflg11;
	char	sriknflg12;
	char	sriknflg13;
	char	sriknflg14;
	char	sriknflg15;
	char	sriknflg16;
	char	sriknflg17;
	char	sriknflg18;
	char	sriknflg19;
	char	sriknflg20;
	char	ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 69 "LD104Sysknrmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT  Sysknrmst

BmlDMMInfo  SysknrmstArray[] = {
	DMM_SSTRING( lbcd ),
	DMM_SSTRING( sateid ),
	DMM_SDATE( kjnsriymd ),
	DMM_SDATE( kkkjsriymd ),
	DMM_SDATE( nxirisriymd ),
	DMM_SDATE( ncnsksriymd ),
	DMM_SDATE( nxbchsriymd ),
	DMM_SCHAR( iriendflg ),
	DMM_STIMESTAMP( irienddh ),
	DMM_SCHAR( nskendflg ),
	DMM_STIMESTAMP( nskenddh ),
	DMM_SCHAR( bchendflg ),
	DMM_STIMESTAMP( bchend0dh ),
	DMM_STIMESTAMP( bchend1dh ),
	DMM_STIMESTAMP( bchend2dh ),
	DMM_STIMESTAMP( bchend3dh ),
	DMM_STIMESTAMP( bchend4dh ),
	DMM_SCHAR( unyflg ),
	DMM_SLONG( ssntubn ),
	DMM_SCHAR( sriknflg01 ),
	DMM_SCHAR( sriknflg02 ),
	DMM_SCHAR( sriknflg03 ),
	DMM_SCHAR( sriknflg04 ),
	DMM_SCHAR( sriknflg05 ),
	DMM_SCHAR( sriknflg06 ),
	DMM_SCHAR( sriknflg07 ),
	DMM_SCHAR( sriknflg08 ),
	DMM_SCHAR( sriknflg09 ),
	DMM_SCHAR( sriknflg10 ),
	DMM_SCHAR( sriknflg11 ),
	DMM_SCHAR( sriknflg12 ),
	DMM_SCHAR( sriknflg13 ),
	DMM_SCHAR( sriknflg14 ),
	DMM_SCHAR( sriknflg15 ),
	DMM_SCHAR( sriknflg16 ),
	DMM_SCHAR( sriknflg17 ),
	DMM_SCHAR( sriknflg18 ),
	DMM_SCHAR( sriknflg19 ),
	DMM_SCHAR( sriknflg20 ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbSysknrmstSelect()
 *	SYSKNRMST レコード全件取得
 * ■引数
 *	[O]  Sysknrmst* pRec	取得レコード配列格納領域
 * ■戻り値
 *	(long) HRC_SQL_NORMAL	 正常終了（レコードあり）
 *		   HRC_SQL_NOT_FOUND  レコードなし
 *		   HRC_SQL_ERR		DBエラー
 ******************************************************************************/
long ZdbSysknrmstSelect( Sysknrmst* pRec )
{
	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 133 "LD104Sysknrmst.sqc"


	
/*
EXEC SQL DECLARE c1 CURSOR FOR
	SELECT
		LBCD,
		SATEID,
		KJNSRIYMD,
		NXIRISRIYMD,
		NCNSKSRIYMD,
		NXBCHSRIYMD,
		IRIENDFLG,
		IRIENDDH,
		NSKENDFLG,
		NSKENDDH,
		BCHENDFLG,
		BCHEND0DH,
		BCHEND1DH,
		BCHEND2DH,
		BCHEND3DH,
		BCHEND4DH,
		UNYFLG,
		SSNTUBN,
		SRIKNFLG01,
		SRIKNFLG02,
		SRIKNFLG03,
		SRIKNFLG04,
		SRIKNFLG05,
		SRIKNFLG06,
		SRIKNFLG07,
		SRIKNFLG08,
		SRIKNFLG09,
		SRIKNFLG10,
		SRIKNFLG11,
		SRIKNFLG12,
		SRIKNFLG13,
		SRIKNFLG14,
		SRIKNFLG15,
		SRIKNFLG16,
		SRIKNFLG17,
		SRIKNFLG18,
		SRIKNFLG19,
		SRIKNFLG20,
		KSNDH
	FROM
		SYSKNRMST
		FOR UPDATE;
*/

#line 178 "LD104Sysknrmst.sqc"


	
/*
EXEC SQL OPEN c1;
*/

{
#line 180 "LD104Sysknrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 180 "LD104Sysknrmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 180 "LD104Sysknrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 180 "LD104Sysknrmst.sqc"
  sqlastop(0L);
}

#line 180 "LD104Sysknrmst.sqc"


	
/*
EXEC SQL FETCH c1 INTO
		:lbcd,
		:sateid,
		:kjnsriymd,
		:nxirisriymd,
		:ncnsksriymd,
		:nxbchsriymd,
		:iriendflg,
		:irienddh,
		:nskendflg,
		:nskenddh,
		:bchendflg,
		:bchend0dh,
		:bchend1dh,
		:bchend2dh,
		:bchend3dh,
		:bchend4dh,
		:unyflg,
		:ssntubn,
		:sriknflg01,
		:sriknflg02,
		:sriknflg03,
		:sriknflg04,
		:sriknflg05,
		:sriknflg06,
		:sriknflg07,
		:sriknflg08,
		:sriknflg09,
		:sriknflg10,
		:sriknflg11,
		:sriknflg12,
		:sriknflg13,
		:sriknflg14,
		:sriknflg15,
		:sriknflg16,
		:sriknflg17,
		:sriknflg18,
		:sriknflg19,
		:sriknflg20,
		:ksndh;
*/

{
#line 221 "LD104Sysknrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 221 "LD104Sysknrmst.sqc"
  sqlaaloc(3,39,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[39];
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 4;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[0].sqldata = (void*)lbcd;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 4;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[1].sqldata = (void*)sateid;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[2].sqldata = (void*)kjnsriymd;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[3].sqldata = (void*)nxirisriymd;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[4].sqldata = (void*)ncnsksriymd;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[5].sqldata = (void*)nxbchsriymd;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[6].sqldata = (void*)&iriendflg;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 27;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[7].sqldata = (void*)irienddh;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[8].sqldata = (void*)&nskendflg;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[9].sqldata = (void*)nskenddh;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[10].sqldata = (void*)&bchendflg;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 27;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[11].sqldata = (void*)bchend0dh;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 27;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[12].sqldata = (void*)bchend1dh;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 27;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[13].sqldata = (void*)bchend2dh;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 27;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[14].sqldata = (void*)bchend3dh;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[15].sqldata = (void*)bchend4dh;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[16].sqldata = (void*)&unyflg;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[17].sqldata = (void*)&ssntubn;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[18].sqldata = (void*)&sriknflg01;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[19].sqldata = (void*)&sriknflg02;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[20].sqldata = (void*)&sriknflg03;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[21].sqldata = (void*)&sriknflg04;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[22].sqldata = (void*)&sriknflg05;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[23].sqldata = (void*)&sriknflg06;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[24].sqldata = (void*)&sriknflg07;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[25].sqldata = (void*)&sriknflg08;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[26].sqldata = (void*)&sriknflg09;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[27].sqldata = (void*)&sriknflg10;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[28].sqldata = (void*)&sriknflg11;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[29].sqldata = (void*)&sriknflg12;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[30].sqldata = (void*)&sriknflg13;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[31].sqldata = (void*)&sriknflg14;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[32].sqldata = (void*)&sriknflg15;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[33].sqldata = (void*)&sriknflg16;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[34].sqldata = (void*)&sriknflg17;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[35].sqldata = (void*)&sriknflg18;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[36].sqldata = (void*)&sriknflg19;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[37].sqldata = (void*)&sriknflg20;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 27;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[38].sqldata = (void*)ksndh;
#line 221 "LD104Sysknrmst.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 221 "LD104Sysknrmst.sqc"
      sqlasetdata(3,0,39,sql_setdlist,0L,0L);
    }
#line 221 "LD104Sysknrmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 221 "LD104Sysknrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 221 "LD104Sysknrmst.sqc"
  sqlastop(0L);
}

#line 221 "LD104Sysknrmst.sqc"


	ZbmlMapHostToStruct( (char*)pRec, SysknrmstArray );

	
/*
EXEC SQL CLOSE c1;
*/

{
#line 225 "LD104Sysknrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 225 "LD104Sysknrmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 225 "LD104Sysknrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 225 "LD104Sysknrmst.sqc"
  sqlastop(0L);
}

#line 225 "LD104Sysknrmst.sqc"


	return (sqlca.sqlcode == 0) ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 230 "LD104Sysknrmst.sqc"

	return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbSysknrmstUpdate()
 *      SYSKNRMST レコードを更新する
 * ■引数
 *      [I]  Sysknrmst* pRec       更新対象レコード
 * ■戻り値
 *      (long) HRC_SQL_NORMAL    正常終了
 *                 HRC_SQL_NOT_FOUND  対象レコードなし
 *                 HRC_NULL_POINTER   パラメータエラー
 *                 HRC_INVALID_VALUE  設定値不正
 *                 HRC_SQL_ERR          DBエラー
 ******************************************************************************/
long ZdbSysknrmstUpdate( Sysknrmst* pRec )
{
	if( !pRec )
		return HRC_NULL_POINTER;

	if( !ZbmlMapStructToHost( (char*)pRec, SysknrmstArray ) )
		return HRC_INVALID_VALUE;

	
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 253 "LD104Sysknrmst.sqc"

	
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 254 "LD104Sysknrmst.sqc"


	
/*
EXEC SQL UPDATE SYSKNRMST
	SET (
		SSNTUBN,
		KSNDH
	) = (
		:ssntubn,
		current timestamp
	) WHERE
		LBCD = :lbcd AND
		SATEID = :sateid;
*/

{
#line 265 "LD104Sysknrmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 265 "LD104Sysknrmst.sqc"
  sqlaaloc(2,3,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 265 "LD104Sysknrmst.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 265 "LD104Sysknrmst.sqc"
      sql_setdlist[0].sqldata = (void*)&ssntubn;
#line 265 "LD104Sysknrmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 265 "LD104Sysknrmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 4;
#line 265 "LD104Sysknrmst.sqc"
      sql_setdlist[1].sqldata = (void*)lbcd;
#line 265 "LD104Sysknrmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 265 "LD104Sysknrmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 4;
#line 265 "LD104Sysknrmst.sqc"
      sql_setdlist[2].sqldata = (void*)sateid;
#line 265 "LD104Sysknrmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 265 "LD104Sysknrmst.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 265 "LD104Sysknrmst.sqc"
  sqlacall((unsigned short)24,2,2,0,0L);
#line 265 "LD104Sysknrmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 265 "LD104Sysknrmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 265 "LD104Sysknrmst.sqc"
  sqlastop(0L);
}

#line 265 "LD104Sysknrmst.sqc"


	return HRC_SQL_NORMAL;

notfound:
	
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 270 "LD104Sysknrmst.sqc"

	return HRC_SQL_NOT_FOUND;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 274 "LD104Sysknrmst.sqc"

	return sqlca.sqlcode;
}

/** End of File *********************************************************/
