/********************************************************************/
/*																	*/
/*		�a�l�k�l���������V�X�e��									*/
/*																	*/
/*		�V�X�e����	�F������V�X�e��								*/
/*		�t�@�C����	�FGD205Main.c									*/
/*		�T�v		�F�ً}���ʕ񍐃t�@�C���쐬����					*/
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
/*  3.01    2007/06/05      INTEC.INC       �ً}�p�ɕύX            */
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
#include "GD205Main.h"
#include "GD205Hkkknri.h"

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
GD205_STSCODE		gintErrorCode;
struct stcLogMember	gstLogMem;
char        G_msg[256];     // 1.06 ADD LogMessage

/******************************************************************************/
/*�@�� �� ���@�FGD205ConvTimestamp()										  */
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
void GD205ConvTimestamp(ULONG ulTm, char *pDest)
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
/*�@�� �� ���@�FGD205ConvNumber()                                             */
/*�@�@�\�T�v�@�F�˗���No�A����No�ϊ��֐�                                      */
/*�@���@�@�́@�F                                                              */
/*�@�@��Q�����Fchar *pSrc          �ϊ��O������                              */
/*�@�@�@�@�@�@                      [1][2][3][4][5][6][7][8][9][10][11]\0     */
/*�@�o�@�@�́@�F                                                              */
/*�@�@��P�����Fchar *pDest         �ϊ��㕶����                              */
/*�@�@�@�@�@�@                      [3][4][5] 0  0 [6][7][8][9][10][11]       */
/*�@���A���@�Fint                                                           */
/*�@�@�@�@�@�@      RTN_OK  : ����I��                                        */
/*�@�@�@�@�@�@      RTN_NG  : �ُ�I��                                        */
/******************************************************************************/
int GD205ConvNumber(char *pDest, char *pSrc)
{
    // �|�C���^�̃`�F�b�N
    if ( pDest == NULL || pSrc == NULL ) {
        return( RTN_NG );
    }

    // �ϊ��O������̒����`�F�b�N
    if ( strlen( pSrc ) < GD205_LEN_NOITEM ) {
        return( RTN_NG );
    }

	/* PNC11���ɕϊ� */
	sprintf (pDest,"%-3.3s00%-6.6s",&pSrc[GD205_POS_SRCNO1],&pSrc[GD205_POS_SRCNO2]);

    return( RTN_OK );
}


/******************************************************************************/
/*�@�� �� ���@�FGD205CopyFromLeft()											  */
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
int GD205CopyFromLeft(char *pDest, char *pSrc, int iSize, BOOL bMbFlg)
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
/*�@�� �� ���@�FGD205CopyFromRight()										  */
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
int GD205CopyFromRight(char *pDest, char *pSrc, int iSize, BOOL bMbFlg)
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

/******************************************************************************/
/*�@�� �� ���@�FGD205CopyReplace()   										  */
/*�@�@�\�T�v�@�F�����_���폜���A�OZERO��ҏW����    						  */
/*�@���@�@�́@�F															  */
/*�@�@��Q�����Fchar *pSrc			�R�s�[��������							  */
/*�@�@��R�����Fint iSize			�R�s�[����								  */
/*�@�o�@�@�́@�F															  */
/*�@�@��P�����Fchar *pDest			�R�s�[�㕶����							  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int GD205CopyReplace(char *pDest, char *pSrc, int iSize )
{
	int	iTargetPos;
	int	iLoop;
	int	iCopySize;

	// �|�C���^�̃`�F�b�N
	if ( pDest == NULL || pSrc == NULL ) {
		return( RTN_NG );
	}

	iCopySize=strlen( pSrc );
	iTargetPos=iSize;
	for( iTargetPos=iSize; iTargetPos >= 0 ; iTargetPos-- ){
			// �o�̓T�C�Y�ɖ����Ȃ��ꍇ0�Ŗ��߂�
		if( iCopySize < 0 ){
			pDest[iTargetPos]='0';	
		} else
			// �����_���폜����
		if( pSrc[iCopySize] == '.' ){
			// ���O�o��
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"�����_�폜" );
			iTargetPos++;
		} else 
			// �󔒂�0�ɒu������
		if( pSrc[iCopySize] == ' ' ){
			pDest[iTargetPos]='0';	
		} else {
			pDest[iTargetPos]=pSrc[iCopySize];
		}
		iCopySize--;
	}

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD205CopyReplace", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"IN[%s] OUT[%s]\n", pSrc ,pDest );

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
/*�@�@��R�����FGD205Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int initFunction( int argc, char *argv[], GD205Env *pEnv )
{
	char	cPrmBuf[256];
	char	*lc_login;

	// ������
	// �G���[�X�e�[�^�X�ύX
	gintErrorCode = 0;
	// �v���O�������ϐ�������
	memset( pEnv, '\0', sizeof( GD205Env ) );

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

	// �J�n���O�o��
	sFncPutLog( TRCKIND_TRACE, __FILE__, "", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�v���O�����N��" );

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
		gintErrorCode = GD205_STSCODE_ERR_PRM_FILE;
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZZbmlPrmOpen", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�p�����[�^�t�@�C���̃I�[�v���Ɏ��s���܂���[%s]", 
					pEnv->pcFileNamePRM );
		return( RTN_NG );
	}

	// �f�[�^�x�[�X�ڑ���
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_DBNAME,
						 pEnv->cDBName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���O�C�����[�U
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_DBUSER,
						pEnv->cDBUser ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���O�C���p�X���[�h
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_DBPAWD,
						pEnv->cDBPawd ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �񍐃f�[�^�t�@�C���o�̓f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_DIR_DATAFILE,
						pEnv->cDirDataFile ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �]���f�[�^�t�@�C���o�̓f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_DIR_TODAY,
						pEnv->cDirToday ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �]���f�[�^�t�@�C���ߋ��f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_DIR_OLDDAY,
						pEnv->cDirOldday ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �]���f�[�^�t�@�C�����M�f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_DIR_SENDFILE,
						pEnv->cDirSendFile ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �]���f�[�^�t�@�C��REQUEST�f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_DIR_SENDREQ,
						pEnv->cDirSendREQ ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �]���f�[�^�t�@�C��OK�f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_DIR_SENDOK,
						pEnv->cDirSendOK ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �]���f�[�^�t�@�C��ERR�f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_DIR_SENDERR,
						pEnv->cDirSendERR ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
/* 3.01 DELL STA 
DEL	// �f�[�^�t���[�h�c
DEL	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_DATAFLOWID,
DEL						pEnv->cDataFlowID ) != 0 ) {
DEL		// �ُ�I��	LOG
DEL		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
DEL		return( RTN_NG );
DEL	}
DEL	// ���M���h�c
DEL	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_SENDID_MOTO,
DEL						pEnv->cSendIDMoto ) != 0 ) {
DEL		// �ُ�I��	LOG
DEL		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
DEL		return( RTN_NG );
DEL	}
DEL	// ���M��h�c
DEL	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_SENDID_SAKI,
DEL						pEnv->cSendIDSaki ) != 0 ) {
DEL		// �ُ�I��	LOG
DEL		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
DEL		return( RTN_NG );
DEL	}
*/
	// �f�o�b�O���O�t�@�C��
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_FILE_DBG,
						pEnv->cDebugLogName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �g���[�X���O�t�@�C��
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_FILE_TR,
						pEnv->cTraceLogName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �A�N�Z�X���O�t�@�C��
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_FILE_ACS,
						pEnv->cAccessLogName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �G���[���O�t�@�C��
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_FILE_ERR,
						pEnv->cErrorLogName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���L�������L�[�擾
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_SHM_KEY,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->shm_Key = atoi( cPrmBuf );
	// �X���[�v���ԁi�b�j�擾
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_SLEEP_SEC,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iSleepSec= atoi( cPrmBuf );
	// �X�V��ID
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_UP_ID,
						pEnv->cUpdateId ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �X�V�Җ�
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_UP_NM,
						pEnv->cUpdateName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���s���[�h
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_PROC_MD,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->proc_mode= atoi( cPrmBuf );

	// 1.13 ADD ���ʏ�� �ꊇCOMMIT����
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_COMMIT_SU,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iCommitSu=atoi( cPrmBuf );

	// 3.01 ADD 
	// �ً}�p�t�@�C�����擪������
	if ( ZbmlPrmGetVal( pEnv->bp, GD205_PRM_PREFIXNM,
						pEnv->cPrefixNm ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}

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
/*�@�� �� ���@�FGD205UpdateHkkknriSts()										  */
/*�@�@�\�T�v�@�F�񍐊Ǘ����G���[�X�V										  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FHkkknri *pHkkknri	�񍐊Ǘ������\����					  */
/*�@�@��Q�����Fchar *pHkkjkflg		�񍐏󋵃t���O							  */
/*�@�@��R�����Fchar *pHkkerrcode	�񍐃G���[�R�[�h						  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�F�Ȃ�														  */
/******************************************************************************/
void GD205UpdateHkkknriSts( Hkkknri *pHkkknri, char *pHkkjkflg, char *pHkkerrcode )
{
	int			iRet;

	// �񍐊Ǘ������X�V
	ZbmlInfocpy( pHkkknri->hkkjkflg, pHkkjkflg, sizeof( pHkkknri->hkkjkflg ) );
	ZbmlInfocpy( pHkkknri->hkkerrcode, pHkkerrcode, sizeof( pHkkknri->hkkerrcode ) );

	// �񍐊Ǘ������X�V
	iRet = ZdbHkkknriGD205UpdateSts( pHkkknri );
	if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
		// ���[���o�b�N
		ZdbRollback();
		// �ُ�I��	LOG
		// 1.06 �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205UpdateHkkknriSts", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"ZdbHkkknriGD205UpdateSts error [%d]", iRet );
	} else {
		// �R�~�b�g
		ZdbCommit();
	}
}

/******************************************************************************/
/*�@�� �� ���@�FmainFunction()												  */
/*�@�@�\�T�v�@�F���C�������֐�												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FGD205Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int mainFunction( GD205Env *pEnv )
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

	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	if( iRet = ZdbConnect( pEnv->cDBName,
						   pEnv->cDBUser,
						   pEnv->cDBPawd ) ) {
		// 1.06 �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"ZdbConnect error [%d]", iRet );
		return( RTN_NG );
	}

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
		iRet = ZdbHkkknriGD205SelectAll( &pHkkknriArrayOut, &iHkkknriNumOut );
		if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
			//�ُ�I��
			//���O�o��
			// 1.06 �ُ�I��	LOG
			sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction", __LINE__,
					EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
					"ZdbHkkknriGD205SelectAll error [%d]", iRet );
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
					// 1.06 �ُ�I��	LOG
					sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
							"ZdbSysknrmstSelect error [%d]", iRet );
					return( RTN_NG );
				}

				// �쐬�J�n�������擾
				time( (long *)&ulSt );

				// �쐬�����A�ۗ��������N���A
				iHkkssknsu = 0;
				iHkkhrysu = 0;
				memset( cDataFile, 0, sizeof( cDataFile ) );

				// ���ʏ�񌟍��i���M�Ώۂ̂݁j
				// �񍐋敪�����ʏ󋵃R�[�h�̒l�ɂ��킹��
				switch ( pHkkknriArrayOut[iHkkknriLoop].hkkkbn ) {
				case GD205_DB_HKKKBN_LAST:	// �ŏI
					pHkkknriArrayOut[iHkkknriLoop].hkkkbn = GD205_DB_KKAJKCD_LAST;
					break;
				case GD205_DB_HKKKBN_CYUU:	// ����
					pHkkknriArrayOut[iHkkknriLoop].hkkkbn = GD205_DB_KKAJKCD_CYUU;
					break;
				}

				// �ē]���̏ꍇ�́A�ē]���������Ăяo��
					// 3.01 �ً}�̏ꍇ�͍��ڃR�[�h�ɕ񍐏������ݒ肳��Ă���
				//if( pHkkknriArrayOut[iHkkknriLoop].hkkjkn == GD205_DB_HKKJKN_RESEND ) [
				if ( pHkkknriArrayOut[iHkkknriLoop].kmkcd[0] == GD205_DB_HKKJKN_RESEND ) {
					if ( GD205ResendFile( pEnv,
										  &stSysknrmst,
						 				  &pHkkknriArrayOut[iHkkknriLoop] ) == RTN_OK ) {
						// �񍐃t�@�C����
						// GD205ResendFile���Őݒ�
						// �񍐏󋵃t���O
						ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg,
									 GD205_DB_HKKJKFLG_CHUU,
									 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg ) );
						// ���X�V�����͊֐����Őݒ�

						// �񍐊Ǘ������X�V
						iRet = ZdbHkkknriGD205UpdateNormal( &pHkkknriArrayOut[iHkkknriLoop] );
						if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
							// ���[���o�b�N
							ZdbRollback();
							// �ُ�I��	LOG
							// 1.06 �ُ�I��	LOG
							sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction",
									 __LINE__,
									EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
									"ZdbHkkknriGD205UpdateNormal error [%d]", 
									iRet );

							return( RTN_NG );
						}

						// �R�~�b�g
						ZdbCommit();
					} else {
						// �ُ�I��	LOG
						// 1.06 �ُ�I��	LOG
						sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction",
								 __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"GD205ResendFile error " );

						// �񍐊Ǘ������X�V
						GD205UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
												GD205_DB_HKKJKFLG_ERRFILE,
												GD205_DB_HKKERRCODE_RESEND );
					}
					continue;
				}

				// �񍐏����ɂ��A�������@��ؑւ���
				// switch ( pHkkknriArrayOut[iHkkknriLoop].hkkjkn ) {
					// 3.01 �ً}���̌��������͍��ڃR�[�h�ɐݒ�
				switch ( pHkkknriArrayOut[iHkkknriLoop].kmkcd[0] ) {
				case GD205_DB_HKKJKN_CTRLNO:	// �R���g���[��No
					iRet = ZdbKekkaGD205SelectByCtrlNo( &pHkkknriArrayOut[iHkkknriLoop],
														&pKekkaArrayOut, &iKekkaNumOut );
					break;
				case GD205_DB_HKKJKN_PLTNO:		// �v���b�gNo
					iRet = ZdbKekkaGD205SelectByPltNo( &pHkkknriArrayOut[iHkkknriLoop],
													   &pKekkaArrayOut, &iKekkaNumOut );
					break;
				case GD205_DB_HKKJKN_KNSSEQ:	// ����SEQ
					iRet = ZdbKekkaGD205SelectByKnsSeq( &pHkkknriArrayOut[iHkkknriLoop],
														&pKekkaArrayOut, &iKekkaNumOut );
					break;
				case GD205_DB_HKKJKN_IRINO:		// �˗���No
					iRet = ZdbKekkaGD205SelectByIriNo( &pHkkknriArrayOut[iHkkknriLoop],
													   &pKekkaArrayOut, &iKekkaNumOut );
					break;
				case GD205_DB_HKKJKN_KNTNO:		// ����No
					iRet = ZdbKekkaGD205SelectByKntNo( &pHkkknriArrayOut[iHkkknriLoop],
													   &pKekkaArrayOut, &iKekkaNumOut );
					break;
				default:
					// 1.06 �ُ�I��	LOG
					sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"kkknri.hkkjkn �͈̔̓G���[ (HKKJKN='%c')", 
							pHkkknriArrayOut[iHkkknriLoop].hkkjkn );

					// �񍐊Ǘ������X�V
					GD205UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
										   GD205_DB_HKKJKFLG_ERRFILE,
										   GD205_DB_HKKERRCODE_HKKJKN );
					continue;
				}
				if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
					// �ُ�I��	LOG
					// 1.06 �ُ�I��	LOG
					sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
							"ZdbKekkaGD205SelectByXXXX error (%d)", iRet);

					// �񍐊Ǘ������X�V
					GD205UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
										   GD205_DB_HKKJKFLG_ERRFILE,
										   GD205_DB_HKKERRCODE_DBACS );
					continue;
				}
				if ( iRet == HRC_SQL_NOT_FOUND ) {
					// �ُ�I��	LOG
					// 1.06 �ُ�I��	LOG
					sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
							"ZdbKekkaGD205SelectByXXXX no data  error" );

					// �񍐊Ǘ������X�V
					GD205UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
										   GD205_DB_HKKJKFLG_ERRFILE,
										   GD205_DB_HKKERRCODE_NODATA );
					continue;
				}
				if ( iRet == HRC_SQL_NORMAL ) {
					// �񍐃f�[�^�t�@�C���̍쐬
				if ( GD205CreateFile( pEnv,
									&stSysknrmst,
									pKekkaArrayOut,
									iKekkaNumOut,
									&iHkkssknsu,
									&iHkkhrysu,
									cDataFile,
									&pHkkknriArrayOut[iHkkknriLoop],  // 3.01 ADD
								   	&li_stopFlg //2006.12.08 Kim Jinsuk DB�G���[���I�������� 
									) == RTN_NG ) {

                          //2006.12.08�@Kim Jinsuk DB�G���[���ُ�I��������
                          if(li_stopFlg==1)
                          {
                                printf("#############################3");
                                sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbKekkaGD205Update"
								, __LINE__,
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
							GD205UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
												   GD205_DB_HKKJKFLG_ERRFILE,
												   GD205_DB_HKKERRCODE_NODATA );
							continue;
						}

						// �ُ�I��	LOG
					sFncPutLog( TRCKIND_WARNING, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"GD205CreateFile error" );


						// �񍐊Ǘ������X�V
						GD205UpdateHkkknriSts( &pHkkknriArrayOut[iHkkknriLoop],
											   GD205_DB_HKKJKFLG_ERRFILE,
											   GD205_DB_HKKERRCODE_CREATE );
						continue;
					}

				}

				// ���ʏ������
				if ( pKekkaArrayOut != NULL ) {
					ZbmlFree( pKekkaArrayOut );
				}

				// �쐬�����������擾
				time( (long *)&ulEd );

				// �񍐃t�@�C����
				// GD205CreateHULFTFile���Őݒ� -> 3.01 GD205CreateFile ���Őݒ�
				// �쐬�J�n����
				GD205ConvTimestamp( ulSt, cTimestamp );
				ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkstdh,
							 cTimestamp,
							 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkstdh ) );
				// �쐬��������
				GD205ConvTimestamp( ulEd, cTimestamp );
				ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkeddh,
							 cTimestamp,
							 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkeddh ) );
				// �쐬����
				pHkkknriArrayOut[iHkkknriLoop].hkkssknsu = iHkkssknsu;
				// �񍐕ۗ�����
				pHkkknriArrayOut[iHkkknriLoop].hkkhrysu = iHkkhrysu;
				// ���M�t�@�C���h�c
				// GD205CreateHULFTFile���Őݒ�
				// �񍐏󋵃t���O
				ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg,
							 GD205_DB_HKKJKFLG_CHUU,
							 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg ) );
				// ���X�V�����͊֐����Őݒ�

				// �񍐊Ǘ������X�V
				iRet = ZdbHkkknriGD205UpdateNormal( &pHkkknriArrayOut[iHkkknriLoop] );
				if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
					// ���[���o�b�N
					ZdbRollback();
					// �ُ�I��	LOG
					// 1.06 �ُ�I��	LOG
					sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction",
							 __LINE__,
							EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
							"ZdbHkkknriGD205UpdateNormal error (%d)", iRet);

					return( RTN_NG );
				}

				// �R�~�b�g
				ZdbCommit();
			}

			// �񍐊Ǘ��������
			ZbmlFree( pHkkknriArrayOut );
		}

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
/*�@�@��P�����FGD205Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�F�Ȃ�														  */
/******************************************************************************/
void endFunction( GD205Env *pEnv )
{
	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "endFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");
	// 1.09 ADD
	/***	
     ***    �f�[�^�x�[�X�N���[�Y
     ***/
    ZdbDisConnect() ;

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
/*�@�� �� ���@�FGD205MakeData()												  */
/*�@�@�\�T�v�@�F�񍐃f�[�^�쐬												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FKekka *pKekka		�������ʃf�[�^							  */
/*�@�@��Q�����Fchar *pLBCD			���{�R�[�h								  */
/*�@�o�@�@�́@�F															  */
/*�@�@��R�����FGD205Rec *pGD205Rec	�񍐃f�[�^								  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int GD205MakeData(Kekka *pKekka, char *pLBCD, GD205Rec *pGD205Rec)
{
	char	cTempBuff[128];
	char	cKkassflg[1+1];		// 1.11 ADD ���ʏC���׸�MAX�擾
	char	cSbtkbn[1+1];		// 3.01 ADD ���ʋ敪
	int		edt_ret;			// 3.01 


	// �������ʃf�[�^�܂��͕񍐃f�[�^�ւ̃|�C���^��NULL�̏ꍇ�ُ�I��
	if ( pKekka == NULL || pGD205Rec == NULL ) {
		return( RTN_NG );
	}

	// 1.06 ADD �{�ݕʊ��Z�Ή�
	GD205_sstknz( pKekka );


	// �񍐃f�[�^���X�y�[�X�ŃN���A
	memset( pGD205Rec, GD205_DATA_SPACE, sizeof(GD205Rec) );

	// �������ʃf�[�^����񍐃f�[�^���쐬
	// �a�l�k��t�N����
	// [YYYYMMDD]�ɕϊ����Đݒ�
	ZbmlChgAPDate( pGD205Rec->cUTKYMD, pKekka->utkymd );

	/* �˗���No�D*/
	/* �����`����PNC�`���ɕϊ� */
	/* (�ϊ��O)[1][2][3][4][5][6][7][8][9][10][11] */
	/* (�ϊ���)[4][5][6] 0  0 [7][8][9][9][10][11] */
	if ( GD205ConvNumber( pGD205Rec->cKNTNO, pKekka->irino ) == RTN_NG ) {
		return( RTN_NG );
	}

	/* �e���ڃR�[�h */
	/* �����ɂ��A���ڃR�[�h��7�������ꂽ�̂ł��̂܂܃R�s�[���� */
	if ( GD205CopyFromLeft( pGD205Rec->cOYAKMKCD,
								pKekka->oyakmkcd,
								sizeof( pGD205Rec->cOYAKMKCD ),
								FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}

	/* ���ڃR�[�h */
	/* �����ɂ��A���ڃR�[�h��7�������ꂽ�̂ł��̂܂܃R�s�[���� */
	if ( GD205CopyFromLeft( pGD205Rec->cKMKCD,
								pKekka->kmkcd,
								sizeof( pGD205Rec->cKMKCD ),
								FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}

	/* WS�R�[�h(�T���v�����O�R�[�h) */
		// 3.01 ADD �ً}�Ή����ڃ}�X�^����ҏW����
/*** AS400�� �����ɔ����A�ً}�Ή����ڃ}�X�^����ASWSCD���擾����̂��~�� -> ***/
/*** �T�e���C�g����WSCD(=SMPCD)�����̂܂ܐݒ肵�đ���                   -> ***/
/*	if( GD205_GetWscd( pGD205Rec->cWSCD, pKekka->kmkcd, pKekka->knskisymd ) != RTN_OK ){*/
/*		if ( GD205CopyFromLeft( pGD205Rec->cWSCD,*/
/*								 pKekka->smpcd,*/
/*								 sizeof( pGD205Rec->cWSCD ),*/
/*								 FALSE ) == RTN_NG ) {*/
/*			return( RTN_NG );*/
/*		}*/
/*	}*/
	if ( GD205CopyFromLeft( pGD205Rec->cWSCD, pKekka->smpcd, 
						   sizeof( pGD205Rec->cWSCD ), FALSE ) == RTN_NG ) {
		return( RTN_NG );									/* KEKKA��SMPCD�����̂܂ܕ񍐂�WSCD�ɐݒ� */
	}
/*** AS400�� �����ɔ����C�� <-                                              ***/

	
	
	// �v�r�r�d�p�i�����r�d�p�j
    // ���l�𕶎���ɕϊ���A�E����4����ݒ�B�i�[���T�v���X�Ȃ��j
    sprintf( cTempBuff, "%06d", pKekka->knsseq );
    if ( GD205CopyFromRight( pGD205Rec->cWSSEQ,
                             cTempBuff,
                             sizeof( pGD205Rec->cWSSEQ ),
                             FALSE ) == RTN_NG ) {
        return( RTN_NG );
    }

    // ��������
/* 3.01 2007.06.12 PTN�Ή��@STA ========================================================
DEL    // �������ʂPor�������ʂQ�i�������ʂP�D��j
DEL		// GD105 knskka1 RIGHT
DEL	memset( cTempBuff, '\0',	sizeof( cTempBuff ));
DEL    if ( pKekka->knskka1[0] != '\0' 
DEL	  && strspn( pKekka->knskka1, " " ) != ( sizeof( pKekka->knskka1 ) - 1 ) ){
DEL        // �������ʂP�F�E����6����ݒ�i�[���T�v���X����A�����_�폜�j
DEL        if ( GD205CopyFromRight( cTempBuff,
DEL                                pKekka->knskka1,
DEL                                sizeof( pGD205Rec->cKNSKKA ),
DEL                                FALSE ) == RTN_NG ) {
DEL            return( RTN_NG );
DEL        }
DEL			// �����_�폜�A�O�[���t��
DEL        if ( GD205CopyReplace( pGD205Rec->cKNSKKA,
DEL                                cTempBuff,
DEL                                sizeof( pGD205Rec->cKNSKKA )) == RTN_NG ) {
DEL            return( RTN_NG );
DEL        }
DEL    } else {
DEL        // �������ʂQ
DEL        // �������ʋ敪='0'��'*'+��2���ڂ���6���ڂ܂�
DEL        // �ȊO��������6����ݒ�i2�o�C�g�����ɒ��ӂ���j
DEL        // ?? if ( ED203CopyFromRight( pED203Rec->cKNSKKA,
DEL        if ( GD205CopyFromLeft( pGD205Rec->cKNSKKA,
DEL                                pKekka->knskka2,
DEL                                sizeof( pGD205Rec->cKNSKKA ),
DEL                                TRUE ) == RTN_NG ) {
DEL            return( RTN_NG );
DEL        }
DEL        if ( pKekka->knskka2kbn[0] == GD205_DATA_CHAR0 ) {
DEL            // �������ʋ敪='0'��'*'+��2���ڂ���6���ڂ܂�
DEL            pGD205Rec->cKNSKKA[0] = GD205_DATA_ASTERISK;
DEL        }
DEL    }
=================================================================================== */
    // ��������
	// 3.01 AS400�p�ɃI���R�[�f�B���O
	edt_ret=RTN_OK;
	memset( cTempBuff, '\0',	sizeof( cTempBuff ));

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD205MakeData", __LINE__,
		"EDIT IN### irino[%s]kmkcd[%s]KNSKKA[%6.6s]\nkka1[%s]kka2[%s]2kbn[%s]kkahskcd[%s]\n"
		,pKekka->irino,pKekka->kmkcd, pGD205Rec->cKNSKKA
		, pKekka->knskka1,pKekka->knskka2,pKekka->knskka2kbn,pKekka->kkahskcd );

	// ���ʂP���󔒈ȊO
    if ( strspn( pKekka->knskka1, " " ) != ( sizeof( pKekka->knskka1 ) - 1 ) ){
		// ���ʕ⑫����
    	if ( pKekka->kkahskcd[0] == ' '  ){
				// �������ʂP�̏����_�A�󔒈ȊO��length <= 6
			if(((sizeof(pKekka->knskka1)-1) - strspn(pKekka->knskka1," ")  ) <= 6 ){
					// �����_�폜�A�O�[���t��
				if ( GD205CopyReplace( cTempBuff,
										pKekka->knskka1,
										sizeof(pKekka->knskka1)) == RTN_NG ) {
					edt_ret=RTN_NG;
				}
				// �������ʂP�F�E����6����ݒ�
				if ( GD205CopyFromRight( pGD205Rec->cKNSKKA,
										cTempBuff,
										sizeof( pGD205Rec->cKNSKKA ),
										FALSE ) == RTN_NG ) {
					edt_ret=RTN_NG;
				}
			} else {
				// ���ʕҏW�s��
				edt_ret=RTN_NG;
			}
		}
		// ���ʕ⑫���󔒈ȊO
		else {
				// �������ʂP�̋󔒈ȊO��length <= 4
			if(((sizeof(pKekka->knskka1)-1) - strspn(pKekka->knskka1," "))<= 4 ){
					// LT�ҏW + �O�X�y�[�X����菜�������ʂP��ҏW
				if( ( memcmp( pKekka->kkahskcd, "001" ,3 ) == 0 )
				 || ( memcmp( pKekka->kkahskcd, "002" ,3 ) == 0 )){
					sprintf( cTempBuff, "LT%s    " , strrchr( pKekka->knskka1, ' ')+1 );
				} else
					// GT�ҏW + �O�X�y�[�X����菜�������ʂP��ҏW
				if( ( memcmp( pKekka->kkahskcd, "003" ,3 ) == 0 )
				 || ( memcmp( pKekka->kkahskcd, "004" ,3 ) == 0 )){
					sprintf( cTempBuff, "GT%s    " , strrchr( pKekka->knskka1, ' ')+1 );
				} else {
					// ���ʕҏW�s��
					edt_ret=RTN_NG;
				}
				// ���X�y�[�X�l�����ݒ�
				if( edt_ret != RTN_NG ){
					memcpy( pGD205Rec->cKNSKKA, cTempBuff, sizeof( pGD205Rec->cKNSKKA ));
				}
			} else {
				// ���ʕҏW�s��
				edt_ret=RTN_NG;
			}
		}
	} 
	// ���ʂP����
	else {
			// ���ʂQ�敪='0'
        if ( pKekka->knskka2kbn[0] == GD205_DATA_CHAR0 ) {
				// ���ʂQ�̐擪�Pbyte��='0'
        	if ( pKekka->knskka2[0] == GD205_DATA_CHAR0 ) {
            		// �擪�Pbyte�ڂ�'*'�ɒu���������ʂQ��ҏW
				if ( GD205CopyFromLeft( pGD205Rec->cKNSKKA,
										pKekka->knskka2,
										sizeof( pGD205Rec->cKNSKKA ),
										TRUE ) == RTN_NG ) {
					// ���ʕҏW�s��
					edt_ret=RTN_NG;
				}
				pGD205Rec->cKNSKKA[0] = GD205_DATA_ASTERISK;
			} else {
				// ���ʂQ�̐擪�Pbyte��<>'0'
				if( memcmp( pKekka->knskka2, "1005" ,4 ) == 0 ) {
					memcpy( pGD205Rec->cKNSKKA, "-     ", 6 );
				} else if( memcmp( pKekka->knskka2, "1006" ,4 ) == 0 ) {
					memcpy( pGD205Rec->cKNSKKA, "+-    ", 6 );
				} else if( memcmp( pKekka->knskka2, "1008" ,4 ) == 0 ) {
					memcpy( pGD205Rec->cKNSKKA, "1+    ", 6 );
				} else if( memcmp( pKekka->knskka2, "1009" ,4 ) == 0 ) {
					memcpy( pGD205Rec->cKNSKKA, "2+    ", 6 );
				} else {
					// ���ʕҏW�s��
					edt_ret=RTN_NG;
				}
			}
        } 
		// ���ʂQ�敪<>'0'
		else {
			// ���ʕҏW�s��
			edt_ret=RTN_NG;
		}
	}
	// ���ʕҏW�s�� -> *340
	if( edt_ret==RTN_NG ){
		memcpy( pGD205Rec->cKNSKKA, "*340  ", 6 );
	}

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD205MakeData", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		"-->cKNSKKA[%6.6s]" , pGD205Rec->cKNSKKA );

	// ���ʃR�����g
    // �E����3����ݒ�
    // 3.01 ��2byte�ڂ���3����ݒ�
    //if ( GD205CopyFromRight( pGD205Rec->cKKACMT,
    if ( GD205CopyFromLeft( pGD205Rec->cKKACMT,
                             //pKekka->kkacmt1,
                             &pKekka->kkacmt1[1],
                             sizeof( pGD205Rec->cKKACMT ),
                             FALSE ) == RTN_NG ) {
        return( RTN_NG );
    }

    // �ُ�l�}�[�N
    // �ُ�l�敪�i�j�A���A�s���j��'4','5','6'�ȊO�ł����'*'
		// 3.01 ADD ����ɗp����l�͐��ʂɂ��ς���
	if ( GD205GetSbtkbn( pKekka, cSbtkbn ) != RTN_OK ){
		cSbtkbn[0] = '9';
	}
/* 3.01 DELL
DEL if ( ( pKekka->ijkbnm != '4' && pKekka->ijkbnm != '5' && pKekka->ijkbnm != '6' ) ||
DEL      ( pKekka->ijkbnf != '4' && pKekka->ijkbnf != '5' && pKekka->ijkbnf != '6' ) ||
DEL      ( pKekka->ijkbnn != '4' && pKekka->ijkbnn != '5' && pKekka->ijkbnn != '6' ) ) [
*/
    if((cSbtkbn[0] =='0' && pKekka->ijkbnm != '4' && pKekka->ijkbnm != '5' && pKekka->ijkbnm != '6' ) ||
       ( cSbtkbn[0] =='1' && pKekka->ijkbnf != '4' && pKekka->ijkbnf != '5' && pKekka->ijkbnf != '6' ) ||
       ( cSbtkbn[0] =='9' && pKekka->ijkbnn != '4' && pKekka->ijkbnn != '5' && pKekka->ijkbnn != '6' ) ) {
        pGD205Rec->cIJKBN = GD205_DATA_ASTERISK;
	}

    // FILLER2
    // �󔒂�ݒ�Ȃ̂ŉ������Ȃ�
    // LF
    pGD205Rec->cLF = GD205_FILE_LINEFEED;


	// �㏈��
// 1.11 ADD ���ʏC���t���O�͓���KEY����MAX(���ʏC��FLG�j��ҏW
	 if ( pKekka->kkassflg != '\0' ){
		memset( cKkassflg,	'\0',	sizeof( cKkassflg ));
		if ( GD205GetKkassflgMax( pKekka, cKkassflg ) == RTN_OK ) {
			// �X�V�p�Ɏ擾����MAX���\���̂ɕҏW����
			pKekka->kkassflg	= cKkassflg[0];
		}
	}
// 1.11 END ====================================================

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FGD205DataFileFilter()										  */
/*�@�@�\�T�v�@�F�f�B���N�g�������p�̃t�@�C���t�B���^(�R�[���o�b�N)			  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����Fstruct dirent *pDirEnt	�f�B���N�g���G���g��				  */
/*�@�o�@�@�́@�F�������ʃt�@�C��											  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		0	: �ΏۊO�t�@�C��									  */
/*�@�@�@�@�@�@		1	: �Ώۃt�@�C��										  */
/******************************************************************************/
int GD205DataFileFilter(struct dirent *pDirEnt)
{
	BmlDate		today;
	char		cToday[GD205_LEN_DATESHORT + 1];

	// �����񒷃`�F�b�N
	if ( strlen ( pDirEnt->d_name )  < GD205_LEN_FILEID ) {
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
/*�@�� �� ���@�FGD205WriteFile()											  */
/*�@�@�\�T�v�@�F�񍐃f�[�^�t�@�C��������									  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FFILE *fp			�t�@�C���|�C���^						  */
/*�@�@��Q�����FGD205Rec *pGD205Rec	�񍐃f�[�^								  */
/*�@�@��R�����Fint iRecCnt			���R�[�h��								  */
/*�@�o�@�@�́@�F�������ʃt�@�C��											  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int GD205WriteFile(FILE *fp, GD205Rec *pGD205Rec, int iRecCnt)
{
	int				iLoop;
	int				iFileCnt;
	GD205Rec		stGD205RecTemp;
	char			cTemp[GD205_FILE_FILLER_SIZE];

	// �t�@�C���o��
	// ���R�[�h������
	iFileCnt = fwrite( pGD205Rec, sizeof( GD205Rec ) * iRecCnt, 1, fp);
	if ( iFileCnt != 1 ) {
		// �ُ�I��	LOG
		// 1.06 �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205WriteFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"write status:[%d] ", iFileCnt );

		gintErrorCode = GD205_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}
	for ( iLoop = iRecCnt; iLoop < GD205_REC_LOOP_MAX; iLoop++ ) {
		memset( &stGD205RecTemp, GD205_DATA_SPACE, sizeof( GD205Rec ) );
		iFileCnt = fwrite( &stGD205RecTemp, sizeof( GD205Rec ), 1, fp);
		if ( iFileCnt != 1 ) {
			// �ُ�I��	LOG
			// 1.06 �ُ�I��	LOG
			sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205WriteFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"write status:[%d]", iFileCnt );

			gintErrorCode = GD205_STSCODE_ERR_FR_FILE ;
			return( RTN_NG ) ;
		}
	}

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FGD205ResendFile()											  */
/*�@�@�\�T�v�@�F�ē]���p�t�@�C���ړ�										  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FGD205Env *pEnv		�v���O�������\����					  */
/*�@�@��Q�����FSysknrmst *pSysknrmst �V�X�e���Ǘ��}�X�^���				  */
/*�@�@��R�����FHkkknri *pHkkknri	�񍐊Ǘ������						  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int GD205ResendFile(GD205Env *pEnv, Sysknrmst *pSysknrmst, Hkkknri *pHkkknri)
{
	int				iRet;
	struct dirent	**pDirEnt;
	int				iFileCnt;
	int	 			iSeqNo;
	char			cSeqBuff[10];
	BmlDate			today;
	char			cKjnsriymd[GD205_LEN_DATESHORT + 1];
	char			cFileDate[GD205_LEN_DATESHORT + 1];
	char			cFileSrc[PATH_MAX + 1];
	char			cSendFile[PATH_MAX + 1];
	char			cSendFileTemp[PATH_MAX + 1];
	FILE *			fpSrc;
	FILE *			fpDest;
	int				iLoop;
	char			cTemp[GD205_SIZE_BUFF + 1];
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

/* 3.01 DELL STA PNC���M�t�@�C�������̂܂܎g�p ============================
DEL	// ���t�@�C���̏������t���擾
DEL	memset( cFileDate, 0, sizeof( cFileDate ) );
DEL	memcpy( cFileDate, pHkkknri->ssnmtfilid, GD205_LEN_DATESHORT );
DEL
DEL	// 1.07 INTEC ADD STA
DEL	// �t�@�C�����̌��󔒂�trim
DEL	sprintf( cWfilnm, "%.*s",
DEL			strcspn( pHkkknri->stsflnm, " " ) ,
DEL			pHkkknri->stsflnm );
DEL	strcpy( pHkkknri->stsflnm, cWfilnm );
DEL	// 1.07 INTEC ADD END
DEL
DEL	// ���M�p�t�@�C��������
DEL   memset(sNewFlName, 0, sizeof(sNewFlName));
DEL   sprintf(sNewFlName, "%-3.3s_%04d_%-18.18s%04d", pHkkknri->stsflnm, pHkkknri->hkksjno,
DEL		&pHkkknri->stsflnm[9], pSysknrmst->ssntubn);
DEL
DEL	memset(cSendFile, 0, sizeof(cSendFile));
DEL	memset(cSendFileTemp, 0, sizeof(cSendFileTemp));
DEL	sprintf(cSendFile, "%s/%s/%s/%s%s",
DEL			pEnv->cDirToday,
DEL		 	pEnv->cDirSendFile,
DEL			pEnv->cDirSendREQ,
DEL			sNewFlName, GD205_FILEEXT_DATA);	
DEL	sprintf(cSendFileTemp, "%s/%s/%s/%s%s",
DEL			pEnv->cDirToday,
DEL		 	pEnv->cDirSendFile,
DEL			pEnv->cDirSendREQ,
DEL			sNewFlName, GD205_FILEEXT_TEMP);	
DEL
DEL	// ���������t�@�C����OK�f�B���N�g���̃t���p�X�𐶐�
DEL	//if ( memcmp( cKjnsriymd, pHkkknri->stsflnm, GD205_LEN_DATESHORT ) == 0 ) [
DEL	if ( memcmp( cKjnsriymd, pHkkknri->ssnmtfilid, GD205_LEN_DATESHORT ) == 0 ) {
DEL		sprintf( cFileSrc, "%s/%s/%s/%s",
DEL			 	pEnv->cDirToday,
DEL			 	pEnv->cDirSendFile,
DEL			 	pEnv->cDirSendOK,
DEL				pHkkknri->stsflnm );
DEL	} else {
DEL		sprintf( cFileSrc, "%s/%s/%s/%s/%s",
DEL			 	pEnv->cDirOldday,
DEL			 	cFileDate,
DEL			 	pEnv->cDirSendFile,
DEL			 	pEnv->cDirSendOK,
DEL				pHkkknri->stsflnm );
DEL	}
========================================================================= */

// 3.01 ADD STA
	sprintf( cWfilnm, "%.*s",
			strcspn( pHkkknri->stsflnm, " " ) ,
			pHkkknri->stsflnm );

	// ���t�@�C��
    sprintf( cFileSrc, "%s/%s/%s/%s",
			 pEnv->cDirToday,
			 pEnv->cDirSendFile,
			 pEnv->cDirSendOK,
			 cWfilnm );

	// ���M�p�t�@�C��������
		// ���b�gNo�̎���byte���P�J�E���g�A�b�v����
		// 20070622 �ē]�����̑��M�ԍ����t�@�C�����ɔ��f������
	memset(sNewFlName, 0, sizeof(sNewFlName));
	//sprintf( sNewFlName, "%-30.30s%1.1d" , cWfilnm, ( cWfilnm[30] - '0' ) + 1 );
	sprintf( sNewFlName, "%-4.4s%04d%-22.22s%1.1d" 
			, cWfilnm
			, pHkkknri->hkksjno
			, &cWfilnm[8]
			, ( cWfilnm[30] - '0' ) + 1 );

	memset(cSendFile, 0, sizeof(cSendFile));
	memset(cSendFileTemp, 0, sizeof(cSendFileTemp));
	sprintf(cSendFile, "%s/%s/%s/%s%s",
			pEnv->cDirToday,
		 	pEnv->cDirSendFile,
			pEnv->cDirSendREQ,
			sNewFlName, GD205_FILEEXT_DATA );	
	sprintf(cSendFileTemp, "%s/%s/%s/%31.31s%s",
			pEnv->cDirToday,
		 	pEnv->cDirSendFile,
			pEnv->cDirSendREQ,
			sNewFlName, GD205_FILEEXT_TEMP );	

// 3.01 ADD  END

	// ���t�@�C���I�[�v��
	fpSrc = fopen ( cFileSrc, "r" );
	if ( fpSrc == NULL ) {
/* 3.01 DELL STA ======================================================
DEL		// �t�@�C�����I�[�v���ł��Ȃ��ꍇ��ERR�f�B���N�g���ōĒ���
DEL		if ( strncmp( cKjnsriymd, pHkkknri->ssnmtfilid, GD205_LEN_DATESHORT ) == 0 ) {
DEL			sprintf( cFileSrc, "%s/%s/%s/%s",
DEL				 	pEnv->cDirToday,
DEL				 	pEnv->cDirSendFile,
DEL				 	pEnv->cDirSendERR,
DEL					pHkkknri->stsflnm );
DEL		} else {
DEL			sprintf( cFileSrc, "%s/%s/%s/%s/%s",
DEL				 	pEnv->cDirOldday,
DEL			 		cFileDate,
DEL				 	pEnv->cDirSendFile,
DEL				 	pEnv->cDirSendERR,
DEL					pHkkknri->stsflnm );
DEL		}
DEL		// ���t�@�C���I�[�v��
DEL		fpSrc = fopen ( cFileSrc, "r" );
======================================================================= */

		if ( fpSrc == NULL ) {
			// �ُ�I��	LOG
			gintErrorCode = GD205_STSCODE_ERR_FR_FILE ;
			return( RTN_NG ) ;
		}
	}

	// ���M�p�t�@�C���I�[�v��
	fpDest = fopen ( cSendFileTemp, "w" );
	if ( fpDest == NULL ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	// �ǂݍ���
	iHead = 0;
	while ( iRet = fgets( cTemp, sizeof ( cTemp ), fpSrc ) != NULL ) {
		if ( fputs( cTemp, fpDest ) < 0 ) {
			//�G���[���O�o��
//1.06 DELL printf("fputs error \n");
			// 1.06 �ُ�I��	LOG
			sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205ResendFile", __LINE__,
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
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205ResendFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"ResendFile rename status:[%d] ", iRet);

		gintErrorCode = GD205_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	// �ԋp�p�Ƀt�@�C�����Ƒ��M�t�@�C���h�c��ݒ�
	memset( pHkkknri->hkkflnm, 0, sizeof( pHkkknri->hkkflnm ) );
	sprintf( pHkkknri->hkkflnm, "%s%s",
			sNewFlName, GD205_FILEEXT_DATA);	

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FGD205CreateFile()											  */
/*�@�@�\�T�v�@�F�񍐃f�[�^�t�@�C���쐬										  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FGD205Env *pEnv		�v���O�������\����					  */
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
int GD205CreateFile(GD205Env *pEnv,
					Sysknrmst *pSysknrmst,
					Kekka *pKekkaArray,
					int iKekkaNum,
					int *piHkkssknsu,
					int *piHkkhrysu,
					char *pFileName,
					Hkkknri *pHkkknriArrayOut,	// 3.01 ADD
					int *sqlErrorFlag)			//2006.12.08 Kim Jinsuk DB�G���[���ُ�I��������
{
	int				iRet;
	struct dirent	**pDirEnt;
	int				iFileCnt;
	int	 			iSeqNo;
	char			cSeqBuff[10];
	BmlDate			today;
	char			cToday[GD205_LEN_DATESHORT + 1];
	char			cFileNameTemp[PATH_MAX + 1];
	char			cFileName[PATH_MAX + 1];
	FILE *			fp;
	int				iLoop;
	GD205Rec		stGD205RecTemp;
	int				iKekkaLoop;
	GD205Rec		stGD205Rec[GD205_REC_LOOP_MAX];
	int				iFileLoopIdx;
	int				iCmmtCnt=0;				// 1.13 ADD

	char			cKjnsriymd[GD205_LEN_DATESHORT + 1];
	char			cSendFileTemp[PATH_MAX + 1];
	char			cSendFile[PATH_MAX + 1];
	FILE *			fpSrc;
	FILE *			fpDest;
	int				iRecCnt;
	char			cTemp[GD205_SIZE_BUFF + 1];
    char            sNewFlName[PATH_MAX + 1];
    char            sKaisibi[10];
    int             i;

    //
	// �����`�F�b�N
	if ( pEnv == NULL || pSysknrmst == NULL || pKekkaArray == NULL ||
		 piHkkssknsu == NULL || piHkkhrysu == NULL || pFileName == NULL ) {
		// �ُ�I��	LOG
//1.06 DELL printf("GD205CreateFile parameter is NULL\n");
		// 1.06 �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205CreateFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"GD205CreateFile parameter is NULL");

		gintErrorCode = GD205_STSCODE_ERR_FR_FILE;
		return( RTN_NG );
	}

// 3.01 ADD STA
	// �������t�擾
	ZbmlChgAPDate( cKjnsriymd, pSysknrmst->kjnsriymd );
	// 1.06 �ُ�I��	LOG
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD205CreateFile", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"������N����:[%s]", cKjnsriymd );

	// �t�@�C��������
    memset(sNewFlName, 0, sizeof(sNewFlName));
		// 3.01 UPD
    //switch(pHkkknriArrayOut->hkkjkn) {
    switch(pHkkknriArrayOut->kmkcd[0]) {
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
    // 3.01 sprintf( cSendFile, "%s/%s/%s/%s_%04d_%s_%s_%s%04d%s",
    sprintf( cSendFile, "%s/%s/%s/%s_%04d_%s_%s_%s%03d0%s",
			 pEnv->cDirToday,
			 pEnv->cDirSendFile,
			 pEnv->cDirSendREQ,
             // 3.01 pSysknrmst->sateid, 
             pEnv->cPrefixNm, 
			 pHkkknriArrayOut->hkksjno,
             pHkkknriArrayOut->seccd, sNewFlName, cKjnsriymd, 
			 // 3.01 pSysknrmst->ssntubn, 
			 pHkkknriArrayOut->kkirilotno, 
			 GD205_FILEEXT_DATA );
			 //cKjnsriymd,
    // 3.01 sprintf( cSendFileTemp, "%s/%s/%s/%s_%04d_%s_%s_%s%04d%s",
    sprintf( cSendFileTemp, "%s/%s/%s/%s_%04d_%s_%s_%s%03d0%s",
			 pEnv->cDirToday,
			 pEnv->cDirSendFile,
			 pEnv->cDirSendREQ,
             // 3.01 pSysknrmst->sateid, 
             pEnv->cPrefixNm, 
			 pHkkknriArrayOut->hkksjno,
             pHkkknriArrayOut->seccd, sNewFlName, cKjnsriymd, 
			 // 3.01 pSysknrmst->ssntubn,
			 pHkkknriArrayOut->kkirilotno, 
			 GD205_FILEEXT_TEMP );
	// �񍐃f�[�^�t�@�C���I�[�v��
	fp = fopen ( cSendFileTemp, "w" );
	if ( fp == NULL ) {
		// 1.06 �ُ�I��    LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205CreateFile", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"file open error[%s]", cSendFileTemp );
		gintErrorCode = GD205_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

// 3.01 ADD END

	// ���ʏ����P��������
	for ( iKekkaLoop = 0, iFileLoopIdx  = 0;
		  iKekkaLoop < iKekkaNum;
		  iKekkaLoop++ ) {

		// 3.01 ADD STA �ً}�˗����b�gNo�̎w��L��̏ꍇ�͊Y�����ʈȊO��SKIP
		if( pHkkknriArrayOut->kkirilotno > 0 ){
			if( pHkkknriArrayOut->kkirilotno != pKekkaArray[iKekkaLoop].kkirilotno ){
				continue;
			}
		}
		// 3.01 ADD END

		// �ۗ����ǂ����`�F�b�N
		if ( pKekkaArray[iKekkaLoop].knsflg == GD205_DB_KNSFLG_HORYU ) {
			++*piHkkhrysu;
			continue;
		}
		// Add 2007.05.09 waj
		// knskka1,knskka2���ɃX�y�[�X�̏ꍇ�A�񍐃��R�[�h���쐬�����ۗ������Ƃ���
		if ((strncmp(pKekkaArray[iKekkaLoop].knskka1, "            ", 12) == 0) &&
		    (strncmp(pKekkaArray[iKekkaLoop].knskka2, "                        ", 24) == 0)) {

            sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205CreateFile", __LINE__,
                        EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
                        "knskka1,knskka2���ɃX�y�[�X�̂��ߕۗ��Ƃ��� [%s %s %d]",
						pKekkaArray[iKekkaLoop].sriymd	,pKekkaArray[iKekkaLoop].kmkcd
						,pKekkaArray[iKekkaLoop].knsseq);

			// �����t���O�ɕۗ���ݒ�
			pKekkaArray[iKekkaLoop].knsflg = GD205_DB_KNSFLG_HORYU;

			// ���ʏ��̌����t���O��ۗ��ɂ��邽�ߍX�V
			iRet = ZdbKekkaGD205Update( &pKekkaArray[iKekkaLoop] );

	        if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
				// DB�G���[�̏ꍇ�́A�����𔲂���
				sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205CreateFile", __LINE__,
                            EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
                            "ZdbKekkaGD205Update error(%d)", iRet);

				// ���[���o�b�N
				ZdbRollback();

            	if((iRet < 0) && (iRet !=-803) && (iRet != -911))
	            {
	                *sqlErrorFlag = 1;
	                printf("##### DB�G���[�@�����@#####\n");
	                printf("iRet %d", iRet);
	                sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbKekkaGD205Update", __LINE__,
	                            EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
	                            "DB �G���[�@�����@error value 0 %d", iRet);

                	return( RTN_NG );
            	}
				// DB�G���[�̏ꍇ�́A�S�Ė���
				*piHkkssknsu=0;
            	break;
        	}

			// �ۗ��J�E���^�A�b�v
			++*piHkkhrysu;

			continue;
		}

		// �J�Ԃ������ɒB������t�@�C���o��
		if ( iFileLoopIdx >= GD205_REC_LOOP_MAX ) {
			// �t�@�C���o��
			if ( GD205WriteFile( fp, &stGD205Rec[0], GD205_REC_LOOP_MAX ) == RTN_NG ) {
				// �ُ�I��	LOG
//1.06 DELL printf("GD205WriteFile error\n");
				// 1.06 �ُ�I��	LOG
				sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205CreateFile",__LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"GD205WriteFile error" );

				return( RTN_NG );
			}

			iFileLoopIdx = 0;
		}
		// ���ʂ��t�@�C���o�͌`���ɓW�J
		if ( GD205MakeData( &pKekkaArray[iKekkaLoop],
							pSysknrmst->lbcd,
							&stGD205Rec[iFileLoopIdx] ) == RTN_NG ) {
			// �ُ�I��	LOG
//1.06 DELL printf("GD205MakeData error\n");
			// 1.06 �ُ�I��	LOG
			sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205CreateFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"GD205MakeData error" );

			return( RTN_NG );
		}

		// ���ʏC���t���O���J�E���g�A�b�v�i�ő�'9'�j
		if ( pKekkaArray[iKekkaLoop].kkassflg == GD205_DATA_SPACE ) {
			pKekkaArray[iKekkaLoop].kkassflg = '0';
		} else if ( pKekkaArray[iKekkaLoop].kkassflg != GD205_DB_KKASSFLG_MAX ) {
			++pKekkaArray[iKekkaLoop].kkassflg;
		}
		// �񍐓����͊֐����Őݒ�

		// �����t���O���񍐍�
		pKekkaArray[iKekkaLoop].knsflg = GD205_DB_KNSFLG_DONE;

		// ���X�V�����͊֐����Őݒ�
        //2006.12.08 Kim Jinsuk DB�G���[���ُ�I��������
        int nRetValue;

		// �������ʏ����X�V
		iRet = ZdbKekkaGD205Update( &pKekkaArray[iKekkaLoop] );
		if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
//1.06 DELL printf("ZdbKekkaGD205Update error(%d)\n", iRet);
			// 1.06 �ُ�I��	LOG
			sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205CreateFile", __LINE__,
						EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
						"ZdbKekkaGD205Update error(%d)", iRet);

            //2006.12.08 Kim Jinsuk DB�G���[���ُ�I��������
            nRetValue = iRet;

			// ���[���o�b�N
			ZdbRollback();

            //2006.12.08�@Kim Jinsuk DB�G���[���ُ�I��������
            if((nRetValue < 0) && (nRetValue !=-803) && (nRetValue != -911))
            {
                *sqlErrorFlag = 1;
                printf("##### DB�G���[�@�����@#####\n");
                printf("iRet %d", iRet);
                sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbKekkaGD205Update", __LINE__,
                        EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
                        "DB �G���[�@�����@error value 0 %d", iRet);

                return( RTN_NG );
            }
            //2006.12.08�@Kim Jinsuk DB�G���[���ُ�I��������

			// 1.13 ADD STA �ꊇCOMMIT�ɔ����G���[���͏����𔲂���			
				// �G���[�t�@�C���Ƃ��邽�ߌ�����0�ɂ���
			*piHkkssknsu=0;	
			break;
			// 1.13 ADD END �ꊇCOMMIT�ɔ����G���[���͏����𔲂���			

		}
// 2006-04-20 H.Suyama Add Start
		if ( pKekkaArray[iKekkaLoop].kkajkcd == GD205_DB_KKAJKCD_LAST ) {
			iRet = ZdbKekkaGD205UpdateOthers( &pKekkaArray[iKekkaLoop] );
			if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
//1.06 DELL printf("ZdbKekkaGD205UpdateOthers error(%d)\n", iRet);
				// 1.06 �ُ�I��	LOG
				sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205CreateFile",__LINE__,
							EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
							"ZdbKekkaGD205UpdateOthers error (%d)", iRet);

				//2006.12.08 Kim Jinsuk DB�G���[���ُ�I��������
 				nRetValue = iRet;				

				// ���[���o�b�N
				ZdbRollback();
			
				//2006.12.08�@Kim Jinsuk DB�G���[���ُ�I��������
				if((nRetValue < 0) && (nRetValue !=-803) && (nRetValue != -911))
				{

    				*sqlErrorFlag = 1;
    				printf("##### DB�G���[�@�����@#####\n");
    				printf("iRet %d", iRet);
					sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbKekkaGD205UpdateOthers", __LINE__,
        			EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
        			"DB �G���[�@����");
    				return( RTN_NG );
				}
				//2006.12.08�@Kim Jinsuk DB�G���[���ُ�I��������

				// 1.13 ADD STA �ꊇCOMMIT�ɔ����G���[���͏����𔲂���			
					// �G���[�t�@�C���Ƃ��邽�ߌ�����0�ɂ���
				*piHkkssknsu=0;	
				break;
				// 1.13 ADD END �ꊇCOMMIT�ɔ����G���[���͏����𔲂���			

			}
		}
		// 1.13 ADD 5000������COMMIT
		++iCmmtCnt;
		if( iCmmtCnt >= pEnv->iCommitSu ){
        	ZdbCommit();
			iCmmtCnt=0;
		}
		// 1.06 ADD �R�~�b�g
		// 1.13 DELL
        //ZdbCommit();

// 2006-04-20 H.Suyama Add End
		++*piHkkssknsu;

		++iFileLoopIdx;
	}
	// 1.13 ADD 5000������COMMIT �t�@�C���I�����ɂ͕K��COMMIT
	if(( iCmmtCnt >= 1 )			// COMMIT �ȍ~�̍X�V�������P�ȏ�
	 ||( *piHkkssknsu > 1 )){		// �񍐃t�@�C���o�͌������P�ȏ�
   		ZdbCommit();
	}

	// 1.12 ADD �ۗ��ȊO�񍐑Ώ�0���̏ꍇ�̍l��
	if( *piHkkssknsu == 0 ){
			// �t�@�C���N���[�Y
			fclose( fp );
			// ���ԃt�@�C���Ȃ̂�0byte�쐬��OK�Ƃ��A�t�@�C���폜�͍s��Ȃ�
			// 3.01 �t�@�C���폜
			sFncPutLog( TRCKIND_TRACE, __FILE__, "GD205CreateFile", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"unlink cSendFileTemp" );
			unlink( cSendFileTemp );
			return( RTN_NG );
	}

	// �t�@�C���o��
	if ( GD205WriteFile( fp, &stGD205Rec[0], iFileLoopIdx ) == RTN_NG ) {
		// �ُ�I��	LOG
//1.06 DELL printf("GD205WriteFile error\n");
		// 1.06 �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205CreateFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"GD205WriteFile error " );
		return( RTN_NG );
	}

	// �t�@�C���N���[�Y
	fclose( fp );

	// �t�@�C�����i�t���p�X�j��ԋp
	ZbmlInfocpy( pFileName, cFileName, PATH_MAX );

// 3.01 ADD STA
	// �t�@�C���g���q���ύX
	iRet = rename( cSendFileTemp, cSendFile );
	if ( iRet != 0 ) {
		// �ُ�I��	LOG
		// 1.06 �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD205CreateFile", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"CreateHULFTFile rename status:[%d] ", iRet );

		gintErrorCode = GD205_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	// �ԋp�p�Ƀt�@�C�����Ƒ��M�t�@�C���h�c��ݒ�
	memset( pHkkknriArrayOut->hkkflnm, 0, sizeof( pHkkknriArrayOut->hkkflnm ) );
	// 3.01 sprintf( pHkkknriArrayOut->hkkflnm, "%s_%04d_%s_%s_%s%04d%s",
	sprintf( pHkkknriArrayOut->hkkflnm, "%s_%04d_%s_%s_%s%03d0%s",
             // 3.01 pSysknrmst->sateid, 
             pEnv->cPrefixNm, 
			 pHkkknriArrayOut->hkksjno,
             pHkkknriArrayOut->seccd, sNewFlName, cKjnsriymd, 
			 // 3.01 pSysknrmst->ssntubn,
			 pHkkknriArrayOut->kkirilotno,
			 GD205_FILEEXT_DATA );
	memset( pHkkknriArrayOut->ssnmtfilid, 0, sizeof( pHkkknriArrayOut->ssnmtfilid ) );
	// 3.01 sprintf( pHkkknriArrayOut->ssnmtfilid, "%s%04d",
	sprintf( pHkkknriArrayOut->ssnmtfilid, "%s%03d0",
			 cKjnsriymd,
			 pHkkknriArrayOut->kkirilotno );
			 // 3.01 pSysknrmst->ssntubn );
// 3.01 ADD END

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FsFncShmCrt()												  */
/*�@�@�\�T�v�@�F���L����������												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FGD205Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F�Ȃ�														  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
static int sFncShmCrt( GD205Env *pEnv )
{
	int	 *shmData;

	// �擾
	pEnv->shm_Id = shmget( (key_t)pEnv->shm_Key,
							GD205_SHM_SIZE,
							0666 | IPC_CREAT );
	if ( pEnv->shm_Id < 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_SHM_GET;
		return( RTN_NG );
	}

	// �A�^�b�`
	shmData = ( int * ) shmat( pEnv->shm_Id, 0 , 0 );
	if ( shmData == ( int * )-1 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_SHM_AT;
		return( RTN_NG );
	}
loging ( "stocker : ���L������[CRT] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n",
		 pEnv->shm_Key, pEnv->shm_Id, *shmData, shmData );

	// �l�ݒ�
	*shmData = 0;

	// �f�^�b�`
	if ( shmdt( shmData ) == -1 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_SHM_DT;
		return( RTN_NG );
	}

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FsFncShmGet()												  */
/*�@�@�\�T�v�@�F���L�������擾												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FGD205Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@�@��Q�����Fint *pshmData		�l										  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
static int sFncShmGet( GD205Env *pEnv, int *pshmData )
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
		gintErrorCode = GD205_STSCODE_ERR_SHM_AT;
		return( RTN_NG );
	}

	// �l�ݒ�
	*pshmData = *shmData;

loging ( "stocker : ���L������[GET] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n",
		 pEnv->shm_Key, pEnv->shm_Id, *shmData, shmData );
	// �f�^�b�`
	if ( shmdt( shmData ) == -1 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_SHM_DT;
		return( RTN_NG );
	}

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FsFncShmDel()												  */
/*�@�@�\�T�v�@�F���L�������폜												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FGD205Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
static int sFncShmDel( GD205Env *pEnv )
{
	int	 *shmData;

loging ( "%s : ���L������[DEL] shmKey[%d]-ID[%d]\n",
		 MYAPP_APP_NAME, pEnv->shm_Key, pEnv->shm_Id);
	// �폜
	if ( shmctl( pEnv->shm_Id, IPC_RMID, NULL) < 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = GD205_STSCODE_ERR_SHM_DEL;
		return( RTN_NG );
	}
	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�F_sFncEnvDip()												  */
/*�@�@�\�T�v�@�F�v���O�������ϐ��o�͊֐��y�g���[�X�p�z					  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FGD205Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�F����														  */
/******************************************************************************/
static void _sFncEnvDip( GD205Env *pEnv )
{
//#if defined ( _TRACE )
	loging( "########## GD205 - _sFncEnvDip ##########\n" );
	loging( "\t%s : [%s]\n", GD205_PRM_DBNAME,		 pEnv->cDBName );
	loging( "\t%s : [%s]\n", GD205_PRM_DBUSER,		 pEnv->cDBUser );
	loging( "\t%s : [%s]\n", GD205_PRM_DBPAWD,		 pEnv->cDBPawd );
	loging( "\t%s : [%s]\n", GD205_PRM_DIR_DATAFILE,   pEnv->cDirDataFile );
	loging( "\t%s : [%s]\n", GD205_PRM_SLEEP_SEC,	  pEnv->iSleepSec );
	loging( "\t%s : [%s]\n", GD205_PRM_SHM_KEY,	pEnv->shm_Key );
	loging( "\t%s : [%s]\n", GD205_PRM_FILE_DBG,	pEnv->cDebugLogName );
	loging( "\t%s : [%s]\n", GD205_PRM_FILE_TR,	pEnv->cTraceLogName );
	loging( "\t%s : [%s]\n", GD205_PRM_FILE_ACS,	pEnv->cAccessLogName );
	loging( "\t%s : [%s]\n", GD205_PRM_FILE_ERR,	pEnv->cErrorLogName );
	loging( "\t%s : [%s]\n", GD205_PRM_UP_ID,		pEnv->cUpdateId );
	loging( "\t%s : [%s]\n", GD205_PRM_UP_NM,		pEnv->cUpdateName );
	loging( "\t%s : [%s]\n", GD205_PRM_PROC_MD,	pEnv->proc_mode );
	loging( "########## GD205 - _sFncEnvDip ##########\n" );
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
	GD205Env	stEnv;

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


