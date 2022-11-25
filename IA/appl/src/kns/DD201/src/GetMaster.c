/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FGetMaster.c                                                  */
/* �@�T�@�@�@�v�F�}�X�^���擾     	                                      */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/03/06     A.Yamada       �V�K�쐬                           */
/* -------------------------------------------------------------------------- */
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  2.00     2008/09/19     K.Ameno        X-M�Ή�����                        */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include "GetMaster.h"

/******************************************************************************/
/*  �֐��錾                                                                  */
/******************************************************************************/
int GetMaster(void);
int GetMechmst(void);
int GetCtrlmst(void);
int GetKinkyu(void);
int GetCtrlmst(void);
int GetKmkmst(void);
int GetSysknrmst(void);
int GetKnsgmst(void);
int GetKmkcd( int,char*,char* );
int GetNbkmkcd( char*,char* );
int GetTstrflg( char*,char*,char* );
int GetKnsgrp( char*,char* );
int GetSmpcd( char*,char*,char* );
int GetOyakmkcd( char*,char*,char* );
int GetSeccd( char*,char*,char* );
int GetXmcount( char*,char*,int* );
int GetYkcd( char*,char* );		/* 060418 009 */
int GetKskbrmst(void);
int GetKskRitu(Kskbrmst *key, char *sMax, char *sMin );
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** X-M�����W�`�F�b�N�̂��ߒǉ� ***/
int GetXbarmmst(void);
int GetRngchkmst(void);
/*** X-M�����l�ɕ��ϒl��ݒ肷�� ***/
double GetXMavg(char*, char*); 
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
/******************************************************************************/
/*  �� �� ���@�FGetMaster()					     							  */
/*  �@�\�T�v�@�F�}�X�^���擾												  */
/*  ���@�@�́@�F�Ȃ�                                                          */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F RTN_OK		: ����											  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
int GetMaster( void )
{
	char	aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetMaster()\n" );
#endif

	GetSysknrmst();
	GetMechmst();
	GetKinkyu();
	GetKmkmst();
	GetCtrlmst();
	GetKnsgmst();
	GetKskbrmst();
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** X-M�����W�`�F�b�N�̂��ߒǉ� ***/
	GetXbarmmst();
/*** ���������W�`�F�b�N�̂��ߒǉ� ***/
	GetRngchkmst();
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
	return RTN_OK;
}
//��ߔ{���}�X�^�ǉ�
int GetKskbrmst( void )
{
	int		iWrk2;
	int		iCnt;
	int		iCnt2;
	char	aWrkBuf[255];
	char	buff[1024];
	FILE	*fp;
	char	** pFld;
	int		cnt;
	int		offset;
	Kskbrmst* wkMst;

	char	aFunc[32];
	char	*adrCR;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetKskbrmst()\n" );
#endif

	wkMst = NULL;
	adrCR = NULL;
	memset( aWrkBuf, 0, sizeof(aWrkBuf) );
	strcpy( aWrkBuf,aMstFolder );
	strcat( aWrkBuf,KSKBRMST_FILE_NAME );

#ifdef _DEBUG_
	printf( "�t�@�C�����F%s\n",aWrkBuf );
#endif

	fp = fopen( aWrkBuf,"r");
	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "GetKskbrmst()", "�t�@�C���̃I�[�v���Ɏ��s���܂����B" ) ;
		printf("�t�@�C���̃I�[�v���Ɏ��s���܂����B\n");
		return RTN_NG;
	}
	iKskbrmstNum = 0;
	iWrk2 = 0;
	memset( buff,0,1024 );
	while( fgets( buff, 1024, fp ) != NULL ) {
		++iWrk2;
	}

	wkMst = malloc(sizeof(Kskbrmst)*iWrk2);
	rewind(fp); 
	iCnt = 0;
	memset( buff,0,1024 );
	while( fgets( buff, 1024, fp ) != NULL ) {
		if( iCnt >= iWrk2 ) {
			break;
		}
		/* �����̉��s�R�[�h���폜 */
		adrCR = strchr(buff, ( int )'\r');
		if (adrCR != NULL) {
			*adrCR = '\0';
		}
		pFld = malloc(sizeof(char *)*16);
		cnt = 0;
		offset = 0;;
		pFld[cnt] = &buff[cnt];
		cnt++;
		while (buff[offset] != '\0') {
			if (buff[offset] == ',') {
				pFld[cnt++] = &buff[offset+1];
				buff[offset] = '\0';
			}
			offset++;
		}
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** ��ߔ{���}�X�^�Ɏ{�݃R�[�h�ǉ� ***/
		/* if (cnt != 10) { */
		if (cnt != 11) {
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
			// �t�B�[���h������v���Ȃ�
			sFncSyslog ( TRCKIND_ERROR, "GetKskbrmst()", "�t�B�[���h������v���܂���ł����B" ) ;
			printf( "�t�B�[���h������v���܂���ł����B\n" );
			free( pFld );
			break;
		}
		/* No. 1 ���͋@�敪�擾 */
		strcpy( wkMst[iCnt].bskkbn,pFld[0] );
		if( (strcmp(wkMst[iCnt].bskkbn,aMekbn) == 0)
				&& (atoi(pFld[6]) <= atoi(sSysknrmst.kjnsriymd)) ) {		/* 070/071 */
			++iKskbrmstNum;
		}
		/* No. 2 �����O���[�v�擾 */
		strcpy( wkMst[iCnt].knsgrp,pFld[1] );
		/* No. 3 ���ڃR�[�h�擾 */
		strcpy( wkMst[iCnt].kmkcd,pFld[2] );
		/* No. 4 ��ߔ{���擾 */
		strcpy( wkMst[iCnt].ksbr,pFld[3] );
		/* No. 5 ��߉����l */
		strcpy( wkMst[iCnt].kmin, pFld[4]);
		/* No. 6 ��ߏ���l */
		strcpy( wkMst[iCnt].kmax, pFld[5]);
		/* No. 7 �J�n�N�����擾 */
		strcpy( wkMst[iCnt].kaiymd,pFld[6] );
		/* No. 8 �p�~�N�����擾 */
		strcpy( wkMst[iCnt].haiymd,pFld[7] );
		/* No. 9 �ύX�S����ID�擾 */
		strcpy( wkMst[iCnt].hnktntid,pFld[8] );
		/* No. 10 ���X�V�����擾 */
		strcpy( wkMst[iCnt].ksndh,pFld[9] );
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** ��ߔ{���}�X�^�Ɏ{�݃R�[�h�ǉ� ***/
		/* No. 11 �{�݃R�[�h�擾 */
		strcpy( wkMst[iCnt].sstcd,pFld[10] );
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
		++iCnt;
		memset( buff,0,1024 );
		free( pFld );
	}

	if( iKskbrmstNum > 0 ) {
		pKskbrmst = malloc(sizeof(Kskbrmst)*iKskbrmstNum);

		iCnt2 = 0;
		for( iCnt=0; iCnt<iWrk2; iCnt++ ) {
			if( (strcmp(wkMst[iCnt].bskkbn,aMekbn) == 0)
					&& (atoi(wkMst[iCnt].kaiymd) <= atoi(sSysknrmst.kjnsriymd)) ) {	/* 070/071 */
				memcpy( &pKskbrmst[iCnt2],&wkMst[iCnt],sizeof(Kskbrmst) );
				++iCnt2;
			}
		}
	}
	free( wkMst );

	return RTN_OK;
}
int GetKskRitu(Kskbrmst *key, char *sMax, char *sMin )
{
	int	i;
#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	for( i=0; i < iKskbrmstNum ;++i ) {
		if( !memcmp((pKskbrmst+i)->bskkbn, key->bskkbn, sizeof(key->bskkbn)-1) &&
			!memcmp((pKskbrmst+i)->knsgrp, key->knsgrp, sizeof(key->knsgrp)-1) &&
			!memcmp((pKskbrmst+i)->kmkcd, key->kmkcd, sizeof(key->kmkcd)-1) ) {
			memcpy(sMax, (pKskbrmst+i)->kmax, 20);
			memcpy(sMin, (pKskbrmst+i)->kmin, 20);
			return RTN_OK;
		}
	}
	return RTN_NG;
}
/******************************************************************************/
/*  �� �� ���@�FGetMechmst()					  							  */
/*  �@�\�T�v�@�F���͋@�`���l���}�X�^�擾	     							  */
/*  ���@�@�́@�F�Ȃ�                                                          */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F RTN_OK		: ����											  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
int GetMechmst( void )
{
	int		iWrk2;
	int		iCnt;
	int		iCnt2;
	char	aWrkBuf[255];
	char	buff[100];
	FILE	*fp;
	char	** pFld;
	int		cnt;
	int		offset;
	Mechmst* wkMst;

	char	aFunc[32];
	char	*adrCR;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetMechmst()\n" );
#endif

	wkMst = NULL;
	adrCR = NULL;
	memset( aWrkBuf, 0, sizeof(aWrkBuf) );
	strcpy( aWrkBuf,aMstFolder );
	strcat( aWrkBuf,MECHMST_FILE_NAME );

#ifdef _DEBUG_
	printf( "�t�@�C�����F%s\n",aWrkBuf );
#endif

	fp = fopen( aWrkBuf,"r");
	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "GetMechmst()", "�t�@�C���̃I�[�v���Ɏ��s���܂����B" ) ;
		printf("�t�@�C���̃I�[�v���Ɏ��s���܂����B\n");
		return RTN_NG;
	}
	iMechmstNum = 0;
	iWrk2 = 0;
	memset( buff,0,100 );
	while( fgets( buff, 100, fp ) != NULL ) {
		++iWrk2;
	}

	wkMst = malloc(sizeof(Mechmst)*iWrk2);
	rewind(fp); 
	iCnt = 0;
	memset( buff,0,100 );
	while( fgets( buff, 100, fp ) != NULL ) {
		if( iCnt >= iWrk2 ) {
			break;
		}
		/* �����̉��s�R�[�h���폜 */
		adrCR = strchr(buff, ( int )'\r');
		if (adrCR != NULL) {
			*adrCR = '\0';
		}
		pFld = malloc(sizeof(char *)*16);
		cnt = 0;
		offset = 0;;
		pFld[cnt] = &buff[cnt];
		cnt++;
		while (buff[offset] != '\0') {
			if (buff[offset] == ',') {
				pFld[cnt++] = &buff[offset+1];
				buff[offset] = '\0';
			}
			offset++;
		}
		if (cnt != 8) {
			/* �t�B�[���h������v���Ȃ� */
			sFncSyslog ( TRCKIND_ERROR, "GetMechmst()", "�t�B�[���h������v���܂���ł����B" ) ;
			printf( "�t�B�[���h������v���܂���ł����B\n" );
			free( pFld );
			break;
		}
		/* No. 1 ���͋@�敪�擾 */
		strcpy( wkMst[iCnt].bskkbn,pFld[0] );
		if( (strcmp(wkMst[iCnt].bskkbn,aMekbn) == 0)
				&& (atoi(pFld[4]) <= atoi(sSysknrmst.kjnsriymd)) ) {		/* 070/071 */
			++iMechmstNum;
		}
		/* No. 2 �������ڃR�[�h�擾 */
		strcpy( wkMst[iCnt].nbkmcd,pFld[1] );
		/* No. 3 �`���l�����̎擾 */
		strcpy( wkMst[iCnt].chnm,pFld[2] );
		/* No. 4 ���ڃR�[�h�擾 */
		strcpy( wkMst[iCnt].kmkcd,pFld[3] );
		/* No. 5 �J�n�N�����擾 */
		strcpy( wkMst[iCnt].kaiymd,pFld[4] );
		/* No. 6 �p�~�N�����擾 */
		strcpy( wkMst[iCnt].haiymd,pFld[5] );
		/* No. 7 �ύX�S����ID�擾 */
		strcpy( wkMst[iCnt].hnktntid,pFld[6] );
		/* No. 8 ���X�V�����擾 */
		strcpy( wkMst[iCnt].ksndh,pFld[7] );

		++iCnt;
		memset( buff,0,100 );
		free( pFld );
	}

	if( iMechmstNum > 0 ) {
		pMechmst = malloc(sizeof(Mechmst)*iMechmstNum);

		iCnt2 = 0;
		for( iCnt=0; iCnt<iWrk2; iCnt++ ) {
			if( (strcmp(wkMst[iCnt].bskkbn,aMekbn) == 0)
					&& (atoi(wkMst[iCnt].kaiymd) <= atoi(sSysknrmst.kjnsriymd)) ) {	/* 070/071 */
				memcpy( &pMechmst[iCnt2],&wkMst[iCnt],sizeof(Mechmst) );
				++iCnt2;
			}
		}
	}
	free( wkMst );

	return RTN_OK;
}
/******************************************************************************/
/*  �� �� ���@�FGetKinkyu()						  							  */
/*  �@�\�T�v�@�F�ً}STAT�p�f�[�^�擾		     							  */
/*  ���@�@�́@�F�Ȃ�                                                          */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F RTN_OK		: ����											  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
int GetKinkyu( void )
{
	int		iWrk2;
	int		iCnt;
	int		iCnt2;
	char	aWrkBuf[255];
	char	buff[100];
	FILE	*fp;
	char	** pFld;
	int		cnt;
	int		offset;
	KINKYU_INF* wkTbl;

	char	aFunc[32];
	char	*adrCR;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetKinkyu()\n" );
#endif

	wkTbl = NULL;
	adrCR = NULL;
	memset( aWrkBuf, 0, sizeof(aWrkBuf) );
	strcpy( aWrkBuf,aKmkcdTblFolder );
	strcat( aWrkBuf,KINKYU_FILE_NAME );

#ifdef _DEBUG_
	printf( "�t�@�C�����F%s\n",aWrkBuf );
#endif

	fp = fopen( aWrkBuf,"r");
	if( fp == NULL ) {
		printf("�t�@�C���̃I�[�v���Ɏ��s���܂����B\n");
		sFncSyslog ( TRCKIND_ERROR, "GetKinkyu()", "�t�@�C���̃I�[�v���Ɏ��s���܂����B" ) ;
		return RTN_NG;
	}
	iKinkyuNum = 0;
	iWrk2 = 0;
	memset( buff,0,100 );
	while( fgets( buff, 100, fp ) != NULL ) {
		++iWrk2;
	}

	wkTbl = malloc(sizeof(KINKYU_INF)*iWrk2);
	rewind(fp); 
	iCnt = 0;
	memset( buff,0,100 );
	while( fgets( buff, 100, fp ) != NULL ) {
		if( iCnt >= iWrk2 ) {
			break;
		}
		/* �����̉��s�R�[�h���폜 */
		adrCR = strchr(buff, ( int )'\r');
		if (adrCR != NULL) {
			*adrCR = '\0';
		}
		pFld = malloc(sizeof(char *)*16);
		cnt = 0;
		offset = 0;;
		pFld[cnt] = &buff[cnt];
		cnt++;
		while (buff[offset] != '\0') {
			if (buff[offset] == ',') {
				pFld[cnt++] = &buff[offset+1];
				buff[offset] = '\0';
			}
			offset++;
		}
		if (cnt != 4) {
			// �t�B�[���h������v���Ȃ�
			printf( "�t�B�[���h������v���܂���ł����B\n" );
			sFncSyslog ( TRCKIND_ERROR, "GetKinkyu()", "�t�B�[���h������v���܂���ł����B" ) ;
			free( pFld );
			break;
		}
		/* No. 1 ���͋@�敪�擾 */
		strcpy( wkTbl[iCnt].bskkbn,pFld[0] );
		if( strcmp(wkTbl[iCnt].bskkbn,aMekbn) == 0 ) {
			++iKinkyuNum;
		}
		/* No. 2 �����O���[�v�擾 */
		strcpy( wkTbl[iCnt].knsgrp,pFld[1] );
		/* No. 3 ���ڃR�[�h�擾 */
		strcpy( wkTbl[iCnt].kmkcd,pFld[2] );
		/* No. 4 �������ڃR�[�h�擾 */
		strcpy( wkTbl[iCnt].nbkmkcd,pFld[3] );

		++iCnt;
		memset( buff,0,100 );
		free( pFld );
	}

	if( iKinkyuNum > 0 ) {
		pKinkyu = malloc(sizeof(KINKYU_INF)*iKinkyuNum);

		iCnt2 = 0;
		for( iCnt=0; iCnt<iWrk2; iCnt++ ) {
			if( strcmp(wkTbl[iCnt].bskkbn,aMekbn) == 0 ) {
				memcpy( &pKinkyu[iCnt2],&wkTbl[iCnt],sizeof(KINKYU_INF) );
				++iCnt2;
			}
		}
	}
	free( wkTbl );

	return RTN_OK;
}
/******************************************************************************/
/*  �� �� ���@�FGetKmkmst()					  						     	  */
/*  �@�\�T�v�@�F���ڃ}�X�^�擾	                 							  */
/*  ���@�@�́@�F�Ȃ�                                                          */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F RTN_OK		: ����											  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
int GetKmkmst( void )
{
	int		iWrk2;
	int		iCnt;
	int		iCnt2;
	char	aWrkBuf[255];
	char	buff[1024];
	FILE	*fp;
	char	** pFld;
	int		cnt;
	int		offset;
	Kmkmst* wkMst;

	char	aFunc[32];
	char	*adrCR;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetKmkmst()\n" );
#endif

	wkMst = NULL;
	adrCR = NULL;
	memset( aWrkBuf, 0, sizeof(aWrkBuf) );
	strcpy( aWrkBuf,aMstFolder );
	strcat( aWrkBuf,KMKMST_FILE_NAME );

#ifdef _DEBUG_
	printf( "�t�@�C�����F%s\n",aWrkBuf );
#endif

	fp = fopen( aWrkBuf,"r");
	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "GetKmkmst()", "�t�@�C���̃I�[�v���Ɏ��s���܂����B" ) ;
		printf("�t�@�C���̃I�[�v���Ɏ��s���܂����B\n");
		return RTN_NG;
	}
	iKmkmstNum = 0;
	iWrk2 = 0;
	memset( buff,0,1024 );
	while( fgets( buff, 1024, fp ) != NULL ) {
		++iWrk2;									/* 070/071 */
	}

	wkMst = malloc(sizeof(Kmkmst)*iWrk2);			/* 070/071 */
	rewind(fp); 
	iCnt = 0;
	memset( buff,0,1024 );
	while( fgets( buff, 1024, fp ) != NULL ) {
		if( iCnt >= iWrk2 ) {
			break;
		}
		/* �����̉��s�R�[�h���폜 */
		adrCR = strchr(buff, ( int )'\r');
		if (adrCR != NULL) {
			*adrCR = '\0';
		}
		pFld = malloc(sizeof(char *)*80);
		cnt = 0;
		offset = 0;;
		pFld[cnt] = &buff[cnt];
		cnt++;
		while (buff[offset] != '\0') {
			if (buff[offset] == ',') {
				pFld[cnt++] = &buff[offset+1];
				buff[offset] = '\0';
			}
			offset++;
		}
		if (cnt != 48) {
		/* �t�B�[���h������v���Ȃ� */
			sFncSyslog ( TRCKIND_ERROR, "GetKmkmst()", "�t�B�[���h������v���܂���ł����B" ) ;
			printf( "�t�B�[���h������v���܂���ł����B\n" );
			free( pFld );
			break;
		}
		if( atoi(pFld[44]) <= atoi(sSysknrmst.kjnsriymd) ) {	/* 070/071 */
			++iKmkmstNum;
		}
		/* No. 1 �����O���[�v�擾 */
		strcpy( wkMst[iCnt].knsgrp,pFld[0] );
		/* No. 2 ���ڃR�[�h�擾 */
		strcpy( wkMst[iCnt].kmkcd,pFld[1] );
		/* No. 11 �T���v�����O�R�[�h�擾 */
		strcpy( wkMst[iCnt].smpcd,pFld[10] );
		/* No. 12 �e���ڃR�[�h�擾 */
		strcpy( wkMst[iCnt].oyakmkcd,pFld[11] );
		/* No. 14 �Z�N�V�����R�[�h�擾 */
		strcpy( wkMst[iCnt].seccd,pFld[13] );
		/* No. 32 �␳�L���t���O */
		wkMst[iCnt].hsiumflg = pFld[31][0];
		/* No. 37 �萫�E��ʃt���O�擾 */
		wkMst[iCnt].tstrflg = pFld[36][0];
		/* No. 40 �������e���t���O 06/04/13 */
		wkMst[iCnt].ksjhflg = pFld[39][0];
		/* No. 42 X-M�W�v�t���O�擾 */
		wkMst[iCnt].xmskflg = pFld[41][0];
		/* No. 43 X-M�`�F�b�N�t���O�擾 */
		wkMst[iCnt].xmchkflg = pFld[42][0];
		/* No. 44 X-M�J�E���g���擾 */
		wkMst[iCnt].xmcount = atoi(pFld[43]);
		/* No. 45 �J�n�N�����擾 */
		strcpy( wkMst[iCnt].kaiymd,pFld[44] );
		/* No. 46 �p�~�N�����擾 */
		strcpy( wkMst[iCnt].haiymd,pFld[45] );

		++iCnt;
		memset( buff,0,1024 );
		free( pFld );
	}

/* [ start 070/071 */
	if( iKmkmstNum > 0 ) {
		pKmkmst = malloc(sizeof(Kmkmst)*iKmkmstNum);

		iCnt2 = 0;
		for( iCnt=0; iCnt<iWrk2; iCnt++ ) {
			if( atoi(wkMst[iCnt].kaiymd) <= atoi(sSysknrmst.kjnsriymd) ) {
				memcpy( &pKmkmst[iCnt2],&wkMst[iCnt],sizeof(Kmkmst) );
				++iCnt2;
			}
		}
	}
	free( wkMst );
/* ] end 070/071 */

	return RTN_OK;
}
/******************************************************************************/
/*  �� �� ���@�FGetCtrlmst()				  						     	  */
/*  �@�\�T�v�@�F�R���g���[���}�X�^�擾	           							  */
/*  ���@�@�́@�F�Ȃ�                                                          */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F RTN_OK		: ����											  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
int GetCtrlmst( void )
{
	int		iWrk2;
	int		iCnt;
	int		iCnt2;
	char	aWrkBuf[255];
	char	buff[1024];
	FILE	*fp;
	char	** pFld;
	int		cnt;
	int		offset;
	Ctrlmst* wkMst;

	char	aFunc[32];
	char	*adrCR;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetCtrlmst()\n" );
#endif

	wkMst = NULL;
	adrCR = NULL;
	memset( aWrkBuf, 0, sizeof(aWrkBuf) );
	strcpy( aWrkBuf,aMstFolder );
	strcat( aWrkBuf,CTRLMST_FILE_NAME );

#ifdef _DEBUG_
	printf( "�t�@�C�����F%s\n",aWrkBuf );
#endif

	fp = fopen( aWrkBuf,"r");
	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "GetCtrlmst()", "�t�@�C���̃I�[�v���Ɏ��s���܂����B" ) ;
		printf("�t�@�C���̃I�[�v���Ɏ��s���܂����B\n");
		return RTN_NG;
	}
	iCtrlmstNum = 0;
	iWrk2 = 0;
	memset( buff,0,1024 );
	while( fgets( buff, 1024, fp ) != NULL ) {
		++iWrk2;
	}

	wkMst = malloc(sizeof(Ctrlmst)*iWrk2);
	rewind(fp); 
	iCnt = 0;
	memset( buff,0,1024 );
	while( fgets( buff, 1024, fp ) != NULL ) {
		if( iCnt >= iWrk2 ) {
			break;
		}
		/* �����̉��s�R�[�h���폜 */
		adrCR = strchr(buff, ( int )'\r');
		if (adrCR != NULL) {
			*adrCR = '\0';
		}
		pFld = malloc(sizeof(char *)*50);
		cnt = 0;
		offset = 0;;
		pFld[cnt] = &buff[cnt];
		cnt++;
		while (buff[offset] != '\0') {
			if (buff[offset] == ',') {
				pFld[cnt++] = &buff[offset+1];
				buff[offset] = '\0';
			}
			offset++;
		}
		if (cnt != 38) {
		/* �t�B�[���h������v���Ȃ� */
			sFncSyslog ( TRCKIND_ERROR, "GetCtrlmst()", "�t�B�[���h������v���܂���ł����B" ) ;
			printf( "�t�B�[���h������v���܂���ł����B\n" );
			free( pFld );
			break;
		}
		/* No. 1 ���͋@�敪�擾 */
		strcpy( wkMst[iCnt].bskkbn,pFld[0] );
		if( (strcmp(wkMst[iCnt].bskkbn,aMekbn) == 0)
				&& (atoi(pFld[34]) <= atoi(sSysknrmst.kjnsriymd)) ) {	/* 070/071 */
			++iCtrlmstNum;
		}
		/* No. 2 �������ڃR�[�h�擾 */
		strcpy( wkMst[iCnt].nbkmkcd,pFld[1] );
		/* No. 3 �R���g���[����ʎ擾 */
		strcpy( wkMst[iCnt].ctrlsbt,pFld[2] );
		/* No. 6 ���򃍃b�gNo�擾 */
		strcpy( wkMst[iCnt].syklotno,pFld[5] );
		/* No. 7 �R���g���[�����x���擾 */
		strcpy( wkMst[iCnt].ctrllbl,pFld[6] );
		/* No. 8 ���ϒl�擾 */
		strcpy( wkMst[iCnt].ctrlx,pFld[7] );
		/* No. 9 �W���΍�(SD)�擾 */
		strcpy( wkMst[iCnt].ctrlsd,pFld[8] );
		/* No. 35 �J�n�N�����擾 */
		strcpy( wkMst[iCnt].kaiymd,pFld[34] );

		++iCnt;
		memset( buff,0,1024 );
		free( pFld );
	}

	if( iCtrlmstNum > 0 ) {
		pCtrlmst = malloc(sizeof(Ctrlmst)*iCtrlmstNum);

		iCnt2 = 0;
		for( iCnt=0; iCnt<iWrk2; iCnt++ ) {
			if( (strcmp(wkMst[iCnt].bskkbn,aMekbn) == 0)
					&& (atoi(wkMst[iCnt].kaiymd) <= atoi(sSysknrmst.kjnsriymd)) ) {	/* 070/071 */
				memcpy( &pCtrlmst[iCnt2],&wkMst[iCnt],sizeof(Ctrlmst) );
				++iCnt2;
			}
		}
	}
	free( wkMst );

	return RTN_OK;
}
/******************************************************************************/
/*  �� �� ���@�FGetSysknrmst()				  						     	  */
/*  �@�\�T�v�@�F�V�X�e���Ǘ��}�X�^�擾	           							  */
/*  ���@�@�́@�F�Ȃ�                                                          */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F RTN_OK		: ����											  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
int GetSysknrmst( void )
{
	char	aWrkBuf[255];
	char	buff[1024];
	FILE	*fp;
	char	** pFld;
	int		cnt;
	int		offset;

	char	aFunc[32];
	char	*adrCR;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetSysknrmst()\n" );
#endif

	adrCR = NULL;
	memset( aWrkBuf, 0, sizeof(aWrkBuf) );
	strcpy( aWrkBuf,aMstFolder );
	strcat( aWrkBuf,SYSKNRMST_FILE_NAME );

#ifdef _DEBUG_
	printf( "�t�@�C�����F%s\n",aWrkBuf );
#endif

	fp = fopen( aWrkBuf,"r");
	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "GetSysknrmst()", "�t�@�C���̃I�[�v���Ɏ��s���܂����B" ) ;
		printf("�t�@�C���̃I�[�v���Ɏ��s���܂����B\n");
		return RTN_NG;
	}
	memset( buff,0,1024 );
	while( fgets( buff, 1024, fp ) != NULL ) {
		/* �����̉��s�R�[�h���폜 */
		adrCR = strchr(buff, ( int )'\r');
		if (adrCR != NULL) {
			*adrCR = '\0';
		}
		pFld = malloc(sizeof(char *)*50);
		cnt = 0;
		offset = 0;;
		pFld[cnt] = &buff[cnt];
		cnt++;
		while (buff[offset] != '\0') {
			if (buff[offset] == ',') {
				pFld[cnt++] = &buff[offset+1];
				buff[offset] = '\0';
			}
			offset++;
		}
		if (cnt != 44) {
		/* �t�B�[���h������v���Ȃ� */
			sFncSyslog ( TRCKIND_ERROR, "GetSysknrmst()", "�t�B�[���h������v���܂���ł����B" ) ;
			printf( "�t�B�[���h������v���܂���ł����B\n" );
			free( pFld );
			break;
		}
		/* No. 3 ����擾 */
		strcpy( sSysknrmst.kjnsriymd,pFld[2] );
		free( pFld );

		break;
	}
	return RTN_OK;
}
/* [ start 009 060417 */
/******************************************************************************/
/*  �� �� ���@�FGetKnsgmst()				  						     	  */
/*  �@�\�T�v�@�F�����O���[�v�}�X�^�擾	           							  */
/*  ���@�@�́@�F�Ȃ�                                                          */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F RTN_OK		: ����											  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
int GetKnsgmst( void )
{
	int		iWrk2;
	int		iCnt;
	int		iCnt2;
	char	aWrkBuf[255];
	char	buff[1024];
	FILE	*fp;
	char	** pFld;
	int		cnt;
	int		offset;
	Knsgmst* wkMst;

	char	aFunc[32];
	char	*adrCR;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetKnsgmst()\n" );
#endif

	wkMst = NULL;
	adrCR = NULL;
	memset( aWrkBuf, 0, sizeof(aWrkBuf) );
	strcpy( aWrkBuf,aMstFolder );
	strcat( aWrkBuf,KNSGMST_FILE_NAME );

#ifdef _DEBUG_
	printf( "�t�@�C�����F%s\n",aWrkBuf );
#endif

	fp = fopen( aWrkBuf,"r");
	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "GetKnsgmst()", "�t�@�C���̃I�[�v���Ɏ��s���܂����B" ) ;
		printf("�t�@�C���̃I�[�v���Ɏ��s���܂����B\n");
		return RTN_NG;
	}
	iKnsgmstNum = 0;
	iWrk2 = 0;
	memset( buff,0,1024 );
	while( fgets( buff, 1024, fp ) != NULL ) {
		++iWrk2;
	}

	wkMst = malloc(sizeof(Knsgmst)*iWrk2);
	rewind(fp); 
	iCnt = 0;
	memset( buff,0,1024 );
	while( fgets( buff, 1024, fp ) != NULL ) {
		if( iCnt >= iWrk2 ) {
			break;
		}
		/* �����̉��s�R�[�h���폜 */
		adrCR = strchr(buff, ( int )'\r');
		if (adrCR != NULL) {
			*adrCR = '\0';
		}
		pFld = malloc(sizeof(char *)*80);
		cnt = 0;
		offset = 0;;
		pFld[cnt] = &buff[cnt];
		cnt++;
		while (buff[offset] != '\0') {
			if (buff[offset] == ',') {
				pFld[cnt++] = &buff[offset+1];
				buff[offset] = '\0';
			}
			offset++;
		}
		if (cnt != 30) {
		/* �t�B�[���h������v���Ȃ� */
			sFncSyslog ( TRCKIND_ERROR, "GetKnsgmst()", "�t�B�[���h������v���܂���ł����B" ) ;
			printf( "�t�B�[���h������v���܂���ł����B(%d,%d)\n",iCnt, cnt );
			free( pFld );
			break;
		}
		if( atoi(pFld[25]) <= atoi(sSysknrmst.kjnsriymd) ) {	/* 070/071 */
			++iKnsgmstNum;
		}
		/* No. 1 �����O���[�v�擾 */
		strcpy( wkMst[iCnt].knsgrp,pFld[0] );
		/* No.19 �e��R�[�h�擾 */
		strcpy( wkMst[iCnt].ykcd,pFld[19] );
		/* No.26 �J�n�N�����擾 */
		strcpy( wkMst[iCnt].kaiymd,pFld[26] );

		++iCnt;
		memset( buff,0,1024 );
		free( pFld );
	}

	if( iKnsgmstNum > 0 ) {
		pKnsgmst = malloc(sizeof(Knsgmst)*iKnsgmstNum);

		iCnt2 = 0;
		for( iCnt=0; iCnt<iWrk2; iCnt++ ) {
			if( atoi(wkMst[iCnt].kaiymd) <= atoi(sSysknrmst.kjnsriymd) ) {
				memcpy( &pKnsgmst[iCnt2],&wkMst[iCnt],sizeof(Knsgmst) );
				++iCnt2;
			}
		}
	}
	free( wkMst );

	return RTN_OK;
}
/* ] end 009 060417 */
/******************************************************************************/
/*  �� �� ���@�FGetKmkcd()					  						     	  */
/*  �@�\�T�v�@�F���ڃR�[�h�擾	                							  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fint			�I�[�_�[����                         		      */
/*�@ ��Q���� �Fchar*       �������ڃR�[�h   					 		      */
/*  �o�@�@�́@�F                                                              */
/*�@ ��R���� �Fchar*       ���ڃR�[�h   					 	     	      */
/*  ���A���@�F RTN_OK		: ����(�I�[�_�[�t�@�C��)     					  */
/* �@�@�@�@�@�@�@2    		: ���s(���ڃR�[�h�e�[�u��)						  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
int GetKmkcd( int reqnum,char* nbkmkcd,char* kmkcd )
{
	int	iCnt;
	int	iCnt2;
	int iLen;
	char aWrk[8];
	char aWrk2[8];
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetKmkcd()\n" );
#endif

	memset( aWrk,0,8 );
	memset( aWrk2,0,8 );
	memset( kmkcd,0,8 );
	strcat( aWrk,"       " );
	iLen = strlen( nbkmkcd );
	strncpy( aWrk,nbkmkcd,iLen );

	for( iCnt=0; iCnt<iMechmstNum; iCnt++ ) {
		if( strncmp( pMechmst[iCnt].nbkmcd,aWrk,7 ) == 0 ) {
			for( iCnt2=0; iCnt2<reqnum; iCnt2++ ) {
				if( strncmp( pKenorder[iCnt2].kmkcd,pMechmst[iCnt].kmkcd,7 ) == 0 ) {
					strncpy( kmkcd,pMechmst[iCnt].kmkcd,7 );
					return RTN_OK;
				}
			}
		}
	}
	for( iCnt=0; iCnt<iKinkyuNum; iCnt++ ) {
		if( strncmp( pKinkyu[iCnt].nbkmkcd,aWrk,7 ) == 0 ) {
			strncpy( kmkcd,pKinkyu[iCnt].kmkcd,7 );
			return 2;
		}
	}
	return RTN_NG;
}
/******************************************************************************/
/*  �� �� ���@�FGetNbkmkcd()					  					     	  */
/*  �@�\�T�v�@�F�������ڃR�[�h�擾	                						  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar*       ���ڃR�[�h       					 		      */
/*  �o�@�@�́@�F                                                              */
/*�@ ��Q���� �Fchar*       �������ڃR�[�h   					 		      */
/*  ���A���@�F RTN_OK		: ����                       					  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
int GetNbkmkcd( char* kmkcd,char* nbkmkcd )
{
	int	iCnt;
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetNbkmkcd()\n" );
#endif

	memset( nbkmkcd,0,8 );
printf("GetNbkmkcd %d\n",iMechmstNum);
	for( iCnt=0; iCnt<iMechmstNum; iCnt++ ) {
		if( strncmp( pMechmst[iCnt].kmkcd,kmkcd,7 ) == 0 ) {
			strncpy( nbkmkcd,pMechmst[iCnt].nbkmcd,7 );
			return RTN_OK;
		}
	}
	return RTN_NG;
}
/******************************************************************************/
/*  �� �� ���@�FGetTstrflg()					       				     	  */
/*  �@�\�T�v�@�F�萫�E��ʃt���O�擾	               						  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar*       ���ڃR�[�h         					 		      */
/*  �o�@�@�́@�F                                                              */
/*�@ ��Q���� �Fchar*       �萫�E��ʃt���O  					 		      */
/*  ���A���@�F RTN_OK		: ����                       					  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
int GetTstrflg( char* kmkcd,char* knsgrp,char* flg )
{
	int	iCnt;
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetTstrflg()\n" );
#endif

	memset( flg,0,32);

	for( iCnt=0; iCnt<iKmkmstNum; iCnt++ ) {

		if( (strncmp( pKmkmst[iCnt].kmkcd,kmkcd,7 ) == 0) 
			&& (strncmp(pKmkmst[iCnt].knsgrp,knsgrp,16) == 0) ) {
			flg[0] = pKmkmst[iCnt].tstrflg;
			return RTN_OK;
		}
	}
	return RTN_NG;
}
/******************************************************************************/
/*  �� �� ���@�FGetKnsgrp()					        				     	  */
/*  �@�\�T�v�@�F�����O���[�v�R�[�h�擾	               						  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar*       ���ڃR�[�h         					 		      */
/*  �o�@�@�́@�F                                                              */
/*�@ ��Q���� �Fchar*       �����O���[�v�R�[�h  				 		      */
/*  ���A���@�F RTN_OK		: ����                       					  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
int GetKnsgrp( char* kmkcd,char* knsgrp )
{
	int	iCnt;
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetKnsgrp()\n" );
#endif

	memset( knsgrp,0,32 );

	for( iCnt=0; iCnt<iKmkmstNum; iCnt++ ) {
		if( strncmp( pKmkmst[iCnt].kmkcd,kmkcd,7 ) == 0 ) {
			strncpy( knsgrp,pKmkmst[iCnt].knsgrp,16 );
			return RTN_OK;
		}
	}
	return RTN_NG;
}
/******************************************************************************/
/*  �� �� ���@�FGetSmpcd()					        				     	  */
/*  �@�\�T�v�@�F�T���v�����O�R�[�h�擾	               						  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar*       ���ڃR�[�h         					 		      */
/*  �o�@�@�́@�F                                                              */
/*�@ ��Q���� �Fchar*       �T���v�����O�R�[�h					 		      */
/*  ���A���@�F RTN_OK		: ����                       					  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
int GetSmpcd( char* kmkcd,char* knsgrp,char* smpcd )
{
	int	iCnt;
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetSmpcd()\n" );
#endif

	memset( smpcd,0,32 );

	for( iCnt=0; iCnt<iKmkmstNum; iCnt++ ) {
		if( (strncmp( pKmkmst[iCnt].kmkcd,kmkcd,7 ) == 0)
			&& (strncmp(pKmkmst[iCnt].knsgrp,knsgrp,16) == 0) ) {

			strncpy( smpcd,pKmkmst[iCnt].smpcd,7 );
			return RTN_OK;
		}
	}
	return RTN_NG;
}
/******************************************************************************/
/*  �� �� ���@�FGetOyakmkcd()					        	     	     	  */
/*  �@�\�T�v�@�F�e���ڃR�[�h�擾	                 						  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar*       ���ڃR�[�h         					 		      */
/*  �o�@�@�́@�F                                                              */
/*�@ ��Q���� �Fchar*       �e���ڃR�[�h     					 		      */
/*  ���A���@�F RTN_OK		: ����                       					  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
int GetOyakmkcd( char* kmkcd,char* knsgrp,char* oyakmkcd )
{
	int	iCnt;
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetOyakmkcd()\n" );
#endif

	memset( oyakmkcd,0,32 );

	for( iCnt=0; iCnt<iKmkmstNum; iCnt++ ) {
		if( (strncmp( pKmkmst[iCnt].kmkcd,kmkcd,7 ) == 0)
			&& (strncmp(pKmkmst[iCnt].knsgrp,knsgrp,16) == 0) ) {
			strncpy( oyakmkcd,pKmkmst[iCnt].oyakmkcd,7 );
			return RTN_OK;
		}
	}
	return RTN_NG;
}
/******************************************************************************/
/*  �� �� ���@�FGetSeccd()			     		        	     	     	  */
/*  �@�\�T�v�@�F�Z�N�V�����R�[�h�擾	              						  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar*       ���ڃR�[�h         					 		      */
/*  �o�@�@�́@�F                                                              */
/*�@ ��Q���� �Fchar*       �Z�N�V�����R�[�h  					 		      */
/*  ���A���@�F RTN_OK		: ����                       					  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
int GetSeccd( char* kmkcd,char* knsgrp,char* seccd )
{
	int	iCnt;
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetSeccd()\n" );
#endif

	memset( seccd,0,32 );

	for( iCnt=0; iCnt<iKmkmstNum; iCnt++ ) {
		if( (strncmp( pKmkmst[iCnt].kmkcd,kmkcd,7 ) == 0)
			&& (strncmp(pKmkmst[iCnt].knsgrp,knsgrp,16) == 0) ) {
			strncpy( seccd,pKmkmst[iCnt].seccd,2 );
			return RTN_OK;
		}
	}
	return RTN_NG;
}
/******************************************************************************/
/*  �� �� ���@�FGetXmcount()		     		        	     	     	  */
/*  �@�\�T�v�@�FX-M�J�E���g�擾	                    						  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar*       �����O���[�v�R�[�h 					 		      */
/*�@ ��Q���� �Fchar*       ���ڃR�[�h         					 		      */
/*  �o�@�@�́@�F                                                              */
/*�@ ��R���� �Fint*        X-M�J�E���g      					 		      */
/*  ���A���@�F RTN_OK		: ����                       					  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
int GetXmcount( char* kmkcd,char* knsgrp,int* xmcount )
{
	int	iCnt;
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "%sGetXmcount()\n", Now() );
#endif

	for( iCnt=0; iCnt<iKmkmstNum; iCnt++ ) {
		if( (strncmp( pKmkmst[iCnt].kmkcd,kmkcd,7 ) == 0)
			&& (strncmp(pKmkmst[iCnt].knsgrp,knsgrp,16) == 0) ) {
			*xmcount = (int)pKmkmst[iCnt].xmcount;
#ifdef _DEBUG_
            printf( "GetXmcount OK!\n");
            printf( "X-M�J�E���g:%d\n", *xmcount);
#endif
			return RTN_OK;
		}
	}
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** X-M�J�E���g���擾�ł��Ȃ������ꍇ�ɁA*xmcount�̒l���s��ƂȂ� ***/
    *xmcount = -1;
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
#ifdef _DEBUG_
            printf( "GetXmcount NG!\n");
#endif
	return RTN_NG;
}
/* [ start 060418 009 */
/******************************************************************************/
/*  �� �� ���@�FGetYkcd()					        				     	  */
/*  �@�\�T�v�@�F�e���ʎ擾			               						  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar*       �����O���[�v�R�[�h 					 		      */
/*  �o�@�@�́@�F                                                              */
/*�@ ��Q���� �Fchar*       �e��R�[�h 		 			     	 		      */
/*  ���A���@�F RTN_OK		: ����                       					  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
int GetYkcd( char* knsgrp,char* ykcd )
{
	int	iCnt;
	char aFunc[32];

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetYkcd()\n" );
#endif

	for( iCnt=0; iCnt<iKnsgmstNum; iCnt++ ) {
		if( strncmp( pKnsgmst[iCnt].knsgrp,knsgrp,16 ) == 0 ) {
			strncpy( ykcd,pKnsgmst[iCnt].ykcd,4 );
			return RTN_OK;
		}
	}
	return RTN_NG;
}
/* ] end 060418 009 */

/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** X-M�����W�`�F�b�N�̂��ߒǉ� ***/
/******************************************************************************/
/*  �� �� ���@�FGetXbarmmst()                                                 */
/*  �@�\�T�v�@�FX-M�}�X�^�擾                                                 */
/*  ���@�@�́@�F�Ȃ�                                                          */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F RTN_OK     : ����                                            */
/* �@�@�@�@�@�@�@RTN_NG     : ���s                                            */
/******************************************************************************/
int GetXbarmmst( void )
{
	int		iWrk2;
	int		iCnt;
	int		iCnt2;
	char	aWrkBuf[255];
	char	buff[200];
	FILE	*fp;
	char	** pFld;
	int		cnt;
	int		offset;
	Xbarmmst* wkMst;

	char	aFunc[32];
	char	*adrCR;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetXbarmmst()\n" );
#endif

	wkMst = NULL;
	adrCR = NULL;
	memset( aWrkBuf, 0, sizeof(aWrkBuf) );
	strcpy( aWrkBuf,aMstFolder );
	strcat( aWrkBuf,XBARMMST_FILE_NAME );

#ifdef _DEBUG_
	printf( "�t�@�C�����F%s\n",aWrkBuf );
#endif

	fp = fopen( aWrkBuf,"r");
	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "GetXbarmmst()", "�t�@�C���̃I�[�v���Ɏ��s���܂����B" ) ;
		printf("�t�@�C���̃I�[�v���Ɏ��s���܂����B\n");
		return RTN_NG;
	}
	iXbarmmstNum = 0;
	iWrk2 = 0;
	memset( buff,0,200 );
	while( fgets( buff, 200, fp ) != NULL ) {
		++iWrk2;
	}

	wkMst = malloc(sizeof(Xbarmmst)*iWrk2);
	rewind(fp); 
	iCnt = 0;
	memset( buff,0,200 );
	while( fgets( buff, 200, fp ) != NULL ) {
		if( iCnt >= iWrk2 ) {
			break;
		}
		/* �����̉��s�R�[�h���폜 */
		adrCR = strchr(buff, ( int )'\r');
		if (adrCR != NULL) {
			*adrCR = '\0';
		}
		pFld = malloc(sizeof(char *)*16);
		if (pFld == NULL) {
			sFncSyslog ( TRCKIND_ERROR, "GetXbarmmst()", "��ƃG���A�̊m�ۂɎ��s���܂����B" ) ;
			printf( "��ƃG���A�̊m�ۂɎ��s���܂����B\n" );
			break;
		}

		cnt = 0;
		offset = 0;;
		pFld[cnt] = &buff[cnt];
		cnt++;
		while (buff[offset] != '\0') {
			if (buff[offset] == ',') {
				pFld[cnt++] = &buff[offset+1];
				buff[offset] = '\0';
			}
			offset++;
		}
		if (cnt != 11) {
		/* �t�B�[���h������v���Ȃ� */
			sFncSyslog ( TRCKIND_ERROR, "GetXbarmmst()", "�t�B�[���h������v���܂���ł����B" ) ;
			printf( "�t�B�[���h������v���܂���ł����B\n" );
			free( pFld );
			break;
		}
		if((atoi(pFld[7]) <= atoi(sSysknrmst.kjnsriymd)) &&
		   (atoi(pFld[8]) >= atoi(sSysknrmst.kjnsriymd))) {
			strcpy(wkMst[iCnt].knsgrp,   pFld[ 0]);	/* No.  1 �����O���[�v		*/
			strcpy(wkMst[iCnt].kmkcd,    pFld[ 1]);	/* No.  2 ���ڃR�[�h�擾	*/
			strcpy(wkMst[iCnt].minval,   pFld[ 2]);	/* No.  3 ���� �����l		*/
			strcpy(wkMst[iCnt].minart,   pFld[ 3]);	/* No.  4 �x�����			*/
			strcpy(wkMst[iCnt].avgval,   pFld[ 4]);	/* No.  5 ���ϒl			*/
			strcpy(wkMst[iCnt].maxart,   pFld[ 5]);	/* No.  6 �x�����			*/
			strcpy(wkMst[iCnt].maxval,   pFld[ 6]);	/* No.  7 ��� ����l		*/
			strcpy(wkMst[iCnt].kaiymd,   pFld[ 7]);	/* No.  8 �J�n�N����		*/
			strcpy(wkMst[iCnt].haiymd,   pFld[ 8]);	/* No.  9 �p�~�N����		*/
			strcpy(wkMst[iCnt].hnktntid, pFld[ 9]);	/* No. 10 �ύX�S���҂h�c	*/
			strcpy(wkMst[iCnt].ksndh,    pFld[10]);	/* No. 11 ���X�V����		*/

			++iXbarmmstNum;
			++iCnt;
		}

		memset( buff,0,200 );
		free( pFld );
	}

	if( iXbarmmstNum > 0 ) {
		pXbarmmst = malloc(sizeof(Xbarmmst)*iXbarmmstNum);

		for( iCnt=0; iCnt<iXbarmmstNum; iCnt++ ) {
			memcpy( &pXbarmmst[iCnt],&wkMst[iCnt],sizeof(Xbarmmst) );
			++iCnt2;
		}
	}
	free( wkMst );

	return RTN_OK;
}

/*** ���������W�`�F�b�N�̂��ߒǉ� ***/
/******************************************************************************/
/*  �� �� ���@�FGetRngchkmst()                                                */
/*  �@�\�T�v�@�F�����W�`�F�b�N�}�X�^�擾(�����̂ݕK�v�Ȃ̂Ŕ͈͋敪5�̂ݑΏ�) */
/*  ���@�@�́@�F�Ȃ�                                                          */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F RTN_OK     : ����                                            */
/* �@�@�@�@�@�@�@RTN_NG     : ���s                                            */
/******************************************************************************/
int GetRngchkmst( void )
{
	int		iWrk2;
	int		iCnt;
	int		iCnt2;
	char	aWrkBuf[255];
	char	buff[200];
	FILE	*fp;
	char	** pFld;
	int		cnt;
	int		offset;
	Rngchkmst* wkMst;

	char	aFunc[32];
	char	*adrCR;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	memcpy(aFunc,__func__,sizeof(aFunc));

#ifdef _DEBUG_
	printf( "GetRngchkmst()\n" );
#endif

	wkMst = NULL;
	adrCR = NULL;
	memset( aWrkBuf, 0, sizeof(aWrkBuf) );
	strcpy( aWrkBuf,aMstFolder );
	strcat( aWrkBuf,RNGCHKMST_FILE_NAME );

#ifdef _DEBUG_
	printf( "�t�@�C�����F%s\n",aWrkBuf );
#endif

	fp = fopen( aWrkBuf,"r");
	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "GetRngchkmst()", "�t�@�C���̃I�[�v���Ɏ��s���܂����B" ) ;
		printf("�t�@�C���̃I�[�v���Ɏ��s���܂����B\n");
		return RTN_NG;
	}
	iRngchkmstNum = 0;
	iWrk2 = 0;
	memset( buff,0,200 );
	while( fgets( buff, 200, fp ) != NULL ) {
		++iWrk2;
	}

	wkMst = malloc(sizeof(Rngchkmst)*iWrk2);
	rewind(fp); 
	iCnt = 0;
	memset( buff,0,200 );
	while( fgets( buff, 200, fp ) != NULL ) {
		if( iCnt >= iWrk2 ) {
			break;
		}
		/* �����̉��s�R�[�h���폜 */
		adrCR = strchr(buff, ( int )'\r');
		if (adrCR != NULL) {
			*adrCR = '\0';
		}
		pFld = malloc(sizeof(char *)*16);
		if (pFld == NULL) {
			sFncSyslog ( TRCKIND_ERROR, "GetRngchkmst()", "��ƃG���A�̊m�ۂɎ��s���܂����B" ) ;
			printf( "��ƃG���A�̊m�ۂɎ��s���܂����B\n" );
			break;
		}

		cnt = 0;
		offset = 0;;
		pFld[cnt] = &buff[cnt];
		cnt++;
		while (buff[offset] != '\0') {
			if (buff[offset] == ',') {
				pFld[cnt++] = &buff[offset+1];
				buff[offset] = '\0';
			}
			offset++;
		}
		if (cnt != 14) {
			/* �t�B�[���h������v���Ȃ� */
			sFncSyslog ( TRCKIND_ERROR, "GetRngchkmst()", "�t�B�[���h������v���܂���ł����B" ) ;
			printf( "�t�B�[���h������v���܂���ł����B\n" );
			free( pFld );
			break;
		}
		if((atoi(pFld[10]) <= atoi(sSysknrmst.kjnsriymd)) &&
		   (atoi(pFld[11]) >= atoi(sSysknrmst.kjnsriymd)) &&
		    pFld[0][0] == '5') {
			wkMst[iCnt].hnikbn     = pFld[ 0][0];		/* No.  1 �͈͋敪			*/
			strcpy(wkMst[iCnt].knsgrp,     pFld[ 1]);	/* No.  2 �����O���[�v		*/
			strcpy(wkMst[iCnt].kmkcd,      pFld[ 2]);	/* No.  3 ���ڃR�[�h		*/
			strcpy(wkMst[iCnt].zaicd,      pFld[ 3]);	/* No.  4 �ޗ��R�[�h		*/
			strcpy(wkMst[iCnt].sstcd,      pFld[ 4]);	/* No.  5 �{�݃R�[�h		*/
			wkMst[iCnt].sbt        = pFld[ 5][0];		/* No.  6 ����				*/
			wkMst[iCnt].ssa        = pFld[ 6][0];		/* No.  7 �㉺���敪		*/
			wkMst[iCnt].zen_kyoyou = pFld[ 7][0];		/* No.  8 ���e�敪			*/
			strcpy(wkMst[iCnt].hrng,       pFld[ 8]);	/* No.  9 �����W���		*/
			strcpy(wkMst[iCnt].lrng,       pFld[ 9]);	/* No. 10 �����W����		*/
			strcpy(wkMst[iCnt].kaiymd,     pFld[10]);	/* No. 11 �J�n�N����		*/
			strcpy(wkMst[iCnt].haiymd,     pFld[11]);	/* No. 12 �p�~�N����		*/
			strcpy(wkMst[iCnt].hnktntid,   pFld[12]);	/* No. 13 �ύX�S���҂h�c	*/
			strcpy(wkMst[iCnt].ksndh,      pFld[13]);	/* No. 14 ���X�V����		*/

			++iRngchkmstNum;
			++iCnt;
		}

		memset( buff,0,200 );
		free( pFld );
	}

	if( iRngchkmstNum > 0 ) {
		pRngchkmst = malloc(sizeof(Rngchkmst)*iRngchkmstNum);

		for( iCnt=0; iCnt<iRngchkmstNum; iCnt++ ) {
			memcpy( &pRngchkmst[iCnt],&wkMst[iCnt],sizeof(Rngchkmst) );
			++iCnt2;
		}
	}
	free( wkMst );

	return RTN_OK;
}

/*** X-M�����l�ɕ��ϒl��ݒ肷�� ***/
double GetXMavg(char* knsgrp, char* kmkcd)
{
	double ret = 0;
	int    i;

	for (i = 0; i < iXbarmmstNum; i++) {
		if ((memcmp(pXbarmmst[i].knsgrp, knsgrp, 16) == 0) &&
			(memcmp(pXbarmmst[i].kmkcd,  kmkcd,   7) == 0)) {
            ret = atof(pXbarmmst[i].avgval);
			break;
        }
    }

	return ret;
}
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */
