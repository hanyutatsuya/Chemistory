/********************************************************************/
/*																	*/
/*		ＢＭＬ様向け検査システム									*/
/*																	*/
/*		システム名：次世代システム									*/
/*		ファイル名：bml_db.h										*/
/*		概要      ：データベース関連の共通関数のヘッダー・ファイル	*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*	Ver.	日付			名前			修正内容				*/
/* ----------------------------------------------------------------	*/
/*	1.00	2005/06/14		E.Osada			Create					*/
/********************************************************************/
#ifndef _bml_db_h
#define _bml_db_h

/********************************************************************/
/*	インクルード宣言												*/
/********************************************************************/
#include "bml_base.h"

#ifdef __cplusplus
extern "C"{
#endif

/********************************************************************/
/*	ｄｅｆｉｎｅ定義												*/
/********************************************************************/
#define	HCOPY_HOST(host, var) \
	bmlCopyToHostData( host, var, sizeof(host)-1 )

/********************************************************************/
/*	プロトタイプ宣言                                            */
/********************************************************************/
BOOL ZbmlStripCopy(char*, char*, SHORT);
BOOL ZbmlCopyToHostData( char* hData, char* cData, int hSize );

void ZbmlErrLogAdd(char *, int, long, char*, char *, ... );

int ZbmlErrLogReadOpen( );				
void ZbmlErrLogReadClose( );			
int ZbmlErrLogRead(char * );			
void ZbmlErrLogClear( );				

typedef struct
{
 char dummy1[5];
 char date[11];
 char dummy2[1];
 char time[8];
 char dummy3[1];
 char file_name[30];
 char dummy4[3];
 char file_position[5];
 char dummy5[3];
 char rcode[7];
 char dummy6[1];
 char state[5];
 char dummy7[30];
}	errLog_File;

#ifdef __cplusplus
}
#endif

#endif
