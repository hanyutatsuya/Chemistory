static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,73,65,83,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,50,51,90,72,89,74,75,32,0,0,0,0,0,0,0,0,
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


#line 1 "Hyjkmk.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Hyjkmk.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Hyjkmk.h"
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


#line 24 "Hyjkmk.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Hyjkmk.sqc"

	char    defkbn;
	char    wkupapp[33];
	char    loginid[9];
	char    hyjniy01[51];
	char    hyjniy02[51];
	char    hyjniy03[51];
	char    hyjniy04[51];
	char    hyjniy05[51];
	char    hyjniy06[51];
	char    hyjniy07[51];
	char    hyjniy08[51];
	char    hyjniy09[51];
	char    hyjniy10[51];
	char    hyjniy11[51];
	char    hyjniy12[51];
	char    hyjniy13[51];
	char    hyjniy14[51];
	char    hyjniy15[51];
	char    hyjniy16[51];
	char    hyjniy17[51];
	char    hyjniy18[51];
	char    hyjniy19[51];
	char    hyjniy20[51];
	char    hyjniy21[51];
	char    hyjniy22[51];
	char    hyjniy23[51];
	char    hyjniy24[51];
	char    hyjniy25[51];
	char    hyjniy26[51];
	char    hyjniy27[51];
	char    hyjniy28[51];
	char    hyjniy29[51];
	char    hyjniy30[51];
	char    hyjniy31[51];
	char    hyjniy32[51];
	char    hyjniy33[51];
	char    hyjniy34[51];
	char    hyjniy35[51];
	char    hyjniy36[51];
	char    hyjniy37[51];
	char    hyjniy38[51];
	char    hyjniy39[51];
	char    hyjniy40[51];
	char    hyjniy41[51];
	char    hyjniy42[51];
	char    hyjniy43[51];
	char    hyjniy44[51];
	char    hyjniy45[51];
	char    hyjniy46[51];
	char    hyjniy47[51];
	char    hyjniy48[51];
	char    hyjniy49[51];
	char    hyjniy50[51];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 84 "Hyjkmk.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Hyjkmk

BmlDMMInfo	HyjkmkArray[] = {
	DMM_SCHAR( defkbn ),
	DMM_SSTRING( wkupapp ),
	DMM_SSTRING( loginid ),
	DMM_SSTRING( hyjniy01 ),
	DMM_SSTRING( hyjniy02 ),
	DMM_SSTRING( hyjniy03 ),
	DMM_SSTRING( hyjniy04 ),
	DMM_SSTRING( hyjniy05 ),
	DMM_SSTRING( hyjniy06 ),
	DMM_SSTRING( hyjniy07 ),
	DMM_SSTRING( hyjniy08 ),
	DMM_SSTRING( hyjniy09 ),
	DMM_SSTRING( hyjniy10 ),
	DMM_SSTRING( hyjniy11 ),
	DMM_SSTRING( hyjniy12 ),
	DMM_SSTRING( hyjniy13 ),
	DMM_SSTRING( hyjniy14 ),
	DMM_SSTRING( hyjniy15 ),
	DMM_SSTRING( hyjniy16 ),
	DMM_SSTRING( hyjniy17 ),
	DMM_SSTRING( hyjniy18 ),
	DMM_SSTRING( hyjniy19 ),
	DMM_SSTRING( hyjniy20 ),
	DMM_SSTRING( hyjniy21 ),
	DMM_SSTRING( hyjniy22 ),
	DMM_SSTRING( hyjniy23 ),
	DMM_SSTRING( hyjniy24 ),
	DMM_SSTRING( hyjniy25 ),
	DMM_SSTRING( hyjniy26 ),
	DMM_SSTRING( hyjniy27 ),
	DMM_SSTRING( hyjniy28 ),
	DMM_SSTRING( hyjniy29 ),
	DMM_SSTRING( hyjniy30 ),
	DMM_SSTRING( hyjniy31 ),
	DMM_SSTRING( hyjniy32 ),
	DMM_SSTRING( hyjniy33 ),
	DMM_SSTRING( hyjniy34 ),
	DMM_SSTRING( hyjniy35 ),
	DMM_SSTRING( hyjniy36 ),
	DMM_SSTRING( hyjniy37 ),
	DMM_SSTRING( hyjniy38 ),
	DMM_SSTRING( hyjniy39 ),
	DMM_SSTRING( hyjniy40 ),
	DMM_SSTRING( hyjniy41 ),
	DMM_SSTRING( hyjniy42 ),
	DMM_SSTRING( hyjniy43 ),
	DMM_SSTRING( hyjniy44 ),
	DMM_SSTRING( hyjniy45 ),
	DMM_SSTRING( hyjniy46 ),
	DMM_SSTRING( hyjniy47 ),
	DMM_SSTRING( hyjniy48 ),
	DMM_SSTRING( hyjniy49 ),
	DMM_SSTRING( hyjniy50 ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbHyjkmkSelectAll()
 *    HYJKMK レコード全件取得
 * ■引数
 *    [O]  Hyjkmk** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbHyjkmkSelectAll( Hyjkmk** arrayOut, int* numOut )
{
    Hyjkmk*     array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 166 "Hyjkmk.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		DEFKBN,
		WKUPAPP,
		LOGINID,
		HYJNIY01,
		HYJNIY02,
		HYJNIY03,
		HYJNIY04,
		HYJNIY05,
		HYJNIY06,
		HYJNIY07,
		HYJNIY08,
		HYJNIY09,
		HYJNIY10,
		HYJNIY11,
		HYJNIY12,
		HYJNIY13,
		HYJNIY14,
		HYJNIY15,
		HYJNIY16,
		HYJNIY17,
		HYJNIY18,
		HYJNIY19,
		HYJNIY20,
		HYJNIY21,
		HYJNIY22,
		HYJNIY23,
		HYJNIY24,
		HYJNIY25,
		HYJNIY26,
		HYJNIY27,
		HYJNIY28,
		HYJNIY29,
		HYJNIY30,
		HYJNIY31,
		HYJNIY32,
		HYJNIY33,
		HYJNIY34,
		HYJNIY35,
		HYJNIY36,
		HYJNIY37,
		HYJNIY38,
		HYJNIY39,
		HYJNIY40,
		HYJNIY41,
		HYJNIY42,
		HYJNIY43,
		HYJNIY44,
		HYJNIY45,
		HYJNIY46,
		HYJNIY47,
		HYJNIY48,
		HYJNIY49,
		HYJNIY50,
		KSNDH
    FROM
        HYJKMK FOR READ ONLY;
*/

#line 225 "Hyjkmk.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 227 "Hyjkmk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 227 "Hyjkmk.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 227 "Hyjkmk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 227 "Hyjkmk.sqc"
  sqlastop(0L);
}

#line 227 "Hyjkmk.sqc"


    while( 1 ) {
        Hyjkmk* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:defkbn,
			:wkupapp,
			:loginid,
			:hyjniy01,
			:hyjniy02,
			:hyjniy03,
			:hyjniy04,
			:hyjniy05,
			:hyjniy06,
			:hyjniy07,
			:hyjniy08,
			:hyjniy09,
			:hyjniy10,
			:hyjniy11,
			:hyjniy12,
			:hyjniy13,
			:hyjniy14,
			:hyjniy15,
			:hyjniy16,
			:hyjniy17,
			:hyjniy18,
			:hyjniy19,
			:hyjniy20,
			:hyjniy21,
			:hyjniy22,
			:hyjniy23,
			:hyjniy24,
			:hyjniy25,
			:hyjniy26,
			:hyjniy27,
			:hyjniy28,
			:hyjniy29,
			:hyjniy30,
			:hyjniy31,
			:hyjniy32,
			:hyjniy33,
			:hyjniy34,
			:hyjniy35,
			:hyjniy36,
			:hyjniy37,
			:hyjniy38,
			:hyjniy39,
			:hyjniy40,
			:hyjniy41,
			:hyjniy42,
			:hyjniy43,
			:hyjniy44,
			:hyjniy45,
			:hyjniy46,
			:hyjniy47,
			:hyjniy48,
			:hyjniy49,
			:hyjniy50,
			:ksndh;
*/

{
#line 286 "Hyjkmk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 286 "Hyjkmk.sqc"
  sqlaaloc(3,54,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[54];
#line 286 "Hyjkmk.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[0].sqldata = (void*)&defkbn;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 33;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[1].sqldata = (void*)wkupapp;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 9;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[2].sqldata = (void*)loginid;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[3].sqldata = (void*)hyjniy01;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[4].sqldata = (void*)hyjniy02;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[5].sqldata = (void*)hyjniy03;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[6].sqldata = (void*)hyjniy04;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[7].sqldata = (void*)hyjniy05;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[8].sqldata = (void*)hyjniy06;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[9].sqldata = (void*)hyjniy07;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[10].sqldata = (void*)hyjniy08;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[11].sqldata = (void*)hyjniy09;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[12].sqldata = (void*)hyjniy10;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[13].sqldata = (void*)hyjniy11;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[14].sqldata = (void*)hyjniy12;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[15].sqldata = (void*)hyjniy13;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[16].sqldata = (void*)hyjniy14;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[17].sqldata = (void*)hyjniy15;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[18].sqldata = (void*)hyjniy16;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[19].sqldata = (void*)hyjniy17;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[20].sqldata = (void*)hyjniy18;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[21].sqldata = (void*)hyjniy19;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[22].sqldata = (void*)hyjniy20;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[23].sqldata = (void*)hyjniy21;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[24].sqldata = (void*)hyjniy22;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[25].sqldata = (void*)hyjniy23;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[26].sqldata = (void*)hyjniy24;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[27].sqldata = (void*)hyjniy25;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[28].sqldata = (void*)hyjniy26;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[29].sqldata = (void*)hyjniy27;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[30].sqldata = (void*)hyjniy28;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[31].sqldata = (void*)hyjniy29;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[32].sqldata = (void*)hyjniy30;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[33].sqldata = (void*)hyjniy31;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[34].sqldata = (void*)hyjniy32;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[35].sqldata = (void*)hyjniy33;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[36].sqldata = (void*)hyjniy34;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[37].sqldata = (void*)hyjniy35;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[38].sqldata = (void*)hyjniy36;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[39].sqldata = (void*)hyjniy37;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[40].sqldata = (void*)hyjniy38;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[41].sqldata = (void*)hyjniy39;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[42].sqldata = (void*)hyjniy40;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[43].sqldata = (void*)hyjniy41;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[44].sqldata = (void*)hyjniy42;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[45].sqldata = (void*)hyjniy43;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[46].sqldata = (void*)hyjniy44;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[47].sqldata = (void*)hyjniy45;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[48].sqldata = (void*)hyjniy46;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[49].sqldata = (void*)hyjniy47;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[50].sqldata = (void*)hyjniy48;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[51].sqldata = (void*)hyjniy49;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 51;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[52].sqldata = (void*)hyjniy50;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 27;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[53].sqldata = (void*)ksndh;
#line 286 "Hyjkmk.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 286 "Hyjkmk.sqc"
      sqlasetdata(3,0,54,sql_setdlist,0L,0L);
    }
#line 286 "Hyjkmk.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 286 "Hyjkmk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 286 "Hyjkmk.sqc"
  sqlastop(0L);
}

#line 286 "Hyjkmk.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Hyjkmk*)ZbmlRealloc( array,
                                    sizeof( Hyjkmk ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Hyjkmk ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, HyjkmkArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 301 "Hyjkmk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 301 "Hyjkmk.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 301 "Hyjkmk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 301 "Hyjkmk.sqc"
  sqlastop(0L);
}

#line 301 "Hyjkmk.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 309 "Hyjkmk.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbHyjkmkSelectKey()
 *    HYJKMK レコードKey条件取得
 * ■引数
 *    [I]  Hyjkmk* pKey       取得するレコードのキー
 *    [O]  Hyjkmk** arrayOut    取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbHyjkmkSelectKey( Hyjkmk* pKey, Hyjkmk** arrayOut, int* numOut )
{
    Hyjkmk*     array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, HyjkmkArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 335 "Hyjkmk.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		DEFKBN,
		WKUPAPP,
		LOGINID,
		HYJNIY01,
		HYJNIY02,
		HYJNIY03,
		HYJNIY04,
		HYJNIY05,
		HYJNIY06,
		HYJNIY07,
		HYJNIY08,
		HYJNIY09,
		HYJNIY10,
		HYJNIY11,
		HYJNIY12,
		HYJNIY13,
		HYJNIY14,
		HYJNIY15,
		HYJNIY16,
		HYJNIY17,
		HYJNIY18,
		HYJNIY19,
		HYJNIY20,
		HYJNIY21,
		HYJNIY22,
		HYJNIY23,
		HYJNIY24,
		HYJNIY25,
		HYJNIY26,
		HYJNIY27,
		HYJNIY28,
		HYJNIY29,
		HYJNIY30,
		HYJNIY31,
		HYJNIY32,
		HYJNIY33,
		HYJNIY34,
		HYJNIY35,
		HYJNIY36,
		HYJNIY37,
		HYJNIY38,
		HYJNIY39,
		HYJNIY40,
		HYJNIY41,
		HYJNIY42,
		HYJNIY43,
		HYJNIY44,
		HYJNIY45,
		HYJNIY46,
		HYJNIY47,
		HYJNIY48,
		HYJNIY49,
		HYJNIY50,
		KSNDH
    FROM
        HYJKMK
    WHERE
		DEFKBN = :defkbn AND
		WKUPAPP = :wkupapp AND
		LOGINID = :loginid FOR READ ONLY;
*/

#line 398 "Hyjkmk.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 400 "Hyjkmk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 400 "Hyjkmk.sqc"
  sqlaaloc(2,3,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 400 "Hyjkmk.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 400 "Hyjkmk.sqc"
      sql_setdlist[0].sqldata = (void*)&defkbn;
#line 400 "Hyjkmk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 400 "Hyjkmk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 33;
#line 400 "Hyjkmk.sqc"
      sql_setdlist[1].sqldata = (void*)wkupapp;
#line 400 "Hyjkmk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 400 "Hyjkmk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 9;
#line 400 "Hyjkmk.sqc"
      sql_setdlist[2].sqldata = (void*)loginid;
#line 400 "Hyjkmk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 400 "Hyjkmk.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 400 "Hyjkmk.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 400 "Hyjkmk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 400 "Hyjkmk.sqc"
  sqlastop(0L);
}

#line 400 "Hyjkmk.sqc"


    while( 1 ) {
        Hyjkmk* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:defkbn,
			:wkupapp,
			:loginid,
			:hyjniy01,
			:hyjniy02,
			:hyjniy03,
			:hyjniy04,
			:hyjniy05,
			:hyjniy06,
			:hyjniy07,
			:hyjniy08,
			:hyjniy09,
			:hyjniy10,
			:hyjniy11,
			:hyjniy12,
			:hyjniy13,
			:hyjniy14,
			:hyjniy15,
			:hyjniy16,
			:hyjniy17,
			:hyjniy18,
			:hyjniy19,
			:hyjniy20,
			:hyjniy21,
			:hyjniy22,
			:hyjniy23,
			:hyjniy24,
			:hyjniy25,
			:hyjniy26,
			:hyjniy27,
			:hyjniy28,
			:hyjniy29,
			:hyjniy30,
			:hyjniy31,
			:hyjniy32,
			:hyjniy33,
			:hyjniy34,
			:hyjniy35,
			:hyjniy36,
			:hyjniy37,
			:hyjniy38,
			:hyjniy39,
			:hyjniy40,
			:hyjniy41,
			:hyjniy42,
			:hyjniy43,
			:hyjniy44,
			:hyjniy45,
			:hyjniy46,
			:hyjniy47,
			:hyjniy48,
			:hyjniy49,
			:hyjniy50,
			:ksndh;
*/

{
#line 459 "Hyjkmk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 459 "Hyjkmk.sqc"
  sqlaaloc(3,54,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[54];
#line 459 "Hyjkmk.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[0].sqldata = (void*)&defkbn;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 33;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[1].sqldata = (void*)wkupapp;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 9;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[2].sqldata = (void*)loginid;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[3].sqldata = (void*)hyjniy01;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[4].sqldata = (void*)hyjniy02;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[5].sqldata = (void*)hyjniy03;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[6].sqldata = (void*)hyjniy04;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[7].sqldata = (void*)hyjniy05;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[8].sqldata = (void*)hyjniy06;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[9].sqldata = (void*)hyjniy07;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[10].sqldata = (void*)hyjniy08;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[11].sqldata = (void*)hyjniy09;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[12].sqldata = (void*)hyjniy10;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[13].sqldata = (void*)hyjniy11;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[14].sqldata = (void*)hyjniy12;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[15].sqldata = (void*)hyjniy13;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[16].sqldata = (void*)hyjniy14;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[17].sqldata = (void*)hyjniy15;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[18].sqldata = (void*)hyjniy16;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[19].sqldata = (void*)hyjniy17;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[20].sqldata = (void*)hyjniy18;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[21].sqldata = (void*)hyjniy19;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[22].sqldata = (void*)hyjniy20;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[23].sqldata = (void*)hyjniy21;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[24].sqldata = (void*)hyjniy22;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[25].sqldata = (void*)hyjniy23;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[26].sqldata = (void*)hyjniy24;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[27].sqldata = (void*)hyjniy25;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[28].sqldata = (void*)hyjniy26;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[29].sqldata = (void*)hyjniy27;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[30].sqldata = (void*)hyjniy28;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[31].sqldata = (void*)hyjniy29;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[32].sqldata = (void*)hyjniy30;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[33].sqldata = (void*)hyjniy31;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[34].sqldata = (void*)hyjniy32;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[35].sqldata = (void*)hyjniy33;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[36].sqldata = (void*)hyjniy34;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[37].sqldata = (void*)hyjniy35;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[38].sqldata = (void*)hyjniy36;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[39].sqldata = (void*)hyjniy37;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[40].sqldata = (void*)hyjniy38;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[41].sqldata = (void*)hyjniy39;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[42].sqldata = (void*)hyjniy40;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[43].sqldata = (void*)hyjniy41;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[44].sqldata = (void*)hyjniy42;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[45].sqldata = (void*)hyjniy43;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[46].sqldata = (void*)hyjniy44;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[47].sqldata = (void*)hyjniy45;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[48].sqldata = (void*)hyjniy46;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[49].sqldata = (void*)hyjniy47;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[50].sqldata = (void*)hyjniy48;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[51].sqldata = (void*)hyjniy49;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 51;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[52].sqldata = (void*)hyjniy50;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 27;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[53].sqldata = (void*)ksndh;
#line 459 "Hyjkmk.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 459 "Hyjkmk.sqc"
      sqlasetdata(3,0,54,sql_setdlist,0L,0L);
    }
#line 459 "Hyjkmk.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 459 "Hyjkmk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 459 "Hyjkmk.sqc"
  sqlastop(0L);
}

#line 459 "Hyjkmk.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Hyjkmk*)ZbmlRealloc( array,
                                    sizeof( Hyjkmk ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Hyjkmk ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, HyjkmkArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 474 "Hyjkmk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 474 "Hyjkmk.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 474 "Hyjkmk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 474 "Hyjkmk.sqc"
  sqlastop(0L);
}

#line 474 "Hyjkmk.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 482 "Hyjkmk.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbHyjkmkInsert()
 *    HYJKMK レコードを挿入する
 * ■引数
 *    [I]  Hyjkmk* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbHyjkmkInsert( Hyjkmk* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, HyjkmkArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 505 "Hyjkmk.sqc"


    
/*
EXEC SQL INSERT INTO HYJKMK
    (
		DEFKBN,
		WKUPAPP,
		LOGINID,
		HYJNIY01,
		HYJNIY02,
		HYJNIY03,
		HYJNIY04,
		HYJNIY05,
		HYJNIY06,
		HYJNIY07,
		HYJNIY08,
		HYJNIY09,
		HYJNIY10,
		HYJNIY11,
		HYJNIY12,
		HYJNIY13,
		HYJNIY14,
		HYJNIY15,
		HYJNIY16,
		HYJNIY17,
		HYJNIY18,
		HYJNIY19,
		HYJNIY20,
		HYJNIY21,
		HYJNIY22,
		HYJNIY23,
		HYJNIY24,
		HYJNIY25,
		HYJNIY26,
		HYJNIY27,
		HYJNIY28,
		HYJNIY29,
		HYJNIY30,
		HYJNIY31,
		HYJNIY32,
		HYJNIY33,
		HYJNIY34,
		HYJNIY35,
		HYJNIY36,
		HYJNIY37,
		HYJNIY38,
		HYJNIY39,
		HYJNIY40,
		HYJNIY41,
		HYJNIY42,
		HYJNIY43,
		HYJNIY44,
		HYJNIY45,
		HYJNIY46,
		HYJNIY47,
		HYJNIY48,
		HYJNIY49,
		HYJNIY50,
		KSNDH
    ) VALUES (
		:defkbn,
		:wkupapp,
		:loginid,
		:hyjniy01,
		:hyjniy02,
		:hyjniy03,
		:hyjniy04,
		:hyjniy05,
		:hyjniy06,
		:hyjniy07,
		:hyjniy08,
		:hyjniy09,
		:hyjniy10,
		:hyjniy11,
		:hyjniy12,
		:hyjniy13,
		:hyjniy14,
		:hyjniy15,
		:hyjniy16,
		:hyjniy17,
		:hyjniy18,
		:hyjniy19,
		:hyjniy20,
		:hyjniy21,
		:hyjniy22,
		:hyjniy23,
		:hyjniy24,
		:hyjniy25,
		:hyjniy26,
		:hyjniy27,
		:hyjniy28,
		:hyjniy29,
		:hyjniy30,
		:hyjniy31,
		:hyjniy32,
		:hyjniy33,
		:hyjniy34,
		:hyjniy35,
		:hyjniy36,
		:hyjniy37,
		:hyjniy38,
		:hyjniy39,
		:hyjniy40,
		:hyjniy41,
		:hyjniy42,
		:hyjniy43,
		:hyjniy44,
		:hyjniy45,
		:hyjniy46,
		:hyjniy47,
		:hyjniy48,
		:hyjniy49,
		:hyjniy50,
		:ksndh
    );
*/

{
#line 618 "Hyjkmk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 618 "Hyjkmk.sqc"
  sqlaaloc(2,54,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[54];
#line 618 "Hyjkmk.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[0].sqldata = (void*)&defkbn;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 33;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[1].sqldata = (void*)wkupapp;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 9;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[2].sqldata = (void*)loginid;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[3].sqldata = (void*)hyjniy01;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[4].sqldata = (void*)hyjniy02;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[5].sqldata = (void*)hyjniy03;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[6].sqldata = (void*)hyjniy04;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[7].sqldata = (void*)hyjniy05;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[8].sqldata = (void*)hyjniy06;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[9].sqldata = (void*)hyjniy07;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[10].sqldata = (void*)hyjniy08;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[11].sqldata = (void*)hyjniy09;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[12].sqldata = (void*)hyjniy10;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[13].sqldata = (void*)hyjniy11;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[14].sqldata = (void*)hyjniy12;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[15].sqldata = (void*)hyjniy13;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[16].sqldata = (void*)hyjniy14;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[17].sqldata = (void*)hyjniy15;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[18].sqldata = (void*)hyjniy16;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[19].sqldata = (void*)hyjniy17;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[20].sqldata = (void*)hyjniy18;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[21].sqldata = (void*)hyjniy19;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[22].sqldata = (void*)hyjniy20;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[23].sqldata = (void*)hyjniy21;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[24].sqldata = (void*)hyjniy22;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[25].sqldata = (void*)hyjniy23;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[26].sqldata = (void*)hyjniy24;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[27].sqldata = (void*)hyjniy25;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[28].sqldata = (void*)hyjniy26;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[29].sqldata = (void*)hyjniy27;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[30].sqldata = (void*)hyjniy28;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[31].sqldata = (void*)hyjniy29;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[32].sqldata = (void*)hyjniy30;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[33].sqldata = (void*)hyjniy31;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[34].sqldata = (void*)hyjniy32;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[35].sqldata = (void*)hyjniy33;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[36].sqldata = (void*)hyjniy34;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[37].sqldata = (void*)hyjniy35;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[38].sqldata = (void*)hyjniy36;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[39].sqldata = (void*)hyjniy37;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[40].sqldata = (void*)hyjniy38;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[41].sqldata = (void*)hyjniy39;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[42].sqldata = (void*)hyjniy40;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[43].sqldata = (void*)hyjniy41;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[44].sqldata = (void*)hyjniy42;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[45].sqldata = (void*)hyjniy43;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[46].sqldata = (void*)hyjniy44;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[47].sqldata = (void*)hyjniy45;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[48].sqldata = (void*)hyjniy46;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[49].sqldata = (void*)hyjniy47;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[50].sqldata = (void*)hyjniy48;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[51].sqldata = (void*)hyjniy49;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 51;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[52].sqldata = (void*)hyjniy50;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 27;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[53].sqldata = (void*)ksndh;
#line 618 "Hyjkmk.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 618 "Hyjkmk.sqc"
      sqlasetdata(2,0,54,sql_setdlist,0L,0L);
    }
#line 618 "Hyjkmk.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 618 "Hyjkmk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 618 "Hyjkmk.sqc"
  sqlastop(0L);
}

#line 618 "Hyjkmk.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 623 "Hyjkmk.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbHyjkmkUpdate()
 *    HYJKMK レコードを更新する
 * ■引数
 *    [I]  Hyjkmk* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbHyjkmkUpdate( Hyjkmk* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, HyjkmkArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 647 "Hyjkmk.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 648 "Hyjkmk.sqc"


    
/*
EXEC SQL UPDATE HYJKMK
    SET (
		HYJNIY01,
		HYJNIY02,
		HYJNIY03,
		HYJNIY04,
		HYJNIY05,
		HYJNIY06,
		HYJNIY07,
		HYJNIY08,
		HYJNIY09,
		HYJNIY10,
		HYJNIY11,
		HYJNIY12,
		HYJNIY13,
		HYJNIY14,
		HYJNIY15,
		HYJNIY16,
		HYJNIY17,
		HYJNIY18,
		HYJNIY19,
		HYJNIY20,
		HYJNIY21,
		HYJNIY22,
		HYJNIY23,
		HYJNIY24,
		HYJNIY25,
		HYJNIY26,
		HYJNIY27,
		HYJNIY28,
		HYJNIY29,
		HYJNIY30,
		HYJNIY31,
		HYJNIY32,
		HYJNIY33,
		HYJNIY34,
		HYJNIY35,
		HYJNIY36,
		HYJNIY37,
		HYJNIY38,
		HYJNIY39,
		HYJNIY40,
		HYJNIY41,
		HYJNIY42,
		HYJNIY43,
		HYJNIY44,
		HYJNIY45,
		HYJNIY46,
		HYJNIY47,
		HYJNIY48,
		HYJNIY49,
		HYJNIY50,
		KSNDH
    ) = (
		:hyjniy01,
		:hyjniy02,
		:hyjniy03,
		:hyjniy04,
		:hyjniy05,
		:hyjniy06,
		:hyjniy07,
		:hyjniy08,
		:hyjniy09,
		:hyjniy10,
		:hyjniy11,
		:hyjniy12,
		:hyjniy13,
		:hyjniy14,
		:hyjniy15,
		:hyjniy16,
		:hyjniy17,
		:hyjniy18,
		:hyjniy19,
		:hyjniy20,
		:hyjniy21,
		:hyjniy22,
		:hyjniy23,
		:hyjniy24,
		:hyjniy25,
		:hyjniy26,
		:hyjniy27,
		:hyjniy28,
		:hyjniy29,
		:hyjniy30,
		:hyjniy31,
		:hyjniy32,
		:hyjniy33,
		:hyjniy34,
		:hyjniy35,
		:hyjniy36,
		:hyjniy37,
		:hyjniy38,
		:hyjniy39,
		:hyjniy40,
		:hyjniy41,
		:hyjniy42,
		:hyjniy43,
		:hyjniy44,
		:hyjniy45,
		:hyjniy46,
		:hyjniy47,
		:hyjniy48,
		:hyjniy49,
		:hyjniy50,
		:ksndh
    ) WHERE
		DEFKBN = :defkbn AND
		WKUPAPP = :wkupapp AND
		LOGINID = :loginid;
*/

{
#line 758 "Hyjkmk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 758 "Hyjkmk.sqc"
  sqlaaloc(2,54,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[54];
#line 758 "Hyjkmk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[0].sqldata = (void*)hyjniy01;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[1].sqldata = (void*)hyjniy02;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[2].sqldata = (void*)hyjniy03;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[3].sqldata = (void*)hyjniy04;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[4].sqldata = (void*)hyjniy05;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[5].sqldata = (void*)hyjniy06;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[6].sqldata = (void*)hyjniy07;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[7].sqldata = (void*)hyjniy08;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[8].sqldata = (void*)hyjniy09;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[9].sqldata = (void*)hyjniy10;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[10].sqldata = (void*)hyjniy11;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[11].sqldata = (void*)hyjniy12;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[12].sqldata = (void*)hyjniy13;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[13].sqldata = (void*)hyjniy14;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[14].sqldata = (void*)hyjniy15;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[15].sqldata = (void*)hyjniy16;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[16].sqldata = (void*)hyjniy17;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[17].sqldata = (void*)hyjniy18;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[18].sqldata = (void*)hyjniy19;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[19].sqldata = (void*)hyjniy20;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[20].sqldata = (void*)hyjniy21;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[21].sqldata = (void*)hyjniy22;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[22].sqldata = (void*)hyjniy23;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[23].sqldata = (void*)hyjniy24;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[24].sqldata = (void*)hyjniy25;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[25].sqldata = (void*)hyjniy26;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[26].sqldata = (void*)hyjniy27;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[27].sqldata = (void*)hyjniy28;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[28].sqldata = (void*)hyjniy29;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[29].sqldata = (void*)hyjniy30;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[30].sqldata = (void*)hyjniy31;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[31].sqldata = (void*)hyjniy32;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[32].sqldata = (void*)hyjniy33;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[33].sqldata = (void*)hyjniy34;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[34].sqldata = (void*)hyjniy35;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[35].sqldata = (void*)hyjniy36;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[36].sqldata = (void*)hyjniy37;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[37].sqldata = (void*)hyjniy38;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[38].sqldata = (void*)hyjniy39;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[39].sqldata = (void*)hyjniy40;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[40].sqldata = (void*)hyjniy41;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[41].sqldata = (void*)hyjniy42;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[42].sqldata = (void*)hyjniy43;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[43].sqldata = (void*)hyjniy44;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[44].sqldata = (void*)hyjniy45;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[45].sqldata = (void*)hyjniy46;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[46].sqldata = (void*)hyjniy47;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[47].sqldata = (void*)hyjniy48;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[48].sqldata = (void*)hyjniy49;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 51;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[49].sqldata = (void*)hyjniy50;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 27;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[50].sqldata = (void*)ksndh;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[51].sqltype = 452; sql_setdlist[51].sqllen = 1;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[51].sqldata = (void*)&defkbn;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 33;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[52].sqldata = (void*)wkupapp;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 9;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[53].sqldata = (void*)loginid;
#line 758 "Hyjkmk.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 758 "Hyjkmk.sqc"
      sqlasetdata(2,0,54,sql_setdlist,0L,0L);
    }
#line 758 "Hyjkmk.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 758 "Hyjkmk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 758 "Hyjkmk.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 758 "Hyjkmk.sqc"
  sqlastop(0L);
}

#line 758 "Hyjkmk.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 763 "Hyjkmk.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 767 "Hyjkmk.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbHyjkmkDelete()
 *    HYJKMK レコードを削除する
 * ■引数
 *    [I]  Hyjkmk* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbHyjkmkDelete( Hyjkmk* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, HyjkmkArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 791 "Hyjkmk.sqc"


    
/*
EXEC SQL DELETE FROM HYJKMK
    WHERE
		DEFKBN = :defkbn AND
		WKUPAPP = :wkupapp AND
		LOGINID = :loginid;
*/

{
#line 797 "Hyjkmk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 797 "Hyjkmk.sqc"
  sqlaaloc(2,3,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 797 "Hyjkmk.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 797 "Hyjkmk.sqc"
      sql_setdlist[0].sqldata = (void*)&defkbn;
#line 797 "Hyjkmk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 797 "Hyjkmk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 33;
#line 797 "Hyjkmk.sqc"
      sql_setdlist[1].sqldata = (void*)wkupapp;
#line 797 "Hyjkmk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 797 "Hyjkmk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 9;
#line 797 "Hyjkmk.sqc"
      sql_setdlist[2].sqldata = (void*)loginid;
#line 797 "Hyjkmk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 797 "Hyjkmk.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 797 "Hyjkmk.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 797 "Hyjkmk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 797 "Hyjkmk.sqc"
  sqlastop(0L);
}

#line 797 "Hyjkmk.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 802 "Hyjkmk.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
