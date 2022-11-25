/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FGetKenorder.c                                                */
/* �@�T�@�@�@�v�F�����I�[�_�[�擾     	                                      */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/31     A.Yamada       �V�K�쐬                           */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
//#include "DD41399.h"
#include "GetKenorder.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/******************************************************************************/
/*  �֐��錾                                                                  */
/******************************************************************************/
int GetKenorder(SOCKET_INF* ,int, int*);	/* �����I�[�_�[�擾���� */

/******************************************************************************/
/*  �� �� ���@�FGetKenorder()  			         							  */
/*  �@�\�T�v�@�F�����I�[�_�[�擾	     									  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �FSOCKET_INF*		���͋@���                         		      */
/*�@ ��Q���� �Fint             �I�[�_�[�t�@�C���i�[�ʒu���    		      */
/*�@ ��R���� �Fint*            �I�[�_�[����         			 		      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F RTN_OK		: ����											  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
int GetKenorder(SOCKET_INF* p,int iType, int* reqnum)
{
	int iCnt;
	char aWrkBuf2[255];
	char aWrkBuf3[255];		// �C���f�b�N�X�m�F�p
	char aWrkBuf4[255];		// ���[�J���R�s�[�p
	char cWrk[32];
	FILE *fp;

	char ** pFld;
	int cnt;
	int offset;


//	char** buff;
//	char* buff;
	char buff[1024];
	char aFunc[32];

	struct stat stStat;

	memcpy(aFunc,__func__,sizeof(aFunc));
//	SetLogDat(TRCKIND_TRACE,aFunc,"xxx","xxx","xxx","xxx","xxx");
//	ZbmlPutLog(&sLog);


	printf( "GetKenorder()\n" );

	memset( cWrk,0,sizeof(cWrk) );
	sprintf( cWrk,"%d",atoi(p->cRackNum) );

//	MakeFileName( p->cRackNum, p->cRackPosNum );
	MakeFileName( cWrk, p->cRackPosNum, 0 );

	memset( aWrkBuf2, 0, sizeof(aWrkBuf2) );

	if( iType == ORDER_DAT_1 ) {
		strcpy( aWrkBuf2,aKenorderFolder );
		strcpy( aWrkBuf3,aKenorderFolder );
		strcat( aWrkBuf3,"../Index/" );
		strcpy( aWrkBuf4,aKenorderFolder );
		strcat( aWrkBuf4,"local" );
		memset(&stStat, 0, sizeof(stStat));
		if (stat(aWrkBuf4, &stStat) == -1) {
			if (errno == ENOENT) {	// �f�B���N�g�������݂��Ȃ��B
				// �f�B���N�g�������݂��Ȃ�����local�t�H���_���쐬����B
				mkdir(aWrkBuf4, 0777);
			}
		}
		strcat(aWrkBuf4,"/" );
	} else {
		strcpy( aWrkBuf2,aKenorderFolder2 );
		strcpy( aWrkBuf3,aKenorderFolder2 );
		strcat( aWrkBuf3,"../Index/" );
		strcpy( aWrkBuf4,aKenorderFolder2 );
		strcat( aWrkBuf4,"local/" );
	}
	strcat( aWrkBuf2,"OD_" );
	strcat( aWrkBuf2,aFileNameStr );
	strcat( aWrkBuf3,"OD_" );
	strcat( aWrkBuf3,aFileNameStr );
	strcat( aWrkBuf4,"OD_" );
	strcat( aWrkBuf4,aFileNameStr );

#ifdef _DEBUG_
	printf( "�t�@�C����:%s\n",aWrkBuf2 );
#endif
	// �t�@�C���̃I�[�v���O��Index�t�H���_���m�F���t�@�C�������邩�`�F�b�N����B
	// ���̌ネ�[�J�����̃I�[�_�t�@�C���́A�i�[�z���_����local�z���_�Ɉړ����g�p����B
	if (stat(aWrkBuf3, &stStat) == -1) {
		sFncSyslog ( TRCKIND_ERROR, "GetKenorder()", "�t�@�C���̑��݂��܂���B" ) ;
		printf("�t�@�C���̑��݂��܂���B\n");
		return RTN_NG;
	}

	if( iType == ORDER_DAT_1 ) {
		if (stat(aWrkBuf2, &stStat) == 0) {
			if (stat(aWrkBuf4, &stStat) == 0) {
				// ���[�J�����Ɋ��ɂ���Ƃ��̓��[�J���̃t�@�C�����폜����B
				remove(aWrkBuf4);
			}
			if (rename(aWrkBuf2, aWrkBuf4) != 0) {
				sFncSyslog ( TRCKIND_ERROR, "GetKenorder()", "�t�@�C���̈ړ��Ɏ��s���܂����B" ) ;
				printf("�t�@�C���̈ړ��Ɏ��s���܂����B\n");
				strcpy(aWrkBuf4, aWrkBuf2);
			}
		}
		fp = fopen( aWrkBuf4,"r");
		
	}
	else {
		fp = fopen( aWrkBuf2,"r");
	}

	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "GetKenorder()", "�t�@�C���̃I�[�v���Ɏ��s���܂����B" ) ;
		printf("�t�@�C���̃I�[�v���Ɏ��s���܂����B\n");
		return RTN_NG;
	}

//	iCnt=0;
//	while ((iWrk = fgetc(fp)) != EOF){
//		aReadDatStr[iCnt] = (unsigned char)iWrk;
//		iCnt++;
//	}
//	fclose(fp);

//	printf( ".dat�t�@�C���f�[�^�F%s\n",aReadDatStr );


//	buff = (  char**)malloc(sizeof( char* )*MAX_ITEM_NUM );
//	for( iCnt=0; iCnt<MAX_ITEM_NUM; iCnt++ ) {
//		buff[iCnt] = (  char* )malloc( sizeof(  char )*512 );
//	}
//	for( iCnt=0; iCnt<MAX_ITEM_NUM; iCnt++ ) {
//		if( fgets( str, 511, fp ) == NULL ) {
//			break;
//		}
//		sprintf( buff[iCnt],"%s",str );
//		printf( "%s",buff[iCnt] );
//	}
//	for( iCnt = 0; iCnt < MAX_ITEM_NUM; iCnt++ ){
//		if( buff[iCnt] != NULL ) {
//			free( buff[iCnt] );
//		}
//	}
//	free( buff );
//	fclose( fp );

//	while( fgets( buff, 1024, fp ) != NULL ) {
//		++(*reqnum);
//	}
//iCnt = 
//	buff = malloc(sizeof(char)*1024);
	pKenorder = malloc(sizeof(Kenorder)*MAX_ITEM_NUM );
//	printf( "%02x\n",pKenorder[351].kmkcd[0] );

	


//	pKenorder = malloc(sizeof(KENORDER)*100 );
	for( iCnt=0; iCnt<MAX_ITEM_NUM; iCnt++ ) {
//	for( iCnt=0; iCnt<100; iCnt++ ) {
		memset( &pKenorder[iCnt],0,sizeof(Kenorder) );
	}

//	memset( &(p->kenorder),0,sizeof(p->kenorder) );

	while( fgets( buff, 1024, fp ) != NULL ) {
		if( *reqnum >= MAX_ITEM_NUM ) {
			break;
		}
//		printf( "%s",buff );
//		getchar();

		pFld = malloc(sizeof(char *)*100);
//		pKenOrder = malloc(sizeof(struct KENORDER));

		// �J���}��؂�̃��R�[�h�𕪊����ADB���R�[�h�̍\���̂ɐݒ肷��B
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
		if (cnt != 58) {
			// �t�B�[���h������v���Ȃ�
			sFncSyslog ( TRCKIND_ERROR, "GetKenorder()", "�t�B�[���h������v���܂���ł����B" ) ;
			printf( "�t�B�[���h������v���܂���ł����B\n" );
			break;
		}
		/* No. 1 �J�n�N�����擾 */
		strcpy( pKenorder[*reqnum].knskisymd,pFld[0] );
		/* No. 2 �������擾 */
		strcpy( pKenorder[*reqnum].sriymd,pFld[1] );
		/* No. 3 ����No�擾 */
		strcpy( pKenorder[*reqnum].kntno,pFld[2] );
		/* No. 4 ����No�����t���O�擾 */
		pKenorder[*reqnum].kntketflg = pFld[3][0];
		/* No. 5 �����O���[�v�擾 */
		strcpy( pKenorder[*reqnum].knsgrp,pFld[4] );
		/* No. 6 ���ڃR�[�h�擾 */
		strcpy( pKenorder[*reqnum].kmkcd,pFld[5] );
		/* No. 7 �����񐔎擾 */
		pKenorder[*reqnum].knssu = atoi(pFld[6]);
		/* No. 8 �����񐔎}�Ԏ擾 */
		pKenorder[*reqnum].knssueda = atoi(pFld[7]);
		/* No. 9 �˗��������敪�擾 */
		pKenorder[*reqnum].irihsmkbn = pFld[8][0];
		/* No.10 �˗��敪�擾 */
		pKenorder[*reqnum].irikbn = pFld[9][0];
		/* No.11 �����H���敪�擾 */
		pKenorder[*reqnum].ksktkbn = pFld[10][0];
		/* No.12 BML��t�N�����擾 */
		strcpy( pKenorder[*reqnum].utkymd,pFld[11] );
		/* No.13 �˗���No�擾 */
		strcpy( pKenorder[*reqnum].irino,pFld[12] );
		/* No.14 �˗���No�����t���O�擾 */
		pKenorder[*reqnum].iriketflg = pFld[13][0];
		/* No.15 ��������No�擾 */
		pKenorder[*reqnum].zssdino = atoi(pFld[14]);
		/* No.16 �{�݃R�[�h�擾 */
		strcpy( pKenorder[*reqnum].sstcd,pFld[15] );
		/* No.17 �g���[ID�擾 */
		strcpy( pKenorder[*reqnum].trid,pFld[16] );
		/* No.18 �g���[�|�W�V�����擾 */
		pKenorder[*reqnum].trpos = atoi(pFld[17]);
		/* No.19 �A�b�Z�C���b�NID */
		strcpy( pKenorder[*reqnum].asyrckid,pFld[18] );
		/* No.20 �A�b�Z�C���b�N�|�W�V���� */
		pKenorder[*reqnum].asyrckpos = atoi(pFld[19]);
		/* No.21 �e���ڃR�[�h�擾 */
		strcpy( pKenorder[*reqnum].oyakmkcd,pFld[20] );
		/* No.22 �Z�N�V�����R�[�h�擾 */
		strcpy( pKenorder[*reqnum].seccd,pFld[21] );
		/* No.23 ���敉�׋敪�擾 */
		pKenorder[*reqnum].bkfkkbn = pFld[22][0];
		/* No.24 �T���v�����O�R�[�h�擾 */
		strcpy( pKenorder[*reqnum].smpcd,pFld[23] );
		/* No.26 �������ڃR�[�h�擾 */
		strcpy( pKenorder[*reqnum].nbkmkcd,pFld[25] );
		/* No.27 �ޗ��R�[�h�擾 */
		strcpy( pKenorder[*reqnum].zrcd,pFld[26] );
		/* No.28 �D�惌�x���擾 */
		strcpy( pKenorder[*reqnum].ysnlbl,pFld[27] );
		/* No.29 ��lNO�擾 */
		strcpy( pKenorder[*reqnum].kjno,pFld[28] );
		/* No.30 ���ו�NO�\���敪�擾 */
		pKenorder[*reqnum].fkhkknohjkbn = pFld[29][0];
		/* No.31 ���ʊ�lNO�擾 */
		strcpy( pKenorder[*reqnum].tbkjno,pFld[30] );
		/* No.32 ���ʊ�l�t���O�擾 */
		pKenorder[*reqnum].tbkjflg = pFld[31][0];
		/* No.33 ���^�t�����Ԏ擾 */
		strcpy( pKenorder[*reqnum].htkfkhms,pFld[32] );
		/* No.34 �W���t���O�擾 */
		pKenorder[*reqnum].skflg = pFld[33][0];
		/* No.35 ���܃t���O�擾 */
		strcpy( pKenorder[*reqnum].tskflg,pFld[34] );
		/* No.36 �����t���O�擾 */
		strcpy( pKenorder[*reqnum].tktflg,pFld[35] );
		/* No.37�\���ߔ{���擾 */
		strcpy( pKenorder[*reqnum].ytiksbr,pFld[36] );
		/* No.38 �ً}�񍐃t���O�擾 */
		pKenorder[*reqnum].kkflg = pFld[37][0];
		/* No.39 �ً}�˗��t���O�擾 */
		pKenorder[*reqnum].kkiriflg = pFld[38][0];
		/* No.40 �ً}�˗����b�gNo�擾 */
		pKenorder[*reqnum].kkirilotno = atoi(pFld[39]);
		/* No.44 ���ʋ敪�擾 */
		pKenorder[*reqnum].sbtkbn = pFld[43][0];
		/* No.47 �N��擾 */
		strcpy( pKenorder[*reqnum].age,pFld[46] );
		/* No.48 �N��敪�擾 */
		pKenorder[*reqnum].agekbn = pFld[47][0];
		/* No. 49 �̎掞�Ԏ擾 */
		strcpy( pKenorder[*reqnum].sstme,pFld[48] );
		/* No. 50 �̎�N�����擾 */
		strcpy( pKenorder[*reqnum].ssymd,pFld[49] );
		/* No. 55 ����SEQ�擾 */
		pKenorder[*reqnum].knsseq = atoi(pFld[54]);

		++(*reqnum);
	
//		free(pKenOrder);
		free(pFld);
//		memset( buff,0,sizeof(buff) );
	}
//	free( buff );
	fclose(fp);
	return RTN_OK;
}
