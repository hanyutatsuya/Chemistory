/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FDD204.h                                                      */
/* �@�T�@�@�@�v�FLST008�ʐM�E���ʏo�̓w�b�_                                   */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/31     A.Yamada       �V�K�쐬                           */
/* -------------------------------------------------------------------------- */
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  2.00     2008/09/25     K.Ameno        X-M�Ή�����                        */
/******************************************************************************/
#ifndef _dd203_h
#define _dd203_h
/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <syslog.h>

#include "bmllog.h"
#include "bmlprm.h"
#include "bml_base.h"

#include "Mechmst.h"
#include "Kmkmst.h"
#include "Ctrlmst.h"
#include "Sysknrmst.h"
#include "Knsgmst.h"		/* 060418 009 */
#include "Kskbrmst2.h"		/* ADD E.Osada 2006-07-13 */
#include "Kekka.h"
#include "Ctrlkka.h"
#include "Kenorder.h"
#include "Xbarm.h"
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
/*** X-M�����W�`�F�b�N�̂��ߒǉ� ***/
#include "Xbarmmst.h"
/*** ���������W�`�F�b�N�̂��ߒǉ� ***/
#include "Rngchkmst.h"
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */

#include "DD40101.h"

/**********************************************************************/
/*  �萔�錾                                                          */
/**********************************************************************/

/***  ���O����������ƒʐM�G���[����������ꍇ�����邽�� ***/
/***  TEST�̎�����ON�ɂ��Ă�������!!!                    ***/
//#define		_DEBUG_		/* �ʏ탍�O */

/* �t���[�����䕶�� */
#define		SOH		0x01	/* <SOH> */
#define		STX		0x02	/* <STX> */
#define		ETX		0x03	/* <ETX> */
#define		EOT		0x04	/* <EOT> */
#define		ENQ		0x05	/* <ENQ> */
#define		ACK		0x06	/* <ACK> */
#define		ELE		0x10	/* <DLE> */
#define		DC1		0x11	/* <DC1> */
#define		DC2		0x12	/* <DC2> */
#define		DC3		0x13	/* <DC3> */
#define		DC4		0x14	/* <DC4> */
#define		NAK		0x15	/* <NAK> */
#define		SYN		0x16	/* <SYN> */
#define		ETB		0x17	/* <ETB> */
#define		CR		0x0d	/* <CR> */
#define		LF		0x0a	/* <LF> */

/* STATUS */
#define		STAT_IDLE			0x00	/* idle */
#define		STAT_AWAKE			0x01	/* Awake */
#define		STAT_RCV_WAIT		0x02	/* Receive Waiting */
#define		STAT_FRAME_RCV		0x03	/* Frame Received */
#define		STAT_HAVE_DATA_SND	0x04	/* Have Data to Send */
#define		STAT_DATA_SEND		0x05	/* Data to Send */
#define		STAT_SND_WAIT		0x06	/* Send Waiting */
#define		STAT_NEXT_FRAME		0x07	/* Next Frame */
#define		STAT_SND_WAIT2		0x08	/* Send Waiting2 */
#define		STAT_OLD_FRAME		0x09	/* Old Frame */

/* ��ߔ{�� */
#define		MAXKSKBRT			"KSKBRT_1"	/* �Œ��ߔ{�� */
#define		MINKSKBRT			"KSKBRT_3"	/* �ō���ߔ{�� */

/* �ő��M�o�C�g�� */
#define		MAX_RCV_NUM			247

/* �f�[�^���M���̃E�G�C�g���� */
#define		SLEEP_USEC			30000	/* 30ms */

/* ��M���b�Z�[�W�̈Ӗ� */
#define		MSG_NON				0		/* �Ȃ� */
#define		MSG_ORDER			1		/* �₢���킹 */
#define		MSG_RESULT			2		/* ���ʑ��M */
#define		MSG_PCR				3		/* ��F�L�����u���ʑ��M */
#define		MSG_ICR				4		/* ISE�L�����u���ʑ��M */

/* �ʐM���O��� */
#define		RCV_LOG				0		/* ��M�f�[�^���O */
#define		SND_LOG				1		/* ���M�f�[�^���O */

/* .dat�t�@�C����� */
#define		RESULT_DAT			0		/* �������ʃt�@�C�� */
#define		ORDER_DAT_1			1		/* �����I�[�_�[�t�@�C��1 */
#define		ORDER_DAT_2			2		/* �����I�[�_�[�t�@�C��2 */

/* �t���[�����g���C�J�E���^ */
#define		FRAME_RETRY_MAX		6		/* 3�� */

/* �e�^�C�}�ݒ�l */
#define		TM_WAIT_10			10		/* 10s */
#define		TM_WAIT_15			15		/* 15s */
#define		TM_WAIT_20			20		/* 20s */
#define		TM_WAIT_30			30		/* 30s */

/* �\�P�b�g�ڑ���� */
#define		TM_SCK_CON			10		/* �\�P�b�g�ڑ��^�C�} */
#define		SCK_CON_NG			0		/* �\�P�b�g���ڑ� */
#define		SCK_CON_OK			1		/* �S�\�P�b�g�ڑ����� */

/* �ő�˗����ڐ� */
#define		MAX_ITEM_NUM		100		/* �ő區�ڐ� */

#define		NO_SND_REQ		0			/* ���M�v���Ȃ� */
#define		SND_REQ			1			/* ���M�v������ */

/* ��M�f�[�^�`�F�b�N */
#define		NO_RCV_DATA		0			/* ��M�f�[�^�Ȃ� */
#define		RCV_DATA_OK		1			/* ��M�f�[�^���� */
#define		RCV_DATA_NG		2			/* ��M�f�[�^NG */

/* ��M���b�Z�[�W�`�F�b�N */
#define		MESSAGE_ERR			0		/* message error */
#define		MESSAGE_NO_ERR		1		/* message no error */
#define		MESSAGE_OK			2		/* message OK */
#define		MESSAGE_ALL_OK		3		/* message All OK */

/* �t���[����Ԑݒ� */
#define		FRAME_CONTINUE		0		/* ���t���[������(<ETB>��M) */
#define		FRAME_END			1		/* �t���[���I��(<ETX>��M>) */

/* �ݒ�t�@�C�� */
#define		INI_FILE_NAME		"DD204_"
#define		INI_FILE_PRM		"00"

/* ���߃��R�[�h��� */
#define		C_RES				0		/* ���ʃt���O */
#define		C_CMM				1		/* �R�����g */

/* ISE�L�����u���[�V�������ʃ��R�[�h���� */
#define		ITEM_NA				0		/* Na */
#define		ITEM_K				1		/* K */
#define		ITEM_CL				2		/* Na */

/* �f�[�^�A���[���z���`�ǉ� 2006.07.13 E.Osada */
typedef struct sndorder {	
	int		seqnum;
	char	kntno[13+1];
	int		knssu;
	int		knssueda;
	int		bskseq;							/* ���̔ԍ� */
	char	racktype[2+1];					/* ���̎�� */
	char	kmkcd[MAX_ITEM_NUM][7+1];		/* No. 6 ���ڃR�[�h */
	char	zrcd[4+1];						/* No.27 �ޗ��R�[�h */
	char	ytiksbr[MAX_ITEM_NUM][15+1];	/* No.37 �\���ߔ{�� */
	char	sbtkbn[1+1];					/* No.44 ���ʋ敪 */
	char	age[3+1];						/* No.47 �N�� */
	char	agekbn[1+1];					/* No.48 �N��敪 */
	char	sstme[8+1];						/* No.49 �̎掞�� */
	char	ssymd[10+1];					/* No.50 �̎�N���� */
}SNDORDER;


/* �\�P�b�g��� */
typedef struct socket_inf {
 	int		iSd;					/* �\�P�b�g�ԍ� */
 	char	aGouki[4];				/* ���͋@���@ */
	char	aHostName[100];			/* �z�X�g�� */
	int		iPortNum;				/* �|�[�g�ԍ� */
	char	aRcvTmpMsgBuf[6000];	/* ��M���b�Z�[�W�R�s�[�G���A */
	char	aSndAllMsgBuf[1700];	/* �S���M���b�Z�[�W�G���A */
	char	aSndTmpBuf[255];		/* ���M�f�[�^�ꎞ�o�b�t�@ */
	char	cRcvFrameCtrlChar;		/* ��M�t���[�����䕶�� */
	char	cSndFrameCtrlChar;		/* ���M�t���[������ */
	char	cFrameNum;				/* �t���[���ԍ� */
	char	cChkRcvData;			/* ��M�f�[�^����/�Ȃ����� */
	char	cSndDataReq;			/* ���M�f�[�^�v������/�Ȃ����� */
	char	cStatus;				/* STATUS�Ǘ� */
	char	cChkRcvMessage;			/* ��M���b�Z�[�W���� */
	char	cChkNextFrame;			/* �t���[���p��/�I������ */
	char	cSndFrameSeqNum;		/* ���񑗐M�t���[���J�E���^ */
	int		iRcvMsg;				/* ��M���b�Z�[�W�̈Ӗ� */
	char	cRackNum[8+1];			/* ���b�N�ԍ� */
	char	cRackPosNum[2+1];		/* ���b�N�ʒu�ԍ� */
	int		iSndRetryCnt;			/* �t���[�����M���g���C�J�E���^ */
	int		iSndBlockCnt;			/* ���M�e�L�X�g�u���b�N�J�E���^ */
	int		iSndBlockNum;			/* �t���[�����M���g���C�J�E���^ */
	int		iSndAgainReq;			/* �đ��v�� */
	char	aSndAgainBuf[1700];		/* �đ��p�o�b�t�@ */
	Kekka* 	pKekka;					/* �������ʏ��(csv�o�^����) */
	Kekka*	pKkkaChk;				/* �������ʏ��(csv�o�^����) �v�Z�`�F�b�N�p */
	int	iKkkaChkNum;				/* �������ʏ��(csv�o�^����) �v�Z�`�F�b�N�p */
	Ctrlkka	sCtrlkka;				/* �R���g���[�����ʏ��(csv�o�^����) */
	Xbarm	sXbarm;					/* X-M���ʏ��(csv�o�^����) */
	SaikenInfo*	pSaiken;			/* �Č��˗���� */
	int			iKekkaNum;			/* �Č��˗����� */
	int			iKekkaCnt;			/* �Č��˗������J�E���^ */
	int		iOrderNum;				/* �˗����ڐ� */
	SNDORDER 	sSndorder;			/* �����I�[�_�[��� */
	time_t	tStartTm;				/* �ʐM�J�n�^�C�} */ 
	float	fTmOutVal;				/* �^�C�} */
	int		aPltseq[7];				/* �v���b�gSEQ */
	int			iCtrlSeq;
	int			iCtrlSeqCnt;
	int		iSendTimer;				/* ���M�^�C�}(msec) */
	struct {
	/* UPD 2007-04-25 S.Nagata �T�C�Y�𑝂₷ 48 -> 5000 */
	int		cnt;
	int		Ctrl_no[5000];
	int		Bunseki_Seq[5000];
	time_t	KnsTime[5000];
	} CtrlInfo;
	struct	socket_inf* next;
	struct	socket_inf* prev;
}SOCKET_INF;

/* �e�L�X�g��` */
/* ���b�Z�[�W��` */
/* Universal Test ID �t�B�[���h*/
struct UNI_TEST_ID {	
	char	cAppCode[5+1];				/* Application Code */
	char	cDilution[3+1];				/* Dilution */
};

/* Message Header Record(���b�Z�[�W���o�����R�[�h) */
struct MSG_HEADER_RCD {	
	char	cRcdTypeId[1+1];			/* Record Type ID */
	char	cDelmtrDef[4+1];			/* Delimiter Definition */
	char	cDeviceName[30+1];			/* ���M���̑��u���� */
	char	cComPrgVer[5+1];			/* �ʐM�v���O�����o�[�W���� */
	char	cRcvrId[30+1];				/* Receiver ID */
	char	cMessageMean[5+1];			/* ���b�Z�[�W�̈Ӗ� */
	char	cGenerateFactor[5+1];		/* �����v�� */
	char	cPrcssingId[1+1];			/* Processing ID */
	char	cVersionNo[1+1];			/* Version No. */
};

/* Patient information Record(���ҏ�񃌃R�[�h) */
struct PATIENT_INF_RCD {
	char	cRcdTypeId[1+1];			/* Record Type ID */
	char	cSeqNum[6+1];				/* Sequence Number */
	char	cPatientSex[1+1];			/* Patient Sex */
	char	cAge[3+1];					/* Age */
	char	cAgeUnit[1+1];				/* Age Unit */

};

/* Request information Record(�₢���킹���R�[�h) */
struct REQ_INF_RCD {
 	char	cRcdTypeId[1+1];			/* Record Type ID */
	char	cSeqNum[6+1];				/* Sequence Number */
	char	cSampleId[22+1];			/* Sample ID. */
	char	cSampleNo[5+1];				/* Sample No. */
	char	cRackId[5+1];				/* Rack ID */
	char	cPositionNo[1+1];			/* Position No. */
	char	cRackType[2+1];				/* Rack Type */
	char	cContainerType[2+1];		/* Container Type */
	char	cUniTestId[3+1];			/* Universal Test ID */
	char	cReqInfStatCode[1+1];		/* Request Information Status Codes */
};

/* Test Order Record(���ڑI�����R�[�h) */
struct TEST_ORDER_RCD {
	char		cRcdTypeId[1+1];			/* Record Type ID */
	char		cSeqNum[6+1];				/* Sequence Number */
	char		cSampleId[22+1];			/* Sample ID */
	char		cSampleNo[5+1];				/* Sample No. */
	char		cRackId[5+1];				/* Rack ID */
	char		cPositionNo[1+1];			/* Position No. */
	char		cRackType[2+1];				/* Rack Type */
	char		cContainerType[2+1];		/* Container Type */
	struct UNI_TEST_ID	sUniTestId[406];			/* Universal Test ID */
	char		cPriority[1+1];				/* Priority */
	char		cSpecimenCollDateTm[14+1];	/* Specimen Collection Date and Time */
	char		cActionCode[1+1];			/* Action Code */
	char		cSpecimenDescriptor[1+1];	/* Specimen Descriptor */
	char		cDateTmResRep_LstMod[14+1];	/* Data/Time Results Reported or Last Modified */
	char		cReportTypes[1+1];			/* Report Types */
};

/* C-RES Record(���߃��R�[�h:���ʃt���O) */
struct COMMENT_RCD {
	char	cRcdTypeId[1+1];			/* Record Type ID */
	char	cSeqNum[6+1];				/* Sequence Number */
	char	cCmntSrc[1+1];				/* Comment Source */
	char	cCmmTxt[3+1];				/* Comment Text */
	char	cCmm1[30+1];				/* Comment1 */
	char	cCmm2[25+1];				/* Comment2 */
	char	cCmm3[20+1];				/* Comment3 */
	char	cCmm4[15+1];				/* Comment4 */
	char	cCmm5[10+1];				/* Comment5 */
	char	cCmntType[1+1];				/* Comment Type */
};

/* Result Record(���ʃ��R�[�h) */
struct RESULT_RCD {
	char	cRcdTypeId[1+1];			/* Record Type ID */
	char	cSeqNum[6+1];				/* Sequence Number */
	char	cAppCode[5+1];				/* Application Code */
	char	cDilution[3+1];				/* Dilution */
	char	cDat_MeasrmntVal[15+1];		/* Data or Measurement Value */
	char	cUnits[6+1];				/* Units */
	char	cResAbnmlFlg[2+1];			/* Result Abnormal Flags */
	char	cResStat[1+1];				/* Result Status */
	char	cOprtrIdentif[6+1];			/* Operator Identification */
	char	cInstIdentif[4+1];			/* Instrument Identification */
	char	cTestStarted[14+1];			/* Date Time Test Started */
};

/* STD Data �t�B�[���h*/
struct STD_DAT {	
	char	c1stDat[6+1];				/* 1��ڂ̋z���x�f�[�^ */
	char	c1stIni_LstDat[6+1];		/* 1��ڂ̏����܂��͍ŏI�z���x�f�[�^ */
	char	c2ndDat[6+1];				/* 2��ڂ̋z���x�f�[�^ */
	char	c2ndIni_LstDat[6+1];		/* 2��ڂ̏����܂��͍ŏI�z���x�f�[�^ */
	char	cDatAlarm[3+1];				/* �f�[�^�A���[�� */
	char	cProZoneVal[6+1];			/* �v���]�[���l */
};

/* ISE�L�����u���[�V�������ʃ��R�[�h����(Na/K/Cl) */
struct ISE_CALB_ITEM {	
	/* Na/K/Cl calibration Alarm */
	char	cCalbAlarm[3+1];		/* Calibration Alarm */
	/* Na/K/Cl data Alarm */
	char	cAlmNaibuKiden[3+1];	/* �����W���t�N�d�̓f�[�^�A���[�� */
	char	cAlmLow[3+1];			/* LOW�t�N�d�̓f�[�^�A���[�� */
	char	cAlmHigh[3+1];			/* HIGH�t�N�d�̓f�[�^�A���[�� */
	char	cAlmCalbKiden[3+1];		/* �L�����u���[�V�����t�N�d�̓f�[�^�A���[�� */
	char	cAlmSlpe[3+1];			/* �\���p�X���[�v�f�[�^�A���[�� */
	char	cAlmNaibuNodo[3+1];		/* �����W���t�Z�x�f�[�^�A���[�� */
	char	cAlmCalbNodo[3+1];		/* �L�����u���[�V�����t�Z�x�f�[�^�A���[�� */
	char	cAlmHosei[3+1];			/* �␳�W���f�[�^�A���[�� */
	/* Na/K/Cl data */
	char	cDatNaibuKiden[6+1];	/* �����W���t�N�d�̓f�[�^ */
	char	cDatLow[6+1];			/* LOW�t�N�d�̓f�[�^ */
	char	cDatHigh[6+1];			/* HIGH�t�N�d�̓f�[�^ */
	char	cDatCalbKiden[6+1];		/* �L�����u���[�V�����t�N�d�̓f�[�^ */
	char	cDatSlpe[6+1];			/* �\���p�X���[�v�f�[�^ */
	char	cDatNaibu[6+1];			/* �����W���t�Z�x�f�[�^ */
	char	cDatCalb[6+1];			/* �L�����u���[�V�����t�Z�x�f�[�^ */
	char	cDatHosei[6+1];			/* �␳�W���f�[�^ */
};

/* Caliblation data Record */
struct CALB_RCD {
	char	cRcdTypeId[1+1];			/* Record Type ID */
	char	cSeqNum[6+1];				/* Sequence Number */
	char	cSubId[3+1];				/* Record Type Sub ID */
	char	cOperatorId[6+1];			/* Operator ID */
	char	cCellNo[3+1];				/* Cell No */
	char	cInputInf[1+1];				/* Input Information */
	char	cReactionTm[2+1];			/* Reaction Time */
	char	cPointNum[2+1];				/* Number of Points */
	char	cCellBlankDat1[6+1];		/* Cell Blank Data1 */
	char	cCellBlankDat2[6+1];		/* Cell Blank Data2 */
	char	cCellBlankDat3[6+1];		/* Cell Blank Data3 */
	char	cCellBlankDat4[6+1];		/* Cell Blank Data4 */
	char	cDeltaAbsDat[38][6+1];		/* Delta ABS Data */
	char	cTestCode[8+1];				/* Test Code */
	char	cModuleId[4+1];				/* Module ID */
	char	cCalbAlarm[3+1];			/* Caribration Alarm */
	char	cSdDatField[6+1];			/* SD Data Field */
	struct STD_DAT	sStdDat[6];					/* STD Data */
	struct ISE_CALB_ITEM	sIseCalbItem[3];	/* ISE�L�����u���[�V�������ʃ��R�[�h���� */
};

/* ���͋@��� */
typedef struct bunseki_inf {
	char	aIpAddr[100];			/* IP�A�h���X */
	int		iPortNum;				/* �|�[�g�ԍ� */
	char	aGouki[4];				/* ���@�ԍ� */
	/* ADD 2006-08-21 E.Osada ���M�^�C�}�ǉ� */
	int		iSendTimer;				/* ���M�^�C�}(msec) */
}BUNSEKI_INF;

/* X-M��� */
typedef struct xbarm_inf {
	int		iGoukiNum;				/* ���@ */
	int		iModuleNum;				/* ���W���[�� */
	char	kmkcd[8];				/* ���ڔԍ� */
	int		iNumCnt;				/* �J�E���^ */
	int		knsseqst;				/* ����SEQ-START */
	int		knsseqed;				/* ����SEQ-END */
	int		bskseqst;				/* ���͋@SEQ-START */
	int		bskseqed;				/* ���͋@SEQ-END */
	int		pltseqst;				/* �v���b�gSEQ-START */
	int		pltseqed;				/* �v���b�gSEQ-END */
	double	xbarmkka;				/* X-M���� */
	double	xbarmsum;				/* X-M���v�l */
	int		xmcount;				/* X-M�J�E���g */
	char	xmchk;					/* X-M���ʏo�͋��t���O */
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
/*** X-M���v�l�����ł͌v�Z������Ȃ��ꍇ������ ***/
	double	xmsub;					/* X-M���ʂƂ̍������v */
	char    knsgrp[17];             /* �����O���[�v */
	int     iXbarmCnt;              /* �������ɕK�v */
	int     iXbarmNum;              /* �������ɕK�v */
	int		saiken;					/* �Č�����     */
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */
}XBARM_INF;

#define		XBARM_ITEM_NUM		(6*7*240)	/* ���@*���W���[��*���� */
#define		PLT_UNIT_DEF		10			/* �v���b�g�P��(default) */

/* X-M��� */
typedef struct ctrl_inf {
	int		iGoukiNum;				/* ���@ */
	int		iModuleNum;				/* ���W���[�� */
	char	nbkmkcd[8];				/* �`���l�� */
	int		ctrlno;					/* �R���g���[��No */
}CTRL_INF;

#define		CTRL_ITEM_NUM		(6*7*60)	/* ���@*���W���[��*���� */

/* X-M��� */
typedef struct kinkyu_inf {
	char    bskkbn[5];
	char    knsgrp[17];
	char    kmkcd[8];
	char    nbkmkcd[8];
}KINKYU_INF;

/* ADD E.Osada �f�t�H���g���M�^�C���A�E�g */
#define DEFSNDTIMER		0
/**********************************************************************/
/*  �O���Q�Ɗ֐�                                                      */
/**********************************************************************/
extern int MakeFileName( char*, char* , int);		/* �t�@�C�����쐬���� */
#define sFncSyslog(p, f, m) _sFncSyslog(p, f, m, "", EXEFLG_NON, __FILE__, __LINE__)
/*  �V�X�e�����O�o�� */
extern  void    _sFncSyslog (LOG_TRCKIND piPri, char * pcFncname,char * pcMsg , char * pcErrCode, char * pcExeFlg, char * file, long lineno) ;
int chkDataAlarm();		//ADD E.Osada 2006-07-13
extern int RealTimeChk(SOCKET_INF *p, SaikenInfo * fSaiken);
extern void GetModule (char *pFrom, int *pTo);
extern char GetXmSkFlg(char *pKnsgrp, char *pKmkcd, char *pKnskisymd);
extern char GetXmChkFlg(char *pKnsgrp, char *pKmkcd, char *pKnskisymd);

/**********************************************************************/
/*  �O���Q�ƕϐ�                                                      */
/**********************************************************************/
extern struct	stcLogMember sLog;		/* ���O�o�͏��\���� */
extern char		aRcvBuf[255];			/* ��M�f�[�^�o�b�t�@ */
extern int		iSckConChk;				/* �\�P�b�g�ڑ��`�F�b�N */
extern time_t	tSckConTm;				/* �\�P�b�g�ڑ��^�C�} */ 
extern int		iBunsekiNum;			/* ���͋@���@�� */
extern int		iGouki;					/* ���@��� */
extern char		aFileNameStr[64];		/* �t�@�C�����G���A */
extern char		aKenorderFolder[256];	/* �����I�[�_�[�t�@�C���i�[�t�H���_�� */
extern char		aKenorderFolder2[256];	/* �����I�[�_�[�t�@�C���i�[�t�H���_�Q�� */
extern char		aKekkaFolder[256];		/* �������ʊi�[�o�͐�t�H���_�� */
extern char		aCtrlkkaFolder[256];	/* �R���g���[�����ʊi�[�o�͐�t�H���_�� */
extern char		aMstFolder[256];		/* �}�X�^�t�@�C���i�[�o�͐�t�H���_�� */
extern char		aKmkcdTblFolder[256];	/* ���ڃR�[�h�ϊ��e�[�u���t�H���_�� */
extern char		aLogOutFolder[256];		/* �ʐM���O�o�͐�t�H���_�� */
extern Mechmst	*pMechmst;
extern int		iMechmstNum;
extern KINKYU_INF	*pKinkyu;
extern int		iKinkyuNum;
extern Sysknrmst	sSysknrmst;
extern Kmkmst	*pKmkmst;
extern int		iKmkmstNum;
extern Ctrlmst	*pCtrlmst;
extern int		iCtrlmstNum;
extern Knsgmst	*pKnsgmst;
extern int		iKnsgmstNum;
extern SOCKET_INF sSocketInf;			/* �\�P�b�g��� */
extern BUNSEKI_INF *sBunsekiInf;		/* ���͋@��� */
extern Kenorder *pKenorder;				/* �����I�[�_�[���[�N�G���A�|�C���^ */
extern char		aMekbn[5];				/* ���͋@�敪 */
/* �f�[�^�A���[�������ǉ� 2006-07-13 E.Osada */
int getDataAm(  char *sBuf, char *sArm  );
extern Kskbrmst *pKskbrmst;
extern int iKskbrmstNum;
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� --> */
/*** X-M�����W�`�F�b�N�̂��ߒǉ� ***/
extern Xbarmmst *pXbarmmst;
extern int iXbarmmstNum;
/*** ���������W�`�F�b�N�̂��ߒǉ� ***/
extern Rngchkmst *pRngchkmst;
extern int iRngchkmstNum;
/*	2.00	2008/09/25		K.Ameno		   X-M�Ή����� <-- */

extern int iStartCtrlSeq;			/* �R���g���[���m�n�̏����l �������̂Ƃ̂��Ԃ�h�~  */

#endif /* DD204.h */
