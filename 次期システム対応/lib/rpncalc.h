/*****************************************************************************

	SYSTEM NAME:	昭和大学病院
	FILE NAME:		計算式処理
	DATE/Var:		2018/10/15	Ver.1.00
	Edited:			T.Hanyu

*****************************************************************************/

#ifndef	_RPNCALC_H_
#define	_RPNCALC_H_

#include <ctype.h>
#include <string.h>
#include <math.h>

/*************************************************************************
	define定義
*************************************************************************/
#define RPN_BUFF_MAX		256		//	計算式の最大長
#define RPN_TOKEN_SIZE		32		//	各トークンのサイズ
#define RPN_TOKEN_MAX		100		//	トークンの最大数
#define RPN_OPSTACK_MAX		100		//	計算用スタックの最大数
#define RPN_VALSTACK_MAX	100		//	計算用スタックの最大数

#define	RPN_TYPE_ERROR		-1
#define	RPN_TYPE_VALUE		0
#define	RPN_TYPE_PLUS		1
#define	RPN_TYPE_MINUS		2
#define	RPN_TYPE_MULTI		3
#define	RPN_TYPE_DIVID		4
#define	RPN_TYPE_REMAN		5
#define	RPN_TYPE_LOG		6
#define	RPN_TYPE_EXP		7
#define	RPN_TYPE_POW		8
#define	RPN_TYPE_ROUND		9
#define	RPN_TYPE_KEKA		10

#define	RPN_OK		0
#define	RPN_NG		-1

/*************************************************************************
	テーブル定義
*************************************************************************/
typedef	struct	RpnKekkaTbl {
	int		kcode;				//	項目コード
	char	inprst[20];			//	結果
	int		point;				//	小数点桁数
} RPNKEKKATBL;

/* end of define */

/*************************************************************************
	プロトタイプ定義
*************************************************************************/
int		RpnPartSplit(char *fn,char *left,char *right);
int		RpnConv(char *fn,char *rpnfn);
int		RpnCalc(char *rpnfn,RPNKEKKATBL *pTbl,int nMaxKmsu);

#endif
