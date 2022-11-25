static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,118,65,118,117,84,71,77,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,70,49,48,49,67,76,73,74,0,0,0,0,0,0,0,0,
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


#line 1 "F101clijhmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： F101ctrlijhmst.sqc
 *     機能概要  ：コントロール異常判定マスタ
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

#include "F101ctrlijhmst.h"
#include "bml_misc.h"
#include "bml_db.h"
#include "bml_dmm.h"
//INTEC ADD
#include "FD101IjouChk.h"

#define ALLOC_UNIT      1


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 30 "F101clijhmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 35 "F101clijhmst.sqc"

    char    bskkbn[5];
    char    nbkmkcd[8];
    short   ctrlhnsu;
    char    kyuhniflg;
    short   sjhnsu;
    char    kaiymd[11];
    char    haiymd[11];
    char    hnktntid[9];
    char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 45 "F101clijhmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT  Ctrlijhmst

BmlDMMInfo  CtrlijhmstArray[] = {
    DMM_SSTRING( bskkbn ),
    DMM_SSTRING( nbkmkcd ),
    DMM_SSHORT( ctrlhnsu ),
    DMM_SCHAR( kyuhniflg ),
    DMM_SSHORT( sjhnsu ),
    DMM_SDATE( kaiymd ),
    DMM_SDATE( haiymd ),
    DMM_SSTRING( hnktntid ),
    DMM_STIMESTAMP( ksndh ),
    DMM_NULL
};

/******************************************************************************
 * FCtrlijhmstSelectByKey()
 *    検査結果情報テーブルを検索
 * ■引数
 *    [I]  Ctrlijhmst*  pKey         検索キー
 *    [O]  Ctrlijhmst** arrayOut     取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long FCtrlijhmstSelectByKey( Ctrlijhmst* pKey, Ctrlijhmst** arrayOut, int* numOut )
{
    Ctrlijhmst*      array = NULL;
    int         num = 0;

	// INTEC ADDトレースログ出力
    mcrPutTrace(&stEnv, TRCKIND_TRACE, "FCtrlijhmstSelectByKey", ""
						, MYAPP_LOG_ERRCODE_NON, "Start Function.");

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, CtrlijhmstArray ) )
        return HRC_INVALID_VALUE;

		
/*INTEC DEBUG STA */
	char	buf[256];
	sprintf( buf, "pKey bskkbn[%s] nbkmkcd[%s] kaiymd[%s]\n"
			,pKey->bskkbn,pKey->nbkmkcd, pKey->kaiymd);
    mcrPutTrace(&stEnv, TRCKIND_DEBUG, "FCtrlijhmstSelectByKey", ""
						, MYAPP_LOG_ERRCODE_NON, buf);
/*INTEC DEBUG END */
	

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 105 "F101clijhmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
             BSKKBN
            ,NBKMKCD
            ,CTRLHNSU
            ,KYUHNIFLG
            ,SJHNSU
            ,KAIYMD
            ,HAIYMD
            ,HNKTNTID
            ,KSNDH
    FROM    CTRLIJHTMST
    WHERE   BSKKBN      =  :bskkbn
    AND     NBKMKCD     =  :nbkmkcd
/-
    AND     CTRLHNSU    =  :ctrlhnsu
-/
    AND     KAIYMD      <= :kaiymd
/- 1.01 INTEC DELL
DEL AND     HAIYMD      >  :kaiymd
-/
    AND     HAIYMD      >=  :kaiymd
    FOR READ ONLY;
*/

#line 129 "F101clijhmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 131 "F101clijhmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 131 "F101clijhmst.sqc"
  sqlaaloc(2,4,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 131 "F101clijhmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 131 "F101clijhmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 131 "F101clijhmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 131 "F101clijhmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 131 "F101clijhmst.sqc"
      sql_setdlist[1].sqldata = (void*)nbkmkcd;
#line 131 "F101clijhmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 131 "F101clijhmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 131 "F101clijhmst.sqc"
      sql_setdlist[2].sqldata = (void*)kaiymd;
#line 131 "F101clijhmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 131 "F101clijhmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 131 "F101clijhmst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 131 "F101clijhmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 131 "F101clijhmst.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 131 "F101clijhmst.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 131 "F101clijhmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 131 "F101clijhmst.sqc"
  sqlastop(0L);
}

#line 131 "F101clijhmst.sqc"


    while( 1 ) {
        Ctrlijhmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
             :bskkbn
            ,:nbkmkcd
            ,:ctrlhnsu
            ,:kyuhniflg
            ,:sjhnsu
            ,:kaiymd
            ,:haiymd
            ,:hnktntid
            ,:ksndh;
*/

{
#line 145 "F101clijhmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 145 "F101clijhmst.sqc"
  sqlaaloc(3,9,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 145 "F101clijhmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[1].sqldata = (void*)nbkmkcd;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[2].sqldata = (void*)&ctrlhnsu;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[3].sqldata = (void*)&kyuhniflg;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[4].sqldata = (void*)&sjhnsu;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[5].sqldata = (void*)kaiymd;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[6].sqldata = (void*)haiymd;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[7].sqldata = (void*)hnktntid;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 145 "F101clijhmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 145 "F101clijhmst.sqc"
      sqlasetdata(3,0,9,sql_setdlist,0L,0L);
    }
#line 145 "F101clijhmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 145 "F101clijhmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 145 "F101clijhmst.sqc"
  sqlastop(0L);
}

#line 145 "F101clijhmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Ctrlijhmst*)ZbmlRealloc( array,
                     sizeof( Ctrlijhmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Ctrlijhmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, CtrlijhmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 160 "F101clijhmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 160 "F101clijhmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 160 "F101clijhmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 160 "F101clijhmst.sqc"
  sqlastop(0L);
}

#line 160 "F101clijhmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 168 "F101clijhmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
