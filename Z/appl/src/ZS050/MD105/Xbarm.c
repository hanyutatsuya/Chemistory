static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,97,65,76,106,84,81,70,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,49,49,90,84,85,78,69,50,0,0,0,0,0,0,0,0,
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


#line 1 "Xbarm.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Xbarm.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2007-06-27     waj            Create
 * --------------------------------------------------------------------
 *	Ver.	 Date			Name		   History
 * --------------------------------------------------------------------
 *	2.00	2008/09/18		K.Ameno		   X-M対応初版
 **********************************************************************/
#include <stdio.h>

#include "Xbarm.h"
#include "Kekka.h"
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


#line 29 "Xbarm.sqc"


/*--------------------------------------*/
/* DBラップ変数定義 */

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 33 "Xbarm.sqc"

	char	    knskisymd[11];
	char		bskkbn[5];
	char		bskgok[7];
	char		kmkcd[8];
	sqlint32	pltno;
	char		xbarmjtkbn;
	char		xbarmjkflg;

/*
EXEC SQL END DECLARE SECTION;
*/

#line 41 "Xbarm.sqc"



/******************************************************************************
 * ZdbXbarmJtkbnUpdateZenkai(pKey, stat)
 *    前回XBARM状態更新
 * ■引数
 *    [I]  Kekka* pKey       更新するレコードのキー
 *    [I]  char   stat       取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbXbarmJtkbnUpdateZenkai(Kekka* pKey, char stat)
{
    if( !pKey )
        return HRC_NULL_POINTER;

	strcpy(knskisymd, pKey->knskisymd);
	strcpy(bskkbn,    pKey->bskkbn);
	strcpy(bskgok,    pKey->bskgok);
	strcpy(kmkcd,     pKey->kmkcd);
	pltno      = pKey->pltno - 1;
	xbarmjtkbn = stat;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 67 "Xbarm.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 68 "Xbarm.sqc"


	
/*
EXEC SQL UPDATE XBARM
	SET XBARMJTKBN = :xbarmjtkbn
    WHERE
		KNSKISYMD = :knskisymd AND
		BSKKBN    = :bskkbn AND
		BSKGOK    = :bskgok AND
		KMKCD     = :kmkcd AND
		PLTNO     = :pltno;
*/

{
#line 77 "Xbarm.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 77 "Xbarm.sqc"
  sqlaaloc(2,6,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 77 "Xbarm.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 77 "Xbarm.sqc"
      sql_setdlist[0].sqldata = (void*)&xbarmjtkbn;
#line 77 "Xbarm.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 77 "Xbarm.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 77 "Xbarm.sqc"
      sql_setdlist[1].sqldata = (void*)knskisymd;
#line 77 "Xbarm.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 77 "Xbarm.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 77 "Xbarm.sqc"
      sql_setdlist[2].sqldata = (void*)bskkbn;
#line 77 "Xbarm.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 77 "Xbarm.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 7;
#line 77 "Xbarm.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 77 "Xbarm.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 77 "Xbarm.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 77 "Xbarm.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 77 "Xbarm.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 77 "Xbarm.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 77 "Xbarm.sqc"
      sql_setdlist[5].sqldata = (void*)&pltno;
#line 77 "Xbarm.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 77 "Xbarm.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 77 "Xbarm.sqc"
  sqlacall((unsigned short)24,1,2,0,0L);
#line 77 "Xbarm.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 77 "Xbarm.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 77 "Xbarm.sqc"
  sqlastop(0L);
}

#line 77 "Xbarm.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 82 "Xbarm.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 86 "Xbarm.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbXbarmJkflgUpdateZenkai(pKey, stat)
 *    前回XBARM確定フラグ更新
 * ■引数
 *    [I]  Kekka* pKey       更新するレコードのキー
 *    [I]  char   stat       更新する値
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbXbarmJkflgUpdateZenkai(Kekka* pKey, char stat)
{
    if( !pKey )
        return HRC_NULL_POINTER;

	strcpy(knskisymd, pKey->knskisymd);
	strcpy(bskkbn,    pKey->bskkbn);
	strcpy(bskgok,    pKey->bskgok);
	strcpy(kmkcd,     pKey->kmkcd);
	pltno      = pKey->pltno - 1;
	xbarmjkflg = stat;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 113 "Xbarm.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 114 "Xbarm.sqc"


	
/*
EXEC SQL UPDATE XBARM
	SET XBARMJKFLG = :xbarmjkflg
    WHERE
		KNSKISYMD = :knskisymd AND
		BSKKBN    = :bskkbn AND
		BSKGOK    = :bskgok AND
		KMKCD     = :kmkcd AND
		PLTNO     = :pltno;
*/

{
#line 123 "Xbarm.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 123 "Xbarm.sqc"
  sqlaaloc(2,6,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 123 "Xbarm.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 123 "Xbarm.sqc"
      sql_setdlist[0].sqldata = (void*)&xbarmjkflg;
#line 123 "Xbarm.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 123 "Xbarm.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 123 "Xbarm.sqc"
      sql_setdlist[1].sqldata = (void*)knskisymd;
#line 123 "Xbarm.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 123 "Xbarm.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 123 "Xbarm.sqc"
      sql_setdlist[2].sqldata = (void*)bskkbn;
#line 123 "Xbarm.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 123 "Xbarm.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 7;
#line 123 "Xbarm.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 123 "Xbarm.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 123 "Xbarm.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 123 "Xbarm.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 123 "Xbarm.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 123 "Xbarm.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 123 "Xbarm.sqc"
      sql_setdlist[5].sqldata = (void*)&pltno;
#line 123 "Xbarm.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 123 "Xbarm.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 123 "Xbarm.sqc"
  sqlacall((unsigned short)24,2,2,0,0L);
#line 123 "Xbarm.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 123 "Xbarm.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 123 "Xbarm.sqc"
  sqlastop(0L);
}

#line 123 "Xbarm.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 128 "Xbarm.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 132 "Xbarm.sqc"

    return sqlca.sqlcode;
}
