/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��  							*/
/*                             							*/
/* �@�V�X�e�����F������V�X�e��							*/
/* �@�t�@�C�����FND101.c              						*/
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

#include "ND101.h"

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
static	int	sFncShmGet ( int *) ;
static	int	sFncShmDel() ;


//	���̑�
static	int     FileFilter( struct dirent *namelist );
static	void	endFunction();

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
	//      �����X�L�b�v�t�@�C���ړ��f�B���N�g��
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DIR_SKIP, pAppEnv.cEndFileDirSKIP ) != 0 ) {
		//      �ُ�I��        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_SKIP ) ;
		return ( -1 ) ;
	}
	//      �����Ώۃt�@�C���g���q
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_FILE_EXT, pAppEnv.cFileExt ) != 0 ) {
		//      �ُ�I��        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_FILE_EXT ) ;
		return ( -1 ) ;
	}
	//      �X�L�b�v�t�@�C���ړ���
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_SKIP_FILE_PRE, pAppEnv.cSkipFilePre ) != 0 ) {
		//      �ُ�I��        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_SKIP_FILE_PRE ) ;
		return ( -1 ) ;
	}
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_FILE_EXT_TRG, pAppEnv.cFileExtTrg ) != 0 ) {
		//      �ُ�I��        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_FILE_EXT_TRG ) ;
		return ( -1 ) ;
	}

	//	�p�����[�^�t�@�C���N���[�Y	
	ZbmlPrmClose ( pAppEnv.bp ) ;

	/***
	 ***	���L����������	
	 ***/
	if ( sFncShmCrt ( ) < 0 ) {
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
int mainFunction()
{
	int	li_retSts = 0;
	int	li_stopFlg = 0;

	int	i = 0;
	char	*p;				// ��Ɨp�̕�����|�C���^
	int	file_cnt = 0;
	int	ins_row_cnt = 0;
	bool	flg_skip_file = 0;		// �����t�@�C�����X�L�b�v�t�@�C�����ǂ���(0:�ʏ� 1:�X�L�b�v�t�@�C��)
	char	w_filenm[256];			// �����t�@�C����(�g���q������)
	char	w_filenm_trg[256];		// �g���K�[�t�@�C����(�t���p�X)
	char	w_infilenm[256];		// �����O�t�@�C����(�t���p�X)
	char	w_endfilenm[256];		// �����I���t�@�C����(�t���p�X)
	struct	dirent  **namelist;		// get input file
	FILE	*fp;				// �Ǎ�̧���߲��

	/*	�i�v���[�v ��~�R�}���h�ŏI�� */
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
				     "�t�����e�B�A���b�N���t�@�C���̎擾(scandir)�Ɏ��s���܂����B") ;
                        continue;
                }
                // �擾�����Ώۃt�@�C�������[�v
		for( i=0; i < file_cnt; i++ ){
			strcpy( w_filenm, namelist[i]->d_name );
			// scadir�t�@�C������free
			free( namelist[i] );
			// �X�L�b�v�t�@�C�����ǂ�����ړ���Ŕ��f
			if( strncmp( pAppEnv.cSkipFilePre, w_filenm , strlen( pAppEnv.cSkipFilePre) ) == 0 ) {
				flg_skip_file = 1; // �X�L�b�v�t�@�C��
			} else {
				flg_skip_file = 0; // �ʏ�t�@�C��
			}
			// �g���q�̍폜
			p = strrchr( w_filenm, '.' );
			if ( p != NULL ) {
				*p = 0x00;
			}
			// �t�@�C�����쐬
			memset( w_infilenm,  '\0',sizeof( w_infilenm ));
			memset( w_endfilenm, '\0',sizeof( w_endfilenm ));
			sprintf( w_infilenm, "%s/%s%s", pAppEnv.cInputDir, w_filenm, pAppEnv.cFileExt );

			sFncPutLog ( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				     "�t�@�C�������J�n[%s]", w_infilenm ) ;
			// FILE OPEN
			if( ( fp = fopen( w_infilenm, "r" ) ) == NULL ){
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "�t�@�C���I�[�v���Ɏ��s���܂����B[FILE_NAME:%s]", w_infilenm ) ;
				continue;
			}
			// ���C������
			li_retSts = mainProc( fp, flg_skip_file, &ins_row_cnt );
			// FILE CLOSE
			fclose( fp );
			// �����σt�@�C�����̎擾
			if ( li_retSts == RTN_OK ){
				// �����t�@�C�����X�L�b�v�t�@�C���ŁA����ɃX�L�b�v����ꍇ�́A�t�@�C�����ړ����Ď��̃t�@�C������������B
				if( flg_skip_file == 1 && ins_row_cnt == 0 ){
					sprintf( w_endfilenm, "%s/%s%s", pAppEnv.cEndFileDirSKIP, w_filenm, pAppEnv.cFileExt );
					if ( rename( w_infilenm, w_endfilenm ) == 0) {
						sFncPutLog ( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
							     "�t�@�C���X�L�b�v[%s]", w_endfilenm ) ;
					} else {
						sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
							     "�t�@�C���X�L�b�v���s[%s]", w_infilenm ) ;
					}
					continue;
				} else {
					li_retSts = sFncMakeEndFileName( pAppEnv.cEndFileDirOK, w_filenm, pAppEnv.cFileExt, w_endfilenm ) ;
				}
			} else {
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"�������ɃG���[���������܂����B[FILE_NAME:%s]", w_infilenm ) ;
				li_retSts = sFncMakeEndFileName( pAppEnv.cEndFileDirNG, w_filenm, pAppEnv.cFileExt, w_endfilenm ) ;
			}
			// �t�@�C�����̎擾���s
			if ( li_retSts != RTN_OK ){
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "�t�@�C�����̎擾�Ɏ��s���܂����B[%s]", w_infilenm );
				continue;
			}
			// �t�@�C�����ύX
			if ( rename( w_infilenm, w_endfilenm ) != 0) {
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "�t�@�C���̈ړ��Ɏ��s���܂����B[%s]->[%s]:%s", w_infilenm , w_endfilenm, strerror(errno) );
				continue;
			}
			// �ʏ�t�@�C���̏ꍇ�A�g���K�[�t�@�C�������݂���̂ō폜����B
			if( flg_skip_file == 0 ) {
				sprintf( w_filenm_trg, "%s/%s%s", pAppEnv.cInputDir, w_filenm, pAppEnv.cFileExtTrg );
				if ( remove( w_filenm_trg ) != 0 ) {
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						     "�g���K�[�t�@�C���̍폜�Ɏ��s���܂����B[%s]", w_filenm_trg );
				}
			}
			sFncPutLog ( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				     "�t�@�C�������I��[%s%s] ���R�[�h��[%d]", w_filenm, pAppEnv.cFileExt, ins_row_cnt ) ;
		}
		sleep( 1 );
	}
	return ( RTN_OK ) ;
}

/******************************************************************************/
/*  �� �� ��  �FmainProc                                                      */
/*  �@�\�T�v  �F�t�@�C������                                                  */
/*  ��    ��  �F                                                              */
/*   ��P���� �F FILE	*pfp		: ���̓t�@�C�����ʎq                  */
/*   ��Q���� �F bool	flg_skip_file	: �X�L�b�v�t�@�C�����ǂ���            */
/*  �o    ��  �F �Ȃ�                                                         */
/*   ��R���� �F int	*rowCnt		: �����s��                            */
/*  ���A���  �F INT                                                          */
/*               RTN_OK     : ����                                            */
/*               RTN_NG     : ���s                                            */
/******************************************************************************/
int	mainProc( pfp, flg_skip_file, ins_row_cnt )
FILE	*pfp;
bool	 flg_skip_file;
int	*ins_row_cnt;
{
	/* �˗���M */
	my_stFileFRONRACK	pFileFronRack;	/* �t�@�C�����R�[�h��� */
	my_stDbFRONRACK		*recFronRack;	/* �t�����e�B�A���b�N��� */

	char    rbuf[MYAPP_RECORD_SIZE+1];		/* �ǂݍ��݃G���A */
	char    tmp_rbuf[MYAPP_RECORD_SIZE+1];		/* �ǂݍ��݃G���A */
	int 	li_retSts = 0;
	int 	i = 0;
	int 	recCnt = 0;
	int	rowCnt = 0;

	/* �t�@�C���̓Ǎ� */
	while( fgets( rbuf, MYAPP_RECORD_SIZE+1, pfp ) != NULL ) {  // read while start ----------->
		/* �X�L�b�v�t�@�C���o�͗p�Ɍ��̕������ޔ����� */
		strcpy( tmp_rbuf, rbuf );
		memset( &pFileFronRack, '\0', sizeof(pFileFronRack) );
		/* �t�@�C�����R�[�h���擾���� */
		li_retSts = sFncGetFileRecord( rbuf, &pFileFronRack );
		if( li_retSts != RTN_OK ){
			goto error;
		}
		/* �d�m�c��񃌃R�[�h�������ꍇ�A�d�m�c����Insert���� */
		if ( strncmp ( pFileFronRack.hkkbn, MYAPP_RECORD_END, strlen( MYAPP_RECORD_END ) ) == 0 ){
			li_retSts = sFncInsEnd( pFileFronRack.sriymd, pFileFronRack.asyrckid, pFileFronRack.hkkbn );
			if( li_retSts != RTN_OK ){
				goto error;
			}
			rowCnt++;
			continue;
		}
		/* �I�[�_�[��񂩂�K�v�ȏ����擾���� */
		li_retSts = sFncSelKenOrder( pFileFronRack.sriymd, pFileFronRack.asyrckid, pFileFronRack.hkkbn, &recFronRack, &recCnt );
		if( li_retSts != RTN_OK ){
			goto error;
		}
		/* �擾���R�[�h�� */
		if( recCnt == 0 ){
			/* �I�[�_�[��񂪑��݂����A���t�@�C�����X�L�b�v�t�@�C���ł͂Ȃ��ꍇ�A�X�L�b�v�t�@�C�����쐬���� */
			if( flg_skip_file == 0 ){
				li_retSts = sFncMakeSkipFile( pFileFronRack.sriymd, pFileFronRack.asyrckid, tmp_rbuf );
				if( li_retSts != RTN_OK ){
					goto error;
				}
			}
		} else {
			for ( i = 0; i < recCnt; i++ ){
				/* �t�����e�B�A���b�N����Insert���� */
				li_retSts = sFncInsFronRack( &recFronRack[i] );
				if( li_retSts != RTN_OK ){
					goto error;
				}
			}
			/* �t�����e�B�A���b�N���֓o�^�ł������R�[�h�����J�E���g���� */
			rowCnt++;
		}
	}
	/* �t�@�C���ǂݍ��ݒ��ɃG���[���������Ă��Ȃ����`�F�b�N */
	if ( feof( pfp ) == 0 ){
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			     "�t�@�C���ǂݍ��ݒ��ɃG���[���������Ă��܂��B");
		goto error;
	}

	ZbmlFree( recFronRack );

	/* �r���ŃG���[���������Ȃ������ꍇ�̓R�~�b�g */
	ZdbCommit();

	*ins_row_cnt = rowCnt;

	return( RTN_OK );
error:
	/* �r���ŃG���[�����������ꍇ�̓��[���o�b�N */
	ZdbRollback();

	return( RTN_NG );
}

/******************************************************************************/
/*  �� �� ��  �FsFncGetFileRecord                                             */
/*  �@�\�T�v  �F�t�@�C�����R�[�h�擾                                          */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fchar *          �t�@�C�����R�[�h���                          */
/*   ��Q���� �Fstruct *        �\����                                        */
/*  �o    ��  �F�Ȃ�                                                          */
/*  ���A���  �F INT                                                          */
/*               0              : ����I��                                    */
/*              -1              : �ُ�I��                                    */
/******************************************************************************/
int sFncGetFileRecord(buff, pFronRack)
char			*buff;
my_stFileFRONRACK	*pFronRack;
{
	char	*pFld[128];
	int	cnt;
	int	offset;
	char	tmpSriymd[8+1];

	memset( pFld, '\0', sizeof( pFld ) );
	/* �J���}��؂�̃��R�[�h�𕪊����ADB���R�[�h�̍\���̂ɐݒ肷��B */
	cnt = 0;
	offset = 0;;
	pFld[cnt] = &buff[cnt];
	while (buff[offset] != '\0') {
		if (buff[offset] == ',') {
			buff[offset] = '\0';
			cnt++;
			pFld[cnt] = &buff[offset+1];
		}
		if (buff[offset] == '\n') {
			buff[offset] = '\0';
		}
		offset++;
	}

	/* �t�B�[���h���`�F�b�N�B�ʏ탌�R�[�h���d�m�c��񂩂Ń`�F�b�N��ς���B */
	if ( strncmp (pFld[1], MYAPP_RECORD_END, strlen( MYAPP_RECORD_END ) ) == 0 ){
		if (cnt == 2) {
			sFncPutLog ( TRCKIND_TRACE, __FILE__, "sFncGetFileRecord", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				     "�d�m�c������M���܂����B" ) ;
		} else {
			/* �t�B�[���h������v���Ȃ� */
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncGetFileRecord", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "�t�@�C���̃t�B�[���h�������v���܂���B[%d]", cnt ) ;
			return -1;
		}
		memset( pFronRack->irino, '\0', sizeof( pFronRack->irino ) );
	} else {
		if (cnt != 3) {
			/* �t�B�[���h������v���Ȃ� */
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncGetFileRecord", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "�t�@�C���̃t�B�[���h�������v���܂���B[%d]", cnt ) ;
			return -1;
		}
		strncpy( pFronRack->irino, pFld[3], sizeof( pFronRack->irino )-1 );
	}

	/* �e�t�B�[���h���i�[����B */
	strncpy( tmpSriymd, pFld[0], sizeof( tmpSriymd )-1 );
	sprintf( pFronRack->sriymd, "%4.4s-%2.2s-%2.2s", tmpSriymd, &tmpSriymd[4], &tmpSriymd[6]);
	strncpy( pFronRack->hkkbn, pFld[1], sizeof( pFronRack->hkkbn )-1 );
	strncpy( pFronRack->asyrckid, pFld[2], sizeof( pFronRack->asyrckid )-1 );     /* ���b�NID */

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

	// �Ώۃt�@�C���̊g���q�ɂ�锻�f(�g���K�[�t�@�C��)
	w_fext = strrchr( namelist->d_name, '.' ) ;

	if( strcmp( w_fext, pAppEnv.cFileExtTrg ) == 0 ){
		// OK
		return ( 1 );
	}

	// �X�L�b�v�t�@�C���̏ꍇ�̓g���K�[�t�@�C���͑��݂��Ȃ����߁A�f�[�^�t�@�C����Ԃ��B
	if( strncmp( pAppEnv.cSkipFilePre, namelist->d_name, strlen( pAppEnv.cSkipFilePre ) ) == 0 ) {
		if( strcmp( w_fext, pAppEnv.cFileExt ) == 0 ){
			// OK
			return ( 1 );
		}
	}
	return ( 0 );
}

/******************************************************************************/
/*  �� �� ��  �FsFncMakeEndFileName                                           */
/*  �@�\�T�v  �F�I���t�@�C�����̍쐬                                          */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fchar *          �쐬�f�B���N�g��                              */
/*   ��Q���� �Fchar *          �t�@�C����(�g���q����)                        */
/*   ��R���� �Fchar *          �g���q                                        */
/*  �o    ��  �F                                                              */
/*   ��S���� �Fchar *          �t�@�C����(�t���p�X)                          */
/*  ���A���  �F INT                                                          */
/*               0              : ����I��                                    */
/*              -1              : �ُ�I��                                    */
/******************************************************************************/
int sFncMakeEndFileName( pDirName, pFileNameBase, pFileNameExt, pEndFileName )
char	*pDirName;
char	*pFileNameBase;
char	*pFileNameExt;
char	*pEndFileName;
{
	int	cnt = 0;
	
	sprintf( pEndFileName, "%s/%s%s", pDirName, pFileNameBase, pFileNameExt );

	// �ύX�t�@�C���Ɠ����̃t�@�C�������݂��Ȃ���
	for( ;; ){
		if( open( pEndFileName, O_RDONLY, 0 ) == EOF ){
			break;
		}
		cnt++;
		sprintf ( pEndFileName, "%s/%s_%d%s", pDirName, pFileNameBase, cnt , pFileNameExt);
	}

	return ( RTN_OK );
}

/******************************************************************************/
/*  �� �� ��  �FsFncMakeSkipFile                                              */
/*  �@�\�T�v  �F�X�L�b�v�t�@�C���o��                                          */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fchar *          ������(�t�@�C�����ݒ�p)                      */
/*   ��Q���� �Fchar *          �A�b�Z�C���b�N�h�c(�t�@�C�����ݒ�p)          */
/*   ��R���� �Fchar *          �t�@�C�����R�[�h���                          */
/*  �o    ��  �F�Ȃ�                                                          */
/*  ���A���  �F INT                                                          */
/*               0              : ����I��                                    */
/*              -1              : �ُ�I��                                    */
/******************************************************************************/
int sFncMakeSkipFile( pSriymd, pAsyrckid, fileRecord )
char	*pSriymd ;
char	*pAsyrckid ;
char	*fileRecord ;
{
	int	li_retSts = 0;
	char	w_filenm_base[256];		// �����t�@�C����(�g���q������)
	char	w_filenm[256];			// �����t�@�C����(�t���p�X)
	FILE	*fp;				/* �X�L�b�v�t�@�C���o�͗p */

	sprintf( w_filenm_base, "%s_%4.4s%2.2s%2.2s_%s", pAppEnv.cSkipFilePre, pSriymd, &pSriymd[5], &pSriymd[8], pAsyrckid );
	li_retSts = sFncMakeEndFileName( pAppEnv.cEndFileDirSKIP, w_filenm_base, pAppEnv.cFileExt, w_filenm );
	if( li_retSts != RTN_OK ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncMakeSkipFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "�X�L�b�v�t�@�C�����̎擾�Ɏ��s���܂����B[SRIYMD:%s ASYRCKID:%s]", pSriymd, pAsyrckid ) ;
		return( RTN_NG );
	}

	if( ( fp = fopen( w_filenm, "w" ) ) == NULL ){
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncMakeSkipFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "�X�L�b�v�t�@�C���I�[�v���Ɏ��s���܂����B[FILE_NAME:%s]", w_filenm ) ;
		return( RTN_NG );
	}

	if( fputs( fileRecord, fp ) < 0 ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncMakeSkipFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "�X�L�b�v�t�@�C���̏o�͂Ɏ��s���܂����B[FILE_NAME:%s]", w_filenm ) ;
		return( RTN_NG );
	}
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "sFncMakeSkipFile", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			     "�X�L�b�v�t�@�C�����o�͂��܂����B[FILE_NAME:%s]", w_filenm ) ;
	fclose( fp );

	return ( RTN_OK );
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
	pAppEnv.shm_Id = shmget ( (key_t)pAppEnv.shm_Key, MYAPP_SHM_SIZE, 0666 | IPC_CREAT ) ;
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

	exit( 0 );
}
/** End of File ***************************************************************/
