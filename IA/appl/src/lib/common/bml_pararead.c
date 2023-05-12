/*******************************************************************

	SYSTEM NAME:	�P�~�X�g���[
	FILE NAME:		�p�����[�^�[�t�@�C���ǂݍ���
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

#include	"bml_pararead.h"				/* for  ���v���Z�X��`		*/

/********************************************************************
	�O���ϐ�
*********************************************************************/
extern	int		errno;

/********************************************************************
	�O���[�o���ϐ�
*********************************************************************/

/********************************************************************
	�v���g�^�C�v�錾
*********************************************************************/
int		GetIniValue(char *IniPath,char *Section,char *Name,char *Value);
static	int		IniFileOpen(char *IniPath,FILE **fp);
static	int		IniFileRead(FILE **fp,char *Section,char *Name,char *Value);
static	int		IniBuffTrim(char *InBuff,char *OutBuff);
static	int		IniGetSection(char *Buff,char *Section);
static	int		IniGetName(char *Buff,char *Name,char *Value);
static	int		IniToUpper(char *inBuff,char *outBuff);
extern	int		LIB_trim();

#ifdef	_TEST_
int main(int argc,char **argv)
{

	int		ret;
	char	sValue[24];

	memset(sValue,0x00,sizeof(sValue));
	if (argc < 4) {
		printf("Parameter Error\n");
		return 0;
	}

	ret = GetIniValue(argv[1],argv[2],argv[3],sValue);
	printf("[%s][%d][%s]\n",argv[1],ret,sValue);

	return 0;
}
#endif


/*---------------------------------------------------------------
fh�i�����j
	int		GetIniValue(char *IniPath,char *Section,char *Name,char *Value)
hc�i�֐��̋@�\�j
	ini�t�@�C������l���擾����
rt�i�߂�l�j
		���� : INI_RET_NORMAL
		�ُ� : INI_RET_NORMAL �ȊO
db�i�����j
		IniPath	�F	ini�t�@�C���p�X
					�p�X����΃p�X�łȂ��ꍇ�A$HOME/ini/ ����̑��΃p�X�ƌ��Ȃ�
		Section	�F	�Z�N�V������(I)
		Name	�F	�p�����[�^��(I)
		Value	�F	�p�����[�^�l(O)
er�i�G���[���̏����j
		����
---------------------------------------------------------------*/
int		GetIniValue(char *IniPath,char *Section,char *Name,char *Value)
{
	int		nRet;
	char	sSection[INI_LENGTH_MAX];
	char	sName[INI_LENGTH_MAX];
	char	sValue[INI_LENGTH_MAX];
	char	sPath[INI_LENGTH_MAX];
	FILE	*fp;

	fp = NULL;
	memset(sValue,0x00,sizeof(sValue));
	strcpy(Value,sValue);
	IniToUpper(Section,sSection);
	IniToUpper(Name,sName);

	LIB_trim(sSection,sSection);
	if (sSection[0] == 0x00) {
		return(INI_RET_SECNFD);
	}

	LIB_trim(sName,sName);
	if (sName[0] == 0x00) {
		return(INI_RET_NAMENFD);
	}

	/*	���΃p�X�`�F�b�N	*/
	if (IniPath[0] == '/') {
		strcpy(sPath,IniPath);
	} else {
		sprintf(sPath,"%s/ini/%s",(char *)getenv("HOME"),IniPath);
	}

	/* ini�t�@�C���n�o�d�m	*/
	nRet = IniFileOpen(sPath,&fp);
	if (nRet != INI_RET_NORMAL) {
		return(nRet);
	}

	/* ini�t�@�C���q�d�`�c	*/
	nRet = IniFileRead(&fp,sSection,sName,sValue);
	if (nRet != INI_RET_NORMAL) {
		fclose(fp);
		return(nRet);
	}

	fclose(fp);
	strcpy(Value,sValue);
	return(INI_RET_NORMAL);
}

/*---------------------------------------------------------------
fh�i�����j
	static	int		IniFileOpen(char *IniPath,FILE *fp)
hc�i�֐��̋@�\�j
	ini�t�@�C���n�o�d�m
rt�i�߂�l�j
		���� : INI_RET_NORMAL
		�ُ� : INI_RET_NORMAL �ȊO
db�i�����j
		IniPath	�Fini�t�@�C���p�X
		fp		�F�Nini�t�@�C���ւ̃t�@�C���|�C���^
er�i�G���[���̏����j
		����
---------------------------------------------------------------*/
static	int		IniFileOpen(char *IniPath,FILE **fp)
{
	int		nRet;
	struct	stat	st;
	
	//	�t�@�C���̑��݃`�F�b�N
	nRet = stat(IniPath,&st);
	if (nRet != 0) {
		switch(errno) {
			case 0:
				break;
			case ENOENT:
				return(INI_RET_ENOENT);
				break;
			default:
				return(INI_RET_ERROR);
				break;
		}
	}

	//	�f�B���N�g�����`�F�b�N
	if (S_ISDIR(st.st_mode) != 0) {
		return(INI_RET_EISDIR);
	}

	//	�t�@�C�����n�o�d�m
    *fp = fopen(IniPath,"r");
	if (*fp == NULL) {
		switch(errno) {
			case ENOENT:
				return(INI_RET_ENOENT);
				break;
			case EACCES:
				return(INI_RET_EACCES);
				break;
			default:
				return(INI_RET_ERROR);
				break;
		}
	}

	return(INI_RET_NORMAL);
}

/*---------------------------------------------------------------
fh�i�����j
	static	int		IniFileRead(FILE *fp,char *Section,char *Name,char *Value)
hc�i�֐��̋@�\�j
	ini�t�@�C���q�d�`�c
rt�i�߂�l�j
		���� : INI_RET_NORMAL
		�ُ� : INI_RET_NORMAL �ȊO
db�i�����j
		fp		�F�Nini�t�@�C���ւ̃t�@�C���|�C���^
		Section	�F�Z�N�V������
		Name	�F�p�����[�^��
		Value	�F�p�����[�^�l
er�i�G���[���̏����j
		����
---------------------------------------------------------------*/
static	int		IniFileRead(FILE **fp,char *Section,char *Name,char *Value)
{
	int		nRet;
	int		nReturn;
	int		nLen;
	int		nFlg;
	int		nFlgSec;
	int		nFlgName;
	char	*pRet;
	char	sBuff[INI_LENGTH_MAX];
	char	sSection[INI_LENGTH_MAX];
	char	sName[INI_LENGTH_MAX];
	char	sValue[INI_LENGTH_MAX];

	memset(sValue,0x00,sizeof(sValue));
	Value[0] = 0x00;

	nFlg = 0;
	nFlgSec = 0;
	nFlgName = 0;
	nReturn = INI_RET_ERROR;
	for (;;) {
		//	�P�s���ǂݍ���
		pRet = fgets(sBuff,sizeof(sBuff),*fp);
		if (pRet == NULL) {
			//	�d�n�e���`�F�b�N
			nRet = feof(*fp);
			if (nRet != 0) {
				break;
			} else {
				return(INI_RET_EIO);
			}
		}

		//	�s���̉��s�R�[�h�����
		nRet = IniBuffTrim(sBuff,sBuff);
		if (nRet == 0) {
			continue;
		}

		//	�Z�N�V�������̃`�F�b�N
		nRet = IniGetSection(sBuff,sSection);
		if (nRet == INI_RET_NORMAL) {
			if (strcmp(sSection,Section) == 0) {
				nFlg = 1;
				nFlgSec = 1;
			} else {
				nFlg = 0;
			}
		} else {
			if (nFlg != 0) {
				//	�p�����[�^���̃`�F�b�N
				nRet = IniGetName(sBuff,sName,sValue);
				if (nRet == INI_RET_NORMAL) {
					if (strcmp(sName,Name) == 0) {
						nLen = strlen(sValue);
						strncpy(Value,sValue,nLen);
						Value[nLen] = 0x00;
						nReturn = INI_RET_NORMAL;
						nFlgName = 1;
						break;
					}
				}
			}
		}
	}

	if (nFlgSec == 0) {
		nReturn = INI_RET_SECNFD;
	}
	if (nFlgName == 0) {
		nReturn = INI_RET_NAMENFD;
	}

	return(nReturn);
}

/*---------------------------------------------------------------
fh�i�����j
	static	int		IniBuffTrim(char *InBuff,char *OutBuff)
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
static	int		IniBuffTrim(char *InBuff,char *OutBuff)
{
	int		nRet;
	int		nLen;
	int		nIdx;
	int		nPos;
	char	sWork[INI_LENGTH_MAX];
	char	sWork2[INI_LENGTH_MAX];

	memset(sWork,0x00,sizeof(sWork));
	memset(sWork2,0x00,sizeof(sWork2));

	strncpy(sWork,InBuff,INI_LENGTH_MAX);
	sWork[INI_LENGTH_MAX] = 0x00;

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

	//	�R�����g�i�Z�~�R�����ȍ~�j���폜
	nLen = strlen(sWork2);
	for (nIdx=0;nIdx<nLen;nIdx++) {
		if (sWork2[nIdx] == ';') {
			sWork2[nIdx] = 0x00;
			break;
		}
	}

	//	�s���̃X�y�[�X�A�s�`�a�A���s�R�[�h�����
	for (;;) {
		nLen = strlen(sWork2);
		if ((sWork2[nLen-1] == ' ') || (sWork[nLen-1] == 0x09) || (sWork2[nLen-1] == 0x0a)) {
			sWork2[nLen-1] = 0x00;
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
	static	int		IniGetSection(char *Buff,char *Section)
hc�i�֐��̋@�\�j
	ini�t�@�C���Z�N�V�������擾
rt�i�߂�l�j
		���� : INI_RET_NORMAL
		�ُ� : INI_RET_NORMAL �ȊO
db�i�����j
		Buff	�F�ǂݍ��ݕ�����
		Section	�F�Z�N�V������
er�i�G���[���̏����j
		����
---------------------------------------------------------------*/
static	int		IniGetSection(char *Buff,char *Section)
{
	int		nLen;
	int		nIdx;
	int		nCnt1;
	int		nCnt2;
	int		nPos1;
	int		nPos2;
	char	sWork[INI_LENGTH_MAX];
	char	sSection[INI_LENGTH_MAX];

	memset(sWork,0x00,sizeof(sWork));
	memset(sSection,0x00,sizeof(sSection));

	strncpy(sWork,Buff,INI_LENGTH_MAX);
	sWork[INI_LENGTH_MAX] = 0x00;

	nLen = strlen(sWork);
	nCnt1 = 0;
	nCnt2 = 0;
	nPos1 = 0;
	nPos2 = 0;

	//	�Z�N�V��������
	for (nIdx=0;nIdx<nLen;nIdx++) {
		if (sWork[nIdx] == '[') {
			nCnt1++;
			nPos1 = nIdx;
		}
		if (sWork[nIdx] == ']') {
			nCnt2++;
			nPos2 = nIdx;
		}
	}

	if ((nCnt1 != 1) || (nCnt2 != 1) || (nPos1 >= nPos2)) {
		return(INI_RET_ERROR);
	}

	//	�Z�N�V�������؂�o��
	strncpy(sSection,&sWork[nPos1+1],nPos2-nPos1-1);
	sSection[nPos2-nPos1-1] = 0x00;
	IniToUpper(sSection,sSection);

	nLen = strlen(sSection);
	strncpy(Section,sSection,nLen);
	Section[nLen] = 0x00;

	return(INI_RET_NORMAL);
}

/*---------------------------------------------------------------
fh�i�����j
	static	int		IniGetName(char *Buff,char *Name,char *Value)
hc�i�֐��̋@�\�j
	ini�t�@�C���p�����[�^�擾
rt�i�߂�l�j
		���� : INI_RET_NORMAL
		�ُ� : INI_RET_NORMAL �ȊO
db�i�����j
		Buff	�F�ǂݍ��ݕ�����
		Name	�F�p�����[�^��
		Value	�F�p�����[�^�l
er�i�G���[���̏����j
		����
---------------------------------------------------------------*/
static	int		IniGetName(char *Buff,char *Name,char *Value)
{
	int		nLen;
	int		nIdx;
	int		nCnt1;
	int		nCnt2;
	int		nPos1;
	int		nPos2;
	char	sWork[INI_LENGTH_MAX];
	char	sName[INI_LENGTH_MAX];
	char	sValue[INI_LENGTH_MAX];

	memset(sWork,0x00,sizeof(sWork));
	memset(sName,0x00,sizeof(sName));
	memset(sValue,0x00,sizeof(sValue));

	strncpy(sWork,Buff,INI_LENGTH_MAX);
	sWork[INI_LENGTH_MAX] = 0x00;

	nLen = strlen(sWork);
	nCnt1 = 0;
	nPos1 = 0;
	for (nIdx=0;nIdx<nLen;nIdx++) {
		if (sWork[nIdx] == '=') {
			nCnt1++;
			if (nCnt1 == 1) {
				nPos1 = nIdx;
			}
		}
	}

//	if (nCnt1 > 1) {
//		return(INI_RET_ERROR);
//	}

	if (nCnt1 == 0) {
		strcpy(Name,sWork);
		strcpy(Value,sValue);
		return(INI_RET_NORMAL);
	}

	strncpy(sName,sWork,nPos1);
	sName[nPos1] = 0x00;
	IniToUpper(sName,sName);

	strncpy(sValue,&sWork[nPos1+1],nLen-nPos1-1);
	sValue[nLen-nPos1-1] = 0x00;
//	IniToUpper(sValue,sValue);

	nLen = strlen(sName);
	strncpy(Name,sName,nLen);
	Name[nLen] = 0x00;

	nLen = strlen(sValue);
	strncpy(Value,sValue,nLen);
	Value[nLen] = 0x00;

	return(INI_RET_NORMAL);
}

/*---------------------------------------------------------------
fh�i�����j
	static	int		IniToUpper(char *inBuff,char *outBuff)
hc�i�֐��̋@�\�j
	�������啶���֕ϊ�
rt�i�߂�l�j
		���� : INI_RET_NORMAL
		�ُ� : INI_RET_NORMAL �ȊO
db�i�����j
		inBuff	�F���͕�����
		outBuff	�F�o�͕�����
er�i�G���[���̏����j
		����
---------------------------------------------------------------*/
static	int		IniToUpper(char *inBuff,char *outBuff)
{
	int		nLoop;
	int		nLen;
	int		nChar;
	char	sInWork[INI_LENGTH_MAX];
	char	sOutWork[INI_LENGTH_MAX];

	strcpy(sInWork,inBuff);
	memset(sOutWork,0x00,sizeof(sOutWork));
//	strcpy(outBuff,sOutWork);

	nLen = strlen(sInWork);
	for (nLoop=0;nLoop<nLen;nLoop++) {
		nChar = toupper((int)sInWork[nLoop]);
		sOutWork[nLoop] = (char)nChar;
	}
	strcpy(outBuff,sOutWork);

	return(INI_RET_NORMAL);
}
