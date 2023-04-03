#include <stdio.h>
#include <stdlib.h>
#include "rpncalc.h"

static	double	RpnValStack[RPN_VALSTACK_MAX];
static	int		RpnValIdx = 0;

static	int		RpnTokenCheck(char *token);
static	int		RpnKcodeCnv(char *sKcode,RPNKEKKATBL *pTbl,int nMaxKmsu);
static	int		RpnNumCheck(char *src);
static	int		RpnUpper(char *src);
static	int		RpnCalcMain(int nType,char *token);
static	int		RpnValStackClear(void);
static	int		RpnValStackPush(double f);
static	double	RpnValStackPop(void);
static	int		RpnKekkaSet(char *left,RPNKEKKATBL *pTbl,int nMaxKmsu);
static	double	MarumeCheck(double dInp,int nIchi);

//
//  項目計算処理
//  rpnfn    : 逆ポーランド記法の計算式
//             [nnnn] = 計算式   で登録
//             [kcode] で項目の結果を参照
//             * - * / % ^ ( ) LN EXP が使用可能
//             負の数は対応していないので (0.0 - 1.0)等とする
//  pTbl     : 計算項目のデータ
//  nMaxKmsu : pTblの項目数
//
//  戻り値   : エラー時 -1
//             正常時    0
//             計算結果はpTblの計算先項目に設定
//
int		RpnCalc(char *rpnfn,RPNKEKKATBL *pTbl,int nMaxKmsu)
{
	int		nRet;
	int		nLoop;
	int		nCount;
	int		nType;
	int		nKcode;
	char	sLeftPart[RPN_BUFF_MAX];
	char	sRightPart[RPN_BUFF_MAX];
	char	*ftoken[RPN_TOKEN_MAX];
	char	*rtoken[RPN_TOKEN_MAX];
	char	*tp;

	memset(sLeftPart,0x00,sizeof(sLeftPart));
	memset(sRightPart,0x00,sizeof(sRightPart));
	memset(ftoken,0x00,RPN_TOKEN_MAX);
	memset(rtoken,0x00,RPN_TOKEN_MAX);

	RpnValStackClear();

	nRet = RpnPartSplit(rpnfn,sLeftPart,sRightPart);
	if (nRet != RPN_OK) {
		return RPN_NG;
	}

	tp = strtok(sRightPart," ");
	nLoop = 0;
	ftoken[nLoop] = tp;
	for (nLoop=1;;nLoop++) {
		tp = strtok(NULL," ");
		if (tp == NULL) {
			break;
		}
		ftoken[nLoop] = tp;
	}
	nCount = nLoop;

	for (nLoop=0;nLoop<nCount;nLoop++) {
		nRet = RpnTokenCheck(ftoken[nLoop]);
		if (nRet == RPN_NG) {
			return RPN_NG;
		}
		nType = nRet;
		//	token を結果値に入れ替え
		if (nType == RPN_TYPE_KEKA) {
			nRet = RpnKcodeCnv(ftoken[nLoop],pTbl,nMaxKmsu);
			if (nRet != RPN_OK) {
				return RPN_NG;
			}
		}
		nRet = RpnCalcMain(nType,ftoken[nLoop]);
		if (nRet != RPN_OK) {
			return RPN_NG;
		}
	}

	nRet = RpnKekkaSet(sLeftPart,pTbl,nMaxKmsu);
	if (nRet != RPN_OK) {
		return RPN_NG;
	}

	return RPN_OK;
}

//
//	トークンのタイプをチェック
//
static	int		RpnTokenCheck(char *token)
{
	int		nRet;
	char	sWork[RPN_TOKEN_SIZE];

	strcpy(sWork,token);
	nRet = RpnNumCheck(sWork);
	if (nRet == 0) {
		if (sWork[0] == '[') {
			return RPN_TYPE_KEKA;
		}
		return RPN_TYPE_VALUE;
	}
	if (strcmp(sWork,"+") == 0) {
		return RPN_TYPE_PLUS;
	}
	if (strcmp(sWork,"-") == 0) {
		return RPN_TYPE_MINUS;
	}
	if (strcmp(sWork,"*") == 0) {
		return RPN_TYPE_MULTI;
	}
	if (strcmp(sWork,"/") == 0) {
		return RPN_TYPE_DIVID;
	}
	if (strcmp(sWork,"%") == 0) {
		return RPN_TYPE_REMAN;
	}
	if (strcmp(sWork,"^") == 0) {
		return RPN_TYPE_POW;
	}
	RpnUpper(sWork);
	if (strcmp(sWork,"LOG") == 0) {
		return RPN_TYPE_LOG;
	}
	if (strcmp(sWork,"EXP") == 0) {
		return RPN_TYPE_EXP;
	}
	if (strcmp(sWork,"POW") == 0) {
		return RPN_TYPE_POW;
	}
	if (strcmp(sWork,"ROUND") == 0) {
		return RPN_TYPE_ROUND;
	}

	return RPN_TYPE_ERROR;
}

//
//	項目コード[nnn]で指定された項目の結果を結果テーブルから取り出す
//
static	int		RpnKcodeCnv(char *sKcode,RPNKEKKATBL *pTbl,int nMaxKmsu)
{
	int		nRet;
	int		nLoop;
	int		nKcode;
	char	sWork[RPN_TOKEN_SIZE];
	char	*pt;

	strcpy(sWork,&sKcode[1]);
	pt = strchr(sWork,']');
	if (pt == NULL) {
		return RPN_NG;
	}
	nKcode = atoi(sWork);
	if (nKcode < 1) {
		return RPN_NG;
	}

	nRet = RPN_NG;
	for (nLoop=0;nLoop<nMaxKmsu;nLoop++) {
		if ((pTbl+nLoop)->kcode == nKcode) {
			strcpy(sKcode,(pTbl+nLoop)->inprst);
			nRet = RPN_OK;
			break;
		}
	}
	return(nRet);
}

//
//	文字列の数値チェック
//
static	int		RpnNumCheck(char *src)
{
	int		nLen;
	int		nLoop;
	int		nPoint;
	char	sWork[RPN_TOKEN_SIZE];

	strcpy(sWork,src);

	nLen = strlen(sWork);
	if (nLen == 0) {
		return RPN_NG;
	}

	//	項目コード指定 [nnnnn]
	if ((sWork[0] == '[') && (sWork[nLen-1] == ']') && (nLen > 2)) {
		strncpy(sWork,&sWork[1],nLen-2);
		sWork[nLen-2] = 0x00;
		nLen = strlen(sWork);
		for (nLoop=0;nLoop<nLen;nLoop++) {
			if ((sWork[nLoop] < '0') || (sWork[nLoop] > '9')) {
				return RPN_NG;
			}
		}
		return RPN_OK;
	}

	nPoint = 0;
	for (nLoop=0;nLoop<nLen;nLoop++) {
		if (sWork[nLoop] == '-') {
			//	- が先頭以外はＮＧ
			if ((nLoop > 0) || (nLen < 2)) {
				return RPN_NG;
			}
			continue;
		}

		if (sWork[nLoop] == '.') {
			//	小数点が先頭または最後はＮＧ
			if ((nLoop == 0) || (nLoop == nLen - 1)) {
				return RPN_NG;
			}
			nPoint++;
			//	小数点が２つ以上はＮＧ
			if (nPoint > 1) {
				return RPN_NG;
			}
			continue;
		}

		if ((sWork[nLoop] < '0') || (sWork[nLoop] > '9')) {
			return RPN_NG;
		}
	}

	return RPN_OK;
}

//
//	文字列を大文字に変換
//
static	int		RpnUpper(char *src)
{
	int		nLen;
	int		nLoop;
	char	sWork[RPN_TOKEN_SIZE];

	strcpy(sWork,src);
	nLen = strlen(sWork);
	if (nLen == 0) {
		return RPN_NG;
	}

	for (nLoop=0;nLoop<nLen;nLoop++) {
		sWork[nLoop] = toupper(sWork[nLoop]);
	}

	return RPN_OK;
}

//
//	トークン１つ毎に計算をする
//
static	int		RpnCalcMain(int nType,char *token)
{
	int		nRet;
	double	Val1,Val2;

	nRet = 0;
	switch (nType) {
		case RPN_TYPE_KEKA:
		case RPN_TYPE_VALUE:
			nRet = RpnValStackPush(atof(token));
			break;
		case RPN_TYPE_PLUS:
			Val2 = RpnValStackPop();
			Val1 = RpnValStackPop();
			nRet = RpnValStackPush(Val1 + Val2);
			break;
		case RPN_TYPE_MINUS:
			Val2 = RpnValStackPop();
			Val1 = RpnValStackPop();
			nRet = RpnValStackPush(Val1 - Val2);
			break;
		case RPN_TYPE_MULTI:
			Val2 = RpnValStackPop();
			Val1 = RpnValStackPop();
			nRet = RpnValStackPush(Val1 * Val2);
			break;
		case RPN_TYPE_DIVID:
			Val2 = RpnValStackPop();
			Val1 = RpnValStackPop();
			if (Val2 != 0.0) {
				nRet = RpnValStackPush(Val1 / Val2);
			} else {
//				printf("error: zero divisor\n");
				nRet = -1;
			}
			break;
		case RPN_TYPE_REMAN:
			Val2 = RpnValStackPop();
			Val1 = RpnValStackPop();
			if (Val2 != 0.0) {
				nRet = RpnValStackPush((int)Val1 % (int)Val2);
			} else {
//				printf("error: zero divisor\n");
				nRet = -1;
			}
			break;
		case RPN_TYPE_LOG:
			Val2 = RpnValStackPop();
			nRet = RpnValStackPush(log(Val2));
			break;
		case RPN_TYPE_EXP:
			Val2 = RpnValStackPop();
			nRet = RpnValStackPush(exp(Val2));
			break;
		case RPN_TYPE_POW:
			Val2 = RpnValStackPop();
			Val1 = RpnValStackPop();
			nRet = RpnValStackPush(pow(Val1,Val2));
			break;
		case RPN_TYPE_ROUND:
			Val2 = RpnValStackPop();
			Val1 = RpnValStackPop();
			nRet = RpnValStackPush(MarumeCheck(Val1,(int)Val2));
			break;
		default:
			nRet = RPN_NG;
			break;
	}

	return nRet;
}

//
//	数値スタックをクリアする
//
static	int		RpnValStackClear(void)
{
	for (RpnValIdx=0;RpnValIdx<RPN_VALSTACK_MAX;RpnValIdx++) {
		RpnValStack[RpnValIdx++] = 0.0;
	}
	RpnValIdx = 0;
	return RPN_OK;
}

//
//	数値をスタックに格納する
//
static	int		RpnValStackPush(double f)
{
	if (RpnValIdx < RPN_VALSTACK_MAX) {
		RpnValStack[RpnValIdx++] = f;
		return RPN_OK;
	} else {
		//	printf("error: stack full, can't push %g\n", f);
		return RPN_NG;
	}
}

//
//	数値をスタックがら取り出す
//
static	double	RpnValStackPop(void)
{
	if (RpnValIdx > 0) {
		return RpnValStack[--RpnValIdx];
	} else {
		//	printf("error: stack empty\n");
		return 0.0;
	}
}

//
//	計算結果（スタックの一番上）から結果に格納する
//
static	int		RpnKekkaSet(char *left,RPNKEKKATBL *pTbl,int nMaxKmsu)
{
	int		nRet;
	int		nLoop;
	int		nKcode;
	double	dKekka;
	double	dMarume;
	char	sKcode[8];
	char	sKekka[20];
	char	*pt;

	strcpy(sKcode,(left+1));
	pt = strchr(sKcode,']');
	if (pt == NULL) {
		return RPN_NG;
	}
	nKcode = atoi(sKcode);
	if (nKcode < 1) {
		return RPN_NG;
	}

	nRet = RPN_NG;
	dKekka = RpnValStackPop();
	for (nLoop=0;nLoop<nMaxKmsu;nLoop++) {
		if ((pTbl+nLoop)->kcode == nKcode) {
			dMarume = MarumeCheck(dKekka,((pTbl+nLoop)->point)+1);
			sprintf(sKekka,"%*.*f",8-(pTbl+nLoop)->point,(pTbl+nLoop)->point,dMarume);
			strcpy((pTbl+nLoop)->inprst,sKekka);
			nRet = RPN_OK;
			break;
		}
	}
	return(nRet);
}

/* ------------------------------------ */
/*	浮動小数点数丸め関数				*/
/*	nIchi は四捨五入する位置(1～11)		*/
/*										*/
/*	更新年月日：	2010.12.01			*/
/*	浮動小数点数近似値（丸め誤差）対応	*/
/*					Tatsuya Hanyu		*/
/* ------------------------------------ */
static	double	MarumeCheck(double dInp,int nIchi)
{
	int		nMinus = 0;
	int		nIdx = 0;
	int		nSeisu = 0;
	double	dWork = 0.0;
	double	dJosu = 0.0;
	double	d1keta = 0.0;
	double	dOut = 0.0;
	char	sMoji[48];
	char	*pPoint = NULL;

	memset(sMoji,0x00,sizeof(sMoji));

	/*	小数点位置が不正の場合はそのまま戻す	*/
	if ((nIchi < 1) || (nIchi > 11)) {
		return(dInp);
	}

	/*	入力値が整数部９桁を超える場合はそのまま戻す	*/
	if ((dInp < -99999999.9) || (dInp > 99999999.9)) {
		return(dInp);
	}

	/*	入力値がマイナスの場合の桁調整	*/
	if (dInp < 0.0) {
		nMinus = 2;
	} else {
		nMinus = 1;
	}

	/*	1.文字列へ変換(四捨五入位置+3桁)	*/
	/*	2.文字列を四捨五入位置の位で切り捨て*/
	/*	3.末尾に"1"を追加					*/
	/*	  double型へ戻す際に、丸め誤差により*/
	/*	  四捨五入を行う位の数字が変わらない*/
	/*	  ようにするため					*/
	/*	  (少数の最下位桁に対して近似値が	*/
	/*	  取られるため)						*/
	/*	4.double型へ戻す					*/
	sprintf(sMoji,"%.*lf",nIchi+3,dInp);
	pPoint = strchr(sMoji,'.');
	sMoji[pPoint - sMoji + nIchi + nMinus] = 0x00;
	strcat(sMoji,"1");
	dWork = atof(sMoji);

	/*	乗数作成	*/
	dJosu = 1.0;
	for (nIdx=0;nIdx<nIchi-1;nIdx++) {
		dJosu *= 10.0;
	}

	/*	1.四捨五入位置を小数点１位へ移動		*/
	/*	2.元の値が正の場合は0.5を加える			*/
	/*	  元の値が負の場合は0.5を引く			*/
	/*	3.int型へ変換して小数点以下を切り捨て	*/
	/*	4.元の桁数へ戻す						*/
	d1keta = dWork * dJosu;
	if (dInp >= 0.0) {
		d1keta += 0.5;
	} else {
		d1keta -= 0.5;
	}
	nSeisu = (int)d1keta;
	dOut   = (double)nSeisu / dJosu;

    return(dOut);
}

