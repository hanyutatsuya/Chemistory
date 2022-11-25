/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FOutputKekka.c                                                */
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
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

//#include "DD41399.h"
#include "OutputKekka.h"

/******************************************************************************/
/*  �֐��錾                                                                  */
/******************************************************************************/
int OutputKekka(SOCKET_INF*);			/* ���ʏ��o�͏��� */

/******************************************************************************/
/*  �� �� ���@�FOutputKekka()  			     				     			  */
/*  �@�\�T�v�@�F���ʏ��o��												  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �FSOCKET_INF*		���͋@���                         		      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F RTN_OK		: ����											  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
int OutputKekka( SOCKET_INF* p )
{
	int iCnt;
	int iCnt2;
	int iLen;
//	char aWrkBuf[1024];
	char* aWrkBuf;
	char aWrkBuf2[255];
	FILE *fp;
	time_t t = time(NULL);
	struct tm* tm;
	struct timeval tv;
	//char cWrk[30];
	char cWrk[30];
//	char aFunc[32];

	//memcpy(aFunc,__func__,sizeof(aFunc));
//	SetLogDat(TRCKIND_TRACE,aFunc,"xxx","xxx","xxx","xxx","xxx");
//	ZbmlPutLog(&sLog);

	printf( "OutputKekka()\n" );

	memset( cWrk,0,sizeof(cWrk) );
	if( (p->cRackNum[0] >= 0x30) && (p->cRackNum[0] <= 0x39) ) {
		sprintf( cWrk,"%d",atoi(p->cRackNum) );
	} else {
		strcpy( cWrk,p->cRackNum );
	}

//	MakeFileName( p->cRackNum, p->cRackPosNum );
	MakeFileName( cWrk, p->cRackPosNum, 1 );

//	memset( aWrkBuf2, 0, sizeof(aWrkBuf2) );
//	strcpy( aWrkBuf2,aKekkaFolder );
//	strcat( aWrkBuf2,aFileNameStr );

	// �t�@�C���̑��݊m�F
	int loopCnt = 0;
	int	len = strlen(aFileNameStr) - 3;
	while (1) {
		struct stat	fst;

		memset( aWrkBuf2, 0, sizeof(aWrkBuf2) );
		strcpy( aWrkBuf2,aKekkaFolder );
		strcat( aWrkBuf2,aFileNameStr );

		if (stat(aWrkBuf2, &fst) == 0) {
			loopCnt++;
			aFileNameStr[len+0] = '\0';
			aFileNameStr[len+1] = '\0';
			aFileNameStr[len+0] = ((loopCnt > 9) ? 'A' : '0') + loopCnt;
			strcat( aFileNameStr,".dat" );
		}
		else {
			break;
		}
	}

	aWrkBuf = malloc(sizeof(char)*1024);

	printf( "OutputKekka(%s)\n",aWrkBuf2 );
	fp = fopen( aWrkBuf2,"a");
	if( fp == NULL ) {
		sFncSyslog ( TRCKIND_ERROR, "OutputKekka()", "�t�@�C���̃I�[�v���Ɏ��s���܂����B" ) ;
		printf("�t�@�C���̃I�[�v���Ɏ��s���܂����B\n");
		return RTN_NG;
	}

	// �R���g���[���ԍ��̊m�F�i��ԏ������l��T���j
	int ctrlNo = 99999999;
	for( iCnt2=0; iCnt2<p->iKekkaNum; iCnt2++ ) {
#ifdef _DEBUG_
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].kmkcd  = %s\n", __LINE__, p->pKekka[iCnt2].kmkcd );
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].ctrlno = %d\n", __LINE__, p->pKekka[iCnt2].ctrlno );
#endif
		if (p->pKekka[iCnt2].knsflg == 'H') continue;
		if (p->pKekka[iCnt2].ctrlno < ctrlNo) {
			ctrlNo = p->pKekka[iCnt2].ctrlno;
#ifdef _DEBUG_
		printf( "OutputKekka(%d) :     p->pKekka[iCnt2].kmkcd = %s\n", __LINE__, p->pKekka[iCnt2].kmkcd );
		printf( "OutputKekka(%d) :     ctrlNo                 = %d\n", __LINE__, ctrlNo );
#endif
		}
	}
	// �R���g���[���ԍ��̍Đݒ�
	for( iCnt2=0; iCnt2<p->iKekkaNum; iCnt2++ ) {
#ifdef _DEBUG_
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].kmkcd    = %s\n", __LINE__, p->pKekka[iCnt2].kmkcd );
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].ctrlno 1 = %d\n", __LINE__, p->pKekka[iCnt2].ctrlno );
#endif
		p->pKekka[iCnt2].ctrlno = ctrlNo;
#ifdef _DEBUG_
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].ctrlno 2 = %d\n", __LINE__, p->pKekka[iCnt2].ctrlno );
#endif
	}


	for( iCnt2=0; iCnt2<p->iKekkaNum; iCnt2++ ) {
		memset( aWrkBuf, 0, 1024 );
		/* No. 1 �����J�n���ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].knskisymd,strlen(p->pKekka[iCnt2].knskisymd) );
		strcat( aWrkBuf,"," );
		/* No. 2 �������擾 */
		strncat( aWrkBuf,p->pKekka[iCnt2].sriymd,strlen(p->pKekka[iCnt2].sriymd) );
		strcat( aWrkBuf,"," );
		/* No. 3 ����No�擾 */
		strncat( aWrkBuf,p->pKekka[iCnt2].kntno,strlen(p->pKekka[iCnt2].kntno) );
		strcat( aWrkBuf,"," );
		/* No. 4 ����No�����t���O�擾 */
		if( p->pKekka[iCnt2].kntketflg == 0 ) {
			p->pKekka[iCnt2].kntketflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].kntketflg),1 );
		strcat( aWrkBuf,"," );
		/* No. 5 �����O���[�v�ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].knsgrp,strlen(p->pKekka[iCnt2].knsgrp) );
		strcat( aWrkBuf,"," );
		/* No. 6 ���ڃR�[�h */
		strncat( aWrkBuf,p->pKekka[iCnt2].kmkcd,strlen(p->pKekka[iCnt2].kmkcd) );
		strcat( aWrkBuf,"," );
		/* No. 7 �����񐔐ݒ� */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->pKekka[iCnt2].knssu );
		strcat( aWrkBuf,"," );
		/* No. 8 �����񐔎}�Ԑݒ� */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->pKekka[iCnt2].knssueda );
		strcat( aWrkBuf,"," );
		/* No. 9 �˗��������敪�ݒ� */
		if( p->pKekka[iCnt2].irihsmkbn == 0 ) {
			p->pKekka[iCnt2].irihsmkbn = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].irihsmkbn),1 );
		strcat( aWrkBuf,"," );
		/* No.10 �˗��敪�ݒ� */
		if( p->pKekka[iCnt2].irikbn == 0 ) {
			p->pKekka[iCnt2].irikbn = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].irikbn),1 );
		strcat( aWrkBuf,"," );
		/* No.11 �����H���敪�ݒ� */
		if( p->pKekka[iCnt2].ksktkbn == 0 ) {
			p->pKekka[iCnt2].ksktkbn = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].ksktkbn),1 );
		strcat( aWrkBuf,"," );
		/* No.12 BML��t�N�����ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].utkymd,strlen(p->pKekka[iCnt2].utkymd) );
		strcat( aWrkBuf,"," );
		/* No.13 �˗���No�ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].irino,strlen(p->pKekka[iCnt2].irino) );
		strcat( aWrkBuf,"," );
		/* No.14 �˗���No�����t���O�ݒ� */
		if( p->pKekka[iCnt2].iriketflg == 0 ) {
			p->pKekka[iCnt2].iriketflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].iriketflg),1 );
		strcat( aWrkBuf,"," );
		/* No.15 ��������No�ݒ� */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->pKekka[iCnt2].zssdino );
		strcat( aWrkBuf,"," );
		/* No.16 �{�݃R�[�h�ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].sstcd,strlen(p->pKekka[iCnt2].sstcd) );
		strcat( aWrkBuf,"," );
		/* No.17 �g���[ID�ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].trid,strlen(p->pKekka[iCnt2].trid) );
		strcat( aWrkBuf,"," );
		/* No.18 �g���[�|�W�V�����ݒ� */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->pKekka[iCnt2].trpos );
		strcat( aWrkBuf,"," );
		/* No.19 �A�b�Z�C���b�NID */
		strncat( aWrkBuf,p->pKekka[iCnt2].asyrckid,strlen(p->pKekka[iCnt2].asyrckid) );
		strcat( aWrkBuf,"," );
		/* No.20 �A�b�Z�C���b�N�|�W�V���� */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->pKekka[iCnt2].asyrckpos );
		strcat( aWrkBuf,"," );
		/* No.21 �e���ڃR�[�h�ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].oyakmkcd,strlen(p->pKekka[iCnt2].oyakmkcd) );
		strcat( aWrkBuf,"," );
		/* No.22 �Z�N�V�����R�[�h�ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].seccd,strlen(p->pKekka[iCnt2].seccd) );
		strcat( aWrkBuf,"," );
		/* No.23 ���敉�׋敪�ݒ� */
		if( p->pKekka[iCnt2].bkfkkbn == 0 ) {
			p->pKekka[iCnt2].bkfkkbn = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].bkfkkbn),1 );
		strcat( aWrkBuf,"," );
		/* No.24 �T���v�����O�R�[�h�ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].smpcd,strlen(p->pKekka[iCnt2].smpcd) );
		strcat( aWrkBuf,"," );
		/* No.25 ���͋@�敪�ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].bskkbn,strlen(p->pKekka[iCnt2].bskkbn) );
		strcat( aWrkBuf,"," );
		/* No.26 ���͋@���C���ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].bsklne,strlen(p->pKekka[iCnt2].bsklne) );
		strcat( aWrkBuf,"," );
		/* No.27 ���͋@���@ */
		strncat( aWrkBuf,p->pKekka[iCnt2].bskgok,strlen(p->pKekka[iCnt2].bskgok) );
		strcat( aWrkBuf,"," );
		/* No.28 ���͋@SEQ */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->pKekka[iCnt2].bskseq );
		strcat( aWrkBuf,"," );
		/* No.29 ���͋@�G���[�X�e�[�^�X */
		strncat( aWrkBuf,p->pKekka[iCnt2].bskerrsts,strlen(p->pKekka[iCnt2].bskerrsts) );
		strcat( aWrkBuf,"," );
		/* No.30 ������� */
		strncat( aWrkBuf,p->pKekka[iCnt2].sktdh,strlen(p->pKekka[iCnt2].sktdh) );
		strcat( aWrkBuf,"," );
		/* No.31 �������ڃR�[�h�ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].nbkmkcd,strlen(p->pKekka[iCnt2].nbkmkcd) );
		strcat( aWrkBuf,"," );
		/* No.32 �萫�E��ʃt���O�ݒ� */
		if( p->pKekka[iCnt2].tstrflg == 0 ) {
			p->pKekka[iCnt2].tstrflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].tstrflg),1 );
		strcat( aWrkBuf,"," );
		/* No.33 �ޗ��R�[�h�ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].zrcd,strlen(p->pKekka[iCnt2].zrcd) );
		strcat( aWrkBuf,"," );
		/* No.34 �D�惌�x���擾 */
		strncat( aWrkBuf,p->pKekka[iCnt2].ysnlbl,strlen(p->pKekka[iCnt2].ysnlbl) );
		strcat( aWrkBuf,"," );
		/* No.35 ��lNO�擾 */
		strncat( aWrkBuf,p->pKekka[iCnt2].kjno,strlen(p->pKekka[iCnt2].kjno) );
		strcat( aWrkBuf,"," );
		/* No.36 ���ו�NO�\���敪�擾 */
		if( p->pKekka[iCnt2].fkhkknohjkbn == 0 ) {
			p->pKekka[iCnt2].fkhkknohjkbn = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].fkhkknohjkbn),1 );
		strcat( aWrkBuf,"," );
		/* No.37 ���ʊ�lNO�擾 */
		strncat( aWrkBuf,p->pKekka[iCnt2].tbkjno,strlen(p->pKekka[iCnt2].tbkjno) );
		strcat( aWrkBuf,"," );
		/* No.38 ���ʊ�l�t���O�擾 */
		if( p->pKekka[iCnt2].tbkjflg == 0 ) {
			p->pKekka[iCnt2].tbkjflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].tbkjflg),1 );
		strcat( aWrkBuf,"," );
		/* No.39 ���^�t�����Ԏ擾 */
		strncat( aWrkBuf,p->pKekka[iCnt2].htkfkhms,strlen(p->pKekka[iCnt2].htkfkhms) );
		strcat( aWrkBuf,"," );
		/* No.40 �W���t���O�擾 */
		if( p->pKekka[iCnt2].skflg == 0 ) {
			p->pKekka[iCnt2].skflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].skflg),1 );
		strcat( aWrkBuf,"," );
		/* No.41 ���܃t���O�擾 */
		strncat( aWrkBuf,p->pKekka[iCnt2].tskflg,strlen(p->pKekka[iCnt2].tskflg) );
		strcat( aWrkBuf,"," );
		/* No.42 �����t���O�擾 */
		strncat( aWrkBuf,p->pKekka[iCnt2].tktflg,strlen(p->pKekka[iCnt2].tktflg) );
		strcat( aWrkBuf,"," );
		/* No.43���{��ߔ{�� */
		strncat( aWrkBuf,p->pKekka[iCnt2].jisksbr,strlen(p->pKekka[iCnt2].jisksbr) );
		strcat( aWrkBuf,"," );
		/* No.44 �ً}�񍐃t���O�ݒ� */
		if( p->pKekka[iCnt2].kkflg == 0 ) {
			p->pKekka[iCnt2].kkflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].kkflg),1 );
		strcat( aWrkBuf,"," );
		/* No.45 �ً}�˗��t���O�ݒ� */
		if( p->pKekka[iCnt2].kkiriflg == 0 ) {
			p->pKekka[iCnt2].kkiriflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].kkiriflg),1 );
		strcat( aWrkBuf,"," );
		/* No.46 �ً}�˗����b�gNo�ݒ� */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->pKekka[iCnt2].kkirilotno );
		strcat( aWrkBuf,"," );
		/* No.47 ��Ɖ�t���O�ݒ� */
		if( p->pKekka[iCnt2].hsykflg == 0 ) {
			p->pKekka[iCnt2].hsykflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].hsykflg),1 );
		strcat( aWrkBuf,"," );
		/* No.48 �񐿋��t���O�ݒ� */
		if( p->pKekka[iCnt2].hskflg == 0 ) {
			p->pKekka[iCnt2].hskflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].hskflg),1 );
		strcat( aWrkBuf,"," );
		/* No.49 ��񍐃t���O�ݒ� */
		if( p->pKekka[iCnt2].hhkkflg == 0 ) {
			p->pKekka[iCnt2].hhkkflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].hhkkflg),1 );
		strcat( aWrkBuf,"," );
		/* No.50 ���f�[�^�ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].rawdata,strlen(p->pKekka[iCnt2].rawdata) );
		strcat( aWrkBuf,"," );
		/* No.51 �������ʂP�ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].knskka1,strlen(p->pKekka[iCnt2].knskka1) );
		strcat( aWrkBuf,"," );
		/* No.52 �������ʂQ�ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].knskka2,strlen(p->pKekka[iCnt2].knskka2) );
		strcat( aWrkBuf,"," );
		/* No.53 */
		strcat( aWrkBuf,"," );
		/* No.54 �������ʕ⑫�ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].kkahskcd,strlen(p->pKekka[iCnt2].kkahskcd) );
		strcat( aWrkBuf,"," );
		/* No.55 �\�����ʐݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].hjkka,strlen(p->pKekka[iCnt2].hjkka) );
		strcat( aWrkBuf,"," );
		/* No.56 �w���iSDI�j�ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].sdi,strlen(p->pKekka[iCnt2].sdi) );
		strcat( aWrkBuf,"," );
		/* No.57 ���ʃR�����g�P�ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].kkacmt1,strlen(p->pKekka[iCnt2].kkacmt1) );
		strcat( aWrkBuf,"," );
		/* No.58 ���ʃR�����g�Q�ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].kkacmt2,strlen(p->pKekka[iCnt2].kkacmt2) );
		strcat( aWrkBuf,"," );
		/* No.59 ���ʏ󋵃R�[�h�ݒ� */
		if( p->pKekka[iCnt2].kkajkcd == 0 ) {
			p->pKekka[iCnt2].kkajkcd = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].kkajkcd),1 );
		strcat( aWrkBuf,"," );
		/* No.60 �p�j�b�N�����W�t���O�ݒ� */
		if( p->pKekka[iCnt2].pncrgflg == 0 ) {
			p->pKekka[iCnt2].pncrgflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].pncrgflg),1 );
		strcat( aWrkBuf,"," );
		/* No.61 �������p�j�b�N�����W�t���O�ݒ� */
		if( p->pKekka[iCnt2].knspncrgflg == 0 ) {
			p->pKekka[iCnt2].knspncrgflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].knspncrgflg),1 );
		strcat( aWrkBuf,"," );
		/* No.62 ���ʊ��Z�t���O�ݒ� */
		if( p->pKekka[iCnt2].kkaksflg == 0 ) {
			p->pKekka[iCnt2].kkaksflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].kkaksflg),1 );
		strcat( aWrkBuf,"," );
		/* No.63 ���ʏC���t���O�ݒ� */
		if( p->pKekka[iCnt2].kkassflg == 0 ) {
			p->pKekka[iCnt2].kkassflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].kkassflg),1 );
		strcat( aWrkBuf,"," );
		/* No.64 �ُ�l�敪(�j)�ݒ� */
		if( p->pKekka[iCnt2].ijkbnm == 0 ) {
			p->pKekka[iCnt2].ijkbnm = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].ijkbnm),1 );
		strcat( aWrkBuf,"," );
		/* No.65 �ُ�l�敪(��)�ݒ� */
		if( p->pKekka[iCnt2].ijkbnf == 0 ) {
			p->pKekka[iCnt2].ijkbnf = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].ijkbnf),1 );
		strcat( aWrkBuf,"," );
		/* No.66 �ُ�l�敪(�s��)�ݒ� */
		if( p->pKekka[iCnt2].ijkbnn == 0 ) {
			p->pKekka[iCnt2].ijkbnn = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].ijkbnn),1 );
		strcat( aWrkBuf,"," );
		/* No.67 ���ʈُ�l�敪(�j)�ݒ� */
		if( p->pKekka[iCnt2].tbijkbnm == 0 ) {
			p->pKekka[iCnt2].tbijkbnm = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].tbijkbnm),1 );
		strcat( aWrkBuf,"," );
		/* No.68 ���ʈُ�l�敪(��)�ݒ� */
		if( p->pKekka[iCnt2].tbijkbnf == 0 ) {
			p->pKekka[iCnt2].tbijkbnf = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].tbijkbnf),1 );
		strcat( aWrkBuf,"," );
		/* No.69 ���ʈُ�l�敪(�s��)�ݒ� */
		if( p->pKekka[iCnt2].tbijkbnn == 0 ) {
			p->pKekka[iCnt2].tbijkbnn = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].tbijkbnn),1 );
		strcat( aWrkBuf,"," );
		/* No.70 �������(����)���x���ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].nbdolbl,strlen(p->pKekka[iCnt2].nbdolbl) );
		strcat( aWrkBuf,"," );
		/* No.71 �������(����)�G���[�X�e�[�^�X�ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].nbdoerr,strlen(p->pKekka[iCnt2].nbdoerr) );
		strcat( aWrkBuf,"," );
		/* No.72 �������(�n��)���x���ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].ykdolbl,strlen(p->pKekka[iCnt2].ykdolbl) );
		strcat( aWrkBuf,"," );
		/* No.73 �������(�n��)�G���[�X�e�[�^�X�ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].ykdoerr,strlen(p->pKekka[iCnt2].ykdoerr) );
		strcat( aWrkBuf,"," );
		/* No.74 �������(etc)���x���ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].etclbl,strlen(p->pKekka[iCnt2].etclbl) );
		strcat( aWrkBuf,"," );
		/* No.75 �������(etc)�G���[�X�e�[�^�X�ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].etcerr,strlen(p->pKekka[iCnt2].etcerr) );
		strcat( aWrkBuf,"," );
		/* No.76 �R���g���[��No */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->pKekka[iCnt2].ctrlno );
#ifdef _DEBUG_
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].kntno     = %s\n", __LINE__, p->pKekka[iCnt2].kntno );
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].knsgrp    = %s\n", __LINE__, p->pKekka[iCnt2].knsgrp );
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].kmkcd     = %s\n", __LINE__, p->pKekka[iCnt2].kmkcd );
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].knssu     = %d\n", __LINE__, p->pKekka[iCnt2].knssu );
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].irino     = %s\n", __LINE__, p->pKekka[iCnt2].irino );
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].asyrckid  = %s\n", __LINE__, p->pKekka[iCnt2].asyrckid );
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].asyrckpos = %d\n", __LINE__, p->pKekka[iCnt2].asyrckpos );
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].bskgok    = %s\n", __LINE__, p->pKekka[iCnt2].bskgok );
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].rawdata   = %s\n", __LINE__, p->pKekka[iCnt2].rawdata );
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].ctrlno    = %d\n", __LINE__, p->pKekka[iCnt2].ctrlno );
#endif
		strcat( aWrkBuf,"," );
		/* No. 77 ����SEQ�ݒ� */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->pKekka[iCnt2].knsseq );
		strcat( aWrkBuf,"," );
		/* No. 78 �����o�b�`No�ݒ� */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->pKekka[iCnt2].bthno );
		strcat( aWrkBuf,"," );
		/* No. 79 �v���b�gNo�ݒ� */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->pKekka[iCnt2].pltno );
#ifdef _DEBUG_
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].pltno     = %d\n", __LINE__, p->pKekka[iCnt2].pltno );
#endif
		strcat( aWrkBuf,"," );
		/* No. 80 �v���b�gSEQ�ݒ� */
		sprintf( &aWrkBuf[strlen(aWrkBuf)],"%d",p->pKekka[iCnt2].pltseq );
#ifdef _DEBUG_
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].pltseq    = %d\n", __LINE__, p->pKekka[iCnt2].pltseq );
#endif
		strcat( aWrkBuf,"," );
		/* No. 81 �f�[�^���͒S���Ґݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].dtnrtts,strlen(p->pKekka[iCnt2].dtnrtts) );
		strcat( aWrkBuf,"," );
		/* No. 82 �f�[�^���͓����ݒ� */
/* [ start 060420 */
//		strncat( aWrkBuf,p->pKekka[iCnt2].dtnrdh,strlen(p->pKekka[iCnt2].dtnrdh) );
//		memset( cWrk, 0, sizeof(cWrk) );
		tm = localtime(&t);
		gettimeofday( &tv, NULL );
//		sprintf( cWrk, "%d", tv.tv_usec );
		sprintf( &aWrkBuf[strlen(aWrkBuf)], "%04d-%02d-%02d %02d:%02d:%02d", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec );
/* ] end 060420 */
		strcat( aWrkBuf,"," );
		/* No. 83 �������������ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].knskrdh,strlen(p->pKekka[iCnt2].knskrdh) );
		strcat( aWrkBuf,"," );
		/* No. 84 �񍐓����ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].hkkdh,strlen(p->pKekka[iCnt2].hkkdh) );
		strcat( aWrkBuf,"," );
		/* No. 85 �񍐊�]���Ԑݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].hkkkbdh,strlen(p->pKekka[iCnt2].hkkkbdh) );
		strcat( aWrkBuf,"," );
		/* No. 86 ����񍐗\����ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].zkhkkyymd,strlen(p->pKekka[iCnt2].zkhkkyymd) );
		strcat( aWrkBuf,"," );
		/* No. 87 ����񍐗\�莞���ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].zkhkkytme,strlen(p->pKekka[iCnt2].zkhkkytme) );
		strcat( aWrkBuf,"," );
		/* No. 88 �t���[���ʃt���O�ݒ� */
		if( p->pKekka[iCnt2].frkkaflg == 0 ) {
			p->pKekka[iCnt2].frkkaflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].frkkaflg),1 );
		strcat( aWrkBuf,"," );
		/* No. 89 �摜�ʎ��t���O�ݒ� */
		if( p->pKekka[iCnt2].gzbsflg == 0 ) {
			p->pKekka[iCnt2].gzbsflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].gzbsflg),1 );
		strcat( aWrkBuf,"," );
		/* No. 90 �␳�t���O�ݒ� */
		if( p->pKekka[iCnt2].hsiflg == 0 ) {
			p->pKekka[iCnt2].hsiflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].hsiflg),1 );
		strcat( aWrkBuf,"," );
		/* No. 91 ���ʗD��t���O�ݒ� */
		if( p->pKekka[iCnt2].kkaysnflg == 0 ) {
			p->pKekka[iCnt2].kkaysnflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].kkaysnflg),1 );
		strcat( aWrkBuf,"," );
		/* No. 92 ����̓t���O�ݒ� */
		if( p->pKekka[iCnt2].tnyrkflg == 0 ) {
			p->pKekka[iCnt2].tnyrkflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].tnyrkflg),1 );
		strcat( aWrkBuf,"," );
		/* No. 93 �̗p�t���O�ݒ� */
		if( p->pKekka[iCnt2].siyflg == 0 ) {
			p->pKekka[iCnt2].siyflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].siyflg),1 );
		strcat( aWrkBuf,"," );
		/* No. 94 �����t���O�ݒ� */
		if( p->pKekka[iCnt2].knsflg == 0 ) {
			p->pKekka[iCnt2].knsflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].knsflg),1 );
		strcat( aWrkBuf,"," );
		/* No. 95 �Č��t���O01(�����W�`�F�b�N)�ݒ� */
		if( p->pKekka[iCnt2].renjicflg == 0 ) {
			p->pKekka[iCnt2].renjicflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].renjicflg),1 );
		strcat( aWrkBuf,"," );
		/* No. 96 �Č��t���O02(���փ`�F�b�N)�ݒ� */
		if( p->pKekka[iCnt2].soukn1flg == 0 ) {
			p->pKekka[iCnt2].soukn1flg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].soukn1flg),1 );
		strcat( aWrkBuf,"," );
		/* No. 97 �Č��t���O03(�֘A�`�F�b�N)�ݒ� */
		if( p->pKekka[iCnt2].kanrenflg == 0 ) {
			p->pKekka[iCnt2].kanrenflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].kanrenflg),1 );
		strcat( aWrkBuf,"," );
		/* No. 98 �Č��t���O04(����`�F�b�N)�ݒ� */
		if( p->pKekka[iCnt2].bunkkuflg == 0 ) {
			p->pKekka[iCnt2].bunkkuflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].bunkkuflg),1 );
		strcat( aWrkBuf,"," );
		/* No. 99 �Č��t���O05(���сE�n���`�F�b�N)�ݒ� */
		if( p->pKekka[iCnt2].kesseiflg == 0 ) {
			p->pKekka[iCnt2].kesseiflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].kesseiflg),1 );
		strcat( aWrkBuf,"," );
		/* No.100 �Č��t���O06(�����`�F�b�N)�ݒ� */
		if( p->pKekka[iCnt2].rirekiflg == 0 ) {
			p->pKekka[iCnt2].rirekiflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].rirekiflg),1 );
		strcat( aWrkBuf,"," );
		/* No.101 �Č��t���O07(�ƍ��`�F�b�N)�ݒ� */
		if( p->pKekka[iCnt2].syougoflg == 0 ) {
			p->pKekka[iCnt2].syougoflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].syougoflg),1 );
		strcat( aWrkBuf,"," );
		/* No.102 �Č��t���O08(�v�Z�`�F�b�N)�ݒ� */
		if( p->pKekka[iCnt2].keisanflg == 0 ) {
			p->pKekka[iCnt2].keisanflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].keisanflg),1 );
		strcat( aWrkBuf,"," );
		/* No.103 �Č��t���O09(�P�O�O���`�F�b�N)�ݒ� */
		if( p->pKekka[iCnt2].per100flg == 0 ) {
			p->pKekka[iCnt2].per100flg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].per100flg),1 );
		strcat( aWrkBuf,"," );
		/* No.104 �Č��t���O10(���͑O��`�F�b�N)�ݒ� */
		if( p->pKekka[iCnt2].tousekflg == 0 ) {
			p->pKekka[iCnt2].tousekflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].tousekflg),1 );
		strcat( aWrkBuf,"," );
		/* No.105 �Č��t���O11(��ߍČ��`�F�b�N)�ݒ� */
		if( p->pKekka[iCnt2].kisyakflg == 0 ) {
			p->pKekka[iCnt2].kisyakflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].kisyakflg),1 );
		strcat( aWrkBuf,"," );
		/* No.106 �Č��t���O12(�Z������)�ݒ� */
		if( p->pKekka[iCnt2].kouseiflg == 0 ) {
			p->pKekka[iCnt2].kouseiflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].kouseiflg),1 );
		strcat( aWrkBuf,"," );
		/* No.107 �Č��t���O13(�ƍ�NG�m�菈��)�ݒ� */
		if( p->pKekka[iCnt2].syoungflg == 0 ) {
			p->pKekka[iCnt2].syoungflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].syoungflg),1 );
		strcat( aWrkBuf,"," );
		/* No.108 �Č��t���O14(���փ`�F�b�N(WS��))�ݒ� */
		if( p->pKekka[iCnt2].soukn2flg == 0 ) {
			p->pKekka[iCnt2].soukn2flg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].soukn2flg),1 );
		strcat( aWrkBuf,"," );
		/* No.109 �Č��t���O15(���׃p�^�[���`�F�b�N)�ݒ� */
		if( p->pKekka[iCnt2].fukaptflg == 0 ) {
			p->pKekka[iCnt2].fukaptflg = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].fukaptflg),1 );
		strcat( aWrkBuf,"," );
		/* No.110 �Č��t���O16(�`�F�b�N��ԃt���O01)�ݒ� */
		if( p->pKekka[iCnt2].yobiflg01 == 0 ) {
			p->pKekka[iCnt2].yobiflg01 = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].yobiflg01),1 );
		strcat( aWrkBuf,"," );
		/* No.111 �Č��t���O17(�`�F�b�N��ԃt���O02)�ݒ� */
		if( p->pKekka[iCnt2].tobiflg02 == 0 ) {
			p->pKekka[iCnt2].tobiflg02 = ' ';
		}
#ifdef _DEBUG_
		printf( "OutputKekka(%d) : p->pKekka[iCnt2].tobiflg02 = %c\n", __LINE__, p->pKekka[iCnt2].tobiflg02 );
#endif
		strncat( aWrkBuf,&(p->pKekka[iCnt2].tobiflg02),1 );
		strcat( aWrkBuf,"," );
		/* No.112 �Č��t���O18(�`�F�b�N��ԃt���O03)�ݒ� */
		if( p->pKekka[iCnt2].yobiflg03 == 0 ) {
			p->pKekka[iCnt2].yobiflg03 = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].yobiflg03),1 );
		strcat( aWrkBuf,"," );
		/* No.113 �Č��t���O19(�`�F�b�N��ԃt���O04)�ݒ� */
		if( p->pKekka[iCnt2].yobiflg04 == 0 ) {
			p->pKekka[iCnt2].yobiflg04 = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].yobiflg04),1 );
		strcat( aWrkBuf,"," );
		/* No.114 �Č��t���O20(�`�F�b�N��ԃt���O05)�ݒ� */
		if( p->pKekka[iCnt2].yobiflg05 == 0 ) {
			p->pKekka[iCnt2].yobiflg05 = ' ';
		}
		strncat( aWrkBuf,&(p->pKekka[iCnt2].yobiflg05),1 );
		strcat( aWrkBuf,"," );
		/* No.115 �Č����R�R�[�h�`�ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].skrycda,strlen(p->pKekka[iCnt2].skrycda) );
		strcat( aWrkBuf,"," );
		/* No.116 �Č����R�R�[�h�a�ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].skrycdb,strlen(p->pKekka[iCnt2].skrycdb) );
		strcat( aWrkBuf,"," );
		/* No.117 �Č����R�R�[�h�b�ݒ� */
		strncat( aWrkBuf,p->pKekka[iCnt2].skrycdc,strlen(p->pKekka[iCnt2].skrycdc) );
		strcat( aWrkBuf,"," );
		/* No.118 ���X�V����  */
/* [ start 060420 */
//		memset( cWrk, 0, sizeof(cWrk) );
//		tm = localtime(&t);
//		gettimeofday( &tv, NULL );
//		sprintf( cWrk, "%d", tv.tv_usec );
/* ] end 060420 */

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
	}
	
	fclose(fp);
	free( aWrkBuf );

	// Index�̍쐬
	memset( aWrkBuf2, 0, sizeof(aWrkBuf2) );
	strcpy( aWrkBuf2,aKekkaFolder );
	strcat( aWrkBuf2,"../Index/" );
	strcat( aWrkBuf2,aFileNameStr );
	
	close(open(aWrkBuf2, O_CREAT, 0644));
	
	return RTN_OK;
}
