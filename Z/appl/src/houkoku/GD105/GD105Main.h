/********************************************************************/
/*																	*/
/*		�a�l�k�l���������V�X�e��									*/
/*																	*/
/*		�V�X�e����	�F������V�X�e��								*/
/*		�t�@�C����	�FGD105Main.h									*/
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
/*  2.00	2009/05/19		K.Moriya		���ʕϊ��}�X�^�Ή�		*/
/********************************************************************/
#ifndef _GD105Main_h
#define _GD105Main_h

/********************************************************************/
/*  �C���N���[�h�錾												*/
/********************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <dirent.h>
#include <sys/shm.h>
#include "bml_base.h"
#include "GD105Sysknrmst.h"
#include "GD105Kekka.h"
/* 2.00 2009.05.19 ���ʕϊ��}�X�^�Ή� START */
#include "GD105KkaConvChk.h"
/* 2.00 2009.05.19 ���ʕϊ��}�X�^�Ή� END */

/******************************************************************************/
/* Define��`																  */
/******************************************************************************/
#define CHAR_KANJI		  0x80
#define iskanji(c)  ((c) & CHAR_KANJI)

#define MYAPP_APP_NAME		  "GD105"

//  �����X�e�[�^�X�R�[�h��`
typedef enum {
	GD105_STSCODE_NORMAL,
	GD105_STSCODE_ERR_USAGE,
	GD105_STSCODE_ERR_PRM_FILE,
	GD105_STSCODE_ERR_PRM_GET,
	GD105_STSCODE_ERR_SHM_AT,
	GD105_STSCODE_ERR_SHM_DT,
	GD105_STSCODE_ERR_SHM_DEL,
	GD105_STSCODE_ERR_SHM_GET,
	GD105_STSCODE_ERR_DIR,
	GD105_STSCODE_ERR_FR_FILE
} GD105_STSCODE;

//  ���L�������T�C�Y
#define GD105_SHM_SIZE			sizeof ( int )
#define GD105_SIZE_BUFF			1024	// �f�[�^�����p�o�b�t�@�T�C�Y

#define GD105_LEN_DATESHORT		8	// YYYYMMDD�̒���
#define GD105_LEN_NOITEM		11	// �˗�No�A����No���ڂ̒���
#define GD105_LEN_SRCNO1		3	// �˗�No�A����No�̃u���b�N1�̒���
#define GD105_LEN_SRCNO2		6	// �˗�No�A����No�̃u���b�N2�̒���
#define GD105_LEN_FILEID		12	// ���M�t�@�C��ID�iYYYYMMDD9999�j�̒���
#define GD105_LEN_FILESEQNO		4	// ���M�t�@�C��ID��SeqNo�i9999�j�̒���

#define GD105_POS_SRCNO1		2	// �˗�No�A����No�̃u���b�N1�̊J�n�ʒu
#define GD105_POS_SRCNO2		5	// �˗�No�A����No�̃u���b�N2�̊J�n�ʒu
#define GD105_POS_DESTNO1		0	// �˗�No�A����No�̕ϊ���̃u���b�N1�̊J�n�ʒu
#define GD105_POS_DESTNO2		3	// �˗�No�A����No��"00"�̊J�n�ʒu
#define GD105_POS_DESTNO3		5	// �˗�No�A����No�̕ϊ���̃u���b�N1�̊J�n�ʒu

//  �p�����[�^�t�@�C���L�[������
#define GD105_PRM_DBNAME		"DBNAME"		// �f�[�^�x�[�X�ڑ���
#define GD105_PRM_DBUSER		"DBUSER"		// ���O�C�����[�U
#define GD105_PRM_DBPAWD		"DBPAWD"		// ���O�C���p�X���[�h
#define GD105_PRM_DIR_DATAFILE	"DIR_DATAFILE"	// �񍐃f�[�^�t�@�C���o�̓f�B���N�g��
#define GD105_PRM_DIR_TODAY		"DIR_TODAY"		// �]���f�[�^�t�@�C���o�̓f�B���N�g��
#define GD105_PRM_DIR_OLDDAY	"DIR_OLDDAY"	// �]���f�[�^�t�@�C���ߋ��f�B���N�g��
#define GD105_PRM_DIR_SENDFILE	"DIR_SENDFILE"	// �]���f�[�^�t�@�C�����M�p�f�B���N�g��
#define GD105_PRM_DIR_SENDREQ	"DIR_SENDREQ"	// �]���f�[�^�t�@�C��REQUEST�f�B���N�g��
#define GD105_PRM_DIR_SENDOK	"DIR_SENDOK"	// �]���f�[�^�t�@�C��OK�f�B���N�g��
#define GD105_PRM_DIR_SENDERR	"DIR_SENDERR"	// �]���f�[�^�t�@�C��ERR�f�B���N�g��
#define GD105_PRM_DATAFLOWID	"DATAFLOWID"	// �f�[�^�t���[�h�c
#define GD105_PRM_SENDID_MOTO	"SENDID_MOTO"	// ���M���h�c
#define GD105_PRM_SENDID_SAKI	"SENDID_SAKI"	// ���M��h�c
#define GD105_PRM_SLEEP_SEC		"SLEEP_SEC"		// �X���[�v���ԁi�b�j
#define GD105_PRM_SHM_KEY		"SHM_KEY"		// ���L�������L�[
#define GD105_PRM_FILE_DBG		"FILE_DBG_NSME"	// �f�o�b�O
#define GD105_PRM_FILE_TR		"FILE_TR_NAME"	// �g���[�X
#define GD105_PRM_FILE_ACS		"FILE_ACS_NAME"	// �A�N�Z�X
#define GD105_PRM_FILE_ERR		"FILE_ERR_NAME"	// �G���[
#define GD105_PRM_UP_ID			"UPDATE_ID"		// �X�V��ID
#define GD105_PRM_UP_NM			"UPDATE_NM"		// �X�V��
#define GD105_PRM_PROC_MD		"PROC_MD"		// ���s���[�h
#define GD105_PRM_COMMIT_SU		"COMMIT_SU"		// 1.13 ADD KEKKA COMMIT

//�f�[�^���ʎq
#define GD105_FILE_HEADERID		"HD"
#define GD105_FILE_TRAILERID	"TR"
#define GD105_FILE_DATAID		"R1"
#define GD105_FILE_LINEFEED		'\n'
#define GD105_FILE_FILLER_SIZE	121
#define GD105_FILEEXT_DATA		".dat"
#define GD105_FILEEXT_TEMP		".tmp"
#define GD105_REC_LOOP_MAX		6
#define GD105_DATA_CHAR0		'0'
#define GD105_DATA_SPACE		' '
#define GD105_DATA_STR00		"00"

#define GD105_DB_HKKJKFLG_CHUU		"1 "
#define GD105_DB_HKKJKFLG_ERRFILE	"4 "
#define GD105_DB_HKKJKFLG_OK		"2 "
#define GD105_DB_HKKJKFLG_OK_DBERR	"9 "
#define GD105_DB_HKKJKN_CTRLNO		'1'
#define GD105_DB_HKKJKN_PLTNO		'2'
#define GD105_DB_HKKJKN_KNSSEQ		'3'
#define GD105_DB_HKKJKN_IRINO		'4'
#define GD105_DB_HKKJKN_KNTNO		'5'
#define GD105_DB_HKKJKN_RESEND		'8'
#define GD105_DB_KNSFLG_HORYU		'H'
#define GD105_DB_KNSFLG_DONE		'E'
#define GD105_DB_KKASSFLG_MAX		'9'
#define GD105_DB_SSNTUBN_MAX		9999
// 2006-04-20 H.Suyama Add Start
#define GD105_DB_HKKKBN_CYUU		'2'
#define GD105_DB_HKKKBN_LAST		'1'
#define GD105_DB_KKAJKCD_CYUU		'1'
#define GD105_DB_KKAJKCD_LAST		'3'
// 2006-04-20 H.Suyama Add End

#define GD105_DB_HKKERRCODE_HKKJKN	"00000001"
#define GD105_DB_HKKERRCODE_HKKKNRI	"00000002"
#define GD105_DB_HKKERRCODE_CREATE	"00000003"
#define GD105_DB_HKKERRCODE_RESEND	"00000004"
#define GD105_DB_HKKERRCODE_SEQMAX	"00000005"
#define GD105_DB_HKKERRCODE_NODATA	"00000006"
// 2006-04-06 H.Suyama Add Start
#define GD105_DB_HKKERRCODE_DBACS	"00000007"
#define GD105_DB_HKKERRCODE_HULFT	"00000008"
// 2006-04-06 H.Suyama Add End

#define MYAPP_LOG_ERRCODE_NON		"00000000"
#define MYAPP_LOG_ERRCODE_APP		"010"
#define MYAPP_LOG_ERRCODE_DB		"020"
#define MYAPP_LOG_ERRCODE_ETC		"0Z0"

// �f�t�H���gINI�t�@�C��
//#define MYAPP_INIFILE "$HOME/appl/src/houkoku/GD105/GD105.ini"
#define MYAPP_INIFILE "$HOME/bin/GD105.ini"
// ���O�t�@�C��INI�t�@�C��
//#define MYAPP_LOGINIFILE "$HOME/appl/src/houkoku/GD105/GD105_LOG.ini"
#define MYAPP_LOGINIFILE "$HOME/bin/GD105_LOG.ini"

/******************************************************************************/
/* �\���̒�`																  */
/******************************************************************************/
// �t�@�C���w�b�_
typedef struct {
	char	cID[2];				// ���R�[�h���ʎq
	char	cSendToID[8];		// ���M��ID
	char	cSendFromID[8];		// ���M��ID
	char	cSendDate[8];		// ���M�������N����
	char	cSeqNo[4];			// �ʔ�
	char	cDataFlowID[10];	// �ް��۰ID
	char	cParam1[128];		// ���Ұ�1
	char	cParam2[128];		// ���Ұ�2
	char	cReserve[728];		// �\��
} FILEHEADER;

// �t�@�C���g���[��
typedef struct {
	char	cID[2];				// ���R�[�h���ʎq
	char	cSendToID[8];		// ���M��ID
	char	cSendFromID[8];		// ���M��ID
	char	cSendDate[8];		// ���M�������N����
	char	cSeqNo[4];			// �ʔ�
	char	cDataFlowID[10];	// �ް��۰ID
	char	cPhysicalCnt[8];	// ����ں��ތ���
	char	cRecCnt1[8];		// �_��ں��ތ����P
	char	cRecCnt2[8];		// �_��ں��ތ����Q
	char	cRecCnt3[8];		// �_��ں��ތ����R
	char	cRecCnt4[8];		// �_��ں��ތ����S
	char	cRecCnt5[8];		// �_��ں��ތ����T
	char	cRecCnt6[8];		// �_��ں��ތ����U
	char	cRecCnt7[8];		// �_��ں��ތ����V
	char	cRecCnt8[8];		// �_��ں��ތ����W
	char	cRecCnt9[8];		// �_��ں��ތ����X
	char	cRecCnt10[8];		// �_��ں��ތ����P�O
	char	cRecCnt11[8];		// �_��ں��ތ����P�P
	char	cRecCnt12[8];		// �_��ں��ތ����P�Q
	char	cRecCnt13[8];		// �_��ں��ތ����P�R
	char	cRecCnt14[8];		// �_��ں��ތ����P�S
	char	cRecCnt15[8];		// �_��ں��ތ����P�T
	char	cReserve[856];		// �\��
} FILETRAILER;

// �񍐃f�[�^�\����
typedef struct {
	char	cUTKYMD[8];		// �a�l�k��t�N����
							// [YYYYMMDD]�ɕϊ����Đݒ�
	char	cIRINO[11];		// �˗����m���D
							// ������11�������̂悤�ɕϊ�
							// (�ϊ��O)[1][2][3][4][5][6][7][8][9][10][11]
							// (�ϊ���)[3][4][5] 0  0 [6][7][8][9][10][11]
	char	cKMKCD[7];		// ���ڃR�[�h
	char	cKNTNO[11];		// ���̂m���D
							// ������11�������̂悤�ɕϊ�
							// (�ϊ��O)[1][2][3][4][5][6][7][8][9][10][11]
							// (�ϊ���)[3][4][5] 0  0 [6][7][8][9][10][11]
	char	cOYAKMKCD[7];	// �e���ڃR�[�h
	char	cKNSKKA1[8];	// �������ʂP
							// �E����8����ݒ�i��ۻ��ڽ����j
	char	cKNSKKA2[8];	// �������ʂQ
							// ������8����ݒ�i2�o�C�g�����ɒ��ӂ���j
	char	cKNSKKA2KBN;	// ���ʂQ�敪
							// ������1����ݒ�
	char	cKKAHSKCD[3];	// ���ʕ⑫�R�[�h
	char	cKKACMT1[4];	// ���ʃR�����g�P
							// �E����4����ݒ�
	char	cKKACMT2[4];	// ���ʃR�����g�Q
							// �E����4����ݒ�
	char	cIJKBNM;		// �ُ�l�敪�i�j�j
	char	cIJKBNF;		// �ُ�l�敪�i���j
	char	cIJKBNN;		// �ُ�l�敪�i�s���j
	char	cSDI[3];		// �w���i�r�c�P�j
	char	cKJNO[3];		// ��l�m���D
	char	cLABOARVDT[8];	// ���{����
							// �󔒂�ݒ�
	char	cKNSENDDT[8];	// ���������\���
							// �󔒂�ݒ�
	char	cEXTKKADBIDCD;	// �g������DB���ʺ���
							// [0]��ݒ�
	char	cKKAJKCD;		// ���ʏ󋵃R�[�h
	char	cPNCRGFLG;		// �p�j�b�N�����W�t���O
	char	cSMPCD[4];		// �v�r�R�[�h
							// �E����4����ݒ�
	char	cKNSSEQ[6];		// �����r�d�p
							// ���l�𕶎���ɕϊ���A�E����6����ݒ�B
							// �i��ۻ��ڽ�Ȃ��j
	char	cZRCD[3];		// ����ޗ��R�[�h
							// �E����3���ݒ�
	char	cKKAKSFLG;		// ���ʊ��Z�t���O
	char	cKKASSFLG;		// ���ʏC���t���O
	char	cHSYKFLG;		// ��Ɖ�t���O
	char	cHSKFLG;		// �񐿋��敪
	char	cHHKKFLG;		// ��񍐃t���O
	char	cKNSIDCD;		// �������ʃR�[�h
							// [0]��ݒ�
	char	cLBCD[3];		// �������{���{�R�[�h
	char	cRESERVE[28];	// �\��t�B�[���h
							// �󔒂�ݒ�
} GD105Rec;

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
} GD105Env;

/******************************************************************************/
/* �O���[�o���錾															  */
/******************************************************************************/
// extern
extern      char        G_msg[256]; // 1.06 ADD LogMessage

/******************************************************************************/
/* �v���g�^�C�v�錾															  */
/******************************************************************************/
void GD105ConvTimestamp(ULONG ulTm, char *pDest);
int GD105ConvNumber(char *pDest, char *pSrc);
int GD105CopyFromLeft(char *pDest, char *pSrc, int iSize, BOOL bMbFlg);
int GD105CopyFromRight(char *pDest, char *pSrc, int iSize, BOOL bMbFlg);

int initFunction( int argc, char *argv[], GD105Env *pEnv );
int mainFunction( GD105Env *pEnv );
void endFunction( GD105Env *pEnv );
int GD105MakeData(Kekka *pKekka, char *pLBCD, GD105Rec *pGD105Rec);
int GD105DataFileFilter(struct dirent *pDirEnt);
int GD105WriteFile(FILE *fp, GD105Rec *pGD105Rec, int iRecCnt);

//2006.12.08 Kim Jinsuk �c�a�G���[�ُ펞�I��
int GD105CreateFile(GD105Env *pEnv, Sysknrmst *pSysknrmst, Kekka *pKekkaArrayOut, int iKekkaNumOut, int *piHkkssknsu, int *piHkkhrysu, char *pFileName,int *sqlErrorFlag);
// 2006-04-06 H.Suyama Change Start

//2006-07-06 CHG Osada �t�@�C�����������@�ύX
int GD105CreateHULFTFile(GD105Env *pEnv, Sysknrmst *pSysknrmst, Hkkknri *pHkkknri, char *pDataFile, int iLogicalCnt, Hkkknri *pHkkknriArrayOut);

//2014-01-15 sekiya �t�@�C���쐬�ƃt���O�X�V�𕪂���Ή�
int GD105UpdateKekka(GD105Env *pEnv, Sysknrmst *pSysknrmst, Kekka *pKekkaArrayOut, int iKekkaNumOut, int *sqlErrorFlag);

// 2006-04-06 H.Suyama Change End
int GD105ResendFile(GD105Env *pEnv, Sysknrmst *pSysknrmst, Hkkknri *pHkkknri);
void GD105UpdateHkkknriSts( Hkkknri *pHkkknri, char *pHkkjkflg, char *pHkkerrcode );

//  ���L����������֐�
static  int sFncShmCrt ( GD105Env * );
static  int sFncShmGet ( GD105Env * , int *);
static  int sFncShmDel ( GD105Env * );
//  �g���[�X�p
static  void	_sFncEnvDip ( GD105Env * );
//���O�֐�
void sFncPutLog( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... );
#endif
/** End of File ***************************************************************/
