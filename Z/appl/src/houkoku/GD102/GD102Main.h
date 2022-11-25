/********************************************************************/
/*																	*/
/*		�a�l�k�l���������V�X�e��									*/
/*																	*/
/*		�V�X�e����	�F������V�X�e��								*/
/*		�t�@�C����	�FGD102Main.h									*/
/*		�T�v		�F�t�@�C���]���w�b�_�[�t�@�C��					*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	�쐬��			���O			�C�����e				*/
/* ---------------------------------------------------------------- */
/*  1.00	2006/02/27		H.Suyama		Create					*/
/********************************************************************/
#ifndef _GD102Main_h
#define _GD102Main_h

/********************************************************************/
/*  �C���N���[�h�錾												*/
/********************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <dirent.h>
#include <sys/shm.h>
#include "bml_base.h"

/******************************************************************************/
/* Define��`																  */
/******************************************************************************/
#define CHAR_KANJI		  0x80
#define iskanji(c)  ((c) & CHAR_KANJI)

#define MYAPP_APP_NAME		  "GD102"

//  �����X�e�[�^�X�R�[�h��`
typedef enum {
	GD102_STSCODE_NORMAL,
	GD102_STSCODE_ERR_USAGE,
	GD102_STSCODE_ERR_PRM_FILE,
	GD102_STSCODE_ERR_PRM_GET,
	GD102_STSCODE_ERR_SHM_AT,
	GD102_STSCODE_ERR_SHM_DT,
	GD102_STSCODE_ERR_SHM_DEL,
	GD102_STSCODE_ERR_SHM_GET,
	GD102_STSCODE_ERR_DIR,
	GD102_STSCODE_ERR_FR_FILE
} GD102_STSCODE;

//  ���L�������T�C�Y
#define GD102_SHM_SIZE			sizeof ( int )

#define GD102_LEN_DATESHORT		8	// YYYYMMDD�̒���
#define GD102_LEN_IRAIFILE		10	// �˗����ڗv�����t�@�C������
#define GD102_LEN_BUNCFILE		10	// �������ʗv�����t�@�C������
#define GD102_LEN_OTHERKKAFILE		10	//

//  �p�����[�^�t�@�C���L�[������
#define GD102_PRM_DBNAME		"DBNAME"		// �f�[�^�x�[�X�ڑ���
#define GD102_PRM_DBUSER		"DBUSER"		// ���O�C�����[�U
#define GD102_PRM_DBPAWD		"DBPAWD"		// ���O�C���p�X���[�h
#define GD102_PRM_DIR_HULFTBIN	"DIR_HULFTBIN"	// HULFT���s�t�@�C���f�B���N�g��
#define GD102_PRM_DIR_REQ_KKA	"DIR_REQ_KKA"	// ���ʕ񍐃t�@�C��REQUEST�f�B���N�g��
#define GD102_PRM_DIR_REQ_IRAI	"DIR_REQ_IRAI"	// �˗��v���t�@�C��REQUEST�f�B���N�g��
#define GD102_PRM_DIR_REQ_BUNC	"DIR_REQ_BUNC"	// �������ʗv���t�@�C��REQUEST�f�B���N�g��
#define GD102_PRM_DIR_REQ_OTHERKKA	"DIR_REQ_OTHERKKA"	// ���T�e���C�g���ʗv���t�@�C��REQUEST�f�B���N�g��
#define GD102_PRM_DIR_OK_KKA	"DIR_OK_KKA"	// ���ʕ񍐃t�@�C��OK�f�B���N�g��
#define GD102_PRM_DIR_OK_IRAI	"DIR_OK_IRAI"	// �˗��v���t�@�C��OK�f�B���N�g��
#define GD102_PRM_DIR_OK_BUNC	"DIR_OK_BUNC"	// �������ʗv���t�@�C��OK�f�B���N�g��
#define GD102_PRM_DIR_OK_OTHERKKA	"DIR_OK_OTHERKKA"	// ���T�e���C�g���ʗv���t�@�C��OK�f�B���N�g��
#define GD102_PRM_DIR_ERR_KKA	"DIR_ERR_KKA"	// ���ʕ񍐃t�@�C��ERR�f�B���N�g��
#define GD102_PRM_DIR_ERR_IRAI	"DIR_ERR_IRAI"	// �˗��v���t�@�C��ERR�f�B���N�g��
#define GD102_PRM_DIR_ERR_BUNC	"DIR_ERR_BUNC"	// �������ʗv���t�@�C��ERR�f�B���N�g��
#define GD102_PRM_DIR_ERR_OTHERKKA	"DIR_ERR_OTHERKKA"	// ���T�e���C�g���ʗv���t�@�C��ERR�f�B���N�g��
#define GD102_PRM_SEND_FILENAME	"SEND_FILENAME"	// HULFT���M�t�@�C����
#define GD102_PRM_SEND_FILEOK	"SEND_FILEOK"	// HULFT���MOK�m�F�t�@�C����
#define GD102_PRM_SEND_FILENG	"SEND_FILENG"	// HULFT���MNG�m�F�t�@�C����
#define GD102_PRM_HULFT_FILEID	"HULFT_FILEID"	// HULFT���M�t�@�C��ID
#define GD102_PRM_INTERVAL		"INTERVAL"		// HULFT���s���ʑ҂�����
#define GD102_PRM_SEND_RETRY	"SEND_RETRY"	// ���M���g���C��
#define GD102_PRM_CMD_RETRY		"CMD_RETRY"		// ���M�R�}���h���g���C��
#define GD102_PRM_RESULT_RETRY	"RESULT_RETRY"	// ���ʃ`�F�b�N���g���C��
#define GD102_PRM_SLEEP_SEC		"SLEEP_SEC"		// �X���[�v���ԁi�b�j
#define GD102_PRM_SHM_KEY		"SHM_KEY"		// ���L�������L�[
#define GD102_PRM_FILE_DBG		"FILE_DBG_NSME"	// �f�o�b�O
#define GD102_PRM_FILE_TR		"FILE_TR_NAME"	// �g���[�X
#define GD102_PRM_FILE_ACS		"FILE_ACS_NAME"	// �A�N�Z�X
#define GD102_PRM_FILE_ERR		"FILE_ERR_NAME"	// �G���[
#define GD102_PRM_UP_ID			"UPDATE_ID"		// �X�V��ID
#define GD102_PRM_UP_NM			"UPDATE_NM"		// �X�V��
#define GD102_PRM_PROC_MD		"PROC_MD"		// ���s���[�h

//�f�[�^���ʎq
#define GD102_FILE_HEADERID		"HD"
#define GD102_FILE_DATAID		"R1"
#define GD102_FILE_LINEFEED		'\n'
#define GD102_FILE_FILLER_SIZE	121
#define GD102_REC_LOOP_MAX		6
#define GD102_DATA_CHAR0		'0'
#define GD102_DATA_SPACE		' '
#define GD102_DATA_STR00		"00"

#define GD102_DB_HKKJKFLG_DONE			"2 "	// ���M����(�c�a�G���[�Ȃ�)
#define GD102_DB_HKKJKFLG_ERRSEND		"5 "	// ���M���s(�c�a�G���[�Ȃ�)
#define GD102_DB_HKKJKFLG_SEND_DBERR	"9 "	// ���M�Ώ�(�c�a�G���[�L��)
#define GD102_DB_HKKJKFLG_ERRFILE		"4 "	// ���M����(�c�a�G���[�L��)

#define GD102_DB_HKKERRCODE_NOFILE	"00000009"
#define GD102_DB_HKKERRCODE_SENDNG	"00000010"

#define MYAPP_LOG_ERRCODE_NON		"00000000"
#define MYAPP_LOG_ERRCODE_APP		"010"
#define MYAPP_LOG_ERRCODE_DB		"020"
#define MYAPP_LOG_ERRCODE_ETC		"0Z0"

// �f�t�H���gINI�t�@�C��
#define MYAPP_INIFILE "./GD102.ini"
// ���O�t�@�C��INI�t�@�C��
// 1.03 INTEC DELL #define MYAPP_LOGINIFILE "./GD102_LOG.ini"
#define MYAPP_LOGINIFILE "$HOME/appl/src/houkoku/GD102/GD102_LOG.ini"

/******************************************************************************/
/* �\���̒�`																  */
/******************************************************************************/
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
	char	cDirHULFTBin[1024];		// HULFT���s�t�@�C���f�B���N�g��
	char	cDirReqKKA[1024];		// ���ʕ񍐃t�@�C��REQUEST�f�B���N�g��
	char	cDirReqIRAI[1024];		// �˗��v���t�@�C��REQUEST�f�B���N�g��
	char	cDirReqBUNC[1024];		// �������ʗv���t�@�C��REQUEST�f�B���N�g��
	char	cDirReqOTHERKKA[1024];		// ���T�e���C�g���ʗv���t�@�C��REQUEST�f�B���N�g��
	char	cDirOkKKA[1024];		// ���ʕ񍐃t�@�C��OK�f�B���N�g��
	char	cDirOkIRAI[1024];		// �˗��v���t�@�C��OK�f�B���N�g��
	char	cDirOkBUNC[1024];		// �������ʗv���t�@�C��OK�f�B���N�g��
	char	cDirOkOTHERKKA[1024];		// ���T�e���C�g���ʗv���t�@�C��OK�f�B���N�g��
	char	cDirErrKKA[1024];		// ���ʕ񍐃t�@�C��ERR�f�B���N�g��
	char	cDirErrIRAI[1024];		// �˗��v���t�@�C��ERR�f�B���N�g��
	char	cDirErrBUNC[1024];		// �������ʗv���t�@�C��ERR�f�B���N�g��
	char	cDirErrOTHERKKA[1024];		// ���T�e���C�g���ʗv���t�@�C��ERR�f�B���N�g��
	char	cSendFileName[1024];	// HULFT���M�t�@�C����
	char	cSendFileOK[1024];		// HULFT���MOK�m�F�t�@�C����
	char	cSendFileNG[1024];		// HULFT���MNG�m�F�t�@�C����
	char	cHULFTFileID[1024];		// HULFT���M�t�@�C��ID
	int		iInterval;				// HULFT���s���ʑ҂�����
	int		iSendRetry;				// ���M���g���C��
	int		iCmdRetry;				// ���M�R�}���h���g���C��
	int		iResultRetry;			// ���ʃ`�F�b�N���g���C��
	char	cDebugLogName[1024];	// �f�o�b�O���O�t�@�C����
	char	cTraceLogName[1024];	// �g���[�X���O�t�@�C����
	char	cAccessLogName[1024];	// �A�N�Z�X���O�t�@�C����
	char	cErrorLogName[1024];	// �G���[���O�t�@�C����
	int		proc_mode;				// �������[�h	0�F�ߓn��   1�F������
	char	cUpdateId[128];			// �X�V��ID
	char	cUpdateName[128];		// �X�V��
	char	cLogName[128];			// ���O
} GD102Env;

/******************************************************************************/
/* �O���[�o���錾															  */
/******************************************************************************/
// 1.03 INTEC ADD extern
extern	char	gcLogMsg[256];				// 1.03 INTEC ADD

/******************************************************************************/
/* �v���g�^�C�v�錾															  */
/******************************************************************************/
void GD102ConvTimestamp(ULONG ulTm, char *pDest);

int initFunction( int argc, char *argv[], GD102Env *pEnv );
int mainFunction( GD102Env *pEnv );
void endFunction( GD102Env *pEnv );
int GD102SendFile(GD102Env *pEnv, char *pFileName);
int GD102SendKekkaFile(GD102Env *pEnv);
int GD102BunchuFileFilter(struct dirent *pDirEnt);
int GD102SendBunchuFile(GD102Env *pEnv);
int GD102IraiFileFilter(struct dirent *pDirEnt);
int GD102SendIraiFile(GD102Env *pEnv);
int GD102OtherKkaFileFilter(struct dirent *pDirEnt);
int GD102SendOtherKkaFile(GD102Env *pEnv);

//  ���L����������֐�
static  int sFncShmCrt ( GD102Env * );
static  int sFncShmGet ( GD102Env * , int *);
static  int sFncShmDel ( GD102Env * );
//  �g���[�X�p
static  void	_sFncEnvDip ( GD102Env * );
//���O�֐�
void sFncPutLog( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... );
#endif
/** End of File ***************************************************************/
