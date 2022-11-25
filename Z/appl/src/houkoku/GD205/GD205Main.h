/********************************************************************/
/*																	*/
/*		�a�l�k�l���������V�X�e��									*/
/*																	*/
/*		�V�X�e����	�F������V�X�e��								*/
/*		�t�@�C����	�FGD205Main.h									*/
/*		�T�v		�F�񍐃f�[�^�t�@�C���쐬�w�b�_�[�t�@�C��		*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	�쐬��			���O			�C�����e				*/
/* ---------------------------------------------------------------- */
/*  1.00	2006/02/27		H.Suyama		Create					*/
/*  1.01	2006/04/06		H.Suyama		�G���[�R�[�h�ǉ�		*/
/*                                          �g���[���̐ݒ�l�C��    */
/*  1.02	2006/04/20		H.Suyama		�R�[�h�ǉ�				*/
/*  2.00	2009/01/06		Merits K.Ameno	�{�݃R�[�h���� �ʐM�d�l�ύX�Ή�    */
/********************************************************************/
#ifndef _GD205Main_h
#define _GD205Main_h

/********************************************************************/
/*  �C���N���[�h�錾												*/
/********************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <dirent.h>
#include <sys/shm.h>
#include "bml_base.h"
#include "GD205Sysknrmst.h"
#include "GD205Kekka.h"

/******************************************************************************/
/* Define��`																  */
/******************************************************************************/
#define CHAR_KANJI		  0x80
#define iskanji(c)  ((c) & CHAR_KANJI)

#define MYAPP_APP_NAME		  "GD205"

//  �����X�e�[�^�X�R�[�h��`
typedef enum {
	GD205_STSCODE_NORMAL,
	GD205_STSCODE_ERR_USAGE,
	GD205_STSCODE_ERR_PRM_FILE,
	GD205_STSCODE_ERR_PRM_GET,
	GD205_STSCODE_ERR_SHM_AT,
	GD205_STSCODE_ERR_SHM_DT,
	GD205_STSCODE_ERR_SHM_DEL,
	GD205_STSCODE_ERR_SHM_GET,
	GD205_STSCODE_ERR_DIR,
	GD205_STSCODE_ERR_FR_FILE
} GD205_STSCODE;

//  ���L�������T�C�Y
#define GD205_SHM_SIZE			sizeof ( int )
#define GD205_SIZE_BUFF			1024	// �f�[�^�����p�o�b�t�@�T�C�Y

#define GD205_LEN_DATESHORT		8	// YYYYMMDD�̒���
#define GD205_LEN_NOITEM		11	// �˗�No�A����No���ڂ̒���
#define GD205_LEN_SRCNO         6   // 3.01 ADD ����No�̗L������
#define GD205_LEN_SRCNO1		3	// �˗�No�A����No�̃u���b�N1�̒���
#define GD205_LEN_SRCNO2		6	// �˗�No�A����No�̃u���b�N2�̒���
#define GD205_LEN_FILEID		12	// ���M�t�@�C��ID�iYYYYMMDD9999�j�̒���
#define GD205_LEN_FILESEQNO		4	// ���M�t�@�C��ID��SeqNo�i9999�j�̒���

#define GD205_POS_SRCNO         3   // 3.01 ADD �˗�No�A����No�̃u���b�N1�̊J�n�ʒu
#define GD205_POS_SRCNO1		2	// �˗�No�A����No�̃u���b�N1�̊J�n�ʒu
#define GD205_POS_SRCNO2		5	// �˗�No�A����No�̃u���b�N2�̊J�n�ʒu
#define GD205_POS_DESTNO1		0	// �˗�No�A����No�̕ϊ���̃u���b�N1�̊J�n�ʒu
#define GD205_POS_DESTNO2		3	// �˗�No�A����No��"00"�̊J�n�ʒu
#define GD205_POS_DESTNO3		5	// �˗�No�A����No�̕ϊ���̃u���b�N1�̊J�n�ʒu

//  �p�����[�^�t�@�C���L�[������
#define GD205_PRM_DBNAME		"DBNAME"		// �f�[�^�x�[�X�ڑ���
#define GD205_PRM_DBUSER		"DBUSER"		// ���O�C�����[�U
#define GD205_PRM_DBPAWD		"DBPAWD"		// ���O�C���p�X���[�h
#define GD205_PRM_DIR_DATAFILE	"DIR_DATAFILE"	// �񍐃f�[�^�t�@�C���o�̓f�B���N�g��
#define GD205_PRM_DIR_TODAY		"DIR_TODAY"		// �]���f�[�^�t�@�C���o�̓f�B���N�g��
#define GD205_PRM_DIR_OLDDAY	"DIR_OLDDAY"	// �]���f�[�^�t�@�C���ߋ��f�B���N�g��
#define GD205_PRM_DIR_SENDFILE	"DIR_SENDFILE"	// �]���f�[�^�t�@�C�����M�p�f�B���N�g��
#define GD205_PRM_DIR_SENDREQ	"DIR_SENDREQ"	// �]���f�[�^�t�@�C��REQUEST�f�B���N�g��
#define GD205_PRM_DIR_SENDOK	"DIR_SENDOK"	// �]���f�[�^�t�@�C��OK�f�B���N�g��
#define GD205_PRM_DIR_SENDERR	"DIR_SENDERR"	// �]���f�[�^�t�@�C��ERR�f�B���N�g��
//#define GD205_PRM_DATAFLOWID	"DATAFLOWID"	// �f�[�^�t���[�h�c
//#define GD205_PRM_SENDID_MOTO	"SENDID_MOTO"	// ���M���h�c
//#define GD205_PRM_SENDID_SAKI	"SENDID_SAKI"	// ���M��h�c
#define GD205_PRM_SLEEP_SEC		"SLEEP_SEC"		// �X���[�v���ԁi�b�j
#define GD205_PRM_SHM_KEY		"SHM_KEY"		// ���L�������L�[
#define GD205_PRM_FILE_DBG		"FILE_DBG_NSME"	// �f�o�b�O
#define GD205_PRM_FILE_TR		"FILE_TR_NAME"	// �g���[�X
#define GD205_PRM_FILE_ACS		"FILE_ACS_NAME"	// �A�N�Z�X
#define GD205_PRM_FILE_ERR		"FILE_ERR_NAME"	// �G���[
#define GD205_PRM_UP_ID			"UPDATE_ID"		// �X�V��ID
#define GD205_PRM_UP_NM			"UPDATE_NM"		// �X�V��
#define GD205_PRM_PROC_MD		"PROC_MD"		// ���s���[�h
#define GD205_PRM_COMMIT_SU		"COMMIT_SU"		// 1.13 ADD KEKKA COMMIT
#define GD205_PRM_PREFIXNM		"PREFIX_NM"		// 1.13 ADD KEKKA COMMIT

//�f�[�^���ʎq
#define GD205_FILE_HEADERID		"HD"
#define GD205_FILE_TRAILERID	"TR"
#define GD205_FILE_DATAID		"R1"
#define GD205_FILE_LINEFEED		'\n'
#define GD205_FILE_FILLER_SIZE	121
#define GD205_FILEEXT_DATA		".dat"
#define GD205_FILEEXT_TEMP		".tmp"
//#define GD205_REC_LOOP_MAX		6
#define GD205_REC_LOOP_MAX		1
#define GD205_DATA_CHAR0		'0'
#define GD205_DATA_SPACE		' '
#define GD205_DATA_STR00		"00"
#define GD205_DATA_ASTERISK     '*'				// 3.01 ADD

//���ʕҏW
#define GD205_KEKKA_NG     		"*340"			// 3.01 ADD ���ʕҏW�s��
#define GD205_KEKKA_LT     		"LT"			// 3.01 ADD �����A�ȉ�
#define GD205_KEKKA_GT     		"GT"			// 3.01 ADD �ȏ�A����

#define GD205_DB_HKKJKFLG_CHUU		"1 "
#define GD205_DB_HKKJKFLG_ERRFILE	"4 "
#define GD205_DB_HKKJKFLG_OK		'2'
#define GD205_DB_HKKJKN_CTRLNO		'1'
#define GD205_DB_HKKJKN_PLTNO		'2'
#define GD205_DB_HKKJKN_KNSSEQ		'3'
#define GD205_DB_HKKJKN_IRINO		'4'
#define GD205_DB_HKKJKN_KNTNO		'5'
#define GD205_DB_HKKJKN_RESEND		'8'
#define GD205_DB_KNSFLG_HORYU		'H'
#define GD205_DB_KNSFLG_DONE		'E'
#define GD205_DB_KKASSFLG_MAX		'9'
#define GD205_DB_SSNTUBN_MAX		9999
// 2006-04-20 H.Suyama Add Start
#define GD205_DB_HKKKBN_CYUU		'2'
#define GD205_DB_HKKKBN_LAST		'1'
#define GD205_DB_KKAJKCD_CYUU		'1'
#define GD205_DB_KKAJKCD_LAST		'3'
// 2006-04-20 H.Suyama Add End

#define GD205_DB_HKKERRCODE_HKKJKN	"00000001"
#define GD205_DB_HKKERRCODE_HKKKNRI	"00000002"
#define GD205_DB_HKKERRCODE_CREATE	"00000003"
#define GD205_DB_HKKERRCODE_RESEND	"00000004"
#define GD205_DB_HKKERRCODE_SEQMAX	"00000005"
#define GD205_DB_HKKERRCODE_NODATA	"00000006"
// 2006-04-06 H.Suyama Add Start
#define GD205_DB_HKKERRCODE_DBACS	"00000007"
#define GD205_DB_HKKERRCODE_HULFT	"00000008"
// 2006-04-06 H.Suyama Add End

#define MYAPP_LOG_ERRCODE_NON		"00000000"
#define MYAPP_LOG_ERRCODE_APP		"010"
#define MYAPP_LOG_ERRCODE_DB		"020"
#define MYAPP_LOG_ERRCODE_ETC		"0Z0"

// �f�t�H���gINI�t�@�C��
//1.03 DELL #define MYAPP_INIFILE "./GD205.ini"
#define MYAPP_INIFILE "$HOME/appl/src/houkoku/GD205/GD205.ini"
// ���O�t�@�C��INI�t�@�C��
//1.03 DELL #define MYAPP_LOGINIFILE "./GD205_LOG.ini"
#define MYAPP_LOGINIFILE "$HOME/appl/src/houkoku/GD205/GD205_LOG.ini"

/******************************************************************************/
/* �\���̒�`																  */
/******************************************************************************/
// �񍐃f�[�^�\����
typedef struct {
    char    cUTKYMD[8];     /* BML��t�N���� [YYYYMMDD]�`�� */
    char    cKNTNO[11];     // ����No Ver 2.00 6->11��PNC�`���ɕύX */
/*	char    cFILLER1[5];*/  /* FILLER *//* Ver 2.00 �폜 */
    char    cOYAKMKCD[7];   /* �e���ڃR�[�h Ver2.00 4->7���ɑ��� */
    char    cKMKCD[7];      /* ���ڃR�[�h Ver2.00 4->7���ɑ��� */
    char    cWSCD[4];       /* WS�R�[�h(�T���v�����O�R�[�h) Ver 2.00 3->4���ɑ��� */
    char    cWSSEQ[4];      /* WSSEQ(����SEQ) */
                            // ���l�𕶎���ϊ���A�E����4����ݒ�iw�w�w�w�w�w�w�w��Ȃ��j
    char    cKNSKKA[6];     /* �������� */
                            /* �������ʂPor�������ʂQ�i�������ʂP�D��j */
                            /* �������ʂP�F�E����6����ݒ�iw�w�w�w�w�w�w�w�����A�����_�폜�j */
                            /* �������ʂQ�F�������ʋ敪='0'��'*'+��2���ڂ���6���ڂ܂� */
                            /* �@�@�@�@�@�@�ȊO��������6����ݒ�i2�o�C�g�����ɒ��ӂ���j */
    char    cKKACMT[3];     /* ���ʃR�����g */
                            /* �E����3����ݒ� */
    char    cIJKBN;         /* �ُ�l�}�[�N�敪 */
                            /* �ُ�l�敪�i�j�A���A�s���j��'4','5','6'�ȊO�ł����'*' */
    char    cFILLER2[6];    /* FILLER */
    char    cLF;            /* LF */
} GD205Rec;

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
	char	cDirToday[1024];		// �]���f�[�^�t�@�C���o�̓f�B���N�g��
	char	cDirOldday[1024];		// �]���f�[�^�t�@�C���ߋ��f�B���N�g��
	char	cDirSendFile[1024];		// �]���f�[�^�t�@�C�����M�p�f�B���N�g��
	char	cDirSendREQ[1024];		// �]���f�[�^�t�@�C��REQ�f�B���N�g��
	char	cDirSendOK[1024];		// �]���f�[�^�t�@�C��OK�f�B���N�g��
	char	cDirSendERR[1024];		// �]���f�[�^�t�@�C��ERR�f�B���N�g��
	char	cDataFlowID[1024];		// �f�[�^�t���[�h�c
	char	cSendIDMoto[1024];		// ���M���h�c
	char	cSendIDSaki[1024];		// ���M��h�c
	char	cDebugLogName[1024];	// �f�o�b�O���O�t�@�C����
	char	cTraceLogName[1024];	// �g���[�X���O�t�@�C����
	char	cAccessLogName[1024];	// �A�N�Z�X���O�t�@�C����
	char	cErrorLogName[1024];	// �G���[���O�t�@�C����
	int		proc_mode;				// �������[�h	0�F�ߓn��   1�F������
	char	cUpdateId[128];			// �X�V��ID
	char	cUpdateName[128];		// �X�V��
	char	cLogName[128];			// ���O
	int		iCommitSu;				// 1.13 ADD ���ʏ�� �ꊇCOMMIT����
	char	cPrefixNm[1024];		// 3.01 ADD ���M�t�@�C���擪������
} GD205Env;

/******************************************************************************/
/* �O���[�o���錾															  */
/******************************************************************************/
// extern
extern      char        G_msg[256]; // 1.06 ADD LogMessage

/******************************************************************************/
/* �v���g�^�C�v�錾															  */
/******************************************************************************/
void GD205ConvTimestamp(ULONG ulTm, char *pDest);
int GD205ConvNumber(char *pDest, char *pSrc);
int GD205CopyFromLeft(char *pDest, char *pSrc, int iSize, BOOL bMbFlg);
int GD205CopyFromRight(char *pDest, char *pSrc, int iSize, BOOL bMbFlg);

int initFunction( int argc, char *argv[], GD205Env *pEnv );
int mainFunction( GD205Env *pEnv );
void endFunction( GD205Env *pEnv );
int GD205MakeData(Kekka *pKekka, char *pLBCD, GD205Rec *pGD205Rec);
int GD205DataFileFilter(struct dirent *pDirEnt);
int GD205WriteFile(FILE *fp, GD205Rec *pGD205Rec, int iRecCnt);

//2006.12.08 Kim Jinsuk �c�a�G���[�ُ펞�I��
//int GD205CreateFile(GD205Env *pEnv, Sysknrmst *pSysknrmst, Kekka *pKekkaArrayOut, int iKekkaNumOut, int *piHkkssknsu, int *piHkkhrysu, char *pFileName,int *sqlErrorFlag);
int GD205CreateFile(GD205Env *pEnv, Sysknrmst *pSysknrmst, Kekka *pKekkaArrayOut, int iKekkaNumOut, int *piHkkssknsu, int *piHkkhrysu, char *pFileName,Hkkknri *pHkkknriArrayOut, int *sqlErrorFlag);
//2006-07-06 CHG Osada �t�@�C�����������@�ύX
//int GD205CreateHULFTFile(GD205Env *pEnv, Sysknrmst *pSysknrmst, Hkkknri *pHkkknri, char *pDataFile, int iLogicalCnt);
int GD205CreateHULFTFile(GD205Env *pEnv, Sysknrmst *pSysknrmst, Hkkknri *pHkkknri, char *pDataFile, int iLogicalCnt, Hkkknri *pHkkknriArrayOut);
// 2006-04-06 H.Suyama Change End
int GD205ResendFile(GD205Env *pEnv, Sysknrmst *pSysknrmst, Hkkknri *pHkkknri);
void GD205UpdateHkkknriSts( Hkkknri *pHkkknri, char *pHkkjkflg, char *pHkkerrcode );

//  ���L����������֐�
static  int sFncShmCrt ( GD205Env * );
static  int sFncShmGet ( GD205Env * , int *);
static  int sFncShmDel ( GD205Env * );
//  �g���[�X�p
static  void	_sFncEnvDip ( GD205Env * );
//���O�֐�
void sFncPutLog( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... );
#endif
/** End of File ***************************************************************/
