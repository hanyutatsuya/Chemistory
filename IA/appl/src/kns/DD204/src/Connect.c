/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：Connect.c                                                    */
/* 　概　　　要：ソケット接続        	                                      */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/31     A.Yamada       新規作成                           */
/******************************************************************************/

/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
//#include "DD41399.h"
#include "Socket.h"
#include "Connect.h"

/******************************************************************************/
/*  関数宣言                                                                  */
/******************************************************************************/
int Connect(int);						/* ソケット接続処理 */
int addlist(int ,int);					/* ソケット情報リスト追加 */
int GetCtrlSeq( char*,int*,int* );
/******************************************************************************/
/*  関 数 名　：Connect()					     							  */
/*  機能概要　：ソケット接続												  */
/*  入　　力　：                                                              */
/*　 第１引数 ：int			接続チェックトリガ                    		      */
/*  出　　力　：                                                              */
/*  復帰情報　： RTN_OK		: 成功											  */
/* 　　　　　　　RTN_NG		: 失敗											  */
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

	if( iInit == 0 ) {		/* 起動時以外 */
		/* ソケット接続タイマカウント */
		tNowTm = time(NULL);
		fWrk = difftime(tNowTm,tSckConTm);
//		printf("ソケット接続ウエイト時間：%f\n",fWrk);
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
				printf( "接続済みです。\n" );
				iWrk = 1;
			}
		}
		if( iWrk == 0 ) {
			if((sd=ClientInit(sBunsekiInf[iCnt3].aIpAddr, sBunsekiInf[iCnt3].iPortNum)) != SOCK_ERR) {
//				iGouki = iCnt3+1;
				if( addlist(sd,iCnt3) == 0 ) {
					iWrk2 = RTN_OK;
					printf( "接続に成功しました。\n" );
					printf( "open:%d\n",sd );
				} else {
					close(sd);
				}
			} else {
//				iWrk2 = 1;
				tSckConTm = time(NULL);
				iSckConChk = SCK_CON_NG;
				printf( "接続に失敗しました。\n" );
				sFncSyslog ( TRCKIND_ERROR, "Connect()", "分析機との接続に失敗しました。" ) ;
			}
		}
//		getchar();
	}
	printf( "\n" );
	return iWrk2;

}
/******************************************************************************/
/*  関 数 名　：addlist()					     							  */
/*  機能概要　：ソケット情報リスト追加  									  */
/*  入　　力　：                                                              */
/*　 第１引数 ：int			ソケット番号                        		      */
/*　 第２引数 ：int			分析機接続チェックカウンタ             		      */
/*  出　　力　：                                                              */
/*  復帰情報　： RTN_OK		: 成功											  */
/* 　　　　　　　RTN_NG		: 失敗											  */
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
	
	p = sSocketInf.next;   /* 先頭要素の次の要素のアドレス */
	q = &sSocketInf;       /* 先頭要素のアドレス */
	while( (p != NULL) && (sd>p->iSd)  )
	{
		q = p;         /* 追加位置の直前の要素のnextを後で設定するために、
			              追加位置の直前の要素のアドレスを記憶しておく */
		p = p->next;   /* 次の要素へ進む */
	}
	
	/* 新しく追加する要素のためのメモリ領域を確保する */
	newcell = malloc( sizeof(SOCKET_INF) );
	if( newcell == NULL )
	{
		puts( "メモリ不足" );
		return RTN_NG;
	}
	
	newcell->iSd = sd;  /* 新しい要素のデータを設定 */
	newcell->next = p;     /* 新しい要素の次の要素へのアドレスを設定 */
	if( p != NULL ) {
		p->prev = newcell;
	}
	newcell->prev = q;     /* 新しい要素の次の要素へのアドレスを設定 */
	q->next = newcell;     /* 新しい要素の直前の要素のnextに、新しい要素のアドレスを設定 */

	newcell->iPortNum = sBunsekiInf[wk].iPortNum;					/* ポート番号 */
	memset(newcell->aHostName,0,sizeof(newcell->aHostName));		/* ホスト名 */
	strncpy(newcell->aHostName,sBunsekiInf[wk].aIpAddr,sizeof(sBunsekiInf[wk].aIpAddr));		/* ホスト名 */
	memset(newcell->aGouki,0,sizeof(newcell->aGouki));			/* 号機 */
	strncpy(newcell->aGouki,sBunsekiInf[wk].aGouki,sizeof(sBunsekiInf[wk].aGouki));
	memset(newcell->aRcvTmpMsgBuf,0,sizeof(newcell->aRcvTmpMsgBuf));
	memset(newcell->aSndAllMsgBuf,0,sizeof(newcell->aSndAllMsgBuf));
	memset(newcell->aSndTmpBuf,0,sizeof(newcell->aSndTmpBuf));		/* 送信データ一時バッファクリア */
	newcell->cRcvFrameCtrlChar = 0xff;										/* 受信フレーム制御文字=エラー */
	newcell->cSndFrameCtrlChar = 0xff;										/* 送信フレーム制御文字=エラー */
	newcell->cFrameNum = 0;												/* フレーム番号 = 0 */
	newcell->cChkRcvData = NO_RCV_DATA;									/* 受信データなし */
	newcell->cSndDataReq = NO_SND_REQ;										/* 送信データ要求なし */
	newcell->cStatus = STAT_IDLE;											/* STATUS = idle */
	newcell->cChkRcvMessage = MESSAGE_NO_ERR;								/* 受信メッセージ判定 */
	newcell->cChkNextFrame = FRAME_END;									/* フレーム終了 */
	newcell->cSndFrameSeqNum = 0;											/* 次回フレーム送信カウンタ */
	newcell->iSndRetryCnt = 0;												/* フレーム送信リトライカウンタ */
	newcell->iRcvMsg = MSG_NON;												/* メッセージの意味 */
	memset(newcell->cRackNum,0,sizeof(newcell->cRackNum));
	memset(newcell->cRackPosNum,0,sizeof(newcell->cRackPosNum));
	newcell->iSndAgainReq = 0;													/* リンクコンテンションなし */
	memset(newcell->aSndAgainBuf,0,sizeof(newcell->aSndAgainBuf));		/*  全送信メッセージエリア(リンクコンテンション) */
	newcell->iSndBlockNum = 0;												/* 送信テキストブロック総数 */
	newcell->iSndBlockCnt = 0;												/* 送信テキストブロックカウンタ */
	newcell->iOrderNum = 0;													/* 依頼項目数 */
//	newcell->iInspctReqNum = 0;														/* 検査依頼件数 */
//	memset( newcell->aItemCode,0,sizeof(newcell->aItemCode) );				/* 検査項目ID格納エリア */
//	memset(&(newcell->sKekka),0,sizeof(newcell->sKekka));
	newcell->pKekka = NULL;
	newcell->pSaiken = NULL;
	newcell->iKekkaNum = 0;
	newcell->iKekkaCnt = 0;
	memset(&(newcell->sSndorder),0,sizeof(newcell->sSndorder));
	newcell->fTmOutVal = 0;												/* フレーム送信リトライカウンタ */
	for( iCnt=0;iCnt<7;iCnt++ ) {
		newcell->aPltseq[iCnt] = 0;
#ifdef _DEBUG_
	printf( "addlist(%d) : newcell->aPltseq[iCnt] = %d\n", __LINE__, newcell->aPltseq[iCnt] );
#endif
	}
	/* 初期化漏れ対応 */
	memset(&(newcell->CtrlInfo),0,sizeof(newcell->CtrlInfo));
	newcell->iCtrlSeq = 0;
	/* 血清項目のコントロールＮＯとかぶると紛らわしいので、初期値を変更する。 */
	newcell->iCtrlSeqCnt = iStartCtrlSeq; 
	if ( GetCtrlSeq( sBunsekiInf[wk].aGouki, &(newcell->iCtrlSeq), &(newcell->iCtrlSeqCnt) ) == RTN_NG ) {
		//	ADD 2006/07/29  Haga
    	//	分析機再起動時にコントロールＮＯにファイルの値を初期値とする
    	newcell->sCtrlkka.ctrlno = newcell->iCtrlSeqCnt ;
#ifdef _DEBUG_
		printf( "addlist(%d) : newcell->sCtrlkka.ctrlno = %d\n", __LINE__, newcell->sCtrlkka.ctrlno );
#endif
	}
	// ADD E.Osada 2006-08-21 送信タイマ設定
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

	printf( "ファイル名：%s\n",cWrk );

	fp = fopen(cWrk,"r");

	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "GetCtrlSeq()", "ファイルのオープンに失敗しました。" ) ;
		printf("ファイルのオープンに失敗しました。\n");
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
