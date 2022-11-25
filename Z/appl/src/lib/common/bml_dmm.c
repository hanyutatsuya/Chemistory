/************************************************************************/
/*																		*/
/*		�a�l�k�l���������V�X�e��										*/
/*																		*/
/*		�V�X�e�����F������												*/
/*		�t�@�C�����Fbml_dmm.c											*/
/*		�T�v      �FDB�ƍ\���̂̃f�[�^�}�b�s���O���s��					*/
/*																		*/
/************************************************************************/

/************************************************************************/
/*	Ver.	���t			���O			�C�����e					*/
/* --------------------------------------------------------------------	*/
/*	1.00	2005/06/14		E.Osada			Create						*/
/*	@V1.1	2005/09/20		E.Osada			TIMESTAMP�Ή�				*/
/*	@V1.2	2005/11/25		E.Osada			DB2 sqlint�Ή�				*/
/************************************************************************/

/************************************************************************/
/*	�C���N���[�h�錾													*/
/************************************************************************/
#include "bml_dmm.h"
#include "bml_db.h"
#include "sqlca.h"	/* @V1.2A */
#define DMM_NOMSG

/************************************************************************/
/*	�֐���		�FZbmlMapHostToStruct()�@�@�@							*/
/*	�@�\�T�v	�FDB���b�v�ϐ��̓��e���\���̂̃f�[�^��COPY				*/
/*	����																*/
/*	 ��P����	�Fchar*      	st      �\���̂̃A�h���X     �@�@		*/
/*	 ��Q����	�FBmlDMMInfo* 	array�@ �}�b�s���O�\���̂̔z��̃A�h���X*/
/*	�o��																*/
/*	 ����FTRUE															*/
/*	 �ُ�FFALSE														*/
/************************************************************************/
BOOL ZbmlMapHostToStruct( char* st, BmlDMMInfo* array)
{
	int	i;

	if( st == NULL || array == NULL ) {
		return FALSE;
	}

	for( i=0; array[i].pchHost!=DMM_NULL; i++ ){
		BmlDMMInfo* pdm = array+i;
		char *ps = (char*)(st+pdm->lDataOffset);     // �\���̃����o�[�̃A�h���X
		char *ph = pdm->pchHost;                     // DB���b�v�ϐ��̃A�h���X
		BOOL nh = (pdm->psInd && *pdm->psInd < 0);   // NULL�\��ł���NULL�l�ł���B

		switch(pdm->shType){
		//@V1.1A
		case TYPE_TIMESTAMP:
			if (nh || strcmp(ph, DMM_NULLTIMESTAMP) == 0) {
				// NULL�l �� '1000-01-01.00.00.00.000001' �̏ꍇ
				*ps = 0;                             // NULL ������ɕϊ�����B
			} else {
				ZbmlStripCopy(ps, ph, 0);
			}
			break;
		//@V1.1E
		case TYPE_DATE:
			if (nh || strcmp(ph, DMM_NULLDATE) == 0) {
				// NULL�l �� '1000-01-01' �̏ꍇ
				*ps = 0;                             // NULL ������ɕϊ�����B
			} else {
				ZbmlStripCopy(ps, ph, 0);
			}
			break;

		case TYPE_TIME:
			if (nh || strcmp(ph, DMM_NULLTIME) == 0) {
				// NULL�l �� '00:00:01' �̏ꍇ
				*ps = 0;                             // NULL ������ɕϊ�����B
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
/*	�֐���		�FZbmlMapStructToHost()									*/
/*	�@�\�T�v	�F�\���̂̓��e��DB���b�v�ϐ��̃f�[�^��COPY				*/
/*	����																*/
/*	 ��P����   :�@ char*      	st      �\���̂̃A�h���X     �@�@		*/
/*	 ��Q����   :   BmlDMMInfo* array�@ �}�b�s���O�\���̂̔z��̃A�h���X*/
/*	�o��																*/
/*	 ����FTRUE															*/
/*	 �ُ�FFALSE														*/
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
				*pdm->psInd = 0;   // NULL �\��ł����炩�̒l�����Ă��܂��B
			}
			if (*ps == 0) {
				// NULL������� '1000-01-01-00.00.00.000001' �ɕϊ�����B 
				strcpy(ph, DMM_NULLTIMESTAMP);
			} else if (strlen(ps) < pdm->size) {
				strcpy(ph, ps);
			} else {
			}
			break;
		//@V1.1E
		case TYPE_DATE:
			if (pdm->psInd) {
				*pdm->psInd = 0;   // NULL �\��ł����炩�̒l�����Ă��܂��B
			}
			if (*ps == 0) {
				// NULL������� '1000-01-01' �ɕϊ�����B 
				strcpy(ph, DMM_NULLDATE);
			} else if (strlen(ps) < pdm->size) {
				strcpy(ph, ps);
			} else {
			}
			break;

		case TYPE_TIME:
			if (pdm->psInd) {
				*pdm->psInd = 0;   // NULL �\��ł����炩�̒l�����Ă��܂��B
			}
			if (*ps == 0){
				// NULL������� '00:00:01' �ɕϊ�����B 
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
				*pdm->psInd = 0;   // NULL �\��ł����炩�̒l�����Ă��܂��B
			}
			if (*ps == 0){
				// NULL������� ' ' �ɕϊ�����B 
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
/*	�֐���		�FZbmlDumpHostAndStruct()								*/
/*	�@�\�T�v	�F���O�E�t�@�C����DB���b�v�ϐ��ƍ\���̂̒l�������o���B	*/
/*	����																*/
/*	 ��P����	�Fchar*      	st      �\���̂̃A�h���X     �@�@		*/
/*	 ��Q����	�FbmlDMMInfo* 	array�@ �}�b�s���O�\���̂̔z��̃A�h���X*/
/*	�o��																*/
/*	 ����FTRUE															*/
/*	 �ُ�FFALSE														*/
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
