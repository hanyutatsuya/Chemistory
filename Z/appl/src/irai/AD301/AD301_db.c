static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,73,65,118,106,84,71,77,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,65,68,51,48,49,95,68,66,0,0,0,0,0,0,0,0,
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


#line 1 "AD301_db.sqc"
/******************************************************************************/
/*   ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/*   システム名：次世代システム                                               */
/*   ファイル名：AD301_db.sqc                                                 */
/*   概      要：ＤＢアクセス                                                 */
/*   OS        ：SUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   言語      ：DB2/C                                                        */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/04/03     INTEC.INC      CREATE                             */
/******************************************************************************/

/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include	<stdio.h>
#include 	<stdlib.h>
#include 	<string.h>
#include	<sqlca.h>
#include	"AD301.h"


/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 25 "AD301_db.sqc"


/*
EXEC SQL INCLUDE 'tagAD301.h';
*/

#line 1 "/home/kea00sys/appl/src/irai/AD301/tagAD301.h"
/******************************************************************************/
/*   ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/*   システム名：次世代システム                                               */
/*   ファイル名：tagAD301.h                                                   */
/*   概      要：患者情報テーブル構造体定義                                   */
/*   特記事項  ：DB2のホスト変数にも使用するためtypedef使用不可               */
/*               またstructの最後で変数名を宣言すること                       */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/08     INTEC.INC      CREATE                             */
/******************************************************************************/
#ifndef _TAGAD301_H
#define _TAGAD301_H

/******************************************************************************/
/* データ構造体定義                                                           */
/******************************************************************************/
/******************************************************************************/
/* マスタ構造体定義                                                           */
/******************************************************************************/
// <<   システム管理マスタ     >>
struct  _SYSKNRMST {
	char	sateid[3];			// サテライトＩＤ
	char	kjnsriymd[11];		// 基準処理年月日
	char	iriendflg[2];		// 依頼ENDフラグ
	char	bchendflg[2];		// 分注ENDフラグ
	sqlint32	ssntubn;		// 送信通番
	char	ksndh[26];			// 更新年月日
} hsysknrmst;

#endif

#line 26 "AD301_db.sqc"

	char		hst_ymd[11];
	sqlint32	hst_cnt;					// マスタ件数
	short		ind_cnt;					// 標識変数

/*
EXEC SQL END DECLARE SECTION;
*/

#line 30 "AD301_db.sqc"


/******************************************************************************/
/*  関 数 名  ：SelSysknrmst                                                  */
/*  機能概要  ：システム管理マスタ SELECT                                     */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  _SYSKNRMST *knr;   : システム管理マスタ               *
/*   第１引数 ：char	ymd[];	: 	基準処理日                                */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		SelSysknrmst( knr )
struct      _SYSKNRMST  *knr;
{
	int		ret;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* 関数名称	*/
	struct	sqlca	sqlca;

	/* 初期処理	*/
	strcpy( func_nm, "SelSysknrmst" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ホスト変数へのキー項目セット	*/
	memset( &hsysknrmst,    '\0',   sizeof( struct _SYSKNRMST ));


/*
EXEC SQL SELECT	
			sateid
		 	, kjnsriymd
			, iriendflg
			, bchendflg
			, ssntubn
			, ksndh
	INTO	:hsysknrmst.sateid
			, :hsysknrmst.kjnsriymd
			, :hsysknrmst.iriendflg
			, :hsysknrmst.bchendflg
			, :hsysknrmst.ssntubn
			, :hsysknrmst.ksndh
	FROM	sysknrmst
	;
*/

{
#line 70 "AD301_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 70 "AD301_db.sqc"
  sqlaaloc(3,6,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 70 "AD301_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 70 "AD301_db.sqc"
      sql_setdlist[0].sqldata = (void*)hsysknrmst.sateid;
#line 70 "AD301_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 70 "AD301_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 70 "AD301_db.sqc"
      sql_setdlist[1].sqldata = (void*)hsysknrmst.kjnsriymd;
#line 70 "AD301_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 70 "AD301_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 70 "AD301_db.sqc"
      sql_setdlist[2].sqldata = (void*)hsysknrmst.iriendflg;
#line 70 "AD301_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 70 "AD301_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 2;
#line 70 "AD301_db.sqc"
      sql_setdlist[3].sqldata = (void*)hsysknrmst.bchendflg;
#line 70 "AD301_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 70 "AD301_db.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 70 "AD301_db.sqc"
      sql_setdlist[4].sqldata = (void*)&hsysknrmst.ssntubn;
#line 70 "AD301_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 70 "AD301_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 26;
#line 70 "AD301_db.sqc"
      sql_setdlist[5].sqldata = (void*)hsysknrmst.ksndh;
#line 70 "AD301_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 70 "AD301_db.sqc"
      sqlasetdata(3,0,6,sql_setdlist,0L,0L);
    }
#line 70 "AD301_db.sqc"
  sqlacall((unsigned short)24,1,0,3,0L);
#line 70 "AD301_db.sqc"
  sqlastop(0L);
}

#line 70 "AD301_db.sqc"


    /* not found --> SQLCODE = +100, SQLSTATE == '02000' */
	/* many rows --> ERROR!!         SQLSTATE == '21000' */
    /* duplicate --> SQLCODE = -803                      */
    /* dead lock --> SQLCODE = -911, SQLERRD[2]== 2      */
    /* time out  --> SQLCODE = -911, SQLERRD[2]== 68     */

	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "SELECT kjnsriymd FROM sysknrmst" );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if ( sqlca.sqlcode == 0 ) {		/* OK */
		memcpy( knr, &hsysknrmst, sizeof( struct _SYSKNRMST ));
		ret = RTN_OK;
	} else  if ( sqlca.sqlcode == 100 ){	/* NOT FOUND */
		/* SQLCODE +100, SQLSTATE '02000' */
		sprintf( G_msg, "システム管理マスタ(kjnsriymd)が存在しません。" );
		LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			
		ret=RTN_ZERO;
	} else {
		if( sqlca.sqlcode == -911 ){		// LOCK
			switch( sqlca.sqlerrd[2] ){
			case	 2 :
				strcpy( G_msg, "システム管理マスタ(kjnsriymd) SELECT で"
					"DEAD LOCK が発生しました。" );
				break;
			case	68 :
				strcpy( G_msg, "システム管理マスタ(kjnsriymd) SELECT で"
					"TIMETOUT が発生しました。" );
				break;
			default	:
				sprintf( G_msg, "システム管理マスタ(kjnsriymd) SELECT で"
					"不具合が発生しました。" );
				break;
			}
		} else {
			/* SQLCODE > 0 -> WARNING */
			/* SQLCODE < 0 -> ERROR */
			sprintf( G_msg, "システム管理マスタ(kjnsriymd) SELECT で"
				"不具合が発生しました。" );
		}
		ret=RTN_DBERR;
		LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
	}


/*
EXEC SQL COMMIT;
*/

{
#line 122 "AD301_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 122 "AD301_db.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 122 "AD301_db.sqc"
  sqlastop(0L);
}

#line 122 "AD301_db.sqc"


	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  関 数 名  ：UpdSysknrmstSsntubn                                           */
/*  機能概要  ：システム管理.送信通番 UPDATE                                  */
/*  入    力  ：                                                              */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/*  特記事項  ：                                                              */
/******************************************************************************/
//int		UpdSysknrmstSsntubn( tuban )
//int		tuban;					// 	送信通番
int		UpdSysknrmstSsntubn( )
{
	struct	sqlca	sqlca;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* 関数名称	*/
	int		ret;

	/* 初期処理	*/
	strcpy( func_nm, "UpdSysknrmstSsntubn" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ホスト変数への項目セット	*/

	// 対象データのSELECT

/*
EXEC SQL DECLARE	tuban_cur CURSOR  FOR
	SELECT	ssntubn
			, ksndh
	FROM	sysknrmst
	FOR		UPDATE
	;
*/

#line 157 "AD301_db.sqc"


/*
EXEC SQL OPEN tuban_cur;
*/

{
#line 158 "AD301_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 158 "AD301_db.sqc"
  sqlacall((unsigned short)26,2,0,0,0L);
#line 158 "AD301_db.sqc"
  sqlastop(0L);
}

#line 158 "AD301_db.sqc"


	while( sqlca.sqlcode == 0 ) {
		
/*
EXEC SQL    FETCH   tuban_cur
					INTO    :hsysknrmst.ssntubn
							, :hsysknrmst.ksndh
					;
*/

{
#line 164 "AD301_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 164 "AD301_db.sqc"
  sqlaaloc(3,2,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 164 "AD301_db.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 164 "AD301_db.sqc"
      sql_setdlist[0].sqldata = (void*)&hsysknrmst.ssntubn;
#line 164 "AD301_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 164 "AD301_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 26;
#line 164 "AD301_db.sqc"
      sql_setdlist[1].sqldata = (void*)hsysknrmst.ksndh;
#line 164 "AD301_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 164 "AD301_db.sqc"
      sqlasetdata(3,0,2,sql_setdlist,0L,0L);
    }
#line 164 "AD301_db.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 164 "AD301_db.sqc"
  sqlastop(0L);
}

#line 164 "AD301_db.sqc"

		// edit sqlcacode for LogOut errcode
		sprintf( G_err, "%d", sqlca.sqlcode );
		// DEBUG
		sprintf(G_msg,"FETCH sysknrmst : ssntubn[%d]",hsysknrmst.ssntubn);
		LogOut( LT_DBG, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		if ( sqlca.sqlcode != 0 ) {		/* OK */
			ret = RTN_NG;
			break;
		}

		
/*
EXEC SQL	UPDATE	sysknrmst	
					SET		ssntubn		=  :hsysknrmst.ssntubn + 1
							,ksndh		=	CURRENT TIMESTAMP
					WHERE   CURRENT OF tuban_cur
					;
*/

{
#line 180 "AD301_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 180 "AD301_db.sqc"
  sqlaaloc(2,1,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 180 "AD301_db.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 180 "AD301_db.sqc"
      sql_setdlist[0].sqldata = (void*)&hsysknrmst.ssntubn;
#line 180 "AD301_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 180 "AD301_db.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 180 "AD301_db.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 180 "AD301_db.sqc"
  sqlastop(0L);
}

#line 180 "AD301_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
		sprintf( G_err, "%d", sqlca.sqlcode );

		// DEBUG
		sprintf(G_msg,"UPDATE sysknrmst : ssntubn[%d]",hsysknrmst.ssntubn);
		LogOut( LT_DBG, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		if (sqlca.sqlcode == 0) {		/* OK */
			ret = hsysknrmst.ssntubn + 1;
		} else {
			if( sqlca.sqlcode == -911 ){		// LOCK
				switch( sqlca.sqlerrd[2] ){
				case	 2 :
					strcpy( G_msg, "システム管理マスタ(kjnsriymd) SELECT で"
						"DEAD LOCK が発生しました。" );
					break;
				case	68 :
					strcpy( G_msg, "システム管理マスタ(kjnsriymd) SELECT で"
						"TIMETOUT が発生しました。" );
					break;
				default :
					sprintf( G_msg, "システム管理マスタ(kjnsriymd) SELECT で"
						"不具合が発生しました。" );
					break;
				}
			} else {
				/* SQLCODE > 0 -> WARNING */
				/* SQLCODE < 0 -> ERROR */
				sprintf( G_msg,
					"システム管理マスタ(sysknrmst)依頼END情報の UPDATE に"
					"失敗しました。基準処理年月日[%s]"
					,stcPRM.myp_kjnymd );
			}
			LogOut( LT_ERR, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			ret=RTN_DBERR;
		}
		// 1回で抜ける
		break;
	}

/*
EXEC SQL    CLOSE   tuban_cur;
*/

{
#line 223 "AD301_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 223 "AD301_db.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 223 "AD301_db.sqc"
  sqlastop(0L);
}

#line 223 "AD301_db.sqc"


/*
EXEC SQL	COMMIT;
*/

{
#line 224 "AD301_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 224 "AD301_db.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 224 "AD301_db.sqc"
  sqlastop(0L);
}

#line 224 "AD301_db.sqc"


	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/****************************************************************************
****************************************************************************/
//-----<Ydbcommit>----------------------------------------------------------
int Ydbcommit()
{
	char	func_nm[MYAPP_LEN_FNCNM+1];
	int		ret=RTN_OK;
	struct	sqlca sqlca;

	strcpy( func_nm, "Ydbcommit" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	
/*
EXEC SQL COMMIT;
*/

{
#line 242 "AD301_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 242 "AD301_db.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 242 "AD301_db.sqc"
  sqlastop(0L);
}

#line 242 "AD301_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	LogOut( LT_DBG, LX_NON, G_err, "COMMIT", func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
  	return( RTN_OK );

} /* DbDisconn */

//-----<Ydbrollback>----------------------------------------------------------
int Ydbrollback()
{
	char	func_nm[MYAPP_LEN_FNCNM+1];
	int		ret=RTN_OK;
	struct	sqlca sqlca;

	strcpy( func_nm, "Ydbrollback" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* rollback the transaction */
	
/*
EXEC SQL ROLLBACK;
*/

{
#line 268 "AD301_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 268 "AD301_db.sqc"
  sqlacall((unsigned short)28,0,0,0,0L);
#line 268 "AD301_db.sqc"
  sqlastop(0L);
}

#line 268 "AD301_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//		sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[2] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	LogOut( LT_DBG, LX_NON, G_err, "ROLLBACK", func_nm, __FILE__, __LINE__ );
/*  SqlInfoPrint("ROLLBACK", &sqlca, __LINE__, __FILE__);*/

	if (sqlca.sqlcode == 0) {
		sprintf( G_msg, "The transaction was rolled back." );
		LogOut( LT_TRC, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
	}

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
  	return( RTN_OK );
} /* TransRollback */

//-----<Ydbconn>----------------------------------------------------------
int Ydbconn()
{
	char	func_nm[MYAPP_LEN_FNCNM+1];
	int		ret=RTN_OK;
	struct	sqlca sqlca;


/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 295 "AD301_db.sqc"

	char	dbAlias[15];
	char	user[129];
	char	pswd[15];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 299 "AD301_db.sqc"


	strcpy( func_nm, "Ydbconn" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	strcpy( dbAlias,	stcPRM.dbp_dbAlias );
	strcpy( user,		stcPRM.dbp_user );
	strcpy( pswd,		stcPRM.dbp_pswd );

	
/*
EXEC SQL CONNECT TO :dbAlias USER :user USING :pswd;
*/

{
#line 308 "AD301_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 308 "AD301_db.sqc"
  sqlaaloc(2,3,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 308 "AD301_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 15;
#line 308 "AD301_db.sqc"
      sql_setdlist[0].sqldata = (void*)dbAlias;
#line 308 "AD301_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 308 "AD301_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 129;
#line 308 "AD301_db.sqc"
      sql_setdlist[1].sqldata = (void*)user;
#line 308 "AD301_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 308 "AD301_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 15;
#line 308 "AD301_db.sqc"
      sql_setdlist[2].sqldata = (void*)pswd;
#line 308 "AD301_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 308 "AD301_db.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 308 "AD301_db.sqc"
  sqlacall((unsigned short)29,5,2,0,0L);
#line 308 "AD301_db.sqc"
  sqlastop(0L);
}

#line 308 "AD301_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	LogOut( LT_DBG, LX_NON, G_err, "CONNECT", func_nm, __FILE__, __LINE__ );

	/* 本当は"00000"でcmpareしたい	*/
	if( memcmp( sqlca.sqlstate, "00000", 5 ) != 0 ){
		/* ERROR  */
		sprintf( G_msg, "ＤＢ２への接続に失敗しました。" );
		LogOut( LT_TRC, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		ret = RTN_NG;
	}

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
  	return( ret );
} /* DbConn */

//-----<Ydbdisconn>----------------------------------------------------------
int Ydbdisconn()
{
	struct sqlca sqlca;
	char	func_nm[MYAPP_LEN_FNCNM+1];
	int	ret=RTN_OK;

	strcpy( func_nm, "Ydbdisconn" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

  	/* Commit all non-committed transactions to release database locks */
	
/*
EXEC SQL COMMIT;
*/

{
#line 341 "AD301_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 341 "AD301_db.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 341 "AD301_db.sqc"
  sqlastop(0L);
}

#line 341 "AD301_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	LogOut( LT_DBG, LX_NON, G_err, "COMMIT BEFORE CONNECT RESET"
			, func_nm, __FILE__, __LINE__ );

	
/*
EXEC SQL CONNECT RESET;
*/

{
#line 352 "AD301_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 352 "AD301_db.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 352 "AD301_db.sqc"
  sqlastop(0L);
}

#line 352 "AD301_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	LogOut( LT_DBG, LX_NON, G_err, "CONNECT RESET",func_nm, __FILE__, __LINE__);

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
  	return( RTN_OK );
} /* DbDisconn */
/** End of File ***************************************************************/
