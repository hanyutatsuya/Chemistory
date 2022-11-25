/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FConnect.c                                                    */
/* �@�T�@�@�@�v�F�\�P�b�g�ڑ�        	                                      */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/31     A.Yamada       �V�K�쐬                           */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
//#include "DD41399.h"
#include "Socket.h"
#include "Connect.h"

/******************************************************************************/
/*  �֐��錾                                                                  */
/******************************************************************************/
int Connect(int);						/* �\�P�b�g�ڑ����� */
int addlist(int ,int);					/* �\�P�b�g��񃊃X�g�ǉ� */
int GetCtrlSeq( char*,int*,int* );
/******************************************************************************/
/*  �� �� ���@�FConnect()					     							  */
/*  �@�\�T�v�@�F�\�P�b�g�ڑ�												  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fint			�ڑ��`�F�b�N�g���K                    		      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F RTN_OK		: ����											  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
int Connect(int iInit)
{
	SOCKET		sd;
	char		port[16];
//	FILE		*fp;
	char		str[32];
//	char		str2[16];
	int			iWrk;
	int			iWrk2;
	int			iCnt3;
	SOCKET_INF* p;
	time_t		tNowTm;
	float		fWrk;
	char cNum[4];
	char cWk[16];

	if( iSckConChk == SCK_CON_OK ) {
		return RTN_OK;
	}

	if( iInit == 0 ) {		/* �N�����ȊO */
		/* �\�P�b�g�ڑ��^�C�}�J�E���g */
		tNowTm = time(NULL);
		fWrk = difftime(tNowTm,tSckConTm);
//		printf("�\�P�b�g�ڑ��E�G�C�g���ԁF%f\n",fWrk);
		if( fWrk < TM_SCK_CON ) {
			for( p=sSocketInf.next; p!=NULL; p=p->next ) {
				return RTN_OK;
			}
			return RTN_NG;
		}
	}

//	memset(str2, 0, sizeof(str2));
//	memset(hostname, 0, sizeof(hostname));
	memset(cNum, 0, sizeof(cNum));
	iSckConChk = SCK_CON_OK;

	iWrk2 = RTN_NG;
	for( iCnt3=0; iCnt3<iBunsekiNum; iCnt3++ ) {
		memset(str, 0, sizeof(str));
		memset( cWk,0,sizeof(cWk) );
		memset(port, 0, sizeof(port));

//		portnum = sBunsekiInf[iCnt3].iPortNum;

		printf("goki = %s\n",sBunsekiInf[iCnt3].aGouki );
		printf("IP   = %s\n",sBunsekiInf[iCnt3].aIpAddr);
		printf("PORT = %d\n",sBunsekiInf[iCnt3].iPortNum);

		iWrk = 0;
		for( p=sSocketInf.next; p!=NULL; p=p->next ) {
			iWrk2 = RTN_OK;
			if( (sBunsekiInf[iCnt3].iPortNum == p->iPortNum) 
					&& (strcmp( sBunsekiInf[iCnt3].aIpAddr,p->aHostName ) == 0) ) {
				printf( "�ڑ��ς݂ł��B\n" );
				iWrk = 1;
			}
		}
		if( iWrk == 0 ) {
			if((sd=ClientInit(sBunsekiInf[iCnt3].aIpAddr, sBunsekiInf[iCnt3].iPortNum)) != SOCK_ERR) {
//				iGouki = iCnt3+1;
				if( addlist(sd,iCnt3) == 0 ) {
					iWrk2 = RTN_OK;
					printf( "�ڑ��ɐ������܂����B\n" );
					printf( "open:%d\n",sd );
				} else {
					close(sd);
				}
			} else {
//				iWrk2 = 1;
				tSckConTm = time(NULL);
				iSckConChk = SCK_CON_NG;
				printf( "�ڑ��Ɏ��s���܂����B\n" );
				sFncSyslog ( TRCKIND_ERROR, "Connect()", "���͋@�Ƃ̐ڑ��Ɏ��s���܂����B" ) ;
			}
		}
//		getchar();
	}
	printf( "\n" );
	return iWrk2;

}
/******************************************************************************/
/*  �� �� ���@�Faddlist()					     							  */
/*  �@�\�T�v�@�F�\�P�b�g��񃊃X�g�ǉ�  									  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fint			�\�P�b�g�ԍ�                        		      */
/*�@ ��Q���� �Fint			���͋@�ڑ��`�F�b�N�J�E���^             		      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F RTN_OK		: ����											  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
int addlist(int sd,int wk)
{
	SOCKET_INF* p, *q, *newcell;
	int iCnt;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));
//	SetLogDat(TRCKIND_TRACE,aFunc,"xxx","xxx","xxx","xxx","xxx");
//	ZbmlPutLog(&sLog);

	printf( "addlist()\n" );
	
	p = sSocketInf.next;   /* �擪�v�f�̎��̗v�f�̃A�h���X */
	q = &sSocketInf;       /* �擪�v�f�̃A�h���X */
	while( (p != NULL) && (sd>p->iSd)  )
	{
		q = p;         /* �ǉ��ʒu�̒��O�̗v�f��next����Őݒ肷�邽�߂ɁA
			              �ǉ��ʒu�̒��O�̗v�f�̃A�h���X���L�����Ă��� */
		p = p->next;   /* ���̗v�f�֐i�� */
	}
	
	/* �V�����ǉ�����v�f�̂��߂̃������̈���m�ۂ��� */
	newcell = malloc( sizeof(SOCKET_INF) );
	if( newcell == NULL )
	{
		puts( "�������s��" );
		return RTN_NG;
	}
	
	newcell->iSd = sd;  /* �V�����v�f�̃f�[�^��ݒ� */
	newcell->next = p;     /* �V�����v�f�̎��̗v�f�ւ̃A�h���X��ݒ� */
	if( p != NULL ) {
		p->prev = newcell;
	}
	newcell->prev = q;     /* �V�����v�f�̎��̗v�f�ւ̃A�h���X��ݒ� */
	q->next = newcell;     /* �V�����v�f�̒��O�̗v�f��next�ɁA�V�����v�f�̃A�h���X��ݒ� */

	newcell->iPortNum = sBunsekiInf[wk].iPortNum;					/* �|�[�g�ԍ� */
	memset(newcell->aHostName,0,sizeof(newcell->aHostName));		/* �z�X�g�� */
	strncpy(newcell->aHostName,sBunsekiInf[wk].aIpAddr,sizeof(sBunsekiInf[wk].aIpAddr));		/* �z�X�g�� */
	memset(newcell->aGouki,0,sizeof(newcell->aGouki));			/* ���@ */
	strncpy(newcell->aGouki,sBunsekiInf[wk].aGouki,sizeof(sBunsekiInf[wk].aGouki));
	memset(newcell->aRcvTmpMsgBuf,0,sizeof(newcell->aRcvTmpMsgBuf));
	memset(newcell->aSndAllMsgBuf,0,sizeof(newcell->aSndAllMsgBuf));
	memset(newcell->aSndTmpBuf,0,sizeof(newcell->aSndTmpBuf));		/* ���M�f�[�^�ꎞ�o�b�t�@�N���A */
	newcell->cRcvFrameCtrlChar = 0xff;										/* ��M�t���[�����䕶��=�G���[ */
	newcell->cSndFrameCtrlChar = 0xff;										/* ���M�t���[�����䕶��=�G���[ */
	newcell->cFrameNum = 0;												/* �t���[���ԍ� = 0 */
	newcell->cChkRcvData = NO_RCV_DATA;									/* ��M�f�[�^�Ȃ� */
	newcell->cSndDataReq = NO_SND_REQ;										/* ���M�f�[�^�v���Ȃ� */
	newcell->cStatus = STAT_IDLE;											/* STATUS = idle */
	newcell->cChkRcvMessage = MESSAGE_NO_ERR;								/* ��M���b�Z�[�W���� */
	newcell->cChkNextFrame = FRAME_END;									/* �t���[���I�� */
	newcell->cSndFrameSeqNum = 0;											/* ����t���[�����M�J�E���^ */
	newcell->iSndRetryCnt = 0;												/* �t���[�����M���g���C�J�E���^ */
	newcell->iRcvMsg = MSG_NON;												/* ���b�Z�[�W�̈Ӗ� */
	memset(newcell->cRackNum,0,sizeof(newcell->cRackNum));
	memset(newcell->cRackPosNum,0,sizeof(newcell->cRackPosNum));
	newcell->iSndAgainReq = 0;													/* �����N�R���e���V�����Ȃ� */
	memset(newcell->aSndAgainBuf,0,sizeof(newcell->aSndAgainBuf));		/*  �S���M���b�Z�[�W�G���A(�����N�R���e���V����) */
	newcell->iSndBlockNum = 0;												/* ���M�e�L�X�g�u���b�N���� */
	newcell->iSndBlockCnt = 0;												/* ���M�e�L�X�g�u���b�N�J�E���^ */
	newcell->iOrderNum = 0;													/* �˗����ڐ� */
//	newcell->iInspctReqNum = 0;														/* �����˗����� */
//	memset( newcell->aItemCode,0,sizeof(newcell->aItemCode) );				/* ��������ID�i�[�G���A */
//	memset(&(newcell->sKekka),0,sizeof(newcell->sKekka));
	newcell->pKekka = NULL;
	newcell->pSaiken = NULL;
	newcell->iKekkaNum = 0;
	newcell->iKekkaCnt = 0;
	memset(&(newcell->sSndorder),0,sizeof(newcell->sSndorder));
	newcell->fTmOutVal = 0;												/* �t���[�����M���g���C�J�E���^ */
	for( iCnt=0;iCnt<7;iCnt++ ) {
		newcell->aPltseq[iCnt] = 0;
#ifdef _DEBUG_
	printf( "addlist(%d) : newcell->aPltseq[iCnt] = %d\n", __LINE__, newcell->aPltseq[iCnt] );
#endif
	}
	/* �������R��Ή� */
	memset(&(newcell->CtrlInfo),0,sizeof(newcell->CtrlInfo));
	newcell->iCtrlSeq = 0;
	/* �������ڂ̃R���g���[���m�n�Ƃ��Ԃ�ƕ���킵���̂ŁA�����l��ύX����B */
	newcell->iCtrlSeqCnt = iStartCtrlSeq; 
	if ( GetCtrlSeq( sBunsekiInf[wk].aGouki, &(newcell->iCtrlSeq), &(newcell->iCtrlSeqCnt) ) == RTN_NG ) {
		//	ADD 2006/07/29  Haga
    	//	���͋@�ċN�����ɃR���g���[���m�n�Ƀt�@�C���̒l�������l�Ƃ���
    	newcell->sCtrlkka.ctrlno = newcell->iCtrlSeqCnt ;
#ifdef _DEBUG_
		printf( "addlist(%d) : newcell->sCtrlkka.ctrlno = %d\n", __LINE__, newcell->sCtrlkka.ctrlno );
#endif
	}
	// ADD E.Osada 2006-08-21 ���M�^�C�}�ݒ�
	newcell->iSendTimer = sBunsekiInf[wk].iSendTimer;
	//
	return(0);
}

int GetCtrlSeq( char* gouki,int* iseq,int* icnt )
{
	char	buff[256];
	char	cWrk[256];
	char	seq[128];
	char	cnt[128];
	FILE	*fp;
	int		iWrk;
	int		iCnt;
	int		iCnt2;
	char	aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));
//	SetLogDat(TRCKIND_TRACE,aFunc,"xxx","xxx","xxx","xxx","xxx");
//	ZbmlPutLog(&sLog);

#ifdef _DEBUG_
	printf( "GetCtrlSeq()\n" );
#endif

	memset( cWrk,0,sizeof(cWrk) );
	strcpy( cWrk,aLogOutFolder );
	strcat( cWrk, "ctrlseq_" );
	strcat( cWrk,gouki );
	strcat( cWrk, ".dat" );

	printf( "�t�@�C�����F%s\n",cWrk );

	fp = fopen(cWrk,"r");

	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "GetCtrlSeq()", "�t�@�C���̃I�[�v���Ɏ��s���܂����B" ) ;
		printf("�t�@�C���̃I�[�v���Ɏ��s���܂����B\n");
		return RTN_NG;
	}
	memset( buff,0,sizeof(buff) );
	memset( seq,0,sizeof(seq) );
	memset( cnt,0,sizeof(cnt) );
	fgets( buff, 256, fp );
	iWrk = strlen(buff);
	for( iCnt=0; iCnt<iWrk; iCnt++ ) {
		if( buff[iCnt] == ',' ) {
			break;
		}
		seq[iCnt] = buff[iCnt];
		*iseq = atoi(seq);
	}
	iCnt2 = 0;
	for( iCnt+=1; iCnt<iWrk; iCnt++ ) {
		if( buff[iCnt] == ',' ) {
			break;
		}
		cnt[iCnt2] = buff[iCnt];
		++iCnt2;
	}
	*icnt = atoi(cnt);
	fclose(fp);

	return RTN_OK;
}
