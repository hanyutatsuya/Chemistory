/******************************************************************************/
/*   �a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/*   �V�X�e�����F������V�X�e��                                               */
/*   �t�@�C�����FAD103.c                                                      */
/*   �T      �v�F������t�i�˗��W�J�j���ҏ��E�����g���o�^                   */
/*	 OS        �FSUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   ����      �FDB2/C                                                        */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/08     INTEC.INC      CREATE                             */
/*  1.01     2006/05/01     INTEC.INC      SJIS,���ڒǉ��Ή�                  */
/*  1.02     2006/05/03     INTEC.INC      UPDATE �����Ƃ���INI�t�@�C���w��   */
/*  1.03     2006/06/10     INTEC.INC      ���ґ����C�����˗���񐢑�No�X�V   */
/*  1.04     2006/12/12     INTEC.INC      DB�G���[���ُ�I��������           */
/*  1.05     2009/06/29     Merits K.Ameno ��Q�Ǘ�No:0904031814/0904031719�Ή�*/
/*                                         ��������No�W�J�s��C��           */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "bmllog.h"
#include "AD103.h"

/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/
iconv_t		G_ic;						// with iconv
char		G_fnm[256];					// InputFileName
char		G_err[MYAPP_LEN_ERR+1];		// LogMessage(errcode)
char		G_msg[MYAPP_LEN_MSG+1];		// LogMessage
char		G_utkymd[10+1];				// LogMessage(csv)
char		G_irino[13+1];				// LogMessage(csv)
int			G_zssdino;					// LogMessage(csv)
int			G_line;						// InputFileLineNo

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
	G_zssdino=0;
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
			sprintf( G_msg, "�˗��t�@�C���̏��擾(scandir)�Ɏ��s���܂����B" );
			EditCsvMsg( G_msg );
			LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			ret=1;
			break;
		} 

		for( i=0; i < inp_cnt; i++ ){	// <------------------�t�@�C���̌�����
			//------------------
			// 	����擾
			//------------------
			if( GetKjnymd( ) != RTN_OK ){
				sprintf( G_msg, "������N�����̎擾�Ɏ��s���܂����B" );
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
				// INI FILE GENERATION PARAM �ł̏������f
			if( strcmp( stcPRM.myp_gene, "PNC" ) == 0 ){

                //2006.12.08 Kim Jinsuk �G���[���ُ�I��������
				//ret = PncProc( fp );
				ret = PncProc( fp , &li_stopFlg);
				//2006.12.08 Kim Jinsuk�@�G���[���ُ�I��������

			} else {
				ret = NxtProc( fp );
			}
			if( ret == RTN_NG ){
				//printf("#### li_stopFlg %d", li_stopFlg);
				sprintf( G_msg, "[%s]�������ɃG���[���������܂����B"
					,w_infilenm );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm
						, __FILE__, __LINE__ );

                //==> 2006.12.08 Kim Jinsuk DB�G���[���ُ�I��������
                if(li_stopFlg == 1)
				{
					sprintf(G_msg, "[[DB ERROR]]");
 					//printf("li_stopFlg %d", li_stopFlg);
                    LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm
                        , __FILE__, __LINE__ );
					fclose( fp );
					break;
				}
                //<== 2006.12.08 Kim Jinsuk DB�G���[���ُ�I��������				
			}

			//------------------
			// INPUT FILE CLOSE
			//------------------
			fclose( fp );

			//---------------------------
			// �����σt�@�C���̖��̕ύX
			//---------------------------
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
			sprintf( G_msg, "�����ψ˗��t�@�C��[%s]�̖��O��[%s]�ɕύX���܂����B"
					, w_infilenm, w_endfilenm );
			LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

			//------------------
			// �I�����f
			//------------------
				// ���L�������擾

			//==> 2006.12.08 Kim Jinsuk DB�G���[���ُ�I��������
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
			//<== 2006.12.08 Kim Jinsuk DB�G���[���ُ�I��������
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

		//==> 2006.12.08 Kim Jinsuk DB�G���[���ُ�I��������
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
		//<== 2006.12.08 Kim Jinsuk DB�G���[���ُ�I��������
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
fprintf(stderr,"����:���ҏ��o�^����\n" );
fprintf(stderr,"    :������t�i�˗��W�J�j���ҏ��E�����g���f�[�^��o�^���܂�\n" );
fprintf(stderr,"     �˗������擾�f�B���N�g��[%s]\n", stcPRM.ifp_indir );
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
	char    *p_fini;                    /* 1.02 INI FILE ����    */
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
	sprintf( stcPRM.lgp_flog, "%s.log", stcPRM.myp_exefile );
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
    cp = GetIniFile( "MYAPP.PARA", "MYAPP_GENE", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", &stcPRM.myp_gene );
    }
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
	sprintf( G_msg, "app_gene   [%s]",  stcPRM.myp_gene );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "G_zairyo  [%s]",	stcPRM.myp_zairyo );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FGetKjnymd                                                     */
/*  �@�\�T�v  �F����擾                                                    */
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
	struct	{
		int	yyyy;
		int	mm;
		int	dd;
	} BmlDate;

	/* �����ݒ�	*/
	strcpy( func_nm,	"GetKjnymd" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	// ��������̎擾
	memset( &knr,	'\0',	sizeof( struct _SYSKNRMST ) );
	if(( ret = SelSysknrmst( &knr )) == RTN_OK ){
		if( knr.iriendflg[0] == '0' ){ 	// 0:��M�O 1:��M��
			strcpy( stcPRM.myp_kjnymd,	knr.kjnsriymd );

			sprintf( G_msg, "�������[%s]������Ƃ��܂��B"
				, stcPRM.myp_kjnymd );
		} else {

			// �˗�END�t���O��M�ς݂� ���˗������N�����������l�ȊO
		 	if( strcmp( knr.nxirisriymd, INIT_DATE ) == 0 ){
				strcpy( stcPRM.myp_kjnymd,	knr.kjnsriymd );

				sprintf( G_msg,
					"�˗�END��M�ςł������˗������N�����������l�̂��߁A"
					"�������[%s]������Ƃ��܂��B"
					, stcPRM.myp_kjnymd );
			} else {
				strcpy( stcPRM.myp_kjnymd,	knr.nxirisriymd );

				sprintf( G_msg, 
					"�˗�END��M�ς̂��ߎ��˗������N����[%s]������Ƃ��܂��B"
					, stcPRM.myp_kjnymd );
			}
		}
		// TRACE
		LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

	} else {
		ZbmlDateGetToday( &BmlDate );
		sprintf( stcPRM.myp_kjnymd, "%04d-%02d-%02d",
			BmlDate.yyyy, BmlDate.mm, BmlDate.dd );
		// WARNING
		sprintf( G_msg, 
			"��������擾�Ɏ��s�������ߊ�����V�X�e�����t[%s]�Ƃ��܂��B"
			, stcPRM.myp_kjnymd );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	}
	
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
/*  �� �� ��  �FPncProc                                                       */
/*  �@�\�T�v  �F�o�m�b�˗��t�@�C������                                        */
/*  ��    ��  �F                                                              */
/*   ��P���� �F FILE	pfp	: ���̓t�@�C�����ʎq                              */
//   ��2 ���� :  int    stopValue : �I�����ʎq�@�@�@�@�@  �@�@�@�@�@�@�@�@�@�@*/�@
/*  �o    ��  �F �Ȃ�                                                         */
/*  ���A���  �F INT                                                          */
/*               RTN_OK     : ����                                            */
/*               RTN_NG     : ���s                                            */
/******************************************************************************/
//==> 2006.12.08 Kim Jinsuk
//int       PncProc( pfp )
int     PncProc( pfp , stopValue)
//<== 2006.12.08 Kim Jinsuk
FILE    	*pfp;
int         *stopValue;
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����		*/
	int		ret;							/* �֐��߂�l	*/

	/* �˗���MPNC format(S-JIS) */
	struct	Z01SJTR			z01sjitr;	/* PNC��M�g���[���[(S-JIS) */
	struct	Z02SJIR1		z02sjir1;	/* PNC��M����(S-JIS) */
	struct	Z04SJIR2		z04sjir2;	/* PNC��M����(S-JIS) */

	struct	_KANJYA			kan;		/* ���ҏ��	*/
	struct	_CHIKENZOK		try;		/* �����g������	*/
	struct	CNT				stcCNT;		/* �������		*/

	char	rbuf[PNC_RECSIZE*2+1];		/* �ǂݍ��ݴر		*/
	char	w_key[MYAPP_LEN_KEY+1];
	int		w_key_r2=0;
	char	w_str[200];
	int		wcnt_kan=0;					/* ���ҏ��o�^����*/
	int		wcnt_try=0;					/* �����g�������o�^����	*/
	int		w_cnt;
	int		i,j;						/* index		*/

    //2006.12.08 Kim Jinsuk DB�G���[��
	int     nSQLErrorValue;

	/* �����ݒ�	*/
	strcpy( func_nm,	"PncProc" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �ر	*/
	ret = RTN_OK;

	stcCNT.cnt_irai	= stcCNT.cnt_irai_err = stcCNT.cnt_irai_del = 0;
	stcCNT.cnt_hd = stcCNT.cnt_tr = stcCNT.cnt_r1 = stcCNT.cnt_r2 = 0;
	stcCNT.cnt_kanjya = stcCNT.cnt_chiken = 0;
	memset( w_key, '\0', sizeof( w_key ));

	sprintf( G_msg,	"��t�i�˗��W�J�j ���ҏ��E�����g�������e�[�u��"
					"�쐬�J�n : �˗������t�@�C����[%s]", G_fnm );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	// DEBUG
	sprintf( G_msg, "INFILE[%s] START!!----->", G_fnm );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	/* ̧�ق̓Ǎ�(S-JIS)��ں��ގ��ʎq�̔���	*/
	while( ReadPnc( rbuf, pfp ) != EOF ){	// read while start ----------->
		/* �׸ޗ޸ر	*/
		stcCNT.cnt_irai++;	/* ���͌���     */
		G_line=stcCNT.cnt_irai;
		memset( G_utkymd,	'\0', sizeof( G_utkymd ));
		memset( G_irino,	'\0', sizeof( G_irino ));
		G_zssdino=0;

		// DEBUG
		strcpy( G_msg, "}" );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
		sprintf( G_msg, "���͌���(%d) size(%d) sbt[%.2s] ===============>{"
				, stcCNT.cnt_irai, strlen( rbuf ), rbuf );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

		/* --------------------------------	*/
		/*	PNC �t�@�C���ǂݍ��݃`�F�b�N	*/
		/* --------------------------------	*/
		// ���R�[�h�T�C�Y�`�F�b�N
		if( strlen( rbuf ) != ( PNC_RECSIZE )){
			// ERROR
			stcCNT.cnt_irai_err++;
			sprintf( G_msg, "�ǂݍ��݃��R�[�h�T�C�Y�G���[[%d]", strlen( rbuf ));
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			continue;
		}
		// �w�b�_�[
		if( strncmp( rbuf, "HD", 2 ) == 0 ){
			stcCNT.cnt_hd++;
			// �P���ڂ̓w�b�_�[	
			if( stcCNT.cnt_irai != 1 ){
				// ERROR
				sprintf( G_msg, "�P���ڂ��w�b�_�[�ł͂���܂���B[%.2s]", rbuf);
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, 
								__FILE__, __LINE__);
			}
			// DEBUG
			strcpy( G_msg, "�w�b�_�[��� SKIP" );
			LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

			continue;
		} else
		// �g���[���[ ���R�[�h���`�F�b�N
		if( strncmp( rbuf, "TR", 2 ) == 0 ){
			stcCNT.cnt_tr++;
			memcpy( &z01sjitr, rbuf, sizeof( struct Z01SJTR ) );
			if( memcmp( z01sjitr.c_reccnt, MYAPP_SPACE10, 8 ) == 0 ){
				// ERROR
				sprintf( G_msg, "�g���[���[�̕������R�[�h�������ݒ�ł��B"
						"[%.8s]", z01sjitr.c_reccnt );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, 
								__FILE__, __LINE__);
				continue;
			}
			// ���������`�F�b�N
			memset( w_str, '\0', sizeof( w_str ));
			w_cnt = atol( strncpy( w_str, z01sjitr.c_reccnt, 8 ));
			if( stcCNT.cnt_irai != w_cnt ){
				// ERROR
				sprintf( G_msg, "�g���[���[�̕������R�[�h���ƈ�v���܂���B"
						"TR   [%d]->[%d]", w_cnt, stcCNT.cnt_irai );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, 
								__FILE__, __LINE__);
			}
			// �_�������`�F�b�N
			memset( w_str, '\0', sizeof( w_str ));
			w_cnt = atol( strncpy( w_str, z01sjitr.c_reccnt01, 8 ));
			if( stcCNT.cnt_r1 != w_cnt ){
				// ERROR
				sprintf( G_msg, "�g���[���[�̘_�����R�[�h���ƈ�v���܂���B"
						"TR-R1[%d]->[%d]", w_cnt, stcCNT.cnt_r1 );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, 
								__FILE__, __LINE__);
			}
			memset( w_str, '\0', sizeof( w_str ));
			w_cnt = atol( strncpy( w_str, z01sjitr.c_reccnt02, 8 ));
			if( stcCNT.cnt_r2 != w_cnt ){
				// ERROR
				sprintf( G_msg, "�g���[���[�̘_�����R�[�h���ƈ�v���܂���B"
						"TR-R2[%d]->[%d]", w_cnt, stcCNT.cnt_r2 );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, 
								__FILE__, __LINE__);
			}
			// DEBUG
			sprintf( G_msg, "�g���[���[��� SKIP" );
			LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

			// �g���[���[�͋����I�� KEY-BREAK
			memset( w_key, '9', MYAPP_LEN_KEY );
		}

		// �g���[���[��̃��R�[�h���݂̓G���[
		if(( stcCNT.cnt_tr == 1 )&&( strncmp( rbuf, "TR", 2 ) != 0 )){
			// ERROR
			sprintf( G_msg, "�g���[���[��Ƀ��R�[�h���܂܂�Ă��܂��B[%.2s]"
					,rbuf );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}

		// 1���ڂ�KEY-BREAK�����Ȃ�
		if( stcCNT.cnt_irai == 2 ){
			memcpy( w_key, &rbuf[2], MYAPP_LEN_KEY );
		}
		// R2�̎���R1��ǂݍ��񂾏ꍇ�� �����I��KEY-BREAK
		if( w_key_r2 != 0 ){
			memset( w_key, '9', MYAPP_LEN_KEY );
		}
		/* --------------------------------	*/
		/*	���� 							*/
		/* --------------------------------	*/
		// DEBUG
		sprintf( G_msg, "���� sbt[%.2s]in[%.19s] key[%s]"
				, rbuf, &rbuf[2], w_key );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

//-----< R1,R2��1TRANSACTION�Ƃ��邽��KEY�̔�r���s�� >------------------
		if( memcmp( w_key, &rbuf[2], MYAPP_LEN_KEY ) != 0 ){
			// DEBUG
			sprintf( G_msg, "KEY-BREAK���� : ret[%d]kan[%d]try[%d]", 
					ret, wcnt_kan, wcnt_try );
			LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

			/* �G���[�����`�F�b�N	*/
			if( ret == RTN_OK ){
				if(( ret = Ydbcommit( )) != RTN_OK ){
						// ERROR
					strcpy( G_msg, "DB2��COMMIT�Ɏ��s���܂����B\n" );
					EditCsvMsg( G_msg );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__ );
					stcCNT.cnt_kanjya -= wcnt_kan;
					stcCNT.cnt_chiken -= wcnt_try;
				}
				stcCNT.cnt_kanjya += wcnt_kan;
				stcCNT.cnt_chiken += wcnt_try;
			} else {
				// ERROR
				strcpy( G_msg, "�f�[�^�����ŃG���[���������܂����B" );
				EditCsvMsg( G_msg );
				LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__);

		        //2006.12.08 Kim Jinsuk DB�G���[���ُ�I��������
        		nSQLErrorValue = atoi(G_err);

				if(( ret = Ydbrollback( )) != RTN_OK ){
						// ERROR
					strcpy( G_msg, "DB2��ROLLBACK�Ɏ��s���܂����B\n"  );
					EditCsvMsg( G_msg );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm,__FILE__, __LINE__);
				}

        		//==> 2006.12.08 Kim Jinsuk DB�G���[���ُ�I��������
        		if((nSQLErrorValue< 0)&& (nSQLErrorValue != -911)&&(nSQLErrorValue !=-803))
        		{
            		*stopValue = 1;
            		sprintf(G_msg, "##### DB�G���[�@�����@##### %d", nSQLErrorValue);

            		//printf("nSQLErrorValue %d stopValue %d \n",nSQLErrorValue, stopValue);
            		return(RTN_NG);
        		}
        		//<== 2006.12.08 Kim Jinsuk DB�G���[���ُ�I��������

			}
			// commit ����
			wcnt_kan = wcnt_try = 0;
			memcpy( w_key, &rbuf[2], MYAPP_LEN_KEY );
			w_key_r2=0;
		}
//-----< R1 >---------------------------------------------------------------
		ret = RTN_OK;
		if( strncmp( rbuf, "R1", 2 ) == 0 ){	// ���ґ���
			stcCNT.cnt_r1++;
			memcpy( &z02sjir1,	rbuf, sizeof( struct Z02SJIR1 ) );
			memset( &kan,		0x00, sizeof( struct _KANJYA ));
			do {		/* Do-while�͂P��̂ݎ��s	�@	*/
				/* �ҏW */
				if(( ret= EditPncKanjya( &z02sjir1, &kan )) != RTN_OK ){
					if( ret == RTN_SKIP ){
						// �폜�˗���M
						stcCNT.cnt_irai_del++;
						ret = RTN_OK;
						break;
					} else {
						/* �װ*/
						ret = RTN_NG;
						break;
					}
				}
				/* ���ʉӏ��̕ҏW */
				if( EditCommonKanjya( &kan ) != RTN_OK ){
					/* �װ*/
					ret = RTN_NG;
					strcpy( G_msg, "EditCommonKanjya ==== \n"  );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm,__FILE__, __LINE__);
					break;
				}

/*  1.05     2009/06/29     Merits K.Ameno ��Q�Ǘ�No:0904031814/0904031719�Ή� -->*/
			/*** 					<<<<<<<NOTE>>>>>>>						  ***/
			/*** �����C��FLG�������Ă���ꍇ�A��������ʃe�[�u���֑ޔ�����  ***/
			/*** Insert����B���̎��̑�������No�͌Œ�B�������Ȃ�0            ***/
			/*** �������z�����Ȃ�100                                          ***/
			/*** ���邱�Ƃ͂����A�����̃��R�[�h���X�V����B���̍ہA��������No ***/
			/*** �ŐV�̂��̂�Update����                                       ***/
				if( kan.zssflg[0] == '1' ){			/* �����C��FLG�������Ă���ꍇ */
				/* �����C���@�����v�Z�N���̓����ɔ����A�����C�����͎�荞�܂Ȃ��悤�ɕύX  */
					ret = RTN_OK;
					break;
					
//					ret = SelKanjya( &kan);			/* �����e�[�u�����瓯���ґ��������擾 */
//					if ( ret == RTN_OK ){			/* ������񂪎�ꂽ�I(���ɑ��݂���) */
//				/*** �������̑ޔ����� ***/
//						ret = InsShusei_Kanjya();	/* �����C���e�[�u���֎���Ă�������Insert */
//						if( ret != RTN_OK ){		/* Insert�Ɏ��s���� */
//							ret = RTN_NG;			/* ���s���ʂ�NG�ɂ��� */
//							break;					/* �����I�� */
//						}
//				/*** �������̍폜���� ***/
//						ret = DelKanjya( &kan );	/* ���҃e�[�u��������������폜 */
//						if( ret != RTN_OK ){		/* Delete�Ɏ��s���� */
//							ret = RTN_NG;			/* ���s���ʂ�NG�ɂ��� */
//							break;					/* �����I�� */
//						}
//					}
//					else if( ret == RTN_DBERR ){	/* DB�G���[�������ꍇ */
//						ret = RTN_NG;				/* ���s���ʂ�NG�ɂ��� */
//						break;						/* �����I�� */
//					}
//					/*** �����e�[�u������DB�G���[���N�����Ă��Ȃ��̂Ɏ��Ȃ� ***/
//					/*** �������z���m��Ȃ̂ŁA���̂܂ܓW�J����B����No��100  ***/
				}									/* �ʏ�̑����W�J And �d�����ޔ��������� */
				ret = InsKanjya( &kan );			/* ���ґ�����Insert���� */

				if( ret != RTN_OK ){				/* ���ґ������X�V�����s���Ă����� */
/*  1.05     2009/06/29     Merits K.Ameno ��Q�Ǘ�No:0904031814/0904031719�Ή� <--*/
					/* INSERT */
// 				if(( ret = InsKanjya( &kan )) != RTN_OK ){
					if( ret != MYAPP_RTN_DUP ){
						// ERROR
						strcpy( G_msg,
							"���ҏ��o�^���ɃG���[���������܂����B" );
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_INS, G_err, G_msg, func_nm, 
										__FILE__, __LINE__);
						ret = RTN_NG;
						break;
					}
					// AS/400����̌���˗���UPDATE
						// AS/400����̌���˗���?
					if( SelKinkyuIrai( &kan ) <= 0 ){
						// �ً}���ڂ����݂��Ȃ����f�[�^�d��
						strcpy( G_msg, "���Ɋ��ҏ�񂪑��݂��܂��B" );
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, 
									__FILE__, __LINE__);
						ret = RTN_NG;
						break;
					}
						//	��������No�̍ő�l�擾
					if( SelKanjyaZssdinoMax( &kan ) != RTN_OK ){
						// ERROR
						strcpy( G_msg, 
							"AS/400����˗��̊��ҏ��X�V�Ώێ擾��"
							"���s���܂����B" );
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, 
									__FILE__, __LINE__);
						ret = RTN_NG;
						break;
					}
					if( UpdKinkyuKanjya( &kan ) != RTN_OK ){
						// ERROR -> LOG OUT ��.sqc�ɂ�
						//strcpy( G_msg,
						//	"AS/400����˗��̊��ҏ��X�V�Ɏ��s���܂����B" );
						//EditCsvMsg( G_msg );
						//LogOut( LT_ERR, LX_INS, G_err, G_msg, func_nm, 
						//				__FILE__, __LINE__);
						ret = RTN_NG;
						break;
					} 
					ret = RTN_OK;
				}
//				/* 1.03 �����C�����͈˗����.����No���X�V���� */
//				if( kan.zssflg[0] == '1' ){
//					if( UpdIraiZssdino( &kan ) != RTN_OK ){
//						// ERROR
//						strcpy( G_msg, 
//							"���ҏ��X�V�Ώۂ̈˗���񐢑�No�X�V��"
//							"���s���܂����B" );
//						EditCsvMsg( G_msg );
//						LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, 
//									__FILE__, __LINE__);
//						ret = RTN_NG;
//						break;
//					}
//				} 
				wcnt_kan++;
			} while( wcnt_kan < 1 );
//-----< R2 >---------------------------------------------------------------
		} else if( strncmp( rbuf, "R2", 2 ) == 0 ){ // �����g��
			stcCNT.cnt_r2++;
			w_key_r2++;
			memcpy( &z04sjir2, rbuf, sizeof( struct Z04SJIR2 ) );
			memset( &try,   0x00, sizeof( struct _CHIKENZOK ));
			do {		/* Do-while�͂P��̂ݎ��s   �@  */
				/* �ҏW */
				if( EditPncChikenzok( &z04sjir2, &try ) != RTN_OK ){
					/* �װ*/
					ret = RTN_NG;
					break;
				}
				// ���ґ����̐���NO�������p��
				try.zssdino = kan.zssdino;
				/* ���ʉӏ��̕ҏW */
				if( EditCommonChikenzok( &try ) != RTN_OK ){
					/* �װ*/
					ret = RTN_NG;
					break;
				}
				// R1������R2�݂̂̓G���[
				if( wcnt_kan == 0 ){
					// error
					ret = RTN_NG;
					break;
				}
				// Kanjya.tktyflg UPDATE
				if( UpdKanjyaTktyflg( &kan ) != RTN_OK ){
					/* �װ*/
					ret = RTN_NG;
					break;
				}
				/* INSERT */
				if( InsChikenzok( &try ) != RTN_OK ){
					/* �װ*/
					ret = RTN_NG;
					break;
				}
				wcnt_try++;
			} while( wcnt_try < 1 );
		}
		if( ret != RTN_OK ){
			// ERROR
			stcCNT.cnt_irai_err++ ;	 /* error */
		}
	}   // <---------------------------------------------------read while end

//-----< 1FILE READ END >-------------------------------------------------------
	// �g���[���[�����̓G���[
	if( stcCNT.cnt_tr == 0 ){
		// error msg
		// ERROR
		strcpy( G_msg, "�g���[���[������܂���B" );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
	}
	// �g���[���[������COMMIT���K�v�ȏꍇ�̍l��
		/* �G���[�����`�F�b�N	*/
	if( ret == RTN_OK ){
		if(( wcnt_kan != 0 ) || ( wcnt_try != 0 )){
        	if(( ret = Ydbcommit( )) != RTN_OK ){
				sprintf( G_msg, "DB2��COMMIT�Ɏ��s���܂���\n" );
				EditCsvMsg( G_msg );
				LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
								__FILE__, __LINE__);
				stcCNT.cnt_kanjya -= wcnt_kan;
				stcCNT.cnt_chiken -= wcnt_try;
			}
			stcCNT.cnt_kanjya += wcnt_kan;
			stcCNT.cnt_chiken += wcnt_try;
		}
	} else {
		strcpy( G_msg,"�f�[�^�����ŃG���[���������܂����B" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__);
       

		//2006.12.08 Kim Jinsuk DB�G���[���ُ�I��������
       	nSQLErrorValue = atoi(G_err);

 	   if(( ret = Ydbrollback( )) != RTN_OK ){
			sprintf( G_msg, "DB2��ROLLBACK�Ɏ��s���܂���\n"  );
			EditCsvMsg( G_msg );
				LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
		}
       
		
		//==> 2006.12.08 Kim Jinsuk DB�G���[���ُ�I��������
       	if((nSQLErrorValue< 0)&& (nSQLErrorValue != -911)&&(nSQLErrorValue !=-803))
       	{
           	*stopValue = 1;
			sprintf(G_msg, "##### DB�G���[�@�����@##### %d", nSQLErrorValue);
        
			//printf("nSQLErrorValue %d stopValue %d \n",nSQLErrorValue, stopValue);
			return(RTN_NG);
        }
		//<== 2006.12.08 Kim Jinsuk DB�G���[���ُ�I��������

	}
	// DEBUG
	sprintf( G_msg, "�ŏI���͌���(%d)kan[%d]chiken[%d]", 
		stcCNT.cnt_irai,stcCNT.cnt_kanjya,stcCNT.cnt_chiken  );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	memset( G_utkymd,	'\0', sizeof( G_utkymd ));
	memset( G_irino,	'\0', sizeof( G_irino ));
	G_zssdino=0;
	G_line=0;

	// TRACE
    sprintf( G_msg, "    ���ҏ��E�����g���e�[�u���쐬�������I�����܂���" );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "        �S�˗�����                  �F%10d��"
														,stcCNT.cnt_irai );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            HD(SKIP)                �F%10d��"
        												,stcCNT.cnt_hd );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            TR(SKIP)                �F%10d��"
        												,stcCNT.cnt_tr );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            �폜�˗�����(SKIP)      �F%10d��"
														,stcCNT.cnt_irai_del );
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

    sprintf( G_msg, "            �����g�����o�^����    �F%10dں���"
														,stcCNT.cnt_chiken );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  �� �� ��  �FReadPnc                                                       */
/*  �@�\�T�v  �F�o�m�b�˗��t�@�C���ǂݍ���                                    */
/*  ��    ��  �F                                                              */
/*   ��P���� �F char	file_nm[]	: ���̓t�@�C���|�C���^                    */
/*  �o    ��  �F char	rbuf[];		: �ǂݍ��݃o�b�t�@                        */
/*  ���A���  �F 0�ȏ�				: ����I��(�Ǎ��T�C�Y)                    */
/*               EOF				: FILE END                                */
/*               �ȊO				: ���s                                    */
/******************************************************************************/
int     ReadPnc( rbuf, pfp )
char		rbuf[];				/* ں��ޓǂݍ����ޯ̧ */
FILE		*pfp;				/* ̧�َ��ʎq */
{
 	char    func_nm[MYAPP_LEN_FNCNM+1];	/* �֐�����     */

 	/* ��������     */
 	strcpy( func_nm, "ReadPnc" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	memset( rbuf, 0x00, sizeof( rbuf ));
	if( fgets( rbuf, PNC_RECSIZE + 1, pfp ) == NULL ){
		/* �ް��Ȃ�	*/
		return( EOF );
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( strlen( rbuf ) );
}

/******************************************************************************/
/*  �� �� ��  �FNxtProc                                                       */
/*  �@�\�T�v  �F������˗��t�@�C������                                        */
/*  ��    ��  �F                                                              */
/*   ��P���� �F FILE	fp	: ���̓t�@�C�����ʎq                              */
/*  �o    ��  �F �Ȃ�                                                         */
/*  ���A���  �F INT                                                          */
/*               RTN_OK     : ����                                            */
/*               RTN_NG     : ���s                                            */
/******************************************************************************/
int		NxtProc( nfp )
FILE    	*nfp;
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����		*/
	int		ret;							/* �֐��߂�l	*/

	/* �����ݒ�	*/
	strcpy( func_nm, "NxtProc" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  �� �� ��  �FReadNxt                                                       */
/*  �@�\�T�v  �F������˗��t�@�C���ǂݍ���                                    */
/*  ��    ��  �F                                                              */
/*   ��P���� �F char	file_nm[]	: ���̓t�@�C���|�C���^                    */
/*  �o    ��  �F char	rbuf[];		: �ǂݍ��݃o�b�t�@                        */
/*  ���A���  �F 0�ȏ�				: ����I��(�Ǎ��T�C�Y)                    */
/*               EOF				: FILE END                                */
/*               �ȊO				: ���s                                    */
/******************************************************************************/
int     ReadNxt( rbuf, nfp )
char		rbuf[];				/* ں��ޓǂݍ����ޯ̧ */
FILE		*nfp;				/* ̧�َ��ʎq */
{
 	char    func_nm[MYAPP_LEN_FNCNM+1];            /* �֐�����     */

 	/* ��������     */
 	strcpy( func_nm, "ReadNxt" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	memset( rbuf, 0x00, sizeof( rbuf ));
	if( fgets( rbuf, NXT_RECSIZE + 1, nfp ) == NULL ){
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
