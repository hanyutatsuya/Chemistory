/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��  							*/
/*                             							*/
/* �@�V�X�e�����F������V�X�e��							*/
/* �@�t�@�C�����FLD103.c              						*/
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
#include <stdbool.h>

#include "bmllog.h"
#include "bmlprm.h"
#include "bml_misc.h"
#include "bml_date.h"
#include "bml_DBCom.h"

#include "sql.h"
#include "LD103.h"

/******************************************************************************/
/* Define��`                                                                 */
/******************************************************************************/

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
static	int	sFncShmGet(int *) ;
static	int	sFncShmDel() ;


//	���̑�
static  int     FileFilter( struct dirent *namelist );

static	int	initFunction(int , char**);
static	int	mainProc(FILE * );
static  void	endFunction() ;

int	ReadFile(char *, FILE *);
int	chkUpdateKanjya(my_stDbKanjya *, my_stCHKZOK *);
int	ChkErrZok(my_stCHKZOK *);

int	sFncSelSysKnr(my_stSYSKNR *);
int	sFncChkZok(char *, char *, my_stCHKZOK **, int *);
int	sFncRuiChkZok(char *, char *, my_stCHKZOK **, int *);
int	sFncMoveRuiTou(char *, char *);
int	sFncUpdateKanjya(my_stCHKZOK *);
int	InsHkHrIrai(my_stCHKZOK *, int);
int	sFncCntOrder(my_stCHKZOK *, int *);
int	sFncInsRecalc(my_stCHKZOK *);

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
	memset ( &pAppEnv , '\0', sizeof ( pAppEnv ) ) ;

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
	//	�t�@�C���擾�p�V�F��
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_FILE_GET_SHELL, pAppEnv.cFileGetSH ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_FILE_GET_SHELL ) ;
		return ( -1 ) ;
	}
	//	�t�@�C�������f�B���N�g��
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DIR_INPUT, pAppEnv.cInputDir ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_INPUT ) ;
		return ( -1 ) ;
	}
	//	�����ς݃t�@�C���ړ��f�B���N�g��
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DIR_OK, pAppEnv.cEndFileDirOK ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_OK ) ;
		return ( -1 ) ;
	}
	//	�����G���[�t�@�C���ړ��f�B���N�g��
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DIR_NG, pAppEnv.cEndFileDirNG ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_NG ) ;
		return ( -1 ) ;
	}
	//	�����Ώۃt�@�C���v���t�B�b�N�X
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_FILE_PRX, pAppEnv.cFilePrx ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_FILE_PRX ) ;
		return ( -1 ) ;
	}
	//	���b�N�t�@�C���BLD101(�����G���[�`�F�b�N���쐬) �N���g���K�[�B�ŏ��̏������I�������쐬�B
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_LOCK_FILE, pAppEnv.cLockFile ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_LOCK_FILE ) ;
		return ( -1 ) ;
	}
	//	�N��x������擾
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_AGE_HI, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_AGE_HI ) ;
		return ( -1 ) ;
	}
	pAppEnv.AgeHi= atoi ( lc_prmBuf ) ;
	//	�N��x�������擾
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_AGE_LOW, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_AGE_LOW ) ;
		return ( -1 ) ;
	}
	pAppEnv.AgeLow= atoi ( lc_prmBuf ) ;
	//	�g���x������擾
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_SC_HI, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_SC_HI ) ;
		return ( -1 ) ;
	}
	pAppEnv.ScHi= atof ( lc_prmBuf ) ;
	//	�g���x�������擾
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_SC_LOW, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_SC_LOW ) ;
		return ( -1 ) ;
	}
	pAppEnv.ScLow= atof ( lc_prmBuf ) ;
	//	�̏d�x������擾
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_TJ_HI, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_TJ_HI ) ;
		return ( -1 ) ;
	}
	pAppEnv.TjHi= atof ( lc_prmBuf ) ;
	//	�̏d�x�������擾
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_TJ_LOW, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_TJ_LOW ) ;
		return ( -1 ) ;
	}
	pAppEnv.TjLow= atof ( lc_prmBuf ) ;
	//	SLEEP���Ԏ擾(��)
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_SLEEP_MIN, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_SLEEP_MIN ) ;
		return ( -1 ) ;
	}
	pAppEnv.SleepMin= atoi ( lc_prmBuf ) ;

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

	int	min = 0;

	char	cmd[1024];
	char	w_infilenm[256];	// �����O�t�@�C����(�t���p�X)
	char	w_endfilenm[256];	// �����I���t�@�C����(�t���p�X)
	char	w_filenm[256];		// �����I���t�@�C����
	struct	dirent  **namelist;	// get input file
	FILE	*fp;			// �Ǎ�̧���߲��

	my_stSYSKNR	pSysKnr;	//

	/***
	 ***		�i�v���[�v
	 ***		��~�R�}���h�ŏI��
	 ***/
	while ( 1 ) {
		/* 1�����Ƃɒ�~�R�}���h���m�F���Ȃ���ݒ肳�ꂽ���ԃX���[�v */
		for ( min=0; min < pAppEnv.SleepMin; min++ ) {
			sleep ( 60 ) ;
			/* ��~�R�}���h�m�F */
			if ( sFncShmGet ( &li_stopFlg ) != 0 ) {
	        		return( RTN_NG );
			}
			if ( li_stopFlg == 1 ) {
	        		return( RTN_OK );
			}
			/* �V�X�e���Ǘ��}�X�^ ���� */
			if ( sFncSelSysKnr( &pSysKnr ) !=  RTN_OK ){
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "�V�X�e���Ǘ����̎擾�Ɏ��s���܂���");
		        	return( RTN_NG );
			}
			/* �˗��d�m�c�����Ă��鎞�͓��������̊J�n�m�F���s���B */
			if( strcmp( pSysKnr.iriendflg, "1" ) == 0 ) {
				/* �����������n�܂��Ă�����I�� */
				if( strcmp( pSysKnr.unyflg, "1" ) == 0 ) {
					sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						     "���������̊J�n���m�F���܂����B");
					return( RTN_OK );
				}
			}
		}

		/* �V�X�e���Ǘ��}�X�^ ���� */
		if ( sFncSelSysKnr( &pSysKnr ) !=  RTN_OK ){
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "�V�X�e���Ǘ����̎擾�Ɏ��s���܂���");
	        	return( RTN_NG );
		}
		/* �˗��d�m�c������܂őҋ@ */
		if( strcmp( pSysKnr.iriendflg, "1" ) != 0 ) {
			continue;
		}

		sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "FTP �R�}���h���J�n���܂��B");

		// FTP�R�}���h�p�V�F���̎��s
		sprintf( cmd, "sh %s", pAppEnv.cFileGetSH);
		system( cmd );

                // �Ώۃt�@�C���̎擾
                file_cnt = scandir( pAppEnv.cInputDir, &namelist, (void*)FileFilter, alphasort);
                if ( file_cnt < 0){
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				     "�t�@�C���̏��擾(scandir)�Ɏ��s���܂����B") ;
                        break;
		} else if ( file_cnt == 0 ) {
			sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "�����C�����͑��݂��܂���ł����B");
			// LD101�X�^�[�g�g���K�[�̃t�@�C�����쐬
			if( ( fp = fopen( pAppEnv.cLockFile, "w" ) ) == NULL ){
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "���b�N�t�@�C���̍쐬�Ɏ��s���܂����B[%s]", pAppEnv.cLockFile ) ;
			}
			fclose( fp );
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
			// INPUT FILE OPEN
			if( ( fp = fopen( w_infilenm, "r" ) ) == NULL ){
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "�t�@�C���I�[�v���Ɏ��s���܂����B[FILE_NAME:%s]", w_infilenm ) ;
				continue;
			}

			sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "�����C�����t�@�C���̏������J�n���܂��B[%s]", w_infilenm );

			// ���C������
                        li_retSts = mainProc( fp );
                        if( li_retSts == RTN_NG ){
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "�������ɃG���[���������܂����B[FILE_NAME:%s]", w_infilenm ) ;
				if ( fp != NULL ) {
					fclose( fp );
				}
				/* �G���[�f�B���N�g���ֈړ� */
				sprintf( w_endfilenm, "%s/%s" , pAppEnv.cEndFileDirNG,  w_filenm );
				// �ύX�t�@�C���Ɠ����̃t�@�C�������݂��Ȃ���
				for( ;; ){
					if( open( w_endfilenm, O_RDONLY, 0 ) == EOF ){
						break;
					}
					strcat( w_endfilenm, "_" );
				}
				rename( w_infilenm, w_endfilenm );
				continue;
			}
			// INPUT FILE CLOSE
			fclose( fp );

			// �����σf�B���N�g���ֈړ�
			sprintf( w_endfilenm, "%s/%s" , pAppEnv.cEndFileDirOK,  w_filenm );
			// �ύX�t�@�C���Ɠ����̃t�@�C�������݂��Ȃ���
			for( ;; ){
				if( open( w_endfilenm, O_RDONLY, 0 ) == EOF ){
					break;
				}
				strcat( w_endfilenm, "_" );
			}
			rename( w_infilenm, w_endfilenm );

			sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "�t�@�C���������I�����܂����B[%s]", w_infilenm );
		}

		// LD101�X�^�[�g�g���K�[�̃t�@�C�����쐬
		if( ( fp = fopen( pAppEnv.cLockFile, "w" ) ) == NULL ){
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "���b�N�t�@�C���̍쐬�Ɏ��s���܂����B[%s]", pAppEnv.cLockFile ) ;
			continue;
		}
		fclose( fp );

	}

	return ( 0 ) ;
}

/******************************************************************************/
/*  �� �� ��  �FmainProc                                                      */
/*  �@�\�T�v  �F���ҏ��t�@�C������                                          */
/*  ��    ��  �F                                                              */
/*   ��P���� �F FILE   pfp     : ���̓t�@�C�����ʎq                          */
/*  �o    ��  �F �Ȃ�                                                         */
/*  ���A���  �F INT                                                          */
/*               RTN_OK     : ����                                            */
/*               RTN_NG     : ���s                                            */
/******************************************************************************/
int	mainProc( pfp )
FILE	*pfp;
{
	my_stFileKanjya		pInpFile;	/* �����C���t�@�C����� */
	my_stDbKanjya		pInpDB;		/* �����C���t�@�C����� DB�`���փR���o�[�g������� */
	my_stCHKZOK		*pChkZok;	/* �X�V�`�F�b�N�pDB���ҏ��     */

	char    rbuf[RECORDSIZE*2+1];		/* �ǂݍ��݃G���A */
	int 	li_retSts = 0;			/* �߂�l�`�F�b�N�p */
	int	i = 0;				/* �J�E���^ */
	int	rec_cnt = 0;			/* �������ʌ��� */
	int	cnt = 0;			/* �I�[�_�[�J�E���g���� */
	bool 	rui_flg = false;		/* �ݐϑΏۃ`�F�b�N�t���O */
	int 	intHkkhrKbn = 0;		/* �񍐕ۗ��敪 */

        /* ̧�ق̓Ǎ� */
        while( ReadFile( rbuf, pfp ) != EOF ){  // read while start ----------->
		/* ���R�[�h�T�C�Y�`�F�b�N */
		if( strlen( rbuf ) != ( RECORDSIZE )){
			// ERROR
			sFncPutLog( TRCKIND_ERROR, __FILE__, "mainProc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�ǂݍ��݃��R�[�h�T�C�Y�G���[[%d]", strlen( rbuf ));
			continue;
		}
		/* --------------------------------     */
		/*      ��������                        */
		/* --------------------------------     */
		memcpy( &pInpFile,	rbuf, sizeof( my_stFileKanjya ) );
		memset( &pInpDB,	0x00, sizeof( my_stDbKanjya ));
		pChkZok = NULL;
		rec_cnt = 0;
		cnt = 0;
		rui_flg = false;
		intHkkhrKbn = 0;

		/* �ҏW */
		li_retSts = EditPncKanjya( &pInpFile, &pInpDB );
		if ( li_retSts != RTN_OK ){
			sFncPutLog( TRCKIND_ERROR, __FILE__, "mainProc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "EditPncKanjya"  );
			break;
		}
		/* ���ʉӏ��̕ҏW */
		li_retSts = EditCommonKanjya( &pInpDB );
		if ( li_retSts != RTN_OK ){
			sFncPutLog( TRCKIND_ERROR, __FILE__, "mainProc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "EditCommonKanjya"  );
			break;
		}
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "�t�@�C���Ǎ��B[utkymd:%s irino:%s]", pInpDB.utkymd, pInpDB.irino );
		/* �����e�[�u������˗��A�����̗L���A�y�сA���݂��鍀�ڂƑ����̒l���擾 */
		li_retSts = sFncChkZok( pInpDB.utkymd, pInpDB.irino, &pChkZok, &rec_cnt);
		if ( li_retSts != RTN_OK ){
			sFncPutLog( TRCKIND_ERROR, __FILE__, "mainProc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "sFncChkZok"  );
			break;
		}
		/* �����Ɉ˗������݂��Ȃ��ꍇ�́A�ݐσe�[�u�����猋�ʂ̗L�����`�F�b�N */
		if( rec_cnt == 0) {
			li_retSts = sFncRuiChkZok( pInpDB.utkymd, pInpDB.irino, &pChkZok, &rec_cnt);
			if ( li_retSts != RTN_OK ){
				sFncPutLog( TRCKIND_ERROR, __FILE__, "mainProc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "sFncRuiChkZok"  );
				break;
			}
			if( rec_cnt > 0) {
				/* �ݐϏ��ɑ��݂��Ă����ꍇ�͓������֖߂� */
				li_retSts = sFncMoveRuiTou( pInpDB.utkymd, pInpDB.irino );
				if( li_retSts != RTN_OK ){
					sFncPutLog( TRCKIND_ERROR, __FILE__, "mainProc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "sFncMoveRuiTou"  );
					break;
				}
				sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "�ݐϕ��̏��𓖓����֖߂��܂����B[utkymd:%s irino:%s]", pInpDB.utkymd, pInpDB.irino );
				rui_flg = true;
			} else {
				/* �ݐςɂ��Ώۂ��Ȃ��ꍇ���� */
				sFncPutLog( TRCKIND_ERROR, __FILE__, "mainProc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
					    "���������݂��܂���B[utkymd:%s irino:%s]", pInpDB.utkymd, pInpDB.irino );
				continue;
			}
		}

		for ( i = 0; i < rec_cnt; i++ ){
			/* �˗��A������񂪎�ꂽ�ꍇ�A�v�Z�Ɏg�p���鑮�����ύX����Ă��邩�m�F */
			/* pChkZok �֑����̏C�����e�𔽉f������ */
			li_retSts  = chkUpdateKanjya( &pInpDB, &pChkZok[i] );
			if( li_retSts == RTN_NONE ){
				/* �Čv�Z�ΏۂȂ��B���̃��R�[�h�� */
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "�Čv�Z�ΏۂȂ��B[utkymd:%s irino:%s]", pInpDB.utkymd, pInpDB.irino );
				continue;
			}

			/* �Čv�Z�ΏۗL��B*/
			sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "�Čv�Z�ΏۗL�� [utkymd:%s irino:%s kmkcd:%s]", pChkZok[i].utkymd, pChkZok[i].irino, pChkZok[i].kmkcd );

			/* ��������UPDATE */
			li_retSts  = sFncUpdateKanjya( &pChkZok[i] );
			if( li_retSts != RTN_OK ){
				break;
			}
			intHkkhrKbn = 0;	/* �񍐕ۗ��敪 */
			/* �����G���[�`�F�b�N�m�F */
			li_retSts = ChkErrZok( &pChkZok[i] );
			if( li_retSts == RTN_OK ){
				/* �����G���[�����������ꍇ�A�Čv�Z�Ώۂ��̊m�F���s�� */
				if( rui_flg == true ) {
					/* �ߋ����������ꍇ�A�Čv�Z�Ώ� */
					intHkkhrKbn = MYAPP_HKKHR_CALC;
				} else {
					/* �������������ꍇ�A�I�[�_�[�o�͑O���ǂ����̊m�F */
					li_retSts  = sFncCntOrder( &pChkZok[i], &cnt );
					if( li_retSts != RTN_OK ){
						break;
					}
					if( cnt == 0) {
						/* �I�[�_�[�o�͑O�ł���΁A�C�����ꂽ�������Ɍv�Z�����̂ŕۗ����� */
						intHkkhrKbn = MYAPP_HKKHR_OK;
					} else {
						/* �I�[�_�[�o�͌�ł���΁A�Čv�Z�Ώ� */
						intHkkhrKbn = MYAPP_HKKHR_CALC;
					}
				}
			}else{
				/* �����G���[���������ꍇ�̓G���[���e�œo�^ */
				if( strcmp(pChkZok[i].scflg, MYAPP_ZOK_NG ) == 0 ||
				    strcmp(pChkZok[i].tjflg, MYAPP_ZOK_NG ) == 0 ||
				    strcmp(pChkZok[i].tjtniflg, MYAPP_ZOK_NG ) == 0 ||
				    strcmp(pChkZok[i].sbtkbnflg, MYAPP_ZOK_NG ) == 0 ||
				    strcmp(pChkZok[i].ageflg, MYAPP_ZOK_NG ) == 0 ||
				    strcmp(pChkZok[i].agekbnflg, MYAPP_ZOK_NG ) == 0 ) {
					intHkkhrKbn = MYAPP_HKKHR_NG ;
				}
			        else if( strcmp(pChkZok[i].scflg, MYAPP_ZOK_ERR ) == 0 ||
					 strcmp(pChkZok[i].tjflg, MYAPP_ZOK_ERR ) == 0 ||
					 strcmp(pChkZok[i].tjtniflg, MYAPP_ZOK_ERR ) == 0 ||
					 strcmp(pChkZok[i].sbtkbnflg, MYAPP_ZOK_ERR ) == 0 ||
					 strcmp(pChkZok[i].ageflg, MYAPP_ZOK_ERR ) == 0 ||
					 strcmp(pChkZok[i].agekbnflg, MYAPP_ZOK_ERR ) == 0 ) {
					intHkkhrKbn = MYAPP_HKKHR_ERR ;
				}
			}
			sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "�񍐕ۗ��t���O���X�V���܂��B[utkymd:%s, irino:%s, hkkhrKbn:%d]", pInpDB.utkymd, pInpDB.irino, intHkkhrKbn );
			/* �񍐕ۗ����̍X�V */
			li_retSts = InsHkHrIrai( &pChkZok[i], intHkkhrKbn );
			if( li_retSts != RTN_OK ){
				break;
			}

			ZdbCommit() ;
		}
	}
	return( RTN_OK );
}

/******************************************************************************/
/*  �� �� ��  �FReadFile							*/
/*  �@�\�T�v  �F�����t�@�C���ǂݍ���						*/
/*  ��    ��  �F                                                              */
/*   ��P���� �F char   file_nm[]	: ���̓t�@�C���|�C���^			*/
/*  �o    ��  �F char   rbuf[];		: �ǂݍ��݃o�b�t�@			*/
/*  ���A���  �F 0�ȏ�			: ����I��(�Ǎ��T�C�Y)			*/
/*               EOF			: FILE END				*/
/*               �ȊO			: ���s					*/
/******************************************************************************/
int	ReadFile( rbuf, pfp )
char		rbuf[];		/* ں��ޓǂݍ����ޯ̧ */
FILE		*pfp;		/* ̧�َ��ʎq */
{
	/* ��������     */
	memset( rbuf, 0x00, strlen( rbuf ));
	if( fgets( rbuf, RECORDSIZE + 1, pfp ) == NULL ){
		/* �ް��Ȃ�     */
		return( EOF );
	}

	return( strlen( rbuf ) );
}

/******************************************************************************/
/*  �� �� ��  �FchkUpdateKanjya                                               */
/*  �@�\�T�v  �F���ҏ��t�@�C������                                          */
/*  ��    ��  �F                                                              */
/*   ��P���� �F FILE   pfp     : ���̓t�@�C�����ʎq                          */
/*   ��Q���� �F int    stopValue : �I�����ʎq                                */
/*  �o    ��  �F �Ȃ�                                                         */
/*  ���A���  �F INT                                                          */
/*               RTN_OK     : ����                                            */
/*               RTN_NG     : ���s                                            */
/******************************************************************************/
int
chkUpdateKanjya( pInpDB, pChkZok )
my_stDbKanjya	*pInpDB ;
my_stCHKZOK	*pChkZok ;
{
	int	ret = RTN_NONE;
	char	sc_InpDB[6];
	char	sc_ChkZok[6];
	char	tj_InpDB[6];
	char	tj_ChkZok[6];
	char	age_InpDB[4];
	char	age_ChkZok[4];

	sFncTrim( sc_InpDB, pInpDB->sc );
	sFncTrim( sc_ChkZok, pChkZok->sc );
	sFncTrim( tj_InpDB, pInpDB->tj );
	sFncTrim( tj_ChkZok, pChkZok->tj );
	sFncTrim( age_InpDB, pInpDB->age );
	sFncTrim( age_ChkZok, pChkZok->age );

	if( strcmp( pChkZok->scflg, MYAPP_ZOK_CHK ) == 0 ){
		if( strcmp( sc_InpDB, sc_ChkZok ) != 0 ) {
			/* �X�V���e�𔽉f������ */
			strcpy( pChkZok->sc, pInpDB->sc ); 
			ret = RTN_OK;
		}
	}

	if( strcmp( pChkZok->tjflg, MYAPP_ZOK_CHK ) == 0 ){
		if( strcmp(tj_InpDB, tj_ChkZok ) != 0 ) {
			/* �X�V���e�𔽉f������ */
			strcpy( pChkZok->tj, pInpDB->tj ); 
			ret = RTN_OK;
		}
	}

	if( strcmp( pChkZok->tjtniflg, MYAPP_ZOK_CHK ) == 0 ){
		if( strcmp(pInpDB->tjtni, pChkZok->tjtni) != 0 ) {
			/* �X�V���e�𔽉f������ */
			strcpy( pChkZok->tjtni, pInpDB->tjtni ); 
			ret = RTN_OK;
		}
	}

	if( strcmp( pChkZok->sbtkbnflg, MYAPP_ZOK_CHK ) == 0 ){
		if( strcmp( pInpDB->sbtkbn, pChkZok->sbtkbn ) != 0 ) {
			/* �X�V���e�𔽉f������ */
			strcpy( pChkZok->sbtkbn, pInpDB->sbtkbn ); 
			ret = RTN_OK;
		}
	}

	if( strcmp( pChkZok->ageflg, MYAPP_ZOK_CHK ) == 0 ){
		if( strcmp( age_InpDB, age_ChkZok ) != 0 ) {
			/* �X�V���e�𔽉f������ */
			strcpy( pChkZok->age, pInpDB->age ); 
			ret = RTN_OK;
		}
	}

	if( strcmp( pChkZok->agekbnflg, MYAPP_ZOK_CHK ) == 0 ){
		if( strcmp( pInpDB->agekbn, pChkZok->agekbn ) != 0 ) {
			/* �X�V���e�𔽉f������ */
			strcpy( pChkZok->agekbn, pInpDB->agekbn ); 
			ret = RTN_OK;
		}
	}

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "sc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "chkUpdateKanjya,%s,%s,%s,%s,%s,", pChkZok->scflg, pChkZok->sc, pInpDB->sc, sc_ChkZok, sc_InpDB );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "tj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "chkUpdateKanjya,%s,%s,%s,%s,%s,", pChkZok->tjflg, pChkZok->tj, pInpDB->tj, tj_ChkZok, tj_InpDB );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "tjtni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "chkUpdateKanjya,%s,%s,%s,", pChkZok->tjtniflg, pChkZok->tjtni, pInpDB->tjtni );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "sbtkbn", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "chkUpdateKanjya.%s,%s,%s,", pChkZok->sbtkbnflg, pChkZok->sbtkbn, pInpDB->sbtkbn );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "age", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "chkUpdateKanjya,%s,%s,%s,%s,%s", pChkZok->ageflg, pChkZok->age, pInpDB->age, age_ChkZok, age_InpDB );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "agekbn", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "chkUpdateKanjya,%s,%s,%s,", pChkZok->agekbnflg, pChkZok->agekbn, pInpDB->agekbn );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FChkErrZok							*/
/*  �@�\�T�v  �F�����G���[�`�F�b�N�֐�						*/
/*  ��    ��  �F								*/
/*   ��P���� �Fstruct my_stCHKZOK  *pChkZok    : �����`�F�b�N���		*/
/*  �o    ��  �F�Ȃ�								*/
/*  ���A���  �FINT								*/
/*		RTN_OK     : ����						*/
/*		RTN_NG     : ���s						*/
/******************************************************************************/
int	ChkErrZok( pChkZok )
my_stCHKZOK	*pChkZok ;
{
	
	int	ret = RTN_OK;
	double	tmpNumDbl = 0.0;
	int	tmpNumInt = 0;

	if( strcmp( pChkZok->scflg, MYAPP_ZOK_CHK ) == 0 ){
		if( isCorrectChar( pChkZok->sc ) != RTN_OK || !strcmp(pChkZok->sc, "     ") ) {
			strcpy( pChkZok->scflg, MYAPP_ZOK_ERR );
			ret = RTN_NG;
		} else {
			tmpNumDbl = atof( pChkZok->sc );
			if( tmpNumDbl > pAppEnv.ScHi || tmpNumDbl < pAppEnv.ScLow ) {
				strcpy( pChkZok->scflg, MYAPP_ZOK_NG );
				ret = RTN_NG;
			}
		}
	}

	if( strcmp( pChkZok->tjflg, MYAPP_ZOK_CHK ) == 0 ){
		if( isCorrectChar( pChkZok->tj ) != RTN_OK || !strcmp(pChkZok->tj, "     ") ) {
			strcpy( pChkZok->tjflg, MYAPP_ZOK_ERR );
			ret = RTN_NG;
		} else {
			tmpNumDbl = atof( pChkZok->tj );
			if ( tmpNumDbl > pAppEnv.TjHi || tmpNumDbl < pAppEnv.TjLow ) {
				strcpy( pChkZok->tjflg, MYAPP_ZOK_NG );
				ret = RTN_NG;
			}
		}
	}

	if( strcmp( pChkZok->tjtniflg, MYAPP_ZOK_CHK ) == 0 ){
		if( strcmp( pChkZok->tjtni, "0" ) != 0 ) {
			strcpy( pChkZok->tjtniflg, MYAPP_ZOK_NG );
			ret = RTN_NG;
		}
	}

	if( strcmp( pChkZok->sbtkbnflg, MYAPP_ZOK_CHK ) == 0 ){
		if( strcmp( pChkZok->sbtkbn, "0" ) != 0 && strcmp( pChkZok->sbtkbn , "1" ) != 0 ) {
			strcpy(pChkZok->sbtkbnflg, MYAPP_ZOK_ERR );
			ret = RTN_NG;
		}
	}

	if( strcmp( pChkZok->ageflg, MYAPP_ZOK_CHK ) == 0 ){
		if( isCorrectChar( pChkZok->age ) != RTN_OK || !strcmp( pChkZok->age , "   ") ) {
			strcpy( pChkZok->ageflg, MYAPP_ZOK_ERR );
			ret = RTN_NG;
		} else {
			tmpNumInt = atoi( pChkZok->age );
			if( tmpNumInt > pAppEnv.AgeHi || tmpNumInt < pAppEnv.AgeLow ) {
				strcpy( pChkZok->ageflg, MYAPP_ZOK_NG );
				ret = RTN_NG;
			}
		}
	}

	if( strcmp( pChkZok->agekbnflg, MYAPP_ZOK_CHK ) == 0 ){
		if( strcmp( pChkZok->agekbn , "Y" ) != 0 ){
			strcpy(pChkZok->agekbnflg, MYAPP_ZOK_NG );
			ret=RTN_NG;
		}
	}
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "ChkErrZok", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "utkymd[%s] irino[%s] kmkcd[%s] sc[%s] tj[%s] tjtni[%s] sbtkbn[%s] age[%s] agekbn[%s] ret[%d]", 
			pChkZok->utkymd, pChkZok->irino, pChkZok->kmkcd, pChkZok->sc, pChkZok->tj, pChkZok->tjtni, pChkZok->sbtkbn, pChkZok->age, pChkZok->agekbn, ret ) ;
	return(ret);
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
	struct  stat    statbuf;                                // get input file status

	// �f�B���N�g���͏���
	sprintf( w_fnm, "%s/%s", pAppEnv.cInputDir, namelist->d_name );
	stat( w_fnm, &statbuf );
	if( S_ISDIR( statbuf.st_mode )){
		// �ΏۊO
		return( 0 );
	}
	// �Ώۃt�@�C���̐擪�ɂ�锻�f
	if(( strcmp( pAppEnv.cFilePrx, "" ) != 0 )
 	 &&( memcmp( namelist->d_name, pAppEnv.cFilePrx , strlen( pAppEnv.cFilePrx )) == 0 )){
		// OK
		return( 1 );
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
	/*	���b�N�t�@�C���폜 */
	remove( pAppEnv.cLockFile );

	/*	�f�[�^�x�[�X�N���[�Y */
	ZdbDisConnect() ;

	/*	���L�������폜	*/
	sFncShmDel () ;

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
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmget", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "���L�������̑���Ɏ��s���܂���" ) ;
		return ( -1 ) ;
	}

	//	�A�^�b�`	
	shmData = ( int * ) shmat ( pAppEnv.shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	�ُ�I��	LOG
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
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
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
int					*pshmData ;
{
	int		*shmData ;

	//	�A�^�b�`	
	shmData = ( int * ) shmat ( pAppEnv.shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	�ُ�I��	LOG
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
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "���L�������̑���Ɏ��s���܂���" ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/********************************************************************************/
/*  �� �� ���@�FsFncShmDel()							*/
/*  �@�\�T�v�@�F���L�������폜							*/
/*  ���@�@�́@�F                                                                */
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
	endFunction() ;

	exit ( 0 ) ;
}
/** End of File ***************************************************************/
