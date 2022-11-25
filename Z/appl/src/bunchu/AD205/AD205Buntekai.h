/********************************************************************/
/*																	*/
/*		�a�l�k�l���������V�X�e��									*/
/*																	*/
/*		�V�X�e����	�F������V�X�e��								*/
/*		�t�@�C����	�FAD205Buntekai.h								*/
/*		�T�v		�F�����W�J�����w�b�_�[�t�@�C��					*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	�쐬��			���O			�C�����e				*/
/* ----------------------------------------------------------------	*/
/*  1.00	2006/01/19		E.Osada			Create					*/
/*  4.01    2009-02-20      K.Ameno         �ً}SUN EOSL�Ή�        */
/********************************************************************/
#ifndef _AD205Buntekai_h
#define _AD205Buntekai_h

/********************************************************************/
/*	�C���N���[�h�錾												*/
/********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iconv.h>
#include <dirent.h>
#include <fcntl.h>
#include <time.h>
#include <stdarg.h>
#include "bmllog.h"
#include "bmlprm.h"
#include "bml_date.h"
#include "Bunchu.h"
#include "A205knja.h"
#include "A205irai.h"
#include "Kmkmst.h"
#include "A205knsgmst.h"
#include "A205zoku.h"
#include "Ninsiki.h"
#include "A205korder.h"
#include "A205realchk.h"
#include "Asyscdlmst.h"
#include "Trmst.h"
//#include "Skchkmst.h"
#include "A205sknchk.h"
#include "Krkmkmst.h"
#include "Kskbrmst.h"
#include "A205rngchk.h"
#include "Sysknrmst.h"
#include "A205Jdkmk.h"
#include "A205kmkmst.h"
#include "A205kjnmst.h"
#include "Calckmkmst.h"
#include "A205wsseq.h"
#include "Rkmst.h"
/******************************************************************************/
/* Define��`                                                                */
/******************************************************************************/
#define MYAPP_APP_NAME          "AD205"
#define RETRY_NAME				"skip_"
#define SKIP_NAME				"zger_"
#define ERR_NAME				"iser_"
#define RETURN_NAME				"RETURN_"
#define BUNCHU_RECV_KIND		"CHK"
#define BUNCHU_RECV_KIND1	"HIBUN"
#define	BUNCHU_SYBT				"R1"
#define	BUNCHU_SYBT_END			"R2"
#define BUNCHU_SYBT_HED			"HD"
#define BUNCHU_SYBT_STP			"TR"
#define BUNCHU_END_OK			"11111"
#define BUNCHU_END_NUM			5
//  �����X�e�[�^�X�R�[�h��`
typedef enum {
	BUNCHU_STSCODE_NORMAL,
	BUNCHU_STSCODE_ERR_USEGE,
	BUNCHU_STSCODE_ERR_PRM_FILE,
	BUNCHU_STSCODE_ERR_PRM_GET,
	BUNCHU_STSCODE_ERR_SHM_AT,
	BUNCHU_STSCODE_ERR_SHM_DT,
	BUNCHU_STSCODE_ERR_SHM_DEL,
	BUNCHU_STSCODE_ERR_SHM_GET,
	BUNCHU_STSCODE_ERR_DIR,
	BUNCHU_STSCODE_ERR_FR_FILE
} BUNCHU_STSCODE ;

//  �G���[�R�[�h��`
#define MYAPP_LOG_ERRCODE_NON       "00000000"
#define MYAPP_LOG_ERRCODE_APP       "010"
#define MYAPP_LOG_ERRCODE_DB        "020"
#define MYAPP_LOG_ERRCODE_ETC       "0Z0"

//	�p�����[�^������
#define	BUNCHU_PRM_DIR_BUNCHU	"DIR_BUNCHU"		//�������
#define	BUNCHU_PRM_DIR_BUNCHU_OK	"DIR_BUNCHU_OK"		//����������
#define	BUNCHU_PRM_DIR_BUNCHU_NG	"DIR_BUNCHU_NG"		//�������G���[
#define BUNCHU_PRM_DIR_TRAY		"DIR_TRAY"			//�g���[���
#define BUNCHU_PRM_DIR_TRAY_OK	"DIR_TRAY_OK"		//�g���[������
#define BUNCHU_PRM_DIR_TRAY_NG	"DIR_ERR_LST"		//�G���[���X�g
#define	BUNCHU_PRM_DIR_LOG		"DIR_LOG"			//���O
#define	BUNCHU_PRM_FILE_DBG		"FILE_DBG_NSME"		//�f�o�b�O
#define	BUNCHU_PRM_FILE_TR		"FILE_TR_NAME"		//�g���[�X
#define	BUNCHU_PRM_FILE_ACS		"FILE_ACS_NAME"		//�A�N�Z�X
#define	BUNCHU_PRM_FILE_ERR		"FILE_ERR_NAME"		//�G���[
#define BUNCHU_PRM_UP_ID		"UPDATE_ID"			//�X�V��ID
#define BUNCHU_PRM_UP_NM		"UPDATE_NM"			//�X�V��
#define BUNCHU_PRM_PROC_MD		"PROC_MD"			//���s���[�h

#define BUNCHU_PRM_DB			"DBNAME"
#define BUNCHU_PRM_UID			"DBUSER"
#define BUNCHU_PRM_PWD			"DBPAWD"
#define BUNCHU_PRM_LBCD			"LABOCD"
#define BUNCHU_PRM_STCD			"SATECD"

#define	BUNCHU_PRM_SHM_KEY			"SHM_KEY"
#define	BUNCHU_PRM_SLEEP_SEC		"SLEEP_SEC"

//	�f�B���N�g���i�[�T�C�Y
#define	BUNCHU_DIR_SIZE			(512)

//	�t�@�C�����T�C�Y
#define	BUNCHU_FILE_SIZE			(1024)

//	���L�������T�C�Y
#define	BUNCHU_SHM_SIZE			sizeof ( int )

//	��M�t�@�C���֘A
#define	BUNCHU_RECV_SFX			".dat"
#define	BUNCHU_RECV_RECSIZE		(1024)

//�������t�@�C���̍��ڃR�[�h�擪�ʒu
#define BUNCHU_KMK_ADR			(101)

//���ڃR�[�h����
#define BUNCHU_KMK_SZ				(7)

//���ڃR�[�hMAX
#define BUNCHU_KMK_MAX				(64)

//�g���[�����b�N�|�W�V������
#define	MAXPOS	10
#define	MAXPOSOLD	100
#define MAXRACK 20

//���O�t�@�C��INI�t�@�C��
#define MYAPP_LOGINIFILE "/home/kea00sys/bin/AD205_LOG.ini"
//�\�[�g�L�[INI�t�@�C��
#define MYAPP_SORTINIFILE "/home/kea00sys/bin/AD205_SORT.ini"

/* 2009-02-20 �ً}SUN EOSL�Ή� INS START */
#define TRID_BLANK "____0000"
/* 2009-02-20 �ً}SUN EOSL�Ή� INS END */


//�W�J�G���[���X�g�p
#define SYBT_BUNCH		"�������"
/******************************************************************************/
/* �\���̒�`                                                                 */
/******************************************************************************/
// �v���O�������\����
typedef struct {
	char	sData[5];
	char	sKey[4];
} BUNSORT;
struct	bunchuEnv	{
	BMLPRM	*bp	;
	char	*pcFielNamePRM ;

	int		shm_Id ;

	key_t	shm_Key ;
	int		sleep_Sec ;
	char	cDirBunchu[BUNCHU_DIR_SIZE];		// �������ʏ��t�@�C���i�[�f�B���N�g��
	char	cDirBunchuOK[BUNCHU_DIR_SIZE];		// �������ʏ��t�@�C���i�[�f�B���N�g��(����)
	char	cDirBunchuNG[BUNCHU_DIR_SIZE];		// �������ʏ��t�@�C���i�[�f�B���N�g��(�G���[)
	char	cDirTryinfo[BUNCHU_DIR_SIZE];		//�g���[No���t�@�C���i�[�f�B���N�g��
	char	cDirTryinfoOK[BUNCHU_DIR_SIZE];		//�g���[No���t�@�C���i�[�f�B���N�g��(����)
	char	cDirTryinfoNG[BUNCHU_DIR_SIZE];		//�G���[���X�g�t�@�C���i�[�f�B���N�g��
	char	cDirLog[BUNCHU_DIR_SIZE];			// ���O�t�@�C���i�[�f�B���N�g��
	char	cDebugLogName[BUNCHU_FILE_SIZE];	// �f�o�b�O���O�t�@�C����
	char	cTraceLogName[BUNCHU_FILE_SIZE];	// �g���[�X���O�t�@�C����
	char	cAccessLogName[BUNCHU_FILE_SIZE];	// �A�N�Z�X���O�t�@�C����
	char	cErrorLogName[BUNCHU_FILE_SIZE];	// �G���[���O�t�@�C����
	int		proc_mode;							//�������[�h	0�F�ߓn��	1�F������
	char	cUpdateId[128];						//�X�V��ID
	char	cUpdateName[128];					//�X�V��
	char	cLogName[128];						//���O
	char	sPutDir[BUNCHU_DIR_SIZE];
	char	sDbName[BUNCHU_FILE_SIZE];
	char	sDbUser[BUNCHU_FILE_SIZE];
	char	sDbPswd[BUNCHU_FILE_SIZE];
	char	sLbcd[BUNCHU_FILE_SIZE];
	char	sSateid[BUNCHU_FILE_SIZE];
	int		pSortNo;
	BUNSORT	*pSort;
} ;

// �������ʏ��t�@�C��
typedef struct {
	char	sDataSybt[2];		//�f�[�^���ʎq
	char	sTranId[6];			//�g�����U�N�V����ID
	char	sRackId[8];			//�A�b�Z�C���b�NID
	char	sUkebi[8];			//��t�N����
	char	sIchi[3];			//�ʒu�P
	char	sUkebiBML[8];		//BML��t��
	char	sIraiNo[11];		//�˗���No
	char	sKentaiNo[11];		//����No
	char	sKenChkChar[2];		//���̃`�F�b�N����
	char	sWStandoku[1];		//WS�P��
	char	sSexKbn[1];			//���ʋ敪
	char	sAgeKbn[1];			//�N��敪
	char	sAge[3];			//�N��
	char	sChikuTm[4];		//�{�A����
	char	sChikuTmTni[1];		//�{�A����(�P��)
	char	sChikuRyo[5];		//�{�A��
	char	sChikuRyoTani[1];	//�{�A��(�P��)
	char	sSisetuCd[7];		//�{�݃R�[�h
	char	sEigyoCd[3];		//�c�ƃR�[�h
	char	sMotoKenRk[8];		//�����̃��b�NID
	char	sMotoKenPos[3];		//�����̃|�W�V����
	char	sWS[4];				//WS�R�[�h
	char	sKmkCd64[7];		//�������ڃR�[�h64
	char	sKmkCd63[7];		//�������ڃR�[�h63
	char	sKmkCd62[7];		//�������ڃR�[�h62
	char	sKmkCd61[7];		//�������ڃR�[�h61
	char	sKmkCd60[7];		//�������ڃR�[�h60
	char	sKmkCd59[7];		//�������ڃR�[�h59
	char	sKmkCd58[7];		//�������ڃR�[�h58
	char	sKmkCd57[7];		//�������ڃR�[�h57
	char	sKmkCd56[7];		//�������ڃR�[�h56
	char	sKmkCd55[7];		//�������ڃR�[�h55
	char	sKmkCd54[7];		//�������ڃR�[�h54
	char	sKmkCd53[7];		//�������ڃR�[�h53
	char	sKmkCd52[7];		//�������ڃR�[�h52
	char	sKmkCd51[7];		//�������ڃR�[�h51
	char	sKmkCd50[7];		//�������ڃR�[�h50
	char	sKmkCd49[7];		//�������ڃR�[�h49
	char	sKmkCd48[7];		//�������ڃR�[�h48
	char	sKmkCd47[7];		//�������ڃR�[�h47
	char	sKmkCd46[7];		//�������ڃR�[�h46
	char	sKmkCd45[7];		//�������ڃR�[�h45
	char	sKmkCd44[7];		//�������ڃR�[�h44
	char	sKmkCd43[7];		//�������ڃR�[�h43
	char	sKmkCd42[7];		//�������ڃR�[�h42
	char	sKmkCd41[7];		//�������ڃR�[�h41
	char	sKmkCd40[7];		//�������ڃR�[�h40
	char	sKmkCd39[7];		//�������ڃR�[�h39
	char	sKmkCd38[7];		//�������ڃR�[�h38
	char	sKmkCd37[7];		//�������ڃR�[�h37
	char	sKmkCd36[7];		//�������ڃR�[�h36
	char	sKmkCd35[7];		//�������ڃR�[�h35
	char	sKmkCd34[7];		//�������ڃR�[�h34
	char	sKmkCd33[7];		//�������ڃR�[�h33
	char	sKmkCd32[7];		//�������ڃR�[�h32
	char	sKmkCd31[7];		//�������ڃR�[�h31
	char	sKmkCd30[7];		//�������ڃR�[�h30
	char	sKmkCd29[7];		//�������ڃR�[�h29
	char	sKmkCd28[7];		//�������ڃR�[�h28
	char	sKmkCd27[7];		//�������ڃR�[�h27
	char	sKmkCd26[7];		//�������ڃR�[�h26
	char	sKmkCd25[7];		//�������ڃR�[�h25
	char	sKmkCd24[7];		//�������ڃR�[�h24
	char	sKmkCd23[7];		//�������ڃR�[�h23
	char	sKmkCd22[7];		//�������ڃR�[�h22
	char	sKmkCd21[7];		//�������ڃR�[�h21
	char	sKmkCd20[7];		//�������ڃR�[�h20
	char	sKmkCd19[7];		//�������ڃR�[�h19
	char	sKmkCd18[7];		//�������ڃR�[�h18
	char	sKmkCd17[7];		//�������ڃR�[�h17
	char	sKmkCd16[7];		//�������ڃR�[�h16
	char	sKmkCd15[7];		//�������ڃR�[�h15
	char	sKmkCd14[7];		//�������ڃR�[�h14
	char	sKmkCd13[7];		//�������ڃR�[�h13
	char	sKmkCd12[7];		//�������ڃR�[�h12
	char	sKmkCd11[7];		//�������ڃR�[�h11
	char	sKmkCd10[7];		//�������ڃR�[�h10
	char	sKmkCd9[7];			//�������ڃR�[�h9
	char	sKmkCd8[7];			//�������ڃR�[�h8
	char	sKmkCd7[7];			//�������ڃR�[�h7
	char	sKmkCd6[7];			//�������ڃR�[�h6
	char	sKmkCd5[7];			//�������ڃR�[�h5
	char	sKmkCd4[7];			//�������ڃR�[�h4
	char	sKmkCd3[7];			//�������ڃR�[�h3
	char	sKmkCd2[7];			//�������ڃR�[�h2
	char	sKmkCd1[7];			//�������ڃR�[�h1
	char	sBunKiId[3];		//�����@ID
	char	sStsFlg[1];			//��ԃt���O
	char	sKnsSyrui[1];		//�������
	char	sChiKenFlg[1];		//�����t���O
	char	sKnkyFlg[1];		//����E�ً}�t���O
	char	sBunKekka[1];		//��������
	char	sFiller[466];		//�t�B���[
	char	sLF[1];				//�I�[�q(LF)
}	Flbun;

//�g���[���
typedef struct {
	char	sUkeDate[9];
	char	sKentaiID[14];
	char	sIraiNo[14];
	char	sKenSybt[4];
} POS;
typedef struct {
	char	sStDate[9];
	char	sRackID[9];
/* 2009-02-20 �ً}SUN EOSL�Ή� INS START */
	char	sPutDir[BUNCHU_DIR_SIZE];
/* 2009-02-20 �ً}SUN EOSL�Ή� INS END */
	int iMaxSeq;
	int iMinSeq;
	int iKntSuu;
	POS strPosInfo[MAXPOS+1];
} RACK;
typedef struct {
	char	sTryID[9];
	char	sStDate[9];
	char	sPutDir[BUNCHU_DIR_SIZE];
	int iMaxSeq;
	int iMinSeq;
	int iKntSuu;
	POS strPosInfo[MAXPOSOLD+1];
}TRAY;

/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/

/******************************************************************************/
/* �v���g�^�C�v�錾                                                           */
/******************************************************************************/
// �������W�J����
int initFunction( int, char **, struct bunchuEnv * );
int mainFunction( struct bunchuEnv * );
void endFunction( struct bunchuEnv * );
int dBunchu_ins( struct bunchuEnv *, char *, RACK **s, int *, char *, int );
static int sFncTrFileRead( struct bunchuEnv *, char *, Flbun * );
static char *sFncTrFileToken( char *, char * );
static int sFncFileFillter( struct dirent * );
int ABunGetKnsgrp( Bunchu *strBunchu, Kanjya *strKanjya, char *sKmkcd, char *sKnsgrp );
// 3.02 int AbunInsZokusei( struct bunchuEnv *pst_Env, Bunchu *strBunchu, Kanjya *strKanjya );
int AbunInsZokusei( struct bunchuEnv *pst_Env, Bunchu *strBunchu, Kanjya *strKanjya , int);
//3.02 int AbunInsNinsiki( struct bunchuEnv *pst_Env, Bunchu *strBunchu, int);
int AbunInsNinsiki( struct bunchuEnv *pst_Env, Bunchu *strBunchu, int, int);
int AbufInsOrder( struct bunchuEnv *pst_Env, Irai *pIrai, Bunchu *pBun, Kanjya *pKan, Kenorder *pOrder);
int AbunInsChk( struct bunchuEnv *pst_Env, Kenorder *pOrder, Kanjya *pKan);
int AerrFilePut( struct bunchuEnv *pEnv, char *sData );
int AerrFilePut1( struct bunchuEnv *pEnv, char *sData );
int AerrFilePut2( struct bunchuEnv *pEnv, char *sData );
int AerrFilePut3( struct bunchuEnv *pEnv, char *sData );
int AerrFilePut4( struct bunchuEnv *pEnv, char *sData, char * );
int AgetSortInfo(BUNSORT **strBun );
int AbunGetSort(struct bunchuEnv *pst_Env, char *sId, char flg );
int dBunEnd( struct bunchuEnv *pst_Env, char *sTrId );
void nowdateget1( char *sysdttm );
int ADateChk( char *sDate );
int ATimeChk( char *sTime );
void ABunchuChk( Bunchu *pBunch );
void AKenzokChk( Kenzok *pKenzok );
void ANinsikiChk( Ninsiki *pNinsiki );
void AKenorderChk( Kenorder *pKen );
void ARealchkChk( Realchk  *pReal );
int     sj2euc(char *, char *, int);
int ABunJido( struct bunchuEnv *pst_Env, Irai *pIrai, Bunchu *pBun, Kanjya *pKan, Kenorder *pOrder, int iLine, int Nflg );
int getKnsKaisibi(char *sKnsgrp, char *sDateK, char *sDateH );
int getShoribi( char *sLbcd, char *sSatecd, char *sSyri );
int GetKjnNo(char *, char *, char *, char, char *, char *, int *);
//2.01 DELL int chkBunchu( struct bunchuEnv *, int, Bunchu *, char *);
int chkBunchu( struct bunchuEnv *, int, Bunchu *, char *, int);
/* 2009-02-20 �ً}SUN EOSL�Ή� INS START */
//int insWsseqknri( char *sSriymd, char *sKnsgrp, char *sTrid, int iKntno, int iMinSeq, int iMaxSeq );
int sFncChkDigit( char * );
/* 2009-02-20 �ً}SUN EOSL�Ή� INS END */
//  ���L����������֐�
static  int sFncShmCrt ( struct bunchuEnv * ) ;
static  int sFncShmGet ( struct bunchuEnv * , int *) ;
static  int sFncShmDel ( struct bunchuEnv * ) ;
//  �g���[�X�p
static  void    _sFncEnvDip ( struct bunchuEnv * ) ;
//���O�֐�
void sFncPutLog( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... );
void sFuncPutErrlist( struct bunchuEnv *, char *, int, char *, char *, char *, 
		char *, char *, char *, ... );
#endif
/** End of File ***************************************************************/
