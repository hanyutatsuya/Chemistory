static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,71,66,77,53,85,71,67,108,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,65,68,49,48,50,95,68,66,0,0,0,0,0,0,0,0,
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


#line 1 "AD102_db.sqc"
/******************************************************************************/
/*   �a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/*   �V�X�e�����F������V�X�e��                                               */
/*   �t�@�C�����FAD102_db.sqc                                                 */
/*   �T      �v�F�c�a�A�N�Z�X                                                 */
/*   OS        �FSUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   ����      �FDB2/C                                                        */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/23     INTEC.INC      CREATE                             */
/*  1.01     2006/05/01     INTEC.INC      SJIS,���ڒǉ�(�e�{��,�o�^����)�Ή� */
/*  1.03     2006/06/10     INTEC.INC      ���ґ����C�����˗���񐢑�No�X�V   */
/*  1.04     2006/06/26     INTEC.INC      �����������ړo�^�{����G�ҏW�ǉ�    */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include	<stdio.h>
#include 	<stdlib.h>
#include 	<string.h>
#include	<sqlca.h>
#include	"AD102.h"


/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 28 "AD102_db.sqc"


/*
EXEC SQL INCLUDE 'tagAD102.h';
*/

#line 1 "/home/kea00sys/appl/src/irai/AD102/tagAD102.h"
/******************************************************************************/
/*   �a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/*   �V�X�e�����F������V�X�e��                                               */
/*   �t�@�C�����FtagAD102.h                                                   */
/*   �T      �v�F���ҏ��e�[�u���\���̒�`                                   */
/*   ���L����  �FDB2�̃z�X�g�ϐ��ɂ��g�p���邽��typedef�g�p�s��               */
/*               �܂�struct�̍Ō�ŕϐ�����錾���邱��                       */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/08     INTEC.INC      CREATE                             */
/*  1.01     2006/05/01     INTEC.INC      SJIS,���ڒǉ�(�e�{��,�o�^����)�Ή� */
/******************************************************************************/
#ifndef _TAGAD102_H
#define _TAGAD102_H

/******************************************************************************/
/* �f�[�^�\���̒�`                                                           */
/******************************************************************************/
// <<   �˗����e�[�u��      >>
struct	_IRAI {
	char	utkymd[10+1];		// 1 �a�l�k��t�N����
	char	irino[11+1];		// 2 �˗����m��
	char	iriketflg[1+1];		// 3 �˗����m�������t���O
	short	zssdino;			// 4 ��������m��
	char	knsgrp[16+1];		// 5 �����O���[�v
	char	kmkcd[7+1];			// 6 ���ڃR�[�h
	char	irihsmkbn[1+1];		// 7 �˗��������敪
	char	irikbn[1+1];		// 8 �˗��敪
	char	ksktkbn[1+1];		// 9 �����H���敪
	char	sriymd[10+1];		// 10 ������
	char	kntno[13+1];		// 11 ���̂m���i����ς�K�v�j
	char	kntketflg[1+1];		// 12 ���̂m�������t���O
	char	chkmj[4+1];			// 13 �`�F�b�N�����i����ς�K�v�j
	char	stsrcd[4+1];		// 14 ����ޗ��R�[�h
	char	kmkrs[16+1];		// 15 ���ڗ���
	char	oyakmkcd[7+1];		// 16 �e���ڃR�[�h
	char	smpcd[7+1];			// 17 �T���v�����O�R�[�h
	char	setkmkcd[7+1];		// 18 �Z�b�g���ڃR�[�h
	char	srinycd[1+1];		// 19 �������e�R�[�h
	char	seccd[2+1];			// 20 �Z�N�V�����R�[�h
	char	skchkflg[1+1];		// 21 �o�׃`�F�b�N�t���O
	char	bkfkkbn[1+1];		// 22 ���敉�׋敪
	char	ysnlbl[2+1];		// 23 �D�惌�x��
	char	skflg[1+1];			// 24 �W���t���O
	char	tkflg[1+1];			// 25 �ǉ��t���O
	char	sjflg[1+1];			// 26 �폜�t���O
	char	jktkflg[1+1];		// 27 �����ǉ��t���O
	char	kjno[3+1];			// 28 ��l�m�n
	char	fkhkknohjkbn[1+1];	// 29 ���ו񍐂m�n�\���敪
	char	tbkjno[3+1];		// 30 ���ʊ�l�m�n
	char	tbkjflg[1+1];		// 31 ���ʊ�l�t���O
	char	htkfkhms[24+1];		// 32 ���^���׎���
	char	tskflg[2+1];		// 33 ���̓t���O
	char	tktflg[2+1];		// 34 �����t���O
	char	bnckbn[1+1];		// 35 �����敪
	char	nbnckbn[1+1];		// 36 �A�����敪
	char	knskisyymd[10+1];	// 37 �����J�n�\���
	char	knskryymd[10+1];	// 38 ���������\���
	char	knskrytme[8+1];		// 39 ���������\�莞��
	char	kkhkkflg[1+1];		// 40 �ً}�񍐃t���O
	char	kkiriflg[1+1];		// 41 �ً}�˗��t���O
	short	kkirilotno;			// 42 �ً}�˗����b�g�m��
	char	kktoutkid[4+1];		// 43 �ً}�Ή���t�h�c
	short	knssu;				// 44 ������
	char	odrssflg[1+1];		// 45 �I�[�_�쐬�t���O
	char	ytiksbr[15+1];		// 46 �\���ߔ{��
	char	hhkjkflg[1+1];		// 47 �񍐏󋵃t���O
	char	ksndh[26+1];		// 48 ���X�V����
	char	trkdh[26+1];		// 1.01 ADD 49 �o�^����
} hirai;	

/******************************************************************************/
/* �}�X�^�\���̒�`                                                           */
/******************************************************************************/
// <<   �V�X�e���Ǘ��}�X�^     >>
struct  _SYSKNRMST {
	char	kjnsriymd[11];		// ������N����
	char	nxirisriymd[11];	// ���˗������N����
	char	iriendflg[2];		// �˗�END�t���O
} hsysknrmst;

// <<   ��l�}�X�^     >>
struct	_KJNMST {
	char	kmkcd[7+1];			// 1 ���ڃR�[�h
	char	kjno[3+1];			// 2 ��lNO
	char	zrcd[4+1];			// 4 �ޗ��R�[�h      
	char	etckbn[3+1];		// 6 ���̑��敪      
	char	nichilw[5+1];		// 7 ����i���j      
	char	nichihi[5+1];		// 8 ����i��j      
	char    kkey[14+1];			// 0 �����L�[(MYAPP)
	sqlint32	knlow;			// 0 �����L�[(���)
	sqlint32	knhigh;			// 0 �����L�[(�����)
} hkjnmst;	

// 1.04 ADD
// <<   ���ڃ}�X�^ >>
struct	_KMKMST {
	char	knsgrp[16+1];		// 1  �����O���[�v�R�[�h
	char	kmkcd[7+1];			// 2  ���ڃR�[�h
	char	kmkrs[16+1];		// 5  ���ڗ���
	char	smpcd[7+1];			// 11 �T���v�����O�R�[�h
	char	oyakmkcd[7+1];		// 12 �e���ڃR�[�h
	char	fkbnkkb[1+1];		// 19 ���ו���敪
	char	skflg[1+1];			// 0  �W���t���O
} hkmkmst;	

// <<   �����������ڃ}�X�^ >>
struct	_JDKMKMST {
	char	knsgrp[16+1];		// 1  �����O���[�v�R�[�h
	char	kmkcd[7+1];			// 2  ���ڃR�[�h
	char	jknsgrp[16+1];		// 3  �������������O���[�v�R�[�h
	char	jkmkcd[7+1];		// 4  �����������ڃR�[�h
	char	hhkumflg[1+1];		// 5  �񍐗L���t���O
} hjdkmkmst;	

#endif

#line 29 "AD102_db.sqc"

	char        hst_utkymd[10+1];
    char        hst_irino[11+1];
	char        hst_knsgrp[16+1];
    char        hst_kmkcd[7+1];
	char		hst_ymd[11];
	sqlint32	hst_cnt;					// �}�X�^����
	short		ind_cnt;					// �W���ϐ�
	sqlint32	hst_zssdino;
	short		ind_zssdino;

/*
EXEC SQL END DECLARE SECTION;
*/

#line 39 "AD102_db.sqc"


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
		 	kjnsriymd
			, nxirisriymd
			, iriendflg
	INTO	:hsysknrmst.kjnsriymd
			, :hsysknrmst.nxirisriymd
			, :hsysknrmst.iriendflg
	FROM	sysknrmst
	;
*/

{
#line 73 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 73 "AD102_db.sqc"
  sqlaaloc(3,3,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 73 "AD102_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 73 "AD102_db.sqc"
      sql_setdlist[0].sqldata = (void*)hsysknrmst.kjnsriymd;
#line 73 "AD102_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 73 "AD102_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 73 "AD102_db.sqc"
      sql_setdlist[1].sqldata = (void*)hsysknrmst.nxirisriymd;
#line 73 "AD102_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 73 "AD102_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 73 "AD102_db.sqc"
      sql_setdlist[2].sqldata = (void*)hsysknrmst.iriendflg;
#line 73 "AD102_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 73 "AD102_db.sqc"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 73 "AD102_db.sqc"
  sqlacall((unsigned short)24,1,0,3,0L);
#line 73 "AD102_db.sqc"
  sqlastop(0L);
}

#line 73 "AD102_db.sqc"


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
		EditCsvMsg( G_msg );
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
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
	}


/*
EXEC SQL COMMIT;
*/

{
#line 127 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 127 "AD102_db.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 127 "AD102_db.sqc"
  sqlastop(0L);
}

#line 127 "AD102_db.sqc"


	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FUpdSysknrmstIriend                                            */
/*  �@�\�T�v  �F�V�X�e���Ǘ�.�˗�END��� UPDATE                               */
/*  ��    ��  �F                                                              */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/*  ���L����  �F                                                              */
/******************************************************************************/
int		UpdSysknrmstIriend( nxtymd )
char		nxtymd[];					// 	���˗������N���� �ݒ��
{
	struct	sqlca	sqlca;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* �֐�����	*/
	int		ret;

	/* ��������	*/
	strcpy( func_nm, "UpdSysknrmstIriend" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̍��ڃZ�b�g	*/
	strcpy( hsysknrmst.nxirisriymd, nxtymd );


/*
EXEC SQL UPDATE	sysknrmst	
	SET		iriendflg		=  '1'
			,irienddh		= CURRENT TIMESTAMP
			,nxirisriymd	= :hsysknrmst.nxirisriymd
	;
*/

/*
SQL0513W  ���� SQL
�X�e�[�g�����g�́A�\�S�̂܂��̓r���[�S�̂�ύX���܂��B 
SQLSTATE=01504

*/

{
#line 160 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 160 "AD102_db.sqc"
  sqlaaloc(2,1,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 160 "AD102_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 160 "AD102_db.sqc"
      sql_setdlist[0].sqldata = (void*)hsysknrmst.nxirisriymd;
#line 160 "AD102_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 160 "AD102_db.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 160 "AD102_db.sqc"
  sqlacall((unsigned short)24,2,2,0,0L);
#line 160 "AD102_db.sqc"
  sqlastop(0L);
}

#line 160 "AD102_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf(G_msg,"UPDATE sysknrmst : nxirisriymd[%s]",hsysknrmst.nxirisriymd);
	LogOut( LT_DBG, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if (sqlca.sqlcode == 0) {		/* OK */
		ret = RTN_OK;
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
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		ret=RTN_DBERR;
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FSelCountKjnmst                                                */
/*  �@�\�T�v  �F��l�}�X�^�i���ڃ}�X�^�����j�����擾                        */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fchar	ymd[];	: 	�������                                */
/*  �o    ��  �F                                                              */
/*  ���A���  �FCOUNT����    ����I��                                         */
/*            �F0 ����       �ُ�I��                                         */
/******************************************************************************/
int		SelCountKjnmst( ymd )
char		ymd[];	
{
	int		ret;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	struct	sqlca	sqlca;

	/* ��������	*/
	strcpy( func_nm, "SelCountKjnmst" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	strcpy( hst_ymd,	ymd );
	hst_cnt=0;
	ind_cnt=0;


/*
EXEC SQL SELECT	COUNT( kj.kmkcd )
	INTO	:hst_cnt	INDICATOR :ind_cnt
	FROM	kjnmst kj
			,(	SELECT	DISTINCT kmkcd
				FROM	kmkmst
				WHERE	kaiymd <= :hst_ymd
				AND		haiymd >= :hst_ymd
				) km
	WHERE	kj.kmkcd	= km.kmkcd
	AND		kj.kaiymd	<= :hst_ymd
	AND		kj.haiymd	>= :hst_ymd
	;
*/

{
#line 241 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 241 "AD102_db.sqc"
  sqlaaloc(2,4,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 241 "AD102_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 241 "AD102_db.sqc"
      sql_setdlist[0].sqldata = (void*)hst_ymd;
#line 241 "AD102_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 241 "AD102_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 241 "AD102_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_ymd;
#line 241 "AD102_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 241 "AD102_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 241 "AD102_db.sqc"
      sql_setdlist[2].sqldata = (void*)hst_ymd;
#line 241 "AD102_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 241 "AD102_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 241 "AD102_db.sqc"
      sql_setdlist[3].sqldata = (void*)hst_ymd;
#line 241 "AD102_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 241 "AD102_db.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 241 "AD102_db.sqc"
  sqlaaloc(3,1,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 241 "AD102_db.sqc"
      sql_setdlist[0].sqltype = 497; sql_setdlist[0].sqllen = 4;
#line 241 "AD102_db.sqc"
      sql_setdlist[0].sqldata = (void*)&hst_cnt;
#line 241 "AD102_db.sqc"
      sql_setdlist[0].sqlind = &ind_cnt;
#line 241 "AD102_db.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 241 "AD102_db.sqc"
  sqlacall((unsigned short)24,3,2,3,0L);
#line 241 "AD102_db.sqc"
  sqlastop(0L);
}

#line 241 "AD102_db.sqc"


    /* not found --> SQLCODE = +100, SQLSTATE == '02000' */
	/* many rows --> ERROR!!         SQLSTATE == '21000' */

	/* SQLCODE */
	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "SELECT COUNT( kmkcd ) FROM kjnmst, kmkmst : "
		"ymd[%s] cnt[%d] indicator[%d]",
		ymd, hst_cnt, ind_cnt );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	// �W���ϐ��ɂ�锻�f
	if( ind_cnt == 0 ) {
		// COUNT���ʂ�Ԃ��i0������j
		ret = hst_cnt;
	} else {
		sprintf( G_msg,
			"��l�}�X�^(kjnmst)�̌����擾�Ɏ��s���܂����B"
			"������N����[%s] SELECT INDICATOR[%d]"
			,ymd, ind_cnt );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		ret=RTN_NG;
	}
	// DEBUG
	sprintf( G_msg, "KJNMST COUNT[%d]", ret );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FSelKjnmst                                                     */
/*  �@�\�T�v  �F��l�}�X�^ SELECT                                           */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fchar	ymd[];   : ���                                     */
/*   ��Q���� �Fint		kensu;   : malloc����                                 */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		SelKjnmst( ymd, kensu )
char		ymd[];	
int			kensu;
{
	int		ret;
	int		i;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* �֐�����	*/
	struct	sqlca	sqlca;

	/* ��������	*/
	strcpy( func_nm, "SelKjnmst" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	memset( &hkjnmst,	'\0', sizeof( struct _KJNMST ));
	strcpy( hst_ymd,	ymd );


/*
EXEC SQL DECLARE    kjn_cur CURSOR  FOR
	SELECT	kj.kmkcd
			, kjno
			, zrcd
			, etckbn
			, nichilw
			, nichihi
	FROM	kjnmst kj
			,(	SELECT DISTINCT kmkcd
				FROM	kmkmst
				WHERE	kaiymd	<= :hst_ymd
				AND		haiymd	>= :hst_ymd
			) km
	WHERE	kj.kmkcd	= km.kmkcd
	AND		kj.kaiymd	<= :hst_ymd
	AND		kj.haiymd	>= :hst_ymd
	ORDER BY kj.kmkcd, kj.zrcd, nichilw, nichihi
	FOR	READ ONLY
	;
*/

#line 325 "AD102_db.sqc"



/*
EXEC SQL OPEN kjn_cur;
*/

{
#line 327 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 327 "AD102_db.sqc"
  sqlaaloc(2,4,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 327 "AD102_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 327 "AD102_db.sqc"
      sql_setdlist[0].sqldata = (void*)hst_ymd;
#line 327 "AD102_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 327 "AD102_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 327 "AD102_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_ymd;
#line 327 "AD102_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 327 "AD102_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 327 "AD102_db.sqc"
      sql_setdlist[2].sqldata = (void*)hst_ymd;
#line 327 "AD102_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 327 "AD102_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 327 "AD102_db.sqc"
      sql_setdlist[3].sqldata = (void*)hst_ymd;
#line 327 "AD102_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 327 "AD102_db.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 327 "AD102_db.sqc"
  sqlacall((unsigned short)26,4,2,0,0L);
#line 327 "AD102_db.sqc"
  sqlastop(0L);
}

#line 327 "AD102_db.sqc"


	i=0;

	while( sqlca.sqlcode == 0 ){
		
/*
EXEC SQL    FETCH   kjn_cur
					INTO	  :hkjnmst.kmkcd
							, :hkjnmst.kjno
							, :hkjnmst.zrcd
							, :hkjnmst.etckbn
							, :hkjnmst.nichilw
							, :hkjnmst.nichihi
					;
*/

{
#line 339 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 339 "AD102_db.sqc"
  sqlaaloc(3,6,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 339 "AD102_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 339 "AD102_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkjnmst.kmkcd;
#line 339 "AD102_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 339 "AD102_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 4;
#line 339 "AD102_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkjnmst.kjno;
#line 339 "AD102_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 339 "AD102_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 339 "AD102_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkjnmst.zrcd;
#line 339 "AD102_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 339 "AD102_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 4;
#line 339 "AD102_db.sqc"
      sql_setdlist[3].sqldata = (void*)hkjnmst.etckbn;
#line 339 "AD102_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 339 "AD102_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 6;
#line 339 "AD102_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkjnmst.nichilw;
#line 339 "AD102_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 339 "AD102_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 6;
#line 339 "AD102_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkjnmst.nichihi;
#line 339 "AD102_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 339 "AD102_db.sqc"
      sqlasetdata(3,0,6,sql_setdlist,0L,0L);
    }
#line 339 "AD102_db.sqc"
  sqlacall((unsigned short)25,4,0,3,0L);
#line 339 "AD102_db.sqc"
  sqlastop(0L);
}

#line 339 "AD102_db.sqc"

		if( i >= kensu ){
			break;
		}
		memcpy( &( pKjn[i] ), &hkjnmst, sizeof( struct _KJNMST ));
		i++;
	}
	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "FETCH kjnmst : ymd[%s]", ymd );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if ( sqlca.sqlcode == 100 ) {	// NOT FOUND or END
		if( i > 0 ){
			ret = RTN_OK;
		} else {
			sprintf( G_msg,
				"��l�}�X�^���擾�ł��܂���B���[%s]", ymd );
			EditCsvMsg( G_msg );
			LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			ret = RTN_NG;
		}
	} else {
		/* SQLCODE > 0 -> WARNING */
		/* SQLCODE < 0 -> ERROR */
		sprintf( G_msg,
			"��l�}�X�^ FETCH �ŕs����������܂����B���[%s]", ymd );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			 
		ret=RTN_DBERR;
	}

/*
EXEC SQL    CLOSE   kjn_cur;
*/

{
#line 375 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 375 "AD102_db.sqc"
  sqlacall((unsigned short)20,4,0,0,0L);
#line 375 "AD102_db.sqc"
  sqlastop(0L);
}

#line 375 "AD102_db.sqc"


/*
EXEC SQL	COMMIT;
*/

{
#line 376 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 376 "AD102_db.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 376 "AD102_db.sqc"
  sqlastop(0L);
}

#line 376 "AD102_db.sqc"


	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}
// 1.04 ADD STA =============================================================
/******************************************************************************/
/*  �� �� ��  �FSelKnsgrp                                                     */
/*  �@�\�T�v  �F�����O���[�v�R�[�h SELECT                                     */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fchar	ymd[];   : ���                                     */
/*   ��Q���� �Fint		kensu;   : malloc����                                 */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		SelKnsgrp( km, ymd )
struct		_KMKMST		*km;
char		ymd[];	
{
	int		ret;
	int		i;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* �֐�����	*/
	struct	sqlca	sqlca;

	/* ��������	*/
	strcpy( func_nm, "SelKnsgrp" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	memset( &hkmkmst,	'\0', sizeof( struct _KMKMST ));
	strcpy( hkmkmst.kmkcd,	km->kmkcd );
	strcpy( hkmkmst.smpcd,	km->smpcd );
	strcpy( hst_ymd,		ymd );

	// �W���t���O�ɂ��Ώی����O���[�v��ʂ̔��f
	if( km->skflg[0] == '1' ){				// �W��

/*
EXEC SQL	SELECT	km.knsgrp
			INTO	:hkmkmst.knsgrp
			FROM	kmkmst km
					, knsgmst kg
			WHERE	km.kmkcd	=  :hkmkmst.kmkcd
			AND		km.smpcd	=  :hkmkmst.smpcd
			AND		km.kaiymd	<= :hst_ymd
			AND		km.haiymd	>= :hst_ymd
			AND		km.knsgrp	=  kg.knsgrp
			AND		kg.knssbt	=  'S'
			AND		kg.kaiymd	<= :hst_ymd
			AND		kg.haiymd	>= :hst_ymd
			ORDER BY km.knsgrp
			FETCH FIRST 1 ROWS ONLY
			;
*/

{
#line 427 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 427 "AD102_db.sqc"
  sqlaaloc(2,6,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 427 "AD102_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 427 "AD102_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkmkmst.kmkcd;
#line 427 "AD102_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 427 "AD102_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 427 "AD102_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkmkmst.smpcd;
#line 427 "AD102_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 427 "AD102_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 427 "AD102_db.sqc"
      sql_setdlist[2].sqldata = (void*)hst_ymd;
#line 427 "AD102_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 427 "AD102_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 427 "AD102_db.sqc"
      sql_setdlist[3].sqldata = (void*)hst_ymd;
#line 427 "AD102_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 427 "AD102_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 427 "AD102_db.sqc"
      sql_setdlist[4].sqldata = (void*)hst_ymd;
#line 427 "AD102_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 427 "AD102_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 427 "AD102_db.sqc"
      sql_setdlist[5].sqldata = (void*)hst_ymd;
#line 427 "AD102_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 427 "AD102_db.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 427 "AD102_db.sqc"
  sqlaaloc(3,1,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 427 "AD102_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 427 "AD102_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkmkmst.knsgrp;
#line 427 "AD102_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 427 "AD102_db.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 427 "AD102_db.sqc"
  sqlacall((unsigned short)24,5,2,3,0L);
#line 427 "AD102_db.sqc"
  sqlastop(0L);
}

#line 427 "AD102_db.sqc"

	} else {								// �W���ȊO

/*
EXEC SQL SELECT		km.knsgrp
			INTO	:hkmkmst.knsgrp
			FROM	kmkmst km
					, knsgmst kg
			WHERE	km.kmkcd	=  :hkmkmst.kmkcd
			AND		km.smpcd	=  :hkmkmst.smpcd
			AND		km.kaiymd	<= :hst_ymd
			AND		km.haiymd	>= :hst_ymd
			AND		km.knsgrp	=  kg.knsgrp
			AND		kg.knssbt	NOT IN ('S','T')
			AND		kg.kaiymd	<= :hst_ymd
			AND		kg.haiymd	>= :hst_ymd
			ORDER BY km.knsgrp
			FETCH FIRST 1 ROWS ONLY
			;
*/

{
#line 443 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 443 "AD102_db.sqc"
  sqlaaloc(2,6,9,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 443 "AD102_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 443 "AD102_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkmkmst.kmkcd;
#line 443 "AD102_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 443 "AD102_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 443 "AD102_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkmkmst.smpcd;
#line 443 "AD102_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 443 "AD102_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 443 "AD102_db.sqc"
      sql_setdlist[2].sqldata = (void*)hst_ymd;
#line 443 "AD102_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 443 "AD102_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 443 "AD102_db.sqc"
      sql_setdlist[3].sqldata = (void*)hst_ymd;
#line 443 "AD102_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 443 "AD102_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 443 "AD102_db.sqc"
      sql_setdlist[4].sqldata = (void*)hst_ymd;
#line 443 "AD102_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 443 "AD102_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 443 "AD102_db.sqc"
      sql_setdlist[5].sqldata = (void*)hst_ymd;
#line 443 "AD102_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 443 "AD102_db.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 443 "AD102_db.sqc"
  sqlaaloc(3,1,10,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 443 "AD102_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 443 "AD102_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkmkmst.knsgrp;
#line 443 "AD102_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 443 "AD102_db.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 443 "AD102_db.sqc"
  sqlacall((unsigned short)24,6,2,3,0L);
#line 443 "AD102_db.sqc"
  sqlastop(0L);
}

#line 443 "AD102_db.sqc"

	}

	sprintf( G_err, "%d", sqlca.sqlcode );
	// DEBUG
	sprintf( G_msg, "SELECT kmkmst : kmkcd[%s]smpcd[%s]ymd[%s]"
			, hkmkmst.kmkcd, hkmkmst.smpcd, ymd );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if ( sqlca.sqlcode == 0 ) {
		strcpy( km->knsgrp,	hkmkmst.knsgrp );
		ret=RTN_OK;
	} else {
		if ( sqlca.sqlcode == 100 ) {
			ret=RTN_ZERO;
		} else {
			sprintf( G_msg,
				"�����O���[�v�R�[�h�擾���ɕs����������܂����B"
				"����CD[%s]SMPCD[%s]�W��F[%s]",
				km->kmkcd, km->smpcd, km->skflg );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			ret=RTN_DBERR;
		}
	}

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

// 1.04 ADD END =============================================================

/******************************************************************************/
/*  �� �� ��  �FInsIrai                                                     */
/*  �@�\�T�v  �F�˗����@INSERT                                              */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _IRAI     *iri;   : �˗����                        */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		InsIrai( iri )
struct		_IRAI	*iri;			/* �˗��f�[�^ */
{
	struct	sqlca	sqlca;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	int	ret;

	/* ��������	*/
	strcpy(func_nm, "InsIrai" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̃Z�b�g	*/
	memcpy( &hirai, iri, sizeof( struct _IRAI ));


/*
EXEC SQL INSERT	INTO	irai
		( utkymd
		, irino
		, iriketflg
		, zssdino
		, knsgrp
		, kmkcd
		, irihsmkbn
		, irikbn
		, ksktkbn
		, sriymd
		, kntno
		, kntketflg
		, chkmj
		, stsrcd
		, kmkrs
		, oyakmkcd
		, smpcd
		, setkmkcd
		, srinycd
		, seccd
		, skchkflg
		, bkfkkbn
		, ysnlbl
		, skflg
		, tkflg
		, sjflg
		, jktkflg
		, kjno
		, fkhkknohjkbn
		, tbkjno
		, tbkjflg
		, htkfkhms
		, tskflg
		, tktflg
		, bnckbn
		, nbnckbn
		, knskisyymd
		, knskryymd
		, knskrytme
		, kkhkkflg
		, kkiriflg
		, kkirilotno
		, kktoutkid
		, knssu
		, odrssflg
		, ytiksbr
		, hhkjkflg
		, ksndh
		, trkdh					-- 1.01 ADD
		)
	VALUES  ( :hirai.utkymd
		, :hirai.irino
		, :hirai.iriketflg
		, :hirai.zssdino
		, :hirai.knsgrp
		, :hirai.kmkcd
		, :hirai.irihsmkbn
		, :hirai.irikbn
		, :hirai.ksktkbn
		, :hirai.sriymd
		, :hirai.kntno
		, :hirai.kntketflg
		, :hirai.chkmj
		, :hirai.stsrcd
		, :hirai.kmkrs
		, :hirai.oyakmkcd
		, :hirai.smpcd
		, :hirai.setkmkcd
		, :hirai.srinycd
		, :hirai.seccd
		, :hirai.skchkflg
		, :hirai.bkfkkbn
		, :hirai.ysnlbl
		, :hirai.skflg
		, :hirai.tkflg
		, :hirai.sjflg
		, :hirai.jktkflg
		, :hirai.kjno
		, :hirai.fkhkknohjkbn
		, :hirai.tbkjno
		, :hirai.tbkjflg
		, :hirai.htkfkhms
		, :hirai.tskflg
		, :hirai.tktflg
		, :hirai.bnckbn
		, :hirai.nbnckbn
		, :hirai.knskisyymd
		, :hirai.knskryymd
		, :hirai.knskrytme
		, :hirai.kkhkkflg
		, :hirai.kkiriflg
		, :hirai.kkirilotno
		, :hirai.kktoutkid
		, :hirai.knssu
		, :hirai.odrssflg
		, :hirai.ytiksbr
		, :hirai.hhkjkflg
		, CURRENT TIMESTAMP
		, CURRENT TIMESTAMP				-- 1.01 ADD
		)
	;
*/

{
#line 599 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 599 "AD102_db.sqc"
  sqlaaloc(2,47,11,0L);
    {
      struct sqla_setdata_list sql_setdlist[47];
#line 599 "AD102_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 599 "AD102_db.sqc"
      sql_setdlist[0].sqldata = (void*)hirai.utkymd;
#line 599 "AD102_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 599 "AD102_db.sqc"
      sql_setdlist[1].sqldata = (void*)hirai.irino;
#line 599 "AD102_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 599 "AD102_db.sqc"
      sql_setdlist[2].sqldata = (void*)hirai.iriketflg;
#line 599 "AD102_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 599 "AD102_db.sqc"
      sql_setdlist[3].sqldata = (void*)&hirai.zssdino;
#line 599 "AD102_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 599 "AD102_db.sqc"
      sql_setdlist[4].sqldata = (void*)hirai.knsgrp;
#line 599 "AD102_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 599 "AD102_db.sqc"
      sql_setdlist[5].sqldata = (void*)hirai.kmkcd;
#line 599 "AD102_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 2;
#line 599 "AD102_db.sqc"
      sql_setdlist[6].sqldata = (void*)hirai.irihsmkbn;
#line 599 "AD102_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 2;
#line 599 "AD102_db.sqc"
      sql_setdlist[7].sqldata = (void*)hirai.irikbn;
#line 599 "AD102_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 2;
#line 599 "AD102_db.sqc"
      sql_setdlist[8].sqldata = (void*)hirai.ksktkbn;
#line 599 "AD102_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 599 "AD102_db.sqc"
      sql_setdlist[9].sqldata = (void*)hirai.sriymd;
#line 599 "AD102_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 14;
#line 599 "AD102_db.sqc"
      sql_setdlist[10].sqldata = (void*)hirai.kntno;
#line 599 "AD102_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 2;
#line 599 "AD102_db.sqc"
      sql_setdlist[11].sqldata = (void*)hirai.kntketflg;
#line 599 "AD102_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 5;
#line 599 "AD102_db.sqc"
      sql_setdlist[12].sqldata = (void*)hirai.chkmj;
#line 599 "AD102_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 5;
#line 599 "AD102_db.sqc"
      sql_setdlist[13].sqldata = (void*)hirai.stsrcd;
#line 599 "AD102_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 17;
#line 599 "AD102_db.sqc"
      sql_setdlist[14].sqldata = (void*)hirai.kmkrs;
#line 599 "AD102_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 599 "AD102_db.sqc"
      sql_setdlist[15].sqldata = (void*)hirai.oyakmkcd;
#line 599 "AD102_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 8;
#line 599 "AD102_db.sqc"
      sql_setdlist[16].sqldata = (void*)hirai.smpcd;
#line 599 "AD102_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 8;
#line 599 "AD102_db.sqc"
      sql_setdlist[17].sqldata = (void*)hirai.setkmkcd;
#line 599 "AD102_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 2;
#line 599 "AD102_db.sqc"
      sql_setdlist[18].sqldata = (void*)hirai.srinycd;
#line 599 "AD102_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 3;
#line 599 "AD102_db.sqc"
      sql_setdlist[19].sqldata = (void*)hirai.seccd;
#line 599 "AD102_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 2;
#line 599 "AD102_db.sqc"
      sql_setdlist[20].sqldata = (void*)hirai.skchkflg;
#line 599 "AD102_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 2;
#line 599 "AD102_db.sqc"
      sql_setdlist[21].sqldata = (void*)hirai.bkfkkbn;
#line 599 "AD102_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 3;
#line 599 "AD102_db.sqc"
      sql_setdlist[22].sqldata = (void*)hirai.ysnlbl;
#line 599 "AD102_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 2;
#line 599 "AD102_db.sqc"
      sql_setdlist[23].sqldata = (void*)hirai.skflg;
#line 599 "AD102_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 2;
#line 599 "AD102_db.sqc"
      sql_setdlist[24].sqldata = (void*)hirai.tkflg;
#line 599 "AD102_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 2;
#line 599 "AD102_db.sqc"
      sql_setdlist[25].sqldata = (void*)hirai.sjflg;
#line 599 "AD102_db.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 2;
#line 599 "AD102_db.sqc"
      sql_setdlist[26].sqldata = (void*)hirai.jktkflg;
#line 599 "AD102_db.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 4;
#line 599 "AD102_db.sqc"
      sql_setdlist[27].sqldata = (void*)hirai.kjno;
#line 599 "AD102_db.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 2;
#line 599 "AD102_db.sqc"
      sql_setdlist[28].sqldata = (void*)hirai.fkhkknohjkbn;
#line 599 "AD102_db.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 4;
#line 599 "AD102_db.sqc"
      sql_setdlist[29].sqldata = (void*)hirai.tbkjno;
#line 599 "AD102_db.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 2;
#line 599 "AD102_db.sqc"
      sql_setdlist[30].sqldata = (void*)hirai.tbkjflg;
#line 599 "AD102_db.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 25;
#line 599 "AD102_db.sqc"
      sql_setdlist[31].sqldata = (void*)hirai.htkfkhms;
#line 599 "AD102_db.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 599 "AD102_db.sqc"
      sql_setdlist[32].sqldata = (void*)hirai.tskflg;
#line 599 "AD102_db.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 599 "AD102_db.sqc"
      sql_setdlist[33].sqldata = (void*)hirai.tktflg;
#line 599 "AD102_db.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 2;
#line 599 "AD102_db.sqc"
      sql_setdlist[34].sqldata = (void*)hirai.bnckbn;
#line 599 "AD102_db.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 2;
#line 599 "AD102_db.sqc"
      sql_setdlist[35].sqldata = (void*)hirai.nbnckbn;
#line 599 "AD102_db.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 11;
#line 599 "AD102_db.sqc"
      sql_setdlist[36].sqldata = (void*)hirai.knskisyymd;
#line 599 "AD102_db.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 11;
#line 599 "AD102_db.sqc"
      sql_setdlist[37].sqldata = (void*)hirai.knskryymd;
#line 599 "AD102_db.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 9;
#line 599 "AD102_db.sqc"
      sql_setdlist[38].sqldata = (void*)hirai.knskrytme;
#line 599 "AD102_db.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 2;
#line 599 "AD102_db.sqc"
      sql_setdlist[39].sqldata = (void*)hirai.kkhkkflg;
#line 599 "AD102_db.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 2;
#line 599 "AD102_db.sqc"
      sql_setdlist[40].sqldata = (void*)hirai.kkiriflg;
#line 599 "AD102_db.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[41].sqltype = 500; sql_setdlist[41].sqllen = 2;
#line 599 "AD102_db.sqc"
      sql_setdlist[41].sqldata = (void*)&hirai.kkirilotno;
#line 599 "AD102_db.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 5;
#line 599 "AD102_db.sqc"
      sql_setdlist[42].sqldata = (void*)hirai.kktoutkid;
#line 599 "AD102_db.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[43].sqltype = 500; sql_setdlist[43].sqllen = 2;
#line 599 "AD102_db.sqc"
      sql_setdlist[43].sqldata = (void*)&hirai.knssu;
#line 599 "AD102_db.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 2;
#line 599 "AD102_db.sqc"
      sql_setdlist[44].sqldata = (void*)hirai.odrssflg;
#line 599 "AD102_db.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 16;
#line 599 "AD102_db.sqc"
      sql_setdlist[45].sqldata = (void*)hirai.ytiksbr;
#line 599 "AD102_db.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 2;
#line 599 "AD102_db.sqc"
      sql_setdlist[46].sqldata = (void*)hirai.hhkjkflg;
#line 599 "AD102_db.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 599 "AD102_db.sqc"
      sqlasetdata(2,0,47,sql_setdlist,0L,0L);
    }
#line 599 "AD102_db.sqc"
  sqlacall((unsigned short)24,7,2,0,0L);
#line 599 "AD102_db.sqc"
  sqlastop(0L);
}

#line 599 "AD102_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "INSERT irai : utkymd[%s]irino[%s]zssdino[%d]kmkcd[%s]",
		iri->utkymd, iri->irino, iri->zssdino, iri->kmkcd );
	LogOut( LT_DBG, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if ( sqlca.sqlcode == 0 ) {		/* OK */
		ret = RTN_OK;
	} else {
		if ( sqlca.sqlcode == MYAPP_RTN_DUP ) {	// duplicate
			//sprintf( G_msg,
			//		"�˗����(irai)�͊��ɑ��݂��Ă��܂��B"
			//		"BML��t�N����[%s]�˗���NO[%s]�˗�����NO[%d]����CD[%s]"
			//		,iri->utkymd, iri->irino, iri->zssdino, iri->kmkcd );
			ret=MYAPP_RTN_DUP;
		} else {
			/* ERROR */
			sprintf( G_msg,
				"�˗����(irai)�� INSERT �Ɏ��s���܂����B"
				"BML��t�N����[%s]�˗���NO[%s]�˗�����NO[%d]����CD[%s]"
				,iri->utkymd, iri->irino, iri->zssdino, iri->kmkcd );
			ret=RTN_DBERR;
			EditCsvMsg( G_msg );
			LogOut( LT_TRC, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		}
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FUpdIraiSjflg                                                  */
/*  �@�\�T�v  �F�˗���� �폜�t���O UPDATE                                    */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _IRAI    *iri;   : �˗����                           */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		UpdIraiSjflg( iri )
struct		_IRAI		*iri;			/* �˗���� */
{
	struct	sqlca	sqlca;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	int		ret;
	int		i;

	/* ��������	*/
	strcpy( func_nm, "UpdIraiSjflg" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	memset( &hirai, '\0', sizeof( struct _IRAI ));
	strcpy( hirai.utkymd,	iri->utkymd );
	strcpy( hirai.irino,	iri->irino );
	hirai.zssdino=iri->zssdino;
	strcpy( hirai.kmkcd,	iri->kmkcd );

	// �Ώۃf�[�^��SELECT

/*
EXEC SQL 	UPDATE	irai
			SET		sjflg	= '1'
					, ksndh	= CURRENT TIMESTAMP
			WHERE	utkymd	= :hirai.utkymd
			AND		irino	= :hirai.irino
			AND		kmkcd	= :hirai.kmkcd
			AND		odrssflg= ' '
			;
*/

{
#line 671 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 671 "AD102_db.sqc"
  sqlaaloc(2,3,12,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 671 "AD102_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 671 "AD102_db.sqc"
      sql_setdlist[0].sqldata = (void*)hirai.utkymd;
#line 671 "AD102_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 671 "AD102_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 671 "AD102_db.sqc"
      sql_setdlist[1].sqldata = (void*)hirai.irino;
#line 671 "AD102_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 671 "AD102_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 671 "AD102_db.sqc"
      sql_setdlist[2].sqldata = (void*)hirai.kmkcd;
#line 671 "AD102_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 671 "AD102_db.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 671 "AD102_db.sqc"
  sqlacall((unsigned short)24,8,2,0,0L);
#line 671 "AD102_db.sqc"
  sqlastop(0L);
}

#line 671 "AD102_db.sqc"


	/* SQLCODE */
	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//		sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "UPDATE irai sjflg : "
		"utkymd[%s]irino[%s]zssdino[%d]kmkcd[%s]"
		,iri->utkymd, iri->irino, hirai.zssdino, iri->kmkcd );
	LogOut( LT_DBG, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if (sqlca.sqlcode == 0) {	
		ret=RTN_OK;
	} else if (sqlca.sqlcode == 100 ) {	
		sprintf( G_msg,
			"�X�V�Ώۂ̈˗����(irai)�����݂��܂���B"
			"BML��t�N����[%s]�˗���NO[%s]�˗�����NO[?]����CD[%s]"
			,iri->utkymd, iri->irino, iri->kmkcd );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		ret=RTN_ZERO;
	} else {
		if( sqlca.sqlcode == -911 ){		// LOCK
			switch( sqlca.sqlerrd[2] ){
			case	 2 :
				strcpy( G_msg, "�˗����(irai)�̍폜�t���O UPDATE ��"
					"DEAD LOCK ���������܂����B" );
				break;
			case	68 :
				strcpy( G_msg, "�˗����(irai)�̍폜�t���O UPDATE ��"
					"TIMETOUT ���������܂����B" );
				break;
			default :
				strcpy( G_msg, "�˗����(irai)�̍폜�t���O UPDATE ��"
					"�s����������܂����B" );
				break;
			}
		} else {
			/* SQLCODE > 0 -> WARNING */
			/* SQLCODE < 0 -> ERROR */
			sprintf( G_msg,
				"�˗����(irai)�̍폜�t���O UPDATE �Ɏ��s���܂����B"
				"BML��t�N����[%s]�˗���NO[%s]�˗�����NO[?]����CD[%s]"
				,iri->utkymd, iri->irino, iri->kmkcd );
		}
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		ret=RTN_DBERR;
	}

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FUpdMichakuIrai                                                */
/*  �@�\�T�v  �F�����Đ��˗��Ή��@�˗���� UPDATE(�I�[�_���쐬�̂݁j          */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _IRAI    *iri;   : �˗����                           */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
// 1.05 DELL int		UpdMichakuIrai( iri )/
int		UpdMichakuIrai( iri, age, age_kbn )
struct		_IRAI		*iri;			/* �˗���� */
char		age[];						// 1.05 ADD
char		age_kbn[];					// 1.05 ADD
{
	int		ret;
	char	func_nm[30];				/* �֐�����	*/
	char	wbuf[30];
	struct	_IRAI	bupIri;
	struct  stcKJNO     kj;                 // ��lNO�擾�p�\����
	struct	sqlca	sqlca;

	/* ��������	*/
	strcpy( func_nm, "UpdMichakuIrai" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	memset( &hirai, '\0', sizeof( struct _IRAI ));
	strcpy( hirai.utkymd,	iri->utkymd );
	strcpy( hirai.irino,	iri->irino );
	strcpy( hirai.kmkcd,	iri->kmkcd );
	strcpy( hirai.sriymd,	iri->sriymd );
	hirai.zssdino = iri->zssdino;

// ----- SELECT  ------------------------------------------------------------
	// �Ώۃf�[�^��SELECT

/*
EXEC SQL SELECT	* INTO
		:hirai.utkymd
		, :hirai.irino
		, :hirai.iriketflg
		, :hirai.zssdino
		, :hirai.knsgrp
		, :hirai.kmkcd
		, :hirai.irihsmkbn
		, :hirai.irikbn
		, :hirai.ksktkbn
		, :hirai.sriymd
		, :hirai.kntno
		, :hirai.kntketflg
		, :hirai.chkmj
		, :hirai.stsrcd
		, :hirai.kmkrs
		, :hirai.oyakmkcd
		, :hirai.smpcd
		, :hirai.setkmkcd
		, :hirai.srinycd
		, :hirai.seccd
		, :hirai.skchkflg
		, :hirai.bkfkkbn
		, :hirai.ysnlbl
		, :hirai.skflg
		, :hirai.tkflg
		, :hirai.sjflg
		, :hirai.jktkflg
		, :hirai.kjno
		, :hirai.fkhkknohjkbn
		, :hirai.tbkjno
		, :hirai.tbkjflg
		, :hirai.htkfkhms
		, :hirai.tskflg
		, :hirai.tktflg
		, :hirai.bnckbn
		, :hirai.nbnckbn
		, :hirai.knskisyymd
		, :hirai.knskryymd
		, :hirai.knskrytme
		, :hirai.kkhkkflg
		, :hirai.kkiriflg
		, :hirai.kkirilotno
		, :hirai.kktoutkid
		, :hirai.knssu
		, :hirai.odrssflg
		, :hirai.ytiksbr
		, :hirai.hhkjkflg
		, :hirai.ksndh
		, :hirai.trkdh
	FROM	irai
	WHERE	utkymd	= :hirai.utkymd
	AND		irino	= :hirai.irino
--	AND		knsgrp	= ' '			// �˗��W�J�ł̌���G�t���ɔ��������O
	AND		kmkcd	= :hirai.kmkcd
	AND		sriymd	<> :hirai.sriymd
	AND		odrssflg	= ' '
	;
*/

{
#line 822 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 822 "AD102_db.sqc"
  sqlaaloc(2,4,13,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 822 "AD102_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 822 "AD102_db.sqc"
      sql_setdlist[0].sqldata = (void*)hirai.utkymd;
#line 822 "AD102_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 822 "AD102_db.sqc"
      sql_setdlist[1].sqldata = (void*)hirai.irino;
#line 822 "AD102_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 822 "AD102_db.sqc"
      sql_setdlist[2].sqldata = (void*)hirai.kmkcd;
#line 822 "AD102_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 822 "AD102_db.sqc"
      sql_setdlist[3].sqldata = (void*)hirai.sriymd;
#line 822 "AD102_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 822 "AD102_db.sqc"
  sqlaaloc(3,49,14,0L);
    {
      struct sqla_setdata_list sql_setdlist[49];
#line 822 "AD102_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 822 "AD102_db.sqc"
      sql_setdlist[0].sqldata = (void*)hirai.utkymd;
#line 822 "AD102_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 822 "AD102_db.sqc"
      sql_setdlist[1].sqldata = (void*)hirai.irino;
#line 822 "AD102_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 822 "AD102_db.sqc"
      sql_setdlist[2].sqldata = (void*)hirai.iriketflg;
#line 822 "AD102_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 822 "AD102_db.sqc"
      sql_setdlist[3].sqldata = (void*)&hirai.zssdino;
#line 822 "AD102_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 822 "AD102_db.sqc"
      sql_setdlist[4].sqldata = (void*)hirai.knsgrp;
#line 822 "AD102_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 822 "AD102_db.sqc"
      sql_setdlist[5].sqldata = (void*)hirai.kmkcd;
#line 822 "AD102_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 2;
#line 822 "AD102_db.sqc"
      sql_setdlist[6].sqldata = (void*)hirai.irihsmkbn;
#line 822 "AD102_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 2;
#line 822 "AD102_db.sqc"
      sql_setdlist[7].sqldata = (void*)hirai.irikbn;
#line 822 "AD102_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 2;
#line 822 "AD102_db.sqc"
      sql_setdlist[8].sqldata = (void*)hirai.ksktkbn;
#line 822 "AD102_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 822 "AD102_db.sqc"
      sql_setdlist[9].sqldata = (void*)hirai.sriymd;
#line 822 "AD102_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 14;
#line 822 "AD102_db.sqc"
      sql_setdlist[10].sqldata = (void*)hirai.kntno;
#line 822 "AD102_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 2;
#line 822 "AD102_db.sqc"
      sql_setdlist[11].sqldata = (void*)hirai.kntketflg;
#line 822 "AD102_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 5;
#line 822 "AD102_db.sqc"
      sql_setdlist[12].sqldata = (void*)hirai.chkmj;
#line 822 "AD102_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 5;
#line 822 "AD102_db.sqc"
      sql_setdlist[13].sqldata = (void*)hirai.stsrcd;
#line 822 "AD102_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 17;
#line 822 "AD102_db.sqc"
      sql_setdlist[14].sqldata = (void*)hirai.kmkrs;
#line 822 "AD102_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 822 "AD102_db.sqc"
      sql_setdlist[15].sqldata = (void*)hirai.oyakmkcd;
#line 822 "AD102_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 8;
#line 822 "AD102_db.sqc"
      sql_setdlist[16].sqldata = (void*)hirai.smpcd;
#line 822 "AD102_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 8;
#line 822 "AD102_db.sqc"
      sql_setdlist[17].sqldata = (void*)hirai.setkmkcd;
#line 822 "AD102_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 2;
#line 822 "AD102_db.sqc"
      sql_setdlist[18].sqldata = (void*)hirai.srinycd;
#line 822 "AD102_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 3;
#line 822 "AD102_db.sqc"
      sql_setdlist[19].sqldata = (void*)hirai.seccd;
#line 822 "AD102_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 2;
#line 822 "AD102_db.sqc"
      sql_setdlist[20].sqldata = (void*)hirai.skchkflg;
#line 822 "AD102_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 2;
#line 822 "AD102_db.sqc"
      sql_setdlist[21].sqldata = (void*)hirai.bkfkkbn;
#line 822 "AD102_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 3;
#line 822 "AD102_db.sqc"
      sql_setdlist[22].sqldata = (void*)hirai.ysnlbl;
#line 822 "AD102_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 2;
#line 822 "AD102_db.sqc"
      sql_setdlist[23].sqldata = (void*)hirai.skflg;
#line 822 "AD102_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 2;
#line 822 "AD102_db.sqc"
      sql_setdlist[24].sqldata = (void*)hirai.tkflg;
#line 822 "AD102_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 2;
#line 822 "AD102_db.sqc"
      sql_setdlist[25].sqldata = (void*)hirai.sjflg;
#line 822 "AD102_db.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 2;
#line 822 "AD102_db.sqc"
      sql_setdlist[26].sqldata = (void*)hirai.jktkflg;
#line 822 "AD102_db.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 4;
#line 822 "AD102_db.sqc"
      sql_setdlist[27].sqldata = (void*)hirai.kjno;
#line 822 "AD102_db.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 2;
#line 822 "AD102_db.sqc"
      sql_setdlist[28].sqldata = (void*)hirai.fkhkknohjkbn;
#line 822 "AD102_db.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 4;
#line 822 "AD102_db.sqc"
      sql_setdlist[29].sqldata = (void*)hirai.tbkjno;
#line 822 "AD102_db.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 2;
#line 822 "AD102_db.sqc"
      sql_setdlist[30].sqldata = (void*)hirai.tbkjflg;
#line 822 "AD102_db.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 25;
#line 822 "AD102_db.sqc"
      sql_setdlist[31].sqldata = (void*)hirai.htkfkhms;
#line 822 "AD102_db.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 822 "AD102_db.sqc"
      sql_setdlist[32].sqldata = (void*)hirai.tskflg;
#line 822 "AD102_db.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 822 "AD102_db.sqc"
      sql_setdlist[33].sqldata = (void*)hirai.tktflg;
#line 822 "AD102_db.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 2;
#line 822 "AD102_db.sqc"
      sql_setdlist[34].sqldata = (void*)hirai.bnckbn;
#line 822 "AD102_db.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 2;
#line 822 "AD102_db.sqc"
      sql_setdlist[35].sqldata = (void*)hirai.nbnckbn;
#line 822 "AD102_db.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 11;
#line 822 "AD102_db.sqc"
      sql_setdlist[36].sqldata = (void*)hirai.knskisyymd;
#line 822 "AD102_db.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 11;
#line 822 "AD102_db.sqc"
      sql_setdlist[37].sqldata = (void*)hirai.knskryymd;
#line 822 "AD102_db.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 9;
#line 822 "AD102_db.sqc"
      sql_setdlist[38].sqldata = (void*)hirai.knskrytme;
#line 822 "AD102_db.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 2;
#line 822 "AD102_db.sqc"
      sql_setdlist[39].sqldata = (void*)hirai.kkhkkflg;
#line 822 "AD102_db.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 2;
#line 822 "AD102_db.sqc"
      sql_setdlist[40].sqldata = (void*)hirai.kkiriflg;
#line 822 "AD102_db.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[41].sqltype = 500; sql_setdlist[41].sqllen = 2;
#line 822 "AD102_db.sqc"
      sql_setdlist[41].sqldata = (void*)&hirai.kkirilotno;
#line 822 "AD102_db.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 5;
#line 822 "AD102_db.sqc"
      sql_setdlist[42].sqldata = (void*)hirai.kktoutkid;
#line 822 "AD102_db.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[43].sqltype = 500; sql_setdlist[43].sqllen = 2;
#line 822 "AD102_db.sqc"
      sql_setdlist[43].sqldata = (void*)&hirai.knssu;
#line 822 "AD102_db.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 2;
#line 822 "AD102_db.sqc"
      sql_setdlist[44].sqldata = (void*)hirai.odrssflg;
#line 822 "AD102_db.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 16;
#line 822 "AD102_db.sqc"
      sql_setdlist[45].sqldata = (void*)hirai.ytiksbr;
#line 822 "AD102_db.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 2;
#line 822 "AD102_db.sqc"
      sql_setdlist[46].sqldata = (void*)hirai.hhkjkflg;
#line 822 "AD102_db.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 27;
#line 822 "AD102_db.sqc"
      sql_setdlist[47].sqldata = (void*)hirai.ksndh;
#line 822 "AD102_db.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 27;
#line 822 "AD102_db.sqc"
      sql_setdlist[48].sqldata = (void*)hirai.trkdh;
#line 822 "AD102_db.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 822 "AD102_db.sqc"
      sqlasetdata(3,0,49,sql_setdlist,0L,0L);
    }
#line 822 "AD102_db.sqc"
  sqlacall((unsigned short)24,9,2,3,0L);
#line 822 "AD102_db.sqc"
  sqlastop(0L);
}

#line 822 "AD102_db.sqc"


	/* SQLCODE */
	// edit sqlcacode for LogOut errcode
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "SELECT * FROM irai before update: "
		"utkymd[%s]irino[%s]kmkcd[%s]",
		iri->utkymd, iri->irino, iri->kmkcd );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if ( sqlca.sqlcode == 0 ) {		/* OK */
		// DEBUG
		sprintf( G_msg, "�����Đ��̈˗������X�V���܂� : "
			"���[%s]�˗���No[%s]����No[%d]����CD[%s]������[%s](�O������[%s])",
			hirai.utkymd,hirai.irino,hirai.zssdino,hirai.kmkcd,
			iri->sriymd, hirai.sriymd );
		EditCsvMsg( G_msg );
		LogOut( LT_TRC, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		// �X�V�O����LOG�o��
		EditCsvIrai( &hirai );
		LogOut( LT_TRC, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
	} else {
		if ( sqlca.sqlcode == 100 ){	/* NOT FOUND */
			// �����Đ��Ώۂł͑��݂��Ȃ�
			return( RTN_ZERO );
		} else {
			sprintf( G_msg, "�X�V�Ώۂ̈˗����(irai) SELECT ��"
				"�s����������܂����B" );
			EditCsvMsg( G_msg );
			LogOut( LT_ERR, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			return( RTN_DBERR );
		}
	}
	/* �z�X�g�ϐ��Z�b�g	*/
		// 1.01 ADD �o�^�����͍X�V�O�̒l�������p��
	strcpy( wbuf,			hirai.trkdh );
	memcpy( &hirai, iri,	sizeof( struct _IRAI ));
	strcpy( hirai.trkdh,	wbuf );				// 1.01 ADD
	if( stcPRM.myp_debug == 1 ){
		irai_pr( &hirai );
	}

// ----- UPDATE ------------------------------------------------------------

/*
EXEC SQL UPDATE	irai	
	SET utkymd			= :hirai.utkymd
		, irino			= :hirai.irino
		, iriketflg		= :hirai.iriketflg
		, zssdino		= :hirai.zssdino
		, knsgrp		= :hirai.knsgrp
		, kmkcd			= :hirai.kmkcd
		, irihsmkbn		= :hirai.irihsmkbn
		, irikbn		= :hirai.irikbn
		, ksktkbn		= :hirai.ksktkbn
		, sriymd		= :hirai.sriymd
		, kntno			= :hirai.kntno
		, kntketflg		= :hirai.kntketflg
		, chkmj			= :hirai.chkmj
		, stsrcd		= :hirai.stsrcd
		, kmkrs			= :hirai.kmkrs
		, oyakmkcd		= :hirai.oyakmkcd
		, smpcd			= :hirai.smpcd
		, setkmkcd		= :hirai.setkmkcd
		, srinycd		= :hirai.srinycd
		, seccd			= :hirai.seccd
		, skchkflg		= :hirai.skchkflg
		, bkfkkbn		= :hirai.bkfkkbn
		, ysnlbl		= :hirai.ysnlbl
		, skflg			= :hirai.skflg
		, tkflg			= :hirai.tkflg
		, sjflg			= :hirai.sjflg
		, jktkflg		= :hirai.jktkflg
		, kjno			= :hirai.kjno
		, fkhkknohjkbn	= :hirai.fkhkknohjkbn
		, tbkjno		= :hirai.tbkjno
		, tbkjflg		= :hirai.tbkjflg
		, htkfkhms		= :hirai.htkfkhms
		, tskflg		= :hirai.tskflg
		, tktflg		= :hirai.tktflg
		, bnckbn		= :hirai.bnckbn
		, nbnckbn		= :hirai.nbnckbn
		, knskisyymd	= :hirai.knskisyymd
		, knskryymd		= :hirai.knskryymd
		, knskrytme		= :hirai.knskrytme
		, kkhkkflg		= :hirai.kkhkkflg
		, kkiriflg		= :hirai.kkiriflg
		, kkirilotno	= :hirai.kkirilotno
		, kktoutkid		= :hirai.kktoutkid
		, knssu			= :hirai.knssu
		, odrssflg		= :hirai.odrssflg
		, ytiksbr		= :hirai.ytiksbr
		, hhkjkflg		= :hirai.hhkjkflg
		, ksndh			= CURRENT TIMESTAMP
		, trkdh			= :hirai.trkdh
	WHERE	utkymd	= :hirai.utkymd
	AND		irino	= :hirai.irino
	AND		zssdino	= :hirai.zssdino
--	AND		knsgrp	= ' '				// �˗��W�J�ł̌���G�t���ɔ��������O
	AND		kmkcd	= :hirai.kmkcd
	;
*/

{
#line 922 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 922 "AD102_db.sqc"
  sqlaaloc(2,52,15,0L);
    {
      struct sqla_setdata_list sql_setdlist[52];
#line 922 "AD102_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 922 "AD102_db.sqc"
      sql_setdlist[0].sqldata = (void*)hirai.utkymd;
#line 922 "AD102_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 922 "AD102_db.sqc"
      sql_setdlist[1].sqldata = (void*)hirai.irino;
#line 922 "AD102_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 922 "AD102_db.sqc"
      sql_setdlist[2].sqldata = (void*)hirai.iriketflg;
#line 922 "AD102_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 922 "AD102_db.sqc"
      sql_setdlist[3].sqldata = (void*)&hirai.zssdino;
#line 922 "AD102_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 922 "AD102_db.sqc"
      sql_setdlist[4].sqldata = (void*)hirai.knsgrp;
#line 922 "AD102_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 922 "AD102_db.sqc"
      sql_setdlist[5].sqldata = (void*)hirai.kmkcd;
#line 922 "AD102_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 2;
#line 922 "AD102_db.sqc"
      sql_setdlist[6].sqldata = (void*)hirai.irihsmkbn;
#line 922 "AD102_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 2;
#line 922 "AD102_db.sqc"
      sql_setdlist[7].sqldata = (void*)hirai.irikbn;
#line 922 "AD102_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 2;
#line 922 "AD102_db.sqc"
      sql_setdlist[8].sqldata = (void*)hirai.ksktkbn;
#line 922 "AD102_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 922 "AD102_db.sqc"
      sql_setdlist[9].sqldata = (void*)hirai.sriymd;
#line 922 "AD102_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 14;
#line 922 "AD102_db.sqc"
      sql_setdlist[10].sqldata = (void*)hirai.kntno;
#line 922 "AD102_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 2;
#line 922 "AD102_db.sqc"
      sql_setdlist[11].sqldata = (void*)hirai.kntketflg;
#line 922 "AD102_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 5;
#line 922 "AD102_db.sqc"
      sql_setdlist[12].sqldata = (void*)hirai.chkmj;
#line 922 "AD102_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 5;
#line 922 "AD102_db.sqc"
      sql_setdlist[13].sqldata = (void*)hirai.stsrcd;
#line 922 "AD102_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 17;
#line 922 "AD102_db.sqc"
      sql_setdlist[14].sqldata = (void*)hirai.kmkrs;
#line 922 "AD102_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 922 "AD102_db.sqc"
      sql_setdlist[15].sqldata = (void*)hirai.oyakmkcd;
#line 922 "AD102_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 8;
#line 922 "AD102_db.sqc"
      sql_setdlist[16].sqldata = (void*)hirai.smpcd;
#line 922 "AD102_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 8;
#line 922 "AD102_db.sqc"
      sql_setdlist[17].sqldata = (void*)hirai.setkmkcd;
#line 922 "AD102_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 2;
#line 922 "AD102_db.sqc"
      sql_setdlist[18].sqldata = (void*)hirai.srinycd;
#line 922 "AD102_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 3;
#line 922 "AD102_db.sqc"
      sql_setdlist[19].sqldata = (void*)hirai.seccd;
#line 922 "AD102_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 2;
#line 922 "AD102_db.sqc"
      sql_setdlist[20].sqldata = (void*)hirai.skchkflg;
#line 922 "AD102_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 2;
#line 922 "AD102_db.sqc"
      sql_setdlist[21].sqldata = (void*)hirai.bkfkkbn;
#line 922 "AD102_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 3;
#line 922 "AD102_db.sqc"
      sql_setdlist[22].sqldata = (void*)hirai.ysnlbl;
#line 922 "AD102_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 2;
#line 922 "AD102_db.sqc"
      sql_setdlist[23].sqldata = (void*)hirai.skflg;
#line 922 "AD102_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 2;
#line 922 "AD102_db.sqc"
      sql_setdlist[24].sqldata = (void*)hirai.tkflg;
#line 922 "AD102_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 2;
#line 922 "AD102_db.sqc"
      sql_setdlist[25].sqldata = (void*)hirai.sjflg;
#line 922 "AD102_db.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 2;
#line 922 "AD102_db.sqc"
      sql_setdlist[26].sqldata = (void*)hirai.jktkflg;
#line 922 "AD102_db.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 4;
#line 922 "AD102_db.sqc"
      sql_setdlist[27].sqldata = (void*)hirai.kjno;
#line 922 "AD102_db.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 2;
#line 922 "AD102_db.sqc"
      sql_setdlist[28].sqldata = (void*)hirai.fkhkknohjkbn;
#line 922 "AD102_db.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 4;
#line 922 "AD102_db.sqc"
      sql_setdlist[29].sqldata = (void*)hirai.tbkjno;
#line 922 "AD102_db.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 2;
#line 922 "AD102_db.sqc"
      sql_setdlist[30].sqldata = (void*)hirai.tbkjflg;
#line 922 "AD102_db.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 25;
#line 922 "AD102_db.sqc"
      sql_setdlist[31].sqldata = (void*)hirai.htkfkhms;
#line 922 "AD102_db.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 922 "AD102_db.sqc"
      sql_setdlist[32].sqldata = (void*)hirai.tskflg;
#line 922 "AD102_db.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 922 "AD102_db.sqc"
      sql_setdlist[33].sqldata = (void*)hirai.tktflg;
#line 922 "AD102_db.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 2;
#line 922 "AD102_db.sqc"
      sql_setdlist[34].sqldata = (void*)hirai.bnckbn;
#line 922 "AD102_db.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 2;
#line 922 "AD102_db.sqc"
      sql_setdlist[35].sqldata = (void*)hirai.nbnckbn;
#line 922 "AD102_db.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 11;
#line 922 "AD102_db.sqc"
      sql_setdlist[36].sqldata = (void*)hirai.knskisyymd;
#line 922 "AD102_db.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 11;
#line 922 "AD102_db.sqc"
      sql_setdlist[37].sqldata = (void*)hirai.knskryymd;
#line 922 "AD102_db.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 9;
#line 922 "AD102_db.sqc"
      sql_setdlist[38].sqldata = (void*)hirai.knskrytme;
#line 922 "AD102_db.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 2;
#line 922 "AD102_db.sqc"
      sql_setdlist[39].sqldata = (void*)hirai.kkhkkflg;
#line 922 "AD102_db.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 2;
#line 922 "AD102_db.sqc"
      sql_setdlist[40].sqldata = (void*)hirai.kkiriflg;
#line 922 "AD102_db.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[41].sqltype = 500; sql_setdlist[41].sqllen = 2;
#line 922 "AD102_db.sqc"
      sql_setdlist[41].sqldata = (void*)&hirai.kkirilotno;
#line 922 "AD102_db.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 5;
#line 922 "AD102_db.sqc"
      sql_setdlist[42].sqldata = (void*)hirai.kktoutkid;
#line 922 "AD102_db.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[43].sqltype = 500; sql_setdlist[43].sqllen = 2;
#line 922 "AD102_db.sqc"
      sql_setdlist[43].sqldata = (void*)&hirai.knssu;
#line 922 "AD102_db.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 2;
#line 922 "AD102_db.sqc"
      sql_setdlist[44].sqldata = (void*)hirai.odrssflg;
#line 922 "AD102_db.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 16;
#line 922 "AD102_db.sqc"
      sql_setdlist[45].sqldata = (void*)hirai.ytiksbr;
#line 922 "AD102_db.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 2;
#line 922 "AD102_db.sqc"
      sql_setdlist[46].sqldata = (void*)hirai.hhkjkflg;
#line 922 "AD102_db.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 27;
#line 922 "AD102_db.sqc"
      sql_setdlist[47].sqldata = (void*)hirai.trkdh;
#line 922 "AD102_db.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 11;
#line 922 "AD102_db.sqc"
      sql_setdlist[48].sqldata = (void*)hirai.utkymd;
#line 922 "AD102_db.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 12;
#line 922 "AD102_db.sqc"
      sql_setdlist[49].sqldata = (void*)hirai.irino;
#line 922 "AD102_db.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[50].sqltype = 500; sql_setdlist[50].sqllen = 2;
#line 922 "AD102_db.sqc"
      sql_setdlist[50].sqldata = (void*)&hirai.zssdino;
#line 922 "AD102_db.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 8;
#line 922 "AD102_db.sqc"
      sql_setdlist[51].sqldata = (void*)hirai.kmkcd;
#line 922 "AD102_db.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 922 "AD102_db.sqc"
      sqlasetdata(2,0,52,sql_setdlist,0L,0L);
    }
#line 922 "AD102_db.sqc"
  sqlacall((unsigned short)24,10,2,0,0L);
#line 922 "AD102_db.sqc"
  sqlastop(0L);
}

#line 922 "AD102_db.sqc"


	/* SQLCODE */
	// edit sqlcacode for LogOut errcode
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "UPDATE irai michakusaisei : "
		"utkymd[%s]irino[%s]zssdino[%d]kmkcd[%s]sriymd[%s]",
		iri->utkymd, iri->irino, iri->zssdino, iri->kmkcd, iri->sriymd );
	LogOut( LT_DBG, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if (sqlca.sqlcode == 0) {		/* OK */
		ret = RTN_OK;
	} else {
        if( sqlca.sqlcode == -911 ){        // LOCK
            switch( sqlca.sqlerrd[2] ){
            case     2 :
                strcpy( G_msg, "�����Đ��˗����(irai)�� "
					"UPDATE �� DEAD LOCK ���������܂����B" );
                break;
            case    68 :
                strcpy( G_msg, "�����Đ��˗����(irai)�� "
                    "UPDATE �� TIMETOUT ���������܂����B" );
                break;
            default :
                strcpy( G_msg, "�����Đ��˗����(irai)�� "
                    "�s����������܂����B" );
                break;
            }
		} else {
			/* SQLCODE > 0 -> WARNING */
			/* SQLCODE < 0 -> ERROR */
			sprintf( G_msg,
			"�����Đ��˗����(irai)�� UPDATE �Ɏ��s���܂����B"
				"��t��[%s]�˗���NO[%s]��������NO[%d]����CD[%s]"
				,iri->utkymd, iri->irino, iri->zssdino, iri->kmkcd );
		}
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		ret=RTN_DBERR;
	}
// 1.05 - �����Đ����ڂ̎����������ڂ̍X�V -----------------------------------
	if( ret != RTN_OK ){
		return( ret );
	}
	// �����������̈˗������e�̑ޔ�
	strcpy( hst_utkymd,	hirai.utkymd );
	strcpy( hst_irino,	hirai.irino );
	strcpy( hst_knsgrp,	hirai.knsgrp );
	strcpy( hst_kmkcd,	hirai.kmkcd );
	memset( &bupIri, '\0', sizeof( struct _IRAI ));
	memcpy( &bupIri, &hirai, sizeof( struct _IRAI ));

	
/*
EXEC SQL DECLARE    miji_cur CURSOR  FOR
    SELECT  irai.*
    FROM    irai
			,( SELECT	jknsgrp, jkmkcd
				FROM	jdkmkmst
				WHERE	knsgrp	=	:hst_knsgrp
				AND		kmkcd	=	:hst_kmkcd 
			) jido
    WHERE   utkymd  = :hst_utkymd
    AND     irino   = :hst_irino
	AND     knsgrp  = jido.jknsgrp
	AND     kmkcd	= jido.jkmkcd
	AND		irihsmkbn<>'0'
--    AND     odrssflg= ' '
    ;
*/

#line 990 "AD102_db.sqc"


/*
EXEC SQL OPEN miji_cur;
*/

{
#line 991 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 991 "AD102_db.sqc"
  sqlaaloc(2,4,16,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 991 "AD102_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 991 "AD102_db.sqc"
      sql_setdlist[0].sqldata = (void*)hst_knsgrp;
#line 991 "AD102_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 991 "AD102_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 991 "AD102_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_kmkcd;
#line 991 "AD102_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 991 "AD102_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 991 "AD102_db.sqc"
      sql_setdlist[2].sqldata = (void*)hst_utkymd;
#line 991 "AD102_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 991 "AD102_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 12;
#line 991 "AD102_db.sqc"
      sql_setdlist[3].sqldata = (void*)hst_irino;
#line 991 "AD102_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 991 "AD102_db.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 991 "AD102_db.sqc"
  sqlacall((unsigned short)26,11,2,0,0L);
#line 991 "AD102_db.sqc"
  sqlastop(0L);
}

#line 991 "AD102_db.sqc"


	while( sqlca.sqlcode == 0 ){

/*
EXEC SQL	FETCH	miji_cur
			INTO	:hirai
			;
*/

{
#line 996 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 996 "AD102_db.sqc"
  sqlaaloc(3,49,17,0L);
    {
      struct sqla_setdata_list sql_setdlist[49];
#line 996 "AD102_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 996 "AD102_db.sqc"
      sql_setdlist[0].sqldata = (void*)hirai.utkymd;
#line 996 "AD102_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 996 "AD102_db.sqc"
      sql_setdlist[1].sqldata = (void*)hirai.irino;
#line 996 "AD102_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 996 "AD102_db.sqc"
      sql_setdlist[2].sqldata = (void*)hirai.iriketflg;
#line 996 "AD102_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 996 "AD102_db.sqc"
      sql_setdlist[3].sqldata = (void*)&hirai.zssdino;
#line 996 "AD102_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 996 "AD102_db.sqc"
      sql_setdlist[4].sqldata = (void*)hirai.knsgrp;
#line 996 "AD102_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 996 "AD102_db.sqc"
      sql_setdlist[5].sqldata = (void*)hirai.kmkcd;
#line 996 "AD102_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 2;
#line 996 "AD102_db.sqc"
      sql_setdlist[6].sqldata = (void*)hirai.irihsmkbn;
#line 996 "AD102_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 2;
#line 996 "AD102_db.sqc"
      sql_setdlist[7].sqldata = (void*)hirai.irikbn;
#line 996 "AD102_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 2;
#line 996 "AD102_db.sqc"
      sql_setdlist[8].sqldata = (void*)hirai.ksktkbn;
#line 996 "AD102_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 996 "AD102_db.sqc"
      sql_setdlist[9].sqldata = (void*)hirai.sriymd;
#line 996 "AD102_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 14;
#line 996 "AD102_db.sqc"
      sql_setdlist[10].sqldata = (void*)hirai.kntno;
#line 996 "AD102_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 2;
#line 996 "AD102_db.sqc"
      sql_setdlist[11].sqldata = (void*)hirai.kntketflg;
#line 996 "AD102_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 5;
#line 996 "AD102_db.sqc"
      sql_setdlist[12].sqldata = (void*)hirai.chkmj;
#line 996 "AD102_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 5;
#line 996 "AD102_db.sqc"
      sql_setdlist[13].sqldata = (void*)hirai.stsrcd;
#line 996 "AD102_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 17;
#line 996 "AD102_db.sqc"
      sql_setdlist[14].sqldata = (void*)hirai.kmkrs;
#line 996 "AD102_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 996 "AD102_db.sqc"
      sql_setdlist[15].sqldata = (void*)hirai.oyakmkcd;
#line 996 "AD102_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 8;
#line 996 "AD102_db.sqc"
      sql_setdlist[16].sqldata = (void*)hirai.smpcd;
#line 996 "AD102_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 8;
#line 996 "AD102_db.sqc"
      sql_setdlist[17].sqldata = (void*)hirai.setkmkcd;
#line 996 "AD102_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 2;
#line 996 "AD102_db.sqc"
      sql_setdlist[18].sqldata = (void*)hirai.srinycd;
#line 996 "AD102_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 3;
#line 996 "AD102_db.sqc"
      sql_setdlist[19].sqldata = (void*)hirai.seccd;
#line 996 "AD102_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 2;
#line 996 "AD102_db.sqc"
      sql_setdlist[20].sqldata = (void*)hirai.skchkflg;
#line 996 "AD102_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 2;
#line 996 "AD102_db.sqc"
      sql_setdlist[21].sqldata = (void*)hirai.bkfkkbn;
#line 996 "AD102_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 3;
#line 996 "AD102_db.sqc"
      sql_setdlist[22].sqldata = (void*)hirai.ysnlbl;
#line 996 "AD102_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 2;
#line 996 "AD102_db.sqc"
      sql_setdlist[23].sqldata = (void*)hirai.skflg;
#line 996 "AD102_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 2;
#line 996 "AD102_db.sqc"
      sql_setdlist[24].sqldata = (void*)hirai.tkflg;
#line 996 "AD102_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 2;
#line 996 "AD102_db.sqc"
      sql_setdlist[25].sqldata = (void*)hirai.sjflg;
#line 996 "AD102_db.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 2;
#line 996 "AD102_db.sqc"
      sql_setdlist[26].sqldata = (void*)hirai.jktkflg;
#line 996 "AD102_db.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 4;
#line 996 "AD102_db.sqc"
      sql_setdlist[27].sqldata = (void*)hirai.kjno;
#line 996 "AD102_db.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 2;
#line 996 "AD102_db.sqc"
      sql_setdlist[28].sqldata = (void*)hirai.fkhkknohjkbn;
#line 996 "AD102_db.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 4;
#line 996 "AD102_db.sqc"
      sql_setdlist[29].sqldata = (void*)hirai.tbkjno;
#line 996 "AD102_db.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 2;
#line 996 "AD102_db.sqc"
      sql_setdlist[30].sqldata = (void*)hirai.tbkjflg;
#line 996 "AD102_db.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 25;
#line 996 "AD102_db.sqc"
      sql_setdlist[31].sqldata = (void*)hirai.htkfkhms;
#line 996 "AD102_db.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 996 "AD102_db.sqc"
      sql_setdlist[32].sqldata = (void*)hirai.tskflg;
#line 996 "AD102_db.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 996 "AD102_db.sqc"
      sql_setdlist[33].sqldata = (void*)hirai.tktflg;
#line 996 "AD102_db.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 2;
#line 996 "AD102_db.sqc"
      sql_setdlist[34].sqldata = (void*)hirai.bnckbn;
#line 996 "AD102_db.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 2;
#line 996 "AD102_db.sqc"
      sql_setdlist[35].sqldata = (void*)hirai.nbnckbn;
#line 996 "AD102_db.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 11;
#line 996 "AD102_db.sqc"
      sql_setdlist[36].sqldata = (void*)hirai.knskisyymd;
#line 996 "AD102_db.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 11;
#line 996 "AD102_db.sqc"
      sql_setdlist[37].sqldata = (void*)hirai.knskryymd;
#line 996 "AD102_db.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 9;
#line 996 "AD102_db.sqc"
      sql_setdlist[38].sqldata = (void*)hirai.knskrytme;
#line 996 "AD102_db.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 2;
#line 996 "AD102_db.sqc"
      sql_setdlist[39].sqldata = (void*)hirai.kkhkkflg;
#line 996 "AD102_db.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 2;
#line 996 "AD102_db.sqc"
      sql_setdlist[40].sqldata = (void*)hirai.kkiriflg;
#line 996 "AD102_db.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[41].sqltype = 500; sql_setdlist[41].sqllen = 2;
#line 996 "AD102_db.sqc"
      sql_setdlist[41].sqldata = (void*)&hirai.kkirilotno;
#line 996 "AD102_db.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 5;
#line 996 "AD102_db.sqc"
      sql_setdlist[42].sqldata = (void*)hirai.kktoutkid;
#line 996 "AD102_db.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[43].sqltype = 500; sql_setdlist[43].sqllen = 2;
#line 996 "AD102_db.sqc"
      sql_setdlist[43].sqldata = (void*)&hirai.knssu;
#line 996 "AD102_db.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 2;
#line 996 "AD102_db.sqc"
      sql_setdlist[44].sqldata = (void*)hirai.odrssflg;
#line 996 "AD102_db.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 16;
#line 996 "AD102_db.sqc"
      sql_setdlist[45].sqldata = (void*)hirai.ytiksbr;
#line 996 "AD102_db.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 2;
#line 996 "AD102_db.sqc"
      sql_setdlist[46].sqldata = (void*)hirai.hhkjkflg;
#line 996 "AD102_db.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 27;
#line 996 "AD102_db.sqc"
      sql_setdlist[47].sqldata = (void*)hirai.ksndh;
#line 996 "AD102_db.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 27;
#line 996 "AD102_db.sqc"
      sql_setdlist[48].sqldata = (void*)hirai.trkdh;
#line 996 "AD102_db.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 996 "AD102_db.sqc"
      sqlasetdata(3,0,49,sql_setdlist,0L,0L);
    }
#line 996 "AD102_db.sqc"
  sqlacall((unsigned short)25,11,0,3,0L);
#line 996 "AD102_db.sqc"
  sqlastop(0L);
}

#line 996 "AD102_db.sqc"

		/* SQLCODE */
		sprintf( G_err, "%d", sqlca.sqlcode );
		// DEBUG
		sprintf( G_msg, "FETCH irai michakusaisei jidohassei  : "	
			"utkymd[%s]irino[%s]knsgrp[%s]kmkcd[%s]"
            , hst_utkymd, hst_irino, hst_knsgrp, hst_kmkcd );
        LogOut( LT_DBG, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );

        if (sqlca.sqlcode == 0) {
			if( hirai.odrssflg[0] == ' ' ){
				sprintf( G_msg,
					"�����Đ��ɕR�Â������������ڂ��X�V���܂��B"
					"��t��[%s]�˗���NO[%s]�����Đ�����[%s]������������[%s]"
					, hst_utkymd, hst_irino, hst_kmkcd, hirai.kmkcd );
				EditCsvMsg( G_msg );
				LogOut( LT_DBG, LX_UPD, G_err, G_msg, func_nm, 
						__FILE__, __LINE__ );
				// �X�V�O����LOG�o��
				EditCsvIrai( &hirai );
				LogOut( LT_TRC, LX_UPD, G_err, G_msg, func_nm, 
							__FILE__, __LINE__ );
            	ret=RTN_OK;
			} else {
				sprintf( G_msg,
					"�����Đ��ɕR�Â������������ڂ͊��ɃI�[�_�쐬�ς݂ł��B"
					"��t��[%s]�˗���NO[%s]�����Đ�����[%s]������������[%s]"
					, hst_utkymd, hst_irino, hst_kmkcd, hirai.kmkcd );
				EditCsvMsg( G_msg );
				LogOut( LT_DBG, LX_UPD, G_err, G_msg, func_nm, 
						__FILE__, __LINE__ );
				ret=RTN_OK;
				continue;
			}
        } else if (sqlca.sqlcode == 100) {
            ret=RTN_OK;
            break;
		} else {
            /* SQLCODE > 0 -> WARNING */
            /* SQLCODE < 0 -> ERROR */
            sprintf( G_msg,
				"�����Đ��ɕR�Â������������ڂ�FETCH �Ɏ��s���܂����B"
				"��t��[%s]�˗���NO[%s]�����Đ�����[%s]"
				, hst_utkymd, hst_irino, hst_kmkcd );
            EditCsvMsg( G_msg );
            LogOut( LT_DBG, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
            ret=RTN_DBERR;
            break;
		}
		//------------------------
		// �Ώێ����������ڂ̍X�V
		//------------------------

		// �ޔ������˗����ɓǂݍ��񂾎����������ڂ̏���ҏW����
		// 5 �����O���[�v
		strcpy( bupIri.knsgrp,   hirai.knsgrp );
		// 6 ���ڃR�[�h
		strcpy( bupIri.kmkcd,    hirai.kmkcd );
		// 7 �˗��������敪
		strcpy( bupIri.irihsmkbn,    hirai.irihsmkbn );
    	// 15 ���ڗ���
		strcpy( bupIri.kmkrs,    hirai.kmkrs );
		// 16 �e���ڃR�[�h
		strcpy( bupIri.oyakmkcd, hirai.oyakmkcd );
		// 17 �T���v�����O�R�[�h
		strcpy( bupIri.smpcd,    hirai.smpcd );
		// 18 �Z�b�g���ڃR�[�h
		strcpy( bupIri.setkmkcd, hirai.setkmkcd );
		// 19 �������e�R�[�h
		strcpy( bupIri.srinycd,  hirai.srinycd );
		// 22 ���敉�׋敪
		strcpy( bupIri.bkfkkbn,  hirai.bkfkkbn );
		// 28 ��l�m�n
		memset( &kj,        '\0', sizeof( struct stcKJNO ));
		strcpy( kj.kmkcd,   bupIri.kmkcd );
		strcpy( kj.zrcd,    bupIri.stsrcd );
		strcpy( kj.age,     age );
		strcpy( kj.agekbn,  age_kbn );
		if( GetKjnmst( &kj ) != RTN_OK ){
			sprintf( G_msg,"�Y�������l�}�X�^�f�[�^������܂���B"
				"����CD[%s]�ޗ�CD[%-4s]",
				bupIri.kmkcd, bupIri.stsrcd );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}
		strcpy( bupIri.kjno,	kj.kjno );
		// 45 �I�[�_�쐬�t���O
		strcpy( bupIri.odrssflg, hirai.odrssflg );
		// �o�^����
		strcpy( bupIri.trkdh, 	hirai.trkdh );

		// �ҏW�����\���̂��z�X�g�ϐ��\���̂ɃZ�b�g
		memcpy( &hirai,	&bupIri,	sizeof( struct _IRAI ));

		// ini�t�@�C���ł�DEBUG�w�莞�̂�print���������s
		if( stcPRM.myp_debug == 1 ){
			irai_pr( &hirai );
		};
    	// ���O�o�͗p�L�[���ڐݒ�
    	strcpy( G_utkymd,   hirai.utkymd );
    	strcpy( G_irino,    hirai.irino );
    	strcpy( G_kmkcd,    hirai.kmkcd );
    	G_zssdino=bupIri.zssdino;
		
	// PG�I�ɂ̓_�T��������UPDATE�����L�q����

/*
EXEC SQL UPDATE	irai	
	SET utkymd			= :hirai.utkymd
		, irino			= :hirai.irino
		, iriketflg		= :hirai.iriketflg
		, zssdino		= :hirai.zssdino
		, knsgrp		= :hirai.knsgrp
		, kmkcd			= :hirai.kmkcd
		, irihsmkbn		= :hirai.irihsmkbn
		, irikbn		= :hirai.irikbn
		, ksktkbn		= :hirai.ksktkbn
		, sriymd		= :hirai.sriymd
		, kntno			= :hirai.kntno
		, kntketflg		= :hirai.kntketflg
		, chkmj			= :hirai.chkmj
		, stsrcd		= :hirai.stsrcd
		, kmkrs			= :hirai.kmkrs
		, oyakmkcd		= :hirai.oyakmkcd
		, smpcd			= :hirai.smpcd
		, setkmkcd		= :hirai.setkmkcd
		, srinycd		= :hirai.srinycd
		, seccd			= :hirai.seccd
		, skchkflg		= :hirai.skchkflg
		, bkfkkbn		= :hirai.bkfkkbn
		, ysnlbl		= :hirai.ysnlbl
		, skflg			= :hirai.skflg
		, tkflg			= :hirai.tkflg
		, sjflg			= :hirai.sjflg
		, jktkflg		= :hirai.jktkflg
		, kjno			= :hirai.kjno
		, fkhkknohjkbn	= :hirai.fkhkknohjkbn
		, tbkjno		= :hirai.tbkjno
		, tbkjflg		= :hirai.tbkjflg
		, htkfkhms		= :hirai.htkfkhms
		, tskflg		= :hirai.tskflg
		, tktflg		= :hirai.tktflg
		, bnckbn		= :hirai.bnckbn
		, nbnckbn		= :hirai.nbnckbn
		, knskisyymd	= :hirai.knskisyymd
		, knskryymd		= :hirai.knskryymd
		, knskrytme		= :hirai.knskrytme
		, kkhkkflg		= :hirai.kkhkkflg
		, kkiriflg		= :hirai.kkiriflg
		, kkirilotno	= :hirai.kkirilotno
		, kktoutkid		= :hirai.kktoutkid
		, knssu			= :hirai.knssu
		, odrssflg		= :hirai.odrssflg
		, ytiksbr		= :hirai.ytiksbr
		, hhkjkflg		= :hirai.hhkjkflg
		, ksndh			= CURRENT TIMESTAMP
		, trkdh			= :hirai.trkdh
	WHERE	utkymd	= :hirai.utkymd
	AND		irino	= :hirai.irino
	AND		zssdino	= :hirai.zssdino
	AND		knsgrp	= :hirai.knsgrp
	AND		kmkcd	= :hirai.kmkcd
	;
*/

{
#line 1156 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1156 "AD102_db.sqc"
  sqlaaloc(2,53,18,0L);
    {
      struct sqla_setdata_list sql_setdlist[53];
#line 1156 "AD102_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1156 "AD102_db.sqc"
      sql_setdlist[0].sqldata = (void*)hirai.utkymd;
#line 1156 "AD102_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1156 "AD102_db.sqc"
      sql_setdlist[1].sqldata = (void*)hirai.irino;
#line 1156 "AD102_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 1156 "AD102_db.sqc"
      sql_setdlist[2].sqldata = (void*)hirai.iriketflg;
#line 1156 "AD102_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 1156 "AD102_db.sqc"
      sql_setdlist[3].sqldata = (void*)&hirai.zssdino;
#line 1156 "AD102_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 1156 "AD102_db.sqc"
      sql_setdlist[4].sqldata = (void*)hirai.knsgrp;
#line 1156 "AD102_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 1156 "AD102_db.sqc"
      sql_setdlist[5].sqldata = (void*)hirai.kmkcd;
#line 1156 "AD102_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 2;
#line 1156 "AD102_db.sqc"
      sql_setdlist[6].sqldata = (void*)hirai.irihsmkbn;
#line 1156 "AD102_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 2;
#line 1156 "AD102_db.sqc"
      sql_setdlist[7].sqldata = (void*)hirai.irikbn;
#line 1156 "AD102_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 2;
#line 1156 "AD102_db.sqc"
      sql_setdlist[8].sqldata = (void*)hirai.ksktkbn;
#line 1156 "AD102_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 1156 "AD102_db.sqc"
      sql_setdlist[9].sqldata = (void*)hirai.sriymd;
#line 1156 "AD102_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 14;
#line 1156 "AD102_db.sqc"
      sql_setdlist[10].sqldata = (void*)hirai.kntno;
#line 1156 "AD102_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 2;
#line 1156 "AD102_db.sqc"
      sql_setdlist[11].sqldata = (void*)hirai.kntketflg;
#line 1156 "AD102_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 5;
#line 1156 "AD102_db.sqc"
      sql_setdlist[12].sqldata = (void*)hirai.chkmj;
#line 1156 "AD102_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 5;
#line 1156 "AD102_db.sqc"
      sql_setdlist[13].sqldata = (void*)hirai.stsrcd;
#line 1156 "AD102_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 17;
#line 1156 "AD102_db.sqc"
      sql_setdlist[14].sqldata = (void*)hirai.kmkrs;
#line 1156 "AD102_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 1156 "AD102_db.sqc"
      sql_setdlist[15].sqldata = (void*)hirai.oyakmkcd;
#line 1156 "AD102_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 8;
#line 1156 "AD102_db.sqc"
      sql_setdlist[16].sqldata = (void*)hirai.smpcd;
#line 1156 "AD102_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 8;
#line 1156 "AD102_db.sqc"
      sql_setdlist[17].sqldata = (void*)hirai.setkmkcd;
#line 1156 "AD102_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 2;
#line 1156 "AD102_db.sqc"
      sql_setdlist[18].sqldata = (void*)hirai.srinycd;
#line 1156 "AD102_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 3;
#line 1156 "AD102_db.sqc"
      sql_setdlist[19].sqldata = (void*)hirai.seccd;
#line 1156 "AD102_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 2;
#line 1156 "AD102_db.sqc"
      sql_setdlist[20].sqldata = (void*)hirai.skchkflg;
#line 1156 "AD102_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 2;
#line 1156 "AD102_db.sqc"
      sql_setdlist[21].sqldata = (void*)hirai.bkfkkbn;
#line 1156 "AD102_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 3;
#line 1156 "AD102_db.sqc"
      sql_setdlist[22].sqldata = (void*)hirai.ysnlbl;
#line 1156 "AD102_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 2;
#line 1156 "AD102_db.sqc"
      sql_setdlist[23].sqldata = (void*)hirai.skflg;
#line 1156 "AD102_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 2;
#line 1156 "AD102_db.sqc"
      sql_setdlist[24].sqldata = (void*)hirai.tkflg;
#line 1156 "AD102_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 2;
#line 1156 "AD102_db.sqc"
      sql_setdlist[25].sqldata = (void*)hirai.sjflg;
#line 1156 "AD102_db.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 2;
#line 1156 "AD102_db.sqc"
      sql_setdlist[26].sqldata = (void*)hirai.jktkflg;
#line 1156 "AD102_db.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 4;
#line 1156 "AD102_db.sqc"
      sql_setdlist[27].sqldata = (void*)hirai.kjno;
#line 1156 "AD102_db.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 2;
#line 1156 "AD102_db.sqc"
      sql_setdlist[28].sqldata = (void*)hirai.fkhkknohjkbn;
#line 1156 "AD102_db.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 4;
#line 1156 "AD102_db.sqc"
      sql_setdlist[29].sqldata = (void*)hirai.tbkjno;
#line 1156 "AD102_db.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 2;
#line 1156 "AD102_db.sqc"
      sql_setdlist[30].sqldata = (void*)hirai.tbkjflg;
#line 1156 "AD102_db.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 25;
#line 1156 "AD102_db.sqc"
      sql_setdlist[31].sqldata = (void*)hirai.htkfkhms;
#line 1156 "AD102_db.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 1156 "AD102_db.sqc"
      sql_setdlist[32].sqldata = (void*)hirai.tskflg;
#line 1156 "AD102_db.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 1156 "AD102_db.sqc"
      sql_setdlist[33].sqldata = (void*)hirai.tktflg;
#line 1156 "AD102_db.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 2;
#line 1156 "AD102_db.sqc"
      sql_setdlist[34].sqldata = (void*)hirai.bnckbn;
#line 1156 "AD102_db.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 2;
#line 1156 "AD102_db.sqc"
      sql_setdlist[35].sqldata = (void*)hirai.nbnckbn;
#line 1156 "AD102_db.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 11;
#line 1156 "AD102_db.sqc"
      sql_setdlist[36].sqldata = (void*)hirai.knskisyymd;
#line 1156 "AD102_db.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 11;
#line 1156 "AD102_db.sqc"
      sql_setdlist[37].sqldata = (void*)hirai.knskryymd;
#line 1156 "AD102_db.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 9;
#line 1156 "AD102_db.sqc"
      sql_setdlist[38].sqldata = (void*)hirai.knskrytme;
#line 1156 "AD102_db.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 2;
#line 1156 "AD102_db.sqc"
      sql_setdlist[39].sqldata = (void*)hirai.kkhkkflg;
#line 1156 "AD102_db.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 2;
#line 1156 "AD102_db.sqc"
      sql_setdlist[40].sqldata = (void*)hirai.kkiriflg;
#line 1156 "AD102_db.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[41].sqltype = 500; sql_setdlist[41].sqllen = 2;
#line 1156 "AD102_db.sqc"
      sql_setdlist[41].sqldata = (void*)&hirai.kkirilotno;
#line 1156 "AD102_db.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 5;
#line 1156 "AD102_db.sqc"
      sql_setdlist[42].sqldata = (void*)hirai.kktoutkid;
#line 1156 "AD102_db.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[43].sqltype = 500; sql_setdlist[43].sqllen = 2;
#line 1156 "AD102_db.sqc"
      sql_setdlist[43].sqldata = (void*)&hirai.knssu;
#line 1156 "AD102_db.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 2;
#line 1156 "AD102_db.sqc"
      sql_setdlist[44].sqldata = (void*)hirai.odrssflg;
#line 1156 "AD102_db.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 16;
#line 1156 "AD102_db.sqc"
      sql_setdlist[45].sqldata = (void*)hirai.ytiksbr;
#line 1156 "AD102_db.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 2;
#line 1156 "AD102_db.sqc"
      sql_setdlist[46].sqldata = (void*)hirai.hhkjkflg;
#line 1156 "AD102_db.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 27;
#line 1156 "AD102_db.sqc"
      sql_setdlist[47].sqldata = (void*)hirai.trkdh;
#line 1156 "AD102_db.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 11;
#line 1156 "AD102_db.sqc"
      sql_setdlist[48].sqldata = (void*)hirai.utkymd;
#line 1156 "AD102_db.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 12;
#line 1156 "AD102_db.sqc"
      sql_setdlist[49].sqldata = (void*)hirai.irino;
#line 1156 "AD102_db.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[50].sqltype = 500; sql_setdlist[50].sqllen = 2;
#line 1156 "AD102_db.sqc"
      sql_setdlist[50].sqldata = (void*)&hirai.zssdino;
#line 1156 "AD102_db.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 17;
#line 1156 "AD102_db.sqc"
      sql_setdlist[51].sqldata = (void*)hirai.knsgrp;
#line 1156 "AD102_db.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 8;
#line 1156 "AD102_db.sqc"
      sql_setdlist[52].sqldata = (void*)hirai.kmkcd;
#line 1156 "AD102_db.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 1156 "AD102_db.sqc"
      sqlasetdata(2,0,53,sql_setdlist,0L,0L);
    }
#line 1156 "AD102_db.sqc"
  sqlacall((unsigned short)24,12,2,0,0L);
#line 1156 "AD102_db.sqc"
  sqlastop(0L);
}

#line 1156 "AD102_db.sqc"


		/* SQLCODE */
		// edit sqlcacode for LogOut errcode
		sprintf( G_err, "%d", sqlca.sqlcode );

		// DEBUG
		sprintf( G_msg, "UPDATE irai michakusaisei jidohassei: "
			"utkymd[%s]irino[%s]kmkcd[%s]",
			hirai.utkymd, hirai.irino, hirai.kmkcd );
		LogOut( LT_DBG, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		if (sqlca.sqlcode == 0) {		/* OK */
			ret = RTN_OK;
		} else {
			if( sqlca.sqlcode == -911 ){        // LOCK
				switch( sqlca.sqlerrd[2] ){
				case     2 :
					strcpy( G_msg, "�����Đ� ���������˗����(irai)�� "
						"UPDATE �� DEAD LOCK ���������܂����B" );
					break;
				case    68 :
                	strcpy( G_msg, "�����Đ� ���������˗����(irai)�� "
                    	"UPDATE �� TIMETOUT ���������܂����B" );
					break;
				default :
					strcpy( G_msg, "�����Đ� ���������˗����(irai)�� "
						"�s����������܂����B" );
					break;
				}
			} else {
				/* SQLCODE > 0 -> WARNING */
				/* SQLCODE < 0 -> ERROR */
				sprintf( G_msg,
				"�����Đ� ���������˗����(irai)�� UPDATE �Ɏ��s���܂����B"
					"��t��[%s]�˗���NO[%s]����CD[%s]",
					hirai.utkymd, hirai.irino, hirai.kmkcd );
			}
			EditCsvMsg( G_msg );
			LogOut( LT_ERR, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			ret=RTN_DBERR;
		}
	}


/*
EXEC SQL CLOSE miji_cur;
*/

{
#line 1200 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1200 "AD102_db.sqc"
  sqlacall((unsigned short)20,11,0,0,0L);
#line 1200 "AD102_db.sqc"
  sqlastop(0L);
}

#line 1200 "AD102_db.sqc"

    // ���O�o�͗p�L�[���ڐݒ�
    strcpy( G_utkymd,   hst_utkymd );
    strcpy( G_irino,    hst_irino );
    strcpy( G_kmkcd,    hst_kmkcd );
    G_zssdino=bupIri.zssdino;
		

//----------------------------------------------------------------------------
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FSelKanjyaZssdinoMax                                           */
/*  �@�\�T�v  �F���ҏ��D��������NO�@MAX�擾                                 */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _IRAI    *iri;   : �˗����                           */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �F�ȊO         �ُ�I��                                         */
/******************************************************************************/
int		SelKanjyaZssdinoMax( iri )
struct		_IRAI		*iri;			// �˗����
{
	int		ret;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* �֐�����	*/
	struct	sqlca	sqlca;

	/* ��������	*/
	strcpy( func_nm, "SelKanjyaZssdinoMax" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	strcpy( hst_utkymd,	iri->utkymd );
	strcpy( hst_irino,	iri->irino );
	hst_zssdino=0;
	ind_zssdino=0;


/*
EXEC SQL SELECT	MAX( zssdino )
	INTO	  :hst_zssdino	INDICATOR :ind_zssdino
	FROM	kanjya
	WHERE	utkymd	= :hst_utkymd
	AND		irino	= :hst_irino
	;
*/

{
#line 1244 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1244 "AD102_db.sqc"
  sqlaaloc(2,2,19,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 1244 "AD102_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1244 "AD102_db.sqc"
      sql_setdlist[0].sqldata = (void*)hst_utkymd;
#line 1244 "AD102_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1244 "AD102_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1244 "AD102_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_irino;
#line 1244 "AD102_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1244 "AD102_db.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 1244 "AD102_db.sqc"
  sqlaaloc(3,1,20,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 1244 "AD102_db.sqc"
      sql_setdlist[0].sqltype = 497; sql_setdlist[0].sqllen = 4;
#line 1244 "AD102_db.sqc"
      sql_setdlist[0].sqldata = (void*)&hst_zssdino;
#line 1244 "AD102_db.sqc"
      sql_setdlist[0].sqlind = &ind_zssdino;
#line 1244 "AD102_db.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 1244 "AD102_db.sqc"
  sqlacall((unsigned short)24,13,2,3,0L);
#line 1244 "AD102_db.sqc"
  sqlastop(0L);
}

#line 1244 "AD102_db.sqc"


	/* SQLCODE */
	// edit sqlcacode for LogOut errcode
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "SELECT MAX(zssdino) FROM kanjya : "
		"utkymd[%s]irino[%s] indicator[%d] max[%d]",
		iri->utkymd, iri->irino, ind_zssdino, hst_zssdino );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	// �W���ϐ��ɂ�锻�f
	if( ind_zssdino == 0 ) {
		ret = hst_zssdino;
	} else {
		if( sqlca.sqlcode != 0 ){
			sprintf( G_msg,
				"���ҏ��(kanjya)��MAX( ��������NO )�擾�Ɏ��s���܂����B"
				"BML��t�N����[%s]�˗���NO[%s] SELECT INDICATOR[%d]"
				,iri->utkymd, iri->irino, ind_zssdino );
			EditCsvMsg( G_msg );
			LogOut( LT_TRC, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		}
		ret=RTN_NG;
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

// 1.04 ADD STA =============================================================
/******************************************************************************/
/*  �� �� ��  �FSelCountJkmkmst                                               */
/*  �@�\�T�v  �F������������ �Ώی����J�E���g                                 */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fchar	utkymd[];	: 	BML��t��                             */
/*   ��Q���� �Fchar	irino[];	: 	�˗���No                              */
/*   ��R���� �Fchar	sriymd[];	: 	������                                */
/*  �o    ��  �F                                                              */
/*  ���A���  �FCOUNT����    ����I��                                         */
/*            �F0 ����       �ُ�I��                                         */
/******************************************************************************/
int		SelCountJkmkmst( utkymd, irino, sriymd )
char		utkymd[];	
char		irino[];	
char		sriymd[];	
{
	int		ret;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	struct	sqlca	sqlca;

	/* ��������	*/
	strcpy( func_nm, "SelCountJkmkmst" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	strcpy( hst_utkymd,	utkymd );
	strcpy( hst_irino,	irino );
	strcpy( hst_ymd,	sriymd );
	hst_cnt=0;
	ind_cnt=0;


/*
EXEC SQL SELECT	COUNT( distinct jkmkcd )
	INTO	:hst_cnt	INDICATOR :ind_cnt
	FROM	jdkmkmst 
	WHERE	( knsgrp, kmkcd ) IN
				( SELECT	knsgrp, kmkcd 
					FROM	irai
					WHERE	utkymd	= :hst_utkymd
					AND		irino	= :hst_irino
				)
	AND		( jknsgrp, jkmkcd ) NOT IN
				( SELECT	knsgrp, kmkcd 
					FROM	irai
					WHERE	utkymd	= :hst_utkymd
					AND		irino	= :hst_irino
				)
	AND		kaiymd	<= :hst_ymd
	AND		haiymd	>= :hst_ymd
	;
*/

{
#line 1323 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1323 "AD102_db.sqc"
  sqlaaloc(2,6,21,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 1323 "AD102_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1323 "AD102_db.sqc"
      sql_setdlist[0].sqldata = (void*)hst_utkymd;
#line 1323 "AD102_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1323 "AD102_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1323 "AD102_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_irino;
#line 1323 "AD102_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1323 "AD102_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 1323 "AD102_db.sqc"
      sql_setdlist[2].sqldata = (void*)hst_utkymd;
#line 1323 "AD102_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1323 "AD102_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 12;
#line 1323 "AD102_db.sqc"
      sql_setdlist[3].sqldata = (void*)hst_irino;
#line 1323 "AD102_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1323 "AD102_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 1323 "AD102_db.sqc"
      sql_setdlist[4].sqldata = (void*)hst_ymd;
#line 1323 "AD102_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1323 "AD102_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 1323 "AD102_db.sqc"
      sql_setdlist[5].sqldata = (void*)hst_ymd;
#line 1323 "AD102_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1323 "AD102_db.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 1323 "AD102_db.sqc"
  sqlaaloc(3,1,22,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 1323 "AD102_db.sqc"
      sql_setdlist[0].sqltype = 497; sql_setdlist[0].sqllen = 4;
#line 1323 "AD102_db.sqc"
      sql_setdlist[0].sqldata = (void*)&hst_cnt;
#line 1323 "AD102_db.sqc"
      sql_setdlist[0].sqlind = &ind_cnt;
#line 1323 "AD102_db.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 1323 "AD102_db.sqc"
  sqlacall((unsigned short)24,14,2,3,0L);
#line 1323 "AD102_db.sqc"
  sqlastop(0L);
}

#line 1323 "AD102_db.sqc"


	/* SQLCODE */
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "SELECT COUNT( kmkcd ) FROM jdkmkmst : "
		"utkymd[%s]irino[%s]ymd[%s] cnt[%d] indicator[%d]",
		utkymd, irino, sriymd, hst_cnt, ind_cnt );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	// �W���ϐ��ɂ�锻�f
	if( ind_cnt == 0 ) {
		// COUNT���ʂ�Ԃ��i0������j
		ret = hst_cnt;
	} else {
		sprintf( G_msg,
			"���������}�X�^(jdkmkmst)�̑Ώی����擾�Ɏ��s���܂����B"
			"���[%s]�˗���[%s]������[%s] SELECT INDICATOR[%d]"
			,utkymd, irino, sriymd, ind_cnt );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		ret=RTN_NG;
	}
	// DEBUG
	sprintf( G_msg, "JDKMKMST COUNT[%d]", ret );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FSelJidoirai                                                   */
/*  �@�\�T�v  �F���������˗����ڏ�� SELECT                                   */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  JIDOIRAI	pJir[];   : ���������˗����ڏ��          */
/*   ��Q���� �Fint		kensu;   : malloc����                                 */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		SelJidoirai( jdi, kensu )
struct		JIDOIRAI		*jdi;	
int			kensu;
{
	int		ret;
	int		i;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* �֐�����	*/
	struct	sqlca	sqlca;

	/* ��������	*/
	strcpy( func_nm, "SelJidoirai" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	memset( &hjdkmkmst,	'\0', sizeof( struct _JDKMKMST ));
	memset( &hkmkmst,	'\0', sizeof( struct _KMKMST ));
	memset( &hirai	,	'\0', sizeof( struct _IRAI ));
	strcpy( hirai.utkymd,	jdi[0].sIri.utkymd );
	strcpy( hirai.irino,	jdi[0].sIri.irino );
	strcpy( hirai.sriymd,	jdi[0].sIri.sriymd );


/*
EXEC SQL DECLARE    jdi_cur CURSOR  FOR
	SELECT	jido.*
			, km.kmkrs 
			, km.oyakmkcd
			, km.smpcd
			, km.fkbnkkb
			, irai.*
	FROM
		( SELECT	knsgrp, kmkcd , jknsgrp , jkmkcd , hhkumflg
			FROM	jdkmkmst
			WHERE	( knsgrp, kmkcd ) IN
						( SELECT	knsgrp, kmkcd 
							FROM	irai
							WHERE	utkymd	= :hirai.utkymd
							AND		irino	= :hirai.irino
						)
			AND		( jknsgrp, jkmkcd ) NOT IN
						( SELECT	knsgrp, kmkcd 
							FROM	irai
							WHERE	utkymd	= :hirai.utkymd
							AND		irino	= :hirai.irino
						)
			AND		kaiymd	<= :hirai.sriymd
			AND		haiymd	>= :hirai.sriymd
		) jido
		, kmkmst km
		, irai
	WHERE	irai.utkymd	= :hirai.utkymd
	AND		irai.irino	= :hirai.irino
	AND		irai.knsgrp	= jido.knsgrp
	AND		irai.kmkcd	= jido.kmkcd
	AND		jido.jknsgrp	= km.knsgrp
	AND		jido.jkmkcd	= km.kmkcd
	AND		km.kaiymd	<= :hirai.sriymd
	AND		km.haiymd	>= :hirai.sriymd
	ORDER BY jido.jknsgrp, jido.jkmkcd, irai.knsgrp, irai.kmkcd
	FOR	READ ONLY
	;
*/

#line 1424 "AD102_db.sqc"



/*
EXEC SQL OPEN jdi_cur;
*/

{
#line 1426 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1426 "AD102_db.sqc"
  sqlaaloc(2,10,23,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 1426 "AD102_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1426 "AD102_db.sqc"
      sql_setdlist[0].sqldata = (void*)hirai.utkymd;
#line 1426 "AD102_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1426 "AD102_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1426 "AD102_db.sqc"
      sql_setdlist[1].sqldata = (void*)hirai.irino;
#line 1426 "AD102_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1426 "AD102_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 1426 "AD102_db.sqc"
      sql_setdlist[2].sqldata = (void*)hirai.utkymd;
#line 1426 "AD102_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1426 "AD102_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 12;
#line 1426 "AD102_db.sqc"
      sql_setdlist[3].sqldata = (void*)hirai.irino;
#line 1426 "AD102_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1426 "AD102_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 1426 "AD102_db.sqc"
      sql_setdlist[4].sqldata = (void*)hirai.sriymd;
#line 1426 "AD102_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1426 "AD102_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 1426 "AD102_db.sqc"
      sql_setdlist[5].sqldata = (void*)hirai.sriymd;
#line 1426 "AD102_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1426 "AD102_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 1426 "AD102_db.sqc"
      sql_setdlist[6].sqldata = (void*)hirai.utkymd;
#line 1426 "AD102_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1426 "AD102_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 12;
#line 1426 "AD102_db.sqc"
      sql_setdlist[7].sqldata = (void*)hirai.irino;
#line 1426 "AD102_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1426 "AD102_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 1426 "AD102_db.sqc"
      sql_setdlist[8].sqldata = (void*)hirai.sriymd;
#line 1426 "AD102_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1426 "AD102_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 1426 "AD102_db.sqc"
      sql_setdlist[9].sqldata = (void*)hirai.sriymd;
#line 1426 "AD102_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1426 "AD102_db.sqc"
      sqlasetdata(2,0,10,sql_setdlist,0L,0L);
    }
#line 1426 "AD102_db.sqc"
  sqlacall((unsigned short)26,15,2,0,0L);
#line 1426 "AD102_db.sqc"
  sqlastop(0L);
}

#line 1426 "AD102_db.sqc"


	i=0;

	while( sqlca.sqlcode == 0 ){
		
/*
EXEC SQL    FETCH   jdi_cur
					INTO	  :hjdkmkmst
							, :hkmkmst.kmkrs
							, :hkmkmst.oyakmkcd
							, :hkmkmst.smpcd
							, :hkmkmst.fkbnkkb
							, :hirai
					;
*/

{
#line 1438 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1438 "AD102_db.sqc"
  sqlaaloc(3,58,24,0L);
    {
      struct sqla_setdata_list sql_setdlist[58];
#line 1438 "AD102_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 1438 "AD102_db.sqc"
      sql_setdlist[0].sqldata = (void*)hjdkmkmst.knsgrp;
#line 1438 "AD102_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 1438 "AD102_db.sqc"
      sql_setdlist[1].sqldata = (void*)hjdkmkmst.kmkcd;
#line 1438 "AD102_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 17;
#line 1438 "AD102_db.sqc"
      sql_setdlist[2].sqldata = (void*)hjdkmkmst.jknsgrp;
#line 1438 "AD102_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 1438 "AD102_db.sqc"
      sql_setdlist[3].sqldata = (void*)hjdkmkmst.jkmkcd;
#line 1438 "AD102_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 2;
#line 1438 "AD102_db.sqc"
      sql_setdlist[4].sqldata = (void*)hjdkmkmst.hhkumflg;
#line 1438 "AD102_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 17;
#line 1438 "AD102_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkmkmst.kmkrs;
#line 1438 "AD102_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 1438 "AD102_db.sqc"
      sql_setdlist[6].sqldata = (void*)hkmkmst.oyakmkcd;
#line 1438 "AD102_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 8;
#line 1438 "AD102_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkmkmst.smpcd;
#line 1438 "AD102_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 2;
#line 1438 "AD102_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkmkmst.fkbnkkb;
#line 1438 "AD102_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 1438 "AD102_db.sqc"
      sql_setdlist[9].sqldata = (void*)hirai.utkymd;
#line 1438 "AD102_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 12;
#line 1438 "AD102_db.sqc"
      sql_setdlist[10].sqldata = (void*)hirai.irino;
#line 1438 "AD102_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 2;
#line 1438 "AD102_db.sqc"
      sql_setdlist[11].sqldata = (void*)hirai.iriketflg;
#line 1438 "AD102_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 1438 "AD102_db.sqc"
      sql_setdlist[12].sqldata = (void*)&hirai.zssdino;
#line 1438 "AD102_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 17;
#line 1438 "AD102_db.sqc"
      sql_setdlist[13].sqldata = (void*)hirai.knsgrp;
#line 1438 "AD102_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 8;
#line 1438 "AD102_db.sqc"
      sql_setdlist[14].sqldata = (void*)hirai.kmkcd;
#line 1438 "AD102_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 2;
#line 1438 "AD102_db.sqc"
      sql_setdlist[15].sqldata = (void*)hirai.irihsmkbn;
#line 1438 "AD102_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 2;
#line 1438 "AD102_db.sqc"
      sql_setdlist[16].sqldata = (void*)hirai.irikbn;
#line 1438 "AD102_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 2;
#line 1438 "AD102_db.sqc"
      sql_setdlist[17].sqldata = (void*)hirai.ksktkbn;
#line 1438 "AD102_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 11;
#line 1438 "AD102_db.sqc"
      sql_setdlist[18].sqldata = (void*)hirai.sriymd;
#line 1438 "AD102_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 14;
#line 1438 "AD102_db.sqc"
      sql_setdlist[19].sqldata = (void*)hirai.kntno;
#line 1438 "AD102_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 2;
#line 1438 "AD102_db.sqc"
      sql_setdlist[20].sqldata = (void*)hirai.kntketflg;
#line 1438 "AD102_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 5;
#line 1438 "AD102_db.sqc"
      sql_setdlist[21].sqldata = (void*)hirai.chkmj;
#line 1438 "AD102_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 5;
#line 1438 "AD102_db.sqc"
      sql_setdlist[22].sqldata = (void*)hirai.stsrcd;
#line 1438 "AD102_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 17;
#line 1438 "AD102_db.sqc"
      sql_setdlist[23].sqldata = (void*)hirai.kmkrs;
#line 1438 "AD102_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 8;
#line 1438 "AD102_db.sqc"
      sql_setdlist[24].sqldata = (void*)hirai.oyakmkcd;
#line 1438 "AD102_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 8;
#line 1438 "AD102_db.sqc"
      sql_setdlist[25].sqldata = (void*)hirai.smpcd;
#line 1438 "AD102_db.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 8;
#line 1438 "AD102_db.sqc"
      sql_setdlist[26].sqldata = (void*)hirai.setkmkcd;
#line 1438 "AD102_db.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 2;
#line 1438 "AD102_db.sqc"
      sql_setdlist[27].sqldata = (void*)hirai.srinycd;
#line 1438 "AD102_db.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 3;
#line 1438 "AD102_db.sqc"
      sql_setdlist[28].sqldata = (void*)hirai.seccd;
#line 1438 "AD102_db.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 2;
#line 1438 "AD102_db.sqc"
      sql_setdlist[29].sqldata = (void*)hirai.skchkflg;
#line 1438 "AD102_db.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 2;
#line 1438 "AD102_db.sqc"
      sql_setdlist[30].sqldata = (void*)hirai.bkfkkbn;
#line 1438 "AD102_db.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 3;
#line 1438 "AD102_db.sqc"
      sql_setdlist[31].sqldata = (void*)hirai.ysnlbl;
#line 1438 "AD102_db.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 2;
#line 1438 "AD102_db.sqc"
      sql_setdlist[32].sqldata = (void*)hirai.skflg;
#line 1438 "AD102_db.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 2;
#line 1438 "AD102_db.sqc"
      sql_setdlist[33].sqldata = (void*)hirai.tkflg;
#line 1438 "AD102_db.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 2;
#line 1438 "AD102_db.sqc"
      sql_setdlist[34].sqldata = (void*)hirai.sjflg;
#line 1438 "AD102_db.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 2;
#line 1438 "AD102_db.sqc"
      sql_setdlist[35].sqldata = (void*)hirai.jktkflg;
#line 1438 "AD102_db.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 4;
#line 1438 "AD102_db.sqc"
      sql_setdlist[36].sqldata = (void*)hirai.kjno;
#line 1438 "AD102_db.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 2;
#line 1438 "AD102_db.sqc"
      sql_setdlist[37].sqldata = (void*)hirai.fkhkknohjkbn;
#line 1438 "AD102_db.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 4;
#line 1438 "AD102_db.sqc"
      sql_setdlist[38].sqldata = (void*)hirai.tbkjno;
#line 1438 "AD102_db.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 2;
#line 1438 "AD102_db.sqc"
      sql_setdlist[39].sqldata = (void*)hirai.tbkjflg;
#line 1438 "AD102_db.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 25;
#line 1438 "AD102_db.sqc"
      sql_setdlist[40].sqldata = (void*)hirai.htkfkhms;
#line 1438 "AD102_db.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 1438 "AD102_db.sqc"
      sql_setdlist[41].sqldata = (void*)hirai.tskflg;
#line 1438 "AD102_db.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 3;
#line 1438 "AD102_db.sqc"
      sql_setdlist[42].sqldata = (void*)hirai.tktflg;
#line 1438 "AD102_db.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 2;
#line 1438 "AD102_db.sqc"
      sql_setdlist[43].sqldata = (void*)hirai.bnckbn;
#line 1438 "AD102_db.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 2;
#line 1438 "AD102_db.sqc"
      sql_setdlist[44].sqldata = (void*)hirai.nbnckbn;
#line 1438 "AD102_db.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 11;
#line 1438 "AD102_db.sqc"
      sql_setdlist[45].sqldata = (void*)hirai.knskisyymd;
#line 1438 "AD102_db.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 11;
#line 1438 "AD102_db.sqc"
      sql_setdlist[46].sqldata = (void*)hirai.knskryymd;
#line 1438 "AD102_db.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 9;
#line 1438 "AD102_db.sqc"
      sql_setdlist[47].sqldata = (void*)hirai.knskrytme;
#line 1438 "AD102_db.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 2;
#line 1438 "AD102_db.sqc"
      sql_setdlist[48].sqldata = (void*)hirai.kkhkkflg;
#line 1438 "AD102_db.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 2;
#line 1438 "AD102_db.sqc"
      sql_setdlist[49].sqldata = (void*)hirai.kkiriflg;
#line 1438 "AD102_db.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[50].sqltype = 500; sql_setdlist[50].sqllen = 2;
#line 1438 "AD102_db.sqc"
      sql_setdlist[50].sqldata = (void*)&hirai.kkirilotno;
#line 1438 "AD102_db.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 5;
#line 1438 "AD102_db.sqc"
      sql_setdlist[51].sqldata = (void*)hirai.kktoutkid;
#line 1438 "AD102_db.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[52].sqltype = 500; sql_setdlist[52].sqllen = 2;
#line 1438 "AD102_db.sqc"
      sql_setdlist[52].sqldata = (void*)&hirai.knssu;
#line 1438 "AD102_db.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 2;
#line 1438 "AD102_db.sqc"
      sql_setdlist[53].sqldata = (void*)hirai.odrssflg;
#line 1438 "AD102_db.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 16;
#line 1438 "AD102_db.sqc"
      sql_setdlist[54].sqldata = (void*)hirai.ytiksbr;
#line 1438 "AD102_db.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 2;
#line 1438 "AD102_db.sqc"
      sql_setdlist[55].sqldata = (void*)hirai.hhkjkflg;
#line 1438 "AD102_db.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 27;
#line 1438 "AD102_db.sqc"
      sql_setdlist[56].sqldata = (void*)hirai.ksndh;
#line 1438 "AD102_db.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 27;
#line 1438 "AD102_db.sqc"
      sql_setdlist[57].sqldata = (void*)hirai.trkdh;
#line 1438 "AD102_db.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 1438 "AD102_db.sqc"
      sqlasetdata(3,0,58,sql_setdlist,0L,0L);
    }
#line 1438 "AD102_db.sqc"
  sqlacall((unsigned short)25,15,0,3,0L);
#line 1438 "AD102_db.sqc"
  sqlastop(0L);
}

#line 1438 "AD102_db.sqc"


		if( i >  kensu ){
			break;
		}

		// DEBUG
		sprintf( G_err, "%d", sqlca.sqlcode );
		sprintf( G_msg, "FETCH jirai: jkmk[%s]<= utkymd[%s]irino[%s]srimd[%s] "
			"kmk[%s], zno[%d] ken[%d] ", hjdkmkmst.jkmkcd, hirai.utkymd 
			,hirai.irino ,hirai.sriymd ,hirai.kmkcd ,hirai.zssdino, i);
		LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		// �����˗����ڂ��瓯�ꎩ���������ڂɊY������ꍇ�̍l��
		if( i > 0 ){
			if(( strcmp( hjdkmkmst.jknsgrp,	jdi[i-1].sJdm.jknsgrp ) == 0 )
			 &&( strcmp( hjdkmkmst.jkmkcd,	jdi[i-1].sJdm.jkmkcd ) == 0 )){
				continue;
			}
		}

		memcpy( &( jdi[i].sJdm ),	&hjdkmkmst,	sizeof( struct _JDKMKMST ));
		memcpy( &( jdi[i].sKmk ),	&hkmkmst,	sizeof( struct _KMKMST ));
		memcpy( &( jdi[i].sIri ),	&hirai,		sizeof( struct _IRAI ));

		// INDEX UP
		i++;
	}

	if ( sqlca.sqlcode == 0 ) {
		// FETCH OK BUT CONTINUE �Ώۃf�[�^�̏ꍇ�̍l��
			ret = RTN_OK;
	} else if ( sqlca.sqlcode == 100 ) {	// NOT FOUND or END
		if( i > 0 ){
			ret = RTN_OK;
		} else {
			sprintf( G_msg,
				"���������˗������擾�ł��܂���B"
				"UKTYMD[%s] IRINO[%s] SRIYMD[%s]"
				, jdi[0].sIri.utkymd ,jdi[0].sIri.irino ,jdi[0].sIri.sriymd );
			EditCsvMsg( G_msg );
			LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			ret = RTN_NG;
		}
	} else {
		/* SQLCODE > 0 -> WARNING */
		/* SQLCODE < 0 -> ERROR */
		sprintf( G_msg,
			"���������˗����FETCH �ŕs����������܂����B"
			"UKTYMD[%s] IRINO[%s] SRIYMD[%s]"
			, jdi[0].sIri.utkymd ,jdi[0].sIri.irino ,jdi[0].sIri.sriymd );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			 
		ret=RTN_DBERR;
	}

/*
EXEC SQL    CLOSE   jdi_cur;
*/

{
#line 1494 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1494 "AD102_db.sqc"
  sqlacall((unsigned short)20,15,0,0,0L);
#line 1494 "AD102_db.sqc"
  sqlastop(0L);
}

#line 1494 "AD102_db.sqc"


	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}
// 1.04 ADD END =============================================================
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
#line 1512 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1512 "AD102_db.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 1512 "AD102_db.sqc"
  sqlastop(0L);
}

#line 1512 "AD102_db.sqc"


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
#line 1538 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1538 "AD102_db.sqc"
  sqlacall((unsigned short)28,0,0,0,0L);
#line 1538 "AD102_db.sqc"
  sqlastop(0L);
}

#line 1538 "AD102_db.sqc"


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

#line 1565 "AD102_db.sqc"

	char	dbAlias[15];
	char	user[129];
	char	pswd[15];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 1569 "AD102_db.sqc"


	strcpy( func_nm, "Ydbconn" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	strcpy( dbAlias,	stcPRM.dbp_dbAlias );
	strcpy( user,		stcPRM.dbp_user );
	strcpy( pswd,		stcPRM.dbp_pswd );

	
/*
EXEC SQL CONNECT TO :dbAlias USER :user USING :pswd;
*/

{
#line 1578 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1578 "AD102_db.sqc"
  sqlaaloc(2,3,25,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 1578 "AD102_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 15;
#line 1578 "AD102_db.sqc"
      sql_setdlist[0].sqldata = (void*)dbAlias;
#line 1578 "AD102_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1578 "AD102_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 129;
#line 1578 "AD102_db.sqc"
      sql_setdlist[1].sqldata = (void*)user;
#line 1578 "AD102_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1578 "AD102_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 15;
#line 1578 "AD102_db.sqc"
      sql_setdlist[2].sqldata = (void*)pswd;
#line 1578 "AD102_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1578 "AD102_db.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 1578 "AD102_db.sqc"
  sqlacall((unsigned short)29,5,2,0,0L);
#line 1578 "AD102_db.sqc"
  sqlastop(0L);
}

#line 1578 "AD102_db.sqc"


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
#line 1611 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1611 "AD102_db.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 1611 "AD102_db.sqc"
  sqlastop(0L);
}

#line 1611 "AD102_db.sqc"


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
#line 1622 "AD102_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1622 "AD102_db.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 1622 "AD102_db.sqc"
  sqlastop(0L);
}

#line 1622 "AD102_db.sqc"


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
