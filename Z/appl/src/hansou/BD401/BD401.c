/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FBD401.c                                                      */
/* �@�T�@�@�@�v�F�T���v���[�f�[���� 	                                      */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/31     �F��O�K       �V�K�쐬                           */
/*  1.01     2006/12/06   YOON JONG JIN    �G���[�ǉ�                         */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <syslog.h>
#include <dirent.h>

#include "bml_base.h"
#include "bmllog.h"
#include "bmlprm.h"
#include "BD401.h"

/******************************************************************************/
/* Define�錾       	                                                      */
/******************************************************************************/
//	TRACE
/*
#if defined ( _TRACE )
#define malloc(a)   _malloc(a, __FILE__, __LINE__)
#define free(p)     _free(p, __FILE__, __LINE__)
#endif
*

/******************************************************************************/
/* �\���̐錾       	                                                      */
/******************************************************************************/

/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/
MYAPP_STSCODE		 gintErrorCode ;
static  char		*gpToken ;						//  sFncToken�p�ÓI�|�C���^
struct stcLogMember	 gstLogMem ;					//  ���O�o�͏��

static	char		 gMatchOrder[256] ;
static	char		 gDirIA_Idx[MYAPP_PATH_SIZE] ;

/******************************************************************************/
/* �֐��錾 		                                                          */
/******************************************************************************/
//	��M�����֘A	
static	int		sFncRcevMain ( struct appEnv *, int ) ;
static	int		sFncOederFileMove ( struct appEnv *, char *, char *) ;

//	�t�@�C�������֘A�y�R�[���o�b�N�z
static	int		sFncFileCompar ( struct dirent **, struct dirent ** )  ;
static	int		sFncFileFillter ( struct dirent * ) ;

//	���L����������֐�
static	int		sFncShmCrt ( struct appEnv * ) ;
static	int		sFncShmGet ( struct appEnv *, int *) ;
static	int		sFncShmDel ( struct appEnv * ) ;

//  �V�X�e�����O�o��
static  void    sFncSyslog ( int, char *, char * ) ;

//	���̑��֐�
static  char*   sFncToken ( char * ) ;
static  int     sFncFileRename ( char *, char *, char *, char * ) ;
static	void	sFncTrim ( char * ) ;

/******************************************************************************/
/*  �� �� ���@�FinitFunction()												  */
/*  �@�\�T�v�@�F���������֐�												  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fint   				���C���p�����[�^��			 			  */
/*�@ ��Q���� �Fchar *   			���C���p�����[�^			 			  */
/*  �o�@�@�́@�F                                                              */
/*�@ ��R���� �Fstruct	appEnv *   	�v���O�������\����		 			  */
/*  ���A���@�F RTN_OK		: ����											  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
int
initFunction( argc, argv, pAppEnv )
int					 argc ;
char				*argv[] ;
struct appEnv		*pAppEnv ;
{
	long	 	 ll_retSts ;
	int	 		 li_retSts ;
	BMLPRM		*bp ;
	char	 	 lc_prmBuf[256] ;
	char		*lc_login ;

	char	   **bufPrmIA ;
	int			 cntPrmIA ;
	char		*bufToken ;
	int			 idx ;

	/***
	 ***    �����`�F�b�N
	 ***/
    if ( argc != 2 ) {
        fprintf ( stderr, "%s : There is an error in a command parameter\n", MYAPP_APP_NAME ) ;
        return ( RTN_NG ) ;
    }

	/***
	 ***	���O�I�[�v��
	 ***/
	if ( ZbmlOpenLog ( argv[1] ) != 0 ) {
		return ( RTN_NG ) ;
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
		return ( RTN_NG ) ;
	}
	 ***/

	/***
	 ***	�p�����[�^�t�@�C�����ޔ�
	 ***/
	//	�p�����[�^�t�@�C���I�[�v��	
	bp = ZbmlPrmOpen ( argv[1] ) ;		
	if ( bp == NULL ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmOpen", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^�t�@�C���̃I�[�v���Ɏ��s���܂���[%s]", argv[1] ) ;
		return ( RTN_NG ) ;
	}
	//	�|�[�g	
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_PORT, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_PORT ) ;
		return ( RTN_NG ) ;
	}
	pAppEnv->Port = atoi ( lc_prmBuf ) ;

	//	�f�[�^�x�[�X��
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_DB_NAME, pAppEnv->cDb_Name ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DB_NAME ) ;
		return ( RTN_NG ) ;
	}
	//	�f�[�^�x�[�X���[�U
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_DB_USER, pAppEnv->cDb_User ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DB_USER ) ;
		return ( RTN_NG ) ;
	}
	//	�f�[�^�x�[�X�p�X���[�h
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_DB_PASSWD, pAppEnv->cDb_Passwd ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DB_PASSWD ) ;
		return ( RTN_NG ) ;
	}
	//	���L�������L�[�擾
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_SHM_KEY, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_SHM_KEY ) ;
		return ( RTN_NG ) ;
	}
	pAppEnv->shm_Key = atoi ( lc_prmBuf ) ;
	//	�^�C���A�E�g���Ԏ擾
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_TIMEOUT_SEC, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_TIMEOUT_SEC ) ;
		return ( RTN_NG ) ;
	}
	pAppEnv->timeout_Sec= atol ( lc_prmBuf ) ;
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_TIMEOUT_USEC, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_TIMEOUT_USEC ) ;
		return ( RTN_NG ) ;
	}
	pAppEnv->timeout_uSec= atol ( lc_prmBuf ) ;

	//	�I�[�_�[�f�[�^
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_DIR_IA_DAT, pAppEnv->cDirIA_Dat ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_IA_DAT ) ;
		return ( RTN_NG ) ;
	}
	//	�쐬�����f�[�^
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_DIR_IA_IDX, pAppEnv->cDirIA_Idx ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_IA_IDX ) ;
		return ( RTN_NG ) ;
	}

	//	�h�`�T�[�o�f�B���N�g��
	bufPrmIA = 0 ;
	li_retSts= ZbmlPrmGetValList ( bp, MYAPP_PRM_IA_SERVER_DIR, &cntPrmIA, &bufPrmIA )  ;
	if ( li_retSts != 0 || cntPrmIA == 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetValList", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_IA_SERVER_DIR ) ;
		return ( RTN_NG ) ;
	}
	pAppEnv->CntInfoIA = cntPrmIA ;
	pAppEnv->infoIA = ( struct my_infoIA * ) malloc ( sizeof ( struct my_infoIA ) * cntPrmIA ) ;	
	if ( pAppEnv->infoIA == NULL ) {
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "malloc", __LINE__,
			 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 "�������A���P�[�V�������s[%d:%s]", errno, strerror ( errno ) ) ;
		return ( RTN_NG ) ;
	}
	for ( idx = 0 ; idx < cntPrmIA ; idx ++ ) {
		bufToken = strtok ( bufPrmIA[idx], "\t" ) ;
		if ( bufToken == NULL ) {
			gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetValList", __LINE__,
					 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 		"�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_IA_SERVER_DIR ) ;
			return ( RTN_NG ) ;
		}
		strcpy ( pAppEnv->infoIA[idx].smpNo, bufToken ) ; 
		bufToken = strtok ( NULL, "\t" ) ;
		if ( bufToken == NULL ) {
			gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetValList", __LINE__,
					 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 		"�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_IA_SERVER_DIR ) ;
			return ( RTN_NG ) ;
		}
		strcpy ( pAppEnv->infoIA[idx].dirIA_DAT, bufToken ) ; 
		bufToken = strtok ( NULL, "\t" ) ;
		if ( bufToken == NULL ) {
			gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetValList", __LINE__,
					 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 		"�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_IA_SERVER_DIR ) ;
			return ( RTN_NG ) ;
		}
		strcpy ( pAppEnv->infoIA[idx].dirIA_IDX, bufToken ) ; 
		free ( bufPrmIA[idx] ) ;
	}
	free ( bufPrmIA ) ;

	//	�p�����[�^�t�@�C���N���[�Y	
	ZbmlPrmClose ( bp ) ;

	/***
	 ***	���L����������	
	 ***/
	if ( sFncShmCrt ( pAppEnv ) != RTN_OK ) {
		return ( RTN_NG ) ;
	}

	/***
	 ***	�f�[�^�x�[�X�I�[�v��
	 ***/
	ll_retSts = ZdbConnect( pAppEnv->cDb_Name, 
							pAppEnv->cDb_User, pAppEnv->cDb_Passwd ) ;
	if ( ll_retSts != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_DB ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZdbConnect", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�f�[�^�x�[�X�I�[�v���Ɏ��s���܂���[DB=%s USER=%s PASS=%s]", pAppEnv->cDb_Name, pAppEnv->cDb_User, pAppEnv->cDb_Passwd ) ;
		return ( RTN_NG ) ;
	}

	return ( RTN_OK ) ; 
}

/******************************************************************************/
/*  �� �� ���@�FmainFunction()												  */
/*  �@�\�T�v�@�F���C�������֐�												  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct	appEnv *   	�v���O�������\����		 			  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F  0     : ����												  */
/* �@�@�@�@�@�@�@-1     : ���s												  */
/*  ���A���@�F RTN_OK		: ����											  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
int
mainFunction( pAppEnv )
struct appEnv	*pAppEnv ;
{

	//	�\�P�b�g�֘A
	struct hostent			*sHostent ;
	struct sockaddr_in		 sSockaddr ;
	struct sockaddr_in		 cCladdr ;
	socklen_t				 iCladdrLen ;
	int						 fh ;
	int						 cfh ;
	char					 cHostname[256+1] ;
	int						 on ;
	//	�\�P�b�g�Ď�
	fd_set				 	 iMask ;
	fd_set				 	 iRead ;
	int					 	 iWatch ;
	struct timeval			 stTimeval ;
	int						 retval ;
	//	���̑�
	int						 li_stopFlg ;
	int						 iRetSts ;
char	trcBuff[4] ;

	/***
	 ***	�ʐM��������
	 ***/
loging ( "mainFunction : �ʐM��������\n" ) ;
	//	�\�P�b�g�쐬
	fh = socket ( PF_INET, SOCK_STREAM, 0 ) ;
	if ( fh < 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SOCKET ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "socket", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�\�P�b�g�̍쐬�Ɏ��s���܂���[error=%d]", errno ) ;
		return ( RTN_NG ) ;
	}

	//	�A�h���X�����ė��p
	on = 1; 
	setsockopt( fh, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );

	//	�z�X�g���擾	
	gethostname ( cHostname, sizeof ( cHostname ) ) ;

	//	IP�A�h���X�擾
	sHostent = gethostbyname ( cHostname ) ;
	if ( sHostent == NULL ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SOCKET ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "socket", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�h�o�A�h���X�̎擾�Ɏ��s���܂���[hostneme=%s error=%d]", cHostname, errno ) ;
		return ( RTN_NG ) ;
	}

	//	���z�X�g���Z�b�g
	memset ( &sSockaddr, '\0', sizeof ( sSockaddr ) ) ;
	sSockaddr.sin_family = PF_INET ;
	sSockaddr.sin_port	 = htons(pAppEnv->Port); ;
	memcpy ( &( sSockaddr.sin_addr ), sHostent->h_addr, sHostent->h_length ) ;
loging ( "    HostName : [%s]\n", cHostname ) ;
loging ( "    Port     : [%d]\n", pAppEnv->Port ) ;
loging ( "    IP       : [%u.%u.%u.%u]\n", *(sHostent->h_addr),
										  *(sHostent->h_addr+1),
										  *(sHostent->h_addr+2),
										  *(sHostent->h_addr+3)) ;

	//	�\�P�b�g�o�C���h
	iRetSts =  bind ( fh, ( struct sockaddr * )&sSockaddr, sizeof ( sSockaddr ) ) ;
	if ( iRetSts == -1 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SOCKET ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "bind", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�o�C���h�Ɏ��s���܂���[error=%d]", errno ) ;
		return ( RTN_NG ) ;
	}
//loging ( "    �\�P�b�g�o�C���h : [bind]\n") ;
	
	// �o�b�t�@�m��
	iRetSts = listen ( fh, 10 ) ;
	if ( iRetSts == -1 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SOCKET ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "listen", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�o�b�t�@�̊m�ۂɎ��s���܂���[error=%d]", errno ) ;
		return ( RTN_NG ) ;
	}
//loging ( "    �o�b�t�@�m�� : [listen]\n") ;

	//	�Ď��\�P�b�g�ݒ�
	FD_ZERO ( &iMask ) ;
	FD_SET ( fh, &iMask ) ;
	iWatch = fh + 1 ;

	/***
	 ***	��M���C������
	 ***/
//loging ( "    ###### ��M���C������ ######\n") ;
	while ( 1 ) {
		//	�ڑ��҂�
//loging ( "    �ڑ��҂�\n") ;
		iRead = iMask;
		stTimeval.tv_sec  = pAppEnv->timeout_Sec ;
		stTimeval.tv_usec = pAppEnv->timeout_uSec ;
		retval = select ( iWatch, &iRead, NULL, NULL, &stTimeval ) ;
		if ( retval == -1 ) {
			if ( errno == SIGILL ) {
				continue ;
			}
			//	�ُ�I��	LOG
			gintErrorCode = MYAPP_STSCODE_ERR_SOCKET ;
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "select", __LINE__,
					 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 	 "�\�P�b�g�Ď��Ŏ��s���܂���[error=%d]", errno ) ;
			return ( RTN_NG ) ;
		} else if ( retval ) {
			//	�N���C�A���g�ڑ�
			if ( FD_ISSET ( fh, &iRead ) ) {
				iCladdrLen = sizeof ( cCladdr ) ;
				cfh = accept ( fh, ( struct sockaddr * )&cCladdr, &iCladdrLen ) ;
				if ( cfh == -1 ) {
					//	�ُ�I��	LOG
					gintErrorCode = MYAPP_STSCODE_ERR_SOCKET ;
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "accept", __LINE__,
							 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 			 "�N���C�A���g�ڑ��Ŏ��s���܂���[error=%d]", errno ) ;
					return ( RTN_NG ) ;
				}
loging ( "    !!!! �N���C�A���g�ڑ� !!!!\n") ;
memcpy ( trcBuff, &cCladdr.sin_addr, sizeof ( trcBuff ) ) ;
loging ( "    IP       : [%u.%u.%u.%u]\n", trcBuff[0],
										   trcBuff[1],
										   trcBuff[2],
										   trcBuff[3] ) ;
				//	�h�`�T�[�o�]������	
				iRetSts = sFncRcevMain ( pAppEnv, cfh ) ;
				if ( iRetSts == RTN_NG ) {
					return ( -1 ) ;
				} else if ( iRetSts == RTN_SKIP ) {
					close ( cfh ) ;
				} else if ( iRetSts == 2 ) {
					//	��~
					close ( fh ) ;
					close ( cfh ) ;
					break ;
				}
			}
		}

		/***
		 *** ��~�R�}���h�m�F
		 ***/
		sFncShmGet ( pAppEnv, &li_stopFlg ) ;
		if ( li_stopFlg == 1 ) {
			close ( fh ) ;
			break ;
		}
	}

	return ( RTN_OK ) ;
}

/******************************************************************************/
/*  �� �� ���@�FendFunction()												  */
/*  �@�\�T�v�@�F�I�������֐�												  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct	appEnv *   	�v���O�������\����		 			  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F����			 											  */
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
/*  �� �� ���@�FsFncRcevMain()	    										  */
/*  �@�\�T�v�@�F��M���C������												  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct	appEnv *   	�v���O�������\����		 			  */
/*�@ ��Q���� �Fint					�\�P�b�g�n���h��						  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F RTN_OK		: ����											  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/* �@�@�@�@�@�@�@2		    : �I���i��~�R�}���h���s�j						  */
/******************************************************************************/
static int
sFncRcevMain ( pAppEnv, pcfh )
struct appEnv	*pAppEnv ;
int				 pcfh ;
{
	int				  	 li_retSts ;

	fd_set				 iMask ;
	fd_set				 iRead ;
	int					 iWatch ;

	int					 iReadsize ;
	char				 cChar ;
	char				 cRcvBuf[MYAPP_RCV_SIZE+1] ;
	int				 	 iidx ;

	char				 cSmpno[8+1] ;
	char				 cRckno[MYAPP_RCKNO_SIZE] ;
	char				*pToken ;

	int					 li_stopFlg ;
	int					 retval ;
	struct timeval		 stTimeval ;

	/***
	 ***	������
	 ***/
	//	�Ď��\�P�b�g�ݒ�
	FD_ZERO ( &iMask ) ;
	FD_SET ( pcfh, &iMask ) ;
	iWatch = pcfh + 1 ;
	//	��M�o�b�t�@������
	memset ( cRcvBuf, '\0', sizeof ( cRcvBuf ) ) ;
	iidx = 0 ;

	/***
	 ***	��M����
	 ***/
	while ( 1 )  {
		//	��M�ҋ@
		iRead = iMask;
		stTimeval.tv_sec  = pAppEnv->timeout_Sec ;
		stTimeval.tv_usec = pAppEnv->timeout_uSec ;
		retval = select ( iWatch, &iRead, NULL, NULL, &stTimeval ) ;
		if ( retval == -1 ) {
			if ( errno == SIGILL ) {
				continue ;
			}
			//	�ُ�I��	LOG
			gintErrorCode = MYAPP_STSCODE_ERR_SOCKET ;
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "select", __LINE__,
					 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 	 "�\�P�b�g�Ď��Ŏ��s���܂���[error=%d]", errno ) ;
			return ( RTN_SKIP ) ;
		} else if ( retval ) {
			//	��M
			if ( FD_ISSET ( pcfh, &iRead ) ) {
				iReadsize = read ( pcfh, &cChar, sizeof ( cChar ) ) ;
				if ( iReadsize < 0 ) {
					//	�ُ�I��	LOG
					gintErrorCode = MYAPP_STSCODE_ERR_SOCKET ;
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "read", __LINE__,
							 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 			 "��M�Ɏ��s���܂���[error=%d]", errno ) ;
					return ( RTN_SKIP ) ;
				} else if ( iReadsize == 0 ) {
					//	�ُ�I��	LOG
					gintErrorCode = MYAPP_STSCODE_ERR_SOCKET ;
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "read", __LINE__,
							 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 			 "�N���C�A���g�Ɛڑ����؂�܂���[error=%d]", errno ) ;
					return ( RTN_SKIP ) ;
				}
loging ( "    ��M: [%d][%c][%x][%d]\n", iidx, cChar, cChar, iReadsize ) ;
				//	��M�f�[�^�T�C�Y�`�F�b�N
				if ( iidx >= MYAPP_RCV_SIZE ) {
loging ( "    ��M: ��M�f�[�^�T�C�Y�I�[�o�[�t���[\n"  ) ;
					//	�ُ�I��	LOG
					gintErrorCode = MYAPP_STSCODE_ERR_DATA ;
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "read", __LINE__,
							 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 			 "��M�f�[�^�T�C�Y�I�[�o�[�t���[" ) ;
					memset ( cRcvBuf, '\0', sizeof ( cRcvBuf ) ) ;
					iidx = 0 ;
					continue ;
				}
				//	��M�o�b�t�@�i�[
				if (  cChar != 0x0a  &&  cChar != 0x0d ) {
					cRcvBuf[iidx] = cChar ;	
					iidx ++ ;
				}
				//	�f�[�^�I�[
				if ( cChar == 0x0a ) {
	 				//	��M�f�[�^�W�J
loging ( "    ��������M�f�[�^������\n") ;
loging ( "    �t�@�C���n���h�� : [%d]\n", pcfh ) ;
loging ( "    ��M�f�[�^       : [%s]\n", cRcvBuf ) ;
					sFncPutLog ( TRCKIND_TRACE, __FILE__, "read", __LINE__,
							 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 			 "��M�d��[%s]", cRcvBuf ) ;
					memset ( cSmpno,  '\0', sizeof ( cSmpno ) ) ;
					memset ( cRckno,  '\0', sizeof ( cRckno ) ) ;
					pToken =  sFncToken ( cRcvBuf ) ;
					if ( pToken != NULL ) {
						memcpy ( cSmpno, pToken, sizeof ( cSmpno )-1 ) ;
					}
					pToken =  sFncToken ( NULL ) ;
					if ( pToken != NULL ) {
						memcpy ( cRckno, pToken, sizeof ( cRckno )-1 ) ;
					}
loging ( "    �T���v�����@     : [%s]\n", cSmpno ) ;
loging ( "    ���b�N�m�n       : [%s]\n", cRckno ) ;

					//	�R�s�[����
//my_loging ( "STR : %s\n", cRckno ) ;
					li_retSts = sFncOederFileMove ( pAppEnv, cSmpno, cRckno ) ;
					if ( li_retSts < 0 ) {
						//return ( RTN_SKIP ) ;
						//return ( RTN_NG ) ;
					}
//my_loging ( "END : %s\n", cRckno ) ;
					memset ( cRcvBuf, '\0', sizeof ( cRcvBuf ) ) ;
					iidx = 0  ;
				}
			} 
		} 

		//	��~�R�}���h�m�F
		sFncShmGet ( pAppEnv, &li_stopFlg ) ;
		if ( li_stopFlg == 1 ) {
			return ( 2 ) ;
		}
	}

	return ( RTN_OK ) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncOederFileMove()	 										  */
/*  �@�\�T�v�@�F�I�[�_�[�t�@�C���ړ�����					  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct	appEnv *   	�v���O�������\����		 			  */
/*�@ ��Q���� �Fchar *   			�T���v���m�n					 	      */
/*�@ ��R���� �Fchar *   			���b�N�m�n						 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F RTN_OK		: ����											  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
static	int
sFncOederFileMove ( pAppEnv, pSmpno, pRckno )
struct appEnv	*pAppEnv ;
char			*pSmpno ;
char			*pRckno ;
{

	int				  li_retSts ;

	struct dirent	**ldirBuf ;
	long			  lfileCnt ;
	long			  idx ;
	char			 *dirIA_DAT ;
	char			 *dirIA_IDX ;
	char			  rlFileName[MYAPP_PATH_SIZE] ;

	FILE			 *fp ;
	char			  koFileName[MYAPP_PATH_SIZE] ;
	char	  		  recBuf[512] ;
	char			  knskisymd[10+1] ;
	char			 *pToken ;

	char			  idxFileName[MYAPP_PATH_SIZE] ;
	/***
	 ***	�����ݒ�
	 ***/
	//	�R�[���o�b�N�֐����Q�ƒl�ݒ�
	// NEW sprintf ( gMatchOrder, "%s_%s", MYAPP_SEND_KIND_OD, pRckno ) ;
	memset ( gMatchOrder, '\0', sizeof ( gMatchOrder )  ) ;
	memset ( gMatchOrder, '_', sizeof ( gMatchOrder ) - 1 ) ;
	memcpy ( gMatchOrder, pRckno, strlen ( pRckno )  ) ;
	strcpy ( gDirIA_Idx, pAppEnv->cDirIA_Idx ) ;
	//	�ړ���f�B���N�g���擾
	dirIA_DAT = NULL ;
	dirIA_IDX = NULL ;
	for ( idx = 0 ; idx < pAppEnv->CntInfoIA ; idx ++ ) {
		if ( strcmp ( pSmpno, pAppEnv->infoIA[idx].smpNo ) == 0 ) {
			dirIA_DAT = pAppEnv->infoIA[idx].dirIA_DAT ;
			dirIA_IDX = pAppEnv->infoIA[idx].dirIA_IDX ;
			break ;
		}
	}

	if ( dirIA_DAT == NULL || dirIA_IDX == NULL ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOederFileMove", __LINE__,
			 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 "�h�`�T�[�o�̃f�B���N�g�������݂��܂���[SNO=%s RNO=%s]", pSmpno, pRckno ) ;
		return ( RTN_NG ) ;
	}

	/***
	 ***	�t�@�C�����݃`�F�b�N
	 ***/
//    sFncPutLog ( TRCKIND_DEBUG, __FILE__, "read", __LINE__,
//        EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//        "�T��DIRECTORY[%s]", gDirIA_Idx ) ;	
	if ( ( lfileCnt = scandir ( pAppEnv->cDirIA_Idx, &ldirBuf,
								(void*)sFncFileFillter, alphasort ) ) < 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_DIR;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "scandir", __LINE__,
			 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 "�����I�[�_�[�t�@�C�����̎擾�Ɏ��s���܂���[SNO=%s RNO=%s]", pSmpno, pRckno ) ;
		return ( RTN_NG ) ;
	}
	if ( lfileCnt == 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncOederFileMove", __LINE__,
			 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 "�����I�[�_���t�@�C�������݂��܂���[SNO=%s RNO=%s]", pSmpno, pRckno ) ;
		return ( RTN_NG ) ;
	}

	/***
	 ***	�����J�n���擾
	 ***		�����I�[�_���t�@�C���̍ŏ��̂P������擾
	 ***/
	sprintf ( koFileName, "%s/%s", pAppEnv->cDirIA_Dat, ldirBuf[0]->d_name ) ;
	//	�t�@�C���I�[�v��
	fp = fopen ( koFileName, "r" ) ;
	if ( fp == NULL ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "fopen", __LINE__,
			 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 "�t�@�C���̃I�[�v���Ɏ��s���܂���[%s]", koFileName ) ;
		return ( RTN_NG ) ;
	}
//    sFncPutLog ( TRCKIND_DEBUG, __FILE__, "read", __LINE__,
//        EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//        "�t�@�C���I�[�v������" ) ;

	//	�ǂݍ���
	if ( fgets ( recBuf, sizeof ( recBuf ), fp ) == NULL ) {
		fclose ( fp ) ;
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_FILE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "fgets", __LINE__,
			 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���[%s]", koFileName ) ;
		return ( RTN_NG ) ;
	}

	//	�N���[�Y
	fclose ( fp ) ;

	//	�����J�n���擾	
	pToken = strtok ( recBuf, "," ) ;
	if ( pToken == NULL ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "fgets", __LINE__,
			 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 	 	 "�����J�n�����̎擾�Ɏ��s���܂���[SNO=%s RNO=%s]", pSmpno, pRckno ) ;
		return ( RTN_NG ) ;
	}
	strcpy ( knskisymd, pToken ) ;
	sFncTrim ( knskisymd ) ;

	/***
	 ***	�t�@�C���ړ�
	 ***/

//    sFncPutLog ( TRCKIND_DEBUG, __FILE__, "read", __LINE__,
//        EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//        "�t�@�C���ړ�" ) ;
	for ( idx = 0 ; idx < lfileCnt ; idx ++ ) {
		//	�����I�[�_�[���t�@�C��
		if ( sFncFileRename ( pAppEnv->cDirIA_Dat, ldirBuf[idx]->d_name,
							  dirIA_DAT, ldirBuf[idx]->d_name ) != RTN_OK ) {
			return ( RTN_NG ) ;
		}
		//	�����`�F�b�N���t�@�C��
		sprintf ( rlFileName, "%s%s", MYAPP_SEND_KIND_CH, 
									  &(ldirBuf[idx]->d_name[2]) ) ;
		if ( sFncFileRename ( pAppEnv->cDirIA_Dat, rlFileName,
							  dirIA_DAT, rlFileName ) != RTN_OK  ) {
			return ( RTN_NG ) ;
		}
		//	�ړ������t�@�C��
		if ( sFncFileRename ( pAppEnv->cDirIA_Idx, ldirBuf[idx]->d_name,
							  dirIA_IDX, ldirBuf[idx]->d_name ) != RTN_OK ) {
			return ( RTN_NG ) ;
		}
		//sprintf ( idxFileName, "%s/%s", pAppEnv->cDirIA_Idx, ldirBuf[idx]->d_name ) ;
		//unlink ( idxFileName ) ;
	}

	/***
	 ***	���̃|�W�V�����Ǘ��ǉ�
	 ***/
//	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "read", __LINE__,
//        EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//        "���̃|�W�V�����Ǘ��ǉ�" ) ;
	li_retSts = sFncInsKENPOS ( knskisymd, pRckno, pSmpno ) ;
	//20070105 YOON
    if ( li_retSts == MYAPP_SQL_DEADLOCK || li_retSts == MYAPP_SQL_DUPLICATION)
    {   //�f�b�h���b�Nor�d��
       	ZdbRollback () ;
		return ( RTN_OK ) ;
		 
    }
	else if ( li_retSts < 0 ) {
		//	���[���o�b�N
		ZdbRollback () ;
		return ( RTN_NG ) ;
	}

	//	�R�~�b�g
	ZdbCommit () ;
	return ( RTN_OK ) ;

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
/*  ���A���@�F RTN_OK		: ����											  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
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
	char	lc_command[1024] ;

	sprintf ( lc_fromPath, "%s/%s", pc_fromDir, pc_fromFileName ) ;
	sprintf ( lc_toPath,   "%s/%s", pc_toDir,   pc_toFileName ) ;
	sprintf ( lc_command, "%s %s %s", MYAPP_COMMAND_CP, lc_fromPath, lc_toPath ) ;

	if ( system ( lc_command ) == -1 ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "rename", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "�t�@�C���̃R�s�[�Ɏ��s���܂���[%s->%s]", lc_fromPath, lc_toPath ) ;
        return ( RTN_NG ) ;
    }

    /***  NFS Mount
	if ( rename ( lc_fromPath, lc_toPath ) < 0 ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "rename", __LINE__,
 	 	 			 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
 	 	 			 "�t�@�C���̈ړ��Ɏ��s���܂���[%s->%s]", lc_fromPath, lc_toPath ) ;
		return ( RTN_NG ) ;
	}
	***/
	
	return ( RTN_OK ) ;
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

	int			 li_len ;

	//printf("yoon d_name:%s,gMatchOrder:%s\n",pdirEnt->d_name,gMatchOrder);
/*DELL 20070120
//  sFncPutLog ( TRCKIND_DEBUG, __FILE__, "read", __LINE__,
//      EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//      "�f�B���N�g���`�F�b�N d_name:%s,gMatchOrder:%s",
//		pdirEnt->d_name,gMatchOrder);
*/
	
	//�f�B���N�g���`�F�b�N
	if ( strcmp ( pdirEnt->d_name, "." ) == 0 ||
		 strcmp ( pdirEnt->d_name, ".." ) == 0 ) {
		return ( 0 ) ;
	}

	//�����񒷃`�F�b�N
	li_len = strlen ( pdirEnt->d_name )  ;
	if ( li_len  != MYAPP_OD_FILE_LEN ) {
		return ( 0 ) ;
	}

	//	���b�N�m�n�`�F�b�N
	if ( memcmp ( &(pdirEnt->d_name[3]), gMatchOrder, sizeof  ( char ) * 10) != 0 ) {
/* OLD
	if ( memcmp ( &(pdirEnt->d_name[16]), gMatchOrder, sizeof ( char ) * 10 ) != 0 ) {
*/
		return ( 0 ) ;
	}


	//�g���q�`�F�b�N
	if ( memcmp ( &(pdirEnt->d_name[li_len-strlen(MYAPP_SEND_SFX)]), 
				  MYAPP_SEND_SFX, 
				  strlen ( MYAPP_SEND_SFX ) ) != 0 ) {
		return ( 0 ) ;
	}


	return ( 1 ) ;
}
/******************************************************************************/
/*  �� �� ���@�FsFncSyslog()				 								  */
/*  �@�\�T�v�@�F�V�X�e�����O�o��							  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fint 			   	�v���C�I���e�B�[						  */
/*�@ ��Q���� �Fchar *   			�֐���									  */
/*�@ ��R���� �Fchar * 		  		���b�Z�[�W								  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F����														  */
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
/*  �� �� ���@�FsFncToken()			 										  */
/*  �@�\�T�v�@�F�g�[�N������								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *   	������									 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fchar *														  */
/*					 NULL	�I�[											  */
/*					 NULL�ȊO	������										  */
/******************************************************************************/
static	char*
sFncToken ( pString )
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
/*  �� �� ���@�FsFncShmCrt()				 								  */
/*  �@�\�T�v�@�F���L����������								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����			 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F RTN_OK		: ����											  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
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
		return ( RTN_NG ) ;
	}

	//	�A�^�b�`	
	shmData = ( int * ) shmat ( pAppEnv->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmat", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "���L�������̑���Ɏ��s���܂���" ) ;
		return ( RTN_NG ) ;
	}
loging ( "stocker : ���L������[CRT] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n", pAppEnv->shm_Key, pAppEnv->shm_Id, *shmData, shmData ) ;

	//	�l�ݒ�	
	*shmData = 0 ;

	//	�f�^�b�`	
	if ( shmdt ( shmData ) == -1 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "���L�������̑���Ɏ��s���܂���" ) ;
		return ( RTN_NG ) ;
	}
	return ( RTN_OK ) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncShmGet()				 								  */
/*  �@�\�T�v�@�F���L�������擾								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����		 		      */
/*�@ ��Q���� �Fint *   			�l							 		      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F RTN_OK		: ����											  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
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
		return ( RTN_NG ) ;
	}

	//	�l�ݒ�	
	*pshmData = *shmData ;

loging ( "stocker : ���L������[GET] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n", pAppEnv->shm_Key, pAppEnv->shm_Id, *shmData, shmData ) ;
	//	�f�^�b�`	
	if ( shmdt ( shmData ) == -1 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "���L�������̑���Ɏ��s���܂���" ) ;
		return ( RTN_NG ) ;
	}
	return ( RTN_OK ) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncShmDel()				 								  */
/*  �@�\�T�v�@�F���L�������폜								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\���́B		 		      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F RTN_OK		: ����											  */
/* �@�@�@�@�@�@�@RTN_NG		: ���s											  */
/******************************************************************************/
static int
sFncShmDel ( pAppEnv )
struct appEnv	*pAppEnv ;
{
	int		*shmData ;

loging ( "stocker : ���L������[DEL] shmKey[%d]-ID[%d]\n", pAppEnv->shm_Key, pAppEnv->shm_Id) ;
	//	�폜	
	if ( shmctl ( pAppEnv->shm_Id, IPC_RMID, NULL) < 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		//sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmctl", __LINE__,
		//		 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		//		 	 "���L�������̑���Ɏ��s���܂���" ) ;
		return ( RTN_NG ) ;
	}
	return ( RTN_OK ) ;
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
	int		i ;
#if defined ( _TRACE )
	loging ( "########## SMPR - _sFncEnvDip ##########\n" ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_IA_DAT,     pAppEnv->cDirIA_Dat ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_IA_IDX,     pAppEnv->cDirIA_Idx ) ;
	for ( i = 0 ; i < pAppEnv->CntInfoIA ; i ++ ) {
		loging ( "\t%s : [%s][%s][%s]\n", MYAPP_PRM_IA_SERVER_DIR,  
									      pAppEnv->infoIA[i].smpNo,
									      pAppEnv->infoIA[i].dirIA_DAT,
									      pAppEnv->infoIA[i].dirIA_IDX ) ;
	}
	loging ( "\t�y���L�������\���z\n" ) ;
	loging ( "\t%s : [%d]\n", MYAPP_PRM_SHM_KEY,		pAppEnv->shm_Key ) ;
	loging ( "\t�y�ʐM�\���z\n" ) ;
	loging ( "\t%s : [%d]\n", MYAPP_PRM_PORT,			pAppEnv->Port ) ;
	loging ( "\t%s : [%ld]\n", MYAPP_PRM_TIMEOUT_SEC,	pAppEnv->timeout_Sec ) ;
	loging ( "\t%s : [%ld]\n", MYAPP_PRM_TIMEOUT_USEC,	pAppEnv->timeout_uSec) ;
	loging ( "\t�y�c�a�֘A�\���z\n" ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DB_NAME,        pAppEnv->cDb_Name ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DB_USER,        pAppEnv->cDb_User ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DB_PASSWD,      pAppEnv->cDb_Passwd ) ;
	loging ( "########## Stocker - _sFncEnvDip ##########\n" ) ;
#endif
}
/******************************************************************************/
/*  �� �� ���@�Fmain()														  */
/*  �@�\�T�v�@�F���������֐�												  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct	env *   	�v���O�������\���́B		 			  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F  0     : ����												  */
/* �@�@�@�@�@�@�@-1     : ���s												  */
/******************************************************************************/
int
main ( argc, argv )
int		 argc ;
char	*argv[] ;
{
	struct appEnv		sAppEnv ;

    /***
     ***    �o�b�N�O���E���h���s
     ***/
	if ( daemon ( 0, 1 ) < 0 ) {
		exit ( 9 ) ;
	}

	/***
	 ***	��������
	 ***/
	if ( initFunction ( argc, argv, &sAppEnv )  != 0 ) {
		fprintf ( stderr,"%s : Error initFunction [%d]\n", MYAPP_APP_NAME, gintErrorCode ) ;
		exit ( 9 ) ;
	}
_sFncEnvDip ( &sAppEnv ) ;

	/***
	 ***	���C������	
	 ***/
	if ( mainFunction ( &sAppEnv )  != 0 ) {
		fprintf ( stderr,"%s : Error mainFunction [%d]\n", MYAPP_APP_NAME, gintErrorCode ) ;
		endFunction ( &sAppEnv ) ;
		exit ( 9 ) ;
	}

	/***
	 ***	�I������
	 ***/
	endFunction ( &sAppEnv ) ;

	exit ( 0 ) ;
}
