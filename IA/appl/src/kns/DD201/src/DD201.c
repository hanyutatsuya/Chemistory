/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FDD201.c                                                      */
/* �@�T�@�@�@�v�FBM8000�ʐM�E���ʏo�� 	                                      */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/31     A.Yamada       �V�K�쐬                           */
/*  1.01     2006/05/20     S.Nagata       �e�X�g�d����ʂ��ׁA�`�F�b�N�T���� */
/*�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@ "ZZ"�̏ꍇ�A�`�F�b�N���s��Ȃ�     */
/* -------------------------------------------------------------------------- */
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  2.00     2008/09/19     K.Ameno        X-M�Ή�����                        */
/******************************************************************************/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/timeb.h>
/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#include "DD201.h"
#include "Socket.h"
#include "SndData.h"
#include "RcvData.h"
#include "Connect.h"
#include "GetKenorder.h"
#include "OutputKekka.h"
#include "OutputCtrlkka.h"
#include "OutputXbarm.h"
#include "GetMaster.h"

/**********************************************************************/
/*  �����֐��錾                                                      */
/**********************************************************************/
void InitFunction(char*);											/* ���������� */
int GetIniPrm( char* );												/* �ݒ�t�@�C���擾���� */
int	GetMechmst(void);
int	GetZairmst(void);
int	GetKmkmst(void);
void EndFunction(void);												/* �I������ */
void sigcatch(int sig);												/* �V�O�i����M */
void SetLogDat(LOG_TRCKIND,char*,char*,char*,char*,char*,char*);	/* ���O�o�̓f�[�^�ݒ菈�� */
int MainFunction(void);												/* BM8000���䏈�� */
void DecodeRcvData(SOCKET_INF*,int);								/* ��M�f�[�^�f�R�[�h���� */
int DecodeRcvMessage(SOCKET_INF*);									/* ��M���b�Z�[�W�f�R�[�h���� */
int DecodeItemInqTxt_Real(SOCKET_INF*);								/* ���ږ₢���킹�e�L�X�g(���A�����ڑI��)�f�R�[�h���� */
int DecodeItemInqTxt_Auto(SOCKET_INF*);								/* ���ږ₢���킹�e�L�X�g(�������ڑI��)�f�R�[�h���� */
int DecodeMeasureDatTxt(SOCKET_INF*,int);							/* ����f�[�^�e�L�X�g(�Č��₢���킹�L��)�f�R�[�h���� */
int DecodeMeasureDatTxt_NoInq(SOCKET_INF*);							/* ����f�[�^�e�L�X�g(�Č��₢���킹����)�f�R�[�h���� */
int ChkNbkmkcd(SOCKET_INF*,int*,char*);
void SetKekkaData(SOCKET_INF*,int,int);
void SetKekkaData_Calb(SOCKET_INF*);
void SetKekkaData_NoOrder(SOCKET_INF*,int);
void SetKekkaData_Kinkyu(SOCKET_INF*,int);
void SetCtrlkkaData(SOCKET_INF*, char*);
int SetCtrlInf(SOCKET_INF*,char*);
int GetCtrlInf(SOCKET_INF*,char*,int);
void SetKsbr(SOCKET_INF*);
int SetXbarmInf(SOCKET_INF*,int);
double CalcXbarm(double,int);
void SetXbarmData(SOCKET_INF*);
void StatusCtrl(SOCKET_INF*);										/* ��Ԑ��䏈�� */
void SetTimer(SOCKET_INF*, char, float);							/* �^�C�}�ݒ菈�� */
void ClearSndInf(SOCKET_INF*);										/* ���M���N���A�� */
void ClrSaikenInf(SOCKET_INF*);
void MakeSndData(SOCKET_INF*,char);									/* ���M�f�[�^�쐬���� */
int CnvtFromKmkcd( char*, char* );
int CnvtFromZrcd( char*, char* );
int CnvtFromYkcd( char*, char* );
int CnvtFromYtiksbr( char*, char* );
int CnvtFromSbtkbn( char*, char* );
int CnvtFromAge( char*, char* );
int CnvtFromSsymd( char*, char* );
int CnvtFromKjnsriymd( char*, char* );
int GetNowCtrlNo(SOCKET_INF *p, int Seq);
int MakeFileName( char*, char*, int );
int OutputCtrlSeq(SOCKET_INF*);

/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� --> */
void SetXSaikenFlg(int saiken, char* knsgrp, char* kmkcd, XBARM_INF* xinf);
int  GetXSaikenFlg(SOCKET_INF* p, char* knsgrp, char* kmkcd, int* module, XBARM_INF* xinf);
int  OutputXbarmInf(char* gouki, XBARM_INF* xinf);
int  InputXbarmInf(char* gouki, XBARM_INF* xinf);
void DelXbarmInf(char* gouki);
char ChkKesseiKmkcd(Kekka* kekka);

extern double GetXMavg(char* knsgrp, char* kmkcd);					/* X-M�����l�ɕ��ϒl��ݒ肷�� */

char* Now(void);
/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� <-- */

/*	���L����������֐� */
static	int		sFncShmCrt ( int ) ;
static	int		sFncShmGet ( int , int *) ;
static	int		sFncShmDel ( int ) ;

int GetKskRitu(Kskbrmst *key, char *sMax, char *sMin );
int OutputBunsekiOrder(SOCKET_INF*);

/**********************************************************************/
/*  �ϐ��錾                                                          */
/**********************************************************************/
SOCKET_INF sSocketInf;
char	aRcvBuf[550];			/* ��M�f�[�^�o�b�t�@ */

int		iRcvAllMsgCnt;			/* �S��M���b�Z�[�W���`�F�b�N�J�E���^ */
int		iRcvMsgCnt;				/* ��M���b�Z�[�W���`�F�b�N�J�E���^ */
char	aFileNameStr[256];		/* �t�@�C�����G���A */
char	aKenorderFolder[256];	/* �t�@�C�����G���A */
char	aKenorderFolder2[256];	/* �t�@�C�����G���A */
char	aKekkaFolder[256];		/* �t�@�C�����G���A */
char	aCtrlkkaFolder[256];	/* �t�@�C�����G���A */
char	aBunsekiOrderFolder[256];	/* �t�@�C�����G���A */
char	aMstFolder[256];		/* �t�@�C�����G���A */
char	aKmkcdTblFolder[256];	/* �t�@�C�����G���A */
char	aLogOutFolder[256];		/* �t�@�C�����G���A */
int		iGouki;
int		iSckConChk;				/* �\�P�b�g�ڑ��`�F�b�N */
time_t	tSckConTm;				/* �\�P�b�g�ڑ��^�C�} */ 
struct stcLogMember sLog;		/* ���O�o�͏��\���� */
BUNSEKI_INF *sBunsekiInf;
int		iBunsekiNum;			/* ���͋@���@�� */

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
Knsgmst		*pKnsgmst;			/* 009 060417 */
int			iKnsgmstNum;		/* 009 060417 */
Kskbrmst *pKskbrmst;     		/* ADD Haga 2006-08-02 */
int iKskbrmstNum;        		/* ADD Haga 2006-08-02 */
/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� --> */
Xbarmmst	*pXbarmmst;
int			iXbarmmstNum;
Rngchkmst	*pRngchkmst;
int			iRngchkmstNum;
/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� <-- */
int		EndFlg = 0;
int		shm_Key = 0;
int		shm_Id;

char	aNa_code[6];
char	aK_code[6];
char	aCl_code[6];

char	aMekbn[5];
char	aZrCd[2][5];
char	aKskbrt[5][4];
char	aYkcd[9][5];

/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� --> */
char    aHnkCd[3][4+1];			/* �ޗ��R�[�h���猟�̎�ʂւ̕ϊ��R�[�h */
/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� <-- */

#define		SAIKEN_ARI		0
#define		DENKAISITU		1
#define		SAIKEN_NASI		2

XBARM_INF	sXbarm_inf[XBARM_ITEM_NUM];
int			iXbarmNum;
int			iXbarmCnt;
#define		X_M_SUM			0
#define		X_M_AVE			1

CTRL_INF	sCtrl_inf[CTRL_ITEM_NUM];
int			iCtrlNum;
int			iCtrlCnt;

int			gCTRL_CHK_TIME;		/* �R���g���[���̓��ꐫ�m�F�͈͎���(��) */

void trim(char * dst, char *src) ;

/* ���b�Z�[�W��` */
struct MEASURE_DAT_TXT			sMeasureDatTxt;			/* ����f�[�^�e�L�X�g(�Č��₢���킹�L��) */
struct ITEM_SEL_INST_TXT_NO_VAL	sItemSelInstTxt_NoVal;	/* ���ڑI���w���e�L�X�g(�O��l����) */

/**********************************************************************/
/*                                                                    */
/*   function name : Init                                             */
/*                                                                    */
/*   purpose : ����������                                             */
/*                                                                    */
/*   data : 2005.12.20                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
void InitFunction( char* prm  )
{
	char name[100];
	int iCnt;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memset( name,0,100 );

	strcpy( name,INI_FILE_NAME );
	strcat( name,prm );
	strcat( name,".ini" );

	if (ZbmlOpenLog( name )  != 0 ) {
		printf("ZbmlOpenLog Error");
	}

	pKenorder = NULL;
	pMechmst = NULL;
	iMechmstNum = 0;
	pKinkyu = NULL;
	iKinkyuNum = 0;
	pKmkmst = NULL;
	iKmkmstNum = 0;
	pCtrlmst = NULL;
	iCtrlmstNum = 0;
	pKnsgmst = NULL;		/* 009 060417 */
	iKnsgmstNum = 0;		/* 009 060417 */
/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� --> */
	pXbarmmst    = NULL;
	iXbarmmstNum = 0;
	pRngchkmst   = NULL;
	iRngchkmstNum= 0;
/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� <-- */

	memset( &sSysknrmst,0,sizeof(Sysknrmst) );
	memset(aRcvBuf,0,sizeof(aRcvBuf));								/* ��M�f�[�^�o�b�t�@�N���A */
	sSocketInf.iSd = 0;												/*�\�P�b�g�ԍ� */
	memset(sSocketInf.aGouki,0,sizeof(sSocketInf.aGouki));			/* ���@�ԍ� */
	sSocketInf.iPortNum  = 0;										/* �|�[�g�ԍ� */
	memset(sSocketInf.aHostName,0,sizeof(sSocketInf.aHostName));	/* �z�X�g�� */
	memset(sSocketInf.aSndTmpBuf,0,sizeof(sSocketInf.aSndTmpBuf));	/* ���M�f�[�^�ꎞ�o�b�t�@�N���A */
	sSocketInf.cRcvFrameCtrlChar = 0xff;							/* ��M�t���[�����䕶��=�G���[ */
	sSocketInf.cSndFrameCtrlChar = 0xff;							/* ���M�t���[�����䕶��=�G���[ */
	sSocketInf.cFrameNum = 0;										/* �t���[���ԍ� = 0 */
	sSocketInf.cChkRcvData = NO_RCV_DATA;							/* ��M�f�[�^�Ȃ� */
	sSocketInf.cSndDataReq = NO_SND_REQ;							/* ���M�f�[�^�v���Ȃ� */
	sSocketInf.cStatus = STAT_IDLE;									/* STATUS = idle */
	sSocketInf.cChkRcvMessage = MESSAGE_NO_ERR;						/* ��M���b�Z�[�W���� */
	sSocketInf.cChkNextFrame = FRAME_END;							/* �t���[���I�� */
	sSocketInf.cSndFrameSeqNum = 0;									/* ����t���[�����M�J�E���^ */
	sSocketInf.iSndRetryCnt = 0;									/* �t���[�����M���g���C�J�E���^ */
	memset( sSocketInf.cRackNum,0,sizeof(sSocketInf.cRackNum) );
	memset( sSocketInf.cRackPosNum,0,sizeof(sSocketInf.cRackPosNum) );
	sSocketInf.iRcvMsg = MSG_NON;									/* ���b�Z�[�W�̈Ӗ� */
	sSocketInf.iSndBlockNum = 0;									/* ���M�e�L�X�g�u���b�N���� */
	sSocketInf.iSndBlockCnt = 0;									/* ���M�e�L�X�g�u���b�N�J�E���^ */
	sSocketInf.fTmOutVal = 0;										/* �t���[�����M���g���C�J�E���^ */
	sSocketInf.iSndAgainReq = 0;									/* �����N�R���e���V�����Ȃ� */
	memset(sSocketInf.aSndAgainBuf,0,sizeof(sSocketInf.aSndAgainBuf));
																	/*  �S���M���b�Z�[�W�G���A(�����N�R���e���V����) */
	memset(&sSocketInf.sCtrlkka,0,sizeof(sSocketInf.sCtrlkka));
	memset(&sSocketInf.sSndorder,0,sizeof(sSocketInf.sSndorder));
	sSocketInf.pKekka = NULL;
	sSocketInf.pSaiken = NULL;
	sSocketInf.iKekkaNum = 0;
	sSocketInf.iKekkaCnt = 0;
	sSocketInf.iCtrlSeq = 0;
	sSocketInf.iCtrlSeqCnt = 0;
	sSocketInf.next = NULL;
	sSocketInf.prev = NULL;
	memset( aFileNameStr,0,sizeof(aFileNameStr) );					/* �t�@�C�����G���A */

	iRcvAllMsgCnt = 0;												/* �S��M���b�Z�[�W���`�F�b�N�J�E���^ */
	iRcvMsgCnt = 0;													/* ��M���b�Z�[�W���`�F�b�N�J�E���^ */

	iSckConChk = SCK_CON_NG;										/* �\�P�b�g�ڑ��`�F�b�N */
	tSckConTm = time(NULL);											/* �\�P�b�g�ڑ��^�C�} */
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
	memset(&sMeasureDatTxt,0,sizeof(sMeasureDatTxt));				/* ����f�[�^�e�L�X�g(�Č��₢���킹�L��) */
	memset(&sMeasureDatTxt,0,sizeof(sMeasureDatTxt));				/* ����f�[�^�e�L�X�g(�Č��₢���킹����) */
	memset(&sItemSelInstTxt_NoVal,0,sizeof(sItemSelInstTxt_NoVal));	/* ���ڑI���w���e�L�X�g(�O��l����) */
	memset(&sMeasureDatTxt,0,sizeof(sMeasureDatTxt));				/* �d��������f�[�^�e�L�X�g */
	memset(aZrCd,0,sizeof(aZrCd));
/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� --> */
	memset(aHnkCd,0,sizeof(aHnkCd));
/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� <-- */
	memset(aKskbrt,0,sizeof(aKskbrt));
	memset(aYkcd,0,sizeof(aYkcd));
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

/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� --> */
/*** Xbarm��񂪕ۑ�����Ă���ꍇ�́A�����ōĐݒ肵�Ă���(pltno�̂���) ***/
/*** Connect�̌�łȂ��ƍ��@���ݒ肳��Ȃ����߃t�@�C����������ł��Ȃ�  ***/
	if (InputXbarmInf(sBunsekiInf[0].aGouki, sXbarm_inf) == RTN_OK) {
		iXbarmCnt = sXbarm_inf[0].iXbarmCnt;
    	iXbarmNum = sXbarm_inf[0].iXbarmNum;
	}
/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� <-- */

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
	char wrk[100];
	char port[16];
	int	iCnt;
	int	iCnt2;
	int	iCnt3;
	int	iWrk;
	char	wk[16];
	int	iWtimer;	// ADD E.Osada 2006-08-21

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
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
	/*	�ُ�I��	LOG */
		return ( -1 ) ;
	}
	shm_Key = atoi ( wk ) ;
	if ( sFncShmCrt ( shm_Key ) < 0 ) {
		sFncSyslog ( TRCKIND_ERROR, "GetIniPrm()", "SHM_KEY�l���ُ�ł��B" ) ;
		return ( -1 ) ;
	}
	/* �R���g���[���m��͈͎��� */
	if ( ZbmlPrmGetVal ( bp, "CTRL_CHK_TIME", wk ) != 0 ) {
	/*	�ُ�I��	LOG */
		return ( -1 ) ;
	}
	gCTRL_CHK_TIME = atoi ( wk ) ;
	
	ZbmlPrmGetVal(bp, "NA_CODE", aNa_code);
	ZbmlPrmGetVal(bp, "K_CODE", aK_code);
	ZbmlPrmGetVal(bp, "CL_CODE", aCl_code);

	memset( wrk,0,sizeof(wrk) );
	ZbmlPrmGetVal(bp, "MEKBN", wrk);
	strcpy( aMekbn,"    " );
	strncpy( aMekbn,wrk,strlen(wrk) );
	printf( "kbn:%s\n",aMekbn );

	/* �ޗ��R�[�h�擾 */
	ZbmlPrmGetVal(bp, "SBT_1", aZrCd[0]);
	ZbmlPrmGetVal(bp, "SBT_2", aZrCd[1]);

/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� --> */
/*** �ޗ��R�[�h���猟�̎�ʂւ̕ϊ��R�[�h ***/
	ZbmlPrmGetVal(bp, "ZCD_1",   aHnkCd[0]);
	ZbmlPrmGetVal(bp, "ZCD_2_1", aHnkCd[1]);
	ZbmlPrmGetVal(bp, "ZCD_2_2", aHnkCd[2]);
/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� <-- */

	/* ��ߔ{���擾 */
	ZbmlPrmGetVal(bp, "KSKBRT_1", aKskbrt[0]);
	ZbmlPrmGetVal(bp, "KSKBRT_2", aKskbrt[1]);
	ZbmlPrmGetVal(bp, "KSKBRT_3", aKskbrt[2]);
	ZbmlPrmGetVal(bp, "KSKBRT_4", aKskbrt[3]);
	ZbmlPrmGetVal(bp, "KSKBRT_5", aKskbrt[4]);

	/* �e���ʃR�[�h�擾 */
	ZbmlPrmGetVal(bp, "YKSBT_1", aYkcd[0]);
	ZbmlPrmGetVal(bp, "YKSBT_2", aYkcd[1]);
	ZbmlPrmGetVal(bp, "YKSBT_3", aYkcd[2]);
	ZbmlPrmGetVal(bp, "YKSBT_4", aYkcd[3]);
	ZbmlPrmGetVal(bp, "YKSBT_5", aYkcd[4]);
	ZbmlPrmGetVal(bp, "YKSBT_6", aYkcd[5]);
	ZbmlPrmGetVal(bp, "YKSBT_7", aYkcd[6]);
	ZbmlPrmGetVal(bp, "YKSBT_8", aYkcd[7]);
	ZbmlPrmGetVal(bp, "YKSBT_9", aYkcd[8]);

	ZbmlPrmGetVal(bp, "BUNSEKI_NUM", cNum);
	iBunsekiNum = atoi( cNum );
	printf( "BUNSEKI_NUM:%d\n",iBunsekiNum );
	sBunsekiInf = malloc(sizeof(BUNSEKI_INF)*iBunsekiNum);

	/* ADD E.Osada 2006-08-21 ���M�^�C�}�擾 */
	if ( ZbmlPrmGetVal ( bp, "SND_TIMER", wk ) != 0 ) {
		/*�h�m�h�t�@�C���ɐݒ肪�����ꍇ�̓f�t�H���g10msec���Z�b�g */
		iWtimer = DEFSNDTIMER;
	} else {
		iWtimer = atoi ( wk ) ;
	}
	/**/

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
		/**/

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
	ZbmlPrmClose(bp);
	return ( 0 ) ;
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

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

	printf( "EndFunction()\n" );

/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� --> */
	DelXbarmInf(sSocketInf.aGouki);
/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� <-- */

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
	if( pKnsgmst != NULL ) {		/* 009 060417 */
		free(pKnsgmst);				/* 009 060417 */
	}								/* 009 060417 */

	ZbmlCloseLog();
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

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif

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
			/* �������Ȃ� */
		}
	}
	EndFunction();
	return ( 0 ) ;
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
#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
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
/*   data : 2005.12.20                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
void DecodeRcvData(SOCKET_INF* p,int len)
{
	char cWrk;
	char cWrk2;
	char csh;
	char csl;
	int iCnt;
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("DecodeRcvData()\n");
#endif

	cWrk = 0;
	cWrk2 = 0;
	iCnt = 0;
	p->cChkRcvMessage = MESSAGE_NO_ERR;

	switch( aRcvBuf[0]) {
	case ENQ:
		p->cRcvFrameCtrlChar = ENQ;	/* <ENQ>�ݒ� */
		p->cChkRcvData = RCV_DATA_OK;
		p->cFrameNum = 0;
		break;
	case ACK:
		p->cRcvFrameCtrlChar = ACK;	/* <ACK>�ݒ� */
		p->cChkRcvData = RCV_DATA_OK;
		break;
	case STX:
		/* �o�C�g���`�F�b�N */
		if( (len > MAX_RCV_NUM) || (len < 0) ) {
			p->cChkRcvData = RCV_DATA_NG;
			break;
		}
		/* No.1 �t���[�����䕶���ݒ� */
#ifdef _DEBUG_
		printf("�t���[���ԍ��`�F�b�N\n");
#endif
		p->cRcvFrameCtrlChar = STX;
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
			break;
		}
		/* CSH/CSL�`�F�b�N */
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
		printf("cWrk:%02x\n",cWrk);
#endif
		csh = ((cWrk >> 4) & 0x0f);
		if( csh <= 0x09 ) {
			csh += 0x30;
		} else {
			csh += 0x37;
		}
#ifdef _DEBUG_
		printf("csh:%c\n",csh);
#endif
		csl = (cWrk & 0x0f);
		if( csl <= 0x09 ) {
			csl += 0x30;
		} else {
			csl += 0x37;
		}
#ifdef _DEBUG_
		printf("csl:%c\n",csl);
#endif
		/* 2006.05.20 S.Nagata */
		if( aRcvBuf[len-4] != 'Z' ){
			if( aRcvBuf[len-4] != csh ) {
				p->cChkRcvData = RCV_DATA_NG;
#ifdef _DEBUG_
				printf( "csh:%c,%c\n",aRcvBuf[len-4],csh );
#endif
				break;
			}
		}
		/* 2006.05.20 S.Nagata */
		if( aRcvBuf[len-3] != 'Z' ){
			if( aRcvBuf[len-3] != csl ) {
#ifdef _DEBUG_
				printf( "csl:%c,%c\n",aRcvBuf[len-3],csl );
#endif
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
			p->cChkRcvData = RCV_DATA_OK;
/*-----------------------------------------------------------*/
/*** 20060702 STX��ACK�̓f�[�^CR�`�F�b�N�܂�OK�Ȃ瑦�Ԃ��B ***/
			MakeSndData(p,ACK);
			SndData(p);
/* ----------------------------------------------------------*/
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
	case DC1:
		p->cRcvFrameCtrlChar = DC1;		/* <DC1>�ݒ� */
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
/*   data : 2005.12.20                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int DecodeRcvMessage(SOCKET_INF* p)
{
	int iLen;
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif

	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("DecodeRcvMessage\n");
#endif

	iRcvAllMsgCnt = 0;
	iLen = strlen(aRcvBuf);

	switch( aRcvBuf[iRcvAllMsgCnt+2] ) {
	case 'S':
		if( iLen != 43 ) {
			return MESSAGE_ERR;
		}
		p->iRcvMsg = MSG_ORDER;
		if( DecodeItemInqTxt_Real(p) == MESSAGE_ERR ) {
			return MESSAGE_ERR;
		}

		/* 2020/11/01 �₢���킹���b�N���̏o�͏��� */
		if( OutputBunsekiOrder(p) != RTN_OK ) {
			sFncSyslog ( TRCKIND_ERROR, "OutputCtrlSeq()", "�t�@�C���̃I�[�v���Ɏ��s���܂����B" ) ;
			return RTN_NG;
		}
#ifdef _DEBUG_
		printf("���ږ₢���킹�e�L�X�g(���A�����ڑI��):%s\n",aRcvBuf);
#endif
		break;

	case 'r':
		p->iRcvMsg = MSG_RESULT;
		if( DecodeMeasureDatTxt(p,SAIKEN_ARI) == MESSAGE_ERR ) {
			return MESSAGE_ERR;
		}
#ifdef _DEBUG_
		printf("%02x\n",p->cRcvFrameCtrlChar);
		printf("����f�[�^�e�L�X�g(�Č��₢���킹�L��):%s\n",aRcvBuf);
#endif
		break;

	case 'R':
		p->iRcvMsg = MSG_NON;;
		/* 2006-08-28 Nagata */
		/* �Č��₢���킹�����t�H�[�}�b�g�̃f�[�^�ł��o�b�`���M���́A   */
		/* ���񌋉ʂ�����Ă��邽�߁A���̒��ɏ���or�Č��̔��f��ǉ����� */
		if( DecodeMeasureDatTxt_NoInq(p) == MESSAGE_ERR ) {
			return MESSAGE_ERR;
		}
#ifdef _DEBUG_
		printf("����f�[�^�e�L�X�g(�Č��₢���킹����):%s\n",aRcvBuf);
#endif
		break;

	case 'e':
		p->iRcvMsg = MSG_ELC;
		if( DecodeMeasureDatTxt(p,DENKAISITU) == MESSAGE_ERR ) {
			return MESSAGE_ERR;
		}
#ifdef _DEBUG_
		printf("�d��������f�[�^�e�L�X�g:%s\n",aRcvBuf);
#endif
		break;

	default:
		p->iRcvMsg = MSG_NON;
		return MESSAGE_ERR;
	}
	return MESSAGE_NO_ERR;	
}
/**********************************************************************/
/*                                                                    */
/*   function name : DecodeItemInqTxt_Real                            */
/*                                                                    */
/*   purpose : ���ږ₢���킹�e�L�X�g(���A�����ڑI��)�f�R�[�h����     */
/*                                                                    */
/*   data : 2006.01.06                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int DecodeItemInqTxt_Real(SOCKET_INF* p)
{
	char cWrk[10];;
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("DecodeItemInqTxt_Real\n");
#endif

	iRcvMsgCnt = 0;
	ClrSaikenInf(p);
	memset(&(p->sCtrlkka),0,sizeof(p->sCtrlkka));
	p->iOrderNum = 0;
	memset(&(p->sSndorder),0,sizeof(p->sSndorder));

	memset( cWrk,0,10 );

	if( aRcvBuf[10] == '0' ) {
		strncpy( p->sSndorder.seqnum,&aRcvBuf[11],13 );
	} else {
		return MESSAGE_ERR;
	}
	strncpy( p->cRackNum,&aRcvBuf[24], 8 );
	strncpy( p->cRackPosNum,&aRcvBuf[33], 2 );

#ifdef _DEBUG_
	printf( "���b�N�ԍ�:%s\n",p->cRackNum);
	printf( "���b�N�ʒu:%s\n",p->cRackPosNum );
#endif

	if( p->cRackNum[0] == ' ' ) {
		return MESSAGE_ERR;
	} else {
		return MESSAGE_OK;
	}
}
/**********************************************************************/
/*                                                                    */
/*   function name : DecodeItemInqTxt_Auto                            */
/*                                                                    */
/*   purpose : ���ږ₢���킹�e�L�X�g(�������ڑI��)�f�R�[�h����       */
/*                                                                    */
/*   data : 2006.03.01                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int DecodeItemInqTxt_Auto(SOCKET_INF* p)
{
	char cWrk[10];;
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("DecodeItemInqTxt_Auto\n");
#endif

	iRcvMsgCnt = 0;
	memset(&(p->sCtrlkka),0,sizeof(p->sCtrlkka));
	p->iOrderNum = 0;
	memset(&(p->sSndorder),0,sizeof(p->sSndorder));

	memset( cWrk,0,10 );

	if( aRcvBuf[10] == '1' ) {
	} else {
		return MESSAGE_ERR;
	}
	/* TT�ԍ� */
	memset( p->cRackNum,0,sizeof(p->cRackNum) );
	strncpy( p->cRackNum,&aRcvBuf[11],2 );
#ifdef _DEBUG_
	printf( "TT�ԍ�:%s\n",p->cRackNum );
#endif
	/* CUP�ԍ� */
	memset( p->cRackPosNum,0,sizeof(p->cRackPosNum) );
	strncpy( p->cRackPosNum,&aRcvBuf[14],2 );
#ifdef _DEBUG_
	printf( "CUP�ԍ�:%s\n",p->cRackPosNum );
#endif

	return MESSAGE_OK;
}
/**********************************************************************/
/*                                                                    */
/*   function name : DecodeMeasureDatTxt_NoInq                        */
/*                                                                    */
/*   purpose : ����f�[�^�e�L�X�g(�Č��₢���킹����)�f�R�[�h����     */
/*                                                                    */
/*   data : 2006.02.16                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int DecodeMeasureDatTxt_NoInq(SOCKET_INF* p)
{
	int allblknum;
	int chk;
	int iWrk;
	int iWrk2;
	int iCnt;
	int iCnt2;
	char cXmSkFlg;
	char cWrk[10];
	char jisksbr[32];
	char aFunc[32];
	char sSpace[128];	/* ADD E.Osada 2006-07-14 */
	char sMark[10];		/* ADD Nagata 2006-08-28  */

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("DecodeMeasureDatTxt_NoInq\n");
#endif

	chk = 0;
	iRcvMsgCnt = 0;
	memset( cWrk,0,sizeof(cWrk));
	memset(&(p->sCtrlkka),0,sizeof(p->sCtrlkka));
	memset(&sMeasureDatTxt,0,sizeof(sMeasureDatTxt));

	/* �u���b�N�ԍ� */
	memcpy( cWrk, &aRcvBuf[6], 2 );
	iWrk = atoi( cWrk );
#ifdef _DEBUG_
	printf( "�u���b�N�ԍ�:%d\n",iWrk );
#endif
	if( iWrk == 1 ) {
		if( aRcvBuf[25] != 'C' ) {
			/* �S�u���b�N�� */
			memcpy( cWrk, &aRcvBuf[4], 2 );
			ClrSaikenInf(p);
			allblknum = atoi( cWrk );
			if( allblknum == 1 ) {
				memcpy( cWrk, &aRcvBuf[8], 3 );
				p->iKekkaNum = atoi( cWrk );
			} else {
				p->iKekkaNum = 19+(atoi(cWrk)-1)*22;
			}
			p->pKekka = malloc(sizeof(Kekka)*(p->iKekkaNum));
			for( iCnt=0;iCnt<p->iKekkaNum;iCnt++ ) {
				memset( &(p->pKekka[iCnt]),0,sizeof(Kekka) );
			}
			p->pSaiken = malloc(sizeof(SaikenInfo)*(p->iKekkaNum));
			for( iCnt=0;iCnt<p->iKekkaNum;iCnt++ ) {
				memset( &(p->pSaiken[iCnt]),0,sizeof(SaikenInfo) );
			}
			p->iOrderNum = 0;
			memset(&(p->sSndorder),0,sizeof(p->sSndorder));
			strncpy( p->cRackNum,&aRcvBuf[83], 8 );
			strncpy( p->cRackPosNum,&aRcvBuf[92], 2 );

			/* ���̎�� */
			sMeasureDatTxt.cSpecimenType[0] = aRcvBuf[115];
			p->sSndorder.racktype[0] = aRcvBuf[115];
		}
	} else {
	}
	/* ���u���ʔԍ� */
	sMeasureDatTxt.cDevIdentifNum[0] = aRcvBuf[3];

	/* ������ */
	strncpy( sMeasureDatTxt.cInspectDay,&aRcvBuf[11],8 );
	if( strncmp(sMeasureDatTxt.cInspectDay,"        ",8) == 0 ) {
		memset( sMeasureDatTxt.cInspectDay,0,sizeof(sMeasureDatTxt.cInspectDay) );
		strcpy( sMeasureDatTxt.cInspectDay,"10000101" );
	}
	/* �������� */
	strncpy( sMeasureDatTxt.cInspectTm,&aRcvBuf[19],6 );
	if( strncmp(sMeasureDatTxt.cInspectTm,"      ",6) == 0 ) {
		memset( sMeasureDatTxt.cInspectTm,0,sizeof(sMeasureDatTxt.cInspectTm) );
		strcpy( sMeasureDatTxt.cInspectTm,"000001" );
	}
	/* ���̋敪 */
	sMeasureDatTxt.cSpecimenDiv[0] = aRcvBuf[25];
	/* ID�d�l */
	sMeasureDatTxt.cIdSpec[0] = aRcvBuf[26];

#ifdef _DEBUG_
		printf("�E���̋敪�@:�@%c\n", sMeasureDatTxt.cSpecimenDiv[0]);
		printf("�E�h�c�d�l�@:�@%c\n", sMeasureDatTxt.cIdSpec[0]);
#endif
	if( sMeasureDatTxt.cIdSpec[0] == '0' ) {
		switch( sMeasureDatTxt.cSpecimenDiv[0] ) {

/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� --> */
/*** �ً}STAT�Ή� ***/
		case 'I': 		/* ������ */
#ifdef _DEBUG_
			printf( "�i�����݁j\n" );
#endif
			iWrk2 = 13;
			break;
		case 'S': 		/* �ً} */
#ifdef _DEBUG_
			printf( "�i�ً}�j\n" );
#endif
			iWrk2 = 3; /* BM8000�ł�STAT Port���T�|�[�g���Ȃ��ׁAExx�̌Œ蒷���̔ԍ��݂̂ƂȂ� */
			break;
/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� <-- */
		case 'C':
			iWrk2 = 5;
			break;
		case 'H':
			iWrk2 = 5;
			break;
		case 'M':
			iWrk2 = 7;
			break;
		case 'N':
			iWrk2 = 9;
			if( p->cRackNum[0] == ' ' ) {
				ClrSaikenInf(p);
				return MESSAGE_ERR;
			}
			break;
		default:
			ClrSaikenInf(p);
			return MESSAGE_ERR;
		}
		strncpy( sMeasureDatTxt.cIdSpecimenId,&aRcvBuf[27],iWrk2 );
		if( iWrk2 != 9 ) {
			memset( p->cRackNum,0,sizeof(p->cRackNum));
			memset( p->cRackPosNum,0,sizeof(p->cRackPosNum));
			strncpy( p->cRackNum,sMeasureDatTxt.cIdSpecimenId,iWrk2);
			strcpy( p->cRackPosNum,"1" );
		}
	} else if( sMeasureDatTxt.cIdSpec[0] == '1' ) {
		if( sMeasureDatTxt.cSpecimenDiv[0] == 'N' ) {
			strncpy( sMeasureDatTxt.cIdSpecimenId,&aRcvBuf[27],13 );
			/* TT�ԍ� */
			strncpy( sMeasureDatTxt.cTtNum,&aRcvBuf[40],2 );
			memset( p->cRackNum,0,sizeof(p->cRackNum) );
			strncpy( p->cRackNum,sMeasureDatTxt.cTtNum,2 );
#ifdef _DEBUG_
			printf( "TT�ԍ�:%s\n",sMeasureDatTxt.cTtNum );
#endif
			/* CUP�ԍ� */
			strncpy( sMeasureDatTxt.cCupNum,&aRcvBuf[43],2 );
			memset( p->cRackPosNum,0,sizeof(p->cRackPosNum) );
			strncpy( p->cRackPosNum,sMeasureDatTxt.cCupNum,2 );
#ifdef _DEBUG_
			printf( "CUP�ԍ�:%s\n",sMeasureDatTxt.cCupNum );
#endif

/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� --> */
/*** �ً}STAT�Ή� ***/
		} else if (sMeasureDatTxt.cSpecimenDiv[0] == 'S' ||
	    	       sMeasureDatTxt.cSpecimenDiv[0] == 'I') {
			/* �ً}STAT�̏ꍇ�͏����𒆒f���Ȃ� */
            strncpy( sMeasureDatTxt.cIdSpecimenId,&aRcvBuf[27],13 );
            /* TT�ԍ� */
            strncpy( sMeasureDatTxt.cTtNum,&aRcvBuf[40],2 );
            memset( p->cRackNum,0,sizeof(p->cRackNum) );
            strncpy( p->cRackNum,sMeasureDatTxt.cTtNum,2 );
#ifdef _DEBUG_
            printf( "TT�ԍ�:%s\n",sMeasureDatTxt.cTtNum );
#endif
            /* CUP�ԍ� */
            strncpy( sMeasureDatTxt.cCupNum,&aRcvBuf[43],2 );
            memset( p->cRackPosNum,0,sizeof(p->cRackPosNum) );
            strncpy( p->cRackPosNum,sMeasureDatTxt.cCupNum,2 );
#ifdef _DEBUG_
            printf( "CUP�ԍ�:%s\n",sMeasureDatTxt.cCupNum );
			printf( "  �ً}�̏ꍇ�����𒆒f���Ȃ�\n");
#endif
		} else {
			ClrSaikenInf(p);
			return MESSAGE_ERR;
		}
	/* add 20070523 waj �ً}STAT�Ή� */
	} else if (sMeasureDatTxt.cSpecimenDiv[0] == 'S' ||
	           sMeasureDatTxt.cSpecimenDiv[0] == 'I') {
		/* �ً}STAT�̏ꍇ�͏����𒆒f���Ȃ� */
#ifdef _DEBUG_
		printf( "  �ً}�̏ꍇ�����𒆒f���Ȃ�\n");
#endif
/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� <-- */

	} else {
		ClrSaikenInf(p);
		return MESSAGE_ERR;
	}

	/* �u���b�N�����ڐ� */
	memset( cWrk,0,sizeof(cWrk));
	memcpy( cWrk, &aRcvBuf[8], 3 );
	iWrk2 = atoi( cWrk );
#ifdef _DEBUG_
	printf( "�u���b�N�����ڐ�:%d\n",iWrk2 );

	printf( "���b�N�ԍ�:%s\n",p->cRackNum);
	printf( "���b�N�ʒu:%s\n",p->cRackPosNum );
#endif

	/* ���ڔԍ� */
	if( iWrk == 1 ) {
		iWrk = 117;
	} else if( (iWrk >= 2) && (iWrk <= 30) ) {
		iWrk = 51;
	} else {
		return MESSAGE_ERR;
	}
	/* ��ʌ��� */

/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� --> */
    /* upd 2007.05.16 waj �ً}STAT�Ή��̂��� */
    if( sMeasureDatTxt.cSpecimenDiv[0] == 'N' ||
        sMeasureDatTxt.cSpecimenDiv[0] == 'S' ||
        sMeasureDatTxt.cSpecimenDiv[0] == 'I' ) {
#ifdef _DEBUG_
		printf("���̋敪�@:�@%c\n", sMeasureDatTxt.cSpecimenDiv[0]);
#endif
/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� <-- */
		for( iCnt=0; iCnt<iWrk2; iCnt++ ) {
			/* ���ڔԍ� */
			strncpy( sMeasureDatTxt.cItemNum,&aRcvBuf[iWrk+iCnt*20],3 );
			/* ���͏��� */
			sMeasureDatTxt.cAnalysCond[0] = aRcvBuf[(iWrk+3)+iCnt*20];
			/* ���͏���->���{��ߔ{�� */
			memset( jisksbr,0,sizeof(jisksbr) );
			/* ����l->���f�[�^ */
			memset(sSpace, 0, sizeof(sSpace));
			memcpy( sSpace, &aRcvBuf[(iWrk+4)+iCnt*20],8 );
			if( !memcmp(sSpace, "////////", 8) ) {
				memset(sMeasureDatTxt.cMeasureVal, ' ', 8);
			} else {
				memcpy( sMeasureDatTxt.cMeasureVal,&aRcvBuf[(iWrk+4)+iCnt*20],8 );
			}
			/* �}�[�N->���͋@�G���[�X�e�[�^�X */
			strncpy( sMeasureDatTxt.cMark,&aRcvBuf[(iWrk+12)+iCnt*20],2 );
			/* ����u���b�N�ԍ�->���W���[���ԍ� */
			sMeasureDatTxt.cDevIdentifNum[0] = aRcvBuf[(iWrk+19)+iCnt*20];

			/* �v���b�gSEQ�C���N�������g */
			++(p->aPltseq[atoi(sMeasureDatTxt.cDevIdentifNum)]);

			memset(&(p->pKekka[p->iKekkaCnt]),0,sizeof(Kekka));

/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� --> */
/*** �ً}STAT�Ή��̂��� ***/
			if( sMeasureDatTxt.cIdSpec[0]      == '0' &&
		        sMeasureDatTxt.cSpecimenDiv[0] == 'N' ) {
#ifdef _DEBUG_
				printf(" >>>>> ��ʃf�[�^����\n");
#endif
/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� <-- */
				chk = 1;
				/* �����I�[�_�[(.dat)�t�@�C���ǂݍ��� */
				if( pKenorder != NULL ) {
					free( pKenorder );
					pKenorder = NULL;
				}
				if( ChkNbkmkcd(p,&iCnt2,jisksbr) == RTN_OK ) {

					/* X-M�W�v�t���O���擾(0:�W�v����A1:�W�v���Ȃ�) */
					cXmSkFlg = GetXmSkFlg(pKenorder[iCnt2].knsgrp, pKenorder[iCnt2].kmkcd, pKenorder[iCnt2].knskisymd);

					/* X-M�W�v����ꍇ(0:�W�v����A1:�W�v���Ȃ�) */
					if(cXmSkFlg == '0') {
						/* xbar_inf�t�@�C���ɐݒ聕PLTSEQ�̍ŏI����XM_�`.dat�t�@�C���o�� */
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
					/*ADD 2006-08-28 Nagata */
					/* �}�[�N�̂R�o�C�g�ڂ�"R"��������A�Č��f�[�^       */
					/* �}�[�N�̂R�o�C�g�ڂ�" "��������A����f�[�^�Ƃ��� */
					memset(sMark,0,sizeof(sMark));
					strncpy( sMark,&aRcvBuf[(iWrk+12)+iCnt*20],3 );
					if(sMark[2] == 'R' ){ // �Č��l
						SetKekkaData(p,iCnt2,SAIKEN_NASI);
					}
					else{
						SetKekkaData(p,iCnt2,SAIKEN_ARI);
					}
				} else {
					SetKekkaData_NoOrder(p,SAIKEN_NASI);
				}
				++(p->iKekkaCnt);
#ifdef _DEBUG_
				printf( "DecodeMeasureDatTxt_NoInq(%d) : p->iKekkaCnt = %d\n", __LINE__, p->iKekkaCnt );
#endif

				if( pKenorder != NULL ) {
					free( pKenorder );
					pKenorder = NULL;
				}
			} else {
#ifdef _DEBUG_
				printf(" >>>>> �ً}�f�[�^����\n");
#endif
				chk = 0;
				/* X-M���ݒ� */
//				if( SetXbarmInf(p,RTN_NG) == RTN_OK ) {
//					SetXbarmData(p);
//					OutputXbarm( p );
//				}
				SetKekkaData_Kinkyu(p,SAIKEN_NASI);
				++(p->iKekkaCnt);
#ifdef _DEBUG_
				printf( "DecodeMeasureDatTxt_NoInq(%d) : p->iKekkaCnt = %d\n", __LINE__, p->iKekkaCnt );
#endif
			}
		}
	/* �W������ */
	}
	else {
		chk = 0;
		memset(&(p->sCtrlkka),0,sizeof(p->sCtrlkka));
		for( iCnt=0; iCnt<iWrk2; iCnt++ ) {
			/* ���ڔԍ� */
			strncpy( sMeasureDatTxt.cItemNum,&aRcvBuf[iWrk+iCnt*20],3 );
			/* �W���Z�x */
			sMeasureDatTxt.cStndrdDensity[0] = aRcvBuf[(iWrk+3)+iCnt*20];
			/* ����l */
			/* CHG E.Osada 2006-07-14 */
			memset(sSpace, 0, sizeof(sSpace));
			memcpy( sSpace, &aRcvBuf[(iWrk+4)+iCnt*20],8 );
			if( !memcmp(sSpace, "////////", 8) ) {
				memset(sMeasureDatTxt.cMeasureVal, ' ', 8);
			} else {
				memcpy( sMeasureDatTxt.cMeasureVal,&aRcvBuf[(iWrk+4)+iCnt*20],8 );
			}
			/* �}�[�N */
			strncpy( sMeasureDatTxt.cMark,&aRcvBuf[(iWrk+12)+iCnt*20],2 );
			/* �J��Ԃ��� */
			sMeasureDatTxt.cRepeatNum[0] = aRcvBuf[(iWrk+15)+iCnt*20];
			/* �v���b�gSEQ�C���N�������g */
			++(p->aPltseq[atoi(sMeasureDatTxt.cDevIdentifNum)]);
			/* ���x�Ǘ����� */
			if( sMeasureDatTxt.cSpecimenDiv[0] == 'C' ) {
				int		cnt;
				int		cnt2;
				char	kmkcd[10][8];
				char	nbkmkcd[8];
				cnt2 = 0;
				memset( nbkmkcd,0,8 );
				strncpy( nbkmkcd,"       ",7 );
				strncpy( nbkmkcd,sMeasureDatTxt.cItemNum,3 );
				memset( kmkcd,0,sizeof(kmkcd) );
				for( cnt=0;cnt<iMechmstNum;cnt++ ) {
					if( strncmp(pMechmst[cnt].nbkmcd,nbkmkcd,7) == 0 ) {
						strncpy( kmkcd[cnt2],pMechmst[cnt].kmkcd,7 );
						++cnt2;
					}
				}

				if ( iCnt == 0 ) {
					/* �t�@�C�����̍쐬 */
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
							aFileNameStr[len+0] = ((loopCnt > 9) ? 'A' : '0') + loopCnt;
							strcat( aFileNameStr,".dat" );
						}
						else {
							break;
						}
					}
				}

				for( cnt=0;cnt<cnt2;cnt++ ) {
					SetCtrlkkaData(p,kmkcd[cnt]);
					/* �R���g���[�����ݒ� */
					if( cnt == 0 ) {
						SetCtrlInf(p,sMeasureDatTxt.cItemNum);

					}

					/* CSV�������� */
					OutputCtrlkka( p );
				}
			/* �L�����u���[�V���� */
			}
			else {
				SetKekkaData_Calb(p);
				++(p->iKekkaCnt);
#ifdef _DEBUG_
				printf( "DecodeMeasureDatTxt_NoInq(%d) : p->iKekkaCnt = %d\n", __LINE__, p->iKekkaCnt );
#endif
			}
		}
		/* ���x�Ǘ����� */
		if( sMeasureDatTxt.cSpecimenDiv[0] == 'C' ) {
			char aWrkBuf2[255];
			/* Index�̍쐬 */
			memset( aWrkBuf2, 0, sizeof(aWrkBuf2) );
			strcpy( aWrkBuf2,aKekkaFolder );
			strcat( aWrkBuf2,"../Index/" );
			strcat( aWrkBuf2,"CT_" );
			strcat( aWrkBuf2,aFileNameStr );
			
			close(open(aWrkBuf2, O_CREAT, 0644));
			return MESSAGE_OK;
		}
	}
	if( aRcvBuf[strlen(aRcvBuf)-5] == ETX ) {
		p->iKekkaNum = p->iKekkaCnt;
		if( chk == 1 ) {
			/* DEL Haga 2006-08-02	�����ύX */
			RealTimeChk( p, p->pSaiken );
		}
		/* CSV�������� */
		OutputKekka( p );
		ClrSaikenInf(p);
	}
	return MESSAGE_OK;
}
/**********************************************************************/
/*                                                                    */
/*   function name : DecodeMeasureDatTxt                              */
/*                                                                    */
/*   purpose : ����f�[�^�e�L�X�g(�Č��₢���킹�L��)�f�R�[�h����     */
/*                                                                    */
/*   data : 2006.01.10                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int DecodeMeasureDatTxt(SOCKET_INF* p,int iType)
{
	int allblknum;
	int iWrk;
	int iWrk2;
	int iAlerm;				/* ADD E.Osada 2006-09-19 */
	int	i;					/* ADD E.Osada 2006-09-19 */
	int iCnt;
	int iCnt2;
	char cXmSkFlg;
	char cWrk[10];
	char jisksbr[32];
	char aFunc[32];

//	int nyubiOrderFlg ;		/* ���n�����t�I�[�_�쐬�ς݃t���O */
//	char ksktkbn;

#ifdef _DEBUG_TRACE_
printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("DecodeMeasureDatTxt\n");
#endif

	iRcvMsgCnt = 0;
	memset( cWrk,0,sizeof(cWrk));
	if( pKenorder != NULL ) {
		free( pKenorder );
		pKenorder = NULL;
	}
	memset(&(p->sCtrlkka),0,sizeof(p->sCtrlkka));
	memset(&sMeasureDatTxt,0,sizeof(sMeasureDatTxt));

	/* �u���b�N�ԍ� */
	memcpy( cWrk, &aRcvBuf[6], 2 );
	iWrk = atoi( cWrk );
#ifdef _DEBUG_
	printf( "�u���b�N�ԍ�:%d\n",iWrk );
#endif
	if( iWrk == 1 ) {
		/* �S�u���b�N�� */
		memcpy( cWrk, &aRcvBuf[4], 2 );
		ClrSaikenInf(p);
		allblknum = atoi( cWrk );
		if( allblknum == 1 ) {
			memcpy( cWrk, &aRcvBuf[8], 3 );
			p->iKekkaNum = atoi( cWrk );
		} else {
			p->iKekkaNum = 19+(atoi(cWrk)-1)*22;
		}
		p->pKekka = malloc(sizeof(Kekka)*(p->iKekkaNum));
		for( iCnt=0;iCnt<p->iKekkaNum;iCnt++ ) {
			memset( &(p->pKekka[iCnt]),0,sizeof(Kekka) );
		}
		p->pSaiken = malloc(sizeof(SaikenInfo)*(p->iKekkaNum));
		for( iCnt=0;iCnt<p->iKekkaNum;iCnt++ ) {
			memset( &(p->pSaiken[iCnt]),0,sizeof(SaikenInfo) );
		}
		p->iOrderNum = 0;
		memset(&(p->sSndorder),0,sizeof(p->sSndorder));
		strncpy( p->cRackNum,&aRcvBuf[83], 8 );
		strncpy( p->cRackPosNum,&aRcvBuf[92], 2 );
		/* ���̎�� */
		sMeasureDatTxt.cSpecimenType[0] = aRcvBuf[115];
		p->sSndorder.racktype[0] = aRcvBuf[115];
	} else {
	}

	/* ���u���ʔԍ� */
	sMeasureDatTxt.cDevIdentifNum[0] = aRcvBuf[3];
	if( (sMeasureDatTxt.cDevIdentifNum[0] < 0x31) && (sMeasureDatTxt.cDevIdentifNum[0] > 0x36) ) {
	}
	/* ������ */
	strncpy( sMeasureDatTxt.cInspectDay,&aRcvBuf[11],8 );
	if( strncmp(sMeasureDatTxt.cInspectDay,"        ",8) == 0 ) {
		memset( sMeasureDatTxt.cInspectDay,0,sizeof(sMeasureDatTxt.cInspectDay) );
		strcpy( sMeasureDatTxt.cInspectDay,"10000101" );
	}
	/* �������� */
	strncpy( sMeasureDatTxt.cInspectTm,&aRcvBuf[19],6 );
	if( strncmp(sMeasureDatTxt.cInspectTm,"      ",6) == 0 ) {
		memset( sMeasureDatTxt.cInspectTm,0,sizeof(sMeasureDatTxt.cInspectTm) );
		strcpy( sMeasureDatTxt.cInspectTm,"000001" );
	}
	/* ���̋敪 */
	sMeasureDatTxt.cSpecimenDiv[0] = aRcvBuf[25];
	/* ID�d�l */
	sMeasureDatTxt.cIdSpec[0] = aRcvBuf[26];

	if( sMeasureDatTxt.cIdSpec[0] == '0' ) {
		switch( sMeasureDatTxt.cSpecimenDiv[0] ) {
/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� --> */
/*** �ً}STAT�Ή� ***/
        case 'I': 		/* ������ */
            iWrk = 13;
            break;
        case 'S': 		/* �ً} */
            iWrk = 3;	/* BM8000�ł�STAT Port���T�|�[�g���Ȃ��ׁAExx�̌Œ蒷���̔ԍ��݂̂ƂȂ� */
            break;
/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� <-- */

		case 'N':
			iWrk2 = 9;
			if( p->cRackNum[0] == ' ' ) {
				ClrSaikenInf(p);
				return MESSAGE_ERR;
			}
			break;

		default:
			ClrSaikenInf(p);
			return MESSAGE_ERR;
		}
		strncpy( sMeasureDatTxt.cIdSpecimenId,&aRcvBuf[27],13 );

/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� --> */
		if (sMeasureDatTxt.cSpecimenDiv[0] == 'N') {
			strncpy( p->sSndorder.seqnum,sMeasureDatTxt.cIdSpecimenId,13 );
		}
/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� <-- */

	} else if( sMeasureDatTxt.cIdSpec[0] == '1' ) {
		if( sMeasureDatTxt.cSpecimenDiv[0] == 'N' ) {
			strncpy( sMeasureDatTxt.cIdSpecimenId,&aRcvBuf[27],13 );
			strncpy( p->sSndorder.seqnum,sMeasureDatTxt.cIdSpecimenId,13 );
			/* TT�ԍ� */
			strncpy( sMeasureDatTxt.cTtNum,&aRcvBuf[40],2 );
			memset( p->cRackNum,0,sizeof(p->cRackNum) );
			strncpy( p->cRackNum,sMeasureDatTxt.cTtNum,2 );
#ifdef _DEBUG_
			printf( "TT�ԍ�:%s\n",sMeasureDatTxt.cTtNum );
#endif
			/* CUP�ԍ� */
			strncpy( sMeasureDatTxt.cCupNum,&aRcvBuf[43],2 );
			memset( p->cRackPosNum,0,sizeof(p->cRackPosNum) );
			strncpy( p->cRackPosNum,sMeasureDatTxt.cCupNum,2 );
#ifdef _DEBUG_
			printf( "CUP�ԍ�:%s\n",sMeasureDatTxt.cCupNum );

/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� --> */
#endif
/*** �ً}STAT�Ή� ***/
		} else if (sMeasureDatTxt.cSpecimenDiv[0] == 'S' ||
	    	       sMeasureDatTxt.cSpecimenDiv[0] == 'I') {
			/* �ً}STAT�̏ꍇ�͏����𒆒f���Ȃ� */
            strncpy( sMeasureDatTxt.cIdSpecimenId,&aRcvBuf[27],13 );
            strncpy( p->sSndorder.seqnum,sMeasureDatTxt.cIdSpecimenId,13 );
            /* TT�ԍ� */
            strncpy( sMeasureDatTxt.cTtNum,&aRcvBuf[40],2 );
            memset( p->cRackNum,0,sizeof(p->cRackNum) );
            strncpy( p->cRackNum,sMeasureDatTxt.cTtNum,2 );
#ifdef _DEBUG_
            printf( "TT�ԍ�:%s\n",sMeasureDatTxt.cTtNum );
#endif
/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� <-- */

			/* CUP�ԍ� */
			strncpy( sMeasureDatTxt.cCupNum,&aRcvBuf[43],2 );
			memset( p->cRackPosNum,0,sizeof(p->cRackPosNum) );
			strncpy( p->cRackPosNum,sMeasureDatTxt.cCupNum,2 );
#ifdef _DEBUG_
            printf( "CUP�ԍ�:%s\n",sMeasureDatTxt.cCupNum );
			printf( "  �ً}�̏ꍇ�����𒆒f���Ȃ�\n");
#endif
		} else {
			ClrSaikenInf(p);
			return MESSAGE_ERR;
		}

/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� --> */
/*** �ً}STAT�Ή� ***/
	} else if (sMeasureDatTxt.cSpecimenDiv[0] == 'S' ||
	           sMeasureDatTxt.cSpecimenDiv[0] == 'I') {
		/* �ً}STAT�̏ꍇ�͏����𒆒f���Ȃ� */
#ifdef _DEBUG_
		printf( "  �ً}�̏ꍇ�����𒆒f���Ȃ�\n");
#endif
/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� <-- */

	} else {
		ClrSaikenInf(p);
		return MESSAGE_ERR;
	}
	/* �u���b�N�����ڐ� */
	memset( cWrk,0,sizeof(cWrk));
	strncpy( cWrk, &aRcvBuf[8], 3 );
	iWrk2 = atoi( cWrk );
#ifdef _DEBUG_
	printf( "�u���b�N�����ڐ�:%d\n",iWrk2 );

	printf( "���b�N�ԍ�:%s\n",p->cRackNum);
	printf( "���b�N�ʒu:%s\n",p->cRackPosNum );
#endif

	/* ���ڔԍ� */
	if( iWrk == 1 ) {
		iWrk = 117;

	} else if( (iWrk >= 2) && (iWrk <= 30) ) {
		iWrk = 51;
	} else {
		//MESSAGE_ERR;
	}
	for( iCnt=0; iCnt<iWrk2; iCnt++ ) {
		/* ���ڔԍ� */
		strncpy( sMeasureDatTxt.cItemNum,&aRcvBuf[iWrk+iCnt*20],3 );
		/* ���͏��� */
		sMeasureDatTxt.cAnalysCond[0] = aRcvBuf[(iWrk+3)+iCnt*20];
		/* ���͏���->���{��ߔ{�� */
		memset( jisksbr,0,sizeof(jisksbr) );
		/* ����l->���f�[�^ */
		strncpy( sMeasureDatTxt.cMeasureVal,&aRcvBuf[(iWrk+4)+iCnt*20],8 );
		/* �}�[�N->���͋@�G���[�X�e�[�^�X */
		strncpy( sMeasureDatTxt.cMark,&aRcvBuf[(iWrk+12)+iCnt*20],2 );
		/* ����u���b�N�ԍ�->���W���[���ԍ� */
		sMeasureDatTxt.cDevIdentifNum[0] = aRcvBuf[(iWrk+19)+iCnt*20];

		/* �v���b�gSEQ�C���N�������g */
		++(p->aPltseq[atoi(sMeasureDatTxt.cDevIdentifNum)]);

		memset(&(p->pKekka[p->iKekkaCnt]),0,sizeof(Kekka));

/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� --> */
/*** �ً}STAT�Ή��̂��� ***/
		/* if( sMeasureDatTxt.cIdSpec[0] == '0' ) { */
		if( sMeasureDatTxt.cIdSpec[0]      == '0' &&
		    sMeasureDatTxt.cSpecimenDiv[0] == 'N' ) {
/*  2.00     2008/09/19     K.Ameno        X-M�Ή����� <-- */

			/* �����I�[�_�[(.dat)�t�@�C���ǂݍ��� */
			if( pKenorder != NULL ) {
				free( pKenorder );
				pKenorder = NULL;
			}
			
			if( ChkNbkmkcd(p,&iCnt2,jisksbr) == RTN_OK ) {

				/* X-M�W�v�t���O���擾('0':�W�v����A'1':�W�v���Ȃ�) */
				cXmSkFlg = GetXmSkFlg(pKenorder[iCnt2].knsgrp, pKenorder[iCnt2].kmkcd, pKenorder[iCnt2].knskisymd);

				/* X-M�W�v����ꍇ('0':�W�v����A'1':�W�v���Ȃ�) */
				if(cXmSkFlg == '0') {
					if( SetXbarmInf(p,iCnt2) == RTN_OK ) {
						SetXbarmData(p);
						OutputXbarm( p );
					}
				}
#ifdef _DEBUG_
				else {
					printf( "DecodeMeasureDatTxt(%d) : pKenorder[iCnt2].knsgrp    = %s\n", __LINE__, pKenorder[iCnt2].knsgrp );
					printf( "DecodeMeasureDatTxt(%d) : pKenorder[iCnt2].kmkcd     = %s\n", __LINE__, pKenorder[iCnt2].kmkcd );
					printf( "DecodeMeasureDatTxt(%d) : cXmSkFlg == '%c' �Ȃ̂ŁAX-M�W�v���s��Ȃ�\n", __LINE__, cXmSkFlg );
				}
#endif

				/* ���ʏ��ݒ�(�I�[�_�[�t�@�C������) */
				SetKekkaData(p,iCnt2,iType);
//				ksktkbn = pKenorder->ksktkbn;
			} else {
				/* ���ʏ��ݒ�(�I�[�_�[�t�@�C���Ȃ�) */
				SetKekkaData_NoOrder(p,iType);
//				ksktkbn = 'A';
			}

			++(p->iKekkaCnt);
#ifdef _DEBUG_
			printf( "DecodeMeasureDatTxt(%d) : p->iKekkaCnt = %d\n", __LINE__, p->iKekkaCnt );
#endif

			if( pKenorder != NULL ) {
				free( pKenorder );
				pKenorder = NULL;
			}
		} else {
			/* X-M���ݒ� */
//			if( SetXbarmInf(p,RTN_NG) == RTN_OK ) {
//				SetXbarmData(p);
//				OutputXbarm( p );
//			}
			/* ���ʏ��ݒ�(�^�[���e�[�u����) */
			SetKekkaData_Kinkyu(p,iType);
			++(p->iKekkaCnt);
#ifdef _DEBUG_
	printf( "DecodeMeasureDatTxt(%d) : p->iKekkaCnt = %d\n", __LINE__, p->iKekkaCnt );
#endif
		}
	}

	if( aRcvBuf[strlen(aRcvBuf)-5] == ETX ) {
//		nyubiOrderFlg = 1 ;
		p->iKekkaNum = p->iKekkaCnt;

		iAlerm = chkDataAlarm( p );

		/* ���A���^�C���`�F�b�N */
		RealTimeChk( p, p->pSaiken );

		/* �l�܂茟�m�G���[�̏ꍇ�S���ڗp��Č������Ƃ��� */
		if( iAlerm == 2 ) {
			for( i=0; i < p->iKekkaNum ;++i ) {
				/* �ۗ��������̃t���O�͕ς��Ȃ� */
				if( p->pKekka[i].knsflg != 'H'){
					p->pKekka[i].knsflg = 'R';
				}
			}
		}
		/* CSV�������� */
		OutputKekka( p );
		for( iCnt2=0; iCnt2<(p->iKekkaNum); iCnt2++ ) {
			/*  �����Č����� */
			/*  �Č��t���O�i�����ϐ��j���P�Ō����H���敪���r�F�đ���܂��͌����񐔂��P�̂��� */
			/*  �� 2006/08/05                                                                */
			/*  �����t���O��'A'�Ō����H���敪���r�F�đ���܂��͌����񐔂��P�̂���            */
			if( p->pKekka[iCnt2].knsflg    == 'A'   &&
				( p->pKekka[iCnt2].ksktkbn == 'S' || p->pKekka[iCnt2].knssu == 1 ) ) {
				strcpy( p->sSndorder.kmkcd[p->iOrderNum], p->pKekka[iCnt2].nbkmkcd );
				/* 2005-08-21 ADD �v�Z���ڂ̊�ߔ{���͑���Ȃ��悤�ɂ��� */
				if( strlen(p->sSndorder.kmkcd[p->iOrderNum]) != 0 ) { /* ADD E.Osada 2006-08-21 */
					if( strcmp(p->pSaiken[iCnt2].KSBR, "0D") == 0 ) {
						strcpy( p->sSndorder.ytiksbr[p->iOrderNum],"Dec" );
					}
					else {
						iWrk2 = atoi(p->pSaiken[iCnt2].KSBR);
						if( strncmp(p->pSaiken[iCnt2].KSBR, aKskbrt[0], 3) == 0 ) {
							strcpy( p->sSndorder.ytiksbr[p->iOrderNum],"1" );
						} else if( strncmp(p->pSaiken[iCnt2].KSBR, aKskbrt[1], 3) == 0 ) {
							strcpy( p->sSndorder.ytiksbr[p->iOrderNum],"2" );
						} else if( strncmp(p->pSaiken[iCnt2].KSBR, aKskbrt[2], 3) == 0 ) {
							strcpy( p->sSndorder.ytiksbr[p->iOrderNum],"3" );
						} else if( strncmp(p->pSaiken[iCnt2].KSBR, aKskbrt[3], 3) == 0 ) {
							strcpy( p->sSndorder.ytiksbr[p->iOrderNum],"4" );
						} else if( strncmp(p->pSaiken[iCnt2].KSBR, aKskbrt[4], 3) == 0 ) {
							strcpy( p->sSndorder.ytiksbr[p->iOrderNum]," " );
						} else {
							strcpy( p->sSndorder.ytiksbr[p->iOrderNum]," " );
						}
					}	/* ADD E.Osada 2006-08-21 */
				}
				++p->iOrderNum;
			} else if( p->pSaiken[iCnt2].flg == '2' ) {
				/* �Č��Ώۂɖ߂�(���ł�'1'���Č��Ώۂ���....) */
				//p->pSaiken[iCnt2].flg == '1';
			}
		}
				
		ClrSaikenInf(p);
	}
	return MESSAGE_OK;
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
int ChkNbkmkcd(SOCKET_INF* p,int* iCnt,char* jisksbr)
{
	int	 ordernum;
	int	 iWrk;
	char cWrkCd[8];
	char aFunc[32];

#ifdef _DEBUG_TRACE_
printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("ChkNbkmkcd\n");
#endif

	ordernum = 0;
	memset( cWrkCd,0,sizeof(cWrkCd) );

	iWrk = GetKenorder( p,ORDER_DAT_1,&ordernum );
	if( iWrk != RTN_OK ) {
		iWrk = GetKenorder( p,ORDER_DAT_2,&ordernum );
	}
	if( iWrk == RTN_OK ) {
		if( GetKmkcd( ordernum,sMeasureDatTxt.cItemNum,cWrkCd ) == RTN_OK ) {
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
void SetKekkaData(SOCKET_INF* p,int iCnt2,int iType)
{
	int iWrk;
	int iCnt;
	char cWrkCd[32];
	char aFunc[32];
	int module;

#ifdef _DEBUG_TRACE_
printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

	printf("SetKekkaData iCnt2 %d;iType %d\n",iCnt2,iType);
#ifdef _DEBUG_
	printf("SetKekkaData\n");
#endif

	memset( &(p->pKekka[p->iKekkaCnt]),0,sizeof(Kekka) );

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
	if( iType == SAIKEN_NASI ) {
		++(p->pKekka[p->iKekkaCnt].knssu);
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
	if( iType == SAIKEN_NASI ) {
		p->pKekka[p->iKekkaCnt].ksktkbn = 'K';
	}
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
	memset( cWrkCd,0,sizeof(cWrkCd) );
	sprintf( cWrkCd ,"%d", atoi(p->cRackNum) );
	strcpy( p->pKekka[p->iKekkaCnt].asyrckid,cWrkCd );
	/* No.20 �A�b�Z�C���b�N�|�W�V�����ݒ� */
	p->pKekka[p->iKekkaCnt].asyrckpos = atoi( p->cRackPosNum );
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
	if( (strncmp(aNa_code,sMeasureDatTxt.cItemNum,3) == 0)
			|| (strncmp(aK_code,sMeasureDatTxt.cItemNum,3) == 0)
			|| (strncmp(aCl_code,sMeasureDatTxt.cItemNum,3) == 0) ) {
		strncpy( p->pKekka[p->iKekkaCnt].bskgok,p->aGouki,2 );
		p->pKekka[p->iKekkaCnt].bskgok[2] = '0';
		p->pKekka[p->iKekkaCnt].bskgok[3] = '0';
		p->pKekka[p->iKekkaCnt].bskgok[4] = '0';
		/* CHG E.Osada 2006-07-14 */
		if( sMeasureDatTxt.cDevIdentifNum[0] == ' ' ) {
			/* ���u���ʔԍ����X�y�[�X�ꍇ�A���@��"1"�Ƃ��� */
			/* ����Ɏ��s�����ꍇ�A���u���ʔԍ����X�y�[�X�̎������� */
			p->pKekka[p->iKekkaCnt].bskgok[5] = '1';
		} else {
			p->pKekka[p->iKekkaCnt].bskgok[5] = sMeasureDatTxt.cDevIdentifNum[0];
		}
	} else {
		strncpy( p->pKekka[p->iKekkaCnt].bskgok,p->aGouki,2 );
		p->pKekka[p->iKekkaCnt].bskgok[2] = '0';
		/* CHG E.Osada 2006-07-14 */
		if( sMeasureDatTxt.cDevIdentifNum[0] == ' ' ) {
			/* ���u���ʔԍ����X�y�[�X�ꍇ�A���@��"1"�Ƃ��� */
			/* ����Ɏ��s�����ꍇ�A���u���ʔԍ����X�y�[�X�̎������� */
			p->pKekka[p->iKekkaCnt].bskgok[3] = '1';
		} else {
			p->pKekka[p->iKekkaCnt].bskgok[3] = sMeasureDatTxt.cDevIdentifNum[0];
		}
		/**/
		p->pKekka[p->iKekkaCnt].bskgok[4] = '0';
		p->pKekka[p->iKekkaCnt].bskgok[5] = '0';
	}
	/* No.28 ���͋@SEQ�ݒ� */
	p->pKekka[p->iKekkaCnt].bskseq = atoi(sMeasureDatTxt.cIdSpecimenId);
	/* No.29 ���͋@�G���[�X�e�[�^�X�ݒ� */
	strncpy( p->pKekka[p->iKekkaCnt].bskerrsts,sMeasureDatTxt.cMark,2 );
	/* No.30 ������� */
	/* ��������ݒ� */
	p->pKekka[p->iKekkaCnt].sktdh[0] = sMeasureDatTxt.cInspectDay[0];
	p->pKekka[p->iKekkaCnt].sktdh[1] = sMeasureDatTxt.cInspectDay[1];
	p->pKekka[p->iKekkaCnt].sktdh[2] = sMeasureDatTxt.cInspectDay[2];
	p->pKekka[p->iKekkaCnt].sktdh[3] = sMeasureDatTxt.cInspectDay[3];
	p->pKekka[p->iKekkaCnt].sktdh[4] = '-';
	p->pKekka[p->iKekkaCnt].sktdh[5] = sMeasureDatTxt.cInspectDay[4];
	p->pKekka[p->iKekkaCnt].sktdh[6] = sMeasureDatTxt.cInspectDay[5];
	p->pKekka[p->iKekkaCnt].sktdh[7] = '-';
	p->pKekka[p->iKekkaCnt].sktdh[8] = sMeasureDatTxt.cInspectDay[6];
	p->pKekka[p->iKekkaCnt].sktdh[9] = sMeasureDatTxt.cInspectDay[7];
	p->pKekka[p->iKekkaCnt].sktdh[10] = ' ';
	/* ��������->������� */
	p->pKekka[p->iKekkaCnt].sktdh[11] = sMeasureDatTxt.cInspectTm[0];
	p->pKekka[p->iKekkaCnt].sktdh[12] = sMeasureDatTxt.cInspectTm[1];
	p->pKekka[p->iKekkaCnt].sktdh[13] = ':';
	p->pKekka[p->iKekkaCnt].sktdh[14] = sMeasureDatTxt.cInspectTm[2];
	p->pKekka[p->iKekkaCnt].sktdh[15] = sMeasureDatTxt.cInspectTm[3];
	p->pKekka[p->iKekkaCnt].sktdh[16] = ':';
	p->pKekka[p->iKekkaCnt].sktdh[17] = sMeasureDatTxt.cInspectTm[4];
	p->pKekka[p->iKekkaCnt].sktdh[18] = sMeasureDatTxt.cInspectTm[5];
	/* No.31 �������ڃR�[�h�ݒ� */
	strncpy( p->pKekka[p->iKekkaCnt].nbkmkcd,sMeasureDatTxt.cItemNum,3 );
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
	if( iType == SAIKEN_NASI ) {
		SetKsbr(p);
	} else {
		strcpy( p->pKekka[p->iKekkaCnt].jisksbr,pKenorder[iCnt2].ytiksbr );
	}
	/* No.44 �ً}�񍐃t���O�擾 */
	p->pKekka[p->iKekkaCnt].kkflg = pKenorder[iCnt2].kkflg;
	/* No.45 �ً}�˗��t���O�擾 */
	p->pKekka[p->iKekkaCnt].kkiriflg = pKenorder[iCnt2].kkiriflg;
	/* No.46 �ً}�˗����b�gNo�擾 */
	p->pKekka[p->iKekkaCnt].kkirilotno = pKenorder[iCnt2].kkirilotno;
	/* No.50 ���f�[�^�ݒ� */
	strncpy( p->pKekka[p->iKekkaCnt].rawdata,sMeasureDatTxt.cMeasureVal,8 );
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
	// ADD Haga 2006-08-02
	p->pKekka[p->iKekkaCnt].ctrlno = GetCtrlInf ( p, p->pKekka[p->iKekkaCnt].nbkmkcd, atoi(sMeasureDatTxt.cDevIdentifNum) ) ;
#ifdef _DEBUG_
	printf( "SetKekkaData(%d) : p->pKekka[p->iKekkaCnt].ctrlno    = %d\n", __LINE__, p->pKekka[p->iKekkaCnt].ctrlno );
#endif
	/* No.77 ����SEQ�ݒ� */
	p->pKekka[p->iKekkaCnt].knsseq = pKenorder[iCnt2].knsseq;
	/* No.78 �����o�b�`�ݒ� */
	p->pKekka[p->iKekkaCnt].bthno = pKenorder[iCnt2].bthno;

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
	/* NO. 90 �␳�t���O */
	int idxKmkmst;
	for ( idxKmkmst = 0 ; idxKmkmst < iKmkmstNum ; idxKmkmst++ ) {
		if ( memcmp ( pKmkmst[idxKmkmst].knsgrp, p->pKekka[p->iKekkaCnt].knsgrp, sizeof ( char ) * 16 ) == 0 && 
		     memcmp ( pKmkmst[idxKmkmst].kmkcd, p->pKekka[p->iKekkaCnt].kmkcd, sizeof ( char ) * 7 ) == 0 ) {
			p->pKekka[p->iKekkaCnt].hsiflg = pKmkmst[idxKmkmst].hsiumflg ; 
			break ;
		}
	}
	/* No.91 ���ʗD��t���O */
	if( sMeasureDatTxt.cMark[1] == 'f' ) {
		p->pKekka[p->iKekkaCnt].kkaysnflg = '1';
	}

/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */  
	GetModule(p->pKekka[p->iKekkaCnt].bskgok, &module);
	GetXSaikenFlg(p, p->pKekka[p->iKekkaCnt].knsgrp, p->pKekka[p->iKekkaCnt].kmkcd, &module, sXbarm_inf);
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */  

}
/**********************************************************************/
/*                                                                    */
/*   function name : SetKekkaData_Kinkyu                              */
/*                                                                    */
/*   purpose : ���ʏ��ݒ�                                           */
/*                                                                    */
/*   data : 2006.03.01                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
void SetKekkaData_Kinkyu(SOCKET_INF* p,int iType)
{
	int		cnt;
	int		flg;
	int iWrk;
	int iCnt;
	char	cWrkCd[32];
	char aFunc[32];
	int		module;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("SetKekkaData_Kinkyu\n");
#endif

	memset( cWrkCd,0,sizeof(cWrkCd) );
	strncpy( cWrkCd,"       ",7 );
	strncpy( cWrkCd,sMeasureDatTxt.cItemNum,3 );
	flg = 0;
	for( cnt=0;cnt<iKinkyuNum;cnt++ ) {
		if( strncmp(cWrkCd,pKinkyu[cnt].nbkmkcd,7) == 0 ) {
			flg = 1;
			break;
		}
	}

	memset( &(p->pKekka[p->iKekkaCnt]),0,sizeof(Kekka) );

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
	p->pKekka[p->iKekkaCnt].kntno[9] = sMeasureDatTxt.cDevIdentifNum[0];
	/* No. 4 ����No�����t���O�ݒ� */
	p->pKekka[p->iKekkaCnt].kntketflg = ' ';
	/* No. 5 �����O���[�v�ݒ� */
	if( flg == 1 ) {
		strncpy( p->pKekka[p->iKekkaCnt].knsgrp,pKinkyu[cnt].knsgrp,16 );
	}
	/* No. 6 ���ڃR�[�h�ݒ� */
	if( flg == 1 ) {
		strncpy( p->pKekka[p->iKekkaCnt].kmkcd,pKinkyu[cnt].kmkcd,7 );
	}
	/* No. 7 �����񐔐ݒ� */
	if( iType == SAIKEN_NASI ) {
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
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** �ً}STAT�̏ꍇ�̈˗��敪��'Z'�Ƃ��� ***/
	p->pKekka[p->iKekkaCnt].irikbn = 'Z';
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
	/* No.11 �����H���敪�ݒ� */
	if( iType == SAIKEN_NASI ) {
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
	/* UPD Nagata 2006-09-01 */
	/*     ���@No�̖��ߍ��݈ʒu��d�����̃`���l���ԍ��݂̂Ŕ��f���� */
	if( (strncmp(aNa_code,sMeasureDatTxt.cItemNum,3) == 0)
			|| (strncmp(aK_code,sMeasureDatTxt.cItemNum,3) == 0)
			|| (strncmp(aCl_code,sMeasureDatTxt.cItemNum,3) == 0) ) {
		strncpy( p->pKekka[p->iKekkaCnt].bskgok,p->aGouki,2 );
		p->pKekka[p->iKekkaCnt].bskgok[2] = '0';
		p->pKekka[p->iKekkaCnt].bskgok[3] = '0';
		p->pKekka[p->iKekkaCnt].bskgok[4] = '0';
		/* CHG E.Osada 2006-07-14 */
		if( sMeasureDatTxt.cDevIdentifNum[0] == ' ' ) {
			p->pKekka[p->iKekkaCnt].bskgok[5] = '1';
		} else {
			p->pKekka[p->iKekkaCnt].bskgok[5] = sMeasureDatTxt.cDevIdentifNum[0];
		}
	} else {
		strncpy( p->pKekka[p->iKekkaCnt].bskgok,p->aGouki,2 );
		p->pKekka[p->iKekkaCnt].bskgok[2] = '0';
		/* CHG E.Osada 2006-07-14 */
		if( sMeasureDatTxt.cDevIdentifNum[0] == ' ' ) {
			p->pKekka[p->iKekkaCnt].bskgok[3] = '1';
		} else {
			p->pKekka[p->iKekkaCnt].bskgok[3] = sMeasureDatTxt.cDevIdentifNum[0];
		}
		p->pKekka[p->iKekkaCnt].bskgok[4] = '0';
		p->pKekka[p->iKekkaCnt].bskgok[5] = '0';
	}
	/* No.28 ���͋@SEQ�ݒ� */
	p->pKekka[p->iKekkaCnt].bskseq = atoi(sMeasureDatTxt.cIdSpecimenId);
	/* No.29 ���͋@�G���[�X�e�[�^�X�ݒ� */
	strncpy( p->pKekka[p->iKekkaCnt].bskerrsts,sMeasureDatTxt.cMark,2 );
	/* No.30 ������� */
	/* ��������ݒ� */
	p->pKekka[p->iKekkaCnt].sktdh[0] = sMeasureDatTxt.cInspectDay[0];
	p->pKekka[p->iKekkaCnt].sktdh[1] = sMeasureDatTxt.cInspectDay[1];
	p->pKekka[p->iKekkaCnt].sktdh[2] = sMeasureDatTxt.cInspectDay[2];
	p->pKekka[p->iKekkaCnt].sktdh[3] = sMeasureDatTxt.cInspectDay[3];
	p->pKekka[p->iKekkaCnt].sktdh[4] = '-';
	p->pKekka[p->iKekkaCnt].sktdh[5] = sMeasureDatTxt.cInspectDay[4];
	p->pKekka[p->iKekkaCnt].sktdh[6] = sMeasureDatTxt.cInspectDay[5];
	p->pKekka[p->iKekkaCnt].sktdh[7] = '-';
	p->pKekka[p->iKekkaCnt].sktdh[8] = sMeasureDatTxt.cInspectDay[6];
	p->pKekka[p->iKekkaCnt].sktdh[9] = sMeasureDatTxt.cInspectDay[7];
	p->pKekka[p->iKekkaCnt].sktdh[10] = ' ';
	/* ��������->������� */
	p->pKekka[p->iKekkaCnt].sktdh[11] = sMeasureDatTxt.cInspectTm[0];
	p->pKekka[p->iKekkaCnt].sktdh[12] = sMeasureDatTxt.cInspectTm[1];
	p->pKekka[p->iKekkaCnt].sktdh[13] = ':';
	p->pKekka[p->iKekkaCnt].sktdh[14] = sMeasureDatTxt.cInspectTm[2];
	p->pKekka[p->iKekkaCnt].sktdh[15] = sMeasureDatTxt.cInspectTm[3];
	p->pKekka[p->iKekkaCnt].sktdh[16] = ':';
	p->pKekka[p->iKekkaCnt].sktdh[17] = sMeasureDatTxt.cInspectTm[4];
	p->pKekka[p->iKekkaCnt].sktdh[18] = sMeasureDatTxt.cInspectTm[5];
	/* No.31 �������ڃR�[�h�ݒ� */
	strncpy( p->pKekka[p->iKekkaCnt].nbkmkcd,sMeasureDatTxt.cItemNum,3 );
	/* No.32 �萫�E��ʃt���O�ݒ� */
	if( flg == 1 ) {
		GetTstrflg( p->pKekka[p->iKekkaCnt].kmkcd,p->pKekka[p->iKekkaCnt].knsgrp,cWrkCd );
		p->pKekka[p->iKekkaCnt].tstrflg = cWrkCd[0];
	}
	/* No.33 �ޗ��R�[�h�ݒ� */
	if( p->sSndorder.racktype[0] == '1' ) {
		strcpy( p->pKekka[p->iKekkaCnt].zrcd,aZrCd[0] );
	} else if( p->sSndorder.racktype[0] == '2' ) {
		strcpy( p->pKekka[p->iKekkaCnt].zrcd,aZrCd[1] );
	}
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
	strncpy( p->pKekka[p->iKekkaCnt].rawdata,sMeasureDatTxt.cMeasureVal,8 );
	/* ADD Haga 2006-08-02 */
	p->pKekka[p->iKekkaCnt].ctrlno = GetCtrlInf ( p, p->pKekka[p->iKekkaCnt].nbkmkcd, atoi(sMeasureDatTxt.cDevIdentifNum) ) ;

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
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** �v���b�g�Ή��𒲍����Ƀo�O���� �v���b�gNO����v���b�gSEQ�ɏC�� ***/
		p->pKekka[p->iKekkaCnt].pltseq = ((sXbarm_inf[iXbarmCnt].iNumCnt - 1) % sXbarm_inf[iXbarmCnt].xmcount) + 1;
#ifdef _DEBUG_
	printf( "SetKekkaData_Kinkyu(%d) : p->pKekka[p->iKekkaCnt].pltseq = %d\n", __LINE__, p->pKekka[p->iKekkaCnt].pltseq );
#endif
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
	}

	/* NO. 90 �␳�t���O */
	int idxKmkmst;
	for ( idxKmkmst = 0 ; idxKmkmst < iKmkmstNum ; idxKmkmst++ ) {
		if ( memcmp ( pKmkmst[idxKmkmst].knsgrp, p->pKekka[p->iKekkaCnt].knsgrp, sizeof ( char ) * 16 ) == 0 && 
		     memcmp ( pKmkmst[idxKmkmst].kmkcd, p->pKekka[p->iKekkaCnt].kmkcd, sizeof ( char ) * 7 ) == 0 ) {
			p->pKekka[p->iKekkaCnt].hsiflg = pKmkmst[idxKmkmst].hsiumflg ; 
			break ;
		}
	}
/* [ start 060420 */
	/* No.91 ���ʗD��t���O */
	if( sMeasureDatTxt.cMark[1] == 'f' ) {
		p->pKekka[p->iKekkaCnt].kkaysnflg = '1';
	}
	/* No.94 �����t���O */
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** �ً}STAT�̏ꍇ�ł����ʓo�^����K�v�����邽�߁A'H'�̐ݒ�����Ȃ� ***/
	p->pKekka[p->iKekkaCnt].knsflg = ' ';

	GetModule(p->pKekka[p->iKekkaCnt].bskgok, &module);
    GetXSaikenFlg(p, p->pKekka[p->iKekkaCnt].knsgrp, p->pKekka[p->iKekkaCnt].kmkcd, &module, sXbarm_inf);
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
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
void SetKekkaData_NoOrder(SOCKET_INF* p,int iType)
{
	int iWrk;
	int iCnt;
	char	cWrkCd[32];
	char aFunc[32];
	int		module;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("SetKekkaData_NoOrder\n");
#endif


	memset( &(p->pKekka[p->iKekkaCnt]),0,sizeof(Kekka) );

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
	p->pKekka[p->iKekkaCnt].kntno[9] = sMeasureDatTxt.cDevIdentifNum[0];
	/* No. 4 ����No�����t���O�ݒ� */
	p->pKekka[p->iKekkaCnt].kntketflg = ' ';
	/* No. 5 �����O���[�v�ݒ� */
	/* No. 6 ���ڃR�[�h�ݒ� */
	memset( cWrkCd,0,sizeof(cWrkCd) );
	GetKmkcd( 0,sMeasureDatTxt.cItemNum,cWrkCd );
	strcpy( p->pKekka[p->iKekkaCnt].kmkcd, cWrkCd );
	/* No. 5 �����O���[�v�ݒ� */
	/* No. 7 �����񐔐ݒ� */
	if( iType == SAIKEN_NASI ) {
		p->pKekka[p->iKekkaCnt].knssu = 2;
	} else {
		p->pKekka[p->iKekkaCnt].knssu = 1;
	}

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
	if( iType == SAIKEN_NASI ) {
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
	/* No.22 �Z�N�V�����R�[�h�ݒ� */
	/* No.24 �T���v�����O�R�[�h�ݒ� */
	/* No.25 ���͋@�敪�ݒ� */
	strcpy( p->pKekka[p->iKekkaCnt].bskkbn,aMekbn );
	/* No.26 ���͋@���C���ݒ� */
	strncpy( p->pKekka[p->iKekkaCnt].bsklne,p->aGouki,2 );
	/* No.27 ���u���ʔԍ�->���͋@���@ */
	/* UPD Nagata 2006-09-01  */
	/* ���@No�̖��ߍ��݈ʒu��d�����̃`���l���ԍ��݂̂Ŕ��f���� */
	if( (strncmp(aNa_code,sMeasureDatTxt.cItemNum,3) == 0)
			|| (strncmp(aK_code,sMeasureDatTxt.cItemNum,3) == 0)
			|| (strncmp(aCl_code,sMeasureDatTxt.cItemNum,3) == 0) ) {
		strncpy( p->pKekka[p->iKekkaCnt].bskgok,p->aGouki,2 );
		p->pKekka[p->iKekkaCnt].bskgok[2] = '0';
		p->pKekka[p->iKekkaCnt].bskgok[3] = '0';
		p->pKekka[p->iKekkaCnt].bskgok[4] = '0';
		/* CHG E.Osada 2006-07-14 */
		if( sMeasureDatTxt.cDevIdentifNum[0] == ' ' ) {
			p->pKekka[p->iKekkaCnt].bskgok[5] = '1';
		} else {
			p->pKekka[p->iKekkaCnt].bskgok[5] = sMeasureDatTxt.cDevIdentifNum[0];
		}
	} else {
		strncpy( p->pKekka[p->iKekkaCnt].bskgok,p->aGouki,2 );
		p->pKekka[p->iKekkaCnt].bskgok[2] = '0';
		/* CHG E.Osada 2006-07-14 */
		if( sMeasureDatTxt.cDevIdentifNum[0] == ' ' ) {
			p->pKekka[p->iKekkaCnt].bskgok[3] = '1';
		} else {
			p->pKekka[p->iKekkaCnt].bskgok[3] = sMeasureDatTxt.cDevIdentifNum[0];
		}
		p->pKekka[p->iKekkaCnt].bskgok[4] = '0';
		p->pKekka[p->iKekkaCnt].bskgok[5] = '0';
	}
	/* No.28 ���͋@SEQ�ݒ� */
	p->pKekka[p->iKekkaCnt].bskseq = atoi(sMeasureDatTxt.cIdSpecimenId);
	/* No.29 ���͋@�G���[�X�e�[�^�X�ݒ� */
	strncpy( p->pKekka[p->iKekkaCnt].bskerrsts,sMeasureDatTxt.cMark,2 );
	/* No.30 ������� */
	/* ��������ݒ� */
	p->pKekka[p->iKekkaCnt].sktdh[0] = sMeasureDatTxt.cInspectDay[0];
	p->pKekka[p->iKekkaCnt].sktdh[1] = sMeasureDatTxt.cInspectDay[1];
	p->pKekka[p->iKekkaCnt].sktdh[2] = sMeasureDatTxt.cInspectDay[2];
	p->pKekka[p->iKekkaCnt].sktdh[3] = sMeasureDatTxt.cInspectDay[3];
	p->pKekka[p->iKekkaCnt].sktdh[4] = '-';
	p->pKekka[p->iKekkaCnt].sktdh[5] = sMeasureDatTxt.cInspectDay[4];
	p->pKekka[p->iKekkaCnt].sktdh[6] = sMeasureDatTxt.cInspectDay[5];
	p->pKekka[p->iKekkaCnt].sktdh[7] = '-';
	p->pKekka[p->iKekkaCnt].sktdh[8] = sMeasureDatTxt.cInspectDay[6];
	p->pKekka[p->iKekkaCnt].sktdh[9] = sMeasureDatTxt.cInspectDay[7];
	p->pKekka[p->iKekkaCnt].sktdh[10] = ' ';
	/* ��������->������� */
	p->pKekka[p->iKekkaCnt].sktdh[11] = sMeasureDatTxt.cInspectTm[0];
	p->pKekka[p->iKekkaCnt].sktdh[12] = sMeasureDatTxt.cInspectTm[1];
	p->pKekka[p->iKekkaCnt].sktdh[13] = ':';
	p->pKekka[p->iKekkaCnt].sktdh[14] = sMeasureDatTxt.cInspectTm[2];
	p->pKekka[p->iKekkaCnt].sktdh[15] = sMeasureDatTxt.cInspectTm[3];
	p->pKekka[p->iKekkaCnt].sktdh[16] = ':';
	p->pKekka[p->iKekkaCnt].sktdh[17] = sMeasureDatTxt.cInspectTm[4];
	p->pKekka[p->iKekkaCnt].sktdh[18] = sMeasureDatTxt.cInspectTm[5];
	/* No.31 �������ڃR�[�h�ݒ� */
	strncpy( p->pKekka[p->iKekkaCnt].nbkmkcd,sMeasureDatTxt.cItemNum,3 );
	/* No.32 �萫�E��ʃt���O�ݒ� */
	/* No.33 �ޗ��R�[�h�ݒ� */
	if( p->sSndorder.racktype[0] == '1' ) {
		strcpy( p->pKekka[p->iKekkaCnt].zrcd,aZrCd[0] );
	} else if( p->sSndorder.racktype[0] == '2' ) {
		strcpy( p->pKekka[p->iKekkaCnt].zrcd,aZrCd[1] );
	}
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
	strncpy( p->pKekka[p->iKekkaCnt].rawdata,sMeasureDatTxt.cMeasureVal,8 );
	/* ADD Haga 2006-08-02 */
	p->pKekka[p->iKekkaCnt].ctrlno = GetCtrlInf ( p, p->pKekka[p->iKekkaCnt].nbkmkcd, atoi(sMeasureDatTxt.cDevIdentifNum) ) ;

	/* No.77 ����SEQ�ݒ� */
	/* No.78 �����o�b�`�ݒ� */
	/* No.79 �v���b�gNo�ݒ� */
	/* No.80 �v���b�gSEQ�ݒ� */

	/* NO. 90 �␳�t���O */
	int idxKmkmst;
	for ( idxKmkmst = 0 ; idxKmkmst < iKmkmstNum ; idxKmkmst++ ) {
		if ( memcmp ( pKmkmst[idxKmkmst].knsgrp, p->pKekka[p->iKekkaCnt].knsgrp, sizeof ( char ) * 16 ) == 0 && 
		     memcmp ( pKmkmst[idxKmkmst].kmkcd, p->pKekka[p->iKekkaCnt].kmkcd, sizeof ( char ) * 7 ) == 0 ) {
			p->pKekka[p->iKekkaCnt].hsiflg = pKmkmst[idxKmkmst].hsiumflg ; 
			break ;
		}
	}
/* [ start 060420 */
	/* No.91 ���ʗD��t���O */
	if( sMeasureDatTxt.cMark[1] == 'f' ) {
		p->pKekka[p->iKekkaCnt].kkaysnflg = '1';
	}
	/* No.94 �����t���O */
	p->pKekka[p->iKekkaCnt].knsflg = 'H';
/* ] end 060420 */

/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** �����Ώۍ��ڃR�[�h�̓}�X�^����擾�ɕύX ***/
	if (ChkKesseiKmkcd(&p->pKekka[p->iKekkaCnt]) == '1') {
		/* �������Ȃ� */
	} else {
/*		sFncSyslog ( TRCKIND_ERROR, "SetKekkaData_NoOrder()", "�I�[�_�[�t�@�C�����擾�ł��܂���ł����B" ) ;*/
	}

	GetModule(p->pKekka[p->iKekkaCnt].bskgok, &module);
    GetXSaikenFlg(p, p->pKekka[p->iKekkaCnt].knsgrp, p->pKekka[p->iKekkaCnt].kmkcd, &module, sXbarm_inf);
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */

}
/**********************************************************************/
/*                                                                    */
/*   function name : SetKekkaData_Calb                                */
/*                                                                    */
/*   purpose : ���ʏ��(�L�����u���[�V����)�ݒ�                       */
/*                                                                    */
/*   data : 2006.03.01                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
void SetKekkaData_Calb(SOCKET_INF* p)
{
	char	cWrkCd[32];
	char aFunc[32];
	int		module;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("SetKekkaData_Calb\n");
#endif

	memset( &(p->pKekka[p->iKekkaCnt]),0,sizeof(Kekka) );

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
	p->pKekka[p->iKekkaCnt].kntno[3] = sMeasureDatTxt.cDevIdentifNum[0];
	p->pKekka[p->iKekkaCnt].kntno[4] = '0';
	p->pKekka[p->iKekkaCnt].kntno[5] = '0';
	struct timeval tv;
	gettimeofday( &tv, NULL );
	struct tm * t = localtime(&(tv.tv_sec));
	sprintf(&(p->pKekka[p->iKekkaCnt].kntno[6]), "%02d%02d%02d%1ld", t->tm_hour, t->tm_min, t->tm_sec, (tv.tv_usec/100000)%10);

	/* No. 4 ����No�����t���O�ݒ� */
	p->pKekka[p->iKekkaCnt].kntketflg = ' ';
	/* No. 6 ���ڃR�[�h�ݒ� */
	memset( cWrkCd,0,sizeof(cWrkCd) );
	GetKmkcd( 0,sMeasureDatTxt.cItemNum,cWrkCd );
	strcpy( p->pKekka[p->iKekkaCnt].kmkcd, cWrkCd );
	/* No. 5 �����O���[�v�ݒ� */
	/* No. 7 �����񐔐ݒ� */
	p->pKekka[p->iKekkaCnt].knssu = atoi(sMeasureDatTxt.cStndrdDensity);
	/* No. 8 �����񐔎}�Ԑݒ� */
	p->pKekka[p->iKekkaCnt].knssueda = atoi( sMeasureDatTxt.cRepeatNum );
	p->pKekka[p->iKekkaCnt].knssueda += 9000;
	/* No. 9 �˗��������敪�ݒ� */
	p->pKekka[p->iKekkaCnt].irihsmkbn = '2';
	/* No.10 �˗��敪�ݒ� */
	p->pKekka[p->iKekkaCnt].irikbn = 'Y';
	/* No.11 �����H���敪�ݒ� */
	p->pKekka[p->iKekkaCnt].ksktkbn = 'A';
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
	// CHG E.Osada 2006-09-12
	if( (strncmp(aNa_code,sMeasureDatTxt.cItemNum,3) == 0)
			|| (strncmp(aK_code,sMeasureDatTxt.cItemNum,3) == 0)
			|| (strncmp(aCl_code,sMeasureDatTxt.cItemNum,3) == 0) ) {
		strncpy( p->pKekka[p->iKekkaCnt].bskgok,p->aGouki,2 );
		p->pKekka[p->iKekkaCnt].bskgok[2] = '0';
		p->pKekka[p->iKekkaCnt].bskgok[3] = '0';
		p->pKekka[p->iKekkaCnt].bskgok[4] = '0';
		if( sMeasureDatTxt.cDevIdentifNum[0] == ' ' ) {
			p->pKekka[p->iKekkaCnt].bskgok[5] = '1';
		} else {
		p->pKekka[p->iKekkaCnt].bskgok[5] = sMeasureDatTxt.cDevIdentifNum[0];
		}
	} else {
		strncpy( p->pKekka[p->iKekkaCnt].bskgok,p->aGouki,2 );
		p->pKekka[p->iKekkaCnt].bskgok[2] = '0';
		if( sMeasureDatTxt.cDevIdentifNum[0] == ' ' ) {
			p->pKekka[p->iKekkaCnt].bskgok[3] = '1';
		} else {
			p->pKekka[p->iKekkaCnt].bskgok[3] = sMeasureDatTxt.cDevIdentifNum[0];
	}
		p->pKekka[p->iKekkaCnt].bskgok[4] = '0';
		p->pKekka[p->iKekkaCnt].bskgok[5] = '0';
	}
	/* No.29 ���͋@�G���[�X�e�[�^�X�ݒ� */
	strncpy( p->pKekka[p->iKekkaCnt].bskerrsts,sMeasureDatTxt.cMark,2 );
	/* No.30 ������� */
	/* ��������ݒ� */
	p->pKekka[p->iKekkaCnt].sktdh[0] = sMeasureDatTxt.cInspectDay[0];
	p->pKekka[p->iKekkaCnt].sktdh[1] = sMeasureDatTxt.cInspectDay[1];
	p->pKekka[p->iKekkaCnt].sktdh[2] = sMeasureDatTxt.cInspectDay[2];
	p->pKekka[p->iKekkaCnt].sktdh[3] = sMeasureDatTxt.cInspectDay[3];
	p->pKekka[p->iKekkaCnt].sktdh[4] = '-';
	p->pKekka[p->iKekkaCnt].sktdh[5] = sMeasureDatTxt.cInspectDay[4];
	p->pKekka[p->iKekkaCnt].sktdh[6] = sMeasureDatTxt.cInspectDay[5];
	p->pKekka[p->iKekkaCnt].sktdh[7] = '-';
	p->pKekka[p->iKekkaCnt].sktdh[8] = sMeasureDatTxt.cInspectDay[6];
	p->pKekka[p->iKekkaCnt].sktdh[9] = sMeasureDatTxt.cInspectDay[7];
	p->pKekka[p->iKekkaCnt].sktdh[10] = ' ';
	/* ��������->������� */
	p->pKekka[p->iKekkaCnt].sktdh[11] = sMeasureDatTxt.cInspectTm[0];
	p->pKekka[p->iKekkaCnt].sktdh[12] = sMeasureDatTxt.cInspectTm[1];
	p->pKekka[p->iKekkaCnt].sktdh[13] = ':';
	p->pKekka[p->iKekkaCnt].sktdh[14] = sMeasureDatTxt.cInspectTm[2];
	p->pKekka[p->iKekkaCnt].sktdh[15] = sMeasureDatTxt.cInspectTm[3];
	p->pKekka[p->iKekkaCnt].sktdh[16] = ':';
	p->pKekka[p->iKekkaCnt].sktdh[17] = sMeasureDatTxt.cInspectTm[4];
	p->pKekka[p->iKekkaCnt].sktdh[18] = sMeasureDatTxt.cInspectTm[5];
	/* No.31 �������ڃR�[�h�ݒ� */
	strncpy( p->pKekka[p->iKekkaCnt].nbkmkcd,sMeasureDatTxt.cItemNum,3 );
	/* No.32 �萫�E��ʃt���O�ݒ� */
	/* No.33 �ޗ��R�[�h�ݒ� */
	if( p->sSndorder.racktype[0] == '1' ) {
		strcpy( p->pKekka[p->iKekkaCnt].zrcd,aZrCd[0] );
	} else if( p->sSndorder.racktype[0] == '2' ) {
		strcpy( p->pKekka[p->iKekkaCnt].zrcd,aZrCd[1] );
	}
	/* No.43 ���{��ߔ{���擾 */
	SetKsbr(p);
	/* No.50 ���f�[�^ */
	strncpy( p->pKekka[p->iKekkaCnt].rawdata,sMeasureDatTxt.cMeasureVal,8 );
	/* No.79 �v���b�gNo�ݒ� */
	/* No.80 �v���b�gSEQ�ݒ� */
/* [ start 060420 */
	/* No.91 ���ʗD��t���O */
	if( sMeasureDatTxt.cMark[1] == 'f' ) {
		p->pKekka[p->iKekkaCnt].kkaysnflg = '1';
	}
/* ] end 060420 */

/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
	GetModule(p->pKekka[p->iKekkaCnt].bskgok, &module);
    GetXSaikenFlg(p, p->pKekka[p->iKekkaCnt].knsgrp, p->pKekka[p->iKekkaCnt].kmkcd, &module, sXbarm_inf);
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */

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

#ifdef _DEBUG_TRACE_
printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("SetKsbr\n");
#endif

/* [ start 060420 068/069 */
	if( sMeasureDatTxt.cAnalysCond[0] == 'M' ) {
		p->pKekka[p->iKekkaCnt].jisksbr[1] = '1';
	} else if( sMeasureDatTxt.cAnalysCond[0] == '1' ) {
		sprintf( &(p->pKekka[p->iKekkaCnt].jisksbr[1]),"%s",aKskbrt[0] );
	} else if( sMeasureDatTxt.cAnalysCond[0] == '2' ) {
		sprintf( &(p->pKekka[p->iKekkaCnt].jisksbr[1]),"%s",aKskbrt[1] );
	} else if( sMeasureDatTxt.cAnalysCond[0] == '3' ) {
		sprintf( &(p->pKekka[p->iKekkaCnt].jisksbr[1]),"%s",aKskbrt[2] );
	} else if( sMeasureDatTxt.cAnalysCond[0] == '4' ) {
		sprintf( &(p->pKekka[p->iKekkaCnt].jisksbr[1]),"%s",aKskbrt[3] );
	} else {
		p->pKekka[p->iKekkaCnt].jisksbr[1] = '1';
	}
	p->pKekka[p->iKekkaCnt].jisksbr[0] = 'B';
/* ] end 060420 068/069 */
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
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("SetCtrlkkaData\n");
#endif

	memset( cWrkCd,0,sizeof(cWrkCd) );
	strncpy( cWrkCd,"       ",7 );
	strncpy( cWrkCd,sMeasureDatTxt.cItemNum,3 );
	flg = 0;
	for( cnt=0;cnt<iCtrlmstNum;cnt++ ) {
		if( (strncmp(cWrkCd,pCtrlmst[cnt].nbkmkcd,7) == 0)
			&& (sMeasureDatTxt.cIdSpecimenId[1] == pCtrlmst[cnt].ctrlsbt[0]) ) {
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
	if( (strncmp(aNa_code,sMeasureDatTxt.cItemNum,3) == 0)
		|| (strncmp(aK_code,sMeasureDatTxt.cItemNum,3) == 0)
		|| (strncmp(aCl_code,sMeasureDatTxt.cItemNum,3) == 0) ) {
		strncpy( p->sCtrlkka.bskgok,p->aGouki,2 );
		p->sCtrlkka.bskgok[2] = '0';
		p->sCtrlkka.bskgok[3] = '0';
		p->sCtrlkka.bskgok[4] = '0';
		if( sMeasureDatTxt.cDevIdentifNum[0] == ' ' ) {
			p->sCtrlkka.bskgok[5] = '1';
		} else {
			p->sCtrlkka.bskgok[5] = sMeasureDatTxt.cDevIdentifNum[0];
		}
	} else {
		strncpy( p->sCtrlkka.bskgok,p->aGouki,2 );
		p->sCtrlkka.bskgok[2] = '0';
		if( sMeasureDatTxt.cDevIdentifNum[0] == ' ' ) {
			p->sCtrlkka.bskgok[3] = '1';
		} else {
			p->sCtrlkka.bskgok[3] = sMeasureDatTxt.cDevIdentifNum[0];
		}
		p->sCtrlkka.bskgok[4] = '0';
		p->sCtrlkka.bskgok[5] = '0';
	}
	/* No. 5 �����O���[�v�ݒ� */
	/* No. 6 ���ڃR�[�h�ݒ� */
	strcpy( p->sCtrlkka.kmkcd, kmkcd );
	/* No. 5 �����O���[�v�ݒ� */
	/* No.7 �������ڃR�[�h�ݒ� */
	strncpy( p->sCtrlkka.nbkmkcd,sMeasureDatTxt.cItemNum,3 );
	/* No.8 �R���g���[��No�ݒ� */
	p->sCtrlkka.ctrlno = GetNowCtrlNo(p, atoi(&sMeasureDatTxt.cIdSpecimenId[2]));
	/* No.9 �R���g���[����ʐݒ� */
	p->sCtrlkka.ctrlsbt[0] = sMeasureDatTxt.cIdSpecimenId[1];
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
	strncpy( p->sCtrlkka.sktti,sMeasureDatTxt.cMeasureVal,8 );
	/* No.21 ���Z�l�ݒ� */
	strncpy( p->sCtrlkka.knzti,sMeasureDatTxt.cMeasureVal,8 );
	/* No.23 ������� */
	/* ��������ݒ� */
	p->sCtrlkka.sktdh[0] = sMeasureDatTxt.cInspectDay[0];
	p->sCtrlkka.sktdh[1] = sMeasureDatTxt.cInspectDay[1];
	p->sCtrlkka.sktdh[2] = sMeasureDatTxt.cInspectDay[2];
	p->sCtrlkka.sktdh[3] = sMeasureDatTxt.cInspectDay[3];
	p->sCtrlkka.sktdh[4] = '-';
	p->sCtrlkka.sktdh[5] = sMeasureDatTxt.cInspectDay[4];
	p->sCtrlkka.sktdh[6] = sMeasureDatTxt.cInspectDay[5];
	p->sCtrlkka.sktdh[7] = '-';
	p->sCtrlkka.sktdh[8] = sMeasureDatTxt.cInspectDay[6];
	p->sCtrlkka.sktdh[9] = sMeasureDatTxt.cInspectDay[7];
	p->sCtrlkka.sktdh[10] = ' ';
	/* ��������->������� */
	p->sCtrlkka.sktdh[11] = sMeasureDatTxt.cInspectTm[0];
	p->sCtrlkka.sktdh[12] = sMeasureDatTxt.cInspectTm[1];
	p->sCtrlkka.sktdh[13] = ':';
	p->sCtrlkka.sktdh[14] = sMeasureDatTxt.cInspectTm[2];
	p->sCtrlkka.sktdh[15] = sMeasureDatTxt.cInspectTm[3];
	p->sCtrlkka.sktdh[16] = ':';
	p->sCtrlkka.sktdh[17] = sMeasureDatTxt.cInspectTm[4];
	p->sCtrlkka.sktdh[18] = sMeasureDatTxt.cInspectTm[5];
	/* No.24 �R���g���[����� */
	if( flg == 1 ) {
		fWrk = atof(sMeasureDatTxt.cMeasureVal) - atof(pCtrlmst[cnt].ctrlx);
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

/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** �v���b�gNO��ێ����邽�߁AXbarM����S�ĕۑ� ***/
/**********************************************************************/
/*                                                                    */
/*   function name : SetXSaikenFlg                                    */
/*                                                                    */
/*   purpose : X-M�Č��t���O�ݒ菈��                                  */
/*                                                                    */
/*   data : 2008.09.18                                                */
/*                                                                    */
/*   produce : Wajima                                                 */
/*                             Copyright(C) 2008 ALL RIGHTS RESERVED  */
/**********************************************************************/
void SetXSaikenFlg(int saiken, char* knsgrp, char* kmkcd, XBARM_INF* xinf)
{
	int   iCnt;
	int   module;

#ifdef _DEBUG_
	printf("%sSetXSaikenFlg\n", Now());
#endif

	module = atoi(sMeasureDatTxt.cDevIdentifNum);

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

/**********************************************************************/
/*                                                                    */
/*   function name : GetXSaikenFlg                                    */
/*                                                                    */
/*   purpose : X-M�Č��t���O�擾����                                  */
/*                                                                    */
/*   data : 2008.09.18                                                */
/*                                                                    */
/*   produce : Wajima                                                 */
/*                             Copyright(C) 2008 ALL RIGHTS RESERVED  */
/**********************************************************************/
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
				/* add 20070725 waj �P�ɐݒ肳��Ă���ꍇ�͂��̂܂� */
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

/**********************************************************************/
/*                                                                    */
/*   function name : OutputXbarmInf                                   */
/*                                                                    */
/*   purpose : X-M���o�͏���                                        */
/*                                                                    */
/*   data : 2008.09.18                                                */
/*                                                                    */
/*   produce : Wajima                                                 */
/*                             Copyright(C) 2008 ALL RIGHTS RESERVED  */
/**********************************************************************/
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
#ifdef _DEBUG_
	printf("%s in.\n", aFunc);
#endif

	sprintf(file, "%sxbarinf_%s.dat", aLogOutFolder, gouki);
#ifdef _DEBUG_
	printf(" > filename : %s\n", file);
#endif

	if ((fp = fopen(file, "w+")) == NULL) {
#ifdef _DEBUG_
		printf("�t�@�C���̃I�[�v���Ɏ��s���܂����B\n");
#endif
		sFncSyslog ( TRCKIND_ERROR, aFunc, "�t�@�C���̃I�[�v���Ɏ��s���܂����B" ) ;
		return RTN_NG;
	}

	for (iCnt = 0; iCnt < XBARM_ITEM_NUM; iCnt++) {
		fwrite(&xinf[iCnt], sizeof(XBARM_INF), 1, fp);
	}

	fclose(fp);

	return RTN_OK;
}

/**********************************************************************/
/*                                                                    */
/*   function name : InputXbarmInf                                    */
/*                                                                    */
/*   purpose : X-M�����͏���                                        */
/*                                                                    */
/*   data : 2008.09.18                                                */
/*                                                                    */
/*   produce : Wajima                                                 */
/*                             Copyright(C) 2008 ALL RIGHTS RESERVED  */
/**********************************************************************/
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
#ifdef _DEBUG_
	printf("%s in.\n", aFunc);
	printf(" > path     : %s\n", aLogOutFolder);
	printf(" > gouki    : %s\n", gouki);
#endif

	sprintf(file, "%sxbarinf_%s.dat", aLogOutFolder, gouki);
#ifdef _DEBUG_
	printf(" > filename : %s\n", file);
#endif

	if ((fp = fopen(file, "r")) == NULL) {
		return RTN_NG;
	}

	for (iCnt = 0; iCnt < XBARM_ITEM_NUM; iCnt++) {
		fread(&xinf[iCnt], sizeof(XBARM_INF), 1, fp);
	}

	fclose(fp);

	return RTN_OK;
}

/**********************************************************************/
/*                                                                    */
/*   function name : DelXbarmInf                                      */
/*                                                                    */
/*   purpose : X-M���폜����                                        */
/*                                                                    */
/*   data : 2008.09.18                                                */
/*                                                                    */
/*   produce : Wajima                                                 */
/*                             Copyright(C) 2008 ALL RIGHTS RESERVED  */
/**********************************************************************/
void DelXbarmInf(char* gouki)
{
	char  file[256];
	char  aFunc[32];

#ifdef _DEBUG_
	printf("%sDelXbarmInf\n", Now());
#endif
    memcpy(aFunc,__func__,sizeof(aFunc));
#ifdef _DEBUG_
	printf("%s in.\n", aFunc);
#endif

	sprintf(file, "%sxbarinf_%s.dat", aLogOutFolder, gouki);
#ifdef _DEBUG_
	printf(" > filename : %s\n", file);
#endif

	/* ���������ŏ����̂ł����ł͉������Ȃ��B���������͎c���Ă��� */
}
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */

int OutputCtrlSeq(SOCKET_INF* p)
{
	char cWrk[256];
	int iCnt;
	FILE *fp;
	char aFunc[32];

#ifdef _DEBUG_
	printf("%sOutputCtrlSeq()\n", Now());
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));
	strcpy( cWrk,aLogOutFolder );
	strcat( cWrk, "ctrlseq_" );
	strcat( cWrk,p->aGouki );
	strcat( cWrk, ".dat" );

    /* add 20070618 waj Xbarm�Č�����̂��߃t���O��ǉ� */
	for (iCnt = 0; iCnt < iXbarmNum; iCnt++) {
		/* �R���g���[�����ς�鎞�A�v�Z�r����Xbarm�͔j������ */
#ifdef _DEBUG_
		printf("�R���g���[�����ς�鎞�A�v�Z�r����Xbarm�͔j������\n");
#endif
		sXbarm_inf[iCnt].saiken   = 0;
		/* add 20070821 waj X-M�����l�ɕ��ϒl��ݒ肷��:�����l�Ƃ��ĕ��ϒl���ݒ肳��Ă���̂ł��̂܂܎g�p */
		/* 0����pltno���N���A����Ă��܂����߁AXMCOUNT�̔{���ɂȂ�悤�������� */
		sXbarm_inf[iCnt].iNumCnt -= (sXbarm_inf[iCnt].iNumCnt % sXbarm_inf[iCnt].xmcount);
		sXbarm_inf[iCnt].xbarmsum = 0;
		/* Add 20070822 waj X-M���v�l�����ł͌v�Z������Ȃ��ꍇ������ */
		sXbarm_inf[iCnt].xmsub = 0;
	}
    OutputXbarmInf(p->aGouki, sXbarm_inf);

	fp = fopen(cWrk,"w");
	if( fp == NULL ) {
#ifdef _DEBUG_
		printf("�t�@�C���̃I�[�v���Ɏ��s���܂����B\n");
#endif
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
	int  iCnt;
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("SetCtrlInf\n");
#endif

#ifdef _DEBUG_
	printf( "SetCtrlInf(%d) : 1 atoi(p->aGouki)                     = %d\n", __LINE__, atoi(p->aGouki) );
	printf( "SetCtrlInf(%d) : 1 atoi(sMeasureDatTxt.cDevIdentifNum) = %d\n", __LINE__, atoi(sMeasureDatTxt.cDevIdentifNum) );
	printf( "SetCtrlInf(%d) : 1 nbkmkcd                             = %s\n", __LINE__, nbkmkcd );
#endif
	for( iCnt=0;iCnt<iCtrlNum;iCnt++ ) {
		if( (sCtrl_inf[iCnt].iGoukiNum == atoi(p->aGouki))
				&& (sCtrl_inf[iCnt].iModuleNum == atoi(sMeasureDatTxt.cDevIdentifNum))
				&& (strncmp(sCtrl_inf[iCnt].nbkmkcd,nbkmkcd,sizeof(sCtrl_inf[iCnt].nbkmkcd)) == 0) ) {
			/* ���ɓo�^�ς݂̏ꍇ�̓f�[�^�X�V */
			sCtrl_inf[iCnt].ctrlno = p->sCtrlkka.ctrlno + 1;
			return RTN_OK;
		}
	}
	/* �V�K���ڂ̏ꍇ�͓o�^ */
	iCnt = iCtrlNum;
	sCtrl_inf[iCnt].iGoukiNum = atoi(p->aGouki);
	sCtrl_inf[iCnt].iModuleNum = atoi(sMeasureDatTxt.cDevIdentifNum);
	strncpy(sCtrl_inf[iCnt].nbkmkcd,nbkmkcd,3);
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
/*   data : 2006.08.02 Add Haga                                       */
/*                                                                    */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int GetCtrlInf(SOCKET_INF* p,char* nbkmkcd, int module )
{
	int  iCnt;
	char aFunc[32];

#ifdef _DEBUG_
	printf("%sGetCtrlInf\n", Now());
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

	for( iCnt=0;iCnt<iCtrlNum;iCnt++ ) {
		if( ( sCtrl_inf[iCnt].iGoukiNum == atoi(p->aGouki)) &&
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
int SetXbarmInf(
		SOCKET_INF* p,							/* ��M�d�� */
		int iCnt								/* */
	)
{
	int		cnt;									/* ���[�v�J�E���^ */
	int		flg;									/* �����t���O	*/
	int		knsseq;									/* ����SEQ */
	int		bskseq;									/* ���͋@SEQ */
	char cWrkCd[8];									/* ���[�N�o�b�t�@ */
	char aFunc[32];
	int  module;
	char cWrkModule[4];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);				/* �f�o�b�O�o�� */
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sSetXbarmInf\n", Now());				/* �f�o�b�O�o�� */
	printf("SetXbarmInf(%d) : iCnt = %d\n", __LINE__, iCnt);
#endif

	memset(cWrkCd,0,sizeof(cWrkCd));				/* ���[�N�o�b�t�@������ */
	memset(cWrkModule,0,sizeof(cWrkModule));

#ifdef _DEBUG_
	printf("SetXbarmInf(%d) : sMeasureDatTxt.cItemNum = %s\n", __LINE__, sMeasureDatTxt.cItemNum);
#endif

	/* ���W���[���ݒ� */
	if( (strncmp(aNa_code,sMeasureDatTxt.cItemNum,3) == 0) ||
		(strncmp(aK_code,sMeasureDatTxt.cItemNum,3) == 0) ||
		(strncmp(aCl_code,sMeasureDatTxt.cItemNum,3) == 0) ) {
		module = atoi(sMeasureDatTxt.cDevIdentifNum);
	} else {
		cWrkModule[0] = sMeasureDatTxt.cDevIdentifNum[0];
		cWrkModule[1] = '0';
		cWrkModule[2] = '0';
		module = atoi(cWrkModule);
	}
#ifdef _DEBUG_
	printf("SetXbarmInf(%d) : ���W���[��No = [%d]\n", __LINE__, module);
#endif

	/* ���ڃR�[�h�̎擾 */
	if( iCnt >= 0 ) {								/* �I�[�_�[���� */
		flg = 1;									/* �����t���OON */
		/* �I�[�_�[�t�@�C������擾 */
		strncpy(cWrkCd,pKenorder[iCnt].kmkcd,7);	/* KENORDER����KMKCD���擾 */
		knsseq = pKenorder[iCnt].knsseq;			/* KENORDER����KNSSEQ���擾 */
	} else {										/* �I�[�_�[�Ȃ� */
		/* �}�X�^�i�t�@�C���j����擾(�ً}STAT����) */
		memset( cWrkCd,0,sizeof(cWrkCd) );			/* ���[�N�o�b�t�@������ */
		strncpy( cWrkCd,"       ",7 );				/* ���p�X�y�[�X�~7��ݒ� */
		strncpy( cWrkCd,sMeasureDatTxt.cItemNum,strlen(sMeasureDatTxt.cItemNum) );
													/* ����f�[�^�e�L�X�g���獀�ڔԍ����擾 */
		flg = 0;									/* �����t���OOFF */
		for( cnt=0;cnt<iKinkyuNum;cnt++ ) {			/* �ً}STAT�������[�v */
			if( strncmp(cWrkCd,pKinkyu[cnt].nbkmkcd,7) == 0 ) {
													/* �ً}STAT���̓������ڃR�[�h�ƈ�v�����H */
				memset( cWrkCd,0,sizeof(cWrkCd) );	/* ���[�N�o�b�t�@������ */
				strncpy( cWrkCd,pKinkyu[cnt].kmkcd,7 );
													/* �ً}STAT����KMKCD���擾 */
				flg = 1;							/* �����t���OON */
				break;
			}
		}
		knsseq = 0;									/* ����SEQ��0�N���A */
	}
	bskseq = atoi(sMeasureDatTxt.cIdSpecimenId);	/* ����f�[�^�e�L�X�g���番�͋@SEQ���擾 */

	if( flg == 1 ) {								/* �����t���OON(�K�v���̎擾���o����)�Ȃ� */
		for( iXbarmCnt=0;iXbarmCnt<iXbarmNum;iXbarmCnt++ ) {	/* xbarinf_XX.dat�ɏo�͂������������[�v */
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
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
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
					return RTN_NG;
				}
				/* X-M���v�l�̎Z�o */
				sXbarm_inf[iXbarmCnt].xbarmsum += CalcXbarm(atof(sMeasureDatTxt.cMeasureVal),X_M_SUM);
				
				/* ���̃v���b�gNO�̍Ō�̃v���b�gSEQ (KMKMST��XMCOUNT = 10 ���Ƃ��āA�v���b�gSEQ = 10 �̏ꍇ) */
				if(	(((sXbarm_inf[iXbarmCnt].iNumCnt - 1) % sXbarm_inf[iXbarmCnt].xmcount) + 1) == sXbarm_inf[iXbarmCnt].xmcount ) {
					/* X-M���ʒl�̎Z�o */
					sXbarm_inf[iXbarmCnt].xbarmkka = CalcXbarm(sXbarm_inf[iXbarmCnt].xbarmsum,X_M_AVE);
#ifdef _DEBUG_
					printf("SetXbarmInf(%d) cWrkCd                            = %s\n",    __LINE__, cWrkCd);
					printf("SetXbarmInf(%d) sXbarm_inf[iXbarmCnt].iNumCnt     = %d\n",    __LINE__, sXbarm_inf[iXbarmCnt].iNumCnt);
					printf("SetXbarmInf(%d) sXbarm_inf[iXbarmCnt].xbarmsum    = %.12f\n", __LINE__, sXbarm_inf[iXbarmCnt].xbarmsum);
					printf("SetXbarmInf(%d) sXbarm_inf[iXbarmCnt].xbarmkka    = %.12f\n", __LINE__, sXbarm_inf[iXbarmCnt].xbarmkka);
					printf("SetXbarmInf(%d) sXbarm_inf[iXbarmCnt].xmsub       = %.12f\n", __LINE__, sXbarm_inf[iXbarmCnt].xmsub);
					printf("SetXbarmInf(%d) atof(sMeasureDatTxt.cMeasureVal)  = %.12f\n", __LINE__, atof(sMeasureDatTxt.cMeasureVal));
#endif
					sXbarm_inf[iXbarmCnt].xbarmsum = 0;
					sXbarm_inf[iXbarmCnt].knsseqed = knsseq;
					sXbarm_inf[iXbarmCnt].bskseqed = bskseq;
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
					sXbarm_inf[0].iXbarmCnt = iXbarmCnt; /* �������ɕK�v�Ȃ����Ȃ̂ŁA0�Ԃ����Ɋi�[ */
    				sXbarm_inf[0].iXbarmNum = iXbarmNum; /* �������ɕK�v�Ȃ����Ȃ̂ŁA0�Ԃ����Ɋi�[ */
					OutputXbarmInf(p->aGouki, sXbarm_inf);

					/*** Xbarm�Č�����̂��߃t���O��ǉ� ***/
					/*** Xbarm���ς������Č��Ȃ� ***/
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
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
					return RTN_OK;
				}
				/* ���̃v���b�gNO�̍ŏ��̃v���b�gSEQ (�v���b�gSEQ = 1 �̏ꍇ) */
				else if( (((sXbarm_inf[iXbarmCnt].iNumCnt - 1) % sXbarm_inf[iXbarmCnt].xmcount) + 1) == 1 ) {
					sXbarm_inf[iXbarmCnt].knsseqst = knsseq;
					sXbarm_inf[iXbarmCnt].bskseqst = bskseq;
				}
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
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
				printf("SetXbarmInf(%d) atof(sMeasureDatTxt.cMeasureVal)  = %.12f\n", __LINE__, atof(sMeasureDatTxt.cMeasureVal));
#endif
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
				return RTN_NG;
			}
		}

		/* �V�K���ڂ̏ꍇ�͓o�^ */
		sXbarm_inf[iXbarmCnt].xmchk = 1;
		iXbarmCnt = iXbarmNum;
		sXbarm_inf[iXbarmCnt].iGoukiNum = atoi(p->aGouki);
		sXbarm_inf[iXbarmCnt].iModuleNum = module;
		strncpy(sXbarm_inf[iXbarmCnt].kmkcd,cWrkCd,7);
		sXbarm_inf[iXbarmCnt].iNumCnt = 1;
		sXbarm_inf[iXbarmCnt].knsseqst = knsseq;
		sXbarm_inf[iXbarmCnt].bskseqst = bskseq;
		if( iCnt >= 0 ) {
			/* �I�[�_�[�t�@�C������擾 */
			GetXmcount( pKenorder[iCnt].kmkcd,pKenorder[iCnt].knsgrp,&sXbarm_inf[iXbarmCnt].xmcount );
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
			/*** Xbarm�̌v�Z�P�ʂ�ύX Xbarm�Ɍ����O���[�v��ǉ� ***/
			strncpy(sXbarm_inf[iXbarmCnt].knsgrp, pKenorder[iCnt].knsgrp, 16);
			/***  X-M�����l�ɕ��ϒl��ݒ肷�� ***/
			sXbarm_inf[iXbarmCnt].xbarmkka = GetXMavg(pKenorder[iCnt].knsgrp, pKenorder[iCnt].kmkcd);
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
		} else {
			GetXmcount( pKinkyu[cnt].kmkcd,pKinkyu[cnt].knsgrp,&sXbarm_inf[iXbarmCnt].xmcount );
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
			/*** Xbarm�̌v�Z�P�ʂ�ύX Xbarm�Ɍ����O���[�v��ǉ� ***/
			strncpy(sXbarm_inf[iXbarmCnt].knsgrp, pKinkyu[cnt].knsgrp, 16);
			/*** X-M�����l�ɕ��ϒl��ݒ肷�� ***/
			sXbarm_inf[iXbarmCnt].xbarmkka = GetXMavg(pKinkyu[cnt].knsgrp, pKinkyu[cnt].kmkcd);

		}
		/*** X-M�����l�ɕ��ϒl��ݒ肷��:�v�Z����xbarmkka���K�v�Ȃ��߂����Ɉړ� ***/
		sXbarm_inf[iXbarmCnt].xbarmsum = CalcXbarm(atof(sMeasureDatTxt.cMeasureVal),X_M_SUM);
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
		if( sXbarm_inf[iXbarmCnt].xmcount <= 0 ) {
			sXbarm_inf[iXbarmCnt].xmcount = PLT_UNIT_DEF;
			sXbarm_inf[iXbarmCnt].xmchk = 0;
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

/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
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
	printf("SetXbarmInf(%d) atof(sMeasureDatTxt.cMeasureVal)  = %.12f\n", __LINE__, atof(sMeasureDatTxt.cMeasureVal));
#endif
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */

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

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sCalcXbarm\n", Now());
#endif
	if( cal == X_M_SUM ) {
		if( (data - sXbarm_inf[iXbarmCnt].xbarmkka) == 0 ) {
			x = 0;
		} else {
			x = ((data - sXbarm_inf[iXbarmCnt].xbarmkka)/fabs(data - sXbarm_inf[iXbarmCnt].xbarmkka)) * sqrt(fabs(data - sXbarm_inf[iXbarmCnt].xbarmkka));
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** X-M���v�l�����ł͌v�Z������Ȃ��ꍇ������ ***/
			sXbarm_inf[iXbarmCnt].xmsub += data - sXbarm_inf[iXbarmCnt].xbarmkka;
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
		}
	} else {
		if( data == 0 ) {
			x = sXbarm_inf[iXbarmCnt].xbarmkka;
		} else {
			x2 = data / (double)sXbarm_inf[iXbarmCnt].xmcount;
			x2 = x2*x2;
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** X-M���v�l�����ł͌v�Z������Ȃ��ꍇ������ ***/
			/* x = sXbarm_inf[iXbarmCnt].xbarmkka + (data/fabs(data) * x2); */
            double x3 = sXbarm_inf[iXbarmCnt].xmsub / (double)sXbarm_inf[iXbarmCnt].xmcount;
            sXbarm_inf[iXbarmCnt].xmsub = 0;
            x = sXbarm_inf[iXbarmCnt].xbarmkka + (x3/fabs(x3) * x2);
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
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

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sSetXbarmData\n", Now());
#endif

	memset(&(p->sXbarm),0,sizeof(Xbarm));

	/* No. 1 �����J�n�� */
	memset( cWrkCd,0,sizeof(cWrkCd) );
	CnvtFromKjnsriymd( sSysknrmst.kjnsriymd,cWrkCd );
	strncpy( p->sXbarm.knskisymd,cWrkCd,strlen(cWrkCd) );
	/* No.2 ���͋@�敪�ݒ� */
	strcpy( p->sXbarm.bskkbn,aMekbn );
	/* No.3 ���͋@���C���ݒ� */
	strncpy( p->sXbarm.bsklne,p->aGouki,2 );
	/* No.4 ���u���ʔԍ�->���͋@���@ */
	if( (strncmp(aNa_code,sMeasureDatTxt.cItemNum,3) == 0)
		|| (strncmp(aK_code,sMeasureDatTxt.cItemNum,3) == 0)
		|| (strncmp(aCl_code,sMeasureDatTxt.cItemNum,3) == 0) ) {
		strncpy( p->sXbarm.bskgok,p->aGouki,2 );
		p->sXbarm.bskgok[2] = '0';
		p->sXbarm.bskgok[3] = '0';
		p->sXbarm.bskgok[4] = '0';
		if( sMeasureDatTxt.cDevIdentifNum[0] == ' ' ) {
			p->sXbarm.bskgok[5] = '1';
		} else {
			p->sXbarm.bskgok[5] = sMeasureDatTxt.cDevIdentifNum[0];
		}
	} else {
		strncpy( p->sXbarm.bskgok,p->aGouki,2 );
		p->sXbarm.bskgok[2] = '0';
		if( sMeasureDatTxt.cDevIdentifNum[0] == ' ' ) {
			p->sXbarm.bskgok[3] = '1';
		} else {
			p->sXbarm.bskgok[3] = sMeasureDatTxt.cDevIdentifNum[0];
		}
		p->sXbarm.bskgok[4] = '0';
		p->sXbarm.bskgok[5] = '0';
	}
	/* No. 5 �����O���[�v�ݒ� */
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
    strncpy( p->sXbarm.knsgrp, sXbarm_inf[iXbarmCnt].knsgrp, 16 );
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
	/* No. 6 ���ڃR�[�h�ݒ� */
	strncpy( p->sXbarm.kmkcd, sXbarm_inf[iXbarmCnt].kmkcd, 7 );
	/* No. 5 �����O���[�v�ݒ� */
	/* No.7 �������ڃR�[�h�ݒ� */
	strncpy( p->sXbarm.nbkmkcd,sMeasureDatTxt.cItemNum,3 );
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
	p->sXbarm.pltsu = (short)sXbarm_inf[iXbarmCnt].xmcount;
	/* No.16 X-M���� */
	sprintf( p->sXbarm.xbarmkka,"%f",sXbarm_inf[iXbarmCnt].xbarmkka );
}

/**********************************************************************/
/*                                                                    */
/*   function name : StatusCtrl                                       */
/*                                                                    */
/*   purpose : ��������                                               */
/*                                                                    */
/*   data : 2005.12.20                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
void StatusCtrl(SOCKET_INF* p)
{
	int		i;
	time_t	tEndTm;
	float	fWrk;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));

	/* �S���@�̃^�C�}�J�E���g */
	if( p == NULL ) {
		tEndTm = time(NULL);
		for( p=sSocketInf.next,i=0; p!=NULL; p=p->next,i++ ) {
			 if( p->fTmOutVal > 0 ) {
				fWrk = difftime(tEndTm,p->tStartTm);
				if( fWrk > p->fTmOutVal ) {
					if( (p->cStatus == STAT_SND_WAIT) || (p->cStatus == STAT_SND_WAIT2) ) {
						if( p->fTmOutVal == TM_WAIT_10 ) {
							p->iSndAgainReq = 1;
							memset( p->aSndAgainBuf,0,sizeof(p->aSndAgainBuf) );
							memcpy( p->aSndAgainBuf,p->aSndAllMsgBuf,sizeof(p->aSndAgainBuf) );
							MakeSndData(p,ENQ);
							SndData(p);
							SetTimer( p, STAT_SND_WAIT, TM_WAIT_5 );
							return;
						} else {
							MakeSndData(p,EOT);
						}
						SndData(p);
					}
					p->fTmOutVal = 0;
					p->cStatus = STAT_IDLE;
				}
			} else if( (p->iSndAgainReq == 1) && (p->cStatus == STAT_IDLE) ) {
				MakeSndData(p,ENQ);
				SndData(p);
				SetTimer( p, STAT_SND_WAIT, TM_WAIT_3 );
			}
		}
		return;
	}

	switch( p->cStatus ) {
	case STAT_IDLE:
		printf("idle���\n");
		if( p->cRcvFrameCtrlChar == ENQ ) {
			MakeSndData(p,ACK);
			SetTimer( p, STAT_RCV_WAIT, TM_WAIT_3 );
		}
		break;
	case STAT_RCV_WAIT:
		printf("Receive Waiting���\n");
		if( p->cRcvFrameCtrlChar == STX ) {
			if( p->cChkRcvData == RCV_DATA_OK ) {
				if( p->cChkRcvMessage == MESSAGE_ERR ) {
					MakeSndData(p,EOT);
					p->fTmOutVal = 0;
					p->cStatus = STAT_IDLE;
				} else {
					SetTimer( p, STAT_RCV_WAIT, TM_WAIT_3 );
				}
				SetTimer( p, STAT_RCV_WAIT, TM_WAIT_3 );
			} else if( p->cChkRcvData == RCV_DATA_NG ) {
				MakeSndData(p,NAK);
				SetTimer( p, STAT_RCV_WAIT, TM_WAIT_3 );
			}
		} else if( p->cRcvFrameCtrlChar == EOT ) {
			if( p->iRcvMsg == MSG_ORDER ) {
				MakeSndData(p,ENQ);
				SetTimer( p, STAT_SND_WAIT, TM_WAIT_5 );
			} else if( p->iRcvMsg == MSG_RESULT ) {
				MakeSndData(p,ENQ);
				SetTimer( p, STAT_SND_WAIT, TM_WAIT_5 );
			} else if( p->iRcvMsg == MSG_ELC ) {
				MakeSndData(p,ENQ);
				SetTimer( p, STAT_SND_WAIT, TM_WAIT_5 );
			} else {
				p->cStatus = STAT_IDLE;
			}
		} else {
			sFncSyslog ( TRCKIND_ERROR, "StatusCtrl()", "STAT_RCV_WAIT���ɒʐM�G���[���������܂����B" ) ;
			printf(" STAT_RCV_WAIT���ɒʐM�G���[���������܂����B\n" );
		}
		break;
	case STAT_SND_WAIT:
		printf("Send Waiting���\n");
		if( p->cRcvFrameCtrlChar == ACK ) {
			p->iSndRetryCnt = 0;	/* �t���[�����M���g���C�J�E���^ */
			MakeSndData(p,STX);
			SetTimer( p, STAT_SND_WAIT2, TM_WAIT_3 );
		} else if( p->cRcvFrameCtrlChar == ENQ ) {
			MakeSndData(p,NAK);
			SetTimer( p, STAT_RCV_WAIT, TM_WAIT_3 );
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
		printf("Send Waiting2���(usleep(5)\n");
		if( p->cRcvFrameCtrlChar == ACK ) {
			p->iSndRetryCnt = 0;
			if( p->cChkNextFrame == FRAME_END ) {
				MakeSndData(p,EOT);
				p->cStatus = STAT_IDLE;
			} else {
				MakeSndData(p,STX);
				SetTimer( p, STAT_SND_WAIT2, TM_WAIT_3 );
			}
		} else if( p->cRcvFrameCtrlChar == NAK ) {
			if( ++(p->iSndRetryCnt) > FRAME_RETRY_MAX ) {
				MakeSndData(p,EOT);
				p->cStatus = STAT_IDLE;
			} else {
				printf( "NAK->���g���C���M!!\n" );
				MakeSndData(p,STX);
				SetTimer( p, STAT_SND_WAIT2, TM_WAIT_3 );
			}
		} else if( p->cRcvFrameCtrlChar == DC1 ) {
				MakeSndData(p,EOT);
				p->cStatus = STAT_IDLE;
		} else if( p->cRcvFrameCtrlChar == EOT ) {
			p->cStatus = STAT_IDLE;
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

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
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

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
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
/*   data : 2005.12.20                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
void MakeSndData(SOCKET_INF* p,char cSnd)
{
	char cWrk;
	char csh;
	char csl;
	int iCnt;
	int iCnt2;
	int iLen;
	int iWrk;
	char aWrk[10];
	char aWrk2[16];
	char cNbkmkcd[8];
	char aFunc[32];
	char aSndWrk[520];
	char snditem[32];
	int reqnum;
	int order;
	int	iKmkNo;			/* ADD E.Osada 2006-08-22 */
	char sKmkNo[10];	/* ADD E.Osada 2006-08-22 */

	int idxKmkmst ;
	char ksjhflg ;
	int nyubiOrderFlg ;		/* ���n�����t�I�[�_�쐬�ς݃t���O */

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf("%sMakeSndData\n", Now());
#endif

	iCnt = 0;
	iCnt2 = 0;
	cWrk = 0;
	iLen = 0;
	iWrk = 0;
	reqnum = 0;
	order = 0;
	nyubiOrderFlg = 0 ;
	if( pKenorder != NULL ) {
		free( pKenorder );
		pKenorder = NULL;
	}

	p->cSndFrameCtrlChar = cSnd;
	if( cSnd == ENQ ) {
		ClearSndInf(p);
		if( (p->iRcvMsg == MSG_NON) && (p->iSndAgainReq == 1) ) {
			printf( "�����N�R���e���V�����I\n" );
			p->iSndAgainReq = 0;
			memcpy( p->aSndAllMsgBuf,p->aSndAgainBuf,sizeof(p->aSndAllMsgBuf) );
		} else if( (p->iRcvMsg == MSG_ORDER) || (p->iRcvMsg == MSG_RESULT)
											 || (p->iRcvMsg == MSG_ELC) ) {
			/* �����I�[�_�[(.dat)�t�@�C���ǂݍ��� */
			iWrk = GetKenorder( p,ORDER_DAT_1,&reqnum );
			if( iWrk != RTN_OK ) {
				iWrk = GetKenorder( p,ORDER_DAT_2,&reqnum );
			}

			if( pKenorder != NULL ) {
				if( p->iRcvMsg == MSG_ORDER ) {
					p->iOrderNum = reqnum;
					for( iCnt=0; iCnt<reqnum; iCnt++ ) {
						/* �������ڃR�[�h�擾 */
						if( GetNbkmkcd( pKenorder[iCnt].kmkcd,cNbkmkcd ) == RTN_OK ) {

							//if( strlen(cNbkmkcd) == 0 ) continue;

							/* �������ڃR�[�h�����݂���ꍇ */
							++order;
							strncpy( p->sSndorder.kmkcd[iCnt2],cNbkmkcd,3 );
							/* �\���ߔ{���擾 */
							if( pKenorder[iCnt].ytiksbr[0] == 'Y' ) {
								strcpy( p->sSndorder.ytiksbr[iCnt2],"M" );
							} else {
								trim(aWrk, &pKenorder[iCnt].ytiksbr[1]);
								if( strncmp(aWrk, aKskbrt[0], 3) == 0 ) {
									strcpy( p->sSndorder.ytiksbr[iCnt2],"1" );
								} else if( strncmp(aWrk, aKskbrt[1], 3) == 0 ) {
									strcpy( p->sSndorder.ytiksbr[iCnt2],"2" );
								} else if( strncmp(aWrk, aKskbrt[2], 3) == 0 ) {
									strcpy( p->sSndorder.ytiksbr[iCnt2],"3" );
								} else if( strncmp(aWrk, aKskbrt[3], 3) == 0 ) {
									strcpy( p->sSndorder.ytiksbr[iCnt2],"4" );
								} else if( strncmp(aWrk, aKskbrt[4], 3) == 0 ) {
									strcpy( p->sSndorder.ytiksbr[iCnt2],"M" );
								} else {
									strcpy( p->sSndorder.ytiksbr[iCnt2],"M" );
								}
							}
							++iCnt2;

							/* ���їn�����t�I�[�_�쐬 */
							if ( nyubiOrderFlg == 0 ) {
								ksjhflg =  '\0' ;
								for ( idxKmkmst = 0 ; idxKmkmst < iKmkmstNum ; idxKmkmst++ ) {
									if ( memcmp ( pKmkmst[idxKmkmst].knsgrp, pKenorder[iCnt].knsgrp, sizeof ( char ) * 16 ) == 0 && 
										 memcmp ( pKmkmst[idxKmkmst].kmkcd, pKenorder[iCnt].kmkcd, sizeof ( char ) * 7 ) == 0 ) {
										ksjhflg = pKmkmst[idxKmkmst].ksjhflg ; 
										break ;
									}
								}
								if ( ksjhflg == '1' ) {
									++order;
									strncpy( p->sSndorder.kmkcd[iCnt2],"268",3 );
									strcpy( p->sSndorder.ytiksbr[iCnt2]," " );
									iCnt2++ ;
	
									++order;
									strncpy( p->sSndorder.kmkcd[iCnt2],"269",3 );
									strcpy( p->sSndorder.ytiksbr[iCnt2]," " );
									iCnt2++ ;
	
									++order;
									strncpy( p->sSndorder.kmkcd[iCnt2],"270",3 );
									strcpy( p->sSndorder.ytiksbr[iCnt2]," " );
									iCnt2++ ;
									nyubiOrderFlg = 1 ;	/* �쐬�ς� */
								} else {
								}
							}
						} else {
						}
					}
					p->iOrderNum = order;
				}
				/* �ޗ��R�[�h�擾 */
				strcpy( p->sSndorder.zrcd,pKenorder[0].zrcd );

				/* ����No */
				strcpy( p->sSndorder.kntno,pKenorder[0].kntno );
				if( pKenorder[0].kntketflg != '9' ) {
					p->sSndorder.kntno[0] = '*';
					p->sSndorder.kntno[1] = '*';
				}
				/* ���ʋ敪�擾 */
				p->sSndorder.sbtkbn[0] = pKenorder[0].sbtkbn;
				/* �N��擾 */
				strcpy( p->sSndorder.age,pKenorder[0].age );
				/* �̎�N�����擾 */
				strcpy( p->sSndorder.ssymd,pKenorder[0].ssymd );
/* [ start 060417 009 */
				/* �e���ʃR�[�h�擾 */
				GetYkcd( pKenorder[0].knsgrp,p->sSndorder.ykcd );
/* ] end 060417 009 */
				if( pKenorder != NULL ) {
					free( pKenorder );
					pKenorder = NULL;
				}
			} else {
				/* ���L����������ƁA�V�[�P���XID���폜���Ă��܂� */
				if( strlen(	p->cRackNum ) != 2 ) {
					/* ���b�N�^�p�̏ꍇ */
					sFncSyslog ( TRCKIND_ERROR, "MakeSndData()", "�I�[�_�[�t�@�C��������܂���B" ) ;
				}
			}
			memset( aWrk2,0,sizeof(aWrk2) );
			if( (p->iRcvMsg == MSG_RESULT) || (p->iRcvMsg == MSG_ELC) ) {
				strcpy( aWrk2,"1" );
			} else {
				strcpy( aWrk2,"0" );
			}
			if( p->iOrderNum <= 0 ) {
				strcpy( aWrk2,"2" );
			}
			p->iRcvMsg = MSG_NON;

			/* �S�u���b�N�� */
			if( p->iOrderNum <= 104 ) {
				strncpy( sItemSelInstTxt_NoVal.cAllBlockNum, "01", 2 );
			} else if( p->iOrderNum <= 221 ) {
				strncpy( sItemSelInstTxt_NoVal.cAllBlockNum, "02", 2 );
			} else if( p->iOrderNum <= 338 ) {
				strncpy( sItemSelInstTxt_NoVal.cAllBlockNum, "03", 2 );
			} else if( p->iOrderNum <= 455 ) {
				strncpy( sItemSelInstTxt_NoVal.cAllBlockNum, "04", 2 );
			} else if( p->iOrderNum <= 572 ) {
				strncpy( sItemSelInstTxt_NoVal.cAllBlockNum, "05", 2 );
			} else {
				strncpy( sItemSelInstTxt_NoVal.cAllBlockNum, "06", 2 );
			}
			p->iSndBlockNum = atoi( sItemSelInstTxt_NoVal.cAllBlockNum );

			for( iCnt=0; iCnt<p->iSndBlockNum; iCnt++ ) {
				memset(aSndWrk,0,sizeof(aSndWrk));
				/* �t���[���ԍ� */
				aSndWrk[0] = ((iCnt+1)%8)+0x30;
				/* �e�L�X�g��ʁE���u���ʔԍ�(���g�p) */
				strncat( aSndWrk,"O ",2 );
				/* �S�u���b�N�� */
				strncat( aSndWrk, sItemSelInstTxt_NoVal.cAllBlockNum, 2 );
				/* �u���b�N�ԍ� */
				sprintf( sItemSelInstTxt_NoVal.cBlockNum,"%02d",iCnt+1 );
				strncat( aSndWrk, sItemSelInstTxt_NoVal.cBlockNum, 2 );
				/* �u���b�N�����ڐ� */
				if( iCnt <= 0 ) {
					if( p->iOrderNum >= 104 ) {
						sprintf( sItemSelInstTxt_NoVal.cItemNumInBlk, "%03d", 104 );
					} else {
						sprintf( sItemSelInstTxt_NoVal.cItemNumInBlk, "%03d", p->iOrderNum );
					}
				} else {
					if( p->iOrderNum >= 104+117*iCnt ) {
						sprintf( sItemSelInstTxt_NoVal.cItemNumInBlk, "%03d", 117 );
					} else {
						sprintf( sItemSelInstTxt_NoVal.cItemNumInBlk, "%03d", p->iOrderNum-(104+117*(iCnt-1)) );
					}
				}
				strncat( aSndWrk, sItemSelInstTxt_NoVal.cItemNumInBlk, 3 );
				if( iCnt <= 0 ) {
					/* ���̋敪�E�o�^��� */
					strcat( aSndWrk, "N" );
					strcat( aSndWrk,aWrk2 );
					/* ����ID */
					strncat( aSndWrk,p->sSndorder.seqnum,13 );
					iLen = strlen( p->cRackNum );
					if( iLen == 2 ) {
						/* �^�[���e�[�u���̏ꍇ */
						/* �ʒu�ԍ� */
						strncat( aSndWrk, p->cRackNum, 2 );
						iLen = strlen(aSndWrk);
						aSndWrk[iLen] = '-';
						strncat( aSndWrk, p->cRackPosNum, 2 );
						strcat( aSndWrk,"      " );
						/* �R�����g�P */
						strcpy( aWrk2,"                " );
//						strcpy( aWrk2,p->sSndorder.kntno );
						strcat( aSndWrk,aWrk2 );
						/* �R�����g�Q */
						strcat( aSndWrk,"                " );
					} else {
						/* ���b�N�^�p�̏ꍇ */
						/* �ʒu�ԍ� */
						strcat( aSndWrk,"           ");
						/* �R�����g�P */
						strcpy( aWrk2,"                " );
						strncpy( aWrk2,p->sSndorder.kntno,strlen(p->sSndorder.kntno) );
						strcat( aSndWrk,aWrk2 );
						/* �R�����g�Q */
						iLen = strlen(aSndWrk);
						iWrk = atoi(p->cRackNum);
						sprintf( &aSndWrk[iLen],"%08d",iWrk );
						strcat( aSndWrk,"-" );
						strncat( aSndWrk, p->cRackPosNum, 2 );
						strcat( aSndWrk,"     ");
					}
					/* ���ʐݒ�*/
					memset( snditem,0,sizeof(snditem) );
					CnvtFromSbtkbn( p->sSndorder.sbtkbn,snditem );
					strncat( aSndWrk,snditem,1 );
					/* �N��ݒ�*/
					memset( snditem,0,sizeof(snditem) );
					CnvtFromAge( p->sSndorder.age,snditem );
					strncat( aSndWrk,snditem,3 );
					/* �̌���(�N����)�ݒ�*/
					memset( snditem,0,sizeof(snditem) );
					CnvtFromSsymd( p->sSndorder.ssymd,snditem );
					strncat( aSndWrk,snditem,8 );
					strcat( aSndWrk," 1.0");
					/* ���̎�ʐݒ�*/
					memset( snditem,0,sizeof(snditem) );
					CnvtFromZrcd( p->sSndorder.zrcd,snditem );
					strncat( aSndWrk,snditem,1 );
					/* �e���ʐݒ�*/
/* [ start 060417 009 */
					memset( snditem,0,sizeof(snditem) );
					CnvtFromYkcd( p->sSndorder.ykcd,snditem );
					strncat( aSndWrk,snditem,1 );
/* ] end 060417 009 */
				} else {
					/* �\�� */
					strncat( aSndWrk, "  ", 2 );
					/* ����ID */
					strncat( aSndWrk,p->sSndorder.seqnum,13 );
					iLen = strlen( p->cRackNum );
					if( iLen == 2 ) {
						/* �^�[���e�[�u���̏ꍇ */
						strncat( aSndWrk, p->cRackNum, 2 );
						iLen = strlen(aSndWrk);
						aSndWrk[iLen] = '-';
						strncat( aSndWrk, p->cRackPosNum, 2 );
						strcat( aSndWrk,"      ");
					} else {
						/* ���b�N�^�p�̏ꍇ */
						strcat( aSndWrk,"           ");
					}
				}
				/* �˗����� */
				if( p->iOrderNum > 0 ) {
					if( iCnt <= 0 ) {
						iCnt2 = 0;
					} else {
						iCnt2 = 104+117*(iCnt-1);
					}
					iKmkNo = 0; 	// ADD E.Osada 2006-08-22
					memset(sKmkNo, 0, sizeof(sKmkNo));
					for( ; iCnt2<p->iOrderNum; iCnt2++ ) {
						if( iCnt2 >= 104+117*iCnt ) {
							break;
						}
						/* ���ڔԍ��ݒ� */
						memset( snditem,0,sizeof(snditem) );
						/* ADD E.Osada 2006-08-17 �������ڃR�[�h���Ȃ��ꍇ�͖��� */
						if( strlen(p->sSndorder.kmkcd[iCnt2]) == 0 ) {
							continue;
						}
						++iKmkNo;
						strncat( aSndWrk,p->sSndorder.kmkcd[iCnt2],3 );
						strcat( aSndWrk,p->sSndorder.ytiksbr[iCnt2] );
					}
					/* ADD E.Osada 2006-08-22 */
					sprintf(sKmkNo, "%03d", iKmkNo);
					memcpy(&aSndWrk[7], sKmkNo, 3);
				}
				iLen = strlen(aSndWrk);
				/* �\�� */
				aSndWrk[iLen] = ' ';
				strcpy(p->aSndAllMsgBuf[iCnt],aSndWrk);
			}
		} else {
			p->cSndFrameCtrlChar = 0xff;
			p->cSndDataReq = NO_SND_REQ;
			return;
		}
	} else if( cSnd == STX ) {
		if( p->iSndRetryCnt != 0 ) {
			p->cSndDataReq = SND_REQ;
			return;
		}
		memset(p->aSndTmpBuf,0,sizeof(p->aSndTmpBuf));				/* ���M�f�[�^�ꎞ�o�b�t�@�N���A */
		memset(aWrk,0,sizeof(aWrk));
		if( p->cChkNextFrame == FRAME_END ) {
			p->iSndBlockCnt = 0;
		} else {
			++p->iSndBlockCnt;
		}
		iLen = strlen( p->aSndAllMsgBuf[p->iSndBlockCnt] );
		memcpy( p->aSndTmpBuf,p->aSndAllMsgBuf[p->iSndBlockCnt],iLen );

		if( p->iSndBlockCnt < p->iSndBlockNum-1 ) {
			p->aSndTmpBuf[iLen] = ETB;
			p->cChkNextFrame = FRAME_CONTINUE;
			p->cSndFrameSeqNum = 1;
		} else {
			p->aSndTmpBuf[iLen] = ETX;
			p->cChkNextFrame = FRAME_END;
	}
		for( iCnt=0; iCnt<(iLen+1); iCnt++ ) {
			if( (p->aSndTmpBuf[iCnt] == ETX) || (p->aSndTmpBuf[iCnt] == ETB) ) {
				cWrk += p->aSndTmpBuf[iCnt];
				break;
			}
			cWrk += (p->aSndTmpBuf[iCnt]);
		}
		csh = ((cWrk >> 4) & 0x0f);
		if( csh <= 0x09 ) {
			csh += 0x30;
		} else {
			csh += 0x37;
		}
		csl = (cWrk & 0x0f);
		if( csl <= 0x09 ) {
			csl += 0x30;
		} else {
			csl += 0x37;
		}
		p->aSndTmpBuf[++iLen] = csh;
		p->aSndTmpBuf[++iLen] = csl;
		p->aSndTmpBuf[++iLen] = CR;
		p->aSndTmpBuf[++iLen] = LF;
	}
	p->cSndDataReq = SND_REQ;

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
#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
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
	char cWrk[16];
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "CnvtFromKmkcd()\n" );
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
		cTo[0] = ' ';
		cTo[1] = cWrk[0];
		cTo[2] = cWrk[1];
	} else if( iCnt2 == 1 ) {
		cTo[0] = ' ';
		cTo[1] = ' ';
		cTo[2] = cWrk[0];
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

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "CnvtFromZrcd()\n" );
#endif

/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
    if((memcmp(cFrom, aHnkCd[1], strlen(aHnkCd[1])) == 0) ||
       (memcmp(cFrom, aHnkCd[2], strlen(aHnkCd[2])) == 0)) {
#ifdef _DEBUG_
	printf("CnvtFromZrcd : �A���[�h(%s)\n", cFrom);
#endif
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
		cTo[0] = '2';
	} else {
		cTo[0] = '1';
	}

	return 0;
}
/* [ start 060417 009 */
/**********************************************************************/
/*                                                                    */
/*   function name : CnvtFromYkcd                                     */
/*                                                                    */
/*   purpose : .�e��R�[�h�ϊ�����                                    */
/*                                                                    */
/*   data : 2006.04.17                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
int CnvtFromYkcd( char* cFrom, char* cTo )
{
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "CnvtFromYkcd()\n" );
#endif

	if( strcmp( cFrom,aYkcd[0] ) == 0 ) {
		cTo[0] = '1';
	} else if( strcmp( cFrom,aYkcd[1] ) == 0 ) {
		cTo[0] = '2';
	} else if( strcmp( cFrom,aYkcd[2] ) == 0 ) {
		cTo[0] = '3';
	} else if( strcmp( cFrom,aYkcd[3] ) == 0 ) {
		cTo[0] = '4';
	} else if( strcmp( cFrom,aYkcd[4] ) == 0 ) {
		cTo[0] = '5';
	} else if( strcmp( cFrom,aYkcd[5] ) == 0 ) {
		cTo[0] = '6';
	} else if( strcmp( cFrom,aYkcd[6] ) == 0 ) {
		cTo[0] = '7';
	} else if( strcmp( cFrom,aYkcd[7] ) == 0 ) {
		cTo[0] = '8';
	} else {
		cTo[0] = '1';
	}

	return 0;
}
/* ] end 060417 009 */
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

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "CnvtFromYtiksbr()\n" );
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

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "CnvtFromSbtkbn()\n" );
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

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "CnvtFromAge()\n" );
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
		cTo[0] = ' ';
		cTo[1] = cWrk[0];
		cTo[2] = cWrk[1];
	} else if( iCnt2 == 1 ) {
		cTo[0] = ' ';
		cTo[1] = ' ';
		cTo[2] = cWrk[0];
	} else {
		cTo[0] = ' ';
		cTo[1] = ' ';
		cTo[2] = ' ';
	}

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

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "CnvtFromSsymd()\n" );
#endif

	if( strncmp(cFrom,INIT_DATE,10) == 0 || strlen(cFrom) != 10 ) {
		strncpy( cFrom,"          ",10 );
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

	return 0;
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

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "CnvtFromKjnsriymd()\n" );
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
int GetNowCtrlNo(SOCKET_INF *p, int Seq)
{
	int lCnt;
	struct tm sTm;
	time_t t_Kns;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memset(&sTm, 0, sizeof(sTm));
	sTm.tm_sec = (sMeasureDatTxt.cInspectTm[4]-'0') * 10 + (sMeasureDatTxt.cInspectTm[5]-'0');				/* Seconds. 	[0-60] (1 leap second) */
	sTm.tm_min = (sMeasureDatTxt.cInspectTm[2]-'0') * 10 + (sMeasureDatTxt.cInspectTm[3]-'0');				/* Minutes. 	[0-59] */
	sTm.tm_hour = (sMeasureDatTxt.cInspectTm[0]-'0') * 10 + (sMeasureDatTxt.cInspectTm[1]-'0');				/* Hours.		[0-23] */
	sTm.tm_mday = (sMeasureDatTxt.cInspectDay[6]-'0') * 10 + (sMeasureDatTxt.cInspectDay[7]-'0');			/* Day. 		[1-31] */
	sTm.tm_mon = (sMeasureDatTxt.cInspectDay[4]-'0') * 10 + (sMeasureDatTxt.cInspectDay[5]-'0') - 1;		/* Month.		[0-11] */
	sTm.tm_year = ((sMeasureDatTxt.cInspectDay[0]-'0') * 1000 + (sMeasureDatTxt.cInspectDay[1]-'0') * 100
				 + (sMeasureDatTxt.cInspectDay[2]-'0') * 10 + (sMeasureDatTxt.cInspectDay[3]-'0')) - 1900; 	/* Year - 1900.  */
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
#ifdef _DEBUG_
		printf("�R���g���[���ԍ� ����I�[�o�[�m�F�p %d\n", p->CtrlInfo.cnt);
#endif
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

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "MakeFileName()\n" );
#endif

	memset( aFileNameStr, 0, sizeof(aFileNameStr) );

#ifdef _DEBUG_
	printf( "���b�NID:%s\n",aRackNum );
	printf( "���b�N�ʒu:%s\n",aPosNum );
#endif

	/* ADD Nagata 2006-08-31 �t�@�C�����̃X�^���v�����𑝌����� */
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
void _sFncSyslog (LOG_TRCKIND piPri, char * pcFncname,char * pcMsg ,char * pcErrCode, char * pcExeFlg, char * file, long lineno) 
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
	plm.lPid = getpid() ;					// �v���Z�XID
	strncpy(plm.pcAppName, "DD201", 32);
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
static int sFncShmCrt ( shm_Key )
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
static int sFncShmGet ( shm_Key, pshmData )
int				shm_Key ;
int				*pshmData ;
{
	int		*shmData ;

	/* �A�^�b�` */
	shmData = ( int * ) shmat ( shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		/* �ُ�I��	LOG */
		sFncSyslog ( TRCKIND_ERROR, "shmat()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}

	/* �l�ݒ� */
	*pshmData = *shmData ;

	/* �f�^�b�`	 */
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
static int sFncShmDel ( shm_Key )
int			shm_Key ;
{
	/* �폜 */
	if ( shmctl ( shm_Id, IPC_RMID, NULL) < 0 ) {
		/* �ُ�I��	LOG */
		sFncSyslog ( TRCKIND_ERROR, "shmctl()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}	

/******************************************************************************/
/*  �� �� ���@�FchkDataAlarm()				 								  */
/*  �@�\�T�v�@�F�f�[�^�A���[���擾����						  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �FSOCKET_INF *   	�v���O�������\����						  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/*	���l      �FADD Haga 2006-08-02											  */
/******************************************************************************/
int chkDataAlarm( SOCKET_INF *p )
{
    char    buf1[128], buf2[128]; 
    Kskbrmst    Key;
	int	iRet, KekkaCnt;
	char cAlCode ;
	int iDenkaiFlg;		/* ADD E.OSADA 2006-09-20 */

	p->iOrderNum = 0;
    memset(buf1, 0, sizeof(buf1));
    memset(buf2, 0, sizeof(buf2));
    memset(&Key, 0,sizeof(Kskbrmst));
    memcpy(Key.bskkbn, "BIOM", 4);
	for( KekkaCnt=0; KekkaCnt < p->iKekkaNum ;++KekkaCnt ) {
		/* ADD E.Osada 2006-08-22 */
		memset(buf1, 0, sizeof(buf1));
		trim(buf1,  p->pKekka[KekkaCnt].kmkcd);
		if( buf1[0] == '\0' ) continue;

    	memcpy(Key.knsgrp, p->pKekka[KekkaCnt].knsgrp, 16);
    	memcpy(Key.kmkcd,  p->pKekka[KekkaCnt].kmkcd, 7);
    	GetKskRitu(&Key, buf1, buf2);

		/* ADD E.Osada 2006-09-20 */
		if( (memcmp(aNa_code, p->pKekka[KekkaCnt].nbkmkcd, 3) == 0)
			|| (memcmp(aK_code, p->pKekka[KekkaCnt].nbkmkcd, 3) == 0)
			|| (memcmp(aCl_code, p->pKekka[KekkaCnt].nbkmkcd, 3) == 0) ) {
			iDenkaiFlg = 1;
		} else {
			iDenkaiFlg = 0;
		}
		/* CHG Nagata 2006-10-05 'A'�N���b�g�G���[��p��Č��ɕύX */
		cAlCode = p->pKekka[KekkaCnt].bskerrsts[1] ;
		switch(cAlCode) {
			case 'S' :    /* ���è�װ */
			case 'r' :    /* ����s�� */
			case 't' :    /* ��߉t�s�� */
			case 'M' :    /* �~�b�N�X�G���[ */
			case 'Q' :    /* �t�ʈُ� */
			case 'G' :    /* �N���b�V�� */
			case 'F' :    /* ���x�ُ� */
			case 'c' :    /* �L�����u�~�X�}�b�` */
			case 'n' :    /* �L���߲�Đ��ُ� */
			case 'N' :    /* �����ݸ�ُ� */
			case '/' :    /* �I�[�o�[�t���[ */
			case 'V' :    /* �P����Ԏ�g���ُ� */
			case 'v' :    /* �P����ԕ��g���ُ� */
			case 'W' :    /* �Q����Ԏ�g���ُ� */
			case 'w' :    /* �Q����ԕ��g���ُ� */
			case 'X' :    /* �R����Ԏ�g���ُ� */
			case 'x' :    /* �R����ԕ��g���ُ� */
			case 'i' :    /* �L�����Z�� */
			case 'J' :    /* ����⏕ */
			case 'O' :    /* �L�����[�I�[�o�[ */
			case 'f' :    /* ��������f�[�^ */
			case 'q' :    /* �͈͋��E�f�[�^ */
			case 'a' :    /* ����f�[�^�Ȃ� */
			case 'B' :	  /* ��߃J�b�v�c�t */
			case 'T' :	  /* �T�[�~�X�^�ُ� */
			case 'I' :    /* ID�G���[ */
				/*---------------------------------------------------------------*/
				/* �����Č��@�Č��ɃA���[�����Ȃ���΍Č��l�@�Č��ς݃R�����g�Ȃ�*/
				/*---------------------------------------------------------------*/
				iRet = 1;
				p->pSaiken[KekkaCnt].flg = 1;			/* �����Č� */
				p->pKekka[KekkaCnt].knsflg = 'A';
				/* CHG E.Osada 2006-09-19 */
                p->pKekka[KekkaCnt].yobiflg01 = '2';	/* �G���[�t���O ADD 2006.08.28 Nagata */
				strcpy(p->pSaiken[KekkaCnt].KSBR, "1");
				break;
			case 'u' :    /* �z���x���E */
			case 'd' :    /* �z���x���E */
			case '*' :    /* ���U�ُ� */
				/* CHG E.Osada 2006-09-20 */
				iRet = 1;
				p->pSaiken[KekkaCnt].flg = 1;   		/* �����Č� */
				p->pKekka[KekkaCnt].knsflg = 'A';
                p->pKekka[KekkaCnt].yobiflg01 = '2';	/* �G���[�t���O  */
				if( iDenkaiFlg == 1 ) {
					/* �d�����̏ꍇ��1�{ */
					strcpy(p->pSaiken[KekkaCnt].KSBR, "1");
				} else {
					/* �d�����ȊO�̏ꍇ��10�{ */
					strcpy(p->pSaiken[KekkaCnt].KSBR, "10");
				}
				break;
			case 'U' :    /* �z���x���E */
			case 'D' :    /* �z���x���E */
			case 'P' :    /* ��ۿް� */
			case 'z' :    /* �s�ǃf�[�^ */
				/*---------------------------------------------------------------*/
				/* �ō���ߔ{���������s�Ȃ�                                      */
				/*---------------------------------------------------------------*/
				iRet = 1;
				p->pSaiken[KekkaCnt].flg = 1;			/* �����Č� */
				p->pKekka[KekkaCnt].knsflg = 'A';
				/* CHG E.Osada 2006-09-19 */
                p->pKekka[KekkaCnt].yobiflg01 = '2';	/* �G���[�t���O ADD 2006.08.28 Nagata */
				/* 10�{���Z�b�g */
				strcpy(p->pSaiken[KekkaCnt].KSBR, "10");
				break;
			case 's' :    /* ����ٕs�� */
			case 'A' :    /* �N���b�g�G���[ */
				/*---------------------------------------------------------------*/
				/* �p��Č��Ƃ���                                                */
				/*---------------------------------------------------------------*/
                iRet = 2;
                p->pSaiken[KekkaCnt].flg = 2;			/* �p��Č� */
                p->pKekka[KekkaCnt].knsflg = 'R';
                p->pKekka[KekkaCnt].yobiflg01 = '2';	/*�G���[�t���O ADD 2006.08.28 Nagata */
                break;

			default:
				iRet = 0;
				break;
		}
	}
	
	return( iRet );
}

/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/**********************************************************************/
/*                                                                    */
/*   function name : ChkKesseiKmkcd                                   */
/*                                                                    */
/*   purpose : �����`�F�b�N�Ώۍ��ڃR�[�h�m�F����                     */
/*                                                                    */
/*   data : 2008.09.18                                                */
/*                                                                    */
/*   produce : Wajima                                                 */
/*                             Copyright(C) 2008 ALL RIGHTS RESERVED  */
/**********************************************************************/
char ChkKesseiKmkcd(Kekka* kekka)
{
    char aFunc[32];
    char ret;
    int  i;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
    memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
    printf("ChkKesseiKmkcd\n");
#endif

	/*** �Ώۂ�������Ό����`�F�b�N�͍s��Ȃ� ***/
	ret = 0;

	if (kekka->knsgrp[0] == '\0')
		return 0;

    for(i = 0; i < iKmkmstNum; i++)
    {
        if ((memcmp(pKmkmst[i].knsgrp, kekka->knsgrp,        16) == 0) &&
            (memcmp(pKmkmst[i].kmkcd,  kekka->kmkcd,          7) == 0) &&
			(memcmp(pKmkmst[i].kaiymd, sSysknrmst.kjnsriymd,  8) >= 0) &&
			(memcmp(pKmkmst[i].haiymd, sSysknrmst.kjnsriymd,  8) <= 0))
        {
			ret = pKmkmst[i].ksjhflg;
		}
	}

	return ret;
}

/*** wajima TEST ***/
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

/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */

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
	memset( cWrk, 0, sizeof( cWrk ) );
	memset( cWrkCd, 0, sizeof( cWrkCd ) );
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
		cTmpRack, 
		p->cRackPosNum );

	sprintf( FullPath, "%s/%s%s", aBunsekiOrderFolder, FileNameBase, ".dat" );
	sprintf( FullPathTmp, "%s/%s%s", aBunsekiOrderFolder, FileNameBase, ".tmp" );

	fp = fopen( FullPathTmp, "w+" );
	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "OutputBunsekiOrder()", "�t�@�C���̃I�[�v���Ɏ��s���܂����B" ) ;
		return RTN_NG;
	} else {
		CnvtFromKjnsriymd( sSysknrmst.kjnsriymd, cWrkCd );
		fprintf( fp, "%s,%s" , cWrkCd, cTmpRack );
	}

	fclose( fp );

	rename( FullPathTmp, FullPath );

	return RTN_OK;

}
