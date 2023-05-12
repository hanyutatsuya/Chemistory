/*****************************************************************************

	SYSTEM NAME:	�P�~�X�g���[
	FILE NAME:		�p�����[�^�[�t�@�C���ǂݍ���
	DATE/Var:		2023/05/11	Ver.1.00
	Edited:			T.Hanyu

*****************************************************************************/

#ifndef	_BML_PARAREAD_H_
#define	_BML_PARAREAD_H_

/*************************************************************************
	define��`
*************************************************************************/

#define		INI_RET_NORMAL		0		// ���^�[���R�[�h
#define		INI_RET_SECNFD		1		// ���^�[���R�[�h
#define		INI_RET_NAMENFD		2		// ���^�[���R�[�h
#define		INI_RET_ERROR		-1		// ���^�[���R�[�h
#define		INI_RET_ENOENT		-2		// ���^�[���R�[�h
#define		INI_RET_EIO			-5		// ���^�[���R�[�h
#define		INI_RET_EACCES		-13		// ���^�[���R�[�h
#define		INI_RET_EISDIR		-21		// ���^�[���R�[�h

#define		INI_LENGTH_MAX	128		// �p�����[�^�̍ő咷

/*************************************************************************
	�e�[�u����`
*************************************************************************/


extern	int		GetIniValue(char *IniPath,char *Section,char *Name,char *Value);

/* end of define */
#endif
