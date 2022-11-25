/******************************************************************************/
/*   �a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/*   �V�X�e�����F������V�X�e��                                               */
/*   �t�@�C�����FAD202.c                                                      */
/*   �T      �v�F������t�i�ً}�����˗��W�J�j�ً}�������W�J                 */
/*	 OS        �FSUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   ����      �FDB2/C                                                        */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/03/03     INTEC.INC      CREATE                             */
/*  1.01     2006/05/01     INTEC.INC      SJIS,���ڒǉ��Ή�                  */
/*  1.02     2006/05/03     INTEC.INC      UPDATE �����Ƃ���INI�t�@�C���w��   */
/*  1.04     2007/06/01     INTEC.INC      DB�G���[���ُ�I��������           */
/*  3.01     2007/06/01     INTEC.INC      �ً}�^�p�ύX�ɔ����ǉ��C��         */
/*  4.00     2009/01/06     Merits K.Ameno �{�݃R�[�h���� �ʐM�d�l�ύX�Ή�    */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "bmllog.h"
#include "AD202.h"

/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/
iconv_t		G_ic;						// with iconv
char		G_fnm[256];					// InputFileName
char		G_err[MYAPP_LEN_ERR+1];		// LogMessage(errcode)
char		G_msg[MYAPP_LEN_MSG+1];		// LogMessage
char		G_utkymd[10+1];				// LogMessage(csv)
char		G_irino[11+1];				// LogMessage(csv)
char		G_kntno[13+1];				// LogMessage(csv)
int			G_zssdino;					// 1.04 LogMessage(csv)
char		G_kmkcd[7+1];				// LogMessage(csv)
int			G_line;						// InputFileLineNo

struct      _KJNMST     *pKjn;

/******************************************************************************/
/*  �� �� ��  �Fmain                                                          */
/*  �@�\�T�v  �F�f�[�����p�吧��                                              */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fint		argc	: �p�����^��                                  */
/*   ��Q���� �Fchar	*argv[]	: �p�����^���X�g                              */
/*  �o    ��  �F                                                              */
/*   �Ȃ�                                                                     */
/*  ���A���  �F0       ����I��                                              */
/*            �F1		�ُ�I��                                              */
/******************************************************************************/
int		main( argc, argv )
int			argc;
char		*argv[];
{
	char	func_nm[MYAPP_LEN_FNCNM+1];	// �֐�����
	int		ret;						// �֐��߂�l
	int		inp_cnt, i;
	char	w_infilenm[256];			// �����O�t�@�C����
	char	w_endfilenm[256];			// �����I���t�@�C����
	struct	dirent	**namelist;			// get input file
	FILE	*fp;						// �Ǎ�̧���߲��

	struct	SHM	stcShm;					// �I�����f���L������
	int		li_stopFlg = 0;				// �I�����f
	
	/*=====================================================*/
	/*	�o�b�N�O���E���h���s                               */
	/*=====================================================*/
	//if ( daemon ( 0, 0 ) < 0 ) {
	//		exit( 1 );
	//}

	/*=====================================================*/
	/*	�����ݒ�                                           */
	/*=====================================================*/
	strcpy( func_nm,	"main" );
	memset( G_msg,		'\0', sizeof( G_msg ) );
	memset( G_utkymd,	'\0', sizeof( G_utkymd ) );
	memset( G_irino,	'\0', sizeof( G_irino ) );
	memset( G_kntno,    '\0', sizeof( G_kntno ) );
	memset( G_kmkcd,    '\0', sizeof( G_kmkcd ) );
	G_line=0;
	fp = NULL;

	// �p�����[�^�擾
	if( ParamCheckProc( argc, argv, &stcShm ) != RTN_OK ){
		/* ����ү���ޏo��	*/
		DispHelpMsg( argc, argv );
		exit( 1 );
	}

	/* 2�d�N���`�F�b�N	*/
	if( DaemonCheckProc( argc, argv ) != RTN_OK ){
		sprintf( G_msg, "�Q�d�N���h�~�̂��߁A�������I�����܂��B" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
		exit( 1 );
	}

	// ���L����������
	if( sFncShmCrt ( &stcShm ) < 0 ) {
		sprintf( G_msg, "���L�����������Ɏ��s�������߁A�������I�����܂��B" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		exit( 1 );
	}

    // DB2�Ƃ̐ڑ� 
	if(( ret = Ydbconn( )) != RTN_OK ){
		sprintf( G_err, "sqlcode=[%d]", ret );
		sprintf( G_msg, "DB2�Ƃ̐ڑ��Ɏ��s���܂����B" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		exit( 1 );
     }

    //  ����擾
    GetKjnymd( );

	// ��l�}�X�^�擾 (�ً}����)
	if( GetKjnmst( NULL ) != RTN_OK ){
		sprintf( G_msg, "��l�}�X�^�̎擾�Ɏ��s���܂����B" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		Ydbdisconn( );
		exit( 1 );
	}

	/* FILE OPEN FOR ICONV */
	// 1.01 DELL	G_ic = iconv_open( "EUC-JP", "SHIFT-JIS" );

	/*=====================================================*/
	/* ���C�����[�e�B��                                    */
	/*=====================================================*/
	for( ; ; ){		//  ......................................... daemon start
		// �Ώۃt�@�C���̎擾
		inp_cnt = scandir( stcPRM.ifp_indir, &namelist, 
					(void*)FileFilter, alphasort);
		if ( inp_cnt < 0){
			sprintf( G_err, "%d", errno );
			sprintf( G_msg, "�ً}�˗��t�@�C���̏��擾(scandir)��"
							"���s���܂����B" );
			EditCsvMsg( G_msg );
			LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			ret=1;
			break;
		} 

		for( i=0; i < inp_cnt; i++ ){	// <------------------�t�@�C���̌�����
			//------------------
			// 	�ً}��t���擾
			//------------------
			if( GetKjnymd( ) != RTN_OK ){
				sprintf( G_msg, "�ً}��t�N�����̎擾�Ɏ��s���܂����B" );
				EditCsvMsg( G_msg );
				LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, 
												__FILE__, __LINE__ );
				break;
			}

			//------------------
			// INPUT FILE OPEN
			//------------------
				// �t�@�C�����쐬
			memset( w_infilenm,		'\0',sizeof( w_infilenm ));
			memset( w_endfilenm,	'\0',sizeof( w_endfilenm ));
			sprintf( w_infilenm, "%s/%s", 
					stcPRM.ifp_indir, namelist[i]->d_name );

				// INPUT FILE OPEN
			if( ( fp = fopen( w_infilenm, "r" ) ) == NULL ){
				ret = RTN_NG;
					// WARNING
				sprintf( G_err, "%d", errno );
				sprintf( G_msg, 
					"[%s]�t�@�C���I�[�v���Ɏ��s���܂����B", w_infilenm );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm
						, __FILE__, __LINE__ );
				continue;
			}
			strcpy( G_fnm, namelist[i]->d_name );

				// scadir�t�@�C������free
			free( namelist[i] );

			//------------------
			// �o�^���� 
			//------------------
/* UPD 1.04
DEL			ret = KinqProc( fp );
*/
			ret = KinqProc( fp , &li_stopFlg );
			if( ret == RTN_NG ){
				sprintf( G_msg, "[%s]�������ɃG���[���������܂����B"
					,w_infilenm );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm
						, __FILE__, __LINE__ );

				// 1.04 DB�G���[���ُ�I��������
                if(li_stopFlg == 1)
                {
                    sprintf(G_msg, "[[DB ERROR]]");
                    //printf("li_stopFlg %d", li_stopFlg);
                    LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm
                        , __FILE__, __LINE__ );
                    fclose( fp );
                    break;
                }
			}

			//------------------
			// INPUT FILE CLOSE
			//------------------
			fclose( fp );

			//---------------------------
			// �����σt�@�C���̖��̕ύX
			// ��SKIP LOT�L�̏ꍇ��rename���Ȃ�
			//---------------------------
			if( ret != RTN_SKIP ){
					// �ύX�t�@�C�����쐬
				sprintf( w_endfilenm, "%s/%s%s" 
					,stcPRM.ifp_indir , stcPRM.ifp_endfprx,  G_fnm );
				
					// �ύX����t�@�C�������݂��Ȃ���
				for( ;; ){
					if( open( w_endfilenm, O_RDONLY, 0 ) == EOF ){
						break;
					}
					strcat( w_endfilenm, "_" );
				}
					// �t�@�C�����ύX
				rename( w_infilenm, w_endfilenm );

					// TRACE
				sprintf( G_msg, 
					"�����ψ˗��t�@�C��[%s]�̖��O��[%s]�ɕύX���܂����B"
					, w_infilenm, w_endfilenm );
				LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, 
						__FILE__, __LINE__);
			}

			//------------------
			// �I�����f
			//------------------
				// ���L�������擾
			// 1.04 DB�G���[���ُ�I��������
            if(li_stopFlg != 1)
            {
			if( sFncShmGet ( &stcShm, &li_stopFlg ) < 0 ){
					// �I��
				li_stopFlg = 1;

					// WARNING
				sprintf( G_msg, 
					"���L�����������Ɏ��s�������߁A�����𔲂��܂��B" );
				EditCsvMsg( G_msg );
				LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
									__FILE__, __LINE__ );
			}
			}
			if( li_stopFlg == 1 ){
				break;
			} 
		} 	// ---------------------------------------------> �t�@�C���̌�����

		// scandir �t�@�C������ free
		free( namelist );

		//------------------
		// �I�����f
		//------------------
			// ���L�������擾

		// 1.04 DB�G���[���ُ�I��������
		if(li_stopFlg != 1)
		{
		if( sFncShmGet ( &stcShm, &li_stopFlg ) < 0 ){
				// WARNING
			sprintf( G_msg, "���L�����������Ɏ��s�������߁A�������I�����܂��B");
			EditCsvMsg( G_msg );
			LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			break;
		}
		}
		if( li_stopFlg == 1 ){
				// TRACE
			sprintf( G_msg, "�I���w�����o�����߁A�������I�����܂��B");
			LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			break;
		} 

		// CONTINUE
			// DEBUG
		sprintf( G_msg, "SLEEP.....[%d]", stcPRM.myp_sleep );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

		sleep( stcPRM.myp_sleep );

	}	// ...................................................... daemon end

	/*=====================================================*/
	/*	�I������                                           */
	/*=====================================================*/
	// ICONV CLOSE
	// 1.01 DELL	iconv_close( G_ic );

	// DB2�Ƃ̐ڑ�����
	if(( ret = Ydbdisconn( )) != RTN_OK ){
		// ERROR
		sprintf( G_msg, "DB2�Ƃ̐ڑ������Ɏ��s���܂����B" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);

		ret=1;
	}
	
	// ��l�}�X�^�̗̈�����
	if( pKjn != NULL ){
		// TRACE
		strcpy( G_msg, "��l�}�X�^�̗̈������B" );
		LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

		 free( pKjn );
	}

	// ���L�������폜
	sFncShmDel ( &stcShm ) ;

	// TRACE
	strcpy( G_msg, "���O�o�͏I���B" );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

    /* LOG CLOSE */
	ZbmlCloseLog( );

	exit( ret );
}

/******************************************************************************/
/*  �� �� ��  �FDispHelpMsg                                                   */
/*  �@�\�T�v  �FHELP���b�Z�[�W�o��                                            */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fint		argc	: �p�����^��                                  */
/*   ��Q���� �Fchar	*argv[]	: �p�����^���X�g                              */
/*  �o    ��  �F�Ȃ�                                                          */
/*  ���A���  �F INT                                                          */
/*               RTN_OK     : ����                                            */
/*               RTN_NG     : ���s                                            */
/******************************************************************************/
void	DispHelpMsg( argc, argv )
int			argc;
char		*argv[];
{
fprintf(stderr,"����:�ً}�������W�J\n" );
fprintf(stderr,"    :������t�i�ً}�����˗��W�J�j���ҏ��E�˗�����o�^���܂�\n" );
fprintf(stderr,"     �ً}�˗��擾�f�B���N�g��[%s]\n", stcPRM.ifp_indir );
fprintf(stderr," \n" );
fprintf(stderr,"   :tst_zok\n" );
fprintf(stderr,"     -LG ���O�t�@�C����(�ȗ���:%s.log)\n", stcPRM.myp_exefile );
fprintf(stderr,"     -SD ����ԍ�(�ȗ���:01)\n" );
fprintf(stderr,"\t[-dbg|-DBG]\n");
	return;
}

/******************************************************************************/
/*  �� �� ��  �FParamCheckProc                                                */
/*  �@�\�T�v  �F�p�����[�^�擾���`�F�b�N                                      */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fint		argc	: �p�����^��                                  */
/*   ��Q���� �Fchar	*argv[]	: �p�����^���X�g                              */
/*  �o    ��  �F�Ȃ�                                                          */
/*  ���A���  �F INT                                                          */
/*               RTN_OK     : ����                                            */
/*               RTN_NG     : ���s                                            */
/******************************************************************************/
int		ParamCheckProc( argc, argv, stcShm )
int			argc;
char		*argv[];
struct		SHM		*stcShm;
{
	char	func_nm[MYAPP_LEN_FNCNM+1];	/* �֐�����	 */
	char	*p_fini;					/* 1.02 INI FILE ����    */
	char	*cp;						/* �Ώۃp�����^ */
	int		ret=RTN_OK;
	int		i;

	/* �����ݒ�	*/
	strcpy( func_nm,	"ParamCheckProc" );
	memset( &stcPRM,	'\0', sizeof( stcPRM ));

	/* ���s�v���O�������̐ݒ� */
	for( cp = argv[0], cp += strlen( cp ); cp != argv[0]; --cp ) {
		if( *cp == '/' || *cp == '\\' ) {
			cp++;
			break;
		}
	}
	// 1.02 INI FILE �������������
    if( argc >= 2 ){
        p_fini = argv[1];
    } else {
        p_fini = MYAPP_INIFILE;
    }
	strncpy( stcPRM.myp_exefile, cp, sizeof( stcPRM.myp_exefile ) - 1 );
	stcPRM.myp_debug=0;
	stcPRM.myp_sleep=10;
	stcPRM.myp_sedai=0;
	
	//-------------------------------
	// LOG�o�͏�������
	//-------------------------------
    cp = GetIniFile( "SERVER.LOG", "LOGINI", p_fini );
    if( cp != NULL ) {
		// ���ϐ�($HOME)��W�J���Ă���Z�b�g
		strcpy( stcPRM.lgp_comlog, EnvRef( cp ));
    }
		// ���Oini�t�@�C���I�[�v��
	if ( ZbmlOpenLog( stcPRM.lgp_comlog ) != 0 ){
			return( RTN_NG );
	}
	strcpy( G_msg, "���O�o�͊J�n" );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	//-------------------------------
	// DB PARAM
	//-------------------------------
    cp = GetIniFile( "DB2.CNCT", "DBALIAS", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.dbp_dbAlias );
    }
    cp = GetIniFile( "DB2.CNCT", "USER", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.dbp_user );
    }
    cp = GetIniFile( "DB2.CNCT", "PSWD", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.dbp_pswd );
    }

	//-------------------------------
	// HOST  PARAM
	//-------------------------------
    cp = GetIniFile( "HOST.PARA", "HOSTDIR", p_fini );
    if( cp != NULL ) {
		// ���ϐ�($HOME)��W�J���Ă���Z�b�g
		strcpy( stcPRM.ifp_indir, EnvRef( cp ));
    }
    cp = GetIniFile( "HOST.PARA", "INFPRX", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_infprx );
    }
    cp = GetIniFile( "HOST.PARA", "ENDFPRX", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_endfprx );
    }

	//-------------------------------
	// ���L�������L�[�擾
	//-------------------------------
	cp = GetIniFile( "MYAPP.PARA", "MYAPP_SHMKEY", p_fini );
    if( cp != NULL ) {
		stcShm->shm_Key = atoi ( cp ) ;
    }

	//-------------------------------
	// MYAPP PARAM
	//-------------------------------
    cp = GetIniFile( "MYAPP.PARA", "MYAPP_SLEEP", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%d", &stcPRM.myp_sleep );
    }
    cp = GetIniFile( "MYAPP.PARA", "MYAPP_SEDAI", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%d", &stcPRM.myp_sedai );
    }
    cp = GetIniFile( "MYAPP.PARA", "MYAPP_ZAIRYO", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", &stcPRM.myp_zairyo );
    }
    cp = GetIniFile( "MYAPP.PARA", "MYAPP_DEBUG", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%d", &stcPRM.myp_debug );
    }

	sprintf( G_msg, "G_exefile [%s]",	stcPRM.myp_exefile );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "DBP       [%s-%s-%s]"
		, stcPRM.dbp_dbAlias, stcPRM.dbp_user, stcPRM.dbp_pswd );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "HOSTDIR   [%s]",	stcPRM.ifp_indir );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "INFPRX    [%s]",	stcPRM.ifp_infprx );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "ENDFPRX   [%s]",	stcPRM.ifp_endfprx );

	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "logini    [%s]",	stcPRM.lgp_comlog );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "G_sleep   [%d]",	stcPRM.myp_sleep );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "G_sedai   [%d]",	stcPRM.myp_sedai );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "G_zairyo  [%s]",	stcPRM.myp_zairyo );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FGetKjnymd                                                     */
/*  �@�\�T�v  �F�ً}��t���擾                                                */
/*  ��    ��  �F�Ȃ�                                                          */
/*  �o    ��  �F�Ȃ�                                                          */
/*  ���A���  �F INT                                                          */
/*               RTN_OK     : ����                                            */
/*               RTN_NG     : ���s                                            */
/******************************************************************************/
int		GetKjnymd( )
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	 */
	int		ret=RTN_OK;

	struct	_SYSKNRMST	knr;

	/* �����ݒ�	*/
	strcpy( func_nm,	"GetKjnymd" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	// �ً}��t���̎擾
	memset( &knr,	'\0',	sizeof( struct _SYSKNRMST ) );
	if(( ret = SelSysknrmst( &knr )) == RTN_OK ){
		strcpy( stcPRM.myp_kjnymd,	knr.kkkjsriymd );
		sprintf( G_msg, "�ً}��t����[%s]�Ƃ��܂��B" ,stcPRM.myp_kjnymd );
	}
	// TRACE
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  �� �� ��  �FFileFilter                                                    */
/*  �@�\�T�v  �F�t�@�C���t�B���^�[�y�R�[���o�b�N�֐��z                        */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct		dirent *     �f�B���N�g���\����                   */
/*  �o    ��  �F�Ȃ�                                                          */
/*  ���A���  �F INT                                                          */
/*               0		: �ΏۊO�t�@�C��                                      */
/*               1		: �Ώۃt�@�C��                                        */
/******************************************************************************/
static	int		FileFilter( namelist )
struct	dirent	*namelist ;
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	 */
	char	w_fnm[256];
	struct	stat	statbuf;				// get input file status

	strcpy( func_nm, "FileFilter" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	// �f�B���N�g���͏���
	sprintf( w_fnm, "%s/%s", stcPRM.ifp_indir, namelist->d_name );
	stat( w_fnm, &statbuf );
	if( S_ISDIR( statbuf.st_mode )){
		// DEBUG
		sprintf( G_msg, "DIR SKIP mode: 0%o [%s]" ,statbuf.st_mode, w_fnm );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
		// �ΏۊO
		return( 0 );
	}
	// ������PREFIX�ɍ��v������̂͏���
	if(( strcmp( stcPRM.ifp_endfprx, "" ) != 0 )
	 &&( memcmp( namelist->d_name, stcPRM.ifp_endfprx
					, strlen( stcPRM.ifp_endfprx )) == 0 )){
		// DEBUG
		sprintf( G_msg, "END FILE SKIP mode: 0%o [%s]" ,statbuf.st_mode, w_fnm);
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
		// �ΏۊO
		return( 0 );
	}
	// �Ώۃt�@�C���̐擪or�g���q�ɂ�锻�f
	if( memcmp( namelist->d_name, stcPRM.ifp_infprx
					, strlen( stcPRM.ifp_infprx )) == 0 ){
		// DEBUG
		sprintf( G_msg, "�����Ώ� mode: 0%o [%s]" ,statbuf.st_mode, w_fnm );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
		// OK
		return ( 1 );
	}
	// DEBUG
	sprintf( G_msg, "�擪�����񂪈قȂ�[%s]" , namelist->d_name );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return ( 0 );
}

/******************************************************************************/
/*  �� �� ��  �FKinqProc                                                      */
/*  �@�\�T�v  �FAS400 �ً}�˗��t�@�C������                                    */
/*  ��    ��  �F                                                              */
/*   ��P���� �F FILE	pfp	: ���̓t�@�C�����ʎq                              */
/*  �o    ��  �F �Ȃ�                                                         */
/*  ���A���  �F INT                                                          */
/*               RTN_OK     : ����                                            */
/*               RTN_NG     : ���s                                            */
/******************************************************************************/
//1.04 int		KinqProc( pfp )
int		KinqProc( pfp , stopValue )
FILE    	*pfp;
int			*stopValue;						// 1.04 ADD
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����		*/
	int		ret;							/* �֐��߂�l	*/

	/* �˗���MKINQ format(S-JIS) */
	struct	AS4IRAI			kinq;		/* PNC��M�g���[���[(S-JIS) */

	struct	_KANJYA			kan;		/* ���ҏ��	*/
	struct	_IRAI			irai;		/* �˗����	*/
	struct	KOMST			*kom;		/* �˗����ڏ��\���� */
	struct  JIDOIRAI        *pJir;      // 1.04 ADD �����������ڏ��
	struct	CNT				stcCNT;		/* �������		*/

	char	rbuf[KINQ_RECSIZE+1];		/* �ǂݍ��ݴر		*/
	char	key_uymd[8+1];				/* Ver 4.00 8���Ɋg�� */
	char	key_kntno[11+1];			/* Ver 4.00 11���Ɋg�� */
	char	key_lot[2+1];
	char	w_ymd[7];
	char	w_str[200];
	int		wcnt_kan=0;					/* ���ҏ��o�^����*/
	int		wcnt_iri=0;					/* �˗����o�^����*/
	int		wcnt_lot=0;					/* LOT���ҏ��o�^����*/
	int		i,j;						/* index		*/
	int		kmax = IKOM_MAX, lotno;

	int		nSQLErrorValue;				// 1.04 DB�G���[���ُ�I��������
    int     jd_max;                     // 1.04 ADD �����������ڐ�
    char    w_age[3+1];                 /* 1.04 ADD �N��         */
    char    w_age_kbn[1+1];             /* 1.04 ADD �N��敪         */
	int     KnkyulotIns_Ret = 0;        /* �ً}LOTNO�e�[�u��INSERT���ʎ擾�̈� */
	int     KanjyaIns_Ret = 0;          /* ���҃e�[�u��INSERT���ʎ擾�̈� */
	int     IraiIns_Ret = 0;            /* �˗��e�[�u��INSERT���ʎ擾�̈� */

	/* �����ݒ�	*/
	strcpy( func_nm,	"KinqProc" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �ر	*/
	ret = RTN_OK;

	stcCNT.cnt_irai = stcCNT.cnt_irai_err = 0;
	stcCNT.cnt_skip = stcCNT.cnt_exc = stcCNT.cnt_sumi = 0;
	stcCNT.cnt_kanjya=stcCNT.cnt_dbirai=0;
	wcnt_kan = wcnt_iri = wcnt_lot = 0;
	memset( key_uymd, '\0', sizeof( key_uymd ));
	memset( key_kntno, '\0', sizeof( key_kntno ));
	memset( key_lot,  '\0', sizeof( key_lot ));

	// �ً}��t���̑ޔ�	(YYYYMMDD�@�ɕύX)
	sprintf( key_uymd,	"%.4s%.2s%.2s", &stcPRM.myp_kjnymd[0]
				,&stcPRM.myp_kjnymd[5], &stcPRM.myp_kjnymd[8] );

	sprintf( G_msg,	"��t�i�ً}�����˗��W�J�j ���ҏ��E�˗����o�^�J�n"
		" : �ً}�˗��t�@�C����[%s]", G_fnm );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	// DEBUG
	sprintf( G_msg, "INFILE[%s] START!!----->", G_fnm );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	while( 1 ){								// read while start ----------->
		/* ̧�ق̓Ǎ�(S-JIS)	*/
		if ( ReadKinq( rbuf, pfp ) != EOF ){
			/* �׸ޗ޸ر	*/
			stcCNT.cnt_irai++;	/* ���͌���     */
			G_line=stcCNT.cnt_irai;
			memset( G_utkymd,	'\0', sizeof( G_utkymd ));
			memset( G_irino,	'\0', sizeof( G_irino ));
			memset( G_kntno,	'\0', sizeof( G_kntno ));
			memset( G_kmkcd,	'\0', sizeof( G_kmkcd ));
			G_zssdino=0;

			// DEBUG
			strcpy( G_msg, "}" );
			LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
			sprintf( G_msg, "���͌���(%d) size(%d) ===============>{"
					, stcCNT.cnt_irai, strlen( rbuf ) );
			LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

			// ���R�[�h�T�C�Y�`�F�b�N
			if( strlen( rbuf ) != ( KINQ_RECSIZE )){
				// ERROR
				stcCNT.cnt_irai_err++;
				sprintf( G_msg, "�ǂݍ��݃��R�[�h�T�C�Y�G���[[%d]", strlen( rbuf ));
				EditCsvMsg( G_msg );
				LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
				continue;
			}
			// 1���ڂ�COMMIT�ΏۊO
			if( stcCNT.cnt_irai == 1 ){
				ret=RTN_SKIP;
			}
		} else {
			memset( rbuf,	'\0', sizeof( rbuf ));
		}

//-----< ����BML����E�˗���NO,LOTNO �����������̂�
//                          1TRANSACTION�Ƃ��邽��KEY�̔�r���s�� >------------
		   // ����L�[�Ȃ��COMMIT���Ȃ�
        if(( memcmp( key_uymd, &rbuf[KINQ_POS_UDATE],   8 ) != 0 ) /* ��t���t */
        || ( memcmp( key_kntno,&rbuf[KINQ_POS_KENNO],   11 ) != 0 )/* ����No */
        || ( memcmp( key_lot,  &rbuf[KINQ_POS_LOT], 2 ) != 0 ))    /* ���b�g */
		{
			// DEBUG
            sprintf( G_msg, "KEY-BREAK���� [%8.8s][%11.11s][%2.2s]---------------",
					&rbuf[KINQ_POS_UDATE], &rbuf[KINQ_POS_KENNO], &rbuf[KINQ_POS_LOT] );
            LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// 1.04 ADD �������������@STA ===================================
			do {		/* Do-while�͂P��̂ݎ��s	�@	*/
				jd_max=0;
				
				// �G���[������ꍇ�͍s��Ȃ�
				if( ret != RTN_OK ){
					break;
				}
				// INSERT�������O�̏ꍇ�͔�����
				if( wcnt_iri == 0 ){
					break;
				}
				// �����������ڂ̗L���`�F�b�N
        		if(( jd_max=SelCountJkmkmst( irai.utkymd
											, irai.irino, irai.sriymd )) < 1 ){
					// ���������Ώۍ��ځ@���݂���
					break;
				}
				// �̈�m��
				if(( pJir = ((struct JIDOIRAI *)malloc(
							sizeof(struct JIDOIRAI) * jd_max ))) == NULL ){
					sprintf( G_err, "%d", errno );
					sprintf( G_msg, "�����������ڂ̗̈�m�ۂɎ��s���܂����B" );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm,
								__FILE__, __LINE__ );
					ret=RTN_NG;
					break;
				}
				// �����������ڗ̈�̏�����
        		memset( pJir, '\0', sizeof( struct JIDOIRAI ) * jd_max );
				// �˗��\���̂P���ڂɎ���{�˗���NO���Z�b�g
				strcpy( pJir[0].sIri.utkymd,		irai.utkymd );
				strcpy( pJir[0].sIri.irino,			irai.irino );
				strcpy( pJir[0].sIri.sriymd,		irai.sriymd );
				// �Ώۃf�[�^���̎擾
				if( SelJidoirai( pJir, jd_max ) !=  RTN_OK ){
					sprintf( G_err, "%d", errno );
					sprintf( G_msg, "�����������ڂ̂̓ǂݍ��݂Ɏ��s���܂����B" );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm,
									__FILE__, __LINE__ );
					free( pJir );
					ret=RTN_NG;
					break;
				}
				for( i = 0; i < jd_max; i++ ){
					// EDIT
					strcpy( pJir[i].age,		kan.age );
					strcpy( pJir[i].agekbn,		kan.agekbn );
					if( EditJidoIrai( &(pJir[i]) ) != RTN_OK ){
						// ERROR
						strcpy( G_msg, "���������˗����ҏW���ɃG���[���������܂����B" );
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__);
						ret = RTN_NG;

						break;
					}
					memcpy( &irai, &pJir[i].sIri, sizeof( struct _IRAI ));

					// ini�t�@�C���ł�DEBUG�w�莞�̂�print���������s
					if( stcPRM.myp_debug == 1 ){
						 irai_pr( &irai );
					}

					/* INSERT */
					if( InsIrai( &irai ) != RTN_OK ){
						// ERROR
						strcpy( G_msg, "���������˗����o�^���ɃG���[���������܂����B" );
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__);
						ret = RTN_NG;

						break;
					}
				}
				free( pJir );
				break;
			} while( 1 );
			// 1.04 ADD �������������@END ===================================

			/* �G���[�����`�F�b�N	*/
			if( ret == RTN_OK ){
				if( Ydbcommit( ) != RTN_OK ){
						// ERROR
					strcpy( G_msg, "DB2��COMMIT�Ɏ��s���܂����B\n" );
					EditCsvMsg( G_msg );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__ );
					stcCNT.cnt_kanjya -= wcnt_kan;
					stcCNT.cnt_dbirai -= wcnt_iri;
				}
				stcCNT.cnt_kanjya += wcnt_kan;
				stcCNT.cnt_dbirai += wcnt_iri;
				wcnt_lot++;
			} else if ( ret == RTN_SKIP ){
			} else {
				// ERROR
				strcpy( G_msg, "�f�[�^�����ŃG���[���������܂����B" );
				EditCsvMsg( G_msg );
				LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__);

				// 1.04 DB�G���[���ُ�I��������
                nSQLErrorValue = atoi(G_err);

				if( Ydbrollback( ) != RTN_OK ){
						// ERROR
					strcpy( G_msg, "DB2��ROLLBACK�Ɏ��s���܂����B"  );
					EditCsvMsg( G_msg );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__);
				}
				// 1.04 DB�G���[���ُ�I��������
                if((nSQLErrorValue< 0)&& (nSQLErrorValue != -911)&&(nSQLErrorValue !=-803))
                {
                    sprintf(G_msg, "##### DB�G���[�@�����@##### %d", nSQLErrorValue);
					EditCsvMsg( G_msg );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__);
                    *stopValue = 1;
                    return(RTN_NG);
                }
			}

			// INIT
			wcnt_kan = wcnt_iri = 0;

			// DEBUG
            strcpy( G_msg, "KEY-BREAK KNTNO ���� END ---------------------->" );
            LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}

		// KEY LOT
		if(( memcmp( key_uymd, &rbuf[KINQ_POS_UDATE],   8 ) != 0 ) /* ��t���t */
		|| ( memcmp( key_lot,  &rbuf[KINQ_POS_LOT], 2 ) != 0 ))    /* ���b�g */
		{
			// �ً}���b�gNO�̓o�^ (�L�[��LOTNO�ɂ�)
			if( wcnt_lot > 0 ){
				lotno = atoi( key_lot );
				KnkyulotIns_Ret = InsKnkyulot( stcPRM.myp_kjnymd, lotno );	/* �ً}LOT INSERT */
				if( KnkyulotIns_Ret != RTN_OK ){							/* INSERT�Ɏ��s�����H */
					// WARNING
					if( KnkyulotIns_Ret == MYAPP_RTN_DUP ){					/* ���s���R���d���̏ꍇ */
						sprintf( G_msg, 
							"�o�^�ςً݂̋}LOTNO�ł��B�˗��ǉ����l�����܂��B"
							":��t�N����[%8.8s] ���b�gNO[%s]", key_uymd, key_lot );
						EditCsvMsg( G_msg );
						LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm,  __FILE__, __LINE__);
					}
					else{													/* ���s���R���d���ȊO */
						sprintf( G_msg, 
							"�ً}���b�gNO�̓o�^�Ɏ��s���܂����B"
							":��t�N����[%8.8s] ���b�gNO[%s]", key_uymd, key_lot );
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm,  __FILE__, __LINE__);
					}
					nSQLErrorValue = atoi(G_err);							/* DB�G���[���ُ�I��������ׁA�G���[�R�[�h�Z�b�g */

					if( Ydbrollback( ) != RTN_OK ){
							// ERROR
						strcpy( G_msg, "DB2��ROLLBACK�Ɏ��s���܂����B"  );
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
								__FILE__, __LINE__);
					}
					if((nSQLErrorValue< 0) && (nSQLErrorValue != -911) && (nSQLErrorValue !=-803)){
																			/* �G���[�R�[�h�`�F�b�N */
						sprintf(G_msg, "##### DB�G���[�@�����@##### %d", nSQLErrorValue);
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
								__FILE__, __LINE__);
						*stopValue = 1;
						return(RTN_NG);
					}
				} else {
					if( Ydbcommit( ) != RTN_OK ){
							// ERROR
						strcpy( G_msg, "�ً}���b�gNO DB2��COMMIT�Ɏ��s���܂����B" );
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
								__FILE__, __LINE__ );
					}
				}
			}
			// INIT 
			wcnt_lot = 0;
		}

		// EOF
        if( rbuf[0] == '\0' ){
            break;
        }

		// ���t�`�F�b�N
		if( memcmp( key_uymd, &rbuf[KINQ_POS_UDATE], 8 ) != 0 ){ /* ��t���t */
			// SKIP
			sprintf( G_msg, 
				"��t�N����[%.8s]���ً}�˗��W�J�Ώۓ�[%s]�ƍ��v���܂���B"
				":LOTNO[%.2s]",
				&rbuf[KINQ_POS_UDATE],	key_uymd, &rbuf[KINQ_POS_LOT] );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, 
							__FILE__, __LINE__);

			// 3.01 ADD ERROR����LOTNO=0�ɐݒ�
			if( UpdKnkyulot( MYAPP_DEF_ERR01 ) != RTN_OK ){
				// WARNING
				sprintf( G_msg, 
					"�ً}���b�gNO�̍X�V�Ɏ��s���܂����B"
					":��t�N����[%8.8s] ���b�gNO=0", key_uymd );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, 
								__FILE__, __LINE__);

				// 1.04 DB�G���[���ُ�I��������
				nSQLErrorValue = atoi(G_err);

				if( Ydbrollback( ) != RTN_OK ){
						// ERROR
					strcpy( G_msg, "DB2��ROLLBACK�Ɏ��s���܂����B"  );
					EditCsvMsg( G_msg );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__);
				}
				if((nSQLErrorValue< 0)&& (nSQLErrorValue != -911)&&(nSQLErrorValue !=-803))
				{
					sprintf(G_msg, "##### DB�G���[�@�����@##### %d", nSQLErrorValue);
					EditCsvMsg( G_msg );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
								__FILE__, __LINE__);
					*stopValue = 1;
					return(RTN_NG);
				}
			} else {
				if( Ydbcommit( ) != RTN_OK ){
					// ERROR
					strcpy( G_msg, "�ً}���b�gNO DB2��COMMIT�Ɏ��s���܂����B" );
					EditCsvMsg( G_msg );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__ );
				}
			}
			
			// 3.01 ��t�����قȂ�ꍇ��PG���I������
			//		�r���̃f�[�^�͂��̂܂ܗL���ɂ���
			stcCNT.cnt_skip++;
			//continue;
			*stopValue = 1;
			return(RTN_SKIP);
		}

		// LOTNO CHECK
		if ( memcmp( key_lot,  &rbuf[KINQ_POS_LOT], 2 ) != 0 ) /* ���b�g */
		{
			// ������LOTNO�`�F�b�N (�ǂݍ��݃f�[�^��LOTNO�ɂ�)
			memset( w_str,	'\0',	sizeof( w_str ));
			memcpy( w_str,	&rbuf[KINQ_POS_LOT],	2 ); /* ���b�g */
			lotno = atoi( w_str );
			if( lotno == 0 ){
				// ERROR
				sprintf( G_msg, "�ً}���b�gNO ������������܂���B "
					" ����No[%11.11s] �ً}���b�gNO[%2.2s]"
					,&rbuf[KINQ_POS_KENNO], &rbuf[KINQ_POS_LOT] );
				EditCsvMsg( G_msg );
				LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
						__FILE__, __LINE__ );
				// 3.01 ��t�����قȂ�ꍇ��PG���I������
				//		�r���̃f�[�^�͂��̂܂ܗL���ɂ���
				stcCNT.cnt_skip++;
				*stopValue = 1;
				return(RTN_SKIP);
			}
				// �Y�����R�[�h������߂�
/*			if( GetKnkyulot( stcPRM.myp_kjnymd, lotno ) > 0 ){
				// �ً}���b�g���o�^�ς� -> SKIP
				stcCNT.cnt_sumi++;
				continue;
			}*/
		}

		// KEY SET
		memcpy( key_lot,	&rbuf[KINQ_POS_LOT],	2 );  /* ���b�g */
		memcpy( key_uymd,	&rbuf[KINQ_POS_UDATE],	8 );  /* ��t���t */
		memcpy( key_kntno,  &rbuf[KINQ_POS_KENNO],  11 ); /* ����No */

		/* --------------------------------	*/
		/*	���� 							*/
		/* --------------------------------	*/
		// DEBUG
		sprintf( G_msg, "���� uymd[%s] kntno[%s] lot[%.2s]"
				, key_uymd, key_kntno, key_lot );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

		ret = RTN_OK;
		memcpy( &kinq,	rbuf, sizeof( struct AS4IRAI ) );
		do {		/* Do-while�͂P��̂ݎ��s	�@	*/
			// ���ґ����ҏW
			memset( &kan,	0x00, sizeof( struct _KANJYA ));
			if(( ret= EditKinqKanjya( &kinq, &kan )) != RTN_OK ){
				/* �װ*/
				ret = RTN_SKIP;
				// do-while
				break;
			}

			// �˗���� 
			if(( kom =  ( struct KOMST *)malloc( 
					sizeof( struct KOMST ) * kmax )) == NULL ){
				sprintf( G_err, "%d", errno );
				strcpy( G_msg, "�ً}�Ή����ڏ��̗̈�m�ۂɎ��s���܂����B" );
				EditCsvMsg( G_msg );
				LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
									__FILE__, __LINE__);
				ret = RTN_NG;
				// do-while
				break;
			}
			memset( kom,	'\0',	sizeof( struct KOMST ) * kmax );
			memset( &irai,	'\0',	sizeof( struct _IRAI ));

			EditKinqIrai( &kinq, &kan, &irai );

			for( i = j = 0; i < kmax; i++ ){
				// ���ڃR�[�h���X�y�[�X�Ȃ�Δ�����
				if( memcmp( kinq.ikm[i].c_koumoku_cd, MYAPP_SPACE10, 
					sizeof( kinq.ikm[i].c_koumoku_cd )) == 0 ){
					// for
					break;
				}
				// ���{�t���O�ɂ��Ώ۔��f
				if( kinq.ikm[i].c_labo_flg[0] != '1' ){
					// for
					continue;
				}
				// �}�X�^�ɂ��Ώ۔��f�A�}�X�^���擾
					// 0->0
				sprintf( kom[j].kmkcd, "%-7.7s", kinq.ikm[i].c_koumoku_cd );

				// 3.01 �ً}�Ή�����(SMPCD�擾)�����ڃ}�X�^������G�}�X�^�擾�܂�
				//      ���݂��Ȃ��ꍇ��SKIP����
				if( EditKinqIraiKomoku( &(kom[j]), irai.stsrcd, kan.age, irai.skflg ) 
									== RTN_SKIP ){
					// for
					continue;
				}
				j++;
			}
			// �Y���˗��������ꍇ�͊��ґ������o�^���Ȃ�
			if( j == 0 ){
				stcCNT.cnt_exc++;
				sprintf( G_msg, "�����{�Ώۂ̈˗����ڂ�����܂���B:KNTNO[%s]", 
						key_kntno );
				EditCsvMsg( G_msg );
				LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, 
									__FILE__, __LINE__);
				if( wcnt_kan > 0 || wcnt_iri > 0 ){
					// ����KEY��KANJYA INSERT OK
					ret = RTN_OK;
				} else {
					ret = RTN_SKIP;
				}
				// do-while
				break;
			}
//-----< �o�^ >----------------------------------------------------------------
			/* KANJYA INSERT */
				/* ����L�[��1���R�[�h�ڂ̂ݑΏ�	 */
			if( wcnt_kan == 0 ){
				KanjyaIns_Ret = InsKanjya( &kan );			/* ���҃e�[�u����INSERT */
				if( KanjyaIns_Ret != RTN_OK ){				/* ���ҏ��INSERT�Ɏ��s�H */
					if( KanjyaIns_Ret != MYAPP_RTN_DUP ){	/* ���s���R���d���G���[�ł͂Ȃ��ꍇ */
						/* ERROR LOG */
						strcpy( G_msg, "���ҏ��o�^���ɃG���[���������܂����B" );
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__);
						ret = RTN_NG;
						// do-while
						break;								/* �d���G���[�ȊO�͏������I�� */
					}
					else{									/* �d���G���[�̏ꍇ */
						/* WARNING LOG */
						sprintf( G_msg,
								"�o�^�ς݂̊��҂ł��B�˗��ǉ����l�����܂��B"
								":��t�N����[%s] �˗���NO[%s]",
								kan.utkymd, kan.irino );
						EditCsvMsg( G_msg );
						LogOut( LT_WRN, LX_INS, G_err, G_msg, func_nm,  __FILE__, __LINE__);
							;								/* �d���G���[�̏ꍇ�͉������Ȃ��Ń��[�j���OLOG��f��*/
															/* �ߋ�LOT���̈˗��ǉ��Ή� */
					}
				}
				else{										/* INSERT������ɏI�������ꍇ */
					ret = RTN_OK;
					wcnt_kan++;
				}
			}

			/* IRAI INSERT */
			for( i = 0; i < j; i++ ){
				strcpy( irai.knsgrp,	kom[i].knsgrp );
				strcpy( irai.kmkcd,		kom[i].kmkcd );
				strcpy( irai.kmkrs,		kom[i].kmkrs );
				strcpy( irai.oyakmkcd,	kom[i].oyakmkcd );
				strcpy( irai.bkfkkbn,	kom[i].fkbnkkb );
				strcpy( irai.seccd,		kom[i].seccd );
				strcpy( irai.smpcd,		kom[i].smpcd );
				strcpy( irai.kjno,		kom[i].kjno );

				// ini�t�@�C���ł�DEBUG�w�莞�̂�print���������s
				if( stcPRM.myp_debug == 1 ){
					 irai_pr( &irai );
				}

				IraiIns_Ret = InsIrai( &irai ); /* �˗��e�[�u����INSERT */
				if( IraiIns_Ret != RTN_OK ){    /* INSERT�Ɏ��s�����H*/
					/* �װ*/
/*** �ߋ�LOT���̈˗��ǉ��Ή� ***/
					if ( IraiIns_Ret == MYAPP_RTN_DUP ){/* ���s���R���d���G���[�̏ꍇ */
						/* WARNING LOG */
						sprintf( G_msg, 
							"�o�^�ς݂̍��ڂł��B�˗��ǉ����l�����܂��B"
							":��t�N����[%s] �˗���NO[%s] ���ڃR�[�h[%s]",
							irai.utkymd, irai.irino, irai.kmkcd );
						EditCsvMsg( G_msg );
						LogOut( LT_WRN, LX_INS, G_err, G_msg, func_nm,  __FILE__, __LINE__);
							;								/* �d���G���[�̏ꍇ�͉������Ȃ��Ń��[�j���OLOG��f��*/
															/* �ߋ�LOT���̈˗��ǉ��Ή� */

						continue;
					}
					else{		/* �d���G���[�ȊO�̏ꍇ�̓}�Y�C�̂ŁA�~�߂� */
						ret = RTN_NG;
						break;
					}
				}
				wcnt_iri++;	
			}
			// �K��
			break;
		} while( wcnt_kan < 1 );
		if( kom != NULL ){
			free( kom );
		}
	}	// <---------------------------------------------------read while end

//-----< 1FILE READ END >-------------------------------------------------------
	// DEBUG
	sprintf( G_msg, "�ŏI���͌���(%d)kan[%d]dbirai[%d]", 
		stcCNT.cnt_irai ,stcCNT.cnt_kanjya ,stcCNT.cnt_dbirai );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	memset( G_utkymd,	'\0', sizeof( G_utkymd ));
	memset( G_irino,	'\0', sizeof( G_irino ));
	memset( G_kntno,	'\0', sizeof( G_kntno ));
	memset( G_kmkcd,	'\0', sizeof( G_kmkcd ));
	G_line=0;

	// TRACE
    sprintf( G_msg, "�ً}  ���ҏ��E�˗����o�^�������I�����܂���" );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "        �S�˗�����                  �F%10d��"
														,stcCNT.cnt_irai );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            ���t�ΏۊO�˗�����(SKIP)�F%10d��"
														,stcCNT.cnt_skip );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            ���ڑΏۊO�˗�����(SKIP)�F%10d��"
														,stcCNT.cnt_exc );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            �����ψ˗�����(SKIP)    �F%10d��"
														,stcCNT.cnt_sumi );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            �G���[�˗�����(SKIP)    �F%10d��"
														,stcCNT.cnt_irai_err );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            ���ґ����o�^����        �F%10dں���"
														,stcCNT.cnt_kanjya );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
    sprintf( G_msg, "            �˗����o�^����        �F%10dں���"
														,stcCNT.cnt_dbirai );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	if( stcCNT.cnt_skip == 0 ){
		ret = RTN_OK;
	} else {
		ret = RTN_SKIP;
	}
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FReadKinq                                                      */
/*  �@�\�T�v  �F�ً}�˗��t�@�C���ǂݍ���                                      */
/*  ��    ��  �F                                                              */
/*   ��P���� �F char	file_nm[]	: ���̓t�@�C���|�C���^                    */
/*  �o    ��  �F char	rbuf[];		: �ǂݍ��݃o�b�t�@                        */
/*  ���A���  �F 0�ȏ�				: ����I��(�Ǎ��T�C�Y)                    */
/*               EOF				: FILE END                                */
/*               �ȊO				: ���s                                    */
/******************************************************************************/
int     ReadKinq( rbuf, pfp )
char		rbuf[];				/* ں��ޓǂݍ����ޯ̧ */
FILE		*pfp;				/* ̧�َ��ʎq */
{
 	char    func_nm[MYAPP_LEN_FNCNM+1];	/* �֐�����     */

 	/* ��������     */
 	strcpy( func_nm, "ReadKinq" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	memset( rbuf, 0x00, sizeof( rbuf ));
	if( fgets( rbuf, KINQ_RECSIZE + 1, pfp ) == NULL ){
		/* �ް��Ȃ�	*/
		return( EOF );
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( strlen( rbuf ) );
}

/******************************************************************************/
/*  �� �� ��  �FLog_out                                                       */
/*  �@�\�T�v  �F���O�t�@�C���o��                                    */
/*  ��    ��  �F                                                              */
/*   ��P���� �F char	file_nm[]	: ���̓t�@�C���|�C���^                    */
/*  �o    ��  �F char	rbuf[];		: �ǂݍ��݃o�b�t�@                        */
/*  ���A���  �F 0�ȏ�				: ����I��(�Ǎ��T�C�Y)                    */
/*               EOF				: FILE END                                */
/*               �ȊO				: ���s                                    */
/******************************************************************************/
int		LogOut( sbt, flg, ecd, msg, fncnm, file, line )
char		sbt[];	
char		flg[];	
char		ecd[];	
char		msg[];	
char		fncnm[] ;
char		file[] ;
long    	line ;
{
		int		ret=RTN_OK;
static	int		init_flg = 0;           /* �Ƽ���׸�    */
static	struct	stcLogMember	gstLogMem ; //  ���O�o�͏��

//------ 1 ----------------------------------------------------------
	if( init_flg == 0 ){
		//  ���O��񏉊��ݒ�	
		memset ( &gstLogMem, '\0', sizeof ( gstLogMem ) ) ;
		strcpy ( gstLogMem.pcAppName,	stcPRM.myp_exefile ) ;
		strcpy ( gstLogMem.pcLoginId,	"DAEMON" ) ;
		init_flg = 1;
	}
//------ 1 ----------------------------------------------------------
	// �g���[�X���
	gstLogMem.eTrcKind=sbt[0];
	// ���s�t���O
	strcpy ( gstLogMem.pcExeFlg,	flg ) ;
	// �G���[�R�[�h
	strcpy ( gstLogMem.pcErrCode,	ecd ) ;
	// ���b�Z�[�W
	strcpy ( gstLogMem.pcMsg,		msg );
	// �֐���
	strcpy ( gstLogMem.pcFncName,	fncnm ) ;

	if(( strcmp( sbt, LT_STA )) == 0 ){
		gstLogMem.eTrcKind='T';
		strcpy( gstLogMem.pcMsg, "start" );
	} else if( strcmp( sbt, LT_END ) == 0 ){
		gstLogMem.eTrcKind='T';
		strcpy( gstLogMem.pcMsg, "end " );
	}

	// LOGOUT
	ret = _ZbmlPutLog( &gstLogMem,	file, line );

	// inifile debug DEBUG
	if( stcPRM.myp_debug == 1 ){
		if( strcmp( ecd, LE_NON ) == 0 ){
			printf( "[%.1s][%s]%s\n"
				,sbt,gstLogMem.pcFncName, gstLogMem.pcMsg );
		} else {
			printf( "[%.1s][%s][%s]%s\n"
				,sbt,gstLogMem.pcFncName,gstLogMem.pcErrCode,gstLogMem.pcMsg);
		}
	}

	return( RTN_OK );
}
/** End of File ***************************************************************/
