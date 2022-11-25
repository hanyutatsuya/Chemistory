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

#include "bmlprm.h"
#include "ZD999IA.h"

/******************************************************************************/
/* Define�錾       	                                                      */
/******************************************************************************/

/******************************************************************************/
/* �\���̐錾       	                                                      */
/******************************************************************************/

/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/

/******************************************************************************/
/* �֐��錾 		                                                          */
/******************************************************************************/
//	��M�����֘A	
static	int		sFncRcevMain ( struct appEnv *, int ) ;
void sFncCOMMAND_EXEC_LABO ( int, struct dataRec * ) ;
void sFncCOMMAND_EXEC_LABO_NYOU ( int, struct dataRec * ) ;
void sFncCOMMAND_EXEC_BM ( int, struct dataRec * ) ;
void sFncCOMMAND_KILL ( int, struct dataRec * ) ;
void sFncCOMMAND_PS ( int ) ;
void sFncCOMMAND_BACK ( ) ;

//  �q�v���Z�X����
static int  sFncChild ( int ) ;

//  �q�v���Z�X����
static void sFncWait ( int ) ;


/******************************************************************************/
/*  �� �� ���@�FinitFunction()												  */
/*  �@�\�T�v�@�F���������֐�												  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fint   				���C���p�����[�^��			 			  */
/*�@ ��Q���� �Fchar *   			���C���p�����[�^			 			  */
/*  �o�@�@�́@�F                                                              */
/*�@ ��R���� �Fstruct	appEnv *   	�v���O�������\����		 			  */
/*  ���A���@�F 0		: ����											  */
/* �@�@�@�@�@�@�@-1		: ���s											  */
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

	/***
	 ***    �����`�F�b�N
	 ***/
	if ( argc != 2 ) {
		fprintf ( stderr, "%s : There is an error in a command parameter\n", MYAPP_APP_NAME ) ;
		return ( -1 ) ;
	}

	/***
	 ***	������	
	 ***/
	memset ( pAppEnv , '\0', sizeof ( struct appEnv ) ) ;

	/***
	 ***	�p�����[�^�t�@�C�����ޔ�
	 ***/
	//	�p�����[�^�t�@�C���I�[�v��	
	bp = ZbmlPrmOpen ( argv[1] ) ;		
	if ( bp == NULL ) {
		return ( -1 ) ;
	}
	//	�|�[�g	
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_PORT, lc_prmBuf ) != 0 ) {
		return ( -1 ) ;
	}
	pAppEnv->Port = atoi ( lc_prmBuf ) ;
	//	�^�C���A�E�g���Ԏ擾
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_TIMEOUT_SEC, lc_prmBuf ) != 0 ) {
		return ( -1 ) ;
	}
	pAppEnv->timeout_Sec= atol ( lc_prmBuf ) ;
	if ( ZbmlPrmGetVal ( bp, MYAPP_PRM_TIMEOUT_USEC, lc_prmBuf ) != 0 ) {
		return ( -1 ) ;
	}
	pAppEnv->timeout_uSec= atol ( lc_prmBuf ) ;

	//	�p�����[�^�t�@�C���N���[�Y	
	ZbmlPrmClose ( bp ) ;

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
/*  ���A���@�F 0		: ����											  */
/* �@�@�@�@�@�@�@-1		: ���s											  */
/******************************************************************************/
int
mainFunction( pAppEnv )
struct appEnv	*pAppEnv ;
{
    struct hostent          *sHostent ;
    struct sockaddr_in       sSockaddr ;
    struct sockaddr_in       cCladdr ;
    socklen_t                iCladdrLen ;
    int                      fh ;
    int                      cfh ;
    fd_set                   iMask ;
    fd_set                   iRead ;
    int                      iWatch ;

    char                     cHostname[256+1] ;
    pid_t                    tPid ;

    struct timeval           stTimeval ;

    int                      retval ;
    int                      li_stopFlg ;
    int                      on ;

    /***
     ***    �ʐM��������
     ***/
    //  �\�P�b�g�쐬
    fh = socket ( PF_INET, SOCK_STREAM, 0 ) ;
    if ( fh < 0 ) {
        return ( -1 ) ;
    }

    //  �A�h���X�����ė��p
    on = 1;
    setsockopt( fh, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );

    //  �z�X�g���擾
    gethostname ( cHostname, sizeof ( cHostname ) ) ;

    //  IP�A�h���X�擾
    sHostent = gethostbyname ( cHostname ) ;
    if ( sHostent == NULL ) {
        return ( -1 ) ;
    }

    //  ���z�X�g���Z�b�g
    memset ( &sSockaddr, '\0', sizeof ( sSockaddr ) ) ;
    sSockaddr.sin_family = PF_INET ;
    sSockaddr.sin_port   = htons(pAppEnv->Port); ;
    memcpy ( &( sSockaddr.sin_addr ), sHostent->h_addr, sHostent->h_length ) ;

	printf ( "addr[%d]" , *(unsigned int *)sHostent->h_addr_list[0] );

    //  �\�P�b�g�o�C���h
    if ( bind ( fh, ( struct sockaddr * )&sSockaddr, sizeof ( sSockaddr ) ) == -1 ) {
        if ( errno == EADDRINUSE ) {
            fprintf ( stderr, "EADDRINUSE\n" ) ;
        }
        fprintf ( stderr, "errno[%d]\n", EADDRINUSE ) ;
        fprintf ( stderr, "errno[%d]\n", errno ) ;
        return ( -1 ) ;
    }

    // �o�b�t�@�m��
    if ( listen ( fh, 10) == -1 ) {
        return ( -1 ) ;
    }

    //  �q�v���Z�X�I���Ď�
    signal ( SIGCHLD, sFncWait ) ;

    //  �Ď��\�P�b�g�ݒ�
    FD_ZERO ( &iMask ) ;
    FD_SET ( fh, &iMask ) ;
    iWatch = fh + 1 ;

    /***
     ***    ��M���C������
     ***/
    while ( 1 ) {
        //  �ڑ��҂�
        iRead = iMask;
        stTimeval.tv_sec = 0 ;
        stTimeval.tv_usec = 100 ;
        retval = select ( iWatch, &iRead, NULL, NULL, &stTimeval ) ;
        if ( retval == -1 ) {
            if ( errno == SIGILL ) {
                continue ;
            }
            return ( -1 ) ;
        } else if ( retval ) {
            //  �N���C�A���g�ڑ�
            if ( FD_ISSET ( fh, &iRead ) ) {
                iCladdrLen = sizeof ( cCladdr ) ;
                cfh = accept ( fh, ( struct sockaddr * )&cCladdr, &iCladdrLen ) ;
                if ( cfh == -1 ) {
                    return ( -1 ) ;
                }
                //  �t�H�[�N
                tPid = fork() ;
                if ( tPid  == 0 ) {
                    //  ����
                    close ( fh ) ;
                    //  �q�v���Z�X
                    if ( sFncChild ( cfh ) < 0 ) {
                        close ( cfh ) ;
                        return ( -1 ) ;
                    } else {
                        close ( cfh ) ;
                        break ;
                    }
                } else if ( tPid == -1 ) {
                    break ;
                } else {
                    //  �e�v���Z�X
                    close ( cfh ) ;
                }
            }
        }
    }

	/**
        if ( sFncShmGet ( pAppEnv, &li_stopFlg ) < 0 ) {
            return ( -1 ) ;
        }
        if ( li_stopFlg == 1 ) {
            close ( fh ) ;
            sFncShmDel ( pAppEnv ) ;
        }
	**/
    return ( 0 ) ;


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
	return ;
}
/******************************************************************************/
/*  �� �� ���@�FsFncChild()                                                   */
/*  �@�\�T�v�@�F�q�v���Z�X����                                                */
/*              ���O���f�[�^�x�[�X�X�V                                      */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fint     �\�P�b�g�n���h��                                      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F  0     : ����                                                */
/* �@�@�@�@�@�@�@-1     : ���s                                                */
/******************************************************************************/
static int
sFncChild ( pcfh )
int      pcfh ;
{

    fd_set               iMask ;
    fd_set               iRead ;
    int                  iWatch ;

    int                  iReadsize ;

    struct dataRec	 stDataRec ;

    /***
     ***    ������
     ***/
    //  �Ď��\�P�b�g�ݒ�
    FD_ZERO ( &iMask ) ;
    FD_SET ( pcfh, &iMask ) ;
    iWatch = pcfh + 1 ;
    //  ��M�o�b�t�@������
    memset ( &stDataRec, '\0', sizeof ( stDataRec ) ) ;
    /***
     ***    ��M����
     ***/
    //  ��M�ҋ@
    iRead = iMask;
    if ( select ( iWatch, &iRead, NULL, NULL, NULL ) == -1 ) {
        return ( -1 ) ;
    }

    //  ��M
    if ( FD_ISSET ( pcfh, &iRead ) ) {
        iReadsize = read ( pcfh, &stDataRec, sizeof ( stDataRec ) ) ;
        if ( iReadsize <= 0 ) {
            return ( -1 ) ;
	}
    }

    /***
     ***	���M����
     ***/
fprintf ( stderr, "[%d]\n", stDataRec.command ) ;
    switch ( stDataRec.command ) {
	case COMMAND_PS :
	    sFncCOMMAND_PS( pcfh ) ;
	    break ;
	case COMMAND_EXEC_LABO :
	    close ( pcfh ) ;
	    sFncCOMMAND_EXEC_LABO( pcfh, &stDataRec ) ;
	    break ;
	case COMMAND_EXEC_LABO_NYOU :
	    close ( pcfh ) ;
	    sFncCOMMAND_EXEC_LABO_NYOU( pcfh, &stDataRec ) ;
	    break ;
	case COMMAND_EXEC_BM :
	    close ( pcfh ) ;
	    sFncCOMMAND_EXEC_BM( pcfh, &stDataRec ) ;
	    break ;
	case COMMAND_KILL :
	    close ( pcfh ) ;
	    sFncCOMMAND_KILL( pcfh, &stDataRec ) ;
	    break ;
	case COMMAND_KILL_DM :
	    close ( pcfh ) ;
	    return ( 9 ) ;
	case COMMAND_EXEC_BACK :
		sFncCOMMAND_BACK() ;
	default :
	    break ;
    }
    return ( 0 ) ;

}

void sFncCOMMAND_EXEC_LABO ( pcfh, pDataRec )
int			 pcfh ;
struct dataRec		*pDataRec ;
{
	struct dataRec	 stDataRec ;
	char		 iniFile[256] ;
	char		 cCommand[256] ;

	memset ( &stDataRec, '\0', sizeof ( stDataRec ) ) ;
	stDataRec.command = pDataRec->command ;
	stDataRec.sts = '0' ;

	strcpy ( iniFile, pDataRec->prmBuf ) ;
	sprintf ( cCommand, "%s %s", MYAPP_COM_EXEC_LABO, iniFile  ) ;
fprintf ( stderr, "#####[%s]\n" , cCommand ) ;
	if ( system( cCommand ) == -1 ) {
		stDataRec.sts = '9' ;
	}
	//write ( pcfh, &stDataRec, sizeof ( stDataRec ) ) ;
}
void sFncCOMMAND_EXEC_LABO_NYOU ( pcfh, pDataRec )
int			 pcfh ;
struct dataRec		*pDataRec ;
{
	struct dataRec	 stDataRec ;
	char		 iniFile[256] ;
	char		 cCommand[256] ;

	memset ( &stDataRec, '\0', sizeof ( stDataRec ) ) ;
	stDataRec.command = pDataRec->command ;
	stDataRec.sts = '0' ;

	strcpy ( iniFile, pDataRec->prmBuf ) ;
	sprintf ( cCommand, "%s %s", MYAPP_COM_EXEC_LABO_NYOU, iniFile  ) ;
fprintf ( stderr, "#####[%s]\n" , cCommand ) ;
	if ( system( cCommand ) == -1 ) {
		stDataRec.sts = '9' ;
	}
	//write ( pcfh, &stDataRec, sizeof ( stDataRec ) ) ;
}
void sFncCOMMAND_EXEC_BM ( pcfh, pDataRec )
int			 pcfh ;
struct dataRec		*pDataRec ;
{
	struct dataRec	 stDataRec ;
	char		 iniFile[256] ;
	char		 cCommand[256] ;

	memset ( &stDataRec, '\0', sizeof ( stDataRec ) ) ;
	stDataRec.command = pDataRec->command ;
	stDataRec.sts = '0' ;
	strcpy ( iniFile, pDataRec->prmBuf ) ;
	sprintf ( cCommand, "%s %s", MYAPP_COM_EXEC_BM, iniFile  ) ;
fprintf ( stderr, "#####[%s]\n" , cCommand ) ;
	if ( system( cCommand ) == -1 ) {
		stDataRec.sts = '9' ;
	}
	//write ( pcfh, &stDataRec, sizeof ( stDataRec ) ) ;
}
void sFncCOMMAND_KILL ( pcfh, pDataRec )
int			 pcfh ;
struct dataRec		*pDataRec ;
{
	struct dataRec	 stDataRec ;
	char		 shmKey[256] ;
	char		 cCommand[256] ;

	memset ( &stDataRec, '\0', sizeof ( stDataRec ) ) ;
	stDataRec.command = pDataRec->command ;
	stDataRec.sts = '0' ;

	strcpy ( shmKey, pDataRec->prmBuf ) ;
	sprintf ( cCommand, "%s %s", MYAPP_COM_KILL, shmKey ) ;
fprintf ( stderr, "#####[%s]\n" , cCommand ) ;
	if ( system( cCommand ) == -1 ) {
		stDataRec.sts = '9' ;
	}
	//write ( pcfh, &stDataRec, sizeof ( stDataRec ) ) ;
}
void sFncCOMMAND_PS ( pcfh )
int	pcfh ;
{
	FILE				*fp ;
	char	 			 cCommand[256] ;
	char				 cBuff[257] ;

	strcpy ( cCommand, "ps -ef" ) ;
	fp = popen ( cCommand , "r" ) ;
	if ( fp == NULL ) {
		return ;
	}
	while ( 1 ) {
		memset ( cBuff, '\0', sizeof ( cBuff ) ) ;
		if ( fread ( cBuff, sizeof ( cBuff ) -1, 1, fp )  <= 0 ) {
			break ;
		}
		write ( pcfh, cBuff, strlen ( cBuff ) ) ;
	}
	write ( pcfh, cBuff, strlen ( cBuff ) ) ;
	pclose ( fp ) ;
}
void sFncCOMMAND_BACK ( )
{
	system (MYAPP_COM_BACK) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncWait()                                                    */
/*  �@�\�T�v�@�F�q�v���Z�X�I���Ď�                                            */
/*  ���@�@�́@�F                                                              */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F����                                                          */
/******************************************************************************/
static void
sFncWait ( sig )
int      sig ;
{
    while ( waitpid ( -1, NULL,WNOHANG ) > 0 ) ;
    signal ( SIGCHLD, sFncWait ) ;
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
	if ( daemon ( 1, 1 ) < 0 ) {
		exit ( 9 ) ;
	}

	/***
	 ***	��������
	 ***/
	if ( initFunction ( argc, argv, &sAppEnv )  != 0 ) {
		fprintf ( stderr, "%s : Error initFunction \n", MYAPP_APP_NAME ) ;
		exit ( 9 ) ;
	}

	/***
	 ***	���C������	
	 ***/
	if ( mainFunction ( &sAppEnv )  != 0 ) {
		fprintf ( stderr, "%s : Error mainFunction \n", MYAPP_APP_NAME ) ;
		exit ( 9 ) ;
	}

	/***
	 ***	�I������
	 ***/
	endFunction ( &sAppEnv ) ;

	exit ( 0 ) ;
}
