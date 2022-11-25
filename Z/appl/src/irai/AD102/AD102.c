/******************************************************************************/
/*   �a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/*   �V�X�e�����F������V�X�e��                                               */
/*   �t�@�C�����FAD102.c                                                      */
/*   �T      �v�F������t�i�˗��W�J�j�˗����o�^                             */
/*	 OS        �FSUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   ����      �FDB2/C                                                        */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/28     INTEC.INC      CREATE                             */
/*  1.01     2006/05/01     INTEC.INC      SJIS,���ڒǉ��Ή�                  */
/*  1.02     2006/05/03     INTEC.INC      UPDATE �����Ƃ���INI�t�@�C���w��   */
/*  1.03     2006/06/10     INTEC.INC      ���ґ����C�����˗���񐢑�No�X�V   */
/*  1.04     2006/06/26     INTEC.INC      �����������ړo�^�{����G�ҏW�ǉ�    */
/*  1.05     2006/08/15     INTEC.INC      �����Đ��̎����������ڍX�V�Ή�     */
/*  2.01     2006/09/28     INTEC.INC      �W������404�̒ǉ�                  */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "bmllog.h"
#include "AD102.h"

/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/
iconv_t		G_ic;						// with iconv
char		G_fnm[256];					// InputFileName
char		G_err[MYAPP_LEN_ERR+1];		// LogMessage(errcode)
char		G_msg[MYAPP_LEN_MSG+1];		// LogMessage
char		G_utkymd[10+1];				// LogMessage(csv)
char		G_irino[13+1];				// LogMessage(csv)
char		G_kntno[13+1];				// LogMessage(csv)
int			G_zssdino;					// LogMessage(csv)
char		G_kmkcd[7+1];				// LogMessage(csv)
int			G_line;						// InputFileLineNo

struct		_KJNMST		*pKjn;

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

	struct	SHM stcShm;					// �I�����f���L������
	int		li_stopFlg = 0;				// �I�����f
	
	/*=====================================================*/
	/*	�o�b�N�O���E���h���s                               */
	/*=====================================================*/

/*
	if ( daemon ( 0,  1) < 0 ) {
			exit( 1 );
	}
*/


	/*=====================================================*/
	/*	�����ݒ�                                           */
	/*=====================================================*/
	strcpy( func_nm,	"main" );
	memset( G_msg,		'\0', sizeof( G_msg ) );
	memset( G_utkymd,	'\0', sizeof( G_utkymd ) );
	memset( G_irino,	'\0', sizeof( G_irino ) );
	memset( G_kntno,	'\0', sizeof( G_kntno ) );
	memset( G_kmkcd,	'\0', sizeof( G_kmkcd ) );
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
		sprintf( G_msg, "DB2�Ƃ̐ڑ��Ɏ��s���܂����B" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		exit( 1 );
     }

	// 	����擾
	GetKjnymd( );

	// ��l�}�X�^�擾
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
	for( ; ; ){		// ......................................... daemon start
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
			//  ����擾
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
				// �擪�P�����ڂł̏������f N:������ P:PNC
				// INI FILE GENERATION PARAM �ł̏������f
			if( strcmp( stcPRM.myp_gene, "PNC" ) == 0 ){

                //2006.12.08 Kim Jinsuk 
				//ret = PncProc( fp );
                ret = PncProc(fp, &li_stopFlg);
                //2006.12.08 Kim Jinsuk

			} else {
				ret = NxtProc( fp );
			}
			if( ret == RTN_NG ){
				sprintf( G_msg, "[%s]�������ɃG���[���������܂����B"
					,w_infilenm );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm
						, __FILE__, __LINE__ );

                //==> 2006.12.08 Kim Jinsuk DB�G���[��
				if(li_stopFlg== 1) 
				{
                	sprintf(G_msg, "[[DB ERROR]]");
					//sprintf(G_msg, "li_stopFlg %d", li_stopFlg);
					//<== 2006.12.08 Kim Jinsuk DB�G���[��
					LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm
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
		}		// -----------------------------------------> �t�@�C���̌�����

		// scandir �t�@�C������free
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
				sprintf( G_msg,
					"���L�����������Ɏ��s�������߁A�������I�����܂��B" );
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

	}	// ...................................................... daemon for

	/*=====================================================*/
	/*	�I������                                           */
	/*=====================================================*/
	// ICONV CLOSE
	// 1.01 DELL	iconv_close( G_ic );

	/* DB2�Ƃ̐ڑ����� */
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
fprintf(stderr,"����:�˗����o�^����\n" );
fprintf(stderr,"    :������t�i�˗��W�J�j�˗�����o�^���܂�\n" );
fprintf(stderr,"     �˗��擾�f�B���N�g��[%s]\n", stcPRM.ifp_indir );
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
	// ���O�I�[�v��
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
        sscanf( cp, "%s", stcPRM.myp_gene );
    }
    cp = GetIniFile( "MYAPP.PARA", "MYAPP_LOGNM2", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.lgp_flog );
    }
    cp = GetIniFile( "MYAPP.PARA", "MYAPP_SLEEP", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%d", &stcPRM.myp_sleep );
    }
    cp = GetIniFile( "MYAPP.PARA", "MYAPP_SEDAI", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%d", &stcPRM.myp_sedai );
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
	sprintf( G_msg, "G_flog    [%s]",	stcPRM.lgp_flog );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "G_sleep   [%d]",	stcPRM.myp_sleep );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "app_gene   [%s]",	stcPRM.myp_gene );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "G_sedai   [%d]",	stcPRM.myp_sedai );
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

	struct  _SYSKNRMST  knr;
	struct	{
		int	yyyy;
		int	mm;
		int	dd;
	} BmlDate;

	/* �����ݒ�	*/
	strcpy( func_nm,	"GetKjnymd" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	// ��������̎擾
	memset( &knr,   '\0',   sizeof( struct _SYSKNRMST ) );
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
/*  �o    ��  �F �Ȃ�                                                         */
/*  ���A���  �F INT                                                          */
/*               RTN_OK     : ����                                            */
/*               RTN_NG     : ���s                                            */
/******************************************************************************/
//==> 2006.12.08 Kim Jinsuk
//int		PncProc( pfp )
int		PncProc( pfp , stopValue)
FILE    	*pfp;
int         *stopValue;
//<== 2006.12.08 Kim Jinsuk
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����		*/
	int		ret;							/* �֐��߂�l	*/

	/* �˗���MPNC format(S-JIS) */
	struct	Z01SJTR			z01sjitr;	/* PNC��M�g���[���[(S-JIS) */
	struct	Z05SJIR1		z05sjir1;	/* PNC��M�˗�(S-JIS) */
	struct	Z11SJIRF		z11sjirf;	/* PNC��MEND(S-JIS) */

	struct	_IRAI			iri;		/* �˗����	*/
	struct	CNT				stcCNT;		/* �������		*/

	struct	JIDOIRAI		*pJir;		// 1.04 ADD

	char	rbuf[PNC_RECSIZE*2+1];		/* �ǂݍ��ݴر		*/
	char	w_key[MYAPP_LEN_KEY+1];
	char	w_key_del[1+1];
	char	w_str[200];
	int		w_max_zssdino;
	int		wcnt_iri=0;					/* �˗����o�^����*/
	int		wcnt_iri_del=0;				/* �˗����폜�X�V����*/
	int		wcnt_rf=0;					/* �����g�������o�^����	*/
	int		w_cnt;
	int		i,j;						/* index		*/
	int		jd_max;						// 1.04 ADD �����������ڐ�
	char    w_age[3+1];           		/* 1.04 ADD �N��         */
    char    w_age_kbn[1+1];       		/* 1.04 ADD �N��敪         */

	//2006.12.08 Kim Jinsuk DB�G���[��
	int     nSQLErrFlag;                     

	/* �����ݒ�	*/
	strcpy( func_nm,	"PncProc" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �ر	*/
	ret = RTN_OK;

	stcCNT.cnt_irai=stcCNT.cnt_irai_err=0;
	stcCNT.cnt_hd=stcCNT.cnt_tr=stcCNT.cnt_r1=stcCNT.cnt_rf=stcCNT.cnt_oth=0;
	stcCNT.cnt_dbirai=stcCNT.cnt_dbirai_del=stcCNT.cnt_end=0;
	stcCNT.cnt_dbirai_jdi=0;
	memset( w_key, '\0', sizeof( w_key ));
	memset( w_key_del, '\0', sizeof( w_key_del ));

	sprintf( G_msg,	"��t�i�˗��W�J�j �˗����e�[�u���쐬�J�n : " 
					"�˗��t�@�C����[%s]", G_fnm );
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
		memset( G_kntno,	'\0', sizeof( G_kntno ));
		memset( G_kmkcd,	'\0', sizeof( G_kmkcd ));
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
		//if( strlen( rbuf ) != ( PNC_RECSIZE + 1 ))[
			// ERROR
			//stcCNT.cnt_irai_err++ ;	
			sprintf( G_msg, "�ǂݍ��݃��R�[�h�T�C�Y�G���[[%d]", strlen( rbuf ));
			EditCsvMsg( G_msg );
			LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

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
/*==============
DEL			memset( w_str, '\0', sizeof( w_str ));
DEL			w_cnt = atol( strncpy( w_str, z01sjitr.c_reccnt02, 8 ));
DEL			if( stcCNT.cnt_rf != w_cnt ){
DEL				// ERROR
DEL				sprintf( G_msg, "�g���[���[�̘_�����R�[�h���ƈ�v���܂���B"
DEL						"TR-R2[%d]->[%d]", w_cnt, stcCNT.cnt_r2 );
DEL				EditCsvMsg( G_msg );
DEL				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, 
DEL								__FILE__, __LINE__);
DEL			}
*/
			// �g���[���[�͋����I�� KEY-BREAK
			memset( w_key, '9', MYAPP_LEN_KEY );

		} else 
			// R2 �����g���͓ǂݔ�΂�
		if( strncmp( rbuf, "R2", 2 ) == 0 ){
			stcCNT.cnt_oth++;
			continue;
		}

		// �g���[���[��̃��R�[�h���݂̓G���[
		if(( stcCNT.cnt_tr == 1 )&&( strncmp( rbuf, "TR", 2 ) != 0 )){
			// ERROR
			sprintf( G_msg, "�g���[���[��Ƀ��R�[�h���܂܂�Ă��܂��B[%.2s]"
					,rbuf );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}
		// RF���TR�ȊO�̃��R�[�h���݂̓G���[
		if(( ( stcCNT.cnt_end == 1 ) || ( wcnt_rf == 1 ))
	 	 &&( strncmp( rbuf, "TR", 2 ) != 0 )){
			// ERROR
			sprintf( G_msg, "�˗��d�m�c�̌�Ƀ��R�[�h���܂܂�Ă��܂��B[%.2s]"
					,rbuf );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}

		// 1���ڂ�KEY-BREAK�����Ȃ�
		if( stcCNT.cnt_irai == 2 ){
			memcpy( w_key,		&rbuf[2],	MYAPP_LEN_KEY );
			memcpy( w_key_del,	&rbuf[77],	1 );
		}
		/* --------------------------------	*/
		/*	���� 							*/
		/* --------------------------------	*/
		// DEBUG
		sprintf( G_msg, "���� sbt[%.2s]in[%.19s] key[%s]"
				, rbuf, &rbuf[2], w_key );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

//-----< ����BML����E�˗���NO�ō폜�t���O�����������̂�
//		                    1TRANSACTION�Ƃ��邽��KEY�̔�r���s�� >------------
		if(( memcmp( w_key,		&rbuf[2],  MYAPP_LEN_KEY ) != 0 )
		 ||( memcmp( w_key_del, &rbuf[77], 1 ) != 0 )){
			// DEBUG
			sprintf( G_msg, "KEY-BREAK���� : ret[%d]iri[%d]del[%d]rf[%d]"
					"------------------------",
					ret, wcnt_iri, wcnt_iri_del, wcnt_rf );
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
				// �폜�̏ꍇ�́A���������������s��Ȃ�
				if( w_key_del[0] == 0 ){
					break;
				}
				// �����������ڂ̗L���`�F�b�N
        		if(( jd_max=SelCountJkmkmst( iri.utkymd
											, iri.irino, iri.sriymd )) < 1 ){
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
				strcpy( pJir[0].sIri.utkymd,		iri.utkymd );
				strcpy( pJir[0].sIri.irino,			iri.irino );
				strcpy( pJir[0].sIri.sriymd,		iri.sriymd );
				// �Ώۃf�[�^���̎擾
				if( SelJidoirai( pJir, jd_max ) !=  RTN_OK ){
					sprintf( G_err, "%d", errno );
					sprintf( G_msg, "��l�}�X�^�̓ǂݍ��݂Ɏ��s���܂����B" );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm,
									__FILE__, __LINE__ );
					free( pJir );
					ret=RTN_NG;
					break;
				}
				for( i = 0; i < jd_max; i++ ){
					// EDIT
					strcpy( pJir[i].age,		w_age );
					strcpy( pJir[i].agekbn,		w_age_kbn );
					// if( EditJidoIrai( &pJir[i] ) != RTN_OK )[
					if( EditJidoIrai( &(pJir[i]) ) != RTN_OK ){
						// ERROR
						strcpy( G_msg,
							"���������˗����ҏW���ɃG���[���������܂����B" );
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, 
										__FILE__, __LINE__);
						ret = RTN_NG;

						break;
					}
					memcpy( &iri, &pJir[i].sIri, sizeof( struct _IRAI ));
					/* INSERT */
					if( InsIrai( &iri ) != RTN_OK ){
						// ERROR
						strcpy( G_msg,
							"���������˗����o�^���ɃG���[���������܂����B" );
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, 
										__FILE__, __LINE__);
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
				if(( ret = Ydbcommit( )) != RTN_OK ){
						// ERROR
					strcpy( G_msg, "DB2��COMMIT�Ɏ��s���܂����B\n" );
					EditCsvMsg( G_msg );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__ );
					stcCNT.cnt_dbirai		-= wcnt_iri;
					stcCNT.cnt_dbirai_del	-= wcnt_iri_del;
					stcCNT.cnt_end			-= wcnt_rf;
					// 1.04 ADD
					stcCNT.cnt_dbirai_jdi	-= jd_max;
				}
				stcCNT.cnt_dbirai		+= wcnt_iri;
				stcCNT.cnt_dbirai_del	+= wcnt_iri_del;
				stcCNT.cnt_end			+= wcnt_rf;
					// 1.04 ADD
				stcCNT.cnt_dbirai_jdi	+= jd_max;
			} else {
				// ERROR
				strcpy( G_msg, "�f�[�^�����ŃG���[���������܂����B" );
				EditCsvMsg( G_msg );
				LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__);

			
			    //2006.12.08 Kim Jinsuk DB�G���[���ُ�I��������	
			    nSQLErrFlag = atoi(G_err);
				//nSQLErrFlag = -5000;
				sprintf(G_msg, "nSQLErrFlag %d", nSQLErrFlag);
				LogOut(LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);				
				
				
				if(( ret = Ydbrollback( )) != RTN_OK ){
						// ERROR
					strcpy( G_msg, "DB2��ROLLBACK�Ɏ��s���܂����B\n"  );
					EditCsvMsg( G_msg );
					LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm,
							__FILE__, __LINE__);
				}

				
				//==> 2006.12.08 Kim Jinsuk DB�G���[���ُ�I��������
		        if((nSQLErrFlag< 0)&& (nSQLErrFlag != -911)&&(nSQLErrFlag !=-803))
				{
				
					*stopValue = 1;

					sprintf(G_msg, "###### ��������������@DB�G���[���� #####");
                    LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm,
                            __FILE__, __LINE__);
					
					return (RTN_NG);	
				}
                //<== 2006.12.08 Kim Jinsuk DB�G���[���ُ�I��������

			}
			// KEY SET
			wcnt_iri = wcnt_iri_del = wcnt_rf = 0;

			memcpy( w_key,		&rbuf[2], MYAPP_LEN_KEY );
			memcpy( w_key_del,	&rbuf[77],1 );

			// DEBUG
			strcpy( G_msg, "KEY-BREAK���� END ---------------------->" );
			LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}

		ret = RTN_OK;

//-----< R1 >---------------------------------------------------------------
			// �˗� 
		if(( strncmp( rbuf, "R1", 2 ) == 0 )&&( rbuf[77]!='1' )){
			stcCNT.cnt_r1++;
			memcpy( &z05sjir1,	rbuf, sizeof( struct Z05SJIR1 ) );
			memset( &iri,		'\0', sizeof( struct _IRAI ));
			do {		/* Do-while�͂P��̂ݎ��s	�@	*/
				/* �ҏW */
				if(( ret= EditPncIrai( &z05sjir1, &iri )) != RTN_OK ){
					/* �װ*/
					ret = RTN_NG;
					break;
				}
				/* ���ʉӏ��̕ҏW */
				if( EditCommonIrai( &iri ) != RTN_OK ){
					/* �װ*/
					ret = RTN_NG;
					break;
				}
				// 1.03 ���ґ����̐���No���擾����
				if( wcnt_iri == 0 ){
					if((	w_max_zssdino = SelKanjyaZssdinoMax( &iri )) < 0 ){
						w_max_zssdino = stcPRM.myp_sedai;;
					}
					// 1.04 ADD �����������ڊ�l�擾�̂��ߔN���ޔ�
					memset( w_age,		'\0',	sizeof( w_age ));
					memset( w_age_kbn,	'\0',	sizeof( w_age_kbn ));
					memcpy( w_age,		z05sjir1.c_age,	sizeof(z05sjir1.c_age));
					memcpy( w_age_kbn,	z05sjir1.c_age_kbn,	
										sizeof( z05sjir1.c_age_kbn ));
				}
				iri.zssdino = w_max_zssdino;
				/* INSERT */
				if(( ret = InsIrai( &iri )) != RTN_OK ){
					if( ret != MYAPP_RTN_DUP ){
						// ERROR
						strcpy( G_msg,
							"�˗����o�^���ɃG���[���������܂����B" );
						EditCsvMsg( G_msg );
						LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, 
									__FILE__, __LINE__);
						ret = RTN_NG;

						break;
					}
					// �f�[�^�d��
					// 1.03 �����Đ��̈˗���UPDATE
					// 1.05 DELL if(( ret = UpdMichakuIrai( &iri )) != RTN_OK )[
					// 1.05 �����Đ��֘A�����������ڊ�l�Ď擾�p�Ɉ����ǉ�
					if(( ret = UpdMichakuIrai( &iri, w_age, w_age_kbn )) != RTN_OK ){
						if( ret == RTN_ZERO ){
							// �����Đ��ΏۊO�@WARNING -> SKIP
							// ����L�[�̑��f�[�^�~�ς̂���OK�Ƃ���
							strcpy( G_msg, "���Ɉ˗���񂪑��݂��܂��B" );
							EditCsvMsg( G_msg );
							LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, 
										__FILE__, __LINE__);
							stcCNT.cnt_irai_err++;
							ret = RTN_OK;
							break;
						} else {
							// ERROR
							strcpy( G_msg,
								"�˗����o�^���ɃG���[���������܂����B" );
							EditCsvMsg( G_msg );
							LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, 
										__FILE__, __LINE__);
						}
					}
				}
				wcnt_iri++;	
			} while( wcnt_iri < 1 );
//-----< R1 DEL>---------------------------------------------------------------
		} else if(( strncmp( rbuf, "R1", 2 ) == 0 )&&( rbuf[77]=='1' )){
			stcCNT.cnt_r1++;
			memcpy( &z05sjir1,	rbuf, sizeof( struct Z05SJIR1 ) );
			memset( &iri,		'\0', sizeof( struct _IRAI ));
			do {		/* Do-while�͂P��̂ݎ��s	�@	*/
				/* �ҏW */
				if(( ret= EditPncIrai( &z05sjir1, &iri )) != RTN_SKIP ){
					/* �װ*/
					ret = RTN_NG;
					break;
				}
				ret=RTN_OK;
				// Irai.tktyflg UPDATE
				if( UpdIraiSjflg( &iri ) != RTN_OK ){
					// ERROR -> Log��.sqc�ɂďo��
					//strcpy( G_msg, 
					//	"�˗����폜�t���O�X�V���ɃG���[���������܂����B" );
					//EditCsvMsg( G_msg );
					//LogOut( LT_ERR, LX_INS, G_err, G_msg, func_nm, 
					//				__FILE__, __LINE__);
					/* �װ*/
					ret = RTN_NG;
					break;
				}
				wcnt_iri_del++;	
			} while( wcnt_iri_del < 1 );
//-----< R2 >---------------------------------------------------------------
		} else if( strncmp( rbuf, "RF", 2 ) == 0 ){	// �˗�END
			stcCNT.cnt_rf++;
			memcpy( &z11sjirf, rbuf, sizeof( struct Z11SJIRF ) );
			do {		/* Do-while�͂P��̂ݎ��s	�@	*/
				// WARNING
				sprintf( G_msg, 
					"������N����[%s]  �˗��d�m�c������M���܂����B", 
					stcPRM.myp_kjnymd );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, 
							__FILE__, __LINE__);

				// Sysknrmst.iriendflg, irienddh UPDATE
						// ���˗������N�����͏����l���Z�b�g
				if( UpdSysknrmstIriend( INIT_DATE ) != RTN_OK ){
					/* �װ*/
					ret = RTN_NG;
					break;
				}
				wcnt_rf++;	
			} while( wcnt_rf < 1 );
		}
		if( ret != RTN_OK ){	
			stcCNT.cnt_irai_err++;
		}
	}	// <---------------------------------------------------read while end

//-----< 1FILE READ END >-------------------------------------------------------
	// �g���[���[�����̓G���[
	if( stcCNT.cnt_tr == 0 ){
		// ERROR
		strcpy( G_msg, "�g���[���[������܂���B" );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

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
			// �폜�̏ꍇ�́A���������������s��Ȃ�
			if( w_key_del[0] == 0 ){
				break;
			}
			// �����������ڂ̗L���`�F�b�N
       		if(( jd_max=SelCountJkmkmst( iri.utkymd
										, iri.irino, iri.sriymd )) < 1 ){
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
			strcpy( pJir[0].sIri.utkymd,		iri.utkymd );
			strcpy( pJir[0].sIri.irino,			iri.irino );
			strcpy( pJir[0].sIri.sriymd,		iri.sriymd );
			// �Ώۃf�[�^���̎擾
			if( SelJidoirai( pJir, jd_max ) !=  RTN_OK ){
				sprintf( G_err, "%d", errno );
				sprintf( G_msg, "��l�}�X�^�̓ǂݍ��݂Ɏ��s���܂����B" );
				LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm,
								__FILE__, __LINE__ );
				free( pJir );
				ret=RTN_NG;
				break;
			}
			for( i = 0; i < jd_max; i++ ){
				// EDIT
				strcpy( pJir[i].age,		w_age );
				strcpy( pJir[i].agekbn,		w_age_kbn );

				if( EditJidoIrai( &pJir[i] ) != RTN_OK ){
					// ERROR
					strcpy( G_msg,
						"���������˗����ҏW���ɃG���[���������܂����B" );
					EditCsvMsg( G_msg );
					LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, 
									__FILE__, __LINE__);
					ret = RTN_NG;
					break;
				}
				memcpy( &iri, &pJir[i].sIri, sizeof( struct _IRAI ));

				/* INSERT */
				if( InsIrai( &iri ) != RTN_OK ){
					// ERROR
					strcpy( G_msg,
						"���������˗����o�^���ɃG���[���������܂����B" );
					EditCsvMsg( G_msg );
					LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, 
									__FILE__, __LINE__);
					ret = RTN_NG;
					break;
				}
			}
			free( pJir );
			break;
		} while( 1 );
		// 1.04 ADD �������������@END ===================================

	}
	// �g���[���[������COMMIT���K�v�ȏꍇ�̍l��
		/* �G���[�����`�F�b�N	*/
	if( ret == RTN_OK ){
		if(( wcnt_iri > 0 )||( wcnt_iri_del > 0 )||( wcnt_rf > 0 )){
        	if(( ret = Ydbcommit( )) != RTN_OK ){
				sprintf( G_msg, "DB2��COMMIT�Ɏ��s���܂���\n" );
				EditCsvMsg( G_msg );
				LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
								__FILE__, __LINE__);
				stcCNT.cnt_dbirai -= wcnt_iri;
				stcCNT.cnt_dbirai_del -= wcnt_iri_del;
				stcCNT.cnt_end -= wcnt_rf;
			}
			stcCNT.cnt_dbirai += wcnt_iri;
			stcCNT.cnt_dbirai_del += wcnt_iri_del;
			stcCNT.cnt_end += wcnt_rf;
		}
	} else {
		// ERROR
		strcpy( G_msg,"�f�[�^�����ŃG���[���������܂����B" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);

      
       //2006.12.08 Kim Jinsuk DB�G���[���ُ�I��������	
		nSQLErrFlag = atoi(G_err);
		sprintf(G_msg,"nSQLErrFlag %d", nSQLErrFlag);
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
		

		if(( ret = Ydbrollback( )) != RTN_OK ){
			sprintf( G_msg, "DB2��ROLLBACK�Ɏ��s���܂���\n"  );
			EditCsvMsg( G_msg );
			LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
		}
		
		//==> 2006.12.08 Kim Jinsuk DB�G���[���ُ�I��������
		if( (nSQLErrFlag< 0)&& (nSQLErrFlag != -911)&&(nSQLErrFlag !=-803))
		{
			*stopValue =1;
			sprintf(G_msg, "###### ��������������@DB�G���[���� #####");
			printf("###### ��������������@DB�G���[���� ######\n");
			printf("nSQLErrFlag %d\n", nSQLErrFlag);

			return (RTN_NG);
		}	
        //<== 2006.12.08 Kim Jinsuk DB�G���[���ُ�I��������
		
	}
	// DEBUG
	sprintf( G_msg, "�ŏI���͌���(%d)iri[%d]end[%d]", 
		stcCNT.cnt_irai,stcCNT.cnt_dbirai,stcCNT.cnt_end  );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	memset( G_utkymd,	'\0', sizeof( G_utkymd ));
	memset( G_irino,	'\0', sizeof( G_irino ));
	memset( G_kntno,	'\0', sizeof( G_kntno ));
	memset( G_kmkcd,	'\0', sizeof( G_kmkcd ));
	G_zssdino=0;
	G_line=0;

	// TRACE
    sprintf( G_msg, "    �˗����e�[�u���쐬�������I�����܂���" );
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

    sprintf( G_msg, "            OTHER(SKIP)             �F%10d��"
        												,stcCNT.cnt_oth );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            �G���[�˗�����(SKIP)    �F%10d��"
														,stcCNT.cnt_irai_err );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            �˗����o�^����        �F%10dں���"
														,stcCNT.cnt_dbirai );
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            ���������˗����o�^�����F%10dں���"
														,stcCNT.cnt_dbirai_jdi);
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            �폜�˗�����(UPD)       �F%10d��"
														,stcCNT.cnt_dbirai_del);
	EditCsvMsg( G_msg );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

    sprintf( G_msg, "            �˗��d�m�c���X�V      �F%10dں���"
														,stcCNT.cnt_end );
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

	memset( rbuf, '\0', sizeof( rbuf ));
	if( fgets( rbuf, PNC_RECSIZE+10, pfp ) == NULL ){
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

	memset( rbuf, '\0', sizeof( rbuf ));
	if( fgets( rbuf, NXT_RECSIZE, nfp ) == NULL ){
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
