/*****************************************************************************

	SYSTEM NAME:	�P�~�X�g���[
	FILE NAME:		�I�����C�������p���ʊ֐�
	DATE/Var:		2023/05/11	Ver.1.00
	Edited:			T.Hanyu

*****************************************************************************/

#ifndef	_KNS_COMMON_H_
#define	_KNS_COMMON_H_

#include	"Kekka.h"

/*************************************************************************
	define��`
*************************************************************************/

#define		PARA_RET_NORMAL		0		// ���^�[���R�[�h(Normal)
#define		PARA_RET_NFND		1		// ���^�[���R�[�h(Not Found)
#define		PARA_RET_ERROR		-1		// ���^�[���R�[�h
#define		PARA_RET_ENOENT		-2		// ���^�[���R�[�h
#define		PARA_RET_EIO		-5		// ���^�[���R�[�h
#define		PARA_RET_ENOMEM		-12		// ���^�[���R�[�h
#define		PARA_RET_EACCES		-13		// ���^�[���R�[�h
#define		PARA_RET_EISDIR		-21		// ���^�[���R�[�h

#define		PARA_LENGTH_MAX		128		// �p�����[�^�̍ő咷
#define		KMKTBL_LEN_KMKCD	7
#define		KMKTBL_LEN_VALUE	31
#define		KMKTBL_LEN_HJKKA	24

/*************************************************************************
	�e�[�u����`
*************************************************************************/

typedef	struct	kmktbl	{
	char	kmkcd[KMKTBL_LEN_KMKCD+1];
	char	value[KMKTBL_LEN_VALUE+1];
}	KMKTBL;

/*************************************************************************
	�v���g�^�C�v��`
*************************************************************************/

extern	int		KnsParaInit(char *ParaPath);
extern	int		KnsParaFind(char *Kmkcd,char *Value);
extern	int		KnsParaFree(void);
extern	int		KnsLowDataCheck(Kekka *pKekka,int nKekkaNum);


/* end of define */
#endif
