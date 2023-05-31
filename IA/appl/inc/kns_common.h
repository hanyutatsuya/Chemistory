/*****************************************************************************

	SYSTEM NAME:	ケミストリー
	FILE NAME:		オンライン処理用共通関数
	DATE/Var:		2023/05/11	Ver.1.00
	Edited:			T.Hanyu

*****************************************************************************/

#ifndef	_KNS_COMMON_H_
#define	_KNS_COMMON_H_

#include	"Kekka.h"

/*************************************************************************
	define定義
*************************************************************************/

#define		PARA_RET_NORMAL		0		// リターンコード(Normal)
#define		PARA_RET_NFND		1		// リターンコード(Not Found)
#define		PARA_RET_ERROR		-1		// リターンコード
#define		PARA_RET_ENOENT		-2		// リターンコード
#define		PARA_RET_EIO		-5		// リターンコード
#define		PARA_RET_ENOMEM		-12		// リターンコード
#define		PARA_RET_EACCES		-13		// リターンコード
#define		PARA_RET_EISDIR		-21		// リターンコード

#define		PARA_LENGTH_MAX		128		// パラメータの最大長
#define		KMKTBL_LEN_KMKCD	7
#define		KMKTBL_LEN_VALUE	31
#define		KMKTBL_LEN_HJKKA	24

/*************************************************************************
	テーブル定義
*************************************************************************/

typedef	struct	kmktbl	{
	char	kmkcd[KMKTBL_LEN_KMKCD+1];
	char	value[KMKTBL_LEN_VALUE+1];
}	KMKTBL;

/*************************************************************************
	プロトタイプ定義
*************************************************************************/

extern	int		KnsParaInit(char *ParaPath);
extern	int		KnsParaFind(char *Kmkcd,char *Value);
extern	int		KnsParaFree(void);
extern	int		KnsLowDataCheck(Kekka *pKekka,int nKekkaNum);


/* end of define */
#endif
