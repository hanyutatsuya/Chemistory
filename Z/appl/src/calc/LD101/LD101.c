/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FLD101.c                                                      */
/* �@�T�@�@�@�v�F                                                             */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2019/12/15     BML.inc        �V�K�쐬                           */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <dirent.h>
#include <fcntl.h>
#include <time.h>
#include <ctype.h>
#include <stdarg.h>
#include <unistd.h>

#include "bmllog.h"
#include "bmlprm.h"
#include "bml_misc.h"
#include "bml_date.h"
#include "bml_DBCom.h"

#include "sql.h"

#include "LD101.h"

/******************************************************************************/
/* Define��`                                                                 */
/******************************************************************************/
//	TRACE
#if defined ( _TRACE )
#define malloc(a)   _malloc(a, __FILE__, __LINE__)
#define free(p)     _free(p, __FILE__, __LINE__)
#endif

/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/
struct stcLogMember	 gstLogMem ;		//	���O�o�͏��

/******************************************************************************/
/* �֐��錾                                                                   */
/******************************************************************************/
//	�t�@�C���E�f�[�^�x�[�X�o�͊֐�
static	int 	sFncGetFileName ( char * ) ;
static	int 	sFncOutHKHRIRAI ( FILE *, my_stCHKZOK ) ;

//      ���L����������֐�
static	int	sFncShmCrt() ;
static	int	sFncShmGet( int *) ;
static	int	sFncShmDel() ;


//	���̑�
int	ChkErrZok( my_stCHKZOK * ) ;
int	isCorrectChar( char * ) ;
void	sFncTrim( char *, char * );
static void	sFncGetdate( char *, char *, int ) ;
static void	endFunction();


/******************************************************************************/
/*  �� �� ���@�FinitFunction()												  */
/*  �@�\�T�v�@�F���������֐�												  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct	env *   	�v���O�������\���́B		 			  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F  0     : ����												  */
/* �@�@�@�@�@�@�@-1     : ���s												  */
/******************************************************************************/
int
initFunction( argc, argv )
int	 argc ;
char	*argv[] ;
{
	char	 lc_prmBuf[256] ;
	long	 ll_retSts ;
	char	*lc_login ;

	/***
	 ***	�����`�F�b�N	
	 ***/
	if ( argc != 2 ) {
		fprintf ( stderr, "%s : There is an error in a command parameter\n", MYAPP_APP_NAME ) ;
		return ( -1 ) ;
	}

	/*	���O�I�[�v�� */
	if ( ZbmlOpenLog ( argv[1] ) != 0 ) {
		fprintf ( stderr, "ZbmlOpenLog NOT OPEN(%s)\n",argv[1]); 
		return ( -1 ) ;
	}

	//	���O��񏉊��ݒ�
	memset ( &gstLogMem, '\0', sizeof ( gstLogMem ) ) ;
	if ( ( lc_login = getenv( "LOGNAME" ) ) != NULL ) {
		strcpy ( gstLogMem.pcLoginId, lc_login ) ;
	}
	strcpy ( gstLogMem.pcAppName, MYAPP_APP_NAME ) ;

	//	�J�n���O�o��
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�v���O�����N��" ) ;

	/*	������	*/

	//	�v���O�������ϐ�������
	memset ( &pAppEnv , '\0', sizeof( pAppEnv ) ) ;

	//	�p�����[�^�t�@�C�����ޔ�
	pAppEnv.pcFielNamePRM = argv[1] ;

	//	�p�����[�^�t�@�C���I�[�v��	
	pAppEnv.bp = ZbmlPrmOpen ( pAppEnv.pcFielNamePRM ) ;		
	if ( pAppEnv.bp == NULL ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmOpen", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^�t�@�C���̃I�[�v���Ɏ��s���܂���[%s]", pAppEnv.pcFielNamePRM ) ;
		return ( -1 ) ;
	}
	//	���L�������L�[�擾
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_SHM_KEY, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_SHM_KEY ) ;
		return ( -1 ) ;
	}
	pAppEnv.shm_Key = atoi ( lc_prmBuf ) ;
	//	�f�[�^�x�[�X��
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DB_NAME, pAppEnv.cDb_Name ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DB_NAME ) ;
		return ( -1 ) ;
	}
	//	�f�[�^�x�[�X���[�U
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DB_USER, pAppEnv.cDb_User ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DB_USER ) ;
		return ( -1 ) ;
	}
	//	�f�[�^�x�[�X�p�X���[�h
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DB_PASSWD, pAppEnv.cDb_Passwd ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DB_PASSWD ) ;
		return ( -1 ) ;
	}
	//	�t�@�C���o�̓f�B���N�g��
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_OUTPUT_DIR, pAppEnv.cOutputDir ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_OUTPUT_DIR ) ;
		return ( -1 ) ;
	}
	//	�o�̓t�@�C����
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_OUTPUT_FILE, pAppEnv.cOutputFile ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_OUTPUT_FILE ) ;
		return ( -1 ) ;
	}
	//	�e�s�o���M�p�V�F����
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_SEND_SHELL, pAppEnv.cSendShell ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_SEND_SHELL ) ;
		return ( -1 ) ;
	}
	//	�X�^�[�g�g���K�[�t�@�C��
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_TRG_FILE, pAppEnv.cTrgFile ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_TRG_FILE ) ;
		return ( -1 ) ;
	}
	//	�N��x������擾
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_AGE_HI, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_AGE_HI ) ;
		return ( -1 ) ;
	}
	pAppEnv.AgeHi= atoi ( lc_prmBuf ) ;
	//	�N��x�������擾
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_AGE_LOW, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_AGE_LOW ) ;
		return ( -1 ) ;
	}
	pAppEnv.AgeLow= atoi ( lc_prmBuf ) ;
	//	�g���x������擾
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_SC_HI, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_SC_HI ) ;
		return ( -1 ) ;
	}
	pAppEnv.ScHi= atof ( lc_prmBuf ) ;
	//	�g���x�������擾
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_SC_LOW, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_SC_LOW ) ;
		return ( -1 ) ;
	}
	pAppEnv.ScLow= atof ( lc_prmBuf ) ;
	//	�̏d�x������擾
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_TJ_HI, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_TJ_HI ) ;
		return ( -1 ) ;
	}
	pAppEnv.TjHi= atof ( lc_prmBuf ) ;
	//	�̏d�x�������擾
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_TJ_LOW, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_TJ_LOW ) ;
		return ( -1 ) ;
	}
	pAppEnv.TjLow= atof ( lc_prmBuf ) ;
	//	SLEEPSEC�擾
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_SLEEP_SEC, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_SLEEP_SEC ) ;
		return ( -1 ) ;
	}
	pAppEnv.sleep_Sec= atoi ( lc_prmBuf ) ;
	//	�������t�̎擾
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DATE_RANGE, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DATE_RANGE ) ;
		return ( -1 ) ;
	}
	pAppEnv.DateRange= atoi ( lc_prmBuf ) ;

	//	�p�����[�^�t�@�C���N���[�Y	
	ZbmlPrmClose ( pAppEnv.bp ) ;

	/***
	 ***	���L����������	
	 ***/
	if ( sFncShmCrt ( ) < 0 ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "���L�������G���[") ;
		return ( -1 ) ;
	}

	/***
	 ***	�f�[�^�x�[�X�I�[�v��
	 ***/
	ll_retSts = ZdbConnect( pAppEnv.cDb_Name, pAppEnv.cDb_User, pAppEnv.cDb_Passwd ) ;
	if ( ll_retSts != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZdbConnect", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "�f�[�^�x�[�X�I�[�v���Ɏ��s���܂���[DB=%s USER=%s PASS=%s]", pAppEnv.cDb_Name, pAppEnv.cDb_User, pAppEnv.cDb_Passwd ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ; 
}
/********************************************************************************/
/*  �� �� ���@�FmainFunction()							*/
/*  �@�\�T�v�@�F���C�������֐�							*/
/*  ���@�@�́@�F								*/
/*�@ ��P���� �Fstruct	env *   	�v���O�������\���́B			*/
/*  �o�@�@�́@�F								*/
/*  ���A���@�F  0     : ����							*/
/* �@�@�@�@�@�@�@-1     : ���s							*/
/********************************************************************************/
int
mainFunction()
{
	int	 li_stopFlg = 0;

	int	 i = 0;
	int	 chk_cnt = 0;
	int	 chk_err = 0;
	char	 serch_date[11];
	FILE	*lfp ;
	char	 sFileName[MYAPP_PATH_SIZE] ;
	char	cmd[MYAPP_PATH_SIZE];

	struct stat st;

	my_stSYSKNR pSysKnr; 	//
	my_stCHKZOK *pChkZok;	// �����`�F�b�N���

	/***
	 ***		�i�v���[�v
	 ***		��~�R�}���h�ŏI��
	 ***/
	while ( 1 ) {
		/* �X���[�v */
		sleep ( pAppEnv.sleep_Sec ) ;

		/* ��~�R�}���h�m�F */
		if ( sFncShmGet ( &li_stopFlg ) != 0 ) {
			return( RTN_NG );
		}
		if ( li_stopFlg == 1 ) {
			return( RTN_OK );
		}
		/* LD103 ���g���K�[�t�@�C�����쐬����܂őҋ@ */
		if ( stat( pAppEnv.cTrgFile, &st ) != 0 ){
			continue ;
		}
		/* �V�X�e���Ǘ��}�X�^�擾 */
		if ( sFncSelSysKnr( &pSysKnr ) !=  RTN_OK ){
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
	 		 		"�V�X�e���Ǘ����̎擾�Ɏ��s���܂���");
			return( RTN_NG );
		}

		chk_cnt = 0;
		chk_err = 0;
		pChkZok = NULL;
		lfp = NULL ;

		sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "�������J�n���܂����B" ) ;
		/* �����͈͂��擾 */
		sFncGetdate( serch_date, pSysKnr.kjnsriymd, pAppEnv.DateRange );
		/* �t�@�C�����擾 */
		if (sFncGetFileName ( sFileName ) != RTN_OK ) {
			return ( RTN_NG ) ;
		}
		/* �Ώی����Ɋւ�炸�A�t�@�C���͍쐬���� */
		lfp = fopen ( sFileName , "w" ) ;
		if ( lfp == NULL ) {
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "fopen", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
	 		 		"�t�@�C���̃I�[�v���Ɏ��s���܂���[%s]", sFileName);
			return ( RTN_NG ) ;
		}

		sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "���M�p�t�@�C�����I�[�v�����܂����B[%s]", sFileName ) ;

		/* �����G���[�`�F�b�N�p���擾���� */
		if( sFncSelChkZok( serch_date, &pChkZok, &chk_cnt ) !=  RTN_OK ){
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
	 		 		"�f�[�^�擾�Ɏ��s���܂���");
			if ( lfp != NULL ) {
				fclose ( lfp ) ;
			}
			if ( pChkZok!= NULL ) {
				ZbmlFree( pChkZok );
			}
			return( RTN_NG );
		}

		sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "�������̎擾�������B�����`�F�b�N�����J�n�B" ) ;

		for ( i = 0; i < chk_cnt; i++ ){
			/* �����G���[�`�F�b�N */
			if( ChkErrZok( &pChkZok[i] ) != RTN_OK ){
				/* �c�a�X�V */
				if ( InsHkHrIrai( &pChkZok[i] ) != RTN_OK ){
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
	 		 			     "�c�a�X�V�Ɏ��s���܂���[%s:%d����]", sFileName, i);
					if ( lfp != NULL ) {
						fclose ( lfp ) ;
					}
					if ( pChkZok!= NULL ) {
						ZbmlFree( pChkZok );
					}
					return( RTN_NG );
				}
			
					/* �t�@�C�����R�[�h�o�� */
				if ( sFncOutHKHRIRAI ( lfp, pChkZok[i] ) != RTN_OK ){
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
	 		 			     "�t�@�C���o�͂Ɏ��s���܂���[%s:%d����]", sFileName, i);
					if ( lfp != NULL ) {
						fclose ( lfp ) ;
					}
					if ( pChkZok!= NULL ) {
						ZbmlFree( pChkZok );
					}
					return( RTN_NG );
				}
				chk_err++;
			}
		}

		sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "�����`�F�b�N���������B[�����F%d��,�G���[�����F%d��]", chk_cnt, chk_err ) ;

		if ( lfp != NULL ) {
			fclose ( lfp ) ;
		}
		if ( pChkZok!= NULL ) {
			ZbmlFree( pChkZok );
		}
		break;
	}

	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                             "FTP �R�}���h���J�n���܂��B");

	// FTP�R�}���h�p�V�F���̎��s
	sprintf( cmd, "sh %s", pAppEnv.cSendShell );
	system( cmd );

	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                             "FTP �R�}���h���I�����܂����B");

	return ( RTN_OK ) ;
}
/******************************************************************************/
/*  �� �� ��  �FChkErrZok							*/
/*  �@�\�T�v  �F�����G���[�`�F�b�N�֐�						*/
/*  ��    ��  �F								*/
/*   ��P���� �Fstruct my_stCHKZOK  *pChkZok    : �����`�F�b�N���		*/
/*  �o    ��  �F�Ȃ�								*/
/*  ���A���  �FINT								*/
/*		RTN_OK     : ����						*/
/*		RTN_NG     : ���s						*/
/******************************************************************************/
int	ChkErrZok( pChkZok )
my_stCHKZOK	*pChkZok ;
{
	
	int	ret = RTN_OK;
	double	tmpNumDbl = 0.0;
	int	tmpNumInt = 0;

	if( strcmp( pChkZok->scflg, MYAPP_ZOK_CHK ) == 0 ){
		if( isCorrectChar( pChkZok->sc ) != RTN_OK || !strcmp(pChkZok->sc, "     ") ) {
			strcpy( pChkZok->scflg, MYAPP_ZOK_ERR );
			ret = RTN_NG;
		} else {
			tmpNumDbl = atof( pChkZok->sc );
			if( tmpNumDbl > pAppEnv.ScHi || tmpNumDbl < pAppEnv.ScLow ) {
				strcpy( pChkZok->scflg, MYAPP_ZOK_NG );
				ret = RTN_NG;
			}
		}
	}

	if( strcmp( pChkZok->tjflg, MYAPP_ZOK_CHK ) == 0 ){
		if( isCorrectChar( pChkZok->tj ) != RTN_OK || !strcmp(pChkZok->tj, "     ") ) {
			strcpy( pChkZok->tjflg, MYAPP_ZOK_ERR );
			ret = RTN_NG;
		} else {
			tmpNumDbl = atof( pChkZok->tj );
			if ( tmpNumDbl > pAppEnv.TjHi || tmpNumDbl < pAppEnv.TjLow ) {
				strcpy( pChkZok->tjflg, MYAPP_ZOK_NG );
				ret = RTN_NG;
			}
		}
	}

	if( strcmp( pChkZok->tjtniflg, MYAPP_ZOK_CHK ) == 0 ){
		if( strcmp( pChkZok->tjtni, "0" ) != 0 ) {
			strcpy( pChkZok->tjtniflg, MYAPP_ZOK_NG );
			ret = RTN_NG;
		}
	}

	if( strcmp( pChkZok->sbtkbnflg, MYAPP_ZOK_CHK ) == 0 ){
		if( strcmp( pChkZok->sbtkbn, "0" ) != 0 && strcmp( pChkZok->sbtkbn , "1" ) != 0 ) {
			strcpy(pChkZok->sbtkbnflg, MYAPP_ZOK_ERR );
			ret = RTN_NG;
		}
	}

	if( strcmp( pChkZok->ageflg, MYAPP_ZOK_CHK ) == 0 ){
		if( isCorrectChar( pChkZok->age ) != RTN_OK || !strcmp( pChkZok->age , "   ") ) {
			strcpy( pChkZok->ageflg, MYAPP_ZOK_ERR );
			ret = RTN_NG;
		} else {
			tmpNumInt = atoi( pChkZok->age );
			if( tmpNumInt > pAppEnv.AgeHi || tmpNumInt < pAppEnv.AgeLow ) {
				strcpy( pChkZok->ageflg, MYAPP_ZOK_NG );
				ret = RTN_NG;
			}
		}
	}

	if( strcmp( pChkZok->agekbnflg, MYAPP_ZOK_CHK ) == 0 ){
		if( strcmp( pChkZok->agekbn , "Y" ) != 0 ){
			strcpy(pChkZok->agekbnflg, MYAPP_ZOK_NG );
			ret=RTN_NG;
		}
	}
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "ChkErrZok", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "utkymd[%s] irino[%s] kmkcd[%s] sc[%s] tj[%s] tjtni[%s] sbtkbn[%s] age[%s] agekbn[%s] ret[%d]", 
			pChkZok->utkymd, pChkZok->irino, pChkZok->kmkcd, pChkZok->sc, pChkZok->tj, pChkZok->tjtni, pChkZok->sbtkbn, pChkZok->age, pChkZok->agekbn, ret ) ;
	return(ret);
}

/**************************************************************************/
/*      �� �� ��  �FisCorrectChar                                         */
/*      �@�\�T�v  �F���ґ������l�G���A�`�F�b�N                            */
/*      ��        ��  �F                                                  */
/*       ��P���� �F char       In[];   : �`�F�b�N������                  */
/*      �o        ��  �F                                                  */
/*      ���A���  �F RTN_OK             : ����I��                        */
/*                               �ȊO   : ���s                            */
/**************************************************************************/
int isCorrectChar(char *In)
{
	int	ret = RTN_OK;

	int	i = 0;
	int	nSuziFlg =0; /*���߂��������Ƃ������� */

	/* ��������     */
	int nMaxNum = strlen(In);
	char    buf[nMaxNum + 1];
	memset( buf,    '\0', sizeof( buf ));

	sFncTrim( buf, In );
	nMaxNum = strlen(buf);

	for( i = 0 ; i < nMaxNum ; i++ ) {
		if(In[i] == ' '){
			if(nSuziFlg == 1){
				// DEBUG
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "���l ��������SPACE[%s]", In );
				// ERROR
				ret=RTN_NG;
				break;
			}
		}
		else if(In[i] == '.'){
			if(i==0){
				// DEBUG
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "���l �擪.�s��[%s]", In );
				// ERROR
				ret=RTN_NG;
				break;
			}
			if(nSuziFlg == 0){
				// DEBUG
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "���l �擪.�s��[%s]" , In );
				// ERROR
				ret=RTN_NG;
				break;
			}
		}
		else if(In[i] >= '0' && In[i] <= '9'){
			nSuziFlg = 1;
		}
		else{
			// DEBUG
			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "���l ��.�ȊO�s��[%s]" , In );
			// ERROR
			ret=RTN_NG;
			break;
		}
	}

	if(i == nMaxNum){
		ret=RTN_OK;
	}

	return( ret );
}


/********************************************************************************/
/*  �� �� ���@�FsFncFileOut()				 			*/
/*  �@�\�T�v�@�F�`�F�b�N���t�@�C���o��		 			*/
/*  ���@�@�́@�F                                                                */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����			*/
/*�@ ��Q���� �FKenorder  *   		�����I�[�_�[�����\����		*/
/*  �o�@�@�́@�F                                                                */
/*  ���A���@�Fint								*/
/*		 0	����							*/
/*		-1	�ُ�							*/
/********************************************************************************/
static int
sFncGetFileName ( sFileName )
char	*sFileName ;
{
	/* �����t�@�C�����l�[���p */
	char	lc_FileName[MYAPP_PATH_SIZE] ;
	struct	stat st;

	/*	�t�@�C�����쐬	*/
	sprintf ( sFileName, "%s/%s", pAppEnv.cOutputDir, pAppEnv.cOutputFile );

	/* �����t�@�C��������ꍇ�̓��l�[�����Ă��� */
	if ( stat( sFileName, &st ) == 0 ){
		sprintf ( lc_FileName, "%s", sFileName );
		for( ;; ){
			strcat( lc_FileName, "_" );
			if( open( lc_FileName, O_RDONLY, 0 ) == EOF ){
				break;
			}
		}
		rename( sFileName, lc_FileName );
	}

	return ( 0 ) ;
}
/******************************************************************************/
/*  �� �� ���@�FsFncOutHKHRIRAI()		 				*/
/*  �@�\�T�v�@�����`�F�b�N�G���[��񃌃R�[�h����				*/
/*  ���@�@�́@�F                                                              */
/*�@ ��Q���� �Fstruct my_stCHKZOK *   	�����I�[�_���\����			*/
/*  �o�@�@�́@�F                                                              */
/*�@ ��P���� �Fchar 	*  	���R�[�h�i�[�o�b�t�@				*/
/*  ���A���@�F����								*/
/******************************************************************************/
static	int
sFncOutHKHRIRAI ( pfp, precChkZok )
FILE	*pfp ;
my_stCHKZOK	precChkZok ;
{
	int	retSts ;
	char	ngKbn[6+1];
	char	cnv_utkymd[10+1];
	char	cnv_irino[8+1];
	char	cnv_sbt[2+1];
	char	cnv_age[3+1];
	char	cnv_agekbn[4+1];
	char	cnv_sc[5+1];
	char	cnv_tj[5+1];
	char	cnv_tjtni[2+1];
	char	sbtchk, agechk, scchk, tjchk;

	// �m�f�敪������
	sprintf( ngKbn, "%s%s%s", MYAPP_SPACE_FULL, MYAPP_SPACE_FULL, MYAPP_SPACE_FULL );

	sprintf( cnv_utkymd, "%.4s/%.2s/%.2s" , precChkZok.utkymd, &precChkZok.utkymd[5], &precChkZok.utkymd[8] );
	sprintf( cnv_irino, "%-3.3s-%-4.4s" , &precChkZok.irino[2], &precChkZok.irino[5] );

	// ����
	if(strcmp( precChkZok.sbtkbnflg, MYAPP_ZOK_NOT_CHK ) == 0 ){
		sprintf( cnv_sbt, "%s", MYAPP_HYPHEN_FULL );
		sbtchk = MYAPP_SPACE_HALF;
	} else {
		// ���ʋ敪 -> ���ʋ敪����
		if(strcmp(precChkZok.sbtkbn ,MYAPP_SBTKBN_MALE) == 0 ){ 
			sprintf( cnv_sbt, "%s", MYAPP_MARK_MALE );
		} else if(strcmp(precChkZok.sbtkbn ,MYAPP_SBTKBN_FEMALE) == 0 ){
			sprintf( cnv_sbt, "%s", MYAPP_MARK_FEMALE );
		} else {
			sprintf( cnv_sbt, "%s", MYAPP_SPACE_FULL );
		} 
		// ���ʋ敪���̓`�F�b�N
		if(strcmp(precChkZok.sbtkbnflg ,MYAPP_ZOK_NG) == 0 ){ 
			sbtchk = MYAPP_MARK_NG;
			sprintf( ngKbn, "%s", MYAPP_MARK_KBN_NG );
		} else if(strcmp(precChkZok.sbtkbnflg ,MYAPP_ZOK_ERR) == 0 ){ 
			sbtchk = MYAPP_MARK_ERR;
			sprintf( ngKbn, "%s", MYAPP_MARK_KBN_ERR );
		} else { 
			sbtchk = MYAPP_SPACE_HALF;
		}
	}
	// �N��{�N��敪
	if((strcmp( precChkZok.ageflg, MYAPP_ZOK_NOT_CHK ) == 0 ) && ( strcmp( precChkZok.agekbnflg, MYAPP_ZOK_NOT_CHK ) == 0 )){
		sprintf( cnv_age, "%c  ", MYAPP_HYPHEN_HALF );
		sprintf( cnv_agekbn, "%s%s", MYAPP_SPACE_FULL, MYAPP_SPACE_FULL );
		agechk = MYAPP_SPACE_HALF;
	} else {
		// �N��
		sprintf( cnv_age, "%-3.3s", precChkZok.age );
		// �N��敪
		if(strcmp(precChkZok.agekbn ,MYAPP_AGEKBN_YEAR) == 0 ){ 
			sprintf( cnv_agekbn, "%-4.4s", MYAPP_MARK_YEAR );
		} else if(strcmp(precChkZok.agekbn ,MYAPP_AGEKBN_MONTH) == 0 ){ 
			sprintf( cnv_agekbn, "%-4.4s", MYAPP_MARK_MONTH );
		} else if(strcmp(precChkZok.agekbn ,MYAPP_AGEKBN_WEEK) == 0 ){ 
			sprintf( cnv_agekbn, "%-4.4s", MYAPP_MARK_WEEK );
		} else if(strcmp(precChkZok.agekbn ,MYAPP_AGEKBN_DAY) == 0 ){ 
			sprintf( cnv_agekbn, "%-4.4s", MYAPP_MARK_DAY );
		} else { 
			sprintf( cnv_agekbn, "%s%s", MYAPP_SPACE_FULL, MYAPP_SPACE_FULL );
		}
		// �N����̓`�F�b�N
		if((strcmp( precChkZok.ageflg, MYAPP_ZOK_NG ) == 0 ) || ( strcmp( precChkZok.agekbnflg, MYAPP_ZOK_NG ) == 0 )){
			agechk = MYAPP_MARK_NG;
			sprintf( ngKbn, "%s", MYAPP_MARK_KBN_NG );
		} else if((strcmp( precChkZok.ageflg, MYAPP_ZOK_ERR ) == 0 ) || ( strcmp( precChkZok.agekbnflg, MYAPP_ZOK_ERR ) == 0 )){
			agechk = MYAPP_MARK_ERR ;
			if( strcmp( ngKbn, MYAPP_MARK_KBN_NG ) != 0 ) {
				/* �����͂ƈُ�̏ꍇ�A�ُ��D�� */
				sprintf( ngKbn, "%s", MYAPP_MARK_KBN_ERR );
			}
		} else {
			agechk = MYAPP_SPACE_HALF;
		}
	}
	// �g��
	if(strcmp( precChkZok.scflg, MYAPP_ZOK_NOT_CHK ) == 0 ){
		sprintf( cnv_sc, "%c    ", MYAPP_HYPHEN_HALF ) ;
		scchk = MYAPP_SPACE_HALF;
	} else {
		// �g��
		sprintf( cnv_sc, "%-5.5s", precChkZok.sc ) ;
		// �g�����̓`�F�b�N
		if(strcmp( precChkZok.scflg, MYAPP_ZOK_NG ) == 0 ){
			scchk = MYAPP_MARK_NG;
			sprintf( ngKbn, "%s", MYAPP_MARK_KBN_NG );
		} else if(strcmp( precChkZok.scflg, MYAPP_ZOK_ERR ) == 0 ){
			scchk = MYAPP_MARK_ERR;
			if( strcmp( ngKbn, MYAPP_MARK_KBN_NG ) != 0 ) {
				sprintf( ngKbn, "%s", MYAPP_MARK_KBN_ERR );
			}
		} else {
			scchk = MYAPP_SPACE_HALF;
		}
	}
	// �̏d
	if((strcmp( precChkZok.tjflg, MYAPP_ZOK_NOT_CHK ) == 0 ) && ( strcmp( precChkZok.tjtniflg, MYAPP_ZOK_NOT_CHK ) == 0 )){
		tjchk = MYAPP_SPACE_HALF;
		sprintf( cnv_tj, "%c  %c", MYAPP_HYPHEN_HALF, tjchk ) ;
	} else {
		// �̏d
		sprintf( cnv_tj, "%-5.5s", precChkZok.tj) ;
		// �̏d�P��
		if(strcmp(precChkZok.tjtni ,MYAPP_TJTNI_KGRAM ) == 0 ){ 
			sprintf( cnv_tjtni, "%-2.2s", MYAPP_MARK_KGRAM ) ;
		} else if(strcmp(precChkZok.tjtni ,MYAPP_TJTNI_GRAM ) == 0 ){ 
			sprintf( cnv_tjtni, "%-2.2s", MYAPP_MARK_GRAM ) ;
		} else {
			sprintf( cnv_tjtni, "%c%c", MYAPP_SPACE_HALF, MYAPP_SPACE_HALF ) ;
		}
		// �̏d���̓`�F�b�N
		if((strcmp( precChkZok.tjflg, MYAPP_ZOK_NG ) == 0 ) || ( strcmp( precChkZok.tjtniflg, MYAPP_ZOK_NG ) == 0 )){
			tjchk = MYAPP_MARK_NG;
			sprintf( ngKbn, "%s", MYAPP_MARK_KBN_NG );
		} else if((strcmp( precChkZok.tjflg, MYAPP_ZOK_ERR ) == 0 ) || ( strcmp( precChkZok.tjtniflg, MYAPP_ZOK_ERR ) == 0 )){
			tjchk = MYAPP_MARK_ERR;
			if( strcmp( ngKbn, MYAPP_MARK_KBN_NG ) != 0 ) {
				sprintf( ngKbn, "%s", MYAPP_MARK_KBN_ERR );
			}
		} else {
			tjchk = MYAPP_SPACE_HALF;
		}
	}

	//	���R�[�h�쐬
	retSts = fprintf ( pfp, "\"%s\",\"%-7s\",\"%-40s\",\"%-10s\",\"%-8s\",\"%-20.20s\",\"%-15.15s\",\"%-7.7s\",\"%-24.24s\",\"%-2.2s\",\"%c\",\"%-3.3s\",\"%-4.4s\",\"%c\",\"%-5.5s\",\"%c\",\"%-5.5s\",\"%-2.2s\",\"%c\"\r\n",
				ngKbn,	
				precChkZok.sstcd,
				precChkZok.sstssnmj,
				cnv_utkymd,
				cnv_irino,
				precChkZok.knjnmn,
				precChkZok.krtno,
				precChkZok.kmkcd,
				precChkZok.kmknmj,
				cnv_sbt,
				sbtchk,
				cnv_age,
				cnv_agekbn,
				agechk,
				cnv_sc,
				scchk,
				cnv_tj,
				cnv_tjtni,
				tjchk ) ;
	if ( retSts < 0 ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOutHKHRIRAI", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "fprintf ���s" ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncGetdate()							*/
/*  �@�\�T�v�@�F���t���Z�֐�							*/
/*  ���@�@�́@�F                                                              */
/*�@ ��Q���� �Fchar *	����t������( yyyy-mm-dd )				*/
/*�@ ��R���� �Fint	��������(���ʂɎw�肷��Ɖ�����B�|�w��ŉ����O�ƂȂ�)	*/
/*  �o�@�@�́@�F      	                                                      */
/*�@ ��P���� �Fchar *	�擾���t������( yyyy-mm-dd )				*/
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

/********************************************************************************/
/*  �� �� ��  �FsFncTrim                                                        */
/*  �@�\�T�v  �F�w�蕶����̑O��̃X�y�[�X����菜���ĕ�������R�s�[����        */
/*  ��    ��  �F                                                                */
/*   ��Q���� �Fchar * �ϊ���������                                             */
/*  �o    ��  �F                                                                */
/*   ��P���� �Fchar * �ϊ��㕶����                                             */
/********************************************************************************/
void sFncTrim(char * dst, char *src) {
	int dstCnt;
	int srcCnt;
	int Flg;

	for(dstCnt = 0, srcCnt = 0, Flg = 0; src[srcCnt] != '\0'; srcCnt ++) {
		if ((dstCnt == 0) && (src[srcCnt] == '\x20')) {
			continue;
		}
		dst[dstCnt++] = src[srcCnt];
		if (src[srcCnt] != '\x20') {
			Flg = dstCnt;
		}
	}
	dst[Flg] = '\0';
}

/******************************************************************************/
/*  �� �� ���@�FendFunction()							*/
/*  �@�\�T�v�@�F�I�������֐�							*/
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct	env *   	�v���O�������\���́B		 	*/
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F  0     : ����							*/
/* �@�@�@�@�@�@�@-1     : ���s							*/
/******************************************************************************/
void
endFunction()
{
	/*	�f�[�^�x�[�X�N���[�Y */
	ZdbDisConnect() ;

	/*	���L�������폜	*/
	sFncShmDel() ;

	/*	�I�����O�o�� */
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�v���O�����I��" ) ;
	/*	���O�N���[�Y */
	ZbmlCloseLog() ;
	
	return ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncPutLog()  			 				*/
/*  �@�\�T�v�@�F�A�v���P�[�V�������O�o��					*/
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *   	�ҏW������					*/
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F����								*/
/******************************************************************************/
void
sFncPutLog ( LOG_TRCKIND peTrcKind, char * pcSrcName, char * pcFncName, int plLineNo, char * pcExeFlg, char * pcErrCode, char * pcfmt, ... ) 
{
	va_list	 ap ;

	/***
	 ***	���O�����l�ݒ�
	 ***/
	gstLogMem.eTrcKind = peTrcKind ;
	strcpy ( gstLogMem.pcFncName, pcFncName ) ;
	strcpy ( gstLogMem.pcExeFlg,  pcExeFlg ) ;
	strcpy ( gstLogMem.pcErrCode, pcErrCode ) ;
	va_start ( ap, pcfmt ) ;
	vsprintf ( gstLogMem.pcMsg, pcfmt, ap ) ;
	va_end ( ap ) ;

	/***
	 ***	���O�o��
	 ***/
	_ZbmlPutLog ( &gstLogMem, pcSrcName, plLineNo) ;
	return ;
	
}
/********************************************************************************/
/*  �� �� ���@�FsFncShmCrt()							*/
/*  �@�\�T�v�@�F���L����������							*/
/*  ���@�@�́@�F                                                                */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����			*/
/*  �o�@�@�́@�F                                                                */
/*  ���A���@�Fint								*/
/*		 0	����							*/
/*		-1	�ُ�							*/
/********************************************************************************/
static int
sFncShmCrt()
{
	int		*shmData ;

	//	�擾
	pAppEnv.shm_Id = shmget ( (key_t)pAppEnv.shm_Key, 
							MYAPP_SHM_SIZE, 
							0666 | IPC_CREAT ) ;
	if ( pAppEnv.shm_Id < 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmget", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "���L�������̑���Ɏ��s���܂���" ) ;
		return ( -1 ) ;
	}

	//	�A�^�b�`	
	shmData = ( int * ) shmat ( pAppEnv.shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmat", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "���L�������̑���Ɏ��s���܂���" ) ;
		return ( -1 ) ;
	}

	//	�l�ݒ�	
	*shmData = 0 ;

	//	�f�^�b�`	
	if ( shmdt ( shmData ) == -1 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "���L�������̑���Ɏ��s���܂���" ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/********************************************************************************/
/*  �� �� ���@�FsFncShmGet()							*/
/*  �@�\�T�v�@�F���L�������擾							*/
/*  ���@�@�́@�F                                                                */
/*�@ ��P���� �Fstruct appEnv *	�v���O�������\����	 			*/
/*�@ ��Q���� �Fint *   	�l						*/
/*  �o�@�@�́@�F                                                                */
/*  ���A���@�Fint								*/
/*		 0	����							*/
/*		-1	�ُ�							*/
/********************************************************************************/
static int
sFncShmGet ( pshmData )
int					*pshmData ;
{
	int		*shmData ;

	//	�A�^�b�`	
	shmData = ( int * ) shmat ( pAppEnv.shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmat", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "���L�������̑���Ɏ��s���܂���" ) ;
		return ( -1 ) ;
	}

	//	�l�ݒ�	
	*pshmData = *shmData ;

	//	�f�^�b�`	
	if ( shmdt ( shmData ) == -1 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "���L�������̑���Ɏ��s���܂���" ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/********************************************************************************/
/*  �� �� ���@�FsFncShmDel()							*/
/*  �@�\�T�v�@�F���L�������폜							*/
/*  ���@�@�́@�F                                                                */
/*�@ ��P���� �Fstruct appEnv *	�v���O�������\���́B		 		*/
/*  �o�@�@�́@�F                                                                */
/*  ���A���@�Fint								*/
/*		 0	����							*/
/*		-1	�ُ�							*/
/********************************************************************************/
static int
sFncShmDel()
{
	//	�폜	
	if ( shmctl ( pAppEnv.shm_Id, IPC_RMID, NULL) < 0 ) {
		//	�ُ�I��	LOG
		return ( -1 ) ;
	}
	return ( 0 ) ;
}	

/********************************************************************************/
/*  �� �� ���@�Fmain()								*/
/*  �@�\�T�v�@�F���C���֐�							*/
/*  ���@�@�́@�F                                                                */
/*�@ ��P���� �Fchar *pcLogName	�y�C�Ӂz���O�t�@�C�������w�肷��B		*/
/*		��NULL���w�肵���ꍇ��INI�t�@�C����胍�O�����擾����		*/
/*  �o�@�@�́@�F                                                                */
/*  ���A���@�F  0     : ����							*/
/* �@�@�@�@�@�@�@-1     : ���s							*/
/********************************************************************************/
int 
main( argc, argv )
int	 argc ;
char	*argv[] ;
{
	/***
	 ***    �o�b�N�O���E���h���s
	 ***/
	if ( daemon ( 0, 1 ) < 0 ) {
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                 "daemon�N�����s" ) ;
		exit ( 9 ) ;
	}

	/***
	 ***	��������	
	 ***/
	if ( initFunction ( argc, argv )  != 0 ) {
		endFunction() ;
		exit ( 9 ) ;
	}
	
	/***
	 ***	�又��	
	 ***/
	if ( mainFunction()  != 0 ) {
		endFunction() ;
		exit ( 9 ) ;
	}

	/***
	 ***	�I������	
	 ***/
	endFunction() ;
	exit( 0 ) ;
}

/** End of File ***************************************************************/
