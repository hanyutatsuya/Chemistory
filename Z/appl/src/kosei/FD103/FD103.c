/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����Fmain.c
 *     �@�\�T�v  �F�����Z�����菈��
 **********************************************************************/

/**********************************************************************/
/*  Ver.     Date           Name           History                    */
/* -------------------------------------------------------------------*/
/*  1.00     2007-04-05                    Create                     */
/* -------------------------------------------------------------------*/
/*  Ver.     Date           Name           History                    */
/* -------------------------------------------------------------------*/
/*  2.00     2008-10-09     K.Ameno        �����Z��                   */
/*  2.01     2009-03-04     R.Mizu         ���茋�ʂ�����������Ȃ����Ƃւ̑Ή� */
/**********************************************************************/

/********************************************************************/
/*  �C���N���[�h�錾                                                */
/********************************************************************/
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <time.h>
#include "bml_base.h"
#include "bmllog.h"
#include "FD103.h"

/* �I������t���O */
int     EndFlg = 0;

/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/
char        G_err[MYAPP_LEN_ERR+1];     /* LogMessage(errcode) */
char        G_msg[MYAPP_LEN_MSG+1];     /* LogMessage */

/*:KH-------------------------------------------------------------------------*/
/*:K  �֐���   : EnvRef                                                       */
/*----------------------------------------------------------------------------*/
/*:A  �@�\�T�v : �����ϐ���W�J����                                         */
/*----------------------------------------------------------------------------*/
/*:I  ����     : char    *src_cp  : �W�J�O������                              */
/*:O  �o��     : ����             : ����                                      */
/*:R  �߂�l   : char *           : �W�J�㕶����                              */
/*:C  ���L���� :                                                              */
/*----------------------------------------------------------------------------*/
char    *EnvRef( src_cp )
char        *src_cp;
{
	char	func_nm[MYAPP_LEN_FNCNM+1]; /* �֐����� */
static char value[256];                 /* �W�J�㕶���� */
    char    *dst_cp;                    /* �W�J�㕶���� */
    char    buf[256];                   /* �����ϐ� */
    char    *env_cp;                    /* �����ϐ� */

    strcpy( func_nm, "EnvRef" );
    LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

    dst_cp = value;
    while( *src_cp != 0 ) {
        if( *src_cp == '$' ) {
            env_cp = buf;
            *env_cp++ = *src_cp++;
            while( *src_cp != 0
                && *src_cp != ' ' && *src_cp != '\t'
                && *src_cp != '$' && *src_cp != '/' && *src_cp != '\\' ) {
                *env_cp++ = *src_cp++;
            }
            *env_cp = 0;
            if( (env_cp = getenv( &buf[1] )) == NULL ) {
                env_cp = buf;
            }
            while( *env_cp != 0 ) {
                *dst_cp++ = *env_cp++;
            }
        } else {
            *dst_cp++ = *src_cp++;
        }
    }
    *dst_cp = 0;

    LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
    return( value );
}

/*:KH-------------------------------------------------------------------------*/
/*:K  �֐���   : GetIniFile                                                   */
/*----------------------------------------------------------------------------*/
/*:A  �@�\�T�v : �ݒ�t�@�C������l���擾����                                 */
/*----------------------------------------------------------------------------*/
/*:I  ����     : char    *section : �Z�N�V������                              */
/*             : char    *key     : �L�[��                                    */
/*             : char    *profile : �ݒ�t�@�C����                            */
/*:O  �o��     : ����             : ����                                      */
/*:R  �߂�l   : char *           : �L�[�l�i������j                          */
/*:C  ���L���� :                                                              */
/*----------------------------------------------------------------------------*/
char    *GetIniFile( section, key, profile )
char        *section;
char        *key;
char        *profile;
{
char        func_nm[MYAPP_LEN_FNCNM+1];     /* �֐����� */
static char value[256];                     /* ���ϐ��l */
    FILE    *fp;                            /* FILE�|�C���^ */
    char    buf[256];                       /* �Ǎ��݃o�b�t�@ */
    int     sec_len;                        /* �Z�N�V�������� */
    int     key_len;                        /* �L�[���� */
    int     value_len;                      /* �L�[�l�� */
    int     i;                              /* �Y���� */

    strcpy( func_nm, "GetIniFile" );
    LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

    /*==========================*/
    /*  �ݒ�t�@�C���̃I�[�v��  */
    /*==========================*/

    if(( fp = fopen( EnvRef( profile ), "rt" )) == NULL ) {
    	LogOut( LT_END, LX_NON, LE_NON, "FOPEN ERROR", func_nm, __FILE__, __LINE__ );
        printf( "FOPEN ERROR:%s\n", profile );
        return( NULL );
    }

    /*==================*/
    /*  �Z�N�V��������  */
    /*==================*/
    sec_len = strlen( section );
    key_len = 0;
    buf[sizeof( buf ) - 1] = 0;
    while( fgets( buf, sizeof( buf ) - 1, fp ) != NULL ) {
        for( i = 0; i < sizeof( buf ); i++ ) {
            if( buf[i] != ' ' && buf[i] != '\t' ) break;
        }
        if( buf[i] == '[' ) {
            for( i++; i < sizeof( buf ); i++ ) {
                if( buf[i] != ' ' && buf[i] != '\t' ) break;
            }
            if( strncmp( &buf[i], section, sec_len ) == 0 ) {
                for( i += sec_len; i < sizeof( buf ); i++ ) {
                    if( buf[i] != ' ' && buf[i] != '\t' ) break;
                }
                if( buf[i] == ']' ) {
                    /*================*/
                    /* ���������ꍇ */
                    /*================*/
                    key_len = strlen( key );
                    break;
                }
            }
        }
    }
    /*======================*/
    /* ������Ȃ������ꍇ */
    /*======================*/
    if( key_len <= 0 ) {
    	LogOut( LT_END, LX_NON, LE_NON, "NO FILE", func_nm, __FILE__, __LINE__ );
        fclose( fp );
        return( NULL );
    }

    /*============*/
    /*  �L�[����  */
    /*============*/
    while( fgets( buf, sizeof( buf ) - 1, fp ) != NULL ) {
        for( i = 0; i < sizeof( buf ); i++ ) {
            if( buf[i] != ' ' && buf[i] != '\t' ) break;
        }
        if( buf[i] == '[' ) break;
        if( strncmp( &buf[i], key, key_len ) == 0 ) {
            for( i += key_len; i < sizeof( buf ); i++ ) {
                if( buf[i] != ' ' && buf[i] != '\t' ) break;
            }
            if( buf[i] == '=' ) {
                /*================*/
                /* ���������ꍇ */
                /*================*/
                for( i++; i < sizeof( buf ); i++ ) {
                    if( buf[i] != ' ' && buf[i] != '\t' ) break;
                }
                strcpy( value, &buf[i] );
                value_len = strlen( value );
                if( value[value_len - 1] == '\n' ) {
                    value[value_len - 1] = 0;
                }
                fclose( fp );
    			LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
                return( EnvRef( value ) );
            }
        }
    }
    /*======================*/
    /* ������Ȃ������ꍇ */
    /*======================*/
    fclose( fp );

    LogOut( LT_END, LX_NON, LE_NON, "NO FILE", func_nm, __FILE__, __LINE__ );
    return( NULL );
}

/******************************************************************************/
/*  �� �� ��  �FLog_out                                                       */
/*  �@�\�T�v  �F���O�t�@�C���o��                                              */
/*  ��    ��  �F                                                              */
/*   ��P���� �F char   file_nm[]   : ���̓t�@�C���|�C���^                    */
/*  �o    ��  �F char   rbuf[];     : �ǂݍ��݃o�b�t�@                        */
/*  ���A���  �F 0�ȏ�              : ����I��(�Ǎ��T�C�Y)                    */
/*               EOF                : FILE END                                */
/*               �ȊO               : ���s                                    */
/******************************************************************************/
int     LogOut( sbt, flg, ecd, msg, fncnm, file, line )
char        sbt[];
char        flg[];
char        ecd[];
char        msg[];
char        fncnm[] ;
char        file[] ;
long        line ;
{
        int     ret=RTN_OK;
static  int     init_flg = 0;               /* �Ƽ���׸�    */
static  struct  stcLogMember    gstLogMem ; /* ���O�o�͏�� */

/*------ 1 ----------------------------------------------------------*/
    if( init_flg == 0 ){
        /* ���O��񏉊��ݒ� */
        memset ( &gstLogMem, '\0', sizeof ( gstLogMem ) ) ;
        strcpy ( gstLogMem.pcAppName,   stcPRM.myp_exefile ) ;
        strcpy ( gstLogMem.pcLoginId,   "DAEMON" ) ;
        init_flg = 1;
    }
/*------ 1 ----------------------------------------------------------*/
    /* �g���[�X��� */
    gstLogMem.eTrcKind=sbt[0];
    /* ���s�t���O */
    strcpy ( gstLogMem.pcExeFlg,    flg ) ;
    /* �G���[�R�[�h */
    strcpy ( gstLogMem.pcErrCode,   ecd ) ;
    /* ���b�Z�[�W */
    strcpy ( gstLogMem.pcMsg,       msg );
    /* �֐��� */
    strcpy ( gstLogMem.pcFncName,   fncnm ) ;

    if(( strcmp( sbt, LT_STA )) == 0 ){
        gstLogMem.eTrcKind='T';
        strcpy( gstLogMem.pcMsg, "start" );
    } else if( strcmp( sbt, LT_END ) == 0 ){
        gstLogMem.eTrcKind='T';
        strcpy( gstLogMem.pcMsg, "end " );
    }

    /* LOGOUT */
    ret = _ZbmlPutLog( &gstLogMem,  file, line );

    /* inifile debug DEBUG */
    if( stcPRM.myp_debug == 1 ){
        if( strcmp( ecd, LE_NON ) == 0 ){
            printf( "sbt[%.1s] pcFncName[%s] pcMsg : %s\n"
                ,sbt,gstLogMem.pcFncName, gstLogMem.pcMsg );
        } else {
            printf( "sbt[%.1s] pcFncName[%s] pcErrCode[%s] pcMsg : %s\n"
                ,sbt,gstLogMem.pcFncName,gstLogMem.pcErrCode,gstLogMem.pcMsg);
        }
    }

    return( RTN_OK );
}

/******************************************************************************/
/*  �� �� ���@�FsFncShmCrt()                                                  */
/*  �@�\�T�v�@�F���L����������                                                */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct stcShm *     ���L�������\����                          */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint                                                           */
/*                   0  ����                                                  */
/*                  -1  �ُ�                                                  */
/******************************************************************************/
int     sFncShmCrt ( stcShm )
struct      SHM     *stcShm;
{
	char	func_nm[MYAPP_LEN_FNCNM+1]; /* �֐����� */
    int     *shmData ;

    /*�g���[�X���O�o�� */
    strcpy( func_nm, "sFncShmCrt" );
    LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

    /*  �擾 */
    stcShm->shm_Id = shmget ( (key_t)stcShm->shm_Key,
                    MYAPP_SHM_SIZE, 0666 | IPC_CREAT ) ;
    if ( stcShm->shm_Id < 0 ) {
        /*  �ُ�I��    LOG */
    	LogOut( LT_ERR, LX_NON, LE_NON, "���L�������̎擾(shmget)�Ɏ��s���܂����B",
				func_nm, __FILE__, __LINE__ );
        return ( RTN_NG ) ;
    }

    /*  �A�^�b�` */
    shmData = ( int * ) shmat ( stcShm->shm_Id, 0 , 0 ) ;
    if ( shmData == ( int * )-1 ) {
        /*  �ُ�I��    LOG */
   		LogOut( LT_ERR, LX_NON, LE_NON, "���L�������̃A�^�b�`(shmat)�Ɏ��s���܂����B",
				func_nm, __FILE__, __LINE__ );
        return ( RTN_NG ) ;
    }

    /*  �l�ݒ� */
    *shmData = 0 ;

    /*  �f�^�b�` */
    if ( shmdt ( shmData ) == -1 ) {
        /*  �ُ�I��    LOG */
    	LogOut( LT_ERR, LX_NON, LE_NON, "���L�������̒l�ݒ�(shmdt)�Ɏ��s���܂����B",
				func_nm, __FILE__, __LINE__ );
        return ( RTN_NG ) ;
    }
    LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
    return ( RTN_OK ) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncShmGet()                                                  */
/*  �@�\�T�v�@�F���L�������擾                                                */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct stcShm *     ���L�������\����                          */
/*�@ ��Q���� �Fint *                   �l                                    */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint                                                           */
/*                   0  ����                                                  */
/*                  -1  �ُ�                                                  */
/******************************************************************************/
int     sFncShmGet ( stcShm, pshmData )
struct      SHM     *stcShm;
int         *pshmData ;
{
	char	func_nm[MYAPP_LEN_FNCNM+1]; /* �֐����� */
    int     *shmData ;

    /* �g���[�X���O�o�� */
    strcpy( func_nm, "sFncShmGet" );
    LogOut( LT_DBG, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

    /* �A�^�b�` */
//printf("ATTACH : %d\n",stcShm->shm_Id);
    shmData = ( int * ) shmat ( stcShm->shm_Id, 0 , 0 ) ;
    if ( shmData == ( int * )-1 ) {
        /* �ُ�I��    LOG */
    	LogOut( LT_ERR, LX_NON, LE_NON, "���L�������̑���(shmget)�Ɏ��s���܂����B",
				func_nm, __FILE__, __LINE__ );
        return ( RTN_NG ) ;
    }

    /* �l�ݒ� */
    *pshmData = *shmData ;

    /* �f�^�b�` */
    if ( shmdt ( shmData ) == -1 ) {
        /* �ُ�I��    LOG */
    	LogOut( LT_ERR, LX_NON, LE_NON, "���L�������̑���(shmget)�Ɏ��s���܂����B",
				func_nm, __FILE__, __LINE__ );
        return ( RTN_NG ) ;
    }
    LogOut( LT_DBG, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
    return ( RTN_OK ) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncShmDel()                                                  */
/*  �@�\�T�v�@�F���L�������폜                                                */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct stcShm *     ���L�������\����                          */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint                                                           */
/*                   0  ����                                                  */
/*                  -1  �ُ�                                                  */
/******************************************************************************/
int     sFncShmDel ( stcShm )
struct      SHM     *stcShm;
{
	char	func_nm[MYAPP_LEN_FNCNM+1]; /* �֐����� */
    int     *shmData ;

    /* �g���[�X���O�o�� */
    strcpy( func_nm, "sFncShmDel" );
    LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

    /* �폜 */
    if ( shmctl ( stcShm->shm_Id, IPC_RMID, NULL) < 0 ) {
        /* �ُ�I��    LOG */
    	LogOut( LT_ERR, LX_NON, LE_NON, "���L�������̑���(shmdel)�Ɏ��s���܂����B",
				func_nm, __FILE__, __LINE__ );
        return ( RTN_NG ) ;
    }
    LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
    return ( RTN_OK ) ;
}
/******************************************************************************/
/*  �� �� ��  �FDaemonCheckProc                                               */
/*  �@�\�T�v  �F�f�[�����d���N���`�F�b�N                                      */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fint     argc    : �p�����^��                                  */
/*   ��Q���� �Fchar    *argv[] : �p�����^���X�g                              */
/*   ��R���� �FPENV    *pEnv   : ���ϐ���                                  */
/*  �o    ��  �F�Ȃ�                                                          */
/*  ���A���  �F INT                                                          */
/*               RTN_OK     : ����                                            */
/*               RTN_NG     : ���s                                            */
/******************************************************************************/
int     DaemonCheckProc( argc, argv, pEnv )
int         argc;
char        *argv[];
PENV		pEnv;
{
    int     ret = RTN_OK;           /* ���A�l */
    int     cnt;                    /* �J�E���g */
    char    func_nm[MYAPP_LEN_FNCNM+1];         /* �֐�����  */
    char    buf[128];               /* �Ǎ��݃o�b�t�@ */
    char    cmd[128];               /* �R�}���h */
    char    tmp[80];                /* ��ƃt�@�C�� */
    FILE    *tfp;                   /* FILE�|�C���^ */

    strcpy( func_nm, "DaemonCheckProc" );
    LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

    /* �R�}���h���s */
    sprintf( tmp, "/tmp/%s.%d.tmp", stcPRM.myp_exefile, getpid() );
    sprintf( cmd, "ps -e | grep %s | grep -v grep | wc > ", pEnv->stLogMem.pcAppName);
    strcat( cmd, tmp );
    system( cmd );

    /* TRACE */
    sprintf( G_msg, "�d���N���`�F�b�N�ŃR�}���h[%s]�����s", cmd );
    LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    /* �N�����̓Ǎ��� */
    if( (tfp = fopen( tmp, "r" )) == NULL ) {
        /* ERROR */
        sprintf( G_msg,"�d���N���`�F�b�N�R�}���h���ʃt�@�C�� �I�[�v���G���[", tmp );
        LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

        return  RTN_NG;
    }
    if( fgets( buf, sizeof( buf ), tfp ) == NULL ) {
        strcpy( buf, "0");
        /* ERROR */
        sprintf( G_msg,"�d���N���`�F�b�N�Ŏ��s�����R�}���h���ʂ��擾�ł��Ȃ�" );
        LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
    }
    fclose( tfp );
    unlink( tmp );

    /* �N�����`�F�b�N */
    cnt = 0;
    sscanf( buf, "%d", &cnt );

    /* TRACE */
    sprintf( G_msg, "�d���N���`�F�b�N��%s"
        , (cnt>1)?"�d�����Ă���" :"�d�����Ă��Ȃ�" );
    LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    if( cnt > 1 ) {
        return( RTN_NG );
    }
    LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
    return RTN_OK;
}
/**********************************************************************/
/*                                                                    */
/*   function name : sigcatch                                         */
/*                                                                    */
/*   purpose : �V�O�i���擾����                                       */
/*                                                                    */
/*   data : 2006.01.26                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2006 ALL RIGHTS RESERVED  */
/**********************************************************************/
void sigcatch(int sig)
{
  fprintf(stdout,"catch signal %d\n",sig);
  EndFlg = 1;
  /* �V�O�i���n���h�����f�t�H���g�ɖ߂� */
  signal(sig,SIG_DFL);
}

/********************************************************************/
/*  �֐���      �Fmain()                                            */
/*  �@�\�T�v    �F�����Z���������C��                                */
/*  ����        �F                                                  */
/*   ��P����   �Fint       argc    �p�����[�^��                    */
/*   ��Q����   �Fchar**    argv    �p�����[�^�l                    */
/*  �o��        �F                                                  */
/*   ����F0                                                        */
/*   �ُ�F1�ȏ�                                                    */
/********************************************************************/
int main(int argc, char** argv)
{
	char	func_nm[MYAPP_LEN_FNCNM+1]; /* �֐����� */
    /*
    *   ���[�J���ϐ���`
    */
    ENV     Env;
    int     rc;

    /***
     ***    �o�b�N�O���E���h���s
     ***/
    if (daemon(1, 1) < 0) {
        exit (9);
    }

    /* man 7 signal �Ŋm�F */
    if(SIG_ERR == signal(SIGINT,sigcatch)){
        fprintf(stderr,"failed to set signalhandler.\n");
        exit(1);
    }

    /*
    *   ����������
    */
    rc = initFunction(argc, argv, &Env);
    if(rc != ERROR_CODE_NORMAL)
    {
        fprintf(stderr, "jidokousei : Error InitFunction [%d]\n", rc);
        return(rc);
    }

    memcpy( &stEnv, &Env, sizeof( ENV ));

    /*
	 *   ���C������
	 */
	rc = mainFunction(&Env);
	if(rc != ERROR_CODE_NORMAL)
	{
	    /* �f�[�^�x�[�X�ؒf */
	    ZdbDisConnect();
	    fprintf(stderr, "jidokousei : Error mainFunction [%d]\n", rc);
	    return(rc);
	}

    /*
    *   �I������
    */
    rc = endFunction(&Env);
    if(rc != ERROR_CODE_NORMAL)
    {
        fprintf(stderr, "jidokousei : Error endFunction [%d]\n", rc);
        return(rc);
    }

    return(ERROR_CODE_NORMAL);
}

/********************************************************************/
/*  �֐���      �FkeyComp                                           */
/*  �@�\�T�v    �F�L�[����r                                        */
/*  ����        �F                                                  */
/*   ��P����   �FKTLIST*   a       ��r���Z���Ώۃ��X�g            */
/*   ��Q����   �FKTLIST*   b       ��r��Z���Ώۃ��X�g            */
/*  �o��        �F                                                  */
/*   ����  �F0                                                      */
/*   �قȂ�F0�ȊO                                                  */
/********************************************************************/
int keyComp(KTLIST* a, KTLIST* b)
{
	/* 32 : knskisymd + bskkbn + bsklne + bskgok + ctrlno */
	return memcmp(a, b, 32);
}

/********************************************************************/
/*  �֐���      �FchannelComp                                       */
/*  �@�\�T�v    �F�L�[����r�i�������ڃR�[�h�܂ށj                  */
/*  ����        �F                                                  */
/*   ��P����   �FKTLIST*   a       ��r���Z���Ώۃ��X�g            */
/*   ��Q����   �FKTLIST*   b       ��r��Z���Ώۃ��X�g            */
/*  �o��        �F                                                  */
/*   ����  �F0                                                      */
/*   �قȂ�F0�ȊO                                                  */
/********************************************************************/
int channelComp(KTLIST* a, KTLIST* b)
{
	/* 40 : knskisymd + bskkbn + bsklne + bskgok + ctrlno + nbkmkcd */
	return memcmp(a, b, 40);
}

/********************************************************************/
/*  �֐���      �FSetControlNG                                      */
/*  �@�\�T�v    �F�R���g���[���ۂ���NG�ݒ�                          */
/*  ����        �F                                                  */
/*   ��P����   �FKTLIST*   kt      �Z���Ώۃ��X�g                  */
/*   ��Q����   �Fint       ng      �G���[�����ʒu�i�Z���Ώۃ��X�g�j*/
/*   ��R����   �FATKSTS*   at      �G���[���                      */
/*   ��S����   �Fint       kensu   �Z���Ώۃ��X�g����              */
/*  �o��        �F                                                  */
/*   ���̃R���g���[���̐擪�ʒu                                     */
/********************************************************************/
int SetControlNG(KTLIST* kt, int ng, ATKSTS* at, int kensu)
{
	char	func_nm[MYAPP_LEN_FNCNM+1]; /* �֐����� */
	int     top  = 0;
	int     next = 0;
	int     j;

    /*�g���[�X���O�o�� */
    strcpy( func_nm, "SetControlNG" );
    LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �R���g���[���͈͎擾 */
	top  = SearchTopControlPosition(kt, ng, 1);
	next = SearchNextControlPosition(kt, ng, kensu, 1);

	/* ���ɓo�^����Ă���Z���Ώۃf�[�^�ɂ��ẮA���R�R�[�h��ݒ肵�ΏۊO�Ƃ��� */
	UpdateATKSTS(at);

	/* �R���g���[���S�̂�NG�ɐݒ� */
	for (j = top; j < next; j++) {
		ATKSTS wk;
		/* �������ݗp�f�[�^�쐬 */
		ConvKTLIST2ATKSTS(kt+j, &wk);
		/* �G���[���͑S�ăG���[�����������`���l���̓��e�����p�� */
		strcpy(wk.autokosiflg, at->autokosiflg);
		strcpy(wk.causecd, at->causecd);

		InsertATKSTS(&wk);
	}

    LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return next;
}

/********************************************************************/
/*  �֐���      �FcheckJidoKousei                                   */
/*  �@�\�T�v    �F�����Z�����菈��                                  */
/*  ����        �F�Ȃ�                                              */
/*  �o��        �F�Ȃ�                                              */
/********************************************************************/
void checkJidoKousei()
{
	char	func_nm[MYAPP_LEN_FNCNM+1]; /* �֐����� */
	KTLIST* kt;							/* �Z���Ώۃ��X�g */
	KTLIST  oldKt;						/* �Z���Ώۃ��X�g�E�R���g���[���m�F�p */
	ATKSTS  at;							/* �����Z���ΏۃR���g���[���e�[�u���C���[�W */
	int		histCnt;					/* �q�X�g�K���� */
	int*	histBefore;					/* �q�X�g�O����(�␳�O�j */
	int*	histAfter;					/* �q�X�g�O����(�␳��j */
	int		kensu;						/* �Z���Ώۃ��X�g���� */
	int		ret;						/* �֐��߂�l */
	int		i;							/* ���[�v�J�E���^ */
	int		j;							/* ���[�v�J�E���^ */
	int		prev;						/* �O�R���g���[���ʒu */
	int		next;						/* ���R���g���[���ʒu */
	int		top;						/* �R���g���[���擪�ʒu */

    /*�g���[�X���O�o�� */
    strcpy( func_nm, "checkJidoKousei" );
    LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	kt    = NULL;
	kensu = 0;
	top   = 0;
	
	/* �Z���Ώۃ��X�g�擾 */
	ret = selectKouseiTaisho(&kt, &kensu);
	/* �G���[�̏ꍇ������0�Ƃ��� */
	if (ret != RTN_OK) {
		kensu = 0;
	} else {
		oldKt = *kt;
	}

	/* ���������[�v����(�`���l���P�ʂŃJ�E���g�A�b�v) */
	for (i = 0; i < kensu; i = SearchNextControlPosition(kt, i, kensu, 0)) {
		memset(&at, 0, sizeof(ATKSTS));
		ConvKTLIST2ATKSTS(kt+i, &at);

		/* �c�a�m��E�L�[�i���͋@�E�R���g���[���m�n�j���ς������m��iCOMMIT�j */
		if (keyComp(kt+i, &oldKt) != 0)
			Commit();

		/* �R���g���[�����x�ُ���ݒ� */
		if (SetCtrlERROR(kt+i, &at) != KSTS_OK) {
			sprintf(G_msg, "�R���g���[�����x�ُ�ibskgok[%s], nbkmkcd[%s], ctrlno[%d])",
					(kt+i)->bskgok,(kt+i)->nbkmkcd,(kt+i)->ctrlno);
    		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

			/* �����Z���ΏۃR���g���[���e�[�u���ɓo�^                  */
			/* �� SetCtrlERROR�ňȉ��̂悤�ɍX�V                       */
			/*    �Eautokosiflg(�����Z���Ώۃt���O) = '0' (�Z���ΏۊO) */
			/*    �Ecausecd(�Z���ΏۊO���R�R�[�h)   = KSTS_CTRLNO (2)  */
			InsertATKSTS(&at);
			continue;
		}

		/* �ŏI�f�[�^�łȂ��A�L�[���̍ŏI�f�[�^�ł������ꍇ�� */
		/* �R���g���[���{���ُ����ݒ肷�� */
		if (i < (kensu-1) && keyComp(kt+i, kt+i+1) == 0) {
			if (SetNoneCount(kt+i, &at) != KSTS_OK) {
				sprintf(G_msg, "�R���g���[���{���ُ�ibskgok[%s], nbkmkcd[%s], ctrlno[%d]�j",
					(kt+i)->bskgok,(kt+i)->nbkmkcd,(kt+i)->ctrlno);
    			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

				/* �����Z���ΏۃR���g���[���e�[�u���ɓo�^                   */
				/* �� SetNoneCount�ňȉ��̂悤�ɍX�V                        */
				/*    �Eautokosiflg(�����Z���Ώۃt���O) = '0' (�Z���ΏۊO)  */
				/*    �Ecausecd(�Z���ΏۊO���R�R�[�h)   = KSTS_CTRLNONE (3) */
				InsertATKSTS(&at);
				continue;
			}
		}

		/* �O�R���g���[�������鎞�����Z���۔���ΏۂƂ��� */
		if ((prev = SearchPrevControlPosition(kt, i, 0)) < 0) {
			/* �����Z���ΏۃR���g���[�����̍ŏI�R���g���[��������ɊY�����鎖�������A */
			/* ���邳���̂ł������~�߂Ă��� */
    		/*LogOut( LT_WRN, LX_NON, LE_NON, "�O�R���g���[������", func_nm, __FILE__, __LINE__ ); */
			continue;
		}

		/* �Z���۔��� */
		ret = KoseiKaHi(kt, i, prev, &at, &next, kensu);

		/* �Z���ۂ�NG�������ꍇ�A�R���g���[���S�̂�NG�Ƃ��� */
		if (ret != RH_KOUSEI) {

            /* �G���[������̏ꍇ�ɏ����i����͍Z���ΏۊO�Ƃ��邽�߁j */
			if (ret == RH_SAIKEN) {
				/* 2009.2.3 Nagata start */
				/* �����Z���ΏۃR���g���[���e�[�u���ɓo�^                   */
				/* �� �đ���̕K�v������ꍇ�A�ȉ��̂悤�ɍX�V                        */
				/*    �Eautokosiflg(�����Z���Ώۃt���O) = '0'  */
				/*    �Ecausecd(�Z���ΏۊO���R�R�[�h)   = KSTS_SAISOKU (12) */
		        strcpy(at.autokosiflg, "0");
        		sprintf(at.causecd, "%d", KSTS_SAISOKU);
				InsertATKSTS(&at);
			}
			else{
				if (ret == RH_NORMAL) {
					sprintf(G_msg, "�Z���ہE����i�Z���ΏۊO�j�ibskgok[%s], nbkmkcd[%s], ctrlno[%d]�j",
						(kt+i)->bskgok,(kt+i)->nbkmkcd,(kt+i)->ctrlno);
    				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
					/* 2009-03-04 Mizu ADD Start --- ���茋�ʂ�����������Ȃ����Ƃւ̑Ή� */
					InsertATKSTS(&at);
					/* 2009-03-04 Mizu ADD End */
				} else {
					sprintf(G_msg, "�Z���ہE�G���[�i�Z���ΏۊO�j�ibskgok[%s], nbkmkcd[%s], ctrlno[%d]�j",
						(kt+i)->bskgok,(kt+i)->nbkmkcd,(kt+i)->ctrlno);
    				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
					/* 2009-03-04 Mizu ADD Start --- ���茋�ʂ�����������Ȃ����Ƃւ̑Ή� */
					InsertATKSTS(&at);
					/* 2009-03-04 Mizu ADD End */
				}
				
				/* 2009-03-04 Mizu DEL Start --- ���茋�ʂ�����������Ȃ����Ƃւ̑Ή� */
				/* next = SetControlNG(kt, i, &at, kensu); */

				/*  ���[�v�J�E���^���R���g���[���u���b�N�̏I�[�ɐݒ� */
				/*  �㑱���铯��R���g���[���f�[�^���X�L�b�v */
				/* i = next - 1; */
				/* 2009-03-04 Mizu DEL End */
			}
			continue;
		
		}

		/* �q�X�g�O�����쐬�i�Z���O�E�Z����j */
		{
			int total = 0;
			int count;

			/* �Z���O */
			ret = MakeHistgramBefore(kt+i, kt+prev, &histBefore);
			if (ret != RTN_OK) {
				sprintf(G_msg, "�Z���O�q�X�g�O�����쐬�s�ibskgok[%s], nbkmkcd[%s], ctrlno[%d]�j",
					(kt+i)->bskgok,(kt+i)->nbkmkcd,(kt+i)->ctrlno);
    			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

				/* �q�X�g�����Ȃ��ꍇ�́A�R���g���[���S�̂��X�L�b�v */
				next = SearchNextControlPosition(kt, i, kensu, 1);
				i = next - 1;
				continue;
			}

			/* �Z���� */
			ret = MakeHistgramAfter(kt+i, kt+prev, &histAfter, at.facter, at.base);
			if (ret != RTN_OK) {
				sprintf(G_msg, "�Z����q�X�g�O�����쐬�s�ibskgok[%s], nbkmkcd[%s], ctrlno[%d]�j",
					(kt+i)->bskgok,(kt+i)->nbkmkcd,(kt+i)->ctrlno);
    			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

				/* �q�X�g�����Ȃ��ꍇ�́A�R���g���[���S�̂��X�L�b�v */
				next = SearchNextControlPosition(kt, i, kensu, 1);
				i = next - 1;
				continue;
			}

			/* �T���v�����`�F�b�N */
			for (count = 0; count < (kt+i)->hstkaikyu; count++) {
				total += histBefore[count];
			}
			if (total < (kt+i)->ksikjnspsu) {
				sprintf(G_msg, "�T���v�������B�ibskgok[%s], nbkmkcd[%s], ctrlno[%d], ksikjnspsu[%d]�j�Ftotal[%d]",
					(kt+i)->bskgok,(kt+i)->nbkmkcd,(kt+i)->ctrlno,(kt+i)->ksikjnspsu, total);
    			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

				/* 2009.2.3 Nagata start */
				/* �����Z���ΏۃR���g���[���e�[�u���ɓo�^                   */
				/* �� SetNoneCount�ňȉ��̂悤�ɍX�V                        */
				/*    �Eautokosiflg(�����Z���Ώۃt���O) = '0' (�T���v�������B)  */
				/*    �Ecausecd(�Z���ΏۊO���R�R�[�h)   = KSTS_COUNT (11) */
		        strcpy(at.autokosiflg, "0");
        		sprintf(at.causecd, "%d", KSTS_COUNT);

				InsertATKSTS(&at);

				/* �T���v����������Ȃ��ꍇ�́A�R���g���[���S�̂��X�L�b�v */
				/* next = SearchNextControlPosition(kt, i, kensu, 1);
				i = next - 1; */
				/* 2009.2.3 Nagata end */

				/* �q�X�g�O�����̈�J�� */
				if (histBefore != NULL) {
					free(histBefore);
					histBefore = NULL;
				}

				continue;
			}
		}

#	ifndef DEBUG_DET
		{/* DEBUG WRITE */
			char tmp[80];
			int l;
			sprintf(tmp, "�q�X�g�O���� bskkbn[%s] bskgok[%s] nbkmkcd[%s] ctrlno[%d]\n",
					(kt+i)->bskkbn, (kt+i)->bskgok, (kt+i)->nbkmkcd, (kt+i)->ctrlno);
			strcpy(G_msg, tmp);
			sprintf(tmp, "�Z���O ");
			strcat(G_msg, tmp);
			for (l = 0; l < (kt+i)->hstkaikyu; l++) {
				sprintf(tmp, "%4d ", histBefore[l]);
				strcat(G_msg, tmp);
			}
			sprintf(tmp, "\n");
			strcat(G_msg, tmp);
			sprintf(tmp, "�Z���� ");
			strcat(G_msg, tmp);
			for (l = 0; l < (kt+i)->hstkaikyu; l++) {
				sprintf(tmp, "%4d ", histAfter[l]);
				strcat(G_msg, tmp);
			}
			sprintf(tmp, "\n");
			strcat(G_msg, tmp);
			
    		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
		}
#	endif

		/* �q�X�g�O�����`�F�b�N */
		{
			/* ���������i�Z���O�j */
			ret = NihoCheck(kt+i, histBefore);

			if (ret != RTN_OK) { 
				sprintf(G_msg, "�����(bskgok[%s], nbkmkcd[%s], ctrlno[%d]) hstkjntn[%f], hstkzmhb[%f]",
					(kt+i)->bskgok, (kt+i)->nbkmkcd, (kt+i)->ctrlno, (kt+i)->hstkjntn, (kt+i)->hstkzmhb);
    			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

				strcpy(at.autokosiflg, "0");
				sprintf(at.causecd, "%d", KSTS_2HOUSEI);

				/* ������f�[�^�����݂����R���g���[���͑S�Ăm�f�Ƃ��� */
				/* next = SetControlNG(kt, i, &at, kensu); */
				/* ���[�v�J�E���^���R���g���[���u���b�N�̏I�[�ɐݒ� */
				/* �㑱���铯��R���g���[���f�[�^���X�L�b�v */
				/* i = next - 1 ;*/
				/* ��L�̏������Ƃ��߂āA�j�����f�[�^�����݂������R�[�h�݂̂m�f�Ƃ���悤�ɕύX */
				InsertATKSTS(&at);

				/* �q�X�g�O�����̈�J�� */
				if (histAfter != NULL) {
					free(histAfter);
					histAfter = NULL;
				}
				if (histBefore != NULL) {
					free(histBefore);
					histBefore = NULL;
				}

				continue;
			}

			/* �ŕp����i�Z���O�E�Z����j */
			ret = SaihinCheck(kt+i, histBefore, histAfter);

			if (ret != RTN_OK) {
				sprintf(G_msg, "�ŕp����i�Z���O�E�Z����j(bskgok[%s], nbkmkcd[%s], ctrlno[%d]) (hstkjntn[%f], hstkzmhb[%f]) shrnglwhf[%f] < data < shrnghihf[%f]",
					(kt+i)->bskgok, (kt+i)->nbkmkcd, (kt+i)->ctrlno, (kt+i)->hstkjntn, (kt+i)->hstkzmhb,
					(kt+i)->shrnglwhf, (kt+i)->shrnghihf);
    			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

				strcpy(at.autokosiflg, "0");
				sprintf(at.causecd, "%d", KSTS_SAIHIN);

				/* �ŕp����G���[�����݂����R���g���[���͑S�Ăm�f�Ƃ��� */
				/* next = SetControlNG(kt, i, &at, kensu); */
				/* ���[�v�J�E���^���R���g���[���u���b�N�̏I�[�ɐݒ� */
				/* �㑱���铯��R���g���[���f�[�^���X�L�b�v */
				/* i = next - 1; */
				/* ��L�̏������Ƃ��߂āA�ŕp�G���[�f�[�^�����݂������R�[�h�݂̂m�f�Ƃ���悤�ɕύX */
				InsertATKSTS(&at);


				/* �q�X�g�O�����̈�J�� */
				if (histAfter != NULL) {
					free(histAfter);
					histAfter = NULL;
				}
				if (histBefore != NULL) {
					free(histBefore);
					histBefore = NULL;
				}

				continue;
			}
		}

		/* �q�X�g�O�����̈�J�� */
		if (histAfter != NULL) {
			free(histAfter);
			histAfter = NULL;
		}

		if (histBefore != NULL) {
			free(histBefore);
			histBefore = NULL;
		}

		/* �S�Ă̌������p�X�����f�[�^�͍Z���ΏۂƂ��ēo�^ */
		/* autokosiflg(�����Z���Ώۃt���O) = '1' (�����Z���Ώ�) */
		/* causecd(�Z���ΏۊO���R�R�[�h)   = KSTS_OK (0)        */
		strcpy(at.autokosiflg, "1");
		sprintf(at.causecd, "%d", KSTS_OK);
		InsertATKSTS(&at);
	}

	if (kt != NULL) {
		free(kt);
		kt = NULL;
	}

    LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
}

/******************************************************************************/
/*  �� �� ��  �FsFncSleepEx()                                                 */
/*  �@�\�T�v  �F�X���[�v                                                      */
/*  ��    ��  �F                                                              */
/*   ��P���� �F       PENV  pEnv    �v���O�����Ǘ��\����                     */
/*   ��Q���� �Fstruct SHM  *stcShm  ���L�������Ǘ��\����                     */
/*  �o    ��  �F                                                              */
/*  ���A���  �F  0     : ����                                                */
/*            �F  1     : ��~�R�}���h��M                                    */
/******************************************************************************/
int sFncSleepEx ( PENV pEnv, struct SHM *stcShm )
{
	int		iStopFlg = 0 ;					/* �I���t���O */
	time_t	sleepTm ;						/* �X���[�v���� */
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐����� */
	
	/* �X���[�v���鎞�Ԏ擾 */
	sleepTm = time(NULL) + (time_t)pEnv->sleepInterval ;
	
	while( time(NULL) < sleepTm )
	{
		/***                        ***/
		/***    ��~�R�}���h�m�F    ***/
		/***                        ***/
		if ( sFncShmGet ( stcShm, &iStopFlg ) == 0 ) {
			if ( iStopFlg == 1 ) {
				strcpy( func_nm, "sFncSleepEx" );
				LogOut( LT_OPT, LX_NON, LE_NON, "��~�R�}���h��M", func_nm, __FILE__, __LINE__ );
				break ;
			}
		}

		/* 1�b�X���[�v */
		sleep ( 1 );
	}

	return iStopFlg;
}

/********************************************************************/
/*  �֐���      �FinitFunction()                                    */
/*  �@�\�T�v    �F����������                                        */
/*  ����        �F                                                  */
/*   ��P����   �Fint       argc    �p�����[�^��                    */
/*   ��Q����   �Fchar**    argv    �p�����[�^�l                    */
/*   ��R����   �FPENV      pEnv    �v���O�����Ǘ��\����            */
/*  �o��        �F                                                  */
/*   ����F0                                                        */
/*   �ُ�F0�ȊO                                                    */
/********************************************************************/
int initFunction(int argc, char** argv, PENV pEnv)
{
	char	func_nm[MYAPP_LEN_FNCNM+1]; /* �֐����� */
    /*
    *   ���[�J���ϐ���`
    */
    int     rc;
    char    tmp[12];

    /*
    *   ������
    */

    /*�v���O�����Ǘ��\���̏����� */
    memset(pEnv, 0, sizeof(ENV));

    /* ���O�t�@�C���I�[�v�� */
    rc = ZbmlOpenLog( EnvRef(LOGINIFILE) );
    if(rc != 0)
    {
        LogOut( LT_ERR, LX_NON, LE_NON, "���O�t�@�C�����I�[�v���ł��܂���ł����B", func_nm, __FILE__, __LINE__ );
        return(ERROR_CODE_LOG_OPEN_ERROR);
    }

    /* ���O��񏉊����ݒ� */
    memset(&pEnv->stLogMem, '\0', sizeof(pEnv->stLogMem)) ;

    char    *cp;                        /* �Ώۃp�����^ */
    /* ���s�v���O�������̐ݒ� */
    for( cp = argv[0], cp += strlen( cp ); cp != argv[0]; --cp ) {
        if( *cp == '/' || *cp == '\\' ) {
            cp++;
            break;
        }
    }
    /* �v���O�������Z�b�g */
    strcpy(pEnv->stLogMem.pcAppName, cp);

    /* �v���O�����J�n���O�o�� */
    strcpy( func_nm, "initFunction" );
    LogOut( LT_OPT, LX_NON, LE_NON, "�v���O�����N��", func_nm, __FILE__, __LINE__ );

    /* 2�d�N���`�F�b�N  
    if( DaemonCheckProc(argc, argv, pEnv) != RTN_OK ){
        sprintf( G_msg, "�Q�d�N���h�~�̂��߁A�������I�����܂��B" );
        LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
        return(ERROR_MULTI_RUN);
    }
    */

    /* �R�}���h���C�������`�F�b�N */
    /* ����2�����Ƀp�����[�^�t�@�C���̃p�X�����͂���Ă��Ȃ���΃G���[ */
    if(argc != 2)
    {
    	LogOut( LT_ERR, LX_NON, LE_NON, "�R�}���h���C���������s���ł��B",
				func_nm, __FILE__, __LINE__ );
        return(ERROR_CODE_CMD_PRM_ERROR);
    }

    /* �p�����[�^�t�@�C���I�[�v�� */
    pEnv->bp = ZbmlPrmOpen(argv[1]) ;
    if(pEnv->bp == NULL)
    {
    	LogOut( LT_ERR, LX_NON, LE_NON, "�p�����[�^�t�@�C���̃I�[�v���Ɏ��s���܂����B",
				func_nm, __FILE__, __LINE__ );
        return(ERROR_CODE_PRM_OPEN_ERROR);
    }

    /*
    *   �p�����[�^�擾
    */

    /* �f�[�^�x�[�X���擾 */
    if(ZbmlPrmGetVal(pEnv->bp, PRM_DB_NAME, pEnv->cDbName) != 0)
    {
		sprintf(G_msg, "�p�����[�^�̎擾�Ɏ��s���܂����B(%s : %s)", PRM_DB_NAME, pEnv->cDbName);
    	LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
        return(ERROR_CODE_PRM_GET_ERROR);
    }
	sprintf(G_msg, "%s     : %s", PRM_DB_NAME, pEnv->cDbName);
    LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    /* �c�a���[�U�h�c�擾 */
    if(ZbmlPrmGetVal(pEnv->bp, PRM_DB_USER_ID, pEnv->cDbUserId) != 0)
    {
		sprintf(G_msg, "�p�����[�^�̎擾�Ɏ��s���܂����B(%s : %s)", PRM_DB_USER_ID, pEnv->cDbUserId);
    	LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
        return(ERROR_CODE_PRM_GET_ERROR);
    }
	sprintf(G_msg, "%s  : %s", PRM_DB_USER_ID, pEnv->cDbUserId);
    LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    /*�c�a�p�X���[�h�擾 */
    if(ZbmlPrmGetVal(pEnv->bp, PRM_DB_PASSWORD, pEnv->cDbPassword) != 0)
    {
		sprintf(G_msg, "�p�����[�^�̎擾�Ɏ��s���܂����B(%s : %s)", PRM_DB_PASSWORD, pEnv->cDbPassword);
    	LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
        return(ERROR_CODE_PRM_GET_ERROR);
    }
	sprintf(G_msg, "%s : %s", PRM_DB_PASSWORD, pEnv->cDbPassword);
    LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    /* �X���[�v(�b)�擾 */
    if(ZbmlPrmGetVal(pEnv->bp, PRM_SLEEP_SEC, tmp) != 0)
    {
		sprintf(G_msg, "�p�����[�^�̎擾�Ɏ��s���܂����B(%s : %s)", PRM_SLEEP_SEC, tmp);
    	LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
        return(ERROR_CODE_PRM_GET_ERROR);
    }
	sprintf(G_msg, "%s   : %s", PRM_SLEEP_SEC, tmp);
    LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
    /* SLEEP_SEC */
    pEnv->sleepInterval = atoi(tmp);

    /* 1.01 SHM_KEY GET */
    if(ZbmlPrmGetVal(pEnv->bp, PRM_SHM_KEY, tmp) != 0)
    {
		sprintf(G_msg, "�p�����[�^�̎擾�Ɏ��s���܂����B(%s : %s)", PRM_SHM_KEY, tmp);
    	LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
        return(ERROR_CODE_PRM_GET_ERROR);
    }
	sprintf(G_msg, "%s     : %s", PRM_SHM_KEY, tmp);
    LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
    /* SHM_KEY */
    pEnv->shm_Key = atoi(tmp);

    /* �p�����[�^�t�@�C���N���[�Y */
    ZbmlPrmClose(pEnv->bp);

    LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
    return(ERROR_CODE_NORMAL);
}

/********************************************************************/
/*  �֐���      �FmainFunction()                                    */
/*  �@�\�T�v    �F���C������                                        */
/*  ����        �F                                                  */
/*   ��P����   �FPENV      pEnv    �v���O�����Ǘ��\����            */
/*  �o��        �F                                                  */
/*   ����F0                                                        */
/*   �ُ�F0�ȊO                                                    */
/********************************************************************/
int
mainFunction(PENV pEnv)
{
	char	func_nm[MYAPP_LEN_FNCNM+1]; /* �֐����� */
    /*
    *   ���[�J���ϐ���`
    */
    int     rc;
    struct  SHM stcShm;                 /* 1.01 �I�����f���L������ */
    int     li_stopFlg = 0;             /* 1.01 �I�����f */

    //�g���[�X���O�o��
    strcpy( func_nm, "mainFunction" );
    LogOut( LT_OPT, LX_NON, LE_NON, "mainFunction START", func_nm, __FILE__, __LINE__ );

    /*
    *   ������
    */

    /* 1.01 ���L���������� */
    stcShm.shm_Key = pEnv->shm_Key;
    if( sFncShmCrt ( &stcShm ) < 0 ) {
        char ebuf[10];
        sprintf( ebuf, "���L�������������s:shmkey[%d]", errno );
    	LogOut( LT_ERR, LX_NON, LE_NON, ebuf, func_nm, __FILE__, __LINE__ );
        return( ERROR_FUNC_ERROR );
    }

    /*
    *   �f�[�^�x�[�X�ڑ�
    */
    rc = ZdbConnect(pEnv->cDbName, pEnv->cDbUserId, pEnv->cDbPassword);
    if(rc != 0)
    {
    	LogOut( LT_ERR, LX_NON, LE_NON, "�f�[�^�x�[�X�̐ڑ��Ɏ��s���܂����B",
				func_nm, __FILE__, __LINE__ );

		sFncShmDel ( &stcShm ) ;

        return(ERROR_CODE_DB_CONNECT_ERROR);
    }

    /*
    *   ���x�Ǘ��ُ�`�F�b�N����
    */
    while(1) {
        /* �I���V�O�i�����`�F�b�N */
        if ( EndFlg ) {
            break;
        }

	    /* �����Z������ */
		checkJidoKousei();

        /***
         *** ��~�R�}���h�m�F
         ***/
		/* �p�ɂɉ񂷕K�v�������̂�FD103.ini��SLEEP_SEC�Őݒ肵���b������SLEEP���� */
		if ( sFncSleepEx ( pEnv, &stcShm ) != 0 ) {
			break;
		}
	}

    ZdbDisConnect();

    sFncShmDel ( &stcShm ) ;

    LogOut( LT_OPT, LX_NON, LE_NON, "mainFunction END", func_nm, __FILE__, __LINE__ );
    return(ERROR_CODE_NORMAL);
}

/********************************************************************/
/*  �֐���      �FendFunction()                                     */
/*  �@�\�T�v    �F�I������                                          */
/*  ����        �F                                                  */
/*   ��P����   �FPENV      pEnv    �v���O�����Ǘ��\����            */
/*  �o��        �F                                                  */
/*   ����F0                                                        */
/*   �ُ�F0�ȊO                                                    */
/********************************************************************/
int endFunction(PENV pEnv)
{
	char	func_nm[MYAPP_LEN_FNCNM+1]; /* �֐����� */
    /*
    *   ���[�J���ϐ���`
    */

    /* �g���[�X���O�o�� */
    strcpy( func_nm, "endFunction " );
    LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

    /*
    *   ������
    */

    LogOut( LT_OPT, LX_NON, LE_NON, "�v���O�����I��", func_nm, __FILE__, __LINE__ );

    LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

    ZbmlCloseLog( );

    return(ERROR_CODE_NORMAL);
}

/** End of File ***************************************************************/
