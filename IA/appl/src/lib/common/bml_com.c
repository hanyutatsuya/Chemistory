/************************************************************************/
/*																		*/
/*		�a�l�k�l���������V�X�e��										*/
/*																		*/
/*		�V�X�e����	�F������V�X�e��									*/
/*		�t�@�C����	�Fbml_com.c											*/
/*		�T�v		�F���̑����ʊ֐�									*/
/*																		*/
/************************************************************************/

/************************************************************************/
/*  Ver.	���t			���O			�C�����e					*/
/* -------------------------------------------------------------------- */
/*  1.00	2005/07/21		E.Osada			Create						*/
/************************************************************************/

/************************************************************************/
/*	�C���N���[�h�錾													*/
/************************************************************************/
#include	"bml_base.h
#include	<time.h>
#include	"bml_com.h"

/************************************************************************/
/*	�֐��錾															*/
/************************************************************************/

/************************************************************************/
/*	�֐���		�FZbmlStrnCpy()											*/
/*	�@�\�T�v	�F�w��o�C�g����������R�s�[����						*/
/* 	����		�F														*/
/*	 ��P����   �Fchar*	pStrOut		������̃R�s�[��					*/
/*	 ��Q����	�Fchar*	pStrIN		������̃R�s�[��					*/
/*	 ��R����	�Fint	Num			������̃R�s�[�o�C�g��				*/
/*	�o��		�F														*/
/*   �Ȃ�																*/
/************************************************************************/
void ZbmlStrnCpy(char* pStrOut, char *pStrIn, int Num)
{
	int		i;

	memset( pStrOut, ' ', Num ); 
	for( i = 0 ;i < Num; i++ ){
		if( *pStrIn == '\0' ){
			return;
		}
		*pStrOut = *pStrIn;
		pStrOut++;
		pStrIn++;
	}
	return;
}

/************************************************************************/
/*	�֐���		�FZbmlCharCpy()											*/
/*	�@�\�T�v	�F�L�����N�^�[���R�s�[����								*/
/*	����		�F														*/
/*	 ��P����	�Fchar*	pCharOut	�L�����N�^�[�̃R�s�[��				*/
/*	 ��Q����	�Fchar*	pCharIN		�L�����N�^�[�̃R�s�[��				*/
/*	�o��		�F														*/
/*   �Ȃ�																*/
/************************************************************************/
void ZbmlCharCpy(char* pCharOut, char *pCharIn)
{
	if( *pCharIn == '\0' ){
		*pCharOut = ' ';
	}else{
		*pCharOut = *pCharIn;
	}
	return;
}

/************************************************************************/
/*	�֐���		�FZbmlGetDateTime()										*/
/*	�@�\�T�v	�F���t�����Ԃ��擾����									*/
/*	����		�F														*/
/*	 ��P����	�Fchar    *pStrOut	���t�����Ԃ��Z�b�g����				*/
/*	�o��		�F														*/
/*   �Ȃ�																*/
/************************************************************************/
void ZbmlGetDateTime(char *pStrOut)
{
    time_t ltime;
	struct tm *today;
    char			buff[20];

    ltime = time(NULL);
    today = localtime( &ltime );
	strftime( buff, sizeof(buff), "%Y%m%d%H%M%S", today );
    strncpy( pStrOut, buff, 14 );

    return;
}

/************************************************************************/
/*	�֐���		�FZbmlGetToday()										*/
/*	�@�\�T�v	�F�{�����t���擾����									*/
/*	����		�F														*/
/*	 ��P����	�Fchar    *pStrOut	�{�����t���Z�b�g����				*/
/*	�o��		�F														*/
/*   �Ȃ�																*/
/************************************************************************/
void ZbmlGetToday(char *pStrOut)
{
    time_t ltime;
	struct tm *today;

    ltime = time(NULL);
    today = localtime( &ltime );
	strftime( pStrOut, 11, "%Y-%m-%d", today );

    return;
}

/************************************************************************/
/*	�֐���		�FZbmlChangeDateDBFormat()								*/
/*	�@�\�T�v	�F���M�f�[�^�̓��t��YYYYMMDD��YYYY-MM-DD�ɕϊ�����		*/
/*	����		�F														*/
/*	 ��P����	�Fchar	*pStrOut	�ϊ����t���i�[����o�b�t�@			*/
/*	 ��Q����	�Fchar	*pStrIn		�ϊ������t							*/
/*	 ��R����	�Fint	iStrSize	�ϊ������t�̃T�C�Y					*/
/*	�o��		�F														*/
/*   �Ȃ�																*/
/************************************************************************/
void ZbmlChangeDateDBFormat(char* pStrOut, char* pStrIn, int iStrSize)
{
    char			buff[20];
	void ifInfocpy();

	memset( pStrOut, '\0', iStrSize );
	if( pStrOut == NULL || pStrIn == NULL || iStrSize < 8 ){
		return;
	}
	if( memcmp( pStrIn,"00000000",8 ) == 0 ){
		strcpy( pStrOut, "1000-01-01" );
		return;
	}
	bmlInfoCpy(buff, pStrIn, iStrSize+1);
	if( buff[0] != '\0' ){
		sprintf(pStrOut, "%4.4s-%2.2s-%2.2s", buff, &buff[4], &buff[6] );
	}else{
		strcpy( pStrOut, "1000-01-01" );
	}

    return;
}

/************************************************************************/
/*	�֐���		�FZbmlChangeYukoDateDBFormat()							*/
/*	�@�\�T�v	�F���M�f�[�^�̗L�����t��YYYYMMDD��YYYY-MM-DD�ɕϊ�����	*/
/*	����		�F														*/
/*	 ��P����	�Fchar	*pStrOut	�ϊ����t���i�[����o�b�t�@			*/
/*	 ��Q����	�Fchar	*pStrIn		�ϊ������t							*/
/*	 ��R����	�Fint	iStrSize	�ϊ������t�̃T�C�Y					*/
/*	�o��		�F														*/
/*   �Ȃ�																*/
/************************************************************************/
void ZbmlChangeYukoDateDBFormat(char* pStrOut, char* pStrIn, int iStrSize)
{
    char			buff[20];

	memset( pStrOut, '\0', iStrSize );
	if( pStrOut == NULL || pStrIn == NULL || iStrSize < 8 ){
		return;
	}
	if( memcmp( pStrIn,"00000000",8 ) == 0 ){
		strcpy( pStrOut, "9999-12-31" );
		return;
	}
	bmlInfoCpy(buff, pStrIn, iStrSize+1);
	if( buff[0] != '\0' ){
		sprintf(pStrOut, "%4.4s-%2.2s-%2.2s", buff, &buff[4], &buff[6] );
	}else{
		strcpy( pStrOut, "9999-12-31" );
	}

    return;
}

/************************************************************************/
/*	�֐���		�FZbmlChangeDateFormat()								*/
/*	�@�\�T�v	�FDB�f�[�^�̓��t��YYYY-MM-DD��YYYYMMDD�ɕϊ�����		*/
/*	����		�F														*/
/*	 ��P����	�Fchar    *pStrOut	�ϊ����t���i�[����o�b�t�@			*/
/*	 ��Q����	�Fchar    *pStrIn		�ϊ������t						*/
/*	�o��		�F														*/
/*   �Ȃ�																*/
/************************************************************************/
void ZbmlChangeDateFormat(char* pStrOut, char* pStrIn)
{
	pStrOut[0] = '\0';
	if( pStrOut == NULL || pStrIn == NULL ){
		return;
	}
	if( pStrIn[0] != '\0' ){
		sprintf(pStrOut, "%4.4s%2.2s%2.2s", pStrIn, &pStrIn[5], &pStrIn[8] );
	}

    return;
}

/************************************************************************/
/*	�֐���		�FZbmlChangeTime()										*/
/*	�@�\�T�v	�F���M�f�[�^�̎���HHMMSS��HH:MM:SS�ɕϊ�����			*/
/*	����		�F														*/
/*	 ��P����	�Fchar	*pStrOut	�ϊ����Ԃ��i�[����o�b�t�@			*/
/*	 ��Q����	�Fchar	*pStrIn		�ϊ�������							*/
/*	 ��R����	�Fint	iStrSize	�ϊ������Ԃ̃T�C�Y					*/
/*	�o��		�F														*/
/*   �Ȃ�																*/
/************************************************************************/
void ZbmlChangeTime(char* pStrOut, char* pStrIn, int iStrSize)
{
    char			buff[20];
	void ifInfocpy();

	memset( pStrOut, '\0', iStrSize );
	if( pStrOut == NULL || pStrIn == NULL || iStrSize < 6 ){
		return;
	}
	ifInfocpy(buff, pStrIn, iStrSize+1);
	if( buff[0] != '\0' ){
		sprintf(pStrOut, "%2.2s:%2.2s:%2.2s", buff, &buff[2], &buff[4] );
	}

    return;
}

/************************************************************************/
/*	�֐���		�FZbmlInfoCpy()											*/
/*	�@�\�T�v	�F�w��o�C�g���R�s�[�����i�s�v�ȃX�y�[�X���폜���A		*/
/* 				  '\0'��t������										*/
/*	����		�F														*/
/*	 ��P����	�Fchar*	pStrOut		�R�s�[��o�b�t�@					*/
/*	 ��Q����	�Fchar	*pStrIn		�R�s�[���o�b�t�@					*/
/*	 ��R����	�Fint	Num			�R�s�[����o�C�g��					*/
/*	�o��		�F														*/
/*   �Ȃ�																*/
/************************************************************************/
void ZbmlInfoCpy(char* pStrOut, char *pStrIn, int Num)
{
	int		i;
	BOOL	bSpace;

	memset( pStrOut, '\0', Num );
	bSpace = FALSE;	
	for( i = Num-2 ;i >= 0; i-- ){
		//�]���ȃX�y�[�X���J�b�g
		if( pStrIn[i] == ' ' && bSpace == FALSE ){	
			pStrOut[i] = '\0';
			continue;
		}
		bSpace = TRUE;	
		pStrOut[i] = pStrIn[i];
	}
	return;
}

/************************************************************************/
/*	�֐���		�FZbmlSetSpace()										*/
/*	�@�\�T�v	�F�w��o�C�g���X�y�[�X�l�ߏ���                          */
/*	����		�F														*/
/*	 ��P����	�Fchar*	pStrOut		�Z�b�g����o�b�t�@					*/
/*	 ��Q����	�Fint	Num			�Z�b�g����o�C�g��					*/
/*	�o��		�F														*/
/*   �Ȃ�																*/
/************************************************************************/
DLLEXPORT void bmlSetSpace(char* pStrOut, int Num)
{
	memset( pStrOut, '\0', Num );
	memset( pStrOut, ' ', Num - 1 );
}

/** End of File *********************************************************/
