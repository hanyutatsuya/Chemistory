/*******************************************************************

	SYSTEM NAME:	ケミストリー
	FILE NAME:		パラメーターファイル読み込み
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

#include	"bml_pararead.h"				/* for  自プロセス定義		*/

/********************************************************************
	外部変数
*********************************************************************/
extern	int		errno;

/********************************************************************
	グローバル変数
*********************************************************************/

static	FILE	*ParaFp;

/********************************************************************
	プロトタイプ宣言
*********************************************************************/
int		BmlParaInit(void);
int		BmlParaOpen(char *ParaPath);
int		BmlParaClose(void);
int		BmlParaRead(char *ReadBuff);

static	int		IniBuffTrim(char *InBuff,char *OutBuff);
static	int		IniToUpper(char *inBuff,char *outBuff);

#ifdef	_TEST_
int main(int argc,char **argv)
{

	int		ret;
	char	sValue[24];

	memset(sValue,0x00,sizeof(sValue));
	if (argc < 4) {
		printf("Parameter Error\n");
		return 0;
	}

	ret = GetIniValue(argv[1],argv[2],argv[3],sValue);
	printf("[%s][%d][%s]\n",argv[1],ret,sValue);

	return 0;
}
#endif

/*---------------------------------------------------------------
fh（書式）
	int		BmlParaInit(void)
hc（関数の機能）
	関数の使用開始時の初期化
rt（戻り値）
		正常 : PARA_RET_NORMAL
		異常 : PARA_RET_NORMAL 以外
db（引数）
		無し
er（エラー時の処理）
		無し
---------------------------------------------------------------*/
int		BmlParaInit(void)
{
	ParaFp = NULL;

	return(PARA_RET_NORMAL);
}






/*---------------------------------------------------------------
fh（書式）
	int		BmlParaOpen(char *ParaPath)
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
int		BmlParaOpen(char *ParaPath)
{
	int		nRet;
	char	sPath[PARA_LENGTH_MAX];
	struct	stat	st;

	if (ParaFp != NULL) {
		return(RAPA_RET_NORMAL);
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
	int		BmlParaClose(void)
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
int		BmlParaClose(void)
{
	int		nRet;

	if (ParaFp != NULL) {
		return(RAPA_RET_NORMAL);
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
	int		BmlParaRead(char *ReadBuff)
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
int		BmlParaRead(char *ReadBuff)
{
	int		nRet;
	int		nReturn;
	int		nLen;
	int		nFlg;
	char	*pRet;
	char	sBuff[PARA_LENGTH_MAX];

	if (ParaFp != NULL) {
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
