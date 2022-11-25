/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FLD101.h                                                      */
/* �@�T�@�@�@�v�F�p�����[�^�擾�w�b�_                                         */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  x.xx     2006/01/15     �F��O�K       �V�K�쐬                           */
/*  x.xx     2006/12/15     YOON	       DEFINE�ǉ�                         */
/*  x.xx     2008/02/04     moriya	       �V�t�����e�B�A�Ή�                 */
/******************************************************************************/
#ifndef _LD101_h
#define _LD101_h
/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <sys/shm.h>
#include "bmlprm.h"
#include "bmllog.h"

/******************************************************************************/
/* Define��`                                                                */
/******************************************************************************/
#define	MYAPP_APP_NAME			"LD101"
#define	MYAPP_APP_NAME_JP		"LD101"
#define	MYAPP_LOGINIFILE		"LD101_LOG.ini"

//  �����X�e�[�^�X�R�[�h��`
typedef enum {
	MYAPP_STSCODE_NML,
	MYAPP_STSCODE_ERR_USEGE,
	MYAPP_STSCODE_ERR_PRM,
	MYAPP_STSCODE_ERR_SHM,
	MYAPP_STSCODE_ERR_DIR,
	MYAPP_STSCODE_ERR_FILE,
	MYAPP_STSCODE_ERR_DB,
	MYAPP_STSCODE_NML_START,
	MYAPP_STSCODE_NML_END
} MYAPP_STSCODE ;

//	�G���[�R�[�h��`
#define	MYAPP_LOG_ERRCODE_NON		"00000000"
#define	MYAPP_LOG_ERRCODE_APP		"010"
#define	MYAPP_LOG_ERRCODE_DB		"020"
#define	MYAPP_LOG_ERRCODE_ETC		"0Z0"

//	�G���[�R�[�h�ڍ�
#define MYAPP_SQL_DEADLOCK		-911
#define MYAPP_SQL_DUPLICATION		-803

//	�p�����[�^������
#define	MYAPP_PRM_SHM_KEY		"SHM_KEY"
#define	MYAPP_PRM_SLEEP_SEC		"SLEEP_SEC"
#define	MYAPP_PRM_DB_NAME		"DB_NAME"
#define	MYAPP_PRM_DB_USER		"DB_USER"
#define	MYAPP_PRM_DB_PASSWD		"DB_PASSWD"
#define MYAPP_PRM_OUTPUT_DIR		"OUTPUT_DIR"
#define MYAPP_PRM_OUTPUT_FILE		"OUTPUT_FILE"
#define MYAPP_PRM_SEND_SHELL		"SEND_SHELL"
#define	MYAPP_PRM_TRG_FILE		"TRG_FILE"
#define	MYAPP_PRM_DATE_RANGE		"DATE_RANGE"
#define MYAPP_PRM_AGE_HI		"AGE_HI"
#define MYAPP_PRM_AGE_LOW		"AGE_LOW"
#define MYAPP_PRM_SC_HI			"SC_HI"
#define MYAPP_PRM_SC_LOW		"SC_LOW"
#define MYAPP_PRM_TJ_HI			"TJ_HI"
#define MYAPP_PRM_TJ_LOW		"TJ_LOW"

//	�f�B���N�g���i�[�T�C�Y
#define	MYAPP_PATH_SIZE			(1024)

#define MYAPP_LEN_FNCNM			32
#define MYAPP_LEN_MSG			3072


//	���L�������T�C�Y
#define	MYAPP_SHM_SIZE			sizeof ( int )

//	�����`�F�b�N�t���O��`
#define MYAPP_ZOK_NOT_CHK		"0"	// �����`�F�b�N�ΏۊO
#define MYAPP_ZOK_CHK			"1"	// �����`�F�b�N�Ώ�
#define MYAPP_ZOK_ERR			"2"	// �����`�F�b�N�G���[
#define MYAPP_ZOK_NG			"3"	// �����`�F�b�N�G���[(�ُ�l)

#define MYAPP_SBTKBN_MALE		"0"	// ���ʋ敪��`(�j)
#define MYAPP_SBTKBN_FEMALE		"1"	// ���ʋ敪��`(��)
#define MYAPP_SBTKBN_UNKNOWN		"9"	// ���ʋ敪��`(�s��)

#define MYAPP_AGEKBN_YEAR		"Y"	// �N��敪��`(�N)
#define MYAPP_AGEKBN_MONTH		"M"	// �N��敪��`(��)
#define MYAPP_AGEKBN_WEEK		"W"	// �N��敪��`(�T)
#define MYAPP_AGEKBN_DAY		"D"	// �N��敪��`(��)

#define MYAPP_TJTNI_KGRAM		"0"	// �̏d�P��(kg)
#define MYAPP_TJTNI_GRAM		"1"	// �̏d�P��(g)

//	�t�@�C���t�B�[���h�p��`
#define MYAPP_SPACE_HALF		' '
#define MYAPP_HYPHEN_HALF		'-'
#define MYAPP_SPACE_FULL		"�@"
#define MYAPP_HYPHEN_FULL		"�|"
#define MYAPP_MARK_MALE			"�j"
#define MYAPP_MARK_FEMALE		"��"
#define MYAPP_MARK_YEAR			"�΁@"
#define MYAPP_MARK_MONTH		"����"
#define MYAPP_MARK_WEEK			"�T"
#define MYAPP_MARK_DAY			"���@"
#define MYAPP_MARK_KGRAM		"KG"
#define MYAPP_MARK_GRAM			"G "
#define MYAPP_MARK_KBN_ERR		"������"
#define MYAPP_MARK_KBN_NG		"�m�F�@"
#define MYAPP_MARK_ERR			'*'
#define MYAPP_MARK_NG			'?'

/******************************************************************************/
/* �\���̒�`                                                                 */
/******************************************************************************/
// �v���O�������\����
struct	appEnv {
	BMLPRM	*bp	;
	char	*pcFielNamePRM ;
	int	 shm_Id ;
	key_t	 shm_Key ;
	int	 sleep_Sec ;
	char	 cDb_Name[32+1] ; 
	char	 cDb_User[32+1] ; 
	char	 cDb_Passwd[32+1] ;
	char	 cOutputDir[MYAPP_PATH_SIZE] ;
	char	 cOutputFile[MYAPP_PATH_SIZE] ;
	char	 cSendShell[MYAPP_PATH_SIZE] ;
	char	 cTrgFile[MYAPP_PATH_SIZE] ;
	int	 DateRange ;
	int	 AgeHi ;
	int	 AgeLow ;
	double	 ScHi ;
	double	 ScLow ;
	double	 TjHi ;
	double	 TjLow ;
} pAppEnv ;

//	�V�X�e���Ǘ��}�X�^���\����
typedef struct  _stSYSKNR 
{
        char    kjnsriymd[10+1];	// ������N����
        char    iriendflg[1+1];		// �˗�END�t���O
        char    bchendflg[1+1];		// ����END�t���O
        char    unyflg[1+1];		// �^�p�t���O
} my_stSYSKNR ;

typedef struct _stCHKZOK
{
	char	utkymd[10+1];		// 1  �a�l�k��t�N����
	char	irino[11+1];		// 2  �˗����m��
	char	knsgrp[16+1];		// 3  �����O���[�v
	char	kmkcd[7+1];		// 4  ���ڃR�[�h
	char	kmknmj[46+1];		// 5  ���ږ�
	char	sstcd[7+1];		// 6  �{�݃R�[�h
	char	sstssnmj[40+1];		// 7  �{�ݖ���
	char	knjnmn[60+1];		// 8  ���Җ�
	char	krtno[40+1];		// 9  �J���e�m�n
	char	sc[5+1];		// 10 �g��
	char	scflg[1+1];		// 11 �g�� �`�F�b�N�t���O
	char	tj[5+1];		// 12 �̏d
	char	tjflg[1+1];		// 13 �̏d  �`�F�b�N�t���O
	char	tjtni[1+1];		// 14 �̏d�敪
	char	tjtniflg[1+1];		// 15 �̏d�敪�`�F�b�N�t���O
	char	sbtkbn[1+1];		// 16 ���ʋ敪
	char	sbtkbnflg[1+1];		// 17 ���ʋ敪�`�F�b�N�t���O
	char	age[3+1];		// 18 �N��
	char	ageflg[1+1];		// 19 �N��`�F�b�N�t���O
	char	agekbn[1+1];		// 20 �N��敪
	char	agekbnflg[1+1];		// 21 �N��敪�`�F�b�N�t���O
} my_stCHKZOK ;

/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/

/******************************************************************************/
/* �v���g�^�C�v�錾                                                           */
/******************************************************************************/
void	sFncPutLog ( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... )  ;
int	sFncSelSysKnr ( my_stSYSKNR* ) ;
int	sFncSelChkZok( char *, my_stCHKZOK **, int * );
int	InsHkHrIrai( my_stCHKZOK * ) ;

#endif
/** End of File ***************************************************************/
