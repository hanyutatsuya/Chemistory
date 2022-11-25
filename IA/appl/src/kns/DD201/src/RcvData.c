/**********************************************************************
 *                                                                    
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：RcvData.c
 *     概要      ：データ受信
 
 *                                                                    
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006/01/31     A.Yamada       Create
 **********************************************************************/
//#include "DD41399.h"
#include "Socket.h"
#include "RcvData.h"
#include "OutputComLog.h"

/**********************************************************************/
/*  内部関数宣言                                                      */
/**********************************************************************/
SOCKET_INF* RcvData(void);						/* ホストデータ受信処理 */
void DecodeRcvData(SOCKET_INF*,int);					/* デコード関数*/
/**********************************************************************/
/*                                                                    */
/*   function name : RcvData                                          */
/*                                                                    */
/*   purpose : ホストデータ受信処理                                   */
/*                                                                    */
/*   data : 2005.12.20                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
SOCKET_INF* RcvData(void)
{
	int len;
	int iCnt;
//	int i;
//	int wrksd[3];
	SOCKET sd;
	SOCKET_INF* p;
//	time_t tEndTm;
//	float fWrk;
	int aWrk[255];
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));
//	SetLogDat(TRCKIND_TRACE,aFunc,"xxx","xxx","xxx","xxx","xxx");
//	ZbmlPutLog(&sLog);

//	printf("RcvData()\n");

	memset( aWrk, 0, sizeof(aWrk) );

	for( p=sSocketInf.next,iCnt=0; p!=NULL; p=p->next,iCnt++ ) {
		aWrk[iCnt] = p->iSd;
	}

//	printf( "ソケット接続情報：" );
//	for( iCnt=0; iCnt<255; iCnt++ ) {
//		printf( "%d|",aWrk[iCnt] );
//		if( aWrk[iCnt] == 0 ) {
//			printf( "\n" );
//			break;
//		}
//	}

	sd = isSelect( aWrk, 0 );
//	printf( "SELECT<SD>:%d\n",sd );

	if( sd <= 0 ) {
		return NULL;
	}

	len = readAll(sd,aRcvBuf);

	for( p=sSocketInf.next,iCnt=0; p!=NULL; p=p->next,iCnt++ ) {
		if( sd == p->iSd ) {
			p->fTmOutVal = 0;
			break;
		}
	}

	if( len == 0 ) {		/* ソケットclose */
		if( p->next != NULL ) {
			p->prev->next = p->next;
			p->next->prev = p->prev;
		} else {
			p->prev->next = NULL;
		}
		free(p);
//		getchar();
		tSckConTm = time(NULL);
		iSckConChk = SCK_CON_NG;
        close(sd);
		printf( "close:%d\n",sd );
//		getchar();
		return NULL;
//	} else if( len < 0 ) {
//		printf("受信データなし\n");
//		p->cChkRcvData = NO_RCV_DATA;
//		return NULL;
//	} else if ( len > 247 ) {
//		p->cRcvFrameCtrlChar = 0xff;	/* エラー値設定 */
//		p->cChkRcvData = RCV_DATA_NG;
//		printf("受信データあり：%d\n",len);
//		return NULL;
	}

	printf("受信データあり：%d\n",len);
#ifdef	_DEBUG_
	for(iCnt=0;iCnt<len;iCnt++){
		printf("%02x",aRcvBuf[iCnt]);
	}
	printf("\n");	
#endif

	/* 通信ログ出力処理 */
	OutputComLog( p,RCV_LOG,aRcvBuf );

	DecodeRcvData(p,len);
	memset(aRcvBuf,0,sizeof(aRcvBuf));					/* 受信データバッファクリア */
	return p;
}
