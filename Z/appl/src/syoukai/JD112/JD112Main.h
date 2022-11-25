/********************************************************************/
/*																	*/
/*		�a�l�k�l���������V�X�e��									*/
/*																	*/
/*		�V�X�e����	�F������V�X�e��								*/
/*		�t�@�C����	�FJD112Main.h									*/
/*		�T�v		�F�����i�s�󋵏W�v�w�b�_�[�t�@�C��				*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	�쐬��			���O			�C�����e				*/
/* ---------------------------------------------------------------- */
/*  1.00	2006/03/23		H.Suyama		Create					*/
/*  1.04    2006-06-17      INTEC           �o�^����10���P�ʂɍ쐬  */
/********************************************************************/
#ifndef _JD112Main_h
#define _JD112Main_h

/********************************************************************/
/*  �C���N���[�h�錾												*/
/********************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <dirent.h>
#include <sys/shm.h>
#include "bml_base.h"
#include "JD112Knssnkjyk.h"

#define MYAPP_APP_NAME		  "JD112"

//  �����X�e�[�^�X�R�[�h��`
typedef enum {
	JD112_STSCODE_NORMAL,
	JD112_STSCODE_ERR_USAGE,
	JD112_STSCODE_ERR_PRM_FILE,
	JD112_STSCODE_ERR_PRM_GET,
	JD112_STSCODE_ERR_SHM_AT,
	JD112_STSCODE_ERR_SHM_DT,
	JD112_STSCODE_ERR_SHM_DEL,
	JD112_STSCODE_ERR_SHM_GET,
	JD112_STSCODE_ERR_DIR,
	JD112_STSCODE_ERR_FR_FILE
} JD112_STSCODE;

// ���L�������T�C�Y
#define JD112_SHM_SIZE			sizeof ( int ) * 2

// �p�����[�^�t�@�C���L�[������
#define JD112_PRM_DBNAME		"DBNAME"		// �f�[�^�x�[�X�ڑ���
#define JD112_PRM_DBUSER		"DBUSER"		// ���O�C�����[�U
#define JD112_PRM_DBPAWD		"DBPAWD"		// ���O�C���p�X���[�h
#define JD112_PRM_PORTNO		"PORTNO"		// �|�[�g�ԍ�
#define JD112_PRM_LISTEN		"LISTEN"		// �R�l�N�g�v���҂���
#define JD112_PRM_RETRY_CNT		"RETRY_CNT"		// �ʐM���g���C��
#define JD112_PRM_TIMEOUT		"TIMEOUT"		// �^�C���A�E�g�l�i�b�j
#define JD112_PRM_APP_IRAI		"APP_IRAI"		// �˗��W�J�A�v����
#define JD112_PRM_APP_KANJYA	"APP_KANJYA"	// ���ґ����W�J�A�v����
#define JD112_PRM_APP_BUNCHU	"APP_BUNCHU"	// �����W�J�A�v����
#define JD112_PRM_APP_NINSIKI	"APP_NINSIKI"	// �F���W�J�A�v����
#define JD112_PRM_APP_KENZOK	"APP_KENZOK"	// ���̑����W�J�A�v����
#define JD112_PRM_UPDATE_MIN	"UPDATE_MIN"	// �X�V�Ԋu�i���j
#define JD112_PRM_SLEEP_SEC		"SLEEP_SEC"		// �X���[�v���ԁi�b�j
#define JD112_PRM_SHM_KEY		"SHM_KEY"		// ���L�������L�[
#define JD112_PRM_FILE_DBG		"FILE_DBG_NSME"	// �f�o�b�O
#define JD112_PRM_FILE_TR		"FILE_TR_NAME"	// �g���[�X
#define JD112_PRM_FILE_ACS		"FILE_ACS_NAME"	// �A�N�Z�X
#define JD112_PRM_FILE_ERR		"FILE_ERR_NAME"	// �G���[
#define JD112_PRM_UP_ID			"UPDATE_ID"		// �X�V��ID
#define JD112_PRM_UP_NM			"UPDATE_NM"		// �X�V��
#define JD112_PRM_PROC_MD		"PROC_MD"		// ���s���[�h

#define JD112_PRM_STA_DH		"STA_DH"		// 1.04 ADD �W�v�J�n����

// �W�v�v���d��
#define JD112_MSG_BUFFLEN		1024
#define JD112_MSG_START			"JD112CALLFUNC"
#define JD112_MSG_END			"JD112FUNCEND"

// �f�[�^���ʎq
#define JD112_DB_KOTEIKBN_IRAI		'A'		// �˗�
#define JD112_DB_KOTEIKBN_KANJYA	'B'		// ����
#define JD112_DB_KOTEIKBN_BUNCHU	'C'		// ����
#define JD112_DB_KOTEIKBN_NINSIKI	'D'		// �F��
#define JD112_DB_KOTEIKBN_KENZOK	'E'		// ���̑���
#define JD112_DB_KOTEIKBN_E_IRAI	'F'		// �˗��i�G���[�j
#define JD112_DB_KOTEIKBN_E_KANJYA	'G'		// ���ҁi�G���[�j
#define JD112_DB_KOTEIKBN_E_BUNCHU	'H'		// �����i�G���[�j
#define JD112_DB_KOTEIKBN_E_NINSIKI	'I'		// �F���i�G���[�j
#define JD112_DB_KOTEIKBN_E_KENZOK	'J'		// ���̑����i�G���[�j
#define JD112_DB_KOTEIKBN_TOUNYU	'K'		// ����
#define JD112_DB_KOTEIKBN_SOKUTEI	'L'		// ����
#define JD112_DB_KOTEIKBN_SYUNOU	'M'		// ���[
//(MOD)<START>2006/5/9 S.Fukuyama
//     �����X�g�b�J�^����X�g�b�J�ɕύX
//#define JD112_DB_KNSJKFLG_CHUU	'1'		// ������
//#define JD112_DB_KNSJKFLG_DONE	'2'		// ��������
#define JD112_DB_KNSJKFLG_CHUU		'A'		// �����X�g�b�J
#define JD112_DB_KNSJKFLG_DONE		'E'		// ����X�g�b�J
//(MOD)<END>2006/5/9 S.Fukuyama
#define JD112_DB_SKFLG_NORMAL		'0'		// ���
#define JD112_DB_SKFLG_SYUKEN		'1'		// �W��
#define JD112_DB_DATAZOK_NORMAL		'A'		// ���
#define JD112_DB_DATAZOK_SYUKEN		'B'		// �W��

#define JD112_CALLFUNC_STOP			0
#define JD112_CALLFUNC_START		1
#define JD112_SECOFMIN				60
#define JD112_CHAR_SPACE			' '

#define JD112_FMT_TIMESTAMP			"%04d-%02d-%02d-%02d.%02d.%02d.000000"
#define JD112_FMT_DATETIME			"%04d-%02d-%02d%02d:%02d:%02d"

#define MYAPP_LOG_ERRCODE_NON		"00000000"
#define MYAPP_LOG_ERRCODE_APP		"010"
#define MYAPP_LOG_ERRCODE_DB		"020"
#define MYAPP_LOG_ERRCODE_ETC		"0Z0"
#define MYAPP_LOG_ERRCODE_SOCKET	999

#define MYAPP_FUNC_MINUS			0				// 1.04 ADD 
#define MYAPP_FUNC_PLUS				1				// 1.04 ADD 

// �f�t�H���gINI�t�@�C��
#define MYAPP_INIFILE "./JD112.ini"
// ���O�t�@�C��INI�t�@�C��
#define MYAPP_LOGINIFILE "$HOME/bin/JD112_LOG.ini"

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
	int		iUpdateMin;				// �X�V�Ԋu�i���j
	int		iSockFd;				// �\�P�b�gFD
	int		iCallFunc;				// �W�v���s�J�n�t���O
	int		iThreadSts;				// �X���b�h�X�e�[�^�X
	int		iPortNo;				// �|�[�g�ԍ�
	int		iListen;				// �R�l�N�g�ڑ��҂���
	int		iRetryCnt;				// �ʐM���g���C��
	int		iTimeout;				// �^�C���A�E�g�l�i�b�j
	char	cAppIrai[1024];			// �˗��W�J�A�v����
	char	cAppKanjya[1024];		// ���ґ����W�J�A�v����
	char	cAppBunchu[1024];		// �����W�J�A�v����
	char	cAppNinsiki[1024];		// �F���W�J�A�v����
	char	cAppKenzok[1024];		// ���̑����W�J�A�v����
	char	cDBName[1024];			// �f�[�^�x�[�X�ڑ���
	char	cDBUser[1024];			// ���O�C�����[�U
	char	cDBPawd[1024];			// ���O�C���p�X���[�h
	char	cDebugLogName[1024];	// �f�o�b�O���O�t�@�C����
	char	cTraceLogName[1024];	// �g���[�X���O�t�@�C����
	char	cAccessLogName[1024];	// �A�N�Z�X���O�t�@�C����
	char	cErrorLogName[1024];	// �G���[���O�t�@�C����
	int		proc_mode;				// �������[�h	0�F�ߓn��   1�F������
	char	cUpdateId[128];			// �X�V��ID
	char	cUpdateName[128];		// �X�V��
	char	cLogName[128];			// ���O
	ULONG	ulPrevKsndh;			// �O��W�v�J�n����
	int		iBaseJikan;				// ����N�����̎���
	char	clPrevKsndh[27];		// 1.04 ADD �O��W�v�J�n����
	char	cStaTimestamp[27];		// 1.04 ADD �W�v�ΏۊJ�n����(�K�{�ł͂Ȃ�)
									// YYYY-MM-DD-HH24:MI:00
} JD112Env;

// 1.02 INTEC ADD STA
	// ���͋@�}�X�^
struct _MEMST {
	char	bskkbn[4+1];			// ���͋@�敪
	char	bsklne[4+1];			// ���͋@���C��
} hmemst;
// 1.02 INTEC ADD END
/******************************************************************************/
/* �O���[�o���錾															  */
/******************************************************************************/

/******************************************************************************/
/* �v���g�^�C�v�錾															  */
/******************************************************************************/
void JD112ConvTimestamp(ULONG ulTm, int iFlg, char *pDest);

int initFunction( int argc, char *argv[], JD112Env *pEnv );
int mainFunction( JD112Env *pEnv );
void endFunction( JD112Env *pEnv );

int JD112SyukeiMain(JD112Env *pEnv, char *pKnskisymd);
int JD112UpdateKnssnkjyk(Knssnkjyk *pKnssnkjyk);
void *JD112SocketThread(void *pParam);

//  ���L����������֐�
static  int sFncShmCrt ( JD112Env * );
static  int sFncShmGet ( JD112Env * , int *);
static  int sFncShmDel ( JD112Env * );
//  �g���[�X�p
static  void	_sFncEnvDip ( JD112Env * );
//���O�֐�
void sFncPutLog( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... );
#endif
/** End of File ***************************************************************/
