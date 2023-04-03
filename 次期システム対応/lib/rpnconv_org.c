#include <stdio.h>
#include <stdlib.h>
#include "rpncalc.h"

static	char	*RpnOpStack[RPN_OPSTACK_MAX];
static	int		RpnOpIdx = 0;

static	int		RpnTokenSplit(char *fn,char *token);
static	int		RpnConvert(char *token[], int length,char *buffer[]);
static	int		RpnOpStackClear(void);
static	int		RpnOpStackPush(char *pToken);
static	char	*RpnOpStackPop(void);
static	char	*RpnOpStackPeek(void);
static	int		RpnOpRank(char *op);

//
//  計算式の右辺と左辺を分割
//
int		RpnPartSplit(char *fn,char *left,char *right)
{
	int		nLoop;
	char	sShiki[RPN_BUFF_MAX];
	char	*pt;

	memset(sShiki,0x00,sizeof(sShiki));
	RpnOpStackClear();

	strcpy(sShiki,fn);
	strcpy(left,"");
	strcpy(right,"");

	pt = strchr(sShiki,'=');
	if (pt == NULL) {
		return RPN_NG;
	}
	*pt = 0x00;
	if (*(pt-1) == ' ') {
		*(pt-1) = 0x00;
	}
	strcpy(left,sShiki);

	for (;;) {
		if (*(pt+1) == ' ') {
			pt++;
		} else {
			break;
		}
	}
	strcpy(right,(pt+1));

	return RPN_OK;
}

//
//  計算式処理
//      計算式を逆ポーランド記法へ変換
//          [nnnn] = 計算式   で登録
//          [kcode] で項目の結果を参照
//          * - * / % ^ ( ) LN EXP が使用可能
//          負の数は対応していないので (0.0 - 1.0)等とする
//
//  戻り値   : エラー時 -1
//             正常時    0
//
int		RpnConv(char *fn,char *rpnfn)
{
	int		nRet;
	int		nLoop;
	char	sLeftPart[RPN_BUFF_MAX];
	char	sRightPart[RPN_BUFF_MAX];
	char	sRpnBuff[RPN_BUFF_MAX*2];
	char	*ftoken[RPN_TOKEN_MAX];
	char	*tp;
	char	*rtoken[RPN_TOKEN_MAX];

	strcpy(rpnfn,"");
	memset(sLeftPart,0x00,sizeof(sLeftPart));
	memset(sRightPart,0x00,sizeof(sRightPart));
	memset(sRpnBuff,0x00,sizeof(sRpnBuff));
	memset(ftoken,0x00,RPN_TOKEN_MAX);
	memset(rtoken,0x00,RPN_TOKEN_MAX);

	nRet = RpnTokenSplit(fn,sRpnBuff);
	if (nRet != RPN_OK) {
		return RPN_NG;
	}

	nRet = RpnPartSplit(sRpnBuff,sLeftPart,sRightPart);
	if (nRet != RPN_OK) {
		return RPN_NG;
	}

	tp = strtok(sRightPart," ");
	nLoop = 0;
	ftoken[nLoop] = tp;
	for (nLoop=1;;nLoop++) {
		if (nLoop > RPN_TOKEN_MAX) {
			return RPN_NG;
		}
		tp = strtok(NULL," ");
		if (tp == NULL) {
			break;
		}
		ftoken[nLoop] = tp;
	}

	nRet = RpnConvert(ftoken,nLoop,rtoken);
	if (nRet != RPN_OK) {
		return RPN_NG;
	}

	strcpy(rpnfn,sLeftPart);
	strcat(rpnfn," = ");

	for (nLoop=0;rtoken[nLoop] != NULL;nLoop++) {
		strcat(rpnfn,rtoken[nLoop]);
		strcat(rpnfn," ");
	}

	return RPN_OK;
}

//
//	計算式のトークン毎に空白を入れる
//
static	int		RpnTokenSplit(char *fn,char *token)
{
	int		nLoop;
	int		nLen;
	int		nCount;
	char	sShiki[RPN_BUFF_MAX*2];
	char	sRpnBuff[RPN_BUFF_MAX*2];

	enum	OpeType	{
		Initial,
		Number,
		Ope,
		Equal,
		Other };
	enum	OpeType	Cur;
	enum	OpeType	Pre;

	memset(sShiki,0x00,sizeof(sShiki));
	memset(sRpnBuff,0x00,sizeof(sRpnBuff));
	strcpy(token,sRpnBuff);

	strcpy(sShiki,fn);
	nLen = strlen(sShiki);
	nCount=0;
	Cur = Initial;
	Pre = Initial;
	for (nLoop=0;nLoop<nLen;nLoop++) {
		if (sShiki[nLoop] == ' ') {
			continue;
		}
		Pre = Cur;
		switch (sShiki[nLoop]) {
			case '=':
				Cur = Equal;
				break;
			case '(': case ')':
			case '+': case '-': case '*': case '/': case '%':
			case '^': case 'E': case 'e': case 'L': case 'l':
				Cur = Ope;
				break;
			case 'N': case 'O': case 'G': case 'X': case 'P': 
			case 'n': case 'o': case 'g': case 'x': case 'p': 
				Cur = Other;
				break;
			case '[': case ']': case '.': 
			case '0': case '1': case '2': case '3': case '4': 
			case '5': case '6': case '7': case '8': case '9': 
				Cur = Number;
				break;
			default:
				Cur = Other;
				break;
		}
		switch(Pre) {
			case Number:
				if ((Cur == Equal) ||
					(Cur == Ope)) {
					sRpnBuff[nCount] = ' ';
					nCount++;
				}
				break;
			case Equal:
				if ((Cur == Number) ||
					(Cur == Ope)) {
					sRpnBuff[nCount] = ' ';
					nCount++;
				}
				break;
			case Ope:
				if ((Cur == Equal) ||
					(Cur == Number) ||
					(Cur == Ope)) {
					sRpnBuff[nCount] = ' ';
					nCount++;
				}
				break;
			case Other:
				if ((Cur == Equal) ||
					(Cur == Number) ||
					(Cur == Ope)) {
					sRpnBuff[nCount] = ' ';
					nCount++;
				}
				break;
			default:
				break;
		}

		sRpnBuff[nCount] = sShiki[nLoop];
		nCount++;

	}
	sRpnBuff[nCount] = 0x00;
	strcpy(token,sRpnBuff);
	return RPN_OK;
}

//
//	計算式のトークンから逆ポーランド記法へ変換
//
static	int		RpnConvert(char *token[], int length,char *buffer[])
{
	int		n;
	int		nRet;
	char	*pToken;

	// 並び替えたトークンを格納するバッファ。
	// 括弧"(", ")" は除くため、元の式に括弧があればその分長さは短くなる。
//	char	**buffer = calloc(length+1, sizeof(char*));
	int		nBuf = 0;

	nRet = 0;
	for (n = 0; n < length; n++) {
		if (isdigit(*token[n])) {
			// 数値ならば、バッファに追加
			buffer[nBuf++] = token[n];
			continue;
		}
		if ((*token[n] == '-') && isdigit(*(token[n]+1))) {
			// マイナス数値ならば、バッファに追加
			buffer[nBuf++] = token[n];
			continue;
		}
		if (*token[n] == '[') {
			// '['ならば、バッファに追加
			buffer[nBuf++] = token[n];
			continue;
		}
		if (*token[n] == ')') {
			// '('までスタックからポップし、バッファへ. '(' と ')' は捨てる.
			for (;;) {
				pToken = RpnOpStackPop();
				if ((pToken == NULL) || (*pToken == '(')) {
					break;
				}
				buffer[nBuf++] = pToken;
			}
			if (pToken == NULL) {
				// '(' がない
				return RPN_NG;
			}
			continue;
		}
		if (*token[n] == '(') {
			nRet = RpnOpStackPush(token[n]);
			if (nRet != RPN_OK) {
				return RPN_NG;
			}
			continue;
		}
		if (RpnOpStackPeek() == NULL) {
			nRet = RpnOpStackPush(token[n]);
			if (nRet != RPN_OK) {
				return RPN_NG;
			}
			continue;
		}
		while (RpnOpStackPeek() != NULL) {
			if (RpnOpRank(token[n]) > RpnOpRank(RpnOpStackPeek())) {
				// 現在のトークンはスタック最上位のトークンより優先順位が低い
				buffer[nBuf++] = RpnOpStackPop();
			} else {
				nRet = RpnOpStackPush(token[n]);
				if (nRet != RPN_OK) {
					return RPN_NG;
				}
				break;
			}
		}
	}

	// スタックが空になるまでトークンを取り出し、バッファへ
	while ((pToken = RpnOpStackPop()) != NULL) {
		buffer[nBuf++] = pToken;
	}
	buffer[nBuf++] = NULL;

	return RPN_OK;
}
//
//	演算子のスタックをクリア
//
static	int		RpnOpStackClear(void)
{
	for (RpnOpIdx=0;RpnOpIdx < RPN_OPSTACK_MAX;RpnOpIdx++) {
		RpnOpStack[RpnOpIdx++] = 0x00;
	}
	RpnOpIdx = 0;
	return RPN_OK;
}

//
//	演算子をスタックへ格納
//
static	int		RpnOpStackPush(char *pToken)
{
	if (RpnOpIdx >= RPN_OPSTACK_MAX)
		return RPN_NG;

	RpnOpStack[RpnOpIdx++] = pToken;
	return RPN_OK;
}

//
//	演算子をスタックから取り出す
//
static	char	*RpnOpStackPop(void)
{
	if (RpnOpIdx > 0) {
		return RpnOpStack[--RpnOpIdx];
	} else {
		return (char *)NULL;
	}
}

//
//	演算子のスタックを確認
//
static	char	*RpnOpStackPeek(void)
{
	if (RpnOpIdx > 0) {
		return RpnOpStack[RpnOpIdx-1];
	} else {
		return NULL;
	}
}

//
// 演算子の優先順位を返す
//
static	int		RpnOpRank(char *op)
{
	if ((*op == 'E') ||
		(*op == 'e') ||
		(*op == 'L') ||
		(*op == 'l')) {
		return 3;
	}
	if ((*op == '*') ||
		(*op == '/') ||
		(*op == '%') ||
		(*op == '^')) {
		return 4;
	}

	if ((*op == '+') ||
		(*op == '-')) {
		return 5;
	}

	return 99;
}

