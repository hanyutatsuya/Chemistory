/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FAD107.c                                                      */
/* �@�T�@�@�@�v�F�R�h�c����M                                               */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2008/02/27     moriya         �V�K�쐬                           */
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

#include "bmllog.h"
#include "bmlprm.h"
#include "bml_misc.h"
#include "bml_date.h"

#include "sql.h"

#include "AD107.h"

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
MYAPP_STSCODE			gintErrorCode ;
struct	stcLogMember	gstLogMem ;			/* ���O�o�͏��				*/
static	int				gintEnd ;			/* �d�m�c����M�t���O		*/
static	int				gintSeq ;			/* BUNPOS�W�J�t�@�C���̘A��	*/

/******************************************************************************/
/* �֐��錾                                                                   */
/******************************************************************************/
// BUNPOS���W�J�֘A�֐�
static	int		sFncGet3rdidMaxSeq ( char * ) ;
static	int		sFncFtpRecv ( struct appEnv * ) ;
static	int		sFncWCline ( char *, int *, int * ) ;
static	int		sFncSleepEx ( struct appEnv * ) ;
static	int		sFncPauseEx ( struct appEnv * ) ;
static	int		sFncMoveSkip ( struct appEnv * ) ;

// ���L����������֐�
static	int		sFncShmCrt ( struct appEnv * ) ;
static	int		sFncShmGet ( struct appEnv * , int * ) ;
static	int		sFncShmDel ( struct appEnv * ) ;

//	�R�[���o�b�N�֐�
static	int		sFncFileFillter ( struct dirent * ) ;

// ���O�֐�
void			sFncPutLog ( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... ) ;

// ���̑�
static	void	sFncTrim ( char * ) ;
static	int		sFncFileRename ( char *, char *, char *, char * ) ;


/******************************************************************************/
/*  �� �� ���@�FinitFunction()												  */
/*  �@�\�T�v�@�F���������֐�												  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct	env *   	�v���O�������\����		 			  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F  0     : ����												  */
/* �@�@�@�@�@�@�@-1     : ���s												  */
/******************************************************************************/
int
initFunction( argc, argv, pAppEnv )
int					 argc ;
char				*argv[] ;
struct appEnv	*pAppEnv ;
{
	char	 lc_prmBuf[256] ;
	long	 ll_retSts ;
	char	*lc_login ;

	/***              ***
	 ***    ������    ***
	 ***              ***/
	//	�G���[�X�e�[�^�X�ύX
	gintErrorCode = 0 ;

	//	�v���O�������ϐ�������
	memset ( pAppEnv , '\0', sizeof ( struct appEnv ) ) ;

	/***                                    ***
	 ***    ���O�I�[�v�� (AD107_LOG.ini)    ***
	 ***                                    ***/
	if ( ZbmlOpenLog ( MYAPP_LOGINIFILE ) != 0 ) {
		return ( -1 ) ;
	}
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "���OINI�I�[�v��[%s]", MYAPP_LOGINIFILE ) ;

	//	���O��񏉊��ݒ�
	memset ( &gstLogMem, '\0', sizeof ( gstLogMem ) ) ;
	if ( ( lc_login = getenv( "LOGNAME" ) ) != NULL ) {
		strcpy ( gstLogMem.pcLoginId, lc_login ) ;
	}
	strcpy ( gstLogMem.pcAppName, MYAPP_APP_NAME ) ;

	//	�J�n���O�o��
	sFncPutLog ( TRCKIND_OPT, __FILE__, "", __LINE__,
				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "�v���O�����N��" ) ;

	/***                    ***
	 ***    �����`�F�b�N    ***
	 ***                    ***/
	if ( argc != 2 ) {
		gintErrorCode = MYAPP_STSCODE_ERR_USEGE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "initFunction", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�R�}���h�p�����[�^�Ɍ�肪����܂�" ) ;
		return ( -1 ) ;
	}

	/***                                  ***
	 ***    �p�����[�^�t�@�C�����ޔ�    ***
	 ***                                  ***/
	//	�p�����[�^�t�@�C�����ޔ� (AD107.ini)
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "�p�����[�^�t�@�C��(AD107.ini)[%s]", argv[1] ) ;
	pAppEnv->pcFielNamePRM = argv[1] ;

	//	�p�����[�^�t�@�C���I�[�v��
	pAppEnv->bp = ZbmlPrmOpen ( pAppEnv->pcFielNamePRM ) ;
	if ( pAppEnv->bp == NULL ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmOpen", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^�t�@�C���̃I�[�v���Ɏ��s���܂���[%s]", pAppEnv->pcFielNamePRM ) ;
		return ( -1 ) ;
	}

	/*** �p�����[�^�l�擾 ***/
	//	���L�������L�[�擾
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_SHM_KEY, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_SHM_KEY ) ;
		return ( -1 ) ;
	}
	pAppEnv->shm_Key = atoi ( lc_prmBuf ) ;
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "pAppEnv->shm_Key[%d]", pAppEnv->shm_Key ) ;

	//	SLEEPSEC�擾
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_SLEEP_SEC, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_SLEEP_SEC ) ;
		return ( -1 ) ;
	}
	pAppEnv->sleep_Sec= atoi ( lc_prmBuf ) ;
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "pAppEnv->sleep_Sec[%d]", pAppEnv->sleep_Sec ) ;

	//	�����[�g���z�X�g���擾
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_FTP_HOST, pAppEnv->cFtpHost ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_FTP_HOST ) ;
		return ( -1 ) ;
	}
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "pAppEnv->cFtpHost[%s]", pAppEnv->cFtpHost ) ;

	//	�����[�g�����O�C�����[�U�擾
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_FTP_USER, pAppEnv->cFtpUser ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_FTP_USER ) ;
		return ( -1 ) ;
	}
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "pAppEnv->cFtpUser[%s]", pAppEnv->cFtpUser ) ;

	//	�����[�g�����O�C���p�X���[�h�擾
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_FTP_PSWD, pAppEnv->cFtpPswd ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_FTP_PSWD ) ;
		return ( -1 ) ;
	}
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "pAppEnv->cFtpPswd[%s]", pAppEnv->cFtpPswd ) ;

	//	�����[�g����M���p�X�擾
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_R_PATH, pAppEnv->cR_Path ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_R_PATH ) ;
		return ( -1 ) ;
	}
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "pAppEnv->cR_Path[%s]", pAppEnv->cR_Path ) ;

	//	�����[�g����M�t�@�C�����擾
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_R_FILE, pAppEnv->cR_File ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_R_FILE ) ;
		return ( -1 ) ;
	}
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "pAppEnv->cR_File[%s]", pAppEnv->cR_File ) ;

	//	���[�J������M��p�X�擾
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_L_PATH, pAppEnv->cL_Path ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_L_PATH ) ;
		return ( -1 ) ;
	}
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "pAppEnv->cL_Path[%s]", pAppEnv->cL_Path ) ;

	//	���[�J�����W�J�p�p�X�擾
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_I_PATH, pAppEnv->cI_Path ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_I_PATH ) ;
		return ( -1 ) ;
	}
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "pAppEnv->cI_Path[%s]", pAppEnv->cI_Path ) ;

	//	�����Ǘ��f�B���N�g���p�X�擾
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_M_PATH, pAppEnv->cM_Path ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_M_PATH ) ;
		return ( -1 ) ;
	}
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "pAppEnv->cM_Path[%s]", pAppEnv->cM_Path ) ;

	//	3ID���W�J(AD108)�̃X�L�b�v�t�@�C���p�X�擾
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_S_PATH, pAppEnv->cS_Path ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_S_PATH ) ;
		return ( -1 ) ;
	}
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "pAppEnv->cS_Path[%s]", pAppEnv->cS_Path ) ;

	//	FTP�����i�P�ʁF�b�j�擾
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_ITVAL, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_ITVAL ) ;
		return ( -1 ) ;
	}
	pAppEnv->iItval= atoi ( lc_prmBuf ) ;
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "initFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "pAppEnv->iItval[%d]", pAppEnv->iItval ) ;

	//	�p�����[�^�t�@�C���N���[�Y	
	ZbmlPrmClose ( pAppEnv->bp ) ;

	/***                                            ***
	 ***    BUNPOS�W�J�p�t�@�C���̘A�ԍő�l�擾    ***
	 ***                                            ***/
	gintSeq = 0 ;
	if ( sFncGet3rdidMaxSeq( pAppEnv->cM_Path ) != 0 )
	{
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "initFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "BUNPOS�W�J�p�t�@�C���̘A�ԍő�l���擾�ł��܂���ł���[%s/%s]", pAppEnv->cM_Path, FNM_3RDID_NUM ) ;
		return( -1 );
	}

	/***                      ***
	 ***    ���L����������    ***
	 ***                      ***/
	if ( sFncShmCrt ( pAppEnv ) < 0 ) {
		return ( -1 ) ;
	}

	return ( 0 ) ; 
}

/******************************************************************************/
/*  �� �� ���@�FmainFunction()												  */
/*  �@�\�T�v�@�F���C�������֐�												  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct	env *   	�v���O�������\���́B		 			  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F  0     : ����												  */
/* �@�@�@�@�@�@�@-1     : ���s												  */
/******************************************************************************/
int
mainFunction( pAppEnv )
struct appEnv	*pAppEnv ;
{
	int			iStopFlg ;
	int			iRet ;
	char		cZenFile[128] ;
	char		cKonFile[128] ;

	/* END����M�t���O������ */
	gintEnd = 0 ;

	/* �O��t�@�C��(3rdid.bak)�A����t�@�C��(3rdid.dat)�p�X������ */
	memset( cZenFile, 0, sizeof(cZenFile) ) ;
	memset( cKonFile, 0, sizeof(cKonFile) ) ;
	/* �O��t�@�C��(3rdid.bak) */
	sprintf( cZenFile , "%s/%s" , pAppEnv->cM_Path , FNM_3RDID_BAK );
	/* ����t�@�C��(3rdid.dat) */
	sprintf( cKonFile , "%s/%s" , pAppEnv->cM_Path , FNM_3RDID_DAT );

	/***                                  ***
	 ***    BUNPOS�t�@�C�����W�J����    ***
	 ***        �i�v���[�v                ***
	 ***        ��~�R�}���h�ŏI��        ***
	 ***                                  ***/
	while ( 1 ) {
		/* �O�X��Ɏ�M�����t�@�C���͏������� */
		unlink( cZenFile );
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "mainFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "unlink( cZenFile:%s )", cZenFile ) ;

		/* ����������O�ɍŐV�̎�M�t�@�C����O���M�t�@�C���Ƃ��� */
		link( cKonFile, cZenFile );
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "mainFunction	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "link( %s, %s )", cKonFile, cZenFile ) ;

		/* 3rdid�t�@�C��(A00_bunpos.dat)�̎�M�������o��(POS.data.XXXX) */
		sFncFtpRecv ( pAppEnv );

		/* 3ID���W�J(AD108)�̃X�L�b�v�t�@�C���ړ� */
		sFncMoveSkip ( pAppEnv );

		/* �d�m�c���R�[�h��M�܂ŌJ��Ԃ� */
		if( gintEnd == 1 ){
			break;
		}

		/* FTP�����p�����[�^�l���A�ҋ@���� */
		if ( sFncSleepEx ( pAppEnv ) != 0 ) {
			break;
		}

		/***                        ***
		 ***    ��~�R�}���h�m�F    ***
		 ***                        ***/
		if ( sFncShmGet ( pAppEnv, &iStopFlg ) == 0 ) {
			if ( iStopFlg == 1 ) {
				break ;
			}
		}
	}

	/* END���R�[�h��M */
	if ( gintEnd == 1 ){
		sFncPutLog ( TRCKIND_OPT, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�d�m�c���R�[�h�̎�M���m�F -> �ҋ@�ɓ���" ) ;
		sFncPauseEx ( pAppEnv ) ;
	}

	return ( 0 ) ;
}

/******************************************************************************/
/*  �� �� ���@�FendFunction()												  */
/*  �@�\�T�v�@�F�I�������֐�												  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct	env *   	�v���O�������\���́B		 			  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F  0     : ����												  */
/* �@�@�@�@�@�@�@-1     : ���s												  */
/******************************************************************************/
void
endFunction( pAppEnv )
struct appEnv	*pAppEnv ;
{

	/***                      ***
	 ***    ���L�������폜    ***
	 ***                      ***/
	sFncShmDel ( pAppEnv ) ;

	/***                    ***
	 ***    ���O�N���[�Y    ***
	 ***                    ***/
	//	�I�����O�o��
	sFncPutLog ( TRCKIND_OPT, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "�v���O�����I��" ) ;

	//	���O����
	ZbmlCloseLog();
	
	return ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncGet3rdidMaxSeq()                                          */
/*  �@�\�T�v�@�FBUNPOS�W�J�p�t�@�C���̍ő�r�d�p���o                          */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *      ���[�J���������Ǘ��p�X                            */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F  0     : ����                                                */
/* �@�@�@�@�@�@�@-1     : ���s                                                */
/******************************************************************************/
static int
sFncGet3rdidMaxSeq( pMpath )
char *pMpath ;
{
	char	cBuf[128] ;
	FILE	*pFp ;

	memset( cBuf, 0, sizeof(cBuf) ) ;
	sprintf( cBuf, "%s/%s", pMpath, FNM_3RDID_NUM );

	/* 3rdid.num�t�@�C�����݃`�F�b�N */
	if( access( cBuf, 0 ) < 0 ){
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncGet3rdidMaxSeq", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "�ʔԊǗ��t�@�C���Ȃ�[%s]", cBuf ) ;
		return ( 0 );
	}

	/* �J�� */
	pFp = fopen( cBuf, "r" ) ;
	if( pFp == NULL ){
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncGet3rdidMaxSeq", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "�ʔԊǗ��t�@�C���I�[�v���G���[[%s]", cBuf ) ;
		return ( -1 );
	}

	/* �ǂݍ��� */
	memset( cBuf, 0, sizeof(cBuf) ) ;
	if( fgets( cBuf, sizeof(cBuf), pFp ) == NULL ) {
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncGet3rdidMaxSeq", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "�ʔԊǗ��t�@�C�����e�Ȃ�" ) ;
	} else {
		/* �A�Ԑݒ� */
		gintSeq = atoi( cBuf ) ;
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncGet3rdidMaxSeq", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "�ʔԎ擾[%d]", gintSeq ) ;
	}

	/* ���� */
	fclose( pFp ) ;

	return ( 0 ) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncFtpRecv()                                                 */
/*  �@�\�T�v�@�F�t�����e�B�A���R�����������t�@�C������M����              */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv * �v���O�������\����                          */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F  0     : ����                                                */
/* �@�@�@�@�@�@�@-1     : ���s                                                */
/******************************************************************************/
static int
sFncFtpRecv( pAppEnv )
struct appEnv	*pAppEnv ;
{
	FILE    *pFp;
	FILE    *pFp_w;
	char	cLnkF[128];
	char	cRcvF[128];
	char	cTenF[128];
	char	cFPath[128];
	char	cCmdLine[128];
	char	cBuf[512];
	int		i;
	int     iRet;
	int		iWcRcv;
	int		iWcRcvSz;
	int		iWcBak;
	int		iWcBakSz;
	long	lOffset;

	/* �O�̂���FTP��M�\��t�@�C��(A00_bunpos.dat)���폜���Ă��� */
	memset( cRcvF, 0, sizeof(cRcvF) ) ;
	sprintf( cRcvF, "%s/%s", pAppEnv->cL_Path, pAppEnv->cR_File );
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "unlink( cRcvF:%s )", cRcvF ) ;
	unlink( cRcvF );

	/* FTP�R�}���h�t�@�C��(3rdid.ftp)�p�X */
	memset( cFPath, 0, sizeof(cFPath) ) ;
	sprintf( cFPath , "%s/%s" , pAppEnv->cM_Path , FNM_3RDID_CMD );
	/* FTP�R�}���h�t�@�C��(3rdid.ftp)�쐬 */
	pFp = fopen( cFPath, "w" );
	if( pFp == NULL ){
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "FTP�R�}���h�t�@�C���I�[�v���G���[[%s]", cFPath ) ;
		return( -1 );
	}
	fprintf( pFp, "open %s\n", pAppEnv->cFtpHost );
	fprintf( pFp, "user %s %s\n", pAppEnv->cFtpUser, pAppEnv->cFtpPswd );
	fprintf( pFp, "cd %s\n", pAppEnv->cR_Path );
	fprintf( pFp, "lcd %s\n", pAppEnv->cL_Path );
/*	fprintf( pFp, "binary\n" ); */
	fprintf( pFp, "get %s\n", pAppEnv->cR_File );
	fprintf( pFp, "close\n" );
	fprintf( pFp, "quit\n" );

	if( ferror(pFp) ){
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "FTP�R�}���h���o�͂ł��܂���[%s]", cFPath ) ;
		return( -1 );
	}
	fclose( pFp );

	/* FTP��M */
	memset( cCmdLine, 0, sizeof(cCmdLine) ) ;
	sprintf( cCmdLine, "lftp -f %s", cFPath );
/*	sprintf( cCmdLine, "ftp -n < %s", cFPath ); */
	system( cCmdLine );

	/* FTP��M�t�@�C�����݊m�F */
	if( access ( cRcvF, 0 ) != 0 ){
//		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//					 "FTP��M�t�@�C��������܂���[%s : %s]", pAppEnv->cFtpHost, cRcvF ) ;
		return( 100 );
	}

	/* �����M�t�@�C���̍s���擾 */
	iWcRcv = 0 ;
	iWcRcvSz = 0 ;
	iRet = sFncWCline( cRcvF, &iWcRcv, &iWcRcvSz );
	if( iRet != 0 ){
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�����M�t�@�C���̍s���擾���s[%s]", cRcvF ) ;
		return( -1 );
	}

	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "�����M�t�@�C��[Line : %d] [Size : %d] [Path : %s]", iWcRcv, iWcRcvSz, cRcvF ) ;

	/* �O���M�t�@�C���p�X */
	memset( cFPath, 0, sizeof(cFPath) ) ;
	sprintf( cFPath , "%s/%s" , pAppEnv->cM_Path , FNM_3RDID_BAK );
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "cFPath( %s )", cFPath ) ;

	/* �O���M�t�@�C���̍s���擾 */
	iWcBak = 0 ;
	iWcBakSz = 0 ;
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "iWcBak( %d ) iWcBakSz( %d )", iWcBak, iWcBakSz ) ;
	if( access ( cFPath, 0 ) == 0 ){
		/* �O���M�t�@�C������ */
		iRet = sFncWCline( cFPath, &iWcBak, &iWcBakSz );
		if( iRet != 0 ){
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 	 "�O���M�t�@�C���̍s���擾���s[%s]", cFPath ) ;
			return( -1 );
		}
//		/* �O���M�t�@�C���̍ŏI�s���s���S�����Ȃ̂� */
//		if( iWcBak > 0 ){
//			iWcBak--;
//		}
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "�O���M�t�@�C��[Line : %d] [Size : %d] [Path : %s]", iWcBak, iWcBakSz, cFPath ) ;
	}
	else{
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "�O���M�t�@�C���Ȃ�" ) ;
	}

	if( iWcRcvSz == iWcBakSz ){
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "�O���M�t�@�C���Ƃ̍����Ȃ�[iWcBakSz(%d) == iWcRcvSz(%d)]", iWcBakSz, iWcRcvSz ) ;
		return( 100 );
	}

	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "�O���M�t�@�C���Ƃ̍�������[iWcBakSz(%d) != iWcRcvSz(%d)]", iWcBakSz, iWcRcvSz ) ;

	/* �����M�t�@�C��(A00_bunpos.dat)���I�[�v�� */
	pFp = fopen( cRcvF, "r" );
	if( pFp == NULL ){
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�����M�t�@�C���I�[�v���G���[[%s]", cRcvF ) ;
		return( -1 );
	}

	/* ���ɑO��W�J���Ă����炻�̕����X�L�b�v */
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "iWcBak( %d )", iWcBak ) ;
	lOffset = (long)( iWcBak * RECLEN_3RDID );
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "lOffset( %ld )", lOffset ) ;
	iRet = fseek( pFp, lOffset, 0 );
	if( iRet < 0 ){
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�����M�t�@�C��SEEK�G���[[%s]", cRcvF ) ;
		fclose( pFp );
		return( -1 );
	}
	
	/* BUNPOS�W�J�pTMP�t�@�C��(TMP.data.0000) */
	memset( cTenF, 0, sizeof(cTenF) ) ;
	sprintf( cTenF, "%s/%s.data.0000", pAppEnv->cI_Path, TMP_BUNPOS );
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "cTenF( %s )", cTenF ) ;
	pFp_w = fopen( cTenF, "w" );
	if( pFp_w == NULL ){
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "BUNPOS�W�J�pTMP�t�@�C���I�[�v���G���[[%s]", cTenF ) ;
		fclose( pFp );
		return( -1 );
	}

	/* �����M�t�@�C���f�[�^�ǂݍ��� */
	memset( cBuf, 0, sizeof(cBuf) );
	while( 1 ){
		/* 1�s�ǂݍ��� */
		if( fgets( cBuf, sizeof(cBuf), pFp ) == NULL ){
			break;
		}
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "cBuf( %s )", cBuf ) ;
		if( strlen( cBuf ) >= RECLEN_3RDID ){
			/* BUNPOS�W�J�pTMP�t�@�C���ɏo�� */
			iRet = fputs( cBuf, pFp_w );
			if( iRet < 0 ){
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						 	 "BUNPOS�W�J�pTMP�t�@�C�������݃G���[[%s]", cBuf ) ;
				fclose(pFp);
				fclose(pFp_w);
				return( -1 );
			}
			if( memcmp( cBuf, RECEND_3RDID, 3 ) == 0 ){
				gintEnd = 1;
			}
		}
	}
	fclose(pFp);
	fclose(pFp_w);

	/* �W�J�t�@�C������ύX */
	for( i=0 ; i<99 ; i++ ){
		gintSeq++;
		sprintf( cLnkF, "%s/%s.data.%4.4d", pAppEnv->cI_Path, SEND_BUNPOS, gintSeq );
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "link( %s, %s )", cTenF, cLnkF ) ;
		iRet = link( cTenF, cLnkF );
		if( iRet == 0 ){
			sFncPutLog ( TRCKIND_TRACE, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 	 "�t�@�C���쐬[%s]", cLnkF ) ;
			break;
		}
	}
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "unlink( %s )", cTenF ) ;
	unlink( cTenF );

	/* �t�@�C��No�������� */
	sprintf( cBuf, "echo '%d' > %s/%s", gintSeq , pAppEnv->cM_Path , FNM_3RDID_NUM );
	system(cBuf);

	/* �����M�t�@�C���p�X */
	sprintf( cFPath , "%s/%s" , pAppEnv->cM_Path , FNM_3RDID_DAT );

	/* �Ō�Ɏ�M�t�@�C��(A00_bunpos.dat)�������M�t�@�C��(3rdid.dat)�Ƃ��ăR�s�[ */
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "unlink( %s )", cFPath ) ;
	unlink( cFPath );
sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncFtpRecv	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "link( %s, %s )", cRcvF, cFPath ) ;
	link( cRcvF, cFPath );

	return( 0 );
}

/******************************************************************************/
/*  �� �� ���@�FsFncWCline()                                                  */
/*  �@�\�T�v�@�F�t�@�C���s���̎擾                                            */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar * �t�@�C���p�X                                           */
/*�@ ��Q���� �Fint  * �t�@�C���s��                                           */
/*�@ ��R���� �Fint  * �t�@�C���T�C�Y                                         */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F  0     : ����                                                */
/* �@�@�@�@�@�@�@-1     : ���s                                                */
/******************************************************************************/
static int
sFncWCline( pFilePath, piLine, piSize )
char *pFilePath ;
int  *piLine ;
int  *piSize ;
{
	int		iSw;
	int		iIdx;
	int		i;
	char	cCmd[256];
	char	cBuf[256];
	char	cSize[256];
	char	cLine[256];
	FILE	*pFp;

	/* �t�@�C���̑��݊m�F */
	if( access( pFilePath, 0 ) < 0 ){
		return( -1 );
	}

	/* �s���ƃo�C�g���擾 */
	memset( cCmd, 0, sizeof(cCmd) );
	sprintf( cCmd, "wc -lc %s", pFilePath );
	pFp = popen( cCmd, "r" );
	if( pFp == NULL ){
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncWCline", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "��M�t�@�C���̂v�b�I�[�v���ł��܂���[%s]", cCmd ) ;
		return( -1 );
	}
	memset( cBuf, 0, sizeof(cBuf) );
	if( fgets( cBuf, sizeof(cBuf), pFp ) == NULL ){
		if( ferror( pFp ) ){
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncWCline", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 	 "��M�t�@�C���̂v�b�G���[[%s]", cCmd ) ;
			pclose(pFp);
			return( -1 );
		}
	}
	pclose( pFp );

	memset( cLine, 0, sizeof(cLine) );
	memset( cSize, 0, sizeof(cSize) );

	for( iSw=0,iIdx=0,i=0 ; i<sizeof(cBuf) ; i++ ){
		if( iSw == 9 ){
			break;
		}
		if( cBuf[i] == 0 || cBuf[i] == '\n' ){
			break;
		}
		if( cBuf[i] == ' ' || cBuf[i] == '\t' ){
			if( iSw == 3 ){ iSw = 9; }
			if( iSw == 1 ){ iSw = 2; }
		}
		if( cBuf[i] >= '0' && cBuf[i] <= '9' ){
			if( iSw == 2 ){ iSw = 3; iIdx = 0; }
			if( iSw == 0 ){ iSw = 1; iIdx = 0; }
		}
		if( iSw == 1 ){
			cLine[iIdx] = cBuf[i];
			iIdx++;
		}
		if( iSw == 3 ){
			cSize[iIdx] = cBuf[i];
			iIdx++;
		}
	}
	*piLine = atoi( cLine );
	*piSize = atoi( cSize );

	return( 0 );
}

/******************************************************************************/
/*  �� �� ���@�FsFncSleepEx()                                                 */
/*  �@�\�T�v�@�F�X���[�v                                                      */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv * �v���O�������\����                          */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F  0     : ����                                                */
/*  �@�@�@�@�@�F  1     : ��~�R�}���h��M                                    */
/******************************************************************************/
static int
sFncSleepEx ( pAppEnv )
struct appEnv	*pAppEnv ;
{
	int		iStopFlg = 0 ;	/* �I���t���O */
	time_t	sleepTm ;		/* �X���[�v���� */
	
	/* �X���[�v���鎞�Ԏ擾 */
	sleepTm = time(NULL) + (time_t)pAppEnv->iItval ;
	
	while( time(NULL) < sleepTm )
	{
		/***                        ***
		 ***    ��~�R�}���h�m�F    ***
		 ***                        ***/
		if ( sFncShmGet ( pAppEnv, &iStopFlg ) == 0 ) {
			if ( iStopFlg == 1 ) {
				break ;
			}
		}

		/* 1�b�X���[�v */
		sleep ( 1 );
	}

	return iStopFlg;
}

/******************************************************************************/
/*  �� �� ���@�FsFncPauseEx()                                                 */
/*  �@�\�T�v�@�F�|�[�Y                                                        */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv * �v���O�������\����                          */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F  0     : ����                                                */
/*  �@�@�@�@�@�F  1     : ��~�R�}���h��M                                    */
/******************************************************************************/
static int
sFncPauseEx ( pAppEnv )
struct appEnv	*pAppEnv ;
{
	int iStopFlg = 0;	/* �I���t���O */
	int iSkipCnt = 0 ;	/* SKIP�t�@�C��MOVE�̂��߂̃J�E���^ */
	int sleepTm ;		/* �X���[�v���� */
	
	/* �X���[�v���鎞�Ԏ擾 */
	sleepTm = pAppEnv->iItval ;

	for( ; ; )
	{
		if ( iSkipCnt == sleepTm )
		{
			/* 3ID���W�J(AD108)��SKIP�t�@�C���ړ� */
			sFncMoveSkip ( pAppEnv );

			iSkipCnt = 0 ;
		}

		/***                        ***
		 ***    ��~�R�}���h�m�F    ***
		 ***                        ***/
		if ( sFncShmGet ( pAppEnv, &iStopFlg ) == 0 ) {
			if ( iStopFlg == 1 ) {
				break ;
			}
		}

		iSkipCnt++ ;

		/* 1�b�X���[�v */
		sleep ( 1 );
	}

	return iStopFlg;
}

/******************************************************************************/
/*  �� �� ���@�FsFncMoveSkip()                                                */
/*  �@�\�T�v�@�FAD108��SKIP���ꂽ�t�@�C����MOVE����                           */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv * �v���O�������\����                          */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F  0     : ����                                                */
/*  �@�@�@�@�@�F -1     : �ُ�                                                */
/******************************************************************************/
static int
sFncMoveSkip ( pAppEnv )
struct appEnv	*pAppEnv ;
{
	int				  li_fileCnt ;
	int				  li_idx ;
	struct dirent	**lpst_dirBuf ;

	// SKIP.�`�t�@�C���̂݌���
	if ( ( li_fileCnt = scandir ( pAppEnv->cS_Path, &lpst_dirBuf, (void*)sFncFileFillter, alphasort ) ) < 0 )
	{
		// �ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_DIR;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncMoveSkip", __LINE__,
			 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 "SKIP�t�@�C���̎擾�Ɏ��s���܂���" ) ;
		return ( -1 ) ;
	}

	if( li_fileCnt ) {
		sFncPutLog ( TRCKIND_OPT, __FILE__, "sFncMoveSkip", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "SKIP�t�@�C���擾��[%d]", li_fileCnt) ;
	} else {
		return ( -1 ) ;
	}

	li_idx = 0 ;
	for ( li_idx = 0 ; li_idx < li_fileCnt ; li_idx ++ ) {
		// SKIP�t�@�C�������[�J�����W�J�p�X�ֈړ�����
		sFncPutLog ( TRCKIND_OPT, __FILE__, "sFncMoveSkip", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "SKIP�t�@�C���ړ�[%s/%s -> %s/%s]",
					 pAppEnv->cS_Path, lpst_dirBuf[li_idx]->d_name,
					 pAppEnv->cI_Path, lpst_dirBuf[li_idx]->d_name ) ;

		sFncFileRename ( pAppEnv->cS_Path, lpst_dirBuf[li_idx]->d_name,
						 pAppEnv->cI_Path, lpst_dirBuf[li_idx]->d_name ) ;
		free ( lpst_dirBuf[li_idx] ) ;
	}

	return ( 0 ) ;

}

/******************************************************************************/
/*  �� �� ���@�FsFncFileFillter()			 								  */
/*  �@�\�T�v�@�F�t�@�C���t�B���^�[�y�R�[���o�b�N�֐��z		  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct dirent *   	�f�B���N�g���\����				 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	�ΏۊO�t�@�C��										  */
/*					 1	�Ώۃt�@�C��										  */
/******************************************************************************/
static	int
sFncFileFillter ( pdirEnt ) 
struct dirent *pdirEnt ;
{
		int		li_len ;

		//�����񒷃`�F�b�N
		li_len = strlen ( pdirEnt->d_name )  ;
		if ( li_len  < 5 ) {
			return ( 0 ) ;
		}
		//���ʃ`�F�b�N
		if ( memcmp ( pdirEnt->d_name, 
					  SKIP_BUNPOS, 
					  strlen ( SKIP_BUNPOS ) ) != 0 ) {
			return ( 0 ) ;
		}
//		//�g���q�`�F�b�N
//		if ( memcmp ( &(pdirEnt->d_name[li_len-strlen(MYAPP_RECV_SFX)]), 
//					  MYAPP_RECV_SFX, 
//					  strlen ( MYAPP_RECV_SFX ) ) != 0 ) {
//			return ( 0 ) ;
//		}
		return ( 1 ) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncPutLog()                                                  */
/*  �@�\�T�v�@�F�A�v���P�[�V�������O�o��                                      */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �FLOG_TRCKIND �g���[�X���                                      */
/*�@ ��Q���� �Fchar *      �\�[�X��                                          */
/*�@ ��R���� �Fchar *      �֐���                                            */
/*�@ ��S���� �Fint         �\�[�X�s��                                        */
/*�@ ��T���� �Fchar *      ���s�t���O                                        */
/*�@ ��U���� �Fchar *      �G���[�R�[�h                                      */
/*�@ ��V���� �Fchar *      �o�̓��b�Z�[�W                                    */
/*�@ �悎���� �F...                                                           */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F����                                                          */
/******************************************************************************/
void
sFncPutLog ( LOG_TRCKIND peTrcKind, char * pcSrcName, char * pcFncName, int plLineNo, char * pcExeFlg, char * pcErrCode, char * pcfmt, ... )
{
	va_list	 ap ;
	char	 cMsg[1024] ;

	/***                      ***
	 ***    ���O�����l�ݒ�    ***
	 ***                      ***/
	gstLogMem.eTrcKind = peTrcKind ;
	strcpy ( gstLogMem.pcFncName, pcFncName ) ;
	strcpy ( gstLogMem.pcExeFlg,  pcExeFlg ) ;
	strcpy ( gstLogMem.pcErrCode, pcErrCode ) ;
	va_start ( ap, pcfmt ) ;
	vsprintf ( gstLogMem.pcMsg, pcfmt, ap ) ;
	va_end ( ap ) ;

	/***                ***
	 ***    ���O�o��    ***
	 ***                ***/
	_ZbmlPutLog ( &gstLogMem, pcSrcName, plLineNo) ;
	return ;
	
}

/******************************************************************************/
/*  �� �� ���@�FsFncTrim()  			 									  */
/*  �@�\�T�v�@�F������O��̃X�y�[�X���폜����				  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *   	�ҏW������								 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F����														  */
/******************************************************************************/
static	void
sFncTrim ( s )
char	*s ;
{
	int		i ;

    i = strlen ( s ) ;

    while ( --i >= 0 && isspace ( (unsigned char)s[i] ) ) ;
    s[i+1] = '\0';
    for (i = 0; isspace((unsigned char)s[i]); i++) ;
    if ( i != 0 ) {
		strcpy ( s, s + i ) ;
	}
}

/******************************************************************************/
/*  �� �� ���@�FsFncFileRename()  			 								  */
/*  �@�\�T�v�@�F�t�@�C�����ړ�����							  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *   	�ړ����f�B���N�g��						 	      */
/*�@ ��Q���� �Fchar *   	�ړ����t�@�C����						 	      */
/*�@ ��R���� �Fchar *   	�ړ���f�B���N�g��						 	      */
/*�@ ��S���� �Fchar *   	�ړ���t�@�C��							 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
static int
sFncFileRename ( pc_fromDir, pc_fromFileName, pc_toDir, pc_toFileName )
char	*pc_fromDir ;
char	*pc_fromFileName ;
char	*pc_toDir ;
char	*pc_toFileName ;
{
	char	lc_fromPath[MYAPP_PATH_SIZE] ;
	char	lc_toPath[MYAPP_PATH_SIZE] ;

	sprintf ( lc_fromPath, "%s/%s", pc_fromDir, pc_fromFileName ) ;
	sprintf ( lc_toPath,   "%s/%s", pc_toDir,   pc_toFileName ) ;

	if ( rename ( lc_fromPath, lc_toPath ) < 0 ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncFileRename", __LINE__,
 	 	 			 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
 	 	 			 "�t�@�C���̈ړ��Ɏ��s���܂���[%s -> %s]", lc_fromPath, lc_toPath ) ;
		return ( -1 ) ;
	}
	
	return ( 0 ) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncShmCrt()				 								  */
/*  �@�\�T�v�@�F���L����������								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����			 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
static int
sFncShmCrt ( pAppEnv )
struct appEnv	*pAppEnv ;
{
	int		*shmData ;

	//	�擾
	pAppEnv->shm_Id = shmget ( (key_t)pAppEnv->shm_Key, 
							MYAPP_SHM_SIZE, 
							0666 | IPC_CREAT ) ;
	if ( pAppEnv->shm_Id < 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncShmCrt", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "���L�������̑���Ɏ��s���܂���" ) ;
		return ( -1 ) ;
	}

	//	�A�^�b�`	
	shmData = ( int * ) shmat ( pAppEnv->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncShmCrt", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "���L�������̑���Ɏ��s���܂���" ) ;
		return ( -1 ) ;
	}

	//	�l�ݒ�	
	*shmData = 0 ;

	//	�f�^�b�`	
	if ( shmdt ( shmData ) == -1 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncShmCrt", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "���L�������̑���Ɏ��s���܂���" ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncShmGet()				 								  */
/*  �@�\�T�v�@�F���L�������擾								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����		 		      */
/*�@ ��Q���� �Fint *   			�l							 		      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
static int
sFncShmGet ( pAppEnv, pshmData )
struct appEnv	*pAppEnv ;
int					*pshmData ;
{
	int		*shmData ;

	//	�A�^�b�`	
	shmData = ( int * ) shmat ( pAppEnv->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncShmGet", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "���L�������̑���Ɏ��s���܂���" ) ;
		return ( -1 ) ;
	}

	//	�l�ݒ�	
	*pshmData = *shmData ;

	//	�f�^�b�`	
	if ( shmdt ( shmData ) == -1 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncShmGet", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "���L�������̑���Ɏ��s���܂���" ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncShmDel()				 								  */
/*  �@�\�T�v�@�F���L�������폜								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\���́B		 		      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
static int
sFncShmDel ( pAppEnv )
struct appEnv	*pAppEnv ;
{
	int		*shmData ;

	//	�폜	
	if ( shmctl ( pAppEnv->shm_Id, IPC_RMID, NULL) < 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncShmDel", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "���L�������̑���Ɏ��s���܂���" ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*  �� �� ���@�Fmain()														  */
/*  �@�\�T�v�@�F���C���֐�													  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *pcLogName    	�y�C�Ӂz���O�t�@�C�������w�肷��B		  */
/*									��NULL���w�肵���ꍇ��INI�t�@�C�����	  */
/*									  ���O�����擾����B					  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F  0     : ����												  */
/* �@�@�@�@�@�@�@-1     : ���s												  */
/******************************************************************************/
int 
main( argc, argv )
int		 argc ;
char	*argv[] ;
{

	struct appEnv	 sAppEnv ;

	/***                            ***
	 ***    �o�b�N�O���E���h���s    ***
	 ***                            ***/
	if ( daemon ( 0, 0 ) < 0 ) {
		exit ( 9 ) ;
	}


	/***                ***
	 ***    ��������    ***
	 ***                ***/
	if ( initFunction ( argc, argv, &sAppEnv )  != 0 ) {
		endFunction ( &sAppEnv ) ;
		exit ( 9 ) ;
	}
	
	/***              ***
	 ***    �又��    ***
	 ***              ***/
	if ( mainFunction ( &sAppEnv )  != 0 ) {
		endFunction ( &sAppEnv ) ;
		exit ( 9 ) ;
	}

	/***                ***
	 ***    �I������    ***
	 ***                ***/
	endFunction ( &sAppEnv ) ;
	exit(9);
}

/** End of File ***************************************************************/
