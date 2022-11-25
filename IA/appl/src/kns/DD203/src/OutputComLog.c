/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FOutputComLog.c                                               */
/* �@�T�@�@�@�v�F�ʐM���O�o��       	                                      */
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
#include "OutputComLog.h"

/******************************************************************************/
/*  �֐��錾                                                                  */
/******************************************************************************/

int OutputComLog(SOCKET_INF*,int,char*);	/* �ʐM���O�o�͏���*/
/******************************************************************************/
/*  �� �� ���@�FOutputComLog()  			     							  */
/*  �@�\�T�v�@�F�ʐM���O�o��												  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �FSOCKET_INF*		���͋@���                         		      */
/*�@ ��Q���� �Fint             �ʐM����      					 		      */
/*�@ ��R���� �Fchar*           ���M�f�[�^�o�b�t�@   			 		      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F RTN_OK		: ����											  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
int OutputComLog(SOCKET_INF* p,int iDir, char* aWrkBuf)
{
	int iWrk;
	int iCnt;
	FILE *fp;
	char aFunc[32];

	memcpy(aFunc,__func__,sizeof(aFunc));
//	SetLogDat(TRCKIND_TRACE,aFunc,"xxx","xxx","xxx","xxx","xxx");
//	ZbmlPutLog(&sLog);

	time_t t = time(NULL);
//	time_t t2;
	struct tm* tm;
//	struct tm* tm2;
	struct timeval tv;
	char cWrk[256];

	memset( cWrk, 0, sizeof(cWrk) );

//	printf("%d.%d\n", tv.tv_sec, tv.tv_usec );

//	printf("OutputComLog()\n");
	strcpy( cWrk,aLogOutFolder );
	strcat( cWrk, "com_" );
	strcat( cWrk,p->aGouki );
	strcat( cWrk, ".log" );

//	fp = fopen("lst008log.dat","a");
	fp = fopen(cWrk,"a");
	if( fp == NULL ) {
		printf("�t�@�C���̃I�[�v���Ɏ��s���܂����B\n");
		sFncSyslog ( TRCKIND_ERROR, "OutputComLog()", "�t�@�C���̃I�[�v���Ɏ��s���܂����B" ) ;
		return RTN_NG;
	} else {

//	printf("%s\n", ctime(&t) );
	tm = localtime(&t);
	gettimeofday( &tv, NULL );
//	tm = localtime((time_t *)&(tv->tv_sec));
	sprintf( cWrk, "%06ld", tv.tv_usec );
//	fprintf(fp, "%04d/%02d/%02d %02d:%02d:%02d.%d\n", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, tv.tv_usec );
	fprintf(fp, "%04d/%02d/%02d %02d:%02d:%02d.%c%c%c\n", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, cWrk[0], cWrk[1], cWrk[2] );
//	printf("%04d/%02d/%02d %02d:%02d:%02d\n", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec );

//    getchar();	


//	t2 = time(NULL);	
//	tm2 = localtime(&t2);
//	printf("%04d/%02d/%02d %02d:%02d:%02d\n", tm2->tm_year+1900, tm2->tm_mon+1, tm2->tm_mday, tm2->tm_hour, tm2->tm_min, tm2->tm_sec );


//	printf("����%f\n", difftime(t2,t));

		memset( cWrk, 0, sizeof(cWrk) );

		if( iDir == RCV_LOG ) {
			strcpy( cWrk, "BUNSEKI_" );
		} else {
			strcpy( cWrk, "HOST_" );
		}
		iWrk = strlen( cWrk );
//		strcpy( &cWrk[iWrk],p->aHostName );
		strcpy( &cWrk[iWrk],p->aGouki );
		iWrk = strlen( cWrk );
		cWrk[iWrk] = '(';
//		strcpy( &cWrk[iWrk+1],p->aHostName );
		sprintf( &cWrk[iWrk+1],"%d",p->iPortNum );
		iWrk = strlen( cWrk );
		cWrk[iWrk] = ')';

		switch( aWrkBuf[0] ) {
		case ENQ:
			strcat( cWrk, ":<ENQ>" );
			fprintf(fp,"%s",cWrk);
			break;
		case ACK:
			strcat( cWrk, ":<ACK>" );
			fprintf(fp,"%s",cWrk);
			break;
		case STX:
			strcat( cWrk, ":<STX>" );
			fprintf(fp,"%s",cWrk);
			break;
		case NAK:
			strcat( cWrk, ":<NAK>" );
			fprintf(fp,"%s",cWrk);
			break;
		case EOT:
			strcat( cWrk, ":<EOT>" );
			fprintf(fp,"%s",cWrk);
			break;
		case DC1:
			strcat( cWrk, ":<DC1>" );
			fprintf(fp,"%s",cWrk);
			break;
		default:
//			fclose(fp);
//			return 0;
			break;
		}
		iWrk = strlen(aWrkBuf);
		fprintf(fp,"\n");
		for( iCnt=1; iCnt<iWrk; iCnt++ ) {
			if( aWrkBuf[iCnt] == CR ){
				fprintf(fp,"%s","<CR>");
				if( (aWrkBuf[iCnt+1] != ETB) && (aWrkBuf[iCnt+1] != ETX)
											 && (aWrkBuf[iCnt+1] != LF) ) {
					fprintf(fp,"%c",'\n');
				}
			} else if( aWrkBuf[iCnt] == ETB ){
				fprintf(fp,"%s","<ETB>");
			} else if( aWrkBuf[iCnt] == ETX ){
				fprintf(fp,"%s","<ETX>");
			} else if( aWrkBuf[iCnt] == LF ){
				fprintf(fp,"%s","<LF>");
				fprintf(fp,"%c",'\n');
				break;
			} else if( aWrkBuf[iCnt] < 0x20 ){
				fprintf(fp,"%02x",aWrkBuf[iCnt]);
			} else if( (iCnt == (iWrk-3)) || (iCnt == (iWrk-4)) ) {
				fprintf(fp,"%c",aWrkBuf[iCnt]);
			} else {
				fprintf(fp,"%c",aWrkBuf[iCnt]);
			}
		}

//		printf("cnt:%d\n",iCnt);

		fprintf(fp,"%c",'\n');
		fclose(fp);
	}
	return RTN_OK;
}
