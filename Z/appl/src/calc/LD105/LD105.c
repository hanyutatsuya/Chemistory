/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��  							*/
/*                             							*/
/* �@�V�X�e�����F������V�X�e��							*/
/* �@�t�@�C�����FLD105.c              						*/
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

#include "bmllog.h"
#include "bmlprm.h"
#include "bml_misc.h"
#include "bml_date.h"

#include "sql.h"

#include "LD105.h"

/******************************************************************************/
/* Define��`                                                                 */
/******************************************************************************/
//	TRACE
#if defined ( _TRACE )
#define malloc(a)   _malloc(a, __FILE__, __LINE__)
#define free(p)     _free(p, __FILE__, __LINE__)
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
	//      �����Ώۃt�@�C���v���t�B�b�N�X
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_FILE_PRX, pAppEnv.cFilePrx ) != 0 ) {
		//      �ُ�I��        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_FILE_PRX ) ;
		return ( -1 ) ;
	}
	//      ���b�N�t�@�C��
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_LOCK_FILE, pAppEnv.cLockFile ) != 0 ) {
		//      �ُ�I��        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_LOCK_FILE ) ;
		return ( -1 ) ;
	}
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
	if ( sFncShmCrt ( pAppEnv ) < 0 ) {
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

	char	w_infilenm[256];	// �����O�t�@�C����(�t���p�X)
	char	w_endfilenm[256];	// �����I���t�@�C����(�t���p�X)
	char	w_filenm[256];		// �����I���t�@�C����
	struct	dirent  **namelist;	// get input file
	FILE	*fp;			// �Ǎ�̧���߲��

	my_stSYSKNR     pSysKnr;        //

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
			if ( sFncSelSysKnr( &pSysKnr ) !=  RTN_OK ){
				return( RTN_NG );
			}
			// �����d�m�c�����Ă���ꍇ�A���������̊J�n�`�F�b�N���s��
			if ( strcmp( pSysKnr.bchendflg, "1" ) == 0 ){
				/* �����������n�܂��Ă�����I�� */
				if( strcmp( pSysKnr.unyflg, "1" ) == 0 ) {
					sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						     "���������̊J�n���m�F���܂����B");
					return( RTN_OK );
				}
			}
		}

                // �Ώۃt�@�C���̎擾
                file_cnt = scandir( pAppEnv.cInputDir, &namelist, (void*)FileFilter, alphasort);
                if ( file_cnt < 0){
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "���T�e���C�g���ʏ��t�@�C���̎擾(scandir)�Ɏ��s���܂����B") ;
                        continue;
                }

		for( i=0; i < file_cnt; i++ ){
			sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				     "�t�@�C�������J�n [%s]", namelist[i]->d_name ) ;
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

			// ���C������
			li_retSts = mainProc( fp , &li_stopFlg);
			if( li_retSts == RTN_NG ){
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"�������ɃG���[���������܂����B[FILE_NAME:%s]", w_infilenm ) ;
			}

			// INPUT FILE CLOSE
			fclose( fp );

			// �����σt�@�C���̖��̕ύX
			// �ύX�t�@�C�����쐬
			if ( li_stopFlg == RTN_OK ){
				sprintf( w_endfilenm, "%s/%s" , pAppEnv.cEndFileDirOK,  w_filenm );
			} else {
				sprintf( w_endfilenm, "%s/%s" , pAppEnv.cEndFileDirNG,  w_filenm );
			}
			// �ύX�t�@�C���Ɠ����̃t�@�C�������݂��Ȃ���
			for( ;; ){
				if( open( w_endfilenm, O_RDONLY, 0 ) == EOF ){
					break;
				}
				strcat( w_endfilenm, "_" );
                        }

			// �t�@�C�����ύX
			if ( rename( w_infilenm, w_endfilenm ) != 0) {
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					     "�t�@�C���̈ړ��Ɏ��s���܂����B[%s]->[%s]:%s", w_infilenm , w_endfilenm, strerror(errno) );
				continue;
			}
			sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				     "�t�@�C�������I�� [%s]", namelist[i]->d_name ) ;
		}
		// ���b�N�̃t�@�C�����쐬
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
/*  �@�\�T�v  �F���T�e���C�g���ʏ��t�@�C������                              */
/*  ��    ��  �F                                                              */
/*   ��P���� �F FILE   pfp     : ���̓t�@�C�����ʎq                          */
//   ��2 ���� :  int    errValue : �G���[���ʎq                               */�@
/*  �o    ��  �F �Ȃ�                                                         */
/*  ���A���  �F INT                                                          */
/*               RTN_OK     : ����                                            */
/*               RTN_NG     : ���s                                            */
/******************************************************************************/
int	mainProc( pfp , errValue)
FILE	*pfp;
int	*errValue;
{
	/* �˗���M */
	my_stFileOTHERKKA	file_kka;	/*  */
	my_stDbOTHERKKA		db_kka;		/* ���ʏ��	*/

	char    rbuf[RECORDSIZE*2+1];          /* �ǂݍ��ݴر          */
	int 	li_retSts = 0;

        /* ̧�ق̓Ǎ� */
        while( ReadFile( rbuf, pfp ) != EOF ){  // read while start ----------->

		/* ���R�[�h�T�C�Y�`�F�b�N */
		if( strlen( rbuf ) != ( RECORDSIZE )){
			// ERROR
			*errValue = RTN_NG;
			sFncPutLog( TRCKIND_ERROR, __FILE__, "mainProc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�ǂݍ��݃��R�[�h�T�C�Y�G���[[%d]", strlen( rbuf ));
			continue;
		}
		/* �w�b�_��ǂݔ�΂� */
		if( strncmp( rbuf, "HD", 2 ) == 0 ){
			continue;
		}
		/* �g���[���[��ǂݔ�΂� */
		if( strncmp( rbuf, "TR", 2 ) == 0 ){
			continue;
		}
		
		/* --------------------------------	*/
		/*	���� 							*/
		/* --------------------------------	*/
		memcpy( &file_kka,	rbuf, sizeof( my_stFileOTHERKKA ));
		memset( &db_kka,	0x00, sizeof( my_stDbOTHERKKA ));
		if (file_kka.kkajkcd[0] == '3'){
			/* �ҏW */
			li_retSts = EditKekka( &file_kka, &db_kka );
			if (li_retSts != RTN_OK ){
				*errValue = RTN_NG;
				continue;
			}
			/* ���T�e���C�g���ʏ���Insert���� */
			li_retSts = sFncInsKekka( &db_kka );
			if( li_retSts != RTN_OK ){
				*errValue = RTN_NG;
				continue;
			}
		}
	}

	return( RTN_OK );
}


/******************************************************************************/
/*  �� �� ��  �FReadFile                                                      */
/*  �@�\�T�v  �F�t�@�C���ǂݍ���                                              */
/*  ��    ��  �F                                                              */
/*   ��P���� �F char	file_nm[]	: ���̓t�@�C���|�C���^                */
/*  �o    ��  �F char	rbuf[];		: �ǂݍ��݃o�b�t�@                    */
/*  ���A���  �F 0�ȏ�			: ����I��(�Ǎ��T�C�Y)                */
/*               EOF			: FILE END                            */
/*               �ȊO			: ���s                                */
/******************************************************************************/
int     ReadFile( rbuf, pfp )
char		rbuf[];				/* ں��ޓǂݍ����ޯ̧ */
FILE		*pfp;				/* ̧�َ��ʎq */
{
 	char    func_nm[MYAPP_LEN_FNCNM+1];	/* �֐�����     */

 	/* ��������     */
 	strcpy( func_nm, "ReadFile" );

	memset( rbuf, 0x00, sizeof( rbuf ));
	if( fgets( rbuf, FILE_RECSIZE + 1, pfp ) == NULL ){
		/* �ް��Ȃ�	*/
		return( EOF );
	}
	return( strlen( rbuf ) );
}

/******************************************************************************/
/*  �� �� ��  �FEditKekka                                                     */
/*  �@�\�T�v  �F���ʏ��ҏW ���@�`�F�b�N                                     */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct	my_stFileOTHERKKA  *file_kka;   : PNC�˗����         */
/*  �o    ��  �F                                                              */
/*   ��Q���� �Fstruct	my_stDbOTHERKKA    *db_kka;     : ���ʏ��            */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int     EditKekka( file_kka, db_kka )
my_stFileOTHERKKA	*file_kka;	/* �t�@�C�����  */
my_stDbOTHERKKA		*db_kka;	/* ���ʏ��\���� */
{
	//=========================================
	//  EDIT
	//=========================================
	// 1 �a�l�k��t�N����
	sprintf( db_kka->utkymd,	"%.4s-%.2s-%.2s",	file_kka->utkymd, &file_kka->utkymd[4], &file_kka->utkymd[6] );
	// 2 �˗����m��
	sprintf( db_kka->irino,		"00%-3.3s%-6.6s",	file_kka->irino, &file_kka->irino[5] );
	// 3 ���ڃR�[�h
	memcpy( db_kka->kmkcd,		file_kka->kmkcd,	sizeof( file_kka->kmkcd ));
	// 4 ������
	sprintf( db_kka->sriymd,	"%.4s-%.2s-%.2s",	file_kka->sriymd, &file_kka->sriymd[4], &file_kka->sriymd[6] );
	// 5 ���̂m��
	sprintf( db_kka->kntno,		"00%-3.3s%-6.6s",	file_kka->kntno, &file_kka->kntno[5] );
	// 6 �`�F�b�N����
	memcpy( db_kka->chkmj,		file_kka->chkmj,	sizeof( file_kka->chkmj ));
	// 7 ����ޗ��R�[�h
	memcpy( db_kka->stzrcd,		file_kka->stzrcd,	sizeof( file_kka->stzrcd ));
	// 8 ���ڗ���
	memcpy( db_kka->kmkrs,		file_kka->kmkrs,	sizeof( file_kka->kmkrs ));
	// 9 �e���ڃR�[�h
	memcpy( db_kka->oyakmkcd,	file_kka->oyakmkcd,	sizeof( file_kka->oyakmkcd ));
	// 10 �Z�N�V�����R�[�h
	memcpy( db_kka->seccd,		file_kka->seccd,	sizeof( file_kka->seccd ));
	// 11 ���敉�׋敪
	memcpy( db_kka->bkfkkbn,	file_kka->bkfkkbn,	sizeof( file_kka->bkfkkbn ));
	// 12 �������{���{�R�[�h
	memcpy( db_kka->knsjslbcd,	file_kka->knslabcd,	sizeof( file_kka->knslabcd ));
	// 13 ���ʏ󋵃R�[�h
	memcpy( db_kka->kkajkcd,	file_kka->kkajkcd,	sizeof( file_kka->kkajkcd ));
	// 14 �p�j�b�N�����W�t���O
	memcpy( db_kka->pncrgflg,	file_kka->pncrgflg,	sizeof( file_kka->pncrgflg ));
	// 15 ���ʊ��Z�t���O
	memcpy( db_kka->kkaksflg,	file_kka->kkaksflg,	sizeof( file_kka->kkaksflg ));
	// 16 ���ʏC���t���O
	memcpy( db_kka->kkassflg,	file_kka->kkassflg,	sizeof( file_kka->kkassflg ));
	// 17 �������ʂP
	memcpy( db_kka->knskka1,	file_kka->knskka1,	sizeof( file_kka->knskka1 ));
	// 18 �������ʂQ
	memcpy( db_kka->knskka2,	file_kka->knskka2,	sizeof( file_kka->knskka2 ));
	// 19 �������ʂQ�敪
	memcpy( db_kka->knskka2kbn,	file_kka->knskka2kbn,	sizeof( file_kka->knskka2kbn ));
	// 20 ���ʕ⑫�R�[�h
	memcpy( db_kka->kkahskcd,	file_kka->kkahskcd,	sizeof( file_kka->kkahskcd ));
	// 21 ���ʃR�����g�P
	memcpy( db_kka->kkacmt1,	file_kka->kkacmt1,	sizeof( file_kka->kkacmt1 ));
	// 22 ���ʃR�����g�Q
	memcpy( db_kka->kkacmt2,	file_kka->kkacmt2,	sizeof( file_kka->kkacmt2 ));
	// 23 �ُ�l�敪�i�j�j
	memcpy( db_kka->ijkbnm,		file_kka->ijkbnm,	sizeof( file_kka->ijkbnm ));
	// 24 �ُ�l�敪�i���j
	memcpy( db_kka->ijkbnf,		file_kka->ijkbnf,	sizeof( file_kka->ijkbnf ));
	// 25 �ُ�l�敪�i�s�� 
	memcpy( db_kka->ijkbnn,		file_kka->ijkbnn,	sizeof( file_kka->ijkbnn ));
	// 26 �w��
	memcpy( db_kka->sdi,		file_kka->sdi,		sizeof( file_kka->sdi ));
	// 27 �񍐌���
	memcpy( db_kka->hkkki,		file_kka->hkkhjkka,	sizeof( file_kka->hkkhjkka ));
	// 28 �񍐌��ʊ���
	memcpy( db_kka->hkkkiknj,	file_kka->hkkhjkkakj,	sizeof( file_kka->hkkhjkkakj ));
	// 29 ��l�m��
	memcpy( db_kka->kjno,		file_kka->kjntino,	sizeof( file_kka->kjntino ));
	// 30 �T���v�����O�R�[�h
	memcpy( db_kka->smpcd,		file_kka->wscd,		sizeof( file_kka->wscd ));
	// 31 �����r�d�p
	char tmpbuf1[6+1] ,tmpbuf2[6+1];
	memset(tmpbuf1, '\0', sizeof( tmpbuf1 ));
	strncpy( tmpbuf1, file_kka->seq, sizeof( file_kka->seq ));
	sFncTrim( tmpbuf2, tmpbuf1) ;
	if( isCorrectChar( tmpbuf2 ) == RTN_OK ) {
		db_kka->knsseq = atoi( tmpbuf2 );
	} else {
		db_kka->knsseq = 0;
	}
	// 32 �X�V��
	// 33 �o�^��

	return( RTN_OK );
}

/********************************************************************************/
/*  �� �� ��  �FsFncTrim                                                        */
/*  �@�\�T�v  �F�w�蕶����̑O��̃X�y�[�X����菜���ĕ�������R�s�[����        */
/*  ��    ��  �F                                                                */
/*   ��Q���� �Fchar * �ϊ���������                                             */
/*  �o    ��  �F                                                                */
/*   ��P���� �Fchar * �ϊ��㕶����                                             */
/********************************************************************************/
void sFncTrim(char *dst, char *src) {
	int dstCnt;
	int srcCnt;
	int Flg;

	for(dstCnt = 0, srcCnt = 0, Flg = 0; src[srcCnt] != '\0'; srcCnt ++) {
		if ((dstCnt == 0) && (src[srcCnt] == '\x20')) {
			continue;
		}
		dst[dstCnt++] = src[srcCnt];
		if (src[srcCnt] != '\x20') {
			Flg = dstCnt;
		}
	}
	dst[Flg] = '\0';
}

/**************************************************************************/
/*      �� �� ��  �FisCorrectChar                                         */
/*      �@�\�T�v  �F���ґ������l�G���A�`�F�b�N                            */
/*      ��        ��  �F                                                  */
/*       ��P���� �F char       In[];   : �`�F�b�N������                  */
/*      �o        ��  �F                                                  */
/*      ���A���  �F RTN_OK             : ����I��                        */
/*                               �ȊO   : ���s                            */
/**************************************************************************/
int isCorrectChar(char *In)
{
	int	ret = RTN_OK;
	int	i = 0;
	int	nSuziFlg =0; /*���߂��������Ƃ������� */
	int	nMaxNum = strlen(In);

	for( i = 0 ; i < nMaxNum ; i++ ) {
		if(In[i] == ' '){
			if(nSuziFlg == 1){
				// DEBUG
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "���l ��������SPACE[%s]", In );
				// ERROR
				ret=RTN_NG;
				break;
			}
		}
		else if(In[i] == '.'){
			if(i==0){
				// DEBUG
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "���l �擪.�s��[%s]", In );
				// ERROR
				ret=RTN_NG;
				break;
			}
			if(nSuziFlg == 0){
				// DEBUG
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "���l �擪.�s��[%s]" , In );
				// ERROR
				ret=RTN_NG;
				break;
			}
		}
		else if(In[i] >= '0' && In[i] <= '9'){
			nSuziFlg = 1;
		}
		else{
			// DEBUG
			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "���l ��.�ȊO�s��[%s]" , In );
			// ERROR
			ret=RTN_NG;
			break;
		}
	}

	if(i == nMaxNum){
		ret=RTN_OK;
	}

	return( ret );
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
		return ( 1 );
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
	remove ( pAppEnv.cLockFile );

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
	char	 cMsg[1024] ;

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
	int		*shmData ;

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
}
/** End of File ***************************************************************/
