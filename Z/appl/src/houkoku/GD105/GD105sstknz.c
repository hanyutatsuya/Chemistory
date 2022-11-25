static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,70,66,70,52,85,97,68,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,49,48,71,49,48,53,32,32,0,0,0,0,0,0,0,0,
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


#line 1 "GD105sstknz.sqc"
/******************************************************************************/
/*   ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/*   システム名：次世代システム                                               */
/*   ファイル名：GD105sstkzn.sqc                                              */
/*   概      要：施設別換算編集                                               */
/*   OS        ：SUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   言語      ：DB2/C                                                        */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/05/03     INTEC.INC      CREATE                             */
/*  2.00     2007/04/25     INTEC.INC      UPDATE CURSOR CLOSE                */
/******************************************************************************/

/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include	<stdio.h>
#include 	<stdlib.h>
#include 	<string.h>
#include	<sqlca.h>
#include	"bml_base.h"
#include	"bmllog.h"
#include	"GD105Kekka.h"


/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 28 "GD105sstknz.sqc"

struct	_SSTSRMST {
	char	sstcd[7+1];
	char	knsgrp[16+1];
	char	kmkcd[7+1];
	char	prm1[50+1];
	char	prm2[50+1];
	char	prm3[50+1];
} hsstsrmst;

/*
struct	_SSTKJMST {
	char	lw1[3][8+1];
	char	lw2[3][8+1];
	char	kjnlw[3][8+1];
	char	kj1[3][8+1];
	char	kj2[3][8+1];
	char	kjnhi[3][8+1];
	char	hi1[3][8+1];
	char	hi2[3][8+1];
} hsstkjmst;
*/

struct	_SSTKJMST {
	char	sstcd[7+1];
	struct	_KJM {
		char	lw1_m[8+1];
		char	lw2_m[8+1];
		char	kjnlw_m[8+1];
		char	kj1_m[8+1];
		char	kj2_m[8+1];
		char	kjnhi_m[8+1];
		char	hi1_m[8+1];
		char	hi2_m[8+1];
	} hkjm;
	struct	_KJF {
		char	lw1_f[8+1];
		char	lw2_f[8+1];
		char	kjnlw_f[8+1];
		char	kj1_f[8+1];
		char	kj2_f[8+1];
		char	kjnhi_f[8+1];
		char	hi1_f[8+1];
		char	hi2_f[8+1];
	} hkjf;
	struct	_KJE {
		char	lw1_e[8+1];
		char	lw2_e[8+1];
		char	kjnlw_e[8+1];
		char	kj1_e[8+1];
		char	kj2_e[8+1];
		char	kjnhi_e[8+1];
		char	hi1_e[8+1];
		char	hi2_e[8+1];
	} hkje;
} hsstkjmst;

	char	hst_sstcd[7+1];
	char	hst_kmkcd[7+1];
	char	hst_kjno[3+1];
	char	hst_ymd[10+1];


/*
EXEC SQL END DECLARE SECTION;
*/

#line 90 "GD105sstknz.sqc"


/******************************************************************************/
/*  関 数 名  ：GD105_sstknz                                                  */
/*  機能概要  ：施設換算処理                                                  */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  _Kekka *kek;   :結果情報                              */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		GD105_sstknz( kek )
 struct	_Kekka		*kek;
{
	int		ret;
	struct	sqlca			sqlca;

	/* 初期処理	*/
#ifdef _TRACE
	//トレースログ
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD105_sstknz", __LINE__, EXEFLG_NON, "00000000",
				"Start Function");
#endif

	// コード結果は対象外
	if( kek->knskka2kbn[0] == '0' ){
		return( RTN_OK );
	}

	//	施設別換算	+++++++++++++++++++++++++++++++++++++++++++++++++++++
	/* ======================== */
	/*	施設別処理マスタの取得	*/
	/* ======================== */
		// ホスト変数へのキー項目セット
	memset( &hsstsrmst,	'\0',	sizeof( struct	_SSTSRMST ));
	strcpy( hst_ymd,			kek->knskisymd );
	strcpy( hsstsrmst.sstcd,	kek->sstcd );
	strcpy( hsstsrmst.kmkcd,	kek->kmkcd );


/*
EXEC SQL DECLARE ssr_cur CURSOR FOR
	SELECT	knsgrp
			, prm1 	
			, prm2
			, prm3
	FROM	sstsrmst
	WHERE	sstcd	=	:hsstsrmst.sstcd
	AND		kmkcd	=	:hsstsrmst.kmkcd
	AND		syrsbt	=	'KZN'
	AND		kaiymd	<=	:hst_ymd
	AND		haiymd	>=	:hst_ymd
	ORDER BY knsgrp DESC
	FOR READ ONLY;
*/

#line 141 "GD105sstknz.sqc"

	;


/*
EXEC SQL OPEN ssr_cur;
*/

{
#line 144 "GD105sstknz.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 144 "GD105sstknz.sqc"
  sqlaaloc(2,4,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 144 "GD105sstknz.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 144 "GD105sstknz.sqc"
      sql_setdlist[0].sqldata = (void*)hsstsrmst.sstcd;
#line 144 "GD105sstknz.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 144 "GD105sstknz.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 144 "GD105sstknz.sqc"
      sql_setdlist[1].sqldata = (void*)hsstsrmst.kmkcd;
#line 144 "GD105sstknz.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 144 "GD105sstknz.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 144 "GD105sstknz.sqc"
      sql_setdlist[2].sqldata = (void*)hst_ymd;
#line 144 "GD105sstknz.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 144 "GD105sstknz.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 144 "GD105sstknz.sqc"
      sql_setdlist[3].sqldata = (void*)hst_ymd;
#line 144 "GD105sstknz.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 144 "GD105sstknz.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 144 "GD105sstknz.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 144 "GD105sstknz.sqc"
  sqlastop(0L);
}

#line 144 "GD105sstknz.sqc"


	while( sqlca.sqlcode == 0 ){

/*
EXEC SQL FETCH ssr_cur
		INTO	:hsstsrmst.knsgrp
				, :hsstsrmst.prm1
				, :hsstsrmst.prm2
				, :hsstsrmst.prm3
		;
*/

{
#line 152 "GD105sstknz.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 152 "GD105sstknz.sqc"
  sqlaaloc(3,4,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 152 "GD105sstknz.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 152 "GD105sstknz.sqc"
      sql_setdlist[0].sqldata = (void*)hsstsrmst.knsgrp;
#line 152 "GD105sstknz.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 152 "GD105sstknz.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 51;
#line 152 "GD105sstknz.sqc"
      sql_setdlist[1].sqldata = (void*)hsstsrmst.prm1;
#line 152 "GD105sstknz.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 152 "GD105sstknz.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 51;
#line 152 "GD105sstknz.sqc"
      sql_setdlist[2].sqldata = (void*)hsstsrmst.prm2;
#line 152 "GD105sstknz.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 152 "GD105sstknz.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 51;
#line 152 "GD105sstknz.sqc"
      sql_setdlist[3].sqldata = (void*)hsstsrmst.prm3;
#line 152 "GD105sstknz.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 152 "GD105sstknz.sqc"
      sqlasetdata(3,0,4,sql_setdlist,0L,0L);
    }
#line 152 "GD105sstknz.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 152 "GD105sstknz.sqc"
  sqlastop(0L);
}

#line 152 "GD105sstknz.sqc"



		if ( sqlca.sqlcode == 0 ) {		/* OK */
			// 施設換算対象
/* del 20070613 waj 速度アップ
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105_sstknz", __LINE__,
						EXEFLG_SEL, "020",
						"SSTSRMST FOUND [%s-%s][%s]", 
						hsstsrmst.sstcd, hsstsrmst.kmkcd, hsstsrmst.knsgrp );	
*/
			// 2.01 ADD
			ret = RTN_OK;
			break;
		} else  if ( sqlca.sqlcode == 100 ){	/* NOT FOUND */
			// 2.01 UPD
			//return( RTN_OK );
			ret = RTN_ZERO;
			break;
		} else {
			// ERROR
			sFncPutLog( TRCKIND_WARNING, __FILE__, "GD105_sstknz", __LINE__,
						EXEFLG_SEL, "020",
						"SSTSRMST SELECT ERROR [%d][%s-%s]", 
						sqlca.sqlcode, hsstsrmst.sstcd, hsstsrmst.kmkcd);	
			// 2.01 UPD
			//return( RTN_OK );
			ret = RTN_DBERR;
			break;
		}
		// １件読み込んだら抜ける
		break;
	}

/*
EXEC SQL CLOSE	ssr_cur;
*/

{
#line 185 "GD105sstknz.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 185 "GD105sstknz.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 185 "GD105sstknz.sqc"
  sqlastop(0L);
}

#line 185 "GD105sstknz.sqc"


	// 2.01 ADD
	if( ret != RTN_OK ){
		return( RTN_OK );
	}


	/* ======== */
	/*	換算	*/
	/* ======== */
	char	c_knskka1[13];
	int		place;					// 小数点以下の桁数
	double	w_calc;
	double	w_zero = 0;
	double	k_knskka1;
	double	d_knskka1;
	double	d_prm2;
	double	d_prm3;

	// 小数点以下の桁数の取得
	place = ( strlen( kek->knskka1 ) - strcspn( kek->knskka1, "." ) );
		// .分を-1する
	if( place > 0 ){
		place--;
	}

	// 各値をdoubleに変換
	d_knskka1	= atof( kek->knskka1 );
	d_prm2		= atof( hsstsrmst.prm2 );
	d_prm3		= atof( hsstsrmst.prm3 );

	if( hsstsrmst.prm1[0] == '1' ){
		// 施設別換算値=(DOUBLE［検査結果１］+ PRM2 ) / PRM3
		w_calc = d_knskka1 + d_prm2 ;
		if( w_calc <= 0 ){
			k_knskka1 = 0;
		} else {
			k_knskka1 = w_calc / d_prm3;
		}
	} else if( hsstsrmst.prm1[0] == '2' ){
		// 施設別換算値=(DOUBLE［検査結果１］* PRM2 ) + PRM3
		k_knskka1 = d_knskka1 * d_prm2;
		if( k_knskka1 <= 0 ){
			k_knskka1 = 0;
		} else {
			k_knskka1 = k_knskka1 + d_prm3;
		}
	} else {
		// 想定外のため換算対象外とする
		return( RTN_OK );
	}

	/* ================ */
	// 換算後の結果編集
	/* ================ */
	memset( c_knskka1,	'\0',	sizeof( c_knskka1 ));
		// overflow check -> 後日報告
	if((( place == 0 ) && ( k_knskka1 > 99999999 ))
	 ||(( place >  0 ) && ( k_knskka1 >  9999999 ))){
			// 編集して処理を抜ける
		strcpy( kek->knskka1	," " );		// 結果１
		strcpy( kek->knskka2	,"0338" );	// 結果２
		strcpy( kek->knskka2kbn	,"0" );		// 結果２区分
		strcpy( kek->kkahskcd	," " );		// 結果補足
		kek->kkaksflg = '1';				// 換算フラグ
		kek->ijkbnm = ' ';					// 異常値区分
		kek->ijkbnf = ' ';
		kek->ijkbnn = ' ';
		return( RTN_OK );

	} else {
		// 倍精度の桁落ち対応で値に"0.00001"を加えsprintfを行なう
		w_calc = k_knskka1 + 0.00001;
			// 幅=結果情報.結果1  精度=小数点以下桁数
		sprintf( c_knskka1, "%*.*f", 
				( sizeof( kek->knskka1 ) - 1) ,place, w_calc );
	}

	//	異常値区分再判定	++++++++++++++++++++++++++++++++++++++++++++++++
	/* ============================ */
	/*	施設別基準値マスタの取得	*/
	/* ============================ */
	/* ホスト変数へのキー項目セット	*/
	memset( &hsstkjmst,	'\0', sizeof( struct _SSTKJMST ));
	strcpy( hst_sstcd,	kek->sstcd );
	strcpy( hst_kmkcd,	kek->kmkcd );
	strcpy( hst_kjno,	kek->kjno );


/*
EXEC SQL DECLARE skj_cur CURSOR FOR
	SELECT	sstcd
			, lwm1
			, lwm2
			, kjnmlw 	
			, kjm1
			, kjm2
			, kjnmhi
			, him1
			, him2
			, lwf1
			, lwf2
			, kjnflw 	
			, kjnnaf1
			, kjnnaf2
			, kjnfhi
			, hif1
			, hif2
			, lwe1
			, lwe2
			, kjnelw 	
			, kje1
			, kje2
			, kjnehi
			, hie1
			, hie2
	FROM	sstkjmst
	WHERE	kmkcd	=	:hst_kmkcd
	AND		kjno	=	:hst_kjno
	AND	(	sstcd	=	:hst_sstcd
		OR	sstcd	=	'0000000'
		)
	AND		kaiymd	<=	:hst_ymd
	AND		haiymd	>=	:hst_ymd
	ORDER BY sstcd DESC
	FOR READ ONLY;
*/

#line 309 "GD105sstknz.sqc"

	;


/*
EXEC SQL OPEN skj_cur;
*/

{
#line 312 "GD105sstknz.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 312 "GD105sstknz.sqc"
  sqlaaloc(2,5,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 312 "GD105sstknz.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 312 "GD105sstknz.sqc"
      sql_setdlist[0].sqldata = (void*)hst_kmkcd;
#line 312 "GD105sstknz.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 312 "GD105sstknz.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 4;
#line 312 "GD105sstknz.sqc"
      sql_setdlist[1].sqldata = (void*)hst_kjno;
#line 312 "GD105sstknz.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 312 "GD105sstknz.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 312 "GD105sstknz.sqc"
      sql_setdlist[2].sqldata = (void*)hst_sstcd;
#line 312 "GD105sstknz.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 312 "GD105sstknz.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 312 "GD105sstknz.sqc"
      sql_setdlist[3].sqldata = (void*)hst_ymd;
#line 312 "GD105sstknz.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 312 "GD105sstknz.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 312 "GD105sstknz.sqc"
      sql_setdlist[4].sqldata = (void*)hst_ymd;
#line 312 "GD105sstknz.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 312 "GD105sstknz.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 312 "GD105sstknz.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 312 "GD105sstknz.sqc"
  sqlastop(0L);
}

#line 312 "GD105sstknz.sqc"


	while( sqlca.sqlcode == 0 ){

/*
EXEC SQL FETCH skj_cur
		INTO	:hsstkjmst
		;
*/

{
#line 317 "GD105sstknz.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 317 "GD105sstknz.sqc"
  sqlaaloc(3,25,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[25];
#line 317 "GD105sstknz.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[0].sqldata = (void*)hsstkjmst.sstcd;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 9;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[1].sqldata = (void*)hsstkjmst.hkjm.lw1_m;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 9;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[2].sqldata = (void*)hsstkjmst.hkjm.lw2_m;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 9;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[3].sqldata = (void*)hsstkjmst.hkjm.kjnlw_m;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 9;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[4].sqldata = (void*)hsstkjmst.hkjm.kj1_m;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 9;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[5].sqldata = (void*)hsstkjmst.hkjm.kj2_m;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 9;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[6].sqldata = (void*)hsstkjmst.hkjm.kjnhi_m;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 9;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[7].sqldata = (void*)hsstkjmst.hkjm.hi1_m;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[8].sqldata = (void*)hsstkjmst.hkjm.hi2_m;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 9;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[9].sqldata = (void*)hsstkjmst.hkjf.lw1_f;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 9;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[10].sqldata = (void*)hsstkjmst.hkjf.lw2_f;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[11].sqldata = (void*)hsstkjmst.hkjf.kjnlw_f;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[12].sqldata = (void*)hsstkjmst.hkjf.kj1_f;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[13].sqldata = (void*)hsstkjmst.hkjf.kj2_f;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 9;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[14].sqldata = (void*)hsstkjmst.hkjf.kjnhi_f;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[15].sqldata = (void*)hsstkjmst.hkjf.hi1_f;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 9;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[16].sqldata = (void*)hsstkjmst.hkjf.hi2_f;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 9;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[17].sqldata = (void*)hsstkjmst.hkje.lw1_e;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 9;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[18].sqldata = (void*)hsstkjmst.hkje.lw2_e;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 9;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[19].sqldata = (void*)hsstkjmst.hkje.kjnlw_e;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 9;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[20].sqldata = (void*)hsstkjmst.hkje.kj1_e;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 9;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[21].sqldata = (void*)hsstkjmst.hkje.kj2_e;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 9;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[22].sqldata = (void*)hsstkjmst.hkje.kjnhi_e;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 9;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[23].sqldata = (void*)hsstkjmst.hkje.hi1_e;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 9;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[24].sqldata = (void*)hsstkjmst.hkje.hi2_e;
#line 317 "GD105sstknz.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 317 "GD105sstknz.sqc"
      sqlasetdata(3,0,25,sql_setdlist,0L,0L);
    }
#line 317 "GD105sstknz.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 317 "GD105sstknz.sqc"
  sqlastop(0L);
}

#line 317 "GD105sstknz.sqc"


		if ( sqlca.sqlcode == 0 ) {		/* OK */
			// 施設換算対象
/* del 20070613 waj 速度アップ
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105_sstknz", __LINE__,
						EXEFLG_SEL, "020",
						"SSTKJMST FOUND [%s][%s][%s]", 
						hst_sstcd, hst_kmkcd, hst_kjno );	
*/
			// 2.01 ADD
			ret = RTN_OK;
			break;
		} else  if ( sqlca.sqlcode == 100 ){	/* NOT FOUND */
			// 施設換算対象外
			sFncPutLog( TRCKIND_WARNING, __FILE__, "GD105_sstknz", __LINE__,
						EXEFLG_SEL, "020",
						"施設別基準マスタに該当なし[%s][%s][%s]", 
						hst_sstcd, hst_kmkcd, hst_kjno );	
			// 2.01 UPD
			//return( RTN_OK );
			ret = RTN_ZERO;
			break;
		} else {
			// ERROR
			sFncPutLog( TRCKIND_WARNING, __FILE__, "GD105_sstknz", __LINE__,
						EXEFLG_SEL, "020",
						"SSTKJMST SELECT ERROR [%d][%s][%s][%s]", 
						sqlca.sqlcode, hst_sstcd, hst_kmkcd, hst_kjno );	
			// 2.01 UPD
			//return( RTN_OK );
			ret = RTN_DBERR;
			break;
		}
		// １件読み込んだら抜ける
		break;
	}

/*
EXEC SQL    CLOSE   skj_cur;
*/

{
#line 354 "GD105sstknz.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 354 "GD105sstknz.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 354 "GD105sstknz.sqc"
  sqlastop(0L);
}

#line 354 "GD105sstknz.sqc"


	// 2.01 ADD
	if( ret != RTN_OK ){
		return( RTN_OK );
	}

	// 判定  index = 0:男性　1:女性 2:不明
	char	c_ijkbn[3+1];
	int		i;

	strcpy( c_ijkbn,	"555" );

	for( i = 0; i < 3 ; i++ ){
		if( i == 1 ){
			memcpy( &hsstkjmst.hkjm, &hsstkjmst.hkjf, sizeof( struct _KJM ));
		} else if( i == 2 ){
			memcpy( &hsstkjmst.hkjm, &hsstkjmst.hkje, sizeof( struct _KJM ));
		}

		// 判定は値が空白以外の場合のみ行う
		if( ( strspn( hsstkjmst.hkjm.lw1_m, " " ) < 8 )
		  &&( k_knskka1 < atof( hsstkjmst.hkjm.lw1_m ))) {
			c_ijkbn[i] = '1';
		} else
		if( ( strspn( hsstkjmst.hkjm.lw2_m, " " ) < 8 )
		  &&( k_knskka1 < atof( hsstkjmst.hkjm.lw2_m ))) {
			c_ijkbn[i] = '2';
		} else
		if( ( strspn( hsstkjmst.hkjm.kjnlw_m, " " ) < 8 )
		  &&( k_knskka1 < atof( hsstkjmst.hkjm.kjnlw_m ))) {
			c_ijkbn[i] = '3';
		} else
		if( ( strspn( hsstkjmst.hkjm.kj1_m, " " ) < 8 )
		  &&( k_knskka1 < atof( hsstkjmst.hkjm.kj1_m ))) {
			c_ijkbn[i] = '4';
		} else
		if( ( strspn( hsstkjmst.hkjm.hi2_m, " " ) < 8 )
		  &&( k_knskka1 > atof( hsstkjmst.hkjm.hi2_m ))) {
			c_ijkbn[i] = '9';
		} else 
		if( ( strspn( hsstkjmst.hkjm.hi1_m, " " ) < 8 )
		  &&( k_knskka1 > atof( hsstkjmst.hkjm.hi1_m ))) {
			c_ijkbn[i] = '8';
		} else
		if( ( strspn( hsstkjmst.hkjm.kjnhi_m, " " ) < 8 )
		  &&( k_knskka1 > atof( hsstkjmst.hkjm.kjnhi_m ))) {
			c_ijkbn[i] = '7';
		} else
		if( ( strspn( hsstkjmst.hkjm.kj2_m, " " ) < 8 )
		  &&( k_knskka1 > atof( hsstkjmst.hkjm.kj2_m ))) {
			c_ijkbn[i] = '6';
		}
	}

	// 結果情報構造体へのセット

	strcpy( kek->knskka1,	c_knskka1 );
	kek->kkaksflg = '1';
	kek->ijkbnm = c_ijkbn[0];
	kek->ijkbnf = c_ijkbn[1];
	kek->ijkbnn = c_ijkbn[2];

	return( RTN_OK );
}

/** End of File ***************************************************************/
