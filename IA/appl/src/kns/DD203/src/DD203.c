/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FDD203.c                                                      */
/* �@�T�@�@�@�v�FLST008�ʐM�E���ʏo�� 	                                      */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/31     A.Yamada       �V�K�쐬                           */
/*  1.01     2006/05/17     S.Nagata       �^���d���𔭐������A�e�X�g���s���� */
/*                                         �`�F�b�N�T���̃`�F�b�N�������C��   */
/*                                         �`�F�b�N�T��"ZZ"�ŗ���d���́A     */
/*                                         �^�������d���Ƃ��A�`�F�b�N���s��Ȃ� */
/* -------------------------------------------------------------------------- */
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  2.00     2008/09/25     K.Ameno        X-M�Ή�����                        */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

#include "DD203.h"
#include "Socket.h"
#include "SndData.h"
#include "RcvData.h"
#include "Connect.h"
#include "GetKenorder.h"
#include "OutputKekka.h"
#include "OutputCtrlkka.h"
#include "GetMaster.h"
// Add 2023.05.23 Hanyu
#include "kns_common.h"

/**********************************************************************/
/*  �����֐��錾                                                      */
/**********************************************************************/
void InitFunction(char*);							/* ���������� */
int GetIniPrm( char* );								/* �ݒ�t�@�C���擾���� */
int	GetMechmst(void);
int	GetZairmst(void);
int	GetKmkmst(void);

void EndFunction(void);								/* �I������ */
void sigcatch(int sig);								/* �V�O�i����M */
void SetLogDat(LOG_TRCKIND,char*,char*,char*,char*,char*,char*);
													/* ���O�o�̓f�[�^�ݒ菈�� */
int MainFunction(void);								/* LST008���� */
void DecodeRcvData(SOCKET_INF*,int);				/* ��M�f�[�^�f�R�[�h���� */
int DecodeRcvMessage(SOCKET_INF*);					/* ��M���b�Z�[�W�f�R�[�h���� */
int DecodeMsgHeaderRcd(SOCKET_INF*,char*);			/* ���b�Z�[�W���o�����R�[�h�f�R�[�h���� */
int DecodePatientInfRcd(SOCKET_INF*,char*);			/* ���ҏ�񃌃R�[�h�f�R�[�h���� */
int DecodeReqInfRcd(SOCKET_INF*,char*);				/* �₢���킹���R�[�h�f�R�[�h���� */
int DecodeTestOrderRcd(SOCKET_INF*,char*);			/* ���ڑI�����R�[�h�f�R�[�h���� */
int DecodeResultRcd(SOCKET_INF*,char*);				/* ���茋�ʃ��R�[�h�f�R�[�h���� */
int DecodeCommentRcd(int,char*);					/* ���߃��R�[�h�f�R�[�h���� */
int DecodeCalbRcd(SOCKET_INF*,char*);				/* �L�����u���[�V�������ʃ��R�[�h�f�R�[�h���� */
int ChkNbkmkcd(SOCKET_INF*,int*);
void SetKekkaData(SOCKET_INF*,int);
void SetKekkaData_Kinkyu(SOCKET_INF*);
void SetKekkaData_NoOrder(SOCKET_INF*);
void SetKekkaData_PCR(SOCKET_INF*,int,int);
void SetKekkaData_ISE(SOCKET_INF*,int);
void SetCtrlkkaData(SOCKET_INF*, char*);
int SetCtrlInf(SOCKET_INF*,char*);
int GetCtrlInf(SOCKET_INF*,char*);
void SetKsbr(SOCKET_INF*);
int SetXbarmInf(SOCKET_INF*,int);
double CalcXbarm(double,int);
void SetXbarmData(SOCKET_INF*);
void SetDivChar(char*);								/* ��؂蕶���ݒ菈�� */
int ChkFieldDiv(char*);								/* �t�B�[���h��؂�`�F�b�N���� */
int ChkFieldDiv2(char*);							/* �t�B�[���h��؂�`�F�b�N����2 */
int ChkCmnt_SpclInst(SOCKET_INF*,char*);			/* Comment or Special Instructions �`�F�b�N���� */
int ChkSeqNum(char*,char*);							/* Sequence Number�`�F�b�N���� */
int ChkStartRangeIdNum(SOCKET_INF*,char*);			/* Statring Range ID Number �`�F�b�N���� */
int ChkInstSpmenId(SOCKET_INF*,char*);				/* Instrument Specimen ID �`�F�b�N���� */
int ChkUniTestId_O(SOCKET_INF*,char*);				/* Universal Test ID(���ڑI��)�`�F�b�N���� */
int ChkActionCode(char*);							/* Action Code �`�F�b�N���� */
int ChkPriority(char*);
int ChkDateTmResRep_LstMod(SOCKET_INF*,char*);		/* Date/Time Results Reported or Last Modified �`�F�b�N���� */
int ChkUniTestId_R(SOCKET_INF*,char*);				/* Universal Test ID(���茋��)�`�F�b�N���� */
int ChkDat_MeasrmntVal(SOCKET_INF*,char*);			/* Data or Measurement Value �`�F�b�N���� */
int ChkResAbnmlFlg(char*);							/* Result Abnormal Flags �`�F�b�N���� */
int ChkResStatus(char*);							/* Result Status �`�F�b�N���� */
int ChkInstIdentif(SOCKET_INF*,char*);				/* Instrument Identification �`�F�b�N���� */
int ChkSubId(char*);								/* Record Type Sub ID�`�F�b�N���� */
int ChkModuleId(SOCKET_INF*,char*);					/* Module ID�`�F�b�N���� */
int ChkTestCode(SOCKET_INF*,char*);					/* Test Code�`�F�b�N���� */
int ChkCalbAlarm(SOCKET_INF*,char*);				/* Calibration Alarm�`�F�b�N���� */
int ChkStdDat(SOCKET_INF* p,char*);					/* STD Dat�`�F�b�N���� */
int ChkCalbAlarm_Ise(int,char*);					/* Calibration Alarm(ISE)�`�F�b�N���� */
int ChkDatAlarm(int,char*);							/* Data Alarm�`�F�b�N���� */
int ChkData(int,char*);								/* Data �`�F�b�N���� */
void StatusCtrl(SOCKET_INF*);						/* ��Ԑ��䏈�� */
void SetTimer(SOCKET_INF*, char, float);			/* �^�C�}�ݒ菈�� */
void ClearSndInf(SOCKET_INF*);						/* ���M���N���A�� */
void ClrSaikenInf(SOCKET_INF*);
void MakeSndData(SOCKET_INF*,char);					/* ���M�f�[�^�쐬���� */
int CnvtFromKmkcd( char*, char* );
int CnvtFromZrcd( char*, char* );
int CnvtFromYtiksbr( char*, char* );
int CnvtFromSbtkbn( char*, char* );
int CnvtFromAge( char*, char* );
int CnvtFromSsymd( char*, char* );
int CnvtFromKntno( char*,char* );
int CnvtFromKjnsriymd( char*, char* );
int MakeFileName( char*, char* , int);
int OutputCtrlSeq(SOCKET_INF*);
int GetNowCtrlNo(SOCKET_INF *, int, char *);
static	void	sBskgokConv ( char *, char * ) ;	/* ADD Haga 2006-08-02 */
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
void SetXSaikenFlg(int saiken, char* knsgrp, char* kmkcd, XBARM_INF* xinf);
int  GetXSaikenFlg(SOCKET_INF* p, char* knsgrp, char* kmkcd, int* module, XBARM_INF* xinf);
int  OutputXbarmInf(char* gouki, XBARM_INF* xinf);
int  InputXbarmInf(char* gouki, XBARM_INF* xinf);
void DelXbarmInf(char* gouki);
char ChkKesseiKmkcd(Kekka* kekka);
/*** X-M�����l�ɕ��ϒl��ݒ肷�� ***/
extern double GetXMavg(char* knsgrp, char* kmkcd);
char* Now(void);
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */
/*	���L����������֐� */
static	int		sFncShmCrt ( int ) ;
static	int		sFncShmGet ( int , int *) ;
static	int		sFncShmDel ( int ) ;

int GetKskRitu(Kskbrmst *key, char *sMax, char *sMin );
int OutputXbarm(SOCKET_INF*);                           /* X-M���ʏo�͏��� */
int R_trim( char* );
int OutputBunsekiOrder(SOCKET_INF*);

//	��l�Č��`�F�b�N
// Add 2023.05.23 Hanyu
int chkLowDataSaiken( SOCKET_INF *p );

/**********************************************************************/
/*  �ϐ��錾                                                          */
/**********************************************************************/
SOCKET_INF sSocketInf;
char	aRcvBuf[255];								/* ��M�f�[�^�o�b�t�@ */
char	aFileNameStr[32];							/* �t�@�C�����G���A */
char	cFieldDivChar;								/* �t�B�[���h��؂蕶�� */
char	cRepeatDivChar;								/* �J��Ԃ���؂蕶�� */
char	cCmpDivChar;								/* �R���|�l���g��؂蕶�� */
char	cEscChar;									/* �G�X�P�[�v���� */
int		iRcvAllMsgCnt;								/* �S��M���b�Z�[�W���`�F�b�N�J�E���^ */
int		iRcvMsgCnt;									/* ��M���b�Z�[�W���`�F�b�N�J�E���^ */
int		iSckConChk;									/* �\�P�b�g�ڑ��`�F�b�N */
time_t	tSckConTm;									/* �\�P�b�g�ڑ��^�C�} */ 
char	aKenorderFolder[256];						/* �t�@�C�����G���A */
char	aKenorderFolder2[256];						/* �t�@�C�����G���A */
char	aKekkaFolder[256];							/* �t�@�C�����G���A */
char	aCtrlkkaFolder[256];						/* �t�@�C�����G���A */
char	aBunsekiOrderFolder[256];					/* �t�@�C�����G���A */
char	aMstFolder[256];							/* �t�@�C�����G���A */
char	aKmkcdTblFolder[256];						/* �t�@�C�����G���A */
char	aLogOutFolder[256];							/* �t�@�C�����G���A */

struct stcLogMember sLog;							/* ���O�o�͏��\���� */
BUNSEKI_INF *sBunsekiInf;
int		iBunsekiNum;								/* ���͋@���@�� */

Kenorder	*pKenorder;
Mechmst		*pMechmst;
int			iMechmstNum;
KINKYU_INF	*pKinkyu;
int			iKinkyuNum;
Kmkmst		*pKmkmst;
int			iKmkmstNum;
Ctrlmst		*pCtrlmst;
int			iCtrlmstNum;
Sysknrmst	sSysknrmst;
Knsgmst		*pKnsgmst;								/* 009 060418 */
int			iKnsgmstNum;							/* 009 060418 */
Kskbrmst *pKskbrmst;								/* ADD E.Osada 2006-07-13 */
int iKskbrmstNum;									/* ADD E.Osada 2006-07-13 */

/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
Xbarmmst    *pXbarmmst;
int         iXbarmmstNum;
Rngchkmst   *pRngchkmst;
int         iRngchkmstNum;
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */

int		EndFlg = 0;
int		shm_Key = 0;
int		shm_Id;

char	aNa_code[6];
char	aK_code[6];
char	aCl_code[6];

char	aMekbn[5];
char	aZrCd[6][4+1];
int		aKskbrt[5];

/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
/*** �ޗ��R�[�h���猟�̎�ʂւ̕ϊ��R�[�h ***/
char	aHnkCd[3][4+1];
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */

//int		iPltUnit;

#define		IPPAN			0
#define		DENKAISITU		1

XBARM_INF	sXbarm_inf[XBARM_ITEM_NUM];
int			iXbarmNum;
int			iXbarmCnt;
#define		X_M_SUM			0
#define		X_M_AVE			1

CTRL_INF	sCtrl_inf[CTRL_ITEM_NUM];
int			iCtrlNum;
int			iCtrlCnt;

int			gCTRL_CHK_TIME;					/* �R���g���[���̓��ꐫ�m�F�͈͎���(��) */

struct MSG_HEADER_RCD sMsgHeaderRcd;		/* ���b�Z�[�W���o�����R�[�h */
struct PATIENT_INF_RCD sPatientInfRcd;		/* ���ҏ�񃌃R�[�h */
struct REQ_INF_RCD sReqInfRcd;				/* �₢���킹��񃌃R�[�h */
struct TEST_ORDER_RCD sTestOrderRcd;		/* ���ڑI�����R�[�h */
struct COMMENT_RCD sCommentRcd;				/* ���߃��R�[�h */
struct RESULT_RCD sResultRcd;				/* ���茋�ʃ��R�[�h */
struct CALB_RCD sCalbRcd;					/* �L�����u���[�V�������ʃ��R�[�h */

/**********************************************************************/
/*                                                                    */
/*   function name : InitFunction                                     */
/*                                                                    */
/*   purpose : ����������                                             */
/*                                                                    */
/*   data : 2005.12.9                                                 */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
void InitFunction( char* prm  )
{
	char name[100];
	int iCnt;

	memset( name,0,100 );

	strcpy( name,INI_FILE_NAME );
	strcat( name,prm );
	strcat( name,".ini" );

	if (ZbmlOpenLog( name )  != 0 ) {
		printf("ZbmlOpenLog Error");
	}

	pKenorder = NULL;
	pMechmst = NULL;;
	iMechmstNum = 0;
	pKinkyu = NULL;
	iKinkyuNum = 0;
	pKmkmst = NULL;
	iKmkmstNum = 0;
	pCtrlmst = NULL;
	iCtrlmstNum = 0;
	pKnsgmst = NULL;		/* 009 060418 */
	iKnsgmstNum = 0;		/* 009 060418 */
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
    pXbarmmst    = NULL;
    iXbarmmstNum = 0;
    pRngchkmst   = NULL;
    iRngchkmstNum= 0;
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */
	memset( &sSysknrmst,0,sizeof(Sysknrmst) );
	memset(aRcvBuf,0,sizeof(aRcvBuf));						/* ��M�f�[�^�o�b�t�@�N���A */
	sSocketInf.iSd = 0;														/*�\�P�b�g�ԍ� */
	memset(sSocketInf.aGouki,0,sizeof(sSocketInf.aGouki));					/* ���@�ԍ� */
	memset(sSocketInf.aHostName,0,sizeof(sSocketInf.aHostName));			/* �z�X�g�� */
	memset(sSocketInf.aRcvTmpMsgBuf,0,sizeof(sSocketInf.aRcvTmpMsgBuf));	/* ��M���b�Z�[�W�R�s�[�G���A */
	memset(sSocketInf.aSndTmpBuf,0,sizeof(sSocketInf.aSndTmpBuf));			/* ���M�f�[�^�ꎞ�o�b�t�@�N���A */
	sSocketInf.cRcvFrameCtrlChar = 0xff;									/* ��M�t���[�����䕶��=�G���[ */
	sSocketInf.cSndFrameCtrlChar = 0xff;									/* ���M�t���[�����䕶��=�G���[ */
	sSocketInf.cFrameNum = 0;												/* �t���[���ԍ� = 0 */
	sSocketInf.cChkRcvData = NO_RCV_DATA;									/* ��M�f�[�^�Ȃ� */
	sSocketInf.cSndDataReq = NO_SND_REQ;									/* ���M�f�[�^�v���Ȃ� */
	sSocketInf.cStatus = STAT_IDLE;											/* STATUS = idle */
	sSocketInf.cChkRcvMessage = MESSAGE_NO_ERR;								/* ��M���b�Z�[�W���� */
	sSocketInf.cChkNextFrame = FRAME_END;									/* �t���[���I�� */
	sSocketInf.cSndFrameSeqNum = 0;											/* ����t���[�����M�J�E���^ */
	sSocketInf.iRcvMsg = MSG_NON;											/* ��M���b�Z�[�W�̈Ӗ� */
	sSocketInf.iSndRetryCnt = 0;											/* �t���[�����M���g���C�J�E���^ */
	memset( sSocketInf.cRackNum,0,sizeof(sSocketInf.cRackNum) );
	memset( sSocketInf.cRackPosNum,0,sizeof(sSocketInf.cRackPosNum) );
	sSocketInf.fTmOutVal = 0;
	sSocketInf.iSndAgainReq = 0;											/* �����N�R���e���V�����Ȃ� */
	memset(sSocketInf.aSndAgainBuf,0,sizeof(sSocketInf.aSndAgainBuf));		/*  �S���M���b�Z�[�W�G���A(�����N�R���e���V����) */
	memset(&sSocketInf.sCtrlkka,0,sizeof(sSocketInf.sCtrlkka));
	memset(&sSocketInf.sSndorder,0,sizeof(sSocketInf.sSndorder));
	sSocketInf.pKekka = NULL;
	sSocketInf.pSaiken = NULL;
	sSocketInf.iKekkaNum = 0;
	sSocketInf.iKekkaCnt = 0;
	sSocketInf.iCtrlSeq = 0;
	sSocketInf.iCtrlSeqCnt = 0;
	/* 2018/05/23 �������R��Ή� */
	memset(&sSocketInf.CtrlInfo,0,sizeof(sSocketInf.CtrlInfo));
	sSocketInf.next = NULL;
	sSocketInf.prev = NULL;
	memset( aFileNameStr,0,sizeof(aFileNameStr) );			/* �t�@�C�����G���A */
	cFieldDivChar = '|';									/* �t�B�[���h��؂蕶�� */
	cRepeatDivChar = '\\';									/* �J��Ԃ���؂蕶�� */
	cCmpDivChar = '^';										/* �R���|�l���g��؂蕶�� */
	cEscChar = '&';											/* �G�X�P�[�v���� */
	iRcvAllMsgCnt = 0;										/* �S��M���b�Z�[�W���`�F�b�N�J�E���^ */
	iRcvMsgCnt = 0;											/* ��M���b�Z�[�W���`�F�b�N�J�E���^ */
	iSckConChk = SCK_CON_NG;								/* �\�P�b�g�ڑ��`�F�b�N */
	tSckConTm = time(NULL);									/* �\�P�b�g�ڑ��^�C�} */
	memset(&sMsgHeaderRcd,0,sizeof(sMsgHeaderRcd));			/* ���b�Z�[�W���o�����R�[�h */
	memset(&sPatientInfRcd,0,sizeof(sPatientInfRcd));		/* ���ҏ�񃌃R�[�h */
	memset(&sReqInfRcd,0,sizeof(sReqInfRcd));				/* �₢���킹���R�[�h */
	memset(&sTestOrderRcd,0,sizeof(sTestOrderRcd));			/* ���ڑI�����R�[�h */
	memset(&sResultRcd,0,sizeof(sResultRcd));				/* ���茋�ʃ��R�[�h */
	memset(&sCommentRcd,0,sizeof(sCommentRcd));				/* ���߃��R�[�h�G���A */
	memset(&aKenorderFolder,0,sizeof(aKenorderFolder));
	memset(&aKenorderFolder2,0,sizeof(aKenorderFolder2));
	memset(&aKekkaFolder,0,sizeof(aKekkaFolder));
	memset(&aCtrlkkaFolder,0,sizeof(aCtrlkkaFolder));
	memset(&aBunsekiOrderFolder,0,sizeof(aBunsekiOrderFolder));
	memset(&aMstFolder,0,sizeof(aMstFolder));
	memset(&aKmkcdTblFolder,0,sizeof(aKmkcdTblFolder));
	memset(&aLogOutFolder,0,sizeof(aLogOutFolder));
	memset(&aNa_code,0,sizeof(aNa_code));
	memset(&aK_code,0,sizeof(aK_code));
	memset(&aCl_code,0,sizeof(aCl_code));
	memset(&aMekbn,0,sizeof(aMekbn));
	memset(aZrCd,0,sizeof(aZrCd));
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
/*** �ޗ��R�[�h���猟�̎�ʂւ̕ϊ��R�[�h ***/
	memset(aHnkCd,0,sizeof(aHnkCd));
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */
	memset(aKskbrt,0,sizeof(aKskbrt));
	for( iCnt=0;iCnt<XBARM_ITEM_NUM;iCnt++ ) {
		memset( &sXbarm_inf[iCnt],0,sizeof(XBARM_INF));
	}
	iXbarmCnt = 0;
	iXbarmNum = 0;

	for( iCnt=0;iCnt<CTRL_ITEM_NUM;iCnt++ ) {
		memset( &sCtrl_inf[iCnt],0,sizeof(CTRL_INF));
	}
	iCtrlCnt = 0;
	iCtrlNum = 0;

	/* ���A���^�C���Č��`�F�b�N�������� */
	RealTimeChkInit();

	/* �ݒ�t�@�C���擾 */
	GetIniPrm( name );
	
	/* �}�X�^���擾 */
	GetMaster();

/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
/*** Xbarm��񂪕ۑ�����Ă���ꍇ�́A�����ōĐݒ肵�Ă���(pltno�̂���) ***/
/*** Connect�̌�łȂ��ƍ��@���ݒ肳��Ȃ����߃t�@�C����������ł��Ȃ�  ***/
    if (InputXbarmInf(sBunsekiInf[0].aGouki, sXbarm_inf) == RTN_OK) {
        iXbarmCnt = sXbarm_inf[0].iXbarmCnt;
        iXbarmNum = sXbarm_inf[0].iXbarmNum;
    }
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */

}
/**********************************************************************/
/*                                                                    */
/*   function name : GetIniPrm                                        */
/*                                                                    */
/*   purpose : �ݒ�t�@�C���擾                                       */
/*                                                                    */
/*   data : 2006.02.27                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int GetIniPrm( char* name )
{
	BMLPRM * bp;
	char cNum[4];
	char str[32];
	char wrk[128]; /* 100 -> 128 Mod Hanyu 2023.05.23 */
	char port[16];
	int	iCnt;
	int	iCnt2;
	int	iCnt3;
	int	iWrk;
	char	wk[16];
	int iWtimer;    /* ADD E.Osada 2006-08-21 */
	int		nRet;	/* Add Hanyu 2023.05.23 */

	memset( wrk,0,sizeof(wrk) );
	printf( "name:%s\n",name );

	bp = ZbmlPrmOpen( name );
	ZbmlPrmGetVal(bp, "GetKenorderFolder", aKenorderFolder);
	ZbmlPrmGetVal(bp, "GetKenorderFolder2", aKenorderFolder2);
	ZbmlPrmGetVal(bp, "GetKekkaFolder", aKekkaFolder);
	ZbmlPrmGetVal(bp, "GetCtrlkkaFolder", aCtrlkkaFolder);
	ZbmlPrmGetVal(bp, "GetMstFolder", aMstFolder);
	ZbmlPrmGetVal(bp, "GetKmkcdTblFolder", aKmkcdTblFolder);
	ZbmlPrmGetVal(bp, "GetLogOutFolder", aLogOutFolder);
	ZbmlPrmGetVal(bp, "GetBunsekiOrderFolder", aBunsekiOrderFolder);
	if ( ZbmlPrmGetVal ( bp, "SHM_KEY", wk ) != 0 ) {
		/* �ُ�I��	LOG */
		return ( -1 ) ;
	}
	shm_Key = atoi ( wk ) ;
	if ( sFncShmCrt ( shm_Key ) < 0 ) {
		sFncSyslog ( TRCKIND_ERROR, "GetIniPrm()", "SHM_KEY�l���ُ�ł��B" ) ;
		return ( -1 ) ;
	}
	
	/* �R���g���[���m��͈͎��� */
	if ( ZbmlPrmGetVal ( bp, "CTRL_CHK_TIME", wk ) != 0 ) {
		/* �ُ�I��	LOG */
		return ( -1 ) ;
	}
	gCTRL_CHK_TIME = atoi ( wk ) ;
	
	/* �ޗ��R�[�h�擾 */
	ZbmlPrmGetVal(bp, "SBT_1", aZrCd[0]);
	ZbmlPrmGetVal(bp, "SBT_2", aZrCd[1]);
	ZbmlPrmGetVal(bp, "SBT_3", aZrCd[2]);
	ZbmlPrmGetVal(bp, "SBT_4", aZrCd[3]);
	ZbmlPrmGetVal(bp, "SBT_5", aZrCd[4]);
	ZbmlPrmGetVal(bp, "SBT_6", aZrCd[5]);

/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
/*** �ޗ��R�[�h���猟�̎�ʂւ̕ϊ��R�[�h ***/
	ZbmlPrmGetVal(bp, "ZCD_1",   aHnkCd[0]);
	ZbmlPrmGetVal(bp, "ZCD_2_1", aHnkCd[1]);
	ZbmlPrmGetVal(bp, "ZCD_2_2", aHnkCd[2]);
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */

	/* ��ߔ{���擾 */
	memset( wrk,0,sizeof(wrk) );
	ZbmlPrmGetVal(bp, "KSKBRT_1", wrk);
	aKskbrt[0] = atoi(wrk);
	memset( wrk,0,sizeof(wrk) );
	ZbmlPrmGetVal(bp, "KSKBRT_2", wrk);
	aKskbrt[1] = atoi(wrk);
	memset( wrk,0,sizeof(wrk) );
	ZbmlPrmGetVal(bp, "KSKBRT_3", wrk);
	aKskbrt[2] = atoi(wrk);
	memset( wrk,0,sizeof(wrk) );
	ZbmlPrmGetVal(bp, "KSKBRT_4", wrk);
	aKskbrt[3] = atoi(wrk);
	memset( wrk,0,sizeof(wrk) );
	ZbmlPrmGetVal(bp, "KSKBRT_5", wrk);
	aKskbrt[4] = atoi(wrk);

	ZbmlPrmGetVal(bp, "NA_CODE", aNa_code);
	ZbmlPrmGetVal(bp, "K_CODE", aK_code);
	ZbmlPrmGetVal(bp, "CL_CODE", aCl_code);

	memset( wrk,0,sizeof(wrk) );
	ZbmlPrmGetVal(bp, "MEKBN", wrk);
	strcpy( aMekbn,"    " );
	strncpy( aMekbn,wrk,strlen(wrk) );
	printf( "kbn:%s\n",aMekbn );//getchar();
	ZbmlPrmGetVal(bp, "BUNSEKI_NUM", cNum);
	iBunsekiNum = atoi( cNum );
	printf( "BUNSEKI_NUM:%d\n",iBunsekiNum );
	sBunsekiInf = malloc(sizeof(BUNSEKI_INF)*iBunsekiNum);

	/* ADD E.Osada 2006-08-21 ���M�^�C�}�擾 */
	if ( ZbmlPrmGetVal ( bp, "SND_TIMER", wk ) != 0 ) {
		/* �h�m�h�t�@�C���ɐݒ肪�����ꍇ�̓f�t�H���g10msec���Z�b�g */
		iWtimer = DEFSNDTIMER;
	} else {
		iWtimer = atoi ( wk ) ;
	}

	for( iCnt=0; iCnt<iBunsekiNum; iCnt++ ) {
		memset(str, 0, sizeof(str));
		memset( wrk,0,sizeof(wrk) );
		memset(port, 0, sizeof(port));
		memset(&sBunsekiInf[iCnt],0,sizeof(BUNSEKI_INF));

		strcpy( wrk,"BUNSEKI_" );
		sprintf( &wrk[8],"%02d",iCnt+1 );
		printf( "str:%s\n",wrk );
		ZbmlPrmGetVal(bp, wrk, str);

		iWrk = strlen( str );
		for( iCnt2=0; iCnt2<iWrk; iCnt2++ ) {
			if( str[iCnt2] == ',' ) {
				break;
			}
			sBunsekiInf[iCnt].aIpAddr[iCnt2] = str[iCnt2];
		}

		iCnt3 = 0;
		for( iCnt2+=1; iCnt2<iWrk; iCnt2++ ) {
			if( str[iCnt2] == ',' ) {
				break;
			}
			port[iCnt3] = str[iCnt2];
			++iCnt3;
		}
		sBunsekiInf[iCnt].iPortNum = atoi(port);
		/* ADD E.Osada 2006-08-21 ���M�^�C�}�ݒ� */
		sBunsekiInf[iCnt].iSendTimer = iWtimer;
		iCnt3 = 0;
		for( iCnt2+=1; iCnt2<iWrk; iCnt2++ ) {
			if( str[iCnt2] == ',' ) {
				break;
			}
			sBunsekiInf[iCnt].aGouki[iCnt3] = str[iCnt2];
			++iCnt3;
		}

		printf("IP   = %s\n",sBunsekiInf[iCnt].aIpAddr);
		printf("PORT = %d\n",sBunsekiInf[iCnt].iPortNum);
		printf("���@ = %s\n",sBunsekiInf[iCnt].aGouki);
	}

	/* ��l�Č��ݒ�t�@�C���擾 */
	/* Add Hanyu 2023.05.23 */
	ZbmlPrmGetVal(bp, "LowSaikenMstPath", wrk);
	nRet = KnsParaInit(wrk);
	if (nRet != PARA_RET_NORMAL) {
		sprintf(wrk,"�ݒ�t�@�C��ReadError[%d]",nRet);
		sFncSyslog ( TRCKIND_ERROR, "KnsParaInit()", wrk ) ;
		ZbmlPrmClose(bp);
		return ( -1 ) ;
	}

	ZbmlPrmClose(bp);
	return 0;
}
/**********************************************************************/
/*                                                                    */
/*   function name : EndFunction                                      */
/*                                                                    */
/*   purpose : �I������                                               */
/*                                                                    */
/*   data : 2006.01.26                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
void EndFunction( void )
{
	SOCKET_INF *p, *q;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

	printf( "EndFunction()\n" );
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
    DelXbarmInf(sSocketInf.aGouki);
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */
	for( p=sSocketInf.next; p!=NULL; p=q ) {
		close(p->iSd);
		q = p->next;
		printf( "close:%d\n",p->iSd );
		free(p);
	}
	if( sBunsekiInf != NULL ) {
		free(sBunsekiInf);
	}
	if( pMechmst != NULL ) {
		free(pMechmst);
	}
	if( pKinkyu != NULL ) {
		free(pKinkyu);
	}
	if( pKmkmst != NULL ) {
		free(pKmkmst);
	}
	if( pCtrlmst != NULL ) {
		free(pCtrlmst);
	}
	if( pKnsgmst != NULL ) {		/* 009 060418 */
		free(pKnsgmst);				/* 009 060418 */
	}								/* 009 060418 */

	ZbmlCloseLog();

	KnsParaFree();		/* Add Hanyu 2023.05.23 */
	return;
}
/**********************************************************************/
/*                                                                    */
/*   function name : main                                             */
/*                                                                    */
/*   purpose : ���C������                                             */
/*                                                                    */
/*   data : 2005.12.9                                                 */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int main (int argc, char **argv)
{
	int				li_stopFlg ;


	/***
	 ***    �o�b�N�O���E���h���s
	 ***/
	if ( daemon ( 1, 1 ) < 0 ) {
		exit ( 9 ) ;
	}


	/* man 7 signal �Ŋm�F */
	if(SIG_ERR == signal(SIGINT,sigcatch)){
		fprintf(stderr,"failed to set signalhandler.\n");
		exit(1);
	}

	if( argc != 2 ) {
		printf( "�p�����[�^���w�肵�ĉ������B\n" );
		return -1;
	}

	InitFunction(argv[1]);

	Connect(1);
	while(1) {
		/***
		 *** ��~�R�}���h�m�F
		 ***/
		if ( sFncShmGet ( shm_Key, &li_stopFlg ) < 0 ) {
			return ( -1 ) ;
		}
		if ( li_stopFlg == 1 ) {
			sFncShmDel ( shm_Key ) ;
			printf("%s\n", "��~�R�}���h��M");
			break ;
		}
		/* �I���V�O�i�����`�F�b�N */
		if ( EndFlg ) {
			break;
		}
		if( Connect(0) == RTN_OK ){
			if( MainFunction() == 0 ) {
				break;
			}
		} else {
		}
	}
	EndFunction();
	return 0;
}
/**********************************************************************/
/*                                                                    */
/*   function name : sigcatch                                         */
/*                                                                    */
/*   purpose : �V�O�i���擾����                                       */
/*                                                                    */
/*   data : 2006.01.26                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
void sigcatch(int sig)
{
  fprintf(stdout,"catch signal %d\n",sig);
  EndFlg = 1;
  /* �V�O�i���n���h�����f�t�H���g�ɖ߂� */
  signal(sig,SIG_DFL);
}
/**********************************************************************/
/*                                                                    */
/*   function name : SetLogDat                                        */
/*                                                                    */
/*   purpose : ���O�o�̓f�[�^�ݒ菈��                                 */
/*                                                                    */
/*   data : 2006.01.26                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
void SetLogDat(LOG_TRCKIND Kind,char* Fnc,char* Login,char* App,char* Exe,char* Err,char* Msg)
{
	sLog.eTrcKind = Kind ;											/* �g���[�X��� */
	memcpy(sLog.pcFncName,Fnc,sizeof(sLog.pcFncName));				/* �֐��� */
	memcpy(sLog.pcLoginId,Login,sizeof(sLog.pcLoginId)) ;			/* ���O�C���h�c */
	memcpy(sLog.pcAppName,App,sizeof(sLog.pcAppName)) ;				/* �A�v���P�[�V������ */
	memcpy(sLog.pcExeFlg,Exe,sizeof(sLog.pcExeFlg)) ;				/* ���s�t���O */
	memcpy(sLog.pcErrCode,Err,sizeof(sLog.pcErrCode)) ;				/* �G���[�R�[�h */
	memcpy(sLog.pcMsg,Msg,sizeof(sLog.pcMsg)) ;						/* �ڍ׃��b�Z�[�W */
}

/**********************************************************************/
/*                                                                    */
/*   function name : MainFunction                                     */
/*                                                                    */
/*   purpose : ���C������                                             */
/*                                                                    */
/*   data : 2005.12.20                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int MainFunction( void )
{
	SOCKET_INF* p;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

	p = RcvData();
	StatusCtrl(p);
	SndData(p);
	return 1;
}

/**********************************************************************/
/*                                                                    */
/*   function name : DecodeRcvData                                    */
/*                                                                    */
/*   purpose : ��M����                                               */
/*                                                                    */
/*   data : 2005.12.12                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
void DecodeRcvData(SOCKET_INF* p,int len)
{
	char cWrk;
	char cWrk2;
	char c1;
	char c2;
	int iCnt;
	char aWrkMsg[255];
	int iLen;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));
#ifdef _DEBUG_
	printf("%sDecodeRcvData()\n", Now());
#endif

	cWrk = 0;
	cWrk2 = 0;
	iCnt = 0;
	memset( aWrkMsg, 0, sizeof(aWrkMsg) );

	switch( aRcvBuf[0]) {
	case ENQ:
		p->cRcvFrameCtrlChar = ENQ;	/* <ENQ>�ݒ� */
		p->cChkRcvData = RCV_DATA_OK;
		p->cFrameNum = 0;
		memset(p->aRcvTmpMsgBuf,0,sizeof(p->aRcvTmpMsgBuf));
									/* ��M���b�Z�[�W�R�s�[�G���A */
		break;
	case ACK:
		p->cRcvFrameCtrlChar = ACK;	/* <ACK>�ݒ� */
		p->cChkRcvData = RCV_DATA_OK;
		break;
	case STX:
		p->cRcvFrameCtrlChar = STX;
		/* �o�C�g���`�F�b�N */
		if( (len > MAX_RCV_NUM) || (len < 0) ) {
			p->cChkRcvData = RCV_DATA_NG;
			break;
		}
		/* No.1 �t���[�����䕶���ݒ� */
#ifdef _DEBUG_
		printf("�t���[���ԍ��`�F�b�N\n");
#endif
		++iCnt;
		/* �t���[���ԍ��`�F�b�N */
		cWrk2 = p->cFrameNum;
		if( aRcvBuf[iCnt] == (cWrk2%8)+0x30 ) {
			p->cChkRcvData = RCV_DATA_NG;
			break;
		} else if( aRcvBuf[iCnt] == (++cWrk2%8)+0x30 ) {
			if( cWrk2 >= 8 ) {
				cWrk2 -= 8;
			}
		} else {
			p->cChkRcvData = RCV_DATA_NG;
			break;
		}

		/* <ETB>or<ETX>�`�F�b�N */
#ifdef _DEBUG_
		printf("ETBorETX�`�F�b�N\n");
#endif
		if( (aRcvBuf[len-5] != ETB) && (aRcvBuf[len-5] != ETX) ) {
			p->cChkRcvData = RCV_DATA_NG;
			break;;
		}
		/* C1/C2�`�F�b�N */
#ifdef _DEBUG_
		printf("C1C2�`�F�b�N\n");
#endif
		cWrk = 0;
		for( iCnt=1; iCnt<len; iCnt++ ) {
			if( (aRcvBuf[iCnt] == ETB) || (aRcvBuf[iCnt] == ETX) ) {
				cWrk += aRcvBuf[iCnt];
				break;
			}
			cWrk += aRcvBuf[iCnt];
		}
#ifdef _DEBUG_
		printf("wWrk:%02x\n",cWrk);
#endif
		c1 = ((cWrk >> 4) & 0x0f);
		if( c1 <= 0x09 ) {
			c1 += 0x30;
		} else {
			c1 += 0x37;
		}
#ifdef _DEBUG_
		printf("c1:%c\n",c1);
#endif
		c2 = (cWrk & 0x0f);
		if( c2 <= 0x09 ) {
			c2 += 0x30;
		} else {
			c2 += 0x37;
		}
#ifdef _DEBUG_
		printf("c2:%c\n",c2);
#endif

		/* v1.01 �^���d���e�X�g�̈� */
		if( aRcvBuf[len-4] != 'Z' ) {
			if( aRcvBuf[len-4] != c1 ) {
				p->cChkRcvData = RCV_DATA_NG;
				break;
			}
		}
		if( aRcvBuf[len-3] != 'Z' ) {
			if( aRcvBuf[len-3] != c2 ) {
				p->cChkRcvData = RCV_DATA_NG;
				break;
			}
		}

		/* CR�`�F�b�N */
#ifdef _DEBUG_
		printf("CR�`�F�b�N\n");
#endif
		if( aRcvBuf[len-2] != CR ) {
			p->cChkRcvData = RCV_DATA_NG;
			break;
		}
		/* LF�`�F�b�N */
#ifdef _DEBUG_
		printf("LF�`�F�b�N\n");
#endif
		if( aRcvBuf[len-1] != LF ) {
			p->cChkRcvData = RCV_DATA_NG;
			break;
		}
		p->cFrameNum = cWrk2;
		/* ��M���b�Z�[�W���ꎞ�G���A�փR�s�[ */
		for( iCnt=0; iCnt<len; iCnt++ ) {
			if( aRcvBuf[iCnt+2] == ETB ) {
				p->cChkNextFrame = FRAME_CONTINUE;
				break;
			} else if( aRcvBuf[iCnt+2] == ETX ) {
				p->cChkNextFrame = FRAME_END;
				break;
			}
			aWrkMsg[iCnt] = aRcvBuf[iCnt+2];
		}
		iLen = strlen( aWrkMsg );
		strncat( p->aRcvTmpMsgBuf, aWrkMsg, iLen );

		iLen = strlen( p->aRcvTmpMsgBuf );

		p->cChkRcvData = RCV_DATA_OK;
		p->cChkRcvMessage = MESSAGE_NO_ERR;
		if( p->cChkNextFrame == FRAME_END ) {
			if( DecodeRcvMessage(p) == MESSAGE_ERR ) {
				p->cChkRcvMessage = MESSAGE_ERR;
			} else {
				p->cChkRcvMessage = MESSAGE_ALL_OK;
			}
		}
		break;
	case NAK:
		p->cRcvFrameCtrlChar = NAK;		/* <NAK>�ݒ� */
		p->cChkRcvData = RCV_DATA_OK;
		break;
	case EOT:
		p->cRcvFrameCtrlChar = EOT;		/* <EOT>�ݒ� */
		p->cChkRcvData = RCV_DATA_OK;
		break;
	default :
		p->cRcvFrameCtrlChar = 0xff;	/* �G���[�l�ݒ� */
		p->cChkRcvData = RCV_DATA_NG;
		p->cChkRcvMessage = MESSAGE_ERR;
		break;
	}

	return;
}
/**********************************************************************/
/*                                                                    */
/*   function name : DecodeRcvMessage                                 */
/*                                                                    */
/*   purpose : ���b�Z�[�W�f�R�[�h����                                 */
/*                                                                    */
/*   data : 2005.12.13                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int DecodeRcvMessage(SOCKET_INF* p)
{
	int iCnt;
	int iCnt2;
	int iLen;
	int iWrk;
	int iWrk2;
//	int saiken;
	int iAlerm; 					/* ADD E.Osada 2006-09-19 */
	int i;							/* ADD E.Osada 2006-09-19 */
	char aFunc[32];
	char *aRcvMsg;
//	int nyubiOrderFlg ;				/* ���їn�����t�I�[�_�쐬�ς݃t���O */
//	char ksktkbn;
	char cXmSkFlg;


	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sDecodeRcvMessage\n", Now());
#endif

	iRcvAllMsgCnt = 0;
	if( pKenorder != NULL ) {
		free( pKenorder );
		pKenorder = NULL;
	}
	iLen = strlen(p->aRcvTmpMsgBuf);

	aRcvMsg = malloc(sizeof(char)*1500);

	do {
		switch( p->aRcvTmpMsgBuf[iRcvAllMsgCnt] ) {
		case 'H':
			memset(aRcvMsg,0,1500);
			for( iCnt=0; iCnt<iLen; iCnt++ ) {
				if( p->aRcvTmpMsgBuf[iRcvAllMsgCnt] == CR ) {
					aRcvMsg[iCnt] = p->aRcvTmpMsgBuf[iRcvAllMsgCnt];
					++iRcvAllMsgCnt;
					break;
				}
				aRcvMsg[iCnt] = p->aRcvTmpMsgBuf[iRcvAllMsgCnt];
				++iRcvAllMsgCnt;
			}
			if( DecodeMsgHeaderRcd(p,aRcvMsg) == MESSAGE_ERR ) {
				return MESSAGE_ERR;
			}
#ifdef _DEBUG_
			printf("���o�����R�[�h:%s\n",aRcvMsg);
#endif
			break;

		case 'P':
			memset(aRcvMsg,0,1500);
			for( iCnt=0; iCnt<iLen; iCnt++ ) {
				if( p->aRcvTmpMsgBuf[iRcvAllMsgCnt] == CR ) {
					aRcvMsg[iCnt] = p->aRcvTmpMsgBuf[iRcvAllMsgCnt];
					++iRcvAllMsgCnt;
					break;
				}
				aRcvMsg[iCnt] = p->aRcvTmpMsgBuf[iRcvAllMsgCnt];
				++iRcvAllMsgCnt;
			}
			if( DecodePatientInfRcd(p,aRcvMsg) == MESSAGE_ERR ) {
				return MESSAGE_ERR;
			}
#ifdef _DEBUG_
			printf("���ҏ�񃌃R�[�h�F%s\n",aRcvMsg);
#endif
			break;

		case 'Q':
			memset(aRcvMsg,0,1500);
			for( iCnt=0; iCnt<iLen; iCnt++ ) {
				if( p->aRcvTmpMsgBuf[iRcvAllMsgCnt] == CR ) {
					aRcvMsg[iCnt] = p->aRcvTmpMsgBuf[iRcvAllMsgCnt];
					++iRcvAllMsgCnt;
					break;
				}
				aRcvMsg[iCnt] = p->aRcvTmpMsgBuf[iRcvAllMsgCnt];
				++iRcvAllMsgCnt;
			}
			if( DecodeReqInfRcd(p,aRcvMsg) == MESSAGE_ERR ) {
#ifdef _DEBUG_
				printf("�₢���킹��񃌃R�[�h!!!ERROR!!!�F%s\n",aRcvMsg);
#endif
				return MESSAGE_ERR;
			}
			/* 2020/11/01 �₢���킹���b�N���̏o�͏��� */
			if( OutputBunsekiOrder(p) != RTN_OK ) {
				sFncSyslog ( TRCKIND_ERROR, "OutputBunsekiOrder()", "�t�@�C���̃I�[�v���Ɏ��s���܂����B" ) ;
				return RTN_NG;
			}
#ifdef _DEBUG_
			printf("�₢���킹��񃌃R�[�h�F%s\n",aRcvMsg);
#endif
			break;

		case 'O':
			memset(aRcvMsg,0,1500);
			for( iCnt=0; iCnt<iLen; iCnt++ ) {
				if( p->aRcvTmpMsgBuf[iRcvAllMsgCnt] == CR ) {
					aRcvMsg[iCnt] = p->aRcvTmpMsgBuf[iRcvAllMsgCnt];
					++iRcvAllMsgCnt;
					break;
				}
				aRcvMsg[iCnt] = p->aRcvTmpMsgBuf[iRcvAllMsgCnt];
				++iRcvAllMsgCnt;
			}
			if( DecodeTestOrderRcd(p,aRcvMsg) == MESSAGE_ERR ) {
				return MESSAGE_ERR;
			}
#ifdef _DEBUG_
			printf("���ڑI�����R�[�h�F%s\n",aRcvMsg);
#endif
			break;

		case 'C':
			memset(aRcvMsg,0,1500);
			for( iCnt=0; iCnt<iLen; iCnt++ ) {
				if( p->aRcvTmpMsgBuf[iRcvAllMsgCnt] == CR ) {
					aRcvMsg[iCnt] = p->aRcvTmpMsgBuf[iRcvAllMsgCnt];
					if( p->aRcvTmpMsgBuf[iRcvAllMsgCnt-1] == 'I' ) {
						iWrk = C_RES;
					} else {
						iWrk = C_CMM;
					}
					++iRcvAllMsgCnt;
					break;
				}
				aRcvMsg[iCnt] = p->aRcvTmpMsgBuf[iRcvAllMsgCnt];
				++iRcvAllMsgCnt;
			}
			if( DecodeCommentRcd(iWrk,aRcvMsg) == MESSAGE_ERR ) {
				return MESSAGE_ERR;
			}
			if( iWrk == C_RES ) {
#ifdef _DEBUG_
				printf("���߃��R�[�h(C_RES)�F%s\n",aRcvMsg);
#endif
			} else {
#ifdef _DEBUG_
				printf("���߃��R�[�h(C_CMM)�F%s\n",aRcvMsg);
#endif
			}
			break;

		case 'R':
			memset(aRcvMsg,0,1500);
			for( iCnt=0; iCnt<iLen; iCnt++ ) {
				if( p->aRcvTmpMsgBuf[iRcvAllMsgCnt] == CR ) {
					aRcvMsg[iCnt] = p->aRcvTmpMsgBuf[iRcvAllMsgCnt];
					++iRcvAllMsgCnt;
					break;
				}
				aRcvMsg[iCnt] = p->aRcvTmpMsgBuf[iRcvAllMsgCnt];
				++iRcvAllMsgCnt;
			}
			if( DecodeResultRcd(p,aRcvMsg) == MESSAGE_ERR ) {
				return MESSAGE_ERR;
			}
#ifdef _DEBUG_
			printf("���茋�ʃ��R�[�h)�F%s\n",aRcvMsg);
#endif

			if ( p->aRcvTmpMsgBuf[iRcvAllMsgCnt] == 'C' ) {
				/* �������߃��R�[�h�̂Ƃ��͐�ǂ݂���B */
				memset(aRcvMsg,0,1500);
				for( iCnt=0; iCnt<iLen; iCnt++ ) {
					if( p->aRcvTmpMsgBuf[iRcvAllMsgCnt] == CR ) {
						aRcvMsg[iCnt] = p->aRcvTmpMsgBuf[iRcvAllMsgCnt];
						if( p->aRcvTmpMsgBuf[iRcvAllMsgCnt-1] == 'I' ) {
							iWrk = C_RES;
						} else {
							iWrk = C_CMM;
						}
						++iRcvAllMsgCnt;
						break;
					}
					aRcvMsg[iCnt] = p->aRcvTmpMsgBuf[iRcvAllMsgCnt];
					++iRcvAllMsgCnt;
				}
				if( DecodeCommentRcd(iWrk,aRcvMsg) == MESSAGE_ERR ) {
					return MESSAGE_ERR;
				}
				if( iWrk == C_RES ) {
#ifdef _DEBUG_
					printf("���߃��R�[�h(C_RES)�F%s\n",aRcvMsg);
#endif
				} else {
#ifdef _DEBUG_
					printf("���߃��R�[�h(C_CMM)�F%s\n",aRcvMsg);
#endif
				}
			}

			if( p->iKekkaCnt >= p->iKekkaNum ) {
				ClrSaikenInf(p);
				if( aRcvMsg != NULL ) {
					free( aRcvMsg );
				}

				return MESSAGE_ERR;
			}

			if( sTestOrderRcd.cActionCode[0] == 'N' ) {
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
/*** �ً}STAT�Ή� �ً}STAT�̔���̓��b�NNO�ōs�� ***/
				int  rackNo  = atoi(p->cRackNum);
				if( sTestOrderRcd.cPriority[0] == 'R' &&
					(rackNo < 40001 || 40999 < rackNo)) {
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */
					/* �����I�[�_�[(.dat)�t�@�C���ǂݍ��� */
					if( pKenorder != NULL ) {
						free( pKenorder );
						pKenorder = NULL;
					}
					if( ChkNbkmkcd(p,&iCnt2) == RTN_OK ) {

						/* X-M�W�v�t���O���擾(0:�W�v����A1:�W�v���Ȃ�) */
						cXmSkFlg = GetXmSkFlg(pKenorder[iCnt2].knsgrp, pKenorder[iCnt2].kmkcd, pKenorder[iCnt2].knskisymd);

						/* X-M�W�v����ꍇ(0:�W�v����A1:�W�v���Ȃ�) */
						if(cXmSkFlg == '0') {
							if( SetXbarmInf(p,iCnt2) == RTN_OK ) {
								SetXbarmData(p);
								OutputXbarm( p );
							}
						}
#ifdef _DEBUG_
						else {
							printf( "DecodeMeasureDatTxt_NoInq(%d) : pKenorder[iCnt2].knsgrp    = %s\n", __LINE__, pKenorder[iCnt2].knsgrp );
							printf( "DecodeMeasureDatTxt_NoInq(%d) : pKenorder[iCnt2].kmkcd     = %s\n", __LINE__, pKenorder[iCnt2].kmkcd );
							printf( "DecodeMeasureDatTxt_NoInq(%d) : cXmSkFlg == '%c' �Ȃ̂ŁAX-M�W�v���s��Ȃ�\n", __LINE__, cXmSkFlg );
						}
#endif
						/* ���ʏ��ݒ�(�I�[�_�[�t�@�C������) */
						SetKekkaData(p,iCnt2);
//						ksktkbn = pKenorder->ksktkbn;
					} else {
						/* ���ʏ��ݒ�(�I�[�_�[�t�@�C���Ȃ�) */
						SetKekkaData_NoOrder(p);
//						ksktkbn = 'A';
					}
					if( pKenorder != NULL ) {
						free( pKenorder );
						pKenorder = NULL;
					}
				} else {
					/* X-M���ݒ� */
//					if( SetXbarmInf(p,RTN_NG) == RTN_OK ) {
//						SetXbarmData(p);
//						OutputXbarm( p );
//					}
					SetKekkaData_Kinkyu(p);
				}
				++(p->iKekkaCnt);
#ifdef _DEBUG_
	printf( "DecodeRcvMessage(%d) : p->iKekkaCnt = %d\n", __LINE__, p->iKekkaCnt );
	printf( "DecodeRcvMessage(%d) : p->iKekkaNum = %d\n", __LINE__, p->iKekkaNum );
#endif

				if( p->iKekkaCnt == p->iKekkaNum ) {
					/* DEL E.Osada 2006-07-17 */
//					nyubiOrderFlg = 1 ;
//					saiken = 0;
					if( sTestOrderRcd.cPriority[0] == 'R' ) {
						/* ADD E.Osada 2006-07-15 */
						/* CHG E.Osada 2006-09-19 */
						iAlerm = chkDataAlarm( p );

						/* ���A���^�C���`�F�b�N */
						RealTimeChk( p, p->pSaiken );

						/* ADD E.Osada 2006-09-19 */
						/* �l�܂茟�m�G���[�̏ꍇ�S���ڗp��Č������Ƃ��� */
						if( iAlerm == 2 ) {
							for( i=0; i < p->iKekkaNum ;++i ) {
				                /* ADD Nagata 2006-09-25 */
			   		            /* �ۗ��������̃t���O�͕ς��Ȃ� */
			  	 	            if( p->pKekka[i].knsflg != 'H'){
									p->pKekka[i].knsflg = 'R';
								}
							}
						}

						/* ��l�f�[�^�`�F�b�N */
						// Add 2023.05.23 Hanyu
						chkLowDataSaiken(p);

					}
					/* CSV�������� */
					OutputKekka( p );
					/* CHG E.Osada 2006-07-16 */
					for( iCnt2=0; iCnt2<(p->iKekkaNum); iCnt2++ ) {
						/* p->pSaiken[iCnt2].flg�� 1 �̂��̂������Č��Ώ�(�čČ������Ȃ� */
						/*	�����Č����� */
						/*	�Č��t���O�i�����ϐ��j���P�Ō����H���敪���r�F�đ���܂��͌����񐔂��P�̂��� */
						/*  �� 2006/08/05 */
						/*	�����t���O��'A'�Ō����H���敪���r�F�đ���܂��͌����񐔂��P�̂��� */
						if( p->pKekka[iCnt2].knsflg    == 'A'   && 
                            ( p->pKekka[iCnt2].ksktkbn == 'S' || p->pKekka[iCnt2].knssu == 1 ) ) {
							strcpy( p->sSndorder.kmkcd[p->iOrderNum], p->pKekka[iCnt2].nbkmkcd );
							if( strcmp(p->pSaiken[iCnt2].KSBR, "0D") == 0 ) {
								strcpy( p->sSndorder.ytiksbr[p->iOrderNum],"Dec" );
							}
							else {
								iWrk2 = atoi(p->pSaiken[iCnt2].KSBR);
								if( iWrk2 == aKskbrt[0] ) {
									strcpy( p->sSndorder.ytiksbr[p->iOrderNum],"3" );
								} else if( iWrk2 == aKskbrt[1] ) {
									strcpy( p->sSndorder.ytiksbr[p->iOrderNum],"5" );
								} else if( iWrk2 == aKskbrt[2] ) {
									strcpy( p->sSndorder.ytiksbr[p->iOrderNum],"10" );
								} else if( iWrk2 == aKskbrt[3] ) {
									strcpy( p->sSndorder.ytiksbr[p->iOrderNum],"20" );
								} else if( iWrk2 == aKskbrt[4] ) {
									strcpy( p->sSndorder.ytiksbr[p->iOrderNum],"50" );
								} else {
									memset( p->sSndorder.ytiksbr[p->iOrderNum],0,sizeof(p->sSndorder.ytiksbr[0]) );
								}
							}	// ADD E.Osada 2006-08-21 */
							++p->iOrderNum;
						} else if( p->pSaiken[iCnt2].flg == '2' ) {
							/* �Č��Ώۂɖ߂�(���ł�'1'���Č��Ώۂ���....) */
//							p->pSaiken[iCnt2].flg == '1';
						}
					}
				}
			} else if( sTestOrderRcd.cActionCode[0] == 'Q' ) {
				p->iRcvMsg = MSG_NON;

				int		cnt;
				int		cnt2;
				char	kmkcd[10][8];
				char	nbkmkcd[8];
				cnt2 = 0;
				memset( nbkmkcd,0,8 );
				strncpy( nbkmkcd,"       ",7 );
				strncpy( nbkmkcd,sResultRcd.cAppCode,strlen(sResultRcd.cAppCode) );
				memset( kmkcd,0,sizeof(kmkcd) );
				for( cnt=0;cnt<iMechmstNum;cnt++ ) {
					if( strncmp(pMechmst[cnt].nbkmcd,nbkmkcd,7) == 0 ) {
						strncpy( kmkcd[cnt2],pMechmst[cnt].kmkcd,7 );
						++cnt2;
					}
				}
				if( p->iKekkaCnt == 0 ) {
					/* �R���g���[�����ʂ̍ŏ��̎��Ƀt�@�C�����̍쐬 */
					char cWrk[30];
					memset( cWrk,0,sizeof(cWrk) );
					if( (p->cRackNum[0] >= 0x30) && (p->cRackNum[0] <= 0x39) ) {
						sprintf( cWrk,"%d",atoi(p->cRackNum) );
					} else {
						strcpy( cWrk,p->cRackNum );
					}

					MakeFileName( cWrk, p->aGouki, 1 );
					
					/* �t�@�C���̑��݊m�F */
					char aWrkBuf2[256];

					int loopCnt = 0;
					int len = strlen(aFileNameStr) - 3;
					while (1) {
						memset( aWrkBuf2, 0, sizeof(aWrkBuf2) );
						strcpy( aWrkBuf2,aCtrlkkaFolder );
						strcat( aWrkBuf2,"CT_" );
						strcat( aWrkBuf2,aFileNameStr );

						struct stat	fst;
						if (stat(aWrkBuf2, &fst) == 0) {
							loopCnt++;
							aFileNameStr[len+0] = '\0';
							aFileNameStr[len+1] = '\0';
							aFileNameStr[len+0] = ((loopCnt > 9) ? 'A'-10 : '0') + loopCnt;
							strcat( aFileNameStr,".dat" );
						}
						else {
							break;
						}
					}

				}
				++(p->iKekkaCnt);
				for( cnt=0;cnt<cnt2;cnt++ ) {
					SetCtrlkkaData(p,kmkcd[cnt]);
					/* �R���g���[�����ݒ� */
					if( cnt == 0 ) {
						SetCtrlInf(p,sResultRcd.cAppCode);
					}

					/* CSV�������� */
					OutputCtrlkka( p );
				}
				if( p->iKekkaCnt == p->iKekkaNum ) {
					char aWrkBuf2[255];
					/* �R���g���[�����ʂ̍Ō�̎���Index�̍쐬 */
					memset( aWrkBuf2, 0, sizeof(aWrkBuf2) );
					strcpy( aWrkBuf2,aKekkaFolder );
					strcat( aWrkBuf2,"../Index/" );
					strcat( aWrkBuf2,"CT_" );
					strcat( aWrkBuf2,aFileNameStr );
					
					close(open(aWrkBuf2, O_CREAT, 0644));
				}
			}
			break;

		case 'M':
			memset(aRcvMsg,0,1500);
			for( iCnt=0; iCnt<iLen; iCnt++ ) {
				if( p->aRcvTmpMsgBuf[iRcvAllMsgCnt] == CR ) {
					aRcvMsg[iCnt] = p->aRcvTmpMsgBuf[iRcvAllMsgCnt];
					++iRcvAllMsgCnt;
					break;
				}
				aRcvMsg[iCnt] = p->aRcvTmpMsgBuf[iRcvAllMsgCnt];
				++iRcvAllMsgCnt;
			}
			if( DecodeCalbRcd(p,aRcvMsg) == MESSAGE_ERR ) {
				return MESSAGE_ERR;
			}
			if( strncmp( sCalbRcd.cSubId,"ABS",3 ) == 0 ) {
#ifdef _DEBUG_
				printf("��F�����ߒ��f�[�^���R�[�h�F%s\n",aRcvMsg);
#endif
				return MESSAGE_ERR;
			} else if( strncmp( sCalbRcd.cSubId,"PCR",3 ) == 0 ) {
#ifdef _DEBUG_
				printf("��F�L�����u���[�V�������ʃ��R�[�h�F%s\n",aRcvMsg);
#endif

				Kekka	*pKekka;
				ClrSaikenInf(p);
				p->iKekkaNum = 0;
				p->pKekka = malloc(sizeof(Kekka));
				pKekka = malloc(sizeof(Kekka)*6*2);

				for( iCnt2=0; iCnt2<6; iCnt2++ ) {
					iWrk = strlen( sCalbRcd.sStdDat[iCnt2].c1stDat );
					if( iWrk > 0 ) {
						memset( &(p->pKekka[0]),0,sizeof(Kekka) );
						SetKekkaData_PCR(p,iCnt2,1);
						memcpy( &(pKekka[p->iKekkaNum]), &(p->pKekka[0]),sizeof(Kekka) );
						++(p->iKekkaNum);
					}
					iWrk = strlen( sCalbRcd.sStdDat[iCnt2].c2ndDat );
					if( iWrk > 0 ) {
						memset( &(p->pKekka[0]),0,sizeof(Kekka) );
						SetKekkaData_PCR(p,iCnt2,2);

						memcpy( &(pKekka[p->iKekkaNum]), &(p->pKekka[0]),sizeof(Kekka) );
						++(p->iKekkaNum);
					}
				}
				if ( p->iKekkaNum > 0 ) {
					strcpy( p->cRackNum,"PCR01" );
					strcpy( p->cRackPosNum,"1" );

					free(p->pKekka);
					p->pKekka = pKekka;

					/* CSV�������� */
					OutputKekka( p );
				}
			} else if( strncmp( sCalbRcd.cSubId,"ICR",3 ) == 0 ) {
#ifdef _DEBUG_
				printf("ISE�L�����u���[�V�������ʃ��R�[�h�F%s\n",aRcvMsg);
#endif

				Kekka	*pKekka;
				ClrSaikenInf(p);
				p->iKekkaNum = 0;
				p->pKekka = malloc(sizeof(Kekka));
				pKekka = malloc(sizeof(Kekka)*3);

				for( iCnt2=0; iCnt2<3; iCnt2++ ) {
					iWrk = strlen( sCalbRcd.sIseCalbItem[iCnt2].cDatHosei );
					if( iWrk > 0 ) {
						memset( &(p->pKekka[0]),0,sizeof(Kekka) );
						SetKekkaData_ISE(p,iCnt2);

						memcpy( &(pKekka[p->iKekkaNum]), &(p->pKekka[0]),sizeof(Kekka) );
						++(p->iKekkaNum);
					}
				}
				if ( p->iKekkaNum > 0 ) {
					strcpy( p->cRackNum,"ICR01" );
					strcpy( p->cRackPosNum,"1" );

					free(p->pKekka);
					p->pKekka = pKekka;

					/* CSV�������� */
					OutputKekka( p );
				}
			} else {
#ifdef _DEBUG_
				printf("�s�����R�[�h�F%s\n",aRcvMsg);
#endif
			}
			break;
		case 'L':
			memset(aRcvMsg,0,1500);
			for( iCnt=0; iCnt<iLen; iCnt++ ) {
				if( p->aRcvTmpMsgBuf[iRcvAllMsgCnt] == CR ) {
					aRcvMsg[iCnt] = p->aRcvTmpMsgBuf[iRcvAllMsgCnt];
					++iRcvAllMsgCnt;
					break;
				}
				aRcvMsg[iCnt] = p->aRcvTmpMsgBuf[iRcvAllMsgCnt];
				++iRcvAllMsgCnt;
			}
#ifdef _DEBUG_
			printf("���b�Z�[�W�I�����R�[�h�F%s\n",aRcvMsg);
#endif
			break;

		default:
			for( iCnt=0; iCnt<iLen; iCnt++ ) {
				if( p->aRcvTmpMsgBuf[iRcvAllMsgCnt] == CR ) {
					++iRcvAllMsgCnt;
					break;
				}
				++iRcvAllMsgCnt;
			}
			memset(aRcvMsg,0,1500);		/* ���o�����R�[�h�G���A */
			break;
		}
	} while( (iLen-iRcvAllMsgCnt) > 0 );

	if( p->pKekka != NULL ) {
		free( p->pKekka );
		p->pKekka = NULL;
	}

	ClrSaikenInf(p);
	return MESSAGE_ALL_OK;
}
/**********************************************************************/
/*                                                                    */
/*   function name : ChkNbkmkcd                                       */
/*                                                                    */
/*   purpose : �������ڃR�[�h�`�F�b�N                                 */
/*                                                                    */
/*   data : 2006.03.14                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int ChkNbkmkcd(SOCKET_INF* p,int* iCnt)
{
	int	 ordernum;
	int	 iWrk;
	char cWrkCd[8];
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sChkNbkmkcd\n", Now());
#endif

	ordernum = 0;
	memset( cWrkCd,0,sizeof(cWrkCd) );

#if(0)
	strncpy( cWrkCd,"       ",7 );
	strncpy( cWrkCd,sResultRcd.cAppCode,strlen(sResultRcd.cAppCode) );
	if( GetKenorder( p,ORDER_DAT_1,&ordernum ) == RTN_OK ) {
		for( *iCnt=0; *iCnt<ordernum; (*iCnt)++ ) {
			if( strncmp( pKenorder[*iCnt].nbkmkcd,cWrkCd,7 ) == 0 ) {
				return RTN_OK;
			}
		}
	} else if( GetKenorder( p,ORDER_DAT_2,&ordernum ) == RTN_OK ) {
		if( GetKmkcd( ordernum,sResultRcd.cAppCode,cWrkCd ) == RTN_OK ) {
			for( *iCnt=0; *iCnt<ordernum; (*iCnt)++ ) {
				if( strncmp( pKenorder[*iCnt].kmkcd,cWrkCd,7 ) == 0 ) {
					return RTN_OK;
				}
			}
		}
	}
#endif

	iWrk = GetKenorder( p,ORDER_DAT_1,&ordernum );
	if( iWrk != RTN_OK ) {
		iWrk = GetKenorder( p,ORDER_DAT_2,&ordernum );
	}
	if( iWrk == RTN_OK ) {
		if( GetKmkcd( ordernum,sResultRcd.cAppCode,cWrkCd ) == RTN_OK ) {
			for( *iCnt=0; *iCnt<ordernum; (*iCnt)++ ) {
				if( strncmp( pKenorder[*iCnt].kmkcd,cWrkCd,7 ) == 0 ) {
					return RTN_OK;
				}
			}
		}
	}
	return RTN_NG;
}

/**********************************************************************/
/*                                                                    */
/*   function name : SetKekkaData                                     */
/*                                                                    */
/*   purpose : ���ʏ��ݒ�                                           */
/*                                                                    */
/*   data : 2006.03.01                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
void SetKekkaData(SOCKET_INF* p,int iCnt2)
{
	int		iWrk;
	int		iCnt;
	int		module;
	char	cWrkCd[32];
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sSetKekkaData\n", Now());
#endif

	memset(&p->pKekka[p->iKekkaCnt],0,sizeof(Kekka));

	/* No. 1 �����J�n���ݒ� */
	strcpy( p->pKekka[p->iKekkaCnt].knskisymd,pKenorder[iCnt2].knskisymd );
	/* No. 2 �������ݒ� */
	strcpy( p->pKekka[p->iKekkaCnt].sriymd,pKenorder[iCnt2].sriymd );
	/* No. 3 ����No�ݒ� */
	strcpy( p->pKekka[p->iKekkaCnt].kntno,pKenorder[iCnt2].kntno );
	/* No. 4 ����No�����t���O�ݒ� */
	p->pKekka[p->iKekkaCnt].kntketflg = pKenorder[iCnt2].kntketflg;
	/* No. 5 �����O���[�v�ݒ� */
	strcpy( p->pKekka[p->iKekkaCnt].knsgrp,pKenorder[iCnt2].knsgrp );
	/* No. 6 ���ڃR�[�h�ݒ� */
	strcpy( p->pKekka[p->iKekkaCnt].kmkcd, pKenorder[iCnt2].kmkcd );
	/* No. 7 �����񐔐ݒ� */
	p->pKekka[p->iKekkaCnt].knssu = pKenorder[iCnt2].knssu;
	if( sResultRcd.cResStat[0] == 'C' ) {
		++p->pKekka[p->iKekkaCnt].knssu;
	}
	/* No. 8 �����񐔎}�Ԑݒ� */
	iWrk = 0;
	for( iCnt=0;iCnt<(p->iKekkaCnt);iCnt++ ) {
		if( strncmp(p->pKekka[iCnt].kmkcd,p->pKekka[p->iKekkaCnt].kmkcd,7) == 0 ) {
			++iWrk;
		}
	}
	p->pKekka[p->iKekkaCnt].knssueda = iWrk;
	/* No. 9 �˗��������敪�ݒ� */
	p->pKekka[p->iKekkaCnt].irihsmkbn = pKenorder[iCnt2].irihsmkbn;
	/* No.10 �˗��敪�ݒ� */
	p->pKekka[p->iKekkaCnt].irikbn = pKenorder[iCnt2].irikbn;
	/* No.11 �����H���敪�ݒ� */
	p->pKekka[p->iKekkaCnt].ksktkbn = pKenorder[iCnt2].ksktkbn;
/* tune add 2006.4.13 */
	if( sResultRcd.cResStat[0] == 'C' ) {
		p->pKekka[p->iKekkaCnt].ksktkbn = 'K';
	}
/* tune add end */
	/* No.12 BML��t�N�����ݒ� */
	strcpy( p->pKekka[p->iKekkaCnt].utkymd,pKenorder[iCnt2].utkymd );
	/* No.13 �˗���No�ݒ� */
	strcpy( p->pKekka[p->iKekkaCnt].irino,pKenorder[iCnt2].irino );
	/* No.14 �˗���No�����t���O�ݒ� */
	p->pKekka[p->iKekkaCnt].iriketflg = pKenorder[iCnt2].iriketflg;
	/* No.15 ��������No�ݒ� */
	p->pKekka[p->iKekkaCnt].zssdino = pKenorder[iCnt2].zssdino;
	/* No.16 �{�݃R�[�h�ݒ� */
	strcpy( p->pKekka[p->iKekkaCnt].sstcd,pKenorder[iCnt2].sstcd );
	/* No.17 �g���[ID�ݒ� */
	strcpy( p->pKekka[p->iKekkaCnt].trid,pKenorder[iCnt2].trid);
	/* No.18 �g���[�|�W�V�����ݒ� */
	p->pKekka[p->iKekkaCnt].trpos = pKenorder[iCnt2].trpos;
	/* No.19 �A�b�Z�C���b�N�ݒ� */
	/* No.20 �A�b�Z�C���b�N�|�W�V�����ݒ� */

	/* No.13 �A�b�Z�C���b�N�ݒ� */
	strcpy( p->pKekka[p->iKekkaCnt].asyrckid,p->cRackNum );
	/* No.14 �A�b�Z�C���b�N�|�W�V�����ݒ� */
	p->pKekka[p->iKekkaCnt].asyrckpos = atoi(p->cRackPosNum);

	/* No.21 �e���ڃR�[�h�ݒ� */
	strcpy( p->pKekka[p->iKekkaCnt].oyakmkcd,pKenorder[iCnt2].oyakmkcd );
	/* No.22 �Z�N�V�����R�[�h�ݒ� */
	strcpy( p->pKekka[p->iKekkaCnt].seccd,pKenorder[iCnt2].seccd );
	/* No.23 ���敉�׋敪�ݒ� */
	p->pKekka[p->iKekkaCnt].bkfkkbn = pKenorder[iCnt2].bkfkkbn;
	/* No.24 �T���v�����O�R�[�h�ݒ� */
	strcpy( p->pKekka[p->iKekkaCnt].smpcd,pKenorder[iCnt2].smpcd );
	/* No.25 ���͋@�敪�ݒ� */
	strcpy( p->pKekka[p->iKekkaCnt].bskkbn,aMekbn );
	/* No.26 ���͋@���C���ݒ� */
	strncpy( p->pKekka[p->iKekkaCnt].bsklne,p->aGouki,2 );
	/* No.27 ���u���ʔԍ�->���͋@���@ */
	strncpy( p->pKekka[p->iKekkaCnt].bskgok,p->aGouki,2 );
	sBskgokConv ( sResultRcd.cInstIdentif, p->pKekka[p->iKekkaCnt].bskgok ) ;	
	/* No.28 ���͋@SEQ�ݒ� */
	p->pKekka[p->iKekkaCnt].bskseq = atoi(sTestOrderRcd.cSampleNo);
	/* No.29 ���͋@�G���[�X�e�[�^�X�ݒ� */
	if ( strlen(sCommentRcd.cCmmTxt) == 3 ) {
		// 3���̃X�e�[�^�X�������Ƃ���"00"��ݒ�
		strncpy( p->pKekka[p->iKekkaCnt].bskerrsts,"00",2 );
	}
	else {
		strncpy( p->pKekka[p->iKekkaCnt].bskerrsts,sCommentRcd.cCmmTxt,2 );
	}
	/* No.30 ������� */
#if 1
	/* ��������ݒ� */
	p->pKekka[p->iKekkaCnt].sktdh[0] = sResultRcd.cTestStarted[0];
	p->pKekka[p->iKekkaCnt].sktdh[1] = sResultRcd.cTestStarted[1];
	p->pKekka[p->iKekkaCnt].sktdh[2] = sResultRcd.cTestStarted[2];
	p->pKekka[p->iKekkaCnt].sktdh[3] = sResultRcd.cTestStarted[3];
	p->pKekka[p->iKekkaCnt].sktdh[4] = '-';
	p->pKekka[p->iKekkaCnt].sktdh[5] = sResultRcd.cTestStarted[4];
	p->pKekka[p->iKekkaCnt].sktdh[6] = sResultRcd.cTestStarted[5];
	p->pKekka[p->iKekkaCnt].sktdh[7] = '-';
	p->pKekka[p->iKekkaCnt].sktdh[8] = sResultRcd.cTestStarted[6];
	p->pKekka[p->iKekkaCnt].sktdh[9] = sResultRcd.cTestStarted[7];
	p->pKekka[p->iKekkaCnt].sktdh[10] = ' ';
	/* ��������->������� */
	p->pKekka[p->iKekkaCnt].sktdh[11] = sResultRcd.cTestStarted[8];
	p->pKekka[p->iKekkaCnt].sktdh[12] = sResultRcd.cTestStarted[9];
	p->pKekka[p->iKekkaCnt].sktdh[13] = ':';
	p->pKekka[p->iKekkaCnt].sktdh[14] = sResultRcd.cTestStarted[10];
	p->pKekka[p->iKekkaCnt].sktdh[15] = sResultRcd.cTestStarted[11];
	p->pKekka[p->iKekkaCnt].sktdh[16] = ':';
	p->pKekka[p->iKekkaCnt].sktdh[17] = sResultRcd.cTestStarted[12];
	p->pKekka[p->iKekkaCnt].sktdh[18] = sResultRcd.cTestStarted[13];
#else
	/* ��������ݒ� */
	p->pKekka[p->iKekkaCnt].sktdh[0] = sTestOrderRcd.cDateTmResRep_LstMod[0];
	p->pKekka[p->iKekkaCnt].sktdh[1] = sTestOrderRcd.cDateTmResRep_LstMod[1];
	p->pKekka[p->iKekkaCnt].sktdh[2] = sTestOrderRcd.cDateTmResRep_LstMod[2];
	p->pKekka[p->iKekkaCnt].sktdh[3] = sTestOrderRcd.cDateTmResRep_LstMod[3];
	p->pKekka[p->iKekkaCnt].sktdh[4] = '-';
	p->pKekka[p->iKekkaCnt].sktdh[5] = sTestOrderRcd.cDateTmResRep_LstMod[4];
	p->pKekka[p->iKekkaCnt].sktdh[6] = sTestOrderRcd.cDateTmResRep_LstMod[5];
	p->pKekka[p->iKekkaCnt].sktdh[7] = '-';
	p->pKekka[p->iKekkaCnt].sktdh[8] = sTestOrderRcd.cDateTmResRep_LstMod[6];
	p->pKekka[p->iKekkaCnt].sktdh[9] = sTestOrderRcd.cDateTmResRep_LstMod[7];
	p->pKekka[p->iKekkaCnt].sktdh[10] = ' ';
	/* ��������->������� */
	p->pKekka[p->iKekkaCnt].sktdh[11] = sTestOrderRcd.cDateTmResRep_LstMod[8];
	p->pKekka[p->iKekkaCnt].sktdh[12] = sTestOrderRcd.cDateTmResRep_LstMod[9];
	p->pKekka[p->iKekkaCnt].sktdh[13] = ':';
	p->pKekka[p->iKekkaCnt].sktdh[14] = sTestOrderRcd.cDateTmResRep_LstMod[10];
	p->pKekka[p->iKekkaCnt].sktdh[15] = sTestOrderRcd.cDateTmResRep_LstMod[11];
	p->pKekka[p->iKekkaCnt].sktdh[16] = ':';
	p->pKekka[p->iKekkaCnt].sktdh[17] = sTestOrderRcd.cDateTmResRep_LstMod[12];
	p->pKekka[p->iKekkaCnt].sktdh[18] = sTestOrderRcd.cDateTmResRep_LstMod[13];
#endif
	/* No.31 �������ڃR�[�h�ݒ� */
	strcpy( p->pKekka[p->iKekkaCnt].nbkmkcd,sResultRcd.cAppCode );
	/* No.32 �萫�E��ʃt���O�ݒ� */
	GetTstrflg( p->pKekka[p->iKekkaCnt].kmkcd,p->pKekka[p->iKekkaCnt].knsgrp,cWrkCd );
	p->pKekka[p->iKekkaCnt].tstrflg = cWrkCd[0];
	/* No.33 �ޗ��R�[�h�ݒ� */
	strcpy( p->pKekka[p->iKekkaCnt].zrcd,pKenorder[iCnt2].zrcd );
	/* No.34 �D�惌�x���擾 */
	strcpy( p->pKekka[p->iKekkaCnt].ysnlbl,pKenorder[iCnt2].ysnlbl );
	/* No.35 ��lNO�擾 */
	strcpy( p->pKekka[p->iKekkaCnt].kjno,pKenorder[iCnt2].kjno );
	/* No.36 ���ו�NO�\���敪�擾 */
	p->pKekka[p->iKekkaCnt].fkhkknohjkbn = pKenorder[iCnt2].fkhkknohjkbn;
	/* No.37 ���ʊ�lNO�擾 */
	strcpy( p->pKekka[p->iKekkaCnt].tbkjno,pKenorder[iCnt2].tbkjno );
	/* No.38 ���ʊ�l�t���O�擾 */
	p->pKekka[p->iKekkaCnt].tbkjflg = pKenorder[iCnt2].tbkjflg;
	/* No.39 ���^�t�����Ԏ擾 */
	strcpy( p->pKekka[p->iKekkaCnt].htkfkhms,pKenorder[iCnt2].htkfkhms );
	/* No.40 �W���t���O�擾 */
	p->pKekka[p->iKekkaCnt].skflg = pKenorder[iCnt2].skflg;
	/* No.41 ���܃t���O�擾 */
	strcpy( p->pKekka[p->iKekkaCnt].tskflg,pKenorder[iCnt2].tskflg );
	/* No.42 �����t���O�擾 */
	strcpy( p->pKekka[p->iKekkaCnt].tktflg,pKenorder[iCnt2].tktflg );
	/* No.43 ���{��ߔ{���擾 */
/* [ start 060418 068/069 */
	if( sResultRcd.cResStat[0] == 'C' ) {
		SetKsbr(p);
	} else {
		strcpy( p->pKekka[p->iKekkaCnt].jisksbr,pKenorder[iCnt2].ytiksbr );
	}
/* ] end 060418 068/069 */
	/* No.44 �ً}�񍐃t���O�擾 */
	p->pKekka[p->iKekkaCnt].kkflg = pKenorder[iCnt2].kkflg;
	/* No.45 �ً}�˗��t���O�擾 */
	p->pKekka[p->iKekkaCnt].kkiriflg = pKenorder[iCnt2].kkiriflg;
	/* No.46 �ً}�˗����b�gNo�擾 */
	p->pKekka[p->iKekkaCnt].kkirilotno = pKenorder[iCnt2].kkirilotno;
	/* No.50 ���f�[�^�ݒ� */
	strncpy( p->pKekka[p->iKekkaCnt].rawdata,sResultRcd.cDat_MeasrmntVal,15 );

#ifdef _DEBUG_
	printf( "SetKekkaData(%d) : p->pKekka[p->iKekkaCnt].kntno     = %s\n", __LINE__, p->pKekka[p->iKekkaCnt].kntno );
	printf( "SetKekkaData(%d) : p->pKekka[p->iKekkaCnt].knsgrp    = %s\n", __LINE__, p->pKekka[p->iKekkaCnt].knsgrp );
	printf( "SetKekkaData(%d) : p->pKekka[p->iKekkaCnt].kmkcd     = %s\n", __LINE__, p->pKekka[p->iKekkaCnt].kmkcd );
	printf( "SetKekkaData(%d) : p->pKekka[p->iKekkaCnt].knssu     = %d\n", __LINE__, p->pKekka[p->iKekkaCnt].knssu );
	printf( "SetKekkaData(%d) : p->pKekka[p->iKekkaCnt].irino     = %s\n", __LINE__, p->pKekka[p->iKekkaCnt].irino );
	printf( "SetKekkaData(%d) : p->pKekka[p->iKekkaCnt].asyrckid  = %s\n", __LINE__, p->pKekka[p->iKekkaCnt].asyrckid );
	printf( "SetKekkaData(%d) : p->pKekka[p->iKekkaCnt].asyrckpos = %d\n", __LINE__, p->pKekka[p->iKekkaCnt].asyrckpos );
	printf( "SetKekkaData(%d) : p->pKekka[p->iKekkaCnt].bskgok    = %s\n", __LINE__, p->pKekka[p->iKekkaCnt].bskgok );
	printf( "SetKekkaData(%d) : p->pKekka[p->iKekkaCnt].rawdata   = %s\n", __LINE__, p->pKekka[p->iKekkaCnt].rawdata );
#endif
	p->pKekka[p->iKekkaCnt].ctrlno = GetCtrlInf ( p, p->pKekka[p->iKekkaCnt].nbkmkcd ) ;
#ifdef _DEBUG_
	printf( "SetKekkaData(%d) : p->pKekka[p->iKekkaCnt].ctrlno    = %d\n", __LINE__, p->pKekka[p->iKekkaCnt].ctrlno );
#endif
	
	/* No.77 ����SEQ�ݒ� */
	p->pKekka[p->iKekkaCnt].knsseq = pKenorder[iCnt2].knsseq;
	/* No.78 �����o�b�`�ݒ� */
	p->pKekka[p->iKekkaCnt].bthno = pKenorder[iCnt2].bthno;

/* [ start 060420 */
	if( sXbarm_inf[iXbarmCnt].xmchk == 1 ) {
		/* No.79 �v���b�gNo�ݒ� */
		p->pKekka[p->iKekkaCnt].pltno = ((sXbarm_inf[iXbarmCnt].iNumCnt - 1) / sXbarm_inf[iXbarmCnt].xmcount) + 1;
#ifdef _DEBUG_
	printf( "SetKekkaData(%d) : p->pKekka[p->iKekkaCnt].pltno     = %d\n", __LINE__, p->pKekka[p->iKekkaCnt].pltno );
#endif
		/* No.80 �v���b�gSEQ�ݒ� */
		p->pKekka[p->iKekkaCnt].pltseq = ((sXbarm_inf[iXbarmCnt].iNumCnt - 1) % sXbarm_inf[iXbarmCnt].xmcount) + 1;
#ifdef _DEBUG_
	printf( "SetKekkaData(%d) : p->pKekka[p->iKekkaCnt].pltseq    = %d\n", __LINE__, p->pKekka[p->iKekkaCnt].pltseq );
#endif
	}

	/* NO. 91 �␳�t���O */
	int idxKmkmst;
	for ( idxKmkmst = 0 ; idxKmkmst < iKmkmstNum ; idxKmkmst++ ) {
		if ( memcmp ( pKmkmst[idxKmkmst].knsgrp, p->pKekka[p->iKekkaCnt].knsgrp, sizeof ( char ) * 16 ) == 0 && 
		     memcmp ( pKmkmst[idxKmkmst].kmkcd, p->pKekka[p->iKekkaCnt].kmkcd, sizeof ( char ) * 7 ) == 0 ) {
			p->pKekka[p->iKekkaCnt].hsiflg = pKmkmst[idxKmkmst].hsiumflg ; 
			break ;
		}
	}
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
	GetModule(p->pKekka[p->iKekkaCnt].bskgok, &module);
	GetXSaikenFlg(p, p->pKekka[p->iKekkaCnt].knsgrp, p->pKekka[p->iKekkaCnt].kmkcd, &module, sXbarm_inf);
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */
}
/**********************************************************************/
/*                                                                    */
/*   function name : SetKekkaData_Kinkyu                              */
/*                                                                    */
/*   purpose : ���ʏ��ݒ�(�ً})                                     */
/*                                                                    */
/*   data : 2006.04.05                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
void SetKekkaData_Kinkyu(SOCKET_INF* p)
{
	int		cnt;
	int		flg;
	int iWrk;
	int	iCnt;
	char	cWrkCd[32];
	char aFunc[32];
	int		module;

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sSetKekkaData_Kinkyu\n", Now());
#endif

	memset( cWrkCd,0,sizeof(cWrkCd) );
	strncpy( cWrkCd,"       ",7 );
	strncpy( cWrkCd,sResultRcd.cAppCode,strlen(sResultRcd.cAppCode) );
	flg = 0;
	for( cnt=0;cnt<iKinkyuNum;cnt++ ) {
		if( strncmp(cWrkCd,pKinkyu[cnt].nbkmkcd,7) == 0 ) {
			flg = 1;
			break;
		}
	}

	memset(&p->pKekka[p->iKekkaCnt],0,sizeof(Kekka));

	/* No. 1 �����J�n�� */
/* [ start 072/073 060417 */
	memset( cWrkCd,0,sizeof(cWrkCd) );
	CnvtFromKjnsriymd( sSysknrmst.kjnsriymd,cWrkCd );
	strncpy( p->pKekka[p->iKekkaCnt].knskisymd,cWrkCd,strlen(cWrkCd) );
	/* No. 2 ������ */
	strncpy( p->pKekka[p->iKekkaCnt].sriymd,cWrkCd,strlen(cWrkCd) );
/* ] end 072/073 060417 */
	/* No. 3 ����No�ݒ� */
	strncpy( p->pKekka[p->iKekkaCnt].kntno,p->aGouki,2 );
	p->pKekka[p->iKekkaCnt].kntno[2] = '0';
	p->pKekka[p->iKekkaCnt].kntno[3] = '0';
	p->pKekka[p->iKekkaCnt].kntno[4] = '0';
	p->pKekka[p->iKekkaCnt].kntno[5] = '0';
	p->pKekka[p->iKekkaCnt].kntno[6] = '0';
	p->pKekka[p->iKekkaCnt].kntno[7] = '0';
	p->pKekka[p->iKekkaCnt].kntno[8] = '0';
	if( sResultRcd.cInstIdentif[0] == 'C' ) {
		p->pKekka[p->iKekkaCnt].kntno[9] = sResultRcd.cInstIdentif[1];
	} else {
		p->pKekka[p->iKekkaCnt].kntno[9] = '0';
	}
	/* No. 4 ����No�����t���O�ݒ� */
	p->pKekka[p->iKekkaCnt].kntketflg = ' ';
	/* No. 5 �����O���[�v�ݒ� */
	/* No. 6 ���ڃR�[�h�ݒ� */
	if( flg == 1 ) {
		strncpy( p->pKekka[p->iKekkaCnt].kmkcd,pKinkyu[cnt].kmkcd,7 );
	}
	/* No. 5 �����O���[�v�ݒ� */
	if( flg == 1 ) {
		strncpy( p->pKekka[p->iKekkaCnt].knsgrp,pKinkyu[cnt].knsgrp,16 );
	}
	/* No. 7 �����񐔐ݒ� */
	if( sResultRcd.cResStat[0] == 'C' ) {
		p->pKekka[p->iKekkaCnt].knssu = 2;
	} else {
		p->pKekka[p->iKekkaCnt].knssu = 1;
	}
	/* No. 8 �����񐔎}�Ԑݒ� */
	iWrk = 0;
	for( iCnt=0;iCnt<(p->iKekkaCnt);iCnt++ ) {
		if( strncmp(p->pKekka[iCnt].kmkcd,p->pKekka[p->iKekkaCnt].kmkcd,7) == 0 ) {
			++iWrk;
		}
	}
	p->pKekka[p->iKekkaCnt].knssueda = iWrk;
	/* No. 9 �˗��������敪�ݒ� */
	/* No.10 �˗��敪�ݒ� */
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
/*** �ً}STAT�̏ꍇ�̈˗��敪��'Z'�Ƃ��� ***/
/*  p->pKekka[p->iKekkaCnt].irikbn = pKenorder[iCnt2].irikbn; */
    p->pKekka[p->iKekkaCnt].irikbn = 'Z';
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */
	/* No.11 �����H���敪�ݒ� */
	if( sResultRcd.cResStat[0] == 'C' ) {
		p->pKekka[p->iKekkaCnt].ksktkbn = 'K';
	} else {
		p->pKekka[p->iKekkaCnt].ksktkbn = 'A';
	}
	/* No.12 BML��t�N�����ݒ� */
	/* No.13 �˗���No�ݒ� */
	/* No.14 �˗���No�����t���O�ݒ� */
	/* No.15 ��������No�ݒ� */
	/* No.16 �{�݃R�[�h�ݒ� */
	/* No.17 �g���[ID�ݒ� */
	/* No.18 �g���[�|�W�V�����ݒ� */
	/* No.19 �A�b�Z�C���b�N�ݒ� */
	memset( cWrkCd,0,sizeof(cWrkCd) );
	sprintf( cWrkCd ,"%d", atoi(p->cRackNum) );
	strcpy( p->pKekka[p->iKekkaCnt].asyrckid,cWrkCd );
	/* No.20 �A�b�Z�C���b�N�|�W�V�����ݒ� */
	p->pKekka[p->iKekkaCnt].asyrckpos = atoi( p->cRackPosNum );
	/* No.21 �e���ڃR�[�h�ݒ� */
	if( flg == 1 ) {
		memset( cWrkCd,0,sizeof(cWrkCd) );
		GetOyakmkcd( p->pKekka[p->iKekkaCnt].kmkcd,p->pKekka[p->iKekkaCnt].knsgrp,cWrkCd );
		strcpy( p->pKekka[p->iKekkaCnt].oyakmkcd, cWrkCd );
	}
	/* No.22 �Z�N�V�����R�[�h�ݒ� */
	if( flg == 1 ) {
		memset( cWrkCd,0,sizeof(cWrkCd) );
		GetSeccd( p->pKekka[p->iKekkaCnt].kmkcd,p->pKekka[p->iKekkaCnt].knsgrp,cWrkCd );
		strcpy( p->pKekka[p->iKekkaCnt].seccd, cWrkCd );
	}
	/* No.24 �T���v�����O�R�[�h�ݒ� */
	if( flg == 1 ) {
		memset( cWrkCd,0,sizeof(cWrkCd) );
		GetSmpcd( p->pKekka[p->iKekkaCnt].kmkcd,p->pKekka[p->iKekkaCnt].knsgrp,cWrkCd );
		strcpy( p->pKekka[p->iKekkaCnt].smpcd, cWrkCd );
	}
	/* No.25 ���͋@�敪�ݒ� */
	strcpy( p->pKekka[p->iKekkaCnt].bskkbn,aMekbn );
	/* No.26 ���͋@���C���ݒ� */
	strncpy( p->pKekka[p->iKekkaCnt].bsklne,p->aGouki,2 );
	/* No.27 ���u���ʔԍ�->���͋@���@ */
	strncpy( p->pKekka[p->iKekkaCnt].bskgok,p->aGouki,2 );
	// ADD START Haga 2006-08-02
	sBskgokConv ( sResultRcd.cInstIdentif, p->pKekka[p->iKekkaCnt].bskgok ) ;
	/* No.28 ���͋@SEQ�ݒ� */
	p->pKekka[p->iKekkaCnt].bskseq = atoi(sTestOrderRcd.cSampleNo);
	/* No.29 ���͋@�G���[�X�e�[�^�X�ݒ� */
	strncpy( p->pKekka[p->iKekkaCnt].bskerrsts,sResultRcd.cResAbnmlFlg,2 );
	/* No.30 ������� */
	/* ��������ݒ� */
	p->pKekka[p->iKekkaCnt].sktdh[0] = sTestOrderRcd.cDateTmResRep_LstMod[0];
	p->pKekka[p->iKekkaCnt].sktdh[1] = sTestOrderRcd.cDateTmResRep_LstMod[1];
	p->pKekka[p->iKekkaCnt].sktdh[2] = sTestOrderRcd.cDateTmResRep_LstMod[2];
	p->pKekka[p->iKekkaCnt].sktdh[3] = sTestOrderRcd.cDateTmResRep_LstMod[3];
	p->pKekka[p->iKekkaCnt].sktdh[4] = '-';
	p->pKekka[p->iKekkaCnt].sktdh[5] = sTestOrderRcd.cDateTmResRep_LstMod[4];
	p->pKekka[p->iKekkaCnt].sktdh[6] = sTestOrderRcd.cDateTmResRep_LstMod[5];
	p->pKekka[p->iKekkaCnt].sktdh[7] = '-';
	p->pKekka[p->iKekkaCnt].sktdh[8] = sTestOrderRcd.cDateTmResRep_LstMod[6];
	p->pKekka[p->iKekkaCnt].sktdh[9] = sTestOrderRcd.cDateTmResRep_LstMod[7];
	p->pKekka[p->iKekkaCnt].sktdh[10] = ' ';
	/* ��������->������� */
	p->pKekka[p->iKekkaCnt].sktdh[11] = sTestOrderRcd.cDateTmResRep_LstMod[8];
	p->pKekka[p->iKekkaCnt].sktdh[12] = sTestOrderRcd.cDateTmResRep_LstMod[9];
	p->pKekka[p->iKekkaCnt].sktdh[13] = ':';
	p->pKekka[p->iKekkaCnt].sktdh[14] = sTestOrderRcd.cDateTmResRep_LstMod[10];
	p->pKekka[p->iKekkaCnt].sktdh[15] = sTestOrderRcd.cDateTmResRep_LstMod[11];
	p->pKekka[p->iKekkaCnt].sktdh[16] = ':';
	p->pKekka[p->iKekkaCnt].sktdh[17] = sTestOrderRcd.cDateTmResRep_LstMod[12];
	p->pKekka[p->iKekkaCnt].sktdh[18] = sTestOrderRcd.cDateTmResRep_LstMod[13];
	/* No.31 �������ڃR�[�h�ݒ� */
	strcpy( p->pKekka[p->iKekkaCnt].nbkmkcd,sResultRcd.cAppCode );
	/* No.32 �萫�E��ʃt���O�ݒ� */
	if( flg == 1 ) {
		memset( cWrkCd,0,sizeof(cWrkCd) );
		GetTstrflg( p->pKekka[p->iKekkaCnt].kmkcd,p->pKekka[p->iKekkaCnt].knsgrp,cWrkCd );
		p->pKekka[p->iKekkaCnt].tstrflg = cWrkCd[0];
	}
	/* No.33 �ޗ��R�[�h�ݒ� */
	if( strncmp( p->sSndorder.racktype,"S1",2 ) == 0 ) {
		iWrk = 0;
	} else if( strncmp( p->sSndorder.racktype,"S2",2 ) == 0 ) {
		iWrk = 1;
	} else if( strncmp( p->sSndorder.racktype,"S3",2 ) == 0 ) {
		iWrk = 2;
	} else if( strncmp( p->sSndorder.racktype,"S4",2 ) == 0 ) {
		iWrk = 3;
	} else if( strncmp( p->sSndorder.racktype,"S5",2 ) == 0 ) {
		iWrk = 4;
	} else {
		iWrk = 5;
	}
	strcpy( p->pKekka[0].zrcd,aZrCd[iWrk] );
	/* No.34 �D�惌�x���擾 */
	/* No.35 ��lNO�擾 */
	/* No.36 ���ו�NO�\���敪�擾 */
	/* No.37 ���ʊ�lNO�擾 */
	/* No.38 ���ʊ�l�t���O�擾 */
	/* No.39 ���^�t�����Ԏ擾 */
	/* No.40 �W���t���O�擾 */
	/* No.41 ���܃t���O�擾 */
	/* No.42 �����t���O�擾 */
	/* No.43 ���{��ߔ{���擾 */
	SetKsbr(p);
	/* No.44 �ً}�񍐃t���O�擾 */
	/* No.45 �ً}�˗��t���O�擾 */
	/* No.46 �ً}�˗����b�gNo�擾 */
	/* No.50 ���f�[�^�ݒ� */
	strncpy( p->pKekka[p->iKekkaCnt].rawdata,sResultRcd.cDat_MeasrmntVal,15 );

	p->pKekka[p->iKekkaCnt].ctrlno = GetCtrlInf ( p, p->pKekka[p->iKekkaCnt].nbkmkcd ) ;


	/* No.77 ����SEQ�ݒ� */
	/* No.78 �����o�b�`�ݒ� */
/* [ start 060420 */
	if( sXbarm_inf[iXbarmCnt].xmchk == 1 ) {
		/* No.79 �v���b�gNo�ݒ� */
		p->pKekka[p->iKekkaCnt].pltno = ((sXbarm_inf[iXbarmCnt].iNumCnt - 1) / sXbarm_inf[iXbarmCnt].xmcount) + 1;
#ifdef _DEBUG_
	printf( "SetKekkaData_Kinkyu(%d) : p->pKekka[p->iKekkaCnt].pltno = %d\n", __LINE__, p->pKekka[p->iKekkaCnt].pltno );
#endif
		/* No.80 �v���b�gSEQ�ݒ� */
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
/*** �v���b�g�Ή��𒲍����Ƀo�O���� �v���b�gNO����v���b�gSEQ�ɏC�� ***/
        p->pKekka[p->iKekkaCnt].pltseq = ((sXbarm_inf[iXbarmCnt].iNumCnt - 1) % sXbarm_inf[iXbarmCnt].xmcount) + 1;
#ifdef _DEBUG_
	printf( "SetKekkaData_Kinkyu(%d) : p->pKekka[p->iKekkaCnt].pltseq = %d\n", __LINE__, p->pKekka[p->iKekkaCnt].pltseq );
#endif
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */
}

	/* NO. 91 �␳�t���O */
	int idxKmkmst;
	for ( idxKmkmst = 0 ; idxKmkmst < iKmkmstNum ; idxKmkmst++ ) {
		if ( memcmp ( pKmkmst[idxKmkmst].knsgrp, p->pKekka[p->iKekkaCnt].knsgrp, sizeof ( char ) * 16 ) == 0 && 
		     memcmp ( pKmkmst[idxKmkmst].kmkcd, p->pKekka[p->iKekkaCnt].kmkcd, sizeof ( char ) * 7 ) == 0 ) {
			p->pKekka[p->iKekkaCnt].hsiflg = pKmkmst[idxKmkmst].hsiumflg ; 
			break ;
		}
	}
/* [ start 060420 */
	/* No.94 �����t���O */
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
/*** �ً}STAT�̏ꍇ�ł����ʓo�^����K�v�����邽�߁A'H'�̐ݒ�����Ȃ� ***/
	p->pKekka[p->iKekkaCnt].knsflg = ' ';

	GetModule(p->pKekka[p->iKekkaCnt].bskgok, &module);
    GetXSaikenFlg(p, p->pKekka[p->iKekkaCnt].knsgrp, p->pKekka[p->iKekkaCnt].kmkcd, &module, sXbarm_inf);
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */
/* ] end 060420 */
}
/**********************************************************************/
/*                                                                    */
/*   function name : SetKekkaData_NoOrder                             */
/*                                                                    */
/*   purpose : ���ʏ��ݒ�                                           */
/*                                                                    */
/*   data : 2006.03.01                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
void SetKekkaData_NoOrder(SOCKET_INF* p)
{
	int iWrk;
	int	iCnt;
	char	cWrkCd[32];
	char aFunc[32];
	int		module;

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sSetKekkaData_NoOrder\n", Now());
#endif

	memset(&p->pKekka[p->iKekkaCnt],0,sizeof(Kekka));

	/* No. 1 �����J�n�� */
/* [ start 072/073 060417 */
	memset( cWrkCd,0,sizeof(cWrkCd) );
	CnvtFromKjnsriymd( sSysknrmst.kjnsriymd,cWrkCd );
	strncpy( p->pKekka[p->iKekkaCnt].knskisymd,cWrkCd,strlen(cWrkCd) );
	/* No. 2 ������ */
	strncpy( p->pKekka[p->iKekkaCnt].sriymd,cWrkCd,strlen(cWrkCd) );
/* ] end 072/073 060417 */
	/* No. 3 ����No�ݒ� */
	strncpy( p->pKekka[p->iKekkaCnt].kntno,p->aGouki,2 );
	p->pKekka[p->iKekkaCnt].kntno[2] = '0';
	p->pKekka[p->iKekkaCnt].kntno[3] = '0';
	p->pKekka[p->iKekkaCnt].kntno[4] = '0';
	p->pKekka[p->iKekkaCnt].kntno[5] = '0';
	p->pKekka[p->iKekkaCnt].kntno[6] = '0';
	p->pKekka[p->iKekkaCnt].kntno[7] = '0';
	p->pKekka[p->iKekkaCnt].kntno[8] = '0';
	if( sResultRcd.cInstIdentif[0] == 'C' ) {
		p->pKekka[p->iKekkaCnt].kntno[9] = sResultRcd.cInstIdentif[1];
	} else {
		p->pKekka[p->iKekkaCnt].kntno[9] = '0';
	}
	/* No. 4 ����No�����t���O�ݒ� */
	p->pKekka[p->iKekkaCnt].kntketflg = ' ';
	/* No. 5 �����O���[�v�ݒ� */
	/* No. 6 ���ڃR�[�h�ݒ� */
	memset( cWrkCd,0,sizeof(cWrkCd) );
	GetKmkcd( 0,sResultRcd.cAppCode,cWrkCd );
	strcpy( p->pKekka[p->iKekkaCnt].kmkcd, cWrkCd );
	/* No. 5 �����O���[�v�ݒ� */
	/* No. 7 �����񐔐ݒ� */
	p->pKekka[p->iKekkaCnt].knssu = 1;
	/* No. 8 �����񐔎}�Ԑݒ� */
	iWrk = 0;
	//
	for( iCnt=0;iCnt<(p->iKekkaCnt);iCnt++ ) {
		if( strncmp(p->pKekka[iCnt].kmkcd,p->pKekka[p->iKekkaCnt].kmkcd,7) == 0 ) {
			++iWrk;
		}
	}
	p->pKekka[p->iKekkaCnt].knssueda = iWrk;
	/* No. 9 �˗��������敪�ݒ� */
	/* No.10 �˗��敪�ݒ� */
	/* No.11 �����H���敪�ݒ� */
	p->pKekka[p->iKekkaCnt].ksktkbn = 'A';
	/* No.12 BML��t�N�����ݒ� */
	/* No.13 �˗���No�ݒ� */
	/* No.14 �˗���No�����t���O�ݒ� */
	/* No.15 ��������No�ݒ� */
	/* No.16 �{�݃R�[�h�ݒ� */
	/* No.17 �g���[ID�ݒ� */
	/* No.18 �g���[�|�W�V�����ݒ� */
	/* No.19 �A�b�Z�C���b�N�ݒ� */
	memset( cWrkCd,0,sizeof(cWrkCd) );
	sprintf( cWrkCd ,"%d", atoi(p->cRackNum) );
	strcpy( p->pKekka[p->iKekkaCnt].asyrckid,cWrkCd );
	/* No.20 �A�b�Z�C���b�N�|�W�V�����ݒ� */
	p->pKekka[p->iKekkaCnt].asyrckpos = atoi( p->cRackPosNum );
	/* No.21 �e���ڃR�[�h�ݒ� */
	/* No.22 �Z�N�V�����R�[�h�ݒ� */
	/* No.24 �T���v�����O�R�[�h�ݒ� */
	/* No.25 ���͋@�敪�ݒ� */
	strcpy( p->pKekka[p->iKekkaCnt].bskkbn,aMekbn );
	/* No.26 ���͋@���C���ݒ� */
	strncpy( p->pKekka[p->iKekkaCnt].bsklne,p->aGouki,2 );
	/* No.27 ���u���ʔԍ�->���͋@���@ */
	strncpy( p->pKekka[p->iKekkaCnt].bskgok,p->aGouki,2 );
	/* ADD START Haga 2006-08-02 */
	sBskgokConv ( sResultRcd.cInstIdentif, p->pKekka[p->iKekkaCnt].bskgok ) ;
	/* No.28 ���͋@SEQ�ݒ� */
	p->pKekka[p->iKekkaCnt].bskseq = atoi(sTestOrderRcd.cSampleNo);
	/* No.29 ���͋@�G���[�X�e�[�^�X�ݒ� */
	strncpy( p->pKekka[p->iKekkaCnt].bskerrsts,sResultRcd.cResAbnmlFlg,2 );
	/* No.30 ������� */
	/* ��������ݒ� */
	p->pKekka[p->iKekkaCnt].sktdh[0] = sTestOrderRcd.cDateTmResRep_LstMod[0];
	p->pKekka[p->iKekkaCnt].sktdh[1] = sTestOrderRcd.cDateTmResRep_LstMod[1];
	p->pKekka[p->iKekkaCnt].sktdh[2] = sTestOrderRcd.cDateTmResRep_LstMod[2];
	p->pKekka[p->iKekkaCnt].sktdh[3] = sTestOrderRcd.cDateTmResRep_LstMod[3];
	p->pKekka[p->iKekkaCnt].sktdh[4] = '-';
	p->pKekka[p->iKekkaCnt].sktdh[5] = sTestOrderRcd.cDateTmResRep_LstMod[4];
	p->pKekka[p->iKekkaCnt].sktdh[6] = sTestOrderRcd.cDateTmResRep_LstMod[5];
	p->pKekka[p->iKekkaCnt].sktdh[7] = '-';
	p->pKekka[p->iKekkaCnt].sktdh[8] = sTestOrderRcd.cDateTmResRep_LstMod[6];
	p->pKekka[p->iKekkaCnt].sktdh[9] = sTestOrderRcd.cDateTmResRep_LstMod[7];
	p->pKekka[p->iKekkaCnt].sktdh[10] = ' ';
	/* ��������->������� */
	p->pKekka[p->iKekkaCnt].sktdh[11] = sTestOrderRcd.cDateTmResRep_LstMod[8];
	p->pKekka[p->iKekkaCnt].sktdh[12] = sTestOrderRcd.cDateTmResRep_LstMod[9];
	p->pKekka[p->iKekkaCnt].sktdh[13] = ':';
	p->pKekka[p->iKekkaCnt].sktdh[14] = sTestOrderRcd.cDateTmResRep_LstMod[10];
	p->pKekka[p->iKekkaCnt].sktdh[15] = sTestOrderRcd.cDateTmResRep_LstMod[11];
	p->pKekka[p->iKekkaCnt].sktdh[16] = ':';
	p->pKekka[p->iKekkaCnt].sktdh[17] = sTestOrderRcd.cDateTmResRep_LstMod[12];
	p->pKekka[p->iKekkaCnt].sktdh[18] = sTestOrderRcd.cDateTmResRep_LstMod[13];
	/* No.31 �������ڃR�[�h�ݒ� */
	strcpy( p->pKekka[p->iKekkaCnt].nbkmkcd,sResultRcd.cAppCode );
	/* No.32 �萫�E��ʃt���O�ݒ� */
	/* No.33 �ޗ��R�[�h�ݒ� */
	if( strncmp( p->sSndorder.racktype,"S1",2 ) == 0 ) {
		iWrk = 0;
	} else if( strncmp( p->sSndorder.racktype,"S2",2 ) == 0 ) {
		iWrk = 1;
	} else if( strncmp( p->sSndorder.racktype,"S3",2 ) == 0 ) {
		iWrk = 2;
	} else if( strncmp( p->sSndorder.racktype,"S4",2 ) == 0 ) {
		iWrk = 3;
	} else if( strncmp( p->sSndorder.racktype,"S5",2 ) == 0 ) {
		iWrk = 4;
	} else {
		iWrk = 5;
	}
	strcpy( p->pKekka[p->iKekkaCnt].zrcd,aZrCd[iWrk] );
	/* No.34 �D�惌�x���擾 */
	/* No.35 ��lNO�擾 */
	/* No.36 ���ו�NO�\���敪�擾 */
	/* No.37 ���ʊ�lNO�擾 */
	/* No.38 ���ʊ�l�t���O�擾 */
	/* No.39 ���^�t�����Ԏ擾 */
	/* No.40 �W���t���O�擾 */
	/* No.41 ���܃t���O�擾 */
	/* No.42 �����t���O�擾 */
	/* No.43 ���{��ߔ{���擾 */
	SetKsbr(p);
	/* No.44 �ً}�񍐃t���O�擾 */
	/* No.45 �ً}�˗��t���O�擾 */
	/* No.46 �ً}�˗����b�gNo�擾 */
	/* No.50 ���f�[�^�ݒ� */
	strncpy( p->pKekka[p->iKekkaCnt].rawdata,sResultRcd.cDat_MeasrmntVal,15 );

	p->pKekka[p->iKekkaCnt].ctrlno = GetCtrlInf ( p, p->pKekka[p->iKekkaCnt].nbkmkcd ) ;

	/* No.77 ����SEQ�ݒ� */
	/* No.78 �����o�b�`�ݒ� */
	/* No.79 �v���b�gNo�ݒ� */
	/* No.80 �v���b�gSEQ�ݒ� */

	/* NO. 91 �␳�t���O */
	int idxKmkmst;
	for ( idxKmkmst = 0 ; idxKmkmst < iKmkmstNum ; idxKmkmst++ ) {
		if ( memcmp ( pKmkmst[idxKmkmst].knsgrp, p->pKekka[p->iKekkaCnt].knsgrp, sizeof ( char ) * 16 ) == 0 && 
		     memcmp ( pKmkmst[idxKmkmst].kmkcd, p->pKekka[p->iKekkaCnt].kmkcd, sizeof ( char ) * 7 ) == 0 ) {
			p->pKekka[p->iKekkaCnt].hsiflg = pKmkmst[idxKmkmst].hsiumflg ; 
			break ;
		}
	}
/* [ start 060420 */
	/* No.94 �����t���O */
	p->pKekka[p->iKekkaCnt].knsflg = 'H';
/* ] end 060420 */
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
/*** �����Ώۍ��ڃR�[�h�̓}�X�^����擾�ɕύX ***/
    /* ADD E.Osada 2006-08-21 ������񃌃R�[�h�̏ꍇ�̓G���[���o�͂��Ȃ� */
    if (ChkKesseiKmkcd(&p->pKekka[p->iKekkaCnt]) == '1') {
		/* �������Ȃ� */
	} else {
	}

	GetModule(p->pKekka[p->iKekkaCnt].bskgok, &module);
    GetXSaikenFlg(p, p->pKekka[p->iKekkaCnt].knsgrp, p->pKekka[p->iKekkaCnt].kmkcd, &module, sXbarm_inf);
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */
}
/**********************************************************************/
/*                                                                    */
/*   function name : SetKekkaData_PCR                                 */
/*                                                                    */
/*   purpose : ��F�L�����u���[�V�������ʏ��ݒ�                     */
/*                                                                    */
/*   data : 2006.03.01                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
void SetKekkaData_PCR(SOCKET_INF* p,int iCnt2,int iNum)
{
	int		iWrk;
	char	cWrkCd[32];
	char aFunc[32];
	int		module;

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sSetKekkaData_PCR\n", Now());
#endif

	memset(&p->pKekka[0],0,sizeof(Kekka));

	/* No. 1 �����J�n�� */
/* [ start 072/073 060417 */
	memset( cWrkCd,0,sizeof(cWrkCd) );
	CnvtFromKjnsriymd( sSysknrmst.kjnsriymd,cWrkCd );
	strncpy( p->pKekka[0].knskisymd,cWrkCd,strlen(cWrkCd) );
	/* No. 2 ������ */
	strncpy( p->pKekka[0].sriymd,cWrkCd,strlen(cWrkCd) );
/* ] end 072/073 060417 */
	/* No. 3 ����No�ݒ� */
	strncpy( p->pKekka[0].kntno,p->aGouki,2 );
	if( sCalbRcd.cModuleId[0] == 'C' ) {
		p->pKekka[0].kntno[2] = '0';
		p->pKekka[0].kntno[3] = sCalbRcd.cModuleId[1];
		p->pKekka[0].kntno[4] = '0';
		p->pKekka[0].kntno[5] = sCalbRcd.cModuleId[2];
	} else {
		p->pKekka[0].kntno[2] = '0';
		p->pKekka[0].kntno[3] = '0';
		p->pKekka[0].kntno[4] = '0';
		p->pKekka[0].kntno[5] = sCalbRcd.cModuleId[3];
	}
	struct timeval tv;
	gettimeofday( &tv, NULL );
	struct tm * t = localtime(&(tv.tv_sec));
	sprintf(&(p->pKekka[0].kntno[6]), "%02d%02d%02d%1ld", t->tm_hour, t->tm_min, t->tm_sec, (tv.tv_usec/100000)%10);
	
	/* No. 4 ����No�����t���O�ݒ� */
	p->pKekka[0].kntketflg = ' ';
	/* No. 6 ���ڃR�[�h�ݒ� */
	memset( cWrkCd,0,sizeof(cWrkCd) );
	GetKmkcd( 0,sCalbRcd.cTestCode,cWrkCd );
	strcpy( p->pKekka[0].kmkcd, cWrkCd );
	/* No. 5 �����O���[�v�ݒ� */
	/* No. 6 ���ڃR�[�h�ݒ� */
	/* No. 7 �����񐔐ݒ� */
	p->pKekka[0].knssu = (short)(iCnt2+1);
	/* No. 8 �����񐔎}�Ԑݒ� */
	p->pKekka[0].knssueda = 9000;
	if( iNum == 1 ) {
		p->pKekka[0].knssueda += 1;
	} else {
		p->pKekka[0].knssueda += 2;
	}
	/* No. 9 �˗��������敪�ݒ� */
	p->pKekka[0].irihsmkbn = '2';
	/* No.10 �˗��敪�ݒ� */
	p->pKekka[0].irikbn = 'Y';
	/* No.11 �����H���敪�ݒ� */
	p->pKekka[0].ksktkbn = 'A';
	/* No.19 �A�b�Z�C���b�N�ݒ� */
	strcpy( p->pKekka[0].asyrckid,"PCR" );
	/* No.20 �A�b�Z�C���b�N�|�W�V�����ݒ� */
	p->pKekka[0].asyrckpos = 1;
	/* No.21 �e���ڃR�[�h�ݒ� */
	/* No.22 �Z�N�V�����R�[�h�ݒ� */
	/* No.24 �T���v�����O�R�[�h�ݒ� */
	/* No.25 ���͋@�敪�ݒ� */
	strcpy( p->pKekka[0].bskkbn,aMekbn );
	/* No.26 ���͋@���C���ݒ� */
	strncpy( p->pKekka[0].bsklne,p->aGouki,2 );
	/* No.27 ���u���ʔԍ�->���͋@���@ */
	strncpy( p->pKekka[0].bskgok,p->aGouki,2 );
	sBskgokConv ( sCalbRcd.cModuleId, p->pKekka[0].bskgok ) ;
	/* No.29 ���͋@�G���[�X�e�[�^�X�ݒ� */
	strncpy( p->pKekka[0].bskerrsts,sCalbRcd.cCalbAlarm,2 );
	/* No.31 �������ڃR�[�h�ݒ� */
	strncpy( p->pKekka[0].nbkmkcd,sCalbRcd.cTestCode,5 );
	/* No.32 �萫�E��ʃt���O�ݒ� */
	/* No.33 �ޗ��R�[�h */
	/* No.50 ���f�[�^ */
	memset( p->pKekka[0].rawdata,0,sizeof(p->pKekka[0].rawdata) );
	if( iNum == 1 ) {
		iWrk = strlen( sCalbRcd.sStdDat[iCnt2].c1stDat );
		strncpy( p->pKekka[0].rawdata,sCalbRcd.sStdDat[iCnt2].c1stDat,iWrk );
	} else {
		iWrk = strlen( sCalbRcd.sStdDat[iCnt2].c2ndDat );
		strncpy( p->pKekka[0].rawdata,sCalbRcd.sStdDat[iCnt2].c2ndDat,iWrk );
	}
	/* No.52 �������ʂQ */
	memset( p->pKekka[0].knskka2,0,sizeof(p->pKekka[0].knskka2) );
	if( iNum == 1 ) {
		iWrk = strlen( sCalbRcd.sStdDat[iCnt2].c1stIni_LstDat );
		strncpy( p->pKekka[0].knskka2,sCalbRcd.sStdDat[iCnt2].c1stIni_LstDat,iWrk );
	} else {
		iWrk = strlen( sCalbRcd.sStdDat[iCnt2].c2ndIni_LstDat );
		strncpy( p->pKekka[0].knskka2,sCalbRcd.sStdDat[iCnt2].c2ndIni_LstDat,iWrk );
	}
	/* No.54 �������ʕ⑫ */
	strncpy( p->pKekka[0].kkahskcd,sCalbRcd.sStdDat[iCnt2].cDatAlarm,3 );
	/* No.55 �\������ */
	strncpy( p->pKekka[0].hjkka,sCalbRcd.sStdDat[iCnt2].cProZoneVal,6 );
	/* No.79 �v���b�gNo�ݒ� */
	/* No.80 �v���b�gSEQ�ݒ� */
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
	GetModule(p->pKekka[0].bskgok, &module);
    GetXSaikenFlg(p, p->pKekka[0].knsgrp, p->pKekka[0].kmkcd, &module, sXbarm_inf);
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <--> */
}
/**********************************************************************/
/*                                                                    */
/*   function name : SetKekkaData_ISE                                 */
/*                                                                    */
/*   purpose : ISE�L�����u���[�V�������ʏ��ݒ�                     */
/*                                                                    */
/*   data : 2006.03.01                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
void SetKekkaData_ISE(SOCKET_INF* p,int iType)
{
	char	cWrkCd[32];
	char aFunc[32];
	int		module;

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sSetKekkaData_ISE\n", Now());
#endif

	memset(&p->pKekka[0],0,sizeof(Kekka));

	/* No. 1 �����J�n�� */
/* [ start 072/073 060417 */
	memset( cWrkCd,0,sizeof(cWrkCd) );
	CnvtFromKjnsriymd( sSysknrmst.kjnsriymd,cWrkCd );
	strncpy( p->pKekka[0].knskisymd,cWrkCd,strlen(cWrkCd) );
	/* No. 2 ������ */
	strncpy( p->pKekka[0].sriymd,cWrkCd,strlen(cWrkCd) );
/* ] end 072/073 060417 */
	/* No. 3 ����No�ݒ� */
	strncpy( p->pKekka[0].kntno,p->aGouki,2 );
	if( sCalbRcd.cModuleId[0] == 'C' ) {
		p->pKekka[0].kntno[2] = '0';
		p->pKekka[0].kntno[3] = sCalbRcd.cModuleId[1];
		p->pKekka[0].kntno[4] = '0';
		p->pKekka[0].kntno[5] = sCalbRcd.cModuleId[2];
	} else {
		p->pKekka[0].kntno[2] = '0';
		p->pKekka[0].kntno[3] = '0';
		p->pKekka[0].kntno[4] = '0';
		p->pKekka[0].kntno[5] = sCalbRcd.cModuleId[3];
	}
	struct timeval tv;
	gettimeofday( &tv, NULL );
	struct tm * t = localtime(&(tv.tv_sec));
	sprintf(&(p->pKekka[0].kntno[6]), "%02d%02d%02d%01ld", t->tm_hour, t->tm_min, t->tm_sec, (tv.tv_usec/100000)%10);

	/* No. 4 ����No�����t���O�ݒ� */
	p->pKekka[0].kntketflg = ' ';
	/* No. 6 ���ڃR�[�h�ݒ� */
	memset( cWrkCd,0,sizeof(cWrkCd) );
	if( iType == ITEM_NA ) {
		GetKmkcd( 0,aNa_code,cWrkCd );
	} else if ( iType == ITEM_K ) {
		GetKmkcd( 0,aK_code,cWrkCd );
	} else {
		GetKmkcd( 0,aCl_code,cWrkCd );
	}
	strcpy( p->pKekka[0].kmkcd, cWrkCd );
	/* No. 5 �����O���[�v�ݒ� */
	/* No. 6 ���ڃR�[�h�ݒ� */
	/* No. 7 �����񐔐ݒ� */
	p->pKekka[0].knssu = 1;
	/* No. 8 �����񐔎}�Ԑݒ� */
	p->pKekka[0].knssueda = 9001;
	/* No. 9 �˗��������敪�ݒ� */
	p->pKekka[0].irihsmkbn = '2';	//�L�����u���[�V�������͂Q�ɐݒ�
	/* No.10 �˗��敪�ݒ� */
	p->pKekka[0].irikbn = 'Y';
	/* No.11 �����H���敪�ݒ� */
	p->pKekka[0].ksktkbn = 'A';
	/* No.19 �A�b�Z�C���b�N�ݒ� */
	strcpy( p->pKekka[0].asyrckid,"ICR" );
	/* No.20 �A�b�Z�C���b�N�|�W�V�����ݒ� */
	p->pKekka[0].asyrckpos = 1;
	/* No.21 �e���ڃR�[�h�ݒ� */
	/* No.22 �Z�N�V�����R�[�h�ݒ� */
	/* No.24 �T���v�����O�R�[�h�ݒ� */
	/* No.25 ���͋@�敪�ݒ� */
	strcpy( p->pKekka[0].bskkbn,aMekbn );
	/* No.26 ���͋@���C���ݒ� */
	strncpy( p->pKekka[0].bsklne,p->aGouki,2 );
	/* No.27 ���u���ʔԍ�->���͋@���@ */
	strncpy( p->pKekka[0].bskgok,p->aGouki,2 );
	p->pKekka[0].bskgok[2] = '0';
	p->pKekka[0].bskgok[3] = '0';
	p->pKekka[0].bskgok[4] = '0';
	if( sCalbRcd.cModuleId[3] == '\0' ) {
		p->pKekka[0].bskgok[5] = '1';
	} else {
		p->pKekka[0].bskgok[5] = sCalbRcd.cModuleId[3];
	}
	/* No.29 ���͋@�G���[�X�e�[�^�X�ݒ� */
	strncpy( p->pKekka[0].bskerrsts,sCalbRcd.sIseCalbItem[iType].cCalbAlarm,2 );
	/* No.31 �������ڃR�[�h�ݒ� */
	if( iType == ITEM_NA ) {
		strcpy( p->pKekka[0].nbkmkcd,aNa_code );
	} else if ( iType == ITEM_K ) {
		strcpy( p->pKekka[0].nbkmkcd,aK_code );
	} else {
		strcpy( p->pKekka[0].nbkmkcd,aCl_code );
	}
	/* No.32 �萫�E��ʃt���O�ݒ� */
	/* No.51 �������ʂP */
	memset( cWrkCd,0,sizeof(cWrkCd) );
	strncpy( cWrkCd,sCalbRcd.sIseCalbItem[iType].cAlmNaibuKiden,3 );
	strncat( cWrkCd,sCalbRcd.sIseCalbItem[iType].cAlmLow,3 );
	strncat( cWrkCd,sCalbRcd.sIseCalbItem[iType].cAlmHigh,3 );
	strncat( cWrkCd,sCalbRcd.sIseCalbItem[iType].cAlmCalbKiden,3 );
	strncpy( p->pKekka[0].knskka1,"            ",12 );
	strncpy( &p->pKekka[0].knskka1[12-strlen(cWrkCd)],cWrkCd,strlen(cWrkCd) );
	/* No.52 �������ʂQ */
	strncpy( p->pKekka[0].knskka2,sCalbRcd.sIseCalbItem[iType].cDatNaibuKiden,6 );
	strncat( p->pKekka[0].knskka2,sCalbRcd.sIseCalbItem[iType].cDatLow,6 );
	strncat( p->pKekka[0].knskka2,sCalbRcd.sIseCalbItem[iType].cDatHigh,6 );
	strncat( p->pKekka[0].knskka2,sCalbRcd.sIseCalbItem[iType].cDatCalbKiden,6 );
	/* No.54 �������ʕ⑫ */
	strncpy( p->pKekka[0].kkahskcd,sCalbRcd.sIseCalbItem[iType].cAlmSlpe,3 );
	/* No.55 �\������ */
	strncpy( p->pKekka[0].hjkka,sCalbRcd.sIseCalbItem[iType].cDatSlpe,6 );
	strncat( p->pKekka[0].hjkka,sCalbRcd.sIseCalbItem[iType].cDatNaibu,6 );
	strncat( p->pKekka[0].hjkka,sCalbRcd.sIseCalbItem[iType].cDatCalb,6 );
	strncat( p->pKekka[0].hjkka,sCalbRcd.sIseCalbItem[iType].cDatHosei,6 );
	/* No.56 �w���iSDI) */
	strncpy( p->pKekka[0].sdi,sCalbRcd.sIseCalbItem[iType].cAlmNaibuNodo,3 );
	/* No.57 ���ʃR�����g�P */
	strncpy( p->pKekka[0].kkacmt1,sCalbRcd.sIseCalbItem[iType].cAlmCalbNodo,3 );
	/* No.58 ���ʃR�����g�Q */
	strncpy( p->pKekka[0].kkacmt2,sCalbRcd.sIseCalbItem[iType].cAlmHosei,3 );
	/* No.79 �v���b�gNo�ݒ� */
	/* No.80 �v���b�gSEQ�ݒ� */

/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
	GetModule(p->pKekka[0].bskgok, &module);
    GetXSaikenFlg(p, p->pKekka[0].knsgrp, p->pKekka[0].kmkcd, &module, sXbarm_inf);
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */
}
/**********************************************************************/
/*                                                                    */
/*   function name : SetKsbr                                          */
/*                                                                    */
/*   purpose : ��ߔ{���ݒ�                                           */
/*                                                                    */
/*   data : 2006.03.20                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
void SetKsbr(SOCKET_INF* p)
{
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sSetKsbr\n", Now());
#endif

/* [ start 060418 068/069 */
/* UPDATE nagata 2006/08/05 ���{��ߔ{�� "0D"�̕Ԃ�l��"dec"�̂��߁A�ύX���s���B */
/*        ���Ƃ���"Dec"�Ŕ��f���Ă����B */
	if( strcmp( sResultRcd.cDilution,"3" ) == 0 ) {
		sprintf( &(p->pKekka[p->iKekkaCnt].jisksbr[1]),"%d",aKskbrt[0] );
	} else if(strcmp( sResultRcd.cDilution,"5" ) == 0 ) {
		sprintf( &(p->pKekka[p->iKekkaCnt].jisksbr[1]),"%d",aKskbrt[1] );
	} else if(strcmp( sResultRcd.cDilution,"10" ) == 0 ) {
		sprintf( &(p->pKekka[p->iKekkaCnt].jisksbr[1]),"%d",aKskbrt[2] );
	} else if(strcmp( sResultRcd.cDilution,"20" ) == 0 ) {
		sprintf( &(p->pKekka[p->iKekkaCnt].jisksbr[1]),"%d",aKskbrt[3] );
	} else if(strcmp( sResultRcd.cDilution,"50" ) == 0 ) {
		sprintf( &(p->pKekka[p->iKekkaCnt].jisksbr[1]),"%d",aKskbrt[4] );
	} else if(strcmp( sResultRcd.cDilution,"dec" ) == 0) {
		sprintf( &(p->pKekka[p->iKekkaCnt].jisksbr[1]),"%s","0D" );
	} else {
		p->pKekka[p->iKekkaCnt].jisksbr[1] = '1';
	}
	p->pKekka[p->iKekkaCnt].jisksbr[0] = 'L';
/* ] end 060418 068/069 */
}
/**********************************************************************/
/*                                                                    */
/*   function name : SetCtrlkkaData                                   */
/*                                                                    */
/*   purpose : �R���g���[�����ʏ��ݒ�                               */
/*                                                                    */
/*   data : 2006.03.01                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
void SetCtrlkkaData(SOCKET_INF* p, char* kmkcd)
{
	int		cnt;
	int		flg;
	double	fWrk;
	char	cWrkCd[32];
	char	cTmp[16];
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sSetCtrlkkaData\n", Now());
#endif

	memset( cWrkCd,0,sizeof(cWrkCd) );
	strncpy( cWrkCd,"       ",7 );
	strncpy( cWrkCd,sResultRcd.cAppCode,strlen(sResultRcd.cAppCode) );
	flg = 0;
	for( cnt=0;cnt<iCtrlmstNum;cnt++ ) {
		if( (strncmp(cWrkCd,pCtrlmst[cnt].nbkmkcd,7) == 0)
			&& ((atoi(sTestOrderRcd.cSampleNo)/1000) == atoi(pCtrlmst[cnt].ctrlsbt)) ) {
			flg = 1;
			break;
		}
	}

	memset(&p->sCtrlkka,0,sizeof(Ctrlkka));

	/* No. 1 �����J�n�� */
/* [ start 072/073 060417 */
	memset( cWrkCd,0,sizeof(cWrkCd) );
	CnvtFromKjnsriymd( sSysknrmst.kjnsriymd,cWrkCd );
	strncpy( p->sCtrlkka.knskisymd,cWrkCd,strlen(cWrkCd) );
/* ] end 072/073 060417 */
	/* No.2 ���͋@�敪�ݒ� */
	strcpy( p->sCtrlkka.bskkbn,aMekbn );
	/* No.3 ���͋@���C���ݒ� */
	strncpy( p->sCtrlkka.bsklne,p->aGouki,2 );
	/* No.4 ���u���ʔԍ�->���͋@���@ */
	strncpy( p->sCtrlkka.bskgok,p->aGouki,2 );
	sBskgokConv ( sResultRcd.cInstIdentif, p->sCtrlkka.bskgok ) ;
	/* No. 6 ���ڃR�[�h�ݒ� */
	strcpy( p->sCtrlkka.kmkcd, kmkcd );
	/* No. 5 �����O���[�v�ݒ� */
	/* No. 6 ���ڃR�[�h�ݒ� */
	/* No.7 �������ڃR�[�h�ݒ� */
	strncpy( p->sCtrlkka.nbkmkcd,sResultRcd.cAppCode,5 );
	/* No.8 �R���g���[��No�ݒ� */
	p->sCtrlkka.ctrlno = GetNowCtrlNo(p, (atoi(sTestOrderRcd.cSampleNo)%1000), sTestOrderRcd.cDateTmResRep_LstMod);
	/* No.9 �R���g���[����ʐݒ� */
	sprintf(cTmp, "%d", atoi(sTestOrderRcd.cSampleNo)/1000);
	strncpy(p->sCtrlkka.ctrlsbt, cTmp, 20);

	/* No.10 �R���g���[����ʎ}�Ԑݒ� */
	p->sCtrlkka.ctrlsbteda = 0;
	/* No.11 �R���g���[�����x���ݒ� */
	if( flg == 1 ) {
		strncpy( p->sCtrlkka.ctrllbl,pCtrlmst[cnt].ctrllbl,2 );
	}
	/* No.12 �萫�E��ʃt���O�ݒ� */
	/* No.13 �A�b�Z�C���b�N�ݒ� */
	strcpy( p->sCtrlkka.asyrckid,p->cRackNum );
	/* No.14 �A�b�Z�C���b�N�|�W�V�����ݒ� */
	p->sCtrlkka.asyrckpos = atoi(p->cRackPosNum);
	/* No.19 ���򃍃b�gNo�ݒ� */
	if( flg == 1 ) {
		strncpy( p->sCtrlkka.syklotno,pCtrlmst[cnt].syklotno,20 );
	}
	/* No.20 ����l�ݒ� */
	strncpy( p->sCtrlkka.sktti,sResultRcd.cDat_MeasrmntVal,15 );
	/* No.21 ���Z�l�ݒ� */
	strncpy( p->sCtrlkka.knzti,sResultRcd.cDat_MeasrmntVal,15 );
	/* No.23 ������� */
	/* ��������ݒ� */
	p->sCtrlkka.sktdh[0] = sTestOrderRcd.cDateTmResRep_LstMod[0];
	p->sCtrlkka.sktdh[1] = sTestOrderRcd.cDateTmResRep_LstMod[1];
	p->sCtrlkka.sktdh[2] = sTestOrderRcd.cDateTmResRep_LstMod[2];
	p->sCtrlkka.sktdh[3] = sTestOrderRcd.cDateTmResRep_LstMod[3];
	p->sCtrlkka.sktdh[4] = '-';
	p->sCtrlkka.sktdh[5] = sTestOrderRcd.cDateTmResRep_LstMod[4];
	p->sCtrlkka.sktdh[6] = sTestOrderRcd.cDateTmResRep_LstMod[5];
	p->sCtrlkka.sktdh[7] = '-';
	p->sCtrlkka.sktdh[8] = sTestOrderRcd.cDateTmResRep_LstMod[6];
	p->sCtrlkka.sktdh[9] = sTestOrderRcd.cDateTmResRep_LstMod[7];
	p->sCtrlkka.sktdh[10] = ' ';
	/* ��������->������� */
	p->sCtrlkka.sktdh[11] = sTestOrderRcd.cDateTmResRep_LstMod[8];
	p->sCtrlkka.sktdh[12] = sTestOrderRcd.cDateTmResRep_LstMod[9];
	p->sCtrlkka.sktdh[13] = ':';
	p->sCtrlkka.sktdh[14] = sTestOrderRcd.cDateTmResRep_LstMod[10];
	p->sCtrlkka.sktdh[15] = sTestOrderRcd.cDateTmResRep_LstMod[11];
	p->sCtrlkka.sktdh[16] = ':';
	p->sCtrlkka.sktdh[17] = sTestOrderRcd.cDateTmResRep_LstMod[12];
	p->sCtrlkka.sktdh[18] = sTestOrderRcd.cDateTmResRep_LstMod[13];
	/* No.24 �R���g���[����� */
	if( flg == 1 ) {
		fWrk = atof(sResultRcd.cDat_MeasrmntVal) - atof(pCtrlmst[cnt].ctrlx);
        /* CHG 2006-09-29 Nagata [0 �� 0.0] */
		if( atof(pCtrlmst[cnt].ctrlsd) > 0.0 ) {
			fWrk = fWrk / atof(pCtrlmst[cnt].ctrlsd);
            /* CHG 2006-09-29 Nagata */
            if(fWrk < 0.0 ){
                p->sCtrlkka.ctrljti = (int)(fWrk - 0.9999);
            }
            else{
                p->sCtrlkka.ctrljti = (int)(fWrk + 0.9999);
            }
		}
	}
	/* No.25 �`�F�b�N�ς݃t���O�ݒ� */
	p->sCtrlkka.chkzmflg = '0';
	/* No.28 �Z����Ԑݒ� */
	p->sCtrlkka.kosijt = '0';
}

/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
/*** �v���b�gNO��ێ����邽�߁AXbarM����S�ĕۑ�***/

void SetXSaikenFlg(int saiken, char* knsgrp, char* kmkcd, XBARM_INF* xinf)
{
    int   iCnt;
	int   module;

#ifdef _DEBUG_
	printf("%sSetXSaikenFlg\n", Now());
#endif

	if( sResultRcd.cInstIdentif[0] == 'C' ) {
		module = (int)(sResultRcd.cInstIdentif[1] - 0x30);
	} else {
		module = (int)(sResultRcd.cInstIdentif[3] - 0x30);
	}

    for (iCnt = 0; iCnt < XBARM_ITEM_NUM; iCnt++) {
        if ((memcmp(xinf[iCnt].knsgrp, knsgrp, 16) == 0) &&
            (memcmp(xinf[iCnt].kmkcd,  kmkcd,   7) == 0) &&
            (xinf[iCnt].iModuleNum == module)) {
            xinf[iCnt].saiken = saiken;
#ifdef _DEBUG_
	printf( "SetXSaikenFlg(%d) : xinf[iCnt].knsgrp = %s\n", __LINE__, xinf[iCnt].knsgrp );
	printf( "SetXSaikenFlg(%d) : xinf[iCnt].kmkcd = %s\n", __LINE__, xinf[iCnt].kmkcd );
	printf( "SetXSaikenFlg(%d) : module = %d\n", __LINE__, module );
	printf( "SetXSaikenFlg(%d) : saiken = %d\n", __LINE__, saiken );
#endif
            return;
        }
    }
}
int GetXSaikenFlg(SOCKET_INF* p, char* knsgrp, char* kmkcd, int* module, XBARM_INF* xinf)
{
    int   iCnt;

#ifdef _DEBUG_
	printf("%sGetXSaikenFlg\n", Now());
	printf( "GetXSaikenFlg(%d) : module            = %d\n", __LINE__, *module );
#endif
    if (knsgrp[0] == '\0')
        return 0;

    for (iCnt = 0; iCnt < XBARM_ITEM_NUM; iCnt++) {
		if (xinf[iCnt].knsgrp[0] == '\0')
			break;

        if ((memcmp(xinf[iCnt].knsgrp, knsgrp, 16) == 0) &&
            (memcmp(xinf[iCnt].kmkcd,  kmkcd,   7) == 0) &&
            (xinf[iCnt].iModuleNum == *module)) {
#ifdef _DEBUG_
			printf( "GetXSaikenFlg(%d) : xinf[iCnt].knsgrp = %s\n", __LINE__, xinf[iCnt].knsgrp );
			printf( "GetXSaikenFlg(%d) : xinf[iCnt].kmkcd  = %s\n", __LINE__, xinf[iCnt].kmkcd );
			printf( "GetXSaikenFlg(%d) : module            = %d\n", __LINE__, *module );
			printf( "GetXSaikenFlg(%d) : xinf[iCnt].saiken = %d\n", __LINE__, xinf[iCnt].saiken );
#endif
            if (xinf[iCnt].saiken == 3) {
                xinf[iCnt].saiken = 0;
                p->pKekka[p->iKekkaCnt].tobiflg02 = '1';
#ifdef _DEBUG_
				printf( "GetXSaikenFlg(%d) : ������ p->pKekka[p->iKekkaCnt].tobiflg02 = %c\n", __LINE__, p->pKekka[p->iKekkaCnt].tobiflg02 );
#endif
            } else {
               /* �P�ɐݒ肳��Ă���ꍇ�͂��̂܂� */
                if (p->pKekka[p->iKekkaCnt].tobiflg02 != '1') {
                    p->pKekka[p->iKekkaCnt].tobiflg02 = '0';
                }
#ifdef _DEBUG_
				printf( "GetXSaikenFlg(%d) : p->pKekka[p->iKekkaCnt].tobiflg02 = %c\n", __LINE__, p->pKekka[p->iKekkaCnt].tobiflg02 );
#endif
			}
        }
    }

    return 0;
}
int OutputXbarmInf(char* gouki, XBARM_INF* xinf)
{
    FILE* fp;
    char  file[256];
    char  aFunc[32];
    int   iCnt;

#ifdef _DEBUG_
	printf("%sOutputXbarmInf\n", Now());
#endif
    memcpy(aFunc,__func__,sizeof(aFunc));

    sprintf(file, "%sxbarinf_%s.dat", aLogOutFolder, gouki);

    if ((fp = fopen(file, "w+")) == NULL) {
        printf("�t�@�C���̃I�[�v���Ɏ��s���܂����B\n");
        sFncSyslog ( TRCKIND_ERROR, aFunc, "�t�@�C���̃I�[�v���Ɏ��s���܂����B" ) ;
        return RTN_NG;
    }

    for (iCnt = 0; iCnt < XBARM_ITEM_NUM; iCnt++) {
        fwrite(&xinf[iCnt], sizeof(XBARM_INF), 1, fp);
    }

    fclose(fp);

    return RTN_OK;
}
int InputXbarmInf(char* gouki, XBARM_INF* xinf)
{
    FILE* fp;
    char  file[256];
    char  aFunc[32];
    int   iCnt;

#ifdef _DEBUG_
	printf("%sInputXbarmInf\n", Now());
#endif
    memcpy(aFunc,__func__,sizeof(aFunc));

    sprintf(file, "%sxbarinf_%s.dat", aLogOutFolder, gouki);

    if ((fp = fopen(file, "r")) == NULL) {
        return RTN_NG;
    }

    for (iCnt = 0; iCnt < XBARM_ITEM_NUM; iCnt++) {
        fread(&xinf[iCnt], sizeof(XBARM_INF), 1, fp);
    }

    fclose(fp);

    return RTN_OK;
}
void DelXbarmInf(char* gouki)
{
    char  file[256];
    char  aFunc[32];

#ifdef _DEBUG_
	printf("%sDelXbarmInf\n", Now());
#endif
    memcpy(aFunc,__func__,sizeof(aFunc));

    sprintf(file, "%sxbarinf_%s.dat", aLogOutFolder, gouki);

    // ���������ŏ����̂ł����ł͉������Ȃ��B���������͎c���Ă���
    // unlink(file);
}
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */

int OutputCtrlSeq(SOCKET_INF* p)
{
	char cWrk[256];
	int iCnt;
	FILE *fp;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));
//	SetLogDat(TRCKIND_TRACE,aFunc,"xxx","xxx","xxx","xxx","xxx");
//	ZbmlPutLog(&sLog);

//	time_t t = time(NULL);
//	time_t t2;
//	struct tm* tm;
//	struct tm* tm2;
//	struct timeval tv;

#ifdef _DEBUG_
	printf("%sOutputCtrlSeq()\n", Now());
#endif
	strcpy( cWrk,aLogOutFolder );
	strcat( cWrk, "ctrlseq_" );
	strcat( cWrk,p->aGouki );
	strcat( cWrk, ".dat" );

/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
/*** Xbarm�Č�����̂��߃t���O��ǉ� ***/
    for (iCnt = 0; iCnt < iXbarmNum; iCnt++) {
        /* �R���g���[�����ς�鎞�A�v�Z�r����Xbarm�͔j������ */
#ifdef _DEBUG_
		printf("�R���g���[�����ς�鎞�A�v�Z�r����Xbarm�͔j������\n");
#endif
        sXbarm_inf[iCnt].saiken   = 0;
/*** X-M�����l�ɕ��ϒl��ݒ肷��:�����l�Ƃ��ĕ��ϒl���ݒ肳��Ă���̂ł��̂܂܎g�p ***/
/*** 0����pltno���N���A����Ă��܂����߁AXMCOUNT�̔{���ɂȂ�悤�������� ***/
        sXbarm_inf[iCnt].iNumCnt -= (sXbarm_inf[iCnt].iNumCnt % sXbarm_inf[iCnt].xmcount);
        sXbarm_inf[iCnt].xbarmsum = 0;
/*** X-M���v�l�����ł͌v�Z������Ȃ��ꍇ������ ***/
		sXbarm_inf[iCnt].xmsub = 0;
    }
    OutputXbarmInf(p->aGouki, sXbarm_inf);
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */

	fp = fopen(cWrk,"w");
	if( fp == NULL ) {
		printf("�t�@�C���̃I�[�v���Ɏ��s���܂����B\n");
		sFncSyslog ( TRCKIND_ERROR, "OutputCtrlSeq()", "�t�@�C���̃I�[�v���Ɏ��s���܂����B" ) ;
		return RTN_NG;
	} else {

		memset( cWrk, 0, sizeof(cWrk) );
		sprintf( cWrk,"%d",p->iCtrlSeq );
		fprintf(fp,"%s,",cWrk);
		memset( cWrk, 0, sizeof(cWrk) );
		sprintf( cWrk,"%d",p->iCtrlSeqCnt );
		fprintf(fp,"%s\n",cWrk);

		fclose(fp);

		return RTN_OK;
	}
}

/**********************************************************************/
/*                                                                    */
/*   function name : SetCtrlInf                                       */
/*                                                                    */
/*   purpose : �R���g���[�����ݒ�                                   */
/*                                                                    */
/*   data : 2006.03.24                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int SetCtrlInf(SOCKET_INF* p,char* nbkmkcd )
{
	int  module;
	int  iCnt;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sSetCtrlInf\n", Now());
#endif

	if( sResultRcd.cInstIdentif[0] == 'C' ) {
		module = (int)(sResultRcd.cInstIdentif[1] - 0x30);
	} else {
		module = (int)(sResultRcd.cInstIdentif[3] - 0x30);
	}

#ifdef _DEBUG_
	printf( "SetCtrlInf(%d) : 1 atoi(p->aGouki) = %d\n", __LINE__, atoi(p->aGouki) );
	printf( "SetCtrlInf(%d) : 1 module          = %d\n", __LINE__, module );
	printf( "SetCtrlInf(%d) : 1 nbkmkcd         = %s\n", __LINE__, nbkmkcd );
#endif
	for( iCnt=0;iCnt<iCtrlNum;iCnt++ ) {
		if( (sCtrl_inf[iCnt].iGoukiNum == atoi(p->aGouki))
				&& (sCtrl_inf[iCnt].iModuleNum == module)
				&& (strncmp(sCtrl_inf[iCnt].nbkmkcd,nbkmkcd,sizeof(sCtrl_inf[iCnt].nbkmkcd)) == 0) ) {
			/* ���ɓo�^�ς݂̏ꍇ�̓f�[�^�X�V */
			sCtrl_inf[iCnt].ctrlno = p->sCtrlkka.ctrlno + 1;

			return RTN_OK;
		}
	}
	/* �V�K���ڂ̏ꍇ�͓o�^ */
	iCnt = iCtrlNum;
	sCtrl_inf[iCnt].iGoukiNum = atoi(p->aGouki);
	sCtrl_inf[iCnt].iModuleNum = module;
	strncpy(sCtrl_inf[iCnt].nbkmkcd,nbkmkcd,strlen(nbkmkcd));
	sCtrl_inf[iCnt].ctrlno = p->sCtrlkka.ctrlno + 1;
	++iCtrlNum;
	return RTN_NG;
}

/**********************************************************************/
/*                                                                    */
/*   function name : GetCtrlInf                                       */
/*                                                                    */
/*   purpose : �R���g���[�����擾                                   */
/*                                                                    */
/*   data : 2007.07.28 Add Haga                                       */
/*                                                                    */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int GetCtrlInf(SOCKET_INF* p,char* nbkmkcd )
{
	int  module;
	int  iCnt;
	char aFunc[32];

#ifdef _DEBUG_
	printf("%sGetCtrlInf\n", Now());
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

	if( sResultRcd.cInstIdentif[0] == 'C' ) {
		module = (int)(sResultRcd.cInstIdentif[1] - 0x30);
	} else {
		module = (int)(sResultRcd.cInstIdentif[3] - 0x30);
	}

	for( iCnt=0;iCnt<iCtrlNum;iCnt++ ) {
		if( sCtrl_inf[iCnt].iGoukiNum == atoi(p->aGouki) && 
            sCtrl_inf[iCnt].iModuleNum == module && 
			strncmp(sCtrl_inf[iCnt].nbkmkcd,nbkmkcd,sizeof(sCtrl_inf[iCnt].nbkmkcd)) == 0 ) {
			/* ���ɓo�^�ς݂̏ꍇ */
			return sCtrl_inf[iCnt].ctrlno;
		}
	}
	/* ���o�^�̏ꍇ�̓t�@�C���̒l��Ԃ� */
	return  p->iCtrlSeqCnt + 1 ;	
}

/**********************************************************************/
/*                                                                    */
/*   function name : SetXbarmInf                                      */
/*                                                                    */
/*   purpose : X-M���ݒ�                                            */
/*                                                                    */
/*   data : 2006.03.20                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int SetXbarmInf(SOCKET_INF* p,int iCnt)
{
	int		cnt;
	int		flg;
	int  module;
	int		knsseq;
	int		bskseq;
	char cWrkCd[8];
	char aFunc[32];
	char cWrkModule[4];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sSetXbarmInf\n", Now());
	printf("SetXbarmInf(%d) : iCnt = %d\n", __LINE__, iCnt);
#endif

	memset(cWrkCd,0,sizeof(cWrkCd));
	memset(cWrkModule,0,sizeof(cWrkModule));

	/* ���W���[���ݒ� */
	if( sResultRcd.cInstIdentif[0] == 'C' ) {
		/* "Cxy"�`�� �� "x0y"�`���ɕύX */
		/*   ��F"C12" �� 102�ɕύX     */
		cWrkModule[0] = sResultRcd.cInstIdentif[1];
		cWrkModule[1] = '0';
		cWrkModule[2] = sResultRcd.cInstIdentif[2];
		module = atoi(cWrkModule);
	} else {
		module = (int)(sResultRcd.cInstIdentif[3] - 0x30);
	}
#ifdef _DEBUG_
	printf("SetXbarmInf(%d) : ���W���[��No = [%d]\n", __LINE__, module);
#endif

	/* ���ڃR�[�h�̎擾 */
	if( iCnt >= 0 ) {
		flg = 1;
		/* �I�[�_�[�t�@�C������擾 */
		strncpy(cWrkCd,pKenorder[iCnt].kmkcd,7);
		knsseq = pKenorder[iCnt].knsseq;
	} else {
		/* �e�[�u������擾 */
		memset( cWrkCd,0,sizeof(cWrkCd) );
		strncpy( cWrkCd,"       ",7 );
		strncpy( cWrkCd,sResultRcd.cAppCode,strlen(sResultRcd.cAppCode) );
		flg = 0;
		for( cnt=0;cnt<iKinkyuNum;cnt++ ) {
			if( strncmp(cWrkCd,pKinkyu[cnt].nbkmkcd,7) == 0 ) {
				memset( cWrkCd,0,sizeof(cWrkCd) );
				strncpy( cWrkCd,pKinkyu[cnt].kmkcd,7 );
				flg = 1;
				break;
			}
		}
		knsseq = 0;
	}
	bskseq = atoi(sTestOrderRcd.cSampleNo);

	if( flg == 1 ) {
		for( iXbarmCnt=0;iXbarmCnt<iXbarmNum;iXbarmCnt++ ) {	/* xbarinf_XX.dat�ɏo�͂������������[�v */
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
/*** �ً}STAT�Ή� �ً}�̏ꍇ�AiCnt���ݒ肳��Ȃ��i�˗����Ȃ��j***/
            if(((iCnt >= 0 && (strncmp(sXbarm_inf[iXbarmCnt].knsgrp, pKenorder[iCnt].knsgrp, 16) == 0)) ||
			    (iCnt <  0 && (strncmp(sXbarm_inf[iXbarmCnt].knsgrp, pKinkyu[cnt].knsgrp,    16) == 0)))
                    && (strncmp(sXbarm_inf[iXbarmCnt].kmkcd,cWrkCd,7) == 0)
					&& (sXbarm_inf[iXbarmCnt].iModuleNum == module) ){
													/* �I�[�_�[����XBAR_INF��KNSGRP����v���Ċ��� */
													/* KMKCD����v�B����Ƀ��W���[������v��������  */
													/* �ȍ~�̏�����XBAR_INF�̍�肱�݂����s         */
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */

				/* ���ɓo�^�ς݂̏ꍇ�̓f�[�^�X�V */
				++sXbarm_inf[iXbarmCnt].iNumCnt;

				if( sXbarm_inf[iXbarmCnt].xmchk == 0 ) {
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
					sXbarm_inf[0].iXbarmCnt = iXbarmCnt; /* �������ɕK�v�Ȃ����Ȃ̂ŁA0�Ԃ����Ɋi�[ */
					sXbarm_inf[0].iXbarmNum = iXbarmNum; /* �������ɕK�v�Ȃ����Ȃ̂ŁA0�Ԃ����Ɋi�[ */
					OutputXbarmInf(p->aGouki, sXbarm_inf);
#ifdef _DEBUG_
					printf("********** EXIT 1(count : %d)\n", iXbarmCnt);
					printf("iNumCnt        %d\n", sXbarm_inf[iXbarmCnt].iNumCnt);
					printf("saiken         %d\n", sXbarm_inf[iXbarmCnt].saiken);
#endif
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */
					return RTN_NG;
				}
				/* X-M���v�l�̎Z�o */
				sXbarm_inf[iXbarmCnt].xbarmsum += CalcXbarm(atof(sResultRcd.cDat_MeasrmntVal),X_M_SUM);
				
				/* ���̃v���b�gNO�̍Ō�̃v���b�gSEQ (KMKMST��XMCOUNT = 10 ���Ƃ��āA�v���b�gSEQ = 10 �̏ꍇ) */
				if(	(((sXbarm_inf[iXbarmCnt].iNumCnt - 1) % sXbarm_inf[iXbarmCnt].xmcount) + 1) == sXbarm_inf[iXbarmCnt].xmcount ) {
					/* X-M���ʒl�̎Z�o */
					sXbarm_inf[iXbarmCnt].xbarmkka = CalcXbarm(sXbarm_inf[iXbarmCnt].xbarmsum,X_M_AVE);
#ifdef _DEBUG_
					printf("SetXbarmInf(%d) cWrkCd                            = %s\n",    __LINE__, cWrkCd);
					printf("SetXbarmInf(%d) sXbarm_inf[iXbarmCnt].iNumCnt     = %d\n",   __LINE__, sXbarm_inf[iXbarmCnt].iNumCnt);
					printf("SetXbarmInf(%d) sXbarm_inf[iXbarmCnt].xbarmsum    = %.12f\n", __LINE__, sXbarm_inf[iXbarmCnt].xbarmsum);
					printf("SetXbarmInf(%d) sXbarm_inf[iXbarmCnt].xbarmkka    = %.12f\n", __LINE__, sXbarm_inf[iXbarmCnt].xbarmkka);
					printf("SetXbarmInf(%d) sXbarm_inf[iXbarmCnt].xmsub       = %.12f\n", __LINE__, sXbarm_inf[iXbarmCnt].xmsub);
					printf("SetXbarmInf(%d) atof(sResultRcd.cDat_MeasrmntVal) = %.12f\n", __LINE__, atof(sResultRcd.cDat_MeasrmntVal));
#endif
					sXbarm_inf[iXbarmCnt].xbarmsum = 0;
					sXbarm_inf[iXbarmCnt].knsseqed = knsseq;
					sXbarm_inf[iXbarmCnt].bskseqed = bskseq;
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
					sXbarm_inf[0].iXbarmCnt = iXbarmCnt; /* �������ɕK�v�Ȃ����Ȃ̂ŁA0�Ԃ����Ɋi�[ */
					sXbarm_inf[0].iXbarmNum = iXbarmNum; /* �������ɕK�v�Ȃ����Ȃ̂ŁA0�Ԃ����Ɋi�[ */
					OutputXbarmInf(p->aGouki, sXbarm_inf);

					/* Xbarm�Č�����̂��߃t���O��ǉ� */
					/* Xbarm���ς������Č��Ȃ� */
					sXbarm_inf[iXbarmCnt].saiken = 0;

					/*** Xbarm�����W�`�F�b�N ***/
					int i;
					for (i = 0; i < iXbarmmstNum; i++) {
						if (memcmp(sXbarm_inf[iXbarmCnt].knsgrp, pXbarmmst[i].knsgrp, 16) == 0 &&
							memcmp(cWrkCd, pXbarmmst[i].kmkcd, 7) == 0) {
							double minval = atof(pXbarmmst[i].minval);
							double maxval = atof(pXbarmmst[i].maxval);
							if (minval >= sXbarm_inf[iXbarmCnt].xbarmkka ||
								maxval <= sXbarm_inf[iXbarmCnt].xbarmkka){
								sXbarm_inf[iXbarmCnt].saiken = 1;
#ifdef _DEBUG_
								printf("\n################################## Xbarm�Č����� ##################################\n");
								printf("!!!!!!! minval [%f] <= xbarmkka�y%f�z<= maxval [%f] !!!!!!!\n\n", 
									   minval, sXbarm_inf[iXbarmCnt].xbarmkka, maxval);
#endif
							}
#ifdef _DEBUG_
							else {
								printf("SetXbarmInf(%d) Xbarm�����W�`�F�b�N OK!\n", __LINE__);
								printf("minval [%f] <= xbarmkka�y%f�z<= maxval [%f]\n", 
									   minval, sXbarm_inf[iXbarmCnt].xbarmkka, maxval);
							}
#endif
							break;
						}
					}
#ifdef _DEBUG_
					printf("********** EXIT 2(count : %d)\n", iXbarmCnt);
					printf("iNumCnt        %d\n", sXbarm_inf[iXbarmCnt].iNumCnt);
					printf("saiken         %d\n", sXbarm_inf[iXbarmCnt].saiken);
#endif
					return RTN_OK;
				}
				/* ���̃v���b�gNO�̍ŏ��̃v���b�gSEQ (�v���b�gSEQ = 1 �̏ꍇ) */
				else if( (((sXbarm_inf[iXbarmCnt].iNumCnt - 1) % sXbarm_inf[iXbarmCnt].xmcount) + 1) == 1 ) {
					sXbarm_inf[iXbarmCnt].knsseqst = knsseq;
					sXbarm_inf[iXbarmCnt].bskseqst = bskseq;
				}
                sXbarm_inf[0].iXbarmCnt = iXbarmCnt; /* �������ɕK�v�Ȃ����Ȃ̂ŁA0�Ԃ����Ɋi�[ */
                sXbarm_inf[0].iXbarmNum = iXbarmNum; /* �������ɕK�v�Ȃ����Ȃ̂ŁA0�Ԃ����Ɋi�[ */
                OutputXbarmInf(p->aGouki, sXbarm_inf);
#ifdef _DEBUG_
				printf("********** EXIT 3(count : %d)\n", iXbarmCnt);
				printf("iNumCnt        %d\n", sXbarm_inf[iXbarmCnt].iNumCnt);
				printf("saiken         %d\n\n", sXbarm_inf[iXbarmCnt].saiken);

				printf("SetXbarmInf(%d) cWrkCd                            = %s\n",    __LINE__, cWrkCd);
				printf("SetXbarmInf(%d) sXbarm_inf[iXbarmCnt].iNumCnt     = %d\n",    __LINE__, sXbarm_inf[iXbarmCnt].iNumCnt);
				printf("SetXbarmInf(%d) sXbarm_inf[iXbarmCnt].xbarmsum    = %.12f\n", __LINE__, sXbarm_inf[iXbarmCnt].xbarmsum);
				printf("SetXbarmInf(%d) sXbarm_inf[iXbarmCnt].xbarmkka    = %.12f\n", __LINE__, sXbarm_inf[iXbarmCnt].xbarmkka);
				printf("SetXbarmInf(%d) sXbarm_inf[iXbarmCnt].xmsub       = %.12f\n", __LINE__, sXbarm_inf[iXbarmCnt].xmsub);
				printf("SetXbarmInf(%d) atof(sResultRcd.cDat_MeasrmntVal) = %.12f\n", __LINE__, atof(sResultRcd.cDat_MeasrmntVal));
#endif
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */
				return RTN_NG;
			}
		}

		/* �V�K���ڂ̏ꍇ�͓o�^ */
		sXbarm_inf[iXbarmCnt].xmchk = 1;	/* 060420 */
		iXbarmCnt = iXbarmNum;
		sXbarm_inf[iXbarmCnt].iGoukiNum = atoi(p->aGouki);
		sXbarm_inf[iXbarmCnt].iModuleNum = module;
		strncpy(sXbarm_inf[iXbarmCnt].kmkcd,cWrkCd,7);
		sXbarm_inf[iXbarmCnt].iNumCnt = 1;
		sXbarm_inf[iXbarmCnt].knsseqst = knsseq;
		sXbarm_inf[iXbarmCnt].bskseqst = bskseq;
		if( iCnt >= 0 ) {
			GetXmcount( pKenorder[iCnt].kmkcd,pKenorder[iCnt].knsgrp,&sXbarm_inf[iXbarmCnt].xmcount );
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
/*** Xbarm�̌v�Z�P�ʂ�ύX Xbarm�Ɍ����O���[�v��ǉ� ***/
			strncpy(sXbarm_inf[iXbarmCnt].knsgrp, pKenorder[iCnt].knsgrp, 16);
/*** X-M�����l�ɕ��ϒl��ݒ肷�� ***/
			sXbarm_inf[iXbarmCnt].xbarmkka = GetXMavg(pKenorder[iCnt].knsgrp, pKenorder[iCnt].kmkcd);
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */
		} else {
			GetXmcount( pKinkyu[cnt].kmkcd,pKinkyu[cnt].knsgrp,&sXbarm_inf[iXbarmCnt].xmcount );
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
/*** Xbarm�̌v�Z�P�ʂ�ύX Xbarm�Ɍ����O���[�v��ǉ� ***/
			strncpy(sXbarm_inf[iXbarmCnt].knsgrp, pKinkyu[cnt].knsgrp, 16);
/*** X-M�����l�ɕ��ϒl��ݒ肷�� ***/
			sXbarm_inf[iXbarmCnt].xbarmkka = GetXMavg(pKinkyu[cnt].knsgrp, pKinkyu[cnt].kmkcd);
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */
		}
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
		sXbarm_inf[iXbarmCnt].xbarmsum = CalcXbarm(atof(sResultRcd.cDat_MeasrmntVal),X_M_SUM);
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */
		if( sXbarm_inf[iXbarmCnt].xmcount <= 0 ) {
			sXbarm_inf[iXbarmCnt].xmcount = PLT_UNIT_DEF;
			sXbarm_inf[iXbarmCnt].xmchk = 0;	/* 060420 */
		}
		++iXbarmNum;

#ifdef _DEBUG_
		printf("SetXbarmInf(%d) ********** sXbarm_inf�ɐV�K���ڂ̓o�^\n", __LINE__);
		printf("SetXbarmInf(%d) sXbarm_inf[iXbarmCnt].xmchk      = %d\n",    __LINE__, sXbarm_inf[iXbarmCnt].xmchk);
		printf("SetXbarmInf(%d) iXbarmCnt                        = %d\n",    __LINE__, iXbarmCnt);
		printf("SetXbarmInf(%d) iXbarmNum                        = %d\n",    __LINE__, iXbarmNum);
		printf("SetXbarmInf(%d) sXbarm_inf[iXbarmCnt].iGoukiNum  = %d\n",    __LINE__, sXbarm_inf[iXbarmCnt].iGoukiNum);
		printf("SetXbarmInf(%d) sXbarm_inf[iXbarmCnt].iModuleNum = %d\n",    __LINE__, sXbarm_inf[iXbarmCnt].iModuleNum);
		printf("SetXbarmInf(%d) sXbarm_inf[iXbarmCnt].knsgrp     = %s\n",    __LINE__, sXbarm_inf[iXbarmCnt].knsgrp);
		printf("SetXbarmInf(%d) sXbarm_inf[iXbarmCnt].kmkcd      = %s\n",    __LINE__, sXbarm_inf[iXbarmCnt].kmkcd);
		printf("SetXbarmInf(%d) sXbarm_inf[iXbarmCnt].knsseqst   = %d\n",    __LINE__, sXbarm_inf[iXbarmCnt].knsseqst);
		printf("SetXbarmInf(%d) sXbarm_inf[iXbarmCnt].bskseqst   = %d\n",    __LINE__, sXbarm_inf[iXbarmCnt].bskseqst);
		printf("SetXbarmInf(%d) sXbarm_inf[iXbarmCnt].xbarmkka   = %.12f\n", __LINE__, sXbarm_inf[iXbarmCnt].xbarmkka);
		printf("SetXbarmInf(%d) sXbarm_inf[iXbarmCnt].xbarmsum   = %.12f\n", __LINE__, sXbarm_inf[iXbarmCnt].xbarmsum);
#endif
	}
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
    sXbarm_inf[0].iXbarmCnt = iXbarmCnt; /* �������ɕK�v�Ȃ����Ȃ̂ŁA0�Ԃ����Ɋi�[ */
    sXbarm_inf[0].iXbarmNum = iXbarmNum; /* �������ɕK�v�Ȃ����Ȃ̂ŁA0�Ԃ����Ɋi�[ */
    OutputXbarmInf(p->aGouki, sXbarm_inf);
#ifdef _DEBUG_
	printf("********** EXIT 4(count : %d)\n", iXbarmCnt);
	printf("iNumCnt        %d\n", sXbarm_inf[iXbarmCnt].iNumCnt);
	printf("saiken         %d\n\n", sXbarm_inf[iXbarmCnt].saiken);

	printf("SetXbarmInf(%d) cWrkCd                            = %s\n",    __LINE__, cWrkCd);
	printf("SetXbarmInf(%d) sXbarm_inf[iXbarmCnt].iNumCnt     = %d\n",    __LINE__, sXbarm_inf[iXbarmCnt].iNumCnt);
	printf("SetXbarmInf(%d) sXbarm_inf[iXbarmCnt].xbarmsum    = %.12f\n", __LINE__, sXbarm_inf[iXbarmCnt].xbarmsum);
	printf("SetXbarmInf(%d) sXbarm_inf[iXbarmCnt].xbarmkka    = %.12f\n", __LINE__, sXbarm_inf[iXbarmCnt].xbarmkka);
	printf("SetXbarmInf(%d) sXbarm_inf[iXbarmCnt].xmsub       = %.12f\n", __LINE__, sXbarm_inf[iXbarmCnt].xmsub);
	printf("SetXbarmInf(%d) atof(sResultRcd.cDat_MeasrmntVal) = %.12f\n", __LINE__, atof(sResultRcd.cDat_MeasrmntVal));
#endif
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */
	return RTN_NG;
}
/**********************************************************************/
/*                                                                    */
/*   function name : CalcXbarm                                        */
/*                                                                    */
/*   purpose : X-M���v�l�Z�o                                          */
/*                                                                    */
/*   data : 2006.03.20                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
double CalcXbarm(double data,int cal)
{
	double  x;
	double  x2;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sCalcXbarm\n", Now());
#endif

	if( cal == X_M_SUM ) {
		if( (data - sXbarm_inf[iXbarmCnt].xbarmkka) == 0 ) {
			x = 0;
		} else {
			x = ((data - sXbarm_inf[iXbarmCnt].xbarmkka)/fabs(data - sXbarm_inf[iXbarmCnt].xbarmkka)) * sqrt(fabs(data - sXbarm_inf[iXbarmCnt].xbarmkka));
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
/*** X-M���v�l�����ł͌v�Z������Ȃ��ꍇ������ ***/
			sXbarm_inf[iXbarmCnt].xmsub += data - sXbarm_inf[iXbarmCnt].xbarmkka;
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <--> */
		}
	} else {
		if( data == 0 ) {
			x = sXbarm_inf[iXbarmCnt].xbarmkka;
		} else {
			x2 = data / (double)sXbarm_inf[iXbarmCnt].xmcount;
			x2 = x2*x2;
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
/*** X-M���v�l�����ł͌v�Z������Ȃ��ꍇ������ ***/
			double x3 = sXbarm_inf[iXbarmCnt].xmsub / (double)sXbarm_inf[iXbarmCnt].xmcount;
			sXbarm_inf[iXbarmCnt].xmsub = 0;
			x = sXbarm_inf[iXbarmCnt].xbarmkka + (x3/fabs(x3) * x2);
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */
		}
	}
	return x;
}
/**********************************************************************/
/*                                                                    */
/*   function name : SetXbarmData                                     */
/*                                                                    */
/*   purpose : X-M���ݒ�                                            */
/*                                                                    */
/*   data : 2006.03.20                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
void SetXbarmData(SOCKET_INF* p)
{
	char cWrkCd[32];
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sSetXbarmData\n", Now());
#endif

	memset(&(p->sXbarm),0,sizeof(Xbarm));

	/* No. 1 �����J�n�� */
/* [ start 072/073 060417 */
	memset( cWrkCd,0,sizeof(cWrkCd) );
	CnvtFromKjnsriymd( sSysknrmst.kjnsriymd,cWrkCd );
	strncpy( p->sXbarm.knskisymd,cWrkCd,strlen(cWrkCd) );
/* ] end 072/073 060417 */
	/* No.2 ���͋@�敪�ݒ� */
	strcpy( p->sXbarm.bskkbn,aMekbn );
	/* No.3 ���͋@���C���ݒ� */
	strncpy( p->sXbarm.bsklne,p->aGouki,2 );
	/* No.4 ���u���ʔԍ�->���͋@���@ */
	strncpy( p->sXbarm.bskgok,p->aGouki,2 );
	// ADD START Haga 2006-08-02
	sBskgokConv ( sResultRcd.cInstIdentif, p->sXbarm.bskgok ) ;
	/* No. 5 �����O���[�v�ݒ� */
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
	strncpy( p->sXbarm.knsgrp, sXbarm_inf[iXbarmCnt].knsgrp, 16 );
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */
	/* No. 6 ���ڃR�[�h�ݒ� */
	strncpy( p->sXbarm.kmkcd, sXbarm_inf[iXbarmCnt].kmkcd, 7 );
	/* No. 5 �����O���[�v�ݒ� */
	/* No.7 �������ڃR�[�h�ݒ� */
	strncpy( p->sXbarm.nbkmkcd,sResultRcd.cAppCode,strlen(sResultRcd.cAppCode) );
	/* No.8 �v���b�gNo */
	p->sXbarm.pltno = ((sXbarm_inf[iXbarmCnt].iNumCnt - 1) / sXbarm_inf[iXbarmCnt].xmcount) + 1;
#ifdef _DEBUG_
	printf( "SetXbarmData(%d) : p->sXbarm.pltno = %d\n", __LINE__, p->sXbarm.pltno );
#endif
	/* No.9 ����SEQ-START */
	p->sXbarm.knsseqst = sXbarm_inf[iXbarmCnt].knsseqst;
	/* No.10 ����SEQ-END */
	p->sXbarm.knsseqed = sXbarm_inf[iXbarmCnt].knsseqed;
	/* No.11 ���͋@SEQ-START */
	p->sXbarm.bskseqst = sXbarm_inf[iXbarmCnt].bskseqst;
	/* No.12 ���͋@SEQ-END */
	p->sXbarm.bskseqed = sXbarm_inf[iXbarmCnt].bskseqed;
	/* No.13 �v���b�gSEQ-START */
	/* No.14 �v���b�gSEQ-END */
	/* No.15 �v���b�g�� */
	p->sXbarm.pltsu = (short)(sXbarm_inf[iXbarmCnt].xmcount);
	/* No.16 X-M���� */
	sprintf( p->sXbarm.xbarmkka,"%f",sXbarm_inf[iXbarmCnt].xbarmkka );
}

/**********************************************************************/
/*                                                                    */
/*   function name : DecodeMsgHeaderRcd                               */
/*                                                                    */
/*   purpose : ���o�����R�[�h�f�R�[�h����                             */
/*                                                                    */
/*   data : 2005.12.13                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int DecodeMsgHeaderRcd(SOCKET_INF* p, char* aRcvMsg)
{
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sDecodeMsgHeaderRcd\n", Now());
#endif

	iRcvMsgCnt = 0;
	memset(&sMsgHeaderRcd,0,sizeof(sMsgHeaderRcd));

	/*------------------------------*/
	/* No.1 Record Type ID �`�F�b�N */
	/*------------------------------*/
	++iRcvMsgCnt;
	/*---------------------*/
	/* No.2 ��؂蕶���ݒ� */
	/*---------------------*/
	SetDivChar(aRcvMsg);
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*---------------------------------*/
	/* No.5 Sender Name or ID �`�F�b�N */
	/*---------------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*----------------------------*/
	/* No.10 Receiver ID �`�F�b�N */
	/*----------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*------------------------------------------------*/
	/* No.11 Comment or Special Instructions �`�F�b�N */
	/*------------------------------------------------*/
	if( ChkCmnt_SpclInst(p,aRcvMsg) == MESSAGE_ERR ) {
		return MESSAGE_ERR;
	}
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*------------------------------*/
	/* No.12 Processing ID �`�F�b�N */
	/*------------------------------*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*----------------------------*/
	/* No.13 Version No. �`�F�b�N */
	/*----------------------------*/
	/*----------------*/
	/* No.14 �`�F�b�N */
	/*------- --------*/
	/*----------------*/
	/* CR �`�F�b�N */
	/*------- --------*/
	return MESSAGE_OK;

}
/**********************************************************************/
/*                                                                    */
/*   function name : SetDivChar                                       */
/*                                                                    */
/*   purpose : ��؂蕶���ݒ菈��                                     */
/*                                                                    */
/*   data : 2005.12.13                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
void SetDivChar(char* aRcvMsg)
{
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sSetDivChar()\n", Now());
#endif

	cFieldDivChar = aRcvMsg[iRcvMsgCnt];			/* �t�B�[���h��؂蕶�� */
	cRepeatDivChar = aRcvMsg[++iRcvMsgCnt];			/* �J��Ԃ���؂蕶�� */
	cCmpDivChar = aRcvMsg[++iRcvMsgCnt];			/* �R���|�l���g��؂蕶�� */
	cEscChar = aRcvMsg[++iRcvMsgCnt];				/* �G�X�P�[�v���� */
	++iRcvMsgCnt;
}
/**********************************************************************/
/*                                                                    */
/*   function name : ChkFieldDiv                                      */
/*                                                                    */
/*   purpose : �t�B�[���h��؂�`�F�b�N����                           */
/*                                                                    */
/*   data : 2005.12.12                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int ChkFieldDiv(char* aRcvMsg)
{
	int	iLen;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("ChkFieldDiv()\n");
#endif

	iLen = strlen( aRcvMsg );
	for( ; iRcvMsgCnt<iLen; iRcvMsgCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cFieldDivChar ) {
			++iRcvMsgCnt;
			return MESSAGE_NO_ERR;
		}
	}
	return MESSAGE_OK;
}
/**********************************************************************/
/*                                                                    */
/*   function name : ChkFieldDiv2                                     */
/*                                                                    */
/*   purpose : �t�B�[���h��؂�`�F�b�N����2                          */
/*                                                                    */
/*   data : 2005.12.14                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int ChkFieldDiv2(char* aRcvMsg)
{
	int	iLen;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("ChkFieldDiv2()\n");
#endif

	iLen = strlen( aRcvMsg );
	for( ; iRcvMsgCnt<iLen; iRcvMsgCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cFieldDivChar ) {
			iRcvMsgCnt++;
			return MESSAGE_NO_ERR;
		} else if( aRcvMsg[iRcvMsgCnt] == CR ) {
			return MESSAGE_OK;
		}
	}
	return MESSAGE_OK;
}
/**********************************************************************/
/*                                                                    */
/*   function name : ChkCmnt_SpclInst                                 */
/*                                                                    */
/*   purpose : Comment or Special Instructions �`�F�b�N����           */
/*                                                                    */
/*   data : 2005.12.13                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int ChkCmnt_SpclInst(SOCKET_INF* p,char* aRcvMsg)
{
	int iCnt;
//	int iWrk;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sChkCmnt_SpclInst()\n", Now());
#endif

	/* �t�B�[���h���̃`�F�b�N */
//	iWrk = iRcvMsgCnt;

	p->iRcvMsg = MSG_NON;

	/* �R���|�l���g(���b�Z�[�W�̈Ӗ�)���̃`�F�b�N */
	for( iCnt=0; iCnt<(5+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
			break;
		}
		sMsgHeaderRcd.cMessageMean[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( iCnt != 5 ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}

	if( strncmp(sMsgHeaderRcd.cMessageMean,"TSREQ",5) == 0 ) {
		p->iRcvMsg = MSG_ORDER;
	} else if( strncmp(sMsgHeaderRcd.cMessageMean,"RSUPL",5) == 0 ) {
		p->iRcvMsg = MSG_RESULT;
	} else if( strncmp(sMsgHeaderRcd.cMessageMean,"PCUPL",5) == 0 ) {
	} else if( strncmp(sMsgHeaderRcd.cMessageMean,"ICUPL",5) == 0 ) {
	} else if( strncmp(sMsgHeaderRcd.cMessageMean,"ABUPL",5) == 0 ) {
	} else {
		p->iRcvMsg = MSG_NON;
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	/* �R���|�l���g(�����v��)���̃`�F�b�N */
	for( iCnt=0; iCnt<(5+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cFieldDivChar ) {
			break;
		}
		sMsgHeaderRcd.cGenerateFactor[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( (iCnt < 4) || (iCnt > 5) ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}
	return MESSAGE_NO_ERR;
}
/**********************************************************************/
/*                                                                    */
/*   function name : DecodePatientInfRcd                              */
/*                                                                    */
/*   purpose : ���ҏ�񃌃R�[�h�f�R�[�h����                           */
/*                                                                    */
/*   data : 2005.12.14                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int DecodePatientInfRcd(SOCKET_INF* p,char* aRcvMsg)
{
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sDecodePatientInfRcd()\n", Now());
#endif

	iRcvMsgCnt = 0;
	memset(&sPatientInfRcd,0,sizeof(sPatientInfRcd));
	/*------------------------------*/
	/* No.1 Record Type ID �`�F�b�N */
	/*------------------------------*/
	++iRcvMsgCnt;
	/*-------------------------------*/
	/* No.2 Sequence Number �`�F�b�N */
	/*-------------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	if( ChkSeqNum( sPatientInfRcd.cSeqNum,aRcvMsg ) == MESSAGE_ERR ) {
		return MESSAGE_ERR;
	}
	p->sSndorder.seqnum = atoi( sPatientInfRcd.cSeqNum );

	return MESSAGE_OK;

}
/**********************************************************************/
/*                                                                    */
/*   function name : ChkSeqNum                                        */
/*                                                                    */
/*   purpose : Sequence Number�`�F�b�N����                            */
/*                                                                    */
/*   data : 2005.12.14                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int ChkSeqNum(char* aSeqNum,char* aRcvMsg)
{
	int iCnt;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sChkSeqNum()\n", Now());
#endif

	/* �t�B�[���h���̃`�F�b�N */
	for( iCnt=0; iCnt<(6+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cFieldDivChar ) {
			break;
		}
		aSeqNum[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( (iCnt < 1) || (iCnt > 6) ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}
	return MESSAGE_NO_ERR;
}
/**********************************************************************/
/*                                                                    */
/*   function name : DecodeReqInfRcd                                  */
/*                                                                    */
/*   purpose : �₢���킹���R�[�h�f�R�[�h����                         */
/*                                                                    */
/*   data : 2005.12.22                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int DecodeReqInfRcd(SOCKET_INF* p,char* aRcvMsg)
{
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sDecodeReqInfRcd\n", Now());
#endif

	iRcvMsgCnt = 0;
	memset(&sReqInfRcd,0,sizeof(sReqInfRcd));
	/*------------------------------*/
	/* No.1 Record Type ID �`�F�b�N */
	/*------------------------------*/
	++iRcvMsgCnt;

	ClrSaikenInf(p);
	memset(&(p->sCtrlkka),0,sizeof(p->sCtrlkka));
	p->iOrderNum = 0;
	memset(&(p->sSndorder),0,sizeof(p->sSndorder));
	/*-------------------------------*/
	/* No.2 Sequence Number �`�F�b�N */
	/*-------------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	if( ChkSeqNum( sReqInfRcd.cSeqNum,aRcvMsg ) == MESSAGE_ERR ) {
		return MESSAGE_ERR;
	}
	p->sSndorder.seqnum = atoi( sReqInfRcd.cSeqNum );
	/*----------------------------------------*/
	/* No.3 Starting Range ID Number �`�F�b�N */
	/*----------------------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	if( ChkStartRangeIdNum(p,aRcvMsg) == MESSAGE_ERR ) {
		return MESSAGE_ERR;
	}
	/*---------------*/
	/* No.4 �`�F�b�N */
	/*---------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*---------------------------------*/
	/* No.5 Universal Test ID �`�F�b�N */
	/*---------------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*---------------*/
	/* No.6 �`�F�b�N */
	/*---------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*---------------*/
	/* No.7 �`�F�b�N */
	/*---------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*---------------*/
	/* No.8 �`�F�b�N */
	/*---------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*---------------------------*/
	/* No.9 �`�F�b�N */
	/*---------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*----------------*/
	/* No.10 �`�F�b�N */
	/*----------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*----------------*/
	/* No.11 �`�F�b�N */
	/*----------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*----------------*/
	/* No.12 �`�F�b�N */
	/*----------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*-------------------------------------------------*/
	/* No.13 Request Information Status Codes �`�F�b�N */
	/*-------------------------------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	if( aRcvMsg[iRcvMsgCnt] == 'A' ) {
		/* ���͋@����"�v��������"��M */
		p->iRcvMsg = MSG_NON;
	}

	/*-------------*/
	/* CR �`�F�b�N */
	/*------- -----*/
	return MESSAGE_OK;
}
/**********************************************************************/
/*                                                                    */
/*   function name : ChkStartRangeIdNum                               */
/*                                                                    */
/*   purpose : Stating Range ID Number �`�F�b�N����                   */
/*                                                                    */
/*   data : 2005.12.22                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int ChkStartRangeIdNum(SOCKET_INF* p,char* aRcvMsg)
{
	int iCnt;
//	int iWrk;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sChkStartRangeIdNum()\n", Now());
#endif

	/* �t�B�[���h���̃`�F�b�N */
//	iWrk = iRcvMsgCnt;
	if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
		return MESSAGE_NO_ERR;

	}
	++iRcvMsgCnt;
	/* �R���|�l���g(Sample ID)���̃`�F�b�N */
	for( iCnt=0; iCnt<(22+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
			break;
		}
		sReqInfRcd.cSampleId[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( iCnt != 22 ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;

	}
	++iRcvMsgCnt;
	/* �R���|�l���g(Sample No)���̃`�F�b�N */
	for( iCnt=0; iCnt<(5+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
			break;
		}
		sReqInfRcd.cSampleNo[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( (iCnt < 1) || (iCnt > 5) ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}
	p->sSndorder.bskseq = atoi( sReqInfRcd.cSampleNo );
	++iRcvMsgCnt;

	memset( p->cRackNum,0,sizeof(p->cRackNum) );
	memset( p->cRackPosNum,0,sizeof(p->cRackPosNum) );
	/* �R���|�l���g(Rack ID)���̃`�F�b�N */
	for( iCnt=0; iCnt<(5+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
			break;
		}
		sReqInfRcd.cRackId[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( (iCnt < 1) || (iCnt > 5) ) {	/* ���������ُ� */
		return MESSAGE_ERR;
	}
	memcpy( p->cRackNum,sReqInfRcd.cRackId,5 );
	++iRcvMsgCnt;
	/* �R���|�l���g(Position No)���̃`�F�b�N */
	for( iCnt=0; iCnt<(1+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
			break;
		}
		sReqInfRcd.cPositionNo[0] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( iCnt != 1 ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}
	p->cRackPosNum[0] = sReqInfRcd.cPositionNo[0];
	if( atoi(p->cRackPosNum) == 0 ) {
		return MESSAGE_ERR;
	}
	++iRcvMsgCnt;
	if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	/* �R���|�l���g(Rack Type)���̃`�F�b�N */
	for( iCnt=0; iCnt<(2+1); iCnt++ ) {
		if( (aRcvMsg[iRcvMsgCnt] == cCmpDivChar) || (aRcvMsg[iRcvMsgCnt] == cFieldDivChar) ) {
			break;
		}
		sReqInfRcd.cRackType[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( (iCnt < 1) || (iCnt > 2) ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}
	strncpy( p->sSndorder.racktype,sReqInfRcd.cRackType,2 );

	++iRcvMsgCnt;
	if( aRcvMsg[iRcvMsgCnt] == cFieldDivChar ) {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	/* �R���|�l���g(Container Type)���̃`�F�b�N */
	for( iCnt=0; iCnt<(2+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cFieldDivChar ) {
			break;
		}
		sReqInfRcd.cContainerType[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( (iCnt == 0) || (iCnt == 2) ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}
	return MESSAGE_NO_ERR;
}
/**********************************************************************/
/*                                                                    */
/*   function name : DecodeTestOrderRcd                               */
/*                                                                    */
/*   purpose : ���ڑI�����R�[�h�f�R�[�h����                           */
/*                                                                    */
/*   data : 2005.12.22                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int DecodeTestOrderRcd(SOCKET_INF* p,char* aRcvMsg)
{
	int iWrk;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sDecodeTestOrderRcd\n", Now());
#endif

	memset(&(p->sCtrlkka),0,sizeof(p->sCtrlkka));
	ClrSaikenInf(p);

	iRcvMsgCnt = 0;
	memset(&sTestOrderRcd,0,sizeof(sTestOrderRcd));
	/*------------------------------*/
	/* No.1 Record Type ID �`�F�b�N */
	/*------------------------------*/
	++iRcvMsgCnt;
	/*-------------------------------*/
	/* No.2 Sequence Number �`�F�b�N */
	/*-------------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	if( ChkSeqNum( sTestOrderRcd.cSeqNum,aRcvMsg ) == MESSAGE_ERR ) {
		return MESSAGE_ERR;
	}
	/*---------------------------*/
	/* No.3 Specimen ID �`�F�b�N */
	/*---------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*--------------------------------------*/
	/* No.4 Instrument Specimen ID �`�F�b�N */
	/*--------------------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	if( ChkInstSpmenId(p,aRcvMsg) == MESSAGE_ERR ) {
		return MESSAGE_ERR;
	}
	/*---------------------------------*/
	/* No.5 Universal Test ID �`�F�b�N */
	/*---------------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	if( ChkUniTestId_O(p,aRcvMsg) == MESSAGE_ERR ) {
		return MESSAGE_ERR;
	}
	/*------------------------*/
	/* No.6 Priority �`�F�b�N */
	/*------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	if( ChkPriority(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*---------------*/
	/* No.7 �`�F�b�N */
	/*---------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*-------------------------------------------------*/
	/* No.8 Specimen Collection Date and Time �`�F�b�N */
	/*-------------------------------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*---------------------------*/
	/* No.9 �`�F�b�N */
	/*---------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*----------------*/
	/* No.10 �`�F�b�N */
	/*----------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*----------------*/
	/* No.11 �`�F�b�N */
	/*----------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*----------------------------*/
	/* No.12 Action Code �`�F�b�N */
	/*----------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	if( ChkActionCode(aRcvMsg) == MESSAGE_ERR ) {
		return MESSAGE_ERR;
	}
	/*----------------*/
	/* No.13 �`�F�b�N */
	/*----------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*----------------*/
	/* No.14 �`�F�b�N */
	/*----------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*----------------*/
	/* No.15 �`�F�b�N */
	/*----------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*------------------------------------*/
	/* No.16 Specimen Descriptor �`�F�b�N */
	/*------------------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*----------------*/
	/* No.17 �`�F�b�N */
	/*----------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*----------------*/
	/* No.18 �`�F�b�N */
	/*----------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*----------------*/
	/* No.19 �`�F�b�N */
	/*----------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*----------------*/
	/* No.20 �`�F�b�N */
	/*----------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*----------------*/
	/* No.21 �`�F�b�N */
	/*----------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*----------------*/
	/* No.22 �`�F�b�N */
	/*----------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*----------------*/
	/* No.23 �`�F�b�N */
	/*----------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	if( ChkDateTmResRep_LstMod(p,aRcvMsg) == MESSAGE_ERR ) {
		return MESSAGE_ERR;
	}
	/*----------------*/
	/* No.24 �`�F�b�N */
	/*----------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*----------------*/
	/* No.25 �`�F�b�N */
	/*----------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*-----------------------------*/
	/* No.26 Report Types �`�F�b�N */
	/*-----------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	sTestOrderRcd.cReportTypes[0] = aRcvMsg[iRcvMsgCnt];
	++iRcvMsgCnt;
	/*----------------*/
	/* No.27 �`�F�b�N */
	/*------- --------*/
	iWrk = ChkFieldDiv2(aRcvMsg);
	if( iWrk == MESSAGE_ERR ) {
		return MESSAGE_ERR;
	} else if( iWrk == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*----------------*/
	/* No.28 �`�F�b�N */
	/*------- --------*/
	iWrk = ChkFieldDiv2(aRcvMsg);
	if( iWrk == MESSAGE_ERR ) {
		return MESSAGE_ERR;
	} else if( iWrk == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*----------------*/
	/* No.29 �`�F�b�N */
	/*------- --------*/
	iWrk = ChkFieldDiv2(aRcvMsg);
	if( iWrk == MESSAGE_ERR ) {
		return MESSAGE_ERR;
	} else if( iWrk == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*----------------*/
	/* No.30 �`�F�b�N */
	/*------- --------*/
	iWrk = ChkFieldDiv2(aRcvMsg);
	if( iWrk == MESSAGE_ERR ) {
		return MESSAGE_ERR;
	} else if( iWrk == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*----------------*/
	/* No.31 �`�F�b�N */
	/*------- --------*/
	iWrk = ChkFieldDiv2(aRcvMsg);
	if( iWrk == MESSAGE_ERR ) {
		return MESSAGE_ERR;
	} else if( iWrk == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*-------------*/
	/* CR �`�F�b�N */
	/*------- -----*/
	return MESSAGE_OK;
}
/**********************************************************************/
/*                                                                    */
/*   function name : ChkInstSpmenId                                   */
/*                                                                    */
/*   purpose : Instrument Specimen ID �`�F�b�N����                    */
/*                                                                    */
/*   data : 2005.12.14                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int ChkInstSpmenId(SOCKET_INF* p,char* aRcvMsg)
{
	int iCnt;
//	int iWrk;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sChkInstSpmenId()\n", Now());
#endif

	/* �t�B�[���h���̃`�F�b�N */
//	iWrk = iRcvMsgCnt;
	/* �R���|�l���g(SampleNo)���̃`�F�b�N */
	for( iCnt=0; iCnt<(5+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
			break;
		}
		sTestOrderRcd.cSampleNo[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( (iCnt < 1) || (iCnt > 5) ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}
	p->sSndorder.bskseq = atoi( sTestOrderRcd.cSampleNo );
	++iRcvMsgCnt;
	memset( p->cRackNum,0,sizeof(p->cRackNum) );
	memset( p->cRackPosNum,0,sizeof(p->cRackPosNum) );
	/* �R���|�l���g(Rack ID)���̃`�F�b�N */
	for( iCnt=0; iCnt<(5+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
			break;
		}
		sTestOrderRcd.cRackId[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( (iCnt < 1) || (iCnt > 5) ) {	/* ���������ُ� */
		return MESSAGE_ERR;
	}
	memcpy( p->cRackNum,sTestOrderRcd.cRackId,5 );
	++iRcvMsgCnt;
	/* �R���|�l���g(Position No)���̃`�F�b�N */
	for( iCnt=0; iCnt<(1+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
			break;
		}
		sTestOrderRcd.cPositionNo[0] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( iCnt != 1 ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}
	p->cRackPosNum[0] = sTestOrderRcd.cPositionNo[0];
	if( atoi(p->cRackPosNum) == 0 ) {
		return MESSAGE_ERR;
	}
	++iRcvMsgCnt;
	if( aRcvMsg[iRcvMsgCnt] == cFieldDivChar ) {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	/* �R���|�l���g(Rack Type)���̃`�F�b�N */
	for( iCnt=0; iCnt<(2+1); iCnt++ ) {
		if( (aRcvMsg[iRcvMsgCnt] == cCmpDivChar) || (aRcvMsg[iRcvMsgCnt] == cFieldDivChar) ) {
			break;
		}
		sTestOrderRcd.cRackType[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( (iCnt < 1) || (iCnt > 2) ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}

	++iRcvMsgCnt;
	if( aRcvMsg[iRcvMsgCnt] == cFieldDivChar ) {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	/* �R���|�l���g(Container Type)���̃`�F�b�N */
	for( iCnt=0; iCnt<(2+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cFieldDivChar ) {
			break;
		}
		sTestOrderRcd.cContainerType[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( (iCnt == 0) || (iCnt == 2) ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}
	return MESSAGE_NO_ERR;
}
/**********************************************************************/
/*                                                                    */
/*   function name : ChkUniTestId_O                                   */
/*                                                                    */
/*   purpose : Universal Test ID(���ڑI��)�`�F�b�N����                */
/*                                                                    */
/*   data : 2005.12.22                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int ChkUniTestId_O(SOCKET_INF* p,char* aRcvMsg)
{
	int iCnt;
	int iCnt2;
//	int iWrk;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sChkUniTestId_O()\n", Now());
#endif

	/* �t�B�[���h���̃`�F�b�N */
//	iWrk = iRcvMsgCnt;

	/* �˗����������[�v */
	for( iCnt2=0; iCnt2<MAX_ITEM_NUM; iCnt2++ ) {

		if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
			return MESSAGE_NO_ERR;
		}
		++iRcvMsgCnt;
		if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
			return MESSAGE_NO_ERR;
		}
		++iRcvMsgCnt;
		if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
			return MESSAGE_NO_ERR;
		}
		++iRcvMsgCnt;
		/* �R���|�l���g(Application Code)���̃`�F�b�N */
		for( iCnt=0; iCnt<(5+1); iCnt++ ) {
			if( (aRcvMsg[iRcvMsgCnt] == cCmpDivChar) || (aRcvMsg[iRcvMsgCnt] == cRepeatDivChar)
															  || (aRcvMsg[iRcvMsgCnt] == cFieldDivChar) ) {
				break;
			}
			sTestOrderRcd.sUniTestId[iCnt2].cAppCode[iCnt] = aRcvMsg[iRcvMsgCnt];
			++iRcvMsgCnt;
		}
		if( (iCnt < 1) || (iCnt > 5) ) {	/* ���������ُ� */
			return MESSAGE_ERR;
		}
		++(p->iKekkaNum);

		if( aRcvMsg[iRcvMsgCnt] == cFieldDivChar ) {
			if( p->iOrderNum == (iCnt2+1) ) {
				return MESSAGE_NO_ERR;
			} else {
				return MESSAGE_NO_ERR;
			}
		} else if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
			++iRcvMsgCnt;
			/* �R���|�l���g(Dilution)���̃`�F�b�N */
			for( iCnt=0; iCnt<(3+1); iCnt++ ) {
				if( (aRcvMsg[iRcvMsgCnt] == cRepeatDivChar) || (aRcvMsg[iRcvMsgCnt] == cFieldDivChar) ) {
					break;
				}
				sTestOrderRcd.sUniTestId[iCnt2].cDilution[iCnt] = aRcvMsg[iRcvMsgCnt];
				++iRcvMsgCnt;
			}
			if( iCnt > 3 ) {	/* ���������ُ� */
				return MESSAGE_NO_ERR;
			}
			if( aRcvMsg[iRcvMsgCnt] == cFieldDivChar ) {
				if( p->iOrderNum == (iCnt2+1) ) {
					return MESSAGE_NO_ERR;
				} else {
					return MESSAGE_NO_ERR;
				}
			}
		} else {
			return MESSAGE_NO_ERR;
		}
		++iRcvMsgCnt;
	}
	return MESSAGE_NO_ERR;
}
/**********************************************************************/
/*                                                                    */
/*   function name : ChkPriority                                      */
/*                                                                    */
/*   purpose : ChkPriority �`�F�b�N����                               */
/*                                                                    */
/*   data : 2006.04.05                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int ChkPriority(char* aRcvMsg)
{
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sChkPriority()\n", Now());
#endif

	if( (aRcvMsg[iRcvMsgCnt] == 'S') || (aRcvMsg[iRcvMsgCnt] == 'R') ) {
		sTestOrderRcd.cPriority[0] = aRcvMsg[iRcvMsgCnt];
	} else {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	return MESSAGE_NO_ERR;
}
/**********************************************************************/
/*                                                                    */
/*   function name : ChkActionCode                                    */
/*                                                                    */
/*   purpose : Action Code �`�F�b�N����                               */
/*                                                                    */
/*   data : 2005.12.26                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int ChkActionCode(char* aRcvMsg)
{
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sChkActionCode()\n", Now());
#endif

	if( (aRcvMsg[iRcvMsgCnt] == 'N') || (aRcvMsg[iRcvMsgCnt] == 'Q') ) {
		sTestOrderRcd.cActionCode[0] = aRcvMsg[iRcvMsgCnt];
	} else {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	return MESSAGE_NO_ERR;
}
/**********************************************************************/
/*                                                                    */
/*   function name : ChkDateTmResRep_LstMod                           */
/*                                                                    */
/*   purpose : Date/Time Results Reported or Last Modified �`�F�b�N���� */
/*                                                                    */
/*   data : 2005.12.26                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int ChkDateTmResRep_LstMod(SOCKET_INF* p,char* aRcvMsg)
{
	int iCnt;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sChkDateTmResRep_LstMod()\n", Now());
#endif

	for( iCnt=0; iCnt<14+1; iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cFieldDivChar ) {
			break;
		}
		sTestOrderRcd.cDateTmResRep_LstMod[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( iCnt != 14 ) {	/* ���������ُ� */
		memset( sTestOrderRcd.cDateTmResRep_LstMod,0,sizeof(sTestOrderRcd.cDateTmResRep_LstMod) );
		strcpy( sTestOrderRcd.cDateTmResRep_LstMod,"10000101000001" );	/* 1000-01-01 00:00:01 */
	}

	return MESSAGE_NO_ERR;
}
/**********************************************************************/
/*                                                                    */
/*   function name : DecodeResultRcd                                  */
/*                                                                    */
/*   purpose : ���茋�ʃ��R�[�h�f�R�[�h����                           */
/*                                                                    */
/*   data : 2005.12.27                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int DecodeResultRcd(SOCKET_INF* p,char* aRcvMsg)
{
	int	iCnt;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sDecodeResultRcd\n", Now());
#endif

	iRcvMsgCnt = 0;
	memset(&sResultRcd,0,sizeof(sResultRcd));
	/*------------------------------*/
	/* No.1 Record Type ID �`�F�b�N */
	/*------------------------------*/
	++iRcvMsgCnt;
	/*-------------------------------*/
	/* No.2 Sequence Number �`�F�b�N */
	/*-------------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	if( ChkSeqNum( sResultRcd.cSeqNum,aRcvMsg ) == MESSAGE_ERR ) {
		return MESSAGE_ERR;
	}
	if( atoi(sResultRcd.cSeqNum) == 1 ) {

		p->iOrderNum = 0;
		memset(&(p->sSndorder),0,sizeof(p->sSndorder));
		p->sSndorder.seqnum = atoi( sPatientInfRcd.cSeqNum );
		strncpy( p->sSndorder.racktype,sTestOrderRcd.cRackType,2 );
		p->sSndorder.bskseq = atoi( sTestOrderRcd.cSampleNo );
		if( p->pKekka != NULL ) {
			free( p->pKekka );
			p->pKekka = NULL;
		}
		if( p->pSaiken != NULL ) {
			free( p->pSaiken );
			p->pSaiken = NULL;
		}
		p->pKekka = malloc(sizeof(Kekka)*(p->iKekkaNum));

		for( iCnt=0;iCnt<p->iKekkaNum;iCnt++ ) {
			memset( &(p->pKekka[iCnt]),0,sizeof(Kekka) );
		}
		p->pSaiken = malloc(sizeof(SaikenInfo)*(p->iKekkaNum));
		for( iCnt=0;iCnt<p->iKekkaNum;iCnt++ ) {
			memset( &(p->pSaiken[iCnt]),0,sizeof(SaikenInfo) );
		}
		p->iKekkaCnt = 0;
	}
	/*---------------------------------*/
	/* No.3 Universal Test ID �`�F�b�N */
	/*---------------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	if( ChkUniTestId_R(p,aRcvMsg) == MESSAGE_ERR ) {
		return MESSAGE_ERR;
	}
	/*-----------------------------------------*/
	/* No.4 Data or Measurement Value �`�F�b�N */
	/*-----------------------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	if( ChkDat_MeasrmntVal(p,aRcvMsg) == MESSAGE_ERR ) {
		return MESSAGE_ERR;
	}
	/*---------------------*/
	/* No.5 Units �`�F�b�N */
	/*---------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*---------------*/
	/* No.6 �`�F�b�N */
	/*---------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*-------------------------------------*/
	/* No.7 Result Abnormal Flags �`�F�b�N */
	/*-------------------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	if( ChkResAbnmlFlg(aRcvMsg) == MESSAGE_ERR ) {
		return MESSAGE_ERR;
	}
	/*---------------*/
	/* No.8 �`�F�b�N */
	/*---------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*-----------------------------*/
	/* No.9 Result Status �`�F�b�N */
	/*-----------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	if( ChkResStatus(aRcvMsg) == MESSAGE_ERR ) {
		return MESSAGE_ERR;
	}
	if( sResultRcd.cResStat[0] != 'F' ) {
		p->iRcvMsg = MSG_NON;
	}
	/*----------------*/
	/* No.10 �`�F�b�N */
	/*----------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*----------------------------------------*/
	/* No.11 Operator Identification �`�F�b�N */
	/*----------------------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*----------------*/
	/* No.12 �`�F�b�N */
	/*----------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	
	{
		int iCnt;
		for( iCnt=0; iCnt<(14+1); iCnt++ ) {
			if( aRcvMsg[iRcvMsgCnt] == CR ) {
				break;
			}
			if( aRcvMsg[iRcvMsgCnt] == cFieldDivChar ) {
				break;
			}
			sResultRcd.cTestStarted[iCnt] = aRcvMsg[iRcvMsgCnt];
			++iRcvMsgCnt;
		}
	}
	/*----------------*/
	/* No.13 �`�F�b�N */
	/*----------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	/*----------------*/
	/* No.14 �`�F�b�N */
	/*----------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	if( ChkInstIdentif(p,aRcvMsg) == MESSAGE_ERR ) {
		return MESSAGE_ERR;
	}
	/*----------------*/
	/* CR �`�F�b�N */
	/*------- --------*/
	return MESSAGE_OK;
}
/**********************************************************************/
/*                                                                    */
/*   function name : ChkUniTestId_R                                   */
/*                                                                    */
/*   purpose : Universal Test ID(���茋��)�`�F�b�N����                */
/*                                                                    */
/*   data : 2005.12.27                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int ChkUniTestId_R(SOCKET_INF* p,char* aRcvMsg)
{
	int iCnt;
//	int iWrk;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sChkUniTestId_R()\n", Now());
#endif

	/* �t�B�[���h���̃`�F�b�N */
//	iWrk = iRcvMsgCnt;
	if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	/* �R���|�l���g(Application Code)���̃`�F�b�N */
	for( iCnt=0; iCnt<(5+1); iCnt++ ) {
		if( (aRcvMsg[iRcvMsgCnt] == '/') || (aRcvMsg[iRcvMsgCnt] == cFieldDivChar) ) {
			break;
		}
		sResultRcd.cAppCode[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	/* �������ڃR�[�h�ݒ� */

	if( (iCnt < 1) || (iCnt > 5) ) {	/* ���������ُ� */
		ClrSaikenInf(p);
		return MESSAGE_ERR;
	}
	if( aRcvMsg[iRcvMsgCnt] == cFieldDivChar ) {
		return MESSAGE_NO_ERR;
	} else if( aRcvMsg[iRcvMsgCnt] == '/' ) {
		++iRcvMsgCnt;
		/* �R���|�l���g(Dilution)���̃`�F�b�N */
		for( iCnt=0; iCnt<(3+1); iCnt++ ) {
			if( aRcvMsg[iRcvMsgCnt] == cFieldDivChar ) {
				break;
			}
			sResultRcd.cDilution[iCnt] = aRcvMsg[iRcvMsgCnt];
			++iRcvMsgCnt;
		}
		if( iCnt > 3 ) {	/* ���������ُ� */
			return MESSAGE_NO_ERR;
		}
	} else {
		return MESSAGE_NO_ERR;
	}

	/* ���{��ߔ{���ݒ� */

	return MESSAGE_NO_ERR;
}
/**********************************************************************/
/*                                                                    */
/*   function name : ChkDat_MeasrmntVal                               */
/*                                                                    */
/*   purpose : Data or Measurement Value�`�F�b�N����                  */
/*                                                                    */
/*   data : 2005.12.28                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int ChkDat_MeasrmntVal(SOCKET_INF* p,char* aRcvMsg)
{
	int iCnt;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sChkDat_MeasrmntVal()\n", Now());
#endif

	/* �t�B�[���h���̃`�F�b�N */
	for( iCnt=0; iCnt<(15+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cFieldDivChar ) {
			break;
		}
		sResultRcd.cDat_MeasrmntVal[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}

	return MESSAGE_NO_ERR;
}
/**********************************************************************/
/*                                                                    */
/*   function name : ChkResAbnmlFlg                                   */
/*                                                                    */
/*   purpose : Result Abnormal Flags�`�F�b�N����                      */
/*                                                                    */
/*   data : 2005.12.28                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int ChkResAbnmlFlg(char* aRcvMsg)
{
	int iCnt;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sChkResAbnmlFlg()\n", Now());
#endif

	/* �t�B�[���h���̃`�F�b�N */
	for( iCnt=0; iCnt<(2+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cFieldDivChar ) {
			break;
		}
		sResultRcd.cResAbnmlFlg[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	return MESSAGE_NO_ERR;
}
/**********************************************************************/
/*                                                                    */
/*   function name : ChkResStatus                                     */
/*                                                                    */
/*   purpose : Result Status �`�F�b�N����                             */
/*                                                                    */
/*   data : 2006.03.13                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int ChkResStatus(char* aRcvMsg)
{
	int iCnt;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sChkResStatus()\n", Now());
#endif

	/* �t�B�[���h���̃`�F�b�N */
	for( iCnt=0; iCnt<(1+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cFieldDivChar ) {
			break;
		}
		sResultRcd.cResStat[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	return MESSAGE_NO_ERR;
}
/**********************************************************************/
/*                                                                    */
/*   function name : ChkInstIdentif                                   */
/*                                                                    */
/*   purpose : Instrument Identification�`�F�b�N����                  */
/*                                                                    */
/*   data : 2005.12.28                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int ChkInstIdentif(SOCKET_INF* p,char* aRcvMsg)
{
	int iCnt;
	char cWrk[8];
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sChkInstIdentif()\n", Now());
#endif

	memset( cWrk,0,sizeof(cWrk) );

	/* �t�B�[���h���̃`�F�b�N */
	for( iCnt=0; iCnt<(4+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == CR ) {
			break;
		}
		sResultRcd.cInstIdentif[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}

	if( sResultRcd.cInstIdentif[0] == 'C' ) {
		cWrk[0] = sResultRcd.cInstIdentif[1];
	} else {
		cWrk[0] = '0';
	}
	/* �v���b�gSEQ�C���N�������g */
#ifdef _DEBUG_
	printf( "ChkInstIdentif(%d) : ++(p->aPltseq[atoi(cWrk)]) = %d\n", __LINE__, p->aPltseq[atoi(cWrk)] );
#endif
	++(p->aPltseq[atoi(cWrk)]);
#ifdef _DEBUG_
	printf( "ChkInstIdentif(%d) : ++(p->aPltseq[atoi(cWrk)]) = %d\n", __LINE__, p->aPltseq[atoi(cWrk)] );
#endif

	return MESSAGE_NO_ERR;
}
/**********************************************************************/
/*                                                                    */
/*   function name : DecodeC_RESRcd                                   */
/*                                                                    */
/*   purpose : ���߃��R�[�h(C_RES)�f�R�[�h����                        */
/*                                                                    */
/*   data : 2005.12.28                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int DecodeCommentRcd(int iType,char* aRcvMsg)
{
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sDecodeCommentRcd\n", Now());
#endif

	iRcvMsgCnt = 0;
	memset(&sCommentRcd,0,sizeof(sCommentRcd));
	/*------------------------------*/
	/* No.1 Record Type ID �`�F�b�N */
	/*------------------------------*/
	++iRcvMsgCnt;
	/*-------------------------------*/
	/* No.2 Sequence Number �`�F�b�N */
	/*-------------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	if( ChkSeqNum( sCommentRcd.cSeqNum,aRcvMsg ) == MESSAGE_ERR ) {
		return MESSAGE_ERR;
	}
	/*------------------------------*/
	/* No.3 Comment Source �`�F�b�N */
	/*------------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	sCommentRcd.cCmntSrc[0] = aRcvMsg[iRcvMsgCnt];
	++iRcvMsgCnt;
	/*----------------------------*/
	/* No.4 Comment Text �`�F�b�N */
	/*----------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	if( ChkSeqNum( sCommentRcd.cCmmTxt,aRcvMsg ) == MESSAGE_ERR ) {
		return MESSAGE_ERR;
	}
	/*----------------------------*/
	/* No.5 Comment Type �`�F�b�N */
	/*----------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	sCommentRcd.cCmntType[0] = aRcvMsg[iRcvMsgCnt];
	++iRcvMsgCnt;
	/*----------------*/
	/* CR �`�F�b�N */
	/*------- --------*/
	return MESSAGE_OK;
}
/**********************************************************************/
/*                                                                    */
/*   function name : DecodeCalbRcd                                    */
/*                                                                    */
/*   purpose : �L�����u���[�V�������ʃ��R�[�h�f�R�[�h����             */
/*                                                                    */
/*   data : 2006.01.24                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int DecodeCalbRcd(SOCKET_INF* p,char* aRcvMsg)
{
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

	ClrSaikenInf(p);
	p->iOrderNum = 0;
	memset(&(p->sSndorder),0,sizeof(p->sSndorder));

#ifdef _DEBUG_
	printf("%sDecodeCalbRcd\n", Now());
#endif

	iRcvMsgCnt = 0;
	memset(&sCalbRcd,0,sizeof(sCalbRcd));
	/*------------------------------*/
	/* No.1 Record Type ID �`�F�b�N */
	/*------------------------------*/
	++iRcvMsgCnt;
	/*-------------------------------*/
	/* No.2 Sequence Number �`�F�b�N */
	/*-------------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	if( ChkSeqNum( sCalbRcd.cSeqNum,aRcvMsg ) == MESSAGE_ERR ) {
		return MESSAGE_ERR;
	}
	/*----------------------------------*/
	/* No.3 Record Type Sub ID �`�F�b�N */
	/*----------------------------------*/
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	if( ChkSubId(aRcvMsg) == MESSAGE_ERR ) {
		return MESSAGE_ERR;
	}
	/* �t�B�[���h��؂�`�F�b�N*/
	if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
		return MESSAGE_OK;
	}
	if( strncmp( sCalbRcd.cSubId,"ABS",3 ) == 0 ) {

	} else if( strncmp( sCalbRcd.cSubId,"PCR",3 ) == 0 ) {
		/*---------------------------*/
		/* No.4 Operator ID �`�F�b�N */
		/*---------------------------*/
		/*-------------------------*/
		/* No.5 Test Code �`�F�b�N */
		/*-------------------------*/
		/* �t�B�[���h��؂�`�F�b�N*/
		if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
			return MESSAGE_OK;
		}
		if( ChkTestCode(p,aRcvMsg) == MESSAGE_ERR ) {
			return MESSAGE_ERR;
		}
		/*-------------------------*/
		/* No.6 Module ID �`�F�b�N */
		/*-------------------------*/
		/* �t�B�[���h��؂�`�F�b�N*/
		if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
			return MESSAGE_OK;
		}
		if( ChkModuleId(p,aRcvMsg) == MESSAGE_ERR ) {
			return MESSAGE_ERR;
		}
		/*---------------------------------*/
		/* No.7 Calibration Alarm �`�F�b�N */
		/*---------------------------------*/
		/* �t�B�[���h��؂�`�F�b�N*/
		if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
			return MESSAGE_OK;
		}
		if( ChkCalbAlarm(p,aRcvMsg) == MESSAGE_ERR ) {
			return MESSAGE_ERR;
		}
		/*-----------------------------*/
		/* No.8 SD Data Field �`�F�b�N */
		/*-----------------------------*/
		/* �t�B�[���h��؂�`�F�b�N*/
		if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
			return MESSAGE_OK;
		}
		/*------------------------*/
		/* No.9 STD Data �`�F�b�N */
		/*------------------------*/
		/* �t�B�[���h��؂�`�F�b�N*/
		if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
			return MESSAGE_OK;
		}
		if( ChkStdDat(p,aRcvMsg) == MESSAGE_ERR ) {
			return MESSAGE_ERR;
		}
	} else if( strncmp( sCalbRcd.cSubId,"ICR",3 ) == 0 ) {
		/*---------------------------*/
		/* No.4 Operator ID �`�F�b�N */
		/*---------------------------*/
		/*-------------------------*/
		/* No.5 Module ID �`�F�b�N */
		/*-------------------------*/
		/* �t�B�[���h��؂�`�F�b�N*/
		if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
			return MESSAGE_OK;
		}
		if( ChkModuleId(p,aRcvMsg) == MESSAGE_ERR ) {
			return MESSAGE_ERR;
		}
		/*-----------------------------------*/
		/* No.6 Na calibraion Alarm �`�F�b�N */
		/*-----------------------------------*/
		/* �t�B�[���h��؂�`�F�b�N*/
		if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
			return MESSAGE_OK;
		}
		if( ChkCalbAlarm_Ise(ITEM_NA,aRcvMsg) == MESSAGE_ERR ) {
			return MESSAGE_ERR;
		}
		/*----------------------------------*/
		/* No.7 K calibraion Alarm �`�F�b�N */
		/*----------------------------------*/
		/* �t�B�[���h��؂�`�F�b�N*/
		if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
			return MESSAGE_OK;
		}
		if( ChkCalbAlarm_Ise(ITEM_K,aRcvMsg) == MESSAGE_ERR ) {
			return MESSAGE_ERR;
		}
		/*-----------------------------------*/
		/* No.8 Cl calibraion Alarm �`�F�b�N */
		/*-----------------------------------*/
		/* �t�B�[���h��؂�`�F�b�N*/
		if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
			return MESSAGE_OK;
		}
		if( ChkCalbAlarm_Ise(ITEM_CL,aRcvMsg) == MESSAGE_ERR ) {
			return MESSAGE_ERR;
		}
		/*-----------------------------*/
		/* No.9 Na data Alarm �`�F�b�N */
		/*-----------------------------*/
		/* �t�B�[���h��؂�`�F�b�N*/
		if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
			return MESSAGE_OK;
		}
		if( ChkDatAlarm(ITEM_NA,aRcvMsg) == MESSAGE_ERR ) {
			return MESSAGE_ERR;
		}
		/*-----------------------------*/
		/* No.10 K data Alarm �`�F�b�N */
		/*-----------------------------*/
		/* �t�B�[���h��؂�`�F�b�N*/
		if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
			return MESSAGE_OK;
		}
		if( ChkDatAlarm(ITEM_K,aRcvMsg) == MESSAGE_ERR ) {
			return MESSAGE_ERR;
		}
		/*------------------------------*/
		/* No.11 Cl data Alarm �`�F�b�N */
		/*------------------------------*/
		/* �t�B�[���h��؂�`�F�b�N*/
		if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
			return MESSAGE_OK;
		}
		if( ChkDatAlarm(ITEM_CL,aRcvMsg) == MESSAGE_ERR ) {
			return MESSAGE_ERR;
		}
		/*------------------------*/
		/* No.12 Na data �`�F�b�N */
		/*------------------------*/
		/* �t�B�[���h��؂�`�F�b�N*/
		if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
			return MESSAGE_OK;
		}
		if( ChkData(ITEM_NA,aRcvMsg) == MESSAGE_ERR ) {
			return MESSAGE_ERR;
		}
		/*-----------------------*/
		/* No.13 K data �`�F�b�N */
		/*-----------------------*/
		/* �t�B�[���h��؂�`�F�b�N*/
		if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
			return MESSAGE_OK;
		}
		if( ChkData(ITEM_K,aRcvMsg) == MESSAGE_ERR ) {
			return MESSAGE_ERR;
		}
		/*------------------------*/
		/* No.14 Cl data �`�F�b�N */
		/*------------------------*/
		/* �t�B�[���h��؂�`�F�b�N*/
		if( ChkFieldDiv(aRcvMsg) == MESSAGE_OK ) {
			return MESSAGE_OK;
		}
		if( ChkData(ITEM_CL,aRcvMsg) == MESSAGE_ERR ) {
			return MESSAGE_ERR;
		}
	}
	/*----------------*/
	/* CR �`�F�b�N */
	/*------- --------*/
	return MESSAGE_OK;
}
/**********************************************************************/
/*                                                                    */
/*   function name : ChkSubId                                         */
/*                                                                    */
/*   purpose : Record Type Sub ID�`�F�b�N����                         */
/*                                                                    */
/*   data : 2006.01.24                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int ChkSubId(char* aRcvMsg)
{
	int iCnt;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sChkSubId()\n", Now());
#endif

	/* �t�B�[���h���̃`�F�b�N */
	for( iCnt=0; iCnt<(3+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cFieldDivChar ) {
			break;
		}
		sCalbRcd.cSubId[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	return MESSAGE_NO_ERR;
}
/**********************************************************************/
/*                                                                    */
/*   function name : ChkModuleId                                      */
/*                                                                    */
/*   purpose : Module ID�`�F�b�N����                                  */
/*                                                                    */
/*   data : 2006.01.24                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int ChkModuleId(SOCKET_INF* p,char* aRcvMsg)
{
	char cWrk[8];
	int iCnt;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sChkModuleId()\n", Now());
#endif

	memset( cWrk,0,sizeof(cWrk) );

	/* �t�B�[���h���̃`�F�b�N */
	for( iCnt=0; iCnt<(4+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cFieldDivChar ) {
			break;
		}
		sCalbRcd.cModuleId[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}

	if( sCalbRcd.cModuleId[0] == 'C' ) {
		cWrk[0] = sCalbRcd.cModuleId[1];
	} else {
		cWrk[0] = '0';
	}
	/* �v���b�gSEQ�C���N�������g */
#ifdef _DEBUG_
	printf( "ChkModuleId(%d) : ++(p->aPltseq[atoi(cWrk)]) = %d\n", __LINE__, p->aPltseq[atoi(cWrk)] );
#endif
	++(p->aPltseq[atoi(cWrk)]);
#ifdef _DEBUG_
	printf( "ChkModuleId(%d) : ++(p->aPltseq[atoi(cWrk)]) = %d\n", __LINE__, p->aPltseq[atoi(cWrk)] );
#endif

	return MESSAGE_NO_ERR;
}
/**********************************************************************/
/*                                                                    */
/*   function name : ChkTestCode                                      */
/*                                                                    */
/*   purpose : Test Code�`�F�b�N����                                  */
/*                                                                    */
/*   data : 2006.01.24                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int ChkTestCode(SOCKET_INF* p,char* aRcvMsg)
{
	int iCnt;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sChkTestCode()\n", Now());
#endif

	if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;

	/* �t�B�[���h���̃`�F�b�N */
	for( iCnt=0; iCnt<(5+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cFieldDivChar ) {
			break;
		}
		sCalbRcd.cTestCode[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}

	return MESSAGE_NO_ERR;
}
/**********************************************************************/
/*                                                                    */
/*   function name : ChkCalbAlarm                                     */
/*                                                                    */
/*   purpose : Calibration Alarm�`�F�b�N����                          */
/*                                                                    */
/*   data : 2006.01.24                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int ChkCalbAlarm(SOCKET_INF* p,char* aRcvMsg)
{
	int iCnt;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sChkCalibAlarm()\n", Now());
#endif

	/* �t�B�[���h���̃`�F�b�N */
	for( iCnt=0; iCnt<(3+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cFieldDivChar ) {
			break;
		}
		sCalbRcd.cCalbAlarm[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}

	return MESSAGE_NO_ERR;
}
/**********************************************************************/
/*                                                                    */
/*   function name : ChkStdDat                                        */
/*                                                                    */
/*   purpose : STD Dat�`�F�b�N����                                    */
/*                                                                    */
/*   data : 2006.01.24                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int ChkStdDat(SOCKET_INF* p,char* aRcvMsg)
{
	int iCnt;
	int iCnt2;
//	int iWrk;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sChkStdDat()\n", Now());
#endif

	/* �t�B�[���h���̃`�F�b�N */
//	iWrk = iRcvMsgCnt;

	/* STD6�����[�v */
	for( iCnt2=0; iCnt2<6; iCnt2++ ) {
		/* �R���|�l���g(1��ڂ̋z���x�f�[�^)���̃`�F�b�N */
		for( iCnt=0; iCnt<(6+1); iCnt++ ) {
			if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
				break;
			}
			sCalbRcd.sStdDat[iCnt2].c1stDat[iCnt] = aRcvMsg[iRcvMsgCnt];
			++iRcvMsgCnt;
		}
		if( iCnt > 6 ) {	/* ���������ُ� */
			return MESSAGE_NO_ERR;
		}
		if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
			return MESSAGE_NO_ERR;
		}
		++iRcvMsgCnt;
		/* �R���|�l���g(1��ڂ̏����܂��͍ŏI�z���x�f�[�^)���̃`�F�b�N */
		for( iCnt=0; iCnt<(6+1); iCnt++ ) {
			if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
				break;
			}
			sCalbRcd.sStdDat[iCnt2].c1stIni_LstDat[iCnt] = aRcvMsg[iRcvMsgCnt];
			++iRcvMsgCnt;
		}
		if( iCnt > 6 ) {	/* ���������ُ� */
			return MESSAGE_NO_ERR;
		}
		if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
			return MESSAGE_NO_ERR;
		}
		++iRcvMsgCnt;
		/* �R���|�l���g(2��ڂ̋z���x�f�[�^)���̃`�F�b�N */
		for( iCnt=0; iCnt<(6+1); iCnt++ ) {
			if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
				break;
			}
			sCalbRcd.sStdDat[iCnt2].c2ndDat[iCnt] = aRcvMsg[iRcvMsgCnt];
			++iRcvMsgCnt;
		}
		if( iCnt > 6 ) {	/* ���������ُ� */
			return MESSAGE_NO_ERR;
		}
		if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
			return MESSAGE_NO_ERR;
		}
		++iRcvMsgCnt;
		/* �R���|�l���g(2��ڂ̏����܂��͍ŏI�z���x�f�[�^)���̃`�F�b�N */
		for( iCnt=0; iCnt<(6+1); iCnt++ ) {
			if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
				break;
			}
			sCalbRcd.sStdDat[iCnt2].c2ndIni_LstDat[iCnt] = aRcvMsg[iRcvMsgCnt];
			++iRcvMsgCnt;
		}
		if( iCnt > 6 ) {	/* ���������ُ� */
			return MESSAGE_NO_ERR;
		}
		if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
			return MESSAGE_NO_ERR;
		}
		++iRcvMsgCnt;
		/* �R���|�l���g(�f�[�^�A���[��)���̃`�F�b�N */
		for( iCnt=0; iCnt<(3+1); iCnt++ ) {
			if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
				break;
			}
			sCalbRcd.sStdDat[iCnt2].cDatAlarm[iCnt] = aRcvMsg[iRcvMsgCnt];
			++iRcvMsgCnt;
		}
		if( iCnt > 3 ) {	/* ���������ُ� */
			return MESSAGE_NO_ERR;
		}
		if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
			return MESSAGE_NO_ERR;
		}
		++iRcvMsgCnt;
		/* �R���|�l���g(�v���]�[���l)���̃`�F�b�N */
		for( iCnt=0; iCnt<(6+1); iCnt++ ) {
			if( (aRcvMsg[iRcvMsgCnt] == cRepeatDivChar) || (aRcvMsg[iRcvMsgCnt] == CR)  ) {
				break;
			}
			sCalbRcd.sStdDat[iCnt2].cProZoneVal[iCnt] = aRcvMsg[iRcvMsgCnt];
			++iRcvMsgCnt;
		}
		if( iCnt > 6 ) {	/* ���������ُ� */
			return MESSAGE_NO_ERR;
		}
		if( aRcvMsg[iRcvMsgCnt] == CR ) {
			return MESSAGE_NO_ERR;
		}
		++iRcvMsgCnt;
	}
	return MESSAGE_NO_ERR;
}
/**********************************************************************/
/*                                                                    */
/*   function name : ChkCalbAlarm_Ise                                 */
/*                                                                    */
/*   purpose : Calibration Alarm(ISE)�`�F�b�N����                     */
/*                                                                    */
/*   data : 2006.01.24                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int ChkCalbAlarm_Ise(int iType,char* aRcvMsg)
{
	int iCnt;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sChkCalbAlarm_Ise()\n", Now());
#endif

	/* �t�B�[���h���̃`�F�b�N */
	for( iCnt=0; iCnt<(3+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cFieldDivChar ) {
			break;
		}
		sCalbRcd.sIseCalbItem[iType].cCalbAlarm[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	return MESSAGE_NO_ERR;
}
/**********************************************************************/
/*                                                                    */
/*   function name : ChkDatAlarm                                      */
/*                                                                    */
/*   purpose : Data Alarm�`�F�b�N����                                 */
/*                                                                    */
/*   data : 2006.01.24                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int ChkDatAlarm(int iType,char* aRcvMsg)
{
	int iCnt;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sChkDatAlarm()\n", Now());
#endif

	/* �R���|�l���g(�����W���t�N�d�̓f�[�^�A���[��)���̃`�F�b�N */
	for( iCnt=0; iCnt<(3+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
			break;
		}
		sCalbRcd.sIseCalbItem[iType].cAlmNaibuKiden[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( iCnt > 3 ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}
	if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	/* �R���|�l���g(LOW�t�N�d�̓f�[�^�A���[��)���̃`�F�b�N */
	for( iCnt=0; iCnt<(3+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
			break;
		}
		sCalbRcd.sIseCalbItem[iType].cAlmLow[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( iCnt > 3 ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}
	if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	/* �R���|�l���g(HIGH�t�N�d�̓f�[�^�A���[��)���̃`�F�b�N */
	for( iCnt=0; iCnt<(3+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
			break;
		}
		sCalbRcd.sIseCalbItem[iType].cAlmHigh[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( iCnt > 3 ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}
	if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	/* �R���|�l���g(�L�����u���[�V�����t�N�d�̓f�[�^�A���[��)���̃`�F�b�N */
	for( iCnt=0; iCnt<(3+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
			break;
		}
		sCalbRcd.sIseCalbItem[iType].cAlmCalbKiden[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( iCnt > 3 ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}
	if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	/* �R���|�l���g(�\���p�X���[�v�f�[�^�A���[��)���̃`�F�b�N */
	for( iCnt=0; iCnt<(3+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
			break;
		}
		sCalbRcd.sIseCalbItem[iType].cAlmSlpe[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( iCnt > 3 ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}
	if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	/* �R���|�l���g(�����W���t�Z�x�f�[�^�A���[��)���̃`�F�b�N */
	for( iCnt=0; iCnt<(3+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
			break;
		}
		sCalbRcd.sIseCalbItem[iType].cAlmNaibuNodo[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( iCnt > 3 ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}
	if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	/* �R���|�l���g(�L�����u���[�V�����t�Z�x�f�[�^�A���[��)���̃`�F�b�N */
	for( iCnt=0; iCnt<(3+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
			break;
		}
		sCalbRcd.sIseCalbItem[iType].cAlmCalbNodo[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( iCnt > 3 ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}
	if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	/* �R���|�l���g(�␳�W���f�[�^�A���[��)���̃`�F�b�N */
	for( iCnt=0; iCnt<(3+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cFieldDivChar ) {
			break;
		}
		sCalbRcd.sIseCalbItem[iType].cAlmHosei[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( iCnt > 3 ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}
	return MESSAGE_NO_ERR;
}
/**********************************************************************/
/*                                                                    */
/*   function name : ChkData                                          */
/*                                                                    */
/*   purpose : Data�`�F�b�N����                                       */
/*                                                                    */
/*   data : 2006.01.24                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int ChkData(int iType,char* aRcvMsg)
{
	int iCnt;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sChkData()\n", Now());
#endif

	/* �R���|�l���g(�����W���t�N�d�̓f�[�^)���̃`�F�b�N */
	for( iCnt=0; iCnt<(6+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
			break;
		}
		sCalbRcd.sIseCalbItem[iType].cDatNaibuKiden[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( iCnt > 6 ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}
	if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	/* �R���|�l���g(LOW�t�N�d�̓f�[�^)���̃`�F�b�N */
	for( iCnt=0; iCnt<(6+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
			break;
		}
		sCalbRcd.sIseCalbItem[iType].cDatLow[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( iCnt > 6 ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}
	if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	/* �R���|�l���g(HIGH�t�N�d�̓f�[�^)���̃`�F�b�N */
	for( iCnt=0; iCnt<(6+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
			break;
		}
		sCalbRcd.sIseCalbItem[iType].cDatHigh[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( iCnt > 6 ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}
	if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	/* �R���|�l���g(�L�����u���[�V�����t�N�d�̓f�[�^)���̃`�F�b�N */
	for( iCnt=0; iCnt<(6+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
			break;
		}
		sCalbRcd.sIseCalbItem[iType].cDatCalbKiden[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( iCnt > 6 ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}
	if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	/* �R���|�l���g(�\���p�X���[�v�f�[�^)���̃`�F�b�N */
	for( iCnt=0; iCnt<(6+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
			break;
		}
		sCalbRcd.sIseCalbItem[iType].cDatSlpe[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( iCnt > 6 ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}
	if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	/* �R���|�l���g(�����W���t�Z�x�f�[�^)���̃`�F�b�N */
	for( iCnt=0; iCnt<(6+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
			break;
		}
		sCalbRcd.sIseCalbItem[iType].cDatNaibu[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( iCnt > 6 ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}
	if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	/* �R���|�l���g(�L�����u���[�V�����t�Z�x�f�[�^)���̃`�F�b�N */
	for( iCnt=0; iCnt<(6+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cCmpDivChar ) {
			break;
		}
		sCalbRcd.sIseCalbItem[iType].cDatCalb[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( iCnt > 6 ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}
	if( aRcvMsg[iRcvMsgCnt] != cCmpDivChar ) {
		return MESSAGE_NO_ERR;
	}
	++iRcvMsgCnt;
	/* �R���|�l���g(�␳�W���f�[�^)���̃`�F�b�N */
	for( iCnt=0; iCnt<(6+1); iCnt++ ) {
		if( aRcvMsg[iRcvMsgCnt] == cFieldDivChar ) {
			break;
		} else if( aRcvMsg[iRcvMsgCnt] == CR ) {
			return MESSAGE_NO_ERR;
		}
		sCalbRcd.sIseCalbItem[iType].cDatHosei[iCnt] = aRcvMsg[iRcvMsgCnt];
		++iRcvMsgCnt;
	}
	if( iCnt > 6 ) {	/* ���������ُ� */
		return MESSAGE_NO_ERR;
	}
	return MESSAGE_NO_ERR;
}
/**********************************************************************/
/*                                                                    */
/*   function name : StatusCtrl                                       */
/*                                                                    */
/*   purpose : ��������                                               */
/*                                                                    */
/*   data : 2005.12.12                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
void StatusCtrl(SOCKET_INF* p)
{
	int		i;
	time_t	tEndTm;
	float	fWrk;

	/* �S���@�̃^�C�}�J�E���g */
	if( p == NULL ) {
		tEndTm = time(NULL);
		for( p=sSocketInf.next,i=0; p!=NULL; p=p->next,i++ ) {
			 if( p->fTmOutVal > 0 ) {
				fWrk = difftime(tEndTm,p->tStartTm);
				if( fWrk > p->fTmOutVal ) {
					p->iSndAgainReq = 0;
					if( (p->cStatus == STAT_SND_WAIT) || (p->cStatus == STAT_SND_WAIT2) ) {
						if( p->fTmOutVal == TM_WAIT_10 ) {
							memset( p->aSndAgainBuf,0,sizeof(p->aSndAgainBuf) );
							memcpy( p->aSndAgainBuf,p->aSndAllMsgBuf,sizeof(p->aSndAgainBuf) );
							MakeSndData(p,ENQ);
							SndData(p);
							SetTimer( p, STAT_SND_WAIT, TM_WAIT_15 );

							return;
						} else {
							MakeSndData(p,EOT);
						}
						SndData(p);
					}
					p->fTmOutVal = 0;
					p->cStatus = STAT_IDLE;
#ifdef _DEBUG_
					printf( "idle" );
#endif
				}
			}

			if( (p->iSndAgainReq == 0) && (p->aSndAgainBuf[0] != 0) && (p->cStatus == STAT_IDLE) ) {
				MakeSndData(p,ENQ);
				SndData(p);
				SetTimer( p, STAT_SND_WAIT, TM_WAIT_15 );
			}
		}
		return;
	}

	switch( p->cStatus ) {
	case STAT_IDLE:
#ifdef _DEBUG_
		printf("idle���\n");
#endif
		if( p->cRcvFrameCtrlChar == ENQ ) {
			p->iSndAgainReq = 0;
			MakeSndData(p,ACK);
			SetTimer( p, STAT_RCV_WAIT, TM_WAIT_30 );
		}
		break;
	case STAT_RCV_WAIT:
#ifdef _DEBUG_
		printf("Receive Waiting���\n");
#endif
		if( p->cRcvFrameCtrlChar == STX ) {
			if( p->cChkRcvData == RCV_DATA_OK ) {
				if( p->cChkRcvMessage == MESSAGE_ERR ) {
					MakeSndData(p,EOT);
					p->fTmOutVal = 0;
					p->cStatus = STAT_IDLE;
				} else {
					MakeSndData(p,ACK);
					SetTimer( p, STAT_RCV_WAIT, TM_WAIT_30 );
				}
			} else if( p->cChkRcvData == RCV_DATA_NG ) {
				MakeSndData(p,NAK);
				SetTimer( p, STAT_RCV_WAIT, TM_WAIT_30 );
			}
		} else if( p->cRcvFrameCtrlChar == EOT ) {
			if( p->iRcvMsg == MSG_ORDER ) {
				MakeSndData(p,ENQ);
				SetTimer( p, STAT_SND_WAIT, TM_WAIT_15 );
			} else if( p->iRcvMsg == MSG_RESULT ) {
				MakeSndData(p,ENQ);
				SetTimer( p, STAT_SND_WAIT, TM_WAIT_15 );
			} else {
				p->cStatus = STAT_IDLE;
			}
		} else {
			sFncSyslog ( TRCKIND_ERROR, "StatusCtrl()", "STAT_RCV_WAIT���ɒʐM�G���[���������܂����B" ) ;
			printf(" STAT_RCV_WAIT���ʐM�G���[���������܂����B\n" );
		}
		break;
	case STAT_SND_WAIT:
#ifdef _DEBUG_
		printf("Send Waiting���\n");
#endif
		if( p->cRcvFrameCtrlChar == ACK ) {
			p->iSndRetryCnt = 0;
			MakeSndData(p,STX);
			SetTimer( p, STAT_SND_WAIT2, TM_WAIT_15 );
		} else if( p->cRcvFrameCtrlChar == ENQ ) {
			p->iSndAgainReq = 1;
			memset( p->aSndAgainBuf,0,sizeof(p->aSndAgainBuf) );
			memcpy( p->aSndAgainBuf,p->aSndAllMsgBuf,sizeof(p->aSndAgainBuf) );
			p->fTmOutVal = TM_WAIT_30;
			p->cStatus = STAT_IDLE;
		} else if( p->cRcvFrameCtrlChar == NAK ) {
			SetTimer( p, STAT_SND_WAIT, TM_WAIT_10 );
		} else if( p->cRcvFrameCtrlChar == EOT ) {
			p->cStatus = STAT_IDLE;
		} else {
			sFncSyslog ( TRCKIND_ERROR, "StatusCtrl()", "STAT_SND_WAIT���ɒʐM�G���[���������܂����B" ) ;
			printf(" STAT_SND_WAIT���ɒʐM�G���[���������܂����B\n" );
		}

		break;
	case STAT_SND_WAIT2:
#ifdef _DEBUG_
		printf("Send Waiting2���\n");
#endif
		if( p->cRcvFrameCtrlChar == ACK ) {
			p->iSndRetryCnt = 0;																		/* �t���[�����M���g���C�J�E���^ */
			if( p->cChkNextFrame == FRAME_END ) {
				MakeSndData(p,EOT);
				p->cStatus = STAT_IDLE;
				p->fTmOutVal = 0;
			} else {
				MakeSndData(p,STX);
				SetTimer( p, STAT_SND_WAIT2, TM_WAIT_15 );
			}
		} else if( p->cRcvFrameCtrlChar == NAK ) {
			if( ++(p->iSndRetryCnt) > 6 ) {
				MakeSndData(p,EOT);
				p->cStatus = STAT_IDLE;
				p->fTmOutVal = 0;
			} else {
				printf( "NAK->���g���C���M!!\n" );
				MakeSndData(p,STX);
				SetTimer( p, STAT_SND_WAIT2, TM_WAIT_15 );
			}
		} else if( p->cRcvFrameCtrlChar == EOT ) {
			MakeSndData(p,EOT);
			SetTimer( p, STAT_IDLE, TM_WAIT_15 );
		} else {
			sFncSyslog ( TRCKIND_ERROR, "StatusCtrl()", "STAT_SND_WAIT2���ɒʐM�G���[���������܂����B" ) ;
			printf(" STAT_SND_WAIT2���ɒʐM�G���[���������܂����B\n" );
		}
		break;
	default:
		break;
	}
	p->cRcvFrameCtrlChar = 0xff;
}
/**********************************************************************/
/*                                                                    */
/*   function name : SetTimer                                         */
/*                                                                    */
/*   purpose : �^�C�}�ݒ菈��                                         */
/*                                                                    */
/*   data : 2006.01.16                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
void SetTimer( SOCKET_INF* p, char cStatus, float fTime )
{
	char aFunc[32];

#ifdef _DEBUG_
	printf("%sSetTimber\n", Now());
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

	p->cStatus = cStatus;
	p->fTmOutVal = fTime;
	p->tStartTm = time(NULL);
}
/**********************************************************************/
/*                                                                    */
/*   function name : ClearSndInf                                      */
/*                                                                    */
/*   purpose : ���M���N���A����                                     */
/*                                                                    */
/*   data : 2006.01.16                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
void ClearSndInf( SOCKET_INF* p )
{
	char aFunc[32];

#ifdef _DEBUG_
	printf("%sClearSndInf\n", Now());
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

	p->iSndRetryCnt = 0;																/* �t���[�����M���g���C�J�E���^ */
	p->cFrameNum = 0;
	p->cSndFrameSeqNum = 0;
	p->cChkNextFrame = FRAME_END;
	memset(p->aSndAllMsgBuf,0,sizeof(p->aSndAllMsgBuf));			/* �S���M���b�Z�[�W�o�b�t�@�N���A */
}

/**********************************************************************/
/*                                                                    */
/*   function name : MakeSndData                                      */
/*                                                                    */
/*   purpose : ���M�f�[�^�쐬����                                     */
/*                                                                    */
/*   data : 2005.12.15                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
void MakeSndData(SOCKET_INF* p,char cSnd)
{

	char cWrk;
	char aSndWrk[1700];
	char c1;
	char c2;
	int iCnt;
	int iCnt2;
	int iLen;
	int iWrk;
	int iWrk2;
	char *aWrkBuf;
	char aWrk2[10];
	char snditem[32];
	char cNbkmkcd[8];
	int reqnum;
	int order;
	char	aSndMsgHeaderRcd[110];	/* ���o�����R�[�h�G���A */
	char	aSndPatientInfRcd[40];	/* ���ҏ�񃌃R�[�h�G���A */
	char	aSndTestOrderRcd[1500];	/* ���ڑI�����R�[�h�G���A */
	char	aSndC_CMMRcd[130];		/* ���߃��R�[�h(�R�����g)�G���A */
	char	aSndMsgEndRcd[10];		/* ���b�Z�[�W�I���R�[�h�G���A */
	char	kntno[14];
	char aFunc[32];
	
		int idxKmkmst ;
	char ksjhflg ;
	int nyubiOrderFlg ;		/* ���n�����t�I�[�_�쐬�ς݃t���O */


	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sMakeSndData\n", Now());
#endif

	iCnt = 0;
	cWrk = 0;
	iLen = 0;
	nyubiOrderFlg = 0 ;
	if( pKenorder != NULL ) {
		free( pKenorder );
		pKenorder = NULL;
	}
	reqnum = 0;
	order = 0;
	memset( kntno,0,sizeof(kntno) );
	aWrkBuf = NULL;

	p->cSndFrameCtrlChar = cSnd;
	if( cSnd == ENQ ) {
		ClearSndInf(p);
		memset(aSndMsgHeaderRcd,0,sizeof(aSndMsgHeaderRcd));	/* ���o�����R�[�h�G���A */
		memset(aSndPatientInfRcd,0,sizeof(aSndPatientInfRcd));	/* ���ҏ�񃌃R�[�h�G���A */
		memset(aSndTestOrderRcd,0,sizeof(aSndTestOrderRcd));	/* ���ڑI�����R�[�h�G���A */
		memset(aSndC_CMMRcd,0,sizeof(aSndC_CMMRcd));			/* ���߃��R�[�h(�R�����g)�G���A */
		memset(aSndMsgEndRcd,0,sizeof(aSndMsgEndRcd));			/* ���b�Z�[�W�I���R�[�h�G���A */

		if( (p->iRcvMsg == MSG_NON) && (p->aSndAgainBuf[0] != 0) ) {
#ifdef _DEBUG_
			printf( "�����N�R���e���V�����I\n" );
#endif

			p->iSndAgainReq = 0;
			memcpy( p->aSndAllMsgBuf,p->aSndAgainBuf,sizeof(p->aSndAllMsgBuf) );
			memset( p->aSndAgainBuf,0,sizeof(p->aSndAgainBuf) );
		} else if( (p->iRcvMsg == MSG_ORDER) || (p->iRcvMsg == MSG_RESULT) ) {

			/* �����I�[�_�[(.dat)�t�@�C���ǂݍ��� */
			iWrk = GetKenorder( p,ORDER_DAT_1,&reqnum );
			if( iWrk != RTN_OK ) {
				iWrk = GetKenorder( p,ORDER_DAT_2,&reqnum );
			}
			if( pKenorder != NULL ) {
				if( p->iRcvMsg == MSG_ORDER ) {
					iCnt2 = 0;
					for( iCnt=0; iCnt<reqnum; iCnt++ ) {
						/* ���ڃR�[�h�擾 */
						if( GetNbkmkcd( pKenorder[iCnt].kmkcd,cNbkmkcd ) == RTN_OK ) {
							++order;
							iLen = R_trim( cNbkmkcd );
							strncpy( p->sSndorder.kmkcd[iCnt2],cNbkmkcd,iLen );
							/* �\���ߔ{���擾 */
/* [ start 068/069 */
							if( pKenorder[iCnt].ytiksbr[0] == 'Y' ) {
								memset( p->sSndorder.ytiksbr[iCnt2],0,sizeof(p->sSndorder.ytiksbr[0]) );
							}
							else if (( pKenorder[iCnt].ytiksbr[1] == '0' ) && ( pKenorder[iCnt].ytiksbr[2] == 'D' ) ) {
								strcpy( p->sSndorder.ytiksbr[iCnt2],"Dec" );
							}
							else {
								iWrk2 = atoi(&pKenorder[iCnt].ytiksbr[1]);
								if( iWrk2 == aKskbrt[0] ) {
									strcpy( p->sSndorder.ytiksbr[iCnt2],"3" );
								} else if( iWrk2 == aKskbrt[1] ) {
									strcpy( p->sSndorder.ytiksbr[iCnt2],"5" );
								} else if( iWrk2 == aKskbrt[2] ) {
									strcpy( p->sSndorder.ytiksbr[iCnt2],"10" );
								} else if( iWrk2 == aKskbrt[3] ) {
									strcpy( p->sSndorder.ytiksbr[iCnt2],"20" );
								} else if( iWrk2 == aKskbrt[4] ) {
									strcpy( p->sSndorder.ytiksbr[iCnt2],"50" );
								} else {
									memset( p->sSndorder.ytiksbr[iCnt2],0,sizeof(p->sSndorder.ytiksbr[0]) );
								}
							}
/* ] end 068/069 */
							++iCnt2;
							
							/* ���їn�����t�I�[�_�쐬 */
							if ( nyubiOrderFlg == 0 ) {
/** HAGA **/
/* h_loging ( "���їn�����t�I�[�_�쐬 : ���� knsgrp[%s] kmkcd[%s]\n", pKenorder[iCnt].knsgrp, pKenorder[iCnt].kmkcd ) ; */
								ksjhflg =  '\0' ;
								for ( idxKmkmst = 0 ; idxKmkmst < iKmkmstNum ; idxKmkmst++ ) {
									if ( memcmp ( pKmkmst[idxKmkmst].knsgrp, pKenorder[iCnt].knsgrp, sizeof ( char ) * 16 ) == 0 && 
								     	     memcmp ( pKmkmst[idxKmkmst].kmkcd, pKenorder[iCnt].kmkcd, sizeof ( char ) * 7 ) == 0 ) {
										ksjhflg = pKmkmst[idxKmkmst].ksjhflg ; 
										break ;
									}
								}
								if ( ksjhflg == '1' ) {
/* h_loging ( "���їn�����t�I�[�_�쐬 : �쐬\n" ) ; */
									++order;
									strncpy( p->sSndorder.kmkcd[iCnt2],"102",3 );
									memset( p->sSndorder.ytiksbr[iCnt2],0,sizeof(p->sSndorder.ytiksbr[0]) );
									iCnt2++ ;
	
									++order;
									strncpy( p->sSndorder.kmkcd[iCnt2],"103",3 );
									memset( p->sSndorder.ytiksbr[iCnt2],0,sizeof(p->sSndorder.ytiksbr[0]) );
									iCnt2++ ;
	
									++order;
									strncpy( p->sSndorder.kmkcd[iCnt2],"104",3 );
									memset( p->sSndorder.ytiksbr[iCnt2],0,sizeof(p->sSndorder.ytiksbr[0]) );
									iCnt2++ ;
									nyubiOrderFlg = 1 ;	/* �쐬�ς� */
								} else {
/* h_loging ( "���їn�����t�I�[�_�쐬 : �쐬���Ȃ�\n" ) ; */
								}
							}

						} else {
						}
					}
					p->iOrderNum = order;
				}
				/* ����No�擾 */
				strcpy( kntno,pKenorder[0].kntno );
				CnvtFromKntno(kntno,p->sSndorder.kntno);
				/* �ޗ��R�[�h�擾 */
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
/*** �ޗ��R�[�h���K�v�Ȃ̂ŕ��� ***/
				strcpy( p->sSndorder.zrcd,pKenorder[0].zrcd );
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */
				/* ���ʋ敪�擾 */
				p->sSndorder.sbtkbn[0] = pKenorder[0].sbtkbn;
				/* �N��擾 */
				strcpy( p->sSndorder.age,pKenorder[0].age );
				/* �N��敪�擾 */
				p->sSndorder.agekbn[0] = pKenorder[0].agekbn;
				/* �̎掞�Ԏ擾 */
				strcpy( p->sSndorder.sstme,pKenorder[0].sstme );
				/* �̎�N�����擾 */
				strcpy( p->sSndorder.ssymd,pKenorder[0].ssymd );

				if( pKenorder != NULL ) {
					free( pKenorder );
					pKenorder = NULL;
				}

			} else {
				sFncSyslog ( TRCKIND_ERROR, "MakeSndData()", "�I�[�_�[�t�@�C��������܂���B" ) ;
			}
			p->iRcvMsg = MSG_NON;
			strcpy(aSndMsgHeaderRcd,"H|\\^&|||host^1|||||LST008|TSDWN^REPLY|P|1");
			strcpy(aSndTestOrderRcd,"O|1");
			strcat(aSndTestOrderRcd,"|                      |");
			strncpy(&aSndTestOrderRcd[4],p->sSndorder.kntno,strlen(p->sSndorder.kntno));
			memset( aWrk2,0,10 );
			sprintf( aWrk2,"%d",p->sSndorder.bskseq );
			iLen = strlen( aWrk2 );
			strncat( aSndTestOrderRcd, aWrk2, iLen );
			strcat(aSndTestOrderRcd,"^");
			strncat(aSndTestOrderRcd,p->cRackNum,5);
			iLen = strlen( aSndTestOrderRcd );
			aSndTestOrderRcd[iLen] = '^';
			aSndTestOrderRcd[iLen+1] = p->cRackPosNum[0];
			strcat(aSndTestOrderRcd,"^^");
			iLen = strlen( p->sSndorder.racktype );
			strncat( aSndTestOrderRcd,p->sSndorder.racktype,iLen );
			strcat(aSndTestOrderRcd,"^SC|");

			if( iWrk == 0 ) {
				for( iCnt=0; iCnt<p->iOrderNum; iCnt++ ) {
					/* �������ڃR�[�h���Ȃ��ꍇ�͖��� */
					if( strlen( p->sSndorder.kmkcd[iCnt]) == 0 ) {
						continue;
					}
					//
					if( iCnt == 0 ) {
						strcat( aSndTestOrderRcd,"^^^" );
					} else {
						strcat( aSndTestOrderRcd,"\\^^^" );
					}
					/* ���ڔԍ��ݒ� */
					memset( snditem,0,sizeof(snditem) );
					iLen = strlen( p->sSndorder.kmkcd[iCnt] );
					strncat( aSndTestOrderRcd,p->sSndorder.kmkcd[iCnt],iLen );
					iLen = strlen( aSndTestOrderRcd );
					aSndTestOrderRcd[iLen] = '^';
					/* �˗����ݒ� */
					strcat( aSndTestOrderRcd,p->sSndorder.ytiksbr[iCnt] );
				}
			}
			strcat( aSndTestOrderRcd,"|R||" );
			iLen = strlen( aSndTestOrderRcd );
			/* �̌���(�N����)�ݒ�͂��Ȃ� */

/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
/*** ���̎�ʐݒ� 1���ݒ肳��Ă��镔�����ޗ��R�[�h�ɍ��킹�ĕҏW ***/
			strcat( aSndTestOrderRcd,"||||A||||" );
			char wkKntsbt[2];
			memset(wkKntsbt, 0, 2);
			CnvtFromZrcd(p->sSndorder.zrcd, wkKntsbt);
			strcat( aSndTestOrderRcd,wkKntsbt );
			strcat( aSndTestOrderRcd,"||||||||||O" );
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */

			/* ���ҏ�� */
			strcpy(aSndPatientInfRcd,"P|1|||");
			strcat(aSndPatientInfRcd,"||||");
			/* ���ʐݒ�*/
			memset( snditem,0,sizeof(snditem) );
			CnvtFromSbtkbn( p->sSndorder.sbtkbn,snditem );
			strncat( aSndPatientInfRcd,snditem,1 );
			strcat( aSndPatientInfRcd,"||||||" );
			/* �N��ݒ�*/
			/* �N��敪�ݒ�*/
			/* �N��ݒ�*/
			/* DEL 2006.12.18 Nagata �N���d����ɏ悹�Ȃ� */
			/* �N��敪�ݒ�*/
			/* DEL 2006.12.18 Nagata �N��敪��d����ɏ悹�Ȃ� */
			strcpy(aSndC_CMMRcd,"C|1");
			strcat(aSndC_CMMRcd,"|I|^^^^|G");
			strcpy(aSndMsgEndRcd,"L|1|N");
			iLen = strlen(aSndMsgHeaderRcd);
			strncat(p->aSndAllMsgBuf,aSndMsgHeaderRcd,iLen);
			iLen = strlen(p->aSndAllMsgBuf);
			p->aSndAllMsgBuf[iLen] = CR;
			iLen = strlen(aSndPatientInfRcd);
			strncat(p->aSndAllMsgBuf,aSndPatientInfRcd,iLen);
			iLen = strlen(p->aSndAllMsgBuf);
			p->aSndAllMsgBuf[iLen] = CR;
			iLen = strlen(aSndTestOrderRcd);
			strncat(p->aSndAllMsgBuf,aSndTestOrderRcd,iLen);
			iLen = strlen(p->aSndAllMsgBuf);
			p->aSndAllMsgBuf[iLen] = CR;
			iLen = strlen(aSndC_CMMRcd);
			strncat(p->aSndAllMsgBuf,aSndC_CMMRcd,iLen);
			iLen = strlen(p->aSndAllMsgBuf);
			p->aSndAllMsgBuf[iLen] = CR;
			iLen = strlen(aSndMsgEndRcd);
			strncat(p->aSndAllMsgBuf,aSndMsgEndRcd,iLen);
			iLen = strlen(p->aSndAllMsgBuf);
			p->aSndAllMsgBuf[iLen] = CR;

			if( p->aSndAgainBuf[0] != 0 ) {
				memset(aSndWrk,0,sizeof(aSndWrk));
				memcpy(aSndWrk,p->aSndAllMsgBuf,sizeof(aSndWrk));
				memset(p->aSndAllMsgBuf,0,sizeof(p->aSndAllMsgBuf));
				memcpy(p->aSndAllMsgBuf,p->aSndAgainBuf,sizeof(p->aSndAllMsgBuf));
				memset(p->aSndAgainBuf,0,sizeof(p->aSndAgainBuf));
				memcpy(p->aSndAgainBuf,aSndWrk,sizeof(p->aSndAgainBuf));
			}
		}
	} else if( cSnd == STX ) {
		if( p->iSndRetryCnt != 0 ) {
			p->cSndDataReq = SND_REQ;
			return;
		}
		aWrkBuf = malloc(sizeof(char)*1700);
		memset( aWrkBuf, 0, 1700 );
		memset(p->aSndTmpBuf,0,sizeof(p->aSndTmpBuf));				/* ���M�f�[�^�ꎞ�o�b�t�@�N���A */
		if( p->cChkNextFrame == FRAME_END ) {
			p->cFrameNum = 1;
			p->cSndFrameSeqNum = 1;
			p->iSndRetryCnt = 0;
		} else {
			if( (++p->cFrameNum) >= 8 ) {
				p->cFrameNum -= 8;
			}
			++p->cSndFrameSeqNum;
		}
#ifdef _DEBUG_
		printf("���M�f�[�^�쐬\n");
#endif
		aWrkBuf[0] = (p->cFrameNum%8)+0x30;
		strcat( aWrkBuf, &(p->aSndAllMsgBuf[239*(p->cSndFrameSeqNum-1)]) );

		iLen = strlen( aWrkBuf );

		if( iLen > 240 ) {
			iLen = 240;
			strncpy( p->aSndTmpBuf, aWrkBuf, iLen );
			p->cChkNextFrame = FRAME_CONTINUE;
			p->aSndTmpBuf[iLen] = ETB;
		} else {
			strncpy( p->aSndTmpBuf, aWrkBuf, iLen );
			p->cChkNextFrame = FRAME_END;
			p->cSndFrameSeqNum = 1;
			p->aSndTmpBuf[iLen] = ETX;
		}
		for( iCnt=0; iCnt<(iLen+1); iCnt++ ) {
			cWrk += p->aSndTmpBuf[iCnt];
		}
		c1 = ((cWrk >> 4) & 0x0f);
		if( c1 <= 0x09 ) {
			c1 += 0x30;
		} else {
			c1 += 0x37;
		}
		c2 = (cWrk & 0x0f);
		if( c2 <= 0x09 ) {
			c2 += 0x30;
		} else {
			c2 += 0x37;
		}
		p->aSndTmpBuf[++iLen] = c1;
		p->aSndTmpBuf[++iLen] = c2;
		p->aSndTmpBuf[++iLen] = CR;
		p->aSndTmpBuf[++iLen] = LF;
	}
	p->cSndDataReq = SND_REQ;

	if (aWrkBuf != NULL) {
		free( aWrkBuf );
	}

	return;
}
/**********************************************************************/
/*                                                                    */
/*   function name : ClrSaikenInf                                     */
/*                                                                    */
/*   purpose : �Č���񏉊�������                                     */
/*                                                                    */
/*   data : 2006.03.13                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
void ClrSaikenInf( SOCKET_INF* p )
{
#ifdef _DEBUG_
	printf("%sClrSaikenInf\n", Now());
#endif
	if( p->pSaiken != NULL ) {
		free(p->pSaiken);
		p->pSaiken = NULL;
	}
	if( p->pKekka != NULL ) {
		free(p->pKekka);
		p->pKekka = NULL;
	}
	p->iKekkaNum = 0;
	p->iKekkaCnt = 0;
}
/**********************************************************************/
/*                                                                    */
/*   function name : R_trim                                           */
/*                                                                    */
/*   purpose : .���ڃR�[�h�擾����                                    */
/*                                                                    */
/*   data : 2006.03.01                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int R_trim( char* cWrk )
{
	int iCnt;
	int iLen;
	int iLen2;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "R_trim()\n" );
#endif

	iLen = strlen( cWrk );
	iLen2 = 0;

	for( iCnt=0; iCnt<iLen; iCnt++ ) {
		if( cWrk[iCnt] != ' ' ) {
			++iLen2;
		} else {
			break;
		}
	}
	return iLen2;
}
/**********************************************************************/
/*                                                                    */
/*   function name : CnvtFromKmkcd                                    */
/*                                                                    */
/*   purpose : .���ڃR�[�h�ϊ�����                                    */
/*                                                                    */
/*   data : 2006.02.10                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int CnvtFromKmkcd( char* cFrom, char* cTo )
{
	int iCnt2;
	int iCnt3;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "%sCnvtFromKmkcd()\n", Now());
#endif

	for( iCnt2=0,iCnt3=0; cFrom[iCnt2]!='\0'; iCnt2++ ) {
		if( cFrom[iCnt2] != ' ' ) {
			cTo[iCnt3] = cFrom[iCnt2];
			++iCnt3;
		}
	}
	return 0;
}

/**********************************************************************/
/*                                                                    */
/*   function name : CnvtFromZrcd                                     */
/*                                                                    */
/*   purpose : .�ޗ��R�[�h�ϊ�����                                    */
/*                                                                    */
/*   data : 2006.02.10                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int CnvtFromZrcd( char* cFrom, char* cTo )
{
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "%sCnvtFromZrcd()\n", Now());
#endif

	if((memcmp(cFrom, aHnkCd[1], strlen(aHnkCd[1])) == 0) ||
	   (memcmp(cFrom, aHnkCd[2], strlen(aHnkCd[2])) == 0)) {
#ifdef _DEBUG_
		printf("CnvtFromZrcd : �A���[�h(%s)\n", cFrom);
#endif
		/* �A���̂��������[�h�ő��肷��悤�ɕύX */
		cTo[0] = '1';
		/* cTo[0] = '2'; */
	} else {
		cTo[0] = '1';
	}

	return 0;
}

/**********************************************************************/
/*                                                                    */
/*   function name : CnvtFromYtiksb                                   */
/*                                                                    */
/*   purpose : .�\���ߔ{���ϊ�����                                  */
/*                                                                    */
/*   data : 2006.02.10                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int CnvtFromYtiksbr( char* cFrom, char* cTo )
{
	int iCnt2;
	int iCnt3;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "%sCnvtFromYtiksbr()\n", Now());
#endif

	for( iCnt2=0,iCnt3=0; cFrom[iCnt2]!='\0'; iCnt2++ ) {
		if( cFrom[iCnt2] != ' ' ) {
			cTo[iCnt3] = cFrom[iCnt2];
			++iCnt3;
		}
	}
	return 0;
}

/**********************************************************************/
/*                                                                    */
/*   function name : CnvtFromSbtkbn                                   */
/*                                                                    */
/*   purpose : .���ʋ敪�ϊ�����                                      */
/*                                                                    */
/*   data : 2006.02.10                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int CnvtFromSbtkbn( char* cFrom, char* cTo )
{
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "%sCnvtFromSbtkbn()\n", Now());
#endif

	if( cFrom[0] == '0' ) {
		cTo[0] = 'M';
	} else if( cFrom[0] == '1' ) {
		cTo[0] = 'F';
	} else {
		cTo[0] = 'U';
	}
	return 0;
}

/**********************************************************************/
/*                                                                    */
/*   function name : CnvtFromAge                                      */
/*                                                                    */
/*   purpose : .�N��ϊ�����                                          */
/*                                                                    */
/*   data : 2006.02.10                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int CnvtFromAge( char* cFrom, char* cTo )
{
	int iCnt2;
	int iCnt3;
	char cWrk[16];
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "%sCnvtFromAge()\n", Now());
#endif

	memset( cWrk,0,sizeof(cWrk) );

	for( iCnt2=0,iCnt3=0; cFrom[iCnt2]!='\0'; iCnt2++ ) {
		if( cFrom[iCnt2] != ' ' ) {
			cWrk[iCnt3] = cFrom[iCnt2];
			++iCnt3;
		}
	}
	iCnt2 = strlen(cWrk);
	if( iCnt2 == 3 ) {
		strcat( cTo,cWrk );
	} else if( iCnt2 == 2 ) {
		cTo[0] = cWrk[0];
		cTo[1] = cWrk[1];
	} else if( iCnt2 == 1 ) {
		cTo[0] = cWrk[0];
	} else {
	}
	return 0;
}

/**********************************************************************/
/*                                                                    */
/*   function name : CnvtFromAgekbn                                   */
/*                                                                    */
/*   purpose : .�N��敪�ϊ�����                                      */
/*                                                                    */
/*   data : 2006.02.10                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int CnvtFromAgekbn( char* cFrom, char* cTo )
{
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "%sCnvtFromAgekbn()\n", Now());
#endif

	if( cFrom[0] == 'Y' ) {
		cTo[0] = 'Y';
	} else if( cFrom[0] == 'M' ) {
		cTo[0] = 'M';
	} else if( cFrom[0] == 'D' ) {
		cTo[0] = 'D';
	} else {
	}
	return 0;
}

/**********************************************************************/
/*                                                                    */
/*   function name : CnvtFromSstme                                    */
/*                                                                    */
/*   purpose : .�̎掞�ԕϊ�����                                      */
/*                                                                    */
/*   data : 2006.02.10                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int CnvtFromSstme( char* cFrom, char* cTo )
{
	int iCnt;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "%sCnvtFromSstme()\n", Now());
#endif

	iCnt = 0;

	cTo[iCnt] = cFrom[0];
	cTo[++iCnt] = cFrom[1];
	cTo[++iCnt] = cFrom[3];
	cTo[++iCnt] = cFrom[4];
	cTo[++iCnt] = cFrom[6];
	cTo[++iCnt] = cFrom[7];

	return 0;
}

/**********************************************************************/
/*                                                                    */
/*   function name : CnvtFromSsymd                                    */
/*                                                                    */
/*   purpose : .�̎�N�����ϊ�����                                    */
/*                                                                    */
/*   data : 2006.02.10                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int CnvtFromSsymd( char* cFrom, char* cTo )
{
	int iCnt;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "%sCnvtFromSsymd()\n", Now());
#endif

	if( strncmp(cFrom,INIT_DATE,10) == 0 || strlen(cFrom) != 10 ) {
		return RTN_NG;
	}

	iCnt = 0;
	cTo[iCnt] = cFrom[0];
	cTo[++iCnt] = cFrom[1];
	cTo[++iCnt] = cFrom[2];
	cTo[++iCnt] = cFrom[3];
	cTo[++iCnt] = cFrom[5];
	cTo[++iCnt] = cFrom[6];
	cTo[++iCnt] = cFrom[8];
	cTo[++iCnt] = cFrom[9];

	return RTN_OK;
}
/**********************************************************************/
/*                                                                    */
/*   function name : CnvtFromKntno                                    */
/*                                                                    */
/*   purpose : .����No�ϊ�����                                        */
/*                                                                    */
/*   data : 2006.03.22                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int CnvtFromKntno( char* cFrom,char* cTo )
{
	int iLen;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "%sCnvtFromKntno()\n", Now());
#endif

	memset( cTo,0,14 );

	if( pKenorder[0].kntketflg == '9' ) {
		iLen = 9;
	} else if( pKenorder[0].kntketflg == '7' ) {
		iLen = 7;
		cFrom[0] = '*';
                cFrom[1] = '*';
	} else if( pKenorder[0].kntketflg == '6' ) {
		iLen = 6;
		cFrom[0] = '*';
		cFrom[1] = '*';
	} else {
		iLen = 13;
		cFrom[0] = '*';
		cFrom[1] = '*';
	}
	strncpy( cTo,cFrom,iLen );

	return RTN_OK;
}
/**********************************************************************/
/*                                                                    */
/*   function name : CnvtFromKjnsriymd                                */
/*                                                                    */
/*   purpose : ����ϊ�����                                         */
/*                                                                    */
/*   data : 2006.05.17                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int CnvtFromKjnsriymd( char* cFrom, char* cTo )
{
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "%sCnvtFromKjnsriymd()\n", Now());
#endif

	cTo[0] = cFrom[0];
	cTo[1] = cFrom[1];
	cTo[2] = cFrom[2];
	cTo[3] = cFrom[3];
	cTo[4] = '-';
	cTo[5] = cFrom[4];
	cTo[6] = cFrom[5];
	cTo[7] = '-';
	cTo[8] = cFrom[6];
	cTo[9] = cFrom[7];

	return RTN_OK;
}

/**********************************************************************/
/*                                                                    */
/*   function name : GetNowCtrlNo                                     */
/*                                                                    */
/*   purpose : �R���g���[���ԍ��擾����                               */
/*                                                                    */
/*   data : 2006.01.23                                                */
/*                                                                    */
/*   produce : S.Tsunekawa                                            */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int GetNowCtrlNo(SOCKET_INF *p, int Seq, char * knsTime)
{
	int lCnt;
	struct tm sTm;
	time_t t_Kns;
	
#ifdef _DEBUG_
	printf("%sGetNowCtrlNo\n", Now());
#endif
	memset(&sTm, 0, sizeof(sTm));
	sTm.tm_sec = (knsTime[12]-'0') * 10 + (knsTime[13]-'0');		/* Seconds. 	[0-60] (1 leap second) */
	sTm.tm_min = (knsTime[10]-'0') * 10 + (knsTime[11]-'0');		/* Minutes. 	[0-59] */
	sTm.tm_hour = (knsTime[8]-'0') * 10 + (knsTime[9]-'0');			/* Hours.		[0-23] */
	sTm.tm_mday = (knsTime[6]-'0') * 10 + (knsTime[7]-'0');			/* Day. 		[1-31] */
	sTm.tm_mon = (knsTime[4]-'0') * 10 + (knsTime[5]-'0') - 1;		/* Month.		[0-11] */
	sTm.tm_year = ((knsTime[0]-'0') * 1000 + (knsTime[1]-'0') * 100
				 + (knsTime[2]-'0') * 10 + (knsTime[3]-'0')) - 1900; /* Year - 1900.  */
	sTm.tm_wday = 0;				/* Day of week. [0-6] */
	sTm.tm_yday = 0;				/* Days in year.[0-365] */
	sTm.tm_isdst = 0; 				/* DST. 		[-1/0/1]*/
	
	/* �������Ԃ��o�C�i���ɕϊ� */
	t_Kns = mktime(&sTm);
	
	/* �Ǘ���񂩂�R���g���[��SEQ�Ǝ��Ԃ����ɃR���g���[���ԍ���T���B */
	for (lCnt = 0; lCnt < p->CtrlInfo.cnt; lCnt ++) {
		if ((p->CtrlInfo.Bunseki_Seq[lCnt] == Seq) &&
			(fabs(difftime(p->CtrlInfo.KnsTime[lCnt], t_Kns)) < (gCTRL_CHK_TIME * 60.0))) {
			break;
		}
	}
	if (lCnt >= p->CtrlInfo.cnt) {
		/* �܂��o�^����Ă��Ȃ� */
		lCnt = p->CtrlInfo.cnt;
		
		p->CtrlInfo.Ctrl_no[lCnt] = p->iCtrlSeqCnt + 1;
		p->CtrlInfo.Bunseki_Seq[lCnt] = Seq;
		p->CtrlInfo.KnsTime[lCnt] = t_Kns;
		p->iCtrlSeqCnt++;

		p->iCtrlSeq = Seq;
		OutputCtrlSeq(p);
		
		p->CtrlInfo.cnt++;
	}
	return p->CtrlInfo.Ctrl_no[lCnt];
}
/**********************************************************************/
/*                                                                    */
/*   function name : MakeFileName                                     */
/*                                                                    */
/*   purpose : .�t�@�C�����쐬����                                    */
/*                                                                    */
/*   data : 2006.01.23                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int MakeFileName( char* aRackNum, char* aPosNum, int mFlg )
{
	int iCnt;
	int iLen;
	char aFunc[32];
	time_t id;
	char idstr[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "%sMakeFileName()\n", Now());
#endif

	memset( aFileNameStr, 0, sizeof(aFileNameStr) );

#ifdef _DEBUG_
	printf( "���b�NID:%s\n",aRackNum );
	printf( "���b�N�ʒu:%s\n",aPosNum );
#endif

	/* ADD  2006-08-31 Nagata �t�@�C�������̃X�^���v�̌����𑝂₷ */
	id = time(0L);
	sprintf(idstr, "_%012ld", id);

	iLen = strlen( aRackNum );
	strncpy( aFileNameStr,aRackNum,iLen );
	for( iCnt=iLen; iCnt<10; iCnt++ ) {
		aFileNameStr[iCnt] = '_';
	}
	strncat( &aFileNameStr[10],"000",3 );
	iLen = strlen( aPosNum );
	if( iLen >= 3 ) {
		strncpy( &aFileNameStr[10],aPosNum,3 );
	} else if( iLen == 2 ) {
		strcpy( &aFileNameStr[11],aPosNum );
	} else if( iLen == 1 ) {
		strcpy( &aFileNameStr[12],aPosNum );
	}
	if ( mFlg == 1 ) {
		strcat( aFileNameStr, idstr );
	}
	strcat( aFileNameStr,".dat" );

	return 0;
}

/******************************************************************************/
/*  �� �� ���@�FsFncSyslog()				 								  */
/*  �@�\�T�v�@�F�V�X�e�����O�o��							  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fint 			   	�v���C�I���e�B�[						  */
/*�@ ��Q���� �Fchar *   			�֐���									  */
/*�@ ��R���� �Fchar * 		  		���b�Z�[�W								  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
 void
_sFncSyslog (LOG_TRCKIND piPri, char * pcFncname,char * pcMsg ,char * pcErrCode, char * pcExeFlg, char * file, long lineno) 
{
#if defined ( _SYSLOGOUT )
	if ( errno != 0 ) {
		syslog ( piPri, "Error: Function %s %s (errno=%d msg=%m)",
						pcFncname, pcMsg, errno ) ;
	} else {
		syslog ( piPri, "Error: Function %s %s (errno=%d)",
						pcFncname, pcMsg, errno ) ;
	}
#endif
#if defined ( _TRACE )
	if ( errno != 0 ) {
		fprintf ( stderr, "Error: Function %s %s (errno=%d msg=%s)\n",
							pcFncname, pcMsg, errno, strerror ( errno ) ) ;
	} else {
		fprintf ( stderr, "Error: Function %s %s (errno=%d)\n",
							pcFncname, pcMsg, errno ) ;
	}
#endif

	struct stcLogMember plm;
	
	memset(&plm, 0, sizeof(plm));
	plm.eTrcKind = piPri;				
	plm.lPid = getpid() ;					/* �v���Z�XID */
	strncpy(plm.pcAppName, "DD203", 32);
	strncpy(plm.pcSrcName, file, 32);
	strncpy(plm.pcFncName, pcFncname, 32);
	plm.lLineNo = lineno;
	strncpy(plm.pcExeFlg, pcExeFlg, 2);
	strncpy(plm.pcErrCode, pcErrCode, 8);
	strncpy(plm.pcMsg, pcMsg, 1024);

	_ZbmlPutLog(&plm, file, lineno);
}
/******************************************************************************/
/*  �� �� ���@�FsFncShmCrt()				 								  */
/*  �@�\�T�v�@�F���L����������								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����		 	      	  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
static int
sFncShmCrt ( shm_Key )
int		shm_Key;
{
	int		*shmData ;

	/* �擾 */
	shm_Id = shmget ( (key_t)shm_Key, 
							sizeof( int ), 
							0666 | IPC_CREAT ) ;
	if ( shm_Id < 0 ) {
		/* �ُ�I��	LOG */
		sFncSyslog ( TRCKIND_ERROR, "shmget()", "Cannot assign shared memory." ) ;
		return ( -1 ) ;
	}

	/* �A�^�b�` */
	shmData = ( int * ) shmat ( shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		/* �ُ�I��	LOG */
		sFncSyslog ( TRCKIND_ERROR, "shmat()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}

	/* �l�ݒ� */
	*shmData = 0 ;

	/* �f�^�b�`	 */
	if ( shmdt ( shmData ) == -1 ) {
		/* �ُ�I��	LOG */
		sFncSyslog ( TRCKIND_ERROR, "shmdt()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncShmGet()				 								  */
/*  �@�\�T�v�@�F���L�������擾								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����			 	      */
/*�@ ��Q���� �Fint *   			�l								 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
static int
sFncShmGet ( shm_Key, pshmData )
int				shm_Key ;
int				*pshmData ;
{
	int		*shmData ;

	/* �A�^�b�`	 */
	shmData = ( int * ) shmat ( shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		/* �ُ�I��	LOG */
		sFncSyslog ( TRCKIND_ERROR, "shmat()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}

	/* �l�ݒ� */
	*pshmData = *shmData ;

	/* �f�^�b�` */
	if ( shmdt ( shmData ) == -1 ) {
		/* �ُ�I��	LOG */
		sFncSyslog ( TRCKIND_ERROR, "shmdt()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncShmDel()				 								  */
/*  �@�\�T�v�@�F���L�������폜								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����			 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
static int
sFncShmDel ( shm_Key )
int			shm_Key ;
{
	/* �폜 */
	if ( shmctl ( shm_Id, IPC_RMID, NULL) < 0 ) {
		/*/ �ُ�I��	LOG */
		sFncSyslog ( TRCKIND_ERROR, "shmctl()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}	
/* �f�[�^�A���[���擾�����ǉ� 2006-07-13 E.Osada */
int
chkDataAlarm( SOCKET_INF *p )
{
    char    buf1[128], buf2[128]; /* ADD E.Osada 2006-07-13 */
    Kskbrmst    Key;
	int	iAlCode, iRet, KekkaCnt;

	p->iOrderNum = 0;
    memset(buf1, 0, sizeof(buf1));
    memset(buf2, 0, sizeof(buf2));
    memset(&Key, 0,sizeof(Kskbrmst));
    memcpy(Key.bskkbn, "LABO", 4);
	for( KekkaCnt=0; KekkaCnt < p->iKekkaNum ;++KekkaCnt ) {
    	memcpy(Key.knsgrp, p->pKekka[KekkaCnt].knsgrp, 16);
    	memcpy(Key.kmkcd,  p->pKekka[KekkaCnt].kmkcd, 7);
    	GetKskRitu(&Key, buf1, buf2);

		iAlCode = atoi(p->pKekka[KekkaCnt].bskerrsts);
		/* ADD 2006-09-20 Nagata �A���[���R�[�h 4 �� �p��Č� �� �����Č� */
		/* ADD 2006-12-18 Nagata �A���[���R�[�h 47 �����Č� */
		/* UPD 2007-04-10 Nagata �A���[���R�[�h 47 �����Č� �� �p��Č� */
		switch(iAlCode) {
			case 1:	/* �����Č� */
			case 2:	
			case 4:	
			case 10:
			case 11:
			case 18:
			case 19:
			case 23:
			case 24:
			case 25:
			case 26:
			case 27:
			case 37:
			case 38:
			case 39:
			case 40:
			case 41:
			case 42:
			case 43:
			case 44:
			case 45:
			case 59:
			case 60:
			case 73:
				iRet = 1;
				p->pSaiken[KekkaCnt].flg = 1;   /* �����Č� */
				p->pKekka[KekkaCnt].knsflg = 'A';
				/* CHG E.Osada 2006-09-19 */
				p->pKekka[KekkaCnt].yobiflg01 = '2';	/* �G���[�t���O ADD 2006.08.11 Hiwa */
				/* 2006-08-28 Nagata �����ł͓������ڂ��Z�b�g���Ȃ� */
				break;
			case 5:	/* �����Č��@�ō���ߔ{�� */
			case 6:
			case 7:
			case 8:
			case 46:
			case 56:
			case 57:
			case 58:
				iRet = 1;
				p->pSaiken[KekkaCnt].flg = 1;   /* �����Č� */
				p->pKekka[KekkaCnt].knsflg = 'A';
				/* CHG E.Osada 2006-09-19 */
				p->pKekka[KekkaCnt].yobiflg01 = '2';	/* �G���[�t���O ADD 2006.08.11 Hiwa */
				/* 2006-08-28 Nagata �����ł͊�ߔ{���̂ݎw������ */
				/* 10�{���Z�b�g */
				strcpy( p->pSaiken[KekkaCnt].KSBR, "10");
				break;
			case 9:	/* �����Č�  �Œ��ߔ{�� */
				iRet = 1;
				p->pSaiken[KekkaCnt].flg = 1;   /* �����Č� */
				p->pKekka[KekkaCnt].knsflg = 'A';
				/* CHG E.Osada 2006-09-19 */
				p->pKekka[KekkaCnt].yobiflg01 = '2';	/*�G���[�t���O ADD 2006.08.11 Hiwa */
				/* 2006-08-28 Nagata �����ł͊�ߔ{���̂ݎw������ */
				/* 3�{���Z�b�g */
				strcpy( p->pSaiken[KekkaCnt].KSBR, "3");
				break;
			case 3:		/* �Č����� */
			case 72:	/* �Č����� */
			case 47:	/* 2007-04-10 �Č����� */
				//* CHG E.Osada 2006-09-20 */
				iRet = 2;
				/* ADD E.Osada 2006-09-19 */
				if( iAlCode == 4 ){
					iRet = 0;
				}
				p->pSaiken[KekkaCnt].flg = 2;	/* �p��Č� */
				p->pKekka[KekkaCnt].knsflg = 'R';
				/* CHG E.Osada 2006-09-19 */
				p->pKekka[KekkaCnt].yobiflg01 = '2';	/* �G���[�t���O ADD 2006.08.11 Hiwa */
				break;
			default:
				iRet = 0;
				break;
		}
		if(iRet == 2){
			break;
		}
	}
	
	return( iRet );
}
int
getDataAm( char *sBuf, char *sArm )
{
	int	i, j, iCnt;
	char	wbuf[1024];

	iCnt = j = 0;
	memset(wbuf, 0, sizeof(wbuf));
	for( i=0; sBuf[i] != '\0' ;++i ) {
		if( sBuf[i] == '|' ) {
			++iCnt;
			continue;
		}
		if(iCnt == 3) {
			wbuf[j++] = sBuf[i];
			continue;
		}
		if( (iCnt == 4) && (sBuf[i] == 'I') ) {
			strcpy(sArm, wbuf);
			return( 1 );
		}
	}
	return( 0 );
}

/******************************************************************************/
/*  �� �� ���@�FsBskgokConv()				 								  */
/*  �@�\�T�v�@�F���͋@���@�ϊ�								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *   	�ϊ���									 	      */
/*�@ ��P���� �Fchar *   	�ϊ���											  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fvoid														  */
/******************************************************************************/
static	void 
sBskgokConv ( pFrom, pTo )
char	*pFrom ;
char	*pTo ;
{
	if( pFrom[0] == 'C' ) {
		if( pFrom[1] == '\0' ) {
			pTo[2] = '0';
			pTo[3] = '1';
			pTo[4] = '0';
			pTo[5] = '1';
		} 
		else if( pFrom[2] == '\0' ) {
			pTo[2] = '0';
			pTo[3] = '1';
			pTo[4] = '0';
			pTo[5] = pFrom[1];
		}
		else {
			pTo[2] = '0';
			pTo[3] = pFrom[1];
			pTo[4] = '0';
			pTo[5] = pFrom[2];
		}
	} else {
		pTo[2] = '0';
		pTo[3] = '0';
		pTo[4] = '0';
		if( pFrom[3] == '\0' ) {
			pTo[5] = '1';
		} else {
			pTo[5] = pFrom[3];
		}
	}
	return ;
}

/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
/*** �����`�F�b�N�Ώۍ��ڃR�[�h�m�F���� ***/
char  ChkKesseiKmkcd(Kekka* kekka)
{
    char aFunc[32];
    char ret;
    int  i;

    memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
    printf("%sChkKesseiKmkcd\n", Now());
#endif

    /* �Ώۂ�������Ό����`�F�b�N�͍s��Ȃ� */
    ret = 0;

    for(i = 0; i < iKmkmstNum; i++)
    {
        if ((strncmp(pKmkmst[i].knsgrp, kekka->knsgrp,        16) == 0) &&
            (strncmp(pKmkmst[i].kmkcd,  kekka->kmkcd,          7) == 0) &&
            (strncmp(pKmkmst[i].kaiymd, sSysknrmst.kjnsriymd,  8) >= 0) &&
            (strncmp(pKmkmst[i].haiymd, sSysknrmst.kjnsriymd,  8) <= 0))
        {
            ret = pKmkmst[i].ksjhflg;
        }
    }

    return ret;
}

/*** Wajima TEST ***/
#include <time.h>
char* Now() {
	time_t t;
	struct tm *tm_time;
	static char now[10];

	time(&t);
	tm_time = localtime(&t);

	memset(now, 0, 10);
	sprintf(now, "%02d:%02d:%02d ",
		tm_time->tm_hour,      /* �� */
		tm_time->tm_min,       /* �� */
		tm_time->tm_sec);      /* �b */

	return now;
}
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */

/**********************************************************************/
/*                                                                    */
/*   function name : OutputBunsekiOrder                               */
/*                                                                    */
/*   purpose : ���͋@�I�[�_�[��M���t�@�C���쐬                     */
/*                                                                    */
/*   data : 2020.11.18                                                */
/*                                                                    */
/**********************************************************************/
int OutputBunsekiOrder(SOCKET_INF* p)
{
	FILE *fp;
	struct timespec ts;
	struct tm tm;

	char FullPath[1024];
	char FullPathTmp[1024];
	char FileNameBase[1024];
	char cWrk[32];
	char cWrkCd[32];
	char cTmpRack[32];

	memset( FullPath, '\0', sizeof( FullPath ) );
	memset( FullPathTmp, '\0', sizeof( FullPathTmp ) );
	memset( FileNameBase, '\0', sizeof( FileNameBase ) );
	memset( cWrk, '\0', sizeof( cWrk ) );
	memset( cWrkCd, '\0', sizeof( cWrkCd ) );
	memset( cTmpRack, '\0', sizeof( cTmpRack ) );

	clock_gettime( CLOCK_REALTIME, &ts );
	localtime_r( &ts.tv_sec, &tm );
	sprintf( cWrk, "%06ld", ts.tv_nsec );

	/* ���b�N�h�c�ɂ͑O�O�������Ă��邽�ߍ폜���� */
	sprintf( cTmpRack, "%05d" , atoi(p->cRackNum) );

	sprintf( FileNameBase, "%02d%02d%02d%02d%c%c%c_%s_%s",
		tm.tm_mday,
		tm.tm_hour,
		tm.tm_min,
		tm.tm_sec,
		cWrk[0],
		cWrk[1],
		cWrk[2],
		p->cRackNum,
		p->cRackPosNum );

	sprintf( FullPath, "%s/%s%s", aBunsekiOrderFolder, FileNameBase, ".dat" );
	sprintf( FullPathTmp, "%s/%s%s", aBunsekiOrderFolder, FileNameBase, ".tmp" );

	fp = fopen( FullPathTmp, "w+" );
	if( fp == NULL ) {
	 	sFncSyslog ( TRCKIND_ERROR, "OutputBunsekiOrder()", "�t�@�C���̃I�[�v���Ɏ��s���܂����B" ) ;
		return RTN_NG;
        } else {
		CnvtFromKjnsriymd( sSysknrmst.kjnsriymd, cWrkCd );
		fprintf( fp, "%s,%s" , cWrkCd, p->cRackNum );
	}

	fclose( fp );

	rename( FullPathTmp, FullPath );

	return RTN_OK;

}

/******************************************************************************/
/*  �� �� ���@�FchkLowDataSaiken()			 								  */
/*  �@�\�T�v�@�F��l�f�[�^�Č�����							  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �FSOCKET_INF *   	�v���O�������\����						  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/*	���l      �FADD Hanyu 2023-05-23										  */
/******************************************************************************/
int chkLowDataSaiken( SOCKET_INF *p )
{
	int		nRet;

	nRet = KnsLowDataCheck(p->pKekka,p->iKekkaNum);

	return(nRet);
}
