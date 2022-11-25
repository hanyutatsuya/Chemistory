static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,73,66,119,117,84,71,77,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,70,49,48,49,67,76,75,65,0,0,0,0,0,0,0,0,
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


#line 1 "F101clka.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： F101ctrlkka.sqc
 *     機能概要  ：コントロール結果情報の入出力
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

#include "F101ctrlkka.h"
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


#line 30 "F101clka.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 35 "F101clka.sqc"

struct sqlCtrlkka {
    char    	knskisymd[11];
    char    	bskkbn[5];
    char    	bskgok[7];
    char    	kmkcd[8];
    char    	nbkmkcd[8];
    sqlint32    ctrlno;
    char    	ctrlsbt[21];
    short   	ctrlsbteda;
    short		ctrljti;
    char    	chkzmflg;
} recCtrlkka;

/*
EXEC SQL END DECLARE SECTION;
*/

#line 48 "F101clka.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT  Ctrlkka

/*
BmlDMMInfo  CtrlkkaArray[] = {
    DMM_SDATE( knskisymd ),
    DMM_SSTRING( bskkbn ),
    DMM_SSTRING( bskgok ),
    DMM_SSTRING( kmkcd ),
    DMM_SSTRING( nbkmkcd ),
    DMM_SLONG( ctrlno ),
    DMM_SSTRING( ctrlsbt ),
    DMM_SSHORT( ctrlsbteda ),
    DMM_SSHORT( ctrljti ),
    DMM_SCHAR( chkzmflg ),
    DMM_NULL
};
*/

/******************************************************************************
 * FCtrlkkkaSelectByKey()
 *    コントロール結果情報テーブルの校正日時を更新
 * ■引数
 *    [O]  Ctrlkka** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 *	  [I]  int  fetchCnt		取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long FCtrlkkaSelectByKey(Ctrlkka** arrayOut, int* numOut, int fetchCnt)
{
    Ctrlkka*    array = NULL;
    int         num = 0;

//INTEC ADD トレースログ出力
    mcrPutTrace(&stEnv, TRCKIND_TRACE, "FCtrlkkaSelectByKey", ""
					, MYAPP_LOG_ERRCODE_NON, "Start Function.");

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 95 "F101clka.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
             KNSKISYMD
            ,BSKKBN
            ,BSKGOK
            ,KMKCD
            ,NBKMKCD
            ,CTRLNO
            ,CTRLSBT
            ,CTRLSBTEDA
            ,CTRLJTI
            ,CHKZMFLG
    FROM    CTRLKKA
    WHERE   CHKZMFLG    = '0'
    ORDER BY
			KSNDH				/- 1.01 INTEC ADD   -/
/- 1.01 INTEC DELL
DEL          KNSKISYMD
DEL         ,BSKKBN
DEL         ,BSKGOK
DEL         ,CTRLNO
DEL         ,KMKCD
DEL         ,NBKMKCD
DEL         ,CTRLSBT
DEL         ,CTRLSBTEDA
-/
    FOR READ ONLY;
*/

#line 123 "F101clka.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 125 "F101clka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 125 "F101clka.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 125 "F101clka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 125 "F101clka.sqc"
  sqlastop(0L);
}

#line 125 "F101clka.sqc"


    while( 1 ) {
        Ctrlkka* rec;
/*
        EXEC SQL FETCH c1 INTO
             :knskisymd
            ,:bskkbn
            ,:bskgok
            ,:kmkcd
            ,:nbkmkcd
            ,:ctrlno
            ,:ctrlsbt
            ,:ctrlsbteda
            ,:ctrljti
            ,:chkzmflg;
*/
		
/*
EXEC SQL FETCH c1 INTO :recCtrlkka;
*/

{
#line 142 "F101clka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 142 "F101clka.sqc"
  sqlaaloc(3,10,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 142 "F101clka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 142 "F101clka.sqc"
      sql_setdlist[0].sqldata = (void*)recCtrlkka.knskisymd;
#line 142 "F101clka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 142 "F101clka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 142 "F101clka.sqc"
      sql_setdlist[1].sqldata = (void*)recCtrlkka.bskkbn;
#line 142 "F101clka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 142 "F101clka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 7;
#line 142 "F101clka.sqc"
      sql_setdlist[2].sqldata = (void*)recCtrlkka.bskgok;
#line 142 "F101clka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 142 "F101clka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 142 "F101clka.sqc"
      sql_setdlist[3].sqldata = (void*)recCtrlkka.kmkcd;
#line 142 "F101clka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 142 "F101clka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 142 "F101clka.sqc"
      sql_setdlist[4].sqldata = (void*)recCtrlkka.nbkmkcd;
#line 142 "F101clka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 142 "F101clka.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 142 "F101clka.sqc"
      sql_setdlist[5].sqldata = (void*)&recCtrlkka.ctrlno;
#line 142 "F101clka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 142 "F101clka.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 21;
#line 142 "F101clka.sqc"
      sql_setdlist[6].sqldata = (void*)recCtrlkka.ctrlsbt;
#line 142 "F101clka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 142 "F101clka.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 142 "F101clka.sqc"
      sql_setdlist[7].sqldata = (void*)&recCtrlkka.ctrlsbteda;
#line 142 "F101clka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 142 "F101clka.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 142 "F101clka.sqc"
      sql_setdlist[8].sqldata = (void*)&recCtrlkka.ctrljti;
#line 142 "F101clka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 142 "F101clka.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 142 "F101clka.sqc"
      sql_setdlist[9].sqldata = (void*)&recCtrlkka.chkzmflg;
#line 142 "F101clka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 142 "F101clka.sqc"
      sqlasetdata(3,0,10,sql_setdlist,0L,0L);
    }
#line 142 "F101clka.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 142 "F101clka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 142 "F101clka.sqc"
  sqlastop(0L);
}

#line 142 "F101clka.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Ctrlkka*)ZbmlRealloc( array,
                                    sizeof( Ctrlkka ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Ctrlkka ) * ALLOC_UNIT );
        }

        rec = array + num++;
/*
        ZbmlMapHostToStruct( (char*)rec, CtrlkkaArray );
*/

		memcpy(rec, &recCtrlkka, sizeof(recCtrlkka));

        if( num == fetchCnt ){
        	break;
        }
    }

/*INTEC DEBUG STA */
    char    buf[256];
    sprintf( buf, "num [%d] fetchCnt[%d] \n", num, fetchCnt );
    mcrPutTrace(&stEnv, TRCKIND_DEBUG, "FCtrlkkaSelectByKey", ""
                        , MYAPP_LOG_ERRCODE_NON, buf);
/*INTEC DEBUG END */

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 172 "F101clka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 172 "F101clka.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 172 "F101clka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 172 "F101clka.sqc"
  sqlastop(0L);
}

#line 172 "F101clka.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 180 "F101clka.sqc"

    return sqlca.sqlcode;
}


/******************************************************************************
 * FCtrlUpdate()
 *    コントロール結果情報テーブルを更新
 * ■引数
 *    [I]  Ctrlkka* rec         更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long FCtrlUpdate( Ctrlkka* rec )
{

//INTEC ADD トレースログ出力
    mcrPutTrace(&stEnv, TRCKIND_TRACE, "FCtrlUpdate", ""
					, MYAPP_LOG_ERRCODE_NON, "Start Function.");

    if( !rec )
        return HRC_NULL_POINTER;
/*
DEL   if( !ZbmlMapStructToHost( (char*)rec, CtrlkkaArray ) )
DEL     return HRC_INVALID_VALUE;
*/

	memcpy(&recCtrlkka, rec, sizeof(recCtrlkka));

/*INTEC DEBUG STA */
/*
DEL	memset( &recCtrlkka, '\0', sizeof( recCtrlkka ));
DEL strcpy(	recCtrlkka.knskisymd,	rec->knskisymd );
DEL strcpy(	recCtrlkka.bskkbn,		rec->bskkbn );
DEL strcpy(	recCtrlkka.bskgok,		rec->bskgok );
DEL strcpy(	recCtrlkka.kmkcd,		rec->kmkcd );
DEL strcpy(	recCtrlkka.nbkmkcd,		rec->nbkmkcd );
DEL recCtrlkka.ctrlno				= rec->ctrlno;
DEL strcpy(	recCtrlkka.ctrlsbt,		rec->ctrlsbt );
DEL recCtrlkka.ctrlsbteda			= rec->ctrlsbteda;
DEL recCtrlkka.ctrljti				= rec->ctrljti;
DEL recCtrlkka.chkzmflg				= rec->chkzmflg;
*/
    char    buf[512];
	memset( buf, '\0', sizeof( buf ));
    sprintf( buf, "upd flg[%c] where ymd[%s] kbn[%s]"
				 " gok[%s] kmk[%s] no[%d] "
				 " sbt[%s] eda[%d]\n"
		,recCtrlkka.chkzmflg	,recCtrlkka.knskisymd	, recCtrlkka.bskkbn
		,recCtrlkka.bskgok		, recCtrlkka.kmkcd		, recCtrlkka.ctrlno
		, recCtrlkka.ctrlsbt	, recCtrlkka.ctrlsbteda );
    mcrPutTrace(&stEnv, TRCKIND_DEBUG, "FCtrlkkaSelectByKey", ""
                        , MYAPP_LOG_ERRCODE_NON, buf);

/*INTEC DEBUG END */

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 240 "F101clka.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 241 "F101clka.sqc"

/*
DEL EXEC SQL UPDATE CTRLKKA
DEL SET
DEL          CHKZMFLG   = :chkzmflg
DEL         ,KSNDH      = CURRENT TIMESTAMP
DEL WHERE   KNSKISYMD   = :knskisymd
DEL AND     BSKKBN      = :bskkbn
DEL AND     BSKGOK      = :bskgok
DEL AND     KMKCD       = :kmkcd
DEL AND     CTRLNO      = :ctrlno
DEL AND     CTRLSBT     = :ctrlsbt
DEL AND     CTRLSBTEDA  = :ctrlsbteda
DEL AND     CHKZMFLG    = '0'
DEL ;
*/
    
/*
EXEC SQL UPDATE CTRLKKA
    SET
             CHKZMFLG   = :recCtrlkka.chkzmflg
            ,KSNDH      = CURRENT TIMESTAMP
    WHERE   KNSKISYMD   = :recCtrlkka.knskisymd
    AND     BSKKBN      = :recCtrlkka.bskkbn
    AND     BSKGOK      = :recCtrlkka.bskgok
    AND     KMKCD       = :recCtrlkka.kmkcd
    AND     CTRLNO      = :recCtrlkka.ctrlno
    AND     CTRLSBT     = :recCtrlkka.ctrlsbt
    AND     CTRLSBTEDA  = :recCtrlkka.ctrlsbteda
    AND     CHKZMFLG    = '0'
    ;
*/

{
#line 269 "F101clka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 269 "F101clka.sqc"
  sqlaaloc(2,8,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 269 "F101clka.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 269 "F101clka.sqc"
      sql_setdlist[0].sqldata = (void*)&recCtrlkka.chkzmflg;
#line 269 "F101clka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 269 "F101clka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 269 "F101clka.sqc"
      sql_setdlist[1].sqldata = (void*)recCtrlkka.knskisymd;
#line 269 "F101clka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 269 "F101clka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 269 "F101clka.sqc"
      sql_setdlist[2].sqldata = (void*)recCtrlkka.bskkbn;
#line 269 "F101clka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 269 "F101clka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 7;
#line 269 "F101clka.sqc"
      sql_setdlist[3].sqldata = (void*)recCtrlkka.bskgok;
#line 269 "F101clka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 269 "F101clka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 269 "F101clka.sqc"
      sql_setdlist[4].sqldata = (void*)recCtrlkka.kmkcd;
#line 269 "F101clka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 269 "F101clka.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 269 "F101clka.sqc"
      sql_setdlist[5].sqldata = (void*)&recCtrlkka.ctrlno;
#line 269 "F101clka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 269 "F101clka.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 21;
#line 269 "F101clka.sqc"
      sql_setdlist[6].sqldata = (void*)recCtrlkka.ctrlsbt;
#line 269 "F101clka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 269 "F101clka.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 269 "F101clka.sqc"
      sql_setdlist[7].sqldata = (void*)&recCtrlkka.ctrlsbteda;
#line 269 "F101clka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 269 "F101clka.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 269 "F101clka.sqc"
  sqlacall((unsigned short)24,2,2,0,0L);
#line 269 "F101clka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 269 "F101clka.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 269 "F101clka.sqc"
  sqlastop(0L);
}

#line 269 "F101clka.sqc"


    return sqlca.sqlcode;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 274 "F101clka.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 278 "F101clka.sqc"


    return sqlca.sqlcode;
}
/** End of File *********************************************************/
