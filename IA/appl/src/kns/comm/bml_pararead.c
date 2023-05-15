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

static	FILE	*ParaFp;

/********************************************************************
	�v���g�^�C�v�錾
*********************************************************************/
int		BmlParaInit(void);
int		BmlParaOpen(char *ParaPath);
int		BmlParaClose(void);
int		BmlParaRead(char *ReadBuff);

static	int		IniBuffTrim(char *InBuff,char *OutBuff);
static	int		IniToUpper(char *inBuff,char *outBuff);

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
	int		BmlParaInit(void)
hc�i�֐��̋@�\�j
	�֐��̎g�p�J�n���̏�����
rt�i�߂�l�j
		���� : PARA_RET_NORMAL
		�ُ� : PARA_RET_NORMAL �ȊO
db�i�����j
		����
er�i�G���[���̏����j
		����
---------------------------------------------------------------*/
int		BmlParaInit(void)
{
	ParaFp = NULL;

	return(PARA_RET_NORMAL);
}






/*---------------------------------------------------------------
fh�i�����j
	int		BmlParaOpen(char *ParaPath)
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
int		BmlParaOpen(char *ParaPath)
{
	int		nRet;
	char	sPath[PARA_LENGTH_MAX];
	struct	stat	st;

	if (ParaFp != NULL) {
		return(RAPA_RET_NORMAL);
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
	int		BmlParaClose(void)
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
int		BmlParaClose(void)
{
	int		nRet;

	if (ParaFp != NULL) {
		return(RAPA_RET_NORMAL);
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
	int		BmlParaRead(char *ReadBuff)
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
int		BmlParaRead(char *ReadBuff)
{
	int		nRet;
	int		nReturn;
	int		nLen;
	int		nFlg;
	char	*pRet;
	char	sBuff[PARA_LENGTH_MAX];

	if (ParaFp != NULL) {
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
