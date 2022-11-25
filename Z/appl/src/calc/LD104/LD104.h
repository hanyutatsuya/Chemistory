/************************************************************************/
/*									*/
/*	�a�l�k�l���������V�X�e��					*/
/*									*/
/*	�V�X�e����	�F������V�X�e��				*/
/*	�t�@�C����	�FLD104.h					*/
/*	�T�v		�F�񍐃f�[�^�t�@�C���쐬�w�b�_�[�t�@�C��	*/
/*									*/
/************************************************************************/

/************************************************************************/
/*  Ver.	�쐬��		���O		�C�����e		*/
/* -------------------------------------------------------------------- */
/*  1.00	2019/12/27	BML.inc		Create			*/
/************************************************************************/
#ifndef _LD104_h
#define _LD104_h

/************************************************************************/
/*  �C���N���[�h�錾							*/
/************************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <dirent.h>
#include <sys/shm.h>
#include "bml_base.h"
#include "LD104Sysknrmst.h"
#include "LD104GetKekka.h"

/************************************************************************/
/* Define��`								*/
/************************************************************************/
#define CHAR_KANJI		  0x80
#define iskanji(c)  ((c) & CHAR_KANJI)

#define MYAPP_APP_NAME		  "LD104"

//  �����X�e�[�^�X�R�[�h��`
typedef enum {
	LD104_STSCODE_NORMAL,
	LD104_STSCODE_ERR_USAGE,
	LD104_STSCODE_ERR_PRM_FILE,
	LD104_STSCODE_ERR_PRM_GET,
	LD104_STSCODE_ERR_SHM_AT,
	LD104_STSCODE_ERR_SHM_DT,
	LD104_STSCODE_ERR_SHM_DEL,
	LD104_STSCODE_ERR_SHM_GET,
	LD104_STSCODE_ERR_DIR,
	LD104_STSCODE_ERR_FR_FILE
} LD104_STSCODE;

//  ���L�������T�C�Y
#define LD104_SHM_SIZE			sizeof ( int )
#define LD104_SIZE_BUFF			1024	// �f�[�^�����p�o�b�t�@�T�C�Y

#define LD104_LEN_DATETIME		14	// YYYYMMDDhhmmss
#define LD104_LEN_NOITEM		11	// �˗�No�A����No���ڂ̒���
#define LD104_LEN_SRCNO1		3	// �˗�No�A����No�̃u���b�N1�̒���
#define LD104_LEN_SRCNO2		6	// �˗�No�A����No�̃u���b�N2�̒���

#define LD104_POS_SRCNO1		2	// �˗�No�A����No�̃u���b�N1�̊J�n�ʒu
#define LD104_POS_SRCNO2		5	// �˗�No�A����No�̃u���b�N2�̊J�n�ʒu
#define LD104_POS_DESTNO1		0	// �˗�No�A����No�̕ϊ���̃u���b�N1�̊J�n�ʒu
#define LD104_POS_DESTNO2		3	// �˗�No�A����No��"00"�̊J�n�ʒu
#define LD104_POS_DESTNO3		5	// �˗�No�A����No�̕ϊ���̃u���b�N1�̊J�n�ʒu

//  �p�����[�^�t�@�C���L�[������
#define LD104_PRM_DBNAME		"DBNAME"	// �f�[�^�x�[�X�ڑ���
#define LD104_PRM_DBUSER		"DBUSER"	// ���O�C�����[�U
#define LD104_PRM_DBPAWD		"DBPAWD"	// ���O�C���p�X���[�h
#define LD104_PRM_DIR_DATAFILE		"DIR_DATAFILE"	// �v���f�[�^�t�@�C���o�̓f�B���N�g��
#define LD104_PRM_DIR_SEND		"DIR_SEND"	// �f�[�^�t�@�C�����M�f�B���N�g��
#define LD104_PRM_DATAFLOWID		"DATAFLOWID"    // �f�[�^�t���[�h�c
#define LD104_PRM_SENDID_MOTO		"SENDID_MOTO"   // ���M���h�c
#define LD104_PRM_SENDID_SAKI		"SENDID_SAKI"   // ���M��h�c
#define LD104_PRM_SLEEP_MIN		"SLEEP_MIN"	// �X���[�v���ԁi���j
#define LD104_PRM_DATE_RANGE		"DATE_RANGE"	// �v���J�[�h�o�͑Ώۊ���
#define LD104_PRM_SHM_KEY		"SHM_KEY"	// ���L�������L�[
#define LD104_PRM_FILE_DBG		"FILE_DBG_NSME"	// �f�o�b�O
#define LD104_PRM_FILE_TR		"FILE_TR_NAME"	// �g���[�X
#define LD104_PRM_FILE_ACS		"FILE_ACS_NAME"	// �A�N�Z�X
#define LD104_PRM_FILE_ERR		"FILE_ERR_NAME"	// �G���[

//�f�[�^���ʎq
#define LD104_FILEEXT_DATA		".kka"
#define LD104_FILEEXT_TEMP		".tmp"
#define LD104_REC_LOOP_MAX		6
#define LD104_DATA_CHAR0		'0'
#define LD104_DATA_SPACE		' '
#define LD104_DATA_STR00		"00"

#define MYAPP_LOG_ERRCODE_NON		"00000000"
#define MYAPP_LOG_ERRCODE_APP		"010"
#define MYAPP_LOG_ERRCODE_DB		"020"
#define MYAPP_LOG_ERRCODE_ETC		"0Z0"

// �f�t�H���gINI�t�@�C��
#define MYAPP_INIFILE "$HOME/bin/LD104.ini"
// ���O�t�@�C��INI�t�@�C��
#define MYAPP_LOGINIFILE "$HOME/bin/LD104_LOG.ini"

/************************************************************************/
/* �\���̒�`								*/
/************************************************************************/
// �񍐃f�[�^�\����
typedef struct {
	char	c_sbt[3];		// ں��ގ��ʎq([R1]�Œ�)
	char	c_utkymd[8];		// �a�l�k��t�N���� [YYYYMMDD]�ɕϊ����Đݒ�
	char	c_irino[11];		// �˗����m���D������11�������̂悤�ɕϊ�
					// (�ϊ��O)[1][2][3][4][5][6][7][8][9][10][11]
					// (�ϊ���)[3][4][5] 0  0 [6][7][8][9][10][11]
	char	c_kmkcd[7];		// ���ڃR�[�h
	char	c_filler[994];		// FILLER
	char	c_kaigyo[1];		// ���s����
} LD104Rec;

// �w�b�_�[���
typedef struct	Z00SJHD {		// ����Mͯ�ް(S-JIS�j 1024byte
	char	c_sbt[2];		// ں��ގ��ʎq([HD]�Œ�)
	char	c_sosinsaki[8];		// ���M��
	char	c_sosinmoto[8];		// ���M��
	char	c_opedate[8];  		// ���M�������N����
	char	c_tuban[4];    	        // �ʔ�
	char	c_dflow[10];		// �ް��۰ID
	char	c_param1[128];		// ���Ұ�1
	char	c_param2[128];		// ���Ұ�2
	char	c_yobi[216];		// �\��
	char	c_filler[511];		// FILLER
	char	c_kaigyo[1];		// ���s����
} LD104Header;

typedef struct	Z01SJTR {		// ����M�ڰװ(S-JIS�j 1024byte
	char	c_sbt[2];		// ں��ގ��ʎq([TR]�Œ�)
	char	c_sosinsaki[8];		// ���M��
	char	c_sosinmoto[8];		// ���M��
	char	c_opedate[8];		// ���M�������N����
	char	c_tuban[4];		// �ʔ�
	char	c_dflow[10];		// �ް��۰ID
	char	c_reccnt[8];		// ����ں��ތ���
	char	c_reccnt01[8];		// �_��ں��ތ����P
	char	c_reccnt02[112];	// �_��ں��ތ����Q�`�P�T( 0 �Œ�)
	char	c_yobi[344];		// �\�� 
	char	c_filler[511];		// FILLER
	char	c_kaigyo[1];		// ���s����
} LD104Trailer ;

// �v���O�������\����
struct appEnv {
	BMLPRM	*bp;
	char	*pcFileNamePRM;
	int	shm_Id;				// ���L������ID
	key_t	shm_Key;			// ���L�������L�[
	int	iSleepMin;			// �X���[�v���ԁi���j
	char	cDBName[1024];			// �f�[�^�x�[�X�ڑ���
	char	cDBUser[1024];			// ���O�C�����[�U
	char	cDBPawd[1024];			// ���O�C���p�X���[�h
	char	cDataFlowID[1024];		// �f�[�^�t���[�h�c
	char	cSendIDMoto[1024];		// ���M���h�c
	char	cSendIDSaki[1024];		// ���M��h�c
	char	cDirDataFile[1024];		// �v���J�[�h�t�@�C���o�̓f�B���N�g��
	char	cDirSend[1024];			// �v���J�[�h�t�@�C�����M�p�f�B���N�g��
	int	DateRange ;			// �v���J�[�h�o�͑Ώۊ���
	char	cDebugLogName[1024];		// �f�o�b�O���O�t�@�C����
	char	cTraceLogName[1024];		// �g���[�X���O�t�@�C����
	char	cAccessLogName[1024];		// �A�N�Z�X���O�t�@�C����
	char	cErrorLogName[1024];		// �G���[���O�t�@�C����
	char	cLogName[128];			// ���O
} pAppEnv;

/**************************************************************************/
/* �O���[�o���錾							  */
/**************************************************************************/
extern	char	G_msg[256]; // LogMessage

/**************************************************************************/
/* �v���g�^�C�v�錾							  */
/**************************************************************************/
void LD104ConvTimestamp(ULONG ulTm, char *pDest);
int LD104ConvNumber(char *pDest, char *pSrc);
int LD104CopyFromLeft(char *pDest, char *pSrc, int iSize, BOOL bMbFlg);
int LD104CopyFromRight(char *pDest, char *pSrc, int iSize, BOOL bMbFlg);

int initFunction( int argc, char *argv[] );
int mainFunction();
void endFunction();
int LD104MakeData(GetKekka *pGetKekka, LD104Rec *pLD104Rec);
int LD104DataFileFilter(struct dirent *pDirEnt);
int LD104WriteFile(FILE *fp, LD104Rec *pLD104Rec);
int LD104CreateFile(Sysknrmst *pSysKnrmst, GetKekka *pGetKekkaArrayOut, int iKekkaNumOut);

void sFncGetdate( char *, char *, int );

//  ���L����������֐�
static  int sFncShmCrt();
static  int sFncShmGet(int *);
static  int sFncShmDel();
//  �g���[�X�p
static  void	_sFncEnvDip();
//���O�֐�
void sFncPutLog( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... );
#endif
/** End of File ***********************************************************/
