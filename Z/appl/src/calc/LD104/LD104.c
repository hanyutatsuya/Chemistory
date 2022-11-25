/********************************************************************/
/*									*/
/*		�a�l�k�l���������V�X�e��				*/
/*									*/
/*		�V�X�e����	�F������V�X�e��			*/
/*		�t�@�C����	�FLD104.c				*/
/*		�T�v		�F���T�e���C�g���ʗv���t�@�C���쐬����	*/
/*									*/
/********************************************************************/

/********************************************************************/
/*  Ver.	�쐬��		���O		�C�����e		*/
/* ---------------------------------------------------------------- */
/********************************************************************/

/********************************************************************/
/*	�C���N���[�h�錾						*/
/********************************************************************/
#include <time.h>
#include <errno.h>
#include "bml_date.h"
#include "bmllog.h"
#include "bmlprm.h"
#include "LD104.h"

/**************************************************************************/
/* Define��`								  */
/**************************************************************************/
// TRACE
#if defined ( _TRACE )
#define malloc(a)   _malloc(a, __FILE__, __LINE__)
#define free(p)	 _free(p, __FILE__, __LINE__)
#endif

#define      isAscii(c)      (((c) >= 0x20 && (c) <= 0x7e) ? 1 : 0)

/**************************************************************************/
/* �O���[�o���錾							  */
/**************************************************************************/
struct stcLogMember	gstLogMem;

/******************************************************************************/
/*�@�� �� ���@�FLD104ConvTimestamp()						*/
/*�@�@�\�T�v�@�F�����ϊ��֐�							*/
/*�@���@�@�́@�F								*/
/*�@�@��P�����FULONG ulTm	����						*/
/*�@�o�@�@�́@�F								*/
/*�@�@��Q�����Fchar *pDest	�ϊ��㕶����					*/
/*�@�@�@�@�@�@				YYYY-MM-DD-HH.MM.SS.000000		*/
/*�@���A���@�Fint								*/
/*�@�@�@�@�@�@	RTN_OK	: ����I��						*/
/*�@�@�@�@�@�@	RTN_NG	: �ُ�I��						*/
/******************************************************************************/
void LD104ConvTimestamp(ULONG ulTm, char *pDest)
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
/*�@�� �� ���@�FLD104ConvNumber()						*/
/*�@�@�\�T�v�@�F�˗���No�A����No�ϊ��֐�					*/
/*�@���@�@�́@�F								*/
/*�@�@��Q�����Fchar *pSrc	�ϊ��O������					*/
/*�@�@�@�@�@�@				[1][2][3][4][5][6][7][8][9][10][11]\0	*/
/*�@�o�@�@�́@�F								*/
/*�@�@��P�����Fchar *pDest	�ϊ��㕶����					*/
/*�@�@�@�@�@�@				[3][4][5] 0  0 [6][7][8][9][10][11]	*/
/*�@���A���@�Fint								*/
/*�@�@�@�@�@�@		RTN_OK	: ����I��					*/
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��					*/
/******************************************************************************/
int LD104ConvNumber(char *pDest, char *pSrc)
{
	// �|�C���^�̃`�F�b�N
	if ( pDest == NULL || pSrc == NULL ) {
		return( RTN_NG );
	}

	// �ϊ��O������̒����`�F�b�N
	if ( strlen( pSrc ) < LD104_LEN_NOITEM ) {
		return( RTN_NG );
	}

	memcpy( &pDest[LD104_POS_DESTNO1], &pSrc[LD104_POS_SRCNO1], LD104_LEN_SRCNO1 );
	memcpy( &pDest[LD104_POS_DESTNO2], LD104_DATA_STR00, strlen( LD104_DATA_STR00 ) );
	memcpy( &pDest[LD104_POS_DESTNO3], &pSrc[LD104_POS_SRCNO2], LD104_LEN_SRCNO2 );

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FLD104CopyFromLeft()						*/
/*�@�@�\�T�v�@�F�w�蕶����̍�����w�茅�����R�s�[����				*/
/*�@���@�@�́@�F								*/
/*�@�@��Q�����Fchar *pSrc			�R�s�[��������			*/
/*�@�@��R�����Fint iSize			�R�s�[����			*/
/*�@�@��S�����FBOOL bMbFlg			�}���`�o�C�g�t���O		*/
/* �@�@�@�@�@		TRUE	: �l������					*/
/* �@�@�@�@�@		FALSE	: ��������					*/
/*�@�o�@�@�́@�F								*/
/*�@�@��P�����Fchar *pDest			�R�s�[�㕶����			*/
/*�@���A���@�Fint								*/
/*�@�@�@�@�@�@		RTN_OK	: ����I��					*/
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��					*/
/******************************************************************************/
int LD104CopyFromLeft(char *pDest, char *pSrc, int iSize, BOOL bMbFlg)
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

/********************************************************************************/
/*�@�� �� ���@�FLD104CopyFromRight()						*/
/*�@�@�\�T�v�@�F�w�蕶����̉E����w�茅�����R�s�[����				*/
/*�@���@�@�́@�F								*/
/*�@�@��Q�����Fchar *pSrc	�R�s�[��������					*/
/*�@�@��R�����Fint iSize	�R�s�[����					*/
/*�@�@��S�����FBOOL bMbFlg	�}���`�o�C�g�t���O				*/
/* �@�@�@�@�@	TRUE	: �l������						*/
/* �@�@�@�@�@	FALSE	: ��������						*/
/*�@�o�@�@�́@�F								*/
/*�@�@��P�����Fchar *pDest			�R�s�[�㕶����			*/
/*�@���A���@�Fint								*/
/*�@�@�@�@�@�@		RTN_OK	: ����I��					*/
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��					*/
/********************************************************************************/
int LD104CopyFromRight(char *pDest, char *pSrc, int iSize, BOOL bMbFlg)
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
/*�@�� �� ���@�FinitFunction()							  */
/*�@�@�\�T�v�@�F���������֐�							  */
/*�@���@�@�́@�F								  */
/*�@�@��P�����Fint argc		�v���O����������			  */
/*�@�@��Q�����Fchar *argv[]		�v���O��������				  */
/*�@�o�@�@�́@�F								  */
/*�@���A���@�Fint								  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��					  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��					  */
/******************************************************************************/
int initFunction( int argc, char *argv[] )
{
	char	cPrmBuf[256];
	char	*lc_login;

	// ������
	// �v���O�������ϐ�������
	memset( &pAppEnv, '\0', sizeof( pAppEnv ) );

	// ���O�I�[�v��
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

	//      �J�n���O�o��
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�v���O�����N��" ) ;

	// �p�����[�^�t�@�C�����ޔ�
	lc_login= EnvRef( MYAPP_LOGINIFILE );
	if ( argc >= 2 ) {
		pAppEnv.pcFileNamePRM = EnvRef( argv[1] );
	} else {
		pAppEnv.pcFileNamePRM = EnvRef( MYAPP_INIFILE );
	}

	pAppEnv.bp = ZbmlPrmOpen( pAppEnv.pcFileNamePRM );
	if ( pAppEnv.bp == NULL ) {
		// �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmOpen", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "�p�����[�^�t�@�C���̃I�[�v���Ɏ��s���܂���[%s]", pAppEnv.pcFileNamePRM );
		return( RTN_NG );
	}

	// �f�[�^�x�[�X�ڑ���
	if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_DBNAME, pAppEnv.cDBName ) != 0 ) {
		// �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "�p�����[�^�̎擾�Ɏ��s���܂���[%s]", LD104_PRM_DBNAME );
		return( RTN_NG );
	}
	// ���O�C�����[�U
	if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_DBUSER, pAppEnv.cDBUser ) != 0 ) {
		// �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "�p�����[�^�̎擾�Ɏ��s���܂���[%s]", LD104_PRM_DBUSER );
		return( RTN_NG );
	}
        // �f�[�^�t���[�h�c
        if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_DATAFLOWID, pAppEnv.cDataFlowID ) != 0 ) {
                // �ُ�I��     LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "�p�����[�^�̎擾�Ɏ��s���܂���[%s]", LD104_PRM_DATAFLOWID );
                return( RTN_NG );
        }
        // ���M���h�c
        if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_SENDID_MOTO, pAppEnv.cSendIDMoto ) != 0 ) {
                // �ُ�I��     LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "�p�����[�^�̎擾�Ɏ��s���܂���[%s]", LD104_PRM_SENDID_MOTO );
                return( RTN_NG );
        }
        // ���M��h�c
        if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_SENDID_SAKI, pAppEnv.cSendIDSaki ) != 0 ) {
                // �ُ�I��     LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "�p�����[�^�̎擾�Ɏ��s���܂���[%s]", LD104_PRM_SENDID_SAKI );
                return( RTN_NG );
        }
	// ���O�C���p�X���[�h
	if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_DBPAWD, pAppEnv.cDBPawd ) != 0 ) {
		// �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "�p�����[�^�̎擾�Ɏ��s���܂���[%s]", LD104_PRM_DBPAWD );
		return( RTN_NG );
	}
	// �f�[�^�t�@�C���o�̓f�B���N�g��
	if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_DIR_DATAFILE, pAppEnv.cDirDataFile ) != 0 ) {
		// �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�p�����[�^�̎擾�Ɏ��s���܂���[%s]", LD104_PRM_DIR_DATAFILE );
		return( RTN_NG );
	}
	// �f�[�^�t�@�C�����M�p�f�B���N�g��
	if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_DIR_SEND, pAppEnv.cDirSend ) != 0 ) {
		// �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "�p�����[�^�̎擾�Ɏ��s���܂���[%s]", LD104_PRM_DIR_SEND );
		return( RTN_NG );
	}
	// �f�o�b�O���O�t�@�C��
	if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_FILE_DBG, pAppEnv.cDebugLogName ) != 0 ) {
		// �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "�p�����[�^�̎擾�Ɏ��s���܂���[%s]", LD104_PRM_FILE_DBG );
		return( RTN_NG );
	}
	// �g���[�X���O�t�@�C��
	if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_FILE_TR, pAppEnv.cTraceLogName ) != 0 ) {
		// �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "�p�����[�^�̎擾�Ɏ��s���܂���[%s]", LD104_PRM_FILE_TR );
		return( RTN_NG );
	}
	// �A�N�Z�X���O�t�@�C��
	if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_FILE_ACS, pAppEnv.cAccessLogName ) != 0 ) {
		// �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "�p�����[�^�̎擾�Ɏ��s���܂���[%s]", LD104_PRM_FILE_ACS );
		return( RTN_NG );
	}
	// �G���[���O�t�@�C��
	if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_FILE_ERR, pAppEnv.cErrorLogName ) != 0 ) {
		// �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "�p�����[�^�̎擾�Ɏ��s���܂���[%s]", LD104_PRM_FILE_ERR );
		return( RTN_NG );
	}
	// ���L�������L�[�擾
	if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_SHM_KEY, cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "�p�����[�^�̎擾�Ɏ��s���܂���[%s]", LD104_PRM_SHM_KEY );
		return( RTN_NG );
	}
	pAppEnv.shm_Key = atoi( cPrmBuf );
	// �X���[�v���ԁi�b�j�擾
	if ( ZbmlPrmGetVal( pAppEnv.bp, LD104_PRM_SLEEP_MIN, cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "�p�����[�^�̎擾�Ɏ��s���܂���[%s]", LD104_PRM_SLEEP_MIN );
		return( RTN_NG );
	}
	pAppEnv.iSleepMin= atoi( cPrmBuf );
	// �������t�̎擾
	if ( ZbmlPrmGetVal ( pAppEnv.bp, LD104_PRM_DATE_RANGE, cPrmBuf ) != 0 ) {
		// �ُ�I��     LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "�p�����[�^���擾�ł��܂���ł���[%s]", LD104_PRM_DATE_RANGE ) ;
		return ( -1 ) ;
	}
	pAppEnv.DateRange= atoi ( cPrmBuf ) ;

	// �p�����[�^�t�@�C���N���[�Y
	ZbmlPrmClose( pAppEnv.bp );

	// ���L����������
	if ( sFncShmCrt() != RTN_OK ) {
		return( RTN_NG );
	}

	return( RTN_OK );
}

/**************************************************************************/
/*�@�� �� ���@�FmainFunction()						  */
/*�@�@�\�T�v�@�F���C�������֐�						  */
/*�@���@�@�́@�F							  */
/*�@�o�@�@�́@�F							  */
/*�@���A���@�Fint							  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��				  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��				  */
/**************************************************************************/
int mainFunction()
{
	int		li_stopFlg = 0;

	int		min = 0;
	int		iRet;
	int		iKekkaNumOut;
	char		serch_date[11];

	Sysknrmst	stSysknrmst;
	GetKekka	*pGetKekkaArrayOut;

	if( iRet = ZdbConnect( pAppEnv.cDBName, pAppEnv.cDBUser, pAppEnv.cDBPawd ) ) {
		return( RTN_NG );
	}

	// �i�v���[�v�A��~�R�}���h�ŏI��
	while ( 1 ) {
		/* 1�����Ƃɒ�~�R�}���h���m�F���Ȃ���ݒ肳�ꂽ���ԃX���[�v */
		for ( min=0; min < pAppEnv.iSleepMin; min++ ) {
			sleep( 60 );
			// ��~�R�}���h�m�F
			if ( sFncShmGet( &li_stopFlg ) != RTN_OK ) {
				return( RTN_NG );
			}
			if ( li_stopFlg == 1 ) {
				return( RTN_OK );
			}
			// �V�X�e���Ǘ����擾
			iRet = ZdbSysknrmstSelect( &stSysknrmst );
			if ( iRet != HRC_SQL_NORMAL ) {
				return( RTN_NG );
			}
			// �����d�m�c�����Ă���ꍇ�́A���������̊J�n�m�F���s���B
			if ( stSysknrmst.bchendflg == '1' ){
				/* �����������n�܂��Ă�����I�� */
				if ( stSysknrmst.unyflg == '1' ){
					sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						     "���������̊J�n���m�F���܂����B");
					return( RTN_OK );
				}
			}
		}

		// �V�X�e���Ǘ����擾
		iRet = ZdbSysknrmstSelect( &stSysknrmst );
		if ( iRet != HRC_SQL_NORMAL ) {
			return( RTN_NG );
		}
		// �����d�m�c�����Ă��Ȃ���΁A�������J�n���Ȃ�
		if ( stSysknrmst.bchendflg != '1' ){
			continue;
		}

		sFncPutLog( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
			    "�v���J�[�h�쐬�����J�n");

		memset( serch_date, '\0', sizeof( serch_date ) );
		sFncGetdate( serch_date, stSysknrmst.kjnsriymd, pAppEnv.DateRange );
		iRet = ZdbKekkaLD104Select( serch_date, &pGetKekkaArrayOut, &iKekkaNumOut );
		if ( iRet == HRC_SQL_NORMAL ) {
			/* ���M�Ǘ��ʔ� �J�E���g�A�b�v */
			++stSysknrmst.ssntubn;
			iRet = ZdbSysknrmstUpdate( &stSysknrmst );
		        if ( iRet != HRC_SQL_NORMAL ) {
				// ���[���o�b�N
				ZdbRollback();
				sFncPutLog( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
					    "ZdbSysknrmstUpdate error [%d]", iRet );

				return( RTN_NG );
		        }
			// �R�~�b�g
			ZdbCommit();

			// �v���J�[�h�t�@�C���̍쐬
			if ( LD104CreateFile( &stSysknrmst, pGetKekkaArrayOut, iKekkaNumOut) != RTN_OK ) {
				return( RTN_NG );
			}
		} else if ( iRet == HRC_SQL_NOT_FOUND ) {
			sFncPutLog( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
				    "�v���J�[�h�쐬�Ώۖ���");
		} else {
			// ���ʏ������
			if ( pGetKekkaArrayOut != NULL ) {
				ZbmlFree( pGetKekkaArrayOut );
			}
			return( RTN_NG );
		}

		// ���ʏ������
		if ( pGetKekkaArrayOut != NULL ) {
			ZbmlFree( pGetKekkaArrayOut );
		}
	}

	return( RTN_OK );
}

/**************************************************************************/
/*�@�� �� ���@�FendFunction()						  */
/*�@�@�\�T�v�@�F�I�������֐�						  */
/*�@���@�@�́@�F							  */
/*�@�o�@�@�́@�F							  */
/*�@���A���@�F�Ȃ�							  */
/**************************************************************************/
void endFunction()
{
	/***	
	***    �f�[�^�x�[�X�N���[�Y
	**/
	ZdbDisConnect() ;

	// ���L�������폜
	if ( sFncShmDel() != RTN_OK ) {
		return;
	}
	/*      �I�����O�o�� */
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�v���O�����I��" ) ;
	/*      ���O�N���[�Y */
	ZbmlCloseLog() ;

	return ;
}

/**************************************************************************/
/*�@�� �� ���@�FLD104MakeData()						  */
/*�@�@�\�T�v�@�F���T�e���C�g���ʗv���t�@�C���f�[�^�쐬			  */
/*�@���@�@�́@�F							  */
/*�@�@��P�����FKekka *pKekka		�������ʃf�[�^			  */
/*�@�o�@�@�́@�F							  */
/*�@�@��R�����FLD104Rec *pLD104Rec	�v���t�@�C���f�[�^		  */
/*�@���A���@�Fint							  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��				  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��				  */
/**************************************************************************/
int LD104WriteRecord(FILE *fp, GetKekka *pGetKekka)
{
	int		iFileCnt;
	LD104Rec	pLD104Rec;

	// �������ʃf�[�^�ւ̃|�C���^��NULL�̏ꍇ�ُ�I��
	if ( pGetKekka == NULL ) {
		return( RTN_NG );
	}

	// �v���t�@�C���f�[�^���X�y�[�X�ŃN���A
	memset( &pLD104Rec, LD104_DATA_SPACE, sizeof(LD104Rec) );

	// ���R�[�h���ʎq
	memcpy( pLD104Rec.c_sbt, "R11", sizeof( pLD104Rec.c_sbt ));

	// �a�l�k��t�N����
	// [YYYYMMDD]�ɕϊ����Đݒ�
	ZbmlChgAPDate( pLD104Rec.c_utkymd, pGetKekka->utkymd );
	// �˗����m���D
	// ������11�������̂悤�ɕϊ�
	// (�ϊ��O)[1][2][3][4][5][6][7][8][9][10][11]
	// (�ϊ���)[3][4][5] 0  0 [6][7][8][9][10][11]
	if ( LD104ConvNumber( pLD104Rec.c_irino, pGetKekka->irino ) == RTN_NG ) {
		return( RTN_NG );
	}
	// ���ڃR�[�h
	if ( LD104CopyFromLeft( pLD104Rec.c_kmkcd, pGetKekka->kmkcd, sizeof( pLD104Rec.c_kmkcd ), FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}

        /* FILLER               */
        memset( pLD104Rec.c_filler, ' ', sizeof( pLD104Rec.c_filler ));
        /* ���s����             */
        memcpy( pLD104Rec.c_kaigyo, "\n", sizeof( pLD104Rec.c_kaigyo ));

	// ���R�[�h������
	iFileCnt = fwrite( &pLD104Rec, sizeof( LD104Rec ) , 1, fp);
	if ( iFileCnt != 1 ) {
		// �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "LD104WriteFile", __LINE__,
			    EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "write status:[%d] ", iFileCnt );
		return( RTN_NG ) ;
	}

	return( RTN_OK );
}

/************************************************************************/
/*�@�� �� ���@�FLD104WriteFile()					*/
/*�@�@�\�T�v�@�F�g���[���[���R�[�h������				*/
/*�@���@�@�́@�F							*/
/*�@�@��P�����FFILE *fp		�t�@�C���|�C���^		*/
/*�@�@��Q�����FLD104Rec *pLD104Rec	�v���t�@�C���f�[�^		*/
/*�@�o�@�@�́@�F�������ʃt�@�C��					*/
/*�@���A���@�Fint							*/
/*�@�@�@�@�@�@		RTN_OK	: ����I��				*/
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��				*/
/************************************************************************/
int LD104WriteHeader(FILE *fp, Sysknrmst *pSysknrmst)
{
	int		iFileCnt;
	LD104Header	z00;

	memset( &z00, ' ', sizeof( struct Z00SJHD ) );

        /* ں��ގ��ʎq          */
        memcpy( z00.c_sbt, "HD", sizeof( z00.c_sbt ));
        /* ���M��               */
        memcpy( z00.c_sosinsaki, pAppEnv.cSendIDSaki, strlen( pAppEnv.cSendIDSaki ));
        /* ���M��               */
        memcpy( z00.c_sosinmoto, pAppEnv.cSendIDMoto, strlen( pAppEnv.cSendIDMoto ));
        /* ���M�������N����     */
	// [YYYYMMDD]�ɕϊ����Đݒ�
	ZbmlChgAPDate( z00.c_opedate, pSysknrmst->kjnsriymd );
        /* �ʔ�                 */
	sprintf( z00.c_tuban, "%04d" , pSysknrmst->ssntubn);
	/* �ް��۰ID */
	memcpy( z00.c_dflow,   pAppEnv.cDataFlowID, strlen( pAppEnv.cDataFlowID ));
        /* ���Ұ�1              */
        memset( z00.c_param1, ' ', sizeof( z00.c_param1 ));
        /* ���Ұ�2              */
        memset( z00.c_param2, ' ', sizeof( z00.c_param2 ));
        /* �\��                 */
        memset( z00.c_yobi, ' ', sizeof( z00.c_yobi ));
        /* FILLER               */
        memset( z00.c_filler, ' ', sizeof( z00.c_filler ));
        /* ���s����             */
        memcpy( z00.c_kaigyo, "\n", sizeof( z00.c_kaigyo ));

	// ���R�[�h������
	iFileCnt = fwrite( &z00, sizeof( z00 ) , 1, fp);
	if ( iFileCnt != 1 ) {
		// �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "LD104WriteFile", __LINE__,
			    EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "write status:[%d] ", iFileCnt );
		return( RTN_NG ) ;
	}


	return( RTN_OK );
}

/************************************************************************/
/*�@�� �� ���@�FLD104WriteTrailer()					*/
/*�@�@�\�T�v�@�F�g���[���[���R�[�h������				*/
/*�@���@�@�́@�F							*/
/*�@�@��P�����FFILE *fp		�t�@�C���|�C���^		*/
/*�@�@��Q�����FLD104Rec *pLD104Rec	�v���t�@�C���f�[�^		*/
/*�@�o�@�@�́@�F�������ʃt�@�C��					*/
/*�@���A���@�Fint							*/
/*�@�@�@�@�@�@		RTN_OK	: ����I��				*/
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��				*/
/************************************************************************/
int LD104WriteTrailer(FILE *fp, Sysknrmst *pSysknrmst, int iKekkaNum)
{
	int		iFileCnt;
	LD104Trailer	z01;

        // PNC����M �A�g���[���[�쐬
	memset( &z01, ' ', sizeof( LD104Trailer ) );

        /* ں��ގ��ʎq          */
	memcpy( z01.c_sbt, "TR", sizeof( z01.c_sbt ));
        /* ���M��               */
        memcpy( z01.c_sosinsaki, pAppEnv.cSendIDSaki, strlen( pAppEnv.cSendIDSaki ));
        /* ���M��               */
        memcpy( z01.c_sosinmoto, pAppEnv.cSendIDMoto, strlen( pAppEnv.cSendIDMoto ));
        /* ���M�������N����     */
	// [YYYYMMDD]�ɕϊ����Đݒ�
	ZbmlChgAPDate( z01.c_opedate, pSysknrmst->kjnsriymd );
        /* �ʔ�                 */
	sprintf( z01.c_tuban, "%04d" , pSysknrmst->ssntubn);
	/* �ް��۰ID */
	memcpy( z01.c_dflow,   pAppEnv.cDataFlowID, strlen( pAppEnv.cDataFlowID ));
        /* ����ں��ތ��� */
	sprintf( z01.c_reccnt, "%08d" , iKekkaNum + 2);
        /* �_��ں��ތ����P */
	sprintf( z01.c_reccnt01, "%08d" , iKekkaNum);
        /* �_��ں��ތ����Q�`�P�T */
        memset( z01.c_reccnt02, '0', sizeof( z01.c_reccnt02 ));
        /* �\��                 */
        memset( z01.c_yobi, ' ', sizeof( z01.c_yobi ));
        /* FILLER               */
        memset( z01.c_filler, ' ', sizeof( z01.c_filler ));
        /* ���s����             */
        memcpy( z01.c_kaigyo, "\n", sizeof( z01.c_kaigyo ));

	// ���R�[�h������
	iFileCnt = fwrite( &z01, sizeof( z01 ) , 1, fp);
	if ( iFileCnt != 1 ) {
		// �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "LD104WriteFile", __LINE__,
			    EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "write status:[%d] ", iFileCnt );
		return( RTN_NG ) ;
	}

	return( RTN_OK );
}

/********************************************************************************/
/*�@�� �� ���@�FLD104CreateFile()						*/
/*�@�@�\�T�v�@�F�v���t�@�C���쐬						*/
/*�@���@�@�́@�F								*/
/*�@�@��P�����FGetKekka *pGetKekkaArray	�������ʏ��			*/
/*�@�@��Q�����Fint iKekkaNum			�������ʏ�񌏐�		*/
/*�@�o�@�@�́@�F								*/
/*�@���A���@�Fint								*/
/*�@�@�@�@�@�@		RTN_OK	: ����I��					*/
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��					*/
/********************************************************************************/
int LD104CreateFile(Sysknrmst *pSysknrmst, GetKekka *pGetKekkaArray, int iKekkaNum)
{
	int		iRet = 0;
	FILE *		fp;
	int		iKekkaLoop;
	time_t timer;
        struct tm	*tm;
	char		cToday[LD104_LEN_DATETIME + 1];
	char		cTmpFileName[PATH_MAX + 1];
	char		cFileName[PATH_MAX + 1];


	// �����`�F�b�N
	if ( pGetKekkaArray == NULL ) {
		return( RTN_NG );
	}

	time(&timer);
        tm = localtime(&timer);
        sprintf( cToday, "%04d%02d%02d%02d%02d%02d",
                         tm->tm_year + 1900,
                         tm->tm_mon + 1,
                         tm->tm_mday,
                         tm->tm_hour,
                         tm->tm_min,
                         tm->tm_sec );

	// �t�@�C��������
	sprintf( cTmpFileName, "%s/REQ00%s%s", pAppEnv.cDirDataFile, cToday, LD104_FILEEXT_DATA );
	sprintf( cFileName, "%s/REQ00%s%s", pAppEnv.cDirSend, cToday, LD104_FILEEXT_DATA );

	// �t�@�C���I�[�v��
	fp = fopen ( cTmpFileName, "w" );
	if ( fp == NULL ) {
		// �ُ�I��	LOG
		sFncPutLog( TRCKIND_ERROR, __FILE__, "LD104CreateFile",__LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			    "fopen error [%s]:%s", cTmpFileName, strerror(errno) );
		fclose( fp );
		return( RTN_NG ) ;
	}

	// �w�b�_�o��
	if ( LD104WriteHeader( fp, pSysknrmst ) == RTN_NG ) {
		sFncPutLog( TRCKIND_ERROR, __FILE__, "LD104CreateFile",__LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			    "LD104WriteFile error [%s]", cTmpFileName );
		fclose( fp );
		return( RTN_NG );
	}

	// �v�����ʏ����P��������
	for ( iKekkaLoop = 0;
		  iKekkaLoop < iKekkaNum;
		  iKekkaLoop++ ) {

		// ���ʂ��t�@�C���o�͌`���ɓW�J
		if ( LD104WriteRecord( fp, &pGetKekkaArray[iKekkaLoop] ) == RTN_NG ) {
			sFncPutLog( TRCKIND_ERROR, __FILE__, "LD104CreateFile",__LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				    "LD104MakeData error [%s]", cTmpFileName );
			fclose( fp );
			return( RTN_NG );
		}

	}

	// �t�b�^�[ �o��
	if ( LD104WriteTrailer( fp, pSysknrmst, iKekkaNum ) == RTN_NG ) {
		sFncPutLog( TRCKIND_ERROR, __FILE__, "LD104CreateFile",__LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "LD104WriteFile error [%s]", cTmpFileName );
		fclose( fp );
		return( RTN_NG );
	}

	// �t�@�C���N���[�Y
	fclose( fp );

	// �t�@�C���𑗐M�p�f�B���N�g���ֈړ�
	if ( rename( cTmpFileName, cFileName ) != 0 ){
		sFncPutLog( TRCKIND_ERROR, __FILE__, "LD104CreateFile",__LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			    "rename error [%s]->[%s]:%s", cTmpFileName, cFileName, strerror(errno) );
		return( RTN_NG );
	}

	sFncPutLog( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
		    "�t�@�C���쐬���� [%s : %d��]", cFileName, iKekkaNum );

	return( RTN_OK );
}

/******************************************************************************/
/*  �� �� ���@�FsFncGetdate()                                                   */
/*  �@�\�T�v�@�F���t���Z�֐�                                                    */
/*  ���@�@�́@�F                                                              */
/*�@ ��Q���� �Fchar *  ����t������( yyyy-mm-dd )                            */
/*�@ ��R���� �Fint     ��������(���ʂɎw�肷��Ɖ�����B�|�w��ŉ����O�ƂȂ�)  */
/*  �o�@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *  �擾���t������( yyyy-mm-dd )                            */
/******************************************************************************/
void sFncGetdate( newdate, date, days )
char *newdate ;
char *date ;
int days ;
{
	int y, m, d;

	sscanf(date, "%d-%d-%d", &y, &m, &d);
	struct tm tm = { 0, 0, 0, d, m-1, y-1900 };
	time_t time = mktime(&tm) + 86400 * days;
	struct tm *ltime = localtime(&time);

	sprintf(newdate, "%d-%02d-%02d", ltime->tm_year+1900, ltime->tm_mon+1, ltime->tm_mday);
}

/******************************************************************************/
/*�@�� �� ���@�FsFncShmCrt()							*/
/*�@�@�\�T�v�@�F���L����������							*/
/*�@���@�@�́@�F								*/
/*�@�o�@�@�́@�F�Ȃ�								*/
/*�@���A���@�Fint								*/
/*�@�@�@�@�@�@		RTN_OK	: ����I��					*/
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��					*/
/******************************************************************************/
static int sFncShmCrt()
{
	int	 *shmData;

	// �擾
	pAppEnv.shm_Id = shmget( (key_t)pAppEnv.shm_Key, LD104_SHM_SIZE, 0666 | IPC_CREAT );
	if ( pAppEnv.shm_Id < 0 ) {
		// �ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmget", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"���L�������̑���Ɏ��s���܂���" ) ;
		return( RTN_NG );
	}

	// �A�^�b�`
	shmData = ( int * ) shmat( pAppEnv.shm_Id, 0 , 0 );
	if ( shmData == ( int * )-1 ) {
		// �ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmat", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"���L�������̑���Ɏ��s���܂���" ) ;
		return( RTN_NG );
	}

	// �l�ݒ�
	*shmData = 0;

	// �f�^�b�`
	if ( shmdt( shmData ) == -1 ) {
		// �ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"���L�������̑���Ɏ��s���܂���" ) ;
		return( RTN_NG );
	}

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FsFncShmGet()							*/
/*�@�@�\�T�v�@�F���L�������擾							*/
/*�@���@�@�́@�F								*/
/*�@�o�@�@�́@�F								*/
/*�@�@��P�����Fint *pshmData		�l					*/
/*�@���A���@�Fint								*/
/*�@�@�@�@�@�@		RTN_OK	: ����I��					*/
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��					*/
/******************************************************************************/
static int sFncShmGet( int *pshmData )
{
	int	 *shmData;

	//
	if ( pshmData == NULL ) {
		// �ُ�I��	LOG
		return( RTN_NG );
	}

	// �A�^�b�`
	shmData = ( int * ) shmat( pAppEnv.shm_Id, 0 , 0 );
	if ( shmData == ( int * )-1 ) {
		//      �ُ�I��        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmat", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"���L�������̑���Ɏ��s���܂���" ) ;

		return( RTN_NG );
	}

	// �l�ݒ�
	*pshmData = *shmData;

	// �f�^�b�`
	if ( shmdt( shmData ) == -1 ) {
		// �ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"���L�������̑���Ɏ��s���܂���" ) ;

		return( RTN_NG );
	}

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FsFncShmDel()							*/
/*�@�@�\�T�v�@�F���L�������폜							*/
/*�@���@�@�́@�F								*/
/*�@�o�@�@�́@�F								*/
/*�@���A���@�Fint								*/
/*�@�@�@�@�@�@		RTN_OK	: ����I��					*/
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��					*/
/******************************************************************************/
static int sFncShmDel()
{
	int	 *shmData;

	loging ( "%s : ���L������[DEL] shmKey[%d]-ID[%d]\n",
		 MYAPP_APP_NAME, pAppEnv.shm_Key, pAppEnv.shm_Id);
	// �폜
	if ( shmctl( pAppEnv.shm_Id, IPC_RMID, NULL) < 0 ) {
		// �ُ�I��	LOG
		return( RTN_NG );
	}
	return( RTN_OK );
}


/******************************************************************************/
/*�@�� �� ���@�FsFncPutLog()							*/
/*�@�@�\�T�v�@�F�A�v���P�[�V�������O�o��					*/
/*�@���@�@�́@�F								*/
/*�@�@��P�����Fchar *	  �ҏW������						*/
/*�@�o�@�@�́@�F								*/
/*�@���A���@�F����								*/
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
/*�@�� �� ���@�Fmain()								*/
/*�@�@�\�T�v�@�F�v���J�[�h�t�@�C���쐬�������C��				*/
/*�@���@�@�́@�F								*/
/*�@�@��P�����Fint argc		�v���O����������			*/
/*�@�@��Q�����Fchar *argv[]		�v���O��������				*/
/*�@�o�@�@�́@�F								*/
/*�@���A���@�Fint								*/
/******************************************************************************/
int main( int argc, char *argv[] )
{
    if ( daemon ( 1, 0 ) < 0 ) {
        exit ( 9 ) ;
    }

	// ��������
	if ( initFunction( argc, argv )  != 0 ) {
		exit( 9 );
	}

	// �又��
	if ( mainFunction()  != 0 ) {
		exit( 9 );
	}

	// �I������
	endFunction();
}
