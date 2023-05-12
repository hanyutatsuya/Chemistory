/*****************************************************************************

	SYSTEM NAME:	昭和大学病院
	FILE NAME:		iniファイル読み込み
	DATE/Var:		2017/12/07	Ver.1.00
	Edited:			T.Hanyu

*****************************************************************************/

#ifndef	_CMD_INIREAD_H_
#define	_CMD_INIREAD_H_

/*************************************************************************
	define定義
*************************************************************************/

#define		INI_RET_NORMAL		0		// リターンコード
#define		INI_RET_SECNFD		1		// リターンコード
#define		INI_RET_NAMENFD		2		// リターンコード
#define		INI_RET_ERROR		-1		// リターンコード
#define		INI_RET_ENOENT		-2		// リターンコード
#define		INI_RET_EIO			-5		// リターンコード
#define		INI_RET_EACCES		-13		// リターンコード
#define		INI_RET_EISDIR		-21		// リターンコード

#define		INI_LENGTH_MAX	128		// パラメータの最大長

/*************************************************************************
	テーブル定義
*************************************************************************/


extern	int		GetIniValue(char *IniPath,char *Section,char *Name,char *Value);

/* end of define */
#endif
