/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：OutputXbarm.c                                                */
/* 　概　　　要：X-M結果情報出力       	                                      */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/03/20     A.Yamada       新規作成                           */
/******************************************************************************/

/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
//#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

//#include "DD41399.h"
#include "OutputXbarm.h"

/******************************************************************************/
/*  関数宣言                                                                  */
/******************************************************************************/
int OutputXbarm(SOCKET_INF*);				/* X-M結果出力処理 */

/******************************************************************************/
/*  関 数 名　：OutputXbarm()  		     				     			      */
/*  機能概要　：X-M結果出力	     			            					  */
/*  入　　力　：                                                              */
/*　 第１引数 ：SOCKET_INF*		分析機情報                         		      */
/*  出　　力　：                                                              */
/*  復帰情報　： RTN_OK		: 成功											  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
int OutputXbarm( SOCKET_INF* p )
{
	int iCnt;
//	int iCnt2;
	int iLen;
//	char aWrkBuf[1024];
	char* aWrkBuf;
	char aWrkBuf2[255];
	FILE *fp;

	time_t t = time(NULL);
	struct tm* tm;
	struct timeval tv;
	//char cWrk[30];
	char cWrk[512];
	char aFunc[512];

	memcpy(aFunc,__func__,sizeof(aFunc));
//	SetLogDat(TRCKIND_TRACE,aFunc,"xxx","xxx","xxx","xxx","xxx");
//	ZbmlPutLog(&sLog);

	printf( "OutputXbarm()\n" );

	memset( cWrk,0,sizeof(cWrk) );
	if( (p->cRackNum[0] >= 0x30) && (p->cRackNum[0] <= 0x39) ) {
		sprintf( cWrk,"%d",atoi(p->cRackNum) );
	} else {
		strcpy( cWrk,p->cRackNum );
	}

//	MakeFileName( p->cRackNum, p->cRackPosNum );
	MakeFileName( cWrk, p->cRackPosNum, 1 );

//	memset( aWrkBuf2, 0, sizeof(aWrkBuf2) );
//	strcpy( aWrkBuf2,aKekkaFolder );
//	strcat( aWrkBuf2,"XM_" );
//	strcat( aWrkBuf2,aFileNameStr );

	// ファイルの存在確認
	int loopCnt = 0;
	int	len = strlen(aFileNameStr) - 3;
	while (1) {
		struct stat	fst;
		memset( aWrkBuf2, 0, sizeof(aWrkBuf2) );
		strcpy( aWrkBuf2,aKekkaFolder );
		strcat( aWrkBuf2,"XM_" );
		strcat( aWrkBuf2,aFileNameStr );

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

	printf( "ファイル名:%s\n",aWrkBuf2 );

	fp = fopen( aWrkBuf2,"a");
	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "OutputXbarm()", "ファイルのオープンに失敗しました。" ) ;
		printf("ファイルのオープンに失敗しました。\n");
		return RTN_NG;
	}

	aWrkBuf = malloc(sizeof(char)*1024);

//	for( iCnt2=0; iCnt2<iItemNum; iCnt2++ ) {
	memset( aWrkBuf, 0, 1024 );
	/* No. 1 検査開始日設定 */
	strncat( aWrkBuf,p->sXbarm.knskisymd,strlen(p->sXbarm.knskisymd) );
	strcat( aWrkBuf,"," );
	/* No. 2 分析機区分取得 */
	strncat( aWrkBuf,p->sXbarm.bskkbn,strlen(p->sXbarm.bskkbn) );
	strcat( aWrkBuf,"," );
	/* No. 3 分析機ライン取得 */
	strncat( aWrkBuf,p->sXbarm.bsklne,strlen(p->sXbarm.bsklne) );
	strcat( aWrkBuf,"," );
	/* No.4 分析機号機 */
	strncat( aWrkBuf,p->sXbarm.bskgok,strlen(p->sXbarm.bskgok) );
	strcat( aWrkBuf,"," );
	/* No. 5 検査グループ設定 */
	strncat( aWrkBuf,p->sXbarm.knsgrp,strlen(p->sXbarm.knsgrp) );
	strcat( aWrkBuf,"," );
	/* No. 6 項目コード */
	strncat( aWrkBuf,p->sXbarm.kmkcd,strlen(p->sXbarm.kmkcd) );
	strcat( aWrkBuf,"," );
	/* No. 7 内部項目コード */
	strncat( aWrkBuf,p->sXbarm.nbkmkcd,strlen(p->sXbarm.nbkmkcd) );
	strcat( aWrkBuf,"," );
	/* No. 8 プロットNo設定 */
	sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->sXbarm.pltno );
	strcat( aWrkBuf,"," );
	/* No. 9 検査SEQ-START設定 */
	sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->sXbarm.knsseqst );
	strcat( aWrkBuf,"," );
	/* No.10 検査SEQ-END設定 */
	sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->sXbarm.knsseqed );
	strcat( aWrkBuf,"," );
	/* No.11 分析機SEQ-START設定 */
	sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->sXbarm.bskseqst );
	strcat( aWrkBuf,"," );
	/* No.12 分析機SEQ-END設定 */
	sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->sXbarm.bskseqed );
	strcat( aWrkBuf,"," );
	/* No.13 プロットSEQ-START設定 */
	sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->sXbarm.pltseqst );
	strcat( aWrkBuf,"," );
	/* No.14 プロットSEQ-END設定 */
	sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->sXbarm.pltseqed );
	strcat( aWrkBuf,"," );
	/* No.15 プロット数設定 */
	sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->sXbarm.pltsu );
	strcat( aWrkBuf,"," );
	/* No.16 X-M結果 */
	strncat( aWrkBuf,p->sXbarm.xbarmkka,strlen(p->sXbarm.xbarmkka) );
	strcat( aWrkBuf,"," );
	/* No.17 X-M状態区分設定 */
	if( p->sXbarm.xbarmjtkbn == 0 ) {
		p->sXbarm.xbarmjtkbn = ' ';
	}
	strncat( aWrkBuf,&(p->sXbarm.xbarmjtkbn),1 );
	strcat( aWrkBuf,"," );
	/* No.18 X-M確定フラグ設定 */
	if( p->sXbarm.xbarmjkflg == 0 ) {
		p->sXbarm.xbarmjkflg = ' ';
	}
	strncat( aWrkBuf,&(p->sXbarm.xbarmjkflg),1 );
	strcat( aWrkBuf,"," );
	/* No.19 情報更新日時 */
	memset( cWrk, 0, sizeof(cWrk) );
	tm = localtime(&t);
	gettimeofday( &tv, NULL );
	sprintf( cWrk, "%ld", tv.tv_usec );
	sprintf( &aWrkBuf[strlen(aWrkBuf)], "%04d-%02d-%02d %02d:%02d:%02d", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec );

	iLen = strlen( aWrkBuf );
	aWrkBuf[iLen] = CR;

	iLen = strlen(aWrkBuf);
	for( iCnt=0; iCnt<iLen; iCnt++ ) {
		if( aWrkBuf[iCnt] == CR ){
			fprintf(fp,"%c",'\n');
			break;
		}
		fprintf(fp,"%c",aWrkBuf[iCnt]);
	}
//		fclose(fp);
//	}

	free( aWrkBuf );
	fclose(fp);

	// Indexの作成
	memset( aWrkBuf2, 0, sizeof(aWrkBuf2) );
	strcpy( aWrkBuf2,aKekkaFolder );
	strcat( aWrkBuf2,"../Index/" );
	strcat( aWrkBuf2,"XM_" );
	strcat( aWrkBuf2,aFileNameStr );
	
	close(open(aWrkBuf2, O_CREAT, 0644));
	
	return RTN_OK;
}
