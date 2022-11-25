/********************************************************************/
/*																	*/
/*		�a�l�k�l���������V�X�e��									*/
/*																	*/
/*		�V�X�e����	�F������V�X�e��								*/
/*		�t�@�C����	�FED203Main.c									*/
/*		�T�v		�F�ً}���ʕ񍐃t�@�C���쐬����					*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	�쐬��			���O			�C�����e				*/
/* ---------------------------------------------------------------- */
/*  1.00	2006/03/13		H.Suyama		Create					*/
/********************************************************************/

/********************************************************************/
/*	�C���N���[�h�錾												*/
/********************************************************************/
#include <time.h>
//#include "bml_misc.h"
#include "bml_date.h"
#include "bmllog.h"
#include "bmlprm.h"
#include "ED203Main.h"
#include "Sysknrmst.h"
#include "ED203Hkkknri.h"

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
ED203_STSCODE		gintErrorCode;
struct stcLogMember	gstLogMem;

/******************************************************************************/
/*�@�� �� ���@�FED203ConvTimestamp()										  */
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
void ED203ConvTimestamp(ULONG ulTm, char *pDest)
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
/*�@�� �� ���@�FED203ConvNumber()											  */
/*�@�@�\�T�v�@�F�˗���No�A����No�ϊ��֐�									  */
/*�@���@�@�́@�F															  */
/*�@�@��Q�����Fchar *pSrc			�ϊ��O������							  */
/*�@�@�@�@�@�@						[1][2][3][4][5][6][7][8][9][10][11]\0	  */
/*�@�o�@�@�́@�F															  */
/*�@�@��P�����Fchar *pDest			�ϊ��㕶����							  */
/*�@�@�@�@�@�@						[4][5][6][7][8][9]						  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int ED203ConvNumber(char *pDest, char *pSrc)
{
	// �|�C���^�̃`�F�b�N
	if ( pDest == NULL || pSrc == NULL ) {
		return( RTN_NG );
	}

	// �ϊ��O������̒����`�F�b�N
	if ( strlen( pSrc ) < ED203_LEN_NOITEM ) {
		return( RTN_NG );
	}

	memcpy( pDest, &pSrc[ED203_POS_SRCNO], ED203_LEN_SRCNO );

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FED203CopyFromLeft()											  */
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
int ED203CopyFromLeft(char *pDest, char *pSrc, int iSize, BOOL bMbFlg)
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
/*�@�� �� ���@�FED203CopyFromRight()										  */
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
int ED203CopyFromRight(char *pDest, char *pSrc, int iSize, BOOL bMbFlg)
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
/*�@�� �� ���@�FinitFunction()												  */
/*�@�@�\�T�v�@�F���������֐�												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����Fint argc			�v���O����������						  */
/*�@�@��Q�����Fchar *argv[]		�v���O��������							  */
/*�@�@��R�����FED203Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int initFunction( int argc, char *argv[], ED203Env *pEnv )
{
	char	cPrmBuf[256];
	char	*lc_login;

	// ������
	// �G���[�X�e�[�^�X�ύX
	gintErrorCode = 0;
	// �v���O�������ϐ�������
	memset( pEnv, '\0', sizeof( ED203Env ) );

	// ���O�I�[�v��
	if( ZbmlOpenLog( MYAPP_LOGINIFILE ) != 0 ) {
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
		gintErrorCode = ED203_STSCODE_ERR_USEGE;
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
		gintErrorCode = ED203_STSCODE_ERR_PRM_FILE;
		sFncPutLog( TRCKIND_ERROR, __FILE__, "ZZbmlPrmOpen", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�p�����[�^�t�@�C���̃I�[�v���Ɏ��s���܂���[%s]", pEnv->pcFileNamePRM );
		return( RTN_NG );
	}

	// �f�[�^�x�[�X�ڑ���
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_DBNAME,
						 pEnv->cDBName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���O�C�����[�U
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_DBUSER,
						pEnv->cDBUser ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���O�C���p�X���[�h
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_DBPAWD,
						pEnv->cDBPawd ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �񍐃f�[�^�t�@�C���o�̓f�B���N�g��
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_DIR_DATAFILE,
						pEnv->cDirDataFile ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �f�o�b�O���O�t�@�C��
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_FILE_DBG,
						pEnv->cDebugLogName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �g���[�X���O�t�@�C��
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_FILE_TR,
						pEnv->cTraceLogName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �A�N�Z�X���O�t�@�C��
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_FILE_ACS,
						pEnv->cAccessLogName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �G���[���O�t�@�C��
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_FILE_ERR,
						pEnv->cErrorLogName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���L�������L�[�擾
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_SHM_KEY,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->shm_Key = atoi( cPrmBuf );
	// �X���[�v���ԁi�b�j�擾
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_SLEEP_SEC,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	pEnv->iSleepSec= atoi( cPrmBuf );
	// �X�V��ID
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_UP_ID,
						pEnv->cUpdateId ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// �X�V�Җ�
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_UP_NM,
						pEnv->cUpdateName ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
		return( RTN_NG );
	}
	// ���s���[�h
	if ( ZbmlPrmGetVal( pEnv->bp, ED203_PRM_PROC_MD,
						cPrmBuf ) != 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = ED203_STSCODE_ERR_PRM_GET;
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
/*�@�@��P�����FED203Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int mainFunction( ED203Env *pEnv )
{
	int			iRet;
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
	char		cHkkflnm[51];
	int			li_stopFlg = 0;

	//�g���[�X���O
	sFncPutLog( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	if( iRet = ZdbConnect( pEnv->cDBName,
						   pEnv->cDBUser,
						   pEnv->cDBPawd ) ) {
		// �ُ�I��	LOG
printf("ZdbConnect error (%d)\n", iRet);
		return( RTN_NG );
	}

	// �񍐊Ǘ����e�[�u���Ď�
	// �i�v���[�v�A��~�R�}���h�ŏI��
	while ( 1 ) {
		// ��~�R�}���h�m�F
		if ( sFncShmGet( pEnv, &li_stopFlg ) != RTN_OK ) {
printf("sFncShmGet error\n");
			return( RTN_NG );
		}
		if ( li_stopFlg == 1 ) {
			break;
		}

		// �񍐊Ǘ���񌟍�
		iRet = ZdbHkkknriED203SelectAll( &pHkkknriArrayOut, &iHkkknriNumOut );
		if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
			//�ُ�I��
			//���O�o��
printf("ZdbHkkknriED203SelectAll error (%d)\n", iRet);
			return( RTN_NG );
		}
		if ( iRet == HRC_SQL_NORMAL ) {
			// �񍐊Ǘ������P��������
			for ( iHkkknriLoop = 0;
				  iHkkknriLoop < iHkkknriNumOut;
				  iHkkknriLoop++ ) {
				// �쐬�J�n�������擾
				time( (long *)&ulSt );

				// �쐬�����A�ۗ��������N���A
				iHkkssknsu = 0;
				iHkkhrysu = 0;
				memset( cHkkflnm, 0, sizeof( cHkkflnm ) );

				// ���ʏ�񌟍��i���M�Ώۂ̂݁j
				// �񍐋敪�����ʏ󋵃R�[�h�̒l�ɂ��킹��
				switch ( pHkkknriArrayOut[iHkkknriLoop].hkkkbn ) {
				case '1':	// �ŏI
					pHkkknriArrayOut[iHkkknriLoop].hkkkbn = '3';
					break;
				case '2':	// ����
					pHkkknriArrayOut[iHkkknriLoop].hkkkbn = '1';
					break;
				}
				iRet = ZdbKekkaED203SelectByKkIriLotNo( &pHkkknriArrayOut[iHkkknriLoop],
														&pKekkaArrayOut, &iKekkaNumOut );
				if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
					// �ُ�I��	LOG
printf("ZdbKekkaED203SelectByXXXX error (%d)\n", iRet);
					return( RTN_NG );
				}
				if ( iRet == HRC_SQL_NORMAL ) {
					if ( ED203CreateFile( pEnv, 
										  pKekkaArrayOut,
										  iKekkaNumOut,
										  &iHkkssknsu,
										  &iHkkhrysu,
										  cHkkflnm ) == RTN_NG ) {
						// �ُ�I��	LOG
printf("ED203CreateFile error\n");
						return( RTN_NG );
					}
				}

				// ���ʏ������
				if ( pKekkaArrayOut != NULL ) {
					ZbmlFree( pKekkaArrayOut );
				}

				// �쐬�����������擾
				time( (long *)&ulEd );

				// �쐬�J�n����
				ED203ConvTimestamp( ulSt, cTimestamp );
				ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkstdh,
							 cTimestamp,
							 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkstdh ) );
				// �쐬��������
				ED203ConvTimestamp( ulEd, cTimestamp );
				ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkeddh,
							 cTimestamp,
							 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkeddh ) );
				// �񍐃t�@�C����
				ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkflnm,
							 cHkkflnm,
							 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkflnm ) );
				// �쐬����
				pHkkknriArrayOut[iHkkknriLoop].hkkssknsu = iHkkssknsu;
				// �񍐕ۗ�����
				pHkkknriArrayOut[iHkkknriLoop].hkkhrysu = iHkkhrysu;
				// �񍐏󋵃t���O
				ZbmlInfocpy( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg,
							 ED203_DB_HKKJKFLG_CHUU,
							 sizeof( pHkkknriArrayOut[iHkkknriLoop].hkkjkflg ) );
				// ���X�V�����͊֐����Őݒ�

				// �񍐊Ǘ������X�V
				iRet = ZdbHkkknriED203Update( &pHkkknriArrayOut[iHkkknriLoop] );
				if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
					// ���[���o�b�N
					ZdbRollback();
					// �ُ�I��	LOG
printf("ZdbHkkknriUpdate error (%d)\n", iRet);
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
/*�@�@��P�����FED203Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�F�Ȃ�														  */
/******************************************************************************/
void endFunction( ED203Env *pEnv )
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
/*�@�� �� ���@�FED203MakeData()												  */
/*�@�@�\�T�v�@�F�񍐃f�[�^�쐬												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FKekka *pKekka		�������ʃf�[�^							  */
/*�@�o�@�@�́@�F															  */
/*�@�@��Q�����FED203Rec *pED203Rec	�񍐃f�[�^								  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int ED203MakeData(Kekka *pKekka, ED203Rec *pED203Rec)
{
	char	cTempBuff[128];

	// �������ʃf�[�^�܂��͕񍐃f�[�^�ւ̃|�C���^��NULL�̏ꍇ�ُ�I��
	if ( pKekka == NULL || pED203Rec == NULL ) {
		return( RTN_NG );
	}

	// �񍐃f�[�^���X�y�[�X�ŃN���A
	memset( pED203Rec, ED203_DATA_SPACE, sizeof(ED203Rec) );

	// �������ʃf�[�^����񍐃f�[�^���쐬
	// �a�l�k��t�N����
	// [YYYYMMDD]�ɕϊ����Đݒ�
	ZbmlChgAPDate( pED203Rec->cUTKYMD, pKekka->utkymd );
	// ���̂m���D
	// ������11�������̂悤�ɕϊ�
	// (�ϊ��O)[1][2][3][4][5][6][7][8][9][10][11]
	// (�ϊ���)[4][5][6][7][8][9]
	if ( ED203ConvNumber( pED203Rec->cKNTNO, pKekka->kntno ) == RTN_NG ) {
		return( RTN_NG );
	}
	// FILLER1
	// �󔒂�ݒ�Ȃ̂ŉ������Ȃ�
	// �e���ڃR�[�h
	if ( ED203CopyFromRight( pED203Rec->cOYAKMKCD,
							 pKekka->oyakmkcd,
							 sizeof( pED203Rec->cOYAKMKCD ),
							 FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// ���ڃR�[�h
	if ( ED203CopyFromRight( pED203Rec->cKMKCD,
							 pKekka->kmkcd,
							 sizeof( pED203Rec->cKMKCD ),
							 FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// �v�r�R�[�h�i�T���v�����O�R�[�h�j
	if ( ED203CopyFromRight( pED203Rec->cWSCD,
							 pKekka->smpcd,
							 sizeof( pED203Rec->cWSCD ),
							 FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// �v�r�r�d�p�i�����r�d�p�j
	// ���l�𕶎���ɕϊ���A�E����4����ݒ�B�iw�w�w�w�w�w�w�w��Ȃ��j
	sprintf( cTempBuff, "%06d", pKekka->knsseq );
	if ( ED203CopyFromRight( pED203Rec->cWSSEQ,
							 cTempBuff,
							 sizeof( pED203Rec->cWSSEQ ),
							 FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// ��������
	// �������ʂPor�������ʂQ�i�������ʂP�D��j
	if ( pKekka->knskka1[0] != '\0' && pKekka->knskka1[0] != ED203_DATA_SPACE ) {
		// �������ʂP�F�E����6����ݒ�iw�w�w�w�w�w�w�w�����A�����_�폜�j
		if ( ED203CopyFromRight( pED203Rec->cKNSKKA,
							 	pKekka->knskka1,
							 	sizeof( pED203Rec->cKNSKKA ),
							 	FALSE ) == RTN_NG ) {
			return( RTN_NG );
		}
	} else {
		// �������ʂQ
		// �������ʋ敪='0'��'*'+��2���ڂ���6���ڂ܂�
		// �ȊO��������6����ݒ�i2�o�C�g�����ɒ��ӂ���j
		if ( ED203CopyFromRight( pED203Rec->cKNSKKA,
							 	pKekka->knskka2,
							 	sizeof( pED203Rec->cKNSKKA ),
							 	TRUE ) == RTN_NG ) {
			return( RTN_NG );
		}
		if ( pKekka->knskka2kbn[0] == ED203_DATA_CHAR0 ) {
			// �������ʋ敪='0'��'*'+��2���ڂ���6���ڂ܂�
			pED203Rec->cKNSKKA[0] = ED203_DATA_ASTERISK;
		}
	}
	// ���ʃR�����g
	// �E����3����ݒ�
	if ( ED203CopyFromRight( pED203Rec->cKKACMT,
							 pKekka->kkacmt1,
							 sizeof( pED203Rec->cKKACMT ),
							 FALSE ) == RTN_NG ) {
		return( RTN_NG );
	}
	// �ُ�l�}�[�N
	// �ُ�l�敪�i�j�A���A�s���j��'4','5','6'�ȊO�ł����'*'
	if ( ( pKekka->ijkbnm != '4' && pKekka->ijkbnm != '5' && pKekka->ijkbnm != '6' ) ||
		 ( pKekka->ijkbnf != '4' && pKekka->ijkbnf != '5' && pKekka->ijkbnf != '6' ) ||
		 ( pKekka->ijkbnn != '4' && pKekka->ijkbnn != '5' && pKekka->ijkbnn != '6' ) ) {
		pED203Rec->cIJKBN = ED203_DATA_ASTERISK;
	}
	// FILLER2
	// �󔒂�ݒ�Ȃ̂ŉ������Ȃ�
	// LF
	pED203Rec->cLF = ED203_FILE_LINEFEED;

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FED203DataFileFilter()										  */
/*�@�@�\�T�v�@�F�f�B���N�g�������p�̃t�@�C���t�B���^(�R�[���o�b�N)			  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����Fstruct dirent *pDirEnt	�f�B���N�g���G���g��				  */
/*�@�o�@�@�́@�F�������ʃt�@�C��											  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		0	: �ΏۊO�t�@�C��									  */
/*�@�@�@�@�@�@		1	: �Ώۃt�@�C��										  */
/******************************************************************************/
int ED203DataFileFilter(struct dirent *pDirEnt)
{
	BmlDate		today;
	char		cToday[ED203_LEN_DATESHORT + 1];

	// �����񒷃`�F�b�N
	if ( strlen ( pDirEnt->d_name )  < ED203_LEN_FILEID ) {
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
/*�@�� �� ���@�FED203CreateFile()											  */
/*�@�@�\�T�v�@�F�񍐃f�[�^�t�@�C���쐬										  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FED203Env *pEnv		�v���O�������\����					  */
/*�@�@��Q�����FKekka *pKekkaArray	�������ʏ��							  */
/*�@�@��R�����Fint iKekkaNum		�������ʏ�񌏐�						  */
/*�@�o�@�@�́@�F															  */
/*�@�@��S�����Fint *piHkkssknsu	�쐬����								  */
/*�@�@��T�����Fint *piHkkhrysu		�ۗ�����								  */
/*�@�@��U�����Fchar *pFileName		�t�@�C����								  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int ED203CreateFile(ED203Env *pEnv,
					Kekka *pKekkaArray,
					int iKekkaNum,
					int *piHkkssknsu,
					int *piHkkhrysu,
					char *pFileName)
{
	int				iRet;
	struct dirent	**pDirEnt;
	int				iFileCnt;
	int	 			iSeqNo;
	char			cSeqBuff[10];
	BmlDate			today;
	char			cToday[ED203_LEN_DATESHORT + 1];
	char			cFileNameTemp[PATH_MAX + 1];
	char			cFileName[PATH_MAX + 1];
	FILE *			fp;
	int				iLoop;
	ED203Rec		stED203RecTemp;
	int				iKekkaLoop;
	ED203Rec		stED203Rec;

	// �����`�F�b�N
	if ( pEnv == NULL || pKekkaArray == NULL ||
		 piHkkssknsu == NULL || piHkkhrysu == NULL || pFileName == NULL ) {
		// �ُ�I��	LOG
printf("ED203CreateFile parameter is NULL\n");
		gintErrorCode = ED203_STSCODE_ERR_FR_FILE;
		return( RTN_NG );
	}

	// �f�[�^�t�@�C���p�f�B���N�g��������
	// �t�B���^�ɂ��A������YYYYMMDD9999�Ŏn�܂�t�@�C���̂݌���
	if ( ( iFileCnt = scandir( pEnv->cDirDataFile,
							   &pDirEnt,
							   (void *)ED203DataFileFilter,
							   alphasort ) ) < 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = ED203_STSCODE_ERR_DIR;
		return( RTN_NG );
	}

	// �t�@�C��SEQ���̔�
	if ( iFileCnt == 0 ) {
		iSeqNo = 1;
	} else {
		memset( cSeqBuff, 0, sizeof( cSeqBuff ) );
		strcpy( cFileName, pDirEnt[iFileCnt - 1]->d_name );
		memcpy( cSeqBuff, &cFileName[ED203_LEN_DATESHORT],
			ED203_LEN_FILESEQNO );
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
	sprintf( cFileNameTemp, "%s/%s%04d.tmp",
			 pEnv->cDirDataFile, cToday, iSeqNo );
	sprintf( cFileName, "%s/%s%04d.dat",
			 pEnv->cDirDataFile, cToday, iSeqNo );
	sprintf( pFileName, "%s%04d.dat", cToday, iSeqNo );

	// �t�@�C���I�[�v��
	fp = fopen ( cFileNameTemp, "w" );
	if ( fp == NULL ) {
		// �ُ�I��	LOG
		gintErrorCode = ED203_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	// ���ʏ����P��������
	for ( iKekkaLoop = 0;
		  iKekkaLoop < iKekkaNum;
		  iKekkaLoop++ ) {
		// �ۗ����ǂ����`�F�b�N
		if ( pKekkaArray[iKekkaLoop].knsflg == ED203_DB_KNSFLG_HORYU ) {
			++*piHkkhrysu;
			continue;
		}

		// ���ʂ��t�@�C���o�͌`���ɓW�J
		if ( ED203MakeData( &pKekkaArray[iKekkaLoop],
							&stED203Rec ) == RTN_NG ) {
			// �ُ�I��	LOG
printf("ED203MakeData error\n");
			return( RTN_NG );
		}

		// �t�@�C���o��
		iRet = fwrite( (char *)&stED203Rec, sizeof( stED203Rec ), 1, fp);
		if ( iRet != 1 ) {
			// �ُ�I��	LOG
printf("fwrite error\n");
			return( RTN_NG );
		}

		// ���ʏC���t���O���J�E���g�A�b�v�i�ő�'9'�j
		if ( pKekkaArray[iKekkaLoop].kkassflg == ED203_DATA_SPACE ) {
			pKekkaArray[iKekkaLoop].kkassflg = '0';
		} else if ( pKekkaArray[iKekkaLoop].kkassflg
					!= pKekkaArray[iKekkaLoop].kkassflg ) {
			++pKekkaArray[iKekkaLoop].kkassflg;
		}
		// �񍐓����͊֐����Őݒ�

		// �����t���O���񍐍�
		pKekkaArray[iKekkaLoop].knsflg = ED203_DB_KNSFLG_DONE;

		// ���X�V�����͊֐����Őݒ�

		// �������ʏ����X�V
		iRet = ZdbKekkaED203Update( &pKekkaArray[iKekkaLoop] );
		if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND ) {
printf("ZdbKekkaED203Update error(%d)\n", iRet);
			// ���[���o�b�N
			ZdbRollback();
			// �ُ�I��	LOG
		}
	}

	// �t�@�C���N���[�Y	
	fclose( fp );

	// �t�@�C���g���q���ύX
	iRet = rename( cFileNameTemp, cFileName );
	if ( iRet != 0 ) {
		// �ُ�I��	LOG
printf("rename status:[%d]\n", iRet);
		gintErrorCode = ED203_STSCODE_ERR_FR_FILE ;
		return( RTN_NG ) ;
	}

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FsFncShmCrt()												  */
/*�@�@�\�T�v�@�F���L����������												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FED203Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F�Ȃ�														  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
static int sFncShmCrt( ED203Env *pEnv )
{
	int	 *shmData;

	// �擾
	pEnv->shm_Id = shmget( (key_t)pEnv->shm_Key,
							ED203_SHM_SIZE,
							0666 | IPC_CREAT );
	if ( pEnv->shm_Id < 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = ED203_STSCODE_ERR_SHM_GET;
		return( RTN_NG );
	}

	// �A�^�b�`
	shmData = ( int * ) shmat( pEnv->shm_Id, 0 , 0 );
	if ( shmData == ( int * )-1 ) {
		// �ُ�I��	LOG
		gintErrorCode = ED203_STSCODE_ERR_SHM_AT;
		return( RTN_NG );
	}
loging ( "stocker : ���L������[CRT] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n",
		 pEnv->shm_Key, pEnv->shm_Id, *shmData, shmData );

	// �l�ݒ�
	*shmData = 0;

	// �f�^�b�`
	if ( shmdt( shmData ) == -1 ) {
		// �ُ�I��	LOG
		gintErrorCode = ED203_STSCODE_ERR_SHM_DT;
		return( RTN_NG );
	}

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FsFncShmGet()												  */
/*�@�@�\�T�v�@�F���L�������擾												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FED203Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@�@��Q�����Fint *pshmData		�l										  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
static int sFncShmGet( ED203Env *pEnv, int *pshmData )
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
		gintErrorCode = ED203_STSCODE_ERR_SHM_AT;
		return( RTN_NG );
	}

	// �l�ݒ�
	*pshmData = *shmData;

loging ( "stocker : ���L������[GET] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n",
		 pEnv->shm_Key, pEnv->shm_Id, *shmData, shmData );
	// �f�^�b�`
	if ( shmdt( shmData ) == -1 ) {
		// �ُ�I��	LOG
		gintErrorCode = ED203_STSCODE_ERR_SHM_DT;
		return( RTN_NG );
	}

	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�FsFncShmDel()												  */
/*�@�@�\�T�v�@�F���L�������폜												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FED203Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
static int sFncShmDel( ED203Env *pEnv )
{
	int	 *shmData;

loging ( "%s : ���L������[DEL] shmKey[%d]-ID[%d]\n",
		 MYAPP_APP_NAME, pEnv->shm_Key, pEnv->shm_Id);
	// �폜
	if ( shmctl( pEnv->shm_Id, IPC_RMID, NULL) < 0 ) {
		// �ُ�I��	LOG
		gintErrorCode = ED203_STSCODE_ERR_SHM_DEL;
		return( RTN_NG );
	}
	return( RTN_OK );
}

/******************************************************************************/
/*�@�� �� ���@�F_sFncEnvDip()												  */
/*�@�@�\�T�v�@�F�v���O�������ϐ��o�͊֐��y�g���[�X�p�z					  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FED203Env *pEnv		�v���O�������\����					  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�F����														  */
/******************************************************************************/
static void _sFncEnvDip( ED203Env *pEnv )
{
//#if defined ( _TRACE )
	loging( "########## ED203 - _sFncEnvDip ##########\n" );
	loging( "\t%s : [%s]\n", ED203_PRM_DBNAME,		 pEnv->cDBName );
	loging( "\t%s : [%s]\n", ED203_PRM_DBUSER,		 pEnv->cDBUser );
	loging( "\t%s : [%s]\n", ED203_PRM_DBPAWD,		 pEnv->cDBPawd );
	loging( "\t%s : [%s]\n", ED203_PRM_DIR_DATAFILE,   pEnv->cDirDataFile );
	loging( "\t%s : [%s]\n", ED203_PRM_SLEEP_SEC,	  pEnv->iSleepSec );
	loging( "\t%s : [%s]\n", ED203_PRM_SHM_KEY,	pEnv->shm_Key );
	loging( "\t%s : [%s]\n", ED203_PRM_FILE_DBG,	pEnv->cDebugLogName );
	loging( "\t%s : [%s]\n", ED203_PRM_FILE_TR,	pEnv->cTraceLogName );
	loging( "\t%s : [%s]\n", ED203_PRM_FILE_ACS,	pEnv->cAccessLogName );
	loging( "\t%s : [%s]\n", ED203_PRM_FILE_ERR,	pEnv->cErrorLogName );
	loging( "\t%s : [%s]\n", ED203_PRM_UP_ID,		pEnv->cUpdateId );
	loging( "\t%s : [%s]\n", ED203_PRM_UP_NM,		pEnv->cUpdateName );
	loging( "\t%s : [%s]\n", ED203_PRM_PROC_MD,	pEnv->proc_mode );
	loging( "########## ED203 - _sFncEnvDip ##########\n" );
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
	ED203Env	stEnv;

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


