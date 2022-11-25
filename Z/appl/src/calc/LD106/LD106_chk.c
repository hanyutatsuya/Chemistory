/**********************************************************************
 *
 *	   �a�l�k�����V�X�e��
 *
 *	   �V�X�e�����F��������DB�o�^
 *	   �t�@�C�����FLD106.c
 *	   �T�v		�F���͋@�����M�����������ʂ�CSV�t�@�C����DB�ɓo�^����
 *
 **********************************************************************/

/**********************************************************************
 *	Ver.	 Date		Name		History
 * --------------------------------------------------------------------
 *	1.00	 2006/01/12 	BML.inc		Create
 **********************************************************************/
#include <signal.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <syslog.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <ctype.h>

#include "sql.h"
#include "bmllog.h"
#include "bmlprm.h"
#include "bml_dbrc.h"
#include "bml_base.h"

#include "LD106.h"
#include "LD106_db.h"

/* �O���[�o���ϐ� */
/* �萫�l��l����ׂ̈̊��Z�e�[�u�� */
char		KZN_Teisei[25][5];
char		KZN_Coment[25][5];
char		IJOU_KKACMT[100][5];

#ifndef MAXBUF
#define MAXBUF                   (260)
#endif									/* !define MAXBUF					*/

/* �����I�[�_�[�Ɋ܂܂�鑮���Ɋւ��鍀�ڂ̃o�C�g �T�C�Y                    */
#define FLDSIZE_SC         ((size_t)5)  /* �g�� (cm)                        */
#define FLDSIZE_TJ         ((size_t)5)  /* �̏d                             */
#define FLDSIZE_TJTNI      ((size_t)1)  /* �̏d�敪                         */
#define FLDSIZE_TNTME      ((size_t)4)  /* �~�A����                         */
#define FLDSIZE_TNTNI      ((size_t)1)  /* �~�A���ԋ敪                     */
#define FLDSIZE_TNRYO      ((size_t)5)  /* �~�A��                           */
#define FLDSIZE_TNRYOTNI   ((size_t)1)  /* �~�A�ʋ敪                       */

#define FLDSIZE_SBTKBN     ((size_t)1)  /* ���ʋ敪                         */
#define FLDSIZE_AGE        ((size_t)3)  /* �N��                             */
#define FLDSIZE_AGEKBN     ((size_t)1)  /* �N��敪                         */

/* �P�ʓ����������ڂɊi�[����鎯�ʎq                                       */
#define _VALUE_TNTNI_HOUR       ('0')   /* �~�A����: ���ԒP��               */
#define _VALUE_TNTNI_MINUTE     ('1')   /* �~�A����: ���P��                 */
#define _VALUE_TNTNI_UNKNOWN    ('9')   /* �~�A����: ���ԒP�ʕs��           */
#define _VALUE_TNRYO_MILLILITER ('0')   /* �~�A��: �~�� ���b�g���P��        */
#define _VALUE_TNRYO_LITER      ('1')   /* �~�A��: ���b�g���P��             */
#define _VALUE_TNRYO_UNKNOWN    ('9')   /* �~�A��: �ʒP�ʕs��               */
#define _VALUE_TJTNI_KILLOGRAM  ('0')   /* �̏d: �L���O�����P��             */
#define _VALUE_TJTNI_GRAM       ('1')   /* �̏d: �O�����P��                 */
#define _VALUE_SBTKBN_MALE      ('0')   /* ����: �j��                       */
#define _VALUE_SBTKBN_FEMALE    ('1')   /* ����: ����                       */
#define _VALUE_SBTKBN_UNKNOWN   ('9')   /* ����: ���ʕs��                   */
#define _VALUE_AGEKBN_YEAR      ('Y')   /* �N��: �N��                       */

/* �v�Z���Ɋ܂܂�鑮�����̒l�ɒu������w��                               */
#define KSNSK_TNTME     ('N')           /* �~�A���� (���ԒP��)              */
#define KSNSK_TNRYO     ('R')           /* �~�A�� (�~�� ���b�g���P��)       */
#define KSNSK_SC        ('T')           /* �g��                             */
#define KSNSK_TJ        ('W')           /* �̏d (�O�����P��)                */
#define KSNSK_SBTKBN    ('S')           /* ���ʋ敪                         */
#define KSNSK_AGE       ('A')           /* �N��                             */

/* �����W�`�F�b�N�}�X�^ �͈͋敪��` */
#define RNG_CHK		('1') 
#define BML_PANIC	('2') 
#define KNS_PANIC	('3')
#define SYOGO_CHK	('4')


/* �v�Z������ IF �u���b�N�W�J                                               */
char	*OperateKSNSK(const char *);
char	*GetIFBlock(const char *);
struct	_IFBLOCK *SplitIFBlockItems(char *);
int	IsFormula(const char *);
void	freeIFBLOCK(struct _IFBLOCK *);

/* common_str.c ���̔ėp�֐�                                                */
extern char	*_replace(const char *, const char *, const char *);
extern char	*_strchain(const char *, const char *);
extern char	*_strndup(const char *, size_t);
extern char	*_touppercase(const char *);
extern char	*_strrstr(char *, const char *);

/* ���l�����񔻒�                                                           */
extern int	_isnumeric(const char *);

double	StringCal_sub(char enzan,double val1,double val2);
double	StringCal(char *CalStr) ;

char	gszTransfer[MAXBUF + 1];		/* �����񁨐��l �ϊ��o�b�t�@ �P��̒l�̒u���݂̂Ȃ̂ŁA�R���ő����    */

/* �w�蕶����̑O��̃X�y�[�X����菜���ĕ�������R�s�[���� */
void trim(char *dst, char *src) {
	int dstCnt;
	int srcCnt;
	int Flg;

	for(dstCnt = 0, srcCnt = 0, Flg = 0;
		src[srcCnt] != '\0';
		srcCnt ++) {
		if ((dstCnt == 0) && (src[srcCnt] == '\x20')) {
			continue;
		}
		dst[dstCnt++] = src[srcCnt];
		if (src[srcCnt] != '\x20') {
			Flg = dstCnt;
		}
	}
	dst[Flg] = '\0';
}

/******************************************************************************/
/*	�� �� ��  �Fkjnchk()							*/
/*	�@�\�T�v  �F��l�`�F�b�N						*/
/*	��	  ��  �F							*/
/*	 ��P���� �FpKekka	���ʏ��					*/
/*	�o	  ��  �F							*/
/*	���A���  �Fint 							*/
/*					 0	����				*/
/*					-1	�ُ�				*/
/******************************************************************************/
int kjnChk(my_stKEKKA *pKekka, my_stKJNMST *pKjnmst)
{
	/* ��l����ُ�敪���`�F�b�N���A���ʈُ�敪��ݒ肷�� */
	char		tmp1[16];
	char		tmp2[16];
	double		rawData = 0.0;
	char		wk_knskka[25];
	int 		ikzn;
	int 		iwkkzn;

	/* �ُ�l�敪�̏����� */
	pKekka->ijkbnm = pKekka->ijkbnf = pKekka->ijkbnn = '0';
	ikzn = 0;

	trim(wk_knskka, pKekka->knskka2);

	/* ���ʃR�����g�̊�l���f��ǉ� */
	if( pKekka->knskka2kbn[0] == '0' && atoi(wk_knskka) < 500 ){ /* *500�ȉ��̌��ʃR�����g���H */
		/* ���ʃR�����g�̃`�F�b�N */
		if(CHK_Kkacmt(wk_knskka) == 0){
			/* �ُ�l�}�[�N����; */
			pKekka->ijkbnm = ' ';
			pKekka->ijkbnf = ' ';
			pKekka->ijkbnn = ' ';
		}
		else {
			/* �ُ�l�}�[�N�L��; */
			pKekka->ijkbnm = '*';
			pKekka->ijkbnf = '*';
			pKekka->ijkbnn = '*';
		}
		return 0;
	}

	/* �萫���ڂ̏ꍇ�A��l����̈ג萫�l�����Z�l�ɕϊ����� */
	if (pKekka->tstrflg == 'S') {
		/* �萫���� */
		/* ���ʃf�[�^�ɐ��l�ȊO�����邩�`�F�b�N */
		ikzn = chk_Mojikjn(wk_knskka,pKekka->knskka2kbn[0]);
		if(ikzn == 0){
			/* ���Z�l��������Ȃ����� */
			/* ��l�}�X�^�Ɋ�l�ݒ肪����ꍇ"*"�A */
			/* ��l�}�X�^�Ɋ�l�ݒ肪�Ȃ��ꍇ" " */
			/* ��ݒ肷�� */

			/* �j�� */
			trim(tmp1, pKjnmst->kjnmlw);
			trim(tmp2, pKjnmst->kjnmhi);
			if (strlen(tmp1) == 0 && strlen(tmp2) == 0) {
				pKekka->ijkbnm = ' ';
			}
			else {
				pKekka->ijkbnm = '*';
			}

			/* ���� */
			trim(tmp1, pKjnmst->kjnflw);
			trim(tmp2, pKjnmst->kjnfhi);
			if (strlen(tmp1) == 0 && strlen(tmp2) == 0) {
				pKekka->ijkbnf = ' ';
			}
			else {
				pKekka->ijkbnf = '*';
			}

			/* �s�� */
			trim(tmp1, pKjnmst->kjnelw);
			trim(tmp2, pKjnmst->kjnehi);
			if (strlen(tmp1) == 0 && strlen(tmp2) == 0) {
				pKekka->ijkbnn = ' ';
			}
			else {
				pKekka->ijkbnn = '*';
			}

			sFncPutLog (TRCKIND_DEBUG , __FILE__, "kjnChk1", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				    "ijkbn %c %c %c", pKekka->ijkbnm, pKekka->ijkbnf, pKekka->ijkbnn );
			/* �ُ�l�敪���ݒ肳�ꂽ�̂Ŕ����� */
			return 0;
		}

		/* ��l �� ���Z�l�ϊ��i�萫���ڂ̂݁j */
		/* �j��l�P */
		iwkkzn = chk_Mojikjn(pKjnmst->lwm1,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->lwm1,"%d",iwkkzn);
		}
		/* �j��l�Q */
		iwkkzn = chk_Mojikjn(pKjnmst->lwm2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->lwm2,"%d",iwkkzn);
		}
		/* �j��l�� */
		iwkkzn =  chk_Mojikjn(pKjnmst->kjnmlw,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjnmlw,"%d",iwkkzn);
		}
		/* �j��l���� */
		iwkkzn =  chk_Mojikjn(pKjnmst->kjm1,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjm1,"%d",iwkkzn);
		}
		/* �j���l�Q */
		iwkkzn =  chk_Mojikjn(pKjnmst->him2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->him2,"%d",iwkkzn);
		}
		/* �j���l�P */
		iwkkzn =  chk_Mojikjn(pKjnmst->him1,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->him1,"%d",iwkkzn);
		}
		/* �j��l�� */
		iwkkzn = chk_Mojikjn(pKjnmst->kjnmhi,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjnmhi,"%d",iwkkzn);
		}
		/* �j��l���� */
		iwkkzn =  chk_Mojikjn(pKjnmst->kjm2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjm2,"%d",iwkkzn);
		}
		/* ����l�P */
		iwkkzn = chk_Mojikjn(pKjnmst->lwf1,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->lwf1,"%d",iwkkzn);
		}
		/* ����l�Q */
		iwkkzn = chk_Mojikjn(pKjnmst->lwf2,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->lwf2,"%d",iwkkzn);
		}
		/* ����l�� */
		iwkkzn =  chk_Mojikjn(pKjnmst->kjnflw,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->kjnflw,"%d",iwkkzn);
		}
		/* ����l���� */
		iwkkzn =  chk_Mojikjn(pKjnmst->kjnnaf1,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->kjnnaf1,"%d",iwkkzn);
		}
		/* �����l�Q */
		iwkkzn =  chk_Mojikjn(pKjnmst->hif2,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->hif2,"%d",iwkkzn);
		}
		/* �����l�P */
		iwkkzn =  chk_Mojikjn(pKjnmst->hif1,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->hif1,"%d",iwkkzn);
		}
		/* ����l�� */
		iwkkzn =  chk_Mojikjn(pKjnmst->kjnfhi,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->kjnfhi,"%d",iwkkzn);
		}
		/* ����l���� */
		iwkkzn = chk_Mojikjn(pKjnmst->kjnnaf2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjnnaf2,"%d",iwkkzn);
		}
		/* �s����l�P */
		iwkkzn = chk_Mojikjn(pKjnmst->lwe1,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->lwe1,"%d",iwkkzn);
		}
		/* �s����l�Q */
		iwkkzn = chk_Mojikjn(pKjnmst->lwe2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->lwe2,"%d",iwkkzn);
		}
		/* �s����l�� */
		iwkkzn =  chk_Mojikjn(pKjnmst->kjnelw,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjnelw,"%d",iwkkzn);
		}
		/* �s����l���� */
		iwkkzn =  chk_Mojikjn(pKjnmst->kje1,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kje1,"%d",iwkkzn);
		}
		/* �s�����l�Q */
		iwkkzn =  chk_Mojikjn(pKjnmst->hie2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->hie2,"%d",iwkkzn);
		}
		/* �s�����l�P */
		iwkkzn =  chk_Mojikjn(pKjnmst->hie1,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->hie1,"%d",iwkkzn);
		}
		/* �s����l�� */
		iwkkzn =  chk_Mojikjn(pKjnmst->kjnehi,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjnehi,"%d",iwkkzn);
		}
		/* �s����l���� */
		iwkkzn =  chk_Mojikjn(pKjnmst->kje2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kje2,"%d",iwkkzn);
		}
	}
#define chknum1(p1, p2) 	((strncmp(p2, "        ", 8) != 0) && (p1 < atof(p2)))
#define chknum2(p1, p2) 	((strncmp(p2, "        ", 8) != 0) && (p1 > atof(p2)))

#define chknumi1(p1, p2)	((strncmp(p2, "        ", 8) != 0) && (p1 < atoi(p2)))
#define chknumi2(p1, p2)	((strncmp(p2, "        ", 8) != 0) && (p1 > atoi(p2)))

	if( ikzn == 0 ){
		rawData = atof(pKekka->knskka1);

		/* ��ʍ��ڂ̔�r(float float) */
		/* �j���̃`�F�b�N */
		pKekka->ijkbnm = '5';
		if chknum1(rawData , pKjnmst->lwm1) {
			pKekka->ijkbnm = '1';
		}
		else if chknum1(rawData, pKjnmst->lwm2) {
			pKekka->ijkbnm = '2';
		}
		else if chknum1(rawData, pKjnmst->kjnmlw) {
			pKekka->ijkbnm = '3';
		}
		else if chknum1(rawData, pKjnmst->kjm1) {
			pKekka->ijkbnm = '4';
		}
		else if chknum2(rawData, pKjnmst->him2) {
			pKekka->ijkbnm = '9';
		}
		else if chknum2(rawData, pKjnmst->him1) {
			pKekka->ijkbnm = '8';
		}
		else if chknum2(rawData, pKjnmst->kjnmhi) {
			pKekka->ijkbnm = '7';
		}
		else if chknum2(rawData, pKjnmst->kjm2) {
			pKekka->ijkbnm = '6';
		}
		/* �����̃`�F�b�N */
		pKekka->ijkbnf = '5';
		if chknum1(rawData, pKjnmst->lwf1) {
			pKekka->ijkbnf = '1';
		}
		else if chknum1(rawData, pKjnmst->lwf2) {
			pKekka->ijkbnf = '2';
		}
		else if chknum1(rawData, pKjnmst->kjnflw) {
			pKekka->ijkbnf = '3';
		}
		else if chknum1(rawData, pKjnmst->kjnnaf1) {
			pKekka->ijkbnf = '4';
		}
		else if chknum2(rawData, pKjnmst->hif2) {
			pKekka->ijkbnf = '9';
		}
		else if chknum2(rawData, pKjnmst->hif1) {
			pKekka->ijkbnf = '8';
		}
		else if chknum2(rawData, pKjnmst->kjnfhi) {
			pKekka->ijkbnf = '7';
		}
		else if chknum2(rawData, pKjnmst->kjnnaf2) {
			pKekka->ijkbnf = '6';
		}
		/* �s���̃`�F�b�N */
		pKekka->ijkbnn = '5';
		if chknum1(rawData, pKjnmst->lwe1) {
			pKekka->ijkbnn = '1';
		}
		else if chknum1(rawData, pKjnmst->lwe2) {
			pKekka->ijkbnn = '2';
		}
		else if chknum1(rawData, pKjnmst->kjnelw) {
			pKekka->ijkbnn = '3';
		}
		else if chknum1(rawData, pKjnmst->kje1) {
			pKekka->ijkbnn = '4';
		}
		else if chknum2(rawData, pKjnmst->hie2) {
			pKekka->ijkbnn = '9';
		}
		else if chknum2(rawData, pKjnmst->hie1) {
			pKekka->ijkbnn = '8';
		}
		else if chknum2(rawData, pKjnmst->kjnehi) {
			pKekka->ijkbnn = '7';
		}
		else if chknum2(rawData, pKjnmst->kje2) {
			pKekka->ijkbnn = '6';
		}
	}
	else{
		/* �萫�l�̊��Z�����������̂ŁA */
		/* ���Z�l�����[�f�[�^�Ƃ��Ĉ��� */

		/* �萫���ڂ̔�r */
		/* �j���̃`�F�b�N */
		pKekka->ijkbnm = '5';
		if chknumi1(ikzn , pKjnmst->lwm1) {
			pKekka->ijkbnm = '1';
		}
		else if chknumi1(ikzn, pKjnmst->lwm2) {
			pKekka->ijkbnm = '2';
		}
		else if chknumi1(ikzn, pKjnmst->kjnmlw) {
			pKekka->ijkbnm = '3';
		}
		else if chknumi1(ikzn, pKjnmst->kjm1) {
			pKekka->ijkbnm = '4';
		}
		else if chknumi2(ikzn, pKjnmst->him2) {
			pKekka->ijkbnm = '9';
		}
		else if chknumi2(ikzn, pKjnmst->him1) {
			pKekka->ijkbnm = '8';
		}
		else if chknumi2(ikzn, pKjnmst->kjnmhi) {
			pKekka->ijkbnm = '7';
		}
		else if chknumi2(ikzn, pKjnmst->kjm2) {
			pKekka->ijkbnm = '6';
		}
		/* �����̃`�F�b�N */
		pKekka->ijkbnf = '5';
		if chknumi1(ikzn, pKjnmst->lwf1) {
			pKekka->ijkbnf = '1';
		}
		else if chknumi1(ikzn, pKjnmst->lwf2) {
			pKekka->ijkbnf = '2';
		}
		else if chknumi1(ikzn, pKjnmst->kjnflw) {
			pKekka->ijkbnf = '3';
		}
		else if chknumi1(ikzn, pKjnmst->kjnnaf1) {
			pKekka->ijkbnf = '4';
		}
		else if chknumi2(ikzn, pKjnmst->hif2) {
			pKekka->ijkbnf = '9';
		}
		else if chknumi2(ikzn, pKjnmst->hif1) {
			pKekka->ijkbnf = '8';
		}
		else if chknumi2(ikzn, pKjnmst->kjnfhi) {
			pKekka->ijkbnf = '7';
		}
		else if chknumi2(ikzn, pKjnmst->kjnnaf2) {
			pKekka->ijkbnf = '6';
		}
		/* �s���̃`�F�b�N */
		pKekka->ijkbnn = '5';
		if chknumi1(ikzn, pKjnmst->lwe1) {
			pKekka->ijkbnn = '1';
		}
		else if chknumi1(ikzn, pKjnmst->lwe2) {
			pKekka->ijkbnn = '2';
		}
		else if chknumi1(ikzn, pKjnmst->kjnelw) {
			pKekka->ijkbnn = '3';
		}
		else if chknumi1(ikzn, pKjnmst->kje1) {
			pKekka->ijkbnn = '4';
		}
		else if chknumi2(ikzn, pKjnmst->hie2) {
			pKekka->ijkbnn = '9';
		}
		else if chknumi2(ikzn, pKjnmst->hie1) {
			pKekka->ijkbnn = '8';
		}
		else if chknumi2(ikzn, pKjnmst->kjnehi) {
			pKekka->ijkbnn = '7';
		}
		else if chknumi2(ikzn, pKjnmst->kje2) {
			pKekka->ijkbnn = '6';
		}
	}
		sFncPutLog (TRCKIND_DEBUG , __FILE__, "kjnChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			    "ijkbn %f %c %c %c", rawData, pKekka->ijkbnm, pKekka->ijkbnf, pKekka->ijkbnn );
	return 0;
}


/******************************************************************************/
/*	�� �� ��  �FfilterChk()							*/
/*	�@�\�T�v  �F�t�B���^�[�`�F�b�N						*/
/*	��	  ��  �F							*/
/*	 ��P���� �FpKekka	���ʏ��					*/
/*	�o	  ��  �F							*/
/*	���A���  �Fint 							*/
/*					 0	����				*/
/*					-1	�ُ�				*/
/******************************************************************************/
int filterChk(my_stKEKKA *pKekka, my_stKJNMST *pKjnmst)
{
	my_stKKAFLTMST	 *pKkafltmst;
	my_stKKAFLTMST	 sKkafltmst;
	int 		ret = 0;
	int 		Kkafltmstflg;
	int 		cnt = 0;
	int 		lCnt = 0;
	double		rawData;
	double		DataMax;
	double		DataMin;
	char		tmp[32];
	int 		mojiFlg = 0;
	char		errMsg[1024] = {0,};

	pKkafltmst = NULL;

	/* �t�B���^�[�}�X�^�[�ǂݏo�� */
	memset(&sKkafltmst, '\0', sizeof(sKkafltmst));
	strncpy(sKkafltmst.knsgrp, pKekka->knsgrp, 16);
	strncpy(sKkafltmst.kmkcd, pKekka->kmkcd, 7);
	strncpy(sKkafltmst.sstcd, pKekka->sstcd, 7);
	cnt = 0;

	ret = ZdbKkafltmstSelectGRPKMKKey(pKekka->knskisymd, &sKkafltmst, &pKkafltmst, &cnt);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"SQL CODE:%d ZdbKkafltmstSelectGRPKMKKey",ret);
		sFncPutLog (TRCKIND_ERROR , __FILE__, "filterChk", __LINE__,
				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			return(RET_CONTINUITY);
		}
		return(RET_STOP);
	}

	/* ���ʒl�̒l������𐔒l������ */
	memset(tmp, '\0', sizeof(tmp));
	trim(tmp, pKekka->knskka1);
	if ((tmp[0] >= '0'&&tmp[0]<='9') || tmp[0]=='+' || tmp[0]=='-' || tmp[0] == '.' ) {
		rawData = atof(tmp);
	}
	else {
		/* �����̂Ƃ��̓t�B���^�[�������s��Ȃ� */
		cnt = 0;
		mojiFlg = 1;
	}

	Kkafltmstflg = 0;
	if (cnt > 0) {
		for (lCnt = 0; lCnt < cnt; lCnt++) {
			/* ����E�����̒l������𐔒l������ */
			memset(tmp, '\0', sizeof(tmp));
			strncpy(tmp, pKkafltmst[lCnt].minval, 12);
			DataMin = atof(tmp);

			memset(tmp, '\0', sizeof(tmp));
			strncpy(tmp, pKkafltmst[lCnt].maxval, 12);
			DataMax = atof(tmp);

			if ((DataMin <= rawData) && (rawData <= DataMax)) {
				strncpy(pKekka->knskka1, pKkafltmst[lCnt].knskka1, 12);
				strncpy(pKekka->knskka2, pKkafltmst[lCnt].knskka2, 24);
				strncpy(pKekka->knskka2kbn, pKkafltmst[lCnt].knskka2kbn, 2);
				strncpy(pKekka->kkahskcd, pKkafltmst[lCnt].kkahskcd, 3);
				strncpy(pKekka->skkka, pKkafltmst[lCnt].hjkka, 24);	 /*  */
				if (pKjnmst->kjsstnksu == 9) {
					sprintf(tmp, "%.0f", (rawData + 0.00001));
				}
				else {
					sprintf(tmp, "%.*f", pKjnmst->kjsstnksu, (rawData + 0.00001));
				}
				strncpy(pKekka->hjkka, tmp, 24);
				Kkafltmstflg = 1;
				break;
			}
		}
	}
	if ((cnt <= 0) || (Kkafltmstflg == 0)) {
		/* �t�B���^�[�}�X�^�[�ɑ��݂��Ȃ��Ƃ� */
		/* �t�B���^�[�}�X�^�[�̏��Ńq�b�g���Ȃ������B */
		if (mojiFlg == 1) {
			strncpy(pKekka->knskka2, tmp, 24);
			strncpy(pKekka->knskka2kbn, "X", 2);
		}
		else if (pKjnmst->kjsstnksu == 9) {
			/* �����_�������X�̎��͒��l */
			sprintf(tmp, "%.0f", (rawData + 0.00001));
			strncpy(pKekka->knskka2, tmp, 24);
			strncpy(pKekka->knskka2kbn, "X", 2);
		}
		else {
			sprintf(tmp, "%.*f", pKjnmst->kjsstnksu, (rawData + 0.00001));
			if (pKekka->tstrflg == 'S') {		/* �萫 */
				strncpy(pKekka->knskka2, tmp, 24);
				strncpy(pKekka->knskka2kbn, "X", 2);
			}
			else if (pKekka->tstrflg == 'R') {	/* ��� */
				memset(pKekka->knskka1, ' ', 12);
				strcpy(&(pKekka->knskka1[12-strlen(tmp)]), tmp);
				strncpy(tmp, pKekka->knskka1, 32);
			}
			else {								/* �s�� */
				strncpy(pKekka->knskka2, tmp, 24);
				strncpy(pKekka->knskka2kbn, "X", 2);
			}
		}
		trim(pKekka->hjkka, tmp);			/* ���l(��ʎ��E�l�ɂȂ��Ă�����̂����l�ɕϊ�) */
		strncpy(pKekka->skkka, tmp, 24);	/* ��ʎ��E�l�E����ȊO���l */
	}
	if (pKkafltmst != NULL ) {
		free( pKkafltmst );
	}
	sFncPutLog (TRCKIND_DEBUG , __FILE__, "filterChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
		    "[%s][%s][%s][%s][%s]", pKekka->knskka1, pKekka->knskka2, pKekka->knskka2kbn, pKekka->hjkka, pKekka->skkka );
	return 0;
}

/******************************************************************************/
/*	�� �� ��  �FrngChk()							*/
/*	�@�\�T�v  �F�Č������W�`�F�b�N						*/
/*	��	  ��  �F							*/
/*	 ��P���� �FpCalc	�`�F�b�N�����					*/
/*	�o	  ��  �F							*/
/*	 ��Q���� �FpKekka	���ʏ��					*/
/*	���A���  �Fint 							*/
/*					 0	����				*/
/*					-1	�ُ�				*/
/******************************************************************************/
int rngChk(my_stCALC *pCalc, my_stKEKKA *pKekka)
{
	my_stRNGCHKMST	sRngchkmst;
	my_stRNGCHKMST	*pRngchkmst;
	int 		cnt = 0;
	int 		ret = 0;
	double		rawData = 0.0;
	char		cRawBuf[256];
	char		errMsg[1024] = {0,};

	pRngchkmst = NULL;

	/* ���f�[�^���Ȃ�(�X�y�[�Xor/)�̏ꍇ�Ȃɂ����Ȃ� */
	memset(cRawBuf, '\0', sizeof(cRawBuf));
	trim(cRawBuf, pKekka->knskka1);
	if( cRawBuf[0]	== '\0' || cRawBuf[0]  == '/' )
		return 0;

	memset(&sRngchkmst, '\0', sizeof(my_stRNGCHKMST));
	/* �͈͋敪�������ɒǉ� */
	sRngchkmst.hnikbn = RNG_CHK;
	strncpy(sRngchkmst.knsgrp, pKekka->knsgrp, 16);
	strncpy(sRngchkmst.kmkcd, pKekka->kmkcd, 7);
	strncpy(sRngchkmst.sstcd, pKekka->sstcd, 7);
	if ((strncmp(pCalc->zrcd, "001", 3) == 0)
		|| (strncmp(pCalc->zrcd, "002", 3) == 0)) {
		strncpy(sRngchkmst.zaicd, pCalc->zrcd, 4);
	}
	else {
		strncpy(sRngchkmst.zaicd, "000 ", 4);
	}
	sRngchkmst.sbt = pCalc->sbtkbn[0];
	/* �{�݃R�[�h�A���ʋ敪���w�肵�Č��� */
	ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING , __FILE__, "BmlPanicChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncPutLog (TRCKIND_ERROR , __FILE__, "BmlPanicChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
		return(RET_STOP);

	}
	/* ������Ȃ������ꍇ�A�{�݃R�[�h���w��A���ʋ敪���I�[��(' ')�Ŏw�肵�Č���*/
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, pKekka->sstcd, 7);
		sRngchkmst.sbt = ' ';
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "BmlPanicChk",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncPutLog (TRCKIND_ERROR, __FILE__, "BmlPanicChk",__LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_STOP);
		}
	}
	/* ����Ɍ�����Ȃ������ꍇ�A���ʋ敪���w�肵�A�{�݃R�[�h���I�[��(0000000)�Ŏw�肵�Č���*/
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, "0000000", 7);
		sRngchkmst.sbt = pCalc->sbtkbn[0];
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectKey2",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING , __FILE__, "BmlPanicChk", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncPutLog (TRCKIND_ERROR , __FILE__, "BmlPanicChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_STOP);
		}
	}
	/* ����ł�������Ȃ������ꍇ�A�{�݃R�[�h�A���ʋ敪���ɃI�[���w��Ō��� */
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, "0000000", 7);
		sRngchkmst.sbt = ' ';
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING , __FILE__, "rngChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncPutLog (TRCKIND_ERROR , __FILE__, "rngChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_STOP);
		}
	}
	if (ret != HRC_SQL_NOT_FOUND) {
		int 	lCnt;
		rawData = atof(pKekka->knskka1);
		pKekka->renjicflg = '1';
		for (lCnt = 0; lCnt < cnt; lCnt++) {
			if ( pRngchkmst[lCnt].ssa == '1'){
				if (atof(pRngchkmst[lCnt].hrng) < rawData) {
					pKekka->renjicflg = '3';
					pKekka->knsflg = 'A';
					break;
				}
			}
			else if ( pRngchkmst[lCnt].ssa == '2'){
				if (atof(pRngchkmst[lCnt].lrng) > rawData) {
					pKekka->renjicflg = '4';
					pKekka->knsflg = 'A';
					break;
				}
			}
		}
	}
	if ( pRngchkmst != NULL ){
		free( pRngchkmst );
	};

	sFncPutLog (TRCKIND_DEBUG , __FILE__, "rngChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "[%s][%s][%s][%s][%s][%c]", 
		pKekka->knskka1, pKekka->knskka2, pKekka->knskka2kbn, pKekka->hjkka, pKekka->skkka, pKekka->renjicflg );
	return( 0 );
}

/******************************************************************************/
/*	�� �� ��  �FBmlPanicChk()						*/
/*	�@�\�T�v  �F�a�l�k�p�j�b�N�`�F�b�N					*/
/*	��	  ��  �F							*/
/*	 ��P���� �FpKekka	���ʏ��					*/
/*	�o	  ��  �F							*/
/*	���A���  �Fint 							*/
/*					 0	����				*/
/*					-1	�ُ�				*/
/******************************************************************************/
int BmlPanicChk(my_stCALC *pCalc, my_stKEKKA *pKekka)
{
	my_stRNGCHKMST	sRngchkmst;
	my_stRNGCHKMST	*pRngchkmst;
	int 		cnt = 0;
	int 		ret = 0;
	double		rawData = 0.0;
	char		cRawBuf[256];
	char		errMsg[1024] = {0,};

	pRngchkmst = NULL;

	/* ���f�[�^���Ȃ�(�X�y�[�Xor/)�̏ꍇ�Ȃɂ����Ȃ� */
	memset(cRawBuf, '\0', sizeof(cRawBuf));
	trim(cRawBuf, pKekka->knskka1);
	if( cRawBuf[0]	== '\0' || cRawBuf[0]  == '/' )
		return 0;

	memset(&sRngchkmst, '\0', sizeof(my_stRNGCHKMST));
	/* �͈͋敪�������ɒǉ� */
	sRngchkmst.hnikbn = BML_PANIC;
	strncpy(sRngchkmst.knsgrp, pKekka->knsgrp, 16);
	strncpy(sRngchkmst.kmkcd, pKekka->kmkcd, 7);
	strncpy(sRngchkmst.sstcd, pKekka->sstcd, 7);
	if ((strncmp(pCalc->zrcd, "001", 3) == 0)
		|| (strncmp(pCalc->zrcd, "002", 3) == 0)) {
		strncpy(sRngchkmst.zaicd, pCalc->zrcd, 4);
	}
	else {
		strncpy(sRngchkmst.zaicd, "000 ", 4);
	}
	sRngchkmst.sbt = pCalc->sbtkbn[0];
	/* �{�݃R�[�h�A���ʋ敪���w�肵�Č��� */
	ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING , __FILE__, "BmlPanicChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncPutLog (TRCKIND_ERROR , __FILE__, "BmlPanicChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
		return(RET_STOP);

	}
	/* ������Ȃ������ꍇ�A�{�݃R�[�h���w��A���ʋ敪���I�[��(' ')�Ŏw�肵�Č���*/
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, pKekka->sstcd, 7);
		sRngchkmst.sbt = ' ';
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "BmlPanicChk",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncPutLog (TRCKIND_ERROR, __FILE__, "BmlPanicChk",__LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_STOP);
		}
	}
	/* ����Ɍ�����Ȃ������ꍇ�A���ʋ敪���w�肵�A�{�݃R�[�h���I�[��(0000000)�Ŏw�肵�Č���*/
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, "0000000", 7);
		sRngchkmst.sbt = pCalc->sbtkbn[0];
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectKey2",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING , __FILE__, "BmlPanicChk", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncPutLog (TRCKIND_ERROR , __FILE__, "BmlPanicChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_STOP);
		}
	}
	/* ����ł�������Ȃ������ꍇ�A�{�݃R�[�h�A���ʋ敪���ɃI�[���w��Ō��� */
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, "0000000", 7);
		sRngchkmst.sbt = ' ';
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING , __FILE__, "BmlPanicChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncPutLog (TRCKIND_ERROR , __FILE__, "BmlPanicChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_STOP);
		}
	}
	if (ret != HRC_SQL_NOT_FOUND) {
		int 	lCnt;
		rawData = atof(pKekka->knskka1);
		pKekka->pncrgflg = '0';
		for (lCnt = 0; lCnt < cnt; lCnt++) {
			if ((atof(pRngchkmst[lCnt].hrng) >= rawData) &&
				(rawData >= atof(pRngchkmst[lCnt].lrng))) {
				pKekka->pncrgflg = '0';
			}
			else {
				pKekka->pncrgflg = '1';
				break;
			}
		}
	}
	if ( pRngchkmst != NULL ){
		free( pRngchkmst );
	};

	sFncPutLog (TRCKIND_DEBUG , __FILE__, "BmlPanicChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "[%s][%s][%s][%s][%s][%c]", 
			pKekka->knskka1, pKekka->knskka2, pKekka->knskka2kbn, pKekka->hjkka, pKekka->skkka, pKekka->pncrgflg );
	return 0;
}

/******************************************************************************/
/*  �� �� ��  �FKnsPanicChk()                                                 */
/*  �@�\�T�v  �F�������p�j�b�N�`�F�b�N                                        */
/*  ��    ��  �F                                                              */
/*   ��P���� �FpKekka  ���ʏ��                                              */
/*  �o    ��  �F                                                              */
/*  ���A���  �Fint                                                           */
/*                   0  ����                                                  */
/*                  -1  �ُ�                                                  */
/******************************************************************************/
int KnsPanicChk(my_stCALC *pCalc, my_stKEKKA *pKekka)
{
	my_stRNGCHKMST   sRngchkmst;
	my_stRNGCHKMST   *pRngchkmst;
	int         cnt = 0;
	int         ret = 0;
	double      rawData = 0.0;
	char        cRawBuf[256];
	char        errMsg[1024] = {0,};

	pRngchkmst = NULL;

	/* ���f�[�^���Ȃ�(�X�y�[�Xor/)�̏ꍇ�Ȃɂ����Ȃ� */
	memset(cRawBuf, '\0', sizeof(cRawBuf));
	trim(cRawBuf, pKekka->knskka1);
	if( cRawBuf[0]	== '\0' || cRawBuf[0]  == '/' )
		return 0;

	memset(&sRngchkmst, '\0', sizeof(my_stRNGCHKMST));
	/* �͈͋敪�������ɒǉ�(�������p�j�b�N�̂ݎ擾) */
	sRngchkmst.hnikbn = KNS_PANIC;
	strncpy(sRngchkmst.knsgrp, pKekka->knsgrp, 16);
	strncpy(sRngchkmst.kmkcd, pKekka->kmkcd, 7);
	strncpy(sRngchkmst.sstcd, pKekka->sstcd, 7);
	if ((strncmp(pCalc->zrcd, "001", 3) == 0) || (strncmp(pCalc->zrcd, "002", 3) == 0)) {
		strncpy(sRngchkmst.zaicd, pCalc->zrcd, 4);
	}
	else {
		strncpy(sRngchkmst.zaicd, "000 ", 4);
	}
	sRngchkmst.sbt = pCalc->sbtkbn[0];
	/* �{�݃R�[�h�A���ʋ敪���w�肵�Č��� */
	ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING , __FILE__, "KnsPanicChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncPutLog (TRCKIND_ERROR , __FILE__, "KnsPanicChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
		return(RET_STOP);

	}
	/* ������Ȃ������ꍇ�A�{�݃R�[�h���w��A���ʋ敪���I�[��(' ')�Ŏw�肵�Č���*/
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, pKekka->sstcd, 7);
		sRngchkmst.sbt = ' ';
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "KnsPanicChk",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncPutLog (TRCKIND_ERROR, __FILE__, "KnsPanicChk",__LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_STOP);
		}
	}
	/* ����Ɍ�����Ȃ������ꍇ�A���ʋ敪���w�肵�A�{�݃R�[�h���I�[��(0000000)�Ŏw�肵�Č���*/
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, "0000000", 7);
		sRngchkmst.sbt = pCalc->sbtkbn[0];
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectKey2",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING , __FILE__, "KnsPanicChk", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncPutLog (TRCKIND_ERROR , __FILE__, "KnsPanicChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_STOP);
		}
	}
	/* ����ł�������Ȃ������ꍇ�A�{�݃R�[�h�A���ʋ敪���ɃI�[���w��Ō��� */
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, "0000000", 7);
		sRngchkmst.sbt = ' ';
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING , __FILE__, "KnsPanicChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncPutLog (TRCKIND_ERROR , __FILE__, "KnsPanicChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_STOP);
		}
	}
	if (ret != HRC_SQL_NOT_FOUND) {
		int 	lCnt;
		rawData = atof(pKekka->knskka1);
		pKekka->knspncrgflg = '0';
		for (lCnt = 0; lCnt < cnt; lCnt++) {
			if ((atof(pRngchkmst[lCnt].hrng) >= rawData) &&
				(rawData >= atof(pRngchkmst[lCnt].lrng))) {
				pKekka->knspncrgflg = '0';
			}
			else {
				pKekka->knspncrgflg = '1';
				break;
			}
		}
	}
	if ( pRngchkmst != NULL ){
		free( pRngchkmst );
	};

	sFncPutLog (TRCKIND_DEBUG , __FILE__, "KnsPanicChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "[%s][%s][%s][%s][%s][%c]", 
			pKekka->knskka1, pKekka->knskka2, pKekka->knskka2kbn, pKekka->hjkka, pKekka->skkka, pKekka->knspncrgflg );
	return 0;
}

/******************************************************************************/
/*	�� �� ��  �FKeisanChk() 						*/
/*	�@�\�T�v  �F�v�Z�`�F�b�N						*/
/*	��	  ��  �F							*/
/*	 ��P���� �FpKekka	���ʏ��					*/
/*	�o	  ��  �F							*/
/*	���A���  �Fint 							*/
/*					 0	����				*/
/*					-1	�ُ�				*/
/******************************************************************************/
int KeisanChk(my_stCALC *pCalc, char *sKSNSK, my_stKEKKA *pCalcKka, char *sKnsflg, int kjsstnksu, int KekkaOtherFlg )
{
	char		calBuff[1024];
	int 		ret;
	char		rawData[64];
	char		knskka2kbn[2+1];
	char		kkahskcd[3+1];
	char		knsflg[1+1];
	int 		iCnt;	/* ���[�v�J�E���^ */
	int 		setCnt;
	int 		tmpCnt;
	char		getKmkcd[32];
	double		calNum = 0.0;

	char *pszExpandKSNSK = (char *) NULL; /* IF ���W�J��̌v�Z��              */
	sKnsflg[0] = '\0';

	/* �����̍��ڃR�[�h�𐔒l�ɒu��������B */
	memset(calBuff, '\0', sizeof(calBuff));
	for (iCnt = 0, setCnt = 0; iCnt < 128; iCnt++ ) {
		/* ���ڃR�[�h�̎n�܂�'['����������B */
		if (sKSNSK[iCnt] == '[') {
			/* ���ڒl������ */
			memset(getKmkcd, '\0', sizeof(getKmkcd));
			tmpCnt = 0;
			iCnt++;
			/* ���ڃR�[�h��]���i�I���ʒu��]��Null�܂Łj */
			while (sKSNSK[iCnt] != ']' && sKSNSK[iCnt] != '\0') {
				getKmkcd[tmpCnt++] = sKSNSK[iCnt++];
			}
			/* ���ʏ��A�������͑��T�e���C�g���ʏ�񂩂�w��̍��ڃR�[�h���������A�u��������B */
			memset(knsflg,'\0', sizeof(knsflg));
			ret = ZdbSelCalcSource(pCalc->utkymd, pCalc->irino, pCalc->kmkcd, getKmkcd, rawData, kkahskcd, knskka2kbn, knsflg, KekkaOtherFlg);
			if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
				if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
					return(RET_CONTINUITY);
				}
				return (RET_STOP);
			}
			if (ret == HRC_SQL_NOT_FOUND) {
				return(RET_CONTINUITY);
			}
			/* �v�Z���ɃR�����g���ʁA�������͌��ʕ⑫�R�[�h�������Ă����ꍇ�A�v�Z���G���[�Ƃ���B */
			if (knskka2kbn[0] == '0' || strcmp(kkahskcd , "   ") != 0) {
				ret = ZdbInsNotCalc( pCalc );
				if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
					if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
						return(RET_CONTINUITY);
					}
					return (RET_STOP);
				}
				return(RET_CONTINUITY);
			}
			/* �v�Z�����ڂɌ����t���O�`�̍��ڂ��������ꍇ�A�񍐂ł��Ȃ��悤�Ɍ����t���O��ݒ肷��B */
			if (knsflg[0] == 'A') {
				sKnsflg[0] = 'A';
				sKnsflg[1] = '\0';
			}
			strncat(calBuff, rawData, 21);
			setCnt = strlen(calBuff);
		}
		else if (KSNSK_SC == (int) sKSNSK[iCnt]) {
			/* �g�� */
			/* ���p�\�Ȓl�ȊO���w�肳��Ă����ꍇ�A�v�Z���Ȃ� */
			if (strncmp(pCalc->sc ,"     ", 5) == 0 ){
				return(RET_CONTINUITY);
			}
			memcpy((void *) gszTransfer, pCalc->sc, FLDSIZE_SC);
			gszTransfer[FLDSIZE_SC] = (char) '\0';
			if (0 == _isnumeric(gszTransfer)) {
				gszTransfer[0] = (char) '0';
				gszTransfer[1] = (char) '\0';
				return(RET_CONTINUITY);
			}
			strcat(calBuff, gszTransfer);
			setCnt = strlen(calBuff);
		}
		else if (KSNSK_TJ == (int) sKSNSK[iCnt]) {
			/* POW�Ƌ�ʂ��邽�߁A�O�̕�����O�Ŗ������`�F�b�N����B */
			if (sKSNSK[iCnt-1] != 'o' || sKSNSK[iCnt-1] != 'O') {
				if (strncmp(pCalc->tj ,"     ", 5) == 0 ){
					return(RET_CONTINUITY);
				}
				/* �̏d */
				strncpy(gszTransfer, pCalc->tj, FLDSIZE_TJ);
				/* ���p�\�Ȓl�ȊO���w�肳��Ă����ꍇ�A�v�Z���Ȃ� */
				gszTransfer[FLDSIZE_TJ] = (char) '\0';
				if (0 == _isnumeric(gszTransfer)) {
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
					return(RET_CONTINUITY);
				}
				else {
					/* �̏d�� kg �ȊO�͂m�f */
					if( ((int)pCalc->tjtni[0]) !=  _VALUE_TJTNI_KILLOGRAM) {
						gszTransfer[0] = (char) '0';
						gszTransfer[1] = (char) '\0';
						return(RET_CONTINUITY);
					}
				}
				strcat(calBuff, gszTransfer);
				setCnt = strlen(calBuff);
			}
		}
		else if (KSNSK_TNTME == (int) sKSNSK[iCnt]) {
			/* �~�A���� */
			/* ���p�\�Ȓl�ȊO���w�肳��Ă����ꍇ�A�v�Z���Ȃ� */
			memcpy((void *) gszTransfer, pCalc->tntme, FLDSIZE_TNTME);
			gszTransfer[FLDSIZE_TNTME] = (char) '\0';
			if (0 == _isnumeric(gszTransfer)) {
				gszTransfer[0] = (char) '0';
				gszTransfer[1] = (char) '\0';
				return(RET_CONTINUITY);
			}
			else {
				/* �~�A���Ԃ� ����(h) �ȊO�͂m�f */
				if( ((int) pCalc->tntni[0]) != _VALUE_TNTNI_HOUR ) {
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
					return(RET_CONTINUITY);
				}
			}
			strcat(calBuff, gszTransfer);
			setCnt = strlen(calBuff);
		}
		else if (KSNSK_TNRYO == (int) sKSNSK[iCnt]) {
			/* �~�A�� */
			/* ���p�\�Ȓl�ȊO���w�肳��Ă����ꍇ�A�v�Z���Ȃ� */
			memcpy((void *) gszTransfer, pCalc->tnryo, FLDSIZE_TNRYO);
			gszTransfer[FLDSIZE_TNRYO] = (char) '\0';
			if (0 == _isnumeric(gszTransfer)) {
				gszTransfer[0] = (char) '0';
				gszTransfer[1] = (char) '\0';
				return(RET_CONTINUITY);
			}
			else {
				/* �~�A�ʂ� ml �ȊO�͂m�f */
				if( ((int) pCalc->tnryotni[0]) != _VALUE_TNRYO_MILLILITER ) {
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
					return(RET_CONTINUITY);
				}
			}
			strcat(calBuff, gszTransfer);
			setCnt = strlen(calBuff);
		}
		else if (KSNSK_SBTKBN == (int) sKSNSK[iCnt]) {
			/* ���ʋ敪 */
			if (_VALUE_SBTKBN_MALE == (int) pCalc->sbtkbn[0] ||
					_VALUE_SBTKBN_FEMALE == (int) pCalc->sbtkbn[0]) {
				strncat(calBuff, &(pCalc->sbtkbn[0]), sizeof(pCalc->sbtkbn[0]));
				setCnt = strlen(calBuff);
			}
			else {
				calBuff[setCnt++] = (char) _VALUE_SBTKBN_UNKNOWN;
				calBuff[setCnt] = (char) '\0';
				/* ���ʕs���������ꍇ�A�v�Z���Ȃ� */
				return(RET_CONTINUITY);
			}
		}
		else if (KSNSK_AGE == (int) sKSNSK[iCnt]) {
			if (strncmp(pCalc->age ,"   ", 3) == 0 ){
				return(RET_CONTINUITY);
			}
			/* �N��	*/
			if (_VALUE_AGEKBN_YEAR != (int) pCalc->agekbn[0]) {
				calBuff[setCnt++] = (char) '0';
				calBuff[setCnt] = (char) '\0';
				/* �N��敪�� �� �ȊO�������ꍇ�A�v�Z���Ȃ� */
				return(RET_CONTINUITY);
			}
			else {
				memcpy((void *) gszTransfer, pCalc->age, FLDSIZE_AGE);
				gszTransfer[FLDSIZE_AGE] = (char) '\0';
				if (0 == _isnumeric(gszTransfer)) {
					/* ���p�\�Ȓl�ȊO���w�肳��Ă����ꍇ�A�v�Z���Ȃ� */
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
					return(RET_CONTINUITY);
				}
				strcat(calBuff, gszTransfer);
				setCnt = strlen(calBuff);
			}
		}
		else if (sKSNSK[iCnt] == '\0') {
			break;
		}
		else {
			calBuff[setCnt++] = sKSNSK[iCnt];
		}
	}

	/* �v�Z���Ɋ܂܂�� IF ���̓W�J                                         */
	if (NULL != (void *) (pszExpandKSNSK = OperateKSNSK(calBuff))) {
		if ('\0' != (int) *pszExpandKSNSK) {
			sFncPutLog (TRCKIND_TRACE, __FILE__, "KeisanChk",__LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�v�Z��[%s]", pszExpandKSNSK ) ;
			strcpy(calBuff, pszExpandKSNSK);
		}
		free((void *) pszExpandKSNSK);
		pszExpandKSNSK = (char *) NULL;
	}


	/* ������̌v�Z�����v�Z����B */
	calNum = StringCal(calBuff);
	if( isfinite(calNum) == 0 ){
		/* �O���Z�╉�̒l��log���A����Ɍv�Z�ł��Ȃ����ƂȂ����ꍇ */
		sFncPutLog (TRCKIND_ERROR , __FILE__, "KeisanChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
					  "�v�Z���ʂ������ł͂���܂���B utkymd: %s irino: %s kmkcd:%s", pCalc->utkymd, pCalc->irino, pCalc->kmkcd) ;

		sprintf( pCalcKka->rawdata, "                    ");
		sprintf( pCalcKka->knskka1, "            ");
		sprintf( pCalcKka->knskka2, "                        " );
		sprintf( pCalcKka->knskka2kbn, "  " );
		sprintf( pCalcKka->kkahskcd, "   " );
		/* �񍐂ł��Ȃ��悤�Ɍ����t���O��ݒ肷��B */
		sKnsflg[0] = 'A';
		sKnsflg[1] = '\0';
	}
	else {
		snprintf( pCalcKka->rawdata, 21, "%-20f", calNum);
		if( kjsstnksu == 9 ) {
			snprintf( pCalcKka->knskka1, 13, "%-12f", calNum);
		}
		else {
			/* �ۂ� */
			calNum = calNum * pow( 10, kjsstnksu );
			calNum = round( calNum );
			calNum /= pow(10, kjsstnksu );
			snprintf( pCalcKka->knskka1, 13, "%12.*f", kjsstnksu, calNum );
		}
		sprintf( pCalcKka->knskka2, "                        " );
		sprintf( pCalcKka->knskka2kbn, "  " );
		sprintf( pCalcKka->kkahskcd, "   " );

		sFncPutLog (TRCKIND_DEBUG, __FILE__, "KeisanChk",__LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			    "(%f)(%s)(%s)", calNum, pCalcKka->rawdata, pCalcKka->knskka1) ;
	}

	return 0;
}
/******************************************************************************/
/*	�� �� ��  �FStringCal_sub() 						*/
/*	�@�\�T�v  �F�w�肳�ꂽ���Z�q�ƒl�Ŏl�����Z�s��				*/
/*	��	  ��  �F							*/
/*	 ��P���� �Fenzan	:	���Z�q					*/
/*	 ��Q���� �Fval1	:	�l�P					*/
/*	 ��R���� �Fval2	:	�l�Q					*/
/*	�o	  ��  �F							*/
/*	���A���  �Fdouble	�v�Z����					*/
/******************************************************************************/
double StringCal_sub(char enzan,double val1,double val2)
{
	sFncPutLog (TRCKIND_DEBUG, __FILE__, "StringCal_sub",__LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
		    "enzan(%c) val1(%f) val2(%f)", enzan, val1, val2) ;
	switch ( enzan ) {
	case '+':
		return (val1 + val2);
		break;
	case '-':
		return (val1 - val2);
		break;
	case '/':
		return (val1 / val2);
		break;
	case '*':
		return (val1 * val2);
		break;
	}
	return(0);
}

/****************************************************************************************/
/*	�� �� ��  �FStringCal() 							*/
/*	�@�\�T�v  �F�n���ꂽ������̌v�Z�����s��					*/
/*	��	  ��  �F								*/
/*	 ��P���� �FCalStr	:	�v�Z������					*/
/*	�o	  ��  �F								*/
/*	���A���  �Fdouble	�v�Z����						*/
/*											*/
/*	���ӁF	�Ή����鉉�Z�q�́u+ - * /�v���\�ł���B				*/
/*			����ȊO��LOG�ALOG10�APOW��3�̌v�Z���s���B			*/
/*			�v�Z�̗D�揇�ʂ́A�l�����Z�̗D�揇�ʂɏ]��*��/���D�悳���B	*/
/****************************************************************************************/
double StringCal(char *CalStr)
{
	char		StacEn;
	double		StacNum;
	int 		flg;
	int 		loopCnt, strCnt;
	double		ret;
	char		cStacNum[1024];
	char		cStacNum2[1024];
	double		tmpStacNum;
	char		cChk[16];
	int 		i, c;
	double		StacRet[10];
	char		StacEnc[10];
	char		StacFlg[10];
	int 		StacCnt;


	ret = 0.0;
	StacEn = '+';
	flg = FALSE;
	strCnt = 0;
	StacCnt = 0;
	for(loopCnt = 0; loopCnt < strlen(CalStr); loopCnt ++) {
		switch (CalStr[loopCnt]) {
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.':
			/* ���l�̎� */
			break;
		case '+': case '-': case '/': case '*':
			/* ���Z�q�̎� */
			if (flg == FALSE) {
				if (strCnt >= loopCnt) {
					StacNum = 0.0;
				}
				else {
					for (c = 0, i = strCnt; i < loopCnt; c++, i++) {
						cStacNum[c] = CalStr[i];
					}
					cStacNum[c] = '\0';
					StacNum = atof(cStacNum);
				}
			}

			if ((StacEn == '+' || StacEn == '-') && (CalStr[loopCnt] == '*' || CalStr[loopCnt] == '/')) {
				StacFlg[StacCnt] = StacEn;
				StacRet[StacCnt] = ret;
				StacEnc[StacCnt] = StacEn;
				StacCnt += 1;

				flg = FALSE;
				ret = StacNum;
				StacEn = CalStr[loopCnt];
				strCnt = loopCnt + 1;
			}
			else if ((StacEn == '*' || StacEn == '/') && (CalStr[loopCnt] == '+' || CalStr[loopCnt] == '-')) {
				ret = StringCal_sub(StacEn, ret, StacNum);
				flg = FALSE;
				StacEn = CalStr[loopCnt];
			}
			else if ((StacCnt > 0) && (StacEnc[StacCnt-1] == '+' || StacEnc[StacCnt-1] == '-') &&
					 (StacFlg[StacCnt-1] != '(') && (CalStr[loopCnt] == '+' || CalStr[loopCnt] == '-')) {
				ret = StringCal_sub(StacEnc[StacCnt-1], StacRet[StacCnt-1], ret);
				StacCnt -= 1;
				ret = StringCal_sub(StacEn, ret, StacNum);
				flg = FALSE;
				StacEn = CalStr[loopCnt];
			}
			else {
				ret = StringCal_sub(StacEn, ret, StacNum);
				flg = FALSE;
				StacEn = CalStr[loopCnt];
			}

			strCnt = loopCnt + 1;
			break;
		case 'L': case 'l':
			/* LOG�y��LOG10�̎� */
			/* LOG�y��LOG10�����v�Z���ɂȂ��Ă���ꍇ�ɂ��Ă͑Ή����Ă��Ȃ� */
			for (c = 0, i = loopCnt; CalStr[i] != '(' && CalStr[i] != '\0'; c++, i++) {
				cChk[c] = toupper(CalStr[i]);
			}
			cChk[c] = '\0';
			if (strcmp(cChk , "LOG10") == 0) {
				for (c = 0, i = loopCnt + 6; CalStr[i] != ')' && CalStr[i] != '\0'; c++, i++) {
					cStacNum[c] = CalStr[i];
				}
				cStacNum[c] = '\0';
				StacNum = log10(atof(cStacNum));
				flg = TRUE;
				loopCnt += i;
			}
			else if (strcmp(cChk , "LOG") == 0) {
				for (c = 0, i = loopCnt + 4; CalStr[i] != ')' && CalStr[i] != '\0'; c++, i++) {
					cStacNum[c] = CalStr[i];
				}
				cStacNum[c] = '\0';
				StacNum = atof(cStacNum);
				StacNum = log(StacNum);
				flg = TRUE;
				loopCnt += i;
			}
			break;
		case 'P': case 'p':
			/* POW�̎� */
			for (c = 0, i = loopCnt; CalStr[i] != '(' && CalStr[i] != '\0'; c++, i++) {
				cChk[c] = toupper(CalStr[i]);
			}
			cChk[c] = '\0';
			if (strcmp(cChk, "POW") == 0) {
				for (c = 0, i = loopCnt + 4; CalStr[i] != ':' && CalStr[i] != '\0'; c++, i++) {
					cStacNum[c] = CalStr[i];
				}
				cStacNum[c] = '\0';
				/* POW�̒ꂪ�v�Z���ɂȂ��Ă���ꍇ������̂ŁA�ċA�Ăяo���Ōv�Z����B */
				/* �H���ێ�ʑΉ��B���������̓��ʏ����B���̃v���O�����̌v�Z���W�b�N�ł͑Ή����Ă��Ȃ� */
				tmpStacNum = 0.0 ;
				tmpStacNum = StringCal(cStacNum);
				for (c = 0, i += 1; CalStr[i] != ':' && CalStr[i] != ')' && CalStr[i] != '\0'; c++, i++) {
					cStacNum2[c] = CalStr[i];
				}
				cStacNum2[c] = '\0';
				/* �w�����v�Z���ɂȂ��Ă���ꍇ�ɂ��Ă͑Ή����Ă��Ȃ� */
				StacNum = pow(tmpStacNum, atof(cStacNum2));
				sFncPutLog (TRCKIND_DEBUG, __FILE__, "StringCal pow",__LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
							"StacNum[%f] tmpStacNum[%f] cStacNum2[%s] cStacNum[%s]",
							 StacNum, tmpStacNum, cStacNum2, cStacNum ) ;
				flg = TRUE;
				loopCnt = i;
			}
			break;
		case '(':
			StacFlg[StacCnt] = '(';
			StacRet[StacCnt] = ret;
			StacEnc[StacCnt] = StacEn;
			StacCnt++;
			ret = 0.0;
			StacEn = '+';
			strCnt = loopCnt + 1;
			break;
		case ')':
			if (flg == FALSE) {
				if (strCnt >= loopCnt) {
					StacNum = 0.0;
				}
				else {
					for (c = 0, i = strCnt; i < loopCnt; c++, i++) {
						cStacNum[c] = CalStr[i];
					}
					cStacNum[c] = '\0';
					StacNum = atof(cStacNum);
				}
			}

			StacNum = StringCal_sub(StacEn, ret, StacNum);
			flg = TRUE;

			StacCnt--;
			StacEn = StacEnc[StacCnt];
			ret = StacRet[StacCnt];
			strCnt = loopCnt + 1;
			break;
		}
	}
	if (flg == FALSE) {
		for (c = 0, i = strCnt; i < loopCnt; c++, i++) {
			cStacNum[c] = CalStr[i];
		}
		cStacNum[c] = '\0';
		StacNum = atof(cStacNum);
	}
	ret = StringCal_sub(StacEn, ret, StacNum);
	if (StacCnt > 0) {
		while (StacCnt > 0) {
			StacCnt -= 1;
			StacEn = StacEnc[StacCnt];
			StacNum = StacRet[StacCnt];
			ret = StringCal_sub(StacEn, StacNum, ret);
		}
	}
	return ret;
}

/**/
int chk_Mojikjn(input,kbn)
/*****************************************************************************
*fc
	��l(������f�[�^)�̊��Z�l�擾
	�i�P�O�[�@�`�@�P�O�{�@�̐��l�ϊ��j
*rt
	���Z�l	 ... ��l(������f�[�^)�̊��Z�l
	BAD_DATA ... ��l(������f�[�^)�ɊY�����銷�Z�l���Ȃ�
*nt
*ag
*****************************************************************************/
char *input;
char kbn;
{
	int 	ret;
	int 	cnt;
	char	wk_input[20];

	ret = 0;

	trim(wk_input, input);

	if(wk_input[0] == '\0'){
		/* �X�y�[�X�Ȃ�I�� */
		return 0;
	}

	if( kbn == 'X' ){
		for(cnt = 1; KZN_Teisei[cnt] != NULL ; cnt++){
			if(memcmp(KZN_Teisei[cnt],"END",3) == 0){
				/* END�Ȃ甲���� */
				break;
			}
			if(memcmp(KZN_Teisei[cnt],wk_input,strlen(wk_input)) == 0){
				ret = cnt;
				break;
			}
		}
	}

	if( kbn == '0' ){
		for(cnt = 1; KZN_Coment[cnt] != NULL ; cnt++){
			if(memcmp(KZN_Coment[cnt],"END",3) == 0){
				/* END�Ȃ甲���� */
				break;
			}
			if(memcmp(KZN_Coment[cnt],wk_input,strlen(wk_input)) == 0){
				ret = cnt;
				break;
			}
		}
	}

	return ret;
}

/**/
int CHK_Kkacmt(input)
/*****************************************************************************
*fc
        �ُ�l�}�[�N������ʃR�����g�̃`�F�b�N
*rt
        0          ... �ُ�l�}�[�N�Ȃ�
        1          ... �ُ�l�}�[�N����
        ���̑� ... �G���[
*nt
*ag
*****************************************************************************/
char *input;
{
	int	cnt;
	char	wk_input[20];

	trim(wk_input, input);

	if(wk_input[0] == '\0'){
		/* �X�y�[�X�Ȃ�I�� */
		return -1;
	}

	for(cnt = 1; IJOU_KKACMT[cnt] != NULL ; cnt++){
		if(memcmp(IJOU_KKACMT[cnt],"END",3) == 0){
			/* END�Ȃ甲���� */
			break;
		}
		if(memcmp(IJOU_KKACMT[cnt],wk_input,strlen(wk_input)) == 0){
			/* �ُ�l�}�[�N�R�����g�ɊY���I�I */
			return 1;
		}
	}
	/* �Y���Ȃ� */
	return 0;
}

/****************************************************************************
 * KSNSK_if.c : �v�Z�������� IF �u���b�N�W�J
 * Copyright(C)2008 INTEC Inc.
 *--------------------------------------------------------------------------
 * [History]
 *  Feb 14, 2008    H.Sato              Original
 ****************************************************************************/

/*--------------------------------------------------------------------------*
 * OperateKSNSK
 *
 * �v�Z�������񒆂Ɋ܂܂�� IF �u���b�N�̓W�J
 *
 * Paramter(s):
 *  pszKSNSK            NULL �������I���R�[�h�Ƃ��镶������i�[���Ă���̈�
 *                      �̐擪�|�C���^���w�肵�܂��B
 *                      �����Ŏw�肷�镶����́A IF �u���b�N���܂ތv�Z���̕�
 *                      ����ł��B
 *
 * Return value:
 *  �֐�������I�������ꍇ�AIF �u���b�N������W�J��̕����񂪊i�[���Ă����
 *  ��̐擪�|�C���^�C���^��Ԃ��܂��B
 *  �G���[�����������ꍇ�A NULL ��Ԃ��܂��B
 *
 * Comment:
 *  ���̊֐����Ԃ� (��������i�[���Ă���) �̈悪�s�v�ɂȂ����ꍇ�A���̊֐���
 *  �Ăяo������ free() ���g�p���ė̈���J�����Ă��������B
 *--------------------------------------------------------------------------*/
char *OperateKSNSK(const char *pszKSNSK)
{
	static char	 szBlank[] = " ";
	static char	 szNE[] = STR_NE;

	char		*pszFormular;				/* �߂�l (�����Ώۂ̌v�Z��)        */
	char		*pszReplace;				/* IF �u���b�N�W�J����              */
	char		*pszIFBlock = (char *) NULL;		/* IF �u���b�N������                */
	struct _IFBLOCK *pstItems = (struct _IFBLOCK *) NULL;	/* IF �u���b�N�����ڗv�f���ɕ���    */
	double		dblLeft;				/* ���������Ӓl                     */
	double		dblRight;				/* �������E�Ӓl                     */
	BOOL		nCompared = FALSE;			/* ���������茋��                   */
	BOOL		nErrorOccured = FALSE;			/* �G���[�����t���O                 */
	static char	 szConvert[32];

	if (NULL != (void *) (pszFormular = _touppercase(_replace(pszKSNSK, szBlank, (char *) NULL)))) {
		if (!nErrorOccured && NULL != (void *) pszFormular) {
			if (!IsFormula(pszFormular)) {
				nErrorOccured = TRUE;   /* �v�Z���Ƃ��Ĉُ�                 */
				free((void *) pszFormular);
				pszFormular = (char *) NULL;
			}
		}

		while (!nErrorOccured && NULL != (void *) (pszIFBlock = GetIFBlock(pszFormular))) {
			if (NULL == (void *) (pstItems = SplitIFBlockItems(pszIFBlock))) {
				nErrorOccured = TRUE;   /* IF �u���b�N���̗v�f�������s      */
				free((void *) pszFormular);
				pszFormular = (char *) NULL;
			}
			else if (NULL == (void *) pstItems->pszConditionLeft ||
			         NULL == (void *) pstItems->pszOperator ||
			         NULL == (void *) pstItems->pszConditionRight ||
			         NULL == (void *) pstItems->pszValueTrue ||
			         NULL == (void *) pstItems->pszValueFalse) {
				nErrorOccured = TRUE;   /* IF �u���b�N���̗v�f�������s      */
				free((void *) pszFormular);
				pszFormular = (char *) NULL;
			}
			else {
				/* �����������e������ IF �u���b�N������ (������ IF �u���b�N�̓W�J�G���W��) */
				dblLeft = StringCal(pstItems->pszConditionLeft);
				dblRight = StringCal(pstItems->pszConditionRight);
				/* ��x������ɕϊ����Ȃ��Ƃ��܂���r�ł��Ȃ�               */
				sprintf(szConvert, "%f", dblLeft);
				dblLeft = strtod(szConvert, (char **) NULL);
				sprintf(szConvert, "%f", dblRight);
				dblRight = strtod(szConvert, (char **) NULL);

				switch ((int) *(pstItems->pszOperator)) {
				case OPERATOR_EQ:       /* ������: ��v                     */
					nCompared = ((dblLeft == dblRight) ? TRUE : FALSE);
					break;
				case OPERATOR_LT:       /* ������: ���� or �s��v           */
					if (strcmp(pstItems->pszOperator, szNE)) {
						nCompared = ((dblLeft < dblRight) ? TRUE : FALSE);
					} else {
						nCompared = ((dblLeft != dblRight) ? TRUE : FALSE);
					}
					break;
				case OPERATOR_GT:       /* ������: �z����                   */
					nCompared = ((dblLeft > dblRight) ? TRUE : FALSE);
					break;
				default:                /* �ُ�Ȕ�r���Z�q                 */
					nErrorOccured = TRUE;
					free((void *) pszFormular);
					pszFormular = (char *) NULL;
					break;
				}
			}
			if (!nErrorOccured) {
				if (nCompared) {
					pszReplace = _replace(pszFormular, pszIFBlock, pstItems->pszValueTrue);
				}
				else {
					pszReplace = _replace(pszFormular, pszIFBlock, pstItems->pszValueFalse);
				}
				if (NULL == (void *) pszReplace) {
					nErrorOccured = TRUE;
					/* IF �u���b�N �� �K�p�l�ϊ����s    */
					free((void *) pszFormular);
					pszFormular = (char *) NULL;
				}
				else {
					free((void *) pszFormular);
					pszFormular = pszReplace;
				}
			}
			if (NULL != (void *) pszIFBlock) {
				free((void *) pszIFBlock);
			}
			freeIFBLOCK(pstItems);
		}
	}

	if (!nErrorOccured && NULL != (void *) pszFormular) {
		if (!IsFormula(pszFormular)) {
			nErrorOccured = TRUE;       /* �v�Z���Ƃ��Ĉُ�                 */
		}
	}

	if (nErrorOccured && NULL != pszFormular) {
		free((void *) pszFormular);
		pszFormular = (char *) NULL;
	}
	return (pszFormular);
}

/*--------------------------------------------------------------------------*
 * GetIFBlock
 *
 * �v�Z���Ɋ܂܂�� IF �u���b�N������𒊏o���܂��B
 *
 * Paramter(s):
 *  pszOrigin           NULL �������I���R�[�h�Ƃ��镶������i�[���Ă���̈�
 *                      �̐擪�|�C���^���w�肵�܂��B
 *                      �����Ŏw�肷�镶����́A IF �u���b�N���܂ތv�Z���̕�
 *                      ����ł��B
 *
 * Return value:
 *  �֐�������I�������ꍇ�A���o���� IF �u���b�N��������i�[����̈�̐擪�|
 *  �C���^��Ԃ��܂��B
 *  �G���[�����������ꍇ�A NULL ��Ԃ��܂��B
 *
 * Comment:
 *  ���̊֐����Ԃ� (��������i�[���Ă���) �̈悪�s�v�ɂȂ����ꍇ�A���̊֐���
 *  �Ăяo������ free() ���g�p���ė̈���J�����Ă��������B
 *--------------------------------------------------------------------------*/
char *GetIFBlock(const char *pszOriginal)
{
	static char	szIFBlock[] = STR_BEGIN_IFBLOCK;

	char	*pszResult = NULL;	/* �߂�l                           */
	char	*pszIFBlock;	 	/* IF �u���b�N�J�n�ʒu              */
	size_t	ulOriginal; 	 	/* ���̕�����̒���                 */
	char	*pszFind;	 	/* IF �u���b�N�I�[����              */
	int	nParenthesis = 0; 	/* ���ʂ̊K�w�k�x                   */
	int	nComma;			/* �J���}�̐�                       */
	BOOL	nTarminate;		/* IF �u���b�N�I�[���o              */

	if (NULL != (void *) pszOriginal) {
		if ((size_t) 0 <= (ulOriginal = strlen(pszOriginal))) {
			if (NULL != (void *) (pszIFBlock = _strrstr((char *) pszOriginal, (const char *) szIFBlock))) {
				for (pszFind = (pszIFBlock + strlen(szIFBlock)), nTarminate = FALSE, nParenthesis = 0, nComma = 0; !nTarminate; pszFind++) {
					switch	((int) *pszFind) {
					case	PARENT_BEGIN:  /* �J�b�R (�J�n)                    */
						nParenthesis++;
						break;
					case	_EOS:
					case	PARENT_END:    /* �J�b�R (�I��)                    */
						nParenthesis--;
						if (0 > nParenthesis) {
							nTarminate = TRUE;
							if (1 < nComma) {
								pszResult = _strndup(pszIFBlock, (size_t) (pszFind - pszIFBlock + 1));
							}
						}
						break;
					case SPLITTER_COMMA: /* �v�f�̋�؂�������J���}         */
						nComma++;
						break;
					default:
					    break;
					}
				}
			}
		}
	}
	return (pszResult);
}

/*--------------------------------------------------------------------------*
 * IsFormula
 *
 * �v�Z���̏����`�F�b�N
 *
 * Paramter(s):
 *  pszOrigin           NULL �������I���R�[�h�Ƃ��镶������i�[���Ă���̈�
 *                      �̐擪�|�C���^���w�肵�܂��B
 *                      �����Ŏw�肷�镶����́A�v�Z���̕�����ł��B
 *
 * Return value:
 *  �w�肳�ꂽ�����񂪁A�v�Z���Ƃ��Đ������Ă���ꍇ�A 0 �ȊO�̒l��Ԃ���
 *  ���B
 *  �v�Z���ȊO�̏ꍇ�A�܂��̓G���[�����������ꍇ�A�l 0 ��Ԃ��܂��B
 *--------------------------------------------------------------------------*/
int IsFormula(const char *pszKSNSK)
{
	BOOL	bResult = FALSE;
	char	*pszFormular;
	char	*pszReplace;
	int	nIndex;
	int	nParenthesis = 0;               /* ���ʂ̊K�w�k�x                   */

	if (NULL != (void *) (pszFormular = _touppercase(_replace(pszKSNSK, " ", (char *) NULL)))) {
		/* �Z�p�֐��̏���                                                   */
		if (NULL != (void *) (pszReplace = _replace(pszFormular, STR_BEGIN_IFBLOCK, (char *) NULL))) {
			free((void *) pszFormular);
			pszFormular = pszReplace;

			if (NULL != (void *) (pszReplace = _replace(pszFormular, ":", (char *) NULL))) {
				free((void *) pszFormular);
				pszFormular = pszReplace;
			}
			if (NULL != (void *) (pszReplace = _replace(pszFormular, ",", (char *) NULL))) {
				free((void *) pszFormular);
				pszFormular = pszReplace;
			}
			/* ���������̔�r���Z�q����                                     */
			if (NULL != (void *) (pszReplace = _replace(pszFormular, "<", (char *) NULL))) {
				free((void *) pszFormular);
				pszFormular = pszReplace;
			}
			if (NULL != (void *) (pszReplace = _replace(pszFormular, ">", (char *) NULL))) {
				free((void *) pszFormular);
				pszFormular = pszReplace;
			}
			if (NULL != (void *) (pszReplace = _replace(pszFormular, "=", (char *) NULL))) {
				free((void *) pszFormular);
				pszFormular = pszReplace;
			}
		}
		if (NULL != (void *) (pszReplace = _replace(pszFormular, STR_BEGIN_LOG10, (char *) NULL))) {
			free((void *) pszFormular);
			pszFormular = pszReplace;
		}
		if (NULL != (void *) (pszReplace = _replace(pszFormular, STR_BEGIN_LOG, (char *) NULL))) {
			free((void *) pszFormular);
			pszFormular = pszReplace;
		}
		if (NULL != (void *) (pszReplace = _replace(pszFormular, STR_BEGIN_POW, (char *) NULL))) {
			free((void *) pszFormular);
			pszFormular = pszReplace;
			if (NULL != (void *) (pszReplace = _replace(pszFormular, ",", (char *) NULL))) {
				free((void *) pszFormular);
				pszFormular = pszReplace;
			}
		}
		/* ������ (�����_���܂�) �A���Z�L������                             */
		for (nIndex = 0, bResult = TRUE; bResult && '\0' != (int) *(pszFormular + nIndex); nIndex++) {
			if (0 == isdigit((int) *(pszFormular + nIndex))) {
				if ('.' != (int) *(pszFormular + nIndex) &&
				    PARENT_BEGIN != (int) *(pszFormular + nIndex) &&
				    PARENT_END != (int) *(pszFormular + nIndex) &&
				    '+' != (int) *(pszFormular + nIndex) &&
				    '*' != (int) *(pszFormular + nIndex) &&
				    '-' != (int) *(pszFormular + nIndex) &&
				    '/' != (int) *(pszFormular + nIndex)) {
					bResult = FALSE;
				}
			}
		}
		free((void *) pszFormular);
		/* ���ʑΉ��`�F�b�N                                                 */
		if (bResult) {
			for (nParenthesis = 0, nIndex = 0; bResult && '\0' != (int) *(pszKSNSK + nIndex); nIndex++) {
				switch ((int) *(pszKSNSK + nIndex)) {
				case PARENT_BEGIN:
					nParenthesis++;
					break;
				case PARENT_END:
					nParenthesis--;
				default:
					break;
				}
			}
			if (nParenthesis) {
				bResult = FALSE;
			}
		}
	}
	return (bResult ? !0:0);
}

/*--------------------------------------------------------------------------*
 * SplitIFBlockItems
 *
 * IF �u���b�N����������ڒP�ʂɕ������܂��B
 *
 * Paramater(s):
 *  pszOrigin           NULL �������I���R�[�h�Ƃ��镶������i�[���Ă���̈�
 *                      �̐擪�|�C���^���w�肵�܂��B
 *                      �����Ŏw�肷�镶����́A�v�f���Ƃɕ�������v�Z���� 
 *                      IF �u���b�N������ł��B
 *
 * Return value:
 *  �֐�������I�������ꍇ�A������̍��ڕ�������i�[���� _IFBLOCK �\���̂̐�
 *  ���|�C���^��Ԃ��܂��B
 *  �G���[�����������ꍇ�A NULL ��Ԃ��܂��B
 *
 * Comment:
 *  ���̊֐����Ԃ� (��������i�[���Ă���) �̈悪�s�v�ɂȂ����ꍇ�A���̊֐���
 *  �Ăяo������ freeIFBLOCK() ���g�p���ė̈���J�����Ă��������B
 *--------------------------------------------------------------------------*/
struct _IFBLOCK *SplitIFBlockItems(char *pszOrigin)
{
	static char szNE[] = STR_NE;

	struct	_IFBLOCK *pstResult = (struct _IFBLOCK *) NULL; /* �߂�l   */
	BOOL	nErrorOccured = FALSE;	/* �G���[���o�t���O                 */
	BOOL	nTerminate = FALSE;	/* �����I���t���O                   */
	char	*pszTarget;		/* ���蕶��                         */
	char	*pszBegin;		/* ����Ώۂ̍��ڂ̐擪             */
	int	nParenthesis;		/* �J�b�R�̓���q�[�x               */
	int	nIndex;			/* �������ڂ̍��ڃC���f�b�N�X       */

	if (NULL == (void *) pszOrigin) {
		pstResult = (struct _IFBLOCK *) NULL;
	}
	else if (NULL != (void *) (pstResult = (struct _IFBLOCK *) malloc(sizeof(struct _IFBLOCK)))) {
		for (nIndex = 0; MAXCNT_ITEM_IFBLOCK >= nIndex; nIndex++) {
			*((void **) pstResult + nIndex) = NULL;
		}
		for (nErrorOccured = FALSE, nTerminate = FALSE, nIndex = 0, nParenthesis = 0, pszBegin = pszTarget = (strchr(pszOrigin, '(') + 1);
			!nErrorOccured && !nTerminate && NULL != (void *) pszTarget && _EOS != (int) *pszTarget;
			pszTarget++) {

			switch	((int) *pszTarget) {
			case	PARENT_BEGIN:          /* �J�b�R (�J�n)                    */
				nParenthesis++;
				break;

			case PARENT_END:            /* �J�b�R (�I��)                    */
				nParenthesis--;
				if (0 > nParenthesis) {
					if (NULL == (void *) pstResult->pszValueTrue ||
					    NULL == (void *) pstResult->pszConditionRight) {
						nErrorOccured = TRUE;
						 /* IF �u���b�N�̏I�������� ')' ����
						    �o�������A�K�{���ڂ��s�����Ă��� */
					}
					else if (NULL == (void *) (pstResult->pszValueFalse = 
								_strndup(pszBegin, (size_t) (pszTarget - pszBegin)))) {
						nErrorOccured = TRUE;
					}
					else {
						nTerminate = TRUE;
					}
				}
				break;
			case OPERATOR_LT:           /* ���������Z�q                     */
			case OPERATOR_GT:
			case OPERATOR_EQ:
				if (nParenthesis &&
					NULL != (void *) pstResult->pszConditionLeft) {
					nErrorOccured = TRUE;
				}
				else if (NULL == (void *) (pstResult->pszConditionLeft = 
				                           _strndup(pszBegin,
				                                    (size_t) (pszTarget - pszBegin)))) {
					nErrorOccured = TRUE;
				}
				else if (OPERATOR_LT == (int) *pszTarget &&
					 OPERATOR_GT == (int) *(pszTarget + 1)) {
					if (NULL == (void *) (pstResult->pszOperator = strdup(szNE))) {
						nErrorOccured = TRUE;
					}
					else {
						pszTarget++;
						pszBegin = pszTarget;
						pszBegin++;
					}
				}
				else if (NULL == (void *) (pstResult->pszOperator = _strndup(pszTarget, 1))) {
					nErrorOccured = TRUE;
				}
				else {
					pszBegin = pszTarget;
					pszBegin++;
				}
				break;
			case SPLITTER_COMMA:    /* �v�f�̋�؂�������J���}             */
				if (nParenthesis) {
					break;
				}
				else if (NULL == (void *) pstResult->pszConditionRight) {
					/* �������E�� - ���������^�̏ꍇ�ɓK�p����l            */
					if (NULL == (void *) (pstResult->pszConditionRight =
						 	_strndup(pszBegin, (size_t) (pszTarget - pszBegin)))) {
						nErrorOccured = TRUE;
					}
					else {
						pszBegin = pszTarget;
						pszBegin++;
					}
				}
				else if (NULL == (void *) pstResult->pszValueTrue) {
					/* ���������^�̏ꍇ�ɓK�p����l - 
					   �U�̏ꍇ�ɓK�p����l                                 */
					if (NULL == (void *) (pstResult->pszValueTrue = 
								_strndup(pszBegin, (size_t) (pszTarget - pszBegin)))) {
						 nErrorOccured = TRUE;
					}
					else {
						pszBegin = pszTarget;
						pszBegin++;
					}
				}
				else {
					nErrorOccured = TRUE;
				}
				break;
			default:                    /* �����ł̏����̑ΏۊO             */
				break;
			}
		}
	}

	/* �G���[�������́A (�r���܂�) �m�ۂ������e���N���A                     */
	if (nErrorOccured && NULL != (void *) pstResult) {
	    freeIFBLOCK(pstResult);
	    pstResult = (struct _IFBLOCK *) NULL;
	}
	return (pstResult);
}

/*--------------------------------------------------------------------------*
 * freeIFBLOCK
 *
 * IF �u���b�N���v�f�����\���̗̂v�f��S�ĊJ��
 *
 * Parameter(s):
 *  pstTarget           IF �u���b�N���v�f�����\���̂̐擪�|�C���^���w�肵��
 *                      ���B
 *
 * Return value:
 *  Nothing
 *--------------------------------------------------------------------------*/
void freeIFBLOCK(struct _IFBLOCK *pstTarget)
{
	int nIndex;                         /* ���ڃC���f�b�N�X                 */

	if (NULL != (void *) pstTarget) {
		for (nIndex = 0; MAXCNT_ITEM_IFBLOCK > nIndex; nIndex++) {
			if (NULL != *((void **) pstTarget + nIndex)) {
				free((void *) *((void **) pstTarget + nIndex));
			}
		}
		free((void *) pstTarget);
	}
	return;
}
