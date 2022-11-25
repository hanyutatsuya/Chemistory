static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,67,65,76,106,84,81,70,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,55,90,84,85,78,69,50,32,0,0,0,0,0,0,0,0,
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


#line 1 "Kkafltmst2.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名： Kkafltmst.sqc
 *     機能概要  ：
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Kkafltmst2.h"
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


#line 24 "Kkafltmst2.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Kkafltmst2.sqc"

	char    knsgrp[17];
	char    kmkcd[8];
	char    fltkka[25];
	char    minval[13];
	char    maxval[13];
	char    knskka1[13];
	char    knskka2[25];
	char    knskka2kbn[3];
	char    kkahskcd[4];
	char    hjkka[25];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
	char 	sstcd[8];
	char 	tkykbn[2];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 46 "Kkafltmst2.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Kkafltmst2

BmlDMMInfo	KkafltmstArray2[] = {
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( fltkka ),
	DMM_SSTRING( minval ),
	DMM_SSTRING( maxval ),
	DMM_SSTRING( knskka1 ),
	DMM_SSTRING( knskka2 ),
	DMM_SSTRING( knskka2kbn ),
	DMM_SSTRING( kkahskcd ),
	DMM_SSTRING( hjkka ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_SSTRING( sstcd ),
	DMM_SSTRING( tkykbn ),
	DMM_NULL
};

long ZdbKkafltmstSelectGRPKMKKey2( Kkafltmst2* pKey, Kkafltmst2** arrayOut, int* numOut )
{
    Kkafltmst2*  array = NULL;
    int         num = 0;
	int 		tkykbnflg = 0; //1ならNOT FOUNDを返します。
	int 		sscdflg = 0; //施設コードが1件目に"0000000"のチェック
    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KkafltmstArray2 ) )
        return HRC_INVALID_VALUE;


    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 87 "Kkafltmst2.sqc"


    
/*
EXEC SQL DECLARE c3 CURSOR FOR
    SELECT
		KNSGRP,
		KMKCD,
		FLTKKA,
		MINVAL,
		MAXVAL,
		KNSKKA1,
		KNSKKA2,
		KNSKKA2KBN,
		KKAHSKCD,
		HJKKA,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH,
		SSTCD,
		TKYKBN
    FROM
        KKAFLTMST
    WHERE
		KNSGRP = :knsgrp AND 
		KMKCD = :kmkcd AND
		KAIYMD <= CURRENT DATE AND
		HAIYMD >= CURRENT DATE AND
		(SSTCD = '0000000' OR
		 SSTCD = :sstcd)
		
		ORDER BY SSTCD DESC
		FOR READ ONLY;
*/

#line 118 "Kkafltmst2.sqc"



    
/*
EXEC SQL OPEN c3;
*/

{
#line 121 "Kkafltmst2.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 121 "Kkafltmst2.sqc"
  sqlaaloc(2,3,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 121 "Kkafltmst2.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 121 "Kkafltmst2.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 121 "Kkafltmst2.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 121 "Kkafltmst2.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 121 "Kkafltmst2.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 121 "Kkafltmst2.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 121 "Kkafltmst2.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 121 "Kkafltmst2.sqc"
      sql_setdlist[2].sqldata = (void*)sstcd;
#line 121 "Kkafltmst2.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 121 "Kkafltmst2.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 121 "Kkafltmst2.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 121 "Kkafltmst2.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 121 "Kkafltmst2.sqc"
  sqlastop(0L);
}

#line 121 "Kkafltmst2.sqc"


//FOR READ ONLY;
    while( 1 ) {
        Kkafltmst2* rec;

        
/*
EXEC SQL FETCH c3 INTO
			:knsgrp,
			:kmkcd,
			:fltkka,
			:minval,
			:maxval,
			:knskka1,
			:knskka2,
			:knskka2kbn,
			:kkahskcd,
			:hjkka,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh,
			:sstcd,
			:tkykbn
			;
*/

{
#line 144 "Kkafltmst2.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 144 "Kkafltmst2.sqc"
  sqlaaloc(3,16,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[16];
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 25;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[2].sqldata = (void*)fltkka;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 13;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[3].sqldata = (void*)minval;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 13;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[4].sqldata = (void*)maxval;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 13;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[5].sqldata = (void*)knskka1;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 25;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[6].sqldata = (void*)knskka2;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[7].sqldata = (void*)knskka2kbn;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[8].sqldata = (void*)kkahskcd;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 25;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[9].sqldata = (void*)hjkka;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[10].sqldata = (void*)kaiymd;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[11].sqldata = (void*)haiymd;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[12].sqldata = (void*)hnktntid;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 27;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[13].sqldata = (void*)ksndh;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 8;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[14].sqldata = (void*)sstcd;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 2;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[15].sqldata = (void*)tkykbn;
#line 144 "Kkafltmst2.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 144 "Kkafltmst2.sqc"
      sqlasetdata(3,0,16,sql_setdlist,0L,0L);
    }
#line 144 "Kkafltmst2.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 144 "Kkafltmst2.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 144 "Kkafltmst2.sqc"
  sqlastop(0L);
}

#line 144 "Kkafltmst2.sqc"


        if( SQLCODE == 100 )
            break;


		//(KkafltmstArray2+14)->pchHost -> sstcd(施設コード)
		char *tmp_sstcd = (KkafltmstArray2+14)->pchHost;

		
		if(strcmp(tmp_sstcd,"0000000")==0 && num == 0)
		{
			sscdflg = 1;//１件目から施設コードが"0000000"の場合
		}
		else if(sscdflg == 0 && strcmp(tmp_sstcd,"0000000")==0 && num > 0)
		{
			break;	//1件目以降に"0000000"が出る場合
		}	

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kkafltmst2*)ZbmlRealloc( array,
                                    sizeof( Kkafltmst2 ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kkafltmst2 ) * ALLOC_UNIT );
        }
        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KkafltmstArray2 );
	
		if(rec->tkykbn[0] == '1'){
			ZbmlFree(rec);
			*numOut  = 0;
			tkykbnflg = 1;
			break;
		}
    }

    
/*
EXEC SQL CLOSE c3;
*/

{
#line 179 "Kkafltmst2.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 179 "Kkafltmst2.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 179 "Kkafltmst2.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 179 "Kkafltmst2.sqc"
  sqlastop(0L);
}

#line 179 "Kkafltmst2.sqc"

	if(tkykbnflg == 1)
		return HRC_SQL_NOT_FOUND;
    
	*arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 189 "Kkafltmst2.sqc"

    return sqlca.sqlcode;
}

/** End of File *********************************************************/
