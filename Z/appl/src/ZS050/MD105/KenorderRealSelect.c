static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,88,66,75,106,84,81,70,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,53,90,84,85,78,69,50,32,0,0,0,0,0,0,0,0,
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


#line 1 "KenorderRealSelect.sqc"
/******************************************************************************/
/* 　ＢＭＬ様向け検査システム												  */
/*																			  */
/* 　システム名：次世代システム 											  */
/* 　ファイル名：BD301_01.sqc												  */
/* 　概　　　要：結果登録													  */
/******************************************************************************/
/*	Ver.	 日付			名前		   修正内容 						  */
/* -------------------------------------------------------------------------- */
/*	1.00	 2006/07/05 	芳賀弘幸	   新規作成 						  */
/******************************************************************************/

/******************************************************************************/
/* インクルード宣言 														  */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "Realchk.h"
#include "Kenorder.h"
#include "bml_misc.h"
#include "bml_db.h"
#include "bml_dmm.h"


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 25 "KenorderRealSelect.sqc"


/******************************************************************************/
/* グローバル宣言															  */
/******************************************************************************/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 30 "KenorderRealSelect.sqc"

struct 
{
  char zrcd[5];
  char sbtkbn;
  char ksktkbn;
  char sc[6];
  char tj[6];
  char tjtni;
  char age[4];
  char agekbn;
  char sstme[9];
  char tnryo[6];
  char tnryotni;
  char renjicflg;
  char soukn1flg;
  char kanrenflg;
  char bunkkuflg;
  char kesseiflg;
  char rirekiflg;
  char syougoflg;
  char keisanflg;
  char per100flg;
  char tousekflg;
  char kisyakflg;
  char kouseiflg;
  char syoungflg;
  char soukn2flg;
  char fukaptflg;
  char yobiflg01;
  char tobiflg02;
  char yobiflg03;
  char yobiflg04;
  char yobiflg05;
} sql_Buf;

char	sel_kntno[14];
char	sel_knsgrp[17];
char	sel_kmkcd[8];
short	sel_knssu;
short	sel_knssueda;
char	sel_knskisymd[11];
char	sel_asyrckid[11];
short	sel_asyrckpos;

// ADD 2006-08-31 S.Ueda >>
sqlint32	num_realchk;
// ADD 2006-08-31 S.Ueda <<

/*
EXEC SQL END DECLARE SECTION;
*/

#line 78 "KenorderRealSelect.sqc"


/******************************************************************************/
/* 関数宣言 																  */
/******************************************************************************/

/******************************************************************************/
/*	関 数 名　：sFncSelKENORDER_REALCHK()									  */
/*	機能概要　：検査オーダー情報・即時チェック情報検索						  */
/*	入　　力　：															  */
/*　 第１引数 ：	検査開始日												  */
/*　 第２引数 ：	トレーＩＤ												  */
/*　 第３引数 ：	トレーポジションＦＲＯＭ								  */
/*　 第４引数 ：	トレーポジションＴＯ									  */
/*　 第５引数 ：	検査オーダー情報検索結果格納構造体						  */
/*　 第６引数 ：	即時チェック情報検索結果格納構造体						  */
/*　 第７引数 ：	検索データ件数											  */
/*	出　　力　：															  */
/*	復帰情報　：int 														  */
/*					 0	正常												  */
/*					 2	デッドロック										  */
/*					-1	異常												  */
/******************************************************************************/
long ZdbKenorderRealchkSelectKey( Kenorder* pKey, Kenorder** arrayOut_K, Realchk** arrayOut_R, int* numOut )
{
	int 					 irecCnt ;
	Kenorder				*rec_K ;
	Realchk 				*rec_R ;

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 107 "KenorderRealSelect.sqc"


	/***
	 ***	変数初期化
	 ***/
	irecCnt = 0 ;
	*arrayOut_K = NULL;
	*arrayOut_R = NULL;
	//	検索キー
	strcpy ( sel_kntno,  pKey->kntno ) ;
	strcpy ( sel_knsgrp, pKey->knsgrp ) ;
	strcpy ( sel_kmkcd,  pKey->kmkcd ) ;
	sel_knssu	 = pKey->knssu ;
	sel_knssueda = pKey->knssueda ;
	strcpy ( sel_knskisymd, pKey->knskisymd ) ;

	/***
	 ***	カーソル定義
	 ***/
	
/*
EXEC SQL DECLARE c1 CURSOR FOR
	SELECT	 O.ZRCD
			,O.SBTKBN
			,O.KSKTKBN
			,O.SC
			,O.TJ
			,O.TJTNI
			,O.SBTKBN
			,O.AGE
			,O.AGEKBN
			,O.SSTME
			,O.TNRYO
			,O.TNRYOTNI
			,R.RENJICFLG
			,R.SOUKN1FLG
			,R.KANRENFLG
			,R.BUNKKUFLG
			,R.KESSEIFLG
			,R.RIREKIFLG
			,R.SYOUGOFLG
			,R.KEISANFLG
			,R.PER100FLG
			,R.TOUSEKFLG
			,R.KISYAKFLG
			,R.KOUSEIFLG
			,R.SYOUNGFLG
			,R.SOUKN2FLG
			,R.FUKAPTFLG
			,R.YOBIFLG01
			,R.TOBIFLG02
			,R.YOBIFLG03
			,R.YOBIFLG04
			,R.YOBIFLG05
	  FROM	KENORDER O, REALCHK R
	 WHERE	O.KNTNO 	=  :sel_kntno
	   AND	O.KNSGRP	=  :sel_knsgrp 
	   AND	O.KMKCD 	=  :sel_kmkcd 
	   AND	O.KNSSU 	=  :sel_knssu
	   AND	O.KNSSUEDA	=  :sel_knssueda
	   AND	O.KNSKISYMD =  :sel_knskisymd 
	   AND	O.KNTNO 	=  R.KNTNO
	   AND	O.KNSGRP	=  R.KNSGRP
	   AND	O.KMKCD 	=  R.KMKCD
	   AND	O.KNSSU 	=  R.KNSSU
	   AND	O.KNSSUEDA	=  R.KNSSUEDA 
	   AND	O.KNSKISYMD =  R.KNSKISYMD
	   AND	O.SRIYMD	=  R.SRIYMD
	 FOR READ ONLY ;
*/

#line 173 "KenorderRealSelect.sqc"


	/***
	 ***	検索
	 ***/
	
/*
EXEC SQL OPEN c1 ;
*/

{
#line 178 "KenorderRealSelect.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 178 "KenorderRealSelect.sqc"
  sqlaaloc(2,6,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 178 "KenorderRealSelect.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 14;
#line 178 "KenorderRealSelect.sqc"
      sql_setdlist[0].sqldata = (void*)sel_kntno;
#line 178 "KenorderRealSelect.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 178 "KenorderRealSelect.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 178 "KenorderRealSelect.sqc"
      sql_setdlist[1].sqldata = (void*)sel_knsgrp;
#line 178 "KenorderRealSelect.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 178 "KenorderRealSelect.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 178 "KenorderRealSelect.sqc"
      sql_setdlist[2].sqldata = (void*)sel_kmkcd;
#line 178 "KenorderRealSelect.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 178 "KenorderRealSelect.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 178 "KenorderRealSelect.sqc"
      sql_setdlist[3].sqldata = (void*)&sel_knssu;
#line 178 "KenorderRealSelect.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 178 "KenorderRealSelect.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 178 "KenorderRealSelect.sqc"
      sql_setdlist[4].sqldata = (void*)&sel_knssueda;
#line 178 "KenorderRealSelect.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 178 "KenorderRealSelect.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 178 "KenorderRealSelect.sqc"
      sql_setdlist[5].sqldata = (void*)sel_knskisymd;
#line 178 "KenorderRealSelect.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 178 "KenorderRealSelect.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 178 "KenorderRealSelect.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 178 "KenorderRealSelect.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 178 "KenorderRealSelect.sqc"
  sqlastop(0L);
}

#line 178 "KenorderRealSelect.sqc"

	while( 1 ) {
		
/*
EXEC SQL FETCH c1 INTO :sql_Buf ;
*/

{
#line 180 "KenorderRealSelect.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 180 "KenorderRealSelect.sqc"
  sqlaaloc(3,31,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[31];
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[0].sqldata = (void*)sql_Buf.zrcd;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[1].sqldata = (void*)&sql_Buf.sbtkbn;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[2].sqldata = (void*)&sql_Buf.ksktkbn;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 6;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[3].sqldata = (void*)sql_Buf.sc;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 6;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[4].sqldata = (void*)sql_Buf.tj;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[5].sqldata = (void*)&sql_Buf.tjtni;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 4;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[6].sqldata = (void*)sql_Buf.age;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[7].sqldata = (void*)&sql_Buf.agekbn;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[8].sqldata = (void*)sql_Buf.sstme;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 6;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[9].sqldata = (void*)sql_Buf.tnryo;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[10].sqldata = (void*)&sql_Buf.tnryotni;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[11].sqldata = (void*)&sql_Buf.renjicflg;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[12].sqltype = 452; sql_setdlist[12].sqllen = 1;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[12].sqldata = (void*)&sql_Buf.soukn1flg;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[13].sqldata = (void*)&sql_Buf.kanrenflg;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[14].sqltype = 452; sql_setdlist[14].sqllen = 1;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[14].sqldata = (void*)&sql_Buf.bunkkuflg;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[15].sqltype = 452; sql_setdlist[15].sqllen = 1;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[15].sqldata = (void*)&sql_Buf.kesseiflg;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[16].sqldata = (void*)&sql_Buf.rirekiflg;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[17].sqldata = (void*)&sql_Buf.syougoflg;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[18].sqldata = (void*)&sql_Buf.keisanflg;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[19].sqltype = 452; sql_setdlist[19].sqllen = 1;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[19].sqldata = (void*)&sql_Buf.per100flg;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[20].sqltype = 452; sql_setdlist[20].sqllen = 1;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[20].sqldata = (void*)&sql_Buf.tousekflg;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[21].sqldata = (void*)&sql_Buf.kisyakflg;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[22].sqldata = (void*)&sql_Buf.kouseiflg;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[23].sqldata = (void*)&sql_Buf.syoungflg;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[24].sqldata = (void*)&sql_Buf.soukn2flg;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[25].sqldata = (void*)&sql_Buf.fukaptflg;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[26].sqldata = (void*)&sql_Buf.yobiflg01;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[27].sqldata = (void*)&sql_Buf.tobiflg02;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[28].sqldata = (void*)&sql_Buf.yobiflg03;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[29].sqldata = (void*)&sql_Buf.yobiflg04;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[30].sqldata = (void*)&sql_Buf.yobiflg05;
#line 180 "KenorderRealSelect.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 180 "KenorderRealSelect.sqc"
      sqlasetdata(3,0,31,sql_setdlist,0L,0L);
    }
#line 180 "KenorderRealSelect.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 180 "KenorderRealSelect.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 180 "KenorderRealSelect.sqc"
  sqlastop(0L);
}

#line 180 "KenorderRealSelect.sqc"

		if ( SQLCODE == 100 ) {
			break;
		}
		*arrayOut_K = ( Kenorder * ) realloc ( *arrayOut_K, sizeof ( Kenorder ) * ( irecCnt + 1 ) ) ;
		if ( arrayOut_K == NULL ) {
			return ( -1 ) ;
		}
		memset ( &(*arrayOut_K)[irecCnt], '\0', sizeof ( Kenorder ) ) ;
		rec_K = &(*arrayOut_K)[irecCnt] ;
		memcpy ( rec_K->zrcd,	  sql_Buf.zrcd, 	sizeof(rec_K->zrcd));
		rec_K->sbtkbn = sql_Buf.sbtkbn;
		rec_K->ksktkbn = sql_Buf.ksktkbn;
		memcpy ( rec_K->sc, 	  sql_Buf.sc,		sizeof(rec_K->sc));
		memcpy ( rec_K->tj, 	  sql_Buf.tj,		sizeof(rec_K->tj));
		rec_K->tjtni = sql_Buf.tjtni;
		memcpy ( rec_K->age,	  sql_Buf.age,		sizeof(rec_K->age));
		rec_K->agekbn = sql_Buf.agekbn;
		memcpy ( rec_K->sstme,	  sql_Buf.sstme,	sizeof(rec_K->sstme));
		memcpy ( rec_K->tnryo,	  sql_Buf.tnryo,	sizeof(rec_K->tnryo));
		rec_K->tnryotni = sql_Buf.tnryotni;
		*arrayOut_R = ( Realchk * ) realloc ( *arrayOut_R, sizeof ( Realchk ) * ( irecCnt + 1 ) ) ;
		if ( arrayOut_R == NULL ) {
			return ( -1 ) ;
		}
		memset ( &(*arrayOut_R)[irecCnt], '\0', sizeof ( Realchk ) ) ;
		rec_R = &(*arrayOut_R)[irecCnt] ;
		rec_R->renjicflg = sql_Buf.renjicflg;
		rec_R->soukn1flg = sql_Buf.soukn1flg;
		rec_R->kanrenflg = sql_Buf.kanrenflg;
		rec_R->bunkkuflg = sql_Buf.bunkkuflg;
		rec_R->kesseiflg = sql_Buf.kesseiflg;
		rec_R->rirekiflg = sql_Buf.rirekiflg;
		rec_R->syougoflg = sql_Buf.syougoflg;
		rec_R->keisanflg = sql_Buf.keisanflg;
		rec_R->per100flg = sql_Buf.per100flg;
		rec_R->tousekflg = sql_Buf.tousekflg;
		rec_R->kisyakflg = sql_Buf.kisyakflg;
		rec_R->kouseiflg = sql_Buf.kouseiflg;
		rec_R->syoungflg = sql_Buf.syoungflg;
		rec_R->soukn2flg = sql_Buf.soukn2flg;
		rec_R->fukaptflg = sql_Buf.fukaptflg;
		rec_R->yobiflg01 = sql_Buf.yobiflg01;
		rec_R->tobiflg02 = sql_Buf.tobiflg02;
		rec_R->yobiflg03 = sql_Buf.yobiflg03;
		rec_R->yobiflg04 = sql_Buf.yobiflg04;
		rec_R->yobiflg05 = sql_Buf.yobiflg05;
		irecCnt ++ ;
	}

	
/*
EXEC SQL CLOSE c1;
*/

{
#line 230 "KenorderRealSelect.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 230 "KenorderRealSelect.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 230 "KenorderRealSelect.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 230 "KenorderRealSelect.sqc"
  sqlastop(0L);
}

#line 230 "KenorderRealSelect.sqc"


	*numOut   = irecCnt ;

	return irecCnt ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 237 "KenorderRealSelect.sqc"

	return ( sqlca.sqlcode ) ;
}
// ADD 2006-08-31 S.Ueda >>
// UPD 2007-05-22 Nagata >>
/******************************************************************************/
/*	関 数 名　：sFncSel_REALCHK 											  */
/*	機能概要　：即時チェック情報検索(血清情報)								  */
/*	入　　力　：															  */
/*　 第１引数 ：	検体No													  */
/*　 第２引数 ：	検査グループ											  */
/*	出　　力　：															  */
/*	復帰情報　：long														  */
/*					 0以上	正常(realchkデータ件数) 						  */
/*					 0未満	SQL Error										  */
/* 2007-05-22 Nagata 条件追加 (アッセイラックID,アッセイラックPOS） 		  */
/******************************************************************************/
int sFncSel_REALCHK( char * aKnskisymd, char * aKntno, char * aKnsgrp,char *aAsyrckid,short aAsyrckpos )
{
	// 変数初期化
	memset( sel_kntno, '\0', sizeof(sel_kntno) );
	memset( sel_knsgrp, '\0', sizeof(sel_knsgrp) );
	memset( sel_knskisymd, '\0',sizeof(sel_knskisymd) ) ;
	memset( sel_asyrckid, '\0',sizeof(sel_asyrckid) ) ;
	sel_asyrckpos = 0 ;

	// ホスト変数へ複写
	memcpy( sel_kntno, aKntno, sizeof(sel_kntno)-1 );
	memcpy( sel_knsgrp, aKnsgrp, sizeof(sel_knsgrp)-1 );
	strcpy ( sel_knskisymd, aKnskisymd ) ;
	strcpy ( sel_asyrckid, aAsyrckid ) ;
	sel_asyrckpos = aAsyrckpos;

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 270 "KenorderRealSelect.sqc"


	
/*
EXEC SQL
		SELECT	COUNT(*)
		INTO	:num_realchk
		FROM	REALCHK R,kenorder K
		WHERE	R.KNTNO   = :sel_kntno
		 AND	R.KNSGRP  = :sel_knsgrp
		 AND	R.KNSKISYMD   = :sel_knskisymd
		 AND	R.KESSEIPARA != '00'
		 AND	K.ASYRCKID = :sel_asyrckid
		 AND	K.ASYRCKPOS = :sel_asyrckpos
		 AND	R.KNSKISYMD = K.KNSKISYMD
		 AND	R.SRIYMD = K.SRIYMD
		 AND	R.KNTNO = K.KNTNO
		 AND	R.KNSGRP = K.KNSGRP
		 AND	R.KMKCD = K.KMKCD
		 AND	R.KNSSU = K.KNSSU
		 AND	R.KNSSUEDA = K.KNSSUEDA
	;
*/

{
#line 289 "KenorderRealSelect.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 289 "KenorderRealSelect.sqc"
  sqlaaloc(2,5,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 289 "KenorderRealSelect.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 14;
#line 289 "KenorderRealSelect.sqc"
      sql_setdlist[0].sqldata = (void*)sel_kntno;
#line 289 "KenorderRealSelect.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 289 "KenorderRealSelect.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 289 "KenorderRealSelect.sqc"
      sql_setdlist[1].sqldata = (void*)sel_knsgrp;
#line 289 "KenorderRealSelect.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 289 "KenorderRealSelect.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 289 "KenorderRealSelect.sqc"
      sql_setdlist[2].sqldata = (void*)sel_knskisymd;
#line 289 "KenorderRealSelect.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 289 "KenorderRealSelect.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 289 "KenorderRealSelect.sqc"
      sql_setdlist[3].sqldata = (void*)sel_asyrckid;
#line 289 "KenorderRealSelect.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 289 "KenorderRealSelect.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 289 "KenorderRealSelect.sqc"
      sql_setdlist[4].sqldata = (void*)&sel_asyrckpos;
#line 289 "KenorderRealSelect.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 289 "KenorderRealSelect.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 289 "KenorderRealSelect.sqc"
  sqlaaloc(3,1,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 289 "KenorderRealSelect.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 289 "KenorderRealSelect.sqc"
      sql_setdlist[0].sqldata = (void*)&num_realchk;
#line 289 "KenorderRealSelect.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 289 "KenorderRealSelect.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 289 "KenorderRealSelect.sqc"
  sqlacall((unsigned short)24,2,2,3,0L);
#line 289 "KenorderRealSelect.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 289 "KenorderRealSelect.sqc"
  sqlastop(0L);
}

#line 289 "KenorderRealSelect.sqc"

		/* SELECT	COUNT(*)
		INTO	:num_realchk
		FROM	REALCHK
		WHERE	KNTNO	= :sel_kntno
		 AND	KNSGRP	= :sel_knsgrp
		 AND	KNSKISYMD	= :sel_knskisymd
		 AND	KESSEIPARA != '00'
	; */

	return num_realchk;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 302 "KenorderRealSelect.sqc"

	return ( sqlca.sqlcode ) ;
}
// UPD 2007-05-22 Nagata >>
// ADD 2006-08-31 S.Ueda <<
/** End of File *********************************************************/
