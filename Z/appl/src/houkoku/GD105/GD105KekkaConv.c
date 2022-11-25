static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,100,65,70,52,85,97,68,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,53,71,49,48,53,32,32,32,0,0,0,0,0,0,0,0,
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


#line 1 "GD105KekkaConv.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： GD105KekkaConv.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2009-05-19     K.Moriya       結果変換マスタ対応
 **********************************************************************/
#include <stdio.h>

#include "GD105KekkaConv.h"
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


#line 26 "GD105KekkaConv.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 31 "GD105KekkaConv.sqc"

	char    knskisymd[11];
	char    sriymd[11];
	char    kntno[14];
	char    knsgrp[17];
	char    kmkcd[8];
	short   knssu;
	short   knssueda;
	char    knskka1[13];
	char    knskka2[25];
	char    knskka2kbn[3];
	char    kkahskcd[4];
	char	dtnrtts[8+1];
	char	skkka[24+1];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 45 "GD105KekkaConv.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	KekkaConv

BmlDMMInfo	KekkaConvArray[] = {
	DMM_SDATE( knskisymd ),
	DMM_SDATE( sriymd ),
	DMM_SSTRING( kntno ),
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSHORT( knssu ),
	DMM_SSHORT( knssueda ),
	DMM_SSTRING( knskka1 ),
	DMM_SSTRING( knskka2 ),
	DMM_SSTRING( knskka2kbn ),
	DMM_SSTRING( kkahskcd ),
	DMM_SSTRING( dtnrtts ),
	DMM_SSTRING( skkka ),
	DMM_NULL
};

/******************************************************************************
 * dGD105UpdKekkaConv()
 *    KEKKA レコードを更新する
 * ■引数
 *    [I]  KekkaConv* rec           更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL(0)      正常終了
 *           HRC_SQL_NOT_FOUND(100) 対象レコードなし
 *           HRC_NULL_POINTER(-3)   パラメータエラー
 *           HRC_INVALID_VALUE(-1)  設定値不正
 *           HRC_SQL_ERR(-2)        DBエラー
 ******************************************************************************/
long dGD105UpdKekkaConv( KekkaConv* rec )
{
#ifdef _DEBUG
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105UpdKekkaConv", __LINE__, EXEFLG_UPD, "020",
				 "● dGD105UpdKekkaConv 入った" ) ;
#endif

	if( !rec ) {
		return HRC_NULL_POINTER;
	}

	if( !ZbmlMapStructToHost( (char*)rec, KekkaConvArray ) ) {
		return HRC_INVALID_VALUE;
	}

#ifdef _DEBUG
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105UpdKekkaConv", __LINE__, EXEFLG_UPD, "020",
				"    knskisymd  = [%s]", knskisymd ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105UpdKekkaConv", __LINE__, EXEFLG_UPD, "020",
				"    sriymd     = [%s]", sriymd ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105UpdKekkaConv", __LINE__, EXEFLG_UPD, "020",
				"    kntno      = [%s]", kntno ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105UpdKekkaConv", __LINE__, EXEFLG_UPD, "020",
				"    knsgrp     = [%s]", knsgrp ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105UpdKekkaConv", __LINE__, EXEFLG_UPD, "020",
				"    kmkcd      = [%s]", kmkcd ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105UpdKekkaConv", __LINE__, EXEFLG_UPD, "020",
				"    knssu      = [%d]", knssu ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105UpdKekkaConv", __LINE__, EXEFLG_UPD, "020",
				"    knssueda   = [%d]", knssueda ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105UpdKekkaConv", __LINE__, EXEFLG_UPD, "020",
				"    knskka1    = [%s]", knskka1 ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105UpdKekkaConv", __LINE__, EXEFLG_UPD, "020",
				"    knskka2    = [%s]", knskka2 ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105UpdKekkaConv", __LINE__, EXEFLG_UPD, "020",
				"    knskka2kbn = [%s]", knskka2kbn ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105UpdKekkaConv", __LINE__, EXEFLG_UPD, "020",
				"    kkahskcd   = [%s]", kkahskcd ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105UpdKekkaConv", __LINE__, EXEFLG_UPD, "020",
				"    dtnrtts    = [%s]", dtnrtts ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105UpdKekkaConv", __LINE__, EXEFLG_UPD, "020",
				"    skkka      = [%s]", skkka ) ;
#endif

	
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 126 "GD105KekkaConv.sqc"

	
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 127 "GD105KekkaConv.sqc"


	
/*
EXEC SQL UPDATE KEKKA
	SET
	(
		KNSKKA1,
		KNSKKA2,
		KNSKKA2KBN,
		KKAHSKCD,
		DTNRTTS,
		SKKKA
	) = (
		:knskka1,
		:knskka2,
		:knskka2kbn,
		:kkahskcd,
		:dtnrtts,
		:skkka
	)
	WHERE
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd AND
		KNTNO = :kntno AND
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		KNSSU = :knssu AND
		KNSSUEDA = :knssueda;
*/

{
#line 153 "GD105KekkaConv.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 153 "GD105KekkaConv.sqc"
  sqlaaloc(2,13,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[13];
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 13;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[0].sqldata = (void*)knskka1;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 25;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[1].sqldata = (void*)knskka2;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[2].sqldata = (void*)knskka2kbn;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 4;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[3].sqldata = (void*)kkahskcd;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 9;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[4].sqldata = (void*)dtnrtts;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 25;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[5].sqldata = (void*)skkka;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[6].sqldata = (void*)knskisymd;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[7].sqldata = (void*)sriymd;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 14;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[8].sqldata = (void*)kntno;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 17;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[9].sqldata = (void*)knsgrp;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 8;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[10].sqldata = (void*)kmkcd;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[11].sqldata = (void*)&knssu;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[12].sqldata = (void*)&knssueda;
#line 153 "GD105KekkaConv.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 153 "GD105KekkaConv.sqc"
      sqlasetdata(2,0,13,sql_setdlist,0L,0L);
    }
#line 153 "GD105KekkaConv.sqc"
  sqlacall((unsigned short)24,1,2,0,0L);
#line 153 "GD105KekkaConv.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 153 "GD105KekkaConv.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 153 "GD105KekkaConv.sqc"
  sqlastop(0L);
}

#line 153 "GD105KekkaConv.sqc"


#ifdef _DEBUG
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105UpdKekkaConv", __LINE__, EXEFLG_UPD, "020",
				 "● dGD105UpdKekkaConv 出る" ) ;
#endif

	return HRC_SQL_NORMAL;

notfound:
	
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 163 "GD105KekkaConv.sqc"


	sFncPutLog( TRCKIND_ERROR, __FILE__, "dGD105UpdKekkaConv", __LINE__, EXEFLG_UPD, "020",
				"SQLERR : [%s]", sqlca.sqlerrmc );

	return HRC_SQL_NOT_FOUND;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 171 "GD105KekkaConv.sqc"


	sFncPutLog( TRCKIND_ERROR, __FILE__, "dGD105UpdKekkaConv", __LINE__, EXEFLG_UPD, "020",
				"SQLERR : [%s]", sqlca.sqlerrmc );

	return sqlca.sqlcode;
}
/** End of File *********************************************************/
