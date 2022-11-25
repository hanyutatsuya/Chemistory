/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FDD201.h                                                      */
/* �@�T�@�@�@�v�FBM8000�ʐM�E���ʏo�̓w�b�_                                   */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/31     A.Yamada       �V�K�쐬                           */
/* -------------------------------------------------------------------------- */
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  2.00     2008/09/19     K.Ameno        X-M�Ή�����                        */
/******************************************************************************/
#ifndef _dd201_h
#define _dd201_h
/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
#include "Knsgmst.h"	/* 060418 009 */
#include "Kekka.h"
#include "Ctrlkka.h"
#include "Kenorder.h"
#include "Xbarm.h"
#include "Kskbrmst2.h"	/* ADD Haga 2006-08-02 */
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
#include "Xbarmmst.h"	/* X-M�����W�`�F�b�N�Ή� add */
#include "Rngchkmst.h"	/* ���������W�`�F�b�N�Ή� add */
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
#include "DD40101.h"
/**********************************************************************/
/*  �萔�錾                                                          */
/**********************************************************************/

/***  ���O����������ƒʐM�G���[����������ꍇ�����邽�� ***/
/***  TEST�̎�����ON�ɂ��Ă�������!!!                    ***/ 
//#define		_DEBUG_

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

/* �ő��M�o�C�g�� */
#define		MAX_RCV_NUM			512

/* �f�[�^���M���̃E�G�C�g���� */
#define		SLEEP_USEC			30000	/* 30ms */

/* ��M���b�Z�[�W�̈Ӗ� */
#define		MSG_NON				0		/* �Ȃ� */
#define		MSG_ORDER			1		/* �₢���킹 */
#define		MSG_RESULT			2		/* ���ʑ��M */
#define		MSG_ELC				3		/* �d��������f�[�^�e�L�X�g */

/* �ʐM���O��� */
#define		RCV_LOG				0		/* ��M�f�[�^���O */
#define		SND_LOG				1		/* ���M�f�[�^���O */

/* .dat�t�@�C����� */
#define		RESULT_DAT			0		/* �������ʃt�@�C�� */
#define		ORDER_DAT_1			1		/* �����I�[�_�[�t�@�C��1 */
#define		ORDER_DAT_2			2		/* �����I�[�_�[�t�@�C��2 */

/* �t���[�����g���C�J�E���^ */
#define		FRAME_RETRY_MAX		3		/* 3�� */

/* �e�^�C�}�ݒ�l */
#define		TM_WAIT_2			2		/* 2s */
#define		TM_WAIT_3			3		/* 3s */
#define		TM_WAIT_5			5		/* 5s */
#define		TM_WAIT_10			10		/* 10s */

/* �\�P�b�g�ڑ���� */
#define		TM_SCK_CON			10		/* �\�P�b�g�ڑ��^�C�} */
#define		SCK_CON_NG			0		/* �\�P�b�g���ڑ� */
#define		SCK_CON_OK			1		/* �S�\�P�b�g�ڑ����� */

/* �ő�t���[�������� */
#define		MAX_LEN_512			1		/* 512byte */
#define		MAX_LEN_256			2		/* 256byte */

/* �ő�˗����ڐ� */
#define		MAX_ITEM_NUM	(114+117*5)	/* �ő區�ڐ� */

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
#define		INI_FILE_NAME		"DD201_"
#define		INI_FILE_PRM		"00"

typedef struct sndorder {	
	char	seqnum[13+1];
	int		seqnum2;
	char	kntno[13+1];
	char	racktype[2+1];				/* ���̎�� */
	char	kmkcd[MAX_ITEM_NUM][7+1];	/* No. 6 ���ڃR�[�h */
	char	zrcd[4+1];					/* No.27 �ޗ��R�[�h */
	char	ytiksbr[MAX_ITEM_NUM][15+1];/* No.37 �\���ߔ{�� */
	char	sbtkbn[1+1];				/* No.44 ���ʋ敪 */
	char	age[3+1];					/* No.47 �N�� */
	char	agekbn[1+1];				/* No.48 �N��敪 */
	char	sstme[8+1];					/* No.49 �̎掞�� */
	char	ssymd[10+1];				/* No.50 �̎�N���� */
	char	ykcd[4+1];					/* �e��R�[�h */		/* 060417 009 */
}SNDORDER;

/* �\�P�b�g��� */
typedef struct socket_inf {
 	int		iSd;						/* �\�P�b�g�ԍ� */
 	char	aGouki[4];					/* ���͋@���@ */
	char	aHostName[100];				/* �z�X�g�� */
	int		iPortNum;					/* �|�[�g�ԍ� */
	char	aRcvTmpMsgBuf[1024];		/* ��M���b�Z�[�W�R�s�[�G���A */
	char	aSndAllMsgBuf[6][520];		/* �S���M���b�Z�[�W�G���A */
	char	aSndTmpBuf[520];			/* ���M�f�[�^�ꎞ�o�b�t�@ */
	char	cRcvFrameCtrlChar;			/* ��M�t���[�����䕶�� */
	char	cSndFrameCtrlChar;			/* ���M�t���[������ */
	char	cFrameNum;					/* �t���[���ԍ� */
	char	cChkRcvData;				/* ��M�f�[�^����/�Ȃ����� */
	char	cSndDataReq;				/* ���M�f�[�^�v������/�Ȃ����� */
	char	cStatus;					/* STATUS�Ǘ� */
	char	cChkRcvMessage;				/* ��M���b�Z�[�W���� */
	char	cChkNextFrame;				/* �t���[���p��/�I������ */
	char	cSndFrameSeqNum;			/* ���񑗐M�t���[���J�E���^ */
	int		iRcvMsg;					/* ��M���b�Z�[�W�̈Ӗ� */
	char	cRackNum[8+1];				/* ���b�N�ԍ� */
	char	cRackPosNum[2+1];			/* ���b�N�ʒu�ԍ� */
	int		iSndRetryCnt;				/* �t���[�����M���g���C�J�E���^ */
	int		iSndBlockCnt;				/* ���M�e�L�X�g�u���b�N�J�E���^ */
	int		iSndBlockNum;				/* �t���[�����M���g���C�J�E���^ */
	int		iSndAgainReq;				/* �đ��v�� */
	char	aSndAgainBuf[6][520];		/* �đ��p�o�b�t�@ */
	Kekka* 	pKekka;						/* �������ʏ��(csv�o�^����) */
	Ctrlkka	sCtrlkka;					/* �R���g���[�����ʏ��(csv�o�^����) */
	Xbarm	sXbarm;						/* X-M���ʏ��(csv�o�^����) */
	SaikenInfo*	pSaiken;				/* �Č��˗���� */
	int			iKekkaNum;				/* �Č��˗����� */
	int			iKekkaCnt;				/* �Č��˗������J�E���^ */
	int		iOrderNum;					/* �˗����ڐ� */
	SNDORDER	sSndorder;				/* �����I�[�_�[��� */
	time_t	tStartTm;					/* �ʐM�J�n�^�C�} */ 
	float	fTmOutVal;					/* �^�C�} */
	int		aPltseq[7];					/* �v���b�gSEQ */
	int			iCtrlSeq;
	int			iCtrlSeqCnt;
	/* ADD 2006-08-21 E.Osada ���M�^�C�}�ǉ� */
	int		iSendTimer;					/* ���M�^�C�}(msec) */
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
/* ���ږ₢���킹�e�L�X�g(���A�����ڑI��) */
struct ITEM_INQ_TXT_REAL {	
	char	cStartCode[1+1];			/* �J�n�R�[�h */
	char	cFrameNum[1+1];				/* �t���[���ԍ� */
	char	cTextType[1+1];				/* �e�L�X�g��� */
	char	cDevIdentifNum[1+1];		/* ���u���ʔԍ� */
	char	cAllBlockNum[2+1];			/* �S�u���b�N�� */
	char	cBlockNum[2+1];				/* �u���b�N�ԍ� */
	char	cSpecimenNumInBlk[2+1];		/* �u���b�N���₢���킹���̐� */
	char	cIdType[1+1];				/* ID��� */
	char	cRackNum[8+1];				/* ���b�N�ԍ� */
	char	cRackPosNum[2+1];			/* ���b�N���ʒu�ԍ� */
	char	cRackNumInf[13+1];			/* ���b�N�ԍ���� */
	char	cReserve[1+1];				/* �\�� */
	char	cEndCode[5+1];				/* �I���R�[�h */
};

/* ����f�[�^�e�L�X�g(�Č��₢���킹�L��) */
struct MEASURE_DAT_TXT {	
	char	cStartCode[1+1];			/* �J�n�R�[�h */
	char	cFrameNum[1+1];				/* �t���[���ԍ� */
	char	cTextType[1+1];				/* �e�L�X�g��� */
	char	cDevIdentifNum[1+1];		/* ���u���ʔԍ� */
	char	cAllBlockNum[2+1];			/* �S�u���b�N�� */
	char	cBlockNum[2+1];				/* �u���b�N�ԍ� */
	char	cItemNumInBlk[2+1];			/* �u���b�N�����ڐ� */
	char	cInspectDay[8+1];			/* ������ */
	char	cInspectTm[6+1];			/* �������� */
	char	cSpecimenDiv[1+1];			/* ���̋敪 */
	char	cIdSpec[1+1];				/* ID�d�l */
	char	cIdSpecimenId[13+1];		/* ����ID */
	char	cRackNum[8+1];				/* ���b�N�ԍ� */
	char	cRackPosNum[2+1];			/* ���b�N���ʒu�ԍ� */
	char	cTtNum[2+1];				/* TT�ԍ� */
	char	cCupNum[2+1];				/* CUP�ʒu�ԍ� */
	char	cReserve[16+1];				/* �\�� */
	char	cCom1[16+1];				/* �R�����g�P */
	char	cCom2[16+1];				/* �R�����g�Q */
	char	cSex[1+1];					/* ���� */
	char	cAge[3+1];					/* �N�� */
	char	cCollBlooddDay[8+1];		/* �̌��� */
	char	cDiltCoeff[4+1];			/* ��ߌW�� */
	char	cSpecimenType[1+1];			/* ���̎�� */
	char	cCntnrType[1+1];			/* �e���� */
	char	cItemNum[3+1];				/* ���ڔԍ� */
	char	cAnalysCond[1+1];			/* ���͏��� */
	char	cStndrdDensity[1+1];		/* �W���Z�x */
	char	cMeasureVal[8+1];			/* ����l */
	char	cMark[3+1];					/* �}�[�N */
	char	cEditDatMark[1+1];			/* �ҏW�f�[�^�}�[�N */
	char	cRepeatNum[1+1];			/* �J��Ԃ��� */
	char	cUserCode[3+1];				/* ���[�U�[�R�[�h */
	char	cMeasureBlkNum[1+1];		/* ����u���b�N�ԍ� */
	char	cEndCode[5+1];				/* �I���R�[�h */
};

/* ����f�[�^�e�L�X�g(�Č��₢���킹����) */
struct MEASURE_DAT_TXT_NO_INQ {	
	char	cStartCode[1+1];			/* �J�n�R�[�h */
	char	cFrameNum[1+1];				/* �t���[���ԍ� */
	char	cTextType[1+1];				/* �e�L�X�g��� */
	char	cDevIdentifNum[1+1];		/* ���u���ʔԍ� */
	char	cAllBlockNum[2+1];			/* �S�u���b�N�� */
	char	cBlockNum[2+1];				/* �u���b�N�ԍ� */
	char	cItemNumInBlk[2+1];			/* �u���b�N�����ڐ� */
	char	cInspectDay[8+1];			/* ������ */
	char	cInspectTm[6+1];			/* �������� */
	char	cSpecimenDiv[8+1];			/* ���̋敪 */
	char	cIdSpec[1+1];				/* ID�d�l */
	char	cIdSpecimenId[13+1];		/* ����ID */
	char	cRackNum[8+1];				/* ���b�N�ԍ� */
	char	cRackPosNum[2+1];			/* ���b�N���ʒu�ԍ� */
	char	cTtNum[2+1];				/* TT�ԍ� */
	char	cCupNum[2+1];				/* CUP�ʒu�ԍ� */
	char	cReserve[16+1];				/* �\�� */
	char	cCom1[16+1];				/* �R�����g�P */
	char	cCom2[16+1];				/* �R�����g�Q */
	char	cSex[1+1];					/* ���� */
	char	cAge[3+1];					/* �N�� */
	char	cCollBlooddDay[8+1];		/* �̌��� */
	char	cDiltCoeff[4+1];			/* ��ߌW�� */
	char	cSpecimenType[1+1];			/* ���̎�� */
	char	cCntnrType[1+1];			/* �e���� */
	char	cItemNum[3+1];				/* ���ڔԍ� */
	char	cAnalysCond[1+1];			/* ���͏��� */
	char	cStndrdDensity[1+1];		/* �W���Z�x */
	char	cMeasureVal[8+1];			/* ����l */
	char	cMark[3+1];					/* �}�[�N */
	char	cEditDatMark[1+1];			/* �ҏW�f�[�^�}�[�N */
	char	cRepeatNum[1+1];			/* �J��Ԃ��� */
	char	cUserCode[3+1];				/* ���[�U�[�R�[�h */
	char	cMeasureBlkNum[1+1];		/* ����u���b�N�ԍ� */
	char	cEndCode[5+1];				/* �I���R�[�h */
};

/* �˗����� */
struct REQ_ITEM {	
	char	cItemNum[3+1];				/* ���ڔԍ� */
	char	cAnalysCond[1+1];			/* ���͏��� */
};

/* ���ڑI���w���e�L�X�g(�O��l����) */
struct ITEM_SEL_INST_TXT_NO_VAL {	
	char	cStartCode[1+1];			/* �J�n�R�[�h */
	char	cFrameNum[1+1];				/* �t���[���ԍ� */
	char	cTextType[1+1];				/* �e�L�X�g��� */
	char	cDevIdentifNum[1+1];		/* ���u���ʔԍ� */
	char	cAllBlockNum[2+1];			/* �S�u���b�N�� */
	char	cBlockNum[2+1];				/* �u���b�N�ԍ� */
	char	cItemNumInBlk[2+1];			/* �u���b�N�����ڐ� */
	char	cSpecimenDiv[1+1];			/* ���̋敪 */
	char	cRegstInf[1+1];				/* �o�^��� */
	char	cIdSpecimenId[13+1];		/* ����ID */
	char	cRackNum[8+1];				/* ���b�N�ԍ� */
	char	cRackPosNum[2+1];			/* ���b�N���ʒu�ԍ� */
//	char	cPosNum[11+1];				/* �ʒu�ԍ� */
	char	cCom1[16+1];				/* �R�����g�P */
	char	cCom2[16+1];				/* �R�����g�Q */
	char	cSex[1+1];					/* ���� */
	char	cAge[3+1];					/* �N�� */
	char	cCollBlooddDay[8+1];		/* �̌��� */
	char	cDiltCoeff[4+1];			/* ��ߌW�� */
	char	cSpecimenType[1+1];			/* ���̎�� */
	char	cCntnrType[1+1];			/* �e���� */
	struct REQ_ITEM	sReqItem[117];		/* �˗����� */
	char	cReserve[16+1];				/* �\�� */
	char	cEndCode[5+1];				/* �I���R�[�h */
};

/* �d��������f�[�^�e�L�X�g */
struct MEASURE_ELEC_TXT {	
	char	cStartCode[1+1];			/* �J�n�R�[�h */
	char	cFrameNum[1+1];				/* �t���[���ԍ� */
	char	cTextType[1+1];				/* �e�L�X�g��� */
	char	cDevIdentifNum[1+1];		/* ���u���ʔԍ� */
	char	cAllBlockNum[2+1];			/* �S�u���b�N�� */
	char	cBlockNum[2+1];				/* �u���b�N�ԍ� */
	char	cItemNumInBlk[2+1];			/* �u���b�N�����ڐ� */
	char	cInspectDay[8+1];			/* ������ */
	char	cInspectTm[6+1];			/* �������� */
	char	cSpecimenDiv[1+1];			/* ���̋敪 */
	char	cIdSpec[1+1];				/* ID�d�l */
	char	cIdSpecimenId[13+1];		/* ����ID */
	char	cRackNum[8+1];				/* ���b�N�ԍ� */
	char	cRackPosNum[2+1];			/* ���b�N���ʒu�ԍ� */
	char	cTtNum[2+1];				/* TT�ԍ� */
	char	cCupNum[2+1];				/* CUP�ʒu�ԍ� */
	char	cReserve[16+1];				/* �\�� */
	char	cCom1[16+1];				/* �R�����g�P */
	char	cCom2[16+1];				/* �R�����g�Q */
	char	cSex[1+1];					/* ���� */
	char	cAge[3+1];					/* �N�� */
	char	cCollBlooddDay[8+1];		/* �̌��� */
	char	cDiltCoeff[4+1];			/* ��ߌW�� */
	char	cSpecimenType[1+1];			/* ���̎�� */
	char	cCntnrType[1+1];			/* �e���� */
	char	cItemNum[3+1];				/* ���ڔԍ� */
	char	cAnalysCond[1+1];			/* ���͏��� */
	char	cMeasureVal[8+1];			/* ����l */
	char	cMark[3+1];					/* �}�[�N */
	char	cEditDatMark[1+1];			/* �ҏW�f�[�^�}�[�N */
	char	cUserCode[3+1];				/* ���[�U�[�R�[�h */
	char	cMeasureBlkNum[1+1];		/* ����u���b�N�ԍ� */
	char	cEndCode[5+1];				/* �I���R�[�h */
};

/* ���͋@��� */
typedef struct bunseki_inf {
	char	aIpAddr[100];				/* IP�A�h���X */
	int		iPortNum;					/* �|�[�g�ԍ� */
	char	aGouki[4];					/* ���@�ԍ� */
	/* ADD 2006-08-21 E.Osada ���M�^�C�}�ǉ� */
	int		iSendTimer;					/* ���M�^�C�}(msec) */
}BUNSEKI_INF;

/* X-M��� */
typedef struct xbarm_inf {
	int		iGoukiNum;					/* ���@ */
	int		iModuleNum;					/* ���W���[�� */
	char	kmkcd[8];					/* ���ڔԍ� */
	int		iNumCnt;					/* �J�E���^ */
	int		knsseqst;					/* ����SEQ-START */
	int		knsseqed;					/* ����SEQ-END */
	int		bskseqst;					/* ���͋@SEQ-START */
	int		bskseqed;					/* ���͋@SEQ-END */
	int		pltseqst;					/* �v���b�gSEQ-START */
	int		pltseqed;					/* �v���b�gSEQ-END */
	double	xbarmkka;					/* X-M���� */
	double	xbarmsum;					/* X-M���v�l */
	int		xmcount;					/* X-M�J�E���g */
	char	xmchk;						/* X-M���ʏo�͋��t���O */
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** X-M���v�l�����ł͌v�Z������Ȃ��ꍇ������ ***/
	double  xmsub;						/* X-M���ʂƂ̍������v */
	char    knsgrp[17];					/* �����O���[�v */
	int		iXbarmCnt;					/* �������ɕK�v */
	int		iXbarmNum;					/* �������ɕK�v */
	int		saiken;						/* �Č�����     */
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
}XBARM_INF;

#define		XBARM_ITEM_NUM		(6*7*240)	/* ���@*���W���[��*���� */
#define		PLT_UNIT_DEF		10			/* �v���b�g�P��(default) */

/* �R���g���[����� */
typedef struct ctrl_inf {
	int		iGoukiNum;					/* ���@ */
	int		iModuleNum;					/* ���W���[�� */
	char	nbkmkcd[8];					/* �`���l�� */
	int		ctrlno;						/* �R���g���[��No */
}CTRL_INF;

#define		CTRL_ITEM_NUM		(6*7*60)	/* ���@*���W���[��*���� */

/* �ً}STAT��� */
typedef struct kinkyu_inf {
	char    bskkbn[5];
	char    knsgrp[17];
	char    kmkcd[8];
	char    nbkmkcd[8];
}KINKYU_INF;

/* ADD E.Osada �f�t�H���g���M�^�C���A�E�g */
#define DEFSNDTIMER		10
/**********************************************************************/
/*  �O���Q�Ɗ֐�                                                      */
/**********************************************************************/
extern int MakeFileName( char*, char*, int );		/* �t�@�C�����쐬���� */
extern int RealTimeChk(SOCKET_INF *p, SaikenInfo * fSaiken);
extern void GetModule (char *pFrom, int *pTo);
extern char GetXmSkFlg(char *pKnsgrp, char *pKmkcd, char *pKnskisymd);
extern char GetXmChkFlg(char *pKnsgrp, char *pKmkcd, char *pKnskisymd);
int chkDataAlarm(); 	/* ADD Haga 2006-08-02 */

#define sFncSyslog(p, f, m) _sFncSyslog(p, f, m, "", EXEFLG_NON, __FILE__, __LINE__)
/* �V�X�e�����O�o�� */
extern  void    _sFncSyslog (LOG_TRCKIND piPri, char * pcFncname,char * pcMsg , char * pcErrCode, char * pcExeFlg, char * file, long lineno) ;

/**********************************************************************/
/*  �O���Q�ƕϐ�                                                      */
/**********************************************************************/
extern struct	stcLogMember sLog;		/* ���O�o�͏��\���� */
extern char		aRcvBuf[550];			/* ��M�f�[�^�o�b�t�@ */
extern int		iSckConChk;				/* �\�P�b�g�ڑ��`�F�b�N */
extern time_t	tSckConTm;				/* �\�P�b�g�ڑ��^�C�} */ 
extern int		iBunsekiNum;			/* ���͋@���@�� */
extern int		iGouki;					/* ���@��� */
extern char		aFileNameStr[256];		/* �t�@�C�����G���A */
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
extern Kskbrmst *pKskbrmst;
extern int iKskbrmstNum;

/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
extern char     gXsaiken;				/* Xbarm�Č�����̂��߂̃t���O */
extern Xbarmmst *pXbarmmst;				/* X-M�����W�`�F�b�N�̂��ߒǉ� */
extern int iXbarmmstNum;
extern Rngchkmst *pRngchkmst;			/* ���������W�`�F�b�N�̂��ߒǉ� */
extern int iRngchkmstNum;
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */

#endif /* DD201.h */
