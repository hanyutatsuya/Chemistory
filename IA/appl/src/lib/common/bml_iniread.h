/*****************************************************************************

	SYSTEM NAME:	���a��w�a�@
	FILE NAME:		ini�t�@�C���ǂݍ���
	DATE/Var:		2017/12/07	Ver.1.00
	Edited:			T.Hanyu

*****************************************************************************/

#ifndef	_CMD_INIREAD_H_
#define	_CMD_INIREAD_H_

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
