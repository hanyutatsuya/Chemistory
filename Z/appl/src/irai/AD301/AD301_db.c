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
/*   �a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/*   �V�X�e�����F������V�X�e��                                               */
/*   �t�@�C�����FAD301_db.sqc                                                 */
/*   �T      �v�F�c�a�A�N�Z�X                                                 */
/*   OS        �FSUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   ����      �FDB2/C                                                        */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/04/03     INTEC.INC      CREATE                             */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
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
/*   �a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/*   �V�X�e�����F������V�X�e��                                               */
/*   �t�@�C�����FtagAD301.h                                                   */
/*   �T      �v�F���ҏ��e�[�u���\���̒�`                                   */
/*   ���L����  �FDB2�̃z�X�g�ϐ��ɂ��g�p���邽��typedef�g�p�s��               */
/*               �܂�struct�̍Ō�ŕϐ�����錾���邱��                       */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/08     INTEC.INC      CREATE                             */
/******************************************************************************/
#ifndef _TAGAD301_H
#define _TAGAD301_H

/******************************************************************************/
/* �f�[�^�\���̒�`                                                           */
/******************************************************************************/
/******************************************************************************/
/* �}�X�^�\���̒�`                                                           */
/******************************************************************************/
// <<   �V�X�e���Ǘ��}�X�^     >>
struct  _SYSKNRMST {
	char	sateid[3];			// �T�e���C�g�h�c
	char	kjnsriymd[11];		// ������N����
	char	iriendflg[2];		// �˗�END�t���O
	char	bchendflg[2];		// ����END�t���O
	sqlint32	ssntubn;		// ���M�ʔ�
	char	ksndh[26];			// �X�V�N����
} hsysknrmst;

#endif

#line 26 "AD301_db.sqc"

	char		hst_ymd[11];
	sqlint32	hst_cnt;					// �}�X�^����
	short		ind_cnt;					// �W���ϐ�

/*
EXEC SQL END DECLARE SECTION;
*/

#line 30 "AD301_db.sqc"


/******************************************************************************/
/*  �� �� ��  �FSelSysknrmst                                                  */
/*  �@�\�T�v  �F�V�X�e���Ǘ��}�X�^ SELECT                                     */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _SYSKNRMST *knr;   : �V�X�e���Ǘ��}�X�^               *
/*   ��P���� �Fchar	ymd[];	: 	�������                                */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		SelSysknrmst( knr )
struct      _SYSKNRMST  *knr;
{
	int		ret;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* �֐�����	*/
	struct	sqlca	sqlca;

	/* ��������	*/
	strcpy( func_nm, "SelSysknrmst" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
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
		sprintf( G_msg, "�V�X�e���Ǘ��}�X�^(kjnsriymd)�����݂��܂���B" );
		LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			
		ret=RTN_ZERO;
	} else {
		if( sqlca.sqlcode == -911 ){		// LOCK
			switch( sqlca.sqlerrd[2] ){
			case	 2 :
				strcpy( G_msg, "�V�X�e���Ǘ��}�X�^(kjnsriymd) SELECT ��"
					"DEAD LOCK ���������܂����B" );
				break;
			case	68 :
				strcpy( G_msg, "�V�X�e���Ǘ��}�X�^(kjnsriymd) SELECT ��"
					"TIMETOUT ���������܂����B" );
				break;
			default	:
				sprintf( G_msg, "�V�X�e���Ǘ��}�X�^(kjnsriymd) SELECT ��"
					"�s����������܂����B" );
				break;
			}
		} else {
			/* SQLCODE > 0 -> WARNING */
			/* SQLCODE < 0 -> ERROR */
			sprintf( G_msg, "�V�X�e���Ǘ��}�X�^(kjnsriymd) SELECT ��"
				"�s����������܂����B" );
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
/*  �� �� ��  �FUpdSysknrmstSsntubn                                           */
/*  �@�\�T�v  �F�V�X�e���Ǘ�.���M�ʔ� UPDATE                                  */
/*  ��    ��  �F                                                              */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/*  ���L����  �F                                                              */
/******************************************************************************/
//int		UpdSysknrmstSsntubn( tuban )
//int		tuban;					// 	���M�ʔ�
int		UpdSysknrmstSsntubn( )
{
	struct	sqlca	sqlca;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* �֐�����	*/
	int		ret;

	/* ��������	*/
	strcpy( func_nm, "UpdSysknrmstSsntubn" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̍��ڃZ�b�g	*/

	// �Ώۃf�[�^��SELECT

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
					strcpy( G_msg, "�V�X�e���Ǘ��}�X�^(kjnsriymd) SELECT ��"
						"DEAD LOCK ���������܂����B" );
					break;
				case	68 :
					strcpy( G_msg, "�V�X�e���Ǘ��}�X�^(kjnsriymd) SELECT ��"
						"TIMETOUT ���������܂����B" );
					break;
				default :
					sprintf( G_msg, "�V�X�e���Ǘ��}�X�^(kjnsriymd) SELECT ��"
						"�s����������܂����B" );
					break;
				}
			} else {
				/* SQLCODE > 0 -> WARNING */
				/* SQLCODE < 0 -> ERROR */
				sprintf( G_msg,
					"�V�X�e���Ǘ��}�X�^(sysknrmst)�˗�END���� UPDATE ��"
					"���s���܂����B������N����[%s]"
					,stcPRM.myp_kjnymd );
			}
			LogOut( LT_ERR, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			ret=RTN_DBERR;
		}
		// 1��Ŕ�����
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

	/* �{����"00000"��cmpare������	*/
	if( memcmp( sqlca.sqlstate, "00000", 5 ) != 0 ){
		/* ERROR  */
		sprintf( G_msg, "�c�a�Q�ւ̐ڑ��Ɏ��s���܂����B" );
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
