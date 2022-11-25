static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,55,65,82,118,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,65,68,50,48,50,95,68,66,0,0,0,0,0,0,0,0,
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


#line 1 "AD202_db.sqc"
/******************************************************************************/
/*   �a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/*   �V�X�e�����F������V�X�e��                                               */
/*   �t�@�C�����FAD202_db.sqc                                                 */
/*   �T      �v�F�c�a�A�N�Z�X                                                 */
/*   OS        �FSUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   ����      �FDB2/C                                                        */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/08     INTEC.INC      CREATE                             */
/*  1.01     2006/05/01     INTEC.INC      SJIS,���ڒǉ�(�e�{��,�o�^����)�Ή� */
/*  2.00     2009/01/06     Merits K.Ameno �{�݃R�[�h���� �ʐM�d�l�ύX�Ή�    */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include	<stdio.h>
#include 	<stdlib.h>
#include 	<string.h>
#include	<sqlca.h>
#include	"AD202.h"


/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 27 "AD202_db.sqc"


/*
EXEC SQL INCLUDE 'tagAD202.h';
*/

#line 1 "/home/kea00sys/appl/src/irai/AD202/tagAD202.h"
/******************************************************************************/
/*   �a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/*   �V�X�e�����F������V�X�e��                                               */
/*   �t�@�C�����FtagAD103.h                                                   */
/*   �T      �v�F���ҏ��e�[�u���\���̒�`                                   */
/*   ���L����  �FDB2�̃z�X�g�ϐ��ɂ��g�p���邽��typedef�g�p�s��               */
/*               �܂�struct�̍Ō�ŕϐ�����錾���邱��                       */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/08     INTEC.INC      CREATE                             */
/*  1.01     2006/05/01     INTEC.INC      SJIS,���ڒǉ�(�e�{��,�o�^����)�Ή� */
/******************************************************************************/
#ifndef _TAGAD103_H
#define _TAGAD103_H

/******************************************************************************/
/* �f�[�^�\���̒�`                                                           */
/******************************************************************************/
// <<   ���ҏ��e�[�u��      >>
struct	_KANJYA {
	char	utkymd[10+1];		// 1 �a�l�k��t�N���� 
	char	irino[11+1];		// 2 �˗����m�� 
	char	iriketflg[1+1];		// 3 �˗����m�������t���O 
	short	zssdino;			// 4 ��������m�� 
	char	sstcd[7+1];			// 5 �{�݃R�[�h 
	char	subsstcd[4+1];		// 6 �T�u�{�݃R�[�h 
	char	cdkbn1[2+1];		// 7 �J�[�h�敪1 
	char	cdkbn2[2+1];		// 8 �J�[�h�敪2 
	char	irimkey[40+1];		// 9 �˗����L�[ 
	char	srkcd[3+1];			// 10 �f�ÉȃR�[�h 
	char	srknm[30+1];		// 11 �f�ÉȖ� 
	char	tticd[8+1];			// 12 �S����R�[�h 
	char	ttinm[40+1];		// 13 �S���㖼 
	char	gpcd[8+1];			// 14 �厡��R�[�h 
	char	gpnm[40+1];			// 15 �厡�㖼 
	char	skicd[8+1];			// 16 �Љ��R�[�h 
	char	skinm[40+1];		// 17 �Љ�㖼 
	char	krtno[40+1];		// 18 �J���e�m��          
	char	knjid[15+1];		// 19 ���҂h�c 
	char	knjnmn[60+1];		// 20 ���Җ��i�J�i�j 
	char	knjnmk[30+1];		// 21 ���Җ��i�����j 
	char	knjnmkey[60+1];		// 22 ���Җ��L�[ 
	char	sc[5+1];			// 23 �g��  
	char	tj[5+1];			// 24 �̏d  
	char	tjtni[1+1];			// 25 �̏d�敪 
	char	sbtkbn[1+1];		// 26 ���ʋ敪 
	char	birthday[8+1];		// 27 ���N����  
	char	birthdaykbn[1+1];	// 28 ���N�����敪 
	char	age[3+1];			// 29 �N��  
	char	agekbn[1+1];		// 30 �N��敪 
	char	btcd[10+1];			// 31 �a���R�[�h 
	char	btnm[30+1];			// 32 �a���� 
	char	utkcmtcd1[2+1];		// 33 ��t�R�����g1  
	char	utkcmtcd2[2+1];		// 34 ��t�R�����g2  
	char	utkcmtcd3[2+1];		// 35 ��t�R�����g3  
	char	utkcmtfr1[70+1];	// 36 ��t�R�����g�t���[1  
	char	utkcmtfr2[70+1];	// 37 ��t�R�����g�t���[2  
	char	utkcmtfrflg[1+1];	// 38 ��t�R�����g�t���[�t���O 
	char	ngkbn[1+1];			// 39 ���@�O���敪           
	char	nsssu[2+1];			// 40 �D�P�T��  
	char	hkncd[1+1];			// 41 �ی��R�[�h 
	char	ktshsu[2+1];		// 42 ���̑��{�� 
	char	iniriymd[10+1];		// 43 �@���˗��� 
	char	zssflg[1+1];		// 44 �����C���t���O 
	char	kkiriflg[1+1];		// 45 �ً}�˗��t���O 
	char	hknskbn[1+1];		// 46 �񌟍��敪 
	char	utkkbn[1+1];		// 47 ��t�敪 
	char	nekbn[1+1];			// 48 �m�d�敪 
	char	inknskbn[1+1];		// 49 �@�������敪 
	char	utkjkkbn[1+1];		// 50 ��t��ԋ敪 
	char	krflg[1+1];			// 51 �����t���O 
	char	fdhhkkflg[1+1];		// 52 �e�c��񍐃t���O 
	char	utkdh[8+1];			// 53 ��t���� 
	char	mutkymd[10+1];		// 54 ���a�l�k��t�� 
	char	mirino[11+1];		// 55 ���˗����m�� 
	char	knsjslbcd1[3+1];	// 56 �������{���{�R�[�h�P 
	char	knsjslbcd2[3+1];	// 57 �������{���{�R�[�h�Q 
	char	knsjslbcd3[3+1];	// 58 �������{���{�R�[�h�R 
	char	knsjslbcd4[3+1];	// 59 �������{���{�R�[�h�S 
	char	ymhkkflg[1+1];		// 60 �������񍐃t���O 
	char	hkkkbdh[8+1];		// 61 �񍐊�]���� 
	char	ecd[3+1];			// 62 �c�Ə��R�[�h 
	char	shcd[2+1];			// 63 �W�z�R�[�h 
	char	sstssnmj[40+1];		// 64 �{�ݖ��������� 
	char	sstssnmn[40+1];		// 65 �{�ݖ��������́i�J�i�j 
	char	sstrsj[20+1];		// 66 �{�ݖ����� 
	char	sstrsn[20+1];		// 67 �{�ݖ����́i�J�i�j 
	char	sstsbt[2+1];		// 68 �{�ݎ�� 
	char	ttsstflg[1+1];		// 69 ����{�݃t���O 
	char	rucd[2+1];			// 70 ���R�R�[�h 
	short	irikmksu;			// 71 �˗����ڐ� 
	char	bmskn[50+1];		// 72 �a���y�я��� 
	char	irinrsbt[2+1];		// 73 �˗����͎�� 
	char	irihsmkbn[1+1];		// 74 �˗��������敪 
	char	caresstflg[1+1];	// 75 ���ʒ��ӎ{�݃t���O 
	char	tktyflg[1+1];		// 76 �����g���t���O 
	char	apkntino[13+1];		// 77 AUTO-P���̂m�� 
	char	sdnm[20+1];			// 78 �f�f�� 
	char	bko1[20+1];			// 79 ���l�P 
	char	bko2[20+1];			// 80 ���l�Q 
	char	bko3[20+1];			// 81 ���l�R 
	char	zstrdh[26+1];		// 82 �����o�^���� 
	char	zsssdh[26+1];		// 83 �����C������ 
	char	stlzsssdh[26+1];	// 84 �T�e���C�g�������C������ 
	char	stlzsssip[15+1];	// 85 �T�e���C�g�������C���[��IP 
	char	stlzssssyaid[8+1];	// 86 �T�e���C�g�������C�����͎� 
	char	ksndh[26+1];		// 87 ���X�V���� 
	char	oyasstcd[7+1];		// 1.01 ADD	88 �{�݃R�[�h 
	char	trkdh[26+1];		// 1.01 ADD	89 ���X�V���� 
} hkanjya;	

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
	char	trkdh[26+1];		// 1.01 ADD	49 ���X�V���� 
} hirai;	

/******************************************************************************/
/* �}�X�^�\���̒�`                                                           */
/******************************************************************************/
// <<   �V�X�e���Ǘ��}�X�^     >>
struct  _SYSKNRMST {
	char	kkkjsriymd[11];		// �ً}������N����
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

// <<   �ً}�˗����ڏ��\����  >>
struct _KNKYUMST {
    char    knsgrp[16+1];               // 1.04 O �����O���[�v
    char    kmkrs[16+1];                // O ���ڗ���
    char    oyakmkcd[7+1];              // O �e���ڃR�[�h
    char    fkbnkkb[1+1];               // O ���敉�׋敪
    char    seccd[2+1];                 // O �Z�N�V�����R�[�h
    char    smpcd[7+1];                 // O �T���v�����O�R�[�h
	char    kmkcd[7+1];                 // I ���ڃR�[�h
} hknkyumst;

// 1.04 ADD
// <<   ���ڃ}�X�^ >>
struct  _KMKMST {
    char    knsgrp[16+1];       // 1  �����O���[�v�R�[�h
    char    kmkcd[7+1];         // 2  ���ڃR�[�h
    char    kmkrs[16+1];        // 5  ���ڗ���
    char    smpcd[7+1];         // 11 �T���v�����O�R�[�h
    char    oyakmkcd[7+1];      // 12 �e���ڃR�[�h
    char    fkbnkkb[1+1];       // 19 ���ו���敪
    char    skflg[1+1];         // 0  �W���t���O
} hkmkmst;

// <<   �����������ڃ}�X�^ >>
struct  _JDKMKMST {
    char    knsgrp[16+1];       // 1  �����O���[�v�R�[�h
    char    kmkcd[7+1];         // 2  ���ڃR�[�h
    char    jknsgrp[16+1];      // 3  �������������O���[�v�R�[�h
    char    jkmkcd[7+1];        // 4  �����������ڃR�[�h
    char    hhkumflg[1+1];      // 5  �񍐗L���t���O
} hjdkmkmst;
// 1.04 END

#endif

#line 28 "AD202_db.sqc"

	char		hst_ymd[11];
	char		hst_kmkcd[8];
	sqlint32	hst_cnt;					// �}�X�^����
	short		ind_cnt;					// �W���ϐ�
	sqlint32	hst_kkirilotno;				// �ً}�˗����b�g�m��
    char        hst_utkymd[10+1];
    char        hst_irino[11+1];
    char        hst_errcd[8+1];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 37 "AD202_db.sqc"


/******************************************************************************/
/*  �� �� ��  �FSelSysknrmst                                                  */
/*  �@�\�T�v  �F�V�X�e���Ǘ��}�X�^ SELECT                                     */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _SYSKNRMST *knr;   : �V�X�e���Ǘ��}�X�^               */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		SelSysknrmst( knr )
struct		_SYSKNRMST	*knr;
{
	int		ret;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* �֐�����	*/
	struct	sqlca	sqlca;

	/* ��������	*/
	strcpy( func_nm, "SelSysknrmst" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	memset( &hsysknrmst,	'\0',	sizeof( struct _SYSKNRMST ));


/*
EXEC SQL SELECT	
		 	kkkjsriymd
			, nxirisriymd
			, iriendflg
	INTO	:hsysknrmst.kkkjsriymd
			, :hsysknrmst.nxirisriymd
			, :hsysknrmst.iriendflg
	FROM	sysknrmst
	;
*/

{
#line 70 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 70 "AD202_db.sqc"
  sqlaaloc(3,3,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 70 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 70 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hsysknrmst.kkkjsriymd;
#line 70 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 70 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 70 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hsysknrmst.nxirisriymd;
#line 70 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 70 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 70 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hsysknrmst.iriendflg;
#line 70 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 70 "AD202_db.sqc"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 70 "AD202_db.sqc"
  sqlacall((unsigned short)24,1,0,3,0L);
#line 70 "AD202_db.sqc"
  sqlastop(0L);
}

#line 70 "AD202_db.sqc"


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
	sprintf( G_msg, "SELECT kkkjsriymd FROM sysknrmst" );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if ( sqlca.sqlcode == 0 ) {		/* OK */
		memcpy( knr, &hsysknrmst, sizeof( struct _SYSKNRMST ));
		ret = RTN_OK;
	} else if ( sqlca.sqlcode == 100 ){	/* NOT FOUND */
		/* SQLCODE +100, SQLSTATE '02000' */
		sprintf( G_msg, "�V�X�e���Ǘ��}�X�^(kjnsriymd)�����݂��܂���B" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			
		ret=RTN_ZERO;
	} else {
		if( sqlca.sqlcode == -911 ){        // LOCK
			switch( sqlca.sqlerrd[2] ){
			case     2 :
				strcpy( G_msg, "�V�X�e���Ǘ��}�X�^(kjnsriymd) SELECT ��"
					"DEAD LOCK ���������܂����B" );
				break;
			case    68 :
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
#line 124 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 124 "AD202_db.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 124 "AD202_db.sqc"
  sqlastop(0L);
}

#line 124 "AD202_db.sqc"


	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FGetKnkyulot                                                   */
/*  �@�\�T�v  �F�ً}���b�g���擾                                            */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fchar	ymd[];	: 	�������                                */
/*   ��Q���� �Fint		lotno;	: 	���b�g�m��                                */
/*  �o    ��  �F                                                              */
/*  ���A���  �FCOUNT����    ����I��                                         */
/*            �F0 ����       �ُ�I��                                         */
/******************************************************************************/
int		GetKnkyulot( ymd, lotno )
char		ymd[];	
int			lotno;	
{
	int		ret;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	struct	sqlca	sqlca;

	/* ��������	*/
	strcpy( func_nm, "GetKnkyulot" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	strcpy( hst_ymd,	ymd );
	hst_kkirilotno = lotno;
	hst_cnt=0;
	ind_cnt=0;


/*
EXEC SQL SELECT	COUNT( seccd )
	INTO	:hst_cnt	INDICATOR :ind_cnt
	FROM	knkyulot 
	WHERE	knskisymd	= :hst_ymd
	AND		seccd		in ( SELECT seccd FROM secmst )
	AND		kkirilotno	= :hst_kkirilotno
	;
*/

{
#line 164 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 164 "AD202_db.sqc"
  sqlaaloc(2,2,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 164 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 164 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hst_ymd;
#line 164 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 164 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 164 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)&hst_kkirilotno;
#line 164 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 164 "AD202_db.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 164 "AD202_db.sqc"
  sqlaaloc(3,1,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 164 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 497; sql_setdlist[0].sqllen = 4;
#line 164 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)&hst_cnt;
#line 164 "AD202_db.sqc"
      sql_setdlist[0].sqlind = &ind_cnt;
#line 164 "AD202_db.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 164 "AD202_db.sqc"
  sqlacall((unsigned short)24,2,2,3,0L);
#line 164 "AD202_db.sqc"
  sqlastop(0L);
}

#line 164 "AD202_db.sqc"


	/* SQLCODE */
	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "SELECT COUNT( seccd ) FROM knkyulot : "
		"ymd[%s] lot[%d] cnt[%d] indicator[%d]",
		ymd, lotno, hst_cnt, ind_cnt );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	// �W���ϐ��ɂ�锻�f
	if( ind_cnt == 0 ) {
		// COUNT���ʂ�Ԃ��i0������j
		ret = hst_cnt;
	} else {
		sprintf( G_msg,
			"�ً}���b�g���(knkyulot)�̌����擾�Ɏ��s���܂����B"
			"�ً}��t��[%s] SELECT INDICATOR[%d]"
			,ymd, ind_cnt );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		ret=RTN_NG;
	}
	// DEBUG
	sprintf( G_msg, "KNKYULOT COUNT[%d]", ret );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

//	1TRANSACTION���ŌĂԂ��߃R�����g��
//EXEC SQL COMMIT;

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FInsKnkyulot                                                   */
/*  �@�\�T�v  �F�ً}���b�gNO�̓o�^                                            */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fchar	ymd[];   : ���                                     */
/*   ��Q���� �Fint		lotno;	: 	���b�g�m��                                */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		InsKnkyulot( ymd, lotno )
char		ymd[];	
int			lotno;
{
	int		i;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* �֐�����	*/
	struct	sqlca	sqlca;

	/* ��������	*/
	strcpy( func_nm, "InsKnkyulot" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	strcpy( hst_ymd,	ymd );
	hst_kkirilotno = lotno;

	// �o�^�����˗����̃Z�N�V�����R�[�h�����p�^�[��

/*
EXEC SQL	INSERT	INTO	knkyulot
	SELECT	:hst_ymd
			, iri.seccd
			, :hst_kkirilotno
			, CURRENT TIMESTAMP
			, '1000-01-01 00:00:01'
			, CURRENT TIMESTAMP
			, ' '							-- errcd
			, '0'							-- almflg
	FROM	(	SELECT	DISTINCT seccd 
				FROM	irai
				WHERE	utkymd		= :hst_ymd
				AND		kkirilotno	= :hst_kkirilotno
			) iri
	;
*/

{
#line 244 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 244 "AD202_db.sqc"
  sqlaaloc(2,4,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 244 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 244 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hst_ymd;
#line 244 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 244 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 244 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)&hst_kkirilotno;
#line 244 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 244 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 244 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hst_ymd;
#line 244 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 244 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 244 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)&hst_kkirilotno;
#line 244 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 244 "AD202_db.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 244 "AD202_db.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 244 "AD202_db.sqc"
  sqlastop(0L);
}

#line 244 "AD202_db.sqc"


/*============================= �Z�N�V�����}�X�^�����p�^�[��
	SELECT	:hst_ymd
			, seccd
			, :hst_kkirilotno
			, CURRENT TIMESTAMP
			, '1000-01-01 00:00:01'
			, CURRENT TIMESTAMP
	FROM	secmst
	;
====================================== */

	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "INSERT knkyulot : lotno[%d] ymd[%s]", lotno, ymd );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if ( sqlca.sqlcode != 0 ) {		/* SQL���sOK�ȊO�H */
		/* WARNING LOG */
		sprintf( G_msg,
			"�ً}���b�gNO(knkyulot)�� INSERT �Ɏ��s���܂����B"
			"��t��[%s]LOTNO[%d]"
			,ymd, lotno );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__ );
	}
	return( sqlca.sqlcode );	/* SQL�R�[�h���Ăяo�����ɕԂ� */
}

/******************************************************************************/
/*  �� �� ��  �FUpdKnkyulot                                                   */
/*  �@�\�T�v  �F�ً}���b�g���D���b�gNO=0�̃G���[�R�[�h�ݒ�                  */
/*  ��    ��  �F                                                              */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/*  ���L����  �F                                                              */
/******************************************************************************/
int		UpdKnkyulot( errcd )
char		errcd[];					// 	�G���[�R�[�h
{
	struct	sqlca	sqlca;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* �֐�����	*/
	int		ret;

	/* ��������	*/
	strcpy( func_nm, "UpdKnkyulot" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̍��ڃZ�b�g	*/
	strcpy( hst_ymd,	stcPRM.myp_kjnymd );
	strcpy( hst_errcd,	errcd );


/*
EXEC SQL UPDATE	Knkyulot	
	SET		errcd		= :hst_errcd
			,almflg		= '0'
			,ksndh		= CURRENT TIMESTAMP
	WHERE	knskisymd	= :hst_ymd
	AND		kkirilotno	= 0
	;
*/

{
#line 308 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 308 "AD202_db.sqc"
  sqlaaloc(2,2,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 308 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 9;
#line 308 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hst_errcd;
#line 308 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 308 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 308 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_ymd;
#line 308 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 308 "AD202_db.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 308 "AD202_db.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 308 "AD202_db.sqc"
  sqlastop(0L);
}

#line 308 "AD202_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf(G_msg,"UPDATE Knkyulot : errcd[%s]ymd[%s]",hst_errcd,hst_ymd );
	LogOut( LT_DBG, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if (sqlca.sqlcode == 0) {		/* OK */
		ret = RTN_OK;
	} else {
		if( sqlca.sqlcode == -911 ){		// LOCK
			switch( sqlca.sqlerrd[2] ){
			case	 2 :
				strcpy( G_msg, "�ً}���b�g���(Knkyulot) UPDATE ��"
					"DEAD LOCK ���������܂����B" );
				break;
			case	68 :
				strcpy( G_msg, "�ً}���b�g���(Knkyulot) UPDATE ��"
					"TIMETOUT ���������܂����B" );
				break;
			default :
				sprintf( G_msg, "�ً}���b�g���(Knkyulot) UPDATE ��"
					"�s����������܂����B" );
				break;
			}
		} else {
			/* SQLCODE > 0 -> WARNING */
			/* SQLCODE < 0 -> ERROR */
			sprintf( G_msg,
				"�ً}���b�g���(Knkyulot)�˗�END���� UPDATE ��"
				"���s���܂����B�ً}������N����[%s] LOTNO=0"
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
/*  �� �� ��  �FSelKinqKomokmst                                               */
/*  �@�\�T�v  �F�ً}�Ή����ڏ�� SELECT                                       */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  KOMST    *kom;   :�ً}�Ή����ڏ��                    */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
//int		SelKinqKomokmst( kom )
int		SelKinqKomokmst( kom, skflg )
struct		KOMST		*kom;			/* �ً}�Ή����ڏ�� */
char		skflg[];
{
	int		ret;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* �֐�����	*/
	struct	sqlca	sqlca;

	/* ��������	*/
	strcpy( func_nm, "SelKinqKomokmst" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	memset( &hknkyumst,			'\0', sizeof( struct _KNKYUMST ));
	strcpy( hknkyumst.kmkcd,	kom->kmkcd );
	strcpy( hst_ymd,			stcPRM.myp_kjnymd );

/* 1.04 �����O���[�v���擾
EXEC SQL SELECT	
			kinq.smpcd
			, kinq.seccd
			, kom.kmkrs
			, kom.oyakmkcd
			, kom.fkbnkkb
	INTO	  :hknkyumst.smpcd
		  	, :hknkyumst.seccd
			, :hknkyumst.kmkrs
			, :hknkyumst.oyakmkcd
		  	, :hknkyumst.fkbnkkb
	FROM	kmkmst kom, kinkmmst kinq
	WHERE	kinq.kmkcd		=  :hknkyumst.kmkcd
	AND		kinq.kmkcd		=	kom.kmkcd
	AND		kinq.smpcd		=	kom.smpcd
	AND		kinq.kaiymd		<= :hst_ymd
	AND		kinq.haiymd		>= :hst_ymd
	AND		kom.kaiymd		<= :hst_ymd
	AND		kom.haiymd		>= :hst_ymd
	;
*/
   // �W���t���O�ɂ��Ώی����O���[�v��ʂ̔��f
    if( skflg[0] == '1' ){              // �W��

/*
EXEC SQL SELECT		q.smpcd
					, q.seccd
					, m.knsgrp
					, m.kmkrs
					, m.oyakmkcd
					, m.fkbnkkb
			INTO	  :hknkyumst.smpcd
					, :hknkyumst.seccd
					, :hknkyumst.knsgrp
					, :hknkyumst.kmkrs
					, :hknkyumst.oyakmkcd
					, :hknkyumst.fkbnkkb
			FROM	knsgmst g
					, kmkmst m
					, kinkmmst q
			WHERE	q.kmkcd		=  :hknkyumst.kmkcd
			AND		q.kmkcd		=	m.kmkcd
			AND		q.smpcd		=	m.smpcd
			AND		q.kaiymd	<= :hst_ymd
			AND		q.haiymd	>= :hst_ymd
			AND		m.kaiymd	<= :hst_ymd
			AND		m.haiymd	>= :hst_ymd
			AND     m.knsgrp   =   g.knsgrp
			AND     g.knssbt   =   'S'
			AND     g.kaiymd   <= :hst_ymd
			AND     g.haiymd   >= :hst_ymd
			ORDER BY m.knsgrp
			FETCH FIRST 1 ROWS ONLY
		;
*/

{
#line 432 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 432 "AD202_db.sqc"
  sqlaaloc(2,7,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 432 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 432 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hknkyumst.kmkcd;
#line 432 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 432 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_ymd;
#line 432 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 432 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hst_ymd;
#line 432 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 432 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)hst_ymd;
#line 432 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 432 "AD202_db.sqc"
      sql_setdlist[4].sqldata = (void*)hst_ymd;
#line 432 "AD202_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 432 "AD202_db.sqc"
      sql_setdlist[5].sqldata = (void*)hst_ymd;
#line 432 "AD202_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 432 "AD202_db.sqc"
      sql_setdlist[6].sqldata = (void*)hst_ymd;
#line 432 "AD202_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 432 "AD202_db.sqc"
  sqlaaloc(3,6,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 432 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 432 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hknkyumst.smpcd;
#line 432 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 432 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hknkyumst.seccd;
#line 432 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 17;
#line 432 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hknkyumst.knsgrp;
#line 432 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 432 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)hknkyumst.kmkrs;
#line 432 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 432 "AD202_db.sqc"
      sql_setdlist[4].sqldata = (void*)hknkyumst.oyakmkcd;
#line 432 "AD202_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 2;
#line 432 "AD202_db.sqc"
      sql_setdlist[5].sqldata = (void*)hknkyumst.fkbnkkb;
#line 432 "AD202_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 432 "AD202_db.sqc"
      sqlasetdata(3,0,6,sql_setdlist,0L,0L);
    }
#line 432 "AD202_db.sqc"
  sqlacall((unsigned short)24,5,2,3,0L);
#line 432 "AD202_db.sqc"
  sqlastop(0L);
}

#line 432 "AD202_db.sqc"

	} else {					// �W���ȊO

/*
EXEC SQL SELECT		q.smpcd
					, q.seccd
					, m.knsgrp
					, m.kmkrs
					, m.oyakmkcd
					, m.fkbnkkb
			INTO	  :hknkyumst.smpcd
					, :hknkyumst.seccd
					, :hknkyumst.knsgrp
					, :hknkyumst.kmkrs
					, :hknkyumst.oyakmkcd
					, :hknkyumst.fkbnkkb
			FROM	knsgmst g
					, kmkmst m
					, kinkmmst q
			WHERE	q.kmkcd		=  :hknkyumst.kmkcd
			AND		q.kmkcd		=	m.kmkcd
			AND		q.smpcd		=	m.smpcd
			AND		q.kaiymd	<= :hst_ymd
			AND		q.haiymd	>= :hst_ymd
			AND		m.kaiymd	<= :hst_ymd
			AND		m.haiymd	>= :hst_ymd
			AND     m.knsgrp   =  g.knsgrp
			AND     g.knssbt   NOT IN ('S','T')
			AND     g.kaiymd   <= :hst_ymd
			AND     g.haiymd   >= :hst_ymd
			ORDER BY m.knsgrp
			FETCH FIRST 1 ROWS ONLY
			;
*/

{
#line 462 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 462 "AD202_db.sqc"
  sqlaaloc(2,7,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 462 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 462 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hknkyumst.kmkcd;
#line 462 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 462 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_ymd;
#line 462 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 462 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hst_ymd;
#line 462 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 462 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)hst_ymd;
#line 462 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 462 "AD202_db.sqc"
      sql_setdlist[4].sqldata = (void*)hst_ymd;
#line 462 "AD202_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 462 "AD202_db.sqc"
      sql_setdlist[5].sqldata = (void*)hst_ymd;
#line 462 "AD202_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 462 "AD202_db.sqc"
      sql_setdlist[6].sqldata = (void*)hst_ymd;
#line 462 "AD202_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 462 "AD202_db.sqc"
  sqlaaloc(3,6,9,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 462 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 462 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hknkyumst.smpcd;
#line 462 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 462 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hknkyumst.seccd;
#line 462 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 17;
#line 462 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hknkyumst.knsgrp;
#line 462 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 462 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)hknkyumst.kmkrs;
#line 462 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 462 "AD202_db.sqc"
      sql_setdlist[4].sqldata = (void*)hknkyumst.oyakmkcd;
#line 462 "AD202_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 2;
#line 462 "AD202_db.sqc"
      sql_setdlist[5].sqldata = (void*)hknkyumst.fkbnkkb;
#line 462 "AD202_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 462 "AD202_db.sqc"
      sqlasetdata(3,0,6,sql_setdlist,0L,0L);
    }
#line 462 "AD202_db.sqc"
  sqlacall((unsigned short)24,6,2,3,0L);
#line 462 "AD202_db.sqc"
  sqlastop(0L);
}

#line 462 "AD202_db.sqc"

	}

	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "SELECT knkyumst : kmkcd[%s]ymd[%s]",
		kom->kmkcd, stcPRM.myp_kjnymd );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if ( sqlca.sqlcode == 0 ) {		/* OK */
		strcpy( kom->knsgrp,	hknkyumst.knsgrp );
		strcpy( kom->kmkrs,		hknkyumst.kmkrs );
		strcpy( kom->oyakmkcd,	hknkyumst.oyakmkcd );
		strcpy( kom->fkbnkkb,	hknkyumst.fkbnkkb );
		strcpy( kom->seccd,		hknkyumst.seccd );
		strcpy( kom->smpcd,		hknkyumst.smpcd );
		ret = RTN_OK;
	} else {
		if ( sqlca.sqlcode == 100 ){	/* NOT FOUND */
			ret=RTN_SKIP;
		} else {
			/* SQLCODE > 0 -> WARNING */
			/* SQLCODE < 0 -> ERROR */
			sprintf( G_msg,
				"�ً}�˗����ڏ��}�X�^ SELECT �ŕs����������܂����B"
				"����[%s]���[%s]"
				,kom->kmkcd, stcPRM.myp_kjnymd );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			 
			ret=RTN_DBERR;
		}
	}

//	1TRANSACTION���ŌĂԂ��߃R�����g��
//EXEC SQL COMMIT;

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FSelCountKjnmst                                                */
/*  �@�\�T�v  �F��l�}�X�^�i�ً}�Ή����ڃ}�X�^�����j�����擾                */
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
	FROM	kjnmst kj, kinkmmst kinq
	WHERE	kj.kmkcd	= kinq.kmkcd
	AND		kj.kaiymd	<= :hst_ymd
	AND		kj.haiymd	>= :hst_ymd
	AND		kinq.kaiymd	<= :hst_ymd
	AND		kinq.haiymd	>= :hst_ymd
	;
*/

{
#line 540 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 540 "AD202_db.sqc"
  sqlaaloc(2,4,10,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 540 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 540 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hst_ymd;
#line 540 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 540 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 540 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_ymd;
#line 540 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 540 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 540 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hst_ymd;
#line 540 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 540 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 540 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)hst_ymd;
#line 540 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 540 "AD202_db.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 540 "AD202_db.sqc"
  sqlaaloc(3,1,11,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 540 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 497; sql_setdlist[0].sqllen = 4;
#line 540 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)&hst_cnt;
#line 540 "AD202_db.sqc"
      sql_setdlist[0].sqlind = &ind_cnt;
#line 540 "AD202_db.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 540 "AD202_db.sqc"
  sqlacall((unsigned short)24,7,2,3,0L);
#line 540 "AD202_db.sqc"
  sqlastop(0L);
}

#line 540 "AD202_db.sqc"


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
/*  �@�\�T�v  �F��l�}�X�^ SELECT  �i�ً}�Ή����ڃ}�X�^�����j               */
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
	FROM	kjnmst kj, kinkmmst kinq
	WHERE	kj.kmkcd	= kinq.kmkcd
	AND		kj.kaiymd	<= :hst_ymd
	AND		kj.haiymd	>= :hst_ymd
	AND		kinq.kaiymd	<= :hst_ymd
	AND		kinq.haiymd	>= :hst_ymd
	ORDER BY kj.kmkcd, kj.zrcd, nichilw, nichihi
	;
*/

#line 620 "AD202_db.sqc"



/*
EXEC SQL OPEN kjn_cur;
*/

{
#line 622 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 622 "AD202_db.sqc"
  sqlaaloc(2,4,12,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 622 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 622 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hst_ymd;
#line 622 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 622 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 622 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_ymd;
#line 622 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 622 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 622 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hst_ymd;
#line 622 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 622 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 622 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)hst_ymd;
#line 622 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 622 "AD202_db.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 622 "AD202_db.sqc"
  sqlacall((unsigned short)26,8,2,0,0L);
#line 622 "AD202_db.sqc"
  sqlastop(0L);
}

#line 622 "AD202_db.sqc"


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
#line 634 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 634 "AD202_db.sqc"
  sqlaaloc(3,6,13,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 634 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 634 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkjnmst.kmkcd;
#line 634 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 634 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 4;
#line 634 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkjnmst.kjno;
#line 634 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 634 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 634 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkjnmst.zrcd;
#line 634 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 634 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 4;
#line 634 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)hkjnmst.etckbn;
#line 634 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 634 "AD202_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 6;
#line 634 "AD202_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkjnmst.nichilw;
#line 634 "AD202_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 634 "AD202_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 6;
#line 634 "AD202_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkjnmst.nichihi;
#line 634 "AD202_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 634 "AD202_db.sqc"
      sqlasetdata(3,0,6,sql_setdlist,0L,0L);
    }
#line 634 "AD202_db.sqc"
  sqlacall((unsigned short)25,8,0,3,0L);
#line 634 "AD202_db.sqc"
  sqlastop(0L);
}

#line 634 "AD202_db.sqc"

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
#line 670 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 670 "AD202_db.sqc"
  sqlacall((unsigned short)20,8,0,0,0L);
#line 670 "AD202_db.sqc"
  sqlastop(0L);
}

#line 670 "AD202_db.sqc"


/*
EXEC SQL	COMMIT;
*/

{
#line 671 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 671 "AD202_db.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 671 "AD202_db.sqc"
  sqlastop(0L);
}

#line 671 "AD202_db.sqc"


	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FInsKanjya                                                     */
/*  �@�\�T�v  �F���ґ����@INSERT                                              */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _KANJYA     *zok;   : ���ҏ��                        */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		InsKanjya( kan )
struct		_KANJYA	*kan;			/* ���ґ����f�[�^ */
{
	struct	sqlca	sqlca;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/

	/* ��������	*/
	strcpy(func_nm, "InsKanjya" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̃Z�b�g	*/
	memcpy( &hkanjya, kan, sizeof( struct _KANJYA ));


/*
EXEC SQL INSERT	INTO	kanjya
		( utkymd
		, irino
		, iriketflg
		, zssdino
		, sstcd
		, subsstcd
		, cdkbn1
		, cdkbn2
		, irimkey
		, srkcd
		, srknm
		, tticd
		, ttinm
		, gpcd
		, gpnm
		, skicd
		, skinm
		, krtno
		, knjid
		, knjnmn
		, knjnmk
		, knjnmkey
		, sc
		, tj
		, tjtni
		, sbtkbn
		, birthday
		, birthdaykbn
		, age
		, agekbn
		, btcd
		, btnm
		, utkcmtcd1
		, utkcmtcd2
		, utkcmtcd3
		, utkcmtfr1
		, utkcmtfr2
		, utkcmtfrflg
		, ngkbn
		, nsssu
		, hkncd
		, ktshsu
		, iniriymd
		, zssflg
		, kkiriflg
		, hknskbn
		, utkkbn
		, nekbn
		, inknskbn
		, utkjkkbn
		, krflg
		, fdhhkkflg
		, utkdh
		, mutkymd
		, mirino
		, knsjslbcd1
		, knsjslbcd2
		, knsjslbcd3
		, knsjslbcd4
		, ymhkkflg
		, hkkkbdh
		, ecd
		, shcd
		, sstssnmj
		, sstssnmn
		, sstrsj
		, sstrsn
		, sstsbt
		, ttsstflg
		, rucd
		, irikmksu
		, bmskn
		, irinrsbt
		, irihsmkbn
		, caresstflg
		, tktyflg
		, apkntino
		, sdnm
		, bko1
		, bko2
		, bko3
		, zstrdh
		, zsssdh
		, stlzsssdh
		, stlzsssip
		, stlzssssyaid
		, ksndh
		, oyasstcd					-- 1.01 ADD
		, trkdh						-- 1.01 ADD
		)
	VALUES	( :hkanjya.utkymd
		, :hkanjya.irino
		, :hkanjya.iriketflg
		, :hkanjya.zssdino
		, :hkanjya.sstcd
		, :hkanjya.subsstcd
		, :hkanjya.cdkbn1
		, :hkanjya.cdkbn2
		, :hkanjya.irimkey
		, :hkanjya.srkcd
		, :hkanjya.srknm
		, :hkanjya.tticd
		, :hkanjya.ttinm
		, :hkanjya.gpcd
		, :hkanjya.gpnm
		, :hkanjya.skicd
		, :hkanjya.skinm
		, :hkanjya.krtno
		, :hkanjya.knjid
		, :hkanjya.knjnmn
		, :hkanjya.knjnmk
		, :hkanjya.knjnmkey
		, :hkanjya.sc
		, :hkanjya.tj
		, :hkanjya.tjtni
		, :hkanjya.sbtkbn
		, :hkanjya.birthday
		, :hkanjya.birthdaykbn
		, :hkanjya.age
		, :hkanjya.agekbn
		, :hkanjya.btcd
		, :hkanjya.btnm
		, :hkanjya.utkcmtcd1
		, :hkanjya.utkcmtcd2
		, :hkanjya.utkcmtcd3
		, :hkanjya.utkcmtfr1
		, :hkanjya.utkcmtfr2
		, :hkanjya.utkcmtfrflg
		, :hkanjya.ngkbn
		, :hkanjya.nsssu
		, :hkanjya.hkncd
		, :hkanjya.ktshsu
		, :hkanjya.iniriymd
		, :hkanjya.zssflg
		, :hkanjya.kkiriflg
		, :hkanjya.hknskbn
		, :hkanjya.utkkbn
		, :hkanjya.nekbn
		, :hkanjya.inknskbn
		, :hkanjya.utkjkkbn
		, :hkanjya.krflg
		, :hkanjya.fdhhkkflg
		, :hkanjya.utkdh
		, :hkanjya.mutkymd
		, :hkanjya.mirino
		, :hkanjya.knsjslbcd1
		, :hkanjya.knsjslbcd2
		, :hkanjya.knsjslbcd3
		, :hkanjya.knsjslbcd4
		, :hkanjya.ymhkkflg
		, :hkanjya.hkkkbdh
		, :hkanjya.ecd
		, :hkanjya.shcd
		, :hkanjya.sstssnmj
		, :hkanjya.sstssnmn
		, :hkanjya.sstrsj
		, :hkanjya.sstrsn
		, :hkanjya.sstsbt
		, :hkanjya.ttsstflg
		, :hkanjya.rucd
		, :hkanjya.irikmksu
		, :hkanjya.bmskn
		, :hkanjya.irinrsbt
		, :hkanjya.irihsmkbn
		, :hkanjya.caresstflg
		, :hkanjya.tktyflg
		, :hkanjya.apkntino
		, :hkanjya.sdnm
		, :hkanjya.bko1
		, :hkanjya.bko2
		, :hkanjya.bko3
		, :hkanjya.zstrdh
		, :hkanjya.zsssdh
		, :hkanjya.stlzsssdh
		, :hkanjya.stlzsssip
		, :hkanjya.stlzssssyaid
		, CURRENT TIMESTAMP
		, :hkanjya.oyasstcd				-- 1.01 ADD
		, CURRENT TIMESTAMP				-- 1.01 ADD
		)
	;
*/

{
#line 880 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 880 "AD202_db.sqc"
  sqlaaloc(2,87,14,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 880 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 880 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.utkymd;
#line 880 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 880 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.irino;
#line 880 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkanjya.iriketflg;
#line 880 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)&hkanjya.zssdino;
#line 880 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 880 "AD202_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkanjya.sstcd;
#line 880 "AD202_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 5;
#line 880 "AD202_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkanjya.subsstcd;
#line 880 "AD202_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 3;
#line 880 "AD202_db.sqc"
      sql_setdlist[6].sqldata = (void*)hkanjya.cdkbn1;
#line 880 "AD202_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 880 "AD202_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkanjya.cdkbn2;
#line 880 "AD202_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 41;
#line 880 "AD202_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkanjya.irimkey;
#line 880 "AD202_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 4;
#line 880 "AD202_db.sqc"
      sql_setdlist[9].sqldata = (void*)hkanjya.srkcd;
#line 880 "AD202_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 31;
#line 880 "AD202_db.sqc"
      sql_setdlist[10].sqldata = (void*)hkanjya.srknm;
#line 880 "AD202_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 880 "AD202_db.sqc"
      sql_setdlist[11].sqldata = (void*)hkanjya.tticd;
#line 880 "AD202_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 41;
#line 880 "AD202_db.sqc"
      sql_setdlist[12].sqldata = (void*)hkanjya.ttinm;
#line 880 "AD202_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 880 "AD202_db.sqc"
      sql_setdlist[13].sqldata = (void*)hkanjya.gpcd;
#line 880 "AD202_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 41;
#line 880 "AD202_db.sqc"
      sql_setdlist[14].sqldata = (void*)hkanjya.gpnm;
#line 880 "AD202_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 880 "AD202_db.sqc"
      sql_setdlist[15].sqldata = (void*)hkanjya.skicd;
#line 880 "AD202_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 41;
#line 880 "AD202_db.sqc"
      sql_setdlist[16].sqldata = (void*)hkanjya.skinm;
#line 880 "AD202_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 41;
#line 880 "AD202_db.sqc"
      sql_setdlist[17].sqldata = (void*)hkanjya.krtno;
#line 880 "AD202_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 16;
#line 880 "AD202_db.sqc"
      sql_setdlist[18].sqldata = (void*)hkanjya.knjid;
#line 880 "AD202_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 61;
#line 880 "AD202_db.sqc"
      sql_setdlist[19].sqldata = (void*)hkanjya.knjnmn;
#line 880 "AD202_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 31;
#line 880 "AD202_db.sqc"
      sql_setdlist[20].sqldata = (void*)hkanjya.knjnmk;
#line 880 "AD202_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 61;
#line 880 "AD202_db.sqc"
      sql_setdlist[21].sqldata = (void*)hkanjya.knjnmkey;
#line 880 "AD202_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 6;
#line 880 "AD202_db.sqc"
      sql_setdlist[22].sqldata = (void*)hkanjya.sc;
#line 880 "AD202_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 6;
#line 880 "AD202_db.sqc"
      sql_setdlist[23].sqldata = (void*)hkanjya.tj;
#line 880 "AD202_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[24].sqldata = (void*)hkanjya.tjtni;
#line 880 "AD202_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[25].sqldata = (void*)hkanjya.sbtkbn;
#line 880 "AD202_db.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 9;
#line 880 "AD202_db.sqc"
      sql_setdlist[26].sqldata = (void*)hkanjya.birthday;
#line 880 "AD202_db.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[27].sqldata = (void*)hkanjya.birthdaykbn;
#line 880 "AD202_db.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 4;
#line 880 "AD202_db.sqc"
      sql_setdlist[28].sqldata = (void*)hkanjya.age;
#line 880 "AD202_db.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[29].sqldata = (void*)hkanjya.agekbn;
#line 880 "AD202_db.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 11;
#line 880 "AD202_db.sqc"
      sql_setdlist[30].sqldata = (void*)hkanjya.btcd;
#line 880 "AD202_db.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 31;
#line 880 "AD202_db.sqc"
      sql_setdlist[31].sqldata = (void*)hkanjya.btnm;
#line 880 "AD202_db.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 880 "AD202_db.sqc"
      sql_setdlist[32].sqldata = (void*)hkanjya.utkcmtcd1;
#line 880 "AD202_db.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 880 "AD202_db.sqc"
      sql_setdlist[33].sqldata = (void*)hkanjya.utkcmtcd2;
#line 880 "AD202_db.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 3;
#line 880 "AD202_db.sqc"
      sql_setdlist[34].sqldata = (void*)hkanjya.utkcmtcd3;
#line 880 "AD202_db.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 71;
#line 880 "AD202_db.sqc"
      sql_setdlist[35].sqldata = (void*)hkanjya.utkcmtfr1;
#line 880 "AD202_db.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 71;
#line 880 "AD202_db.sqc"
      sql_setdlist[36].sqldata = (void*)hkanjya.utkcmtfr2;
#line 880 "AD202_db.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[37].sqldata = (void*)hkanjya.utkcmtfrflg;
#line 880 "AD202_db.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[38].sqldata = (void*)hkanjya.ngkbn;
#line 880 "AD202_db.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 3;
#line 880 "AD202_db.sqc"
      sql_setdlist[39].sqldata = (void*)hkanjya.nsssu;
#line 880 "AD202_db.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[40].sqldata = (void*)hkanjya.hkncd;
#line 880 "AD202_db.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 880 "AD202_db.sqc"
      sql_setdlist[41].sqldata = (void*)hkanjya.ktshsu;
#line 880 "AD202_db.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 11;
#line 880 "AD202_db.sqc"
      sql_setdlist[42].sqldata = (void*)hkanjya.iniriymd;
#line 880 "AD202_db.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[43].sqldata = (void*)hkanjya.zssflg;
#line 880 "AD202_db.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[44].sqldata = (void*)hkanjya.kkiriflg;
#line 880 "AD202_db.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[45].sqldata = (void*)hkanjya.hknskbn;
#line 880 "AD202_db.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[46].sqldata = (void*)hkanjya.utkkbn;
#line 880 "AD202_db.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[47].sqldata = (void*)hkanjya.nekbn;
#line 880 "AD202_db.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[48].sqldata = (void*)hkanjya.inknskbn;
#line 880 "AD202_db.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[49].sqldata = (void*)hkanjya.utkjkkbn;
#line 880 "AD202_db.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[50].sqldata = (void*)hkanjya.krflg;
#line 880 "AD202_db.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[51].sqldata = (void*)hkanjya.fdhhkkflg;
#line 880 "AD202_db.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 9;
#line 880 "AD202_db.sqc"
      sql_setdlist[52].sqldata = (void*)hkanjya.utkdh;
#line 880 "AD202_db.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 11;
#line 880 "AD202_db.sqc"
      sql_setdlist[53].sqldata = (void*)hkanjya.mutkymd;
#line 880 "AD202_db.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 12;
#line 880 "AD202_db.sqc"
      sql_setdlist[54].sqldata = (void*)hkanjya.mirino;
#line 880 "AD202_db.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 880 "AD202_db.sqc"
      sql_setdlist[55].sqldata = (void*)hkanjya.knsjslbcd1;
#line 880 "AD202_db.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 4;
#line 880 "AD202_db.sqc"
      sql_setdlist[56].sqldata = (void*)hkanjya.knsjslbcd2;
#line 880 "AD202_db.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 4;
#line 880 "AD202_db.sqc"
      sql_setdlist[57].sqldata = (void*)hkanjya.knsjslbcd3;
#line 880 "AD202_db.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[58].sqltype = 460; sql_setdlist[58].sqllen = 4;
#line 880 "AD202_db.sqc"
      sql_setdlist[58].sqldata = (void*)hkanjya.knsjslbcd4;
#line 880 "AD202_db.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[59].sqltype = 460; sql_setdlist[59].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[59].sqldata = (void*)hkanjya.ymhkkflg;
#line 880 "AD202_db.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[60].sqltype = 460; sql_setdlist[60].sqllen = 9;
#line 880 "AD202_db.sqc"
      sql_setdlist[60].sqldata = (void*)hkanjya.hkkkbdh;
#line 880 "AD202_db.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[61].sqltype = 460; sql_setdlist[61].sqllen = 4;
#line 880 "AD202_db.sqc"
      sql_setdlist[61].sqldata = (void*)hkanjya.ecd;
#line 880 "AD202_db.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[62].sqltype = 460; sql_setdlist[62].sqllen = 3;
#line 880 "AD202_db.sqc"
      sql_setdlist[62].sqldata = (void*)hkanjya.shcd;
#line 880 "AD202_db.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[63].sqltype = 460; sql_setdlist[63].sqllen = 41;
#line 880 "AD202_db.sqc"
      sql_setdlist[63].sqldata = (void*)hkanjya.sstssnmj;
#line 880 "AD202_db.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sqlasetdata(2,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[23];
#line 880 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 41;
#line 880 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.sstssnmn;
#line 880 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 880 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.sstrsj;
#line 880 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 880 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkanjya.sstrsn;
#line 880 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 880 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)hkanjya.sstsbt;
#line 880 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkanjya.ttsstflg;
#line 880 "AD202_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 880 "AD202_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkanjya.rucd;
#line 880 "AD202_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[6].sqldata = (void*)&hkanjya.irikmksu;
#line 880 "AD202_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 880 "AD202_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkanjya.bmskn;
#line 880 "AD202_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 3;
#line 880 "AD202_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkanjya.irinrsbt;
#line 880 "AD202_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[9].sqldata = (void*)hkanjya.irihsmkbn;
#line 880 "AD202_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[10].sqldata = (void*)hkanjya.caresstflg;
#line 880 "AD202_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 2;
#line 880 "AD202_db.sqc"
      sql_setdlist[11].sqldata = (void*)hkanjya.tktyflg;
#line 880 "AD202_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 14;
#line 880 "AD202_db.sqc"
      sql_setdlist[12].sqldata = (void*)hkanjya.apkntino;
#line 880 "AD202_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 880 "AD202_db.sqc"
      sql_setdlist[13].sqldata = (void*)hkanjya.sdnm;
#line 880 "AD202_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 21;
#line 880 "AD202_db.sqc"
      sql_setdlist[14].sqldata = (void*)hkanjya.bko1;
#line 880 "AD202_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 21;
#line 880 "AD202_db.sqc"
      sql_setdlist[15].sqldata = (void*)hkanjya.bko2;
#line 880 "AD202_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 21;
#line 880 "AD202_db.sqc"
      sql_setdlist[16].sqldata = (void*)hkanjya.bko3;
#line 880 "AD202_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 880 "AD202_db.sqc"
      sql_setdlist[17].sqldata = (void*)hkanjya.zstrdh;
#line 880 "AD202_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 880 "AD202_db.sqc"
      sql_setdlist[18].sqldata = (void*)hkanjya.zsssdh;
#line 880 "AD202_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 880 "AD202_db.sqc"
      sql_setdlist[19].sqldata = (void*)hkanjya.stlzsssdh;
#line 880 "AD202_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 16;
#line 880 "AD202_db.sqc"
      sql_setdlist[20].sqldata = (void*)hkanjya.stlzsssip;
#line 880 "AD202_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 9;
#line 880 "AD202_db.sqc"
      sql_setdlist[21].sqldata = (void*)hkanjya.stlzssssyaid;
#line 880 "AD202_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 8;
#line 880 "AD202_db.sqc"
      sql_setdlist[22].sqldata = (void*)hkanjya.oyasstcd;
#line 880 "AD202_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 880 "AD202_db.sqc"
      sqlasetdata(2,64,23,sql_setdlist,0L,0L);
    }
#line 880 "AD202_db.sqc"
  sqlacall((unsigned short)24,9,2,0,0L);
#line 880 "AD202_db.sqc"
  sqlastop(0L);
}

#line 880 "AD202_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "INSERT kanjya : utkymd[%s]irino[%s]zssdino[%d]",
		kan->utkymd, kan->irino, kan->zssdino );
	LogOut( LT_DBG, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if ( sqlca.sqlcode != 0 ) {		/* OK */
		if ( sqlca.sqlcode == MYAPP_RTN_DUP ) {	// duplicate
			;						/* ���͉������Ȃ����A����d���G���[��LOG�o�͂� */
									/* �������ꍇ�ɂ͂����ɒǉ��I                  */
		}
		else {
			sprintf( G_msg,
				"���ҏ��(kanjya)�� INSERT �Ɏ��s���܂����B"
				"BML��t�N����[%s]�˗���NO[%s]��������NO[%d]"
				,kan->utkymd, kan->irino, kan->zssdino );
		}
		EditCsvMsg( G_msg );
		LogOut( LT_TRC, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__ );
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( sqlca.sqlcode );
}

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
		, trkdh						-- 1.01 ADD
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
		, CURRENT TIMESTAMP					-- 1.01 ADD
		)
	;
*/

{
#line 1033 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1033 "AD202_db.sqc"
  sqlaaloc(2,47,15,0L);
    {
      struct sqla_setdata_list sql_setdlist[47];
#line 1033 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1033 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hirai.utkymd;
#line 1033 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1033 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hirai.irino;
#line 1033 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hirai.iriketflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)&hirai.zssdino;
#line 1033 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 17;
#line 1033 "AD202_db.sqc"
      sql_setdlist[4].sqldata = (void*)hirai.knsgrp;
#line 1033 "AD202_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 1033 "AD202_db.sqc"
      sql_setdlist[5].sqldata = (void*)hirai.kmkcd;
#line 1033 "AD202_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[6].sqldata = (void*)hirai.irihsmkbn;
#line 1033 "AD202_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[7].sqldata = (void*)hirai.irikbn;
#line 1033 "AD202_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[8].sqldata = (void*)hirai.ksktkbn;
#line 1033 "AD202_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 1033 "AD202_db.sqc"
      sql_setdlist[9].sqldata = (void*)hirai.sriymd;
#line 1033 "AD202_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 14;
#line 1033 "AD202_db.sqc"
      sql_setdlist[10].sqldata = (void*)hirai.kntno;
#line 1033 "AD202_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[11].sqldata = (void*)hirai.kntketflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 5;
#line 1033 "AD202_db.sqc"
      sql_setdlist[12].sqldata = (void*)hirai.chkmj;
#line 1033 "AD202_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 5;
#line 1033 "AD202_db.sqc"
      sql_setdlist[13].sqldata = (void*)hirai.stsrcd;
#line 1033 "AD202_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 17;
#line 1033 "AD202_db.sqc"
      sql_setdlist[14].sqldata = (void*)hirai.kmkrs;
#line 1033 "AD202_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 8;
#line 1033 "AD202_db.sqc"
      sql_setdlist[15].sqldata = (void*)hirai.oyakmkcd;
#line 1033 "AD202_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 8;
#line 1033 "AD202_db.sqc"
      sql_setdlist[16].sqldata = (void*)hirai.smpcd;
#line 1033 "AD202_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 8;
#line 1033 "AD202_db.sqc"
      sql_setdlist[17].sqldata = (void*)hirai.setkmkcd;
#line 1033 "AD202_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[18].sqldata = (void*)hirai.srinycd;
#line 1033 "AD202_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 3;
#line 1033 "AD202_db.sqc"
      sql_setdlist[19].sqldata = (void*)hirai.seccd;
#line 1033 "AD202_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[20].sqldata = (void*)hirai.skchkflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[21].sqldata = (void*)hirai.bkfkkbn;
#line 1033 "AD202_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 3;
#line 1033 "AD202_db.sqc"
      sql_setdlist[22].sqldata = (void*)hirai.ysnlbl;
#line 1033 "AD202_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[23].sqldata = (void*)hirai.skflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[24].sqldata = (void*)hirai.tkflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[25].sqldata = (void*)hirai.sjflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[26].sqldata = (void*)hirai.jktkflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 4;
#line 1033 "AD202_db.sqc"
      sql_setdlist[27].sqldata = (void*)hirai.kjno;
#line 1033 "AD202_db.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[28].sqldata = (void*)hirai.fkhkknohjkbn;
#line 1033 "AD202_db.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 4;
#line 1033 "AD202_db.sqc"
      sql_setdlist[29].sqldata = (void*)hirai.tbkjno;
#line 1033 "AD202_db.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[30].sqldata = (void*)hirai.tbkjflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 25;
#line 1033 "AD202_db.sqc"
      sql_setdlist[31].sqldata = (void*)hirai.htkfkhms;
#line 1033 "AD202_db.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 1033 "AD202_db.sqc"
      sql_setdlist[32].sqldata = (void*)hirai.tskflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 1033 "AD202_db.sqc"
      sql_setdlist[33].sqldata = (void*)hirai.tktflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[34].sqldata = (void*)hirai.bnckbn;
#line 1033 "AD202_db.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[35].sqldata = (void*)hirai.nbnckbn;
#line 1033 "AD202_db.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 11;
#line 1033 "AD202_db.sqc"
      sql_setdlist[36].sqldata = (void*)hirai.knskisyymd;
#line 1033 "AD202_db.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 11;
#line 1033 "AD202_db.sqc"
      sql_setdlist[37].sqldata = (void*)hirai.knskryymd;
#line 1033 "AD202_db.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 9;
#line 1033 "AD202_db.sqc"
      sql_setdlist[38].sqldata = (void*)hirai.knskrytme;
#line 1033 "AD202_db.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[39].sqldata = (void*)hirai.kkhkkflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[40].sqldata = (void*)hirai.kkiriflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[41].sqltype = 500; sql_setdlist[41].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[41].sqldata = (void*)&hirai.kkirilotno;
#line 1033 "AD202_db.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 5;
#line 1033 "AD202_db.sqc"
      sql_setdlist[42].sqldata = (void*)hirai.kktoutkid;
#line 1033 "AD202_db.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[43].sqltype = 500; sql_setdlist[43].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[43].sqldata = (void*)&hirai.knssu;
#line 1033 "AD202_db.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[44].sqldata = (void*)hirai.odrssflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 16;
#line 1033 "AD202_db.sqc"
      sql_setdlist[45].sqldata = (void*)hirai.ytiksbr;
#line 1033 "AD202_db.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 2;
#line 1033 "AD202_db.sqc"
      sql_setdlist[46].sqldata = (void*)hirai.hhkjkflg;
#line 1033 "AD202_db.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 1033 "AD202_db.sqc"
      sqlasetdata(2,0,47,sql_setdlist,0L,0L);
    }
#line 1033 "AD202_db.sqc"
  sqlacall((unsigned short)24,10,2,0,0L);
#line 1033 "AD202_db.sqc"
  sqlastop(0L);
}

#line 1033 "AD202_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "INSERT irai : utkymd[%s]irino[%s]zssdino[%d]kmkcd[%s]",
		iri->utkymd, iri->irino, iri->zssdino, iri->kmkcd );
	LogOut( LT_DBG, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if ( sqlca.sqlcode != 0 ) {		/* OK */
		if ( sqlca.sqlcode == MYAPP_RTN_DUP ) {	// duplicate
			sprintf( G_msg,
				"�˗����(irai)�͊��ɑ��݂��Ă��܂��B"
				"BML��t�N����[%s]�˗���NO[%s]�˗�����NO[%d]����CD[%s]"
				,iri->utkymd, iri->irino, iri->zssdino, iri->kmkcd );
		}
		else {
			sprintf( G_msg,
				"�˗����(irai)�� INSERT �Ɏ��s���܂����B"
				"BML��t�N����[%s]�˗���NO[%s]�˗�����NO[%d]����CD[%s]"
				,iri->utkymd, iri->irino, iri->zssdino, iri->kmkcd );
		}
		/* ERROR */
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__ );
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( sqlca.sqlcode );
}
// 3.01 ADD STA =============================================================
/******************************************************************************/
/*  �� �� ��  �FSelKinkyuIrai                                                 */
/*  �@�\�T�v  �FAS/400����̈˗����ڂ����݂��邩�`�F�b�N����                  */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _KANJYA    *kan;   : ���ҏ��                         */
/*  �o    ��  �F                                                              */
/*  ���A���  �FCOUNT����    ����I��                                         */
/*            �F0 ����       �ُ�I��                                         */
/******************************************************************************/
int		SelKinkyuIrai( iri )
struct		_IRAI		*iri;			// �˗����
{
	int		ret;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	struct	sqlca	sqlca;

	/* ��������	*/
	strcpy( func_nm, "SelKinkyuIrai" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	strcpy( hst_utkymd,	iri->utkymd );
	strcpy( hst_irino,	iri->irino );
	hst_kkirilotno=iri->kkirilotno;
	hst_cnt=0;
	ind_cnt=0;

	// �폜�t���O�͍l�����Ȃ�

/*
EXEC SQL SELECT	COUNT( kmkcd )
	INTO	  :hst_cnt	INDICATOR :ind_cnt
	FROM	irai
	WHERE	utkymd	= :hst_utkymd
	AND		irino	= :hst_irino
	AND	  ( kkirilotno = 0 or kkirilotno= :hst_kkirilotno )
	;
*/

{
#line 1100 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1100 "AD202_db.sqc"
  sqlaaloc(2,3,16,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 1100 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1100 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hst_utkymd;
#line 1100 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1100 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1100 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_irino;
#line 1100 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1100 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 1100 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)&hst_kkirilotno;
#line 1100 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1100 "AD202_db.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 1100 "AD202_db.sqc"
  sqlaaloc(3,1,17,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 1100 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 497; sql_setdlist[0].sqllen = 4;
#line 1100 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)&hst_cnt;
#line 1100 "AD202_db.sqc"
      sql_setdlist[0].sqlind = &ind_cnt;
#line 1100 "AD202_db.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 1100 "AD202_db.sqc"
  sqlacall((unsigned short)24,11,2,3,0L);
#line 1100 "AD202_db.sqc"
  sqlastop(0L);
}

#line 1100 "AD202_db.sqc"


    /* not found --> SQLCODE = +100, SQLSTATE == '02000' */
	/* many rows --> ERROR!!         SQLSTATE == '21000' */

	/* SQLCODE */
	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "SELECT COUNT( kmkcd ) FROM irai WHERE ___ kkirilotno : "
		"utkymd[%s]irino[%s] lotno[%d] indicator[%d] sqlcode[%s]",
		iri->utkymd, iri->irino, iri->kkirilotno, ind_cnt, G_err );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	// �W���ϐ��ɂ�锻�f
	if( ind_cnt == 0 ) {
		// COUNT���ʂ�Ԃ��i0������j
		ret = hst_cnt;
	} else {
		sprintf( G_msg,
			"AS400�˗����ڏ��(irai)�擾�Ɏ��s���܂����B"
			"BML��t�N����[%s]�˗���NO[%s] SELECT INDICATOR[%d]"
			,iri->utkymd, iri->irino, ind_cnt );
		EditCsvMsg( G_msg );
		LogOut( LT_TRC, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		ret=RTN_NG;
	}
	// DEBUG
	sprintf( G_msg, "AS400 irai COUNT[%d]", ret );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

// 3.01 ADD END =============================================================

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
#line 1190 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1190 "AD202_db.sqc"
  sqlaaloc(2,6,18,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 1190 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1190 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hst_utkymd;
#line 1190 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1190 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1190 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_irino;
#line 1190 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1190 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 1190 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hst_utkymd;
#line 1190 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1190 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 12;
#line 1190 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)hst_irino;
#line 1190 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1190 "AD202_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 1190 "AD202_db.sqc"
      sql_setdlist[4].sqldata = (void*)hst_ymd;
#line 1190 "AD202_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1190 "AD202_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 1190 "AD202_db.sqc"
      sql_setdlist[5].sqldata = (void*)hst_ymd;
#line 1190 "AD202_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1190 "AD202_db.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 1190 "AD202_db.sqc"
  sqlaaloc(3,1,19,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 1190 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 497; sql_setdlist[0].sqllen = 4;
#line 1190 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)&hst_cnt;
#line 1190 "AD202_db.sqc"
      sql_setdlist[0].sqlind = &ind_cnt;
#line 1190 "AD202_db.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 1190 "AD202_db.sqc"
  sqlacall((unsigned short)24,12,2,3,0L);
#line 1190 "AD202_db.sqc"
  sqlastop(0L);
}

#line 1190 "AD202_db.sqc"


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

#line 1291 "AD202_db.sqc"



/*
EXEC SQL OPEN jdi_cur;
*/

{
#line 1293 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1293 "AD202_db.sqc"
  sqlaaloc(2,10,20,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 1293 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1293 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hirai.utkymd;
#line 1293 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1293 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1293 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hirai.irino;
#line 1293 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1293 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 1293 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hirai.utkymd;
#line 1293 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1293 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 12;
#line 1293 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)hirai.irino;
#line 1293 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1293 "AD202_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 1293 "AD202_db.sqc"
      sql_setdlist[4].sqldata = (void*)hirai.sriymd;
#line 1293 "AD202_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1293 "AD202_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 1293 "AD202_db.sqc"
      sql_setdlist[5].sqldata = (void*)hirai.sriymd;
#line 1293 "AD202_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1293 "AD202_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 1293 "AD202_db.sqc"
      sql_setdlist[6].sqldata = (void*)hirai.utkymd;
#line 1293 "AD202_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1293 "AD202_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 12;
#line 1293 "AD202_db.sqc"
      sql_setdlist[7].sqldata = (void*)hirai.irino;
#line 1293 "AD202_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1293 "AD202_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 1293 "AD202_db.sqc"
      sql_setdlist[8].sqldata = (void*)hirai.sriymd;
#line 1293 "AD202_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1293 "AD202_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 1293 "AD202_db.sqc"
      sql_setdlist[9].sqldata = (void*)hirai.sriymd;
#line 1293 "AD202_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1293 "AD202_db.sqc"
      sqlasetdata(2,0,10,sql_setdlist,0L,0L);
    }
#line 1293 "AD202_db.sqc"
  sqlacall((unsigned short)26,13,2,0,0L);
#line 1293 "AD202_db.sqc"
  sqlastop(0L);
}

#line 1293 "AD202_db.sqc"


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
#line 1305 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1305 "AD202_db.sqc"
  sqlaaloc(3,58,21,0L);
    {
      struct sqla_setdata_list sql_setdlist[58];
#line 1305 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 1305 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)hjdkmkmst.knsgrp;
#line 1305 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 1305 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)hjdkmkmst.kmkcd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 17;
#line 1305 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)hjdkmkmst.jknsgrp;
#line 1305 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 1305 "AD202_db.sqc"
      sql_setdlist[3].sqldata = (void*)hjdkmkmst.jkmkcd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[4].sqldata = (void*)hjdkmkmst.hhkumflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 17;
#line 1305 "AD202_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkmkmst.kmkrs;
#line 1305 "AD202_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 8;
#line 1305 "AD202_db.sqc"
      sql_setdlist[6].sqldata = (void*)hkmkmst.oyakmkcd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 8;
#line 1305 "AD202_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkmkmst.smpcd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkmkmst.fkbnkkb;
#line 1305 "AD202_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 1305 "AD202_db.sqc"
      sql_setdlist[9].sqldata = (void*)hirai.utkymd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 12;
#line 1305 "AD202_db.sqc"
      sql_setdlist[10].sqldata = (void*)hirai.irino;
#line 1305 "AD202_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[11].sqldata = (void*)hirai.iriketflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[12].sqldata = (void*)&hirai.zssdino;
#line 1305 "AD202_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 17;
#line 1305 "AD202_db.sqc"
      sql_setdlist[13].sqldata = (void*)hirai.knsgrp;
#line 1305 "AD202_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 8;
#line 1305 "AD202_db.sqc"
      sql_setdlist[14].sqldata = (void*)hirai.kmkcd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[15].sqldata = (void*)hirai.irihsmkbn;
#line 1305 "AD202_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[16].sqldata = (void*)hirai.irikbn;
#line 1305 "AD202_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[17].sqldata = (void*)hirai.ksktkbn;
#line 1305 "AD202_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 11;
#line 1305 "AD202_db.sqc"
      sql_setdlist[18].sqldata = (void*)hirai.sriymd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 14;
#line 1305 "AD202_db.sqc"
      sql_setdlist[19].sqldata = (void*)hirai.kntno;
#line 1305 "AD202_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[20].sqldata = (void*)hirai.kntketflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 5;
#line 1305 "AD202_db.sqc"
      sql_setdlist[21].sqldata = (void*)hirai.chkmj;
#line 1305 "AD202_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 5;
#line 1305 "AD202_db.sqc"
      sql_setdlist[22].sqldata = (void*)hirai.stsrcd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 17;
#line 1305 "AD202_db.sqc"
      sql_setdlist[23].sqldata = (void*)hirai.kmkrs;
#line 1305 "AD202_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 8;
#line 1305 "AD202_db.sqc"
      sql_setdlist[24].sqldata = (void*)hirai.oyakmkcd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 8;
#line 1305 "AD202_db.sqc"
      sql_setdlist[25].sqldata = (void*)hirai.smpcd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 8;
#line 1305 "AD202_db.sqc"
      sql_setdlist[26].sqldata = (void*)hirai.setkmkcd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[27].sqldata = (void*)hirai.srinycd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 3;
#line 1305 "AD202_db.sqc"
      sql_setdlist[28].sqldata = (void*)hirai.seccd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[29].sqldata = (void*)hirai.skchkflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[30].sqldata = (void*)hirai.bkfkkbn;
#line 1305 "AD202_db.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 3;
#line 1305 "AD202_db.sqc"
      sql_setdlist[31].sqldata = (void*)hirai.ysnlbl;
#line 1305 "AD202_db.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[32].sqldata = (void*)hirai.skflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[33].sqldata = (void*)hirai.tkflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[34].sqldata = (void*)hirai.sjflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[35].sqldata = (void*)hirai.jktkflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 4;
#line 1305 "AD202_db.sqc"
      sql_setdlist[36].sqldata = (void*)hirai.kjno;
#line 1305 "AD202_db.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[37].sqldata = (void*)hirai.fkhkknohjkbn;
#line 1305 "AD202_db.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 4;
#line 1305 "AD202_db.sqc"
      sql_setdlist[38].sqldata = (void*)hirai.tbkjno;
#line 1305 "AD202_db.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[39].sqldata = (void*)hirai.tbkjflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 25;
#line 1305 "AD202_db.sqc"
      sql_setdlist[40].sqldata = (void*)hirai.htkfkhms;
#line 1305 "AD202_db.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 1305 "AD202_db.sqc"
      sql_setdlist[41].sqldata = (void*)hirai.tskflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 3;
#line 1305 "AD202_db.sqc"
      sql_setdlist[42].sqldata = (void*)hirai.tktflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[43].sqldata = (void*)hirai.bnckbn;
#line 1305 "AD202_db.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[44].sqldata = (void*)hirai.nbnckbn;
#line 1305 "AD202_db.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 11;
#line 1305 "AD202_db.sqc"
      sql_setdlist[45].sqldata = (void*)hirai.knskisyymd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 11;
#line 1305 "AD202_db.sqc"
      sql_setdlist[46].sqldata = (void*)hirai.knskryymd;
#line 1305 "AD202_db.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 9;
#line 1305 "AD202_db.sqc"
      sql_setdlist[47].sqldata = (void*)hirai.knskrytme;
#line 1305 "AD202_db.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[48].sqldata = (void*)hirai.kkhkkflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[49].sqldata = (void*)hirai.kkiriflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[50].sqltype = 500; sql_setdlist[50].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[50].sqldata = (void*)&hirai.kkirilotno;
#line 1305 "AD202_db.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 5;
#line 1305 "AD202_db.sqc"
      sql_setdlist[51].sqldata = (void*)hirai.kktoutkid;
#line 1305 "AD202_db.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[52].sqltype = 500; sql_setdlist[52].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[52].sqldata = (void*)&hirai.knssu;
#line 1305 "AD202_db.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[53].sqldata = (void*)hirai.odrssflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 16;
#line 1305 "AD202_db.sqc"
      sql_setdlist[54].sqldata = (void*)hirai.ytiksbr;
#line 1305 "AD202_db.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 2;
#line 1305 "AD202_db.sqc"
      sql_setdlist[55].sqldata = (void*)hirai.hhkjkflg;
#line 1305 "AD202_db.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 27;
#line 1305 "AD202_db.sqc"
      sql_setdlist[56].sqldata = (void*)hirai.ksndh;
#line 1305 "AD202_db.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 27;
#line 1305 "AD202_db.sqc"
      sql_setdlist[57].sqldata = (void*)hirai.trkdh;
#line 1305 "AD202_db.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 1305 "AD202_db.sqc"
      sqlasetdata(3,0,58,sql_setdlist,0L,0L);
    }
#line 1305 "AD202_db.sqc"
  sqlacall((unsigned short)25,13,0,3,0L);
#line 1305 "AD202_db.sqc"
  sqlastop(0L);
}

#line 1305 "AD202_db.sqc"


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
#line 1361 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1361 "AD202_db.sqc"
  sqlacall((unsigned short)20,13,0,0,0L);
#line 1361 "AD202_db.sqc"
  sqlastop(0L);
}

#line 1361 "AD202_db.sqc"


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
#line 1379 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1379 "AD202_db.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 1379 "AD202_db.sqc"
  sqlastop(0L);
}

#line 1379 "AD202_db.sqc"


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
#line 1405 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1405 "AD202_db.sqc"
  sqlacall((unsigned short)28,0,0,0,0L);
#line 1405 "AD202_db.sqc"
  sqlastop(0L);
}

#line 1405 "AD202_db.sqc"


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

#line 1432 "AD202_db.sqc"

	char	dbAlias[15];
	char	user[129];
	char	pswd[15];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 1436 "AD202_db.sqc"


	strcpy( func_nm, "Ydbconn" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	strcpy( dbAlias,	stcPRM.dbp_dbAlias );
	strcpy( user,		stcPRM.dbp_user );
	strcpy( pswd,		stcPRM.dbp_pswd );

	
/*
EXEC SQL CONNECT TO :dbAlias USER :user USING :pswd;
*/

{
#line 1445 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1445 "AD202_db.sqc"
  sqlaaloc(2,3,22,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 1445 "AD202_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 15;
#line 1445 "AD202_db.sqc"
      sql_setdlist[0].sqldata = (void*)dbAlias;
#line 1445 "AD202_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1445 "AD202_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 129;
#line 1445 "AD202_db.sqc"
      sql_setdlist[1].sqldata = (void*)user;
#line 1445 "AD202_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1445 "AD202_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 15;
#line 1445 "AD202_db.sqc"
      sql_setdlist[2].sqldata = (void*)pswd;
#line 1445 "AD202_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1445 "AD202_db.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 1445 "AD202_db.sqc"
  sqlacall((unsigned short)29,5,2,0,0L);
#line 1445 "AD202_db.sqc"
  sqlastop(0L);
}

#line 1445 "AD202_db.sqc"


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
#line 1478 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1478 "AD202_db.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 1478 "AD202_db.sqc"
  sqlastop(0L);
}

#line 1478 "AD202_db.sqc"


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
#line 1489 "AD202_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1489 "AD202_db.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 1489 "AD202_db.sqc"
  sqlastop(0L);
}

#line 1489 "AD202_db.sqc"


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
