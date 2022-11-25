/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��  							*/
/*                             							*/
/* �@�V�X�e�����F������V�X�e��							*/
/* �@�t�@�C�����FND102.c              						*/
/* �@�T�@�@�@�v�F	        						*/
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
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

#include "ND102.h"

/******************************************************************************/
/* Define��`                                                                 */
/******************************************************************************/
//	TRACE
#if defined ( _TRACE )
#define malloc(a)   _malloc(a, __FILE__, __LINE__)
#endif

/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/
struct stcLogMember	gstLogMem ;		//	���O�o�͏��

/******************************************************************************/
/* �֐��錾                                                                   */
/******************************************************************************/
//	�t�@�C���E�f�[�^�x�[�X�o�͊֐�

//	���L����������֐�
static	int	sFncShmCrt() ;
static	int	sFncShmGet ( int *) ;
static	int	sFncShmDel() ;


//	���̑�
static	int     FileFilter( struct dirent *namelist );
static	void	endFunction();
void	sFncTrim( char *, char * );

/******************************************************************************/
/*  �� �� ���@�FinitFunction()							*/
/*  �@�\�T�v�@�F���������֐�							*/
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct	env *  	�v���O�������\���́B		 		*/
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F  0     : ����							*/
/* �@�@�@�@�@�@�@-1     : ���s							*/
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
        //      �t�@�C�������f�B���N�g��
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DIR_INPUT, pAppEnv.cInputDir ) != 0 ) {
		//      �ُ�I��        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_INPUT ) ;
		return ( -1 ) ;
	}
	//      �����ς݃t�@�C���ړ��f�B���N�g��
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DIR_OK, pAppEnv.cEndFileDirOK ) != 0 ) {
		//      �ُ�I��        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_OK ) ;
		return ( -1 ) ;
	}
	//      �����G���[�t�@�C���ړ��f�B���N�g��
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DIR_NG, pAppEnv.cEndFileDirNG ) != 0 ) {
		//      �ُ�I��        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_NG ) ;
		return ( -1 ) ;
	}
	//      �����Ώۃt�@�C���g���q
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_FILE_EXT, pAppEnv.cFileExt ) != 0 ) {
		//      �ُ�I��        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_FILE_EXT ) ;
		return ( -1 ) ;
	}

	//	�p�����[�^�t�@�C���N���[�Y	
	ZbmlPrmClose ( pAppEnv.bp ) ;

	/***
	 ***	���L����������	
	 ***/
	if ( sFncShmCrt() < 0 ) {
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
/*  �o�@�@�́@�F								*/
/*  ���A���@�F  0     : ����							*/
/* �@�@�@�@�@�@�@-1     : ���s							*/
/********************************************************************************/
int
mainFunction()
{
	int	li_retSts = 0;
	int	li_stopFlg = 0;

	int	i = 0;
	int	file_cnt = 0;

	char	w_infilenm[256];	// �����O�t�@�C����(�t���p�X)
	char	w_endfilenm[256];	// �����I���t�@�C����(�t���p�X)
	char	w_endfilenm_base[256];	// �����I���t�@�C����
	char	w_filenm[256];		// �����t�@�C����
	struct	dirent  **namelist;	// get input file
	FILE	*fp;			// �Ǎ�̧���߲��

	/***
	 ***		�i�v���[�v
	 ***		��~�R�}���h�ŏI��
	 ***/
	while ( 1 ) {
		/* ��~�R�}���h�m�F */
		if ( sFncShmGet ( &li_stopFlg ) != 0 ) {
			return( RTN_NG );
		}
		if ( li_stopFlg == 1 ) {
			return( RTN_OK );
		}

                // �Ώۃt�@�C���̎擾
                file_cnt = scandir( pAppEnv.cInputDir, &namelist, (void*)FileFilter, alphasort);
                if ( file_cnt < 0){
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "���T�e���C�g���ʏ��t�@�C���̎擾(scandir)�Ɏ��s���܂����B") ;
                        continue;
                }

		for( i=0; i < file_cnt; i++ ){
			strcpy( w_filenm, namelist[i]->d_name );
			// scadir�t�@�C������free
			free( namelist[i] );

			// �t�@�C�����쐬
			memset( w_infilenm,  '\0',sizeof( w_infilenm ));
			memset( w_endfilenm, '\0',sizeof( w_endfilenm ));
			sprintf( w_infilenm, "%s/%s", pAppEnv.cInputDir, w_filenm );

			sFncPutLog ( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "�t�@�C�������J�n[%s]", w_infilenm );

			// INPUT FILE OPEN
			if( ( fp = fopen( w_infilenm, "r" ) ) == NULL ){
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "�t�@�C���I�[�v���Ɏ��s���܂����B[FILE_NAME:%s]", w_infilenm ) ;
				continue;
			}

			// ���C������
			li_retSts = mainProc( fp );
			if( li_retSts == RTN_NG ){
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"�������ɃG���[���������܂����B[FILE_NAME:%s]", w_infilenm ) ;
			}

			// INPUT FILE CLOSE
			fclose( fp );

			// �����σt�@�C���̖��̕ύX
			// �ύX�t�@�C�����쐬
			if ( li_retSts == RTN_OK ){
				sprintf( w_endfilenm, "%s/%s" , pAppEnv.cEndFileDirOK,  w_filenm );
			} else {
				sprintf( w_endfilenm, "%s/%s" , pAppEnv.cEndFileDirNG,  w_filenm );
			}
			// �ύX�t�@�C���Ɠ����̃t�@�C�������݂��Ȃ���
			int cnt = 0;
			strcpy ( w_endfilenm_base, w_endfilenm );
			for( ;; ){
				int fd = open( w_endfilenm, O_RDONLY, 0 );
				if( fd == EOF ){
					break;
				} else {
					close( fd );
				}
				sFncPutLog ( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "�d���t�@�C���L��[%s]", w_endfilenm );
				cnt++;
				sprintf ( w_endfilenm, "%s.%d", w_endfilenm_base, cnt );
                        }

			// �t�@�C�����ύX
			if ( rename( w_infilenm, w_endfilenm ) != 0) {
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "�t�@�C���̈ړ��Ɏ��s���܂����B[%s]->[%s]:%s", w_infilenm , w_endfilenm, strerror(errno) );
				continue;
			}

			sFncPutLog ( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "�t�@�C����������[%s]", w_endfilenm );
		}
		sleep( 1 );
	}

	return ( 0 ) ;
}

/******************************************************************************/
/*  �� �� ��  �FmainProc                                                      */
/*  �@�\�T�v  �F���T�e���C�g���ʏ��t�@�C������                              */
/*  ��    ��  �F                                                              */
/*   ��P���� �F FILE   pfp     : ���̓t�@�C�����ʎq                          */
//   ��2 ���� :  int    errValue : �G���[���ʎq                               */�@
/*  �o    ��  �F �Ȃ�                                                         */
/*  ���A���  �F INT                                                          */
/*               RTN_OK     : ����                                            */
/*               RTN_NG     : ���s                                            */
/******************************************************************************/
int	mainProc( pfp )
FILE	*pfp;
{
	/* �˗���M */
	my_stORDERRACK	file_kka;	/* �t�@�C����� */

	char    rbuf[RECORDSIZE*2+1];          /* �ǂݍ��ݴر          */
	int 	li_retSts = 0;

        /* ̧�ق̓Ǎ� */
	while( fgets( rbuf, FILE_RECSIZE + 1, pfp ) != NULL ){	// read while start ----------->
		
		/* --------------------------------	*/
		/*	���� 				*/
		/* --------------------------------	*/
		/* �t�@�C�����R�[�h���擾���� */
		li_retSts = sFncGetFileRecord( rbuf, &file_kka );
		if( li_retSts != RTN_OK ){
			return( RTN_NG );
		}

		/* ���T�e���C�g���ʏ���Insert���� */
		li_retSts = sFncInsRackOeder( &file_kka );
		if( li_retSts != RTN_OK ){
			return( RTN_NG );
		}
	}

	return( RTN_OK );
}

/********************************************************************************/
/*  �� �� ��  �FsFncGetFileRecord						*/
/*  �@�\�T�v  �F�t�@�C�����R�[�h�擾						*/
/*  ��    ��  �F								*/
/*   ��P���� �Fchar	*  	�t�@�C�����R�[�h���				*/
/*   ��Q���� �Fstruct	*	�t�@�C�����\����				*/
/*  �o    ��  �F�Ȃ�								*/
/*  ���A���  �F INT								*/
/*		 0		: ����I��					*/
/*		 1		: �ُ�I��    					*/	
/********************************************************************************/
int sFncGetFileRecord(buff, pOrderRack)
char			*buff;
my_stORDERRACK		*pOrderRack;
{
	char	*pFld[128];
	int	cnt;
	int	offset;

	memset( pFld, '\0', sizeof( pFld ) );
	/* �J���}��؂�̃��R�[�h�𕪊����ADB���R�[�h�̍\���̂ɐݒ肷��B */
	cnt = 0;
	offset = 0;;
	pFld[cnt] = &buff[cnt];
	cnt++;
	while (buff[offset] != '\0') {
		if (buff[offset] == ',') {
			pFld[cnt++] = &buff[offset+1];
			buff[offset] = '\0';
		}
		if (buff[offset] == '\n') {
			buff[offset] = '\0';
		}
		offset++;
	}

	if (cnt != 2) {
		/* �t�B�[���h������v���Ȃ� */
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncGetFileRecord", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		             "�t�@�C���̃t�B�[���h�������v���܂���B" ) ;
		return -1;
	}

	/* �e�t�B�[���h���i�[����B */
        sprintf( pOrderRack->knskisymd, pFld[0], sizeof( pOrderRack->knskisymd )-1 );
	strncpy( pOrderRack->asyrckid, pFld[1], sizeof( pOrderRack->asyrckid )-1 );     /* ���b�NID */

	return( 0 );
}

/******************************************************************************/
/*  �� �� ��  �FFileFilter                                                    */
/*  �@�\�T�v  �F�t�@�C���t�B���^�[�y�R�[���o�b�N�֐��z                        */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct          dirent *     �f�B���N�g���\����               */
/*  �o    ��  �F�Ȃ�                                                          */
/*  ���A���  �F INT                                                          */
/*               0              : �ΏۊO�t�@�C��                              */
/*               1              : �Ώۃt�@�C��                                */
/******************************************************************************/
static  int     FileFilter( namelist )
struct	dirent  *namelist ;
{
	char    w_fnm[256];
	char    *w_fext;
	struct  stat    statbuf;                                // get input file status

	// �f�B���N�g���͏���
	sprintf( w_fnm, "%s/%s", pAppEnv.cInputDir, namelist->d_name );
	stat( w_fnm, &statbuf );
	if( S_ISDIR( statbuf.st_mode )){
		// �ΏۊO
		return( 0 );
	}

	// �Ώۃt�@�C���̊g���q�ɂ�锻�f
	if( strcmp( pAppEnv.cFileExt, "" ) != 0 ) {
		w_fext = strrchr( namelist->d_name, '.' ) ;
		if( strcmp( w_fext, pAppEnv.cFileExt ) == 0 ){
			// OK
			return ( 1 );
		}
	}

	return ( 0 );
}

/******************************************************************************/
/*  �� �� ���@�FendFunction()							*/
/*  �@�\�T�v�@�F�I�������֐�							*/
/*  ���@�@�́@�F                                                              */
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
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmget", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "���L�������̑���Ɏ��s���܂���" ) ;
		return ( -1 ) ;
	}

	//	�A�^�b�`	
	shmData = ( int * ) shmat ( pAppEnv.shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmat", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "���L�������̑���Ɏ��s���܂���" ) ;
		return ( -1 ) ;
	}

	//	�l�ݒ�	
	*shmData = 0 ;

	//	�f�^�b�`	
	if ( shmdt ( shmData ) == -1 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "���L�������̑���Ɏ��s���܂���" ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/********************************************************************************/
/*  �� �� ���@�FsFncShmGet()							*/
/*  �@�\�T�v�@�F���L�������擾							*/
/*  ���@�@�́@�F                                                                */
/*�@ ��P���� �Fint *   	�l						*/
/*  �o�@�@�́@�F                                                                */
/*  ���A���@�Fint								*/
/*		 0	����							*/
/*		-1	�ُ�							*/
/********************************************************************************/
static int
sFncShmGet ( pshmData )
int	*pshmData ;
{
	int		*shmData ;

	//	�A�^�b�`	
	shmData = ( int * ) shmat ( pAppEnv.shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmat", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "���L�������̑���Ɏ��s���܂���" ) ;
		return ( -1 ) ;
	}

	//	�l�ݒ�	
	*pshmData = *shmData ;

	//	�f�^�b�`	
	if ( shmdt ( shmData ) == -1 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
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
	endFunction () ;
	exit ( 0 ) ;
}
/** End of File ***************************************************************/
