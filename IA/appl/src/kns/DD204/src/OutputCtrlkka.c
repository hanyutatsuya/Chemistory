/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：OutputCtrlkka.c                                              */
/* 　概　　　要：結果情報出力       	                                      */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/31     A.Yamada       新規作成                           */
/******************************************************************************/

/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
//#include <time.h>
#include <sys/time.h>

//#include "DD41399.h"
#include "OutputCtrlkka.h"

/******************************************************************************/
/*  関数宣言                                                                  */
/******************************************************************************/
int OutputCtrlkka(SOCKET_INF*);				/* コントロール結果出力処理 */

/******************************************************************************/
/*  関 数 名　：OutputCtrlkka()  		     				     			  */
/*  機能概要　：コントロール結果出力	　　								  */
/*  入　　力　：                                                              */
/*　 第１引数 ：SOCKET_INF*		分析機情報                         		      */
/*  出　　力　：                                                              */
/*  復帰情報　： RTN_OK		: 成功											  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
int OutputCtrlkka( SOCKET_INF* p )
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
	char cWrk[30];
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));
//	SetLogDat(TRCKIND_TRACE,aFunc,"xxx","xxx","xxx","xxx","xxx");
//	ZbmlPutLog(&sLog);

	printf( "OutputCtrlkka()\n" );
#if 0
	memset( cWrk,0,sizeof(cWrk) );
	if( (p->cRackNum[0] >= 0x30) && (p->cRackNum[0] <= 0x39) ) {
		sprintf( cWrk,"%d",atoi(p->cRackNum) );
	} else {
		strcpy( cWrk,p->cRackNum );
	}

//	MakeFileName( p->cRackNum, p->cRackPosNum );
//	MakeFileName( cWrk, p->cRackPosNum );
	MakeFileName( cWrk, p->aGouki, 1 );
#endif
	memset( aWrkBuf2, 0, sizeof(aWrkBuf2) );
	strcpy( aWrkBuf2,aCtrlkkaFolder );
	strcat( aWrkBuf2,"CT_" );
	strcat( aWrkBuf2,aFileNameStr );

	printf( "ファイル名:%s\n",aWrkBuf2 );

	fp = fopen( aWrkBuf2,"a");
	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "OutputCtrlkka()", "ファイルのオープンに失敗しました。" ) ;
		printf("ファイルのオープンに失敗しました。\n");
		return RTN_NG;
	}

		aWrkBuf = malloc(sizeof(char)*1024);

//	for( iCnt2=0; iCnt2<iItemNum; iCnt2++ ) {
		memset( aWrkBuf, 0, 1024 );
		/* No. 1 検査開始日設定 */
		strncat( aWrkBuf,p->sCtrlkka.knskisymd,strlen(p->sCtrlkka.knskisymd) );
		strcat( aWrkBuf,"," );
		/* No. 2 分析機区分取得 */
		strncat( aWrkBuf,p->sCtrlkka.bskkbn,strlen(p->sCtrlkka.bskkbn) );
		strcat( aWrkBuf,"," );
		/* No. 3 分析機ライン取得 */
		strncat( aWrkBuf,p->sCtrlkka.bsklne,strlen(p->sCtrlkka.bsklne) );
		strcat( aWrkBuf,"," );
		/* No.4 分析機号機 */
		strncat( aWrkBuf,p->sCtrlkka.bskgok,strlen(p->sCtrlkka.bskgok) );
		strcat( aWrkBuf,"," );
		/* No. 5 検査グループ設定 */
		strncat( aWrkBuf,p->sCtrlkka.knsgrp,strlen(p->sCtrlkka.knsgrp) );
		strcat( aWrkBuf,"," );
		/* No. 6 項目コード */
		strncat( aWrkBuf,p->sCtrlkka.kmkcd,strlen(p->sCtrlkka.kmkcd) );
		strcat( aWrkBuf,"," );
		/* No. 7 内部項目コード */
		strncat( aWrkBuf,p->sCtrlkka.nbkmkcd,strlen(p->sCtrlkka.nbkmkcd) );
		strcat( aWrkBuf,"," );
		/* No. 8 コントロールNo設定 */
#ifdef _DEBUG_
	printf( "OutputCtrlkka(%d) : p->sCtrlkka.ctrlno = %d\n", __LINE__, p->sCtrlkka.ctrlno );
#endif
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->sCtrlkka.ctrlno );
		strcat( aWrkBuf,"," );
		/* No. 9 コントロール種別設定 */
		strncat( aWrkBuf,p->sCtrlkka.ctrlsbt,strlen(p->sCtrlkka.ctrlsbt) );
		strcat( aWrkBuf,"," );
		/* No.10 コントロール種別枝番設定 */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->sCtrlkka.ctrlsbteda );
		strcat( aWrkBuf,"," );
		/* No.11 コントロールレベル設定 */
		strncat( aWrkBuf,p->sCtrlkka.ctrllbl,strlen(p->sCtrlkka.ctrllbl) );
		strcat( aWrkBuf,"," );
		/* No.12 定性・定量フラグ設定 */
		if( p->sCtrlkka.tstrflg == 0 ) {
			p->sCtrlkka.tstrflg = ' ';
		}
		strncat( aWrkBuf,&(p->sCtrlkka.tstrflg),1 );
		strcat( aWrkBuf,"," );
		/* No.13 アッセイラックID */
		strncat( aWrkBuf,p->sCtrlkka.asyrckid,strlen(p->sCtrlkka.asyrckid) );
		strcat( aWrkBuf,"," );
		/* No.14 アッセイラックポジション */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->sCtrlkka.asyrckpos );
		strcat( aWrkBuf,"," );
		/* No.15 検査SEQ設定 */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->sCtrlkka.knsseq );
		strcat( aWrkBuf,"," );
		/* No.16 分析機SEQ設定 */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->sCtrlkka.bskseq );
		strcat( aWrkBuf,"," );
		/* No.17 検査バッチNo設定 */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->sCtrlkka.bthno );
		strcat( aWrkBuf,"," );
		/* No.18 検査バッチ内ラック順番設定 */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->sCtrlkka.bthrckjbn );
		strcat( aWrkBuf,"," );
		/* No.19 試薬ロットNo設定 */
		strncat( aWrkBuf,p->sCtrlkka.syklotno,strlen(p->sCtrlkka.syklotno) );
		strcat( aWrkBuf,"," );
		/* No.20 測定値設定 */
		strncat( aWrkBuf,p->sCtrlkka.sktti,strlen(p->sCtrlkka.sktti) );
		strcat( aWrkBuf,"," );
		/* No.21 換算値設定 */
		strncat( aWrkBuf,p->sCtrlkka.knzti,strlen(p->sCtrlkka.knzti) );
		strcat( aWrkBuf,"," );
		/* No.22 換算値設定フラグ設定 */
		if( p->sCtrlkka.knztistflg == 0 ) {
			p->sCtrlkka.knztistflg = ' ';
		}
		strncat( aWrkBuf,&(p->sCtrlkka.knztistflg),1 );
		strcat( aWrkBuf,"," );
		/* No.23 測定日時設定 */
		strncat( aWrkBuf,p->sCtrlkka.sktdh,strlen(p->sCtrlkka.sktdh) );
		strcat( aWrkBuf,"," );
		/* No.24 コントロール状態設定 */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->sCtrlkka.ctrljti );
		strcat( aWrkBuf,"," );
		/* No.25 チェック済みフラグ設定 */
		if( p->sCtrlkka.chkzmflg == 0 ) {
			p->sCtrlkka.chkzmflg = ' ';
		}
		strncat( aWrkBuf,&(p->sCtrlkka.chkzmflg),1 );
		strcat( aWrkBuf,"," );
		/* No.26 ファクター */
		strncat( aWrkBuf,p->sCtrlkka.facter,strlen(p->sCtrlkka.facter) );
		strcat( aWrkBuf,"," );
		/* No.27 ベース設定 */
		strncat( aWrkBuf,p->sCtrlkka.base,strlen(p->sCtrlkka.base) );
		strcat( aWrkBuf,"," );
		/* No.28 校正状態設定 */
		if( p->sCtrlkka.kosijt == 0 ) {
			p->sCtrlkka.kosijt = ' ';
		}
		strncat( aWrkBuf,&(p->sCtrlkka.kosijt),1 );
		strcat( aWrkBuf,"," );
		/* No.29 校正担当者設定 */
		strncat( aWrkBuf,p->sCtrlkka.kositts,strlen(p->sCtrlkka.kositts) );
		strcat( aWrkBuf,"," );
		/* No.30 校正日時 */
		strncat( aWrkBuf,p->sCtrlkka.kosidh,strlen(p->sCtrlkka.kosidh) );
		strcat( aWrkBuf,"," );
		/* No.31 情報更新日時 */
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
#if 0
	// Indexの作成
	memset( aWrkBuf2, 0, sizeof(aWrkBuf2) );
	strcpy( aWrkBuf2,aKekkaFolder );
	strcat( aWrkBuf2,"../Index/" );
	strcat( aWrkBuf2,"CT_" );
	strcat( aWrkBuf2,aFileNameStr );
	
	close(open(aWrkBuf2, O_CREAT, 0644));
#endif
	return RTN_OK;
}
