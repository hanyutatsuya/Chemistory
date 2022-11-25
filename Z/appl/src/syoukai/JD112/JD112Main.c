/********************************************************************/
/*																	*/
/*		�a�l�k�l���������V�X�e��									*/
/*																	*/
/*		�V�X�e����	�F������V�X�e��								*/
/*		�t�@�C����	�FJD112Main.c									*/
/*		�T�v		�F�����i�s�󋵏W�v����							*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	�쐬��			���O			�C�����e				*/
/* ---------------------------------------------------------------- */
/*  1.00	2006/03/23		H.Suyama		Create					*/
/*  1.01	2006-04-26		H.Suyama		BSKGOK��BSKLNE�ɕύX	*/
/*  1.02	2006-06-03		INTEC   		�W�v����0��INSERT		*/
/*  1.04    2006-06-17      INTEC           �o�^����10���P�ʂɍ쐬 */
/********************************************************************/

/********************************************************************/
/*	�C���N���[�h�錾												*/
/********************************************************************/
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "bml_date.h"
#include "bmllog.h"
#include "bmlprm.h"
#include "JD112Main.h"
#include "JD112Sysknrmst.h"
#include "JD112Syukei.h"

/******************************************************************************/
/* Define��`																  */
/******************************************************************************/
// TRACE
#if defined ( _TRACE )
#define malloc(a)   _malloc(a, __FILE__, __LINE__)
#define free(p)	 _free(p, __FILE__, __LINE__)
#endif

/******************************************************************************/
/* �O���[�o���錾															  */
/******************************************************************************/
JD112_STSCODE		gintErrorCode;
struct stcLogMember	gstLogMem;

/*:KH-------------------------------------------------------------------------*/
/*:K  �֐���   : EnvRef                                                       */
/*----------------------------------------------------------------------------*/
/*:A  �@�\�T�v : �����ϐ���W�J����                                         */
/*----------------------------------------------------------------------------*/
/*:I  ����     : char    *src_cp  : �W�J�O������                              */
/*:O  �o��     : ����             : ����                                      */
/*:R  �߂�l   : char *           : �W�J�㕶����                              */
/*:C  ���L���� :                                                              */
/*----------------------------------------------------------------------------*/
char    *EnvRef( src_cp )
char        *src_cp;
{
static char value[256];                 /* �W�J�㕶���� */
    char    *dst_cp;                    /* �W�J�㕶���� */
    char    buf[256];                   /* �����ϐ� */
    char    *env_cp;                    /* �����ϐ� */

    dst_cp = value;
    while( *src_cp != 0 ) {
        if( *src_cp == '$' ) {
            env_cp = buf;
            *env_cp++ = *src_cp++;
            while( *src_cp != 0
                && *src_cp != ' ' && *src_cp != '\t'
                && *src_cp != '$' && *src_cp != '/' && *src_cp != '\\' ) {
                *env_cp++ = *src_cp++;
            }
            *env_cp = 0;
            if( (env_cp = getenv( &buf[1] )) == NULL ) {
                env_cp = buf;
            }
            while( *env_cp != 0 ) {
                *dst_cp++ = *env_cp++;
            }
        } else {
            *dst_cp++ = *src_cp++;
        }
    }
    *dst_cp = 0;

    return( value );
}

/******************************************************************************/
/*�@�� �� ���@�FinitFunction()												  */
/*�@�@�\�T�v�@�F���������֐�												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����Fint argc			�v���O����������						  */
/*�@�@��Q�����Fchar *argv[]		�v���O��������							  */
/*�@�@��R�����FJD112Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int initFunction( int argc, char *argv[], JD112Env *pEnv )
{
	char	cPrmBuf[256];
	char	*lc_login;

	// ������
	// �G���[�X�e�[�^�X�ύX
	gintErrorCode = 0;
	// �v���O�������ϐ�������
	memset( pEnv, '\0', sizeof( JD112Env ) );

	// ���O�I�[�v��
    // 1.03 HAGA DELL ���ϐ��W�J��̒l��n��
/*
DEL if( ZbmlOpenLog( MYAPP_LOGINIFILE ) != 0 ) {
*/
    if( ZbmlOpenLog( EnvRef( MYAPP_LOGINIFILE ) ) != 0 ) {
        return( RTN_NG );
    }

	// ���O��񏉊��ݒ�
	memset( &gstLogMem, '\0', sizeof( gstLogMem ) );
	if ( ( lc_login = getenv( "LOGNAME" ) ) != NULL ) {
		strcpy( gstLogMem.pcLoginId, lc_login );
	}
	strcpy( gstLogMem.pcAppName, MYAPP_APP_NAME );

	// �J�n���O�o��
	sFncPutLog( TRCKIND_TRACE, __FILE__, "", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�v���O�����N��" );

/*
	// �������`�F�b�N
	if ( argc != 2 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_USEGE;
		sFncPutLog( TRCKIND_ERROR, __FILE__, "initFunction", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�R�}���h�p�����[�^�Ɍ�肪����܂�" );
		return( RTN_NG );
	}
*/
	// �p�����[�^�t�@�C�����ޔ�
	if ( argc >= 2 ) {
		pEnv->pcFileNamePRM = argv[1];
	} else {
		pEnv->pcFileNamePRM = MYAPP_INIFILE;
	}

	// �p�����[�^�t�@�C���I�[�v��
	pEnv->bp = ZbmlPrmOpen( pEnv->pcFileNamePRM );
	if ( pEnv->bp == NULL ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_FILE;
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZZbmlPrmOpen", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�p�����[�^�t�@�C���̃I�[�v���Ɏ��s���܂���[%s]", pEnv->pcFileNamePRM );
		return( RTN_NG );
	}

	// �f�[�^�x�[�X�ڑ���
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_DBNAME,
						 pEnv->cDBName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���O�C�����[�U
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_DBUSER,
						pEnv->cDBUser ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���O�C���p�X���[�h
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_DBPAWD,
						pEnv->cDBPawd ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �|�[�g�ԍ�
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_PORTNO,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iPortNo= atoi( cPrmBuf );
	// �R�l�N�g�ڑ��҂���
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_LISTEN,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iListen= atoi( cPrmBuf );
	// �ʐM���g���C��
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_RETRY_CNT,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iRetryCnt= atoi( cPrmBuf );
	// �^�C���A�E�g�l�i�b�j
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_TIMEOUT,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iTimeout= atoi( cPrmBuf );
	// �˗��W�J�A�v����
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_APP_IRAI,
						pEnv->cAppIrai ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���ґ����W�J�A�v����
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_APP_KANJYA,
						pEnv->cAppKanjya ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �����W�J�A�v����
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_APP_BUNCHU,
						pEnv->cAppBunchu ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �F���W�J�A�v����
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_APP_NINSIKI,
						pEnv->cAppNinsiki ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���̑����W�J�A�v����
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_APP_KENZOK,
						pEnv->cAppKenzok ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �f�o�b�O���O�t�@�C��
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_FILE_DBG,
						pEnv->cDebugLogName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �g���[�X���O�t�@�C��
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_FILE_TR,
						pEnv->cTraceLogName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �A�N�Z�X���O�t�@�C��
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_FILE_ACS,
						pEnv->cAccessLogName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �G���[���O�t�@�C��
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_FILE_ERR,
						pEnv->cErrorLogName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���L�������L�[�擾
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_SHM_KEY,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->shm_Key = atoi( cPrmBuf );
	// �X���[�v���ԁi�b�j�擾
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_SLEEP_SEC,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iSleepSec= atoi( cPrmBuf );
	// �X�V�Ԋu�i���j�擾
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_UPDATE_MIN,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iUpdateMin= atoi( cPrmBuf );
	// �X�V��ID
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_UP_ID,
						pEnv->cUpdateId ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �X�V�Җ�
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_UP_NM,
						pEnv->cUpdateName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���s���[�h
	if ( ZbmlPrmGetVal( pEnv->bp, JD112_PRM_PROC_MD,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->proc_mode= atoi( cPrmBuf );

	// 1.04 ADD �W�v�ΏۊJ�n����(YYYY-MM-DD-HH24:MI:00)(�K�{�ł͂Ȃ�)
	ZbmlPrmGetVal( pEnv->bp, JD112_PRM_STA_DH, pEnv->cStaTimestamp );

	// �p�����[�^�t�@�C���N���[�Y
	ZbmlPrmClose( pEnv->bp );

	// ���L����������
	if ( sFncShmCrt( pEnv ) != RTN_OK ) {
		return( RTN_NG );
	}

	// �\�P�b�gFD������
	pEnv->iSockFd = 0;
	// �X���b�h�X�e�[�^�X������
	pEnv->iThreadSts = 0;
	// �W�v���s�J�n�t���O������
	pEnv->iCallFunc = JD112_CALLFUNC_START;
	// �W�v�J�n���ԏ�����
	pEnv->ulPrevKsndh = 0;
	// ����N�����̎���
	pEnv->iBaseJikan = 0;

	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "initFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function" );
	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FmainFunction()												  */
/*�@�@�\�T�v�@�F���C�������֐�												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FJD112Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int mainFunction( JD112Env *pEnv )
{
	int			iRet;
	int			iShmMem;
	int			iLapseSec = 0;
	pthread_t	thread;
	int			*pExitCode;
	Sysknrmst	stSysknrmst;

	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	// �f�[�^�x�[�X�ڑ�
	if( iRet = ZdbConnect( pEnv->cDBName,
						   pEnv->cDBUser,
						   pEnv->cDBPawd ) ) {
		// �ُ�I��	LOG
printf("ZdbConnect error (%d)\n", iRet);
		return( RTN_NG );
	}

	// �\�P�b�g�ʐM�p�X���b�h�̍쐬
	if ( iRet = pthread_create( &thread, NULL, JD112SocketThread, (void *)pEnv ) ) {
		// �ُ�I��	LOG
printf("pthread_create error (%d)\n", iRet);
		return( RTN_NG );
	}

	// �V�X�e���Ǘ����擾
	iRet = ZdbSysknrmstSelect( &stSysknrmst );
	if ( iRet != HRC_SQL_NORMAL ) {
		// �ُ�I��	LOG
printf("ZdbSysknrmstSelect error (%d)\n", iRet);
		return( RTN_NG );
	}

	// �񍐊Ǘ����e�[�u���Ď�
	// �i�v���[�v�A��~�R�}���h�ŏI��
	while ( 1 ) {
		// ��~�R�}���h�m�F
		if ( sFncShmGet( pEnv, &iShmMem ) != RTN_OK ) {
printf("sFncShmGet error\n");
			return( RTN_NG );
		}
		if ( iShmMem == 1 ) {
			if ( pEnv->iSockFd != 0 ) {
				shutdown( pEnv->iSockFd, SHUT_RDWR );
			}
printf( "sock FD:[%d]\n", pEnv->iSockFd );
//			pthread_cancel( thread );
			break;
		}

		// �X�V�Ԋu�𒴂�����W�v�������R�[������
		if ( iLapseSec >= ( pEnv->iUpdateMin * JD112_SECOFMIN ) ) {
			iLapseSec = 0;
			pEnv->iCallFunc = JD112_CALLFUNC_START;
		}

		// ����A�X�V�Ԋu�o�ߌ�A�N���C�A���g�v�����͌o�ߎ��Ԃ��O
		if ( pEnv->iCallFunc == JD112_CALLFUNC_START ) {
printf("call JD112SyukeiMain\n");
			// �����i�s�󋵏W�v���C���Ăяo��
			JD112SyukeiMain( pEnv, stSysknrmst.kjnsriymd );
			pEnv->iCallFunc = JD112_CALLFUNC_STOP;
		}
		
		// �X���[�v
		sleep( pEnv->iSleepSec );
		iLapseSec += pEnv->iSleepSec;
	}

	pthread_join( thread, (void **)&pExitCode );
	if ( pExitCode == NULL ) {
		printf("Thread code is NULL\n");
	} else {
printf("3\n");
		printf("Thread code is %d\n", *pExitCode);
	}

	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FendFunction()												  */
/*�@�@�\�T�v�@�F�I�������֐�												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FJD112Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�F�Ȃ�														  */
/******************************************************************************/
void endFunction( JD112Env *pEnv )
{
	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "endFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");
	// ���L�������폜
	if ( sFncShmDel( pEnv ) != RTN_OK ) {
		return;
	}

	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "endFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");
}

/******************************************************************************/
/*�@�� �� ���@�FJD112SyukeiMain()											  */
/*�@�@�\�T�v�@�F�����i�s�󋵏W�v���C��										  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FJD112Env *pEnv		�v���O�������\����					  */
/*�@�@��Q�����Fchar *pKnskisymd	�����J�n��								  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�F�Ȃ�														  */
/******************************************************************************/
int JD112SyukeiMain( JD112Env *pEnv, char *pKnskisymd )
{
	int			iRet;
	JD112Syukei	*pJD112SyukeiArray = NULL;
	int			iJD112SyukeiNum;
	Knssnkjyk	stKnssnkjyk;
	ULONG		ulExecTime;
	struct tm	*tm;
	char		cFromDt[27];
	char		cToDt[27];
	char		cFromDateTime[19];
	char		cToDateTime[19];
	char		cKoteiLoop;
	int			iLoop;
	int			iJikan;
	char		cbuf[10];			// 1.02 ADD
	int			iLoop2;				// 1.02 ADD
	int			me_max;				// 1.02 ADD
	struct		_MEMST	*pMe;		// 1.02 ADD
	char		clExecTime[27];		// 1.04 ADD
	int			iDateRet;			// 1.04 ADD
	int 		icnt0 = 0;				// 1.04 ADD

	// ���������ݒ�
	time( (long *)&ulExecTime );
	tm = localtime( (long *)&ulExecTime );
/* 1.04 DELL 
//	sprintf( cToDt, JD112_FMT_TIMESTAMP,
//			 tm->tm_year + 1900,
//			 tm->tm_mon + 1,
//			 tm->tm_mday,
//			 tm->tm_hour,
//			 tm->tm_min,
//			 tm->tm_sec );
//	sprintf( cToDateTime, JD112_FMT_DATETIME,
//			 tm->tm_year + 1900,
//			 tm->tm_mon + 1,
//			 tm->tm_mday,
//			 tm->tm_hour,
//			 tm->tm_min,
//			 tm->tm_sec );
//
//	if ( pEnv->ulPrevKsndh == 0 ) {
//		// �O��W�v�J�n���Ԃ������l�̏ꍇ�̓V�X�e���N�����Ԃ���Z�o
//		tm->tm_min = 0;
//		tm->tm_sec = 0;
//		// ����N�����̎��Ԃ�ۑ�
//	 	pEnv->iBaseJikan = tm->tm_hour;
//	} else {
//		// �O��W�v�J�n����
//		tm = localtime( (long *)&pEnv->ulPrevKsndh );
//	}
//	sprintf( cFromDt, JD112_FMT_TIMESTAMP,
//			 tm->tm_year + 1900,
//			 tm->tm_mon + 1,
//			 tm->tm_mday,
//			 tm->tm_hour,
//			 tm->tm_min,
//			 tm->tm_sec );
//	sprintf( cFromDateTime, JD112_FMT_DATETIME,
//			 tm->tm_year + 1900,
//			 tm->tm_mon + 1,
//			 tm->tm_mday,
//			 tm->tm_hour,
//			 tm->tm_min,
//			 tm->tm_sec );
*/
	// �����ΏۏI������(=SYSDATE)�̐ݒ�
	memset( clExecTime, '\0', sizeof( clExecTime ));
	sprintf( clExecTime, JD112_FMT_TIMESTAMP,
			 tm->tm_year + 1900,
			 tm->tm_mon + 1,
			 tm->tm_mday,
			 tm->tm_hour,
			 tm->tm_min,
			 tm->tm_sec );
		// �����O�ɂ���	
	clExecTime[15] = '0';

	// �����ΏۊJ�n�����̐ݒ� TO -10min -> FROM
	memset( cFromDt,	'\0',	sizeof( cFromDt ));
	memset( cToDt,		'\0',	sizeof( cToDt ));
		// ����
	if ( pEnv->clPrevKsndh[0] == '\0' ) {
			// CurrenTimestamp -1 hour ���擾
		if( SelStaTimestamp( cToDt ) != RTN_OK ){
			// ERROR
			strcpy( cToDt,	clExecTime );
		}
		// �W�v�J�n�����̎w�肠��
		if ( pEnv->cStaTimestamp[0] != '\0' ) {
				// �����Ó����`�F�b�N
			if( SelStaTimestamp( pEnv->cStaTimestamp ) == RTN_OK ){
				strcpy( cToDt, pEnv->cStaTimestamp );	
			}
		}
		// �����Ώۂ͂P�O���P�ʂƂ����͐؂�̂�,�b�ȉ����O��
		strcpy( cFromDt,	cToDt );
		sprintf( cToDt, "%.15s0.00.000000", cFromDt );
	} else {
		// �O��W�v�J�n����
		strcpy( cToDt,	pEnv->clPrevKsndh );
	}
		// MINUS 10
	SelPlus10Minutes( cToDt, MYAPP_FUNC_MINUS );

// 1.04 ADD �J�n��������SYSDATE�܂�10�����݂ŏW�v���������{
while( 1 ){
	strcpy( cFromDt, cToDt );
	if(( iDateRet = SelPlus10Minutes( cToDt, MYAPP_FUNC_PLUS )) !=  RTN_OK ){
		strcpy( cToDt, clExecTime );	
	}
//printf("exec[%s] from[%s] to[%s]\n", clExecTime, cFromDt, cToDt );
	if( strncmp( clExecTime, cFromDt, 15 ) < 0 ){
		break;
	}
		
	for ( cKoteiLoop = JD112_DB_KOTEIKBN_IRAI;
		  cKoteiLoop <= JD112_DB_KOTEIKBN_SYUNOU;
		  cKoteiLoop++ ) {
		switch ( cKoteiLoop ) {
		// �˗����W�v
		case JD112_DB_KOTEIKBN_IRAI:
			iRet = ZdbJD112SelectCountA( cFromDt, cToDt,
										 &pJD112SyukeiArray,
										 &iJD112SyukeiNum );
			break;
		// ���Ґ��W�v
		case JD112_DB_KOTEIKBN_KANJYA:
			iRet = ZdbJD112SelectCountB( cFromDt, cToDt,
										 &pJD112SyukeiArray,
										 &iJD112SyukeiNum );
			// 1.04 ADD �W���t���ONULL�Ή� 0�ƍ��Z
			for( iLoop2 = 0; iLoop2 < iJD112SyukeiNum ; iLoop2++ ){
				if ( pJD112SyukeiArray[iLoop2].skflg == JD112_DB_SKFLG_NORMAL ){
					icnt0 += pJD112SyukeiArray[iLoop2].count;
				}
			}
			for( iLoop2 = 0; iLoop2 < iJD112SyukeiNum ; iLoop2++ ){
				if ( pJD112SyukeiArray[iLoop2].skflg == JD112_DB_SKFLG_NORMAL ){
					pJD112SyukeiArray[iLoop2].count = icnt0;
				}
			}
			break;
		// �������W�v
		case JD112_DB_KOTEIKBN_BUNCHU:
			iRet = ZdbJD112SelectCountC( cFromDt, cToDt,
										 &pJD112SyukeiArray,
										 &iJD112SyukeiNum );
			break;
		// �F�����W�v
		case JD112_DB_KOTEIKBN_NINSIKI:
			iRet = ZdbJD112SelectCountD( cFromDt, cToDt,
										 &pJD112SyukeiArray,
										 &iJD112SyukeiNum );
			break;
		// ���̑������W�v
		case JD112_DB_KOTEIKBN_KENZOK:
			iRet = ZdbJD112SelectCountE( cFromDt, cToDt,
										 &pJD112SyukeiArray,
										 &iJD112SyukeiNum );
			break;
		// �˗��i�G���[�j���W�v
		case JD112_DB_KOTEIKBN_E_IRAI:
			// 1.04 UPD
			//iRet = ZdbJD112SelectCountFGHIJ( cFromDateTime,
			//								 cToDateTime,
			iRet = ZdbJD112SelectCountFGHIJ( cFromDt, cToDt,
											 pEnv->cAppIrai,
											 &pJD112SyukeiArray,
											 &iJD112SyukeiNum );
			break;
		// ���ҁi�G���[�j���W�v
		case JD112_DB_KOTEIKBN_E_KANJYA:
			// 1.04 UPD
			//iRet = ZdbJD112SelectCountFGHIJ( cFromDateTime,
			//								 cToDateTime,
			iRet = ZdbJD112SelectCountFGHIJ( cFromDt, cToDt,
											 pEnv->cAppKanjya,
											 &pJD112SyukeiArray,
											 &iJD112SyukeiNum );
			break;
		// �����i�G���[�j���W�v
		case JD112_DB_KOTEIKBN_E_BUNCHU:
			// 1.04 UPD
			//iRet = ZdbJD112SelectCountFGHIJ( cFromDateTime,
			//								 cToDateTime,
			iRet = ZdbJD112SelectCountFGHIJ( cFromDt, cToDt,
											 pEnv->cAppBunchu,
											 &pJD112SyukeiArray,
											 &iJD112SyukeiNum );
			break;
		// �F���i�G���[�j���W�v
		case JD112_DB_KOTEIKBN_E_NINSIKI:
			// 1.04 UPD
			//iRet = ZdbJD112SelectCountFGHIJ( cFromDateTime,
			//								 cToDateTime,
			iRet = ZdbJD112SelectCountFGHIJ( cFromDt, cToDt,
											 pEnv->cAppNinsiki,
											 &pJD112SyukeiArray,
											 &iJD112SyukeiNum );
			break;
		// ���̑����i�G���[�j���W�v
		case JD112_DB_KOTEIKBN_E_KENZOK:
			// 1.04 UPD
			//iRet = ZdbJD112SelectCountFGHIJ( cFromDateTime,
			//								 cToDateTime,
			iRet = ZdbJD112SelectCountFGHIJ( cFromDt, cToDt,
											 pEnv->cAppKenzok,
											 &pJD112SyukeiArray,
											 &iJD112SyukeiNum );
			break;
		// �������W�v
		case JD112_DB_KOTEIKBN_TOUNYU:
			iRet = ZdbJD112SelectCountKM( cFromDt, cToDt,
										  JD112_DB_KNSJKFLG_CHUU,
										 &pJD112SyukeiArray,
										 &iJD112SyukeiNum );
			break;
		// ���萔�W�v
		case JD112_DB_KOTEIKBN_SOKUTEI:
			iRet = ZdbJD112SelectCountL( cFromDt, cToDt,
										 &pJD112SyukeiArray,
										 &iJD112SyukeiNum );
			break;
		// ���[���W�v
		case JD112_DB_KOTEIKBN_SYUNOU:
			iRet = ZdbJD112SelectCountKM( cFromDt, cToDt,
										  JD112_DB_KNSJKFLG_DONE,
										  &pJD112SyukeiArray,
										  &iJD112SyukeiNum );
			break;
		}
		if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
			//�ُ�I��
			//���O�o��
printf("ZdbJD112SelectCount* error (%d)\n", iRet);
			return( RTN_NG );
		}

		// �擾�������ޕ��W�v�e�[�u���X�V
		for ( iLoop = 0; iLoop < iJD112SyukeiNum; iLoop++ ) {
			memset( &stKnssnkjyk, 0, sizeof( stKnssnkjyk ) );

/* 1.04 DELL �����J�n���ɂ͓o�^�����A�o��seq�͎Z�o����������ݒ�
//			ZbmlInfocpy( stKnssnkjyk.knskisymd, pKnskisymd, 
//					sizeof( stKnssnkjyk.knskisymd ) );
//			// �o�߂r�d�p�͋N�����̎��Ԃ���Z�o
//			iJikan = atoi( pJD112SyukeiArray[iLoop].jikan );
//			if ( iJikan >= pEnv->iBaseJikan ) {
//				stKnssnkjyk.keikseq = iJikan - pEnv->iBaseJikan + 1;
//			} else {
//				stKnssnkjyk.keikseq = iJikan + 24 - pEnv->iBaseJikan + 1;
//			}
*/
			// jikan( YYYY-MM-DD-HH24:MI )
			// �����J�n�� (jikan YYYY-MM-DD)
			sprintf( stKnssnkjyk.knskisymd, "%.10s"
					, pJD112SyukeiArray[iLoop].jikan );
			// �o��seq ����( jikan HH24MI 0 )
			sprintf( stKnssnkjyk.jikan, "%.2s%.1s0"
					, &pJD112SyukeiArray[iLoop].jikan[11] 
					, &pJD112SyukeiArray[iLoop].jikan[14] );
			stKnssnkjyk.keikseq = atoi( stKnssnkjyk.jikan );

			stKnssnkjyk.koteikbn = cKoteiLoop;
			if ( pJD112SyukeiArray[iLoop].skflg == JD112_DB_SKFLG_NORMAL )
				stKnssnkjyk.datazok = JD112_DB_DATAZOK_NORMAL;
			else if ( pJD112SyukeiArray[iLoop].skflg == JD112_DB_SKFLG_SYUKEN )
				stKnssnkjyk.datazok = JD112_DB_DATAZOK_SYUKEN;

			if ( stKnssnkjyk.koteikbn == JD112_DB_KOTEIKBN_SOKUTEI ) {
				ZbmlInfocpy( stKnssnkjyk.bskkbn
					, pJD112SyukeiArray[iLoop].bskkbn
					, sizeof( stKnssnkjyk.bskkbn ) );
// 2006-04-26 H.Suyama Change Start
#if 0
//				ZbmlInfocpy( stKnssnkjyk.bskgok, pJD112SyukeiArray[iLoop].bskgok, sizeof( stKnssnkjyk.bskgok ) );
#else
				ZbmlInfocpy( stKnssnkjyk.bskgok
					, pJD112SyukeiArray[iLoop].bsklne
					, sizeof( stKnssnkjyk.bskgok ) );
#endif
// 2006-04-26 H.Suyama Change End
			} else {
				memset( stKnssnkjyk.bskkbn, JD112_CHAR_SPACE
						, sizeof( stKnssnkjyk.bskkbn ) - 1 );
				memset( stKnssnkjyk.bskgok, JD112_CHAR_SPACE
						, sizeof( stKnssnkjyk.bskgok ) - 1 );
			}
			stKnssnkjyk.syukka = pJD112SyukeiArray[iLoop].count;
/* 1.04 DELL 
//			sprintf( stKnssnkjyk.jikan, "%2s00"
//					, pJD112SyukeiArray[iLoop].jikan );
*/
			ZbmlInfocpy( stKnssnkjyk.ksndh, cToDt, sizeof( stKnssnkjyk.ksndh ));

			// �����i�s�󋵏W�v�X�V
			iRet = JD112UpdateKnssnkjyk( &stKnssnkjyk );
			if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
				//�ُ�I��
				//���O�o��
printf("JD112UpdateKnssnkjyk error (%d)\n", iRet);
				return( RTN_NG );
			}
		}

		// 1.02 INTEC ADD STA
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// �S�f�[�^�����A���͋@�敪�A���@�̃��R�[�h���O���ō쐬����
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			// ���ʃf�[�^�ݒ�
		memset( &stKnssnkjyk, '\0', sizeof( stKnssnkjyk ) );
/* 1.04 DELL
//		ZbmlInfocpy( stKnssnkjyk.knskisymd, pKnskisymd, 
//					sizeof( stKnssnkjyk.knskisymd ) );
//			// �o�߂r�d�p�Z�o���́Afrom�̎��Ԃ��Z�b�g
//		memset( cbuf, '\0', sizeof( cbuf ));
//		sprintf( cbuf, "%.2s", &cToDt[11] );
//		iJikan = atoi( cbuf );
//		if ( iJikan >= pEnv->iBaseJikan ) {
//			stKnssnkjyk.keikseq = iJikan - pEnv->iBaseJikan + 1;
//		} else {
//			stKnssnkjyk.keikseq = iJikan + 24 - pEnv->iBaseJikan + 1;
//		}
*/
		// �����J�n�� (cToDt YYYY-MM-DD)
		sprintf( stKnssnkjyk.knskisymd, "%.10s" , cFromDt  );
		// �o��seq ����( cToDt HH24MI 0 )
		sprintf( stKnssnkjyk.jikan, "%.2s%.1s0"
				, &cFromDt[11], &cFromDt[14] );
		stKnssnkjyk.keikseq = atoi( stKnssnkjyk.jikan );

		stKnssnkjyk.koteikbn = cKoteiLoop;

		memset( stKnssnkjyk.bskkbn, JD112_CHAR_SPACE, 
						sizeof( stKnssnkjyk.bskkbn ) - 1 );
		memset( stKnssnkjyk.bskgok, JD112_CHAR_SPACE, 
						sizeof( stKnssnkjyk.bskgok ) - 1 );
		stKnssnkjyk.syukka = 0;
/* 1.04 DELL
//			// ���Ԃɂ�from�̎��Ԃ��g�p
//		sprintf( stKnssnkjyk.jikan, "%2s00", cbuf );
*/
		ZbmlInfocpy( stKnssnkjyk.ksndh, cToDt, sizeof( stKnssnkjyk.ksndh ));

		// �f�[�^�������쐬
		for ( iLoop = 0; iLoop < 2; iLoop++ ) {
			if ( stKnssnkjyk.koteikbn == JD112_DB_KOTEIKBN_SOKUTEI ) {
				continue;
			}
			if( iLoop == 0 ){
				stKnssnkjyk.datazok = JD112_DB_DATAZOK_NORMAL;
			} else {
				stKnssnkjyk.datazok = JD112_DB_DATAZOK_SYUKEN;
			}
			// �����i�s�󋵏W�v�X�V

			iRet = JD112UpdateKnssnkjyk( &stKnssnkjyk );
			if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
				//�ُ�I��
				//���O�o��
				// commit rollback ��JD112UpdateKnssnkjyk�@�ɂĎ��{
				return( RTN_NG );
			}
		}
		// �H����L�̏ꍇ�́A���͋@�敪�A���C�����쐬 �f�[�^�������쐬
		if ( stKnssnkjyk.koteikbn == JD112_DB_KOTEIKBN_SOKUTEI ) {
			// ���͋@�}�X�^�̌����擾
			me_max=SelCountMemst( stKnssnkjyk.knskisymd );
			if( me_max == 0 ){
				// ERROR
				break;
			}
			// �̈�m��
			if(( pMe = ((struct _MEMST *)malloc(
					sizeof(struct _MEMST) * me_max ))) == NULL ){
				//sprintf(G_msg, "���͋@�}�X�^�̗̈�m�ۂɎ��s���܂����B" );
				// WARNING
				break;
			}
			/* ��l�}�X�^�ޔ�̈�̏����� */
			memset( pMe, '\0', sizeof( struct _MEMST ) * me_max );

			// �Ώۊ�l�}�X�^�̎擾
			if( SelMemst( stKnssnkjyk.knskisymd, me_max, pMe ) !=  RTN_OK ){
				//sprintf(G_msg, "���͋@�}�X�^�̓ǂݍ��݂Ɏ��s���܂����B" );
				// WARNING
				free( pMe );
				break;
       		}
			
			// �f�[�^�������쐬
			for ( iLoop2 = 0; iLoop2 < me_max; iLoop2++ ) {
				strcpy( stKnssnkjyk.bskkbn, pMe[iLoop2].bskkbn );
				strcpy( stKnssnkjyk.bskgok, pMe[iLoop2].bsklne );

				for ( iLoop = 0; iLoop < 2; iLoop++ ) {
					if( iLoop == 0 ){
						stKnssnkjyk.datazok = JD112_DB_DATAZOK_NORMAL;
					} else {
						stKnssnkjyk.datazok = JD112_DB_DATAZOK_SYUKEN;
					}
					// �����i�s�󋵏W�v�X�V
					iRet = JD112UpdateKnssnkjyk( &stKnssnkjyk );
					if (iRet != HRC_SQL_NORMAL&&iRet != HRC_SQL_NOT_FOUND){
						//�ُ�I��
						//���O�o��
						free( pMe );
						return( RTN_NG );
					}
				}
			}
			if( pMe != NULL ){
				free( pMe );
			}
		}
		// 1.02 INTEC ADD END

		if ( pJD112SyukeiArray ) {
			ZbmlFree( pJD112SyukeiArray );
			pJD112SyukeiArray = NULL;
		}
	}

	ZdbCommit();
}

	pEnv->ulPrevKsndh = ulExecTime;
	strcpy( pEnv->clPrevKsndh, cFromDt );

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FJD112UpdateKnssnkjyk()										  */
/*�@�@�\�T�v�@�F�����i�s�󋵏W�v�X�V										  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FKnssnkjyk	*pKnssnkjyk	�����i�s�󋵏W�v���\����			  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int JD112UpdateKnssnkjyk(Knssnkjyk *pKnssnkjyk)
{
	int			iRet;
	Knssnkjyk	stKnssnkjyk;
	int			iKeikseq;

	//memset( &stKnssnkjyk, 0, sizeof( stKnssnkjyk ) );
	memset( &stKnssnkjyk, '\0', sizeof( stKnssnkjyk ) );

	// �������ԑт̓���L�[���R�[�h�����邩����
	iRet = ZdbKnssnkjykJD112SelectJikan( pKnssnkjyk,
										 &stKnssnkjyk );
	if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
		// ���[���o�b�N
		ZdbRollback();
		// �ُ�I��	LOG
printf("ZdbKnssnkjykJD112SelectJikan error (%d)\n", iRet);
		return( RTN_NG );
	}

	if ( iRet == HRC_SQL_NOT_FOUND ) {
		// �����i�s�󋵏W�v�}��
		iRet = ZdbKnssnkjykInsert( pKnssnkjyk );
	} else {
		// 1.04 ADD �W�v�l���O�̏ꍇ�͏����𔲂���
		if( pKnssnkjyk->syukka == 0 ){
			ZdbCommit();
			return( RTN_OK );
		}
		// 1.04 DELL ���Z�͂����ɍX�V����
/*
//		// �݌v���v�Z
//		stKnssnkjyk.syukka += pKnssnkjyk->syukka;
//		// ���X�V������ύX
//		ZbmlInfocpy( stKnssnkjyk.ksndh, pKnssnkjyk->ksndh, sizeof( stKnssnkjyk.ksndh ) );
//
//		// �����i�s�󋵏W�v�X�V
//		iRet = ZdbKnssnkjykUpdate( &stKnssnkjyk );
*/
		// �����i�s�󋵏W�v�X�V
		iRet = ZdbKnssnkjykUpdate( pKnssnkjyk );
	}

	if ( iRet != HRC_SQL_NORMAL ) {
		// ���[���o�b�N
		ZdbRollback();
		// �ُ�I��	LOG
printf("ZdbKnssnkjykXXXXXX error (%d)\n", iRet);
// 1.02 INTEC ADD STA
		sFncPutLog( TRCKIND_ERROR, __FILE__, "JD112UpdateKnssnkjyk", __LINE__,
                    EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
               	 	"�����i�s�󋵏W�v�X�V�Ɏ��s���܂����B"
					"KNSKISYMD[%s] KEIKSEQ[%d] KOTEIKBN[%c] DATAZOK[%c]", 
					pKnssnkjyk->knskisymd,	pKnssnkjyk->keikseq, 
					pKnssnkjyk->koteikbn,	pKnssnkjyk->datazok );
// 1.02 INTEC ADD END
		return( RTN_NG );
	}
ZdbCommit();

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FJD112SocketThread()											  */
/*�@�@�\�T�v�@�F�\�P�b�g�ʐM�p�X���b�h										  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FJD112Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�F�Ȃ�														  */
/******************************************************************************/
void *JD112SocketThread(void *pParam)
{
	JD112Env	*pEnv;
	int			iSockFd;
	int			iNewSockFd;
	int			iSockSts;
	int			iFcSts;
	int			iLen;
	struct sockaddr_in	stSockAddrIn;
	struct sockaddr_in	stSockAddrInCl;
	char		cBuff[JD112_MSG_BUFFLEN];

	pEnv = (JD112Env *)pParam;

	// �\�P�b�g������
	if ( ( iSockFd = socket( AF_INET, SOCK_STREAM, 0 ) ) == 0 ) {
printf( "socket error\n", iSockFd );
		pEnv->iThreadSts = MYAPP_LOG_ERRCODE_SOCKET;
		pthread_exit( &pEnv->iThreadSts );
	}
	pEnv->iSockFd = iSockFd;

	// �o�C���h
	memset( &stSockAddrIn, 0, sizeof( stSockAddrIn ) );
	stSockAddrIn.sin_family = AF_INET;
	stSockAddrIn.sin_addr.s_addr = INADDR_ANY;
	stSockAddrIn.sin_port = htons( pEnv->iPortNo );
	if ( bind( iSockFd, (struct sockaddr *)&stSockAddrIn,
			   sizeof( struct sockaddr_in ) ) == -1 ) {
		close( iSockFd );
		pEnv->iThreadSts = MYAPP_LOG_ERRCODE_SOCKET;
		pthread_exit( &pEnv->iThreadSts );
	}

	// �ڑ��҂��ݒ�
	if ( listen( iSockFd, pEnv->iListen ) < 0 ) {
		close( iSockFd );
		pEnv->iThreadSts = MYAPP_LOG_ERRCODE_SOCKET;
		pthread_exit( &pEnv->iThreadSts );
	}
printf("Thread start\n");

	while ( 1 ) {
		// �ڑ��҂�
		if ( ( iNewSockFd = accept( iSockFd,
									(struct sockaddr *)&stSockAddrInCl,
									&iLen ) ) < 0 ) {
			close( iSockFd );
			if ( errno != EINVAL ) {
				pEnv->iThreadSts = MYAPP_LOG_ERRCODE_SOCKET;
			}
			if ( errno != EINTR ) {
				close( iNewSockFd );
			}
			pthread_exit( &pEnv->iThreadSts );
		}
printf("accept OK\n");

		// �f�[�^�ǂݍ���
		if ( JD112SocketRead( iNewSockFd,
							  cBuff,
							  sizeof( cBuff ),
							  pEnv ) == RTN_NG ) {
			shutdown( iNewSockFd, SHUT_RDWR );
			close( iNewSockFd );
			pEnv->iThreadSts = MYAPP_LOG_ERRCODE_SOCKET;
			pthread_exit( &pEnv->iThreadSts );
		}

		// �f�[�^����
		if ( memcmp( cBuff, JD112_MSG_START, sizeof( JD112_MSG_START ) ) == 0 ) {
			pEnv->iCallFunc = JD112_CALLFUNC_START;

			// �W�v�����҂�
			while ( pEnv->iCallFunc == JD112_CALLFUNC_START ) {
				sleep( 1 );
			}
printf("Syukei end\n");

			// �I���d�����M
			strcpy( cBuff, JD112_MSG_END );
			if ( JD112SocketWrite( iNewSockFd,
								   cBuff,
								   strlen( cBuff ),
								   pEnv ) == RTN_NG ) {
				shutdown( iNewSockFd, SHUT_RDWR );
				close( iNewSockFd );
				pEnv->iThreadSts = MYAPP_LOG_ERRCODE_SOCKET;
				pthread_exit( &pEnv->iThreadSts );
			}
		}

		close( iNewSockFd );
	}

printf("Thread end\n");

	return( NULL );
}

/******************************************************************************/
/*�@�� �� ���@�FJD112SocketRead()											  */
/*�@�@�\�T�v�@�F�\�P�b�g�f�[�^�ǂݍ���										  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����Fint		 iSockFd	�\�P�b�gFD								  */
/*�@�@��R�����Fint		 iSize		�o�b�t�@�T�C�Y							  */
/*�@�@��S�����FJD112Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@�@��Q�����Fchar	 *pBuff		�ǂݍ��ݗp�o�b�t�@						  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int JD112SocketRead(int iSockFd, char *pBuff, int iSize, JD112Env *pEnv)
{
	int			iLoop;
	int			iSts;
	int			iRet = RTN_NG;

	for ( iLoop = 0; iLoop < pEnv->iRetryCnt; iLoop++ ) {
		memset( pBuff, 0, iSize );
		
		iSts = read( iSockFd, pBuff, iSize );
		if ( iSts < 0 ) {
			if ( errno == EINTR ) {
				continue;
			}
		} else {
			iRet = RTN_OK;
			break;
		}
	}

	return( iRet );
}

/******************************************************************************/
/*�@�� �� ���@�FJD112SocketWrite()											  */
/*�@�@�\�T�v�@�F�\�P�b�g�f�[�^��������										  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����Fint		 iSockFd	�\�P�b�gFD								  */
/*�@�@��R�����Fint		 iSize		�o�b�t�@�T�C�Y							  */
/*�@�@��S�����FJD112Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@�@��Q�����Fchar	 *pBuff		�ǂݍ��ݗp�o�b�t�@						  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int JD112SocketWrite(int iSockFd, char *pBuff, int iSize, JD112Env *pEnv)
{
	int			iLoop;
	int			iSts;
	int			iRet = RTN_NG;

	for ( iLoop = 0; iLoop < pEnv->iRetryCnt; iLoop++ ) {
		iSts = write( iSockFd, pBuff, iSize );
		if ( iSts < 0 ) {
			if ( errno == EINTR ) {
				continue;
			}
		} else {
			iRet = RTN_OK;
			break;
		}
	}

	return( iRet );
}

/******************************************************************************/
/*�@�� �� ���@�FsFncShmCrt()												  */
/*�@�@�\�T�v�@�F���L����������												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FJD112Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F�Ȃ�														  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
static int sFncShmCrt( JD112Env *pEnv )
{
	int	 *shmData;

	// �擾
	pEnv->shm_Id = shmget( (key_t)pEnv->shm_Key,
							JD112_SHM_SIZE,
							0666 | IPC_CREAT );
	if ( pEnv->shm_Id < 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_SHM_GET;
		return( RTN_NG );
	}

	// �A�^�b�`
	shmData = ( int * ) shmat( pEnv->shm_Id, 0 , 0 );
	if ( shmData == ( int * )-1 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_SHM_AT;
		return( RTN_NG );
	}
loging ( "stocker : ���L������[CRT] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n",
		 pEnv->shm_Key, pEnv->shm_Id, *shmData, shmData );

	// �l�ݒ�
	*shmData = 0;

	// �f�^�b�`
	if ( shmdt( shmData ) == -1 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_SHM_DT;
		return( RTN_NG );
	}

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FsFncShmGet()												  */
/*�@�@�\�T�v�@�F���L�������擾												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FJD112Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@�@��Q�����Fint *pshmData		�l										  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
static int sFncShmGet( JD112Env *pEnv, int *pshmData )
{
	int	 *shmData;

	// 
	if ( pshmData == NULL ) {
		// �ُ�I��	LOG
		return( RTN_NG );
	}

	// �A�^�b�`
	shmData = ( int * ) shmat( pEnv->shm_Id, 0 , 0 );
	if ( shmData == ( int * )-1 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_SHM_AT;
		return( RTN_NG );
	}

	// �l�ݒ�
	*pshmData = *shmData;

loging ( "stocker : ���L������[GET] shmKey[%d]-ID[%d]-Data[%d]-Data2[%d]-Add[%x]\n",
		 pEnv->shm_Key, pEnv->shm_Id, shmData[0], shmData[1], shmData );
	// �f�^�b�`
	if ( shmdt( shmData ) == -1 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_SHM_DT;
		return( RTN_NG );
	}

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FsFncShmDel()												  */
/*�@�@�\�T�v�@�F���L�������폜												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FJD112Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
static int sFncShmDel( JD112Env *pEnv )
{
	int	 *shmData;

loging ( "%s : ���L������[DEL] shmKey[%d]-ID[%d]\n",
		 MYAPP_APP_NAME, pEnv->shm_Key, pEnv->shm_Id);
	// �폜
	if ( shmctl( pEnv->shm_Id, IPC_RMID, NULL) < 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = JD112_STSCODE_ERR_SHM_DEL;
		return( RTN_NG );
	}
	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�F_sFncEnvDip()												  */
/*�@�@�\�T�v�@�F�v���O�������ϐ��o�͊֐��y�g���[�X�p�z					  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FJD112Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�F����														  */
/******************************************************************************/
static void _sFncEnvDip( JD112Env *pEnv )
{
//#if defined ( _TRACE )
	loging( "########## JD112 - _sFncEnvDip ##########\n" );
	loging( "\t%s : [%s]\n", JD112_PRM_DBNAME,		 pEnv->cDBName );
	loging( "\t%s : [%s]\n", JD112_PRM_DBUSER,		 pEnv->cDBUser );
	loging( "\t%s : [%s]\n", JD112_PRM_DBPAWD,		 pEnv->cDBPawd );
	loging( "\t%s : [%s]\n", JD112_PRM_SLEEP_SEC,	  pEnv->iSleepSec );
	loging( "\t%s : [%s]\n", JD112_PRM_SHM_KEY,	pEnv->shm_Key );
	loging( "\t%s : [%s]\n", JD112_PRM_FILE_DBG,	pEnv->cDebugLogName );
	loging( "\t%s : [%s]\n", JD112_PRM_FILE_TR,	pEnv->cTraceLogName );
	loging( "\t%s : [%s]\n", JD112_PRM_FILE_ACS,	pEnv->cAccessLogName );
	loging( "\t%s : [%s]\n", JD112_PRM_FILE_ERR,	pEnv->cErrorLogName );
	loging( "\t%s : [%s]\n", JD112_PRM_UP_ID,		pEnv->cUpdateId );
	loging( "\t%s : [%s]\n", JD112_PRM_UP_NM,		pEnv->cUpdateName );
	loging( "\t%s : [%s]\n", JD112_PRM_PROC_MD,	pEnv->proc_mode );
	loging( "########## JD112 - _sFncEnvDip ##########\n" );
//#endif
}

/******************************************************************************/
/*�@�� �� ���@�FsFncPutLog()												  */
/*�@�@�\�T�v�@�F�A�v���P�[�V�������O�o��									  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����Fchar *	  �ҏW������										*/
/*�@�o�@�@�́@�F															  */
/*�@���A���@�F����														  */
/******************************************************************************/
void sFncPutLog( LOG_TRCKIND peTrcKind, char * pcSrcName, char * pcFncName, int plLineNo, char * pcExeFlg, char * pcErrCode, char * pcfmt, ... )
{
	va_list  ap;
	char	 cMsg[1024];

	// ���O�����l�ݒ�
	gstLogMem.eTrcKind = peTrcKind;
	//strcpy( gstLogMem.pcSrcName, pcSrcName );
	strcpy( gstLogMem.pcFncName, pcFncName );
	//gstLogMem.lLineNo = plLineNo;
	strcpy( gstLogMem.pcExeFlg,  pcExeFlg );
	strcpy( gstLogMem.pcErrCode, pcErrCode );
	va_start( ap, pcfmt );
	vsprintf( gstLogMem.pcMsg, pcfmt, ap );
	va_end( ap );

	// ���O�o��
	_ZbmlPutLog( &gstLogMem, pcSrcName, plLineNo);
}

/******************************************************************************/
/*�@�� �� ���@�Fmain()														  */
/*�@�@�\�T�v�@�F�f�[�^�]���������C��										  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����Fint argc			�v���O����������						  */
/*�@�@��Q�����Fchar *argv[]		�v���O��������							  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		0		�F ����											  */
/*�@�@�@�@�@�@		1�ȏ�	�F �ُ�											  */
/******************************************************************************/
int main( int argc, char *argv[] )
{
	JD112Env	stEnv;
    if ( daemon ( 1, 0 ) < 0 ) {
        exit ( 9 ) ;
    }

	// ��������
	if ( initFunction( argc, argv, &stEnv )  != 0 ) {
		fprintf( stderr, "%s : Error initFunction [%d]\n",
				 MYAPP_APP_NAME, gintErrorCode );
		exit( 9 );
	}
	_sFncEnvDip( &stEnv );

	// �又��
	if ( mainFunction( &stEnv )  != 0 ) {
		fprintf( stderr, "%s : Error mainFunction [%d]\n",
				 MYAPP_APP_NAME, gintErrorCode );
		exit( 9 );
	}

	// �I������
	endFunction( &stEnv );
	fprintf( stderr, "%s : endFunction [%d]\n",
			 MYAPP_APP_NAME, gintErrorCode );
}


