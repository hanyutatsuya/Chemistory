/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FAD108.c                                                      */
/* �@�T�@�@�@�v�F�R�h�c���W�J                                               */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2008/02/12     moriya         �V�K�쐬                           */
/*  1.01     2008/11/13     sekiya         ��܂v�r�̕��я������������Ȃ邱�� */
/*                                         �ɑ΂���Ή�                       */
/*  1.02     2008/12/22     sekiya         SKIP�t�@�C�����o�͂��Ă��鎞�ɁA   */
/*                                         AD107���A�N�Z�X���Ȃ��悤��        */
/*                                         �P�x�Atmp�ɏo�͂��ă��l�[������    */
/*                                         �悤�Ɏd�l��ύX                   */
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

#include "AD108.h"

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
struct stcLogMember		 gstLogMem ;		//	���O�o�͏��

/******************************************************************************/
/* �֐��錾                                                                   */
/******************************************************************************/
//	BUNPOS���W�J�֘A�֐�
static	int		sFncTrFileRead ( struct appEnv *, char *, int * ) ;
/* 1.01 �Ή��̂��߈�����ύX */
static  int     AbunGetSort ( struct appEnv *, char *, char ) ;
static	int		AgetSortInfo( BUNSORT ** ) ;

//	�t�@�C���o�͊֐�
static	int 	sFncOutput ( struct appEnv *, char *, char * ) ;

//	���L����������֐�
static	int		sFncShmCrt ( struct appEnv * ) ;
static	int		sFncShmGet ( struct appEnv * , int *) ;
static	int		sFncShmDel ( struct appEnv * ) ;

//	�R�[���o�b�N�֐�
static	int		sFncFileFillter ( struct dirent * ) ;

//	���̑�
static	void	sFncGetNowdate ( char *, char * ) ;
static	void	sFncGetNowdate1 ( char * ) ;
static	int		sFncFileRename ( char *, char *, char *, char * ) ;
static	void	sFncTrim ( char * ) ;


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

	/***
	 ***	������	
	 ***/
	//	�G���[�X�e�[�^�X�ύX
	gintErrorCode = 0 ;

	//	�v���O�������ϐ�������
	memset ( pAppEnv , '\0', sizeof ( struct appEnv ) ) ;

	/***
	 ***	���O�I�[�v�� (AD108_LOG.ini)
	 ***/
	if ( ZbmlOpenLog ( MYAPP_LOGINIFILE ) != 0 ) {
		return ( -1 ) ;
	}

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

	/***
	 ***	�����`�F�b�N	
	 ***/
	if ( argc != 2 ) {
		gintErrorCode = MYAPP_STSCODE_ERR_USEGE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "initFunction", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�R�}���h�p�����[�^�Ɍ�肪����܂�" ) ;
		return ( -1 ) ;
	}

	/***
	 ***	�p�����[�^�t�@�C�����ޔ�
	 ***/
	//	�p�����[�^�t�@�C�����ޔ� (AD108.ini)
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

	//	BUNPOS�W�J�t�@�C���f�B���N�g��
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_3ID, pAppEnv->cDir3Id ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_3ID ) ;
		return ( -1 ) ;
	}

	//	BUNPOS�W�J�t�@�C��OK�f�B���N�g��
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_3ID_OK, pAppEnv->cDir3IdOk ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_3ID_OK ) ;
		return ( -1 ) ;
	}

	//	BUNPOS�W�J�t�@�C��NG�f�B���N�g��
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_3ID_NG, pAppEnv->cDir3IdNg ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_3ID_NG ) ;
		return ( -1 ) ;
	}

	//	BUNPOS�W�J�t�@�C��SKIP�f�B���N�g��
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_3ID_SKIP, pAppEnv->cDir3IdSkip ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_3ID_SKIP ) ;
		return ( -1 ) ;
	}

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
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DB_NAME, pAppEnv->cDb_Name ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DB_NAME ) ;
		return ( -1 ) ;
	}

	//	�f�[�^�x�[�X���[�U
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DB_USER, pAppEnv->cDb_User ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DB_USER ) ;
		return ( -1 ) ;
	}

	//	�f�[�^�x�[�X�p�X���[�h
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DB_PASSWD, pAppEnv->cDb_Passwd ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DB_PASSWD ) ;
		return ( -1 ) ;
	}

	//	���{�R�[�h
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_LABOCD, pAppEnv->cLbcd ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_LABOCD ) ;
		return ( -1 ) ;
	}

	//	�T�e���C�g�h�c
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_SATECD, pAppEnv->cSateid ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_SATECD ) ;
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

	//	�p�����[�^�t�@�C���N���[�Y	
	ZbmlPrmClose ( pAppEnv->bp ) ;

	// �\�[�g�L�[���̎擾
	if( (pAppEnv->pSortNo = AgetSortInfo(&pAppEnv->pSort)) < 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "AgetSortInfo", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "SORT�L�[��񂪎擾�ł��܂���ł���[%s]", MYAPP_AD105SORTINIFILE ) ;
		return ( -1 ) ;
	}

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
	int				  li_retSts ;
	long			  ll_retSts ;
	int				  li_idx ;	
	int				  li_stopFlg ;
	int				  li_OkSkipFlg ;
	char			  sDttm[128];

	//	�f�B���N�g����� 
	DIR				 *lt_dp ;
	struct dirent	**lpst_dirBuf ;

	//	�w��f�B���N�g�����t�@�C���J�E���g
	int				  li_fileCnt ;

	/***
	 ***	BUNPOS�t�@�C�����W�J����
	 ***		�i�v���[�v
	 ***		��~�R�}���h�ŏI��
	 ***/
	while ( 1 ) {

		/***
		 *** �t�@�C�����擾
		 ***/
		if ( ( li_fileCnt = scandir ( pAppEnv->cDir3Id, 
									  &lpst_dirBuf,
									  (void*)sFncFileFillter,
					   				  alphasort ) ) < 0 ) {
			//	�ُ�I��	LOG
			gintErrorCode = MYAPP_STSCODE_ERR_DIR;
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "scandir", __LINE__,
				 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 	 "3ID���t�@�C���̎擾�Ɏ��s���܂���" ) ;
			return ( -1 ) ;
		}

		if( li_fileCnt ) {
			//�g���[�X���O
			memset(sDttm, 0, sizeof(sDttm));
			sFncGetNowdate1( sDttm ) ;
			sFncPutLog ( TRCKIND_OPT, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						 "�����J�n(%s) �t�@�C����(%d)", sDttm, li_fileCnt);
		}

		/***
		 ***	�f�[�^����
		 ***/
		li_idx = 0 ;
		for ( li_idx = 0 ; li_idx < li_fileCnt ; li_idx ++ ) {

			//	BUNPOS���t�@�C���擾
			li_retSts=sFncTrFileRead ( pAppEnv,lpst_dirBuf[li_idx]->d_name, &li_OkSkipFlg ) ;
			if ( li_retSts < 0 ) {
				// NG�f�B���N�g���Ɉړ�
				sFncPutLog ( TRCKIND_OPT, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							 "  RENAME NG [%s/%s]->[%s/%s]", pAppEnv->cDir3Id, lpst_dirBuf[li_idx]->d_name, pAppEnv->cDir3IdNg, lpst_dirBuf[li_idx]->d_name);
				sFncFileRename ( pAppEnv->cDir3Id, 
								 lpst_dirBuf[li_idx]->d_name,
								 pAppEnv->cDir3IdNg,
								 lpst_dirBuf[li_idx]->d_name ) ;
				// BUNPOS���t�@�C���̏������s��
				free ( lpst_dirBuf[li_idx] ) ;
				continue ;
			} else if ( li_retSts == 2 ) {
				// BUNPOS���t�@�C���ȊO
				// ����BUNPOS���t�@�C���̏������s��
				free ( lpst_dirBuf[li_idx] ) ;
				continue ;
			} else {
				// �e�[�u����UPDATE�ɐ�������(POS�ASKIP�t�@�C�������Ƃ�) or POS�t�@�C���̏ꍇ
				if ( li_OkSkipFlg == 0 ) {
					// OK�f�B���N�g���Ɉړ�
					sFncPutLog ( TRCKIND_OPT, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								 "  RENAME OK [%s/%s]->[%s/%s]", pAppEnv->cDir3Id, lpst_dirBuf[li_idx]->d_name, pAppEnv->cDir3IdOk, lpst_dirBuf[li_idx]->d_name);
					sFncFileRename ( pAppEnv->cDir3Id, 
									 lpst_dirBuf[li_idx]->d_name,
									 pAppEnv->cDir3IdOk,
									 lpst_dirBuf[li_idx]->d_name ) ;

				// ���t�@�C����SKIP�t�@�C���ŁAUPDATE�ł��Ȃ������ꍇ
				} else {
					// �ǂݍ��݌��t�@�C��(SKIP.�`)��SKIP�f�B���N�g���Ɉړ�
					sFncPutLog ( TRCKIND_OPT, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								 "  RENAME SKIP [%s/%s]->[%s/%s]", pAppEnv->cDir3Id, lpst_dirBuf[li_idx]->d_name, pAppEnv->cDir3IdSkip, lpst_dirBuf[li_idx]->d_name);
					sFncFileRename ( pAppEnv->cDir3Id, 
									 lpst_dirBuf[li_idx]->d_name,
									 pAppEnv->cDir3IdSkip,
									 lpst_dirBuf[li_idx]->d_name ) ;
				}
			}
				
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
	sFncPutLog ( TRCKIND_OPT, __FILE__, "", __LINE__,
				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "�v���O�����I��" ) ;
	ZbmlCloseLog() ;
	
	return ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncTrFileRead()			 								  */
/*  �@�\�T�v�@�FBUNPOS���t�@�C���Ǎ�										  */
/*	���L����  �F��Q������free												  */
/*              1.01 SMPCD���Ƃɕ������ʂ��擾����悤�ɕύX                  */
/*  ���@�@�́@�F															  */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����					  */
/*�@ ��Q���� �Fchar *  	 		BUNPOS���t�@�C����					  */
/*  �o�@�@�́@�F															  */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/*					 1	�f�[�^�ُ�											  */
/******************************************************************************/
static	int
sFncTrFileRead ( pAppEnv, pc_trFileName, piOkSkipFlg )
struct appEnv	*pAppEnv ;
char			*pc_trFileName ;
int				*piOkSkipFlg ;
{
	FILE				*lfp ;
	ID3Info				*pId3Info ;
	ID3TB				 strId3Tb ;
	char				 lc_recBuf[MYAPP_RECV_RECSIZE] ;
	int					 li_recBuflen;
	int					 li_retryCnt ;
	char				 lc_fileName[1024] ;
	char				 cEnd ;
	char                 cBnckka ;
	struct stat			 lst_statBuf ;
	int					 li_retSts ;
	int					 li_EndFlg ;
	LC_BOOLEAN			 blnErrFlg ;
	LC_BOOLEAN			 blnNotFoundFlg ;

	int					 li_idx ;
	int					 li_CntSmpcd ;
	SORTInfo			*pSortInfo ;

	/***
	 ***	�ϐ�������
	 ***/
	blnErrFlg = LC_false ;
	blnNotFoundFlg = LC_false ;
	li_EndFlg = 0 ;
	cEnd = '0' ;
	*piOkSkipFlg = 0 ;

	li_idx = 0 ;
	li_CntSmpcd = 0 ;

	/***
	 ***	�t�@�C�������`�F�b�N
	 ***/
	//	�t�@�C�����쐬
	sprintf ( lc_fileName, "%s/%s", pAppEnv->cDir3Id, pc_trFileName ) ;
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
	li_retryCnt = 0 ;
	while ( li_retryCnt  < pAppEnv->fileRetry ) {
		// �t�@�C���I�[�v��	
		lfp = fopen ( lc_fileName, "r" ) ;
		
		// �t�@�C���I�[�v�����s
		if ( lfp == NULL ) {
			li_retryCnt ++ ;
			
			if ( li_retryCnt == pAppEnv->fileRetry ) {
				//	�ُ�I��	LOG
				gintErrorCode = MYAPP_STSCODE_ERR_TR_FILE ;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 	 	"�t�@�C���̓ǂݍ��݂Ɏ��s���܂���[%s] retry[%d]", lc_fileName, li_retryCnt ) ;
				if ( lfp != NULL ) {
					fclose ( lfp ) ;
				}
				return ( -1 ) ;
			}
			continue ;
		} else {
			break ;
		}
	}

	memset(lc_recBuf, 0, MYAPP_RECV_RECSIZE) ;
	memset(&strId3Tb, 0, sizeof(ID3TB)) ;

	// 1���R�[�h������
	while ( fgets ( lc_recBuf, sizeof ( lc_recBuf ), lfp ) != NULL ) {
		// ���s�R�[�h�u��
		li_recBuflen = strlen ( lc_recBuf ) ;
		if ( lc_recBuf[li_recBuflen-2] == '\r' ) {
			lc_recBuf[li_recBuflen-2] = '\0' ;
		}
		if ( lc_recBuf[li_recBuflen-1] == '\n' ) { 
			lc_recBuf[li_recBuflen-1] = '\0' ;
		}

		// SQL���ʃt���O������
		blnErrFlg 	= LC_false ;
		blnNotFoundFlg  = LC_false ;

		// BUNPOS���R�[�h����
		pId3Info = (ID3Info *)lc_recBuf ;

		/*** BUNPOS���R�[�h����e�l��ݒ� ***/
		// ��t��
		memcpy( strId3Tb.cUtkymd, pId3Info->cUtkymd, sizeof(pId3Info->cUtkymd) ) ;
		// �˗���No
		memcpy( strId3Tb.cIrino, pId3Info->cIrino, sizeof(pId3Info->cIrino) ) ;
		// ������
		memcpy( strId3Tb.cSriymd, pId3Info->cSriymd, sizeof(pId3Info->cSriymd) ) ;
		// ���̔ԍ�
		memcpy( strId3Tb.cKntno, pId3Info->cKntno, sizeof(pId3Info->cKntno) ) ;
		// ���b�NID
		memcpy( strId3Tb.cRackId, pId3Info->cRackId, sizeof(pId3Info->cRackId) ) ;
		// ���b�N�|�W�V����
		memcpy( strId3Tb.cRackPos, pId3Info->cRackPos, sizeof(pId3Info->cRackPos) ) ;
		// �\��
		memcpy( strId3Tb.cYobi, pId3Info->cYobi, sizeof(pId3Info->cYobi) ) ;

		// END���R�[�h���ǂ������f����
		if ( !memcmp( strId3Tb.cUtkymd, RECEND_3RDID, 3 ) ) {

			cEnd = '1' ;

			// 3ID END���R�[�h�̏ꍇ
			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						 "3ID END���R�[�h�W�J TBL[SYSKNRMST] LBCD[%s] SATEID[%s] NSKENDFLG[%c]", pAppEnv->cLbcd, pAppEnv->cSateid, cEnd ) ;

			/********************************************/
			/***                                      ***/
			/***  �V�X�e���Ǘ��}�X�^�e�[�u����UPDATE  ***/
			/***                                      ***/
			/********************************************/

			// �V�X�e���Ǘ��}�X�^�e�[�u����UPDATE
			li_retSts = sFncUpdSYSKNRMST( pAppEnv->cLbcd, pAppEnv->cSateid, cEnd ) ;
			if ( li_retSts == MYAPP_SQL_NOTFOUND )
			{
				//�X�V�Ώۃf�[�^���Ȃ��ꍇ
				blnNotFoundFlg = LC_true ;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"UPDATE SYSKNRMST NOTFOUND[%ld] LBCD[%s] SATEID[%s] NSKENDFLG[%c]", pAppEnv->cLbcd, pAppEnv->cSateid, cEnd ) ;
			}
			else if ( li_retSts < 0 ) {
				blnErrFlg = LC_true ;
			}
		} else {

			// 3ID���R�[�h�̏ꍇ
			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"3ID���R�[�h�W�J UTKYMD[%s] IRINO[%s] SRIYMD[%s] KNTNO[%s] RACKID[%s] RACKPOS[%s]",
						strId3Tb.cUtkymd, strId3Tb.cIrino, strId3Tb.cSriymd, strId3Tb.cKntno, strId3Tb.cRackId, strId3Tb.cRackPos ) ;

			/****************************/
			/***                      ***/
			/***  �e�e�[�u����UPDATE  ***/
			/***                      ***/
			/****************************/
            // �������ʃe�[�u������T���v�����O�R�[�h(SMPCD)�A��������(BNCKKA)���擾
            li_retSts = sFncSelBUNCHU( &strId3Tb, &pSortInfo, &li_CntSmpcd ) ;
			if ( li_retSts == MYAPP_SQL_NOTFOUND )
			{
				//�X�V�Ώۃf�[�^���Ȃ��ꍇ
				blnNotFoundFlg = LC_true ;
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"SELECT BUNCHU NOTFOUND[%ld] UTKYMD[%s] IRINO[%s] SRIYMD[%s] KNTNO[%s] RACKID[%s] RACKPOS[%s]",
							li_retSts, strId3Tb.cUtkymd, strId3Tb.cIrino, strId3Tb.cSriymd, strId3Tb.cKntno, strId3Tb.cRackId, strId3Tb.cRackPos ) ;
			}
			else if ( li_retSts < 0 ) {
				blnErrFlg = LC_true ;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"SELECT BUNCHU ERROR[%ld] UTKYMD[%s] IRINO[%s] SRIYMD[%s] KNTNO[%s] RACKID[%s] RACKPOS[%s]",
							li_retSts, strId3Tb.cUtkymd, strId3Tb.cIrino, strId3Tb.cSriymd, strId3Tb.cKntno, strId3Tb.cRackId, strId3Tb.cRackPos ) ;
			}
			else {
				/* 1.01 �擾�����T���v�����O�R�[�h���ƂɃ\�[�g�L�[��ݒ肵��UPDATE */
				for ( li_idx = 0 ; li_idx < li_CntSmpcd ; li_idx++ ) {

					cBnckka =  pSortInfo[li_idx].cBnckka ;

					// �\�[�g�L�[�ݒ�
					pSortInfo[li_idx].iSrtkey = AbunGetSort( pAppEnv, pId3Info->cRackId, cBnckka ) ;

					// �������ʃe�[�u����UPDATE
					li_retSts = sFncUpdBUNCHU( &strId3Tb, &pSortInfo[li_idx] ) ;
					if ( li_retSts == MYAPP_SQL_NOTFOUND )
					{
						//�X�V�Ώۃf�[�^���Ȃ��ꍇ
						blnNotFoundFlg = LC_true ;
						sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"SELECT BUNCHU NOTFOUND[%ld] UTKYMD[%s] IRINO[%s] SRIYMD[%s] KNTNO[%s] RACKID[%s] RACKPOS[%s]",
									li_retSts, strId3Tb.cUtkymd, strId3Tb.cIrino, strId3Tb.cSriymd, strId3Tb.cKntno, strId3Tb.cRackId, strId3Tb.cRackPos ) ;
					}
					else if ( li_retSts < 0 ) {
						blnErrFlg = LC_true ;
						sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"SELECT BUNCHU ERROR[%ld] UTKYMD[%s] IRINO[%s] SRIYMD[%s] KNTNO[%s] RACKID[%s] RACKPOS[%s]",
									li_retSts, strId3Tb.cUtkymd, strId3Tb.cIrino, strId3Tb.cSriymd, strId3Tb.cKntno, strId3Tb.cRackId, strId3Tb.cRackPos ) ;
					}
				}

				// ���̑������e�[�u����UPDATE
				li_retSts = sFncUpdKENZOK( &strId3Tb ) ;
				if ( li_retSts == MYAPP_SQL_NOTFOUND )
				{
					//�X�V�Ώۃf�[�^���Ȃ��ꍇ
					blnNotFoundFlg = LC_true ;
					sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"UPDATE KENZOK NOTFOUND[%ld] UTKYMD[%s] IRINO[%s] SRIYMD[%s] KNTNO[%s] RACKID[%s] RACKPOS[%s]",
								li_retSts, strId3Tb.cUtkymd, strId3Tb.cIrino, strId3Tb.cSriymd, strId3Tb.cKntno, strId3Tb.cRackId, strId3Tb.cRackPos ) ;
				}
				else if ( li_retSts < 0 ) {
					blnErrFlg = LC_true ;
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"UPDATE KENZOK ERROR[%ld] UTKYMD[%s] IRINO[%s] SRIYMD[%s] KNTNO[%s] RACKID[%s] RACKPOS[%s]",
								li_retSts, strId3Tb.cUtkymd, strId3Tb.cIrino, strId3Tb.cSriymd, strId3Tb.cKntno, strId3Tb.cRackId, strId3Tb.cRackPos ) ;
				}

				// ���̔F�����e�[�u����UPDATE
				li_retSts = sFncUpdNINSIKI( &strId3Tb ) ;
				if ( li_retSts == MYAPP_SQL_NOTFOUND )
				{
					//�X�V�Ώۃf�[�^���Ȃ��ꍇ
					blnNotFoundFlg = LC_true ;
					sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"UPDATE NINSIKI NOTFOUND[%ld] UTKYMD[%s] IRINO[%s] SRIYMD[%s] KNTNO[%s] RACKID[%s] RACKPOS[%s]",
								li_retSts, strId3Tb.cUtkymd, strId3Tb.cIrino, strId3Tb.cSriymd, strId3Tb.cKntno, strId3Tb.cRackId, strId3Tb.cRackPos ) ;
				}
				else if ( li_retSts < 0 ) {
					blnErrFlg = LC_true ;
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"UPDATE NINSIKI ERROR[%ld] UTKYMD[%s] IRINO[%s] SRIYMD[%s] KNTNO[%s] RACKID[%s] RACKPOS[%s]",
								li_retSts, strId3Tb.cUtkymd, strId3Tb.cIrino, strId3Tb.cSriymd, strId3Tb.cKntno, strId3Tb.cRackId, strId3Tb.cRackPos ) ;
				}
			}
			/* 1.01 �\�[�g�p�\���̗̈�̊J�� */
			free ( pSortInfo ) ;
		}

		/*** BUNPOS�t�@�C����1���R�[�h�P�ʂ�COMMIT or ROLLBACK ***/
		// �X�V�Ώۃ��R�[�h��������Ȃ� or �X�V�G���[�̏ꍇ
		if ( blnNotFoundFlg == LC_true || blnErrFlg == LC_true ) {
//			sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//						"Rollback !!! UTKYMD[%s] IRINO[%s] SRIYMD[%s] KNTNO[%s] RACKID[%s] RACKPOS[%s]",
//						strId3Tb.cUtkymd, strId3Tb.cIrino, strId3Tb.cSriymd, strId3Tb.cKntno, strId3Tb.cRackId, strId3Tb.cRackPos ) ;

			// ���[���o�b�N
			ZdbRollback () ;

			// �ǂݍ��݌��t�@�C���� POS.data.XXXX �̏ꍇ
			if ( !memcmp( pc_trFileName, MYAPP_RECV_KIND_POS, 3 ) ) {
				// �Ώۃ��R�[�h(lc_recBuf)��SKIP�t�@�C���ɏo��
				if ( sFncOutput( pAppEnv, strId3Tb.cKntno, lc_recBuf ) < 0 ) {
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"SKIP�t�@�C���o�� ERROR UTKYMD[%s] IRINO[%s] SRIYMD[%s] KNTNO[%s] RACKID[%s] RACKPOS[%s]",
								strId3Tb.cUtkymd, strId3Tb.cIrino, strId3Tb.cSriymd, strId3Tb.cKntno, strId3Tb.cRackId, strId3Tb.cRackPos ) ;
					if ( lfp != NULL ) {
						fclose ( lfp ) ;
					}
					return ( -1 ) ;
				}

			// �ǂݍ��݌��t�@�C���� SKIP.�` �̏ꍇ
			} else if ( !memcmp( pc_trFileName, MYAPP_RECV_KIND_SKIP, 4 ) ) {
				// mainFunction�֐���SKIP�t�@�C����SKIP�f�B���N�g����MOVE����ׂ̃t���O�ݒ�
				*piOkSkipFlg = 1 ;
			}
		} else {
			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "sFncTrFileRead", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "COMMIT !!!" ) ;

			// �R�~�b�g
			ZdbCommit () ; 
		}

		memset(lc_recBuf, 0, MYAPP_RECV_RECSIZE) ;
		memset(&strId3Tb, 0, sizeof(ID3TB)) ;

		/* 1.01 �\�[�g�p�\���̗̈�̊J�� */
//		free ( pSortInfo ) ;
	}

	fclose ( lfp ) ;

	return ( 0 ) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncOutput()				 								  */
/*  �@�\�T�v�@�F�X�V�Ɏ��s�����f�[�^��SKIP�t�@�C���ɏo�͂���				  */
/*  ���@�@�́@�F															  */
/*   ��P���� �Fstruct appEnv * 	�v���O�������\����					  */
/*   ��Q���� �Fchar lc_Kntno * 	����No									  */
/*   ��R���� �Fchar lc_recBuf * 	BUNPOS��񃌃R�[�h						  */
/*  �o�@�@�́@�F															  */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
static int
sFncOutput ( pAppEnv, lc_Kntno, lc_recBuf )
struct appEnv		*pAppEnv ;
char				*lc_Kntno ;
char				*lc_recBuf ;
{
	FILE	*lfp ;
	char	 sRetryFile[1024];
	char	 sSysdate[128] ;
	char	 sSystime[128] ;

	/* 1.02 �ꎞ�t�@�C���̃t�@�C���� */
	char     sRetryTmpFile[1024];

    /* ���݂̔N�����A�����b�擾 */
	memset( sSysdate, 0, sizeof(sSysdate) ) ;
	memset( sSystime, 0, sizeof(sSystime) ) ;
	sFncGetNowdate( sSysdate, sSystime ) ;

	memset( sRetryTmpFile, 0, sizeof(sRetryTmpFile) ) ;
	sprintf( sRetryTmpFile, "%s/%s.%s%s.%s", pAppEnv->cDir3IdSkip, MYAPP_RECV_KIND_TMP, sSysdate, sSystime, lc_Kntno );

	/* 1.02�Ή� SKIP�쐬�pTMP�t�@�C���I�[�v�� */
	if( (lfp = fopen(sRetryTmpFile,"a")) == NULL ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOutput   ", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"SKIP�쐬�pTMP�t�@�C���̃I�[�v���Ɏ��s���܂���[%s]", sRetryTmpFile ) ;
		return -1;
	}

	/* �X�V���s�f�[�^�����g���C�p�t�@�C���ɏo�� */
	if( fputs(lc_recBuf, lfp) == EOF ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOutput	", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "SKIP�t�@�C���̏o�͂Ɏ��s���܂���[%s]", lc_recBuf ) ;
		if ( lfp != NULL ) {
			fclose ( lfp ) ;
		}
		return -1;
	}

	fclose ( lfp ) ;

	/* SKIP�t�@�C�����쐬 (/apdata/today/online/host/Recv/3id/SKIP/SKIP.YYYYMMDDHHMMSS.12345678901) */
	memset( sRetryFile, 0, sizeof(sRetryFile) ) ;
	sprintf( sRetryFile, "%s/%s.%s%s.%s", pAppEnv->cDir3IdSkip, MYAPP_RECV_KIND_SKIP, sSysdate, sSystime, lc_Kntno ) ;

	/* �����̃X�L�b�v�t�@�C�������łɑ��݂���ꍇ�͏o�͂��Ȃ� (���ꌟ�̂̏�񂪂��łɑ��݂��Ă��邽��) */
	if ( (lfp = fopen( sRetryFile,"r")) != NULL ){
		fclose( lfp );
		unlink( sRetryTmpFile );
		return ( 0 ) ;
	}

	/* 1.02�Ή� TMP �� SKIP �t�@�C�����ύX */
	if ( link( sRetryTmpFile, sRetryFile ) == 0 ) {
		sFncPutLog ( TRCKIND_OPT, __FILE__, "sFncOutput ", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  SKIP�t�@�C���o��[%s]", sRetryFile ) ;
		unlink( sRetryTmpFile );
	} else {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOutput ", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  TMP�t�@�C������SKIP�t�@�C���ւ̕ϊ��Ɏ��s���܂���[%s] �� [%s]", sRetryTmpFile, sRetryFile ) ;
		return -1;
	}

	return ( 0 ) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncGetNowdate()			 								  */
/*  �@�\�T�v�@�F���݂̔N�����A�����b��Ԃ�									  */
/*  ���@�@�́@�F															  */
/*   ��P���� �Fchar *sysdate	YYYYMMDD�`��								  */
/*   ��Q���� �Fchar *systime	HHMMSS�`��									  */
/*  �o�@�@�́@�F															  */
/*  ���A���@�F����														  */
/******************************************************************************/
void
sFncGetNowdate( sysdate, systime )
char	*sysdate ;
char	*systime ;
{
	struct	tm	*newtime ;
	long		 ltime ;

	time( &ltime) ;
	newtime = localtime( &ltime ) ;
	sprintf( sysdate, "%04d%02d%02d", newtime->tm_year+1900,
			 newtime->tm_mon+1, newtime->tm_mday ) ;
	sprintf( systime, "%02d%02d%02d", newtime->tm_hour,
			 newtime->tm_min, newtime->tm_sec ) ;

	return ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncGetNowdate1()			 								  */
/*  �@�\�T�v�@�F���݂̔N�����A�����b��Ԃ�									  */
/*  ���@�@�́@�F															  */
/*   ��P���� �Fchar *sysdttm	YYYY-MM-DD HH:MI:SS�`��						  */
/*  �o�@�@�́@�F															  */
/*  ���A���@�F����														  */
/******************************************************************************/
void
sFncGetNowdate1( sysdttm )
char	*sysdttm ;
{
	struct	tm	*newtime ;
	long		 ltime ;

	time( &ltime) ;
	newtime = localtime( &ltime ) ;
	sprintf( sysdttm, "%04d-%02d-%02d %02d:%02d:%02d", newtime->tm_year+1900,
			 newtime->tm_mon+1, newtime->tm_mday, newtime->tm_hour,
			 newtime->tm_min, newtime->tm_sec ) ;

	return ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncPutLog()                                                  */
/*  �@�\�T�v�@�F�A�v���P�[�V�������O�o��                                      */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *      �ҏW������                                        */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F����                                                          */
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
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncShmCrt", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "���L�������̑���Ɏ��s���܂���" ) ;
		return ( -1 ) ;
	}

	//	�A�^�b�`	
	shmData = ( int * ) shmat ( pAppEnv->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncShmCrt", __LINE__,
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
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncShmCrt", __LINE__,
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
int				*pshmData ;
{
	int		*shmData ;

	//	�A�^�b�`	
	shmData = ( int * ) shmat ( pAppEnv->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncShmGet", __LINE__,
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
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncShmGet", __LINE__,
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
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncShmDel", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "���L�������̑���Ɏ��s���܂���" ) ;
		return ( -1 ) ;
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
		//���ʃ`�F�b�N("POS")
		if ( memcmp ( pdirEnt->d_name, 
					  MYAPP_RECV_KIND_POS, 
					  strlen ( MYAPP_RECV_KIND_POS ) ) == 0 ) {
			return ( 1 ) ;
		}
		//���ʃ`�F�b�N("SKIP")
		if ( memcmp ( pdirEnt->d_name, 
					  MYAPP_RECV_KIND_SKIP, 
					  strlen ( MYAPP_RECV_KIND_SKIP ) ) == 0 ) {
			return ( 1 ) ;
		}
//		//�g���q�`�F�b�N
//		if ( memcmp ( &(pdirEnt->d_name[li_len-strlen(MYAPP_RECV_SFX)]), 
//					  MYAPP_RECV_SFX, 
//					  strlen ( MYAPP_RECV_SFX ) ) == 0 ) {
//			return ( 1 ) ;
//		}
		return ( 0 ) ;
}

/****************************************************************************/
/*  �� �� ���@�FAbunGetSort()												*/
/*  �@�\�T�v�@�F����TBL�Ɋi�[����\�[�g�L�[���Z�o����						*/
/*              1.01 ������ύX                                             */
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �F															*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
static    int
AbunGetSort( pst_Env, sId, cBnckka )
struct appEnv *pst_Env ;
char          *sId ;
char          cBnckka ;
{
	int		i, cnt, iKey, iHit ;
	char	sBuf[10] ;
	BUNSORT	*p ;
	char	flg_tbl[] = {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"} ;

	memset(sBuf, 0, sizeof(sBuf)) ;
	memcpy(sBuf, sId, 4) ;
	cnt = pst_Env->pSortNo ;

	iKey = 999 ;
	for( i=0; i < cnt ;++i ) {
		p = pst_Env->pSort + i ;
		if( !memcmp(sBuf, p->sData, 2) ) {
			iKey = atoi(p->sKey) ;
			break ;
		}
	}

	if( !memcmp(sBuf, "XX", 2) || !memcmp(sBuf, "YY", 2) ) {
		return( iKey ) ;
	}

	iHit = 0 ;
	for( i=0; flg_tbl[i] != '\0' ;++i ) {
		if ( flg_tbl[i] == cBnckka ) {
			iHit = 1 ;
			break ;
		}
	}
	if( iHit == 1 ) {
		if( i == 36) i = 40 ;
		iKey = iKey + i ;
	}

	return( iKey ) ;
}

/****************************************************************************/
/*  �� �� ���@�FAgetSortInfo()												*/
/*  �@�\�T�v�@�F�\�[�g�����t�@�C������\�[�g�����擾����					*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �FBUNSORT **strBun	�\�[�g�\����							*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
static int AgetSortInfo(BUNSORT **strBun )
{
	FILE *fp;
	char	buf[1024], buf1[10];
	BUNSORT *pBun = NULL;
	int		i, j, k, cnt, iHit, iSu;

	if( (fp = fopen(MYAPP_AD105SORTINIFILE, "r")) == NULL ) {
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "AgetSortInfo", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"fopen ERROR(%d)", errno);
		return( -1 );
	}

	memset(buf, 0, sizeof(buf));
	iSu = 0;
	for( i=0; fgets(buf, sizeof(buf), fp ) != NULL ;++i ) {
		// �擪��#�̓X�L�b�v����B
		if( (buf[0] == '#') || (buf[0] == '\n') ) {
			memset(buf, 0, sizeof(buf));
			continue;
		}
		pBun = (BUNSORT *)realloc((BUNSORT *)pBun, sizeof(BUNSORT) * (iSu + 1));
		memset(pBun+iSu, 0, sizeof(BUNSORT));
		memcpy((pBun+iSu)->sData, buf, 4);
		memcpy((pBun+iSu)->sKey, &buf[5], 3);
		++iSu;
	}

	fclose(fp);

	*strBun = pBun;

	return( iSu );
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
