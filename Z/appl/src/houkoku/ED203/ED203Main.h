/********************************************************************/
/*																	*/
/*		�a�l�k�l���������V�X�e��									*/
/*																	*/
/*		�V�X�e����	�F������V�X�e��								*/
/*		�t�@�C����	�FED203Main.h									*/
/*		�T�v		�F�ً}�񍐃f�[�^�t�@�C���쐬�w�b�_�[�t�@�C��	*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	�쐬��			���O			�C�����e				*/
/* ---------------------------------------------------------------- */
/*  1.00	2006/03/13		H.Suyama		Create					*/
/********************************************************************/
#ifndef _ED203Main_h
#define _ED203Main_h

/********************************************************************/
/*  �C���N���[�h�錾												*/
/********************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <dirent.h>
#include <sys/shm.h>
#include "bml_base.h"
#include "ED203Kekka.h"

/******************************************************************************/
/* Define��`																  */
/******************************************************************************/
#define CHAR_KANJI		  0x80
#define iskanji(c)  ((c) & CHAR_KANJI)

#define MYAPP_APP_NAME		  "ED203"

//  �����X�e�[�^�X�R�[�h��`
typedef enum {
	ED203_STSCODE_NORMAL,
	ED203_STSCODE_ERR_USAGE,
	ED203_STSCODE_ERR_PRM_FILE,
	ED203_STSCODE_ERR_PRM_GET,
	ED203_STSCODE_ERR_SHM_AT,
	ED203_STSCODE_ERR_SHM_DT,
	ED203_STSCODE_ERR_SHM_DEL,
	ED203_STSCODE_ERR_SHM_GET,
	ED203_STSCODE_ERR_DIR,
	ED203_STSCODE_ERR_FR_FILE
} ED203_STSCODE;

//  ���L�������T�C�Y
#define ED203_SHM_SIZE			sizeof ( int )

#define ED203_LEN_DATESHORT		8	// YYYYMMDD�̒���
#define ED203_LEN_NOITEM		11	// ����No���ڂ̒���
#define ED203_LEN_SRCNO			6	// ����No�̗L������
#define ED203_LEN_FILEID		12	// ���M�t�@�C��ID�iYYYYMMDD9999�j�̒���
#define ED203_LEN_FILESEQNO		4	// ���M�t�@�C��ID��SeqNo�i9999�j�̒���

#define ED203_POS_SRCNO			3	// �˗�No�A����No�̃u���b�N1�̊J�n�ʒu

//  �p�����[�^�t�@�C���L�[������
#define ED203_PRM_DBNAME		"DBNAME"		// �f�[�^�x�[�X�ڑ���
#define ED203_PRM_DBUSER		"DBUSER"		// ���O�C�����[�U
#define ED203_PRM_DBPAWD		"DBPAWD"		// ���O�C���p�X���[�h
#define ED203_PRM_DIR_DATAFILE	"DIR_DATAFILE"	// �񍐃f�[�^�t�@�C���o�̓f�B���N�g��
#define ED203_PRM_SLEEP_SEC		"SLEEP_SEC"		// �X���[�v���ԁi�b�j
#define ED203_PRM_SHM_KEY		"SHM_KEY"		// ���L�������L�[
#define ED203_PRM_FILE_DBG		"FILE_DBG_NSME"	// �f�o�b�O
#define ED203_PRM_FILE_TR		"FILE_TR_NAME"	// �g���[�X
#define ED203_PRM_FILE_ACS		"FILE_ACS_NAME"	// �A�N�Z�X
#define ED203_PRM_FILE_ERR		"FILE_ERR_NAME"	// �G���[
#define ED203_PRM_UP_ID			"UPDATE_ID"		// �X�V��ID
#define ED203_PRM_UP_NM			"UPDATE_NM"		// �X�V��
#define ED203_PRM_PROC_MD		"PROC_MD"		// ���s���[�h

//�f�[�^���ʎq
#define ED203_FILE_LINEFEED		'\n'
#define ED203_REC_LOOP_MAX		6
#define ED203_DATA_CHAR0		'0'
#define ED203_DATA_SPACE		' '
#define ED203_DATA_ASTERISK		'*'
#define ED203_DATA_STR00		"00"

#define ED203_DB_HKKJKFLG_CHUU		"1 "
#define ED203_DB_KNSFLG_HORYU		'H'
#define ED203_DB_KNSFLG_DONE		'E'
#define ED203_DB_KKASSFLG_MAX		'9'

#define MYAPP_LOG_ERRCODE_NON		"00000000"
#define MYAPP_LOG_ERRCODE_APP		"010"
#define MYAPP_LOG_ERRCODE_DB		"020"
#define MYAPP_LOG_ERRCODE_ETC		"0Z0"

// �f�t�H���gINI�t�@�C��
#define MYAPP_INIFILE "./ED203.ini"
// ���O�t�@�C��INI�t�@�C��
#define MYAPP_LOGINIFILE "./ED203_LOG.ini"

/******************************************************************************/
/* �\���̒�`																  */
/******************************************************************************/
// �񍐃f�[�^�\����
typedef struct {
	char	cUTKYMD[8];		// �a�l�k��t�N����
							// [YYYYMMDD]�ɕϊ����Đݒ�
	char	cKNTNO[6];		// ���̂m���D
							// ������11�������̂悤�ɕϊ�
							// (�ϊ��O)[1][2][3][4][5][6][7][8][9][10][11]
							// (�ϊ���)[4][5][6][7][8][9]
	char	cFILLER1[5];	// FILLER
	char	cOYAKMKCD[4];	// �e���ڃR�[�h
							// �E����4����ݒ�
	char	cKMKCD[4];		// ���ڃR�[�h
							// �E����4����ݒ�
	char	cWSCD[3];		// �v�r�R�[�h�i�T���v�����O�R�[�h�j
							// �E����3����ݒ�
	char	cWSSEQ[4];		// �v�r�r�d�p�i�����r�d�p�j
							// ���l�𕶎���ϊ���A�E����4����ݒ�iw�w�w�w�w�w�w�w��Ȃ��j
	char	cKNSKKA[6];		// ��������
							// �������ʂPor�������ʂQ�i�������ʂP�D��j
							// �������ʂP�F�E����6����ݒ�iw�w�w�w�w�w�w�w�����A�����_�폜�j
							// �������ʂQ�F�������ʋ敪='0'��'*'+��2���ڂ���6���ڂ܂�
							// �@�@�@�@�@�@�ȊO��������6����ݒ�i2�o�C�g�����ɒ��ӂ���j
	char	cKKACMT[3];		// ���ʃR�����g
							// �E����3����ݒ�
	char	cIJKBN;			// �ُ�l�}�[�N�敪
							// �ُ�l�敪�i�j�A���A�s���j��'4','5','6'�ȊO�ł����'*'
	char	cFILLER2[6];	// FILLER
	char	cLF;			// LF
} ED203Rec;

// �v���O�������\����
typedef struct {
	BMLPRM	*bp;
	char	*pcFileNamePRM;
	int		shm_Id;					// ���L������ID
	key_t	shm_Key;				// ���L�������L�[
	int		iSleepSec;				// �X���[�v���ԁi�b�j
	char	cDBName[1024];			// �f�[�^�x�[�X�ڑ���
	char	cDBUser[1024];			// ���O�C�����[�U
	char	cDBPawd[1024];			// ���O�C���p�X���[�h
	char	cDirDataFile[1024];		// �񍐃f�[�^�t�@�C���o�̓f�B���N�g��
	char	cDebugLogName[1024];	// �f�o�b�O���O�t�@�C����
	char	cTraceLogName[1024];	// �g���[�X���O�t�@�C����
	char	cAccessLogName[1024];	// �A�N�Z�X���O�t�@�C����
	char	cErrorLogName[1024];	// �G���[���O�t�@�C����
	int		proc_mode;				// �������[�h	0�F�ߓn��   1�F������
	char	cUpdateId[128];			// �X�V��ID
	char	cUpdateName[128];		// �X�V��
	char	cLogName[128];			// ���O
} ED203Env;

/******************************************************************************/
/* �O���[�o���錾															  */
/******************************************************************************/

/******************************************************************************/
/* �v���g�^�C�v�錾															  */
/******************************************************************************/
void ED203ConvTimestamp(ULONG ulTm, char *pDest);
int ED203ConvNumber(char *pDest, char *pSrc);
int ED203CopyFromLeft(char *pDest, char *pSrc, int iSize, BOOL bMbFlg);
int ED203CopyFromRight(char *pDest, char *pSrc, int iSize, BOOL bMbFlg);

int initFunction( int argc, char *argv[], ED203Env *pEnv );
int mainFunction( ED203Env *pEnv );
void endFunction( ED203Env *pEnv );
int ED203MakeData(Kekka *pKekka, ED203Rec *pED203Rec);
int ED203DataFileFilter(struct dirent *pDirEnt);
int ED203HulftFileFilter(struct dirent *pDirEnt);
int ED203WriteFile(FILE *fp, ED203Rec *pED203Rec, int iRecCnt);
int ED203CreateFile(ED203Env *pEnv, Kekka *pKekkaArrayOut, int iKekkaNumOut, int *piHkkssknsu, int *piHkkhrysu, char *pFileName);

//  ���L����������֐�
static  int sFncShmCrt ( ED203Env * );
static  int sFncShmGet ( ED203Env * , int *);
static  int sFncShmDel ( ED203Env * );
//  �g���[�X�p
static  void	_sFncEnvDip ( ED203Env * );
//���O�֐�
void sFncPutLog( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... );
#endif

