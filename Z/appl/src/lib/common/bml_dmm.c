/************************************************************************/
/*																		*/
/*		ＢＭＬ様向け検査システム										*/
/*																		*/
/*		システム名：次世代												*/
/*		ファイル名：bml_dmm.c											*/
/*		概要      ：DBと構造体のデータマッピングを行う					*/
/*																		*/
/************************************************************************/

/************************************************************************/
/*	Ver.	日付			名前			修正内容					*/
/* --------------------------------------------------------------------	*/
/*	1.00	2005/06/14		E.Osada			Create						*/
/*	@V1.1	2005/09/20		E.Osada			TIMESTAMP対応				*/
/*	@V1.2	2005/11/25		E.Osada			DB2 sqlint対応				*/
/************************************************************************/

/************************************************************************/
/*	インクルード宣言													*/
/************************************************************************/
#include "bml_dmm.h"
#include "bml_db.h"
#include "sqlca.h"	/* @V1.2A */
#define DMM_NOMSG

/************************************************************************/
/*	関数名		：ZbmlMapHostToStruct()　　　							*/
/*	機能概要	：DBラップ変数の内容を構造体のデータにCOPY				*/
/*	入力																*/
/*	 第１引数	：char*      	st      構造体のアドレス     　　		*/
/*	 第２引数	：BmlDMMInfo* 	array　 マッピング構造体の配列のアドレス*/
/*	出力																*/
/*	 正常：TRUE															*/
/*	 異常：FALSE														*/
/************************************************************************/
BOOL ZbmlMapHostToStruct( char* st, BmlDMMInfo* array)
{
	int	i;

	if( st == NULL || array == NULL ) {
		return FALSE;
	}

	for( i=0; array[i].pchHost!=DMM_NULL; i++ ){
		BmlDMMInfo* pdm = array+i;
		char *ps = (char*)(st+pdm->lDataOffset);     // 構造体メンバーのアドレス
		char *ph = pdm->pchHost;                     // DBラップ変数のアドレス
		BOOL nh = (pdm->psInd && *pdm->psInd < 0);   // NULL可能列でかつNULL値である。

		switch(pdm->shType){
		//@V1.1A
		case TYPE_TIMESTAMP:
			if (nh || strcmp(ph, DMM_NULLTIMESTAMP) == 0) {
				// NULL値 か '1000-01-01.00.00.00.000001' の場合
				*ps = 0;                             // NULL 文字列に変換する。
			} else {
				ZbmlStripCopy(ps, ph, 0);
			}
			break;
		//@V1.1E
		case TYPE_DATE:
			if (nh || strcmp(ph, DMM_NULLDATE) == 0) {
				// NULL値 か '1000-01-01' の場合
				*ps = 0;                             // NULL 文字列に変換する。
			} else {
				ZbmlStripCopy(ps, ph, 0);
			}
			break;

		case TYPE_TIME:
			if (nh || strcmp(ph, DMM_NULLTIME) == 0) {
				// NULL値 か '00:00:01' の場合
				*ps = 0;                             // NULL 文字列に変換する。
			} else {
				ZbmlStripCopy(ps, ph, 0);
			}
			break;

		case TYPE_STRING: 
			if ( strlen(pdm->pchHost) <= pdm->size ){
				if (nh) {
					strcpy(ps, DMM_NULLSTRING);
				} else {
/*
					ZbmlStripCopy(ps, ph, 0);
*/
					strcpy(ps, ph);
				}
			}else{
				return FALSE;
			}
			break;
		case TYPE_LONG:
			/* @V1.2C
			*(long*)ps = (nh) ? DMM_NULLLONG : *(long*)ph;
			*/
			*(sqlint32*)ps = (nh) ? DMM_NULLLONG : *(sqlint32*)ph;
			/* @V1.2E */
			break;
		case TYPE_SHORT:
			*(short*)ps = (nh) ? DMM_NULLSHORT : *(short*)ph;
			break;
		case TYPE_CHAR:
			*ps = (nh) ? DMM_NULLCHAR : *ph;
			break;
		default:
			break;
	  }
	}
	return TRUE;
}

/************************************************************************/
/*	関数名		：ZbmlMapStructToHost()									*/
/*	機能概要	：構造体の内容をDBラップ変数のデータにCOPY				*/
/*	入力																*/
/*	 第１引数   :　 char*      	st      構造体のアドレス     　　		*/
/*	 第２引数   :   BmlDMMInfo* array　 マッピング構造体の配列のアドレス*/
/*	出力																*/
/*	 正常：TRUE															*/
/*	 異常：FALSE														*/
/************************************************************************/
BOOL ZbmlMapStructToHost( char* st, BmlDMMInfo* array)
{
	int	i;

	if( st == NULL || array == NULL ) {
		return FALSE;
	}
	for( i=0; array[i].pchHost!=DMM_NULL; i++ ){
		BmlDMMInfo* pdm = array+i;
		char *ps = (char*)(st+pdm->lDataOffset);
		char *ph = pdm->pchHost;

		switch(pdm->shType){
		//@V1.1A
		case TYPE_TIMESTAMP:
			if (pdm->psInd)	{
				*pdm->psInd = 0;   // NULL 可能列でも何らかの値を入れてしまう。
			}
			if (*ps == 0) {
				// NULL文字列を '1000-01-01-00.00.00.000001' に変換する。 
				strcpy(ph, DMM_NULLTIMESTAMP);
			} else if (strlen(ps) < pdm->size) {
				strcpy(ph, ps);
			} else {
			}
			break;
		//@V1.1E
		case TYPE_DATE:
			if (pdm->psInd) {
				*pdm->psInd = 0;   // NULL 可能列でも何らかの値を入れてしまう。
			}
			if (*ps == 0) {
				// NULL文字列を '1000-01-01' に変換する。 
				strcpy(ph, DMM_NULLDATE);
			} else if (strlen(ps) < pdm->size) {
				strcpy(ph, ps);
			} else {
			}
			break;

		case TYPE_TIME:
			if (pdm->psInd) {
				*pdm->psInd = 0;   // NULL 可能列でも何らかの値を入れてしまう。
			}
			if (*ps == 0){
				// NULL文字列を '00:00:01' に変換する。 
				strcpy(ph, DMM_NULLTIME);
			} else if (strlen(ps) < pdm->size) {
				strcpy(ph, ps);
			}else{
			}
			break;

		case TYPE_STRING: 
/* 2006.04.05 CHG OSADA
			if ( pdm->psInd && strcmp(ps, DMM_NULLSTRING) == 0){
				*ph = 0;
				*pdm->psInd = -1;
			}
			else if ( strlen(ps) < pdm->size ){
				strcpy( ph, ps );
				if (pdm->psInd) {
					*pdm->psInd = 0;
				}
			}else{
				return FALSE;
			}
*/
			if ( pdm->psInd ) {
				*pdm->psInd = 0;   // NULL 可能列でも何らかの値を入れてしまう。
			}
			if (*ps == 0){
				// NULL文字列を ' ' に変換する。 
				memset(ph, ' ', pdm->size - 1);
			} else if (strlen(ps) < pdm->size) {
				strcpy(ph, ps);
			}else{
			}
			break;

		case TYPE_LONG:
			/* @V1.2C
			if (pdm->psInd && *(long*)ps == DMM_NULLLONG){
				*ph = 0;
				*pdm->psInd = -1;
			}
			else{
				*(long*)ph = *(long*)ps;
				if (pdm->psInd)
					*pdm->psInd = 0;
			} */
			if (pdm->psInd && *(sqlint32*)ps == DMM_NULLLONG){
				*ph = 0;
				*pdm->psInd = -1;
			}
			else{
				*(sqlint32*)ph = *(sqlint32*)ps;
				if (pdm->psInd) {
					*pdm->psInd = 0;
				}
			}
			/* @V1.2E */
			break;
		case TYPE_SHORT:
			if (pdm->psInd && *(short*)ps == DMM_NULLSHORT){
				*ph = 0;
				*pdm->psInd = -1;
			}
			else{
				*(short*)ph = *(short*)ps;
				if (pdm->psInd) {
					*pdm->psInd = 0;
				}
			}
			break;
			
		case TYPE_CHAR:
/* 2006.04.05 CHG OSADA
			if (pdm->psInd && *ps == DMM_NULLCHAR){
				*ph = 0;
				*pdm->psInd = -1;
			}
			if{
				*ph = *ps;
				if (pdm->psInd) {
					*pdm->psInd = 0;
				}
			}
*/
			if( pdm->psInd ) {
				*ph = 0;
			}
			if( *ps == 0 ) {
				*ph = ' ';
			} else {
				*ph = *ps;
				if (pdm->psInd) {
					*pdm->psInd = 0;
				}
			}
			break;
		default:
			break;
	  }
	}
	return TRUE;
}

/************************************************************************/
/*	関数名		：ZbmlDumpHostAndStruct()								*/
/*	機能概要	：ログ・ファイルにDBラップ変数と構造体の値を書き出す。	*/
/*	入力																*/
/*	 第１引数	：char*      	st      構造体のアドレス     　　		*/
/*	 第２引数	：bmlDMMInfo* 	array　 マッピング構造体の配列のアドレス*/
/*	出力																*/
/*	 正常：TRUE															*/
/*	 異常：FALSE														*/
/************************************************************************/
BOOL ZbmlDumpHostAndStruct(char *st, BmlDMMInfo *array)
{
	int i;
	FILE *fp;
	char *logfile = "\\bmldmm.log";
	char *null = "(NULL)";

	if (NULL == st || NULL == array) {
		return FALSE;
	}

	if (NULL == (fp = fopen(logfile, "a"))){
		return FALSE;
	}

	fprintf(fp, "begin ---------\n");

	for( i=0; array[i].pchHost!=DMM_NULL; i++ ){
		BmlDMMInfo* pdm = array+i;
		char *ps = (char*)(st+pdm->lDataOffset);
		char *ph = pdm->pchHost;
		char *ns = "";
		char *nh = (pdm->psInd && *pdm->psInd < 0) ? null : "";

		fprintf(fp, "#%02d:", i);

		switch(pdm->shType){
		case TYPE_STRING:
			if (strcmp(ps, DMM_NULLSTRING) == 0)
				ns = null;
			fprintf(fp, "STRING H[%s]%s S[%s]%s\n", ph, nh, ps, ns);
			break;
		case TYPE_SHORT:
			if (*(short*)ps == DMM_NULLSHORT)
				ns = null;
			fprintf(fp, "SHORT  H=%d%s S=%d%s\n", *(short*)ph, nh, *(short*)ps, ns);
			break;
		case TYPE_CHAR:
			if (*ps == DMM_NULLCHAR)
				ns = null;
			fprintf(fp, "CHAR   H[%c](%d)%s S[%c](%d)%s\n", *ph, *ph, nh, *ps, *ps, ns);
			break;
		default:
			fprintf(fp, "INVALID type=%d\n", pdm->shType);
			break;
		}
	}

	fprintf(fp, "end ---------\n");

	return TRUE;
}
/** End of File *********************************************************/
