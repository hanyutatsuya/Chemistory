/**********************************************************************
 *                                                                    
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FSndData.c
 *     �T�v      �F�f�[�^���M
 
 *                                                                    
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006/01/31     A.Yamada       Create
 **********************************************************************/
//#include "DD41399.h"
#include "Socket.h"
#include "SndData.h"
#include "OutputComLog.h"

/**********************************************************************/
/*  �����֐��錾                                                      */
/**********************************************************************/
int SndData(SOCKET_INF*);					/* ���M�f�[�^�ݒ菈�� */
/**********************************************************************/
/*                                                                    */
/*   function name : SndData                                       */
/*                                                                    */
/*   purpose : ���M�f�[�^�쐬����                                     */
/*                                                                    */
/*   data : 2005.12.20                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
int SndData(SOCKET_INF* p)
{
	int iLen;
	char aSndBuf[520];
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));
//	SetLogDat(TRCKIND_TRACE,aFunc,"xxx","xxx","xxx","xxx","xxx");
//	ZbmlPutLog(&sLog);

//	printf("SndData\n");

	if( p == NULL ) {
		return 0;
	}

	if( p->cSndDataReq != SND_REQ ) {
//		printf("���M�v���Ȃ�\n");
		return 0;
	}

	memset(aSndBuf,0,sizeof(aSndBuf));						/* ���M�f�[�^�o�b�t�@�N���A */

	aSndBuf[0] = p->cSndFrameCtrlChar;
	if( aSndBuf[0] == STX ) {
		strcat( aSndBuf,p->aSndTmpBuf );
	}

	iLen = strlen(aSndBuf);

	printf("���M�f�[�^:%d\n",iLen);
#ifdef	_DEBUG_
	int iCnt;
	for( iCnt=0;iCnt<iLen;iCnt++) {
		printf("%02x",aSndBuf[iCnt]);
	}
	printf("\n");
#endif

// ADD E.Osada 2006-08-21 �ʐM�^�C���A�E�g�����p
	usleep(p->iSendTimer);
//
//	usleep(SLEEP_USEC);		/* �E�G�C�g */

	writen(p->iSd,aSndBuf,iLen);

	/* �ʐM���O�o�͏��� */
	OutputComLog( p,SND_LOG,aSndBuf );

	p->cSndDataReq = NO_SND_REQ;

	return 0;
}
