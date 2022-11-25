/********************************************************************/
/*																	*/
/*		ＢＭＬ様向け検査システム									*/
/*																	*/
/*		システム名：次世代											*/
/*		ファイル名：bml_misc.h										*/
/*		概要      ：共通関数（その他）のヘッダー・ファイル			*/
/********************************************************************/

/********************************************************************/
/*	Ver.	日付			名前			修正内容				*/
/* ----------------------------------------------------------------	*/
/*	1.00	2005/06/14		E.Osada			Create					*/
/*			2006/01/31		E.Osada			bmlStrCpy()追加			*/
/********************************************************************/
#ifndef _bml_misc_h
#define _bml_misc_h

/********************************************************************/
/*	インクルード宣言												*/
/********************************************************************/
#include "bml_base.h"

#ifdef __cplusplus
extern "C"{
#endif

/********************************************************************/
/*	プロトタイプ宣言												*/
/********************************************************************/
BOOL ZbmlSetLogFileName(char*);
BOOL ZbmlLog(char*, int, char*, ...);

void ZbmlSetHomeDirectory(char*);
char *ZbmlGetHomeDirectory(char*);
char *ZbmlMakePath(char*, char*);

char *ZbmlStrTok(char*, char*);

void ZbmlSetAppName(char*);
char *ZbmlGetAppName(char*);

BOOL ZbmlMakeSysFilePath(char*, char*);

BOOL ZbmlIsValidTime(char*);
BOOL ZbmlGetNow(char*);

void* ZbmlMalloc(size_t);
void* ZbmlCalloc(size_t, size_t);
void* ZbmlRealloc(void*, size_t);
void  ZbmlFree(void*);
char* ZbmlStrDup(char*);

BOOL ZbmlGetTodayString(char*);
BOOL ZbmlGetNowString(char*);

BOOL ZbmlStripString(char*, ULONG);

char* ZbmlZen2Han(char*, int);

void bmlStrCpy(char* pStrOut, char *pStrIn, int Num);
void ZbmlChgDBDate(char* pStrOut, char* pStrIn, int iStrSize);
void ZbmlChgAPDate(char* pStrOut, char* pStrIn);
void ZbmlChgDBTime(char* pStrOut, char* pStrIn, int iStrSize);
void ZbmlChgAPTime(char* pStrOut, char* pStrIn);
void ZbmlInfocpy(char* pStrOut, char *pStrIn, int Num);

/********************************************************************/
/*	ｄｅｆｉｎｅ定義												*/
/********************************************************************/
#define HSS_STRIP_TAIL   0x0001L
#define HSS_STRIP_HEAD   0x0002L
#define HSS_STRIP_BOTH   (HSS_STRIP_TAIL | HSS_STRIP_HEAD)
#define BMLFL __FILE__, __LINE__
#define BMLLOG(str)         ZbmlLog(BMLFL, str)
#define BMLLOG2(s1, s2)     ZbmlLog(BMLFL, s1, s2)
#define BMLLOG3(s1, s2, s3) ZbmlLog(BMLFL, s1, s2, s3)

#ifdef __cplusplus
}
#endif

#endif
/** End of File *****************************************************/
