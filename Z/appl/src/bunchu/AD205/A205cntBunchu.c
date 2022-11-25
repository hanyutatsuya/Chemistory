static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,82,65,81,86,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,65,50,48,53,67,78,84,66,0,0,0,0,0,0,0,0,
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


#line 1 "A205cntBunchu.sqc"
/******************************************************************************/
/*   ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/*   システム名：次世代システム                                               */
/*   ファイル名：A205cntBunchu.sqc                                            */
/*   概      要：ＤＢアクセス                                                 */
/*   OS        ：SUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   言語      ：DB2/C                                                        */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/10/24     INTEC.INC      CREATE                             */
/******************************************************************************/

/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include	<stdio.h>
#include 	<stdlib.h>
#include 	<string.h>
#include	<sqlca.h>
#include	"bmllog.h"
#include	"bmlprm.h"
#include	"AD205Buntekai.h"


/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 27 "A205cntBunchu.sqc"

	char		hst_utkymd[11];
	char		hst_irino[12];
	char		hst_smpcd[8];
	char		hst_kmkcd[8];
	char		hst_sriymd[11];
	sqlint32    hst_cnt;
	short		ind_cnt;

/*
EXEC SQL END DECLARE SECTION;
*/

#line 35 "A205cntBunchu.sqc"


/******************************************************************************/
/*  関 数 名  ：cntBunchuOk                                                   */
/*  機能概要  ：分注OKデータ件数取得                                          */
/*  入    力  ：                                                              */
/*   第１引数 ：char	ymd[];	: 	基準処理日                                */
/*  出    力  ：                                                              */
/*  復帰情報  ：COUNT結果    正常終了                                         */
/*            ：0 未満       異常終了                                         */
/******************************************************************************/
int		cntBunchuOk( bun )
Bunchu		*bun;	
{
	int		ret;
	struct	sqlca	sqlca;

	/* 初期処理	*/
	//トレースログ
    sFncPutLog( TRCKIND_TRACE, __FILE__, "cntBunchuOk", __LINE__,
                EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "Start Function");

	/* ホスト変数へのキー項目セット	*/
	strcpy( hst_utkymd,	bun->utkymd );
	strcpy( hst_irino,	bun->irino );
	strcpy( hst_smpcd,	bun->smpcd );
	strcpy( hst_kmkcd,	bun->kmkcd );
	strcpy( hst_sriymd,	bun->sriymd );
	hst_cnt=0;
	ind_cnt=0;


/*
EXEC SQL SELECT	COUNT( bnckka )
	INTO	:hst_cnt	INDICATOR :ind_cnt
	FROM	bunchu
	WHERE	SRIYMD = :hst_sriymd
	AND		IRINO  = :hst_irino
	AND		SMPCD  = :hst_smpcd
	AND		KMKCD  = :hst_kmkcd
	AND		UTKYMD = :hst_utkymd
	AND		BNCKKA in ('0','4')
	;
*/

{
#line 76 "A205cntBunchu.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 76 "A205cntBunchu.sqc"
  sqlaaloc(2,5,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[0].sqldata = (void*)hst_sriymd;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[1].sqldata = (void*)hst_irino;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[2].sqldata = (void*)hst_smpcd;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[3].sqldata = (void*)hst_kmkcd;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[4].sqldata = (void*)hst_utkymd;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 76 "A205cntBunchu.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 76 "A205cntBunchu.sqc"
  sqlaaloc(3,1,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[0].sqltype = 497; sql_setdlist[0].sqllen = 4;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[0].sqldata = (void*)&hst_cnt;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[0].sqlind = &ind_cnt;
#line 76 "A205cntBunchu.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 76 "A205cntBunchu.sqc"
  sqlacall((unsigned short)24,1,2,3,0L);
#line 76 "A205cntBunchu.sqc"
  sqlastop(0L);
}

#line 76 "A205cntBunchu.sqc"


	// 標識変数による判断
	if( ind_cnt == 0 ) {
		// COUNT結果を返す（0もあり）
		ret = hst_cnt;
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "cntBunchuOk", __LINE__,
                    EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
                    "分注(bunchu)の件数取得しました。"
                    "[CNT:%d %s %s %s %s %s]",
                    hst_cnt, bun->sriymd, bun->utkymd,
                    bun->kntno, bun->irino,bun->kmkcd );
	} else {
		sFncPutLog( TRCKIND_ERROR, __FILE__, "cntBunchuOk", __LINE__,
					EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
					"分注(bunchu)の件数取得に失敗しました。"
                    "[%s %s %s %s %s]",
                    bun->sriymd, bun->utkymd,
                    bun->kntno, bun->irino,bun->kmkcd );
		ret=RTN_NG;
	}
	//トレースログ
    sFncPutLog( TRCKIND_TRACE, __FILE__, "cntBunchuOk", __LINE__,
                EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "End Function");
	return( ret );
}
// end of text
