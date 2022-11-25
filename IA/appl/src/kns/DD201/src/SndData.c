/**********************************************************************
 *                                                                    
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：SndData.c
 *     概要      ：データ送信
 
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
/*  内部関数宣言                                                      */
/**********************************************************************/
int SndData(SOCKET_INF*);					/* 送信データ設定処理 */
/**********************************************************************/
/*                                                                    */
/*   function name : SndData                                       */
/*                                                                    */
/*   purpose : 送信データ作成処理                                     */
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
//		printf("送信要求なし\n");
		return 0;
	}

	memset(aSndBuf,0,sizeof(aSndBuf));						/* 送信データバッファクリア */

	aSndBuf[0] = p->cSndFrameCtrlChar;
	if( aSndBuf[0] == STX ) {
		strcat( aSndBuf,p->aSndTmpBuf );
	}

	iLen = strlen(aSndBuf);

	printf("送信データ:%d\n",iLen);
#ifdef	_DEBUG_
	int iCnt;
	for( iCnt=0;iCnt<iLen;iCnt++) {
		printf("%02x",aSndBuf[iCnt]);
	}
	printf("\n");
#endif

// ADD E.Osada 2006-08-21 通信タイムアウト封じ用
	usleep(p->iSendTimer);
//
//	usleep(SLEEP_USEC);		/* ウエイト */

	writen(p->iSd,aSndBuf,iLen);

	/* 通信ログ出力処理 */
	OutputComLog( p,SND_LOG,aSndBuf );

	p->cSndDataReq = NO_SND_REQ;

	return 0;
}
