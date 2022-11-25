/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FZD101.c                                                      */
/* �@�T�@�@�@�v�F���O�f�[�^�x�[�X�o�̓f�[����                                 */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/15     �F��O�K       �V�K�쐬                           */
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
#include <syslog.h>

#include "bmlprm.h"
#include "bmllog.h"
#include "bml_misc.h"
#include "bml_misc.h"
#include "bml_date.h"
#include "ZD101.h"

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

/******************************************************************************/
/* �֐��錾                                                                   */
/******************************************************************************/
//	�c�a�o�͊֐�
static	int		sFncDbWrite ( char * ) ;

//	���L����������֐�
static	int		sFncShmCrt ( struct appEnv * ) ;
static	int		sFncShmGet ( struct appEnv * , int *) ;
static	int		sFncShmDel ( struct appEnv * ) ;

//	�R�[���o�b�N�֐�
static	int		sFncFileFillter ( struct dirent * ) ;

//	�V�X�e�����O�o��
static	void	sFncSyslog ( int, char *, char * ) ;

//	�g���[�X�p
static	void	_sFncApllogDisp ( struct stcLogAPLLOG * ) ;

/******************************************************************************/
/*  �� �� ���@�FinitFunction()												  */
/*  �@�\�T�v�@�F���������֐�												  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fint				   	���C���p�����[�^��						  */
/*�@ ��Q���� �Fchar *   			���C���p�����[�^						  */
/*�@ ��R���� �Fstruct	appEnv *   	�v���O�������\����		 			  */
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
	long	 ll_retSts ;
	BMLPRM	*bp ;
	char	 lc_prmBuf[256] ;
	char	 lc_logBuf[1024] ;

	/***
	 ***	������	
	 ***/
	//	�G���[�X�e�[�^�X�ύX
	gintErrorCode = 0 ;

	//	�v���O�������ϐ�������
	memset ( pAppEnv , '\0', sizeof ( struct appEnv ) ) ;


	/***
	 ***	�����`�F�b�N	
	 ***/
	//	�������`�F�b�N	
	if ( argc != 2 ) {
		//	�ُ�I��	LOG
		sFncSyslog ( LOG_ERR, "", "A parameter file is not appointed." ) ;
		return ( -1 ) ;
	}

	/***
	 ***	�p�����[�^�t�@�C�����ޔ�
	 ***/
	//	�p�����[�^�t�@�C���I�[�v��	
	bp = ZbmlPrmOpen ( argv[1] ) ;		
	if ( bp == NULL ) {
		gintErrorCode = MYAPP_STSCODE_ERR_PRM;
		sprintf ( lc_logBuf, "Parameter file cannot open.[%s]", argv[1] ) ;
		sFncSyslog ( LOG_ERR, "ZbmlPrmOpen()", lc_logBuf ) ;
		return ( -1 ) ;
	}

	//	�f�[�^�x�[�X��
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_DB_NAME, 
						pAppEnv->cDb_Name ) != 0 ) {
		gintErrorCode = MYAPP_STSCODE_ERR_PRM;
		sprintf ( lc_logBuf, "Failed in the acquisition of a parameter value.[%s]", MYAPP_PRM_DB_NAME ) ;
		sFncSyslog ( LOG_ERR, "ZbmlPrmGetVal()", lc_logBuf ) ;
		return ( -1 ) ;
	}
	//	���[�U��	
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_DB_USER, 
						pAppEnv->cDb_User ) != 0 ) {
		gintErrorCode = MYAPP_STSCODE_ERR_PRM;
		sprintf ( lc_logBuf, "Failed in the acquisition of a parameter value.[%s]", MYAPP_PRM_DB_USER ) ;
		sFncSyslog ( LOG_ERR, "ZbmlPrmGetVal()", lc_logBuf ) ;
		return ( -1 ) ;
	}
	//	�p�X���[�h��
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_DB_PASSWD, 
						pAppEnv->cDb_Passwd ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM;
		sprintf ( lc_logBuf, "Failed in the acquisition of a parameter value.[%s]", MYAPP_PRM_DB_PASSWD ) ;
		sFncSyslog ( LOG_ERR, "ZbmlPrmGetVal()", lc_logBuf ) ;
		return ( -1 ) ;
	}
	//	�Ď��f�B���N�g��	
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_DIR_WATCH, 
						pAppEnv->cDir_Watch ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM;
		sprintf ( lc_logBuf, "Failed in the acquisition of a parameter value.[%s]", MYAPP_PRM_DIR_WATCH ) ;
		sFncSyslog ( LOG_ERR, "ZbmlPrmGetVal()", lc_logBuf ) ;
		return ( -1 ) ;
	}
	//	���L�������L�[�擾
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_SHM_KEY, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM;
		sprintf ( lc_logBuf, "Failed in the acquisition of a parameter value.[%s]", MYAPP_PRM_SHM_KEY ) ;
		sFncSyslog ( LOG_ERR, "ZbmlPrmGetVal()", lc_logBuf ) ;
		return ( -1 ) ;
	}
	pAppEnv->shm_Key = atoi ( lc_prmBuf ) ;
	//	SLEEPSEC�擾
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_SLEEP_SEC, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM;
		sprintf ( lc_logBuf, "Failed in the acquisition of a parameter value.[%s]", MYAPP_PRM_SLEEP_SEC ) ;
		sFncSyslog ( LOG_ERR, "ZbmlPrmGetVal()", lc_logBuf ) ;
		return ( -1 ) ;
	}
	pAppEnv->sleep_Sec= atoi ( lc_prmBuf ) ;

	//	�p�����[�^�t�@�C���N���[�Y	
	ZbmlPrmClose ( bp ) ;

	/***
	 ***	���L����������	
	 ***/
	if ( sFncShmCrt ( pAppEnv ) < 0 ) {
		return ( -1 ) ;
	}

	/***
	 ***	�f�[�^�x�[�X�I�[�v��
	 ***/
	ll_retSts = ZdbConnect( pAppEnv->cDb_Name, 
							pAppEnv->cDb_User, pAppEnv->cDb_Passwd ) ;
	if ( ll_retSts != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_DB ;
		sprintf ( lc_logBuf, "Cannot be connected to a database.[DB=%s USR=%s PASS=%s]", pAppEnv->cDb_Name, pAppEnv->cDb_User, pAppEnv->cDb_Passwd ) ;
		sFncSyslog ( LOG_ERR, "ZdbConnect()", lc_logBuf ) ;
		return ( -1 ) ;
	}

	return ( 0 ) ; 
}
/******************************************************************************/
/*  �� �� ���@�FmainFunction()												  */
/*  �@�\�T�v�@�F���C�������֐�												  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct	appEnv *   	�v���O�������\����		 			  */
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
	int					  li_fileCnt ;				
	char				  lc_fileName[1024] ;
	struct stat			  lst_statBuf ;
	char	 			  lc_logBuf[1024] ;


	/***
	 ***	���O���f�B���N�g���Ď�	
	 ***		�i�v���[�v
	 ***		��~�R�}���h�ŏI��
	 ***/
	while ( 1 ) {

		//	�t�@�C�����擾
		if ( ( li_fileCnt = scandir ( pAppEnv->cDir_Watch, 
									  &lpst_dirBuf,
									  (void*)sFncFileFillter,
					   				  alphasort ) ) < 0 ) {
			//	�ُ�I��	LOG
			gintErrorCode = MYAPP_STSCODE_ERR_DIR;
			sFncSyslog ( LOG_ERR, "scandir()", "Cannot acquire a file name." ) ;
			return ( -1 ) ;
		}

		//	�c�a�o�̓��[�v
		for ( li_idx = 0 ; li_idx < li_fileCnt ; li_idx ++ ) {
			sprintf ( lc_fileName, "%s/%s", pAppEnv->cDir_Watch, 
											lpst_dirBuf[li_idx]->d_name ) ;

			//  �ʏ�t�@�C���̂ݏ������s��
			if ( stat ( lc_fileName, &lst_statBuf ) < 0 ) {
				//  �ُ�I��    LOG
				gintErrorCode = MYAPP_STSCODE_ERR_DIR;
				sFncSyslog ( LOG_ERR, "stat()", "Cannot acquire a file information." ) ;
				return ( -1 ) ;
			}
			if ( !S_ISREG ( lst_statBuf.st_mode ) ) {
				continue ;
			}

			if ( sFncDbWrite ( lc_fileName ) < 0 ) {
loging ( "���[���o�b�N\n" ) ;
				ZdbRollback () ;					//	���[���o�b�N
			} else {
loging ( "�R�~�b�g\n" ) ;
				ZdbCommit () ; 						//	�R�~�b�g
				unlink ( lc_fileName ) ;			//	�t�@�C���폜
			}
				
			//	���
			free ( lpst_dirBuf[li_idx] ) ;

			//	
			if ( sFncShmGet ( pAppEnv, &li_stopFlg ) < 0 ) {
				return ( -1 ) ;
			}
			if ( li_stopFlg == 1 ) {
				break ;
			}
		}
//break ;

		/***
		 *** ��~�R�}���h�m�F
		 ***/
		if ( sFncShmGet ( pAppEnv, &li_stopFlg ) < 0 ) {
			return ( -1 ) ;
		}
		if ( li_stopFlg == 1 ) {
			break ;
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
	if ( sFncShmDel ( pAppEnv ) < 0 ) {
		return ;
	}
	
	return ;
}
/******************************************************************************/
/*  �� �� ���@�FsFncDbWrite()			 									  */
/*  �@�\�T�v�@�F�f�[�^�x�[�X�o��							  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *			   		�t�@�C����							  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
static	int
sFncDbWrite ( pc_trFileName )
char			*pc_trFileName ;
{
	FILE				*lfp ;
	long				 ll_retSts ;
	char				 lc_logBuf[1024] ;
	struct stcLogAPLLOG  recAPLLOG ;

	//	�I�[�v��	
	lfp  = fopen ( pc_trFileName, "rb" ) ;
	if ( lfp == NULL ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
		sprintf ( lc_logBuf, "Cannot open a file .[%s]",pc_trFileName ) ;
		sFncSyslog ( LOG_ERR, "fopen()", lc_logBuf ) ;
		return ( -1 ) ;
	}

	//	�c�a�o�̓��[�v
	while ( 1 ) {
		if ( fread ( &recAPLLOG, sizeof ( recAPLLOG ), 1, lfp ) < 1 ) {
			if ( ferror ( lfp ) ) {
				gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
				sprintf ( lc_logBuf, "Cannot read a file .[%s]", pc_trFileName ) ;
				sFncSyslog ( LOG_ERR, "fread()", lc_logBuf ) ;
				fclose ( lfp ) ;
				return ( -1 ) ;
			}
			if ( feof ( lfp ) ) {
				break ;
			}
		}
_sFncApllogDisp ( &recAPLLOG ) ;
		ll_retSts = sFncInsKENPOS ( &recAPLLOG )  ;
		if ( ll_retSts != 0 ) {
			gintErrorCode = MYAPP_STSCODE_ERR_DB ;
			sFncSyslog ( LOG_ERR, "sFncInsKENPOS()", "Cannot insert Apllog." ) ;
			fclose ( lfp ) ;
			return ( -1 ) ;
		}
	}
	
	//	�N���[�Y	
	fclose ( lfp ) ;

	//	�R�~�b�g

	return ( 0 ) ;
}
/******************************************************************************/
/*  �� �� ���@�FsFncSyslog()				 								  */
/*  �@�\�T�v�@�F�V�X�e�����O�o��							  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fint 			   	�v���C�I���e�B�[						  */
/*�@ ��Q���� �Fchar *   			�֐���									  */
/*�@ ��R���� �Fchar * 		  		���b�Z�[�W								  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
static void
sFncSyslog ( piPri, pcFncname, pcMsg ) 
int		 piPri ;
char	*pcFncname ;
char	*pcMsg ;
{
#if defined ( _SYSLOGOUT )
	if ( errno != 0 ) {
		syslog ( piPri, "Error: Function %s %s (errno=%d msg=%m)",
						pcFncname, pcMsg, errno ) ;
	} else {
		syslog ( piPri, "Error: Function %s %s (errno=%d)",
						pcFncname, pcMsg, errno ) ;
	}
#endif
#if defined ( _TRACE )
	if ( errno != 0 ) {
		fprintf ( stderr, "Error: Function %s %s (errno=%d msg=%s)\n",
							pcFncname, pcMsg, errno, strerror ( errno ) ) ;
	} else {
		fprintf ( stderr, "Error: Function %s %s (errno=%d)\n",
							pcFncname, pcMsg, errno ) ;
	}
#endif
}
/******************************************************************************/
/*  �� �� ���@�FsFncShmCrt()				 								  */
/*  �@�\�T�v�@�F���L����������								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����		 	      */
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
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		sFncSyslog ( LOG_ERR, "shmget()", "Cannot assign shared memory." ) ;
		return ( -1 ) ;
	}

	//	�A�^�b�`	
	shmData = ( int * ) shmat ( pAppEnv->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		sFncSyslog ( LOG_ERR, "shmat()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}
loging ( "%s : ���L������[CRT] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n", MYAPP_APP_NAME, pAppEnv->shm_Key, pAppEnv->shm_Id, *shmData, shmData ) ;

	//	�l�ݒ�	
	*shmData = 0 ;

	//	�f�^�b�`	
	if ( shmdt ( shmData ) == -1 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		sFncSyslog ( LOG_ERR, "shmdt()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncShmGet()				 								  */
/*  �@�\�T�v�@�F���L�������擾								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����			 	      */
/*�@ ��Q���� �Fint *   			�l								 	      */
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
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		sFncSyslog ( LOG_ERR, "shmat()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}

	//	�l�ݒ�	
	*pshmData = *shmData ;

loging ( "%s : ���L������[GET] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n", MYAPP_APP_NAME, pAppEnv->shm_Key, pAppEnv->shm_Id, *shmData, shmData ) ;
	//	�f�^�b�`	
	if ( shmdt ( shmData ) == -1 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		sFncSyslog ( LOG_ERR, "shmdt()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncShmDel()				 								  */
/*  �@�\�T�v�@�F���L�������폜								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����			 	      */
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

loging ( "%s : ���L������[DEL] shmKey[%d]-ID[%d]\n", MYAPP_APP_NAME, pAppEnv->shm_Key, pAppEnv->shm_Id) ;
	//	�폜	
	if ( shmctl ( pAppEnv->shm_Id, IPC_RMID, NULL) < 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		sFncSyslog ( LOG_ERR, "shmctl()", "Cannot operate shared memory." ) ;
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


		//�t�@�C���^�C�v�`�F�b�N
/*
		if ( pdirEnt->d_type != DT_REG ) {
			return ( 0 ) ;
		}	
*/

		//������
		li_len = strlen ( pdirEnt->d_name )  ;

		//�g���q�`�F�b�N
		if ( memcmp ( &(pdirEnt->d_name[li_len-strlen(MYAPP_LOG_SFX)]), 
					  MYAPP_LOG_SFX, 
					  strlen ( MYAPP_LOG_SFX ) ) != 0 ) {
			return ( 0 ) ;
		}
		return ( 1 ) ;
}

/******************************************************************************/
/*  �� �� ���@�F_sFncEnvDip()				 								  */
/*  �@�\�T�v�@�F�v���O�������ϐ��o�͊֐��y�g���[�X�p�z	  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\���́B		 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F����														  */
/******************************************************************************/
static void
_sFncEnvDip( pAppEnv )
struct appEnv	*pAppEnv ;
{
#if defined ( _TRACE )
loging ( "########## %s  - �p�����[�^ ##########\n", MYAPP_APP_NAME ) ;
loging ( "\t%s : [%s]\n", MYAPP_PRM_DB_NAME,   pAppEnv->cDb_Name ) ;
loging ( "\t%s : [%s]\n", MYAPP_PRM_DB_USER,   pAppEnv->cDb_User ) ;
loging ( "\t%s : [%s]\n", MYAPP_PRM_DB_PASSWD, pAppEnv->cDb_Passwd ) ;
loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_WATCH, pAppEnv->cDir_Watch ) ;
loging ( "\t%s : [%d]\n", MYAPP_PRM_SHM_KEY,   pAppEnv->shm_Key ) ;
loging ( "\t%s : [%d]\n", MYAPP_PRM_SLEEP_SEC, pAppEnv->sleep_Sec ) ;
loging ( "########## %s  - �p�����[�^ ##########\n", MYAPP_APP_NAME ) ;
#endif
}
/******************************************************************************/
/*  �� �� ���@�F_sFncKenorderDisp()			 								  */
/*  �@�\�T�v�@�F�����I�[�_�[���o�͊֐��y�g���[�X�p�z  					  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �FKenorder *   	�����I�[�_�[���\����				 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F����														  */
/******************************************************************************/
static void
_sFncApllogDisp ( precApllog )
struct stcLogAPLLOG	*precApllog ;
{
#if defined ( _TRACE )
loging ( "#################################################################\n" ) ;
loging ( "# sydate      : [%s]\n",  precApllog->sydate ) ;
loging ( "# sytime      : [%s]\n",  precApllog->sytime ) ;
loging ( "# tracekbn    : [%c]\n",  precApllog->tracekbn ) ;
loging ( "# pcname      : [%s]\n",  precApllog->pcname ) ;
loging ( "# proccessid  : [%ld]\n", precApllog->proccessid ) ;
loging ( "# loginid     : [%s]\n",  precApllog->loginid ) ;
loging ( "# wkupapp     : [%s]\n",  precApllog->wkupapp ) ;
loging ( "# srcname     : [%s]\n",  precApllog->srcname ) ;
loging ( "# funcname    : [%s]\n",  precApllog->funcname ) ;
loging ( "# getline     : [%d]\n",  precApllog->getline ) ;
loging ( "# procflg     : [%s]\n",  precApllog->procflg ) ;
loging ( "# errcode     : [%s]\n",  precApllog->errcode ) ;
loging ( "# message     : [%s]\n",  precApllog->message.data ) ;
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

	struct appEnv	 sEnv ;

	/***
	 ***	�o�b�N�O���E���h���s
	 ***/
	if ( daemon ( 1, 0 ) < 0 ) {
		exit ( 9 ) ;
	}

	/***
	 ***	��������	
	 ***/
	if ( initFunction ( argc, argv, &sEnv )  != 0 ) {
		fprintf ( stderr, "%s : Error initFunction [%d]\n", MYAPP_APP_NAME, gintErrorCode ) ;
		exit ( 9 ) ;
	}
	_sFncEnvDip ( &sEnv ) ;
	
	/***
	 ***	�又��	
	 ***/
	if ( mainFunction ( &sEnv )  != 0 ) {
		fprintf ( stderr, "%s : Error mainFunction [%d]\n", MYAPP_APP_NAME, gintErrorCode ) ;
		exit ( 9 ) ;
	}

	/***
	 ***	�I������	
	 ***/
	endFunction ( &sEnv ) ;
	fprintf ( stderr, "%s : Error mainFunction [%d]\n", MYAPP_APP_NAME, gintErrorCode ) ;
}

/** End of File ***************************************************************/
