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
