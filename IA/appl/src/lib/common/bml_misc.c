/************************************************************************/
/*																		*/
/*		�a�l�k�l���������V�X�e��										*/
/*																		*/
/*		�V�X�e�����F������												*/
/*		�t�@�C�����Fbml_misc.c											*/
/*		�T�v      �F���̑����ʊ֐�										*/
/************************************************************************/

/************************************************************************/
/*	Ver.	���t			���O			�C�����e					*/
/* --------------------------------------------------------------------	*/
/*	1.00	2005/06/14		E.Osada			Create						*/
/*			2006/01/31		E.Osada			bmlStrCpy()�ǉ�				*/
/************************************************************************/

/************************************************************************/
/*	�C���N���[�h��`													*/
/************************************************************************/
#include <stdlib.h>
#include <memory.h>
#include <bml_misc.h>

/************************************************************************/
/*	�֐���		�FZbmlMalloc()											*/
/*	�@�\�T�v	�F�w�肳�ꂽ�T�C�Y���̗̈���m�ۂ���					*/
/*	����																*/
/*	 ��P����   :�@size_t size   �̈�m�ۃT�C�Y							*/
/*	�o�� 																*/
/*	 �m�ۂ����̈�̃A�h���X��Ԃ�										*/
/************************************************************************/
void * ZbmlMalloc( size_t size )
{
		return( malloc( size ) );
}

/************************************************************************/
/*	�֐���		�FZbmlMalloc()											*/
/*	�@�\�T�v	�F�w�肳�ꂽ�T�C�Y���̗̈���w�肳�ꂽ�����m�ۂ���	*/
/*	����																*/
/*	 ��P����	�Fsize_t count	�̈�m�ی�							*/
/*	 ��Q����	�Fsize_t size	�̈�m�ۃT�C�Y							*/
/*	�o�� 																*/
/*	 �m�ۂ����̈�̃A�h���X��Ԃ�										*/
/************************************************************************/
void * ZbmlCalloc( size_t count,size_t size )
{
		return( calloc( count,size ) );
}

/************************************************************************/
/*	�֐���		�FZbmlRealloc()											*/
/*	�@�\�T�v	�F�w�肳�ꂽ�̈���w��T�C�Y�ɕύX�m�ۂ���				*/
/*	����																*/
/*	 ��P����	�Fvoid*		area   �̈�|�C���^							*/
/*	 ��Q����	�Fsize_t	size   �̈�m�ۃT�C�Y						*/
/*	�o��																*/
/*	 �m�ۂ����̈�̃A�h���X��Ԃ�										*/
/************************************************************************/
void * ZbmlRealloc( void *area, size_t size )
{
		return( realloc( area, size ) );
}

/************************************************************************/
/*	�֐���		�FZbmlFree()											*/
/*	�@�\�T�v	�F�w�肳�ꂽ�̈���������								*/
/*	����																*/
/*	 ��P����   :�@void* area   �̈�|�C���^							*/
/*	�o��																*/
/*	 �Ȃ�																*/
/************************************************************************/
void ZbmlFree( void *area )
{
		free( area );
		return;
}

/************************************************************************/
/*	�S�p�����p�ϊ��֐��p�̂��������������z���`						*/
/************************************************************************/
#define	SPACE1	0x81
#define	SPACE2	0x40
#define	YEN1	0x81
#define	YEN2	0x8f
#define	A_YEN	0x5c
#define	OPAR1	0x81
#define	OPAR2	0x69
#define	A_OPAR	0x28
#define	CPAR1	0x81
#define	CPAR2	0x6a
#define	A_CPAR	0x29

typedef unsigned char uc;

uc ztable1[256] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0x00 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0x10 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0x20 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0x30 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0x20, 0xff, 0xff, 0x2c, 0x2e, 0xff, 0x3a, 0x3b,	/* 0x40 */
	0x3f, 0x21, 0xff, 0xff, 0xff, 0xff, 0xff, 0x5e,
	0x7e, 0x5f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0x50 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x2f, 0x5c,
	0xff, 0xff, 0x7c, 0xff, 0xff, 0x60, 0x27, 0xff,	/* 0x60 */
	0x22, 0xff, 0xff, 0xff, 0xff, 0x5b, 0x5d, 0x7b,
	0x7d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0x70 */
	0xff, 0xff, 0xff, 0x2b, 0x2d, 0xff, 0xff, 0xff,
	0xff, 0x3d, 0xff, 0x3c, 0x3e, 0xff, 0xff, 0xff,	/* 0x80 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0x24, 0xff, 0xff, 0x25, 0x23, 0x26, 0x2a, 0x40,	/* 0x90 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0xa0 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0xb0 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0xc0 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0xd0 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0xe0 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0xf0 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};

uc ztable2[256] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0x00 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0x10 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0x20 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0x30 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0x40 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x30,
	0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,	/* 0x50 */
	0x39, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,	/* 0x60 */
	0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50,
	0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,	/* 0x70 */
	0x59, 0x5a, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,	/* 0x80 */
	0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
	0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,	/* 0x90 */
	0x78, 0x79, 0x7a, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0xa0 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0xb0 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0xc0 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0xd0 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0xe0 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0xf0 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};
#define	isAscii(c)	(((c) >= 0x20 && (c) <= 0x7e) ? 1 : 0)

/************************************************************************/
/*	�֐���		�FbmlZen2Han()											*/
/*	�@�\�T�v	�F��������̑S�p�����𔼊p�����ɕϊ�����				*/
/*                �ϊ��ł��Ȃ������̓X�L�b�v����						*/
/*	����																*/
/*	 ��P����	�Fchar* psString   �ϊ��Ώە�����						*/
/*	 ��Q����	�Fint nMasLen      ������o�b�t�@�i�[�ő咷				*/
/*	�o��																*/
/*	 �ϊ����pString��Ԃ�												*/
/************************************************************************/
char* ZbmlZen2Han( char* psString, int nMaxLen )
{
	char	sBuf[4096] = "";
	char*	pDest = sBuf;
	char*	p = psString;
	uc		*ztable;

	if(!psString) {
		return NULL;
	}

	while(*p){
		register short int	c1;
		register short int	c2;

		c1 = *p & 0xff;
		if(isAscii(c1)){		/* ascii */
			memcpy(pDest++, p++, 1);
			continue;
		}
		if(c1 != 0x81 && c1 != 0x82){	/* not a target */
			memcpy(pDest, p, 2);
			p += 2;
			pDest += 2;
			continue;
		}
		c2 = *(++p) & 0xff;
		if(c1 == YEN1 && c2 == YEN2){ /* convert YEN */
			*(pDest++) = A_YEN;
			p++;
			continue;
		}
		if(c1 == OPAR1 && c2 == OPAR2){ /* convert PARENTHESIS */
			*(pDest++) = A_OPAR;
			p++;
			continue;
		}
		if(c1 == CPAR1 && c2 == CPAR2){ /* convert PARENTHESIS */
			*(pDest++) = A_CPAR;
			p++;
			continue;
		}
		if(c1 == 0x81)
			ztable = ztable1;
		else
			ztable = ztable2;
		if(ztable[c2] == 0xff){
			*(pDest++) = (char)c1;
			*(pDest++) = (char)c2;
		}
		else
			*(pDest++) = ztable[c2];
		p++;
	}

	nMaxLen -= nMaxLen % 2;
	strncpy( psString, sBuf, nMaxLen );

	return psString;
}
/************************************************************************/
/*	�֐���		�FZbmlStrCpy()											*/
/*	�@�\�T�v	�F�w��o�C�g����������R�s�[����(���X�y�[�X�l��)		*/
/*	����																*/
/*	 ��P����   :�@char*	pStrOut		������̃R�s�[��				*/
/*	 ��Q����   :�@char*	pStrIN		������̃R�s�[��				*/
/*	 ��R����   :�@int		Num			������̃R�s�[�o�C�g��			*/
/*	�o��																*/
/*	 ����																*/
/************************************************************************/
void ZbmlStrCpy(char* pStrOut, char *pStrIn, int Num)
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
/*	�֐���		�FZbmlChgDBDate()										*/
/*	�@�\�T�v	�F�f�[�^�̓��tYYYYMMDD��YYYY-MM-DD�ɕϊ�����			*/
/*	����																*/
/*	 ��P����   :�@char    *pStrOut		�ϊ����t���i�[����o�b�t�@		*/
/*	 ��Q����   :�@char    *pStrIn		�ϊ������t						*/
/*	 ��R����   :�@int		iStrSize	�ϊ������t�̃T�C�Y				*/
/*	�o��																*/
/*	 ����																*/
/************************************************************************/
void ZbmlChgDBDate(char* pStrOut, char* pStrIn, int iStrSize)
{
    char			buff[20];

	memset( pStrOut, '\0', iStrSize );
	if( pStrOut == NULL || pStrIn == NULL || iStrSize < 8 ){
		return;
	}
	if( memcmp( pStrIn,"00000000",8 ) == 0 ){
		strcpy( pStrOut, "1000-01-01" );
		return;
	}
	ZbmlInfocpy(buff, pStrIn, iStrSize+1);
	if( buff[0] != '\0' && buff[0] != ' ' ){
		sprintf(pStrOut, "%4.4s-%2.2s-%2.2s", buff, &buff[4], &buff[6] );
	}else{
		strcpy( pStrOut, "1000-01-01" );
	}

    return;
}

/************************************************************************/
/*	�֐���		�FZbmlChgAPDate()									*/
/*	�@�\�T�v	�FDB�f�[�^�̓��t��YYYY-MM-DD��YYYYMMDD�ɕϊ�����		*/
/*	����																*/
/*	 ��P����   :�@char    *pStrOut	�ϊ����t���i�[����o�b�t�@			*/
/*	 ��Q����   :�@char    *pStrIn		�ϊ������t						*/
/*	�o��																*/
/*	 ����																*/
/************************************************************************/
void ZbmlChgAPDate(char* pStrOut, char* pStrIn)
{
	if( pStrOut == NULL || pStrIn == NULL ){
		return;
	}
	pStrOut[0] = '\0';
	if( pStrIn[0] != '\0' ){
		sprintf(pStrOut, "%4.4s%2.2s%2.2s", pStrIn, &pStrIn[5], &pStrIn[8] );
	}

    return;
}

/************************************************************************/
/*	�֐���		�FZbmlChgDBtime()										*/
/*	�@�\�T�v	�F�f�[�^�̎���HHMMSS��HH:MM:SS�ɕϊ�����				*/
/*	����																*/
/*	 ��P����   :�@char    *pStrOut	�ϊ����Ԃ��i�[����o�b�t�@			*/
/*	 ��Q����   :�@char    *pStrIn		�ϊ�������						*/
/*	 ��R����   :�@int		iStrSize	�ϊ������Ԃ̃T�C�Y				*/
/*	�o��																*/
/*	 ����																*/
/************************************************************************/
void ZbmlChgDBTime(char* pStrOut, char* pStrIn, int iStrSize)
{
    char			buff[20];

	memset( pStrOut, '\0', iStrSize );
	if( pStrOut == NULL || pStrIn == NULL || iStrSize < 6 ){
		return;
	}
	if( pStrOut == NULL || pStrIn == NULL ){
		return;
	}
	if( memcmp( pStrIn,"00000000",6 ) == 0 ){
		strcpy( pStrOut, "00:00:01" );
		return;
	}
	ZbmlInfocpy(buff, pStrIn, iStrSize+1);
	if( buff[0] != '\0' ){
		sprintf(pStrOut, "%2.2s:%2.2s:%2.2s", buff, &buff[2], &buff[4] );
	} else {
		strcpy( pStrOut, "00:00:01" );
	}

    return;
}
/************************************************************************/
/*	�֐���		�FZbmlChgAPtime()										*/
/*	�@�\�T�v	�F�f�[�^�̎���HH:MM:SS��HHMMSS�ɕϊ�����				*/
/*	����																*/
/*	 ��P����   :�@char    *pStrOut	�ϊ����Ԃ��i�[����o�b�t�@			*/
/*	 ��Q����   :�@char    *pStrIn		�ϊ�������						*/
/*	�o��																*/
/*	 ����																*/
/************************************************************************/
void ZbmlChgAPTime(char* pStrOut, char* pStrIn)
{
	if( pStrOut == NULL || pStrIn == NULL ){
		return;
	}
	pStrOut[0] = '\0';
	if( pStrIn[0] != '\0' ){
		sprintf(pStrOut, "%2.2s%2.2s%2.2s", pStrIn, &pStrIn[3], &pStrIn[6] );
	}

    return;
}
/************************************************************************/
/*	�֐���		�FZbmlInfocpy()											*/
/*	�@�\�T�v	�F�w��o�C�g���R�s�[����								*/
/*				  (�s�v�ȃX�y�[�X���폜���A'\0'��t������)				*/
/*	����																*/
/*	 ��P����   :�@char* pStrOut	�R�s�[��o�b�t�@					*/
/*	 ��Q����   :�@char *pStrIn	�R�s�[���o�b�t�@						*/
/*	 ��R����   :�@int Num			�R�s�[����o�C�g��					*/
/*	�o��																*/
/*	 ����																*/
/************************************************************************/
void ZbmlInfocpy(char* pStrOut, char *pStrIn, int Num)
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

/** End of File *********************************************************/
