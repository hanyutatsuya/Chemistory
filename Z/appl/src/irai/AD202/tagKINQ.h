/******************************************************************************/
/*   �a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/*   �V�X�e�����F������V�X�e��                                               */
/*   �t�@�C�����FtagKINQ.h                                                    */
/*   �T      �v�FAS400�ً}�˗���M�t�@�C���\���̒�`                          */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/03/03     INTEC.INC      CREATE                             */
/*  2.00     2009/01/05     Merits K.Ameno �{�݃R�[�h���� �ʐM�d�l�ύX�Ή�    */
/******************************************************************************/
#ifndef _TAGKINQ_H
#define _TAGKINQ_H

/* #define KINQ_RECSIZE 1144 */	/*	�\���̂̑��T�C�Y"1201Byte" - FILLER�T�C�Y"57Byte"	*/
#define KINQ_RECSIZE 		( sizeof(struct AS4IRAI) - KINQ_FILLER_SIZE )
								/* Ver 2.00 1800 - 32Byte */
#define KINQ_FILLER_SIZE	32	/* FILLER�̃T�C�Y �\���́FAS4IRAI ��filler2�̃T�C�Y */
#define	IKOM_MAX			200

/*** ��M�t�@�C���t�B�[���h�ʒu��`(1���C��1�����z�񉻎��̃_�C���N�g�A�N�Z�X�p) ***/
#define	KINQ_POS_ID			0				/* ID							 */
#define	KINQ_POS_STAT		2				/* �X�e�[�^�X					 */
#define	KINQ_POS_ECODE		3				/* �c�Ə��R�[�h					 */
#define	KINQ_POS_UCODE		8				/* �{�݃R�[�h					 */
#define	KINQ_POS_UDATE		15				/* ��t���t						 */
#define	KINQ_POS_KENNO		23				/* ����No						 */
#define	KINQ_POS_NAME		34				/* ���Җ�						 */
#define	KINQ_POS_KARUTE		50				/* �J���eNo						 */
#define	KINQ_POS_BYOTO		62				/* �a��							 */
#define	KINQ_POS_DOCTOR		67				/* �S����						 */
#define	KINQ_POS_CARD		73				/* �J�[�h�敪					 */
#define	KINQ_POS_NYUGAI		75				/* ���O�敪						 */
#define	KINQ_POS_SINRYO		76				/* �f�ÉȃR�[�h					 */
#define	KINQ_POS_SEX		79				/* ����							 */
#define	KINQ_POS_AGE		80				/* �N��							 */
#define	KINQ_POS_HOKEN		83				/* �ی��R�[�h					 */
#define	KINQ_POS_SDATE		84				/* �̎��						 */
#define	KINQ_POS_ZAI		88				/* �ޗ��R�[�h					 */
#define	KINQ_POS_NRYO		91				/* �~�A��						 */
#define	KINQ_POS_NTIME		95				/* �~�A����						 */
#define	KINQ_POS_UCMT		97				/* ��t�R�����g					 */
#define	KINQ_POS_KINFLG		99				/* �ً}�t���O					 */
#define	KINQ_POS_HGRP		100				/* �����񍐃O���[�v				 */
#define	KINQ_POS_TUIKA		102				/* ���ڒǉ��t���O				 */
#define	KINQ_POS_KCOUNT		103				/* ���ڐ�						 */
#define	KINQ_POS_FCOUNT		106				/* ���א�						 */
#define	KINQ_POS_FIL		107				/* FILLER						 */
#define	KINQ_POS_CH			108				/* �`�F�b�N����					 */
#define	KINQ_POS_LCODE		110				/* ���{�R�[�h					 */

#define	KINQ_POS_KCODE1		112				/* ���ڃR�[�h 001				 */
#define	KINQ_POS_LABO1		119				/* ���{�Ώۃt���O 001			 */

#define	KINQ_POS_FKCODE1	1712			/* ���׍��ڃR�[�h 001			 */
#define	KINQ_POS_FLABO1		1719			/* ���׍��ڃ��{�Ώۃt���O 001	 */

#define	KINQ_POS_LOT		1744			/* ���b�g						 */
#define	KINQ_POS_UNAME		1746			/* �{�ݖ�						 */
#define	KINQ_POS_NEFLG		1766			/* NE�t���O						 */
#define	KINQ_POS_FIL2		1767			/* FILLER2						 */

/******************************************************************************/
/* �\���̒�`                                                                 */
/******************************************************************************/
/*===============================================================*/
/*		�˗�													 */
/*===============================================================*/
/*--- S-JIS�p�\���� ---*/

struct	AS4IKOM {			/* PNC����M���� 	*/
	char	c_koumoku_cd[7];	// ���ں��� Ver 02.00 4->7���֊g��
	char	c_labo_flg[1];		// ���{�t���O
};

struct	AS4IRAI {
/*** �{�\���̂̒�`��ύX�����ꍇ�A�K��KINQ_RECSIZE�̃`���[�j���O���K�v�I ***/
/*** ��{�I�ɂ́Asizeof �� Define���g�p���Ă���̂ŁADefine�̕ύX�݂̂�   ***/
/*** �őΉ��\�Ȃ͂������A�v�`�F�b�N�I                                   ***/
	char	c_sbt[2];			// ID
	char	c_status[1];		// �X�e�[�^�X
	char	c_eigyo_cd[5];		// �c�Ə��R�[�h Ver 02.00 2->5���֊g��
	char	c_siset_cd[7];		// �{�݃R�[�h Ver 02.00 5->7���֊g��
	char	c_bml_ymd[8];		// ��t�N���� Ver 02.00 6->8���֊g��
	char	c_kentai_no[11];	// ����No Ver 02.00 6->11���֊g��
	char	c_kanja_nm[16];		// ���Җ�
	char	c_karte_no[12];		// �J���eNo
	char	c_byoto_nm[5];		// �a��(��)
	char	c_dr_nm[6];			// �S����(��)
	char	c_card1_kbn[2];		// �J�[�h�敪
	char	c_ng_kbn[1];		// ���@�O���敪
	char	c_ka_cd[3];			// �f�ÉȃR�[�h Ver 02.00 2->3���֊g��
	char	c_sex[1];			// ���ʋ敪
	char	c_age[3];			// �N��
	char	c_hoken_cd[1];		// �ی��R�[�h
	char	c_saisyu_bi[4];		// �̎��
	char	c_zairyo_cd[3];		// �ޗ��R�[�h Ver 02.00 2->3���֊g��
	char	c_nyoryo[4];		// �~�A��
	char	c_nyotime[2];		// �~�A����
	char	c_ukecmt_cd[2];		// ��t�R�����g
	char	c_kinkyu_flg[1];	// �ً}�t���O
	char	c_hokokug[2];		// �����񍐃O���[�v
	char	c_add_flg[1];		// ���ڒǉ��t���O
	char	c_kmcnt[3];			// ��ʍ��ڐ�
	char	c_fukacnt[1];		// ���׍��ڐ�
	char	c_filler[1];		// �e�h�k�d�d�q
	char	c_kentai_ch[2];		// �`�F�b�N����
	char	c_labocd[2];		// ���{�R�[�h
    struct  AS4IKOM	ikm[IKOM_MAX];
	char	c_fukaoya1[7];		// ���אe���ڂP Ver 02.00 4->7���֊g��
	char	c_fukano1[1];		// ���ׂm���D1
	char	c_fukaoya2[7];		// ���אe���ڂQ Ver 02.00 4->7���֊g��
	char	c_fukano2[1];		// ���ׂm���D�Q
	char	c_fukaoya3[7];		// ���אe���ڂR Ver 02.00 4->7���֊g��
	char	c_fukano3[1];		// ���ׂm���D�R
	char	c_fukaoya4[7];		// ���אe���ڂS Ver 02.00 4->7���֊g��
	char	c_fukano4[1];		// ���ׂm���D�S
	char	c_lotno[2];			// ���b�g�m���D
	char	c_sisetr_knm[20];	// �{�ݖ�
	char	c_ne_kbn[1];		// �m�d�t���O
	char	c_filler2[KINQ_FILLER_SIZE];		// �e�h�k�d�d�q Ver 02.00 ���R�[�h������ 57->32�� �����ɃT�C�Y��Define��
	char	c_kaigyo[1];		/* ���s����		*/ 
};


#endif
