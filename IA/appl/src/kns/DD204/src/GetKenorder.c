/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：GetKenorder.c                                                */
/* 　概　　　要：検査オーダー取得     	                                      */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/31     A.Yamada       新規作成                           */
/******************************************************************************/

/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
//#include "DD41399.h"
#include "GetKenorder.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/******************************************************************************/
/*  関数宣言                                                                  */
/******************************************************************************/
int GetKenorder(SOCKET_INF* ,int, int*);	/* 検査オーダー取得処理 */

/******************************************************************************/
/*  関 数 名　：GetKenorder()  			         							  */
/*  機能概要　：検査オーダー取得	     									  */
/*  入　　力　：                                                              */
/*　 第１引数 ：SOCKET_INF*		分析機情報                         		      */
/*　 第２引数 ：int             オーダーファイル格納位置情報    		      */
/*　 第３引数 ：int*            オーダー件数         			 		      */
/*  出　　力　：                                                              */
/*  復帰情報　： RTN_OK		: 成功											  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
int GetKenorder(SOCKET_INF* p,int iType, int* reqnum)
{
	int iCnt;
	char aWrkBuf2[255];
	char aWrkBuf3[255];		// インデックス確認用
	char aWrkBuf4[255];		// ローカルコピー用
	char cWrk[32];
	FILE *fp;

	char ** pFld;
	int cnt;
	int offset;


//	char** buff;
//	char* buff;
	char buff[1024];
	char aFunc[32];

	struct stat stStat;

	memcpy(aFunc,__func__,sizeof(aFunc));
//	SetLogDat(TRCKIND_TRACE,aFunc,"xxx","xxx","xxx","xxx","xxx");
//	ZbmlPutLog(&sLog);


	printf( "GetKenorder()\n" );

	memset( cWrk,0,sizeof(cWrk) );
	sprintf( cWrk,"%d",atoi(p->cRackNum) );

//	MakeFileName( p->cRackNum, p->cRackPosNum );
	MakeFileName( cWrk, p->cRackPosNum, 0 );

	memset( aWrkBuf2, 0, sizeof(aWrkBuf2) );

	if( iType == ORDER_DAT_1 ) {
		strcpy( aWrkBuf2,aKenorderFolder );
		strcpy( aWrkBuf3,aKenorderFolder );
		strcat( aWrkBuf3,"../Index/" );
		strcpy( aWrkBuf4,aKenorderFolder );
		strcat( aWrkBuf4,"local" );
		memset(&stStat, 0, sizeof(stStat));
		if (stat(aWrkBuf4, &stStat) == -1) {
			if (errno == ENOENT) {	// ディレクトリが存在しない。
				// ディレクトリが存在しない時はlocalフォルダを作成する。
				mkdir(aWrkBuf4, 0777);
			}
		}
		strcat(aWrkBuf4,"/" );
	} else {
		strcpy( aWrkBuf2,aKenorderFolder2 );
		strcpy( aWrkBuf3,aKenorderFolder2 );
		strcat( aWrkBuf3,"../Index/" );
		strcpy( aWrkBuf4,aKenorderFolder2 );
		strcat( aWrkBuf4,"local/" );
	}
	strcat( aWrkBuf2,"OD_" );
	strcat( aWrkBuf2,aFileNameStr );
	strcat( aWrkBuf3,"OD_" );
	strcat( aWrkBuf3,aFileNameStr );
	strcat( aWrkBuf4,"OD_" );
	strcat( aWrkBuf4,aFileNameStr );

#ifdef _DEBUG_
	printf( "ファイル名:%s\n",aWrkBuf2 );
#endif
	// ファイルのオープン前にIndexフォルダを確認しファイルがあるかチェックする。
	// その後ローカル側のオーダファイルは、格納ホルダからlocalホルダに移動し使用する。
	if (stat(aWrkBuf3, &stStat) == -1) {
		sFncSyslog ( TRCKIND_ERROR, "GetKenorder()", "ファイルの存在しません。" ) ;
		printf("ファイルの存在しません。\n");
		return RTN_NG;
	}

	if( iType == ORDER_DAT_1 ) {
		if (stat(aWrkBuf2, &stStat) == 0) {
			if (stat(aWrkBuf4, &stStat) == 0) {
				// ローカル側に既にあるときはローカルのファイルを削除する。
				remove(aWrkBuf4);
			}
			if (rename(aWrkBuf2, aWrkBuf4) != 0) {
				sFncSyslog ( TRCKIND_ERROR, "GetKenorder()", "ファイルの移動に失敗しました。" ) ;
				printf("ファイルの移動に失敗しました。\n");
				strcpy(aWrkBuf4, aWrkBuf2);
			}
		}
		fp = fopen( aWrkBuf4,"r");
		
	}
	else {
		fp = fopen( aWrkBuf2,"r");
	}

	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "GetKenorder()", "ファイルのオープンに失敗しました。" ) ;
		printf("ファイルのオープンに失敗しました。\n");
		return RTN_NG;
	}

//	iCnt=0;
//	while ((iWrk = fgetc(fp)) != EOF){
//		aReadDatStr[iCnt] = (unsigned char)iWrk;
//		iCnt++;
//	}
//	fclose(fp);

//	printf( ".datファイルデータ：%s\n",aReadDatStr );


//	buff = (  char**)malloc(sizeof( char* )*MAX_ITEM_NUM );
//	for( iCnt=0; iCnt<MAX_ITEM_NUM; iCnt++ ) {
//		buff[iCnt] = (  char* )malloc( sizeof(  char )*512 );
//	}
//	for( iCnt=0; iCnt<MAX_ITEM_NUM; iCnt++ ) {
//		if( fgets( str, 511, fp ) == NULL ) {
//			break;
//		}
//		sprintf( buff[iCnt],"%s",str );
//		printf( "%s",buff[iCnt] );
//	}
//	for( iCnt = 0; iCnt < MAX_ITEM_NUM; iCnt++ ){
//		if( buff[iCnt] != NULL ) {
//			free( buff[iCnt] );
//		}
//	}
//	free( buff );
//	fclose( fp );

//	while( fgets( buff, 1024, fp ) != NULL ) {
//		++(*reqnum);
//	}
//iCnt = 
//	buff = malloc(sizeof(char)*1024);
	pKenorder = malloc(sizeof(Kenorder)*MAX_ITEM_NUM );
//	printf( "%02x\n",pKenorder[351].kmkcd[0] );

	


//	pKenorder = malloc(sizeof(KENORDER)*100 );
	for( iCnt=0; iCnt<MAX_ITEM_NUM; iCnt++ ) {
//	for( iCnt=0; iCnt<100; iCnt++ ) {
		memset( &pKenorder[iCnt],0,sizeof(Kenorder) );
	}

//	memset( &(p->kenorder),0,sizeof(p->kenorder) );

	while( fgets( buff, 1024, fp ) != NULL ) {
		if( *reqnum >= MAX_ITEM_NUM ) {
			break;
		}
//		printf( "%s",buff );
//		getchar();

		pFld = malloc(sizeof(char *)*100);
//		pKenOrder = malloc(sizeof(struct KENORDER));

		// カンマ区切りのレコードを分割し、DBレコードの構造体に設定する。
		cnt = 0;
		offset = 0;;
		pFld[cnt] = &buff[cnt];
		cnt++;
		while (buff[offset] != '\0') {
			if (buff[offset] == ',') {
				pFld[cnt++] = &buff[offset+1];
				buff[offset] = '\0';
			}
			offset++;
		}
		if (cnt != 58) {
			// フィールド数が一致しない
			sFncSyslog ( TRCKIND_ERROR, "GetKenorder()", "フィールド数が一致しませんでした。" ) ;
			printf( "フィールド数が一致しませんでした。\n" );
			break;
		}
		/* No. 1 開始年月日取得 */
		strcpy( pKenorder[*reqnum].knskisymd,pFld[0] );
		/* No. 2 処理日取得 */
		strcpy( pKenorder[*reqnum].sriymd,pFld[1] );
		/* No. 3 検体No取得 */
		strcpy( pKenorder[*reqnum].kntno,pFld[2] );
		/* No. 4 検体No桁数フラグ取得 */
		pKenorder[*reqnum].kntketflg = pFld[3][0];
		/* No. 5 検査グループ取得 */
		strcpy( pKenorder[*reqnum].knsgrp,pFld[4] );
		/* No. 6 項目コード取得 */
		strcpy( pKenorder[*reqnum].kmkcd,pFld[5] );
		/* No. 7 検査回数取得 */
		pKenorder[*reqnum].knssu = atoi(pFld[6]);
		/* No. 8 検査回数枝番取得 */
		pKenorder[*reqnum].knssueda = atoi(pFld[7]);
		/* No. 9 依頼発生元区分取得 */
		pKenorder[*reqnum].irihsmkbn = pFld[8][0];
		/* No.10 依頼区分取得 */
		pKenorder[*reqnum].irikbn = pFld[9][0];
		/* No.11 検査工程区分取得 */
		pKenorder[*reqnum].ksktkbn = pFld[10][0];
		/* No.12 BML受付年月日取得 */
		strcpy( pKenorder[*reqnum].utkymd,pFld[11] );
		/* No.13 依頼書No取得 */
		strcpy( pKenorder[*reqnum].irino,pFld[12] );
		/* No.14 依頼書No桁数フラグ取得 */
		pKenorder[*reqnum].iriketflg = pFld[13][0];
		/* No.15 属性世代No取得 */
		pKenorder[*reqnum].zssdino = atoi(pFld[14]);
		/* No.16 施設コード取得 */
		strcpy( pKenorder[*reqnum].sstcd,pFld[15] );
		/* No.17 トレーID取得 */
		strcpy( pKenorder[*reqnum].trid,pFld[16] );
		/* No.18 トレーポジション取得 */
		pKenorder[*reqnum].trpos = atoi(pFld[17]);
		/* No.19 アッセイラックID */
		strcpy( pKenorder[*reqnum].asyrckid,pFld[18] );
		/* No.20 アッセイラックポジション */
		pKenorder[*reqnum].asyrckpos = atoi(pFld[19]);
		/* No.21 親項目コード取得 */
		strcpy( pKenorder[*reqnum].oyakmkcd,pFld[20] );
		/* No.22 セクションコード取得 */
		strcpy( pKenorder[*reqnum].seccd,pFld[21] );
		/* No.23 分画負荷区分取得 */
		pKenorder[*reqnum].bkfkkbn = pFld[22][0];
		/* No.24 サンプリングコード取得 */
		strcpy( pKenorder[*reqnum].smpcd,pFld[23] );
		/* No.26 内部項目コード取得 */
		strcpy( pKenorder[*reqnum].nbkmkcd,pFld[25] );
		/* No.27 材料コード取得 */
		strcpy( pKenorder[*reqnum].zrcd,pFld[26] );
		/* No.28 優先レベル取得 */
		strcpy( pKenorder[*reqnum].ysnlbl,pFld[27] );
		/* No.29 基準値NO取得 */
		strcpy( pKenorder[*reqnum].kjno,pFld[28] );
		/* No.30 負荷報告NO表示区分取得 */
		pKenorder[*reqnum].fkhkknohjkbn = pFld[29][0];
		/* No.31 特別基準値NO取得 */
		strcpy( pKenorder[*reqnum].tbkjno,pFld[30] );
		/* No.32 特別基準値フラグ取得 */
		pKenorder[*reqnum].tbkjflg = pFld[31][0];
		/* No.33 非定型付加時間取得 */
		strcpy( pKenorder[*reqnum].htkfkhms,pFld[32] );
		/* No.34 集検フラグ取得 */
		pKenorder[*reqnum].skflg = pFld[33][0];
		/* No.35 透折フラグ取得 */
		strcpy( pKenorder[*reqnum].tskflg,pFld[34] );
		/* No.36 凍結フラグ取得 */
		strcpy( pKenorder[*reqnum].tktflg,pFld[35] );
		/* No.37予定希釈倍率取得 */
		strcpy( pKenorder[*reqnum].ytiksbr,pFld[36] );
		/* No.38 緊急報告フラグ取得 */
		pKenorder[*reqnum].kkflg = pFld[37][0];
		/* No.39 緊急依頼フラグ取得 */
		pKenorder[*reqnum].kkiriflg = pFld[38][0];
		/* No.40 緊急依頼ロットNo取得 */
		pKenorder[*reqnum].kkirilotno = atoi(pFld[39]);
		/* No.44 性別区分取得 */
		pKenorder[*reqnum].sbtkbn = pFld[43][0];
		/* No.47 年齢取得 */
		strcpy( pKenorder[*reqnum].age,pFld[46] );
		/* No.48 年齢区分取得 */
		pKenorder[*reqnum].agekbn = pFld[47][0];
		/* No. 49 採取時間取得 */
		strcpy( pKenorder[*reqnum].sstme,pFld[48] );
		/* No. 50 採取年月日取得 */
		strcpy( pKenorder[*reqnum].ssymd,pFld[49] );
		/* No. 55 検査SEQ取得 */
		pKenorder[*reqnum].knsseq = atoi(pFld[54]);

		++(*reqnum);
	
//		free(pKenOrder);
		free(pFld);
//		memset( buff,0,sizeof(buff) );
	}
//	free( buff );
	fclose(fp);
	return RTN_OK;
}
