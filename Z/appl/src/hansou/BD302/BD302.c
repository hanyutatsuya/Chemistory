/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FBD302.c                                                      */
/* �@�T�@�@�@�v�F�X�g�b�J�[�y����z                                           */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/15     �F��O�K       �V�K�쐬                           */
/*  1.01     2006/12/06   YOON JONG JIN    �G���[�ǉ�                         */
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

#include "BD302.h"

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

//	�t�@�C���폜
static	void	sDelOrderFile ( char *, char *, char *, char * ) ;


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
     ***    �����`�F�b�N
     ***/
	if ( argc != 2 ) {
		fprintf ( stderr, "%s : There is an error in a command parameter\n", MYAPP_APP_NAME ) ;
		return ( -1 ) ;
	}

	/***
	 ***	���O�I�[�v��
	 ***/
	if ( ZbmlOpenLog ( argv[1] ) != 0 ) {
		return ( -1 ) ;
	}

	//	���O��񏉊��ݒ�
	memset ( &gstLogMem, '\0', sizeof ( gstLogMem ) ) ;
	if ( ( lc_login = getenv( "LOGNAME" ) ) != NULL ) {
		strcpy ( gstLogMem.pcLoginId, lc_login ) ;
	}
	strcpy ( gstLogMem.pcAppName, MYAPP_APP_NAME ) ;

	//	�J�n���O�o��
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__,
				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "�v���O�����N��" ) ;

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

	//	��M���
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_NR_COL,
						pAppEnv->cDirNR_Col ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_NR_COL ) ;
		return ( -1 ) ;
	}
	//	��M�������
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_NR_COL_OK, 
						pAppEnv->cDirNR_ColOk ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_NR_COL_OK ) ;
		return ( -1 ) ;
	}
	//	��M����G���[
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_NR_COL_ERR, 
						pAppEnv->cDirNR_ColErr ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_NR_COL_ERR ) ;
		return ( -1 ) ;
	}
	//	�I�[�_���
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_IA_DAT, 
						pAppEnv->cDirIA_Dat ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_IA_DAT ) ;
		return ( -1 ) ;
	}
	//	�I�[�_�[��񊮗�
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_IA_IDX, 
						pAppEnv->cDirIA_Idx ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_IA_IDX ) ;
		return ( -1 ) ;
	}
	//	���O
//DEL	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_NR_LOG, 
//DEL						pAppEnv->cDirNR_Log ) != 0 ) {
//DEL		//	�ُ�I��	LOG
//DEL		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
//DEL		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
//DEL				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//DEL				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_NR_LOG ) ;
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
//DEL	gtSystemVersion = MYAPP_SYSTEM_NEW ;
//DEL	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_VERSION, 
//DEL						pAppEnv->cVersion ) != 0 ) {
//DEL		gtSystemVersion = MYAPP_SYSTEM_OLD ;
//DEL	}

	//	�p�����[�^�t�@�C���N���[�Y	
	ZbmlPrmClose ( pAppEnv->bp ) ;

	/***
	 ***	���L����������	
	 ***/
	if ( sFncShmCrt ( pAppEnv ) < 0 ) {
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
	 ***	��M�g���[�E���b�N����f�B���N�g���Ď�	
	 ***		�i�v���[�v
	 ***		��~�R�}���h�ŏI��
	 ***/
	while ( 1 ) {

		/***
		 *** �t�@�C�����擾
		 ***/
		if ( ( li_fileCnt = scandir ( pAppEnv->cDirNR_Col, 
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
			li_retSts=sFncTrFileRead ( pAppEnv,lpst_dirBuf[li_idx]->d_name, &lst_trInfo ) ;
			if ( li_retSts < 0 ) {
				//	�G���[�f�B���N�g���Ɉړ�
				sFncFileRename ( pAppEnv->cDirNR_Col, 
							     lpst_dirBuf[li_idx]->d_name,
								 pAppEnv->cDirNR_ColErr,
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

			//	���o��
			li_retSts = sFncOutput ( pAppEnv, &lst_trInfo ) ;
			if ( li_retSts == 0 ) {
				//	���ǃf�B���N�g���Ɉړ�
				sFncFileRename ( pAppEnv->cDirNR_Col, 
								 lpst_dirBuf[li_idx]->d_name,
								 pAppEnv->cDirNR_ColOk,
								 lpst_dirBuf[li_idx]->d_name ) ;
			} else {
				//2006-12-15 YOON
				if ( li_retSts != 2 ) {
					//	�G���[�f�B���N�g���Ɉړ�
					sFncFileRename ( pAppEnv->cDirNR_Col,
                             lpst_dirBuf[li_idx]->d_name,
                             pAppEnv->cDirNR_ColErr,
                             lpst_dirBuf[li_idx]->d_name ) ;
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__,
				 		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 		"[[DB ERROR]] �v���Z�X�I��" ) ;
		
					return 0;						
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
					break ;
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
	 ***	���O�N���[�X
	 ***/
	//	�J�n���O�o��
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
	int						 recCnt ;
	LC_BOOLEAN				 blnErrFlg ;
	LC_BOOLEAN               blnLockFlg ;
	
	/***
	 ***	�ϐ�������
	 ***/
	recCnt = 0 ;
	blnErrFlg 	= LC_false ;
	blnLockFlg  = LC_false ;
	li_Return = 0 ;
	
	//	��{�����L�[�ݒ�
	sprintf ( cSel_knskisymd, "%4.4s-%2.2s-%2.2s", 
					  		  pst_trInfo->knskisymd, 
					  		  &(pst_trInfo->knskisymd[4]), 
					  		  &(pst_trInfo->knskisymd[6]) ) ;
	
	/***
	 ***	���C������
	 ***/
	for ( li_idx = 0 ; li_idx < MYAPP_RACK_MAXCNT ; li_idx++ ) {
		//	�u�����N�͏������s��Ȃ�
		if ( pst_trInfo->asyrckid[li_idx][0] == '\0' ) {
			continue ;
		}

		blnErrFlg = LC_false ;

		/***
		 ***	�X�V
		 ***/
		//	���̃|�W�V�������ǉ�
		li_retSts = sFncInsKENPOS ( cSel_knskisymd,
									pst_trInfo->asyrckid[li_idx],
									pst_trInfo->trid,
									pst_trInfo->stkno,
									li_idx ) ;
		
           	//2006-12-16 YOON 
		if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
        {	//�f�b�h���b�Nor�d��
			    blnLockFlg = LC_true ;
		}
		else if ( li_retSts < 0 ) {
			blnErrFlg = LC_true ;
			//break ;
		}

		//	�����I�[�_�[���X�V
		li_retSts = sFncUpdKENORDER ( cSel_knskisymd,
										  pst_trInfo->asyrckid[li_idx] ) ;
		//2006-12-16 YOON 
        if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
        {   //�f�b�h���b�Nor�d��
                blnLockFlg = LC_true ;
        }		
		if ( li_retSts < 0 ) {
			blnErrFlg = LC_true ;
			//break ;
		}

		//	Z�T�[�o�I�[�_�[���폜
/*		
		sDelOrderFile( pAppEnv->cDirIA_Dat, 
					   pst_trInfo->asyrckid[li_idx], 
					   MYAPP_SEND_KIND_OD, MYAPP_SEND_SFX ) ;
		sDelOrderFile( pAppEnv->cDirIA_Dat, 
					   pst_trInfo->asyrckid[li_idx], 
					   MYAPP_SEND_KIND_CH, MYAPP_SEND_SFX ) ;
		sDelOrderFile( pAppEnv->cDirIA_Idx, 
					   pst_trInfo->asyrckid[li_idx], 
					   MYAPP_SEND_KIND_OD, MYAPP_SEND_SFX ) ;
*/

		/***
	 	 ***    �g�����U�N�V�����I��
	  	 ***    �����I�[�_���̂݃g�����U�N�V�����I��
	 	 ***    ADD NO.14 2006/05/26
	 	 ***/
		if ( blnLockFlg == LC_true) {
            //  ���[���o�b�N
            ZdbRollback () ;
        }
        else if(blnErrFlg == LC_true){
            ZdbRollback () ;
            break;
        } else {
            //  �R�~�b�g
            ZdbCommit () ;
        }
	} 

	/***
	 ***	�g���[�Ǘ����X�V
	 ***/
	li_retSts = sFncUpdTRAYKNRI ( cSel_knskisymd,
							  	  pst_trInfo->trid,
							  	  pst_trInfo->stkno ) ;
	if ( li_retSts < 0 ) {
		//  ���[���o�b�N
		ZdbRollback () ;
	} else {
		//  �R�~�b�g
		ZdbCommit () ;
	}


	/***
	 ***	�g�����U�N�V�����I��
	 ***/
	if ( blnLockFlg == LC_true ) {
        return ( 2 ) ;
    }
	if ( blnErrFlg == LC_true ) {
		return ( -1 ) ;
	}
	
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
	FILE		 *lfp ;
	char	 	  lc_recBuf[MYAPP_RECV_RECSIZE] ;
	int	 	 	  li_recBuflen;
	char		 *lpc_recBuf ;
	char		 *lpc_Token ;
	char		 *lpc_trInfoMem[MYAPP_RECV_COLCNT] ;
	int		 	  li_tokenCnt ;
	int	 		  li_rackCnt ;
	int			  li_retryCnt ;
	char		  lc_fileName[1024] ;
	char		  lc_fileNameBuf[1024] ;
	char		 *pToken ;
	struct stat	  lst_statBuf ;

	/***
	 ***	�t�@�C�������`�F�b�N
	 ***/
	//	�t�@�C�����쐬
	sprintf ( lc_fileName, "%s/%s", pAppEnv->cDirNR_Col, pc_trFileName ) ;
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
		gintErrorCode = MYAPP_STSCODE_ERR_TR_FILE ;
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
		gintErrorCode = MYAPP_STSCODE_ERR_TR_FILE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "fgets", __LINE__,
			 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 "�t�H�[�}�b�g�Ɍ�肪����܂�[%s]", lc_fileName ) ;
		return ( -1 ) ;
	}

	//	�\���̐ݒ�
	li_tokenCnt = 0 ;
	li_rackCnt = 0 ;
	memset ( pst_trInfo, '\0', sizeof ( struct trInfo ) ) ;
	while ( li_tokenCnt  < MYAPP_RACK_MAXCNT + 3 ) {
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
/*  �� �� ���@�FsDelOrderFile() 		 									  */
/*  �@�\�T�v�@�FZ�T�[�o�̃I�[�_�[�t�@�C�������폜����						  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *   	�ҏW������								 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F����														  */
/******************************************************************************/
static	void
sDelOrderFile( pc_dir, pc_asyrckid, pc_kind, pc_sfx )
char	*pc_dir ;
char	*pc_asyrckid ;
char	*pc_kind ;
char	*pc_sfx ;
{

	char    lc_Path[MYAPP_PATH_SIZE] ;
	char    lc_command[1024] ;

	char	lc_asyrckid[MYAPP_RKNO_SIZE] ;
	char	lc_asyrckidBuf[MYAPP_RKNO_SIZE] ;

	//	���b�N�m�n�ҏW
    memset ( lc_asyrckid, '\0', sizeof ( lc_asyrckid ) ) ;
    memset ( lc_asyrckid, '_', sizeof ( lc_asyrckid ) - 1 ) ;
    strcpy ( lc_asyrckidBuf, pc_asyrckid ) ;
    sFncTrim ( lc_asyrckidBuf ) ;
    memcpy ( lc_asyrckid, lc_asyrckidBuf, strlen ( lc_asyrckidBuf ) ) ;

	//  �t�@�C�����쐬
	sprintf ( lc_command, "%s %s/%s_%s001%s",
						MYAPP_COMMAND_RM,
						pc_dir,
						pc_kind,
						lc_asyrckid,
						pc_sfx ) ;
	system ( lc_command ) ;
	sprintf ( lc_command, "%s %s/%s_%s002%s",
						MYAPP_COMMAND_RM,
						pc_dir,
						pc_kind,
						lc_asyrckid,
						pc_sfx ) ;
	system ( lc_command ) ;
	sprintf ( lc_command, "%s %s/%s_%s003%s",
						MYAPP_COMMAND_RM,
						pc_dir,
						pc_kind,
						lc_asyrckid,
						pc_sfx ) ;
	system ( lc_command ) ;
	sprintf ( lc_command, "%s %s/%s_%s004%s",
						MYAPP_COMMAND_RM,
						pc_dir,
						pc_kind,
						lc_asyrckid,
						pc_sfx ) ;
	system ( lc_command ) ;
	sprintf ( lc_command, "%s %s/%s_%s005%s",
						MYAPP_COMMAND_RM,
						pc_dir,
						pc_kind,
						lc_asyrckid,
						pc_sfx ) ;
	system ( lc_command ) ;
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
	loging ( "\t�y���L�f�B���N�g���\���z\n" ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_NR_COL,     pAppEnv->cDirNR_Col ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_NR_COL_OK,  pAppEnv->cDirNR_ColOk ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_NR_COL_ERR, pAppEnv->cDirNR_ColErr ) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_NR_LOG,     pAppEnv->cDirNR_Log ) ;
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
	if ( daemon ( 0, 0 ) < 0 ) {
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
	exit(9);
}

/** End of File ***************************************************************/
