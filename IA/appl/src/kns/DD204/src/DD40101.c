/*******************************************************************************/
/*                                                                             */
/*     �a�l�k�l���������V�X�e��                                                */
/*                                                                             */
/*     �V�X�e�����F�������ʈُ�`�F�b�N                                        */
/*     �t�@�C�����FDD40101.c                                                   */
/*     �T�v      �F���͋@����̌������ʂ̃��A���^�C���`�F�b�N���s���B          */
/*                                                                             */
/*******************************************************************************/

/*******************************************************************************/
/*  Ver.     Date           Name           History                             */
/* --------------------------------------------------------------------------- */
/*  1.00     2006/01/13     S.Tsunekawa    Create                              */
/* --------------------------------------------------------------------------- */
/*  Ver.     ���t           ���O           �C�����e                            */
/* --------------------------------------------------------------------------- */
/*  2.00     2008/09/19     K.Ameno        X-M�Ή�����                         */
/*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "DD204.h"
#include "DD40101.h"
/*
#include "bmllog.h"
#include "bmlprm.h"
*/

void SetKekkaDefault(Kekka *pKekka);
void SetKekkaDefaultSpace(Kekka *pKekka);
int chkInfoRead(int mode, char * kmkcd,char * fName, char **Data, char *buff);

int	RenjiChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, char **ODFld, int keta);
int	SoukanChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, char **ODFld, int keta);
int	KanrenChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, char **ODFld,SaikenInfo * fSaiken);
int	BungaChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, char **ODFld,SaikenInfo * fSaiken);
int	NyubiYoketuChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, int fNyuYou);
int	NyubiYoketu(Kekka * pKekka, int KekkaCnt);
int	KisyakuChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, char *cKisyak, int keta);
void GetModule( char * pFrom, int * pTo ) ;

int KekkaMarume(Kekka * pKekka, int KekkaCnt, char * ReadFileName);

double StringCal_sub(char enzan,double val1,double val2);
double StringCal(char *CalStr) ;

void trim(char * dst, char *src);

int GetKenorder(SOCKET_INF* ,int, int*);        /* �����I�[�_�[�擾���� */
void SetKekkaData(SOCKET_INF*,int);

/*----<< Begin add source Feb 27, 2008 H.Sato >>----*/
/* �v�Z���g���Ή�                                                           */

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

/* �����I�[�_�[�̃t�@�C�� (CSV �`��) �Ɋ܂܂�鑮�����̈ʒu               */
#define FLDIDX_SC                 (40)  /* �g�� (cm)                        */
#define FLDIDX_TJ                 (41)  /* �̏d                             */
#define FLDIDX_TJTNI              (42)  /* �̏d�敪                         */
#define FLDIDX_TNTME              (50)  /* �~�A����                         */
#define FLDIDX_TNTNI              (51)  /* �~�A���ԋ敪                     */
#define FLDIDX_TNRYO              (52)  /* �~�A��                           */
#define FLDIDX_TNRYOTNI           (53)  /* �~�A�ʋ敪                       */
#define FLDIDX_SBTKBN             (43)  /* ���ʋ敪                         */
#define FLDIDX_AGE                (46)  /* �N��                             */
#define FLDIDX_AGEKBN             (47)  /* �N��敪                         */

/* �P�ʓ����������ڂɊi�[����鎯�ʎq                                       */
#define _VALUE_TNTNI_HOUR       ('0')   /* �~�A����: ���ԒP��               */
#define _VALUE_TNTNI_MINUTE     ('1')   /* �~�A����: ���P��                 */
#define _VALUE_TNTNI_UNKNOWN    ('9')   /* �~�A����: ���ԒP�ʕs��           */
#define _VALUE_TNRYO_MILLILITER ('0')   /* �~�A��: �~�� ���b�g���P��        */
#define _VALUE_TNRYO_LITER      ('1')   /* �~�A��: ���b�g���P��             */
#define _VALUE_TNRYO_UNKNOWN    ('9')   /* �~�A��: �ʒP�ʕs��               */
#define _VALUE_TJTNI_GRAM       ('1')   /* �̏d: �O�����P��                 */
#define _VALUE_TJTNI_KILLOGRAM  ('0')   /* �̏d: �L���O�����P��             */
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

char gszTransfer[MAXBUF + 1];			/* �����񁨐��l �ϊ��o�b�t�@
										   �P��̒l�̒u���݂̂Ȃ̂ŁA�R����
										   �����                           */

/* �v�Z������ IF �u���b�N�W�J                                               */
extern char *OperateKSNSK(const char *);

/* ���l�����񔻒�                                                           */
extern int _isnumeric(const char *);

/*---<< End add source Feb 27, 2008 H.Sato >>---*/

#define		READ_BUFF_SIZE		10240

char		GetFolder[256];
char		GetFolder2[256];
char		ReadFileName[256];
char		ReadFileNameOD[256];

char		testChkValue[21];
char		NyubiCD[8];
char		NyubiCM[6];
char		NyubiCHK[21];
char		NyubiKekka[21];
char		NyubiSTS[3];
char		YoketsuCD[8];
char		YoketsuCM[6];
char		YoketsuCHK[21];
char		YoketsuKekka[21];
char		YoketsuSTS[3];
char		OudanCD[8];
char		OudanCM[6];
char		OudanCHK[21];
char		OudanKekka[21];
char		OudanSTS[3];

/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
extern XBARM_INF  sXbarm_inf[XBARM_ITEM_NUM];
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
char	aMstFolder[256];		/* �t�@�C�����G���A */

// ��ߔ{���}�X�^�Œ蒷��`
typedef struct stKSKBRMST {
	char	BSKKBN[4];		/* ���͋@�敪 */
	char	KNSGRP[16];		/* �����O���[�v */
	char	KMKCD[7];		/* ���ڃR�[�h */
	char	KSBR[15];		/* ��ߔ{�� */
	double	KMIN; 			/* ��߉����l */
	double	KMAX;			/* ��ߏ���l */
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** ��ߔ{���}�X�^�̎{�݃R�[�h�Ή� ***/
    char    KAIYMD[8];      /* �J�n�N���� */
    char    HAIYMD[8];      /* �p�~�N���� */
    char    HNKTNTID[8];    /* �ύX�S��ID */
    char    KSNDHKSNDH[12]; /* ���X�V���� */
    char    SSTCD[8];       /* �{�݃R�[�h */
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
} KSKBRMST;

KSKBRMST * gpKSKBRMST;
int		 gKSKBRMSTnum;

typedef enum myFlg {
	MY_FLG_ON,
	MY_FLG_OFF
} MY_FLG ;

typedef struct stKeisanChk_tag {
	char motoKMKCD[8];
	char KMKCD[8];
	double raw;
	MY_FLG flgRawNone ;
} STKEISANCHK;


int	KeisanChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, char **ODFld, STKEISANCHK * calbuf );

/******************************************************************************/
/*	�� �� ��  �FRealTimeChkInit()											  */
/*	�@�\�T�v  �F���A���^�C���Č��`�F�b�N��������							  */
/*	��	  ��  �F															  */
/*	 ��P���� �F															  */
/*	 ��Q���� �F															  */
/*	�o	  ��  �F															  */
/*	���A���  �Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
int RealTimeChkInit()
{
	BMLPRM * bp;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	bp = ZbmlPrmOpen( DD40101_INI_FILE_NAME );
	ZbmlPrmGetVal(bp, "ChkInfoFileFolder", GetFolder);
	ZbmlPrmGetVal(bp, "ChkInfoFileFolder2", GetFolder2);

	/* ���сE�n���̍��ڃR�[�h�y�ѐݒ�R�����gCD�̎擾 */
	ZbmlPrmGetVal(bp, "NyubiCD", NyubiCD);
	ZbmlPrmGetVal(bp, "NyubiCM", NyubiCM);
	ZbmlPrmGetVal(bp, "NyubiCHK", NyubiCHK);
	ZbmlPrmGetVal(bp, "YoketsuCD", YoketsuCD);
	ZbmlPrmGetVal(bp, "YoketsuCM", YoketsuCM);
	ZbmlPrmGetVal(bp, "YoketsuCHK", YoketsuCHK);
	ZbmlPrmGetVal(bp, "OudanCD", OudanCD);
	ZbmlPrmGetVal(bp, "OudanCM", OudanCM);
	ZbmlPrmGetVal(bp, "OudanCHK", OudanCHK);

	ZbmlPrmGetVal(bp, "GetMstFolder", aMstFolder);

	ZbmlPrmClose(bp);

	/* ��ߔ{���}�X�^���t�@�C�����ǂݏo���B */


	int		iWrk;
	char	aWrkBuf[255];
	char	buff[1024];
	FILE	*fp;
	char	** pFld;
	int		cnt;
	int		offset;
	char    *adrCR;

	memset( aWrkBuf, 0, sizeof(aWrkBuf) );
	strcpy( aWrkBuf,aMstFolder );
	strcat( aWrkBuf,"kskbrmst.del" );
	adrCR = NULL;

#ifdef _DEBUG_
	printf( "�t�@�C�����F%s\n",aWrkBuf );
#endif

	fp = fopen( aWrkBuf,"r");
	if( fp == NULL ) {
		printf("�t�@�C���̃I�[�v���Ɏ��s���܂����B\n");
		return -1;
	}
	gKSKBRMSTnum = 0;
	memset( buff,0,1024 );
	while( fgets( buff, 1024, fp ) != NULL ) {
		++gKSKBRMSTnum;
	}

	gpKSKBRMST = malloc(sizeof(KSKBRMST)*gKSKBRMSTnum);
	memset(gpKSKBRMST, 0, sizeof(KSKBRMST)*gKSKBRMSTnum);
	rewind(fp);
	iWrk = 0;
	memset( buff,0,1024 );
	pFld = malloc(sizeof(char *)*15);
	while( fgets( buff, 1024, fp ) != NULL ) {
		if( iWrk >= gKSKBRMSTnum ) {
			break;
		}
		/* �����̉��s�R�[�h���폜 */
		adrCR = strchr(buff, ( int )'\r');
		if (adrCR != NULL) {
			*adrCR = '\0';
		}
		cnt = 0;
		offset = 0;;
		pFld[cnt] = &buff[cnt];
		cnt++;
		while (buff[offset] != '\0') {
			if (buff[offset] == ',') {
				pFld[cnt++] = &buff[offset+1];
				buff[offset] = '\0';
			}
			offset++;
		}
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** ��ߔ{���}�X�^�̎{�݃R�[�h�Ή� ***/
        /*if (cnt != 10) {*/
        if (cnt != 11) {
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
			// �t�B�[���h������v���Ȃ�
			printf( "�t�B�[���h������v���܂���ł����B\n" );
			break;
		}

		// �t�B�[���h�̗L���������`�F�b�N���邵�A�������֓]������B
		strcpy( gpKSKBRMST[iWrk].BSKKBN,pFld[0] );
		strcpy( gpKSKBRMST[iWrk].KNSGRP,pFld[1] );
		strcpy( gpKSKBRMST[iWrk].KMKCD,pFld[2] );
		strcpy( gpKSKBRMST[iWrk].KSBR,pFld[3] );
		gpKSKBRMST[iWrk].KMIN = atof( pFld[4] );
		gpKSKBRMST[iWrk].KMAX = atof( pFld[5] );
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** ��ߔ{���}�X�^�̎{�݃R�[�h�Ή� ***/
		strcpy( gpKSKBRMST[iWrk].SSTCD,pFld[10] );
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
		++iWrk;
		memset( buff,0,1024 );
	}
	gKSKBRMSTnum = iWrk;
	free(pFld);

	return 0;
}

/******************************************************************************/
/*	�� �� ��  �FRealTimeChk()												  */
/*	�@�\�T�v  �F���A���^�C���Č��`�F�b�N����								  */
/*	��	  ��  �F															  */
/*	 ��P���� �Fp		:	�A�v���P�[�V�������\���̃|�C���^				  */
/*	 ��Q���� �FpKekka	:	�������ʍ\���̃|�C���^							  */
/*	 ��R���� �FKekkaCnt:	���ʐ�											  */
/*	�o	  ��  �FfSaiken	:	�Č����|�C���^								  */
/*	���A���  �Fint															  */
/*					0:����													  */
/*					1:�Č�����												  */
/******************************************************************************/
int	RealTimeChk(SOCKET_INF *p, SaikenInfo * fSaiken)
{
	static	int	chkCnt = 0;
	static	int	stCnt = 0;
	int		lCnt;
	int		ret = 0;
	int		ret2;
	int		flg;
	char	*pBuff;
	char	**pFld;
	char	*pBuffOD;
	char	**pFldOD;
	char	tmpBuff[11];
	int		fNyuYou;

	int		kCnt = 0;
	STKEISANCHK	kekkabuf[32];

	char	 cRawBuf[256] ;

	int 		 li_SaveKekkaNum ;
	int 		 li_KenorderCnt ;
	SaikenInfo	*nfSaiken;
	int			 li_idxC ;
	int			 li_idxK ;
	int			 li_idxO ;
	int			 li_RetSts ;
	int			iKnssu;
	char		cKsktkbn;
#ifdef _DEBUG_
	char		cMsgBuf[512];
#endif

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
#ifdef _DEBUG_
	printf("\n������ RealTimeChk(%d���) Start\n", chkCnt + 1);
	memset(cMsgBuf, 0, sizeof(cMsgBuf));
	sprintf(cMsgBuf, "\n������ RealTimeChk(%d���) Start\n", chkCnt + 1);
	sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif

	if (chkCnt > 3) return 0;
	chkCnt ++;

	pFld = malloc(sizeof(char *)*200);
	pBuff = malloc(sizeof(char) * READ_BUFF_SIZE);
	pFldOD = malloc(sizeof(char *)*200);
	pBuffOD = malloc(sizeof(char) * READ_BUFF_SIZE);
	/* ADD E.Osada 2006-07-15 */
	memset(pFld, 0, sizeof(char *)*200);
	memset(pBuff, 0, sizeof(char) * READ_BUFF_SIZE);
	memset(pFldOD, 0, sizeof(char *)*200);
	memset(pBuffOD, 0, sizeof(char) * READ_BUFF_SIZE);
	/**/
	/* �����`�F�b�N���̃t�@�C������擪�̌��ʏ�񂩂�쐬 */
	strncpy(ReadFileName, "CH_", 256);
	strncpy(tmpBuff, p->pKekka->asyrckid, 10);
	strncat(tmpBuff, "__________", 10-strlen(p->pKekka->asyrckid));
	strncat(ReadFileName, tmpBuff, 256);
	sprintf(tmpBuff, "%03d", p->pKekka->asyrckpos);
	strncat(ReadFileName, tmpBuff, 256);
	strncat(ReadFileName, ".dat", 256);

	/* �I�[�_�[�t�@�C���̖��O�𑦎��`�F�b�N���̃t�@�C��������쐬 */
	strncpy(ReadFileNameOD, ReadFileName, 256);
	ReadFileNameOD[0] = 'O';
	ReadFileNameOD[1] = 'D';

	/* ���сE�n���̑��݃`�F�b�N */
	fNyuYou = NyubiYoketu(p->pKekka, p->iKekkaNum);

	/* RAW�f�[�^�̊ۂߏ��� */
	KekkaMarume(p->pKekka, p->iKekkaNum, ReadFileName);

	for (lCnt = stCnt; lCnt < p->iKekkaNum; lCnt ++) {
// 2009.02.18 moriya ->
		memset(pFld, 0, sizeof(char *)*200);
		memset(pBuff, 0, sizeof(char) * READ_BUFF_SIZE);
		memset(pFldOD, 0, sizeof(char *)*200);
		memset(pBuffOD, 0, sizeof(char) * READ_BUFF_SIZE);
// 2009.02.18 moriya -<
		fSaiken[lCnt].flg = 0;

		if ( p->pKekka[lCnt].knsflg == 'H' ) {
			continue;
		}
		/* �����`�F�b�N���t�@�C���ǂݍ��� */
		ret2 = chkInfoRead(0, p->pKekka[lCnt].kmkcd, ReadFileName, pFld, pBuff);
		if ( ret2 != 0 ) {
			/*  �����`�F�b�N���Ȃ� */
			continue;
		}
		/* �I�[�_�[���t�@�C���ǂݍ��� */
		ret2 = chkInfoRead(1, p->pKekka[lCnt].kmkcd, ReadFileNameOD, pFldOD, pBuffOD);
		if ( ret2 != 0 ) {
			/* �I�[�_�[���Ȃ� */
			continue;
		}

#ifdef _DEBUG_
		printf("�`�F�b�N�X�^�[�g >>>>>>>>>>>>>>\n");
		sFncSyslog ( LOG_ERR, "", "�`�F�b�N�X�^�[�g >>>>>>>>>>>>>>\n" ) ;
#endif
		/* 2006.08.11 Nagata ���͋@�A���[���`�F�b�N��NG�̏ꍇ�A*/
		/* ���ʂɃf�t�H���g�l���Z�b�g���Ȃ�                    */
		if(p->pKekka[lCnt].yobiflg01 != '2'){
			/* ���ʏ���Default�l��ݒ� */
			SetKekkaDefault(&p->pKekka[lCnt]);
		}
		else{
			/* 2006.08.11 Nagata ���͋@�A���[���`�F�b�N��NG�̏ꍇ�A */
			/* �����t���O�A���ʂ̃G���[�t���O�ȊO�Ƀf�t�H���g�l���Z�b�g���� */
			SetKekkaDefaultSpace(&p->pKekka[lCnt]);
		}

		trim(cRawBuf, p->pKekka[lCnt].rawdata);

		if ( cRawBuf[0]  == '\0' || cRawBuf[0]  == '/' ) {
			fSaiken[lCnt].flg = 1;
			ret = 1;
			if( p->pKekka[lCnt].yobiflg01 != '2'){
				p->pKekka[lCnt].knsflg = 'A';
				p->pKekka[lCnt].yobiflg01 = '2';	/* �G���[�t���O ADD 2006.08.11 */
				/* 2006.08.11 Nagata �u�����N�f�[�^�̏ꍇ�A                      */
				/* �����t���O�A���ʂ̃G���[�t���O�ȊO�Ƀf�t�H���g�l���Z�b�g����  */
				SetKekkaDefaultSpace(&p->pKekka[lCnt]);
			}
			continue ;
		}

		if (pFld[18][0] == '1') {		/* �����W�`�F�b�N */
			flg = RenjiChk(pFld[38], p->pKekka, p->iKekkaNum, lCnt, pFldOD, atoi(pFld[57]));
			if (flg == 1) {
				fSaiken[lCnt].flg = 1;
				ret = 1;
				if (p->pKekka[lCnt].knsflg != 'R') {	/* �f�[�^�A���[���Ή� */
					p->pKekka[lCnt].knsflg = 'A';
				}

			}
		}
		else {
		}
		if (pFld[19][0] == '1') {		/* ���փ`�F�b�N(WS��) */
			flg = SoukanChk(pFld[39], p->pKekka, p->iKekkaNum, lCnt, pFldOD, atoi(pFld[57]));
			if (flg == 1) {
				fSaiken[lCnt].flg = 1;
				ret = 1;
				if (p->pKekka[lCnt].knsflg != 'R') {/* �f�[�^�A���[���Ή� */
					p->pKekka[lCnt].knsflg = 'A';
				}
			}
		}
		else {
		}
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** �����`�F�b�N���s�����ږ��ɍČ����s�����߂������畜��---�� ***/
		if (pFld[22][0] == '1') {		/* ���сE�n���`�F�b�N */
			flg = NyubiYoketuChk(pFld[42], p->pKekka, p->iKekkaNum, lCnt, fNyuYou);
			if (flg == 1) {
				fSaiken[lCnt].flg = 1;
				ret = 1;
				if (p->pKekka[lCnt].knsflg != 'R') {	/* �f�[�^�A���[���Ή� */
					p->pKekka[lCnt].knsflg = 'A';
				}
			}
		}
		else {
		}
/*** �����`�F�b�N���s�����ږ��ɍČ����s�����߂����܂ŕ���---�� ***/
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */

		/* 2006-08-30 Nagata ���͋@�A���[���Ŋ�ߔ{�����Z�b�g����Ă���ꍇ�́A��߃`�F�b�N���s��Ȃ� */
		if( pFld[28][0] == '1' &&
				!(p->pKekka[lCnt].yobiflg01 == '2' && strlen(fSaiken[lCnt].KSBR) != 0) ) {	/* ��ߍČ��`�F�b�N */
			flg = KisyakuChk(pFld[43], p->pKekka, p->iKekkaNum, lCnt, fSaiken[lCnt].KSBR, atoi(pFld[57]));
			/* CHG E.Osada 2006.07.21 �Č��f�[�^�̏ꍇ�������Ō����t���O:'A' */
			if (flg == 1) {
				fSaiken[lCnt].flg = 1;
				ret = 1;
				if (p->pKekka[lCnt].knsflg != 'R') {	/* �f�[�^�A���[���Ή� */
					p->pKekka[lCnt].knsflg = 'A';
				}
			}
			else if (flg == 2) {
				fSaiken[lCnt].flg = 2;
				ret = 0;
				p->pKekka[lCnt].knsflg		= 'R';
			}
		}
		else {
		}

	}

	/* �֘A�E����`�F�b�N�݂̂��ׂẴ`�F�b�N���I����Ă���`�F�b�N����B*/
	for (lCnt = stCnt; lCnt < p->iKekkaNum; lCnt ++) {
// 2009.02.18 moriya ->
		memset(pFld, 0, sizeof(char *)*200);
		memset(pBuff, 0, sizeof(char) * READ_BUFF_SIZE);
		memset(pFldOD, 0, sizeof(char *)*200);
		memset(pBuffOD, 0, sizeof(char) * READ_BUFF_SIZE);
// 2009.02.18 moriya -<

		/* �����`�F�b�N���t�@�C���ǂݍ��� */
#ifdef _DEBUG_
		printf( "RealTimeChk(%d) : �����`�F�b�N���t�@�C���ǂݍ���\n", __LINE__);
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : �����`�F�b�N���t�@�C���ǂݍ���\n", __LINE__);
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
		ret2 = chkInfoRead(0, p->pKekka[lCnt].kmkcd, ReadFileName, pFld, pBuff);
		if ( ret2 != 0 ) {
			/* �����`�F�b�N���Ȃ� */
#ifdef _DEBUG_
			printf( "RealTimeChk(%d) : �����`�F�b�N���t�@�C���ǂݍ��� - �����`�F�b�N���Ȃ�\n", __LINE__);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : �����`�F�b�N���t�@�C���ǂݍ��� - �����`�F�b�N���Ȃ�\n", __LINE__);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf( "RealTimeChk(%d) : p->pKekka[lCnt].kmkcd = %s\n", __LINE__, p->pKekka[lCnt].kmkcd);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : p->pKekka[lCnt].kmkcd = %s\n", __LINE__, p->pKekka[lCnt].kmkcd);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf( "RealTimeChk(%d) : ReadFileName          = %s\n\n", __LINE__, ReadFileName);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : ReadFileName          = %s\n\n", __LINE__, ReadFileName);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
			continue;
		}
		/* �I�[�_�[���t�@�C���ǂݍ��� */
#ifdef _DEBUG_
		printf( "RealTimeChk(%d) : �I�[�_�[���t�@�C���ǂݍ���\n", __LINE__);
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : �I�[�_�[���t�@�C���ǂݍ���\n", __LINE__);
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
		ret2 = chkInfoRead(1, p->pKekka[lCnt].kmkcd, ReadFileNameOD, pFldOD, pBuffOD);
		if ( ret2 != 0 ) {
			/* �����`�F�b�N���Ȃ� */
#ifdef _DEBUG_
			printf( "RealTimeChk(%d) : �I�[�_�[���t�@�C���ǂݍ��� - �����`�F�b�N���Ȃ�\n", __LINE__);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : �I�[�_�[���t�@�C���ǂݍ��� - �����`�F�b�N���Ȃ�\n", __LINE__);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf( "RealTimeChk(%d) : p->pKekka[lCnt].kmkcd = %s\n", __LINE__, p->pKekka[lCnt].kmkcd);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : p->pKekka[lCnt].kmkcd = %s\n", __LINE__, p->pKekka[lCnt].kmkcd);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf( "RealTimeChk(%d) : ReadFileName          = %s\n\n", __LINE__, ReadFileName);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : ReadFileName          = %s\n\n", __LINE__, ReadFileName);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
			continue;
		}
#ifdef _DEBUG_
		printf( "RealTimeChk(%d) : ����`�F�b�N\n", __LINE__);
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : ����`�F�b�N\n", __LINE__);
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
		if (pFld[21][0] == '1') {		/* ����`�F�b�N */
			flg = BungaChk(pFld[41], p->pKekka, p->iKekkaNum, lCnt, pFldOD, fSaiken);
			if (flg == 1) {
				fSaiken[lCnt].flg = 1;
				ret = 1;
				if (p->pKekka[lCnt].knsflg != 'R') {	/* �f�[�^�A���[���Ή� */
					p->pKekka[lCnt].knsflg = 'A';
				}
			}
		}
		else {
		}
#ifdef _DEBUG_
		printf( "RealTimeChk(%d) : �֘A�`�F�b�N\n", __LINE__);
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : �֘A�`�F�b�N\n", __LINE__);
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
		if (pFld[20][0] == '1') {		/* �֘A�`�F�b�N */
			flg = KanrenChk(pFld[40], p->pKekka, p->iKekkaNum, lCnt, pFldOD, fSaiken);
			if( !flg )
				p->pKekka[lCnt].kanrenflg	= '0';
		}
		else {
		}
		/* �v�Z�`�F�b�N */
#ifdef _DEBUG_
		printf( "RealTimeChk(%d) : �v�Z�`�F�b�N\n", __LINE__ );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : �v�Z�`�F�b�N\n", __LINE__);
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : ReadFileName          = %s\n", __LINE__, ReadFileName);
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : ReadFileName          = %s\n", __LINE__, ReadFileName);
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : pFld[18][0] = [%c]\n", __LINE__, pFld[18][0] );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : pFld[18][0] = [%c]\n", __LINE__, pFld[18][0] );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : pFld[19][0] = [%c]\n", __LINE__, pFld[19][0] );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : pFld[19][0] = [%c]\n", __LINE__, pFld[19][0] );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : pFld[20][0] = [%c]\n", __LINE__, pFld[20][0] );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : pFld[20][0] = [%c]\n", __LINE__, pFld[20][0] );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : pFld[21][0] = [%c]\n", __LINE__, pFld[21][0] );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : pFld[21][0] = [%c]\n", __LINE__, pFld[21][0] );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : pFld[22][0] = [%c]\n", __LINE__, pFld[22][0] );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : pFld[22][0] = [%c]\n", __LINE__, pFld[22][0] );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : pFld[23][0] = [%c]\n", __LINE__, pFld[23][0] );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : pFld[23][0] = [%c]\n", __LINE__, pFld[23][0] );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : pFld[24][0] = [%c]\n", __LINE__, pFld[24][0] );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : pFld[24][0] = [%c]\n", __LINE__, pFld[24][0] );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : pFld[25][0] = [%c]\n", __LINE__, pFld[25][0] );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : pFld[25][0] = [%c]\n", __LINE__, pFld[25][0] );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : pFld[26][0] = [%c]\n", __LINE__, pFld[26][0] );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : pFld[26][0] = [%c]\n", __LINE__, pFld[26][0] );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : pFld[27][0] = [%c]\n", __LINE__, pFld[27][0] );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : pFld[27][0] = [%c]\n", __LINE__, pFld[27][0] );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : pFld[28][0] = [%c]\n", __LINE__, pFld[28][0] );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : pFld[28][0] = [%c]\n", __LINE__, pFld[28][0] );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : p->pKekka[lCnt].kmkcd = %s\n\n", __LINE__, p->pKekka[lCnt].kmkcd);
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : p->pKekka[lCnt].kmkcd = %s\n\n", __LINE__, p->pKekka[lCnt].kmkcd);
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
		if (pFld[25][0] == '1') {
#ifdef _DEBUG_
			printf( "RealTimeChk(%d) : �v�Z�`�F�b�N������\n", __LINE__ );
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : �v�Z�`�F�b�N������\n", __LINE__ );
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
			kCnt += KeisanChk(pFld[45], p->pKekka, p->iKekkaNum, lCnt, pFldOD, &kekkabuf[kCnt]);
		}
	}
#ifdef _DEBUG_
	printf( "\n�� RealTimeChk(%d) : kCnt = [%d]\n", __LINE__, kCnt );
	memset(cMsgBuf, 0, sizeof(cMsgBuf));
	sprintf(cMsgBuf, "\n�� RealTimeChk(%d) : kCnt = [%d]\n", __LINE__, kCnt );
	sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif

	/***
	 ***	�v�Z���ڏ���
	 ***		�����Ōv�Z���ڂ̌��ʂ�p->pKekka�ϐ��ɒǉ�����
	 ***/
	if (kCnt > 0) {
		/*---------------------------------------------------------------------*/
		/*	�ǉ��O�̌��ʌ�����ޔ�                                             */
		/*		���̒l�͍Č��t���O�ݒ莞�Ɏg�p����                             */
		/*---------------------------------------------------------------------*/
		li_SaveKekkaNum = p->iKekkaNum ;

		/*---------------------------------------------------------------------*/
		/*  �����I�[�_���擾                                                 */
		/*		���ʒǉ����̐ݒ�l�Ƃ��Ďg�p����                               */
		/*---------------------------------------------------------------------*/
		li_KenorderCnt = 0 ;
		li_RetSts = GetKenorder ( p, ORDER_DAT_1, &li_KenorderCnt );
		if( li_RetSts != RTN_OK ) {
			li_RetSts = GetKenorder ( p, ORDER_DAT_2, &li_KenorderCnt );
		}
#ifdef _DEBUG_
		printf( "\n�� RealTimeChk(%d) : GetKenorder��\n", __LINE__, kCnt );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "\n�� RealTimeChk(%d) : GetKenorder��\n", __LINE__, kCnt );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif

		/*---------------------------------------------------------------------*/
		/*	�Č��t���O�ݒ�̈�쐬���ݒ�                                       */
		/*		�v�Z���ڂ����ʂɒǉ���A�ēx���A���`�F�b�N���s��               */
		/*---------------------------------------------------------------------*/
		nfSaiken = malloc(sizeof(SaikenInfo)*(p->iKekkaNum + kCnt));
		memset(nfSaiken, 0, sizeof(SaikenInfo)*(p->iKekkaNum + kCnt));
		memcpy(nfSaiken, fSaiken, sizeof(SaikenInfo)*(p->iKekkaNum + kCnt));
#ifdef _DEBUG_
		printf( "\n�� RealTimeChk(%d) : malloc��\n", __LINE__, kCnt );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "\n�� RealTimeChk(%d) : malloc��\n", __LINE__, kCnt );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif

		/*---------------------------------------------------------------------*/
		/*	���ʏ��Ɍv�Z���ڂ�ǉ�����                                       */
		/*		kCnt : �����ׂ��v�Z���ڐ�                                    */
		/*---------------------------------------------------------------------*/
		for ( li_idxC = 0; li_idxC < kCnt; li_idxC ++ ) {
			if( li_idxC == 0 ) iKnssu = p->pKekka[li_idxC].knssu;	/* ADD E.Osada 2006-08-12 */
			/* ADD Nagata 2006-09-02 */
			/*     �����H���敪�́A�t�@�C���̂P���R�[�h��������p�� */
			if( li_idxC == 0 ) cKsktkbn = p->pKekka[li_idxC].ksktkbn;

			/*	���ʏ�񌟍� */
			for ( li_idxK = 0; li_idxK < p->iKekkaNum ; li_idxK ++ ) {
				if ( memcmp ( kekkabuf[li_idxC].KMKCD,
							  p->pKekka[li_idxK].kmkcd, 7) == 0) {
					break;
				}
			}
			if (li_idxK < p->iKekkaNum )  {
				/*	���ɑ��݂����ꍇ�͒l�����ύX���� */
				if ( kekkabuf[li_idxC].flgRawNone == MY_FLG_ON ) {
					memset ( p->pKekka[li_idxK].rawdata, ' ', sizeof ( p->pKekka[li_idxK].rawdata ) - 1 ) ;
					/* MOD(S) 2006.08.11 Hiwa �v�Z�t���O='2'����߂ăG���[�t���O='2' */
					p->pKekka[li_idxK].yobiflg01 = '2';
				}
				else {
					sprintf(p->pKekka[li_idxK].rawdata, "%f", kekkabuf[li_idxC].raw);
				}
				continue;
			}
			/*	���݂��Ȃ��ꍇ�̓I�[�_���ɑ��݂��邩�`�F�b�N���s�� */
			for ( li_idxO = 0; li_idxO < li_KenorderCnt ; li_idxO ++) {
				if ( memcmp( kekkabuf[li_idxC].KMKCD,
							 pKenorder[li_idxO].kmkcd, 7) == 0) {
					break;
				}
			}
			if (li_idxO >= li_KenorderCnt ) {
				/*	���݂��Ȃ��ꍇ�͎��̌v�Z���ڂɈڂ� */
				continue;
			}
			/*	���݂���ꍇ�A���ʏ���ǉ����� */
#ifdef _DEBUG_
			printf( "\n�� RealTimeChk(%d) : ���݂���ꍇ�A���ʏ���ǉ�����\n", __LINE__, kCnt );
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "\n�� RealTimeChk(%d) : ���݂���ꍇ�A���ʏ���ǉ�����\n", __LINE__, kCnt );
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
//			p->iKekkaNum++ ;
			p->pKekka = realloc ( p->pKekka, sizeof(Kekka)*(p->iKekkaNum + 1) ) ;
//			p->pKekka = realloc ( p->pKekka, sizeof(Kekka)*(p->iKekkaNum) ) ;
#ifdef _DEBUG_
			printf( "\n�� RealTimeChk(%d) : realloc��\n", __LINE__, kCnt );
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "\n�� RealTimeChk(%d) : realloc��\n", __LINE__, kCnt );
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
			SetKekkaData ( p, li_idxO ) ;
			/* ADD E.Osada 2006-08-12 �����R�[�h�̓N���A���� */
			memset(p->pKekka[p->iKekkaNum].nbkmkcd, 0, sizeof(p->pKekka[p->iKekkaNum].nbkmkcd));
			memset(p->pKekka[p->iKekkaNum].jisksbr, 0, sizeof(p->pKekka[p->iKekkaNum].jisksbr));
			p->pKekka[p->iKekkaNum].knssu = iKnssu;
			/* ADD Nagata 2006-09-02 */
			/*     �����H���敪�́A�t�@�C���̂P���R�[�h��������p�� */
			p->pKekka[p->iKekkaNum].ksktkbn = cKsktkbn;

			if ( kekkabuf[li_idxC].flgRawNone == MY_FLG_ON ) {
				memset ( p->pKekka[p->iKekkaNum].rawdata, ' ', sizeof ( p->pKekka[p->iKekkaNum].rawdata ) - 1 ) ;
				/* MOD(S) 2006.08.11 Hiwa �v�Z�t���O='2'����߂ăG���[�t���O='2' */
				p->pKekka[p->iKekkaNum].yobiflg01 = '2';
			}
			else {
				sprintf(p->pKekka[p->iKekkaNum].rawdata, "%f", kekkabuf[li_idxC].raw);
			}
			p->iKekkaNum++ ;
			p->iKekkaCnt++ ;
		}
#ifdef _DEBUG_
		printf( "\n�� RealTimeChk(%d) : �v�Z������\n", __LINE__, kCnt );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "\n�� RealTimeChk(%d) : �v�Z������\n", __LINE__, kCnt );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif

		free( pKenorder );
		pKenorder = NULL ;

		/*---------------------------------------------------------------------*/
		/*	���A���^�C���`�F�b�N���ċA�I�ɌĂяo��                             */
		/*		�ǉ��܂��͕ύX���ꂽ �v�Z���ڂ̃`�F�b�N�̂���                  */
		/*---------------------------------------------------------------------*/
		ret2 = RealTimeChk(p, nfSaiken);
		/* �`�F�b�N���e���}�[�W����B */
		/*---------------------------------------------------------------------*/
		/*	���������Č��t���O�𔽉f����                                       */
		/*		�I�I�d�v�I�I �������v�Z�q���ڂ̍Č��t���O���X�V����            */
		/*---------------------------------------------------------------------*/
		for (lCnt = 0; lCnt < li_SaveKekkaNum; lCnt++) {
			if (nfSaiken[lCnt].flg == 1) {
				fSaiken[lCnt].flg = 1;
				if (p->pKekka[lCnt].knsflg != 'R') {
					p->pKekka[lCnt].knsflg = 'A';
				} else {
					fSaiken[lCnt].flg = 2;
					p->pKekka[lCnt].knsflg = 'R';
				}
			}
		}

		free(nfSaiken);

	}

/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** Xbarm�Č�����̂��߃t���O��ǉ� ***/
	/* RealTimeChk�̍ċN�Ăяo�����l�����āARealTimeChk(1���)�̏ꍇ�̂݃`�F�b�N����B */
	/* �����x���ċN�Ăяo�����ꂽ�ꍇ�́A��ԍŌ�Ń`�F�b�N���� */
	if (chkCnt == 1) {
		int iPos;
		int iKekkaPos;
		int gXsaiken = 0;
		int saiken   = 0;
		int module;
		char cXmChkFlg;

#ifdef _DEBUG_
		printf("%s������ Xbarm�Č�����\n", Now());
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "%s������ Xbarm�Č�����\n", Now());
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
		// RealTimeChk�ōČ����ݒ肳��Ă��Ȃ������m�F
		for (lCnt = stCnt; lCnt < p->iKekkaNum; lCnt ++) {
			if (fSaiken[lCnt].flg == 1) {
#ifdef _DEBUG_
				printf("%sXbarm�ُ�f�[�^�̂���Xbarm�Č��Ȃ�\n", Now());
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "%sXbarm�ُ�f�[�^�̂���Xbarm�Č��Ȃ�\n", Now());
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
				saiken = 1;
				break;
			}
		}
		
	    for (iPos = 0; iPos < XBARM_ITEM_NUM; iPos++) {
			// ���ݒ�̈�ɒB������u���C�N
			if (sXbarm_inf[iPos].knsgrp[0] == '\0')
				break;

			// ���������Ă���Xbarm_inf�\���̂̍��ڃR�[�h�ƌ��ʏ��\���̂̍��ڃR�[�h���������A
			// ����������iKekkaPos�̓Y�����m��
			for (iKekkaPos = 0; iKekkaPos < p->iKekkaNum; iKekkaPos++) {
				if (memcmp(sXbarm_inf[iPos].kmkcd,  p->pKekka[iKekkaPos].kmkcd, 7) == 0) {
					break;
				}
			}
			
			/* ������Ȃ������ꍇ */
			if (iKekkaPos == p->iKekkaNum) {
				/* sXbarm_inf�̎��̍��ڃR�[�h�� */
#ifdef _DEBUG_
				printf( "RealTimeChk(%d) : ������Ȃ������ꍇ�AsXbarm_inf�̎��̍��ڃR�[�h��\n", __LINE__ );
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "RealTimeChk(%d) : ������Ȃ������ꍇ�AsXbarm_inf�̎��̍��ڃR�[�h��\n", __LINE__ );
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
				continue;
			}

			/* ���ڃ}�X�^����X-M�`�F�b�N�t���O���擾('0':�ُ픻����s���A'1':�ُ픻����s��Ȃ�) */
			cXmChkFlg = GetXmChkFlg(p->pKekka[iKekkaPos].knsgrp, p->pKekka[iKekkaPos].kmkcd, p->pKekka[iKekkaPos].knskisymd);

			/* X-M�`�F�b�N�t���O(0:�ُ픻����s���A1:�ُ픻����s��Ȃ�) */
			if (cXmChkFlg == '1') {
#ifdef _DEBUG_
				printf( "RealTimeChk(%d) : p->pKekka[iKekkaPos].knsgrp    = %s\n", __LINE__, p->pKekka[iKekkaPos].knsgrp );
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "RealTimeChk(%d) : p->pKekka[iKekkaPos].knsgrp    = %s\n", __LINE__, p->pKekka[iKekkaPos].knsgrp );
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
				printf( "RealTimeChk(%d) : p->pKekka[iKekkaPos].kmkcd     = %s\n", __LINE__, p->pKekka[iKekkaPos].kmkcd );
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "RealTimeChk(%d) : p->pKekka[iKekkaPos].kmkcd     = %s\n", __LINE__, p->pKekka[iKekkaPos].kmkcd );
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
				printf( "RealTimeChk(%d) : cXmChkFlg == '%c' �Ȃ̂ŁAX-M�ُ픻����s��Ȃ�\n", __LINE__, cXmChkFlg );
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "RealTimeChk(%d) : cXmChkFlg == '%c' �Ȃ̂ŁAX-M�ُ픻����s��Ȃ�\n", __LINE__, cXmChkFlg );
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
				continue;
			}

#ifdef _DEBUG_
			printf("RealTimeChk(%d) : gXsaiken �O                    = %d\n", __LINE__, gXsaiken);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : gXsaiken �O                    = %d\n", __LINE__, gXsaiken);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
			gXsaiken = sXbarm_inf[iPos].saiken;

			GetModule(p->pKekka[iKekkaPos].bskgok, &module);
#ifdef _DEBUG_
			printf("RealTimeChk(%d) : gXsaiken ��                    = %d\n", __LINE__, gXsaiken);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : gXsaiken ��                    = %d\n", __LINE__, gXsaiken);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : saiken                         = %d\n", __LINE__, saiken);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : saiken                         = %d\n", __LINE__, saiken);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : sXbarm_inf[iPos].iModuleNum    = %d\n", __LINE__, sXbarm_inf[iPos].iModuleNum);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : sXbarm_inf[iPos].iModuleNum    = %d\n", __LINE__, sXbarm_inf[iPos].iModuleNum);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : module                         = %d\n", __LINE__, module);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : module                         = %d\n", __LINE__, module);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : sXbarm_inf[iPos].kmkcd         = %s\n", __LINE__, sXbarm_inf[iPos].kmkcd);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : sXbarm_inf[iPos].kmkcd         = %s\n", __LINE__, sXbarm_inf[iPos].kmkcd);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : p->pKekka[iKekkaPos].kntno     = %s\n", __LINE__, p->pKekka[iKekkaPos].kntno);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : p->pKekka[iKekkaPos].kntno     = %s\n", __LINE__, p->pKekka[iKekkaPos].kntno);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : p->pKekka[iKekkaPos].kmkcd     = %s\n", __LINE__, p->pKekka[iKekkaPos].kmkcd);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : p->pKekka[iKekkaPos].kmkcd     = %s\n", __LINE__, p->pKekka[iKekkaPos].kmkcd);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : p->pKekka[iKekkaPos].knssu     = %d\n", __LINE__, p->pKekka[iKekkaPos].knssu);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : p->pKekka[iKekkaPos].knssu     = %d\n", __LINE__, p->pKekka[iKekkaPos].knssu);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : p->pKekka[iKekkaPos].bskgok    = %s\n", __LINE__, p->pKekka[iKekkaPos].bskgok);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : p->pKekka[iKekkaPos].bskgok    = %s\n", __LINE__, p->pKekka[iKekkaPos].bskgok);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : p->pKekka[iKekkaPos].irikbn    = %c\n\n", __LINE__, p->pKekka[iKekkaPos].irikbn);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : p->pKekka[iKekkaPos].irikbn    = %c\n\n", __LINE__, p->pKekka[iKekkaPos].irikbn);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif

			// Xbarm�Č��������̏������Ȃ�A�X�e�[�^�X��i�߂�
			if (gXsaiken == 1 && (p->pKekka[iKekkaPos].knssu >= 2 || saiken == 0)) {
#ifdef _DEBUG_
				printf("%s ������ Xbarm�Č��t���O2�ݒ�(kntno  = %s)\n", Now(), p->pKekka[iKekkaPos].kntno);
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "%s ������ Xbarm�Č��t���O2�ݒ�(kntno  = %s)\n", Now(), p->pKekka[iKekkaPos].kntno);
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
				printf("%s                            (knsgrp = %s)\n", Now(), p->pKekka[iKekkaPos].knsgrp);
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "%s                            (knsgrp = %s)\n", Now(), p->pKekka[iKekkaPos].knsgrp);
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
				printf("%s                            (kmkcd  = %s)\n", Now(), p->pKekka[iKekkaPos].kmkcd);
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "%s                            (kmkcd  = %s)\n", Now(), p->pKekka[iKekkaPos].kmkcd);
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
				printf("%s                            (knssu  = %d)\n", Now(), p->pKekka[iKekkaPos].knssu);
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "%s                            (knssu  = %d)\n", Now(), p->pKekka[iKekkaPos].knssu);
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
				printf("%s                            (module = %d)\n\n", Now(), module);
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "%s                            (module = %d)\n\n", Now(), module);
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
				gXsaiken = 2;
				// 1:Xbarm�Č��ݒ�A2:�ݒ莞�̃`�F�b�N�I���E���񕪂���Č������J�n�A3:Xbarm�Č�������
			} else
			// Xbarm�Č��w����̐��팟�̂̏ꍇ�A�ΏۃO���[�v�E���ڂ�����΂�����Č�����
		   	if (gXsaiken == 2 && saiken == 0 && p->pKekka[iKekkaPos].knssu <= 1 && p->pKekka[iKekkaPos].irikbn != 'Z') {
				// Xbarm�Č����ŁA���Č��t���O�������Ă��Ȃ��i����j�ꍇ
				for (lCnt = stCnt; lCnt < p->iKekkaNum; lCnt ++) {
					if ((memcmp(sXbarm_inf[iPos].knsgrp, p->pKekka[lCnt].knsgrp, 16) == 0) &&
					    (memcmp(sXbarm_inf[iPos].kmkcd,  p->pKekka[lCnt].kmkcd,   7) == 0) &&
					    (sXbarm_inf[iPos].iModuleNum == module)) {
#ifdef _DEBUG_
						printf("%s ������ Xbarm�Č��t���O3�ݒ�(kntno  = %s)\n", Now(), p->pKekka[lCnt].kntno);
						memset(cMsgBuf, 0, sizeof(cMsgBuf));
						sprintf(cMsgBuf, "%s ������ Xbarm�Č��t���O3�ݒ�(kntno  = %s)\n", Now(), p->pKekka[lCnt].kntno);
						sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
						printf("%s                            (knsgrp = %s)\n", Now(), p->pKekka[lCnt].knsgrp);
						memset(cMsgBuf, 0, sizeof(cMsgBuf));
						sprintf(cMsgBuf, "%s                            (knsgrp = %s)\n", Now(), p->pKekka[lCnt].knsgrp);
						sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
						printf("%s                            (kmkcd  = %s)\n", Now(), p->pKekka[lCnt].kmkcd);
						memset(cMsgBuf, 0, sizeof(cMsgBuf));
						sprintf(cMsgBuf, "%s                            (kmkcd  = %s)\n", Now(), p->pKekka[lCnt].kmkcd);
						sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
						printf("%s                            (knssu  = %d)\n", Now(), p->pKekka[iKekkaPos].knssu);
						memset(cMsgBuf, 0, sizeof(cMsgBuf));
						sprintf(cMsgBuf, "%s                            (knssu  = %d)\n", Now(), p->pKekka[iKekkaPos].knssu);
						sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
						printf("%s                            (module = %d)\n\n", Now(), module);
						memset(cMsgBuf, 0, sizeof(cMsgBuf));
						sprintf(cMsgBuf, "%s                            (module = %d)\n\n", Now(), module);
						sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
						fSaiken[lCnt].flg = 1;
						ret = 1;
						gXsaiken = 3; // �Č��ݒ肵���猋�ʏ��E�\���Q��Xbarm�Č���ݒ�
						p->pKekka[lCnt].tobiflg02 = '1';
#ifdef _DEBUG_
						printf( "RealTimeChk(%d) : p->pKekka[lCnt].tobiflg02 = %c\n\n", __LINE__, p->pKekka[lCnt].tobiflg02 );
						memset(cMsgBuf, 0, sizeof(cMsgBuf));
						sprintf(cMsgBuf, "RealTimeChk(%d) : p->pKekka[lCnt].tobiflg02 = %c\n\n", __LINE__, p->pKekka[lCnt].tobiflg02 );
						sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
						if (p->pKekka[lCnt].knsflg != 'R') {
							p->pKekka[lCnt].knsflg = 'A';
						}
					}
				}
			}
			sXbarm_inf[iPos].saiken = gXsaiken;
#ifdef _DEBUG_
			printf("RealTimeChk(%d) : sXbarm_inf[iPos].knsgrp        = %s\n", __LINE__, sXbarm_inf[iPos].knsgrp);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : sXbarm_inf[iPos].knsgrp        = %s\n", __LINE__, sXbarm_inf[iPos].knsgrp);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : sXbarm_inf[iPos].kmkcd         = %s\n", __LINE__, sXbarm_inf[iPos].kmkcd);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : sXbarm_inf[iPos].kmkcd         = %s\n", __LINE__, sXbarm_inf[iPos].kmkcd);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : sXbarm_inf[iPos].iModuleNum    = %d\n", __LINE__, sXbarm_inf[iPos].iModuleNum);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : sXbarm_inf[iPos].iModuleNum    = %d\n", __LINE__, sXbarm_inf[iPos].iModuleNum);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : module                         = %d\n", __LINE__, module);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : module                         = %d\n", __LINE__, module);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : gXsaiken                       = %d\n\n", __LINE__, gXsaiken);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : gXsaiken                       = %d\n\n", __LINE__, gXsaiken);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
		}
	}
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */

	free(pFld);
	free(pBuff);
	free(pFldOD);
	free(pBuffOD);

	stCnt = 0;
	chkCnt --;
#ifdef _DEBUG_
	printf("\n������ RealTimeChk(%d���) End ret(%d)\n", chkCnt + 1, ret);
	memset(cMsgBuf, 0, sizeof(cMsgBuf));
	sprintf(cMsgBuf, "\n������ RealTimeChk(%d���) End ret(%d)\n", chkCnt + 1, ret);
	sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif

	return ret;
}
/******************************************************************************/
/*	�� �� ��  �FSetKekkaDefault()											  */
/*	�@�\�T�v  �F���ʏ��Default�ݒ�											  */
/*	��	  ��  �F															  */
/*	 ��P���� �FpKekka	: ���ʏ��\���̃|�C���^							  */
/*	�o	  ��  �FpKekka	: 													  */
/*	���A���  �Fvoid														  */
/******************************************************************************/
void SetKekkaDefault(Kekka *pKekka)
{
#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	pKekka->pncrgflg		= '0';				// �p�j�b�N�����W�t���O
	pKekka->knspncrgflg		= '0';				// �������p�j�b�N�����W�t���O
	pKekka->kkaksflg		= '0';				// ���ʊ��Z�t���O

	pKekka->kkajkcd			= '3';				// ���ʏ󋵃R�[�h

	pKekka->frkkaflg		= '0';				// �t���[���ʃt���O
	pKekka->gzbsflg			= '0';				// �摜�ʎ��t���O

	pKekka->kkaysnflg		= '1';				// ���ʗD��t���O
	pKekka->tnyrkflg		= ' ';				// ����̓t���O
	pKekka->siyflg			= '1';				// �̗p�t���O
	pKekka->kkassflg		= '0';				// ���ʏC���t���O

	pKekka->knsflg			= 'X';				// �����t���O
	pKekka->renjicflg		= '0';				// �����W�`�F�b�N
	pKekka->soukn1flg		= '0';				// ���փ`�F�b�N(WS��)
	pKekka->kanrenflg		= '0';				// �֘A�`�F�b�N
	pKekka->bunkkuflg		= '0';				// ����`�F�b�N
	pKekka->kesseiflg		= '0';				// ���сE�n���`�F�b�N
	pKekka->rirekiflg		= '0';				// �����`�F�b�N
	pKekka->syougoflg		= '0';				// �ƍ��`�F�b�N
	pKekka->keisanflg		= '0';				// �v�Z�`�F�b�N
	pKekka->per100flg		= '0';				// �P�O�O���`�F�b�N
	pKekka->tousekflg		= '0';				// ���͑O��`�F�b�N
	pKekka->kisyakflg		= '0';				// ��ߍČ��`�F�b�N
	pKekka->kouseiflg		= '0';				// �Z������
	pKekka->syoungflg		= '0';				// �ƍ�NG�m�菈��
	pKekka->soukn2flg		= '0';				// ���փ`�F�b�N(WS��)
	pKekka->fukaptflg		= '0';				// ���׃p�^�[���`�F�b�N
	pKekka->yobiflg01		= '1';				//
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*	pKekka->tobiflg02		= '1';				// Xbarm�Č��w�� */
	pKekka->tobiflg02		= '0';				// Xbarm�Č��w��
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
	pKekka->yobiflg03		= '1';				//
	pKekka->yobiflg04		= '1';				//
	pKekka->yobiflg05		= '1';				//
}

/******************************************************************************/
/*	�� �� ��  �FSetKekkaDefaultSpace()										  */
/*	�@�\�T�v  �F���ʏ��Default�ݒ�(�X�y�[�X�������́A"/"���ʑΉ��j			  */
/*	��	  ��  �F															  */
/*	 ��P���� �FpKekka	: ���ʏ��\���̃|�C���^							  */
/*	�o	  ��  �FpKekka	: 													  */
/*	���A���  �Fvoid														  */
/******************************************************************************/
void SetKekkaDefaultSpace(Kekka *pKekka)
{
#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	pKekka->pncrgflg		= '0';				// �p�j�b�N�����W�t���O
	pKekka->knspncrgflg		= '0';				// �������p�j�b�N�����W�t���O
	pKekka->kkaksflg		= '0';				// ���ʊ��Z�t���O

	pKekka->kkajkcd			= '3';				// ���ʏ󋵃R�[�h

	pKekka->frkkaflg		= '0';				// �t���[���ʃt���O
	pKekka->gzbsflg			= '0';				// �摜�ʎ��t���O

	pKekka->kkaysnflg		= '1';				// ���ʗD��t���O
	pKekka->tnyrkflg		= ' ';				// ����̓t���O
	pKekka->siyflg			= '1';				// �̗p�t���O
	pKekka->kkassflg		= '0';				// ���ʏC���t���O

	// 2006/08/12 nagata �t���O�ނ͋󔒂̎��Ƀf�t�H���g�l���Z�b�g����
	if(pKekka->knsflg  == '\0'){
		pKekka->knsflg			= 'R';				// �����t���O
	}
	if(pKekka->renjicflg == '\0'){
		pKekka->renjicflg		= '0';				// �����W�`�F�b�N
	}
	if(pKekka->soukn1flg == '\0'){
		pKekka->soukn1flg		= '0';				// ���փ`�F�b�N(WS��)
	}
	if(pKekka->kanrenflg == '\0'){
		pKekka->kanrenflg		= '0';				// �֘A�`�F�b�N
	}
	if(pKekka->bunkkuflg == '\0'){
		pKekka->bunkkuflg		= '0';				// ����`�F�b�N
	}
	if(pKekka->kesseiflg == '\0'){
		pKekka->kesseiflg		= '0';				// ���сE�n���`�F�b�N
	}
	if(pKekka->rirekiflg == '\0'){
		pKekka->rirekiflg		= '0';				// �����`�F�b�N
	}
	if(pKekka->syougoflg == '\0'){
		pKekka->syougoflg		= '0';				// �ƍ��`�F�b�N
	}
	if(pKekka->keisanflg == '\0'){
		pKekka->keisanflg		= '0';				// �v�Z�`�F�b�N
	}
	if(pKekka->per100flg == '\0'){
		pKekka->per100flg		= '0';				// �P�O�O���`�F�b�N
	}
	if(pKekka->tousekflg == '\0'){
		pKekka->tousekflg		= '0';				// ���͑O��`�F�b�N
	}
	if(pKekka->kisyakflg == '\0'){
		pKekka->kisyakflg		= '0';				// ��ߍČ��`�F�b�N
	}
	if(pKekka->kouseiflg == '\0'){
		pKekka->kouseiflg		= '0';				// �Z������
	}
	if(pKekka->syoungflg == '\0'){
		pKekka->syoungflg		= '0';				// �ƍ�NG�m�菈��
	}
	if(pKekka->soukn2flg == '\0'){
		pKekka->soukn2flg		= '0';				// ���փ`�F�b�N(WS��)
	}
	if(pKekka->fukaptflg == '\0'){
		pKekka->fukaptflg		= '0';				// ���׃p�^�[���`�F�b�N
	}
	if(pKekka->yobiflg01 == '\0'){
		pKekka->yobiflg01		= '1';				//
	}
	if(pKekka->tobiflg02 == '\0'){
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
	/*	pKekka->tobiflg02		= '1';				//*/
		pKekka->tobiflg02		= '0';				// Xbarm�Č��w��
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
	}
	if(pKekka->yobiflg03 == '\0'){
		pKekka->yobiflg03		= '1';				//
	}
	if(pKekka->yobiflg04 == '\0'){
		pKekka->yobiflg04		= '1';				//
	}
	if(pKekka->yobiflg05 == '\0'){
		pKekka->yobiflg05		= '1';				//
	}
}

/******************************************************************************/
/*	�� �� ��  �FchkInfoRead()												  */
/*	�@�\�T�v  �F�t�@�C�����ǂݏo��										  */
/*	��	  ��  �F															  */
/*	 ��P���� �F���[�h	: 0:�����`�F�b�N�t�@�C��/ 1:�I�[�_�[�t�@�C��		  */
/*	 ��Q���� �Fkmkcd	:	���ڃR�[�h										  */
/*	 ��R���� �FfName	:	�t�@�C����										  */
/*	�o	  ��  �FData	:	���i�w�荀�ڃR�[�h�j							  */
/*			  �Fbuff	:	�o�͗p�o�b�t�@									  */
/*	���A���  �Fint															  */
/*					0:����													  */
/*					1:�ُ�(���ڃR�[�h����)									  */
/*					2:�ُ�i���̑��j										  */
/******************************************************************************/
int chkInfoRead(int mode, char * kmkcd,char * fName, char **Data, char *buff)
{
	FILE * fp;

	char		** pFld;
	int			cnt;
	int			offset;
	int			ret = 1;
	int			hitFlg = 0;

	char		fPath[256];
#ifdef _DEBUG_
	char		cMsgBuf[512];
#endif

#ifdef _DEBUG_
	printf( "chkInfoRead(%d) : �I�[�_�[���t�@�C���ǂݍ���\n", __LINE__);
	memset(cMsgBuf, 0, sizeof(cMsgBuf));
	sprintf(cMsgBuf, "chkInfoRead(%d) : �I�[�_�[���t�@�C���ǂݍ���\n", __LINE__);
	sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
	strncpy(fPath, GetFolder, 256);
	if (mode == 1) {
		strcat(fPath, "local/");
	}
	strncat(fPath, fName, 256);
#ifdef _DEBUG_
	printf( "chkInfoRead(%d) : fPath = [%s]\n", __LINE__, fPath);
	memset(cMsgBuf, 0, sizeof(cMsgBuf));
	sprintf(cMsgBuf, "chkInfoRead(%d) : fPath = [%s]\n", __LINE__, fPath);
	sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif

	fp = fopen(fPath, "r");
	if (fp == NULL) {
		// ���[�J������擾�ł��Ȃ��Ƃ���2�Ԗڂ̃p�X��T���B
		strncpy(fPath, GetFolder2, 256);
		strncat(fPath, fName, 256);

		fp = fopen(fPath, "r");
		if (fp == NULL) {
			return 2;
		}
	}

	pFld = malloc(sizeof(char *)*200);
#ifdef _DEBUG_
	printf( "chkInfoRead(%d) : pFld = malloc\n", __LINE__);
	memset(cMsgBuf, 0, sizeof(cMsgBuf));
	sprintf(cMsgBuf, "chkInfoRead(%d) : pFld = malloc\n", __LINE__);
	sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
	while (fgets(buff, READ_BUFF_SIZE, fp)) {
		// �J���}��؂�̃��R�[�h�𕪊����A
		hitFlg = 0;
		cnt = 0;
		offset = 0;;
		pFld[cnt] = &buff[cnt];
		cnt++;
		while (buff[offset] != '\0') {
			if (buff[offset] == ',') {
				pFld[cnt] = &buff[offset+1];
				buff[offset] = '\0';
				if (cnt == 5) {
					if (strncmp(kmkcd, pFld[5], 7) == 0) {
						hitFlg = 1;
#ifdef _DEBUG_
						printf( "chkInfoRead(%d) : pFld[5] = [%s]\n", __LINE__, pFld[5]);
						memset(cMsgBuf, 0, sizeof(cMsgBuf));
						sprintf(cMsgBuf, "chkInfoRead(%d) : pFld[5] = [%s]\n", __LINE__, pFld[5]);
						sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
					}
					else {
						break;
					}
				}
				cnt++;
			}
			offset++;
		}
		if (hitFlg == 0) {
			continue;
		}
		if (mode == 0) {
			if (cnt != 59) {
				// CSV�t�B�[���h���s���i�ǂݔ�΂��j
				continue;
			}
			if (strncmp(kmkcd, pFld[5], 7) == 0) {
				// �w�荀�ڃR�[�h��������
				memcpy(Data, pFld, sizeof(char *) * 118);
#ifdef _DEBUG_
				printf( "chkInfoRead(%d) : pFld[5] = [%s]\n", __LINE__, pFld[5]);
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "chkInfoRead(%d) : pFld[5] = [%s]\n", __LINE__, pFld[5]);
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
				printf( "chkInfoRead(%d) : Data = [%s]\n", __LINE__, Data);
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "chkInfoRead(%d) : Data = [%s]\n", __LINE__, Data);
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
				ret = 0;
				break;
			}
		}
		else {
			if (cnt != 58) {
				// CSV�t�B�[���h���s���i�ǂݔ�΂��j
				continue;
			}
			if (strncmp(kmkcd, pFld[5], 7) == 0) {
#ifdef _DEBUG_
				printf( "chkInfoRead(%d) : pFld[5]�O\n", __LINE__);
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "chkInfoRead(%d) : pFld[5]�O\n", __LINE__);
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
				// �w�荀�ڃR�[�h��������
				memcpy(Data, pFld, sizeof(char *) * 118);
#ifdef _DEBUG_
				printf( "chkInfoRead(%d) : pFld[5]��\n", __LINE__);
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "chkInfoRead(%d) : pFld[5]��\n", __LINE__);
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
				ret = 0;
				break;
			}
		}
	}
#ifdef _DEBUG_
	printf( "chkInfoRead(%d) : free(pFld)�O\n", __LINE__);
	memset(cMsgBuf, 0, sizeof(cMsgBuf));
	sprintf(cMsgBuf, "chkInfoRead(%d) : free(pFld)�O\n", __LINE__);
	sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif

	free(pFld);
#ifdef _DEBUG_
	printf( "chkInfoRead(%d) : free(pFld)��\n", __LINE__);
	memset(cMsgBuf, 0, sizeof(cMsgBuf));
	sprintf(cMsgBuf, "chkInfoRead(%d) : free(pFld)��\n", __LINE__);
	sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif

	fclose(fp);

#ifdef _DEBUG_
	printf( "chkInfoRead(%d) : ret = [%d]\n", __LINE__, ret);
	memset(cMsgBuf, 0, sizeof(cMsgBuf));
	sprintf(cMsgBuf, "chkInfoRead(%d) : ret = [%d]\n", __LINE__, ret);
	sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif

	return (ret);
}

/******************************************************************************/
/*	�� �� ��  �FKekkaMarume()												  */
/*	�@�\�T�v  �FRAWDATA�̊ۂߏ������s���A�\�����ʂɊi�[����B				  */
/*	��	  ��  �F															  */
/*	 ��P���� �FpKekka	:	���ʏ��\���̔z��								  */
/*	 ��Q���� �FKekkaCnt:	���ʏ��\���̐�								  */
/*	�o	  ��  �FpKekka	:	���ʏ��\���̔z��								  */
/*	���A���  �Fint															  */
/*					0:����													  */
/*					1:�ُ�i���̑��j										  */
/******************************************************************************/
int KekkaMarume(Kekka * pKekka, int KekkaCnt, char * ReadFileName)
{
	int		lCnt;
	char	*pBuff;
	char	**pFld;
	int		ret2;
	int		ketasuu;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	pFld = malloc(sizeof(char *)*200);
	pBuff = malloc(sizeof(char) * READ_BUFF_SIZE);

	for (lCnt = 0; lCnt < KekkaCnt; lCnt ++){
		// �����`�F�b�N���t�@�C���ǂݍ���
		ret2 = chkInfoRead(0, pKekka[lCnt].kmkcd, ReadFileName, pFld, pBuff);
		if ( ret2 != 0 ) {
			// �����`�F�b�N���Ȃ�
			ketasuu = 9;
		}
		else {
			ketasuu = atoi(pFld[57]);
		}

		// �ۂߏ���

		if (ketasuu == 9) {
			strncpy(pKekka[lCnt].hjkka, pKekka[lCnt].rawdata, 20);
		}
		else {
			double		rawData;
			rawData = atof(pKekka[lCnt].rawdata) + 0.00001;
			sprintf(pKekka[lCnt].hjkka, "%.*f", ketasuu, rawData);
		}
	}
	free(pFld);
	free(pBuff);

	return 0;
}
/******************************************************************************/
/*	�� �� ��  �FRenjiChk()													  */
/*	�@�\�T�v  �F�����W�`�F�b�N												  */
/*	��	  ��  �F															  */
/*	 ��P���� �FchkPara	:	�`�F�b�N�p�p�����[�^							  */
/*	 ��Q���� �FpKekka	:	���ʏ��\���̔z��								  */
/*	 ��R���� �FKekkaCnt:	���ʏ��\���̐�								  */
/*	 ��R���� �FlCnt	:	�������ʒu										  */
/*	 ��R���� �FODFld	:	�I�[�_�[���									  */
/*	�o	  ��  �F															  */
/*	���A���  �Fint															  */
/*					0:�Č�����												  */
/*					1:�Č�����												  */
/******************************************************************************/
int	RenjiChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, char **ODFld, int keta)
{
	int			ret = 0;
	double		rawData;
	double		rawData2;
	double		hiData;
	double		loData;
//	int			iCnt;
	int			lpCnt;
	char		tmp[32];
//	char		tmp2[32];
//	char		*chk;
	struct stRNGCHKMST {
		char	HNIKBN; 				//�͈͋敪
		char	KNSGRP[16]; 			//�����O���[�v
		char	KMKCD[7];				//���ڃR�[�h
		char	ZAICD[4];				//�ޗ��R�[�h
		char	KRKNSGRP[7];			//�{�݃R�[�h
		char	SBT;					//����
		char	SSA;					//�㉺���敪
		char	ZEN_KYOYOU;				//���e�敪
		char	HRNG[20];				//�����W���
		char	LRNG [20];				//�����W����
		char	KAIYMD[8];				//�J�n�N����
		char	HAIYMD[8];				//�p�~�N����
		char	HNKTNTID[8];			//�ύX�S��ID
		char	KSNDH[12];				//���X�V����
	} *pRNGCHKMST;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
#ifdef _DEBUG_
	printf("�����W�`�F�b�N");
#endif

	if (pKekka[lCnt].renjicflg == '1' || pKekka[lCnt].renjicflg == '2') {
		// ���Ƀ`�F�b�N�ς݂̎��͏������Ȃ�
		return 0;
	}

	// �����W�}�X�^�̏��
	pRNGCHKMST = (struct stRNGCHKMST *)chkPara;

/*
	memset(tmp, 0, sizeof(tmp));
	strncpy(tmp, pKekka[lCnt].rawdata, 20);
	rawData = atof(tmp);
*/
	memset(tmp, 0, sizeof(tmp));
	strncpy(tmp, pKekka[lCnt].hjkka, 20);
	rawData = atof(tmp);
	//rawData +=  0.00001;
	sprintf(tmp, "%.*f", keta, rawData);
	rawData2 = atof(tmp);

	ret = 0;

	for (lpCnt = 0; lpCnt < (strlen(chkPara) / sizeof(struct stRNGCHKMST)); lpCnt++, pRNGCHKMST++) {
		memset(tmp, 0, sizeof(tmp));
		strncpy(tmp, pRNGCHKMST->HRNG, 20);
		hiData = atof(tmp);

		memset(tmp, 0, sizeof(tmp));
		strncpy(tmp, pRNGCHKMST->LRNG, 20);
		loData = atof(tmp);

/*		// �����W�}�X�^�̒l����ۂߌ��������߂�B
		memset(tmp, 0, sizeof(tmp));
		if (pRNGCHKMST->SSA == '1') {
			// ���l���̎�
			memset(tmp2, 0, sizeof(tmp2));
			strncpy(tmp2, pRNGCHKMST->HRNG, 20);
			trim(tmp, tmp2);
		}
		else {
			// ��l���̂Ƃ�
			memset(tmp2, 0, sizeof(tmp2));
			strncpy(tmp2, pRNGCHKMST->LRNG, 20);
			trim(tmp, tmp2);
		}
		// �����_���������߂�
		iCnt = 0;
		if ((chk = strchr(tmp, '.')) != (char *)NULL) {
			iCnt = strlen(chk + 1);
		}
		// �ۂߏ���
		// �ǉ� osada
		rawData +=  0.00001;

		sprintf(tmp, "%.*f", iCnt, rawData);
		rawData2 = atof(tmp);
*/
		// �����W�`�F�b�N���͑���l���͈͓����`�F�b�N����B
		if ((hiData < rawData2) || (rawData2 < loData)) {
#ifdef _DEBUG_
			printf(" (raw = %f, raw2 = %f, hi = %f, lo = %f)", rawData, rawData2, hiData, loData); 
#endif
			ret = 1;
			break;
		}
	}
//	memset(tmp, 0, sizeof(tmp));
//	strncpy(tmp, pRNGCHKMST->ZEN_KYOYOU, 4);
//	switch (atoi(tmp)) {
//	case 1:		// ��(%)
//		if ((hiData < rawData) || (rawData < loData)) {
//			ret = 1;
//		}
//		break;
//	case 2:		// ��(���)
//		if ((hiData < rawData) || (rawData < loData)) {
//			ret = 1;
//		}
//		break;
//	default:
//		ret = 0;
//		break;
//	}

	if (ret != 0) {
		if (pRNGCHKMST->SSA == '1') {
			pKekka[lCnt].renjicflg = '3';
		}
		else {
			pKekka[lCnt].renjicflg = '4';
		}
#ifdef _DEBUG_
		printf("NG\n");
#endif
	}
	else {
		pKekka[lCnt].renjicflg = '1';
#ifdef _DEBUG_
		printf("OK\n");
#endif
	}
	return ret;
}

/******************************************************************************/
/*	�� �� ��  �FSoukanChk()													  */
/*	�@�\�T�v  �F���փ`�F�b�N(WS��)											  */
/*	��	  ��  �F															  */
/*	 ��P���� �FchkPara	:	�`�F�b�N�p�p�����[�^							  */
/*	 ��Q���� �FpKekka	:	���ʏ��\���̔z��								  */
/*	 ��R���� �FKekkaCnt:	���ʏ��\���̐�								  */
/*	 ��R���� �FlCnt	:	�������ʒu										  */
/*	 ��R���� �FODFld	:	�I�[�_�[���									  */
/*	�o	  ��  �F															  */
/*	���A���  �Fint															  */
/*					0:�Č�����												  */
/*					1:�Č�����												  */
/******************************************************************************/
int	SoukanChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, char **ODFld, int keta)
{
	int			ret = 0;
	char		calBuff[256];
/*	struct stSKCHKMST {
		char	KNSGRP[16];			//�����O���[�v
		char	KMKCD[7];           //���ڃR�[�h
		char	SSTCD[7];           //�{�݃R�[�h
		char	ZAIKBN[4];          //�ޗ��敪(����)
		char	KRKNSGRP[4];        //�s����
		char	SOUKAN[128];        //���֎�
		char	KAIYMD[8];          //�J�n�N����
		char	HAIYMD[8];          //�p�~�N����
		char	HNKTNTID[8];		//�ύX�S��ID
		char	KSNDH[12];          //���X�V����
	} sSKCHKMST, *pSKCHKMST;
*/	struct stSKCHKMST {
		int		KRKNSGRP;           //�s����
		char	SOUKAN[128];        //���֎�
	} sSKCHKMST;
	int			iCnt;	// ���[�v�J�E���^
	int			paraCnt;
	int			i;
	int			setCnt;
	int			tmpCnt;
	char		tmp[32];
	double		calNum;
	double		rawData;

#ifdef _DEBUG_
	printf("SoukanChk(%d)\n", __LINE__);
#endif

	/*----<< Begin add source Feb 27, 2008 H.Sato >>----*/

	char *pszExpandKSNSK = (char *) NULL;
										/* IF ���W�J��̌v�Z��              */
	double dTransferLimit;

	/*----<< End add source Feb 27, 2008 H.Sato >>----*/

	if (pKekka[lCnt].soukn1flg == '1' || pKekka[lCnt].soukn1flg == '2') {
		// ���Ƀ`�F�b�N�ς݂̎��͏������Ȃ�
		return 0;
	}

	paraCnt = 0;
	while (paraCnt < strlen(chkPara)) {
		memset(&sSKCHKMST, 0, sizeof(sSKCHKMST));
		memset(tmp, 0, sizeof(tmp));
		memcpy(tmp, &chkPara[paraCnt], 4);
		sSKCHKMST.KRKNSGRP = atoi(tmp);
		paraCnt += 4;
		for (i = paraCnt + 1; i < 50; i++ ) if (chkPara[i] == '!') break;
		memcpy(sSKCHKMST.SOUKAN, &chkPara[paraCnt+1], i-paraCnt-1);
		paraCnt += (i-paraCnt+1);

		// ���ʒl�̒l������𐔒l������
/*		memset(tmp, 0, sizeof(tmp));
		strncpy(tmp, pKekka[lCnt].rawdata, 20);
		rawData = atof(tmp);
*/		memset(tmp, 0, sizeof(tmp));
		strncpy(tmp, pKekka[lCnt].hjkka, 20);
		rawData = atof(tmp);

		// �����̍��ڃR�[�h�𐔒l�ɒu��������B
		memset(calBuff, 0, sizeof(calBuff));
		for (iCnt = 0, setCnt = 0; iCnt < 128; iCnt++ ) {
			// ���ڃR�[�h�̎n�܂�'['����������B
			if (sSKCHKMST.SOUKAN[iCnt] == '[') {
				// ���ڒl������
				memset(tmp, 0, sizeof(tmp));
				tmpCnt = 0;
				iCnt++;
				// ���ڃR�[�h��]���i�I���ʒu��]��Null�܂Łj
				while (sSKCHKMST.SOUKAN[iCnt] != ']' && sSKCHKMST.SOUKAN[iCnt] != '\0') {
					tmp[tmpCnt++] = sSKCHKMST.SOUKAN[iCnt++];
				}
				// ���ʏ�񂩂�w��̍��ڃR�[�h���������A�u��������B
				for (tmpCnt = 0; tmpCnt < KekkaCnt; tmpCnt++) {
					if (strncmp(pKekka[tmpCnt].kmkcd, tmp, strlen(tmp)) == 0) {
//						strncat(calBuff, pKekka[tmpCnt].rawdata, 21);
						strncat(calBuff, pKekka[tmpCnt].hjkka, 20);
						setCnt = strlen(calBuff);
						break;
					}
				}
				if (tmpCnt == KekkaCnt) {
					// �֘A���ڂ�������Ȃ��B
//					pKekka[lCnt].soukn1flg = '1';
					break;
				}
			}
			else if (KSNSK_SC == (int) sSKCHKMST.SOUKAN[iCnt]) {
				// �g��

				/*---<< Begin modified source May 27, 2008 H.Sato >>---*/
				// ���p�\�Ȓl�ȊO���w�肳��Ă����ꍇ�A�l 0 ���w�肳�ꂽ���̂Ƃ���

				//strncat(calBuff, ODFld[40], 5);
				//setCnt = strlen(calBuff);

				memcpy((void *) gszTransfer, ODFld[FLDIDX_SC], FLDSIZE_SC);
				gszTransfer[FLDSIZE_SC] = (char) '\0';
				if (0 == _isnumeric(gszTransfer)) {
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
				}
				strcat(calBuff, gszTransfer);
				setCnt = strlen(calBuff);

				/*---<< End modified source May 27, 2008 H.Sato >>---*/

			}
			else if (KSNSK_TJ == (int) sSKCHKMST.SOUKAN[iCnt]) {
				// POW�Ƌ�ʂ��邽�߁A�O�̕�����O�Ŗ������`�F�b�N����B
				if (0 < iCnt &&
				    (sSKCHKMST.SOUKAN[iCnt-1] == 'o' ||
				     sSKCHKMST.SOUKAN[iCnt-1] == 'O')) {
					break;
				}
				else {
					// �̏d

					/*---<< Begin modified source May 27, 2008 H.Sato >>---*/
					// ���p�\�Ȓl�ȊO���w�肳��Ă����ꍇ�A�l 0 ���w�肳�ꂽ���̂Ƃ���

					//if (ODFld[41][0] == '0') {
					//	// �̏d��Kg�̎��̓O�����Ōv�Z
					//	memset(tmp, 0, sizeof(tmp));
					//	strncpy(tmp, ODFld[41], 5);
					//	sprintf(tmp,"%-lf",(atof(tmp)*1000));
					//	strcat(calBuff, tmp);
					//}
					//else {
					//	strncat(calBuff, ODFld[41], 5);
					//}

					strncpy(gszTransfer, ODFld[FLDIDX_TJ], FLDSIZE_TJ);
					gszTransfer[FLDSIZE_TJ] = (char) '\0';
					if (0 == _isnumeric(gszTransfer)) {
						gszTransfer[0] = (char) '0';
						gszTransfer[1] = (char) '\0';
					}
					else {
						switch ((int) ODFld[FLDIDX_TJTNI][0]) {
						case _VALUE_TJTNI_KILLOGRAM:
							dTransferLimit = 
									atof(gszTransfer) * (double) 1000.0;
							if ((double) 0.0 < dTransferLimit) {
								sprintf(gszTransfer, "%f", dTransferLimit);
							}
							else {
								gszTransfer[0] = (char) '0';
								gszTransfer[1] = (char) '\0';
							}

						case _VALUE_TJTNI_GRAM:
							break;		/* NOP                              */

						default:
							gszTransfer[0] = (char) '0';
							gszTransfer[1] = (char) '\0';
						}
					}
					strcat(calBuff, gszTransfer);

					/*---<< End modified source May 27, 2008 H.Sato >>---*/

					setCnt = strlen(calBuff);
				}
			}
			else if (KSNSK_TNTME == (int) sSKCHKMST.SOUKAN[iCnt]) {
				// �~�A����

				/*---<< Begin modified source May 27, 2008 H.Sato >>---*/
				// ���p�\�Ȓl�ȊO���w�肳��Ă����ꍇ�A�l 0 ���w�肳�ꂽ���̂Ƃ���

				//strncat(calBuff, ODFld[50], 4);
				//setCnt = strlen(calBuff);

				memcpy((void *) gszTransfer, ODFld[FLDIDX_TNTME], FLDSIZE_TNTME);
				gszTransfer[FLDSIZE_TNTME] = (char) '\0';
				if (0 == _isnumeric(gszTransfer)) {
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
				}
				else {
					switch ((int) ODFld[FLDIDX_TNTNI][0]) {
					/* 2014/02/06 sekiya ���ԒP�ʈȊO�̏ꍇ�͌v�Z���Ȃ��悤�Ɏd�l�ύX
					case _VALUE_TNTNI_MINUTE:
						sprintf(gszTransfer,
						        "%-lf",
						        (atof(gszTransfer) / (double) 60.0));
						gszTransfer[FLDSIZE_TNTME] = (char) '\0';
					*/
					case _VALUE_TNTNI_HOUR:
						break;			/* NOP                             */

					default:
						gszTransfer[0] = (char) '0';
						gszTransfer[1] = (char) '\0';
					}
				}
				strcat(calBuff, gszTransfer);
				setCnt = strlen(calBuff);

				/*---<< End modified source May 27, 2008 H.Sato >>---*/

			}
			else if (KSNSK_TNRYO == (int) sSKCHKMST.SOUKAN[iCnt]) {
				// �~�A��

				/*---<< Begin modified source May 27, 2008 H.Sato >>---*/
				// ���p�\�Ȓl�ȊO���w�肳��Ă����ꍇ�A�l 0 ���w�肳�ꂽ���̂Ƃ���

				//strncat(calBuff, ODFld[52], 5);
				//setCnt = strlen(calBuff);

				memcpy((void *) gszTransfer, ODFld[FLDIDX_TNRYO], FLDSIZE_TNRYO);
				gszTransfer[FLDSIZE_TNRYO] = (char) '\0';
				if (0 == _isnumeric(gszTransfer)) {
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
				}
				else {
					switch ((int) ODFld[FLDIDX_TNRYOTNI][0]) {
					/* 2014/02/06 sekiya �~�����b�g���P�ʈȊO�̏ꍇ�͌v�Z���Ȃ��悤�Ɏd�l�ύX
					case _VALUE_TNRYO_LITER:
						dTransferLimit = atof(gszTransfer) * (double) 1000.0;
						if ((double) 0.0 < dTransferLimit) {
							sprintf(gszTransfer, "%-lf", dTransferLimit);
						}
						else {
							gszTransfer[0] = (char) '0';
							gszTransfer[1] = (char) '\0';
						}
					*/
					case _VALUE_TNRYO_MILLILITER:
						break;

					default:
						gszTransfer[0] = (char) '0';
						gszTransfer[1] = (char) '\0';
					}
				}
				strcat(calBuff, gszTransfer);
				setCnt = strlen(calBuff);

				/*---<< End modified source May 27, 2008 H.Sato >>---*/

			}

			/*----<< Begin add source Feb 27, 2008 H.Sato >>----*/
			/* �v�Z���g���Ή�                                               */

			else if (KSNSK_SBTKBN == sSKCHKMST.SOUKAN[iCnt]) {
				/* ���ʋ敪                                                 */
				if (_VALUE_SBTKBN_MALE == (int) ODFld[FLDIDX_SBTKBN][0] ||
						_VALUE_SBTKBN_FEMALE == (int) ODFld[FLDIDX_SBTKBN][0]) {
					calBuff[setCnt++] = ODFld[FLDIDX_SBTKBN][0];
					calBuff[setCnt] = (char) '\0';
				}
				else {
					calBuff[setCnt++] = (char) _VALUE_SBTKBN_UNKNOWN;
					calBuff[setCnt] = (char) '\0';
										/* �W�J�s��							*/
				}
			}
			else if (KSNSK_AGE == sSKCHKMST.SOUKAN[iCnt]) {
				/* �N��                                                     */
				if (_VALUE_AGEKBN_YEAR != (int) ODFld[FLDIDX_AGEKBN][0]) {
					calBuff[setCnt++] = (char) '0';
					calBuff[setCnt] = (char) '\0';
										/* �W�J�s��							*/
				}
				else {
					memcpy((void *) gszTransfer, ODFld[FLDIDX_AGE], FLDSIZE_AGE);
					gszTransfer[FLDSIZE_AGE] = (char) '\0';
					if (0 == _isnumeric(gszTransfer)) {
						gszTransfer[0] = (char) '0';
						gszTransfer[1] = (char) '\0';
					}
					strcat(calBuff, gszTransfer);
					setCnt = strlen(calBuff);
				}
			}

			/*----<< End add source Feb 27, 2008 H.Sato >>----*/

			else if (sSKCHKMST.SOUKAN[iCnt] == '\0') {
				break;
			}
			else {
				calBuff[setCnt++] = sSKCHKMST.SOUKAN[iCnt];
			}
		}
		// CHG 2006/08/03 E.Osada ���֑���̌��ʂ��X�y�[�X�̏ꍇ�A�v�Z���Ȃ�
		if (tmpCnt == KekkaCnt) {
			// �֘A���ڂ�������Ȃ��B
			break;
		}

		/*----<< Begin add source Feb 27, 2008 H.Sato >>----*/
		/* �v�Z���Ɋ܂܂�� IF ���̓W�J                                     */
#ifdef _DEBUG_
		printf("SoukanChk(%d) : calBuff =�y%s�z\n", __LINE__, calBuff);
		printf("SoukanChk(%d) : pKekka[lCnt].kmkcd =�y%s�z\n", __LINE__, pKekka[lCnt].kmkcd);
#endif
		if (NULL != (void *) (pszExpandKSNSK = OperateKSNSK(calBuff))) {
			if ('\0' != (int) *pszExpandKSNSK) {
				strcpy(calBuff, pszExpandKSNSK);
			}
			free((void *) pszExpandKSNSK);
			pszExpandKSNSK = (char *) NULL;
		}

		/*----<< End add source Feb 27, 2008 H.Sato >>----*/

		// ������̌v�Z�����v�Z����B
		calNum = StringCal(calBuff);
#ifdef _DEBUG_
		printf("SoukanChk(%d) : calNum =�y%.9f�z\n", __LINE__, calNum);
#endif

		// �v�Z���ʂ��ۂ߂�
		if (keta != 9) {
			sprintf(tmp, "%.*f", keta, calNum);
			calNum = atof(tmp);
		}
		// �s�����̐ݒ�ɏ]���A�l�𔻒肷��B
		switch (sSKCHKMST.KRKNSGRP) {
		case 0:	// =
			if (rawData == calNum) {
				ret = 0;
			} else {
				ret = 1;
			}
			break;
		case 1:	// !=
			if (rawData != calNum) {
				ret = 0;
			} else {
				ret = 1;
			}
			break;
		case 2:	// >=
			if (rawData >= calNum) {
				ret = 0;
			} else {
				ret = 1;
			}
			break;
		case 3:	// <=
			if (rawData <= calNum) {
				ret = 0;
			} else {
				ret = 1;
			}
			break;
		case 4:	// >
			if (rawData > calNum) {
				ret = 0;
			} else {
				ret = 1;
			}
			break;
		case 5:	// <
			if (rawData < calNum) {
				ret = 0;
			} else {
				ret = 1;
			}
			break;
		}
//		if (ret == 1) {
//			break;
//		}
	}

	// CHG E.Osada 2006-07-23
	//if (ret == 1) {
	//if( (ret == 1) || (ret == 0) ) {
	if ( ret == 0 ) {
		pKekka[lCnt].soukn1flg = '1';
		//ret = 0;
	}
	else {
		pKekka[lCnt].soukn1flg = '2';
		//ret = 1;
	}

	return ret;
}
/******************************************************************************/
/*	�� �� ��  �FKanrenChk()													  */
/*	�@�\�T�v  �F�֘A�`�F�b�N												  */
/*	��	  ��  �F															  */
/*	 ��P���� �FchkPara	:	�`�F�b�N�p�p�����[�^							  */
/*	 ��Q���� �FpKekka	:	���ʏ��\���̔z��								  */
/*	 ��R���� �FKekkaCnt:	���ʏ��\���̐�								  */
/*	 ��R���� �FlCnt	:	�������ʒu										  */
/*	 ��R���� �FODFld	:	�I�[�_�[���									  */
/*	�o	  ��  �F															  */
/*	���A���  �Fint															  */
/*					0:�Č�����												  */
/*					1:�Č�����												  */
/******************************************************************************/
int	KanrenChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, char **ODFld, SaikenInfo * fSaiken)
{
	int			ret = 0;
//	struct stKRKMKMST {
////		char	KNSGRP[16];		// �����O���[�v
//		char	KMKCD[7];		// ���ڃR�[�h
////		char	KRKNSGRP[4];	// �֘A�����O���[�v
//		char	KRKMKCD[7]; 	// �֘A���ڃR�[�h
//		char	KAIYMD[8];		// �J�n�N����
//		char	HAIYMD[8];		// �p�~�N����
//		char	HNKTNTID[8];	//�ύX�S��ID
//		char	KSNDH[12];		// ���X�V����
//	} *pKRKMKMST;
	int			iCnt;	// ���[�v�J�E���^
	char		*kmkcd;
	int			paraCnt;
//	int	iHit;	// ADD E.Osada 2006-07-21
//	char	cFlg;	// ADD E.Osada 2006-07-21

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	if (pKekka[lCnt].kanrenflg == '1' || pKekka[lCnt].kanrenflg == '2') {
		// ���Ƀ`�F�b�N�ς݂̎��͏������Ȃ�
		return 1;
	}

//	pKRKMKMST = (struct stKRKMKMST *)chkPara;
	kmkcd = chkPara;

//	memset(kmkcd, 0, sizeof(kmkcd));
//	strncpy(kmkcd, pKRKMKMST->KRKMKCD, 7);

	if (pKekka[lCnt].renjicflg < '2' &&
		pKekka[lCnt].soukn1flg < '2' &&
		pKekka[lCnt].kesseiflg < '2' &&
		pKekka[lCnt].rirekiflg < '2' &&
		pKekka[lCnt].syougoflg < '2' &&
		pKekka[lCnt].keisanflg < '2' &&
		pKekka[lCnt].per100flg < '2' &&
		pKekka[lCnt].tousekflg < '2' &&
		pKekka[lCnt].kisyakflg < '2' &&
		pKekka[lCnt].kouseiflg < '2' &&
		pKekka[lCnt].syoungflg < '2' &&
		pKekka[lCnt].soukn2flg < '2' &&
		pKekka[lCnt].fukaptflg < '2' &&
		// DEL E.Osada 2006-08-21 �u�����N���ʂ� '�A' ���t���Ă��܂��Ή�
		//pKekka[lCnt].yobiflg01 < '2' &&
		pKekka[lCnt].tobiflg02 < '2' &&
		pKekka[lCnt].yobiflg03 < '2' &&
		pKekka[lCnt].yobiflg04 < '2' &&
		pKekka[lCnt].yobiflg05 < '2') {
		// ����������̂Ƃ��́A�������Ȃ�
		return 0;
	}

//	iHit = 0;	//ADD E.Osada 2006-07-21
	//CHG E.Osada 2006-08-06 E.Osada
	//for (paraCnt = 0; kmkcd[paraCnt*50] != 0; paraCnt++ ) [
	//	if( !memcmp(&kmkcd[paraCnt*50], "       ", 7) ) break;
	for (paraCnt = 0; kmkcd[paraCnt*7] != 0; paraCnt++ ) {
		if( !memcmp(&kmkcd[paraCnt*7], "       ", 7) ) break;
	//
		for (iCnt = 0; iCnt < KekkaCnt; iCnt++) {
			if (iCnt == lCnt) {
				continue;
			}

			//CHG E.Osada 2006-08-06 E.Osada
			//if(  strncmp(pKekka[iCnt].kmkcd, &kmkcd[(paraCnt*50)+7], 7) == 0 ) [
			if(  strncmp(pKekka[iCnt].kmkcd, &kmkcd[paraCnt*7], 7) == 0 ) {
				ret = 1;
				pKekka[iCnt].kanrenflg = '2';

//CHG E.Osada 2006-08-07
#if 0
				if( (pKekka[lCnt].knsflg == 'R') && (pKekka[iCnt].knsflg != 'R') ) {
					pKekka[iCnt].knsflg = 'R';
					// �����t���O���Č��u�q�v�̏ꍇ�A�����Č����s��Ȃ�
					//		�Q�F�p��Č�
					fSaiken[iCnt].flg = 2;
					ret = 2;
				}
				else {
					// �����t���O���Č��u�q�v�łȂ���Ύ����Č����s��
					//		�P�F�����Č�
					fSaiken[iCnt].flg = 1;
					// 2006/08/06 nagata
					// �����t���O�Ŏ����Č��I�[�_�L����
					// �؂蕪����悤�ɂ������߁A
					// ���̕����ɑ����'A'�ɂ���s�ׂ��K�v�ƂȂ�B
					pKekka[iCnt].knsflg = 'A';
				}

				iHit = 1; //ADD E.Osada 2006-07-21
				//�����������֘A�G���[�̏ꍇ�͎������֘A�G���[�ƂȂ�B
				if( pKekka[iCnt].kanrenflg == '2' ) {
					pKekka[lCnt].kanrenflg = '2';
					if( pKekka[iCnt].knsflg == 'R' ) {
						pKekka[lCnt].knsflg = 'R';
					//ret = 1;
					// �����t���O���Č��u�q�v�̏ꍇ�A�����Č����s��Ȃ�
					//		�Q�F�p��Č�
						ret = 2;
					}
				}
#endif
                ret = 1;
                pKekka[iCnt].kanrenflg = '2';
                pKekka[lCnt].kanrenflg = '2';
//DEL E.Osada 2006-08-21
//�������p���߂̏ꍇ�͑����'A'�ɂ���
                if( pKekka[lCnt].knsflg == 'R' ) {
					if( pKekka[lCnt].kisyakflg == '2' ) {
						//CHG Nagata 2006-09-27 �������p��Č��̎��A
						//		���肪"R"��������A����ɑ΂��ĉ������Ȃ��B
                    	if(pKekka[iCnt].knsflg != 'R'){
                        	pKekka[iCnt].knsflg = 'A';
                        	fSaiken[iCnt].flg = 1;
                        	ret = 1;
						}
					} else {
                    	pKekka[iCnt].knsflg = 'R';
                    	fSaiken[iCnt].flg = 2;
                    	ret = 2;
					}
                }
                if(pKekka[lCnt].knsflg == 'A'){
                    if(pKekka[iCnt].knsflg != 'R'){
                        pKekka[iCnt].knsflg = 'A';
                        fSaiken[iCnt].flg = 1;
                        ret = 1;
                    }
                }
			}
		}
	}
#if 0
	//��l�u�A�v����
	//����������NG�ł����֘A���ڂ����݂��Ȃ������ꍇ�͊֘A�t���O�𗎂Ƃ�
	if( !iHit ) ret = 0;
#endif

	return ret;
}
/******************************************************************************/
/*	�� �� ��  �FBungaChk()													  */
/*	�@�\�T�v  �F����`�F�b�N												  */
/*	��	  ��  �F															  */
/*	 ��P���� �FchkPara	:	�`�F�b�N�p�p�����[�^							  */
/*	 ��Q���� �FpKekka	:	���ʏ��\���̔z��								  */
/*	 ��R���� �FKekkaCnt:	���ʏ��\���̐�								  */
/*	 ��R���� �FlCnt	:	�������ʒu										  */
/*	 ��R���� �FODFld	:	�I�[�_�[���									  */
/*	�o	  ��  �F															  */
/*	���A���  �Fint															  */
/*					0:�Č�����												  */
/*					1:�Č�����												  */
/******************************************************************************/
int	BungaChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, char **ODFld,SaikenInfo * fSaiken)
{
	int			ret = 0;
	int			ret2;
	int			iCnt;	// ���[�v�J�E���^
	char		*pBuffOD;
	char		**pFldOD;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	if (pKekka[lCnt].bunkkuflg == '1' || pKekka[lCnt].bunkkuflg == '2') {
		// ���Ƀ`�F�b�N�ς݂̎��͏������Ȃ�
		return 0;
	}

	pFldOD = malloc(sizeof(char *)*200);
	pBuffOD = malloc(sizeof(char) * READ_BUFF_SIZE);

	if (ODFld[22][0] != '2') {
		// ����q�łȂ��Ƃ�
		free(pFldOD);
		free(pBuffOD);
		pKekka[lCnt].bunkkuflg = '1';
		return 0;
	}

	if (pKekka[lCnt].renjicflg >= '2' ||
		pKekka[lCnt].soukn1flg == '2' ||
		pKekka[lCnt].kesseiflg == '2' ||
		pKekka[lCnt].rirekiflg == '2' ||
		pKekka[lCnt].syougoflg == '2' ||
		pKekka[lCnt].keisanflg == '2' ||
		pKekka[lCnt].per100flg == '2' ||
		pKekka[lCnt].tousekflg == '2' ||
		pKekka[lCnt].kisyakflg == '2' ||
		pKekka[lCnt].kouseiflg == '2' ||
		pKekka[lCnt].syoungflg == '2' ||
		pKekka[lCnt].soukn2flg == '2' ||
		pKekka[lCnt].fukaptflg == '2' ||
		pKekka[lCnt].yobiflg01 == '2' ||
		pKekka[lCnt].tobiflg02 == '2' ||
		pKekka[lCnt].yobiflg03 == '2' ||
		pKekka[lCnt].yobiflg04 == '2' ||
		pKekka[lCnt].yobiflg05 == '2') {
//		cFlg = 1;
	}
	else {
		// �G���[�łȂ��Ƃ�
		free(pFldOD);
		free(pBuffOD);
		pKekka[lCnt].bunkkuflg = '1';
		return 0;
	}

	for (iCnt = 0; iCnt < KekkaCnt; iCnt++) {
//		if (iCnt == lCnt) {
//			continue;
//		}
		ret2 = chkInfoRead(1, pKekka[iCnt].kmkcd, ReadFileNameOD, pFldOD, pBuffOD);
		if ( ret2 != 0 ) {
			// �I�[�_�[���Ȃ�
			continue;
		}
		if (pFldOD[22][0] == '2') {
			// ����q
			if (strncmp(ODFld[20],pFldOD[20],7) == 0) {
				// �e�R�[�h�������Ƃ�
				fSaiken[iCnt].flg = 1;
				ret = 1;
				pKekka[iCnt].bunkkuflg = '2';
				if (pKekka[iCnt].knsflg != 'R') {
					pKekka[iCnt].knsflg = 'A';
				}
//				break;
			}
		}
	}

	if (ret != 0) {
		pKekka[lCnt].bunkkuflg = '2';
	}
	else {
		pKekka[lCnt].bunkkuflg = '1';
	}

	free(pFldOD);
	free(pBuffOD);

	return ret;
}
/******************************************************************************/
/*	�� �� ��  �FNyubiYoketuChk()											  */
/*	�@�\�T�v  �F���сE�n���`�F�b�N											  */
/*	��	  ��  �F															  */
/*	 ��P���� �FchkPara	:	�`�F�b�N�p�p�����[�^							  */
/*	 ��Q���� �FpKekka	:	���ʏ��\���̔z��								  */
/*	 ��R���� �FKekkaCnt:	���ʏ��\���̐�								  */
/*	 ��S���� �FlCnt	:	�������ʒu										  */
/*	 ��T���� �FfNyuYou	:	���сE�n���t���O								  */
/*	�o	  ��  �F															  */
/*	���A���  �Fint															  */
/*					0:�Č�����												  */
/*					1:�Č�����												  */
/******************************************************************************/
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** �����`�F�b�N�E�Č��Ή�                           ***/
/*** �C���Ŋ֐������ɍ쐬���A��������R�����g�A�E�g����---�� ***/
#if 0

int	NyubiYoketuChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, int fNyuYou)
{
	int			ret = 0;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	if (pKekka[lCnt].kesseiflg == '1' || pKekka[lCnt].kesseiflg == '2') {
		// ���Ƀ`�F�b�N�ς݂̎��͏������Ȃ�
		return 0;
	}

	if (fNyuYou == 0) {
		// ���сE�n���o�Ȃ��Ƃ��͏������Ȃ�
		return 0;
	}

	if (chkPara[1] == '1') {
		switch (chkPara[0]) {
		case '0':
			break;
		case '1':	// ���т̂�
			if (fNyuYou & 1) {
				strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
				ret = 1;
			}
			//ADD E.Osada 2006-07-21 ���їn���̏ꍇ
			if( (fNyuYou & 1) && (fNyuYou & 2) ) {
				strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
				ret = 1;
			}
			//
			break;
		case '2':	// �n���̂�
			if (fNyuYou & 2) {
				strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
				ret = 1;
			}
			//ADD E.Osada 2006-07-21 ���їn���̏ꍇ
			if( (fNyuYou & 1) && (fNyuYou & 2) ) {
				strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
				ret = 1;
			}
			//
			break;
		case '3':	// ���їD��
			if (fNyuYou & 1) {
				strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
				ret = 1;
			}
			else if (fNyuYou & 2) {
				strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
				ret = 1;
			}
			//ADD E.Osada 2006-07-21 ���їn���̏ꍇ
			if( (fNyuYou & 1) && (fNyuYou & 2) ) {
				strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
				strncpy( pKekka[lCnt].kkacmt2, YoketsuCM, 5);
				ret = 1;
			}
			//
			break;
		case '4':	// �n���D��
			if (fNyuYou & 2) {
				strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
				ret = 1;
			}
			else if (fNyuYou & 1) {
				strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
				ret = 1;
			}
			//ADD E.Osada 2006-07-21 ���їn���̏ꍇ
			if( (fNyuYou & 1) && (fNyuYou & 2) ) {
				strncpy( pKekka[lCnt].kkacmt2, NyubiCM, 5);
				strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
				ret = 1;
			}
			//
			break;
		}
	}
	ret = 0;		// ���їn���ł͍Č����s��Ȃ��̂ŁA0��ݒ� 2006.06.15
	if (ret != 0) {
		pKekka[lCnt].kesseiflg = '2';
	}
	else {
		pKekka[lCnt].kesseiflg = '1';
	}
	return ret;
}
#endif
/*** �C���Ŋ֐������ɍ쐬���A�����܂ŃR�����g�A�E�g����---�� ***/
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */

/******************************************************************************/
/*	�� �� ��  �FNyubiYoketu()												  */
/*	�@�\�T�v  �F���сE�n�����݃`�F�b�N										  */
/*	��	  ��  �F															  */
/*	 ��P���� �FpKekka	:	���ʏ��\���̔z��								  */
/*	 ��Q���� �FKekkaCnt:	���ʏ��\���̐�								  */
/*	�o	  ��  �F															  */
/*	���A���  �Fint															  */
/*					0:���сE�n������										  */
/*					1:���т���												  */
/*					2:�n������												  */
/*					3:���сE�n������										  */
/******************************************************************************/
void trim(char * dst, char *src) {
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
int	NyubiYoketu( Kekka * pKekka, int KekkaCnt)
{
	int			ret = 0;
//	double		rawData;
	char		tmp[22];
	int			lCnt;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	ret = 0;
	for (lCnt = 0; lCnt < KekkaCnt; lCnt++ ) {
		// ���ʒl�̒l������𐔒l������
		memset(tmp, 0, sizeof(tmp));
		strncpy(tmp, pKekka[lCnt].rawdata, 20);
//		rawData = atof(tmp);

		// ���у`�F�b�N
		if (strncmp( pKekka[lCnt].kmkcd , NyubiCD, 7) == 0 ) {
//			strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
			printf("���уf�[�^����\n");
			ret |= 0x10;
			memset( NyubiKekka, 0, sizeof(NyubiKekka));
			trim( NyubiKekka, pKekka[lCnt].rawdata );
			memset( NyubiSTS, 0, sizeof(NyubiSTS));
			strncpy( NyubiSTS, pKekka[lCnt].bskerrsts, 2);
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** �����ł��Č����s�����ߏ������폜 ***/
			/* pKekka[lCnt].knsflg = 'H';*/
			/* if ( rawData > atof(NyubiCHK) ) { */
			/* 	ret |= 0x01;*/
			/* }*/
			ret |= 0x01; // upd 20070623 waj
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
		}
		// �n���`�F�b�N
		else if (strncmp( pKekka[lCnt].kmkcd , YoketsuCD, 7) == 0 ) {
//			strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
			printf("�n���f�[�^����\n");
			ret |= 0x20;
			memset( YoketsuKekka, 0, sizeof(YoketsuKekka));
			trim( YoketsuKekka, pKekka[lCnt].rawdata );
			memset( YoketsuSTS, 0, sizeof(YoketsuSTS));
			strncpy( YoketsuSTS, pKekka[lCnt].bskerrsts, 2);
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** �����ł��Č����s�����ߏ������폜 ***/
			/* pKekka[lCnt].knsflg = 'H';*/
			/* if ( rawData > atof(YoketsuCHK) ) {*/
			/* 	ret |= 0x02;*/
			/* }*/
			ret |= 0x02; // upd 20070623 waj
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
		}
		// ������`�F�b�N
		else if (strncmp( pKekka[lCnt].kmkcd , OudanCD, 7) == 0 ) {
//			strncpy( pKekka[lCnt].kkacmt1, OudanCM, 5);
			printf("������f�[�^����\n");
			ret |= 0x40;
			memset( OudanKekka, 0, sizeof(OudanKekka));
			trim( OudanKekka, pKekka[lCnt].rawdata );
			memset( OudanSTS, 0, sizeof(OudanSTS));
			strncpy( OudanSTS, pKekka[lCnt].bskerrsts, 2);
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** �����ł��Č����s�����ߏ������폜 ***/
		/*	pKekka[lCnt].knsflg = 'H';*/
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
		}
	}
	return ret;
}
/******************************************************************************/
/*	�� �� ��  �FKeisanChk()													  */
/*	�@�\�T�v  �F�v�Z�`�F�b�N(WS��)											  */
/*	��	  ��  �F															  */
/*	 ��P���� �FchkPara	:	�`�F�b�N�p�p�����[�^							  */
/*	 ��Q���� �FpKekka	:	���ʏ��\���̔z��								  */
/*	 ��R���� �FKekkaCnt:	���ʏ��\���̐�								  */
/*	 ��R���� �FlCnt	:	�������ʒu										  */
/*	 ��R���� �FODFld	:	�I�[�_�[���									  */
/*	�o	  ��  �F															  */
/*	���A���  �Fint															  */
/*					0:�Č�����												  */
/*					1:�Č�����												  */
/******************************************************************************/
int	KeisanChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, char **ODFld, STKEISANCHK * calbuf)
{
	int			ret = 0;
	int			ret2;
	char		calBuff[256];
	struct stKEISANCHK {
		char	KMKCD[7+1];	   // ���ڃR�[�h
		char	KSNSK[128];	   // �v�Z��
	} sKEISANCHK;
	int			iCnt;	// ���[�v�J�E���^
	int			paraCnt;
	int			i;
	int			setCnt;
	int			tmpCnt;
	char		tmp[32];
	double		calNum;
//	double		rawData;
	char		*pBuffOD;
	char		**pFldOD;
	char		*pBuffRealchk ;
	char		**pFldRealchk;
	int			li_Keta ;
	char		lc_RawBuf[256] ;
	char		*lcp_RawBuf ;
	MY_FLG		 myFlg_RawNone ;

	/*----<< Begin add source Feb 27, 2008 H.Sato >>----*/
	char *pszExpandKSNSK = (char *) NULL;
										/* IF ���W�J��̌v�Z��              */
    double dTransferLimit = (double) 0.0;
	/*----<< End add source Feb 27, 2008 H.Sato >>----*/

	if (pKekka[lCnt].keisanflg == '1' || pKekka[lCnt].keisanflg == '2') {
		// ���Ƀ`�F�b�N�ς݂̎��͏������Ȃ�
		return 0;
	}

	pFldOD = malloc(sizeof(char *)*200);
	pBuffOD = malloc(sizeof(char) * READ_BUFF_SIZE);

	paraCnt = 0;
	while (paraCnt < strlen(chkPara)) {
		memset(&sKEISANCHK, 0, sizeof(sKEISANCHK));
		memcpy(sKEISANCHK.KMKCD, &chkPara[paraCnt], 7);
		paraCnt += 7;
		for (i = paraCnt + 1; i < strlen(chkPara) ; i++ ) if (chkPara[i] == '!') break;
		memcpy(sKEISANCHK.KSNSK, &chkPara[paraCnt+1], i-paraCnt-1);
		paraCnt += (i-paraCnt+1);
		ret2 = chkInfoRead(1, sKEISANCHK.KMKCD, ReadFileNameOD, pFldOD, pBuffOD);
		if ( ret2 != 0 ) {
			// �I�[�_�[�Ɍv�Z���ږ���
			continue;
		}

		//--------------------------------------------------------
		// ���ʒl�̒l������𐔒l������
		//	���ʒl���u�����N�̏ꍇ�A�v�Z�͍s�킸�A�v�Z���ڂɂ�
		//	�u�����N��ݒ肷��
		//--------------------------------------------------------
		memset(tmp, 0, sizeof(tmp));
		strncpy(tmp, pKekka[lCnt].rawdata, 20);
//		rawData = atof(tmp);

		myFlg_RawNone = MY_FLG_OFF ;

		// �����̍��ڃR�[�h�𐔒l�ɒu��������B
		memset(calBuff, 0, sizeof(calBuff));
		for (iCnt = 0, setCnt = 0; iCnt < 128; iCnt++ ) {
			// ���ڃR�[�h�̎n�܂�'['����������B
			if (sKEISANCHK.KSNSK[iCnt] == '[') {
				// ���ڒl������
				memset(tmp, 0, sizeof(tmp));
				tmpCnt = 0;
				iCnt++;
				// ���ڃR�[�h��]���i�I���ʒu��]��Null�܂Łj
				while (sKEISANCHK.KSNSK[iCnt] != ']' && sKEISANCHK.KSNSK[iCnt] != '\0') {
					tmp[tmpCnt++] = sKEISANCHK.KSNSK[iCnt++];
				}
				// ���ʏ�񂩂�w��̍��ڃR�[�h���������A�u��������B
				for (tmpCnt = 0; tmpCnt < KekkaCnt; tmpCnt++) {
					if (strncmp(pKekka[tmpCnt].kmkcd, tmp, strlen(tmp)) == 0) {
						strcpy ( lc_RawBuf, pKekka[tmpCnt].rawdata ) ;
						lcp_RawBuf = strtok ( lc_RawBuf, " " ) ;
						if ( lcp_RawBuf == NULL || pKekka[tmpCnt].rawdata[0] == '/' ) {
							//	�l���u�����N�ꍇ
							myFlg_RawNone = MY_FLG_ON ;
						}
						else {
							//	�l���ݒ肳��Ă���ꍇ
							strncat(calBuff, pKekka[tmpCnt].rawdata, 21);
							setCnt = strlen(calBuff);
						}
						break;
					}
				}
				if (tmpCnt == KekkaCnt) {
					// �֘A���ڂ�������Ȃ��B
					pKekka[lCnt].keisanflg = '0';
					break;
				}
			}
			else if (KSNSK_SC == (int) sKEISANCHK.KSNSK[iCnt]) {
				// �g��

				/*---<< Begin modified source May 27, 2008 H.Sato >>---*/
				// ���p�\�Ȓl�ȊO���w�肳��Ă����ꍇ�A�l 0 ���w�肳�ꂽ���̂Ƃ���

				//strncat(calBuff, ODFld[40], 5);
				//setCnt = strlen(calBuff);

				memcpy((void *) gszTransfer, ODFld[FLDIDX_SC], FLDSIZE_SC);
				gszTransfer[FLDSIZE_SC] = (char) '\0';
				if (0 == _isnumeric(gszTransfer)) {
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
				}
				strcat(calBuff, gszTransfer);
				setCnt = strlen(calBuff);

				/*---<< End modified source May 27, 2008 H.Sato >>---*/

			}
			else if (KSNSK_TJ == (int) sKEISANCHK.KSNSK[iCnt]) {
				// POW�Ƌ�ʂ��邽�߁A�O�̕�����O�Ŗ������`�F�b�N����B
                if (0 < iCnt &&
				    (sKEISANCHK.KSNSK[iCnt - 1] == 'o' ||
				     sKEISANCHK.KSNSK[iCnt - 1] == 'O')) {
                    break;
                }
                else {
					// �̏d

					/*---<< Begin modified source May 27, 2008 H.Sato >>---*/
					// ���p�\�Ȓl�ȊO���w�肳��Ă����ꍇ�A�l 0 ���w�肳�ꂽ���̂Ƃ���

					//if (ODFld[41][0] == '0') {
					//	// �̏d��Kg�̎��̓O�����Ōv�Z
					//	memset(tmp, 0, sizeof(tmp));
					//	strncpy(tmp, ODFld[41], 5);
					//	sprintf(tmp,"%-lf",(atof(tmp)*1000));
					//	strcat(calBuff, tmp);
					//}
					//else {
					//	strncat(calBuff, ODFld[41], 5);
					//}

					strncpy(gszTransfer, ODFld[FLDIDX_TJ], FLDSIZE_TJ);
					gszTransfer[FLDSIZE_TJ] = (char) '\0';
					if (0 == _isnumeric(gszTransfer)) {
						gszTransfer[0] = (char) '0';
						gszTransfer[1] = (char) '\0';
					}
					else {
						switch ((int) ODFld[FLDIDX_TJTNI][0]) {
						case _VALUE_TJTNI_KILLOGRAM:
							dTransferLimit = 
									atof(gszTransfer) * (double) 1000.0;
							if ((double) 0.0 < dTransferLimit) {
								sprintf(gszTransfer, "%f", dTransferLimit);
							}
							else {
								gszTransfer[0] = (char) '0';
								gszTransfer[1] = (char) '\0';
							}

						case _VALUE_TJTNI_GRAM:
							break;		/* NOP                              */

						default:
							gszTransfer[0] = (char) '0';
							gszTransfer[1] = (char) '\0';
						}
					}
					strcat(calBuff, gszTransfer);

					/*---<< End modified source May 27, 2008 H.Sato >>---*/

					setCnt = strlen(calBuff);
				}
			}
			else if (KSNSK_TNTME == (int) sKEISANCHK.KSNSK[iCnt]) {
				// �~�A����

				/*---<< Begin modified source May 27, 2008 H.Sato >>---*/
				// ���p�\�Ȓl�ȊO���w�肳��Ă����ꍇ�A�l 0 ���w�肳�ꂽ���̂Ƃ���

				//strncat(calBuff, ODFld[50], 4);
				//setCnt = strlen(calBuff);

				memcpy((void *) gszTransfer, ODFld[FLDIDX_TNTME], FLDSIZE_TNTME);
				gszTransfer[FLDSIZE_TNTME] = (char) '\0';
				if (0 == _isnumeric(gszTransfer)) {
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
				}
				else {
					switch ((int) ODFld[FLDIDX_TNTNI][0]) {
					/* 2014/02/06 sekiya ���ԒP�ʈȊO�̏ꍇ�͌v�Z���Ȃ��悤�Ɏd�l�ύX
					case _VALUE_TNTNI_MINUTE:
						sprintf(gszTransfer,
						        "%-lf",
						        (atof(gszTransfer) / (double) 60.0));
						gszTransfer[FLDSIZE_TNTME] = (char) '\0';
					*/
					case _VALUE_TNTNI_HOUR:
						break;			/* NOP                             */

					default:
						gszTransfer[0] = (char) '0';
						gszTransfer[1] = (char) '\0';
					}
				}
				strcat(calBuff, gszTransfer);
				setCnt = strlen(calBuff);

				/*---<< End modified source May 27, 2008 H.Sato >>---*/

			}
			else if (KSNSK_TNRYO == (int) sKEISANCHK.KSNSK[iCnt]) {
				// �~�A��

				/*---<< Begin modified source May 27, 2008 H.Sato >>---*/
				// ���p�\�Ȓl�ȊO���w�肳��Ă����ꍇ�A�l 0 ���w�肳�ꂽ���̂Ƃ���

				//strncat(calBuff, ODFld[52], 5);
				//setCnt = strlen(calBuff);

				memcpy((void *) gszTransfer, ODFld[FLDIDX_TNRYO], FLDSIZE_TNRYO);
				gszTransfer[FLDSIZE_TNRYO] = (char) '\0';
				if (0 == _isnumeric(gszTransfer)) {
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
				}
				else {
					switch ((int) ODFld[FLDIDX_TNRYOTNI][0]) {
					/* 2014/02/06 sekiya �~�����b�g���P�ʈȊO�̏ꍇ�͌v�Z���Ȃ��悤�Ɏd�l�ύX
					case _VALUE_TNRYO_LITER:
						dTransferLimit = atof(gszTransfer) * (double) 1000.0;
						if ((double) 0.0 < dTransferLimit) {
							sprintf(gszTransfer, "%-lf", dTransferLimit);
						}
						else {
							gszTransfer[0] = (char) '0';
							gszTransfer[1] = (char) '\0';
						}
					*/
					case _VALUE_TNRYO_MILLILITER:
						break;

					default:
						gszTransfer[0] = (char) '0';
						gszTransfer[1] = (char) '\0';
					}
				}
				strcat(calBuff, gszTransfer);
				setCnt = strlen(calBuff);

				/*---<< End modified source May 27, 2008 H.Sato >>---*/

			}

			/*----<< Begin add source Feb 27, 2008 H.Sato >>----*/
			/* �v�Z���g���Ή�                                               */

			else if (KSNSK_SBTKBN == (int) sKEISANCHK.KSNSK[iCnt]) {
				/* ���ʋ敪                                                 */
				if (_VALUE_SBTKBN_MALE == (int) ODFld[FLDIDX_SBTKBN][0] ||
						_VALUE_SBTKBN_FEMALE == (int) ODFld[FLDIDX_SBTKBN][0]) {
					calBuff[setCnt++] = ODFld[FLDIDX_SBTKBN][0];
					calBuff[setCnt] = (char) '\0';
				}
				else {
					calBuff[setCnt++] = (char) _VALUE_SBTKBN_UNKNOWN;
					calBuff[setCnt] = (char) '\0';
										/* �W�J�s��							*/
				}
			}
			else if (KSNSK_AGE == (int) sKEISANCHK.KSNSK[iCnt]) {
				/* �N��                                                     */
				if (_VALUE_AGEKBN_YEAR != (int) ODFld[FLDIDX_AGEKBN][0]) {
					calBuff[setCnt++] = (char) '0';
					calBuff[setCnt] = (char) '\0';
										/* �W�J�s��							*/
				}
				else {
					memcpy((void *) gszTransfer, ODFld[FLDIDX_AGE], FLDSIZE_AGE);
					gszTransfer[FLDSIZE_AGE] = (char) '\0';
					if (0 == _isnumeric(gszTransfer)) {
						gszTransfer[0] = (char) '0';
						gszTransfer[1] = (char) '\0';
					}
					strcat(calBuff, gszTransfer);
					setCnt = strlen(calBuff);
				}
			}

			/*----<< End add source Feb 27, 2008 H.Sato >>----*/

			else if (sKEISANCHK.KSNSK[iCnt] == '\0') {
				break;
			}
			else {
				calBuff[setCnt++] = sKEISANCHK.KSNSK[iCnt];
			}
		}

		//--------------------------------------------------------
		// �v�Z���ڂ�z��ɑޔ�����
		//	�v�Z���̍��ڂ̂����ꂩ���u�����N�̏ꍇ��
		//	���ʒl�t���O��ݒ肵�A��ʂŌ��ʒl�Ƀu�����N��ݒ肷��
		//--------------------------------------------------------
		if (iCnt == 128 || iCnt == strlen ( sKEISANCHK.KSNSK ) ) {
			//	�����擾
			pFldRealchk = malloc(sizeof(char *)*200);
			pBuffRealchk = malloc(sizeof(char) * READ_BUFF_SIZE);
			ret2 = chkInfoRead(0, sKEISANCHK.KMKCD, ReadFileName, pFldRealchk, pBuffRealchk);
			if ( ret2 != 0 ) {
				// �I�[�_�[�Ɍv�Z���ږ���
				free ( pFldRealchk ) ;
				free ( pBuffRealchk ) ;
				continue;
			}
			li_Keta = atoi(pFldRealchk[57]) ;
			free ( pFldRealchk ) ;
			free ( pBuffRealchk ) ;

			//	���ڃR�[�h�ݒ�
			memcpy(calbuf[ret].motoKMKCD, pKekka[lCnt].kmkcd,8);
			memcpy(calbuf[ret].KMKCD, sKEISANCHK.KMKCD,8);

			/*----<< Begin add source Feb 27, 2008 H.Sato >>----*/
			/* �v�Z���Ɋ܂܂�� IF ���̓W�J                                     */
			if (NULL != (void *) (pszExpandKSNSK = OperateKSNSK(calBuff))) {
				if ('\0' != (int) *pszExpandKSNSK) {
					strcpy(calBuff, pszExpandKSNSK);
				}
				free((void *) pszExpandKSNSK);
				pszExpandKSNSK = (char *) NULL;
			}

			/*----<< End add source Feb 27, 2008 H.Sato >>----*/

			// ������̌v�Z�����v�Z����B
			calNum = StringCal(calBuff);
			if (li_Keta != 9) {
				//ADD E.Osada 2006-08-06 �ۂߏ����ύX
				//calNum += + 0.00001;
				//sprintf(tmp, "%.*f", li_Keta, calNum);
				sprintf(tmp, "%f", calNum);
				calNum = atof(tmp);
			}
			calbuf[ret].raw = calNum;
			calbuf[ret].flgRawNone = myFlg_RawNone ;
			ret ++;
		}
	}
	pKekka[lCnt].keisanflg = '1';

	free(pFldOD);
	free(pBuffOD);

	return ret;
}
/******************************************************************************/
/*	�� �� ��  �FKisyakuChk()												  */
/*	�@�\�T�v  �F��ߍČ��`�F�b�N											  */
/*	��	  ��  �F															  */
/*	 ��P���� �FchkPara	:	�`�F�b�N�p�p�����[�^							  */
/*	 ��Q���� �FpKekka	:	���ʏ��\���̔z��								  */
/*	 ��R���� �FKekkaCnt:	���ʏ��\���̐�								  */
/*	 ��R���� �FlCnt	:	�������ʒu										  */
/*	 ��R���� �FODFld	:	�I�[�_�[���									  */
/*	�o	  ��  �F															  */
/*	���A���  �Fint															  */
/*					0:�Č�����												  */
/*					1:�Č�����												  */
/*					2:�Č��Ȃ��E��߃G���[									  */
/******************************************************************************/
int	KisyakuChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, char *cKisyak, int keta)
{
	int			ret = 0;
	char		tmp[32];
	double		rawData;
//	double		DataMax;
//	double		DataMin;
	int			lpCnt;
	int			flg;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
//	if (pKekka[lCnt].kisyakflg == '1' || pKekka[lCnt].kisyakflg == '2') {
		// ���Ƀ`�F�b�N�ς݂̎��͏������Ȃ�
//		return 0;
//	}

//	pKSKBRMST = (struct stKSKBRMST *)chkPara;

	// �������ʋy�сA�����A����l�𕶎��񂩂琔�l�ɕϊ�
	memset(tmp, 0, sizeof(tmp));
//	strncpy(tmp, pKekka[lCnt].rawdata, 20);
	strncpy(tmp, pKekka[lCnt].hjkka, 20);
	rawData = atof(tmp);

//	���͋@����A���Ă����l�ɑ΂��A�|�����v�Z���s��Ȃ�
//DEL	if (strcmp(&(pKekka[lCnt].jisksbr[1]), "0D") != 0) {
//DEL		if (pKekka[lCnt].jisksbr[0] != ' ') {
//DEL			rawData *= atof(&(pKekka[lCnt].jisksbr[1]));
//DEL		}
//DEL	}

//	memset(tmp, 0, sizeof(tmp));
//	strncpy(tmp, pKSKBRMST->KMAX, 20);
//	DataMax = atof(tmp);

//	memset(tmp, 0, sizeof(tmp));
//	strncpy(tmp, pKSKBRMST->KMIN, 20);
//	DataMin = atof(tmp);

	flg = -1;
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** �{�݃R�[�h���Y���Ȃ��̎���0000000������ ***/
	int i;
	for (i = 0; i < 2 && flg < 0; i++) {
		char wrkSST[8];
		memset(wrkSST, 0, sizeof(wrkSST));
		memcpy(wrkSST, (i==0?pKekka[lCnt].sstcd:"0000000"), 7);

	for (lpCnt = 0; lpCnt < gKSKBRMSTnum; lpCnt ++ ){
			if ((strncmp(gpKSKBRMST[lpCnt].BSKKBN, pKekka[lCnt].bskkbn,  4) == 0) &&
				(strncmp(gpKSKBRMST[lpCnt].KNSGRP, pKekka[lCnt].knsgrp, 16) == 0) &&
				(strncmp(gpKSKBRMST[lpCnt].KMKCD,  pKekka[lCnt].kmkcd,   7) == 0) &&
/*** ��߃����W�{�ݕʑΉ� �{�݃R�[�h�������ɒǉ� ***/
				(strncmp(gpKSKBRMST[lpCnt].SSTCD,  wrkSST,               7) == 0)) {
#ifdef _DEBUG_
printf("��߃����W�{�ݕʑΉ�\n");
				char wwww[20];
				memset(wwww,0,20); memcpy(wwww,gpKSKBRMST[lpCnt].BSKKBN,4); printf("BSKKBN  %s\n", wwww);
				memset(wwww,0,20); memcpy(wwww,gpKSKBRMST[lpCnt].KNSGRP,16);printf("KNSGRP  %s\n", wwww);
				memset(wwww,0,20); memcpy(wwww,gpKSKBRMST[lpCnt].KMKCD,7);  printf("KMKCD   %s\n", wwww);
				memset(wwww,0,20); memcpy(wwww,pKekka[lCnt].sstcd,7);       printf("SSTCD.1 %s\n", wwww);
				memset(wwww,0,20); memcpy(wwww,gpKSKBRMST[lpCnt].SSTCD,7);  printf("SSTCD.2 %s\n", wwww);
#endif
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
				//UPD 2006-09-09 Nagata
				// ��r����������l�ȉ��A�����l�ȏ�Ƃ���
				// if ((gpKSKBRMST[lpCnt].KMIN <= rawData) && (rawData < gpKSKBRMST[lpCnt].KMAX)) {
				if ((gpKSKBRMST[lpCnt].KMIN <= rawData) && (rawData <= gpKSKBRMST[lpCnt].KMAX)) {
					flg = 0; /* ����ŊY���f�[�^�����\�� */
					ret = 1;
					break;
				}
			}
#if 0		// DEL E.Osada 2006-07-21
		if ((strncmp(gpKSKBRMST[lpCnt].BSKKBN, "YOUS", 4) == 0) &&
			(strncmp(gpKSKBRMST[lpCnt].KNSGRP, pKekka[lCnt].knsgrp, 16) == 0) &&
			(strncmp(gpKSKBRMST[lpCnt].KMKCD, pKekka[lCnt].kmkcd, 7) == 0)) {
			if ((gpKSKBRMST[lpCnt].KMIN <= rawData) && (rawData < gpKSKBRMST[lpCnt].KMAX)) {
				flg = lpCnt;
			}
		}
#endif
		}
	}

//DEL	if ((lpCnt == gKSKBRMSTnum) && (flg > -1)) {
//DEL		ret = 2;
//DEL		lpCnt = flg;
//DEL	}

	// �����l�A����l�̊m�F
//	if (rawData < DataMin) {
//		ret = 1;
//	}
//	else if (rawData > DataMax) {
//		ret = 1;
//	}

	// �o�͏��̐ݒ�
	if (ret != 0) {
		memset(cKisyak, 0, 15+1);
		// CHG E.Osada 2006-07-21 �p���߂̏ꍇ�́@'R' �ł��`��
#if 0
		// �Č��p�ɕԂ���ߔ{���ɂ́A�擪��1�����͓���Ȃ�
		trim(tmp, gpKSKBRMST[lpCnt].KSBR);
		strncpy(cKisyak, &tmp[1], 15);
		pKekka[lCnt].kisyakflg = '2';
#endif
		if( gpKSKBRMST[lpCnt].KSBR[0] == 'Y' ) {
			pKekka[lCnt].kisyakflg = '2';
			ret = 2;
		} else {
			// �Č��p�ɕԂ���ߔ{���ɂ́A�擪��1�����͓���Ȃ�
			trim(tmp, gpKSKBRMST[lpCnt].KSBR);
			strncpy(cKisyak, &tmp[1], 15);
			pKekka[lCnt].kisyakflg = '2';
		}
		//
	}
	else {
		memset(cKisyak, 0, 15+1);
		pKekka[lCnt].kisyakflg = '1';
	}

	return ret;
}

/******************************************************************************/
/*	�� �� ��  �FStringCal_sub()												  */
/*	�@�\�T�v  �F�w�肳�ꂽ���Z�q�ƒl�Ŏl�����Z�s��							  */
/*	��	  ��  �F															  */
/*	 ��P���� �Fenzan	:	���Z�q											  */
/*	 ��Q���� �Fval1	:	�l�P											  */
/*	 ��R���� �Fval2	:	�l�Q											  */
/*	�o	  ��  �F															  */
/*	���A���  �Fdouble	�v�Z����											  */
/******************************************************************************/
double StringCal_sub(char enzan,double val1,double val2)
{
	switch ( enzan ) {
	case '+':
		return (val1 + val2);
		break;
	case '-':
		return (val1 - val2);
		break;
	case '/':
		if (val2 == 0.0) {
			return 0;
		}
		return (val1 / val2);
		break;
	case '*':
		return (val1 * val2);
		break;
	}
	return 0;
}

/******************************************************************************/
/*	�� �� ��  �FStringCal()													  */
/*	�@�\�T�v  �F�n���ꂽ������̌v�Z�����s��								  */
/*	��	  ��  �F															  */
/*	 ��P���� �FCalStr	:	�v�Z������										  */
/*	�o	  ��  �F															  */
/*	���A���  �Fdouble	�v�Z����											  */
/*																			  */
/*	���ӁF	�Ή����鉉�Z�q�́u+ - / *�v���\�ł���B							  */
/*			����ȊO��LOG�ALOG10�APOW��3�̌v�Z���s���B					  */
/*			�v�Z�̗D�揇�ʂ́A�l�����Z�̗D�揇�ʂɏ]��*��/���D�悳���B	  */
/******************************************************************************/
double StringCal(char *CalStr)
{
	char		StacEn;
	double		StacNum;
	int			flg;
	int			loopCnt, strCnt;
	double		ret;
	char		cStacNum[32];
	char		cStacNum2[32];
	char		cChk[16];
	int			i, c;
	double		StacRet[10];
	char		StacEnc[10];
	char		StacFlg[10];
	int			StacCnt;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	ret = 0.0;
	StacEn = '+';
	flg = FALSE;
	strCnt = 0;
	StacCnt = 0;
	for(loopCnt = 0; loopCnt < strlen(CalStr); loopCnt ++) {
		switch (CalStr[loopCnt]) {
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.':
			// ���l�̎�
			break;

		case '+': case '-': case '/': case '*':
			// ���Z�q�̎�
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

//			if ((loopCnt == strCnt) && ((CalStr[loopCnt] == '+') || (CalStr[loopCnt] == '-'))) {
//				break;
//			}
//			else
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

//			ret = StringCal_sub(StacEn, ret, StacNum);
//			flg = FALSE;
//			StacEn = CalStr[loopCnt];
			strCnt = loopCnt + 1;
			break;

		case 'L': case 'l':
			// LOG�y��LOG10�̎�
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
			// POW�̎�
			for (c = 0, i = loopCnt; CalStr[i] != '(' && CalStr[i] != '\0'; c++, i++) {
				cChk[c] = toupper(CalStr[i]);
			}
			cChk[c] = '\0';
			if (strcmp(cChk, "POW") == 0) {
				for (c = 0, i = loopCnt + 4; CalStr[i] != ':' && CalStr[i] != ')' && CalStr[i] != '\0'; c++, i++) {
					cStacNum[c] = CalStr[i];
				}
				cStacNum[c] = '\0';
				for (c = 0, i += 1; CalStr[i] != ':' && CalStr[i] != ')' && CalStr[i] != '\0'; c++, i++) {
					cStacNum2[c] = CalStr[i];
				}
				cStacNum2[c] = '\0';
				StacNum = pow(atof(cStacNum), atof(cStacNum2));
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

/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** �����`�F�b�N�E�Č��Ή� ***/
/******************************************************************************/
/*	�� �� ��  �FNyubiYoketuChk()											  */
/*	�@�\�T�v  �F���сE�n���`�F�b�N											  */
/*	��	  ��  �F															  */
/*	 ��P���� �FchkPara	:	�`�F�b�N�p�p�����[�^							  */
/*	 ��Q���� �FpKekka	:	���ʏ��\���̔z��								  */
/*	 ��R���� �FKekkaCnt:	���ʏ��\���̐�								  */
/*	 ��S���� �FlCnt	:	�������ʒu										  */
/*	 ��T���� �FfNyuYou	:	���сE�n���t���O								  */
/*	�o	  ��  �F															  */
/*	���A���  �Fint															  */
/*					0:�Č�����												  */
/*					1:�Č�����												  */
/******************************************************************************/
int	NyubiYoketuChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, int fNyuYou)
{
	int			ret = 0;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
#ifdef _DEBUG_
		printf("NyubiYoketuChk(%d)\n", __LINE__);
#endif
	if (pKekka[lCnt].kesseiflg == '1' || pKekka[lCnt].kesseiflg == '2') {
		// ���Ƀ`�F�b�N�ς݂̎��͏������Ȃ�
#ifdef _DEBUG_
		printf("NyubiYoketuChk(%d) : ���Ƀ`�F�b�N�ς݂̎��͏������Ȃ�\n", __LINE__);
#endif
		return 0;
	}

	if (fNyuYou == 0) {
		// ���сE�n���łȂ��Ƃ��͏������Ȃ�
#ifdef _DEBUG_
		printf("NyubiYoketuChk(%d) : ���сE�n���łȂ��Ƃ��͏������Ȃ�\n", __LINE__);
#endif
		return 0;
	}

    // add 20070623 waj ��E�����l���擾
    int i;
    double hLimit = 0;
    double lLimit = 0;
    char   sw = 0;
    for (i = 0; i < iRngchkmstNum; i++) {
        if ((memcmp(pKekka[lCnt].knsgrp, pRngchkmst[i].knsgrp, 16) == 0) &&
            (memcmp(pKekka[lCnt].kmkcd,  pRngchkmst[i].kmkcd,   7) == 0) &&
            ((memcmp(pKekka[lCnt].zrcd,  pRngchkmst[i].zaicd,   4) == 0) ||
             (memcmp("000 ",             pRngchkmst[i].zaicd,   4) == 0)) &&
            ((memcmp(pKekka[lCnt].sstcd, pRngchkmst[i].sstcd,   7) == 0) ||
             (memcmp("0000000",          pRngchkmst[i].sstcd,   7) == 0))) {
            hLimit = atof(pRngchkmst[i].hrng);
            lLimit = atof(pRngchkmst[i].lrng);
            sw = 1;
#ifdef _DEBUG_
			printf("���� H:%f, L:%f\n", hLimit, lLimit);
#endif
            break;
        }
    }
	// add 20070623 waj ���сE�n���E���t�̑���l
	double datNyubi  = 0;
	double datYoketu = 0;
//	double datOdan   = 0;
	for (i = 0; i < KekkaCnt; i++) {
		if (memcmp(pKekka[i].kmkcd, NyubiCD,   7) == 0)
			datNyubi  = atof(pKekka[i].rawdata);
		if (memcmp(pKekka[i].kmkcd, YoketsuCD, 7) == 0)
			datYoketu = atof(pKekka[i].rawdata);
//		if (memcmp(pKekka[i].kmkcd, OudanCD,   7) == 0)
//			datOdan   = atof(pKekka[i].rawdata);
	}
#ifdef _DEBUG_
	printf("���� ����:%f, �n��:%f, ���t:%f\n", datNyubi, datYoketu, datOdan);
	printf("fNyuYou=%d, chkPara=%c%c\n", fNyuYou, chkPara[0], chkPara[1]);
#endif

	if (chkPara[1] == '1') {
		switch (chkPara[0]) {
		case '0':
			break;
		case '1':	// ���т̂�
			// upd 20070623 waj
            // if (fNyuYou & 1) {
            if ((fNyuYou & 1) && ((sw == 1) && ((datNyubi < lLimit) || (hLimit < datNyubi)))) {
                if( (pKekka[lCnt].kkacmt1[0] == ' ') || (pKekka[lCnt].kkacmt1[0] == '\0') ) {
                    // ���ʃR�����g�P�ɉ����Z�b�g����Ă��Ȃ�������0105������
                    strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
                }
                else if( memcmp(pKekka[lCnt].kkacmt1, NyubiCM, 4 ) == 0
                        || memcmp(pKekka[lCnt].kkacmt2, NyubiCM, 4) == 0 ) {
                    // �����A���ʃR�����g�ɓ��уR�����g�������Ă�����Ȃɂ����Ȃ�
                }
                else {
                    // ���ʃR�����g�P�ɃR�����g���Z�b�g����Ă�����A�P�̓��e���Q�Ɉڂ��A
                    // �P��0105������
                    memset(pKekka[lCnt].kkacmt2, 0, sizeof(pKekka[lCnt].kkacmt2));
                    strncpy( pKekka[lCnt].kkacmt2, pKekka[lCnt].kkacmt1, 5);
                    memset(pKekka[lCnt].kkacmt1, 0, sizeof(pKekka[lCnt].kkacmt1));
                    strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
                }
                //
                ret = 1;
            }
			//
			break;
		case '2':	// �n���̂�
			// upd 20070623 waj
            // if (fNyuYou & 2) {
            if ((fNyuYou & 2) && ((sw == 1) && ((datYoketu < lLimit) || (hLimit < datYoketu)))) {
                if( (pKekka[lCnt].kkacmt1[0] == ' ') || (pKekka[lCnt].kkacmt1[0] == '\0') ) {
                    strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
                }
                else if( memcmp(pKekka[lCnt].kkacmt1, YoketsuCM, 4 ) == 0
                        || memcmp(pKekka[lCnt].kkacmt2, YoketsuCM, 4) == 0 ) {
                    // �����A���ʃR�����g�ɗn���R�����g�������Ă�����Ȃɂ����Ȃ�
                }
                else {
                    memset(pKekka[lCnt].kkacmt2, 0, sizeof(pKekka[lCnt].kkacmt2));
                    strncpy( pKekka[lCnt].kkacmt2, pKekka[lCnt].kkacmt1, 5);
                    memset(pKekka[lCnt].kkacmt1, 0, sizeof(pKekka[lCnt].kkacmt1));
                    strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
                }
                ret = 1;
            }
			//
			break;
		case '3':	// ���їD��
			// upd 20070623 waj
            // if (fNyuYou & 2) {      //�n��
            if ((fNyuYou & 2) && ((sw == 1) && ((datYoketu < lLimit) || (hLimit < datYoketu)))) { //�n��
                if( (pKekka[lCnt].kkacmt1[0] == ' ') || (pKekka[lCnt].kkacmt1[0] == '\0') ) {
                    strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
                }
                else if( memcmp(pKekka[lCnt].kkacmt1, YoketsuCM, 4 ) == 0
                        || memcmp(pKekka[lCnt].kkacmt2, YoketsuCM, 4) == 0 ) {
                    // �����A���ʃR�����g�ɗn���R�����g�������Ă�����Ȃɂ����Ȃ�
                }
                else {
                    memset(pKekka[lCnt].kkacmt2, 0, sizeof(pKekka[lCnt].kkacmt2));
                    strncpy( pKekka[lCnt].kkacmt2, pKekka[lCnt].kkacmt1, 5);
                    memset(pKekka[lCnt].kkacmt1, 0, sizeof(pKekka[lCnt].kkacmt1));
                    strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
                }
                ret = 1;
            }
			// upd 20070623 waj
            // if (fNyuYou & 1) {      //����
            if ((fNyuYou & 1) && ((sw == 1) && ((datNyubi < lLimit) || (hLimit < datNyubi)))) { //����
                if( (pKekka[lCnt].kkacmt1[0] == ' ') || (pKekka[lCnt].kkacmt1[0] == '\0') ) {
                    strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
                }
                else if( memcmp(pKekka[lCnt].kkacmt1, NyubiCM, 4 ) == 0
                        || memcmp(pKekka[lCnt].kkacmt2, NyubiCM, 4) == 0 ) {
                    // �����A���ʃR�����g�ɓ��уR�����g�������Ă�����Ȃɂ����Ȃ�
                }
                else {
                    memset(pKekka[lCnt].kkacmt2, 0, sizeof(pKekka[lCnt].kkacmt2));
                    strncpy( pKekka[lCnt].kkacmt2, pKekka[lCnt].kkacmt1, 5);
                    memset(pKekka[lCnt].kkacmt1, 0, sizeof(pKekka[lCnt].kkacmt1));
                    strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
                }
                ret = 1;
            }
			//
			break;
		case '4':	// �n���D��
			// upd 20070623 waj
            // if (fNyuYou & 1) {      //����
            if ((fNyuYou & 1) && ((sw == 1) && ((datNyubi < lLimit) || (hLimit < datNyubi)))) { //����
                if( (pKekka[lCnt].kkacmt1[0] == ' ') || (pKekka[lCnt].kkacmt1[0] == '\0') ) {
                    strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
                }
                else if( memcmp(pKekka[lCnt].kkacmt1, NyubiCM, 4 ) == 0
                        || memcmp(pKekka[lCnt].kkacmt2, NyubiCM, 4) == 0 ) {
                    // �����A���ʃR�����g�ɓ��уR�����g�������Ă�����Ȃɂ����Ȃ�
                }
                else {
                    memset(pKekka[lCnt].kkacmt2, 0, sizeof(pKekka[lCnt].kkacmt2));
                    strncpy( pKekka[lCnt].kkacmt2, pKekka[lCnt].kkacmt1, 5);
                    memset(pKekka[lCnt].kkacmt1, 0, sizeof(pKekka[lCnt].kkacmt1));
                    strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
                }
                ret = 1;
            }
			// upd 20070623 waj
            // if (fNyuYou & 2) {      //�n��
            if ((fNyuYou & 2) && ((sw == 1) && ((datYoketu < lLimit) || (hLimit < datYoketu)))) { //�n��
                if( (pKekka[lCnt].kkacmt1[0] == ' ') || (pKekka[lCnt].kkacmt1[0] == '\0') ) {
                    strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
                }
                else if( memcmp(pKekka[lCnt].kkacmt1, YoketsuCM, 4 ) == 0
                        || memcmp(pKekka[lCnt].kkacmt2, YoketsuCM, 4) == 0 ) {
                    // �����A���ʃR�����g�ɗn���R�����g�������Ă�����Ȃɂ����Ȃ�
                }
                else {
                    memset(pKekka[lCnt].kkacmt2, 0, sizeof(pKekka[lCnt].kkacmt2));
                    strncpy( pKekka[lCnt].kkacmt2, pKekka[lCnt].kkacmt1, 5);
                    memset(pKekka[lCnt].kkacmt1, 0, sizeof(pKekka[lCnt].kkacmt1));
                    strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
                }
                ret = 1;
            }
			//
			break;
		}
	}
#ifdef _DEBUG_
	printf("���ʃR�����g�P %s\n", pKekka[lCnt].kkacmt1);
	printf("NyubiYoketuChk(%d) : ret = %d\n", __LINE__, ret);
#endif
	// del 2007.05.16 waj ����ς荀�ږ��ɍČ����邱�ƂɂȂ����̂ŁA�������R�����g�A�E�g
	// ret = 0;		// ���їn���ł͍Č����s��Ȃ��̂ŁA0��ݒ� 2006.06.15
	if (ret != 0) {
		pKekka[lCnt].kesseiflg = '2';
	}
	else {
		pKekka[lCnt].kesseiflg = '1';
	}
	return ret;
}

/******************************************************************************/
/*  �� �� ���@�FGetModule()				 									  */
/*  �@�\�T�v�@�F���͋@���@�����W���[��No�ϊ�								  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *   �ϊ���												  */
/*�@ ��Q���� �Fchar *   �ϊ���												  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fstatic void													  */
/******************************************************************************/
void GetModule ( char *pFrom, int *pTo )
{
#ifdef _DEBUG_
    printf("GetModule(%d)\n", __LINE__);
#endif

	*pTo = atoi(&pFrom[3]) ;

	return ;
}

/******************************************************************************/
/*  �� �� ���@�FGetXmSkFlg()												  */
/*  �@�\�T�v�@�FX-M�W�v�t���O�擾											  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *   �����O���[�v										  */
/*�@ ��Q���� �Fchar *   ���ڃR�[�h											  */
/*�@ ��R���� �Fchar *   �����J�n��(YYYY-MM-DD�`��)							  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fstatic void													  */
/******************************************************************************/
char GetXmSkFlg(char *pKnsgrp, char *pKmkcd, char *pKnskisymd)
{
	int		iKmkCnt;
	char	cXmSkFlg;
	char	cWrkKnskisymd[9];

#ifdef _DEBUG_
	printf( "GetXmSkFlg(%d) : pKnsgrp                        = %s\n", __LINE__, pKnsgrp );
	printf( "GetXmSkFlg(%d) : pKmkcd                         = %s\n", __LINE__, pKmkcd );
	printf( "GetXmSkFlg(%d) : pKnskisymd                     = %s\n\n", __LINE__, pKnskisymd );
#endif

	memset( cWrkKnskisymd, 0, sizeof(cWrkKnskisymd) );
	cWrkKnskisymd[0] = pKnskisymd[0];
	cWrkKnskisymd[1] = pKnskisymd[1];
	cWrkKnskisymd[2] = pKnskisymd[2];
	cWrkKnskisymd[3] = pKnskisymd[3];
	cWrkKnskisymd[4] = pKnskisymd[5];
	cWrkKnskisymd[5] = pKnskisymd[6];
	cWrkKnskisymd[6] = pKnskisymd[8];
	cWrkKnskisymd[7] = pKnskisymd[9];

	/* ������ */
	cXmSkFlg = '1';

	for( iKmkCnt = 0; iKmkCnt < iKmkmstNum; iKmkCnt++ ) {
		/* �I�[�_�[�̍��ڃR�[�h�ƍ��ڃ}�X�^�̍��ڃR�[�h����v�����ꍇ */
		if( (memcmp(pKmkmst[iKmkCnt].knsgrp, pKnsgrp, 7) == 0) &&
			(memcmp(pKmkmst[iKmkCnt].kmkcd, pKmkcd, 7) == 0) &&
			(memcmp(pKmkmst[iKmkCnt].kaiymd, cWrkKnskisymd, 8) <= 0) &&
			(memcmp(pKmkmst[iKmkCnt].haiymd, cWrkKnskisymd, 8) >= 0) ) {
			/* X-M�W�v�t���O���擾(0:�W�v����A1:�W�v���Ȃ�) */
			cXmSkFlg = pKmkmst[iKmkCnt].xmskflg;
#ifdef _DEBUG_
			printf( "GetXmSkFlg(%d) : pKmkmst[iKmkCnt].knsgrp        = %s\n", __LINE__, pKmkmst[iKmkCnt].knsgrp );
			printf( "GetXmSkFlg(%d) : pKmkmst[iKmkCnt].kmkcd         = %s\n", __LINE__, pKmkmst[iKmkCnt].kmkcd );
			printf( "GetXmSkFlg(%d) : pKmkmst[iKmkCnt].kaiymd        = %s\n", __LINE__, pKmkmst[iKmkCnt].kaiymd );
			printf( "GetXmSkFlg(%d) : pKmkmst[iKmkCnt].haiymd        = %s\n", __LINE__, pKmkmst[iKmkCnt].haiymd );
			printf( "GetXmSkFlg(%d) : pKnsgrp                        = %s\n", __LINE__, pKnsgrp );
			printf( "GetXmSkFlg(%d) : pKmkcd                         = %s\n", __LINE__, pKmkcd );
			printf( "GetXmSkFlg(%d) : cWrkKnskisymd                  = %s\n", __LINE__, cWrkKnskisymd );
			printf( "GetXmSkFlg(%d) : pKmkmst[iKmkCnt].xmskflg       = %c\n", __LINE__, pKmkmst[iKmkCnt].xmskflg );
			printf( "GetXmSkFlg(%d) : cXmSkFlg                       = %c\n\n", __LINE__, cXmSkFlg );
#endif
			break;
		}
	}

	return cXmSkFlg;

}

/******************************************************************************/
/*  �� �� ���@�FGetXmChkFlg()												  */
/*  �@�\�T�v�@�FX-M�`�F�b�N�t���O�擾										  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *   �����O���[�v										  */
/*�@ ��Q���� �Fchar *   ���ڃR�[�h											  */
/*�@ ��R���� �Fchar *   �����J�n��(YYYY-MM-DD�`��)							  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fstatic void													  */
/******************************************************************************/
char GetXmChkFlg(char *pKnsgrp, char *pKmkcd, char *pKnskisymd)
{
	int		iKmkCnt;
	char	cXmChkFlg;
	char	cWrkKnskisymd[9];

#ifdef _DEBUG_
	printf( "GetXmChkFlg(%d) : pKnsgrp                        = %s\n", __LINE__, pKnsgrp );
	printf( "GetXmChkFlg(%d) : pKmkcd                         = %s\n", __LINE__, pKmkcd );
	printf( "GetXmChkFlg(%d) : pKnskisymd                     = %s\n\n", __LINE__, pKnskisymd );
#endif

	memset( cWrkKnskisymd, 0, sizeof(cWrkKnskisymd) );
	cWrkKnskisymd[0] = pKnskisymd[0];
	cWrkKnskisymd[1] = pKnskisymd[1];
	cWrkKnskisymd[2] = pKnskisymd[2];
	cWrkKnskisymd[3] = pKnskisymd[3];
	cWrkKnskisymd[4] = pKnskisymd[5];
	cWrkKnskisymd[5] = pKnskisymd[6];
	cWrkKnskisymd[6] = pKnskisymd[8];
	cWrkKnskisymd[7] = pKnskisymd[9];

	/* ������ */
	cXmChkFlg = '1';

	for( iKmkCnt = 0; iKmkCnt < iKmkmstNum; iKmkCnt++ ) {
		/* �I�[�_�[�̍��ڃR�[�h�ƍ��ڃ}�X�^�̍��ڃR�[�h����v�����ꍇ */
		if( (memcmp(pKmkmst[iKmkCnt].knsgrp, pKnsgrp, 7) == 0) &&
			(memcmp(pKmkmst[iKmkCnt].kmkcd, pKmkcd, 7) == 0) &&
			(memcmp(pKmkmst[iKmkCnt].kaiymd, cWrkKnskisymd, 8) <= 0) &&
			(memcmp(pKmkmst[iKmkCnt].haiymd, cWrkKnskisymd, 8) >= 0) ) {

			/* X-M�`�F�b�N�t���O���擾(0:�ُ픻����s���A1:�ُ픻����s��Ȃ�) */
			cXmChkFlg = pKmkmst[iKmkCnt].xmchkflg;
#ifdef _DEBUG_
			printf( "GetXmChkFlg(%d) : pKmkmst[iKmkCnt].knsgrp        = %s\n", __LINE__, pKmkmst[iKmkCnt].knsgrp );
			printf( "GetXmChkFlg(%d) : pKmkmst[iKmkCnt].kmkcd         = %s\n", __LINE__, pKmkmst[iKmkCnt].kmkcd );
			printf( "GetXmChkFlg(%d) : pKmkmst[iKmkCnt].kaiymd        = %s\n", __LINE__, pKmkmst[iKmkCnt].kaiymd );
			printf( "GetXmChkFlg(%d) : pKmkmst[iKmkCnt].haiymd        = %s\n", __LINE__, pKmkmst[iKmkCnt].haiymd );
			printf( "GetXmChkFlg(%d) : pKnsgrp                        = %s\n", __LINE__, pKnsgrp );
			printf( "GetXmChkFlg(%d) : pKmkcd                         = %s\n", __LINE__, pKmkcd );
			printf( "GetXmChkFlg(%d) : cWrkKnskisymd                  = %s\n", __LINE__, cWrkKnskisymd );
			printf( "GetXmChkFlg(%d) : pKmkmst[iKmkCnt].xmchkflg      = %c\n", __LINE__, pKmkmst[iKmkCnt].xmchkflg );
			printf( "GetXmChkFlg(%d) : cXmChkFlg                      = %c\n\n", __LINE__, cXmChkFlg );
#endif
			break;
		}
	}

	return cXmChkFlg;

}

//******************************************************************************
//
//	�g���[�X�֐�
//
//******************************************************************************
#if 0
my_trace(Kekka *pKekka, int KekkaCnt, int KenorderCnt )
{
  int      idx ;

  my_loging ( "MY_TRACE\n", idx ) ;
  // �I�[�_���
  my_loging ( "��������������������������\n" ) ;
  my_loging ( "��������������������������\n" ) ;
  my_loging ( "�������I�[�_���[%d]������\n", KenorderCnt ) ;
  my_loging ( "��������������������������\n" ) ;
  my_loging ( "��������������������������\n" ) ;
  for ( idx = 0 ; idx <  KenorderCnt ; idx ++ ) {
      my_loging ( "\%d --------------------------------------\n", idx ) ;
      my_loging ( "\t����No       : [%s]\n", pKenorder[idx].kntno ) ;
      my_loging ( "\t�����O���[�v : [%s]\n", pKenorder[idx].knsgrp ) ;
      my_loging ( "\t���ڃR�[�h   : [%s]\n", pKenorder[idx].kmkcd ) ;
      my_loging ( "\t������     : [%d]\n", pKenorder[idx].knssu ) ;
      my_loging ( "\t���b�NID     : [%s]\n", pKenorder[idx].asyrckid ) ;
      my_loging ( "\t���b�NPOS    : [%d]\n", pKenorder[idx].asyrckpos ) ;
  }

  // ���ʏ��
  my_loging ( "��������������������������\n" ) ;
  my_loging ( "��������������������������\n" ) ;
  my_loging ( "������ ���ʏ�� [%d]������\n", KekkaCnt ) ;
  my_loging ( "��������������������������\n" ) ;
  my_loging ( "��������������������������\n" ) ;
  for ( idx = 0 ; idx <  KekkaCnt ; idx ++ ) {
      my_loging ( "\%d --------------------------------------\n", idx ) ;
      my_loging ( "\t����No       : [%s]\n", pKekka[idx].kntno ) ;
      my_loging ( "\t�����O���[�v : [%s]\n", pKekka[idx].knsgrp ) ;
      my_loging ( "\t���ڃR�[�h   : [%s]\n", pKekka[idx].kmkcd ) ;
      my_loging ( "\t������     : [%d]\n", pKekka[idx].knssu ) ;
      my_loging ( "\t���b�NID     : [%s]\n", pKekka[idx].asyrckid ) ;
      my_loging ( "\t���b�NPOS    : [%d]\n", pKekka[idx].asyrckpos ) ;
      my_loging ( "\tRAW�f�[�^    : [%s]\n", pKekka[idx].rawdata ) ;
  }
  return ;
}
#endif
