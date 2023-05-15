/*****************************************************************************

	SYSTEM NAME:	ケミストリー
	FILE NAME:		パラメーターファイル読み込み
	DATE/Var:		2023/05/11	Ver.1.00
	Edited:			T.Hanyu

*****************************************************************************/

#ifndef	_BML_PARAREAD_H_
#define	_BML_PARAREAD_H_

/*************************************************************************
	define定義
*************************************************************************/

#define		PARA_RET_NORMAL		0		// リターンコード
#define		PARA_RET_SECNFD		1		// リターンコード
#define		PARA_RET_NAMENFD		2		// リターンコード
#define		PARA_RET_ERROR		-1		// リターンコード
#define		PARA_RET_ENOENT		-2		// リターンコード
#define		PARA_RET_EIO			-5		// リターンコード
#define		PARA_RET_EACCES		-13		// リターンコード
#define		PARA_RET_EISDIR		-21		// リターンコード

#define		PARA_LENGTH_MAX	128		// パラメータの最大長

/*************************************************************************
	テーブル定義
*************************************************************************/

/*************************************************************************
	プロトタイプ定義
*************************************************************************/

extern	int		BmlParaInit(void);
extern	int		BmlParaOpen(char *ParaPath);
extern	int		BmlParaClose(void);
extern	int		BmlParaRead(char *ReadBuff);


/* end of define */
#endif
