/*******************************************************************

	SYSTEM NAME:	�P�~�X�g���[
	FILE NAME:		�I�����C�������p���ʊ֐�
	DATE/Var:		2023/05/11	Ver.1.00
	Edited:			T.Hanyu

*******************************************************************/

/*******************************************************************
	�C���N���[�h�t�@�C��
********************************************************************/
#include	<stdio.h>					/* for	�W���C���N��-�h�t�@�C��		*/
#include	<stdlib.h>					/* for	�W���C���N��-�h�t�@�C��		*/
#include	<string.h>					/* for	�W���C���N��-�h�t�@�C��		*/
#include	<ctype.h>					/* for	�W���C���N��-�h�t�@�C��		*/
#include	<sys/stat.h>				/* for 	�W���C���N��-�h�t�@�C��		*/
#include	<sys/types.h>				/* for 	�W���C���N��-�h�t�@�C��		*/
#include	<sys/errno.h>				/* for 	�W���C���N��-�h�t�@�C��		*/

#include	"kns_common.h"				/* for  ���v���Z�X��`		*/

/********************************************************************
	�O���ϐ�
*********************************************************************/
extern	int		errno;

/********************************************************************
	�O���[�o���ϐ�
*********************************************************************/

static	FILE	*ParaFp;
static	KMKTBL	*KmkTbl;
static	int		nTblCount;

/********************************************************************
	�v���g�^�C�v�錾
*********************************************************************/
int		KnsParaInit(char *ParaPath);
int		KnsParaFind(char *Kmkcd,char *Value);
int		KnsParaFree(void);
int		KnsLowDataCheck(Kekka *pKekka,int nKekkaNum);

static	int		KnsParaOpen(char *ParaPath);
static	int		KnsParaClose(void);
static	int		KnsParaRead(char *ReadBuff);
static	int		ParaBuffTrim(char *InBuff,char *OutBuff);
static	int		ParaToUpper(char *inBuff,char *outBuff);
static	int		ParaNumCheck(char *inBuff);
static	int		ParaDataSet(char *ReadBuff,int nIdx);

#ifdef	_TEST_
int main(int argc,char **argv)
{

	int		ret;
	char	sValue[24];

	memset(sValue,0x00,sizeof(sValue));
	if (argc < 2) {
		printf("Parameter Error\n");
		return 0;
	}

	ret = GetIniValue(argv[1],sValue);
	printf("[%s][%d][%s]\n",argv[1],ret,sValue);

	return 0;
}
#endif

/*---------------------------------------------------------------
fh�i�����j
	int		KnsParaInit(char *ParaPath)
hc�i�֐��̋@�\�j
	�֐��̎g�p�J�n���̏�����
rt�i�߂�l�j
		���� : PARA_RET_NORMAL
		�ُ� : PARA_RET_NORMAL �ȊO
db�i�����j
		ParaPath	�p�����[�^�t�@�C���̃p�X
er�i�G���[���̏����j
		����
---------------------------------------------------------------*/
int		KnsParaInit(char *ParaPath)
{
	int		nRet;
	int		nLoop;
	char	sBuff[PARA_LENGTH_MAX];

	ParaFp = NULL;
	KmkTbl = NULL;
	nTblCount = 0;

	nRet = KnsParaOpen(ParaPath);
	if (nRet != PARA_RET_NORMAL) {
		return(nRet);
	}

	for (;;) {
		memset(sBuff,0x00,sizeof(sBuff));
		nRet = KnsParaRead(sBuff);
		if (nRet != PARA_RET_NORMAL) {
			KnsParaClose();
			return(nRet);
		}
		if (sBuff[0] == 0x00) {
			break;
		}
		nTblCount++;
	}

	nRet = KnsParaClose();
	if (nRet != PARA_RET_NORMAL) {
		return(nRet);
	}

	KmkTbl = (KMKTBL *)malloc(sizeof(KMKTBL)*(nTblCount+1));
	if (KmkTbl == NULL) {
		return(PARA_RET_ENOMEM);
	}
	memset(KmkTbl->kmkcd,0x00,sizeof(KMKTBL)*(nTblCount+1));

	nRet = KnsParaOpen(ParaPath);
	if (nRet != PARA_RET_NORMAL) {
		return(nRet);
	}

	for (nLoop=0;nLoop<nTblCount;nLoop++) {
		memset(sBuff,0x00,sizeof(sBuff));
		nRet = KnsParaRead(sBuff);
		if (nRet != PARA_RET_NORMAL) {
			KnsParaClose();
			return(nRet);
		}
		if (sBuff[0] == 0x00) {
			break;
		}
		nRet = ParaDataSet(sBuff,nLoop);
		if (nRet != PARA_RET_NORMAL) {
			KnsParaClose();
			return(nRet);
		}
	}

	nRet = KnsParaClose();
	if (nRet != PARA_RET_NORMAL) {
		return(nRet);
	}

	return(PARA_RET_NORMAL);
}


/*---------------------------------------------------------------
fh�i�����j
	int		KnsParaFind(char *Kmkcd,char *Value)
hc�i�֐��̋@�\�j
	�������̈悩��w�荀�ڃR�[�h�̃f�[�^���擾����
rt�i�߂�l�j
		���� : PARA_RET_NORMAL
		�ُ� : PARA_RET_NFND 	���ڃR�[�h������
		       PARA_RET_ERROR	�G���[����
db�i�����j
		Kmkcd	�F�������ڃR�[�h
		Valuef	�F�擾�f�[�^
er�i�G���[���̏����j
		����
---------------------------------------------------------------*/
int		KnsParaFind(char *Kmkcd,char *Value)
{
	int		nLoop;
	char	sValue[KMKTBL_LEN_VALUE+1];

	memset(sValue,0x00,sizeof(sValue));
	for (nLoop=0;nLoop<nTblCount;nLoop++) {
		if (strncmp((KmkTbl+nLoop)->kmkcd,Kmkcd,KMKTBL_LEN_KMKCD) == 0) {
			strncpy(sValue,(KmkTbl+nLoop)->value,KMKTBL_LEN_VALUE);
			sValue[KMKTBL_LEN_VALUE] = 0x00;
			strcpy(Value,sValue);
			break;
		}
	}

	if (sValue[0] == 0x00) {
		return(PARA_RET_NFND);
	}

	return(PARA_RET_NORMAL);
}

/*---------------------------------------------------------------
fh�i�����j
	int		KnsParaFree(void)
hc�i�֐��̋@�\�j
	�������̈���J������
rt�i�߂�l�j
		���� : PARA_RET_NORMAL
		�ُ� : PARA_RET_NORMAL �ȊO
db�i�����j
		����
er�i�G���[���̏����j
		����
---------------------------------------------------------------*/
int		KnsParaFree(void)
{
	int		nRet;

	if (KmkTbl == NULL) {
		return(PARA_RET_NORMAL);
	}

	free(KmkTbl);

	KmkTbl = NULL;
	nTblCount = 0;

	return(PARA_RET_NORMAL);
}

/*---------------------------------------------------------------
fh�i�����j
	int		KnsLowDataCheck(Kekka *pKekka,int nKekkaNum)
hc�i�֐��̋@�\�j
	��l�Č��`�F�b�N
rt�i�߂�l�j
		���� : PARA_RET_NORMAL
		�ُ� : PARA_RET_NORMAL �ȊO
db�i�����j
		pKekka		�������ʏ��ւ̃|�C���^
		nKekkaNum	�������ʏ��̐�
er�i�G���[���̏����j
		����
---------------------------------------------------------------*/
int		KnsLowDataCheck(Kekka *pKekka,int nKekkaNum)
{
	int		nRet;
	int		nLoop;
	int		nFlg;
	char	sKmkcd[KMKTBL_LEN_KMKCD+1];
	char	sValue[KMKTBL_LEN_VALUE+1];
	char	sHjkka[KMKTBL_LEN_HJKKA+1];
	double	dHjkka;
	double	dLowData;

	nFlg = 0;
	for (nLoop=0;nLoop<nKekkaNum;nLoop++) {
		memset(sKmkcd,0x00,sizeof(sKmkcd));
		trim(sKmkcd,pKekka[nLoop].kmkcd);
		if (sKmkcd[0] == 0x00) {
			continue;
		}
		memset(sHjkka,0x00,sizeof(sHjkka));
		strncpy(sHjkka,pKekka[nLoop].hjkka,KMKTBL_LEN_HJKKA);
		sHjkka[KMKTBL_LEN_HJKKA] = 0x00;

		nRet = ParaNumCheck(sHjkka);
		if (nRet != PARA_RET_NORMAL) {
			// ���l����Ȃ��ꍇ�͔�r���Ȃ�
			continue;
		}
		dHjkka = atof(sHjkka) + 0.00001;

		nRet = KnsParaFind(sKmkcd,sValue);
		if (nRet == PARA_RET_NFND) {
			//	�ݒ�l��������Ȃ��ꍇ�̓`�F�b�N���Ȃ�
			continue;
		}
		if (nRet != PARA_RET_NORMAL) {
			//	���̑��̃G���[
			return(PARA_RET_ERROR);
		}
		nRet = ParaNumCheck(sValue);
		if (nRet != PARA_RET_NORMAL) {
			// ���l����Ȃ��ꍇ�͔�r���Ȃ�
			continue;
		}
		dLowData = atof(sValue) + 0.00001;
		if (dHjkka < dLowData) {
			nFlg = -1;
			break;
		}
	}

	//	�ݒ�l�ȉ��̍��ڂ��������ꍇ
	if (nFlg != 0) {
		for (nLoop=0;nLoop<nKekkaNum;nLoop++) {
			/* �ۗ��������̃t���O�͕ς��Ȃ� */
			if (pKekka[nLoop].knsflg != 'H'){
				pKekka[nLoop].knsflg = 'R';
			}
		}
	}

	return(PARA_RET_NORMAL);
}

/*---------------------------------------------------------------
fh�i�����j
	static	int		KnsParaOpen(char *ParaPath)
hc�i�֐��̋@�\�j
	�p�����[�^�t�@�C�����I�[�v������
rt�i�߂�l�j
		���� : PARA_RET_NORMAL
		�ُ� : PARA_RET_NORMAL �ȊO
db�i�����j
	ParaPath	�p�����[�^�t�@�C���p�X
				�p�X����΃p�X�łȂ��ꍇ�A$HOME/ ����̑��΃p�X�ƌ��Ȃ�
er�i�G���[���̏����j
		����
---------------------------------------------------------------*/
static	int		KnsParaOpen(char *ParaPath)
{
	int		nRet;
	char	sPath[PARA_LENGTH_MAX];
	struct	stat	st;

	if (ParaFp != NULL) {
		return(PARA_RET_NORMAL);
	}

	/*	���΃p�X�`�F�b�N	*/
	if (ParaPath[0] == '/') {
		strcpy(sPath,ParaPath);
	} else {
		sprintf(sPath,"%s/%s",(char *)getenv("HOME"),ParaPath);
	}

	//	�t�@�C���̑��݃`�F�b�N
	nRet = stat(sPath,&st);
	if (nRet != 0) {
		switch(errno) {
			case 0:
				break;
			case ENOENT:
				return(PARA_RET_ENOENT);
				break;
			default:
				return(PARA_RET_ERROR);
				break;
		}
	}

	//	�f�B���N�g�����`�F�b�N
	if (S_ISDIR(st.st_mode) != 0) {
		return(PARA_RET_EISDIR);
	}

	//	�t�@�C�����n�o�d�m
    ParaFp = fopen(ParaPath,"r");
	if (ParaFp == NULL) {
		switch(errno) {
			case ENOENT:
				return(PARA_RET_ENOENT);
				break;
			case EACCES:
				return(PARA_RET_EACCES);
				break;
			default:
				return(PARA_RET_ERROR);
				break;
		}
	}

	return(PARA_RET_NORMAL);
}

/*---------------------------------------------------------------
fh�i�����j
	static	int		KnsParaClose(void)
hc�i�֐��̋@�\�j
	�p�����[�^�t�@�C�����N���[�Y����
	ini�t�@�C���n�o�d�m
rt�i�߂�l�j
		���� : PARA_RET_NORMAL
		�ُ� : PARA_RET_NORMAL �ȊO
db�i�����j
		IniPath	�Fini�t�@�C���p�X
		fp		�F�Nini�t�@�C���ւ̃t�@�C���|�C���^
er�i�G���[���̏����j
		����
---------------------------------------------------------------*/
static	int		KnsParaClose(void)
{
	int		nRet;

	if (ParaFp != NULL) {
		return(PARA_RET_NORMAL);
	}

	nRet = fclose(ParaFp);
	if (nRet != 0) {
		ParaFp = NULL;
		return(PARA_RET_ERROR);
	}

	ParaFp = NULL;
	return(PARA_RET_NORMAL);
}


/*---------------------------------------------------------------
fh�i�����j
	static	int		KnsParaRead(char *ReadBuff)
hc�i�֐��̋@�\�j
	ini�t�@�C���q�d�`�c
rt�i�߂�l�j
		���� : PARA_RET_NORMAL
		�ُ� : PARA_RET_NORMAL �ȊO
db�i�����j
		ReadBuff�F�ǂݍ��݃o�b�t�@�[
er�i�G���[���̏����j
		����
---------------------------------------------------------------*/
static	int		KnsParaRead(char *ReadBuff)
{
	int		nRet;
	int		nReturn;
	int		nLen;
	int		nFlg;
	char	*pRet;
	char	sBuff[PARA_LENGTH_MAX];

	if (ParaFp == NULL) {
		return(PARA_RET_ERROR);
	}

	nReturn = PARA_RET_ERROR;
	for (;;) {
		memset(sBuff,0x00,sizeof(sBuff));
		//	�P�s���ǂݍ���
		pRet = fgets(sBuff,sizeof(sBuff),ParaFp);
		if (pRet == NULL) {
			//	�d�n�e���`�F�b�N
			nRet = feof(ParaFp);
			if (nRet != 0) {
				break;
			} else {
				return(PARA_RET_EIO);
			}
		}

		//	�s���̉��s�R�[�h�����
		nRet = ParaBuffTrim(sBuff,sBuff);
		if (nRet == 0) {
			//	�󔒍s�������̓R�����g�s�Ȃ̂Ōp��
			continue;
		} else {
			break;
		}
	}

	strcpy(ReadBuff,sBuff);

	return(nReturn);
}

/*---------------------------------------------------------------
fh�i�����j
	static	int		ParaBuffTrim(char *InBuff,char *OutBuff)
hc�i�֐��̋@�\�j
	�s���̃X�y�[�X�A�s�`�a�ƍs���̉��s�R�[�h�����
	�R�����g�i�Z�~�R�����ȍ~�j���폜
rt�i�߂�l�j
		������̕�����
db�i�����j
		InBUff	�F���͕�����
		OutBUff	�F�o�͕�����
er�i�G���[���̏����j
		����
---------------------------------------------------------------*/
static	int		ParaBuffTrim(char *InBuff,char *OutBuff)
{
	int		nRet;
	int		nLen;
	int		nIdx;
	int		nPos;
	char	sWork[PARA_LENGTH_MAX];
	char	sWork2[PARA_LENGTH_MAX];

	memset(sWork,0x00,sizeof(sWork));
	memset(sWork2,0x00,sizeof(sWork2));

	strncpy(sWork,InBuff,PARA_LENGTH_MAX-1);
	sWork[PARA_LENGTH_MAX-1] = 0x00;

	//	�s���̃X�y�[�X�A�s�`�a�����
	nLen = strlen(sWork);
	nPos = 0;
	for (nIdx=0;nIdx<nLen;nIdx++) {
		if ((sWork[nIdx] == ' ') || (sWork[nIdx] == 0x09) || (sWork[nIdx] == 0x00)) {
			nPos = nIdx + 1;
		} else {
			break;
		}
	}
	nLen = strlen(&sWork[nPos]);
	strncpy(sWork2,&sWork[nPos],nLen);
	sWork2[nLen] = 0x00;

	//	�R�����g�i# or ; �ȍ~�j���폜
	nLen = strlen(sWork2);
	for (nIdx=0;nIdx<nLen;nIdx++) {
		if ((sWork2[nIdx] == '#') ||
			(sWork2[nIdx] == ';')) {
			sWork2[nIdx] = 0x00;
			break;
		}
	}

	//	�s���̃X�y�[�X�A�s�`�a�A���s�R�[�h�����
	for (;;) {
		nLen = strlen(sWork2);
		if (nLen > 0) {
			if ((sWork2[nLen-1] == ' ') || (sWork[nLen-1] == 0x09) || (sWork2[nLen-1] == 0x0a)) {
				sWork2[nLen-1] = 0x00;
			} else {
				break;
			}
		} else {
			break;
		}
	}

	nLen = strlen(sWork2);
	strncpy(OutBuff,sWork2,nLen);
	OutBuff[nLen] = 0x00;

	return(nLen);
}

/*---------------------------------------------------------------
fh�i�����j
	static	int		ParaToUpper(char *inBuff,char *outBuff)
hc�i�֐��̋@�\�j
	�������啶���֕ϊ�
rt�i�߂�l�j
		���� : PARA_RET_NORMAL
		�ُ� : PARA_RET_NORMAL �ȊO
db�i�����j
		inBuff	�F���͕�����
		outBuff	�F�o�͕�����
er�i�G���[���̏����j
		����
---------------------------------------------------------------*/
static	int		ParaToUpper(char *inBuff,char *outBuff)
{
	int		nLoop;
	int		nLen;
	int		nChar;
	char	sInWork[PARA_LENGTH_MAX+1];
	char	sOutWork[PARA_LENGTH_MAX+1];

	strcpy(sInWork,inBuff);
	memset(sOutWork,0x00,sizeof(sOutWork));
//	strcpy(outBuff,sOutWork);

	nLen = strlen(sInWork);
	for (nLoop=0;nLoop<nLen;nLoop++) {
		nChar = toupper((int)sInWork[nLoop]);
		sOutWork[nLoop] = (char)nChar;
	}
	strcpy(outBuff,sOutWork);

	return(PARA_RET_NORMAL);
}

/*---------------------------------------------------------------
fh�i�����j
	static	int		ParaNumCheck(char *inBufff)
hc�i�֐��̋@�\�j
	������̐��l�`�F�b�N
	�����_�͂P�܂łn�j�Ƃ���
rt�i�߂�l�j
		���� : PARA_RET_NORMAL
		�ُ� : PARA_RET_NORMAL �ȊO
db�i�����j
		inBuff	�F���͕�����
er�i�G���[���̏����j
		����
---------------------------------------------------------------*/
static	int		ParaNumCheck(char *inBuff)
{
	int		nLoop;
	int		nLen;
	int		nPoint;
	char	sWork[PARA_LENGTH_MAX+1];

	strcpy(sWork,inBuff);

	nLen = strlen(sWork);
	nPoint = 0;
	for (nLoop=0;nLoop<nLen;nLoop++) {
		if (sWork[nLoop] == '.') {
			nPoint++;
		} else {
			if (isdigit((int)sWork[nLoop]) == 0) {
				return(PARA_RET_ERROR);
			}
		}
	}

	if (nPoint > 1) {
		return(PARA_RET_ERROR);
	}

	return(PARA_RET_NORMAL);
}

/*---------------------------------------------------------------
fh�i�����j
	static	int		ParaDataSet(char *ReadBuff,int nIdx)
hc�i�֐��̋@�\�j
	�ǂݍ��݃f�[�^���������̈�ɃZ�b�g
rt�i�߂�l�j
		���� : PARA_RET_NORMAL
		�ُ� : PARA_RET_NORMAL �ȊO
db�i�����j
		inBuff	�F���͕�����
		nIdx	�F�������̈�̃C���f�b�N�X
er�i�G���[���̏����j
		����
---------------------------------------------------------------*/
static	int		ParaDataSet(char *ReadBuff,int nIdx)
{
	int		nLoop;
	char	sWork[PARA_LENGTH_MAX+1];
	char	*pWork;
	KMKTBL	Tbl;

	strcpy(sWork,ReadBuff);
	//	���͕����񒆂�TAB���X�y�[�X�ɕϊ�
	for (nLoop=0;;nLoop++) {
		if (sWork[nLoop] == 0x00) {
			break;
		}
		if (sWork[nLoop] == 0x09) {
			sWork[nLoop] = ' ';
		}
	}

	memset(Tbl.kmkcd,0x00,sizeof(KMKTBL));
	//	�X�y�[�X����؂蕶���Ƃ��ē��͕�����𕪊�
	pWork = strtok(sWork," ");
	if (pWork != NULL) {
		strncpy(Tbl.kmkcd,pWork,KMKTBL_LEN_KMKCD);
		Tbl.kmkcd[KMKTBL_LEN_KMKCD] = 0x00;
		pWork = strtok(NULL," ");
		if (pWork != NULL) {
			strncpy(Tbl.value,pWork,KMKTBL_LEN_VALUE);
			Tbl.value[KMKTBL_LEN_VALUE] = 0x00;
		}
		memcpy((KmkTbl+nIdx)->kmkcd,Tbl.kmkcd,sizeof(KMKTBL));
	}

	return(PARA_RET_NORMAL);
}

