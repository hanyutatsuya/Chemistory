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
