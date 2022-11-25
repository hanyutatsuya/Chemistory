static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,117,65,108,122,85,84,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,70,49,48,51,67,76,75,75,0,0,0,0,0,0,0,0,
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


#line 1 "F103clkka.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： F103ctrlkka.sqc
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

#include "F103ctrlkka.h"
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


#line 28 "F103clkka.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 33 "F103clkka.sqc"

    char    	knskisymd[11];
    char    	bskkbn[5];
    char    	bsklne[5];
    char    	bskgok[7];
    char    	knsgrp[17];
    char    	kmkcd[8];
    char    	nbkmkcd[8];
    sqlint32	ctrlno;
    char    	ctrlsbt[21];
    short   	ctrlsbteda;
    char    	ctrllbl[3];
    char    	tstrflg;
    char    	asyrckid[11];
    short   	asyrckpos;
    sqlint32   	knsseq;
    sqlint32   	bskseq;
    short   	bthno;
    sqlint32   	bthrckjbn;
    char    	syklotno[21];
    char    	sktti[25];
    char    	knzti[25];
    char    	knztistflg;
    char    	sktdh[27];
    short   	ctrljti;
    char    	chkzmflg;
    char    	facter[13];
    char    	base[13];
    char    	kosijt;
    char    	kositts[9];
    char    	kosidh[27];
    char    	ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 65 "F103clkka.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT  Ctrlkka

BmlDMMInfo  CtrlkkaArray[] = {
    DMM_SDATE( knskisymd ),
    DMM_SSTRING( bskkbn ),
    DMM_SSTRING( bsklne ),
    DMM_SSTRING( bskgok ),
    DMM_SSTRING( knsgrp ),
    DMM_SSTRING( kmkcd ),
    DMM_SSTRING( nbkmkcd ),
    DMM_SLONG( ctrlno ),
    DMM_SSTRING( ctrlsbt ),
    DMM_SSHORT( ctrlsbteda ),
    DMM_SSTRING( ctrllbl ),
    DMM_SCHAR( tstrflg ),
    DMM_SSTRING( asyrckid ),
    DMM_SSHORT( asyrckpos ),
    DMM_SLONG( knsseq ),
    DMM_SLONG( bskseq ),
    DMM_SSHORT( bthno ),
    DMM_SLONG( bthrckjbn ),
    DMM_SSTRING( syklotno ),
    DMM_SSTRING( sktti ),
    DMM_SSTRING( knzti ),
    DMM_SCHAR( knztistflg ),
    DMM_STIMESTAMP( sktdh ),
    DMM_SSHORT( ctrljti ),
    DMM_SCHAR( chkzmflg ),
    DMM_SSTRING( facter ),
    DMM_SSTRING( base ),
    DMM_SCHAR( kosijt ),
    DMM_SSTRING( kositts ),
    DMM_STIMESTAMP( kosidh ),
    DMM_STIMESTAMP( ksndh ),
    DMM_NULL
};

/******************************************************************************
 * FCtrlkkkaSelectAll()
 *    コントロール結果情報テーブルの校正日時を更新
 * ■引数
 *    [O]  Ctrlkka** arrayOut   取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long FCtrlkkkaSelectAll( Ctrlkka** arrayOut, int* numOut )
{
    Ctrlkka*    array = NULL;
    int         num = 0;
    Ctrlkka     key;

    /*
    *   検索条件をセット
    */
    memset(&key, 0, sizeof(Ctrlkka));
    /* 校正状態に'1'(自動校正)をセット */
    key.kosijt = '1';
    /* 校正日時に初期日付をセット */
    strcpy(key.kosidh, DMM_NULLTIMESTAMP);

    if( !ZbmlMapStructToHost( (char*)&key, CtrlkkaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 139 "F103clkka.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
             KNSKISYMD
            ,BSKKBN
            ,BSKLNE
            ,BSKGOK
            ,KNSGRP
            ,KMKCD
            ,NBKMKCD
            ,CTRLNO
            ,CTRLSBT
            ,CTRLSBTEDA
            ,CTRLLBL
            ,TSTRFLG
            ,ASYRCKID
            ,ASYRCKPOS
            ,KNSSEQ
            ,BSKSEQ
            ,BTHNO
            ,BTHRCKJBN
            ,SYKLOTNO
            ,SKTTI
            ,KNZTI
            ,KNZTISTFLG
            ,SKTDH
            ,CTRLJTI
            ,CHKZMFLG
            ,FACTER
            ,BASE
            ,KOSIJT
            ,KOSITTS
            ,KOSIDH
            ,KSNDH
    FROM    CTRLKKA
    WHERE   KOSIJT  = :kosijt
    AND     KOSIDH  = '1000-01-01 00:00:00.000000'
/-
    AND     KOSIDH  = :kosidh
-/
    ORDER BY
             KNSKISYMD
            ,BSKKBN
            ,BSKGOK
            ,KMKCD
            ,CTRLNO
            ,CTRLSBT
            ,CTRLSBTEDA
    FOR READ ONLY;
*/

#line 188 "F103clkka.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 190 "F103clkka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 190 "F103clkka.sqc"
  sqlaaloc(2,1,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 190 "F103clkka.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 190 "F103clkka.sqc"
      sql_setdlist[0].sqldata = (void*)&kosijt;
#line 190 "F103clkka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 190 "F103clkka.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 190 "F103clkka.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 190 "F103clkka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 190 "F103clkka.sqc"
  sqlastop(0L);
}

#line 190 "F103clkka.sqc"

    while( 1 ) {
        Ctrlkka* rec;

        
/*
EXEC SQL FETCH c1 INTO
             :knskisymd
            ,:bskkbn
            ,:bsklne
            ,:bskgok
            ,:knsgrp
            ,:kmkcd
            ,:nbkmkcd
            ,:ctrlno
            ,:ctrlsbt
            ,:ctrlsbteda
            ,:ctrllbl
            ,:tstrflg
            ,:asyrckid
            ,:asyrckpos
            ,:knsseq
            ,:bskseq
            ,:bthno
            ,:bthrckjbn
            ,:syklotno
            ,:sktti
            ,:knzti
            ,:knztistflg
            ,:sktdh
            ,:ctrljti
            ,:chkzmflg
            ,:facter
            ,:base
            ,:kosijt
            ,:kositts
            ,:kosidh
            ,:ksndh;
*/

{
#line 225 "F103clkka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 225 "F103clkka.sqc"
  sqlaaloc(3,31,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[31];
#line 225 "F103clkka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 225 "F103clkka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 225 "F103clkka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 225 "F103clkka.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 225 "F103clkka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 225 "F103clkka.sqc"
      sql_setdlist[2].sqldata = (void*)bsklne;
#line 225 "F103clkka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 7;
#line 225 "F103clkka.sqc"
      sql_setdlist[3].sqldata = (void*)bskgok;
#line 225 "F103clkka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 225 "F103clkka.sqc"
      sql_setdlist[4].sqldata = (void*)knsgrp;
#line 225 "F103clkka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 225 "F103clkka.sqc"
      sql_setdlist[5].sqldata = (void*)kmkcd;
#line 225 "F103clkka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 225 "F103clkka.sqc"
      sql_setdlist[6].sqldata = (void*)nbkmkcd;
#line 225 "F103clkka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 225 "F103clkka.sqc"
      sql_setdlist[7].sqldata = (void*)&ctrlno;
#line 225 "F103clkka.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 21;
#line 225 "F103clkka.sqc"
      sql_setdlist[8].sqldata = (void*)ctrlsbt;
#line 225 "F103clkka.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 225 "F103clkka.sqc"
      sql_setdlist[9].sqldata = (void*)&ctrlsbteda;
#line 225 "F103clkka.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 3;
#line 225 "F103clkka.sqc"
      sql_setdlist[10].sqldata = (void*)ctrllbl;
#line 225 "F103clkka.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 225 "F103clkka.sqc"
      sql_setdlist[11].sqldata = (void*)&tstrflg;
#line 225 "F103clkka.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 11;
#line 225 "F103clkka.sqc"
      sql_setdlist[12].sqldata = (void*)asyrckid;
#line 225 "F103clkka.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[13].sqltype = 500; sql_setdlist[13].sqllen = 2;
#line 225 "F103clkka.sqc"
      sql_setdlist[13].sqldata = (void*)&asyrckpos;
#line 225 "F103clkka.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 225 "F103clkka.sqc"
      sql_setdlist[14].sqldata = (void*)&knsseq;
#line 225 "F103clkka.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 225 "F103clkka.sqc"
      sql_setdlist[15].sqldata = (void*)&bskseq;
#line 225 "F103clkka.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[16].sqltype = 500; sql_setdlist[16].sqllen = 2;
#line 225 "F103clkka.sqc"
      sql_setdlist[16].sqldata = (void*)&bthno;
#line 225 "F103clkka.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 225 "F103clkka.sqc"
      sql_setdlist[17].sqldata = (void*)&bthrckjbn;
#line 225 "F103clkka.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 21;
#line 225 "F103clkka.sqc"
      sql_setdlist[18].sqldata = (void*)syklotno;
#line 225 "F103clkka.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 25;
#line 225 "F103clkka.sqc"
      sql_setdlist[19].sqldata = (void*)sktti;
#line 225 "F103clkka.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 25;
#line 225 "F103clkka.sqc"
      sql_setdlist[20].sqldata = (void*)knzti;
#line 225 "F103clkka.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 225 "F103clkka.sqc"
      sql_setdlist[21].sqldata = (void*)&knztistflg;
#line 225 "F103clkka.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 27;
#line 225 "F103clkka.sqc"
      sql_setdlist[22].sqldata = (void*)sktdh;
#line 225 "F103clkka.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[23].sqltype = 500; sql_setdlist[23].sqllen = 2;
#line 225 "F103clkka.sqc"
      sql_setdlist[23].sqldata = (void*)&ctrljti;
#line 225 "F103clkka.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 225 "F103clkka.sqc"
      sql_setdlist[24].sqldata = (void*)&chkzmflg;
#line 225 "F103clkka.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 13;
#line 225 "F103clkka.sqc"
      sql_setdlist[25].sqldata = (void*)facter;
#line 225 "F103clkka.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 13;
#line 225 "F103clkka.sqc"
      sql_setdlist[26].sqldata = (void*)base;
#line 225 "F103clkka.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 225 "F103clkka.sqc"
      sql_setdlist[27].sqldata = (void*)&kosijt;
#line 225 "F103clkka.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 9;
#line 225 "F103clkka.sqc"
      sql_setdlist[28].sqldata = (void*)kositts;
#line 225 "F103clkka.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 27;
#line 225 "F103clkka.sqc"
      sql_setdlist[29].sqldata = (void*)kosidh;
#line 225 "F103clkka.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 27;
#line 225 "F103clkka.sqc"
      sql_setdlist[30].sqldata = (void*)ksndh;
#line 225 "F103clkka.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 225 "F103clkka.sqc"
      sqlasetdata(3,0,31,sql_setdlist,0L,0L);
    }
#line 225 "F103clkka.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 225 "F103clkka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 225 "F103clkka.sqc"
  sqlastop(0L);
}

#line 225 "F103clkka.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Ctrlkka*)ZbmlRealloc( array,
                                    sizeof( Ctrlkka ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Ctrlkka ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, CtrlkkaArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 240 "F103clkka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 240 "F103clkka.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 240 "F103clkka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 240 "F103clkka.sqc"
  sqlastop(0L);
}

#line 240 "F103clkka.sqc"


    *arrayOut = array;
    *numOut   = num;


    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
printf("error code=%d %s\n",sqlca.sqlcode, &sqla_program_id[1]);
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 250 "F103clkka.sqc"

    return sqlca.sqlcode;
}


/******************************************************************************
 * FKsidhUpdate()
 *    コントロール結果情報テーブルの校正日時を更新
 * ■引数
 *    [I]  Ctrlkka* rec         更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long FKsidhUpdate( Ctrlkka* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, CtrlkkaArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 275 "F103clkka.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 276 "F103clkka.sqc"


    
/*
EXEC SQL UPDATE CTRLKKA
    SET
         KOSIDH     = CURRENT TIMESTAMP
        ,KSNDH      = CURRENT TIMESTAMP
    WHERE   KNSKISYMD   = :knskisymd
    AND     BSKKBN      = :bskkbn
    AND     BSKGOK      = :bskgok
    AND     KMKCD       = :kmkcd
    AND     CTRLNO      = :ctrlno
    AND     CTRLSBT     = :ctrlsbt
    AND     CTRLSBTEDA  = :ctrlsbteda
    ;
*/

{
#line 289 "F103clkka.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 289 "F103clkka.sqc"
  sqlaaloc(2,7,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 289 "F103clkka.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 289 "F103clkka.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 289 "F103clkka.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 289 "F103clkka.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 289 "F103clkka.sqc"
      sql_setdlist[1].sqldata = (void*)bskkbn;
#line 289 "F103clkka.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 289 "F103clkka.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 7;
#line 289 "F103clkka.sqc"
      sql_setdlist[2].sqldata = (void*)bskgok;
#line 289 "F103clkka.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 289 "F103clkka.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 289 "F103clkka.sqc"
      sql_setdlist[3].sqldata = (void*)kmkcd;
#line 289 "F103clkka.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 289 "F103clkka.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 289 "F103clkka.sqc"
      sql_setdlist[4].sqldata = (void*)&ctrlno;
#line 289 "F103clkka.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 289 "F103clkka.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 289 "F103clkka.sqc"
      sql_setdlist[5].sqldata = (void*)ctrlsbt;
#line 289 "F103clkka.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 289 "F103clkka.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 289 "F103clkka.sqc"
      sql_setdlist[6].sqldata = (void*)&ctrlsbteda;
#line 289 "F103clkka.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 289 "F103clkka.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 289 "F103clkka.sqc"
  sqlacall((unsigned short)24,2,2,0,0L);
#line 289 "F103clkka.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 289 "F103clkka.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 289 "F103clkka.sqc"
  sqlastop(0L);
}

#line 289 "F103clkka.sqc"

printf("update code=%d %s\n",sqlca.sqlcode, &sqla_program_id[1]);

    return sqlca.sqlcode;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 295 "F103clkka.sqc"

    return HRC_SQL_NOT_FOUND;

error:
printf("error code=%d %s\n",sqlca.sqlcode, &sqla_program_id[1]);
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 300 "F103clkka.sqc"


    return sqlca.sqlcode;
}
/** End of File *********************************************************/
