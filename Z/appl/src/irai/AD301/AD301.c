/******************************************************************************/
/*   �a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/*   �V�X�e�����F������V�X�e��                                               */
/*   �t�@�C�����FAD301.c                                                      */
/*   �T      �v�F������t�i�v���J�[�h���M�j�v���J�[�h�쐬                     */
/*	 OS        �FSUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   ����      �FDB2/C                                                        */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/04/03     INTEC.INC      CREATE                             */
/*  1.01     2006/05/03     INTEC.INC      UPDATE �����Ƃ���INI�t�@�C���w��   */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "bmllog.h"
#include "AD301.h"

/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/
iconv_t     G_ic;                       // with iconv
char		G_err[MYAPP_LEN_ERR+1];		// LogMessage(errcode)
char		G_msg[MYAPP_LEN_MSG+1];		// LogMessage
int			G_line;						// InputFileLineNo

char		G_otdir[256+1];				// �o��DIRECTRY
char		G_ext[10+1];				// �o�̓t�@�C���g���q

struct		_SYSKNRMST	pKnr;			// �V�X�e���Ǘ��}�X�^

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
	int		iri,kan;						// Loop
	int		kan_cnt, kan_end_cnt, iri_cnt = 0;
	int		ini_flg = 0;

	struct	Z00SJHD		z00;			// HD �w�b�_
	struct	Z01SJTR		z01;			// TR �g���[���[
	struct	Z12SJR1		z12;			// R1 �v���J�[�h

	struct	SHM stcShm;					// �I�����f���L������
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
	memset( &pKnr,		'\0', sizeof( struct _SYSKNRMST ) );
	G_line=0;

	// �p�����[�^�擾
	if( ParamCheckProc( argc, argv, &stcShm ) != RTN_OK ){
		/* ����ү���ޏo��	*/
		DispHelpMsg( argc, argv );
		exit( 1 );
	}

	/* 2�d�N���`�F�b�N	*/
	if( DaemonCheckProc( argc, argv ) != RTN_OK ){
		sprintf( G_msg, "�Q�d�N���h�~�̂��߁A�������I�����܂��B" );
		LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
		exit( 1 );
	}

	// ���L����������
	if( sFncShmCrt ( &stcShm ) < 0 ) {
		sprintf( G_msg, "���L�����������Ɏ��s�������߁A�������I�����܂��B" );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		exit( 1 );
	}

    // DB2�Ƃ̐ڑ� 
	if(( ret = Ydbconn( )) != RTN_OK ){
		sprintf( G_msg, "DB2�Ƃ̐ڑ��Ɏ��s���܂����B" );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		exit( 1 );
     }

	/* FILE OPEN FOR ICONV */
//    G_ic = iconv_open( "EUC-JP", "SHIFT-JIS" );

	// 	�V�X�e���Ǘ��}�X�^�擾
	SelSysknrmst( &pKnr );

	// HD,TR,R1 �ҏW
	memset( &z00,	'\0',	sizeof( struct	Z00SJHD ));
	memset( &z01,	'\0',	sizeof( struct	Z01SJTR ));
	memset( &z12,	'\0',	sizeof( struct	Z12SJR1 ));
	EditInitRequest( &z00, &z01, &z12 );

	// LOOP �񐔎擾 �e�t�@�C�������b�ɂP��쐬���邩
	// �����쐬�^�C�~���O���P�P�ʂƂ��A���P�ʖ��Ɉ˗��A���҂��쐬���邩
	iri_cnt = stcPRM.ifp_iri_time / stcPRM.ifp_bun_time;
	if( iri_cnt == 0 ){
		iri_cnt = 1;
	}
	kan_cnt = stcPRM.ifp_kan_time / stcPRM.ifp_bun_time;
	if( kan_cnt == 0 ){
		kan_cnt = 1;
	}

	sprintf( G_msg, "LOOP �� iri_cnt[%d] kan_cnt[%d]\n", iri_cnt, kan_cnt );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	/*=====================================================*/
	/* ���C�����[�e�B��                                    */
	/*=====================================================*/
	iri = kan = kan_end_cnt = 0;
	for( ; ; ){		// ......................................... daemon start
		sprintf( G_msg, "MainLoop iend[%s]bend[%s]ecnt[%d]================>\n", 
			pKnr.iriendflg, pKnr.bchendflg, kan_end_cnt );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

		// =============================================
		// �˗�������END��M�ς�
		// �˗�END��M�㊳�җv��3�񑗐M�ς�
		// =============================================
		if(( strcmp( pKnr.iriendflg, "1" ) == 0 )
		 &&( strcmp( pKnr.bchendflg, "1" ) == 0 )
		 &&( kan_end_cnt >= 3 )){
			// �����I��
			break;
		}

		// =============================================
		// �������ʁ@�v���J�[�h�쐬
		// =============================================
		if( WriteRequestFile( MYAPP_BUN, &z00, &z01, &z12 ) == RTN_NG ){
			// ERROR
			strcpy( G_msg, "�������ʁ@�v���J�[�h�쐬�����ɂ�"
				"�G���[���������܂����B");
			LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}

		iri++;
		kan++;

		// =============================================
		// 	����@or�@�������H��o�́@->�@�˗��v���쐬
		// =============================================
		if(( ini_flg == 0 )||( iri == iri_cnt )){
			iri=0;
			// �˗����@�v���J�[�h�쐬
			if( WriteRequestFile( MYAPP_IRI, &z00, &z01, &z12 ) == RTN_NG ){
				// ERROR
				strcpy( G_msg, "�˗����@�v���J�[�h�쐬�����ɂ�"
					"�G���[���������܂����B");
				LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, 
						__FILE__, __LINE__);
			}
		}

		// ===========================================================
		// 	����@or�@�������H��o�́@or�@�˗�END�㊳�җv���񑗐M�ς�
		//	-> ���җv���쐬
		// ===========================================================
		if(( ini_flg == 0 )||( kan == kan_cnt )){
			if( kan_end_cnt < 3 ){
				kan=0;
				// ���ҏ��@�v���J�[�h�쐬
				if( WriteRequestFile( MYAPP_KAN, &z00, &z01, &z12 ) == RTN_NG ){
					// ERROR
					strcpy( G_msg, "���ҏ��@�v���J�[�h�쐬�����ɂ�"
						"�G���[���������܂����B");
					LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, 
							__FILE__, __LINE__);
				}
			}
			if( strcmp( pKnr.iriendflg, "1" ) == 0 ){
				kan_end_cnt++;
			}
		}
		// �����t���O��ON��
		if( ini_flg == 0 ){
			ini_flg = 1;
		}

		// SLEEP
		sprintf( G_msg, "SLEEP .....BUN_SLEEP_TIME[%d]", stcPRM.ifp_bun_time );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

		sleep( stcPRM.ifp_bun_time );
	
		//------------------
		// �I�����f
		//------------------
			// ���L�������擾
		if( sFncShmGet ( &stcShm, &li_stopFlg ) < 0 ){
			// WARNING
			sprintf( G_msg,
				"���L�����������Ɏ��s�������߁A�������I�����܂��B" );
			LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			break;
		}
		if( li_stopFlg == 1 ){
				// TRACE
			sprintf( G_msg, "�I���w�����o�����߁A�������I�����܂��B");
			LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			break;
		} 

		// DAEMON SLEEP
		sprintf( G_msg, "SLEEP ..............[%d]", stcPRM.myp_sleep );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

		sleep( stcPRM.myp_sleep );
	
	}	// ...................................................... daemon for

	/*=====================================================*/
	/*	�I������                                           */
	/*=====================================================*/
	// ICONV CLOSE
//    iconv_close( G_ic );

	/* DB2�Ƃ̐ڑ����� */
	if(( ret = Ydbdisconn( )) != RTN_OK ){
		// ERROR
		sprintf( G_msg, "DB2�Ƃ̐ڑ������Ɏ��s���܂����B" );
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
fprintf(stderr,"����:�v���J�[�h�쐬����\n" );
fprintf(stderr,"    :������t�i�v���J�[�h���M�j�v���J�[�h���쐬���܂�\n" );
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
	char	*p_fini;					/* 1.01 INI FILE ����	 */
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
	// 1.01 INI FILE �������������
	if( argc >= 2 ){
		p_fini = argv[1];
	} else {
		p_fini = MYAPP_INIFILE;
	}
	strncpy( stcPRM.myp_exefile, cp, sizeof( stcPRM.myp_exefile ) - 1 );
	strcpy( stcPRM.ifp_fprefix, "REQ" );
	stcPRM.myp_debug=0;
	stcPRM.myp_sleep=0;
	stcPRM.ifp_bun_time=120;
	stcPRM.ifp_iri_time=600;
	stcPRM.ifp_kan_time=1200;
	
	//-------------------------------
	// LOG�o�͏�������
	//-------------------------------
	//cp = GetIniFile( "SERVER.LOG", "LOGINI", MYAPP_INIFILE );
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
		// �������ʗv��
    cp = GetIniFile( "HOST.PARA", "BUN_OTDIR", p_fini );
    if( cp != NULL ) {
		// ���ϐ�($HOME)��W�J���Ă���Z�b�g
		strcpy( stcPRM.ifp_bun_otdir, EnvRef( cp ));
    }
    cp = GetIniFile( "HOST.PARA", "BUN_EXT", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_bun_ext );
    }
    cp = GetIniFile( "HOST.PARA", "BUN_YKKBN", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_bun_ykkbn );
    }
    cp = GetIniFile( "HOST.PARA", "BUN_TIME", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%d", &stcPRM.ifp_bun_time );
    }

		// �˗����v��
    cp = GetIniFile( "HOST.PARA", "IRI_OTDIR", p_fini );
    if( cp != NULL ) {
		// ���ϐ�($HOME)��W�J���Ă���Z�b�g
		strcpy( stcPRM.ifp_iri_otdir, EnvRef( cp ));
    }
    cp = GetIniFile( "HOST.PARA", "IRI_EXT", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_iri_ext );
    }
    cp = GetIniFile( "HOST.PARA", "IRI_YKKBN", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_iri_ykkbn );
    }
    cp = GetIniFile( "HOST.PARA", "IRI_TIME", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%d", &stcPRM.ifp_iri_time );
    }

		// ���ҏ��v��
    cp = GetIniFile( "HOST.PARA", "KAN_OTDIR", p_fini );
    if( cp != NULL ) {
		// ���ϐ�($HOME)��W�J���Ă���Z�b�g
		strcpy( stcPRM.ifp_kan_otdir, EnvRef( cp ));
    }
    cp = GetIniFile( "HOST.PARA", "KAN_EXT", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_kan_ext );
    }
    cp = GetIniFile( "HOST.PARA", "KAN_YKKBN", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_kan_ykkbn );
    }
    cp = GetIniFile( "HOST.PARA", "KAN_TIME", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%d", &stcPRM.ifp_kan_time );
    }

		// HD,TR �ҏW���
    cp = GetIniFile( "HOST.PARA", "FPREFIX", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_fprefix );
    }
    cp = GetIniFile( "HOST.PARA", "SOSINSAKI", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_sosinsaki );
    }
    cp = GetIniFile( "HOST.PARA", "SOSINMOTO", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_sosinmoto );
    }
    cp = GetIniFile( "HOST.PARA", "KAN_DFLOW", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_kan_dflow );
    }
    cp = GetIniFile( "HOST.PARA", "IRI_DFLOW", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_iri_dflow );
    }
    cp = GetIniFile( "HOST.PARA", "BUN_DFLOW", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%s", stcPRM.ifp_bun_dflow );
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
    cp = GetIniFile( "MYAPP.PARA", "MYAPP_SLEEP", p_fini );
    if( cp != NULL ) {
        sscanf( cp, "%d", &stcPRM.myp_sleep );
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

	sprintf( G_msg, "BUNCYU   [%s][%s][%s][%d]"
		,stcPRM.ifp_bun_otdir	,stcPRM.ifp_bun_ext
		,stcPRM.ifp_bun_ykkbn,stcPRM.ifp_bun_time );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "IRAI     [%s][%s][%s][%d]"
		,stcPRM.ifp_iri_otdir	,stcPRM.ifp_iri_ext
		,stcPRM.ifp_iri_ykkbn,stcPRM.ifp_iri_time );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "KANJYA   [%s][%s][%s][%d]"
		,stcPRM.ifp_kan_otdir	,stcPRM.ifp_kan_ext
		,stcPRM.ifp_kan_ykkbn,stcPRM.ifp_kan_time );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	sprintf( G_msg, "Dflow    [%s][%s][%s]", stcPRM.ifp_bun_dflow
			, stcPRM.ifp_iri_dflow, stcPRM.ifp_kan_dflow );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	sprintf( G_msg, "G_sleep   [%d]",	stcPRM.myp_sleep );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	sprintf( G_msg, "app_gene   [%s]",	stcPRM.myp_gene );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FEditInitRequest                                               */
/*  �@�\�T�v  �F�o�m�b���M�p�w�b�_�[�A�g���[���A�v���J�[�h�ҏW����            */
/*	�\��  : int	Lmk_hdtr( syok, pg, dflow, z00, z01 )                         */
/*  ��    ��  �F                                                              */
/*	����  : (in) 	char	*syok;	 	�E������                              */
/*		(in)	char	*pg;		PG_ID                                     */
/*		(in)	char	*dflow;	 	�ް��۰ID	                              */
/*		(out)	struct  Z00SJHD	*z00;  	PNC����Mͯ�ް�\����	              */
/*		(out)	struct 	Z01SJTR *z01;   PNC����M�ڰװ�\����                  */
/*                                                                            */
/*	��-ݒl:  0  :����I��                                                     */
/*		-1  :�װ                                                              */
/*                                                                            */
/*   ��P���� �Fstruct		dirent *     �f�B���N�g���\����                   */
/*  �o    ��  �F�Ȃ�                                                          */
/*  ���A���  �F INT                                                          */
/*               0		: �ΏۊO�t�@�C��                                      */
/*               1		: �Ώۃt�@�C��                                        */
/******************************************************************************/
int	EditInitRequest( z00, z01, z12 )
struct  Z00SJHD		*z00;    	/* PNC����Mͯ�ް�\����	*/
struct 	Z01SJTR 	*z01;    	/* PNC����M�ڰװ�\���� */ 
struct 	Z12SJR1 	*z12;    	/* PNC����M�ڰװ�\���� */ 
{
#define	SQL_LOCK -54			/* record lock by other user	*//* ADD H001 */
#define	MAX_LOCK 50			/* ۯ����s�ő�� 	*//* ADD H001 */
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	 */
	char	w_fnm[256];

	int     ret;
	char    cbuf[512];
	char    dbuf[512];
	int	rcnt;			/* ۯ����s��		*//* ADD H001 */

	rcnt = 0;						 /* ADD H001 */

	strcpy( func_nm, "EditInitReqest" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	//====================================
	// PNC����M �w�b�_�A�g���[���[�쐬 
	//====================================
	memset( z00, ' ', sizeof( struct Z00SJHD ) );
    memset( z01, ' ', sizeof( struct Z01SJTR ) );
	memset( z12, ' ', sizeof( struct Z12SJR1 ) );

	/* ں��ގ��ʎq		*/
   	memcpy( z00->c_sbt, "HD", sizeof( z00->c_sbt ));
    memcpy( z01->c_sbt, "TR", sizeof( z01->c_sbt ));
   	memcpy( z12->c_sbt, "R1", sizeof( z12->c_sbt ));

	/* ���M��               */
	memcpy( z00->c_sosinsaki,	stcPRM.ifp_sosinsaki, 
								strlen( stcPRM.ifp_sosinsaki ));
	memcpy( z01->c_sosinsaki,	stcPRM.ifp_sosinsaki, 
								strlen( stcPRM.ifp_sosinsaki));

	/* ���M��               */
	memcpy( z00->c_sosinmoto,	stcPRM.ifp_sosinmoto, 
								strlen( stcPRM.ifp_sosinmoto ));
	memcpy( z01->c_sosinmoto,	stcPRM.ifp_sosinmoto, 
								strlen( stcPRM.ifp_sosinmoto ));

	/* ���M�������N����     */
	memset( cbuf, '\0',	sizeof( cbuf ));
	sprintf( cbuf, "%.4s%.2s%.2s", 
		pKnr.kjnsriymd, &pKnr.kjnsriymd[5], &pKnr.kjnsriymd[8] );
	memcpy( z00->c_opedate, cbuf, sizeof( z00->c_opedate ));
	memcpy( z01->c_opedate, cbuf, sizeof( z01->c_opedate ));
	memcpy( z12->c_opedate, cbuf, sizeof( z12->c_opedate ));

	/* �ʔ�                 */
	/* �ް��۰ID		*/
		// ���M�t�@�C���쐬���ɕҏW	

	/* ����ں��ތ��� & �_��ں��ތ����P�`�P�T */
	/* '0' �ҏW(�����������p) */
	memset( cbuf, '0', sizeof( z01->c_reccnt ) );

	/* ����ں��ތ���	<- 3REC �Œ�	*/
   	memcpy( z01->c_reccnt, cbuf, sizeof( z01->c_reccnt ));
	z01->c_reccnt[7] = '3';
	/* �_��ں��ތ����P�`�P�T*/
		// R1 			<- 1REC �Œ�
	memcpy( z01->c_reccnt01, cbuf, sizeof( z01->c_reccnt01 ));
	z01->c_reccnt01[7] = '1';
	memcpy( z01->c_reccnt02, cbuf, sizeof( z01->c_reccnt02 ));
	memcpy( z01->c_reccnt03, cbuf, sizeof( z01->c_reccnt03 ));
	memcpy( z01->c_reccnt04, cbuf, sizeof( z01->c_reccnt04 ));
	memcpy( z01->c_reccnt05, cbuf, sizeof( z01->c_reccnt05 ));
	memcpy( z01->c_reccnt06, cbuf, sizeof( z01->c_reccnt06 ));
	memcpy( z01->c_reccnt07, cbuf, sizeof( z01->c_reccnt07 ));
	memcpy( z01->c_reccnt08, cbuf, sizeof( z01->c_reccnt08 ));
	memcpy( z01->c_reccnt09, cbuf, sizeof( z01->c_reccnt09 ));
	memcpy( z01->c_reccnt10, cbuf, sizeof( z01->c_reccnt10 ));
	memcpy( z01->c_reccnt11, cbuf, sizeof( z01->c_reccnt11 ));
	memcpy( z01->c_reccnt12, cbuf, sizeof( z01->c_reccnt12 ));
	memcpy( z01->c_reccnt13, cbuf, sizeof( z01->c_reccnt13 ));
	memcpy( z01->c_reccnt14, cbuf, sizeof( z01->c_reccnt14 ));
	memcpy( z01->c_reccnt15, cbuf, sizeof( z01->c_reccnt15 ));

	/* ���Ұ�1              */
	memset( z00->c_param1, ' ', sizeof( z00->c_param1 ));
	/* ���Ұ�2              */
	memset( z00->c_param2, ' ', sizeof( z00->c_param2 ));

	// �����T�e���C�g
	memcpy( z12->c_sateraito, pKnr.sateid, sizeof( z12->c_sateraito ));
		// �v���敪	<-���M�t�@�C���쐬���ɕҏW
	
	/* �\��                 */
	memset( z00->c_yobi, ' ', sizeof( z00->c_yobi ));
	memset( z01->c_yobi, ' ', sizeof( z01->c_yobi ));

	/* FILLER               */
	memset( z00->c_filler, ' ', sizeof( z00->c_filler ));
	memset( z01->c_filler, ' ', sizeof( z01->c_filler ));
	memset( z12->c_filler, ' ', sizeof( z12->c_filler ));
	
	/* ���s����             */
	memcpy( z00->c_kaigyo, "\n", sizeof( z00->c_kaigyo ));
	memcpy( z01->c_kaigyo, "\n", sizeof( z01->c_kaigyo ));
	memcpy( z12->c_kaigyo, "\n", sizeof( z12->c_kaigyo ));

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  �� �� ��  �FWriteRequestFile                                              */
/*  �@�\�T�v  �F�o�m�b�v���J�[�h�o�͏���                                      */
/*  ��    ��  �F                                                              */
/*   ��P���� �F FILE	pfp	: ���̓t�@�C�����ʎq                              */
/*  �o    ��  �F �Ȃ�                                                         */
/*  ���A���  �F INT                                                          */
/*               RTN_OK     : ����                                            */
/*               RTN_NG     : ���s                                            */
/******************************************************************************/
int		WriteRequestFile( kbn, z00, z01, z12 )
int		kbn;
struct	Z00SJHD		*z00;
struct	Z01SJTR		*z01;
struct	Z12SJR1		*z12;
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����		*/
	int		ret;							/* �֐��߂�l	*/
	int		inp_cnt;
	int		i,j;							/* index		*/
	char	w_ofile[256+1];					// OutPutFile
	char	wbuf[256+1];					// work area
	char	w_modenm[10+1];				// work area

	FILE	*fp;						// �Ǎ�̧���߲��
	struct	dirent	**namelist;			// get input file
	struct	stat	statbuf;			// get input file status

	/* �����ݒ�	*/
	strcpy( func_nm,	"WriteRequestFile" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	if( stcPRM.myp_debug == 1 ){
		if( kbn == MYAPP_BUN ){
			strcpy( w_modenm, "�����v��" );
		} else if( kbn == MYAPP_IRI ){
			strcpy( w_modenm, "�˗��v��" );
		} else if( kbn == MYAPP_KAN ){
			strcpy( w_modenm, "���җv��" );
		}
	}

	/* �ر	*/
	ret = RTN_OK;
	fp = NULL;

	//===================
	// �t�@�C���쐬���f
	//===================

	// �����M�t�@�C���L���`�F�b�N ++++++++++++++++++++++++++++++++++++
	memset( G_otdir,	'\0',	sizeof( G_otdir ));
	memset( G_ext,		'\0',	sizeof( G_ext ));

	switch( kbn ){
	case	MYAPP_BUN :
		strcpy( G_otdir,	stcPRM.ifp_bun_otdir );	
		strcpy( G_ext,		stcPRM.ifp_bun_ext );	
		break;
	case	MYAPP_IRI :
		strcpy( G_otdir,	stcPRM.ifp_iri_otdir );	
		strcpy( G_ext,		stcPRM.ifp_iri_ext );	
		break;
	case	MYAPP_KAN :
		strcpy( G_otdir,	stcPRM.ifp_kan_otdir );	
		strcpy( G_ext,		stcPRM.ifp_kan_ext );	
		break;
	default:
		break;
	}

	inp_cnt = scandir( G_otdir, &namelist, (void*)FileFilter, alphasort);
	if( inp_cnt > 0 ){
			// DEBUG LOG
		sprintf( G_msg, "[%s]�����M�t�@�C���̗L->SKIP", w_modenm );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

		// �����M�t�@�C�������݂��邽��SKIP
		return( RTN_SKIP );

	} else if( inp_cnt < 0){
			// ERROR LOG
		sprintf( G_err, "%d", errno );
		sprintf( G_msg, "�o�̓t�@�C���̗L���擾(scandir)�Ɏ��s���܂����B" );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		return( RTN_NG );
	} 
	// scandir �t�@�C������free
	free( namelist );

	// END��񔻒f +++++++++++++++++++++++++++++++++++++++++++++
		// �V�X�e���Ǘ����擾
	if( SelSysknrmst( &pKnr ) != RTN_OK ){
		sprintf( G_msg, "������N�����̎擾�Ɏ��s���܂����B" );
		LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		return( RTN_NG );
	}
		// ����
	if(( kbn == MYAPP_BUN )&&( pKnr.bchendflg[0] == '1' )){
			// DEBUG LOG
		sprintf( G_msg, "[%s]END����M�ς�", w_modenm );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

		return( RTN_SKIP );
	}
		// �˗�	( ���҂�END���o�͌�񐔂Ŕ��f�j
	if(( kbn == MYAPP_IRI )&&( pKnr.iriendflg[0] == '1' )){
			// DEBUG LOG
		sprintf( G_msg, "[%s]END����M�ς�", w_modenm );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

		return( RTN_SKIP );
	}

	//===================
	// �t�@�C���쐬����
	//===================
	// �ʔ�UPDATE
	// Sysknrmst.ssntub UPDATE & COMMIT
	if(( pKnr.ssntubn = UpdSysknrmstSsntubn( )) < 0 ){
		return( RTN_NG );
	}

	//------------------
	// OUTPUT FILE OPEN
	//------------------
		// �t�@�C�����쐬
		//	PREFIX + ������N���� + �ʔ� + ����.�g���q
	memset( w_ofile,	'\0',	sizeof( w_ofile ));
	sprintf( w_ofile, "%s/%s%.8s%04d%.2s%.2s.%s"
		, G_otdir, stcPRM.ifp_fprefix, z00->c_opedate, pKnr.ssntubn
		, &pKnr.ksndh[11], &pKnr.ksndh[14], G_ext );

		// OUTPUT FILE OPEN
	if(( fp = fopen( w_ofile, "w" )) == NULL ){
		// ERROR
		sprintf( G_err, "%d", errno );
		sprintf( G_msg, "[%s]�t�@�C���I�[�v���Ɏ��s���܂����B", w_ofile );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		return( RTN_NG );
	}

	//------------------
	// EDIT
	//------------------
		// �ʔ�
	memset( wbuf,	'\0',	sizeof( wbuf ));
	sprintf( wbuf, "%0*d",	sizeof( z00->c_tuban ), pKnr.ssntubn );
	memcpy( z00->c_tuban,	wbuf,	sizeof( z00->c_tuban ));
	memcpy( z01->c_tuban,	wbuf,	sizeof( z01->c_tuban ));
	
	switch( kbn ){
	case	MYAPP_BUN :
		memcpy( z00->c_dflow,	stcPRM.ifp_bun_dflow,	
								strlen( stcPRM.ifp_bun_dflow ));
		memcpy( z01->c_dflow,	stcPRM.ifp_bun_dflow,
								strlen( stcPRM.ifp_bun_dflow ));
		memcpy( z12->c_yokyu_kbn,
			stcPRM.ifp_bun_ykkbn,	sizeof( z12->c_yokyu_kbn ));
		break;
	case	MYAPP_IRI :
		memcpy( z00->c_dflow,	stcPRM.ifp_iri_dflow,
								strlen( stcPRM.ifp_iri_dflow ));
		memcpy( z01->c_dflow,	stcPRM.ifp_iri_dflow,
								strlen( stcPRM.ifp_iri_dflow ));
		memcpy( z12->c_yokyu_kbn,
			stcPRM.ifp_iri_ykkbn,	sizeof( z12->c_yokyu_kbn ));
		break;
	case	MYAPP_KAN :
		memcpy( z00->c_dflow,	stcPRM.ifp_kan_dflow,
								strlen( stcPRM.ifp_kan_dflow ));
		memcpy( z01->c_dflow,	stcPRM.ifp_kan_dflow,
								strlen( stcPRM.ifp_kan_dflow ));
		memcpy( z12->c_yokyu_kbn,
			stcPRM.ifp_kan_ykkbn,	sizeof( z12->c_yokyu_kbn ));
		break;
	default:
		break;
	}

		// HD
	if( fwrite( z00, sizeof( struct Z00SJHD ), 1, fp ) < 1 ){
			// ERROR LOG
		sprintf( G_err, "%d", errno );
		sprintf( G_msg,"[%s]�t�@�C���o�͂Ɏ��s���܂����B[%s]",w_modenm,w_ofile);
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		fclose( fp );
		if( stat( w_ofile, &statbuf ) == 0 ){
			unlink( w_ofile );
		}
		return( RTN_NG );
	}

		// R1
	if( fwrite( z12, sizeof( struct Z12SJR1 ), 1, fp ) < 1 ){
			// ERROR LOG
		sprintf( G_err, "%d", errno );
		sprintf( G_msg,"[%s]�t�@�C���o�͂Ɏ��s���܂����B[%s]",w_modenm,w_ofile);
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		fclose( fp );
		if( stat( w_ofile, &statbuf ) == 0 ){
			unlink( w_ofile );
		}
		return( RTN_NG );
	}

		// TR
	if( fwrite( z01, sizeof( struct Z01SJTR ), 1, fp ) < 1 ){
			// ERROR LOG
		sprintf( G_err, "%d", errno );
		sprintf( G_msg,"[%s]�t�@�C���o�͂Ɏ��s���܂����B[%s]",w_modenm,w_ofile);
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		fclose( fp );
		if( stat( w_ofile, &statbuf ) == 0 ){
			unlink( w_ofile );
		}
		return( RTN_NG );
	}

	//------------------
	// OUTPUT FILE CLOSE
	//------------------
	fclose( fp );

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
	char	wbuf[25];
	struct	stat	statbuf;				// get input file status

	strcpy( func_nm, "FileFilter" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	// �f�B���N�g���͏���
	sprintf( w_fnm, "%s/%s", G_otdir, namelist->d_name );
	stat( w_fnm, &statbuf );
	if( S_ISDIR( statbuf.st_mode )){
		// DEBUG
		sprintf( G_msg, "DIR SKIP mode: 0%o [%s]" ,statbuf.st_mode, w_fnm );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
		// �ΏۊO
		return( 0 );
	}
	// �Ώۃt�@�C���̐擪 AND �g���q�ɂ�锻�f
	if( memcmp( namelist->d_name, stcPRM.ifp_fprefix 
					, strlen( stcPRM.ifp_fprefix )) == 0 ){
		memset( wbuf,	'\0',	sizeof( wbuf ));
		sprintf( wbuf, ".%s", G_ext );
		if( memcmp( strrchr( namelist->d_name, '.' ) , wbuf
						, strlen( G_ext ) + 1 ) == 0 ){
			// DEBUG
			sprintf( G_msg, "�����Ώ� mode: 0%o [%s]" ,statbuf.st_mode, w_fnm );
			LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// OK
			return ( 1 );
		}
	}

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return ( 0 );
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
