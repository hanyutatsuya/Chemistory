/*******************************************************************

	SYSTEM NAME:	ケミストリー
	FILE NAME:		オンライン処理用共通関数
	DATE/Var:		2023/05/11	Ver.1.00
	Edited:			T.Hanyu

*******************************************************************/

/*******************************************************************
	インクルードファイル
********************************************************************/
#include	<stdio.h>					/* for	標準インクル-ドファイル		*/
#include	<stdlib.h>					/* for	標準インクル-ドファイル		*/
#include	<string.h>					/* for	標準インクル-ドファイル		*/
#include	<ctype.h>					/* for	標準インクル-ドファイル		*/
#include	<sys/stat.h>				/* for 	標準インクル-ドファイル		*/
#include	<sys/types.h>				/* for 	標準インクル-ドファイル		*/
#include	<sys/errno.h>				/* for 	標準インクル-ドファイル		*/

#include	"kns_common.h"				/* for  自プロセス定義		*/

/********************************************************************
	外部変数
*********************************************************************/
extern	int		errno;

/********************************************************************
	グローバル変数
*********************************************************************/

static	FILE	*ParaFp;
static	KMKTBL	*KmkTbl;
static	int		nTblCount;

/********************************************************************
	プロトタイプ宣言
*********************************************************************/
int		KnsParaInit(char *ParaPath);
int		KnsParaFind(char *Kmkcd,char *Value);
int		KnsParaFree(void);
int		KnsLowDataCheck(Kekka *pKekka,int nKekkaNum);

static	int		KnsParaOpen(char *ParaPath);
static	int		KnsParaClose(void);
static	int		KnsParaRead(char *ReadBuff);
static	int		ParaBuffTrim(char *InBuff,char *OutBuff);
static	int		ParaToUpper(char *inBuff,char *outBuff);
static	int		ParaNumCheck(char *inBuff);
static	int		ParaDataSet(char *ReadBuff,int nIdx);

#ifdef	_TEST_
int main(int argc,char **argv)
{

	int		ret;
	char	sValue[24];

	memset(sValue,0x00,sizeof(sValue));
	if (argc < 2) {
		printf("Parameter Error\n");
		return 0;
	}

	ret = GetIniValue(argv[1],sValue);
	printf("[%s][%d][%s]\n",argv[1],ret,sValue);

	return 0;
}
#endif

/*---------------------------------------------------------------
fh（書式）
	int		KnsParaInit(char *ParaPath)
hc（関数の機能）
	関数の使用開始時の初期化
rt（戻り値）
		正常 : PARA_RET_NORMAL
		異常 : PARA_RET_NORMAL 以外
db（引数）
		ParaPath	パラメータファイルのパス
er（エラー時の処理）
		無し
---------------------------------------------------------------*/
int		KnsParaInit(char *ParaPath)
{
	int		nRet;
	int		nLoop;
	char	sBuff[PARA_LENGTH_MAX];

	ParaFp = NULL;
	KmkTbl = NULL;
	nTblCount = 0;

	nRet = KnsParaOpen(ParaPath);
	if (nRet != PARA_RET_NORMAL) {
		return(nRet);
	}

	for (;;) {
		memset(sBuff,0x00,sizeof(sBuff));
		nRet = KnsParaRead(sBuff);
		if (nRet != PARA_RET_NORMAL) {
			KnsParaClose();
			return(nRet);
		}
		if (sBuff[0] == 0x00) {
			break;
		}
		nTblCount++;
	}

	nRet = KnsParaClose();
	if (nRet != PARA_RET_NORMAL) {
		return(nRet);
	}

	KmkTbl = (KMKTBL *)malloc(sizeof(KMKTBL)*(nTblCount+1));
	if (KmkTbl == NULL) {
		return(PARA_RET_ENOMEM);
	}
	memset(KmkTbl->kmkcd,0x00,sizeof(KMKTBL)*(nTblCount+1));

	nRet = KnsParaOpen(ParaPath);
	if (nRet != PARA_RET_NORMAL) {
		return(nRet);
	}

	for (nLoop=0;nLoop<nTblCount;nLoop++) {
		memset(sBuff,0x00,sizeof(sBuff));
		nRet = KnsParaRead(sBuff);
		if (nRet != PARA_RET_NORMAL) {
			KnsParaClose();
			return(nRet);
		}
		if (sBuff[0] == 0x00) {
			break;
		}
		nRet = ParaDataSet(sBuff,nLoop);
		if (nRet != PARA_RET_NORMAL) {
			KnsParaClose();
			return(nRet);
		}
	}

	nRet = KnsParaClose();
	if (nRet != PARA_RET_NORMAL) {
		return(nRet);
	}

	return(PARA_RET_NORMAL);
}


/*---------------------------------------------------------------
fh（書式）
	int		KnsParaFind(char *Kmkcd,char *Value)
hc（関数の機能）
	メモリ領域から指定項目コードのデータを取得する
rt（戻り値）
		正常 : PARA_RET_NORMAL
		異常 : PARA_RET_NFND 	項目コード未発見
		       PARA_RET_ERROR	エラー発生
db（引数）
		Kmkcd	：検索項目コード
		Valuef	：取得データ
er（エラー時の処理）
		無し
---------------------------------------------------------------*/
int		KnsParaFind(char *Kmkcd,char *Value)
{
	int		nLoop;
	char	sValue[KMKTBL_LEN_VALUE+1];

	memset(sValue,0x00,sizeof(sValue));
	for (nLoop=0;nLoop<nTblCount;nLoop++) {
		if (strncmp((KmkTbl+nLoop)->kmkcd,Kmkcd,KMKTBL_LEN_KMKCD) == 0) {
			strncpy(sValue,(KmkTbl+nLoop)->value,KMKTBL_LEN_VALUE);
			sValue[KMKTBL_LEN_VALUE] = 0x00;
			strcpy(Value,sValue);
			break;
		}
	}

	if (sValue[0] == 0x00) {
		return(PARA_RET_NFND);
	}

	return(PARA_RET_NORMAL);
}

/*---------------------------------------------------------------
fh（書式）
	int		KnsParaFree(void)
hc（関数の機能）
	メモリ領域を開放する
rt（戻り値）
		正常 : PARA_RET_NORMAL
		異常 : PARA_RET_NORMAL 以外
db（引数）
		無し
er（エラー時の処理）
		無し
---------------------------------------------------------------*/
int		KnsParaFree(void)
{
	int		nRet;

	if (KmkTbl == NULL) {
		return(PARA_RET_NORMAL);
	}

	free(KmkTbl);

	KmkTbl = NULL;
	nTblCount = 0;

	return(PARA_RET_NORMAL);
}

/*---------------------------------------------------------------
fh（書式）
	int		KnsLowDataCheck(Kekka *pKekka,int nKekkaNum)
hc（関数の機能）
	低値再検チェック
rt（戻り値）
		正常 : PARA_RET_NORMAL
		異常 : PARA_RET_NORMAL 以外
db（引数）
		pKekka		検査結果情報へのポインタ
		nKekkaNum	検査結果情報の数
er（エラー時の処理）
		無し
---------------------------------------------------------------*/
int		KnsLowDataCheck(Kekka *pKekka,int nKekkaNum)
{
	int		nRet;
	int		nLoop;
	int		nFlg;
	char	sKmkcd[KMKTBL_LEN_KMKCD+1];
	char	sValue[KMKTBL_LEN_VALUE+1];
	char	sHjkka[KMKTBL_LEN_HJKKA+1];
	double	dHjkka;
	double	dLowData;

	nFlg = 0;
	for (nLoop=0;nLoop<nKekkaNum;nLoop++) {
		memset(sKmkcd,0x00,sizeof(sKmkcd));
		trim(sKmkcd,pKekka[nLoop].kmkcd);
		if (sKmkcd[0] == 0x00) {
			continue;
		}
		memset(sHjkka,0x00,sizeof(sHjkka));
		strncpy(sHjkka,pKekka[nLoop].hjkka,KMKTBL_LEN_HJKKA);
		sHjkka[KMKTBL_LEN_HJKKA] = 0x00;

		nRet = ParaNumCheck(sHjkka);
		if (nRet != PARA_RET_NORMAL) {
			// 数値じゃない場合は比較しない
			continue;
		}
		dHjkka = atof(sHjkka) + 0.00001;

		nRet = KnsParaFind(sKmkcd,sValue);
		if (nRet == PARA_RET_NFND) {
			//	設定値が見つからない場合はチェックしない
			continue;
		}
		if (nRet != PARA_RET_NORMAL) {
			//	その他のエラー
			return(PARA_RET_ERROR);
		}
		nRet = ParaNumCheck(sValue);
		if (nRet != PARA_RET_NORMAL) {
			// 数値じゃない場合は比較しない
			continue;
		}
		dLowData = atof(sValue) + 0.00001;
		if (dHjkka < dLowData) {
			nFlg = -1;
			break;
		}
	}

	//	設定値以下の項目があった場合
	if (nFlg != 0) {
		for (nLoop=0;nLoop<nKekkaNum;nLoop++) {
			/* 保留あつかいのフラグは変えない */
			if (pKekka[nLoop].knsflg != 'H'){
				pKekka[nLoop].knsflg = 'R';
			}
		}
	}

	return(PARA_RET_NORMAL);
}

/*---------------------------------------------------------------
fh（書式）
	static	int		KnsParaOpen(char *ParaPath)
hc（関数の機能）
	パラメータファイルをオープンする
rt（戻り値）
		正常 : PARA_RET_NORMAL
		異常 : PARA_RET_NORMAL 以外
db（引数）
	ParaPath	パラメータファイルパス
				パスが絶対パスでない場合、$HOME/ からの相対パスと見なす
er（エラー時の処理）
		無し
---------------------------------------------------------------*/
static	int		KnsParaOpen(char *ParaPath)
{
	int		nRet;
	char	sPath[PARA_LENGTH_MAX];
	struct	stat	st;

	if (ParaFp != NULL) {
		return(PARA_RET_NORMAL);
	}

	/*	相対パスチェック	*/
	if (ParaPath[0] == '/') {
		strcpy(sPath,ParaPath);
	} else {
		sprintf(sPath,"%s/%s",(char *)getenv("HOME"),ParaPath);
	}

	//	ファイルの存在チェック
	nRet = stat(sPath,&st);
	if (nRet != 0) {
		switch(errno) {
			case 0:
				break;
			case ENOENT:
				return(PARA_RET_ENOENT);
				break;
			default:
				return(PARA_RET_ERROR);
				break;
		}
	}

	//	ディレクトリかチェック
	if (S_ISDIR(st.st_mode) != 0) {
		return(PARA_RET_EISDIR);
	}

	//	ファイルをＯＰＥＮ
    ParaFp = fopen(ParaPath,"r");
	if (ParaFp == NULL) {
		switch(errno) {
			case ENOENT:
				return(PARA_RET_ENOENT);
				break;
			case EACCES:
				return(PARA_RET_EACCES);
				break;
			default:
				return(PARA_RET_ERROR);
				break;
		}
	}

	return(PARA_RET_NORMAL);
}

/*---------------------------------------------------------------
fh（書式）
	static	int		KnsParaClose(void)
hc（関数の機能）
	パラメータファイルをクローズする
	iniファイルＯＰＥＮ
rt（戻り値）
		正常 : PARA_RET_NORMAL
		異常 : PARA_RET_NORMAL 以外
db（引数）
		IniPath	：iniファイルパス
		fp		：起iniファイルへのファイルポインタ
er（エラー時の処理）
		無し
---------------------------------------------------------------*/
static	int		KnsParaClose(void)
{
	int		nRet;

	if (ParaFp != NULL) {
		return(PARA_RET_NORMAL);
	}

	nRet = fclose(ParaFp);
	if (nRet != 0) {
		ParaFp = NULL;
		return(PARA_RET_ERROR);
	}

	ParaFp = NULL;
	return(PARA_RET_NORMAL);
}


/*---------------------------------------------------------------
fh（書式）
	static	int		KnsParaRead(char *ReadBuff)
hc（関数の機能）
	iniファイルＲＥＡＤ
rt（戻り値）
		正常 : PARA_RET_NORMAL
		異常 : PARA_RET_NORMAL 以外
db（引数）
		ReadBuff：読み込みバッファー
er（エラー時の処理）
		無し
---------------------------------------------------------------*/
static	int		KnsParaRead(char *ReadBuff)
{
	int		nRet;
	int		nReturn;
	int		nLen;
	int		nFlg;
	char	*pRet;
	char	sBuff[PARA_LENGTH_MAX];

	if (ParaFp == NULL) {
		return(PARA_RET_ERROR);
	}

	nReturn = PARA_RET_ERROR;
	for (;;) {
		memset(sBuff,0x00,sizeof(sBuff));
		//	１行ずつ読み込み
		pRet = fgets(sBuff,sizeof(sBuff),ParaFp);
		if (pRet == NULL) {
			//	ＥＯＦかチェック
			nRet = feof(ParaFp);
			if (nRet != 0) {
				break;
			} else {
				return(PARA_RET_EIO);
			}
		}

		//	行末の改行コードを取る
		nRet = ParaBuffTrim(sBuff,sBuff);
		if (nRet == 0) {
			//	空白行もしくはコメント行なので継続
			continue;
		} else {
			break;
		}
	}

	strcpy(ReadBuff,sBuff);

	return(nReturn);
}

/*---------------------------------------------------------------
fh（書式）
	static	int		ParaBuffTrim(char *InBuff,char *OutBuff)
hc（関数の機能）
	行頭のスペース、ＴＡＢと行末の改行コードを取る
	コメント（セミコロン以降）を削除
rt（戻り値）
		処理後の文字列長
db（引数）
		InBUff	：入力文字列
		OutBUff	：出力文字列
er（エラー時の処理）
		無し
---------------------------------------------------------------*/
static	int		ParaBuffTrim(char *InBuff,char *OutBuff)
{
	int		nRet;
	int		nLen;
	int		nIdx;
	int		nPos;
	char	sWork[PARA_LENGTH_MAX];
	char	sWork2[PARA_LENGTH_MAX];

	memset(sWork,0x00,sizeof(sWork));
	memset(sWork2,0x00,sizeof(sWork2));

	strncpy(sWork,InBuff,PARA_LENGTH_MAX-1);
	sWork[PARA_LENGTH_MAX-1] = 0x00;

	//	行頭のスペース、ＴＡＢを取る
	nLen = strlen(sWork);
	nPos = 0;
	for (nIdx=0;nIdx<nLen;nIdx++) {
		if ((sWork[nIdx] == ' ') || (sWork[nIdx] == 0x09) || (sWork[nIdx] == 0x00)) {
			nPos = nIdx + 1;
		} else {
			break;
		}
	}
	nLen = strlen(&sWork[nPos]);
	strncpy(sWork2,&sWork[nPos],nLen);
	sWork2[nLen] = 0x00;

	//	コメント（# or ; 以降）を削除
	nLen = strlen(sWork2);
	for (nIdx=0;nIdx<nLen;nIdx++) {
		if ((sWork2[nIdx] == '#') ||
			(sWork2[nIdx] == ';')) {
			sWork2[nIdx] = 0x00;
			break;
		}
	}

	//	行末のスペース、ＴＡＢ、改行コードを取る
	for (;;) {
		nLen = strlen(sWork2);
		if (nLen > 0) {
			if ((sWork2[nLen-1] == ' ') || (sWork[nLen-1] == 0x09) || (sWork2[nLen-1] == 0x0a)) {
				sWork2[nLen-1] = 0x00;
			} else {
				break;
			}
		} else {
			break;
		}
	}

	nLen = strlen(sWork2);
	strncpy(OutBuff,sWork2,nLen);
	OutBuff[nLen] = 0x00;

	return(nLen);
}

/*---------------------------------------------------------------
fh（書式）
	static	int		ParaToUpper(char *inBuff,char *outBuff)
hc（関数の機能）
	文字列を大文字へ変換
rt（戻り値）
		正常 : PARA_RET_NORMAL
		異常 : PARA_RET_NORMAL 以外
db（引数）
		inBuff	：入力文字列
		outBuff	：出力文字列
er（エラー時の処理）
		無し
---------------------------------------------------------------*/
static	int		ParaToUpper(char *inBuff,char *outBuff)
{
	int		nLoop;
	int		nLen;
	int		nChar;
	char	sInWork[PARA_LENGTH_MAX+1];
	char	sOutWork[PARA_LENGTH_MAX+1];

	strcpy(sInWork,inBuff);
	memset(sOutWork,0x00,sizeof(sOutWork));
//	strcpy(outBuff,sOutWork);

	nLen = strlen(sInWork);
	for (nLoop=0;nLoop<nLen;nLoop++) {
		nChar = toupper((int)sInWork[nLoop]);
		sOutWork[nLoop] = (char)nChar;
	}
	strcpy(outBuff,sOutWork);

	return(PARA_RET_NORMAL);
}

/*---------------------------------------------------------------
fh（書式）
	static	int		ParaNumCheck(char *inBufff)
hc（関数の機能）
	文字列の数値チェック
	小数点は１つまでＯＫとする
rt（戻り値）
		正常 : PARA_RET_NORMAL
		異常 : PARA_RET_NORMAL 以外
db（引数）
		inBuff	：入力文字列
er（エラー時の処理）
		無し
---------------------------------------------------------------*/
static	int		ParaNumCheck(char *inBuff)
{
	int		nLoop;
	int		nLen;
	int		nPoint;
	char	sWork[PARA_LENGTH_MAX+1];

	strcpy(sWork,inBuff);

	nLen = strlen(sWork);
	nPoint = 0;
	for (nLoop=0;nLoop<nLen;nLoop++) {
		if (sWork[nLoop] == '.') {
			nPoint++;
		} else {
			if (isdigit((int)sWork[nLoop]) == 0) {
				return(PARA_RET_ERROR);
			}
		}
	}

	if (nPoint > 1) {
		return(PARA_RET_ERROR);
	}

	return(PARA_RET_NORMAL);
}

/*---------------------------------------------------------------
fh（書式）
	static	int		ParaDataSet(char *ReadBuff,int nIdx)
hc（関数の機能）
	読み込みデータをメモリ領域にセット
rt（戻り値）
		正常 : PARA_RET_NORMAL
		異常 : PARA_RET_NORMAL 以外
db（引数）
		inBuff	：入力文字列
		nIdx	：メモリ領域のインデックス
er（エラー時の処理）
		無し
---------------------------------------------------------------*/
static	int		ParaDataSet(char *ReadBuff,int nIdx)
{
	int		nLoop;
	char	sWork[PARA_LENGTH_MAX+1];
	char	*pWork;
	KMKTBL	Tbl;

	strcpy(sWork,ReadBuff);
	//	入力文字列中のTABをスペースに変換
	for (nLoop=0;;nLoop++) {
		if (sWork[nLoop] == 0x00) {
			break;
		}
		if (sWork[nLoop] == 0x09) {
			sWork[nLoop] = ' ';
		}
	}

	memset(Tbl.kmkcd,0x00,sizeof(KMKTBL));
	//	スペースを区切り文字として入力文字列を分割
	pWork = strtok(sWork," ");
	if (pWork != NULL) {
		strncpy(Tbl.kmkcd,pWork,KMKTBL_LEN_KMKCD);
		Tbl.kmkcd[KMKTBL_LEN_KMKCD] = 0x00;
		pWork = strtok(NULL," ");
		if (pWork != NULL) {
			strncpy(Tbl.value,pWork,KMKTBL_LEN_VALUE);
			Tbl.value[KMKTBL_LEN_VALUE] = 0x00;
		}
		memcpy((KmkTbl+nIdx)->kmkcd,Tbl.kmkcd,sizeof(KMKTBL));
	}

	return(PARA_RET_NORMAL);
}

