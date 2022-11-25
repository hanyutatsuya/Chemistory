/********************************************************************/
/*																	*/
/*		�a�l�k�l���������V�X�e��									*/
/*																	*/
/*		�V�X�e����	�F������V�X�e��								*/
/*		�t�@�C����	�FGD105Main.c									*/
/*		�T�v		�F���ʕ񍐃t�@�C���쐬����						*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	�쐬��			���O			�C�����e				*/
/* ---------------------------------------------------------------- */
/*  1.00	2006/02/27		H.Suyama		Create					*/
/*  1.01    2006/04/01      H.Suyama        �V�X�e���Ǘ����̑��M  */
/*                          �ʔԂ��擾����ɍX�V                    */
/*  1.02    2006/04/06      H.Suyama        �G���[�R�[�h�C��		*/
/*                                          �g���[���̐ݒ�l�C��	*/
/*  1.03    2006/04/06      H.Suyama        �t�@�C���ݒ���e�C��	*/
/*  1.04    2006/04/07      H.Suyama        �������R�[�h�����C��	*/
/*  1.05    2006/04/20      H.Suyama        �w�b�_�p�����[�^�P�C��	*/
/*                                          �P���̍���NULL��' '		*/
/*                                          ���ʏ󋵍ŏI��������	*/
/*											���R�[�h��'M'�ɍX�V		*/
/*  1.06    2006/05/03      INTEC.INC       �{�ݕʊ��Z�����ǉ�,LOG  */
/*  1.07    2006/06/06      INTEC.INC       �t�@�C�����]�����̍l��  */
/*  1.09    2006/07/25      INTEC.INC       �������ʂQ�͍�����ҏW  */
/*  1.10    2006/08/23      INTEC.INC       �ē]�����t�@�C�����ύX  */
/*  1.11    2006/08/29      INTEC.INC       ���ʏC��FLG��MAX����    */
/*  1.12    2006/09/04      INTEC.INC       �ۗ��ȊO�o�͌���0�̍l�� */
/*  1.13    2006/09/13      INTEC.INC       ���ʂ�commit��1000������*/
/*  1.14    2006/12/08      INTEC.INC       DB�G���[���ُ�I��������*/
/*  2.00    2009/05/19      K.Moriya        ���ʕϊ��}�X�^�Ή�      */
/********************************************************************/

/********************************************************************/
/*	�C���N���[�h�錾												*/
/********************************************************************/
#include <time.h>
#include <errno.h>							// 1.07 INTEC ADD
//#include "bml_misc.h"
#include "bml_date.h"
#include "bmllog.h"
#include "bmlprm.h"
#include "GD105Main.h"
#include "GD105Hkkknri.h"

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
GD105_STSCODE		gintErrorCode;
struct stcLogMember	gstLogMem;
char        G_msg[256];     // 1.06 ADD LogMessage
/* 2.00 2009.05.19 ���ʕϊ��}�X�^�Ή� START */
Kkaconvmst	*g_pKkaconvmst = NULL;	/* ���ʕϊ��}�X�^�\���� */
int			g_iNumOut;				/* ���ʕϊ��}�X�^�S���� */
/* 2.00 2009.05.19 ���ʕϊ��}�X�^�Ή� END */

/******************************************************************************/
/*�@�� �� ���@�FGD105ConvTimestamp()										  */
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
void GD105ConvTimestamp(ULONG ulTm, char *pDest)
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

/******************************************************************************/
/*�@�� �� ���@�FGD105ConvNumber()											  */
/*�@�@�\�T�v�@�F�˗���No�A����No�ϊ��֐�									  */
/*�@���@�@�́@�F															  */
/*�@�@��Q�����Fchar *pSrc			�ϊ��O������							  */
/*�@�@�@�@�@�@						[1][2][3][4][5][6][7][8][9][10][11]\0	  */
/*�@�o�@�@�́@�F															  */
/*�@�@��P�����Fchar *pDest			�ϊ��㕶����							  */
/*�@�@�@�@�@�@						[3][4][5] 0  0 [6][7][8][9][10][11]		  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int GD105ConvNumber(char *pDest, char *pSrc)
{
	// �|�C���^�̃`�F�b�N
	if ( pDest == NULL || pSrc == NULL ) {
		return( RTN_NG );
	}

	// �ϊ��O������̒����`�F�b�N
	if ( strlen( pSrc ) < GD105_LEN_NOITEM ) {
		return( RTN_NG );
	}

	memcpy( &pDest[GD105_POS_DESTNO1], &pSrc[GD105_POS_SRCNO1], GD105_LEN_SRCNO1 );
	memcpy( &pDest[GD105_POS_DESTNO2], GD105_DATA_STR00, strlen( GD105_DATA_STR00 ) );
	memcpy( &pDest[GD105_POS_DESTNO3], &pSrc[GD105_POS_SRCNO2], GD105_LEN_SRCNO2 );

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FGD105CopyFromLeft()											  */
/*�@�@�\�T�v�@�F�w�蕶����̍�����w�茅�����R�s�[����						  */
/*�@���@�@�́@�F															  */
/*�@�@��Q�����Fchar *pSrc			�R�s�[��������							  */
/*�@�@��R�����Fint iSize			�R�s�[����								  */
/*�@�@��S�����FBOOL bMbFlg			�}���`�o�C�g�t���O						  */
/* �@�@�@�@�@		TRUE	: �l������										  */
/* �@�@�@�@�@		FALSE	: ��������										  */
/*�@�o�@�@�́@�F															  */
/*�@�@��P�����Fchar *pDest			�R�s�[�㕶����							  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int GD105CopyFromLeft(char *pDest, char *pSrc, int iSize, BOOL bMbFlg)
{
	int	iLoop;
	int	iCopySize;

	// �|�C���^�̃`�F�b�N
	if ( pDest == NULL || pSrc == NULL ) {
		return( RTN_NG );
	}

	// �R�s�[�������񂪃R�s�[�����ɖ����Ȃ��ꍇ
	if ( strlen( pSrc ) <= iSize ) {
		// ���ׂăR�s�[����
		iCopySize = strlen( pSrc );
	} else {
		iCopySize = iSize;
		// �}���`�o�C�g���l������ꍇ
		if ( bMbFlg ) {
			// �������菈��
			for ( iLoop = 0; iLoop < iSize; iLoop++ ) {
				if ( isAscii(pSrc[iLoop]) == 0 ) {
					++iLoop;
					if ( iLoop == iLoop ) {
						--iCopySize;
						break;
					}
				}
			}
		}
	}
	memcpy( pDest, pSrc, iCopySize );

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FGD105CopyFromRight()										  */
/*�@�@�\�T�v�@�F�w�蕶����̉E����w�茅�����R�s�[����						  */
/*�@���@�@�́@�F															  */
/*�@�@��Q�����Fchar *pSrc			�R�s�[��������							  */
/*�@�@��R�����Fint iSize			�R�s�[����								  */
/*�@�@��S�����FBOOL bMbFlg			�}���`�o�C�g�t���O						  */
/* �@�@�@�@�@		TRUE	: �l������										  */
/* �@�@�@�@�@		FALSE	: ��������										  */
/*�@�o�@�@�́@�F															  */
/*�@�@��P�����Fchar *pDest			�R�s�[�㕶����							  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int GD105CopyFromRight(char *pDest, char *pSrc, int iSize, BOOL bMbFlg)
{
	int 	iTargetPos;
	int	iLoop;
	int	iCopySize;

	// �|�C���^�̃`�F�b�N
	if ( pDest == NULL || pSrc == NULL ) {
		return( RTN_NG );
	}

	// �R�s�[�������񂪃R�s�[�����ɖ����Ȃ��ꍇ
	if ( strlen( pSrc ) <= iSize ) {
		// ���ׂăR�s�[����
		iTargetPos = 0;
		iCopySize = strlen( pSrc );
	} else {
		iTargetPos = strlen( pSrc ) - iSize;
		iCopySize = iSize;
		// �}���`�o�C�g���l������ꍇ
		if ( bMbFlg ) {
			// �������菈��
			for ( iLoop = 0; iLoop < strlen( pSrc ); iLoop++ ) {
				if ( isAscii(pSrc[iLoop]) == 0 ) {
					++iLoop;
					if ( iLoop == iTargetPos ) {
						++iTargetPos;
						--iCopySize;
						break;
					}
				}
			}
		}
	}
	memcpy( pDest, &pSrc[iTargetPos], iCopySize );

	return( RTN_OK );
}

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
/*�@�@��R�����FGD105Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int initFunction( int argc, char *argv[], GD105Env *pEnv )
{
	char	cPrmBuf[256];
	char	*lc_login;

	// ������
	// �G���[�X�e�[�^�X�ύX
	gintErrorCode = 0;
	// �v���O�������ϐ�������
	memset( pEnv, '\0', sizeof( GD105Env ) );

	// ���O�I�[�v��
	// 1.06 UPD	if( ZbmlOpenLog( MYAPP_LOGINIFILE ) != 0 ) [
	lc_login= EnvRef( MYAPP_LOGINIFILE );
	if( ZbmlOpenLog( lc_login ) != 0 ) {
		return( RTN_NG );
	}

	// ���O��񏉊��ݒ�
	memset( &gstLogMem, '\0', sizeof( gstLogMem ) );
	if ( ( lc_login = getenv( "LOGNAME" ) ) != NULL ) {
		strcpy( gstLogMem.pcLoginId, lc_login );
	}
	strcpy( gstLogMem.pcAppName, MYAPP_APP_NAME );

#ifdef _TRACE
	// �J�n���O�o��
	sFncPutLog( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�v���O�����N��" );
#endif

/*
	// �������`�F�b�N
	if ( argc != 2 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_USEGE;
		sFncPutLog( TRCKIND_ERROR, __FILE__, "initFunction", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�R�}���h�p�����[�^�Ɍ�肪����܂�" );
		return( RTN_NG );
	}
*/
	// �p�����[�^�t�@�C�����ޔ�
	lc_login= EnvRef( MYAPP_LOGINIFILE );
	if ( argc >= 2 ) {
/* 1.06
DEL		pEnv->pcFileNamePRM = argv[1];
*/
		pEnv->pcFileNamePRM = EnvRef( argv[1] );
	} else {
/* 1.06
DEL		pEnv->pcFileNamePRM = MYAPP_INIFILE;
*/
		pEnv->pcFileNamePRM = EnvRef( MYAPP_INIFILE );
	}

	// �p�����[�^�t�@�C���I�[�v��
	// 1.06 UPD pEnv->bp = ZbmlPrmOpen( pEnv->pcFileNamePRM );
	pEnv->bp = ZbmlPrmOpen( pEnv->pcFileNamePRM );
	if ( pEnv->bp == NULL ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_FILE;
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZZbmlPrmOpen", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�p�����[�^�t�@�C���̃I�[�v���Ɏ��s���܂���[%s]", 
					pEnv->pcFileNamePRM );
		return( RTN_NG );
	}

	// �f�[�^�x�[�X�ڑ���
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_DBNAME,
						 pEnv->cDBName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���O�C�����[�U
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_DBUSER,
						pEnv->cDBUser ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���O�C���p�X���[�h
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_DBPAWD,
						pEnv->cDBPawd ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �񍐃f�[�^�t�@�C���o�̓f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_DIR_DATAFILE,
						pEnv->cDirDataFile ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �]���f�[�^�t�@�C���o�̓f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_DIR_TODAY,
						pEnv->cDirToday ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �]���f�[�^�t�@�C���ߋ��f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_DIR_OLDDAY,
						pEnv->cDirOldday ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �]���f�[�^�t�@�C�����M�f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_DIR_SENDFILE,
						pEnv->cDirSendFile ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �]���f�[�^�t�@�C��REQUEST�f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_DIR_SENDREQ,
						pEnv->cDirSendREQ ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �]���f�[�^�t�@�C��OK�f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_DIR_SENDOK,
						pEnv->cDirSendOK ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �]���f�[�^�t�@�C��ERR�f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_DIR_SENDERR,
						pEnv->cDirSendERR ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �f�[�^�t���[�h�c
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_DATAFLOWID,
						pEnv->cDataFlowID ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���M���h�c
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_SENDID_MOTO,
						pEnv->cSendIDMoto ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���M��h�c
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_SENDID_SAKI,
						pEnv->cSendIDSaki ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �f�o�b�O���O�t�@�C��
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_FILE_DBG,
						pEnv->cDebugLogName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �g���[�X���O�t�@�C��
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_FILE_TR,
						pEnv->cTraceLogName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �A�N�Z�X���O�t�@�C��
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_FILE_ACS,
						pEnv->cAccessLogName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �G���[���O�t�@�C��
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_FILE_ERR,
						pEnv->cErrorLogName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���L�������L�[�擾
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_SHM_KEY,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->shm_Key = atoi( cPrmBuf );
	// �X���[�v���ԁi�b�j�擾
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_SLEEP_SEC,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iSleepSec= atoi( cPrmBuf );
	// �X�V��ID
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_UP_ID,
						pEnv->cUpdateId ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �X�V�Җ�
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_UP_NM,
						pEnv->cUpdateName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���s���[�h
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_PROC_MD,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->proc_mode= atoi( cPrmBuf );

	// 1.13 ADD ���ʏ�� �ꊇCOMMIT����
	if ( ZbmlPrmGetVal( pEnv->bp, GD105_PRM_COMMIT_SU,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iCommitSu=atoi( cPrmBuf );

	// �p�����[�^�t�@�C���N���[�Y
	ZbmlPrmClose( pEnv->bp );

	// ���L����������
	if ( sFncShmCrt( pEnv ) != RTN_OK ) {
		return( RTN_NG );
	}

#ifdef _TRACE
	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "initFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function" );
#endif

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FGD105UpdateHkkknriSts()										  */
/*�@�@�\�T�v�@�F�񍐊Ǘ����G���[�X�V										  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FHkkknri *pHkkknri	�񍐊Ǘ������\����					  */
/*�@�@��Q�����Fchar *pHkkjkflg		�񍐏󋵃t���O							  */
/*�@�@��R�����Fchar *pHkkerrcode	�񍐃G���[�R�[�h						  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�F�Ȃ�														  */
/******************************************************************************/
void GD105UpdateHkkknriSts( Hkkknri *pHkkknri, char *pHkkjkflg, char *pHkkerrcode )
{
	int			iRet;

	// �񍐊Ǘ������X�V
	ZbmlInfocpy( pHkkknri->hkkjkflg, pHkkjkflg, sizeof( pHkkknri->hkkjkflg ) );
	ZbmlInfocpy( pHkkknri->hkkerrcode, pHkkerrcode, sizeof( pHkkknri->hkkerrcode ) );

	// �񍐊Ǘ������X�V
	iRet = ZdbHkkknriGD105UpdateSts( pHkkknri );
	if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
		// ���[���o�b�N
		ZdbRollback();
		// �ُ�I��	LOG
// 1.06 printf("ZdbHkkknriGD105UpdateSts error (%d)\n", iRet);
		// 1.06 �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105UpdateHkkknriSts", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"ZdbHkkknriGD105UpdateSts error [%d]", iRet );
	} else {
		// �R�~�b�g
		ZdbCommit();
	}
}

/******************************************************************************/
/*�@�� �� ���@�FmainFunction()												  */
/*�@�@�\�T�v�@�F���C�������֐�												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FGD105Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int mainFunction( GD105Env *pEnv )
{
	int			iRet;
	Sysknrmst	stSysknrmst;
	Hkkknri		*pHkkknriArrayOut;
	int			iHkkknriNumOut;
	int			iHkkknriLoop;
	Kekka		stKekkaKey;
	Kekka		*pKekkaArrayOut;
	int			iKekkaNumOut;
	ULONG		ulNow;
	ULONG		ulSt;
	ULONG		ulEd;
	char		cTimestamp[27];
	int			iHkkssknsu;
	int			iHkkhrysu;
	char		cDataFile[PATH_MAX + 1];
	int			li_stopFlg = 0;

#ifdef _TRACE
	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");
#endif

	if( iRet = ZdbConnect( pEnv->cDBName,
						   pEnv->cDBUser,
						   pEnv->cDBPawd ) ) {
		// �ُ�I��	LOG
// 1.06 DELL printf("ZdbConnect error (%d)\n", iRet);
		// 1.06 �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"ZdbConnect error [%d]", iRet );
		return( RTN_NG );
	}

/* 2.00 2009.05.19 ���ʕϊ��}�X�^�Ή� START */
	/*************************************************************************/
	/* ���ʕϊ��}�X�^�擾                                                    */
	/* �� ���ʕϊ��}�X�^��S���擾���A�O���[�o���ϐ��Ɍ����ƈꏏ�Ɋi�[����B */
	/*************************************************************************/
	iRet = mGD105_KKACONVMST_SelAll( &g_pKkaconvmst, &g_iNumOut );
	if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
		//�ُ�I��
		//���O�o��
		sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction", __LINE__,
				EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"mGD105_KKACONVMST_SelAll ERROR iRet = [%d]", iRet );
		return( RTN_NG );
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
			"g_iNumOut = [%d]", g_iNumOut );

	for (iRet = 0; iRet < g_iNumOut; iRet++)
	{
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].knsgrp     = [%s]", iRet, g_pKkaconvmst[iRet].knsgrp );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].kmkcd      = [%s]", iRet, g_pKkaconvmst[iRet].kmkcd );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].sstcd      = [%s]", iRet, g_pKkaconvmst[iRet].sstcd );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].no         = [%d]", iRet, g_pKkaconvmst[iRet].no );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].sbtkbn     = [%c]", iRet, g_pKkaconvmst[iRet].sbtkbn );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].age        = [%s]", iRet, g_pKkaconvmst[iRet].age );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].agekbn     = [%c]", iRet, g_pKkaconvmst[iRet].agekbn );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].sc         = [%s]", iRet, g_pKkaconvmst[iRet].sc );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].tj         = [%s]", iRet, g_pKkaconvmst[iRet].tj );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].tjtni      = [%c]", iRet, g_pKkaconvmst[iRet].tjtni );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].tntme      = [%s]", iRet, g_pKkaconvmst[iRet].tntme );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].tntni      = [%c]", iRet, g_pKkaconvmst[iRet].tntni );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].tnryo      = [%s]", iRet, g_pKkaconvmst[iRet].tnryo );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].tnryotni   = [%c]", iRet, g_pKkaconvmst[iRet].tnryotni );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].knskka1    = [%s]", iRet, g_pKkaconvmst[iRet].knskka1 );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].knskka2    = [%s]", iRet, g_pKkaconvmst[iRet].knskka2 );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].knskka2kbn = [%s]", iRet, g_pKkaconvmst[iRet].knskka2kbn );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].kkahskcd   = [%s]", iRet, g_pKkaconvmst[iRet].kkahskcd );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].hjkka      = [%s]", iRet, g_pKkaconvmst[iRet].hjkka );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].kaiymd     = [%s]", iRet, g_pKkaconvmst[iRet].kaiymd );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].haiymd     = [%s]", iRet, g_pKkaconvmst[iRet].haiymd );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].hnktntid   = [%s]", iRet, g_pKkaconvmst[iRet].hnktntid );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"g_pKkaconvmst[%d].ksndh      = [%s]", iRet, g_pKkaconvmst[iRet].ksndh );
	}
#endif
/* 2.00 2009.05.19 ���ʕϊ��}�X�^�Ή� END */

	// �񍐊Ǘ����e�[�u���Ď�
	// �i�v���[�v�A��~�R�}���h�ŏI��
	while ( 1 ) {
		// ��~�R�}���h�m�F
		if ( sFncShmGet( pEnv, &li_stopFlg ) != RTN_OK ) {
			// 1.06 �ُ�I��	LOG
			sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"sFncShmGet error" );
			return( RTN_NG );
		}
		if ( li_stopFlg == 1 ) {
			break;
		}

		// �񍐊Ǘ���񌟍�
		iRet = ZdbHkkknriGD105SelectAll( &pHkkknriArrayOut, &iHkkknriNumOut );
		if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
			//�ُ�I��
			//���O�o��
			// 1.06 �ُ�I��	LOG
			sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction", __LINE__,
					EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
					"ZdbHkkknriGD105SelectAll error [%d]", iRet );
			return( RTN_NG );
		}
		if ( iRet == HRC_SQL_NORMAL ) {
			// �񍐊Ǘ������P��������
			for ( iHkkknriLoop = 0;
				  iHkkknriLoop < iHkkknriNumOut;
				  iHkkknriLoop++ ) {
				// �V�X�e���Ǘ����擾
                iRet = ZdbSysknrmstSelect( &stSysknrmst );
				if ( iRet != HRC_SQL_NORMAL ) {
					// �ُ�I��	LOG
// 1.06 DELL printf("ZdbSysknrmstSelect error (%d)\n", iRet);
					// 1.06 �ُ�I��	LOG
					sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
							"ZdbSysknrmstSelect error [%d]", iRet );
					return( RTN_NG );
				}

				// �V�X�e���Ǘ����̑��M�ʔԂ�MAX�̏ꍇ�̓G���[
				if ( stSysknrmst.ssntubn == GD105_DB_SSNTUBN_MAX ) {
					// �ُ�I��	LOG
// 1.06 DELL	printf("SYSKNRMST.SSTUBN is max\n");
					// 1.06 �ُ�I��	LOG
					sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
							"SYSKNRMST.SSTUBN is max " );
					// �񍐊Ǘ������X�V
					GD105UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
											GD105_DB_HKKJKFLG_ERRFILE,
											GD105_DB_HKKERRCODE_SEQMAX );

// 2006-04-01 H.Suyama Add Start
					continue;
// 2006-04-01 H.Suyama Add End
				}
				++stSysknrmst.ssntubn;
// 2006-04-01 H.Suyama Add Start
				// �V�X�e���Ǘ������X�V
				iRet = ZdbSysknrmstUpdate( &stSysknrmst );
				if ( iRet != HRC_SQL_NORMAL ) {
					// ���[���o�b�N
					ZdbRollback();

					// �ُ�I��	LOG
//1.06 DELL printf("ZdbSysknrmstUpdate error (%d)\n", iRet);
					// 1.06 �ُ�I��	LOG
					sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
							"ZdbSysknrmstUpdate error [%d]", iRet );

					return( RTN_NG );
				}

				// �R�~�b�g
				ZdbCommit();
// 2006-04-01 H.Suyama Add End

				// �쐬�J�n�������擾
				time( (long *)&ulSt );

				// �쐬�����A�ۗ��������N���A
				iHkkssknsu = 0;
				iHkkhrysu = 0;
				memset( cDataFile, 0, sizeof( cDataFile ) );

				// ���ʏ�񌟍��i���M�Ώۂ̂݁j
				// �񍐋敪�����ʏ󋵃R�[�h�̒l�ɂ��킹��
// 2006-04-20 H.Suyama Change Start
#if 0
//				switch ( pHkkknriArrayOut[iHkkknriLoop].hkkkbn ) {
//				case '1':	// �ŏI
//					pHkkknriArrayOut[iHkkknriLoop].hkkkbn = '3';
//					break;
//				case '2':	// ����
//					pHkkknriArrayOut[iHkkknriLoop].hkkkbn = '1';
//					break;
//				}
#else
				switch ( pHkkknriArrayOut[iHkkknriLoop].hkkkbn ) {
				case GD105_DB_HKKKBN_LAST:	// �ŏI
					pHkkknriArrayOut[iHkkknriLoop].hkkkbn = GD105_DB_KKAJKCD_LAST;
					break;
				case GD105_DB_HKKKBN_CYUU:	// ����
					pHkkknriArrayOut[iHkkknriLoop].hkkkbn = GD105_DB_KKAJKCD_CYUU;
					break;
				}
#endif
// 2006-04-20 H.Suyama Change End

				// �ē]���̏ꍇ�́A�ē]���������Ăяo��
				if ( pHkkknriArrayOut[iHkkknriLoop].hkkjkn == GD105_DB_HKKJKN_RESEND ) {
					if ( GD105ResendFile( pEnv,
										  &stSysknrmst,
						 				  &pHkkknriArrayOut[iHkkknriLoop] ) == RTN_OK ) {
						// �񍐃t�@�C����
						// GD105ResendFile���Őݒ�
						// �񍐏󋵃t���O
						ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg,
									 GD105_DB_HKKJKFLG_CHUU,
									 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg ) );
						// ���X�V�����͊֐����Őݒ�

						// �񍐊Ǘ������X�V
						iRet = ZdbHkkknriGD105UpdateNormal( &pHkkknriArrayOut[iHkkknriLoop] );
						if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
							// ���[���o�b�N
							ZdbRollback();
							// �ُ�I��	LOG
//1.06 DELL printf("ZdbHkkknriGD105UpdateNormal error (%d)\n", iRet);
							// 1.06 �ُ�I��	LOG
							sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction",
									 __LINE__,
									EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
									"ZdbHkkknriGD105UpdateNormal error [%d]", 
									iRet );

							return( RTN_NG );
						}

						// �R�~�b�g
						ZdbCommit();
					} else {
						// �ُ�I��	LOG
// 1.06 DELL printf("GD105ResendFile error\n");
						// 1.06 �ُ�I��	LOG
						sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction",
								 __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"GD105ResendFile error " );

						// �񍐊Ǘ������X�V
						GD105UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
												GD105_DB_HKKJKFLG_ERRFILE,
												GD105_DB_HKKERRCODE_RESEND );
					}
					continue;
				}

				// �񍐏����ɂ��A�������@��ؑւ���
				switch ( pHkkknriArrayOut[iHkkknriLoop].hkkjkn ) {
				case GD105_DB_HKKJKN_CTRLNO:	// �R���g���[��No
					iRet = ZdbKekkaGD105SelectByCtrlNo( &pHkkknriArrayOut[iHkkknriLoop],
														&pKekkaArrayOut, &iKekkaNumOut );
					break;
				case GD105_DB_HKKJKN_PLTNO:		// �v���b�gNo
					iRet = ZdbKekkaGD105SelectByPltNo( &pHkkknriArrayOut[iHkkknriLoop],
													   &pKekkaArrayOut, &iKekkaNumOut );
					break;
				case GD105_DB_HKKJKN_KNSSEQ:	// ����SEQ
					iRet = ZdbKekkaGD105SelectByKnsSeq( &pHkkknriArrayOut[iHkkknriLoop],
														&pKekkaArrayOut, &iKekkaNumOut );
					break;
				case GD105_DB_HKKJKN_IRINO:		// �˗���No
					iRet = ZdbKekkaGD105SelectByIriNo( &pHkkknriArrayOut[iHkkknriLoop],
													   &pKekkaArrayOut, &iKekkaNumOut );
					break;
				case GD105_DB_HKKJKN_KNTNO:		// ����No
					iRet = ZdbKekkaGD105SelectByKntNo( &pHkkknriArrayOut[iHkkknriLoop],
													   &pKekkaArrayOut, &iKekkaNumOut );
					break;
				default:
					// �ُ�I��	LOG
//1.06 DELL printf("hkkknri.hkkjkn �͈̔̓G���[ (HKKJKN='%c')\n", pHkkknriArrayOut[iHkkknriLoop].hkkjkn);
					// 1.06 �ُ�I��	LOG
					sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"kkknri.hkkjkn �͈̔̓G���[ (HKKJKN='%c')", 
							pHkkknriArrayOut[iHkkknriLoop].hkkjkn );

					// �񍐊Ǘ������X�V
					GD105UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
										   GD105_DB_HKKJKFLG_ERRFILE,
										   GD105_DB_HKKERRCODE_HKKJKN );
					continue;
				}
				if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
					// �ُ�I��	LOG
//1.06 DELL printf("ZdbKekkaGD105SelectByXXXX error (%d)\n", iRet);
					// 1.06 �ُ�I��	LOG
					sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
							"ZdbKekkaGD105SelectByXXXX error (%d)", iRet);

					// �񍐊Ǘ������X�V
					GD105UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
										   GD105_DB_HKKJKFLG_ERRFILE,
// 2006-04-06 H.Suyama Change Start
#if 0
//										   GD105_DB_HKKERRCODE_HKKJKN );
#else
										   GD105_DB_HKKERRCODE_DBACS );
#endif
// 2006-04-06 H.Suyama Change End
					continue;
				}
				if ( iRet == HRC_SQL_NOT_FOUND ) {
					// �ُ�I��	LOG
//1.06 DELL printf("ZdbKekkaGD105SelectByXXXX no data error\n");
					// 1.06 �ُ�I��	LOG
					sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
							"ZdbKekkaGD105SelectByXXXX no data  error" );

					// �񍐊Ǘ������X�V
					GD105UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
										   GD105_DB_HKKJKFLG_ERRFILE,
										   GD105_DB_HKKERRCODE_NODATA );
					continue;
				}
				if ( iRet == HRC_SQL_NORMAL ) {
					// �񍐃f�[�^�t�@�C���̍쐬
					if ( GD105CreateFile( pEnv,
										  &stSysknrmst,
										  pKekkaArrayOut,
										  iKekkaNumOut,
										  &iHkkssknsu,
										  &iHkkhrysu,
										  cDataFile,
											&li_stopFlg//2006.12.08 Kim Jinsuk DB�G���[���I�������� 
											) == RTN_NG ) {

						//2006.12.08�@Kim Jinsuk DB�G���[���ُ�I��������
						if(li_stopFlg==1)
						{
						    printf("#############################3");
						    sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbKekkaGD105Update", __LINE__,
						    EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
						    "[[DB ERROR]]" );

						    return( RTN_NG );
						}
						//2006.12.08�@Kim Jinsuk DB�G���[���ُ�I��������


						// 1.12 ADD �ۗ������ȊO�񍐑Ώ�0���̏ꍇ
						if( iKekkaNumOut == iHkkhrysu ){
							sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction", __LINE__,
									EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"�ۗ��ȊO�񍐑Ώ�0��" );
							// �񍐕ۗ�����
	            			pHkkknriArrayOut[iHkkknriLoop].hkkssknsu = iHkkssknsu;
	            			pHkkknriArrayOut[iHkkknriLoop].hkkhrysu = iHkkhrysu;
							GD105UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
												   GD105_DB_HKKJKFLG_ERRFILE,
												   GD105_DB_HKKERRCODE_NODATA );

							// �����t���O���X�V
							if ( GD105UpdateKekka( pEnv,
												   &stSysknrmst,
												   pKekkaArrayOut,
												   iKekkaNumOut,
												   &li_stopFlg
												 ) == RTN_NG ) {

								if(li_stopFlg==1) {
									sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105UpdateKekka", __LINE__,
											EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON, "[[DB ERROR]]" );

									return( RTN_NG );
								}
								sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction", __LINE__,
											EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "GD105UpdateKekka error" );
							}

							continue;
						}

						// �ُ�I��	LOG
// 1.06 DELL printf("GD105CreateFile error\n");
						// 1.06 �ُ�I��	LOG
						sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
								 __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"GD105CreateFile error" );


						// �񍐊Ǘ������X�V
						GD105UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
											   GD105_DB_HKKJKFLG_ERRFILE,
// 2006-04-06 H.Suyama Change Start
#if 0
//											   GD105_DB_HKKERRCODE_HKKJKN );
#else
											   GD105_DB_HKKERRCODE_CREATE );
#endif
// 2006-04-06 H.Suyama Change End

/* 2008-09-02 Start �� 2014-01-15 �폜
						if ( iHkkssknsu != 0 ) {
							// HULFT���M�p�t�@�C���̍쐬
							if ( GD105CreateHULFTFile( pEnv,
													   &stSysknrmst,
													   &pHkkknriArrayOut[iHkkknriLoop],
													   cDataFile,
													   iHkkssknsu,
											  			&pHkkknriArrayOut[iHkkknriLoop] ) == RTN_NG ) {

								sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
										 __LINE__,
										EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
										"GD105CreateHULFTFile error" );

								// �񍐊Ǘ������X�V
								GD105UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
													   GD105_DB_HKKJKFLG_ERRFILE,
													   GD105_DB_HKKERRCODE_HULFT );
							}

							// �쐬�J�n����
							GD105ConvTimestamp( ulSt, cTimestamp );
							ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkstdh,
										 cTimestamp,
										 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkstdh ) );
							// �쐬�����������擾
							time( (long *)&ulEd );
							// �쐬��������
							GD105ConvTimestamp( ulEd, cTimestamp );
							ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkeddh,
										 cTimestamp,
										 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkeddh ) );
							// �쐬����
							pHkkknriArrayOut[iHkkknriLoop].hkkssknsu = iHkkssknsu;
							// �񍐕ۗ�����
							pHkkknriArrayOut[iHkkknriLoop].hkkhrysu = iHkkhrysu;
							// ���M�t�@�C���h�c
							// GD105CreateHULFTFile���Őݒ�
							// �񍐏󋵃t���O
							ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg,
										 GD105_DB_HKKJKFLG_ERRFILE,
										 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg ) );
							// ���X�V�����͊֐����Őݒ�

							// �񍐊Ǘ������X�V
							iRet = ZdbHkkknriGD105UpdateNormal( &pHkkknriArrayOut[iHkkknriLoop] );
							if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
								// ���[���o�b�N
								ZdbRollback();
								// �ُ�I��	LOG
								sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction",
										 __LINE__,
										EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
										"ZdbHkkknriGD105UpdateNormal error (%d)", iRet);

								return( RTN_NG );
							}

							// �񍐊Ǘ������X�V GD105_DB_HKKERRCODE_DBACS �͉��Ƃ���
							GD105UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
												   GD105_DB_HKKJKFLG_ERRFILE,
												   GD105_DB_HKKERRCODE_DBACS );

							// �R�~�b�g
							ZdbCommit();
						}
 2008-09-02 End �� 2014-01-15 �폜 */
						continue;
					}


					// HULFT���M�p�t�@�C���̍쐬
// 2006-04-06 H.Suyama Change Start
#if 0
//					if ( GD105CreateHULFTFile( pEnv,
//											   &stSysknrmst,
//											   &pHkkknriArrayOut[iHkkknriLoop],
//											   cDataFile ) == RTN_NG ) {
#else
//2006-07-06 CHG Osada �t�@�C�����������@�ύX
//					if ( GD105CreateHULFTFile( pEnv,
//											   &stSysknrmst,
//											   &pHkkknriArrayOut[iHkkknriLoop],
//											   cDataFile,
//											   iHkkssknsu ) == RTN_NG ) {
					if ( GD105CreateHULFTFile( pEnv,
											   &stSysknrmst,
											   &pHkkknriArrayOut[iHkkknriLoop],
											   cDataFile,
											   iHkkssknsu,
									  			&pHkkknriArrayOut[iHkkknriLoop] ) == RTN_NG ) {
#endif
// 2006-04-06 H.Suyama Change End
						// �ُ�I��	LOG
// 1.06 DELL printf("GD105CreateHULFTFile error\n");
					// 1.06 �ُ�I��	LOG
						sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
								 __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"GD105CreateHULFTFile error" );

						// �񍐊Ǘ������X�V
						GD105UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
											   GD105_DB_HKKJKFLG_ERRFILE,
// 2006-04-06 H.Suyama Change Start
#if 0
//											   GD105_DB_HKKERRCODE_HKKJKN );
#else
											   GD105_DB_HKKERRCODE_HULFT );
#endif
// 2006-04-06 H.Suyama Change End
						continue;
					}
				}


				// �쐬�����������擾
				time( (long *)&ulEd );

				// �񍐃t�@�C����
				// GD105CreateHULFTFile���Őݒ�
				// �쐬�J�n����
				GD105ConvTimestamp( ulSt, cTimestamp );
				ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkstdh,
							 cTimestamp,
							 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkstdh ) );
				// �쐬��������
				GD105ConvTimestamp( ulEd, cTimestamp );
				ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkeddh,
							 cTimestamp,
							 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkeddh ) );
				// �쐬����
				pHkkknriArrayOut[iHkkknriLoop].hkkssknsu = iHkkssknsu;
				// �񍐕ۗ�����
				pHkkknriArrayOut[iHkkknriLoop].hkkhrysu = iHkkhrysu;
				// ���M�t�@�C���h�c
				// GD105CreateHULFTFile���Őݒ�
			

				// �����t���O��񍐍ς݂ɍX�V
				if ( GD105UpdateKekka( pEnv,
									   &stSysknrmst,
									   pKekkaArrayOut,
									   iKekkaNumOut,
									   &li_stopFlg 
										) == RTN_OK ) {
					// �񍐏󋵃t���O
					ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg,
								 GD105_DB_HKKJKFLG_CHUU,
								 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg ) );
				} else {

					// �񍐊Ǘ������X�V
					GD105UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
										   GD105_DB_HKKJKFLG_OK_DBERR,
										   GD105_DB_HKKERRCODE_DBACS );

					if(li_stopFlg==1) {
						sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105UpdateKekka", __LINE__,
									EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON, "[[DB ERROR]]" );
						return( RTN_NG );
					}
					sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "GD105UpdateKekka error" );

					// �񍐏󋵃t���O
					ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg,
								 GD105_DB_HKKJKFLG_OK_DBERR,
								 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg ) );
				}

				// ���X�V�����͊֐����Őݒ�

				// �񍐊Ǘ������X�V
				iRet = ZdbHkkknriGD105UpdateNormal( &pHkkknriArrayOut[iHkkknriLoop] );
				if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
					// ���[���o�b�N
					ZdbRollback();
					// �ُ�I��	LOG
// 1.06 DELL printf("ZdbHkkknriGD105UpdateNormal error (%d)\n", iRet);
					// 1.06 �ُ�I��	LOG
					sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
							"ZdbHkkknriGD105UpdateNormal error (%d)", iRet);

					return( RTN_NG );
				}

// 2006-04-01 H.Suyama Del Start
#if 0
//				// �V�X�e���Ǘ������X�V
//				iRet = ZdbSysknrmstUpdate( &stSysknrmst );
//				if ( iRet != HRC_SQL_NORMAL ) {
//					// �ُ�I��	LOG
//printf("ZdbSysknrmstUpdate error (%d)\n", iRet);
//					return( RTN_NG );
//				}
#endif
// 2006-04-01 H.Suyama Del Start

				// �R�~�b�g
				ZdbCommit();
				
				
				// ���ʏ������
				if ( pKekkaArrayOut != NULL ) {
					ZbmlFree( pKekkaArrayOut );
				}
			}

			// �񍐊Ǘ��������
			ZbmlFree( pHkkknriArrayOut );
		}

		// �X���[�v
		sleep( pEnv->iSleepSec );
	}

#ifdef _TRACE
	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");
#endif

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FendFunction()												  */
/*�@�@�\�T�v�@�F�I�������֐�												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FGD105Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�F�Ȃ�														  */
/******************************************************************************/
void endFunction( GD105Env *pEnv )
{
#ifdef _TRACE
	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "endFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");
#endif
	// 1.09 ADD
	/***	
     ***    �f�[�^�x�[�X�N���[�Y
     ***/
    ZdbDisConnect() ;

	// ���L�������폜
	if ( sFncShmDel( pEnv ) != RTN_OK ) {
		return;
	}

#ifdef _TRACE
	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "endFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");
#endif
}

/******************************************************************************/
/*�@�� �� ���@�FGD105MakeData()												  */
/*�@�@�\�T�v�@�F�񍐃f�[�^�쐬												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FKekka *pKekka		�������ʃf�[�^							  */
/*�@�@��Q�����Fchar *pLBCD			���{�R�[�h								  */
/*�@�o�@�@�́@�F															  */
/*�@�@��R�����FGD105Rec *pGD105Rec	�񍐃f�[�^								  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int GD105MakeData(Kekka *pKekka, char *pLBCD, GD105Rec *pGD105Rec)
{
	char	cTempBuff[128];
	char	cKkassflg[1+1];		// 1.11 ADD ���ʏC���׸�MAX�擾


	// �������ʃf�[�^�܂��͕񍐃f�[�^�ւ̃|�C���^��NULL�̏ꍇ�ُ�I��
	if ( pKekka == NULL || pGD105Rec == NULL ) {
		return( RTN_NG );
	}

	// 1.06 ADD �{�ݕʊ��Z�Ή�
	GD105_sstknz( pKekka );

	// �񍐃f�[�^���X�y�[�X�ŃN���A
	memset( pGD105Rec, GD105_DATA_SPACE, sizeof(GD105Rec) );

	// �������ʃf�[�^����񍐃f�[�^���쐬
	// �a�l�k��t�N����
	// [YYYYMMDD]�ɕϊ����Đݒ�
	ZbmlChgAPDate( pGD105Rec->cUTKYMD, pKekka->utkymd );
	// �˗����m���D
	// ������11�������̂悤�ɕϊ�
	// (�ϊ��O)[1][2][3][4][5][6][7][8][9][10][11]
	// (�ϊ���)[3][4][5] 0  0 [6][7][8][9][10][11]
	if ( GD105ConvNumber( pGD105Rec->cIRINO, pKekka->irino ) == RTN_NG ) {
		return( RTN_NG );
	}
	// ���ڃR�[�h
	if ( GD105CopyFromLeft( pGD105Rec->cKMKCD,
							pKekka->kmkcd,
							sizeof( pGD105Rec->cKMKCD ),
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// ���̂m���D
	// ������11�������̂悤�ɕϊ�
	// (�ϊ��O)[1][2][3][4][5][6][7][8][9][10][11]
	// (�ϊ���)[3][4][5] 0  0 [6][7][8][9][10][11]
	if ( GD105ConvNumber( pGD105Rec->cKNTNO, pKekka->kntno ) == RTN_NG ) {
		return( RTN_NG );
	}
	// �e���ڃR�[�h
	if ( GD105CopyFromLeft( pGD105Rec->cOYAKMKCD,
							pKekka->oyakmkcd,
							sizeof( pGD105Rec->cOYAKMKCD ),
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// �������ʂP
	// �E����8����ݒ�i��ۻ��ڽ����j
	if ( GD105CopyFromRight( pGD105Rec->cKNSKKA1,
							 pKekka->knskka1,
							 sizeof( pGD105Rec->cKNSKKA1 ),
							 FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// �������ʂQ
	// ������8����ݒ�i2�o�C�g�����ɒ��ӂ���j
	//1.09 UPD
	//if ( GD105CopyFromRight( pGD105Rec->cKNSKKA2,
	if ( GD105CopyFromLeft( pGD105Rec->cKNSKKA2,
							 pKekka->knskka2,
							 sizeof( pGD105Rec->cKNSKKA2 ),
							 TRUE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// ���ʂQ�敪
	// ������1����ݒ�
// 2006-04-20 H.Suyama Change Start
#if 0
//	pGD105Rec->cKNSKKA2KBN = pKekka->knskka2kbn[0];
#else
	if ( pKekka->knskka2kbn[0] == '\0' )
		pGD105Rec->cKNSKKA2KBN = GD105_DATA_SPACE;
	else
		pGD105Rec->cKNSKKA2KBN = pKekka->knskka2kbn[0];
#endif
// 2006-04-20 H.Suyama Change End
	// ���ʕ⑫�R�[�h
	if ( GD105CopyFromLeft( pGD105Rec->cKKAHSKCD,
							pKekka->kkahskcd,
							sizeof( pGD105Rec->cKKAHSKCD ),
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// ���ʃR�����g�P
// 2006-04-06 H.Suyama Change Start
#if 0
//	// �E����4����ݒ�
//	if ( GD105CopyFromRight( pGD105Rec->cKKACMT1,
//							 pKekka->kkacmt1,
//							 sizeof( pGD105Rec->cKKACMT1 ),
//							 FALSE ) == RTN_NG ) {
//		return( RTN_NG );
//	}
#else
	// ������4����ݒ�
	if ( GD105CopyFromLeft( pGD105Rec->cKKACMT1,
							pKekka->kkacmt1,
							sizeof( pGD105Rec->cKKACMT1 ),
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
#endif
// 2006-04-06 H.Suyama Change End
	// ���ʃR�����g�Q
// 2006-04-06 H.Suyama Change Start
#if 0
//	// �E����4����ݒ�
//	if ( GD105CopyFromRight( pGD105Rec->cKKACMT2,
//							 pKekka->kkacmt2,
//							 sizeof( pGD105Rec->cKKACMT2 ),
//							 FALSE ) == RTN_NG ) {
//		return( RTN_NG );
//	}
#else
	// ������4����ݒ�
	if ( GD105CopyFromLeft( pGD105Rec->cKKACMT2,
							pKekka->kkacmt2,
							sizeof( pGD105Rec->cKKACMT2 ),
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
#endif
// 2006-04-06 H.Suyama Change End
	// �ُ�l�敪�i�j�j
// 2006-04-20 H.Suyama Change Start
#if 0
//	pGD105Rec->cIJKBNM = pKekka->ijkbnm;
#else
	if ( pKekka->ijkbnm == '\0' )
		pGD105Rec->cIJKBNM = GD105_DATA_SPACE;
	else
		pGD105Rec->cIJKBNM = pKekka->ijkbnm;
#endif
// 2006-04-20 H.Suyama Change End
	// �ُ�l�敪�i���j
// 2006-04-20 H.Suyama Change Start
#if 0
//	pGD105Rec->cIJKBNF = pKekka->ijkbnf;
#else
	if ( pKekka->ijkbnf == '\0' )
		pGD105Rec->cIJKBNF = GD105_DATA_SPACE;
	else
		pGD105Rec->cIJKBNF = pKekka->ijkbnf;
#endif
// 2006-04-20 H.Suyama Change End
	// �ُ�l�敪�i�s���j
// 2006-04-20 H.Suyama Change Start
#if 0
//	pGD105Rec->cIJKBNN = pKekka->ijkbnn;
#else
	if ( pKekka->ijkbnn == '\0' )
		pGD105Rec->cIJKBNN = GD105_DATA_SPACE;
	else
		pGD105Rec->cIJKBNN = pKekka->ijkbnn;
#endif
// 2006-04-20 H.Suyama Change End
	// �w���i�r�c�P�j
	if ( GD105CopyFromLeft( pGD105Rec->cSDI,
							pKekka->sdi,
							sizeof( pGD105Rec->cSDI ),
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// ��l�m���D
	if ( GD105CopyFromLeft( pGD105Rec->cKJNO,
							pKekka->kjno,
							sizeof( pGD105Rec->cKJNO ),
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// ���{����
	// �󔒂�ݒ�Ȃ̂ŉ������Ȃ�
	// ���������\���
	// �󔒂�ݒ�Ȃ̂ŉ������Ȃ�
	// �g������DB���ʺ���
	// [0]��ݒ�
	pGD105Rec->cEXTKKADBIDCD = GD105_DATA_CHAR0;
	// ���ʏ󋵃R�[�h
// 2006-04-20 H.Suyama Change Start
#if 0
//	pGD105Rec->cKKAJKCD = pKekka->kkajkcd;
#else
	if ( pKekka->kkajkcd == '\0' )
		pGD105Rec->cKKAJKCD = GD105_DATA_SPACE;
	else
		pGD105Rec->cKKAJKCD = pKekka->kkajkcd;
#endif
// 2006-04-20 H.Suyama Change End
	// �p�j�b�N�����W�t���O
// 2006-04-20 H.Suyama Change Start
#if 0
//	pGD105Rec->cPNCRGFLG = pKekka->pncrgflg;
#else
	if ( pKekka->pncrgflg == '\0' )
		pGD105Rec->cPNCRGFLG = GD105_DATA_SPACE;
	else
		pGD105Rec->cPNCRGFLG = pKekka->pncrgflg;
#endif
// 2006-04-20 H.Suyama Change End
	// �v�r�R�[�h
// 2006-04-06 H.Suyama Change Start
#if 0
//	// �E����4����ݒ�
//	if ( GD105CopyFromRight( pGD105Rec->cSMPCD,
//							 pKekka->smpcd,
//							 sizeof( pGD105Rec->cSMPCD ),
//							 FALSE ) == RTN_NG ) {
//		return( RTN_NG );
//	}
#else
	// ������4����ݒ�
	if ( GD105CopyFromLeft( pGD105Rec->cSMPCD,
							pKekka->smpcd,
							sizeof( pGD105Rec->cSMPCD ),
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
#endif
// 2006-04-06 H.Suyama Change End
	// �����r�d�p
	// ���l�𕶎���ɕϊ���A�E����6����ݒ�B�i��ۻ��ڽ�Ȃ��j
	sprintf( cTempBuff, "%06d", pKekka->knsseq );
	if ( GD105CopyFromRight( pGD105Rec->cKNSSEQ,
							 cTempBuff,
							 sizeof( pGD105Rec->cKNSSEQ ),
							 FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// ����ޗ��R�[�h
		// 1.06 ADD �����ɂ��Œ�Ő���ޗ���ݒ�
		// 099: ?
/* 1.13 STA str->mem */
//	if( strncmp( pKekka->smpcd, "0952", 4 ) == 0 ){
//		strcpy( pKekka->zrcd,	"099" );
//	}
	if( memcmp( pKekka->smpcd, "0952", 4 ) == 0 ){
		memcpy( pKekka->zrcd,	"099", 3 );
	}
		// 007:�_�`
//	if( strncmp( pKekka->smpcd, "0959", 4 ) == 0 ){
//		strcpy( pKekka->zrcd,	"007" );
//	}
	if( memcmp( pKekka->smpcd, "0959", 4 ) == 0 ){
		memcpy( pKekka->zrcd,	"007", 3 );
	}
/* 1.13 END str->mem */

// 2006-04-06 H.Suyama Change Start
#if 0
//	// �E����3���ݒ�
//	if ( GD105CopyFromRight( pGD105Rec->cZRCD,
//							 pKekka->zrcd,
//							 sizeof( pGD105Rec->cZRCD ),
//							 FALSE ) == RTN_NG ) {
//		return( RTN_NG );
//	}
#else
	// ������3���ݒ�
	if ( GD105CopyFromLeft( pGD105Rec->cZRCD,
							pKekka->zrcd,
							sizeof( pGD105Rec->cZRCD ),
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
#endif
// 2006-04-06 H.Suyama Change End
	// ���ʊ��Z�t���O
// 2006-04-20 H.Suyama Change Start
#if 0
//	pGD105Rec->cKKAKSFLG = pKekka->kkaksflg;
#else
	if ( pKekka->kkaksflg == '\0' )
		pGD105Rec->cKKAKSFLG = GD105_DATA_SPACE;
	else
		pGD105Rec->cKKAKSFLG = pKekka->kkaksflg;
#endif
// 2006-04-20 H.Suyama Change End

	// ���ʏC���t���O
// 1.11 STA ====================================================
// 1.11 DEL// 2006-04-20 H.Suyama Change Start
// 1.11 DEL #if 0
// 1.11 DEL //	pGD105Rec->cKKASSFLG = pKekka->kkassflg;
// 1.11 DEL #else
// 1.11 DEL 	if ( pKekka->kkassflg == '\0' )
// 1.11 DEL 		pGD105Rec->cKKASSFLG = GD105_DATA_SPACE;
// 1.11 DEL 	else
// 1.11 DEL 		pGD105Rec->cKKASSFLG = pKekka->kkassflg;
// 1.11 DEL #endif
// 1.11 DEL // 2006-04-20 H.Suyama Change End

// 1.11 ADD ���ʏC���t���O�͓���KEY����MAX(���ʏC��FLG�j��ҏW
	 if ( pKekka->kkassflg == '\0' ){
		pGD105Rec->cKKASSFLG = GD105_DATA_SPACE;
	} else {
		memset( cKkassflg,	'\0',	sizeof( cKkassflg ));
		if ( GD105GetKkassflgMax( pKekka, cKkassflg ) == RTN_OK ) {
			pGD105Rec->cKKASSFLG = cKkassflg[0];
			// �X�V�p�Ɏ擾����MAX���\���̂ɕҏW����
			pKekka->kkassflg	= cKkassflg[0];
		} else {
			pGD105Rec->cKKASSFLG = pKekka->kkassflg;
		}
	}
// 1.11 END ====================================================

	// ��Ɖ�t���O
// 2006-04-20 H.Suyama Change Start
#if 0
//	pGD105Rec->cHSYKFLG = pKekka->hsykflg;
#else
	if ( pKekka->hsykflg == '\0' )
		pGD105Rec->cHSYKFLG = GD105_DATA_SPACE;
	else
		pGD105Rec->cHSYKFLG = pKekka->hsykflg;
#endif
// 2006-04-20 H.Suyama Change End
	// �񐿋��敪
// 2006-04-20 H.Suyama Change Start
#if 0
//	pGD105Rec->cHSKFLG = pKekka->hskflg;
#else
	if ( pKekka->hskflg == '\0' )
		pGD105Rec->cHSKFLG = GD105_DATA_SPACE;
	else
		pGD105Rec->cHSKFLG = pKekka->hskflg;
#endif
// 2006-04-20 H.Suyama Change End
	// ��񍐃t���O
// 2006-04-20 H.Suyama Change Start
#if 0
//	pGD105Rec->cHHKKFLG = pKekka->hhkkflg;
#else
	if ( pKekka->hhkkflg == '\0' )
		pGD105Rec->cHHKKFLG = GD105_DATA_SPACE;
	else
		pGD105Rec->cHHKKFLG = pKekka->hhkkflg;
#endif
// 2006-04-20 H.Suyama Change End
	// �������ʃR�[�h
	// [0]��ݒ�
	pGD105Rec->cKNSIDCD = GD105_DATA_CHAR0;
	// �������{���{�R�[�h
	if ( GD105CopyFromLeft( pGD105Rec->cLBCD,
							pLBCD,
							sizeof( pGD105Rec->cLBCD ),
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// �\��t�B�[���h
	// �󔒂�ݒ�Ȃ̂ŉ������Ȃ�

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FGD105DataFileFilter()										  */
/*�@�@�\�T�v�@�F�f�B���N�g�������p�̃t�@�C���t�B���^(�R�[���o�b�N)			  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����Fstruct dirent *pDirEnt	�f�B���N�g���G���g��				  */
/*�@�o�@�@�́@�F�������ʃt�@�C��											  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		0	: �ΏۊO�t�@�C��									  */
/*�@�@�@�@�@�@		1	: �Ώۃt�@�C��										  */
/******************************************************************************/
int GD105DataFileFilter(struct dirent *pDirEnt)
{
	BmlDate		today;
	char		cToday[GD105_LEN_DATESHORT + 1];

	// �����񒷃`�F�b�N
	if ( strlen ( pDirEnt->d_name )  < GD105_LEN_FILEID ) {
		return( 0 ) ;
	}

	// �������t�擾
	if ( ZbmlDateGetToday(&today) == FALSE ) {
		return( 0 );
	}
	sprintf( cToday, "%04d%02d%02d", today.year, today.month, today.day);

	// ���t�`�F�b�N
	if ( memcmp ( pDirEnt->d_name,
				  cToday,
				  strlen ( cToday ) ) != 0 ) {
		return( 0 ) ;
	}

	return( 1 );
}

/******************************************************************************/
/*�@�� �� ���@�FGD105WriteFile()											  */
/*�@�@�\�T�v�@�F�񍐃f�[�^�t�@�C��������									  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FFILE *fp			�t�@�C���|�C���^						  */
/*�@�@��Q�����FGD105Rec *pGD105Rec	�񍐃f�[�^								  */
/*�@�@��R�����Fint iRecCnt			���R�[�h��								  */
/*�@�o�@�@�́@�F�������ʃt�@�C��											  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int GD105WriteFile(FILE *fp, GD105Rec *pGD105Rec, int iRecCnt)
{
	int				iLoop;
	int				iFileCnt;
	GD105Rec		stGD105RecTemp;
	char			cTemp[GD105_FILE_FILLER_SIZE];

	// �t�@�C���o��
	// �f�[�^���ʎq������
	iFileCnt = fwrite( GD105_FILE_DATAID, strlen( GD105_FILE_DATAID ), 1, fp);
	if ( iFileCnt != 1 ) {
		// �ُ�I��	LOG
// 1.06 DELL printf("write status:[%d]\n", iFileCnt);
		// 1.06 �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105WriteFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"write status:[%d]", iFileCnt );

		gintErrorCode = GD105_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	// ���R�[�h������
	iFileCnt = fwrite( pGD105Rec, sizeof( GD105Rec ) * iRecCnt, 1, fp);
	if ( iFileCnt != 1 ) {
		// �ُ�I��	LOG
// 1.06 DELL printf("write status:[%d]\n", iFileCnt);
		// 1.06 �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105WriteFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"write status:[%d] ", iFileCnt );

		gintErrorCode = GD105_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}
	for ( iLoop = iRecCnt; iLoop < GD105_REC_LOOP_MAX; iLoop++ ) {
		memset( &stGD105RecTemp, GD105_DATA_SPACE, sizeof( GD105Rec ) );
		iFileCnt = fwrite( &stGD105RecTemp, sizeof( GD105Rec ), 1, fp);
		if ( iFileCnt != 1 ) {
			// �ُ�I��	LOG
// 1.06 DELL printf("write status:[%d]\n", iFileCnt);
			// 1.06 �ُ�I��	LOG
			sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105WriteFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"write status:[%d]", iFileCnt );

			gintErrorCode = GD105_STSCODE_ERR_FR_FILE ;
			return( RTN_NG ) ;
		}
	}

	// Filler������
	memset( cTemp, GD105_DATA_SPACE, GD105_FILE_FILLER_SIZE );
	iFileCnt = fwrite( cTemp, GD105_FILE_FILLER_SIZE, 1, fp );
	if ( iFileCnt != 1 ) {
		// �ُ�I��	LOG
//1.06 DELL printf("write status:[%d]\n", iFileCnt);
		// 1.06 �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105WriteFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"write status:[%d]", iFileCnt );

		gintErrorCode = GD105_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	// LF������
	cTemp[0] = GD105_FILE_LINEFEED;
	iFileCnt = fwrite( cTemp, 1, 1, fp);
	if ( iFileCnt != 1 ) {
		// �ُ�I��	LOG
// 1.06 DELL printf("write status:[%d]\n", iFileCnt);
		// 1.06 �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105WriteFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"write status:[%d] ", iFileCnt );

		gintErrorCode = GD105_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FGD105ResendFile()											  */
/*�@�@�\�T�v�@�F�ē]���p�t�@�C���ړ�										  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FGD105Env *pEnv		�v���O�������\����					  */
/*�@�@��Q�����FSysknrmst *pSysknrmst �V�X�e���Ǘ��}�X�^���				  */
/*�@�@��R�����FHkkknri *pHkkknri	�񍐊Ǘ������						  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int GD105ResendFile(GD105Env *pEnv, Sysknrmst *pSysknrmst, Hkkknri *pHkkknri)
{
	int				iRet;
	struct dirent	**pDirEnt;
	int				iFileCnt;
	int	 			iSeqNo;
	char			cSeqBuff[10];
	BmlDate			today;
	char			cKjnsriymd[GD105_LEN_DATESHORT + 1];
	char			cFileDate[GD105_LEN_DATESHORT + 1];
	char			cFileSrc[PATH_MAX + 1];
	char			cSendFile[PATH_MAX + 1];
	char			cSendFileTemp[PATH_MAX + 1];
	FILE *			fpSrc;
	FILE *			fpDest;
	int				iLoop;
	FILEHEADER		stHeader, *pHead;
	FILETRAILER		stTrailer;
	char			cTemp[GD105_SIZE_BUFF + 1];
	char			cWfilnm[PATH_MAX + 1];
    //2006-07-06 ADD Osada �t�@�C�����������@�ύX
    char            sNewFlName[PATH_MAX + 1];
    char            sKaisibi[10];
	char			sSecCd[3];
    int             i;
	int	iHead;
	char			sBuf[128];
    //

	// �������t�擾
	ZbmlChgAPDate( cKjnsriymd, pSysknrmst->kjnsriymd );

	// ���t�@�C���̏������t���擾
	memset( cFileDate, 0, sizeof( cFileDate ) );
	memcpy( cFileDate, pHkkknri->ssnmtfilid, GD105_LEN_DATESHORT );

	// 1.07 INTEC ADD STA
	// �t�@�C�����̌��󔒂�Trim
	sprintf( cWfilnm, "%.*s",
			strcspn( pHkkknri->stsflnm, " " ) ,
			pHkkknri->stsflnm );
	strcpy( pHkkknri->stsflnm, cWfilnm );
	// 1.07 INTEC ADD END

	// ���M�p�t�@�C��������
//2006-07-06 CHG Osada �t�@�C�����������@�ύX
#if 0
	sprintf( cSendFile, "%s/%s/%s/%s%04d%s",
			 pEnv->cDirToday,
			 pEnv->cDirSendFile,
			 pEnv->cDirSendREQ,
			 pHkkknri->ssnmtfilid,
			 pHkkknri->hkksjno,
			 GD105_FILEEXT_DATA );
	sprintf( cSendFileTemp, "%s/%s/%s/%s%04d%s",
			 pEnv->cDirToday,
			 pEnv->cDirSendFile,
			 pEnv->cDirSendREQ,
			 pHkkknri->ssnmtfilid,
			 pHkkknri->hkksjno,
			 GD105_FILEEXT_TEMP );
#else
   memset(sNewFlName, 0, sizeof(sNewFlName));
   //CHG E/Osada 2006-07-18 
   //sprintf(sNewFlName, "%-3.3s_%04d_%-22.22s", pHkkknri->stsflnm, pHkkknri->hkksjno,
	// 1.10 UPD �񍐎w��NO�����̂܂ܕҏW(-1���Ȃ�)
   //sprintf(sNewFlName, "%-3.3s_%04d_%-18.18s%04d", pHkkknri->stsflnm, pHkkknri->hkksjno - 1,
   sprintf(sNewFlName, "%-3.3s_%04d_%-18.18s%04d", pHkkknri->stsflnm, pHkkknri->hkksjno,
		&pHkkknri->stsflnm[9], pSysknrmst->ssntubn);
	memset(cSendFile, 0, sizeof(cSendFile));
	memset(cSendFileTemp, 0, sizeof(cSendFileTemp));
	sprintf(cSendFile, "%s/%s/%s/%s%s",
			pEnv->cDirToday,
		 	pEnv->cDirSendFile,
			pEnv->cDirSendREQ,
			sNewFlName, GD105_FILEEXT_DATA);	
	sprintf(cSendFileTemp, "%s/%s/%s/%s%s",
			pEnv->cDirToday,
		 	pEnv->cDirSendFile,
			pEnv->cDirSendREQ,
			sNewFlName, GD105_FILEEXT_TEMP);	
#endif
//

	// ���������t�@�C����OK�f�B���N�g���̃t���p�X�𐶐�
	//if ( memcmp( cKjnsriymd, pHkkknri->stsflnm, GD105_LEN_DATESHORT ) == 0 ) {
	if ( memcmp( cKjnsriymd, pHkkknri->ssnmtfilid, GD105_LEN_DATESHORT ) == 0 ) {
		sprintf( cFileSrc, "%s/%s/%s/%s",
			 	pEnv->cDirToday,
			 	pEnv->cDirSendFile,
			 	pEnv->cDirSendOK,
				pHkkknri->stsflnm );
	} else {
		sprintf( cFileSrc, "%s/%s/%s/%s/%s",
			 	pEnv->cDirOldday,
			 	cFileDate,
			 	pEnv->cDirSendFile,
			 	pEnv->cDirSendOK,
				pHkkknri->stsflnm );
	}
	// ���t�@�C���I�[�v��
	fpSrc = fopen ( cFileSrc, "r" );
	if ( fpSrc == NULL ) {
		// �t�@�C�����I�[�v���ł��Ȃ��ꍇ��ERR�f�B���N�g���ōĒ���
		if ( strncmp( cKjnsriymd, pHkkknri->ssnmtfilid, GD105_LEN_DATESHORT ) == 0 ) {
		//if ( strncmp( cKjnsriymd, pHkkknri->stsflnm, GD105_LEN_DATESHORT ) == 0 ) {
			sprintf( cFileSrc, "%s/%s/%s/%s",
				 	pEnv->cDirToday,
				 	pEnv->cDirSendFile,
				 	pEnv->cDirSendERR,
					pHkkknri->stsflnm );
		} else {
			sprintf( cFileSrc, "%s/%s/%s/%s/%s",
				 	pEnv->cDirOldday,
			 		cFileDate,
				 	pEnv->cDirSendFile,
				 	pEnv->cDirSendERR,
					pHkkknri->stsflnm );
		}
		// ���t�@�C���I�[�v��
		fpSrc = fopen ( cFileSrc, "r" );
		if ( fpSrc == NULL ) {
			// �ُ�I��	LOG
			gintErrorCode = GD105_STSCODE_ERR_FR_FILE ;
			return( RTN_NG ) ;
		}
	}

	// ���M�p�t�@�C���I�[�v��
	fpDest = fopen ( cSendFileTemp, "w" );
	if ( fpDest == NULL ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	// �ǂݍ���
	iHead = 0;
	while ( iRet = fgets( cTemp, sizeof ( cTemp ), fpSrc ) != NULL ) {
		if( !iHead ) {
			pHead = (FILEHEADER *)cTemp;
			memset(sBuf, 0, sizeof(sBuf));
			sprintf( sBuf, "%04d", pSysknrmst->ssntubn );
			ZbmlStrCpy( pHead->cSeqNo, sBuf, sizeof( stHeader.cSeqNo ) );
			memset(sBuf, 0, sizeof(sBuf));
			memset(pHead->cParam1, ' ', 128);
			// 1.10 UPD �ē]�����t�@�C�����̐擪18byte���p�����ɐݒ肷��
			//sprintf( sBuf, "%s%s", sNewFlName, GD105_FILEEXT_DATA );
			//memcpy(pHead->cParam1, sBuf, 18);
			memcpy(pHead->cParam1, pHkkknri->stsflnm, 18);
			iHead = 1;
		}
		// ���Ұ�1
	//stHeader.cParam1
// 2006-04-20 H.Suyama Add Start
	// 1.07 INTEC UPD cSendIDSaki -> cSendIDMoto
	//							pEnv->cSendIDSaki,
		if ( fputs( cTemp, fpDest ) < 0 ) {
			//�G���[���O�o��
//1.06 DELL printf("fputs error \n");
			// 1.06 �ُ�I��	LOG
			sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105ResendFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"fputs error ");

			return( RTN_NG );
		}
	}

	// �t�@�C���N���[�Y
	fclose( fpSrc );
	fclose( fpDest );

	// �t�@�C���g���q���ύX
	iRet = rename( cSendFileTemp, cSendFile );
	if ( iRet != 0 ) {
		// �ُ�I��	LOG
//1.06 DELL printf("ResendFile rename status:[%d]\n", iRet);
		// 1.06 �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105ResendFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"ResendFile rename status:[%d] ", iRet);

		gintErrorCode = GD105_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	// �ԋp�p�Ƀt�@�C�����Ƒ��M�t�@�C���h�c��ݒ�
	memset( pHkkknri->hkkflnm, 0, sizeof( pHkkknri->hkkflnm ) );
//2006-07-06 CHG Osada �t�@�C�����������@�ύX
//	sprintf( pHkkknri->hkkflnm, "%s%04d%s",
//			 pHkkknri->ssnmtfilid,
//			 pHkkknri->hkksjno,
//			 GD105_FILEEXT_DATA );
	sprintf( pHkkknri->hkkflnm, "%s%s",
			sNewFlName, GD105_FILEEXT_DATA);	

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FGD105CreateHULFTFile()										  */
/*�@�@�\�T�v�@�FHULFT�]���p�t�@�C���쐬										  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FGD105Env *pEnv		�v���O�������\����					  */
/*�@�@��Q�����FSysknrmst *pSysknrmst �V�X�e���Ǘ��}�X�^���				  */
/*�@�@��R�����FHkkknri *pHkkknri	�񍐊Ǘ������\����					  */
/*�@�@��S�����Fchar *pDataFile		�񍐃f�[�^�t�@�C����					  */
/*�@�@��T�����Fint iLogicalCnt		�_�����R�[�h����						  */
/*�@�o�@�@�́@�F															  */
/*�@�@��R�����FHkkknri *pHkkknri	�񍐊Ǘ������\����					  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
// 2006-04-06 H.Suyama Change Start
#if 0
//int GD105CreateHULFTFile(GD105Env *pEnv, Sysknrmst *pSysknrmst, Hkkknri *pHkkknri, char *pDataFile)
#else
//2006-07-06 CHG Osada �t�@�C�����������@�ύX
//int GD105CreateHULFTFile(GD105Env *pEnv, Sysknrmst *pSysknrmst, Hkkknri *pHkkknri, char *pDataFile, int iLogicalCnt)
int GD105CreateHULFTFile(GD105Env *pEnv, Sysknrmst *pSysknrmst, Hkkknri *pHkkknri, char *pDataFile, int iLogicalCnt, Hkkknri *pHkkknriArrayOut)
#endif
// 2006-04-06 H.Suyama Change End
{
	int				iRet;
	char			cKjnsriymd[GD105_LEN_DATESHORT + 1];
	char			cSendFileTemp[PATH_MAX + 1];
	char			cSendFile[PATH_MAX + 1];
	FILE *			fpSrc;
	FILE *			fpDest;
	int				iLoop;
	int				iRecCnt;
	FILEHEADER		stHeader;
	FILETRAILER		stTrailer;
	char			cTemp[GD105_SIZE_BUFF + 1];
    //2006-07-06 ADD Osada �t�@�C�����������@�ύX
    char            sNewFlName[PATH_MAX + 1];
    char            sKaisibi[10];
    int             i;
    //

	// �������t�擾
	ZbmlChgAPDate( cKjnsriymd, pSysknrmst->kjnsriymd );
//1.06 DELL printf("������N����:[%s]\n", cKjnsriymd);
#ifdef _TRACE
	// 1.06 �ُ�I��	LOG
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD105CreateHULFTFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"������N����:[%s]", cKjnsriymd );
#endif

	// �t�@�C��������
//2006-07-06 CHG Osada �t�@�C�����������@�ύX
#if 0
	sprintf( cSendFile, "%s/%s/%s/%s%04d%04d%s",
			 pEnv->cDirToday,
			 pEnv->cDirSendFile,
			 pEnv->cDirSendREQ,
			 cKjnsriymd,
			 pSysknrmst->ssntubn,
			 pHkkknri->hkksjno,
			 GD105_FILEEXT_DATA );
	sprintf( cSendFileTemp, "%s/%s/%s/%s%04d%04d%s",
			 pEnv->cDirToday,
			 pEnv->cDirSendFile,
			 pEnv->cDirSendREQ,
			 cKjnsriymd,
			 pSysknrmst->ssntubn,
			 pHkkknri->hkksjno,
			 GD105_FILEEXT_TEMP );
#else
    memset(sNewFlName, 0, sizeof(sNewFlName));
    switch(pHkkknriArrayOut->hkkjkn) {
    case '1':
        memcpy(sNewFlName, "CTRLNO", 6);
        break;
    case '2':
        memcpy(sNewFlName, "PLOTNO", 6);
        break;
    case '3':
        for(i=0; i < 16 ;++i) {
            if( (pHkkknriArrayOut->knsgrp[i] == 0) || (pHkkknriArrayOut->knsgrp[i] == ' ') ) {
                pHkkknriArrayOut->knsgrp[i] = '-';
            }
        }
        memcpy(sNewFlName, pHkkknriArrayOut->knsgrp, 6);
        break;
    case '4':
        memcpy(sNewFlName, "IRAINO", 6);
        break;
    case '5':
        memcpy(sNewFlName, "KENTNO", 6);
        break;
    }
    for(i=0; i < 2 ;++i) {
        if( (pHkkknriArrayOut->seccd[i] == 0) || (pHkkknriArrayOut->seccd[i] == ' ') ) {
            pHkkknriArrayOut->seccd[i] = '-';
        }
    }
    sprintf( cSendFile, "%s/%s/%s/%s_%04d_%s_%s_%s%04d%s",
			 pEnv->cDirToday,
			 pEnv->cDirSendFile,
			 pEnv->cDirSendREQ,
             pSysknrmst->sateid, pHkkknriArrayOut->hkksjno,
             pHkkknriArrayOut->seccd, sNewFlName, cKjnsriymd, pSysknrmst->ssntubn, 
			 GD105_FILEEXT_DATA );
			 cKjnsriymd,
    sprintf( cSendFileTemp, "%s/%s/%s/%s_%04d_%s_%s_%s%04d%s",
			 pEnv->cDirToday,
			 pEnv->cDirSendFile,
			 pEnv->cDirSendREQ,
             pSysknrmst->sateid, pHkkknriArrayOut->hkksjno,
             pHkkknriArrayOut->seccd, sNewFlName, cKjnsriymd, pSysknrmst->ssntubn,
			 GD105_FILEEXT_TEMP );
#endif
	// �񍐃f�[�^�t�@�C���I�[�v��
	fpSrc = fopen ( pDataFile, "r" );
	if ( fpSrc == NULL ) {
		// �ُ�I��	LOG
// 1.06 DELL printf("file open error[%s]\n", pDataFile);
		// 1.06 �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105CreateHULFTFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"file open error[%s]", pDataFile );

		gintErrorCode = GD105_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	// HULFT�]���p�t�@�C���I�[�v��
	fpDest = fopen ( cSendFileTemp, "w" );
	if ( fpDest == NULL ) {
		// �ُ�I��	LOG
// 1.06 DELL printf("file open error[%s]\n", cSendFileTemp);
		// 1.06 �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105CreateHULFTFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"file open error[%s]", cSendFileTemp );

		gintErrorCode = GD105_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	// �t�@�C���w�b�_�̏o��
	memset( &stHeader, GD105_DATA_SPACE, sizeof( stHeader ) );
	// ���R�[�h���ʎq
	ZbmlStrCpy( stHeader.cID, GD105_FILE_HEADERID, sizeof( stHeader.cID ) );
	// ���M��ID
	ZbmlStrCpy( stHeader.cSendToID, pEnv->cSendIDSaki, sizeof( stHeader.cSendToID ) );
	// ���M��ID
	ZbmlStrCpy( stHeader.cSendFromID, pEnv->cSendIDMoto, sizeof( stHeader.cSendFromID ) );
	// ���M�������N����
	ZbmlStrCpy( stHeader.cSendDate, cKjnsriymd, sizeof( stHeader.cSendDate ) );
	// �ʔ�
	sprintf( cTemp, "%04d", pSysknrmst->ssntubn );
	ZbmlStrCpy( stHeader.cSeqNo, cTemp, sizeof( stHeader.cSeqNo ) );
	// �ް��۰ID
	ZbmlStrCpy( stHeader.cDataFlowID, pEnv->cDataFlowID, sizeof( stHeader.cDataFlowID ) );
	// ���Ұ�1
	//stHeader.cParam1
// 2006-04-20 H.Suyama Add Start
	// 1.07 INTEC UPD cSendIDSaki -> cSendIDMoto
	//							pEnv->cSendIDSaki,
//CHG E.Osada 2006-07-18
#if 0
	if ( GD105CopyFromLeft( stHeader.cParam1,
							pEnv->cSendIDMoto,
							8,
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	sprintf( cTemp, "%04d%04d", pSysknrmst->ssntubn, pHkkknri->hkksjno );
	if ( GD105CopyFromLeft( &stHeader.cParam1[8],
							cTemp,
							8,
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
#else
	memset(cTemp, 0, sizeof(cTemp));
	memset(stHeader.cParam1, 0, sizeof(stHeader.cParam1));
	sprintf( cTemp, "%s_%04d_%s_%s_%s%04d%s",
             pSysknrmst->sateid, pHkkknriArrayOut->hkksjno,
             pHkkknriArrayOut->seccd, sNewFlName, cKjnsriymd, pSysknrmst->ssntubn,
			 GD105_FILEEXT_DATA );
	/*
	if ( GD105CopyFromLeft( stHeader.cParam1,
							cTemp,
							8,
							FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	*/
	memset(stHeader.cParam1, ' ', 128);
	memcpy(stHeader.cParam1, cTemp, 18);
#endif
// 2006-04-20 H.Suyama Add End
	// ���Ұ�2
	//stHeader.cParam2
	// �\��
	//stHeader.cReserve
	// �Ō��'\n'������
	stHeader.cReserve[sizeof( stHeader.cReserve ) - 1] = GD105_FILE_LINEFEED;

	iRet = fwrite( (char *)&stHeader, sizeof( stHeader ), 1, fpDest);
	if ( iRet != 1 ) {
		//�G���[���O�o��
//1.06 DELL printf("fwrite header error \n");
		// 1.06 �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105CreateHULFTFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"fwrite header error" );

		return( RTN_NG );
	}

	// ���R�[�h�����N���A
	iRecCnt = 0;

	// �ǂݍ���
	while ( iRet = fgets( cTemp, sizeof ( cTemp ), fpSrc ) != NULL ) {
		if ( fputs( cTemp, fpDest ) < 0 ) {
			//�G���[���O�o��
//1.06 DELL printf("fputs error \n");
			// 1.06 �ُ�I��	LOG
			sFncPutLog(TRCKIND_ERROR, __FILE__,"GD105CreateHULFTFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"fputs error " );

			return( RTN_NG );
		}
		// ���R�[�h�����J�E���g
		++iRecCnt;
	}

	// �t�@�C���g���[���̏o��
	memset( &stTrailer, GD105_DATA_SPACE, sizeof( stTrailer ) );
	// ���R�[�h���ʎq
	ZbmlStrCpy( stTrailer.cID, GD105_FILE_TRAILERID, sizeof( stTrailer.cID ) );
	// ���M��ID
// 2006-04-06 H.Suyama Change Start
#if 0
//	ZbmlStrCpy( stHeader.cSendToID, pEnv->cSendIDSaki, sizeof( stHeader.cSendToID ) );
#else
	ZbmlStrCpy( stTrailer.cSendToID, pEnv->cSendIDSaki, sizeof( stTrailer.cSendToID ) );
#endif
// 2006-04-06 H.Suyama Change End
	// ���M��ID
// 2006-04-06 H.Suyama Change Start
#if 0
//	ZbmlStrCpy( stHeader.cSendFromID, pEnv->cSendIDMoto, sizeof( stHeader.cSendFromID ) );
#else
	ZbmlStrCpy( stTrailer.cSendFromID, pEnv->cSendIDMoto, sizeof( stTrailer.cSendFromID ) );
#endif
// 2006-04-06 H.Suyama Change End
	// ���M�������N����
	ZbmlStrCpy( stTrailer.cSendDate, cKjnsriymd, sizeof( stTrailer.cSendDate ) );
	// �ʔ�
	sprintf( cTemp, "%04d", pSysknrmst->ssntubn );
	ZbmlStrCpy( stTrailer.cSeqNo, cTemp, sizeof( stTrailer.cSeqNo ) );
	// �ް��۰ID
// 2006-04-06 H.Suyama Change Start
#if 0
//	ZbmlStrCpy( stHeader.cDataFlowID, pEnv->cDataFlowID, sizeof( stHeader.cDataFlowID ) );
#else
	ZbmlStrCpy( stTrailer.cDataFlowID, pEnv->cDataFlowID, sizeof( stTrailer.cDataFlowID ) );
#endif
// 2006-04-06 H.Suyama Change End
	// ����ں��ތ���
// 2006-04-06 H.Suyama Change Start
#if 0
//	sprintf( cTemp, "%04d", iRecCnt );
#else
	// ���R�[�h�����Ƀw�b�_�ƃg���[���������Z
// 2006-04-07 H.Suyama Change Start
#if 0
//	sprintf( cTemp, "%04d", iRecCnt + 2 );
#else
	sprintf( cTemp, "%08d", iRecCnt + 2 );
#endif
// 2006-04-07 H.Suyama Change End
#endif
// 2006-04-06 H.Suyama Change End
	ZbmlStrCpy( stTrailer.cPhysicalCnt, cTemp, sizeof( stTrailer.cPhysicalCnt ) );
	// �_��ں��ތ����P
	// ���R�[�h�����Ƀw�b�_�ƃg���[���������Z
// 2006-04-06 H.Suyama Change Start
#if 0
//	sprintf( cTemp, "%08d", iRecCnt + 2 );
#else
	sprintf( cTemp, "%08d", iLogicalCnt );
#endif
// 2006-04-06 H.Suyama Change End
	ZbmlStrCpy( stTrailer.cRecCnt1, cTemp, sizeof( stTrailer.cRecCnt1 ) );
	// �_��ں��ތ����Q
	memset( stTrailer.cRecCnt2, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt2 ) );
	// �_��ں��ތ����R
	memset( stTrailer.cRecCnt3, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt3 ) );
	// �_��ں��ތ����S
	memset( stTrailer.cRecCnt4, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt4 ) );
	// �_��ں��ތ����T
	memset( stTrailer.cRecCnt5, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt5 ) );
	// �_��ں��ތ����U
	memset( stTrailer.cRecCnt6, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt6 ) );
	// �_��ں��ތ����V
	memset( stTrailer.cRecCnt7, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt7 ) );
	// �_��ں��ތ����W
	memset( stTrailer.cRecCnt8, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt8 ) );
	// �_��ں��ތ����X
	memset( stTrailer.cRecCnt9, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt9 ) );
	// �_��ں��ތ����P�O
	memset( stTrailer.cRecCnt10, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt10 ) );
	// �_��ں��ތ����P�P
	memset( stTrailer.cRecCnt11, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt11 ) );
	// �_��ں��ތ����P�Q
	memset( stTrailer.cRecCnt12, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt12 ) );
	// �_��ں��ތ����P�R
	memset( stTrailer.cRecCnt13, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt13 ) );
	// �_��ں��ތ����P�S
	memset( stTrailer.cRecCnt14, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt14 ) );
	// �_��ں��ތ����P�T
	memset( stTrailer.cRecCnt15, GD105_DATA_CHAR0, sizeof( stTrailer.cRecCnt15 ) );
	// �\��
	//stTrailer.cReserve
	// �Ō��'\n'������
	stTrailer.cReserve[sizeof( stTrailer.cReserve ) - 1] = GD105_FILE_LINEFEED;

	iRet = fwrite( (char *)&stTrailer, sizeof( stTrailer ), 1, fpDest);
	if ( iRet != 1 ) {
		//�G���[���O�o��
//1.06 DELL printf("fwrite trailer error \n");
		// 1.06 �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105CreateHULFTFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"fwrite trailer error " );

		return( RTN_NG );
	}

	// �t�@�C���N���[�Y
	fclose( fpSrc );
	fclose( fpDest );

	// �t�@�C���g���q���ύX
	iRet = rename( cSendFileTemp, cSendFile );
	if ( iRet != 0 ) {
		// �ُ�I��	LOG
//1.06 DELL printf("CreateHULFTFile rename status:[%d]\n", iRet);
		// 1.06 �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105CreateHULFTFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"CreateHULFTFile rename status:[%d] ", iRet );

		gintErrorCode = GD105_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	// �ԋp�p�Ƀt�@�C�����Ƒ��M�t�@�C���h�c��ݒ�
	memset( pHkkknri->hkkflnm, 0, sizeof( pHkkknri->hkkflnm ) );
//2006-07-06 CHG Osada �t�@�C�����������@�ύX
//	sprintf( pHkkknri->hkkflnm, "%s%04d%04d%s",
//			 cKjnsriymd,
//			 pSysknrmst->ssntubn,
//			 pHkkknri->hkksjno,
//			 GD105_FILEEXT_DATA );
	sprintf( pHkkknri->hkkflnm, "%s_%04d_%s_%s_%s%04d%s",
             pSysknrmst->sateid, pHkkknriArrayOut->hkksjno,
             pHkkknriArrayOut->seccd, sNewFlName, cKjnsriymd, pSysknrmst->ssntubn,
			 GD105_FILEEXT_DATA );
	memset( pHkkknri->ssnmtfilid, 0, sizeof( pHkkknri->ssnmtfilid ) );
	sprintf( pHkkknri->ssnmtfilid, "%s%04d",
			 cKjnsriymd,
			 pSysknrmst->ssntubn );

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FGD105CreateFile()											  */
/*�@�@�\�T�v�@�F�񍐃f�[�^�t�@�C���쐬										  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FGD105Env *pEnv		�v���O�������\����					  */
/*�@�@��Q�����FSysknrmst *pSysknrmst �V�X�e���Ǘ��}�X�^���				  */
/*�@�@��R�����FKekka *pKekkaArray	�������ʏ��							  */
/*�@�@��S�����Fint iKekkaNum		�������ʏ�񌏐�						  */
/*�@�o�@�@�́@�F															  */
/*�@�@��T�����Fint *piHkkssknsu	�쐬����								  */
/*�@�@��U�����Fint *piHkkhrysu		�ۗ�����								  */
/*�@�@��V�����Fchar *pFileName		�t�@�C����								  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int GD105CreateFile(GD105Env *pEnv,
					Sysknrmst *pSysknrmst,
					Kekka *pKekkaArray,
					int iKekkaNum,
					int *piHkkssknsu,
					int *piHkkhrysu,
					char *pFileName,
					int *sqlErrorFlag)//2006.12.08 Kim Jinsuk DB�G���[���ُ�I��������
{
	int				iRet;
	struct dirent	**pDirEnt;
	int				iFileCnt;
	int	 			iSeqNo;
	char			cSeqBuff[10];
	BmlDate			today;
	char			cToday[GD105_LEN_DATESHORT + 1];
	char			cFileNameTemp[PATH_MAX + 1];
	char			cFileName[PATH_MAX + 1];
	FILE *			fp;
	int				iLoop;
	GD105Rec		stGD105RecTemp;
	int				iKekkaLoop;
	GD105Rec		stGD105Rec[GD105_REC_LOOP_MAX];
	int				iFileLoopIdx;
/*	int				iCmmtCnt=0; */
	int				iFlg911=0;

/* 2.00 2009.05.19 ���ʕϊ��}�X�^�Ή� START */
	char			cSstcd[7+1];		/* �{�݃R�[�h */
	int				iSstcdLoopCnt;		/* �{�݃R�[�h�p���[�v�J�E���^ */
	int				iKkaconvCnt;		/* ���ʕϊ��}�X�^�������[�v�J�E���^ */
	int				iRetChk;			/* ���ʕϊ������t���O */
/* 2.00 2009.05.19 ���ʕϊ��}�X�^�Ή� END */

	// �����`�F�b�N
	if ( pEnv == NULL || pSysknrmst == NULL || pKekkaArray == NULL ||
		 piHkkssknsu == NULL || piHkkhrysu == NULL || pFileName == NULL ) {
		// �ُ�I��	LOG
//1.06 DELL printf("GD105CreateFile parameter is NULL\n");
		// 1.06 �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105CreateFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"GD105CreateFile parameter is NULL");

		gintErrorCode = GD105_STSCODE_ERR_FR_FILE;
		return( RTN_NG );
	}

	// �f�[�^�t�@�C���p�f�B���N�g��������
	// �t�B���^�ɂ��A������YYYYMMDD9999�Ŏn�܂�t�@�C���̂݌���
	if ( ( iFileCnt = scandir( pEnv->cDirDataFile,
							   &pDirEnt,
							   (void *)GD105DataFileFilter,
							   alphasort ) ) < 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_DIR;
		return( RTN_NG );
	}

	// �t�@�C��SEQ���̔�
	if ( iFileCnt == 0 ) {
		iSeqNo = 1;
	} else {
		memset( cSeqBuff, 0, sizeof( cSeqBuff ) );
		strcpy( cFileName, pDirEnt[iFileCnt - 1]->d_name );
		memcpy( cSeqBuff, &cFileName[GD105_LEN_DATESHORT],
			GD105_LEN_FILESEQNO );
		iSeqNo = atoi( cSeqBuff ) + 1;
	}

	// �������������
	for ( iLoop = 0; iLoop < iFileCnt; iLoop++ ) {
		ZbmlFree( pDirEnt[iLoop] );
	}

	// �������t�擾
	if ( ZbmlDateGetToday(&today) == FALSE ) {
		return( RTN_NG );
	}
	sprintf( cToday, "%04d%02d%02d", today.year, today.month, today.day);

	// �t�@�C��������
	sprintf( cFileName, "%s/%s%04d%s",
			 pEnv->cDirDataFile, cToday, iSeqNo, GD105_FILEEXT_DATA );

	// �t�@�C���I�[�v��
	fp = fopen ( cFileName, "w" );
	if ( fp == NULL ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	// ���ʏ����P��������
	for ( iKekkaLoop = 0, iFileLoopIdx  = 0;
		  iKekkaLoop < iKekkaNum;
		  iKekkaLoop++ ) {
		// �ۗ����ǂ����`�F�b�N
		if ( pKekkaArray[iKekkaLoop].knsflg == GD105_DB_KNSFLG_HORYU ) {
			// �ۗ����J�E���^ +1
			++*piHkkhrysu;
			continue;
		}

		// Add 2007.05.09 waj
		// knskka1,knskka2���ɃX�y�[�X�̏ꍇ�A�񍐃��R�[�h���쐬�����ۗ������Ƃ���
		// Add 2008.02.07 Nagata
		// knskka2��'////////'�̏ꍇ�A�񍐃��R�[�h���쐬�����ۗ������ɂ���B
		if ( ( (strncmp(pKekkaArray[iKekkaLoop].knskka1, "            ", 12) == 0) &&
		       (strncmp(pKekkaArray[iKekkaLoop].knskka2, "                        ", 24) == 0) )
			|| strncmp(pKekkaArray[iKekkaLoop].knskka2, "////////", 8) == 0) {

            sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105CreateFile", __LINE__,
                        EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
                        "knskka1,knskka2���ɃX�y�[�X�̂��ߕۗ��Ƃ��� [%s %s %d]",
						pKekkaArray[iKekkaLoop].sriymd,pKekkaArray[iKekkaLoop].kmkcd,pKekkaArray[iKekkaLoop].knsseq);

			// �����t���O�ɕۗ���ݒ�
			pKekkaArray[iKekkaLoop].knsflg = GD105_DB_KNSFLG_HORYU;
			
			// �ۗ����J�E���^ +1
			++*piHkkhrysu;

			continue;
		}

		// �J�Ԃ������ɒB������t�@�C���o��
		if ( iFileLoopIdx >= GD105_REC_LOOP_MAX ) {
			// �t�@�C���o��
			if ( GD105WriteFile( fp, &stGD105Rec[0], GD105_REC_LOOP_MAX ) == RTN_NG ) {
				// �ُ�I��	LOG
//1.06 DELL printf("GD105WriteFile error\n");
				// 1.06 �ُ�I��	LOG
				sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105CreateFile",__LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"GD105WriteFile error" );

				return( RTN_NG );
			}

			iFileLoopIdx = 0;
		}

/* 2.00 2009.05.19 ���ʕϊ��}�X�^�Ή� START */
		/*******************************************************************/
		/* knskka2kbn == '0'�̏ꍇ�A���ɃR�����g���͂���Ă����ԂȂ̂ŁA */
		/* �����ϊ��̑Ώۂɂ��Ȃ��B                                        */
		/*******************************************************************/
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"pKekkaArray[%d].knskka2kbn[0] = [%c]", iKekkaLoop, pKekkaArray[iKekkaLoop].knskka2kbn[0] );
#endif
		if (pKekkaArray[iKekkaLoop].knskka2kbn[0] != GD105_DATA_CHAR0)
		{
			/* ���ʕϊ������t���O������ */
			iRetChk = 0;

			/**************************************************************************/
			/* ���ʃe�[�u���̎{�݃R�[�h�ƌ��ʕϊ��}�X�^�̎{�݃R�[�h����v���Ȃ��ꍇ�A */
			/* �{�݃R�[�h��'0000000'�ł�����x��������B                              */
			/**************************************************************************/
			for (iSstcdLoopCnt = 0; iSstcdLoopCnt < GD105_SSTCD_LOOP_CNT; iSstcdLoopCnt++)
			{
				memset(cSstcd, 0, sizeof(cSstcd));
				/* 1��ڃ��[�v�F�{�݃R�[�h = ���ʃe�[�u���̎{�݃R�[�h(�������A'0000000' �łȂ��ꍇ) */
				if (iSstcdLoopCnt == 0 &&
					memcmp(pKekkaArray[iKekkaLoop].sstcd, GD105_SSTCD_ALL_ZERO, sizeof(pKekkaArray[iKekkaLoop].sstcd) - 1) != 0)
				{
					strcpy(cSstcd, pKekkaArray[iKekkaLoop].sstcd);
				}
				/* 2��ڃ��[�v�F�{�݃R�[�h = '0000000' (ALL�[��)�ł�����x�����ɍs�� */
				else
				{
					strcpy(cSstcd, GD105_SSTCD_ALL_ZERO);
					iSstcdLoopCnt++;
				}

				/********************************************************************/
				/* ���ʕϊ��}�X�^�`�F�b�N(�������̍��ڂ��}�X�^�ɐݒ肳��Ă��邩�H) */
				/********************************************************************/
				for (iKkaconvCnt = 0; iKkaconvCnt < g_iNumOut; iKkaconvCnt++)
				{
#ifdef _DEBUG
					sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"�� ���ʃL�[�ƌ��ʕϊ��}�X�^�L�[��r" );
					sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"  �� ���ʃL�[" );
					sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"    pKekkaArray[%d].knsgrp   = [%s]", iKekkaLoop, pKekkaArray[iKekkaLoop].knsgrp );
					sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"    pKekkaArray[%d].kmkcd    = [%s]", iKekkaLoop, pKekkaArray[iKekkaLoop].kmkcd );
					sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"    cSstcd                   = [%s]", cSstcd );

					sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"  �� ���ʕϊ��}�X�^�L�[" );
					sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"    g_pKkaconvmst[%d].knsgrp = [%s]", iKkaconvCnt, g_pKkaconvmst[iKkaconvCnt].knsgrp );
					sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"    g_pKkaconvmst[%d].kmkcd  = [%s]", iKkaconvCnt, g_pKkaconvmst[iKkaconvCnt].kmkcd );
					sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"    g_pKkaconvmst[%d].sstcd  = [%s]", iKkaconvCnt, g_pKkaconvmst[iKkaconvCnt].sstcd );
#endif

					/* ���L�̏����Ń}�X�^�����𔲂���(�}�X�^�̓v���C�}���L�[�Ń\�[�g���Ă��薳�ʃ��[�v�����Ȃ���)   */
					/*   �E����.����G < �}�X�^.����G                                                                */
					/*   �E����.����G = �}�X�^.����G && ����.����CD < �}�X�^.����CD                                 */
					/*   �E����.����G = �}�X�^.����G && ����.����CD = �}�X�^.����CD && ����.�{��CD < �}�X�^.�{��CD  */
					if ((atoi(pKekkaArray[iKekkaLoop].knsgrp) <  atoi(g_pKkaconvmst[iKkaconvCnt].knsgrp)) ||
						
						(atoi(pKekkaArray[iKekkaLoop].knsgrp) == atoi(g_pKkaconvmst[iKkaconvCnt].knsgrp)  &&
						 atoi(pKekkaArray[iKekkaLoop].kmkcd)  <  atoi(g_pKkaconvmst[iKkaconvCnt].kmkcd))  ||
						
						(atoi(pKekkaArray[iKekkaLoop].knsgrp) == atoi(g_pKkaconvmst[iKkaconvCnt].knsgrp)  &&
						 atoi(pKekkaArray[iKekkaLoop].kmkcd)  == atoi(g_pKkaconvmst[iKkaconvCnt].kmkcd)   &&
						 atoi(cSstcd)                         <  atoi(g_pKkaconvmst[iKkaconvCnt].sstcd)))
					{
#ifdef _DEBUG
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"�� ���ʃL�[ < ���ʕϊ��}�X�^�L�[ �Ȃ̂� break�I" );
#endif
						break;
					}

					/* �����O���[�v�A���ڃR�[�h�A�{�݃R�[�h�A�ޗ��R�[�h�A�J�n���`�p�~���ɍ��v�����ꍇ */
					if (memcmp(g_pKkaconvmst[iKkaconvCnt].knsgrp, pKekkaArray[iKekkaLoop].knsgrp, sizeof(pKekkaArray[iKekkaLoop].knsgrp)-1) == 0 &&
						memcmp(g_pKkaconvmst[iKkaconvCnt].kmkcd, pKekkaArray[iKekkaLoop].kmkcd, sizeof(pKekkaArray[iKekkaLoop].kmkcd)-1) == 0 &&
						memcmp(g_pKkaconvmst[iKkaconvCnt].sstcd, cSstcd, sizeof(cSstcd)-1) == 0 &&
						(memcmp(g_pKkaconvmst[iKkaconvCnt].kaiymd, pKekkaArray[iKekkaLoop].knskisymd, sizeof(pKekkaArray[iKekkaLoop].knskisymd)-1) <= 0 &&
						 memcmp(pKekkaArray[iKekkaLoop].knskisymd, g_pKkaconvmst[iKkaconvCnt].haiymd, sizeof(pKekkaArray[iKekkaLoop].knskisymd)-1) <= 0))
					{
#ifdef _DEBUG
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"�� ���ʕϊ��}�X�^�`�F�b�N - �J�n" );
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"  �� ���ʕϊ��}�X�^�f�[�^" );
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"    g_pKkaconvmst[%d]->knsgrp = [%s]", iKkaconvCnt, g_pKkaconvmst[iKkaconvCnt].knsgrp );
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"    g_pKkaconvmst[%d]->kmkcd  = [%s]", iKkaconvCnt, g_pKkaconvmst[iKkaconvCnt].kmkcd );
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"    g_pKkaconvmst[%d]->sstcd  = [%s]", iKkaconvCnt, g_pKkaconvmst[iKkaconvCnt].sstcd );
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"    g_pKkaconvmst[%d]->kaiymd = [%s]", iKkaconvCnt, g_pKkaconvmst[iKkaconvCnt].kaiymd );
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"    g_pKkaconvmst[%d]->haiymd = [%s]", iKkaconvCnt, g_pKkaconvmst[iKkaconvCnt].haiymd );
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"  �� ���ʏ��f�[�^" );
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"    pKekkaArray[%d].knskisymd = [%s]", iKekkaLoop, pKekkaArray[iKekkaLoop].knskisymd );
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"    pKekkaArray[%d].knsgrp    = [%s]", iKekkaLoop, pKekkaArray[iKekkaLoop].knsgrp );
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"    pKekkaArray[%d].kmkcd     = [%s]", iKekkaLoop, pKekkaArray[iKekkaLoop].kmkcd );
						sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"    cSstcd                    = [%s]", cSstcd );
#endif

						/* ���ʕϊ��`�F�b�N�֐� */
						iRet = GD105KkaConvChk(&pKekkaArray[iKekkaLoop], &g_pKkaconvmst[iKkaconvCnt], cSstcd);
						/* ���ʕϊ������ꍇ */
						if (iRet == RTN_OK)
						{
							/* ���ʕϊ��ς� */
#ifdef _DEBUG
							sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
										"  �� ���ʕϊ��ς�" );
#endif
							iRetChk = 1;
							break;
						}
						/* �ϊ��ΏۂɂȂ炸�A�X�L�b�v�����ꍇ */
						else if (iRet == RTN_SKIP)
						{
#ifdef _DEBUG
							sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
										"  �� �ϊ��ΏۂɂȂ炸�A�X�L�b�v����" );
#endif
						}
						/* ��������̃G���[���������ꍇ */
						else if ( iRet == RTN_NG )
						{
							// �ُ�I��	LOG
							sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105CreateFile", __LINE__,
										EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
										"GD105KkaConvChk ERROR iRet = [%d]", iRet );

							return RTN_NG;
						}
					}
				}
				
				/* ���ʕϊ������ꍇ�͎{�݃��[�v�����𔲂��� */
				if (iRetChk == 1)
				{
#ifdef _DEBUG
					sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"  �� �{�݃��[�v�����𔲂���" );
#endif
					break;
				}
			}
		}
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CreateFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�� ���ʕϊ��}�X�^�`�F�b�N - �I��" );
#endif
/* 2.00 2009.05.19 ���ʕϊ��}�X�^�Ή� END */

		// ���ʂ��t�@�C���o�͌`���ɓW�J
		if ( GD105MakeData( &pKekkaArray[iKekkaLoop],
							pSysknrmst->lbcd,
							&stGD105Rec[iFileLoopIdx] ) == RTN_NG ) {
			// �ُ�I��	LOG
			sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105CreateFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"GD105MakeData error" );

			return( RTN_NG );
		}

		++*piHkkssknsu;

		++iFileLoopIdx;
	}

	// 1.12 ADD �ۗ��ȊO�񍐑Ώ�0���̏ꍇ�̍l��
	if( *piHkkssknsu == 0 || iFlg911 == 1 ){
			// �t�@�C���N���[�Y
			fclose( fp );
			// ���ԃt�@�C���Ȃ̂�0byte�쐬��OK�Ƃ��A�t�@�C���폜�͍s��Ȃ�
			return( RTN_NG );
	}

	// �t�@�C���o��
	if ( GD105WriteFile( fp, &stGD105Rec[0], iFileLoopIdx ) == RTN_NG ) {
		// �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105CreateFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"GD105WriteFile error " );
		return( RTN_NG );
	}

	// �t�@�C���N���[�Y
	fclose( fp );

	// �t�@�C�����i�t���p�X�j��ԋp
	ZbmlInfocpy( pFileName, cFileName, PATH_MAX );
	return( RTN_OK );
}


/******************************************************************************/
/*�@�� �� ���@�FGD105UpdateKekka()											  */
/*�@�@�\�T�v�@�F�񍐃f�[�^ �t���O�X�V										  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FGD105Env *pEnv		�v���O�������\����					  */
/*�@�@��Q�����FSysknrmst *pSysknrmst �V�X�e���Ǘ��}�X�^���				  */
/*�@�@��R�����FKekka *pKekkaArray	�������ʏ��							  */
/*�@�@��S�����Fint iKekkaNum		�������ʏ�񌏐�						  */
/*�@�o�@�@�́@�F															  */
/*�@�@��T�����Fint *splErrorFlag	�G���[��~�t���O						  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int GD105UpdateKekka(GD105Env *pEnv,
					Sysknrmst *pSysknrmst,
					Kekka *pKekkaArray,
					int iKekkaNum,
					int *sqlErrorFlag)
{
	int				iRet;
	int				iLoop;
	int				iKekkaLoop;
	int				iFileLoopIdx;
	int				iCmmtCnt=0;

	char			last_sriymd[11];
	char			last_kntno[11];
	char			last_knsgrp[17];

	strcpy(last_sriymd, pKekkaArray[0].sriymd);
	strcpy(last_kntno, pKekkaArray[0].kntno);
	strcpy(last_knsgrp, pKekkaArray[0].knsgrp);

	for ( iKekkaLoop = 0, iFileLoopIdx  = 0;
		  iKekkaLoop < iKekkaNum;
		  iKekkaLoop++ ) {

		/* COMMIT�P�ʂ����̒P�ʂɕύX ������INI�t�@�C���ɐݒ� */
		if ( (strncmp(pKekkaArray[iKekkaLoop].sriymd, last_sriymd , 11) != 0) ||
			 (strncmp(pKekkaArray[iKekkaLoop].kntno, last_kntno , 11) != 0) ||
			 (strncmp(pKekkaArray[iKekkaLoop].knsgrp, last_knsgrp , 17) != 0) ) {

			++iCmmtCnt;
			if( iCmmtCnt >= pEnv->iCommitSu ){
        		ZdbCommit();
				iCmmtCnt=0;
			}
		}

		if ( pKekkaArray[iKekkaLoop].knsflg == GD105_DB_KNSFLG_HORYU ) {
			// �ۗ��̏ꍇ�̓t���O��ύX���Ȃ��B
		} else {
			// ���ʏC���t���O���J�E���g�A�b�v�i�ő�'9'�j
			if ( pKekkaArray[iKekkaLoop].kkassflg == GD105_DATA_SPACE ) {
				pKekkaArray[iKekkaLoop].kkassflg = '0';
			} else if ( pKekkaArray[iKekkaLoop].kkassflg != GD105_DB_KKASSFLG_MAX ) {
				++pKekkaArray[iKekkaLoop].kkassflg;
			}

			// �����t���O���񍐍�
			pKekkaArray[iKekkaLoop].knsflg = GD105_DB_KNSFLG_DONE;
		}

		// ���X�V�����͊֐����Őݒ�
        int nRetValue;

		// �������ʏ����X�V
		iRet = ZdbKekkaGD105Update( &pKekkaArray[iKekkaLoop] );
		if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
			// �ُ�I��	LOG
			sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105UpdateKekka", __LINE__,
						EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
						"ZdbKekkaGD105Update error(%d)", iRet);

            nRetValue = iRet;

			// ���[���o�b�N
			ZdbRollback();

			if((nRetValue < 0) && (nRetValue !=-803) && (nRetValue != -911)) {
				*sqlErrorFlag = 1;
				sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbKekkaGD105Update", __LINE__,
							EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
							"DB �G���[�@�����@error value 0 %d", iRet);
			}
			return( RTN_NG );
		}

		if ( pKekkaArray[iKekkaLoop].knsflg == GD105_DB_KNSFLG_HORYU ) {
			//�ۗ��̏ꍇ�� ZdbKekkaGD105UpdateOthers(���񍐊����ւ̍X�V)���s��Ȃ��B
		} else if ( pKekkaArray[iKekkaLoop].kkajkcd == GD105_DB_KKAJKCD_LAST ) {
			iRet = ZdbKekkaGD105UpdateOthers( &pKekkaArray[iKekkaLoop] );
			if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
				// 1.06 �ُ�I��	LOG
				sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105UpdateKekka",__LINE__,
							EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
							"ZdbKekkaGD105UpdateOthers error (%d)", iRet);

 				nRetValue = iRet;				

				// ���[���o�b�N
				ZdbRollback();
			
				if((nRetValue < 0) && (nRetValue !=-803) && (nRetValue != -911)) {
    				*sqlErrorFlag = 1;
					sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbKekkaGD105Update", __LINE__,
								EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
								"DB �G���[�@�����@error value 0 %d", iRet);
				}
				return( RTN_NG );
			}
		}
		
		strcpy(last_sriymd, pKekkaArray[iKekkaLoop].sriymd);
		strcpy(last_kntno, pKekkaArray[iKekkaLoop].kntno);
		strcpy(last_knsgrp, pKekkaArray[iKekkaLoop].knsgrp);

		++iFileLoopIdx;
	}

	ZdbCommit();

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FsFncShmCrt()												  */
/*�@�@�\�T�v�@�F���L����������												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FGD105Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F�Ȃ�														  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
static int sFncShmCrt( GD105Env *pEnv )
{
	int	 *shmData;

	// �擾
	pEnv->shm_Id = shmget( (key_t)pEnv->shm_Key,
							GD105_SHM_SIZE,
							0666 | IPC_CREAT );
	if ( pEnv->shm_Id < 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_SHM_GET;
		return( RTN_NG );
	}

	// �A�^�b�`
	shmData = ( int * ) shmat( pEnv->shm_Id, 0 , 0 );
	if ( shmData == ( int * )-1 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_SHM_AT;
		return( RTN_NG );
	}
loging ( "stocker : ���L������[CRT] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n",
		 pEnv->shm_Key, pEnv->shm_Id, *shmData, shmData );

	// �l�ݒ�
	*shmData = 0;

	// �f�^�b�`
	if ( shmdt( shmData ) == -1 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_SHM_DT;
		return( RTN_NG );
	}

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FsFncShmGet()												  */
/*�@�@�\�T�v�@�F���L�������擾												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FGD105Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@�@��Q�����Fint *pshmData		�l										  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
static int sFncShmGet( GD105Env *pEnv, int *pshmData )
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
		gintErrorCode = GD105_STSCODE_ERR_SHM_AT;
		return( RTN_NG );
	}

	// �l�ݒ�
	*pshmData = *shmData;

loging ( "stocker : ���L������[GET] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n",
		 pEnv->shm_Key, pEnv->shm_Id, *shmData, shmData );
	// �f�^�b�`
	if ( shmdt( shmData ) == -1 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_SHM_DT;
		return( RTN_NG );
	}

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FsFncShmDel()												  */
/*�@�@�\�T�v�@�F���L�������폜												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FGD105Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
static int sFncShmDel( GD105Env *pEnv )
{
	int	 *shmData;

loging ( "%s : ���L������[DEL] shmKey[%d]-ID[%d]\n",
		 MYAPP_APP_NAME, pEnv->shm_Key, pEnv->shm_Id);
	// �폜
	if ( shmctl( pEnv->shm_Id, IPC_RMID, NULL) < 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD105_STSCODE_ERR_SHM_DEL;
		return( RTN_NG );
	}
	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�F_sFncEnvDip()												  */
/*�@�@�\�T�v�@�F�v���O�������ϐ��o�͊֐��y�g���[�X�p�z					  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FGD105Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�F����														  */
/******************************************************************************/
static void _sFncEnvDip( GD105Env *pEnv )
{
//#if defined ( _TRACE )
	loging( "########## GD105 - _sFncEnvDip ##########\n" );
	loging( "\t%s : [%s]\n", GD105_PRM_DBNAME,		 pEnv->cDBName );
	loging( "\t%s : [%s]\n", GD105_PRM_DBUSER,		 pEnv->cDBUser );
	loging( "\t%s : [%s]\n", GD105_PRM_DBPAWD,		 pEnv->cDBPawd );
	loging( "\t%s : [%s]\n", GD105_PRM_DIR_DATAFILE,   pEnv->cDirDataFile );
	loging( "\t%s : [%s]\n", GD105_PRM_SLEEP_SEC,	  pEnv->iSleepSec );
	loging( "\t%s : [%s]\n", GD105_PRM_SHM_KEY,	pEnv->shm_Key );
	loging( "\t%s : [%s]\n", GD105_PRM_FILE_DBG,	pEnv->cDebugLogName );
	loging( "\t%s : [%s]\n", GD105_PRM_FILE_TR,	pEnv->cTraceLogName );
	loging( "\t%s : [%s]\n", GD105_PRM_FILE_ACS,	pEnv->cAccessLogName );
	loging( "\t%s : [%s]\n", GD105_PRM_FILE_ERR,	pEnv->cErrorLogName );
	loging( "\t%s : [%s]\n", GD105_PRM_UP_ID,		pEnv->cUpdateId );
	loging( "\t%s : [%s]\n", GD105_PRM_UP_NM,		pEnv->cUpdateName );
	loging( "\t%s : [%s]\n", GD105_PRM_PROC_MD,	pEnv->proc_mode );
	loging( "########## GD105 - _sFncEnvDip ##########\n" );
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
/*�@�@�\�T�v�@�F�񍐃f�[�^�t�@�C���쐬�������C��							  */
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
	GD105Env	stEnv;

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
