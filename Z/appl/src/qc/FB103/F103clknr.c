static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,70,66,109,122,85,84,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,70,49,48,51,67,76,75,78,0,0,0,0,0,0,0,0,
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


#line 1 "F103clknr.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： F103ctrlknr.sqc
 *     機能概要  ：コントロール管理テーブルアクセス
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-27                    Create
 **********************************************************************/

/********************************************************************/
/*  インクルード宣言                                                */
/********************************************************************/
#include <stdio.h>

#include "F103ctrlknr.h"
#include "bml_misc.h"
#include "bml_db.h"
#include "bml_dmm.h"

#define ALLOC_UNIT      1


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 28 "F103clknr.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 33 "F103clknr.sqc"

    char    	knskisymd[11];
    char    	bskkbn[5];
    char    	bsklne[5];
    char    	bskgok[7];
    sqlint32   	ctrlno;
    char    	ctrlhdflg;
    char    	ctrlktflg;
    char    	ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 42 "F103clknr.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT  Ctrlknr

BmlDMMInfo  CtrlknrArray[] = {
    DMM_SDATE( knskisymd ),
    DMM_SSTRING( bskkbn ),
    DMM_SSTRING( bsklne ),
    DMM_SSTRING( bskgok ),
    DMM_SLONG( ctrlno ),
    DMM_SCHAR( ctrlhdflg ),
    DMM_SCHAR( ctrlktflg ),
    DMM_STIMESTAMP( ksndh ),
    DMM_NULL
};


/******************************************************************************
 * FKtflgUpdate()
 *    コントロール管理テーブルのコントロール確定フラグを更新
 * ■引数
 *    [I]  Ctrlknr* rec         更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long FKtflgUpdate( Ctrlknr* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, CtrlknrArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 83 "F103clknr.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 84 "F103clknr.sqc"


    
/*
EXEC SQL UPDATE CTRLKNR
    SET 
         CTRLKTFLG  = '1'
        ,KSNDH      = CURRENT TIMESTAMP
    WHERE   KNSKISYMD   = :knskisymd
    AND     BSKKBN      = :bskkbn
    AND     BSKGOK      = :bskgok
    AND     CTRLNO      = :ctrlno
    ;
*/

{
#line 94 "F103clknr.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 94 "F103clknr.sqc"
  sqlaaloc(2,4,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 94 "F103clknr.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 94 "F103clknr.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 94 "F103clknr.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 94 "F103clknr.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 94 "F103clknr.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 94 "F103clknr.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 94 "F103clknr.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 7;
#line 94 "F103clknr.sqc"
      sql_setdlist[2].sqldata = (void*)bskgok;
#line 94 "F103clknr.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 94 "F103clknr.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 94 "F103clknr.sqc"
      sql_setdlist[3].sqldata = (void*)&ctrlno;
#line 94 "F103clknr.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 94 "F103clknr.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 94 "F103clknr.sqc"
  sqlacall((unsigned short)24,1,2,0,0L);
#line 94 "F103clknr.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 94 "F103clknr.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 94 "F103clknr.sqc"
  sqlastop(0L);
}

#line 94 "F103clknr.sqc"

    
    return sqlca.sqlcode;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 99 "F103clknr.sqc"

    return HRC_SQL_NOT_FOUND;

error:
printf("error code=%d %s\n",sqlca.sqlcode, &sqla_program_id[1]);
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 104 "F103clknr.sqc"


    return sqlca.sqlcode;
}
/** End of File *********************************************************/
