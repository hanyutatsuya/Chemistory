static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,79,66,84,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,52,49,90,75,78,75,77,32,0,0,0,0,0,0,0,0,
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


#line 1 "Knkmhmzk.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Knkmhmzk.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Knkmhmzk.h"
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


#line 24 "Knkmhmzk.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Knkmhmzk.sqc"

	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    kmkcd[8];
	char    sriymd1[11];
	char    kntno1[14];
	char    knt1ketflg;
	char    knsgslbcd1[4];
	short   kntzssdino1;
	char    sriymd2[11];
	char    kntno2[14];
	char    knt2ketflg;
	char    knsgslbcd2[4];
	short   kntzssdino2;
	char    sriymd3[11];
	char    kntno3[14];
	char    knt3ketflg;
	char    knsgslbcd3[4];
	short   kntzssdino3;
	char    sriymd4[11];
	char    kntno4[14];
	char    knt4ketflg;
	char    knsgslbcd4[4];
	short   kntzssdino4;
	char    sriymd5[11];
	char    kntno5[14];
	char    knt5ketflg;
	char    knsgslbcd5[4];
	short   kntzssdino5;
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 61 "Knkmhmzk.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Knkmhmzk

BmlDMMInfo	KnkmhmzkArray[] = {
	DMM_SDATE( utkymd ),
	DMM_SSTRING( irino ),
	DMM_SCHAR( iriketflg ),
	DMM_SSHORT( zssdino ),
	DMM_SSTRING( kmkcd ),
	DMM_SDATE( sriymd1 ),
	DMM_SSTRING( kntno1 ),
	DMM_SCHAR( knt1ketflg ),
	DMM_SSTRING( knsgslbcd1 ),
	DMM_SSHORT( kntzssdino1 ),
	DMM_SDATE( sriymd2 ),
	DMM_SSTRING( kntno2 ),
	DMM_SCHAR( knt2ketflg ),
	DMM_SSTRING( knsgslbcd2 ),
	DMM_SSHORT( kntzssdino2 ),
	DMM_SDATE( sriymd3 ),
	DMM_SSTRING( kntno3 ),
	DMM_SCHAR( knt3ketflg ),
	DMM_SSTRING( knsgslbcd3 ),
	DMM_SSHORT( kntzssdino3 ),
	DMM_SDATE( sriymd4 ),
	DMM_SSTRING( kntno4 ),
	DMM_SCHAR( knt4ketflg ),
	DMM_SSTRING( knsgslbcd4 ),
	DMM_SSHORT( kntzssdino4 ),
	DMM_SDATE( sriymd5 ),
	DMM_SSTRING( kntno5 ),
	DMM_SCHAR( knt5ketflg ),
	DMM_SSTRING( knsgslbcd5 ),
	DMM_SSHORT( kntzssdino5 ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKnkmhmzkSelectAll()
 *    KNKMHMZK レコード全件取得
 * ■引数
 *    [O]  Knkmhmzk** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKnkmhmzkSelectAll( Knkmhmzk** arrayOut, int* numOut )
{
    Knkmhmzk*   array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 120 "Knkmhmzk.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		KMKCD,
		SRIYMD1,
		KNTNO1,
		KNT1KETFLG,
		KNSGSLBCD1,
		KNTZSSDINO1,
		SRIYMD2,
		KNTNO2,
		KNT2KETFLG,
		KNSGSLBCD2,
		KNTZSSDINO2,
		SRIYMD3,
		KNTNO3,
		KNT3KETFLG,
		KNSGSLBCD3,
		KNTZSSDINO3,
		SRIYMD4,
		KNTNO4,
		KNT4KETFLG,
		KNSGSLBCD4,
		KNTZSSDINO4,
		SRIYMD5,
		KNTNO5,
		KNT5KETFLG,
		KNSGSLBCD5,
		KNTZSSDINO5,
		KSNDH
    FROM
        KNKMHMZK FOR READ ONLY;
*/

#line 156 "Knkmhmzk.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 158 "Knkmhmzk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 158 "Knkmhmzk.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 158 "Knkmhmzk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 158 "Knkmhmzk.sqc"
  sqlastop(0L);
}

#line 158 "Knkmhmzk.sqc"


    while( 1 ) {
        Knkmhmzk* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:kmkcd,
			:sriymd1,
			:kntno1,
			:knt1ketflg,
			:knsgslbcd1,
			:kntzssdino1,
			:sriymd2,
			:kntno2,
			:knt2ketflg,
			:knsgslbcd2,
			:kntzssdino2,
			:sriymd3,
			:kntno3,
			:knt3ketflg,
			:knsgslbcd3,
			:kntzssdino3,
			:sriymd4,
			:kntno4,
			:knt4ketflg,
			:knsgslbcd4,
			:kntzssdino4,
			:sriymd5,
			:kntno5,
			:knt5ketflg,
			:knsgslbcd5,
			:kntzssdino5,
			:ksndh;
*/

{
#line 194 "Knkmhmzk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 194 "Knkmhmzk.sqc"
  sqlaaloc(3,31,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[31];
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[5].sqldata = (void*)sriymd1;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 14;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[6].sqldata = (void*)kntno1;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[7].sqldata = (void*)&knt1ketflg;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[8].sqldata = (void*)knsgslbcd1;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[9].sqldata = (void*)&kntzssdino1;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[10].sqldata = (void*)sriymd2;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 14;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[11].sqldata = (void*)kntno2;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[12].sqltype = 452; sql_setdlist[12].sqllen = 1;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[12].sqldata = (void*)&knt2ketflg;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 4;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[13].sqldata = (void*)knsgslbcd2;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[14].sqldata = (void*)&kntzssdino2;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 11;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[15].sqldata = (void*)sriymd3;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 14;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[16].sqldata = (void*)kntno3;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[17].sqldata = (void*)&knt3ketflg;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 4;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[18].sqldata = (void*)knsgslbcd3;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[19].sqldata = (void*)&kntzssdino3;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 11;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[20].sqldata = (void*)sriymd4;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 14;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[21].sqldata = (void*)kntno4;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[22].sqldata = (void*)&knt4ketflg;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 4;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[23].sqldata = (void*)knsgslbcd4;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[24].sqltype = 500; sql_setdlist[24].sqllen = 2;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[24].sqldata = (void*)&kntzssdino4;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 11;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[25].sqldata = (void*)sriymd5;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 14;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[26].sqldata = (void*)kntno5;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[27].sqldata = (void*)&knt5ketflg;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 4;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[28].sqldata = (void*)knsgslbcd5;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[29].sqltype = 500; sql_setdlist[29].sqllen = 2;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[29].sqldata = (void*)&kntzssdino5;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 27;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[30].sqldata = (void*)ksndh;
#line 194 "Knkmhmzk.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 194 "Knkmhmzk.sqc"
      sqlasetdata(3,0,31,sql_setdlist,0L,0L);
    }
#line 194 "Knkmhmzk.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 194 "Knkmhmzk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 194 "Knkmhmzk.sqc"
  sqlastop(0L);
}

#line 194 "Knkmhmzk.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Knkmhmzk*)ZbmlRealloc( array,
                                    sizeof( Knkmhmzk ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Knkmhmzk ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KnkmhmzkArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 209 "Knkmhmzk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 209 "Knkmhmzk.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 209 "Knkmhmzk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 209 "Knkmhmzk.sqc"
  sqlastop(0L);
}

#line 209 "Knkmhmzk.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 217 "Knkmhmzk.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKnkmhmzkSelectKey()
 *    KNKMHMZK レコードKey条件取得
 * ■引数
 *    [I]  Knkmhmzk* pKey       取得するレコードのキー
 *    [O]  Knkmhmzk** arrayOut  取得レコード配列格納領域
 *    [O]  int* numOut          取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND  レコードなし
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKnkmhmzkSelectKey( Knkmhmzk* pKey, Knkmhmzk** arrayOut, int* numOut )
{
    Knkmhmzk*   array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KnkmhmzkArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 243 "Knkmhmzk.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		KMKCD,
		SRIYMD1,
		KNTNO1,
		KNT1KETFLG,
		KNSGSLBCD1,
		KNTZSSDINO1,
		SRIYMD2,
		KNTNO2,
		KNT2KETFLG,
		KNSGSLBCD2,
		KNTZSSDINO2,
		SRIYMD3,
		KNTNO3,
		KNT3KETFLG,
		KNSGSLBCD3,
		KNTZSSDINO3,
		SRIYMD4,
		KNTNO4,
		KNT4KETFLG,
		KNSGSLBCD4,
		KNTZSSDINO4,
		SRIYMD5,
		KNTNO5,
		KNT5KETFLG,
		KNSGSLBCD5,
		KNTZSSDINO5,
		KSNDH
    FROM
        KNKMHMZK
    WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		ZSSDINO = :zssdino AND
		KMKCD = :kmkcd FOR READ ONLY;
*/

#line 284 "Knkmhmzk.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 286 "Knkmhmzk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 286 "Knkmhmzk.sqc"
  sqlaaloc(2,4,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 286 "Knkmhmzk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 286 "Knkmhmzk.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 286 "Knkmhmzk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 286 "Knkmhmzk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 286 "Knkmhmzk.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 286 "Knkmhmzk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 286 "Knkmhmzk.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 286 "Knkmhmzk.sqc"
      sql_setdlist[2].sqldata = (void*)&zssdino;
#line 286 "Knkmhmzk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 286 "Knkmhmzk.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 286 "Knkmhmzk.sqc"
      sql_setdlist[3].sqldata = (void*)kmkcd;
#line 286 "Knkmhmzk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 286 "Knkmhmzk.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 286 "Knkmhmzk.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 286 "Knkmhmzk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 286 "Knkmhmzk.sqc"
  sqlastop(0L);
}

#line 286 "Knkmhmzk.sqc"


    while( 1 ) {
        Knkmhmzk* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:kmkcd,
			:sriymd1,
			:kntno1,
			:knt1ketflg,
			:knsgslbcd1,
			:kntzssdino1,
			:sriymd2,
			:kntno2,
			:knt2ketflg,
			:knsgslbcd2,
			:kntzssdino2,
			:sriymd3,
			:kntno3,
			:knt3ketflg,
			:knsgslbcd3,
			:kntzssdino3,
			:sriymd4,
			:kntno4,
			:knt4ketflg,
			:knsgslbcd4,
			:kntzssdino4,
			:sriymd5,
			:kntno5,
			:knt5ketflg,
			:knsgslbcd5,
			:kntzssdino5,
			:ksndh;
*/

{
#line 322 "Knkmhmzk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 322 "Knkmhmzk.sqc"
  sqlaaloc(3,31,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[31];
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[5].sqldata = (void*)sriymd1;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 14;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[6].sqldata = (void*)kntno1;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[7].sqldata = (void*)&knt1ketflg;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[8].sqldata = (void*)knsgslbcd1;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[9].sqldata = (void*)&kntzssdino1;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[10].sqldata = (void*)sriymd2;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 14;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[11].sqldata = (void*)kntno2;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[12].sqltype = 452; sql_setdlist[12].sqllen = 1;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[12].sqldata = (void*)&knt2ketflg;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 4;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[13].sqldata = (void*)knsgslbcd2;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[14].sqldata = (void*)&kntzssdino2;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 11;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[15].sqldata = (void*)sriymd3;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 14;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[16].sqldata = (void*)kntno3;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[17].sqldata = (void*)&knt3ketflg;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 4;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[18].sqldata = (void*)knsgslbcd3;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[19].sqldata = (void*)&kntzssdino3;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 11;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[20].sqldata = (void*)sriymd4;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 14;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[21].sqldata = (void*)kntno4;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[22].sqldata = (void*)&knt4ketflg;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 4;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[23].sqldata = (void*)knsgslbcd4;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[24].sqltype = 500; sql_setdlist[24].sqllen = 2;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[24].sqldata = (void*)&kntzssdino4;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 11;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[25].sqldata = (void*)sriymd5;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 14;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[26].sqldata = (void*)kntno5;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[27].sqldata = (void*)&knt5ketflg;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 4;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[28].sqldata = (void*)knsgslbcd5;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[29].sqltype = 500; sql_setdlist[29].sqllen = 2;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[29].sqldata = (void*)&kntzssdino5;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 27;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[30].sqldata = (void*)ksndh;
#line 322 "Knkmhmzk.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 322 "Knkmhmzk.sqc"
      sqlasetdata(3,0,31,sql_setdlist,0L,0L);
    }
#line 322 "Knkmhmzk.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 322 "Knkmhmzk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 322 "Knkmhmzk.sqc"
  sqlastop(0L);
}

#line 322 "Knkmhmzk.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Knkmhmzk*)ZbmlRealloc( array,
                                    sizeof( Knkmhmzk ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Knkmhmzk ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KnkmhmzkArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 337 "Knkmhmzk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 337 "Knkmhmzk.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 337 "Knkmhmzk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 337 "Knkmhmzk.sqc"
  sqlastop(0L);
}

#line 337 "Knkmhmzk.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 345 "Knkmhmzk.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKnkmhmzkInsert()
 *    KNKMHMZK レコードを挿入する
 * ■引数
 *    [I]  Knkmhmzk* rec       挿入レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKnkmhmzkInsert( Knkmhmzk* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KnkmhmzkArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 368 "Knkmhmzk.sqc"


    
/*
EXEC SQL INSERT INTO KNKMHMZK
    (
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		KMKCD,
		SRIYMD1,
		KNTNO1,
		KNT1KETFLG,
		KNSGSLBCD1,
		KNTZSSDINO1,
		SRIYMD2,
		KNTNO2,
		KNT2KETFLG,
		KNSGSLBCD2,
		KNTZSSDINO2,
		SRIYMD3,
		KNTNO3,
		KNT3KETFLG,
		KNSGSLBCD3,
		KNTZSSDINO3,
		SRIYMD4,
		KNTNO4,
		KNT4KETFLG,
		KNSGSLBCD4,
		KNTZSSDINO4,
		SRIYMD5,
		KNTNO5,
		KNT5KETFLG,
		KNSGSLBCD5,
		KNTZSSDINO5,
		KSNDH
    ) VALUES (
		:utkymd,
		:irino,
		:iriketflg,
		:zssdino,
		:kmkcd,
		:sriymd1,
		:kntno1,
		:knt1ketflg,
		:knsgslbcd1,
		:kntzssdino1,
		:sriymd2,
		:kntno2,
		:knt2ketflg,
		:knsgslbcd2,
		:kntzssdino2,
		:sriymd3,
		:kntno3,
		:knt3ketflg,
		:knsgslbcd3,
		:kntzssdino3,
		:sriymd4,
		:kntno4,
		:knt4ketflg,
		:knsgslbcd4,
		:kntzssdino4,
		:sriymd5,
		:kntno5,
		:knt5ketflg,
		:knsgslbcd5,
		:kntzssdino5,
		:ksndh
    );
*/

{
#line 435 "Knkmhmzk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 435 "Knkmhmzk.sqc"
  sqlaaloc(2,31,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[31];
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[5].sqldata = (void*)sriymd1;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 14;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[6].sqldata = (void*)kntno1;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[7].sqldata = (void*)&knt1ketflg;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[8].sqldata = (void*)knsgslbcd1;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[9].sqldata = (void*)&kntzssdino1;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[10].sqldata = (void*)sriymd2;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 14;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[11].sqldata = (void*)kntno2;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[12].sqltype = 452; sql_setdlist[12].sqllen = 1;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[12].sqldata = (void*)&knt2ketflg;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 4;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[13].sqldata = (void*)knsgslbcd2;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[14].sqltype = 500; sql_setdlist[14].sqllen = 2;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[14].sqldata = (void*)&kntzssdino2;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 11;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[15].sqldata = (void*)sriymd3;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 14;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[16].sqldata = (void*)kntno3;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[17].sqldata = (void*)&knt3ketflg;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 4;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[18].sqldata = (void*)knsgslbcd3;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[19].sqltype = 500; sql_setdlist[19].sqllen = 2;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[19].sqldata = (void*)&kntzssdino3;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 11;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[20].sqldata = (void*)sriymd4;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 14;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[21].sqldata = (void*)kntno4;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[22].sqldata = (void*)&knt4ketflg;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 4;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[23].sqldata = (void*)knsgslbcd4;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[24].sqltype = 500; sql_setdlist[24].sqllen = 2;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[24].sqldata = (void*)&kntzssdino4;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 11;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[25].sqldata = (void*)sriymd5;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 14;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[26].sqldata = (void*)kntno5;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[27].sqldata = (void*)&knt5ketflg;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 4;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[28].sqldata = (void*)knsgslbcd5;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[29].sqltype = 500; sql_setdlist[29].sqllen = 2;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[29].sqldata = (void*)&kntzssdino5;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 27;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[30].sqldata = (void*)ksndh;
#line 435 "Knkmhmzk.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 435 "Knkmhmzk.sqc"
      sqlasetdata(2,0,31,sql_setdlist,0L,0L);
    }
#line 435 "Knkmhmzk.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 435 "Knkmhmzk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 435 "Knkmhmzk.sqc"
  sqlastop(0L);
}

#line 435 "Knkmhmzk.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 440 "Knkmhmzk.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKnkmhmzkUpdate()
 *    KNKMHMZK レコードを更新する
 * ■引数
 *    [I]  Knkmhmzk* rec       更新対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKnkmhmzkUpdate( Knkmhmzk* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KnkmhmzkArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 464 "Knkmhmzk.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 465 "Knkmhmzk.sqc"


    
/*
EXEC SQL UPDATE KNKMHMZK
    SET (
		IRIKETFLG,
		SRIYMD1,
		KNTNO1,
		KNT1KETFLG,
		KNSGSLBCD1,
		KNTZSSDINO1,
		SRIYMD2,
		KNTNO2,
		KNT2KETFLG,
		KNSGSLBCD2,
		KNTZSSDINO2,
		SRIYMD3,
		KNTNO3,
		KNT3KETFLG,
		KNSGSLBCD3,
		KNTZSSDINO3,
		SRIYMD4,
		KNTNO4,
		KNT4KETFLG,
		KNSGSLBCD4,
		KNTZSSDINO4,
		SRIYMD5,
		KNTNO5,
		KNT5KETFLG,
		KNSGSLBCD5,
		KNTZSSDINO5,
		KSNDH
    ) = (
		:iriketflg,
		:sriymd1,
		:kntno1,
		:knt1ketflg,
		:knsgslbcd1,
		:kntzssdino1,
		:sriymd2,
		:kntno2,
		:knt2ketflg,
		:knsgslbcd2,
		:kntzssdino2,
		:sriymd3,
		:kntno3,
		:knt3ketflg,
		:knsgslbcd3,
		:kntzssdino3,
		:sriymd4,
		:kntno4,
		:knt4ketflg,
		:knsgslbcd4,
		:kntzssdino4,
		:sriymd5,
		:kntno5,
		:knt5ketflg,
		:knsgslbcd5,
		:kntzssdino5,
		:ksndh
    ) WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		ZSSDINO = :zssdino AND
		KMKCD = :kmkcd;
*/

{
#line 528 "Knkmhmzk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 528 "Knkmhmzk.sqc"
  sqlaaloc(2,31,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[31];
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[0].sqldata = (void*)&iriketflg;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd1;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[2].sqldata = (void*)kntno1;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[3].sqldata = (void*)&knt1ketflg;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 4;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[4].sqldata = (void*)knsgslbcd1;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[5].sqldata = (void*)&kntzssdino1;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[6].sqldata = (void*)sriymd2;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 14;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[7].sqldata = (void*)kntno2;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[8].sqltype = 452; sql_setdlist[8].sqllen = 1;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[8].sqldata = (void*)&knt2ketflg;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 4;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[9].sqldata = (void*)knsgslbcd2;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[10].sqltype = 500; sql_setdlist[10].sqllen = 2;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[10].sqldata = (void*)&kntzssdino2;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[11].sqldata = (void*)sriymd3;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 14;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[12].sqldata = (void*)kntno3;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[13].sqldata = (void*)&knt3ketflg;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 4;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[14].sqldata = (void*)knsgslbcd3;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[15].sqltype = 500; sql_setdlist[15].sqllen = 2;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[15].sqldata = (void*)&kntzssdino3;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 11;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[16].sqldata = (void*)sriymd4;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 14;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[17].sqldata = (void*)kntno4;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[18].sqldata = (void*)&knt4ketflg;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 4;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[19].sqldata = (void*)knsgslbcd4;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[20].sqltype = 500; sql_setdlist[20].sqllen = 2;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[20].sqldata = (void*)&kntzssdino4;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 11;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[21].sqldata = (void*)sriymd5;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 14;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[22].sqldata = (void*)kntno5;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[23].sqldata = (void*)&knt5ketflg;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 4;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[24].sqldata = (void*)knsgslbcd5;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[25].sqltype = 500; sql_setdlist[25].sqllen = 2;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[25].sqldata = (void*)&kntzssdino5;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 27;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[26].sqldata = (void*)ksndh;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 11;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[27].sqldata = (void*)utkymd;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 12;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[28].sqldata = (void*)irino;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[29].sqltype = 500; sql_setdlist[29].sqllen = 2;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[29].sqldata = (void*)&zssdino;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 8;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[30].sqldata = (void*)kmkcd;
#line 528 "Knkmhmzk.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 528 "Knkmhmzk.sqc"
      sqlasetdata(2,0,31,sql_setdlist,0L,0L);
    }
#line 528 "Knkmhmzk.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 528 "Knkmhmzk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 528 "Knkmhmzk.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 528 "Knkmhmzk.sqc"
  sqlastop(0L);
}

#line 528 "Knkmhmzk.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 533 "Knkmhmzk.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 537 "Knkmhmzk.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKnkmhmzkDelete()
 *    KNKMHMZK レコードを削除する
 * ■引数
 *    [I]  Knkmhmzk* rec       削除対象レコード
 * ■戻り値
 *    (long) HRC_SQL_NORMAL     正常終了
 *           HRC_SQL_NOT_FOUND  対象レコードなし
 *           HRC_NULL_POINTER   パラメータエラー
 *           HRC_INVALID_VALUE  設定値不正
 *           HRC_SQL_ERR        DBエラー
 ******************************************************************************/
long ZdbKnkmhmzkDelete( Knkmhmzk* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KnkmhmzkArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 561 "Knkmhmzk.sqc"


    
/*
EXEC SQL DELETE FROM KNKMHMZK
    WHERE
		UTKYMD = :utkymd AND
		IRINO = :irino AND
		ZSSDINO = :zssdino AND
		KMKCD = :kmkcd;
*/

{
#line 568 "Knkmhmzk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 568 "Knkmhmzk.sqc"
  sqlaaloc(2,4,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 568 "Knkmhmzk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 568 "Knkmhmzk.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 568 "Knkmhmzk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 568 "Knkmhmzk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 568 "Knkmhmzk.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 568 "Knkmhmzk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 568 "Knkmhmzk.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 568 "Knkmhmzk.sqc"
      sql_setdlist[2].sqldata = (void*)&zssdino;
#line 568 "Knkmhmzk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 568 "Knkmhmzk.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 568 "Knkmhmzk.sqc"
      sql_setdlist[3].sqldata = (void*)kmkcd;
#line 568 "Knkmhmzk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 568 "Knkmhmzk.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 568 "Knkmhmzk.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 568 "Knkmhmzk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 568 "Knkmhmzk.sqc"
  sqlastop(0L);
}

#line 568 "Knkmhmzk.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 573 "Knkmhmzk.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
