/******************************************************************************/
/* �@�y�r�O�T�O�@�����V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FMD103.c                                                      */
/* �@�T�@�@�@�v�F�X�g�b�J�[�y�����z                                           */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2020/05/02                    �V�K�쐬                           */
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

#include "MD103.h"

/******************************************************************************/
/* Define��`                                                                 */
/******************************************************************************/

//  �t���O��`
typedef enum {
    LC_false,
    LC_true
} LC_BOOLEAN ;

/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/
MYAPP_STSCODE		 gintErrorCode ;
int			 gtBunchuFlg;		//	���������n�j or �m�f
struct stcLogMember	 gstLogMem ;		//	���O�o�͏��

/******************************************************************************/
/* �֐��錾                                                                   */
/******************************************************************************/
//	�g���[�E���b�N�R�t�����֘A�֐�
static	int	sFncTrFileRead ( struct appEnv *, char *, struct trInfo *, int * ) ;
/*
static	int	sFncSelChkOrderSumiTray ( char *, char *, int * ) ;
static	int	sFncSelChkOrderSumiRack ( char *, char *, int * ) ;
*/
//	�t�@�C���E�f�[�^�x�[�X�o�͊֐�
static	int 	sFncOutput ( struct appEnv *, struct trInfo *, int ) ;
static	int 	sFncFileOutOnline ( struct appEnv *, struct my_stKENORDER *, int ) ;
static	int 	sFncFileOutLane ( struct appEnv *, struct my_stKENORDER *, int ) ;
static	int 	sFncOutRecKENORDER ( FILE *, char *, struct my_stKENORDER *, struct appEnv * ) ;
static	int 	sFncOutRecKESSEI ( FILE *, char *, struct my_stKENORDER *, struct appEnv * ) ;
static	int 	sFncOutRecLane ( FILE *, char *, struct my_stKENORDER * ) ;
static	int 	sFncOutRecLaneHeader ( FILE *, char *, struct my_stKENORDER * ) ;
static	void	sFncCreFileName ( char *, char *, char *, short, char *, struct tm * ) ;

//	���L����������֐�
static	int	sFncShmCrt ( struct appEnv * ) ;
static	int	sFncShmGet ( struct appEnv * , int *) ;
static	int	sFncShmDel ( struct appEnv * ) ;

//	�R�[���o�b�N�֐�
static	int	sFncFileCompar ( struct dirent **, struct dirent ** )  ;
static	int	sFncFileFillter ( struct dirent * ) ;

//	���̑�
static	int	sFncFileRename ( char *, char *, char *, char * ) ;
static	void	sFncTrim ( char * ) ;
static  void	endFunction(struct appEnv *);

//	�g���[�X�p

/******************************************************************************/
/*  �� �� ���@�FinitFunction()							*/
/*  �@�\�T�v�@�F���������֐�							*/
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct	env *   	�v���O�������\���́B		 	*/
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F  0     : ����							*/
/* �@�@�@�@�@�@�@-1     : ���s							*/
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

	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"�v���O�����N��" ) ;
	//	�J�n���O�o��

	/***
	 ***	������	
	 ***/
	//	�G���[�X�e�[�^�X�ύX
	gintErrorCode = 0 ;

	//	�v���O�������ϐ�������
	memset ( pAppEnv , '\0', sizeof ( struct appEnv ) ) ;

	//	�p�����[�^�t�@�C�����ޔ�
	pAppEnv->pcFielNamePRM = argv[1] ;

	//	�p�����[�^�t�@�C���I�[�v��	
	pAppEnv->bp = ZbmlPrmOpen ( pAppEnv->pcFielNamePRM ) ;		
	if ( pAppEnv->bp == NULL ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmOpen", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�p�����[�^�t�@�C���̃I�[�v���Ɏ��s���܂���[%s]", pAppEnv->pcFielNamePRM ) ;
		return ( -1 ) ;
	}

	//	��M����
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_NR_SUP, pAppEnv->cDirNR_Sup ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_NR_SUP ) ;
		return ( -1 ) ;
	}
	//	��M��������
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_NR_SUP_OK, pAppEnv->cDirNR_SupOk ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_NR_SUP_OK ) ;
		return ( -1 ) ;
	}
	//	��M�����G���[
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_NR_SUP_ERR, pAppEnv->cDirNR_SupErr ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_NR_SUP_ERR ) ;
		return ( -1 ) ;
	}
	//	�I�����C���p�˗��t�@�C���o�̓f�B���N�g��
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_ONL_DAT, pAppEnv->cDirOnl_Dat ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_ONL_DAT ) ;
		return ( -1 ) ;
	}
	//	���݃��[���p�˗��t�@�C���o�̓f�B���N�g��
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_LANE_DAT, pAppEnv->cDirLane_Dat ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_LANE_DAT ) ;
		return ( -1 ) ;
	}
	//	�������(����)���ڃR�[�h
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_NYUBI_CODE, pAppEnv->cNyubiCD ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_NYUBI_CODE ) ;
		return ( -1 ) ;
	}
	//	�������(�n��)���ڃR�[�h
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_YOKETSU_CODE, pAppEnv->cYoketsuCD ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_YOKETSU_CODE ) ;
		return ( -1 ) ;
	}
	//	�������(������)���ڃR�[�h
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_OUDANCD_CODE, pAppEnv->cOudanCD ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_OUDANCD_CODE ) ;
		return ( -1 ) ;
	}
	//	�������(���H)���ڃR�[�h�@--�@�������𑪒肷��ۂɓ����Ɉ˗��𔭐�������K�v����B
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_SEISYOKU_CODE, pAppEnv->cSeisyokuCD ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_SEISYOKU_CODE ) ;
		return ( -1 ) ;
	}
	//	��ߔ{���\���p(B10)
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_KSKBR_B10_HYOJI, pAppEnv->cKskbrB10HY ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_KSKBR_B10_HYOJI ) ;
		return ( -1 ) ;
	}
	//	��ߔ{�����͋@���M�p�R�[�h(B10)
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_KSKBR_B10_CODE, pAppEnv->cKskbrB10CD ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_KSKBR_B10_CODE ) ;
		return ( -1 ) ;
	}
	//	��ߔ{���\���p(B2)
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_KSKBR_B2_HYOJI, pAppEnv->cKskbrB2HY ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_KSKBR_B2_HYOJI ) ;
		return ( -1 ) ;
	}
	//	��ߔ{�����͋@���M�p�R�[�h(B2)
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_KSKBR_B2_CODE, pAppEnv->cKskbrB2CD ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_KSKBR_B2_CODE ) ;
		return ( -1 ) ;
	}
	//	���L�������L�[�擾
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_SHM_KEY, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_SHM_KEY ) ;
		return ( -1 ) ;
	}

	pAppEnv->shm_Key = atoi ( lc_prmBuf ) ;
	//	SLEEPSEC�擾
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_SLEEP_SEC, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_SLEEP_SEC ) ;
		return ( -1 ) ;
	}
	pAppEnv->sleep_Sec= atoi ( lc_prmBuf ) ;
	//	�f�[�^�x�[�X��
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DB_NAME, pAppEnv->cDb_Name ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	"�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DB_NAME ) ;
		return ( -1 ) ;
	}
	//	�f�[�^�x�[�X���[�U
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DB_USER, pAppEnv->cDb_User ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DB_USER ) ;
		return ( -1 ) ;
	}
	//	�f�[�^�x�[�X�p�X���[�h
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DB_PASSWD, pAppEnv->cDb_Passwd ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DB_PASSWD ) ;
		return ( -1 ) ;
	}
	//	�t�@�C���Ǎ����g���C��
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_FILE_RETRY, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_FILE_RETRY ) ;
		return ( -1 ) ;
	}
	pAppEnv->fileRetry = atoi ( lc_prmBuf ) ;

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
/*  �� �� ���@�FmainFunction()							*/
/*  �@�\�T�v�@�F���C�������֐�							*/
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct	env *   	�v���O�������\���́B		 	*/
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F  0     : ����							*/
/* �@�@�@�@�@�@�@-1     : ���s							*/
/******************************************************************************/
int
mainFunction( pAppEnv )
struct appEnv	*pAppEnv ;
{
	int		  li_retSts ;

	int		  li_idx ;	
	int		  li_stopFlg ;

	//	�f�B���N�g����� 
	struct dirent	**lpst_dirBuf ;

	//	�g���[���b�N���֘A
	int		 li_fileCnt ;				
	int		 li_rackCnt ;				
	struct trInfo	 lst_trInfo ;
	char		 file_basename[1024];

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
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "scandir", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	  "�g���[�E���b�N�R�t�����t�@�C���̎擾�Ɏ��s���܂���" ) ;
			return ( -1 ) ;
		}

		/***
		 ***	�f�[�^����
		 ***/
		li_idx = 0 ;
		for ( li_idx = 0 ; li_idx < li_fileCnt ; li_idx ++ ) {
			memset( file_basename, '\0', sizeof ( file_basename ) );
			strncpy( file_basename, lpst_dirBuf[li_idx]->d_name, strlen(lpst_dirBuf[li_idx]->d_name)-strlen(MYAPP_RECV_SFX) );
			//	�g���[�E���b�N�R�t�����擾
			li_retSts = sFncTrFileRead ( pAppEnv, lpst_dirBuf[li_idx]->d_name, &lst_trInfo, &li_rackCnt ) ;
			if ( li_retSts < 0 ) {
				//	�G���[�f�B���N�g���Ɉړ�
				sFncFileRename ( pAppEnv->cDirNR_Sup, lpst_dirBuf[li_idx]->d_name,
						 pAppEnv->cDirNR_SupErr, strcat ( file_basename, MYAPP_RECV_SFX_ERR ) ) ;
				//	���̃g���[�E���b�N�R�t�����t�@�C���̏������s��
				free ( lpst_dirBuf[li_idx] ) ;
				continue ;
			} else if ( li_retSts == 2 ) {
				//	�g���[�E���b�N�R�t�����t�@�C���ȊO
				//	���̃g���[�E���b�N�R�t�����t�@�C���̏������s��
				free ( lpst_dirBuf[li_idx] ) ;
				continue ;
			}

			sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						 "�t�@�C�������J�n[%s]", lpst_dirBuf[li_idx]->d_name ) ;

			//	�����I�[�_�[�E�����`�F�b�N���o��
			li_retSts = sFncOutput ( pAppEnv, &lst_trInfo, li_rackCnt ) ;
			if ( li_retSts == 0 ) {
				//	���ǃf�B���N�g���Ɉړ�
				sFncFileRename ( pAppEnv->cDirNR_Sup, lpst_dirBuf[li_idx]->d_name,
						 pAppEnv->cDirNR_SupOk, strcat ( file_basename, MYAPP_RECV_SFX_END ) ) ;
			} else if ( li_retSts == 2 ) {
				//	DB���b�N�����������ꍇ�A�Y���t�@�C�����X�L�b�v���Ď��̃t�@�C���̏����ֈڂ�
				sleep ( 3 );
				free ( lpst_dirBuf[li_idx] ) ;
				continue ;
			} else {
				//	�G���[�f�B���N�g���Ɉړ�
				sFncFileRename ( pAppEnv->cDirNR_Sup, lpst_dirBuf[li_idx]->d_name,
						 pAppEnv->cDirNR_SupErr, strcat ( file_basename, MYAPP_RECV_SFX_ERR ) ) ;

				if ( li_retSts < 0 ) {
					//	���
					free ( lpst_dirBuf[li_idx] ) ;
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "[[DB ERROR]]�ŏI��" ) ;
					endFunction ( pAppEnv ) ;
        				exit ( 9 ) ;
				}
			}
			//	���
			free ( lpst_dirBuf[li_idx] ) ;

			sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						 "�t�@�C����������[%s]", lpst_dirBuf[li_idx]->d_name ) ;
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
/*  �� �� ���@�FendFunction()							*/
/*  �@�\�T�v�@�F�I�������֐�							*/
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct	env *   	�v���O�������\���́B		 	*/
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F  0     : ����							*/
/* �@�@�@�@�@�@�@-1     : ���s							*/
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
/*  �� �� ���@�FsFncOutput()				 			*/
/*  �@�\�T�v�@�F�����I�[�_�[���A�����`�F�b�N�t�@�C���o��	 	 	*/
/*				���b�N���Ɋe�t�@�C���A�f�[�^�x�[�X�̍X�V���s��	*/
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����			*/
/*�@ ��R���� �Fstruct trInfo *  	�g���[�E���b�N�R�t�����i�[�\����	*/
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint								*/
/*					 0	����				*/
/*					 2	�f�b�h���b�N			*/
/*					-1	�ُ�				*/
/******************************************************************************/
static int
sFncOutput ( pAppEnv, pst_trInfo, li_rackCnt )
struct appEnv	*pAppEnv ;
struct trInfo	*pst_trInfo ;
int		 li_rackCnt ;
{
	int			li_idx ;
	int			li_retSts ;

	char			cSel_knskisymd[MYAPP_DATE_SIZE] ;
	struct my_stKENORDER	*recKENORDER ;		 		 
	struct my_stREALCHK	*recREALCHK ;
	int			recCnt ;
	int			svRecCnt ;
	LC_BOOLEAN		blnErrFlg ;
	LC_BOOLEAN		blnLockFlg ;
	LC_BOOLEAN		blnNgFlg ;
	int			li_BunTrCnt ;
	int			li_len ;
	int			li_Trknhsu ;	//�g���[�����̖{��
	int			li_MaxOrderTrpos ;
	char			buf[11], buf1[11], buf2[11], cKnsgrp[17] ;

	int			li_TrRkhsu  = 0 ;	//�g���[�����b�N����
	int			li_chkCnt = 0 ;		//�o�^�ς݃I�[�_�[����
	int			li_LineNo = 0 ;		//�����惉�C���m�n
	int			li_cntSkip  = 0 ;	//�X�L�b�v�������b�N��
	
	/***
	 ***	�ϐ�������
	 ***/
	blnErrFlg   = LC_false ;
	blnLockFlg  = LC_false ;
	blnNgFlg    = LC_false ;

	recCnt      = 0 ;
	svRecCnt    = 0 ;
	recKENORDER = NULL ;
	recREALCHK  = NULL ;
	
	//	��{�����L�[�ݒ� �����J�n��)
	sprintf ( cSel_knskisymd, "%4.4s-%2.2s-%2.2s", 
		  pst_trInfo->knskisymd, &(pst_trInfo->knskisymd[4]), &(pst_trInfo->knskisymd[6]) ) ;

	//	�擾�����g���[�����łɓo�^����Ă��Ȃ����m�F����B
	li_chkCnt = 0;
	li_retSts = sFncSelChkOrderSumiTray ( cSel_knskisymd, pst_trInfo->trid, &li_chkCnt ) ;
	if ( li_retSts == MYAPP_SQL_DEADLOCK ) {
		//�f�b�h���b�N
		return ( 2 );
	} else if ( li_retSts < 0 ) {
		return ( -1 );
	}
	if ( li_chkCnt > 0 ){
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "�Y���̃g���[�͂��łɓo�^�ς݂ł��B[%s]", pst_trInfo->trid ) ;
		return ( 1 );
	}

	// pst_trInfo->trid(���݃t�@�C�����̃g���[ID)��KENORDER������
	li_BunTrCnt = 0 ;
	li_retSts = sFncSelCntKENORDER ( cSel_knskisymd, pst_trInfo->trid, &li_BunTrCnt ) ;
	if ( li_retSts == MYAPP_SQL_DEADLOCK ) {
		//�f�b�h���b�N
		return ( 2 );
	} else if ( li_retSts < 0 ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "�c�a�����b�N�� �������s" ) ;
		return ( -1 );
	}

	if ( li_BunTrCnt == 0 ) {
		gtBunchuFlg = MYAPP_BUNCHU_OK;
	} else {
		/* �����������ȊO(�����m�f�A�񕪒��A�p��Č���)*/
		gtBunchuFlg = MYAPP_BUNCHU_NG;
/*	
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "�O�ǂ݃��b�N��[%d] �c�a�����̐�[%d]" ,li_rackCnt, li_BunTrCnt ) ;
*/
		if ( ( li_BunTrCnt % 5 ) == 0 ) {
			li_TrRkhsu = li_BunTrCnt / 5 ;
		} else {
			li_TrRkhsu = ( li_BunTrCnt / 5 ) + 1;
		}
		/*�@�O�ǂ݂œo�^�������b�N���Ƃc�a���̃��b�N�������v���Ȃ��ꍇ�̓G���[ */
		if ( li_TrRkhsu != li_rackCnt ) {
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "�s��v�I�O�ǂ݃��b�N��[%d] �c�a�����b�N��[%d]" ,li_rackCnt, li_TrRkhsu ) ;
			return ( 1 );
		}
		/*�@�O�ǂ݂œo�^�����g���[�̐擪�̌��̂Ń��C���̓�������`�F�b�N���A�}�X�^�ɓo�^����Ă��Ȃ��ꍇ�̓G���[ */
		li_retSts = sFncSelZsLineMstTray( cSel_knskisymd, pst_trInfo->trid, &li_LineNo ) ;
		if ( li_retSts == MYAPP_SQL_DEADLOCK ) {
			//�f�b�h���b�N
			return ( 2 );
		} else if ( li_retSts < 0 ) {
			return ( -1 );
		}
		if ( li_LineNo <= 0 ) {
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "�����惉�C�����o�^ �g���[�h�c[%s]", pst_trInfo->trid ) ;
			return ( 0 );
		}
	}
	
	/***
	 ***	���C������
	 ***/
	for ( li_idx = 0 ; li_idx < MYAPP_RACK_MAXCNT ; li_idx++ ) {
		//	�u�����N�͏������s��Ȃ�
		if ( pst_trInfo->asyrckid[li_idx][0] == '\0' ) {
			continue ;
		}
		li_chkCnt = 0;
		//	�擾�������b�N�����łɓo�^����Ă��Ȃ����m�F����B
		li_retSts = sFncSelChkOrderSumiRack ( cSel_knskisymd, pst_trInfo->asyrckid[li_idx], &li_chkCnt ) ;
		if ( li_retSts == MYAPP_SQL_DEADLOCK ) {
			//�f�b�h���b�N
			blnLockFlg = LC_true ;
			break ;
		} else if ( li_retSts < 0 ) {
			blnErrFlg = LC_true ;
			break ;
		}
		if ( li_chkCnt > 0 ){
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "�Y���̃A�b�Z�C���b�N�͂��łɓo�^�ς݂ł��B[%s]", pst_trInfo->asyrckid[li_idx] ) ;
			blnNgFlg = LC_true ;
			break ;
		}

		/***
		 ***	�X�V�E����
		 ***/
		if ( gtBunchuFlg == MYAPP_BUNCHU_NG ) {
			//	�����I�[�_�[���X�V
			li_retSts = sFncUpdKENORDER ( cSel_knskisymd, pst_trInfo->trid, ( 5 * li_idx ) + 1, ( 5 * li_idx ) + 5, pst_trInfo->asyrckid[li_idx], li_idx ) ;
			if ( li_retSts == MYAPP_SQL_DEADLOCK ) {
				//�f�b�h���b�N
				blnLockFlg = LC_true ;
				break ;
			} else if ( li_retSts < 0 ) {
				blnErrFlg = LC_true ;
				break ;
			}

			//	���̃|�W�V�������ǉ�
			li_retSts = sFncInsKENPOS ( cSel_knskisymd, pst_trInfo->trid, ( 5 * li_idx ) + 1, ( 5 * li_idx ) + 5, pst_trInfo->stkno ) ;
			if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION) {
				//�f�b�h���b�Nor�d��
				blnLockFlg = LC_true ;
				break ;
			} else if ( li_retSts < 0 ) {
				blnErrFlg = LC_true ;
				break ;
			}
			
			//	�����I�[�_�[���E�����`�F�b�N��񌟍�
			li_retSts = sFncSelKENORDER_REALCHK ( cSel_knskisymd, pst_trInfo->trid, ( 5 * li_idx ) + 1, ( 5 * li_idx ) + 5,
							      &recKENORDER, &recREALCHK, &recCnt ) ;
			if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION) {
				//�f�b�h���b�Nor�d��
				blnLockFlg = LC_true ;
				break ;
			} else if ( li_retSts < 0 ) {
			 	blnErrFlg = LC_true ;
				break ;
			}		

			if ( ( recCnt - svRecCnt ) == 0 ) {
				sFncPutLog ( TRCKIND_WARNING, __FILE__, "sFncOutput", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
			 		 	 "�����I�[�_���A�܂��͑����`�F�b�N��񂪑��݂��܂��� KNSKISYMD='%s' TRID='%s' TRPOS %d-%d RCKID='%s'",
						 cSel_knskisymd, pst_trInfo->trid, ( 5 * li_idx ) + 1, ( 5 * li_idx ) + 5, pst_trInfo->asyrckid[li_idx] ) ;
			 	blnNgFlg = LC_true ;
				break ;
			} else {
				svRecCnt = recCnt ;
			}
		} else {
			/*�@�O�ǂ݂œo�^�������b�N�̐擪�̌��̂Ń��C���̓�������`�F�b�N���A�}�X�^�ɓo�^����Ă��Ȃ��ꍇ�̓X�L�b�v */
			li_LineNo = 0 ;
			li_retSts = sFncSelZsLineMstRack( cSel_knskisymd, pst_trInfo->asyrckid[li_idx], &li_LineNo ) ;
			if ( li_retSts == MYAPP_SQL_DEADLOCK ) {
				//�f�b�h���b�N
				blnLockFlg = LC_true ;
				break;
			} else if ( li_retSts == MYAPP_SQL_NOT_FOUND ) {
				sFncPutLog ( TRCKIND_WARNING, __FILE__, "sFncOutput", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
			 		 	"�����I�[�_���A�܂��͑����`�F�b�N��񂪑��݂��܂��� KNSKISYMD='%s' TRID='%s' RCKID='%s'",
						cSel_knskisymd, pst_trInfo->trid, pst_trInfo->asyrckid[li_idx] ) ;
			 	blnNgFlg = LC_true ;
				break;
			} else if ( li_retSts < 0 ) {
			 	blnErrFlg = LC_true ;
				break;
			}
			if ( li_LineNo <= 0 ) {
				sFncPutLog ( TRCKIND_WARNING, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "�����惉�C�����o�^ ���b�N�h�c[%s]", pst_trInfo->asyrckid[li_idx] ) ;
				li_cntSkip++ ;
				continue;
			}

			// �g���[�����̖{�� (100)
			li_Trknhsu = MYAPP_TRKNHSU_MAXCNT ;
			//	�����I�[�_�[���X�V
			memset(buf, 0, sizeof(buf)) ;
			memset(buf1, 0, sizeof(buf1)) ;
			memcpy(buf, pst_trInfo->trid, 11) ;
			li_len = strlen(buf) - 4 ;
			strcpy(buf1, &buf[li_len]);
			li_len = atoi(buf1);
			li_retSts = sFncUpdKENORDER_NXT ( cSel_knskisymd, pst_trInfo->asyrckid[li_idx], pst_trInfo->trid, li_len * li_Trknhsu, li_idx - li_cntSkip) ;
			if ( li_retSts == MYAPP_SQL_DEADLOCK ) {
				//�f�b�h���b�N
				blnLockFlg = LC_true ;
				break ;
			} else if ( li_retSts < 0 ) {
				blnErrFlg = LC_true ;
				break ;
			}

			//	���̃|�W�V�������ǉ�
			li_retSts = sFncInsKENPOS_NXT ( cSel_knskisymd, pst_trInfo->asyrckid[li_idx], pst_trInfo->stkno ) ;
			if ( li_retSts == MYAPP_SQL_DEADLOCK ) {
				//�f�b�h���b�N
				blnLockFlg = LC_true ;
				break ;
			} else if ( li_retSts < 0 ) {
				blnErrFlg = LC_true ;
				break ;
			}
			//	�����I�[�_�[���E�����`�F�b�N��񌟍�
			li_retSts = sFncSelKENORDER_REALCHK_NXT ( cSel_knskisymd,
								  pst_trInfo->trid,
								  ( 5 * (li_idx - li_cntSkip) ) + 1,
								  ( 5 * (li_idx - li_cntSkip) ) + 5,
								  &recKENORDER,
								  &recREALCHK,
								  &recCnt ) ;
			if ( li_retSts == MYAPP_SQL_DEADLOCK ) {
				//�f�b�h���b�N
				blnLockFlg = LC_true ;
				break ;
			} else if ( li_retSts < 0 ) {
				blnErrFlg = LC_true ;
				break ;
			}			
			if ( ( recCnt - svRecCnt ) == 0 ) {
				sFncPutLog ( TRCKIND_WARNING, __FILE__, "sFncOutput", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
			 		 	"�����I�[�_���A�܂��͑����`�F�b�N��񂪑��݂��܂��� KNSKISYMD='%s' TRID='%s' TRPOS %d-%d RCKID='%s'",
						cSel_knskisymd, pst_trInfo->trid, ( 5 * (li_idx - li_cntSkip) ) + 1, ( 5 * (li_idx - li_cntSkip) ) + 5, pst_trInfo->asyrckid[li_idx] ) ;
			 	blnNgFlg = LC_true ;
				break ;
			} else {
				svRecCnt = recCnt ;
			}
		}
	} 

	if ( gtBunchuFlg == MYAPP_BUNCHU_OK ) {
		li_retSts = sFncSelKENORDER ( cSel_knskisymd, pst_trInfo->trid, &li_MaxOrderTrpos );
		if ( li_retSts == MYAPP_SQL_DEADLOCK ) {
			//�f�b�h���b�N
			blnLockFlg = LC_true ;
		} else if ( li_retSts < 0 ) {
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
			li_retSts = insWsseqknri(cSel_knskisymd, cKnsgrp, pst_trInfo->trid, li_MaxOrderTrpos,
					 (li_len * li_Trknhsu + 1), (li_len * li_Trknhsu + li_MaxOrderTrpos) ) ;

			if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION) {
			    //�f�b�h���b�N or �d��
			    blnLockFlg = LC_true ;
			} else if ( li_retSts < 0 ) {
			    blnErrFlg = LC_true ;
			}
		}
	}

	/***
	 ***	�g�����U�N�V�����I��
	 ***/
	if ( blnErrFlg == LC_true || blnLockFlg == LC_true || blnNgFlg == LC_true ) {
	 	//	���[���o�b�N
		ZdbRollback () ;
	} else {
		//	�R�~�b�g
		ZdbCommit () ; 
	}

	/***
	 ***	�t�@�C���o��
	 ***/
	if ( blnErrFlg != LC_true && blnLockFlg != LC_true && blnNgFlg != LC_true && recCnt > 0 ) {
		//	�����I�[�_�[���
		li_retSts = sFncFileOutOnline ( pAppEnv, recKENORDER, recCnt ) ;
		if ( li_retSts < 0 ) {
			blnErrFlg = LC_true ;
		}
		//	�����I�[�_�[���
		li_retSts = sFncFileOutLane ( pAppEnv, recKENORDER, recCnt ) ;
		if ( li_retSts < 0 ) {
			blnErrFlg = LC_true ;
		}
	}

	free ( recKENORDER ) ;
	free ( recREALCHK ) ;

	if ( blnNgFlg == LC_true ) {
		return ( 1 ) ; /* ��񖢒����̗L��B�G���[�f�B���N�g���ֈړ��B */
	}
	if ( blnErrFlg == LC_true ) {
		return ( -1 ) ; /* �c�a�G���[�����B�G���[�f�B���N�g���ֈړ��B */
	}
	if ( blnLockFlg == LC_true ) {
		return ( 2 ) ; /* �c�a���b�N�����B�X�L�b�v���Ď���ɍď�������B */
	}
	return ( 0 ) ;
}
/******************************************************************************/
/*  �� �� ���@�FsFncFileOutOnline()			 			*/
/*  �@�\�T�v�@�F�����I�[�_�[�E�����`�F�b�N���t�@�C���o��			*/
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����			*/
/*�@ ��Q���� �FKenorder  *   		�����I�[�_�[�����\����		*/
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint								*/
/*					 0	����				*/
/*					-1	�ُ�				*/
/******************************************************************************/
static int
sFncFileOutOnline ( pAppEnv, precKenorder, precCnt )
struct appEnv		*pAppEnv ;
struct my_stKENORDER	*precKenorder ;
int			 precCnt ;
{
	FILE		*lfp_K ;
	int		 li_cntKessei ;
	char		 lc_recBuf_K[512] ;
	char		 lc_dataFileName_K[MYAPP_PATH_SIZE] ;
	char		 lc_dataFileName_tmp[MYAPP_PATH_SIZE] ;
	char		 lc_fileName_K[MYAPP_PATH_SIZE] ;
	char		 lc_fileName_tmp[MYAPP_PATH_SIZE] ;

	char		 SV_asyrckid[MYAPP_RKNO_SIZE] ;
	int		 SV_asyrckpos ;
	LC_BOOLEAN	 blnFirstFlg ;

	int		 idx ;

	struct tm	*timepos ;
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
	lfp_K   = NULL ;
	
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
				fclose ( lfp_K ) ;
				//�����I�[�_�[��� �t�@�C�����ύX
				if ( rename( lc_dataFileName_tmp, lc_dataFileName_K ) != 0 ) {
					//	�ُ�I��	LOG
					gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "rename", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"�t�@�C�����̕ύX�Ɏ��s���܂���[%s]", lc_fileName_K ) ;
					return ( -1 ) ;
				}
				sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"�I�����C���p�˗��t�@�C���o��[%s]", lc_dataFileName_K ) ;
			} else {
				blnFirstFlg = LC_false ;
			}

			/* �u���C�N�L�[������ */
			strcpy ( SV_asyrckid, precKenorder[idx].asyrckid ) ;
			SV_asyrckpos =  precKenorder[idx].asyrckpos ;

			//	�����I�[�_�[���t�@�C�����쐬
			sFncCreFileName ( lc_fileName_K, MYAPP_SEND_KIND_OD, 
							  precKenorder[idx].asyrckid, 
							  precKenorder[idx].asyrckpos, 
							  MYAPP_SEND_SFX, timepos ) ;
			sprintf ( lc_dataFileName_K, "%s/%s", pAppEnv->cDirOnl_Dat,lc_fileName_K);
			//	�����I�[�_�[���ꎟ�t�@�C�����쐬
			sFncCreFileName ( lc_fileName_tmp, MYAPP_SEND_KIND_OD, 
							  precKenorder[idx].asyrckid, 
							  precKenorder[idx].asyrckpos, 
							  MYAPP_SEND_SFX_TMP, timepos ) ;
			sprintf ( lc_dataFileName_tmp,  "%s/%s", pAppEnv->cDirOnl_Dat,lc_fileName_tmp);

			/* �t�@�C���I�[�v�� �����I�[�_�[���t�@�C�� */
			lfp_K  = fopen ( lc_dataFileName_tmp , "w" ) ;
			if ( lfp_K == NULL ) {
				//	�ُ�I��	LOG
				gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "fopen", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 			"�t�@�C���̃I�[�v���Ɏ��s���܂���[%s]",lc_dataFileName_K);
				return ( -1 ) ;
			}
			/* ������񑪒�L���m�F */
			if ( sFncSelCntKesseiOrder ( precKenorder[idx].knskisymd,
					 	     precKenorder[idx].asyrckid,
						     precKenorder[idx].asyrckpos, 
						     &li_cntKessei ) != 0 ) {
				if ( lfp_K != NULL ) {
					fclose ( lfp_K ) ;
				}
				//	�ُ�I��	LOG
				gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncSelCntKesseiOrder", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"�t�@�C���̏o�͂Ɏ��s���܂���[%s]", lc_dataFileName_K ) ;
				return ( -1 ) ;
			}
			if ( li_cntKessei > 0 ) {
				//	�������I�[�_�[��񃌃R�[�h�쐬
				if ( sFncOutRecKESSEI ( lfp_K, lc_recBuf_K, &precKenorder[idx], pAppEnv ) < 0 ) {
					if ( lfp_K != NULL ) {
						fclose ( lfp_K ) ;
					}
					//	�ُ�I��	LOG
					gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOutRecKESSEI", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"�t�@�C���̏o�͂Ɏ��s���܂���[%s]", lc_dataFileName_K ) ;
					return ( -1 ) ;
				}
			}
		}
		
		//	�����I�[�_�[��񃌃R�[�h�쐬
		if ( sFncOutRecKENORDER ( lfp_K, lc_recBuf_K, &precKenorder[idx], pAppEnv ) < 0 ) {
			if ( lfp_K != NULL ) {
				fclose ( lfp_K ) ;
			}
			//	�ُ�I��	LOG
			gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOutRecKENORDER", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�t�@�C���̏o�͂Ɏ��s���܂���[%s]", lc_dataFileName_K ) ;
			return ( -1 ) ;
		}
	}

	/***
	 ***	�t�@�C���o�͌㏈��
	 ***/
	//	�t�@�C���N���[�Y
	if ( lfp_K != NULL ) {
		fclose ( lfp_K ) ;
	}
	//�����I�[�_�[��� �t�@�C�����ύX
	if ( rename( lc_dataFileName_tmp, lc_dataFileName_K ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "rename", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�t�@�C�����̕ύX�Ɏ��s���܂���[%s -> %s]", lc_fileName_tmp, lc_fileName_K ) ;
		return ( -1 ) ;
	}

	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�I�����C���p�˗��t�@�C���o��[%s]", lc_dataFileName_K ) ;
	return ( 0 ) ;
}
/******************************************************************************/
/*  �� �� ���@�FsFncFileOutLane()			 			*/
/*  �@�\�T�v�@�F�����I�[�_�[�E�����`�F�b�N���t�@�C���o��			*/
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����			*/
/*�@ ��Q���� �FKenorder  *   		�����I�[�_�[�����\����		*/
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint								*/
/*					 0	����				*/
/*					-1	�ُ�				*/
/******************************************************************************/
static int
sFncFileOutLane ( pAppEnv, precKenorder, precCnt )
struct appEnv		*pAppEnv ;
struct my_stKENORDER	*precKenorder ;
int			 precCnt ;
{
	FILE		*lfp_Lane ;
	char		 lc_recBuf_Lane[512] ;
	char		 lc_asyrckidBuf[MYAPP_RKNO_SIZE] ;	
	char		 lc_dataFileName_Lane[MYAPP_PATH_SIZE] ;
	char		 lc_dataFileName_tmp[MYAPP_PATH_SIZE] ;
	char		 lc_fileName_Lane[MYAPP_PATH_SIZE] ;
	char		 lc_fileName_tmp[MYAPP_PATH_SIZE] ;

	char		 SV_asyrckid[MYAPP_RKNO_SIZE] ;
	int		 SV_asyrckpos ;
	LC_BOOLEAN	 blnFirstFlg ;

	int		 idx ;
 
	/***
	 ***	��������
	 ***/
	blnFirstFlg   = LC_true ;
	//	�u���C�N�L�[
	memset ( SV_asyrckid, '\0', sizeof ( SV_asyrckid ) ) ;
	SV_asyrckpos = -1 ;
	//	�ϐ�������
	lfp_Lane = NULL ;
	
	for ( idx = 0 ; idx < precCnt ; idx ++ ) {

		if ( strcmp ( SV_asyrckid, precKenorder[idx].asyrckid ) != 0 ){
			/* ����ȊO�̏���(�����I�[�_�[���t�@�C���o��, �t�@�C���N���[�X) */
			if ( blnFirstFlg != LC_true ) {
			 	//	�t�@�C���N���[�Y
				fclose ( lfp_Lane ) ;
				//�����I�[�_�[��� �t�@�C�����ύX
				if ( rename( lc_dataFileName_tmp, lc_dataFileName_Lane ) != 0 ) {
					//	�ُ�I��	LOG
					gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "rename", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"�t�@�C�����̕ύX�Ɏ��s���܂���[%s]", lc_fileName_Lane ) ;
					return ( -1 ) ;
				}
				sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"���݃��C���p�˗��t�@�C���o��[%s]", lc_dataFileName_Lane ) ;
			} else {
				blnFirstFlg = LC_false ;
			}

			/* �u���C�N�L�[������ */
			strcpy ( SV_asyrckid, precKenorder[idx].asyrckid ) ;
			SV_asyrckpos =  precKenorder[idx].asyrckpos ;

			//	���b�N�m�n
			memset ( lc_asyrckidBuf, '\0', sizeof ( lc_asyrckidBuf ) ) ;
			strcpy ( lc_asyrckidBuf, precKenorder[idx].asyrckid ) ;
			sFncTrim ( lc_asyrckidBuf ) ;

			/* �����I�[�_�[���t�@�C�����쐬 */
			sprintf ( lc_fileName_Lane, "%s%s", lc_asyrckidBuf, MYAPP_SEND_SFX ) ;
			sprintf ( lc_dataFileName_Lane, "%s/%s", pAppEnv->cDirLane_Dat,lc_fileName_Lane);
			/* �����I�[�_�[���ꎟ�t�@�C�����쐬 */
			sprintf ( lc_fileName_tmp, "%s%s", lc_asyrckidBuf, MYAPP_SEND_SFX_TMP ) ;
			sprintf ( lc_dataFileName_tmp,  "%s/%s", pAppEnv->cDirLane_Dat,lc_fileName_tmp);

			/* �����I�[�_�[���t�@�C�� �I�[�v�� */
			lfp_Lane  = fopen ( lc_dataFileName_tmp , "w" ) ;
			if ( lfp_Lane == NULL ) {
				//	�ُ�I��	LOG
				gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "fopen", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"�t�@�C���̃I�[�v���Ɏ��s���܂���[%s]",lc_dataFileName_tmp);
				return ( -1 ) ;
			}
			/* ���b�N�h�c���؂�ւ������A�w�b�_���R�[�h�쐬 */
			if ( sFncOutRecLaneHeader ( lfp_Lane, lc_recBuf_Lane, &precKenorder[idx] ) < 0 ) {
				//	�ُ�I��	LOG
				gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOutRecLane", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"�t�@�C���̏o�͂Ɏ��s���܂���[%s]", lc_dataFileName_tmp ) ;
				return ( -1 ) ;
			}
			/* ���b�N�h�c���؂�ւ������A�����I�[�_�[��񃌃R�[�h�쐬 */
			if ( sFncOutRecLane ( lfp_Lane, lc_recBuf_Lane, &precKenorder[idx] ) < 0 ) {
				//	�ُ�I��	LOG
				gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOutRecLane", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"�t�@�C���̏o�͂Ɏ��s���܂���[%s]", lc_dataFileName_tmp ) ;
				return ( -1 ) ;
			}
		}
		
		/* ���b�N�|�W�V�������؂�ւ������A�����I�[�_�[��񃌃R�[�h�쐬 */
		if ( SV_asyrckpos != precKenorder[idx].asyrckpos ){
			if ( sFncOutRecLane ( lfp_Lane, lc_recBuf_Lane, &precKenorder[idx] ) < 0 ) {
				//	�ُ�I��	LOG
				gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOutRecLane", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"�t�@�C���̏o�͂Ɏ��s���܂���[%s]", lc_dataFileName_tmp ) ;
				return ( -1 ) ;
			}
			SV_asyrckpos =  precKenorder[idx].asyrckpos ;
		}
	}

	//	�t�@�C���N���[�Y
	if ( lfp_Lane != NULL ) {
		fclose ( lfp_Lane ) ;
	}
	//�����I�[�_�[��� �t�@�C�����ύX
	if ( rename( lc_dataFileName_tmp, lc_dataFileName_Lane ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "rename", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
	 	 		"�t�@�C�����̕ύX�Ɏ��s���܂���[%s]", lc_fileName_Lane ) ;
		return ( -1 ) ;
	}

	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		     "���݃��C���p�˗��t�@�C���o��[%s]", lc_dataFileName_Lane ) ;
	return ( 0 ) ;
}
/******************************************************************************/
/*  �� �� ���@�FsFncTrFileRead()			 			*/
/*  �@�\�T�v�@�F�g���[�E���b�N�R�t�����Ǎ�				  	*/
/*	���L����  �F��Q������free						*/
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����		 	*/
/*�@ ��Q���� �Fchar *  	 	�g���[�E���b�N�R�t�����t�@�C����	*/
/*�@ ��R���� �Fstruct trInfo *   	�g���[�E���b�N�R�t�����i�[�\����    	*/
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint								*/
/*					 0	����				*/
/*					-1	�ُ�				*/
/*					 1	�f�[�^�ُ�			*/
/******************************************************************************/
static	int
sFncTrFileRead ( pAppEnv, pc_trFileName, pst_trInfo, li_rackCnt )
struct appEnv	*pAppEnv ;
char		*pc_trFileName ;
struct trInfo	*pst_trInfo ;
int		*li_rackCnt ;
{
	FILE		*lfp ;
	char		 lc_recBuf[MYAPP_RECV_RECSIZE] ;
	int	 	 li_recBuflen;
	int		 li_idx ;
	int		 li_idx_rack ;
	int		 li_retryCnt ;

	char		 lc_fileName[1024] ;
	struct stat	 lst_statBuf ;

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

	//	�\���̐ݒ�
	li_idx = 0 ;
	li_idx_rack = 0 ;
	memset ( pst_trInfo, '\0', sizeof ( struct trInfo ) ) ;
	//	�g���[�h�c�擾
	strncpy ( pst_trInfo->trid, lc_recBuf, 8 ) ;
	//	���b�N�h�c�擾
	while ( li_idx  < MYAPP_RACK_MAXCNT ) {
		strncpy ( pst_trInfo->asyrckid[li_idx], &lc_recBuf[ 8+(li_idx*5) ], 5 ) ;
		sFncTrim ( pst_trInfo->asyrckid[li_idx] ) ;
                if ( pst_trInfo->asyrckid[li_idx][0] != '\0' ) {
			li_idx_rack++ ;
                }
		li_idx++ ;
	}
	*li_rackCnt = li_idx_rack;

	//	�g���[�h�c�擾
	strncpy ( pst_trInfo->knskisymd, &lc_recBuf[108], 8 ) ;

	/***
	 ***	�X�g�b�J�[�m�n(�O�ǂ݈��̂��ߌŒ�Ƃ���)
	 ***/
	memcpy ( pst_trInfo->stkno, "10", sizeof ( pst_trInfo->stkno ) - 1 ) ;

	return ( 0 ) ;
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
/******************************************************************************/
/*  �� �� ���@�FsFncOutRecKENORDER()		 				*/
/*  �@�\�T�v�@�F�����I�[�_����񃌃R�[�h����				  	*/
/*  ���@�@�́@�F                                                              */
/*�@ ��Q���� �Fstruct my_stKENORDER *   	�����I�[�_���\����		*/
/*  �o�@�@�́@�F                                                              */
/*�@ ��P���� �Fchar 				*   	���R�[�h�i�[�o�b�t�@	*/
/*  ���A���@�F����								*/
/******************************************************************************/
static	int
sFncOutRecKENORDER ( pfp, p_recBuf, precKenorder, pAppEnv )
FILE					*pfp ;
char					*p_recBuf ;
struct my_stKENORDER	*precKenorder ;
struct appEnv	*pAppEnv ;
{
	int		retSts ;
	char		cYtiksbr[15+1];

	/* �Z�b�g����\���ߔ{���𕪐͋@�����ɕϊ����� */
	memset( cYtiksbr, '\0', sizeof ( cYtiksbr ) );
	strncpy( cYtiksbr, precKenorder->ytiksbr, sizeof ( cYtiksbr ) - 1 );
	sFncTrim ( cYtiksbr );
	if( strcmp( cYtiksbr, pAppEnv->cKskbrB10HY ) == 0 ){
		memset( cYtiksbr, ' ', sizeof ( cYtiksbr ) - 1 );
		strncpy( cYtiksbr, pAppEnv->cKskbrB10CD , strlen( pAppEnv->cKskbrB10CD ) );
	} else if ( strcmp( cYtiksbr, pAppEnv->cKskbrB2HY ) == 0 ) {
		memset( cYtiksbr, ' ', sizeof ( cYtiksbr ) - 1 );
		strncpy( cYtiksbr, pAppEnv->cKskbrB2CD , strlen( pAppEnv->cKskbrB2CD ) );
	} else {
		memset( cYtiksbr, ' ', sizeof ( cYtiksbr ) - 1 );
	}

	//	���R�[�h�쐬
	retSts = fprintf ( pfp, "%s,%s,%s,%s,%s,%s,%hd,%hd,%s,%s,%s,%s,%s,%s,%hd,%s,%s,%hd,%s,%hd,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%hd,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%hd,%s,%s\n",
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
				/* precKenorder->ytiksbr, */
				cYtiksbr,
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
/*  �� �� ���@�FsFncOutRecKESSEI()		 				*/
/*  �@�\�T�v�@�F�������I�[�_����񃌃R�[�h����			  	*/
/*  ���@�@�́@�F                                                              */
/*�@ ��Q���� �Fstruct my_stKENORDER *   	�����I�[�_���\����		*/
/*  �o�@�@�́@�F                                                              */
/*�@ ��P���� �Fchar 				*   	���R�[�h�i�[�o�b�t�@	*/
/*  ���A���@�F����								*/
/******************************************************************************/
static	int
sFncOutRecKESSEI ( pfp, p_recBuf, precKenorder, pAppEnv )
FILE					*pfp ;
char					*p_recBuf ;
struct my_stKENORDER	*precKenorder ;
struct appEnv	*pAppEnv ;
{
	int	retSts ;
	int	i ;
	char	cKesseiCd[4][7+1] ;

	strcpy( cKesseiCd[0], pAppEnv->cNyubiCD );
	strcpy( cKesseiCd[1], pAppEnv->cYoketsuCD );
	strcpy( cKesseiCd[2], pAppEnv->cOudanCD );
	strcpy( cKesseiCd[3], pAppEnv->cSeisyokuCD );
	for(i = 0; i <= 3; i++) {
	//	���R�[�h�쐬
		retSts = fprintf ( pfp, "%s,%s,%s,%s,%s,%s,%hd,%hd,%s,%s,%s,%s,%s,%s,%hd,%s,%s,%hd,%s,%hd,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%hd,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%hd,%s,%s\n",
					precKenorder->knskisymd,
					precKenorder->sriymd,
					precKenorder->kntno,
					precKenorder->kntketflg,
					"    ",
					cKesseiCd[i],
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
					"       ",
					precKenorder->seccd,
					precKenorder->bkfkkbn,
					precKenorder->smpcd,
					precKenorder->bskkbn,
					precKenorder->nbkmkcd,
					"   ",
					precKenorder->ysnlbl,
					"  ",
					precKenorder->fkhkknohjkbn,
					precKenorder->tbkjno,
					precKenorder->tbkjflg,
					precKenorder->htkfkhms,
					precKenorder->skflg,
					precKenorder->tskflg,
					precKenorder->tktflg,
					/* precKenorder->ytiksbr, */
					" ",
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
	}
	return ( 0 ) ;
}
/******************************************************************************/
/*  �� �� ���@�FsFncOutRecLaneHeader()		 				*/
/*  �@�\�T�v�@�F�������[���p�˗����w�b�_���R�[�h����			  	*/
/*  ���@�@�́@�F                                                              */
/*�@ ��Q���� �Fstruct my_stKENORDER *   	�����I�[�_���\����		*/
/*  �o�@�@�́@�F                                                              */
/*�@ ��P���� �Fchar 				*   	���R�[�h�i�[�o�b�t�@	*/
/*  ���A���@�F����								*/
/******************************************************************************/
static	int
sFncOutRecLaneHeader ( pfp, p_recBuf, precKenorder )
FILE			*pfp ;
char			*p_recBuf ;
struct my_stKENORDER	*precKenorder ;
{
	int	retSts ;
	int	iLine ;	
	char	lc_asyrckidBuf[MYAPP_RKNO_SIZE] ;
	char	lc_knskisymdBuf[10+1] ;
	char	lc_yyyyBuf[4+1] ;
	char	lc_mmBuf[2+1] ;
	char	lc_ddBuf[2+1] ;

	retSts = sFncSelZsLineMst ( precKenorder->knskisymd, precKenorder->knsgrp, &iLine ) ;
	if ( retSts < 0 ) {
		return ( -1 ) ;
	}

	//	�����J�n��
	memset ( lc_knskisymdBuf, '\0', sizeof ( lc_knskisymdBuf ) ) ;
	strncpy ( lc_knskisymdBuf, precKenorder->knskisymd, 10 ) ;
	memset ( lc_yyyyBuf, '\0', sizeof ( lc_yyyyBuf ) ) ;
	strncpy ( lc_yyyyBuf, lc_knskisymdBuf, 4 ) ;
	memset ( lc_mmBuf, '\0', sizeof ( lc_mmBuf ) ) ;
	strncpy ( lc_mmBuf, &lc_knskisymdBuf[5], 2 ) ;
	memset ( lc_ddBuf, '\0', sizeof ( lc_ddBuf ) ) ;
	strncpy ( lc_ddBuf, &lc_knskisymdBuf[8], 2 ) ;
	
	//	���b�N�m�n
	memset ( lc_asyrckidBuf, '\0', sizeof ( lc_asyrckidBuf ) ) ;
	strcpy ( lc_asyrckidBuf, precKenorder->asyrckid ) ;
	sFncTrim ( lc_asyrckidBuf ) ;
/*
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "sFncOutRecLaneHeader[%s,%s]", precKenorder->knskisymd, lc_asyrckidBuf ) ;
*/
	//	���R�[�h�쐬
	retSts = fprintf ( pfp, "%s%s%s%s%d\r\n",
				lc_yyyyBuf ,
				lc_mmBuf ,
				lc_ddBuf ,
				lc_asyrckidBuf,
				iLine ) ;
	if ( retSts < 0 ) {
		return ( -1 ) ;
	}
	return ( 0 ) ;
}
/******************************************************************************/
/*  �� �� ���@�FsFncOutRecLane()		 				*/
/*  �@�\�T�v�@�F�������[���p�˗���񃌃R�[�h����			  	*/
/*  ���@�@�́@�F                                                              */
/*�@ ��Q���� �Fstruct my_stKENORDER *   	�����I�[�_���\����		*/
/*  �o�@�@�́@�F                                                              */
/*�@ ��P���� �Fchar 				*   	���R�[�h�i�[�o�b�t�@	*/
/*  ���A���@�F����								*/
/******************************************************************************/
static	int
sFncOutRecLane ( pfp, p_recBuf, precKenorder )
FILE			*pfp ;
char			*p_recBuf ;
struct my_stKENORDER	*precKenorder ;
{
	int		retSts ;
	//	���R�[�h�쐬
/*
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"sFncOutRecLane[%03d,%s]", precKenorder->asyrckpos, precKenorder->irino ) ;
*/
	retSts = fprintf ( pfp, "%03d%s\r\n",
				precKenorder->asyrckpos,
				precKenorder->irino ) ;
	if ( retSts < 0 ) {
		return ( -1 ) ;
	}
	return ( 0 ) ;
}
/******************************************************************************/
/*  �� �� ���@�FsFncCreFileName()						*/
/*  �@�\�T�v�@�F�I�[�_�[�t�@�C��������						*/
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *   	�t�@�C�����i�[�o�b�t�@				*/
/*�@ ��Q���� �Fchar *   	���						*/
/*�@ ��R���� �Fchar *   	���b�N�m�n					*/
/*�@ ��S���� �Fshort   	�|�W�V����					*/
/*�@ ��T���� �Fchar *   	�g���q						*/
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fchar *								*/
/*					 NULL	�I�[				*/
/*					 NULL�ȊO	������			*/
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
	return ;
}
/******************************************************************************/
/*  �� �� ���@�FsFncTrim()  			 				*/
/*  �@�\�T�v�@�F������O��̃X�y�[�X���폜����				  	*/
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *   	�ҏW������					*/
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F����								*/
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
/*  �� �� ���@�FsFncFileRename()  			 			*/
/*  �@�\�T�v�@�F�t�@�C�����ړ�����B						*/
/*	�@�@�@�@�ړ���ɓ������O�̃t�@�C�������݂����ꍇ�̓C���N�������g����B	*/
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *   	�ړ����f�B���N�g��				*/
/*�@ ��Q���� �Fchar *   	�ړ����t�@�C����				*/
/*�@ ��R���� �Fchar *   	�ړ���f�B���N�g��				*/
/*�@ ��S���� �Fchar *   	�ړ���t�@�C��					*/
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint								*/
/*					 0	����				*/
/*					-1	�ُ�				*/
/******************************************************************************/
static int
sFncFileRename ( pc_fromDir, pc_fromFileName, pc_toDir, pc_toFileName )
char	*pc_fromDir ;
char	*pc_fromFileName ;
char	*pc_toDir ;
char	*pc_toFileName ;
{
	char		lc_fromPath[MYAPP_PATH_SIZE] ;
	char		lc_toPath[MYAPP_PATH_SIZE] ;
	int		ret = 0;
	int		retry_cnt = 1;
	struct stat	fst;

	sprintf ( lc_fromPath, "%s/%s", pc_fromDir, pc_fromFileName ) ;
	sprintf ( lc_toPath,   "%s/%s", pc_toDir,   pc_toFileName ) ;

	ret = stat ( lc_toPath, &fst ) ;
	if (ret == 0) {
		/* ���Ƀt�@�C�������݂���B�����t�@�C���������� */
		while ( ret == 0 ) {
			sprintf ( lc_toPath, "%s/%s%02d", pc_toDir, pc_toFileName, retry_cnt ) ;
			ret = stat ( lc_toPath, &fst ) ;
			retry_cnt ++ ;
			if ( retry_cnt > 99 ) {
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncFileRename", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
 	 			 		 "�t�@�C���̃J�E���^���ő�l�𒴂��܂���" ) ;
				return ( -1 ) ;
			}
		}
	}

	if ( rename ( lc_fromPath, lc_toPath ) < 0 ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncFileRename:rename", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
 	 	 		 "�t�@�C���̈ړ��Ɏ��s���܂���[%s->%s]", lc_fromPath, lc_toPath ) ;
		return ( -1 ) ;
	}
	
	return ( 0 ) ;
}
/******************************************************************************/
/*  �� �� ���@�FsFncShmCrt()				 			*/
/*  �@�\�T�v�@�F���L����������							*/
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����			*/
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint								*/
/*					 0	����				*/
/*					-1	�ُ�				*/
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
/*  �� �� ���@�FsFncShmGet()				 			*/
/*  �@�\�T�v�@�F���L�������擾							*/
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����		 	*/
/*�@ ��Q���� �Fint *   			�l				*/
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint								*/
/*					 0	����				*/
/*					-1	�ُ�				*/
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
/*  �� �� ���@�FsFncShmDel()				 			*/
/*  �@�\�T�v�@�F���L�������폜							*/
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\���́B		 	*/
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint								*/
/*					 0	����				*/
/*					-1	�ُ�				*/
/******************************************************************************/
static int
sFncShmDel ( pAppEnv )
struct appEnv	*pAppEnv ;
{

	//	�폜	
	if ( shmctl ( pAppEnv->shm_Id, IPC_RMID, NULL) < 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}	
/******************************************************************************/
/*  �� �� ���@�FsFncFileCompar()			 			*/
/*  �@�\�T�v�@�F�t�@�C������r�y�R�[���o�b�N�֐��z			  	*/
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *   	��r������					*/
/*�@ ��Q���� �Fchar *   	��r������					*/
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint								*/
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
/*  �� �� ���@�FsFncFileFillter()						*/
/*  �@�\�T�v�@�F�t�@�C���t�B���^�[�y�R�[���o�b�N�֐��z				*/
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct dirent *		�f�B���N�g���\����		 	*/
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint								*/
/*					 0	�ΏۊO�t�@�C��			*/
/*					 1	�Ώۃt�@�C��			*/
/******************************************************************************/
static	int
sFncFileFillter ( pdirEnt ) 
struct dirent *pdirEnt ;
{
		int		li_len ;

		//�����񒷃`�F�b�N
		li_len = strlen ( pdirEnt->d_name )  ;
		if ( li_len != 12 ) {
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

/****************************************************************************/
/*  �� �� ���@�FinsWsseqknri()							*/
/*  �@�\�T�v�@�F����WS�̏����e�[�u���ɓo�^����				*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �F								*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����							*/
/* �@�@�@�@�@�@�@-1     : ���s							*/
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
	
	return( 0 );
}

/******************************************************************************/
/*  �� �� ���@�Fmain()								*/
/*  �@�\�T�v�@�F���C���֐�							*/
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *pcLogName	�y�C�Ӂz���O�t�@�C�������w�肷��B		*/
/*					��NULL���w�肵���ꍇ��INI�t�@�C�����	*/
/*					  ���O�����擾����B			*/
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F  0     : ����							*/
/* �@�@�@�@�@�@�@-1     : ���s							*/
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

	exit ( 0 ) ;
}

/** End of File ***************************************************************/
