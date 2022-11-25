/********************************************************************/
/*																	*/
/*		ＢＭＬ様向け検査システム									*/
/*																	*/
/*		システム名：次世代											*/
/*		ファイル名：bml_dmm.h										*/
/*		概要      ：DBと構造体のデータマッピングのための定義		*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*	Ver.	日付			名前			修正内容				*/
/* ----------------------------------------------------------------	*/
/*	1.00	2005/06/14		E.Osada			Create					*/
/*	@V1.1	2005/09/20		E.Osada			TIMESTAMP対応			*/
/********************************************************************/
#ifndef _bml_dmm_h
#define _bml_dmm_h

/********************************************************************/
/*	インクルード宣言												*/
/********************************************************************/
#include "bml_base.h"

/********************************************************************/
/*	ｄｅｆｉｎｅ定義												*/
/********************************************************************/
#define	DMM_NULL		0
#define	TYPE_STRING		1
#define	TYPE_SHORT		2
#define	TYPE_LONG		3
#define TYPE_CHAR       4
#define TYPE_DATE       5
#define TYPE_TIME       6
#define TYPE_TIMESTAMP  7	/* @V1.1A */


#define DMM_ENTRY(host,var,type) \
{(char*)&host, \
 (long)&((DMM_STRUCT*)0)->var, \
 (short)type, \
 sizeof(host), NULL }

#define DMM_IENTRY(host, var, type, ind) \
{(char*)&host, \
 (long)&((DMM_STRUCT*)0)->var, \
 (short)type, \
 sizeof(host), &ind }

#define DMM_STRING(host, var) DMM_ENTRY(host, var, TYPE_STRING)
#define DMM_SHORT(host, var)  DMM_ENTRY(host, var, TYPE_SHORT)
#define DMM_LONG(host, var)   DMM_ENTRY(host, var, TYPE_LONG)
#define DMM_CHAR(host, var)   DMM_ENTRY(host, var, TYPE_CHAR)

#define DMM_SCHAR(var)        DMM_CHAR(var, var)
#define DMM_SSTRING(var) DMM_STRING(var,var)
#define DMM_SSHORT(var)  DMM_SHORT(var,var)
#define DMM_SLONG(var)   DMM_LONG(var,var)
#define DMM_NULLLONG  -99999

#define DMM_ISTRING(var, ind) DMM_IENTRY(var, var, TYPE_STRING, ind)
#define DMM_ISHORT(var, ind)  DMM_IENTRY(var, var, TYPE_SHORT, ind)
#define DMM_ICHAR(var, ind)   DMM_IENTRY(var, var, TYPE_CHAR, ind)

#define DMM_NULLSTRING "\n"
#define DMM_NULLSHORT  -999 
#define DMM_NULLCHAR   '\n'

#define DMM_DATE(host, var)   DMM_ENTRY(host, var, TYPE_DATE)
#define DMM_SDATE(var)        DMM_DATE(var,var)
#define DMM_IDATE(var, ind)   DMM_IENTRY(var, var, TYPE_DATE, ind)
#define DMM_NULLDATE   "1000-01-01"

#define DMM_TIME(host, var)   DMM_ENTRY(host, var, TYPE_TIME)
#define DMM_STIME(var)        DMM_TIME(var,var)
#define DMM_ITIME(var, ind)   DMM_IENTRY(var, var, TYPE_TIME, ind)
#define DMM_NULLTIME   "00:00:01"

/* @V1.1A */
#define DMM_TIMESTAMP(host, var)   DMM_ENTRY(host, var, TYPE_TIMESTAMP)
#define DMM_STIMESTAMP(var)        DMM_TIMESTAMP(var,var)
#define DMM_ITIMESTAMP(var, ind)   DMM_IENTRY(var, var, TYPE_TIMESTAMP, ind)
#define DMM_NULLTIMESTAMP   "1000-01-01-00.00.00.000001"
/* @V1.1E */

/********************************************************************/
/*	構造体定義														*/
/********************************************************************/
typedef struct{
	char*	pchHost;
	long	lDataOffset;
	short	shType;
	unsigned int   size;
	short *psInd;
}BmlDMMInfo;

/********************************************************************/
/*	プロトタイプ宣言												*/
/********************************************************************/
BOOL ZbmlMapStructToHost( char*, BmlDMMInfo* );
BOOL ZbmlMapHostToStruct( char*, BmlDMMInfo* );

BOOL ZbmlDumpHostAndStruct( char*, BmlDMMInfo* );

#endif
/** End of File *****************************************************/
