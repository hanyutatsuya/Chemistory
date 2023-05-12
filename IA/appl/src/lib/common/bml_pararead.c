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

/********************************************************************
	プロトタイプ宣言
*********************************************************************/
int		GetIniValue(char *IniPath,char *Section,char *Name,char *Value);
static	int		IniFileOpen(char *IniPath,FILE **fp);
static	int		IniFileRead(FILE **fp,char *Section,char *Name,char *Value);
static	int		IniBuffTrim(char *InBuff,char *OutBuff);
static	int		IniGetSection(char *Buff,char *Section);
static	int		IniGetName(char *Buff,char *Name,char *Value);
static	int		IniToUpper(char *inBuff,char *outBuff);
extern	int		LIB_trim();

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
	int		GetIniValue(char *IniPath,char *Section,char *Name,char *Value)
hc（関数の機能）
	iniファイルから値を取得する
rt（戻り値）
		正常 : INI_RET_NORMAL
		異常 : INI_RET_NORMAL 以外
db（引数）
		IniPath	：	iniファイルパス
					パスが絶対パスでない場合、$HOME/ini/ からの相対パスと見なす
		Section	：	セクション名(I)
		Name	：	パラメータ名(I)
		Value	：	パラメータ値(O)
er（エラー時の処理）
		無し
---------------------------------------------------------------*/
int		GetIniValue(char *IniPath,char *Section,char *Name,char *Value)
{
	int		nRet;
	char	sSection[INI_LENGTH_MAX];
	char	sName[INI_LENGTH_MAX];
	char	sValue[INI_LENGTH_MAX];
	char	sPath[INI_LENGTH_MAX];
	FILE	*fp;

	fp = NULL;
	memset(sValue,0x00,sizeof(sValue));
	strcpy(Value,sValue);
	IniToUpper(Section,sSection);
	IniToUpper(Name,sName);

	LIB_trim(sSection,sSection);
	if (sSection[0] == 0x00) {
		return(INI_RET_SECNFD);
	}

	LIB_trim(sName,sName);
	if (sName[0] == 0x00) {
		return(INI_RET_NAMENFD);
	}

	/*	相対パスチェック	*/
	if (IniPath[0] == '/') {
		strcpy(sPath,IniPath);
	} else {
		sprintf(sPath,"%s/ini/%s",(char *)getenv("HOME"),IniPath);
	}

	/* iniファイルＯＰＥＮ	*/
	nRet = IniFileOpen(sPath,&fp);
	if (nRet != INI_RET_NORMAL) {
		return(nRet);
	}

	/* iniファイルＲＥＡＤ	*/
	nRet = IniFileRead(&fp,sSection,sName,sValue);
	if (nRet != INI_RET_NORMAL) {
		fclose(fp);
		return(nRet);
	}

	fclose(fp);
	strcpy(Value,sValue);
	return(INI_RET_NORMAL);
}

/*---------------------------------------------------------------
fh（書式）
	static	int		IniFileOpen(char *IniPath,FILE *fp)
hc（関数の機能）
	iniファイルＯＰＥＮ
rt（戻り値）
		正常 : INI_RET_NORMAL
		異常 : INI_RET_NORMAL 以外
db（引数）
		IniPath	：iniファイルパス
		fp		：起iniファイルへのファイルポインタ
er（エラー時の処理）
		無し
---------------------------------------------------------------*/
static	int		IniFileOpen(char *IniPath,FILE **fp)
{
	int		nRet;
	struct	stat	st;
	
	//	ファイルの存在チェック
	nRet = stat(IniPath,&st);
	if (nRet != 0) {
		switch(errno) {
			case 0:
				break;
			case ENOENT:
				return(INI_RET_ENOENT);
				break;
			default:
				return(INI_RET_ERROR);
				break;
		}
	}

	//	ディレクトリかチェック
	if (S_ISDIR(st.st_mode) != 0) {
		return(INI_RET_EISDIR);
	}

	//	ファイルをＯＰＥＮ
    *fp = fopen(IniPath,"r");
	if (*fp == NULL) {
		switch(errno) {
			case ENOENT:
				return(INI_RET_ENOENT);
				break;
			case EACCES:
				return(INI_RET_EACCES);
				break;
			default:
				return(INI_RET_ERROR);
				break;
		}
	}

	return(INI_RET_NORMAL);
}

/*---------------------------------------------------------------
fh（書式）
	static	int		IniFileRead(FILE *fp,char *Section,char *Name,char *Value)
hc（関数の機能）
	iniファイルＲＥＡＤ
rt（戻り値）
		正常 : INI_RET_NORMAL
		異常 : INI_RET_NORMAL 以外
db（引数）
		fp		：起iniファイルへのファイルポインタ
		Section	：セクション名
		Name	：パラメータ名
		Value	：パラメータ値
er（エラー時の処理）
		無し
---------------------------------------------------------------*/
static	int		IniFileRead(FILE **fp,char *Section,char *Name,char *Value)
{
	int		nRet;
	int		nReturn;
	int		nLen;
	int		nFlg;
	int		nFlgSec;
	int		nFlgName;
	char	*pRet;
	char	sBuff[INI_LENGTH_MAX];
	char	sSection[INI_LENGTH_MAX];
	char	sName[INI_LENGTH_MAX];
	char	sValue[INI_LENGTH_MAX];

	memset(sValue,0x00,sizeof(sValue));
	Value[0] = 0x00;

	nFlg = 0;
	nFlgSec = 0;
	nFlgName = 0;
	nReturn = INI_RET_ERROR;
	for (;;) {
		//	１行ずつ読み込み
		pRet = fgets(sBuff,sizeof(sBuff),*fp);
		if (pRet == NULL) {
			//	ＥＯＦかチェック
			nRet = feof(*fp);
			if (nRet != 0) {
				break;
			} else {
				return(INI_RET_EIO);
			}
		}

		//	行末の改行コードを取る
		nRet = IniBuffTrim(sBuff,sBuff);
		if (nRet == 0) {
			continue;
		}

		//	セクション名のチェック
		nRet = IniGetSection(sBuff,sSection);
		if (nRet == INI_RET_NORMAL) {
			if (strcmp(sSection,Section) == 0) {
				nFlg = 1;
				nFlgSec = 1;
			} else {
				nFlg = 0;
			}
		} else {
			if (nFlg != 0) {
				//	パラメータ名のチェック
				nRet = IniGetName(sBuff,sName,sValue);
				if (nRet == INI_RET_NORMAL) {
					if (strcmp(sName,Name) == 0) {
						nLen = strlen(sValue);
						strncpy(Value,sValue,nLen);
						Value[nLen] = 0x00;
						nReturn = INI_RET_NORMAL;
						nFlgName = 1;
						break;
					}
				}
			}
		}
	}

	if (nFlgSec == 0) {
		nReturn = INI_RET_SECNFD;
	}
	if (nFlgName == 0) {
		nReturn = INI_RET_NAMENFD;
	}

	return(nReturn);
}

/*---------------------------------------------------------------
fh（書式）
	static	int		IniBuffTrim(char *InBuff,char *OutBuff)
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
static	int		IniBuffTrim(char *InBuff,char *OutBuff)
{
	int		nRet;
	int		nLen;
	int		nIdx;
	int		nPos;
	char	sWork[INI_LENGTH_MAX];
	char	sWork2[INI_LENGTH_MAX];

	memset(sWork,0x00,sizeof(sWork));
	memset(sWork2,0x00,sizeof(sWork2));

	strncpy(sWork,InBuff,INI_LENGTH_MAX);
	sWork[INI_LENGTH_MAX] = 0x00;

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

	//	コメント（セミコロン以降）を削除
	nLen = strlen(sWork2);
	for (nIdx=0;nIdx<nLen;nIdx++) {
		if (sWork2[nIdx] == ';') {
			sWork2[nIdx] = 0x00;
			break;
		}
	}

	//	行末のスペース、ＴＡＢ、改行コードを取る
	for (;;) {
		nLen = strlen(sWork2);
		if ((sWork2[nLen-1] == ' ') || (sWork[nLen-1] == 0x09) || (sWork2[nLen-1] == 0x0a)) {
			sWork2[nLen-1] = 0x00;
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
	static	int		IniGetSection(char *Buff,char *Section)
hc（関数の機能）
	iniファイルセクション名取得
rt（戻り値）
		正常 : INI_RET_NORMAL
		異常 : INI_RET_NORMAL 以外
db（引数）
		Buff	：読み込み文字列
		Section	：セクション名
er（エラー時の処理）
		無し
---------------------------------------------------------------*/
static	int		IniGetSection(char *Buff,char *Section)
{
	int		nLen;
	int		nIdx;
	int		nCnt1;
	int		nCnt2;
	int		nPos1;
	int		nPos2;
	char	sWork[INI_LENGTH_MAX];
	char	sSection[INI_LENGTH_MAX];

	memset(sWork,0x00,sizeof(sWork));
	memset(sSection,0x00,sizeof(sSection));

	strncpy(sWork,Buff,INI_LENGTH_MAX);
	sWork[INI_LENGTH_MAX] = 0x00;

	nLen = strlen(sWork);
	nCnt1 = 0;
	nCnt2 = 0;
	nPos1 = 0;
	nPos2 = 0;

	//	セクション検索
	for (nIdx=0;nIdx<nLen;nIdx++) {
		if (sWork[nIdx] == '[') {
			nCnt1++;
			nPos1 = nIdx;
		}
		if (sWork[nIdx] == ']') {
			nCnt2++;
			nPos2 = nIdx;
		}
	}

	if ((nCnt1 != 1) || (nCnt2 != 1) || (nPos1 >= nPos2)) {
		return(INI_RET_ERROR);
	}

	//	セクション名切り出し
	strncpy(sSection,&sWork[nPos1+1],nPos2-nPos1-1);
	sSection[nPos2-nPos1-1] = 0x00;
	IniToUpper(sSection,sSection);

	nLen = strlen(sSection);
	strncpy(Section,sSection,nLen);
	Section[nLen] = 0x00;

	return(INI_RET_NORMAL);
}

/*---------------------------------------------------------------
fh（書式）
	static	int		IniGetName(char *Buff,char *Name,char *Value)
hc（関数の機能）
	iniファイルパラメータ取得
rt（戻り値）
		正常 : INI_RET_NORMAL
		異常 : INI_RET_NORMAL 以外
db（引数）
		Buff	：読み込み文字列
		Name	：パラメータ名
		Value	：パラメータ値
er（エラー時の処理）
		無し
---------------------------------------------------------------*/
static	int		IniGetName(char *Buff,char *Name,char *Value)
{
	int		nLen;
	int		nIdx;
	int		nCnt1;
	int		nCnt2;
	int		nPos1;
	int		nPos2;
	char	sWork[INI_LENGTH_MAX];
	char	sName[INI_LENGTH_MAX];
	char	sValue[INI_LENGTH_MAX];

	memset(sWork,0x00,sizeof(sWork));
	memset(sName,0x00,sizeof(sName));
	memset(sValue,0x00,sizeof(sValue));

	strncpy(sWork,Buff,INI_LENGTH_MAX);
	sWork[INI_LENGTH_MAX] = 0x00;

	nLen = strlen(sWork);
	nCnt1 = 0;
	nPos1 = 0;
	for (nIdx=0;nIdx<nLen;nIdx++) {
		if (sWork[nIdx] == '=') {
			nCnt1++;
			if (nCnt1 == 1) {
				nPos1 = nIdx;
			}
		}
	}

//	if (nCnt1 > 1) {
//		return(INI_RET_ERROR);
//	}

	if (nCnt1 == 0) {
		strcpy(Name,sWork);
		strcpy(Value,sValue);
		return(INI_RET_NORMAL);
	}

	strncpy(sName,sWork,nPos1);
	sName[nPos1] = 0x00;
	IniToUpper(sName,sName);

	strncpy(sValue,&sWork[nPos1+1],nLen-nPos1-1);
	sValue[nLen-nPos1-1] = 0x00;
//	IniToUpper(sValue,sValue);

	nLen = strlen(sName);
	strncpy(Name,sName,nLen);
	Name[nLen] = 0x00;

	nLen = strlen(sValue);
	strncpy(Value,sValue,nLen);
	Value[nLen] = 0x00;

	return(INI_RET_NORMAL);
}

/*---------------------------------------------------------------
fh（書式）
	static	int		IniToUpper(char *inBuff,char *outBuff)
hc（関数の機能）
	文字列を大文字へ変換
rt（戻り値）
		正常 : INI_RET_NORMAL
		異常 : INI_RET_NORMAL 以外
db（引数）
		inBuff	：入力文字列
		outBuff	：出力文字列
er（エラー時の処理）
		無し
---------------------------------------------------------------*/
static	int		IniToUpper(char *inBuff,char *outBuff)
{
	int		nLoop;
	int		nLen;
	int		nChar;
	char	sInWork[INI_LENGTH_MAX];
	char	sOutWork[INI_LENGTH_MAX];

	strcpy(sInWork,inBuff);
	memset(sOutWork,0x00,sizeof(sOutWork));
//	strcpy(outBuff,sOutWork);

	nLen = strlen(sInWork);
	for (nLoop=0;nLoop<nLen;nLoop++) {
		nChar = toupper((int)sInWork[nLoop]);
		sOutWork[nLoop] = (char)nChar;
	}
	strcpy(outBuff,sOutWork);

	return(INI_RET_NORMAL);
}
