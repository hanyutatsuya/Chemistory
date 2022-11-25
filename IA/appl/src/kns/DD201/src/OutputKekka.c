/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：OutputKekka.c                                                */
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
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

//#include "DD41399.h"
#include "OutputKekka.h"

/******************************************************************************/
/*  関数宣言                                                                  */
/******************************************************************************/
int OutputKekka(SOCKET_INF*);			/* 結果情報出力処理 */

/******************************************************************************/
/*  関 数 名　：OutputKekka()  			     				     			  */
/*  機能概要　：結果情報出力												  */
/*  入　　力　：                                                              */
/*　 第１引数 ：SOCKET_INF*		分析機情報                         		      */
/*  出　　力　：                                                              */
/*  復帰情報　： RTN_OK		: 成功											  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
int OutputKekka( SOCKET_INF* p )
{
	int iCnt;
	int iCnt2;
	int iLen;
//	char aWrkBuf[1024];
	char* aWrkBuf;
	char aWrkBuf2[255];
	FILE *fp;
	time_t t = time(NULL);
	struct tm* tm;
	struct timeval tv;
	//char cWrk[30];
	char cWrk[30];
//	char aFunc[32];

	//memcpy(aFunc,__func__,sizeof(aFunc));
//	SetLogDat(TRCKIND_TRACE,aFunc,"xxx","xxx","xxx","xxx","xxx");
//	ZbmlPutLog(&sLog);

	printf( "OutputKekka()\n" );

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
//	strcat( aWrkBuf2,aFileNameStr );

	// ファイルの存在確認
	int loopCnt = 0;
	int	len = strlen(aFileNameStr) - 3;
	while (1) {
		struct stat	fst;

		memset( aWrkBuf2, 0, sizeof(aWrkBuf2) );
		strcpy( aWrkBuf2,aKekkaFolder );
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

	aWrkBuf = malloc(sizeof(char)*1024);

	printf( "OutputKekka(%s)\n",aWrkBuf2 );
	fp = fopen( aWrkBuf2,"a");
	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "OutputKekka()", "ファイルのオープンに失敗しました。" ) ;
		printf("ファイルのオープンに失敗しました。\n");
		return RTN_NG;
	}

	// コントロール番号の確認（一番小さい値を探す）
	int ctrlNo = 99999999;
	for( iCnt2=0; iCnt2<p->iKekkaNum; iCnt2++ ) {
#ifdef _DEBUG_
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].kmkcd  = %s\n", __LINE__, p->pKekka[iCnt2].kmkcd );
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].ctrlno = %d\n", __LINE__, p->pKekka[iCnt2].ctrlno );
#endif
		if (p->pKekka[iCnt2].knsflg == 'H') continue;
		if (p->pKekka[iCnt2].ctrlno < ctrlNo) {
			ctrlNo = p->pKekka[iCnt2].ctrlno;
#ifdef _DEBUG_
		printf( "OutputKekka(%d) :     p->pKekka[iCnt2].kmkcd = %s\n", __LINE__, p->pKekka[iCnt2].kmkcd );
		printf( "OutputKekka(%d) :     ctrlNo                 = %d\n", __LINE__, ctrlNo );
#endif
		}
	}
	// コントロール番号の再設定
	for( iCnt2=0; iCnt2<p->iKekkaNum; iCnt2++ ) {
#ifdef _DEBUG_
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].kmkcd    = %s\n", __LINE__, p->pKekka[iCnt2].kmkcd );
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].ctrlno 1 = %d\n", __LINE__, p->pKekka[iCnt2].ctrlno );
#endif
		p->pKekka[iCnt2].ctrlno = ctrlNo;
#ifdef _DEBUG_
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].ctrlno 2 = %d\n", __LINE__, p->pKekka[iCnt2].ctrlno );
#endif
	}


	for( iCnt2=0; iCnt2<p->iKekkaNum; iCnt2++ ) {
		memset( aWrkBuf, 0, 1024 );
		/* No. 1 検査開始日設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].knskisymd,strlen(p->pKekka[iCnt2].knskisymd) );
		strcat( aWrkBuf,"," );
		/* No. 2 処理日取得 */
		strncat( aWrkBuf,p->pKekka[iCnt2].sriymd,strlen(p->pKekka[iCnt2].sriymd) );
		strcat( aWrkBuf,"," );
		/* No. 3 検体No取得 */
		strncat( aWrkBuf,p->pKekka[iCnt2].kntno,strlen(p->pKekka[iCnt2].kntno) );
		strcat( aWrkBuf,"," );
		/* No. 4 検体No桁数フラグ取得 */
		if( p->pKekka[iCnt2].kntketflg == 0 ) {
			p->pKekka[iCnt2].kntketflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].kntketflg),1 );
		strcat( aWrkBuf,"," );
		/* No. 5 検査グループ設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].knsgrp,strlen(p->pKekka[iCnt2].knsgrp) );
		strcat( aWrkBuf,"," );
		/* No. 6 項目コード */
		strncat( aWrkBuf,p->pKekka[iCnt2].kmkcd,strlen(p->pKekka[iCnt2].kmkcd) );
		strcat( aWrkBuf,"," );
		/* No. 7 検査回数設定 */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->pKekka[iCnt2].knssu );
		strcat( aWrkBuf,"," );
		/* No. 8 検査回数枝番設定 */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->pKekka[iCnt2].knssueda );
		strcat( aWrkBuf,"," );
		/* No. 9 依頼発生元区分設定 */
		if( p->pKekka[iCnt2].irihsmkbn == 0 ) {
			p->pKekka[iCnt2].irihsmkbn = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].irihsmkbn),1 );
		strcat( aWrkBuf,"," );
		/* No.10 依頼区分設定 */
		if( p->pKekka[iCnt2].irikbn == 0 ) {
			p->pKekka[iCnt2].irikbn = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].irikbn),1 );
		strcat( aWrkBuf,"," );
		/* No.11 検査工程区分設定 */
		if( p->pKekka[iCnt2].ksktkbn == 0 ) {
			p->pKekka[iCnt2].ksktkbn = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].ksktkbn),1 );
		strcat( aWrkBuf,"," );
		/* No.12 BML受付年月日設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].utkymd,strlen(p->pKekka[iCnt2].utkymd) );
		strcat( aWrkBuf,"," );
		/* No.13 依頼書No設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].irino,strlen(p->pKekka[iCnt2].irino) );
		strcat( aWrkBuf,"," );
		/* No.14 依頼書No桁数フラグ設定 */
		if( p->pKekka[iCnt2].iriketflg == 0 ) {
			p->pKekka[iCnt2].iriketflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].iriketflg),1 );
		strcat( aWrkBuf,"," );
		/* No.15 属性世代No設定 */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->pKekka[iCnt2].zssdino );
		strcat( aWrkBuf,"," );
		/* No.16 施設コード設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].sstcd,strlen(p->pKekka[iCnt2].sstcd) );
		strcat( aWrkBuf,"," );
		/* No.17 トレーID設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].trid,strlen(p->pKekka[iCnt2].trid) );
		strcat( aWrkBuf,"," );
		/* No.18 トレーポジション設定 */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->pKekka[iCnt2].trpos );
		strcat( aWrkBuf,"," );
		/* No.19 アッセイラックID */
		strncat( aWrkBuf,p->pKekka[iCnt2].asyrckid,strlen(p->pKekka[iCnt2].asyrckid) );
		strcat( aWrkBuf,"," );
		/* No.20 アッセイラックポジション */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->pKekka[iCnt2].asyrckpos );
		strcat( aWrkBuf,"," );
		/* No.21 親項目コード設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].oyakmkcd,strlen(p->pKekka[iCnt2].oyakmkcd) );
		strcat( aWrkBuf,"," );
		/* No.22 セクションコード設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].seccd,strlen(p->pKekka[iCnt2].seccd) );
		strcat( aWrkBuf,"," );
		/* No.23 分画負荷区分設定 */
		if( p->pKekka[iCnt2].bkfkkbn == 0 ) {
			p->pKekka[iCnt2].bkfkkbn = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].bkfkkbn),1 );
		strcat( aWrkBuf,"," );
		/* No.24 サンプリングコード設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].smpcd,strlen(p->pKekka[iCnt2].smpcd) );
		strcat( aWrkBuf,"," );
		/* No.25 分析機区分設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].bskkbn,strlen(p->pKekka[iCnt2].bskkbn) );
		strcat( aWrkBuf,"," );
		/* No.26 分析機ライン設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].bsklne,strlen(p->pKekka[iCnt2].bsklne) );
		strcat( aWrkBuf,"," );
		/* No.27 分析機号機 */
		strncat( aWrkBuf,p->pKekka[iCnt2].bskgok,strlen(p->pKekka[iCnt2].bskgok) );
		strcat( aWrkBuf,"," );
		/* No.28 分析機SEQ */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->pKekka[iCnt2].bskseq );
		strcat( aWrkBuf,"," );
		/* No.29 分析機エラーステータス */
		strncat( aWrkBuf,p->pKekka[iCnt2].bskerrsts,strlen(p->pKekka[iCnt2].bskerrsts) );
		strcat( aWrkBuf,"," );
		/* No.30 測定日時 */
		strncat( aWrkBuf,p->pKekka[iCnt2].sktdh,strlen(p->pKekka[iCnt2].sktdh) );
		strcat( aWrkBuf,"," );
		/* No.31 内部項目コード設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].nbkmkcd,strlen(p->pKekka[iCnt2].nbkmkcd) );
		strcat( aWrkBuf,"," );
		/* No.32 定性・定量フラグ設定 */
		if( p->pKekka[iCnt2].tstrflg == 0 ) {
			p->pKekka[iCnt2].tstrflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].tstrflg),1 );
		strcat( aWrkBuf,"," );
		/* No.33 材料コード設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].zrcd,strlen(p->pKekka[iCnt2].zrcd) );
		strcat( aWrkBuf,"," );
		/* No.34 優先レベル取得 */
		strncat( aWrkBuf,p->pKekka[iCnt2].ysnlbl,strlen(p->pKekka[iCnt2].ysnlbl) );
		strcat( aWrkBuf,"," );
		/* No.35 基準値NO取得 */
		strncat( aWrkBuf,p->pKekka[iCnt2].kjno,strlen(p->pKekka[iCnt2].kjno) );
		strcat( aWrkBuf,"," );
		/* No.36 負荷報告NO表示区分取得 */
		if( p->pKekka[iCnt2].fkhkknohjkbn == 0 ) {
			p->pKekka[iCnt2].fkhkknohjkbn = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].fkhkknohjkbn),1 );
		strcat( aWrkBuf,"," );
		/* No.37 特別基準値NO取得 */
		strncat( aWrkBuf,p->pKekka[iCnt2].tbkjno,strlen(p->pKekka[iCnt2].tbkjno) );
		strcat( aWrkBuf,"," );
		/* No.38 特別基準値フラグ取得 */
		if( p->pKekka[iCnt2].tbkjflg == 0 ) {
			p->pKekka[iCnt2].tbkjflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].tbkjflg),1 );
		strcat( aWrkBuf,"," );
		/* No.39 非定型付加時間取得 */
		strncat( aWrkBuf,p->pKekka[iCnt2].htkfkhms,strlen(p->pKekka[iCnt2].htkfkhms) );
		strcat( aWrkBuf,"," );
		/* No.40 集検フラグ取得 */
		if( p->pKekka[iCnt2].skflg == 0 ) {
			p->pKekka[iCnt2].skflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].skflg),1 );
		strcat( aWrkBuf,"," );
		/* No.41 透折フラグ取得 */
		strncat( aWrkBuf,p->pKekka[iCnt2].tskflg,strlen(p->pKekka[iCnt2].tskflg) );
		strcat( aWrkBuf,"," );
		/* No.42 凍結フラグ取得 */
		strncat( aWrkBuf,p->pKekka[iCnt2].tktflg,strlen(p->pKekka[iCnt2].tktflg) );
		strcat( aWrkBuf,"," );
		/* No.43実施希釈倍率 */
		strncat( aWrkBuf,p->pKekka[iCnt2].jisksbr,strlen(p->pKekka[iCnt2].jisksbr) );
		strcat( aWrkBuf,"," );
		/* No.44 緊急報告フラグ設定 */
		if( p->pKekka[iCnt2].kkflg == 0 ) {
			p->pKekka[iCnt2].kkflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].kkflg),1 );
		strcat( aWrkBuf,"," );
		/* No.45 緊急依頼フラグ設定 */
		if( p->pKekka[iCnt2].kkiriflg == 0 ) {
			p->pKekka[iCnt2].kkiriflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].kkiriflg),1 );
		strcat( aWrkBuf,"," );
		/* No.46 緊急依頼ロットNo設定 */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->pKekka[iCnt2].kkirilotno );
		strcat( aWrkBuf,"," );
		/* No.47 非照会フラグ設定 */
		if( p->pKekka[iCnt2].hsykflg == 0 ) {
			p->pKekka[iCnt2].hsykflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].hsykflg),1 );
		strcat( aWrkBuf,"," );
		/* No.48 非請求フラグ設定 */
		if( p->pKekka[iCnt2].hskflg == 0 ) {
			p->pKekka[iCnt2].hskflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].hskflg),1 );
		strcat( aWrkBuf,"," );
		/* No.49 非報告フラグ設定 */
		if( p->pKekka[iCnt2].hhkkflg == 0 ) {
			p->pKekka[iCnt2].hhkkflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].hhkkflg),1 );
		strcat( aWrkBuf,"," );
		/* No.50 生データ設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].rawdata,strlen(p->pKekka[iCnt2].rawdata) );
		strcat( aWrkBuf,"," );
		/* No.51 検査結果１設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].knskka1,strlen(p->pKekka[iCnt2].knskka1) );
		strcat( aWrkBuf,"," );
		/* No.52 検査結果２設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].knskka2,strlen(p->pKekka[iCnt2].knskka2) );
		strcat( aWrkBuf,"," );
		/* No.53 */
		strcat( aWrkBuf,"," );
		/* No.54 検査結果補足設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].kkahskcd,strlen(p->pKekka[iCnt2].kkahskcd) );
		strcat( aWrkBuf,"," );
		/* No.55 表示結果設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].hjkka,strlen(p->pKekka[iCnt2].hjkka) );
		strcat( aWrkBuf,"," );
		/* No.56 指数（SDI）設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].sdi,strlen(p->pKekka[iCnt2].sdi) );
		strcat( aWrkBuf,"," );
		/* No.57 結果コメント１設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].kkacmt1,strlen(p->pKekka[iCnt2].kkacmt1) );
		strcat( aWrkBuf,"," );
		/* No.58 結果コメント２設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].kkacmt2,strlen(p->pKekka[iCnt2].kkacmt2) );
		strcat( aWrkBuf,"," );
		/* No.59 結果状況コード設定 */
		if( p->pKekka[iCnt2].kkajkcd == 0 ) {
			p->pKekka[iCnt2].kkajkcd = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].kkajkcd),1 );
		strcat( aWrkBuf,"," );
		/* No.60 パニックレンジフラグ設定 */
		if( p->pKekka[iCnt2].pncrgflg == 0 ) {
			p->pKekka[iCnt2].pncrgflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].pncrgflg),1 );
		strcat( aWrkBuf,"," );
		/* No.61 検査室パニックレンジフラグ設定 */
		if( p->pKekka[iCnt2].knspncrgflg == 0 ) {
			p->pKekka[iCnt2].knspncrgflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].knspncrgflg),1 );
		strcat( aWrkBuf,"," );
		/* No.62 結果換算フラグ設定 */
		if( p->pKekka[iCnt2].kkaksflg == 0 ) {
			p->pKekka[iCnt2].kkaksflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].kkaksflg),1 );
		strcat( aWrkBuf,"," );
		/* No.63 結果修正フラグ設定 */
		if( p->pKekka[iCnt2].kkassflg == 0 ) {
			p->pKekka[iCnt2].kkassflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].kkassflg),1 );
		strcat( aWrkBuf,"," );
		/* No.64 異常値区分(男)設定 */
		if( p->pKekka[iCnt2].ijkbnm == 0 ) {
			p->pKekka[iCnt2].ijkbnm = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].ijkbnm),1 );
		strcat( aWrkBuf,"," );
		/* No.65 異常値区分(女)設定 */
		if( p->pKekka[iCnt2].ijkbnf == 0 ) {
			p->pKekka[iCnt2].ijkbnf = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].ijkbnf),1 );
		strcat( aWrkBuf,"," );
		/* No.66 異常値区分(不明)設定 */
		if( p->pKekka[iCnt2].ijkbnn == 0 ) {
			p->pKekka[iCnt2].ijkbnn = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].ijkbnn),1 );
		strcat( aWrkBuf,"," );
		/* No.67 特別異常値区分(男)設定 */
		if( p->pKekka[iCnt2].tbijkbnm == 0 ) {
			p->pKekka[iCnt2].tbijkbnm = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].tbijkbnm),1 );
		strcat( aWrkBuf,"," );
		/* No.68 特別異常値区分(女)設定 */
		if( p->pKekka[iCnt2].tbijkbnf == 0 ) {
			p->pKekka[iCnt2].tbijkbnf = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].tbijkbnf),1 );
		strcat( aWrkBuf,"," );
		/* No.69 特別異常値区分(不明)設定 */
		if( p->pKekka[iCnt2].tbijkbnn == 0 ) {
			p->pKekka[iCnt2].tbijkbnn = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].tbijkbnn),1 );
		strcat( aWrkBuf,"," );
		/* No.70 血清情報(乳び)レベル設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].nbdolbl,strlen(p->pKekka[iCnt2].nbdolbl) );
		strcat( aWrkBuf,"," );
		/* No.71 血清情報(乳び)エラーステータス設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].nbdoerr,strlen(p->pKekka[iCnt2].nbdoerr) );
		strcat( aWrkBuf,"," );
		/* No.72 血清情報(溶血)レベル設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].ykdolbl,strlen(p->pKekka[iCnt2].ykdolbl) );
		strcat( aWrkBuf,"," );
		/* No.73 血清情報(溶血)エラーステータス設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].ykdoerr,strlen(p->pKekka[iCnt2].ykdoerr) );
		strcat( aWrkBuf,"," );
		/* No.74 血清情報(etc)レベル設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].etclbl,strlen(p->pKekka[iCnt2].etclbl) );
		strcat( aWrkBuf,"," );
		/* No.75 血清情報(etc)エラーステータス設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].etcerr,strlen(p->pKekka[iCnt2].etcerr) );
		strcat( aWrkBuf,"," );
		/* No.76 コントロールNo */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->pKekka[iCnt2].ctrlno );
#ifdef _DEBUG_
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].kntno     = %s\n", __LINE__, p->pKekka[iCnt2].kntno );
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].knsgrp    = %s\n", __LINE__, p->pKekka[iCnt2].knsgrp );
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].kmkcd     = %s\n", __LINE__, p->pKekka[iCnt2].kmkcd );
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].knssu     = %d\n", __LINE__, p->pKekka[iCnt2].knssu );
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].irino     = %s\n", __LINE__, p->pKekka[iCnt2].irino );
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].asyrckid  = %s\n", __LINE__, p->pKekka[iCnt2].asyrckid );
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].asyrckpos = %d\n", __LINE__, p->pKekka[iCnt2].asyrckpos );
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].bskgok    = %s\n", __LINE__, p->pKekka[iCnt2].bskgok );
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].rawdata   = %s\n", __LINE__, p->pKekka[iCnt2].rawdata );
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].ctrlno    = %d\n", __LINE__, p->pKekka[iCnt2].ctrlno );
#endif
		strcat( aWrkBuf,"," );
		/* No. 77 検査SEQ設定 */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->pKekka[iCnt2].knsseq );
		strcat( aWrkBuf,"," );
		/* No. 78 検査バッチNo設定 */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->pKekka[iCnt2].bthno );
		strcat( aWrkBuf,"," );
		/* No. 79 プロットNo設定 */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->pKekka[iCnt2].pltno );
#ifdef _DEBUG_
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].pltno     = %d\n", __LINE__, p->pKekka[iCnt2].pltno );
#endif
		strcat( aWrkBuf,"," );
		/* No. 80 プロットSEQ設定 */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->pKekka[iCnt2].pltseq );
#ifdef _DEBUG_
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].pltseq    = %d\n", __LINE__, p->pKekka[iCnt2].pltseq );
#endif
		strcat( aWrkBuf,"," );
		/* No. 81 データ入力担当者設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].dtnrtts,strlen(p->pKekka[iCnt2].dtnrtts) );
		strcat( aWrkBuf,"," );
		/* No. 82 データ入力日時設定 */
/* [ start 060420 */
//		strncat( aWrkBuf,p->pKekka[iCnt2].dtnrdh,strlen(p->pKekka[iCnt2].dtnrdh) );
//		memset( cWrk, 0, sizeof(cWrk) );
		tm = localtime(&t);
		gettimeofday( &tv, NULL );
//		sprintf( cWrk, "%d", tv.tv_usec );
		sprintf( &aWrkBuf[strlen(aWrkBuf)], "%04d-%02d-%02d %02d:%02d:%02d", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec );
/* ] end 060420 */
		strcat( aWrkBuf,"," );
		/* No. 83 検査完了日時設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].knskrdh,strlen(p->pKekka[iCnt2].knskrdh) );
		strcat( aWrkBuf,"," );
		/* No. 84 報告日時設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].hkkdh,strlen(p->pKekka[iCnt2].hkkdh) );
		strcat( aWrkBuf,"," );
		/* No. 85 報告希望時間設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].hkkkbdh,strlen(p->pKekka[iCnt2].hkkkbdh) );
		strcat( aWrkBuf,"," );
		/* No. 86 次回報告予定日設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].zkhkkyymd,strlen(p->pKekka[iCnt2].zkhkkyymd) );
		strcat( aWrkBuf,"," );
		/* No. 87 次回報告予定時刻設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].zkhkkytme,strlen(p->pKekka[iCnt2].zkhkkytme) );
		strcat( aWrkBuf,"," );
		/* No. 88 フリー結果フラグ設定 */
		if( p->pKekka[iCnt2].frkkaflg == 0 ) {
			p->pKekka[iCnt2].frkkaflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].frkkaflg),1 );
		strcat( aWrkBuf,"," );
		/* No. 89 画像別紙フラグ設定 */
		if( p->pKekka[iCnt2].gzbsflg == 0 ) {
			p->pKekka[iCnt2].gzbsflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].gzbsflg),1 );
		strcat( aWrkBuf,"," );
		/* No. 90 補正フラグ設定 */
		if( p->pKekka[iCnt2].hsiflg == 0 ) {
			p->pKekka[iCnt2].hsiflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].hsiflg),1 );
		strcat( aWrkBuf,"," );
		/* No. 91 結果優先フラグ設定 */
		if( p->pKekka[iCnt2].kkaysnflg == 0 ) {
			p->pKekka[iCnt2].kkaysnflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].kkaysnflg),1 );
		strcat( aWrkBuf,"," );
		/* No. 92 手入力フラグ設定 */
		if( p->pKekka[iCnt2].tnyrkflg == 0 ) {
			p->pKekka[iCnt2].tnyrkflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].tnyrkflg),1 );
		strcat( aWrkBuf,"," );
		/* No. 93 採用フラグ設定 */
		if( p->pKekka[iCnt2].siyflg == 0 ) {
			p->pKekka[iCnt2].siyflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].siyflg),1 );
		strcat( aWrkBuf,"," );
		/* No. 94 検査フラグ設定 */
		if( p->pKekka[iCnt2].knsflg == 0 ) {
			p->pKekka[iCnt2].knsflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].knsflg),1 );
		strcat( aWrkBuf,"," );
		/* No. 95 再検フラグ01(レンジチェック)設定 */
		if( p->pKekka[iCnt2].renjicflg == 0 ) {
			p->pKekka[iCnt2].renjicflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].renjicflg),1 );
		strcat( aWrkBuf,"," );
		/* No. 96 再検フラグ02(相関チェック)設定 */
		if( p->pKekka[iCnt2].soukn1flg == 0 ) {
			p->pKekka[iCnt2].soukn1flg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].soukn1flg),1 );
		strcat( aWrkBuf,"," );
		/* No. 97 再検フラグ03(関連チェック)設定 */
		if( p->pKekka[iCnt2].kanrenflg == 0 ) {
			p->pKekka[iCnt2].kanrenflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].kanrenflg),1 );
		strcat( aWrkBuf,"," );
		/* No. 98 再検フラグ04(分画チェック)設定 */
		if( p->pKekka[iCnt2].bunkkuflg == 0 ) {
			p->pKekka[iCnt2].bunkkuflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].bunkkuflg),1 );
		strcat( aWrkBuf,"," );
		/* No. 99 再検フラグ05(乳び・溶血チェック)設定 */
		if( p->pKekka[iCnt2].kesseiflg == 0 ) {
			p->pKekka[iCnt2].kesseiflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].kesseiflg),1 );
		strcat( aWrkBuf,"," );
		/* No.100 再検フラグ06(履歴チェック)設定 */
		if( p->pKekka[iCnt2].rirekiflg == 0 ) {
			p->pKekka[iCnt2].rirekiflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].rirekiflg),1 );
		strcat( aWrkBuf,"," );
		/* No.101 再検フラグ07(照合チェック)設定 */
		if( p->pKekka[iCnt2].syougoflg == 0 ) {
			p->pKekka[iCnt2].syougoflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].syougoflg),1 );
		strcat( aWrkBuf,"," );
		/* No.102 再検フラグ08(計算チェック)設定 */
		if( p->pKekka[iCnt2].keisanflg == 0 ) {
			p->pKekka[iCnt2].keisanflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].keisanflg),1 );
		strcat( aWrkBuf,"," );
		/* No.103 再検フラグ09(１００％チェック)設定 */
		if( p->pKekka[iCnt2].per100flg == 0 ) {
			p->pKekka[iCnt2].per100flg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].per100flg),1 );
		strcat( aWrkBuf,"," );
		/* No.104 再検フラグ10(透析前後チェック)設定 */
		if( p->pKekka[iCnt2].tousekflg == 0 ) {
			p->pKekka[iCnt2].tousekflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].tousekflg),1 );
		strcat( aWrkBuf,"," );
		/* No.105 再検フラグ11(希釈再検チェック)設定 */
		if( p->pKekka[iCnt2].kisyakflg == 0 ) {
			p->pKekka[iCnt2].kisyakflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].kisyakflg),1 );
		strcat( aWrkBuf,"," );
		/* No.106 再検フラグ12(校正処理)設定 */
		if( p->pKekka[iCnt2].kouseiflg == 0 ) {
			p->pKekka[iCnt2].kouseiflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].kouseiflg),1 );
		strcat( aWrkBuf,"," );
		/* No.107 再検フラグ13(照合NG確定処理)設定 */
		if( p->pKekka[iCnt2].syoungflg == 0 ) {
			p->pKekka[iCnt2].syoungflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].syoungflg),1 );
		strcat( aWrkBuf,"," );
		/* No.108 再検フラグ14(相関チェック(WS間))設定 */
		if( p->pKekka[iCnt2].soukn2flg == 0 ) {
			p->pKekka[iCnt2].soukn2flg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].soukn2flg),1 );
		strcat( aWrkBuf,"," );
		/* No.109 再検フラグ15(負荷パターンチェック)設定 */
		if( p->pKekka[iCnt2].fukaptflg == 0 ) {
			p->pKekka[iCnt2].fukaptflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].fukaptflg),1 );
		strcat( aWrkBuf,"," );
		/* No.110 再検フラグ16(チェック状態フラグ01)設定 */
		if( p->pKekka[iCnt2].yobiflg01 == 0 ) {
			p->pKekka[iCnt2].yobiflg01 = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].yobiflg01),1 );
		strcat( aWrkBuf,"," );
		/* No.111 再検フラグ17(チェック状態フラグ02)設定 */
		if( p->pKekka[iCnt2].tobiflg02 == 0 ) {
			p->pKekka[iCnt2].tobiflg02 = ' ';
		}
#ifdef _DEBUG_
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].tobiflg02 = %c\n", __LINE__, p->pKekka[iCnt2].tobiflg02 );
#endif
		strncat( aWrkBuf,&(p->pKekka[iCnt2].tobiflg02),1 );
		strcat( aWrkBuf,"," );
		/* No.112 再検フラグ18(チェック状態フラグ03)設定 */
		if( p->pKekka[iCnt2].yobiflg03 == 0 ) {
			p->pKekka[iCnt2].yobiflg03 = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].yobiflg03),1 );
		strcat( aWrkBuf,"," );
		/* No.113 再検フラグ19(チェック状態フラグ04)設定 */
		if( p->pKekka[iCnt2].yobiflg04 == 0 ) {
			p->pKekka[iCnt2].yobiflg04 = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].yobiflg04),1 );
		strcat( aWrkBuf,"," );
		/* No.114 再検フラグ20(チェック状態フラグ05)設定 */
		if( p->pKekka[iCnt2].yobiflg05 == 0 ) {
			p->pKekka[iCnt2].yobiflg05 = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].yobiflg05),1 );
		strcat( aWrkBuf,"," );
		/* No.115 再検理由コードＡ設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].skrycda,strlen(p->pKekka[iCnt2].skrycda) );
		strcat( aWrkBuf,"," );
		/* No.116 再検理由コードＢ設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].skrycdb,strlen(p->pKekka[iCnt2].skrycdb) );
		strcat( aWrkBuf,"," );
		/* No.117 再検理由コードＣ設定 */
		strncat( aWrkBuf,p->pKekka[iCnt2].skrycdc,strlen(p->pKekka[iCnt2].skrycdc) );
		strcat( aWrkBuf,"," );
		/* No.118 情報更新日時  */
/* [ start 060420 */
//		memset( cWrk, 0, sizeof(cWrk) );
//		tm = localtime(&t);
//		gettimeofday( &tv, NULL );
//		sprintf( cWrk, "%d", tv.tv_usec );
/* ] end 060420 */

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
	}
	
	fclose(fp);
	free( aWrkBuf );

	// Indexの作成
	memset( aWrkBuf2, 0, sizeof(aWrkBuf2) );
	strcpy( aWrkBuf2,aKekkaFolder );
	strcat( aWrkBuf2,"../Index/" );
	strcat( aWrkBuf2,aFileNameStr );
	
	close(open(aWrkBuf2, O_CREAT, 0644));
	
	return RTN_OK;
}
