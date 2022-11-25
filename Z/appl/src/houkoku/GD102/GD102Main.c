/********************************************************************/
/*																	*/
/*		�a�l�k�l���������V�X�e��									*/
/*																	*/
/*		�V�X�e����	�F������V�X�e��								*/
/*		�t�@�C����	�FGD102Main.c									*/
/*		�T�v		�F���ʕ񍐃t�@�C���쐬����						*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	�쐬��			���O			�C�����e				*/
/* ---------------------------------------------------------------- */
/*  1.00	2006/02/27		H.Suyama		Create					*/
/*  1.01	2006/04/05		H.Suyama		HKKSTDH��TNSSTDH		*/
/*      	          		        		HKKEDDH��TNSEDDH		*/
/*  1.02	2006/04/13		H.Suyama		�t�@�C�����݃`�F�b�N��	*/
/*      	          		        		���g���C�����ǉ�		*/
/*  1.03	2006/04/21		INTEC   		�]���G���[�Ή�          */
/*                            	            stat�ɂ͌�󔒖�FILE�n��*/
/********************************************************************/

/********************************************************************/
/*	�C���N���[�h�錾												*/
/********************************************************************/
#include <time.h>
#include <sys/stat.h>
#include <errno.h>
#include "bml_date.h"
#include "bmllog.h"
#include "bmlprm.h"
#include "GD102Main.h"
#include "GD102Hkkknri.h"

/******************************************************************************/
/* Define��`																  */
/******************************************************************************/
// TRACE
#if defined ( _TRACE )
#define malloc(a)   _malloc(a, __FILE__, __LINE__)
#define free(p)	 _free(p, __FILE__, __LINE__)
#endif

#define      isAscii(c)      (((c) >= 0x20 && (c) <= 0x7e) ? 1 : 0)

/******************************************************************************/
/* �O���[�o���錾															  */
/******************************************************************************/
GD102_STSCODE		gintErrorCode;
struct stcLogMember	gstLogMem;
char				gcLogMsg[256];				// 1.03 INTEC ADD

/******************************************************************************/
/*�@�� �� ���@�FGD102ConvTimestamp()										  */
/*�@�@�\�T�v�@�F�����ϊ��֐�												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FULONG ulTm			����									  */
/*�@�o�@�@�́@�F															  */
/*�@�@��Q�����Fchar *pDest			�ϊ��㕶����							  */
/*�@�@�@�@�@�@						YYYY-MM-DD-HH.MM.SS.000000				  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
void GD102ConvTimestamp(ULONG ulTm, char *pDest)
{
	struct tm	*tm;

	tm = localtime((long *)&ulTm);
	sprintf( pDest, "%04d-%02d-%02d-%02d.%02d.%02d.000000",
			 tm->tm_year + 1900,
			 tm->tm_mon + 1,
			 tm->tm_mday,
			 tm->tm_hour,
			 tm->tm_min,
			 tm->tm_sec );
}

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
char		*src_cp;
{
static char	value[256];     			/* �W�J�㕶���� */
    char	*dst_cp;        			/* �W�J�㕶���� */
    char	buf[256];       			/* �����ϐ� */
    char	*env_cp;        			/* �����ϐ� */

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
/*�@�@��R�����FGD102Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int initFunction( int argc, char *argv[], GD102Env *pEnv )
{
	char	cPrmBuf[256];
	char	*lc_login;

	// ������
		// 1.03 INTEC ADD
	memset( gcLogMsg, '\0',	sizeof( gcLogMsg ));
	// �G���[�X�e�[�^�X�ύX
	gintErrorCode = 0;
	// �v���O�������ϐ�������
	memset( pEnv, '\0', sizeof( GD102Env ) );

	// ���O�I�[�v��
	// 1.03 INTEC DELL ���ϐ��W�J��̒l��n��
/*	
DEL	if( ZbmlOpenLog( MYAPP_LOGINIFILE ) != 0 ) {
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
	sFncPutLog( TRCKIND_TRACE, __FILE__, "initFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�v���O�����N��" );

/*
	// �������`�F�b�N
	if ( argc != 2 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD102_STSCODE_ERR_USEGE;
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
		gintErrorCode = GD102_STSCODE_ERR_PRM_FILE;
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmOpen", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"�p�����[�^�t�@�C���̃I�[�v���Ɏ��s���܂���[%s]", pEnv->pcFileNamePRM );
		return( RTN_NG );
	}

	// �f�[�^�x�[�X�ڑ���
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DBNAME,
						 pEnv->cDBName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���O�C�����[�U
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DBUSER,
						pEnv->cDBUser ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���O�C���p�X���[�h
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DBPAWD,
						pEnv->cDBPawd ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// HULFT���s�t�@�C���f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_HULFTBIN,
						pEnv->cDirHULFTBin ) != 0 ) {
		// �ُ�I��     LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���ʕ񍐃t�@�C��REQUEST�f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_REQ_KKA,
						pEnv->cDirReqKKA ) != 0 ) {
		// �ُ�I�� LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �˗��v���t�@�C��REQUEST�f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_REQ_IRAI,
						pEnv->cDirReqIRAI ) != 0 ) {
		// �ُ�I�� LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �������ʗv���t�@�C��REQUEST�f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_REQ_BUNC,
						pEnv->cDirReqBUNC ) != 0 ) {
		// �ُ�I�� LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���T�e���C�g���ʗv���t�@�C��REQUEST�f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_REQ_OTHERKKA,
						pEnv->cDirReqOTHERKKA ) != 0 ) {
		// �ُ�I�� LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���ʕ񍐃t�@�C��OK�f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_OK_KKA,
						pEnv->cDirOkKKA ) != 0 ) {
		// �ُ�I�� LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �˗��v���t�@�C��OK�f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_OK_IRAI,
						pEnv->cDirOkIRAI ) != 0 ) {
		// �ُ�I�� LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �������ʗv���t�@�C��OK�f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_OK_BUNC,
						pEnv->cDirOkBUNC ) != 0 ) {
		// �ُ�I�� LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���T�e���C�g���ʗv���t�@�C��OK�f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_OK_OTHERKKA,
						pEnv->cDirOkOTHERKKA ) != 0 ) {
		// �ُ�I�� LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���ʕ񍐃t�@�C��ERR�f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_ERR_KKA,
						pEnv->cDirErrKKA ) != 0 ) {
		// �ُ�I�� LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �˗��v���t�@�C��ERR�f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_ERR_IRAI,
						pEnv->cDirErrIRAI ) != 0 ) {
		// �ُ�I�� LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �������ʗv���t�@�C��ERR�f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_ERR_BUNC,
						pEnv->cDirErrBUNC ) != 0 ) {
		// �ُ�I�� LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���T�e���C�g���ʗv���t�@�C��ERR�f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_DIR_ERR_OTHERKKA,
						pEnv->cDirErrOTHERKKA ) != 0 ) {
		// �ُ�I�� LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// HULFT���M�t�@�C����
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_SEND_FILENAME,
						pEnv->cSendFileName ) != 0 ) {
		// �ُ�I�� LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// HULFT���MOK�m�F�t�@�C����
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_SEND_FILEOK,
						pEnv->cSendFileOK ) != 0 ) {
		// �ُ�I�� LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// HULFT���MNG�m�F�t�@�C����
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_SEND_FILENG,
						pEnv->cSendFileNG ) != 0 ) {
		// �ُ�I�� LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// HULFT���M�t�@�C��ID
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_HULFT_FILEID,
						pEnv->cHULFTFileID ) != 0 ) {
		// �ُ�I��     LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// HULFT���s���ʑ҂�����
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_INTERVAL,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iInterval= atoi( cPrmBuf );
	// ���M���g���C��
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_SEND_RETRY,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iSendRetry= atoi( cPrmBuf );
	// ���M�R�}���h���g���C��
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_CMD_RETRY,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iCmdRetry= atoi( cPrmBuf );
	// ���ʃ`�F�b�N�R�}���h���g���C��
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_RESULT_RETRY,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iResultRetry= atoi( cPrmBuf );
	// �f�o�b�O���O�t�@�C��
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_FILE_DBG,
						pEnv->cDebugLogName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �g���[�X���O�t�@�C��
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_FILE_TR,
						pEnv->cTraceLogName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �A�N�Z�X���O�t�@�C��
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_FILE_ACS,
						pEnv->cAccessLogName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �G���[���O�t�@�C��
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_FILE_ERR,
						pEnv->cErrorLogName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���L�������L�[�擾
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_SHM_KEY,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->shm_Key = atoi( cPrmBuf );
	// �X���[�v���ԁi�b�j�擾
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_SLEEP_SEC,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iSleepSec= atoi( cPrmBuf );
	// �X�V��ID
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_UP_ID,
						pEnv->cUpdateId ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �X�V�Җ�
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_UP_NM,
						pEnv->cUpdateName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���s���[�h
	if ( ZbmlPrmGetVal( pEnv->bp, GD102_PRM_PROC_MD,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD102_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->proc_mode= atoi( cPrmBuf );

	// �p�����[�^�t�@�C���N���[�Y
	ZbmlPrmClose( pEnv->bp );

	// ���L����������
	if ( sFncShmCrt( pEnv ) != RTN_OK ) {
		return( RTN_NG );
	}

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
/*�@�@��P�����FGD102Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int mainFunction( GD102Env *pEnv )
{
	int			iRet;
	int			li_stopFlg = 0;

	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	if( iRet = ZdbConnect( pEnv->cDBName,
						   pEnv->cDBUser,
						   pEnv->cDBPawd ) ) {
		// �ُ�I��	LOG
		//	1.03 printf -> LOG
		sprintf( gcLogMsg,	"ZdbConnect error (%d)", iRet);
		sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_DB, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("ZdbConnect error (%d)\n", iRet);
*/
		return( RTN_NG );
	}

	// �񍐊Ǘ����e�[�u���Ď�
	// �i�v���[�v�A��~�R�}���h�ŏI��
	while ( 1 ) {
		// ��~�R�}���h�m�F
		if ( sFncShmGet( pEnv, &li_stopFlg ) != RTN_OK ) {
				//	1.03 printf -> LOG
				sprintf( gcLogMsg,	"sFncShmGet error [%d]", gintErrorCode );
				sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_ETC, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("sFncShmGet error\n");
*/
			return( RTN_NG );
		}
		if ( li_stopFlg == 1 ) {
			break;
		}

		// ���ʕ񍐃t�@�C���̑��M
		GD102SendKekkaFile( pEnv );

		// ���T�e���C�g���ʗv�����̑��M
		GD102SendOtherKkaFile( pEnv );

		// �˗����ڗv�����̑��M
		GD102SendIraiFile( pEnv );

		// �������ʗv�����̑��M
		GD102SendBunchuFile( pEnv );

		// �X���[�v
		sleep( pEnv->iSleepSec );
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
/*�@�@��P�����FGD102Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�F�Ȃ�														  */
/******************************************************************************/
void endFunction( GD102Env *pEnv )
{
	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "endFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");
	// ���L�������폜
	if ( sFncShmDel( pEnv ) != RTN_OK ) {
		//	1.03 LOG
		sprintf( gcLogMsg,	"sFncShmDel error (%d)", gintErrorCode );
		sFncPutLog( TRCKIND_WARNING, __FILE__, "endFunction", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_ETC, gcLogMsg );
		return;
	}

	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "endFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");
}

/******************************************************************************/
/*�@�� �� ���@�FGD102UpdateHkkknriSts()										  */
/*�@�@�\�T�v�@�F�񍐊Ǘ����G���[�X�V										  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FHkkknri *pHkkknri	�񍐊Ǘ������\����					  */
/*�@�@��Q�����Fchar *pHkkjkflg		�񍐏󋵃t���O							  */
/*�@�@��R�����Fchar *pHkkerrcode	�񍐃G���[�R�[�h						  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�F�Ȃ�														  */
/******************************************************************************/
void GD102UpdateHkkknriSts( Hkkknri *pHkkknri, char *pHkkjkflg, char *pHkkerrcode )
{
	int			iRet;

	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102UpdateHkkknriSts", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	// �񍐊Ǘ������X�V
	ZbmlInfocpy( pHkkknri->hkkjkflg, pHkkjkflg, sizeof( pHkkknri->hkkjkflg ) );
	ZbmlInfocpy( pHkkknri->hkkerrcode, pHkkerrcode, sizeof( pHkkknri->hkkerrcode ) );

	// �񍐊Ǘ������X�V
	iRet = ZdbHkkknriGD102Update( pHkkknri );
	if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
		// ���[���o�b�N
		ZdbRollback();
		// �ُ�I��	LOG
			//	1.03 printf -> LOG
		sprintf( gcLogMsg,	"ZdbHkkknriGD102Update error (%d)", iRet );
		sFncPutLog( TRCKIND_WARNING, __FILE__, "GD102UpdateHkkknriSts", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_DB, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("ZdbHkkknriGD102Update error (%d)\n", iRet);
*/
	} else {
		// �R�~�b�g
		ZdbCommit();
	}

	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102UpdateHkkknriSts", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");
}

/******************************************************************************/
/*�@�� �� ���@�FGD102SendFile()												  */
/*�@�@�\�T�v�@�F���ʕ񍐃t�@�C�����M										  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FGD102Env *pEnv		�v���O�������\����					  */
/*�@�@��Q�����Fchar *pFileName		���M�t�@�C����							  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int GD102SendFile(GD102Env *pEnv, char *pFileName)
{
	int				iRet;
	int				iLoop;
	char			cCmdBuff[256];
	char			iRetryLoop;
	char			iCmdRetryLoop;
	int				iResult;
	struct stat		stStat;

	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102SendFile", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	// ���M�Ώۃt�@�C����HULFT���M�p�t�@�C���ɃR�s�[
	memset( cCmdBuff, 0, sizeof( cCmdBuff ) );
	sprintf( cCmdBuff, "cp -p %s %s", pFileName, pEnv->cSendFileName );
	system( cCmdBuff );
	
	iResult = RTN_NG;
	for ( iRetryLoop = 0; iRetryLoop < pEnv->iSendRetry; iRetryLoop++ ) {
		// ���M��ԁiSEND_OK,SEND_NG�j���폜
		if ( ( stat( pEnv->cSendFileOK, &stStat ) ) == 0 ) {
			remove( pEnv->cSendFileOK );
		}
		if ( ( stat( pEnv->cSendFileNG, &stStat ) ) == 0 ) {
			remove( pEnv->cSendFileNG );
		}
		
		// HULFT�ő��M
		memset( cCmdBuff, 0, sizeof( cCmdBuff ) );
		sprintf( cCmdBuff, "%s/utlsend -f %s",
				 pEnv->cDirHULFTBin,
				 pEnv->cHULFTFileID );
		for ( iCmdRetryLoop = 0; iCmdRetryLoop < pEnv->iCmdRetry; iCmdRetryLoop++ ) {
			iRet = system( cCmdBuff );
			// �R�}���h������Ɏ��s���ꂽ�甲����
			if ( iRet == 0 )
				break;

			sleep( 20 );
		}
		// �R�}���h���s���s�Ȃ�Δ�����
		if ( iRet != 0 ) {
			//	1.03 printf -> LOG
			sprintf( gcLogMsg,	"�R�}���h���s���s:[%s]", cCmdBuff);
			sFncPutLog( TRCKIND_WARNING, __FILE__,"GD102SendFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_ETC, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("�R�}���h���s���s:[%s]\n", cCmdBuff);
*/
			break;
		}

		// SEND_OK or SEND_NG��҂�
		sleep( 3 );
		for ( iLoop = 0; iLoop < pEnv->iResultRetry; iLoop++ ) {
			// SEND_OK�m�F
			if ( ( stat( pEnv->cSendFileOK, &stStat ) ) == 0 ) {
				iResult = RTN_OK;
				remove( pEnv->cSendFileOK );
				break;
			}

			// SEND_NG�m�F
			if ( ( stat( pEnv->cSendFileNG, &stStat ) ) == 0 ) {
				remove( pEnv->cSendFileNG );
				break;
			}

			sleep( pEnv->iInterval );
		}
		if ( iResult == RTN_OK )
			break;

			//	1.03 printf -> LOG
			sprintf( gcLogMsg,"���M��� SEND_OK or SEND_NG �҂�[%d�b]����", 
						iLoop * pEnv->iInterval );
			sFncPutLog( TRCKIND_TRACE, __FILE__,"GD102SendFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_APP, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("���M��� SEND_OK or SEND_NG �҂�[%d�b]����\n",
DEL 	   iLoop * pEnv->iInterval );
*/
	}
 
	// HULFT���M�p�t�@�C�����폜
	memset( cCmdBuff, 0, sizeof( cCmdBuff ) );
	sprintf( cCmdBuff, "rm %s", pEnv->cSendFileName );
	system( cCmdBuff );

	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102SendFile", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");

	return( iResult );
}

/******************************************************************************/
/*�@�� �� ���@�FGD102SendKekkaFile()										  */
/*�@�@�\�T�v�@�F���ʕ񍐃t�@�C�����M										  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FGD102Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int GD102SendKekkaFile(GD102Env *pEnv)
{
	int				iRet;
	char			cFileName[PATH_MAX + 1];
	int				iLoop;
	Hkkknri			*pHkkknriArrayOut;
	int				iHkkknriNumOut;
	int				iHkkknriLoop;
	ULONG			ulSt;
	ULONG			ulEd;
	char			cTimestamp[27];
	char			cCmdBuff[256];
	struct stat		stStat;
// 2006-04-13 H.Suyama Add Start
	char			iRetryLoop;
// 2006-04-13 H.Suyama Add End

	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102SendKekkaFile", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	// �񍐊Ǘ���񌟍�
	iRet = ZdbHkkknriGD102SelectAll( &pHkkknriArrayOut, &iHkkknriNumOut );
	if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
		//�ُ�I��
		//���O�o��
		//	1.03 printf -> LOG
		sprintf( gcLogMsg, "ZdbHkkknriGD102SelectAll error (%d)\n", iRet );
		sFncPutLog( TRCKIND_WARNING, __FILE__,"GD102SendKekkaFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_DB, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("ZdbHkkknriGD102SelectAll error (%d)\n", iRet);
*/
		return( RTN_NG );
	}

	// �񍐊Ǘ������P��������
	for ( iHkkknriLoop = 0;
		  iHkkknriLoop < iHkkknriNumOut;
		  iHkkknriLoop++ ) {
		// �]���J�n�������擾
		time( (long *)&ulSt );

		// ���M�t�@�C�����̐���
/* 1.03 INTEDE DELL
DEL		sprintf( cFileName, "%s/%s",
DEL				 pEnv->cDirReqKKA,
DEL				 pHkkknriArrayOut[iHkkknriLoop].hkkflnm );
*/
			// 1.03 ���M�t�@�C�����͌��SPACE��CUT����
		sprintf( cFileName, "%s/%.*s",
				 pEnv->cDirReqKKA,
				 strcspn( pHkkknriArrayOut[iHkkknriLoop].hkkflnm , " " ) ,
				 pHkkknriArrayOut[iHkkknriLoop].hkkflnm );
		errno=0;

		// �t�@�C���̑��݊m�F
// 2006-04-13 H.Suyama Change Start
#if 0
//		if ( ( stat( cFileName, &stStat ) ) != 0 ) {
//			// �ُ�I��	LOG
//			gintErrorCode = GD102_STSCODE_ERR_FR_FILE ;
//printf("file not exist:[%s]\n", cFileName);
//			// �񍐊Ǘ������X�V
//			GD102UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
//									GD102_DB_HKKJKFLG_ERRSEND,
//									GD102_DB_HKKERRCODE_NOFILE );
//
//			continue;
//		}
#else
		for ( iRetryLoop = 0; iRetryLoop < pEnv->iCmdRetry; iRetryLoop++ ) {
			iRet = stat( cFileName, &stStat );
			if ( iRet == 0 )
				break;
			sleep( 1 );
		}

		if ( iRet != 0 ) {
			// �ُ�I��	LOG
			gintErrorCode = GD102_STSCODE_ERR_FR_FILE ;

			//	1.03 printf -> LOG
			sprintf( gcLogMsg, "file not exist:[%s] err[%d]", cFileName, errno);
			sFncPutLog( TRCKIND_WARNING, __FILE__,"GD102SendKekkaFile",__LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_APP, gcLogMsg );
/* 1.03 INTEC DEL ****************************************
printf("file not exist:[%s]\n", cFileName);
switch ( iRet ) {
case EBADF:
	printf("stat�G���[�R�[�h:[EBADF],filedes ���s���B\n");
case ENOENT:
	printf("stat�G���[�R�[�h:[ENOENT],file_name �̃p�X���������݂��Ȃ����A�p�X���󕶎���ł���B\n");
case ENOTDIR:
	printf("stat�G���[�R�[�h:[ENOTDIR],�p�X�̐������f�B���N�g���ł͂Ȃ��B\n");
case ELOOP:
	printf("stat�G���[�R�[�h:[ELOOP],�p�X����������ۂɑ��������V���{���b�N�E�����N�����߂���B\n");
case EFAULT:
	printf("stat�G���[�R�[�h:[EFAULT],�A�h���X���Ԉ���Ă���B\n");
case EACCES:
	printf("stat�G���[�R�[�h:[EACCES],�����Ȃ��B\n");
case ENOMEM:
	printf("stat�G���[�R�[�h:[ENOMEM],�J�[�l���̃�����������Ȃ��B\n");
case ENAMETOOLONG:
	printf("stat�G���[�R�[�h:[ENAMETOOLONG],�t�@�C���������߂���B\n");
default:
	printf("stat�G���[�R�[�h:[%d],�G���[���e�s��\n", iRet);
}
************************************************************* */
			// �񍐊Ǘ������X�V
			GD102UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
									GD102_DB_HKKJKFLG_ERRSEND,
									GD102_DB_HKKERRCODE_NOFILE );

			continue;
		}
#endif
// 2006-04-13 H.Suyama Change End

		// �t�@�C�����M
		if ( GD102SendFile( pEnv, cFileName ) == RTN_OK ) {
			//	1.03 printf -> LOG
			sprintf( gcLogMsg, "HULFT���MOK:[%s]", cFileName);
			sFncPutLog( TRCKIND_TRACE, __FILE__,"GD102SendKekkaFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("HULFT���MOK:[%s]\n", cFileName);
*/
			// �t�@�C����OK�f�B���N�g���Ɉړ�
			memset( cCmdBuff, 0, sizeof( cCmdBuff ) );
			sprintf( cCmdBuff, "mv %s %s",
					 cFileName,
					 pEnv->cDirOkKKA );
			system( cCmdBuff );
		} else {
			//	1.03 printf -> LOG
			sprintf( gcLogMsg, "HULFT���MNG:[%s]", cFileName );
			sFncPutLog( TRCKIND_WARNING, __FILE__,"GD102SendKekkaFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_APP, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("HULFT���MNG:[%s]\n", cFileName);
*/
			// �ُ�I��	LOG
			gintErrorCode = GD102_STSCODE_ERR_FR_FILE ;
			// �t�@�C����ERR�f�B���N�g���Ɉړ�
			memset( cCmdBuff, 0, sizeof( cCmdBuff ) );
			sprintf( cCmdBuff, "mv %s %s",
					 cFileName,
					 pEnv->cDirErrKKA );
			system( cCmdBuff );
			
			// �񍐊Ǘ������X�V
			GD102UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
									GD102_DB_HKKJKFLG_ERRSEND,
									GD102_DB_HKKERRCODE_SENDNG );
			continue;
		}

		// �]�������������擾
		time( (long *)&ulEd );

		// �]���J�n����
		GD102ConvTimestamp( ulSt, cTimestamp );
// 2006-04-05 H.Suyama Change Start
#if 0
//		ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkstdh,
//					 cTimestamp,
//					 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkstdh ) );
#else
		ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].tnsstdh,
					 cTimestamp,
					 sizeof( pHkkknriArrayOut[iHkkknriLoop].tnsstdh ) );
#endif
// 2006-04-05 H.Suyama Change End
		// �]����������
		GD102ConvTimestamp( ulEd, cTimestamp );
// 2006-04-05 H.Suyama Change Start
#if 0
//		ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkeddh,
//					 cTimestamp,
//					 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkeddh ) );
#else
		ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].tnseddh,
					 cTimestamp,
					 sizeof( pHkkknriArrayOut[iHkkknriLoop].tnseddh ) );
#endif
// 2006-04-05 H.Suyama Change End
		// �񍐏󋵃t���O
		if ( strcmp( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg, GD102_DB_HKKJKFLG_SEND_DBERR ) == 0) {
			ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg,
						 GD102_DB_HKKJKFLG_ERRFILE,
						 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg ) );
		} else {
			ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg,
						 GD102_DB_HKKJKFLG_DONE,
						 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg ) );
		}
		// ���X�V�����͊֐����Őݒ�

		// �񍐊Ǘ������X�V
		iRet = ZdbHkkknriGD102Update( &pHkkknriArrayOut[iHkkknriLoop] );
		if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
			// ���[���o�b�N
			ZdbRollback();
			// �ُ�I��	LOG
			//	1.03 printf -> LOG
			sprintf( gcLogMsg, "ZdbHkkknriGD102Update error (%d)\n", iRet);
			sFncPutLog( TRCKIND_WARNING, __FILE__,"GD102SendKekkaFile", __LINE__,
						EXEFLG_UPD, MYAPP_LOG_ERRCODE_DB, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("ZdbHkkknriGD102Update error (%d)\n", iRet);
*/
			return( RTN_NG );
		}

		// �R�~�b�g
		ZdbCommit();
	}

	// �񍐊Ǘ��������
	ZbmlFree( pHkkknriArrayOut );

	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102SendKekkaFile", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FGD102BunchuFileFilter()										  */
/*�@�@�\�T�v�@�F�f�B���N�g�������p�̃t�@�C���t�B���^(�R�[���o�b�N)			  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����Fstruct dirent *pDirEnt	�f�B���N�g���G���g��				  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		0	: �ΏۊO�t�@�C��									  */
/*�@�@�@�@�@�@		1	: �Ώۃt�@�C��										  */
/******************************************************************************/
int GD102BunchuFileFilter(struct dirent *pDirEnt)
{
//	BmlDate		today;
//	char		cToday[GD102_LEN_DATESHORT + 1];

	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102BunchuFileFilter", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	// �����񒷃`�F�b�N
	if ( strlen ( pDirEnt->d_name ) < GD102_LEN_BUNCFILE ) {
		return( 0 ) ;
	}

//	// �������t�擾
//	if ( ZbmlDateGetToday(&today) == FALSE ) {
//		return( 0 );
//	}
//	sprintf( cToday, "%04d%02d%02d", today.year, today.month, today.day);

//	// ���t�`�F�b�N
//	if ( memcmp ( pDirEnt->d_name, 
//				  cToday, 
//				  strlen ( cToday ) ) != 0 ) {
//		return( 0 ) ;
//	}

	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102BunchuFileFilter", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");

	return( 1 );
}

/******************************************************************************/
/*�@�� �� ���@�FGD102SendBunchuFile()										  */
/*�@�@�\�T�v�@�F�������ʗv�����t�@�C�����M								  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FGD102Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int GD102SendBunchuFile(GD102Env *pEnv)
{
	int				iFileCnt;
	int				iFileLoopIdx;
	char			cFileName[PATH_MAX + 1];
	struct dirent	**pDirEnt;
	char			cCmdBuff[256];

	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102SendBunchuFile", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	// �t�B���^�ɂ��A�������ʗv�����t�@�C���̂݌���
	if ( ( iFileCnt = scandir( pEnv->cDirReqBUNC,
							   &pDirEnt,
							   (void *)GD102BunchuFileFilter,
							   alphasort ) ) < 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD102_STSCODE_ERR_DIR;
		return( RTN_NG );
	}

	// �����������������M
	for ( iFileLoopIdx = 0; iFileLoopIdx < iFileCnt; iFileLoopIdx++ ) {
		sprintf( cFileName, "%s/%s", pEnv->cDirReqBUNC, pDirEnt[iFileLoopIdx]->d_name );

		// �t�@�C�����M
		memset( cCmdBuff, 0, sizeof( cCmdBuff ) );
		if ( GD102SendFile( pEnv, cFileName ) == RTN_OK ) {
			//	1.03 printf -> LOG
			sprintf( gcLogMsg, "HULFT���MOK:[%s]", cFileName);
			sFncPutLog( TRCKIND_WARNING, __FILE__,"GD102SendBunchuFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("HULFT���MOK:[%s]\n", cFileName);
*/
			// �t�@�C���̈ړ����OK�f�B���N�g���ɐݒ�
			sprintf( cCmdBuff, "mv %s %s",
					 cFileName,
					 pEnv->cDirOkBUNC );
		} else {
			//	1.03 printf -> LOG
			sprintf( gcLogMsg, "HULFT���MNG:[%s]", cFileName );
			sFncPutLog( TRCKIND_WARNING, __FILE__,"GD102SendBunchuFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_APP, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("HULFT���MNG:[%s]\n", cFileName);
*/
			// �ُ�I��	LOG
			gintErrorCode = GD102_STSCODE_ERR_FR_FILE ;
			// �t�@�C���̈ړ����ERR�f�B���N�g���ɐݒ�
			sprintf( cCmdBuff, "mv %s %s",
					 cFileName,
					 pEnv->cDirErrBUNC );
		}
		// �t�@�C�����ړ�
		system( cCmdBuff );
		
		// �������������
		ZbmlFree( pDirEnt[iFileLoopIdx] );
	}

	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102SendBunchuFile", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FGD102IraiFileFilter()										  */
/*�@�@�\�T�v�@�F�f�B���N�g�������p�̃t�@�C���t�B���^(�R�[���o�b�N)			  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����Fstruct dirent *pDirEnt	�f�B���N�g���G���g��				  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		0	: �ΏۊO�t�@�C��									  */
/*�@�@�@�@�@�@		1	: �Ώۃt�@�C��										  */
/******************************************************************************/
int GD102IraiFileFilter(struct dirent *pDirEnt)
{
//	BmlDate		today;
//	char		cToday[GD102_LEN_DATESHORT + 1];

	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102IraiFileFilter", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	// �����񒷃`�F�b�N
	if ( strlen ( pDirEnt->d_name )  < GD102_LEN_IRAIFILE ) {
		return( 0 ) ;
	}

//	// �������t�擾
//	if ( ZbmlDateGetToday(&today) == FALSE ) {
//		return( 0 );
//	}
//	sprintf( cToday, "%04d%02d%02d", today.year, today.month, today.day);

//	// ���t�`�F�b�N
//	if ( memcmp ( pDirEnt->d_name, 
//				  cToday, 
//				  strlen ( cToday ) ) != 0 ) {
//		return( 0 ) ;
//	}

	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102IraiFileFilter", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");

	return( 1 );
}

/******************************************************************************/
/*�@�� �� ���@�FGD102SendIraiFile()											  */
/*�@�@�\�T�v�@�F�˗����ڗv�����t�@�C�����M								  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FGD102Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int GD102SendIraiFile(GD102Env *pEnv)
{
	int				iFileCnt;
	int				iFileLoopIdx;
	char			cFileName[PATH_MAX + 1];
	struct dirent	**pDirEnt;
	char			cCmdBuff[256];

	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102SendIraiFile", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	// �t�B���^�ɂ��A�˗����ڗv�����t�@�C���̂݌���
	if ( ( iFileCnt = scandir( pEnv->cDirReqIRAI,
							   &pDirEnt,
							   (void *)GD102IraiFileFilter,
							   alphasort ) ) < 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD102_STSCODE_ERR_DIR;
		return( RTN_NG );
	}

	// �����������������M
	for ( iFileLoopIdx = 0; iFileLoopIdx < iFileCnt; iFileLoopIdx++ ) {
		sprintf( cFileName, "%s/%s", pEnv->cDirReqIRAI, pDirEnt[iFileLoopIdx]->d_name );

		// �t�@�C�����M
		memset( cCmdBuff, 0, sizeof( cCmdBuff ) );
		if ( GD102SendFile( pEnv, cFileName ) == RTN_OK ) {
			//	1.03 printf -> LOG
			sprintf( gcLogMsg, "HULFT���MOK:[%s]", cFileName);
			sFncPutLog( TRCKIND_TRACE, __FILE__,"GD102SendIraiFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("HULFT���MOK:[%s]\n", cFileName);
*/
			// �t�@�C���̈ړ����OK�f�B���N�g���ɐݒ�
			sprintf( cCmdBuff, "mv %s %s",
					 cFileName,
					 pEnv->cDirOkIRAI );
		} else {
			//	1.03 printf -> LOG
			sprintf( gcLogMsg, "HULFT���MNG:[%s]\n", cFileName );
			sFncPutLog( TRCKIND_WARNING, __FILE__,"GD102SendIraiFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_APP, gcLogMsg );
/* 1.03 INTEC DEL
DEL printf("HULFT���MNG:[%s]\n", cFileName);
*/
			// �ُ�I��	LOG
			gintErrorCode = GD102_STSCODE_ERR_FR_FILE ;
			// �t�@�C���̈ړ����ERR�f�B���N�g���ɐݒ�
			sprintf( cCmdBuff, "mv %s %s",
					 cFileName,
					 pEnv->cDirErrIRAI );
		}
		// �t�@�C�����ړ�
		system( cCmdBuff );
		
		// �������������
		ZbmlFree( pDirEnt[iFileLoopIdx] );
	}

	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102SendIraiFile", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");

	return( RTN_OK );
}

/**********************************************************************************/
/*�@�� �� ���@�FGD102OtherKkaFileFilter()					  */
/*�@�@�\�T�v�@�F�f�B���N�g�������p�̃t�@�C���t�B���^(�R�[���o�b�N)		  */
/*�@���@�@�́@�F								  */
/*�@�@��P�����Fstruct dirent *pDirEnt	�f�B���N�g���G���g��			  */
/*�@�o�@�@�́@�F								  */
/*�@���A���@�Fint								  */
/*�@�@�@�@�@�@		0	: �ΏۊO�t�@�C��				  */
/*�@�@�@�@�@�@		1	: �Ώۃt�@�C��					  */
/**********************************************************************************/
int GD102OtherKkaFileFilter(struct dirent *pDirEnt)
{
	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102OtherKkaFileFilter", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	// �����񒷃`�F�b�N
	if ( strlen ( pDirEnt->d_name )  < GD102_LEN_OTHERKKAFILE ) {
		return( 0 ) ;
	}

	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102OtherKkaFileFilter", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");

	return( 1 );
}

/**********************************************************************************/
/*�@�� �� ���@�FGD102SendOtherKkaFile()						  */
/*�@�@�\�T�v�@�F���T�e���C�g���ʗv�����t�@�C�����M				  */
/*�@���@�@�́@�F								  */
/*�@�@��P�����FGD102Env *pEnv		�v���O�������\����			  */
/*�@�o�@�@�́@�F								  */
/*�@���A���@�Fint								  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��					  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��					  */
/**********************************************************************************/
int GD102SendOtherKkaFile(GD102Env *pEnv)
{
	int		iFileCnt;
	int		iFileLoopIdx;
	char		cFileName[PATH_MAX + 1];
	struct dirent	**pDirEnt;
	char		cCmdBuff[256];

	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102SendOtherKkaFile", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	// �t�B���^�ɂ��A�˗����ڗv�����t�@�C���̂݌���
	if ( ( iFileCnt = scandir( pEnv->cDirReqOTHERKKA,
							   &pDirEnt,
							   (void *)GD102OtherKkaFileFilter,
							   alphasort ) ) < 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD102_STSCODE_ERR_DIR;
		return( RTN_NG );
	}

	// �����������������M
	for ( iFileLoopIdx = 0; iFileLoopIdx < iFileCnt; iFileLoopIdx++ ) {
		sprintf( cFileName, "%s/%s", pEnv->cDirReqOTHERKKA, pDirEnt[iFileLoopIdx]->d_name );

		// �t�@�C�����M
		memset( cCmdBuff, 0, sizeof( cCmdBuff ) );
		if ( GD102SendFile( pEnv, cFileName ) == RTN_OK ) {
			//	1.03 printf -> LOG
			sprintf( gcLogMsg, "HULFT���MOK:[%s]", cFileName);
			sFncPutLog( TRCKIND_TRACE, __FILE__,"GD102SendOtherKkaFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, gcLogMsg );
			// �t�@�C���̈ړ����OK�f�B���N�g���ɐݒ�
			sprintf( cCmdBuff, "mv %s %s",
					 cFileName,
					 pEnv->cDirOkOTHERKKA );
		} else {
			sprintf( gcLogMsg, "HULFT���MNG:[%s]\n", cFileName );
			sFncPutLog( TRCKIND_WARNING, __FILE__,"GD102SendOtherKkaFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_APP, gcLogMsg );
			// �ُ�I��	LOG
			gintErrorCode = GD102_STSCODE_ERR_FR_FILE ;
			// �t�@�C���̈ړ����ERR�f�B���N�g���ɐݒ�
			sprintf( cCmdBuff, "mv %s %s",
					 cFileName,
					 pEnv->cDirErrOTHERKKA );
		}
		// �t�@�C�����ړ�
		system( cCmdBuff );
		
		// �������������
		ZbmlFree( pDirEnt[iFileLoopIdx] );
	}

	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD102SendOtherKkaFile", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");

	return( RTN_OK );
}
/******************************************************************************/
/*�@�� �� ���@�FsFncShmCrt()												  */
/*�@�@�\�T�v�@�F���L����������												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FGD102Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F�Ȃ�														  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
static int sFncShmCrt( GD102Env *pEnv )
{
	int	 *shmData;

	// �擾
	pEnv->shm_Id = shmget( (key_t)pEnv->shm_Key,
							GD102_SHM_SIZE,
							0666 | IPC_CREAT );
	if ( pEnv->shm_Id < 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD102_STSCODE_ERR_SHM_GET;
		return( RTN_NG );
	}

	// �A�^�b�`
	shmData = ( int * ) shmat( pEnv->shm_Id, 0 , 0 );
	if ( shmData == ( int * )-1 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD102_STSCODE_ERR_SHM_AT;
		return( RTN_NG );
	}
loging ( "stocker : ���L������[CRT] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n",
		 pEnv->shm_Key, pEnv->shm_Id, *shmData, shmData );

	// �l�ݒ�
	*shmData = 0;

	// �f�^�b�`
	if ( shmdt( shmData ) == -1 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD102_STSCODE_ERR_SHM_DT;
		return( RTN_NG );
	}

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FsFncShmGet()												  */
/*�@�@�\�T�v�@�F���L�������擾												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FGD102Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@�@��Q�����Fint *pshmData		�l										  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
static int sFncShmGet( GD102Env *pEnv, int *pshmData )
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
		gintErrorCode = GD102_STSCODE_ERR_SHM_AT;
		return( RTN_NG );
	}

	// �l�ݒ�
	*pshmData = *shmData;

loging ( "stocker : ���L������[GET] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n",
		 pEnv->shm_Key, pEnv->shm_Id, *shmData, shmData );
	// �f�^�b�`
	if ( shmdt( shmData ) == -1 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD102_STSCODE_ERR_SHM_DT;
		return( RTN_NG );
	}

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FsFncShmDel()												  */
/*�@�@�\�T�v�@�F���L�������폜												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FGD102Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
static int sFncShmDel( GD102Env *pEnv )
{
	int	 *shmData;

loging ( "%s : ���L������[DEL] shmKey[%d]-ID[%d]\n",
		 MYAPP_APP_NAME, pEnv->shm_Key, pEnv->shm_Id);
	// �폜
	if ( shmctl( pEnv->shm_Id, IPC_RMID, NULL) < 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD102_STSCODE_ERR_SHM_DEL;
		//	1.03 LOG
		sprintf( gcLogMsg, "���L�������폜 error errno[%d]", errno );
		sFncPutLog( TRCKIND_WARNING, __FILE__,"sFncShmDel", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_APP, gcLogMsg );

		return( RTN_NG );
	}
	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�F_sFncEnvDip()												  */
/*�@�@�\�T�v�@�F�v���O�������ϐ��o�͊֐��y�g���[�X�p�z					  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FGD102Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�F����														  */
/******************************************************************************/
static void _sFncEnvDip( GD102Env *pEnv )
{
//#if defined ( _TRACE )
	loging( "########## GD102 - _sFncEnvDip ##########\n" );
	loging( "\t%s : [%s]\n", GD102_PRM_DBNAME,		 pEnv->cDBName );
	loging( "\t%s : [%s]\n", GD102_PRM_DBUSER,		 pEnv->cDBUser );
	loging( "\t%s : [%s]\n", GD102_PRM_DBPAWD,		 pEnv->cDBPawd );
	loging( "\t%s : [%s]\n", GD102_PRM_SLEEP_SEC,	  pEnv->iSleepSec );
	loging( "\t%s : [%s]\n", GD102_PRM_SHM_KEY,	pEnv->shm_Key );
	loging( "\t%s : [%s]\n", GD102_PRM_FILE_DBG,	pEnv->cDebugLogName );
	loging( "\t%s : [%s]\n", GD102_PRM_FILE_TR,	pEnv->cTraceLogName );
	loging( "\t%s : [%s]\n", GD102_PRM_FILE_ACS,	pEnv->cAccessLogName );
	loging( "\t%s : [%s]\n", GD102_PRM_FILE_ERR,	pEnv->cErrorLogName );
	loging( "\t%s : [%s]\n", GD102_PRM_UP_ID,		pEnv->cUpdateId );
	loging( "\t%s : [%s]\n", GD102_PRM_UP_NM,		pEnv->cUpdateName );
	loging( "\t%s : [%s]\n", GD102_PRM_PROC_MD,	pEnv->proc_mode );
	loging( "########## GD102 - _sFncEnvDip ##########\n" );
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
	GD102Env	stEnv;

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


