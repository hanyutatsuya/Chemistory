/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：GetMaster.c                                                  */
/* 　概　　　要：マスタ情報取得     	                                      */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/03/06     A.Yamada       新規作成                           */
/* -------------------------------------------------------------------------- */
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  2.00     2008/09/19     K.Ameno        X-M対応初版                        */
/******************************************************************************/

/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include "GetMaster.h"

/******************************************************************************/
/*  関数宣言                                                                  */
/******************************************************************************/
int GetMaster(void);
int GetMechmst(void);
int GetCtrlmst(void);
int GetKinkyu(void);
int GetCtrlmst(void);
int GetKmkmst(void);
int GetSysknrmst(void);
int GetKnsgmst(void);
int GetKmkcd( int,char*,char* );
int GetNbkmkcd( char*,char* );
int GetTstrflg( char*,char*,char* );
int GetKnsgrp( char*,char* );
int GetSmpcd( char*,char*,char* );
int GetOyakmkcd( char*,char*,char* );
int GetSeccd( char*,char*,char* );
int GetXmcount( char*,char*,int* );
int GetYkcd( char*,char* );		/* 060418 009 */
int GetKskbrmst(void);
int GetKskRitu(Kskbrmst *key, char *sMax, char *sMin );
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 --> */
/*** X-Mレンジチェックのため追加 ***/
int GetXbarmmst(void);
int GetRngchkmst(void);
/*** X-M初期値に平均値を設定する ***/
double GetXMavg(char*, char*); 
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 <-- */
/******************************************************************************/
/*  関 数 名　：GetMaster()					     							  */
/*  機能概要　：マスタ情報取得												  */
/*  入　　力　：なし                                                          */
/*  出　　力　：                                                              */
/*  復帰情報　： RTN_OK		: 成功											  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
int GetMaster( void )
{
	char	aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetMaster()\n" );
#endif

	GetSysknrmst();
	GetMechmst();
	GetKinkyu();
	GetKmkmst();
	GetCtrlmst();
	GetKnsgmst();
	GetKskbrmst();
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 --> */
/*** X-Mレンジチェックのため追加 ***/
	GetXbarmmst();
/*** 血清レンジチェックのため追加 ***/
	GetRngchkmst();
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 <-- */
	return RTN_OK;
}
//希釈倍率マスタ追加
int GetKskbrmst( void )
{
	int		iWrk2;
	int		iCnt;
	int		iCnt2;
	char	aWrkBuf[255];
	char	buff[1024];
	FILE	*fp;
	char	** pFld;
	int		cnt;
	int		offset;
	Kskbrmst* wkMst;

	char	aFunc[32];
	char	*adrCR;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetKskbrmst()\n" );
#endif

	wkMst = NULL;
	adrCR = NULL;
	memset( aWrkBuf, 0, sizeof(aWrkBuf) );
	strcpy( aWrkBuf,aMstFolder );
	strcat( aWrkBuf,KSKBRMST_FILE_NAME );

#ifdef _DEBUG_
	printf( "ファイル名：%s\n",aWrkBuf );
#endif

	fp = fopen( aWrkBuf,"r");
	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "GetKskbrmst()", "ファイルのオープンに失敗しました。" ) ;
		printf("ファイルのオープンに失敗しました。\n");
		return RTN_NG;
	}
	iKskbrmstNum = 0;
	iWrk2 = 0;
	memset( buff,0,1024 );
	while( fgets( buff, 1024, fp ) != NULL ) {
		++iWrk2;
	}

	wkMst = malloc(sizeof(Kskbrmst)*iWrk2);
	rewind(fp); 
	iCnt = 0;
	memset( buff,0,1024 );
	while( fgets( buff, 1024, fp ) != NULL ) {
		if( iCnt >= iWrk2 ) {
			break;
		}
		/* 末尾の改行コードを削除 */
		adrCR = strchr(buff, ( int )'\r');
		if (adrCR != NULL) {
			*adrCR = '\0';
		}
		pFld = malloc(sizeof(char *)*16);
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
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 --> */
/*** 希釈倍率マスタに施設コード追加 ***/
		/* if (cnt != 10) { */
		if (cnt != 11) {
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 <-- */
			// フィールド数が一致しない
			sFncSyslog ( TRCKIND_ERROR, "GetKskbrmst()", "フィールド数が一致しませんでした。" ) ;
			printf( "フィールド数が一致しませんでした。\n" );
			free( pFld );
			break;
		}
		/* No. 1 分析機区分取得 */
		strcpy( wkMst[iCnt].bskkbn,pFld[0] );
		if( (strcmp(wkMst[iCnt].bskkbn,aMekbn) == 0)
				&& (atoi(pFld[6]) <= atoi(sSysknrmst.kjnsriymd)) ) {		/* 070/071 */
			++iKskbrmstNum;
		}
		/* No. 2 検査グループ取得 */
		strcpy( wkMst[iCnt].knsgrp,pFld[1] );
		/* No. 3 項目コード取得 */
		strcpy( wkMst[iCnt].kmkcd,pFld[2] );
		/* No. 4 希釈倍率取得 */
		strcpy( wkMst[iCnt].ksbr,pFld[3] );
		/* No. 5 希釈下限値 */
		strcpy( wkMst[iCnt].kmin, pFld[4]);
		/* No. 6 希釈上限値 */
		strcpy( wkMst[iCnt].kmax, pFld[5]);
		/* No. 7 開始年月日取得 */
		strcpy( wkMst[iCnt].kaiymd,pFld[6] );
		/* No. 8 廃止年月日取得 */
		strcpy( wkMst[iCnt].haiymd,pFld[7] );
		/* No. 9 変更担当者ID取得 */
		strcpy( wkMst[iCnt].hnktntid,pFld[8] );
		/* No. 10 情報更新日時取得 */
		strcpy( wkMst[iCnt].ksndh,pFld[9] );
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 --> */
/*** 希釈倍率マスタに施設コード追加 ***/
		/* No. 11 施設コード取得 */
		strcpy( wkMst[iCnt].sstcd,pFld[10] );
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 <-- */
		++iCnt;
		memset( buff,0,1024 );
		free( pFld );
	}

	if( iKskbrmstNum > 0 ) {
		pKskbrmst = malloc(sizeof(Kskbrmst)*iKskbrmstNum);

		iCnt2 = 0;
		for( iCnt=0; iCnt<iWrk2; iCnt++ ) {
			if( (strcmp(wkMst[iCnt].bskkbn,aMekbn) == 0)
					&& (atoi(wkMst[iCnt].kaiymd) <= atoi(sSysknrmst.kjnsriymd)) ) {	/* 070/071 */
				memcpy( &pKskbrmst[iCnt2],&wkMst[iCnt],sizeof(Kskbrmst) );
				++iCnt2;
			}
		}
	}
	free( wkMst );

	return RTN_OK;
}
int GetKskRitu(Kskbrmst *key, char *sMax, char *sMin )
{
	int	i;
#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	for( i=0; i < iKskbrmstNum ;++i ) {
		if( !memcmp((pKskbrmst+i)->bskkbn, key->bskkbn, sizeof(key->bskkbn)-1) &&
			!memcmp((pKskbrmst+i)->knsgrp, key->knsgrp, sizeof(key->knsgrp)-1) &&
			!memcmp((pKskbrmst+i)->kmkcd, key->kmkcd, sizeof(key->kmkcd)-1) ) {
			memcpy(sMax, (pKskbrmst+i)->kmax, 20);
			memcpy(sMin, (pKskbrmst+i)->kmin, 20);
			return RTN_OK;
		}
	}
	return RTN_NG;
}
/******************************************************************************/
/*  関 数 名　：GetMechmst()					  							  */
/*  機能概要　：分析機チャネルマスタ取得	     							  */
/*  入　　力　：なし                                                          */
/*  出　　力　：                                                              */
/*  復帰情報　： RTN_OK		: 成功											  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
int GetMechmst( void )
{
	int		iWrk2;
	int		iCnt;
	int		iCnt2;
	char	aWrkBuf[255];
	char	buff[100];
	FILE	*fp;
	char	** pFld;
	int		cnt;
	int		offset;
	Mechmst* wkMst;

	char	aFunc[32];
	char	*adrCR;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetMechmst()\n" );
#endif

	wkMst = NULL;
	adrCR = NULL;
	memset( aWrkBuf, 0, sizeof(aWrkBuf) );
	strcpy( aWrkBuf,aMstFolder );
	strcat( aWrkBuf,MECHMST_FILE_NAME );

#ifdef _DEBUG_
	printf( "ファイル名：%s\n",aWrkBuf );
#endif

	fp = fopen( aWrkBuf,"r");
	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "GetMechmst()", "ファイルのオープンに失敗しました。" ) ;
		printf("ファイルのオープンに失敗しました。\n");
		return RTN_NG;
	}
	iMechmstNum = 0;
	iWrk2 = 0;
	memset( buff,0,100 );
	while( fgets( buff, 100, fp ) != NULL ) {
		++iWrk2;
	}

	wkMst = malloc(sizeof(Mechmst)*iWrk2);
	rewind(fp); 
	iCnt = 0;
	memset( buff,0,100 );
	while( fgets( buff, 100, fp ) != NULL ) {
		if( iCnt >= iWrk2 ) {
			break;
		}
		/* 末尾の改行コードを削除 */
		adrCR = strchr(buff, ( int )'\r');
		if (adrCR != NULL) {
			*adrCR = '\0';
		}
		pFld = malloc(sizeof(char *)*16);
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
		if (cnt != 8) {
			/* フィールド数が一致しない */
			sFncSyslog ( TRCKIND_ERROR, "GetMechmst()", "フィールド数が一致しませんでした。" ) ;
			printf( "フィールド数が一致しませんでした。\n" );
			free( pFld );
			break;
		}
		/* No. 1 分析機区分取得 */
		strcpy( wkMst[iCnt].bskkbn,pFld[0] );
		if( (strcmp(wkMst[iCnt].bskkbn,aMekbn) == 0)
				&& (atoi(pFld[4]) <= atoi(sSysknrmst.kjnsriymd)) ) {		/* 070/071 */
			++iMechmstNum;
		}
		/* No. 2 内部項目コード取得 */
		strcpy( wkMst[iCnt].nbkmcd,pFld[1] );
		/* No. 3 チャネル名称取得 */
		strcpy( wkMst[iCnt].chnm,pFld[2] );
		/* No. 4 項目コード取得 */
		strcpy( wkMst[iCnt].kmkcd,pFld[3] );
		/* No. 5 開始年月日取得 */
		strcpy( wkMst[iCnt].kaiymd,pFld[4] );
		/* No. 6 廃止年月日取得 */
		strcpy( wkMst[iCnt].haiymd,pFld[5] );
		/* No. 7 変更担当者ID取得 */
		strcpy( wkMst[iCnt].hnktntid,pFld[6] );
		/* No. 8 情報更新日時取得 */
		strcpy( wkMst[iCnt].ksndh,pFld[7] );

		++iCnt;
		memset( buff,0,100 );
		free( pFld );
	}

	if( iMechmstNum > 0 ) {
		pMechmst = malloc(sizeof(Mechmst)*iMechmstNum);

		iCnt2 = 0;
		for( iCnt=0; iCnt<iWrk2; iCnt++ ) {
			if( (strcmp(wkMst[iCnt].bskkbn,aMekbn) == 0)
					&& (atoi(wkMst[iCnt].kaiymd) <= atoi(sSysknrmst.kjnsriymd)) ) {	/* 070/071 */
				memcpy( &pMechmst[iCnt2],&wkMst[iCnt],sizeof(Mechmst) );
				++iCnt2;
			}
		}
	}
	free( wkMst );

	return RTN_OK;
}
/******************************************************************************/
/*  関 数 名　：GetKinkyu()						  							  */
/*  機能概要　：緊急STAT用データ取得		     							  */
/*  入　　力　：なし                                                          */
/*  出　　力　：                                                              */
/*  復帰情報　： RTN_OK		: 成功											  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
int GetKinkyu( void )
{
	int		iWrk2;
	int		iCnt;
	int		iCnt2;
	char	aWrkBuf[255];
	char	buff[100];
	FILE	*fp;
	char	** pFld;
	int		cnt;
	int		offset;
	KINKYU_INF* wkTbl;

	char	aFunc[32];
	char	*adrCR;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetKinkyu()\n" );
#endif

	wkTbl = NULL;
	adrCR = NULL;
	memset( aWrkBuf, 0, sizeof(aWrkBuf) );
	strcpy( aWrkBuf,aKmkcdTblFolder );
	strcat( aWrkBuf,KINKYU_FILE_NAME );

#ifdef _DEBUG_
	printf( "ファイル名：%s\n",aWrkBuf );
#endif

	fp = fopen( aWrkBuf,"r");
	if( fp == NULL ) {
		printf("ファイルのオープンに失敗しました。\n");
		sFncSyslog ( TRCKIND_ERROR, "GetKinkyu()", "ファイルのオープンに失敗しました。" ) ;
		return RTN_NG;
	}
	iKinkyuNum = 0;
	iWrk2 = 0;
	memset( buff,0,100 );
	while( fgets( buff, 100, fp ) != NULL ) {
		++iWrk2;
	}

	wkTbl = malloc(sizeof(KINKYU_INF)*iWrk2);
	rewind(fp); 
	iCnt = 0;
	memset( buff,0,100 );
	while( fgets( buff, 100, fp ) != NULL ) {
		if( iCnt >= iWrk2 ) {
			break;
		}
		/* 末尾の改行コードを削除 */
		adrCR = strchr(buff, ( int )'\r');
		if (adrCR != NULL) {
			*adrCR = '\0';
		}
		pFld = malloc(sizeof(char *)*16);
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
		if (cnt != 4) {
			// フィールド数が一致しない
			printf( "フィールド数が一致しませんでした。\n" );
			sFncSyslog ( TRCKIND_ERROR, "GetKinkyu()", "フィールド数が一致しませんでした。" ) ;
			free( pFld );
			break;
		}
		/* No. 1 分析機区分取得 */
		strcpy( wkTbl[iCnt].bskkbn,pFld[0] );
		if( strcmp(wkTbl[iCnt].bskkbn,aMekbn) == 0 ) {
			++iKinkyuNum;
		}
		/* No. 2 検査グループ取得 */
		strcpy( wkTbl[iCnt].knsgrp,pFld[1] );
		/* No. 3 項目コード取得 */
		strcpy( wkTbl[iCnt].kmkcd,pFld[2] );
		/* No. 4 内部項目コード取得 */
		strcpy( wkTbl[iCnt].nbkmkcd,pFld[3] );

		++iCnt;
		memset( buff,0,100 );
		free( pFld );
	}

	if( iKinkyuNum > 0 ) {
		pKinkyu = malloc(sizeof(KINKYU_INF)*iKinkyuNum);

		iCnt2 = 0;
		for( iCnt=0; iCnt<iWrk2; iCnt++ ) {
			if( strcmp(wkTbl[iCnt].bskkbn,aMekbn) == 0 ) {
				memcpy( &pKinkyu[iCnt2],&wkTbl[iCnt],sizeof(KINKYU_INF) );
				++iCnt2;
			}
		}
	}
	free( wkTbl );

	return RTN_OK;
}
/******************************************************************************/
/*  関 数 名　：GetKmkmst()					  						     	  */
/*  機能概要　：項目マスタ取得	                 							  */
/*  入　　力　：なし                                                          */
/*  出　　力　：                                                              */
/*  復帰情報　： RTN_OK		: 成功											  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
int GetKmkmst( void )
{
	int		iWrk2;
	int		iCnt;
	int		iCnt2;
	char	aWrkBuf[255];
	char	buff[1024];
	FILE	*fp;
	char	** pFld;
	int		cnt;
	int		offset;
	Kmkmst* wkMst;

	char	aFunc[32];
	char	*adrCR;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetKmkmst()\n" );
#endif

	wkMst = NULL;
	adrCR = NULL;
	memset( aWrkBuf, 0, sizeof(aWrkBuf) );
	strcpy( aWrkBuf,aMstFolder );
	strcat( aWrkBuf,KMKMST_FILE_NAME );

#ifdef _DEBUG_
	printf( "ファイル名：%s\n",aWrkBuf );
#endif

	fp = fopen( aWrkBuf,"r");
	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "GetKmkmst()", "ファイルのオープンに失敗しました。" ) ;
		printf("ファイルのオープンに失敗しました。\n");
		return RTN_NG;
	}
	iKmkmstNum = 0;
	iWrk2 = 0;
	memset( buff,0,1024 );
	while( fgets( buff, 1024, fp ) != NULL ) {
		++iWrk2;									/* 070/071 */
	}

	wkMst = malloc(sizeof(Kmkmst)*iWrk2);			/* 070/071 */
	rewind(fp); 
	iCnt = 0;
	memset( buff,0,1024 );
	while( fgets( buff, 1024, fp ) != NULL ) {
		if( iCnt >= iWrk2 ) {
			break;
		}
		/* 末尾の改行コードを削除 */
		adrCR = strchr(buff, ( int )'\r');
		if (adrCR != NULL) {
			*adrCR = '\0';
		}
		pFld = malloc(sizeof(char *)*80);
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
		if (cnt != 48) {
		/* フィールド数が一致しない */
			sFncSyslog ( TRCKIND_ERROR, "GetKmkmst()", "フィールド数が一致しませんでした。" ) ;
			printf( "フィールド数が一致しませんでした。\n" );
			free( pFld );
			break;
		}
		if( atoi(pFld[44]) <= atoi(sSysknrmst.kjnsriymd) ) {	/* 070/071 */
			++iKmkmstNum;
		}
		/* No. 1 検査グループ取得 */
		strcpy( wkMst[iCnt].knsgrp,pFld[0] );
		/* No. 2 項目コード取得 */
		strcpy( wkMst[iCnt].kmkcd,pFld[1] );
		/* No. 11 サンプリングコード取得 */
		strcpy( wkMst[iCnt].smpcd,pFld[10] );
		/* No. 12 親項目コード取得 */
		strcpy( wkMst[iCnt].oyakmkcd,pFld[11] );
		/* No. 14 セクションコード取得 */
		strcpy( wkMst[iCnt].seccd,pFld[13] );
		/* No. 32 補正有無フラグ */
		wkMst[iCnt].hsiumflg = pFld[31][0];
		/* No. 37 定性・定量フラグ取得 */
		wkMst[iCnt].tstrflg = pFld[36][0];
		/* No. 40 血清情報影響フラグ 06/04/13 */
		wkMst[iCnt].ksjhflg = pFld[39][0];
		/* No. 42 X-M集計フラグ取得 */
		wkMst[iCnt].xmskflg = pFld[41][0];
		/* No. 43 X-Mチェックフラグ取得 */
		wkMst[iCnt].xmchkflg = pFld[42][0];
		/* No. 44 X-Mカウント数取得 */
		wkMst[iCnt].xmcount = atoi(pFld[43]);
		/* No. 45 開始年月日取得 */
		strcpy( wkMst[iCnt].kaiymd,pFld[44] );
		/* No. 46 廃止年月日取得 */
		strcpy( wkMst[iCnt].haiymd,pFld[45] );

		++iCnt;
		memset( buff,0,1024 );
		free( pFld );
	}

/* [ start 070/071 */
	if( iKmkmstNum > 0 ) {
		pKmkmst = malloc(sizeof(Kmkmst)*iKmkmstNum);

		iCnt2 = 0;
		for( iCnt=0; iCnt<iWrk2; iCnt++ ) {
			if( atoi(wkMst[iCnt].kaiymd) <= atoi(sSysknrmst.kjnsriymd) ) {
				memcpy( &pKmkmst[iCnt2],&wkMst[iCnt],sizeof(Kmkmst) );
				++iCnt2;
			}
		}
	}
	free( wkMst );
/* ] end 070/071 */

	return RTN_OK;
}
/******************************************************************************/
/*  関 数 名　：GetCtrlmst()				  						     	  */
/*  機能概要　：コントロールマスタ取得	           							  */
/*  入　　力　：なし                                                          */
/*  出　　力　：                                                              */
/*  復帰情報　： RTN_OK		: 成功											  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
int GetCtrlmst( void )
{
	int		iWrk2;
	int		iCnt;
	int		iCnt2;
	char	aWrkBuf[255];
	char	buff[1024];
	FILE	*fp;
	char	** pFld;
	int		cnt;
	int		offset;
	Ctrlmst* wkMst;

	char	aFunc[32];
	char	*adrCR;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetCtrlmst()\n" );
#endif

	wkMst = NULL;
	adrCR = NULL;
	memset( aWrkBuf, 0, sizeof(aWrkBuf) );
	strcpy( aWrkBuf,aMstFolder );
	strcat( aWrkBuf,CTRLMST_FILE_NAME );

#ifdef _DEBUG_
	printf( "ファイル名：%s\n",aWrkBuf );
#endif

	fp = fopen( aWrkBuf,"r");
	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "GetCtrlmst()", "ファイルのオープンに失敗しました。" ) ;
		printf("ファイルのオープンに失敗しました。\n");
		return RTN_NG;
	}
	iCtrlmstNum = 0;
	iWrk2 = 0;
	memset( buff,0,1024 );
	while( fgets( buff, 1024, fp ) != NULL ) {
		++iWrk2;
	}

	wkMst = malloc(sizeof(Ctrlmst)*iWrk2);
	rewind(fp); 
	iCnt = 0;
	memset( buff,0,1024 );
	while( fgets( buff, 1024, fp ) != NULL ) {
		if( iCnt >= iWrk2 ) {
			break;
		}
		/* 末尾の改行コードを削除 */
		adrCR = strchr(buff, ( int )'\r');
		if (adrCR != NULL) {
			*adrCR = '\0';
		}
		pFld = malloc(sizeof(char *)*50);
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
		if (cnt != 38) {
		/* フィールド数が一致しない */
			sFncSyslog ( TRCKIND_ERROR, "GetCtrlmst()", "フィールド数が一致しませんでした。" ) ;
			printf( "フィールド数が一致しませんでした。\n" );
			free( pFld );
			break;
		}
		/* No. 1 分析機区分取得 */
		strcpy( wkMst[iCnt].bskkbn,pFld[0] );
		if( (strcmp(wkMst[iCnt].bskkbn,aMekbn) == 0)
				&& (atoi(pFld[34]) <= atoi(sSysknrmst.kjnsriymd)) ) {	/* 070/071 */
			++iCtrlmstNum;
		}
		/* No. 2 内部項目コード取得 */
		strcpy( wkMst[iCnt].nbkmkcd,pFld[1] );
		/* No. 3 コントロール種別取得 */
		strcpy( wkMst[iCnt].ctrlsbt,pFld[2] );
		/* No. 6 試薬ロットNo取得 */
		strcpy( wkMst[iCnt].syklotno,pFld[5] );
		/* No. 7 コントロールレベル取得 */
		strcpy( wkMst[iCnt].ctrllbl,pFld[6] );
		/* No. 8 平均値取得 */
		strcpy( wkMst[iCnt].ctrlx,pFld[7] );
		/* No. 9 標準偏差(SD)取得 */
		strcpy( wkMst[iCnt].ctrlsd,pFld[8] );
		/* No. 35 開始年月日取得 */
		strcpy( wkMst[iCnt].kaiymd,pFld[34] );

		++iCnt;
		memset( buff,0,1024 );
		free( pFld );
	}

	if( iCtrlmstNum > 0 ) {
		pCtrlmst = malloc(sizeof(Ctrlmst)*iCtrlmstNum);

		iCnt2 = 0;
		for( iCnt=0; iCnt<iWrk2; iCnt++ ) {
			if( (strcmp(wkMst[iCnt].bskkbn,aMekbn) == 0)
					&& (atoi(wkMst[iCnt].kaiymd) <= atoi(sSysknrmst.kjnsriymd)) ) {	/* 070/071 */
				memcpy( &pCtrlmst[iCnt2],&wkMst[iCnt],sizeof(Ctrlmst) );
				++iCnt2;
			}
		}
	}
	free( wkMst );

	return RTN_OK;
}
/******************************************************************************/
/*  関 数 名　：GetSysknrmst()				  						     	  */
/*  機能概要　：システム管理マスタ取得	           							  */
/*  入　　力　：なし                                                          */
/*  出　　力　：                                                              */
/*  復帰情報　： RTN_OK		: 成功											  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
int GetSysknrmst( void )
{
	char	aWrkBuf[255];
	char	buff[1024];
	FILE	*fp;
	char	** pFld;
	int		cnt;
	int		offset;

	char	aFunc[32];
	char	*adrCR;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetSysknrmst()\n" );
#endif

	adrCR = NULL;
	memset( aWrkBuf, 0, sizeof(aWrkBuf) );
	strcpy( aWrkBuf,aMstFolder );
	strcat( aWrkBuf,SYSKNRMST_FILE_NAME );

#ifdef _DEBUG_
	printf( "ファイル名：%s\n",aWrkBuf );
#endif

	fp = fopen( aWrkBuf,"r");
	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "GetSysknrmst()", "ファイルのオープンに失敗しました。" ) ;
		printf("ファイルのオープンに失敗しました。\n");
		return RTN_NG;
	}
	memset( buff,0,1024 );
	while( fgets( buff, 1024, fp ) != NULL ) {
		/* 末尾の改行コードを削除 */
		adrCR = strchr(buff, ( int )'\r');
		if (adrCR != NULL) {
			*adrCR = '\0';
		}
		pFld = malloc(sizeof(char *)*50);
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
		if (cnt != 44) {
		/* フィールド数が一致しない */
			sFncSyslog ( TRCKIND_ERROR, "GetSysknrmst()", "フィールド数が一致しませんでした。" ) ;
			printf( "フィールド数が一致しませんでした。\n" );
			free( pFld );
			break;
		}
		/* No. 3 基準日取得 */
		strcpy( sSysknrmst.kjnsriymd,pFld[2] );
		free( pFld );

		break;
	}
	return RTN_OK;
}
/* [ start 009 060417 */
/******************************************************************************/
/*  関 数 名　：GetKnsgmst()				  						     	  */
/*  機能概要　：検査グループマスタ取得	           							  */
/*  入　　力　：なし                                                          */
/*  出　　力　：                                                              */
/*  復帰情報　： RTN_OK		: 成功											  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
int GetKnsgmst( void )
{
	int		iWrk2;
	int		iCnt;
	int		iCnt2;
	char	aWrkBuf[255];
	char	buff[1024];
	FILE	*fp;
	char	** pFld;
	int		cnt;
	int		offset;
	Knsgmst* wkMst;

	char	aFunc[32];
	char	*adrCR;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetKnsgmst()\n" );
#endif

	wkMst = NULL;
	adrCR = NULL;
	memset( aWrkBuf, 0, sizeof(aWrkBuf) );
	strcpy( aWrkBuf,aMstFolder );
	strcat( aWrkBuf,KNSGMST_FILE_NAME );

#ifdef _DEBUG_
	printf( "ファイル名：%s\n",aWrkBuf );
#endif

	fp = fopen( aWrkBuf,"r");
	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "GetKnsgmst()", "ファイルのオープンに失敗しました。" ) ;
		printf("ファイルのオープンに失敗しました。\n");
		return RTN_NG;
	}
	iKnsgmstNum = 0;
	iWrk2 = 0;
	memset( buff,0,1024 );
	while( fgets( buff, 1024, fp ) != NULL ) {
		++iWrk2;
	}

	wkMst = malloc(sizeof(Knsgmst)*iWrk2);
	rewind(fp); 
	iCnt = 0;
	memset( buff,0,1024 );
	while( fgets( buff, 1024, fp ) != NULL ) {
		if( iCnt >= iWrk2 ) {
			break;
		}
		/* 末尾の改行コードを削除 */
		adrCR = strchr(buff, ( int )'\r');
		if (adrCR != NULL) {
			*adrCR = '\0';
		}
		pFld = malloc(sizeof(char *)*80);
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
		if (cnt != 30) {
		/* フィールド数が一致しない */
			sFncSyslog ( TRCKIND_ERROR, "GetKnsgmst()", "フィールド数が一致しませんでした。" ) ;
			printf( "フィールド数が一致しませんでした。(%d,%d)\n",iCnt, cnt );
			free( pFld );
			break;
		}
		if( atoi(pFld[25]) <= atoi(sSysknrmst.kjnsriymd) ) {	/* 070/071 */
			++iKnsgmstNum;
		}
		/* No. 1 検査グループ取得 */
		strcpy( wkMst[iCnt].knsgrp,pFld[0] );
		/* No.19 容器コード取得 */
		strcpy( wkMst[iCnt].ykcd,pFld[19] );
		/* No.26 開始年月日取得 */
		strcpy( wkMst[iCnt].kaiymd,pFld[26] );

		++iCnt;
		memset( buff,0,1024 );
		free( pFld );
	}

	if( iKnsgmstNum > 0 ) {
		pKnsgmst = malloc(sizeof(Knsgmst)*iKnsgmstNum);

		iCnt2 = 0;
		for( iCnt=0; iCnt<iWrk2; iCnt++ ) {
			if( atoi(wkMst[iCnt].kaiymd) <= atoi(sSysknrmst.kjnsriymd) ) {
				memcpy( &pKnsgmst[iCnt2],&wkMst[iCnt],sizeof(Knsgmst) );
				++iCnt2;
			}
		}
	}
	free( wkMst );

	return RTN_OK;
}
/* ] end 009 060417 */
/******************************************************************************/
/*  関 数 名　：GetKmkcd()					  						     	  */
/*  機能概要　：項目コード取得	                							  */
/*  入　　力　：                                                              */
/*　 第１引数 ：int			オーダー件数                         		      */
/*　 第２引数 ：char*       内部項目コード   					 		      */
/*  出　　力　：                                                              */
/*　 第３引数 ：char*       項目コード   					 	     	      */
/*  復帰情報　： RTN_OK		: 成功(オーダーファイル)     					  */
/* 　　　　　　　2    		: 失敗(項目コードテーブル)						  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
int GetKmkcd( int reqnum,char* nbkmkcd,char* kmkcd )
{
	int	iCnt;
	int	iCnt2;
	int iLen;
	char aWrk[8];
	char aWrk2[8];
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetKmkcd()\n" );
#endif

	memset( aWrk,0,8 );
	memset( aWrk2,0,8 );
	memset( kmkcd,0,8 );
	strcat( aWrk,"       " );
	iLen = strlen( nbkmkcd );
	strncpy( aWrk,nbkmkcd,iLen );

	for( iCnt=0; iCnt<iMechmstNum; iCnt++ ) {
		if( strncmp( pMechmst[iCnt].nbkmcd,aWrk,7 ) == 0 ) {
			for( iCnt2=0; iCnt2<reqnum; iCnt2++ ) {
				if( strncmp( pKenorder[iCnt2].kmkcd,pMechmst[iCnt].kmkcd,7 ) == 0 ) {
					strncpy( kmkcd,pMechmst[iCnt].kmkcd,7 );
					return RTN_OK;
				}
			}
		}
	}
	for( iCnt=0; iCnt<iKinkyuNum; iCnt++ ) {
		if( strncmp( pKinkyu[iCnt].nbkmkcd,aWrk,7 ) == 0 ) {
			strncpy( kmkcd,pKinkyu[iCnt].kmkcd,7 );
			return 2;
		}
	}
	return RTN_NG;
}
/******************************************************************************/
/*  関 数 名　：GetNbkmkcd()					  					     	  */
/*  機能概要　：内部項目コード取得	                						  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char*       項目コード       					 		      */
/*  出　　力　：                                                              */
/*　 第２引数 ：char*       内部項目コード   					 		      */
/*  復帰情報　： RTN_OK		: 成功                       					  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
int GetNbkmkcd( char* kmkcd,char* nbkmkcd )
{
	int	iCnt;
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetNbkmkcd()\n" );
#endif

	memset( nbkmkcd,0,8 );
printf("GetNbkmkcd %d\n",iMechmstNum);
	for( iCnt=0; iCnt<iMechmstNum; iCnt++ ) {
		if( strncmp( pMechmst[iCnt].kmkcd,kmkcd,7 ) == 0 ) {
			strncpy( nbkmkcd,pMechmst[iCnt].nbkmcd,7 );
			return RTN_OK;
		}
	}
	return RTN_NG;
}
/******************************************************************************/
/*  関 数 名　：GetTstrflg()					       				     	  */
/*  機能概要　：定性・定量フラグ取得	               						  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char*       項目コード         					 		      */
/*  出　　力　：                                                              */
/*　 第２引数 ：char*       定性・定量フラグ  					 		      */
/*  復帰情報　： RTN_OK		: 成功                       					  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
int GetTstrflg( char* kmkcd,char* knsgrp,char* flg )
{
	int	iCnt;
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetTstrflg()\n" );
#endif

	memset( flg,0,32);

	for( iCnt=0; iCnt<iKmkmstNum; iCnt++ ) {

		if( (strncmp( pKmkmst[iCnt].kmkcd,kmkcd,7 ) == 0) 
			&& (strncmp(pKmkmst[iCnt].knsgrp,knsgrp,16) == 0) ) {
			flg[0] = pKmkmst[iCnt].tstrflg;
			return RTN_OK;
		}
	}
	return RTN_NG;
}
/******************************************************************************/
/*  関 数 名　：GetKnsgrp()					        				     	  */
/*  機能概要　：検査グループコード取得	               						  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char*       項目コード         					 		      */
/*  出　　力　：                                                              */
/*　 第２引数 ：char*       検査グループコード  				 		      */
/*  復帰情報　： RTN_OK		: 成功                       					  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
int GetKnsgrp( char* kmkcd,char* knsgrp )
{
	int	iCnt;
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetKnsgrp()\n" );
#endif

	memset( knsgrp,0,32 );

	for( iCnt=0; iCnt<iKmkmstNum; iCnt++ ) {
		if( strncmp( pKmkmst[iCnt].kmkcd,kmkcd,7 ) == 0 ) {
			strncpy( knsgrp,pKmkmst[iCnt].knsgrp,16 );
			return RTN_OK;
		}
	}
	return RTN_NG;
}
/******************************************************************************/
/*  関 数 名　：GetSmpcd()					        				     	  */
/*  機能概要　：サンプリングコード取得	               						  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char*       項目コード         					 		      */
/*  出　　力　：                                                              */
/*　 第２引数 ：char*       サンプリングコード					 		      */
/*  復帰情報　： RTN_OK		: 成功                       					  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
int GetSmpcd( char* kmkcd,char* knsgrp,char* smpcd )
{
	int	iCnt;
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetSmpcd()\n" );
#endif

	memset( smpcd,0,32 );

	for( iCnt=0; iCnt<iKmkmstNum; iCnt++ ) {
		if( (strncmp( pKmkmst[iCnt].kmkcd,kmkcd,7 ) == 0)
			&& (strncmp(pKmkmst[iCnt].knsgrp,knsgrp,16) == 0) ) {

			strncpy( smpcd,pKmkmst[iCnt].smpcd,7 );
			return RTN_OK;
		}
	}
	return RTN_NG;
}
/******************************************************************************/
/*  関 数 名　：GetOyakmkcd()					        	     	     	  */
/*  機能概要　：親項目コード取得	                 						  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char*       項目コード         					 		      */
/*  出　　力　：                                                              */
/*　 第２引数 ：char*       親項目コード     					 		      */
/*  復帰情報　： RTN_OK		: 成功                       					  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
int GetOyakmkcd( char* kmkcd,char* knsgrp,char* oyakmkcd )
{
	int	iCnt;
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetOyakmkcd()\n" );
#endif

	memset( oyakmkcd,0,32 );

	for( iCnt=0; iCnt<iKmkmstNum; iCnt++ ) {
		if( (strncmp( pKmkmst[iCnt].kmkcd,kmkcd,7 ) == 0)
			&& (strncmp(pKmkmst[iCnt].knsgrp,knsgrp,16) == 0) ) {
			strncpy( oyakmkcd,pKmkmst[iCnt].oyakmkcd,7 );
			return RTN_OK;
		}
	}
	return RTN_NG;
}
/******************************************************************************/
/*  関 数 名　：GetSeccd()			     		        	     	     	  */
/*  機能概要　：セクションコード取得	              						  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char*       項目コード         					 		      */
/*  出　　力　：                                                              */
/*　 第２引数 ：char*       セクションコード  					 		      */
/*  復帰情報　： RTN_OK		: 成功                       					  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
int GetSeccd( char* kmkcd,char* knsgrp,char* seccd )
{
	int	iCnt;
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetSeccd()\n" );
#endif

	memset( seccd,0,32 );

	for( iCnt=0; iCnt<iKmkmstNum; iCnt++ ) {
		if( (strncmp( pKmkmst[iCnt].kmkcd,kmkcd,7 ) == 0)
			&& (strncmp(pKmkmst[iCnt].knsgrp,knsgrp,16) == 0) ) {
			strncpy( seccd,pKmkmst[iCnt].seccd,2 );
			return RTN_OK;
		}
	}
	return RTN_NG;
}
/******************************************************************************/
/*  関 数 名　：GetXmcount()		     		        	     	     	  */
/*  機能概要　：X-Mカウント取得	                    						  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char*       検査グループコード 					 		      */
/*　 第２引数 ：char*       項目コード         					 		      */
/*  出　　力　：                                                              */
/*　 第３引数 ：int*        X-Mカウント      					 		      */
/*  復帰情報　： RTN_OK		: 成功                       					  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
int GetXmcount( char* kmkcd,char* knsgrp,int* xmcount )
{
	int	iCnt;
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "%sGetXmcount()\n", Now() );
#endif

	for( iCnt=0; iCnt<iKmkmstNum; iCnt++ ) {
		if( (strncmp( pKmkmst[iCnt].kmkcd,kmkcd,7 ) == 0)
			&& (strncmp(pKmkmst[iCnt].knsgrp,knsgrp,16) == 0) ) {
			*xmcount = (int)pKmkmst[iCnt].xmcount;
#ifdef _DEBUG_
            printf( "GetXmcount OK!\n");
            printf( "X-Mカウント:%d\n", *xmcount);
#endif
			return RTN_OK;
		}
	}
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 --> */
/*** X-Mカウントが取得できなかった場合に、*xmcountの値が不定となる ***/
    *xmcount = -1;
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 <-- */
#ifdef _DEBUG_
            printf( "GetXmcount NG!\n");
#endif
	return RTN_NG;
}
/* [ start 060418 009 */
/******************************************************************************/
/*  関 数 名　：GetYkcd()					        				     	  */
/*  機能概要　：容器種別取得			               						  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char*       検査グループコード 					 		      */
/*  出　　力　：                                                              */
/*　 第２引数 ：char*       容器コード 		 			     	 		      */
/*  復帰情報　： RTN_OK		: 成功                       					  */
/* 　　　　　　　RTN_NG		: 失敗											  */
/******************************************************************************/
int GetYkcd( char* knsgrp,char* ykcd )
{
	int	iCnt;
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetYkcd()\n" );
#endif

	for( iCnt=0; iCnt<iKnsgmstNum; iCnt++ ) {
		if( strncmp( pKnsgmst[iCnt].knsgrp,knsgrp,16 ) == 0 ) {
			strncpy( ykcd,pKnsgmst[iCnt].ykcd,4 );
			return RTN_OK;
		}
	}
	return RTN_NG;
}
/* ] end 060418 009 */

/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 --> */
/*** X-Mレンジチェックのため追加 ***/
/******************************************************************************/
/*  関 数 名　：GetXbarmmst()                                                 */
/*  機能概要　：X-Mマスタ取得                                                 */
/*  入　　力　：なし                                                          */
/*  出　　力　：                                                              */
/*  復帰情報　： RTN_OK     : 成功                                            */
/* 　　　　　　　RTN_NG     : 失敗                                            */
/******************************************************************************/
int GetXbarmmst( void )
{
	int		iWrk2;
	int		iCnt;
	int		iCnt2;
	char	aWrkBuf[255];
	char	buff[200];
	FILE	*fp;
	char	** pFld;
	int		cnt;
	int		offset;
	Xbarmmst* wkMst;

	char	aFunc[32];
	char	*adrCR;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetXbarmmst()\n" );
#endif

	wkMst = NULL;
	adrCR = NULL;
	memset( aWrkBuf, 0, sizeof(aWrkBuf) );
	strcpy( aWrkBuf,aMstFolder );
	strcat( aWrkBuf,XBARMMST_FILE_NAME );

#ifdef _DEBUG_
	printf( "ファイル名：%s\n",aWrkBuf );
#endif

	fp = fopen( aWrkBuf,"r");
	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "GetXbarmmst()", "ファイルのオープンに失敗しました。" ) ;
		printf("ファイルのオープンに失敗しました。\n");
		return RTN_NG;
	}
	iXbarmmstNum = 0;
	iWrk2 = 0;
	memset( buff,0,200 );
	while( fgets( buff, 200, fp ) != NULL ) {
		++iWrk2;
	}

	wkMst = malloc(sizeof(Xbarmmst)*iWrk2);
	rewind(fp); 
	iCnt = 0;
	memset( buff,0,200 );
	while( fgets( buff, 200, fp ) != NULL ) {
		if( iCnt >= iWrk2 ) {
			break;
		}
		/* 末尾の改行コードを削除 */
		adrCR = strchr(buff, ( int )'\r');
		if (adrCR != NULL) {
			*adrCR = '\0';
		}
		pFld = malloc(sizeof(char *)*16);
		if (pFld == NULL) {
			sFncSyslog ( TRCKIND_ERROR, "GetXbarmmst()", "作業エリアの確保に失敗しました。" ) ;
			printf( "作業エリアの確保に失敗しました。\n" );
			break;
		}

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
		if (cnt != 11) {
		/* フィールド数が一致しない */
			sFncSyslog ( TRCKIND_ERROR, "GetXbarmmst()", "フィールド数が一致しませんでした。" ) ;
			printf( "フィールド数が一致しませんでした。\n" );
			free( pFld );
			break;
		}
		if((atoi(pFld[7]) <= atoi(sSysknrmst.kjnsriymd)) &&
		   (atoi(pFld[8]) >= atoi(sSysknrmst.kjnsriymd))) {
			strcpy(wkMst[iCnt].knsgrp,   pFld[ 0]);	/* No.  1 検査グループ		*/
			strcpy(wkMst[iCnt].kmkcd,    pFld[ 1]);	/* No.  2 項目コード取得	*/
			strcpy(wkMst[iCnt].minval,   pFld[ 2]);	/* No.  3 下限 下限値		*/
			strcpy(wkMst[iCnt].minart,   pFld[ 3]);	/* No.  4 警告上限			*/
			strcpy(wkMst[iCnt].avgval,   pFld[ 4]);	/* No.  5 平均値			*/
			strcpy(wkMst[iCnt].maxart,   pFld[ 5]);	/* No.  6 警告上限			*/
			strcpy(wkMst[iCnt].maxval,   pFld[ 6]);	/* No.  7 上限 上限値		*/
			strcpy(wkMst[iCnt].kaiymd,   pFld[ 7]);	/* No.  8 開始年月日		*/
			strcpy(wkMst[iCnt].haiymd,   pFld[ 8]);	/* No.  9 廃止年月日		*/
			strcpy(wkMst[iCnt].hnktntid, pFld[ 9]);	/* No. 10 変更担当者ＩＤ	*/
			strcpy(wkMst[iCnt].ksndh,    pFld[10]);	/* No. 11 情報更新日時		*/

			++iXbarmmstNum;
			++iCnt;
		}

		memset( buff,0,200 );
		free( pFld );
	}

	if( iXbarmmstNum > 0 ) {
		pXbarmmst = malloc(sizeof(Xbarmmst)*iXbarmmstNum);

		for( iCnt=0; iCnt<iXbarmmstNum; iCnt++ ) {
			memcpy( &pXbarmmst[iCnt],&wkMst[iCnt],sizeof(Xbarmmst) );
			++iCnt2;
		}
	}
	free( wkMst );

	return RTN_OK;
}

/*** 血清レンジチェックのため追加 ***/
/******************************************************************************/
/*  関 数 名　：GetRngchkmst()                                                */
/*  機能概要　：レンジチェックマスタ取得(血清のみ必要なので範囲区分5のみ対象) */
/*  入　　力　：なし                                                          */
/*  出　　力　：                                                              */
/*  復帰情報　： RTN_OK     : 成功                                            */
/* 　　　　　　　RTN_NG     : 失敗                                            */
/******************************************************************************/
int GetRngchkmst( void )
{
	int		iWrk2;
	int		iCnt;
	int		iCnt2;
	char	aWrkBuf[255];
	char	buff[200];
	FILE	*fp;
	char	** pFld;
	int		cnt;
	int		offset;
	Rngchkmst* wkMst;

	char	aFunc[32];
	char	*adrCR;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetRngchkmst()\n" );
#endif

	wkMst = NULL;
	adrCR = NULL;
	memset( aWrkBuf, 0, sizeof(aWrkBuf) );
	strcpy( aWrkBuf,aMstFolder );
	strcat( aWrkBuf,RNGCHKMST_FILE_NAME );

#ifdef _DEBUG_
	printf( "ファイル名：%s\n",aWrkBuf );
#endif

	fp = fopen( aWrkBuf,"r");
	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "GetRngchkmst()", "ファイルのオープンに失敗しました。" ) ;
		printf("ファイルのオープンに失敗しました。\n");
		return RTN_NG;
	}
	iRngchkmstNum = 0;
	iWrk2 = 0;
	memset( buff,0,200 );
	while( fgets( buff, 200, fp ) != NULL ) {
		++iWrk2;
	}

	wkMst = malloc(sizeof(Rngchkmst)*iWrk2);
	rewind(fp); 
	iCnt = 0;
	memset( buff,0,200 );
	while( fgets( buff, 200, fp ) != NULL ) {
		if( iCnt >= iWrk2 ) {
			break;
		}
		/* 末尾の改行コードを削除 */
		adrCR = strchr(buff, ( int )'\r');
		if (adrCR != NULL) {
			*adrCR = '\0';
		}
		pFld = malloc(sizeof(char *)*16);
		if (pFld == NULL) {
			sFncSyslog ( TRCKIND_ERROR, "GetRngchkmst()", "作業エリアの確保に失敗しました。" ) ;
			printf( "作業エリアの確保に失敗しました。\n" );
			break;
		}

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
		if (cnt != 14) {
			/* フィールド数が一致しない */
			sFncSyslog ( TRCKIND_ERROR, "GetRngchkmst()", "フィールド数が一致しませんでした。" ) ;
			printf( "フィールド数が一致しませんでした。\n" );
			free( pFld );
			break;
		}
		if((atoi(pFld[10]) <= atoi(sSysknrmst.kjnsriymd)) &&
		   (atoi(pFld[11]) >= atoi(sSysknrmst.kjnsriymd)) &&
		    pFld[0][0] == '5') {
			wkMst[iCnt].hnikbn     = pFld[ 0][0];		/* No.  1 範囲区分			*/
			strcpy(wkMst[iCnt].knsgrp,     pFld[ 1]);	/* No.  2 検査グループ		*/
			strcpy(wkMst[iCnt].kmkcd,      pFld[ 2]);	/* No.  3 項目コード		*/
			strcpy(wkMst[iCnt].zaicd,      pFld[ 3]);	/* No.  4 材料コード		*/
			strcpy(wkMst[iCnt].sstcd,      pFld[ 4]);	/* No.  5 施設コード		*/
			wkMst[iCnt].sbt        = pFld[ 5][0];		/* No.  6 性別				*/
			wkMst[iCnt].ssa        = pFld[ 6][0];		/* No.  7 上下限区分		*/
			wkMst[iCnt].zen_kyoyou = pFld[ 7][0];		/* No.  8 許容区分			*/
			strcpy(wkMst[iCnt].hrng,       pFld[ 8]);	/* No.  9 レンジ上限		*/
			strcpy(wkMst[iCnt].lrng,       pFld[ 9]);	/* No. 10 レンジ下限		*/
			strcpy(wkMst[iCnt].kaiymd,     pFld[10]);	/* No. 11 開始年月日		*/
			strcpy(wkMst[iCnt].haiymd,     pFld[11]);	/* No. 12 廃止年月日		*/
			strcpy(wkMst[iCnt].hnktntid,   pFld[12]);	/* No. 13 変更担当者ＩＤ	*/
			strcpy(wkMst[iCnt].ksndh,      pFld[13]);	/* No. 14 情報更新日時		*/

			++iRngchkmstNum;
			++iCnt;
		}

		memset( buff,0,200 );
		free( pFld );
	}

	if( iRngchkmstNum > 0 ) {
		pRngchkmst = malloc(sizeof(Rngchkmst)*iRngchkmstNum);

		for( iCnt=0; iCnt<iRngchkmstNum; iCnt++ ) {
			memcpy( &pRngchkmst[iCnt],&wkMst[iCnt],sizeof(Rngchkmst) );
			++iCnt2;
		}
	}
	free( wkMst );

	return RTN_OK;
}

/*** X-M初期値に平均値を設定する ***/
double GetXMavg(char* knsgrp, char* kmkcd)
{
	double ret = 0;
	int    i;

	for (i = 0; i < iXbarmmstNum; i++) {
		if ((memcmp(pXbarmmst[i].knsgrp, knsgrp, 16) == 0) &&
			(memcmp(pXbarmmst[i].kmkcd,  kmkcd,   7) == 0)) {
            ret = atof(pXbarmmst[i].avgval);
			break;
        }
    }

	return ret;
}
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 <-- */
