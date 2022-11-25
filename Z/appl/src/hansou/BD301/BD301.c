/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FBD301.c                                                      */
/* �@�T�@�@�@�v�F�X�g�b�J�[�y�����z                                           */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/15     �F��O�K       �V�K�쐬                           */
/*  1.01     2006/12/16   YOON JONG JIN    �G���[�ǉ�                         */
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

#include "sql.h"

#include "BD301.h"

/******************************************************************************/
/* Define��`                                                                 */
/******************************************************************************/
//	TRACE
#if defined ( _TRACE )
#define malloc(a)   _malloc(a, __FILE__, __LINE__)
#define free(p)     _free(p, __FILE__, __LINE__)
#endif

//  �t���O��`
typedef enum {
    LC_false,
    LC_true
} LC_BOOLEAN ;

/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/
MYAPP_STSCODE			 gintErrorCode ;
MYAPP_SYSTEM_VERSION	 gtSystemVersion ;
// 2008-02-04 �V�t�����e�B�A�Ή� INS START
MYAPP_SYSTEM_VERSION	 gtNewFrontierFlg;
// 2008-02-04 �V�t�����e�B�A�Ή� INS END
static	char			*gpToken ;			//	sFncTrFileToken�p�ÓI�|�C���^
struct stcLogMember		 gstLogMem ;		//	���O�o�͏��

/******************************************************************************/
/* �֐��錾                                                                   */
/******************************************************************************/
//	�g���[�E���b�N�R�t�����֘A�֐�
static	int		sFncTrFileRead ( struct appEnv *, char *, struct trInfo * ) ;
static	char*	sFncTrFileToken ( char * ) ;

//	�t�@�C���E�f�[�^�x�[�X�o�͊֐�
static	int 	sFncOutput ( struct appEnv *, struct trInfo * ) ;
static	int 	sFncFileOut ( struct appEnv *, struct my_stKENORDER *, struct my_stREALCHK *, int ) ;
static	int 	sFncOutRecKENORDER ( FILE *, char *, struct my_stKENORDER * ) ;
static	int 	sFncOutRecREALCHK ( FILE *, char *, struct my_stREALCHK * ) ;
static	void	sFncCreFileName ( char *, char *, char *, short, char *, struct tm * ) ;

//	���L����������֐�
static	int		sFncShmCrt ( struct appEnv * ) ;
static	int		sFncShmGet ( struct appEnv * , int *) ;
static	int		sFncShmDel ( struct appEnv * ) ;

//	�R�[���o�b�N�֐�
static	int		sFncFileCompar ( struct dirent **, struct dirent ** )  ;
static	int		sFncFileFillter ( struct dirent * ) ;

//	���̑�
static	int		sFncFileRename ( char *, char *, char *, char * ) ;
static	void	sFncTrim ( char * ) ;
static  void	endFunction(struct appEnv *);

//	�g���[�X�p
static	void	_sFncEnvDip ( struct appEnv * ) ;
static	void	_sFncTrInfoDisp ( struct trInfo * ) ;

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
initFunction( argc, argv, pAppEnv )
int					 argc ;
char				*argv[] ;
struct appEnv	*pAppEnv ;
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

	/***
	 ***	���O�I�[�v��
	 ***/
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

	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__,
				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "�v���O�����N��" ) ;
	//	�J�n���O�o��

	/***
	 ***	������	
	 ***/
	//	�G���[�X�e�[�^�X�ύX
	gintErrorCode = 0 ;

	//	�v���O�������ϐ�������
	memset ( pAppEnv , '\0', sizeof ( struct appEnv ) ) ;


	/***
	 ***	�����`�F�b�N	
	if ( argc != 2 ) {
		gintErrorCode = MYAPP_STSCODE_ERR_USEGE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "initFunction", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�R�}���h�p�����[�^�Ɍ�肪����܂�" ) ;
		return ( -1 ) ;
	}
	 ***/

	/***
	 ***	�p�����[�^�t�@�C�����ޔ�
	 ***/
	//	�p�����[�^�t�@�C�����ޔ�
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

	//	��M����
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_NR_SUP,
						pAppEnv->cDirNR_Sup ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_NR_SUP ) ;
		return ( -1 ) ;
	}
	//	��M��������
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_NR_SUP_OK, 
						pAppEnv->cDirNR_SupOk ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_NR_SUP_OK ) ;
		return ( -1 ) ;
	}
	//	��M�����G���[
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_NR_SUP_ERR, 
						pAppEnv->cDirNR_SupErr ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_NR_SUP_ERR ) ;
		return ( -1 ) ;
	}
	//	��M�������O
//DEL	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_NR_LOG, 
//DEL						pAppEnv->cDirNR_Log ) != 0 ) {
//DEL		//	�ُ�I��	LOG
//DEL		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
//DEL		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
//DEL				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//DEL				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_NR_LOG ) ;
//DEL		return ( -1 ) ;
//DEL	}
	//	�I�[�_�[�f�[�^
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_IA_DAT, 
						pAppEnv->cDirIA_Dat ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_IA_DAT ) ;
		return ( -1 ) ;
	}
	//	�I�[�_�[�f�[�^����
//DEL	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_IA_DAT_OK, 
//DEL						pAppEnv->cDirIA_DatOk ) != 0 ) {
//DEL		//	�ُ�I��	LOG
//DEL		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
//DEL		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
//DEL				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//DEL				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_IA_DAT_OK ) ;
//DEL		return ( -1 ) ;
//DEL	}
	//	�I�[�_�[�f�[�^�G���[
//DEL	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_IA_DAT_ERR, 
//DEL						pAppEnv->cDirIA_DatErr ) != 0 ) {
//DEL		//	�ُ�I��	LOG
//DEL		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
//DEL		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
//DEL				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//DEL				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_IA_DAT_ERR ) ;
//DEL		return ( -1 ) ;
//DEL	}
	//	�쐬�����f�[�^
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_IA_IDX, 
						pAppEnv->cDirIA_Idx ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_IA_IDX ) ;
		return ( -1 ) ;
	}
	//	�쐬�����f�[�^����
//DEL	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_IA_IDX_OK, 
//DEL						pAppEnv->cDirIA_IdxOk ) != 0 ) {
//DEL		//	�ُ�I��	LOG
//DEL		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
//DEL		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
//DEL				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//DEL				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_IA_IDX_OK ) ;
//DEL		return ( -1 ) ;
//DEL	}
	//	�쐬�����f�[�^�G���[
//DEL	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_IA_IDX_ERR, 
//DEL						pAppEnv->cDirIA_IdxErr ) != 0 ) {
//DEL		//	�ُ�I��	LOG
//DEL		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
//DEL		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
//DEL				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//DEL				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_IA_IDX_ERR ) ;
//DEL		return ( -1 ) ;
//DEL	}
	//	�I�[�_�[�f�[�^���O
//DEL	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_IA_LOG, 
//DEL						pAppEnv->cDirIA_Log ) != 0 ) {
//DEL		//	�ُ�I��	LOG
//DEL		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
//DEL		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
//DEL				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//DEL				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_IA_LOG ) ;
//DEL		return ( -1 ) ;
//DEL	}
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
	//	�f�[�^�x�[�X��
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DB_NAME, 
						pAppEnv->cDb_Name ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DB_NAME ) ;
		return ( -1 ) ;
	}
	//	�f�[�^�x�[�X���[�U
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DB_USER, 
						pAppEnv->cDb_User ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DB_USER ) ;
		return ( -1 ) ;
	}
	//	�f�[�^�x�[�X�p�X���[�h
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DB_PASSWD, 
						pAppEnv->cDb_Passwd ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DB_PASSWD ) ;
		return ( -1 ) ;
	}
	//	�t�@�C���Ǎ����g���C��
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_FILE_RETRY, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_FILE_RETRY ) ;
		return ( -1 ) ;
	}
	pAppEnv->fileRetry = atoi ( lc_prmBuf ) ;
	//	�o�[�W�������i������Ή��j	
	gtSystemVersion = MYAPP_SYSTEM_NEW ;
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_VERSION, 
						pAppEnv->cVersion ) != 0 ) {
		gtSystemVersion = MYAPP_SYSTEM_OLD ;
	}

	//	�p�����[�^�t�@�C���N���[�Y	
	ZbmlPrmClose ( pAppEnv->bp ) ;

	/***
	 ***	���L����������	
	 ***/
	if ( sFncShmCrt ( pAppEnv ) < 0 ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
        	EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "���L����������[") ;
		return ( -1 ) ;
	}

	/***
	 ***	�f�[�^�x�[�X�I�[�v��
	 ***/
	ll_retSts = ZdbConnect( pAppEnv->cDb_Name, pAppEnv->cDb_User, pAppEnv->cDb_Passwd ) ;
	if ( ll_retSts != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_DB ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZdbConnect", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�f�[�^�x�[�X�I�[�v���Ɏ��s���܂���[DB=%s USER=%s PASS=%s]", pAppEnv->cDb_Name, pAppEnv->cDb_User, pAppEnv->cDb_Passwd ) ;
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
	int					  li_retSts ;
	long				  ll_retSts ;

	int					  li_idx ;	
	int					  li_stopFlg ;

	//	�f�B���N�g����� 
	DIR					 *lt_dp ;
	struct dirent		**lpst_dirBuf ;

	//	�g���[���b�N���֘A
	int					  li_fileCnt ;				
	struct trInfo		  lst_trInfo ;

	/***
	 ***	��M�g���[�E���b�N�����f�B���N�g���Ď�	
	 ***		�i�v���[�v
	 ***		��~�R�}���h�ŏI��
	 ***/
	while ( 1 ) {

		/***
		 *** �t�@�C�����擾
		 ***/
		if ( ( li_fileCnt = scandir ( pAppEnv->cDirNR_Sup, 
									  &lpst_dirBuf,
									  (void*)sFncFileFillter,
					   				  (void*)sFncFileCompar ) ) < 0 ) {
			//	�ُ�I��	LOG
			gintErrorCode = MYAPP_STSCODE_ERR_DIR;
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "scandir", __LINE__,
				 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 	 "�g���[�E���b�N�R�t�����t�@�C���̎擾�Ɏ��s���܂���" ) ;
			return ( -1 ) ;
		}

		/***
		 ***	�f�[�^����
		 ***/
		li_idx = 0 ;
		for ( li_idx = 0 ; li_idx < li_fileCnt ; li_idx ++ ) {
//my_loging ( "STR : %s\n", lpst_dirBuf[li_idx]->d_name ) ;
			//	�g���[�E���b�N�R�t�����擾
			li_retSts = sFncTrFileRead ( pAppEnv, lpst_dirBuf[li_idx]->d_name, 
				&lst_trInfo ) ;
			if ( li_retSts < 0 ) {
				//	�G���[�f�B���N�g���Ɉړ�
				sFncFileRename ( pAppEnv->cDirNR_Sup, 
								 lpst_dirBuf[li_idx]->d_name,
								 pAppEnv->cDirNR_SupErr,
								 lpst_dirBuf[li_idx]->d_name ) ;
				//	���̃g���[�E���b�N�R�t�����t�@�C���̏������s��
				free ( lpst_dirBuf[li_idx] ) ;
				continue ;
			} else if ( li_retSts == 2 ) {
				//	�g���[�E���b�N�R�t�����t�@�C���ȊO
				//	���̃g���[�E���b�N�R�t�����t�@�C���̏������s��
				free ( lpst_dirBuf[li_idx] ) ;
				continue ;
			}
_sFncTrInfoDisp ( &lst_trInfo ) ;

			//	�����I�[�_�[�E�����`�F�b�N���o��
			li_retSts = sFncOutput ( pAppEnv, &lst_trInfo ) ;
			if ( li_retSts == 0 ) {
				//	���ǃf�B���N�g���Ɉړ�
				sFncFileRename ( pAppEnv->cDirNR_Sup, 
								 lpst_dirBuf[li_idx]->d_name,
								 pAppEnv->cDirNR_SupOk,
								 lpst_dirBuf[li_idx]->d_name ) ;
			} else {
				    
				//2006-12-15 YOON
				if ( li_retSts != 2 ) {
					//	�G���[�f�B���N�g���Ɉړ�
					sFncFileRename ( pAppEnv->cDirNR_Sup, 
								 	lpst_dirBuf[li_idx]->d_name,
								 	pAppEnv->cDirNR_SupErr,
								 	lpst_dirBuf[li_idx]->d_name ) ;
					sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__,
    					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
	                 	"[[DB ERROR]]�ŏI��" ) ;

					endFunction ( pAppEnv ) ;
        			exit ( 9 ) ;
				}
			}
//my_loging ( "END : %s\n", lpst_dirBuf[li_idx]->d_name ) ;
				
			//	���
			free ( lpst_dirBuf[li_idx] ) ;

			/***
		 	 *** ��~�R�}���h�m�F
		 	 ***/
			if ( sFncShmGet ( pAppEnv, &li_stopFlg ) == 0 ) {
				if ( li_stopFlg == 1 ) {
					return ( 0 ) ;
				}
			}
		}

		/***
		 *** ��~�R�}���h�m�F
		 ***/
		if ( sFncShmGet ( pAppEnv, &li_stopFlg ) == 0 ) {
			if ( li_stopFlg == 1 ) {
				break ;
			}
		}

		/***
		 *** �X���[�v
		 ***/
		sleep ( pAppEnv->sleep_Sec ) ;
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
	/***
	 ***	�f�[�^�x�[�X�N���[�Y
	 ***/
	ZdbDisConnect() ;

	/***
	 ***	���L�������폜	
	 ***/
	sFncShmDel ( pAppEnv ) ;

	/***
	 ***	���O�N���[�Y
	 ***/
	//	�I�����O�o��
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__,
				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "�v���O�����I��" ) ;
	ZbmlCloseLog() ;
	
	return ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncOutput()				 								  */
/*  �@�\�T�v�@�F�����I�[�_�[���A�����`�F�b�N�t�@�C���o��	 	 			  */
/*				���b�N���Ɋe�t�@�C���A�f�[�^�x�[�X�̍X�V���s��				  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����			 	      */
/*�@ ��R���� �Fstruct trInfo *  	�g���[�E���b�N�R�t�����i�[�\����		  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					 2	�f�b�h���b�N										  */
/*					-1	�ُ�												  */
/******************************************************************************/
static int
sFncOutput ( pAppEnv, pst_trInfo )
struct appEnv		*pAppEnv ;
struct trInfo		*pst_trInfo ;
{
	int		 				 li_idx ;
	int		 				 li_recIdx ;
	int		 				 li_retSts ;
	long	 				 ll_retSts ;
	int		 				 li_Return ;

	char					 cSel_knskisymd[MYAPP_DATE_SIZE] ;
	/*
	struct my_stKENORDER	 recKENORDER[100] ;		 		 
	struct my_stREALCHK		 recREALCHK[100] ;
	*/
	struct my_stKENORDER	*recKENORDER ;		 		 
	struct my_stREALCHK		*recREALCHK ;
	int						 recCnt ;
	int						 svRecCnt ;
	LC_BOOLEAN				 blnErrFlg ;
	LC_BOOLEAN				 blnLockFlg ;
// 2008-02-04 �V�t�����e�B�A�Ή� INS START
	int						 li_BunTrCnt ;
	int						 li_len ;
	int						 li_Trknhsu ;	//�g���[�����̖{��
	int						 li_MaxOrderTrpos ;
	char					 buf[11], buf1[11], buf2[11], cTrhdid[11], cKnsgrp[17] ;
	int						 recTrCnt ;
// 2008-02-04 �V�t�����e�B�A�Ή� INS END

	
	/***
	 ***	�ϐ�������
	 ***/
	blnErrFlg   = LC_false ;
	blnLockFlg  = LC_false ;
	li_Return   = 0 ;

	recCnt      = 0 ;
	svRecCnt    = 0 ;
	recKENORDER = NULL ;
	recREALCHK  = NULL ;
	
	//	��{�����L�[�ݒ� �����J�n��)
	sprintf ( cSel_knskisymd, "%4.4s-%2.2s-%2.2s", 
					  		  pst_trInfo->knskisymd, 
					  		  &(pst_trInfo->knskisymd[4]), 
					  		  &(pst_trInfo->knskisymd[6]) ) ;

// 2008-02-04 �V�t�����e�B�A�Ή� INS START
	// pst_trInfo->trid(���݃t�@�C�����̃g���[ID)��BUNCHU������
	li_BunTrCnt = 0 ;
	li_retSts = sFncSelCntKENORDER ( cSel_knskisymd,
									 pst_trInfo->trid,
									 &li_BunTrCnt ) ;
	
	// �������ʂ�0�̏ꍇ�͐V�t���Ή��f�[�^ (TRID = '____0000')
	if ( li_BunTrCnt == 0 ) {
		gtNewFrontierFlg = MYAPP_SYSTEM_NEW;
	} else {
		gtNewFrontierFlg = MYAPP_SYSTEM_OLD;
	}
// 2008-02-04 �V�t�����e�B�A�Ή� INS END
	
	/***
	 ***	���C������
	 ***/
	/*
	memset ( recKENORDER, '\0', sizeof ( recKENORDER ) ) ;
	memset ( recREALCHK,  '\0', sizeof ( recREALCHK ) ) ;
	*/
	for ( li_idx = 0 ; li_idx < MYAPP_RACK_MAXCNT ; li_idx++ ) {

		//	�u�����N�͏������s��Ȃ�
		if ( pst_trInfo->asyrckid[li_idx][0] == '\0' ) {
			continue ;
		}

		/***
		 ***	�X�V�E����
		 ***/
// 2008-02-04 �V�t�����e�B�A�Ή� UPD START
//		if ( gtSystemVersion == MYAPP_SYSTEM_OLD ) {
		if ( gtNewFrontierFlg == MYAPP_SYSTEM_OLD ) {
// 2008-02-04 �V�t�����e�B�A�Ή� UPD END
			//	�y�ߓn���z	
			//	�����I�[�_�[���X�V
			li_retSts = sFncUpdKENORDER ( cSel_knskisymd,
										  pst_trInfo->trid,
										  ( 5 * li_idx ) + 1,
										  ( 5 * li_idx ) + 5,
										  pst_trInfo->asyrckid[li_idx],
										  li_idx ) ;
           	//2006-12-16 YOON 
            if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
            {
                //�f�b�h���b�Nor�d��
                blnLockFlg = LC_true ;
                break ;
            }
            else if ( li_retSts < 0 ) {
                blnErrFlg = LC_true ;
                break ;
            }
			//DEL	�����`�F�b�N���X�V
			//DEL	li_retSts = sFncUpdREALCHK ( cSel_knskisymd,
			//DEL								 pst_trInfo->trid,
			//DEL								 ( 5 * li_idx ) + 1,
			//DEL								 ( 5 * li_idx ) + 5,
			//DEL								 pst_trInfo->asyrckid[li_idx], 
			//DEL								 li_idx ) ;
			//DEL	if ( li_retSts == 2 ) {
			//DEL		//�f�b�h���b�N
			//DEL		blnLockFlg = LC_true ;
			//DEL		break ;
			//DEL	}
			//DEL	if ( li_retSts < 0 ) {
			//DEL		blnErrFlg = LC_true ;
			//DEL		break ;
			//DEL	}

			//	���̃|�W�V�������ǉ�
			li_retSts = sFncInsKENPOS ( cSel_knskisymd,
										pst_trInfo->trid,
										( 5 * li_idx ) + 1,
										( 5 * li_idx ) + 5,
										pst_trInfo->stkno ) ;
           	//2006-12-16 YOON 
            if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
            {
                //�f�b�h���b�Nor�d��
                blnLockFlg = LC_true ;
                break ;
            }
            else if ( li_retSts < 0 ) {
                blnErrFlg = LC_true ;
                break ;
            }
			
			//	�����I�[�_�[���E�����`�F�b�N��񌟍�
			li_retSts = sFncSelKENORDER_REALCHK ( cSel_knskisymd,
												  pst_trInfo->trid,
												  ( 5 * li_idx ) + 1,
												  ( 5 * li_idx ) + 5,
												  &recKENORDER,
												  &recREALCHK,
												  &recCnt ) ;
           	//2006-12-16 YOON 
			if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
            {
                //�f�b�h���b�Nor�d��
                blnLockFlg = LC_true ;
                break ;
            }
            else if ( li_retSts < 0 ) {
                blnErrFlg = LC_true ;
                break ;
            }		


			if ( ( recCnt - svRecCnt ) == 0 ) {
				sFncPutLog ( TRCKIND_WARNING, __FILE__, "sFncOutput", __LINE__,
			 	 			 EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
			 		 		 "�����I�[�_���A�܂��͑����`�F�b�N��񂪑��݂��܂��� KNSKISYMD='%s' TRID='%s' TRPOS %d-%d RCKID='%s'", cSel_knskisymd, pst_trInfo->trid, ( 5 * li_idx ) + 1, ( 5 * li_idx ) + 5, pst_trInfo->asyrckid[li_idx] ) ;
			} else {
				svRecCnt = recCnt ;
			}
			
		} else {
			//	�y������z	
// 2008-02-04 �V�t�����e�B�A�Ή� INS START
// ������ �g���[�Ǘ��}�X�^�������Ă�li_Trknhsu��100�Ȃ̂ŁA
// �w�b�_�t�@�C���� MYAPP_TRKNHSU_MAXCNT (100)���g���B
			// �g���[�����̖{�� (100)
			li_Trknhsu = MYAPP_TRKNHSU_MAXCNT ;
// �g���[�Ǘ��}�X�^������ꍇ�́����R�����g�ɂ��A���𕜊�����B
//			// �g���[�Ǘ��}�X�^����g���[�����̖{�����擾
//			memset(cTrhdid, 0, sizeof(cTrhdid)) ;
//			memcpy(cTrhdid, pst_trInfo->trid, 4) ;
//			li_retSts = sFncSelTRMST ( cTrhdid,
//									   cSel_knskisymd,
//									   &li_Trknhsu,
//									   &recTrCnt ) ;
//
//			if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
//			{
//				//�f�b�h���b�Nor�d��
//				blnLockFlg = LC_true ;
//				break ;
//			}
//			else if ( li_retSts < 0 ) {
//				blnErrFlg = LC_true ;
//				break ;
//			}
//			else if ( recTrCnt == 0 ) {
//				blnErrFlg = LC_true ;
//				sFncPutLog ( TRCKIND_WARNING, __FILE__, "sFncOutput", __LINE__,
//							 EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
//							 "�g���[�Ǘ��}�X�^�ɊY���f�[�^�����݂��܂��� TRHDID='%s' KAIYMD='%s' HAIYMD='%s'", cTrhdid, cSel_knskisymd, cSel_knskisymd ) ;
//				break ;
//			}
// 2008-02-04 �V�t�����e�B�A�Ή� INS END

			//	�����I�[�_�[���X�V
// 2008-02-04 �V�t�����e�B�A�Ή� UPD START
//			li_retSts = sFncUpdKENORDER_NXT ( cSel_knskisymd,
//											  pst_trInfo->asyrckid[li_idx],
//											  pst_trInfo->trid,
//											  li_idx ) ;

			memset(buf, 0, sizeof(buf)) ;
			memset(buf1, 0, sizeof(buf1)) ;
			memcpy(buf, pst_trInfo->trid, 11) ;
			li_len = strlen(buf) - 4 ;
			strcpy(buf1, &buf[li_len]);
			li_len = atoi(buf1);
			li_retSts = sFncUpdKENORDER_NXT ( cSel_knskisymd,
											  pst_trInfo->asyrckid[li_idx],
											  pst_trInfo->trid,
											  li_len * li_Trknhsu,
											  li_idx ) ;
// 2008-02-04 �V�t�����e�B�A�Ή� UPD END

           	//2006-12-16 YOON 
            if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
            {
                //�f�b�h���b�Nor�d��
                blnLockFlg = LC_true ;
                break ;
            }
            else if ( li_retSts < 0 ) {
                blnErrFlg = LC_true ;
                break ;
            }

// 2008-02-04 �V�t�����e�B�A�Ή� DEL START
//			//	�����`�F�b�N���X�V
//			li_retSts = sFncUpdREALCHK_NXT ( cSel_knskisymd,
//											 pst_trInfo->asyrckid[li_idx],
//										     pst_trInfo->trid,
//										     li_idx ) ;
//           	//2006-12-16 YOON 
//            if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
//            {
//                //�f�b�h���b�Nor�d��
//                blnLockFlg = LC_true ;
//                break ;
//            }
//            else if ( li_retSts < 0 ) {
//                blnErrFlg = LC_true ;
//                break ;
//            }
// 2008-02-04 �V�t�����e�B�A�Ή� DEL END

			//	���̃|�W�V�������ǉ�
			li_retSts = sFncInsKENPOS_NXT ( cSel_knskisymd,
											pst_trInfo->asyrckid[li_idx],
											pst_trInfo->stkno ) ;
           	//2006-12-16 YOON 
            if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
            {
                //�f�b�h���b�Nor�d��
                blnLockFlg = LC_true ;
                break ;
            }
            else if ( li_retSts < 0 ) {
                blnErrFlg = LC_true ;
                break ;
            }
			//	�����I�[�_�[���E�����`�F�b�N��񌟍�
			li_retSts = sFncSelKENORDER_REALCHK_NXT ( cSel_knskisymd,
												      pst_trInfo->trid,
												      ( 5 * li_idx ) + 1,
												      ( 5 * li_idx ) + 5,
												      &recKENORDER,
												      &recREALCHK,
												      &recCnt ) ;
           	//2006-12-16 YOON 
            if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
            {
                //�f�b�h���b�Nor�d��
                blnLockFlg = LC_true ;
                break ;
            }
            else if ( li_retSts < 0 ) {
                blnErrFlg = LC_true ;
                break ;
            }			
			if ( ( recCnt - svRecCnt ) == 0 ) {
				sFncPutLog ( TRCKIND_WARNING, __FILE__, "sFncOutput", __LINE__,
			 	 			 EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
			 		 		 "�����I�[�_���A�܂��͑����`�F�b�N��񂪑��݂��܂��� KNSKISYMD='%s' TRID='%s' TRPOS %d-%d RCKID='%s'", cSel_knskisymd, pst_trInfo->trid, ( 5 * li_idx ) + 1, ( 5 * li_idx ) + 5, pst_trInfo->asyrckid[li_idx] ) ;
			} else {
				svRecCnt = recCnt ;
			}
		}
	} 

// 2008-02-04 �V�t�����e�B�A�Ή� INS (AD105����ڍs) START
	if ( gtNewFrontierFlg == MYAPP_SYSTEM_NEW ) {
		li_retSts = sFncSelKENORDER ( cSel_knskisymd,
									  pst_trInfo->trid,
									  &li_MaxOrderTrpos );
		if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
		{
		    //�f�b�h���b�Nor�d��
		    blnLockFlg = LC_true ;
		}
		else if ( li_retSts < 0 ) {
		    blnErrFlg = LC_true ;
		}

		// �I�[�_�[������ꍇ�̂�WSSEQKNRI��INSERT����
		if ( li_MaxOrderTrpos != 0 ) {
			// �����O���[�v(�X�y�[�X16��)�ݒ�
			memset(cKnsgrp, 0, sizeof(cKnsgrp));
			memset(cKnsgrp, ' ', 16);
			//�g���[ID�̉�4���𐔒l��
			memset(buf1, 0, sizeof(buf1));
			memset(buf2, 0, sizeof(buf2));
			ZbmlInfocpy(buf1, pst_trInfo->trid, 11) ;
			li_len = strlen(buf1) - 4 ;
			strcpy(buf2, &buf1[li_len]);
			li_len = atoi(buf2);

			//����WS���R�[�h�̓o�^
			insWsseqknri(cSel_knskisymd,
						 cKnsgrp,
						 pst_trInfo->trid,
						 li_MaxOrderTrpos,
						 (li_len * li_Trknhsu + 1),
						 (li_len * li_Trknhsu + li_MaxOrderTrpos) ) ;

			if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
			{
			    //�f�b�h���b�Nor�d��
			    blnLockFlg = LC_true ;
			}
			else if ( li_retSts < 0 ) {
			    blnErrFlg = LC_true ;
			}
		}
	}
// 2008-02-04 �V�t�����e�B�A�Ή� INS (AD105����ڍs) END

	/***
	 ***	�g�����U�N�V�����I��
	 ***	�����I�[�_���A�����`�F�b�N���̂݃g�����U�N�V�����I��
	 ***	ADD NO.14 2006/05/26
	 ***/
	if ( blnErrFlg == LC_true || blnLockFlg == LC_true ) {
	 	//	���[���o�b�N
		ZdbRollback () ;
	} else {
		//	�R�~�b�g
		ZdbCommit () ; 
	}

// 2008-02-04 �V�t�����e�B�A�Ή� DEL (�g���ĂȂ������E�E�E) START
//	/***
//	 ***	�g���[�Ǘ����X�V
//	 ***	�G���[���������Ă������_�̃t�@�C�����쐬����
//	 ***/
//	li_retSts = sFncUpdTRAYKNRI ( cSel_knskisymd,
//							  	  pst_trInfo->trid,
//							  	  pst_trInfo->stkno ) ;
//	if ( li_retSts < 0 ) {
//	 	//	���[���o�b�N
//		ZdbRollback () ;
//	} else {
//		//	�R�~�b�g
//		ZdbCommit () ; 
//	}
// 2008-02-04 �V�t�����e�B�A�Ή� DEL (�g���ĂȂ������E�E�E) END


	/***
	 ***	�t�@�C���o��
	 ***/
	if ( blnErrFlg != LC_true && blnLockFlg != LC_true && recCnt > 0 ) {
		//	�����I�[�_�[���
		li_retSts = sFncFileOut ( pAppEnv, recKENORDER, recREALCHK, recCnt ) ;
		if ( li_retSts < 0 ) {
			blnErrFlg = LC_true ;
		}
	}

	free ( recKENORDER ) ;
	free ( recREALCHK ) ;

	if ( blnLockFlg == LC_true ) {
		return ( 2 ) ;
	}
	if ( blnErrFlg == LC_true ) {
		return ( -1 ) ;
	}
	return ( 0 ) ;
}
/******************************************************************************/
/*  �� �� ���@�FsFncFileOut()				 								  */
/*  �@�\�T�v�@�F�����I�[�_�[�E�����`�F�b�N���t�@�C���o��				 	  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����			 	      */
/*�@ ��Q���� �FKenorder  *   		�����I�[�_�[�����\����			      */
/*�@ ��R���� �FRealchk  *   		�����`�F�b�N�����\����		 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
static int
sFncFileOut ( pAppEnv, precKenorder, precRealchk, precCnt )
struct appEnv			*pAppEnv ;
struct my_stKENORDER	*precKenorder ;
struct my_stREALCHK		*precRealchk ;
int						 precCnt ;
{
	FILE			*lfp_R ;
	FILE			*lfp_K ;
	FILE			*lfp_IDX ;
	char			 lc_recBuf_K[512] ;
	char			 lc_recBuf_R[8192] ;
	char			 lc_dataFileName_K[MYAPP_PATH_SIZE] ;
	char			 lc_dataFileName_R[MYAPP_PATH_SIZE] ;
	char			 lc_fileName_K[MYAPP_PATH_SIZE] ;
	char			 lc_fileName_R[MYAPP_PATH_SIZE] ;
	char			 lc_idxFileName[MYAPP_PATH_SIZE] ;

	char			 SV_asyrckid[MYAPP_RKNO_SIZE] ;
	int			 	 SV_asyrckpos ;
	LC_BOOLEAN		 blnFirstFlg ;

	int				 idx ;

	struct tm		*timepos ;
	struct timeb	 timebuf ;

	/***
	 ***	��������
	 ***/
	blnFirstFlg   = LC_true ;
	//	�V�X�e�����t�����擾
	ftime ( &timebuf ) ;
	timepos  = ( struct tm * ) localtime ( &( timebuf.time ) ) ;
	//	�u���C�N�L�[
	memset ( SV_asyrckid, '\0', sizeof ( SV_asyrckid ) ) ;
	SV_asyrckpos = -1 ;
	//	�ϐ�������
	lfp_R   = NULL ;
	lfp_K   = NULL ;
	lfp_IDX = NULL ;

	
	/***
	 ***	�t�@�C���o��
	 ***/
	for ( idx = 0 ; idx < precCnt ; idx ++ ) {
		/***
		 ***	�u���C�N���� 
		 ***/
		if ( strcmp ( SV_asyrckid, precKenorder[idx].asyrckid ) != 0 ||
			 SV_asyrckpos != precKenorder[idx].asyrckpos ) {
			/***
			 ***	����ȊO�̏���
			 ***		�����I�[�_�[���t�@�C���o��
			 ***		�t�@�C���N���[�X
			 ***/
			if ( blnFirstFlg != LC_true ) {
			 	//	�t�@�C���N���[�Y
				fclose ( lfp_R ) ;
				fclose ( lfp_K ) ;
				//�����I�[�_�[���t�@�C���o��
				lfp_IDX  = fopen ( lc_idxFileName , "w" ) ;
				if ( lfp_IDX == NULL ) {
					//	�ُ�I��	LOG
					unlink ( lc_dataFileName_R ) ;
					unlink ( lc_dataFileName_K ) ;
					gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "fopen", __LINE__,
			 	 	 			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 			"�t�@�C���̃I�[�v���Ɏ��s���܂���[%s]", 
								lc_idxFileName ) ;
					return ( -1 ) ;
				}
				fclose ( lfp_IDX ) ;
			} else {
				blnFirstFlg = LC_false ;
			}

			/***
			 ***	�u���C�N�L�[������
			 ***/
			strcpy ( SV_asyrckid, precKenorder[idx].asyrckid ) ;
			SV_asyrckpos =  precKenorder[idx].asyrckpos ;

			/***
			 ***	�t�@�C�����쐬	
			 ***/
			//	�����`�F�b�N���t�@�C�����쐬
			sFncCreFileName ( lc_fileName_R, MYAPP_SEND_KIND_CH, 
							  precKenorder[idx].asyrckid, 
							  precKenorder[idx].asyrckpos, 
							  MYAPP_SEND_SFX, timepos ) ;
			sprintf ( lc_dataFileName_R, "%s/%s", pAppEnv->cDirIA_Dat,lc_fileName_R);
			//	�����I�[�_�[���t�@�C�����쐬
			sFncCreFileName ( lc_fileName_K, MYAPP_SEND_KIND_OD, 
							  precKenorder[idx].asyrckid, 
							  precKenorder[idx].asyrckpos, 
							  MYAPP_SEND_SFX, timepos ) ;
			sprintf ( lc_dataFileName_K, "%s/%s", pAppEnv->cDirIA_Dat,lc_fileName_K);
			sprintf ( lc_idxFileName,  "%s/%s", pAppEnv->cDirIA_Idx,lc_fileName_K);

			/***
			 ***	�t�@�C���I�[�v��	
			 ***/
			//	�����`�F�b�N���t�@�C��
			lfp_R  = fopen ( lc_dataFileName_R , "w" ) ;
			if ( lfp_R == NULL ) {
				//	�ُ�I��	LOG
				gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "fopen", __LINE__,
			 	 	 		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 		"�t�@�C���̃I�[�v���Ɏ��s���܂���[%s]",lc_dataFileName_R);
				return ( -1 ) ;
			}
			//	�����I�[�_�[���t�@�C��
			lfp_K  = fopen ( lc_dataFileName_K , "w" ) ;
			if ( lfp_K == NULL ) {
				//	�ُ�I��	LOG
				gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "fopen", __LINE__,
			 	 	 		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 		"�t�@�C���̃I�[�v���Ɏ��s���܂���[%s]",lc_dataFileName_K);
				return ( -1 ) ;
			}
		}
		
		/***
		 ***	�f�[�^�o��
		 ***/
		//	�����`�F�b�N��񃌃R�[�h�쐬
		if ( sFncOutRecREALCHK ( lfp_R, lc_recBuf_R, &precRealchk[idx] ) < 0 ) {
			//	�ُ�I��	LOG
			gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOutRecREALCHK", __LINE__,
			 	 	 	EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 	"�t�@�C���̏o�͂Ɏ��s���܂���[%s]", lc_dataFileName_R ) ;
			return ( -1 ) ;
		}
		//	�����I�[�_�[��񃌃R�[�h�쐬
		if ( sFncOutRecKENORDER ( lfp_K, lc_recBuf_K, &precKenorder[idx] ) < 0 ) {
			//	�ُ�I��	LOG
			gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOutRecKENORDER", __LINE__,
			 	 	 	EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 	"�t�@�C���̏o�͂Ɏ��s���܂���[%s]", lc_dataFileName_K ) ;
			return ( -1 ) ;
		}
	}

	/***
	 ***	�t�@�C���o�͌㏈��
	 ***/
	//	�t�@�C���N���[�Y
	if ( lfp_R != NULL ) {
		fclose ( lfp_R ) ;
	}
	if ( lfp_K != NULL ) {
		fclose ( lfp_K ) ;
	}
	//�����I�[�_�[���t�@�C���o��
	lfp_IDX  = fopen ( lc_idxFileName , "w" ) ;
	if ( lfp_IDX == NULL ) {
		//	�ُ�I��	LOG
		unlink ( lc_dataFileName_R ) ;
		unlink ( lc_dataFileName_K ) ;
		gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "fopen", __LINE__,
 	 	 			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
 	 	 			"�t�@�C���̃I�[�v���Ɏ��s���܂���[%s]", 
					lc_idxFileName ) ;
		return ( -1 ) ;
	}
	fclose ( lfp_IDX ) ;

	return ( 0 ) ;
}
/******************************************************************************/
/*  �� �� ���@�FsFncTrFileRead()			 								  */
/*  �@�\�T�v�@�F�g���[�E���b�N�R�t�����Ǎ�				  	 			  */
/*	���L����  �F��Q������free												  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����		 	          */
/*�@ ��Q���� �Fchar *  	 		�g���[�E���b�N�R�t�����t�@�C����	      */
/*�@ ��R���� �Fstruct trInfo *   	�g���[�E���b�N�R�t�����i�[�\����    	  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/*					 1	�f�[�^�ُ�											  */
/******************************************************************************/
static	int
sFncTrFileRead ( pAppEnv, pc_trFileName, pst_trInfo )
struct appEnv	*pAppEnv ;
char			*pc_trFileName ;
struct trInfo	*pst_trInfo ;
{
	FILE	*lfp ;
	char	 lc_recBuf[MYAPP_RECV_RECSIZE] ;
	int	 	 li_recBuflen;
	char	*lpc_recBuf ;
	char	*lpc_Token ;
	char	*lpc_trInfoMem[MYAPP_RECV_COLCNT] ;
	int		 li_tokenCnt ;
	int		 li_rackCnt ;
	int		 li_retryCnt ;

	char		  lc_fileName[1024] ;
	char		  lc_fileNameBuf[1024] ;
	char		 *pToken ;
	struct stat	  lst_statBuf ;

	/***
	 ***	�t�@�C�������`�F�b�N
	 ***/
	//	�t�@�C�����쐬
	sprintf ( lc_fileName, "%s/%s", pAppEnv->cDirNR_Sup, pc_trFileName ) ;
	//	�t�@�C�������擾
	if ( stat ( lc_fileName, &lst_statBuf ) < 0 ) {
			//	�ُ�I��	LOG
			gintErrorCode = MYAPP_STSCODE_ERR_DIR;
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "stat", __LINE__,
				 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 	 "�t�@�C�������̎擾�Ɏ��s���܂���[%s]", lc_fileName ) ;
			return ( -1 ) ;
	}
	//	�ʏ�t�@�C���ȊO�͏������s��Ȃ�
	if ( !S_ISREG ( lst_statBuf.st_mode ) ) {
			return ( 2 ) ;
	}

	/***
	 ***	�Ǎ�����
	 ***/
	//	�t�@�C���I�[�v��	
	li_retryCnt = 0 ;
	while ( li_retryCnt  < pAppEnv->fileRetry ) {
		lfp  = fopen ( lc_fileName, "r" ) ;
		if ( lfp == NULL ) {
			li_retryCnt ++ ;
			continue ;
		}
	
		//	�ǂݍ��݁i�P�s�̂݁j
		if ( fgets ( lc_recBuf, sizeof ( lc_recBuf ), lfp ) == NULL ) {
			fclose ( lfp ) ;
			li_retryCnt ++ ;
			continue ;
		}
		
		//	�t�@�C���N���[�Y	
		fclose ( lfp ) ;
		break ;
	}
	if ( li_retryCnt == pAppEnv->fileRetry ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncTrFileRead", __LINE__,
		 	 	 	EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		 	 	 	"�t�@�C���̓ǂݍ��݂Ɏ��s���܂���[%s]", lc_fileName ) ;
		return ( -1 ) ;
	}

	//	���s�R�[�h�u��
	li_recBuflen = strlen ( lc_recBuf ) ;
	if ( lc_recBuf[li_recBuflen-2] == '\r' ) {
		lc_recBuf[li_recBuflen-2] = '\0' ;
	}
	if ( lc_recBuf[li_recBuflen-1] == '\n' ) { 
		lc_recBuf[li_recBuflen-1] = '\0' ;
	}

	//	�g�[�N������
	memset ( lpc_trInfoMem, '\0', sizeof ( lpc_trInfoMem ) )  ;
	lpc_recBuf = lc_recBuf ;
	for ( li_tokenCnt = 0 ; li_tokenCnt < MYAPP_RECV_COLCNT ; li_tokenCnt ++ ) {
		lpc_Token = sFncTrFileToken ( lpc_recBuf ) ;
		//lpc_Token = strtok ( lpc_recBuf, "," ) ;
		if ( lpc_Token == NULL ) {
			break ;
		}
		if ( lpc_recBuf != NULL ) {
			lpc_recBuf = NULL ;
		}
		lpc_trInfoMem[li_tokenCnt] = lpc_Token ;
	}

	//	�g�[�N�����`�F�b�N�i�Q�R�ȊO�̓t�@�C���ُ�j
	if ( li_tokenCnt != MYAPP_RECV_COLCNT ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "fgets", __LINE__,
			 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 "�t�H�[�}�b�g�Ɍ�肪����܂�[%s]", lc_fileName ) ;
		return ( -1 ) ;
	}

	//	�\���̐ݒ�
	li_tokenCnt = 0 ;
	li_rackCnt = 0 ;
	memset ( pst_trInfo, '\0', sizeof ( struct trInfo ) ) ;
	while ( li_tokenCnt  < MYAPP_RECV_COLCNT ) {
		if ( li_tokenCnt == 0 ) {	//�g���[�m�n
			strcpy ( pst_trInfo->trid, lpc_trInfoMem[li_tokenCnt] ) ;
			sFncTrim ( pst_trInfo->trid ) ;
		}
		else 
		if ( li_tokenCnt == 1 ) {	//�����J�n��
			strcpy ( pst_trInfo->knskisymd, lpc_trInfoMem[li_tokenCnt] ) ;
			sFncTrim ( pst_trInfo->knskisymd ) ;
		}
		else 
		if ( li_tokenCnt == 22 ) {	//��������
			strcpy ( pst_trInfo->createDate, lpc_trInfoMem[li_tokenCnt] ) ;
			sFncTrim ( pst_trInfo->createDate ) ;
		}
		else {
			strcpy ( pst_trInfo->asyrckid[li_rackCnt], lpc_trInfoMem[li_tokenCnt] ) ;
			sFncTrim ( pst_trInfo->asyrckid[li_rackCnt] ) ;
			li_rackCnt++ ;
		}
		li_tokenCnt++ ;
	}

	/***
	 ***	�X�g�b�J�[�m�n�擾
	 ***		�t�@�C�������擾	
	 ***/
	strcpy ( lc_fileNameBuf, &pc_trFileName[ strlen ( MYAPP_RECV_KIND ) ] ) ;
	if ( ( pToken = strtok ( lc_fileNameBuf, "_" ) ) != NULL ) {
		memcpy ( pst_trInfo->stkno, pToken, sizeof ( pst_trInfo->stkno ) - 1 ) ;
	}


	return ( 0 ) ;
}
/******************************************************************************/
/*  �� �� ���@�FsFncPutLog()  			 									  */
/*  �@�\�T�v�@�F�A�v���P�[�V�������O�o��					  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *   	�ҏW������								 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F����														  */
/******************************************************************************/
void
sFncPutLog ( LOG_TRCKIND peTrcKind, char * pcSrcName, char * pcFncName, int plLineNo, char * pcExeFlg, char * pcErrCode, char * pcfmt, ... ) 
{
	va_list	 ap ;
	char	 cMsg[1024] ;

	/***
	 ***	���O�����l�ݒ�
	 ***/
	gstLogMem.eTrcKind = peTrcKind ;
	//strcpy ( gstLogMem.pcSrcName, pcSrcName ) ;
	strcpy ( gstLogMem.pcFncName, pcFncName ) ;
	//gstLogMem.lLineNo = plLineNo ;
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
/******************************************************************************/
/*  �� �� ���@�FsFncOutRecKENORDER()		 								  */
/*  �@�\�T�v�@�F�����I�[�_����񃌃R�[�h����				  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��Q���� �Fstruct my_stKENORDER *   	�����I�[�_���\����		      */
/*  �o�@�@�́@�F                                                              */
/*�@ ��P���� �Fchar 				*   	���R�[�h�i�[�o�b�t�@			  */
/*  ���A���@�F����														  */
/******************************************************************************/
static	int
sFncOutRecKENORDER ( pfp, p_recBuf, precKenorder )
FILE					*pfp ;
char					*p_recBuf ;
struct my_stKENORDER	*precKenorder ;
{
	int		retSts ;
	//	���R�[�h�쐬
	retSts = fprintf ( pfp, "%s,%s,%s,%s,%s,%s,%hd,%hd,%s,%s,%s,%s,%s,%s,%hd,%s,%s,%hd,%s,%hd,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%hd,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%ld,%hd,%s,%s\n",
				precKenorder->knskisymd,
				precKenorder->sriymd,
				precKenorder->kntno,
				precKenorder->kntketflg,
				precKenorder->knsgrp,
				precKenorder->kmkcd,
				precKenorder->knssu,
				precKenorder->knssueda,
				precKenorder->irihsmkbn,
				precKenorder->irikbn,
				precKenorder->ksktkbn,
				precKenorder->utkymd,
				precKenorder->irino,
				precKenorder->iriketflg,
				precKenorder->zssdino,
				precKenorder->sstcd,
				precKenorder->trid,
				precKenorder->trpos,
				precKenorder->asyrckid,
				precKenorder->asyrckpos,
				precKenorder->oyakmkcd,
				precKenorder->seccd,
				precKenorder->bkfkkbn,
				precKenorder->smpcd,
				precKenorder->bskkbn,
				precKenorder->nbkmkcd,
				precKenorder->zrcd,
				precKenorder->ysnlbl,
				precKenorder->kjno,
				precKenorder->fkhkknohjkbn,
				precKenorder->tbkjno,
				precKenorder->tbkjflg,
				precKenorder->htkfkhms,
				precKenorder->skflg,
				precKenorder->tskflg,
				precKenorder->tktflg,
				precKenorder->ytiksbr,
				precKenorder->kkflg,
				precKenorder->kkiriflg,
				precKenorder->kkirilotno,
				precKenorder->sc,
				precKenorder->tj,
				precKenorder->tjtni,
				precKenorder->sbtkbn,
				precKenorder->birthday,
				precKenorder->birthdaykbn,
				precKenorder->age,
				precKenorder->agekbn,
				precKenorder->sstme,
				precKenorder->ssymd,
				precKenorder->tntme,
				precKenorder->tntni,
				precKenorder->tnryo,
				precKenorder->tnryotni,
				precKenorder->knsseq,
				precKenorder->bthno,
				precKenorder->knsjkflg,
				precKenorder->ksndh ) ;
	if ( retSts < 0 ) {
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncCreRecREALCHK()			 								  */
/*  �@�\�T�v�@�F�����`�F�b�N��񃌃R�[�h����				  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��Q���� �Fstruct my_stREALCHK *   	�����`�F�b�N���\����		      */
/*  �o�@�@�́@�F                                                              */
/*�@ ��P���� �Fchar 				*   	���R�[�h�i�[�o�b�t�@			  */
/*  ���A���@�F����														  */
/******************************************************************************/
static	int
sFncOutRecREALCHK ( pfp, p_recBuf, precRealchk )
FILE					*pfp ;
char					*p_recBuf ;
struct my_stREALCHK		*precRealchk ;
{

	int		retSts ;
	//	���R�[�h�쐬
	retSts = fprintf ( pfp, "%s,%s,%s,%s,%s,%s,%hd,%hd,%s,%s,%s,%hd,%s,%hd,%s,%hd,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%.256s,%.256s,%.256s,%.256s,%.256s,%.256s,%.256s,%.1024s,%.256s,%.256s,%.256s,%.256s,%.256s,%.256s,%.256s,%.256s,%.256s,%.256s,%.256s,%.256s,%s\n",
				precRealchk->knskisymd,
				precRealchk->sriymd,
				precRealchk->kntno,
				precRealchk->kntketflg,
				precRealchk->knsgrp,
				precRealchk->kmkcd,
				precRealchk->knssu,
				precRealchk->knssueda,
				precRealchk->utkymd,
				precRealchk->irino,
				precRealchk->iriketflg,
				precRealchk->zssdino,
				precRealchk->trid,
				precRealchk->trpos,
				precRealchk->asyrckid,
				precRealchk->asyrckpos,
				precRealchk->bskkbn,
				precRealchk->nbkmkcd,
				precRealchk->renjicflg,
				precRealchk->soukn1flg,
				precRealchk->kanrenflg,
				precRealchk->bunkkuflg,
				precRealchk->kesseiflg,
				precRealchk->rirekiflg,
				precRealchk->syougoflg,
				precRealchk->keisanflg,
				precRealchk->per100flg,
				precRealchk->tousekflg,
				precRealchk->kisyakflg,
				precRealchk->kouseiflg,
				precRealchk->syoungflg,
				precRealchk->soukn2flg,
				precRealchk->fukaptflg,
				precRealchk->yobiflg01,
				precRealchk->tobiflg02,
				precRealchk->yobiflg03,
				precRealchk->yobiflg04,
				precRealchk->yobiflg05,
				precRealchk->renjicpara.data,
				precRealchk->soukn1para.data,
				precRealchk->kanrenpara.data,
				precRealchk->bunkkupara.data,
				precRealchk->kesseipara.data,
				precRealchk->rirekipara.data,
				precRealchk->syougopara.data,
				precRealchk->keisanpara.data,
				precRealchk->per100para.data,
				precRealchk->tousekpara.data,
				precRealchk->kisyakpara.data,
				precRealchk->kouseipara.data,
				precRealchk->syoungpara.data,
				precRealchk->soukn2para.data,
				precRealchk->fukaptpara.data,
				precRealchk->yobipara01.data,
				precRealchk->yobipara02.data,
				precRealchk->yobipara03.data,
				precRealchk->yobipara04.data,
				precRealchk->yobipara05.data,
				precRealchk->ksndh ) ;
	if ( retSts < 0 ) {
		return ( -1 ) ;
	}
	return ( 0 ) ;
}
/******************************************************************************/
/*  �� �� ���@�FsFncCreFileName()			 								  */
/*  �@�\�T�v�@�F�I�[�_�[�t�@�C��������						  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *   	�t�@�C�����i�[�o�b�t�@					 	      */
/*�@ ��Q���� �Fchar *   	���									 	      */
/*�@ ��R���� �Fchar *   	���b�N�m�n								 	      */
/*�@ ��S���� �Fshort   	�|�W�V����								 	      */
/*�@ ��T���� �Fchar *   	�g���q									 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fchar *														  */
/*					 NULL	�I�[											  */
/*					 NULL�ȊO	������										  */
/******************************************************************************/
static	void
sFncCreFileName ( pc_fileName, pc_kind, pc_asyrckid, ps_pos, pc_sfx, pst_timepos )
char				*pc_fileName ;
char				*pc_kind ;
char				*pc_asyrckid ;
short				 ps_pos ;
char				*pc_sfx ;
struct tm			*pst_timepos ;
{
	
	char	lc_asyrckid[MYAPP_RKNO_SIZE] ;	
	char	lc_asyrckidBuf[MYAPP_RKNO_SIZE] ;	
	
	//	���b�N�m�n�ҏW
	memset ( lc_asyrckid, '\0', sizeof ( lc_asyrckid ) ) ;
	memset ( lc_asyrckid, '_', sizeof ( lc_asyrckid ) - 1 ) ;
	strcpy ( lc_asyrckidBuf, pc_asyrckid ) ;
	sFncTrim ( lc_asyrckidBuf ) ;
	memcpy ( lc_asyrckid, lc_asyrckidBuf, strlen ( lc_asyrckidBuf ) ) ;

		
	//	�t�@�C�����쐬
	sprintf ( pc_fileName, "%s_%s%03d%s",
						pc_kind,
						lc_asyrckid,
						ps_pos,
						pc_sfx ) ;
/*****	���I�[�_�t�@�C����
	sprintf ( pc_fileName, "%s_%02d%02d%02d%02d%02d%02d_%s%03d%s",
						pc_kind,
						( pst_timepos->tm_year + 1900 ) % 100,
						pst_timepos->tm_mon + 1,
						pst_timepos->tm_mday,
						pst_timepos->tm_hour,
						pst_timepos->tm_min,
						pst_timepos->tm_sec,
						lc_asyrckid,
						ps_pos,
						pc_sfx ) ;
*****/
	return ;
}
/******************************************************************************/
/*  �� �� ���@�FsFncTrFileToken()			 								  */
/*  �@�\�T�v�@�F�g�[�N������								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *   	������									 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fchar *														  */
/*					 NULL	�I�[											  */
/*					 NULL�ȊO	������										  */
/******************************************************************************/
static	char*
sFncTrFileToken ( pString )
char	*pString ;
{
	char	*p ;
	char	*pRet ;
	int		 liIdx ;

	//	����������|�C���^�[�ݒ�
	if ( pString == NULL ) {
		p = gpToken ;	
	}
	else {
		gpToken = pString ;
		p = pString ;	
	}

	//	�I�[�`�F�b�N�i�ŏI�J���}�ȍ~���Ō�̒l�Ǝ擾���邽�߁j	
	if ( p == NULL ) {
		return ( NULL ) ;
	}

	//	�g�[�N������
	gpToken = NULL ;	//�ŏI�J���}�ȍ~���Ō�̒l�Ǝ擾���邽��
	pRet = p ;
	while ( *p ) {
		if ( *p == ',' ) {
			*p  = '\0' ;
			gpToken =  p + 1 ;
			break  ;
		}	
		p++ ;
	}
	return ( pRet ) ;
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
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "rename", __LINE__,
 	 	 			 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
 	 	 			 "�t�@�C���̈ړ��Ɏ��s���܂���[%s->%s]", lc_fromPath, lc_toPath ) ;
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
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmget", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "���L�������̑���Ɏ��s���܂���" ) ;
		return ( -1 ) ;
	}

	//	�A�^�b�`	
	shmData = ( int * ) shmat ( pAppEnv->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
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
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
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
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
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
		//sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmctl", __LINE__,
		//		 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		//		 	 "���L�������̑���Ɏ��s���܂���" ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}	
/******************************************************************************/
/*  �� �� ���@�FsFncFileCompar()			 								  */
/*  �@�\�T�v�@�F�t�@�C������r�y�R�[���o�b�N�֐��z			  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *   	��r������								 	      */
/*�@ ��Q���� �Fchar *   	��r������								 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/******************************************************************************/
static	int
sFncFileCompar ( a, b ) 
struct dirent	**a ;
struct dirent	**b ;
{
		char	*p1 ;
		char	*p2 ;

		p1 = strchr ( (*a)->d_name, '_' ) ;
		if ( p1 == NULL ) {
			p1 = (*a)->d_name ;
		}
		p2 = strchr ( (*b)->d_name, '_' ) ;
		if ( p2 == NULL ) {
			p2 = (*b)->d_name ;
		}
		return ( strcoll ( p1, p2 ) ) ;
		
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
					  MYAPP_RECV_KIND, 
					  strlen ( MYAPP_RECV_KIND ) ) != 0 ) {
			return ( 0 ) ;
		}
		//�g���q�`�F�b�N
		if ( memcmp ( &(pdirEnt->d_name[li_len-strlen(MYAPP_RECV_SFX)]), 
					  MYAPP_RECV_SFX, 
					  strlen ( MYAPP_RECV_SFX ) ) != 0 ) {
			return ( 0 ) ;
		}
		return ( 1 ) ;
}
/******************************************************************************/
/*  �� �� ���@�F_sFncEnvDip()				 								  */
/*  �@�\�T�v�@�F�v���O�������ϐ��o�͊֐��y�g���[�X�p�z	  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����			 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F����														  */
/******************************************************************************/
static void
_sFncEnvDip( pAppEnv )
struct appEnv	*pAppEnv ;
{
#if defined ( _TRACE )
	loging ( "########## Stocker - _sFncEnvDip ##########\n" ) ;
	loging ( "\t�y���L�f�B���N�g���z\n" ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_NR_SUP,     pAppEnv->cDirNR_Sup ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_NR_SUP_OK,  pAppEnv->cDirNR_SupOk ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_NR_SUP_ERR, pAppEnv->cDirNR_SupErr ) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_NR_COL,     pAppEnv->cDirNR_Col ) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_NR_COL_OK,  pAppEnv->cDirNR_ColOk ) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_NR_COL_ERR, pAppEnv->cDirNR_ColErr ) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_NR_LOG,     pAppEnv->cDirNR_Log ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_IA_DAT,     pAppEnv->cDirIA_Dat ) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_IA_DAT_OK,  pAppEnv->cDirIA_DatOk ) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_IA_DAT_ERR, pAppEnv->cDirIA_DatErr ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_IA_IDX,     pAppEnv->cDirIA_Idx ) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_IA_IDX_OK,  pAppEnv->cDirIA_IdxOk ) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_IA_IDX_ERR, pAppEnv->cDirIA_IdxErr ) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_IA_LOG,     pAppEnv->cDirIA_Log ) ;
	loging ( "\t%s : [%d]\n", MYAPP_PRM_SHM_KEY,        pAppEnv->shm_Key ) ;
	loging ( "\t%s : [%d]\n", MYAPP_PRM_SLEEP_SEC,      pAppEnv->sleep_Sec ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DB_NAME,        pAppEnv->cDb_Name ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DB_USER,        pAppEnv->cDb_User ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DB_PASSWD,      pAppEnv->cDb_Passwd ) ;
	loging ( "########## Stocker - _sFncEnvDip ##########\n" ) ;
#endif
}
/******************************************************************************/
/*  �� �� ���@�F_sFncTrInfoDisp()			 								  */
/*  �@�\�T�v�@�F�g���[���b�N�R�t�����\���̏o�͊֐��y�g���[�X�p�z  		  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct trInfo *   	�g���[���b�N�R�t�����\���́B	 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F����														  */
/******************************************************************************/
static void
_sFncTrInfoDisp ( pst_trInfo )
struct trInfo	*pst_trInfo ;
{
#if defined ( _TRACE )
	int li_rackCnt ;
	loging ( "########## Stocker - _sFncTrInfoDisp ##########\n" ) ;
	loging ( "�X�g�b�J�[  :[%s]\n",pst_trInfo->stkno ) ;
	loging ( "�g���[�m�n  :[%s]\n",pst_trInfo->trid ) ;
	loging ( "�����J�n��  :[%s]\n",pst_trInfo->knskisymd ) ;
	for ( li_rackCnt = 0 ; li_rackCnt < MYAPP_RACK_MAXCNT ; li_rackCnt++ ) {
		loging ( "���b�N�m�n%02d:[%s]\n",li_rackCnt+1, pst_trInfo->asyrckid[li_rackCnt] ) ;
	}
	loging ( "��������    :[%s]\n",pst_trInfo->createDate ) ;
	loging ( "########## Stocker - _sFncTrInfoDisp ##########\n" ) ;
#endif
}

/****************************************************************************/
/*  �� �� ���@�FinsWsseqknri()												*/
/*  �@�\�T�v�@�F����WS�̏����e�[�u���ɓo�^����							*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �F															*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
int insWsseqknri( char *sSriymd, char *sKnsgrp, char *sTrid, int iKntsu, int iMinSeq, int iMaxSeq )
{
	int num;
	struct	my_stWSSEQKNRI	strWsSeq ;
	long lRet;
	char	buf[10];

	//���[�N�V�[�g�r�d�p�Ǘ����̌������擾����
	if( (lRet = sFncSelWSSEQKNRI( &num ) ) < 0 ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "insWsseqknri", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"WSSEQKNRI SELECT(ALL) ERROR SQLCODE(%d)", lRet );
		return( -1 );
	}

	//�f�[�^�̃Z�b�g
	memset(&strWsSeq, 0, sizeof(strWsSeq));
	strWsSeq.wstbnknr = num+1;
	memcpy(strWsSeq.knskisymd, sSriymd, sizeof(strWsSeq.knskisymd)-1);
	memcpy(strWsSeq.knsgrp, sKnsgrp, sizeof(strWsSeq.knsgrp)-1);
	memcpy(strWsSeq.wssbt, sTrid, 4);
	memset(buf, 0, sizeof(buf));
	memcpy(buf, &sTrid[4], 4);
	strWsSeq.wsno = atoi(buf);
	strWsSeq.knsseqst = iMinSeq;
	strWsSeq.knsseqed = iMaxSeq;
	strWsSeq.knsseqsu = iKntsu;
	strcpy(strWsSeq.dtnrtts, "DEAMON");
	strWsSeq.ksktkbn = 'A';

	if( (lRet = sFncInsWSSEQKNRI( &strWsSeq )) < 0 ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "insWsseqknri", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"WSSEQKNRI INSERT ERROR! SQLCODE(%d) �v�r�Ǘ��ʔ�(%d) �g���[ID(%s)", lRet, strWsSeq.wstbnknr, sTrid );
		return( -1 );
	}
	
	ZdbCommit();

	return( 0 );
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

	/***
	 ***    �o�b�N�O���E���h���s
	 ***/
//	if ( daemon ( 0, 1 ) < 0 ) {
	if ( daemon ( 0, 1 ) < 0 ) {
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                 "daemon�N�����s" ) ;
		exit ( 9 ) ;
	}



	/***
	 ***	��������	
	 ***/
	if ( initFunction ( argc, argv, &sAppEnv )  != 0 ) {
		endFunction ( &sAppEnv ) ;
		exit ( 9 ) ;
	}
_sFncEnvDip ( &sAppEnv ) ;
	
	/***
	 ***	�又��	
	 ***/
	if ( mainFunction ( &sAppEnv )  != 0 ) {
		endFunction ( &sAppEnv ) ;
		exit ( 9 ) ;
	}

	/***
	 ***	�I������	
	 ***/
	endFunction ( &sAppEnv ) ;
}

/** End of File ***************************************************************/
