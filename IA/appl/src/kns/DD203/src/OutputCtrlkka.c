/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FOutputCtrlkka.c                                              */
/* �@�T�@�@�@�v�F���ʏ��o��       	                                      */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/31     A.Yamada       �V�K�쐬                           */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
//#include <time.h>
#include <sys/time.h>

//#include "DD41399.h"
#include "OutputCtrlkka.h"

/******************************************************************************/
/*  �֐��錾                                                                  */
/******************************************************************************/
int OutputCtrlkka(SOCKET_INF*);				/* �R���g���[�����ʏo�͏��� */

/******************************************************************************/
/*  �� �� ���@�FOutputCtrlkka()  		     				     			  */
/*  �@�\�T�v�@�F�R���g���[�����ʏo��	�@�@								  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �FSOCKET_INF*		���͋@���                         		      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F RTN_OK		: ����											  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
int OutputCtrlkka( SOCKET_INF* p )
{
	int iCnt;
//	int iCnt2;
	int iLen;
//	char aWrkBuf[1024];
	char* aWrkBuf;
	char aWrkBuf2[255];
	FILE *fp;

	time_t t = time(NULL);
	struct tm* tm;
	struct timeval tv;
	char cWrk[30];
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));
//	SetLogDat(TRCKIND_TRACE,aFunc,"xxx","xxx","xxx","xxx","xxx");
//	ZbmlPutLog(&sLog);

	printf( "OutputCtrlkka()\n" );
#if 0
	memset( cWrk,0,sizeof(cWrk) );
	if( (p->cRackNum[0] >= 0x30) && (p->cRackNum[0] <= 0x39) ) {
		sprintf( cWrk,"%d",atoi(p->cRackNum) );
	} else {
		strcpy( cWrk,p->cRackNum );
	}

//	MakeFileName( p->cRackNum, p->cRackPosNum );
//	MakeFileName( cWrk, p->cRackPosNum );
	MakeFileName( cWrk, p->aGouki, 1 );
#endif
	memset( aWrkBuf2, 0, sizeof(aWrkBuf2) );
	strcpy( aWrkBuf2,aCtrlkkaFolder );
	strcat( aWrkBuf2,"CT_" );
	strcat( aWrkBuf2,aFileNameStr );

	printf( "�t�@�C����:%s\n",aWrkBuf2 );

	fp = fopen( aWrkBuf2,"a");
	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "OutputCtrlkka()", "�t�@�C���̃I�[�v���Ɏ��s���܂����B" ) ;
		printf("�t�@�C���̃I�[�v���Ɏ��s���܂����B\n");
		return RTN_NG;
	}

		aWrkBuf = malloc(sizeof(char)*1024);

//	for( iCnt2=0; iCnt2<iItemNum; iCnt2++ ) {
		memset( aWrkBuf, 0, 1024 );
		/* No. 1 �����J�n���ݒ� */
		strncat( aWrkBuf,p->sCtrlkka.knskisymd,strlen(p->sCtrlkka.knskisymd) );
		strcat( aWrkBuf,"," );
		/* No. 2 ���͋@�敪�擾 */
		strncat( aWrkBuf,p->sCtrlkka.bskkbn,strlen(p->sCtrlkka.bskkbn) );
		strcat( aWrkBuf,"," );
		/* No. 3 ���͋@���C���擾 */
		strncat( aWrkBuf,p->sCtrlkka.bsklne,strlen(p->sCtrlkka.bsklne) );
		strcat( aWrkBuf,"," );
		/* No.4 ���͋@���@ */
		strncat( aWrkBuf,p->sCtrlkka.bskgok,strlen(p->sCtrlkka.bskgok) );
		strcat( aWrkBuf,"," );
		/* No. 5 �����O���[�v�ݒ� */
		strncat( aWrkBuf,p->sCtrlkka.knsgrp,strlen(p->sCtrlkka.knsgrp) );
		strcat( aWrkBuf,"," );
		/* No. 6 ���ڃR�[�h */
		strncat( aWrkBuf,p->sCtrlkka.kmkcd,strlen(p->sCtrlkka.kmkcd) );
		strcat( aWrkBuf,"," );
		/* No. 7 �������ڃR�[�h */
		strncat( aWrkBuf,p->sCtrlkka.nbkmkcd,strlen(p->sCtrlkka.nbkmkcd) );
		strcat( aWrkBuf,"," );
		/* No. 8 �R���g���[��No�ݒ� */
#ifdef _DEBUG_
	printf( "OutputCtrlkka(%d) : p->sCtrlkka.ctrlno = %d\n", __LINE__, p->sCtrlkka.ctrlno );
#endif
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->sCtrlkka.ctrlno );
		strcat( aWrkBuf,"," );
		/* No. 9 �R���g���[����ʐݒ� */
		strncat( aWrkBuf,p->sCtrlkka.ctrlsbt,strlen(p->sCtrlkka.ctrlsbt) );
		strcat( aWrkBuf,"," );
		/* No.10 �R���g���[����ʎ}�Ԑݒ� */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->sCtrlkka.ctrlsbteda );
		strcat( aWrkBuf,"," );
		/* No.11 �R���g���[�����x���ݒ� */
		strncat( aWrkBuf,p->sCtrlkka.ctrllbl,strlen(p->sCtrlkka.ctrllbl) );
		strcat( aWrkBuf,"," );
		/* No.12 �萫�E��ʃt���O�ݒ� */
		if( p->sCtrlkka.tstrflg == 0 ) {
			p->sCtrlkka.tstrflg = ' ';
		}
		strncat( aWrkBuf,&(p->sCtrlkka.tstrflg),1 );
		strcat( aWrkBuf,"," );
		/* No.13 �A�b�Z�C���b�NID */
		strncat( aWrkBuf,p->sCtrlkka.asyrckid,strlen(p->sCtrlkka.asyrckid) );
		strcat( aWrkBuf,"," );
		/* No.14 �A�b�Z�C���b�N�|�W�V���� */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->sCtrlkka.asyrckpos );
		strcat( aWrkBuf,"," );
		/* No.15 ����SEQ�ݒ� */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->sCtrlkka.knsseq );
		strcat( aWrkBuf,"," );
		/* No.16 ���͋@SEQ�ݒ� */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->sCtrlkka.bskseq );
		strcat( aWrkBuf,"," );
		/* No.17 �����o�b�`No�ݒ� */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->sCtrlkka.bthno );
		strcat( aWrkBuf,"," );
		/* No.18 �����o�b�`�����b�N���Ԑݒ� */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->sCtrlkka.bthrckjbn );
		strcat( aWrkBuf,"," );
		/* No.19 ���򃍃b�gNo�ݒ� */
		strncat( aWrkBuf,p->sCtrlkka.syklotno,strlen(p->sCtrlkka.syklotno) );
		strcat( aWrkBuf,"," );
		/* No.20 ����l�ݒ� */
		strncat( aWrkBuf,p->sCtrlkka.sktti,strlen(p->sCtrlkka.sktti) );
		strcat( aWrkBuf,"," );
		/* No.21 ���Z�l�ݒ� */
		strncat( aWrkBuf,p->sCtrlkka.knzti,strlen(p->sCtrlkka.knzti) );
		strcat( aWrkBuf,"," );
		/* No.22 ���Z�l�ݒ�t���O�ݒ� */
		if( p->sCtrlkka.knztistflg == 0 ) {
			p->sCtrlkka.knztistflg = ' ';
		}
		strncat( aWrkBuf,&(p->sCtrlkka.knztistflg),1 );
		strcat( aWrkBuf,"," );
		/* No.23 ��������ݒ� */
		strncat( aWrkBuf,p->sCtrlkka.sktdh,strlen(p->sCtrlkka.sktdh) );
		strcat( aWrkBuf,"," );
		/* No.24 �R���g���[����Ԑݒ� */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->sCtrlkka.ctrljti );
		strcat( aWrkBuf,"," );
		/* No.25 �`�F�b�N�ς݃t���O�ݒ� */
		if( p->sCtrlkka.chkzmflg == 0 ) {
			p->sCtrlkka.chkzmflg = ' ';
		}
		strncat( aWrkBuf,&(p->sCtrlkka.chkzmflg),1 );
		strcat( aWrkBuf,"," );
		/* No.26 �t�@�N�^�[ */
		strncat( aWrkBuf,p->sCtrlkka.facter,strlen(p->sCtrlkka.facter) );
		strcat( aWrkBuf,"," );
		/* No.27 �x�[�X�ݒ� */
		strncat( aWrkBuf,p->sCtrlkka.base,strlen(p->sCtrlkka.base) );
		strcat( aWrkBuf,"," );
		/* No.28 �Z����Ԑݒ� */
		if( p->sCtrlkka.kosijt == 0 ) {
			p->sCtrlkka.kosijt = ' ';
		}
		strncat( aWrkBuf,&(p->sCtrlkka.kosijt),1 );
		strcat( aWrkBuf,"," );
		/* No.29 �Z���S���Ґݒ� */
		strncat( aWrkBuf,p->sCtrlkka.kositts,strlen(p->sCtrlkka.kositts) );
		strcat( aWrkBuf,"," );
		/* No.30 �Z������ */
		strncat( aWrkBuf,p->sCtrlkka.kosidh,strlen(p->sCtrlkka.kosidh) );
		strcat( aWrkBuf,"," );
		/* No.31 ���X�V���� */
		memset( cWrk, 0, sizeof(cWrk) );
		tm = localtime(&t);
		gettimeofday( &tv, NULL );
		sprintf( cWrk, "%ld", tv.tv_usec );
		sprintf( &aWrkBuf[strlen(aWrkBuf)], "%04d-%02d-%02d %02d:%02d:%02d", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec );

		iLen = strlen( aWrkBuf );
		aWrkBuf[iLen] = CR;

		iLen = strlen(aWrkBuf);
		for( iCnt=0; iCnt<iLen; iCnt++ ) {
			if( aWrkBuf[iCnt] == CR ){
				fprintf(fp,"%c",'\n');
				break;
			}
			fprintf(fp,"%c",aWrkBuf[iCnt]);
		}
//		fclose(fp);
//	}

	free( aWrkBuf );
	fclose(fp);
#if 0
	// Index�̍쐬
	memset( aWrkBuf2, 0, sizeof(aWrkBuf2) );
	strcpy( aWrkBuf2,aKekkaFolder );
	strcat( aWrkBuf2,"../Index/" );
	strcat( aWrkBuf2,"CT_" );
	strcat( aWrkBuf2,aFileNameStr );
	
	close(open(aWrkBuf2, O_CREAT, 0644));
#endif
	return RTN_OK;
}
